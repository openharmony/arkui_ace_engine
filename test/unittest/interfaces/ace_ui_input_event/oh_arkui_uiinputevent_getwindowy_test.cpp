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
constexpr float ARKUI_EVENT_Y = 3.0;
} // namespace

namespace OHOS::Ace {

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowY001
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetWindowY function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowY001, TestSize.Level0)
{
    /**
     * @tc.steps: step1.call functions and return expected results.
     */
    auto result = OH_ArkUI_PointerEvent_GetWindowY(nullptr);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowY101
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetWindowY function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowY101, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 1 ArkUITouchEvent {C_TOUCH_EVENT_ID, HandleCTouchEventWindowY}
    ArkUITouchEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_TOUCH_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr },
            0.0f },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            ARKUI_EVENT_Y - 1 }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;

        auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(input.inputEvent);
        if (touchEvent) {
            touchEvent->actionTouchPoint.windowY = expect;
        }

        auto result = OH_ArkUI_PointerEvent_GetWindowY(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowY102
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetWindowY function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowY102, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 2 ArkUIMouseEvent {C_MOUSE_EVENT_ID, HandleCMouseEventWindowY}
    ArkUIMouseEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_MOUSE_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr },
            0.0f },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            ARKUI_EVENT_Y - 1 }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        
        auto* touchEvent = reinterpret_cast<ArkUIMouseEvent*>(input.inputEvent);
        if (touchEvent) {
            touchEvent->actionTouchPoint.windowY = expect;
        }

        auto result = OH_ArkUI_PointerEvent_GetWindowY(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowY103
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetWindowY function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowY103, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 3 ArkUIAxisEvent {C_AXIS_EVENT_ID, HandleCAxisEventWindowY}
    ArkUIAxisEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_AXIS_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr },
            0.0f },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            ARKUI_EVENT_Y - 1 }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        
        auto* touchEvent = reinterpret_cast<ArkUIAxisEvent*>(input.inputEvent);
        if (touchEvent) {
            touchEvent->actionTouchPoint.windowY = expect;
        }

        auto result = OH_ArkUI_PointerEvent_GetWindowY(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowY104
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetWindowY function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowY104, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 4 ArkUIClickEvent {C_CLICK_EVENT_ID, HandleCClickEventY}
    ArkUIClickEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_CLICK_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr },
            0.0f },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            ARKUI_EVENT_Y - 1 }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        
        auto* touchEvent = reinterpret_cast<ArkUIClickEvent*>(input.inputEvent);
        if (touchEvent) {
            touchEvent->windowY = expect;
        }

        auto result = OH_ArkUI_PointerEvent_GetWindowY(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowY105
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetWindowY function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowY105, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 5 OHOS::Ace::AxisEvent {AXIS_EVENT_ID, HandleAxisEventWindowY}
    OHOS::Ace::AxisEvent inputEvent;
    ArkUIEventTypeId eventTypeId = AXIS_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr },
            0.0f },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            ARKUI_EVENT_Y - 1 }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        
        auto* touchEvent = reinterpret_cast<OHOS::Ace::AxisEvent*>(input.inputEvent);
        if (touchEvent) {
            touchEvent->y = expect;
        }

        auto result = OH_ArkUI_PointerEvent_GetWindowY(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowY106
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetWindowY function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowY106, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 6 OHOS::Ace::TouchEvent {TOUCH_EVENT_ID, HandleTouchEventWindowY}
    OHOS::Ace::TouchEvent inputEvent;
    ArkUIEventTypeId eventTypeId = TOUCH_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr },
            0.0f },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            ARKUI_EVENT_Y - 1 }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        
        auto* touchEvent = reinterpret_cast<OHOS::Ace::TouchEvent*>(input.inputEvent);
        if (touchEvent) {
            touchEvent->y = expect;
        }

        auto result = OH_ArkUI_PointerEvent_GetWindowY(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowY107
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetWindowY function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowY107, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 2 Other ArkUIEventTypeId
    std::vector<ArkUIEventTypeId> typeIds = {
        C_KEY_EVENT_ID,
        C_FOCUS_AXIS_EVENT_ID,
        C_HOVER_EVENT_ID
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto typeId : typeIds) {
        auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, typeId, nullptr };
        auto result = OH_ArkUI_PointerEvent_GetWindowY(&uiInputEvent);
        EXPECT_EQ(result, static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN)) << "other index = " << count;
        count++;
    }
}

} // namespace OHOS::Ace