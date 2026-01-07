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
 * @tc.desc: Test PanRecognizer function: GetGestureEventInfo
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
 * @tc.name: PanRecognizerTest021
 * @tc.desc: Test PanRecognizer function: IsPanGestureAccept
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerTestNg, PanRecognizerTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. case7: GetX == GetY, GetY < distance_, angle_ = 45.0, PanDirection::VERTICAL.
     * @tc.expected: step2. return ACCEPT.
     */
    PanRecognizer::GestureAcceptResult result;
    panRecognizer->direction_.type = PanDirection::VERTICAL;
    panRecognizer->averageDistance_ = Offset(1, 1);
    panRecognizer->distanceMap_[SourceTool::UNKNOWN] = Dimension(1, DimensionUnit::PX);
    result = panRecognizer->IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case7: GetX == GetY, GetY < distance_, angle_ = 60.0, PanDirection::VERTICAL.
     * @tc.expected: step2. return DETECTING.
     */
    panRecognizer->angle_ = 60.0;
    result = panRecognizer->IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::DETECTING);

    /**
     * @tc.steps: step2. case7: GetX == GetY, GetY < distance_, angle_ = 30.0, PanDirection::VERTICAL.
     * @tc.expected: step2. return ACCEPT.
     */
    panRecognizer->angle_ = 30.0;
    result = panRecognizer->IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);
}
} // namespace OHOS::Ace::NG