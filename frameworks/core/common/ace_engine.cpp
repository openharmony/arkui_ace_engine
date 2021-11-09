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

#if !defined(WINDOWS_PLATFORM) && !defined(MAC_PLATFORM)
#include <dlfcn.h>
#include <unistd.h>
#endif

#include "core/common/ace_engine.h"

#if !defined(WINDOWS_PLATFORM) && !defined(MAC_PLATFORM)
#include "core/common/ace_application_info.h"
#endif
#include "base/log/log.h"
#include "base/memory/memory_monitor.h"
#include "base/thread/background_task_executor.h"
#include "core/common/ace_page.h"
#include "core/image/image_cache.h"

namespace OHOS::Ace {
namespace {

std::unique_ptr<AceEngine> g_aceEngine;
#if !defined(WINDOWS_PLATFORM) && !defined(MAC_PLATFORM)
void* g_debugger = nullptr;
bool g_isNeedDebugBreakPoint = false;
#endif

}

#if !defined(WINDOWS_PLATFORM) && !defined(MAC_PLATFORM)
using StartServer = bool (*)(const std::string& componentName, const bool flagNeedDebugBreakPoint);
using StartUnixSocket = void (*)(const std::string& componentName);
using SendMessage = void (*)(const std::string& message);
using StopServer = void (*)(const std::string& componentName);
using AddMessage = void (*)(const int32_t instanceId, const std::string& message);
using RemoveMessage = void (*)(const int32_t instanceId);
using IsAttachStart = bool (*)();

void LoadDebuggerSo()
{
    LOGI("Load libconnectserver_debugger.z.so");
    const std::string soDir = "libconnectserver_debugger.z.so";
    g_debugger = dlopen(soDir.c_str(), RTLD_LAZY);
    if (g_debugger == nullptr) {
        LOGE("cannot find libconnectserver_debugger.z.so");
    }
}

void StartConnectServer(const std::string& componentName, const bool flagNeedDebugBreakPoint)
{
    LOGI("Start connect server");
    if (g_debugger == nullptr) {
        LOGE("g_debugger is null");
        return;
    }
    StartServer startServer = (StartServer)dlsym(g_debugger, "StartServer");
    if (startServer == nullptr) {
        LOGE("startServer=NULL, dlerror=%s", dlerror());
        return;
    }
    startServer(componentName, flagNeedDebugBreakPoint);
}

void StartSocket(const std::string& componentName)
{
    LOGI("Start unix socket");
    if (g_debugger == nullptr) {
        LOGE("g_debugger is null");
        return;
    }
    StartUnixSocket startUnixSocket = (StartUnixSocket)dlsym(g_debugger, "StartUnixSocket");
    if (startUnixSocket == nullptr) {
        LOGE("startUnixSocket=NULL, dlerror=%s", dlerror());
        return;
    }
    startUnixSocket(componentName);
}
#endif

AceEngine::AceEngine()
{
    // Watch dog thread(anr) can not exit when app stop.
    // watchDog_ = AceType::MakeRefPtr<WatchDog>();
#if !defined(WINDOWS_PLATFORM) && !defined(MAC_PLATFORM)
    if (AceApplicationInfo::GetInstance().IsDebugVersion()) {
        LoadDebuggerSo();
        g_isNeedDebugBreakPoint = AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint();
        std::string componentName = AceApplicationInfo::GetInstance().GetPackageName();
        StartConnectServer(componentName, g_isNeedDebugBreakPoint);
        StartSocket(componentName);
    }
#endif
}

AceEngine& AceEngine::Get()
{
    if (!g_aceEngine) {
        LOGI("AceEngine initialized in first time");
        g_aceEngine.reset(new AceEngine());
    }
    return *g_aceEngine;
}

void AceEngine::AddContainer(int32_t instanceId, const RefPtr<Container>& container, const std::string instanceName)
{
    LOGI("AddContainer %{public}d", instanceId);
    {
        std::lock_guard<std::mutex> lock(mutex_);
        const auto result = containerMap_.try_emplace(instanceId, container);
        if (!result.second) {
            LOGW("Already have container of this instance id: %{public}d", instanceId);
            return;
        }
#if !defined(WINDOWS_PLATFORM) && !defined(MAC_PLATFORM)
        const auto resultInstance = instanceMap_.try_emplace(instanceId, instanceName);
        if (!resultInstance.second) {
            LOGW("Already have instance name of this instance id: %{public}d", instanceId);
            return;
        }
#endif
    }
#if !defined(WINDOWS_PLATFORM) && !defined(MAC_PLATFORM)
    std::string message = GetInstanceMapMessage("addInstance", instanceId);
    LOGI("Addcontainer messageStr %{public}s", message.c_str());
    if (g_debugger == nullptr) {
        LOGE("g_debugger is null");
        return;
    }
    IsAttachStart isAttachStart = (IsAttachStart)dlsym(g_debugger, "IsAttachStart");
    if (isAttachStart != nullptr) {
        g_isNeedDebugBreakPoint = g_isNeedDebugBreakPoint || isAttachStart();
    }
    if (g_isNeedDebugBreakPoint) {
        AceApplicationInfo::GetInstance().SetNeedDebugBreakPoint(true);
        SendMessage sendMessage = (SendMessage)dlsym(g_debugger, "SendMessage");
        if (sendMessage != nullptr) {
            sendMessage(message);
        }
    } else {
        AddMessage addMessage = (AddMessage)dlsym(g_debugger, "AddMessage");
        if (addMessage != nullptr) {
            addMessage(instanceId, message);
        }
    }
#endif
}

void AceEngine::RemoveContainer(int32_t instanceId)
{
    LOGI("RemoveContainer %{public}d", instanceId);
    size_t num = 0;
#if !defined(WINDOWS_PLATFORM) && !defined(MAC_PLATFORM)
    size_t numInstance = 0;
    std::string message = GetInstanceMapMessage("destroyInstance", instanceId);
    LOGI("RemoveContainer messageStr %{public}s", message.c_str());
    if (g_debugger) {
        IsAttachStart isAttachStart = (IsAttachStart)dlsym(g_debugger, "IsAttachStart");
        if (isAttachStart != nullptr) {
            g_isNeedDebugBreakPoint = g_isNeedDebugBreakPoint || isAttachStart();
        }
        if (g_isNeedDebugBreakPoint) {
            SendMessage sendMessage = (SendMessage)dlsym(g_debugger, "SendMessage");
            if (sendMessage != nullptr) {
                sendMessage(message);
            }
        } else {
            RemoveMessage removeMessage = (RemoveMessage)dlsym(g_debugger, "RemoveMessage");
            if (removeMessage != nullptr) {
                removeMessage(instanceId);
            }
        }
    }
#endif
    {
        std::lock_guard<std::mutex> lock(mutex_);
        num = containerMap_.erase(instanceId);
#if !defined(WINDOWS_PLATFORM) && !defined(MAC_PLATFORM)
        numInstance = instanceMap_.erase(instanceId);
#endif
    }
    if (num == 0) {
        LOGW("container not found with instance id: %{public}d", instanceId);
    }
#if !defined(WINDOWS_PLATFORM) && !defined(MAC_PLATFORM)
    if (numInstance == 0) {
        LOGW("Instance name not found with instance id: %{public}d", instanceId);
    }
#endif
    if (watchDog_) {
        watchDog_->Unregister(instanceId);
    }
}

void AceEngine::Dump(const std::vector<std::string>& params) const
{
    std::unordered_map<int32_t, RefPtr<Container>> copied;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        copied = containerMap_;
    }
    for (const auto& container : copied) {
        auto pipelineContext = container.second->GetPipelineContext();
        if (!pipelineContext) {
            LOGW("the pipeline context is nullptr, pa container");
            continue;
        }
        pipelineContext->GetTaskExecutor()->PostSyncTask(
            [params, container = container.second]() { container->Dump(params); }, TaskExecutor::TaskType::UI);
    }
}

RefPtr<Container> AceEngine::GetContainer(int32_t instanceId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto container = containerMap_.find(instanceId);
    if (container != containerMap_.end()) {
        return container->second;
    } else {
        return nullptr;
    }
}

void AceEngine::RegisterToWatchDog(int32_t instanceId, const RefPtr<TaskExecutor>& taskExecutor)
{
    if (watchDog_) {
        watchDog_->Register(instanceId, taskExecutor);
    }
}

void AceEngine::BuriedBomb(int32_t instanceId, uint64_t bombId)
{
    if (watchDog_) {
        watchDog_->BuriedBomb(instanceId, bombId);
    }
}

void AceEngine::DefusingBomb(int32_t instanceId)
{
    if (watchDog_) {
        watchDog_->DefusingBomb(instanceId);
    }
}

void AceEngine::TriggerGarbageCollection()
{
    std::unordered_map<int32_t, RefPtr<Container>> copied;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (containerMap_.empty()) {
            return;
        }
        copied = containerMap_;
    }

    auto taskExecutor = copied.begin()->second->GetTaskExecutor();
    taskExecutor->PostTask([] { PurgeMallocCache(); }, TaskExecutor::TaskType::PLATFORM);
#if defined(OHOS_PLATFORM) && defined(ENABLE_NATIVE_VIEW)
    // GPU and IO thread is shared while enable native view
    taskExecutor->PostTask([] { PurgeMallocCache(); }, TaskExecutor::TaskType::GPU);
    taskExecutor->PostTask([] { PurgeMallocCache(); }, TaskExecutor::TaskType::IO);
#endif

    for (const auto& container : copied) {
        container.second->TriggerGarbageCollection();
    }

    ImageCache::Purge();
    BackgroundTaskExecutor::GetInstance().TriggerGarbageCollection();
    PurgeMallocCache();
}

void AceEngine::NotifyContainers(const std::function<void(const RefPtr<Container>&)>& callback)
{
    if (!callback) {
        return;
    }
    std::lock_guard<std::mutex> lock(mutex_);
    for (const auto& [first, second] : containerMap_) {
        callback(second);
    }
}

#if !defined(WINDOWS_PLATFORM) && !defined(MAC_PLATFORM)
std::string AceEngine::GetInstanceMapMessage(const char* messageType, const int32_t instanceId)
{
    auto message = JsonUtil::Create(true);

    message->Put("type", messageType);
    message->Put("tid", instanceId);
    message->Put("name", instanceMap_[instanceId].c_str());

    return message->ToString();
}
#endif
} // namespace OHOS::Ace