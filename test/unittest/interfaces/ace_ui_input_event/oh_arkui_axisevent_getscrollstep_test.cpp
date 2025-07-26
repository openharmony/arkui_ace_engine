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

#include "frameworks/base/error/error_code.h"

using namespace testing;
using namespace testing::ext;

namespace {
constexpr int32_t TEST_SCROLL_STEP = 30;
constexpr int32_t DEFAULT_SCROLL_STEP = 0;
} // namespace

namespace OHOS::Ace {

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetScrollStep001
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetScrollStep with null event pointer
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetScrollStep001, TestSize.Level0)
{
    auto result = OH_ArkUI_AxisEvent_GetScrollStep(nullptr);
    EXPECT_EQ(result, DEFAULT_SCROLL_STEP);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetScrollStep002
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetScrollStep with unsupported event type
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetScrollStep002, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, nullptr };
    auto result = OH_ArkUI_AxisEvent_GetScrollStep(&event);
    EXPECT_EQ(result, DEFAULT_SCROLL_STEP);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetScrollStep101
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetScrollStep with AXIS_EVENT_ID type
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetScrollStep101, TestSize.Level0)
{
    // Prepare test data
    OHOS::Ace::AxisEvent axisEvent;
    axisEvent.scrollStep = TEST_SCROLL_STEP;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, &axisEvent };

    // Test normal case
    auto result = OH_ArkUI_AxisEvent_GetScrollStep(&event);
    EXPECT_EQ(result, TEST_SCROLL_STEP);

    // Test null inputEvent case
    ArkUI_UIInputEvent nullEvent = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, nullptr };
    result = OH_ArkUI_AxisEvent_GetScrollStep(&nullEvent);
    EXPECT_EQ(result, DEFAULT_SCROLL_STEP);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetScrollStep102
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetScrollStep with C_AXIS_EVENT_ID type
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetScrollStep102, TestSize.Level0)
{
    // Prepare test data
    ArkUIAxisEvent axisEvent;
    axisEvent.scrollStep = TEST_SCROLL_STEP;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &axisEvent };

    // Test normal case
    auto result = OH_ArkUI_AxisEvent_GetScrollStep(&event);
    EXPECT_EQ(result, TEST_SCROLL_STEP);

    // Test null inputEvent case
    ArkUI_UIInputEvent nullEvent = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, nullptr };
    result = OH_ArkUI_AxisEvent_GetScrollStep(&nullEvent);
    EXPECT_EQ(result, DEFAULT_SCROLL_STEP);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetScrollStep103
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetScrollStep with different scroll step values
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetScrollStep103, TestSize.Level0)
{
    // Test positive value
    OHOS::Ace::AxisEvent positiveEvent;
    positiveEvent.scrollStep = 50;
    ArkUI_UIInputEvent event1 = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, &positiveEvent };
    auto result = OH_ArkUI_AxisEvent_GetScrollStep(&event1);
    EXPECT_EQ(result, 50);

    // Test zero value
    ArkUIAxisEvent zeroEvent;
    zeroEvent.scrollStep = 0;
    ArkUI_UIInputEvent event2 = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &zeroEvent };
    result = OH_ArkUI_AxisEvent_GetScrollStep(&event2);
    EXPECT_EQ(result, 0);

    // Test negative value
    OHOS::Ace::AxisEvent negativeEvent;
    negativeEvent.scrollStep = -20;
    ArkUI_UIInputEvent event3 = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, &negativeEvent };
    result = OH_ArkUI_AxisEvent_GetScrollStep(&event3);
    EXPECT_EQ(result, -20);
}

} // namespace OHOS::Ace