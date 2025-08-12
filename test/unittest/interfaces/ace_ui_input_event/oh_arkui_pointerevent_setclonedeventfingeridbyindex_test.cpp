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
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex001
 * @tc.desc: Test with null event pointer
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex001, TestSize.Level0)
{
    auto result = OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(nullptr, 1, 0);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex002
 * @tc.desc: Test with non-cloned event
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex002, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &touchEvent, false };

    auto result = OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(&event, 1, 0);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex003
 * @tc.desc: Test with null inputEvent in cloned event
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex003, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, nullptr, true };

    auto result = OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(&event, 1, 0);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex004
 * @tc.desc: Test with invalid pointer index
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex004, TestSize.Level0)
{
    ArkUITouchPoint point = { .id = 0 };
    ArkUITouchEvent touchEvent = { .touchPointes = &point, .touchPointSize = 1 };
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };

    // Test with negative index
    auto result1 = OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(&event, 1, -1);
    EXPECT_EQ(result1, ARKUI_ERROR_CODE_PARAM_INVALID);

    // Test with index >= touchPointSize
    auto result2 = OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(&event, 1, MAX_TOUCH_POINTS);
    EXPECT_EQ(result2, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex101
 * @tc.desc: Test with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex101, TestSize.Level0)
{
    ArkUITouchPoint points[2] = { { .id = 0 }, { .id = 1 } };
    ArkUITouchEvent touchEvent = { .touchPointes = points, .touchPointSize = 2 };
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };

    const int32_t testFingerId = 5;
    auto result = OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(&event, testFingerId, 1);

    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(points[1].id, testFingerId);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex102
 * @tc.desc: Test with unsupported event type (mouse event)
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex102, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, &touchEvent, true };

    auto result = OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(&event, 1, 0);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

} // namespace OHOS::Ace