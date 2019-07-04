#include "fbbench.grpc.fb.h"
#include "fbbench_generated.h"

#include "fbbench.h"
#include "../config.h"
#include <grpc++/grpc++.h>

#include <iostream>
#include <memory>
#include <string>

void RunServer() {
    std::string server_address(SERVER_ADDRESS_FBS);
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
