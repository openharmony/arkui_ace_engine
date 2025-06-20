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
constexpr float ARKUI_EVENT_X = 2.0;
} // namespace

namespace OHOS::Ace {

namespace {
struct GetWindowXByIndexTestInputType {
    explicit GetWindowXByIndexTestInputType(const ArkUI_UIInputEvent event, uint32_t pointerIndex = 0)
        : event(event), pointerIndex(pointerIndex)
        {};
    ArkUI_UIInputEvent event;
    uint32_t pointerIndex;
};
} // namespace

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowXByIndex001
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetWindowXByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowXByIndex001, TestSize.Level0)
{
    /**
     * @tc.steps: step1.call functions and return expected results.
     */
    auto result = OH_ArkUI_PointerEvent_GetWindowXByIndex(nullptr, 0);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowXByIndex101
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetWindowXByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowXByIndex101, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 1 ArkUITouchEvent {C_TOUCH_EVENT_ID, touchPointes[pointerIndex].nodeY}
    ArkUITouchEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_TOUCH_EVENT_ID;

    ArkUITouchPoint points[1];
    points[0].windowX = ARKUI_EVENT_X;
    inputEvent.touchPointes = &points[0];
    inputEvent.touchPointSize = 1;

    ArkUITouchEvent inputEventEmpty;

    std::vector<std::pair<GetWindowXByIndexTestInputType, int32_t>> testCases = {
        // case 1 !touchEvent
        { GetWindowXByIndexTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr}, 0), 0.0f },
        // case 2 pointerIndex < 0
        { GetWindowXByIndexTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent}, -1), 0.0f },
        // case 3 pointerIndex >= touchEvent->touchPointSize
        { GetWindowXByIndexTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent}, 1), 0.0f },
        // case 4 !(touchEvent->touchPointes)
        { GetWindowXByIndexTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEventEmpty}, 0), 0.0f },
        // case 5 getValue
        { GetWindowXByIndexTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent}, 0), ARKUI_EVENT_X},
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        auto result = OH_ArkUI_PointerEvent_GetWindowXByIndex(&input.event, input.pointerIndex);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowXByIndex102
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetWindowXByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowXByIndex102, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 2 ArkUIMouseEvent {C_MOUSE_EVENT_ID, mouseEvent->actionTouchPoint.nodeY}
    ArkUIMouseEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_MOUSE_EVENT_ID;
    inputEvent.actionTouchPoint.windowX = ARKUI_EVENT_X;

    std::vector<std::pair<GetWindowXByIndexTestInputType, int32_t>> testCases = {
        // case 1 !mouseEvent
        { GetWindowXByIndexTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr}, 0), 0.0f },
        // case 2 pointerIndex != 0
        { GetWindowXByIndexTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent}, 1), 0.0f },
        // case 3 getValue
        { GetWindowXByIndexTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent}, 0), ARKUI_EVENT_X },
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        auto result = OH_ArkUI_PointerEvent_GetWindowXByIndex(&input.event, input.pointerIndex);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowXByIndex103
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetWindowXByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowXByIndex103, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 3 ArkUIAxisEvent {C_AXIS_EVENT_ID, actionTouchPoint.nodeY}
    ArkUIAxisEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_AXIS_EVENT_ID;
    inputEvent.actionTouchPoint.windowX = ARKUI_EVENT_X;

    std::vector<std::pair<GetWindowXByIndexTestInputType, int32_t>> testCases = {
        // case 1 !mouseEvent
        { GetWindowXByIndexTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr}, 0), 0.0f },
        // case 2 pointerIndex != 0
        { GetWindowXByIndexTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent}, 1), 0.0f },
        // case 3 getValue
        { GetWindowXByIndexTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent}, 0), ARKUI_EVENT_X },
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        auto result = OH_ArkUI_PointerEvent_GetWindowXByIndex(&input.event, input.pointerIndex);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowXByIndex104
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetWindowXByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowXByIndex104, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 2 Other ArkUIEventTypeId
    std::vector<ArkUIEventTypeId> typeIds = {
        AXIS_EVENT_ID,
        TOUCH_EVENT_ID,
        C_KEY_EVENT_ID,
        C_FOCUS_AXIS_EVENT_ID,
        C_CLICK_EVENT_ID,
        C_HOVER_EVENT_ID
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    uint32_t pointerIndex = 0;
    for (auto typeId : typeIds) {
        auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, typeId, nullptr };
        auto result = OH_ArkUI_PointerEvent_GetWindowXByIndex(&uiInputEvent, pointerIndex);
        EXPECT_EQ(result, 0) << "other index = " << count;
        count++;
    }
}

} // namespace OHOS::Ace