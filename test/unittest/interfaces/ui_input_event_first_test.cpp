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

#include "event/ui_input_event_impl.h"
#include "gtest/gtest.h"
#include "interfaces/native/node/event_converter.h"
#include "native_node.h"
#include "ui_input_event.h"
#include "frameworks/core/event/ace_events.h"
#include "frameworks/core/event/axis_event.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
namespace {
constexpr int32_t ARKUI_EVENT_NULL = -1;
constexpr int32_t ARKUI_EVENT_ACTION = 1;
constexpr int32_t ARKUI_MOUSE_ACTION = 0;
} // namespace
class UIInputEventTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

/**
 * @tc.name:UIInputEventGetType001  OH_ArkUI_UIInputEvent_GetType
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, UIInputEventGetType001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    uiInputEvent.inputEvent = &event.clickEvent;
    uiInputEvent.eventTypeId = C_CLICK_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    auto sourceType = OH_ArkUI_UIInputEvent_GetType(inputEvent);
    EXPECT_NE(sourceType, UI_INPUT_EVENTT_SOURCE_TYPE_MOUSE);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);

    inputEvent = nullptr;
    sourceType = OH_ArkUI_UIInputEvent_GetType(inputEvent);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:UIInputEventGetAction001  OH_ArkUI_UIInputEvent_GetAction
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, UIInputEventGetAction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUI_UIInputEvent uiInputEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    auto sourceType = OH_ArkUI_UIInputEvent_GetAction(inputEvent);
    EXPECT_EQ(sourceType, ARKUI_EVENT_NULL);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);

    inputEvent = nullptr;
    sourceType = OH_ArkUI_UIInputEvent_GetAction(inputEvent);
    EXPECT_EQ(sourceType, ARKUI_EVENT_NULL);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:UIInputEventGetAction002
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, UIInputEventGetAction002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    uiInputEvent.inputEvent = &event.clickEvent;
    uiInputEvent.eventTypeId = C_TOUCH_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    auto sourceType = OH_ArkUI_UIInputEvent_GetAction(inputEvent);
    EXPECT_EQ(sourceType, ARKUI_EVENT_ACTION);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:UIInputEventGetAction003
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, UIInputEventGetAction003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUI_UIInputEvent uiInputEvent;
    uiInputEvent.eventTypeId = C_MOUSE_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    auto sourceType = OH_ArkUI_UIInputEvent_GetAction(inputEvent);
    EXPECT_EQ(sourceType, ARKUI_EVENT_NULL);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:UIInputEventGetAction004
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, UIInputEventGetAction004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    uiInputEvent.inputEvent = &event.clickEvent;
    uiInputEvent.eventTypeId = C_MOUSE_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    auto sourceType = OH_ArkUI_UIInputEvent_GetAction(inputEvent);
    EXPECT_EQ(sourceType, ARKUI_MOUSE_ACTION);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetPointerId001  OH_ArkUI_PointerEvent_GetPointerId
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetPointerId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(uiInputEvent, nullptr);
    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;

    uint32_t pointerIndex = 0;
    ArkUINodeEvent event;
    event.touchEvent.touchPointSize = 1;
    ArkUITouchPoint points[2];
    points[0].operatingHand = ARKUI_EVENT_HAND_LEFT;
    points[1].operatingHand = ARKUI_EVENT_HAND_RIGHT;
    event.touchEvent.touchPointes = points;
    auto sourceType = OH_ArkUI_PointerEvent_GetPointerId(uiInputEvent.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetPointerId002
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetPointerId002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;
    event->inputEvent = nullptr;
    uint32_t pointerIndex = 1;
    auto sourceType = OH_ArkUI_PointerEvent_GetPointerId(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetPointerId003
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetPointerId003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto sourceType = OH_ArkUI_PointerEvent_GetPointerId(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetPointerId004
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetPointerId004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;
    uint32_t pointerIndex = 0;
    event->inputEvent = nullptr;
    auto sourceType = OH_ArkUI_PointerEvent_GetPointerId(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetPointerId005
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetPointerId005, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;
    uint32_t pointerIndex = 0;

    auto sourceType = OH_ArkUI_PointerEvent_GetPointerId(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetPointerId006
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetPointerId006, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;
    event->inputEvent = nullptr;
    uint32_t pointerIndex = 1;

    auto sourceType = OH_ArkUI_PointerEvent_GetPointerId(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetPointerId007
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetPointerId007, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;
    event->inputEvent = nullptr;
    uint32_t pointerIndex = 0;

    auto sourceType = OH_ArkUI_PointerEvent_GetPointerId(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetPointerId008
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetPointerId008, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto sourceType = OH_ArkUI_PointerEvent_GetPointerId(nullptr, 0);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetPointerId009
 * @tc.desc: Test the UIInputEvent property functions touch event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetPointerId009, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_UIInputEvent.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    auto touchPoint = std::make_unique<ArkUITouchPoint>();
    touchEvent->touchPointSize = 1;
    touchEvent->touchPointes = touchPoint.get();
    event->inputEvent = touchEvent.get();
    uint32_t pointerIndex = 0;

    OH_ArkUI_PointerEvent_GetPointerId(event.get(), pointerIndex);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetXByIndex001 OH_ArkUI_PointerEvent_GetXByIndex
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetXByIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto sourceType = OH_ArkUI_PointerEvent_GetXByIndex(nullptr, 0);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetXByIndex002
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetXByIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_TOUCH_EVENT_ID;

    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    uint32_t pointerIndex = 1;
    auto sourceType = OH_ArkUI_PointerEvent_GetXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetXByIndex003
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetXByIndex003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_TOUCH_EVENT_ID;

    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    event->inputEvent = static_cast<void*>(touchEvent.get());
    touchEvent->touchPointSize = 3;
    uint32_t pointerIndex = 1;
    ArkUITouchPoint touchPoint;
    touchEvent->touchPointes = &touchPoint;

    auto sourceType = OH_ArkUI_PointerEvent_GetXByIndex(event.get(), pointerIndex);
    EXPECT_NE(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetXByIndex004
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetXByIndex004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    event->inputEvent = static_cast<void*>(mouseEvent.get());
    uint32_t pointerIndex = 1;
    auto sourceType = OH_ArkUI_PointerEvent_GetXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetXByIndex005
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetXByIndex005, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto sourceType = OH_ArkUI_PointerEvent_GetXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    event->inputEvent = static_cast<void*>(mouseEvent.get());
    pointerIndex = 1;
    sourceType = OH_ArkUI_PointerEvent_GetXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetXByIndex006
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetXByIndex006, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    event->inputEvent = static_cast<void*>(mouseEvent.get());
    auto sourceType = OH_ArkUI_PointerEvent_GetXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetXByIndex007
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetXByIndex007, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;

    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    event->inputEvent = static_cast<void*>(axisEvent.get());
    uint32_t pointerIndex = 1;
    auto sourceType = OH_ArkUI_PointerEvent_GetXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetXByIndex008
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetXByIndex008, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto sourceType = OH_ArkUI_PointerEvent_GetXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);

    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    event->inputEvent = static_cast<void*>(axisEvent.get());
    pointerIndex = 1;
    sourceType = OH_ArkUI_PointerEvent_GetXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetXByIndex009
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetXByIndex009, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    event->inputEvent = static_cast<void*>(axisEvent.get());
    auto sourceType = OH_ArkUI_PointerEvent_GetXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetYByIndex001
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetYByIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto sourceType = OH_ArkUI_PointerEvent_GetYByIndex(nullptr, 0);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);

    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    uint32_t pointerIndex = 1;
    sourceType = OH_ArkUI_PointerEvent_GetYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetYByIndex002
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetYByIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_TOUCH_EVENT_ID;

    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    event->inputEvent = static_cast<void*>(touchEvent.get());
    touchEvent->touchPointSize = 3;
    uint32_t pointerIndex = 1;
    ArkUITouchPoint touchPoint;
    touchEvent->touchPointes = &touchPoint;

    auto sourceType = OH_ArkUI_PointerEvent_GetYByIndex(event.get(), pointerIndex);
    EXPECT_NE(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetYByIndex003
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetYByIndex003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    event->inputEvent = static_cast<void*>(mouseEvent.get());
    uint32_t pointerIndex = 1;
    auto sourceType = OH_ArkUI_PointerEvent_GetYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetYByIndex004
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetYByIndex004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto sourceType = OH_ArkUI_PointerEvent_GetYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    event->inputEvent = static_cast<void*>(mouseEvent.get());
    pointerIndex = 1;
    sourceType = OH_ArkUI_PointerEvent_GetYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetYByIndex005
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetYByIndex005, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    event->inputEvent = static_cast<void*>(mouseEvent.get());
    auto sourceType = OH_ArkUI_PointerEvent_GetYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetYByIndex006
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetYByIndex006, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;

    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    event->inputEvent = static_cast<void*>(axisEvent.get());
    uint32_t pointerIndex = 1;
    auto sourceType = OH_ArkUI_PointerEvent_GetYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetYByIndex007
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetYByIndex007, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto sourceType = OH_ArkUI_PointerEvent_GetYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);

    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    event->inputEvent = static_cast<void*>(axisEvent.get());
    pointerIndex = 1;
    sourceType = OH_ArkUI_PointerEvent_GetYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetYByIndex008
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetYByIndex008, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    event->inputEvent = static_cast<void*>(axisEvent.get());
    auto sourceType = OH_ArkUI_PointerEvent_GetYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetWindowXByIndex001
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetWindowXByIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto sourceType = OH_ArkUI_PointerEvent_GetWindowXByIndex(nullptr, 0);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);

    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    uint32_t pointerIndex = 1;
    sourceType = OH_ArkUI_PointerEvent_GetWindowXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetWindowXByIndex002
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetWindowXByIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_TOUCH_EVENT_ID;

    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    event->inputEvent = static_cast<void*>(touchEvent.get());
    touchEvent->touchPointSize = 3;
    uint32_t pointerIndex = 1;
    ArkUITouchPoint touchPoint;
    touchEvent->touchPointes = &touchPoint;

    auto sourceType = OH_ArkUI_PointerEvent_GetWindowXByIndex(event.get(), pointerIndex);
    EXPECT_NE(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetWindowXByIndex003
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetWindowXByIndex003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    event->inputEvent = static_cast<void*>(mouseEvent.get());
    uint32_t pointerIndex = 1;
    auto sourceType = OH_ArkUI_PointerEvent_GetWindowXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetWindowXByIndex004
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetWindowXByIndex004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto sourceType = OH_ArkUI_PointerEvent_GetWindowXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    event->inputEvent = static_cast<void*>(mouseEvent.get());
    pointerIndex = 1;
    sourceType = OH_ArkUI_PointerEvent_GetWindowXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetWindowXByIndex005
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetWindowXByIndex005, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    event->inputEvent = static_cast<void*>(mouseEvent.get());
    auto sourceType = OH_ArkUI_PointerEvent_GetWindowXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetWindowXByIndex006
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetWindowXByIndex006, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;

    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    event->inputEvent = static_cast<void*>(axisEvent.get());
    uint32_t pointerIndex = 1;
    auto sourceType = OH_ArkUI_PointerEvent_GetWindowXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetWindowXByIndex007
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetWindowXByIndex007, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto sourceType = OH_ArkUI_PointerEvent_GetWindowXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);

    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    event->inputEvent = static_cast<void*>(axisEvent.get());
    pointerIndex = 1;
    sourceType = OH_ArkUI_PointerEvent_GetWindowXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetWindowXByIndex008
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetWindowXByIndex008, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    event->inputEvent = static_cast<void*>(axisEvent.get());
    auto sourceType = OH_ArkUI_PointerEvent_GetWindowXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetWindowYByIndex001
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetWindowYByIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto sourceType = OH_ArkUI_PointerEvent_GetWindowYByIndex(nullptr, 0);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);

    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    uint32_t pointerIndex = 1;
    sourceType = OH_ArkUI_PointerEvent_GetWindowYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetWindowYByIndex002
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetWindowYByIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_TOUCH_EVENT_ID;

    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    event->inputEvent = static_cast<void*>(touchEvent.get());
    touchEvent->touchPointSize = 3;
    uint32_t pointerIndex = 1;
    ArkUITouchPoint touchPoint;
    touchEvent->touchPointes = &touchPoint;

    auto sourceType = OH_ArkUI_PointerEvent_GetWindowYByIndex(event.get(), pointerIndex);
    EXPECT_NE(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetWindowYByIndex003
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetWindowYByIndex003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    event->inputEvent = static_cast<void*>(mouseEvent.get());
    uint32_t pointerIndex = 1;
    auto sourceType = OH_ArkUI_PointerEvent_GetWindowYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetWindowYByIndex004
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetWindowYByIndex004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto sourceType = OH_ArkUI_PointerEvent_GetWindowYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    event->inputEvent = static_cast<void*>(mouseEvent.get());
    pointerIndex = 1;
    sourceType = OH_ArkUI_PointerEvent_GetWindowYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetWindowYByIndex005
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetWindowYByIndex005, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    event->inputEvent = static_cast<void*>(mouseEvent.get());
    auto sourceType = OH_ArkUI_PointerEvent_GetWindowYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetWindowYByIndex006
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetWindowYByIndex006, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;

    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    event->inputEvent = static_cast<void*>(axisEvent.get());
    uint32_t pointerIndex = 1;
    auto sourceType = OH_ArkUI_PointerEvent_GetWindowYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetWindowYByIndex007
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetWindowYByIndex007, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto sourceType = OH_ArkUI_PointerEvent_GetWindowYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);

    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    event->inputEvent = static_cast<void*>(axisEvent.get());
    pointerIndex = 1;
    sourceType = OH_ArkUI_PointerEvent_GetWindowYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetWindowYByIndex008
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetWindowYByIndex008, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    event->inputEvent = static_cast<void*>(axisEvent.get());
    auto sourceType = OH_ArkUI_PointerEvent_GetWindowYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetDisplayXByIndex001
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetDisplayXByIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto sourceType = OH_ArkUI_PointerEvent_GetDisplayXByIndex(nullptr, 0);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);

    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    uint32_t pointerIndex = 1;
    sourceType = OH_ArkUI_PointerEvent_GetDisplayXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetDisplayXByIndex002
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetDisplayXByIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_TOUCH_EVENT_ID;

    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    event->inputEvent = static_cast<void*>(touchEvent.get());
    touchEvent->touchPointSize = 3;
    uint32_t pointerIndex = 1;
    ArkUITouchPoint touchPoint;
    touchEvent->touchPointes = &touchPoint;

    auto sourceType = OH_ArkUI_PointerEvent_GetDisplayXByIndex(event.get(), pointerIndex);
    EXPECT_NE(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetDisplayXByIndex003
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetDisplayXByIndex003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    event->inputEvent = static_cast<void*>(mouseEvent.get());
    uint32_t pointerIndex = 1;
    auto sourceType = OH_ArkUI_PointerEvent_GetDisplayXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetDisplayXByIndex004
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetDisplayXByIndex004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto sourceType = OH_ArkUI_PointerEvent_GetDisplayXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    event->inputEvent = static_cast<void*>(mouseEvent.get());
    pointerIndex = 1;
    sourceType = OH_ArkUI_PointerEvent_GetDisplayXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetDisplayXByIndex005
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetDisplayXByIndex005, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    event->inputEvent = static_cast<void*>(mouseEvent.get());
    auto sourceType = OH_ArkUI_PointerEvent_GetDisplayXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetDisplayXByIndex006
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetDisplayXByIndex006, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;

    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    event->inputEvent = static_cast<void*>(axisEvent.get());
    uint32_t pointerIndex = 1;
    auto sourceType = OH_ArkUI_PointerEvent_GetDisplayXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetDisplayXByIndex007
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetDisplayXByIndex007, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto sourceType = OH_ArkUI_PointerEvent_GetDisplayXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);

    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    event->inputEvent = static_cast<void*>(axisEvent.get());
    pointerIndex = 1;
    sourceType = OH_ArkUI_PointerEvent_GetDisplayXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetDisplayXByIndex008
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetDisplayXByIndex008, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    event->inputEvent = static_cast<void*>(axisEvent.get());
    auto sourceType = OH_ArkUI_PointerEvent_GetDisplayXByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetDisplayYByIndex001
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetDisplayYByIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto sourceType = OH_ArkUI_PointerEvent_GetDisplayYByIndex(nullptr, 0);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);

    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    uint32_t pointerIndex = 1;
    sourceType = OH_ArkUI_PointerEvent_GetDisplayYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetDisplayYByIndex002
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetDisplayYByIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_TOUCH_EVENT_ID;

    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    event->inputEvent = static_cast<void*>(touchEvent.get());
    touchEvent->touchPointSize = 3;
    uint32_t pointerIndex = 1;
    ArkUITouchPoint touchPoint;
    touchEvent->touchPointes = &touchPoint;

    auto sourceType = OH_ArkUI_PointerEvent_GetDisplayYByIndex(event.get(), pointerIndex);
    EXPECT_NE(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetDisplayYByIndex003
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetDisplayYByIndex003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    event->inputEvent = static_cast<void*>(mouseEvent.get());
    uint32_t pointerIndex = 1;
    auto sourceType = OH_ArkUI_PointerEvent_GetDisplayYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetDisplayYByIndex004
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetDisplayYByIndex004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto sourceType = OH_ArkUI_PointerEvent_GetDisplayYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    event->inputEvent = static_cast<void*>(mouseEvent.get());
    pointerIndex = 1;
    sourceType = OH_ArkUI_PointerEvent_GetDisplayYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetDisplayYByIndex005
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetDisplayYByIndex005, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_MOUSE_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    event->inputEvent = static_cast<void*>(mouseEvent.get());
    auto sourceType = OH_ArkUI_PointerEvent_GetDisplayYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name:PointerEventGetDisplayYByIndex006
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetDisplayYByIndex006, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;

    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    event->inputEvent = static_cast<void*>(axisEvent.get());
    uint32_t pointerIndex = 1;
    auto sourceType = OH_ArkUI_PointerEvent_GetDisplayYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetDisplayYByIndex007
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetDisplayYByIndex007, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto sourceType = OH_ArkUI_PointerEvent_GetDisplayYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);

    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    event->inputEvent = static_cast<void*>(axisEvent.get());
    pointerIndex = 1;
    sourceType = OH_ArkUI_PointerEvent_GetDisplayYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name:PointerEventGetDisplayYByIndex008
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, PointerEventGetDisplayYByIndex008, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_AXIS_EVENT_ID;

    uint32_t pointerIndex = 0;
    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    event->inputEvent = static_cast<void*>(axisEvent.get());
    auto sourceType = OH_ArkUI_PointerEvent_GetDisplayYByIndex(event.get(), pointerIndex);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}
} // namespace OHOS::Ace