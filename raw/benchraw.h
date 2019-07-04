
// Compare against the fastest possible serialization: just write out naked
// structs. This is of course very apples to oranges, since this would be
// quite unusable as is in real world code, but good as a performance baseline.

// We have to hardcode everything, including the string length.
// 32 wastes a bit of memory but is overal a fair comparison.
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <assert.h>
#include <evpp/buffer.h>
#include "../bench.h"
#include "../config.h"

#define STRING_LENGTH 32
#define VEC_LENGTH 3

enum Enum { Apples, Pears, Bananas };

struct ID {
    int64_t id;
};

struct Foo {
    int64_t id;
    short count;
    char prefix;
    int length;
};

struct Bar {
    Foo parent;
    int time;
    float ratio;
    unsigned short size;
};

struct FooBar {
    Bar sibling;
    // We have to stick this in, otherwise strlen() will make it slower than
    // FlatBuffers:
    int name_len;
    char name[STRING_LENGTH];
    double rating;
    unsigned char postfix;
};

struct FooBarContainer {
    FooBar list[VEC_LENGTH];  // 3 copies of the above
    bool initialized;
    Enum fruit;
    int location_len;
    char location[STRING_LENGTH];
};

using namespace std;

struct RAWBench {
    evpp::Buffer* Encode() {
        FooBarContainer fbc{};
        strcpy(fbc.location, "http://google.com/flatbuffers/");  // Unsafe eek!
        fbc.location_len = (int)strlen(fbc.location);
        fbc.fruit = Bananas;
        fbc.initialized = true;
        for (int i = 0; i < VEC_LENGTH; i++) {
            // We add + i to not make these identical copies for a more realistic
            // compression test.
            auto &foobar = fbc.list[i];
            foobar.rating = 3.1415432432445543543 + i;
            foobar.postfix = '!' + i;
            strcpy(foobar.name, "Hello, World!");
            foobar.name_len = (int)strlen(foobar.name);
            auto &bar = foobar.sibling;
            bar.ratio = 3.14159f + i;
            bar.size = 10000 + i;
            bar.time = 123456 + i;
            auto &foo = bar.parent;
            foo.id = 0xABADCAFEABADCAFE + i;
            foo.count = 10000 + i;
            foo.length = 1000000 + i;
            foo.prefix = '@' + i;
        }
        auto len = sizeof(FooBarContainer);
        auto * result = new evpp::Buffer();
        result->Append(&fbc, len);
        return result;
    }

    static int64_t Use(evpp::Buffer *decoded) {
        auto foobarcontainer = (FooBarContainer *)decoded->NextAll().data();
        auto sum = 0;
        sum += (foobarcontainer->initialized);
        sum += (foobarcontainer->location_len);
        sum += (foobarcontainer->fruit);
        for (unsigned int i = 0; i < VEC_LENGTH; i++) {
            auto foobar = &foobarcontainer->list[i];
            sum += (foobar->name_len);
            sum += (foobar->postfix);
            sum += (static_cast<int64_t>(foobar->rating));
            auto bar = &foobar->sibling;
            sum += (static_cast<int64_t>(bar->ratio));
            sum += (bar->size);
            sum += (bar->time);
            auto &foo = bar->parent;
            sum += (foo.count);
            sum += (foo.id);
            sum += (foo.length);
            sum += (foo.prefix);
        }
        return sum;
    }

    void Dealloc(void *decoded) {}
};

RAWBench *NewRAWBench() { return new RAWBench(); }
