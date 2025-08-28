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

// defined in  ace_engine/interfaces/native/node/event_converter.cpp
namespace {
constexpr int32_t ORIGIN_INPUT_EVENT_TOOL_TYPE_UNKNOW = -1;
constexpr int32_t ORIGIN_INPUT_EVENT_TOOL_TYPE_FINGER = 1;
constexpr int32_t ORIGIN_INPUT_EVENT_TOOL_TYPE_PEN = 2;
constexpr int32_t ORIGIN_INPUT_EVENT_TOOL_TYPE_MOUSE = 7;
constexpr int32_t ORIGIN_INPUT_EVENT_TOOL_TYPE_TOUCHPAD = 9;
constexpr int32_t ORIGIN_INPUT_EVENT_TOOL_TYPE_JOYSTICK = 10;
} // namespace

namespace OHOS::Ace {

namespace {
struct GetToolTypeTestInputType {
    explicit GetToolTypeTestInputType(const ArkUI_UIInputEvent event, ArkUI_Int32 originType = 0)
        : event(event), originType(originType)
        {};
    ArkUI_UIInputEvent event;
    ArkUI_Int32 originType;
};
} // namespace

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetToolType001
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetToolType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetToolType001, TestSize.Level0)
{
    /**
     * @tc.steps: step1.call functions and return expected results.
     */
    auto result = OH_ArkUI_UIInputEvent_GetToolType(nullptr);
    EXPECT_EQ(result, static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN));
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetToolType101
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetToolType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetToolType101, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 1 ArkUITouchEvent HandleCTouchEventToolType
    ArkUITouchEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_TOUCH_EVENT_ID;

    std::vector<std::pair<GetToolTypeTestInputType, int32_t>> testCases = {
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_UNKNOW),
                UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_UNKNOW),
                UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_FINGER),
                UI_INPUT_EVENT_TOOL_TYPE_FINGER },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_PEN),
                UI_INPUT_EVENT_TOOL_TYPE_PEN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_MOUSE),
                UI_INPUT_EVENT_TOOL_TYPE_MOUSE },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_TOUCHPAD),
                UI_INPUT_EVENT_TOOL_TYPE_TOUCHPAD },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_JOYSTICK),
                UI_INPUT_EVENT_TOOL_TYPE_JOYSTICK }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;

        auto* touchEvent = reinterpret_cast<ArkUITouchEvent*>(input.event.inputEvent);
        if (touchEvent) {
            touchEvent->actionTouchPoint.toolType = input.originType;
        }
        auto result = OH_ArkUI_UIInputEvent_GetToolType(&input.event);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetToolType102
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetToolType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetToolType102, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 2 ArkUIMouseEvent HandleCMouseEventToolType
    ArkUIMouseEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_MOUSE_EVENT_ID;

    std::vector<std::pair<GetToolTypeTestInputType, int32_t>> testCases = {
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_UNKNOW),
                UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_UNKNOW),
                UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_FINGER),
                UI_INPUT_EVENT_TOOL_TYPE_FINGER },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_PEN),
                UI_INPUT_EVENT_TOOL_TYPE_PEN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_MOUSE),
                UI_INPUT_EVENT_TOOL_TYPE_MOUSE },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_TOUCHPAD),
                UI_INPUT_EVENT_TOOL_TYPE_TOUCHPAD },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_JOYSTICK),
                UI_INPUT_EVENT_TOOL_TYPE_JOYSTICK }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;

        auto* touchEvent = reinterpret_cast<ArkUIMouseEvent*>(input.event.inputEvent);
        if (touchEvent) {
            touchEvent->actionTouchPoint.toolType = input.originType;
        }
        auto result = OH_ArkUI_UIInputEvent_GetToolType(&input.event);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetToolType103
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetToolType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetToolType103, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 3 ArkUIAxisEvent HandleCAxisEventToolType
    ArkUIAxisEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_AXIS_EVENT_ID;

    std::vector<std::pair<GetToolTypeTestInputType, int32_t>> testCases = {
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_UNKNOW),
                UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_UNKNOW),
                UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_FINGER),
                UI_INPUT_EVENT_TOOL_TYPE_FINGER },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_PEN),
                UI_INPUT_EVENT_TOOL_TYPE_PEN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_MOUSE),
                UI_INPUT_EVENT_TOOL_TYPE_MOUSE },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_TOUCHPAD),
                UI_INPUT_EVENT_TOOL_TYPE_TOUCHPAD },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_JOYSTICK),
                UI_INPUT_EVENT_TOOL_TYPE_JOYSTICK }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;

        auto* touchEvent = reinterpret_cast<ArkUIAxisEvent*>(input.event.inputEvent);
        if (touchEvent) {
            touchEvent->actionTouchPoint.toolType = input.originType;
        }
        auto result = OH_ArkUI_UIInputEvent_GetToolType(&input.event);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetToolType104
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetToolType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetToolType104, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 4 ArkUIFocusAxisEvent HandleCFocusAxisEventToolType
    ArkUIFocusAxisEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_FOCUS_AXIS_EVENT_ID;

    std::vector<std::pair<GetToolTypeTestInputType, int32_t>> testCases = {
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_UNKNOW),
                UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_UNKNOW),
                UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_FINGER),
                UI_INPUT_EVENT_TOOL_TYPE_FINGER },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_PEN),
                UI_INPUT_EVENT_TOOL_TYPE_PEN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_MOUSE),
                UI_INPUT_EVENT_TOOL_TYPE_MOUSE },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_TOUCHPAD),
                UI_INPUT_EVENT_TOOL_TYPE_TOUCHPAD },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_JOYSTICK),
                UI_INPUT_EVENT_TOOL_TYPE_JOYSTICK }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;

        auto* touchEvent = reinterpret_cast<ArkUIFocusAxisEvent*>(input.event.inputEvent);
        if (touchEvent) {
            touchEvent->toolType = input.originType;
        }
        auto result = OH_ArkUI_UIInputEvent_GetToolType(&input.event);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetToolType105
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetToolType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetToolType105, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 5 ArkUIHoverEvent HandleCHoverEventToolType
    ArkUIHoverEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_HOVER_EVENT_ID;

    std::vector<std::pair<GetToolTypeTestInputType, int32_t>> testCases = {
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_UNKNOW),
                UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_UNKNOW),
                UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_FINGER),
                UI_INPUT_EVENT_TOOL_TYPE_FINGER },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_PEN),
                UI_INPUT_EVENT_TOOL_TYPE_PEN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_MOUSE),
                UI_INPUT_EVENT_TOOL_TYPE_MOUSE },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_TOUCHPAD),
                UI_INPUT_EVENT_TOOL_TYPE_TOUCHPAD },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_JOYSTICK),
                UI_INPUT_EVENT_TOOL_TYPE_JOYSTICK }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;

        auto* touchEvent = reinterpret_cast<ArkUIHoverEvent*>(input.event.inputEvent);
        if (touchEvent) {
            touchEvent->toolType = input.originType;
        }
        auto result = OH_ArkUI_UIInputEvent_GetToolType(&input.event);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetToolType106
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetToolType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetToolType106, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 6 ArkUIClickEvent HandleCClickEventToolType
    ArkUIClickEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_CLICK_EVENT_ID;

    std::vector<std::pair<GetToolTypeTestInputType, int32_t>> testCases = {
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_UNKNOW),
                UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_UNKNOW),
                UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_FINGER),
                UI_INPUT_EVENT_TOOL_TYPE_FINGER },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_PEN),
                UI_INPUT_EVENT_TOOL_TYPE_PEN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_MOUSE),
                UI_INPUT_EVENT_TOOL_TYPE_MOUSE },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_TOUCHPAD),
                UI_INPUT_EVENT_TOOL_TYPE_TOUCHPAD },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_JOYSTICK),
                UI_INPUT_EVENT_TOOL_TYPE_JOYSTICK }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;

        auto* touchEvent = reinterpret_cast<ArkUIClickEvent*>(input.event.inputEvent);
        if (touchEvent) {
            touchEvent->toolType = input.originType;
        }
        auto result = OH_ArkUI_UIInputEvent_GetToolType(&input.event);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetToolType107
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetToolType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetToolType107, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 7 OHOS::Ace::AxisEvent HandleAxisEventToolType
    OHOS::Ace::AxisEvent inputEvent;
    ArkUIEventTypeId eventTypeId = AXIS_EVENT_ID;

    std::vector<std::pair<GetToolTypeTestInputType, int32_t>> testCases = {
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_UNKNOW),
                UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_UNKNOW),
                UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_FINGER),
                UI_INPUT_EVENT_TOOL_TYPE_FINGER },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_PEN),
                UI_INPUT_EVENT_TOOL_TYPE_PEN },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_MOUSE),
                UI_INPUT_EVENT_TOOL_TYPE_MOUSE },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_TOUCHPAD),
                UI_INPUT_EVENT_TOOL_TYPE_TOUCHPAD },
        { GetToolTypeTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent},
                ORIGIN_INPUT_EVENT_TOOL_TYPE_JOYSTICK),
                UI_INPUT_EVENT_TOOL_TYPE_JOYSTICK }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;

        auto* touchEvent = reinterpret_cast<OHOS::Ace::AxisEvent*>(input.event.inputEvent);
        if (touchEvent) {
            touchEvent->sourceTool = static_cast<SourceTool>(input.originType);
        }
        auto result = OH_ArkUI_UIInputEvent_GetToolType(&input.event);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetToolType108
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetToolType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetToolType108, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 2 Other ArkUIEventTypeId
    std::vector<ArkUIEventTypeId> typeIds = {
        TOUCH_EVENT_ID,
        C_KEY_EVENT_ID
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto typeId : typeIds) {
        auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, typeId, nullptr };
        auto result = OH_ArkUI_UIInputEvent_GetToolType(&uiInputEvent);
        EXPECT_EQ(result, static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN)) << "other index = " << count;
        count++;
    }
}

} // namespace OHOS::Ace