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
#include "test/mock/base/mock_system_properties.h"
#include "test/unittest/core/gestures/gestures_common_test_ng.h"
#include "core/components_ng/event/event_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
constexpr float GESTURE_EVENT_PROPERTY_DEFAULT_VALUE = 0.0;
constexpr float GESTURE_EVENT_PROPERTY_VALUE = 10.0;
class PanRecognizerTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void PanRecognizerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void PanRecognizerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: PanRecognizerPanRecognizerTest001
 * @tc.desc: Test PanRecognizer function PanRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerPanRecognizerTest001, TestSize.Level1)
{
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    RefPtr<PanRecognizer> panRecognizer =
        AceType::MakeRefPtr<PanRecognizer>(FINGER_NUMBER_OVER_MAX, panDirection, 0.0);
    EXPECT_NE(panRecognizer->refereeState_, RefereeState::FAIL);
    panDirection.type = PanDirection::NONE;
    RefPtr<PanRecognizer> panRecognizer1 =
        AceType::MakeRefPtr<PanRecognizer>(FINGER_NUMBER_OVER_MAX, panDirection, 0.0);
    EXPECT_NE(panRecognizer1->refereeState_, RefereeState::FAIL);
    panDirection.type = PanDirection::LEFT;
    RefPtr<PanRecognizer> panRecognizer2 = AceType::MakeRefPtr<PanRecognizer>(FINGER_NUMBER, panDirection, 0.0);
    EXPECT_NE(panRecognizer2->refereeState_, RefereeState::FAIL);
    panDirection.type = PanDirection::RIGHT;
    RefPtr<PanRecognizer> panRecognizer3 = AceType::MakeRefPtr<PanRecognizer>(FINGER_NUMBER, panDirection, 0.0);
    EXPECT_NE(panRecognizer3->refereeState_, RefereeState::FAIL);
    panDirection.type = PanDirection::HORIZONTAL;
    RefPtr<PanRecognizer> panRecognizer4 = AceType::MakeRefPtr<PanRecognizer>(FINGER_NUMBER, panDirection, 0.0);
    EXPECT_NE(panRecognizer4->refereeState_, RefereeState::FAIL);
    panDirection.type = PanDirection::UP;
    RefPtr<PanRecognizer> panRecognizer5 = AceType::MakeRefPtr<PanRecognizer>(0, panDirection, 0.0);
    EXPECT_NE(panRecognizer5->refereeState_, RefereeState::FAIL);
    panDirection.type = PanDirection::DOWN;
    RefPtr<PanRecognizer> panRecognizer6 = AceType::MakeRefPtr<PanRecognizer>(0, panDirection, 0.0);
    EXPECT_NE(panRecognizer6->refereeState_, RefereeState::FAIL);
    panDirection.type = PanDirection::VERTICAL;
    RefPtr<PanRecognizer> panRecognizer7 = AceType::MakeRefPtr<PanRecognizer>(0, panDirection, 0.0);
    EXPECT_NE(panRecognizer7->refereeState_, RefereeState::FAIL);
    panDirection.type = PanDirection::ALL;
    RefPtr<PanRecognizer> panRecognizer8 = AceType::MakeRefPtr<PanRecognizer>(0, panDirection, 0.0);
    EXPECT_NE(panRecognizer8->refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: PanRecognizerPanRecognizerTest002
 * @tc.desc: Test PanRecognizer function PanRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerPanRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panGestureOption->fingers_ = FINGER_NUMBER_OVER_MAX;
    panDirection.type = PanDirection::VERTICAL;
    panGestureOption->SetDirection(panDirection);
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    EXPECT_NE(panRecognizer->refereeState_, RefereeState::SUCCEED);
    panGestureOption->fingers_ = FINGER_NUMBER;
    panDirection.type = PanDirection::NONE;
    panGestureOption->SetDirection(panDirection);
    RefPtr<PanRecognizer> panRecognizer1 = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    EXPECT_NE(panRecognizer1->refereeState_, RefereeState::SUCCEED);
    panGestureOption->fingers_ = FINGER_NUMBER_OVER_MAX;
    panDirection.type = PanDirection::LEFT;
    panGestureOption->SetDirection(panDirection);
    RefPtr<PanRecognizer> panRecognizer2 = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    EXPECT_NE(panRecognizer2->refereeState_, RefereeState::SUCCEED);
    panGestureOption->fingers_ = FINGER_NUMBER;
    panDirection.type = PanDirection::RIGHT;
    panGestureOption->SetDirection(panDirection);
    RefPtr<PanRecognizer> panRecognizer3 = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    EXPECT_NE(panRecognizer3->refereeState_, RefereeState::SUCCEED);
    panGestureOption->fingers_ = FINGER_NUMBER_OVER_MAX;
    panDirection.type = PanDirection::HORIZONTAL;
    panGestureOption->SetDirection(panDirection);
    RefPtr<PanRecognizer> panRecognizer4 = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    EXPECT_NE(panRecognizer4->refereeState_, RefereeState::SUCCEED);
    panGestureOption->fingers_ = 0;
    panDirection.type = PanDirection::UP;
    panGestureOption->SetDirection(panDirection);
    RefPtr<PanRecognizer> panRecognizer5 = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    EXPECT_NE(panRecognizer5->refereeState_, RefereeState::SUCCEED);
    panGestureOption->fingers_ = 0;
    panDirection.type = PanDirection::DOWN;
    panGestureOption->SetDirection(panDirection);
    RefPtr<PanRecognizer> panRecognizer6 = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    EXPECT_NE(panRecognizer6->refereeState_, RefereeState::SUCCEED);
    panGestureOption->fingers_ = 0;
    panDirection.type = PanDirection::DOWN;
    panGestureOption->SetDirection(panDirection);
    RefPtr<PanRecognizer> panRecognizer7 = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    EXPECT_NE(panRecognizer7->refereeState_, RefereeState::SUCCEED);
    panGestureOption->fingers_ = 0;
    panDirection.type = PanDirection::ALL;
    panGestureOption->SetDirection(panDirection);
    RefPtr<PanRecognizer> panRecognizer8 = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    EXPECT_NE(panRecognizer8->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: PanRecognizerTest001
 * @tc.desc: Test PanRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.expected: step2. result equals.
     */
    panRecognizer->inputEventType_ = InputEventType::AXIS;
    panRecognizer->OnAccepted();
    EXPECT_EQ(panRecognizer->refereeState_, RefereeState::SUCCEED);
    panRecognizer->inputEventType_ = InputEventType::TOUCH_SCREEN;
    panRecognizer->OnAccepted();
    EXPECT_EQ(panRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.expected: step3. result equals.
     */
    panRecognizer->OnRejected();
    EXPECT_EQ(panRecognizer->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: PanRecognizerTest002
 * @tc.desc: Test PanRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case1: call TouchEvent, refereeState is SUCCEED, return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    panRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case2: call TouchEvent, normal case
     * @tc.expected: step2. result equals.
     */
    panRecognizer->refereeState_ = RefereeState::PENDING;
    panRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizer->deviceId_, touchEvent.deviceId);
    EXPECT_EQ(panRecognizer->deviceType_, touchEvent.sourceType);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case3: call TouchEvent, set fingerNum != fingers_
     * @tc.expected: step2. result equals.
     */
    panRecognizer->fingers_ = FINGER_NUMBER;
    panRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizer->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case4: call TouchEvent, set fingerNum = fingers_
     * @tc.expected: step2. result equals.
     */
    panRecognizer->fingers_ = 1;
    panRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizer->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case4: call AxisEvent, refereeState is SUCCEED, return
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    panRecognizer->touchPoints_.clear();
    panRecognizer->HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case5: call AxisEvent, refereeState is PENDING, normal case
     * @tc.expected: step2. result equals.
     */
    panRecognizer->refereeState_ = RefereeState::PENDING;
    panRecognizer->HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(panRecognizer->deviceId_, axisEvent.deviceId);
    EXPECT_EQ(panRecognizer->deviceType_, axisEvent.sourceType);
    EXPECT_EQ(panRecognizer->refereeState_, RefereeState::DETECTING);
}

/**
 * @tc.name: PanRecognizerHandleTouchDownEventTest001
 * @tc.desc: Test PanRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerHandleTouchDownEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case1: call TouchEvent, refereeState is SUCCEED, return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    touchEvent.sourceType = SourceType::MOUSE;
    panRecognizer->fingers_ = 1;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    panRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case2: call TouchEvent, normal case
     * @tc.expected: step2. result equals.
     */
    panRecognizer->refereeState_ = RefereeState::PENDING;
    panRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizer->deviceId_, touchEvent.deviceId);
    EXPECT_EQ(panRecognizer->deviceType_, touchEvent.sourceType);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case3: call TouchEvent, set fingerNum != fingers_
     * @tc.expected: step2. result equals.
     */
    panRecognizer->fingers_ = FINGER_NUMBER;
    panRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizer->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case4: call TouchEvent, set fingerNum = fingers_
     * @tc.expected: step2. result equals.
     */
    panRecognizer->fingers_ = 1;
    panRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizer->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case4: call AxisEvent, refereeState is SUCCEED, return
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    panRecognizer->touchPoints_.clear();
    panRecognizer->HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case5: call AxisEvent, refereeState is PENDING, normal case
     * @tc.expected: step2. result equals.
     */
    panRecognizer->refereeState_ = RefereeState::PENDING;
    panRecognizer->HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(panRecognizer->deviceId_, axisEvent.deviceId);
    EXPECT_EQ(panRecognizer->deviceType_, axisEvent.sourceType);
    EXPECT_EQ(panRecognizer->refereeState_, RefereeState::DETECTING);
}

/**
 * @tc.name: PanRecognizerTest003
 * @tc.desc: Test PanRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case1: refereeState is SUCCEED
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    panRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(panRecognizer->globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(panRecognizer->globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(panRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case2: refereeState is SUCCEED, size > 1
     * @tc.expected: step2. result equals.
     */
    panRecognizer->touchPoints_[0] = touchEvent;
    panRecognizer->touchPoints_[1] = touchEvent;
    panRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(panRecognizer->globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(panRecognizer->globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(panRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case3: refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    panRecognizer->refereeState_ = RefereeState::FAIL;
    EXPECT_EQ(panRecognizer->globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(panRecognizer->globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(panRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step3. call HandleTouchUp function and compare result.
     * @tc.steps: case1: refereeState is SUCCEED
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    panRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(panRecognizer->globalPoint_.GetX(), axisEvent.x);
    EXPECT_EQ(panRecognizer->globalPoint_.GetY(), axisEvent.y);

    /**
     * @tc.steps: step3. call HandleTouchUp function and compare result.
     * @tc.steps: case2: refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    panRecognizer->refereeState_ = RefereeState::FAIL;
    panRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(panRecognizer->globalPoint_.GetX(), axisEvent.x);
    EXPECT_EQ(panRecognizer->globalPoint_.GetY(), axisEvent.y);
}

/**
 * @tc.name: PanRecognizerHandleTouchUpEventTest001
 * @tc.desc: Test PanRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerHandleTouchUpEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case1: refereeState is SUCCEED
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(panRecognizer->globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(panRecognizer->globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(panRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case2: refereeState is SUCCEED, size > 1
     * @tc.expected: step2. result equals.
     */
    panRecognizer->touchPoints_[0] = touchEvent;
    panRecognizer->touchPoints_[1] = touchEvent;
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->refereeState_ = RefereeState::FAIL;
    panRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(panRecognizer->globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(panRecognizer->globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(panRecognizer->lastTouchEvent_.id, touchEvent.id);
}

/**
 * @tc.name: PanRecognizerHandleTouchMoveEventTest001
 * @tc.desc: Test PanRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerHandleTouchMoveEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case1: direction.type is VERTICAL
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    panRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->isFlushTouchEventsEnd_ = true;
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizer->globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(panRecognizer->globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(panRecognizer->delta_.GetX(), 0);
    EXPECT_EQ(panRecognizer->delta_.GetY(), 0);
    EXPECT_EQ(panRecognizer->averageDistance_.GetX(), 0);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case2: direction.type is HORIZONTAL
     * @tc.expected: step2. result equals.
     */
    panRecognizer->direction_.type = PanDirection::HORIZONTAL;
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizer->averageDistance_.GetY(), 0);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case3: isFlushTouchEventsEnd_ is false
     * @tc.expected: step2. result equals.
     */
    panRecognizer->isFlushTouchEventsEnd_ = false;
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizer->averageDistance_.GetY(), 0);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case3: isFlushTouchEventsEnd_ is true
     * @tc.expected: step2. result equals.
     */
    panRecognizer->isFlushTouchEventsEnd_ = true;
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizer->averageDistance_.GetY(), 0);
}

/**
 * @tc.name: PanRecognizerTest004
 * @tc.desc: Test PanRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case1: direction.type is VERTICAL
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    panRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->isFlushTouchEventsEnd_ = true;
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizer->globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(panRecognizer->globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(panRecognizer->delta_.GetX(), 0);
    EXPECT_EQ(panRecognizer->delta_.GetY(), 0);
    EXPECT_EQ(panRecognizer->averageDistance_.GetX(), 0);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case2: direction.type is HORIZONTAL
     * @tc.expected: step2. result equals.
     */
    panRecognizer->direction_.type = PanDirection::HORIZONTAL;
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizer->averageDistance_.GetY(), 0);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case3: isFlushTouchEventsEnd_ is false
     * @tc.expected: step2. result equals.
     */
    panRecognizer->isFlushTouchEventsEnd_ = false;
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizer->averageDistance_.GetY(), 0);
}

/**
 * @tc.name: PanRecognizerTest005
 * @tc.desc: Test PanRecognizer function: OnFlushTouchEvents begin end
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.expected: step2. result equals.
     */
    panRecognizer->OnFlushTouchEventsBegin();
    EXPECT_EQ(panRecognizer->isFlushTouchEventsEnd_, false);
    panRecognizer->OnFlushTouchEventsEnd();
    EXPECT_EQ(panRecognizer->isFlushTouchEventsEnd_, true);
}

/**
 * @tc.name: PanRecognizerTest006
 * @tc.desc: Test PanRecognizer function: IsPanGestureAccept
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    APIVersionGuard aPIVersionGuard(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));
    ASSERT_EQ(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY),
        AceApplicationInfo::GetInstance().GetApiTargetVersion());
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. case1: PanDirection::ALL, fabs(offset) >= distance_.
     * @tc.expected: step2. return ACCEPT.
     */
    PanRecognizer::GestureAcceptResult result;
    panRecognizer->direction_.type = PanDirection::ALL;
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case2: PanDirection::ALL, fabs(offset) < distance_.
     * @tc.expected: step2. return DETECTING.
     */
    panRecognizer->direction_.type = PanDirection::ALL;
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(1, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::DETECTING);

    /**
     * @tc.steps: step2. case3: GetX > GetY, GetX < distance, PanDirection::HORIZONTAL.
     * @tc.expected: step2. return DETECTING.
     */
    panRecognizer->direction_.type = PanDirection::HORIZONTAL;
    panRecognizer->averageDistance_ = Offset(0, -1);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(1, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::DETECTING);

    /**
     * @tc.steps: step2. case4: GetX > GetY, GetX > 0, GetX > distance_, PanDirection::LEFT.
     * @tc.expected: step2. return REJECT.
     */
    panRecognizer->direction_.type = PanDirection::LEFT;
    panRecognizer->averageDistance_ = Offset(1, 0);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case5: GetX > GetY, GetX > 0, GetX > distance_, PanDirection::VERTICAL.
     * @tc.expected: step2. return REJECT.
     */
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->averageDistance_ = Offset(1, 0);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case6: GetX > GetY, GetX = distance_ = 0, PanDirection::VERTICAL.
     * @tc.expected: step2. return ACCEPT.
     */
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->averageDistance_ = Offset(0, -1);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);
}

/**
 * @tc.name: PanRecognizerTest007
 * @tc.desc: Test PanRecognizer function: IsPanGestureAccept
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. case7: GetX <= GetY, GetY < distance_, PanDirection::VERTICAL.
     * @tc.expected: step2. return DETECTING.
     */
    PanRecognizer::GestureAcceptResult result;
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->averageDistance_ = Offset(-1, 0);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(1, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::DETECTING);

    /**
     * @tc.steps: step2. case8: GetX <= GetY, GetY > distance_, GetY < 0, PanDirection::DOWN.
     * @tc.expected: step2. return ACCEPT.
     */
    panRecognizer->direction_.type = PanDirection::DOWN;
    panRecognizer->averageDistance_ = Offset(-1, 1);
    panRecognizer->touchPointsDistance_[0] = Offset(-1, 1);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case9: GetX <= GetY, GetY > distance_, GetY > 0, PanDirection::UP.
     * @tc.expected: step2. return ACCEPT.
     */
    panRecognizer->direction_.type = PanDirection::UP;
    panRecognizer->averageDistance_ = Offset(-1, 1);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case10: GetX <= GetY, GetY = distance_ = 0, PanDirection::UP.
     * @tc.expected: step2. return ACCEPT.
     */
    panRecognizer->direction_.type = PanDirection::UP;
    panRecognizer->averageDistance_ = Offset(-1, 0);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);
}

/**
 * @tc.name: PanRecognizerTest008
 * @tc.desc: Test PanRecognizer function: HandleTouchCancelEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call HandleTouchCancel function and compare result.
     * @tc.steps: case1: Touch, refereeState is SUCCEED
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    panRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call HandleTouchCancel function and compare result.
     * @tc.steps: case2: Touch, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    panRecognizer->refereeState_ = RefereeState::FAIL;
    panRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step3. call HandleTouchCancel function and compare result.
     * @tc.steps: case1: Axis, refereeState is SUCCEED
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    panRecognizer->HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step3. call HandleTouchCancel function and compare result.
     * @tc.steps: case2: Axis, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    panRecognizer->refereeState_ = RefereeState::FAIL;
    panRecognizer->HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 0);
}

/**
 * @tc.name: PanRecognizerTest009
 * @tc.desc: Test PanRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case1: onAction is no, *onAction is no
     * @tc.expected: step2. result equals.
     */
    std::unique_ptr<GestureEventFunc> onAction;
    panRecognizer->SendCallbackMsg(onAction, GestureCallbackType::START);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case2: onAction is yes, *onAction is no
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>();
    panRecognizer->SendCallbackMsg(onAction, GestureCallbackType::START);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty, type is AXIS
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    panRecognizer->inputEventType_ = InputEventType::AXIS;
    panRecognizer->SendCallbackMsg(onAction, GestureCallbackType::START);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y, type is not AXIS
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    panRecognizer->lastTouchEvent_ = touchEvent;
    panRecognizer->SendCallbackMsg(onAction, GestureCallbackType::START);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    touchEvent.tiltX = 0.0f;
    touchEvent.tiltY = 0.0f;
    panRecognizer->lastTouchEvent_ = touchEvent;
    panRecognizer->SendCallbackMsg(onAction, GestureCallbackType::START);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 0);
    panRecognizer->SendCallbackMsg(onAction, GestureCallbackType::END);
    EXPECT_TRUE(panRecognizer->localMatrix_.empty());
}

/**
 * @tc.name: PanRecognizerTest010
 * @tc.desc: Test PanRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case1: recognizer is nullptr
     * @tc.expected: step2. result equals.
     */
    auto result = panRecognizer->ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case2: recognizer is normal
     * @tc.expected: step2. result equals.
     */
    result = panRecognizer->ReconcileFrom(panRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case3: fingers not same
     * @tc.expected: step2. result equals.
     */
    panRecognizer->fingers_ = panRecognizerPtr->fingers_ + 1;
    result = panRecognizer->ReconcileFrom(panRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case4: fingers not same, priority not same
     * @tc.expected: step2. result equals.
     */
    panRecognizer->priorityMask_ = GestureMask::End;
    result = panRecognizer->ReconcileFrom(panRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case4: fingers same, priority not same
     * @tc.expected: step2. result equals.
     */
    panRecognizer->fingers_ = panRecognizerPtr->fingers_;
    result = panRecognizer->ReconcileFrom(panRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PanRecognizerTest012
 * @tc.desc: Test PanRecognizer function: ChangeFingers
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call ChangeFingers function
     * @tc.steps: case1: fingers not same
     * @tc.expected: step2. result equals.
     */
    panRecognizer->fingers_ = 0;
    panRecognizer->ChangeFingers(1);
    EXPECT_EQ(panRecognizer->newFingers_, 1);

    /**
     * @tc.steps: step2. call ChangeFingers function
     * @tc.steps: case1: fingers not same
     * @tc.expected: step2. result equals.
     */
    panRecognizer->fingers_ = 1;
    panRecognizer->ChangeFingers(1);
    EXPECT_EQ(panRecognizer->newFingers_, 1);
}

/**
 * @tc.name: PanRecognizerTest013
 * @tc.desc: Test PanRecognizer function: ChangeDirection
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call ChangeDirection function
     * @tc.steps: case1: type not same
     * @tc.expected: step2. result equals.
     */
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    panRecognizer->direction_.type = PanDirection::HORIZONTAL;
    panRecognizer->ChangeDirection(panDirection);
    EXPECT_EQ(panRecognizer->direction_.type, PanDirection::VERTICAL);
    EXPECT_EQ(panRecognizer->newDirection_.type, PanDirection::VERTICAL);

    /**
     * @tc.steps: step2. call ChangeDirection function
     * @tc.steps: case2: type same
     * @tc.expected: step2. result equals.
     */
    panDirection.type = PanDirection::VERTICAL;
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->ChangeDirection(panDirection);
    EXPECT_EQ(panRecognizer->direction_.type, PanDirection::VERTICAL);
    EXPECT_EQ(panRecognizer->newDirection_.type, PanDirection::VERTICAL);
}

/**
 * @tc.name: PanRecognizerTest014
 * @tc.desc: Test PanRecognizer function: ChangeDistance
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case1: distance not same, refereeState is READY
     * @tc.expected: step2. result equals.
     */
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    panRecognizer->ChangeDistance(1);
    panRecognizer->refereeState_ = RefereeState::READY;
    EXPECT_EQ(panRecognizer->distanceMap_[SourceTool::UNKNOWN].ConvertToPx(), 1);
    EXPECT_EQ(panRecognizer->newDistanceMap_[SourceTool::UNKNOWN].ConvertToPx(), 1);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case2: distance not same, refereeState is DETECTING
     * @tc.expected: step2. result equals.
     */
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    panRecognizer->ChangeDistance(1);
    panRecognizer->refereeState_ = RefereeState::DETECTING;
    EXPECT_EQ(panRecognizer->distanceMap_[SourceTool::UNKNOWN].ConvertToPx(), 1);
    EXPECT_EQ(panRecognizer->newDistanceMap_[SourceTool::UNKNOWN].ConvertToPx(), 1);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case3: distance not same, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    panRecognizer->ChangeDistance(1);
    panRecognizer->refereeState_ = RefereeState::FAIL;
    EXPECT_EQ(panRecognizer->distanceMap_[SourceTool::UNKNOWN].ConvertToPx(), 1);
    EXPECT_EQ(panRecognizer->newDistanceMap_[SourceTool::UNKNOWN].ConvertToPx(), 1);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case4: distance same
     * @tc.expected: step2. result equals.
     */
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    panRecognizer->ChangeDistance(0);
    panRecognizer->refereeState_ = RefereeState::FAIL;
    EXPECT_EQ(panRecognizer->distanceMap_[SourceTool::UNKNOWN].ConvertToPx(), 0);
    EXPECT_EQ(panRecognizer->newDistanceMap_[SourceTool::UNKNOWN].ConvertToPx(), 1);
}

/**
 * @tc.name: PanRecognizerSendCallbackMsgTest001
 * @tc.desc: Test PanRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerSendCallbackMsgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case1: onAction is no, *onAction is no
     * @tc.expected: step2. result equals.
     */
    std::unique_ptr<GestureEventFunc> onAction = std::make_unique<GestureEventFunc>();
    panRecognizer->inputEventType_ = InputEventType::TOUCH_SCREEN;
    panRecognizer->SendCallbackMsg(onAction, GestureCallbackType::START);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 0);
}

/**
 * @tc.name: PanRecognizerSendCallbackMsgTest002
 * @tc.desc: Test PanRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerSendCallbackMsgTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. SendCallbackMsg
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    panRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 1);
    std::unique_ptr<GestureEventFunc> onAction;
    panRecognizer->SendCallbackMsg(onAction, GestureCallbackType::START);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 1);
}

/**
 * @tc.name: PanRecognizerChangeDistanceTest001
 * @tc.desc: Test PanRecognizer function: ChangeDistance
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerChangeDistanceTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case1: distance not same, refereeState is READY
     * @tc.expected: step2. result equals.
     */
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    panRecognizer->refereeState_ = RefereeState::READY;
    panRecognizer->ChangeDistance(1);
    EXPECT_EQ(panRecognizer->distanceMap_[SourceTool::UNKNOWN].ConvertToPx(), 1);
    EXPECT_EQ(panRecognizer->newDistanceMap_[SourceTool::UNKNOWN].ConvertToPx(), 1);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case2: distance not same, refereeState is DETECTING
     * @tc.expected: step2. result equals.
     */
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    panRecognizer->refereeState_ = RefereeState::DETECTING;
    panRecognizer->ChangeDistance(1);
    EXPECT_EQ(panRecognizer->distanceMap_[SourceTool::UNKNOWN].ConvertToPx(), 1);
    EXPECT_EQ(panRecognizer->newDistanceMap_[SourceTool::UNKNOWN].ConvertToPx(), 1);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case3: distance not same, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    panRecognizer->refereeState_ = RefereeState::FAIL;
    panRecognizer->ChangeDistance(1);
    EXPECT_EQ(panRecognizer->newDistanceMap_[SourceTool::UNKNOWN].ConvertToPx(), 1);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case4: distance same
     * @tc.expected: step2. result equals.
     */
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    panRecognizer->refereeState_ = RefereeState::FAIL;
    panRecognizer->ChangeDistance(1);
    EXPECT_EQ(panRecognizer->distanceMap_[SourceTool::UNKNOWN].ConvertToPx(), 0);
    EXPECT_EQ(panRecognizer->newDistanceMap_[SourceTool::UNKNOWN].ConvertToPx(), 1);
}

/**
 * @tc.name: PanRecognizerTest015
 * @tc.desc: Test PanRecognizer function: GetMainAxisDelta
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case1: directionType is ALL
     * @tc.expected: step2. result equals.
     */
    PanDirection panDirection;
    panRecognizer->direction_ = panDirection;
    panRecognizer->direction_.type = PanDirection::ALL;
    auto result = panRecognizer->GetMainAxisDelta();
    EXPECT_EQ(result, 0);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case2: directionType is HORIZONTAL
     * @tc.expected: step2. result equals.
     */
    panRecognizer->direction_.type = PanDirection::HORIZONTAL;
    result = panRecognizer->GetMainAxisDelta();
    EXPECT_EQ(result, 0);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case3: directionType is VERTICAL
     * @tc.expected: step2. result equals.
     */
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    result = panRecognizer->GetMainAxisDelta();
    EXPECT_EQ(result, 0);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case4: directionType is LEFT
     * @tc.expected: step2. result equals.
     */
    panRecognizer->direction_.type = PanDirection::LEFT;
    result = panRecognizer->GetMainAxisDelta();
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: PanRecognizerTest016
 * @tc.desc: Test PanRecognizer function: PanRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();

    /**
     * @tc.steps: step2. call PanRecognizer function
     * @tc.steps: case1: 0 <= direction.type <= 15
     * @tc.expected: step2. result equals.
     */
    RefPtr<PanRecognizer> panRecognizer1 = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    EXPECT_EQ(panRecognizer1->direction_.type, PanDirection::ALL);

    /**
     * @tc.steps: step2. call PanRecognizer function
     * @tc.steps: case1: 0 > direction.type
     * @tc.expected: step2. result equals.
     */
    panGestureOption->direction_.type = -1;
    RefPtr<PanRecognizer> panRecognizer2 = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    EXPECT_EQ(panRecognizer2->direction_.type, PanDirection::ALL);

    /**
     * @tc.steps: step2. call PanRecognizer function
     * @tc.steps: case1: 0 > direction.type
     * @tc.expected: step2. result equals.
     */
    panGestureOption->direction_.type = PanDirection::ALL + 1;
    RefPtr<PanRecognizer> panRecognizer3 = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    EXPECT_EQ(panRecognizer3->direction_.type, PanDirection::ALL);
}

/**
 * @tc.name: PanRecognizerTest017
 * @tc.desc: Test PanRecognizer function: HandleTouchMoveEvent(AxisEvent)
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    AxisEvent axisEvent;

    /**
     * @tc.steps: step2. call HandleTouchMove function and compare result.
     * @tc.steps: case1: fingers_ is 0, return
     * @tc.expected: step2. result equals.
     */
    panRecognizer->fingers_ = 0;
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call HandleTouchMove function and compare result.
     * @tc.steps: case2: fingers_ is 1, direction is VERTICAL, refereeState is SUCCEED
     * @tc.expected: step2. result equals.
     */
    panRecognizer->fingers_ = 1;
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 1);
    EXPECT_EQ(panRecognizer->delta_.GetX(), 0);
    EXPECT_EQ(panRecognizer->delta_.GetY(), 0);

    /**
     * @tc.steps: step2. call HandleTouchMove function and compare result.
     * @tc.steps: case3: fingers_ is 1, direction is HORIZONTAL, refereeState is SUCCEED
     * @tc.steps: case3: event.horizontalAxis = 0
     * @tc.expected: step2. result equals.
     */
    panRecognizer->direction_.type = PanDirection::HORIZONTAL;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    axisEvent.horizontalAxis = 0;
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 1);
    EXPECT_EQ(panRecognizer->delta_.GetX(), 0);
    EXPECT_EQ(panRecognizer->delta_.GetY(), 0);

    /**
     * @tc.steps: step2. call HandleTouchMove function and compare result.
     * @tc.steps: case3: fingers_ is 1, direction is HORIZONTAL, refereeState is PENDING
     * @tc.steps: case3: event.horizontalAxis != 0
     * @tc.expected: step2. result equals.
     */
    panRecognizer->direction_.type = PanDirection::HORIZONTAL;
    panRecognizer->refereeState_ = RefereeState::PENDING;
    axisEvent.horizontalAxis = 1;
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 1);
}

/**
 * @tc.name: PanRecognizerTest018
 * @tc.desc: Test PanRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    ASSERT_NE(panRecognizer, nullptr);

    /**
     * @tc.steps: step2. test with HandleTouchDownEvent(AxisEvent).
     * @tc.expect: panRecognizer->lastAxisEvent_ is equal to axisEvent
     * @tc.expect: panRecognizer->touchPoints_[axisEvent.id].originalId is equal to axisEvent.originalId
     * @tc.expect: panRecognizer->touchPoints_[axisEvent.id].screenX is equal to axisEvent.screenX
     * @tc.expect: panRecognizer->touchPoints_[axisEvent.id].screenY is equal to axisEvent.screenY
     */
    AxisEvent axisEvent;
    axisEvent.id = TEST_EVENT_ID;
    axisEvent.originalId = TEST_EVENT_ID;
    axisEvent.isRotationEvent = false;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    panRecognizer->fingers_ = SINGLE_FINGER_NUMBER;
    panRecognizer->direction_.type = PanDirection::HORIZONTAL;
    panRecognizer->HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(panRecognizer->lastAxisEvent_.id, axisEvent.id);
    EXPECT_EQ(panRecognizer->touchPoints_[axisEvent.id].originalId, axisEvent.originalId);
    EXPECT_EQ(panRecognizer->touchPoints_[axisEvent.id].screenX, axisEvent.screenX);
    EXPECT_EQ(panRecognizer->touchPoints_[axisEvent.id].screenY, axisEvent.screenY);
}

/**
 * @tc.name: PanRecognizerTest019
 * @tc.desc: Test PanRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    ASSERT_NE(panRecognizer, nullptr);

    /**
     * @tc.steps: step2. test with HandleTouchUpEvent(AxisEvent).
     * @tc.expect: panRecognizer->lastAxisEvent_ is equal to axisEvent
     */
    AxisEvent axisEvent;
    axisEvent.id = TEST_EVENT_ID;
    axisEvent.isRotationEvent = false;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    panRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(panRecognizer->lastAxisEvent_.id, axisEvent.id);
}

/**
 * @tc.name: PanRecognizerTest020
 * @tc.desc: Test PanRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    ASSERT_NE(panRecognizer, nullptr);

    /**
     * @tc.steps: step2. test with HandleTouchMoveEvent(AxisEvent).
     * @tc.expect: panRecognizer->lastAxisEvent_ is equal to axisEvent
     */
    AxisEvent axisEvent;
    axisEvent.id = TEST_EVENT_ID;
    axisEvent.isRotationEvent = false;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    panRecognizer->fingers_ = SINGLE_FINGER_NUMBER;
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(panRecognizer->lastAxisEvent_.id, axisEvent.id);
}

/**
 * @tc.name: PanRecognizerSendCallbackMsgTest003
 * @tc.desc: Test PanRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerSendCallbackMsgTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    std::unique_ptr<GestureEventFunc> onAction;

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty, type is AXIS
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    panRecognizer->inputEventType_ = InputEventType::AXIS;
    panRecognizer->SendCallbackMsg(onAction, GestureCallbackType::START);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y, type is not AXIS
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    panRecognizer->lastTouchEvent_ = touchEvent;
    panRecognizer->inputEventType_ = InputEventType::AXIS;
    panRecognizer->SendCallbackMsg(onAction, GestureCallbackType::START);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    touchEvent.tiltX = 0.0f;
    touchEvent.tiltY = 0.0f;
    panRecognizer->lastTouchEvent_ = touchEvent;
    panRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    panRecognizer->inputEventType_ = InputEventType::AXIS;
    panRecognizer->SendCallbackMsg(onAction, GestureCallbackType::START);
    EXPECT_EQ(panRecognizer->touchPoints_.size(), 1);
}

/*
 * @tc.name: PanGestureTest001
 * @tc.desc: Test PanGesture CreateRecognizer function
 */
HWTEST_F(PanRecognizerTestNg, PanGestureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanGesture.
     */
    auto panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    auto panGesture = AceType::MakeRefPtr<PanGesture>(panGestureOption);
    ASSERT_NE(panGesture, nullptr);
    EXPECT_EQ(panGesture->panGestureOption_->fingers_, panGestureOption->fingers_);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result.
     * @tc.expect: panRecognizer create successfully, use the same Option as panGesture.
     */
    panGesture->priority_ = GesturePriority::Low;
    panGesture->gestureMask_ = GestureMask::Normal;
    auto panRecognizer = AceType::DynamicCast<PanRecognizer>(panGesture->CreateRecognizer());
    ASSERT_NE(panRecognizer, nullptr);
    EXPECT_EQ(panRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(panRecognizer->GetPriorityMask(), GestureMask::Normal);
    EXPECT_EQ(panRecognizer->distanceMap_[SourceTool::UNKNOWN], DEFAULT_PAN_DISTANCE);
}

/**
 * @tc.name: PanGestureTest002
 * @tc.desc: Test PanGesture CreateRecognizer function
 */
HWTEST_F(PanRecognizerTestNg, PanGestureTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanGesture.
     */
    PanDirection panDirection;
    panDirection.type = PanDirection::RIGHT;
    auto panGesture = AceType::MakeRefPtr<PanGesture>(SINGLE_FINGER_NUMBER, panDirection, PAN_DISTANCE);
    ASSERT_NE(panGesture, nullptr);
    EXPECT_EQ(panGesture->fingers_, SINGLE_FINGER_NUMBER);

    /**
     * @tc.steps: step2. create onActionStart, onActionUpdate, onActionEnd, onActionCancel for PanRecognizer.
     * @tc.expect: panRecognizer create successfully with the OnActionCall.
     */
    panGesture->priority_ = GesturePriority::Low;
    panGesture->gestureMask_ = GestureMask::Normal;
    auto onActionStart = [](GestureEvent& info) { return true; };
    auto onActionUpdate = [](GestureEvent& info) { return true; };
    auto onActionEnd = [](GestureEvent& info) { return true; };
    auto onActionCancel = [](GestureEvent& info) { return true; };
    panGesture->SetOnActionStartId(onActionStart);
    panGesture->SetOnActionUpdateId(onActionUpdate);
    panGesture->SetOnActionEndId(onActionEnd);
    panGesture->SetOnActionCancelId(onActionCancel);
    EXPECT_TRUE(panGesture->onActionStartId_);
    EXPECT_TRUE(panGesture->onActionUpdateId_);
    EXPECT_TRUE(panGesture->onActionEndId_);
    EXPECT_TRUE(panGesture->onActionCancelId_);

    auto panRecognizer = AceType::DynamicCast<PanRecognizer>(panGesture->CreateRecognizer());
    ASSERT_NE(panRecognizer, nullptr);
    EXPECT_EQ(panRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(panRecognizer->GetPriorityMask(), GestureMask::Normal);
}

/**
 * @tc.name: PanRecognizerHandleTouchDownEventTest003
 * @tc.desc: Test PanRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerHandleTouchDownEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;
    touchEvent.sourceType = SourceType::MOUSE;

    panRecognizerPtr->direction_.type = PanDirection::NONE;
    panRecognizerPtr->isAllowMouse_ = false;
    panRecognizerPtr->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizerPtr->globalPoint_.GetX(), 0);
}


/**
 * @tc.name: PanRecognizerHandleTouchCancelEventTest003
 * @tc.desc: Test PanRecognizer function: HandleTouchCancelEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerHandleTouchCancelEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;
    touchEvent.sourceType = SourceType::MOUSE;
    AxisEvent axisEvent;

    panRecognizerPtr->refereeState_ = RefereeState::PENDING_BLOCKED;
    panRecognizerPtr->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(panRecognizerPtr->globalPoint_.GetX(), 0);

    panRecognizerPtr->refereeState_ = RefereeState::PENDING_BLOCKED;
    panRecognizerPtr->HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(panRecognizerPtr->globalPoint_.GetX(), 0);
}

/**
 * @tc.name: PanRecognizerOnRejectedTest001
 * @tc.desc: Test PanRecognizer function: OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerOnRejectedTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    panRecognizerPtr->refereeState_ = RefereeState::PENDING_BLOCKED;
    panRecognizerPtr->OnRejected();
    EXPECT_EQ(panRecognizerPtr->globalPoint_.GetX(), 0);
}

/**
 * @tc.name: PanRecognizerHandleTouchDownEventTest004
 * @tc.desc: Test PanRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerHandleTouchDownEventTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;
    touchEvent.sourceType = SourceType::MOUSE;

    panRecognizerPtr->newDirection_.type = PanDirection::NONE;
    panRecognizerPtr->isAllowMouse_ = false;
    panRecognizerPtr->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizerPtr->globalPoint_.GetX(), 0);
    EXPECT_EQ(panRecognizerPtr->fingersId_.size(), 1);
}

/**
 * @tc.name: PanRecognizerHandleTouchDownEventTest005
 * @tc.desc: Test PanRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerHandleTouchDownEventTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;
    touchEvent.sourceType = SourceType::MOUSE;
    AxisEvent axisEvent;

    panRecognizerPtr->newDirection_.type = PanDirection::NONE;
    panRecognizerPtr->newFingers_ = 1;
    panRecognizerPtr->isAllowMouse_ = false;
    panRecognizerPtr->HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(panRecognizerPtr->globalPoint_.GetX(), 0);

    panRecognizerPtr->newDirection_.type = PanDirection::NONE;
    panRecognizerPtr->newFingers_ = FINGER_NUMBER;
    panRecognizerPtr->isAllowMouse_ = false;
    panRecognizerPtr->HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(panRecognizerPtr->globalPoint_.GetX(), 0);
}

/**
 * @tc.name: PanRecognizerHandleTouchMoveEventTest005
 * @tc.desc: Test PanRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerHandleTouchMoveEventTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;
    touchEvent.sourceType = SourceType::MOUSE;

    panRecognizerPtr->fingers_ = 11;
    panRecognizerPtr->currentFingers_ = panRecognizerPtr->fingers_;
    panRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    panRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizerPtr->globalPoint_.GetX(), 0);

    panRecognizerPtr->fingers_ = 0;
    panRecognizerPtr->currentFingers_ = panRecognizerPtr->fingers_;
    panRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    panRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizerPtr->globalPoint_.GetX(), touchEvent.x);
}

/**
 * @tc.name: PanRecognizerHandleTouchMoveEventTest006
 * @tc.desc: Test PanRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerHandleTouchMoveEventTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    APIVersionGuard aPIVersionGuard(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));
    ASSERT_EQ(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY),
        AceApplicationInfo::GetInstance().GetApiTargetVersion());
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;

    /**
     * @tc.steps: step2. case1: PanDirection::ALL, fabs(offset) >= distance_.
     * @tc.expected: step2. return ACCEPT.
     */
    PanRecognizer::GestureAcceptResult result;
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->refereeState_ = RefereeState::DETECTING;
    panRecognizer->direction_.type = PanDirection::ALL;
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case2: PanDirection::ALL, fabs(offset) < distance_.
     * @tc.expected: step2. return DETECTING.
     */
    panRecognizer->direction_.type = PanDirection::ALL;
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(1, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::DETECTING);

    /**
     * @tc.steps: step2. case3: GetX > GetY, GetX < distance, PanDirection::HORIZONTAL.
     * @tc.expected: step2. return DETECTING.
     */
    panRecognizer->direction_.type = PanDirection::HORIZONTAL;
    panRecognizer->averageDistance_ = Offset(0, -1);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(1, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::DETECTING);

    /**
     * @tc.steps: step2. case4: GetX > GetY, GetX > 0, GetX > distance_, PanDirection::LEFT.
     * @tc.expected: step2. return REJECT.
     */
    panRecognizer->direction_.type = PanDirection::LEFT;
    panRecognizer->averageDistance_ = Offset(1, 0);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case5: GetX > GetY, GetX > 0, GetX > distance_, PanDirection::VERTICAL.
     * @tc.expected: step2. return REJECT.
     */
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->averageDistance_ = Offset(1, 0);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case6: GetX > GetY, GetX = distance_ = 0, PanDirection::VERTICAL.
     * @tc.expected: step2. return ACCEPT.
     */
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->averageDistance_ = Offset(0, -1);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);
}

/**
 * @tc.name: PanRecognizerHandleTouchMoveEventTest007
 * @tc.desc: Test PanRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerHandleTouchMoveEventTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. case1: PanDirection::ALL, fabs(offset) >= distance_.
     * @tc.expected: step2. return ACCEPT.
     */
    PanRecognizer::GestureAcceptResult result;
    panRecognizer->direction_.type = PanDirection::ALL;
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->refereeState_ = RefereeState::DETECTING;
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    panRecognizer->direction_.type = PanDirection::ALL;
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(1, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->refereeState_ = RefereeState::DETECTING;
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::DETECTING);

    /**
     * @tc.steps: step2. case3: GetX > GetY, GetX < distance, PanDirection::HORIZONTAL.
     * @tc.expected: step2. return ACCEPT.
     */
    panRecognizer->direction_.type = PanDirection::HORIZONTAL;
    panRecognizer->averageDistance_ = Offset(0, -1);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(1, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->refereeState_ = RefereeState::DETECTING;
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    panRecognizer->direction_.type = PanDirection::LEFT;
    panRecognizer->averageDistance_ = Offset(1, 0);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->refereeState_ = RefereeState::DETECTING;
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case5: GetX > GetY, GetX > 0, GetX > distance_, PanDirection::VERTICAL.
     * @tc.expected: step2. return REJECT.
     */
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->averageDistance_ = Offset(1, 0);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->refereeState_ = RefereeState::DETECTING;
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->averageDistance_ = Offset(0, -1);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->refereeState_ = RefereeState::DETECTING;
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);
}

/**
 * @tc.name: PanRecognizerHandleTouchMoveEventTest008
 * @tc.desc: Test PanRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerHandleTouchMoveEventTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    AxisEvent axisEvent;

    panRecognizerPtr->fingers_ = 11;
    panRecognizerPtr->currentFingers_ = panRecognizerPtr->fingers_;
    panRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    panRecognizerPtr->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(panRecognizerPtr->globalPoint_.GetX(), 0);

    panRecognizerPtr->fingers_ = 0;
    panRecognizerPtr->currentFingers_ = panRecognizerPtr->fingers_;
    panRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    panRecognizerPtr->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(panRecognizerPtr->globalPoint_.GetX(), 0);
}

/**
 * @tc.name: PanRecognizerHandleTouchMoveEventTest009
 * @tc.desc: Test PanRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerHandleTouchMoveEventTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    APIVersionGuard aPIVersionGuard(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));
    ASSERT_EQ(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY),
        AceApplicationInfo::GetInstance().GetApiTargetVersion());
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    AxisEvent axisEvent;

    /**
     * @tc.steps: step2. case1: PanDirection::ALL, fabs(offset) >= distance_.
     * @tc.expected: step2. return ACCEPT.
     */
    PanRecognizer::GestureAcceptResult result;
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->refereeState_ = RefereeState::DETECTING;
    panRecognizer->direction_.type = PanDirection::ALL;
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case2: PanDirection::ALL, fabs(offset) < distance_.
     * @tc.expected: step2. return DETECTING.
     */
    panRecognizer->direction_.type = PanDirection::ALL;
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(1, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::DETECTING);

    /**
     * @tc.steps: step2. case3: GetX > GetY, GetX < distance, PanDirection::HORIZONTAL.
     * @tc.expected: step2. return DETECTING.
     */
    panRecognizer->direction_.type = PanDirection::HORIZONTAL;
    panRecognizer->averageDistance_ = Offset(0, -1);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(1, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::DETECTING);

    /**
     * @tc.steps: step2. case4: GetX > GetY, GetX > 0, GetX > distance_, PanDirection::LEFT.
     * @tc.expected: step2. return REJECT.
     */
    panRecognizer->direction_.type = PanDirection::LEFT;
    panRecognizer->averageDistance_ = Offset(1, 0);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case5: GetX > GetY, GetX > 0, GetX > distance_, PanDirection::VERTICAL.
     * @tc.expected: step2. return REJECT.
     */
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->averageDistance_ = Offset(1, 0);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case6: GetX > GetY, GetX = distance_ = 0, PanDirection::VERTICAL.
     * @tc.expected: step2. return ACCEPT.
     */
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->averageDistance_ = Offset(0, -1);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);
}

/**
 * @tc.name: PanRecognizerHandleTouchMoveEventTest010
 * @tc.desc: Test PanRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerHandleTouchMoveEventTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    AxisEvent axisEvent;

    /**
     * @tc.steps: step2. case1: PanDirection::ALL, fabs(offset) >= distance_.
     * @tc.expected: step2. return ACCEPT.
     */
    PanRecognizer::GestureAcceptResult result;
    panRecognizer->direction_.type = PanDirection::ALL;
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->refereeState_ = RefereeState::DETECTING;
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    panRecognizer->direction_.type = PanDirection::ALL;
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(1, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->refereeState_ = RefereeState::DETECTING;
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::DETECTING);

    /**
     * @tc.steps: step2. case3: GetX > GetY, GetX < distance, PanDirection::HORIZONTAL.
     * @tc.expected: step2. return ACCEPT.
     */
    panRecognizer->direction_.type = PanDirection::HORIZONTAL;
    panRecognizer->averageDistance_ = Offset(0, -1);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(1, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->refereeState_ = RefereeState::DETECTING;
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    panRecognizer->direction_.type = PanDirection::LEFT;
    panRecognizer->averageDistance_ = Offset(1, 0);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->refereeState_ = RefereeState::DETECTING;
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case5: GetX > GetY, GetX > 0, GetX > distance_, PanDirection::VERTICAL.
     * @tc.expected: step2. return REJECT.
     */
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->averageDistance_ = Offset(1, 0);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->refereeState_ = RefereeState::DETECTING;
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->averageDistance_ = Offset(0, -1);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->refereeState_ = RefereeState::DETECTING;
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);
}

/**
 * @tc.name: PanRecognizerHandleTouchMoveEventTest011
 * @tc.desc: Test PanRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerHandleTouchMoveEventTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    APIVersionGuard aPIVersionGuard(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    ASSERT_EQ(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN),
        AceApplicationInfo::GetInstance().GetApiTargetVersion());
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    AxisEvent axisEvent;
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;
    PanRecognizer::GestureAcceptResult result;
    
    /**
     * @tc.steps: step2. case1: GetX > GetY, GetX > 0, GetX > distance_, PanDirection::LEFT.
     * @tc.expected: step2. return ACCEPT.
     */
    panRecognizer->direction_.type = PanDirection::LEFT;
    panRecognizer->averageDistance_ = Offset(1, 0);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case2: GetX > GetY, GetX > 0, GetX > distance_, PanDirection::VERTICAL.
     * @tc.expected: step2. return ACCEPT.
     */
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->averageDistance_ = Offset(1, 0);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case3: GetX > GetY, GetX > 0, GetX > distance_, PanDirection::LEFT.
     * @tc.expected: step2. return ACCEPT.
     */
    panRecognizer->direction_.type = PanDirection::LEFT;
    panRecognizer->averageDistance_ = Offset(1, 0);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case4: GetX > GetY, GetX > 0, GetX > distance_, PanDirection::VERTICAL.
     * @tc.expected: step2. return ACCEPT.
     */
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->averageDistance_ = Offset(1, 0);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);
    
    /**
     * @tc.steps: step2. case5: GetX > GetY, GetX > 0, GetX > distance_, PanDirection::LEFT.
     * @tc.expected: step2. return ACCEPT.
     */
    panRecognizer->direction_.type = PanDirection::LEFT;
    panRecognizer->averageDistance_ = Offset(1, 0);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case6: GetX > GetY, GetX > 0, GetX > distance_, PanDirection::VERTICAL.
     * @tc.expected: step2. return ACCEPT.
     */
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->averageDistance_ = Offset(1, 0);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    panRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);
}

/**
 * @tc.name: PanRecognizerHandleTouchUpEvent002
 * @tc.desc: Test HandleTouchUpEvent in PanRecognizer
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerHandleTouchUpEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    TouchEvent touchEvent;

    panRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    panRecognizerPtr->fingers_ = 0;
    panRecognizerPtr->isForDrag_ = true;
    panRecognizerPtr->currentFingers_ = panRecognizerPtr->fingers_;
    panRecognizerPtr->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(panRecognizerPtr->refereeState_, RefereeState::FAIL);

    panRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    panRecognizerPtr->fingers_ = 0;
    panRecognizerPtr->isForDrag_ = false;
    panRecognizerPtr->currentFingers_ = panRecognizerPtr->fingers_;
    panRecognizerPtr->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(panRecognizerPtr->refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: PanRecognizerHandleTouchUpEvent005
 * @tc.desc: Test HandleTouchUpEvent in PanRecognizer
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerHandleTouchUpEvent005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    AxisEvent axisEvent;

    panRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    panRecognizerPtr->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(panRecognizerPtr->refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: SetOnActionCancelTest001
 * @tc.desc: Test SendCallbackMsg function in the HandleTouchCancelEvent with touch event input. The onActionCancel
 * function will return GestureEvent info.
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, SetOnActionCancelTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizerTestNg.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. Call SetOnActionCancel.
     * @tc.expected: panRecognizer's callback onActionCancel is not nullptr.
     */
    panRecognizer->deviceId_ = GESTURE_EVENT_PROPERTY_VALUE;
    double unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    auto onActionCancel = [&unknownPropertyValue](
                                GestureEvent& info) { unknownPropertyValue = info.GetDeviceId(); };
    panRecognizer->SetOnActionCancel(onActionCancel);
    EXPECT_NE(panRecognizer->onActionCancel_, nullptr);

    /**
     * @tc.steps: step3. Invoke HandleTouchCancelEvent when onActionCancel_ is not null.
     * @tc.expected: The functions have been executed and the unknownPropertyValue has been assigned the correct
     * value. panRecognizer->refereeState_ = RefereeState::READY
     */
    TouchEvent touchEvent;
    panRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    panRecognizer->currentFingers_ = panRecognizer->fingers_;
    panRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
    EXPECT_EQ(panRecognizer->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: SetOnActionCancelTest002
 * @tc.desc: Test SendCallbackMsg function in the HandleTouchCancelEvent with axis event input. The onActionCancel
 * function will return GestureEvent info.
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, SetOnActionCancelTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizerTestNg.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. Call SetOnActionCancel.
     * @tc.expected: panRecognizerPtr's callback onActionCancel is not nullptr.
     */
    panRecognizer->deviceId_ = GESTURE_EVENT_PROPERTY_VALUE;
    double unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    auto onActionCancel = [&unknownPropertyValue](
                                GestureEvent& info) { unknownPropertyValue = info.GetDeviceId(); };
    panRecognizer->SetOnActionCancel(onActionCancel);
    EXPECT_NE(panRecognizer->onActionCancel_, nullptr);

    /**
     * @tc.steps: step3. Invoke HandleTouchCancelEvent when onActionCancel_ is not null.
     * @tc.expected: The functions have been executed and the unknownPropertyValue has been assigned the correct
     * value.
     */
    AxisEvent axisEvent;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    panRecognizer->HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
}

/**
 * @tc.name: SetOnActionCancelTest003
 * @tc.desc: Test SendCallbackMsg function in the ReconcileFrom. The onActionCancel function will return
 * GestureEvent info.
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, SetOnActionCancelTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. Call SetOnActionCancel.
     * @tc.expected: panRecognizer's callback onActionCancel is not nullptr.
     */
    panRecognizer->deviceId_ = GESTURE_EVENT_PROPERTY_VALUE;
    double unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    auto onActionCancel = [&unknownPropertyValue](
                                GestureEvent& info) { unknownPropertyValue = info.GetDeviceId(); };
    panRecognizer->SetOnActionCancel(onActionCancel);
    EXPECT_NE(panRecognizer->onActionCancel_, nullptr);

    /**
     * @tc.steps: step3. Invoke ReconcileFrom when onActionCancel_ is not null.
     * @tc.expected: The functions have been executed and the unknownPropertyValue has been assigned the correct
     * value.
     */
    TouchEvent touchEvent;
    panRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    panRecognizer->fingers_ = 0;
    panRecognizer->refereeState_ = RefereeState::SUCCEED;
    auto result = panRecognizer->ReconcileFrom(panRecognizerPtr);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: SetOnActionCancelTest004
 * @tc.desc: Test SendCallbackMsg function in the OnSucceedCancel. The onActionCancel function will return
 * GestureEvent info.
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, SetOnActionCancelTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. Call SetOnActionCancel.
     * @tc.expected: panRecognizer's callback onActionCancel is not nullptr.
     */
    panRecognizer->deviceId_ = GESTURE_EVENT_PROPERTY_VALUE;
    double unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    auto onActionCancel = [&unknownPropertyValue](
                                GestureEvent& info) { unknownPropertyValue = info.GetDeviceId(); };
    panRecognizer->SetOnActionCancel(onActionCancel);
    EXPECT_NE(panRecognizer->onActionCancel_, nullptr);

    /**
     * @tc.steps: step4. Invoke OnSucceedCancel when onActionCancel_ is not null.
     * @tc.expected: The functions have been executed and the unknownPropertyValue has been assigned the correct
     * value.
     */
    panRecognizer->OnSucceedCancel();
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
}

/**
 * @tc.name: PanGestureLimitFingerTest001
 * @tc.desc: Test PanGesture CreateRecognizer function
 */
HWTEST_F(PanRecognizerTestNg, PanGestureLimitFingerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanGesture.
     */
    PanDirection panDirection;
    panDirection.type = PanDirection::RIGHT;
    auto panGesture = AceType::MakeRefPtr<PanGesture>(
        SINGLE_FINGER_NUMBER, panDirection, PAN_DISTANCE, IS_LIMIT_FINGER_COUNT);
    ASSERT_NE(panGesture, nullptr);
    EXPECT_EQ(panGesture->fingers_, SINGLE_FINGER_NUMBER);
    EXPECT_EQ(panGesture->isLimitFingerCount_, IS_LIMIT_FINGER_COUNT);

    /**
     * @tc.steps: step2. create onActionStart, onActionUpdate, onActionEnd, onActionCancel for PanRecognizer.
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     * @tc.expect: panRecognizer create successfully with the OnActionCall.
     */
    panGesture->priority_ = GesturePriority::Low;
    panGesture->gestureMask_ = GestureMask::Normal;
    auto panRecognizer = AceType::DynamicCast<PanRecognizer>(panGesture->CreateRecognizer());
    ASSERT_NE(panRecognizer, nullptr);
    EXPECT_EQ(panRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(panRecognizer->GetPriorityMask(), GestureMask::Normal);
    EXPECT_EQ(panRecognizer->isLimitFingerCount_, IS_LIMIT_FINGER_COUNT);

    /**
     * @tc.steps: step2. create onActionStart, onActionUpdate, onActionEnd, onActionCancel for PanRecognizer.
     * @tc.steps: case2: onActionId, onActionEndId, onActionCancelId not existed
     * @tc.expect: panRecognizer create successfully without the OnActionCall.
     */
    panGesture->priority_ = GesturePriority::Low;
    panGesture->gestureMask_ = GestureMask::Normal;
    auto panRecognizerWithoutFunc = AceType::DynamicCast<PanRecognizer>(panGesture->CreateRecognizer());
    ASSERT_NE(panRecognizerWithoutFunc, nullptr);
    EXPECT_EQ(panRecognizerWithoutFunc->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(panRecognizerWithoutFunc->GetPriorityMask(), GestureMask::Normal);
    EXPECT_EQ(panRecognizerWithoutFunc->isLimitFingerCount_, IS_LIMIT_FINGER_COUNT);
}

/**
 * @tc.name: PanGestureLimitFingerTest002
 * @tc.desc: Test PanGesture CreateRecognizer function
 */
HWTEST_F(PanRecognizerTestNg, PanGestureLimitFingerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanGesture.
     */
    PanDirection panDirection;
    panDirection.type = PanDirection::RIGHT;
    auto panGesture = AceType::MakeRefPtr<PanGesture>(
        SINGLE_FINGER_NUMBER, panDirection, PAN_DISTANCE, IS_NOT_LIMIT_FINGER_COUNT);
    ASSERT_NE(panGesture, nullptr);
    EXPECT_EQ(panGesture->fingers_, SINGLE_FINGER_NUMBER);
    EXPECT_EQ(panGesture->isLimitFingerCount_, IS_NOT_LIMIT_FINGER_COUNT);

    /**
     * @tc.steps: step2. create onActionStart, onActionUpdate, onActionEnd, onActionCancel for PanRecognizer.
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     * @tc.expect: panRecognizer create successfully with the OnActionCall.
     */
    panGesture->priority_ = GesturePriority::Low;
    panGesture->gestureMask_ = GestureMask::Normal;
    auto panRecognizer = AceType::DynamicCast<PanRecognizer>(panGesture->CreateRecognizer());
    ASSERT_NE(panRecognizer, nullptr);
    EXPECT_EQ(panRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(panRecognizer->GetPriorityMask(), GestureMask::Normal);
    EXPECT_EQ(panRecognizer->isLimitFingerCount_, IS_NOT_LIMIT_FINGER_COUNT);

    /**
     * @tc.steps: step2. create onActionStart, onActionUpdate, onActionEnd, onActionCancel for PanRecognizer.
     * @tc.steps: case2: onActionId, onActionEndId, onActionCancelId existed
     * @tc.expect: panRecognizer create successfully with the OnActionCall.
     */
    panGesture->priority_ = GesturePriority::Low;
    panGesture->gestureMask_ = GestureMask::Normal;
    auto onActionStart = [](GestureEvent& info) { return true; };
    auto onActionUpdate = [](GestureEvent& info) { return true; };
    auto onActionEnd = [](GestureEvent& info) { return true; };
    auto onActionCancel = [](GestureEvent& info) { return true; };
    panGesture->SetOnActionStartId(onActionStart);
    panGesture->SetOnActionUpdateId(onActionUpdate);
    panGesture->SetOnActionEndId(onActionEnd);
    panGesture->SetOnActionCancelId(onActionCancel);
    EXPECT_TRUE(panGesture->onActionStartId_);
    EXPECT_TRUE(panGesture->onActionUpdateId_);
    EXPECT_TRUE(panGesture->onActionEndId_);
    EXPECT_TRUE(panGesture->onActionCancelId_);

    auto panRecognizerWithFunc = AceType::DynamicCast<PanRecognizer>(panGesture->CreateRecognizer());
    ASSERT_NE(panRecognizerWithFunc, nullptr);
    EXPECT_EQ(panRecognizerWithFunc->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(panRecognizerWithFunc->GetPriorityMask(), GestureMask::Normal);
    EXPECT_EQ(panRecognizerWithFunc->isLimitFingerCount_, IS_NOT_LIMIT_FINGER_COUNT);
}

/**
 * @tc.name: IsPanGestureAcceptInAllDirection001
 * @tc.desc: Test IsPanGestureAcceptInAllDirection function
 */
HWTEST_F(PanRecognizerTestNg, IsPanGestureAcceptInAllDirection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. set judgeDistance is 0.0 and call IsPanGestureAcceptInAllDirection function.
     * @tc.expect: gestureAcceptResult is equal to GestureAcceptResult::ACCEPT.
     */
    double judgeDistance = 0.0;
    auto gestureAcceptResult = panRecognizer.IsPanGestureAcceptInAllDirection(judgeDistance);
    EXPECT_EQ(gestureAcceptResult, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step3. set judgeDistance is 1.0 and call IsPanGestureAcceptInAllDirection function.
     * @tc.expect: gestureAcceptResult is equal to GestureAcceptResult::DETECTING.
     */
    judgeDistance = 1.0;
    gestureAcceptResult = panRecognizer.IsPanGestureAcceptInAllDirection(judgeDistance);
    EXPECT_EQ(gestureAcceptResult, PanRecognizer::GestureAcceptResult::DETECTING);
}

/**
 * @tc.name: PanRecognizerTest001
 * @tc.desc: Test OnAccepted function
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, OnAcceptedTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.expected: step2. result equals.
     */
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanoseconds(currentTime);
    TimeStamp time(nanoseconds);
    panRecognizer.firstInputTime_ = time;
    panRecognizer.isTouchEventFinished_ = true;
    panRecognizer.SetEnabled(false);
    panRecognizer.OnAccepted();
    EXPECT_EQ(panRecognizer.refereeState_, RefereeState::SUCCEED);
    EXPECT_FALSE(panRecognizer.isStartTriggered_);
}

/**
 * @tc.name: HandleTouchUpEvent001
 * @tc.desc: Test HandleTouchUpEvent function
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, HandleTouchUpEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. set axisEvent.isRotationEvent is true and call HandleTouchUp function.
     * @tc.expected: result equals.
     */
    AxisEvent axisEvent;
    axisEvent.isRotationEvent = true;
    panRecognizer.HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(panRecognizer.globalPoint_.GetX(), axisEvent.x);
    EXPECT_EQ(panRecognizer.globalPoint_.GetY(), axisEvent.y);
}
/**
 * @tc.name: PanRecognizerTypeTest001
 * @tc.desc: Test PanRecognizerType
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTypeTest001, TestSize.Level1)
{
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    panRecognizer.AttachFrameNode(frameNode);
    panRecognizer.SetRecognizerType(GestureTypeName::PAN_GESTURE);
    GestureEvent info;
    panRecognizer.HandleReports(info, GestureCallbackType::END);
    EXPECT_EQ(panRecognizer.GetRecognizerType(), GestureTypeName::PAN_GESTURE);
}

/**
 * @tc.name: OnResetStatus001
 * @tc.desc: Test OnResetStatus function
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, OnResetStatus001, TestSize.Level1)
{
    /**
      * @tc.steps: step1. create PanRecognizer.
      */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);
  
    /**
      * @tc.steps: step2. call OnResetStatus function.
      * @tc.expected: result equals.
      */
    panRecognizer.OnResetStatus();
    EXPECT_EQ(panRecognizer.touchPoints_.size(), 0);
    EXPECT_EQ(panRecognizer.isStartTriggered_, false);
}

/**
 * @tc.name: HandlePanExtAccept001
 * @tc.desc: Test HandlePanExtAccept function
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, HandlePanExtAccept001, TestSize.Level1)
{
    /**
      * @tc.steps: step1. create PanRecognizer.
      */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
      * @tc.steps: step2. call HandlePanExtAccept function.
      * @tc.describe: set onActionExtUpdate_ to null.
      * @tc.expected: result equals.
      */
    uint32_t tag = 0;
    panRecognizer.onActionExtUpdate_ = nullptr;
    panRecognizer.HandlePanExtAccept();

    /**
      * @tc.steps: step3. call HandlePanExtAccept function.
      * @tc.describe: set onActionExtUpdate_ to custom callback.
      * @tc.expected: result equals.
      */
    panRecognizer.onActionExtUpdate_ = std::make_unique<GestureEventFunc>([&tag](GestureEvent& info) {
        tag = 1;
    });
    panRecognizer.HandlePanExtAccept();
    EXPECT_NE(tag, 0);
}

/**
 * @tc.name: PanRecognizerTest030
 * @tc.desc: Test PanRecognizer function: GetGestureEventInfo
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call ChangeDirection function
     * @tc.steps: case1: type not same
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    axisEvent.postEventNodeId = 100;
    TouchEvent touchEvent;
    touchEvent.postEventNodeId = 10;
    panRecognizer->touchPoints_[0] = touchEvent;
    panRecognizer->lastTouchEvent_ = touchEvent;
    panRecognizer->lastAxisEvent_ = axisEvent;

    panRecognizer->inputEventType_ = InputEventType::AXIS;
    auto gestureEvent = panRecognizer->GetGestureEventInfo();
    EXPECT_EQ(gestureEvent.GetPostEventNodeId(), 100);
    panRecognizer->inputEventType_ = InputEventType::TOUCH_SCREEN;
    gestureEvent = panRecognizer->GetGestureEventInfo();
    EXPECT_EQ(gestureEvent.GetPostEventNodeId(), 10);
}

/**
 * @tc.name: GetGestureInfoString001
 * @tc.desc: Test PanRecognizer function: GetGestureInfoString
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, GetGestureInfoString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    panRecognizer->isFlushTouchEventsEnd_ = true;
    panRecognizer->isForDrag_ = true;
    panRecognizer->isAllowMouse_ = false;
    panRecognizer->isStartTriggered_ = true;
    panRecognizer->lastAction_ = 1;
    panRecognizer->angle_ = 60.0;

    std::string result = panRecognizer->GetGestureInfoString();
    EXPECT_THAT(result, HasSubstr("FTE:1"));
    EXPECT_THAT(result, HasSubstr("FD:1"));
    EXPECT_THAT(result, HasSubstr("AM:0"));
    EXPECT_THAT(result, HasSubstr("ST:1"));
    EXPECT_THAT(result, HasSubstr("LA:1"));
    EXPECT_THAT(result, HasSubstr("AG:60"));
}

/**
 * @tc.name: PanRecognizerJudgeVerticalDistanceTest001
 * @tc.desc: Test JudgeVerticalDistance when direction is VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerJudgeVerticalDistanceTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer and set direction to VERTICAL
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Call JudgeVerticalDistance when direction is VERTICAL
     * @tc.expected: step2. Should return true for VERTICAL direction
     */
    panRecognizer.deviceType_ = SourceType::TOUCH;
    bool result = panRecognizer.JudgeVerticalDistance();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: PanRecognizerJudgeVerticalDistanceTest002
 * @tc.desc: Test JudgeVerticalDistance with DOWN direction when offset is negative
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerJudgeVerticalDistanceTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with DOWN direction
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::DOWN;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set touch point distance with negative Y offset (moving up)
     * @tc.expected: step2. Should return false as DOWN direction rejects negative offset
     */
    panRecognizer.deviceType_ = SourceType::TOUCH;
    TouchEvent touchEvent;
    touchEvent.id = FINGER_NUMBER;
    panRecognizer.touchPointsDistance_[touchEvent.id] = Offset(0.0, -5.0);
    bool result = panRecognizer.JudgeVerticalDistance();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PanRecognizerJudgeVerticalDistanceTest003
 * @tc.desc: Test JudgeVerticalDistance with UP direction when offset is positive
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerJudgeVerticalDistanceTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with UP direction
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::UP;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set touch point distance with positive Y offset (moving down)
     * @tc.expected: step2. Should return false as UP direction rejects positive offset
     */
    panRecognizer.deviceType_ = SourceType::TOUCH;
    TouchEvent touchEvent;
    touchEvent.id = FINGER_NUMBER;
    panRecognizer.touchPointsDistance_[touchEvent.id] = Offset(0.0, 5.0);
    bool result = panRecognizer.JudgeVerticalDistance();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PanRecognizerCalculateTruthFingersTest001
 * @tc.desc: Test CalculateTruthFingers with isDirectionUp as true
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerCalculateTruthFingersTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set up touch points with positive Y offset (moving down)
     * @tc.expected: step2. Should return false when isDirectionUp is true but movement is down
     */
    panRecognizer.deviceType_ = SourceType::TOUCH;
    panRecognizer.distance_ = 10.0;
    panRecognizer.fingers_ = FINGER_NUMBER;

    TouchEvent touchEvent;
    touchEvent.id = FINGER_NUMBER;
    panRecognizer.touchPointsDistance_[touchEvent.id] = Offset(0.0, 5.0);

    bool result = panRecognizer.CalculateTruthFingers(true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PanRecognizerCalculateTruthFingersTest002
 * @tc.desc: Test CalculateTruthFingers with isDirectionUp as true and sufficient distance
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerCalculateTruthFingersTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set up touch points with sufficient positive Y offset
     * @tc.expected: step2. Should return true when distance threshold is met
     */
    panRecognizer.deviceType_ = SourceType::TOUCH;
    panRecognizer.distance_ = 10.0;
    panRecognizer.fingers_ = FINGER_NUMBER;

    TouchEvent touchEvent;
    touchEvent.id = FINGER_NUMBER;
    panRecognizer.touchPointsDistance_[touchEvent.id] = Offset(0.0, 15.0);

    bool result = panRecognizer.CalculateTruthFingers(true);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: PanRecognizerCalculateTruthFingersTest003
 * @tc.desc: Test CalculateTruthFingers with isDirectionUp as false
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerCalculateTruthFingersTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set up touch points with negative Y offset (moving up)
     * @tc.expected: step2. Should return true when isDirectionUp is false and movement is up
     */
    panRecognizer.deviceType_ = SourceType::TOUCH;
    panRecognizer.distance_ = 10.0;
    panRecognizer.fingers_ = FINGER_NUMBER;

    TouchEvent touchEvent;
    touchEvent.id = FINGER_NUMBER;
    panRecognizer.touchPointsDistance_[touchEvent.id] = Offset(0.0, -15.0);

    bool result = panRecognizer.CalculateTruthFingers(false);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: PanRecognizerCalculateTruthFingersTest004
 * @tc.desc: Test CalculateTruthFingers with MOUSE device type using mouseDistance
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerCalculateTruthFingersTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with different mouse and touch distances
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set up for MOUSE device type with sufficient mouse distance
     * @tc.expected: step2. Should use mouseDistance_ for MOUSE device type
     */
    panRecognizer.deviceType_ = SourceType::MOUSE;
    panRecognizer.distance_ = 10.0;
    panRecognizer.mouseDistance_ = 5.0;
    panRecognizer.fingers_ = FINGER_NUMBER;

    TouchEvent touchEvent;
    touchEvent.id = FINGER_NUMBER;
    panRecognizer.touchPointsDistance_[touchEvent.id] = Offset(0.0, 5.0);

    bool result = panRecognizer.CalculateTruthFingers(true);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: PanRecognizerGetAxisDirectionTest001
 * @tc.desc: Test GetAxisDirection returns FREE for ALL direction
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerGetAxisDirectionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with ALL direction
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Call GetAxisDirection
     * @tc.expected: step2. Should return Axis::FREE for ALL direction
     */
    Axis result = panRecognizer.GetAxisDirection();
    EXPECT_EQ(result, Axis::FREE);
}

/**
 * @tc.name: PanRecognizerGetAxisDirectionTest002
 * @tc.desc: Test GetAxisDirection returns HORIZONTAL for horizontal-only direction
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerGetAxisDirectionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with HORIZONTAL direction
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::HORIZONTAL;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Call GetAxisDirection
     * @tc.expected: step2. Should return Axis::HORIZONTAL
     */
    Axis result = panRecognizer.GetAxisDirection();
    EXPECT_EQ(result, Axis::HORIZONTAL);
}

/**
 * @tc.name: PanRecognizerGetAxisDirectionTest003
 * @tc.desc: Test GetAxisDirection returns VERTICAL for vertical-only direction
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerGetAxisDirectionTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with VERTICAL direction
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Call GetAxisDirection
     * @tc.expected: step2. Should return Axis::VERTICAL
     */
    Axis result = panRecognizer.GetAxisDirection();
    EXPECT_EQ(result, Axis::VERTICAL);
}

/**
 * @tc.name: PanRecognizerGetAxisDirectionTest004
 * @tc.desc: Test GetAxisDirection returns FREE for combined horizontal and vertical direction
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerGetAxisDirectionTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with combined HORIZONTAL and VERTICAL direction
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::HORIZONTAL | PanDirection::VERTICAL;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Call GetAxisDirection
     * @tc.expected: step2. Should return Axis::FREE for combined directions
     */
    Axis result = panRecognizer.GetAxisDirection();
    EXPECT_EQ(result, Axis::FREE);
}

/**
 * @tc.name: PanRecognizerGetAxisDirectionTest005
 * @tc.desc: Test GetAxisDirection returns NONE for NONE direction
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerGetAxisDirectionTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with NONE direction
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::NONE;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Call GetAxisDirection
     * @tc.expected: step2. Should return Axis::NONE
     */
    Axis result = panRecognizer.GetAxisDirection();
    EXPECT_EQ(result, Axis::NONE);
}

/**
 * @tc.name: PanRecognizerIsPanGestureAcceptInAllDirectionTest001
 * @tc.desc: Test IsPanGestureAcceptInAllDirection returns DETECTING when distance insufficient
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerIsPanGestureAcceptInAllDirectionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set average distance below threshold
     * @tc.expected: step2. Should return DETECTING
     */
    panRecognizer.averageDistance_ = Offset(5.0, 5.0);
    double judgeDistance = 10.0;

    auto result = panRecognizer.IsPanGestureAcceptInAllDirection(judgeDistance);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::DETECTING);
}

/**
 * @tc.name: PanRecognizerIsPanGestureAcceptInAllDirectionTest002
 * @tc.desc: Test IsPanGestureAcceptInAllDirection returns ACCEPT when distance sufficient
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerIsPanGestureAcceptInAllDirectionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set average distance above threshold
     * @tc.expected: step2. Should return ACCEPT
     */
    panRecognizer.averageDistance_ = Offset(15.0, 15.0);
    double judgeDistance = 10.0;

    auto result = panRecognizer.IsPanGestureAcceptInAllDirection(judgeDistance);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);
}

/**
 * @tc.name: PanRecognizerIsPanGestureAcceptInHorizontalDirectionTest001
 * @tc.desc: Test IsPanGestureAcceptInHorizontalDirection returns DETECTING for insufficient distance
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerIsPanGestureAcceptInHorizontalDirectionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with HORIZONTAL direction
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::HORIZONTAL;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set X offset below threshold
     * @tc.expected: step2. Should return DETECTING
     */
    panRecognizer.averageDistance_ = Offset(5.0, 0.0);
    double judgeDistance = 10.0;

    auto result = panRecognizer.IsPanGestureAcceptInHorizontalDirection(judgeDistance);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::DETECTING);
}

/**
 * @tc.name: PanRecognizerIsPanGestureAcceptInHorizontalDirectionTest002
 * @tc.desc: Test IsPanGestureAcceptInHorizontalDirection rejects LEFT direction with positive offset
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerIsPanGestureAcceptInHorizontalDirectionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with LEFT direction only
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::LEFT;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set positive X offset (moving right) with sufficient distance
     * @tc.expected: step2. Should return REJECT for LEFT direction with rightward movement
     */
    panRecognizer.averageDistance_ = Offset(15.0, 0.0);
    double judgeDistance = 10.0;

    auto result = panRecognizer.IsPanGestureAcceptInHorizontalDirection(judgeDistance);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::REJECT);
}

/**
 * @tc.name: PanRecognizerIsPanGestureAcceptInHorizontalDirectionTest003
 * @tc.desc: Test IsPanGestureAcceptInHorizontalDirection accepts LEFT direction with negative offset
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerIsPanGestureAcceptInHorizontalDirectionTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with LEFT direction
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::LEFT;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set negative X offset (moving left) with sufficient distance
     * @tc.expected: step2. Should return ACCEPT
     */
    panRecognizer.averageDistance_ = Offset(-15.0, 0.0);
    double judgeDistance = 10.0;

    auto result = panRecognizer.IsPanGestureAcceptInHorizontalDirection(judgeDistance);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);
}

/**
 * @tc.name: PanRecognizerIsPanGestureAcceptInVerticalDirectionTest001
 * @tc.desc: Test IsPanGestureAcceptInVerticalDirection returns DETECTING for insufficient distance
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerIsPanGestureAcceptInVerticalDirectionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with VERTICAL direction
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set Y offset below threshold
     * @tc.expected: step2. Should return DETECTING
     */
    panRecognizer.averageDistance_ = Offset(0.0, 5.0);
    double judgeDistance = 10.0;

    auto result = panRecognizer.IsPanGestureAcceptInVerticalDirection(judgeDistance);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::DETECTING);
}

/**
 * @tc.name: PanRecognizerIsPanGestureAcceptInVerticalDirectionTest002
 * @tc.desc: Test IsPanGestureAcceptInVerticalDirection rejects UP direction with positive offset
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerIsPanGestureAcceptInVerticalDirectionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with UP direction only
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::UP;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set positive Y offset (moving down) with sufficient distance for touch
     * @tc.expected: step2. Should return REJECT for UP direction with downward movement
     */
    panRecognizer.inputEventType_ = InputEventType::TOUCH_SCREEN;
    panRecognizer.averageDistance_ = Offset(0.0, 15.0);
    double judgeDistance = 10.0;

    auto result = panRecognizer.IsPanGestureAcceptInVerticalDirection(judgeDistance);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::REJECT);
}

/**
 * @tc.name: PanRecognizerIsPanGestureAcceptInVerticalDirectionTest003
 * @tc.desc: Test IsPanGestureAcceptInVerticalDirection accepts UP direction with negative offset
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerIsPanGestureAcceptInVerticalDirectionTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with UP direction
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::UP;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set negative Y offset (moving up) with sufficient distance for touch
     * @tc.expected: step2. Should return ACCEPT
     */
    panRecognizer.inputEventType_ = InputEventType::TOUCH_SCREEN;
    panRecognizer.averageDistance_ = Offset(0.0, -15.0);
    double judgeDistance = 10.0;

    auto result = panRecognizer.IsPanGestureAcceptInVerticalDirection(judgeDistance);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);
}

/**
 * @tc.name: PanRecognizerIsPanGestureAcceptInVerticalDirectionTest004
 * @tc.desc: Test IsPanGestureAcceptInVerticalDirection with AXIS input type
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerIsPanGestureAcceptInVerticalDirectionTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with DOWN direction
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::DOWN;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set negative Y offset (moving up) with AXIS input type
     * @tc.expected: step2. Should return REJECT for DOWN direction with upward movement
     */
    panRecognizer.inputEventType_ = InputEventType::AXIS;
    panRecognizer.averageDistance_ = Offset(0.0, -15.0);
    double judgeDistance = 10.0;

    auto result = panRecognizer.IsPanGestureAcceptInVerticalDirection(judgeDistance);
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::REJECT);
}

/**
 * @tc.name: PanRecognizerGetMainAxisDeltaTest001
 * @tc.desc: Test GetMainAxisDelta returns distance for ALL direction
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerGetMainAxisDeltaTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with ALL direction
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set delta with both X and Y components
     * @tc.expected: step2. Should return distance magnitude for ALL direction
     */
    panRecognizer.delta_ = Offset(3.0, 4.0);
    double result = panRecognizer.GetMainAxisDelta();
    EXPECT_DOUBLE_EQ(result, 5.0);
}

/**
 * @tc.name: PanRecognizerGetMainAxisDeltaTest002
 * @tc.desc: Test GetMainAxisDelta returns X for HORIZONTAL direction
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerGetMainAxisDeltaTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with HORIZONTAL direction
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::HORIZONTAL;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set delta with both X and Y components
     * @tc.expected: step2. Should return X component for HORIZONTAL direction
     */
    panRecognizer.delta_ = Offset(10.0, 5.0);
    double result = panRecognizer.GetMainAxisDelta();
    EXPECT_DOUBLE_EQ(result, 10.0);
}

/**
 * @tc.name: PanRecognizerGetMainAxisDeltaTest003
 * @tc.desc: Test GetMainAxisDelta returns Y for VERTICAL direction
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerGetMainAxisDeltaTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with VERTICAL direction
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set delta with both X and Y components
     * @tc.expected: step2. Should return Y component for VERTICAL direction
     */
    panRecognizer.delta_ = Offset(5.0, 10.0);
    double result = panRecognizer.GetMainAxisDelta();
    EXPECT_DOUBLE_EQ(result, 10.0);
}

/**
 * @tc.name: PanRecognizerGetMainAxisDeltaTest004
 * @tc.desc: Test GetMainAxisDelta returns zero for unknown direction
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerGetMainAxisDeltaTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer with NONE direction
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::NONE;
    panGestureOption->SetDirection(panDirection);
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set delta with both X and Y components
     * @tc.expected: step2. Should return 0.0 for NONE direction
     */
    panRecognizer.delta_ = Offset(5.0, 10.0);
    double result = panRecognizer.GetMainAxisDelta();
    EXPECT_DOUBLE_EQ(result, 0.0);
}

/**
 * @tc.name: PanRecognizerChangeFingersTest001
 * @tc.desc: Test ChangeFingers updates newFingers when different
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerChangeFingersTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);
    int32_t originalFingers = panRecognizer.fingers_;

    /**
     * @tc.steps: step2. Call ChangeFingers with different value
     * @tc.expected: step2. newFingers_ should be updated
     */
    panRecognizer.ChangeFingers(originalFingers + 1);
    EXPECT_EQ(panRecognizer.newFingers_, originalFingers + 1);
}

/**
 * @tc.name: PanRecognizerChangeFingersTest002
 * @tc.desc: Test ChangeFingers does not update newFingers when same
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerChangeFingersTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);
    int32_t originalFingers = panRecognizer.fingers_;
    panRecognizer.newFingers_ = originalFingers;

    /**
     * @tc.steps: step2. Call ChangeFingers with same value
     * @tc.expected: step2. newFingers_ should remain unchanged
     */
    panRecognizer.ChangeFingers(originalFingers);
    EXPECT_EQ(panRecognizer.newFingers_, originalFingers);
}

/**
 * @tc.name: PanRecognizerChangeDirectionTest001
 * @tc.desc: Test ChangeDirection updates direction and newDirection when different
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerChangeDirectionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Call ChangeDirection with different direction type
     * @tc.expected: step2. Both direction_ and newDirection_ should be updated
     */
    PanDirection newDirection;
    newDirection.type = PanDirection::HORIZONTAL;
    panRecognizer.ChangeDirection(newDirection);
    EXPECT_EQ(panRecognizer.direction_.type, PanDirection::HORIZONTAL);
    EXPECT_EQ(panRecognizer.newDirection_.type, PanDirection::HORIZONTAL);
}

/**
 * @tc.name: PanRecognizerUpdateDistanceTest001
 * @tc.desc: Test UpdateDistance updates distance when in READY state
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerUpdateDistanceTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer in READY state
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);
    panRecognizer.refereeState_ = RefereeState::READY;
    double originalDistance = 10.0;
    panRecognizer.distance_ = originalDistance;
    panRecognizer.newDistance_ = originalDistance;

    /**
     * @tc.steps: step2. Call UpdateDistance with different value
     * @tc.expected: step2. Both distance_ and newDistance_ should be updated
     */
    double newDistance = 20.0;
    panRecognizer.ChangeDistance(newDistance);
    EXPECT_DOUBLE_EQ(panRecognizer.distance_, newDistance);
    EXPECT_DOUBLE_EQ(panRecognizer.newDistance_, newDistance);
}

/**
 * @tc.name: PanRecognizerUpdateDistanceTest002
 * @tc.desc: Test UpdateDistance updates distance when in DETECTING state
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerUpdateDistanceTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer in DETECTING state
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);
    panRecognizer.refereeState_ = RefereeState::DETECTING;
    double originalDistance = 10.0;
    panRecognizer.distance_ = originalDistance;
    panRecognizer.newDistance_ = originalDistance;

    /**
     * @tc.steps: step2. Call UpdateDistance with different value
     * @tc.expected: step2. Both distance_ and newDistance_ should be updated
     */
    double newDistance = 20.0;
    panRecognizer.ChangeDistance(newDistance);
    EXPECT_DOUBLE_EQ(panRecognizer.distance_, newDistance);
    EXPECT_DOUBLE_EQ(panRecognizer.newDistance_, newDistance);
}

/**
 * @tc.name: PanRecognizerUpdateDistanceTest003
 * @tc.desc: Test UpdateDistance does not update distance when in SUCCEED state
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerUpdateDistanceTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer in SUCCEED state
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);
    panRecognizer.refereeState_ = RefereeState::SUCCEED;
    double originalDistance = 10.0;
    panRecognizer.distance_ = originalDistance;
    panRecognizer.newDistance_ = originalDistance;

    /**
     * @tc.steps: step2. Call UpdateDistance with different value
     * @tc.expected: step2. distance_ should remain unchanged, newDistance_ should be updated
     */
    double newDistance = 20.0;
    panRecognizer.ChangeDistance(newDistance);
    EXPECT_DOUBLE_EQ(panRecognizer.distance_, originalDistance);
    EXPECT_DOUBLE_EQ(panRecognizer.newDistance_, newDistance);
}

/**
 * @tc.name: PanRecognizerUpdateDistanceTest004
 * @tc.desc: Test UpdateDistance updates mouseDistance
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerUpdateDistanceTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer in READY state
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);
    panRecognizer.refereeState_ = RefereeState::READY;
    double originalDistance = 10.0;
    panRecognizer.distance_ = originalDistance;
    panRecognizer.newDistance_ = originalDistance;
    panRecognizer.mouseDistance_ = originalDistance;

    /**
     * @tc.steps: step2. Call UpdateDistance with different value
     * @tc.expected: step2. mouseDistance_ should also be updated
     */
    double newDistance = 20.0;
    panRecognizer.ChangeDistance(newDistance);
    EXPECT_DOUBLE_EQ(panRecognizer.mouseDistance_, newDistance);
}

/**
 * @tc.name: PanRecognizerForceCleanRecognizerTest001
 * @tc.desc: Test ForceCleanRecognizer resets all state correctly
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerForceCleanRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer and set various state
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set up state that should be cleared
     * @tc.expected: step2. State should be set before cleanup
     */
    panRecognizer.averageDistance_ = Offset(10.0, 10.0);
    TouchEvent touchEvent;
    touchEvent.id = FINGER_NUMBER;
    panRecognizer.touchPointsDistance_[touchEvent.id] = Offset(5.0, 5.0);
    panRecognizer.isStartTriggered_ = true;

    /**
     * @tc.steps: step3. Call ForceCleanRecognizer
     * @tc.expected: step3. All state should be reset
     */
    panRecognizer.ForceCleanRecognizer();
    EXPECT_DOUBLE_EQ(panRecognizer.averageDistance_.GetX(), 0.0);
    EXPECT_DOUBLE_EQ(panRecognizer.averageDistance_.GetY(), 0.0);
    EXPECT_TRUE(panRecognizer.touchPointsDistance_.empty());
    EXPECT_FALSE(panRecognizer.isStartTriggered_);
}

/**
 * @tc.name: PanRecognizerDumpTest001
 * @tc.desc: Test Dump returns valid GestureSnapshot
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerDumpTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection;
    panDirection.type = PanDirection::HORIZONTAL;
    panGestureOption->SetDirection(panDirection);
    panGestureOption->SetDistance(15.0);
    panGestureOption->fingers_ = FINGER_NUMBER;
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Call Dump
     * @tc.expected: step2. Should return valid GestureSnapshot with customInfo
     */
    RefPtr<GestureSnapshot> snapshot = panRecognizer.Dump();
    ASSERT_NE(snapshot, nullptr);
    EXPECT_FALSE(snapshot->customInfo.empty());
}

/**
 * @tc.name: PanRecognizerOnResetStatusTest001
 * @tc.desc: Test OnResetStatus clears all state correctly
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerOnResetStatusTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer and set various state
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set up state that should be cleared
     */
    panRecognizer.averageDistance_ = Offset(10.0, 10.0);
    TouchEvent touchEvent;
    touchEvent.id = FINGER_NUMBER;
    panRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    panRecognizer.touchPointsDistance_[touchEvent.id] = Offset(5.0, 5.0);
    panRecognizer.isStartTriggered_ = true;

    /**
     * @tc.steps: step3. Call OnResetStatus
     * @tc.expected: step3. All state should be reset
     */
    panRecognizer.OnResetStatus();
    EXPECT_TRUE(panRecognizer.touchPoints_.empty());
    EXPECT_DOUBLE_EQ(panRecognizer.averageDistance_.GetX(), 0.0);
    EXPECT_DOUBLE_EQ(panRecognizer.averageDistance_.GetY(), 0.0);
    EXPECT_TRUE(panRecognizer.touchPointsDistance_.empty());
    EXPECT_FALSE(panRecognizer.isStartTriggered_);
}

/**
 * @tc.name: PanRecognizerOnSucceedCancelTest001
 * @tc.desc: Test OnSucceedCancel sends callback when set
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerOnSucceedCancelTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Set up onActionCancel callback
     * @tc.expected: step2. Callback should be invoked
     */
    bool callbackInvoked = false;
    auto onActionCancel = [&callbackInvoked](GestureEvent& info) {
        callbackInvoked = true;
    };
    panRecognizer.SetOnActionCancel(onActionCancel);

    /**
     * @tc.steps: step3. Call OnSucceedCancel
     * @tc.expected: step3. Callback should be invoked
     */
    panRecognizer.OnSucceedCancel();
    EXPECT_TRUE(callbackInvoked);
}

/**
 * @tc.name: PanRecognizerReconcileFromTest001
 * @tc.desc: Test ReconcileFrom returns false when recognizer is null
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerReconcileFromTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PanRecognizer
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. Call ReconcileFrom with null recognizer
     * @tc.expected: step2. Should return false and reset state
     */
    RefPtr<NGGestureRecognizer> nullRecognizer = nullptr;
    bool result = panRecognizer.ReconcileFrom(nullRecognizer);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PanRecognizerReconcileFromTest002
 * @tc.desc: Test ReconcileFrom returns false when fingers differ
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerReconcileFromTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create two PanRecognizers with different fingers
     */
    RefPtr<PanGestureOption> panGestureOption1 = AceType::MakeRefPtr<PanGestureOption>();
    panGestureOption1->fingers_ = FINGER_NUMBER;
    PanRecognizer panRecognizer1 = PanRecognizer(panGestureOption1);

    RefPtr<PanGestureOption> panGestureOption2 = AceType::MakeRefPtr<PanGestureOption>();
    panGestureOption2->fingers_ = FINGER_NUMBER + 1;
    RefPtr<PanRecognizer> panRecognizer2 = AceType::MakeRefPtr<PanRecognizer>(panGestureOption2);

    /**
     * @tc.steps: step2. Call ReconcileFrom with different fingers
     * @tc.expected: step2. Should return false and reset state
     */
    bool result = panRecognizer1.ReconcileFrom(panRecognizer2);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PanRecognizerReconcileFromTest003
 * @tc.desc: Test ReconcileFrom returns true and updates properties when compatible
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerReconcileFromTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create two compatible PanRecognizers
     */
    RefPtr<PanGestureOption> panGestureOption1 = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection1;
    panDirection1.type = PanDirection::HORIZONTAL;
    panGestureOption1->SetDirection(panDirection1);
    panGestureOption1->SetDistance(10.0);
    panGestureOption1->fingers_ = FINGER_NUMBER;
    PanRecognizer panRecognizer1 = PanRecognizer(panGestureOption1);

    RefPtr<PanGestureOption> panGestureOption2 = AceType::MakeRefPtr<PanGestureOption>();
    PanDirection panDirection2;
    panDirection2.type = PanDirection::VERTICAL;
    panGestureOption2->SetDirection(panDirection2);
    panGestureOption2->SetDistance(20.0);
    panGestureOption2->fingers_ = FINGER_NUMBER;
    RefPtr<PanRecognizer> panRecognizer2 = AceType::MakeRefPtr<PanRecognizer>(panGestureOption2);

    /**
     * @tc.steps: step2. Call ReconcileFrom with compatible recognizer
     * @tc.expected: step2. Should return true and update properties
     */
    bool result = panRecognizer1.ReconcileFrom(panRecognizer2);
    EXPECT_TRUE(result);
    EXPECT_EQ(panRecognizer1.direction_.type, PanDirection::VERTICAL);
    EXPECT_DOUBLE_EQ(panRecognizer1.distance_, 20.0);
}
} // namespace OHOS::Ace::NG