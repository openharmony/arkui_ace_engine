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

#include "event/ui_input_event_impl.h"
#include "gtest/gtest.h"
#include "interfaces/native/node/event_converter.h"
#include "native_node.h"
#include "ui_input_event.h"

#include "frameworks/core/event/ace_events.h"
#include "frameworks/core/event/axis_event.h"

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
constexpr ArkUI_Uint64 ARKUI_MODIFIERKEYSTATE = 1;
constexpr ArkUI_Uint32 ARKUI_POINTERCOUNTER = 2;
} // namespace
class UIInputEventTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

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
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetModifierKeyStates(inputEvent, 0), ARKUI_MODIFIERKEYSTATE);
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
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetModifierKeyStates(inputEvent, 0), ARKUI_MODIFIERKEYSTATE);
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
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetModifierKeyStates(inputEvent, 0), ARKUI_MODIFIERKEYSTATE);
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
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetModifierKeyStates(inputEvent, 0), ARKUI_MODIFIERKEYSTATE);
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
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetModifierKeyStates(inputEvent, 0), ARKUI_MODIFIERKEYSTATE);
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
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetModifierKeyStates(inputEvent, 0), ARKUI_MODIFIERKEYSTATE);
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
} // namespace OHOS::Ace