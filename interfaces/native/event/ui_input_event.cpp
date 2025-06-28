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
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (event->apiVersion >= static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY)) {
        RETURN_RET_WITH_STATUS_CHECK(event->inputType, ARKUI_ERROR_CODE_NO_ERROR);
    }
    switch (event->eventTypeId) {
        case C_KEY_EVENT_ID: {
            RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
        }
        case C_FOCUS_AXIS_EVENT_ID: {
            RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
        }
        case C_CLICK_EVENT_ID: {
            if (event->inputType == ARKUI_UIINPUTEVENT_TYPE_KEY) {
                RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_NO_ERROR);
            }
            break;
        }
        default: {
            break;
        }
    }
    RETURN_RET_WITH_STATUS_CHECK(event->inputType, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCTouchEventAction(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        OHOS::Ace::NodeModel::ConvertToCTouchActionType(touchEvent->action), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCMouseEventAction(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        OHOS::Ace::NodeModel::ConvertToCMouseActionType(mouseEvent->action), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCAxisEventAction(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        OHOS::Ace::NodeModel::ConvertToCAxisActionType(axisEvent->action), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCClickEventAction(const ArkUI_UIInputEvent* event)
{
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        OHOS::Ace::NodeModel::ConvertToCKeyActionType(keyEvent->type), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleTouchEventAction(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        OHOS::Ace::NodeModel::ConvertToCTouchActionType(static_cast<int32_t>(touchEvent->type)),
        ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleAxisEventAction(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        OHOS::Ace::NodeModel::ConvertToCAxisActionType(static_cast<int32_t>(axisEvent->action)),
        ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_UIInputEvent_GetAction_Ext(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    std::map<ArkUIEventTypeId, std::function<int32_t(ArkUI_UIInputEvent*)>> eventHandlers = {
        { C_TOUCH_EVENT_ID, HandleCTouchEventAction },
        { C_MOUSE_EVENT_ID, HandleCMouseEventAction },
        { C_AXIS_EVENT_ID, HandleCAxisEventAction },
        { C_CLICK_EVENT_ID, HandleCClickEventAction },
        { TOUCH_EVENT_ID, HandleTouchEventAction},
        { AXIS_EVENT_ID, HandleAxisEventAction },
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return it->second(inputEvent);
    }
    RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_UIInputEvent_GetAction(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
                                      S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT | S_GESTURE_CLICK_EVENT |
                                      S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (event->apiVersion >= static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY)) {
        return OH_ArkUI_UIInputEvent_GetAction_Ext(event);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent) {
                RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                OHOS::Ace::NodeModel::ConvertToCTouchActionType(touchEvent->action), ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                OHOS::Ace::NodeModel::ConvertToCMouseActionType(mouseEvent->action), ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t HandleCTouchEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(
            static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->sourceType, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCClickEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_RET_WITH_STATUS_CHECK(
            static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(clickEvent->sourceType, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCMouseEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(
            static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(mouseEvent->sourceType, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCAxisEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(
            static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->sourceType, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCFocusAxisEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(
            static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(focusAxisEvent->sourceType, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCHoverEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_RET_WITH_STATUS_CHECK(
            static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(hoverEvent->sourceType, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleAxisEventSourceType(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(
            static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(static_cast<int32_t>(axisEvent->sourceType), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_UIInputEvent_GetSourceType(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_FOCUS_AXIS | S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT |
                                      S_NODE_ON_HOVER_EVENT | S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT |
                                      S_GESTURE_MOUSE_EVENT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(
            static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_RET_WITH_STATUS_CHECK(
        static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t HandleCTouchEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(
            static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        OHOS::Ace::NodeModel::ConvertToCInputEventToolType(touchEvent->actionTouchPoint.toolType),
        ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCMouseEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(
            static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        OHOS::Ace::NodeModel::ConvertToCInputEventToolType(mouseEvent->actionTouchPoint.toolType),
        ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCHoverEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_RET_WITH_STATUS_CHECK(
            static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        OHOS::Ace::NodeModel::ConvertToCInputEventToolType(hoverEvent->toolType), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCClickEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_RET_WITH_STATUS_CHECK(
            static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        OHOS::Ace::NodeModel::ConvertToCInputEventToolType(clickEvent->toolType), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCAxisEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(
            static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        OHOS::Ace::NodeModel::ConvertToCInputEventToolType(axisEvent->actionTouchPoint.toolType),
        ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCFocusAxisEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(
            static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        OHOS::Ace::NodeModel::ConvertToCInputEventToolType(focusAxisEvent->toolType), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleAxisEventToolType(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(
            static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        OHOS::Ace::NodeModel::ConvertToCInputEventToolType(static_cast<int32_t>(axisEvent->sourceTool)),
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
        RETURN_RET_WITH_STATUS_CHECK(
            static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_RET_WITH_STATUS_CHECK(
        static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int64_t HandleCTouchEvent(ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->timeStamp, ARKUI_ERROR_CODE_NO_ERROR);
}

int64_t HandleTouchEvent(ArkUI_UIInputEvent* event)
{
    const auto* uiEvent = reinterpret_cast<const OHOS::Ace::PointerEvent*>(event->inputEvent);
    if (!uiEvent) {
        LOGE("The parameter of OH_ArkUI_UIInputEvent_GetEventTime is invalid");
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(uiEvent->time.time_since_epoch().count(), ARKUI_ERROR_CODE_NO_ERROR);
}

int64_t HandleAxisEvent(ArkUI_UIInputEvent* event)
{
    const auto* uiEvent = reinterpret_cast<const OHOS::Ace::PointerEvent*>(event->inputEvent);
    if (!uiEvent) {
        LOGE("The parameter of OH_ArkUI_UIInputEvent_GetEventTime is invalid");
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(uiEvent->time.time_since_epoch().count(), ARKUI_ERROR_CODE_NO_ERROR);
}

int64_t HandleCMouseEvent(ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(mouseEvent->timeStamp, ARKUI_ERROR_CODE_NO_ERROR);
}

int64_t HandleCAxisEvent(ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->timeStamp, ARKUI_ERROR_CODE_NO_ERROR);
}

int64_t HandleCKeyEvent(ArkUI_UIInputEvent* event)
{
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(keyEvent->timestamp, ARKUI_ERROR_CODE_NO_ERROR);
}

int64_t HandleCFocusAxisEvent(ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(focusAxisEvent->timeStamp, ARKUI_ERROR_CODE_NO_ERROR);
}

int64_t HandleCHoverEventTimestamp(ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(hoverEvent->timeStamp, ARKUI_ERROR_CODE_NO_ERROR);
}

int64_t HandleCClickEventTimestamp(ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(clickEvent->timestamp, ARKUI_ERROR_CODE_NO_ERROR);
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
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t GetCKeyEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(static_cast<int32_t>(keyEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t GetCFocusAxisEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(static_cast<int32_t>(focusAxisEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t GetCMouseEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(static_cast<int32_t>(mouseEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t GetCTouchEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (event->apiVersion < static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY) &&
        touchEvent->subKind == ON_TOUCH_INTERCEPT) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    if (event->apiVersion < static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY) &&
        touchEvent->subKind == ON_HOVER_MOVE) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    RETURN_RET_WITH_STATUS_CHECK(static_cast<int32_t>(touchEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t GetCHoverEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(static_cast<int32_t>(hoverEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t GetCClickEventDeviceId(ArkUI_UIInputEvent* event)
{
    if (event->inputType == ARKUI_UIINPUTEVENT_TYPE_KEY) {
        if (event->apiVersion >= static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY)) {
            const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
            if (!keyEvent) {
                RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(static_cast<int32_t>(keyEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
        }
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_NO_ERROR);
    }
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(static_cast<int32_t>(clickEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t GetCAxisEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (axisEvent->subKind == ON_AXIS &&
        event->apiVersion < static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY)) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    RETURN_RET_WITH_STATUS_CHECK(static_cast<int32_t>(axisEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t GetAxisEventDeviceId(ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(static_cast<int32_t>(axisEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t GetTouchEventDeviceId(ArkUI_UIInputEvent* event)
{
    if (event->apiVersion < static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY)) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(static_cast<int32_t>(touchEvent->deviceId), ARKUI_ERROR_CODE_NO_ERROR);
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
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_UIInputEvent_GetPressedKeys(
    const ArkUI_UIInputEvent* event, int32_t* pressedKeyCodes, int32_t* length)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_ON_KEY_EVENT | S_NODE_ON_KEY_PRE_IME | S_NODE_DISPATCH_KEY_EVENT, event);
    if (!event || !pressedKeyCodes || !length) {
        RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto inputLength = *length;
    if (keyEvent->keyCodesLength > inputLength) {
        RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH, ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH);
    }
    *length = keyEvent->keyCodesLength;
    for (int i = 0; i < keyEvent->keyCodesLength; i++) {
        pressedKeyCodes[i] = keyEvent->pressedKeyCodes[i];
    }

    RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

uint32_t OH_ArkUI_PointerEvent_GetPointerCount(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
        S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT | S_GESTURE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent) {
                RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(touchEvent->touchPointSize, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(1, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(1, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_CLICK_EVENT_ID: {
            const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
            if (!clickEvent) {
                RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(clickEvent->clickPointSize, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_GetPointerId(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT |
                                      S_GESTURE_MOUSE_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(touchEvent->touchPointes[pointerIndex].id, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(mouseEvent->actionTouchPoint.id, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(axisEvent->actionTouchPoint.id, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCClickEventX(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(clickEvent->localX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCTouchEventX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->actionTouchPoint.nodeX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCMouseEventX(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(mouseEvent->actionTouchPoint.nodeX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->actionTouchPoint.nodeX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(touchEvent->localX, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float HandleAxisEventX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(axisEvent->localX, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float OH_ArkUI_PointerEvent_GetX(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_MOVE |
                                      S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT |
                                      S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
                                      S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(touchEvent->touchPointes[pointerIndex].nodeX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(mouseEvent->actionTouchPoint.nodeX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(axisEvent->actionTouchPoint.nodeX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCClickEventY(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(clickEvent->localY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCTouchEventY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->actionTouchPoint.nodeY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCMouseEventY(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(mouseEvent->actionTouchPoint.nodeY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->actionTouchPoint.nodeY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(touchEvent->localY, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float HandleAxisEventY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(axisEvent->localY, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float OH_ArkUI_PointerEvent_GetY(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_MOVE |
                                      S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT |
                                      S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
                                      S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(touchEvent->touchPointes[pointerIndex].nodeY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(mouseEvent->actionTouchPoint.nodeY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(axisEvent->actionTouchPoint.nodeY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCTouchEventWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->actionTouchPoint.windowX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(touchEvent->x, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float HandleAxisEventWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(axisEvent->x, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float HandleCMouseEventWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(mouseEvent->actionTouchPoint.windowX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->actionTouchPoint.windowX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(clickEvent->windowX, ARKUI_ERROR_CODE_NO_ERROR);
}

float OH_ArkUI_PointerEvent_GetWindowX(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_MOVE |
                                      S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT |
                                      S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetWindowXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
                                      S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(touchEvent->touchPointes[pointerIndex].windowX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(mouseEvent->actionTouchPoint.windowX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(axisEvent->actionTouchPoint.windowX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCClickEventWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(clickEvent->windowY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCTouchEventWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->actionTouchPoint.windowY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->actionTouchPoint.windowY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCMouseEventWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(mouseEvent->actionTouchPoint.windowY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(touchEvent->y, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float HandleAxisEventWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(axisEvent->y, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float OH_ArkUI_PointerEvent_GetWindowY(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_MOVE |
                                      S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT |
                                      S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetWindowYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
                                      S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(touchEvent->touchPointes[pointerIndex].windowY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(mouseEvent->actionTouchPoint.windowY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(axisEvent->actionTouchPoint.windowY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCTouchEventDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->actionTouchPoint.screenX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(clickEvent->displayX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCMouseEventDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(mouseEvent->actionTouchPoint.screenX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->actionTouchPoint.screenX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(touchEvent->screenX, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float HandleAxisEventDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(axisEvent->screenX, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float OH_ArkUI_PointerEvent_GetDisplayX(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_MOVE |
                                      S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT |
                                      S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetDisplayXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
                                      S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(touchEvent->touchPointes[pointerIndex].screenX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(mouseEvent->actionTouchPoint.screenX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(axisEvent->actionTouchPoint.screenX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCTouchEventDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->actionTouchPoint.screenY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(clickEvent->displayY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCMouseEventDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(mouseEvent->actionTouchPoint.screenY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->actionTouchPoint.screenY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(touchEvent->screenY, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float HandleAxisEventDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(axisEvent->screenY, ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float OH_ArkUI_PointerEvent_GetDisplayY(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_MOVE |
                                      S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT |
                                      S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetDisplayYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
                                      S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(touchEvent->touchPointes[pointerIndex].screenY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(mouseEvent->actionTouchPoint.screenY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(axisEvent->actionTouchPoint.screenY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCTouchEventGlobalDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        static_cast<float>(touchEvent->actionTouchPoint.globalDisplayX), ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventGlobalDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(static_cast<float>(clickEvent->globalDisplayX), ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCHoverEventGlobalDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(static_cast<float>(hoverEvent->globalDisplayX), ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCMouseEventGlobalDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        static_cast<float>(mouseEvent->actionTouchPoint.globalDisplayX), ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventGlobalDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        static_cast<float>(axisEvent->actionTouchPoint.globalDisplayX), ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventGlobalDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(static_cast<float>(touchEvent->globalDisplayX), ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float HandleAxisEventGlobalDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(static_cast<float>(axisEvent->globalDisplayX), ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float OH_ArkUI_PointerEvent_GetGlobalDisplayX(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_MOVE |
                                      S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT |
                                      S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT | S_NODE_ON_HOVER_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    std::map<ArkUIEventTypeId, std::function<float(ArkUI_UIInputEvent*)>> eventHandlers = {
        { C_TOUCH_EVENT_ID, HandleCTouchEventGlobalDisplayX },
        { TOUCH_EVENT_ID, HandleTouchEventGlobalDisplayX },
        { AXIS_EVENT_ID, HandleAxisEventGlobalDisplayX },
        { C_MOUSE_EVENT_ID, HandleCMouseEventGlobalDisplayX },
        { C_AXIS_EVENT_ID, HandleCAxisEventGlobalDisplayX },
        { C_CLICK_EVENT_ID, HandleCClickEventGlobalDisplayX },
        { C_HOVER_EVENT_ID, HandleCHoverEventGlobalDisplayX },
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return it->second(inputEvent);
    }
    LOGE("The parameter of OH_ArkUI_PointerEvent_GetGlobalDisplayX is invalid");
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
                                      S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                static_cast<float>(touchEvent->touchPointes[pointerIndex].globalDisplayX), ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                static_cast<float>(mouseEvent->actionTouchPoint.globalDisplayX), ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                static_cast<float>(axisEvent->actionTouchPoint.globalDisplayX), ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCTouchEventGlobalDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        static_cast<float>(touchEvent->actionTouchPoint.globalDisplayY), ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventGlobalDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(static_cast<float>(clickEvent->globalDisplayY), ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCHoverEventGlobalDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(static_cast<float>(hoverEvent->globalDisplayY), ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCMouseEventGlobalDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        static_cast<float>(mouseEvent->actionTouchPoint.globalDisplayY), ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventGlobalDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(
        static_cast<float>(axisEvent->actionTouchPoint.globalDisplayY), ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventGlobalDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(static_cast<float>(touchEvent->globalDisplayY), ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float HandleAxisEventGlobalDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(static_cast<float>(axisEvent->globalDisplayY), ARKUI_ERROR_CODE_NO_ERROR);
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
}

float OH_ArkUI_PointerEvent_GetGlobalDisplayY(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_MOVE |
                                      S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT |
                                      S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT | S_NODE_ON_HOVER_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    std::map<ArkUIEventTypeId, std::function<float(ArkUI_UIInputEvent*)>> eventHandlers = {
        { C_TOUCH_EVENT_ID, HandleCTouchEventGlobalDisplayY },
        { TOUCH_EVENT_ID, HandleTouchEventGlobalDisplayY },
        { AXIS_EVENT_ID, HandleAxisEventGlobalDisplayY },
        { C_MOUSE_EVENT_ID, HandleCMouseEventGlobalDisplayY },
        { C_AXIS_EVENT_ID, HandleCAxisEventGlobalDisplayY },
        { C_CLICK_EVENT_ID, HandleCClickEventGlobalDisplayY },
        { C_HOVER_EVENT_ID, HandleCHoverEventGlobalDisplayY },
    };
    auto it = eventHandlers.find(event->eventTypeId);
    if (it != eventHandlers.end()) {
        ArkUI_UIInputEvent* inputEvent = const_cast<ArkUI_UIInputEvent*>(event);
        return it->second(inputEvent);
    }
    LOGE("The parameter of OH_ArkUI_PointerEvent_GetGlobalDisplayY is invalid");
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
                                      S_NODE_ON_AXIS | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
                                      S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                static_cast<float>(touchEvent->touchPointes[pointerIndex].globalDisplayY), ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent || pointerIndex != 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                static_cast<float>(mouseEvent->actionTouchPoint.globalDisplayY), ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent || pointerIndex != 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                static_cast<float>(axisEvent->actionTouchPoint.globalDisplayY), ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetPressure(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE |
        S_GESTURE_TOUCH_EVENT | S_GESTURE_MOUSE_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                touchEvent->touchPointes[touchEvent->touchPointSize - 1].pressure, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(mouseEvent->actionTouchPoint.pressure, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_CLICK_EVENT_ID: {
            const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
            if (!clickEvent) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(clickEvent->pressure, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetTiltX(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_CLICK_EVENT |
                                      S_NODE_ON_HOVER_EVENT | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (touchEvent && touchEvent->subKind == ON_HOVER_MOVE) {
                RETURN_RET_WITH_STATUS_CHECK(touchEvent->actionTouchPoint.tiltX, ARKUI_ERROR_CODE_NO_ERROR);
            }
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                touchEvent->touchPointes[touchEvent->touchPointSize - 1].tiltX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_CLICK_EVENT_ID: {
            const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
            if (!clickEvent) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(clickEvent->tiltX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_HOVER_EVENT_ID: {
            const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
            if (!hoverEvent) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(hoverEvent->tiltX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetTiltY(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_CLICK_EVENT |
                                      S_NODE_ON_HOVER_EVENT | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (touchEvent && touchEvent->subKind == ON_HOVER_MOVE) {
                RETURN_RET_WITH_STATUS_CHECK(touchEvent->actionTouchPoint.tiltY, ARKUI_ERROR_CODE_NO_ERROR);
            }
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                touchEvent->touchPointes[touchEvent->touchPointSize - 1].tiltY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_CLICK_EVENT_ID: {
            const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
            if (!clickEvent) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(clickEvent->tiltY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_HOVER_EVENT_ID: {
            const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
            if (!hoverEvent) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(hoverEvent->tiltY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_PointerEvent_GetRollAngle(const ArkUI_UIInputEvent* event, double* rollAngle)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_CLICK_EVENT |
                                      S_NODE_ON_HOVER_EVENT | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (rollAngle == nullptr || event == nullptr) {
        RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (touchEvent && touchEvent->subKind == ON_HOVER_MOVE) {
                *rollAngle = touchEvent->actionTouchPoint.rollAngle;
                RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
            }
            if (touchEvent && touchEvent->subKind == ON_TOUCH) {
                *rollAngle = touchEvent->rollAngle;
                RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
            }
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            *rollAngle = touchEvent->touchPointes[touchEvent->touchPointSize - 1].rollAngle;
            RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_CLICK_EVENT_ID: {
            const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
            if (!clickEvent) {
                RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            *rollAngle = clickEvent->rollAngle;
            RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_HOVER_EVENT_ID: {
            const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
            if (!hoverEvent) {
                RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            *rollAngle = hoverEvent->rollAngle;
            RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_PointerEvent_GetInteractionHand(const ArkUI_UIInputEvent *event, ArkUI_InteractionHand *hand)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_GESTURE_TOUCH_EVENT, event);
    if (!event || !hand) {
        RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            *hand = static_cast<ArkUI_InteractionHand>(touchEvent->actionTouchPoint.operatingHand);
            break;
        }
        default:
            RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_GetInteractionHandByIndex(const ArkUI_UIInputEvent *event, int32_t pointerIndex,
    ArkUI_InteractionHand *hand)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_GESTURE_TOUCH_EVENT, event);
    if (!event || !hand) {
        RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }

    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            *hand = static_cast<ArkUI_InteractionHand>(touchEvent->touchPointes[pointerIndex].operatingHand);
            break;
        }
        default:
            RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

float OH_ArkUI_PointerEvent_GetTouchAreaWidth(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                touchEvent->touchPointes[touchEvent->touchPointSize - 1].contactAreaWidth, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetTouchAreaHeight(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                touchEvent->touchPointes[touchEvent->touchPointSize - 1].contactAreaHeight, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_PointerEvent_GetChangedPointerId(const ArkUI_UIInputEvent* event, uint32_t* pointerIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_GESTURE_TOUCH_EVENT, event);
    if (!event || !pointerIndex) {
        RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || touchEvent->touchPointSize <= 0) {
                RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            *pointerIndex = touchEvent->changedPointerId;
            RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

uint32_t OH_ArkUI_PointerEvent_GetHistorySize(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || !touchEvent->historyEvents) {
                RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(touchEvent->historySize, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int64_t OH_ArkUI_PointerEvent_GetHistoryEventTime(const ArkUI_UIInputEvent* event, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || !touchEvent->historyEvents || touchEvent->historySize <= historyIndex ||
                historyIndex < 0) {
                RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(touchEvent->historyEvents[historyIndex].timeStamp, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

uint32_t OH_ArkUI_PointerEvent_GetHistoryPointerCount(const ArkUI_UIInputEvent* event, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!touchEvent || !touchEvent->historyEvents || touchEvent->historySize <= historyIndex ||
                historyIndex < 0) {
                RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                touchEvent->historyEvents[historyIndex].touchPointSize, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_PointerEvent_GetHistoryPointerId(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].id, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryX(const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].nodeX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryY(const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].nodeY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryWindowX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].windowX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryWindowY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].windowY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryDisplayX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].screenX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryDisplayY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].screenY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                static_cast<float>(touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].globalDisplayX),
                ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                static_cast<float>(touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].globalDisplayY),
                ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryPressure(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].pressure, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryTiltX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].tiltX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryTiltY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].tiltY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].contactAreaWidth,
                ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_HOVER_MOVE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isHistoryCTouchEventParamValid(touchEvent, historyIndex, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                touchEvent->historyEvents[historyIndex].touchPointes[pointerIndex].contactAreaHeight,
                ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

double OH_ArkUI_AxisEvent_GetVerticalAxisValue(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_AXIS | S_GESTURE_AXIS_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                RETURN_RET_WITH_STATUS_CHECK(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(axisEvent->verticalAxis, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                RETURN_RET_WITH_STATUS_CHECK(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(axisEvent->verticalAxis, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

double OH_ArkUI_AxisEvent_GetHorizontalAxisValue(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_GESTURE_AXIS_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                RETURN_RET_WITH_STATUS_CHECK(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(axisEvent->horizontalAxis, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                RETURN_RET_WITH_STATUS_CHECK(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(axisEvent->horizontalAxis, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

double OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_GESTURE_AXIS_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                RETURN_RET_WITH_STATUS_CHECK(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(axisEvent->pinchAxisScale, ARKUI_ERROR_CODE_NO_ERROR);
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (!axisEvent) {
                RETURN_RET_WITH_STATUS_CHECK(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(axisEvent->pinchAxisScale, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_AxisEvent_GetAxisAction(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_GESTURE_AXIS_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(UI_AXIS_EVENT_ACTION_NONE, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
            if (axisEvent) {
                RETURN_RET_WITH_STATUS_CHECK(
                    OHOS::Ace::NodeModel::ConvertToCAxisActionType(static_cast<int32_t>(axisEvent->action)),
                    ARKUI_ERROR_CODE_NO_ERROR);
            }
            break;
        }
        case C_AXIS_EVENT_ID: {
            const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (axisEvent) {
                RETURN_RET_WITH_STATUS_CHECK(
                    OHOS::Ace::NodeModel::ConvertToCAxisActionType(axisEvent->action), ARKUI_ERROR_CODE_NO_ERROR);
            }
            break;
        }
        default:
            RETURN_RET_WITH_STATUS_CHECK(UI_AXIS_EVENT_ACTION_NONE, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    RETURN_RET_WITH_STATUS_CHECK(UI_AXIS_EVENT_ACTION_NONE, ARKUI_ERROR_CODE_PARAM_INVALID);
}

int32_t OH_ArkUI_PointerEvent_SetInterceptHitTestMode(const ArkUI_UIInputEvent* event, HitTestMode mode)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_TOUCH_INTERCEPT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
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
                RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                mouseEvent->interceptResult = static_cast<int32_t>(mode), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
        }
        default:
            RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_SetStopPropagation(const ArkUI_UIInputEvent* event, bool stopPropagation)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT | S_NODE_ON_MOUSE | S_NODE_ON_HOVER_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
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
            RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_MouseEvent_GetMouseButton(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_MOUSE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                OHOS::Ace::NodeModel::ConvertToCMouseEventButtonType(mouseEvent->button), ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_MouseEvent_GetMouseAction(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_MOUSE | S_GESTURE_MOUSE_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_MOUSE_EVENT_ID: {
            const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(
                OHOS::Ace::NodeModel::ConvertToCMouseActionType(mouseEvent->action), ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int64_t OH_ArkUI_PointerEvent_GetPressedTimeByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_GESTURE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_TOUCH_EVENT_ID: {
            const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
            if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
                RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(touchEvent->touchPointes[pointerIndex].pressedTime, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_MouseEvent_GetRawDeltaX(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_MOUSE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_MOUSE_EVENT_ID: {
            auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(mouseEvent->rawDeltaX, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float OH_ArkUI_MouseEvent_GetRawDeltaY(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_MOUSE, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_MOUSE_EVENT_ID: {
            auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(mouseEvent->rawDeltaY, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_UIInputEvent_GetTargetDisplayId(const ArkUI_UIInputEvent* event)
{
    const int32_t supportedScenario =
        S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT | S_NODE_ON_MOUSE | S_NODE_ON_FOCUS_AXIS | S_NODE_ON_AXIS |
        S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_EVENT | S_NODE_ON_HOVER_MOVE | S_GESTURE_TOUCH_EVENT |
        S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT | S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto getTargetDisplayId = [](auto* specificEvent) -> int32_t {
        return specificEvent ? specificEvent->targetDisplayId : 0;
    };
    switch (event->eventTypeId) {
        case C_MOUSE_EVENT_ID:
            RETURN_RET_WITH_STATUS_CHECK(
                getTargetDisplayId(reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent)), ARKUI_ERROR_CODE_NO_ERROR);
        case C_TOUCH_EVENT_ID:
            RETURN_RET_WITH_STATUS_CHECK(
                getTargetDisplayId(reinterpret_cast<ArkUITouchEvent*>(event->inputEvent)), ARKUI_ERROR_CODE_NO_ERROR);
        case C_AXIS_EVENT_ID:
            RETURN_RET_WITH_STATUS_CHECK(
                getTargetDisplayId(reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent)), ARKUI_ERROR_CODE_NO_ERROR);
        case C_FOCUS_AXIS_EVENT_ID:
            RETURN_RET_WITH_STATUS_CHECK(getTargetDisplayId(reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent)),
                ARKUI_ERROR_CODE_NO_ERROR);
        case TOUCH_EVENT_ID: {
            RETURN_RET_WITH_STATUS_CHECK(
                getTargetDisplayId(reinterpret_cast<OHOS::Ace::TouchEvent*>(event->inputEvent)),
                ARKUI_ERROR_CODE_NO_ERROR);
        }
        case AXIS_EVENT_ID: {
            RETURN_RET_WITH_STATUS_CHECK(getTargetDisplayId(reinterpret_cast<OHOS::Ace::AxisEvent*>(event->inputEvent)),
                ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
}

int32_t OH_ArkUI_MouseEvent_GetPressedButtons(const ArkUI_UIInputEvent* event, int32_t* pressedButtons, int32_t* length)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_MOUSE, event);
    if (!event || !pressedButtons || !length) {
        RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_MOUSE_EVENT_ID: {
            auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
            if (!mouseEvent) {
                RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            auto inputLength = *length;
            if (mouseEvent->pressedButtonsLength > inputLength) {
                RETURN_RET_WITH_STATUS_CHECK(
                    ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH, ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH);
            }
            *length = mouseEvent->pressedButtonsLength;
            for (int i = 0; i < mouseEvent->pressedButtonsLength; i++) {
                pressedButtons[i] = mouseEvent->pressedButtons[i];
            }
            RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

double OH_ArkUI_FocusAxisEvent_GetAxisValue(const ArkUI_UIInputEvent* event, int32_t axis)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_FOCUS_AXIS, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (event->eventTypeId != C_FOCUS_AXIS_EVENT_ID) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (axis) {
        case UI_FOCUS_AXIS_EVENT_ABS_X:
            RETURN_RET_WITH_STATUS_CHECK(focusAxisEvent->absXValue, ARKUI_ERROR_CODE_NO_ERROR);
        case UI_FOCUS_AXIS_EVENT_ABS_Y:
            RETURN_RET_WITH_STATUS_CHECK(focusAxisEvent->absYValue, ARKUI_ERROR_CODE_NO_ERROR);
        case UI_FOCUS_AXIS_EVENT_ABS_Z:
            RETURN_RET_WITH_STATUS_CHECK(focusAxisEvent->absZValue, ARKUI_ERROR_CODE_NO_ERROR);
        case UI_FOCUS_AXIS_EVENT_ABS_RZ:
            RETURN_RET_WITH_STATUS_CHECK(focusAxisEvent->absRzValue, ARKUI_ERROR_CODE_NO_ERROR);
        case UI_FOCUS_AXIS_EVENT_ABS_GAS:
            RETURN_RET_WITH_STATUS_CHECK(focusAxisEvent->absGasValue, ARKUI_ERROR_CODE_NO_ERROR);
        case UI_FOCUS_AXIS_EVENT_ABS_BRAKE:
            RETURN_RET_WITH_STATUS_CHECK(focusAxisEvent->absBrakeValue, ARKUI_ERROR_CODE_NO_ERROR);
        case UI_FOCUS_AXIS_EVENT_ABS_HAT0X:
            RETURN_RET_WITH_STATUS_CHECK(focusAxisEvent->absHat0XValue, ARKUI_ERROR_CODE_NO_ERROR);
        case UI_FOCUS_AXIS_EVENT_ABS_HAT0Y:
            RETURN_RET_WITH_STATUS_CHECK(focusAxisEvent->absHat0YValue, ARKUI_ERROR_CODE_NO_ERROR);
        default:
            RETURN_RET_WITH_STATUS_CHECK(0.0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    RETURN_RET_WITH_STATUS_CHECK(0.0, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_FocusAxisEvent_SetStopPropagation(const ArkUI_UIInputEvent* event, bool stopPropagation)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_FOCUS_AXIS, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_FOCUS_AXIS_EVENT_ID: {
            auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
            focusAxisEvent->stopPropagation = stopPropagation;
            break;
        }
        default:
            RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCMouseEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(mouseEvent->width, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCTouchEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->width, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCHoverEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(hoverEvent->width, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(clickEvent->width, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->width, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCFocusAxisEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(focusAxisEvent->width, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleAxisEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->width, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->width, ARKUI_ERROR_CODE_NO_ERROR);
}

float OH_ArkUI_UIInputEvent_GetEventTargetWidth(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_MOUSE | S_NODE_ON_FOCUS_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_EVENT |
        S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCMouseEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(mouseEvent->height, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCTouchEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->height, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCHoverEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(hoverEvent->height, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(clickEvent->height, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->height, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCFocusAxisEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(focusAxisEvent->height, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleAxisEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->height, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->height, ARKUI_ERROR_CODE_NO_ERROR);
}

float OH_ArkUI_UIInputEvent_GetEventTargetHeight(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_MOUSE | S_NODE_ON_FOCUS_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_EVENT |
        S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCMouseEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(mouseEvent->targetPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCTouchEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->targetPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCHoverEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(hoverEvent->targetPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(clickEvent->targetPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->targetPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCFocusAxisEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(focusAxisEvent->targetPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleAxisEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->targetPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->targetPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float OH_ArkUI_UIInputEvent_GetEventTargetPositionX(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_MOUSE | S_NODE_ON_FOCUS_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_EVENT |
        S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCMouseEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(mouseEvent->targetPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCTouchEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->targetPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCHoverEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(hoverEvent->targetPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(clickEvent->targetPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->targetPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCFocusAxisEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(focusAxisEvent->targetPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleAxisEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->targetPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->targetPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float OH_ArkUI_UIInputEvent_GetEventTargetPositionY(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_MOUSE | S_NODE_ON_FOCUS_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_EVENT |
        S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCMouseEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(mouseEvent->targetGlobalPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCTouchEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->targetGlobalPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCHoverEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(hoverEvent->targetGlobalPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(clickEvent->targetGlobalPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->targetGlobalPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCFocusAxisEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(focusAxisEvent->targetGlobalPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleAxisEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->targetGlobalPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->targetGlobalPositionX, ARKUI_ERROR_CODE_NO_ERROR);
}

float OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_MOUSE | S_NODE_ON_FOCUS_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_EVENT |
        S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

float HandleCMouseEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    if (!mouseEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(mouseEvent->targetGlobalPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCTouchEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->targetGlobalPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCHoverEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    if (!hoverEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(hoverEvent->targetGlobalPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCClickEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    if (!clickEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(clickEvent->targetGlobalPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCAxisEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->targetGlobalPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleCFocusAxisEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    if (!focusAxisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(focusAxisEvent->targetGlobalPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleAxisEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    if (!axisEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(axisEvent->targetGlobalPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float HandleTouchEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(touchEvent->targetGlobalPositionY, ARKUI_ERROR_CODE_NO_ERROR);
}

float OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(
        S_NODE_TOUCH_EVENT | S_NODE_ON_MOUSE | S_NODE_ON_FOCUS_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_EVENT |
        S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_RET_WITH_STATUS_CHECK(0.0f, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t HandleCMouseEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(event->inputEvent);
    *keys = mouseEvent->modifierKeyState;
    RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCTouchEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    *keys = touchEvent->modifierKeyState;
    RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCHoverEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
    *keys = hoverEvent->modifierKeyState;
    RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCClickEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(event->inputEvent);
    *keys = clickEvent->modifierKeyState;
    RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCAxisEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
    *keys = axisEvent->modifierKeyState;
    RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCKeyEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    *keys = keyEvent->modifierKeyState;
    RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleCFocusAxisEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* focusAxisEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(event->inputEvent);
    *keys = focusAxisEvent->modifierKeyState;
    RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleAxisEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* axisEvent = reinterpret_cast<const OHOS::Ace::AxisEvent*>(event->inputEvent);
    *keys = axisEvent->modifierKeyState;
    RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t HandleTouchEventModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const auto* touchEvent = reinterpret_cast<const OHOS::Ace::TouchEvent*>(event->inputEvent);
    *keys = touchEvent->modifierKeyState;
    RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_UIInputEvent_GetModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys)
{
    const int32_t supportedScenario = S_NODE_TOUCH_EVENT | S_NODE_ON_MOUSE | S_NODE_ON_KEY_EVENT |
                                      S_NODE_ON_FOCUS_AXIS | S_NODE_ON_CLICK_EVENT | S_NODE_ON_HOVER_EVENT |
                                      S_GESTURE_TOUCH_EVENT | S_GESTURE_AXIS_EVENT | S_GESTURE_MOUSE_EVENT |
                                      S_NXC_ON_TOUCH_INTERCEPT | S_NXC_DISPATCH_AXIS_EVENT;
    CheckSupportedScenarioAndResetEventStatus(supportedScenario, event);
    if (!event || !keys) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
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
    RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

bool OH_ArkUI_HoverEvent_IsHovered(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_HOVER_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(false, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_HOVER_EVENT_ID: {
            const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(event->inputEvent);
            if (!hoverEvent) {
                RETURN_RET_WITH_STATUS_CHECK(false, ARKUI_ERROR_CODE_PARAM_INVALID);
            }
            RETURN_RET_WITH_STATUS_CHECK(hoverEvent->isHover, ARKUI_ERROR_CODE_NO_ERROR);
        }
        default:
            break;
    }
    RETURN_RET_WITH_STATUS_CHECK(false, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

int32_t OH_ArkUI_AxisEvent_SetPropagation(const ArkUI_UIInputEvent* event, bool propagation)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_AXIS, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    switch (event->eventTypeId) {
        case C_AXIS_EVENT_ID: {
            auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(event->inputEvent);
            if (axisEvent) {
                axisEvent->propagation = propagation;
                break;
            }
            RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
        }
        default:
            RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_AxisEvent_GetScrollStep(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_AXIS | S_GESTURE_AXIS_EVENT | S_NXC_DISPATCH_AXIS_EVENT, event);
    int32_t scroll_step_value = 0;

    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(scroll_step_value, ARKUI_ERROR_CODE_PARAM_INVALID);
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
            RETURN_RET_WITH_STATUS_CHECK(scroll_step_value, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
    }
    RETURN_RET_WITH_STATUS_CHECK(scroll_step_value, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_CreateClonedEvent(const ArkUI_UIInputEvent* event, ArkUI_UIInputEvent** clonedEvent)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!fullImpl) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    ArkUI_UIInputEvent* currentEvent = new ArkUI_UIInputEvent();
    currentEvent->inputType = event->inputType;
    currentEvent->eventTypeId = event->eventTypeId;
    ArkUITouchEvent* touchEventCloned = new ArkUITouchEvent();
    fullImpl->getNodeModifiers()->getCommonModifier()->createClonedTouchEvent(touchEventCloned, touchEvent);
    currentEvent->inputEvent = touchEventCloned;
    currentEvent->isCloned = true;
    *clonedEvent = currentEvent;
    RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_DestroyClonedEvent(const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (!event->isCloned) {
        RETURN_RET_WITH_STATUS_CHECK(
            ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (touchEvent) {
        delete touchEvent;
        touchEvent = nullptr;
    }
    delete event;
    event = nullptr;
    RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(const ArkUI_UIInputEvent* event, float x, float y)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (!event->isCloned) {
        RETURN_RET_WITH_STATUS_CHECK(
            ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    touchEvent->actionTouchPoint.nodeX = x;
    touchEvent->actionTouchPoint.nodeY = y;
    RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(
    const ArkUI_UIInputEvent* event, float x, float y, int32_t pointerIndex)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (!event->isCloned) {
        RETURN_RET_WITH_STATUS_CHECK(
            ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
        RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    touchEvent->touchPointes[pointerIndex].nodeX = x;
    touchEvent->touchPointes[pointerIndex].nodeY = y;
    RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_SetClonedEventActionType(const ArkUI_UIInputEvent* event, int32_t actionType)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (!event->isCloned) {
        RETURN_RET_WITH_STATUS_CHECK(
            ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    touchEvent->action = actionType;
    RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(const ArkUI_UIInputEvent* event, int32_t fingerId)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (!event->isCloned) {
        RETURN_RET_WITH_STATUS_CHECK(
            ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    touchEvent->actionTouchPoint.id = fingerId;
    RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(
    const ArkUI_UIInputEvent* event, int32_t fingerId, int32_t pointerIndex)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (!event->isCloned) {
        RETURN_RET_WITH_STATUS_CHECK(
            ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (!isCurrentCTouchEventParamValid(touchEvent, pointerIndex)) {
        RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    touchEvent->touchPointes[pointerIndex].id = fingerId;
    RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_PointerEvent_PostClonedEvent(ArkUI_NodeHandle node, const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_TOUCH_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    if (!node) {
        RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL,
            ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL);
    }
    if (!event->isCloned) {
        RETURN_RET_WITH_STATUS_CHECK(
            ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
    }
    auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(event->inputEvent);
    if (!touchEvent) {
        RETURN_RET_WITH_STATUS_CHECK(OHOS::Ace::ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!fullImpl) {
        RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL,
            ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL);
    }
    int32_t res = fullImpl->getNodeModifiers()->getCommonModifier()->postTouchEvent(node->uiNodeHandle, touchEvent);
    RETURN_RET_WITH_STATUS_CHECK(res, ARKUI_ERROR_CODE_NO_ERROR);
}

ArkUI_ErrorCode IsTouchEventSupportedScenario(int32_t scenarioExpr, const ArkUITouchEvent* touchEvent)
{
    if (!touchEvent) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    bool support = false;
    if (touchEvent->subKind == ON_TOUCH) {
        // mouse event registed by NODE_ON_TOUCH
        support = scenarioExpr & S_NODE_TOUCH_EVENT;
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

ArkUI_ErrorCode IsMouseEventSupportedScenario(int32_t scenarioExpr, const ArkUIMouseEvent* mouseEvent)
{
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

ArkUI_ErrorCode IsAxisEventSupportedScenario(int32_t scenarioExpr, const ArkUIAxisEvent* axisEvent)
{
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

ArkUI_ErrorCode IsKeyEventSupportedScenario(int32_t scenarioExpr, const ArkUIKeyEvent* keyEvent)
{
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
            if (event->inputType == ARKUI_UIINPUTEVENT_TYPE_KEY) {
                // click event from click or tap gesture triggered by keyboard
                return scenarioExpr & S_GESTURE_CLICK_EVENT ? ARKUI_ERROR_CODE_NO_ERROR
                                                            : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
            } else {
                // click event registed by NODE_ON_CLICK
                return scenarioExpr & S_NODE_ON_CLICK_EVENT ? ARKUI_ERROR_CODE_NO_ERROR
                                                            : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
            }
        }
        case C_HOVER_EVENT_ID: {
            // hover event registed by NODE_ON_HOVER_EVENT
            return scenarioExpr & S_NODE_ON_HOVER_EVENT ? ARKUI_ERROR_CODE_NO_ERROR
                                                        : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
        }
        default: {
            LOGE("received event with unknown eventType");
        }
    }
    return ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
}

ArkUI_ErrorCode OH_ArkUI_UIInputEvent_GetLatestStatus()
{
    return g_latestEventStatus;
}

#ifdef __cplusplus
};
#endif
