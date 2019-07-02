//
// Created by Thanh Phu on 7/2/2019.
//

#ifndef BUFFER_BENCH_FBBENCH_H
#define BUFFER_BENCH_FBBENCH_H

#include "fbbench_generated.h"
#include "fbbench.grpc.fb.h"
#include "../bench.h"
#include "../config.h"
#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using namespace benchfb;
using namespace std;

struct FBBench : Bench {
    void Encode(void *buf, size_t &len) {
        const int veclen = 3;
        flatbuffers::Offset<FooBar> vec[veclen];
        flatbuffers::FlatBufferBuilder fbb;
        for (int i = 0; i < veclen; i++) {
            // We add + i to not make these identical copies for a more realistic
            // compression test.
            auto foo = CreateFoo(fbb, 0xABADCAFEABADCAFE + i, 10000 + i, '@' + i, 1000000 + i);
            auto bar = CreateBar(fbb, foo, 123456 + i, 3.14159f + i, 10000 + i);
            auto name = fbb.CreateString("Hello, World!");
            auto foobar = CreateFooBar(fbb, bar.o, name, 3.1415432432445543543 + i, i);
            vec[i] = foobar;
        }
        auto location = fbb.CreateString("http://google.com/flatbuffers/");
        auto foobarvec = fbb.CreateVector(vec, veclen);
        auto foobarcontainer = CreateFooBarContainer(fbb, foobarvec, true,
                                                     Enum_Bananas, location);
        buf = &foobarcontainer;
        len = sizeof(foobarcontainer);
    }

    void *Decode(void *buf, size_t len) { return buf; }

    int64_t Use(void *decoded) {
        auto foobarcontainer = GetFooBarContainer(decoded);
        sum = 0;
        Add(foobarcontainer->initialized());
        Add(foobarcontainer->location()->size());
        Add(foobarcontainer->fruit());
        for (unsigned int i = 0; i < foobarcontainer->list()->size(); i++) {
            auto foobar = foobarcontainer->list()->Get(i);
            Add(foobar->name()->size());
            Add(foobar->postfix());
            Add(static_cast<int64_t>(foobar->rating()));
            auto bar = foobar->sibling();
            Add(static_cast<int64_t>(bar->ratio()));
            Add(bar->size());
            Add(bar->time());
            auto foo = bar->parent();
            Add(foo->count());
            Add(foo->id());
            Add(foo->length());
            Add(foo->prefix());
        }
        return sum;
    }

    void Dealloc(void *decoded) {}
};

Bench *NewFBBench() {
    return new FBBench();
}

class FBServer: public BenchServer {
    std::unique_ptr<Server> server;
public:
    FBServer() = default;

    // Logic and data behind the server's behavior.
    class FooBarServiceImpl final : public FooBarService::Service {
        Bench *instance = new FBBench();

        Status GetFooBarContainer(ServerContext *context,
                                  const flatbuffers::grpc::Message<ID>  *request,
                                  flatbuffers::grpc::Message<FooBarContainer> *reply) override {
            size_t len;
            instance->Encode(reply, len);
            return Status::OK;
        }
    };

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
        server = builder.BuildAndStart();
        std::cout << "Server listening on " << server_address << std::endl;

        // Wait for the server to shutdown. Note that some other thread must be
        // responsible for shutting down the server for this call to ever return.
        server->Wait();
    }

    void ShutdownServer(int signal) override {
        server->Shutdown();
        BenchServer::ShutdownServer(signal);
    }

};

#endif //BUFFER_BENCH_FBBENCH_H
