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
#include "test/unittest/core/gestures/gestures_common_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class RotationRecognizerTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void RotationRecognizerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void RotationRecognizerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: RotationRecognizerTest001
 * @tc.desc: Test RotationRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.OnAccepted();
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.expected: step3. result equals.
     */
    rotationRecognizer.OnRejected();
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: RotationRecognizerTest002
 * @tc.desc: Test RotationRecognizer function: TouchDown TouchUp TouchMove
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    auto rotationRecognizer = AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: touchPoints.size == fingers
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    rotationRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer->fingers_ = FINGER_NUMBER;
    rotationRecognizer->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer->HandleTouchDownEvent(touchEvent);
    rotationRecognizer->HandleTouchUpEvent(touchEvent);
    rotationRecognizer->HandleTouchMoveEvent(touchEvent);
    rotationRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->refereeState_, RefereeState::FAIL);
    EXPECT_EQ(rotationRecognizer->resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer->fingers_ = FINGER_NUMBER;
    rotationRecognizer->refereeState_ = RefereeState::FAIL;
    rotationRecognizer->HandleTouchDownEvent(touchEvent);
    rotationRecognizer->HandleTouchUpEvent(touchEvent);
    rotationRecognizer->HandleTouchMoveEvent(touchEvent);
    rotationRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->refereeState_, RefereeState::FAIL);
    EXPECT_EQ(rotationRecognizer->resultAngle_, 0);
}

/**
 * @tc.name: RotationRecognizerHandleTouchDownEventTest001
 * @tc.desc: Test RotationRecognizer function: TouchDown TouchUp TouchMove
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerHandleTouchDownEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    auto rotationRecognizer = AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: touchPoints.size == fingers
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    rotationRecognizer->fingers_ = FINGER_NUMBER_OVER_MAX;
    rotationRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer->fingers_ = FINGER_NUMBER_OVER_MAX;
    rotationRecognizer->HandleTouchDownEvent(touchEvent);
    rotationRecognizer->HandleTouchUpEvent(touchEvent);
    rotationRecognizer->HandleTouchMoveEvent(touchEvent);
    rotationRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->refereeState_, RefereeState::FAIL);
    EXPECT_EQ(rotationRecognizer->resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer->refereeState_ = RefereeState::FAIL;
    rotationRecognizer->fingers_ = FINGER_NUMBER_OVER_MAX;
    rotationRecognizer->HandleTouchDownEvent(touchEvent);
    rotationRecognizer->HandleTouchUpEvent(touchEvent);
    rotationRecognizer->HandleTouchMoveEvent(touchEvent);
    rotationRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->refereeState_, RefereeState::FAIL);
    EXPECT_EQ(rotationRecognizer->resultAngle_, 0);
}

/**
 * @tc.name: RotationRecognizerHandleTouchDownEventTest002
 * @tc.desc: Test RotationRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerHandleTouchDownEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: touchPoints.size == fingers
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    rotationRecognizer.fingers_ = 0;
    rotationRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer.fingers_ = 0;
    rotationRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.refereeState_ = RefereeState::FAIL;
    rotationRecognizer.fingers_ = 0;
    rotationRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);
}

/**
 * @tc.name: RotationRecognizerHandleTouchUpEventTest001
 * @tc.desc: Test RotationRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerHandleTouchUpEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: touchPoints.size == fingers
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = FINGER_NUMBER;
    rotationRecognizer.refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer.currentFingers_ = rotationRecognizer.fingers_;
    rotationRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = FINGER_NUMBER;
    rotationRecognizer.refereeState_ = RefereeState::FAIL;
    rotationRecognizer.currentFingers_ = rotationRecognizer.fingers_;
    rotationRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::FAIL);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);
}

/**
 * @tc.name: RotationRecognizerHandleTouchMoveEventTest001
 * @tc.desc: Test RotationRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerHandleTouchMoveEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: touchPoints.size == fingers
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = FINGER_NUMBER;
    rotationRecognizer.refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer.currentFingers_ = rotationRecognizer.fingers_;
    rotationRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = FINGER_NUMBER;
    rotationRecognizer.refereeState_ = RefereeState::FAIL;
    rotationRecognizer.currentFingers_ = rotationRecognizer.fingers_;
    rotationRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::FAIL);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);
}

/**
 * @tc.name: RotationRecognizerHandleTouchMoveEventTest002
 * @tc.desc: Test RotationRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerHandleTouchMoveEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: touchPoints.size == fingers
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = FINGER_NUMBER_OVER_MAX;
    rotationRecognizer.refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer.currentFingers_ = rotationRecognizer.fingers_;
    rotationRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = 0;
    rotationRecognizer.refereeState_ = RefereeState::FAIL;
    rotationRecognizer.currentFingers_ = rotationRecognizer.fingers_;
    rotationRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::FAIL);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);
}

/**
 * @tc.name: RotationRecognizerHandleTouchMoveEventTest003
 * @tc.desc: Test RotationRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerHandleTouchMoveEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: touchPoints.size == fingers
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = FINGER_NUMBER_OVER_MAX;
    rotationRecognizer.refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer.currentFingers_ = rotationRecognizer.fingers_;
    rotationRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = 0;
    rotationRecognizer.refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer.currentFingers_ = rotationRecognizer.fingers_;
    rotationRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);
}

/**
 * @tc.name: RotationRecognizerTest003
 * @tc.desc: Test RotationRecognizer function: ChangeValueRange
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call ChangeValueRange function and compare result.
     * @tc.expected: step2. result equals.
     */
    auto result = rotationRecognizer.ChangeValueRange(COMMON_VALUE_RANGE_CASE);
    EXPECT_EQ(result, COMMON_VALUE_RANGE_CASE);

    result = rotationRecognizer.ChangeValueRange(SPECIAL_VALUE_RANGE_CASE1);
    EXPECT_EQ(result, SPECIAL_VALUE_RANGE_CASE1 - PI);

    result = rotationRecognizer.ChangeValueRange(SPECIAL_VALUE_RANGE_CASE2);
    EXPECT_EQ(result, SPECIAL_VALUE_RANGE_CASE2 + PI);
}

/**
 * @tc.name: RotationRecognizerTest004
 * @tc.desc: Test RotationRecognizer function: ComputeAngle
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call ComputeAngle function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEventStart;
    touchEventStart.id = 0;
    rotationRecognizer.touchPoints_[0] = touchEventStart;
    TouchEvent touchEventEnd;
    touchEventEnd.id = 1;
    rotationRecognizer.touchPoints_[1] = touchEventEnd;
    auto result = rotationRecognizer.ComputeAngle();
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: RotationRecognizerTest005
 * @tc.desc: Test RotationRecognizer function: OnResetStatus
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call OnResetStatus function and compare result.
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.OnResetStatus();
    EXPECT_EQ(rotationRecognizer.initialAngle_, 0.0);
    EXPECT_EQ(rotationRecognizer.currentAngle_, 0.0);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0.0);
}

/**
 * @tc.name: RotationRecognizerTest006
 * @tc.desc: Test RotationRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case1: onAction is no, *onAction is no
     * @tc.expected: step2. result equals.
     */
    std::unique_ptr<GestureEventFunc> onAction;
    rotationRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(rotationRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case2: onAction is yes, *onAction is no
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>();
    rotationRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(rotationRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    rotationRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(rotationRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    rotationRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    rotationRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(rotationRecognizer.touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    touchEvent.tiltX = 0.0f;
    touchEvent.tiltY = 0.0f;
    rotationRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    rotationRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(rotationRecognizer.touchPoints_.size(), 1);
}

/**
 * @tc.name: RotationRecognizerTest007
 * @tc.desc: Test RotationRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    RefPtr<RotationRecognizer> rotationRecognizerPtr =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    bool result = false;

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case1: recognizerPtr is nullptr
     * @tc.expected: step2. result equals.
     */
    result = rotationRecognizer.ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is normal, curr->fingers != fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = rotationRecognizerPtr->fingers_ + 1;
    result = rotationRecognizer.ReconcileFrom(rotationRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is normal, curr->angle != angle
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = rotationRecognizerPtr->fingers_;
    rotationRecognizer.angle_ = rotationRecognizerPtr->angle_ + 1;
    result = rotationRecognizer.ReconcileFrom(rotationRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is normal, curr->priorityMask != priorityMask
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = rotationRecognizerPtr->fingers_;
    rotationRecognizer.angle_ = rotationRecognizerPtr->angle_;
    rotationRecognizer.priorityMask_ = GestureMask::Begin;
    result = rotationRecognizer.ReconcileFrom(rotationRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is normal
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = rotationRecognizerPtr->fingers_;
    rotationRecognizer.angle_ = rotationRecognizerPtr->angle_;
    rotationRecognizer.priorityMask_ = rotationRecognizerPtr->priorityMask_;
    result = rotationRecognizer.ReconcileFrom(rotationRecognizerPtr);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: RotationRecognizerTest008
 * @tc.desc: Test RotationRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create rotationRecognizer.
     */
    auto rotationRecognizer = AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    ASSERT_NE(rotationRecognizer, nullptr);

    /**
     * @tc.steps: step2. test with HandleTouchDownEvent(AxisEvent).
     * @tc.expect: rotationRecognizer.lastAxisEvent_ is equal to axisEvent
     * @tc.expect: rotationRecognizer.touchPoints_[axisEvent.id].originalId is equal to axisEvent.originalId
     * @tc.expect: rotationRecognizer.touchPoints_[axisEvent.id].screenX is equal to axisEvent.screenX
     * @tc.expect: rotationRecognizer.touchPoints_[axisEvent.id].screenY is equal to axisEvent.screenY
     */
    AxisEvent axisEvent;
    axisEvent.id = TEST_EVENT_ID;
    axisEvent.originalId = TEST_EVENT_ID;
    axisEvent.isRotationEvent = true;

    rotationRecognizer->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer->currentFingers_ = rotationRecognizer->fingers_;
    rotationRecognizer->HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(rotationRecognizer->lastAxisEvent_.id, axisEvent.id);
    EXPECT_EQ(rotationRecognizer->touchPoints_[axisEvent.id].originalId, axisEvent.originalId);
    EXPECT_EQ(rotationRecognizer->touchPoints_[axisEvent.id].screenX, axisEvent.screenX);
    EXPECT_EQ(rotationRecognizer->touchPoints_[axisEvent.id].screenY, axisEvent.screenY);
}

/**
 * @tc.name: RotationRecognizerTest009
 * @tc.desc: Test RotationRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create rotationRecognizer.
     */
    auto rotationRecognizer = AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    ASSERT_NE(rotationRecognizer, nullptr);

    /**
     * @tc.steps: step2. test with HandleTouchUpEvent(AxisEvent).
     * @tc.expect: rotationRecognizer->lastAxisEvent_ is equal to axisEvent
     */
    AxisEvent axisEvent;
    axisEvent.isRotationEvent = true;
    axisEvent.id = TEST_EVENT_ID;
    rotationRecognizer->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer->currentFingers_ = rotationRecognizer->fingers_;
    rotationRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(rotationRecognizer->lastAxisEvent_.id, axisEvent.id);
}

/**
 * @tc.name: RotationRecognizerTest010
 * @tc.desc: Test RotationRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create rotationRecognizer.
     */
    auto rotationRecognizer = AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    ASSERT_NE(rotationRecognizer, nullptr);

    /**
     * @tc.steps: step2. test with HandleTouchMoveEvent(AxisEvent).
     * @tc.expect: rotationRecognizer->lastAxisEvent_ is equal to axisEvent
     * @tc.expect: rotationRecognizer->touchPoints_[axisEvent.id].originalId is equal to axisEvent.originalId
     * @tc.expect: rotationRecognizer->touchPoints_[axisEvent.id].screenX is equal to axisEvent.screenX
     * @tc.expect: rotationRecognizer->touchPoints_[axisEvent.id].screenY is equal to axisEvent.screenY
     */
    AxisEvent axisEvent;
    axisEvent.id = TEST_EVENT_ID;
    axisEvent.originalId = TEST_EVENT_ID;
    axisEvent.isRotationEvent = true;
    rotationRecognizer->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer->currentFingers_ = rotationRecognizer->fingers_;
    rotationRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(rotationRecognizer->lastAxisEvent_.id, axisEvent.id);
    EXPECT_EQ(rotationRecognizer->touchPoints_[axisEvent.id].originalId, axisEvent.originalId);
    EXPECT_EQ(rotationRecognizer->touchPoints_[axisEvent.id].screenX, axisEvent.screenX);
    EXPECT_EQ(rotationRecognizer->touchPoints_[axisEvent.id].screenY, axisEvent.screenY);
}

/**
 * @tc.name: RotationRecognizerSendCallbackMsgTest001
 * @tc.desc: Test RotationRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerSendCallbackMsgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    std::unique_ptr<GestureEventFunc> onAction;

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty, type is AXIS
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    rotationRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(rotationRecognizer.touchPoints_.size(), 0);
}

/**
 * @tc.name: RotationGestureTest001
 * @tc.desc: Test RotationGesture CreateRecognizer function
 */
HWTEST_F(RotationRecognizerTestNg, RotationGestureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationGestureGesture.
     */
    RotationGestureModelNG rotationGestureModelNG;
    rotationGestureModelNG.Create(FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto rotationGestureNG = AceType::DynamicCast<NG::RotationGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(rotationGestureNG->angle_, ROTATION_GESTURE_ANGLE);

    RotationGesture rotationGesture = RotationGesture(FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    EXPECT_EQ(rotationGesture.angle_, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: functions are not existed
     */
    rotationGesture.priority_ = GesturePriority::Low;
    rotationGesture.gestureMask_ = GestureMask::Normal;
    auto rotationRecognizer = AceType::DynamicCast<RotationRecognizer>(rotationGesture.CreateRecognizer());
    EXPECT_NE(rotationRecognizer, nullptr);
    EXPECT_EQ(rotationRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(rotationRecognizer->GetPriorityMask(), GestureMask::Normal);

    // /**
    //  * @tc.steps: step2. call CreateRecognizer function and compare result
    //  * @tc.steps: case2: functions are existed
    //  */
    std::unique_ptr<GestureEventFunc> onActionStartId;
    std::unique_ptr<GestureEventFunc> onActionUpdateId;
    std::unique_ptr<GestureEventFunc> onActionEndId;
    std::unique_ptr<GestureEventNoParameter> onActionCancelId;
    rotationGesture.onActionStartId_ = std::move(onActionStartId);
    rotationGesture.onActionUpdateId_ = std::move(onActionUpdateId);
    rotationGesture.onActionEndId_ = std::move(onActionEndId);
    rotationGesture.onActionCancelId_ = std::move(onActionCancelId);
    rotationRecognizer = AceType::DynamicCast<RotationRecognizer>(rotationGesture.CreateRecognizer());
    EXPECT_EQ(rotationRecognizer->priority_, rotationGesture.priority_);
    EXPECT_EQ(rotationRecognizer->priorityMask_, rotationGesture.gestureMask_);
}

/**
 * @tc.name: RotationGestureCreateRecognizerTest001
 * @tc.desc: Test RotationGesture CreateRecognizer function
 */
HWTEST_F(RotationRecognizerTestNg, RotationGestureCreateRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationGestureGesture.
     */
    RotationGestureModelNG rotationGestureModelNG;
    rotationGestureModelNG.Create(FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto rotationGestureNG = AceType::DynamicCast<NG::RotationGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(rotationGestureNG->angle_, ROTATION_GESTURE_ANGLE);

    RotationGesture rotationGesture = RotationGesture(FINGER_NUMBER, 0.0);
    EXPECT_EQ(rotationGesture.angle_, ROTATION_GESTURE_ANGLE);
    RotationGesture rotationGestureTwo = RotationGesture(FINGER_NUMBER, -1.0);
    EXPECT_EQ(rotationGestureTwo.angle_, ROTATION_GESTURE_ANGLE);
    RotationGesture rotationGestureThree = RotationGesture(FINGER_NUMBER, 361.0);
    EXPECT_EQ(rotationGestureThree.angle_, ROTATION_GESTURE_ANGLE);
}


/**
 * @tc.name: RotationGestureCreateRecognizerTest002
 * @tc.desc: Test RotationGesture CreateRecognizer function
 */
HWTEST_F(RotationRecognizerTestNg, RotationGestureCreateRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationGestureGesture.
     */
    RotationGestureModelNG rotationGestureModelNG;
    rotationGestureModelNG.Create(FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto rotationGestureNG = AceType::DynamicCast<NG::RotationGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(rotationGestureNG->angle_, ROTATION_GESTURE_ANGLE);

    RotationGesture rotationGesture = RotationGesture(FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    EXPECT_EQ(rotationGesture.angle_, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: functions are not existed
     */
    rotationGesture.priority_ = GesturePriority::Low;
    rotationGesture.gestureMask_ = GestureMask::Normal;
    auto rotationRecognizer = AceType::DynamicCast<RotationRecognizer>(rotationGesture.CreateRecognizer());
    EXPECT_NE(rotationRecognizer, nullptr);
    EXPECT_EQ(rotationRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(rotationRecognizer->GetPriorityMask(), GestureMask::Normal);

    // /**
    //  * @tc.steps: step2. call CreateRecognizer function and compare result
    //  * @tc.steps: case2: functions are existed
    //  */
    std::unique_ptr<GestureEventFunc> onActionStartId;
    std::unique_ptr<GestureEventFunc> onActionUpdateId;
    std::unique_ptr<GestureEventFunc> onActionEndId;
    std::unique_ptr<GestureEventNoParameter> onActionCancelId;
    rotationGesture.onActionStartId_ = std::move(onActionStartId);
    rotationGesture.onActionUpdateId_ = std::move(onActionUpdateId);
    rotationGesture.onActionEndId_ = std::move(onActionEndId);
    rotationGesture.onActionCancelId_ = std::move(onActionCancelId);
    rotationGesture.priority_ = GesturePriority::Low;
    rotationGesture.gestureMask_ = GestureMask::Normal;
    auto onActionStart = [](GestureEvent& info) { return true; };
    auto onActionUpdate = [](GestureEvent& info) { return true; };
    auto onActionEnd = [](GestureEvent& info) { return true; };
    auto onActionCancel = []() { return true; };
    rotationGesture.SetOnActionStartId(onActionStart);
    rotationGesture.SetOnActionUpdateId(onActionUpdate);
    rotationGesture.SetOnActionEndId(onActionEnd);
    rotationGesture.SetOnActionCancelId(onActionCancel);
    rotationRecognizer = AceType::DynamicCast<RotationRecognizer>(rotationGesture.CreateRecognizer());
    EXPECT_EQ(rotationRecognizer->priority_, rotationGesture.priority_);
    EXPECT_EQ(rotationRecognizer->priorityMask_, rotationGesture.gestureMask_);
}

/**
 * @tc.name: RotationRecognizerHandleTouchUpEventTest002
 * @tc.desc: Test HandleTouchUpEvent in RotationRecognizer
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerHandleTouchUpEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create clickRecognizerPtr.
     */
    RefPtr<RotationRecognizer> rotationRecognizerPtr =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    TouchEvent touchEvent;
    rotationRecognizerPtr->activeFingers_.emplace_back(touchEvent.id);

    rotationRecognizerPtr->refereeState_ = RefereeState::PENDING;
    rotationRecognizerPtr->currentFingers_ = rotationRecognizerPtr->fingers_;
    rotationRecognizerPtr->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(rotationRecognizerPtr->refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: RotationRecognizerHandleTouchCancelEventTest002
 * @tc.desc: Test HandleTouchCancelEvent in RotationRecognizer
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerHandleTouchCancelEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create clickRecognizerPtr.
     */
    RefPtr<RotationRecognizer> rotationRecognizerPtr =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    TouchEvent touchEvent;

    rotationRecognizerPtr->activeFingers_.emplace_back(touchEvent.id);
    rotationRecognizerPtr->refereeState_ = RefereeState::PENDING;
    rotationRecognizerPtr->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(rotationRecognizerPtr->refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: RotationRecognizerHandleTouchMoveEventTest006
 * @tc.desc: Test HandleTouchMoveEvent in RotationRecognizer
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerHandleTouchMoveEventTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create clickRecognizerPtr.
     */
    RefPtr<RotationRecognizer> rotationRecognizerPtr =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    TouchEvent touchEvent;

    rotationRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    rotationRecognizerPtr->fingers_ = 0;
    rotationRecognizerPtr->currentFingers_ = rotationRecognizerPtr->fingers_;
    rotationRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizerPtr->refereeState_, RefereeState::DETECTING);
}

/**
 * @tc.name: RotationRecognizerPtrHandleTouchUpEventTest001
 * @tc.desc: Test RotationRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerPtrHandleTouchUpEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and set Recognizer、TargetComponent.
     */
    RefPtr<RotationRecognizer> rotationRecognizerPtr =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;};
    targetComponent->SetOnGestureJudgeBegin(gestureJudgeFunc);
    TouchEvent touchEvent;
    touchEvent.tiltX.emplace(1.0f);
    touchEvent.tiltY.emplace(1.0f);
    rotationRecognizerPtr->targetComponent_ = targetComponent;
    /**
     * @tc.steps: step2. test the function who calls TriggerGestureJudgeCallback.
     * @tc.expected: step2. result equals REJECT.
     */
    rotationRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    rotationRecognizerPtr->currentFingers_ = 2;
    rotationRecognizerPtr->fingers_ = 2;
    rotationRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    rotationRecognizerPtr->activeFingers_.push_back(1);
    rotationRecognizerPtr->angle_ = 0;
    rotationRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizerPtr->disposal_, GestureDisposal::REJECT);
}

/**
 * @tc.name: RotationRecognizerHandleTouchDownEventTest001
 * @tc.desc: Test RotationRecognizer function with axis event input: Down
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerHandleAxisEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create rotation recognizer and axis event.
     */
    AxisEvent event;
    RefPtr<RotationRecognizer> recognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    /**
     * @tc.steps: step2. Test HandleTouchDownEvent
     */
    event.isRotationEvent = false;
    recognizer->refereeState_ = RefereeState::READY;
    recognizer->HandleTouchDownEvent(event);
    EXPECT_EQ(recognizer->refereeState_, RefereeState::READY);

    event.isRotationEvent = true;
    recognizer->refereeState_ = RefereeState::READY;
    recognizer->HandleTouchDownEvent(event);
    EXPECT_EQ(recognizer->refereeState_, RefereeState::DETECTING);

    event.isRotationEvent = true;
    recognizer->refereeState_ = RefereeState::SUCCEED;
    recognizer->HandleTouchDownEvent(event);
    EXPECT_EQ(recognizer->refereeState_, RefereeState::SUCCEED);
}
/**
 * @tc.name: RotationRecognizerHandleTouchDownEventTest002
 * @tc.desc: Test RotationRecognizer function with axis event input: Up
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerHandleAxisEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create rotation recognizer and axis event.
     */
    AxisEvent event;
    RefPtr<RotationRecognizer> recognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    /**
     * @tc.steps: step2. Test HandleTouchUpEvent
     */
    recognizer->refereeState_ = RefereeState::READY;
    recognizer->HandleTouchUpEvent(event);
    EXPECT_EQ(recognizer->refereeState_, RefereeState::READY);

    recognizer->refereeState_ = RefereeState::SUCCEED;
    recognizer->HandleTouchUpEvent(event);
    EXPECT_EQ(recognizer->refereeState_, RefereeState::SUCCEED);
}
/**
 * @tc.name: RotationRecognizerHandleTouchDownEventTest003
 * @tc.desc: Test RotationRecognizer function with axis event input: Move
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerHandleAxisEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create rotation recognizer and axis event.
     */
    AxisEvent event;
    RefPtr<RotationRecognizer> recognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    /**
     * @tc.steps: step2. Test HandleTouchMoveEvent
     */
    event.isRotationEvent = true;
    recognizer->refereeState_ = RefereeState::DETECTING;
    recognizer->HandleTouchMoveEvent(event);
    EXPECT_EQ(recognizer->refereeState_, RefereeState::DETECTING);

    event.isRotationEvent = true;
    event.rotateAxisAngle = ROTATION_GESTURE_ANGLE;
    recognizer->refereeState_ = RefereeState::DETECTING;
    recognizer->HandleTouchMoveEvent(event);
    EXPECT_EQ(recognizer->refereeState_, RefereeState::DETECTING);

    event.isRotationEvent = true;
    event.rotateAxisAngle = 2 * ROTATION_GESTURE_ANGLE;
    recognizer->refereeState_ = RefereeState::DETECTING;
    recognizer->HandleTouchMoveEvent(event);
    EXPECT_NE(recognizer->refereeState_, RefereeState::DETECTING);

    event.isRotationEvent = true;
    recognizer->refereeState_ = RefereeState::SUCCEED;
    recognizer->HandleTouchMoveEvent(event);
    EXPECT_EQ(recognizer->refereeState_, RefereeState::SUCCEED);

    event.isRotationEvent = true;
    recognizer->refereeState_ = RefereeState::READY;
    recognizer->HandleTouchMoveEvent(event);
    EXPECT_EQ(recognizer->refereeState_, RefereeState::READY);

    event.isRotationEvent = false;
    recognizer->refereeState_ = RefereeState::READY;
    recognizer->HandleTouchMoveEvent(event);
    EXPECT_EQ(recognizer->refereeState_, RefereeState::READY);
}
/**
 * @tc.name: RotationRecognizerHandleTouchDownEventTest004
 * @tc.desc: Test RotationRecognizer function with axis event input: Cancel
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerHandleAxisEventTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create rotation recognizer and axis event.
     */
    AxisEvent event;
    RefPtr<RotationRecognizer> recognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    /**
     * @tc.steps: step2. Test HandleTouchCancelEvent
     */
    recognizer->refereeState_ = RefereeState::READY;
    recognizer->HandleTouchCancelEvent(event);
    EXPECT_EQ(recognizer->refereeState_, RefereeState::FAIL);

    recognizer->refereeState_ = RefereeState::SUCCEED;
    recognizer->HandleTouchCancelEvent(event);
    EXPECT_EQ(recognizer->refereeState_, RefereeState::SUCCEED);
}
} // namespace OHOS::Ace::NG