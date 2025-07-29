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
constexpr double TEST_HORIZONTAL_AXIS = 2.5;
constexpr double TEST_HORIZONTAL_AXIS_2 = -1.8;
} // namespace

namespace OHOS::Ace {

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetHorizontalAxisValue001
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetHorizontalAxisValue with null event pointer
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetHorizontalAxisValue001, TestSize.Level0)
{
    auto result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(nullptr);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetHorizontalAxisValue002
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetHorizontalAxisValue with all unsupported event types
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetHorizontalAxisValue002, TestSize.Level0)
{
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
        auto result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(&event);
        EXPECT_DOUBLE_EQ(result, 0.0) << "Failed for event type: " << static_cast<int>(eventTypeId);
    }
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetHorizontalAxisValue101
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetHorizontalAxisValue with AXIS_EVENT_ID type
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetHorizontalAxisValue101, TestSize.Level0)
{
    // Prepare test data
    OHOS::Ace::AxisEvent axisEvent;
    axisEvent.horizontalAxis = TEST_HORIZONTAL_AXIS;

    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, &axisEvent };

    // Test normal case
    auto result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(&event);
    EXPECT_DOUBLE_EQ(result, TEST_HORIZONTAL_AXIS);

    // Test null inputEvent case
    ArkUI_UIInputEvent nullEvent = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, nullptr };
    result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(&nullEvent);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetHorizontalAxisValue102
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetHorizontalAxisValue with C_AXIS_EVENT_ID type
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetHorizontalAxisValue102, TestSize.Level0)
{
    // Prepare test data
    ArkUIAxisEvent axisEvent;
    axisEvent.horizontalAxis = TEST_HORIZONTAL_AXIS_2;

    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &axisEvent };

    // Test normal case
    auto result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(&event);
    EXPECT_DOUBLE_EQ(result, TEST_HORIZONTAL_AXIS_2);

    // Test null inputEvent case
    ArkUI_UIInputEvent nullEvent = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, nullptr };
    result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(&nullEvent);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetHorizontalAxisValue103
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetHorizontalAxisValue with boundary values for both event types
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetHorizontalAxisValue103, TestSize.Level0)
{
    // Test zero value for AXIS_EVENT_ID
    OHOS::Ace::AxisEvent zeroEvent;
    zeroEvent.horizontalAxis = 0.0;
    ArkUI_UIInputEvent event1 = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, &zeroEvent };
    auto result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(&event1);
    EXPECT_DOUBLE_EQ(result, 0.0);

    // Test maximum value for AXIS_EVENT_ID
    OHOS::Ace::AxisEvent largeAceEvent;
    largeAceEvent.horizontalAxis = DBL_MAX;
    ArkUI_UIInputEvent event2 = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, &largeAceEvent };
    result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(&event2);
    EXPECT_DOUBLE_EQ(result, DBL_MAX);

    // Test minimum value for AXIS_EVENT_ID
    OHOS::Ace::AxisEvent smallAceEvent;
    smallAceEvent.horizontalAxis = -DBL_MAX;
    ArkUI_UIInputEvent event3 = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, &smallAceEvent };
    result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(&event3);
    EXPECT_DOUBLE_EQ(result, -DBL_MAX);

    // Test zero value for C_AXIS_EVENT_ID
    ArkUIAxisEvent zeroCEvent;
    zeroCEvent.horizontalAxis = 0.0;
    ArkUI_UIInputEvent event4 = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &zeroCEvent };
    result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(&event4);
    EXPECT_DOUBLE_EQ(result, 0.0);

    // Test maximum value for C_AXIS_EVENT_ID
    ArkUIAxisEvent largeCEvent;
    largeCEvent.horizontalAxis = DBL_MAX;
    ArkUI_UIInputEvent event5 = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &largeCEvent };
    result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(&event5);
    EXPECT_DOUBLE_EQ(result, DBL_MAX);

    // Test minimum value for C_AXIS_EVENT_ID
    ArkUIAxisEvent smallCEvent;
    smallCEvent.horizontalAxis = -DBL_MAX;
    ArkUI_UIInputEvent event6 = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &smallCEvent };
    result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(&event6);
    EXPECT_DOUBLE_EQ(result, -DBL_MAX);
}

} // namespace OHOS::Ace