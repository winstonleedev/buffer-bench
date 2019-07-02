#include <iostream>
#include <assert.h>
#include "bench.h"
#include "config.h"
#include <chrono>
#include <zconf.h>
#include <zlib.h>

BenchServer *PBBench;
std::thread PBThread;

void stopServers(int s){
    printf("Caught signal %d\n",s);
    PBBench->ShutdownServer();

    PBThread.join();
    exit(1);
}

void runServers() {
    PBBench = new PBServer();

    PBThread(PBBench->StartServer())
}

int main() {

    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    runServers();

    return 0;
}

