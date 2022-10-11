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
#include <string>
#include <unistd.h>

#include "base/json/json_util.h"
#include "base/log/log.h"
#include "core/common/ace_application_info.h"
#include "core/common/ace_engine.h"
#include "core/common/ace_page.h"
#include "core/common/container.h"
#include "core/event/ace_event_handler.h"


namespace OHOS::Ace {

namespace {

using StartServer = bool (*)(const std::string& packageName);
using SendMessage = void (*)(const std::string& message);
using StopServer = void (*)(const std::string& packageName);
using StoreMessage = void (*)(int32_t instanceId, const std::string& message);
using StoreInspectorInfo = void (*)(const std::string& jsonTreeStr, const std::string& jsonSnapshotStr);
using RemoveMessage = void (*)(int32_t instanceId);
using WaitForDebugger = bool (*)();
using SetCreatTreeCallBack = void (*)(const std::function<void(int32_t)>& setConnectedStaus, int32_t instanceId);

void SetCallbackFunc(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        LOGE("Container is null");
        return;
    }
    container->SetIdeDebuggerConnected(true);
}

} // namespace

ConnectServerManager::ConnectServerManager(): handlerConnectServerSo_(nullptr)
{
    isDebugVersion_ = AceApplicationInfo::GetInstance().IsDebugVersion();
    if (!isDebugVersion_) {
        return;
    }
    packageName_ = AceApplicationInfo::GetInstance().GetPackageName();
    LoadConnectServerSo();
    StartConnectServer();
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

void ConnectServerManager::LoadConnectServerSo()
{
    const std::string soDir = "libconnectserver_debugger.z.so";
    handlerConnectServerSo_ = dlopen(soDir.c_str(), RTLD_LAZY);
    if (handlerConnectServerSo_ == nullptr) {
        LOGE("Cannot find %{public}s", soDir.c_str());
    }
}

void ConnectServerManager::CloseConnectServerSo()
{
    if (handlerConnectServerSo_ == nullptr) {
        return;
    }
    dlclose(handlerConnectServerSo_);
    handlerConnectServerSo_ = nullptr;
}

void ConnectServerManager::StartConnectServer()
{
    LOGI("Start connect server");
    if (handlerConnectServerSo_ == nullptr) {
        LOGE("handlerConnectServerSo_ is null");
        return;
    }
    StartServer startServer = (StartServer)dlsym(handlerConnectServerSo_, "StartServer");
    if (startServer == nullptr) {
        LOGE("startServer = NULL, dlerror = %s", dlerror());
        return;
    }
    startServer(packageName_);
}

void ConnectServerManager::StopConnectServer()
{
    LOGI("Stop connect server");
    if (handlerConnectServerSo_ == nullptr) {
        LOGE("handlerConnectServerSo_ is null");
        return;
    }
    StopServer stopServer = (StopServer)dlsym(handlerConnectServerSo_, "StopServer");
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
    LOGI("AddInstance %{public}d", instanceId);
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

    WaitForDebugger waitForDebugger = (WaitForDebugger)dlsym(handlerConnectServerSo_, "WaitForDebugger");
    if (waitForDebugger == nullptr) {
        return;
    }
    if (!waitForDebugger()) { // waitForDebugger : waitForDebugger means the connection state of the connect server
        AceApplicationInfo::GetInstance().SetNeedDebugBreakPoint(true);
        SendMessage sendMessage = (SendMessage)dlsym(handlerConnectServerSo_, "SendMessage");
        if (sendMessage != nullptr) {
            sendMessage(message); // if connected, message will be sent immediately.
        }
    } else { // if not connected, message will be stored and sent later when "connected" coming.
        StoreMessage storeMessage = (StoreMessage)dlsym(handlerConnectServerSo_, "StoreMessage");
        if (storeMessage != nullptr) {
            storeMessage(instanceId, message);
        }
    }
    SetCreatTreeCallBack setCreatTreeCallBack = (SetCreatTreeCallBack)dlsym(handlerConnectServerSo_,
        "SetCreatTreeCallBack");
    setCreatTreeCallBack(std::bind(&SetCallbackFunc, std::placeholders::_1), instanceId);
}

void ConnectServerManager::SendInspector(const std::string& jsonTreeStr, const std::string& jsonSnapshotStr)
{
    WaitForDebugger waitForDebugger = (WaitForDebugger)dlsym(handlerConnectServerSo_, "WaitForDebugger");
    if (waitForDebugger == nullptr) {
        return;
    }
    SendMessage sendMessage = (SendMessage)dlsym(handlerConnectServerSo_, "SendMessage");
    StoreInspectorInfo storeInspectorInfo = (StoreInspectorInfo)dlsym(handlerConnectServerSo_, "StoreInspectorInfo");
    if (sendMessage == nullptr) {
        LOGE("sendMessage == nullptr");
        return;
    }
    if (storeInspectorInfo == nullptr) {
        LOGE("storeInspectorInfo == nullptr");
        return;
    }
    sendMessage(jsonTreeStr);
    sendMessage(jsonSnapshotStr);
    storeInspectorInfo(jsonTreeStr, jsonSnapshotStr);
}

void ConnectServerManager::RemoveInstance(int32_t instanceId)
{
    if (!isDebugVersion_ || handlerConnectServerSo_ == nullptr) {
        return;
    }
    LOGI("RemoveInstance %{public}d", instanceId);

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

    WaitForDebugger waitForDebugger = (WaitForDebugger)dlsym(handlerConnectServerSo_, "WaitForDebugger");
    if (waitForDebugger == nullptr) {
        return;
    }
    if (!waitForDebugger()) {
        SendMessage sendMessage = (SendMessage)dlsym(handlerConnectServerSo_, "SendMessage");
        if (sendMessage != nullptr) {
            sendMessage(message);
        }
    } else {
        RemoveMessage removeMessage = (RemoveMessage)dlsym(handlerConnectServerSo_, "RemoveMessage");
        if (removeMessage != nullptr) {
            removeMessage(instanceId);
        }
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
