/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/common/container.h"
namespace OHOS::Ace {
int32_t ContainerScope::CurrentId()
{
    return 0;
}

int32_t ContainerScope::CurrentLocalId()
{
    return 0;
}

int32_t ContainerScope::DefaultId()
{
    return 0;
}

int32_t ContainerScope::SingletonId()
{
    return 0;
}

int32_t ContainerScope::RecentActiveId()
{
    return 0;
}

int32_t ContainerScope::RecentForegroundId()
{
    return 0;
}

std::pair<int32_t, InstanceIdGenReason> ContainerScope::CurrentIdWithReason(bool checkThread)
{
    (void)checkThread;
    return { 0, InstanceIdGenReason::UNDEFINED };
}

const std::string ContainerScope::ReasonToDescription(InstanceIdGenReason reason)
{
    (void)reason;
    return {};
}

const std::set<int32_t> ContainerScope::GetAllUIContexts()
{
    return {};
}

void ContainerScope::Add(int32_t id)
{
    (void)id;
}

void ContainerScope::Remove(int32_t id)
{
    (void)id;
}

void ContainerScope::RemoveAndCheck(int32_t id)
{
    (void)id;
}

uint32_t ContainerScope::ContainerCount()
{
    return 0;
}

void ContainerScope::UpdateCurrent(int32_t id)
{
    (void)id;
}

void ContainerScope::UpdateLocalCurrent(int32_t id)
{
    (void)id;
}

void ContainerScope::UpdateSingleton(int32_t id)
{
    (void)id;
}

void ContainerScope::UpdateRecentActive(int32_t id)
{
    (void)id;
}

void ContainerScope::UpdateRecentForeground(int32_t id)
{
    (void)id;
}

int32_t ContainerScope::SafelyId(bool checkThread)
{
    (void)checkThread;
    return 0;
}

void ContainerScope::CheckIdChange(int32_t id)
{
    (void)id;
}

void ContainerScope::MarkIsolatedThread() {}

void ContainerScope::AddLocal(int32_t id)
{
    (void)id;
}

void ContainerScope::RemoveLocal(int32_t id)
{
    (void)id;
}

void ContainerScope::ResetIsolatedThread() {}

#ifdef ENABLE_CONTAINER_SCOPE_TRACKING

uint64_t ContainerScope::PushCurrent(int32_t id, const char* fileId, int32_t line, int32_t sourceType)
{
    (void)id;
    (void)fileId;
    (void)line;
    (void)sourceType;
    return 0;
}

void ContainerScope::PopCurrent(uint64_t uid, int32_t restoreId, const char* fileId, int32_t line, int32_t sourceType)
{
    (void)uid;
    (void)restoreId;
    (void)fileId;
    (void)line;
    (void)sourceType;
}

std::vector<CurrentIdStackFrame> ContainerScope::GetStackHistory()
{
    return {};
}

std::vector<CurrentIdStackFrame> ContainerScope::GetActiveFrames()
{
    return {};
}

void ContainerScope::ClearHistory() {}

void ContainerScope::EnableTracking(bool enable)
{
    (void)enable;
}

bool ContainerScope::IsTrackingEnabled()
{
    return false;
}

void ContainerScope::SetMaxHistorySize(size_t size)
{
    (void)size;
}

bool ContainerScope::IsStackBalanced()
{
    return true;
}

std::string ContainerScope::Diagnose()
{
    return {};
}

ContainerScope::ContainerScope(int32_t id, const char* fileId, int32_t line)
    : restoreId_(CurrentId()), pushedUid_(0), pushed_(false)
{
    (void)fileId;
    (void)line;
    UpdateCurrent(id);
}

ContainerScope::ContainerScope(int32_t id, bool enable, const char* fileId, int32_t line)
    : restoreId_(CurrentId()), pushedUid_(0), pushed_(false)
{
    (void)fileId;
    (void)line;
    if (enable) {
        UpdateCurrent(id);
    }
}
#endif // ENABLE_CONTAINER_SCOPE_TRACKING

ContainerScope::ContainerScope(int32_t id)
{
    UpdateCurrent(id);
}

ContainerScope::ContainerScope(int32_t id, bool enable)
{
    if (enable) {
        UpdateCurrent(id);
    }
}

ContainerScope::~ContainerScope()
{
    UpdateCurrent(restoreId_);
}

void ContainerScope::RegisterThreadCheckFunc(CheckRunOnUIThreadFunc checkFunc)
{
    (void)checkFunc;
}
} // namespace OHOS::Ace
