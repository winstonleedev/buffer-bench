#include <iostream>
#include <assert.h>
#include "bench.h"
#include "config.h"
#include <chrono>
#include <zconf.h>
#include <zlib.h>
#include "raw/benchraw.h"
#include <evpp/tcp_client.h>
#include <evpp/buffer.h>
#include <evpp/tcp_conn.h>
#include <mutex>
#include <condition_variable>

std::chrono::time_point<std::chrono::system_clock> endTime, start;

void InitTime() {
    start = std::chrono::system_clock::now();
}

double SecondsSinceStart() {
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = endTime - start;
    return diff.count();
}

std::mutex m;
std::condition_variable cv;
evpp::Buffer *outgoing;
evpp::Buffer *incoming;
bool readyToSend = false;
bool receivedSomething = false;

class TCPClient {
    evpp::EventLoop loop;
    evpp::TCPClient * client;
public:

    TCPClient() {
        std::string addr = CLIENT_ACCESS_RAW;

        client = new evpp::TCPClient(&loop, addr, "TCPPingPongClient");

        client->SetMessageCallback([this](const evpp::TCPConnPtr &conn,
                                                   evpp::Buffer *msg) {
            receivedSomething = true;
            incoming = msg;
            cv.notify_one();
        });

        client->SetConnectionCallback([](const evpp::TCPConnPtr &conn) {
            if (conn->IsConnected()) {
                std::unique_lock<std::mutex> lk(m);
                cv.wait(lk, [] { return readyToSend; });

                conn->Send(outgoing);
                readyToSend = false;
            }
        });
        client->Connect();
    }

    void Start() {
        loop.Run();
    }

    void Stop() {
        loop.Stop();
        client->Disconnect();
    }
};

void Run() {
    printf("=================================\n");

    printf("%s bench start...\n", "RAW");
    uint64_t total = 0;
    double create = 0, receive = 0, use = 0, free = 0;

    auto client = new TCPClient();
    std::thread clientThread(&TCPClient::Start, client);

    // we use an outer loop also, since bumping up "iterations" to 10000 or so
    // puts so much strain on the allocator that use of free() dwarfs all
    // timings. Running the benchmark in batches gives more realistic timings and
    // keeps it accurate
    for (int j = 0; j < ITERATIONS_OUTER; j++) {
        InitTime();

        double time1 = SecondsSinceStart();
        ID id{};
        id.id = 42;
        auto request = new evpp::Buffer();
        request->Append(&id, sizeof(ID));
        // send data to the worker thread
        {
            std::lock_guard<std::mutex> lk(m);
            outgoing = request;
            readyToSend = true;
        }
        cv.notify_one();
        double time2 = SecondsSinceStart();

        evpp::Buffer *message = nullptr;
        // wait for the worker
        {
            std::unique_lock<std::mutex> lk(m);
            cv.wait(lk, []{return receivedSomething;});
        }
        message = incoming;

        double time3 = SecondsSinceStart();
        auto result = RAWBench::Use(message);
        // TODO Find out why this is wrong
        // assert(result == 218812692406581874);

        double time4 = SecondsSinceStart();
        total += result;

        double time5 = SecondsSinceStart();
        create += time2 - time1;
        receive += time3 - time2;
        use += time4 - time3;
        free += time5 - time4;
    }
    client->Stop();
    clientThread.join();

    printf("total bytes = %lu\n", total);
    printf("* %f create time\n", create);
    printf("* %f receive time\n", receive);
    printf("* %f use\n", use);
    printf("* %f free\n", free);
    printf("* %f total time\n", create + receive + use + free);
}

int main() {
    InitTime();
    Run();
    return 0;
}

