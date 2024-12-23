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

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
namespace {
constexpr int32_t ARKUI_DEVICE_ID = 1;
constexpr uint64_t ARKUI_TIME = 20;
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
} // namespace OHOS::Ace