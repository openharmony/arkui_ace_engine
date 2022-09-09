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

#include "ws_server.h"

#include <fstream>
#include <iostream>
#include <sys/types.h>

#include "hilog_wrapper.h"

namespace OHOS::Ace::Framework {

void WsServer::RunServer()
{
    terminateExecution_ = false;
    try {
        tid_ = pthread_self();
#if defined(PREVIEW)
        constexpr int32_t DEFAULT_INSEPTOR_PORT = 9230;
        CommProtocol::endpoint endPoint(CommProtocol::v4(), DEFAULT_INSEPTOR_PORT);
#else
        int appPid = getpid();
        std::string pidStr = std::to_string(appPid);
        std::string instanceIdStr("");
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
        CommProtocol::endpoint endPoint(sockName);
#endif
        ioContext_ = std::make_unique<boost::asio::io_context>();
        CommProtocol::socket socket(*ioContext_);
        CommProtocol::acceptor acceptor(*ioContext_, endPoint);
        auto& connectFlag = connectState_;
        acceptor.async_accept(socket, [&connectFlag](const boost::system::error_code& error) {
            if (!error) {
                connectFlag = true;
            }
        });
        ioContext_->run();
        if (terminateExecution_ || !connectState_) {
            return;
        }
        webSocket_ = std::unique_ptr<websocket::stream<CommProtocol::socket>>(
            std::make_unique<websocket::stream<CommProtocol::socket>>(std::move(socket)));
        webSocket_->accept();
        while (!terminateExecution_) {
            beast::flat_buffer buffer;
            boost::system::error_code error;
            webSocket_->read(buffer, error);
            if (error) {
                webSocket_.reset();
                return;
            }
            std::string message = boost::beast::buffers_to_string(buffer.data());
            LOGI("WsServer OnMessage: %{public}s", message.c_str());
            wsOnMessage_(std::move(message));
        }
    } catch (const beast::system_error& se) {
        if (se.code() != websocket::error::closed) {
            webSocket_.reset();
            LOGE("Error system_error, %{public}s", se.what());
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
        ioContext_->stop();
    } else if (webSocket_ != nullptr) {
        boost::system::error_code error;
        webSocket_->close(websocket::close_code::normal, error);
    }
    pthread_join(tid_, nullptr);
}

void WsServer::SendReply(const std::string& message) const
{
    if (webSocket_ == nullptr) {
        LOGE("WsServer SendReply websocket has been closed unexpectedly");
        return;
    }
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
