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
constexpr float TEST_PRESSURE = 0.5f;
constexpr float TEST_PRESSURE_2 = 0.7f;
} // namespace

namespace OHOS::Ace {

namespace {
struct GetPressureTestInputType {
    explicit GetPressureTestInputType(const ArkUI_UIInputEvent event, uint32_t pointerIndex = 0)
        : event(event), pointerIndex(pointerIndex) {};
    ArkUI_UIInputEvent event;
    uint32_t pointerIndex;
};
} // namespace

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPressure001
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetPressure function with null event.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPressure001, TestSize.Level0)
{
    auto result = OH_ArkUI_PointerEvent_GetPressure(nullptr, 0);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPressure101
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetPressure function with touch event.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPressure101, TestSize.Level0)
{
    ArkUITouchEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_TOUCH_EVENT_ID;

    ArkUITouchPoint points[2];
    points[0].pressure = TEST_PRESSURE;
    points[1].pressure = TEST_PRESSURE_2;
    inputEvent.touchPointes = &points[0];
    inputEvent.touchPointSize = 2;

    ArkUITouchEvent inputEventEmpty;
    inputEventEmpty.touchPointes = nullptr;
    inputEventEmpty.touchPointSize = 0;

    std::vector<std::pair<GetPressureTestInputType, float>> testCases = {
        // case 1: null touch event
        { GetPressureTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0),
            0.0f },
        // case 2: invalid pointer index (negative)
        { GetPressureTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, -1),
            TEST_PRESSURE_2 },
        // case 3: invalid pointer index (out of range)
        { GetPressureTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 2),
            TEST_PRESSURE_2 },
        // case 4: empty touch points
        { GetPressureTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEventEmpty }, 0),
            0.0f },
        // case 5: valid pointer index 0
        { GetPressureTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 0),
            TEST_PRESSURE_2 },
        // case 6: valid pointer index 1
        { GetPressureTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 1),
            TEST_PRESSURE_2 },
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& testCase = testCases[i];
        auto result = OH_ArkUI_PointerEvent_GetPressure(&testCase.first.event, testCase.first.pointerIndex);
        EXPECT_FLOAT_EQ(result, testCase.second) << "Test case " << i + 1 << " failed";
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPressure102
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetPressure function with mouse event.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPressure102, TestSize.Level0)
{
    ArkUIMouseEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_MOUSE_EVENT_ID;
    inputEvent.actionTouchPoint.pressure = TEST_PRESSURE;

    ArkUIMouseEvent inputEventEmpty;
    inputEventEmpty.actionTouchPoint.pressure = 0.0f;

    std::vector<std::pair<GetPressureTestInputType, float>> testCases = {
        // case 1: null mouse event
        { GetPressureTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0),
            0.0f },
        // case 2: invalid pointer index (non-zero)
        { GetPressureTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 1),
            TEST_PRESSURE },
        // case 3: valid case with index 0
        { GetPressureTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 0),
            TEST_PRESSURE },
        // case 4: empty mouse event
        { GetPressureTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEventEmpty }, 0),
            0.0f },
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& testCase = testCases[i];
        auto result = OH_ArkUI_PointerEvent_GetPressure(&testCase.first.event, testCase.first.pointerIndex);
        EXPECT_FLOAT_EQ(result, testCase.second) << "Test case " << i + 1 << " failed";
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPressure103
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetPressure function with click event.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPressure103, TestSize.Level0)
{
    ArkUIClickEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_CLICK_EVENT_ID;
    inputEvent.pressure = TEST_PRESSURE;

    ArkUIClickEvent inputEventEmpty;
    inputEventEmpty.pressure = 0.0f;

    std::vector<std::pair<GetPressureTestInputType, float>> testCases = {
        // case 1: null click event
        { GetPressureTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0),
            0.0f },
        // case 2: invalid pointer index (non-zero)
        { GetPressureTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 1),
            TEST_PRESSURE },
        // case 3: valid case with index 0
        { GetPressureTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 0),
            TEST_PRESSURE },
        // case 4: empty click event
        { GetPressureTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEventEmpty }, 0),
            0.0f },
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& testCase = testCases[i];
        auto result = OH_ArkUI_PointerEvent_GetPressure(&testCase.first.event, testCase.first.pointerIndex);
        EXPECT_FLOAT_EQ(result, testCase.second) << "Test case " << i + 1 << " failed";
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPressure104
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetPressure function with unsupported event types.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPressure104, TestSize.Level0)
{
    std::vector<ArkUIEventTypeId> unsupportedTypeIds = { C_AXIS_EVENT_ID, C_KEY_EVENT_ID, C_FOCUS_AXIS_EVENT_ID,
        C_HOVER_EVENT_ID };

    uint32_t pointerIndex = 0;
    for (size_t i = 0; i < unsupportedTypeIds.size(); ++i) {
        auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, unsupportedTypeIds[i], nullptr };
        auto result = OH_ArkUI_PointerEvent_GetPressure(&uiInputEvent, pointerIndex);
        EXPECT_FLOAT_EQ(result, 0.0f) << "Unsupported type test " << i + 1 << " failed";
    }
}

} // namespace OHOS::Ace