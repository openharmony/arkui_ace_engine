/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_BASE_MOCK_SYSTEM_PROPERTIES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_BASE_MOCK_SYSTEM_PROPERTIES_H
#include "core/common/ace_application_info.h"
namespace OHOS::Ace {
namespace MockSystemProperties {
extern bool g_isSuperFoldDisplayDevice;
}
// unit test globals
extern bool g_segmentedWaterflow;
extern bool g_isNeedSymbol;
extern bool g_isResourceDecoupling;
extern bool g_isConfigChangePerform;
extern bool g_isMultiInstanceEnabled;

class APIVersionGuard final {
public:
    explicit APIVersionGuard(int32_t apiVersion)
    {
        backupApiVersion_ = AceApplicationInfo::GetInstance().GetApiTargetVersion();
        AceApplicationInfo::GetInstance().SetApiTargetVersion(apiVersion);
    }

    ~APIVersionGuard()
    {
        AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion_);
    }

private:
    int32_t backupApiVersion_ = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_BASE_MOCK_SYSTEM_PROPERTIES_H
