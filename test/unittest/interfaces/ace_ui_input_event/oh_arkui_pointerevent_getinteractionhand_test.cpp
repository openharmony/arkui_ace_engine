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

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetInteractionHand001
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetInteractionHand function with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetInteractionHand001, TestSize.Level0)
{
    ArkUI_InteractionHand hand;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, nullptr };

    // case 1: null event
    auto result1 = OH_ArkUI_PointerEvent_GetInteractionHand(nullptr, &hand);
    EXPECT_EQ(result1, ARKUI_ERROR_CODE_PARAM_INVALID);

    // case 2: null hand
    auto result2 = OH_ArkUI_PointerEvent_GetInteractionHand(&event, nullptr);
    EXPECT_EQ(result2, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetInteractionHand101
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetInteractionHand function with touch event.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetInteractionHand101, TestSize.Level0)
{
    ArkUIEventTypeId eventTypeId = C_TOUCH_EVENT_ID;
    ArkUI_InteractionHand hand;

    // Test left hand case
    ArkUITouchEvent leftInputEvent;
    leftInputEvent.actionTouchPoint.operatingHand = static_cast<int32_t>(ARKUI_LEFT_HAND);
    ArkUI_UIInputEvent leftHandEvent = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &leftInputEvent };

    auto leftResult = OH_ArkUI_PointerEvent_GetInteractionHand(&leftHandEvent, &hand);
    EXPECT_EQ(leftResult, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(hand, ARKUI_LEFT_HAND) << "Left hand test failed";

    // Test right hand case
    ArkUITouchEvent rightInputEvent;
    rightInputEvent.actionTouchPoint.operatingHand = static_cast<int32_t>(ARKUI_RIGHT_HAND);
    ArkUI_UIInputEvent rightHandEvent = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &rightInputEvent };

    auto rightResult = OH_ArkUI_PointerEvent_GetInteractionHand(&rightHandEvent, &hand);
    EXPECT_EQ(rightResult, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(hand, ARKUI_RIGHT_HAND) << "Right hand test failed";
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetInteractionHand102
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetInteractionHand function with unsupported event types.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetInteractionHand102, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent;
    ArkUIAxisEvent axisEvent;
    ArkUI_InteractionHand hand;

    ArkUI_UIInputEvent mouseEventWrapper = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, &mouseEvent };
    ArkUI_UIInputEvent axisEventWrapper = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &axisEvent };
    ArkUI_UIInputEvent keyEventWrapper = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_KEY_EVENT_ID, nullptr };
    ArkUI_UIInputEvent hoverEventWrapper = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_HOVER_EVENT_ID, nullptr };

    // case 1: mouse event
    auto result1 = OH_ArkUI_PointerEvent_GetInteractionHand(&mouseEventWrapper, &hand);
    EXPECT_EQ(result1, ARKUI_ERROR_CODE_NO_ERROR);

    // case 2: axis event
    auto result2 = OH_ArkUI_PointerEvent_GetInteractionHand(&axisEventWrapper, &hand);
    EXPECT_EQ(result2, ARKUI_ERROR_CODE_NO_ERROR);

    // case 3: key event
    auto result3 = OH_ArkUI_PointerEvent_GetInteractionHand(&keyEventWrapper, &hand);
    EXPECT_EQ(result3, ARKUI_ERROR_CODE_NO_ERROR);

    // case 4: hover event
    auto result4 = OH_ArkUI_PointerEvent_GetInteractionHand(&hoverEventWrapper, &hand);
    EXPECT_EQ(result4, ARKUI_ERROR_CODE_NO_ERROR);
}

} // namespace OHOS::Ace