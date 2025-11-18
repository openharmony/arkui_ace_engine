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

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetTouchAreaWidth
 * @tc.desc: test OH_ArkUI_PointerEvent_GetTouchAreaWidth
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetTouchAreaWidth, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetTouchAreaWidth(nullptr, 0);
    EXPECT_EQ(result, 0);
    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetTouchAreaWidth(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetTouchAreaWidth(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 0);

    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    touchEvent->touchPointSize = 0;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetTouchAreaWidth(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 0);

    touchEvent->touchPointSize = 2;
    ArkUITouchPoint touchPointes[2];
    touchPointes[1].contactAreaWidth = 1.0;
    touchEvent->touchPointes = touchPointes;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetTouchAreaWidth(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetTouchAreaHeight
 * @tc.desc: test OH_ArkUI_PointerEvent_GetTouchAreaHeight
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetTouchAreaHeight, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetTouchAreaHeight(nullptr, 0);
    EXPECT_EQ(result, 0);
    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetTouchAreaHeight(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetTouchAreaHeight(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 0);

    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    touchEvent->touchPointSize = 0;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetTouchAreaHeight(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 0);

    touchEvent->touchPointSize = 2;
    ArkUITouchPoint touchPointes[2];
    touchPointes[1].contactAreaHeight = 1.0;
    touchEvent->touchPointes = touchPointes;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetTouchAreaHeight(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetChangedPointerId
 * @tc.desc: test OH_ArkUI_PointerEvent_GetChangedPointerId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetChangedPointerId, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetChangedPointerId(nullptr, 0);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetChangedPointerId(uiInputEvent.get(), 0);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetChangedPointerId(uiInputEvent.get(), 0);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    touchEvent->touchPointSize = 0;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetChangedPointerId(uiInputEvent.get(), 0);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistorySize
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistorySize
 * @tc.type: FUNC
 */

HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistorySize, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistorySize(nullptr);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistorySize(uiInputEvent.get());
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistorySize(uiInputEvent.get());
    EXPECT_EQ(result, 0);

    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    touchEvent->historyEvents = events;
    touchEvent->historySize = 1;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistorySize(uiInputEvent.get());
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryEventTime
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryEventTime
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryEventTime, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryEventTime(nullptr, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryEventTime(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    events[1].timeStamp = 1;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryEventTime(uiInputEvent.get(), 1);
    EXPECT_EQ(result, 1);

    result = OH_ArkUI_PointerEvent_GetHistoryEventTime(uiInputEvent.get(), -1);
    EXPECT_EQ(result, 0);

    result = OH_ArkUI_PointerEvent_GetHistoryEventTime(uiInputEvent.get(), 10);
    EXPECT_EQ(result, 0);

    touchEvent->historyEvents = nullptr;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryEventTime(uiInputEvent.get(), 1);
    EXPECT_EQ(result, 0);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryEventTime(uiInputEvent.get(), 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryPointerCount
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryPointerCount
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryPointerCount, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryPointerCount(nullptr, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryPointerCount(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    events[1].touchPointSize = 1;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryPointerCount(uiInputEvent.get(), 1);
    EXPECT_EQ(result, 1);

    result = OH_ArkUI_PointerEvent_GetHistoryPointerCount(uiInputEvent.get(), -1);
    EXPECT_EQ(result, 0);

    result = OH_ArkUI_PointerEvent_GetHistoryPointerCount(uiInputEvent.get(), 10);
    EXPECT_EQ(result, 0);

    touchEvent->historyEvents = nullptr;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryPointerCount(uiInputEvent.get(), 1);
    EXPECT_EQ(result, 0);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryPointerCount(uiInputEvent.get(), 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryPointerId
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryPointerId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryPointerId, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryPointerId(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryPointerId(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].id = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryPointerId(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryPointerId(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryX
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryX, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryX(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryX(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].nodeX = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryX(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryX(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryY
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryY, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryY(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryY(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].nodeY = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryY(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryY(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryWindowX
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryWindowX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryWindowX, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryWindowX(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryWindowX(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].windowX = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryWindowX(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryWindowX(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryWindowY
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryWindowY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryWindowY, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryWindowY(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryWindowY(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].windowY = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryWindowY(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryWindowY(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryDisplayX
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryDisplayX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryDisplayX, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryDisplayX(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryDisplayX(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].screenX = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryDisplayX(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryDisplayX(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryDisplayY
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryDisplayY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryDisplayY, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryDisplayY(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryDisplayY(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].screenY = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryDisplayY(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryDisplayY(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryPressure
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryPressure
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryPressure, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryPressure(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryPressure(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].pressure = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryPressure(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryPressure(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryTiltX
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryTiltX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryTiltX, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryTiltX(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryTiltX(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].tiltX = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryTiltX(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryTiltX(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryTiltY
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryTiltY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryTiltY, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryTiltY(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryTiltY(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].tiltY = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryTiltY(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryTiltY(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].contactAreaWidth = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight
 * @tc.desc: test OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight(nullptr, 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight(uiInputEvent.get(), 0, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    ArkUIHistoryTouchEvent events[2];
    ArkUITouchPoint pointes[2];
    events[1].touchPointSize = 2;
    pointes[1].contactAreaHeight = 20;
    events[1].touchPointes = pointes;
    touchEvent->historyEvents = events;
    touchEvent->historySize = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 20);

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight(uiInputEvent.get(), 1, 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetVerticalAxisValue
 * @tc.desc: test OH_ArkUI_AxisEvent_GetVerticalAxisValue
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetVerticalAxisValue, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(nullptr);
    EXPECT_EQ(result, 0.0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 0.0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    auto axisEvent = std::make_unique<OHOS::Ace::AxisEvent>();
    axisEvent->verticalAxis = 1.1;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 0.0);

    uiInputEvent->inputEvent = axisEvent.get();
    result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 1.1);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;

    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 0.0);

    auto cAxisEvent = std::make_unique<ArkUIAxisEvent>();
    cAxisEvent->verticalAxis = 1.1;
    uiInputEvent->inputEvent = cAxisEvent.get();
    result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 1.1);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetHorizontalAxisValue
 * @tc.desc: test OH_ArkUI_AxisEvent_GetHorizontalAxisValue
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetHorizontalAxisValue, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(nullptr);
    EXPECT_EQ(result, 0.0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 0.0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    auto axisEvent = std::make_unique<OHOS::Ace::AxisEvent>();
    axisEvent->horizontalAxis = 1.1;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 0.0);

    uiInputEvent->inputEvent = axisEvent.get();
    result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 1.1);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 0.0);

    auto cAxisEvent = std::make_unique<ArkUIAxisEvent>();
    cAxisEvent->verticalAxis = 1.1;
    uiInputEvent->inputEvent = cAxisEvent.get();
    result = OH_ArkUI_AxisEvent_GetVerticalAxisValue(uiInputEvent.get());
    EXPECT_EQ(result, 1.1);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_GetPinchAxisScaleValue
 * @tc.desc: test OH_ArkUI_AxisEvent_GetPinchAxisScaleValue
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_GetPinchAxisScaleValue, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(nullptr);
    EXPECT_EQ(result, 0.0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    result = OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(uiInputEvent.get());
    EXPECT_EQ(result, 0.0);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    auto axisEvent = std::make_unique<OHOS::Ace::AxisEvent>();
    axisEvent->pinchAxisScale = 1.1;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(uiInputEvent.get());
    EXPECT_EQ(result, 0.0);

    uiInputEvent->inputEvent = axisEvent.get();
    result = OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(uiInputEvent.get());
    EXPECT_EQ(result, 1.1);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(uiInputEvent.get());
    EXPECT_EQ(result, 0.0);

    auto cAxisEvent = std::make_unique<ArkUIAxisEvent>();
    cAxisEvent->pinchAxisScale = 1.1;
    uiInputEvent->inputEvent = cAxisEvent.get();
    result = OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(uiInputEvent.get());
    EXPECT_EQ(result, 1.1);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetInterceptHitTestMode
 * @tc.desc: test OH_ArkUI_PointerEvent_SetInterceptHitTestMode
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetInterceptHitTestMode, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto mode = HTM_TRANSPARENT;
    auto result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(nullptr, mode);
    int32_t ERROR_CODE_PARAM_INVALID = 401;
    int32_t ERROR_CODE_NO_ERROR = 0;
    EXPECT_EQ(result, ERROR_CODE_PARAM_INVALID);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    touchEvent->interceptResult = 0;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(uiInputEvent.get(), mode);
    EXPECT_EQ(touchEvent->interceptResult, static_cast<int32_t>(HTM_TRANSPARENT));
    EXPECT_EQ(result, ERROR_CODE_NO_ERROR);

    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    mouseEvent->interceptResult = 0;
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(uiInputEvent.get(), mode);
    EXPECT_EQ(result, ERROR_CODE_PARAM_INVALID);

    uiInputEvent->inputEvent = mouseEvent.get();
    result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(uiInputEvent.get(), mode);
    EXPECT_EQ(touchEvent->interceptResult, static_cast<int32_t>(HTM_TRANSPARENT));

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_SetInterceptHitTestMode(uiInputEvent.get(), mode);
    EXPECT_EQ(result, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_SetStopPropagation
 * @tc.desc: test OH_ArkUI_PointerEvent_SetStopPropagation
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetStopPropagation, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto stopPropagation = true;
    auto result = OH_ArkUI_PointerEvent_SetStopPropagation(nullptr, true);
    int32_t ERROR_CODE_PARAM_INVALID = 401;
    EXPECT_EQ(result, ERROR_CODE_PARAM_INVALID);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    touchEvent->stopPropagation = false;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_SetStopPropagation(uiInputEvent.get(), stopPropagation);
    EXPECT_EQ(touchEvent->stopPropagation, stopPropagation);

    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    mouseEvent->stopPropagation = false;
    uiInputEvent->inputEvent = mouseEvent.get();
    result = OH_ArkUI_PointerEvent_SetStopPropagation(uiInputEvent.get(), stopPropagation);
    EXPECT_EQ(mouseEvent->stopPropagation, stopPropagation);

    uiInputEvent->eventTypeId = C_HOVER_EVENT_ID;
    auto hoverEvent = std::make_unique<ArkUIHoverEvent>();
    hoverEvent->stopPropagation = false;
    uiInputEvent->inputEvent = hoverEvent.get();
    result = OH_ArkUI_PointerEvent_SetStopPropagation(uiInputEvent.get(), stopPropagation);
    EXPECT_EQ(hoverEvent->stopPropagation, stopPropagation);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_SetStopPropagation(uiInputEvent.get(), stopPropagation);
    EXPECT_EQ(result, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetMouseButton
 * @tc.desc: test OH_ArkUI_MouseEvent_GetMouseButton
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetMouseButton, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_MouseEvent_GetMouseButton(nullptr);
    EXPECT_EQ(result, -1);

    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetMouseButton(uiInputEvent.get());
    EXPECT_EQ(result, -1);

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    mouseEvent->button = 2;
    uiInputEvent->inputEvent = mouseEvent.get();
    result = OH_ArkUI_MouseEvent_GetMouseButton(uiInputEvent.get());
    EXPECT_EQ(result, 2);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetMouseButton(uiInputEvent.get());
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetMouseAction
 * @tc.desc: test OH_ArkUI_MouseEvent_GetMouseAction
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetMouseAction, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_MouseEvent_GetMouseAction(nullptr);
    EXPECT_EQ(result, -1);

    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetMouseAction(uiInputEvent.get());
    EXPECT_EQ(result, -1);

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    mouseEvent->action = 2;
    uiInputEvent->inputEvent = mouseEvent.get();
    result = OH_ArkUI_MouseEvent_GetMouseAction(uiInputEvent.get());
    EXPECT_EQ(result, 2);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetMouseAction(uiInputEvent.get());
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_GetPressedTimeByIndex
 * @tc.desc: test OH_ArkUI_PointerEvent_GetPressedTimeByIndex
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_GetPressedTimeByIndex, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(nullptr, 0);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(uiInputEvent.get(), 0);
    EXPECT_EQ(result, 0);

    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    touchEvent->touchPointSize = 2;
    ArkUITouchPoint touchPointes[2];
    touchPointes[1].pressedTime = 1;
    touchEvent->touchPointes = touchPointes;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(uiInputEvent.get(), 1);
    EXPECT_EQ(result, 1);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    result = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(uiInputEvent.get(), 1);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaX
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaX, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaX(nullptr);
    EXPECT_EQ(result, 0.0f);

    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetRawDeltaX(uiInputEvent.get());
    EXPECT_EQ(result, 0.0f);

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    mouseEvent->rawDeltaX = 2.0f;
    uiInputEvent->inputEvent = mouseEvent.get();
    result = OH_ArkUI_MouseEvent_GetRawDeltaX(uiInputEvent.get());
    EXPECT_EQ(result, 2.0f);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetRawDeltaX(uiInputEvent.get());
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetRawDeltaY
 * @tc.desc: test OH_ArkUI_MouseEvent_GetRawDeltaY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaY, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_MouseEvent_GetRawDeltaY(nullptr);
    EXPECT_EQ(result, 0.0f);

    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetRawDeltaY(uiInputEvent.get());
    EXPECT_EQ(result, 0.0f);

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    mouseEvent->rawDeltaY = 2.0f;
    uiInputEvent->inputEvent = mouseEvent.get();
    result = OH_ArkUI_MouseEvent_GetRawDeltaY(uiInputEvent.get());
    EXPECT_EQ(result, 2.0f);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetRawDeltaY(uiInputEvent.get());
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId
 * @tc.desc: test OH_ArkUI_UIInputEvent_GetTargetDisplayId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(nullptr);
    EXPECT_EQ(result, 0);

    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    mouseEvent->targetDisplayId = 1;
    uiInputEvent->inputEvent = mouseEvent.get();
    result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(uiInputEvent.get());
    EXPECT_EQ(result, 1);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    auto touchEvent = std::make_unique<ArkUITouchEvent>();
    touchEvent->targetDisplayId = 2;
    uiInputEvent->inputEvent = touchEvent.get();
    result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(uiInputEvent.get());
    EXPECT_EQ(result, 2);

    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;
    auto axisEvent = std::make_unique<ArkUIAxisEvent>();
    axisEvent->targetDisplayId = 3;
    uiInputEvent->inputEvent = axisEvent.get();
    result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(uiInputEvent.get());
    EXPECT_EQ(result, 3);

    uiInputEvent->eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    auto focusAxisEvent = std::make_unique<ArkUIFocusAxisEvent>();
    focusAxisEvent->targetDisplayId = 4;
    uiInputEvent->inputEvent = focusAxisEvent.get();
    result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(uiInputEvent.get());
    EXPECT_EQ(result, 4);

    uiInputEvent->eventTypeId = TOUCH_EVENT_ID;
    auto ohosTouchEvent = std::make_unique<OHOS::Ace::TouchEvent>();
    ohosTouchEvent->targetDisplayId = 5;
    uiInputEvent->inputEvent = ohosTouchEvent.get();
    result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(uiInputEvent.get());
    EXPECT_EQ(result, 5);

    uiInputEvent->eventTypeId = AXIS_EVENT_ID;
    auto ohosAxisEvent = std::make_unique<OHOS::Ace::AxisEvent>();
    ohosAxisEvent->targetDisplayId = 6;
    uiInputEvent->inputEvent = ohosAxisEvent.get();
    result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(uiInputEvent.get());
    EXPECT_EQ(result, 6);

    uiInputEvent->eventTypeId = C_HOVER_EVENT_ID;
    auto ohosHoverEvent = std::make_unique<ArkUIHoverEvent>();
    ohosHoverEvent->targetDisplayId = 7;
    uiInputEvent->inputEvent = ohosHoverEvent.get();
    result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(uiInputEvent.get());
    EXPECT_EQ(result, 7);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetTargetDisplayId008
 * @tc.desc: test OH_ArkUI_UIInputEvent_GetTargetDisplayId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetTargetDisplayId008, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    uiInputEvent->eventTypeId = C_CLICK_EVENT_ID;
    auto ohosClickEvent = std::make_unique<ArkUIClickEvent>();
    ohosClickEvent->targetDisplayId = 8;
    uiInputEvent->inputEvent = ohosClickEvent.get();
    auto result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(uiInputEvent.get());
    EXPECT_EQ(result, 8);

    uiInputEvent->eventTypeId = C_KEY_EVENT_ID;
    result = OH_ArkUI_UIInputEvent_GetTargetDisplayId(uiInputEvent.get());
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OH_ArkUI_MouseEvent_GetPressedButtons
 * @tc.desc: test OH_ArkUI_MouseEvent_GetPressedButtons
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetPressedButtons, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    int32_t pressedButtons[1] = { 0 };
    int32_t length = 1;
    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    uiInputEvent->inputEvent = nullptr;
    auto result = OH_ArkUI_MouseEvent_GetPressedButtons(uiInputEvent.get(), pressedButtons, &length);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    auto mouseEvent = std::make_unique<ArkUIMouseEvent>();
    mouseEvent->pressedButtonsLength = 2;
    uiInputEvent->inputEvent = mouseEvent.get();

    uiInputEvent->eventTypeId = C_MOUSE_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetPressedButtons(uiInputEvent.get(), pressedButtons, &length);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH);

    mouseEvent->pressedButtonsLength = 1;
    ArkUI_Int32 mousePressedButtons[1] = { 3 };
    mouseEvent->pressedButtons = mousePressedButtons;
    uiInputEvent->inputEvent = mouseEvent.get();
    result = OH_ArkUI_MouseEvent_GetPressedButtons(uiInputEvent.get(), pressedButtons, &length);
    EXPECT_EQ(pressedButtons[0], 3);

    uiInputEvent->eventTypeId = C_TOUCH_EVENT_ID;
    result = OH_ArkUI_MouseEvent_GetPressedButtons(uiInputEvent.get(), pressedButtons, &length);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    result = OH_ArkUI_MouseEvent_GetPressedButtons(uiInputEvent.get(), pressedButtons, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    result = OH_ArkUI_MouseEvent_GetPressedButtons(uiInputEvent.get(), nullptr, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    result = OH_ArkUI_MouseEvent_GetPressedButtons(nullptr, nullptr, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_FocusAxisEvent_GetAxisValue
 * @tc.desc: test OH_ArkUI_FocusAxisEvent_GetAxisValue
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_FocusAxisEvent_GetAxisValue, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    int32_t axis = 100;
    auto result = OH_ArkUI_FocusAxisEvent_GetAxisValue(nullptr, axis);
    EXPECT_EQ(result, 0.0);

    uiInputEvent->eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    result = OH_ArkUI_FocusAxisEvent_GetAxisValue(nullptr, axis);
    EXPECT_EQ(result, 0.0);

    auto focusAxisEvent = std::make_unique<ArkUIFocusAxisEvent>();
    uiInputEvent->inputEvent = focusAxisEvent.get();
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: OH_ArkUI_FocusAxisEvent_SetStopPropagation
 * @tc.desc: Test function OH_ArkUI_FocusAxisEvent_SetStopPropagation.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_FocusAxisEvent_SetStopPropagation, TestSize.Level1)
{
    int32_t ret = OH_ArkUI_FocusAxisEvent_SetStopPropagation(nullptr, true);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ArkUI_UIInputEvent event;
    event.eventTypeId = C_TOUCH_EVENT_ID;
    ret = OH_ArkUI_FocusAxisEvent_SetStopPropagation(&event, true);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ArkUIFocusAxisEvent focusAxisEvent;
    focusAxisEvent.stopPropagation = false;
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    event.inputEvent = &focusAxisEvent;
    ret = OH_ArkUI_FocusAxisEvent_SetStopPropagation(&event, true);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_TRUE(focusAxisEvent.stopPropagation);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetWidth001
 * @tc.desc: Test function OH_ArkUI_UIInputEvent_GetEventTargetWidth.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetWidth001, TestSize.Level1)
{
    float width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(nullptr);
    EXPECT_EQ(width, 0.0f);
    ArkUI_UIInputEvent event;

    ArkUITouchEvent touchEvent;
    touchEvent.width = 10.0f;
    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 0.0f);
    event.inputEvent = &touchEvent;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 10.0f);

    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.width = 20.0f;
    event.eventTypeId = TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 0.0f);
    event.inputEvent = &aceTouchEvent;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 20.0f);

    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.width = 30.0f;
    event.eventTypeId = AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 0.0f);
    event.inputEvent = &aceAxisEvent;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 30.0f);

    ArkUIMouseEvent mouseEvent;
    mouseEvent.width = 40.0f;
    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 0.0f);
    event.inputEvent = &mouseEvent;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 40.0f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetWidth002
 * @tc.desc: Test function OH_ArkUI_UIInputEvent_GetEventTargetWidth.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetWidth002, TestSize.Level1)
{
    float width = 1.0f;
    ArkUI_UIInputEvent event;

    ArkUIAxisEvent axisEvent;
    axisEvent.width = 50.0f;
    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 0.0f);
    event.inputEvent = &axisEvent;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 50.0f);

    ArkUIFocusAxisEvent focusAxisEvent;
    focusAxisEvent.width = 60.0f;
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 0.0f);
    event.inputEvent = &focusAxisEvent;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 60.0f);

    ArkUIHoverEvent hoverEvent;
    hoverEvent.width = 70.0f;
    event.eventTypeId = C_HOVER_EVENT_ID;
    event.inputEvent = nullptr;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 0.0f);
    event.inputEvent = &hoverEvent;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 70.0f);

    ArkUIClickEvent clickEvent;
    clickEvent.width = 80.0f;
    event.eventTypeId = C_CLICK_EVENT_ID;
    event.inputEvent = nullptr;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 0.0f);
    event.inputEvent = &clickEvent;
    width = OH_ArkUI_UIInputEvent_GetEventTargetWidth(&event);
    EXPECT_EQ(width, 80.0f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetHeight001
 * @tc.desc: Test function OH_ArkUI_UIInputEvent_GetEventTargetHeight.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetHeight001, TestSize.Level1)
{
    float height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(nullptr);
    EXPECT_EQ(height, 0.0f);

    ArkUI_UIInputEvent event;

    ArkUITouchEvent touchEvent;
    touchEvent.height = 15.0f;
    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 0.0f);
    event.inputEvent = &touchEvent;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 15.0f);

    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.height = 25.0f;
    event.eventTypeId = TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 0.0f);
    event.inputEvent = &aceTouchEvent;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 25.0f);

    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.height = 35.0f;
    event.eventTypeId = AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 0.0f);
    event.inputEvent = &aceAxisEvent;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 35.0f);

    ArkUIMouseEvent mouseEvent;
    mouseEvent.height = 45.0f;
    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 0.0f);
    event.inputEvent = &mouseEvent;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 45.0f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetHeight002
 * @tc.desc: Test function OH_ArkUI_UIInputEvent_GetEventTargetHeight.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetHeight002, TestSize.Level1)
{
    float height = 1.0f;
    ArkUI_UIInputEvent event;
    ArkUIAxisEvent axisEvent;
    axisEvent.height = 55.0f;
    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 0.0f);
    event.inputEvent = &axisEvent;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 55.0f);

    ArkUIFocusAxisEvent focusAxisEvent;
    focusAxisEvent.height = 65.0f;
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 0.0f);
    event.inputEvent = &focusAxisEvent;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 65.0f);

    ArkUIHoverEvent hoverEvent;
    hoverEvent.height = 75.0f;
    event.eventTypeId = C_HOVER_EVENT_ID;
    event.inputEvent = nullptr;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 0.0f);
    event.inputEvent = &hoverEvent;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 75.0f);

    ArkUIClickEvent clickEvent;
    clickEvent.height = 85.0f;
    event.eventTypeId = C_CLICK_EVENT_ID;
    event.inputEvent = nullptr;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 0.0f);
    event.inputEvent = &clickEvent;
    height = OH_ArkUI_UIInputEvent_GetEventTargetHeight(&event);
    EXPECT_EQ(height, 85.0f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetPositionX001
 * @tc.desc: Test function OH_ArkUI_UIInputEvent_GetEventTargetPositionX.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetPositionX001, TestSize.Level1)
{
    float positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(nullptr);
    EXPECT_EQ(positionX, 0.0f);

    ArkUI_UIInputEvent event;

    ArkUITouchEvent touchEvent;
    touchEvent.targetPositionX = 100.5f;
    event.eventTypeId = C_TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &touchEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 100.5f);

    OHOS::Ace::TouchEvent aceTouchEvent;
    aceTouchEvent.targetPositionX = 200.5f;
    event.eventTypeId = TOUCH_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &aceTouchEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 200.5f);

    OHOS::Ace::AxisEvent aceAxisEvent;
    aceAxisEvent.targetPositionX = 300.5f;
    event.eventTypeId = AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &aceAxisEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 300.5f);

    ArkUIMouseEvent mouseEvent;
    mouseEvent.targetPositionX = 400.5f;
    event.eventTypeId = C_MOUSE_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &mouseEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 400.5f);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetEventTargetPositionX002
 * @tc.desc: Test function OH_ArkUI_UIInputEvent_GetEventTargetPositionX.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetPositionX002, TestSize.Level1)
{
    float positionX = 1.0f;
    ArkUI_UIInputEvent event;

    ArkUIAxisEvent axisEvent;
    axisEvent.targetPositionX = 500.5f;
    event.eventTypeId = C_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &axisEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 500.5f);

    ArkUIFocusAxisEvent focusAxisEvent;
    focusAxisEvent.targetPositionX = 600.5f;
    event.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &focusAxisEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 600.5f);

    ArkUIHoverEvent hoverEvent;
    hoverEvent.targetPositionX = 700.5f;
    event.eventTypeId = C_HOVER_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &hoverEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 700.5f);

    ArkUIClickEvent clickEvent;
    clickEvent.targetPositionX = 800.5f;
    event.eventTypeId = C_CLICK_EVENT_ID;
    event.inputEvent = nullptr;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 0.0f);
    event.inputEvent = &clickEvent;
    positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(&event);
    EXPECT_EQ(positionX, 800.5f);
}
} // namespace OHOS::Ace