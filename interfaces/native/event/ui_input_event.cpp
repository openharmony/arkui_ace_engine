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

int32_t OH_ArkUI_UIInputEvent_GetSourceType(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent) {
                return static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
            }
            return touchEvent->sourceType;
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                return static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
            }
            return mouseEvent->sourceType;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                return static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
            }
            return axisEvent->sourceType;
        }
        case C_FOCUS_AXIS_EVENT_ID: {
            const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
            if (!focusAxisEvent) {
                return static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
            }
            return focusAxisEvent->sourceType;
        }
        default:
            break;
    }
    return static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
}

int32_t OH_ArkUI_UIInputEvent_GetToolType(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent) {
                return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
            }
            return OHOS::Ace::NodeModel::ConvertToCInputEventToolType(touchEvent->actionTouchPoint.toolType);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
            }
            return OHOS::Ace::NodeModel::ConvertToCInputEventToolType(mouseEvent->actionTouchPoint.toolType);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
            }
            return OHOS::Ace::NodeModel::ConvertToCInputEventToolType(axisEvent->actionTouchPoint.toolType);
        }
        case C_FOCUS_AXIS_EVENT_ID: {
            const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
            if (!focusAxisEvent) {
                return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
            }
            return OHOS::Ace::NodeModel::ConvertToCInputEventToolType(focusAxisEvent->toolType);
        }
        default:
            break;
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

int32_t OH_ArkUI_UIInputEvent_GetDeviceId(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        return -1;
    }
    std::map<ArkUIEventTypeId, std::function<int64_t(ArkUI_UIInputEvent*)>> eventHandlers = {
        {C_KEY_EVENT_ID, GetCKeyEventDeviceId},
        {C_FOCUS_AXIS_EVENT_ID, GetCFocusAxisEventDeviceId},
    };
    auto iter = eventHandlers.find(event->eventTypeId);
    if (iter != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return iter->second(inputEvent);
    }
    return -1;
}

int32_t GetCKeyEventPressedKeys(
    const ArkUI_UIInputEvent* event, int32_t* pressedKeyCodes, int32_t* length)
{
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

int32_t GetCFocusAxisEventPressedKeys(
    const ArkUI_UIInputEvent* event, int32_t* pressedKeyCodes, int32_t* length)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto inputLength = *length;
    if (focusAxisEvent->keyCodesLength > inputLength) {
        return ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH;
    }
    *length = focusAxisEvent->keyCodesLength;
    for (int i = 0; i < focusAxisEvent->keyCodesLength; i++) {
        pressedKeyCodes[i] = focusAxisEvent->pressedKeyCodes[i];
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_UIInputEvent_GetPressedKeys(
    const ArkUI_UIInputEvent* event, int32_t* pressedKeyCodes, int32_t* length)
{
    if (!event || !pressedKeyCodes || !length) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    std::map<ArkUIEventTypeId, std::function<int64_t(ArkUI_UIInputEvent*, int32_t*, int32_t*)>> eventHandlers = {
        {C_KEY_EVENT_ID, GetCKeyEventPressedKeys},
        {C_FOCUS_AXIS_EVENT_ID, GetCFocusAxisEventPressedKeys},
    };
    auto iter = eventHandlers.find(event->eventTypeId);
    if (iter != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return iter->second(inputEvent, pressedKeyCodes, length);
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

float OH_ArkUI_PointerEvent_GetX(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent) {
                return 0.0f;
            }
            return touchEvent->actionTouchPoint.nodeX;
        }
        case TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
            if (touchEvent) {
                return touchEvent->localX;
            }
            break;
        }
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (axisEvent) {
                return axisEvent->localX;
            }
            break;
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                return 0.0f;
            }
            return mouseEvent->actionTouchPoint.nodeX;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                return 0.0f;
            }
            return axisEvent->actionTouchPoint.nodeX;
        }
        default:
            break;
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

float OH_ArkUI_PointerEvent_GetY(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent) {
                return 0.0f;
            }
            return touchEvent->actionTouchPoint.nodeY;
        }
        case TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
            if (touchEvent) {
                return touchEvent->localY;
            }
            break;
        }
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (axisEvent) {
                return axisEvent->localY;
            }
            break;
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                return 0.0f;
            }
            return mouseEvent->actionTouchPoint.nodeY;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                return 0.0f;
            }
            return axisEvent->actionTouchPoint.nodeY;
        }
        default:
            break;
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

float OH_ArkUI_PointerEvent_GetWindowX(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent) {
                return 0.0f;
            }
            return touchEvent->actionTouchPoint.windowX;
        }
        case TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
            if (touchEvent) {
                return touchEvent->x;
            }
            break;
        }
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (axisEvent) {
                return axisEvent->x;
            }
            break;
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                return 0.0f;
            }
            return mouseEvent->actionTouchPoint.windowX;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                return 0.0f;
            }
            return axisEvent->actionTouchPoint.windowX;
        }
        default:
            break;
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

float OH_ArkUI_PointerEvent_GetWindowY(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent) {
                return 0.0f;
            }
            return touchEvent->actionTouchPoint.windowY;
        }
        case TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
            if (touchEvent) {
                return touchEvent->y;
            }
            break;
        }
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (axisEvent) {
                return axisEvent->y;
            }
            break;
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                return 0.0f;
            }
            return mouseEvent->actionTouchPoint.windowY;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                return 0.0f;
            }
            return axisEvent->actionTouchPoint.windowY;
        }
        default:
            break;
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

float OH_ArkUI_PointerEvent_GetDisplayX(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent) {
                return 0.0f;
            }
            return touchEvent->actionTouchPoint.screenX;
        }
        case TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
            if (touchEvent) {
                return touchEvent->screenX;
            }
            break;
        }
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (axisEvent) {
                return axisEvent->screenX;
            }
            break;
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                return 0.0f;
            }
            return mouseEvent->actionTouchPoint.screenX;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                return 0.0f;
            }
            return axisEvent->actionTouchPoint.screenX;
        }
        default:
            break;
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

float OH_ArkUI_PointerEvent_GetDisplayY(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent) {
                return 0.0f;
            }
            return touchEvent->actionTouchPoint.screenY;
        }
        case TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
            if (touchEvent) {
                return touchEvent->screenY;
            }
            break;
        }
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (axisEvent) {
                return axisEvent->screenY;
            }
            break;
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                return 0.0f;
            }
            return mouseEvent->actionTouchPoint.screenY;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                return 0.0f;
            }
            return axisEvent->actionTouchPoint.screenY;
        }
        default:
            break;
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
        default:
            break;
    }
    return 0.0f;
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

#ifdef __cplusplus
};
#endif
