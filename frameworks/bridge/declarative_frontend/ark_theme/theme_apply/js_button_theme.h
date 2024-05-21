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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_BUTTON_THEME_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_BUTTON_THEME_H

#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/button/button_model.h"

namespace OHOS::Ace::Framework {
class JSButtonTheme {
public:
    static bool ApplyTheme(const ButtonRole& role, const ButtonStyleMode& styleMode, bool isLabelButton)
    {
        JSButtonTheme::buttonRole = role;
        JSButtonTheme::buttonStyleMode = styleMode;
        return JSButtonTheme::ApplyTheme(isLabelButton);
    }
    static bool ApplyTheme(const ButtonRole& role, bool isLabelButton)
    {
        JSButtonTheme::buttonRole = role;
        return JSButtonTheme::ApplyTheme(isLabelButton);
    }
    static bool ApplyTheme(const ButtonStyleMode& styleMode, bool isLabelButton)
    {
        JSButtonTheme::buttonStyleMode = styleMode;
        return JSButtonTheme::ApplyTheme(isLabelButton);
    }
private:
    // last button role value
    inline static ButtonRole buttonRole = ButtonRole::NORMAL;
    // last button style mode value
    inline static ButtonStyleMode buttonStyleMode = ButtonStyleMode::EMPHASIZE;

    static bool ApplyTheme(bool isLabelButton)
    {
        auto themeColors = JSThemeUtils::GetThemeColors();
        if (!themeColors) {
            // no need to apply custom theme colors
            return false;
        }

        // normal
        ViewStackModel::GetInstance()->SetVisualState(VisualState::NORMAL);
        if (isLabelButton) {
            ButtonModel::GetInstance()->SetFontColor(JSButtonTheme::FontColor(themeColors));
        }
        ButtonModel::GetInstance()->BackgroundColor(JSButtonTheme::BackgroundColor(themeColors, false), true);

        // clear state
        ViewStackModel::GetInstance()->ClearVisualState();
        return true;
    }

    static Color FontColor(const std::optional<JSThemeColors>& themeColors)
    {
        switch (JSButtonTheme::buttonStyleMode) {
            case ButtonStyleMode::NORMAL:
            case ButtonStyleMode::TEXT:
                if (JSButtonTheme::buttonRole == ButtonRole::ERROR) {
                    return themeColors->Warning();
                }
                return themeColors->FontEmphasize();
            case ButtonStyleMode::EMPHASIZE:
            default:
                return themeColors->FontOnPrimary();
        }
    }

    static Color BackgroundColor(const std::optional<JSThemeColors>& themeColors, bool isPressed)
    {
        switch (JSButtonTheme::buttonStyleMode) {
            case ButtonStyleMode::TEXT:
                return Color::TRANSPARENT;
            case ButtonStyleMode::NORMAL:
                return themeColors->CompBackgroundTertiary();
            case ButtonStyleMode::EMPHASIZE:
            default:
                if (JSButtonTheme::buttonRole == ButtonRole::ERROR) {
                    return themeColors->Warning();
                }
                return themeColors->BackgroundEmphasize();
        }
    }
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_BUTTON_THEME_H
