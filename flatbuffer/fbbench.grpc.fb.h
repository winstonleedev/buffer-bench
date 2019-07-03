// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: fbbench
#ifndef GRPC_fbbench__INCLUDED
#define GRPC_fbbench__INCLUDED

#include "fbbench_generated.h"
#include "flatbuffers/grpc.h"

#include <grpc++/impl/codegen/async_stream.h>
#include <grpc++/impl/codegen/async_unary_call.h>
#include <grpc++/impl/codegen/method_handler_impl.h>
#include <grpc++/impl/codegen/proto_utils.h>
#include <grpc++/impl/codegen/rpc_method.h>
#include <grpc++/impl/codegen/service_type.h>
#include <grpc++/impl/codegen/status.h>
#include <grpc++/impl/codegen/stub_options.h>
#include <grpc++/impl/codegen/sync_stream.h>

namespace benchfb {

class FooBarService final {
 public:
  static constexpr char const* service_full_name() {
    return "benchfb.FooBarService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status GetFoo(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, flatbuffers::grpc::Message<Foo>* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<Foo>>> AsyncGetFoo(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<Foo>>>(AsyncGetFooRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<Foo>>> PrepareAsyncGetFoo(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<Foo>>>(PrepareAsyncGetFooRaw(context, request, cq));
    }
    virtual ::grpc::Status GetBar(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, flatbuffers::grpc::Message<Bar>* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<Bar>>> AsyncGetBar(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<Bar>>>(AsyncGetBarRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<Bar>>> PrepareAsyncGetBar(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<Bar>>>(PrepareAsyncGetBarRaw(context, request, cq));
    }
    virtual ::grpc::Status GetFooBar(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, flatbuffers::grpc::Message<FooBar>* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<FooBar>>> AsyncGetFooBar(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<FooBar>>>(AsyncGetFooBarRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<FooBar>>> PrepareAsyncGetFooBar(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<FooBar>>>(PrepareAsyncGetFooBarRaw(context, request, cq));
    }
    virtual ::grpc::Status GetFooBarContainer(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, flatbuffers::grpc::Message<FooBarContainer>* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<FooBarContainer>>> AsyncGetFooBarContainer(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<FooBarContainer>>>(AsyncGetFooBarContainerRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<FooBarContainer>>> PrepareAsyncGetFooBarContainer(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<FooBarContainer>>>(PrepareAsyncGetFooBarContainerRaw(context, request, cq));
    }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<Foo>>* AsyncGetFooRaw(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<Foo>>* PrepareAsyncGetFooRaw(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<Bar>>* AsyncGetBarRaw(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<Bar>>* PrepareAsyncGetBarRaw(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<FooBar>>* AsyncGetFooBarRaw(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<FooBar>>* PrepareAsyncGetFooBarRaw(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<FooBarContainer>>* AsyncGetFooBarContainerRaw(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< flatbuffers::grpc::Message<FooBarContainer>>* PrepareAsyncGetFooBarContainerRaw(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status GetFoo(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, flatbuffers::grpc::Message<Foo>* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<Foo>>> AsyncGetFoo(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<Foo>>>(AsyncGetFooRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<Foo>>> PrepareAsyncGetFoo(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<Foo>>>(PrepareAsyncGetFooRaw(context, request, cq));
    }
    ::grpc::Status GetBar(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, flatbuffers::grpc::Message<Bar>* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<Bar>>> AsyncGetBar(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<Bar>>>(AsyncGetBarRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<Bar>>> PrepareAsyncGetBar(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<Bar>>>(PrepareAsyncGetBarRaw(context, request, cq));
    }
    ::grpc::Status GetFooBar(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, flatbuffers::grpc::Message<FooBar>* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<FooBar>>> AsyncGetFooBar(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<FooBar>>>(AsyncGetFooBarRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<FooBar>>> PrepareAsyncGetFooBar(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<FooBar>>>(PrepareAsyncGetFooBarRaw(context, request, cq));
    }
    ::grpc::Status GetFooBarContainer(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, flatbuffers::grpc::Message<FooBarContainer>* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<FooBarContainer>>> AsyncGetFooBarContainer(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<FooBarContainer>>>(AsyncGetFooBarContainerRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<FooBarContainer>>> PrepareAsyncGetFooBarContainer(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<FooBarContainer>>>(PrepareAsyncGetFooBarContainerRaw(context, request, cq));
    }
  
   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<Foo>>* AsyncGetFooRaw(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<Foo>>* PrepareAsyncGetFooRaw(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<Bar>>* AsyncGetBarRaw(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<Bar>>* PrepareAsyncGetBarRaw(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<FooBar>>* AsyncGetFooBarRaw(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<FooBar>>* PrepareAsyncGetFooBarRaw(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<FooBarContainer>>* AsyncGetFooBarContainerRaw(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< flatbuffers::grpc::Message<FooBarContainer>>* PrepareAsyncGetFooBarContainerRaw(::grpc::ClientContext* context, const flatbuffers::grpc::Message<ID>& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_GetFoo_;
    const ::grpc::internal::RpcMethod rpcmethod_GetBar_;
    const ::grpc::internal::RpcMethod rpcmethod_GetFooBar_;
    const ::grpc::internal::RpcMethod rpcmethod_GetFooBarContainer_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
  
  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status GetFoo(::grpc::ServerContext* context, const flatbuffers::grpc::Message<ID>* request, flatbuffers::grpc::Message<Foo>* response);
    virtual ::grpc::Status GetBar(::grpc::ServerContext* context, const flatbuffers::grpc::Message<ID>* request, flatbuffers::grpc::Message<Bar>* response);
    virtual ::grpc::Status GetFooBar(::grpc::ServerContext* context, const flatbuffers::grpc::Message<ID>* request, flatbuffers::grpc::Message<FooBar>* response);
    virtual ::grpc::Status GetFooBarContainer(::grpc::ServerContext* context, const flatbuffers::grpc::Message<ID>* request, flatbuffers::grpc::Message<FooBarContainer>* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_GetFoo : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_GetFoo() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_GetFoo() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetFoo(::grpc::ServerContext* context, const flatbuffers::grpc::Message<ID>* request, flatbuffers::grpc::Message<Foo>* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetFoo(::grpc::ServerContext* context, flatbuffers::grpc::Message<ID>* request, ::grpc::ServerAsyncResponseWriter< flatbuffers::grpc::Message<Foo>>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_GetBar : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_GetBar() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_GetBar() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetBar(::grpc::ServerContext* context, const flatbuffers::grpc::Message<ID>* request, flatbuffers::grpc::Message<Bar>* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetBar(::grpc::ServerContext* context, flatbuffers::grpc::Message<ID>* request, ::grpc::ServerAsyncResponseWriter< flatbuffers::grpc::Message<Bar>>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_GetFooBar : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_GetFooBar() {
      ::grpc::Service::MarkMethodAsync(2);
    }
    ~WithAsyncMethod_GetFooBar() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetFooBar(::grpc::ServerContext* context, const flatbuffers::grpc::Message<ID>* request, flatbuffers::grpc::Message<FooBar>* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetFooBar(::grpc::ServerContext* context, flatbuffers::grpc::Message<ID>* request, ::grpc::ServerAsyncResponseWriter< flatbuffers::grpc::Message<FooBar>>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_GetFooBarContainer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_GetFooBarContainer() {
      ::grpc::Service::MarkMethodAsync(3);
    }
    ~WithAsyncMethod_GetFooBarContainer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetFooBarContainer(::grpc::ServerContext* context, const flatbuffers::grpc::Message<ID>* request, flatbuffers::grpc::Message<FooBarContainer>* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetFooBarContainer(::grpc::ServerContext* context, flatbuffers::grpc::Message<ID>* request, ::grpc::ServerAsyncResponseWriter< flatbuffers::grpc::Message<FooBarContainer>>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(3, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef   WithAsyncMethod_GetFoo<  WithAsyncMethod_GetBar<  WithAsyncMethod_GetFooBar<  WithAsyncMethod_GetFooBarContainer<  Service   >   >   >   >   AsyncService;
  template <class BaseClass>
  class WithGenericMethod_GetFoo : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_GetFoo() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_GetFoo() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetFoo(::grpc::ServerContext* context, const flatbuffers::grpc::Message<ID>* request, flatbuffers::grpc::Message<Foo>* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_GetBar : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_GetBar() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_GetBar() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetBar(::grpc::ServerContext* context, const flatbuffers::grpc::Message<ID>* request, flatbuffers::grpc::Message<Bar>* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_GetFooBar : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_GetFooBar() {
      ::grpc::Service::MarkMethodGeneric(2);
    }
    ~WithGenericMethod_GetFooBar() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetFooBar(::grpc::ServerContext* context, const flatbuffers::grpc::Message<ID>* request, flatbuffers::grpc::Message<FooBar>* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_GetFooBarContainer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_GetFooBarContainer() {
      ::grpc::Service::MarkMethodGeneric(3);
    }
    ~WithGenericMethod_GetFooBarContainer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetFooBarContainer(::grpc::ServerContext* context, const flatbuffers::grpc::Message<ID>* request, flatbuffers::grpc::Message<FooBarContainer>* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_GetFoo : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_GetFoo() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler< flatbuffers::grpc::Message<ID>, flatbuffers::grpc::Message<Foo>>(std::bind(&WithStreamedUnaryMethod_GetFoo<BaseClass>::StreamedGetFoo, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_GetFoo() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status GetFoo(::grpc::ServerContext* context, const flatbuffers::grpc::Message<ID>* request, flatbuffers::grpc::Message<Foo>* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedGetFoo(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< flatbuffers::grpc::Message<ID>,flatbuffers::grpc::Message<Foo>>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_GetBar : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_GetBar() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler< flatbuffers::grpc::Message<ID>, flatbuffers::grpc::Message<Bar>>(std::bind(&WithStreamedUnaryMethod_GetBar<BaseClass>::StreamedGetBar, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_GetBar() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status GetBar(::grpc::ServerContext* context, const flatbuffers::grpc::Message<ID>* request, flatbuffers::grpc::Message<Bar>* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedGetBar(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< flatbuffers::grpc::Message<ID>,flatbuffers::grpc::Message<Bar>>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_GetFooBar : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_GetFooBar() {
      ::grpc::Service::MarkMethodStreamed(2,
        new ::grpc::internal::StreamedUnaryHandler< flatbuffers::grpc::Message<ID>, flatbuffers::grpc::Message<FooBar>>(std::bind(&WithStreamedUnaryMethod_GetFooBar<BaseClass>::StreamedGetFooBar, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_GetFooBar() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status GetFooBar(::grpc::ServerContext* context, const flatbuffers::grpc::Message<ID>* request, flatbuffers::grpc::Message<FooBar>* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedGetFooBar(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< flatbuffers::grpc::Message<ID>,flatbuffers::grpc::Message<FooBar>>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_GetFooBarContainer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_GetFooBarContainer() {
      ::grpc::Service::MarkMethodStreamed(3,
        new ::grpc::internal::StreamedUnaryHandler< flatbuffers::grpc::Message<ID>, flatbuffers::grpc::Message<FooBarContainer>>(std::bind(&WithStreamedUnaryMethod_GetFooBarContainer<BaseClass>::StreamedGetFooBarContainer, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_GetFooBarContainer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status GetFooBarContainer(::grpc::ServerContext* context, const flatbuffers::grpc::Message<ID>* request, flatbuffers::grpc::Message<FooBarContainer>* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedGetFooBarContainer(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< flatbuffers::grpc::Message<ID>,flatbuffers::grpc::Message<FooBarContainer>>* server_unary_streamer) = 0;
  };
  typedef   WithStreamedUnaryMethod_GetFoo<  WithStreamedUnaryMethod_GetBar<  WithStreamedUnaryMethod_GetFooBar<  WithStreamedUnaryMethod_GetFooBarContainer<  Service   >   >   >   >   StreamedUnaryService;
  typedef   Service   SplitStreamedService;
  typedef   WithStreamedUnaryMethod_GetFoo<  WithStreamedUnaryMethod_GetBar<  WithStreamedUnaryMethod_GetFooBar<  WithStreamedUnaryMethod_GetFooBarContainer<  Service   >   >   >   >   StreamedService;
};

}  // namespace benchfb


#endif  // GRPC_fbbench__INCLUDED