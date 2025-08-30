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

#include <cstdint>

#include "../ui_input_event_test.h"
#include "arkoala_api.h"
#include "gtest/gtest.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
namespace {
constexpr float HISTORY_X_ERROR = 0.0f;
constexpr float ARKUI_X = 1234.0f;
constexpr int32_t EVENT_SIZE = 2;
constexpr int32_t POINT_SIZE = 2;

struct HistoryTestInputType {
    HistoryTestInputType(const ArkUI_UIInputEvent event, uint32_t pointerIndex, uint32_t historyIndex,
        ArkUIHistoryTouchEvent* events = nullptr, uint32_t historySize = 0)
        : event(event), pointerIndex(pointerIndex), historyIndex(historyIndex), historyEvents(events),
          historySize(historySize) {};
    ArkUI_UIInputEvent event;
    uint32_t pointerIndex;
    uint32_t historyIndex;
    ArkUIHistoryTouchEvent* historyEvents = nullptr;
    uint32_t historySize = 0;
};
} // namespace

HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryWindowX_001, TestSize.Level0)
{
    auto result = OH_ArkUI_PointerEvent_GetHistoryWindowX(nullptr, 0, 0);
    EXPECT_FLOAT_EQ(result, HISTORY_X_ERROR);
}

HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryWindowX_002, TestSize.Level0)
{
    ArkUITouchEvent touchEvent;
    int32_t pointerIndex = 1;
    int32_t historyIndex = 1;
    ArkUIAxisEvent axisEvent;
    ArkUINodeEvent nodeEvent;
    std::vector<std::pair<HistoryTestInputType, float>> testCases = {
        { HistoryTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, &axisEvent },
              pointerIndex, historyIndex),
            HISTORY_X_ERROR },
        { HistoryTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, TOUCH_EVENT_ID, &touchEvent },
              pointerIndex, historyIndex),
            HISTORY_X_ERROR },
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, &nodeEvent.mouseEvent },
              pointerIndex, historyIndex),
            HISTORY_X_ERROR },
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &nodeEvent.axisEvent },
              pointerIndex, historyIndex),
            HISTORY_X_ERROR },
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_KEY_EVENT_ID, &nodeEvent.keyEvent }, pointerIndex,
              historyIndex),
            HISTORY_X_ERROR },
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_FOCUS_AXIS_EVENT_ID, &nodeEvent.focusAxisEvent },
              pointerIndex, historyIndex),
            HISTORY_X_ERROR },
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_CLICK_EVENT_ID, &nodeEvent.clickEvent },
              pointerIndex, historyIndex),
            HISTORY_X_ERROR },
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_HOVER_EVENT_ID, &nodeEvent.hoverEvent },
              pointerIndex, historyIndex),
            HISTORY_X_ERROR },
    };

    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        auto result = OH_ArkUI_PointerEvent_GetHistoryWindowX(&input.event, input.pointerIndex, input.historyIndex);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryWindowX_003, TestSize.Level0)
{
    ArkUIHistoryTouchEvent events[EVENT_SIZE];
    ArkUIHistoryTouchEvent emptyEvents[EVENT_SIZE];
    ArkUITouchPoint pointes[POINT_SIZE];
    pointes[0].windowX = ARKUI_X;
    pointes[1].windowX = ARKUI_X;
    events[0].touchPointSize = POINT_SIZE;
    events[1].touchPointSize = POINT_SIZE;
    events[0].touchPointes = pointes;
    events[1].touchPointes = pointes;
    emptyEvents[0].touchPointSize = POINT_SIZE;
    emptyEvents[1].touchPointSize = POINT_SIZE;
    ArkUINodeEvent nodeEvent;
    std::vector<std::pair<HistoryTestInputType, float>> testCases = {
        { HistoryTestInputType(ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, nullptr }, 0, 0),
            HISTORY_X_ERROR }, // test when touchEvent is nullptr
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, -1, 0),
            HISTORY_X_ERROR }, // test when historyIndex < 0
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, 10, 0),
            HISTORY_X_ERROR }, // test when historyIndex > touchEvent->historySize
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, 2, 0),
            HISTORY_X_ERROR }, // test when historyIndex = touchEvent->historySize

        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, 1, 0),
            HISTORY_X_ERROR }, // test when touchEvent->historyEvents = nullptr
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, 1, -1,
              emptyEvents, EVENT_SIZE),
            HISTORY_X_ERROR }, // test when pointerIndex < 0
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, 1, 10,
              emptyEvents, EVENT_SIZE),
            HISTORY_X_ERROR }, // test when pointerIndex > touchEvent->historyEvents[historyIndex].touchPointSize
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, 1, 2,
              emptyEvents, EVENT_SIZE),
            HISTORY_X_ERROR }, // test when pointerIndex = touchEvent->historyEvents[historyIndex].touchPointSize
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, 1, 1,
              emptyEvents, EVENT_SIZE),
            HISTORY_X_ERROR }, // test when (touchEvent->historyEvents[historyIndex].touchPointes) = nullptr
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, 1, 1,
              events, EVENT_SIZE),
            ARKUI_X }, // test when valid input with pointerIndex valid
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, 1, 0,
              emptyEvents, EVENT_SIZE),
            HISTORY_X_ERROR }, // test when pointerIndex = Lower boundary,
                               // (touchEvent->historyEvents[historyIndex].touchPointes) = nullptr
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, 1, 0,
              events, EVENT_SIZE),
            ARKUI_X }, // test when valid input with pointerIndex = Lower boundary

        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, 0, 0),
            HISTORY_X_ERROR }, // test when historyIndex = Lower boundary, touchEvent->historyEvents = nullptr
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, 0, -1,
              emptyEvents, EVENT_SIZE),
            HISTORY_X_ERROR }, // test when historyIndex = Lower boundary, pointerIndex < 0
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, 0, 10,
              emptyEvents, EVENT_SIZE),
            HISTORY_X_ERROR }, // test when historyIndex = Lower boundary, pointerIndex >
                               // touchEvent->historyEvents[historyIndex].touchPointSize
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, 0, 2,
              emptyEvents, EVENT_SIZE),
            HISTORY_X_ERROR }, // test when historyIndex = Lower boundary, pointerIndex =
                               // touchEvent->historyEvents[historyIndex].touchPointSize
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, 0, 1,
              emptyEvents, EVENT_SIZE),
            HISTORY_X_ERROR }, // test when historyIndex = Lower boundary,
                               // (touchEvent->historyEvents[historyIndex].touchPointes) = nullptr
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, 0, 1,
              events, EVENT_SIZE),
            ARKUI_X }, // test when historyIndex = Lower boundary, input valid
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, 0, 0,
              emptyEvents, EVENT_SIZE),
            HISTORY_X_ERROR }, // test when historyIndex = Lower boundary, pointerIndex = Lower boundary,
                               // (touchEvent->historyEvents[historyIndex].touchPointes) = nullptr
        { HistoryTestInputType(
              ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &nodeEvent.touchEvent }, 0, 0,
              events, EVENT_SIZE),
            ARKUI_X }, // test when historyIndex = Lower boundary, pointerIndex = Lower boundary, input valid
    };

    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(input.event.inputEvent);
        if (touchEvent) {
            touchEvent->historyEvents = input.historyEvents;
            touchEvent->historySize = input.historySize;
        }
        auto expect = testCase.second;
        auto result = OH_ArkUI_PointerEvent_GetHistoryWindowX(&input.event, input.pointerIndex, input.historyIndex);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}
} // namespace OHOS::Ace