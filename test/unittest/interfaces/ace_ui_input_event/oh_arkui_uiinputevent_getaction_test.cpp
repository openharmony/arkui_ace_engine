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
#include "core/common/ace_application_info.h"

using namespace testing;
using namespace testing::ext;

// defined in  ace_engine/interfaces/native/node/event_converter.cpp
namespace {
constexpr int32_t ORIGIN_TOUCH_ACTION_DOWN = 0;
constexpr int32_t ORIGIN_TOUCH_ACTION_UP = 1;
constexpr int32_t ORIGIN_TOUCH_ACTION_MOVE = 2;
constexpr int32_t ORIGIN_TOUCH_ACTION_CANCEL = 3;
constexpr int32_t ORIGIN_TOUCH_ACTION_LESS_THAN_LIMIT = ORIGIN_TOUCH_ACTION_DOWN - 1;
constexpr int32_t ORIGIN_TOUCH_ACTION_MORE_THAN_LIMIT = ORIGIN_TOUCH_ACTION_CANCEL + 1;

constexpr int32_t ORIGIN_MOUSE_ACTION_PRESS = 1;
constexpr int32_t ORIGIN_MOUSE_ACTION_RELEASE = 2;
constexpr int32_t ORIGIN_MOUSE_ACTION_MOVE = 3;
constexpr int32_t ORIGIN_MOUSE_ACTION_CANCEL = 13;
constexpr int32_t ORIGIN_MOUSE_ACTION_LESS_THAN_LIMIT = ORIGIN_MOUSE_ACTION_PRESS - 1;
constexpr int32_t ORIGIN_MOUSE_ACTION_MORE_THAN_LIMIT = ORIGIN_MOUSE_ACTION_CANCEL + 1;

constexpr int32_t ORIGIN_AXIS_ACTION_NONE = 0;
constexpr int32_t ORIGIN_AXIS_ACTION_BEGIN = 1;
constexpr int32_t ORIGIN_AXIS_ACTION_UPDATE = 2;
constexpr int32_t ORIGIN_AXIS_ACTION_END = 3;
constexpr int32_t ORIGIN_AXIS_ACTION_CANCEL = 4;
constexpr int32_t ORIGIN_AXIS_ACTION_LESS_THAN_LIMIT = ORIGIN_AXIS_ACTION_NONE - 1;
constexpr int32_t ORIGIN_AXIS_ACTION_MORE_THAN_LIMIT = ORIGIN_AXIS_ACTION_CANCEL + 1;

constexpr int32_t ARKUI_EVENT_ACTION_NULL = -1;
} // namespace

namespace OHOS::Ace {
/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetAction001
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */


HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetAction001, TestSize.Level0)
{
    /**
     * @tc.steps: step1.call functions and return expected results.
     */
    auto result = OH_ArkUI_UIInputEvent_GetAction(nullptr);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetAction101
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetAction101, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 1 ArkUITouchEvent ConvertToCTouchActionType
    ArkUITouchEvent inputEvent;
    std::vector<std::pair<ArkUI_Int32, int32_t>> testCases = {
        { ORIGIN_TOUCH_ACTION_DOWN, UI_TOUCH_EVENT_ACTION_DOWN },
        { ORIGIN_TOUCH_ACTION_UP, UI_TOUCH_EVENT_ACTION_UP },
        { ORIGIN_TOUCH_ACTION_MOVE, UI_TOUCH_EVENT_ACTION_MOVE },
        { ORIGIN_TOUCH_ACTION_CANCEL, UI_TOUCH_EVENT_ACTION_CANCEL },
        { ORIGIN_TOUCH_ACTION_LESS_THAN_LIMIT, ARKUI_EVENT_ACTION_NULL },
        { ORIGIN_TOUCH_ACTION_MORE_THAN_LIMIT, ARKUI_EVENT_ACTION_NULL }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        inputEvent.action = testCase.first;
        auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &inputEvent };
        auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
        EXPECT_EQ(result, testCase.second)
            << "index = " << count << " : originAction = " << testCase.first << " , result = " << result;
        count++;
    }

    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, nullptr };
    auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ACTION_NULL) << "index = " << count;
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetAction102
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetAction102, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 2 ArkUIMouseEvent ConvertToCMouseActionType
    ArkUIMouseEvent inputEvent;
    std::vector<std::pair<ArkUI_Int32, int32_t>> testCases = {
        { ORIGIN_MOUSE_ACTION_PRESS, UI_MOUSE_EVENT_ACTION_PRESS },
        { ORIGIN_MOUSE_ACTION_RELEASE, UI_MOUSE_EVENT_ACTION_RELEASE },
        { ORIGIN_MOUSE_ACTION_MOVE, UI_MOUSE_EVENT_ACTION_MOVE },
        { ORIGIN_MOUSE_ACTION_CANCEL, UI_MOUSE_EVENT_ACTION_CANCEL },
        { ORIGIN_MOUSE_ACTION_LESS_THAN_LIMIT, UI_MOUSE_EVENT_ACTION_UNKNOWN },
        { ORIGIN_MOUSE_ACTION_MORE_THAN_LIMIT, UI_MOUSE_EVENT_ACTION_UNKNOWN }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        inputEvent.action = testCase.first;
        auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, &inputEvent };
        auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
        EXPECT_EQ(result, testCase.second)
            << "index = " << count << " : originAction = " << testCase.first << " , result = " << result;
        count++;
    }

    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, nullptr };
    auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ACTION_NULL) << "index = " << count;
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetAction103
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetAction103, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 3 Other ArkUIEventTypeId
    std::vector<ArkUIEventTypeId> typeIds = {
        AXIS_EVENT_ID,
        TOUCH_EVENT_ID,
        C_AXIS_EVENT_ID,
        C_KEY_EVENT_ID,
        C_FOCUS_AXIS_EVENT_ID,
        C_CLICK_EVENT_ID,
        C_HOVER_EVENT_ID
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto typeId : typeIds) {
        auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, typeId, nullptr };
        auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
        EXPECT_EQ(result, ARKUI_EVENT_ACTION_NULL) << "other index = " << count;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetAction201
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetAction201, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    const int32_t apiVersion = static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY);
    // 1 ArkUITouchEvent ConvertToCTouchActionType
    ArkUITouchEvent inputEvent;
    std::vector<std::pair<ArkUI_Int32, int32_t>> testCases = {
        { ORIGIN_TOUCH_ACTION_DOWN, UI_TOUCH_EVENT_ACTION_DOWN },
        { ORIGIN_TOUCH_ACTION_UP, UI_TOUCH_EVENT_ACTION_UP },
        { ORIGIN_TOUCH_ACTION_MOVE, UI_TOUCH_EVENT_ACTION_MOVE },
        { ORIGIN_TOUCH_ACTION_CANCEL, UI_TOUCH_EVENT_ACTION_CANCEL },
        { ORIGIN_TOUCH_ACTION_LESS_THAN_LIMIT, ARKUI_EVENT_ACTION_NULL },
        { ORIGIN_TOUCH_ACTION_MORE_THAN_LIMIT, ARKUI_EVENT_ACTION_NULL }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        inputEvent.action = testCase.first;
        auto uiInputEvent =
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &inputEvent, false, apiVersion };
        auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
        EXPECT_EQ(result, testCase.second)
            << "index = " << count << " : originAction = " << testCase.first << " , result = " << result;
        count++;
    }

    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, nullptr };
    auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ACTION_NULL) << "index = " << count;
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetAction202
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetAction202, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    const int32_t apiVersion = static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY);
    // 2 ArkUIMouseEvent ConvertToCMouseActionType
    ArkUIMouseEvent inputEvent;
    std::vector<std::pair<ArkUI_Int32, int32_t>> testCases = {
        { ORIGIN_MOUSE_ACTION_PRESS, UI_MOUSE_EVENT_ACTION_PRESS },
        { ORIGIN_MOUSE_ACTION_RELEASE, UI_MOUSE_EVENT_ACTION_RELEASE },
        { ORIGIN_MOUSE_ACTION_MOVE, UI_MOUSE_EVENT_ACTION_MOVE },
        { ORIGIN_MOUSE_ACTION_CANCEL, UI_MOUSE_EVENT_ACTION_CANCEL },
        { ORIGIN_MOUSE_ACTION_LESS_THAN_LIMIT, UI_MOUSE_EVENT_ACTION_UNKNOWN },
        { ORIGIN_MOUSE_ACTION_MORE_THAN_LIMIT, UI_MOUSE_EVENT_ACTION_UNKNOWN }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        inputEvent.action = testCase.first;
        auto uiInputEvent =
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, &inputEvent, false, apiVersion };
        auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
        EXPECT_EQ(result, testCase.second)
            << "index = " << count << " : originAction = " << testCase.first << " , result = " << result;
        count++;
    }

    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, nullptr };
    auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ACTION_NULL) << "index = " << count;
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetAction203
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetAction203, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    const int32_t apiVersion = static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY);
    // 3 ArkUIAxisEvent ConvertToCAxisActionType
    ArkUIAxisEvent inputEvent;
    std::vector<std::pair<ArkUI_Int32, int32_t>> testCases = {
        { ORIGIN_AXIS_ACTION_NONE, UI_AXIS_EVENT_ACTION_NONE },
        { ORIGIN_AXIS_ACTION_BEGIN, UI_AXIS_EVENT_ACTION_BEGIN },
        { ORIGIN_AXIS_ACTION_UPDATE, UI_AXIS_EVENT_ACTION_UPDATE },
        { ORIGIN_AXIS_ACTION_END, UI_AXIS_EVENT_ACTION_END },
        { ORIGIN_AXIS_ACTION_CANCEL, UI_AXIS_EVENT_ACTION_CANCEL },
        { ORIGIN_AXIS_ACTION_LESS_THAN_LIMIT, UI_MOUSE_EVENT_ACTION_UNKNOWN },
        { ORIGIN_AXIS_ACTION_MORE_THAN_LIMIT, UI_MOUSE_EVENT_ACTION_UNKNOWN }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        inputEvent.action = testCase.first;
        auto uiInputEvent =
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &inputEvent, false, apiVersion };
        auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
        EXPECT_EQ(result, testCase.second)
            << "index = " << count << " : originAction = " << testCase.first << " , result = " << result;
        count++;
    }

    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, nullptr };
    auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ACTION_NULL) << "index = " << count;
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetAction204
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetAction204, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    const int32_t apiVersion = static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY);
    // 4 ArkUIKeyEvent ConvertToCKeyActionType
    ArkUIKeyEvent inputEvent;
    std::vector<std::pair<ArkUI_Int32, int32_t>> testCases = {
        { ORIGIN_TOUCH_ACTION_DOWN, ARKUI_KEY_EVENT_DOWN },
        { ORIGIN_TOUCH_ACTION_UP, ARKUI_KEY_EVENT_UP },
        { ORIGIN_TOUCH_ACTION_MOVE, ARKUI_KEY_EVENT_UNKNOWN },
        { ORIGIN_TOUCH_ACTION_CANCEL, ARKUI_KEY_EVENT_UNKNOWN },
        { ORIGIN_TOUCH_ACTION_LESS_THAN_LIMIT, ARKUI_EVENT_ACTION_NULL },
        { ORIGIN_TOUCH_ACTION_MORE_THAN_LIMIT, ARKUI_EVENT_ACTION_NULL }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        inputEvent.type = testCase.first;
        auto uiInputEvent =
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_CLICK_EVENT_ID, &inputEvent, false, apiVersion };
        auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
        EXPECT_EQ(result, testCase.second)
            << "index = " << count << " : originAction = " << testCase.first << " , result = " << result;
        count++;
    }

    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_CLICK_EVENT_ID, nullptr };
    auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ACTION_NULL) << "index = " << count;
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetAction205
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetAction205, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    const int32_t apiVersion = static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY);
    // 5 OHOS::Ace::TouchEvent ConvertToCTouchActionType
    OHOS::Ace::TouchEvent inputEvent;
    std::vector<std::pair<ArkUI_Int32, int32_t>> testCases = {
        { ORIGIN_TOUCH_ACTION_DOWN, UI_TOUCH_EVENT_ACTION_DOWN },
        { ORIGIN_TOUCH_ACTION_UP, UI_TOUCH_EVENT_ACTION_UP },
        { ORIGIN_TOUCH_ACTION_MOVE, UI_TOUCH_EVENT_ACTION_MOVE },
        { ORIGIN_TOUCH_ACTION_CANCEL, UI_TOUCH_EVENT_ACTION_CANCEL },
        { ORIGIN_TOUCH_ACTION_LESS_THAN_LIMIT, ARKUI_EVENT_ACTION_NULL },
        { ORIGIN_TOUCH_ACTION_MORE_THAN_LIMIT, ARKUI_EVENT_ACTION_NULL }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        inputEvent.type = static_cast<TouchType>(testCase.first);
        auto uiInputEvent =
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, TOUCH_EVENT_ID, &inputEvent, false, apiVersion };
        auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
        EXPECT_EQ(result, testCase.second)
            << "index = " << count << " : originAction = " << testCase.first << " , result = " << result;
        count++;
    }

    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, TOUCH_EVENT_ID, nullptr };
    auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ACTION_NULL) << "index = " << count;
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetAction206
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetAction206, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    const int32_t apiVersion = static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY);
    // 6 OHOS::Ace::AxisEvent ConvertToCAxisActionType
    OHOS::Ace::AxisEvent inputEvent;
    std::vector<std::pair<ArkUI_Int32, int32_t>> testCases = {
        { ORIGIN_AXIS_ACTION_NONE, UI_AXIS_EVENT_ACTION_NONE },
        { ORIGIN_AXIS_ACTION_BEGIN, UI_AXIS_EVENT_ACTION_BEGIN },
        { ORIGIN_AXIS_ACTION_UPDATE, UI_AXIS_EVENT_ACTION_UPDATE },
        { ORIGIN_AXIS_ACTION_END, UI_AXIS_EVENT_ACTION_END },
        { ORIGIN_AXIS_ACTION_CANCEL, UI_AXIS_EVENT_ACTION_CANCEL },
        { ORIGIN_AXIS_ACTION_LESS_THAN_LIMIT, UI_MOUSE_EVENT_ACTION_UNKNOWN },
        { ORIGIN_AXIS_ACTION_MORE_THAN_LIMIT, UI_MOUSE_EVENT_ACTION_UNKNOWN }
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        inputEvent.action = static_cast<AxisAction>(testCase.first);
        auto uiInputEvent =
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, &inputEvent, false, apiVersion };
        auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
        EXPECT_EQ(result, testCase.second)
            << "index = " << count << " : originAction = " << testCase.first << " , result = " << result;
        count++;
    }


    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, nullptr };
    auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_ACTION_NULL) << "index = " << count;
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetAction207
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetAction function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetAction207, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    const int32_t apiVersion = static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY);
    // 6 Other ArkUIEventTypeId
    std::vector<ArkUIEventTypeId> typeIds = {
        C_KEY_EVENT_ID,
        C_FOCUS_AXIS_EVENT_ID,
        C_HOVER_EVENT_ID
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto typeId : typeIds) {
        auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, typeId, nullptr, false, apiVersion };
        auto result = OH_ArkUI_UIInputEvent_GetAction(&uiInputEvent);
        EXPECT_EQ(result, ARKUI_EVENT_ACTION_NULL) << "other index = " << count;
        count++;
    }
}

} // namespace OHOS::Ace