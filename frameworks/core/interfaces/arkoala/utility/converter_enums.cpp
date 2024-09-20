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

// Convert Ark_ButtonRole
template<>
void AssignCast(std::optional<ButtonRole>& dst, const Ark_ButtonRole& src)
{
    switch (src) {
        case ARK_BUTTON_ROLE_NORMAL: dst = ButtonRole::NORMAL; break;
        case ARK_BUTTON_ROLE_ERROR: dst = ButtonRole::ERROR; break;
        default: LOGE("Unexpected enum value in Ark_ButtonRole: %{public}d", src);
    }
}

// Convert Ark_ButtonType
template<>
void AssignCast(std::optional<ButtonType>& dst, const Ark_ButtonType& src)
{
    switch (src) {
        case ARK_BUTTON_TYPE_CAPSULE: dst = ButtonType::CAPSULE; break;
        case ARK_BUTTON_TYPE_CIRCLE: dst = ButtonType::CIRCLE; break;
        case ARK_BUTTON_TYPE_NORMAL: dst = ButtonType::NORMAL; break;
        case ARK_BUTTON_TYPE_ROUNDED_RECTANGLE: dst = ButtonType::ROUNDED_RECTANGLE; break;
        default: LOGE("Unexpected enum value in Ark_ButtonType: %{public}d", src);
    }
}

// Convert Ark_ControlSize
template<>
void AssignCast(std::optional<ControlSize>& dst, const Ark_ControlSize& src)
{
    switch (src) {
        case ARK_CONTROL_SIZE_SMALL: dst = ControlSize::SMALL; break;
        case ARK_CONTROL_SIZE_NORMAL: dst = ControlSize::NORMAL; break;
        default: LOGE("Unexpected enum value in Ark_ControlSize: %{public}d", src);
    }
}

// Convert Ark_ButtonStyleMode
template<>
void AssignCast(std::optional<ButtonStyleMode>& dst, const Ark_ButtonStyleMode& src)
{
    switch (src) {
        case ARK_BUTTON_STYLE_MODE_NORMAL: dst = ButtonStyleMode::NORMAL; break;
        case ARK_BUTTON_STYLE_MODE_EMPHASIZED: dst = ButtonStyleMode::EMPHASIZE; break;
        case ARK_BUTTON_STYLE_MODE_TEXTUAL: dst = ButtonStyleMode::TEXT; break;
        default: LOGE("Unexpected enum value in Ark_ButtonStyleMode: %{public}d", src);
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

template<>
void AssignCast(std::optional<ScrollState>& dst, const Ark_ScrollState& src)
{
    switch (src) {
        case ARK_SCROLL_STATE_IDLE: dst = ScrollState::IDLE; break;
        case ARK_SCROLL_STATE_SCROLL: dst = ScrollState::SCROLL; break;
        case ARK_SCROLL_STATE_FLING: dst = ScrollState::FLING; break;
        default: LOGE("Unexpected enum value in Ark_ScrollState: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TextDecorationStyle>& dst, const Ark_TextDecorationStyle& src)
{
    switch (src) {
        case ARK_TEXT_DECORATION_STYLE_SOLID: dst = TextDecorationStyle::SOLID; break;
        case ARK_TEXT_DECORATION_STYLE_DOUBLE: dst = TextDecorationStyle::DOUBLE; break;
        case ARK_TEXT_DECORATION_STYLE_DOTTED: dst = TextDecorationStyle::DOTTED; break;
        case ARK_TEXT_DECORATION_STYLE_DASHED: dst = TextDecorationStyle::DASHED; break;
        case ARK_TEXT_DECORATION_STYLE_WAVY: dst = TextDecorationStyle::WAVY; break;
        default: LOGE("Unexpected enum value in Ark_TextDecorationStyle: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<FlexDirection>& dst, const Ark_GridDirection& src)
{
    switch (src) {
        case ARK_GRID_DIRECTION_ROW: dst = FlexDirection::ROW; break;
        case ARK_GRID_DIRECTION_COLUMN: dst = FlexDirection::COLUMN; break;
        case ARK_GRID_DIRECTION_ROW_REVERSE: dst = FlexDirection::ROW_REVERSE; break;
        case ARK_GRID_DIRECTION_COLUMN_REVERSE: dst = FlexDirection::COLUMN_REVERSE; break;
        default: LOGE("Unexpected enum value in Ark_GridDirection: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TextDecoration>& dst, const Ark_TextDecorationType& src)
{
    switch (src) {
        case ARK_TEXT_DECORATION_TYPE_NONE: dst = TextDecoration::NONE; break;
        case ARK_TEXT_DECORATION_TYPE_UNDERLINE: dst = TextDecoration::UNDERLINE; break;
        case ARK_TEXT_DECORATION_TYPE_OVERLINE: dst = TextDecoration::OVERLINE; break;
        case ARK_TEXT_DECORATION_TYPE_LINE_THROUGH: dst = TextDecoration::LINE_THROUGH; break;
        default: LOGE("Unexpected enum value in Ark_TextDecorationType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<EdgeEffect>& dst, const Ark_EdgeEffect& src)
{
    switch (src) {
        case ARK_EDGE_EFFECT_SPRING: dst = EdgeEffect::SPRING; break;
        case ARK_EDGE_EFFECT_FADE: dst = EdgeEffect::FADE; break;
        case ARK_EDGE_EFFECT_NONE: dst = EdgeEffect::NONE; break;
        default: LOGE("Unexpected enum value in Ark_EdgeEffect: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TextAlign>& dst, const Ark_TextAlign& src)
{
    switch (src) {
        case ARK_TEXT_ALIGN_CENTER: dst = TextAlign::CENTER; break;
        case ARK_TEXT_ALIGN_START: dst = TextAlign::START; break;
        case ARK_TEXT_ALIGN_END: dst = TextAlign::END; break;
        case ARK_TEXT_ALIGN_JUSTIFY: dst = TextAlign::JUSTIFY; break;
        default: LOGE("Unexpected enum value in Ark_TextAlign: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TextInputAction>& dst, const Ark_EnterKeyType& src)
{
    switch (src) {
        case ARK_ENTER_KEY_TYPE_GO: dst = TextInputAction::GO; break;
        case ARK_ENTER_KEY_TYPE_SEARCH: dst = TextInputAction::SEARCH; break;
        case ARK_ENTER_KEY_TYPE_SEND: dst = TextInputAction::SEND; break;
        case ARK_ENTER_KEY_TYPE_NEXT: dst = TextInputAction::NEXT; break;
        case ARK_ENTER_KEY_TYPE_DONE: dst = TextInputAction::DONE; break;
        case ARK_ENTER_KEY_TYPE_PREVIOUS: dst = TextInputAction::PREVIOUS; break;
        case ARK_ENTER_KEY_TYPE_NEW_LINE: dst = TextInputAction::NEW_LINE; break;
        default: LOGE("Unexpected enum value in Ark_EnterKeyType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TextInputType>& dst, const Ark_TextAreaType& src)
{
    switch (src) {
        case ARK_TEXT_AREA_TYPE_NORMAL: dst = TextInputType::TEXT; break;
        case ARK_TEXT_AREA_TYPE_NUMBER: dst = TextInputType::NUMBER; break;
        case ARK_TEXT_AREA_TYPE_PHONE_NUMBER: dst = TextInputType::PHONE; break;
        case ARK_TEXT_AREA_TYPE_EMAIL: dst = TextInputType::EMAIL_ADDRESS; break;
        case ARK_TEXT_AREA_TYPE_NUMBER_DECIMAL: dst = TextInputType::NUMBER_DECIMAL; break;
        case ARK_TEXT_AREA_TYPE_URL: dst = TextInputType::URL; break;
        default: LOGE("Unexpected enum value in Ark_TextAreaType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TextDeleteDirection>& dst, const Ark_TextDeleteDirection& src)
{
    switch (src) {
        case ARK_TEXT_DELETE_DIRECTION_BACKWARD: dst = TextDeleteDirection::BACKWARD; break;
        case ARK_TEXT_DELETE_DIRECTION_FORWARD: dst = TextDeleteDirection::FORWARD; break;
        default: LOGE("Unexpected enum value in Ark_TextDeleteDirection: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<CopyOptions>& dst, const Ark_CopyOptions& src)
{
    switch (src) {
        case ARK_COPY_OPTIONS_NONE: dst = CopyOptions::None; break;
        case ARK_COPY_OPTIONS_IN_APP: dst = CopyOptions::InApp; break;
        case ARK_COPY_OPTIONS_LOCAL_DEVICE: dst = CopyOptions::Local; break;
        case ARK_COPY_OPTIONS_CROSS_DEVICE: dst = CopyOptions::Distributed; break;
        default: LOGE("Unexpected enum value in Ark_CopyOptions: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TextContentType>& dst, const Ark_ContentType& src)
{
    switch (src) {
        case ARK_CONTENT_TYPE_USER_NAME: dst = TextContentType::USER_NAME; break;
        case ARK_CONTENT_TYPE_PASSWORD: dst = TextContentType::VISIBLE_PASSWORD; break;
        case ARK_CONTENT_TYPE_NEW_PASSWORD: dst = TextContentType::NEW_PASSWORD; break;
        case ARK_CONTENT_TYPE_FULL_STREET_ADDRESS: dst = TextContentType::FULL_STREET_ADDRESS; break;
        case ARK_CONTENT_TYPE_HOUSE_NUMBER: dst = TextContentType::HOUSE_NUMBER; break;
        case ARK_CONTENT_TYPE_DISTRICT_ADDRESS: dst = TextContentType::DISTRICT_ADDRESS; break;
        case ARK_CONTENT_TYPE_CITY_ADDRESS: dst = TextContentType::CITY_ADDRESS; break;
        case ARK_CONTENT_TYPE_PROVINCE_ADDRESS: dst = TextContentType::PROVINCE_ADDRESS; break;
        case ARK_CONTENT_TYPE_COUNTRY_ADDRESS: dst = TextContentType::COUNTRY_ADDRESS; break;
        case ARK_CONTENT_TYPE_PERSON_FULL_NAME: dst = TextContentType::PERSON_FULL_NAME; break;
        case ARK_CONTENT_TYPE_PERSON_LAST_NAME: dst = TextContentType::PERSON_LAST_NAME; break;
        case ARK_CONTENT_TYPE_PERSON_FIRST_NAME: dst = TextContentType::PERSON_FIRST_NAME; break;
        case ARK_CONTENT_TYPE_PHONE_NUMBER: dst = TextContentType::PHONE_NUMBER; break;
        case ARK_CONTENT_TYPE_PHONE_COUNTRY_CODE: dst = TextContentType::PHONE_COUNTRY_CODE; break;
        case ARK_CONTENT_TYPE_FULL_PHONE_NUMBER: dst = TextContentType::FULL_PHONE_NUMBER; break;
        case ARK_CONTENT_TYPE_EMAIL_ADDRESS: dst = TextContentType::EMAIL_ADDRESS; break;
        case ARK_CONTENT_TYPE_BANK_CARD_NUMBER: dst = TextContentType::BANK_CARD_NUMBER; break;
        case ARK_CONTENT_TYPE_ID_CARD_NUMBER: dst = TextContentType::ID_CARD_NUMBER; break;
        case ARK_CONTENT_TYPE_NICKNAME: dst = TextContentType::NICKNAME; break;
        case ARK_CONTENT_TYPE_DETAIL_INFO_WITHOUT_STREET: dst = TextContentType::DETAIL_INFO_WITHOUT_STREET; break;
        case ARK_CONTENT_TYPE_FORMAT_ADDRESS: dst = TextContentType::FORMAT_ADDRESS; break;
        default: LOGE("Unexpected enum value in Ark_ContentType: %{public}d", src);
    }
}
} // namespace OHOS::Ace::NG::Converter
