/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "node/event_converter.h"

#include <cstdint>

#include "native_node.h"
#include "node/gesture_impl.h"
#include "node/native_compatible.h"
#include "node/node_model.h"
#include "securec.h"

#include "base/log/log_wrapper.h"
#include "core/event/touch_event.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NodeModel {
namespace {
constexpr int32_t ORIGIN_TOUCH_ACTION_DOWN = 0;
constexpr int32_t ORIGIN_TOUCH_ACTION_UP = 1;
constexpr int32_t ORIGIN_TOUCH_ACTION_MOVE = 2;
constexpr int32_t ORIGIN_TOUCH_ACTION_CANCEL = 3;
constexpr int32_t ORIGIN_INPUT_EVENT_TOOL_TYPE_FINGER = 1;
constexpr int32_t ORIGIN_INPUT_EVENT_TOOL_TYPE_PEN = 2;
constexpr int32_t ORIGIN_INPUT_EVENT_TOOL_TYPE_MOUSE = 7;
constexpr int32_t ORIGIN_INPUT_EVENT_TOOL_TYPE_TOUCHPAD = 9;

void ConvertToTouchEvent(const ArkUITouchEvent& origin, ArkUI_NodeTouchEvent& event)
{
    memset_s(&event, sizeof(ArkUI_NodeTouchEvent), 0, sizeof(ArkUI_NodeTouchEvent));
    event.actionTouch.id = origin.actionTouchPoint.id;
    event.actionTouch.nodeX = origin.actionTouchPoint.nodeX;
    event.actionTouch.nodeY = origin.actionTouchPoint.nodeY;
    event.actionTouch.windowX = origin.actionTouchPoint.windowX;
    event.actionTouch.windowY = origin.actionTouchPoint.windowY;
    event.actionTouch.screenX = origin.actionTouchPoint.screenX;
    event.actionTouch.screenY = origin.actionTouchPoint.screenY;
    event.actionTouch.contactAreaHeight = origin.actionTouchPoint.contactAreaHeight;
    event.actionTouch.contactAreaWidth = origin.actionTouchPoint.contactAreaWidth;
    event.actionTouch.toolHeight = origin.actionTouchPoint.toolHeight;
    event.actionTouch.toolWidth = origin.actionTouchPoint.toolWidth;
    event.actionTouch.toolType = static_cast<ArkUI_NodeToolType>(origin.actionTouchPoint.toolType);
    event.actionTouch.pressure = origin.actionTouchPoint.pressure;
    event.actionTouch.tiltX = origin.actionTouchPoint.tiltX;
    event.actionTouch.tiltY = origin.actionTouchPoint.tiltY;
    event.actionTouch.rawX = origin.actionTouchPoint.rawX;
    event.actionTouch.rawY = origin.actionTouchPoint.rawY;

    event.timeStamp = origin.timeStamp;
    if (origin.sourceType == UI_INPUT_EVENTT_SOURCE_TYPE_TOUCH_SCREEN) {
        event.sourceType = NODE_SOURCE_TYPE_TOUCH_SCREEN;
    } else {
        event.sourceType = NODE_SOURCE_TYPE_UNKNOWN;
    }

    switch (origin.action) {
        case static_cast<int32_t>(TouchType::DOWN):
            event.action = NODE_ACTION_DOWN;
            break;
        // TouchType::UP
        case static_cast<int32_t>(TouchType::UP):
            event.action = NODE_ACTION_UP;
            break;
            // TouchType::MOVE
        case static_cast<int32_t>(TouchType::MOVE):
            event.action = NODE_ACTION_MOVE;
            break;
        case static_cast<int32_t>(TouchType::CANCEL):
            event.action = NODE_ACTION_CANCEL;
            break;
        default:
            event.action = static_cast<ArkUI_NodeTouchEventAction>(-1);
    }
    static ArkUI_Uint32 touchPointSize = origin.touchPointSize;
    static ArkUITouchPoint* touchPoints = origin.touchPointes;
    auto getTouchPoints = [](ArkUI_NodeTouchPoint** points) -> ArkUI_Int32 {
        *points = new ArkUI_NodeTouchPoint[touchPointSize] {};
        for (uint32_t index = 0; index < touchPointSize; index++) {
            (*points)[index].id = touchPoints[index].id;
            (*points)[index].nodeX = touchPoints[index].nodeX;
            (*points)[index].nodeY = touchPoints[index].nodeY;
            (*points)[index].windowX = touchPoints[index].windowX;
            (*points)[index].windowY = touchPoints[index].windowY;
            (*points)[index].screenX = touchPoints[index].screenX;
            (*points)[index].screenY = touchPoints[index].screenY;
            (*points)[index].contactAreaHeight = touchPoints[index].contactAreaHeight;
            (*points)[index].contactAreaWidth = touchPoints[index].contactAreaWidth;
            (*points)[index].toolHeight = touchPoints[index].toolHeight;
            (*points)[index].toolWidth = touchPoints[index].toolWidth;
            (*points)[index].toolType = static_cast<ArkUI_NodeToolType>(touchPoints[index].toolType);
            (*points)[index].pressure = touchPoints[index].pressure;
            (*points)[index].tiltX = touchPoints[index].tiltX;
            (*points)[index].tiltY = touchPoints[index].tiltY;
            (*points)[index].rawX = touchPoints[index].rawX;
            (*points)[index].rawY = touchPoints[index].rawY;
        }
        return touchPointSize;
    };
    event.getTouches = getTouchPoints;
}

} // namespace
ArkUI_Int32 ConvertOriginEventType(ArkUI_NodeEventType type, int32_t nodeType)
{
    auto arkUINodeType = static_cast<ArkUI_NodeType>(nodeType);
    switch (type) {
        case NODE_TEXT_INPUT_ON_CHANGE:
            return ON_TEXT_INPUT_CHANGE;
        case NODE_SCROLL_EVENT_ON_SCROLL:
            if (arkUINodeType == ARKUI_NODE_LIST) {
                return ON_LIST_SCROLL;
            }
            return ON_SCROLL;
        case NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN:
            if (arkUINodeType == ARKUI_NODE_LIST) {
                return ON_LIST_SCROLL_FRAME_BEGIN;
            } else if (arkUINodeType == ARKUI_NODE_WATER_FLOW) {
                return ON_WATER_FLOW_SCROLL_FRAME_BEGIN;
            }
            return ON_SCROLL_FRAME_BEGIN;
        case NODE_SCROLL_EVENT_ON_SCROLL_START:
            if (arkUINodeType == ARKUI_NODE_LIST) {
                return ON_LIST_SCROLL_START;
            } else if (arkUINodeType == ARKUI_NODE_WATER_FLOW) {
                return ON_WATER_FLOW_SCROLL_START;
            }
            return ON_SCROLL_START;
        case NODE_SCROLL_EVENT_ON_SCROLL_STOP:
            if (arkUINodeType == ARKUI_NODE_LIST) {
                return ON_LIST_SCROLL_STOP;
            } else if (arkUINodeType == ARKUI_NODE_WATER_FLOW) {
                return ON_WATER_FLOW_SCROLL_STOP;
            }
            return ON_SCROLL_STOP;
        case NODE_EVENT_ON_APPEAR:
            return ON_APPEAR;
        case NODE_EVENT_ON_DISAPPEAR:
            return ON_DISAPPEAR;
        case NODE_EVENT_ON_AREA_CHANGE:
            return ON_AREA_CHANGE;
        case NODE_TEXT_AREA_ON_CHANGE:
            return ON_TEXTAREA_CHANGE;
        case NODE_ON_FOCUS:
            return ON_FOCUS;
        case NODE_ON_BLUR:
            return ON_BLUR;
        case NODE_TEXT_INPUT_ON_SUBMIT:
            return ON_TEXT_INPUT_SUBMIT;
        case NODE_REFRESH_STATE_CHANGE:
            return ON_REFRESH_STATE_CHANGE;
        case NODE_REFRESH_ON_REFRESH:
            return ON_REFRESH_REFRESHING;
        case NODE_SCROLL_EVENT_ON_SCROLL_EDGE:
            return ON_SCROLL_EDGE;
        case NODE_TOGGLE_ON_CHANGE:
            return ON_TOGGLE_CHANGE;
        case NODE_IMAGE_ON_COMPLETE:
            return ON_IMAGE_COMPLETE;
        case NODE_IMAGE_ON_ERROR:
            return ON_IMAGE_ERROR;
        case NODE_IMAGE_ON_SVG_PLAY_FINISH:
            return ON_IMAGE_SVG_PLAY_FINISH;
        case NODE_TEXT_PICKER_EVENT_ON_CHANGE:
            return ON_TEXT_PICKER_CHANGE;
        case NODE_DATE_PICKER_EVENT_ON_DATE_CHANGE:
            return ON_DATE_PICKER_DATE_CHANGE;
        case NODE_TIME_PICKER_EVENT_ON_CHANGE:
            return ON_TIME_PICKER_CHANGE;
        case NODE_CALENDAR_PICKER_EVENT_ON_CHANGE:
            return ON_CALENDAR_PICKER_CHANGE;
        case NODE_TOUCH_EVENT:
            return ON_TOUCH;
        case NODE_ON_CLICK:
            return ON_CLICK;
        case NODE_CHECKBOX_EVENT_ON_CHANGE:
            return ON_CHECKBOX_CHANGE;
        case NODE_SLIDER_EVENT_ON_CHANGE:
            return ON_SLIDER_CHANGE;
        case NODE_TEXT_INPUT_ON_CUT:
            return ON_TEXT_INPUT_CUT;
        case NODE_TEXT_INPUT_ON_PASTE:
            return ON_TEXT_INPUT_PASTE;
        case NODE_TEXT_INPUT_ON_TEXT_SELECTION_CHANGE:
            return ON_TEXT_INPUT_TEXT_SELECTION_CHANGE;
        case NODE_TEXT_INPUT_ON_EDIT_CHANGE:
            return ON_TEXT_INPUT_EDIT_CHANGE;
        case NODE_TEXT_INPUT_ON_INPUT_FILTER_ERROR:
            return ON_TEXT_INPUT_INPUT_FILTER_ERROR;
        case NODE_TEXT_INPUT_ON_CONTENT_SCROLL:
            return ON_TEXT_INPUT_CONTENT_SCROLL;
        case NODE_TEXT_AREA_ON_INPUT_FILTER_ERROR:
            return ON_TEXT_AREA_INPUT_FILTER_ERROR;
        case NODE_TEXT_AREA_ON_EDIT_CHANGE:
            return ON_TEXTAREA_EDIT_CHANGE;
        case NODE_TEXT_AREA_ON_SUBMIT:
            return ON_TEXTAREA_ON_SUBMIT;
        case NODE_TEXT_AREA_ON_PASTE:
            return ON_TEXTAREA_PASTE;
        case NODE_TEXT_AREA_ON_TEXT_SELECTION_CHANGE:
            return ON_TEXTAREA_TEXT_SELECTION_CHANGE;
        case NODE_TEXT_AREA_ON_CONTENT_SCROLL:
            return ON_TEXT_AREA_CONTENT_SCROLL;
        case NODE_SWIPER_EVENT_ON_CHANGE:
            return ON_SWIPER_CHANGE;
        case NODE_SWIPER_EVENT_ON_ANIMATION_START:
            return ON_SWIPER_ANIMATION_START;
        case NODE_SWIPER_EVENT_ON_ANIMATION_END:
            return ON_SWIPER_ANIMATION_END;
        case NODE_SWIPER_EVENT_ON_GESTURE_SWIPE:
            return ON_SWIPER_GESTURE_SWIPE;
        case NODE_WATER_FLOW_ON_WILL_SCROLL:
            return ON_WATER_FLOW_WILL_SCROLL;
        case NODE_ON_TOUCH_INTERCEPT:
            return ON_TOUCH_INTERCEPT;
        case NODE_SCROLL_EVENT_ON_REACH_START:
            if (arkUINodeType == ARKUI_NODE_LIST) {
                return ON_LIST_REACH_START;
            } else if (arkUINodeType == ARKUI_NODE_WATER_FLOW) {
                return ON_WATER_FLOW_REACH_START;
            }
            return ON_SCROLL_REACH_START;
        case NODE_SCROLL_EVENT_ON_REACH_END:
            if (arkUINodeType == ARKUI_NODE_LIST) {
                return ON_LIST_REACH_END;
            } else if (arkUINodeType == ARKUI_NODE_WATER_FLOW) {
                return ON_WATER_FLOW_REACH_END;
            }
            return ON_SCROLL_REACH_END;
        case NODE_WATER_FLOW_ON_DID_SCROLL:
            return ON_WATER_FLOW_DID_SCROLL;
        case NODE_LIST_ON_SCROLL_INDEX:
            return ON_LIST_SCROLL_INDEX;
        case NODE_WATER_FLOW_ON_SCROLL_INDEX:
            return ON_WATER_FLOW_SCROLL_INDEX;
        case NODE_TEXT_ON_DETECT_RESULT_UPDATE:
            return ON_DETECT_RESULT_UPDATE;
        default:
            return -1;
    }
}

ArkUI_Int32 ConvertToNodeEventType(ArkUIEventSubKind type)
{
    switch (type) {
        case ON_TEXT_INPUT_CHANGE:
            return NODE_TEXT_INPUT_ON_CHANGE;
        case ON_SCROLL:
            return NODE_SCROLL_EVENT_ON_SCROLL;
        case ON_SCROLL_FRAME_BEGIN:
            return NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN;
        case ON_SCROLL_START:
            return NODE_SCROLL_EVENT_ON_SCROLL_START;
        case ON_SCROLL_STOP:
            return NODE_SCROLL_EVENT_ON_SCROLL_STOP;
        case ON_APPEAR:
            return NODE_EVENT_ON_APPEAR;
        case ON_DISAPPEAR:
            return NODE_EVENT_ON_DISAPPEAR;
        case ON_AREA_CHANGE:
            return NODE_EVENT_ON_AREA_CHANGE;
        case ON_TEXTAREA_CHANGE:
            return NODE_TEXT_AREA_ON_CHANGE;
        case ON_FOCUS:
            return NODE_ON_FOCUS;
        case ON_BLUR:
            return NODE_ON_BLUR;
        case ON_TEXT_INPUT_SUBMIT:
            return NODE_TEXT_INPUT_ON_SUBMIT;
        case ON_REFRESH_STATE_CHANGE:
            return NODE_REFRESH_STATE_CHANGE;
        case ON_REFRESH_REFRESHING:
            return NODE_REFRESH_ON_REFRESH;
        case ON_SCROLL_EDGE:
            return NODE_SCROLL_EVENT_ON_SCROLL_EDGE;
        case ON_TOGGLE_CHANGE:
            return NODE_TOGGLE_ON_CHANGE;
        case ON_IMAGE_COMPLETE:
            return NODE_IMAGE_ON_COMPLETE;
        case ON_IMAGE_ERROR:
            return NODE_IMAGE_ON_ERROR;
        case ON_IMAGE_SVG_PLAY_FINISH:
            return NODE_IMAGE_ON_SVG_PLAY_FINISH;
        case ON_TEXT_PICKER_CHANGE:
            return NODE_TEXT_PICKER_EVENT_ON_CHANGE;
        case ON_DATE_PICKER_DATE_CHANGE:
            return NODE_DATE_PICKER_EVENT_ON_DATE_CHANGE;
        case ON_TIME_PICKER_CHANGE:
            return NODE_TIME_PICKER_EVENT_ON_CHANGE;
        case ON_CALENDAR_PICKER_CHANGE:
            return NODE_CALENDAR_PICKER_EVENT_ON_CHANGE;
        case ON_TOUCH:
            return NODE_TOUCH_EVENT;
        case ON_CLICK:
            return NODE_ON_CLICK;
        case ON_CHECKBOX_CHANGE:
            return NODE_CHECKBOX_EVENT_ON_CHANGE;
        case ON_SLIDER_CHANGE:
            return NODE_SLIDER_EVENT_ON_CHANGE;
        case ON_TEXT_INPUT_CUT:
            return NODE_TEXT_INPUT_ON_CUT;
        case ON_TEXT_INPUT_PASTE:
            return NODE_TEXT_INPUT_ON_PASTE;
        case ON_TEXT_INPUT_TEXT_SELECTION_CHANGE:
            return NODE_TEXT_INPUT_ON_TEXT_SELECTION_CHANGE;
        case ON_TEXT_INPUT_EDIT_CHANGE:
            return NODE_TEXT_INPUT_ON_EDIT_CHANGE;
        case ON_TEXT_INPUT_INPUT_FILTER_ERROR:
            return NODE_TEXT_INPUT_ON_INPUT_FILTER_ERROR;
        case ON_TEXT_INPUT_CONTENT_SCROLL:
            return NODE_TEXT_INPUT_ON_CONTENT_SCROLL;
        case ON_TEXT_AREA_INPUT_FILTER_ERROR:
            return NODE_TEXT_AREA_ON_INPUT_FILTER_ERROR;
        case ON_TEXTAREA_EDIT_CHANGE:
            return NODE_TEXT_AREA_ON_EDIT_CHANGE;
        case ON_TEXTAREA_ON_SUBMIT:
            return NODE_TEXT_AREA_ON_SUBMIT;
        case ON_TEXTAREA_PASTE:
            return NODE_TEXT_AREA_ON_PASTE;
        case ON_TEXTAREA_TEXT_SELECTION_CHANGE:
            return NODE_TEXT_AREA_ON_TEXT_SELECTION_CHANGE;
        case ON_TEXT_AREA_CONTENT_SCROLL:
            return NODE_TEXT_AREA_ON_CONTENT_SCROLL;
        case ON_SWIPER_CHANGE:
            return NODE_SWIPER_EVENT_ON_CHANGE;
        case ON_SWIPER_ANIMATION_START:
            return NODE_SWIPER_EVENT_ON_ANIMATION_START;
        case ON_SWIPER_ANIMATION_END:
            return NODE_SWIPER_EVENT_ON_ANIMATION_END;
        case ON_SWIPER_GESTURE_SWIPE:
            return NODE_SWIPER_EVENT_ON_GESTURE_SWIPE;
        case ON_LIST_SCROLL:
            return NODE_SCROLL_EVENT_ON_SCROLL;
        case ON_LIST_SCROLL_FRAME_BEGIN:
            return NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN;
        case ON_LIST_SCROLL_START:
            return NODE_SCROLL_EVENT_ON_SCROLL_START;
        case ON_LIST_WILL_SCROLL:
            return NODE_LIST_ON_WILL_SCROLL;
        case ON_LIST_SCROLL_STOP:
            return NODE_SCROLL_EVENT_ON_SCROLL_STOP;
        case ON_WATER_FLOW_WILL_SCROLL:
            return NODE_WATER_FLOW_ON_WILL_SCROLL;
        case ON_TOUCH_INTERCEPT:
            return NODE_ON_TOUCH_INTERCEPT;
        case ON_LIST_REACH_END:
            return NODE_SCROLL_EVENT_ON_REACH_END;
        case ON_WATER_FLOW_REACH_END:
            return NODE_SCROLL_EVENT_ON_REACH_END;
        case ON_SCROLL_REACH_END:
            return NODE_SCROLL_EVENT_ON_REACH_END;
        case ON_WATER_FLOW_DID_SCROLL:
            return NODE_WATER_FLOW_ON_DID_SCROLL;
        case ON_WATER_FLOW_SCROLL:
            return NODE_SCROLL_EVENT_ON_SCROLL;
        case ON_WATER_FLOW_SCROLL_FRAME_BEGIN:
            return NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN;
        case ON_WATER_FLOW_SCROLL_START:
            return NODE_SCROLL_EVENT_ON_SCROLL_START;
        case ON_WATER_FLOW_SCROLL_STOP:
            return NODE_SCROLL_EVENT_ON_SCROLL_STOP;
        case ON_LIST_SCROLL_INDEX:
            return NODE_LIST_ON_SCROLL_INDEX;
        case ON_LIST_DID_SCROLL:
            return NODE_LIST_ON_DID_SCROLL;
        case ON_WATER_FLOW_SCROLL_INDEX:
            return NODE_WATER_FLOW_ON_SCROLL_INDEX;
        case ON_WATER_FLOW_REACH_START:
            return NODE_SCROLL_EVENT_ON_REACH_START;
        case ON_SCROLL_REACH_START:
            return NODE_SCROLL_EVENT_ON_REACH_START;
        case ON_LIST_REACH_START:
            return NODE_SCROLL_EVENT_ON_REACH_START;
        case ON_DETECT_RESULT_UPDATE:
            return NODE_TEXT_ON_DETECT_RESULT_UPDATE;
        default:
            return -1;
    }
}

bool IsStringEvent(ArkUI_Int32 type)
{
    switch (type) {
        case NODE_TEXT_INPUT_ON_CHANGE:
        case NODE_TEXT_INPUT_ON_CUT:
        case NODE_TEXT_INPUT_ON_PASTE:
        case NODE_TEXT_AREA_ON_CHANGE:
        case NODE_TEXT_AREA_ON_PASTE:
            return true;
        default:
            return false;
    }
}

bool IsTouchEvent(ArkUI_Int32 type)
{
    switch (type) {
        case NODE_TOUCH_EVENT:
        case NODE_ON_TOUCH_INTERCEPT:
            return true;
        default:
            return false;
    }
}

bool ConvertEvent(ArkUINodeEvent* origin, ArkUI_NodeEvent* event)
{
    ArkUIEventCategory eventCategory = static_cast<ArkUIEventCategory>(origin->kind);
    switch (eventCategory) {
        case COMPONENT_ASYNC_EVENT: {
            event->category = static_cast<int32_t>(NODE_EVENT_CATEGORY_COMPONENT_EVENT);
            ArkUIEventSubKind subKind = static_cast<ArkUIEventSubKind>(origin->componentAsyncEvent.subKind);
            event->kind = ConvertToNodeEventType(subKind);
            return true;
        }
        case TEXT_INPUT: {
            event->category = static_cast<int32_t>(NODE_EVENT_CATEGORY_STRING_ASYNC_EVENT);
            ArkUIEventSubKind subKind = static_cast<ArkUIEventSubKind>(origin->textInputEvent.subKind);
            event->kind = ConvertToNodeEventType(subKind);
            return true;
        }
        case TOUCH_EVENT: {
            event->category = static_cast<int32_t>(NODE_EVENT_CATEGORY_INPUT_EVENT);
            ArkUIEventSubKind subKind = static_cast<ArkUIEventSubKind>(origin->touchEvent.subKind);
            event->kind = ConvertToNodeEventType(subKind);
            return true;
        }
        default:
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "failed to convert origin event data");
            break;
    }
    return false;
}

void HandleInnerEvent(ArkUINodeEvent* innerEvent)
{
    switch (innerEvent->kind) {
        case ArkUIEventCategory::GESTURE_ASYNC_EVENT: {
            // handle gesture event.
            OHOS::Ace::GestureModel::HandleGestureEvent(innerEvent);
            break;
        }
        default: {
            OHOS::Ace::NodeModel::HandleInnerNodeEvent(innerEvent);
            break;
        }
    }
}

int32_t ConvertToCTouchActionType(int32_t originActionType)
{
    switch (originActionType) {
        case ORIGIN_TOUCH_ACTION_DOWN:
            return static_cast<int32_t>(UI_TOUCH_EVENT_ACTION_DOWN);
        case ORIGIN_TOUCH_ACTION_UP:
            return static_cast<int32_t>(UI_TOUCH_EVENT_ACTION_UP);
        case ORIGIN_TOUCH_ACTION_MOVE:
            return static_cast<int32_t>(UI_TOUCH_EVENT_ACTION_MOVE);
        case ORIGIN_TOUCH_ACTION_CANCEL:
            return static_cast<int32_t>(UI_TOUCH_EVENT_ACTION_CANCEL);
        default:
            break;
    }
    return -1;
}

int32_t ConvertToCInputEventToolType(int32_t originSourceToolType)
{
    switch (originSourceToolType) {
        case ORIGIN_INPUT_EVENT_TOOL_TYPE_FINGER:
            return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_FINGER);
        case ORIGIN_INPUT_EVENT_TOOL_TYPE_PEN:
            return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_PEN);
        case ORIGIN_INPUT_EVENT_TOOL_TYPE_MOUSE:
            return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_MOUSE);
        case ORIGIN_INPUT_EVENT_TOOL_TYPE_TOUCHPAD:
            return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_TOUCHPAD);
        default:
            break;
    }
    return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
}

bool ConvertEvent(ArkUINodeEvent* origin, ArkUI_CompatibleNodeEvent* event)
{
    ArkUIEventCategory eventCategory = static_cast<ArkUIEventCategory>(origin->kind);
    switch (eventCategory) {
        case COMPONENT_ASYNC_EVENT: {
            ArkUIEventSubKind subKind = static_cast<ArkUIEventSubKind>(origin->componentAsyncEvent.subKind);
            event->kind = ConvertToNodeEventType(subKind);
            if (memcpy_sp(event->componentEvent.data, MAX_COMPONENT_EVENT_ARG_NUM * sizeof(ArkUI_NumberValue),
                    origin->componentAsyncEvent.data, MAX_COMPONENT_EVENT_ARG_NUM * sizeof(ArkUI_NumberValue)) != 0) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to convert origin event data");
                return false;
            }
            return true;
        }
        case TEXT_INPUT: {
            ArkUIEventSubKind subKind = static_cast<ArkUIEventSubKind>(origin->textInputEvent.subKind);
            event->kind = ConvertToNodeEventType(subKind);
            event->stringEvent.pStr = reinterpret_cast<ArkUI_CharPtr>(origin->textInputEvent.nativeStringPtr);
            return true;
        }
        case TOUCH_EVENT:
            event->kind = ConvertToNodeEventType(ON_TOUCH);
            ConvertToTouchEvent(origin->touchEvent, event->touchEvent);
            return true;
        default:
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "failed to convert origin event data");
            return false;
    }

    return true;
}

bool ConvertEventResult(ArkUI_CompatibleNodeEvent* event, ArkUINodeEvent* origin)
{
    if (IsTouchEvent(event->kind)) {
        origin->touchEvent.preventDefault = event->touchEvent.preventDefault;
        origin->touchEvent.stopPropagation = event->touchEvent.stopPropagation;
        return true;
    }
    if (!IsStringEvent(event->kind)) {
        if (memcpy_sp(origin->componentAsyncEvent.data, MAX_COMPONENT_EVENT_ARG_NUM * sizeof(ArkUI_NumberValue),
                event->componentEvent.data, MAX_COMPONENT_EVENT_ARG_NUM * sizeof(ArkUI_NumberValue)) != 0) {
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to convert event result data");
            return false;
        }
    }
    return true;
}

}; // namespace OHOS::Ace::NodeModel

#ifdef __cplusplus
extern "C" {
#endif

ArkUI_NodeEventType OH_ArkUI_NodeEvent_GetEventType(ArkUI_NodeEvent* event)
{
    if (!event || event->kind < 0) {
        return ArkUI_NodeEventType::NODE_TOUCH_EVENT;
    }
    return static_cast<ArkUI_NodeEventType>(event->kind);
}

int32_t OH_ArkUI_NodeEvent_GetTargetId(ArkUI_NodeEvent* event)
{
    if (!event) {
        return -1;
    }
    return event->eventId;
}

ArkUI_NodeHandle OH_ArkUI_NodeEvent_GetNodeHandle(ArkUI_NodeEvent* event)
{
    if (!event) {
        return nullptr;
    }
    return reinterpret_cast<ArkUI_NodeHandle>(event->node);
}

ArkUI_UIInputEvent* OH_ArkUI_NodeEvent_GetInputEvent(ArkUI_NodeEvent* event)
{
    if (!event || event->category != static_cast<int32_t>(NODE_EVENT_CATEGORY_INPUT_EVENT)) {
        return nullptr;
    }
    return reinterpret_cast<ArkUI_UIInputEvent*>(event->origin);
}

ArkUI_NodeComponentEvent* OH_ArkUI_NodeEvent_GetNodeComponentEvent(ArkUI_NodeEvent* event)
{
    if (!event || event->category != static_cast<int32_t>(NODE_EVENT_CATEGORY_COMPONENT_EVENT)) {
        return nullptr;
    }
    const auto* originNodeEvent = reinterpret_cast<ArkUINodeEvent*>(event->origin);
    if (!originNodeEvent) {
        return nullptr;
    }
    return const_cast<ArkUI_NodeComponentEvent*>(
        reinterpret_cast<const ArkUI_NodeComponentEvent*>(&(originNodeEvent->componentAsyncEvent)));
}

ArkUI_StringAsyncEvent* OH_ArkUI_NodeEvent_GetStringAsyncEvent(ArkUI_NodeEvent* event)
{
    if (!event || event->category != static_cast<int32_t>(NODE_EVENT_CATEGORY_STRING_ASYNC_EVENT)) {
        return nullptr;
    }
    const auto* originNodeEvent = reinterpret_cast<ArkUINodeEvent*>(event->origin);
    if (!originNodeEvent) {
        return nullptr;
    }
    return const_cast<ArkUI_StringAsyncEvent*>(
        reinterpret_cast<const ArkUI_StringAsyncEvent*>(&(originNodeEvent->textInputEvent)));
}

void* OH_ArkUI_NodeEvent_GetUserData(ArkUI_NodeEvent* event)
{
    if (!event) {
        return nullptr;
    }
    return event->userData;
}
#ifdef __cplusplus
};
#endif
