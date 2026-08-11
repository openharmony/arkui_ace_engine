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

#include "base/external_instance_id_mapper.h"

namespace OHOS::Ace {

SINGLETON_INSTANCE_IMPL(ExternalInstanceIdMapper);

ExternalInstanceIdMapper::ExternalInstanceIdMapper() = default;

ExternalInstanceIdMapper::~ExternalInstanceIdMapper() = default;

void ExternalInstanceIdMapper::Add(uint32_t windowId, int32_t instanceId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    windowToInstance_[windowId] = instanceId;
}

void ExternalInstanceIdMapper::Remove(uint32_t windowId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    windowToInstance_.erase(windowId);
}

int32_t ExternalInstanceIdMapper::GetInstanceId(uint32_t windowId) const
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = windowToInstance_.find(windowId);
    if (it == windowToInstance_.end()) {
        return -1;
    }
    return it->second;
}

int32_t ExternalInstanceIdMapper::GetWindowId(int32_t instanceId) const
{
    std::lock_guard<std::mutex> lock(mutex_);
    for (const auto& entry : windowToInstance_) {
        if (entry.second == instanceId) {
            return static_cast<int32_t>(entry.first);
        }
    }
    return -1;
}

} // namespace OHOS::Ace
