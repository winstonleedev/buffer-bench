#include <iostream>
#include <assert.h>
#include "bench.h"
#include "config.h"
#include <chrono>
#include <zconf.h>
#include <zlib.h>
#include "protobuf/benchpb.h"

#include <grpc++/grpc++.h>

std::chrono::time_point<std::chrono::system_clock> endTime, start;

void InitTime() {
    start = std::chrono::system_clock::now();
}

double SecondsSinceStart() {
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = endTime - start;
    return diff.count();
}

class FooBarClient {
public:
    explicit FooBarClient(std::shared_ptr<grpc::Channel> channel)
            : stub_(FooBarService::NewStub(channel)) {}

    // Assembles the client's payload, sends it and presents the response back
    // from the server.
    FooBarContainer GetFooBarContainer(ID request) {

        // Container for the data we expect from the server.
        FooBarContainer reply;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        grpc::ClientContext context;

        // The actual RPC.
        Status status = stub_->GetFooBarContainer(&context, request, &reply);

        // Act upon its status.
        if (status.ok()) {
            return reply;
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return FooBarContainer();
        }
    }

private:
    std::unique_ptr<FooBarService::Stub> stub_;
};

void Run() {

    printf("=================================\n");
    printf("%s bench start...\n", "PROTOBUF");
    uint64_t total = 0;
    double create = 0, receive = 0, use = 0, free = 0;

    std::string server_address(CLIENT_ACCESS_PROTO);

    auto channel =
            grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
    FooBarClient client(channel);

    std::string name("world");

    // we use an outer loop also, since bumping up "iterations" to 10000 or so
    // puts so much strain on the allocator that use of free() dwarfs all
    // timings. Running the benchmark in batches gives more realistic timings and
    // keeps it accurate
    for (int j = 0; j < ITERATIONS_OUTER; j++) {
        ID id;
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

