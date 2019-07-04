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

struct FBBench {
    int64_t sum;

    virtual ~FBBench() {}

    void Add(int64_t x) {
        sum += x;
    }

    flatbuffers::Offset<FooBarContainer> Encode(flatbuffers::FlatBufferBuilder &fbb) {
        const int veclen = 3;
        flatbuffers::Offset<FooBar> vec[veclen];

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
        return foobarcontainer;
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

// Logic and data behind the server's behavior.
class FooBarServiceImpl final : public FooBarService::Service {
    flatbuffers::grpc::MessageBuilder mb_;
    FBBench *instance = new FBBench();

    Status GetFooBarContainer(ServerContext *context,
                              const flatbuffers::grpc::Message<ID>  *request,
                              flatbuffers::grpc::Message<FooBarContainer> *reply) override {
        size_t len;
        flatbuffers::Offset<FooBarContainer> createdMessage = instance->Encode(mb_);
        mb_.Finish(createdMessage);
        *reply = mb_.ReleaseMessage<FooBarContainer>();
        assert(reply->Verify());
        return Status::OK;
    }
};

#endif //BUFFER_BENCH_FBBENCH_H
