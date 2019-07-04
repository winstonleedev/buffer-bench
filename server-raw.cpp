#include "bench.h"
#include "config.h"

class RAWServer: BenchServer {

public:
    RAWServer() = default;

    void StartServer() override {
        std::string server_address(SERVER_ADDRESS_PROTO);
        /*
         * TODO implement a TCP server
         */
    }
};
using namespace std;

int main() {
    auto server = new RAWServer();
    server->StartServer();

    return 0;
}

