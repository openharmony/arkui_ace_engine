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

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetGlobalDisplayX001
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetGlobalDisplayX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetGlobalDisplayX001, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_GetGlobalDisplayX(nullptr);
    EXPECT_EQ(ret, 0.0f);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayX(&event);
    EXPECT_EQ(ret, 0.0f);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUITouchEvent touchEvent;
    touchEvent.actionTouchPoint.globalDisplayX = 100.1f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayX(&event);
    EXPECT_EQ(ret, 100.1f);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    ArkUIMouseEvent mouseEvent;
    mouseEvent.actionTouchPoint.globalDisplayX = 200.2f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayX(&event);
    EXPECT_EQ(ret, 200.2f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetGlobalDisplayX002
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetGlobalDisplayX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetGlobalDisplayX002, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    event.eventTypeId = C_AXIS_EVENT_ID;
    ArkUIAxisEvent axisEvent;
    axisEvent.actionTouchPoint.globalDisplayX = 300.3f;
    event.inputEvent = nullptr;
    auto ret = OH_ArkUI_PointerEvent_GetGlobalDisplayX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayX(&event);
    EXPECT_EQ(ret, 300.3f);

    event.eventTypeId = TOUCH_EVENT_ID;
    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.globalDisplayX = 400.4f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &aceTouchEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayX(&event);
    EXPECT_EQ(ret, 400.4f);

    event.eventTypeId = AXIS_EVENT_ID;
    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.globalDisplayX = 500.5f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &aceAxisEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayX(&event);
    EXPECT_EQ(ret, 500.5f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetGlobalDisplayX003
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetGlobalDisplayX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetGlobalDisplayX003, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    event.eventTypeId = C_CLICK_EVENT_ID;
    ArkUIClickEvent clickEvent;
    clickEvent.globalDisplayX = 300.3f;
    event.inputEvent = nullptr;
    auto ret = OH_ArkUI_PointerEvent_GetGlobalDisplayX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &clickEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayX(&event);
    EXPECT_EQ(ret, 300.3f);

    event.eventTypeId = C_HOVER_EVENT_ID;
    ArkUIHoverEvent hoverEvent;
    hoverEvent.globalDisplayX = 400.4f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayX(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &hoverEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayX(&event);
    EXPECT_EQ(ret, 400.4f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetGlobalDisplayY001
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetGlobalDisplayY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetGlobalDisplayY001, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_GetGlobalDisplayY(nullptr);
    EXPECT_EQ(ret, 0.0f);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayY(&event);
    EXPECT_EQ(ret, 0.0f);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    ArkUITouchEvent touchEvent;
    touchEvent.actionTouchPoint.globalDisplayY = 100.1f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayY(&event);
    EXPECT_EQ(ret, 100.1f);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    ArkUIMouseEvent mouseEvent;
    mouseEvent.actionTouchPoint.globalDisplayY = 200.2f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayY(&event);
    EXPECT_EQ(ret, 200.2f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetGlobalDisplayY002
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetGlobalDisplayY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetGlobalDisplayY002, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    event.eventTypeId = C_AXIS_EVENT_ID;
    ArkUIAxisEvent axisEvent;
    axisEvent.actionTouchPoint.globalDisplayY = 300.3f;
    event.inputEvent = nullptr;
    auto ret = OH_ArkUI_PointerEvent_GetGlobalDisplayY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayY(&event);
    EXPECT_EQ(ret, 300.3f);

    event.eventTypeId = TOUCH_EVENT_ID;
    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.globalDisplayY = 400.4f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &aceTouchEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayY(&event);
    EXPECT_EQ(ret, 400.4f);

    event.eventTypeId = AXIS_EVENT_ID;
    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.globalDisplayY = 500.5f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &aceAxisEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayY(&event);
    EXPECT_EQ(ret, 500.5f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetGlobalDisplayY003
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetGlobalDisplayY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetGlobalDisplayY003, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    event.eventTypeId = C_CLICK_EVENT_ID;
    ArkUIClickEvent clickEvent;
    clickEvent.globalDisplayY = 300.3f;
    event.inputEvent = nullptr;
    auto ret = OH_ArkUI_PointerEvent_GetGlobalDisplayY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &clickEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayY(&event);
    EXPECT_EQ(ret, 300.3f);

    event.eventTypeId = C_HOVER_EVENT_ID;
    ArkUIHoverEvent hoverEvent;
    hoverEvent.globalDisplayY = 400.4f;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayY(&event);
    EXPECT_EQ(ret, 0.0f);
    event.inputEvent = &hoverEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayY(&event);
    EXPECT_EQ(ret, 400.4f);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex(nullptr, 0);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex(&event, 0);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex(&event, 0);
    EXPECT_EQ(ret, 0);
    ArkUITouchEvent touchEvent;
    ArkUITouchPoint touchPointes[3];
    touchPointes[2].globalDisplayX = 10;
    touchEvent.touchPointSize = 3;
    touchEvent.touchPointes = touchPointes;
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex(&event, 2);
    EXPECT_EQ(ret, 10);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ArkUIMouseEvent mouseEvent;
    mouseEvent.actionTouchPoint.globalDisplayX = 20;
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex(&event, 0);
    EXPECT_EQ(ret, 20);

    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex(&event, 0);
    EXPECT_EQ(ret, 0);
    ArkUIAxisEvent axisEvent;
    axisEvent.actionTouchPoint.globalDisplayX = 30;
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex(&event, 0);
    EXPECT_EQ(ret, 30);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex
 * @tc.desc: Test OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    auto ret = OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex(nullptr, 0);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_KEY_EVENT_ID;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex(&event, 0);
    EXPECT_EQ(ret, 0);

    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex(&event, 0);
    EXPECT_EQ(ret, 0);
    ArkUITouchEvent touchEvent;
    ArkUITouchPoint touchPointes[3];
    touchPointes[2].globalDisplayY = 10;
    touchEvent.touchPointSize = 3;
    touchEvent.touchPointes = touchPointes;
    event.inputEvent = &touchEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex(&event, 2);
    EXPECT_EQ(ret, 10);

    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ArkUIMouseEvent mouseEvent;
    mouseEvent.actionTouchPoint.globalDisplayY = 20;
    event.inputEvent = &mouseEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex(&event, 0);
    EXPECT_EQ(ret, 20);

    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex(&event, 0);
    EXPECT_EQ(ret, 0);
    ArkUIAxisEvent axisEvent;
    axisEvent.actionTouchPoint.globalDisplayY = 30;
    event.inputEvent = &axisEvent;
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex(&event, 1);
    EXPECT_EQ(ret, 0);
    ret = OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex(&event, 0);
    EXPECT_EQ(ret, 30);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayX
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayX, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayX(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayX(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].globalDisplayX = 30;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayX(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 30);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayX(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayY
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayY, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayY(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayY(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].globalDisplayY = 40;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayY(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 40);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayY(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: CheckIsSupportedScenario001
 * @tc.desc: Test CheckIsSupportedScenario
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, CheckIsSupportedScenario001, TestSize.Level1)
{
    auto errorCode = CheckIsSupportedScenario(S_UNKNOWN, nullptr);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_PARAM_INVALID);

    ArkUI_UIInputEvent event;
    event.inputType = ARKUI_UIINPUTEVENT_TYPE_AXIS;
    event.eventTypeId = AXIS_EVENT_ID;
    errorCode = CheckIsSupportedScenario(S_NXC_DISPATCH_AXIS_EVENT, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_NO_ERROR);
    errorCode = CheckIsSupportedScenario(S_UNKNOWN, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);

    event.inputType = ARKUI_UIINPUTEVENT_TYPE_TOUCH;
    event.eventTypeId = TOUCH_EVENT_ID;
    errorCode = CheckIsSupportedScenario(S_NXC_ON_TOUCH_INTERCEPT, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_NO_ERROR);
    errorCode = CheckIsSupportedScenario(S_UNKNOWN, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

/**
 * @tc.name: CheckIsSupportedScenario002
 * @tc.desc: Test CheckIsSupportedScenario
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, CheckIsSupportedScenario002, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    ArkUITouchEvent touchEvent;
    event.inputType = ARKUI_UIINPUTEVENT_TYPE_TOUCH;
    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    auto errorCode = CheckIsSupportedScenario(S_UNKNOWN, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_PARAM_INVALID);
    event.inputEvent = &touchEvent;
    touchEvent.subKind = ON_TOUCH;
    errorCode = CheckIsSupportedScenario(S_NODE_TOUCH_EVENT, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_NO_ERROR);
    touchEvent.subKind = ON_TOUCH_INTERCEPT;
    errorCode = CheckIsSupportedScenario(S_NODE_ON_TOUCH_INTERCEPT, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_NO_ERROR);
    touchEvent.subKind = ON_HOVER_MOVE;
    errorCode = CheckIsSupportedScenario(S_NODE_ON_HOVER_MOVE, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_NO_ERROR);
    touchEvent.subKind = 0;
    errorCode = CheckIsSupportedScenario(S_GESTURE_TOUCH_EVENT, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_NO_ERROR);
    errorCode = CheckIsSupportedScenario(S_UNKNOWN, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);

    ArkUIMouseEvent mouseEvent;
    event.inputType = ARKUI_UIINPUTEVENT_TYPE_MOUSE;
    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    errorCode = CheckIsSupportedScenario(S_UNKNOWN, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_PARAM_INVALID);
    event.inputEvent = &mouseEvent;
    mouseEvent.subKind = ON_MOUSE;
    errorCode = CheckIsSupportedScenario(S_NODE_ON_MOUSE, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_NO_ERROR);
    mouseEvent.subKind = 0;
    errorCode = CheckIsSupportedScenario(S_GESTURE_MOUSE_EVENT, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_NO_ERROR);
    errorCode = CheckIsSupportedScenario(S_UNKNOWN, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

/**
 * @tc.name: CheckIsSupportedScenario003
 * @tc.desc: Test CheckIsSupportedScenario
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, CheckIsSupportedScenario003, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    ArkUIAxisEvent axisEvent;
    event.inputType = ARKUI_UIINPUTEVENT_TYPE_AXIS;
    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    auto errorCode = CheckIsSupportedScenario(S_UNKNOWN, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_PARAM_INVALID);
    event.inputEvent = &axisEvent;
    axisEvent.subKind = ON_AXIS;
    errorCode = CheckIsSupportedScenario(S_NODE_ON_AXIS, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_NO_ERROR);
    axisEvent.subKind = 0;
    errorCode = CheckIsSupportedScenario(S_GESTURE_AXIS_EVENT, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_NO_ERROR);
    errorCode = CheckIsSupportedScenario(S_UNKNOWN, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);

    ArkUIKeyEvent keyEvent;
    event.inputType = ARKUI_UIINPUTEVENT_TYPE_KEY;
    event.eventTypeId = C_KEY_EVENT_ID;
    event.inputEvent = nullptr;
    errorCode = CheckIsSupportedScenario(S_UNKNOWN, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_PARAM_INVALID);
    event.inputEvent = &keyEvent;
    keyEvent.subKind = ON_KEY_EVENT;
    errorCode = CheckIsSupportedScenario(S_NODE_ON_KEY_EVENT, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_NO_ERROR);
    event.inputEvent = &keyEvent;
    keyEvent.subKind = ON_KEY_PREIME;
    errorCode = CheckIsSupportedScenario(S_NODE_ON_KEY_PRE_IME, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_NO_ERROR);
    event.inputEvent = &keyEvent;
    keyEvent.subKind = ON_KEY_DISPATCH;
    errorCode = CheckIsSupportedScenario(S_NODE_DISPATCH_KEY_EVENT, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_NO_ERROR);
    errorCode = CheckIsSupportedScenario(S_UNKNOWN, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

/**
 * @tc.name: CheckIsSupportedScenario004
 * @tc.desc: Test CheckIsSupportedScenario
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, CheckIsSupportedScenario004, TestSize.Level1)
{
    ArkUI_UIInputEvent event;
    event.inputType = ARKUI_UIINPUTEVENT_TYPE_UNKNOWN;
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    auto errorCode = CheckIsSupportedScenario(S_NODE_ON_FOCUS_AXIS, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_NO_ERROR);
    errorCode = CheckIsSupportedScenario(S_UNKNOWN, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);

    event.inputType = ARKUI_UIINPUTEVENT_TYPE_UNKNOWN;
    event.eventTypeId = C_CLICK_EVENT_ID;
    errorCode = CheckIsSupportedScenario(S_NODE_ON_CLICK_EVENT, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_NO_ERROR);
    errorCode = CheckIsSupportedScenario(S_UNKNOWN, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);

    event.inputType = ARKUI_UIINPUTEVENT_TYPE_KEY;
    errorCode = CheckIsSupportedScenario(S_GESTURE_CLICK_EVENT, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_NO_ERROR);
    errorCode = CheckIsSupportedScenario(S_UNKNOWN, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);

    event.inputType = ARKUI_UIINPUTEVENT_TYPE_UNKNOWN;
    event.eventTypeId = C_HOVER_EVENT_ID;
    errorCode = CheckIsSupportedScenario(S_NODE_ON_HOVER_EVENT, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_NO_ERROR);
    errorCode = CheckIsSupportedScenario(S_UNKNOWN, &event);
    EXPECT_EQ(errorCode, ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}
} // namespace OHOS::Ace
