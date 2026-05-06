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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_THEME_WRAPPER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_THEME_WRAPPER_H

#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

class TabThemeWrapper : public TabTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(TabThemeWrapper, TabTheme, TokenThemeWrapper);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto themeWrapper = AceType::MakeRefPtr<TabThemeWrapper>();
            auto theme = AceType::DynamicCast<TabTheme>(themeWrapper);
            if (!themeConstants) {
                return themeWrapper;
            }
            ParsePattern(themeConstants, theme);
            return themeWrapper;
        }
    };

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (auto colors = theme.Colors(); colors) {
            subTabTextOnColor_ = colors->FontEmphasize();
            subTabTextOffColor_ = colors->FontSecondary();
            subTabBarHoverColor_ = colors->InteractiveHover();
            subTabBarPressedColor_ = colors->InteractiveClick();
            bottomTabTextOn_ = colors->FontEmphasize();
            bottomTabTextOff_ = colors->FontSecondary();
            dividerColor_ = colors->CompDivider();

            activeIndicatorColor_ = colors->CompBackgroundEmphasize();
            bottomTabIconOn_ = colors->IconEmphasize();
            bottomTabIconOff_ = colors->IconFourth();
            bottomTabSymbolOff_ = colors->IconTertiary();
        }
    }

protected:
    TabThemeWrapper() = default;
};

} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_THEME_WRAPPER_H