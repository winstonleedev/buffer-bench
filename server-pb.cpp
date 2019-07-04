#include "pbbench.pb.h"
#include <pbbench.grpc.pb.h>

#include <grpcpp/grpcpp.h>

#include "bench.h"
#include "config.h"
#include "protobuf/benchpb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using namespace benchpb;

// Logic and data behind the server's behavior.
class FooBarServiceImpl final : public FooBarService::Service {
    PBBench *instance = NewPBBench();
    Status GetFooBarContainer(ServerContext *context,
                              const ID *request,
                              FooBarContainer *reply) override {
        size_t len;
        instance->Encode(*reply);
        return Status::OK;
    }
};

class PBServer: BenchServer {

public:
    PBServer() = default;

    void StartServer() override {
        std::string server_address(SERVER_ADDRESS_PROTO);
        FooBarServiceImpl service;

        ServerBuilder builder;
        // Listen on the given address without any authentication mechanism.
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        // Register "service" as the instance through which we'll communicate with
        // clients. In this case it corresponds to an *synchronous* service.
        builder.RegisterService(&service);
        // Finally assemble the server.
        auto server = builder.BuildAndStart();
        std::cout << "Server listening on " << server_address << std::endl;

        // Wait for the server to shutdown. Note that some other thread must be
        // responsible for shutting down the server for this call to ever return.
        server->Wait();
    }
};

int main() {

    auto server = new PBServer();
    server->StartServer();
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}

