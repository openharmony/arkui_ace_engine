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
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/common/ace_engine.h"
#include "core/common/ace_page.h"
#include "core/common/container.h"
#include "core/common/layout_inspector.h"
#include "core/event/ace_event_handler.h"

#if defined(IOS_PLATFORM)
#include "inspector/connect_inspector.h"
#include <sys/sysctl.h>
#endif

namespace OHOS::Ace {

namespace {

using StartServer = bool (*)(const std::string& packageName);
using SendMessage = void (*)(const std::string& message);
using SendLayoutMessage = void (*)(const std::string& message);
using StopServer = void (*)(const std::string& packageName);
using StoreMessage = void (*)(int32_t instanceId, const std::string& message);
using StoreInspectorInfo = void (*)(const std::string& jsonTreeStr, const std::string& jsonSnapshotStr);
using RemoveMessage = void (*)(int32_t instanceId);
using WaitForConnection = bool (*)();
using SetSwitchCallBack = void (*)(const std::function<void(bool)>& setStatus,
    const std::function<void(int32_t)>& createLayoutInfo, int32_t instanceId);

SendMessage g_sendMessage = nullptr;
SendLayoutMessage g_sendLayoutMessage = nullptr;
RemoveMessage g_removeMessage = nullptr;
StoreInspectorInfo g_storeInspectorInfo = nullptr;
StoreMessage g_storeMessage = nullptr;
SetSwitchCallBack g_setSwitchCallBack = nullptr;
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
    g_sendLayoutMessage = reinterpret_cast<SendLayoutMessage>(dlsym(handlerConnectServerSo_, "SendLayoutMessage"));
    g_storeInspectorInfo = reinterpret_cast<StoreInspectorInfo>(dlsym(handlerConnectServerSo_, "StoreInspectorInfo"));
    g_waitForConnection = reinterpret_cast<WaitForConnection>(dlsym(handlerConnectServerSo_, "WaitForConnection"));
#else
    using namespace OHOS::ArkCompiler;
    g_sendMessage = reinterpret_cast<SendMessage>(&Toolchain::SendMessage);
    g_storeMessage = reinterpret_cast<StoreMessage>(&Toolchain::StoreMessage);
    g_removeMessage = reinterpret_cast<RemoveMessage>(&Toolchain::RemoveMessage);
    g_setSwitchCallBack = reinterpret_cast<SetSwitchCallBack>(&Toolchain::SetSwitchCallBack);
    g_sendLayoutMessage = reinterpret_cast<SendLayoutMessage>(&Toolchain::SendLayoutMessage);
    g_storeInspectorInfo = reinterpret_cast<StoreInspectorInfo>(&Toolchain::StoreInspectorInfo);
    g_waitForConnection = reinterpret_cast<WaitForConnection>(&Toolchain::WaitForConnection);
#endif
    if (g_sendMessage == nullptr || g_storeMessage == nullptr || g_removeMessage == nullptr) {
        CloseConnectServerSo();
        return false;
    }

    if (g_storeInspectorInfo == nullptr || g_setSwitchCallBack == nullptr || g_waitForConnection == nullptr ||
        g_sendLayoutMessage == nullptr) {
        CloseConnectServerSo();
        return false;
    }
    return true;
}

void ConnectServerManager::InitConnectServer()
{
#if !defined(IOS_PLATFORM)
#if defined(ANDROID_PLATFORM)
    const std::string soDir = "libconnectserver_debugger.so";
#else
    const std::string soDir = "libconnectserver_debugger.z.so";
#endif // ANDROID_PLATFORM
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
#else
    StartServer startServer = reinterpret_cast<StartServer>(&ArkCompiler::Toolchain::StartServer);
#endif // IOS_PLATFORM
    startServer(packageName_);
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
    LOGD("Stop connect server");
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
    std::string message = GetInstanceMapMessage("addInstance", instanceId, language);

    if (!g_waitForConnection()) { // g_waitForConnection : the res means the connection state of the connect server
        g_sendMessage(message); // if connected, message will be sent immediately.
    } else { // if not connected, message will be stored and sent later when "connected" coming.
        g_storeMessage(instanceId, message);
    }
    CHECK_NULL_VOID(createLayoutInfo_);
    g_setSwitchCallBack([this](bool status) { setStatus_(status); },
        [this](int32_t containerId) { createLayoutInfo_(containerId); }, instanceId);
}

void ConnectServerManager::SendInspector(const std::string& jsonTreeStr, const std::string& jsonSnapshotStr)
{
    LOGI("ConnectServerManager SendInspector Start");
    g_sendLayoutMessage(jsonTreeStr);
    g_sendLayoutMessage(jsonSnapshotStr);
    g_storeInspectorInfo(jsonTreeStr, jsonSnapshotStr);
}

void ConnectServerManager::RemoveInstance(int32_t instanceId)
{
    if (!CheckDebugVersion()) {
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

    if (!g_waitForConnection()) {
        g_sendMessage(message);
    } else {
        g_removeMessage(instanceId);
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
