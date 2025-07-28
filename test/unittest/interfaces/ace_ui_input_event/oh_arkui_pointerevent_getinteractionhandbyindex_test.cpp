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
constexpr ArkUI_InteractionHand ARKUI_LEFT_HAND = ARKUI_EVENT_HAND_LEFT;
constexpr ArkUI_InteractionHand ARKUI_RIGHT_HAND = ARKUI_EVENT_HAND_RIGHT;
} // namespace

namespace OHOS::Ace {

namespace {
struct GetInteractionHandTestInputType {
    explicit GetInteractionHandTestInputType(
        ArkUI_UIInputEvent event, int32_t pointerIndex, ArkUI_InteractionHand* hand)
        : event(event), pointerIndex(pointerIndex), hand(hand) {};
    ArkUI_UIInputEvent event;
    int32_t pointerIndex;
    ArkUI_InteractionHand* hand;
};
} // namespace

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetInteractionHandByIndex001
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetInteractionHandByIndex function with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetInteractionHandByIndex001, TestSize.Level0)
{
    ArkUI_InteractionHand hand;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, nullptr };

    // case 1: null event
    auto result1 = OH_ArkUI_PointerEvent_GetInteractionHandByIndex(nullptr, 0, &hand);
    EXPECT_EQ(result1, ARKUI_ERROR_CODE_PARAM_INVALID);

    // case 2: null hand
    auto result2 = OH_ArkUI_PointerEvent_GetInteractionHandByIndex(&event, 0, nullptr);
    EXPECT_EQ(result2, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetInteractionHandByIndex101
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetInteractionHandByIndex function with touch event.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetInteractionHandByIndex101, TestSize.Level0)
{
    ArkUITouchEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_TOUCH_EVENT_ID;

    ArkUITouchPoint points[2];
    points[0].operatingHand = static_cast<int32_t>(ARKUI_LEFT_HAND);
    points[1].operatingHand = static_cast<int32_t>(ARKUI_RIGHT_HAND);
    inputEvent.touchPointes = &points[0];
    inputEvent.touchPointSize = 2;

    ArkUITouchEvent inputEventEmpty;
    ArkUI_InteractionHand hand;

    ArkUI_UIInputEvent nullEvent = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr };
    ArkUI_UIInputEvent emptyEvent = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEventEmpty };
    ArkUI_UIInputEvent validEvent = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent };

    std::vector<std::tuple<ArkUI_UIInputEvent, int32_t, ArkUI_InteractionHand*, ArkUI_InteractionHand, int32_t>>
        testCases = {
            // case 1: null touch event
            { nullEvent, 0, &hand, ARKUI_EVENT_HAND_NONE, ARKUI_ERROR_CODE_PARAM_INVALID },
            // case 2: empty touch points
            { emptyEvent, 0, &hand, ARKUI_EVENT_HAND_NONE, ARKUI_ERROR_CODE_PARAM_INVALID },
            // case 3: invalid pointer index (negative)
            { validEvent, -1, &hand, ARKUI_EVENT_HAND_NONE, ARKUI_ERROR_CODE_PARAM_INVALID },
            // case 4: invalid pointer index (out of range)
            { validEvent, 2, &hand, ARKUI_EVENT_HAND_NONE, ARKUI_ERROR_CODE_PARAM_INVALID },
            // case 5: valid pointer index 0
            { validEvent, 0, &hand, ARKUI_LEFT_HAND, ARKUI_ERROR_CODE_NO_ERROR },
            // case 6: valid pointer index 1
            { validEvent, 1, &hand, ARKUI_RIGHT_HAND, ARKUI_ERROR_CODE_NO_ERROR },
        };

    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& testCase = testCases[i];
        auto result = OH_ArkUI_PointerEvent_GetInteractionHandByIndex(
            &std::get<0>(testCase), std::get<1>(testCase), std::get<2>(testCase));

        if (std::get<2>(testCase) != nullptr) {
            EXPECT_EQ(*std::get<2>(testCase), std::get<3>(testCase)) << "Test case " << i << " hand value mismatch";
        }
        EXPECT_EQ(result, std::get<4>(testCase)) << "Test case " << i << " return code mismatch";
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetInteractionHandByIndex102
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetInteractionHandByIndex function with unsupported event types.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetInteractionHandByIndex102, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent;
    ArkUIAxisEvent axisEvent;
    ArkUI_InteractionHand hand;

    ArkUI_UIInputEvent mouseEventWrapper = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, &mouseEvent };
    ArkUI_UIInputEvent axisEventWrapper = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &axisEvent };
    ArkUI_UIInputEvent keyEventWrapper = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_KEY_EVENT_ID, nullptr };
    ArkUI_UIInputEvent hoverEventWrapper = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_HOVER_EVENT_ID, nullptr };

    std::vector<std::pair<ArkUI_UIInputEvent, ArkUIEventTypeId>> testCases = {
        // case 1: mouse event
        { mouseEventWrapper, C_MOUSE_EVENT_ID },
        // case 2: axis event
        { axisEventWrapper, C_AXIS_EVENT_ID },
        // case 3: key event
        { keyEventWrapper, C_KEY_EVENT_ID },
        // case 4: hover event
        { hoverEventWrapper, C_HOVER_EVENT_ID },
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& testCase = testCases[i];
        auto result = OH_ArkUI_PointerEvent_GetInteractionHandByIndex(&testCase.first, 0, &hand);
        EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR) << "Unsupported type test " << i << " failed";
    }
}

} // namespace OHOS::Ace