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
constexpr uint64_t TEST_MODIFIER_KEYS = 0x12345678;
} // namespace

namespace OHOS::Ace {

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetModifierKeyStates001
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetModifierKeyStates function with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetModifierKeyStates001, TestSize.Level0)
{
    uint64_t keys = 0;
    auto result = OH_ArkUI_UIInputEvent_GetModifierKeyStates(nullptr, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    result = OH_ArkUI_UIInputEvent_GetModifierKeyStates(nullptr, &keys);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, nullptr };
    result = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetModifierKeyStates101
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetModifierKeyStates function with C_TOUCH_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetModifierKeyStates101, TestSize.Level0)
{
    ArkUITouchEvent touchEvent;
    touchEvent.modifierKeyState = TEST_MODIFIER_KEYS;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &touchEvent };
    uint64_t keys = 0;

    auto result = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &keys);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(keys, TEST_MODIFIER_KEYS);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetModifierKeyStates102
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetModifierKeyStates function with TOUCH_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetModifierKeyStates102, TestSize.Level0)
{
    OHOS::Ace::PointerEvent pointerEvent;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, TOUCH_EVENT_ID, &pointerEvent };
    uint64_t keys = 0;

    auto result = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &keys);
    EXPECT_TRUE(result == ARKUI_ERROR_CODE_NO_ERROR || result == ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetModifierKeyStates103
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetModifierKeyStates function with AXIS_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetModifierKeyStates103, TestSize.Level0)
{
    OHOS::Ace::PointerEvent pointerEvent;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, &pointerEvent };
    uint64_t keys = 0;

    auto result = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &keys);
    EXPECT_TRUE(result == ARKUI_ERROR_CODE_NO_ERROR || result == ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetModifierKeyStates104
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetModifierKeyStates function with C_MOUSE_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetModifierKeyStates104, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent;
    mouseEvent.modifierKeyState = TEST_MODIFIER_KEYS;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, &mouseEvent };
    uint64_t keys = 0;

    auto result = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &keys);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(keys, TEST_MODIFIER_KEYS);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetModifierKeyStates105
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetModifierKeyStates function with C_AXIS_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetModifierKeyStates105, TestSize.Level0)
{
    ArkUIAxisEvent axisEvent;
    axisEvent.modifierKeyState = TEST_MODIFIER_KEYS;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &axisEvent };
    uint64_t keys = 0;

    auto result = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &keys);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(keys, TEST_MODIFIER_KEYS);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetModifierKeyStates106
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetModifierKeyStates function with C_KEY_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetModifierKeyStates106, TestSize.Level0)
{
    ArkUIKeyEvent keyEvent;
    keyEvent.modifierKeyState = TEST_MODIFIER_KEYS;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_KEY_EVENT_ID, &keyEvent };
    uint64_t keys = 0;

    auto result = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &keys);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(keys, TEST_MODIFIER_KEYS);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetModifierKeyStates107
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetModifierKeyStates function with C_FOCUS_AXIS_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetModifierKeyStates107, TestSize.Level0)
{
    ArkUIFocusAxisEvent focusAxisEvent;
    focusAxisEvent.modifierKeyState = TEST_MODIFIER_KEYS;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_FOCUS_AXIS_EVENT_ID, &focusAxisEvent };
    uint64_t keys = 0;

    auto result = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &keys);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(keys, TEST_MODIFIER_KEYS);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetModifierKeyStates108
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetModifierKeyStates function with C_HOVER_EVENT_ID.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetModifierKeyStates108, TestSize.Level0)
{
    ArkUIHoverEvent hoverEvent;
    hoverEvent.modifierKeyState = TEST_MODIFIER_KEYS;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_HOVER_EVENT_ID, &hoverEvent };
    uint64_t keys = 0;

    auto result = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &keys);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(keys, TEST_MODIFIER_KEYS);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetModifierKeyStates109
 * @tc.desc: Test the OH_ArkUI_UIInputEvent_GetModifierKeyStates function with C_CLICK_EVENT_ID.


 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetModifierKeyStates109, TestSize.Level0)
{
    ArkUIClickEvent clickEvent;
    clickEvent.modifierKeyState = TEST_MODIFIER_KEYS;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_CLICK_EVENT_ID, &clickEvent };
    uint64_t keys = 0;

    auto result = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &keys);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(keys, TEST_MODIFIER_KEYS);
}

} // namespace OHOS::Ace