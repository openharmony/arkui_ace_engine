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
#include "converter2.h"
#include "reverse_converter.h"

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
void AssignCast(std::optional<AnimationDirection>& dst, const Ark_PlayMode& src)
{
    switch (src) {
        case ARK_PLAY_MODE_NORMAL: dst = AnimationDirection::NORMAL; break;
        case ARK_PLAY_MODE_REVERSE: dst = AnimationDirection::REVERSE; break;
        case ARK_PLAY_MODE_ALTERNATE: dst = AnimationDirection::ALTERNATE; break;
        case ARK_PLAY_MODE_ALTERNATE_REVERSE: dst = AnimationDirection::ALTERNATE_REVERSE; break;
        default: LOGE("Unexpected enum value in Ark_PlayMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<BindSheetDismissReason>& dst, const Ark_DismissReason& src)
{
    switch (src) {
        case ARK_DISMISS_REASON_PRESS_BACK : dst = BindSheetDismissReason::BACK_PRESSED; break;
        case ARK_DISMISS_REASON_TOUCH_OUTSIDE: dst = BindSheetDismissReason::TOUCH_OUTSIDE; break;
        case ARK_DISMISS_REASON_CLOSE_BUTTON: dst = BindSheetDismissReason::CLOSE_BUTTON; break;
        case ARK_DISMISS_REASON_SLIDE_DOWN: dst = BindSheetDismissReason::SLIDE_DOWN; break;
        default: LOGE("Unexpected enum value in Ark_DismissReason: %{public}d", src); break;
    }
}

template<>
void AssignCast(std::optional<BlurStyle>& dst, const Ark_BlurStyle& src)
{
    switch (src) {
        case ARK_BLUR_STYLE_THIN: dst = BlurStyle::THIN; break;
        case ARK_BLUR_STYLE_REGULAR: dst = BlurStyle::REGULAR; break;
        case ARK_BLUR_STYLE_THICK: dst = BlurStyle::THICK; break;
        case ARK_BLUR_STYLE_BACKGROUND_THIN: dst = BlurStyle::BACKGROUND_THIN; break;
        case ARK_BLUR_STYLE_BACKGROUND_REGULAR: dst = BlurStyle::BACKGROUND_REGULAR; break;
        case ARK_BLUR_STYLE_BACKGROUND_THICK: dst = BlurStyle::BACKGROUND_THICK; break;
        case ARK_BLUR_STYLE_BACKGROUND_ULTRA_THICK: dst = BlurStyle::BACKGROUND_ULTRA_THICK; break;
        case ARK_BLUR_STYLE_NONE: dst = BlurStyle::NO_MATERIAL; break;
        case ARK_BLUR_STYLE_COMPONENT_ULTRA_THIN: dst = BlurStyle::COMPONENT_ULTRA_THIN; break;
        case ARK_BLUR_STYLE_COMPONENT_THIN: dst = BlurStyle::COMPONENT_THIN; break;
        case ARK_BLUR_STYLE_COMPONENT_REGULAR: dst = BlurStyle::COMPONENT_REGULAR; break;
        case ARK_BLUR_STYLE_COMPONENT_THICK: dst = BlurStyle::COMPONENT_THICK; break;
        case ARK_BLUR_STYLE_COMPONENT_ULTRA_THICK: dst = BlurStyle::COMPONENT_ULTRA_THICK; break;
        default: LOGE("Unexpected enum value in Ark_BlurStyle: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<BlurStyleActivePolicy>& dst, const Ark_BlurStyleActivePolicy& src)
{
    switch (src) {
        case ARK_BLUR_STYLE_ACTIVE_POLICY_FOLLOWS_WINDOW_ACTIVE_STATE:
            dst = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE; break;
        case ARK_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_ACTIVE: dst = BlurStyleActivePolicy::ALWAYS_ACTIVE; break;
        case ARK_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_INACTIVE: dst = BlurStyleActivePolicy::ALWAYS_INACTIVE; break;
        default: LOGE("Unexpected enum value in Ark_BlurStyleActivePolicy: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<BlurStyleOption>& dst, const Ark_BlurStyle& src)
{
    auto blurStyle = OptConvert<BlurStyle>(src);
    if (blurStyle) {
        BlurStyleOption blurStyleOptions;
        blurStyleOptions.blurStyle = blurStyle.value();
        dst = blurStyleOptions;
    }
}

template<>
void AssignCast(std::optional<BorderStyle>& dst, const Ark_BorderStyle& src)
{
    switch (src) {
        case ARK_BORDER_STYLE_DOTTED: dst = BorderStyle::DOTTED; break;
        case ARK_BORDER_STYLE_DASHED: dst = BorderStyle::DASHED; break;
        case ARK_BORDER_STYLE_SOLID: dst = BorderStyle::SOLID; break;
        default: LOGE("Unexpected enum value in Ark_BorderStyle: %{public}d", src);
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
void AssignCast(std::optional<NavigationType>& dst, const Ark_WebNavigationType& src)
{
    switch (src) {
        case ARK_WEB_NAVIGATION_TYPE_UNKNOWN: dst = NavigationType::NAVIGATION_TYPE_UNKNOWN; break;
        case ARK_WEB_NAVIGATION_TYPE_MAIN_FRAME_NEW_ENTRY: dst =
            NavigationType::NAVIGATION_TYPE_MAIN_FRAME_NEW_ENTRY; break;
        case ARK_WEB_NAVIGATION_TYPE_MAIN_FRAME_EXISTING_ENTRY: dst =
            NavigationType::NAVIGATION_TYPE_MAIN_FRAME_EXISTING_ENTRY; break;
        case ARK_WEB_NAVIGATION_TYPE_NAVIGATION_TYPE_NEW_SUBFRAME: dst =
            NavigationType::NAVIGATION_TYPE_NEW_SUBFRAME; break;
        case ARK_WEB_NAVIGATION_TYPE_NAVIGATION_TYPE_AUTO_SUBFRAME: dst =
            NavigationType::NAVIGATION_TYPE_AUTO_SUBFRAME; break;
        default: LOGE("Unexpected enum value in Ark_WebNavigationType: %{public}d", src);
    }
}

// Convert Ark_NavRouteMode
template<>
void AssignCast(std::optional<NavRouteMode>& dst, const Ark_NavRouteMode& src)
{
    switch (src) {
        case ARK_NAV_ROUTE_MODE_PUSH_WITH_RECREATE: dst = NavRouteMode::PUSH_WITH_RECREATE; break;
        case ARK_NAV_ROUTE_MODE_PUSH: dst = NavRouteMode::PUSH; break;
        case ARK_NAV_ROUTE_MODE_REPLACE: dst = NavRouteMode::REPLACE; break;
        default: LOGE("Unexpected enum value in Ark_NavRouteMode: %{public}d", src);
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
void AssignCast(std::optional<GestureMask>& dst, const Ark_GestureMask& src)
{
    switch (src) {
        case ARK_GESTURE_MASK_NORMAL: dst = GestureMask::Normal; break;
        case ARK_GESTURE_MASK_IGNORE_INTERNAL: dst = GestureMask::IgnoreInternal; break;
        default: LOGE("Unexpected enum value in Ark_GestureMask: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ImageAnalyzerType>& dst, const Ark_ImageAnalyzerType& src)
{
    switch (src) {
        case ARK_IMAGE_ANALYZER_TYPE_TEXT: dst = ImageAnalyzerType::TEXT; break;
        case ARK_IMAGE_ANALYZER_TYPE_SUBJECT: dst = ImageAnalyzerType::SUBJECT; break;
        default: LOGE("Unexpected enum value in Ark_ImageAnalyzerType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ImageFit>& dst, const Ark_ImageFit& src)
{
    switch (src) {
        case ARK_IMAGE_FIT_CONTAIN: dst = ImageFit::CONTAIN; break;
        case ARK_IMAGE_FIT_COVER: dst = ImageFit::COVER; break;
        case ARK_IMAGE_FIT_AUTO: dst = ImageFit::FITWIDTH; break;
        case ARK_IMAGE_FIT_FILL: dst = ImageFit::FILL; break;
        case ARK_IMAGE_FIT_SCALE_DOWN: dst = ImageFit::SCALE_DOWN; break;
        case ARK_IMAGE_FIT_NONE: dst = ImageFit::NONE; break;
        case ARK_IMAGE_FIT_TOP_START: dst = ImageFit::TOP_LEFT; break;
        case ARK_IMAGE_FIT_TOP: dst = ImageFit::TOP; break;
        case ARK_IMAGE_FIT_TOP_END: dst = ImageFit::TOP_END; break;
        case ARK_IMAGE_FIT_START: dst = ImageFit::START; break;
        case ARK_IMAGE_FIT_CENTER: dst = ImageFit::CENTER; break;
        case ARK_IMAGE_FIT_END: dst = ImageFit::END; break;
        case ARK_IMAGE_FIT_BOTTOM_START: dst = ImageFit::BOTTOM_START; break;
        case ARK_IMAGE_FIT_BOTTOM: dst = ImageFit::BOTTOM; break;
        case ARK_IMAGE_FIT_BOTTOM_END: dst = ImageFit::BOTTOM_END; break;
        default: LOGE("Unexpected enum value in Ark_ImageFit: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ImageInterpolation>& dst, const Ark_ImageInterpolation& src)
{
    switch (src) {
        case ARK_IMAGE_INTERPOLATION_NONE: dst = ImageInterpolation::NONE; break;
        case ARK_IMAGE_INTERPOLATION_LOW: dst = ImageInterpolation::LOW; break;
        case ARK_IMAGE_INTERPOLATION_MEDIUM: dst = ImageInterpolation::MEDIUM; break;
        case ARK_IMAGE_INTERPOLATION_HIGH: dst = ImageInterpolation::HIGH; break;
        default: LOGE("Unexpected enum value in Ark_ImageInterpolation: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ImageRenderMode>& dst, const Ark_ImageRenderMode& src)
{
    switch (src) {
        case ARK_IMAGE_RENDER_MODE_ORIGINAL: dst = ImageRenderMode::ORIGINAL; break;
        case ARK_IMAGE_RENDER_MODE_TEMPLATE: dst = ImageRenderMode::TEMPLATE; break;
        default: LOGE("Unexpected enum value in Ark_ImageRenderMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ImageRepeat>& dst, const Ark_ImageRepeat& src)
{
    switch (src) {
        case ARK_IMAGE_REPEAT_NO_REPEAT: dst = ImageRepeat::NO_REPEAT; break;
        case ARK_IMAGE_REPEAT_X: dst = ImageRepeat::REPEAT_X; break;
        case ARK_IMAGE_REPEAT_Y: dst = ImageRepeat::REPEAT_Y; break;
        case ARK_IMAGE_REPEAT_XY: dst = ImageRepeat::REPEAT; break;
        default: LOGE("Unexpected enum value in Ark_ImageRepeat: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<VerticalAlign>& dst, const Ark_ImageSpanAlignment& src)
{
    switch (src) {
        case Ark_ImageSpanAlignment::ARK_IMAGE_SPAN_ALIGNMENT_TOP: dst = VerticalAlign::TOP; break;
        case Ark_ImageSpanAlignment::ARK_IMAGE_SPAN_ALIGNMENT_CENTER: dst = VerticalAlign::CENTER; break;
        case Ark_ImageSpanAlignment::ARK_IMAGE_SPAN_ALIGNMENT_BOTTOM: dst = VerticalAlign::BOTTOM; break;
        case Ark_ImageSpanAlignment::ARK_IMAGE_SPAN_ALIGNMENT_BASELINE: dst = VerticalAlign::BASELINE; break;
        default: LOGE("Unexpected enum value in Ark_ImageSpanAlignment: %{public}d", src);
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
void AssignCast(std::optional<LineCapStyle>& dst, const Ark_LineCapStyle& src)
{
    switch (src) {
        case ARK_LINE_CAP_STYLE_BUTT: dst = LineCapStyle::BUTT; break;
        case ARK_LINE_CAP_STYLE_ROUND: dst = LineCapStyle::ROUND; break;
        case ARK_LINE_CAP_STYLE_SQUARE: dst = LineCapStyle::SQUARE; break;
        default: LOGE("Unexpected enum value in Ark_LineCapStyle: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<LineJoinStyle>& dst, const Ark_LineJoinStyle& src)
{
    switch (src) {
        case ARK_LINE_JOIN_STYLE_MITER: dst = LineJoinStyle::MITER; break;
        case ARK_LINE_JOIN_STYLE_ROUND: dst = LineJoinStyle::ROUND; break;
        case ARK_LINE_JOIN_STYLE_BEVEL: dst = LineJoinStyle::BEVEL; break;
        default: LOGE("Unexpected enum value in Ark_LineJoinStyle: %{public}d", src);
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
void AssignCast(std::optional<ShadowType>& dst, const Ark_ShadowType& src)
{
    switch (src) {
        case ARK_SHADOW_TYPE_COLOR: dst = ShadowType::COLOR; break;
        case ARK_SHADOW_TYPE_BLUR: dst = ShadowType::BLUR; break;
        default: LOGE("Unexpected enum value in Ark_ShadowType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<SheetKeyboardAvoidMode>& dst, const Ark_SheetKeyboardAvoidMode& src)
{
    switch (src) {
        case ARK_SHEET_KEYBOARD_AVOID_MODE_NONE: dst = SheetKeyboardAvoidMode::NONE; break;
        case ARK_SHEET_KEYBOARD_AVOID_MODE_TRANSLATE_AND_RESIZE:
            dst = SheetKeyboardAvoidMode::TRANSLATE_AND_RESIZE; break;
        case ARK_SHEET_KEYBOARD_AVOID_MODE_RESIZE_ONLY: dst = SheetKeyboardAvoidMode::RESIZE_ONLY; break;
        case ARK_SHEET_KEYBOARD_AVOID_MODE_TRANSLATE_AND_SCROLL:
            dst = SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL; break;
        default: LOGE("Unexpected enum value in Ark_SheetKeyboardAvoidMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<SheetLevel>& dst, const Ark_SheetMode& src)
{
    switch (src) {
        case ARK_SHEET_MODE_OVERLAY: dst = SheetLevel::OVERLAY; break;
        case ARK_SHEET_MODE_EMBEDDED: dst = SheetLevel::EMBEDDED; break;
        default: LOGE("Unexpected enum value in Ark_SheetMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<SheetMode>& dst, const Ark_SheetSize& src)
{
    switch (src) {
        case ARK_SHEET_SIZE_MEDIUM: dst = SheetMode::MEDIUM; break;
        case ARK_SHEET_SIZE_LARGE: dst = SheetMode::LARGE; break;
        case ARK_SHEET_SIZE_FIT_CONTENT: dst = SheetMode::AUTO; break;
        default: LOGE("Unexpected enum value in Ark_SheetSize: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<SheetType>& dst, const Ark_SheetType& src)
{
    switch (src) {
        case ARK_SHEET_TYPE_BOTTOM: dst = SheetType::SHEET_BOTTOM; break;
        case ARK_SHEET_TYPE_CENTER: dst = SheetType::SHEET_CENTER; break;
        case ARK_SHEET_TYPE_POPUP: dst = SheetType::SHEET_POPUP; break;
        default: LOGE("Unexpected enum value in Ark_SheetType: %{public}d", src);
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

// Convert Ark_TextDecorationStyle
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
void AssignCast(std::optional<V2::StickyMode>& dst, const Ark_Sticky& src)
{
    switch (src) {
        case ARK_STICKY_NONE: dst = V2::StickyMode::NONE; break;
        case ARK_STICKY_NORMAL: dst = V2::StickyMode::NORMAL; break;
        case ARK_STICKY_OPACITY: dst = V2::StickyMode::OPACITY; break;
        default: LOGE("Unexpected enum value in Ark_Sticky: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<V2::ListItemAlign>& dst, const Ark_ListItemAlign& src)
{
    switch (src) {
        case ARK_LIST_ITEM_ALIGN_START: dst = V2::ListItemAlign::START; break;
        case ARK_LIST_ITEM_ALIGN_CENTER: dst = V2::ListItemAlign::CENTER; break;
        case ARK_LIST_ITEM_ALIGN_END: dst = V2::ListItemAlign::END; break;
        default: LOGE("Unexpected enum value in Ark_ListItemAlign: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<FinishCallbackType>& dst, const Ark_FinishCallbackType& src)
{
    switch (src) {
        case ARK_FINISH_CALLBACK_TYPE_REMOVED: dst = FinishCallbackType::REMOVED; break;
        case ARK_FINISH_CALLBACK_TYPE_LOGICALLY: dst = FinishCallbackType::LOGICALLY; break;
        default: LOGE("Unexpected enum value in Ark_FinishCallbackType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<FlexAlign>& dst, const Ark_FlexAlign& src)
{
    switch (src) {
        case ARK_FLEX_ALIGN_START: dst = FlexAlign::FLEX_START; break;
        case ARK_FLEX_ALIGN_CENTER: dst = FlexAlign::CENTER; break;
        case ARK_FLEX_ALIGN_END: dst = FlexAlign::FLEX_END; break;
        case ARK_FLEX_ALIGN_SPACE_BETWEEN: dst = FlexAlign::SPACE_BETWEEN; break;
        case ARK_FLEX_ALIGN_SPACE_AROUND: dst = FlexAlign::SPACE_AROUND; break;
        case ARK_FLEX_ALIGN_SPACE_EVENLY: dst = FlexAlign::SPACE_EVENLY; break;
        default: LOGE("Unexpected enum value in Ark_FlexAlign: %{public}d", src);
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
void AssignCast(std::optional<FlexDirection>& dst, const Ark_FlexDirection& src)
{
    switch (src) {
        case ARK_FLEX_DIRECTION_ROW: dst = FlexDirection::ROW; break;
        case ARK_FLEX_DIRECTION_COLUMN: dst = FlexDirection::COLUMN; break;
        case ARK_FLEX_DIRECTION_ROW_REVERSE: dst = FlexDirection::ROW_REVERSE; break;
        case ARK_FLEX_DIRECTION_COLUMN_REVERSE: dst = FlexDirection::COLUMN_REVERSE; break;
        default: LOGE("Unexpected enum value in Ark_FlexDirection: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<Axis>& dst, const Ark_Axis& src)
{
    switch (src) {
        case ARK_AXIS_VERTICAL: dst = Axis::VERTICAL; break;
        case ARK_AXIS_HORIZONTAL: dst = Axis::HORIZONTAL; break;
        default: LOGE("Unexpected enum value in Ark_Axis: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<DisplayMode>& dst, const Ark_BarState& src)
{
    switch (src) {
        case ARK_BAR_STATE_OFF: dst = DisplayMode::OFF; break;
        case ARK_BAR_STATE_AUTO: dst = DisplayMode::AUTO; break;
        case ARK_BAR_STATE_ON: dst = DisplayMode::ON; break;
        default: LOGE("Unexpected enum value in Ark_BarState: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<DragPreviewMode>& dst, const Ark_DragPreviewMode& src)
{
    switch (src) {
        case ARK_DRAG_PREVIEW_MODE_AUTO: dst = DragPreviewMode::AUTO; break;
        case ARK_DRAG_PREVIEW_MODE_DISABLE_SCALE: dst = DragPreviewMode::DISABLE_SCALE; break;
        case ARK_DRAG_PREVIEW_MODE_ENABLE_DEFAULT_SHADOW: dst = DragPreviewMode::ENABLE_DEFAULT_SHADOW; break;
        case ARK_DRAG_PREVIEW_MODE_ENABLE_DEFAULT_RADIUS: dst = DragPreviewMode::ENABLE_DEFAULT_RADIUS; break;
        default: LOGE("Unexpected enum value in Ark_DragPreviewMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<DynamicRangeMode>& dst, const Ark_DynamicRangeMode& src)
{
    switch (src) {
        case ARK_DYNAMIC_RANGE_MODE_HIGH: dst = DynamicRangeMode::HIGH; break;
        case ARK_DYNAMIC_RANGE_MODE_CONSTRAINT: dst = DynamicRangeMode::CONSTRAINT; break;
        case ARK_DYNAMIC_RANGE_MODE_STANDARD: dst = DynamicRangeMode::STANDARD; break;
        default: LOGE("Unexpected enum value in Ark_DynamicRangeMode: %{public}d", src);
    }
}

// Convert Ark_TextDecorationType
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
void AssignCast(std::optional<V2::ListItemStyle>& dst, const Ark_ListItemStyle& src)
{
    switch (src) {
        case ARK_LIST_ITEM_STYLE_NONE: dst = V2::ListItemStyle::NONE; break;
        case ARK_LIST_ITEM_STYLE_CARD: dst = V2::ListItemStyle::CARD; break;
        default: LOGE("Unexpected enum value in Ark_ListItemStyle: %{public}d", src);
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
void AssignCast(std::optional<EllipsisMode>& dst, const Ark_EllipsisMode& src)
{
    switch (src) {
        case ARK_ELLIPSIS_MODE_START: dst = EllipsisMode::HEAD; break;
        case ARK_ELLIPSIS_MODE_CENTER: dst = EllipsisMode::MIDDLE; break;
        case ARK_ELLIPSIS_MODE_END: dst = EllipsisMode::TAIL; break;
        default: LOGE("Unexpected enum value in Ark_EllipsisMode: %{public}d", src);
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
void AssignCast(std::optional<TextHeightAdaptivePolicy>& dst, const Ark_TextHeightAdaptivePolicy& src)
{
    switch (src) {
        case ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_LAYOUT_CONSTRAINT_FIRST:
            dst = TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST; break;
        case ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST: dst = TextHeightAdaptivePolicy::MAX_LINES_FIRST; break;
        case ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_MIN_FONT_SIZE_FIRST:
            dst = TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST; break;
        default: LOGE("Unexpected enum value in Ark_TextHeightAdaptivePolicy: %{public}d", src);
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
void AssignCast(std::optional<TextInputType>& dst, const Ark_InputType& src)
{
    switch (src) {
        case ARK_INPUT_TYPE_NORMAL: dst = TextInputType::TEXT; break;
        case ARK_INPUT_TYPE_NUMBER: dst = TextInputType::NUMBER; break;
        case ARK_INPUT_TYPE_PHONE_NUMBER: dst = TextInputType::PHONE; break;
        case ARK_INPUT_TYPE_EMAIL: dst = TextInputType::EMAIL_ADDRESS; break;
        case ARK_INPUT_TYPE_PASSWORD: dst = TextInputType::VISIBLE_PASSWORD; break;
        case ARK_INPUT_TYPE_NUMBER_PASSWORD: dst = TextInputType::NUMBER_PASSWORD; break;
        case ARK_INPUT_TYPE_SCREEN_LOCK_PASSWORD: dst = TextInputType::SCREEN_LOCK_PASSWORD; break;
        case ARK_INPUT_TYPE_USER_NAME: dst = TextInputType::USER_NAME; break;
        case ARK_INPUT_TYPE_NEW_PASSWORD: dst = TextInputType::NEW_PASSWORD; break;
        case ARK_INPUT_TYPE_NUMBER_DECIMAL: dst = TextInputType::NUMBER_DECIMAL; break;
        case ARK_INPUT_TYPE_URL: dst = TextInputType::URL; break;
        default: LOGE("Unexpected enum value in Ark_InputType: %{public}d", src);
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
void AssignCast(std::optional<TextOverflow>& dst, const Ark_TextOverflow& src)
{
    switch (src) {
        case ARK_TEXT_OVERFLOW_NONE: dst = TextOverflow::NONE; break;
        case ARK_TEXT_OVERFLOW_ELLIPSIS: dst = TextOverflow::ELLIPSIS; break;
        case ARK_TEXT_OVERFLOW_CLIP: dst = TextOverflow::CLIP; break;
        case ARK_TEXT_OVERFLOW_MARQUEE: dst = TextOverflow::MARQUEE; break;
        default: LOGE("Unexpected enum value in Ark_TextOverflow: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TextInputType>& dst, const Ark_SearchType& src)
{
    switch (src) {
        case ARK_SEARCH_TYPE_NORMAL: dst = TextInputType::TEXT; break;
        case ARK_SEARCH_TYPE_NUMBER: dst = TextInputType::NUMBER; break;
        case ARK_SEARCH_TYPE_PHONE_NUMBER: dst = TextInputType::PHONE; break;
        case ARK_SEARCH_TYPE_EMAIL: dst = TextInputType::EMAIL_ADDRESS; break;
        case ARK_SEARCH_TYPE_NUMBER_DECIMAL: dst = TextInputType::NUMBER_DECIMAL; break;
        case ARK_SEARCH_TYPE_URL: dst = TextInputType::JS_ENUM_URL; break;
        default: LOGE("Unexpected enum value in Ark_TextAreaType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<CancelButtonStyle>& dst, const Ark_CancelButtonStyle& src)
{
    switch (src) {
        case ARK_CANCEL_BUTTON_STYLE_CONSTANT : dst = CancelButtonStyle::CONSTANT; break;
        case ARK_CANCEL_BUTTON_STYLE_INVISIBLE: dst = CancelButtonStyle::INVISIBLE; break;
        case ARK_CANCEL_BUTTON_STYLE_INPUT: dst = CancelButtonStyle::INPUT; break;
        default: LOGE("Unexpected enum value in Ark_CancelButtonStyle: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<CleanNodeStyle>& dst, const Ark_CancelButtonStyle& src)
{
    switch (src) {
        case ARK_CANCEL_BUTTON_STYLE_CONSTANT : dst = CleanNodeStyle::CONSTANT; break;
        case ARK_CANCEL_BUTTON_STYLE_INVISIBLE: dst = CleanNodeStyle::INVISIBLE; break;
        case ARK_CANCEL_BUTTON_STYLE_INPUT: dst = CleanNodeStyle::INPUT; break;
        default: LOGE("Unexpected enum value in Ark_CancelButtonStyle: %{public}d", src);
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
void AssignCast(std::optional<DimensionUnit>& dst, const Ark_LengthUnit& src)
{
    switch (src) {
        case ARK_LENGTH_UNIT_PX: dst = DimensionUnit::PX; break;
        case ARK_LENGTH_UNIT_VP: dst = DimensionUnit::VP; break;
        case ARK_LENGTH_UNIT_FP: dst = DimensionUnit::FP; break;
        case ARK_LENGTH_UNIT_PERCENT: dst = DimensionUnit::PERCENT; break;
        case ARK_LENGTH_UNIT_LPX: dst = DimensionUnit::LPX; break;
        default: LOGE("Unexpected enum value in Ark_LengthUnit: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<Dimension>& dst, const Ark_ArrowPointPosition& src)
{
    switch (src) {
        case ARK_ARROW_POINT_POSITION_START: dst = 0.0_pct; break;
        case ARK_ARROW_POINT_POSITION_CENTER: dst = 0.5_pct; break;
        case ARK_ARROW_POINT_POSITION_END: dst = 1.0_pct; break;
        default: LOGE("Unexpected enum value in Ark_ArrowPointPosition: %{public}d", src);
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

template<>
void AssignCast(std::optional<TextCase>& dst, const Ark_TextCase& src)
{
    switch (src) {
        case ARK_TEXT_CASE_NORMAL: dst = TextCase::NORMAL; break;
        case ARK_TEXT_CASE_LOWER_CASE: dst = TextCase::LOWERCASE; break;
        case ARK_TEXT_CASE_UPPER_CASE: dst = TextCase::UPPERCASE; break;
        default: LOGE("Unexpected enum value in Ark_TextCase: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<V2::StickyStyle>& dst, const Ark_StickyStyle& src)
{
    switch (src) {
        case ARK_STICKY_STYLE_NONE: dst = V2::StickyStyle::NONE; break;
        case ARK_STICKY_STYLE_HEADER: dst = V2::StickyStyle::HEADER; break;
        case ARK_STICKY_STYLE_FOOTER: dst = V2::StickyStyle::FOOTER; break;
        default: LOGE("Unexpected enum value in Ark_StickyStyle: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<OHOS::Ace::FontStyle>& dst, const Ark_FontStyle& src)
{
    switch (src) {
        case ARK_FONT_STYLE_NORMAL: dst = OHOS::Ace::FontStyle::NORMAL; break;
        case ARK_FONT_STYLE_ITALIC: dst = OHOS::Ace::FontStyle::ITALIC; break;
        default: LOGE("Unexpected enum value in Ark_FontStyle: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<V2::ScrollSnapAlign>& dst, const Ark_ScrollSnapAlign& src)
{
    switch (src) {
        case ARK_SCROLL_SNAP_ALIGN_NONE: dst = V2::ScrollSnapAlign::NONE; break;
        case ARK_SCROLL_SNAP_ALIGN_START: dst = V2::ScrollSnapAlign::START; break;
        case ARK_SCROLL_SNAP_ALIGN_CENTER: dst = V2::ScrollSnapAlign::CENTER; break;
        case ARK_SCROLL_SNAP_ALIGN_END: dst = V2::ScrollSnapAlign::END; break;
        default: LOGE("Unexpected enum value in Ark_ScrollSnapAlign: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<Ace::ScrollSnapAlign>& dst, const Ark_ScrollSnapAlign& src)
{
    switch (src) {
        case ARK_SCROLL_SNAP_ALIGN_NONE: dst = Ace::ScrollSnapAlign::NONE; break;
        case ARK_SCROLL_SNAP_ALIGN_START: dst = Ace::ScrollSnapAlign::START; break;
        case ARK_SCROLL_SNAP_ALIGN_CENTER: dst = Ace::ScrollSnapAlign::CENTER; break;
        case ARK_SCROLL_SNAP_ALIGN_END: dst = Ace::ScrollSnapAlign::END; break;
        default: LOGE("Unexpected enum value in Ark_ScrollSnapAlign: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ChainEdgeEffect>& dst, const Ark_ChainEdgeEffect& src)
{
    switch (src) {
        case ARK_CHAIN_EDGE_EFFECT_DEFAULT: dst = ChainEdgeEffect::DEFAULT; break;
        case ARK_CHAIN_EDGE_EFFECT_STRETCH: dst = ChainEdgeEffect::STRETCH; break;
        default: LOGE("Unexpected enum value in Ark_ChainEdgeEffect: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<NestedScrollMode>& dst, const Ark_NestedScrollMode& src)
{
    switch (src) {
        case ARK_NESTED_SCROLL_MODE_SELF_ONLY: dst = NestedScrollMode::SELF_ONLY; break;
        case ARK_NESTED_SCROLL_MODE_SELF_FIRST: dst = NestedScrollMode::SELF_FIRST; break;
        case ARK_NESTED_SCROLL_MODE_PARENT_FIRST: dst = NestedScrollMode::PARENT_FIRST; break;
        case ARK_NESTED_SCROLL_MODE_PARALLEL: dst = NestedScrollMode::PARALLEL; break;
        default: LOGE("Unexpected enum value in Ark_NestedScrollMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ListItemGroupArea>& dst, const Ark_ListItemGroupArea& src)
{
    switch (src) {
        case ARK_LIST_ITEM_GROUP_AREA_NONE: dst = ListItemGroupArea::NONE_AREA; break;
        case ARK_LIST_ITEM_GROUP_AREA_IN_LIST_ITEM_AREA: dst = ListItemGroupArea::IN_LIST_ITEM_AREA; break;
        case ARK_LIST_ITEM_GROUP_AREA_IN_HEADER_AREA: dst = ListItemGroupArea::IN_HEADER_AREA; break;
        case ARK_LIST_ITEM_GROUP_AREA_IN_FOOTER_AREA: dst = ListItemGroupArea::IN_FOOTER_AREA; break;
        default: LOGE("Unexpected enum value in Ark_ListItemGroupArea: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<V2::ListItemGroupStyle>& dst, const Ark_ListItemGroupStyle& src)
{
    switch (src) {
        case ARK_LIST_ITEM_GROUP_STYLE_NONE: dst = V2::ListItemGroupStyle::NONE; break;
        case ARK_LIST_ITEM_GROUP_STYLE_CARD: dst = V2::ListItemGroupStyle::CARD; break;
        default: LOGE("Unexpected enum value in Ark_ListItemGroupStyle: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<V2::SwipeEdgeEffect>& dst, const Ark_SwipeEdgeEffect& src)
{
    switch (src) {
        case ARK_SWIPE_EDGE_EFFECT_SPRING: dst = V2::SwipeEdgeEffect::Spring; break;
        case ARK_SWIPE_EDGE_EFFECT_NONE: dst = V2::SwipeEdgeEffect::None; break;
        default: LOGE("Unexpected enum value in Ark_SwipeEdgeEffect: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<FlexAlign>& dst, const Ark_VerticalAlign& src)
{
    switch (src) {
        case ARK_VERTICAL_ALIGN_TOP: dst = FlexAlign::FLEX_START; break;
        case ARK_VERTICAL_ALIGN_CENTER: dst = FlexAlign::CENTER; break;
        case ARK_VERTICAL_ALIGN_BOTTOM: dst = FlexAlign::FLEX_END; break;
        default: LOGE("Unexpected enum value in Ark_VerticalAlign: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<SharedTransitionEffectType>& dst, const Ark_SharedTransitionEffectType& src)
{
    switch (src) {
        case ARK_SHARED_TRANSITION_EFFECT_TYPE_STATIC:
            dst = OHOS::Ace::SharedTransitionEffectType::SHARED_EFFECT_STATIC; break;
        case ARK_SHARED_TRANSITION_EFFECT_TYPE_EXCHANGE:
            dst = OHOS::Ace::SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE; break;
        default: LOGE("Unexpected enum value in Ark_SharedTransitionEffectType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TabAnimateMode>& dst, const Ark_AnimationMode& src)
{
    switch (src) {
        case ARK_ANIMATION_MODE_CONTENT_FIRST: dst = TabAnimateMode::CONTENT_FIRST; break;
        case ARK_ANIMATION_MODE_ACTION_FIRST: dst = TabAnimateMode::ACTION_FIRST; break;
        case ARK_ANIMATION_MODE_NO_ANIMATION: dst = TabAnimateMode::NO_ANIMATION; break;
        default: LOGE("Unexpected enum value in Ark_AnimationMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<BarPosition>& dst, const Ark_BarPosition& src)
{
    switch (src) {
        case ARK_BAR_POSITION_START: dst = BarPosition::START; break;
        case ARK_BAR_POSITION_END: dst = BarPosition::END; break;
        default: LOGE("Unexpected enum value in Ark_BarPosition: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TabBarMode>& dst, const Ark_BarMode& src)
{
    switch (src) {
        case ARK_BAR_MODE_SCROLLABLE: dst = TabBarMode::SCROLLABLE; break;
        case ARK_BAR_MODE_FIXED: dst = TabBarMode::FIXED; break;
        default: LOGE("Unexpected enum value in Ark_BarMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<SslError>& dst, const Ark_SslError& src)
{
    switch (src) {
        case ARK_SSL_ERROR_INVALID: dst = SslError::INVALID; break;
        case ARK_SSL_ERROR_HOST_MISMATCH: dst = SslError::HOST_MISMATCH; break;
        case ARK_SSL_ERROR_DATE_INVALID: dst = SslError::DATE_INVALID; break;
        case ARK_SSL_ERROR_UNTRUSTED: dst = SslError::UNTRUSTED; break;
        default: LOGE("Unexpected enum value in Ark_SslError: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<std::string>& dst, const Ark_FunctionKey& src)
{
    switch (src) {
        case ARK_FUNCTION_KEY_ESC: dst = "ESC"; break;
        case ARK_FUNCTION_KEY_F1: dst = "F1"; break;
        case ARK_FUNCTION_KEY_F2: dst = "F2"; break;
        case ARK_FUNCTION_KEY_F3: dst = "F3"; break;
        case ARK_FUNCTION_KEY_F4: dst = "F4"; break;
        case ARK_FUNCTION_KEY_F5: dst = "F5"; break;
        case ARK_FUNCTION_KEY_F6: dst = "F6"; break;
        case ARK_FUNCTION_KEY_F7: dst = "F7"; break;
        case ARK_FUNCTION_KEY_F8: dst = "F8"; break;
        case ARK_FUNCTION_KEY_F9: dst = "F9"; break;
        case ARK_FUNCTION_KEY_F10: dst = "F10"; break;
        case ARK_FUNCTION_KEY_F11: dst = "F11"; break;
        case ARK_FUNCTION_KEY_F12: dst = "F12"; break;
        case ARK_FUNCTION_KEY_TAB: dst = "TAB"; break;
        case ARK_FUNCTION_KEY_DPAD_UP: dst = "DPAD_UP"; break;
        case ARK_FUNCTION_KEY_DPAD_DOWN: dst = "DPAD_DOWN"; break;
        case ARK_FUNCTION_KEY_DPAD_LEFT: dst = "DPAD_LEFT"; break;
        case ARK_FUNCTION_KEY_DPAD_RIGHT: dst = "DPAD_RIGHT"; break;
        default: LOGE("Unexpected enum value in Ark_FunctionKey: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<SubMenuExpandingMode>& dst, const Ark_SubMenuExpandingMode& src)
{
    switch (src) {
        case ARK_SUB_MENU_EXPANDING_MODE_SIDE_EXPAND: dst = SubMenuExpandingMode::SIDE; break;
        case ARK_SUB_MENU_EXPANDING_MODE_EMBEDDED_EXPAND: dst = SubMenuExpandingMode::EMBEDDED; break;
        case ARK_SUB_MENU_EXPANDING_MODE_STACK_EXPAND: dst = SubMenuExpandingMode::STACK; break;
        default: LOGE("Unexpected enum value in Ark_SubMenuExpandingMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<LayoutStyle>& dst, const Ark_LayoutStyle& src)
{
    switch (src) {
        case ARK_LAYOUT_STYLE_ALWAYS_CENTER: dst = LayoutStyle::ALWAYS_CENTER; break;
        case ARK_LAYOUT_STYLE_ALWAYS_AVERAGE_SPLIT: dst = LayoutStyle::ALWAYS_AVERAGE_SPLIT; break;
        case ARK_LAYOUT_STYLE_SPACE_BETWEEN_OR_CENTER: dst = LayoutStyle::SPACE_BETWEEN_OR_CENTER; break;
        default: LOGE("Unexpected enum value in Ark_LayoutStyle: %{public}d", src);
    }
}

// need check
// template<>
// void AssignCast(std::optional<DataPanelType>& dst, const Ark_DataPanelType& src)
// {
//     switch (src) {
//         case ARK_DATA_PANEL_TYPE_LINE: dst = DataPanelType::LINE; break;
//         case ARK_DATA_PANEL_TYPE_CIRCLE: dst = DataPanelType::CIRCLE; break;
//         default: LOGE("Unexpected enum value in Ark_DataPanelType: %{public}d", src);
//     }
// }

template<>
void AssignCast(std::optional<SliderModel::SliderMode>& dst, const Ark_SliderStyle& src)
{
    switch (src) {
        case ARK_SLIDER_STYLE_OUT_SET: dst = SliderModel::SliderMode::OUTSET; break;
        case ARK_SLIDER_STYLE_IN_SET: dst = SliderModel::SliderMode::INSET; break;
        case ARK_SLIDER_STYLE_NONE: dst = SliderModel::SliderMode::NONE; break;
        default: LOGE("Unexpected enum value in Ark_SliderStyle: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<AccessibilityHoverAction>& dst, const Ark_AccessibilityHoverType& src)
{
    switch (src) {
        case ARK_ACCESSIBILITY_HOVER_TYPE_HOVER_ENTER: dst = AccessibilityHoverAction::HOVER_ENTER; break;
        case ARK_ACCESSIBILITY_HOVER_TYPE_HOVER_MOVE: dst = AccessibilityHoverAction::HOVER_MOVE; break;
        case ARK_ACCESSIBILITY_HOVER_TYPE_HOVER_EXIT: dst = AccessibilityHoverAction::HOVER_EXIT; break;
        case ARK_ACCESSIBILITY_HOVER_TYPE_HOVER_CANCEL: dst = AccessibilityHoverAction::HOVER_CANCEL; break;
        default: LOGE("Unexpected enum value in Ark_AccessibilityHoverType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<AdaptiveColor>& dst, const Ark_AdaptiveColor& src)
{
    switch (src) {
        case ARK_ADAPTIVE_COLOR_DEFAULT: dst = AdaptiveColor::DEFAULT; break;
        case ARK_ADAPTIVE_COLOR_AVERAGE: dst = AdaptiveColor::AVERAGE; break;
        default: LOGE("Unexpected enum value in Ark_AdaptiveColor: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<SliderModel::SliderInteraction>& dst, const Ark_SliderInteraction& src)
{
    switch (src) {
        case ARK_SLIDER_INTERACTION_SLIDE_AND_CLICK: dst = SliderModel::SliderInteraction::SLIDE_AND_CLICK;
            break;
        case ARK_SLIDER_INTERACTION_SLIDE_ONLY: dst = SliderModel::SliderInteraction::SLIDE_ONLY;
            break;
        case ARK_SLIDER_INTERACTION_SLIDE_AND_CLICK_UP: dst = SliderModel::SliderInteraction::SLIDE_AND_CLICK_UP;
            break;
        default: LOGE("Unexpected enum value in Ark_SliderInteraction: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<BorderImageRepeat>& dst, const Ark_RepeatMode& src)
{
    switch (src) {
        case ARK_REPEAT_MODE_REPEAT: dst = BorderImageRepeat::REPEAT; break;
        case ARK_REPEAT_MODE_STRETCH: dst = BorderImageRepeat::STRETCH; break;
        case ARK_REPEAT_MODE_ROUND: dst = BorderImageRepeat::ROUND; break;
        case ARK_REPEAT_MODE_SPACE: dst = BorderImageRepeat::SPACE; break;
        default: LOGE("Unexpected enum value in Ark_RepeatMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<SliderModel::BlockStyleType>& dst, const Ark_SliderBlockType& src)
{
    switch (src) {
        case ARK_SLIDER_BLOCK_TYPE_DEFAULT: dst = SliderModel::BlockStyleType::DEFAULT;
            break;
        case ARK_SLIDER_BLOCK_TYPE_IMAGE: dst = SliderModel::BlockStyleType::IMAGE;
            break;
        case ARK_SLIDER_BLOCK_TYPE_SHAPE: dst = SliderModel::BlockStyleType::SHAPE;
            break;
        default: LOGE("Unexpected enum value in Ark_SliderBlockType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ThemeColorMode>& dst, const Ark_ThemeColorMode& src)
{
    switch (src) {
        case ARK_THEME_COLOR_MODE_SYSTEM: dst = ThemeColorMode::SYSTEM; break;
        case ARK_THEME_COLOR_MODE_LIGHT: dst = ThemeColorMode::LIGHT; break;
        case ARK_THEME_COLOR_MODE_DARK: dst = ThemeColorMode::DARK; break;
        default: LOGE("Unexpected enum value in Ark_ThemeColorMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ThreatType>& dst, const Ark_ThreatType& src)
{
    switch (src) {
        case ARK_THREAT_TYPE_THREAT_ILLEGAL: dst = ThreatType::ILLEGAL; break;
        case ARK_THREAT_TYPE_THREAT_FRAUD: dst = ThreatType::FRAUD; break;
        case ARK_THREAT_TYPE_THREAT_RISK: dst = ThreatType::RISK; break;
        case ARK_THREAT_TYPE_THREAT_WARNING: dst = ThreatType::WARNING; break;
        default: LOGE("Unexpected enum value in Ark_ThreatType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<SliderModel::SliderChangeMode>& dst, const Ark_SliderChangeMode& src)
{
    switch (src) {
        case ARK_SLIDER_CHANGE_MODE_BEGIN: dst = SliderModel::SliderChangeMode::BEGIN; break;
        case ARK_SLIDER_CHANGE_MODE_MOVING: dst = SliderModel::SliderChangeMode::MOVING; break;
        case ARK_SLIDER_CHANGE_MODE_END: dst = SliderModel::SliderChangeMode::END; break;
        case ARK_SLIDER_CHANGE_MODE_CLICK: dst = SliderModel::SliderChangeMode::CLICK; break;
        default: LOGE("Unexpected enum value in Ark_SliderChangeMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<WebDarkMode>& dst, const Ark_WebDarkMode& src)
{
    switch (src) {
        case ARK_WEB_DARK_MODE_OFF: dst = WebDarkMode::Off; break;
        case ARK_WEB_DARK_MODE_ON: dst = WebDarkMode::On; break;
        case ARK_WEB_DARK_MODE_AUTO: dst = WebDarkMode::Auto; break;
        default: LOGE("Unexpected enum value in Ark_WebDarkMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<WebElementType>& dst, const Ark_WebElementType& src)
{
    switch (src) {
        case ARK_WEB_ELEMENT_TYPE_IMAGE: dst = WebElementType::IMAGE; break;
        default: LOGE("Unexpected enum value in Ark_WebElementType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<WebKeyboardAvoidMode>& dst, const Ark_WebKeyboardAvoidMode& src)
{
    switch (src) {
        case ARK_WEB_KEYBOARD_AVOID_MODE_RESIZE_VISUAL: dst = WebKeyboardAvoidMode::RESIZE_VISUAL; break;
        case ARK_WEB_KEYBOARD_AVOID_MODE_RESIZE_CONTENT: dst = WebKeyboardAvoidMode::RESIZE_CONTENT; break;
        case ARK_WEB_KEYBOARD_AVOID_MODE_OVERLAYS_CONTENT: dst = WebKeyboardAvoidMode::OVERLAYS_CONTENT; break;
        default: LOGE("Unexpected enum value in Ark_WebKeyboardAvoidMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<WebLayoutMode>& dst, const Ark_WebLayoutMode& src)
{
    switch (src) {
        case ARK_WEB_LAYOUT_MODE_NONE: dst = WebLayoutMode::NONE; break;
        case ARK_WEB_LAYOUT_MODE_FIT_CONTENT: dst = WebLayoutMode::FIT_CONTENT; break;
        default: LOGE("Unexpected enum value in Ark_WebLayoutMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<WebCacheMode>& dst, const Ark_CacheMode& src)
{
    switch (src) {
        case ARK_CACHE_MODE_DEFAULT: dst = WebCacheMode::DEFAULT; break;
        case ARK_CACHE_MODE_NONE: dst = WebCacheMode::USE_CACHE_ELSE_NETWORK; break;
        case ARK_CACHE_MODE_ONLINE: dst = WebCacheMode::USE_NO_CACHE; break;
        case ARK_CACHE_MODE_ONLY: dst = WebCacheMode::USE_CACHE_ONLY; break;
        default: LOGE("Unexpected enum value in Ark_CacheMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<WordBreak>& dst, const Ark_WordBreak& src)
{
    switch (src) {
        case ARK_WORD_BREAK_NORMAL: dst = WordBreak::NORMAL; break;
        case ARK_WORD_BREAK_BREAK_ALL: dst = WordBreak::BREAK_ALL; break;
        case ARK_WORD_BREAK_BREAK_WORD: dst = WordBreak::BREAK_WORD; break;
        default: LOGE("Unexpected enum value in Ark_WordBreak: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<XComponentType>& dst, const Ark_XComponentType& src)
{
    dst = XComponentType::UNKNOWN;
    switch (src) {
        case ARK_XCOMPONENT_TYPE_SURFACE: dst = XComponentType::SURFACE; break;
        case ARK_XCOMPONENT_TYPE_COMPONENT: dst = XComponentType::COMPONENT; break;
        case ARK_XCOMPONENT_TYPE_TEXTURE: dst = XComponentType::TEXTURE; break;
        case ARK_XCOMPONENT_TYPE_NODE: dst = XComponentType::NODE; break;
        default: LOGE("Unexpected enum value in Ark_XComponentType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<LineBreakStrategy>& dst, const Ark_LineBreakStrategy& src)
{
    switch (src) {
        case ARK_LINE_BREAK_STRATEGY_BALANCED: dst = LineBreakStrategy::BALANCED; break;
        case ARK_LINE_BREAK_STRATEGY_GREEDY: dst = LineBreakStrategy::GREEDY; break;
        case ARK_LINE_BREAK_STRATEGY_HIGH_QUALITY: dst = LineBreakStrategy::HIGH_QUALITY; break;
        default: LOGE("Unexpected enum value in Ark_LineBreakStrategy: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<MenuPolicy>& dst, const Ark_MenuPolicy& src)
{
    switch (src) {
        case ARK_MENU_POLICY_DEFAULT: dst = MenuPolicy::DEFAULT; break;
        case ARK_MENU_POLICY_HIDE: dst = MenuPolicy::HIDE; break;
        case ARK_MENU_POLICY_SHOW: dst = MenuPolicy::SHOW; break;
        default:
            LOGE("Unexpected enum value in Ark_MenuPolicy: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<MenuPreviewMode>& dst, const Ark_MenuPreviewMode& src)
{
    switch (src) {
        case ARK_MENU_PREVIEW_MODE_NONE: dst = MenuPreviewMode::NONE; break;
        case ARK_MENU_PREVIEW_MODE_IMAGE: dst = MenuPreviewMode::IMAGE; break;
        default:
            LOGE("Unexpected enum value in Ark_MenuPreviewMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ToggleType>& dst, const Ark_ToggleType& src)
{
    switch (src) {
        case ARK_TOGGLE_TYPE_CHECKBOX: dst = ToggleType::CHECKBOX; break;
        case ARK_TOGGLE_TYPE_SWITCH: dst = ToggleType::SWITCH; break;
        case ARK_TOGGLE_TYPE_BUTTON: dst = ToggleType::BUTTON; break;
        default: LOGE("Unexpected enum value in Ark_ToggleOptions: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<GradientDirection>& dst, const Ark_GradientDirection& src)
{
    switch (src) {
        case ARK_GRADIENT_DIRECTION_LEFT: dst = GradientDirection::LEFT; break;
        case ARK_GRADIENT_DIRECTION_TOP: dst = GradientDirection::TOP; break;
        case ARK_GRADIENT_DIRECTION_RIGHT: dst = GradientDirection::RIGHT; break;
        case ARK_GRADIENT_DIRECTION_BOTTOM: dst = GradientDirection::BOTTOM; break;
        case ARK_GRADIENT_DIRECTION_LEFT_TOP: dst = GradientDirection::LEFT_TOP; break;
        case ARK_GRADIENT_DIRECTION_LEFT_BOTTOM: dst = GradientDirection::LEFT_BOTTOM; break;
        case ARK_GRADIENT_DIRECTION_RIGHT_TOP: dst = GradientDirection::RIGHT_TOP; break;
        case ARK_GRADIENT_DIRECTION_RIGHT_BOTTOM: dst = GradientDirection::RIGHT_BOTTOM; break;
        case ARK_GRADIENT_DIRECTION_NONE: dst = GradientDirection::NONE; break;
        default: LOGE("Unexpected enum value in Ark_GradientDirection: %{public}d", src);
    }
}
template<>
void AssignCast(std::optional<HoverEffectType>& dst, const Ark_HoverEffect& src)
{
    switch (src) {
        case ARK_HOVER_EFFECT_AUTO: dst = HoverEffectType::AUTO; break;
        case ARK_HOVER_EFFECT_SCALE: dst = HoverEffectType::SCALE; break;
        case ARK_HOVER_EFFECT_HIGHLIGHT: dst = HoverEffectType::BOARD; break;
        case ARK_HOVER_EFFECT_NONE: dst = HoverEffectType::NONE; break;
        default: LOGE("Unexpected enum value in Ark_HoverEffect: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<FlexAlign>& dst, const Ark_ItemAlign& src)
{
    switch (src) {
        case ARK_ITEM_ALIGN_AUTO: dst = FlexAlign::AUTO; break;
        case ARK_ITEM_ALIGN_START: dst = FlexAlign::FLEX_START; break;
        case ARK_ITEM_ALIGN_CENTER: dst = FlexAlign::CENTER; break;
        case ARK_ITEM_ALIGN_END: dst = FlexAlign::FLEX_END; break;
        case ARK_ITEM_ALIGN_BASELINE: dst = FlexAlign::BASELINE; break;
        case ARK_ITEM_ALIGN_STRETCH: dst = FlexAlign::STRETCH; break;
        default: LOGE("Unexpected enum value in Ark_ItemAlign: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TextDirection>& dst, const Ark_Direction& src)
{
    switch (src) {
        case ARK_DIRECTION_LTR: dst = TextDirection::LTR; break;
        case ARK_DIRECTION_RTL: dst = TextDirection::RTL; break;
        case ARK_DIRECTION_AUTO: dst = TextDirection::AUTO; break;
        default: LOGE("Unexpected enum value in Ark_Direction: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<SelectionMenuType>& dst, const Ark_MenuType& src)
{
    switch (src) {
        case ARK_MENU_TYPE_SELECTION_MENU: dst = SelectionMenuType::SELECTION_MENU; break;
        case ARK_MENU_TYPE_PREVIEW_MENU: dst = SelectionMenuType::PREVIEW_MENU; break;
        default: LOGE("Unexpected enum value in Ark_MenuType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ShadowStyle>& dst, const Ark_ShadowStyle& src)
{
    switch (src) {
        case ARK_SHADOW_STYLE_OUTER_DEFAULT_XS: dst = ShadowStyle::OuterDefaultXS; break;
        case ARK_SHADOW_STYLE_OUTER_DEFAULT_SM: dst = ShadowStyle::OuterDefaultSM; break;
        case ARK_SHADOW_STYLE_OUTER_DEFAULT_MD: dst = ShadowStyle::OuterDefaultMD; break;
        case ARK_SHADOW_STYLE_OUTER_DEFAULT_LG: dst = ShadowStyle::OuterDefaultLG; break;
        case ARK_SHADOW_STYLE_OUTER_FLOATING_SM: dst = ShadowStyle::OuterFloatingSM; break;
        case ARK_SHADOW_STYLE_OUTER_FLOATING_MD: dst = ShadowStyle::OuterFloatingMD; break;
        default: LOGE("Unexpected enum value in Ark_ShadowStyle: %{public}d", src);
    }
}
template<>
void AssignCast(std::optional<InputStyle>& dst, const Ark_TextContentStyle& src)
{
    switch (src) {
        case ARK_TEXT_CONTENT_STYLE_DEFAULT: dst = InputStyle::DEFAULT; break;
        case ARK_TEXT_CONTENT_STYLE_INLINE: dst = InputStyle::INLINE; break;
        default: LOGE("Unexpected enum value in Ark_TextContentStyle: %{public}d", src);
    }
}
template<>
void AssignCast(std::optional<InputStyle>& dst, const Ark_TextInputStyle& src)
{
    switch (src) {
        case ARK_TEXT_INPUT_STYLE_DEFAULT: dst = InputStyle::DEFAULT; break;
        case ARK_TEXT_INPUT_STYLE_INLINE: dst = InputStyle::INLINE; break;
        default: LOGE("Unexpected enum value in Ark_TextInputStyle: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<RenderProcessNotRespondingReason>& dst, const Ark_RenderProcessNotRespondingReason& src)
{
    switch (src) {
        case ARK_RENDER_PROCESS_NOT_RESPONDING_REASON_INPUT_TIMEOUT: dst =
            RenderProcessNotRespondingReason::INPUT_TIMEOUT; break;
        case ARK_RENDER_PROCESS_NOT_RESPONDING_REASON_NAVIGATION_COMMIT_TIMEOUT: dst =
            RenderProcessNotRespondingReason::NAVIGATION_COMMIT_TIMEOUT; break;
        default: LOGE("Unexpected enum value in Ark_RenderProcessNotRespondingReason: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ScrollAlign>& dst, const Ark_ScrollAlign& src)
{
    switch (src) {
        case ARK_SCROLL_ALIGN_START: dst = ScrollAlign::START; break;
        case ARK_SCROLL_ALIGN_CENTER: dst = ScrollAlign::CENTER; break;
        case ARK_SCROLL_ALIGN_END: dst = ScrollAlign::END; break;
        case ARK_SCROLL_ALIGN_AUTO: dst = ScrollAlign::AUTO; break;
        default: LOGE("Unexpected enum value in Ark_ScrollAlign: %{public}d", src);
    }
}

template<> void AssignCast(std::optional<ScrollSizeMode>& dst, const Ark_ScrollSizeMode& src)
{
    switch (src) {
        case ARK_SCROLL_SIZE_MODE_FOLLOW_DETENT: dst = ScrollSizeMode::FOLLOW_DETENT; break;
        case ARK_SCROLL_SIZE_MODE_CONTINUOUS: dst = ScrollSizeMode::CONTINUOUS; break;
        default: LOGE("Unexpected enum value in Ark_ScrollSizeMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<OHOS::Ace::RenderingStrategy>& dst, const Ark_SymbolRenderingStrategy& src)
{
    switch (src) {
        case ARK_SYMBOL_RENDERING_STRATEGY_SINGLE: dst = OHOS::Ace::RenderingStrategy::SINGLE; break;
        case ARK_SYMBOL_RENDERING_STRATEGY_MULTIPLE_COLOR:
            dst = OHOS::Ace::RenderingStrategy::MULTIPLE_COLOR; break;
        case ARK_SYMBOL_RENDERING_STRATEGY_MULTIPLE_OPACITY:
            dst = OHOS::Ace::RenderingStrategy::MULTIPLE_OPACITY; break;
        default: LOGE("Unexpected enum value in Ark_SymbolRenderingStrategy: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<LineDirection>& dst, const Ark_Axis& src)
{
    switch (src) {
        case ARK_AXIS_VERTICAL: dst = LineDirection::VERTICAL; break;
        case ARK_AXIS_HORIZONTAL: dst = LineDirection::HORIZONTAL; break;
        default: LOGE("Unexpected enum value in Ark_Axis: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<OHOS::Ace::SymbolEffectType>& dst, const Ark_SymbolEffectStrategy& src)
{
    switch (src) {
        case ARK_SYMBOL_EFFECT_STRATEGY_NONE: dst = OHOS::Ace::SymbolEffectType::NONE; break;
        case ARK_SYMBOL_EFFECT_STRATEGY_SCALE: dst = OHOS::Ace::SymbolEffectType::SCALE; break;
        case ARK_SYMBOL_EFFECT_STRATEGY_HIERARCHICAL:
            dst = OHOS::Ace::SymbolEffectType::HIERARCHICAL; break;
        default: LOGE("Unexpected enum value in Ark_SymbolEffectStrategy: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<OverScrollMode>& dst, const Ark_OverScrollMode& src)
{
    switch (src) {
        case ARK_OVER_SCROLL_MODE_NEVER: dst = OverScrollMode::NEVER; break;
        case ARK_OVER_SCROLL_MODE_ALWAYS: dst = OverScrollMode::ALWAYS; break;
        default: LOGE("Unexpected enum value in Ark_OverScrollMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<PanelMode>& dst, const Ark_PanelMode& src)
{
    switch (src) {
        case ARK_PANEL_MODE_MINI: dst = PanelMode::MINI; break;
        case ARK_PANEL_MODE_HALF: dst = PanelMode::HALF; break;
        case ARK_PANEL_MODE_FULL: dst = PanelMode::FULL; break;
        default: LOGE("Unexpected enum value in Ark_PanelMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<Axis>& dst, const Ark_ScrollBarDirection& src)
{
    switch (src) {
        case ARK_SCROLL_BAR_DIRECTION_VERTICAL: dst = Axis::VERTICAL; break;
        case ARK_SCROLL_BAR_DIRECTION_HORIZONTAL: dst = Axis::HORIZONTAL; break;
        default: LOGE("Unexpected enum value in Ark_ScrollBarDirection: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<Axis>& dst, const Ark_ScrollDirection& src)
{
    switch (src) {
        case ARK_SCROLL_DIRECTION_VERTICAL: dst = Axis::VERTICAL; break;
        case ARK_SCROLL_DIRECTION_HORIZONTAL: dst = Axis::HORIZONTAL; break;
        case ARK_SCROLL_DIRECTION_FREE: dst = Axis::FREE; break;
        case ARK_SCROLL_DIRECTION_NONE: dst = Axis::NONE; break;
        default: LOGE("Unexpected enum value in Ark_ScrollDirection: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<MessageLevel>& dst, const Ark_MessageLevel& src)
{
    switch (src) {
        case ARK_MESSAGE_LEVEL_DEBUG: dst = MessageLevel::DEBUG; break;
        case ARK_MESSAGE_LEVEL_ERROR: dst = MessageLevel::ERROR; break;
        case ARK_MESSAGE_LEVEL_INFO: dst = MessageLevel::INFO; break;
        case ARK_MESSAGE_LEVEL_LOG: dst = MessageLevel::LOG; break;
        case ARK_MESSAGE_LEVEL_WARN: dst = MessageLevel::WARN; break;
        default: LOGE("Unexpected enum value in Ark_MessageLevel: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TextSpanType>& dst, const Ark_RichEditorSpanType& src)
{
    switch (src) {
        case ARK_RICH_EDITOR_SPAN_TYPE_TEXT: dst = TextSpanType::TEXT; break;
        case ARK_RICH_EDITOR_SPAN_TYPE_IMAGE: dst = TextSpanType::IMAGE; break;
        case ARK_RICH_EDITOR_SPAN_TYPE_MIXED: dst = TextSpanType::MIXED; break;
        case ARK_RICH_EDITOR_SPAN_TYPE_BUILDER: dst = TextSpanType::BUILDER; break;
        default: LOGE("Unexpected enum value in Ark_RichEditorSpanType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TextResponseType>& dst, const Ark_ResponseType& src)
{
    switch (src) {
        case ARK_RESPONSE_TYPE_RIGHT_CLICK: dst = TextResponseType::RIGHT_CLICK; break;
        case ARK_RESPONSE_TYPE_LONG_PRESS: dst = TextResponseType::LONG_PRESS; break;
        default: LOGE("Unexpected enum value in Ark_ResponseType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TextResponseType>& dst, const Ark_RichEditorResponseType& src)
{
    switch (src) {
        case ARK_RICH_EDITOR_RESPONSE_TYPE_RIGHT_CLICK: dst = TextResponseType::RIGHT_CLICK; break;
        case ARK_RICH_EDITOR_RESPONSE_TYPE_LONG_PRESS: dst = TextResponseType::LONG_PRESS; break;
        case ARK_RICH_EDITOR_RESPONSE_TYPE_SELECT: dst = TextResponseType::SELECTED_BY_MOUSE; break;
        default: LOGE("Unexpected enum value in Ark_RichEditorResponseType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<Ark_IlluminatedType>& dst, const Ark_IlluminatedType& src)
{
    switch (src) {
        case ARK_ILLUMINATED_TYPE_NONE: dst = ARK_ILLUMINATED_TYPE_NONE; break;
        case ARK_ILLUMINATED_TYPE_BORDER: dst = ARK_ILLUMINATED_TYPE_BORDER; break;
        case ARK_ILLUMINATED_TYPE_CONTENT: dst = ARK_ILLUMINATED_TYPE_CONTENT; break;
        case ARK_ILLUMINATED_TYPE_BORDER_CONTENT: dst = ARK_ILLUMINATED_TYPE_BORDER_CONTENT; break;
        case ARK_ILLUMINATED_TYPE_BLOOM_BORDER: dst = ARK_ILLUMINATED_TYPE_BLOOM_BORDER; break;
        case ARK_ILLUMINATED_TYPE_BLOOM_BORDER_CONTENT: dst = ARK_ILLUMINATED_TYPE_BLOOM_BORDER_CONTENT; break;
        default:
            LOGE("Unknown illumination type: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ChainStyle>& dst, const Ark_ChainStyle& src)
{
    switch (src) {
        case ARK_CHAIN_STYLE_SPREAD: dst = ChainStyle::SPREAD; break;
        case ARK_CHAIN_STYLE_SPREAD_INSIDE: dst = ChainStyle::SPREAD_INSIDE; break;
        case ARK_CHAIN_STYLE_PACKED: dst = ChainStyle::PACKED; break;
        default: LOGE("Unexpected enum value in Ark_ChainStyle: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<MixedModeContent>& dst, const Ark_MixedMode& src)
{
    switch (src) {
        case ARK_MIXED_MODE_ALL: dst = MixedModeContent::MIXED_CONTENT_ALWAYS_ALLOW; break;
        case ARK_MIXED_MODE_COMPATIBLE: dst = MixedModeContent::MIXED_CONTENT_COMPATIBILITY_MODE; break;
        case ARK_MIXED_MODE_NONE: dst = MixedModeContent::MIXED_CONTENT_NEVER_ALLOW; break;
        default: LOGE("Unexpected enum value in Ark_MixedMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ModalTransition>& dst, const Ark_ModalTransition& src)
{
    switch (src) {
        case ARK_MODAL_TRANSITION_DEFAULT: dst = ModalTransition::DEFAULT; break;
        case ARK_MODAL_TRANSITION_NONE: dst = ModalTransition::NONE; break;
        case ARK_MODAL_TRANSITION_ALPHA: dst = ModalTransition::ALPHA; break;
        default: LOGE("Unexpected enum value in Ark_ModalTransition: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ModifierKey>& dst, const Ark_ModifierKey& src)
{
    switch (src) {
        case ARK_MODIFIER_KEY_CTRL: dst = ModifierKey::CTRL; break;
        case ARK_MODIFIER_KEY_SHIFT: dst = ModifierKey::SHIFT; break;
        case ARK_MODIFIER_KEY_ALT: dst = ModifierKey::ALT; break;
        default: LOGE("Unexpected enum value in Ark_ModifierKey: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<NavDestinationMode>& dst, const Ark_NavDestinationMode& src)
{
    switch (src) {
        case ARK_NAV_DESTINATION_MODE_STANDARD: dst = NavDestinationMode::STANDARD; break;
        case ARK_NAV_DESTINATION_MODE_DIALOG: dst = NavDestinationMode::DIALOG; break;
        default: LOGE("Unexpected enum value in Ark_NavDestinationMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ViewportFit>& dst, const Ark_ViewportFit& src)
{
    switch (src) {
        case ARK_VIEWPORT_FIT_AUTO: dst = ViewportFit::AUTO; break;
        case ARK_VIEWPORT_FIT_CONTAINS: dst = ViewportFit::CONTAINS; break;
        case ARK_VIEWPORT_FIT_COVER: dst = ViewportFit::COVER; break;
        default: LOGE("Unexpected enum value in Ark_NavDestinationMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TransitionEdge>& dst, const Ark_TransitionEdge& src)
{
    switch (src) {
        case ARK_TRANSITION_EDGE_TOP: dst = TransitionEdge::TOP; break;
        case ARK_TRANSITION_EDGE_BOTTOM: dst = TransitionEdge::BOTTOM; break;
        case ARK_TRANSITION_EDGE_START: dst = TransitionEdge::START; break;
        case ARK_TRANSITION_EDGE_END: dst = TransitionEdge::END; break;
        default:
            LOGE("Unknown transition edge type: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<BlendApplyType>& dst, const Ark_BlendApplyType& src)
{
    switch (src) {
        case ARK_BLEND_APPLY_TYPE_FAST: dst = BlendApplyType::FAST; break;
        case ARK_BLEND_APPLY_TYPE_OFFSCREEN: dst = BlendApplyType::OFFSCREEN; break;
        default: LOGE("Unexpected enum value in Ark_BlendApplyType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<BlendMode>& dst, const Ark_BlendMode& src)
{
    switch (src) {
        case ARK_BLEND_MODE_NONE: dst = BlendMode::NONE; break;
        case ARK_BLEND_MODE_CLEAR: dst = BlendMode::CLEAR; break;
        case ARK_BLEND_MODE_SRC: dst = BlendMode::SRC; break;
        case ARK_BLEND_MODE_DST: dst = BlendMode::DST; break;
        case ARK_BLEND_MODE_SRC_OVER: dst = BlendMode::SRC_OVER; break;
        case ARK_BLEND_MODE_DST_OVER: dst = BlendMode::DST_OVER; break;
        case ARK_BLEND_MODE_SRC_IN: dst = BlendMode::SRC_IN; break;
        case ARK_BLEND_MODE_DST_IN: dst = BlendMode::DST_IN; break;
        case ARK_BLEND_MODE_SRC_OUT: dst = BlendMode::SRC_OUT; break;
        case ARK_BLEND_MODE_DST_OUT: dst = BlendMode::DST_OUT; break;
        case ARK_BLEND_MODE_SRC_ATOP: dst = BlendMode::SRC_ATOP; break;
        case ARK_BLEND_MODE_DST_ATOP: dst = BlendMode::DST_ATOP; break;
        case ARK_BLEND_MODE_XOR: dst = BlendMode::XOR; break;
        case ARK_BLEND_MODE_PLUS: dst = BlendMode::PLUS; break;
        case ARK_BLEND_MODE_MODULATE: dst = BlendMode::MODULATE; break;
        case ARK_BLEND_MODE_SCREEN: dst = BlendMode::SCREEN; break;
        case ARK_BLEND_MODE_OVERLAY: dst = BlendMode::OVERLAY; break;
        case ARK_BLEND_MODE_DARKEN: dst = BlendMode::DARKEN; break;
        case ARK_BLEND_MODE_LIGHTEN: dst = BlendMode::LIGHTEN; break;
        case ARK_BLEND_MODE_COLOR_DODGE: dst = BlendMode::COLOR_DODGE; break;
        case ARK_BLEND_MODE_COLOR_BURN: dst = BlendMode::COLOR_BURN; break;
        case ARK_BLEND_MODE_HARD_LIGHT: dst = BlendMode::HARD_LIGHT; break;
        case ARK_BLEND_MODE_SOFT_LIGHT: dst = BlendMode::SOFT_LIGHT; break;
        case ARK_BLEND_MODE_DIFFERENCE: dst = BlendMode::DIFF; break;
        case ARK_BLEND_MODE_EXCLUSION: dst = BlendMode::EXCLUSION; break;
        case ARK_BLEND_MODE_MULTIPLY: dst = BlendMode::MULTIPLY; break;
        case ARK_BLEND_MODE_HUE: dst = BlendMode::HUE; break;
        case ARK_BLEND_MODE_SATURATION: dst = BlendMode::SATURATION; break;
        case ARK_BLEND_MODE_COLOR: dst = BlendMode::COLOR; break;
        case ARK_BLEND_MODE_LUMINOSITY: dst = BlendMode::LUMINOSITY; break;
        default: LOGE("Unknown transition Ark_BlendMode type: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<Placement>& dst, const Ark_Placement& src)
{
    switch (src) {
        case ARK_PLACEMENT_LEFT: dst = Placement::LEFT; break;
        case ARK_PLACEMENT_RIGHT: dst = Placement::RIGHT; break;
        case ARK_PLACEMENT_TOP: dst = Placement::TOP; break;
        case ARK_PLACEMENT_BOTTOM: dst = Placement::BOTTOM; break;
        case ARK_PLACEMENT_TOP_LEFT: dst = Placement::TOP_LEFT; break;
        case ARK_PLACEMENT_TOP_RIGHT: dst = Placement::TOP_RIGHT; break;
        case ARK_PLACEMENT_BOTTOM_LEFT: dst = Placement::BOTTOM_LEFT; break;
        case ARK_PLACEMENT_BOTTOM_RIGHT: dst = Placement::BOTTOM_RIGHT; break;
        case ARK_PLACEMENT_LEFT_TOP: dst = Placement::LEFT_TOP; break;
        case ARK_PLACEMENT_LEFT_BOTTOM: dst = Placement::LEFT_BOTTOM; break;
        case ARK_PLACEMENT_RIGHT_TOP: dst = Placement::RIGHT_TOP; break;
        case ARK_PLACEMENT_RIGHT_BOTTOM: dst = Placement::RIGHT_BOTTOM; break;
        default: LOGE("Unknown transition Ark_Placement type: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<RectHeightStyle>& dst, const Ark_RectHeightStyle& src)
{
    switch (src) {
        case ARK_RECT_HEIGHT_STYLE_TIGHT: dst = RectHeightStyle::TIGHT; break;
        case ARK_RECT_HEIGHT_STYLE_MAX: dst = RectHeightStyle::MAX; break;
        case ARK_RECT_HEIGHT_STYLE_INCLUDE_LINE_SPACE_MIDDLE: dst = RectHeightStyle::INCLUDE_LINE_SPACE_MIDDLE; break;
        case ARK_RECT_HEIGHT_STYLE_INCLUDE_LINE_SPACE_TOP: dst = RectHeightStyle::INCLUDE_LINE_SPACE_TOP; break;
        case ARK_RECT_HEIGHT_STYLE_INCLUDE_LINE_SPACE_BOTTOM: dst = RectHeightStyle::INCLUDE_LINE_SPACE_BOTTOM; break;
        case ARK_RECT_HEIGHT_STYLE_STRUT: dst = RectHeightStyle::STRUT; break;
        default: LOGE("Unexpected enum value in Ark_RectHeightStyle: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<DialogAlignment>& dst, const Ark_DialogAlignment& src)
{
    switch (src) {
        case ARK_DIALOG_ALIGNMENT_TOP: dst = DialogAlignment::TOP; break;
        case ARK_DIALOG_ALIGNMENT_CENTER: dst = DialogAlignment::CENTER; break;
        case ARK_DIALOG_ALIGNMENT_BOTTOM: dst = DialogAlignment::BOTTOM; break;
        case ARK_DIALOG_ALIGNMENT_DEFAULT: dst = DialogAlignment::DEFAULT; break;
        case ARK_DIALOG_ALIGNMENT_TOP_START: dst = DialogAlignment::TOP_START; break;
        case ARK_DIALOG_ALIGNMENT_TOP_END: dst = DialogAlignment::TOP_END; break;
        case ARK_DIALOG_ALIGNMENT_CENTER_START: dst = DialogAlignment::CENTER_START; break;
        case ARK_DIALOG_ALIGNMENT_CENTER_END: dst = DialogAlignment::CENTER_END; break;
        case ARK_DIALOG_ALIGNMENT_BOTTOM_START: dst = DialogAlignment::BOTTOM_START; break;
        case ARK_DIALOG_ALIGNMENT_BOTTOM_END: dst = DialogAlignment::BOTTOM_END; break;
        default: LOGE("Unexpected enum value in Ark_DialogAlignment: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<DialogButtonDirection>& dst, const Ark_DialogButtonDirection& src)
{
    switch (src) {
        case ARK_DIALOG_BUTTON_DIRECTION_AUTO: dst = DialogButtonDirection::AUTO; break;
        case ARK_DIALOG_BUTTON_DIRECTION_HORIZONTAL: dst = DialogButtonDirection::HORIZONTAL; break;
        case ARK_DIALOG_BUTTON_DIRECTION_VERTICAL: dst = DialogButtonDirection::VERTICAL; break;
        default: LOGE("Unexpected enum value in Ark_DialogButtonDirection: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<DialogButtonStyle>& dst, const Ark_DialogButtonStyle& src)
{
    switch (src) {
        case ARK_DIALOG_BUTTON_STYLE_DEFAULT: dst = DialogButtonStyle::DEFAULT; break;
        case ARK_DIALOG_BUTTON_STYLE_HIGHLIGHT: dst = DialogButtonStyle::HIGHTLIGHT; break;
        default: LOGE("Unexpected enum value in Ark_DialogButtonStyle: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<RectWidthStyle>& dst, const Ark_RectWidthStyle& src)
{
    switch (src) {
        case ARK_RECT_WIDTH_STYLE_TIGHT: dst = RectWidthStyle::TIGHT; break;
        case ARK_RECT_WIDTH_STYLE_MAX: dst = RectWidthStyle::MAX; break;
        default: LOGE("Unexpected enum value in Ark_RectWidthStyle: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<RenderMode>& dst, const Ark_RenderMode& src)
{
    switch (src) {
        case ARK_RENDER_MODE_ASYNC_RENDER: dst = RenderMode::ASYNC_RENDER; break;
        case ARK_RENDER_MODE_SYNC_RENDER: dst = RenderMode::SYNC_RENDER; break;
        default: LOGE("Unexpected enum value in Ark_RenderMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ResponseType>& dst, const Ark_ResponseType& src)
{
    switch (src) {
        case ARK_RESPONSE_TYPE_RIGHT_CLICK: dst = ResponseType::RIGHT_CLICK; break;
        case ARK_RESPONSE_TYPE_LONG_PRESS: dst = ResponseType::LONG_PRESS; break;
        default: LOGE("Unexpected enum value in Ark_ResponseType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ResponseType>& dst, const Ark_WebResponseType& src)
{
    switch (src) {
        case ARK_WEB_RESPONSE_TYPE_LONG_PRESS: dst = ResponseType::LONG_PRESS; break;
        default: LOGE("Unexpected enum value in Ark_WebResponseType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TimePickerFormat>& dst, const Ark_TimePickerFormat& src)
{
    switch (src) {
        case ARK_TIME_PICKER_FORMAT_HOUR_MINUTE: dst = TimePickerFormat::HOUR_MINUTE; break;
        case ARK_TIME_PICKER_FORMAT_HOUR_MINUTE_SECOND: dst = TimePickerFormat::HOUR_MINUTE_SECOND; break;
        default: LOGE("Unexpected enum value in Ark_TimePickerFormat: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<HoverModeAreaType>& dst, const Ark_HoverModeAreaType& src)
{
    switch (src) {
        case ARK_HOVER_MODE_AREA_TYPE_TOP_SCREEN: dst = HoverModeAreaType::TOP_SCREEN; break;
        case ARK_HOVER_MODE_AREA_TYPE_BOTTOM_SCREEN: dst = HoverModeAreaType::BOTTOM_SCREEN; break;
        default: LOGE("Unexpected enum value in Ark_HoverModeAreaType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<SessionType>& dst, const Ark_EmbeddedType& src)
{
    switch (src) {
        case ARK_EMBEDDED_TYPE_EMBEDDED_UI_EXTENSION: dst = SessionType::EMBEDDED_UI_EXTENSION; break;
        default: LOGE("Unexpected enum value in Ark_EmbeddedType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<SwipeActionState>& dst, const Ark_SwipeActionState& src)
{
    switch (src) {
        case ARK_SWIPE_ACTION_STATE_COLLAPSED: dst = SwipeActionState::COLLAPSED; break;
        case ARK_SWIPE_ACTION_STATE_EXPANDED: dst = SwipeActionState::EXPANDED; break;
        case ARK_SWIPE_ACTION_STATE_ACTIONING: dst = SwipeActionState::ACTIONING; break;
        default: {
            LOGE("Unexpected enum value in Ark_SwipeActionState: %{public}d", src);
        }
    }
}

template<>
void AssignCast(std::optional<HitTestMode>& dst, const Ark_HitTestMode& src)
{
    switch (src) {
        case ARK_HIT_TEST_MODE_DEFAULT: dst = HitTestMode::HTMDEFAULT; break;
        case ARK_HIT_TEST_MODE_BLOCK: dst = HitTestMode::HTMBLOCK; break;
        case ARK_HIT_TEST_MODE_TRANSPARENT: dst = HitTestMode::HTMTRANSPARENT; break;
        case ARK_HIT_TEST_MODE_NONE: dst = HitTestMode::HTMNONE; break;
        default: {
            LOGE("Unexpected enum value in Ark_HitTestMode: %{public}d", src);
        }
    }
}

template<>
void AssignCast(std::optional<DragBehavior>& dst, const Ark_DragBehavior& src)
{
    switch (src) {
        case ARK_DRAG_BEHAVIOR_COPY: dst = DragBehavior::COPY; break;
        case ARK_DRAG_BEHAVIOR_MOVE: dst = DragBehavior::MOVE; break;
        default: {
            LOGE("Unexpected enum value in Ark_DragBehavior: %{public}d", src);
        }
    }
}
template<>
void AssignCast(std::optional<OHOS::Ace::ScopeType>& dst, const Ark_EffectScope& src)
{
    switch (src) {
        case ARK_EFFECT_SCOPE_LAYER: dst = OHOS::Ace::ScopeType::LAYER; break;
        case ARK_EFFECT_SCOPE_WHOLE: dst = OHOS::Ace::ScopeType::WHOLE; break;
        default: {
            LOGE("Unexpected enum value in Ark_EffectScope: %{public}d", src);
        }
    }
}
template<>
void AssignCast(std::optional<OHOS::Ace::CommonSubType>& dst, const Ark_EffectDirection& src)
{
    switch (src) {
        case ARK_EFFECT_DIRECTION_DOWN: dst = OHOS::Ace::CommonSubType::DOWN; break;
        case ARK_EFFECT_DIRECTION_UP: dst = OHOS::Ace::CommonSubType::UP; break;
        default: {
            LOGE("Unexpected enum value in Ark_EffectDirection: %{public}d", src);
        }
    }
}
template<>
void AssignCast(std::optional<OHOS::Ace::FillStyle>& dst, const Ark_EffectFillStyle& src)
{
    switch (src) {
        case ARK_EFFECT_FILL_STYLE_CUMULATIVE: dst = OHOS::Ace::FillStyle::CUMULATIVE; break;
        case ARK_EFFECT_FILL_STYLE_ITERATIVE: dst = OHOS::Ace::FillStyle::ITERATIVE; break;
        default: {
            LOGE("Unexpected enum value in Ark_EffectFillStyle: %{public}d", src);
        }
    }
}
} // namespace OHOS::Ace::NG::Converter
