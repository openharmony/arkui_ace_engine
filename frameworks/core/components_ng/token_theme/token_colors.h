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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_TOKEN_THEME_TOKEN_COLORS_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_TOKEN_THEME_TOKEN_COLORS_H

#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"

namespace OHOS::Ace::NG {

class TokenColors : public virtual AceType {
    DECLARE_ACE_TYPE(TokenColors, AceType);

    struct TokenColorData {
        const char* colorName;
        const int32_t systemResourceId;
    };

public:
    static constexpr int32_t BRAND = 0;
    static constexpr int32_t WARNING = 1;
    static constexpr int32_t ALERT = 2;
    static constexpr int32_t CONFIRM = 3;

    static constexpr int32_t FONT_PRIMARY = 4;
    static constexpr int32_t FONT_SECONDARY = 5;
    static constexpr int32_t FONT_TERTIARY = 6;
    static constexpr int32_t FONT_FOURTH = 7;
    static constexpr int32_t FONT_EMPHASIZE = 8;

    static constexpr int32_t FONT_ON_PRIMARY = 9;
    static constexpr int32_t FONT_ON_SECONDARY = 10;
    static constexpr int32_t FONT_ON_TERTIARY = 11;
    static constexpr int32_t FONT_ON_FOURTH = 12;

    static constexpr int32_t ICON_PRIMARY = 13;
    static constexpr int32_t ICON_SECONDARY = 14;
    static constexpr int32_t ICON_TERTIARY = 15;
    static constexpr int32_t ICON_FOURTH = 16;
    static constexpr int32_t ICON_EMPHASIZE = 17;
    static constexpr int32_t ICON_SUB_EMPHASIZE = 18;

    static constexpr int32_t ICON_ON_PRIMARY = 19;
    static constexpr int32_t ICON_ON_SECONDARY = 20;
    static constexpr int32_t ICON_ON_TERTIARY = 21;
    static constexpr int32_t ICON_ON_FOURTH = 22;

    static constexpr int32_t BACKGROUND_PRIMARY = 23;
    static constexpr int32_t BACKGROUND_SECONDARY = 24;
    static constexpr int32_t BACKGROUND_TERTIARY = 25;
    static constexpr int32_t BACKGROUND_FOURTH = 26;
    static constexpr int32_t BACKGROUND_EMPHASIZE = 27;

    static constexpr int32_t COMP_FOREGROUND_PRIMARY = 28;
    static constexpr int32_t COMP_BACKGROUND_PRIMARY = 29;
    static constexpr int32_t COMP_BACKGROUND_PRIMARY_TRAN = 30;
    static constexpr int32_t COMP_BACKGROUND_PRIMARY_CONTRARY = 31;
    static constexpr int32_t COMP_BACKGROUND_GRAY = 32;
    static constexpr int32_t COMP_BACKGROUND_SECONDARY = 33;
    static constexpr int32_t COMP_BACKGROUND_TERTIARY = 34;
    static constexpr int32_t COMP_BACKGROUND_EMPHASIZE = 35;
    static constexpr int32_t COMP_BACKGROUND_NEUTRAL = 36;
    static constexpr int32_t COMP_EMPHASIZE_SECONDARY = 37;
    static constexpr int32_t COMP_EMPHASIZE_TERTIARY = 38;
    static constexpr int32_t COMP_DIVIDER = 39;
    static constexpr int32_t COMP_COMMON_CONTRARY = 40;
    static constexpr int32_t COMP_BACKGROUND_FOCUS = 41;
    static constexpr int32_t COMP_FOCUSED_PRIMARY = 42;
    static constexpr int32_t COMP_FOCUSED_SECONDARY = 43;
    static constexpr int32_t COMP_FOCUSED_TERTIARY = 44;

    static constexpr int32_t INTERACTIVE_HOVER = 45;
    static constexpr int32_t INTERACTIVE_PRESSED = 46;
    static constexpr int32_t INTERACTIVE_FOCUS = 47;
    static constexpr int32_t INTERACTIVE_ACTIVE = 48;
    static constexpr int32_t INTERACTIVE_SELECT = 49;
    static constexpr int32_t INTERACTIVE_CLICK = 50;
    static constexpr int32_t TOTAL_NUMBER = 51;

    TokenColors() = default;
    virtual ~TokenColors() = default;

    void SetColors(const std::vector<Color>& colors)
    {
        colors_ = colors;
    }

    Color Brand() const
    {
        return colors_[BRAND];
    }
    Color Warning() const
    {
        return colors_[WARNING];
    }
    Color Alert() const
    {
        return colors_[ALERT];
    }
    Color Confirm() const
    {
        return colors_[CONFIRM];
    }

    Color FontPrimary() const
    {
        return colors_[FONT_PRIMARY];
    }
    Color FontSecondary() const
    {
        return colors_[FONT_SECONDARY];
    }
    Color FontTertiary() const
    {
        return colors_[FONT_TERTIARY];
    }
    Color FontFourth() const
    {
        return colors_[FONT_FOURTH];
    }
    Color FontEmphasize() const
    {
        return colors_[FONT_EMPHASIZE];
    }

    Color FontOnPrimary() const
    {
        return colors_[FONT_ON_PRIMARY];
    }
    Color FontOnSecondary() const
    {
        return colors_[FONT_ON_SECONDARY];
    }
    Color FontOnTertiary() const
    {
        return colors_[FONT_ON_TERTIARY];
    }
    Color FontOnFourth() const
    {
        return colors_[FONT_ON_FOURTH];
    }

    Color IconPrimary() const
    {
        return colors_[ICON_PRIMARY];
    }
    Color IconSecondary() const
    {
        return colors_[ICON_SECONDARY];
    }
    Color IconTertiary() const
    {
        return colors_[ICON_TERTIARY];
    }
    Color IconFourth() const
    {
        return colors_[ICON_FOURTH];
    }
    Color IconEmphasize() const
    {
        return colors_[ICON_EMPHASIZE];
    }
    Color IconSubEmphasize() const
    {
        return colors_[ICON_SUB_EMPHASIZE];
    }

    Color IconOnPrimary() const
    {
        return colors_[ICON_ON_PRIMARY];
    }
    Color IconOnSecondary() const
    {
        return colors_[ICON_ON_SECONDARY];
    }
    Color IconOnTertiary() const
    {
        return colors_[ICON_ON_TERTIARY];
    }
    Color IconOnFourth() const
    {
        return colors_[ICON_ON_FOURTH];
    }

    Color BackgroundPrimary() const
    {
        return colors_[BACKGROUND_PRIMARY];
    }
    Color BackgroundSecondary() const
    {
        return colors_[BACKGROUND_SECONDARY];
    }
    Color BackgroundTertiary() const
    {
        return colors_[BACKGROUND_TERTIARY];
    }
    Color BackgroundFourth() const
    {
        return colors_[BACKGROUND_FOURTH];
    }
    Color BackgroundEmphasize() const
    {
        return colors_[BACKGROUND_EMPHASIZE];
    }

    Color CompForegroundPrimary() const
    {
        return colors_[COMP_FOREGROUND_PRIMARY];
    }
    Color CompBackgroundPrimary() const
    {
        return colors_[COMP_BACKGROUND_PRIMARY];
    }
    Color CompBackgroundPrimaryTran() const
    {
        return colors_[COMP_BACKGROUND_PRIMARY_TRAN];
    }
    Color CompBackgroundPrimaryContrary() const
    {
        return colors_[COMP_BACKGROUND_PRIMARY_CONTRARY];
    }
    Color CompBackgroundGray() const
    {
        return colors_[COMP_BACKGROUND_GRAY];
    }
    Color CompBackgroundSecondary() const
    {
        return colors_[COMP_BACKGROUND_SECONDARY];
    }
    Color CompBackgroundTertiary() const
    {
        return colors_[COMP_BACKGROUND_TERTIARY];
    }
    Color CompBackgroundEmphasize() const
    {
        return colors_[COMP_BACKGROUND_EMPHASIZE];
    }
    Color CompBackgroundNeutral() const
    {
        return colors_[COMP_BACKGROUND_NEUTRAL];
    }
    Color CompEmphasizeSecondary() const
    {
        return colors_[COMP_EMPHASIZE_SECONDARY];
    }
    Color CompEmphasizeTertiary() const
    {
        return colors_[COMP_EMPHASIZE_TERTIARY];
    }
    Color CompDivider() const
    {
        return colors_[COMP_DIVIDER];
    }
    Color CompCommonContrary() const
    {
        return colors_[COMP_COMMON_CONTRARY];
    }
    Color CompBackgroundFocus() const
    {
        return colors_[COMP_BACKGROUND_FOCUS];
    }
    Color CompFocusedPrimary() const
    {
        return colors_[COMP_FOCUSED_PRIMARY];
    }
    Color CompFocusedSecondary() const
    {
        return colors_[COMP_FOCUSED_SECONDARY];
    }
    Color CompFocusedTertiary() const
    {
        return colors_[COMP_FOCUSED_TERTIARY];
    }

    Color InteractiveHover() const
    {
        return colors_[INTERACTIVE_HOVER];
    }
    Color InteractivePressed() const
    {
        return colors_[INTERACTIVE_PRESSED];
    }
    Color InteractiveFocus() const
    {
        return colors_[INTERACTIVE_FOCUS];
    }
    Color InteractiveActive() const
    {
        return colors_[INTERACTIVE_ACTIVE];
    }
    Color InteractiveSelect() const
    {
        return colors_[INTERACTIVE_SELECT];
    }
    Color InteractiveClick() const
    {
        return colors_[INTERACTIVE_CLICK];
    }
    static const char* GetColorNameByIndex(int32_t idx)
    {
        return GetTokenColorDataByIndex(idx).colorName;
    }

    static int32_t GetSystemColorResIdByIndex(int32_t idx)
    {
        return GetTokenColorDataByIndex(idx).systemResourceId;
    }

    inline Color GetByIndex(int32_t idx)
    {
        return colors_[idx];
    }

    static const TokenColorData& GetTokenColorDataByIndex(int32_t idx)
    {
        static const std::vector<TokenColorData> colorData = {
            { /* BRAND = 0 */                               "brand",                            125830976 },
            { /* WARNING = 1; */                            "warning",                          125830979 },
            { /* ALERT = 2 */                               "alert",                            125830980 },
            { /* CONFIRM = 3 */                             "confirm",                          125830981 },

            { /* FONT_PRIMARY = 4 */                        "fontPrimary",                      125830982 },
            { /* FONT_SECONDARY = 5 */                      "fontSecondary",                    125830983 },
            { /* FONT_TERTIARY = 6 */                       "fontTertiary",                     125830984 },
            { /* FONT_FOURTH = 7 */                         "fontFourth",                       125830985 },
            { /* FONT_EMPHASIZE = 8 */                      "fontEmphasize",                    125830986 },

            { /* FONT_ON_PRIMARY = 9 */                     "fontOnPrimary",                    125830987 },
            { /* FONT_ON_SECONDARY = 10 */                  "fontOnSecondary",                  125830988 },
            { /* FONT_ON_TERTIARY = 11 */                   "fontOnTertiary",                   125830989 },
            { /* FONT_ON_FOURTH = 12 */                     "fontOnFourth",                     125830990 },

            { /* ICON_PRIMARY = 13 */                       "iconPrimary",                      125830991 },
            { /* ICON_SECONDARY = 14 */                     "iconSecondary",                    125830992 },
            { /* ICON_TERTIARY = 15 */                      "iconTertiary",                     125830993 },
            { /* ICON_FOURTH = 16 */                        "iconFourth",                       125830994 },
            { /* ICON_EMPHASIZE = 17 */                     "iconEmphasize",                    125830995 },
            { /* ICON_SUB_EMPHASIZE = 18 */                 "iconSubEmphasize",                 125830996 },

            { /* ICON_ON_PRIMARY = 19 */                    "iconOnPrimary",                    125831057 },
            { /* ICON_ON_SECONDARY = 20 */                  "iconOnSecondary",                  125831058 },
            { /* ICON_ON_TERTIARY = 21 */                   "iconOnTertiary",                   125831059 },
            { /* ICON_ON_FOURTH = 22 */                     "iconOnFourth",                     125831060 },

            { /* BACKGROUND_PRIMARY = 23 */                 "backgroundPrimary",                125831061 },
            { /* BACKGROUND_SECONDARY = 24 */               "backgroundSecondary",              125831062 },
            { /* BACKGROUND_TERTIARY = 25 */                "backgroundTertiary",               125831063 },
            { /* BACKGROUND_FOURTH = 26 */                  "backgroundFourth",                 125831064 },
            { /* BACKGROUND_EMPHASIZE = 27 */               "backgroundEmphasize",              125831065 },

            { /* COMP_FOREGROUND_PRIMARY = 28 */            "compForegroundPrimary",            125831003 },
            { /* COMP_BACKGROUND_PRIMARY = 29 */            "compBackgroundPrimary",            125831004 },
            { /* COMP_BACKGROUND_PRIMARY_TRAN = 30 */       "compBackgroundPrimaryTran",        -1 }, // not defined
            { /* COMP_BACKGROUND_PRIMARY_CONTRARY = 31 */   "compBackgroundPrimaryContrary",    125831005 },
            { /* COMP_BACKGROUND_GRAY = 32 */               "compBackgroundGray",               125831006 },
            { /* COMP_BACKGROUND_SECONDARY = 33 */          "compBackgroundSecondary",          125831007 },
            { /* COMP_BACKGROUND_TERTIARY = 34 */           "compBackgroundTertiary",           125831008 },
            { /* COMP_BACKGROUND_EMPHASIZE = 35 */          "compBackgroundEmphasize",          125831009 },
            { /* COMP_BACKGROUND_NEUTRAL = 36 */            "compBackgroundNeutral",            125831066 },
            { /* COMP_EMPHASIZE_SECONDARY = 37 */           "compEmphasizeSecondary",           125831011 },
            { /* COMP_EMPHASIZE_TERTIARY = 38 */            "compEmphasizeTertiary",            125831012 },
            { /* COMP_DIVIDER = 39 */                       "compDivider",                      125831013 },
            { /* COMP_COMMON_CONTRARY = 40 */               "compCommonContrary",               125831014 },
            { /* COMP_BACKGROUND_FOCUS = 41 */              "compBackgroundFocus",              125831015 },
            { /* COMP_FOCUSED_PRIMARY = 42 */               "compFocusedPrimary",               125831016 },
            { /* COMP_FOCUSED_SECONDARY = 43 */             "compFocusedSecondary",             125831017 },
            { /* COMP_FOCUSED_TERTIARY = 44 */              "compFocusedTertiary",              125831018 },

            { /* INTERACTIVE_HOVER = 45 */                  "interactiveHover",                 125831019 },
            { /* INTERACTIVE_PRESSED = 46 */                "interactivePressed",               125831020 },
            { /* INTERACTIVE_FOCUS = 47 */                  "interactiveFocus",                 125831021 },
            { /* INTERACTIVE_ACTIVE = 48 */                 "interactiveActive",                125831022 },
            { /* INTERACTIVE_SELECT = 49 */                 "interactiveSelect",                125831023 },
            { /* INTERACTIVE_CLICK = 50 */                  "interactiveClick",                 125831024 },

            { /* TOTAL_NUMBER = 51; */                      nullptr,                            -1        }
        };
        return (idx >= 0 && idx < TokenColors::TOTAL_NUMBER) ? colorData[idx] : colorData[TokenColors::TOTAL_NUMBER];
    }

private:
    std::vector<Color> colors_;
};

} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_CORE_COMPONENTS_NG_TOKEN_THEME_TOKEN_COLORS_H
