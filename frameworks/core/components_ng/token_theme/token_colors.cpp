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

#include "core/components_ng/token_theme/token_colors.h"

#include <vector>

namespace OHOS::Ace::NG {

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

void TokenColors::SetColors(const std::vector<Color>& colors)
{
    colors_ = colors;
}

void TokenColors::SetColor(int32_t idx, const Color& color)
{
    if (idx >= 0 && idx < colors_.size()) {
        colors_[idx] = color;
    }
}

const std::vector<Color>& TokenColors::GetColors()
{
    return colors_;
}

Color TokenColors::Brand() const
{
    return colors_[BRAND];
}

Color TokenColors::Warning() const
{
    return colors_[WARNING];
}

Color TokenColors::Alert() const
{
    return colors_[ALERT];
}

Color TokenColors::Confirm() const
{
    return colors_[CONFIRM];
}

Color TokenColors::FontPrimary() const
{
    return colors_[FONT_PRIMARY];
}

Color TokenColors::FontSecondary() const
{
    return colors_[FONT_SECONDARY];
}

Color TokenColors::FontTertiary() const
{
    return colors_[FONT_TERTIARY];
}

Color TokenColors::FontFourth() const
{
    return colors_[FONT_FOURTH];
}

Color TokenColors::FontEmphasize() const
{
    return colors_[FONT_EMPHASIZE];
}

Color TokenColors::FontOnPrimary() const
{
    return colors_[FONT_ON_PRIMARY];
}

Color TokenColors::FontOnSecondary() const
{
    return colors_[FONT_ON_SECONDARY];
}

Color TokenColors::FontOnTertiary() const
{
    return colors_[FONT_ON_TERTIARY];
}

Color TokenColors::FontOnFourth() const
{
    return colors_[FONT_ON_FOURTH];
}

Color TokenColors::IconPrimary() const
{
    return colors_[ICON_PRIMARY];
}

Color TokenColors::IconSecondary() const
{
    return colors_[ICON_SECONDARY];
}

Color TokenColors::IconTertiary() const
{
    return colors_[ICON_TERTIARY];
}

Color TokenColors::IconFourth() const
{
    return colors_[ICON_FOURTH];
}

Color TokenColors::IconEmphasize() const
{
    return colors_[ICON_EMPHASIZE];
}

Color TokenColors::IconSubEmphasize() const
{
    return colors_[ICON_SUB_EMPHASIZE];
}

Color TokenColors::IconOnPrimary() const
{
    return colors_[ICON_ON_PRIMARY];
}

Color TokenColors::IconOnSecondary() const
{
    return colors_[ICON_ON_SECONDARY];
}

Color TokenColors::IconOnTertiary() const
{
    return colors_[ICON_ON_TERTIARY];
}

Color TokenColors::IconOnFourth() const
{
    return colors_[ICON_ON_FOURTH];
}

Color TokenColors::BackgroundPrimary() const
{
    return colors_[BACKGROUND_PRIMARY];
}

Color TokenColors::BackgroundSecondary() const
{
    return colors_[BACKGROUND_SECONDARY];
}

Color TokenColors::BackgroundTertiary() const
{
    return colors_[BACKGROUND_TERTIARY];
}

Color TokenColors::BackgroundFourth() const
{
    return colors_[BACKGROUND_FOURTH];
}

Color TokenColors::BackgroundEmphasize() const
{
    return colors_[BACKGROUND_EMPHASIZE];
}

Color TokenColors::CompForegroundPrimary() const
{
    return colors_[COMP_FOREGROUND_PRIMARY];
}

Color TokenColors::CompBackgroundPrimary() const
{
    return colors_[COMP_BACKGROUND_PRIMARY];
}

Color TokenColors::CompBackgroundPrimaryTran() const
{
    return colors_[COMP_BACKGROUND_PRIMARY_TRAN];
}

Color TokenColors::CompBackgroundPrimaryContrary() const
{
    return colors_[COMP_BACKGROUND_PRIMARY_CONTRARY];
}

Color TokenColors::CompBackgroundGray() const
{
    return colors_[COMP_BACKGROUND_GRAY];
}

Color TokenColors::CompBackgroundSecondary() const
{
    return colors_[COMP_BACKGROUND_SECONDARY];
}

Color TokenColors::CompBackgroundTertiary() const
{
    return colors_[COMP_BACKGROUND_TERTIARY];
}

Color TokenColors::CompBackgroundEmphasize() const
{
    return colors_[COMP_BACKGROUND_EMPHASIZE];
}

Color TokenColors::CompBackgroundNeutral() const
{
    return colors_[COMP_BACKGROUND_NEUTRAL];
}

Color TokenColors::CompEmphasizeSecondary() const
{
    return colors_[COMP_EMPHASIZE_SECONDARY];
}

Color TokenColors::CompEmphasizeTertiary() const
{
    return colors_[COMP_EMPHASIZE_TERTIARY];
}

Color TokenColors::CompDivider() const
{
    return colors_[COMP_DIVIDER];
}

Color TokenColors::CompCommonContrary() const
{
    return colors_[COMP_COMMON_CONTRARY];
}

Color TokenColors::CompBackgroundFocus() const
{
    return colors_[COMP_BACKGROUND_FOCUS];
}

Color TokenColors::CompFocusedPrimary() const
{
    return colors_[COMP_FOCUSED_PRIMARY];
}

Color TokenColors::CompFocusedSecondary() const
{
    return colors_[COMP_FOCUSED_SECONDARY];
}

Color TokenColors::CompFocusedTertiary() const
{
    return colors_[COMP_FOCUSED_TERTIARY];
}

Color TokenColors::InteractiveHover() const
{
    return colors_[INTERACTIVE_HOVER];
}

Color TokenColors::InteractivePressed() const
{
    return colors_[INTERACTIVE_PRESSED];
}

Color TokenColors::InteractiveFocus() const
{
    return colors_[INTERACTIVE_FOCUS];
}

Color TokenColors::InteractiveActive() const
{
    return colors_[INTERACTIVE_ACTIVE];
}

Color TokenColors::InteractiveSelect() const
{
    return colors_[INTERACTIVE_SELECT];
}

Color TokenColors::InteractiveClick() const
{
    return colors_[INTERACTIVE_CLICK];
}

const char* TokenColors::GetColorNameByIndex(int32_t idx)
{
    return GetTokenColorDataByIndex(idx).colorName;
}

int32_t TokenColors::GetSystemColorResIdByIndex(int32_t idx)
{
    return GetTokenColorDataByIndex(idx).systemResourceId;
}

const TokenColorData& TokenColors::GetTokenColorDataByIndex(int32_t idx)
{
    return (idx >= 0 && idx < TokenColors::TOTAL_NUMBER) ? colorData[idx] : colorData[TokenColors::TOTAL_NUMBER];
}

Color TokenColors::GetByIndex(int32_t idx)
{
    return (idx >= 0 && idx < colors_.size()) ? colors_[idx] : Color{};
}
} // namespace OHOS::Ace::NG
