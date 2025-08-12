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
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventLocalPosition001
 * @tc.desc: Test with null event pointer
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventLocalPosition001, TestSize.Level0)
{
    auto result = OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(nullptr, 10.0f, 20.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventLocalPosition002
 * @tc.desc: Test with non-cloned event
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventLocalPosition002, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &touchEvent, false };

    auto result = OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(&event, 10.0f, 20.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventLocalPosition003
 * @tc.desc: Test with null inputEvent in cloned event
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventLocalPosition003, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, nullptr, true };

    auto result = OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(&event, 10.0f, 20.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventLocalPosition101
 * @tc.desc: Test successful position setting with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventLocalPosition101, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &touchEvent, true };

    const float testX = 15.5f;
    const float testY = 25.5f;
    auto result = OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(&event, testX, testY);

    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_FLOAT_EQ(touchEvent.actionTouchPoint.nodeX, testX);
    EXPECT_FLOAT_EQ(touchEvent.actionTouchPoint.nodeY, testY);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventLocalPosition102
 * @tc.desc: Test with unsupported event type (mouse event)
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventLocalPosition102, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, &touchEvent, true };

    auto result = OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(&event, 10.0f, 20.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
}

} // namespace OHOS::Ace