#include "fbbench.grpc.fb.h"
#include "fbbench_generated.h"

#include <grpc++/grpc++.h>

#include <iostream>
#include <memory>
#include <string>

using namespace benchfb;

class FooBarClient {
public:
    explicit FooBarClient(std::shared_ptr<grpc::Channel> channel)
            : stub_(FooBarService::NewStub(channel)) {}

    std::string SayHello(const std::string &name) {
        flatbuffers::grpc::MessageBuilder mb;
        auto name_offset = mb.CreateString(name);
        auto request_offset = CreateID(mb, 0);
        mb.Finish(request_offset);
        auto request_msg = mb.ReleaseMessage<ID>();

        flatbuffers::grpc::Message<FooBarContainer> response_msg;

        grpc::ClientContext context;

        auto status = stub_->GetFooBarContainer(&context, request_msg, &response_msg);
        if (status.ok()) {
            const FooBarContainer *response = response_msg.GetRoot();
            return response->location()->str();
        } else {
            std::cerr << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return "RPC failed";
        }
    }

private:
    std::unique_ptr<FooBarService::Stub> stub_;
};

int main(int argc, char **argv) {
    std::string server_address("localhost:50051");

    auto channel =
            grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
    FooBarClient greeter(channel);

    std::string name("world");

    std::string message = greeter.SayHello(name);
    std::cerr << "Greeter received: " << message << std::endl;


    return 0;
}
