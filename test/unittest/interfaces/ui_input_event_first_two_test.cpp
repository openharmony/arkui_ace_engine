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
class UIInputEventTwoTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

/**
 * @tc.name:PointerEventGetDisplayYByIndex008
 * @tc.desc: Test the UIInputEvent property functions in focus axis event case.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTwoTest, PointerEventGetDisplayYByIndex008, TestSize.Level1)
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

/**
 * @tc.name: AxisEventHasAxis001
 * @tc.desc: Test function OH_ArkUI_AxisEvent_HasAxis.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTwoTest, AxisEventHasAxis001, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    ASSERT_NE(uiInputEvent, nullptr);
    auto event = std::make_unique<OHOS::Ace::AxisEvent>();
    ASSERT_NE(event, nullptr);

    event->axes = 7;
    uiInputEvent->inputEvent = static_cast<void*>(event.get());
    uiInputEvent->eventTypeId = AXIS_EVENT_ID;

    auto result = OH_ArkUI_AxisEvent_HasAxis(uiInputEvent.get(), 0);
    EXPECT_TRUE(result);
    result = OH_ArkUI_AxisEvent_HasAxis(uiInputEvent.get(), -1);
    EXPECT_FALSE(result);
    result = OH_ArkUI_AxisEvent_HasAxis(uiInputEvent.get(), 3);
    EXPECT_FALSE(result);
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_AxisEvent_HasAxis(uiInputEvent.get(), 0);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: AxisEventHasAxis002
 * @tc.desc: Test function OH_ArkUI_AxisEvent_HasAxis.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTwoTest, AxisEventHasAxis002, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    ASSERT_NE(uiInputEvent, nullptr);
    auto event = std::make_unique<ArkUIAxisEvent>();
    ASSERT_NE(event, nullptr);

    event->axes = 7;
    uiInputEvent->inputEvent = static_cast<void*>(event.get());
    uiInputEvent->eventTypeId = C_AXIS_EVENT_ID;

    auto result = OH_ArkUI_AxisEvent_HasAxis(uiInputEvent.get(), 0);
    EXPECT_TRUE(result);
    result = OH_ArkUI_AxisEvent_HasAxis(uiInputEvent.get(), -1);
    EXPECT_FALSE(result);
    result = OH_ArkUI_AxisEvent_HasAxis(uiInputEvent.get(), 3);
    EXPECT_FALSE(result);
    uiInputEvent->inputEvent = nullptr;
    result = OH_ArkUI_AxisEvent_HasAxis(uiInputEvent.get(), 3);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: AxisEventHasAxis002
 * @tc.desc: Test function OH_ArkUI_AxisEvent_HasAxis.
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTwoTest, AxisEventHasAxis003, TestSize.Level1)
{
    auto uiInputEvent = std::make_unique<ArkUI_UIInputEvent>();
    ASSERT_NE(uiInputEvent, nullptr);
    auto event = std::make_unique<ArkUIAxisEvent>();
    ASSERT_NE(event, nullptr);

    event->axes = 7;
    uiInputEvent->inputEvent = static_cast<void*>(event.get());
    uiInputEvent->eventTypeId = C_KEY_EVENT_ID;
    auto result = OH_ArkUI_AxisEvent_HasAxis(uiInputEvent.get(), 0);
    EXPECT_FALSE(result);
    result = OH_ArkUI_AxisEvent_HasAxis(nullptr, 0);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OH_ArkUI_UIInputEvent_GetCoastingAxisEvent
 * @tc.desc: Test function OH_ArkUI_UIInputEvent_GetCoastingAxisEvent
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTwoTest, OH_ArkUI_UIInputEvent_GetCoastingAxisEvent, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_COASTING_AXIS_EVENT_ID;

    auto coastingAxisEventPtr = OH_ArkUI_UIInputEvent_GetCoastingAxisEvent(nullptr);
    EXPECT_EQ(coastingAxisEventPtr, nullptr);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);

    auto coastingAxisEvent = std::make_unique<ArkUICoastingAxisEvent>();
    event->inputEvent = static_cast<void*>(coastingAxisEvent.get());
    coastingAxisEventPtr = OH_ArkUI_UIInputEvent_GetCoastingAxisEvent(event.get());
    ASSERT_NE(coastingAxisEventPtr, nullptr);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);

    event->eventTypeId = C_AXIS_EVENT_ID;
    coastingAxisEventPtr = OH_ArkUI_UIInputEvent_GetCoastingAxisEvent(event.get());
    EXPECT_EQ(coastingAxisEventPtr, nullptr);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);

    event->eventTypeId = C_COASTING_AXIS_EVENT_ID;
    event->inputEvent = nullptr;
    coastingAxisEventPtr = OH_ArkUI_UIInputEvent_GetCoastingAxisEvent(event.get());
    EXPECT_EQ(coastingAxisEventPtr, nullptr);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_CoastingAxisEvent_GetEventTime
 * @tc.desc: Test function OH_ArkUI_CoastingAxisEvent_GetEventTime
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTwoTest, GetCoastingAxisEventTime001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_COASTING_AXIS_EVENT_ID;

    auto time = OH_ArkUI_CoastingAxisEvent_GetEventTime(nullptr);
    EXPECT_EQ(time, 0);

    event->inputEvent = nullptr;
    time = OH_ArkUI_CoastingAxisEvent_GetEventTime(OH_ArkUI_UIInputEvent_GetCoastingAxisEvent(event.get()));
    EXPECT_EQ(time, 0);

    auto coastingAxisEvent = std::make_unique<ArkUICoastingAxisEvent>();
    coastingAxisEvent->timeStamp = 100;
    event->inputEvent = static_cast<void*>(coastingAxisEvent.get());
    time = OH_ArkUI_CoastingAxisEvent_GetEventTime(OH_ArkUI_UIInputEvent_GetCoastingAxisEvent(event.get()));
    EXPECT_EQ(time, 100);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: OH_ArkUI_CoastingAxisEvent_GetPhase
 * @tc.desc: Test function OH_ArkUI_CoastingAxisEvent_GetPhase
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTwoTest, GetCoastingAxisEventPhase001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_COASTING_AXIS_EVENT_ID;

    auto phase = OH_ArkUI_CoastingAxisEvent_GetPhase(nullptr);
    EXPECT_EQ(phase, ArkUI_CoastingAxisEventPhase::ARKUI_COASTING_AXIS_EVENT_PHASE_NONE);

    event->inputEvent = nullptr;
    phase = OH_ArkUI_CoastingAxisEvent_GetPhase(OH_ArkUI_UIInputEvent_GetCoastingAxisEvent(event.get()));
    EXPECT_EQ(phase, 0);

    auto coastingAxisEvent = std::make_unique<ArkUICoastingAxisEvent>();
    coastingAxisEvent->phase = ArkUI_CoastingAxisEventPhase::ARKUI_COASTING_AXIS_EVENT_PHASE_BEGIN;
    event->inputEvent = static_cast<void*>(coastingAxisEvent.get());
    phase = OH_ArkUI_CoastingAxisEvent_GetPhase(OH_ArkUI_UIInputEvent_GetCoastingAxisEvent(event.get()));
    EXPECT_EQ(phase, ArkUI_CoastingAxisEventPhase::ARKUI_COASTING_AXIS_EVENT_PHASE_BEGIN);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: OH_ArkUI_CoastingAxisEvent_GetDeltaX
 * @tc.desc: Test function OH_ArkUI_CoastingAxisEvent_GetDeltaX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTwoTest, OH_ArkUI_CoastingAxisEvent_GetDeltaX, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_COASTING_AXIS_EVENT_ID;

    auto ret = OH_ArkUI_CoastingAxisEvent_GetDeltaX(nullptr);
    EXPECT_EQ(ret, 0);

    event->inputEvent = nullptr;
    ret = OH_ArkUI_CoastingAxisEvent_GetDeltaX(OH_ArkUI_UIInputEvent_GetCoastingAxisEvent(event.get()));
    EXPECT_EQ(ret, 0);

    auto coastingAxisEvent = std::make_unique<ArkUICoastingAxisEvent>();
    coastingAxisEvent->deltaX = 100;
    event->inputEvent = static_cast<void*>(coastingAxisEvent.get());
    ret = OH_ArkUI_CoastingAxisEvent_GetDeltaX(OH_ArkUI_UIInputEvent_GetCoastingAxisEvent(event.get()));
    EXPECT_EQ(ret, 100);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: OH_ArkUI_CoastingAxisEvent_GetDeltaY
 * @tc.desc: Test function OH_ArkUI_CoastingAxisEvent_GetDeltaY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTwoTest, OH_ArkUI_CoastingAxisEvent_GetDeltaY, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_COASTING_AXIS_EVENT_ID;

    auto ret = OH_ArkUI_CoastingAxisEvent_GetDeltaY(nullptr);
    EXPECT_EQ(ret, 0);

    event->inputEvent = nullptr;
    ret = OH_ArkUI_CoastingAxisEvent_GetDeltaY(OH_ArkUI_UIInputEvent_GetCoastingAxisEvent(event.get()));
    EXPECT_EQ(ret, 0);

    auto coastingAxisEvent = std::make_unique<ArkUICoastingAxisEvent>();
    coastingAxisEvent->deltaY = 100;
    event->inputEvent = static_cast<void*>(coastingAxisEvent.get());
    ret = OH_ArkUI_CoastingAxisEvent_GetDeltaY(OH_ArkUI_UIInputEvent_GetCoastingAxisEvent(event.get()));
    EXPECT_EQ(ret, 100);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: OH_ArkUI_CoastingAxisEvent_SetPropagation
 * @tc.desc: Test function OH_ArkUI_CoastingAxisEvent_SetPropagation
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTwoTest, OH_ArkUI_CoastingAxisEvent_SetPropagation, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto event = std::make_unique<ArkUI_UIInputEvent>();
    EXPECT_NE(event, nullptr);
    event->eventTypeId = C_COASTING_AXIS_EVENT_ID;

    int32_t ret = OH_ArkUI_CoastingAxisEvent_SetPropagation(nullptr, true);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    event->inputEvent = nullptr;
    ret = OH_ArkUI_CoastingAxisEvent_SetPropagation(OH_ArkUI_UIInputEvent_GetCoastingAxisEvent(event.get()), true);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    auto coastingAxisEvent = std::make_unique<ArkUICoastingAxisEvent>();
    coastingAxisEvent->stopPropagation = true;
    event->inputEvent = static_cast<void*>(coastingAxisEvent.get());
    ret = OH_ArkUI_CoastingAxisEvent_SetPropagation(OH_ArkUI_UIInputEvent_GetCoastingAxisEvent(event.get()), true);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_FALSE(coastingAxisEvent->stopPropagation);
    EXPECT_EQ(OH_ArkUI_UIInputEvent_GetLatestStatus(), ARKUI_ERROR_CODE_NO_ERROR);
}
} // namespace OHOS::Ace