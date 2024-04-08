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

#include "base/utils/type_definition.h"
#include "core/event/touch_event.h"
#include "core/event/axis_event.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "interfaces/native/node/event_converter.h"

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
        default:
            break;
    }
    return static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
}

int64_t OH_ArkUI_UIInputEvent_GetEventTime(const ArkUI_UIInputEvent* event)
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
            return touchEvent->timeStamp;
        }
        case TOUCH_EVENT_ID: {
            const auto* uiEvent = reinterpret_cast<const OHOS::Ace::UIInputEvent*>(event->inputEvent);
            if (!uiEvent) {
                LOGE("The parameter of OH_ArkUI_UIInputEvent_GetEventTime is invalid");
                return 0;
            }
            return uiEvent->time.time_since_epoch().count();
        }
        case AXIS_EVENT_ID: {
            const auto* uiEvent = reinterpret_cast<const OHOS::Ace::UIInputEvent*>(event->inputEvent);
            if (!uiEvent) {
                LOGE("The parameter of OH_ArkUI_UIInputEvent_GetEventTime is invalid");
                return 0;
            }
            return uiEvent->time.time_since_epoch().count();
        }
        default:
            break;
    }
    return 0;
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
        default:
            break;
    }
    return 0.0;
}

#ifdef __cplusplus
};
#endif
