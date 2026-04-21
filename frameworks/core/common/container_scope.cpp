/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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

#if defined(NAPI_SCOPE_ERROR_HIVEW_REPORT)
#include <dlfcn.h>
#endif

#include "core/common/container_scope.h"

#include "core/common/container_consts.h"

namespace OHOS::Ace {
namespace {
// preview not support multi-instance, always using default instance id 0.
#if defined(PREVIEW)
constexpr int32_t DEFAULT_ID = 0;
#else
constexpr int32_t DEFAULT_ID = INSTANCE_ID_UNDEFINED;
#endif

std::shared_mutex mutex_;
std::set<int32_t> containerSet_;
thread_local int32_t currentLocalId_(DEFAULT_ID);
thread_local int32_t currentId_(DEFAULT_ID);
std::atomic<int32_t> recentActiveId_(DEFAULT_ID);
std::atomic<int32_t> recentForegroundId_(DEFAULT_ID);
}
#if defined(NAPI_SCOPE_ERROR_HIVEW_REPORT)
void* ContainerScope::registerHandler_ = nullptr;
ContainerScope::ReportScopeErrorFun ContainerScope::reportScopeError_ = nullptr;

void ContainerScope::ReportScopeError()
{
    if (reportScopeError_ != nullptr) {
        reportScopeError_();
        return;
    }
    registerHandler_ = dlopen("libace_compatible.z.so", RTLD_LAZY);
    reportScopeError_ = (ReportScopeErrorFun)dlsym(registerHandler_, "OHOS_ACE_ScopeErrorHivewReport");
    reportScopeError_();
}

void ContainerScope::CheckIdChange(int32_t id)
{
    if (id < 0) {
        return;
    }
    auto safeId = SafelyId();
    if (id != safeId) {
        ReportScopeError();
    }
}
#endif

int32_t ContainerScope::CurrentId()
{
    return currentId_;
}

void ContainerScope::UpdateLocalCurrent(int32_t id)
{
    currentLocalId_ = id;
}

int32_t ContainerScope::CurrentLocalId()
{
    return currentLocalId_;
}

int32_t ContainerScope::DefaultId()
{
    if (ContainerCount() > 0) {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return *containerSet_.rbegin();
    }
    return INSTANCE_ID_UNDEFINED;
}

int32_t ContainerScope::SingletonId()
{
    if (ContainerCount() != 1) {
        return INSTANCE_ID_UNDEFINED;
    }
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return *containerSet_.begin();
}

int32_t ContainerScope::RecentActiveId()
{
    return recentActiveId_.load(std::memory_order_relaxed);
}

int32_t ContainerScope::RecentForegroundId()
{
    return recentForegroundId_.load(std::memory_order_relaxed);
}

int32_t ContainerScope::SafelyId()
{
    uint32_t containerCount = ContainerCount();
    if (containerCount == 0) {
        return INSTANCE_ID_UNDEFINED;
    }
    if (containerCount == 1) {
        return SingletonId();
    }
    int32_t currentId = RecentActiveId();
    if (currentId >= 0) {
        return currentId;
    }
    currentId = RecentForegroundId();
    if (currentId >= 0) {
        return currentId;
    }
    return DefaultId();
}

std::pair<int32_t, InstanceIdGenReason> ContainerScope::CurrentIdWithReason()
{
    int32_t currentId = CurrentId();
    if (currentId >= 0) {
        return { currentId, InstanceIdGenReason::SCOPE };
    }
    uint32_t containerCount = ContainerCount();
    if (containerCount == 0) {
        return { INSTANCE_ID_UNDEFINED, InstanceIdGenReason::UNDEFINED };
    }
    if (containerCount == 1) {
        return { SingletonId(), InstanceIdGenReason::SINGLETON };
    }
    currentId = ContainerScope::RecentActiveId();
    if (currentId >= 0) {
        return { currentId, InstanceIdGenReason::ACTIVE };
    }
    currentId = ContainerScope::RecentForegroundId();
    if (currentId >= 0) {
        return { currentId, InstanceIdGenReason::FOREGROUND };
    }
    return { ContainerScope::DefaultId(), InstanceIdGenReason::DEFAULT };
}

const std::string ContainerScope::ReasonToDescription(InstanceIdGenReason reason)
{
    switch (reason) {
        case InstanceIdGenReason::SCOPE:
            return "The instance is determined by the caller";
        case InstanceIdGenReason::ACTIVE:
            return "No specific instance was specified, so the most recently active instance was retrieved";
        case InstanceIdGenReason::DEFAULT:
            return "No specific instance was specified, using default";
        case InstanceIdGenReason::SINGLETON:
            return "No specific instance was specified, return the only remaining instance";
        case InstanceIdGenReason::FOREGROUND:
            return "No specific instance was specified, return the foreground instance";
        case InstanceIdGenReason::UNDEFINED:
            return "No valid instance exists";
        default:
            return "Unknown reason";
    }
}

const std::set<int32_t> ContainerScope::GetAllUIContexts()
{
    return containerSet_;
}

void ContainerScope::UpdateCurrent(int32_t id)
{
    currentId_ = id;
}

void ContainerScope::UpdateRecentActive(int32_t id)
{
    recentActiveId_.store(id, std::memory_order_relaxed);
}

void ContainerScope::UpdateRecentForeground(int32_t id)
{
    recentForegroundId_.store(id, std::memory_order_relaxed);
}

uint32_t ContainerScope::ContainerCount()
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return static_cast<uint32_t>(containerSet_.size());
}

void ContainerScope::Add(int32_t id)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    containerSet_.emplace(id);
}

void ContainerScope::Remove(int32_t id)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    containerSet_.erase(id);
}

void ContainerScope::RemoveAndCheck(int32_t id)
{
    Remove(id);
    if (RecentActiveId() == id) {
        UpdateRecentActive(INSTANCE_ID_UNDEFINED);
    }
    if (RecentForegroundId() == id) {
        UpdateRecentForeground(INSTANCE_ID_UNDEFINED);
    }
}
} // namespace OHOS::Ace
