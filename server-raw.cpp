#include <evpp/tcp_server.h>
#include <evpp/buffer.h>
#include <evpp/tcp_conn.h>

#include "bench.h"
#include "raw/benchraw.h"
#include "config.h"

using namespace std;

RAWBench *instance;

void OnConnection(const evpp::TCPConnPtr& conn) {
    if (conn->IsConnected()) {
        conn->SetTCPNoDelay(true);
        cout << "A new connection from " << conn->remote_addr();
    } else {
        cout << "Lost the connection from " << conn->remote_addr();
    }
}

void OnMessage(const evpp::TCPConnPtr& conn,
               evpp::Buffer* msg) {
    evpp::Buffer * output = instance->Encode();
    conn->Send(output);
}

int main() {
    instance = NewRAWBench();
    std::string addr = SERVER_ADDRESS_RAW;
    int thread_num = 1;

    evpp::EventLoop loop;
    evpp::TCPServer server(&loop, addr, "RAW BENCH", thread_num);
    server.SetMessageCallback(&OnMessage);
    server.SetConnectionCallback(&OnConnection);
    server.Init();
    server.Start();
    loop.Run();
    return 0;
}

