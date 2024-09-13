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

#include <optional>

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shadow.h"

#include "converter.h"

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<Alignment>& dst, const Ark_Alignment& src)
{
    switch (src) {
        case ARK_ALIGNMENT_TOP_START: dst = Alignment::TOP_LEFT; break;
        case ARK_ALIGNMENT_TOP: dst = Alignment::TOP_CENTER; break;
        case ARK_ALIGNMENT_TOP_END: dst = Alignment::TOP_RIGHT; break;
        case ARK_ALIGNMENT_START: dst = Alignment::CENTER_LEFT; break;
        case ARK_ALIGNMENT_CENTER: dst = Alignment::CENTER; break;
        case ARK_ALIGNMENT_END: dst = Alignment::CENTER_RIGHT; break;
        case ARK_ALIGNMENT_BOTTOM_START: dst = Alignment::BOTTOM_LEFT; break;
        case ARK_ALIGNMENT_BOTTOM: dst = Alignment::BOTTOM_CENTER; break;
        case ARK_ALIGNMENT_BOTTOM_END: dst = Alignment::BOTTOM_RIGHT; break;
        default: LOGE("Unexpected enum value in Ark_Alignment: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ButtonRole>& dst, const Ark_ButtonRole& src)
{
    switch (src) {
        case ARK_BUTTON_ROLE_NORMAL: dst = ButtonRole::NORMAL; break;
        case ARK_BUTTON_ROLE_ERROR: dst = ButtonRole::ERROR; break;
        default: LOGE("Unexpected enum value in Ark_ButtonRole: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<Color>& dst, const enum Ark_Color& src)
{
    switch (src) {
        case ARK_COLOR_WHITE: dst = Color(0xffffffff); break; // White
        case ARK_COLOR_BLACK: dst = Color(0xff000000); break; // Black
        case ARK_COLOR_BLUE: dst = Color(0xff0000ff); break; // Blue
        case ARK_COLOR_BROWN: dst = Color(0xffa52a2a); break; // Brown
        case ARK_COLOR_GRAY: dst = Color(0xff808080); break; // Gray
        case ARK_COLOR_GREEN: dst = Color(0xff008000); break; // Green
        case ARK_COLOR_GREY: dst = Color(0xff808080); break; // Grey
        case ARK_COLOR_ORANGE: dst = Color(0xffffa500); break; // Orange
        case ARK_COLOR_PINK: dst = Color(0xffffc0cb); break; // Pink
        case ARK_COLOR_RED: dst = Color(0xffff0000); break; // Red
        case ARK_COLOR_YELLOW: dst = Color(0xffffff00); break; // Yellow
        case ARK_COLOR_TRANSPARENT: dst = Color(0x00000000); break; // Transparent
        default: LOGE("Unexpected enum value in Ark_Color: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<FontWeight>& dst, const Ark_FontWeight& src)
{
    switch (src) {
        case ARK_FONT_WEIGHT_LIGHTER: dst = FontWeight::LIGHTER; break;
        case ARK_FONT_WEIGHT_NORMAL: dst = FontWeight::NORMAL; break;
        case ARK_FONT_WEIGHT_REGULAR: dst = FontWeight::REGULAR; break;
        case ARK_FONT_WEIGHT_MEDIUM: dst = FontWeight::MEDIUM; break;
        case ARK_FONT_WEIGHT_BOLD: dst = FontWeight::BOLD; break;
        case ARK_FONT_WEIGHT_BOLDER: dst = FontWeight::BOLDER; break;
        default: LOGE("Unexpected enum value in Ark_FontWeight: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ForegroundColorStrategy>& dst, const Ark_ColoringStrategy& src)
{
    switch (src) {
        case ARK_COLORING_STRATEGY_INVERT: dst = ForegroundColorStrategy::INVERT; break;
        default: LOGE("Unexpected enum value in Ark_ColoringStrategy: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<LineCap>& dst, const Ark_LineCapStyle& src)
{
    switch (src) {
        case ARK_LINE_CAP_STYLE_BUTT: dst = LineCap::BUTT; break;
        case ARK_LINE_CAP_STYLE_ROUND: dst = LineCap::ROUND; break;
        case ARK_LINE_CAP_STYLE_SQUARE: dst = LineCap::SQUARE; break;
        default: LOGE("Unexpected enum value in Ark_LineCapStyle: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ShadowColorStrategy>& dst, const Ark_ColoringStrategy& src)
{
    switch (src) {
        case ARK_COLORING_STRATEGY_AVERAGE: dst = ShadowColorStrategy::AVERAGE; break;
        case ARK_COLORING_STRATEGY_PRIMARY: dst = ShadowColorStrategy::PRIMARY; break;
        default: LOGE("Unexpected enum value in Ark_ColoringStrategy: %{public}d", src);
    }
}
} // namespace OHOS::Ace::NG::Converter
