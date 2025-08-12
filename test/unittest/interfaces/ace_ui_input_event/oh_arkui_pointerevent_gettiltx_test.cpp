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
constexpr float ARKUI_TILT_X = 15.0f;
constexpr float ARKUI_NEGATIVE_TILT_X = -30.0f;
constexpr float ARKUI_TILT_X_OVER_MAX = 95.0f;   // Over maximum valid value
constexpr float ARKUI_TILT_X_UNDER_MIN = -95.0f; // Under minimum valid value
} // namespace

namespace OHOS::Ace {

namespace {
struct GetTiltXTestInputType {
    explicit GetTiltXTestInputType(const ArkUI_UIInputEvent event, uint32_t pointerIndex = 0)
        : event(event), pointerIndex(pointerIndex) {};
    ArkUI_UIInputEvent event;
    uint32_t pointerIndex;
};
} // namespace

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetTiltX001
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetTiltX function with null event.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetTiltX001, TestSize.Level0)
{
    auto result = OH_ArkUI_PointerEvent_GetTiltX(nullptr, 0);
    EXPECT_EQ(result, 0.0f);
}
/**
 * @tc.name: OH_ArkUI_PointerEvent_GetTiltX101
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetTiltX function with touch event including negative values.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetTiltX101, TestSize.Level0)
{
    static ArkUITouchPoint points[3];
    points[0].tiltX = ARKUI_TILT_X;          // 15.0f
    points[1].tiltX = ARKUI_NEGATIVE_TILT_X; // -30.0f
    points[2].tiltX = ARKUI_TILT_X_OVER_MAX; // 95.0f

    static ArkUITouchEvent inputEvent;
    inputEvent.touchPointes = &points[0];
    inputEvent.touchPointSize = 3;

    static ArkUITouchEvent inputEventHover;
    inputEventHover.subKind = ON_HOVER_MOVE;
    inputEventHover.actionTouchPoint.tiltX = ARKUI_NEGATIVE_TILT_X; // -30.0f

    static ArkUITouchEvent inputEventNegative;
    inputEventNegative.touchPointes = &points[1];
    inputEventNegative.touchPointSize = 1;

    static ArkUITouchEvent inputEventEmpty;

    static ArkUITouchEvent inputEventUnderMin;
    static ArkUITouchPoint underMinPoint;
    underMinPoint.tiltX = ARKUI_TILT_X_UNDER_MIN; // -95.0f
    inputEventUnderMin.touchPointes = &underMinPoint;
    inputEventUnderMin.touchPointSize = 1;

    ArkUIEventTypeId eventTypeId = C_TOUCH_EVENT_ID;

    std::vector<std::pair<GetTiltXTestInputType, float>> testCases = {
        // case 1: null touch event
        { GetTiltXTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0),
            0.0f },
        // case 2: empty touch points
        { GetTiltXTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEventEmpty }, 0),
            0.0f },
        // case 3: hover move subkind with negative tilt
        { GetTiltXTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEventHover }, 0),
            ARKUI_NEGATIVE_TILT_X },
        // case 4: normal touch event with mixed values
        { GetTiltXTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 0),
            ARKUI_TILT_X_OVER_MAX },
        // case 5: touch event with only negative value
        { GetTiltXTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEventNegative }, 0),
            ARKUI_NEGATIVE_TILT_X },
        // case 6: value below minimum
        { GetTiltXTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEventUnderMin }, 0),
            ARKUI_TILT_X_UNDER_MIN },
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& testCase = testCases[i];
        auto result = OH_ArkUI_PointerEvent_GetTiltX(&testCase.first.event, testCase.first.pointerIndex);
        EXPECT_FLOAT_EQ(result, testCase.second) << "Test case " << i << " failed";
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetTiltX102
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetTiltX function with click event including negative values.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetTiltX102, TestSize.Level0)
{
    ArkUIClickEvent inputEvent;
    ArkUIClickEvent inputEventNegative;
    ArkUIClickEvent inputEventOverMax;
    ArkUIEventTypeId eventTypeId = C_CLICK_EVENT_ID;
    inputEvent.tiltX = ARKUI_TILT_X;
    inputEventNegative.tiltX = ARKUI_NEGATIVE_TILT_X;
    inputEventOverMax.tiltX = ARKUI_TILT_X_OVER_MAX;

    std::vector<std::pair<GetTiltXTestInputType, float>> testCases = {
        // case 1: null click event
        { GetTiltXTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0),
            0.0f },
        // case 2: valid click event with positive tilt
        { GetTiltXTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 0),
            ARKUI_TILT_X },
        // case 3: click event with negative tilt
        { GetTiltXTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEventNegative }, 0),
            ARKUI_NEGATIVE_TILT_X },
        // case 4: click event with tilt over maximum (should be clamped)
        { GetTiltXTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEventOverMax }, 0),
            ARKUI_TILT_X_OVER_MAX },
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& testCase = testCases[i];
        auto result = OH_ArkUI_PointerEvent_GetTiltX(&testCase.first.event, testCase.first.pointerIndex);
        EXPECT_FLOAT_EQ(result, testCase.second) << "Test case " << i << " failed";
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetTiltX103
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetTiltX function with hover event including negative values.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetTiltX103, TestSize.Level0)
{
    ArkUIHoverEvent inputEvent;
    ArkUIHoverEvent inputEventNegative;
    ArkUIHoverEvent inputEventUnderMin;
    ArkUIEventTypeId eventTypeId = C_HOVER_EVENT_ID;
    inputEvent.tiltX = ARKUI_TILT_X;
    inputEventNegative.tiltX = ARKUI_NEGATIVE_TILT_X;
    inputEventUnderMin.tiltX = ARKUI_TILT_X_UNDER_MIN;

    std::vector<std::pair<GetTiltXTestInputType, float>> testCases = {
        // case 1: null hover event
        { GetTiltXTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0),
            0.0f },
        // case 2: valid hover event with positive tilt
        { GetTiltXTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 0),
            ARKUI_TILT_X },
        // case 3: hover event with negative tilt
        { GetTiltXTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEventNegative }, 0),
            ARKUI_NEGATIVE_TILT_X },
        // case 4: hover event with tilt under minimum (should be clamped)
        { GetTiltXTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEventUnderMin }, 0),
            ARKUI_TILT_X_UNDER_MIN },
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& testCase = testCases[i];
        auto result = OH_ArkUI_PointerEvent_GetTiltX(&testCase.first.event, testCase.first.pointerIndex);
        EXPECT_FLOAT_EQ(result, testCase.second) << "Test case " << i << " failed";
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetTiltX104
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetTiltX function with unsupported event types.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetTiltX104, TestSize.Level0)
{
    std::vector<ArkUIEventTypeId> unsupportedTypeIds = { AXIS_EVENT_ID, C_MOUSE_EVENT_ID, C_KEY_EVENT_ID,
        C_FOCUS_AXIS_EVENT_ID };

    uint32_t pointerIndex = 0;
    for (size_t i = 0; i < unsupportedTypeIds.size(); ++i) {
        auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, unsupportedTypeIds[i], nullptr };
        auto result = OH_ArkUI_PointerEvent_GetTiltX(&uiInputEvent, pointerIndex);
        EXPECT_EQ(result, 0.0f) << "Unsupported type test " << i << " failed";
    }
}

} // namespace OHOS::Ace