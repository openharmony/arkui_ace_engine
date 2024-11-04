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

#include "reverse_converter.h"

namespace OHOS::Ace::NG::Converter {
void AssignArkValue(Ark_AnimationMode& dst, const TabAnimateMode& src)
{
    switch (src) {
        case TabAnimateMode::CONTENT_FIRST: dst = ARK_ANIMATION_MODE_CONTENT_FIRST; break;
        case TabAnimateMode::ACTION_FIRST: dst = ARK_ANIMATION_MODE_ACTION_FIRST; break;
        case TabAnimateMode::NO_ANIMATION: dst = ARK_ANIMATION_MODE_NO_ANIMATION; break;
        default:
            dst = static_cast<Ark_AnimationMode>(-1);
            LOGE("Unexpected enum value in TabAnimateMode: %{public}d", src);
            break;
    }
}

void AssignArkValue(Ark_Axis& dst, const Axis& src)
{
    switch (src) {
        case Axis::VERTICAL: dst = ARK_AXIS_VERTICAL; break;
        case Axis::HORIZONTAL: dst = ARK_AXIS_HORIZONTAL; break;
        default: dst = static_cast<Ark_Axis>(-1);
            LOGE("Unexpected enum value in Axis: %{public}d", src);
    }
}

void AssignArkValue(Ark_BarMode& dst, const TabBarMode& src)
{
    switch (src) {
        case TabBarMode::SCROLLABLE: dst = ARK_BAR_MODE_SCROLLABLE; break;
        case TabBarMode::FIXED: dst = ARK_BAR_MODE_FIXED; break;
        default:
            dst = static_cast<Ark_BarMode>(-1);
            LOGE("Unexpected enum value in TabBarMode: %{public}d", src);
            break;
    }
}

void AssignArkValue(Ark_BarPosition& dst, const BarPosition& src)
{
    switch (src) {
        case BarPosition::START: dst = ARK_BAR_POSITION_START; break;
        case BarPosition::END: dst = ARK_BAR_POSITION_END; break;
        default:
            dst = static_cast<Ark_BarPosition>(-1);
            LOGE("Unexpected enum value in BarPosition: %{public}d", src);
            break;
    }
}

void AssignArkValue(Ark_BarState& dst, const DisplayMode& src)
{
    switch (src) {
        case DisplayMode::OFF: dst = ARK_BAR_STATE_OFF; break;
        case DisplayMode::AUTO: dst = ARK_BAR_STATE_AUTO; break;
        case DisplayMode::ON: dst = ARK_BAR_STATE_ON; break;
        default: dst = static_cast<Ark_BarState>(-1);
            LOGE("Unexpected enum value in DisplayMode: %{public}d", src);
    }
}

void AssignArkValue(Ark_BlurStyle& dst, const BlurStyle& src)
{
    switch (src) {
        case BlurStyle::THIN: dst = ARK_BLUR_STYLE_THIN; break;
        case BlurStyle::REGULAR: dst = ARK_BLUR_STYLE_REGULAR; break;
        case BlurStyle::THICK: dst = ARK_BLUR_STYLE_THICK; break;
        case BlurStyle::BACKGROUND_THIN: dst = ARK_BLUR_STYLE_BACKGROUND_THIN; break;
        case BlurStyle::BACKGROUND_REGULAR: dst = ARK_BLUR_STYLE_BACKGROUND_REGULAR; break;
        case BlurStyle::BACKGROUND_THICK: dst = ARK_BLUR_STYLE_BACKGROUND_THICK; break;
        case BlurStyle::BACKGROUND_ULTRA_THICK: dst = ARK_BLUR_STYLE_BACKGROUND_ULTRA_THICK; break;
        case BlurStyle::NO_MATERIAL: dst = ARK_BLUR_STYLE_NONE; break;
        case BlurStyle::COMPONENT_ULTRA_THIN: dst = ARK_BLUR_STYLE_COMPONENT_ULTRA_THIN; break;
        case BlurStyle::COMPONENT_THIN: dst = ARK_BLUR_STYLE_COMPONENT_THIN; break;
        case BlurStyle::COMPONENT_REGULAR: dst = ARK_BLUR_STYLE_COMPONENT_REGULAR; break;
        case BlurStyle::COMPONENT_THICK: dst = ARK_BLUR_STYLE_COMPONENT_THICK; break;
        case BlurStyle::COMPONENT_ULTRA_THICK: dst = ARK_BLUR_STYLE_COMPONENT_ULTRA_THICK; break;
        default:
            dst = static_cast<Ark_BlurStyle>(-1);
            LOGE("Unexpected enum value in BlurStyle: %{public}d", src);
            break;
    }
}

void AssignArkValue(Ark_EdgeEffect& dst, const EdgeEffect& src)
{
    switch (src) {
        case EdgeEffect::SPRING: dst = ARK_EDGE_EFFECT_SPRING; break;
        case EdgeEffect::FADE: dst = ARK_EDGE_EFFECT_FADE; break;
        case EdgeEffect::NONE: dst = ARK_EDGE_EFFECT_NONE; break;
        default: dst = static_cast<Ark_EdgeEffect>(-1);
            LOGE("Unexpected enum value in EdgeEffect: %{public}d", src);
    }
}

void AssignArkValue(Ark_EnterKeyType& dst, const TextInputAction& src)
{
    switch (src) {
        case TextInputAction::GO: dst = ARK_ENTER_KEY_TYPE_GO; break;
        case TextInputAction::SEARCH: dst = ARK_ENTER_KEY_TYPE_SEARCH; break;
        case TextInputAction::SEND: dst = ARK_ENTER_KEY_TYPE_SEND; break;
        case TextInputAction::NEXT: dst = ARK_ENTER_KEY_TYPE_NEXT; break;
        case TextInputAction::DONE: dst = ARK_ENTER_KEY_TYPE_DONE; break;
        case TextInputAction::PREVIOUS: dst = ARK_ENTER_KEY_TYPE_PREVIOUS; break;
        case TextInputAction::NEW_LINE: dst = ARK_ENTER_KEY_TYPE_NEW_LINE; break;
        default:
            LOGE("Unexpected enum value in TextInputAction: %{public}d", src);
            dst = static_cast<Ark_EnterKeyType>(-1);
    }
}

void AssignArkValue(Ark_FontStyle& dst, const OHOS::Ace::FontStyle& src)
{
    switch (src) {
        case OHOS::Ace::FontStyle::NORMAL: dst = ARK_FONT_STYLE_NORMAL; break;
        case OHOS::Ace::FontStyle::ITALIC: dst = ARK_FONT_STYLE_ITALIC; break;
        default:
            dst = static_cast<Ark_FontStyle>(-1);
            LOGE("Unexpected enum value in FontStyle: %{public}d", src);
            break;
    }
}

void AssignArkValue(Ark_FoldStatus& dst, const FoldStatus& src)
{
    switch (src) {
        case FoldStatus::UNKNOWN: dst = ARK_FOLD_STATUS_FOLD_STATUS_UNKNOWN; break;
        case FoldStatus::EXPAND: dst = ARK_FOLD_STATUS_FOLD_STATUS_EXPANDED; break;
        case FoldStatus::FOLDED: dst = ARK_FOLD_STATUS_FOLD_STATUS_FOLDED; break;
        case FoldStatus::HALF_FOLD: dst = ARK_FOLD_STATUS_FOLD_STATUS_HALF_FOLDED; break;
        default:
            LOGE("Unexpected enum value in FoldStatus: %{public}d", src);
            dst = static_cast<Ark_FoldStatus>(-1);
    }
}

void AssignArkValue(Ark_LayoutStyle& dst, const LayoutStyle& src)
{
    switch (src) {
        case LayoutStyle::ALWAYS_CENTER: dst = ARK_LAYOUT_STYLE_ALWAYS_CENTER; break;
        case LayoutStyle::ALWAYS_AVERAGE_SPLIT: dst = ARK_LAYOUT_STYLE_ALWAYS_AVERAGE_SPLIT; break;
        case LayoutStyle::SPACE_BETWEEN_OR_CENTER: dst = ARK_LAYOUT_STYLE_SPACE_BETWEEN_OR_CENTER; break;
        default:
            dst = static_cast<Ark_LayoutStyle>(-1);
            LOGE("Unexpected enum value in LayoutStyle: %{public}d", src);
            break;
    }
}

void AssignArkValue(Ark_ListItemAlign& dst, const V2::ListItemAlign& src)
{
    switch (src) {
        case V2::ListItemAlign::START: dst = ARK_LIST_ITEM_ALIGN_START; break;
        case V2::ListItemAlign::CENTER: dst = ARK_LIST_ITEM_ALIGN_CENTER; break;
        case V2::ListItemAlign::END: dst = ARK_LIST_ITEM_ALIGN_END; break;
        default: dst = static_cast<Ark_ListItemAlign>(-1);
            LOGE("Unexpected enum value in V2::ListItemAlign: %{public}d", src);
    }
}

void AssignArkValue(Ark_ListItemGroupArea& dst, const ListItemGroupArea& src)
{
    switch (src) {
        case ListItemGroupArea::NONE_AREA: dst = ARK_LIST_ITEM_GROUP_AREA_NONE; break;
        case ListItemGroupArea::IN_LIST_ITEM_AREA: dst = ARK_LIST_ITEM_GROUP_AREA_IN_LIST_ITEM_AREA; break;
        case ListItemGroupArea::IN_HEADER_AREA: dst = ARK_LIST_ITEM_GROUP_AREA_IN_HEADER_AREA; break;
        case ListItemGroupArea::IN_FOOTER_AREA: dst = ARK_LIST_ITEM_GROUP_AREA_IN_FOOTER_AREA; break;
        default: dst = static_cast<Ark_ListItemGroupArea>(-1);
            LOGE("Unexpected enum value in ListItemGroupArea: %{public}d", src);
    }
}

void AssignArkValue(Ark_ListItemGroupStyle& dst, const V2::ListItemGroupStyle& src)
{
    switch (src) {
        case V2::ListItemGroupStyle::NONE: dst = ARK_LIST_ITEM_GROUP_STYLE_NONE; break;
        case V2::ListItemGroupStyle::CARD: dst = ARK_LIST_ITEM_GROUP_STYLE_CARD; break;
        default: dst = static_cast<Ark_ListItemGroupStyle>(-1);
            LOGE("Unexpected enum value in ListItemGroupStyle: %{public}d", src);
    }
}

void AssignArkValue(Ark_ListItemStyle& dst, const V2::ListItemStyle& src)
{
    switch (src) {
        case V2::ListItemStyle::NONE: dst = ARK_LIST_ITEM_STYLE_NONE; break;
        case V2::ListItemStyle::CARD: dst = ARK_LIST_ITEM_STYLE_CARD; break;
        default: dst = static_cast<Ark_ListItemStyle>(-1);
            LOGE("Unexpected enum value in V2::ListItemStyle: %{public}d", src);
    }
}

void AssignArkValue(Ark_LocationButtonOnClickResult& dst, const SecurityComponentHandleResult& src)
{
    switch (src) {
        case SecurityComponentHandleResult::CLICK_SUCCESS:
            dst = ARK_LOCATION_BUTTON_ON_CLICK_RESULT_SUCCESS;
            break;
        case SecurityComponentHandleResult::CLICK_GRANT_FAILED:
            dst = ARK_LOCATION_BUTTON_ON_CLICK_RESULT_TEMPORARY_AUTHORIZATION_FAILED;
            break;
        default:
            dst = static_cast<Ark_LocationButtonOnClickResult>(-1);
            LOGE("Unexpected enum value in SecurityComponentHandleResult: %{public}d", src);
            break;
    }
}

void AssignArkValue(Ark_NavigationMode& dst, const NavigationMode& src)
{
    switch (src) {
        case NavigationMode::STACK: dst = ARK_NAVIGATION_MODE_STACK; break;
        case NavigationMode::SPLIT: dst = ARK_NAVIGATION_MODE_SPLIT; break;
        case NavigationMode::AUTO: dst = ARK_NAVIGATION_MODE_AUTO; break;
        default: {
            dst = static_cast<Ark_NavigationMode>(-1);
            LOGE("Unexpected enum value in NavigationMode: %{public}d", src);
        }
    }
}

void AssignArkValue(Ark_NestedScrollMode& dst, const NestedScrollMode& src)
{
    switch (src) {
        case NestedScrollMode::SELF_ONLY: dst = ARK_NESTED_SCROLL_MODE_SELF_ONLY; break;
        case NestedScrollMode::SELF_FIRST: dst = ARK_NESTED_SCROLL_MODE_SELF_FIRST; break;
        case NestedScrollMode::PARENT_FIRST: dst = ARK_NESTED_SCROLL_MODE_PARENT_FIRST; break;
        case NestedScrollMode::PARALLEL: dst = ARK_NESTED_SCROLL_MODE_PARALLEL; break;
        default: {
            dst = static_cast<Ark_NestedScrollMode>(-1);
            LOGE("Unexpected enum value in NestedScrollMode: %{public}d", src);
        }
    }
}

void AssignArkValue(Ark_NestedScrollOptions& dst, const NestedScrollOptions& src)
{
    dst.scrollForward = ArkValue<Ark_NestedScrollMode>(src.forward);
    dst.scrollBackward = ArkValue<Ark_NestedScrollMode>(src.backward);
}

void AssignArkValue(Ark_PasteButtonOnClickResult& dst, const SecurityComponentHandleResult& src)
{
    switch (src) {
        case SecurityComponentHandleResult::CLICK_SUCCESS:
            dst = ARK_PASTE_BUTTON_ON_CLICK_RESULT_SUCCESS;
            break;
        case SecurityComponentHandleResult::CLICK_GRANT_FAILED:
            dst = ARK_PASTE_BUTTON_ON_CLICK_RESULT_TEMPORARY_AUTHORIZATION_FAILED;
            break;
        default:
            dst = static_cast<Ark_PasteButtonOnClickResult>(-1);
            LOGE("Unexpected enum value in SecurityComponentHandleResult: %{public}d", src);
            break;
    }
}

void AssignArkValue(Ark_SaveButtonOnClickResult& dst, const SecurityComponentHandleResult& src)
{
    switch (src) {
        case SecurityComponentHandleResult::CLICK_SUCCESS:
            dst = ARK_SAVE_BUTTON_ON_CLICK_RESULT_SUCCESS;
            break;
        case SecurityComponentHandleResult::CLICK_GRANT_FAILED:
            dst = ARK_SAVE_BUTTON_ON_CLICK_RESULT_TEMPORARY_AUTHORIZATION_FAILED;
            break;
        default:
            dst = static_cast<Ark_SaveButtonOnClickResult>(-1);
            LOGE("Unexpected enum value in SecurityComponentHandleResult: %{public}d", src);
            break;
    }
}

void AssignArkValue(Ark_ScrollSnapAlign& dst, const V2::ScrollSnapAlign& src)
{
    switch (src) {
        case V2::ScrollSnapAlign::NONE: dst = ARK_SCROLL_SNAP_ALIGN_NONE; break;
        case V2::ScrollSnapAlign::START: dst = ARK_SCROLL_SNAP_ALIGN_START; break;
        case V2::ScrollSnapAlign::CENTER: dst = ARK_SCROLL_SNAP_ALIGN_CENTER; break;
        case V2::ScrollSnapAlign::END: dst = ARK_SCROLL_SNAP_ALIGN_END; break;
        default: dst = static_cast<Ark_ScrollSnapAlign>(-1);
            LOGE("Unexpected enum value in V2::ScrollSnapAlign: %{public}d", src);
    }
}

void AssignArkValue(Ark_ScrollState& dst, const ScrollState& src)
{
    switch (src) {
        case ScrollState::IDLE: dst = ARK_SCROLL_STATE_IDLE; break;
        case ScrollState::SCROLL: dst = ARK_SCROLL_STATE_SCROLL; break;
        case ScrollState::FLING: dst = ARK_SCROLL_STATE_FLING; break;
        default: dst = static_cast<Ark_ScrollState>(-1);
            LOGE("Unexpected enum value in ScrollState: %{public}d", src);
    }
}

void AssignArkValue(Ark_SharedTransitionEffectType& dst, const SharedTransitionEffectType& src)
{
    switch (src) {
        case SharedTransitionEffectType::SHARED_EFFECT_STATIC:
            dst = ARK_SHARED_TRANSITION_EFFECT_TYPE_STATIC; break;
        case SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE:
            dst = ARK_SHARED_TRANSITION_EFFECT_TYPE_EXCHANGE; break;
        default: dst = static_cast<Ark_SharedTransitionEffectType>(-1);
    }
}

void AssignArkValue(Ark_Sticky& dst, const V2::StickyMode& src)
{
    switch (src) {
        case V2::StickyMode::NONE: dst = ARK_STICKY_NONE; break;
        case V2::StickyMode::NORMAL: dst = ARK_STICKY_NORMAL; break;
        case V2::StickyMode::OPACITY: dst = ARK_STICKY_OPACITY; break;
        default: dst = static_cast<Ark_Sticky>(-1);
            LOGE("Unexpected enum value in V2::StickyMode: %{public}d", src);
    }
}

void AssignArkValue(Ark_StickyStyle& dst, const V2::StickyStyle& src)
{
    switch (src) {
        case V2::StickyStyle::NONE: dst = ARK_STICKY_STYLE_NONE; break;
        case V2::StickyStyle::HEADER: dst = ARK_STICKY_STYLE_HEADER; break;
        case V2::StickyStyle::FOOTER: dst = ARK_STICKY_STYLE_FOOTER; break;
        default: dst = static_cast<Ark_StickyStyle>(-1);
            LOGE("Unexpected enum value in V2::StickyStyle: %{public}d", src);
    }
}

void AssignArkValue(Ark_SwipeEdgeEffect& dst, const V2::SwipeEdgeEffect& src)
{
    switch (src) {
        case V2::SwipeEdgeEffect::Spring: dst = ARK_SWIPE_EDGE_EFFECT_SPRING; break;
        case V2::SwipeEdgeEffect::None: dst = ARK_SWIPE_EDGE_EFFECT_NONE; break;
        default: dst = static_cast<Ark_SwipeEdgeEffect>(-1);
            LOGE("Unexpected enum value in V2::SwipeEdgeEffect: %{public}d", src);
    }
}

void AssignArkValue(Ark_TextDecorationStyle& dst, const OHOS::Ace::TextDecorationStyle& src)
{
    switch (src) {
        case OHOS::Ace::TextDecorationStyle::SOLID: dst = ARK_TEXT_DECORATION_STYLE_SOLID; break;
        case OHOS::Ace::TextDecorationStyle::DOUBLE: dst = ARK_TEXT_DECORATION_STYLE_DOUBLE; break;
        case OHOS::Ace::TextDecorationStyle::DOTTED: dst = ARK_TEXT_DECORATION_STYLE_DOTTED; break;
        case OHOS::Ace::TextDecorationStyle::DASHED: dst = ARK_TEXT_DECORATION_STYLE_DASHED; break;
        case OHOS::Ace::TextDecorationStyle::WAVY: dst = ARK_TEXT_DECORATION_STYLE_WAVY; break;
        default: LOGE("Unexpected enum value in Ark_TextDecorationStyle: %{public}d", src);
    }
}

void AssignArkValue(Ark_TextDecorationType& dst, const OHOS::Ace::TextDecoration& src)
{
    switch (src) {
        case OHOS::Ace::TextDecoration::NONE: dst = ARK_TEXT_DECORATION_TYPE_NONE; break;
        case OHOS::Ace::TextDecoration::UNDERLINE: dst = ARK_TEXT_DECORATION_TYPE_UNDERLINE; break;
        case OHOS::Ace::TextDecoration::OVERLINE: dst = ARK_TEXT_DECORATION_TYPE_OVERLINE; break;
        case OHOS::Ace::TextDecoration::LINE_THROUGH: dst = ARK_TEXT_DECORATION_TYPE_LINE_THROUGH; break;
        default:
            dst = static_cast<Ark_TextDecorationType>(-1);
            LOGE("Unexpected enum value in TextDecoration: %{public}d", src);
            break;
    }
}

void AssignArkValue(Ark_RichEditorDeleteDirection& dst, const RichEditorDeleteDirection& src)
{
    switch (src) {
        case OHOS::Ace::NG::RichEditorDeleteDirection::BACKWARD:
            dst = ARK_RICH_EDITOR_DELETE_DIRECTION_BACKWARD;
            break;
        case OHOS::Ace::NG::RichEditorDeleteDirection::FORWARD:
            dst = ARK_RICH_EDITOR_DELETE_DIRECTION_FORWARD;
            break;
        default: dst = static_cast<Ark_RichEditorDeleteDirection>(-1);
    }
}

void AssignArkValue(Ark_TextDeleteDirection& dst, const TextDeleteDirection& src)
{
    switch (src) {
        case TextDeleteDirection::BACKWARD: dst = ARK_TEXT_DELETE_DIRECTION_BACKWARD; break;
        case TextDeleteDirection::FORWARD: dst = ARK_TEXT_DELETE_DIRECTION_FORWARD; break;
        default: dst = static_cast<Ark_TextDeleteDirection>(-1);
    }
}

void AssignArkValue(Ark_SliderChangeMode& dst, const SliderModel::SliderChangeMode& src)
{
    switch (src) {
        case SliderModel::SliderChangeMode::BEGIN: dst = ARK_SLIDER_CHANGE_MODE_BEGIN; break;
        case SliderModel::SliderChangeMode::MOVING: dst = ARK_SLIDER_CHANGE_MODE_MOVING; break;
        case SliderModel::SliderChangeMode::END: dst = ARK_SLIDER_CHANGE_MODE_END; break;
        case SliderModel::SliderChangeMode::CLICK: dst = ARK_SLIDER_CHANGE_MODE_CLICK; break;
        default: dst = static_cast<Ark_SliderChangeMode>(-1);
    }
}

void AssignArkValue(Ark_ScrollAlign& dst, const ScrollAlign& src)
{
    switch (src) {
        case ScrollAlign::START: dst = ARK_SCROLL_ALIGN_START; break;
        case ScrollAlign::CENTER: dst = ARK_SCROLL_ALIGN_CENTER; break;
        case ScrollAlign::END: dst = ARK_SCROLL_ALIGN_END; break;
        case ScrollAlign::AUTO: dst = ARK_SCROLL_ALIGN_AUTO; break;
        default: dst = static_cast<Ark_ScrollAlign>(-1);
    }
}
} // namespace OHOS::Ace::NG::Converter
