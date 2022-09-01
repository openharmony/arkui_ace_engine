/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_ARK_DEBUGGER_WS_SERVER_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_ARK_DEBUGGER_WS_SERVER_H

#include <boost/asio/error.hpp>
#if defined(PREVIEW)
#include <boost/asio/ip/tcp.hpp>
#else
#include <boost/asio/local/stream_protocol.hpp>
#endif
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <functional>
#include <iostream>
#include <queue>

#include <pthread.h>

namespace OHOS::Ace::Framework {

namespace beast = boost::beast;
namespace websocket = beast::websocket;
#if defined(PREVIEW)
using CommProtocol = boost::asio::ip::tcp;
#else
using CommProtocol = boost::asio::local::stream_protocol;
#endif

class WsServer {
public:
    WsServer(const std::string& component, const std::function<void(std::string&&)>& onMessage, int32_t instanceId)
        : instanceId_(instanceId), componentName_(component), wsOnMessage_(onMessage)
    {}
    ~WsServer() = default;
    void RunServer();
    void StopServer();
    void SendReply(const std::string& message) const;

private:
    std::atomic<bool> connectState_ {false};
    std::atomic<bool> terminateExecution_ { false };
    [[maybe_unused]] int32_t instanceId_ {0};
    pthread_t tid_ {0};
    std::string componentName_ {};
    std::function<void(std::string&&)> wsOnMessage_ {};
    std::unique_ptr<websocket::stream<CommProtocol::socket>> webSocket_ { nullptr };
    std::unique_ptr<boost::asio::io_context> ioContext_ { nullptr };
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_ARK_DEBUGGER_WS_SERVER_H
