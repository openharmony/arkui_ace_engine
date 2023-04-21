/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_PICKER_THEME_MOCK_THEME_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_PICKER_THEME_MOCK_THEME_MANAGER_H

#include "gmock/gmock.h"

#include "core/components/dialog/dialog_theme.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components/theme/theme_manager.h"

namespace OHOS::Ace {
class MockPickerThemeManager : public ThemeManager {
    DECLARE_ACE_TYPE(MockPickerThemeManager, ThemeManager);

public:
    MockPickerThemeManager() = default;
    ~MockPickerThemeManager() override = default;
    RefPtr<Theme> GetTheme(ThemeType type) override
    {
        auto themeConstants_ = AceType::MakeRefPtr<ThemeConstants>(nullptr);
        if (type == PickerTheme::TypeId()) {
            return (PickerTheme::Builder().Build(themeConstants_));
        } else if (type == DialogTheme::TypeId()) {
            return (DialogTheme::Builder().Build(themeConstants_));
        } else if (type == IconTheme::TypeId()) {
            return (IconTheme::Builder().Build(themeConstants_));
        }
        return nullptr;
    }
    MOCK_CONST_METHOD0(GetBackgroundColor, Color());
    MOCK_CONST_METHOD0(GetThemeConstants, RefPtr<ThemeConstants>());
    MOCK_CONST_METHOD2(
        GetThemeConstants, RefPtr<ThemeConstants>(const std::string& bundleName, const std::string& moduleName));
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_PICKER_THEME_MOCK_THEME_MANAGER_H
