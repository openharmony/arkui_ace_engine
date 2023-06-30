/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_APP_BAR_MOCK_THEME_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_APP_BAR_MOCK_THEME_MANAGER_H

#include "gmock/gmock.h"

#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/pattern/app_bar/app_bar_theme.h"

namespace OHOS::Ace {
class MockThemeManager : public ThemeManager {
    DECLARE_ACE_TYPE(MockThemeManager, ThemeManager);

public:
    MockThemeManager() = default;
    ~MockThemeManager() override = default;

    RefPtr<Theme> GetTheme(ThemeType type) override
    {
        auto theme = AceType::MakeRefPtr<NG::AppBarTheme>();
        return theme;
    };
    MOCK_METHOD(Color, GetBackgroundColor, (), (const));
    RefPtr<ThemeConstants> GetThemeConstants() const override
    {
        auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);
        return themeConstants;
    };
    MOCK_METHOD(RefPtr<ThemeConstants>, GetThemeConstants,
        (const std::string& bundleName, const std::string& moduleName), (const));
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_APP_BAR_MOCK_THEME_MANAGER_H
