/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAV_BAR_THEME_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAV_BAR_THEME_WRAPPER_H

#include "core/components/navigation_bar/navigation_bar_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

class NavigationBarThemeWrapper : public NavigationBarTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(NavigationBarThemeWrapper, NavigationBarTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto theme = AceType::Claim(new NavigationBarThemeWrapper());
            InitTheme(theme, themeConstants);
            return theme;
        }
    };

    ~NavigationBarThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (auto colors = theme.Colors(); colors) {
            SetTitleColor(colors->FontPrimary());
            SetMainTitleFontColor(colors->FontPrimary());
            SetSubTitleColor(colors->FontSecondary());
            SetSubTitleFontColor(colors->FontSecondary());
            SetMenuIconColor(colors->IconPrimary());
            SetIconColor(colors->IconPrimary());
            SetBackButtonIconColor(colors->IconPrimary());
            SetToolbarBgColor(colors->CompBackgroundGray());
            SetToolBarDividerColor(colors->CompDivider());
            SetToolBarItemFocusColor(colors->InteractiveFocus());
            SetToolBarItemFontColor(colors->FontPrimary());
            SetToolbarIconColor(colors->IconPrimary());
            SetToolbarActiveIconColor(colors->IconEmphasize());
            SetToolBarItemActiveFontColor(colors->FontEmphasize());
            SetNavigationDividerColor(colors->CompDivider());
        }
    }

protected:
    NavigationBarThemeWrapper() = default;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAV_BAR_THEME_WRAPPER_H
