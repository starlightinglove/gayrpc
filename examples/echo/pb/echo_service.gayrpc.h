// Generated by github.com/IronsDu/protoc-gen-gayrpc
// Coding by github.com/liuhan907
// DO NOT EDIT!!!

#ifndef DODO_TEST_ECHO_SERVICE_H
#define DODO_TEST_ECHO_SERVICE_H

#include <string>
#include <unordered_map>
#include <memory>
#include <cstdint>
#include <future>
#include <chrono>

#include <google/protobuf/util/json_util.h>

#include "meta.pb.h"
#include "echo_service.pb.h"

#include "GayRpcCore.h"
#include "GayRpcError.h"
#include "GayRpcTypeHandler.h"
#include "GayRpcClient.h"
#include "GayRpcService.h"
#include "GayRpcReply.h"

namespace dodo {
namespace test {

    using namespace gayrpc::core;
    using namespace google::protobuf::util;
    
    enum class echo_service_ServiceID:uint32_t
    {
        EchoServer,
        
    };

    
    enum class EchoServerMsgID:uint64_t
    {
        Echo = 2333,
        Login = 3333,
        
    };

    class EchoServerClient : public BaseClient
    {
    public:
        using PTR = std::shared_ptr<EchoServerClient>;
        using WeakPtr = std::weak_ptr<EchoServerClient>;

        using EchoHandle = std::function<void(const dodo::test::EchoResponse&, const gayrpc::core::RpcError&)>;
        using LoginHandle = std::function<void(const dodo::test::LoginResponse&, const gayrpc::core::RpcError&)>;
        

    public:
        void Echo(const dodo::test::EchoRequest& request,
            const EchoHandle& handle = nullptr)
        {
            call<dodo::test::EchoResponse>(request, 
                static_cast<uint32_t>(echo_service_ServiceID::EchoServer), 
                static_cast<uint64_t>(EchoServerMsgID::Echo), 
                handle);
        }
        void Login(const dodo::test::LoginRequest& request,
            const LoginHandle& handle = nullptr)
        {
            call<dodo::test::LoginResponse>(request, 
                static_cast<uint32_t>(echo_service_ServiceID::EchoServer), 
                static_cast<uint64_t>(EchoServerMsgID::Login), 
                handle);
        }
        
        void Echo(const dodo::test::EchoRequest& request,
            const EchoHandle& handle,
            std::chrono::seconds timeout, 
            BaseClient::TIMEOUT_CALLBACK timeoutCallback)
        {
            call<dodo::test::EchoResponse>(request, 
                static_cast<uint32_t>(echo_service_ServiceID::EchoServer), 
                static_cast<uint64_t>(EchoServerMsgID::Echo), 
                handle,
                timeout,
                std::move(timeoutCallback));
        }
        void Login(const dodo::test::LoginRequest& request,
            const LoginHandle& handle,
            std::chrono::seconds timeout, 
            BaseClient::TIMEOUT_CALLBACK timeoutCallback)
        {
            call<dodo::test::LoginResponse>(request, 
                static_cast<uint32_t>(echo_service_ServiceID::EchoServer), 
                static_cast<uint64_t>(EchoServerMsgID::Login), 
                handle,
                timeout,
                std::move(timeoutCallback));
        }
        

        dodo::test::EchoResponse SyncEcho(
            const dodo::test::EchoRequest& request,
            gayrpc::core::RpcError& error)
        {
            auto errorPromise = std::make_shared<std::promise<gayrpc::core::RpcError>>();
            auto responsePromise = std::make_shared<std::promise<dodo::test::EchoResponse>>();

            Echo(request, [responsePromise, errorPromise](const dodo::test::EchoResponse& response,
                const gayrpc::core::RpcError& error) {
                errorPromise->set_value(error);
                responsePromise->set_value(response);
            });

            error = errorPromise->get_future().get();
            return responsePromise->get_future().get();
        }
        dodo::test::LoginResponse SyncLogin(
            const dodo::test::LoginRequest& request,
            gayrpc::core::RpcError& error)
        {
            auto errorPromise = std::make_shared<std::promise<gayrpc::core::RpcError>>();
            auto responsePromise = std::make_shared<std::promise<dodo::test::LoginResponse>>();

            Login(request, [responsePromise, errorPromise](const dodo::test::LoginResponse& response,
                const gayrpc::core::RpcError& error) {
                errorPromise->set_value(error);
                responsePromise->set_value(response);
            });

            error = errorPromise->get_future().get();
            return responsePromise->get_future().get();
        }
        

    public:
        static PTR Create(const RpcTypeHandleManager::PTR& rpcHandlerManager,
            const UnaryServerInterceptor& inboundInterceptor,
            const UnaryServerInterceptor& outboundInterceptor)
        {
            struct make_shared_enabler : public EchoServerClient
            {
            public:
                make_shared_enabler(const RpcTypeHandleManager::PTR& rpcHandlerManager,
                    const UnaryServerInterceptor& inboundInterceptor,
                    const UnaryServerInterceptor& outboundInterceptor)
                    : 
                    EchoServerClient(rpcHandlerManager, inboundInterceptor, outboundInterceptor) {}
            };

            auto client = PTR(new make_shared_enabler(rpcHandlerManager, inboundInterceptor, outboundInterceptor));
            client->installResponseStub(rpcHandlerManager, static_cast<uint32_t>(echo_service_ServiceID::EchoServer));

            return client;
        }

    private:
        using BaseClient::BaseClient;
    };

    class EchoServerService : public BaseService
    {
    public:
        using PTR = std::shared_ptr<EchoServerService>;
        using WeakPtr = std::weak_ptr<EchoServerService>;

        using EchoReply = TemplateReply<dodo::test::EchoResponse>;
        using LoginReply = TemplateReply<dodo::test::LoginResponse>;
        

        using BaseService::BaseService;

        virtual ~EchoServerService()
        {
        }

        virtual void onClose() {}

        static inline bool Install(const EchoServerService::PTR& service);
    private:
        virtual void Echo(const dodo::test::EchoRequest& request, 
            const EchoReply::PTR& replyObj) = 0;
        virtual void Login(const dodo::test::LoginRequest& request, 
            const LoginReply::PTR& replyObj) = 0;
        

    private:

        static void Echo_stub(const RpcMeta& meta,
            const std::string& data,
            const EchoServerService::PTR& service,
            const UnaryServerInterceptor& inboundInterceptor,
            const UnaryServerInterceptor& outboundInterceptor)
        {
            dodo::test::EchoRequest request;
            parseRequestWrapper(request, meta, data, inboundInterceptor, [service,
                outboundInterceptor,
                &request](const RpcMeta& meta, const google::protobuf::Message& message) {
                auto replyObject = std::make_shared<EchoReply>(meta, outboundInterceptor);
                service->Echo(request, replyObject);
            });
        }
        static void Login_stub(const RpcMeta& meta,
            const std::string& data,
            const EchoServerService::PTR& service,
            const UnaryServerInterceptor& inboundInterceptor,
            const UnaryServerInterceptor& outboundInterceptor)
        {
            dodo::test::LoginRequest request;
            parseRequestWrapper(request, meta, data, inboundInterceptor, [service,
                outboundInterceptor,
                &request](const RpcMeta& meta, const google::protobuf::Message& message) {
                auto replyObject = std::make_shared<LoginReply>(meta, outboundInterceptor);
                service->Login(request, replyObject);
            });
        }
        
    };

    inline bool EchoServerService::Install(const EchoServerService::PTR& service)
    {
        auto rpcTypeHandleManager = service->getServiceContext().getTypeHandleManager();
        auto inboundInterceptor = service->getServiceContext().getInInterceptor();
        auto outboundInterceptor = service->getServiceContext().getOutInterceptor();

        using EchoServerServiceRequestHandler = std::function<void(const RpcMeta&,
            const std::string& data,
            const EchoServerService::PTR&,
            const UnaryServerInterceptor&,
            const UnaryServerInterceptor&)>;

        using EchoServerServiceHandlerMapById = std::unordered_map<uint64_t, EchoServerServiceRequestHandler>;
        using EchoServerServiceHandlerMapByStr = std::unordered_map<std::string, EchoServerServiceRequestHandler>;

        // TODO::static unordered map
        auto serviceHandlerMapById = std::make_shared<EchoServerServiceHandlerMapById>();
        auto serviceHandlerMapByStr = std::make_shared<EchoServerServiceHandlerMapByStr>();

        const std::string namespaceStr = "dodo.test.";

        (*serviceHandlerMapById)[static_cast<uint64_t>(EchoServerMsgID::Echo)] = EchoServerService::Echo_stub;
        (*serviceHandlerMapById)[static_cast<uint64_t>(EchoServerMsgID::Login)] = EchoServerService::Login_stub;
        
        (*serviceHandlerMapByStr)[namespaceStr+"EchoServer.Echo"] = EchoServerService::Echo_stub;
        (*serviceHandlerMapByStr)[namespaceStr+"EchoServer.Login"] = EchoServerService::Login_stub;
        

        auto requestStub = [service,
            serviceHandlerMapById,
            serviceHandlerMapByStr,
            inboundInterceptor,
            outboundInterceptor](const RpcMeta& meta, const std::string& data) {
            
            if (meta.type() != RpcMeta::REQUEST)
            {
                throw std::runtime_error("meta type not request, It is:" + std::to_string(meta.type()));
            }
            
            EchoServerServiceRequestHandler handler;

            if (!meta.request_info().strmethod().empty())
            {
                auto it = serviceHandlerMapByStr->find(meta.request_info().strmethod());
                if (it == serviceHandlerMapByStr->end())
                {
                    throw std::runtime_error("not found handle, method:" + meta.request_info().strmethod());
                }
                handler = (*it).second;
            }
            else
            {
                auto it = serviceHandlerMapById->find(meta.request_info().intmethod());
                if (it == serviceHandlerMapById->end())
                {
                    throw std::runtime_error("not found handle, method:" + meta.request_info().intmethod());
                }
                handler = (*it).second;
            }

            handler(meta,
                data,
                service,
                inboundInterceptor,
                outboundInterceptor);
        };

        return rpcTypeHandleManager->registerTypeHandle(RpcMeta::REQUEST, requestStub, static_cast<uint32_t>(echo_service_ServiceID::EchoServer));
    }
    
}
}

#endif

