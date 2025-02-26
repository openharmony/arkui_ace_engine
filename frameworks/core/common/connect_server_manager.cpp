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
#include "core/common/layout_inspector.h"
#if defined(IOS_PLATFORM)
#include "inspector/connect_inspector.h"
#include <sys/sysctl.h>
#endif

namespace OHOS::Ace {

namespace {

using StartServer = bool (*)(const std::string& packageName);
using StartServerForSocketPair = bool (*)(int32_t);
using SendMessage = void (*)(const std::string& message);
using StopServer = void (*)(const std::string& packageName);
using StoreMessage = void (*)(int32_t instanceId, const std::string& message);
using RemoveMessage = void (*)(int32_t instanceId);
using WaitForConnection = bool (*)();
using SetSwitchCallBack = void (*)(const std::function<void(bool)>& setStatus,
    const std::function<void(int32_t)>& createLayoutInfo, int32_t instanceId);
using SetDebugModeCallBack = void (*)(const std::function<void()>& setDebugMode);

SendMessage g_sendMessage = nullptr;
RemoveMessage g_removeMessage = nullptr;
StoreMessage g_storeMessage = nullptr;
SetSwitchCallBack g_setSwitchCallBack = nullptr;
SetDebugModeCallBack g_setDebugModeCallBack = nullptr;
WaitForConnection g_waitForConnection = nullptr;


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

bool ConnectServerManager::CheckDebugVersion()
{
#if !defined(IOS_PLATFORM)
    if (!isDebugVersion_ || handlerConnectServerSo_ == nullptr) {
        return false;
    }
#else
    if (!isDebugVersion_) {
        return false;
    }
#endif
    return true;
}

ConnectServerManager& ConnectServerManager::Get()
{
    static ConnectServerManager connectServerManager;
    return connectServerManager;
}

bool ConnectServerManager::InitFunc()
{
#if !defined(IOS_PLATFORM)
    g_sendMessage = reinterpret_cast<SendMessage>(dlsym(handlerConnectServerSo_, "SendMessage"));
    g_storeMessage = reinterpret_cast<StoreMessage>(dlsym(handlerConnectServerSo_, "StoreMessage"));
    g_removeMessage = reinterpret_cast<RemoveMessage>(dlsym(handlerConnectServerSo_, "RemoveMessage"));
    g_setSwitchCallBack = reinterpret_cast<SetSwitchCallBack>(dlsym(handlerConnectServerSo_, "SetSwitchCallBack"));
    g_setDebugModeCallBack =
        reinterpret_cast<SetDebugModeCallBack>(dlsym(handlerConnectServerSo_, "SetDebugModeCallBack"));
    g_waitForConnection = reinterpret_cast<WaitForConnection>(dlsym(handlerConnectServerSo_, "WaitForConnection"));
#else
    using namespace OHOS::ArkCompiler;
    g_sendMessage = reinterpret_cast<SendMessage>(&Toolchain::SendMessage);
    g_storeMessage = reinterpret_cast<StoreMessage>(&Toolchain::StoreMessage);
    g_removeMessage = reinterpret_cast<RemoveMessage>(&Toolchain::RemoveMessage);
    g_setSwitchCallBack = reinterpret_cast<SetSwitchCallBack>(&Toolchain::SetSwitchCallBack);
    g_setDebugModeCallBack = reinterpret_cast<SetDebugModeCallBack>(&Toolchain::SetDebugModeCallBack);
    g_waitForConnection = reinterpret_cast<WaitForConnection>(&Toolchain::WaitForConnection);
#endif
    if (g_sendMessage == nullptr || g_storeMessage == nullptr || g_removeMessage == nullptr) {
        CloseConnectServerSo();
        return false;
    }

    if (g_setSwitchCallBack == nullptr || g_waitForConnection == nullptr) {
        CloseConnectServerSo();
        return false;
    }
    return true;
}

void ConnectServerManager::InitConnectServer()
{
#if !defined(IOS_PLATFORM)
#if defined(ANDROID_PLATFORM)
    const std::string soDir = "libark_connect_inspector.so";
#else
    const std::string soDir = "libark_connect_inspector.z.so";
#endif // ANDROID_PLATFORM
    if (handlerConnectServerSo_ == nullptr) {
        handlerConnectServerSo_ = dlopen(soDir.c_str(), RTLD_LAZY);
    }
    if (handlerConnectServerSo_ == nullptr) {
        LOGE("Cannot find %{public}s", soDir.c_str());
        return;
    }
    StartServer startServer = reinterpret_cast<StartServer>(dlsym(handlerConnectServerSo_, "StartServer"));
    if (startServer == nullptr || !InitFunc()) {
        LOGE("startServer = NULL, dlerror = %s", dlerror());
        return;
    }
#else
    StartServer startServer = reinterpret_cast<StartServer>(&ArkCompiler::Toolchain::StartServer);
#endif // IOS_PLATFORM
    startServer(packageName_);
    g_setDebugModeCallBack([]() {
        AceApplicationInfo::GetInstance().SetNeedDebugBreakPoint(false);
    });
}

void ConnectServerManager::StartConnectServerWithSocketPair(int32_t socketFd)
{
    if (handlerConnectServerSo_ == nullptr) {
        handlerConnectServerSo_ = dlopen("libark_connect_inspector.z.so", RTLD_LAZY);
    }
    CHECK_NULL_VOID(handlerConnectServerSo_);

    auto startServerForSocketPair =
        reinterpret_cast<StartServerForSocketPair>(dlsym(handlerConnectServerSo_, "StartServerForSocketPair"));
    CHECK_NULL_VOID(startServerForSocketPair);
    startServerForSocketPair(socketFd);
}

void ConnectServerManager::CloseConnectServerSo()
{
#if !defined(IOS_PLATFORM)
    CHECK_NULL_VOID(handlerConnectServerSo_);
    dlclose(handlerConnectServerSo_);
    handlerConnectServerSo_ = nullptr;
#endif
}

// When use multi-instances project, debug mode should be set to support debug
void ConnectServerManager::SetDebugMode()
{
    if (!CheckDebugVersion()) {
        return;
    }

    if (!g_waitForConnection()) { // waitForDebugger : waitForDebugger means the connection state of the connect server
        AceApplicationInfo::GetInstance().SetNeedDebugBreakPoint(true);
    }
}

void ConnectServerManager::StopConnectServer()
{
#if !defined(IOS_PLATFORM)
    CHECK_NULL_VOID(handlerConnectServerSo_);
    StopServer stopServer = reinterpret_cast<StopServer>(dlsym(handlerConnectServerSo_, "StopServer"));
    if (stopServer == nullptr) {
        LOGE("stopServer = NULL, dlerror = %s", dlerror());
        return;
    }
#else
    StopServer stopServer = reinterpret_cast<StopServer>(&ArkCompiler::Toolchain::StopServer);
#endif
    stopServer(packageName_);
}

void ConnectServerManager::AddInstance(
    int32_t instanceId, const std::string& language, const std::string& instanceName)
{
    if (!CheckDebugVersion()) {
        return;
    }
    {
        std::lock_guard<std::mutex> lock(mutex_);
        const auto result = instanceMap_.try_emplace(instanceId, instanceName);
        if (!result.second) {
            return;
        }
    }
    // Get the message including information of new instance, which will be send to IDE.
    std::string message = GetInstanceMapMessage("addInstance", instanceId, language);

    g_storeMessage(instanceId, message);
    if (!g_waitForConnection()) { // g_waitForConnection : the res means the connection state of the connect server
        g_sendMessage(message); // if connected, message will be sent immediately.
    }
    CHECK_NULL_VOID(createLayoutInfo_);
    auto setStatus = [this](bool status) {
        setStatus_(status);
    };
    auto createLayoutInfo = [this](int32_t containerId) {
        createLayoutInfo_(containerId);
    };
    g_setSwitchCallBack(setStatus, createLayoutInfo, instanceId);
}

void ConnectServerManager::SendInspector(const std::string& jsonTreeStr, const std::string& jsonSnapshotStr)
{
    LOGI("ConnectServerManager SendInspector Start");
    g_sendMessage(jsonTreeStr);
    g_sendMessage(jsonSnapshotStr);
}

void ConnectServerManager::RemoveInstance(int32_t instanceId)
{
    if (!CheckDebugVersion()) {
        return;
    }

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

    g_removeMessage(instanceId);
    if (!g_waitForConnection()) {
        g_sendMessage(message);
    }
}

std::string ConnectServerManager::GetInstanceMapMessage(
    const char* messageType, int32_t instanceId, const std::string& language)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto message = JsonUtil::Create(true);
    message->Put("type", messageType);
    message->Put("instanceId", instanceId);
    message->Put("name", instanceMap_[instanceId].c_str());
#if !defined(IOS_PLATFORM)
    message->Put("tid", gettid());
#else
    uint64_t tid;
    pthread_threadid_np(0, &tid);
    message->Put("tid", static_cast<int64_t>(tid));
#endif
    message->Put("apiType", "faMode");
    message->Put("language", language.c_str());
    return message->ToString();
}

void ConnectServerManager::SetLayoutInspectorCallback(
    const std::function<void(int32_t)>& createLayoutInfo, const std::function<void(bool)>& setStatus)
{
    createLayoutInfo_ = createLayoutInfo;
    setStatus_ = setStatus;
}

std::function<void(int32_t)> ConnectServerManager::GetLayoutInspectorCallback()
{
    return createLayoutInfo_;
}
} // namespace OHOS::Ace
