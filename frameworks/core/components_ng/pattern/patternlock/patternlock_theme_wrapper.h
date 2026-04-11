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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_THEME_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_THEME_WRAPPER_H

#include "core/components_ng/token_theme/token_theme_wrapper.h"
#include "core/components_v2/pattern_lock/pattern_lock_theme.h"

namespace OHOS::Ace::NG {

class PatternLockThemeWrapper : public V2::PatternLockTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(PatternLockThemeWrapper, V2::PatternLockTheme);

public:
    class WrapperBuilder : public V2::PatternLockTheme::Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() override = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto wrapper = AceType::MakeRefPtr<PatternLockThemeWrapper>();
            auto theme = AceType::DynamicCast<V2::PatternLockTheme>(wrapper);
            if (!themeConstants) {
                return wrapper;
            }
            SetTheme(themeConstants, theme);
            return wrapper;
        }
    };

    ~PatternLockThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (const auto& colors = theme.Colors(); colors) {
            regularColor_ = (colors->CompBackgroundNeutral());
            activeColor_ = (colors->CompBackgroundNeutral());
            selectedColor_ = (colors->CompBackgroundNeutral());
            pathColor_ = (colors->CompDivider());
            wrongColor_ = (colors->Warning());
            correctColor_ = (colors->CompBackgroundEmphasize());
            hoverColor_ = (colors->InteractiveHover());
            focusColor_ = (colors->InteractiveFocus());
        }
    }

protected:
    PatternLockThemeWrapper() = default;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_THEME_WRAPPER_H
