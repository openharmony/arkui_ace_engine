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

constexpr int32_t MAX_TOUCH_POINTS = 10;

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex001
 * @tc.desc: Test with null event pointer
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex001, TestSize.Level0)
{
    auto result = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(nullptr, 10.0f, 20.0f, 0);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex002
 * @tc.desc: Test with non-cloned event
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex002, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = {
        ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &touchEvent,
        false // isCloned
    };

    auto result = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(&event, 10.0f, 20.0f, 0);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex003
 * @tc.desc: Test with null inputEvent in cloned event
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex003, TestSize.Level0)
{
    ArkUI_UIInputEvent event = {
        ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, nullptr,
        true // isCloned
    };

    auto result = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(&event, 10.0f, 20.0f, 0);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex004
 * @tc.desc: Test with invalid pointer index (assuming MAX_TOUCH_POINTS is defined)
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex004, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = {
        ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &touchEvent,
        true // isCloned
    };

    // Test with negative index
    auto result1 = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(&event, 10.0f, 20.0f, -1);
    EXPECT_EQ(result1, ARKUI_ERROR_CODE_PARAM_INVALID);

    auto result2 = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(&event, 10.0f, 20.0f, MAX_TOUCH_POINTS);
    EXPECT_EQ(result2, ARKUI_ERROR_CODE_PARAM_INVALID);
}
/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex101
 * @tc.desc: Test the OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex function with valid parameters.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex101, TestSize.Level0)
{
    ArkUITouchPoint point = { .nodeX = 0.0f, .nodeY = 0.0f };
    ArkUITouchEvent touchEvent = { .touchPointes = &point, .touchPointSize = 1 };

    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };

    const float testX = 15.5f;
    const float testY = 25.5f;
    auto result = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(&event, testX, testY, 0);

    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_FLOAT_EQ(point.nodeX, testX);
    EXPECT_FLOAT_EQ(point.nodeY, testY);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex102
 * @tc.desc: Test with unsupported event type (mouse event)
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex102, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = {
        ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, &touchEvent,
        true // isCloned
    };

    auto result = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(&event, 10.0f, 20.0f, 0);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

} // namespace OHOS::Ace