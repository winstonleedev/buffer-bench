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

std::chrono::time_point<std::chrono::system_clock> endTime, start;

void InitTime() {
    start = std::chrono::system_clock::now();
}

double SecondsSinceStart() {
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = endTime - start;
    return diff.count();
}

void Run() {
    printf("=================================\n");

    printf("%s bench start...\n", "RAW");
    uint64_t total = 0;
    double create = 0, receive = 0, use = 0, free = 0;

    std::string addr = CLIENT_ACCESS_RAW;

    evpp::EventLoop loop;
    evpp::TCPClient client(&loop, addr, "TCPPingPongClient");
    client.SetMessageCallback([&loop, &client](const evpp::TCPConnPtr& conn,
                                               evpp::Buffer* msg) {
        client.Disconnect();
    });

    client.SetConnectionCallback([](const evpp::TCPConnPtr& conn) {
        if (conn->IsConnected()) {
            conn->Send("hello");
        } else {
            conn->loop()->Stop();
        }
    });
    client.Connect();
    loop.Run();

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
        double time2 = SecondsSinceStart();

        // TODO make TCP client
        evpp::Buffer * message = nullptr; //client.GetFooBarContainer(id);

        double time3 = SecondsSinceStart();
        auto result = RAWBench::Use(message);
        assert(result == 218812692406581874);

        double time4 = SecondsSinceStart();
        total += result;

        double time5 = SecondsSinceStart();
        create += time2 - time1;
        receive += time3 - time2;
        use += time4 - time3;
        free += time5 - time4;
    }

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

