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
constexpr int32_t TEST_AXIS_ACTION_BEGIN = 1;
constexpr int32_t TEST_AXIS_ACTION_UPDATE = 2;
constexpr int32_t TEST_AXIS_ACTION_END = 3;
constexpr int32_t TEST_AXIS_ACTION_NONE = 0;
} // namespace

namespace OHOS::Ace {

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetAxisAction001
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetAxisAction with null event pointer
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetAxisAction001, TestSize.Level0)
{
    auto result = OH_ArkUI_AxisEvent_GetAxisAction(nullptr);
    EXPECT_EQ(result, UI_AXIS_EVENT_ACTION_NONE);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetAxisAction002
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetAxisAction with all unsupported event types
 * @tc.type: FUNC
 */
/**
 * @tc.name: OH_ArkUI_AxisEvent_GetAxisAction002
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetAxisAction with all unsupported event types
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetAxisAction002, TestSize.Level0)
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
        auto result = OH_ArkUI_AxisEvent_GetAxisAction(&event);
        EXPECT_EQ(result, UI_AXIS_EVENT_ACTION_NONE) << "Failed for event type: " << static_cast<int>(eventTypeId);
    }
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetAxisAction101
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetAxisAction with AXIS_EVENT_ID type
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetAxisAction101, TestSize.Level0)
{
    // Prepare test data
    OHOS::Ace::AxisEvent axisEvent;
    axisEvent.action = OHOS::Ace::AxisAction::BEGIN;

    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, &axisEvent };

    // Test normal case
    auto result = OH_ArkUI_AxisEvent_GetAxisAction(&event);
    EXPECT_EQ(result, TEST_AXIS_ACTION_BEGIN);

    // Test null inputEvent case
    ArkUI_UIInputEvent nullEvent = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, nullptr };
    result = OH_ArkUI_AxisEvent_GetAxisAction(&nullEvent);
    EXPECT_EQ(result, UI_AXIS_EVENT_ACTION_NONE);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetAxisAction102
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetAxisAction with C_AXIS_EVENT_ID type
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetAxisAction102, TestSize.Level0)
{
    // Prepare test data
    ArkUIAxisEvent axisEvent;
    axisEvent.action = TEST_AXIS_ACTION_UPDATE;

    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &axisEvent };

    // Test normal case
    auto result = OH_ArkUI_AxisEvent_GetAxisAction(&event);
    EXPECT_EQ(result, TEST_AXIS_ACTION_UPDATE);

    // Test null inputEvent case
    ArkUI_UIInputEvent nullEvent = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, nullptr };
    result = OH_ArkUI_AxisEvent_GetAxisAction(&nullEvent);
    EXPECT_EQ(result, UI_AXIS_EVENT_ACTION_NONE);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetAxisAction103
 * @tc.desc: Test OH_ArkUI_AxisEvent_GetAxisAction with all action types
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetAxisAction103, TestSize.Level0)
{
    // Test BEGIN action
    OHOS::Ace::AxisEvent beginEvent;
    beginEvent.action = OHOS::Ace::AxisAction::BEGIN;
    ArkUI_UIInputEvent event1 = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, &beginEvent };
    auto result = OH_ArkUI_AxisEvent_GetAxisAction(&event1);
    EXPECT_EQ(result, TEST_AXIS_ACTION_BEGIN);

    // Test UPDATE action
    ArkUIAxisEvent updateEvent;
    updateEvent.action = TEST_AXIS_ACTION_UPDATE;
    ArkUI_UIInputEvent event2 = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &updateEvent };
    result = OH_ArkUI_AxisEvent_GetAxisAction(&event2);
    EXPECT_EQ(result, TEST_AXIS_ACTION_UPDATE);

    // Test END action
    OHOS::Ace::AxisEvent endEvent;
    endEvent.action = OHOS::Ace::AxisAction::END;
    ArkUI_UIInputEvent event3 = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, &endEvent };
    result = OH_ArkUI_AxisEvent_GetAxisAction(&event3);
    EXPECT_EQ(result, TEST_AXIS_ACTION_END);

    // Test NONE action
    ArkUIAxisEvent noneEvent;
    noneEvent.action = TEST_AXIS_ACTION_NONE;
    ArkUI_UIInputEvent event4 = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &noneEvent };
    result = OH_ArkUI_AxisEvent_GetAxisAction(&event4);
    EXPECT_EQ(result, TEST_AXIS_ACTION_NONE);
}

} // namespace OHOS::Ace