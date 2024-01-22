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
#include "core/common/container_consts.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {
namespace {
// preview not support multi-instance, always using default instance id 0.
#if defined(PREVIEW)
constexpr int32_t DEFAULT_ID = 0;
#else
constexpr int32_t DEFAULT_ID = INSTANCE_ID_UNDEFINED;
#endif

const std::array<const char*, 4> ID_GENERATE_METHODS { "scope", "recent", "singelton", "undefined" };

std::atomic<uint32_t> containerCount_(0);
thread_local int32_t currentId_(DEFAULT_ID);
std::atomic<int32_t> singletonId_(DEFAULT_ID);
std::atomic<int32_t> recentActiveId_(DEFAULT_ID);
std::atomic<uint32_t> idGenerateMethod_(static_cast<uint32_t>(ID_GENERATE_METHOD::SCOPE));
}

int32_t ContainerScope::CurrentId()
{
    return currentId_;
}

const char* ContainerScope::CurrentIdGenerateMethod()
{
    return ID_GENERATE_METHODS[idGenerateMethod_.load(std::memory_order_relaxed)];
}

void ContainerScope::UpdateIdGenerateMethod(ID_GENERATE_METHOD method)
{
    idGenerateMethod_.store(static_cast<uint32_t>(method), std::memory_order_relaxed);
}

int32_t ContainerScope::SingletonId()
{
    return singletonId_.load(std::memory_order_relaxed);
}

int32_t ContainerScope::RecentActiveId()
{
    return recentActiveId_.load(std::memory_order_relaxed);
}

void ContainerScope::UpdateCurrent(int32_t id)
{
    currentId_ = id;
}

void ContainerScope::UpdateSingleton(int32_t id)
{
    singletonId_.store(id, std::memory_order_relaxed);
}

void ContainerScope::UpdateRecentActive(int32_t id)
{
    recentActiveId_.store(id, std::memory_order_relaxed);
}

uint32_t ContainerScope::ContainerCount()
{
    return containerCount_.load(std::memory_order_relaxed);
}

void ContainerScope::AddCount()
{
    containerCount_.fetch_add(1, std::memory_order_relaxed);
}

void ContainerScope::MinusCount()
{
    containerCount_.fetch_sub(1, std::memory_order_relaxed);
}

} // namespace OHOS::Ace
