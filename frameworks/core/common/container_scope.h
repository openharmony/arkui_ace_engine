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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_SCOPE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_SCOPE_H
#include <set>
#include <array>
#include <atomic>
#include <cinttypes>

#include <mutex>
#include <shared_mutex>


#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"

namespace OHOS::Ace {

enum class InstanceIdGenReason : uint32_t {
    SCOPE = 0,
    ACTIVE,
    DEFAULT,
    SINGLETON,
    FOREGROUND,
    UNDEFINED,
};

class ACE_EXPORT ContainerScope {
public:
    explicit ContainerScope(int32_t id)
    {
        UpdateCurrent(id);
    }

    ~ContainerScope()
    {
        UpdateCurrent(restoreId_);
    }

    static int32_t CurrentId();
    static int32_t DefaultId();
    static int32_t SingletonId();
    static int32_t RecentActiveId();
    static int32_t RecentForegroundId();
    static std::pair<int32_t, InstanceIdGenReason> CurrentIdWithReason();

    static void Add(int32_t id);
    static void Remove(int32_t id);
    static void RemoveAndCheck(int32_t id);

    static uint32_t ContainerCount();

    static void UpdateCurrent(int32_t id);
    static void UpdateSingleton(int32_t id);
    static void UpdateRecentActive(int32_t id);
    static void UpdateRecentForeground(int32_t id);
private:
    int32_t restoreId_ = CurrentId();

    ACE_DISALLOW_COPY_AND_MOVE(ContainerScope);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_SCOPE_H
