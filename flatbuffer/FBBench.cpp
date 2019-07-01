//
// Created by Thanh Phu on 6/27/2019.
//

#include "bench_generated.h"
#include "../bench.h"

using namespace flatbuffers;
using namespace benchfb;

struct FBBench : Bench {
    void Encode(void *buf, size_t &len) {
        const int veclen = 3;
        Offset<FooBar> vec[veclen];
        FlatBufferBuilder fbb;
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
        fbb.Finish(foobarcontainer);
        assert(len >= fbb.GetSize());
        len = fbb.GetSize();
        memcpy(buf, fbb.GetBufferPointer(), len);
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

Bench *NewFBBench() { return new FBBench(); }
