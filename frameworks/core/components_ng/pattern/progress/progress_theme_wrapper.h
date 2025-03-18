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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_THEME_WRAPPER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_THEME_WRAPPER_H

#include <memory>

#include "base/memory/ace_type.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

/**
 * ProgressThemeWrapper defines colors and styles for Progress and LoadingProgress components
 * basing on TokenTheme's data.
 * ProgressThemeWrapper should be built using ProgressThemeWrapper::WrapperBuilder.
 */
class ProgressThemeWrapper : public ProgressTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(ProgressThemeWrapper, ProgressTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() override = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto wrapper = AceType::Claim(new ProgressThemeWrapper());
            ParsePattern(themeConstants, AceType::DynamicCast<ProgressTheme>(wrapper));
            return wrapper;
        }
    };

    ~ProgressThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (auto themeColors = theme.Colors(); themeColors) {
            // update only required attributes by TokenTheme tokens
            loadingColor_ = themeColors->IconSecondary();

            capsuleBgColor_ = themeColors->CompBackgroundTertiary();
            ringProgressBackgroundColor_ = themeColors->CompBackgroundTertiary();
            trackBgColor_ = themeColors->CompBackgroundTertiary();

            capsuleSelectColor_ = themeColors->CompEmphasizeSecondary();
            trackSelectedColor_ = themeColors->BackgroundEmphasize();
            borderColor_ = themeColors->CompEmphasizeSecondary();
        }
    }

protected:
    ProgressThemeWrapper() = default;
};

} // namespace
#endif
