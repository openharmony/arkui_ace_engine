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
constexpr float ARKUI_EVENT_Y = 1.0;
} // namespace

namespace OHOS::Ace {

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayY001
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetDisplayY function with null input.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayY001, TestSize.Level0)
{
    auto result = OH_ArkUI_PointerEvent_GetDisplayY(nullptr);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayY002
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetDisplayY function with C_TOUCH_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayY002, TestSize.Level0)
{
    ArkUITouchEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_TOUCH_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0.0f },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, ARKUI_EVENT_Y - 1 }
    };

    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;

        auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(input.inputEvent);
        if (touchEvent) {
            touchEvent->actionTouchPoint.nodeY = expect;
        }

        auto result = OH_ArkUI_PointerEvent_GetDisplayY(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayY003
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetDisplayY function with C_MOUSE_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayY003, TestSize.Level0)
{
    ArkUIMouseEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_MOUSE_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0.0f },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, ARKUI_EVENT_Y - 1 }
    };

    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;

        auto* mouseEvent = reinterpret_cast<ArkUIMouseEvent*>(input.inputEvent);
        if (mouseEvent) {
            mouseEvent->actionTouchPoint.nodeY = expect;
        }

        auto result = OH_ArkUI_PointerEvent_GetDisplayY(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayY004
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetDisplayY function with C_AXIS_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayY004, TestSize.Level0)
{
    ArkUIAxisEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_AXIS_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0.0f },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, ARKUI_EVENT_Y - 1 }
    };

    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;

        auto* axisEvent = reinterpret_cast<ArkUIAxisEvent*>(input.inputEvent);
        if (axisEvent) {
            axisEvent->actionTouchPoint.nodeY = expect;
        }

        auto result = OH_ArkUI_PointerEvent_GetDisplayY(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayY005
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetDisplayY function with C_CLICK_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayY005, TestSize.Level0)
{
    ArkUIClickEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_CLICK_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0.0f },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, ARKUI_EVENT_Y - 1 }
    };

    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;

        auto* clickEvent = reinterpret_cast<ArkUIClickEvent*>(input.inputEvent);
        if (clickEvent) {
            clickEvent->localY = expect;
        }

        auto result = OH_ArkUI_PointerEvent_GetDisplayY(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayY006
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetDisplayY function with AXIS_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayY006, TestSize.Level0)
{
    OHOS::Ace::AxisEvent inputEvent;
    ArkUIEventTypeId eventTypeId = AXIS_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0.0f },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, ARKUI_EVENT_Y - 1 }
    };

    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;

        auto* axisEvent = reinterpret_cast<OHOS::Ace::AxisEvent*>(input.inputEvent);
        if (axisEvent) {
            axisEvent->localY = expect;
        }

        auto result = OH_ArkUI_PointerEvent_GetDisplayY(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayY007
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetDisplayY function with TOUCH_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayY007, TestSize.Level0)
{
    OHOS::Ace::TouchEvent inputEvent;
    ArkUIEventTypeId eventTypeId = TOUCH_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr }, 0.0f },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent }, ARKUI_EVENT_Y - 1 }
    };

    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;

        auto* touchEvent = reinterpret_cast<OHOS::Ace::TouchEvent*>(input.inputEvent);
        if (touchEvent) {
            touchEvent->localY = expect;
        }

        auto result = OH_ArkUI_PointerEvent_GetDisplayY(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayY008
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetDisplayY function with unsupported event types.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayY008, TestSize.Level0)
{
    std::vector<ArkUIEventTypeId> typeIds = { C_KEY_EVENT_ID, C_FOCUS_AXIS_EVENT_ID, C_HOVER_EVENT_ID };

    auto count = 0;
    for (auto typeId : typeIds) {
        auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, typeId, nullptr };
        auto result = OH_ArkUI_PointerEvent_GetDisplayY(&uiInputEvent);
        EXPECT_EQ(result, 0.0f) << "Unsupported event type index = " << count;
        count++;
    }
}
} // namespace OHOS::Ace