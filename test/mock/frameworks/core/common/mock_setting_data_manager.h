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

#ifndef FOUNDATION_ACE_TEST_MOCK_CORE_COMMON_MOCK_SETTING_DATA_MANAGER_H
#define FOUNDATION_ACE_TEST_MOCK_CORE_COMMON_MOCK_SETTING_DATA_MANAGER_H

#include "gmock/gmock.h"

#include "core/common/setting_data_manager.h"

namespace OHOS::Ace {

class ACE_EXPORT MockSettingDataManager: public SettingDataManager {
public:
    MOCK_METHOD(int32_t, Initialize, (), (override));
    MOCK_METHOD(bool, IsInitialized, (), (const, override));
    MOCK_METHOD(int32_t, GetCurrentUserId, (), (override));
    MOCK_METHOD(int32_t, RegisterObserver, (const std::string&, const DataUpdateFunc&, int32_t userId), (override));
    MOCK_METHOD(int32_t, UnregisterObserver, (const std::string&, int32_t), (override));
    MOCK_METHOD(int32_t, GetStringValue, (const std::string&, std::string&, int32_t), (const, override));
    MOCK_METHOD(int32_t, GetInt32ValueStrictly, (const std::string&, int32_t&, int32_t), (const, override));
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_SETTING_DATA_MANAGER_H
