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
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId001
 * @tc.desc: Test with null event pointer
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId001, TestSize.Level0)
{
    auto result = OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(nullptr, 1);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId002
 * @tc.desc: Test with non-cloned event
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId002, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &touchEvent, false };

    auto result = OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(&event, 1);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId003
 * @tc.desc: Test with null inputEvent in cloned event
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId003, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, nullptr, true };

    auto result = OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(&event, 1);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId101
 * @tc.desc: Test with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId101, TestSize.Level0)
{
    ArkUITouchPoint touchPoint = { .id = 0 };
    ArkUITouchEvent touchEvent = { .actionTouchPoint = touchPoint };
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };

    const int32_t testFingerId = 5;
    auto result = OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(&event, testFingerId);

    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(touchEvent.actionTouchPoint.id, testFingerId);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId102
 * @tc.desc: Test with mouse event type (should be accepted)
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId102, TestSize.Level0)
{
    ArkUITouchPoint touchPoint = { .id = 0 };
    ArkUITouchEvent touchEvent = { .actionTouchPoint = touchPoint };
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, &touchEvent, true };

    const int32_t testFingerId = 1;
    auto result = OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(&event, testFingerId);

    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(touchEvent.actionTouchPoint.id, testFingerId);
}

} // namespace OHOS::Ace