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

#include "arkoala_api_generated.h"
#include "reverse_converter.h"

namespace OHOS::Ace::NG::Converter {
void AssignArkValue(Ark_AccessibilityHoverType& dst, const AccessibilityHoverAction& src)
{
    switch (src) {
        case AccessibilityHoverAction::HOVER_ENTER: dst = ARK_ACCESSIBILITY_HOVER_TYPE_HOVER_ENTER; break;
        case AccessibilityHoverAction::HOVER_MOVE: dst = ARK_ACCESSIBILITY_HOVER_TYPE_HOVER_MOVE; break;
        case AccessibilityHoverAction::HOVER_EXIT: dst = ARK_ACCESSIBILITY_HOVER_TYPE_HOVER_EXIT; break;
        case AccessibilityHoverAction::HOVER_CANCEL: dst = ARK_ACCESSIBILITY_HOVER_TYPE_HOVER_CANCEL; break;
        default:
            dst = static_cast<Ark_AccessibilityHoverType>(-1);
            LOGE("Unexpected enum value in Ark_AccessibilityHoverType: %{public}d", src);
            break;
    }
}

void AssignArkValue(Ark_DismissReason& dst, const BindSheetDismissReason& src)
{
    switch (src) {
        case BindSheetDismissReason::BACK_PRESSED: dst = ARK_DISMISS_REASON_PRESS_BACK; break;
        case BindSheetDismissReason::TOUCH_OUTSIDE: dst = ARK_DISMISS_REASON_TOUCH_OUTSIDE; break;
        case BindSheetDismissReason::CLOSE_BUTTON: dst = ARK_DISMISS_REASON_CLOSE_BUTTON; break;
        case BindSheetDismissReason::SLIDE_DOWN: dst = ARK_DISMISS_REASON_SLIDE_DOWN; break;
        default: dst = static_cast<Ark_DismissReason>(-1);
            LOGE("Unexpected enum value in BindSheetDismissReason: %{public}d", src); break;
    }
}

void AssignArkValue(Ark_Edge& dst, const ScrollEdge& src)
{
    switch (src) {
        case ScrollEdge::TOP:
        case ScrollEdge::LEFT: dst = Ark_Edge::ARK_EDGE_TOP;
            break;
        case ScrollEdge::BOTTOM:
        case ScrollEdge::RIGHT: dst = Ark_Edge::ARK_EDGE_BOTTOM;
            break;
        default: dst = static_cast<Ark_Edge>(-1);
            LOGE("Unexpected enum value in ScrollEdge: %{public}d", src);
    }
}

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

void AssignArkValue(Ark_CrownAction& dst, const CrownAction& src)
{
    switch (src) {
        case CrownAction::BEGIN: dst = ARK_CROWN_ACTION_BEGIN; break;
        case CrownAction::UPDATE: dst = ARK_CROWN_ACTION_UPDATE; break;
        case CrownAction::END: dst = ARK_CROWN_ACTION_END; break;
        default:
            dst = INVALID_ENUM_VAL<Ark_CrownAction>;
            LOGE("Unexpected enum value in CrownAction: %{public}d", src);
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

void AssignArkValue(Ark_FontWeight& dst, OHOS::Ace::FontWeight src)
{
    switch (src) {
        case FontWeight::LIGHTER: dst = ARK_FONT_WEIGHT_LIGHTER; break;
        case FontWeight::NORMAL: dst = ARK_FONT_WEIGHT_NORMAL; break;
        case FontWeight::REGULAR: dst = ARK_FONT_WEIGHT_REGULAR; break;
        case FontWeight::MEDIUM: dst = ARK_FONT_WEIGHT_MEDIUM; break;
        case FontWeight::BOLD: dst = ARK_FONT_WEIGHT_BOLD; break;
        case FontWeight::BOLDER: dst = ARK_FONT_WEIGHT_BOLDER; break;
        default:
            LOGE("Unexpected enum value in FontWeight: %{public}d", src);
            dst = static_cast<Ark_FontWeight>(-1);
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

void AssignArkValue(Ark_GestureControl_GestureType &dst, const GestureTypeName &src)
{
    switch (src) {
        case GestureTypeName::TAP_GESTURE: dst = ARK_GESTURE_CONTROL_GESTURE_TYPE_TAP_GESTURE; break;
        case GestureTypeName::LONG_PRESS_GESTURE: dst = ARK_GESTURE_CONTROL_GESTURE_TYPE_LONG_PRESS_GESTURE; break;
        case GestureTypeName::PAN_GESTURE: dst = ARK_GESTURE_CONTROL_GESTURE_TYPE_PAN_GESTURE; break;
        case GestureTypeName::PINCH_GESTURE: dst = ARK_GESTURE_CONTROL_GESTURE_TYPE_PINCH_GESTURE; break;
        case GestureTypeName::SWIPE_GESTURE: dst = ARK_GESTURE_CONTROL_GESTURE_TYPE_SWIPE_GESTURE; break;
        case GestureTypeName::ROTATION_GESTURE: dst = ARK_GESTURE_CONTROL_GESTURE_TYPE_ROTATION_GESTURE; break;
        case GestureTypeName::DRAG: dst = ARK_GESTURE_CONTROL_GESTURE_TYPE_DRAG; break;
        case GestureTypeName::CLICK: dst = ARK_GESTURE_CONTROL_GESTURE_TYPE_CLICK; break;
        default:
            LOGE("Unexpected enum value in GestureTypeName: %{public}d", src);
            dst = static_cast<Ark_GestureControl_GestureType>(-1);
    }
}

void AssignArkValue(Ark_GestureRecognizerState &dst, const NG::RefereeState& src)
{
    switch (src) {
        case NG::RefereeState::READY: dst = ARK_GESTURE_RECOGNIZER_STATE_READY; break;
        case NG::RefereeState::DETECTING: dst = ARK_GESTURE_RECOGNIZER_STATE_DETECTING; break;
        case NG::RefereeState::PENDING: dst = ARK_GESTURE_RECOGNIZER_STATE_PENDING; break;
        case NG::RefereeState::PENDING_BLOCKED: dst = ARK_GESTURE_RECOGNIZER_STATE_BLOCKED; break;
        case NG::RefereeState::SUCCEED_BLOCKED: dst = ARK_GESTURE_RECOGNIZER_STATE_BLOCKED; break;
        case NG::RefereeState::SUCCEED: dst = ARK_GESTURE_RECOGNIZER_STATE_SUCCESSFUL; break;
        case NG::RefereeState::FAIL: dst = ARK_GESTURE_RECOGNIZER_STATE_FAILED; break;
        default:
            dst = INVALID_ENUM_VAL<Ark_GestureRecognizerState>;
            LOGE("Unexpected enum value in RefereeState: %{public}d", src);
    }
}

void AssignArkValue(Ark_IntentionCode& dst, const KeyIntention& src)
{
    switch (src) {
        case KeyIntention::INTENTION_UNKNOWN: dst = ARK_INTENTION_CODE_INTENTION_UNKNOWN; break;
        case KeyIntention::INTENTION_UP: dst = ARK_INTENTION_CODE_INTENTION_UP; break;
        case KeyIntention::INTENTION_DOWN: dst = ARK_INTENTION_CODE_INTENTION_DOWN; break;
        case KeyIntention::INTENTION_LEFT: dst = ARK_INTENTION_CODE_INTENTION_LEFT; break;
        case KeyIntention::INTENTION_RIGHT: dst = ARK_INTENTION_CODE_INTENTION_RIGHT; break;
        case KeyIntention::INTENTION_SELECT: dst = ARK_INTENTION_CODE_INTENTION_SELECT; break;
        case KeyIntention::INTENTION_ESCAPE: dst = ARK_INTENTION_CODE_INTENTION_ESCAPE; break;
        case KeyIntention::INTENTION_BACK: dst = ARK_INTENTION_CODE_INTENTION_BACK; break;
        case KeyIntention::INTENTION_FORWARD: dst = ARK_INTENTION_CODE_INTENTION_FORWARD; break;
        case KeyIntention::INTENTION_MENU: dst = ARK_INTENTION_CODE_INTENTION_MENU; break;
        case KeyIntention::INTENTION_PAGE_UP: dst = ARK_INTENTION_CODE_INTENTION_PAGE_UP; break;
        case KeyIntention::INTENTION_PAGE_DOWN: dst = ARK_INTENTION_CODE_INTENTION_PAGE_DOWN; break;
        case KeyIntention::INTENTION_ZOOM_OUT: dst = ARK_INTENTION_CODE_INTENTION_ZOOM_OUT; break;
        case KeyIntention::INTENTION_ZOOM_IN: dst = ARK_INTENTION_CODE_INTENTION_ZOOM_IN; break;
        default:
            LOGE("Unexpected enum value in KeyIntention: %{public}d", src);
            dst = static_cast<Ark_IntentionCode>(-1);
            break;
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

void AssignArkValue(Ark_LengthUnit& dst, const DimensionUnit& src)
{
    switch (src) {
        case DimensionUnit::PX: dst = ARK_LENGTH_UNIT_PX; break;
        case DimensionUnit::VP: dst = ARK_LENGTH_UNIT_VP; break;
        case DimensionUnit::FP: dst = ARK_LENGTH_UNIT_FP; break;
        case DimensionUnit::PERCENT: dst = ARK_LENGTH_UNIT_PERCENT; break;
        case DimensionUnit::LPX: dst = ARK_LENGTH_UNIT_LPX; break;
        default:
            LOGE("Unexpected enum value in DimensionUnit: %{public}d", src);
            dst = static_cast<Ark_LengthUnit>(-1);
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

void AssignArkValue(Ark_LineBreakStrategy& dst, const LineBreakStrategy& src)
{
    switch (src) {
        case LineBreakStrategy::GREEDY: dst = ARK_LINE_BREAK_STRATEGY_GREEDY; break;
        case LineBreakStrategy::HIGH_QUALITY: dst = ARK_LINE_BREAK_STRATEGY_HIGH_QUALITY; break;
        case LineBreakStrategy::BALANCED: dst = ARK_LINE_BREAK_STRATEGY_BALANCED; break;
        default: dst = static_cast<Ark_LineBreakStrategy>(-1);
            LOGE("Unexpected enum value in LineBreakStrategy: %{public}d", src);
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

void AssignArkValue(Ark_ListItemGroupArea& dst, const int& src)
{
    AssignArkValue(dst, static_cast<ListItemGroupArea>(src));
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

void AssignArkValue(Ark_MessageLevel& dst, const MessageLevel& src)
{
    switch (src) {
        case MessageLevel::DEBUG: dst = ARK_MESSAGE_LEVEL_DEBUG; break;
        case MessageLevel::ERROR: dst = ARK_MESSAGE_LEVEL_ERROR; break;
        case MessageLevel::INFO: dst = ARK_MESSAGE_LEVEL_INFO; break;
        case MessageLevel::LOG: dst = ARK_MESSAGE_LEVEL_LOG; break;
        case MessageLevel::WARN: dst = ARK_MESSAGE_LEVEL_WARN; break;
        default: {
            dst = static_cast<Ark_MessageLevel>(-1);
            LOGE("Unexpected enum value in MessageLevel: %{public}d", src);
        }
    }
}

void AssignArkValue(Ark_MouseAction& dst, const MouseAction& src)
{
    switch (src) {
        case MouseAction::PRESS: dst = ARK_MOUSE_ACTION_PRESS; break;
        case MouseAction::RELEASE: dst = ARK_MOUSE_ACTION_RELEASE; break;
        case MouseAction::MOVE: dst = ARK_MOUSE_ACTION_MOVE; break;
        case MouseAction::HOVER: dst = ARK_MOUSE_ACTION_HOVER; break;
        case MouseAction::CANCEL: dst = ARK_MOUSE_ACTION_CANCEL; break;
        default: {
            dst = static_cast<Ark_MouseAction>(-1);
            LOGE("Unexpected enum value in MouseAction: %{public}d", src);
        }
    }
}

void AssignArkValue(Ark_MouseButton& dst, const MouseButton& src)
{
    switch (src) {
        case MouseButton::LEFT_BUTTON: dst = ARK_MOUSE_BUTTON_LEFT; break;
        case MouseButton::RIGHT_BUTTON: dst = ARK_MOUSE_BUTTON_RIGHT; break;
        case MouseButton::MIDDLE_BUTTON: dst = ARK_MOUSE_BUTTON_MIDDLE; break;
        case MouseButton::BACK_BUTTON: dst = ARK_MOUSE_BUTTON_BACK; break;
        case MouseButton::FORWARD_BUTTON: dst = ARK_MOUSE_BUTTON_FORWARD; break;
        case MouseButton::NONE_BUTTON: dst = ARK_MOUSE_BUTTON_NONE; break;
        default: {
            dst = static_cast<Ark_MouseButton>(-1);
            LOGE("Unexpected enum value in MouseButton: %{public}d", src);
        }
    }
}

void AssignArkValue(Ark_AxisAction& dst, const AxisAction& src)
{
    switch (src) {
        case AxisAction::NONE: dst = ARK_AXIS_ACTION_NONE; break;
        case AxisAction::BEGIN: dst = ARK_AXIS_ACTION_BEGIN; break;
        case AxisAction::UPDATE: dst = ARK_AXIS_ACTION_UPDATE; break;
        case AxisAction::END: dst = ARK_AXIS_ACTION_END; break;
        default: {
            dst = static_cast<Ark_AxisAction>(-1);
            LOGE("Unexpected enum value in AxisAction: %{public}d", src);
        }
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

void AssignArkValue(Ark_NavigationTitleMode& dst, const NavigationTitleMode& src)
{
    switch (src) {
        case NavigationTitleMode::FREE: dst = ARK_NAVIGATION_TITLE_MODE_FREE; break;
        case NavigationTitleMode::FULL: dst = ARK_NAVIGATION_TITLE_MODE_FULL; break;
        case NavigationTitleMode::MINI: dst = ARK_NAVIGATION_TITLE_MODE_MINI; break;
        default: {
            dst = static_cast<Ark_NavigationTitleMode>(-1);
            LOGE("Unexpected enum value in NavigationTitleMode: %{public}d", src);
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
void AssignArkValue(Ark_PanDirection& dst, const PanDirection& src)
{
    switch (src.type) {
        case PanDirection::NONE:
            dst = Ark_PanDirection::ARK_PAN_DIRECTION_NONE;
            break;
        case PanDirection::LEFT:
            dst = Ark_PanDirection::ARK_PAN_DIRECTION_LEFT;
            break;
        case PanDirection::RIGHT:
            dst = Ark_PanDirection::ARK_PAN_DIRECTION_RIGHT;
            break;
        case PanDirection::HORIZONTAL:
            dst = Ark_PanDirection::ARK_PAN_DIRECTION_HORIZONTAL;
            break;
        case PanDirection::UP:
            dst = Ark_PanDirection::ARK_PAN_DIRECTION_UP;
            break;
        case PanDirection::DOWN:
            dst = Ark_PanDirection::ARK_PAN_DIRECTION_DOWN;
            break;
        case PanDirection::VERTICAL:
            dst = Ark_PanDirection::ARK_PAN_DIRECTION_VERTICAL;
            break;
        case PanDirection::ALL:
            dst = Ark_PanDirection::ARK_PAN_DIRECTION_ALL;
            break;
        default:
            dst = static_cast<Ark_PanDirection>(-1);
            LOGE("Unexpected enum value in PanDirection: %{public}d", src.type);
    }
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

void AssignArkValue(Ark_ScrollSource& dst, const ScrollSource& src)
{
    switch (src) {
        case ScrollSource::DRAG: dst = ARK_SCROLL_SOURCE_DRAG; break;
        case ScrollSource::FLING: dst = ARK_SCROLL_SOURCE_FLING; break;
        case ScrollSource::EDGE_EFFECT: dst = ARK_SCROLL_SOURCE_EDGE_EFFECT; break;
        case ScrollSource::OTHER_USER_INPUT: dst = ARK_SCROLL_SOURCE_OTHER_USER_INPUT; break;
        case ScrollSource::SCROLL_BAR: dst = ARK_SCROLL_SOURCE_SCROLL_BAR; break;
        case ScrollSource::SCROLL_BAR_FLING: dst = ARK_SCROLL_SOURCE_SCROLL_BAR_FLING; break;
        case ScrollSource::SCROLLER: dst = ARK_SCROLL_SOURCE_SCROLLER; break;
        case ScrollSource::SCROLLER_ANIMATION: dst = ARK_SCROLL_SOURCE_SCROLLER_ANIMATION; break;
        default:
            dst = static_cast<Ark_ScrollSource>(-1);
            LOGE("Unexpected enum value in ScrollSource: %{public}d", src);
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

void AssignArkValue(Ark_ShadowType& dst, const ShadowType& src)
{
    switch (src) {
        case ShadowType::COLOR: dst = ARK_SHADOW_TYPE_COLOR; break;
        case ShadowType::BLUR: dst = ARK_SHADOW_TYPE_BLUR; break;
        default:
            dst = static_cast<Ark_ShadowType>(-1);
            LOGE("Unexpected enum value in ShadowType: %{public}d", src);
            break;
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

void AssignArkValue(Ark_SheetType& dst, const SheetType& src)
{
    switch (src) {
        case SheetType::SHEET_BOTTOM: dst = ARK_SHEET_TYPE_BOTTOM; break;
        case SheetType::SHEET_CENTER: dst = ARK_SHEET_TYPE_CENTER; break;
        case SheetType::SHEET_POPUP: dst = ARK_SHEET_TYPE_POPUP; break;
        default: dst = static_cast<Ark_SheetType>(-1);
            LOGE("Unexpected enum value in SheetType: %{public}d", src);
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

void AssignArkValue(Ark_SwipeActionState& dst, const SwipeActionState& src)
{
    switch (src) {
        case SwipeActionState::COLLAPSED: dst = ARK_SWIPE_ACTION_STATE_COLLAPSED; break;
        case SwipeActionState::EXPANDED: dst = ARK_SWIPE_ACTION_STATE_EXPANDED; break;
        case SwipeActionState::ACTIONING: dst = ARK_SWIPE_ACTION_STATE_ACTIONING; break;
        default: {
            dst = static_cast<Ark_SwipeActionState>(-1);
            LOGE("Unexpected enum value in SwipeActionState: %{public}d", src);
        }
    }
}

void AssignArkValue(Ark_SwipeDirection& dst, const OHOS::Ace::SwipeDirection& src)
{
    switch (src.type) {
        case SwipeDirection::NONE: dst = ARK_SWIPE_DIRECTION_NONE; break;
        case SwipeDirection::HORIZONTAL: dst = ARK_SWIPE_DIRECTION_HORIZONTAL; break;
        case SwipeDirection::VERTICAL: dst = ARK_SWIPE_DIRECTION_VERTICAL; break;
        case SwipeDirection::ALL: dst = ARK_SWIPE_DIRECTION_ALL; break;
        default: {
            dst = static_cast<Ark_SwipeDirection>(-1);
            LOGE("Unexpected enum value in OHOS::Ace::SwipeDirection: %{public}d", src.type);
        }
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

void AssignArkValue(Ark_StyledStringKey& dst, OHOS::Ace::SpanType src)
{
    switch (src) {
        case Ace::SpanType::Font: dst = ARK_STYLED_STRING_KEY_FONT; break;
        case Ace::SpanType::Decoration: dst = ARK_STYLED_STRING_KEY_DECORATION; break;
        case Ace::SpanType::BaselineOffset: dst = ARK_STYLED_STRING_KEY_BASELINE_OFFSET; break;
        case Ace::SpanType::LetterSpacing: dst = ARK_STYLED_STRING_KEY_LETTER_SPACING; break;
        case Ace::SpanType::TextShadow: dst = ARK_STYLED_STRING_KEY_TEXT_SHADOW; break;
        case Ace::SpanType::LineHeight: dst = ARK_STYLED_STRING_KEY_LINE_HEIGHT; break;
        case Ace::SpanType::BackgroundColor: dst = ARK_STYLED_STRING_KEY_BACKGROUND_COLOR; break;
        case Ace::SpanType::Url: dst = ARK_STYLED_STRING_KEY_URL; break;
        case Ace::SpanType::Gesture: dst = ARK_STYLED_STRING_KEY_GESTURE; break;
        case Ace::SpanType::ParagraphStyle: dst = ARK_STYLED_STRING_KEY_PARAGRAPH_STYLE; break;
        case Ace::SpanType::Image: dst = ARK_STYLED_STRING_KEY_IMAGE; break;
        case Ace::SpanType::CustomSpan: dst = ARK_STYLED_STRING_KEY_CUSTOM_SPAN; break;
        case Ace::SpanType::ExtSpan: dst = ARK_STYLED_STRING_KEY_USER_DATA; break;
        default: LOGE("Unexpected enum value in SpanType: %{public}d", src);
    }
}

void AssignArkValue(Ark_TextAlign& dst, const TextAlign& src)
{
    switch (src) {
        case TextAlign::LEFT: dst = ARK_TEXT_ALIGN_START; break;
        case TextAlign::RIGHT: dst = ARK_TEXT_ALIGN_END; break;
        case TextAlign::CENTER: dst = ARK_TEXT_ALIGN_CENTER; break;
        case TextAlign::JUSTIFY: dst = ARK_TEXT_ALIGN_JUSTIFY; break;
        case TextAlign::START: dst = ARK_TEXT_ALIGN_START; break;
        case TextAlign::END: dst = ARK_TEXT_ALIGN_END; break;
        default:
            dst = static_cast<Ark_TextAlign>(-1);
            LOGE("Unexpected enum value in TextAlign: %{public}d", src);
    }
}
void AssignArkValue(Ark_TextOverflow& dst, const TextOverflow& src)
{
    switch (src) {
        case TextOverflow::NONE: dst = ARK_TEXT_OVERFLOW_NONE; break;
        case TextOverflow::CLIP: dst = ARK_TEXT_OVERFLOW_CLIP; break;
        case TextOverflow::ELLIPSIS: dst = ARK_TEXT_OVERFLOW_ELLIPSIS; break;
        case TextOverflow::MARQUEE: dst = ARK_TEXT_OVERFLOW_MARQUEE; break;
        case TextOverflow::DEFAULT: dst = ARK_TEXT_OVERFLOW_NONE; break;
        default:
            dst = static_cast<Ark_TextOverflow>(-1);
            LOGE("Unexpected enum value in TextOverflow: %{public}d", src);
    }
}
void AssignArkValue(Ark_ImageSpanAlignment& dst, const VerticalAlign& src)
{
    switch (src) {
        case VerticalAlign::TOP: dst = ARK_IMAGE_SPAN_ALIGNMENT_TOP; break;
        case VerticalAlign::CENTER: dst = ARK_IMAGE_SPAN_ALIGNMENT_CENTER; break;
        case VerticalAlign::BOTTOM: dst = ARK_IMAGE_SPAN_ALIGNMENT_BOTTOM; break;
        case VerticalAlign::BASELINE: dst = ARK_IMAGE_SPAN_ALIGNMENT_BASELINE; break;
        default:
            dst = INVALID_ENUM_VAL<Ark_ImageSpanAlignment>;
            LOGE("Unexpected enum value in Ark_ImageSpanAlignment: %{public}d", static_cast<int>(src));
    }
}

void AssignArkValue(Ark_ImageFit& dst, const ImageFit& src)
{
    switch (src) {
        case ImageFit::CONTAIN: dst = ARK_IMAGE_FIT_CONTAIN; break;
        case ImageFit::COVER: dst = ARK_IMAGE_FIT_COVER; break;
        case ImageFit::FITWIDTH: dst = ARK_IMAGE_FIT_AUTO; break;
        case ImageFit::FILL: dst = ARK_IMAGE_FIT_FILL; break;
        case ImageFit::SCALE_DOWN: dst = ARK_IMAGE_FIT_SCALE_DOWN; break;
        case ImageFit::NONE: dst = ARK_IMAGE_FIT_NONE; break;
        case ImageFit::TOP_LEFT: dst = ARK_IMAGE_FIT_TOP_START; break;
        case ImageFit::TOP: dst = ARK_IMAGE_FIT_TOP; break;
        case ImageFit::TOP_END: dst = ARK_IMAGE_FIT_TOP_END; break;
        case ImageFit::START: dst = ARK_IMAGE_FIT_START; break;
        case ImageFit::CENTER: dst = ARK_IMAGE_FIT_CENTER; break;
        case ImageFit::END: dst = ARK_IMAGE_FIT_END; break;
        case ImageFit::BOTTOM_START: dst = ARK_IMAGE_FIT_BOTTOM_START; break;
        case ImageFit::BOTTOM: dst = ARK_IMAGE_FIT_BOTTOM; break;
        case ImageFit::BOTTOM_END: dst = ARK_IMAGE_FIT_BOTTOM_END; break;
        default:
            dst = INVALID_ENUM_VAL<Ark_ImageFit>;
            LOGE("Unexpected enum value in Ark_ImageFit: %{public}d", static_cast<int>(src));
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
        default: {
            dst = static_cast<Ark_TextDecorationStyle>(-1);
            LOGE("Unexpected enum value in Ark_TextDecorationStyle: %{public}d", src);
        }
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

void AssignArkValue(Ark_SourceType& dst, const SourceType& src)
{
    switch (src) {
        case SourceType::NONE: dst = Ark_SourceType::ARK_SOURCE_TYPE_UNKNOWN; break;
        case SourceType::MOUSE: dst = Ark_SourceType::ARK_SOURCE_TYPE_MOUSE; break;
        case SourceType::TOUCH: dst = Ark_SourceType::ARK_SOURCE_TYPE_TOUCH_SCREEN; break;
        default: dst = static_cast<Ark_SourceType>(-1);
            LOGE("Unexpected enum value in SourceType: %{public}d", src);
    }
}

void AssignArkValue(Ark_SourceTool& dst, const SourceTool& src)
{
    switch (src) {
        case SourceTool::UNKNOWN: dst = Ark_SourceTool::ARK_SOURCE_TOOL_UNKNOWN; break;
        case SourceTool::FINGER: dst = Ark_SourceTool::ARK_SOURCE_TOOL_FINGER; break;
        case SourceTool::PEN: dst = Ark_SourceTool::ARK_SOURCE_TOOL_PEN; break;
        case SourceTool::MOUSE: dst = Ark_SourceTool::ARK_SOURCE_TOOL_MOUSE; break;
        case SourceTool::TOUCHPAD: dst = Ark_SourceTool::ARK_SOURCE_TOOL_TOUCHPAD; break;
        case SourceTool::JOYSTICK: dst = Ark_SourceTool::ARK_SOURCE_TOOL_JOYSTICK; break;
        default: dst = static_cast<Ark_SourceTool>(-1);
            LOGE("Unexpected enum value in SourceTool: %{public}d", src);
    }
}

void AssignArkValue(Ark_TouchType& dst, const TouchType& src)
{
    switch (src) {
        case TouchType::DOWN: dst = Ark_TouchType::ARK_TOUCH_TYPE_DOWN; break;
        case TouchType::UP: dst = Ark_TouchType::ARK_TOUCH_TYPE_UP; break;
        case TouchType::MOVE: dst = Ark_TouchType::ARK_TOUCH_TYPE_MOVE; break;
        case TouchType::CANCEL: dst = Ark_TouchType::ARK_TOUCH_TYPE_CANCEL; break;
        default: dst = static_cast<Ark_TouchType>(-1);
            LOGE("Unexpected enum value in TouchType: %{public}zu", src);
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

void AssignArkValue(Ark_TransitionEdge& dst, const TransitionEdge& src)
{
    switch (src) {
        case TransitionEdge::TOP: dst = ARK_TRANSITION_EDGE_TOP; break;
        case TransitionEdge::BOTTOM: dst = ARK_TRANSITION_EDGE_BOTTOM; break;
        case TransitionEdge::START: dst = ARK_TRANSITION_EDGE_START; break;
        case TransitionEdge::END: dst = ARK_TRANSITION_EDGE_END; break;
        default: dst = static_cast<Ark_TransitionEdge>(-1);
    }
}

void AssignArkValue(Ark_RenderProcessNotRespondingReason& dst, const RenderProcessNotRespondingReason& src)
{
    switch (src) {
        case RenderProcessNotRespondingReason::INPUT_TIMEOUT: dst =
            ARK_RENDER_PROCESS_NOT_RESPONDING_REASON_INPUT_TIMEOUT; break;
        case RenderProcessNotRespondingReason::NAVIGATION_COMMIT_TIMEOUT: dst =
            ARK_RENDER_PROCESS_NOT_RESPONDING_REASON_NAVIGATION_COMMIT_TIMEOUT; break;
        default: dst = static_cast<Ark_RenderProcessNotRespondingReason>(-1);
            LOGE("Unexpected enum value in RenderProcessNotRespondingReason: %{public}d", src);
    }
}

void AssignArkValue(Ark_RenderExitReason& dst, const RenderExitReason& src)
{
    switch (src) {
        case RenderExitReason::ABNORMAL_TERMINATION: dst = ARK_RENDER_EXIT_REASON_PROCESS_ABNORMAL_TERMINATION; break;
        case RenderExitReason::WAS_KILLED: dst = ARK_RENDER_EXIT_REASON_PROCESS_WAS_KILLED; break;
        case RenderExitReason::CRASHED: dst = ARK_RENDER_EXIT_REASON_PROCESS_CRASHED; break;
        case RenderExitReason::OOM: dst = ARK_RENDER_EXIT_REASON_PROCESS_OOM; break;
        case RenderExitReason::EXIT_UNKNOWN: dst = ARK_RENDER_EXIT_REASON_PROCESS_EXIT_UNKNOWN; break;
        default: dst = static_cast<Ark_RenderExitReason>(-1);
            LOGE("Unexpected enum value in RenderExitReason: %{public}d", src);
    }
}

void AssignArkValue(Ark_KeyType& dst, const KeyAction& src)
{
    switch (src) {
        case KeyAction::DOWN: dst = Ark_KeyType::ARK_KEY_TYPE_DOWN; break;
        case KeyAction::UP: dst = Ark_KeyType::ARK_KEY_TYPE_UP; break;
        default: dst = static_cast<Ark_KeyType>(-1);
            LOGE("Unexpected enum value in KeyAction: %{public}d", src);
    }
}

void AssignArkValue(Ark_KeySource& dst, const SourceType& src)
{
    switch (src) {
        case SourceType::NONE: dst = Ark_KeySource::ARK_KEY_SOURCE_UNKNOWN; break;
        case SourceType::KEYBOARD: dst = Ark_KeySource::ARK_KEY_SOURCE_KEYBOARD; break;
        default: dst = static_cast<Ark_KeySource>(-1);
            LOGE("Unexpected enum value in SourceType: %{public}d", src);
    }
}

void AssignArkValue(Ark_SslError& dst, const SslError& src)
{
    switch (src) {
        case SslError::INVALID: dst = Ark_SslError::ARK_SSL_ERROR_INVALID; break;
        case SslError::HOST_MISMATCH: dst = Ark_SslError::ARK_SSL_ERROR_HOST_MISMATCH; break;
        case SslError::DATE_INVALID: dst = Ark_SslError::ARK_SSL_ERROR_DATE_INVALID; break;
        case SslError::UNTRUSTED: dst = Ark_SslError::ARK_SSL_ERROR_UNTRUSTED; break;
        default: dst = static_cast<Ark_SslError>(-1);
            LOGE("Unexpected enum value in SslError: %{public}d", src);
    }
}

void AssignArkValue(Ark_NativeEmbedStatus& dst, const NativeEmbedStatus& src)
{
    switch (src) {
        case NativeEmbedStatus::CREATE: dst = Ark_NativeEmbedStatus::ARK_NATIVE_EMBED_STATUS_CREATE; break;
        case NativeEmbedStatus::UPDATE: dst = Ark_NativeEmbedStatus::ARK_NATIVE_EMBED_STATUS_UPDATE; break;
        case NativeEmbedStatus::DESTROY: dst = Ark_NativeEmbedStatus::ARK_NATIVE_EMBED_STATUS_DESTROY; break;
        case NativeEmbedStatus::ENTER_BFCACHE: dst =
            Ark_NativeEmbedStatus::ARK_NATIVE_EMBED_STATUS_ENTER_BFCACHE; break;
        case NativeEmbedStatus::LEAVE_BFCACHE: dst =
            Ark_NativeEmbedStatus::ARK_NATIVE_EMBED_STATUS_LEAVE_BFCACHE; break;
        default: dst = static_cast<Ark_NativeEmbedStatus>(-1);
            LOGE("Unexpected enum value in NativeEmbedStatus: %{public}d", src);
    }
}

void AssignArkValue(Ark_MenuPolicy& dst, const MenuPolicy& src)
{
    switch (src) {
        case MenuPolicy::DEFAULT: dst = ARK_MENU_POLICY_DEFAULT; break;
        case MenuPolicy::HIDE: dst = ARK_MENU_POLICY_HIDE; break;
        case MenuPolicy::SHOW: dst = ARK_MENU_POLICY_SHOW; break;
        default: dst = static_cast<Ark_MenuPolicy>(-1);
    }
}

void AssignArkValue(Ark_DragBehavior& dst, const DragBehavior& src)
{
    switch (src) {
        case DragBehavior::UNKNOWN:
        case DragBehavior::COPY: dst = ARK_DRAG_BEHAVIOR_COPY; break;
        case DragBehavior::MOVE: dst = ARK_DRAG_BEHAVIOR_MOVE; break;
        default:
            dst = static_cast<Ark_DragBehavior>(DragBehavior::UNKNOWN);
            LOGE("Unexpected enum value in DragBehavior: %{public}d", src);
            break;
    }
}

void AssignArkValue(Ark_WordBreak& dst, const OHOS::Ace::WordBreak& src)
{
    switch (src) {
        case WordBreak::NORMAL: dst = ARK_WORD_BREAK_NORMAL; break;
        case WordBreak::BREAK_ALL: dst = ARK_WORD_BREAK_BREAK_ALL; break;
        case WordBreak::BREAK_WORD: dst = ARK_WORD_BREAK_BREAK_WORD; break;
        default:
            dst = static_cast<Ark_WordBreak>(-1);
            LOGE("Unexpected enum value in WordBreak: %{public}d", src);
    }
}

void AssignArkValue(Ark_EffectScope& dst, const OHOS::Ace::ScopeType& src)
{
    switch (src) {
        case OHOS::Ace::ScopeType::LAYER: dst = ARK_EFFECT_SCOPE_LAYER; break;
        case OHOS::Ace::ScopeType::WHOLE: dst = ARK_EFFECT_SCOPE_WHOLE; break;
        default: dst = static_cast<Ark_EffectScope>(-1);
    }
}

void AssignArkValue(Ark_EffectDirection& dst, const OHOS::Ace::CommonSubType& src)
{
    switch (src) {
        case OHOS::Ace::CommonSubType::DOWN: dst = ARK_EFFECT_DIRECTION_DOWN; break;
        case OHOS::Ace::CommonSubType::UP: dst = ARK_EFFECT_DIRECTION_UP; break;
        default: dst = static_cast<Ark_EffectDirection>(-1);
    }
}

void AssignArkValue(Ark_SelectStatus& dst, const int32_t& src)
{
    const int32_t valueAll = 0;
    const int32_t valuePart = 1;
    const int32_t valueNone = 2;
    switch (src) {
        case valueAll: dst = ARK_SELECT_STATUS_ALL; break;
        case valuePart: dst = ARK_SELECT_STATUS_PART; break;
        case valueNone: dst = ARK_SELECT_STATUS_NONE; break;
        default: dst = static_cast<Ark_SelectStatus>(-1);
    }
}
} // namespace OHOS::Ace::NG::Converter
