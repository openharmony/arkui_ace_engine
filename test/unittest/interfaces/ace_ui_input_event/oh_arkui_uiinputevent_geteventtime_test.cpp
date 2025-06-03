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
constexpr uint64_t ARKUI_EVENT_ARKUI_TIME = 20;
constexpr uint64_t ARKUI_EVENT_ARKUI_TIME_NULL = 0;
} // namespace

namespace OHOS::Ace {

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTime001
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetEventTime function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTime001, TestSize.Level0)
{
    /**
     * @tc.steps: step1.call functions and return expected results.
     */
    auto result = OH_ArkUI_UIInputEvent_GetEventTime(nullptr);
    EXPECT_EQ(result, ARKUI_EVENT_ARKUI_TIME_NULL);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTime101
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetEventTime function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTime101, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 1 ArkUITouchEvent {C_TOUCH_EVENT_ID, HandleCTouchEvent}
    ArkUITouchEvent inputEvent;

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    // case 1
    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, nullptr };
    auto result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ARKUI_TIME_NULL) << " , result = " << result;

    // case 2
    inputEvent.timeStamp = ARKUI_EVENT_ARKUI_TIME;
    uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &inputEvent };
    result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ARKUI_TIME) << " , result = " << result;
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTime102
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetEventTime function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTime102, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 2 ArkUIMouseEvent {C_MOUSE_EVENT_ID, HandleCMouseEvent}
    ArkUIMouseEvent inputEvent;

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    // case 1
    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, nullptr };
    auto result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ARKUI_TIME_NULL) << " , result = " << result;

    // case 2
    inputEvent.timeStamp = ARKUI_EVENT_ARKUI_TIME;
    uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, &inputEvent };
    result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ARKUI_TIME) << " , result = " << result;
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTime103
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetEventTime function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTime103, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 3 ArkUIAxisEvent {C_AXIS_EVENT_ID, HandleCAxisEvent}
    ArkUIAxisEvent inputEvent;

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    // case 1
    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, nullptr };
    auto result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ARKUI_TIME_NULL) << " , result = " << result;

    // case 2
    inputEvent.timeStamp = ARKUI_EVENT_ARKUI_TIME;
    uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &inputEvent };
    result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ARKUI_TIME) << " , result = " << result;
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTime104
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetEventTime function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTime104, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 4 ArkUIFocusAxisEvent {C_FOCUS_AXIS_EVENT_ID, HandleCFocusAxisEvent}
    ArkUIFocusAxisEvent inputEvent;

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    // case 1
    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_FOCUS_AXIS_EVENT_ID, nullptr };
    auto result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ARKUI_TIME_NULL) << " , result = " << result;

    // case 2
    inputEvent.timeStamp = ARKUI_EVENT_ARKUI_TIME;
    uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_FOCUS_AXIS_EVENT_ID, &inputEvent };
    result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ARKUI_TIME) << " , result = " << result;
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTime105
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetEventTime function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTime105, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 5 ArkUIHoverEvent {C_HOVER_EVENT_ID, HandleCHoverEventTimestamp}
    ArkUIHoverEvent inputEvent;

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    // case 1
    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_HOVER_EVENT_ID, nullptr };
    auto result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ARKUI_TIME_NULL) << " , result = " << result;

    // case 2
    inputEvent.timeStamp = ARKUI_EVENT_ARKUI_TIME;
    uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_HOVER_EVENT_ID, &inputEvent };
    result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ARKUI_TIME) << " , result = " << result;
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTime106
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetEventTime function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTime106, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 6 ArkUIClickEvent {C_CLICK_EVENT_ID, HandleCClickEventTimestamp}
    ArkUIClickEvent inputEvent;

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    // case 1
    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_CLICK_EVENT_ID, nullptr };
    auto result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ARKUI_TIME_NULL) << " , result = " << result;

    // case 2
    inputEvent.timestamp = ARKUI_EVENT_ARKUI_TIME;
    uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_CLICK_EVENT_ID, &inputEvent };
    result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ARKUI_TIME) << " , result = " << result;
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTime107
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetEventTime function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTime107, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 7 OHOS::Ace::AxisEvent {AXIS_EVENT_ID, HandleAxisEvent}
    OHOS::Ace::PointerEvent inputEvent;

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    // case 1
    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, nullptr };
    auto result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ARKUI_TIME_NULL) << " , result = " << result;

    // case 2
    inputEvent.time = TimeStamp(std::chrono::nanoseconds(ARKUI_EVENT_ARKUI_TIME));
    uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, &inputEvent };
    result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
    EXPECT_EQ(result, inputEvent.time.time_since_epoch().count()) << " , result = " << result;
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTime108
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetEventTime function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTime108, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 8 OHOS::Ace::TouchEvent {TOUCH_EVENT_ID, HandleTouchEvent}
    OHOS::Ace::PointerEvent inputEvent;

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    // case 1
    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, TOUCH_EVENT_ID, nullptr };
    auto result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ARKUI_TIME_NULL) << " , result = " << result;

    // case 2
    inputEvent.time = TimeStamp(std::chrono::nanoseconds(ARKUI_EVENT_ARKUI_TIME));
    uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, TOUCH_EVENT_ID, &inputEvent };
    result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
    EXPECT_EQ(result, inputEvent.time.time_since_epoch().count()) << " , result = " << result;
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTime109
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetEventTime function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTime109, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 9 ArkUIKeyEvent {C_KEY_EVENT_ID, HandleCKeyEvent}
    ArkUIKeyEvent inputEvent;

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    // case 1
    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_KEY_EVENT_ID, nullptr };
    auto result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ARKUI_TIME_NULL) << " , result = " << result;

    // case 2
    inputEvent.timestamp = ARKUI_EVENT_ARKUI_TIME;
    uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_KEY_EVENT_ID, &inputEvent };
    result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ARKUI_TIME) << " , result = " << result;
}

} // namespace OHOS::Ace