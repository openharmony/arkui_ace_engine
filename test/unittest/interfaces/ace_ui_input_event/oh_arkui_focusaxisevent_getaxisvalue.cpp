/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "../ui_input_event_test.h"
#include "interfaces/native/event/ui_input_event_impl.h"
#include "interfaces/native/ui_input_event.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
HWTEST_F(UIInputEventTest, OH_ArkUI_FocusAxisEvent_GetAxisValue_NullEvent, TestSize.Level0)
{
    auto result = OH_ArkUI_FocusAxisEvent_GetAxisValue(nullptr, UI_FOCUS_AXIS_EVENT_ABS_X);
    EXPECT_EQ(result, 0.0) << "Input event is nullptr, expected 0.0, got " << result;
}

HWTEST_F(UIInputEventTest, OH_ArkUI_FocusAxisEvent_GetAxisValue_WrongEventTypeId, TestSize.Level0)
{
    ArkUIFocusAxisEvent axisEvent = {};
    ArkUI_UIInputEvent inputEvent = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN,
        C_AXIS_EVENT_ID, // not C_FOCUS_AXIS_EVENT_ID
        &axisEvent };
    auto result = OH_ArkUI_FocusAxisEvent_GetAxisValue(&inputEvent, UI_FOCUS_AXIS_EVENT_ABS_X);
    EXPECT_EQ(result, 0.0) << "EventTypeId != C_FOCUS_AXIS_EVENT_ID, expected 0.0, got " << result;
}

HWTEST_F(UIInputEventTest, OH_ArkUI_FocusAxisEvent_GetAxisValue_InputEventNull, TestSize.Level0)
{
    ArkUI_UIInputEvent inputEvent = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_FOCUS_AXIS_EVENT_ID, nullptr };
    auto result = OH_ArkUI_FocusAxisEvent_GetAxisValue(&inputEvent, UI_FOCUS_AXIS_EVENT_ABS_X);
    EXPECT_EQ(result, 0.0) << "inputEvent is nullptr, expected 0.0, got " << result;
}

HWTEST_F(UIInputEventTest, OH_ArkUI_FocusAxisEvent_GetAxisValue_AxisVariants, TestSize.Level0)
{
    ArkUIFocusAxisEvent axisEvent = {};
    axisEvent.absXValue = 1.1;
    axisEvent.absYValue = 2.2;
    axisEvent.absZValue = 3.3;
    axisEvent.absRzValue = 4.4;
    axisEvent.absGasValue = 5.5;
    axisEvent.absBrakeValue = 6.6;
    axisEvent.absHat0XValue = 7.7;
    axisEvent.absHat0YValue = 8.8;

    ArkUI_UIInputEvent inputEvent = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_FOCUS_AXIS_EVENT_ID, &axisEvent };

    struct AxisTestCase {
        int32_t axis;
        double expected;
        const char* axisName;
    };
    std::vector<AxisTestCase> cases = {
        { UI_FOCUS_AXIS_EVENT_ABS_X, axisEvent.absXValue, "ABS_X" },
        { UI_FOCUS_AXIS_EVENT_ABS_Y, axisEvent.absYValue, "ABS_Y" },
        { UI_FOCUS_AXIS_EVENT_ABS_Z, axisEvent.absZValue, "ABS_Z" },
        { UI_FOCUS_AXIS_EVENT_ABS_RZ, axisEvent.absRzValue, "ABS_RZ" },
        { UI_FOCUS_AXIS_EVENT_ABS_GAS, axisEvent.absGasValue, "ABS_GAS" },
        { UI_FOCUS_AXIS_EVENT_ABS_BRAKE, axisEvent.absBrakeValue, "ABS_BRAKE" },
        { UI_FOCUS_AXIS_EVENT_ABS_HAT0X, axisEvent.absHat0XValue, "ABS_HAT0X" },
        { UI_FOCUS_AXIS_EVENT_ABS_HAT0Y, axisEvent.absHat0YValue, "ABS_HAT0Y" },
        { 999, 0.0, "UNKNOWN_AXIS" }, // Invalid axis
    };
    int count = 0;
    for (const auto& testCase : cases) {
        double result = OH_ArkUI_FocusAxisEvent_GetAxisValue(&inputEvent, testCase.axis);
        EXPECT_DOUBLE_EQ(result, testCase.expected) << "index = " << count << " : axis = " << testCase.axisName
                                                    << " expected = " << testCase.expected << " actual = " << result;
        count++;
    }
}
} // namespace OHOS::Ace
