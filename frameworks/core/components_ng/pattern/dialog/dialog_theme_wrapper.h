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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_DIALOG_THEME_WRAPPER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_DIALOG_THEME_WRAPPER_H

#include <memory>

#include "base/memory/ace_type.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

/**
 * DialogThemeWrapper defines color and styles of DialogComponent basing on TokenTheme's data.
 * DialogThemeWrapper should be built using DialogThemeWrapper::Builder.
 */
class DialogThemeWrapper : public DialogTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(DialogThemeWrapper, DialogTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() override = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto wrapper = AceType::MakeRefPtr<DialogThemeWrapper>();
            auto theme = AceType::DynamicCast<DialogTheme>(wrapper);
            if (!themeConstants) {
                return wrapper;
            }
            ParseNewPattern(themeConstants, theme);
            ParsePattern(themeConstants, theme);
            return wrapper;
        }
    };

    ~DialogThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (const auto& colors = theme.Colors(); colors) {
            backgroundColor_ = colors->CompBackgroundPrimary();
            titleTextStyle_.SetTextColor(colors->FontPrimary());
            subtitleTextStyle_.SetTextColor(colors->FontSecondary());
            contentTextStyle_.SetTextColor(colors->FontPrimary());
            buttonBackgroundColor_ = colors->CompBackgroundPrimary();
            buttonClickedColor_ = colors->InteractiveClick();
            commonButtonBgColor_ = colors->CompBackgroundTertiary();
            emphasizeButtonBgColor_ = colors->Warning();
            emphasizeButtonTextColor_ = colors->CompBackgroundPrimaryContrary();
            buttonDefaultFontColor_ = colors->FontEmphasize();
            buttonHighlightBgColor_ = colors->CompBackgroundEmphasize();
            buttonHighlightFontColor_ = colors->CompBackgroundPrimaryContrary();
            dividerColor_ = colors->CompDivider();
        }
    }

protected:
    DialogThemeWrapper() = default;
};

} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_DIALOG_THEME_WRAPPER_H
