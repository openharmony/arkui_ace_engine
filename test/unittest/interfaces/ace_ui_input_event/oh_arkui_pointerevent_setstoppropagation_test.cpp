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
 * @tc.name: OH_ArkUI_PointerEvent_SetStopPropagation001
 * @tc.desc: Test OH_ArkUI_PointerEvent_SetStopPropagation with null event pointer
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetStopPropagation001, TestSize.Level0)
{
    auto result = OH_ArkUI_PointerEvent_SetStopPropagation(nullptr, true);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetStopPropagation002
 * @tc.desc: Test OH_ArkUI_PointerEvent_SetStopPropagation with unsupported event type
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetStopPropagation002, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, nullptr };
    auto result = OH_ArkUI_PointerEvent_SetStopPropagation(&event, true);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetStopPropagation101
 * @tc.desc: Test OH_ArkUI_PointerEvent_SetStopPropagation with C_TOUCH_EVENT_ID type
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetStopPropagation101, TestSize.Level0)
{
    // Prepare test data
    ArkUITouchEvent touchEvent;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &touchEvent };

    // Test stop propagation true
    auto result = OH_ArkUI_PointerEvent_SetStopPropagation(&event, true);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_TRUE(touchEvent.stopPropagation);

    // Test stop propagation false
    result = OH_ArkUI_PointerEvent_SetStopPropagation(&event, false);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_FALSE(touchEvent.stopPropagation);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetStopPropagation102
 * @tc.desc: Test OH_ArkUI_PointerEvent_SetStopPropagation with C_MOUSE_EVENT_ID type
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetStopPropagation102, TestSize.Level0)
{
    // Prepare test data
    ArkUIMouseEvent mouseEvent;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, &mouseEvent };

    // Test stop propagation true
    auto result = OH_ArkUI_PointerEvent_SetStopPropagation(&event, true);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_TRUE(mouseEvent.stopPropagation);

    // Test stop propagation false
    result = OH_ArkUI_PointerEvent_SetStopPropagation(&event, false);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_FALSE(mouseEvent.stopPropagation);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetStopPropagation103
 * @tc.desc: Test OH_ArkUI_PointerEvent_SetStopPropagation with C_HOVER_EVENT_ID type
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetStopPropagation103, TestSize.Level0)
{
    // Prepare test data
    ArkUIHoverEvent hoverEvent;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_HOVER_EVENT_ID, &hoverEvent };

    // Test stop propagation true
    auto result = OH_ArkUI_PointerEvent_SetStopPropagation(&event, true);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_TRUE(hoverEvent.stopPropagation);

    // Test stop propagation false
    result = OH_ArkUI_PointerEvent_SetStopPropagation(&event, false);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_FALSE(hoverEvent.stopPropagation);
}

} // namespace OHOS::Ace