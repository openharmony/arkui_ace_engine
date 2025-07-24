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
constexpr int32_t TEST_DISPLAY_ID = 123;
constexpr int32_t DEFAULT_DISPLAY_ID = 0;
constexpr ArkUIEventTypeId UNSUPPORTED_EVENT_ID = static_cast<ArkUIEventTypeId>(0xFFFF);
} // namespace

namespace OHOS::Ace {

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId001
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetTargetDisplayId function with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId001, TestSize.Level0)
{
    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(nullptr);
    EXPECT_EQ(result, DEFAULT_DISPLAY_ID);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId101
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetTargetDisplayId function with C_MOUSE_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId101, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent;
    mouseEvent.targetDisplayId = TEST_DISPLAY_ID;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, &mouseEvent };

    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(&event);
    EXPECT_EQ(result, TEST_DISPLAY_ID);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId102
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetTargetDisplayId function with C_TOUCH_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId102, TestSize.Level0)
{
    ArkUITouchEvent touchEvent;
    touchEvent.targetDisplayId = TEST_DISPLAY_ID;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &touchEvent };

    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(&event);
    EXPECT_EQ(result, TEST_DISPLAY_ID);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId103
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetTargetDisplayId function with C_AXIS_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId103, TestSize.Level0)
{
    ArkUIAxisEvent axisEvent;
    axisEvent.targetDisplayId = TEST_DISPLAY_ID;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &axisEvent };

    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(&event);
    EXPECT_EQ(result, TEST_DISPLAY_ID);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId104
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetTargetDisplayId function with C_FOCUS_AXIS_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId104, TestSize.Level0)
{
    ArkUIFocusAxisEvent focusAxisEvent;
    focusAxisEvent.targetDisplayId = TEST_DISPLAY_ID;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_FOCUS_AXIS_EVENT_ID, &focusAxisEvent };

    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(&event);
    EXPECT_EQ(result, TEST_DISPLAY_ID);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId105
 * @tc.desc: Test with TOUCH_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId105, TestSize.Level0)
{
    OHOS::Ace::PointerEvent pointerEvent;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, TOUCH_EVENT_ID, &pointerEvent };

    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(&event);
    EXPECT_GE(result, 0);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId106
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetTargetDisplayId function with AXIS_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId106, TestSize.Level0)
{
    OHOS::Ace::PointerEvent pointerEvent;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, &pointerEvent };

    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(&event);
    EXPECT_TRUE(result == DEFAULT_DISPLAY_ID || result == TEST_DISPLAY_ID);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId107
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetTargetDisplayId function with unsupported event type.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId107, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, UNSUPPORTED_EVENT_ID, nullptr };

    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(&event);
    EXPECT_EQ(result, DEFAULT_DISPLAY_ID);
}

} // namespace OHOS::Ace