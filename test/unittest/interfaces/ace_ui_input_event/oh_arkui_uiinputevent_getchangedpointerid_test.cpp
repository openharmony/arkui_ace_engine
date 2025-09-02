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

namespace {
struct ChangedPointerIdTestInputType {
    explicit ChangedPointerIdTestInputType(const ArkUI_UIInputEvent event, uint32_t* pointerIndex = nullptr,
        ArkUI_Uint32 touchPointSize = 0, ArkUI_Uint32 changedPointerId = 0)
        : event(event), pointerIndex(pointerIndex), touchPointSize(touchPointSize), changedPointerId(changedPointerId)
        {};
    ArkUI_UIInputEvent event;
    uint32_t* pointerIndex;
    ArkUI_Uint32 touchPointSize;
    ArkUI_Int32 changedPointerId;
};
} // namespace

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetChangedPointerId001
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetChangedPointerId function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetChangedPointerId001, TestSize.Level0)
{
    /**
     * @tc.steps: step1.call functions and return expected results.
     */
    auto result = OH_ArkUI_PointerEvent_GetChangedPointerId(nullptr, 0);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetChangedPointerId101
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetChangedPointerId function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetChangedPointerId101, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 1 ArkUITouchEvent {C_TOUCH_EVENT_ID, touchEvent->changedPointerId, ARKUI_ERROR_CODE_NO_ERROR}
    ArkUITouchEvent inputEvent;
    ArkUIEventTypeId eventTypeId = C_TOUCH_EVENT_ID;
    uint32_t pointerIndex = 1;

    std::vector<std::pair<ChangedPointerIdTestInputType, int32_t>> testCases = {
        // case 1.2 !pointerIndex
        { ChangedPointerIdTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent}, nullptr, 0, 0),
            ARKUI_ERROR_CODE_PARAM_INVALID },
        // case 2.1 !touchEvent
        { ChangedPointerIdTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, nullptr}, &pointerIndex, 0, 0),
            ARKUI_ERROR_CODE_PARAM_INVALID },
        // case 2.2 touchEvent->touchPointSize <= 0
        { ChangedPointerIdTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent}, &pointerIndex, 0, 0),
            ARKUI_ERROR_CODE_PARAM_INVALID },
        // case 2.3 other
        { ChangedPointerIdTestInputType(
            ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, eventTypeId, &inputEvent}, &pointerIndex, 1, 10),
            ARKUI_ERROR_CODE_PARAM_INVALID },
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        auto result = OH_ArkUI_PointerEvent_GetChangedPointerId(&input.event, input.pointerIndex);
        EXPECT_FLOAT_EQ(result, expect) << "index = " << count << ",result = " << result << ",expect = " << expect;
        count++;
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetChangedPointerId102
 * @tc.desc: Test the OH_ArkUI_PointerEvent_GetChangedPointerId function.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetChangedPointerId102, TestSize.Level0)
{
    /**
     * @tc.steps: step1.create and init ArkUI_UIInputEvent.
     */
    // 2 Other ArkUIEventTypeId
    std::vector<ArkUIEventTypeId> typeIds = {
        AXIS_EVENT_ID,
        TOUCH_EVENT_ID,
        C_MOUSE_EVENT_ID,
        C_AXIS_EVENT_ID,
        C_KEY_EVENT_ID,
        C_FOCUS_AXIS_EVENT_ID,
        C_CLICK_EVENT_ID,
        C_HOVER_EVENT_ID,
    };

    /**
     * @tc.steps: step2. Init testCases and call functions.
     * @tc.expected: Return expected results.
     */
    auto count = 0;
    uint32_t pointerIndex = 0;
    for (auto typeId : typeIds) {
        auto uiInputEvent = ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, typeId, nullptr };
        auto result = OH_ArkUI_PointerEvent_GetChangedPointerId(&uiInputEvent, &pointerIndex);
        EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID) << "other index = " << count;
        count++;
    }
}

} // namespace OHOS::Ace