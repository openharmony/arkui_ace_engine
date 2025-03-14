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

#include "ui_input_event_test.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
    
/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetModifierKeyStates001
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetModifierKeyStates
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetModifierKeyStates001, TestSize.Level1)
{
    auto state = OH_ArkUI_UIInputEvent_GetModifierKeyStates(nullptr, nullptr);
    EXPECT_EQ(state, ARKUI_ERROR_CODE_PARAM_INVALID);

    ArkUI_UIInputEvent event;
    uint64_t key = 1;

    ArkUITouchEvent touchEvent;
    touchEvent.modifierKeyState = 1;
    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    state = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &key);
    EXPECT_EQ(state, ARKUI_ERROR_CODE_PARAM_INVALID);
    event.inputEvent = &touchEvent;
    state = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &key);
    EXPECT_EQ(state, 1);

    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.modifierKeyState = 2;
    event.eventTypeId = TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    state = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &key);
    EXPECT_EQ(state, ARKUI_ERROR_CODE_PARAM_INVALID);
    event.inputEvent = &aceTouchEvent;
    state = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &key);
    EXPECT_EQ(state, 2);

    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.modifierKeyState = 3;
    event.eventTypeId = AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    state = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &key);
    EXPECT_EQ(state, ARKUI_ERROR_CODE_PARAM_INVALID);
    event.inputEvent = &aceAxisEvent;
    state = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &key);
    EXPECT_EQ(state, 3);

    ArkUIMouseEvent mouseEvent;
    mouseEvent.modifierKeyState = 4;
    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    state = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &key);
    EXPECT_EQ(state, ARKUI_ERROR_CODE_PARAM_INVALID);
    event.inputEvent = &mouseEvent;
    state = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &key);
    EXPECT_EQ(state, 4);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetModifierKeyStates002
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetModifierKeyStates
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetModifierKeyStates002, TestSize.Level1)
{
    int32_t state = 1;
    ArkUI_UIInputEvent event;
    uint64_t key = 1;

    ArkUIAxisEvent axisEvent;
    axisEvent.modifierKeyState = 5;
    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    state = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &key);
    EXPECT_EQ(state, ARKUI_ERROR_CODE_PARAM_INVALID);
    event.inputEvent = &axisEvent;
    state = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &key);
    EXPECT_EQ(state, 5);

    ArkUIFocusAxisEvent focusAxisEvent;
    focusAxisEvent.modifierKeyState = 6;
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    state = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &key);
    EXPECT_EQ(state, ARKUI_ERROR_CODE_PARAM_INVALID);
    event.inputEvent = &focusAxisEvent;
    state = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &key);
    EXPECT_EQ(state, 6);

    ArkUIHoverEvent hoverEvent;
    hoverEvent.modifierKeyState = 7;
    event.eventTypeId = C_HOVER_EVENT_ID;
    event.inputEvent = nullptr;
    state = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &key);
    EXPECT_EQ(state, ARKUI_ERROR_CODE_PARAM_INVALID);
    event.inputEvent = &hoverEvent;
    state = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &key);
    EXPECT_EQ(state, 7);

    ArkUIClickEvent clickEvent;
    clickEvent.modifierKeyState = 8;
    event.eventTypeId = C_CLICK_EVENT_ID;
    event.inputEvent = nullptr;
    state = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &key);
    EXPECT_EQ(state, ARKUI_ERROR_CODE_PARAM_INVALID);
    event.inputEvent = &clickEvent;
    state = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&event, &key);
    EXPECT_EQ(state, 8);
}

/**
 * @tc.name: OH_ArkUI_HoverEvent_IsHovered
 * @tc.desc: test OH_ArkUI_HoverEvent_IsHovered
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_HoverEvent_IsHovered, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_HoverEvent_IsHovered(nullptr);
    EXPECT_EQ(result, false);

    uiInputEvent->eventTypeId = C_HOVER_EVENT_ID;
    auto hoverEvent = std::make_unique<ArkUIHoverEvent>();
    hoverEvent->isHover = true;
    result = OH_ArkUI_HoverEvent_IsHovered(uiInputEvent.get());
    EXPECT_EQ(result, false);
    uiInputEvent->inputEvent = hoverEvent.get();
    result = OH_ArkUI_HoverEvent_IsHovered(uiInputEvent.get());
    EXPECT_EQ(result, true);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    result = OH_ArkUI_HoverEvent_IsHovered(uiInputEvent.get());
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_SetPropagation
 * @tc.desc: Test function OH_ArkUI_AxisEvent_SetPropagation
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_SetPropagation, TestSize.Level1)
{
    int32_t ret = OH_ArkUI_AxisEvent_SetPropagation(nullptr, true);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ArkUI_UIInputEvent event;
    ret = OH_ArkUI_AxisEvent_SetPropagation(&event, true);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_AxisEvent_SetPropagation(&event, true);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ArkUIAxisEvent axisEvent;
    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_AxisEvent_SetPropagation(&event, true);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_TRUE(axisEvent.propagation);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetScrollStep
 * @tc.desc: Test function OH_ArkUI_AxisEvent_GetScrollStep
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetScrollStep, TestSize.Level1)
{
    int32_t step = OH_ArkUI_AxisEvent_GetScrollStep(nullptr);
    EXPECT_EQ(step, 0);

    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.scrollStep = 5;
    ArkUI_UIInputEvent event;
    event.eventTypeId = AXIS_EVENT_ID;
    event.inputEvent = &aceAxisEvent;
    step = OH_ArkUI_AxisEvent_GetScrollStep(&event);
    EXPECT_EQ(step, 5);

    ArkUIAxisEvent axisEvent;
    axisEvent.scrollStep = 3;
    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = &axisEvent;
    step = OH_ArkUI_AxisEvent_GetScrollStep(&event);
    EXPECT_EQ(step, 3);

    event.eventTypeId = C_HOVER_EVENT_ID;
    step = OH_ArkUI_AxisEvent_GetScrollStep(&event);
    EXPECT_EQ(step, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventLocalPosition
 * @tc.desc: Test setting cloned event position
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventLocalPosition, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(nullptr, 0.0f, 0.0f);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    event.isCloned = false;
    ret = OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(&event, 0.0f, 0.0f);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);

    event.isCloned = true;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(&event, 0.0f, 0.0f);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ArkUITouchEvent touchEvent;
    touchEvent.actionTouchPoint.nodeX = 0.0f;
    touchEvent.actionTouchPoint.nodeY = 0.0f;
    event.inputEvent = &touchEvent;

    ret = OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(&event, 1.1f, 2.2f);
    EXPECT_EQ(touchEvent.actionTouchPoint.nodeX, 1.1f);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex
 * @tc.desc: Test OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(nullptr, 0.0f, 0.0f, 1);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    event.isCloned = false;
    ret = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(&event, 0.0f, 0.0f, 1);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);

    event.isCloned = true;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(&event, 0.0f, 0.0f, 1);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ArkUITouchEvent touchEvent;
    touchEvent.touchPointSize = 0;
    ArkUITouchPoint touchPointes[2];
    touchPointes[1].nodeX = 1.0f;
    touchPointes[1].nodeY = 2.0f;
    touchEvent.touchPointes = touchPointes;
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(&event, 1.1f, 2.2f, 1);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    touchEvent.touchPointSize = 2;
    event.inputEvent = &touchEvent;

    ret = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(&event, 1.1f, 2.2f, 1);
    EXPECT_EQ(touchPointes[1].nodeX, 1.1f);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventActionType
 * @tc.desc: Test OH_ArkUI_PointerEvent_SetClonedEventActionType
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventActionType, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_SetClonedEventActionType(nullptr, 1);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    event.isCloned = false;
    ret = OH_ArkUI_PointerEvent_SetClonedEventActionType(&event, 1);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);

    event.isCloned = true;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_SetClonedEventActionType(&event, 1);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ArkUITouchEvent touchEvent;
    touchEvent.action = 0;
    event.inputEvent = &touchEvent;

    ret = OH_ArkUI_PointerEvent_SetClonedEventActionType(&event, 1);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId
 * @tc.desc: Test OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(nullptr, 1);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    event.isCloned = false;
    ret = OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(&event, 1);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);

    event.isCloned = true;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(&event, 1);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ArkUITouchEvent touchEvent;
    touchEvent.actionTouchPoint.id = 0;
    event.inputEvent = &touchEvent;

    ret = OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(&event, 1);
    EXPECT_EQ(touchEvent.actionTouchPoint.id, 1);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex
 * @tc.desc: Test OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(nullptr, 1, 1);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    event.isCloned = false;
    ret = OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(&event, 1, 1);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);

    event.isCloned = true;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(&event, 1, 1);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ArkUITouchEvent touchEvent;
    touchEvent.touchPointSize = 0;
    ArkUITouchPoint touchPointes[2];
    touchPointes[1].id = 0;
    touchPointes[1].nodeY = 2.0f;
    touchEvent.touchPointes = touchPointes;
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(&event, 1, 1);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    touchEvent.touchPointSize = 2;
    event.inputEvent = &touchEvent;

    ret = OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(&event, 1, 1);
    EXPECT_EQ(touchPointes[1].id, 1);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
}
} // namespace OHOS::Ace
