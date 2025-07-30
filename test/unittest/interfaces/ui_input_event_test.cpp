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

#include "ui_input_event_test.h"

#include "node_model.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
namespace {
constexpr int32_t ARKUI_DEVICE_ID = 1;
constexpr uint64_t ARKUI_TIME = 20;
constexpr ArkUI_Int32 AXIS_UPDATE = 2;
constexpr float ARKUI_X = 2.0;
constexpr float ARKUI_Y = 3.0;
constexpr float ARKUI_WIDTH = 2.0;
constexpr float ARKUI_HEIGHT = 3.0;
constexpr double ARKUI_TILTX = 2.0;
constexpr double ARKUI_TILTY = 3.0;
constexpr double ARKUI_PRESSURE = 1.0;
constexpr int32_t ARKUI_SOURCETYPE = 1;
constexpr int32_t ARKUI_TOOLTYPE = 7;
constexpr int32_t ARKUI_ACTIONTYPE = 1;
constexpr int32_t ARKUI_ACTIONTYPE_SET = 0;
constexpr int32_t ARKUI_FINGERID = 1;
constexpr int32_t ARKUI_FINGERID_SET = 0;
constexpr ArkUI_Uint64 ARKUI_MODIFIERKEYSTATE = 1;
constexpr ArkUI_Uint32 ARKUI_POINTERCOUNTER = 2;
} // namespace
/**
 * @tc.name: UIInputEventTest001
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, UIInputEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = ArkUIEventCategory::FOCUS_AXIS_EVENT;
    event.focusAxisEvent.subKind = ArkUIEventSubKind::ON_FOCUS_AXIS;
    event.focusAxisEvent.absXValue = 0.5;
    event.focusAxisEvent.absYValue = 0.5;
    event.focusAxisEvent.absZValue = 0.5;
    event.focusAxisEvent.absRzValue = 0.5;
    event.focusAxisEvent.absHat0XValue = 1;
    event.focusAxisEvent.absHat0YValue = 1;
    event.focusAxisEvent.absBrakeValue = 0.5;
    event.focusAxisEvent.absGasValue = 0.5;
    event.focusAxisEvent.sourceType = static_cast<int32_t>(SourceType::MOUSE);
    event.focusAxisEvent.toolType = static_cast<int32_t>(SourceTool::JOYSTICK);
    event.focusAxisEvent.deviceId = ARKUI_DEVICE_ID;
    event.focusAxisEvent.timeStamp = ARKUI_TIME;
    uiInputEvent.inputEvent = &event.focusAxisEvent;
    uiInputEvent.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    /**
     * @tc.steps: step2. call functions.
     */
    auto absXValue = OH_ArkUI_FocusAxisEvent_GetAxisValue(inputEvent, UI_FOCUS_AXIS_EVENT_ABS_X);
    auto absYValue = OH_ArkUI_FocusAxisEvent_GetAxisValue(inputEvent, UI_FOCUS_AXIS_EVENT_ABS_Y);
    auto absZValue = OH_ArkUI_FocusAxisEvent_GetAxisValue(inputEvent, UI_FOCUS_AXIS_EVENT_ABS_Z);
    auto absRzValue = OH_ArkUI_FocusAxisEvent_GetAxisValue(inputEvent, UI_FOCUS_AXIS_EVENT_ABS_RZ);
    auto absHat0XValue = OH_ArkUI_FocusAxisEvent_GetAxisValue(inputEvent, UI_FOCUS_AXIS_EVENT_ABS_HAT0X);
    auto absHat0YValue = OH_ArkUI_FocusAxisEvent_GetAxisValue(inputEvent, UI_FOCUS_AXIS_EVENT_ABS_HAT0Y);
    auto absBrakeValue = OH_ArkUI_FocusAxisEvent_GetAxisValue(inputEvent, UI_FOCUS_AXIS_EVENT_ABS_BRAKE);
    auto absGasValue = OH_ArkUI_FocusAxisEvent_GetAxisValue(inputEvent, UI_FOCUS_AXIS_EVENT_ABS_GAS);
    auto diviceId = OH_ArkUI_UIInputEvent_GetDeviceId(inputEvent);
    auto time = OH_ArkUI_UIInputEvent_GetEventTime(inputEvent);
    auto sourceType = OH_ArkUI_UIInputEvent_GetSourceType(inputEvent);
    auto toolType = OH_ArkUI_UIInputEvent_GetToolType(inputEvent);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(absXValue, 0.5);
    EXPECT_EQ(absYValue, 0.5);
    EXPECT_EQ(absZValue, 0.5);
    EXPECT_EQ(absRzValue, 0.5);
    EXPECT_EQ(absHat0XValue, 1);
    EXPECT_EQ(absHat0YValue, 1);
    EXPECT_EQ(absBrakeValue, 0.5);
    EXPECT_EQ(absGasValue, 0.5);
    EXPECT_EQ(diviceId, ARKUI_DEVICE_ID);
    EXPECT_EQ(time, ARKUI_TIME);
    EXPECT_EQ(sourceType, UI_INPUT_EVENTT_SOURCE_TYPE_MOUSE);
    EXPECT_EQ(toolType, UI_INPUT_EVENT_TOOL_TYPE_JOYSTICK);
}

/**
 * @tc.name: NativeTouchEventTest001
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetChangedPointerId function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, NativeTouchEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.touchEvent.changedPointerId = 1;
    event.touchEvent.touchPointSize = 1;
    uint32_t pointerIndex = 0;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    /**
     * @tc.steps: step2. call functions.
     */
    auto changed_PointerId = OH_ArkUI_PointerEvent_GetChangedPointerId(inputEvent, &pointerIndex);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(changed_PointerId, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(pointerIndex, 1);
}

/**
 * @tc.name: AxisEventGetActionTest001
 * @tc.desc: Test function OH_ArkUI_AxisEvent_GetAxisAction.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, AxisEventGetActionTest001, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(uiInputEvent, nullptr);
    auto event = std::make_unique<OHOS::Ace::AxisEvent>();
    EXPECT_NE(event, nullptr);

    event->action = AxisAction::BEGIN;
    uiInputEvent->inputEvent = static_cast<void*>(event.get());
    uiInputEvent->eventTypeId = AXIS_EVENT_ID;

    auto action = OH_ArkUI_AxisEvent_GetAxisAction(uiInputEvent.get());
    EXPECT_EQ(action, UI_AXIS_EVENT_ACTION_BEGIN);
}

/**
 * @tc.name: AxisEventGetActionTest002
 * @tc.desc: Test function OH_ArkUI_AxisEvent_GetAxisAction.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, AxisEventGetActionTest002, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(uiInputEvent, nullptr);
    auto event = std::make_unique<ArkUIAxisEvent>();
    EXPECT_NE(event, nullptr);

    event->action = AXIS_UPDATE;
    uiInputEvent->inputEvent = static_cast<void*>(event.get());
    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;

    auto action = OH_ArkUI_AxisEvent_GetAxisAction(uiInputEvent.get());
    EXPECT_EQ(action, UI_AXIS_EVENT_ACTION_UPDATE);
}

/**
 * @tc.name: AxisEventGetActionTest003
 * @tc.desc: Test function OH_ArkUI_AxisEvent_GetAxisActionfunction.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, AxisEventGetActionTest003, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(uiInputEvent, nullptr);
    auto event = std::make_unique<ArkUIAxisEvent>();
    EXPECT_NE(event, nullptr);

    event->action = AXIS_UPDATE;
    uiInputEvent->inputEvent = static_cast<void*>(event.get());
    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;

    auto action = OH_ArkUI_AxisEvent_GetAxisAction(uiInputEvent.get());
    EXPECT_EQ(action, UI_AXIS_EVENT_ACTION_NONE);

    action = OH_ArkUI_AxisEvent_GetAxisAction(nullptr);
    EXPECT_EQ(action, UI_AXIS_EVENT_ACTION_NONE);
}

/**
 * @tc.name: AxisEventGetActionTest004
 * @tc.desc: Test function OH_ArkUI_AxisEvent_GetAxisAction.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, AxisEventGetActionTest004, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(uiInputEvent, nullptr);

    uiInputEvent->inputEvent = nullptr;
    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    auto action = OH_ArkUI_AxisEvent_GetAxisAction(uiInputEvent.get());
    EXPECT_EQ(action, UI_AXIS_EVENT_ACTION_NONE);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    action = OH_ArkUI_AxisEvent_GetAxisAction(uiInputEvent.get());
    EXPECT_EQ(action, UI_AXIS_EVENT_ACTION_NONE);
}

/**
 * @tc.name: CapiInputTest001
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, CapiInputTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = ArkUIEventCategory::CLICK_EVENT;
    event.clickEvent.subKind = ArkUIEventSubKind::ON_CLICK_EVENT;
    event.clickEvent.localX = ARKUI_X;
    event.clickEvent.localY = ARKUI_Y;
    event.clickEvent.timestamp = ARKUI_TIME;
    event.clickEvent.sourceType = ARKUI_SOURCETYPE;
    event.clickEvent.windowX = ARKUI_X;
    event.clickEvent.windowY = ARKUI_Y;
    event.clickEvent.displayX = ARKUI_X;
    event.clickEvent.displayY = ARKUI_Y;
    event.clickEvent.targetPositionX = ARKUI_X;
    event.clickEvent.targetPositionY = ARKUI_Y;
    event.clickEvent.targetGlobalPositionX = ARKUI_X;
    event.clickEvent.targetGlobalPositionY = ARKUI_Y;
    uiInputEvent.inputEvent = &event.clickEvent;
    uiInputEvent.eventTypeId = C_CLICK_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetX(inputEvent), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetY(inputEvent), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTime(inputEvent), ARKUI_TIME);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetSourceType(inputEvent), ARKUI_SOURCETYPE);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetWindowX(inputEvent), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetWindowY(inputEvent), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetDisplayX(inputEvent), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetDisplayY(inputEvent), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetPositionX(inputEvent), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetPositionY(inputEvent), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(inputEvent), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(inputEvent), ARKUI_Y);
}

/**
 * @tc.name: CapiInputTest002
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, CapiInputTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = ArkUIEventCategory::CLICK_EVENT;
    event.clickEvent.subKind = ArkUIEventSubKind::ON_CLICK_EVENT;
    event.clickEvent.width = ARKUI_WIDTH;
    event.clickEvent.height = ARKUI_HEIGHT;
    event.clickEvent.tiltX = ARKUI_TILTX;
    event.clickEvent.tiltY = ARKUI_TILTY;
    event.clickEvent.pressure = ARKUI_PRESSURE;
    event.clickEvent.toolType = ARKUI_TOOLTYPE;
    event.clickEvent.deviceId = ARKUI_DEVICE_ID;
    event.clickEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    event.clickEvent.clickPointSize = ARKUI_POINTERCOUNTER;
    uiInputEvent.inputEvent = &event.clickEvent;
    uiInputEvent.eventTypeId = C_CLICK_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetWidth(inputEvent), ARKUI_WIDTH);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetHeight(inputEvent), ARKUI_HEIGHT);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetTiltX(inputEvent, 0), ARKUI_TILTX);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetTiltY(inputEvent, 0), ARKUI_TILTY);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetPressure(inputEvent, 0), ARKUI_PRESSURE);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetToolType(inputEvent), NodeModel::ConvertToCInputEventToolType(ARKUI_TOOLTYPE));
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetDeviceId(inputEvent), ARKUI_DEVICE_ID);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetModifierKeyStates(inputEvent, 0), 401);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetPointerCount(inputEvent), ARKUI_POINTERCOUNTER);
}

/**
 * @tc.name: CapiInputTest003
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, CapiInputTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = ArkUIEventCategory::HOVER_EVENT;
    event.hoverEvent.subKind = ON_HOVER_EVENT;
    event.hoverEvent.isHover = true;
    // width height x y globalx globaly
    event.hoverEvent.targetPositionX = ARKUI_X;
    event.hoverEvent.targetPositionY = ARKUI_Y;
    event.hoverEvent.targetGlobalPositionX = ARKUI_X;
    event.hoverEvent.targetGlobalPositionY = ARKUI_Y;
    event.hoverEvent.width = ARKUI_WIDTH;
    event.hoverEvent.height = ARKUI_HEIGHT;
    // deviceid
    event.hoverEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.hoverEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    // timestamp
    event.hoverEvent.timeStamp = ARKUI_TIME;
    // sourcetool
    event.hoverEvent.toolType = ARKUI_TOOLTYPE;
    // source
    event.hoverEvent.sourceType = ARKUI_SOURCETYPE;
    // tiltX tiltY
    event.hoverEvent.tiltX = ARKUI_TILTX;
    event.hoverEvent.tiltY = ARKUI_TILTY;
    // stoppropagation
    event.hoverEvent.stopPropagation = false;
    uiInputEvent.inputEvent = &event.hoverEvent;
    uiInputEvent.eventTypeId = C_HOVER_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTime(inputEvent), ARKUI_TIME);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetSourceType(inputEvent), ARKUI_SOURCETYPE);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetPositionX(inputEvent), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetPositionY(inputEvent), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(inputEvent), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(inputEvent), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetWidth(inputEvent), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetHeight(inputEvent), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetTiltX(inputEvent, 0), ARKUI_TILTX);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetTiltY(inputEvent, 0), ARKUI_TILTY);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetToolType(inputEvent), NodeModel::ConvertToCInputEventToolType(ARKUI_TOOLTYPE));
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetDeviceId(inputEvent), ARKUI_DEVICE_ID);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetModifierKeyStates(inputEvent, 0), 401);
    EXPECT_TRUE(OH_ArkUI_HoverEvent_IsHovered(inputEvent));
    const auto* hoverEvent = reinterpret_cast<ArkUIHoverEvent*>(inputEvent->inputEvent);
    EXPECT_FALSE(hoverEvent->stopPropagation);
    OH_ArkUI_PointerEvent_SetStopPropagation(inputEvent, true);
    EXPECT_TRUE(hoverEvent->stopPropagation);
}

/**
 * @tc.name: CapiInputTest004
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, CapiInputTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    // width height x y globalx globaly
    event.touchEvent.targetPositionX = ARKUI_X;
    event.touchEvent.targetPositionY = ARKUI_Y;
    event.touchEvent.targetGlobalPositionX = ARKUI_X;
    event.touchEvent.targetGlobalPositionY = ARKUI_Y;
    event.touchEvent.width = ARKUI_WIDTH;
    event.touchEvent.height = ARKUI_HEIGHT;
    // deviceid
    event.touchEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.touchEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetPositionX(inputEvent), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetPositionY(inputEvent), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(inputEvent), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(inputEvent), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetWidth(inputEvent), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetHeight(inputEvent), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetDeviceId(inputEvent), ARKUI_DEVICE_ID);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetModifierKeyStates(inputEvent, 0), 401);
}

/**
 * @tc.name: CapiInputTest005
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, CapiInputTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = MOUSE_INPUT_EVENT;
    event.mouseEvent.subKind = ON_MOUSE;
    // width height x y globalx globaly
    event.mouseEvent.targetPositionX = ARKUI_X;
    event.mouseEvent.targetPositionY = ARKUI_Y;
    event.mouseEvent.targetGlobalPositionX = ARKUI_X;
    event.mouseEvent.targetGlobalPositionY = ARKUI_Y;
    event.mouseEvent.width = ARKUI_WIDTH;
    event.mouseEvent.height = ARKUI_HEIGHT;
    // deviceid
    event.mouseEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.mouseEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    // pressure
    event.mouseEvent.actionTouchPoint.pressure = ARKUI_PRESSURE;
    // toolType
    event.mouseEvent.actionTouchPoint.toolType = ARKUI_TOOLTYPE;
    // source
    event.mouseEvent.sourceType = ARKUI_SOURCETYPE;
    // stoppropagation
    event.mouseEvent.stopPropagation = false;
    uiInputEvent.inputEvent = &event.mouseEvent;
    uiInputEvent.eventTypeId = C_MOUSE_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetPositionX(inputEvent), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetPositionY(inputEvent), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(inputEvent), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(inputEvent), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetWidth(inputEvent), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetHeight(inputEvent), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetDeviceId(inputEvent), ARKUI_DEVICE_ID);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetModifierKeyStates(inputEvent, 0), 401);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetPressure(inputEvent, 0), ARKUI_PRESSURE);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetSourceType(inputEvent), ARKUI_SOURCETYPE);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetToolType(inputEvent), NodeModel::ConvertToCInputEventToolType(ARKUI_TOOLTYPE));
    const auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(inputEvent->inputEvent);
    EXPECT_FALSE(mouseEvent->stopPropagation);
    OH_ArkUI_PointerEvent_SetStopPropagation(inputEvent, true);
    EXPECT_TRUE(mouseEvent->stopPropagation);
}

/**
 * @tc.name: CapiInputTest006
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, CapiInputTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = ArkUIEventCategory::FOCUS_AXIS_EVENT;
    event.focusAxisEvent.subKind = ArkUIEventCategory::FOCUS_AXIS_EVENT;
    // width height x y globalx globaly
    event.focusAxisEvent.targetPositionX = ARKUI_X;
    event.focusAxisEvent.targetPositionY = ARKUI_Y;
    event.focusAxisEvent.targetGlobalPositionX = ARKUI_X;
    event.focusAxisEvent.targetGlobalPositionY = ARKUI_Y;
    event.focusAxisEvent.width = ARKUI_WIDTH;
    event.focusAxisEvent.height = ARKUI_HEIGHT;
    // deviceid
    event.focusAxisEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.focusAxisEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    uiInputEvent.inputEvent = &event.focusAxisEvent;
    uiInputEvent.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetPositionX(inputEvent), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetPositionY(inputEvent), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(inputEvent), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(inputEvent), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetWidth(inputEvent), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetEventTargetHeight(inputEvent), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetDeviceId(inputEvent), ARKUI_DEVICE_ID);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetModifierKeyStates(inputEvent, 0), 401);
}

/**
 * @tc.name: CapiInputTest007
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, CapiInputTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = ArkUIEventCategory::KEY_INPUT_EVENT;
    event.keyEvent.subKind = ArkUIEventSubKind::ON_KEY_EVENT;
    // deviceid
    event.keyEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.keyEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    uiInputEvent.inputEvent = &event.mouseEvent;
    uiInputEvent.eventTypeId = C_KEY_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetDeviceId(inputEvent), ARKUI_DEVICE_ID);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetModifierKeyStates(inputEvent, 0), 401);
}

/**
 * @tc.name: CapiInputTest008
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, CapiInputTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    // width height x y globalx globaly
    event.touchEvent.targetPositionX = ARKUI_X;
    event.touchEvent.targetPositionY = ARKUI_Y;
    event.touchEvent.targetGlobalPositionX = ARKUI_X;
    event.touchEvent.targetGlobalPositionY = ARKUI_Y;
    event.touchEvent.width = ARKUI_WIDTH;
    event.touchEvent.height = ARKUI_HEIGHT;
    // deviceid
    event.touchEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.touchEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    event.touchEvent.subKind = ON_HOVER_MOVE;
    event.touchEvent.actionTouchPoint.id = 1;
    event.touchEvent.actionTouchPoint.nodeX = ARKUI_X;
    event.touchEvent.actionTouchPoint.nodeY = ARKUI_Y;
    event.touchEvent.actionTouchPoint.windowX = ARKUI_X;
    event.touchEvent.actionTouchPoint.windowY = ARKUI_Y;
    event.touchEvent.actionTouchPoint.screenX = ARKUI_X;
    event.touchEvent.actionTouchPoint.screenY = ARKUI_Y;
    event.touchEvent.actionTouchPoint.globalDisplayX = ARKUI_X;
    event.touchEvent.actionTouchPoint.globalDisplayY = ARKUI_Y;

    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetXByIndex(inputEvent, 0), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetYByIndex(inputEvent, 0), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetWindowXByIndex(inputEvent, 0), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetWindowYByIndex(inputEvent, 0), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetDisplayXByIndex(inputEvent, 0), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetDisplayYByIndex(inputEvent, 0), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex(inputEvent, 0), ARKUI_X);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex(inputEvent, 0), ARKUI_Y);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetPointerId(inputEvent, 0), 1);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetPointerCount(inputEvent), 1);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetPressure(inputEvent, 0), 0);

    EXPECT_EQ(OH_ArkUI_PointerEvent_GetXByIndex(inputEvent, 1), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetYByIndex(inputEvent, 1), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetWindowXByIndex(inputEvent, 1), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetWindowYByIndex(inputEvent, 1), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetDisplayXByIndex(inputEvent, 1), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetDisplayYByIndex(inputEvent, 1), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex(inputEvent, 1), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex(inputEvent, 1), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetPointerId(inputEvent, 1), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetPressure(inputEvent, 1), 0);
}

/**
 * @tc.name: CapiInputTest009
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, CapiInputTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    event.touchEvent.subKind = ON_HOVER_EVENT;

    uiInputEvent.inputEvent = nullptr;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetXByIndex(inputEvent, 0), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetYByIndex(inputEvent, 0), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetWindowXByIndex(inputEvent, 0), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetWindowYByIndex(inputEvent, 0), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetDisplayXByIndex(inputEvent, 0), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetDisplayYByIndex(inputEvent, 0), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex(inputEvent, 0), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex(inputEvent, 0), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetPointerId(inputEvent, 0), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetPointerCount(inputEvent), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetPressure(inputEvent, 0), 0);
}

/**
 * @tc.name: CapiInputTest010
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, CapiInputTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    event.touchEvent.subKind = ON_HOVER_EVENT;

    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetXByIndex(inputEvent, 0), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetYByIndex(inputEvent, 0), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetWindowXByIndex(inputEvent, 0), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetWindowYByIndex(inputEvent, 0), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetDisplayXByIndex(inputEvent, 0), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetDisplayYByIndex(inputEvent, 0), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex(inputEvent, 0), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex(inputEvent, 0), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetPointerId(inputEvent, 0), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetPointerCount(inputEvent), 0);
    EXPECT_EQ(OH_ArkUI_PointerEvent_GetPressure(inputEvent, 0), 0);
}

/**
 * @tc.name: PointerEventGetInteractionHandTest001
 * @tc.desc: Test function OH_ArkUI_PointerEvent_GetInteractionHand.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetInteractionHandTest001, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(uiInputEvent, nullptr);

    uiInputEvent->inputEvent = nullptr;
    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;

    ArkUI_InteractionHand *hand = nullptr;
    auto result = OH_ArkUI_PointerEvent_GetInteractionHand(uiInputEvent.get(), hand);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: PointerEventGetInteractionHandTest002
 * @tc.desc: Test function OH_ArkUI_PointerEvent_GetInteractionHand.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetInteractionHandTest002, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(uiInputEvent, nullptr);

    uiInputEvent->inputEvent = nullptr;
    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    ArkUI_InteractionHand hand = ARKUI_EVENT_HAND_NONE;
    auto result = OH_ArkUI_PointerEvent_GetInteractionHand(uiInputEvent.get(), &hand);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(hand, ARKUI_EVENT_HAND_NONE);
}

/**
 * @tc.name: PointerEventGetInteractionHandTest003
 * @tc.desc: Test function OH_ArkUI_PointerEvent_GetInteractionHand.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetInteractionHandTest003, TestSize.Level1)
{
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.touchEvent.actionTouchPoint.operatingHand = ARKUI_EVENT_HAND_LEFT;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUI_InteractionHand hand = ARKUI_EVENT_HAND_NONE;
    auto result = OH_ArkUI_PointerEvent_GetInteractionHand(&uiInputEvent, &hand);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(hand, ARKUI_EVENT_HAND_LEFT);
}

/**
 * @tc.name: PointerEventGetInteractionHandTest004
 * @tc.desc: Test function OH_ArkUI_PointerEvent_GetInteractionHand.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetInteractionHandTest004, TestSize.Level1)
{
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.touchEvent.actionTouchPoint.operatingHand = ARKUI_EVENT_HAND_RIGHT;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUI_InteractionHand hand = ARKUI_EVENT_HAND_NONE;
    auto result = OH_ArkUI_PointerEvent_GetInteractionHand(&uiInputEvent, &hand);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(hand, ARKUI_EVENT_HAND_RIGHT);
}

/**
 * @tc.name: PointerEventGetInteractionHandByIndexTest001
 * @tc.desc: Test function OH_ArkUI_PointerEvent_GetInteractionHandByIndex.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetInteractionHandByIndexTest001, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(uiInputEvent, nullptr);

    uiInputEvent->inputEvent = nullptr;
    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    ArkUI_InteractionHand *hand = nullptr;
    auto result = OH_ArkUI_PointerEvent_GetInteractionHandByIndex(uiInputEvent.get(), 0, hand);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: PointerEventGetInteractionHandByIndexTest002
 * @tc.desc: Test function OH_ArkUI_PointerEvent_GetInteractionHandByIndex.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetInteractionHandByIndexTest002, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(uiInputEvent, nullptr);

    uiInputEvent->inputEvent = nullptr;
    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    ArkUI_InteractionHand hand = ARKUI_EVENT_HAND_NONE;
    auto result = OH_ArkUI_PointerEvent_GetInteractionHandByIndex(uiInputEvent.get(), 0, &hand);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(hand, ARKUI_EVENT_HAND_NONE);
}

/**
 * @tc.name: PointerEventGetInteractionHandByIndexTest003
 * @tc.desc: Test function OH_ArkUI_PointerEvent_GetInteractionHandByIndex.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetInteractionHandByIndexTest003, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(uiInputEvent, nullptr);

    uiInputEvent->inputEvent = nullptr;
    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    ArkUI_InteractionHand hand = ARKUI_EVENT_HAND_NONE;
    auto result = OH_ArkUI_PointerEvent_GetInteractionHandByIndex(uiInputEvent.get(), 0, &hand);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(hand, ARKUI_EVENT_HAND_NONE);
}

/**
 * @tc.name: PointerEventGetInteractionHandByIndexTest004
 * @tc.desc: Test function OH_ArkUI_PointerEvent_GetInteractionHandByIndex.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetInteractionHandByIndexTest004, TestSize.Level1)
{
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    ArkUITouchPoint points[2]; // 2 points
    points[0].operatingHand = ARKUI_EVENT_HAND_LEFT;
    points[1].operatingHand = ARKUI_EVENT_HAND_RIGHT;
    event.touchEvent.touchPointes = points;
    event.touchEvent.touchPointSize = 2;  // 2 points
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUI_InteractionHand hand = ARKUI_EVENT_HAND_NONE;
    int32_t result = OH_ArkUI_PointerEvent_GetInteractionHandByIndex(&uiInputEvent, 0, &hand);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(hand, ARKUI_EVENT_HAND_LEFT);

    hand = ARKUI_EVENT_HAND_NONE;
    result = OH_ArkUI_PointerEvent_GetInteractionHandByIndex(&uiInputEvent, 1, &hand);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(hand, ARKUI_EVENT_HAND_RIGHT);

    hand = ARKUI_EVENT_HAND_NONE;
    // 2 is out of range
    result = OH_ArkUI_PointerEvent_GetInteractionHandByIndex(&uiInputEvent, 2, &hand);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(hand, ARKUI_EVENT_HAND_NONE);
}

/**
 * @tc.name: AxisEventScrollStepTest001
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetScrollStep function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, AxisEventScrollStepTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = ArkUIEventCategory::AXIS_EVENT;
    event.axisEvent.subKind = ArkUIEventSubKind::ON_AXIS;
    event.axisEvent.timeStamp = ARKUI_TIME;
    event.axisEvent.scrollStep = 3;
    uiInputEvent.inputEvent = &event.axisEvent;
    uiInputEvent.eventTypeId = C_AXIS_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    /**
     * @tc.steps: step2. call functions.
     */
    auto scroll_step = OH_ArkUI_AxisEvent_GetScrollStep(inputEvent);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(scroll_step, 3);
}

/**
 * @tc.name: AxisEventToolTypeTest001
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetScrollStep function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, AxisEventToolTypeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = ArkUIEventCategory::AXIS_EVENT;
    event.axisEvent.subKind = ArkUIEventSubKind::ON_AXIS;
    event.axisEvent.timeStamp = ARKUI_TIME;
    event.axisEvent.actionTouchPoint.toolType = ARKUI_TOOLTYPE;
    uiInputEvent.inputEvent = &event.axisEvent;
    uiInputEvent.eventTypeId = C_AXIS_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);
    /**
     * @tc.steps: step2. call functions.
     */
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetToolType(inputEvent), NodeModel::ConvertToCInputEventToolType(ARKUI_TOOLTYPE));
}

/*
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaY001
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, MouseEventGetRawDeltaY001, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(uiInputEvent, nullptr);
    auto event = std::make_unique<ArkUIMouseEvent>();
    EXPECT_NE(event, nullptr);

    event->rawDeltaY = 5.0;
    uiInputEvent->inputEvent = event.get();
    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;

    auto action = OH_ArkUI_MouseEvent_GetRawDeltaY(uiInputEvent.get());
    EXPECT_EQ(action, 5.0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaY002
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, MouseEventGetRawDeltaY002, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(uiInputEvent, nullptr);
    auto event = std::make_unique<ArkUIMouseEvent>();
    EXPECT_NE(event, nullptr);

    event->rawDeltaY = 5.0;
    uiInputEvent->inputEvent = static_cast<void*>(event.get());
    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;

    auto action = OH_ArkUI_MouseEvent_GetRawDeltaY(uiInputEvent.get());
    EXPECT_EQ(action, 0.0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaY003
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaY003, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_TOUCH_EVENT_ID;
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(event.get());
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaY004
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaY004, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = TOUCH_EVENT_ID;
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(event.get());
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaY005
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaY005, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_MOUSE_EVENT_ID;
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(event.get());
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaY006
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaY006, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_AXIS_EVENT_ID;
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(event.get());
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaY007
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaY007, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(event.get());
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaY008
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaY008, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_HOVER_EVENT_ID;
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(event.get());
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaY009
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaY009, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_CLICK_EVENT_ID;
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(event.get());
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetPressedButtons001
 * @tc.desc: test OH_ArkUI_MouseEvent_GetPressedButtons
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, MouseEventGetPressedButtons001, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(uiInputEvent, nullptr);
    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    auto event = std::make_unique<ArkUIMouseEvent>();
    event->pressedButtonsLength = 0;
    EXPECT_NE(event, nullptr);
    uiInputEvent->inputEvent = static_cast<void*>(event.get());
    int32_t pressedButtons[] = {5, 5, 5};
    int32_t length = 1;

    auto result = OH_ArkUI_MouseEvent_GetPressedButtons(uiInputEvent.get(), pressedButtons, &length);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetPressedButtons002
 * @tc.desc: test OH_ArkUI_MouseEvent_GetPressedButtons
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, MouseEventGetPressedButtons002, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(uiInputEvent, nullptr);
    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    auto event = std::make_unique<ArkUIMouseEvent>();
    event->pressedButtonsLength = 6;
    EXPECT_NE(event, nullptr);
    uiInputEvent->inputEvent = static_cast<void*>(event.get());
    int32_t pressedButtons[] = {5, 5, 5};
    int32_t length = 1;

    auto result = OH_ArkUI_MouseEvent_GetPressedButtons(uiInputEvent.get(), pressedButtons, &length);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetPressedButtons003
 * @tc.desc: test OH_ArkUI_MouseEvent_GetPressedButtons
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, MouseEventGetPressedButtons003, TestSize.Level1)
{
    int32_t length = 1;
    auto result = OH_ArkUI_MouseEvent_GetPressedButtons(nullptr, nullptr, &length);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetPressedButtons004
 * @tc.desc: test OH_ArkUI_MouseEvent_GetPressedButtons
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, MouseEventGetPressedButtons004, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(uiInputEvent, nullptr);
    uiInputEvent->inputEvent = nullptr;
    int32_t pressedButtons[] = {5, 5, 5};
    int32_t length = 1;

    auto result = OH_ArkUI_MouseEvent_GetPressedButtons(uiInputEvent.get(), pressedButtons, &length);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId001
 * @tc.desc: test OH_ArkUI_UIInputEvent_GetTargetDisplayId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId001, TestSize.Level1)
{
    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(nullptr);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId002
 * @tc.desc: test OH_ArkUI_UIInputEvent_GetTargetDisplayId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId002, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_MOUSE_EVENT_ID;
    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    mouseEvent->targetDisplayId = 1;
    event->inputEvent = mouseEvent.get();
    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(event.get());
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId003
 * @tc.desc: test OH_ArkUI_UIInputEvent_GetTargetDisplayId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId003, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    touchEvent->targetDisplayId = 2;
    event->inputEvent = touchEvent.get();
    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(event.get());
    EXPECT_EQ(result, 2);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId004
 * @tc.desc: test OH_ArkUI_UIInputEvent_GetTargetDisplayId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId004, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_AXIS_EVENT_ID;
    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    axisEvent->targetDisplayId = 3;
    event->inputEvent = axisEvent.get();
    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(event.get());
    EXPECT_EQ(result, 3);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId005
 * @tc.desc: test OH_ArkUI_UIInputEvent_GetTargetDisplayId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId005, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    auto focusAxisEvent = std::make_unique<ArkUIFocusAxisEvent>();
    focusAxisEvent->targetDisplayId = 4;
    event->inputEvent = focusAxisEvent.get();
    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(event.get());
    EXPECT_EQ(result, 4);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId006
 * @tc.desc: test OH_ArkUI_UIInputEvent_GetTargetDisplayId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId006, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = AXIS_EVENT_ID;
    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(event.get());
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId007
 * @tc.desc: test OH_ArkUI_UIInputEvent_GetTargetDisplayId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId007, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_AXIS_EVENT_ID;
    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    axisEvent->targetDisplayId = 0;
    event->inputEvent = axisEvent.get();
    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(event.get());
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaX001
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaX001, TestSize.Level1)
{
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(nullptr);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaX002
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaX002, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_MOUSE_EVENT_ID;
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(event.get());
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaX003
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaX003, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_MOUSE_EVENT_ID;
    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    mouseEvent->rawDeltaX = 1;
    event->inputEvent = mouseEvent.get();
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(event.get());
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaX004
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaX004, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = AXIS_EVENT_ID;
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(event.get());
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaX005
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaX005, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_TOUCH_EVENT_ID;
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(event.get());
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaX006
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaX006, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = TOUCH_EVENT_ID;
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(event.get());
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaX007
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaX007, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = AXIS_EVENT_ID;
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(event.get());
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaX008
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaX008, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_CLICK_EVENT_ID;
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(event.get());
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaX009
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaX009, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_HOVER_EVENT_ID;
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(event.get());
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaX0010
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaX0010, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(event.get());
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPressedTimeByIndex001
 * @tc.desc: test OH_ArkUI_PointerEvent_GetPressedTimeByIndex
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPressedTimeByIndex001, TestSize.Level1)
{
    auto result = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(nullptr, 0);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPressedTimeByIndex002
 * @tc.desc: test OH_ArkUI_PointerEvent_GetPressedTimeByIndex
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPressedTimeByIndex002, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_TOUCH_EVENT_ID;
    auto result = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(event.get(), -1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPressedTimeByIndex003
 * @tc.desc: test OH_ArkUI_PointerEvent_GetPressedTimeByIndex
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPressedTimeByIndex003, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_TOUCH_EVENT_ID;
    auto result = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(event.get(), 0);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPressedTimeByIndex004
 * @tc.desc: test OH_ArkUI_PointerEvent_GetPressedTimeByIndex
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPressedTimeByIndex004, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    auto result = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(event.get(), -2);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPressedTimeByIndex005
 * @tc.desc: test OH_ArkUI_PointerEvent_GetPressedTimeByIndex
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPressedTimeByIndex005, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUITouchPoint touchPoint;
    touchPoint.pressedTime = 20;
    touchEvent->touchPointes = &touchPoint;
    touchEvent->touchPointSize = 2;
    event->inputEvent = touchEvent.get();
    auto result = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(event.get(), 0);
    EXPECT_EQ(result, 20);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPressedTimeByIndex006
 * @tc.desc: test OH_ArkUI_PointerEvent_GetPressedTimeByIndex
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPressedTimeByIndex006, TestSize.Level1)
{
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    event->eventTypeId = AXIS_EVENT_ID;
    auto result = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(event.get(), 0);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetTouchAreaWidth
 * @tc.desc: test OH_ArkUI_PointerEvent_GetTouchAreaWidth
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetTouchAreaWidth, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetTouchAreaWidth(nullptr, 0);
    EXPECT_EQ(result, 0);
    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetTouchAreaWidth(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetTouchAreaWidth(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 0);

    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    touchEvent->touchPointSize = 0;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetTouchAreaWidth(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 0);

    touchEvent->touchPointSize = 2;
    ArkUITouchPoint touchPointes[2];
    touchPointes[1].contactAreaWidth = 1.0;
    touchEvent->touchPointes = touchPointes;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetTouchAreaWidth(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetTouchAreaHeight
 * @tc.desc: test OH_ArkUI_PointerEvent_GetTouchAreaHeight
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetTouchAreaHeight, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetTouchAreaHeight(nullptr, 0);
    EXPECT_EQ(result, 0);
    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetTouchAreaHeight(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetTouchAreaHeight(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 0);

    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    touchEvent->touchPointSize = 0;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetTouchAreaHeight(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 0);

    touchEvent->touchPointSize = 2;
    ArkUITouchPoint touchPointes[2];
    touchPointes[1].contactAreaHeight = 1.0;
    touchEvent->touchPointes = touchPointes;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetTouchAreaHeight(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetChangedPointerId
 * @tc.desc: test OH_ArkUI_PointerEvent_GetChangedPointerId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetChangedPointerId, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetChangedPointerId(nullptr, 0);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetChangedPointerId(uiInputEvent.get(), 0);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetChangedPointerId(uiInputEvent.get(), 0);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    touchEvent->touchPointSize = 0;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetChangedPointerId(uiInputEvent.get(), 0);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistorySize
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistorySize
 * @tc.type: FUNC
 */

HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistorySize, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistorySize(nullptr);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistorySize(uiInputEvent.get());
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistorySize(uiInputEvent.get());
    EXPECT_EQ(result, 0);

    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    touchEvent->historyEvents = events;
    touchEvent->historySize = 1;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistorySize(uiInputEvent.get());
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryEventTime
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryEventTime
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryEventTime, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryEventTime(nullptr, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryEventTime(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    events[1].timeStamp = 1;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryEventTime(uiInputEvent.get(), 1);
    EXPECT_EQ(result, 1);

    result = OH_ArkUI_PointerEvent_GetHistoryEventTime(uiInputEvent.get(), -1);
    EXPECT_EQ(result, 0);

    result = OH_ArkUI_PointerEvent_GetHistoryEventTime(uiInputEvent.get(), 10);
    EXPECT_EQ(result, 0);

    touchEvent->historyEvents = nullptr;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryEventTime(uiInputEvent.get(), 1);
    EXPECT_EQ(result, 0);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryEventTime(uiInputEvent.get(), 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryPointerCount
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryPointerCount
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryPointerCount, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryPointerCount(nullptr, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryPointerCount(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    events[1].touchPointSize = 1;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryPointerCount(uiInputEvent.get(), 1);
    EXPECT_EQ(result, 1);

    result = OH_ArkUI_PointerEvent_GetHistoryPointerCount(uiInputEvent.get(), -1);
    EXPECT_EQ(result, 0);

    result = OH_ArkUI_PointerEvent_GetHistoryPointerCount(uiInputEvent.get(), 10);
    EXPECT_EQ(result, 0);

    touchEvent->historyEvents = nullptr;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryPointerCount(uiInputEvent.get(), 1);
    EXPECT_EQ(result, 0);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryPointerCount(uiInputEvent.get(), 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryPointerId
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryPointerId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryPointerId, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryPointerId(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryPointerId(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].id = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryPointerId(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryPointerId(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryX
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryX, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryX(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryX(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].nodeX = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryX(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryX(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryY
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryY, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryY(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryY(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].nodeY = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryY(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryY(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryWindowX
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryWindowX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryWindowX, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryWindowX(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryWindowX(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].windowX = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryWindowX(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryWindowX(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryWindowY
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryWindowY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryWindowY, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryWindowY(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryWindowY(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].windowY = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryWindowY(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryWindowY(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryDisplayX
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryDisplayX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryDisplayX, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryDisplayX(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryDisplayX(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].screenX = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryDisplayX(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryDisplayX(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryDisplayY
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryDisplayY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryDisplayY, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryDisplayY(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryDisplayY(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].screenY = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryDisplayY(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryDisplayY(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryPressure
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryPressure
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryPressure, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryPressure(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryPressure(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].pressure = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryPressure(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryPressure(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryTiltX
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryTiltX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryTiltX, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryTiltX(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryTiltX(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].tiltX = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryTiltX(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryTiltX(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryTiltY
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryTiltY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryTiltY, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryTiltY(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryTiltY(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].tiltY = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryTiltY(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryTiltY(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].contactAreaWidth = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].contactAreaHeight = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetVerticalAxisValue
 * @tc.desc: test OH_ArkUI_AxisEvent_GetVerticalAxisValue
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetVerticalAxisValue, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(nullptr);
    EXPECT_EQ(result, 0.0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 0.0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    auto axisEvent = std::make_unique<OHOS::Ace::AxisEvent>();
    axisEvent->verticalAxis = 1.1;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 0.0);

    uiInputEvent->inputEvent = axisEvent.get();
    result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 1.1);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 0.0);

    auto cAxisEvent = std::make_unique<ArkUIAxisEvent>();
    cAxisEvent->verticalAxis = 1.1;
    uiInputEvent->inputEvent = cAxisEvent.get();
    result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 1.1);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetHorizontalAxisValue
 * @tc.desc: test OH_ArkUI_AxisEvent_GetHorizontalAxisValue
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetHorizontalAxisValue, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(nullptr);
    EXPECT_EQ(result, 0.0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 0.0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    auto axisEvent = std::make_unique<OHOS::Ace::AxisEvent>();
    axisEvent->horizontalAxis = 1.1;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 0.0);

    uiInputEvent->inputEvent = axisEvent.get();
    result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 1.1);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 0.0);

    auto cAxisEvent = std::make_unique<ArkUIAxisEvent>();
    cAxisEvent->verticalAxis = 1.1;
    uiInputEvent->inputEvent = cAxisEvent.get();
    result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 1.1);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetPinchAxisScaleValue
 * @tc.desc: test OH_ArkUI_AxisEvent_GetPinchAxisScaleValue
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetPinchAxisScaleValue, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(nullptr);
    EXPECT_EQ(result, 0.0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    result = OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(uiInputEvent.get());
    EXPECT_EQ(result, 0.0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    auto axisEvent = std::make_unique<OHOS::Ace::AxisEvent>();
    axisEvent->pinchAxisScale = 1.1;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(uiInputEvent.get());
    EXPECT_EQ(result, 0.0);

    uiInputEvent->inputEvent = axisEvent.get();
    result = OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(uiInputEvent.get());
    EXPECT_EQ(result, 1.1);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(uiInputEvent.get());
    EXPECT_EQ(result, 0.0);

    auto cAxisEvent = std::make_unique<ArkUIAxisEvent>();
    cAxisEvent->pinchAxisScale = 1.1;
    uiInputEvent->inputEvent = cAxisEvent.get();
    result = OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(uiInputEvent.get());
    EXPECT_EQ(result, 1.1);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetInterceptHitTestMode
 * @tc.desc: test OH_ArkUI_PointerEvent_SetInterceptHitTestMode
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetInterceptHitTestMode, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto mode = HTM_TRANSPARENT;
    auto result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(nullptr, mode);
    int32_t ERROR_CODE_PARAM_INVALID = 401;
    int32_t ERROR_CODE_NO_ERROR = 0;
    EXPECT_EQ(result, ERROR_CODE_PARAM_INVALID);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    touchEvent->interceptResult = 0;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(uiInputEvent.get(), mode);
    EXPECT_EQ(touchEvent->interceptResult, static_cast<int32_t>(HTM_TRANSPARENT));
    EXPECT_EQ(result, ERROR_CODE_NO_ERROR);

    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    mouseEvent->interceptResult = 0;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(uiInputEvent.get(), mode);
    EXPECT_EQ(result, ERROR_CODE_PARAM_INVALID);

    uiInputEvent->inputEvent = mouseEvent.get();
    result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(uiInputEvent.get(), mode);
    EXPECT_EQ(touchEvent->interceptResult, static_cast<int32_t>(HTM_TRANSPARENT));

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(uiInputEvent.get(), mode);
    EXPECT_EQ(result, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetStopPropagation
 * @tc.desc: test OH_ArkUI_PointerEvent_SetStopPropagation
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetStopPropagation, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto stopPropagation = true;
    auto result = OH_ArkUI_PointerEvent_SetStopPropagation(nullptr, true);
    int32_t ERROR_CODE_PARAM_INVALID = 401;
    EXPECT_EQ(result, ERROR_CODE_PARAM_INVALID);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    touchEvent->stopPropagation = false;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_SetStopPropagation(uiInputEvent.get(), stopPropagation);
    EXPECT_EQ(touchEvent->stopPropagation, stopPropagation);

    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    mouseEvent->stopPropagation = false;
    uiInputEvent->inputEvent = mouseEvent.get();
    result = OH_ArkUI_PointerEvent_SetStopPropagation(uiInputEvent.get(), stopPropagation);
    EXPECT_EQ(mouseEvent->stopPropagation, stopPropagation);

    uiInputEvent->eventTypeId = C_HOVER_EVENT_ID;
    auto hoverEvent = std::make_unique<ArkUIHoverEvent>();
    hoverEvent->stopPropagation = false;
    uiInputEvent->inputEvent = hoverEvent.get();
    result = OH_ArkUI_PointerEvent_SetStopPropagation(uiInputEvent.get(), stopPropagation);
    EXPECT_EQ(hoverEvent->stopPropagation, stopPropagation);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_SetStopPropagation(uiInputEvent.get(), stopPropagation);
    EXPECT_EQ(result, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetMouseButton
 * @tc.desc: test OH_ArkUI_MouseEvent_GetMouseButton
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetMouseButton, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_MouseEvent_GetMouseButton(nullptr);
    EXPECT_EQ(result, -1);

    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetMouseButton(uiInputEvent.get());
    EXPECT_EQ(result, -1);

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    mouseEvent->button = 2;
    uiInputEvent->inputEvent = mouseEvent.get();
    result = OH_ArkUI_MouseEvent_GetMouseButton(uiInputEvent.get());
    EXPECT_EQ(result, 2);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetMouseButton(uiInputEvent.get());
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetMouseAction
 * @tc.desc: test OH_ArkUI_MouseEvent_GetMouseAction
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetMouseAction, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_MouseEvent_GetMouseAction(nullptr);
    EXPECT_EQ(result, -1);

    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetMouseAction(uiInputEvent.get());
    EXPECT_EQ(result, -1);

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    mouseEvent->action = 2;
    uiInputEvent->inputEvent = mouseEvent.get();
    result = OH_ArkUI_MouseEvent_GetMouseAction(uiInputEvent.get());
    EXPECT_EQ(result, 2);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetMouseAction(uiInputEvent.get());
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPressedTimeByIndex
 * @tc.desc: test OH_ArkUI_PointerEvent_GetPressedTimeByIndex
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPressedTimeByIndex, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(nullptr, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 0);

    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    touchEvent->touchPointSize = 2;
    ArkUITouchPoint touchPointes[2];
    touchPointes[1].pressedTime = 1;
    touchEvent->touchPointes = touchPointes;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(uiInputEvent.get(), 1);
    EXPECT_EQ(result, 1);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(uiInputEvent.get(), 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaX
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaX, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(nullptr);
    EXPECT_EQ(result, 0.0f);

    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetRawDeltaX(uiInputEvent.get());
    EXPECT_EQ(result, 0.0f);

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    mouseEvent->rawDeltaX = 2.0f;
    uiInputEvent->inputEvent = mouseEvent.get();
    result = OH_ArkUI_MouseEvent_GetRawDeltaX(uiInputEvent.get());
    EXPECT_EQ(result, 2.0f);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetRawDeltaX(uiInputEvent.get());
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaY
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaY, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaY(nullptr);
    EXPECT_EQ(result, 0.0f);

    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetRawDeltaY(uiInputEvent.get());
    EXPECT_EQ(result, 0.0f);

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    mouseEvent->rawDeltaY = 2.0f;
    uiInputEvent->inputEvent = mouseEvent.get();
    result = OH_ArkUI_MouseEvent_GetRawDeltaY(uiInputEvent.get());
    EXPECT_EQ(result, 2.0f);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetRawDeltaY(uiInputEvent.get());
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId
 * @tc.desc: test OH_ArkUI_UIInputEvent_GetTargetDisplayId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(nullptr);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    mouseEvent->targetDisplayId = 1;
    uiInputEvent->inputEvent = mouseEvent.get();
    result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(uiInputEvent.get());
    EXPECT_EQ(result, 1);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    touchEvent->targetDisplayId = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(uiInputEvent.get());
    EXPECT_EQ(result, 2);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    axisEvent->targetDisplayId = 3;
    uiInputEvent->inputEvent = axisEvent.get();
    result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(uiInputEvent.get());
    EXPECT_EQ(result, 3);

    uiInputEvent->eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    auto focusAxisEvent = std::make_unique<ArkUIFocusAxisEvent>();
    focusAxisEvent->targetDisplayId = 4;
    uiInputEvent->inputEvent = focusAxisEvent.get();
    result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(uiInputEvent.get());
    EXPECT_EQ(result, 4);

    uiInputEvent->eventTypeId = TOUCH_EVENT_ID;
    auto ohosTouchEvent = std::make_unique<OHOS::Ace::TouchEvent>();
    ohosTouchEvent->targetDisplayId = 5;
    uiInputEvent->inputEvent = ohosTouchEvent.get();
    result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(uiInputEvent.get());
    EXPECT_EQ(result, 5);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    auto ohosAxisEvent = std::make_unique<OHOS::Ace::AxisEvent>();
    ohosAxisEvent->targetDisplayId = 6;
    uiInputEvent->inputEvent = ohosAxisEvent.get();
    result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(uiInputEvent.get());
    EXPECT_EQ(result, 6);

    uiInputEvent->eventTypeId = C_HOVER_EVENT_ID;
    auto ohosHoverEvent = std::make_unique<ArkUIHoverEvent>();
    ohosHoverEvent->targetDisplayId = 7;
    uiInputEvent->inputEvent = ohosHoverEvent.get();
    result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(uiInputEvent.get());
    EXPECT_EQ(result, 7);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId008
 * @tc.desc: test OH_ArkUI_UIInputEvent_GetTargetDisplayId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId008, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    uiInputEvent->eventTypeId = C_CLICK_EVENT_ID;
    auto ohosClickEvent = std::make_unique<ArkUIClickEvent>();
    ohosClickEvent->targetDisplayId = 8;
    uiInputEvent->inputEvent = ohosClickEvent.get();
    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(uiInputEvent.get());
    EXPECT_EQ(result, 8);

    uiInputEvent->eventTypeId = C_KEY_EVENT_ID;
    result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(uiInputEvent.get());
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetPressedButtons
 * @tc.desc: test OH_ArkUI_MouseEvent_GetPressedButtons
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetPressedButtons, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    int32_t pressedButtons[1] = { 0 };
    int32_t length = 1;
    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    uiInputEvent->inputEvent = nullptr;
    auto result = OH_ArkUI_MouseEvent_GetPressedButtons(uiInputEvent.get(), pressedButtons, &length);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    mouseEvent->pressedButtonsLength = 2;
    uiInputEvent->inputEvent = mouseEvent.get();

    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetPressedButtons(uiInputEvent.get(), pressedButtons, &length);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH);

    mouseEvent->pressedButtonsLength = 1;
    ArkUI_Int32 mousePressedButtons[1] = { 3 };
    mouseEvent->pressedButtons = mousePressedButtons;
    uiInputEvent->inputEvent = mouseEvent.get();
    result = OH_ArkUI_MouseEvent_GetPressedButtons(uiInputEvent.get(), pressedButtons, &length);
    EXPECT_EQ(pressedButtons[0], 3);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetPressedButtons(uiInputEvent.get(), pressedButtons, &length);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    result = OH_ArkUI_MouseEvent_GetPressedButtons(uiInputEvent.get(), pressedButtons, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    result = OH_ArkUI_MouseEvent_GetPressedButtons(uiInputEvent.get(), nullptr, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    result = OH_ArkUI_MouseEvent_GetPressedButtons(nullptr, nullptr, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_FocusAxisEvent_GetAxisValue
 * @tc.desc: test OH_ArkUI_FocusAxisEvent_GetAxisValue
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_FocusAxisEvent_GetAxisValue, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    int32_t axis = 100;
    auto result = OH_ArkUI_FocusAxisEvent_GetAxisValue(nullptr, axis);
    EXPECT_EQ(result, 0.0);

    uiInputEvent->eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    result = OH_ArkUI_FocusAxisEvent_GetAxisValue(nullptr, axis);
    EXPECT_EQ(result, 0.0);

    auto focusAxisEvent = std::make_unique<ArkUIFocusAxisEvent>();
    uiInputEvent->inputEvent = focusAxisEvent.get();
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_FocusAxisEvent_SetStopPropagation
 * @tc.desc: Test function OH_ArkUI_FocusAxisEvent_SetStopPropagation.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_FocusAxisEvent_SetStopPropagation, TestSize.Level1)
{
    int32_t ret = OH_ArkUI_FocusAxisEvent_SetStopPropagation(nullptr, true);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ArkUI_UIInputEvent event;
    event.eventTypeId = C_TOUCH_EVENT_ID;
    ret = OH_ArkUI_FocusAxisEvent_SetStopPropagation(&event, true);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ArkUIFocusAxisEvent focusAxisEvent;
    focusAxisEvent.stopPropagation = false;
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    event.inputEvent = &focusAxisEvent;
    ret = OH_ArkUI_FocusAxisEvent_SetStopPropagation(&event, true);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_TRUE(focusAxisEvent.stopPropagation);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetWidth001
 * @tc.desc: Test function OH_ArkUI_UIInputEvent_GetEventTargetWidth.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetWidth001, TestSize.Level1)
{
    float width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(nullptr);
    EXPECT_EQ(width, 0.0f);
    ArkUI_UIInputEvent event;

    ArkUITouchEvent touchEvent;
    touchEvent.width = 10.0f;
    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 0.0f);
    event.inputEvent = &touchEvent;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 10.0f);

    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.width = 20.0f;
    event.eventTypeId = TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 0.0f);
    event.inputEvent = &aceTouchEvent;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 20.0f);

    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.width = 30.0f;
    event.eventTypeId = AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 0.0f);
    event.inputEvent = &aceAxisEvent;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 30.0f);

    ArkUIMouseEvent mouseEvent;
    mouseEvent.width = 40.0f;
    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 0.0f);
    event.inputEvent = &mouseEvent;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 40.0f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetWidth002
 * @tc.desc: Test function OH_ArkUI_UIInputEvent_GetEventTargetWidth.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetWidth002, TestSize.Level1)
{
    float width = 1.0f;
    ArkUI_UIInputEvent event;

    ArkUIAxisEvent axisEvent;
    axisEvent.width = 50.0f;
    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 0.0f);
    event.inputEvent = &axisEvent;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 50.0f);

    ArkUIFocusAxisEvent focusAxisEvent;
    focusAxisEvent.width = 60.0f;
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 0.0f);
    event.inputEvent = &focusAxisEvent;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 60.0f);

    ArkUIHoverEvent hoverEvent;
    hoverEvent.width = 70.0f;
    event.eventTypeId = C_HOVER_EVENT_ID;
    event.inputEvent = nullptr;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 0.0f);
    event.inputEvent = &hoverEvent;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 70.0f);

    ArkUIClickEvent clickEvent;
    clickEvent.width = 80.0f;
    event.eventTypeId = C_CLICK_EVENT_ID;
    event.inputEvent = nullptr;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 0.0f);
    event.inputEvent = &clickEvent;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 80.0f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetHeight001
 * @tc.desc: Test function OH_ArkUI_UIInputEvent_GetEventTargetHeight.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetHeight001, TestSize.Level1)
{
    float height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(nullptr);
    EXPECT_EQ(height, 0.0f);

    ArkUI_UIInputEvent event;

    ArkUITouchEvent touchEvent;
    touchEvent.height = 15.0f;
    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 0.0f);
    event.inputEvent = &touchEvent;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 15.0f);

    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.height = 25.0f;
    event.eventTypeId = TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 0.0f);
    event.inputEvent = &aceTouchEvent;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 25.0f);

    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.height = 35.0f;
    event.eventTypeId = AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 0.0f);
    event.inputEvent = &aceAxisEvent;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 35.0f);

    ArkUIMouseEvent mouseEvent;
    mouseEvent.height = 45.0f;
    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 0.0f);
    event.inputEvent = &mouseEvent;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 45.0f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetHeight002
 * @tc.desc: Test function OH_ArkUI_UIInputEvent_GetEventTargetHeight.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetHeight002, TestSize.Level1)
{
    float height = 1.0f;
    ArkUI_UIInputEvent event;
    ArkUIAxisEvent axisEvent;
    axisEvent.height = 55.0f;
    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 0.0f);
    event.inputEvent = &axisEvent;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 55.0f);

    ArkUIFocusAxisEvent focusAxisEvent;
    focusAxisEvent.height = 65.0f;
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 0.0f);
    event.inputEvent = &focusAxisEvent;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 65.0f);

    ArkUIHoverEvent hoverEvent;
    hoverEvent.height = 75.0f;
    event.eventTypeId = C_HOVER_EVENT_ID;
    event.inputEvent = nullptr;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 0.0f);
    event.inputEvent = &hoverEvent;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 75.0f);

    ArkUIClickEvent clickEvent;
    clickEvent.height = 85.0f;
    event.eventTypeId = C_CLICK_EVENT_ID;
    event.inputEvent = nullptr;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 0.0f);
    event.inputEvent = &clickEvent;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 85.0f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetPositionX001
 * @tc.desc: Test function OH_ArkUI_UIInputEvent_GetEventTargetPositionX.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetPositionX001, TestSize.Level1)
{
    float positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(nullptr);
    EXPECT_EQ(positionX, 0.0f);

    ArkUI_UIInputEvent event;

    ArkUITouchEvent touchEvent;
    touchEvent.targetPositionX = 100.5f;
    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &touchEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 100.5f);

    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.targetPositionX = 200.5f;
    event.eventTypeId = TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &aceTouchEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 200.5f);

    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.targetPositionX = 300.5f;
    event.eventTypeId = AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &aceAxisEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 300.5f);

    ArkUIMouseEvent mouseEvent;
    mouseEvent.targetPositionX = 400.5f;
    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &mouseEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 400.5f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetPositionX002
 * @tc.desc: Test function OH_ArkUI_UIInputEvent_GetEventTargetPositionX.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetPositionX002, TestSize.Level1)
{
    float positionX = 1.0f;
    ArkUI_UIInputEvent event;

    ArkUIAxisEvent axisEvent;
    axisEvent.targetPositionX = 500.5f;
    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &axisEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 500.5f);

    ArkUIFocusAxisEvent focusAxisEvent;
    focusAxisEvent.targetPositionX = 600.5f;
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &focusAxisEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 600.5f);

    ArkUIHoverEvent hoverEvent;
    hoverEvent.targetPositionX = 700.5f;
    event.eventTypeId = C_HOVER_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &hoverEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 700.5f);

    ArkUIClickEvent clickEvent;
    clickEvent.targetPositionX = 800.5f;
    event.eventTypeId = C_CLICK_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &clickEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 800.5f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetPositionY001
 * @tc.desc: Test function OH_ArkUI_UIInputEvent_GetEventTargetPositionY.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetPositionY001, TestSize.Level1)
{
    float positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(nullptr);
    EXPECT_EQ(positionY, 0.0f);

    ArkUI_UIInputEvent event;

    ArkUITouchEvent touchEvent;
    touchEvent.targetPositionY = 150.5f;
    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &touchEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 150.5f);

    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.targetPositionY = 250.5f;
    event.eventTypeId = TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &aceTouchEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 250.5f);

    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.targetPositionY = 350.5f;
    event.eventTypeId = AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &aceAxisEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 350.5f);

    ArkUIMouseEvent mouseEvent;
    mouseEvent.targetPositionY = 450.5f;
    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &mouseEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 450.5f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetPositionY002
 * @tc.desc: Test function OH_ArkUI_UIInputEvent_GetEventTargetPositionY.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetPositionY002, TestSize.Level1)
{
    float positionY = 1.0f;
    ArkUI_UIInputEvent event;

    ArkUIAxisEvent axisEvent;
    axisEvent.targetPositionY = 550.5f;
    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &axisEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 550.5f);

    ArkUIFocusAxisEvent focusAxisEvent;
    focusAxisEvent.targetPositionY = 650.5f;
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &focusAxisEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 650.5f);

    ArkUIHoverEvent hoverEvent;
    hoverEvent.targetPositionY = 750.5f;
    event.eventTypeId = C_HOVER_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &hoverEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 750.5f);

    ArkUIClickEvent clickEvent;
    clickEvent.targetPositionY = 850.5f;
    event.eventTypeId = C_CLICK_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &clickEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 850.5f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX001
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX001, TestSize.Level1)
{
    float positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(nullptr);
    EXPECT_EQ(positionX, 0.0f);

    ArkUI_UIInputEvent event;

    ArkUITouchEvent touchEvent;
    touchEvent.targetGlobalPositionX = 1234.56f;
    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &touchEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 1234.56f);

    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.targetGlobalPositionX = 2345.67f;
    event.eventTypeId = TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &aceTouchEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 2345.67f);

    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.targetGlobalPositionX = 3456.78f;
    event.eventTypeId = AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &aceAxisEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 3456.78f);

    ArkUIMouseEvent mouseEvent;
    mouseEvent.targetGlobalPositionX = 4567.89f;
    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &mouseEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 4567.89f);
}
/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX002
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX002, TestSize.Level1)
{
    float positionX = 1.0f;
    ArkUI_UIInputEvent event;

    ArkUIAxisEvent axisEvent;
    axisEvent.targetGlobalPositionX = 5678.90f;
    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &axisEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 5678.90f);

    ArkUIFocusAxisEvent focusAxisEvent;
    focusAxisEvent.targetGlobalPositionX = 6789.01f;
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &focusAxisEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 6789.01f);

    ArkUIHoverEvent hoverEvent;
    hoverEvent.targetGlobalPositionX = 7890.12f;
    event.eventTypeId = C_HOVER_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &hoverEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 7890.12f);

    ArkUIClickEvent clickEvent;
    clickEvent.targetGlobalPositionX = 8901.23f;
    event.eventTypeId = C_CLICK_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &clickEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 8901.23f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY001
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY001, TestSize.Level1)
{
    float positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(nullptr);
    EXPECT_EQ(positionY, 0.0f);

    ArkUI_UIInputEvent event;

    ArkUITouchEvent touchEvent;
    touchEvent.targetGlobalPositionY = 1122.33f;
    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &touchEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 1122.33f);

    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.targetGlobalPositionY = 2233.44f;
    event.eventTypeId = TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &aceTouchEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 2233.44f);

    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.targetGlobalPositionY = 3344.55f;
    event.eventTypeId = AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &aceAxisEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 3344.55f);

    ArkUIMouseEvent mouseEvent;
    mouseEvent.targetGlobalPositionY = 4455.66f;
    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &mouseEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 4455.66f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY002
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY002, TestSize.Level1)
{
    float positionY = 1.0f;
    ArkUI_UIInputEvent event;

    ArkUIAxisEvent axisEvent;
    axisEvent.targetGlobalPositionY = 5566.77f;
    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &axisEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 5566.77f);

    ArkUIFocusAxisEvent focusAxisEvent;
    focusAxisEvent.targetGlobalPositionY = 6677.88f;
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &focusAxisEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 6677.88f);

    ArkUIHoverEvent hoverEvent;
    hoverEvent.targetGlobalPositionY = 7788.99f;
    event.eventTypeId = C_HOVER_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &hoverEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 7788.99f);

    ArkUIClickEvent clickEvent;
    clickEvent.targetGlobalPositionY = 8899.00f;
    event.eventTypeId = C_CLICK_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &clickEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 8899.00f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_CreateClonedEvent001
 * @tc.desc: Test OH_ArkUI_PointerEvent_CreateClonedEvent
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_CreateClonedEvent001, TestSize.Level1)
{
    ArkUI_UIInputEvent* inputEvent = nullptr;
    ArkUI_UIInputEvent* clonedEvent;
    int32_t res = OH_ArkUI_PointerEvent_CreateClonedEvent(inputEvent, &clonedEvent);
    EXPECT_EQ(res, 401);
    inputEvent = new ArkUI_UIInputEvent();
    inputEvent->inputEvent = nullptr;
    res = OH_ArkUI_PointerEvent_CreateClonedEvent(inputEvent, &clonedEvent);
    EXPECT_EQ(res, 401);
    ArkUITouchEvent* touchEvent = new ArkUITouchEvent();
    inputEvent->inputEvent = touchEvent;
    inputEvent->isCloned = false;
    res = OH_ArkUI_PointerEvent_CreateClonedEvent(inputEvent, &clonedEvent);
    EXPECT_EQ(res, 401);
    inputEvent->isCloned = true;
    res = OH_ArkUI_PointerEvent_CreateClonedEvent(inputEvent, &clonedEvent);
    EXPECT_EQ(res, 401);
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent1;
    event.touchEvent.changedPointerId = 1;
    event.touchEvent.touchPointSize = 1;
    uiInputEvent1.inputEvent = &event.touchEvent;
    uiInputEvent1.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent1;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);
    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);

    touchEvent->target.id = touchEvenInput->target.id;
    touchEvent->target.type = touchEvenInput->target.type;
    touchEvent->target.area = touchEvenInput->target.area;
    touchEvent->target.origin = touchEvenInput->target.origin;
    touchEvent->action = touchEvenInput->action;
    touchEvent->changedPointerId = touchEvenInput->changedPointerId;
    touchEvent->actionTouchPoint = touchEvenInput->actionTouchPoint;
    touchEvent->timeStamp = touchEvenInput->timeStamp;
    touchEvent->sourceType = touchEvenInput->sourceType;
    touchEvent->targetDisplayId = touchEvenInput->targetDisplayId;
    touchEvent->deviceId = touchEvenInput->deviceId;
    res = OH_ArkUI_PointerEvent_CreateClonedEvent(inputEvent, &clonedEvent);
    EXPECT_EQ(res, 401);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_DestroyClonedEvent001
 * @tc.desc: Test OH_ArkUI_PointerEvent_DestroyClonedEvent
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_DestroyClonedEvent001, TestSize.Level1)
{
    ArkUI_UIInputEvent* inputEvent = nullptr;
    ArkUI_UIInputEvent* clonedEvent;
    inputEvent = new ArkUI_UIInputEvent();
    inputEvent->inputEvent = nullptr;
    ArkUITouchEvent* touchEvent = new ArkUITouchEvent();
    inputEvent->inputEvent = touchEvent;
    inputEvent->isCloned = false;
    inputEvent->isCloned = true;
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent1;
    event.touchEvent.changedPointerId = 1;
    event.touchEvent.touchPointSize = 1;
    uiInputEvent1.inputEvent = &event.touchEvent;
    uiInputEvent1.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent1;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);
    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);

    touchEvent->target.id = touchEvenInput->target.id;
    touchEvent->target.type = touchEvenInput->target.type;
    touchEvent->target.area = touchEvenInput->target.area;
    touchEvent->target.origin = touchEvenInput->target.origin;
    touchEvent->action = touchEvenInput->action;
    touchEvent->changedPointerId = touchEvenInput->changedPointerId;
    touchEvent->actionTouchPoint = touchEvenInput->actionTouchPoint;
    touchEvent->timeStamp = touchEvenInput->timeStamp;
    touchEvent->sourceType = touchEvenInput->sourceType;
    touchEvent->targetDisplayId = touchEvenInput->targetDisplayId;
    touchEvent->deviceId = touchEvenInput->deviceId;

    auto res = OH_ArkUI_PointerEvent_CreateClonedEvent(inputEvent, &clonedEvent);
    EXPECT_EQ(res, 401);

    auto res1 = OH_ArkUI_PointerEvent_DestroyClonedEvent(clonedEvent);
    EXPECT_EQ(res1, 401);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventLocalPosition001
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventLocalPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    event.touchEvent.actionTouchPoint.nodeX = ARKUI_X;
    event.touchEvent.actionTouchPoint.nodeY = ARKUI_Y;
    // deviceid
    event.touchEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.touchEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);
    event.touchEvent.target.id = touchEvenInput->target.id;
    event.touchEvent.target.type = touchEvenInput->target.type;
    event.touchEvent.target.area = touchEvenInput->target.area;
    event.touchEvent.target.origin = touchEvenInput->target.origin;
    event.touchEvent.action = touchEvenInput->action;
    event.touchEvent.changedPointerId = touchEvenInput->changedPointerId;
    event.touchEvent.actionTouchPoint = touchEvenInput->actionTouchPoint;
    event.touchEvent.timeStamp = touchEvenInput->timeStamp;
    event.touchEvent.sourceType = touchEvenInput->sourceType;
    event.touchEvent.targetDisplayId = touchEvenInput->targetDisplayId;
    event.touchEvent.deviceId = touchEvenInput->deviceId;

    auto nodeX = ARKUI_X - 1;
    auto nodeY = ARKUI_Y - 1;
    
    auto res = OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(inputEvent, nodeX, nodeY);
    EXPECT_EQ(res, 180003);
    auto x = OH_ArkUI_PointerEvent_GetX(inputEvent);
    auto y = OH_ArkUI_PointerEvent_GetY(inputEvent);
    EXPECT_EQ(x, ARKUI_X);
    EXPECT_EQ(y, ARKUI_Y);
    inputEvent->isCloned = true;
    res = OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(inputEvent, nodeX, nodeY);
    EXPECT_EQ(res, 0);
    auto x1 = OH_ArkUI_PointerEvent_GetX(inputEvent);
    auto y1 = OH_ArkUI_PointerEvent_GetY(inputEvent);
    EXPECT_EQ(x1, ARKUI_X - 1);
    EXPECT_EQ(y1, ARKUI_Y - 1);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex001
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    event.touchEvent.actionTouchPoint.nodeX = ARKUI_X;
    event.touchEvent.actionTouchPoint.nodeY = ARKUI_Y;
    // deviceid
    event.touchEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.touchEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);
    auto nodeX = ARKUI_X - 1;
    auto nodeY = ARKUI_Y - 1;
    
    auto res = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(inputEvent, nodeX, nodeY, 0);
    EXPECT_EQ(res, 180003);
    auto x = OH_ArkUI_PointerEvent_GetXByIndex(inputEvent, 0);
    auto y = OH_ArkUI_PointerEvent_GetYByIndex(inputEvent, 0);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 0);
    inputEvent->isCloned = true;
    res = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(inputEvent, nodeX, nodeY, 0);
    EXPECT_EQ(res, 401);
    auto x1 = OH_ArkUI_PointerEvent_GetXByIndex(inputEvent, 0);
    auto y1 = OH_ArkUI_PointerEvent_GetYByIndex(inputEvent, 0);
    EXPECT_EQ(x1, 0);
    EXPECT_EQ(y1, 0);

    ArkUITouchPoint points[2]; // 2 points
    points[0].nodeX = ARKUI_X;
    points[1].nodeY = ARKUI_Y;
    event.touchEvent.touchPointes = points;
    inputEvent->isCloned = false;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);
    event.touchEvent.target.id = touchEvenInput->target.id;
    event.touchEvent.target.type = touchEvenInput->target.type;
    event.touchEvent.target.area = touchEvenInput->target.area;
    event.touchEvent.target.origin = touchEvenInput->target.origin;
    event.touchEvent.action = touchEvenInput->action;
    event.touchEvent.changedPointerId = touchEvenInput->changedPointerId;
    event.touchEvent.actionTouchPoint = touchEvenInput->actionTouchPoint;
    event.touchEvent.timeStamp = touchEvenInput->timeStamp;
    event.touchEvent.sourceType = touchEvenInput->sourceType;
    event.touchEvent.targetDisplayId = touchEvenInput->targetDisplayId;
    event.touchEvent.deviceId = touchEvenInput->deviceId;

    res = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(inputEvent, nodeX, nodeY, 0);
    EXPECT_EQ(res, 180003);
    x = OH_ArkUI_PointerEvent_GetXByIndex(inputEvent, 0);
    y = OH_ArkUI_PointerEvent_GetYByIndex(inputEvent, 0);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 0);
    inputEvent->isCloned = true;
    res = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(inputEvent, nodeX, nodeY, 0);
    EXPECT_EQ(res, 401);
    x1 = OH_ArkUI_PointerEvent_GetXByIndex(inputEvent, 0);
    y1 = OH_ArkUI_PointerEvent_GetYByIndex(inputEvent, 0);
    EXPECT_EQ(x1, 0);
    EXPECT_EQ(y1, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventActionType001
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventActionType001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    event.touchEvent.actionTouchPoint.nodeX = ARKUI_X;
    event.touchEvent.actionTouchPoint.nodeY = ARKUI_Y;
    // deviceid
    event.touchEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.touchEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    event.touchEvent.action = ARKUI_ACTIONTYPE;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);
    event.touchEvent.target.id = touchEvenInput->target.id;
    event.touchEvent.target.type = touchEvenInput->target.type;
    event.touchEvent.target.area = touchEvenInput->target.area;
    event.touchEvent.target.origin = touchEvenInput->target.origin;
    event.touchEvent.action = touchEvenInput->action;
    event.touchEvent.changedPointerId = touchEvenInput->changedPointerId;
    event.touchEvent.actionTouchPoint = touchEvenInput->actionTouchPoint;
    event.touchEvent.timeStamp = touchEvenInput->timeStamp;
    event.touchEvent.sourceType = touchEvenInput->sourceType;
    event.touchEvent.targetDisplayId = touchEvenInput->targetDisplayId;
    event.touchEvent.deviceId = touchEvenInput->deviceId;

    auto res = OH_ArkUI_PointerEvent_SetClonedEventActionType(inputEvent, ARKUI_ACTIONTYPE_SET);
    auto action = OH_ArkUI_UIInputEvent_GetAction(inputEvent);
    EXPECT_EQ(res, 180003);
    EXPECT_EQ(action, 3);
    inputEvent->isCloned = true;
    res = OH_ArkUI_PointerEvent_SetClonedEventActionType(inputEvent, ARKUI_ACTIONTYPE_SET);
    action = OH_ArkUI_UIInputEvent_GetAction(inputEvent);
    EXPECT_EQ(res, 0);
    EXPECT_EQ(action, 1);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId001
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    event.touchEvent.actionTouchPoint.nodeX = ARKUI_X;
    event.touchEvent.actionTouchPoint.nodeY = ARKUI_Y;
    // deviceid
    event.touchEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.touchEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    event.touchEvent.action = ARKUI_FINGERID;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);
    event.touchEvent.target.id = touchEvenInput->target.id;
    event.touchEvent.target.type = touchEvenInput->target.type;
    event.touchEvent.target.area = touchEvenInput->target.area;
    event.touchEvent.target.origin = touchEvenInput->target.origin;
    event.touchEvent.action = touchEvenInput->action;
    event.touchEvent.changedPointerId = touchEvenInput->changedPointerId;
    event.touchEvent.actionTouchPoint = touchEvenInput->actionTouchPoint;
    event.touchEvent.timeStamp = touchEvenInput->timeStamp;
    event.touchEvent.sourceType = touchEvenInput->sourceType;
    event.touchEvent.targetDisplayId = touchEvenInput->targetDisplayId;
    event.touchEvent.deviceId = touchEvenInput->deviceId;

    auto res = OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(inputEvent, ARKUI_FINGERID_SET);
    auto pointerId = OH_ArkUI_PointerEvent_GetPointerId(inputEvent, 0);
    EXPECT_EQ(res, 180003);
    EXPECT_EQ(pointerId, 0);
    inputEvent->isCloned = true;
    res = OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(inputEvent, ARKUI_FINGERID_SET);
    pointerId = OH_ArkUI_PointerEvent_GetPointerId(inputEvent, 0);
    EXPECT_EQ(res, 0);
    EXPECT_EQ(pointerId, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex001
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    event.touchEvent.actionTouchPoint.nodeX = ARKUI_X;
    event.touchEvent.actionTouchPoint.nodeY = ARKUI_Y;
    // deviceid
    event.touchEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.touchEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    event.touchEvent.action = ARKUI_FINGERID;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);
    event.touchEvent.target.id = touchEvenInput->target.id;
    event.touchEvent.target.type = touchEvenInput->target.type;
    event.touchEvent.target.area = touchEvenInput->target.area;
    event.touchEvent.target.origin = touchEvenInput->target.origin;
    event.touchEvent.action = touchEvenInput->action;
    event.touchEvent.changedPointerId = touchEvenInput->changedPointerId;
    event.touchEvent.actionTouchPoint = touchEvenInput->actionTouchPoint;
    event.touchEvent.timeStamp = touchEvenInput->timeStamp;
    event.touchEvent.sourceType = touchEvenInput->sourceType;
    event.touchEvent.targetDisplayId = touchEvenInput->targetDisplayId;
    event.touchEvent.deviceId = touchEvenInput->deviceId;

    auto res = OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(inputEvent, ARKUI_FINGERID_SET, 0);
    auto pointerId = OH_ArkUI_PointerEvent_GetPointerId(inputEvent, 0);
    EXPECT_EQ(res, 180003);
    EXPECT_EQ(pointerId, 0);
    inputEvent->isCloned = true;
    res = OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(inputEvent, ARKUI_FINGERID_SET, 0);
    pointerId = OH_ArkUI_PointerEvent_GetPointerId(inputEvent, 0);
    EXPECT_EQ(res, 401);
    EXPECT_EQ(pointerId, 0);

    ArkUITouchPoint points[2]; // 2 points
    points[0].id = ARKUI_FINGERID;
    points[1].id = ARKUI_FINGERID;
    event.touchEvent.touchPointes = points;
    inputEvent->isCloned = true;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    res = OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(inputEvent, ARKUI_FINGERID_SET, 0);
    pointerId = OH_ArkUI_PointerEvent_GetPointerId(inputEvent, 0);
    EXPECT_EQ(res, 401);
    EXPECT_EQ(pointerId, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_PostClonedEvent001
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_PostClonedEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    event.touchEvent.actionTouchPoint.nodeX = ARKUI_X;
    event.touchEvent.actionTouchPoint.nodeY = ARKUI_Y;
    // deviceid
    event.touchEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.touchEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);
    ArkUI_NodeHandle nodeHandle = nullptr;

    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);
    event.touchEvent.target.id = touchEvenInput->target.id;
    event.touchEvent.target.type = touchEvenInput->target.type;
    event.touchEvent.target.area = touchEvenInput->target.area;
    event.touchEvent.target.origin = touchEvenInput->target.origin;
    event.touchEvent.action = touchEvenInput->action;
    event.touchEvent.changedPointerId = touchEvenInput->changedPointerId;
    event.touchEvent.actionTouchPoint = touchEvenInput->actionTouchPoint;
    event.touchEvent.timeStamp = touchEvenInput->timeStamp;
    event.touchEvent.sourceType = touchEvenInput->sourceType;
    event.touchEvent.targetDisplayId = touchEvenInput->targetDisplayId;
    event.touchEvent.deviceId = touchEvenInput->deviceId;
    inputEvent->isCloned = true;
    auto res = OH_ArkUI_PointerEvent_PostClonedEvent(nodeHandle, inputEvent);
    EXPECT_EQ(res, 180004);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_SetPropagation001
 * @tc.desc: Test OH_ArkUI_AxisEvent_SetPropagation functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_SetPropagation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    event.touchEvent.actionTouchPoint.nodeX = ARKUI_X;
    event.touchEvent.actionTouchPoint.nodeY = ARKUI_Y;
    // deviceid
    event.touchEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.touchEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    event.touchEvent.action = ARKUI_FINGERID;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);
    event.touchEvent.target.id = touchEvenInput->target.id;
    event.touchEvent.target.type = touchEvenInput->target.type;
    event.touchEvent.target.area = touchEvenInput->target.area;
    event.touchEvent.target.origin = touchEvenInput->target.origin;
    event.touchEvent.action = touchEvenInput->action;
    event.touchEvent.changedPointerId = touchEvenInput->changedPointerId;
    event.touchEvent.actionTouchPoint = touchEvenInput->actionTouchPoint;
    event.touchEvent.timeStamp = touchEvenInput->timeStamp;
    event.touchEvent.sourceType = touchEvenInput->sourceType;
    event.touchEvent.targetDisplayId = touchEvenInput->targetDisplayId;
    event.touchEvent.deviceId = touchEvenInput->deviceId;

    ArkUI_UIInputEvent setEvent;
    ArkUIAxisEvent cAxisEvent;
    cAxisEvent.propagation = true;
    setEvent.inputEvent = &cAxisEvent;
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    auto res = OH_ArkUI_AxisEvent_SetPropagation(nullptr, true);
    EXPECT_EQ(res, 401);
    res = OH_ArkUI_AxisEvent_SetPropagation(&setEvent, true);
    EXPECT_EQ(res, 0);
    cAxisEvent.propagation = false;
    setEvent.inputEvent = &cAxisEvent;
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_AxisEvent_SetPropagation(&setEvent, false);
    EXPECT_EQ(res, 0);
    cAxisEvent.propagation = true;
    setEvent.inputEvent = &cAxisEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    res = OH_ArkUI_AxisEvent_SetPropagation(&setEvent, true);
    EXPECT_EQ(res, 401);
    cAxisEvent.propagation = false;
    setEvent.inputEvent = &cAxisEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    res = OH_ArkUI_AxisEvent_SetPropagation(&setEvent, false);
    EXPECT_EQ(res, 401);
}

/**
 * @tc.name: OH_ArkUI_HoverEvent_IsHovered001
 * @tc.desc: Test OH_ArkUI_HoverEvent_IsHovered functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_HoverEvent_IsHovered001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    event.touchEvent.actionTouchPoint.nodeX = ARKUI_X;
    event.touchEvent.actionTouchPoint.nodeY = ARKUI_Y;
    // deviceid
    event.touchEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.touchEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    event.touchEvent.action = ARKUI_FINGERID;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);
    event.touchEvent.target.id = touchEvenInput->target.id;
    event.touchEvent.target.type = touchEvenInput->target.type;
    event.touchEvent.target.area = touchEvenInput->target.area;
    event.touchEvent.target.origin = touchEvenInput->target.origin;
    event.touchEvent.action = touchEvenInput->action;
    event.touchEvent.changedPointerId = touchEvenInput->changedPointerId;
    event.touchEvent.actionTouchPoint = touchEvenInput->actionTouchPoint;
    event.touchEvent.timeStamp = touchEvenInput->timeStamp;
    event.touchEvent.sourceType = touchEvenInput->sourceType;
    event.touchEvent.targetDisplayId = touchEvenInput->targetDisplayId;
    event.touchEvent.deviceId = touchEvenInput->deviceId;

    ArkUI_UIInputEvent setEvent;
    ArkUIHoverEvent hoverEvent;
    hoverEvent.isHover = true;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    auto res = OH_ArkUI_HoverEvent_IsHovered(nullptr);
    EXPECT_EQ(res, false);
    res = OH_ArkUI_HoverEvent_IsHovered(&setEvent);
    EXPECT_EQ(res, false);
    hoverEvent.isHover = false;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_HoverEvent_IsHovered(&setEvent);
    EXPECT_EQ(res, false);
    hoverEvent.isHover = true;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    res = OH_ArkUI_HoverEvent_IsHovered(&setEvent);
    EXPECT_EQ(res, true);
    hoverEvent.isHover = false;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    res = OH_ArkUI_HoverEvent_IsHovered(&setEvent);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetModifierKeyStates009
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetModifierKeyStates functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetModifierKeyStates009, TestSize.Level1)
{
    ArkUI_UIInputEvent setEvent;
    ArkUITouchEvent touchEvent;
    setEvent.inputEvent = &touchEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    uint64_t keys = C_TOUCH_EVENT_ID;
    auto res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(nullptr, &keys);
    EXPECT_EQ(res, 401);
    res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&setEvent, &keys);
    setEvent.eventTypeId = TOUCH_EVENT_ID;
    keys = TOUCH_EVENT_ID;
    res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&setEvent, &keys);
    ArkUIAxisEvent axisEvent;
    setEvent.inputEvent = &axisEvent;
    setEvent.eventTypeId = AXIS_EVENT_ID;
    keys = AXIS_EVENT_ID;
    res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&setEvent, &keys);
    EXPECT_EQ(res, 0);
    ArkUIMouseEvent mouseEvent;
    setEvent.inputEvent = &mouseEvent;
    setEvent.eventTypeId = C_MOUSE_EVENT_ID;
    keys = C_MOUSE_EVENT_ID;
    res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&setEvent, &keys);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    keys = C_AXIS_EVENT_ID;
    res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&setEvent, &keys);
    EXPECT_EQ(res, 0);
    ArkUIKeyEvent keyEvent;
    setEvent.inputEvent = &keyEvent;
    setEvent.eventTypeId = C_KEY_EVENT_ID;
    keys = C_KEY_EVENT_ID;
    res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&setEvent, &keys);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    keys = C_AXIS_EVENT_ID;
    res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&setEvent, &keys);
    EXPECT_EQ(res, 0);
    ArkUIHoverEvent hoverEvent;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    keys = C_HOVER_EVENT_ID;
    res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&setEvent, &keys);
    EXPECT_EQ(res, 0);
    ArkUIClickEvent clickEvent;
    setEvent.inputEvent = &clickEvent;
    setEvent.eventTypeId = C_CLICK_EVENT_ID;
    keys = C_CLICK_EVENT_ID;
    res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&setEvent, &keys);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetTiltX001
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetTiltX functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetTiltX001, TestSize.Level1)
{
    ArkUI_UIInputEvent setEvent;
    ArkUITouchEvent touchEvent;
    setEvent.inputEvent = &touchEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    auto res = OH_ArkUI_PointerEvent_GetTiltX(nullptr, -1);
    EXPECT_EQ(res, 0);
    touchEvent.subKind = ON_HOVER_MOVE;
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, 0);
    EXPECT_EQ(res, 0);
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, -1);
    setEvent.eventTypeId = TOUCH_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIAxisEvent axisEvent;
    setEvent.inputEvent = &axisEvent;
    setEvent.eventTypeId = AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIMouseEvent mouseEvent;
    setEvent.inputEvent = &mouseEvent;
    setEvent.eventTypeId = C_MOUSE_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, 0);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIKeyEvent keyEvent;
    setEvent.inputEvent = &keyEvent;
    setEvent.eventTypeId = C_KEY_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, 0);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIHoverEvent hoverEvent;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIClickEvent clickEvent;
    setEvent.inputEvent = &clickEvent;
    setEvent.eventTypeId = C_CLICK_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, 0);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetTiltY001
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetTiltY functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetTiltY001, TestSize.Level1)
{
    ArkUI_UIInputEvent setEvent;
    ArkUITouchEvent touchEvent;
    setEvent.inputEvent = &touchEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    auto res = OH_ArkUI_PointerEvent_GetTiltY(nullptr, -1);
    EXPECT_EQ(res, 0);
    touchEvent.subKind = ON_HOVER_MOVE;
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, 0);
    EXPECT_EQ(res, 0);
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, -1);
    setEvent.eventTypeId = TOUCH_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIAxisEvent axisEvent;
    setEvent.inputEvent = &axisEvent;
    setEvent.eventTypeId = AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIMouseEvent mouseEvent;
    setEvent.inputEvent = &mouseEvent;
    setEvent.eventTypeId = C_MOUSE_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, 0);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIKeyEvent keyEvent;
    setEvent.inputEvent = &keyEvent;
    setEvent.eventTypeId = C_KEY_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, 0);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIHoverEvent hoverEvent;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIClickEvent clickEvent;
    setEvent.inputEvent = &clickEvent;
    setEvent.eventTypeId = C_CLICK_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, 0);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetRollAngle001
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetRollAngle functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetRollAngle001, TestSize.Level1)
{
    ArkUI_UIInputEvent setEvent;
    ArkUITouchEvent touchEvent;
    setEvent.inputEvent = &touchEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    double rollAngle = 0.0;
    touchEvent.subKind = ON_HOVER_MOVE;
    touchEvent.actionTouchPoint.rollAngle = 1.0;
    auto res = OH_ArkUI_PointerEvent_GetRollAngle(nullptr, &rollAngle);
    EXPECT_EQ(res, 401);
    res = OH_ArkUI_PointerEvent_GetRollAngle(&setEvent, &rollAngle);
    setEvent.eventTypeId = TOUCH_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetRollAngle(&setEvent, &rollAngle);
    EXPECT_EQ(res, 401);
    ArkUIAxisEvent axisEvent;
    setEvent.inputEvent = &axisEvent;
    setEvent.eventTypeId = AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetRollAngle(&setEvent, &rollAngle);
    EXPECT_EQ(res, 401);
    ArkUIMouseEvent mouseEvent;
    setEvent.inputEvent = &mouseEvent;
    setEvent.eventTypeId = C_MOUSE_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetRollAngle(&setEvent, &rollAngle);
    EXPECT_EQ(res, 401);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetRollAngle(&setEvent, &rollAngle);
    EXPECT_EQ(res, 401);
    ArkUIKeyEvent keyEvent;
    setEvent.inputEvent = &keyEvent;
    setEvent.eventTypeId = C_KEY_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetRollAngle(&setEvent, &rollAngle);
    EXPECT_EQ(res, 401);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetRollAngle(&setEvent, &rollAngle);
    EXPECT_EQ(res, 401);
    ArkUIHoverEvent hoverEvent;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetRollAngle(&setEvent, &rollAngle);
    EXPECT_EQ(res, 0);
    ArkUIClickEvent clickEvent;
    setEvent.inputEvent = &clickEvent;
    setEvent.eventTypeId = C_CLICK_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetRollAngle(&setEvent, &rollAngle);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayYByIndex008
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetDisplayYByIndex functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayYByIndex008, TestSize.Level1)
{
    ArkUI_UIInputEvent setEvent;
    ArkUITouchEvent touchEvent;
    setEvent.inputEvent = &touchEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUITouchPoint points[2]; // 2 points
    ArkUITouchEvent* touchEventPtr = new ArkUITouchEvent();
    touchEventPtr->touchPointes = points;
    touchEventPtr->touchPointSize = 2;
    setEvent.inputEvent = touchEventPtr;
    auto res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(nullptr, 0);
    EXPECT_EQ(res, 0);
    res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&setEvent, 0);
    setEvent.eventTypeId = TOUCH_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIAxisEvent axisEvent;
    setEvent.inputEvent = &axisEvent;
    setEvent.eventTypeId = AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIMouseEvent mouseEvent;
    setEvent.inputEvent = &mouseEvent;
    setEvent.eventTypeId = C_MOUSE_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIKeyEvent keyEvent;
    setEvent.inputEvent = &keyEvent;
    setEvent.eventTypeId = C_KEY_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIHoverEvent hoverEvent;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIClickEvent clickEvent;
    setEvent.inputEvent = &clickEvent;
    setEvent.eventTypeId = C_CLICK_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayXByIndex008
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetDisplayXByIndex functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayXByIndex008, TestSize.Level1)
{
    ArkUI_UIInputEvent setEvent;
    ArkUITouchEvent touchEvent;
    setEvent.inputEvent = &touchEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUITouchPoint points[2]; // 2 points
    ArkUITouchEvent* touchEventPtr = new ArkUITouchEvent();
    touchEventPtr->touchPointes = points;
    touchEventPtr->touchPointSize = 2;
    setEvent.inputEvent = touchEventPtr;
    auto res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(nullptr, 0);
    EXPECT_EQ(res, 0);
    res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&setEvent, 0);
    setEvent.eventTypeId = TOUCH_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIAxisEvent axisEvent;
    setEvent.inputEvent = &axisEvent;
    setEvent.eventTypeId = AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIMouseEvent mouseEvent;
    setEvent.inputEvent = &mouseEvent;
    setEvent.eventTypeId = C_MOUSE_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIKeyEvent keyEvent;
    setEvent.inputEvent = &keyEvent;
    setEvent.eventTypeId = C_KEY_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIHoverEvent hoverEvent;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIClickEvent clickEvent;
    setEvent.inputEvent = &clickEvent;
    setEvent.eventTypeId = C_CLICK_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayX008
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetDisplayX functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayX008, TestSize.Level1)
{
    ArkUI_UIInputEvent setEvent;
    ArkUITouchEvent touchEvent;
    setEvent.inputEvent = &touchEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUITouchPoint points[2]; // 2 points
    ArkUITouchEvent* touchEventPtr = new ArkUITouchEvent();
    touchEventPtr->touchPointes = points;
    touchEventPtr->touchPointSize = 2;
    setEvent.inputEvent = touchEventPtr;
    auto res = OH_ArkUI_PointerEvent_GetDisplayX(nullptr);
    EXPECT_EQ(res, 0);
    res = OH_ArkUI_PointerEvent_GetDisplayX(&setEvent);
    setEvent.eventTypeId = TOUCH_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayX(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIAxisEvent axisEvent;
    setEvent.inputEvent = &axisEvent;
    setEvent.eventTypeId = AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayX(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIMouseEvent mouseEvent;
    setEvent.inputEvent = &mouseEvent;
    setEvent.eventTypeId = C_MOUSE_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayX(&setEvent);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayX(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIKeyEvent keyEvent;
    setEvent.inputEvent = &keyEvent;
    setEvent.eventTypeId = C_KEY_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayX(&setEvent);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayX(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIHoverEvent hoverEvent;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayX(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIClickEvent clickEvent;
    setEvent.inputEvent = &clickEvent;
    setEvent.eventTypeId = C_CLICK_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayX(&setEvent);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayY008
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetDisplayY functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayY008, TestSize.Level1)
{
    ArkUI_UIInputEvent setEvent;
    ArkUITouchEvent touchEvent;
    setEvent.inputEvent = &touchEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUITouchPoint points[2]; // 2 points
    points[0].screenY = 3.0;
    points[1].screenY = 4.0;
    ArkUITouchEvent* touchEventPtr = new ArkUITouchEvent();
    touchEventPtr->touchPointes = points;
    touchEventPtr->touchPointSize = 2;
    setEvent.inputEvent = touchEventPtr;
    auto res = OH_ArkUI_PointerEvent_GetDisplayY(nullptr);
    EXPECT_EQ(res, 0);
    res = OH_ArkUI_PointerEvent_GetDisplayY(&setEvent);
    setEvent.eventTypeId = TOUCH_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayY(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIAxisEvent axisEvent;
    setEvent.inputEvent = &axisEvent;
    setEvent.eventTypeId = AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayY(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIMouseEvent mouseEvent;
    setEvent.inputEvent = &mouseEvent;
    setEvent.eventTypeId = C_MOUSE_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayY(&setEvent);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayY(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIKeyEvent keyEvent;
    setEvent.inputEvent = &keyEvent;
    setEvent.eventTypeId = C_KEY_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayY(&setEvent);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayY(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIHoverEvent hoverEvent;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayY(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIClickEvent clickEvent;
    setEvent.inputEvent = &clickEvent;
    setEvent.eventTypeId = C_CLICK_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayY(&setEvent);
    EXPECT_EQ(res, 0);
}
} // namespace OHOS::Ace