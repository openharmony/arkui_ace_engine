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
#include "interfaces/native/ui_input_event.h"
#include "interfaces/native/event/ui_input_event_impl.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {

HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPressedTimeByIndex_NullEvent, TestSize.Level0)
{
    int64_t result = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(nullptr, 0);
    EXPECT_EQ(result, 0) << "event is nullptr, should return 0";
}

HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPressedTimeByIndex_EventTypeNotTouch, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent inputEvent = {
        ARKUI_UIINPUTEVENT_TYPE_TOUCH,
        C_AXIS_EVENT_ID,
        &touchEvent
    };
    int64_t result = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(&inputEvent, 0);
    EXPECT_EQ(result, 0) << "eventTypeId != C_TOUCH_EVENT_ID, should return 0";
}

HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPressedTimeByIndex_TouchEvent_NullPoints, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    touchEvent.touchPointes = nullptr;
    touchEvent.touchPointSize = 1;
    ArkUI_UIInputEvent inputEvent = {
        ARKUI_UIINPUTEVENT_TYPE_TOUCH,
        C_TOUCH_EVENT_ID,
        &touchEvent
    };
    int64_t result = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(&inputEvent, 0);
    EXPECT_EQ(result, 0) << "touchPointes == nullptr, should return 0";
}

HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPressedTimeByIndex_TouchEvent_IndexOutOfBounds, TestSize.Level0)
{
    ArkUITouchPoint points[1] = {};
    ArkUITouchEvent touchEvent = {};
    touchEvent.touchPointes = points;
    touchEvent.touchPointSize = 1;
    ArkUI_UIInputEvent inputEvent = {
        ARKUI_UIINPUTEVENT_TYPE_TOUCH,
        C_TOUCH_EVENT_ID,
        &touchEvent
    };
    int64_t result = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(&inputEvent, 1);
    EXPECT_EQ(result, 0) << "pointerIndex >= touchPointSize, should return 0";
}

HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPressedTimeByIndex_TouchEvent_Normal, TestSize.Level0)
{
    ArkUITouchPoint points[2] = {};
    points[0].pressedTime = 123456;
    points[1].pressedTime = 789012;
    ArkUITouchEvent touchEvent = {};
    touchEvent.touchPointes = points;
    touchEvent.touchPointSize = 2;
    ArkUI_UIInputEvent inputEvent = {
        ARKUI_UIINPUTEVENT_TYPE_TOUCH,
        C_TOUCH_EVENT_ID,
        &touchEvent
    };
    int64_t result0 = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(&inputEvent, 0);
    EXPECT_EQ(result0, 123456) << "pointerIndex 0, expected 123456, got " << result0;

    int64_t result1 = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(&inputEvent, 1);
    EXPECT_EQ(result1, 789012) << "pointerIndex 1, expected 789012, got " << result1;
}

} // namespace OHOS::Ace
