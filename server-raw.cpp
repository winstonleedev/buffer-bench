#include <iostream>
#include <assert.h>
#include "bench.h"
#include "config.h"
#include <chrono>
#include <zconf.h>
#include <zlib.h>
#include <thread>
#include <csignal>

using namespace std;

BenchServer *RAWBench;
std::thread RAWThread;

void stopServers(int s){
    printf("Caught signal %d\n",s);
    RAWBench->ShutdownServer();

    RAWThread.join();
    exit(1);
}

void runServers() {
    RAWBench = new RawServer();

    RAWThread(RAWBench->StartServer());
}

int main() {

    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = stopServers;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    runServers();

    return 0;
}

