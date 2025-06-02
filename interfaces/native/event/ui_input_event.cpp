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
#include "frameworks/core/common/ace_application_info.h"

#ifdef __cplusplus
extern "C" {
#endif

thread_local ArkUI_ErrorCode g_latestEventStatus = ARKUI_ERROR_CODE_NO_ERROR;
thread_local ArkUI_ErrorCode g_scenarioSupportCheckResult = ARKUI_ERROR_CODE_NO_ERROR;

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
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_KEY_EVENT | S_NODE_ON_KEY_PRE_IME | S_NODE_ON_FOCUS_AXIS |
                                      S_NODE_DISPATCH_KEY_EVENT | S_NODE_ON_AXIS | S_NODE_ON_HOVER_MOVE |
                                      S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT |
                                      S_GESTURE_CLICK_EVENT | S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (event->apiVersion >= static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY)) {
        RETURN_WITH_STATUS(event->inputType, ARKUI_ERROR_CODE_NO_ERROR);
    }
    switch (event->eventTypeId) {
        case C_KEY_EVENT_ID: {
            RETURN_WITH_STATUS(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
        }
        case C_FOCUS_AXIS_EVENT_ID: {
            RETURN_WITH_STATUS(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
        }
        case C_CLICK_EVENT_ID: {
            if (event->inputType == ARKUI_UIINPUTEVENT_TYPE_KEY) {
                RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_NO_ERROR);
            }
            break;
        }
        default: {
            break;
        }
    }
    RETURN_WITH_STATUS(event->inputType, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_UIInputEvent_GetAction_Ext(const ArkUI_UIInputEvent* event)
{
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent) {
                RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                OHOS::Ace::NodeModel::ConvertToCTouchActionType(touchEvent->action), ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                OHOS::Ace::NodeModel::ConvertToCMouseActionType(mouseEvent->action), ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                OHOS::Ace::NodeModel::ConvertToCAxisActionType(axisEvent->action), ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_CLICK_EVENT_ID: {
            const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
            if (!keyEvent) {
                RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                OHOS::Ace::NodeModel::ConvertToCKeyActionType(keyEvent->type), ARKUI_ERROR_CODE_NO_ERROR);
        }
        case TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
            if (!touchEvent) {
                RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(OHOS::Ace::NodeModel::ConvertToCTouchActionType(static_cast<int32_t>(touchEvent->type)),
                ARKUI_ERROR_CODE_NO_ERROR);
        }
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(OHOS::Ace::NodeModel::ConvertToCAxisActionType(static_cast<int32_t>(axisEvent->action)),
                ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(-1, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_UIInputEvent_GetAction(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
                                      S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT | S_GESTURE_CLICK_EVENT |
                                      S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (event->apiVersion >= static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY)) {
        return OH_ArkUI_UIInputEvent_GetAction_Ext(event);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent) {
                RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                OHOS::Ace::NodeModel::ConvertToCTouchActionType(touchEvent->action), ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                OHOS::Ace::NodeModel::ConvertToCMouseActionType(mouseEvent->action), ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(-1, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t HandleCTouchEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->sourceType, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCClickEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_WITH_STATUS(static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(clickEvent->sourceType, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCMouseEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_WITH_STATUS(static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(mouseEvent->sourceType, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCAxisEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->sourceType, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCFocusAxisEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_WITH_STATUS(static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(focusAxisEvent->sourceType, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCHoverEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_WITH_STATUS(static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(hoverEvent->sourceType, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleAxisEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(static_cast<int32_t>(axisEvent->sourceType), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_UIInputEvent_GetSourceType(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_FOCUS_AXIS | S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT |
                                      S_NODE_ON_HOVER_EVENT | S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT |
                                      S_GESTURE_MOUSE_EVENT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
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
        RETURN_WITH_STATUS(it->second(inputEvent), ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_WITH_STATUS(
        static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t HandleCTouchEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(OHOS::Ace::NodeModel::ConvertToCInputEventToolType(touchEvent->actionTouchPoint.toolType),
        ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCMouseEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_WITH_STATUS(static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(OHOS::Ace::NodeModel::ConvertToCInputEventToolType(mouseEvent->actionTouchPoint.toolType),
        ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCHoverEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_WITH_STATUS(static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(
        OHOS::Ace::NodeModel::ConvertToCInputEventToolType(hoverEvent->toolType), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCClickEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_WITH_STATUS(static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(
        OHOS::Ace::NodeModel::ConvertToCInputEventToolType(clickEvent->toolType), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCAxisEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(OHOS::Ace::NodeModel::ConvertToCInputEventToolType(axisEvent->actionTouchPoint.toolType),
        ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCFocusAxisEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_WITH_STATUS(static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(
        OHOS::Ace::NodeModel::ConvertToCInputEventToolType(focusAxisEvent->toolType), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleAxisEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(OHOS::Ace::NodeModel::ConvertToCInputEventToolType(static_cast<int32_t>(axisEvent->sourceTool)),
        ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_UIInputEvent_GetToolType(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_FOCUS_AXIS | S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT |
                                      S_NODE_ON_HOVER_EVENT | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
                                      S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_WITH_STATUS(
        static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int64_t HandleCTouchEvent(ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->timeStamp, ARKUI_ERROR_CODE_NO_ERROR);
}

int64_t HandleTouchEvent(ArkUI_UIInputEvent* event)
{
    const auto* uiEvent = reinterpret_cast<const OHOS::Ace::PointerEvent*>(event->inputEvent);
    if (!uiEvent) {
        LOGE("The parameter of OH_ArkUI_UIInputEvent_GetEventTime is invalid");
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(uiEvent->time.time_since_epoch().count(), ARKUI_ERROR_CODE_NO_ERROR);
}

int64_t HandleAxisEvent(ArkUI_UIInputEvent* event)
{
    const auto* uiEvent = reinterpret_cast<const OHOS::Ace::PointerEvent*>(event->inputEvent);
    if (!uiEvent) {
        LOGE("The parameter of OH_ArkUI_UIInputEvent_GetEventTime is invalid");
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(uiEvent->time.time_since_epoch().count(), ARKUI_ERROR_CODE_NO_ERROR);
}

int64_t HandleCMouseEvent(ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(mouseEvent->timeStamp, ARKUI_ERROR_CODE_NO_ERROR);
}

int64_t HandleCAxisEvent(ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->timeStamp, ARKUI_ERROR_CODE_NO_ERROR);
}

int64_t HandleCKeyEvent(ArkUI_UIInputEvent* event)
{
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(keyEvent->timestamp, ARKUI_ERROR_CODE_NO_ERROR);
}

int64_t HandleCFocusAxisEvent(ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(focusAxisEvent->timeStamp, ARKUI_ERROR_CODE_NO_ERROR);
}

int64_t HandleCHoverEventTimestamp(ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(hoverEvent->timeStamp, ARKUI_ERROR_CODE_NO_ERROR);
}

int64_t HandleCClickEventTimestamp(ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(clickEvent->timestamp, ARKUI_ERROR_CODE_NO_ERROR);
}

int64_t OH_ArkUI_UIInputEvent_GetEventTime(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario =
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE | S_NODE_ON_KEY_EVENT | S_NODE_ON_KEY_PRE_IME |
        S_NODE_ON_FOCUS_AXIS | S_NODE_DISPATCH_KEY_EVENT | S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT |
        S_NODE_ON_HOVER_EVENT | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT |
        S_GESTURE_MOUSE_EVENT | S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_WITH_STATUS(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t GetCKeyEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(static_cast<int32_t>(keyEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t GetCFocusAxisEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(static_cast<int32_t>(focusAxisEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t GetCMouseEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(static_cast<int32_t>(mouseEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t GetCTouchEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (event->apiVersion < static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY) &&
        touchEvent->subKind == ON_TOUCH_INTERCEPT) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    if (event->apiVersion < static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY) &&
        touchEvent->subKind == ON_HOVER_MOVE) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    RETURN_WITH_STATUS(static_cast<int32_t>(touchEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t GetCHoverEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(static_cast<int32_t>(hoverEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t GetCClickEventDeviceId(ArkUI_UIInputEvent* event)
{
    if (event->inputType == ARKUI_UIINPUTEVENT_TYPE_KEY) {
        if (event->apiVersion >= static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY)) {
            const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
            if (!keyEvent) {
                RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(static_cast<int32_t>(keyEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
        }
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_NO_ERROR);
    }
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(static_cast<int32_t>(clickEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t GetCAxisEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (axisEvent->subKind == ON_AXIS &&
        event->apiVersion < static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY)) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    RETURN_WITH_STATUS(static_cast<int32_t>(axisEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t GetAxisEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(static_cast<int32_t>(axisEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t GetTouchEventDeviceId(ArkUI_UIInputEvent* event)
{
    if (event->apiVersion < static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY)) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(static_cast<int32_t>(touchEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_UIInputEvent_GetDeviceId(const ArkUI_UIInputEvent *event)
{
    const int32_t supportedScenario =
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE | S_NODE_ON_KEY_EVENT | S_NODE_ON_KEY_PRE_IME |
        S_NODE_ON_FOCUS_AXIS | S_NODE_DISPATCH_KEY_EVENT | S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT |
        S_NODE_ON_HOVER_EVENT | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT |
        S_GESTURE_MOUSE_EVENT | S_GESTURE_CLICK_EVENT | S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_WITH_STATUS(-1, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_UIInputEvent_GetPressedKeys(
    const ArkUI_UIInputEvent* event, int32_t* pressedKeyCodes, int32_t* length)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_ON_KEY_EVENT | S_NODE_ON_KEY_PRE_IME | S_NODE_DISPATCH_KEY_EVENT, event);
    if (!event || !pressedKeyCodes || !length) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto inputLength = *length;
    if (keyEvent->keyCodesLength > inputLength) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH, ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH);
    }
    *length = keyEvent->keyCodesLength;
    for (int i = 0; i < keyEvent->keyCodesLength; i++) {
        pressedKeyCodes[i] = keyEvent->pressedKeyCodes[i];
    }

    RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

uint32_t OH_ArkUI_PointerEvent_GetPointerCount(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
        S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT | S_GESTURE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent) {
                RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(touchEvent->touchPointSize, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(1, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(1, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_CLICK_EVENT_ID: {
            const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
            if (!clickEvent) {
                RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(clickEvent->clickPointSize, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_GetPointerId(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT |
                                      S_GESTURE_MOUSE_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }

            RETURN_WITH_STATUS(touchEvent->touchPointes[pointerIndex].id, ARKUI_ERROR_CODE_PARAM_INVALID);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(mouseEvent->actionTouchPoint.id, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(axisEvent->actionTouchPoint.id, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCClickEventX(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(clickEvent->localX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCTouchEventX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->actionTouchPoint.nodeX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCMouseEventX(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(mouseEvent->actionTouchPoint.nodeX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->actionTouchPoint.nodeX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        RETURN_WITH_STATUS(touchEvent->localX, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float HandleAxisEventX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        RETURN_WITH_STATUS(axisEvent->localX, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float OH_ArkUI_PointerEvent_GetX(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_MOVE |
                                      S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT |
                                      S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
        RETURN_WITH_STATUS(it->second(inputEvent), ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
                                      S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(touchEvent->touchPointes[pointerIndex].nodeX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(mouseEvent->actionTouchPoint.nodeX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(axisEvent->actionTouchPoint.nodeX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCClickEventY(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(clickEvent->localY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCTouchEventY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->actionTouchPoint.nodeY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCMouseEventY(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(mouseEvent->actionTouchPoint.nodeY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->actionTouchPoint.nodeY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        RETURN_WITH_STATUS(touchEvent->localY, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float HandleAxisEventY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        RETURN_WITH_STATUS(axisEvent->localY, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float OH_ArkUI_PointerEvent_GetY(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_MOVE |
                                      S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT |
                                      S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
        RETURN_WITH_STATUS(it->second(inputEvent), ARKUI_ERROR_CODE_NO_ERROR);
    }
    LOGE("The parameter of OH_ArkUI_PointerEvent_GetY is invalid");
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
                                      S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(touchEvent->touchPointes[pointerIndex].nodeY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(mouseEvent->actionTouchPoint.nodeY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(axisEvent->actionTouchPoint.nodeY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCTouchEventWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->actionTouchPoint.windowX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        RETURN_WITH_STATUS(touchEvent->x, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float HandleAxisEventWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        RETURN_WITH_STATUS(axisEvent->x, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float HandleCMouseEventWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(mouseEvent->actionTouchPoint.windowX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->actionTouchPoint.windowX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(clickEvent->windowX, ARKUI_ERROR_CODE_NO_ERROR);
}

float OH_ArkUI_PointerEvent_GetWindowX(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_MOVE |
                                      S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT |
                                      S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetWindowXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
                                      S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(touchEvent->touchPointes[pointerIndex].windowX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(mouseEvent->actionTouchPoint.windowX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(axisEvent->actionTouchPoint.windowX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCClickEventWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(clickEvent->windowY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCTouchEventWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->actionTouchPoint.windowY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->actionTouchPoint.windowY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCMouseEventWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(mouseEvent->actionTouchPoint.windowY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        RETURN_WITH_STATUS(touchEvent->y, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float HandleAxisEventWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        RETURN_WITH_STATUS(axisEvent->y, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float OH_ArkUI_PointerEvent_GetWindowY(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_MOVE |
                                      S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT |
                                      S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
        RETURN_WITH_STATUS(it->second(inputEvent), ARKUI_ERROR_CODE_NO_ERROR);
    }
    LOGE("The parameter of OH_ArkUI_PointerEvent_GetWindowY is invalid");
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetWindowYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
                                      S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(touchEvent->touchPointes[pointerIndex].windowY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(mouseEvent->actionTouchPoint.windowY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(axisEvent->actionTouchPoint.windowY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCTouchEventDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->actionTouchPoint.screenX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(clickEvent->displayX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCMouseEventDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(mouseEvent->actionTouchPoint.screenX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->actionTouchPoint.screenX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        RETURN_WITH_STATUS(touchEvent->screenX, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float HandleAxisEventDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        RETURN_WITH_STATUS(axisEvent->screenX, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float OH_ArkUI_PointerEvent_GetDisplayX(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_MOVE |
                                      S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT |
                                      S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetDisplayXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
                                      S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(touchEvent->touchPointes[pointerIndex].screenX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(mouseEvent->actionTouchPoint.screenX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(axisEvent->actionTouchPoint.screenX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCTouchEventDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->actionTouchPoint.screenY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(clickEvent->displayY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCMouseEventDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(mouseEvent->actionTouchPoint.screenY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->actionTouchPoint.screenY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        RETURN_WITH_STATUS(touchEvent->screenY, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float HandleAxisEventDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        RETURN_WITH_STATUS(axisEvent->screenY, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float OH_ArkUI_PointerEvent_GetDisplayY(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_MOVE |
                                      S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT |
                                      S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
        RETURN_WITH_STATUS(it->second(inputEvent), ARKUI_ERROR_CODE_NO_ERROR);
    }
    LOGE("The parameter of OH_ArkUI_PointerEvent_GetDisplayY is invalid");
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetDisplayYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
                                      S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(touchEvent->touchPointes[pointerIndex].screenY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(mouseEvent->actionTouchPoint.screenY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(axisEvent->actionTouchPoint.screenY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetPressure(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
        S_GESTURE_TOUCH_EVENT | S_GESTURE_MOUSE_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                touchEvent->touchPointes[touchEvent->touchPointSize - 1].pressure, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(mouseEvent->actionTouchPoint.pressure, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_CLICK_EVENT_ID: {
            const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
            if (!clickEvent) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(clickEvent->pressure, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetTiltX(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_CLICK_EVENT |
        S_NODE_ON_HOVER_EVENT | S_GESTURE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                touchEvent->touchPointes[touchEvent->touchPointSize - 1].tiltX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_CLICK_EVENT_ID: {
            const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
            if (!clickEvent) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(clickEvent->tiltX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_HOVER_EVENT_ID: {
            const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
            if (!hoverEvent) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(hoverEvent->tiltX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetTiltY(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_CLICK_EVENT |
        S_NODE_ON_HOVER_EVENT | S_GESTURE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(touchEvent->touchPointes[touchEvent->touchPointSize-1].tiltY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_CLICK_EVENT_ID: {
            const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
            if (!clickEvent) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(clickEvent->tiltY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_HOVER_EVENT_ID: {
            const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
            if (!hoverEvent) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(hoverEvent->tiltY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_PointerEvent_GetRollAngle(const ArkUI_UIInputEvent* event, double* rollAngle)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_CLICK_EVENT |
                                      S_NODE_ON_HOVER_EVENT | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (rollAngle == nullptr || event == nullptr) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (touchEvent && touchEvent->subKind == ON_HOVER_MOVE) {
                *rollAngle = touchEvent->actionTouchPoint.rollAngle;
                RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
            }
            if (touchEvent && touchEvent->subKind == ON_TOUCH) {
                *rollAngle = touchEvent->rollAngle;
                RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
            }
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                RETURN_WITH_STATUS(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            *rollAngle = touchEvent->touchPointes[touchEvent->touchPointSize - 1].rollAngle;
            RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_CLICK_EVENT_ID: {
            const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
            if (!clickEvent) {
                RETURN_WITH_STATUS(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            *rollAngle = clickEvent->rollAngle;
            RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_HOVER_EVENT_ID: {
            const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
            if (!hoverEvent) {
                RETURN_WITH_STATUS(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            *rollAngle = hoverEvent->rollAngle;
            RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_PointerEvent_GetInteractionHand(const ArkUI_UIInputEvent *event, ArkUI_InteractionHand *hand)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_GESTURE_TOUCH_EVENT, event);
    if (!event || !hand) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_PARAM_INVALID);
}

int32_t OH_ArkUI_PointerEvent_GetInteractionHandByIndex(const ArkUI_UIInputEvent *event, int32_t pointerIndex,
    ArkUI_InteractionHand *hand)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_GESTURE_TOUCH_EVENT, event);
    if (!event || !hand) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }

    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_WITH_STATUS(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            *hand = static_cast<ArkUI_InteractionHand>(touchEvent->touchPointes[pointerIndex].operatingHand);
            break;
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float OH_ArkUI_PointerEvent_GetTouchAreaWidth(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                touchEvent->touchPointes[touchEvent->touchPointSize - 1].contactAreaWidth, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetTouchAreaHeight(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                touchEvent->touchPointes[touchEvent->touchPointSize - 1].contactAreaHeight, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_PointerEvent_GetChangedPointerId(const ArkUI_UIInputEvent* event, uint32_t* pointerIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_GESTURE_TOUCH_EVENT, event);
    if (!event || !pointerIndex) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                RETURN_WITH_STATUS(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            *pointerIndex = touchEvent->changedPointerId;
            RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

uint32_t OH_ArkUI_PointerEvent_GetHistorySize(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || !touchEvent->historyEvents) {
                RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(touchEvent->historySize, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int64_t OH_ArkUI_PointerEvent_GetHistoryEventTime(const ArkUI_UIInputEvent* event, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || !touchEvent->historyEvents || touchEvent->historySize <= historyIndex ||
                historyIndex < 0) {
                RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(touchEvent->historyEvents[historyIndex].timeStamp, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

uint32_t OH_ArkUI_PointerEvent_GetHistoryPointerCount(const ArkUI_UIInputEvent* event, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || !touchEvent->historyEvents || touchEvent->historySize <= historyIndex ||
                historyIndex < 0) {
                RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(touchEvent->historyEvents[historyIndex].touchPointSize, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_PointerEvent_GetHistoryPointerId(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].id, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryX(const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].nodeX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryY(const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].nodeY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryWindowX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].windowX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryWindowY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].windowY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryDisplayX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].screenX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryDisplayY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].screenY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryPressure(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].pressure, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryTiltX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].tiltX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryTiltY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].tiltY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].contactAreaWidth,
                ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].contactAreaHeight,
                ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

double OH_ArkUI_AxisEvent_GetVerticalAxisValue(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_AXIS | S_GESTURE_AXIS_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (axisEvent) {
                RETURN_WITH_STATUS(axisEvent->verticalAxis, ARKUI_ERROR_CODE_NO_ERROR);
            }
            break;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                RETURN_WITH_STATUS(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(axisEvent->verticalAxis, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

double OH_ArkUI_AxisEvent_GetHorizontalAxisValue(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_GESTURE_AXIS_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (axisEvent) {
                RETURN_WITH_STATUS(axisEvent->horizontalAxis, ARKUI_ERROR_CODE_NO_ERROR);
            }
            break;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                RETURN_WITH_STATUS(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(axisEvent->horizontalAxis, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

double OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_GESTURE_AXIS_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (axisEvent) {
                RETURN_WITH_STATUS(axisEvent->pinchAxisScale, ARKUI_ERROR_CODE_NO_ERROR);
            }
            break;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                RETURN_WITH_STATUS(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(axisEvent->pinchAxisScale, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_AxisEvent_GetAxisAction(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_GESTURE_AXIS_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(UI_AXIS_EVENT_ACTION_NONE, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (axisEvent) {
                RETURN_WITH_STATUS(
                    OHOS::Ace::NodeModel::ConvertToCAxisActionType(static_cast<int32_t>(axisEvent->action)),
                    ARKUI_ERROR_CODE_NO_ERROR);
            }
            break;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (axisEvent) {
                RETURN_WITH_STATUS(
                    OHOS::Ace::NodeModel::ConvertToCAxisActionType(axisEvent->action), ARKUI_ERROR_CODE_NO_ERROR);
            }
            break;
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(UI_AXIS_EVENT_ACTION_NONE, ARKUI_ERROR_CODE_PARAM_INVALID);
}

int32_t OH_ArkUI_PointerEvent_SetInterceptHitTestMode(const ArkUI_UIInputEvent* event, HitTestMode mode)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_TOUCH_INTERCEPT, event);
    if (!event) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
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
                RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                mouseEvent->interceptResult = static_cast<int32_t>(mode), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
        }
        default:
            RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_PointerEvent_SetStopPropagation(const ArkUI_UIInputEvent* event, bool stopPropagation)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT | S_NODE_ON_MOUSE | S_NODE_ON_HOVER_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
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
            RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_MouseEvent_GetMouseButton(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_MOUSE, event);
    if (!event) {
        RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                OHOS::Ace::NodeModel::ConvertToCMouseEventButtonType(mouseEvent->button), ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(-1, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_MouseEvent_GetMouseAction(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_MOUSE | S_GESTURE_MOUSE_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                RETURN_WITH_STATUS(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(
                OHOS::Ace::NodeModel::ConvertToCMouseActionType(mouseEvent->action), ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(-1, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int64_t OH_ArkUI_PointerEvent_GetPressedTimeByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_GESTURE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(touchEvent->touchPointes[pointerIndex].pressedTime, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_MouseEvent_GetRawDeltaX(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_MOUSE, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_MOUSE_EVENT_ID: {
            auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(mouseEvent->rawDeltaX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_MouseEvent_GetRawDeltaY(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_MOUSE, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_MOUSE_EVENT_ID: {
            auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(mouseEvent->rawDeltaY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_UIInputEvent_GetTargetDisplayId(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario =
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE | S_NODE_ON_FOCUS_AXIS | S_NODE_ON_AXIS |
        S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_EVENT | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
        S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT | S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_WITH_STATUS(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto getTargetDisplayId = [](auto* specificEvent) -> int32_t {
        RETURN_WITH_STATUS(specificEvent ? specificEvent->targetDisplayId : 0, ARKUI_ERROR_CODE_NO_ERROR);
    };
    switch (event->eventTypeId) {
        case C_MOUSE_EVENT_ID:
            RETURN_WITH_STATUS(
                getTargetDisplayId(reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent)), ARKUI_ERROR_CODE_NO_ERROR);
        case C_TOUCH_EVENT_ID:
            RETURN_WITH_STATUS(
                getTargetDisplayId(reinterpret_cast<ArkUITouchEvent*>(event->inputEvent)), ARKUI_ERROR_CODE_NO_ERROR);
        case C_AXIS_EVENT_ID:
            RETURN_WITH_STATUS(
                getTargetDisplayId(reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent)), ARKUI_ERROR_CODE_NO_ERROR);
        case C_FOCUS_AXIS_EVENT_ID:
            RETURN_WITH_STATUS(getTargetDisplayId(reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent)),
                ARKUI_ERROR_CODE_NO_ERROR);
        case TOUCH_EVENT_ID: {
            RETURN_WITH_STATUS(getTargetDisplayId(reinterpret_cast<OHOS::Ace::TouchEvent*>(event->inputEvent)),
                ARKUI_ERROR_CODE_NO_ERROR);
        }
        case AXIS_EVENT_ID: {
            RETURN_WITH_STATUS(getTargetDisplayId(reinterpret_cast<OHOS::Ace::AxisEvent*>(event->inputEvent)),
                ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            RETURN_WITH_STATUS(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
}

int32_t OH_ArkUI_MouseEvent_GetPressedButtons(const ArkUI_UIInputEvent* event, int32_t* pressedButtons, int32_t* length)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_MOUSE, event);
    if (!event || !pressedButtons || !length) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_MOUSE_EVENT_ID: {
            auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                RETURN_WITH_STATUS(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            auto inputLength = *length;
            if (mouseEvent->pressedButtonsLength > inputLength) {
                RETURN_WITH_STATUS(ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH, ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH);
            }
            *length = mouseEvent->pressedButtonsLength;
            for (int i = 0; i < mouseEvent->pressedButtonsLength; i++) {
                pressedButtons[i] = mouseEvent->pressedButtons[i];
            }
            RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

double OH_ArkUI_FocusAxisEvent_GetAxisValue(const ArkUI_UIInputEvent* event, int32_t axis)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_FOCUS_AXIS, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (event->eventTypeId != C_FOCUS_AXIS_EVENT_ID) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_WITH_STATUS(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (axis) {
        case UI_FOCUS_AXIS_EVENT_ABS_X:
            RETURN_WITH_STATUS(focusAxisEvent->absXValue, ARKUI_ERROR_CODE_NO_ERROR);
        case UI_FOCUS_AXIS_EVENT_ABS_Y:
            RETURN_WITH_STATUS(focusAxisEvent->absYValue, ARKUI_ERROR_CODE_NO_ERROR);
        case UI_FOCUS_AXIS_EVENT_ABS_Z:
            RETURN_WITH_STATUS(focusAxisEvent->absZValue, ARKUI_ERROR_CODE_NO_ERROR);
        case UI_FOCUS_AXIS_EVENT_ABS_RZ:
            RETURN_WITH_STATUS(focusAxisEvent->absRzValue, ARKUI_ERROR_CODE_NO_ERROR);
        case UI_FOCUS_AXIS_EVENT_ABS_GAS:
            RETURN_WITH_STATUS(focusAxisEvent->absGasValue, ARKUI_ERROR_CODE_NO_ERROR);
        case UI_FOCUS_AXIS_EVENT_ABS_BRAKE:
            RETURN_WITH_STATUS(focusAxisEvent->absBrakeValue, ARKUI_ERROR_CODE_NO_ERROR);
        case UI_FOCUS_AXIS_EVENT_ABS_HAT0X:
            RETURN_WITH_STATUS(focusAxisEvent->absHat0XValue, ARKUI_ERROR_CODE_NO_ERROR);
        case UI_FOCUS_AXIS_EVENT_ABS_HAT0Y:
            RETURN_WITH_STATUS(focusAxisEvent->absHat0YValue, ARKUI_ERROR_CODE_NO_ERROR);
        default:
            RETURN_WITH_STATUS(0.0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    RETURN_WITH_STATUS(0.0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_FocusAxisEvent_SetStopPropagation(const ArkUI_UIInputEvent* event, bool stopPropagation)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_FOCUS_AXIS, event);
    if (!event) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_FOCUS_AXIS_EVENT_ID: {
            auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
            focusAxisEvent->stopPropagation = stopPropagation;
            break;
        }
        default:
            RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCMouseEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(mouseEvent->width, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCTouchEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->width, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCHoverEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(hoverEvent->width, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(clickEvent->width, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->width, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCFocusAxisEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(focusAxisEvent->width, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleAxisEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->width, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->width, ARKUI_ERROR_CODE_NO_ERROR);
}

float OH_ArkUI_UIInputEvent_GetEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_MOUSE | S_NODE_ON_FOCUS_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_EVENT |
        S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCMouseEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(mouseEvent->height, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCTouchEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->height, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCHoverEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(hoverEvent->height, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(clickEvent->height, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->height, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCFocusAxisEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(focusAxisEvent->height, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleAxisEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->height, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->height, ARKUI_ERROR_CODE_NO_ERROR);
}

float OH_ArkUI_UIInputEvent_GetEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_MOUSE | S_NODE_ON_FOCUS_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_EVENT |
        S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCMouseEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(mouseEvent->targetPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCTouchEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->targetPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCHoverEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(hoverEvent->targetPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(clickEvent->targetPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->targetPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCFocusAxisEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(focusAxisEvent->targetPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleAxisEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->targetPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->targetPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float OH_ArkUI_UIInputEvent_GetEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_MOUSE | S_NODE_ON_FOCUS_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_EVENT |
        S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCMouseEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(mouseEvent->targetPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCTouchEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->targetPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCHoverEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(hoverEvent->targetPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(clickEvent->targetPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->targetPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCFocusAxisEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(focusAxisEvent->targetPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleAxisEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->targetPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->targetPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float OH_ArkUI_UIInputEvent_GetEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_MOUSE | S_NODE_ON_FOCUS_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_EVENT |
        S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCMouseEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(mouseEvent->targetGlobalPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCTouchEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->targetGlobalPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCHoverEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(hoverEvent->targetGlobalPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(clickEvent->targetGlobalPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->targetGlobalPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCFocusAxisEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(focusAxisEvent->targetGlobalPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleAxisEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->targetGlobalPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->targetGlobalPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_MOUSE | S_NODE_ON_FOCUS_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_EVENT |
        S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCMouseEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(mouseEvent->targetGlobalPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCTouchEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->targetGlobalPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCHoverEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(hoverEvent->targetGlobalPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(clickEvent->targetGlobalPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->targetGlobalPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCFocusAxisEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(focusAxisEvent->targetGlobalPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleAxisEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(axisEvent->targetGlobalPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_WITH_STATUS(touchEvent->targetGlobalPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_MOUSE | S_NODE_ON_FOCUS_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_EVENT |
        S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_WITH_STATUS(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t HandleCMouseEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    *keys = mouseEvent->modifierKeyState;
    RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCTouchEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    *keys = touchEvent->modifierKeyState;
    RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCHoverEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    *keys = hoverEvent->modifierKeyState;
    RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCClickEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    *keys = clickEvent->modifierKeyState;
    RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCAxisEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    *keys = axisEvent->modifierKeyState;
    RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCKeyEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    *keys = keyEvent->modifierKeyState;
    RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCFocusAxisEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    *keys = focusAxisEvent->modifierKeyState;
    RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleAxisEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    *keys = axisEvent->modifierKeyState;
    RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleTouchEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    *keys = touchEvent->modifierKeyState;
    RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_UIInputEvent_GetModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_MOUSE | S_NODE_ON_KEY_EVENT |
                                      S_NODE_ON_FOCUS_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_EVENT |
                                      S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT |
                                      S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event || !keys) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
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
        RETURN_WITH_STATUS(it->second(inputEvent, inputkeys), ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

bool OH_ArkUI_HoverEvent_IsHovered(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_HOVER_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(false, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_HOVER_EVENT_ID: {
            const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
            if (!hoverEvent) {
                RETURN_WITH_STATUS(false, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_WITH_STATUS(hoverEvent->isHover, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_WITH_STATUS(false, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_AxisEvent_SetPropagation(const ArkUI_UIInputEvent* event, bool propagation)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_FOCUS_AXIS, event);
    if (!event) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_AXIS_EVENT_ID: {
            auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (axisEvent) {
                axisEvent->propagation = propagation;
                break;
            }
            RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
        }
        default:
            RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_AxisEvent_GetScrollStep(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_AXIS | S_GESTURE_AXIS_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    int32_t scroll_step_value = 0;

    if (!event) {
        RETURN_WITH_STATUS(scroll_step_value, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_WITH_STATUS(scroll_step_value, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_CreateClonedEvent(const ArkUI_UIInputEvent* event, ArkUI_UIInputEvent** clonedEvent)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!fullImpl) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    ArkUI_UIInputEvent* currentEvent = new ArkUI_UIInputEvent();
    currentEvent->inputType = event->inputType;
    currentEvent->eventTypeId = event->eventTypeId;
    ArkUITouchEvent* touchEventCloned = new ArkUITouchEvent();
    fullImpl->getNodeModifiers()->getCommonModifier()->createClonedTouchEvent(touchEventCloned, touchEvent);
    currentEvent->inputEvent = touchEventCloned;
    currentEvent->isCloned = true;
    *clonedEvent = currentEvent;
    RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_DestroyClonedEvent(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (!event->isCloned) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (touchEvent) {
        delete touchEvent;
        touchEvent = nullptr;
    }
    delete event;
    event = nullptr;
    RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(const ArkUI_UIInputEvent* event, float x, float y)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (!event->isCloned) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    touchEvent->actionTouchPoint.nodeX = x;
    touchEvent->actionTouchPoint.nodeY = y;
    RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(
    const ArkUI_UIInputEvent* event, float x, float y, int32_t pointerIndex)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (!event->isCloned) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    touchEvent->touchPointes[pointerIndex].nodeX = x;
    touchEvent->touchPointes[pointerIndex].nodeY = y;
    RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_SetClonedEventActionType(const ArkUI_UIInputEvent* event, int32_t actionType)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (!event->isCloned) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    touchEvent->action = actionType;
    RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(const ArkUI_UIInputEvent* event, int32_t fingerId)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (!event->isCloned) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    touchEvent->actionTouchPoint.id = fingerId;
    RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(
    const ArkUI_UIInputEvent* event, int32_t fingerId, int32_t pointerIndex)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (!event->isCloned) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    touchEvent->touchPointes[pointerIndex].id = fingerId;
    RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_PostClonedEvent(ArkUI_NodeHandle node, const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (!node) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL,
            ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL);
    }
    if (!event->isCloned) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_WITH_STATUS(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!fullImpl) {
        RETURN_WITH_STATUS(ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL,
            ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL);
    }
    int32_t res = fullImpl->getNodeModifiers()->getCommonModifier()->postTouchEvent(node->uiNodeHandle, touchEvent);
    RETURN_WITH_STATUS(res, ARKUI_ERROR_CODE_NO_ERROR);
}

ArkUI_ErrorCode IsTouchEventSupportedScenario(int32_t scenarioExpr, const ArkUITouchEvent* touchEvent) {
    if (!touchEvent) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    bool support = false;
    if (touchEvent->subKind == ON_TOUCH) {
        // mouse event registed by NODE_ON_TOUCH
        support = scenarioExpr & S_NODE_ON_MOUSE;
    } else if (touchEvent->subKind == ON_TOUCH_INTERCEPT) {
        // key event registed by NODE_ON_TOUCH_INTERCEPT
        support = scenarioExpr & S_NODE_ON_TOUCH_INTERCEPT;
    } else if (touchEvent->subKind == ON_HOVER_MOVE) {
        // key event registed by NODE_ON_HOVER_MOVE
        support = scenarioExpr & S_NODE_ON_HOVER_MOVE;
    } else {
        // gesture triggered by touch
        support = scenarioExpr & S_GESTURE_TOUCH_EVENT;
    }
    return support ? ARKUI_ERROR_CODE_NO_ERROR : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
}

ArkUI_ErrorCode IsMouseEventSupportedScenario(int32_t scenarioExpr, const ArkUIMouseEvent* mouseEvent) {
    if (!mouseEvent) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    bool support = false;
    if (mouseEvent->subKind == ON_MOUSE) {
        // mouse event registed by NODE_ON_MOUSE
        support = scenarioExpr & S_NODE_ON_MOUSE;
    } else {
        // gesture triggered by mouse
        support = scenarioExpr & S_GESTURE_MOUSE_EVENT;
    }
    return support ? ARKUI_ERROR_CODE_NO_ERROR : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
}

ArkUI_ErrorCode IsAxisEventSupportedScenario(int32_t scenarioExpr, const ArkUIAxisEvent* axisEvent) {
    if (!axisEvent) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    bool support = false;
    if (axisEvent->subKind == ON_AXIS) {
        // axis event registed by NODE_ON_AXIS
        support = scenarioExpr & S_NODE_ON_AXIS;
    } else {
        // gesture triggered by axis
        support = scenarioExpr & S_GESTURE_AXIS_EVENT;
    }
    return support ? ARKUI_ERROR_CODE_NO_ERROR : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
}


ArkUI_ErrorCode IsKeyEventSupportedScenario(int32_t scenarioExpr, const ArkUIKeyEvent* keyEvent) {
    if (!keyEvent) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    bool support = false;
    if (keyEvent->subKind == ON_KEY_EVENT) {
        // key event registed by NODE_ON_KEY_EVENT
        support = scenarioExpr & S_NODE_ON_KEY_EVENT;
    } else if (keyEvent->subKind == ON_KEY_PREIME) {
        // key event registed by NODE_ON_KEY_PREIME
        support = scenarioExpr & S_NODE_ON_KEY_PRE_IME;
    } else {
        // key event registed by NODE_NODE_DISPATCH_KEY_EVENT
        support = scenarioExpr & S_NODE_DISPATCH_KEY_EVENT;
    }
    return support ? ARKUI_ERROR_CODE_NO_ERROR : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
}

ArkUI_ErrorCode CheckIsSupportedScenario(int32_t scenarioExpr, const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    switch (event->eventTypeId) {
        case AXIS_EVENT_ID: {
            // axis event from nativeXComponent
            return scenarioExpr & S_NXC_DISPATCH_AXIS_EVENT ? ARKUI_ERROR_CODE_NO_ERROR
                                                            : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
        }
        case TOUCH_EVENT_ID: {
            // touch intercept from nativeXComponent
            return scenarioExpr & S_NXC_ON_TOUCH_INTERCEPT ? ARKUI_ERROR_CODE_NO_ERROR
                                                            : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
        }
        case C_TOUCH_EVENT_ID: {
            return IsTouchEventSupportedScenario(scenarioExpr, reinterpret_cast<ArkUITouchEvent*>(event->inputEvent));
        }
        case C_MOUSE_EVENT_ID: {
            return IsMouseEventSupportedScenario(scenarioExpr, reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent));
        }
        case C_AXIS_EVENT_ID: {
            return IsAxisEventSupportedScenario(scenarioExpr, reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent));
        }
        case C_KEY_EVENT_ID: {
            return IsKeyEventSupportedScenario(scenarioExpr, reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent));
        }
        case C_FOCUS_AXIS_EVENT_ID: {
            // focus axis event registed by NODE_ON_FOCUS_AXIS
            return scenarioExpr & S_NODE_ON_FOCUS_AXIS ? ARKUI_ERROR_CODE_NO_ERROR
                                                       : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
        }
        case C_CLICK_EVENT_ID: {
            if (event->inputType == ARKUI_UIINPUTEVENT_TYPE_KEY && scenarioExpr & S_GESTURE_CLICK_EVENT) {
                // click event from click or tap gesture triggered by keyboard
                return ARKUI_ERROR_CODE_NO_ERROR;
            } else if (scenarioExpr & S_NODE_ON_CLICK_EVENT) {
                // click event registed by NODE_ON_CLICK
                return ARKUI_ERROR_CODE_NO_ERROR;
            }
            return ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
        }
        case C_HOVER_EVENT_ID: {
            // hover event registed by NODE_ON_HOVER_EVENT
            return scenarioExpr & S_NODE_ON_HOVER_EVENT ? ARKUI_ERROR_CODE_NO_ERROR
                                                        : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
        }
        default:{
            LOGE("received event with unknown eventType");
        }
    }
    return ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
}

void CheckSupportedScenarioAndResetEventStatus(int32_t scenarioExpr, const ArkUI_UIInputEvent* event)
{
    g_scenarioSupportCheckResult = CheckIsSupportedScenario(scenarioExpr, event);
    g_latestEventStatus = ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_GetLastestEventStatus()
{
    return g_latestEventStatus;
}

#ifdef __cplusplus
};
#endif
