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
 * @tc.name: OH_ArkUI_PointerEvent_GetY001
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetY function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetY001, TestSize.Level0)
{
    /**
     * @tc.steps: step1.call functions and return expected results.
     */
    auto result = OH_ArkUI_PointerEvent_GetY(nullptr);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetY101
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetY function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetY101, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 1 ArkUITouchEvent {C_TOUCH_EVENT_ID, HandleCTouchEventX}
    ArkUITouchEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_TOUCH_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0.0f },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, ARKUI_EVENT_Y - 1 }
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
            touchEvent->actionTouchPoint.nodeY = expect;
        }

        auto result = OH_ArkUI_PointerEvent_GetY(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetY102
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetY function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetY102, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 2 ArkUIMouseEvent {C_MOUSE_EVENT_ID, HandleCMouseEventX}
    ArkUIMouseEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_MOUSE_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0.0f },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, ARKUI_EVENT_Y - 1 }
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
            touchEvent->actionTouchPoint.nodeY = expect;
        }

        auto result = OH_ArkUI_PointerEvent_GetY(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetY103
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetY function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetY103, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 3 ArkUIAxisEvent {C_AXIS_EVENT_ID, HandleCAxisEventX}
    ArkUIAxisEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_AXIS_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0.0f },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, ARKUI_EVENT_Y - 1 }
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
            touchEvent->actionTouchPoint.nodeY = expect;
        }

        auto result = OH_ArkUI_PointerEvent_GetY(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetY104
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetY function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetY104, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 4 ArkUIClickEvent {C_CLICK_EVENT_ID, HandleCClickEventX}
    ArkUIClickEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_CLICK_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0.0f },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, ARKUI_EVENT_Y - 1 }
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
            touchEvent->localY = expect;
        }

        auto result = OH_ArkUI_PointerEvent_GetY(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetY105
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetY function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetY105, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 5 OHOS::Ace::AxisEvent {AXIS_EVENT_ID, HandleAxisEventX}
    OHOS::Ace::AxisEvent inputEvent;
    ArkUIEventTypeId eventTypeId = AXIS_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0.0f },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, ARKUI_EVENT_Y - 1 }
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
            touchEvent->localY = expect;
        }

        auto result = OH_ArkUI_PointerEvent_GetY(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetY106
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetY function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetY106, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 6 OHOS::Ace::TouchEvent {TOUCH_EVENT_ID, HandleTouchEventX}
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
            touchEvent->localY = expect;
        }

        auto result = OH_ArkUI_PointerEvent_GetY(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetY107
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetY function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetY107, TestSize.Level0)
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
        auto result = OH_ArkUI_PointerEvent_GetY(&uiInputEvent);
        EXPECT_EQ(result, static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN)) << "other index = " << count;
        count++;
    }
}

} // namespace OHOS::Ace