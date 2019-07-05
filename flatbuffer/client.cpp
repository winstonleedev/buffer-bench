#include "fbbench.grpc.fb.h"
#include "fbbench_generated.h"

#include <grpc++/grpc++.h>
#include "../config.h"
#include "fbbench.h"

#include <iostream>
#include <memory>
#include <string>
#include <chrono>

using namespace benchfb;

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

    std::unique_ptr<FooBarService::Stub> stub_;
};


void Run() {

    printf("=================================\n");

    const size_t bufsize = BUFFER_SIZE;
    char buf[bufsize];

    printf("%s bench start...\n", "FLATBUF");
    uint64_t total = 0;
    double create = 0, receive = 0, use = 0, free = 0;

    std::string server_address(CLIENT_ACCESS_FBS);

    auto channel =
            grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
    FooBarClient client(channel);

    // we use an outer loop also, since bumping up "iterations" to 10000 or so
    // puts so much strain on the allocator that use of free() dwarfs all
    // timings. Running the benchmark in batches gives more realistic timings and
    // keeps it accurate
    for (int j = 0; j < ITERATIONS_OUTER; j++) {
        flatbuffers::grpc::MessageBuilder mb;
        grpc::ClientContext context;
        InitTime();

        double time1 = SecondsSinceStart();
        auto request_offset = CreateID(mb, 42);
        mb.Finish(request_offset);
        flatbuffers::grpc::Message<ID> id = mb.ReleaseMessage<ID>();

        double time2 = SecondsSinceStart();
        const FooBarContainer *response;
        flatbuffers::grpc::Message<FooBarContainer> message;
        auto status = client.stub_->GetFooBarContainer(&context, id, &message);
        assert(status.ok());
        response = message.GetRoot();

        double time3 = SecondsSinceStart();
        auto result = FBBench::Use(response);
        // TODO find out why this is wrong
        // assert(result == 218812692406581874);

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

int main(int argc, char **argv) {
    InitTime();
    Run();
    return 0;
}
