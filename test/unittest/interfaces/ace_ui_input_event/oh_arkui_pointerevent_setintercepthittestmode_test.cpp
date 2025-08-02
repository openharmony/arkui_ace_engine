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
 * @tc.name: OH_ArkUI_PointerEvent_SetInterceptHitTestMode001
 * @tc.desc: Test OH_ArkUI_PointerEvent_SetInterceptHitTestMode with null event pointer
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetInterceptHitTestMode001, TestSize.Level0)
{
    auto result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(nullptr, HTM_DEFAULT);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetInterceptHitTestMode002
 * @tc.desc: Test OH_ArkUI_PointerEvent_SetInterceptHitTestMode with unsupported event type
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetInterceptHitTestMode002, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, nullptr };
    auto result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(&event, HTM_DEFAULT);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetInterceptHitTestMode101
 * @tc.desc: Test OH_ArkUI_PointerEvent_SetInterceptHitTestMode with C_TOUCH_EVENT_ID type
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetInterceptHitTestMode101, TestSize.Level0)
{
    // Prepare test data
    ArkUITouchEvent touchEvent;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &touchEvent };

    // Test HTM_DEFAULT mode
    auto result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(&event, HTM_DEFAULT);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(touchEvent.interceptResult, HTM_DEFAULT);

    // Test HTM_BLOCK mode
    result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(&event, HTM_BLOCK);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(touchEvent.interceptResult, HTM_BLOCK);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetInterceptHitTestMode102
 * @tc.desc: Test OH_ArkUI_PointerEvent_SetInterceptHitTestMode with C_MOUSE_EVENT_ID type
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetInterceptHitTestMode102, TestSize.Level0)
{
    // Prepare test data
    ArkUIMouseEvent mouseEvent;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, &mouseEvent };

    // Test HTM_TRANSPARENT mode
    auto result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(&event, HTM_TRANSPARENT);
    EXPECT_EQ(result, static_cast<int32_t>(HTM_TRANSPARENT));
    EXPECT_EQ(mouseEvent.interceptResult, HTM_TRANSPARENT);

    // Test HTM_NONE mode
    result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(&event, HTM_NONE);
    EXPECT_EQ(result, static_cast<int32_t>(HTM_NONE));
    EXPECT_EQ(mouseEvent.interceptResult, HTM_NONE);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetInterceptHitTestMode103
 * @tc.desc: Test OH_ArkUI_PointerEvent_SetInterceptHitTestMode with null inputEvent for C_MOUSE_EVENT_ID
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetInterceptHitTestMode103, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, nullptr };
    auto result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(&event, HTM_DEFAULT);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetInterceptHitTestMode104
 * @tc.desc: Test OH_ArkUI_PointerEvent_SetInterceptHitTestMode with all HitTestMode values
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetInterceptHitTestMode104, TestSize.Level0)
{
    ArkUITouchEvent touchEvent;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &touchEvent };

    // Test all possible HitTestMode values
    auto result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(&event, HTM_DEFAULT);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(touchEvent.interceptResult, HTM_DEFAULT);

    result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(&event, HTM_BLOCK);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(touchEvent.interceptResult, HTM_BLOCK);

    result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(&event, HTM_TRANSPARENT);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(touchEvent.interceptResult, HTM_TRANSPARENT);

    result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(&event, HTM_NONE);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(touchEvent.interceptResult, HTM_NONE);
}

} // namespace OHOS::Ace