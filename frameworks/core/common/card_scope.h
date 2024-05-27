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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CARD_SCOPE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CARD_SCOPE_H

#include <functional>
#include <shared_mutex>
#include <stdint.h>

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"

namespace OHOS::Ace {

constexpr uint64_t INVALID_CARD_ID = 0;

class ACE_EXPORT CardScope {
public:
    explicit CardScope(uint64_t id)
    {
        restoreId_ = CardScope::CurrentId();
        CardScope::UpdateCurrent(id);
    }

    ~CardScope()
    {
        CardScope::UpdateCurrent(restoreId_);
    }

    ACE_FORCE_EXPORT static uint64_t CurrentId();

    static void UpdateCurrent(uint64_t id);

private:
    static thread_local uint64_t currentId_;
    uint64_t restoreId_ = INVALID_CARD_ID;

    ACE_DISALLOW_COPY_AND_MOVE(CardScope);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CARD_SCOPE_H
