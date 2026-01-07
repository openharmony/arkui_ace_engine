/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "node_model.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
namespace {
constexpr int32_t ARKUI_DEVICE_ID = 1;
constexpr float ARKUI_X = 2.0;
constexpr float ARKUI_Y = 3.0;
constexpr int32_t ARKUI_FINGERID = 1;
constexpr int32_t ARKUI_FINGERID_SET = 0;
constexpr ArkUI_Uint64 ARKUI_MODIFIERKEYSTATE = 1;
} // namespace

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetPositionY001
 * @tc.desc: Test function OH_ArkUI_UIInputEvent_GetEventTargetPositionY.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetPositionY001, TestSize.Level1)
{
    float positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(nullptr);
    EXPECT_EQ(positionY, 0.0f);

    ArkUI_UIInputEvent event;

    ArkUITouchEvent touchEvent;
    touchEvent.targetPositionY = 150.5f;
    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &touchEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 150.5f);

    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.targetPositionY = 250.5f;
    event.eventTypeId = TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &aceTouchEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 250.5f);

    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.targetPositionY = 350.5f;
    event.eventTypeId = AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &aceAxisEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 350.5f);

    ArkUIMouseEvent mouseEvent;
    mouseEvent.targetPositionY = 450.5f;
    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &mouseEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 450.5f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetPositionY002
 * @tc.desc: Test function OH_ArkUI_UIInputEvent_GetEventTargetPositionY.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetPositionY002, TestSize.Level1)
{
    float positionY = 1.0f;
    ArkUI_UIInputEvent event;

    ArkUIAxisEvent axisEvent;
    axisEvent.targetPositionY = 550.5f;
    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &axisEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 550.5f);

    ArkUIFocusAxisEvent focusAxisEvent;
    focusAxisEvent.targetPositionY = 650.5f;
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &focusAxisEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 650.5f);

    ArkUIHoverEvent hoverEvent;
    hoverEvent.targetPositionY = 750.5f;
    event.eventTypeId = C_HOVER_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &hoverEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 750.5f);

    ArkUIClickEvent clickEvent;
    clickEvent.targetPositionY = 850.5f;
    event.eventTypeId = C_CLICK_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &clickEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(&event);
    EXPECT_EQ(positionY, 850.5f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX001
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX001, TestSize.Level1)
{
    float positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(nullptr);
    EXPECT_EQ(positionX, 0.0f);

    ArkUI_UIInputEvent event;

    ArkUITouchEvent touchEvent;
    touchEvent.targetGlobalPositionX = 1234.56f;
    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &touchEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 1234.56f);

    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.targetGlobalPositionX = 2345.67f;
    event.eventTypeId = TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &aceTouchEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 2345.67f);

    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.targetGlobalPositionX = 3456.78f;
    event.eventTypeId = AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &aceAxisEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 3456.78f);

    ArkUIMouseEvent mouseEvent;
    mouseEvent.targetGlobalPositionX = 4567.89f;
    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &mouseEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 4567.89f);
}
/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX002
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX002, TestSize.Level1)
{
    float positionX = 1.0f;
    ArkUI_UIInputEvent event;

    ArkUIAxisEvent axisEvent;
    axisEvent.targetGlobalPositionX = 5678.90f;
    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &axisEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 5678.90f);

    ArkUIFocusAxisEvent focusAxisEvent;
    focusAxisEvent.targetGlobalPositionX = 6789.01f;
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &focusAxisEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 6789.01f);

    ArkUIHoverEvent hoverEvent;
    hoverEvent.targetGlobalPositionX = 7890.12f;
    event.eventTypeId = C_HOVER_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &hoverEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 7890.12f);

    ArkUIClickEvent clickEvent;
    clickEvent.targetGlobalPositionX = 8901.23f;
    event.eventTypeId = C_CLICK_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &clickEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&event);
    EXPECT_EQ(positionX, 8901.23f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY001
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY001, TestSize.Level1)
{
    float positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(nullptr);
    EXPECT_EQ(positionY, 0.0f);

    ArkUI_UIInputEvent event;

    ArkUITouchEvent touchEvent;
    touchEvent.targetGlobalPositionY = 1122.33f;
    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &touchEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 1122.33f);

    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.targetGlobalPositionY = 2233.44f;
    event.eventTypeId = TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &aceTouchEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 2233.44f);

    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.targetGlobalPositionY = 3344.55f;
    event.eventTypeId = AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &aceAxisEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 3344.55f);

    ArkUIMouseEvent mouseEvent;
    mouseEvent.targetGlobalPositionY = 4455.66f;
    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &mouseEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 4455.66f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY002
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY002, TestSize.Level1)
{
    float positionY = 1.0f;
    ArkUI_UIInputEvent event;

    ArkUIAxisEvent axisEvent;
    axisEvent.targetGlobalPositionY = 5566.77f;
    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &axisEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 5566.77f);

    ArkUIFocusAxisEvent focusAxisEvent;
    focusAxisEvent.targetGlobalPositionY = 6677.88f;
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &focusAxisEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 6677.88f);

    ArkUIHoverEvent hoverEvent;
    hoverEvent.targetGlobalPositionY = 7788.99f;
    event.eventTypeId = C_HOVER_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &hoverEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 7788.99f);

    ArkUIClickEvent clickEvent;
    clickEvent.targetGlobalPositionY = 8899.00f;
    event.eventTypeId = C_CLICK_EVENT_ID;
    event.inputEvent = nullptr;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 0.0f);
    event.inputEvent = &clickEvent;
    positionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&event);
    EXPECT_EQ(positionY, 8899.00f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_CreateClonedEvent001
 * @tc.desc: Test OH_ArkUI_PointerEvent_CreateClonedEvent
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_CreateClonedEvent001, TestSize.Level1)
{
    ArkUI_UIInputEvent* inputEvent = nullptr;
    ArkUI_UIInputEvent* clonedEvent;
    int32_t res = OH_ArkUI_PointerEvent_CreateClonedEvent(inputEvent, &clonedEvent);
    EXPECT_EQ(res, 401);
    inputEvent = new ArkUI_UIInputEvent();
    inputEvent->inputEvent = nullptr;
    res = OH_ArkUI_PointerEvent_CreateClonedEvent(inputEvent, &clonedEvent);
    EXPECT_EQ(res, 0);
    ArkUITouchEvent* touchEvent = new ArkUITouchEvent();
    inputEvent->inputEvent = touchEvent;
    inputEvent->isCloned = false;
    res = OH_ArkUI_PointerEvent_CreateClonedEvent(inputEvent, &clonedEvent);
    EXPECT_EQ(res, 0);
    inputEvent->isCloned = true;
    res = OH_ArkUI_PointerEvent_CreateClonedEvent(inputEvent, &clonedEvent);
    EXPECT_EQ(res, 0);
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent1;
    event.touchEvent.changedPointerId = 1;
    event.touchEvent.touchPointSize = 1;
    uiInputEvent1.inputEvent = &event.touchEvent;
    uiInputEvent1.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent1;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);
    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);

    touchEvent->target.id = touchEvenInput->target.id;
    touchEvent->target.type = touchEvenInput->target.type;
    touchEvent->target.area = touchEvenInput->target.area;
    touchEvent->target.origin = touchEvenInput->target.origin;
    touchEvent->action = touchEvenInput->action;
    touchEvent->changedPointerId = touchEvenInput->changedPointerId;
    touchEvent->actionTouchPoint = touchEvenInput->actionTouchPoint;
    touchEvent->timeStamp = touchEvenInput->timeStamp;
    touchEvent->sourceType = touchEvenInput->sourceType;
    touchEvent->targetDisplayId = touchEvenInput->targetDisplayId;
    touchEvent->deviceId = touchEvenInput->deviceId;
    res = OH_ArkUI_PointerEvent_CreateClonedEvent(inputEvent, &clonedEvent);
    EXPECT_EQ(res, 401);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_DestroyClonedEvent001
 * @tc.desc: Test OH_ArkUI_PointerEvent_DestroyClonedEvent
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_DestroyClonedEvent001, TestSize.Level1)
{
    ArkUI_UIInputEvent* inputEvent = nullptr;
    ArkUI_UIInputEvent* clonedEvent;
    inputEvent = new ArkUI_UIInputEvent();
    inputEvent->inputEvent = nullptr;
    ArkUITouchEvent* touchEvent = new ArkUITouchEvent();
    inputEvent->inputEvent = touchEvent;
    inputEvent->isCloned = false;
    inputEvent->isCloned = true;
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent1;
    event.touchEvent.changedPointerId = 1;
    event.touchEvent.touchPointSize = 1;
    uiInputEvent1.inputEvent = &event.touchEvent;
    uiInputEvent1.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent1;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);
    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);

    touchEvent->target.id = touchEvenInput->target.id;
    touchEvent->target.type = touchEvenInput->target.type;
    touchEvent->target.area = touchEvenInput->target.area;
    touchEvent->target.origin = touchEvenInput->target.origin;
    touchEvent->action = touchEvenInput->action;
    touchEvent->changedPointerId = touchEvenInput->changedPointerId;
    touchEvent->actionTouchPoint = touchEvenInput->actionTouchPoint;
    touchEvent->timeStamp = touchEvenInput->timeStamp;
    touchEvent->sourceType = touchEvenInput->sourceType;
    touchEvent->targetDisplayId = touchEvenInput->targetDisplayId;
    touchEvent->deviceId = touchEvenInput->deviceId;

    auto res = OH_ArkUI_PointerEvent_CreateClonedEvent(inputEvent, &clonedEvent);
    EXPECT_EQ(res, 401);

    auto res1 = OH_ArkUI_PointerEvent_DestroyClonedEvent(clonedEvent);
    EXPECT_EQ(res1, 401);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventLocalPosition001
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventLocalPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    event.touchEvent.actionTouchPoint.nodeX = ARKUI_X;
    event.touchEvent.actionTouchPoint.nodeY = ARKUI_Y;
    // deviceid
    event.touchEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.touchEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);
    event.touchEvent.target.id = touchEvenInput->target.id;
    event.touchEvent.target.type = touchEvenInput->target.type;
    event.touchEvent.target.area = touchEvenInput->target.area;
    event.touchEvent.target.origin = touchEvenInput->target.origin;
    event.touchEvent.action = touchEvenInput->action;
    event.touchEvent.changedPointerId = touchEvenInput->changedPointerId;
    event.touchEvent.actionTouchPoint = touchEvenInput->actionTouchPoint;
    event.touchEvent.timeStamp = touchEvenInput->timeStamp;
    event.touchEvent.sourceType = touchEvenInput->sourceType;
    event.touchEvent.targetDisplayId = touchEvenInput->targetDisplayId;
    event.touchEvent.deviceId = touchEvenInput->deviceId;

    auto nodeX = ARKUI_X - 1;
    auto nodeY = ARKUI_Y - 1;
    
    auto res = OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(inputEvent, nodeX, nodeY);
    EXPECT_EQ(res, 180003);
    auto x = OH_ArkUI_PointerEvent_GetX(inputEvent);
    auto y = OH_ArkUI_PointerEvent_GetY(inputEvent);
    EXPECT_EQ(x, ARKUI_X);
    EXPECT_EQ(y, ARKUI_Y);
    inputEvent->isCloned = true;
    res = OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(inputEvent, nodeX, nodeY);
    EXPECT_EQ(res, 0);
    auto x1 = OH_ArkUI_PointerEvent_GetX(inputEvent);
    auto y1 = OH_ArkUI_PointerEvent_GetY(inputEvent);
    EXPECT_EQ(x1, ARKUI_X - 1);
    EXPECT_EQ(y1, ARKUI_Y - 1);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex001
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    event.touchEvent.actionTouchPoint.nodeX = ARKUI_X;
    event.touchEvent.actionTouchPoint.nodeY = ARKUI_Y;
    // deviceid
    event.touchEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.touchEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);
    auto nodeX = ARKUI_X - 1;
    auto nodeY = ARKUI_Y - 1;
    
    auto res = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(inputEvent, nodeX, nodeY, 0);
    EXPECT_EQ(res, 180003);
    auto x = OH_ArkUI_PointerEvent_GetXByIndex(inputEvent, 0);
    auto y = OH_ArkUI_PointerEvent_GetYByIndex(inputEvent, 0);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 0);
    inputEvent->isCloned = true;
    res = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(inputEvent, nodeX, nodeY, 0);
    EXPECT_EQ(res, 401);
    auto x1 = OH_ArkUI_PointerEvent_GetXByIndex(inputEvent, 0);
    auto y1 = OH_ArkUI_PointerEvent_GetYByIndex(inputEvent, 0);
    EXPECT_EQ(x1, 0);
    EXPECT_EQ(y1, 0);

    ArkUITouchPoint points[2]; // 2 points
    points[0].nodeX = ARKUI_X;
    points[1].nodeY = ARKUI_Y;
    event.touchEvent.touchPointes = points;
    inputEvent->isCloned = false;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);
    event.touchEvent.target.id = touchEvenInput->target.id;
    event.touchEvent.target.type = touchEvenInput->target.type;
    event.touchEvent.target.area = touchEvenInput->target.area;
    event.touchEvent.target.origin = touchEvenInput->target.origin;
    event.touchEvent.action = touchEvenInput->action;
    event.touchEvent.changedPointerId = touchEvenInput->changedPointerId;
    event.touchEvent.actionTouchPoint = touchEvenInput->actionTouchPoint;
    event.touchEvent.timeStamp = touchEvenInput->timeStamp;
    event.touchEvent.sourceType = touchEvenInput->sourceType;
    event.touchEvent.targetDisplayId = touchEvenInput->targetDisplayId;
    event.touchEvent.deviceId = touchEvenInput->deviceId;

    res = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(inputEvent, nodeX, nodeY, 0);
    EXPECT_EQ(res, 180003);
    x = OH_ArkUI_PointerEvent_GetXByIndex(inputEvent, 0);
    y = OH_ArkUI_PointerEvent_GetYByIndex(inputEvent, 0);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 0);
    inputEvent->isCloned = true;
    res = OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(inputEvent, nodeX, nodeY, 0);
    EXPECT_EQ(res, 401);
    x1 = OH_ArkUI_PointerEvent_GetXByIndex(inputEvent, 0);
    y1 = OH_ArkUI_PointerEvent_GetYByIndex(inputEvent, 0);
    EXPECT_EQ(x1, 0);
    EXPECT_EQ(y1, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId001
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    event.touchEvent.actionTouchPoint.nodeX = ARKUI_X;
    event.touchEvent.actionTouchPoint.nodeY = ARKUI_Y;
    // deviceid
    event.touchEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.touchEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    event.touchEvent.action = ARKUI_FINGERID;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);
    event.touchEvent.target.id = touchEvenInput->target.id;
    event.touchEvent.target.type = touchEvenInput->target.type;
    event.touchEvent.target.area = touchEvenInput->target.area;
    event.touchEvent.target.origin = touchEvenInput->target.origin;
    event.touchEvent.action = touchEvenInput->action;
    event.touchEvent.changedPointerId = touchEvenInput->changedPointerId;
    event.touchEvent.actionTouchPoint = touchEvenInput->actionTouchPoint;
    event.touchEvent.timeStamp = touchEvenInput->timeStamp;
    event.touchEvent.sourceType = touchEvenInput->sourceType;
    event.touchEvent.targetDisplayId = touchEvenInput->targetDisplayId;
    event.touchEvent.deviceId = touchEvenInput->deviceId;

    auto res = OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(inputEvent, ARKUI_FINGERID_SET);
    auto pointerId = OH_ArkUI_PointerEvent_GetPointerId(inputEvent, 0);
    EXPECT_EQ(res, 180003);
    EXPECT_EQ(pointerId, 0);
    inputEvent->isCloned = true;
    res = OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(inputEvent, ARKUI_FINGERID_SET);
    pointerId = OH_ArkUI_PointerEvent_GetPointerId(inputEvent, 0);
    EXPECT_EQ(res, 0);
    EXPECT_EQ(pointerId, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex001
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    event.touchEvent.actionTouchPoint.nodeX = ARKUI_X;
    event.touchEvent.actionTouchPoint.nodeY = ARKUI_Y;
    // deviceid
    event.touchEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.touchEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    event.touchEvent.action = ARKUI_FINGERID;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);
    event.touchEvent.target.id = touchEvenInput->target.id;
    event.touchEvent.target.type = touchEvenInput->target.type;
    event.touchEvent.target.area = touchEvenInput->target.area;
    event.touchEvent.target.origin = touchEvenInput->target.origin;
    event.touchEvent.action = touchEvenInput->action;
    event.touchEvent.changedPointerId = touchEvenInput->changedPointerId;
    event.touchEvent.actionTouchPoint = touchEvenInput->actionTouchPoint;
    event.touchEvent.timeStamp = touchEvenInput->timeStamp;
    event.touchEvent.sourceType = touchEvenInput->sourceType;
    event.touchEvent.targetDisplayId = touchEvenInput->targetDisplayId;
    event.touchEvent.deviceId = touchEvenInput->deviceId;

    auto res = OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(inputEvent, ARKUI_FINGERID_SET, 0);
    auto pointerId = OH_ArkUI_PointerEvent_GetPointerId(inputEvent, 0);
    EXPECT_EQ(res, 180003);
    EXPECT_EQ(pointerId, 0);
    inputEvent->isCloned = true;
    res = OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(inputEvent, ARKUI_FINGERID_SET, 0);
    pointerId = OH_ArkUI_PointerEvent_GetPointerId(inputEvent, 0);
    EXPECT_EQ(res, 401);
    EXPECT_EQ(pointerId, 0);

    ArkUITouchPoint points[2]; // 2 points
    points[0].id = ARKUI_FINGERID;
    points[1].id = ARKUI_FINGERID;
    event.touchEvent.touchPointes = points;
    inputEvent->isCloned = true;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    res = OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(inputEvent, ARKUI_FINGERID_SET, 0);
    pointerId = OH_ArkUI_PointerEvent_GetPointerId(inputEvent, 0);
    EXPECT_EQ(res, 401);
    EXPECT_EQ(pointerId, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_PostClonedEvent001
 * @tc.desc: Test OH_ArkUI_UIInputEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_PostClonedEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    event.touchEvent.actionTouchPoint.nodeX = ARKUI_X;
    event.touchEvent.actionTouchPoint.nodeY = ARKUI_Y;
    // deviceid
    event.touchEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.touchEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);
    ArkUI_NodeHandle nodeHandle = nullptr;

    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);
    event.touchEvent.target.id = touchEvenInput->target.id;
    event.touchEvent.target.type = touchEvenInput->target.type;
    event.touchEvent.target.area = touchEvenInput->target.area;
    event.touchEvent.target.origin = touchEvenInput->target.origin;
    event.touchEvent.action = touchEvenInput->action;
    event.touchEvent.changedPointerId = touchEvenInput->changedPointerId;
    event.touchEvent.actionTouchPoint = touchEvenInput->actionTouchPoint;
    event.touchEvent.timeStamp = touchEvenInput->timeStamp;
    event.touchEvent.sourceType = touchEvenInput->sourceType;
    event.touchEvent.targetDisplayId = touchEvenInput->targetDisplayId;
    event.touchEvent.deviceId = touchEvenInput->deviceId;
    inputEvent->isCloned = true;
    auto res = OH_ArkUI_PointerEvent_PostClonedEvent(nodeHandle, inputEvent);
    EXPECT_EQ(res, 180004);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_SetPropagation001
 * @tc.desc: Test OH_ArkUI_AxisEvent_SetPropagation functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_SetPropagation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    event.touchEvent.actionTouchPoint.nodeX = ARKUI_X;
    event.touchEvent.actionTouchPoint.nodeY = ARKUI_Y;
    // deviceid
    event.touchEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.touchEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    event.touchEvent.action = ARKUI_FINGERID;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);
    event.touchEvent.target.id = touchEvenInput->target.id;
    event.touchEvent.target.type = touchEvenInput->target.type;
    event.touchEvent.target.area = touchEvenInput->target.area;
    event.touchEvent.target.origin = touchEvenInput->target.origin;
    event.touchEvent.action = touchEvenInput->action;
    event.touchEvent.changedPointerId = touchEvenInput->changedPointerId;
    event.touchEvent.actionTouchPoint = touchEvenInput->actionTouchPoint;
    event.touchEvent.timeStamp = touchEvenInput->timeStamp;
    event.touchEvent.sourceType = touchEvenInput->sourceType;
    event.touchEvent.targetDisplayId = touchEvenInput->targetDisplayId;
    event.touchEvent.deviceId = touchEvenInput->deviceId;

    ArkUI_UIInputEvent setEvent;
    ArkUIAxisEvent cAxisEvent;
    cAxisEvent.propagation = true;
    setEvent.inputEvent = &cAxisEvent;
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    auto res = OH_ArkUI_AxisEvent_SetPropagation(nullptr, true);
    EXPECT_EQ(res, 401);
    res = OH_ArkUI_AxisEvent_SetPropagation(&setEvent, true);
    EXPECT_EQ(res, 0);
    cAxisEvent.propagation = false;
    setEvent.inputEvent = &cAxisEvent;
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_AxisEvent_SetPropagation(&setEvent, false);
    EXPECT_EQ(res, 0);
    cAxisEvent.propagation = true;
    setEvent.inputEvent = &cAxisEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    res = OH_ArkUI_AxisEvent_SetPropagation(&setEvent, true);
    EXPECT_EQ(res, 401);
    cAxisEvent.propagation = false;
    setEvent.inputEvent = &cAxisEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    res = OH_ArkUI_AxisEvent_SetPropagation(&setEvent, false);
    EXPECT_EQ(res, 401);
}

/**
 * @tc.name: OH_ArkUI_HoverEvent_IsHovered001
 * @tc.desc: Test OH_ArkUI_HoverEvent_IsHovered functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_HoverEvent_IsHovered001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = TOUCH_EVENT;
    event.touchEvent.actionTouchPoint.nodeX = ARKUI_X;
    event.touchEvent.actionTouchPoint.nodeY = ARKUI_Y;
    // deviceid
    event.touchEvent.deviceId = ARKUI_DEVICE_ID;
    // modifierkeystates
    event.touchEvent.modifierKeyState = ARKUI_MODIFIERKEYSTATE;
    uiInputEvent.inputEvent = &event.touchEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    event.touchEvent.action = ARKUI_FINGERID;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    auto* touchEvenInput = reinterpret_cast<ArkUITouchEvent*>(inputEvent->inputEvent);
    event.touchEvent.target.id = touchEvenInput->target.id;
    event.touchEvent.target.type = touchEvenInput->target.type;
    event.touchEvent.target.area = touchEvenInput->target.area;
    event.touchEvent.target.origin = touchEvenInput->target.origin;
    event.touchEvent.action = touchEvenInput->action;
    event.touchEvent.changedPointerId = touchEvenInput->changedPointerId;
    event.touchEvent.actionTouchPoint = touchEvenInput->actionTouchPoint;
    event.touchEvent.timeStamp = touchEvenInput->timeStamp;
    event.touchEvent.sourceType = touchEvenInput->sourceType;
    event.touchEvent.targetDisplayId = touchEvenInput->targetDisplayId;
    event.touchEvent.deviceId = touchEvenInput->deviceId;

    ArkUI_UIInputEvent setEvent;
    ArkUIHoverEvent hoverEvent;
    hoverEvent.isHover = true;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    auto res = OH_ArkUI_HoverEvent_IsHovered(nullptr);
    EXPECT_EQ(res, false);
    res = OH_ArkUI_HoverEvent_IsHovered(&setEvent);
    EXPECT_EQ(res, false);
    hoverEvent.isHover = false;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_HoverEvent_IsHovered(&setEvent);
    EXPECT_EQ(res, false);
    hoverEvent.isHover = true;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    res = OH_ArkUI_HoverEvent_IsHovered(&setEvent);
    EXPECT_EQ(res, true);
    hoverEvent.isHover = false;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    res = OH_ArkUI_HoverEvent_IsHovered(&setEvent);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetModifierKeyStates009
 * @tc.desc: Test OH_ArkUI_UIInputEvent_GetModifierKeyStates functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetModifierKeyStates009, TestSize.Level1)
{
    ArkUI_UIInputEvent setEvent;
    ArkUITouchEvent touchEvent;
    setEvent.inputEvent = &touchEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    uint64_t keys = C_TOUCH_EVENT_ID;
    auto res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(nullptr, &keys);
    EXPECT_EQ(res, 401);
    res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&setEvent, &keys);
    setEvent.eventTypeId = TOUCH_EVENT_ID;
    keys = TOUCH_EVENT_ID;
    res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&setEvent, &keys);
    ArkUIAxisEvent axisEvent;
    setEvent.inputEvent = &axisEvent;
    setEvent.eventTypeId = AXIS_EVENT_ID;
    keys = AXIS_EVENT_ID;
    res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&setEvent, &keys);
    EXPECT_EQ(res, 0);
    ArkUIMouseEvent mouseEvent;
    setEvent.inputEvent = &mouseEvent;
    setEvent.eventTypeId = C_MOUSE_EVENT_ID;
    keys = C_MOUSE_EVENT_ID;
    res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&setEvent, &keys);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    keys = C_AXIS_EVENT_ID;
    res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&setEvent, &keys);
    EXPECT_EQ(res, 0);
    ArkUIKeyEvent keyEvent;
    setEvent.inputEvent = &keyEvent;
    setEvent.eventTypeId = C_KEY_EVENT_ID;
    keys = C_KEY_EVENT_ID;
    res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&setEvent, &keys);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    keys = C_AXIS_EVENT_ID;
    res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&setEvent, &keys);
    EXPECT_EQ(res, 0);
    ArkUIHoverEvent hoverEvent;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    keys = C_HOVER_EVENT_ID;
    res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&setEvent, &keys);
    EXPECT_EQ(res, 0);
    ArkUIClickEvent clickEvent;
    setEvent.inputEvent = &clickEvent;
    setEvent.eventTypeId = C_CLICK_EVENT_ID;
    keys = C_CLICK_EVENT_ID;
    res = OH_ArkUI_UIInputEvent_GetModifierKeyStates(&setEvent, &keys);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetTiltX001
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetTiltX functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetTiltX001, TestSize.Level1)
{
    ArkUI_UIInputEvent setEvent;
    ArkUITouchEvent touchEvent;
    setEvent.inputEvent = &touchEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    auto res = OH_ArkUI_PointerEvent_GetTiltX(nullptr, -1);
    EXPECT_EQ(res, 0);
    touchEvent.subKind = ON_HOVER_MOVE;
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, 0);
    EXPECT_EQ(res, 0);
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, -1);
    setEvent.eventTypeId = TOUCH_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIAxisEvent axisEvent;
    setEvent.inputEvent = &axisEvent;
    setEvent.eventTypeId = AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIMouseEvent mouseEvent;
    setEvent.inputEvent = &mouseEvent;
    setEvent.eventTypeId = C_MOUSE_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, 0);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIKeyEvent keyEvent;
    setEvent.inputEvent = &keyEvent;
    setEvent.eventTypeId = C_KEY_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, 0);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIHoverEvent hoverEvent;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIClickEvent clickEvent;
    setEvent.inputEvent = &clickEvent;
    setEvent.eventTypeId = C_CLICK_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltX(&setEvent, 0);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetTiltY001
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetTiltY functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetTiltY001, TestSize.Level1)
{
    ArkUI_UIInputEvent setEvent;
    ArkUITouchEvent touchEvent;
    setEvent.inputEvent = &touchEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    auto res = OH_ArkUI_PointerEvent_GetTiltY(nullptr, -1);
    EXPECT_EQ(res, 0);
    touchEvent.subKind = ON_HOVER_MOVE;
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, 0);
    EXPECT_EQ(res, 0);
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, -1);
    setEvent.eventTypeId = TOUCH_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIAxisEvent axisEvent;
    setEvent.inputEvent = &axisEvent;
    setEvent.eventTypeId = AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIMouseEvent mouseEvent;
    setEvent.inputEvent = &mouseEvent;
    setEvent.eventTypeId = C_MOUSE_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, 0);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIKeyEvent keyEvent;
    setEvent.inputEvent = &keyEvent;
    setEvent.eventTypeId = C_KEY_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, 0);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIHoverEvent hoverEvent;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIClickEvent clickEvent;
    setEvent.inputEvent = &clickEvent;
    setEvent.eventTypeId = C_CLICK_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetTiltY(&setEvent, 0);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetRollAngle001
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetRollAngle functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetRollAngle001, TestSize.Level1)
{
    ArkUI_UIInputEvent setEvent;
    ArkUITouchEvent touchEvent;
    setEvent.inputEvent = &touchEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    double rollAngle = 0.0;
    touchEvent.subKind = ON_HOVER_MOVE;
    touchEvent.actionTouchPoint.rollAngle = 1.0;
    auto res = OH_ArkUI_PointerEvent_GetRollAngle(nullptr, &rollAngle);
    EXPECT_EQ(res, 401);
    res = OH_ArkUI_PointerEvent_GetRollAngle(&setEvent, &rollAngle);
    setEvent.eventTypeId = TOUCH_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetRollAngle(&setEvent, &rollAngle);
    EXPECT_EQ(res, 401);
    ArkUIAxisEvent axisEvent;
    setEvent.inputEvent = &axisEvent;
    setEvent.eventTypeId = AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetRollAngle(&setEvent, &rollAngle);
    EXPECT_EQ(res, 401);
    ArkUIMouseEvent mouseEvent;
    setEvent.inputEvent = &mouseEvent;
    setEvent.eventTypeId = C_MOUSE_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetRollAngle(&setEvent, &rollAngle);
    EXPECT_EQ(res, 401);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetRollAngle(&setEvent, &rollAngle);
    EXPECT_EQ(res, 401);
    ArkUIKeyEvent keyEvent;
    setEvent.inputEvent = &keyEvent;
    setEvent.eventTypeId = C_KEY_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetRollAngle(&setEvent, &rollAngle);
    EXPECT_EQ(res, 401);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetRollAngle(&setEvent, &rollAngle);
    EXPECT_EQ(res, 401);
    ArkUIHoverEvent hoverEvent;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetRollAngle(&setEvent, &rollAngle);
    EXPECT_EQ(res, 0);
    ArkUIClickEvent clickEvent;
    setEvent.inputEvent = &clickEvent;
    setEvent.eventTypeId = C_CLICK_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetRollAngle(&setEvent, &rollAngle);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayYByIndex008
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetDisplayYByIndex functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayYByIndex008, TestSize.Level1)
{
    ArkUI_UIInputEvent setEvent;
    ArkUITouchEvent touchEvent;
    setEvent.inputEvent = &touchEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUITouchPoint points[2]; // 2 points
    ArkUITouchEvent* touchEventPtr = new ArkUITouchEvent();
    touchEventPtr->touchPointes = points;
    touchEventPtr->touchPointSize = 2;
    setEvent.inputEvent = touchEventPtr;
    auto res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(nullptr, 0);
    EXPECT_EQ(res, 0);
    res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&setEvent, 0);
    setEvent.eventTypeId = TOUCH_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIAxisEvent axisEvent;
    setEvent.inputEvent = &axisEvent;
    setEvent.eventTypeId = AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIMouseEvent mouseEvent;
    setEvent.inputEvent = &mouseEvent;
    setEvent.eventTypeId = C_MOUSE_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIKeyEvent keyEvent;
    setEvent.inputEvent = &keyEvent;
    setEvent.eventTypeId = C_KEY_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIHoverEvent hoverEvent;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIClickEvent clickEvent;
    setEvent.inputEvent = &clickEvent;
    setEvent.eventTypeId = C_CLICK_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayYByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayXByIndex008
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetDisplayXByIndex functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayXByIndex008, TestSize.Level1)
{
    ArkUI_UIInputEvent setEvent;
    ArkUITouchEvent touchEvent;
    setEvent.inputEvent = &touchEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUITouchPoint points[2]; // 2 points
    ArkUITouchEvent* touchEventPtr = new ArkUITouchEvent();
    touchEventPtr->touchPointes = points;
    touchEventPtr->touchPointSize = 2;
    setEvent.inputEvent = touchEventPtr;
    auto res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(nullptr, 0);
    EXPECT_EQ(res, 0);
    res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&setEvent, 0);
    setEvent.eventTypeId = TOUCH_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIAxisEvent axisEvent;
    setEvent.inputEvent = &axisEvent;
    setEvent.eventTypeId = AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIMouseEvent mouseEvent;
    setEvent.inputEvent = &mouseEvent;
    setEvent.eventTypeId = C_MOUSE_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIKeyEvent keyEvent;
    setEvent.inputEvent = &keyEvent;
    setEvent.eventTypeId = C_KEY_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIHoverEvent hoverEvent;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
    ArkUIClickEvent clickEvent;
    setEvent.inputEvent = &clickEvent;
    setEvent.eventTypeId = C_CLICK_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayXByIndex(&setEvent, 0);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayX008
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetDisplayX functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayX008, TestSize.Level1)
{
    ArkUI_UIInputEvent setEvent;
    ArkUITouchEvent touchEvent;
    setEvent.inputEvent = &touchEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUITouchPoint points[2]; // 2 points
    ArkUITouchEvent* touchEventPtr = new ArkUITouchEvent();
    touchEventPtr->touchPointes = points;
    touchEventPtr->touchPointSize = 2;
    setEvent.inputEvent = touchEventPtr;
    auto res = OH_ArkUI_PointerEvent_GetDisplayX(nullptr);
    EXPECT_EQ(res, 0);
    res = OH_ArkUI_PointerEvent_GetDisplayX(&setEvent);
    setEvent.eventTypeId = TOUCH_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayX(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIAxisEvent axisEvent;
    setEvent.inputEvent = &axisEvent;
    setEvent.eventTypeId = AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayX(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIMouseEvent mouseEvent;
    setEvent.inputEvent = &mouseEvent;
    setEvent.eventTypeId = C_MOUSE_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayX(&setEvent);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayX(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIKeyEvent keyEvent;
    setEvent.inputEvent = &keyEvent;
    setEvent.eventTypeId = C_KEY_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayX(&setEvent);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayX(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIHoverEvent hoverEvent;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayX(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIClickEvent clickEvent;
    setEvent.inputEvent = &clickEvent;
    setEvent.eventTypeId = C_CLICK_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayX(&setEvent);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetDisplayY008
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetDisplayY functions.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetDisplayY008, TestSize.Level1)
{
    ArkUI_UIInputEvent setEvent;
    ArkUITouchEvent touchEvent;
    setEvent.inputEvent = &touchEvent;
    setEvent.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUITouchPoint points[2]; // 2 points
    points[0].screenY = 3.0;
    points[1].screenY = 4.0;
    ArkUITouchEvent* touchEventPtr = new ArkUITouchEvent();
    touchEventPtr->touchPointes = points;
    touchEventPtr->touchPointSize = 2;
    setEvent.inputEvent = touchEventPtr;
    auto res = OH_ArkUI_PointerEvent_GetDisplayY(nullptr);
    EXPECT_EQ(res, 0);
    res = OH_ArkUI_PointerEvent_GetDisplayY(&setEvent);
    setEvent.eventTypeId = TOUCH_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayY(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIAxisEvent axisEvent;
    setEvent.inputEvent = &axisEvent;
    setEvent.eventTypeId = AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayY(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIMouseEvent mouseEvent;
    setEvent.inputEvent = &mouseEvent;
    setEvent.eventTypeId = C_MOUSE_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayY(&setEvent);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayY(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIKeyEvent keyEvent;
    setEvent.inputEvent = &keyEvent;
    setEvent.eventTypeId = C_KEY_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayY(&setEvent);
    EXPECT_EQ(res, 0);
    setEvent.eventTypeId = C_AXIS_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayY(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIHoverEvent hoverEvent;
    setEvent.inputEvent = &hoverEvent;
    setEvent.eventTypeId = C_HOVER_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayY(&setEvent);
    EXPECT_EQ(res, 0);
    ArkUIClickEvent clickEvent;
    setEvent.inputEvent = &clickEvent;
    setEvent.eventTypeId = C_CLICK_EVENT_ID;
    res = OH_ArkUI_PointerEvent_GetDisplayY(&setEvent);
    EXPECT_EQ(res, 0);
}
} // namespace OHOS::Ace