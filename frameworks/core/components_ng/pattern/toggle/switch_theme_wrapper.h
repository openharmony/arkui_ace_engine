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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TOGGLE_SWITCH_THEME_WRAPPER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TOGGLE_SWITCH_THEME_WRAPPER_H

#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

class SwitchThemeWrapper : public SwitchTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(SwitchThemeWrapper, SwitchTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto themeWrapper = AceType::MakeRefPtr<SwitchThemeWrapper>();
            auto theme = AceType::DynamicCast<SwitchTheme>(themeWrapper);
            if (!themeConstants) {
                return themeWrapper;
            }
            ParsePattern(themeConstants, theme);
            return themeWrapper;
        }
    };

    ~SwitchThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (auto colors = theme.Colors(); colors) {
            pointColor_ = colors->CompBackgroundPrimaryContrary();
            activeColor_ = colors->CompBackgroundEmphasize();
        }
    }

protected:
    SwitchThemeWrapper() = default;
};

} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TOGGLE_SWITCH_THEME_WRAPPER_H