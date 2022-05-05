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

#include "frameworks/bridge/js_frontend/engine/jsi/debugger/ws_server.h"

#include <fstream>
#include <iostream>
#include <sys/types.h>

#include "base/log/log.h"
thread_local boost::asio::io_context g_ioContext;

namespace OHOS::Ace::Framework {

void DispatchMsgToSocket(int sign)
{
    g_ioContext.stop();
}

void WsServer::RunServer()
{
    terminateExecution_ = false;
    try {
        boost::asio::io_context ioContext;
        int appPid = getpid();
        tid_ = pthread_self();
        std::string pidStr = std::to_string(appPid);
        std::string instanceIdStr("");
        auto& connectFlag = connectState_;
        /**
         * The old version of IDE is not compatible with the new images due to the connect server.
         * The First instance will use "pid" instead of "pid + instanceId" to avoid this.
         * If old version of IDE does not get the instanceId by connect server, it can still connect the debug server.
         */
        if (instanceId_ != 0) {
            instanceIdStr = std::to_string(instanceId_);
        }
        std::string sockName = '\0' + pidStr + instanceIdStr + componentName_;
        LOGI("WsServer RunServer: %{public}d%{public}d%{public}s", appPid, instanceId_, componentName_.c_str());
        localSocket::endpoint endPoint(sockName);
        localSocket::socket socket(g_ioContext);
        localSocket::acceptor acceptor(g_ioContext, endPoint);
        acceptor.async_accept(socket, [&connectFlag](const boost::system::error_code& error) {
            if (!error) {
                connectFlag = true;
            }
        });
        if (signal(SIGURG, &DispatchMsgToSocket) == SIG_ERR) {
            LOGE("WsServer RunServer: Error exception");
            return;
        }
        g_ioContext.run();
        if (terminateExecution_ || !connectState_) {
            return;
        }
        webSocket_ = std::unique_ptr<websocket::stream<localSocket::socket>>(
            std::make_unique<websocket::stream<localSocket::socket>>(std::move(socket)));
        webSocket_->accept();
        while (!terminateExecution_) {
            beast::flat_buffer buffer;
            webSocket_->read(buffer);
            std::string message = boost::beast::buffers_to_string(buffer.data());
            LOGI("WsServer OnMessage: %{public}s", message.c_str());
            ideMsgQueue.push(std::move(message));
            wsOnMessage_();
        }
    } catch (const beast::system_error& se) {
        if (se.code() != websocket::error::closed) {
            LOGE("Error system_error");
        }
    } catch (const std::exception& e) {
        LOGE("Error exception, %{public}s", e.what());
    }
}

void WsServer::StopServer()
{
    LOGI("WsServer StopServer");
    terminateExecution_ = true;
    if (!connectState_) {
        pthread_kill(tid_, SIGURG);
    }
}

void WsServer::SendReply(const std::string& message) const
{
    LOGI("WsServer SendReply: %{public}s", message.c_str());
    try {
        boost::beast::multi_buffer buffer;
        boost::beast::ostream(buffer) << message;

        webSocket_->text(webSocket_->got_text());
        webSocket_->write(buffer.data());
    } catch (const beast::system_error& se) {
        if (se.code() != websocket::error::closed) {
            LOGE("SendReply Error system_error");
        }
    } catch (const std::exception& e) {
        LOGE("SendReply Error exception");
    }
}

} // namespace OHOS::Ace::Framework
