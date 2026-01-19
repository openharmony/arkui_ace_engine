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

#ifndef FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_ANI_THEME_H
#define FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_ANI_THEME_H

#include <cstdint>
#include <optional>
#include <vector>
#include <map>

#include "ui/base/referenced.h"
#include "ui/properties/color.h"
#include "core/interfaces/ani/ani_api.h"

namespace OHOS::Ace::NG {
enum class AniThemeColorIdentifier : int32_t {
    BRAND = 0,
    WARNING = 1,
    ALERT = 2,
    CONFIRM = 3,
    FONT_PRIMARY = 4,
    FONT_SECONDARY = 5,
    FONT_TERTIARY = 6,
    FONT_FOURTH = 7,
    FONT_EMPHASIZE = 8,
    FONT_ON_PRIMARY = 9,
    FONT_ON_SECONDARY = 10,
    FONT_ON_TERTIARY = 11,
    FONT_ON_FOURTH = 12,
    ICON_PRIMARY = 13,
    ICON_SECONDARY = 14,
    ICON_TERTIARY = 15,
    ICON_FOURTH = 16,
    ICON_EMPHASIZE = 17,
    ICON_SUB_EMPHASIZE = 18,
    ICON_ON_PRIMARY = 19,
    ICON_ON_SECONDARY = 20,
    ICON_ON_TERTIARY = 21,
    ICON_ON_FOURTH = 22,
    BACKGROUND_PRIMARY = 23,
    BACKGROUND_SECONDARY = 24,
    BACKGROUND_TERTIARY = 25,
    BACKGROUND_FOURTH = 26,
    BACKGROUND_EMPHASIZE = 27,
    COMP_FOREGROUND_PRIMARY = 28,
    COMP_BACKGROUND_PRIMARY = 29,
    COMP_BACKGROUND_PRIMARY_TRAN = 30,
    COMP_BACKGROUND_PRIMARY_CONTRARY = 31,
    COMP_BACKGROUND_GRAY = 32,
    COMP_BACKGROUND_SECONDARY = 33,
    COMP_BACKGROUND_TERTIARY = 34,
    COMP_BACKGROUND_EMPHASIZE = 35,
    COMP_BACKGROUND_NEUTRAL = 36,
    COMP_EMPHASIZE_SECONDARY = 37,
    COMP_EMPHASIZE_TERTIARY = 38,
    COMP_DIVIDER = 39,
    COMP_COMMON_CONTRARY = 40,
    COMP_BACKGROUND_FOCUS = 41,
    COMP_FOCUSED_PRIMARY = 42,
    COMP_FOCUSED_SECONDARY = 43,
    COMP_FOCUSED_TERTIARY = 44,
    INTERACTIVE_HOVER = 45,
    INTERACTIVE_PRESSED = 46,
    INTERACTIVE_FOCUS = 47,
    INTERACTIVE_ACTIVE = 48,
    INTERACTIVE_SELECT = 49,
    INTERACTIVE_CLICK = 50,
};
class AniThemeColors : public Referenced {
public:
    AniThemeColors() = default;
    virtual ~AniThemeColors() = default;

    void SetColors(const std::vector<Ark_ResourceColor>& colors)
    {
        colors_ = colors;
    }

    Color Brand() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::BRAND);
    }
    Color Warning() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::WARNING);
    }
    Color Alert() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::ALERT);
    }
    Color Confirm() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::CONFIRM);
    }

    Color FontPrimary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::FONT_PRIMARY);
    }
    Color FontSecondary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::FONT_SECONDARY);
    }
    Color FontTertiary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::FONT_TERTIARY);
    }
    Color FontFourth() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::FONT_FOURTH);
    }
    Color FontEmphasize() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::FONT_EMPHASIZE);
    }

    Color FontOnPrimary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::FONT_ON_PRIMARY);
    }
    Color FontOnSecondary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::FONT_ON_SECONDARY);
    }
    Color FontOnTertiary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::FONT_ON_TERTIARY);
    }
    Color FontOnFourth() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::FONT_ON_FOURTH);
    }

    Color IconPrimary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::ICON_PRIMARY);
    }
    Color IconSecondary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::ICON_SECONDARY);
    }
    Color IconTertiary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::ICON_TERTIARY);
    }
    Color IconFourth() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::ICON_FOURTH);
    }
    Color IconEmphasize() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::ICON_EMPHASIZE);
    }
    Color IconSubEmphasize() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::ICON_SUB_EMPHASIZE);
    }

    Color IconOnPrimary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::ICON_ON_PRIMARY);
    }
    Color IconOnSecondary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::ICON_ON_SECONDARY);
    }
    Color IconOnTertiary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::ICON_ON_TERTIARY);
    }
    Color IconOnFourth() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::ICON_ON_FOURTH);
    }

    Color BackgroundPrimary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::BACKGROUND_PRIMARY);
    }
    Color BackgroundSecondary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::BACKGROUND_SECONDARY);
    }
    Color BackgroundTertiary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::BACKGROUND_TERTIARY);
    }
    Color BackgroundFourth() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::BACKGROUND_FOURTH);
    }
    Color BackgroundEmphasize() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::BACKGROUND_EMPHASIZE);
    }

    Color CompForegroundPrimary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::COMP_FOREGROUND_PRIMARY);
    }
    Color CompBackgroundPrimary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::COMP_BACKGROUND_PRIMARY);
    }
    Color CompBackgroundPrimaryTran() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::COMP_BACKGROUND_PRIMARY_TRAN);
    }
    Color CompBackgroundPrimaryContrary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::COMP_BACKGROUND_PRIMARY_CONTRARY);
    }
    Color CompBackgroundGray() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::COMP_BACKGROUND_GRAY);
    }
    Color CompBackgroundSecondary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::COMP_BACKGROUND_SECONDARY);
    }
    Color CompBackgroundTertiary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::COMP_BACKGROUND_TERTIARY);
    }
    Color CompBackgroundEmphasize() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::COMP_BACKGROUND_EMPHASIZE);
    }
    Color CompBackgroundNeutral() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::COMP_BACKGROUND_NEUTRAL);
    }
    Color CompEmphasizeSecondary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::COMP_EMPHASIZE_SECONDARY);
    }
    Color CompEmphasizeTertiary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::COMP_EMPHASIZE_TERTIARY);
    }
    Color CompDivider() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::COMP_DIVIDER);
    }
    Color CompCommonContrary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::COMP_COMMON_CONTRARY);
    }
    Color CompBackgroundFocus() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::COMP_BACKGROUND_FOCUS);
    }
    Color CompFocusedPrimary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::COMP_FOCUSED_PRIMARY);
    }
    Color CompFocusedSecondary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::COMP_FOCUSED_SECONDARY);
    }
    Color CompFocusedTertiary() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::COMP_FOCUSED_TERTIARY);
    }

    Color InteractiveHover() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::INTERACTIVE_HOVER);
    }
    Color InteractivePressed() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::INTERACTIVE_PRESSED);
    }
    Color InteractiveFocus() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::INTERACTIVE_FOCUS);
    }
    Color InteractiveActive() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::INTERACTIVE_ACTIVE);
    }
    Color InteractiveSelect() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::INTERACTIVE_SELECT);
    }
    Color InteractiveClick() const
    {
        return ConvertAniValueToColor(AniThemeColorIdentifier::INTERACTIVE_CLICK);
    }

private:
    Color ConvertAniValueToColor(AniThemeColorIdentifier identifier) const;

    std::vector<Ark_ResourceColor> colors_;
};

class AniTheme {
public:
    AniTheme() = default;
    virtual ~AniTheme() = default;

    void SetColors(const RefPtr<AniThemeColors>& colors)
    {
        colors_ = colors;
    }
    void SetDarkColors(const RefPtr<AniThemeColors>& colors)
    {
        darkColors_ = colors;
    }

    const RefPtr<AniThemeColors>& Colors() const
    {
        return colors_;
    }
    const RefPtr<AniThemeColors>& DarkColors() const
    {
        return darkColors_;
    }

private:
    RefPtr<AniThemeColors> colors_;
    RefPtr<AniThemeColors> darkColors_;
};

class AniThemeScope {
public:
    // keeps the current theme in static optional object
    inline static std::optional<AniTheme> aniCurrentTheme = std::nullopt;
    inline static bool isCurrentThemeDefault = true;

    static const AniTheme& GetAniTheme(int32_t themeScopeId)
    {
        return aniThemes[themeScopeId];
    }

    static void AddAniTheme(int32_t themeScopeId, const AniTheme& aniTheme)
    {
        aniThemes[themeScopeId] = aniTheme;
    }

    static void RemoveAniTheme(int32_t themeScopeId)
    {
        aniThemes.erase(themeScopeId);
    }

    static bool IsAniThemeExists(int32_t themeScopeId)
    {
        auto iter = aniThemes.find(themeScopeId);
        return iter != aniThemes.end();
    }
private:
    static std::map<int32_t, AniTheme> aniThemes;
};
} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_ANI_THEME_H