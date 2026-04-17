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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUTTON_BUTTON_THEME_WRAPPER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUTTON_BUTTON_THEME_WRAPPER_H

#include "base/log/dump_log.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

class ButtonThemeWrapper : public ButtonTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(ButtonThemeWrapper, ButtonTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants> &themeConstants) const
        {
            auto themeWrapper = AceType::Claim(new ButtonThemeWrapper());
            auto theme = AceType::DynamicCast<ButtonTheme>(themeWrapper);
            if (!themeConstants) {
                return themeWrapper;
            }
            ParsePattern(themeConstants, theme);
            return themeWrapper;
        }
    };

    ~ButtonThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme &theme) override
    {
        if (auto colors = theme.Colors(); colors) {
            warningColor_ = colors->Warning();
            fontEmphasizeColor_ = colors->FontEmphasize();
            fontOnPrimaryColor_ = colors->FontOnPrimary();
            backgroundEmphasizeColor_ = colors->BackgroundEmphasize();
            compBackgroundTertiaryColor_ = colors->CompBackgroundTertiary();

            textStyle_.SetTextColor(fontOnPrimaryColor_);
        }
    }

    const Color &GetBgColor() const override
    {
        return backgroundEmphasizeColor_;
    }

    Color GetBgColor(ButtonStyleMode buttonStyle, ButtonRole buttonRole) const override
    {
        switch (buttonStyle) {
            case ButtonStyleMode::TEXT:
                return Color::TRANSPARENT;
            case ButtonStyleMode::NORMAL:
                return compBackgroundTertiaryColor_;
            case ButtonStyleMode::EMPHASIZE:
            default:
                if (buttonRole == ButtonRole::ERROR) {
                    return warningColor_;
                }
                return backgroundEmphasizeColor_;
        }
    }

    const Color &GetTextColor(ButtonStyleMode buttonStyle, ButtonRole buttonRole) const override
    {
        switch (buttonStyle) {
            case ButtonStyleMode::NORMAL:
            case ButtonStyleMode::TEXT:
                if (buttonRole == ButtonRole::ERROR) {
                    return warningColor_;
                }
                return fontEmphasizeColor_;
            case ButtonStyleMode::EMPHASIZE:
            default:
                return fontOnPrimaryColor_;
        }
    }

protected:
    ButtonThemeWrapper() = default;

private:
    Color warningColor_;
    Color fontEmphasizeColor_;
    Color fontOnPrimaryColor_;
    Color backgroundEmphasizeColor_;
    Color compBackgroundTertiaryColor_;
};

}  // namespace OHOS::Ace::NG
#endif  // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUTTON_BUTTON_THEME_WRAPPER_H
