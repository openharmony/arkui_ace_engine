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
constexpr float ARKUI_DISPLAY_Y = 3.0f;
} // namespace

namespace OHOS::Ace {

namespace {
struct GetDisplayYByIndexTestInputType {
    explicit GetDisplayYByIndexTestInputType(const ArkUI_UIInputEvent event, uint32_t pointerIndex = 0)
        : event(event), pointerIndex(pointerIndex) {};
    ArkUI_UIInputEvent event;
    uint32_t pointerIndex;
};
} // namespace

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayYByIndex001
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetDisplayYByIndex function with null event.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayYByIndex001, TestSize.Level0)
{
    auto result = OH_ArkUI_PointerEvent_GetDisplayYByIndex(nullptr, 0);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayYByIndex101
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetDisplayYByIndex function with touch event.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayYByIndex101, TestSize.Level0)
{
    ArkUITouchEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_TOUCH_EVENT_ID;

    ArkUITouchPoint points[2];
    points[0].screenY = ARKUI_DISPLAY_Y;
    points[1].screenY = ARKUI_DISPLAY_Y + 1.0f;
    inputEvent.touchPointes = &points[0];
    inputEvent.touchPointSize = 2;

    ArkUITouchEvent inputEventEmpty;

    std::vector<std::pair<GetDisplayYByIndexTestInputType, float>> testCases = {
        // case 1: null touch event
        { GetDisplayYByIndexTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0),
            0.0f },
        // case 2: invalid pointer index (negative)
        { GetDisplayYByIndexTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, -1),
            0.0f },
        // case 3: invalid pointer index (out of range)
        { GetDisplayYByIndexTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 2),
            0.0f },
        // case 4: empty touch points
        { GetDisplayYByIndexTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEventEmpty }, 0),
            0.0f },
        // case 5: valid pointer index 0
        { GetDisplayYByIndexTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 0),
            ARKUI_DISPLAY_Y },
        // case 6: valid pointer index 1
        { GetDisplayYByIndexTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 1),
            ARKUI_DISPLAY_Y + 1.0f },
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& testCase = testCases[i];
        auto result = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&testCase.first.event, testCase.first.pointerIndex);
        EXPECT_FLOAT_EQ(result, testCase.second) << "Test case " << i << " failed";
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayYByIndex102
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetDisplayYByIndex function with mouse event.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayYByIndex102, TestSize.Level0)
{
    ArkUIMouseEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_MOUSE_EVENT_ID;
    inputEvent.actionTouchPoint.screenY = ARKUI_DISPLAY_Y;

    std::vector<std::pair<GetDisplayYByIndexTestInputType, float>> testCases = {
        // case 1: null mouse event
        { GetDisplayYByIndexTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0),
            0.0f },
        // case 2: invalid pointer index (non-zero)
        { GetDisplayYByIndexTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 1),
            0.0f },
        // case 3: valid case with index 0
        { GetDisplayYByIndexTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 0),
            ARKUI_DISPLAY_Y },
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& testCase = testCases[i];
        auto result = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&testCase.first.event, testCase.first.pointerIndex);
        EXPECT_FLOAT_EQ(result, testCase.second) << "Test case " << i << " failed";
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayYByIndex103
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetDisplayYByIndex function with axis event.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayYByIndex103, TestSize.Level0)
{
    ArkUIAxisEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_AXIS_EVENT_ID;
    inputEvent.actionTouchPoint.screenY = ARKUI_DISPLAY_Y;

    std::vector<std::pair<GetDisplayYByIndexTestInputType, float>> testCases = {
        // case 1: null axis event
        { GetDisplayYByIndexTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0),
            0.0f },
        // case 2: invalid pointer index (non-zero)
        { GetDisplayYByIndexTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 1),
            0.0f },
        // case 3: valid case with index 0
        { GetDisplayYByIndexTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 0),
            ARKUI_DISPLAY_Y },
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& testCase = testCases[i];
        auto result = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&testCase.first.event, testCase.first.pointerIndex);
        EXPECT_FLOAT_EQ(result, testCase.second) << "Test case " << i << " failed";
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayYByIndex104
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetDisplayYByIndex function with unsupported event types.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayYByIndex104, TestSize.Level0)
{
    std::vector<ArkUIEventTypeId> unsupportedTypeIds = { AXIS_EVENT_ID, TOUCH_EVENT_ID, C_KEY_EVENT_ID,
        C_FOCUS_AXIS_EVENT_ID, C_CLICK_EVENT_ID, C_HOVER_EVENT_ID };

    uint32_t pointerIndex = 0;
    for (size_t i = 0; i < unsupportedTypeIds.size(); ++i) {
        auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, unsupportedTypeIds[i], nullptr };
        auto result = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&uiInputEvent, pointerIndex);
        EXPECT_EQ(result, 0.0f) << "Unsupported type test " << i << " failed";
    }
}

} // namespace OHOS::Ace