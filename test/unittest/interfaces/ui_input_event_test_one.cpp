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

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetType
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetType
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetType, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    event.inputType = ARKUI_UIINPUTEVENT_TYPE_MOUSE;
    auto ret = OH_ArkUI_UIInputEvent_GetType(&event);
    EXPECT_EQ(ret, ARKUI_UIINPUTEVENT_TYPE_MOUSE);

    ret = OH_ArkUI_UIInputEvent_GetType(nullptr);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetAction
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetAction
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetAction, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_UIInputEvent_GetAction(nullptr);
    EXPECT_EQ(ret, -1);

    event.eventTypeId = C_HOVER_EVENT_ID;
    ret = OH_ArkUI_UIInputEvent_GetAction(&event);
    EXPECT_EQ(ret, -1);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUITouchEvent touchEvent;
    touchEvent.action = 1;
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_UIInputEvent_GetAction(&event);
    EXPECT_EQ(ret, 3);
    event.inputEvent = nullptr;
    ret = OH_ArkUI_UIInputEvent_GetAction(&event);
    EXPECT_EQ(ret, -1);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    ArkUIMouseEvent mouseEvent;
    mouseEvent.action = 1;
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_UIInputEvent_GetAction(&event);
    EXPECT_EQ(ret, 1);
    event.inputEvent = nullptr;
    ret = OH_ArkUI_UIInputEvent_GetAction(&event);
    EXPECT_EQ(ret, -1);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetSourceType001
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetSourceType
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetSourceType001, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_UIInputEvent_GetSourceType(nullptr);
    auto unknown = static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
    EXPECT_EQ(ret, unknown);

    event.eventTypeId = C_CLICK_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_UIInputEvent_GetSourceType(&event);
    EXPECT_EQ(ret, unknown);
    event.eventTypeId = C_MOUSE_EVENT_ID;
    ret = OH_ArkUI_UIInputEvent_GetSourceType(&event);
    EXPECT_EQ(ret, unknown);
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    ret = OH_ArkUI_UIInputEvent_GetSourceType(&event);
    EXPECT_EQ(ret, unknown);
    event.eventTypeId = C_HOVER_EVENT_ID;
    ret = OH_ArkUI_UIInputEvent_GetSourceType(&event);
    EXPECT_EQ(ret, unknown);
    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_UIInputEvent_GetSourceType(&event);
    EXPECT_EQ(ret, unknown);
}
/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetSourceType002
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetSourceType
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetSourceType002, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto unknown = static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    auto ret = OH_ArkUI_UIInputEvent_GetSourceType(&event);
    EXPECT_EQ(ret, unknown);
    ArkUITouchEvent touchEvent;
    touchEvent.sourceType = 1;
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_UIInputEvent_GetSourceType(&event);
    EXPECT_EQ(ret, 1);

    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_UIInputEvent_GetSourceType(&event);
    EXPECT_EQ(ret, unknown);
    ArkUIAxisEvent axisEvent;
    axisEvent.sourceType = 2;
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_UIInputEvent_GetSourceType(&event);
    EXPECT_EQ(ret, 2);

    event.eventTypeId = AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_UIInputEvent_GetSourceType(&event);
    EXPECT_EQ(ret, unknown);
    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.sourceType = SourceType::CROWN;
    event.inputEvent = &aceAxisEvent;
    ret = OH_ArkUI_UIInputEvent_GetSourceType(&event);
    EXPECT_EQ(ret, static_cast<int32_t>(SourceType::CROWN));
}
/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetToolType001
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetToolType
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetToolType001, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_UIInputEvent_GetSourceType(nullptr);
    auto unknown = static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);
    EXPECT_EQ(ret, unknown);

    event.eventTypeId = C_CLICK_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_UIInputEvent_GetToolType(&event);
    EXPECT_EQ(ret, unknown);
    event.eventTypeId = C_MOUSE_EVENT_ID;
    ret = OH_ArkUI_UIInputEvent_GetToolType(&event);
    EXPECT_EQ(ret, unknown);
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    ret = OH_ArkUI_UIInputEvent_GetToolType(&event);
    EXPECT_EQ(ret, unknown);
    event.eventTypeId = C_HOVER_EVENT_ID;
    ret = OH_ArkUI_UIInputEvent_GetToolType(&event);
    EXPECT_EQ(ret, unknown);
    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_UIInputEvent_GetToolType(&event);
    EXPECT_EQ(ret, unknown);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetToolType002
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetToolType
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetToolType002, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto unknown = static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    auto ret = OH_ArkUI_UIInputEvent_GetToolType(&event);
    EXPECT_EQ(ret, unknown);
    ArkUITouchEvent touchEvent;
    touchEvent.actionTouchPoint.toolType = 1;
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_UIInputEvent_GetToolType(&event);
    EXPECT_EQ(ret, OHOS::Ace::NodeModel::ConvertToCInputEventToolType(touchEvent.actionTouchPoint.toolType));

    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_UIInputEvent_GetToolType(&event);
    EXPECT_EQ(ret, unknown);
    ArkUIAxisEvent axisEvent;
    axisEvent.actionTouchPoint.toolType = 2;
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_UIInputEvent_GetToolType(&event);
    EXPECT_EQ(ret, OHOS::Ace::NodeModel::ConvertToCInputEventToolType(axisEvent.actionTouchPoint.toolType));

    event.eventTypeId = AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_UIInputEvent_GetToolType(&event);
    EXPECT_EQ(ret, unknown);
    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.sourceTool = SourceTool::JOYSTICK;
    event.inputEvent = &aceAxisEvent;
    ret = OH_ArkUI_UIInputEvent_GetToolType(&event);
    EXPECT_EQ(ret, OHOS::Ace::NodeModel::ConvertToCInputEventToolType(static_cast<int32_t>(aceAxisEvent.sourceTool)));
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTime001
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetEventTime
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTime001, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_UIInputEvent_GetEventTime(nullptr);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_CLICK_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_UIInputEvent_GetEventTime(&event);
    EXPECT_EQ(ret, 0);
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    ret = OH_ArkUI_UIInputEvent_GetEventTime(&event);
    EXPECT_EQ(ret, 0);
    event.eventTypeId = C_HOVER_EVENT_ID;
    ret = OH_ArkUI_UIInputEvent_GetEventTime(&event);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_UIInputEvent_GetEventTime(&event);
    EXPECT_EQ(ret, 0);
    ArkUITouchEvent touchEvent;
    touchEvent.timeStamp = 1;
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_UIInputEvent_GetEventTime(&event);
    EXPECT_EQ(ret, 1);

    event.eventTypeId = TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_UIInputEvent_GetEventTime(&event);
    EXPECT_EQ(ret, 0);
    OHOS::Ace::PointerEvent aceTouchEvent;
    event.inputEvent = &aceTouchEvent;
    ret = OH_ArkUI_UIInputEvent_GetEventTime(&event);
    EXPECT_EQ(ret, aceTouchEvent.time.time_since_epoch().count());
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTime002
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetEventTime
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTime002, TestSize.Level1)
{
    ArkUI_UIInputEvent event;

    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    auto ret = OH_ArkUI_UIInputEvent_GetEventTime(&event);
    EXPECT_EQ(ret, 0);
    ArkUIMouseEvent mouseEvent;
    mouseEvent.timeStamp = 2;
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_UIInputEvent_GetEventTime(&event);
    EXPECT_EQ(ret, 2);

    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_UIInputEvent_GetEventTime(&event);
    EXPECT_EQ(ret, 0);
    ArkUIAxisEvent axisEvent;
    axisEvent.timeStamp = 3;
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_UIInputEvent_GetEventTime(&event);
    EXPECT_EQ(ret, 3);

    event.eventTypeId = AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_UIInputEvent_GetEventTime(&event);
    EXPECT_EQ(ret, 0);
    OHOS::Ace::PointerEvent aceAxisEvent;
    event.inputEvent = &aceAxisEvent;
    ret = OH_ArkUI_UIInputEvent_GetEventTime(&event);
    EXPECT_EQ(ret, aceAxisEvent.time.time_since_epoch().count());

    event.eventTypeId = C_KEY_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_UIInputEvent_GetEventTime(&event);
    EXPECT_EQ(ret, 0);
    ArkUIKeyEvent keyEvent;
    keyEvent.timestamp = 4;
    event.inputEvent = &keyEvent;
    ret = OH_ArkUI_UIInputEvent_GetEventTime(&event);
    EXPECT_EQ(ret, 4);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetDeviceId001
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetDeviceId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetDeviceId001, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_UIInputEvent_GetDeviceId(nullptr);
    EXPECT_EQ(ret, -1);

    event.eventTypeId = C_CLICK_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_UIInputEvent_GetDeviceId(&event);
    EXPECT_EQ(ret, -1);
    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_UIInputEvent_GetDeviceId(&event);
    EXPECT_EQ(ret, -1);
    event.eventTypeId = C_MOUSE_EVENT_ID;
    ret = OH_ArkUI_UIInputEvent_GetDeviceId(&event);
    EXPECT_EQ(ret, -1);
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    ret = OH_ArkUI_UIInputEvent_GetDeviceId(&event);
    EXPECT_EQ(ret, -1);
    event.eventTypeId = C_HOVER_EVENT_ID;
    ret = OH_ArkUI_UIInputEvent_GetDeviceId(&event);
    EXPECT_EQ(ret, -1);
    event.eventTypeId = C_TOUCH_EVENT_ID;
    ret = OH_ArkUI_UIInputEvent_GetDeviceId(&event);
    EXPECT_EQ(ret, -1);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetDeviceId002
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetDeviceId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetDeviceId002, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    event.eventTypeId = TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    auto ret = OH_ArkUI_UIInputEvent_GetDeviceId(&event);
    EXPECT_EQ(ret, -1);
    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.deviceId = 1;
    event.inputEvent = &aceTouchEvent;
    ret = OH_ArkUI_UIInputEvent_GetDeviceId(&event);
    EXPECT_EQ(ret, static_cast<int32_t>(aceTouchEvent.deviceId));

    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_UIInputEvent_GetDeviceId(&event);
    EXPECT_EQ(ret, -1);
    ArkUIAxisEvent axisEvent;
    axisEvent.deviceId = 2;
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_UIInputEvent_GetDeviceId(&event);
    EXPECT_EQ(ret, static_cast<int32_t>(axisEvent.deviceId));

    event.eventTypeId = AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_UIInputEvent_GetDeviceId(&event);
    EXPECT_EQ(ret, -1);
    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.deviceId = 3;
    event.inputEvent = &aceAxisEvent;
    ret = OH_ArkUI_UIInputEvent_GetDeviceId(&event);
    EXPECT_EQ(ret, static_cast<int32_t>(aceAxisEvent.deviceId));
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetPressedKeys
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetPressedKeys
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetPressedKeys, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    int32_t pressedKeyCodes[3];
    int32_t length = 0;
    auto ret = OH_ArkUI_UIInputEvent_GetPressedKeys(&event, pressedKeyCodes, &length);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
    ret = OH_ArkUI_UIInputEvent_GetPressedKeys(&event, nullptr, &length);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
    ret = OH_ArkUI_UIInputEvent_GetPressedKeys(nullptr, pressedKeyCodes, &length);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ArkUIKeyEvent keyEvent;
    length = 1;
    event.inputEvent = nullptr;
    keyEvent.keyCodesLength = 2;
    ArkUI_Int32 keyPressedKeyCodes[2] = { 1, 2 };
    keyEvent.pressedKeyCodes = keyPressedKeyCodes;
    ret = OH_ArkUI_UIInputEvent_GetPressedKeys(&event, pressedKeyCodes, &length);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
    event.inputEvent = &keyEvent;
    ret = OH_ArkUI_UIInputEvent_GetPressedKeys(&event, pressedKeyCodes, &length);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH);
    length = 3;
    ret = OH_ArkUI_UIInputEvent_GetPressedKeys(&event, pressedKeyCodes, &length);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPointerCount
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetPointerCount
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPointerCount, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_GetPointerCount(nullptr);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetPointerCount(&event);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetPointerCount(&event);
    EXPECT_EQ(ret, 0);
    ArkUITouchEvent touchEvent;
    touchEvent.touchPointSize = 1;
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetPointerCount(&event);
    EXPECT_EQ(ret, 1);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetPointerCount(&event);
    EXPECT_EQ(ret, 0);
    ArkUIMouseEvent mouseEvent;
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_PointerEvent_GetPointerCount(&event);
    EXPECT_EQ(ret, 1);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetPointerCount(&event);
    EXPECT_EQ(ret, 0);
    ArkUIAxisEvent axisEvent;
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_PointerEvent_GetPointerCount(&event);
    EXPECT_EQ(ret, 1);

    event.eventTypeId = C_CLICK_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetPointerCount(&event);
    EXPECT_EQ(ret, 0);
    ArkUIClickEvent clickEvent;
    clickEvent.clickPointSize = 2;
    event.inputEvent = &clickEvent;
    ret = OH_ArkUI_PointerEvent_GetPointerCount(&event);
    EXPECT_EQ(ret, 2);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPointerId
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetPointerId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPointerId, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_GetPointerId(nullptr, 0);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetPointerId(&event, 0);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetPointerId(&event, 0);
    EXPECT_EQ(ret, 0);
    ArkUITouchEvent touchEvent;
    ArkUITouchPoint touchPointes[3];
    touchPointes[2].id = 10;
    touchEvent.touchPointSize = 3;
    touchEvent.touchPointes = touchPointes;
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetPointerId(&event, 2);
    EXPECT_EQ(ret, 10);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetPointerId(&event, 1);
    EXPECT_EQ(ret, 0);
    ArkUIMouseEvent mouseEvent;
    mouseEvent.actionTouchPoint.id = 20;
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_PointerEvent_GetPointerId(&event, 1);
    EXPECT_EQ(ret, 0);
    ret = OH_ArkUI_PointerEvent_GetPointerId(&event, 0);
    EXPECT_EQ(ret, 20);

    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetPointerId(&event, 0);
    EXPECT_EQ(ret, 0);
    ArkUIAxisEvent axisEvent;
    axisEvent.actionTouchPoint.id = 30;
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_PointerEvent_GetPointerId(&event, 1);
    EXPECT_EQ(ret, 0);
    ret = OH_ArkUI_PointerEvent_GetPointerId(&event, 0);
    EXPECT_EQ(ret, 30);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetX001
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetX001, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_GetX(nullptr);
    EXPECT_EQ(ret, 0.0f);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetX(&event);
    EXPECT_EQ(ret, 0.0f);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUITouchEvent touchEvent;
    touchEvent.actionTouchPoint.nodeX = 1.1f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetX(&event);
    EXPECT_EQ(ret, 1.1f);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    ArkUIMouseEvent mouseEvent;
    mouseEvent.actionTouchPoint.nodeX = 2.2f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_PointerEvent_GetX(&event);
    EXPECT_EQ(ret, 2.2f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetX002
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetX002, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    event.eventTypeId = C_AXIS_EVENT_ID;
    ArkUIAxisEvent axisEvent;
    axisEvent.actionTouchPoint.nodeX = 3.3f;
    event.inputEvent = nullptr;
    auto ret = OH_ArkUI_PointerEvent_GetX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_PointerEvent_GetX(&event);
    EXPECT_EQ(ret, 3.3f);

    event.eventTypeId = TOUCH_EVENT_ID;
    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.localX = 4.4f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &aceTouchEvent;
    ret = OH_ArkUI_PointerEvent_GetX(&event);
    EXPECT_EQ(ret, 4.4f);

    event.eventTypeId = AXIS_EVENT_ID;
    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.localX = 5.5f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &aceAxisEvent;
    ret = OH_ArkUI_PointerEvent_GetX(&event);
    EXPECT_EQ(ret, 5.5f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetY001
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetY001, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_GetY(nullptr);
    EXPECT_EQ(ret, 0.0f);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetY(&event);
    EXPECT_EQ(ret, 0.0f);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUITouchEvent touchEvent;
    touchEvent.actionTouchPoint.nodeY = 10.1f;
    ret = OH_ArkUI_PointerEvent_GetY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetY(&event);
    EXPECT_EQ(ret, 10.1f);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    ArkUIMouseEvent mouseEvent;
    mouseEvent.actionTouchPoint.nodeY = 20.2f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_PointerEvent_GetY(&event);
    EXPECT_EQ(ret, 20.2f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetY002
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetY002, TestSize.Level1)
{
    ArkUI_UIInputEvent event;

    event.eventTypeId = C_AXIS_EVENT_ID;
    ArkUIAxisEvent axisEvent;
    axisEvent.actionTouchPoint.nodeY = 30.3f;
    event.inputEvent = nullptr;
    auto ret = OH_ArkUI_PointerEvent_GetY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_PointerEvent_GetY(&event);
    EXPECT_EQ(ret, 30.3f);

    event.eventTypeId = TOUCH_EVENT_ID;
    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.localY = 40.4f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &aceTouchEvent;
    ret = OH_ArkUI_PointerEvent_GetY(&event);
    EXPECT_EQ(ret, 40.4f);

    // AXIS_EVENT 类型测试（Ace AxisEvent）
    event.eventTypeId = AXIS_EVENT_ID;
    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.localY = 50.5f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &aceAxisEvent;
    ret = OH_ArkUI_PointerEvent_GetY(&event);
    EXPECT_EQ(ret, 50.5f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowX001
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetWindowX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowX001, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_GetWindowX(nullptr);
    EXPECT_EQ(ret, 0.0f);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetWindowX(&event);
    EXPECT_EQ(ret, 0.0f);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUITouchEvent touchEvent;
    touchEvent.actionTouchPoint.windowX = 100.1f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetWindowX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetWindowX(&event);
    EXPECT_EQ(ret, 100.1f);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    ArkUIMouseEvent mouseEvent;
    mouseEvent.actionTouchPoint.windowX = 200.2f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetWindowX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_PointerEvent_GetWindowX(&event);
    EXPECT_EQ(ret, 200.2f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowX002
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetWindowX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowX002, TestSize.Level1)
{
    ArkUI_UIInputEvent event;

    event.eventTypeId = C_AXIS_EVENT_ID;
    ArkUIAxisEvent axisEvent;
    axisEvent.actionTouchPoint.windowX = 300.3f;
    event.inputEvent = nullptr;
    auto ret = OH_ArkUI_PointerEvent_GetWindowX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_PointerEvent_GetWindowX(&event);
    EXPECT_EQ(ret, 300.3f);

    event.eventTypeId = TOUCH_EVENT_ID;
    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.x = 400.4f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetWindowX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &aceTouchEvent;
    ret = OH_ArkUI_PointerEvent_GetWindowX(&event);
    EXPECT_EQ(ret, 400.4f);

    event.eventTypeId = AXIS_EVENT_ID;
    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.x = 500.5f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetWindowX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &aceAxisEvent;
    ret = OH_ArkUI_PointerEvent_GetWindowX(&event);
    EXPECT_EQ(ret, 500.5f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowY001
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetWindowY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowY001, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_GetWindowY(nullptr);
    EXPECT_EQ(ret, 0.0f);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetWindowY(&event);
    EXPECT_EQ(ret, 0.0f);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUITouchEvent touchEvent;
    touchEvent.actionTouchPoint.windowY = 100.1f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetWindowY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetWindowY(&event);
    EXPECT_EQ(ret, 100.1f);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    ArkUIMouseEvent mouseEvent;
    mouseEvent.actionTouchPoint.windowY = 200.2f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetWindowY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_PointerEvent_GetWindowY(&event);
    EXPECT_EQ(ret, 200.2f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowY002
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetWindowY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowY002, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    event.eventTypeId = C_AXIS_EVENT_ID;
    ArkUIAxisEvent axisEvent;
    axisEvent.actionTouchPoint.windowY = 300.3f;
    event.inputEvent = nullptr;
    auto ret = OH_ArkUI_PointerEvent_GetWindowY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_PointerEvent_GetWindowY(&event);
    EXPECT_EQ(ret, 300.3f);

    event.eventTypeId = TOUCH_EVENT_ID;
    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.y = 400.4f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetWindowY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &aceTouchEvent;
    ret = OH_ArkUI_PointerEvent_GetWindowY(&event);
    EXPECT_EQ(ret, 400.4f);

    event.eventTypeId = AXIS_EVENT_ID;
    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.y = 500.5f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetWindowY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &aceAxisEvent;
    ret = OH_ArkUI_PointerEvent_GetWindowY(&event);
    EXPECT_EQ(ret, 500.5f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayX001
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetDisplayX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayX001, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_GetDisplayX(nullptr);
    EXPECT_EQ(ret, 0.0f);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetDisplayX(&event);
    EXPECT_EQ(ret, 0.0f);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUITouchEvent touchEvent;
    touchEvent.actionTouchPoint.screenX = 100.1f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetDisplayX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetDisplayX(&event);
    EXPECT_EQ(ret, 100.1f);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    ArkUIMouseEvent mouseEvent;
    mouseEvent.actionTouchPoint.screenX = 200.2f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetDisplayX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_PointerEvent_GetDisplayX(&event);
    EXPECT_EQ(ret, 200.2f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayX002
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetDisplayX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayX002, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    event.eventTypeId = C_AXIS_EVENT_ID;
    ArkUIAxisEvent axisEvent;
    axisEvent.actionTouchPoint.screenX = 300.3f;
    event.inputEvent = nullptr;
    auto ret = OH_ArkUI_PointerEvent_GetDisplayX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_PointerEvent_GetDisplayX(&event);
    EXPECT_EQ(ret, 300.3f);

    event.eventTypeId = TOUCH_EVENT_ID;
    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.screenX = 400.4f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetDisplayX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &aceTouchEvent;
    ret = OH_ArkUI_PointerEvent_GetDisplayX(&event);
    EXPECT_EQ(ret, 400.4f);

    event.eventTypeId = AXIS_EVENT_ID;
    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.screenX = 500.5f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetDisplayX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &aceAxisEvent;
    ret = OH_ArkUI_PointerEvent_GetDisplayX(&event);
    EXPECT_EQ(ret, 500.5f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayY001
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetDisplayY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayY001, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_GetDisplayY(nullptr);
    EXPECT_EQ(ret, 0.0f);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetDisplayY(&event);
    EXPECT_EQ(ret, 0.0f);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUITouchEvent touchEvent;
    touchEvent.actionTouchPoint.screenY = 100.1f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetDisplayY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetDisplayY(&event);
    EXPECT_EQ(ret, 100.1f);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    ArkUIMouseEvent mouseEvent;
    mouseEvent.actionTouchPoint.screenY = 200.2f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetDisplayY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_PointerEvent_GetDisplayY(&event);
    EXPECT_EQ(ret, 200.2f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayY002
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetDisplayY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayY002, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    event.eventTypeId = C_AXIS_EVENT_ID;
    ArkUIAxisEvent axisEvent;
    axisEvent.actionTouchPoint.screenY = 300.3f;
    event.inputEvent = nullptr;
    auto ret = OH_ArkUI_PointerEvent_GetDisplayY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_PointerEvent_GetDisplayY(&event);
    EXPECT_EQ(ret, 300.3f);

    event.eventTypeId = TOUCH_EVENT_ID;
    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.screenY = 400.4f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetDisplayY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &aceTouchEvent;
    ret = OH_ArkUI_PointerEvent_GetDisplayY(&event);
    EXPECT_EQ(ret, 400.4f);

    event.eventTypeId = AXIS_EVENT_ID;
    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.screenY = 500.5f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetDisplayY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &aceAxisEvent;
    ret = OH_ArkUI_PointerEvent_GetDisplayY(&event);
    EXPECT_EQ(ret, 500.5f);
}
/**
 * @tc.name: OH_ArkUI_PointerEvent_GetXByIndex
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetXByIndex
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetXByIndex, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_GetXByIndex(nullptr, 0);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetXByIndex(&event, 0);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetXByIndex(&event, 0);
    EXPECT_EQ(ret, 0);
    ArkUITouchEvent touchEvent;
    ArkUITouchPoint touchPointes[3];
    touchPointes[2].nodeX = 10;
    touchEvent.touchPointSize = 3;
    touchEvent.touchPointes = touchPointes;
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetXByIndex(&event, 2);
    EXPECT_EQ(ret, 10);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetXByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ArkUIMouseEvent mouseEvent;
    mouseEvent.actionTouchPoint.nodeX = 20;
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_PointerEvent_GetXByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ret = OH_ArkUI_PointerEvent_GetXByIndex(&event, 0);
    EXPECT_EQ(ret, 20);

    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetXByIndex(&event, 0);
    EXPECT_EQ(ret, 0);
    ArkUIAxisEvent axisEvent;
    axisEvent.actionTouchPoint.nodeX = 30;
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_PointerEvent_GetXByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ret = OH_ArkUI_PointerEvent_GetXByIndex(&event, 0);
    EXPECT_EQ(ret, 30);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetYByIndex
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetYByIndex
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetYByIndex, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_GetYByIndex(nullptr, 0);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetYByIndex(&event, 0);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetYByIndex(&event, 0);
    EXPECT_EQ(ret, 0);
    ArkUITouchEvent touchEvent;
    ArkUITouchPoint touchPointes[3];
    touchPointes[2].nodeY = 10;
    touchEvent.touchPointSize = 3;
    touchEvent.touchPointes = touchPointes;
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetYByIndex(&event, 2);
    EXPECT_EQ(ret, 10);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetYByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ArkUIMouseEvent mouseEvent;
    mouseEvent.actionTouchPoint.nodeY = 20;
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_PointerEvent_GetYByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ret = OH_ArkUI_PointerEvent_GetYByIndex(&event, 0);
    EXPECT_EQ(ret, 20);

    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetYByIndex(&event, 0);
    EXPECT_EQ(ret, 0);
    ArkUIAxisEvent axisEvent;
    axisEvent.actionTouchPoint.nodeY = 30;
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_PointerEvent_GetYByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ret = OH_ArkUI_PointerEvent_GetYByIndex(&event, 0);
    EXPECT_EQ(ret, 30);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowXByIndex
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetWindowXByIndex
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowXByIndex, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_GetWindowXByIndex(nullptr, 0);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetWindowXByIndex(&event, 0);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetWindowXByIndex(&event, 0);
    EXPECT_EQ(ret, 0);
    ArkUITouchEvent touchEvent;
    ArkUITouchPoint touchPointes[3];
    touchPointes[2].windowX = 10;
    touchEvent.touchPointSize = 3;
    touchEvent.touchPointes = touchPointes;
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetWindowXByIndex(&event, 2);
    EXPECT_EQ(ret, 10);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetWindowXByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ArkUIMouseEvent mouseEvent;
    mouseEvent.actionTouchPoint.windowX = 20;
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_PointerEvent_GetWindowXByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ret = OH_ArkUI_PointerEvent_GetWindowXByIndex(&event, 0);
    EXPECT_EQ(ret, 20);

    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetWindowXByIndex(&event, 0);
    EXPECT_EQ(ret, 0);
    ArkUIAxisEvent axisEvent;
    axisEvent.actionTouchPoint.windowX = 30;
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_PointerEvent_GetWindowXByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ret = OH_ArkUI_PointerEvent_GetWindowXByIndex(&event, 0);
    EXPECT_EQ(ret, 30);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetWindowYByIndex
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetWindowYByIndex
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetWindowYByIndex, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_GetWindowYByIndex(nullptr, 0);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetWindowYByIndex(&event, 0);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetWindowYByIndex(&event, 0);
    EXPECT_EQ(ret, 0);
    ArkUITouchEvent touchEvent;
    ArkUITouchPoint touchPointes[3];
    touchPointes[2].windowY = 10;
    touchEvent.touchPointSize = 3;
    touchEvent.touchPointes = touchPointes;
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetWindowYByIndex(&event, 2);
    EXPECT_EQ(ret, 10);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetWindowYByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ArkUIMouseEvent mouseEvent;
    mouseEvent.actionTouchPoint.windowY = 20;
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_PointerEvent_GetWindowYByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ret = OH_ArkUI_PointerEvent_GetWindowYByIndex(&event, 0);
    EXPECT_EQ(ret, 20);

    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetWindowYByIndex(&event, 0);
    EXPECT_EQ(ret, 0);
    ArkUIAxisEvent axisEvent;
    axisEvent.actionTouchPoint.windowY = 30;
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_PointerEvent_GetWindowYByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ret = OH_ArkUI_PointerEvent_GetWindowYByIndex(&event, 0);
    EXPECT_EQ(ret, 30);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayXByIndex
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetDisplayXByIndex
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayXByIndex, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_GetDisplayXByIndex(nullptr, 0);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&event, 0);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&event, 0);
    EXPECT_EQ(ret, 0);
    ArkUITouchEvent touchEvent;
    ArkUITouchPoint touchPointes[3];
    touchPointes[2].screenX = 10;
    touchEvent.touchPointSize = 3;
    touchEvent.touchPointes = touchPointes;
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&event, 2);
    EXPECT_EQ(ret, 10);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ArkUIMouseEvent mouseEvent;
    mouseEvent.actionTouchPoint.screenX = 20;
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ret = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&event, 0);
    EXPECT_EQ(ret, 20);

    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&event, 0);
    EXPECT_EQ(ret, 0);
    ArkUIAxisEvent axisEvent;
    axisEvent.actionTouchPoint.screenX = 30;
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ret = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&event, 0);
    EXPECT_EQ(ret, 30);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayYByIndex
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetDisplayYByIndex
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayYByIndex, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_GetDisplayYByIndex(nullptr, 0);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&event, 0);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&event, 0);
    EXPECT_EQ(ret, 0);
    ArkUITouchEvent touchEvent;
    ArkUITouchPoint touchPointes[3];
    touchPointes[2].screenY = 10;
    touchEvent.touchPointSize = 3;
    touchEvent.touchPointes = touchPointes;
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&event, 2);
    EXPECT_EQ(ret, 10);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ArkUIMouseEvent mouseEvent;
    mouseEvent.actionTouchPoint.screenY = 20;
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ret = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&event, 0);
    EXPECT_EQ(ret, 20);

    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&event, 0);
    EXPECT_EQ(ret, 0);
    ArkUIAxisEvent axisEvent;
    axisEvent.actionTouchPoint.screenY = 30;
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ret = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&event, 0);
    EXPECT_EQ(ret, 30);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetRollAngle
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetRollAngle
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetRollAngle, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    double rollAngle = 2.0;
    auto ret = OH_ArkUI_PointerEvent_GetRollAngle(nullptr, &rollAngle);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
    ret = OH_ArkUI_PointerEvent_GetRollAngle(&event, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetRollAngle(&event, &rollAngle);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    ArkUITouchEvent touchEvent;
    touchEvent.actionTouchPoint.rollAngle = 3.0;
    touchEvent.touchPointSize = 0;
    touchEvent.subKind = ON_AXIS;
    ret = OH_ArkUI_PointerEvent_GetRollAngle(&event, &rollAngle);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetRollAngle(&event, &rollAngle);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
    touchEvent.touchPointSize = 3;
    ArkUITouchPoint pointes[3];
    pointes[2].rollAngle = 4.0;
    touchEvent.touchPointes = pointes;
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetRollAngle(&event, &rollAngle);
    EXPECT_FLOAT_EQ(rollAngle, 4.0);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    touchEvent.subKind = ON_HOVER_MOVE;
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetRollAngle(&event, &rollAngle);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_FLOAT_EQ(rollAngle, 3.0);

    event.eventTypeId = C_HOVER_EVENT_ID;
    event.inputEvent = nullptr;
    ArkUIHoverEvent hoverEvent;
    hoverEvent.rollAngle = 2.2;
    ret = OH_ArkUI_PointerEvent_GetRollAngle(&event, &rollAngle);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
    event.inputEvent = &hoverEvent;
    ret = OH_ArkUI_PointerEvent_GetRollAngle(&event, &rollAngle);
    EXPECT_FLOAT_EQ(rollAngle, 2.2);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
}
} // namespace OHOS::Ace
