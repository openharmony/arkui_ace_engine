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

#include "frameworks/core/common/debugger/connect_inspector.h"

#include <shared_mutex>

#include "base/log/log.h"

namespace OHOS::Ace {
std::shared_mutex g_mutex;
std::unique_ptr<ConnectInspector> g_inspector = nullptr;

void* HandleDebugManager(void* const server)
{
    if (server == nullptr) {
        LOGE("HandleDebugManager server nullptr");
        return nullptr;
    }
    static_cast<ConnectServer*>(server)->RunServer();
    return nullptr;
}

void OnMessage(const std::string& message)
{
    std::shared_lock<std::shared_mutex> lock(g_mutex);
    if (message.empty()) {
        LOGE("message is empty");
        return;
    }

    LOGI("ConnectServer OnMessage: %{public}s", message.c_str());
    if (g_inspector != nullptr && g_inspector->connectServer_ != nullptr) {
        g_inspector->ideMsgQueue_.push(message);
        std::string checkMessage = "connected";
        std::string requestMessage = "tree";
        if (message.find(checkMessage, 0) != std::string::npos) {
            g_inspector->waitingForDebugger_ = false;
            g_inspector->setConnectedStaus_(g_inspector->instanceId_);
            for (auto& info : g_inspector->infoBuffer_) {
                g_inspector->connectServer_->SendMessage(info.second);
            }
        }
        if (message.find(requestMessage, 0) != std::string::npos) {
            g_inspector->connectServer_->SendMessage(g_inspector->layoutInspectorInfo_.tree);
            g_inspector->connectServer_->SendMessage(g_inspector->layoutInspectorInfo_.snapShot);
        }
    }
}

void SetCreatTreeCallBack(const std::function<void(int32_t)>& setConnectedStaus, int32_t instanceId)
{
    g_inspector->instanceId_ = instanceId;
    g_inspector->setConnectedStaus_ = setConnectedStaus;
}

void ResetService()
{
    if (g_inspector != nullptr && g_inspector->connectServer_ != nullptr) {
        g_inspector->connectServer_->StopServer();
        g_inspector->connectServer_.reset();
    }
}

void StartServer(const std::string& componentName)
{
    g_inspector = std::make_unique<ConnectInspector>();
    g_inspector->connectServer_ = std::make_unique<ConnectServer>(componentName,
        std::bind(&OnMessage, std::placeholders::_1));

    pthread_t tid;
    if (pthread_create(&tid, nullptr, &HandleDebugManager,
        static_cast<void*>(g_inspector->connectServer_.get())) != 0) {
        LOGE("pthread_create fail!");
        ResetService();
        return;
    }
}

void StopServer(const std::string& componentName)
{
    ResetService();
}

void StoreMessage(int32_t instanceId, const std::string& message)
{
    std::unique_lock<std::shared_mutex> lock(g_mutex);
    if (g_inspector->infoBuffer_.count(instanceId) == 1) {
        LOGE("The message with the current instance id has existed.");
        return;
    }
    g_inspector->infoBuffer_[instanceId] = message;
}

void StoreInspectorInfo(const std::string& jsonTreeStr, const std::string& jsonSnapshotStr)
{
    std::unique_lock<std::shared_mutex> lock(g_mutex);
    g_inspector->layoutInspectorInfo_.tree = jsonTreeStr;
    g_inspector->layoutInspectorInfo_.snapShot = jsonSnapshotStr;
}

void RemoveMessage(int32_t instanceId)
{
    std::unique_lock<std::shared_mutex> lock(g_mutex);
    if (g_inspector->infoBuffer_.count(instanceId) != 1) {
        LOGE("The message with the current instance id does not exist.");
        return;
    }
    g_inspector->infoBuffer_.erase(instanceId);
}

void SendMessage(const std::string& message)
{
    if (g_inspector != nullptr && g_inspector->connectServer_ != nullptr && !g_inspector->waitingForDebugger_) {
        g_inspector->connectServer_->SendMessage(message);
    }
}

bool WaitForDebugger()
{
    if (g_inspector == nullptr) {
        return true;
    }
    return g_inspector->waitingForDebugger_;
}

} // namespace OHOS::Ace
