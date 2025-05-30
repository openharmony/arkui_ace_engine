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
#include "interfaces/native/native_key_event.h"
#include "interfaces/native/ui_input_event.h"

#include "core/components_ng/event/event_constants.h"
#include "frameworks/core/common/ace_application_info.h"

using namespace testing;
using namespace testing::ext;

// defined in  ace_engine/interfaces/native/node/event_converter.cpp
namespace {
constexpr int32_t ORIGIN_TOUCH_ACTION_DOWN = 0;
constexpr int32_t ORIGIN_TOUCH_ACTION_UP = 1;
constexpr int32_t ORIGIN_TOUCH_ACTION_MOVE = 2;
constexpr int32_t ORIGIN_TOUCH_ACTION_CANCEL = 3;
constexpr int32_t ORIGIN_INPUT_EVENT_TOOL_TYPE_FINGER = 1;
constexpr int32_t ORIGIN_INPUT_EVENT_TOOL_TYPE_PEN = 2;
constexpr int32_t ORIGIN_INPUT_EVENT_TOOL_TYPE_MOUSE = 7;
constexpr int32_t ORIGIN_INPUT_EVENT_TOOL_TYPE_TOUCHPAD = 9;
constexpr int32_t ORIGIN_INPUT_EVENT_TOOL_TYPE_JOYSTICK = 10;
constexpr int32_t ORIGIN_MOUSE_ACTION_PRESS = 1;
constexpr int32_t ORIGIN_MOUSE_ACTION_RELEASE = 2;
constexpr int32_t ORIGIN_MOUSE_ACTION_MOVE = 3;
constexpr int32_t ORIGIN_MOUSE_ACTION_CANCEL = 13;
constexpr int32_t ORIGIN_AXIS_ACTION_NONE = 0;
constexpr int32_t ORIGIN_AXIS_ACTION_BEGIN = 1;
constexpr int32_t ORIGIN_AXIS_ACTION_UPDATE = 2;
constexpr int32_t ORIGIN_AXIS_ACTION_END = 3;
constexpr int32_t ORIGIN_AXIS_ACTION_CANCEL = 4;
constexpr int32_t ARKUI_EVENT_ACTION_NULL = -1;

constexpr uint64_t ARKUI_EVENT_ARKUI_TIME = 20;
constexpr uint64_t ARKUI_EVENT_ARKUI_TIME_NULL = 0;
} // namespace

namespace OHOS::Ace {

HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetType001, TestSize.Level0)
{
    auto result = OH_ArkUI_UIInputEvent_GetType(nullptr);
    EXPECT_EQ(result, ArkUI_UIInputEvent_Type::ARKUI_UIINPUTEVENT_TYPE_UNKNOWN);
}

HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetType002, TestSize.Level0)
{
    std::vector<std::pair<ArkUI_UIInputEvent, ArkUI_UIInputEvent_Type>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, TOUCH_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_KEY_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_FOCUS_AXIS_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_CLICK_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_HOVER_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },

        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, AXIS_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_TOUCH },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, TOUCH_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_TOUCH },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_TOUCH },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_MOUSE_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_TOUCH },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_AXIS_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_TOUCH },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_KEY_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_FOCUS_AXIS_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_CLICK_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_TOUCH },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_HOVER_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_TOUCH },

        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, AXIS_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_AXIS },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, TOUCH_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_AXIS },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_TOUCH_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_AXIS },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_MOUSE_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_AXIS },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_AXIS_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_AXIS },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_KEY_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_FOCUS_AXIS_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_CLICK_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_AXIS },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_HOVER_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_AXIS },

        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_MOUSE, AXIS_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_MOUSE },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_MOUSE, TOUCH_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_MOUSE },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_TOUCH_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_MOUSE },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_MOUSE },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_AXIS_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_MOUSE },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_KEY_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_FOCUS_AXIS_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_CLICK_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_MOUSE },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_HOVER_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_MOUSE },

        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, AXIS_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_KEY },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, TOUCH_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_KEY },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, C_TOUCH_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_KEY },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, C_MOUSE_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_KEY },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, C_AXIS_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_KEY },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, C_KEY_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, C_FOCUS_AXIS_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, C_CLICK_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, C_HOVER_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_KEY },
    };

    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        auto result = OH_ArkUI_UIInputEvent_GetType(&input);
        EXPECT_EQ(result, expect) << "index = " << count << " : inputtype = " << input.inputType
                                  << " , eventTypeId = " << input.eventTypeId;
        count++;
    }
}

HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetType003, TestSize.Level0)
{
    const int32_t apiVersion = static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY);

    std::vector<ArkUI_UIInputEvent_Type> types = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, ARKUI_UIINPUTEVENT_TYPE_TOUCH,
        ARKUI_UIINPUTEVENT_TYPE_AXIS, ARKUI_UIINPUTEVENT_TYPE_MOUSE, ARKUI_UIINPUTEVENT_TYPE_KEY };

    std::vector<ArkUIEventTypeId> typeIds = {
        AXIS_EVENT_ID,
        TOUCH_EVENT_ID,
        C_TOUCH_EVENT_ID,
        C_MOUSE_EVENT_ID,
        C_AXIS_EVENT_ID,
        C_KEY_EVENT_ID,
        C_FOCUS_AXIS_EVENT_ID,
        C_CLICK_EVENT_ID,
        C_HOVER_EVENT_ID,
    };

    auto count = 0;
    for (auto type : types) {
        for (auto typeId : typeIds) {
            auto uiInputEvent = ArkUI_UIInputEvent { type, typeId, nullptr, false, apiVersion };
            auto result = OH_ArkUI_UIInputEvent_GetType(&uiInputEvent);
            EXPECT_EQ(result, type) << "index = " << count << " : inputtype = " << type
                                    << " , eventTypeId = " << typeId;
            count++;
        }
    }
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetAction001
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetAction001, TestSize.Level0)
{
    auto result = OH_ArkUI_UIInputEvent_GetAction(nullptr);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetAction002
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetAction002, TestSize.Level0)
{
    std::vector<ArkUI_UIInputEvent_Type> types = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, ARKUI_UIINPUTEVENT_TYPE_TOUCH,
        ARKUI_UIINPUTEVENT_TYPE_AXIS, ARKUI_UIINPUTEVENT_TYPE_MOUSE, ARKUI_UIINPUTEVENT_TYPE_KEY };

    std::vector<ArkUIEventTypeId> typeIds = {
        AXIS_EVENT_ID,
        TOUCH_EVENT_ID,
        C_TOUCH_EVENT_ID,
        C_MOUSE_EVENT_ID,
        C_AXIS_EVENT_ID,
        C_KEY_EVENT_ID,
        C_FOCUS_AXIS_EVENT_ID,
        C_CLICK_EVENT_ID,
        C_HOVER_EVENT_ID,
    };

    // 1 ArkUITouchEvent //ConvertToCTouchActionType
    ArkUITouchEvent touchInputEvent;
    std::vector<std::pair<ArkUI_Int32, int32_t>> touchActionTestCases = { { ORIGIN_TOUCH_ACTION_DOWN,
                                                                              UI_TOUCH_EVENT_ACTION_DOWN },
        { ORIGIN_TOUCH_ACTION_UP, UI_TOUCH_EVENT_ACTION_UP }, { ORIGIN_TOUCH_ACTION_MOVE, UI_TOUCH_EVENT_ACTION_MOVE },
        { ORIGIN_TOUCH_ACTION_CANCEL, UI_TOUCH_EVENT_ACTION_CANCEL } };

    // 2 ArkUIMouseEvent ConvertToCMouseActionType
    ArkUIMouseEvent mouseInputEvent;
    std::vector<std::pair<ArkUI_Int32, int32_t>> mouseActionTestCases = { { ORIGIN_MOUSE_ACTION_PRESS,
                                                                              UI_MOUSE_EVENT_ACTION_PRESS },
        { ORIGIN_MOUSE_ACTION_RELEASE, UI_MOUSE_EVENT_ACTION_RELEASE },
        { ORIGIN_MOUSE_ACTION_MOVE, UI_MOUSE_EVENT_ACTION_MOVE },
        { ORIGIN_MOUSE_ACTION_CANCEL, UI_MOUSE_EVENT_ACTION_CANCEL } };

    auto count = 0;
    for (auto type : types) {
        for (auto typeId : typeIds) {
            for (auto testCase : touchActionTestCases) {
                    auto input = testCase.first;
                    auto expect = (typeId == C_TOUCH_EVENT_ID) ? testCase.second : ARKUI_EVENT_ACTION_NULL;
                    touchInputEvent.action = input;

                    auto uiInputEvent =
                        ArkUI_UIInputEvent { type, typeId, (typeId != C_TOUCH_EVENT_ID) ? nullptr : &touchInputEvent };
                    auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "touch index = " << count << " : originAction = " << touchInputEvent.action
                        << " , action = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;
            }

            for (auto testCase : mouseActionTestCases) {
                    auto input = testCase.first;
                    auto expect = (typeId == C_MOUSE_EVENT_ID) ? testCase.second : ARKUI_EVENT_ACTION_NULL;
                    mouseInputEvent.action = input;

                    auto uiInputEvent =
                        ArkUI_UIInputEvent { type, typeId, (typeId != C_MOUSE_EVENT_ID) ? nullptr : &mouseInputEvent };
                    auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "mouse index = " << count << " : originAction = " << mouseInputEvent.action
                        << " , action = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;
            }
        }
    }
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetAction003
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetAction003, TestSize.Level0)
{
    const int32_t apiVersion = static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY);

    std::vector<ArkUI_UIInputEvent_Type> types = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, ARKUI_UIINPUTEVENT_TYPE_TOUCH,
        ARKUI_UIINPUTEVENT_TYPE_AXIS, ARKUI_UIINPUTEVENT_TYPE_MOUSE, ARKUI_UIINPUTEVENT_TYPE_KEY };

    std::vector<ArkUIEventTypeId> typeIds = {
        AXIS_EVENT_ID,
        TOUCH_EVENT_ID,
        C_TOUCH_EVENT_ID,
        C_MOUSE_EVENT_ID,
        C_AXIS_EVENT_ID,
        C_KEY_EVENT_ID,
        C_FOCUS_AXIS_EVENT_ID,
        C_CLICK_EVENT_ID,
        C_HOVER_EVENT_ID,
    };

    // 1 ArkUITouchEvent //ConvertToCTouchActionType
    ArkUITouchEvent touchInputEvent;
    std::vector<std::pair<ArkUI_Int32, int32_t>> touchActionTestCases = { { ORIGIN_TOUCH_ACTION_DOWN,
                                                                              UI_TOUCH_EVENT_ACTION_DOWN },
        { ORIGIN_TOUCH_ACTION_UP, UI_TOUCH_EVENT_ACTION_UP }, { ORIGIN_TOUCH_ACTION_MOVE, UI_TOUCH_EVENT_ACTION_MOVE },
        { ORIGIN_TOUCH_ACTION_CANCEL, UI_TOUCH_EVENT_ACTION_CANCEL } };

    // 2 ArkUIMouseEvent ConvertToCMouseActionType
    ArkUIMouseEvent mouseInputEvent;
    std::vector<std::pair<ArkUI_Int32, int32_t>> mouseActionTestCases = { { ORIGIN_MOUSE_ACTION_PRESS,
                                                                              UI_MOUSE_EVENT_ACTION_PRESS },
        { ORIGIN_MOUSE_ACTION_RELEASE, UI_MOUSE_EVENT_ACTION_RELEASE },
        { ORIGIN_MOUSE_ACTION_MOVE, UI_MOUSE_EVENT_ACTION_MOVE },
        { ORIGIN_MOUSE_ACTION_CANCEL, UI_MOUSE_EVENT_ACTION_CANCEL } };

    // 3 ArkUIAxisEvent ConvertToCAxisActionType
    ArkUIAxisEvent axisInputEvent;
    std::vector<std::pair<ArkUI_Int32, int32_t>> axisActionTestCases = {
        { ORIGIN_AXIS_ACTION_NONE, UI_AXIS_EVENT_ACTION_NONE },
        { ORIGIN_AXIS_ACTION_BEGIN, UI_AXIS_EVENT_ACTION_BEGIN },
        { ORIGIN_AXIS_ACTION_UPDATE, UI_AXIS_EVENT_ACTION_UPDATE },
        { ORIGIN_AXIS_ACTION_END, UI_AXIS_EVENT_ACTION_END }, { ORIGIN_AXIS_ACTION_CANCEL, UI_AXIS_EVENT_ACTION_CANCEL }
    };

    // 4 ArkUIKeyEvent ConvertToCKeyActionType
    ArkUIKeyEvent keyInputEvent;
    std::vector<std::pair<ArkUI_Int32, int32_t>> keyActionTestCases = {
        { ORIGIN_TOUCH_ACTION_DOWN, ARKUI_KEY_EVENT_DOWN }, { ORIGIN_TOUCH_ACTION_UP, ARKUI_KEY_EVENT_UP },
        { ORIGIN_TOUCH_ACTION_MOVE, ARKUI_KEY_EVENT_UNKNOWN }, { ORIGIN_TOUCH_ACTION_CANCEL, ARKUI_KEY_EVENT_UNKNOWN }
    };

    // 5 OHOS::Ace::TouchEvent ConvertToCTouchActionType
    OHOS::Ace::TouchEvent aceTouchInputEvent;
    std::vector<std::pair<ArkUI_Int32, int32_t>> aceTouchActionTestCases = { { ORIGIN_TOUCH_ACTION_DOWN,
                                                                                 UI_TOUCH_EVENT_ACTION_DOWN },
        { ORIGIN_TOUCH_ACTION_UP, UI_TOUCH_EVENT_ACTION_UP }, { ORIGIN_TOUCH_ACTION_MOVE, UI_TOUCH_EVENT_ACTION_MOVE },
        { ORIGIN_TOUCH_ACTION_CANCEL, UI_TOUCH_EVENT_ACTION_CANCEL } };

    // 6 OHOS::Ace::AxisEvent ConvertToCAxisActionType
    OHOS::Ace::AxisEvent aceAxisInputEvent;
    std::vector<std::pair<ArkUI_Int32, int32_t>> aceAxisActionTestCases = {
        { ORIGIN_AXIS_ACTION_NONE, UI_AXIS_EVENT_ACTION_NONE },
        { ORIGIN_AXIS_ACTION_BEGIN, UI_AXIS_EVENT_ACTION_BEGIN },
        { ORIGIN_AXIS_ACTION_UPDATE, UI_AXIS_EVENT_ACTION_UPDATE },
        { ORIGIN_AXIS_ACTION_END, UI_AXIS_EVENT_ACTION_END }, { ORIGIN_AXIS_ACTION_CANCEL, UI_AXIS_EVENT_ACTION_CANCEL }
    };

    auto count = 0;

    for (auto type : types) {
        for (auto typeId : typeIds) {
            for (auto testCase : touchActionTestCases) {
                    auto input = testCase.first;
                    auto expect = (typeId == C_TOUCH_EVENT_ID) ? testCase.second : ARKUI_EVENT_ACTION_NULL;
                    touchInputEvent.action = input;

                    auto uiInputEvent = ArkUI_UIInputEvent { type, typeId,
                        (typeId != C_TOUCH_EVENT_ID) ? nullptr : &touchInputEvent, false, apiVersion };
                    auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "touch index = " << count << " : originAction = " << touchInputEvent.action
                        << " , action = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;
            }

            for (auto testCase : mouseActionTestCases) {
                    auto input = testCase.first;
                    auto expect = (typeId == C_MOUSE_EVENT_ID) ? testCase.second : ARKUI_EVENT_ACTION_NULL;
                    mouseInputEvent.action = input;

                    auto uiInputEvent = ArkUI_UIInputEvent { type, typeId,
                        (typeId != C_MOUSE_EVENT_ID) ? nullptr : &mouseInputEvent, false, apiVersion };
                    auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "mouse index = " << count << " : originAction = " << mouseInputEvent.action
                        << " , action = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;
            }

            for (auto testCase : axisActionTestCases) {
                    auto input = testCase.first;
                    auto expect = (typeId == C_AXIS_EVENT_ID) ? testCase.second : ARKUI_EVENT_ACTION_NULL;
                    axisInputEvent.action = input;

                    auto uiInputEvent = ArkUI_UIInputEvent { type, typeId,
                        (typeId != C_AXIS_EVENT_ID) ? nullptr : &axisInputEvent, false, apiVersion };
                    auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "axis index = " << count << " : originAction = " << axisInputEvent.action
                        << " , action = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;
            }

            for (auto testCase : keyActionTestCases) {
                    auto input = testCase.first;
                    auto expect = (typeId == C_CLICK_EVENT_ID) ? testCase.second : ARKUI_EVENT_ACTION_NULL;
                    keyInputEvent.type = input;

                    auto uiInputEvent = ArkUI_UIInputEvent { type, typeId,
                        (typeId != C_CLICK_EVENT_ID) ? nullptr : &keyInputEvent, false, apiVersion };
                    auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "key index = " << count << " : originAction = " << keyInputEvent.type
                        << " , action = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;
            }

            for (auto testCase : aceTouchActionTestCases) {
                    auto input = testCase.first;
                    auto expect = (typeId == TOUCH_EVENT_ID) ? testCase.second : ARKUI_EVENT_ACTION_NULL;
                    aceTouchInputEvent.type = static_cast<TouchType>(input);

                    auto uiInputEvent = ArkUI_UIInputEvent { type, typeId,
                        (typeId != TOUCH_EVENT_ID) ? nullptr : &aceTouchInputEvent, false, apiVersion };
                    auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "aceTouch index = " << count
                        << " : originAction = " << static_cast<int32_t>(aceTouchInputEvent.type)
                        << " , action = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;
            }

            for (auto testCase : aceAxisActionTestCases) {
                    auto input = testCase.first;
                    auto expect = (typeId == AXIS_EVENT_ID) ? testCase.second : ARKUI_EVENT_ACTION_NULL;
                    aceAxisInputEvent.action = static_cast<AxisAction>(input);

                    auto uiInputEvent = ArkUI_UIInputEvent { type, typeId,
                        (typeId != AXIS_EVENT_ID) ? nullptr : &aceAxisInputEvent, false, apiVersion };
                    auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "aceAxis index = " << count
                        << " : originAction = " << static_cast<int32_t>(aceAxisInputEvent.action)
                        << " , action = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;
            }
        }
    }
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetSourceType001
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetSourceType001, TestSize.Level0)
{
    auto result = OH_ArkUI_UIInputEvent_GetSourceType(nullptr);
    EXPECT_EQ(result, static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN));
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetSourceType002
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetSourceType002, TestSize.Level0)
{
    std::vector<ArkUI_UIInputEvent_Type> types = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, ARKUI_UIINPUTEVENT_TYPE_TOUCH,
        ARKUI_UIINPUTEVENT_TYPE_AXIS, ARKUI_UIINPUTEVENT_TYPE_MOUSE, ARKUI_UIINPUTEVENT_TYPE_KEY };

    std::vector<ArkUIEventTypeId> typeIds = {
        AXIS_EVENT_ID,
        TOUCH_EVENT_ID,
        C_TOUCH_EVENT_ID,
        C_MOUSE_EVENT_ID,
        C_AXIS_EVENT_ID,
        C_KEY_EVENT_ID,
        C_FOCUS_AXIS_EVENT_ID,
        C_CLICK_EVENT_ID,
        C_HOVER_EVENT_ID,
    };

    std::vector<SourceType> testCases = { SourceType::NONE, SourceType::MOUSE, SourceType::TOUCH, SourceType::TOUCH_PAD,
        SourceType::KEYBOARD, SourceType::JOYSTICK, SourceType::CROWN };

    // 1 ArkUITouchEvent HandleCTouchEventSourceType
    ArkUITouchEvent touchInputEvent;
    // 2 ArkUIMouseEvent HandleCMouseEventSourceType
    ArkUIMouseEvent mouseInputEvent;
    // 3 ArkUIAxisEvent HandleCAxisEventSourceType
    ArkUIAxisEvent axisInputEvent;
    // 4 ArkUIFocusAxisEvent HandleCFocusAxisEventSourceType
    ArkUIFocusAxisEvent focusAxisInputEvent;
    // 5 ArkUIHoverEvent HandleCHoverEventSourceType
    ArkUIHoverEvent hoverInputEvent;
    // 6 ArkUIClickEvent HandleCClickEventSourceType
    ArkUIClickEvent clickInputEvent;
    // 7 OHOS::Ace::AxisEvent HandleAxisEventSourceType
    OHOS::Ace::AxisEvent aceAxisInputEvent;

    auto count = 0;
    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, nullptr };
    auto input = static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    auto expect = static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    auto result = static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);

    for (auto type : types) {
        for (auto typeId : typeIds) {
            for (auto testCase : testCases) {
                    input = static_cast<int32_t>(testCase);
                    expect = static_cast<int32_t>(testCase);

                    touchInputEvent.sourceType = input;
                    if (typeId != C_TOUCH_EVENT_ID) {
                    expect = static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
                    } else {
                    expect = static_cast<int32_t>(testCase);
                    }
                    uiInputEvent =
                        ArkUI_UIInputEvent { type, typeId, (typeId != C_TOUCH_EVENT_ID) ? nullptr : &touchInputEvent };
                    result = OH_ArkUI_UIInputEvent_GetSourceType(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "touch index = " << count
                        << " : sourceType = " << static_cast<int32_t>(touchInputEvent.sourceType)
                        << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;

                    mouseInputEvent.sourceType = input;
                    if (typeId != C_MOUSE_EVENT_ID) {
                    expect = static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
                    } else {
                    expect = static_cast<int32_t>(testCase);
                    }
                    uiInputEvent =
                        ArkUI_UIInputEvent { type, typeId, (typeId != C_MOUSE_EVENT_ID) ? nullptr : &mouseInputEvent };
                    result = OH_ArkUI_UIInputEvent_GetSourceType(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "mouse index = " << count
                        << " : sourceType = " << static_cast<int32_t>(mouseInputEvent.sourceType)
                        << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;

                    axisInputEvent.sourceType = input;
                    if (typeId != C_AXIS_EVENT_ID) {
                    expect = static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
                    } else {
                    expect = static_cast<int32_t>(testCase);
                    }
                    uiInputEvent =
                        ArkUI_UIInputEvent { type, typeId, (typeId != C_AXIS_EVENT_ID) ? nullptr : &axisInputEvent };
                    result = OH_ArkUI_UIInputEvent_GetSourceType(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "axis index = " << count
                        << " : sourceType = " << static_cast<int32_t>(axisInputEvent.sourceType)
                        << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;

                    focusAxisInputEvent.sourceType = input;
                    if (typeId != C_FOCUS_AXIS_EVENT_ID) {
                    expect = static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
                    } else {
                    expect = static_cast<int32_t>(testCase);
                    }
                    uiInputEvent = ArkUI_UIInputEvent { type, typeId,
                        (typeId != C_FOCUS_AXIS_EVENT_ID) ? nullptr : &focusAxisInputEvent };
                    result = OH_ArkUI_UIInputEvent_GetSourceType(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "focus axis index = " << count
                        << " : sourceType = " << static_cast<int32_t>(focusAxisInputEvent.sourceType)
                        << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;

                    hoverInputEvent.sourceType = input;
                    if (typeId != C_HOVER_EVENT_ID) {
                    expect = static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
                    } else {
                    expect = static_cast<int32_t>(testCase);
                    }
                    uiInputEvent =
                        ArkUI_UIInputEvent { type, typeId, (typeId != C_HOVER_EVENT_ID) ? nullptr : &hoverInputEvent };
                    result = OH_ArkUI_UIInputEvent_GetSourceType(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "hover index = " << count
                        << " : sourceType = " << static_cast<int32_t>(hoverInputEvent.sourceType)
                        << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;

                    clickInputEvent.sourceType = input;
                    if (typeId != C_CLICK_EVENT_ID) {
                    expect = static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
                    } else {
                    expect = static_cast<int32_t>(testCase);
                    }
                    uiInputEvent =
                        ArkUI_UIInputEvent { type, typeId, (typeId != C_CLICK_EVENT_ID) ? nullptr : &clickInputEvent };
                    result = OH_ArkUI_UIInputEvent_GetSourceType(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "click index = " << count
                        << " : sourceType = " << static_cast<int32_t>(clickInputEvent.sourceType)
                        << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;

                    aceAxisInputEvent.sourceType = testCase;
                    if (typeId != AXIS_EVENT_ID) {
                    expect = static_cast<int32_t>(UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
                    } else {
                    expect = static_cast<int32_t>(testCase);
                    }
                    uiInputEvent =
                        ArkUI_UIInputEvent { type, typeId, (typeId != AXIS_EVENT_ID) ? nullptr : &aceAxisInputEvent };
                    result = OH_ArkUI_UIInputEvent_GetSourceType(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "ace axis index = " << count
                        << " : sourceType = " << static_cast<int32_t>(aceAxisInputEvent.sourceType)
                        << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;
            }
        }
    }
}

// OH_ArkUI_UIInputEvent_GetToolType 1
/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetToolType001
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetToolType001, TestSize.Level0)
{
    auto result = OH_ArkUI_UIInputEvent_GetToolType(nullptr);
    EXPECT_EQ(result, static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN));
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetToolType002
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetToolType002, TestSize.Level0)
{
    std::vector<ArkUI_UIInputEvent_Type> types = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, ARKUI_UIINPUTEVENT_TYPE_TOUCH,
        ARKUI_UIINPUTEVENT_TYPE_AXIS, ARKUI_UIINPUTEVENT_TYPE_MOUSE, ARKUI_UIINPUTEVENT_TYPE_KEY };

    std::vector<ArkUIEventTypeId> typeIds = {
        AXIS_EVENT_ID,
        TOUCH_EVENT_ID,
        C_TOUCH_EVENT_ID,
        C_MOUSE_EVENT_ID,
        C_AXIS_EVENT_ID,
        C_KEY_EVENT_ID,
        C_FOCUS_AXIS_EVENT_ID,
        C_CLICK_EVENT_ID,
        C_HOVER_EVENT_ID,
    };

    std::vector<std::pair<ArkUI_Int32, int32_t>> testCases = { { ORIGIN_INPUT_EVENT_TOOL_TYPE_FINGER,
                                                                   UI_INPUT_EVENT_TOOL_TYPE_FINGER },
        { ORIGIN_INPUT_EVENT_TOOL_TYPE_PEN, UI_INPUT_EVENT_TOOL_TYPE_PEN },
        { ORIGIN_INPUT_EVENT_TOOL_TYPE_MOUSE, UI_INPUT_EVENT_TOOL_TYPE_MOUSE },
        { ORIGIN_INPUT_EVENT_TOOL_TYPE_TOUCHPAD, UI_INPUT_EVENT_TOOL_TYPE_TOUCHPAD },
        { ORIGIN_INPUT_EVENT_TOOL_TYPE_JOYSTICK, UI_INPUT_EVENT_TOOL_TYPE_JOYSTICK } };

    // 1 ArkUITouchEvent HandleCTouchEventToolType
    ArkUITouchEvent touchInputEvent;
    // 2 ArkUIMouseEvent HandleCMouseEventToolType
    ArkUIMouseEvent mouseInputEvent;
    // 3 ArkUIAxisEvent HandleCAxisEventToolType
    ArkUIAxisEvent axisInputEvent;
    // 4 ArkUIFocusAxisEvent HandleCFocusAxisEventToolType
    ArkUIFocusAxisEvent focusAxisInputEvent;
    // 5 ArkUIHoverEvent HandleCHoverEventToolType
    ArkUIHoverEvent hoverInputEvent;
    // 6 ArkUIClickEvent HandleCClickEventToolType
    ArkUIClickEvent clickInputEvent;
    // 7 OHOS::Ace::AxisEvent HandleAxisEventToolType
    OHOS::Ace::AxisEvent aceAxisInputEvent;

    auto count = 0;
    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, nullptr };
    auto input = static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
    auto expect = static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
    auto result = static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);

    for (auto type : types) {
        for (auto typeId : typeIds) {
            for (auto testCase : testCases) {
                    input = static_cast<int32_t>(testCase.first);
                    expect = static_cast<int32_t>(testCase.second);

                    touchInputEvent.actionTouchPoint.toolType = input;
                    if (typeId != C_TOUCH_EVENT_ID) {
                    expect = static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
                    } else {
                    expect = static_cast<int32_t>(testCase.second);
                    }
                    uiInputEvent =
                        ArkUI_UIInputEvent { type, typeId, (typeId != C_TOUCH_EVENT_ID) ? nullptr : &touchInputEvent };
                    result = OH_ArkUI_UIInputEvent_GetToolType(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "touch index = " << count
                        << " : sourceTool = " << static_cast<int32_t>(touchInputEvent.actionTouchPoint.toolType)
                        << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;

                    mouseInputEvent.actionTouchPoint.toolType = input;
                    if (typeId != C_MOUSE_EVENT_ID) {
                    expect = static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
                    } else {
                    expect = static_cast<int32_t>(testCase.second);
                    }
                    uiInputEvent =
                        ArkUI_UIInputEvent { type, typeId, (typeId != C_MOUSE_EVENT_ID) ? nullptr : &mouseInputEvent };
                    result = OH_ArkUI_UIInputEvent_GetToolType(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "mouse index = " << count
                        << " : sourceTool = " << static_cast<int32_t>(mouseInputEvent.actionTouchPoint.toolType)
                        << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;

                    axisInputEvent.actionTouchPoint.toolType = input;
                    if (typeId != C_AXIS_EVENT_ID) {
                    expect = static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
                    } else {
                    expect = static_cast<int32_t>(testCase.second);
                    }
                    uiInputEvent =
                        ArkUI_UIInputEvent { type, typeId, (typeId != C_AXIS_EVENT_ID) ? nullptr : &axisInputEvent };
                    result = OH_ArkUI_UIInputEvent_GetToolType(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "axis index = " << count
                        << " : sourceTool = " << static_cast<int32_t>(axisInputEvent.actionTouchPoint.toolType)
                        << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;

                    focusAxisInputEvent.toolType = input;
                    if (typeId != C_FOCUS_AXIS_EVENT_ID) {
                    expect = static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
                    } else {
                    expect = static_cast<int32_t>(testCase.second);
                    }
                    uiInputEvent = ArkUI_UIInputEvent { type, typeId,
                        (typeId != C_FOCUS_AXIS_EVENT_ID) ? nullptr : &focusAxisInputEvent };
                    result = OH_ArkUI_UIInputEvent_GetToolType(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "focus axis index = " << count
                        << " : sourceTool = " << static_cast<int32_t>(focusAxisInputEvent.toolType)
                        << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;

                    hoverInputEvent.toolType = input;
                    if (typeId != C_HOVER_EVENT_ID) {
                    expect = static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
                    } else {
                    expect = static_cast<int32_t>(testCase.second);
                    }
                    uiInputEvent =
                        ArkUI_UIInputEvent { type, typeId, (typeId != C_HOVER_EVENT_ID) ? nullptr : &hoverInputEvent };
                    result = OH_ArkUI_UIInputEvent_GetToolType(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "hover index = " << count
                        << " : sourceTool = " << static_cast<int32_t>(hoverInputEvent.toolType)
                        << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;

                    clickInputEvent.toolType = input;
                    if (typeId != C_CLICK_EVENT_ID) {
                    expect = static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
                    } else {
                    expect = static_cast<int32_t>(testCase.second);
                    }
                    uiInputEvent =
                        ArkUI_UIInputEvent { type, typeId, (typeId != C_CLICK_EVENT_ID) ? nullptr : &clickInputEvent };
                    result = OH_ArkUI_UIInputEvent_GetToolType(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "click index = " << count
                        << " : sourceTool = " << static_cast<int32_t>(clickInputEvent.toolType)
                        << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;

                    aceAxisInputEvent.sourceTool = static_cast<SourceTool>(testCase.first);
                    if (typeId != AXIS_EVENT_ID) {
                    expect = static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
                    } else {
                    expect = static_cast<int32_t>(testCase.second);
                    }
                    uiInputEvent =
                        ArkUI_UIInputEvent { type, typeId, (typeId != AXIS_EVENT_ID) ? nullptr : &aceAxisInputEvent };
                    result = OH_ArkUI_UIInputEvent_GetToolType(&uiInputEvent);
                    EXPECT_EQ(result, expect)
                        << "ace axis index = " << count
                        << " : sourceTool = " << static_cast<int32_t>(aceAxisInputEvent.sourceTool)
                        << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
                    count++;
            }
        }
    }
}

// OH_ArkUI_UIInputEvent_GetEventTime
/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTime001
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTime001, TestSize.Level0)
{
    auto result = OH_ArkUI_UIInputEvent_GetEventTime(nullptr);
    EXPECT_EQ(result, ARKUI_EVENT_ARKUI_TIME_NULL);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTime002
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTime002, TestSize.Level0)
{
    std::vector<ArkUI_UIInputEvent_Type> types = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, ARKUI_UIINPUTEVENT_TYPE_TOUCH,
        ARKUI_UIINPUTEVENT_TYPE_AXIS, ARKUI_UIINPUTEVENT_TYPE_MOUSE, ARKUI_UIINPUTEVENT_TYPE_KEY };

    std::vector<ArkUIEventTypeId> typeIds = {
        AXIS_EVENT_ID,
        TOUCH_EVENT_ID,
        C_TOUCH_EVENT_ID,
        C_MOUSE_EVENT_ID,
        C_AXIS_EVENT_ID,
        C_KEY_EVENT_ID,
        C_FOCUS_AXIS_EVENT_ID,
        C_CLICK_EVENT_ID,
        C_HOVER_EVENT_ID,
    };
    uint64_t testCases = ARKUI_EVENT_ARKUI_TIME;

    // 1 ArkUITouchEvent {C_TOUCH_EVENT_ID, HandleCTouchEvent}
    ArkUITouchEvent touchInputEvent;
    // 2 ArkUIMouseEvent {C_MOUSE_EVENT_ID, HandleCMouseEvent}
    ArkUIMouseEvent mouseInputEvent;
    // 3 ArkUIAxisEvent {C_AXIS_EVENT_ID, HandleCAxisEvent}
    ArkUIAxisEvent axisInputEvent;
    // 4 ArkUIFocusAxisEvent {C_FOCUS_AXIS_EVENT_ID, HandleCFocusAxisEvent}
    ArkUIFocusAxisEvent focusAxisInputEvent;
    // 5 ArkUIHoverEvent {C_HOVER_EVENT_ID, HandleCHoverEventTimestamp}
    ArkUIHoverEvent hoverInputEvent;
    // 6 ArkUIClickEvent {C_CLICK_EVENT_ID, HandleCClickEventTimestamp}
    ArkUIClickEvent clickInputEvent;
    // 7 OHOS::Ace::AxisEvent {AXIS_EVENT_ID, HandleAxisEvent}
    OHOS::Ace::PointerEvent aceAxisInputEvent;
    // 8 OHOS::Ace::TouchEvent {TOUCH_EVENT_ID, HandleTouchEvent}
    OHOS::Ace::PointerEvent acePointerInputEvent;
    // 9 ArkUIKeyEvent {C_KEY_EVENT_ID, HandleCKeyEvent}
    ArkUIKeyEvent keyInputEvent;

    auto count = 0;
    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, nullptr };
    auto input = ARKUI_EVENT_ARKUI_TIME;
    auto expect = ARKUI_EVENT_ARKUI_TIME;
    auto result = ARKUI_EVENT_ARKUI_TIME;

    for (auto type : types) {
        for (auto typeId : typeIds) {
            input = testCases;
            expect = testCases;

            touchInputEvent.timeStamp = input;
            if (typeId != C_TOUCH_EVENT_ID) {
                    expect = ARKUI_EVENT_ARKUI_TIME_NULL;
            } else {
                    expect = testCases;
            }
            uiInputEvent =
                ArkUI_UIInputEvent { type, typeId, (typeId != C_TOUCH_EVENT_ID) ? nullptr : &touchInputEvent };
            result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
            EXPECT_EQ(result, expect) << "touch index = " << count << " : time = " << touchInputEvent.timeStamp
                                      << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
            count++;

            mouseInputEvent.timeStamp = input;
            if (typeId != C_MOUSE_EVENT_ID) {
                    expect = ARKUI_EVENT_ARKUI_TIME_NULL;
            } else {
                    expect = testCases;
            }
            uiInputEvent =
                ArkUI_UIInputEvent { type, typeId, (typeId != C_MOUSE_EVENT_ID) ? nullptr : &mouseInputEvent };
            result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
            EXPECT_EQ(result, expect) << "mouse index = " << count << " : time = " << mouseInputEvent.timeStamp
                                      << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
            count++;

            axisInputEvent.timeStamp = input;
            if (typeId != C_AXIS_EVENT_ID) {
                    expect = ARKUI_EVENT_ARKUI_TIME_NULL;
            } else {
                    expect = testCases;
            }
            uiInputEvent = ArkUI_UIInputEvent { type, typeId, (typeId != C_AXIS_EVENT_ID) ? nullptr : &axisInputEvent };
            result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
            EXPECT_EQ(result, expect) << "axis index = " << count << " : time = " << axisInputEvent.timeStamp
                                      << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
            count++;

            focusAxisInputEvent.timeStamp = input;
            if (typeId != C_FOCUS_AXIS_EVENT_ID) {
                    expect = ARKUI_EVENT_ARKUI_TIME_NULL;
            } else {
                    expect = testCases;
            }
            uiInputEvent =
                ArkUI_UIInputEvent { type, typeId, (typeId != C_FOCUS_AXIS_EVENT_ID) ? nullptr : &focusAxisInputEvent };
            result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
            EXPECT_EQ(result, expect) << "focus axis index = " << count << " : time = " << focusAxisInputEvent.timeStamp
                                      << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
            count++;

            hoverInputEvent.timeStamp = input;
            if (typeId != C_HOVER_EVENT_ID) {
                    expect = ARKUI_EVENT_ARKUI_TIME_NULL;
            } else {
                    expect = testCases;
            }
            uiInputEvent =
                ArkUI_UIInputEvent { type, typeId, (typeId != C_HOVER_EVENT_ID) ? nullptr : &hoverInputEvent };
            result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
            EXPECT_EQ(result, expect) << "hover index = " << count << " : time = " << hoverInputEvent.timeStamp
                                      << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
            count++;

            clickInputEvent.timestamp = input;
            if (typeId != C_CLICK_EVENT_ID) {
                    expect = ARKUI_EVENT_ARKUI_TIME_NULL;
            } else {
                    expect = testCases;
            }
            uiInputEvent =
                ArkUI_UIInputEvent { type, typeId, (typeId != C_CLICK_EVENT_ID) ? nullptr : &clickInputEvent };
            result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
            EXPECT_EQ(result, expect) << "click index = " << count << " : time = " << clickInputEvent.timestamp
                                      << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
            count++;

            if (typeId != AXIS_EVENT_ID) {
                    expect = ARKUI_EVENT_ARKUI_TIME_NULL;
            } else {
                    expect = aceAxisInputEvent.time.time_since_epoch().count();
            }
            uiInputEvent =
                ArkUI_UIInputEvent { type, typeId, (typeId != AXIS_EVENT_ID) ? nullptr : &aceAxisInputEvent };
            result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
            EXPECT_EQ(result, expect) << "ace axis index = " << count
                                      << " : time = " << aceAxisInputEvent.time.time_since_epoch().count()
                                      << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
            count++;

            if (typeId != TOUCH_EVENT_ID) {
                    expect = ARKUI_EVENT_ARKUI_TIME_NULL;
            } else {
                    expect = acePointerInputEvent.time.time_since_epoch().count();
            }
            uiInputEvent =
                ArkUI_UIInputEvent { type, typeId, (typeId != TOUCH_EVENT_ID) ? nullptr : &acePointerInputEvent };
            result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
            EXPECT_EQ(result, expect) << "ace Pointer index = " << count
                                      << " : time = " << acePointerInputEvent.time.time_since_epoch().count()
                                      << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
            count++;

            keyInputEvent.timestamp = input;
            if (typeId != C_KEY_EVENT_ID) {
                    expect = ARKUI_EVENT_ARKUI_TIME_NULL;
            } else {
                    expect = testCases;
            }
            uiInputEvent = ArkUI_UIInputEvent { type, typeId, (typeId != C_KEY_EVENT_ID) ? nullptr : &keyInputEvent };
            result = OH_ArkUI_UIInputEvent_GetEventTime(&uiInputEvent);
            EXPECT_EQ(result, expect) << "key index = " << count << " : time = " << keyInputEvent.timestamp
                                      << " , result = " << result << " , type = " << type << " , typeId = " << typeId;
            count++;
        }
    }
}

} // namespace OHOS::Ace