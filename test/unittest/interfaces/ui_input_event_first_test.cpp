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

    inputEvent = nullptr;
    sourceType = OH_ArkUI_UIInputEvent_GetType(inputEvent);
    EXPECT_EQ(sourceType, UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN);
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

    inputEvent = nullptr;
    sourceType = OH_ArkUI_UIInputEvent_GetAction(inputEvent);
    EXPECT_EQ(sourceType, ARKUI_EVENT_NULL);
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
}
} // namespace OHOS::Ace