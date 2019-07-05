#include <iostream>
#include <assert.h>
#include "bench.h"
#include <chrono>
#include <zconf.h>
#include <zlib.h>

std::chrono::time_point<std::chrono::system_clock> end, start;

void InitTime()
{
    start = std::chrono::system_clock::now();
}

double SecondsSinceStart()
{
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    return diff.count();
}

size_t DeflateTest(void *buf, size_t len) {
    auto outbuf = malloc(len * 2);
    uLongf size;
    auto err = compress((Bytef *)outbuf, &size, (Bytef *)buf, (uLong)len);
    assert(err == Z_OK);
    free(outbuf);
    return size;
}

void Run(Bench *bench, const char *name) {
    bench->Init();

    printf("=================================\n");

    const size_t bufsize = 10000;
    char buf[bufsize];
    size_t len = bufsize;
    const int iterations = 1000;
    void *decoded[iterations];

    printf("%s bench start...\n", name);
    uint64_t total = 0;
    double encode = 0, decode = 0, use = 0, dealloc = 0;

    // we use an outer loop also, since bumping up "iterations" to 10000 or so
    // puts so much strain on the allocator that use of free() dwarfs all
    // timings. Running the benchmark in batches gives more realistic timings and
    // keeps it accurate
    for (int j = 0; j < 1000; j++) {

        InitTime();

        double time1 = SecondsSinceStart();
        for (int i = 0; i < iterations; i++) {
            len = bufsize;
            bench->Encode(buf, len);
        }
        double time2 = SecondsSinceStart();
#ifdef _CRTDBG_MAP_ALLOC
        _CrtMemState ms1;
      _CrtMemCheckpoint(&ms1);
#endif
        double time3 = SecondsSinceStart();
        for (auto & i : decoded) {
            i = bench->Decode(buf, len);
        }
        double time4 = SecondsSinceStart();
#ifdef _CRTDBG_MAP_ALLOC
        _CrtMemState ms2;
      _CrtMemCheckpoint(&ms2);
      _CrtMemState msdiff;
      _CrtMemDifference(&msdiff, &ms1, &ms2);
      // This shows the amount of bytes & blocks needed for a decode,
      // also transient memory in totalcount
      if (!j) _CrtMemDumpStatistics(&msdiff);
#endif
        /*
        PROCESS_MEMORY_COUNTERS pmc = { sizeof(PROCESS_MEMORY_COUNTERS) };
        auto ok = GetProcessMemoryInfo(GetCurrentProcess(), &pmc,
                                       sizeof(PROCESS_MEMORY_COUNTERS));
        assert(ok);
        */
        double time5 = SecondsSinceStart();
        for (auto & i : decoded) {
            auto result = bench->Use(i);
            //printf("\n");
            assert(result == 218812692406581874);
            total += result;
        }
        double time6 = SecondsSinceStart();
        for (auto & i : decoded) {
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
    //printf("* %d K paged pool\n", pmc.PagefileUsage / 1024);

    bench->ShutDown();
    delete bench;
}

int main() {
    InitTime();

    std::cout << "Hello, World!" << std::endl;
    Bench *NewRAWBench();  Run(NewRAWBench(),  "Raw structs");
    Bench *NewFBBench();   Run(NewFBBench(),   "FlatBuffers");
    Bench *NewPBBench();   Run(NewPBBench(),   "Protocol Buffers LITE");

    // getchar();
    return 0;
}

