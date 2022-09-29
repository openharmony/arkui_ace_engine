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

#include "frameworks/core/common/debugger/connect_server.h"
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <thread>
#include "base/log/log.h"

namespace OHOS::Ace {

void ConnectServer::RunServer()
{
    terminateExecution_ = false;

    try {
        boost::asio::io_context ioContext;
        int appPid = getpid();
        std::string pidStr = std::to_string(appPid);
        std::string sockName = '\0' + pidStr + bundleName_;
        if (sockName.size() > 102) { // 102 : the longest len that boost socket can support
            sockName = sockName.substr(0, 102);
        }
        localSocket::endpoint endPoint(sockName);
        localSocket::socket socket(ioContext);
        localSocket::acceptor acceptor(ioContext, endPoint);
        acceptor.accept(socket);
        webSocket_ = std::unique_ptr<websocket::stream<localSocket::socket>>(
            std::make_unique<websocket::stream<localSocket::socket>>(std::move(socket)));
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
            wsOnMessage_(std::move(message));
            usleep(DEBUGGER_WAIT_SEND_SIGNAL_TIME);
        }
    } catch (const beast::system_error& se) {
        if (se.code() != websocket::error::closed) {
            LOGE("Error system_error");
        }
    } catch (const std::exception& e) {
        LOGE("Error exception, %{private}s", e.what());
    }
}

void ConnectServer::StopServer()
{
    terminateExecution_ = true;
}

void ConnectServer::SendMessage(const std::string& message) const
{
    try {
        if (webSocket_ == nullptr) {
            LOGE("Error Excpetion: SendMessage Failed");
            return;
        }
        LOGI("ConnectServer SendMessage: %{public}s", message.c_str());
        boost::beast::multi_buffer buffer;
        boost::beast::ostream(buffer) << message;

        webSocket_->text(webSocket_->got_text());
        webSocket_->write(buffer.data());
    } catch (beast::system_error const& se) {
        if (se.code() != websocket::error::closed) {
            LOGE("Error system_error");
        }
    } catch (std::exception const& e) {
        LOGE("Error exception");
    }
}

} // namespace OHOS::Ace
