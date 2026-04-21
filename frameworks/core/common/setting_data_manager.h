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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_SETTING_DATA_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_SETTING_DATA_MANAGER_H

#include <functional>
#include <string>

#include "ui/base/macros.h"

namespace OHOS::Ace {

using DataUpdateFunc = std::function<void(const std::string&, int32_t)>;

class ACE_EXPORT SettingDataManager {
public:
    static constexpr int32_t INVALID_USER_ID = -1;

    static SettingDataManager& GetInstance();

    SettingDataManager() = default;
    virtual ~SettingDataManager() = default;

    virtual int32_t Initialize() = 0;

    virtual bool IsInitialized() const = 0;

    virtual int32_t GetCurrentUserId() = 0;

    virtual int32_t RegisterObserver(
        const std::string& key, const DataUpdateFunc& updateFunc, int32_t userId = INVALID_USER_ID) = 0;

    virtual int32_t UnregisterObserver(const std::string& key, int32_t userId = INVALID_USER_ID) = 0;

    virtual int32_t GetStringValue(
        const std::string& key, std::string& value, int32_t userId = INVALID_USER_ID) const = 0;

    virtual int32_t GetInt32ValueStrictly(
        const std::string& key, int32_t& value, int32_t userId = INVALID_USER_ID) const = 0;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_SETTING_DATA_MANAGER_H
