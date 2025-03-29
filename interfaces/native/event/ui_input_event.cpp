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

#include "interfaces/native/event/ui_input_event_impl.h"

#include "core/event/touch_event.h"
#include "interfaces/native/node/event_converter.h"
#include "interfaces/native/node/node_model.h"
#include "base/error/error_code.h"

#ifdef __cplusplus
extern "C" {
#endif
bool isCurrentCTouchEventParamValid(const ArkUITouchEvent* touchEvent, uint32_t pointerIndex)
{
    if (!touchEvent) {
        return false;
    }
    if ((pointerIndex < 0 || pointerIndex >= touchEvent->touchPointSize) ||
        !(touchEvent->touchPointes)) {
        return false;
    }
    return true;
}

bool isHistoryCTouchEventParamValid(const ArkUITouchEvent* touchEvent, uint32_t historyIndex, uint32_t pointerIndex)
{
    if (!touchEvent) {
        return false;
    }
    if ((historyIndex < 0 || historyIndex >= touchEvent->historySize) ||
        !touchEvent->historyEvents) {
        return false;
    }
    if ((pointerIndex < 0 || pointerIndex >= touchEvent->historyEvents[historyIndex].touchPointSize) ||
        !(touchEvent->historyEvents[historyIndex].touchPointes)) {
        return false;
    }
    return true;
}

int32_t OH_ArkUI_UIInputEvent_GetType(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0;
    }
    return event->inputType;
}

int32_t OH_ArkUI_UIInputEvent_GetAction(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return -1;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent) {
                return -1;
            }
            return OHOS::Ace::NodeModel::ConvertToCTouchActionType(touchEvent->action);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                return -1;
            }
            return OHOS::Ace::NodeModel::ConvertToCMouseActionType(mouseEvent->action);
        }
        default:
            break;
    }
    return -1;
}

int32_t HandleCTouchEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    }
    return touchEvent->sourceType;
}

int32_t HandleCClickEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
    }
    return clickEvent->sourceType;
}

int32_t HandleCMouseEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
    }
    return mouseEvent->sourceType;
}

int32_t HandleCAxisEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
    }
    return axisEvent->sourceType;
}

int32_t HandleCFocusAxisEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
    }
    return focusAxisEvent->sourceType;
}

int32_t HandleCHoverEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
    }
    return hoverEvent->sourceType;
}

int32_t HandleAxisEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    }
    return static_cast<int32_t>(axisEvent->sourceType);
}

int32_t OH_ArkUI_UIInputEvent_GetSourceType(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    }
    std::map<ArkUIEventTypeId, std::function<int32_t(ArkUI_UIInputEvent*)>> eventHandlers = {
        { C_TOUCH_EVENT_ID, HandleCTouchEventSourceType },
        { C_MOUSE_EVENT_ID, HandleCMouseEventSourceType },
        { C_AXIS_EVENT_ID, HandleCAxisEventSourceType },
        { C_FOCUS_AXIS_EVENT_ID, HandleCFocusAxisEventSourceType },
        { C_HOVER_EVENT_ID, HandleCHoverEventSourceType },
        { C_CLICK_EVENT_ID, HandleCClickEventSourceType },
        { AXIS_EVENT_ID, HandleAxisEventSourceType },
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return it->second(inputEvent);
    }
    return static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
}

int32_t HandleCTouchEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
    }
    return OHOS::Ace::NodeModel::ConvertToCInputEventToolType(touchEvent->actionTouchPoint.toolType);
}

int32_t HandleCMouseEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
    }
    return OHOS::Ace::NodeModel::ConvertToCInputEventToolType(mouseEvent->actionTouchPoint.toolType);
}

int32_t HandleCHoverEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
    }
    return OHOS::Ace::NodeModel::ConvertToCInputEventToolType(hoverEvent->toolType);
}

int32_t HandleCClickEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
    }
    return OHOS::Ace::NodeModel::ConvertToCInputEventToolType(clickEvent->toolType);
}

int32_t HandleCAxisEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
    }
    return OHOS::Ace::NodeModel::ConvertToCInputEventToolType(axisEvent->actionTouchPoint.toolType);
}

int32_t HandleCFocusAxisEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
    }
    return OHOS::Ace::NodeModel::ConvertToCInputEventToolType(focusAxisEvent->toolType);
}

int32_t HandleAxisEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
    }
    return OHOS::Ace::NodeModel::ConvertToCInputEventToolType(static_cast<int32_t>(axisEvent->sourceTool));
}

int32_t OH_ArkUI_UIInputEvent_GetToolType(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
    }
    std::map<ArkUIEventTypeId, std::function<int32_t(ArkUI_UIInputEvent*)>> eventHandlers = {
        { C_TOUCH_EVENT_ID, HandleCTouchEventToolType },
        { C_MOUSE_EVENT_ID, HandleCMouseEventToolType },
        { C_AXIS_EVENT_ID, HandleCAxisEventToolType },
        { C_FOCUS_AXIS_EVENT_ID, HandleCFocusAxisEventToolType },
        { C_HOVER_EVENT_ID, HandleCHoverEventToolType },
        { C_CLICK_EVENT_ID, HandleCClickEventToolType },
        { AXIS_EVENT_ID, HandleAxisEventToolType },
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return it->second(inputEvent);
    }
    return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
}

int64_t HandleCTouchEvent(ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0;
    }
    return touchEvent->timeStamp;
}

int64_t HandleTouchEvent(ArkUI_UIInputEvent* event)
{
    const auto* uiEvent = reinterpret_cast<const OHOS::Ace::PointerEvent*>(event->inputEvent);
    if (!uiEvent) {
        LOGE("The parameter of OH_ArkUI_UIInputEvent_GetEventTime is invalid");
        return 0;
    }
    return uiEvent->time.time_since_epoch().count();
}

int64_t HandleAxisEvent(ArkUI_UIInputEvent* event)
{
    const auto* uiEvent = reinterpret_cast<const OHOS::Ace::PointerEvent*>(event->inputEvent);
    if (!uiEvent) {
        LOGE("The parameter of OH_ArkUI_UIInputEvent_GetEventTime is invalid");
        return 0;
    }
    return uiEvent->time.time_since_epoch().count();
}

int64_t HandleCMouseEvent(ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        return 0;
    }
    return mouseEvent->timeStamp;
}

int64_t HandleCAxisEvent(ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0;
    }
    return axisEvent->timeStamp;
}

int64_t HandleCKeyEvent(ArkUI_UIInputEvent* event)
{
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return 0;
    }
    return keyEvent->timestamp;
}

int64_t HandleCFocusAxisEvent(ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        return 0;
    }
    return focusAxisEvent->timeStamp;
}

int64_t HandleCHoverEventTimestamp(ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        return 0;
    }
    return hoverEvent->timeStamp;
}

int64_t HandleCClickEventTimestamp(ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        return 0;
    }
    return clickEvent->timestamp;
}

int64_t OH_ArkUI_UIInputEvent_GetEventTime(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0;
    }
    std::map<ArkUIEventTypeId, std::function<int64_t(ArkUI_UIInputEvent*)>> eventHandlers = {
        {C_TOUCH_EVENT_ID, HandleCTouchEvent},
        {TOUCH_EVENT_ID, HandleTouchEvent},
        {AXIS_EVENT_ID, HandleAxisEvent},
        {C_MOUSE_EVENT_ID, HandleCMouseEvent},
        {C_AXIS_EVENT_ID, HandleCAxisEvent},
        {C_KEY_EVENT_ID, HandleCKeyEvent},
        {C_FOCUS_AXIS_EVENT_ID, HandleCFocusAxisEvent},
        {C_HOVER_EVENT_ID, HandleCHoverEventTimestamp},
        {C_CLICK_EVENT_ID, HandleCClickEventTimestamp},
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return it->second(inputEvent);
    }
    return 0;
}

int32_t GetCKeyEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return -1;
    }
    return static_cast<int32_t>(keyEvent->deviceId);
}

int32_t GetCFocusAxisEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        return -1;
    }
    return static_cast<int32_t>(focusAxisEvent->deviceId);
}

int32_t GetCMouseEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        return -1;
    }
    return static_cast<int32_t>(mouseEvent->deviceId);
}

int32_t GetCTouchEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return -1;
    }
    return static_cast<int32_t>(touchEvent->deviceId);
}

int32_t GetCHoverEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        return -1;
    }
    return static_cast<int32_t>(hoverEvent->deviceId);
}

int32_t GetCClickEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        return -1;
    }
    return static_cast<int32_t>(clickEvent->deviceId);
}

int32_t GetCAxisEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return -1;
    }
    return static_cast<int32_t>(axisEvent->deviceId);
}

int32_t GetAxisEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return -1;
    }
    return static_cast<int32_t>(axisEvent->deviceId);
}

int32_t GetTouchEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return -1;
    }
    return static_cast<int32_t>(touchEvent->deviceId);
}

int32_t OH_ArkUI_UIInputEvent_GetDeviceId(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        return -1;
    }
    std::map<ArkUIEventTypeId, std::function<int64_t(ArkUI_UIInputEvent*)>> eventHandlers = {
        {C_KEY_EVENT_ID, GetCKeyEventDeviceId},
        {C_FOCUS_AXIS_EVENT_ID, GetCFocusAxisEventDeviceId},
        {C_MOUSE_EVENT_ID, GetCMouseEventDeviceId},
        {C_TOUCH_EVENT_ID, GetCTouchEventDeviceId},
        {C_HOVER_EVENT_ID, GetCHoverEventDeviceId},
        {C_CLICK_EVENT_ID, GetCClickEventDeviceId},
        {C_AXIS_EVENT_ID, GetCAxisEventDeviceId },
        {AXIS_EVENT_ID, GetAxisEventDeviceId },
        {TOUCH_EVENT_ID, GetTouchEventDeviceId },
    };
    auto iter = eventHandlers.find(event->eventTypeId);
    if (iter != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return iter->second(inputEvent);
    }
    return -1;
}

int32_t OH_ArkUI_UIInputEvent_GetPressedKeys(
    const ArkUI_UIInputEvent* event, int32_t* pressedKeyCodes, int32_t* length)
{
    if (!event || !pressedKeyCodes || !length) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto inputLength = *length;
    if (keyEvent->keyCodesLength > inputLength) {
        return ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH;
    }
    *length = keyEvent->keyCodesLength;
    for (int i = 0; i < keyEvent->keyCodesLength; i++) {
        pressedKeyCodes[i] = keyEvent->pressedKeyCodes[i];
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

uint32_t OH_ArkUI_PointerEvent_GetPointerCount(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent) {
                return 0;
            }
            return touchEvent->touchPointSize;
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                return 0;
            }
            return 1;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                return 0;
            }
            return 1;
        }
        case C_CLICK_EVENT_ID: {
            const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
            if (!clickEvent) {
                return 0;
            }
            return clickEvent->clickPointSize;
        }
        default:
            break;
    }
    return 0;
}

int32_t OH_ArkUI_PointerEvent_GetPointerId(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    if (!event) {
        return 0;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                return 0;
            }
            return touchEvent->touchPointes[pointerIndex].id;
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                return 0;
            }
            return mouseEvent->actionTouchPoint.id;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                return 0;
            }
            return axisEvent->actionTouchPoint.id;
        }
        default:
            break;
    }
    return 0;
}

float HandleCClickEventX(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        return 0.0f;
    }
    return clickEvent->localX;
}

float HandleCTouchEventX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0.0f;
    }
    return touchEvent->actionTouchPoint.nodeX;
}

float HandleCMouseEventX(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        return 0.0f;
    }
    return mouseEvent->actionTouchPoint.nodeX;
}

float HandleCAxisEventX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0.0f;
    }
    return axisEvent->actionTouchPoint.nodeX;
}

float HandleTouchEventX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        return touchEvent->localX;
    }
    return 0.0f;
}

float HandleAxisEventX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        return axisEvent->localX;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetX(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    std::map<ArkUIEventTypeId, std::function<float(ArkUI_UIInputEvent*)>> eventHandlers = {
        { C_TOUCH_EVENT_ID, HandleCTouchEventX },
        { TOUCH_EVENT_ID, HandleTouchEventX },
        { AXIS_EVENT_ID, HandleAxisEventX },
        { C_MOUSE_EVENT_ID, HandleCMouseEventX },
        { C_AXIS_EVENT_ID, HandleCAxisEventX },
        { C_CLICK_EVENT_ID, HandleCClickEventX },
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return it->second(inputEvent);
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                return 0.0f;
            }
            return touchEvent->touchPointes[pointerIndex].nodeX;
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                return 0.0f;
            }
            return mouseEvent->actionTouchPoint.nodeX;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                return 0.0f;
            }
            return axisEvent->actionTouchPoint.nodeX;
        }
        default:
            break;
    }
    return 0.0f;
}

float HandleCClickEventY(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        return 0.0f;
    }
    return clickEvent->localY;
}

float HandleCTouchEventY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0.0f;
    }
    return touchEvent->actionTouchPoint.nodeY;
}

float HandleCMouseEventY(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        return 0.0f;
    }
    return mouseEvent->actionTouchPoint.nodeY;
}

float HandleCAxisEventY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0.0f;
    }
    return axisEvent->actionTouchPoint.nodeY;
}

float HandleTouchEventY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        return touchEvent->localY;
    }
    return 0.0f;
}

float HandleAxisEventY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        return axisEvent->localY;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetY(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    std::map<ArkUIEventTypeId, std::function<float(ArkUI_UIInputEvent*)>> eventHandlers = {
        { C_TOUCH_EVENT_ID, HandleCTouchEventY },
        { TOUCH_EVENT_ID, HandleTouchEventY },
        { AXIS_EVENT_ID, HandleAxisEventY },
        { C_MOUSE_EVENT_ID, HandleCMouseEventY },
        { C_AXIS_EVENT_ID, HandleCAxisEventY },
        { C_CLICK_EVENT_ID, HandleCClickEventY },
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return it->second(inputEvent);
    }
    LOGE("The parameter of OH_ArkUI_PointerEvent_GetY is invalid");
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                return 0.0f;
            }
            return touchEvent->touchPointes[pointerIndex].nodeY;
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                return 0.0f;
            }
            return mouseEvent->actionTouchPoint.nodeY;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                return 0.0f;
            }
            return axisEvent->actionTouchPoint.nodeY;
        }
        default:
            break;
    }
    return 0.0f;
}

float HandleCTouchEventWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0.0f;
    }
    return touchEvent->actionTouchPoint.windowX;
}

float HandleTouchEventWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        return touchEvent->x;
    }
    return 0.0f;
}

float HandleAxisEventWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        return axisEvent->x;
    }
    return 0.0f;
}

float HandleCMouseEventWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        return 0.0f;
    }
    return mouseEvent->actionTouchPoint.windowX;
}

float HandleCAxisEventWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0.0f;
    }
    return axisEvent->actionTouchPoint.windowX;
}

float HandleCClickEventWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        return 0.0f;
    }
    return clickEvent->windowX;
}

float OH_ArkUI_PointerEvent_GetWindowX(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    std::map<ArkUIEventTypeId, std::function<float(ArkUI_UIInputEvent*)>> eventHandlers = {
        { C_TOUCH_EVENT_ID, HandleCTouchEventWindowX },
        { TOUCH_EVENT_ID, HandleTouchEventWindowX },
        { AXIS_EVENT_ID, HandleAxisEventWindowX },
        { C_MOUSE_EVENT_ID, HandleCMouseEventWindowX },
        { C_AXIS_EVENT_ID, HandleCAxisEventWindowX },
        { C_CLICK_EVENT_ID, HandleCClickEventWindowX },
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return it->second(inputEvent);
    }
    LOGE("The parameter of OH_ArkUI_PointerEvent_GetWindowX is invalid");
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetWindowXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                return 0.0f;
            }
            return touchEvent->touchPointes[pointerIndex].windowX;
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                return 0.0f;
            }
            return mouseEvent->actionTouchPoint.windowX;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                return 0.0f;
            }
            return axisEvent->actionTouchPoint.windowX;
        }
        default:
            break;
    }
    return 0.0f;
}

float HandleCClickEventWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        return 0.0f;
    }
    return clickEvent->windowY;
}

float HandleCTouchEventWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0.0f;
    }
    return touchEvent->actionTouchPoint.windowY;
}

float HandleCAxisEventWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0.0f;
    }
    return axisEvent->actionTouchPoint.windowY;
}

float HandleCMouseEventWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        return 0.0f;
    }
    return mouseEvent->actionTouchPoint.windowY;
}

float HandleTouchEventWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        return touchEvent->y;
    }
    return 0.0f;
}

float HandleAxisEventWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        return axisEvent->y;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetWindowY(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    std::map<ArkUIEventTypeId, std::function<float(ArkUI_UIInputEvent*)>> eventHandlers = {
        { C_TOUCH_EVENT_ID, HandleCTouchEventWindowY },
        { TOUCH_EVENT_ID, HandleTouchEventWindowY },
        { AXIS_EVENT_ID, HandleAxisEventWindowY },
        { C_MOUSE_EVENT_ID, HandleCMouseEventWindowY },
        { C_AXIS_EVENT_ID, HandleCAxisEventWindowY },
        { C_CLICK_EVENT_ID, HandleCClickEventWindowY },
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return it->second(inputEvent);
    }
    LOGE("The parameter of OH_ArkUI_PointerEvent_GetWindowY is invalid");
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetWindowYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                return 0.0f;
            }
            return touchEvent->touchPointes[pointerIndex].windowY;
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                return 0.0f;
            }
            return mouseEvent->actionTouchPoint.windowY;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                return 0.0f;
            }
            return axisEvent->actionTouchPoint.windowY;
        }
        default:
            break;
    }
    return 0.0f;
}

float HandleCTouchEventDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0.0f;
    }
    return touchEvent->actionTouchPoint.screenX;
}

float HandleCClickEventDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        return 0.0f;
    }
    return clickEvent->displayX;
}

float HandleCMouseEventDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        return 0.0f;
    }
    return mouseEvent->actionTouchPoint.screenX;
}

float HandleCAxisEventDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0.0f;
    }
    return axisEvent->actionTouchPoint.screenX;
}

float HandleTouchEventDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        return touchEvent->screenX;
    }
    return 0.0f;
}

float HandleAxisEventDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        return axisEvent->screenX;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetDisplayX(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    std::map<ArkUIEventTypeId, std::function<float(ArkUI_UIInputEvent*)>> eventHandlers = {
        { C_TOUCH_EVENT_ID, HandleCTouchEventDisplayX },
        { TOUCH_EVENT_ID, HandleTouchEventDisplayX },
        { AXIS_EVENT_ID, HandleAxisEventDisplayX },
        { C_MOUSE_EVENT_ID, HandleCMouseEventDisplayX },
        { C_AXIS_EVENT_ID, HandleCAxisEventDisplayX },
        { C_CLICK_EVENT_ID, HandleCClickEventDisplayX },
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return it->second(inputEvent);
    }
    LOGE("The parameter of OH_ArkUI_PointerEvent_GetDisplayX is invalid");
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetDisplayXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                return 0.0f;
            }
            return touchEvent->touchPointes[pointerIndex].screenX;
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                return 0.0f;
            }
            return mouseEvent->actionTouchPoint.screenX;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                return 0.0f;
            }
            return axisEvent->actionTouchPoint.screenX;
        }
        default:
            break;
    }
    return 0.0f;
}

float HandleCTouchEventDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0.0f;
    }
    return touchEvent->actionTouchPoint.screenY;
}

float HandleCClickEventDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        return 0.0f;
    }
    return clickEvent->displayY;
}

float HandleCMouseEventDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        return 0.0f;
    }
    return mouseEvent->actionTouchPoint.screenY;
}

float HandleCAxisEventDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0.0f;
    }
    return axisEvent->actionTouchPoint.screenY;
}

float HandleTouchEventDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        return touchEvent->screenY;
    }
    return 0.0f;
}

float HandleAxisEventDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        return axisEvent->screenY;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetDisplayY(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    std::map<ArkUIEventTypeId, std::function<float(ArkUI_UIInputEvent*)>> eventHandlers = {
        { C_TOUCH_EVENT_ID, HandleCTouchEventDisplayY },
        { TOUCH_EVENT_ID, HandleTouchEventDisplayY },
        { AXIS_EVENT_ID, HandleAxisEventDisplayY },
        { C_MOUSE_EVENT_ID, HandleCMouseEventDisplayY },
        { C_AXIS_EVENT_ID, HandleCAxisEventDisplayY },
        { C_CLICK_EVENT_ID, HandleCClickEventDisplayY },
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return it->second(inputEvent);
    }
    LOGE("The parameter of OH_ArkUI_PointerEvent_GetDisplayY is invalid");
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetDisplayYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                return 0.0f;
            }
            return touchEvent->touchPointes[pointerIndex].screenY;
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                return 0.0f;
            }
            return mouseEvent->actionTouchPoint.screenY;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                return 0.0f;
            }
            return axisEvent->actionTouchPoint.screenY;
        }
        default:
            break;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetPressure(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                return 0.0f;
            }
            return touchEvent->touchPointes[touchEvent->touchPointSize-1].pressure;
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                return 0.0f;
            }
            return mouseEvent->actionTouchPoint.pressure;
        }
        case C_CLICK_EVENT_ID: {
            const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
            if (!clickEvent) {
                return 0.0f;
            }
            return clickEvent->pressure;
        }
        default:
            break;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetTiltX(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                return 0.0f;
            }
            return touchEvent->touchPointes[touchEvent->touchPointSize-1].tiltX;
        }
        case C_CLICK_EVENT_ID: {
            const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
            if (!clickEvent) {
                return 0.0f;
            }
            return clickEvent->tiltX;
        }
        case C_HOVER_EVENT_ID: {
            const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
            if (!hoverEvent) {
                return 0.0f;
            }
            return hoverEvent->tiltX;
        }
        default:
            break;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetTiltY(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                return 0.0f;
            }
            return touchEvent->touchPointes[touchEvent->touchPointSize-1].tiltY;
        }
        case C_CLICK_EVENT_ID: {
            const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
            if (!clickEvent) {
                return 0.0f;
            }
            return clickEvent->tiltY;
        }
        case C_HOVER_EVENT_ID: {
            const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
            if (!hoverEvent) {
                return 0.0f;
            }
            return hoverEvent->tiltY;
        }
        default:
            break;
    }
    return 0.0f;
}

int32_t OH_ArkUI_PointerEvent_GetRollAngle(const ArkUI_UIInputEvent* event, double* rollAngle)
{
    if (rollAngle == nullptr || event == nullptr) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (touchEvent && touchEvent->subKind == ON_HOVER_MOVE) {
                *rollAngle = touchEvent->actionTouchPoint.rollAngle;
                return ARKUI_ERROR_CODE_NO_ERROR;
            }
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                return ARKUI_ERROR_CODE_PARAM_INVALID;
            }
            *rollAngle = touchEvent->touchPointes[touchEvent->touchPointSize - 1].rollAngle;
            return ARKUI_ERROR_CODE_NO_ERROR;
        }
        case C_HOVER_EVENT_ID: {
            const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
            if (!hoverEvent) {
                return ARKUI_ERROR_CODE_PARAM_INVALID;
            }
            *rollAngle = hoverEvent->rollAngle;
            return ARKUI_ERROR_CODE_NO_ERROR;
        }
        default:
            break;
    }
    return ARKUI_ERROR_CODE_PARAM_INVALID;
}

int32_t OH_ArkUI_PointerEvent_GetInteractionHand(const ArkUI_UIInputEvent *event, ArkUI_InteractionHand *hand)
{
    if (!event || !hand) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            *hand = static_cast<ArkUI_InteractionHand>(touchEvent->actionTouchPoint.operatingHand);
            break;
        }
        default:
            break;
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_PointerEvent_GetInteractionHandByIndex(const ArkUI_UIInputEvent *event, int32_t pointerIndex,
    ArkUI_InteractionHand *hand)
{
    if (!event || !hand) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }

    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                return ARKUI_ERROR_CODE_PARAM_INVALID;
            }
            *hand = static_cast<ArkUI_InteractionHand>(touchEvent->touchPointes[pointerIndex].operatingHand);
            break;
        }
        default:
            break;
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

float OH_ArkUI_PointerEvent_GetTouchAreaWidth(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                return 0.0f;
            }
            return touchEvent->touchPointes[touchEvent->touchPointSize-1].contactAreaWidth;
        }
        default:
            break;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetTouchAreaHeight(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                return 0.0f;
            }
            return touchEvent->touchPointes[touchEvent->touchPointSize-1].contactAreaHeight;
        }
        default:
            break;
    }
    return 0.0f;
}

int32_t OH_ArkUI_PointerEvent_GetChangedPointerId(const ArkUI_UIInputEvent* event, uint32_t* pointerIndex)
{
    if (!event || !pointerIndex) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                return ARKUI_ERROR_CODE_PARAM_INVALID;
            }
            *pointerIndex = touchEvent->changedPointerId;
            return ARKUI_ERROR_CODE_NO_ERROR;
        }
        default:
            break;
    }
    return ARKUI_ERROR_CODE_PARAM_INVALID;
}

uint32_t OH_ArkUI_PointerEvent_GetHistorySize(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || !touchEvent->historyEvents) {
                return 0;
            }
            return touchEvent->historySize;
        }
        default:
            break;
    }
    return 0;
}

int64_t OH_ArkUI_PointerEvent_GetHistoryEventTime(const ArkUI_UIInputEvent* event, uint32_t historyIndex)
{
    if (!event) {
        return 0;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || !touchEvent->historyEvents || touchEvent->historySize <= historyIndex ||
                historyIndex < 0) {
                return 0;
            }
            return touchEvent->historyEvents[historyIndex].timeStamp;
        }
        default:
            break;
    }
    return 0;
}

uint32_t OH_ArkUI_PointerEvent_GetHistoryPointerCount(const ArkUI_UIInputEvent* event, uint32_t historyIndex)
{
    if (!event) {
        return 0;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || !touchEvent->historyEvents || touchEvent->historySize <= historyIndex ||
                historyIndex < 0) {
                return 0;
            }
            return touchEvent->historyEvents[historyIndex].touchPointSize;
        }
        default:
            break;
    }
    return 0;
}

int32_t OH_ArkUI_PointerEvent_GetHistoryPointerId(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    if (!event) {
        return 0;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                return 0;
            }
            return touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].id;
        }
        default:
            break;
    }
    return 0;
}

float OH_ArkUI_PointerEvent_GetHistoryX(const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                return 0.0f;
            }
            return touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].nodeX;
        }
        default:
            break;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetHistoryY(const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                return 0.0f;
            }
            return touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].nodeY;
        }
        default:
            break;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetHistoryWindowX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                return 0.0f;
            }
            return touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].windowX;
        }
        default:
            break;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetHistoryWindowY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                return 0.0f;
            }
            return touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].windowY;
        }
        default:
            break;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetHistoryDisplayX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                return 0.0f;
            }
            return touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].screenX;
        }
        default:
            break;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetHistoryDisplayY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                return 0.0f;
            }
            return touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].screenY;
        }
        default:
            break;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetHistoryPressure(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                return 0.0f;
            }
            return touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].pressure;
        }
        default:
            break;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetHistoryTiltX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                return 0.0f;
            }
            return touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].tiltX;
        }
        default:
            break;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetHistoryTiltY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                return 0.0f;
            }
            return touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].tiltY;
        }
        default:
            break;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                return 0.0f;
            }
            return touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].contactAreaWidth;
        }
        default:
            break;
    }
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                return 0.0f;
            }
            return touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].contactAreaHeight;
        }
        default:
            break;
    }
    return 0.0f;
}

double OH_ArkUI_AxisEvent_GetVerticalAxisValue(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0;
    }
    switch (event->eventTypeId) {
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (axisEvent) {
                return axisEvent->verticalAxis;
            }
            break;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                return 0.0;
            }
            return axisEvent->verticalAxis;
        }
        default:
            break;
    }
    return 0.0;
}

double OH_ArkUI_AxisEvent_GetHorizontalAxisValue(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0;
    }
    switch (event->eventTypeId) {
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (axisEvent) {
                return axisEvent->horizontalAxis;
            }
            break;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                return 0.0;
            }
            return axisEvent->horizontalAxis;
        }
        default:
            break;
    }
    return 0.0;
}

double OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0;
    }
    switch (event->eventTypeId) {
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (axisEvent) {
                return axisEvent->pinchAxisScale;
            }
            break;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                return 0.0;
            }
            return axisEvent->pinchAxisScale;
        }
        default:
            break;
    }
    return 0.0;
}

int32_t OH_ArkUI_AxisEvent_GetAxisAction(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return UI_AXIS_EVENT_ACTION_NONE;
    }
    switch (event->eventTypeId) {
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (axisEvent) {
                return OHOS::Ace::NodeModel::ConvertToCAxisActionType(static_cast<int32_t>(axisEvent->action));
            }
            break;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (axisEvent) {
                return OHOS::Ace::NodeModel::ConvertToCAxisActionType(axisEvent->action);
            }
            break;
        }
        default:
            break;
    }
    return UI_AXIS_EVENT_ACTION_NONE;
}

int32_t OH_ArkUI_PointerEvent_SetInterceptHitTestMode(const ArkUI_UIInputEvent* event, HitTestMode mode)
{
    if (!event) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            touchEvent->interceptResult = static_cast<int32_t>(mode);
            break;
        }
        case C_MOUSE_EVENT_ID: {
            auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
            }
            return mouseEvent->interceptResult = static_cast<int32_t>(mode);
        }
        default:
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_PointerEvent_SetStopPropagation(const ArkUI_UIInputEvent* event, bool stopPropagation)
{
    if (!event) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            touchEvent->stopPropagation = stopPropagation;
            break;
        }
        case C_MOUSE_EVENT_ID: {
            auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            mouseEvent->stopPropagation = stopPropagation;
            break;
        }
        case C_HOVER_EVENT_ID: {
            auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
            hoverEvent->stopPropagation = stopPropagation;
            break;
        }
        default:
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_MouseEvent_GetMouseButton(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return -1;
    }
    switch (event->eventTypeId) {
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                return -1;
            }
            return OHOS::Ace::NodeModel::ConvertToCMouseEventButtonType(mouseEvent->button);
        }
        default:
            break;
    }
    return -1;
}

int32_t OH_ArkUI_MouseEvent_GetMouseAction(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return -1;
    }
    switch (event->eventTypeId) {
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                return -1;
            }
            return OHOS::Ace::NodeModel::ConvertToCMouseActionType(mouseEvent->action);
        }
        default:
            break;
    }
    return -1;
}

int64_t OH_ArkUI_PointerEvent_GetPressedTimeByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    if (!event) {
        return 0;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                return 0;
            }
            return touchEvent->touchPointes[pointerIndex].pressedTime;
        }
        default:
            break;
    }
    return 0;
}

float OH_ArkUI_MouseEvent_GetRawDeltaX(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_MOUSE_EVENT_ID: {
            auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                return 0.0f;
            }
            return mouseEvent->rawDeltaX;
        }
        default:
            break;
    }
    return 0.0f;
}

float OH_ArkUI_MouseEvent_GetRawDeltaY(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_MOUSE_EVENT_ID: {
            auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                return 0.0f;
            }
            return mouseEvent->rawDeltaY;
        }
        default:
            break;
    }
    return 0.0f;
}

int32_t OH_ArkUI_UIInputEvent_GetTargetDisplayId(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0;
    }
    auto getTargetDisplayId = [](auto* specificEvent) -> int32_t {
        return specificEvent ? specificEvent->targetDisplayId : 0;
    };
    switch (event->eventTypeId) {
        case C_MOUSE_EVENT_ID:
            return getTargetDisplayId(reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent));
        case C_TOUCH_EVENT_ID:
            return getTargetDisplayId(reinterpret_cast<ArkUITouchEvent*>(event->inputEvent));
        case C_AXIS_EVENT_ID:
            return getTargetDisplayId(reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent));
        case C_FOCUS_AXIS_EVENT_ID:
            return getTargetDisplayId(reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent));
        case TOUCH_EVENT_ID: {
            return getTargetDisplayId(reinterpret_cast<OHOS::Ace::TouchEvent*>(event->inputEvent));
        }
        case AXIS_EVENT_ID: {
            return getTargetDisplayId(reinterpret_cast<OHOS::Ace::AxisEvent*>(event->inputEvent));
        }
        default:
            return 0;
    }
}

int32_t OH_ArkUI_MouseEvent_GetPressedButtons(const ArkUI_UIInputEvent* event, int32_t* pressedButtons, int32_t* length)
{
    if (!event || !pressedButtons || !length) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    switch (event->eventTypeId) {
        case C_MOUSE_EVENT_ID: {
            auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                return ARKUI_ERROR_CODE_PARAM_INVALID;
            }
            auto inputLength = *length;
            if (mouseEvent->pressedButtonsLength > inputLength) {
                return ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH;
            }
            *length = mouseEvent->pressedButtonsLength;
            for (int i = 0; i < mouseEvent->pressedButtonsLength; i++) {
                pressedButtons[i] = mouseEvent->pressedButtons[i];
            }
            return ARKUI_ERROR_CODE_NO_ERROR;
        }
        default:
            break;
    }
    return ARKUI_ERROR_CODE_PARAM_INVALID;
}

double OH_ArkUI_FocusAxisEvent_GetAxisValue(const ArkUI_UIInputEvent* event, int32_t axis)
{
    if (!event) {
        return 0.0;
    }
    if (event->eventTypeId != C_FOCUS_AXIS_EVENT_ID) {
        return 0.0f;
    }
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        return 0.0;
    }
    switch (axis) {
        case UI_FOCUS_AXIS_EVENT_ABS_X:
            return focusAxisEvent->absXValue;
        case UI_FOCUS_AXIS_EVENT_ABS_Y:
            return focusAxisEvent->absYValue;
        case UI_FOCUS_AXIS_EVENT_ABS_Z:
            return focusAxisEvent->absZValue;
        case UI_FOCUS_AXIS_EVENT_ABS_RZ:
            return focusAxisEvent->absRzValue;
        case UI_FOCUS_AXIS_EVENT_ABS_GAS:
            return focusAxisEvent->absGasValue;
        case UI_FOCUS_AXIS_EVENT_ABS_BRAKE:
            return focusAxisEvent->absBrakeValue;
        case UI_FOCUS_AXIS_EVENT_ABS_HAT0X:
            return focusAxisEvent->absHat0XValue;
        case UI_FOCUS_AXIS_EVENT_ABS_HAT0Y:
            return focusAxisEvent->absHat0YValue;
        default:
            return 0.0;
    }
    return 0.0;
}

int32_t OH_ArkUI_FocusAxisEvent_SetStopPropagation(const ArkUI_UIInputEvent* event, bool stopPropagation)
{
    if (!event) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    switch (event->eventTypeId) {
        case C_FOCUS_AXIS_EVENT_ID: {
            auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
            focusAxisEvent->stopPropagation = stopPropagation;
            break;
        }
        default:
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

float HandleCMouseEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        return 0.0f;
    }
    return mouseEvent->width;
}

float HandleCTouchEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0.0f;
    }
    return touchEvent->width;
}

float HandleCHoverEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        return 0.0f;
    }
    return hoverEvent->width;
}

float HandleCClickEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        return 0.0f;
    }
    return clickEvent->width;
}

float HandleCAxisEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0.0f;
    }
    return axisEvent->width;
}

float HandleCFocusAxisEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        return 0.0f;
    }
    return focusAxisEvent->width;
}

float HandleAxisEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0.0f;
    }
    return axisEvent->width;
}

float HandleTouchEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0.0f;
    }
    return touchEvent->width;
}

float OH_ArkUI_UIInputEvent_GetEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    std::map<ArkUIEventTypeId, std::function<float(ArkUI_UIInputEvent*)>> eventHandlers = {
        { C_TOUCH_EVENT_ID, HandleCTouchEventTargetWidth },
        { TOUCH_EVENT_ID, HandleTouchEventTargetWidth },
        { AXIS_EVENT_ID, HandleAxisEventTargetWidth },
        { C_MOUSE_EVENT_ID, HandleCMouseEventTargetWidth },
        { C_AXIS_EVENT_ID, HandleCAxisEventTargetWidth },
        { C_FOCUS_AXIS_EVENT_ID, HandleCFocusAxisEventTargetWidth },
        { C_HOVER_EVENT_ID, HandleCHoverEventTargetWidth },
        { C_CLICK_EVENT_ID, HandleCClickEventTargetWidth },
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return it->second(inputEvent);
    }
    return 0.0f;
}

float HandleCMouseEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        return 0.0f;
    }
    return mouseEvent->height;
}

float HandleCTouchEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0.0f;
    }
    return touchEvent->height;
}

float HandleCHoverEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        return 0.0f;
    }
    return hoverEvent->height;
}

float HandleCClickEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        return 0.0f;
    }
    return clickEvent->height;
}

float HandleCAxisEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0.0f;
    }
    return axisEvent->height;
}

float HandleCFocusAxisEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        return 0.0f;
    }
    return focusAxisEvent->height;
}

float HandleAxisEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0.0f;
    }
    return axisEvent->height;
}

float HandleTouchEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0.0f;
    }
    return touchEvent->height;
}

float OH_ArkUI_UIInputEvent_GetEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    std::map<ArkUIEventTypeId, std::function<float(ArkUI_UIInputEvent*)>> eventHandlers = {
        { C_TOUCH_EVENT_ID, HandleCTouchEventTargetHeight },
        { TOUCH_EVENT_ID, HandleTouchEventTargetHeight },
        { AXIS_EVENT_ID, HandleAxisEventTargetHeight },
        { C_MOUSE_EVENT_ID, HandleCMouseEventTargetHeight },
        { C_AXIS_EVENT_ID, HandleCAxisEventTargetHeight },
        { C_FOCUS_AXIS_EVENT_ID, HandleCFocusAxisEventTargetHeight },
        { C_HOVER_EVENT_ID, HandleCHoverEventTargetHeight },
        { C_CLICK_EVENT_ID, HandleCClickEventTargetHeight },
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return it->second(inputEvent);
    }
    return 0.0f;
}

float HandleCMouseEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        return 0.0f;
    }
    return mouseEvent->targetPositionX;
}

float HandleCTouchEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0.0f;
    }
    return touchEvent->targetPositionX;
}

float HandleCHoverEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        return 0.0f;
    }
    return hoverEvent->targetPositionX;
}

float HandleCClickEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        return 0.0f;
    }
    return clickEvent->targetPositionX;
}

float HandleCAxisEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0.0f;
    }
    return axisEvent->targetPositionX;
}

float HandleCFocusAxisEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        return 0.0f;
    }
    return focusAxisEvent->targetPositionX;
}

float HandleAxisEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0.0f;
    }
    return axisEvent->targetPositionX;
}

float HandleTouchEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0.0f;
    }
    return touchEvent->targetPositionX;
}

float OH_ArkUI_UIInputEvent_GetEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    std::map<ArkUIEventTypeId, std::function<float(ArkUI_UIInputEvent*)>> eventHandlers = {
        { C_TOUCH_EVENT_ID, HandleCTouchEventTargetPositionX },
        { TOUCH_EVENT_ID, HandleTouchEventTargetPositionX },
        { AXIS_EVENT_ID, HandleAxisEventTargetPositionX },
        { C_MOUSE_EVENT_ID, HandleCMouseEventTargetPositionX },
        { C_AXIS_EVENT_ID, HandleCAxisEventTargetPositionX },
        { C_FOCUS_AXIS_EVENT_ID, HandleCFocusAxisEventTargetPositionX },
        { C_HOVER_EVENT_ID, HandleCHoverEventTargetPositionX },
        { C_CLICK_EVENT_ID, HandleCClickEventTargetPositionX },
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return it->second(inputEvent);
    }
    return 0.0f;
}

float HandleCMouseEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        return 0.0f;
    }
    return mouseEvent->targetPositionY;
}

float HandleCTouchEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0.0f;
    }
    return touchEvent->targetPositionY;
}

float HandleCHoverEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        return 0.0f;
    }
    return hoverEvent->targetPositionY;
}

float HandleCClickEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        return 0.0f;
    }
    return clickEvent->targetPositionY;
}

float HandleCAxisEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0.0f;
    }
    return axisEvent->targetPositionY;
}

float HandleCFocusAxisEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        return 0.0f;
    }
    return focusAxisEvent->targetPositionY;
}

float HandleAxisEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0.0f;
    }
    return axisEvent->targetPositionY;
}

float HandleTouchEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0.0f;
    }
    return touchEvent->targetPositionY;
}

float OH_ArkUI_UIInputEvent_GetEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    std::map<ArkUIEventTypeId, std::function<float(ArkUI_UIInputEvent*)>> eventHandlers = {
        { C_TOUCH_EVENT_ID, HandleCTouchEventTargetPositionY },
        { TOUCH_EVENT_ID, HandleTouchEventTargetPositionY },
        { AXIS_EVENT_ID, HandleAxisEventTargetPositionY },
        { C_MOUSE_EVENT_ID, HandleCMouseEventTargetPositionY },
        { C_AXIS_EVENT_ID, HandleCAxisEventTargetPositionY },
        { C_FOCUS_AXIS_EVENT_ID, HandleCFocusAxisEventTargetPositionY },
        { C_HOVER_EVENT_ID, HandleCHoverEventTargetPositionY },
        { C_CLICK_EVENT_ID, HandleCClickEventTargetPositionY },
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return it->second(inputEvent);
    }
    return 0.0f;
}

float HandleCMouseEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        return 0.0f;
    }
    return mouseEvent->targetGlobalPositionX;
}

float HandleCTouchEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0.0f;
    }
    return touchEvent->targetGlobalPositionX;
}

float HandleCHoverEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        return 0.0f;
    }
    return hoverEvent->targetGlobalPositionX;
}

float HandleCClickEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        return 0.0f;
    }
    return clickEvent->targetGlobalPositionX;
}

float HandleCAxisEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0.0f;
    }
    return axisEvent->targetGlobalPositionX;
}

float HandleCFocusAxisEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        return 0.0f;
    }
    return focusAxisEvent->targetGlobalPositionX;
}

float HandleAxisEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0.0f;
    }
    return axisEvent->targetGlobalPositionX;
}

float HandleTouchEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0.0f;
    }
    return touchEvent->targetGlobalPositionX;
}

float OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    std::map<ArkUIEventTypeId, std::function<float(ArkUI_UIInputEvent*)>> eventHandlers = {
        { C_TOUCH_EVENT_ID, HandleCTouchEventTargetGlobalPositionX },
        { TOUCH_EVENT_ID, HandleTouchEventTargetGlobalPositionX },
        { AXIS_EVENT_ID, HandleAxisEventTargetGlobalPositionX },
        { C_MOUSE_EVENT_ID, HandleCMouseEventTargetGlobalPositionX },
        { C_AXIS_EVENT_ID, HandleCAxisEventTargetGlobalPositionX },
        { C_FOCUS_AXIS_EVENT_ID, HandleCFocusAxisEventTargetGlobalPositionX },
        { C_HOVER_EVENT_ID, HandleCHoverEventTargetGlobalPositionX },
        { C_CLICK_EVENT_ID, HandleCClickEventTargetGlobalPositionX },
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return it->second(inputEvent);
    }
    return 0.0f;
}

float HandleCMouseEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        return 0.0f;
    }
    return mouseEvent->targetGlobalPositionY;
}

float HandleCTouchEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0.0f;
    }
    return touchEvent->targetGlobalPositionY;
}

float HandleCHoverEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        return 0.0f;
    }
    return hoverEvent->targetGlobalPositionY;
}

float HandleCClickEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        return 0.0f;
    }
    return clickEvent->targetGlobalPositionY;
}

float HandleCAxisEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0.0f;
    }
    return axisEvent->targetGlobalPositionY;
}

float HandleCFocusAxisEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        return 0.0f;
    }
    return focusAxisEvent->targetGlobalPositionY;
}

float HandleAxisEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        return 0.0f;
    }
    return axisEvent->targetGlobalPositionY;
}

float HandleTouchEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return 0.0f;
    }
    return touchEvent->targetGlobalPositionY;
}

float OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    std::map<ArkUIEventTypeId, std::function<float(ArkUI_UIInputEvent*)>> eventHandlers = {
        { C_TOUCH_EVENT_ID, HandleCTouchEventTargetGlobalPositionY },
        { TOUCH_EVENT_ID, HandleTouchEventTargetGlobalPositionY },
        { AXIS_EVENT_ID, HandleAxisEventTargetGlobalPositionY },
        { C_MOUSE_EVENT_ID, HandleCMouseEventTargetGlobalPositionY },
        { C_AXIS_EVENT_ID, HandleCAxisEventTargetGlobalPositionY },
        { C_FOCUS_AXIS_EVENT_ID, HandleCFocusAxisEventTargetGlobalPositionY },
        { C_HOVER_EVENT_ID, HandleCHoverEventTargetGlobalPositionY },
        { C_CLICK_EVENT_ID, HandleCClickEventTargetGlobalPositionY },
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return it->second(inputEvent);
    }
    return 0.0f;
}

int32_t HandleCMouseEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    *keys = mouseEvent->modifierKeyState;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t HandleCTouchEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    *keys = touchEvent->modifierKeyState;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t HandleCHoverEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    *keys = hoverEvent->modifierKeyState;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t HandleCClickEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    *keys = clickEvent->modifierKeyState;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t HandleCAxisEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    *keys = axisEvent->modifierKeyState;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t HandleCKeyEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    *keys = keyEvent->modifierKeyState;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t HandleCFocusAxisEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    *keys = focusAxisEvent->modifierKeyState;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t HandleAxisEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    *keys = axisEvent->modifierKeyState;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t HandleTouchEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    *keys = touchEvent->modifierKeyState;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_UIInputEvent_GetModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    if (!event || !keys) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    std::map<ArkUIEventTypeId, std::function<int32_t(ArkUI_UIInputEvent*, uint64_t*)>> eventHandlers = {
        { C_TOUCH_EVENT_ID, HandleCTouchEventModifierKeyStates },
        { TOUCH_EVENT_ID, HandleTouchEventModifierKeyStates },
        { AXIS_EVENT_ID, HandleAxisEventModifierKeyStates },
        { C_MOUSE_EVENT_ID, HandleCMouseEventModifierKeyStates },
        { C_AXIS_EVENT_ID, HandleCAxisEventModifierKeyStates },
        { C_KEY_EVENT_ID, HandleCKeyEventModifierKeyStates },
        { C_FOCUS_AXIS_EVENT_ID, HandleCFocusAxisEventModifierKeyStates },
        { C_HOVER_EVENT_ID, HandleCHoverEventModifierKeyStates },
        { C_CLICK_EVENT_ID, HandleCClickEventModifierKeyStates },
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        uint64_t* inputkeys = const_cast<uint64_t*>(keys);
        return it->second(inputEvent, inputkeys);
    }
    return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
}

bool OH_ArkUI_HoverEvent_IsHovered(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return false;
    }
    switch (event->eventTypeId) {
        case C_HOVER_EVENT_ID: {
            const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
            if (!hoverEvent) {
                return false;
            }
            return hoverEvent->isHover;
        }
        default:
            break;
    }
    return false;
}

int32_t OH_ArkUI_AxisEvent_SetPropagation(const ArkUI_UIInputEvent* event, bool propagation)
{
    if (!event) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    switch (event->eventTypeId) {
        case C_AXIS_EVENT_ID: {
            auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (axisEvent) {
                axisEvent->propagation = propagation;
                break;
            }
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
        default:
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AxisEvent_GetScrollStep(const ArkUI_UIInputEvent* event)
{
    int32_t scroll_step_value = 0;

    if (!event) {
        return scroll_step_value;
    }
    switch (event->eventTypeId) {
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (axisEvent) {
                scroll_step_value = axisEvent->scrollStep;
            }
            break;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (axisEvent) {
                scroll_step_value = axisEvent->scrollStep;
            }
            break;
        }
        default:
            break;
    }
    return scroll_step_value;
}

int32_t OH_ArkUI_PointerEvent_CreateClonedEvent(const ArkUI_UIInputEvent* event, ArkUI_UIInputEvent** clonedEvent)
{
    if (!event) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!fullImpl) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_UIInputEvent* currentEvent = new ArkUI_UIInputEvent();
    currentEvent->inputType = event->inputType;
    currentEvent->eventTypeId = event->eventTypeId;
    ArkUITouchEvent* touchEventCloned = new ArkUITouchEvent();
    fullImpl->getNodeModifiers()->getCommonModifier()->createClonedTouchEvent(touchEventCloned, touchEvent);
    currentEvent->inputEvent = touchEventCloned;
    currentEvent->isCloned = true;
    *clonedEvent = currentEvent;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_PointerEvent_DestroyClonedEvent(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!event->isCloned) {
        return ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT;
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (touchEvent) {
        delete touchEvent;
        touchEvent = nullptr;
    }
    delete event;
    event = nullptr;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(const ArkUI_UIInputEvent* event, float x, float y)
{
    if (!event) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!event->isCloned) {
        return ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT;
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    touchEvent->actionTouchPoint.nodeX = x;
    touchEvent->actionTouchPoint.nodeY = y;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(
    const ArkUI_UIInputEvent* event, float x, float y, int32_t pointerIndex)
{
    if (!event) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!event->isCloned) {
        return ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT;
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    touchEvent->touchPointes[pointerIndex].nodeX = x;
    touchEvent->touchPointes[pointerIndex].nodeY = y;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_PointerEvent_SetClonedEventActionType(const ArkUI_UIInputEvent* event, int32_t actionType)
{
    if (!event) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!event->isCloned) {
        return ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT;
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    touchEvent->action = actionType;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(const ArkUI_UIInputEvent* event, int32_t fingerId)
{
    if (!event) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!event->isCloned) {
        return ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT;
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    touchEvent->actionTouchPoint.id = fingerId;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(
    const ArkUI_UIInputEvent* event, int32_t fingerId, int32_t pointerIndex)
{
    if (!event) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!event->isCloned) {
        return ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT;
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    touchEvent->touchPointes[pointerIndex].id = fingerId;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_PointerEvent_PostClonedEvent(ArkUI_NodeHandle node, const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!node) {
        return ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL;
    }
    if (!event->isCloned) {
        return ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT;
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!fullImpl) {
        return ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL;
    }
    int32_t res = fullImpl->getNodeModifiers()->getCommonModifier()->postTouchEvent(node->uiNodeHandle, touchEvent);
    return res;
}

#ifdef __cplusplus
};
#endif
