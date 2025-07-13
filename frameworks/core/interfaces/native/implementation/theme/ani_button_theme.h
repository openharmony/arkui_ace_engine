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

#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/button/button_model.h"
#include "core/interfaces/native/ani/ani_theme.h"
#include "core/interfaces/native/implementation/theme/ani_theme_utils.h"

namespace OHOS::Ace::NG {
class AniButtonTheme {
public:
    static bool ApplyTheme(const ButtonRole& role, const ButtonStyleMode& styleMode, bool isLabelButton)
    {
        AniButtonTheme::buttonRole = role;
        AniButtonTheme::buttonStyleMode = styleMode;
        return AniButtonTheme::ApplyTheme(isLabelButton);
    }
    static bool ApplyTheme(const ButtonRole& role, bool isLabelButton)
    {
        AniButtonTheme::buttonRole = role;
        return AniButtonTheme::ApplyTheme(isLabelButton);
    }
    static bool ApplyTheme(const ButtonStyleMode& styleMode, bool isLabelButton)
    {
        AniButtonTheme::buttonStyleMode = styleMode;
        return AniButtonTheme::ApplyTheme(isLabelButton);
    }
private:
    // last button role value
    inline static ButtonRole buttonRole = ButtonRole::NORMAL;
    // last button style mode value
    inline static ButtonStyleMode buttonStyleMode = ButtonStyleMode::EMPHASIZE;

    static bool ApplyTheme(bool isLabelButton)
    {
        auto themeColors = AniThemeUtils::GetThemeColors();
        if (!themeColors) {
            // no need to apply custom theme colors
            return false;
        }

        // normal
        ViewStackModel::GetInstance()->SetVisualState(VisualState::NORMAL);
        if (isLabelButton) {
            LOGI("FZY ButtonTheme ApplyTheme FontColor %{public}s",
                AniButtonTheme::FontColor(themeColors).ToString().c_str());
            ButtonModel::GetInstance()->SetFontColor(AniButtonTheme::FontColor(themeColors));
        }
        ButtonModel::GetInstance()->BackgroundColor(AniButtonTheme::BackgroundColor(themeColors, false), true);

        // clear state
        ViewStackModel::GetInstance()->ClearVisualState();
        return true;
    }

    static Color FontColor(const RefPtr<AniThemeColors>& themeColors)
    {
        switch (AniButtonTheme::buttonStyleMode) {
            case ButtonStyleMode::NORMAL:
            case ButtonStyleMode::TEXT:
                if (AniButtonTheme::buttonRole == ButtonRole::ERROR) {
                    return themeColors->FontPrimary();
                }
                return themeColors->FontPrimary();
            case ButtonStyleMode::EMPHASIZE:
            default:
                return themeColors->FontPrimary();
        }
    }

    static Color BackgroundColor(const RefPtr<AniThemeColors>& themeColors, bool isPressed)
    {
        switch (AniButtonTheme::buttonStyleMode) {
            case ButtonStyleMode::TEXT:
                return Color::TRANSPARENT;
            case ButtonStyleMode::NORMAL:
                return themeColors->CompBackgroundTertiary();
            case ButtonStyleMode::EMPHASIZE:
            default:
                if (AniButtonTheme::buttonRole == ButtonRole::ERROR) {
                    return themeColors->Warning();
                }
                return themeColors->BackgroundEmphasize();
        }
    }
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_BUTTON_THEME_H
