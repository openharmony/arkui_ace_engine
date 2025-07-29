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

using namespace testing;
using namespace testing::ext;

namespace {
constexpr double TEST_VERTICAL_AXIS = 1.5;
constexpr double TEST_VERTICAL_AXIS_2 = -2.3;
} // namespace

namespace OHOS::Ace {

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetVerticalAxisValue001
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetVerticalAxisValue with null event pointer
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetVerticalAxisValue001, TestSize.Level0)
{
    auto result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(nullptr);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetVerticalAxisValue002
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetVerticalAxisValue with all unsupported event types
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetVerticalAxisValue002, TestSize.Level0)
{
    // Define all unsupported event types (excluding AXIS_EVENT_ID which should be supported)
    std::vector<std::pair<ArkUI_UIInputEvent_Type, ArkUIEventTypeId>> unsupportedEventTypes = {
        { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, TOUCH_EVENT_ID },        // 1
        { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID },      // 2
        { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID },        // 3
        { ARKUI_UIINPUTEVENT_TYPE_KEY, C_KEY_EVENT_ID },            // 5
        { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_FOCUS_AXIS_EVENT_ID }, // 6
        { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_CLICK_EVENT_ID },      // 7
        { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_HOVER_EVENT_ID },      // 8
    };

    // Test each unsupported event type
    for (const auto& [inputType, eventTypeId] : unsupportedEventTypes) {
        ArkUITouchEvent inputEvent;
        ArkUI_UIInputEvent event = { inputType, eventTypeId, &inputEvent, false };
        auto result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(&event);
        EXPECT_DOUBLE_EQ(result, 0.0) << "Failed for event type: " << static_cast<int>(eventTypeId);
    }
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetVerticalAxisValue101
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetVerticalAxisValue with AXIS_EVENT_ID type event
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetVerticalAxisValue101, TestSize.Level0)
{
    // Prepare test data
    OHOS::Ace::AxisEvent axisEvent;
    axisEvent.verticalAxis = TEST_VERTICAL_AXIS;

    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, &axisEvent };

    // Test normal case
    auto result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(&event);
    EXPECT_DOUBLE_EQ(result, TEST_VERTICAL_AXIS);

    // Test case with null inputEvent
    ArkUI_UIInputEvent nullEvent = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, nullptr };
    result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(&nullEvent);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetVerticalAxisValue102
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetVerticalAxisValue with C_AXIS_EVENT_ID type event
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetVerticalAxisValue102, TestSize.Level0)
{
    // Prepare test data

    ArkUIAxisEvent axisEvent;

    axisEvent.verticalAxis = TEST_VERTICAL_AXIS_2;

    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &axisEvent };

    // Test normal case
    auto result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(&event);
    EXPECT_DOUBLE_EQ(result, TEST_VERTICAL_AXIS_2);

    // Test case with null inputEvent
    ArkUI_UIInputEvent nullEvent = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, nullptr };
    result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(&nullEvent);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetVerticalAxisValue103
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetVerticalAxisValue with boundary values
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetVerticalAxisValue103, TestSize.Level0)
{
    // Test zero value
    OHOS::Ace::AxisEvent zeroEvent;
    zeroEvent.verticalAxis = 0.0;
    ArkUI_UIInputEvent event1 = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, &zeroEvent };
    auto result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(&event1);
    EXPECT_DOUBLE_EQ(result, 0.0);

    // Test maximum value
    ArkUIAxisEvent largeEvent;
    largeEvent.verticalAxis = DBL_MAX;
    ArkUI_UIInputEvent event2 = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &largeEvent };
    result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(&event2);
    EXPECT_DOUBLE_EQ(result, DBL_MAX);

    // Test minimum value
    ArkUIAxisEvent smallEvent;
    smallEvent.verticalAxis = -DBL_MAX;
    ArkUI_UIInputEvent event3 = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &smallEvent };
    result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(&event3);
    EXPECT_DOUBLE_EQ(result, -DBL_MAX);
}

} // namespace OHOS::Ace