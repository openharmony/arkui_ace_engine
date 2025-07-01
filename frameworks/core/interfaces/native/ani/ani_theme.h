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

#include "ui/properties/color.h"

#define COLORS_NUMBER (51)

#define BRAND (0)
#define WARNING (1)
#define ALERT (2)
#define CONFIRM (3)

#define FONT_PRIMARY (4)
#define FONT_SECONDARY (5)
#define FONT_TERTIARY (6)
#define FONT_FOURTH (7)
#define FONT_EMPHASIZE (8)

#define FONT_ON_PRIMARY (9)
#define FONT_ON_SECONDARY (10)
#define FONT_ON_TERTIARY (11)
#define FONT_ON_FOURTH (12)

#define ICON_PRIMARY (13)
#define ICON_SECONDARY (14)
#define ICON_TERTIARY (15)
#define ICON_FOURTH (16)
#define ICON_EMPHASIZE (17)
#define ICON_SUB_EMPHASIZE (18)

#define ICON_ON_PRIMARY (19)
#define ICON_ON_SECONDARY (20)
#define ICON_ON_TERTIARY (21)
#define ICON_ON_FOURTH (22)

#define BACKGROUND_PRIMARY (23)
#define BACKGROUND_SECONDARY (24)
#define BACKGROUND_TERTIARY (25)
#define BACKGROUND_FOURTH (26)
#define BACKGROUND_EMPHASIZE (27)

#define COMP_FOREGROUND_PRIMARY (28)
#define COMP_BACKGROUND_PRIMARY (29)
#define COMP_BACKGROUND_PRIMARY_TRAN (30)
#define COMP_BACKGROUND_PRIMARY_CONTRARY (31)
#define COMP_BACKGROUND_GRAY (32)
#define COMP_BACKGROUND_SECONDARY (33)
#define COMP_BACKGROUND_TERTIARY (34)
#define COMP_BACKGROUND_EMPHASIZE (35)
#define COMP_BACKGROUND_NEUTRAL (36)
#define COMP_EMPHASIZE_SECONDARY (37)
#define COMP_EMPHASIZE_TERTIARY (38)
#define COMP_DIVIDER (39)
#define COMP_COMMON_CONTRARY (40)
#define COMP_BACKGROUND_FOCUS (41)
#define COMP_FOCUSED_PRIMARY (42)
#define COMP_FOCUSED_SECONDARY (43)
#define COMP_FOCUSED_TERTIARY (44)

#define INTERACTIVE_HOVER (45)
#define INTERACTIVE_PRESSED (46)
#define INTERACTIVE_FOCUS (47)
#define INTERACTIVE_ACTIVE (48)
#define INTERACTIVE_SELECT (49)
#define INTERACTIVE_CLICK (50)

typedef class __ani_array* ani_array;
typedef class __ani_object* ani_object;
typedef struct __ani_env ani_env;
typedef struct __ani_vm ani_vm;

namespace OHOS::Ace::NG {
class AniThemeColors {
public:
    AniThemeColors() = default;
    virtual ~AniThemeColors() = default;

    void SetColors(ani_env* env, ani_array colors);

    Color Brand() const
    {
        return ConvertAniValueToColor(colors_[BRAND]);
    }
    Color Warning() const
    {
        return ConvertAniValueToColor(colors_[WARNING]);
    }
    Color Alert() const
    {
        return ConvertAniValueToColor(colors_[ALERT]);
    }
    Color Confirm() const
    {
        return ConvertAniValueToColor(colors_[CONFIRM]);
    }

    Color FontPrimary() const
    {
        return ConvertAniValueToColor(colors_[FONT_PRIMARY]);
    }
    Color FontSecondary() const
    {
        return ConvertAniValueToColor(colors_[FONT_SECONDARY]);
    }
    Color FontTertiary() const
    {
        return ConvertAniValueToColor(colors_[FONT_TERTIARY]);
    }
    Color FontFourth() const
    {
        return ConvertAniValueToColor(colors_[FONT_FOURTH]);
    }
    Color FontEmphasize() const
    {
        return ConvertAniValueToColor(colors_[FONT_EMPHASIZE]);
    }

    Color FontOnPrimary() const
    {
        return ConvertAniValueToColor(colors_[FONT_ON_PRIMARY]);
    }
    Color FontOnSecondary() const
    {
        return ConvertAniValueToColor(colors_[FONT_ON_SECONDARY]);
    }
    Color FontOnTertiary() const
    {
        return ConvertAniValueToColor(colors_[FONT_ON_TERTIARY]);
    }
    Color FontOnFourth() const
    {
        return ConvertAniValueToColor(colors_[FONT_ON_FOURTH]);
    }

    Color IconPrimary() const
    {
        return ConvertAniValueToColor(colors_[ICON_PRIMARY]);
    }
    Color IconSecondary() const
    {
        return ConvertAniValueToColor(colors_[ICON_SECONDARY]);
    }
    Color IconTertiary() const
    {
        return ConvertAniValueToColor(colors_[ICON_TERTIARY]);
    }
    Color IconFourth() const
    {
        return ConvertAniValueToColor(colors_[ICON_FOURTH]);
    }
    Color IconEmphasize() const
    {
        return ConvertAniValueToColor(colors_[ICON_EMPHASIZE]);
    }
    Color IconSubEmphasize() const
    {
        return ConvertAniValueToColor(colors_[ICON_SUB_EMPHASIZE]);
    }

    Color IconOnPrimary() const
    {
        return ConvertAniValueToColor(colors_[ICON_ON_PRIMARY]);
    }
    Color IconOnSecondary() const
    {
        return ConvertAniValueToColor(colors_[ICON_ON_SECONDARY]);
    }
    Color IconOnTertiary() const
    {
        return ConvertAniValueToColor(colors_[ICON_ON_TERTIARY]);
    }
    Color IconOnFourth() const
    {
        return ConvertAniValueToColor(colors_[ICON_ON_FOURTH]);
    }

    Color BackgroundPrimary() const
    {
        return ConvertAniValueToColor(colors_[BACKGROUND_PRIMARY]);
    }
    Color BackgroundSecondary() const
    {
        return ConvertAniValueToColor(colors_[BACKGROUND_SECONDARY]);
    }
    Color BackgroundTertiary() const
    {
        return ConvertAniValueToColor(colors_[BACKGROUND_TERTIARY]);
    }
    Color BackgroundFourth() const
    {
        return ConvertAniValueToColor(colors_[BACKGROUND_FOURTH]);
    }
    Color BackgroundEmphasize() const
    {
        return ConvertAniValueToColor(colors_[BACKGROUND_EMPHASIZE]);
    }

    Color CompForegroundPrimary() const
    {
        return ConvertAniValueToColor(colors_[COMP_FOREGROUND_PRIMARY]);
    }
    Color CompBackgroundPrimary() const
    {
        return ConvertAniValueToColor(colors_[COMP_BACKGROUND_PRIMARY]);
    }
    Color CompBackgroundPrimaryTran() const
    {
        return ConvertAniValueToColor(colors_[COMP_BACKGROUND_PRIMARY_TRAN]);
    }
    Color CompBackgroundPrimaryContrary() const
    {
        return ConvertAniValueToColor(colors_[COMP_BACKGROUND_PRIMARY_CONTRARY]);
    }
    Color CompBackgroundGray() const
    {
        return ConvertAniValueToColor(colors_[COMP_BACKGROUND_GRAY]);
    }
    Color CompBackgroundSecondary() const
    {
        return ConvertAniValueToColor(colors_[COMP_BACKGROUND_SECONDARY]);
    }
    Color CompBackgroundTertiary() const
    {
        return ConvertAniValueToColor(colors_[COMP_BACKGROUND_TERTIARY]);
    }
    Color CompBackgroundEmphasize() const
    {
        return ConvertAniValueToColor(colors_[COMP_BACKGROUND_EMPHASIZE]);
    }
    Color CompBackgroundNeutral() const
    {
        return ConvertAniValueToColor(colors_[COMP_BACKGROUND_NEUTRAL]);
    }
    Color CompEmphasizeSecondary() const
    {
        return ConvertAniValueToColor(colors_[COMP_EMPHASIZE_SECONDARY]);
    }
    Color CompEmphasizeTertiary() const
    {
        return ConvertAniValueToColor(colors_[COMP_EMPHASIZE_TERTIARY]);
    }
    Color CompDivider() const
    {
        return ConvertAniValueToColor(colors_[COMP_DIVIDER]);
    }
    Color CompCommonContrary() const
    {
        return ConvertAniValueToColor(colors_[COMP_COMMON_CONTRARY]);
    }
    Color CompBackgroundFocus() const
    {
        return ConvertAniValueToColor(colors_[COMP_BACKGROUND_FOCUS]);
    }
    Color CompFocusedPrimary() const
    {
        return ConvertAniValueToColor(colors_[COMP_FOCUSED_PRIMARY]);
    }
    Color CompFocusedSecondary() const
    {
        return ConvertAniValueToColor(colors_[COMP_FOCUSED_SECONDARY]);
    }
    Color CompFocusedTertiary() const
    {
        return ConvertAniValueToColor(colors_[COMP_FOCUSED_TERTIARY]);
    }

    Color InteractiveHover() const
    {
        return ConvertAniValueToColor(colors_[INTERACTIVE_HOVER]);
    }
    Color InteractivePressed() const
    {
        return ConvertAniValueToColor(colors_[INTERACTIVE_PRESSED]);
    }
    Color InteractiveFocus() const
    {
        return ConvertAniValueToColor(colors_[INTERACTIVE_FOCUS]);
    }
    Color InteractiveActive() const
    {
        return ConvertAniValueToColor(colors_[INTERACTIVE_ACTIVE]);
    }
    Color InteractiveSelect() const
    {
        return ConvertAniValueToColor(colors_[INTERACTIVE_SELECT]);
    }
    Color InteractiveClick() const
    {
        return ConvertAniValueToColor(colors_[INTERACTIVE_CLICK]);
    }

private:
    Color ConvertAniValueToColor(ani_object aniValue) const;

    std::vector<ani_object> colors_;
    ani_vm* vm_ = nullptr;
};

class AniTheme {
public:
    AniTheme() = default;
    virtual ~AniTheme() = default;

    void SetColors(const AniThemeColors& colors)
    {
        colors_ = colors;
    }

    const AniThemeColors& Colors() const
    {
        return colors_;
    }

private:
    AniThemeColors colors_;
};

class AniThemeScope {
public:
    static std::map<int32_t, AniTheme> aniThemes;
    // keeps the current theme in static optional object
    inline static std::optional<AniTheme> aniCurrentTheme = std::nullopt;
    inline static bool isCurrentThemeDefault = true;
};
} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_ANI_THEME_H