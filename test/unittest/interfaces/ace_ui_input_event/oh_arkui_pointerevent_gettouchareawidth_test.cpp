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
constexpr float TOUCH_AREA_WIDTH = 10.0f;
} // namespace

namespace OHOS::Ace {

namespace {
struct GetTOUCH_AREA_WIDTHTestInputType {
    explicit GetTOUCH_AREA_WIDTHTestInputType(const ArkUI_UIInputEvent event, uint32_t pointerIndex = 0)
        : event(event), pointerIndex(pointerIndex) {};
    ArkUI_UIInputEvent event;
    uint32_t pointerIndex;
};
} // namespace

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetTOUCH_AREA_WIDTH001
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetTOUCH_AREA_WIDTH function with null event.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetTOUCH_AREA_WIDTH001, TestSize.Level0)
{
    auto result = OH_ArkUI_PointerEvent_GetTouchAreaWidth(nullptr, 0);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetTOUCH_AREA_WIDTH101
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetTOUCH_AREA_WIDTH function with touch event.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetTOUCH_AREA_WIDTH101, TestSize.Level0)
{
    ArkUITouchEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_TOUCH_EVENT_ID;

    ArkUITouchPoint points[2];
    points[0].contactAreaWidth = TOUCH_AREA_WIDTH;
    points[1].contactAreaWidth = TOUCH_AREA_WIDTH + 5.0f;
    inputEvent.touchPointes = &points[0];
    inputEvent.touchPointSize = 2;

    ArkUITouchEvent inputEventEmpty;

    std::vector<std::pair<GetTOUCH_AREA_WIDTHTestInputType, float>> testCases = {
        // case 1: null touch event
        { GetTOUCH_AREA_WIDTHTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0),
            0.0f },
        // case 2: empty touch points
        { GetTOUCH_AREA_WIDTHTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEventEmpty }, 0),
            0.0f },
        // case 3: valid case (returns last point's width regardless of index)
        { GetTOUCH_AREA_WIDTHTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 0),
            TOUCH_AREA_WIDTH + 5.0f },
        { GetTOUCH_AREA_WIDTHTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 1),
            TOUCH_AREA_WIDTH + 5.0f },
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& testCase = testCases[i];
        auto result = OH_ArkUI_PointerEvent_GetTouchAreaWidth(&testCase.first.event, testCase.first.pointerIndex);
        EXPECT_FLOAT_EQ(result, testCase.second) << "Test case " << i << " failed";
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetTOUCH_AREA_WIDTH102
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetTOUCH_AREA_WIDTH function with unsupported event types.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetTOUCH_AREA_WIDTH102, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent;
    ArkUIAxisEvent axisEvent;

    std::vector<std::pair<ArkUI_UIInputEvent, ArkUIEventTypeId>> testCases = {
        // case 1: mouse event
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, &mouseEvent }, C_MOUSE_EVENT_ID },
        // case 2: axis event
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &axisEvent }, C_AXIS_EVENT_ID },
        // case 3: key event
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_KEY_EVENT_ID, nullptr }, C_KEY_EVENT_ID },
        // case 4: hover event
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_HOVER_EVENT_ID, nullptr }, C_HOVER_EVENT_ID },
    };

    uint32_t pointerIndex = 0;
    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& testCase = testCases[i];
        auto result = OH_ArkUI_PointerEvent_GetTouchAreaWidth(&testCase.first, pointerIndex);
        EXPECT_EQ(result, 0.0f) << "Unsupported type test " << i << " failed";
    }
}

} // namespace OHOS::Ace