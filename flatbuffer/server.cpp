#include "fbbench.grpc.fb.h"
#include "fbbench_generated.h"

#include "fbbench.h"
#include <grpc++/grpc++.h>

#include <iostream>
#include <memory>
#include <string>

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    FooBarServiceImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cerr << "Server listening on " << server_address << std::endl;

    server->Wait();
}

int main(int argc, const char *argv[]) {
    RunServer();
    return 0;
}
