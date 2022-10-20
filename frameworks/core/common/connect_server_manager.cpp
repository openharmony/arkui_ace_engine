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

#include "core/common/connect_server_manager.h"

#include <dlfcn.h>
#include <unistd.h>

#include "base/json/json_util.h"
#include "base/log/log.h"
#include "core/common/ace_application_info.h"

namespace OHOS::Ace {

namespace {

using StartServer = bool (*)(const std::string& packageName);
using SendMessage = void (*)(const std::string& message);
using StopServer = void (*)(const std::string& packageName);
using StoreMessage = void (*)(int32_t instanceId, const std::string& message);
using RemoveMessage = void (*)(int32_t instanceId);
using WaitForDebugger = bool (*)();

SendMessage g_sendMessage = nullptr;
RemoveMessage g_removeMessage = nullptr;
StoreMessage g_storeMessage = nullptr;
} // namespace

ConnectServerManager::ConnectServerManager(): handlerConnectServerSo_(nullptr)
{
    isDebugVersion_ = AceApplicationInfo::GetInstance().IsDebugVersion();
    if (!isDebugVersion_) {
        return;
    }
    packageName_ = AceApplicationInfo::GetInstance().GetPackageName();
    InitConnectServer();
}

ConnectServerManager::~ConnectServerManager()
{
    if (!isDebugVersion_) {
        return;
    }
    StopConnectServer();
    CloseConnectServerSo();
}

ConnectServerManager& ConnectServerManager::Get()
{
    static ConnectServerManager connectServerManager;
    return connectServerManager;
}

bool ConnectServerManager::InitFunc()
{
    g_sendMessage = reinterpret_cast<SendMessage>(dlsym(handlerConnectServerSo_, "SendMessage"));
    g_storeMessage = reinterpret_cast<StoreMessage>(dlsym(handlerConnectServerSo_, "StoreMessage"));
    g_removeMessage = reinterpret_cast<RemoveMessage>(dlsym(handlerConnectServerSo_, "RemoveMessage"));
    if (g_sendMessage == nullptr || g_storeMessage == nullptr || g_removeMessage == nullptr) {
        CloseConnectServerSo();
        return false;
    }
    return true;
}

void ConnectServerManager::InitConnectServer()
{
    const std::string soDir = "libconnectserver_debugger.z.so";
    handlerConnectServerSo_ = dlopen(soDir.c_str(), RTLD_LAZY);
    if (handlerConnectServerSo_ == nullptr) {
        LOGE("Cannot find %{public}s", soDir.c_str());
        return;
    }
    StartServer startServer = reinterpret_cast<StartServer>(dlsym(handlerConnectServerSo_, "StartServer"));
    if (startServer == nullptr || !InitFunc()) {
        LOGE("startServer = NULL, dlerror = %s", dlerror());
        return;
    }
    startServer(packageName_);
}

void ConnectServerManager::CloseConnectServerSo()
{
    if (handlerConnectServerSo_ == nullptr) {
        return;
    }
    dlclose(handlerConnectServerSo_);
    handlerConnectServerSo_ = nullptr;
}

// When use multi-instances project, debug mode should be set to support debug
void ConnectServerManager::SetDebugMode()
{
    if (!isDebugVersion_ || handlerConnectServerSo_ == nullptr) {
        return;
    }
    WaitForDebugger waitForDebugger = reinterpret_cast<WaitForDebugger>(
        dlsym(handlerConnectServerSo_, "WaitForDebugger"));
    if (waitForDebugger == nullptr) {
        return;
    }
    if (!waitForDebugger()) { // waitForDebugger : waitForDebugger means the connection state of the connect server
        isDebugMode_ = true;
        AceApplicationInfo::GetInstance().SetNeedDebugBreakPoint(true);
    }
}

void ConnectServerManager::StopConnectServer()
{
    LOGD("Stop connect server");
    if (handlerConnectServerSo_ == nullptr) {
        LOGE("handlerConnectServerSo_ is null");
        return;
    }
    StopServer stopServer = reinterpret_cast<StopServer>(dlsym(handlerConnectServerSo_, "StopServer"));
    if (stopServer == nullptr) {
        LOGE("stopServer = NULL, dlerror = %s", dlerror());
        return;
    }
    stopServer(packageName_);
}

void ConnectServerManager::AddInstance(int32_t instanceId, const std::string& instanceName)
{
    if (!isDebugVersion_ || handlerConnectServerSo_ == nullptr) {
        return;
    }
    LOGD("AddInstance %{public}d", instanceId);
    {
        std::lock_guard<std::mutex> lock(mutex_);
        const auto result = instanceMap_.try_emplace(instanceId, instanceName);
        if (!result.second) {
            LOGD("Already have instance name of this instance id: %{public}d", instanceId);
            return;
        }
    }
    // Get the message including information of new instance, which will be send to IDE.
    std::string message = GetInstanceMapMessage("addInstance", instanceId);

    if (isDebugMode_) { // isDebugMode_ : isDebugMode_ means the connection state of the connect server
        g_sendMessage(message); // if connected, message will be sent immediately.
    } else { // if not connected, message will be stored and sent later when "connected" coming.
        g_storeMessage(instanceId, message);
    }
}

void ConnectServerManager::RemoveInstance(int32_t instanceId)
{
    if (!isDebugVersion_ || handlerConnectServerSo_ == nullptr) {
        return;
    }
    LOGD("RemoveInstance %{public}d", instanceId);

    // Get the message including information of deleted instance, which will be send to IDE.
    std::string message = GetInstanceMapMessage("destroyInstance", instanceId);
    size_t numInstance = 0;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        numInstance = instanceMap_.erase(instanceId);
    }
    if (numInstance == 0) {
        LOGW("Instance name not found with instance id: %{public}d", instanceId);
    }

    if (isDebugMode_) {
        g_sendMessage(message);
    } else {
        g_removeMessage(instanceId);
    }
}

std::string ConnectServerManager::GetInstanceMapMessage(const char* messageType, int32_t instanceId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto message = JsonUtil::Create(true);
    message->Put("type", messageType);
    message->Put("instanceId", instanceId);
    message->Put("name", instanceMap_[instanceId].c_str());
    message->Put("tid", gettid());
    return message->ToString();
}

} // namespace OHOS::Ace