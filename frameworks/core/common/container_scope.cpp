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

#include "core/common/container_scope.h"

namespace OHOS::Ace {
namespace {
std::shared_mutex mutex_;
std::set<int32_t> containerSet_;
thread_local int32_t currentId_(ContainerScope::DEFAULT_ID);
std::atomic<int32_t> recentActiveId_(ContainerScope::DEFAULT_ID);
std::atomic<int32_t> recentForegroundId_(ContainerScope::DEFAULT_ID);
}

// preview not support multi-instance, always using default instance id 0.
#if defined(PREVIEW)
const int32_t ContainerScope::DEFAULT_ID = 0;
#else
const int32_t ContainerScope::DEFAULT_ID = INSTANCE_ID_UNDEFINED;
#endif

int32_t ContainerScope::CurrentId()
{
    return currentId_;
}

int32_t ContainerScope::DefaultId()
{
    if (ContainerCount() > 0) {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return *containerSet_.rbegin();
    }
    return DEFAULT_ID;
}

int32_t ContainerScope::SingletonId()
{
    if (ContainerCount() != 1) {
        return DEFAULT_ID;
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

std::pair<int32_t, InstanceIdGenReason> ContainerScope::CurrentIdWithReason()
{
    int32_t currentId = CurrentId();
    if (currentId >= 0) {
        return { currentId, InstanceIdGenReason::SCOPE };
    }
    uint32_t containerCount = ContainerCount();
    if (containerCount == 0) {
        return { DEFAULT_ID, InstanceIdGenReason::UNDEFINED };
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
        UpdateRecentActive(DEFAULT_ID);
    }
    if (RecentForegroundId() == id) {
        UpdateRecentForeground(DEFAULT_ID);
    }
}

} // namespace OHOS::Ace
