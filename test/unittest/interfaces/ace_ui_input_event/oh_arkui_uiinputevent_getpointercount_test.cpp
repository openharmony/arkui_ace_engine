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
constexpr ArkUI_Uint32 ARKUI_EVENT_POINTERCOUNTER_NULL = 0;
constexpr ArkUI_Uint32 ARKUI_EVENT_POINTERCOUNTER = 2;
} // namespace

namespace OHOS::Ace {

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPointerCount001
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetPointerCount function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPointerCount001, TestSize.Level0)
{
    /**
     * @tc.steps: step1.call functions and return expected results.
     */
    auto result = OH_ArkUI_PointerEvent_GetPointerCount(nullptr);
    EXPECT_EQ(result, ARKUI_EVENT_POINTERCOUNTER_NULL);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPointerCount101
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetPointerCount function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPointerCount101, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 1 ArkUITouchEvent {C_TOUCH_EVENT_ID, touchEvent->touchPointSize}
    ArkUITouchEvent inputEvent;

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    // case 1
    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, nullptr };
    auto result = OH_ArkUI_PointerEvent_GetPointerCount(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_POINTERCOUNTER_NULL) << " , result = " << result;

    // case 2
    inputEvent.touchPointSize = ARKUI_EVENT_POINTERCOUNTER;
    uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &inputEvent };
    result = OH_ArkUI_PointerEvent_GetPointerCount(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_POINTERCOUNTER) << " , result = " << result;
}


/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPointerCount102
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetPointerCount function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPointerCount102, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 2 ArkUIMouseEvent {C_MOUSE_EVENT_ID, 1}
    ArkUIMouseEvent inputEvent;

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    // case 1
    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, nullptr };
    auto result = OH_ArkUI_PointerEvent_GetPointerCount(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_POINTERCOUNTER_NULL) << " , result = " << result;

    // case 2
    uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, &inputEvent };
    result = OH_ArkUI_PointerEvent_GetPointerCount(&uiInputEvent);
    EXPECT_EQ(result, 1) << " , result = " << result;
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPointerCount103
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetPointerCount function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPointerCount103, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 3 ArkUIAxisEvent {C_AXIS_EVENT_ID, 1}
    ArkUIAxisEvent inputEvent;

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    // case 1
    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, nullptr };
    auto result = OH_ArkUI_PointerEvent_GetPointerCount(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_POINTERCOUNTER_NULL) << " , result = " << result;

    // case 2
    uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &inputEvent };
    result = OH_ArkUI_PointerEvent_GetPointerCount(&uiInputEvent);
    EXPECT_EQ(result, 1) << " , result = " << result;
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPointerCount104
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetPointerCount function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPointerCount104, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 4 ArkUIClickEvent {C_CLICK_EVENT_ID, clickEvent->clickPointSize}
    ArkUIClickEvent inputEvent;

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    // case 1
    auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_CLICK_EVENT_ID, nullptr };
    auto result = OH_ArkUI_PointerEvent_GetPointerCount(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_POINTERCOUNTER_NULL) << " , result = " << result;

    // case 2
    inputEvent.clickPointSize = ARKUI_EVENT_POINTERCOUNTER;
    uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_CLICK_EVENT_ID, &inputEvent };
    result = OH_ArkUI_PointerEvent_GetPointerCount(&uiInputEvent);
    EXPECT_EQ(result, ARKUI_EVENT_POINTERCOUNTER) << " , result = " << result;
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPointerCount105
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetPointerCount function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPointerCount105, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 2 Other ArkUIEventTypeId
    std::vector<ArkUIEventTypeId> typeIds = {
        AXIS_EVENT_ID,
        TOUCH_EVENT_ID,
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
        auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, typeId, nullptr };
        auto result = OH_ArkUI_PointerEvent_GetPointerCount(&uiInputEvent);
        EXPECT_EQ(result, ARKUI_EVENT_POINTERCOUNTER_NULL) << "other index = " << count;
        count++;
    }
}

} // namespace OHOS::Ace