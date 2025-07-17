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

#include "ui/view/theme/token_colors.h"

#include <vector>

#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace {

static const std::vector<TokenColorData> colorData = {
    { "brand", 125830976 }, /* BRAND = 0 */
    { "warning", 125830979 }, /* WARNING = 1; */
    { "alert", 125830980 }, /* ALERT = 2 */
    { "confirm", 125830981 }, /* CONFIRM = 3 */

    { "fontPrimary", 125830982 }, /* FONT_PRIMARY = 4 */
    { "fontSecondary", 125830983 }, /* FONT_SECONDARY = 5 */
    { "fontTertiary", 125830984 }, /* FONT_TERTIARY = 6 */
    { "fontFourth", 125830985 }, /* FONT_FOURTH = 7 */
    { "fontEmphasize", 125830986 }, /* FONT_EMPHASIZE = 8 */

    { "fontOnPrimary", 125830987 }, /* FONT_ON_PRIMARY = 9 */
    { "fontOnSecondary", 125830988 }, /* FONT_ON_SECONDARY = 10 */
    { "fontOnTertiary", 125830989 }, /* FONT_ON_TERTIARY = 11 */
    { "fontOnFourth", 125830990 }, /* FONT_ON_FOURTH = 12 */

    { "iconPrimary", 125830991 }, /* ICON_PRIMARY = 13 */
    { "iconSecondary", 125830992 }, /* ICON_SECONDARY = 14 */
    { "iconTertiary", 125830993 }, /* ICON_TERTIARY = 15 */
    { "iconFourth", 125830994 }, /* ICON_FOURTH = 16 */
    { "iconEmphasize", 125830995 }, /* ICON_EMPHASIZE = 17 */
    { "iconSubEmphasize", 125830996 }, /* ICON_SUB_EMPHASIZE = 18 */

    { "iconOnPrimary", 125831057 }, /* ICON_ON_PRIMARY = 19 */
    { "iconOnSecondary", 125831058 }, /* ICON_ON_SECONDARY = 20 */
    { "iconOnTertiary", 125831059 }, /* ICON_ON_TERTIARY = 21 */
    { "iconOnFourth", 125831060 }, /* ICON_ON_FOURTH = 22 */

    { "backgroundPrimary", 125831061 }, /* BACKGROUND_PRIMARY = 23 */
    { "backgroundSecondary", 125831062 }, /* BACKGROUND_SECONDARY = 24 */
    { "backgroundTertiary", 125831063 }, /* BACKGROUND_TERTIARY = 25 */
    { "backgroundFourth", 125831064 }, /* BACKGROUND_FOURTH = 26 */
    { "backgroundEmphasize", 125831065 }, /* BACKGROUND_EMPHASIZE = 27 */

    { "compForegroundPrimary", 125831003 }, /* COMP_FOREGROUND_PRIMARY = 28 */
    { "compBackgroundPrimary", 125831004 }, /* COMP_BACKGROUND_PRIMARY = 29 */
    { "compBackgroundPrimaryTran", -1 }, /* COMP_BACKGROUND_PRIMARY_TRAN = 30 */
    { "compBackgroundPrimaryContrary", 125831005 }, /* COMP_BACKGROUND_PRIMARY_CONTRARY = 31 */
    { "compBackgroundGray", 125831006 }, /* COMP_BACKGROUND_GRAY = 32 */
    { "compBackgroundSecondary", 125831007 }, /* COMP_BACKGROUND_SECONDARY = 33 */
    { "compBackgroundTertiary", 125831008 }, /* COMP_BACKGROUND_TERTIARY = 34 */
    { "compBackgroundEmphasize", 125831009 }, /* COMP_BACKGROUND_EMPHASIZE = 35 */
    { "compBackgroundNeutral", 125831066 }, /* COMP_BACKGROUND_NEUTRAL = 36 */
    { "compEmphasizeSecondary", 125831011 }, /* COMP_EMPHASIZE_SECONDARY = 37 */
    { "compEmphasizeTertiary", 125831012 }, /* COMP_EMPHASIZE_TERTIARY = 38 */
    { "compDivider", 125831013 }, /* COMP_DIVIDER = 39 */
    { "compCommonContrary", 125831014 }, /* COMP_COMMON_CONTRARY = 40 */
    { "compBackgroundFocus", 125831015 }, /* COMP_BACKGROUND_FOCUS = 41 */
    { "compFocusedPrimary", 125831016 }, /* COMP_FOCUSED_PRIMARY = 42 */
    { "compFocusedSecondary", 125831017 }, /* COMP_FOCUSED_SECONDARY = 43 */
    { "compFocusedTertiary", 125831018 }, /* COMP_FOCUSED_TERTIARY = 44 */

    { "interactiveHover", 125831019 }, /* INTERACTIVE_HOVER = 45 */
    { "interactivePressed", 125831020 }, /* INTERACTIVE_PRESSED = 46 */
    { "interactiveFocus", 125831021 }, /* INTERACTIVE_FOCUS = 47 */
    { "interactiveActive", 125831022 }, /* INTERACTIVE_ACTIVE = 48 */
    { "interactiveSelect", 125831023 }, /* INTERACTIVE_SELECT = 49 */
    { "interactiveClick", 125831024 }, /* INTERACTIVE_CLICK = 50 */

    { nullptr, -1 } /* TOTAL_NUMBER = 51; */
};

void TokenColors::SetColors(const std::vector<Color>& colors)
{
    colors_ = colors;
}

void TokenColors::SetColor(uint32_t idx, const Color& color)
{
    if (idx >= 0 && idx < colors_.size()) {
        colors_[idx] = color;
    }
}

const std::vector<Color>& TokenColors::GetColors()
{
    return colors_;
}

Color TokenColors::GetColorWithResourceObject(int32_t colorIndex) const
{
    if ((colorMode_ == ColorMode::COLOR_MODE_UNDEFINED) && (resObjs_.size() == TokenColors::TOTAL_NUMBER) &&
        resObjs_[colorIndex]) {
        Color color;
        ResourceParseUtils::ParseResColor(resObjs_[colorIndex], color);
        return color;
    }
    return colors_[colorIndex];
}

Color TokenColors::Brand() const
{
    return GetColorWithResourceObject(BRAND);
}

Color TokenColors::Warning() const
{
    return GetColorWithResourceObject(WARNING);
}

Color TokenColors::Alert() const
{
    return GetColorWithResourceObject(ALERT);
}

Color TokenColors::Confirm() const
{
    return GetColorWithResourceObject(CONFIRM);
}

Color TokenColors::FontPrimary() const
{
    return GetColorWithResourceObject(FONT_PRIMARY);
}

Color TokenColors::FontSecondary() const
{
    return GetColorWithResourceObject(FONT_SECONDARY);
}

Color TokenColors::FontTertiary() const
{
    return GetColorWithResourceObject(FONT_TERTIARY);
}

Color TokenColors::FontFourth() const
{
    return GetColorWithResourceObject(FONT_FOURTH);
}

Color TokenColors::FontEmphasize() const
{
    return GetColorWithResourceObject(FONT_EMPHASIZE);
}

Color TokenColors::FontOnPrimary() const
{
    return GetColorWithResourceObject(FONT_ON_PRIMARY);
}

Color TokenColors::FontOnSecondary() const
{
    return GetColorWithResourceObject(FONT_ON_SECONDARY);
}

Color TokenColors::FontOnTertiary() const
{
    return GetColorWithResourceObject(FONT_ON_TERTIARY);
}

Color TokenColors::FontOnFourth() const
{
    return GetColorWithResourceObject(FONT_ON_FOURTH);
}

Color TokenColors::IconPrimary() const
{
    return GetColorWithResourceObject(ICON_PRIMARY);
}

Color TokenColors::IconSecondary() const
{
    return GetColorWithResourceObject(ICON_SECONDARY);
}

Color TokenColors::IconTertiary() const
{
    return GetColorWithResourceObject(ICON_TERTIARY);
}

Color TokenColors::IconFourth() const
{
    return GetColorWithResourceObject(ICON_FOURTH);
}

Color TokenColors::IconEmphasize() const
{
    return GetColorWithResourceObject(ICON_EMPHASIZE);
}

Color TokenColors::IconSubEmphasize() const
{
    return GetColorWithResourceObject(ICON_SUB_EMPHASIZE);
}

Color TokenColors::IconOnPrimary() const
{
    return GetColorWithResourceObject(ICON_ON_PRIMARY);
}

Color TokenColors::IconOnSecondary() const
{
    return GetColorWithResourceObject(ICON_ON_SECONDARY);
}

Color TokenColors::IconOnTertiary() const
{
    return GetColorWithResourceObject(ICON_ON_TERTIARY);
}

Color TokenColors::IconOnFourth() const
{
    return GetColorWithResourceObject(ICON_ON_FOURTH);
}

Color TokenColors::BackgroundPrimary() const
{
    return GetColorWithResourceObject(BACKGROUND_PRIMARY);
}

Color TokenColors::BackgroundSecondary() const
{
    return GetColorWithResourceObject(BACKGROUND_SECONDARY);
}

Color TokenColors::BackgroundTertiary() const
{
    return GetColorWithResourceObject(BACKGROUND_TERTIARY);
}

Color TokenColors::BackgroundFourth() const
{
    return GetColorWithResourceObject(BACKGROUND_FOURTH);
}

Color TokenColors::BackgroundEmphasize() const
{
    return GetColorWithResourceObject(BACKGROUND_EMPHASIZE);
}

Color TokenColors::CompForegroundPrimary() const
{
    return GetColorWithResourceObject(COMP_FOREGROUND_PRIMARY);
}

Color TokenColors::CompBackgroundPrimary() const
{
    return GetColorWithResourceObject(COMP_BACKGROUND_PRIMARY);
}

Color TokenColors::CompBackgroundPrimaryTran() const
{
    return GetColorWithResourceObject(COMP_BACKGROUND_PRIMARY_TRAN);
}

Color TokenColors::CompBackgroundPrimaryContrary() const
{
    return GetColorWithResourceObject(COMP_BACKGROUND_PRIMARY_CONTRARY);
}

Color TokenColors::CompBackgroundGray() const
{
    return GetColorWithResourceObject(COMP_BACKGROUND_GRAY);
}

Color TokenColors::CompBackgroundSecondary() const
{
    return GetColorWithResourceObject(COMP_BACKGROUND_SECONDARY);
}

Color TokenColors::CompBackgroundTertiary() const
{
    return GetColorWithResourceObject(COMP_BACKGROUND_TERTIARY);
}

Color TokenColors::CompBackgroundEmphasize() const
{
    return GetColorWithResourceObject(COMP_BACKGROUND_EMPHASIZE);
}

Color TokenColors::CompBackgroundNeutral() const
{
    return GetColorWithResourceObject(COMP_BACKGROUND_NEUTRAL);
}

Color TokenColors::CompEmphasizeSecondary() const
{
    return GetColorWithResourceObject(COMP_EMPHASIZE_SECONDARY);
}

Color TokenColors::CompEmphasizeTertiary() const
{
    return GetColorWithResourceObject(COMP_EMPHASIZE_TERTIARY);
}

Color TokenColors::CompDivider() const
{
    return GetColorWithResourceObject(COMP_DIVIDER);
}

Color TokenColors::CompCommonContrary() const
{
    return GetColorWithResourceObject(COMP_COMMON_CONTRARY);
}

Color TokenColors::CompBackgroundFocus() const
{
    return GetColorWithResourceObject(COMP_BACKGROUND_FOCUS);
}

Color TokenColors::CompFocusedPrimary() const
{
    return GetColorWithResourceObject(COMP_FOCUSED_PRIMARY);
}

Color TokenColors::CompFocusedSecondary() const
{
    return GetColorWithResourceObject(COMP_FOCUSED_SECONDARY);
}

Color TokenColors::CompFocusedTertiary() const
{
    return GetColorWithResourceObject(COMP_FOCUSED_TERTIARY);
}

Color TokenColors::InteractiveHover() const
{
    return GetColorWithResourceObject(INTERACTIVE_HOVER);
}

Color TokenColors::InteractivePressed() const
{
    return GetColorWithResourceObject(INTERACTIVE_PRESSED);
}

Color TokenColors::InteractiveFocus() const
{
    return GetColorWithResourceObject(INTERACTIVE_FOCUS);
}

Color TokenColors::InteractiveActive() const
{
    return GetColorWithResourceObject(INTERACTIVE_ACTIVE);
}

Color TokenColors::InteractiveSelect() const
{
    return GetColorWithResourceObject(INTERACTIVE_SELECT);
}

Color TokenColors::InteractiveClick() const
{
    return GetColorWithResourceObject(INTERACTIVE_CLICK);
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

Color TokenColors::GetByIndex(uint32_t idx)
{
    return (idx >= 0 && idx < colors_.size()) ? colors_[idx] : Color{};
}
} // namespace OHOS::Ace::NG
