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
constexpr uint32_t ARKUI_HISTORY_POINTER_COUNT = 2;
constexpr uint32_t ARKUI_HISTORY_SIZE = 3;
} // namespace

namespace OHOS::Ace {

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryPointerCount001
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetHistoryPointerCount function with null event.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryPointerCount001, TestSize.Level0)
{
    auto result = OH_ArkUI_PointerEvent_GetHistoryPointerCount(nullptr, 0);
    EXPECT_EQ(result, 0u);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryPointerCount101
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetHistoryPointerCount function with touch event.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryPointerCount101, TestSize.Level0)
{
    ArkUITouchEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_TOUCH_EVENT_ID;

    // Setup valid history events with different pointer counts
    ArkUIHistoryTouchEvent historyEvents[ARKUI_HISTORY_SIZE];
    historyEvents[0].touchPointSize = ARKUI_HISTORY_POINTER_COUNT;
    historyEvents[1].touchPointSize = ARKUI_HISTORY_POINTER_COUNT + 1;
    historyEvents[2].touchPointSize = ARKUI_HISTORY_POINTER_COUNT + 2;
    inputEvent.historyEvents = historyEvents;
    inputEvent.historySize = ARKUI_HISTORY_SIZE;

    ArkUITouchEvent nullHistoryEvent;
    nullHistoryEvent.historyEvents = nullptr;
    nullHistoryEvent.historySize = ARKUI_HISTORY_SIZE;

    ArkUITouchEvent emptyEvent;

    std::vector<std::tuple<ArkUI_UIInputEvent, uint32_t, uint32_t>> testCases = {
        // case 1: null touch event
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0, 0 },
        // case 2: null history events
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &nullHistoryEvent }, 0, 0 },
        // case 3: empty touch event
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &emptyEvent }, 0, 0 },
        // case 4: invalid history index (negative)
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, -1, 0 },
        // case 5: invalid history index (out of range)
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, ARKUI_HISTORY_SIZE, 0 },
        // case 6: valid history index 0
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 0,
            ARKUI_HISTORY_POINTER_COUNT },
        // case 7: valid history index 1
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 1,
            ARKUI_HISTORY_POINTER_COUNT + 1 },
        // case 8: valid history index 2
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, 2,
            ARKUI_HISTORY_POINTER_COUNT + 2 },
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& testCase = testCases[i];
        auto result = OH_ArkUI_PointerEvent_GetHistoryPointerCount(&std::get<0>(testCase), std::get<1>(testCase));
        EXPECT_EQ(result, std::get<2>(testCase)) << "Test case " << i << " failed";
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryPointerCount102
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetHistoryPointerCount function with unsupported event types.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryPointerCount102, TestSize.Level0)
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

    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& testCase = testCases[i];
        auto result = OH_ArkUI_PointerEvent_GetHistoryPointerCount(&testCase.first, 0);
        EXPECT_EQ(result, 0u) << "Unsupported type test " << i << " failed";
    }
}

} // namespace OHOS::Ace