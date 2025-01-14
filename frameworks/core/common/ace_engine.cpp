/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/common/ace_engine.h"

#include <csignal>
#include "base/thread/background_task_executor.h"
#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "core/common/plugin_manager.h"
#endif

namespace OHOS::Ace {
namespace {

#ifdef OHOS_STANDARD_SYSTEM
enum class SignalType {
    SIGNAL_JSHEAP_OLD,
    SIGNAL_JSHEAP,
    SIGNAL_JSHEAP_PRIV,
    SIGNAL_NO_TRIGGERID,
    SIGNAL_NO_TRIGGERID_PRIV,
    SIGNAL_FORCE_FULLGC,
};

void HandleSignal(int signal, [[maybe_unused]] siginfo_t *siginfo, void *context)
{
    LOGW("HandleSignal start, signal is %{public}d", signal);
    if (signal != MUSL_SIGNAL_JSHEAP) {
        LOGW("HandleSignal failed, signal is %{public}d", signal);
        return;
    }
    LOGW("HandleSignal sival_int is %{public}d", siginfo->si_value.sival_int);
    switch (static_cast<SignalType>(siginfo->si_value.sival_int)) {
        case SignalType::SIGNAL_JSHEAP_OLD: {
            AceEngine::Get().DumpJsHeap(false);
            break;
        }
        case SignalType::SIGNAL_JSHEAP: {
            AceEngine::Get().DumpJsHeap(false);
            break;
        }
        case SignalType::SIGNAL_JSHEAP_PRIV: {
            AceEngine::Get().DumpJsHeap(true);
            break;
        }
        case SignalType::SIGNAL_NO_TRIGGERID: {
            AceEngine::Get().DumpJsHeap(false);
            AceEngine::Get().DestroyHeapProfiler();
            break;
        }
        case SignalType::SIGNAL_NO_TRIGGERID_PRIV: {
            AceEngine::Get().DumpJsHeap(true);
            AceEngine::Get().DestroyHeapProfiler();
            break;
        }
        case SignalType::SIGNAL_FORCE_FULLGC: {
            AceEngine::Get().ForceFullGC();
            break;
        }
        default:
            break;
    }
}
#endif

} // namespace

AceEngine::AceEngine()
{
    if (!SystemProperties::GetHookModeEnabled()) {
        watchDog_ = AceType::MakeRefPtr<WatchDog>();
    }
}

AceEngine::~AceEngine() {}

AceEngine& AceEngine::Get()
{
    static AceEngine engine;
    return engine;
}

void AceEngine::InitJsDumpHeadSignal()
{
#ifdef OHOS_STANDARD_SYSTEM
    struct sigaction sigAct;
    sigemptyset(&sigAct.sa_mask);
    sigAct.sa_flags = SA_SIGINFO;
    sigAct.sa_sigaction = HandleSignal;
    sigaction(MUSL_SIGNAL_JSHEAP, &sigAct, NULL);
#endif
}

void AceEngine::AddContainer(int32_t instanceId, const RefPtr<Container>& container)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    containerMap_.try_emplace(instanceId, container);
}

void AceEngine::RemoveContainer(int32_t instanceId)
{
    size_t num = 0;
    {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        num = containerMap_.erase(instanceId);
    }
    if (num == 0) {
        LOGW("container not found with instance id: %{public}d", instanceId);
    }
}

RefPtr<Container> AceEngine::GetContainer(int32_t instanceId)
{
#ifdef PLUGIN_COMPONENT_SUPPORTED
    if (instanceId >= MIN_PLUGIN_SUBCONTAINER_ID) {
        instanceId = PluginManager::GetInstance().GetPluginParentContainerId(instanceId);
    }
#endif
    std::shared_lock<std::shared_mutex> lock(mutex_);
    auto container = containerMap_.find(instanceId);
    if (container != containerMap_.end()) {
        return container->second;
    } else {
        return nullptr;
    }
}

bool AceEngine::HasContainer(int32_t containerId) const
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    auto iter = containerMap_.find(containerId);
    return iter != containerMap_.end();
}

void AceEngine::RegisterToWatchDog(int32_t instanceId, const RefPtr<TaskExecutor>& taskExecutor, bool useUIAsJSThread)
{
    CHECK_NULL_VOID(watchDog_);
    watchDog_->Register(instanceId, taskExecutor, useUIAsJSThread);
}

void AceEngine::UnRegisterFromWatchDog(int32_t instanceId)
{
    CHECK_NULL_VOID(watchDog_);
    watchDog_->Unregister(instanceId);
}

void AceEngine::BuriedBomb(int32_t instanceId, uint64_t bombId)
{
    CHECK_NULL_VOID(watchDog_);
    watchDog_->BuriedBomb(instanceId, bombId);
}

void AceEngine::DefusingBomb(int32_t instanceId)
{
    CHECK_NULL_VOID(watchDog_);
    watchDog_->DefusingBomb(instanceId);
}

void AceEngine::TriggerGarbageCollection()
{
    decltype(containerMap_) copied;
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        if (containerMap_.empty()) {
            return;
        }
        copied = containerMap_;
    }

    auto taskExecutor = copied.begin()->second->GetTaskExecutor();
    taskExecutor->PostTask([] { PurgeMallocCache(); }, TaskExecutor::TaskType::PLATFORM, "ArkUIPurgeMallocCache",
        TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
#if defined(OHOS_PLATFORM) && defined(ENABLE_NATIVE_VIEW)
    // GPU and IO thread is shared while enable native view
    taskExecutor->PostTask([] { PurgeMallocCache(); }, TaskExecutor::TaskType::GPU, "ArkUIPurgeMallocCache",
        TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
    taskExecutor->PostTask([] { PurgeMallocCache(); }, TaskExecutor::TaskType::IO, "ArkUIPurgeMallocCache",
        TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
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
    CHECK_NULL_VOID(callback);
    decltype(containerMap_) copied;
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        copied = containerMap_;
    }
    for (const auto& [first, second] : copied) {
        // first = container ID
        ContainerScope scope(first);
        callback(second);
    }
}

void AceEngine::NotifyContainersOrderly(const std::function<void(const RefPtr<Container>&)>& callback)
{
    CHECK_NULL_VOID(callback);
    std::map<int32_t, RefPtr<Container>> copied;
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        for (const auto& pair : containerMap_) {
            copied.insert(pair);
        }
    }
    for (const auto& [first, second] : copied) {
        // first = container ID
        ContainerScope scope(first);
        callback(second);
    }
}

void AceEngine::DumpJsHeap(bool isPrivate) const
{
    decltype(containerMap_) copied;
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        copied = containerMap_;
    }
    for (const auto& container : copied) {
        container.second->DumpHeapSnapshot(isPrivate);
    }
}

void AceEngine::DestroyHeapProfiler() const
{
    decltype(containerMap_) copied;
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        copied = containerMap_;
    }
    for (const auto& container : copied) {
        container.second->DestroyHeapProfiler();
    }
}

void AceEngine::ForceFullGC() const
{
    decltype(containerMap_) copied;
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        copied = containerMap_;
    }
    for (const auto& container : copied) {
        container.second->ForceFullGC();
    }
}

} // namespace OHOS::Ace
