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
namespace OHOS::Ace {

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetSourceType001
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetSourceType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetSourceType001, TestSize.Level0)
{
    /**
     * @tc.steps: step1.call functions and return expected results.
     */
    auto result = OH_ArkUI_UIInputEvent_GetSourceType(nullptr);
    EXPECT_EQ(result, static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN));
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetSourceType101
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetSourceType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetSourceType101, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 1 ArkUITouchEvent {C_TOUCH_EVENT_ID, HandleCTouchEvent}
    ArkUITouchEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_TOUCH_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, int32_t>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr },
            static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::NONE) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::MOUSE) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::TOUCH) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::TOUCH_PAD) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::KEYBOARD) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::JOYSTICK) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::CROWN) },
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        inputEvent.sourceType = expect;
        auto result = OH_ArkUI_UIInputEvent_GetSourceType(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetSourceType102
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetSourceType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetSourceType102, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 2 ArkUIMouseEvent HandleCMouseEventSourceType
    ArkUIMouseEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_MOUSE_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, int32_t>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr },
            static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::NONE) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::MOUSE) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::TOUCH) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::TOUCH_PAD) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::KEYBOARD) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::JOYSTICK) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::CROWN) },
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        inputEvent.sourceType = expect;
        auto result = OH_ArkUI_UIInputEvent_GetSourceType(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetSourceType103
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetSourceType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetSourceType103, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 3 ArkUIAxisEvent HandleCAxisEventSourceType
    ArkUIAxisEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_AXIS_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, int32_t>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr },
            static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::NONE) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::MOUSE) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::TOUCH) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::TOUCH_PAD) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::KEYBOARD) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::JOYSTICK) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::CROWN) },
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        inputEvent.sourceType = expect;
        auto result = OH_ArkUI_UIInputEvent_GetSourceType(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetSourceType104
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetSourceType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetSourceType104, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 4 ArkUIFocusAxisEvent HandleCFocusAxisEventSourceType
    ArkUIFocusAxisEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_FOCUS_AXIS_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, int32_t>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr },
            static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::NONE) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::MOUSE) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::TOUCH) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::TOUCH_PAD) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::KEYBOARD) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::JOYSTICK) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::CROWN) },
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        inputEvent.sourceType = expect;
        auto result = OH_ArkUI_UIInputEvent_GetSourceType(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetSourceType105
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetSourceType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetSourceType105, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 5 ArkUIHoverEvent HandleCHoverEventSourceType
    ArkUIHoverEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_HOVER_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, int32_t>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr },
            static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::NONE) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::MOUSE) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::TOUCH) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::TOUCH_PAD) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::KEYBOARD) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::JOYSTICK) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::CROWN) },
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        inputEvent.sourceType = expect;
        auto result = OH_ArkUI_UIInputEvent_GetSourceType(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetSourceType106
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetSourceType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetSourceType106, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 6 ArkUIClickEvent HandleCClickEventSourceType
    ArkUIClickEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_CLICK_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, int32_t>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr },
            static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::NONE) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::MOUSE) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::TOUCH) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::TOUCH_PAD) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::KEYBOARD) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::JOYSTICK) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::CROWN) },
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        inputEvent.sourceType = expect;
        auto result = OH_ArkUI_UIInputEvent_GetSourceType(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetSourceType107
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetSourceType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetSourceType107, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 7 OHOS::Ace::AxisEvent HandleAxisEventSourceType
    OHOS::Ace::AxisEvent inputEvent;
    ArkUIEventTypeId eventTypeId = AXIS_EVENT_ID;

    std::vector<std::pair<ArkUI_UIInputEvent, int32_t>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr },
            static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::NONE) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::MOUSE) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::TOUCH) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::TOUCH_PAD) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::KEYBOARD) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::JOYSTICK) },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent },
            static_cast<int32_t>(SourceType::CROWN) },
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        inputEvent.sourceType = static_cast<SourceType>(expect);
        auto result = OH_ArkUI_UIInputEvent_GetSourceType(&input);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetSourceType108
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetSourceType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetSourceType108, TestSize.Level0)
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
        auto result = OH_ArkUI_UIInputEvent_GetSourceType(&uiInputEvent);
        EXPECT_EQ(result, static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN)) << "other index = " << count;
        count++;
    }
}

} // namespace OHOS::Ace