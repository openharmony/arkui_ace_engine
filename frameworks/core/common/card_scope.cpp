/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/common/card_scope.h"

namespace OHOS::Ace {

// preview not support multi-instance, always using default instance id 0.
#if defined(PREVIEW)
thread_local uint64_t CardScope::currentId_ = 0;
#else
thread_local uint64_t CardScope::currentId_ = -1;
#endif
std::function<void(uint64_t)> CardScope::updateScopeNotify_;
std::shared_mutex CardScope::scopeLock_;

uint64_t CardScope::CurrentId()
{
    return currentId_;
}

void CardScope::UpdateCurrent(uint64_t id)
{
    currentId_ = id;
    std::shared_lock<std::shared_mutex> readLock(scopeLock_);
    if (updateScopeNotify_) {
        updateScopeNotify_(id);
    }
}

void CardScope::SetScopeNotify(std::function<void(uint64_t)>&& notify)
{
    std::unique_lock<std::shared_mutex> writeLock(scopeLock_);
    updateScopeNotify_ = std::move(notify);
}

} // namespace OHOS::Ace