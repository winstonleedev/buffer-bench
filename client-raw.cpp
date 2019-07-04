#include <iostream>
#include <assert.h>
#include "bench.h"
#include "config.h"
#include <chrono>
#include <zconf.h>
#include <zlib.h>

std::chrono::time_point<std::chrono::system_clock> endTime, start;

void InitTime() {
    start = std::chrono::system_clock::now();
}

double SecondsSinceStart() {
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = endTime - start;
    return diff.count();
}

size_t DeflateTest(void *buf, size_t len) {
    auto outbuf = malloc(len * 2);
    uLongf size;
    auto err = compress((Bytef *) outbuf, &size, (Bytef *) buf, (uLong) len);
    assert(err == Z_OK);
    free(outbuf);
    return size;
}

void Run(Bench *bench, const char *name) {
    bench->Init();

    printf("=================================\n");

    const size_t bufsize = BUFFER_SIZE;
    char buf[bufsize];
    size_t len = bufsize;
    const int iterations = ITERATIONS;
    void *decoded[iterations];

    printf("%s bench start...\n", name);
    uint64_t total = 0;
    double encode = 0, decode = 0, use = 0, dealloc = 0;

    // we use an outer loop also, since bumping up "iterations" to 10000 or so
    // puts so much strain on the allocator that use of free() dwarfs all
    // timings. Running the benchmark in batches gives more realistic timings and
    // keeps it accurate
    for (int j = 0; j < ITERATIONS_OUTER; j++) {

        InitTime();

        double time1 = SecondsSinceStart();
        for (int i = 0; i < iterations; i++) {
            len = bufsize;
            bench->Encode(buf, len);
        }
        double time2 = SecondsSinceStart();

        double time3 = SecondsSinceStart();
        for (auto &i : decoded) {
            i = bench->Decode(buf, len);
        }
        double time4 = SecondsSinceStart();

        double time5 = SecondsSinceStart();
        for (auto &i : decoded) {
            auto result = bench->Use(i);

            assert(result == 218812692406581874);
            total += result;
        }
        double time6 = SecondsSinceStart();
        for (auto &i : decoded) {
            bench->Dealloc(i);
        }
        double time7 = SecondsSinceStart();
        encode += time2 - time1;
        decode += time4 - time3;
        use += time6 - time5;
        dealloc += time7 - time6;
    }
    auto complen = DeflateTest(buf, len);
    // Ensure none of the code gets optimized out.
    printf("total = %lu\n", total);
    printf("%s bench: %lu wire size, %lu compressed wire size\n", name, len, complen);
    printf("* %f encode time, %f decode time\n", encode, decode);
    printf("* %f use time, %f dealloc time\n", use, dealloc);
    printf("* %f decode/use/dealloc\n", decode + use + dealloc);

    bench->ShutDown();
    delete bench;
}

void Run() {
    printf("=================================\n");

    const size_t bufsize = BUFFER_SIZE;
    char buf[bufsize];

    printf("%s bench start...\n", "RAW");
    uint64_t total = 0;
    double create = 0, receive = 0, use = 0, free = 0;

    std::string server_address(CLIENT_ACCESS_PROTO);

    // we use an outer loop also, since bumping up "iterations" to 10000 or so
    // puts so much strain on the allocator that use of free() dwarfs all
    // timings. Running the benchmark in batches gives more realistic timings and
    // keeps it accurate
    for (int j = 0; j < ITERATIONS_OUTER; j++) {
        InitTime();

        double time1 = SecondsSinceStart();
        id.set_id(42);

        double time2 = SecondsSinceStart();
        FooBarContainer message = client.GetFooBarContainer(id);

        double time3 = SecondsSinceStart();
        auto result = PBBench::Use(&message);
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

    // getchar();
    return 0;
}

