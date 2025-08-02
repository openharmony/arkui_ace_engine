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
constexpr uint32_t ARKUI_HISTORY_SIZE = 5;
} // namespace

namespace OHOS::Ace {

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistorySize001
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetHistorySize function with null event.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistorySize001, TestSize.Level0)
{
    auto result = OH_ArkUI_PointerEvent_GetHistorySize(nullptr);
    EXPECT_EQ(result, 0u);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistorySize101
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetHistorySize function with touch event.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistorySize101, TestSize.Level0)
{
    ArkUITouchEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_TOUCH_EVENT_ID;

    ArkUIHistoryTouchEvent historyEvents[ARKUI_HISTORY_SIZE];
    inputEvent.historyEvents = historyEvents;
    inputEvent.historySize = ARKUI_HISTORY_SIZE;

    ArkUITouchEvent nullHistoryEvent;
    nullHistoryEvent.historyEvents = nullptr;
    nullHistoryEvent.historySize = ARKUI_HISTORY_SIZE;

    ArkUITouchEvent emptyEvent;

    std::vector<std::pair<ArkUI_UIInputEvent, uint32_t>> testCases = {
        // case 1: null touch event
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0 },
        // case 2: null history events
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &nullHistoryEvent }, 0 },
        // case 3: empty touch event
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &emptyEvent }, 0 },
        // case 4: valid history size
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, ARKUI_HISTORY_SIZE },
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& testCase = testCases[i];
        auto result = OH_ArkUI_PointerEvent_GetHistorySize(&testCase.first);
        EXPECT_EQ(result, testCase.second) << "Test case " << i << " failed";
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistorySize102
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetHistorySize function with unsupported event types.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistorySize102, TestSize.Level0)
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
        auto result = OH_ArkUI_PointerEvent_GetHistorySize(&testCase.first);
        EXPECT_EQ(result, 0u) << "Unsupported type test " << i << " failed";
    }
}

} // namespace OHOS::Ace