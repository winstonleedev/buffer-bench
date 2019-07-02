#include <iostream>
#include <assert.h>
#include "bench.h"
#include "config.h"
#include "flatbuffer/fbbench.h"
#include <chrono>
#include <zconf.h>
#include <zlib.h>
#include <bits/sigaction.h>
#include <signal.h>

using namespace std;

int main() {

    struct sigaction sigIntHandler{};
    BenchServer *server = new FBServer();

    sigIntHandler.sa_handler = ;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, nullptr);

    server->StartServer();

    return 0;
}

