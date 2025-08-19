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
#include "ui/base/ace_type.h"
#include "ui/base/referenced.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
constexpr float GESTURE_EVENT_PROPERTY_DEFAULT_VALUE = 0.0;
constexpr float GESTURE_EVENT_PROPERTY_VALUE = 10.0;
struct MockRotationRecognizerCase {
    int32_t fingers;
    double angle;
    RefereeState refereeState;
    int32_t expectedFingers;
    double expectedAngle;
    RefereeState expectedRefereeState;
    std::vector<TouchEvent> inputTouchEvents;
};
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
    RefPtr<RotationRecognizer> rotationRecognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer->OnAccepted();
    EXPECT_EQ(rotationRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.expected: step3. result equals.
     */
    rotationRecognizer->OnRejected();
    EXPECT_EQ(rotationRecognizer->refereeState_, RefereeState::SUCCEED);
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
    RefPtr<RotationRecognizer> rotationRecognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: touchPoints.size == fingers
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    rotationRecognizer->fingers_ = 0;
    rotationRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer->fingers_ = 0;
    rotationRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer->refereeState_ = RefereeState::FAIL;
    rotationRecognizer->fingers_ = 0;
    rotationRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->resultAngle_, 0);
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
    RefPtr<RotationRecognizer> rotationRecognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

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
    rotationRecognizer->fingers_ = FINGER_NUMBER;
    rotationRecognizer->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer->currentFingers_ = rotationRecognizer->fingers_;
    rotationRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(rotationRecognizer->resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer->fingers_ = FINGER_NUMBER;
    rotationRecognizer->refereeState_ = RefereeState::FAIL;
    rotationRecognizer->currentFingers_ = rotationRecognizer->fingers_;
    rotationRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->refereeState_, RefereeState::FAIL);
    EXPECT_EQ(rotationRecognizer->resultAngle_, 0);
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
    RefPtr<RotationRecognizer> rotationRecognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

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
    rotationRecognizer->fingers_ = FINGER_NUMBER;
    rotationRecognizer->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer->currentFingers_ = rotationRecognizer->fingers_;
    rotationRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(rotationRecognizer->resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer->fingers_ = FINGER_NUMBER;
    rotationRecognizer->refereeState_ = RefereeState::FAIL;
    rotationRecognizer->currentFingers_ = rotationRecognizer->fingers_;
    rotationRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->refereeState_, RefereeState::FAIL);
    EXPECT_EQ(rotationRecognizer->resultAngle_, 0);
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
    RefPtr<RotationRecognizer> rotationRecognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

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
    rotationRecognizer->fingers_ = FINGER_NUMBER_OVER_MAX;
    rotationRecognizer->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer->currentFingers_ = rotationRecognizer->fingers_;
    rotationRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(rotationRecognizer->resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer->fingers_ = 0;
    rotationRecognizer->refereeState_ = RefereeState::FAIL;
    rotationRecognizer->currentFingers_ = rotationRecognizer->fingers_;
    rotationRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->refereeState_, RefereeState::FAIL);
    EXPECT_EQ(rotationRecognizer->resultAngle_, 0);
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
    RefPtr<RotationRecognizer> rotationRecognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

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
    rotationRecognizer->fingers_ = FINGER_NUMBER_OVER_MAX;
    rotationRecognizer->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer->currentFingers_ = rotationRecognizer->fingers_;
    rotationRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(rotationRecognizer->resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer->fingers_ = 0;
    rotationRecognizer->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer->currentFingers_ = rotationRecognizer->fingers_;
    rotationRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(rotationRecognizer->resultAngle_, 0);
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
    RefPtr<RotationRecognizer> rotationRecognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call ChangeValueRange function and compare result.
     * @tc.expected: step2. result equals.
     */
    auto result = rotationRecognizer->ChangeValueRange(COMMON_VALUE_RANGE_CASE);
    EXPECT_EQ(result, COMMON_VALUE_RANGE_CASE);

    result = rotationRecognizer->ChangeValueRange(SPECIAL_VALUE_RANGE_CASE1);
    EXPECT_EQ(result, SPECIAL_VALUE_RANGE_CASE1 - PI);

    result = rotationRecognizer->ChangeValueRange(SPECIAL_VALUE_RANGE_CASE2);
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
    RefPtr<RotationRecognizer> rotationRecognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call ComputeAngle function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEventStart;
    touchEventStart.id = 0;
    rotationRecognizer->touchPoints_[0] = touchEventStart;
    TouchEvent touchEventEnd;
    touchEventEnd.id = 1;
    rotationRecognizer->touchPoints_[1] = touchEventEnd;
    auto result = rotationRecognizer->ComputeAngle();
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
    RefPtr<RotationRecognizer> rotationRecognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call OnResetStatus function and compare result.
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer->OnResetStatus();
    EXPECT_EQ(rotationRecognizer->initialAngle_, 0.0);
    EXPECT_EQ(rotationRecognizer->currentAngle_, 0.0);
    EXPECT_EQ(rotationRecognizer->resultAngle_, 0.0);
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
    RefPtr<RotationRecognizer> rotationRecognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case1: onAction is no, *onAction is no
     * @tc.expected: step2. result equals.
     */
    std::unique_ptr<GestureEventFunc> onAction;
    rotationRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(rotationRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case2: onAction is yes, *onAction is no
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>();
    rotationRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(rotationRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    rotationRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(rotationRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    rotationRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    rotationRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(rotationRecognizer->touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    touchEvent.tiltX = 0.0f;
    touchEvent.tiltY = 0.0f;
    rotationRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    rotationRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(rotationRecognizer->touchPoints_.size(), 1);
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
    RefPtr<RotationRecognizer> rotationRecognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    RefPtr<RotationRecognizer> rotationRecognizerPtr =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    bool result = false;

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case1: recognizerPtr is nullptr
     * @tc.expected: step2. result equals.
     */
    result = rotationRecognizer->ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is normal, curr->fingers != fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer->fingers_ = rotationRecognizerPtr->fingers_ + 1;
    result = rotationRecognizer->ReconcileFrom(rotationRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is normal, curr->angle != angle
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer->fingers_ = rotationRecognizerPtr->fingers_;
    rotationRecognizer->angle_ = rotationRecognizerPtr->angle_ + 1;
    result = rotationRecognizer->ReconcileFrom(rotationRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is normal, curr->priorityMask != priorityMask
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer->fingers_ = rotationRecognizerPtr->fingers_;
    rotationRecognizer->angle_ = rotationRecognizerPtr->angle_;
    rotationRecognizer->priorityMask_ = GestureMask::Begin;
    result = rotationRecognizer->ReconcileFrom(rotationRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is normal
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer->fingers_ = rotationRecognizerPtr->fingers_;
    rotationRecognizer->angle_ = rotationRecognizerPtr->angle_;
    rotationRecognizer->priorityMask_ = rotationRecognizerPtr->priorityMask_;
    result = rotationRecognizer->ReconcileFrom(rotationRecognizerPtr);
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
     * @tc.steps: step1. create rotationRecognizer->
     */
    auto rotationRecognizer = AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    ASSERT_NE(rotationRecognizer, nullptr);

    /**
     * @tc.steps: step2. test with HandleTouchDownEvent(AxisEvent).
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
     * @tc.steps: step1. create rotationRecognizer->
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
     * @tc.steps: step1. create rotationRecognizer->
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
    RefPtr<RotationRecognizer> rotationRecognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    std::unique_ptr<GestureEventFunc> onAction;

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty, type is AXIS
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    rotationRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(rotationRecognizer->touchPoints_.size(), 0);
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
    std::unique_ptr<GestureEventFunc> onActionCancelId;
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
    std::unique_ptr<GestureEventFunc> onActionCancelId;
    rotationGesture.onActionStartId_ = std::move(onActionStartId);
    rotationGesture.onActionUpdateId_ = std::move(onActionUpdateId);
    rotationGesture.onActionEndId_ = std::move(onActionEndId);
    rotationGesture.onActionCancelId_ = std::move(onActionCancelId);
    rotationGesture.priority_ = GesturePriority::Low;
    rotationGesture.gestureMask_ = GestureMask::Normal;
    auto onActionStart = [](GestureEvent& info) { return true; };
    auto onActionUpdate = [](GestureEvent& info) { return true; };
    auto onActionEnd = [](GestureEvent& info) { return true; };
    auto onActionCancel = [](GestureEvent& info) { return true; };
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

/**
 * @tc.name: SetOnActionCancelTest001
 * @tc.desc: Test SendCallbackMsg function in the HandleTouchCancelEvent with touch event input. The onActionCancel
 * function will return GestureEvent info.
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, SetOnActionCancelTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RotationRecognizerTestNg.
     */
    RefPtr<RotationRecognizer> rotationRecognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. Call SetOnActionCancel.
     * @tc.expected: RotationRecognizer's callback onActionCancel is not nullptr.
     */
    rotationRecognizer->deviceId_ = GESTURE_EVENT_PROPERTY_VALUE;
    double unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    auto onActionCancel = [&unknownPropertyValue](
                                GestureEvent& info) { unknownPropertyValue = info.GetDeviceId(); };
    rotationRecognizer->SetOnActionCancel(onActionCancel);
    EXPECT_NE(rotationRecognizer->onActionCancel_, nullptr);

    /**
     * @tc.steps: step3. Invoke HandleTouchCancelEvent when onActionCancel_ is not null.
     * @tc.expected: The functions have been executed and the unknownPropertyValue has been assigned the correct
     * value. rotationRecognizer->refereeState_ = RefereeState::READY
     */
    TouchEvent touchEvent;
    rotationRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    rotationRecognizer->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer->activeFingers_.emplace_back(touchEvent.id);
    rotationRecognizer->activeFingers_.push_back(1);
    rotationRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
    EXPECT_EQ(rotationRecognizer->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: SetOnActionCancelTest002
 * @tc.desc: Test SendCallbackMsg function in the HandleTouchCancelEvent with axis event input. The onActionCancel
 * function will return GestureEvent info.
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, SetOnActionCancelTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RotationRecognizer.
     */
    RefPtr<RotationRecognizer> rotationRecognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. Call SetOnActionCancel.
     * @tc.expected: rotationRecognizer's callback onActionCancel is not nullptr.
     */
    rotationRecognizer->deviceId_ = GESTURE_EVENT_PROPERTY_VALUE;
    double unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    auto onActionCancel = [&unknownPropertyValue](
                                GestureEvent& info) { unknownPropertyValue = info.GetDeviceId(); };
    rotationRecognizer->SetOnActionCancel(onActionCancel);
    EXPECT_NE(rotationRecognizer->onActionCancel_, nullptr);

    /**
     * @tc.steps: step3. Invoke HandleTouchCancelEvent when onActionCancel_ is not null.
     * @tc.expected: The functions have been executed and the unknownPropertyValue has been assigned the correct
     * value.
     */
    AxisEvent axisEvent;
    rotationRecognizer->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer->HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
}

/**
 * @tc.name: SetOnActionCancelTest003
 * @tc.desc: Test SendCallbackMsg function in the ReconcileFrom. The onActionCancel function will return
 * GestureEvent info.
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, SetOnActionCancelTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RotationRecognizer.
     */
    RefPtr<RotationRecognizer> rotationRecognizer =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    RefPtr<RotationRecognizer> rotationRecognizerPtr =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. Call SetOnActionCancel.
     * @tc.expected: rotationRecognizer's callback onActionCancel is not nullptr.
     */
    rotationRecognizer->deviceId_ = GESTURE_EVENT_PROPERTY_VALUE;
    double unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    auto onActionCancel = [&unknownPropertyValue](
                                GestureEvent& info) { unknownPropertyValue = info.GetDeviceId(); };
    rotationRecognizer->SetOnActionCancel(onActionCancel);
    EXPECT_NE(rotationRecognizer->onActionCancel_, nullptr);

    /**
     * @tc.steps: step3. Invoke ReconcileFrom when onActionCancel_ is not null.
     * @tc.expected: The functions have been executed and the unknownPropertyValue has been assigned the correct
     * value.
     */
    rotationRecognizer->fingers_ = 0;
    rotationRecognizer->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer->activeFingers_.push_back(1);
    rotationRecognizer->activeFingers_.push_back(2);
    auto result = rotationRecognizer->ReconcileFrom(rotationRecognizerPtr);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: RotationGestureLimitFingerTest001
 * @tc.desc: Test RotationGesture CreateRecognizer function
 */
HWTEST_F(RotationRecognizerTestNg, RotationGestureLimitFingerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationGestureGesture.
     */
    RotationGestureModelNG rotationGestureModelNG;
    rotationGestureModelNG.Create(FINGER_NUMBER, ROTATION_GESTURE_ANGLE, IS_LIMIT_FINGER_COUNT);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto rotationGestureNG = AceType::DynamicCast<NG::RotationGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(rotationGestureNG->angle_, ROTATION_GESTURE_ANGLE);
    EXPECT_EQ(rotationGestureNG->isLimitFingerCount_, IS_LIMIT_FINGER_COUNT);

    RotationGesture rotationGesture = RotationGesture(FINGER_NUMBER, ROTATION_GESTURE_ANGLE, IS_LIMIT_FINGER_COUNT);
    EXPECT_EQ(rotationGesture.angle_, ROTATION_GESTURE_ANGLE);
    EXPECT_EQ(rotationGesture.isLimitFingerCount_, IS_LIMIT_FINGER_COUNT);

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
    EXPECT_EQ(rotationRecognizer->isLimitFingerCount_, IS_LIMIT_FINGER_COUNT);

    // /**
    //  * @tc.steps: step2. call CreateRecognizer function and compare result
    //  * @tc.steps: case2: functions are existed
    //  */
    std::unique_ptr<GestureEventFunc> onActionStartId;
    std::unique_ptr<GestureEventFunc> onActionUpdateId;
    std::unique_ptr<GestureEventFunc> onActionEndId;
    std::unique_ptr<GestureEventFunc> onActionCancelId;
    rotationGesture.onActionStartId_ = std::move(onActionStartId);
    rotationGesture.onActionUpdateId_ = std::move(onActionUpdateId);
    rotationGesture.onActionEndId_ = std::move(onActionEndId);
    rotationGesture.onActionCancelId_ = std::move(onActionCancelId);
    rotationRecognizer = AceType::DynamicCast<RotationRecognizer>(rotationGesture.CreateRecognizer());
    EXPECT_EQ(rotationRecognizer->priority_, rotationGesture.priority_);
    EXPECT_EQ(rotationRecognizer->priorityMask_, rotationGesture.gestureMask_);
    EXPECT_EQ(rotationRecognizer->isLimitFingerCount_, IS_LIMIT_FINGER_COUNT);
}

/**
 * @tc.name: RotationGestureLimitFingerTest002
 * @tc.desc: Test RotationGesture CreateRecognizer function
 */
HWTEST_F(RotationRecognizerTestNg, RotationGestureLimitFingerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationGestureGesture.
     */
    RotationGestureModelNG rotationGestureModelNG;
    rotationGestureModelNG.Create(FINGER_NUMBER, ROTATION_GESTURE_ANGLE, IS_NOT_LIMIT_FINGER_COUNT);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto rotationGestureNG = AceType::DynamicCast<NG::RotationGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(rotationGestureNG->angle_, ROTATION_GESTURE_ANGLE);
    EXPECT_EQ(rotationGestureNG->isLimitFingerCount_, IS_NOT_LIMIT_FINGER_COUNT);

    RotationGesture rotationGesture = RotationGesture(FINGER_NUMBER, ROTATION_GESTURE_ANGLE, IS_NOT_LIMIT_FINGER_COUNT);
    EXPECT_EQ(rotationGesture.angle_, ROTATION_GESTURE_ANGLE);
    EXPECT_EQ(rotationGesture.isLimitFingerCount_, IS_NOT_LIMIT_FINGER_COUNT);

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
    EXPECT_EQ(rotationRecognizer->isLimitFingerCount_, IS_NOT_LIMIT_FINGER_COUNT);

    // /**
    //  * @tc.steps: step2. call CreateRecognizer function and compare result
    //  * @tc.steps: case2: functions are existed
    //  */
    std::unique_ptr<GestureEventFunc> onActionStartId;
    std::unique_ptr<GestureEventFunc> onActionUpdateId;
    std::unique_ptr<GestureEventFunc> onActionEndId;
    std::unique_ptr<GestureEventFunc> onActionCancelId;
    rotationGesture.onActionStartId_ = std::move(onActionStartId);
    rotationGesture.onActionUpdateId_ = std::move(onActionUpdateId);
    rotationGesture.onActionEndId_ = std::move(onActionEndId);
    rotationGesture.onActionCancelId_ = std::move(onActionCancelId);
    rotationRecognizer = AceType::DynamicCast<RotationRecognizer>(rotationGesture.CreateRecognizer());
    EXPECT_EQ(rotationRecognizer->priority_, rotationGesture.priority_);
    EXPECT_EQ(rotationRecognizer->priorityMask_, rotationGesture.gestureMask_);
    EXPECT_EQ(rotationRecognizer->isLimitFingerCount_, IS_NOT_LIMIT_FINGER_COUNT);
}

/**
 * @tc.name: OnAcceptedTest001
 * @tc.desc: Test OnAccepted function
 */
HWTEST_F(RotationRecognizerTestNg, OnAcceptedTest001, TestSize.Level1)
{
    RotationGestureModelNG rotationGestureModelNG;
    rotationGestureModelNG.Create(FINGER_NUMBER, ROTATION_GESTURE_ANGLE, IS_NOT_LIMIT_FINGER_COUNT);
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto rotationGestureNG = AceType::DynamicCast<NG::RotationGesture>(gestureProcessor->TopGestureNG());
    RotationGesture rotationGesture = RotationGesture(FINGER_NUMBER, ROTATION_GESTURE_ANGLE, IS_NOT_LIMIT_FINGER_COUNT);

    rotationGesture.priority_ = GesturePriority::Low;
    rotationGesture.gestureMask_ = GestureMask::Normal;
    auto rotationRecognizer = AceType::DynamicCast<RotationRecognizer>(rotationGesture.CreateRecognizer());
    TimeStamp timeStape = std::chrono::high_resolution_clock::now();
    rotationRecognizer->firstInputTime_ = timeStape;
    SystemProperties::traceInputEventEnable_ = true;
    rotationRecognizer->OnAccepted();
    EXPECT_NE(rotationRecognizer, nullptr);
}

/**
 * @tc.name: HandleTouchUpEvent001
 * @tc.desc: Test HandleTouchUpEvent function
 */
HWTEST_F(RotationRecognizerTestNg, HandleTouchUpEvent001, TestSize.Level1)
{
    RotationGestureModelNG rotationGestureModelNG;
    rotationGestureModelNG.Create(FINGER_NUMBER, ROTATION_GESTURE_ANGLE, IS_NOT_LIMIT_FINGER_COUNT);
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto rotationGestureNG = AceType::DynamicCast<NG::RotationGesture>(gestureProcessor->TopGestureNG());
    RotationGesture rotationGesture = RotationGesture(FINGER_NUMBER, ROTATION_GESTURE_ANGLE, IS_NOT_LIMIT_FINGER_COUNT);

    rotationGesture.priority_ = GesturePriority::Low;
    rotationGesture.gestureMask_ = GestureMask::Normal;
    auto rotationRecognizer = AceType::DynamicCast<RotationRecognizer>(rotationGesture.CreateRecognizer());
    TouchEvent touchEvent;

    rotationRecognizer->isNeedResetVoluntarily_ = true;
    rotationRecognizer->currentFingers_ = 1;
    rotationRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->isNeedResetVoluntarily_, false);

    rotationRecognizer->isNeedResetVoluntarily_ = false;
    rotationRecognizer->currentFingers_ = 1;
    rotationRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->isNeedResetVoluntarily_, false);

    rotationRecognizer->isNeedResetVoluntarily_ = true;
    rotationRecognizer->currentFingers_ = 0;
    rotationRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->isNeedResetVoluntarily_, true);

    rotationRecognizer->isNeedResetVoluntarily_ = false;
    rotationRecognizer->currentFingers_ = 0;
    rotationRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->isNeedResetVoluntarily_, false);
}

/**
 * @tc.name: HandleTouchUpEvent002
 * @tc.desc: Test HandleTouchUpEvent function
 */
HWTEST_F(RotationRecognizerTestNg, HandleTouchUpEvent002, TestSize.Level1)
{
    int32_t DEFAULT_ROTATION_FINGERS = 2;
    auto rotationRecognizer = AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    int32_t testId = 1;
    int32_t testId2 = 2;
    TouchEvent touchEvent;
    touchEvent.id = testId;
    rotationRecognizer->activeFingers_.push_front(testId);
    rotationRecognizer->activeFingers_.push_front(testId2);
    rotationRecognizer->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->activeFingers_.size(), DEFAULT_ROTATION_FINGERS - 1);
    EXPECT_TRUE(rotationRecognizer->isNeedResetVoluntarily_);
    rotationRecognizer->activeFingers_.push_front(testId);
    TimeStamp timeStape = std::chrono::high_resolution_clock::now();
    rotationRecognizer->firstInputTime_ = timeStape;
    SystemProperties::traceInputEventEnable_ = false;
    rotationRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer->activeFingers_.size(), DEFAULT_ROTATION_FINGERS - 1);
    EXPECT_TRUE(rotationRecognizer->isNeedResetVoluntarily_);

    auto rotationRecognizer1 = AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    rotationRecognizer1->activeFingers_.clear();
    rotationRecognizer1->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer1->activeFingers_.push_front(testId);
    rotationRecognizer1->HandleTouchUpEvent(touchEvent);
    EXPECT_FALSE(rotationRecognizer1->isNeedResetVoluntarily_);

    auto rotationRecognizer2 = AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    rotationRecognizer2->activeFingers_.clear();
    rotationRecognizer2->activeFingers_.push_front(testId2);
    rotationRecognizer2->activeFingers_.push_front(testId);
    rotationRecognizer2->refereeState_ = RefereeState::FAIL;
    rotationRecognizer2->HandleTouchUpEvent(touchEvent);
    EXPECT_FALSE(rotationRecognizer2->isNeedResetVoluntarily_);

    auto rotationRecognizer3 = AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    int32_t testId3 = 3;
    rotationRecognizer3->activeFingers_.clear();
    rotationRecognizer3->activeFingers_.push_front(testId);
    rotationRecognizer3->activeFingers_.push_front(testId2);
    rotationRecognizer3->activeFingers_.push_front(testId3);
    rotationRecognizer3->refereeState_ = RefereeState::FAIL;
    rotationRecognizer3->HandleTouchUpEvent(touchEvent);
    EXPECT_FALSE(rotationRecognizer3->isNeedResetVoluntarily_);
}

/**
 * @tc.name: HandleTouchUpEvent003
 * @tc.desc: Test HandleTouchUpEvent function
 */
HWTEST_F(RotationRecognizerTestNg, HandleTouchUpEvent003, TestSize.Level1)
{
    auto rotationRecognizer = AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    AxisEvent event;
    event.isRotationEvent = true;
    rotationRecognizer->refereeState_ = RefereeState::FAIL;
    rotationRecognizer->HandleTouchUpEvent(event);
    EXPECT_TRUE(rotationRecognizer->lastAxisEvent_.isRotationEvent);

    rotationRecognizer->refereeState_ = RefereeState::READY;
    rotationRecognizer->HandleTouchUpEvent(event);
    EXPECT_TRUE(rotationRecognizer->lastAxisEvent_.isRotationEvent);

    rotationRecognizer->refereeState_ = RefereeState::SUCCEED;
    TimeStamp timeStape = std::chrono::high_resolution_clock::now();
    rotationRecognizer->firstInputTime_ = timeStape;
    SystemProperties::traceInputEventEnable_ = true;
    rotationRecognizer->HandleTouchUpEvent(event);
    EXPECT_TRUE(rotationRecognizer->lastAxisEvent_.isRotationEvent);
}

/**
 * @tc.name: RotationRecognizerPtrHandleTouchUpEventTest002
 * @tc.desc: Test RotationRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerPtrHandleTouchUpEventTest002, TestSize.Level1)
{
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

    rotationRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    rotationRecognizerPtr->currentFingers_ = 2;
    rotationRecognizerPtr->fingers_ = 2;
    rotationRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    rotationRecognizerPtr->angle_ = 0;
    rotationRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizerPtr->lastAngle_, 0.0);
    EXPECT_EQ(rotationRecognizerPtr->angleSignChanged_, false);
}

/**
 * @tc.name: RotationRecognizerPtrHandleTouchUpEventTest003
 * @tc.desc: Test RotationRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerPtrHandleTouchUpEventTest003, TestSize.Level1)
{
    RefPtr<RotationRecognizer> rotationRecognizerPtr =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;};
    targetComponent->SetOnGestureJudgeBegin(gestureJudgeFunc);
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.SetX(-100);
    touchEvent.SetY(200);
    TouchEvent touchEvent2;
    touchEvent2.id = 2;
    touchEvent2.SetX(0);
    touchEvent2.SetY(0);
    rotationRecognizerPtr->targetComponent_ = targetComponent;

    rotationRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    rotationRecognizerPtr->currentFingers_ = 2;
    rotationRecognizerPtr->fingers_ = 2;
    rotationRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    rotationRecognizerPtr->activeFingers_.push_back(touchEvent2.id);
    rotationRecognizerPtr->angle_ = 0;
    rotationRecognizerPtr->lastAngle_ = -10;

    rotationRecognizerPtr->touchPoints_[touchEvent2.id] = touchEvent2;
    rotationRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    rotationRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizerPtr->angleSignChanged_, false);

    rotationRecognizerPtr->initialAngle_ = 1;
    rotationRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    rotationRecognizerPtr->lastAngle_ = -10;
    rotationRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizerPtr->angleSignChanged_, false);

    touchEvent.SetX(100);
    rotationRecognizerPtr->lastAngle_ = 10;
    rotationRecognizerPtr->activeFingers_.clear();
    rotationRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    rotationRecognizerPtr->activeFingers_.push_back(touchEvent2.id);
    rotationRecognizerPtr->touchPoints_.clear();
    rotationRecognizerPtr->touchPoints_[touchEvent2.id] = touchEvent2;
    rotationRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    rotationRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    rotationRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizerPtr->angleSignChanged_, false);
}

/**
 * @tc.name: RotationRecognizerPtrHandleTouchUpEventTest004
 * @tc.desc: Test RotationRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerPtrHandleTouchUpEventTest004, TestSize.Level1)
{
    RefPtr<RotationRecognizer> rotationRecognizerPtr =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;};
    targetComponent->SetOnGestureJudgeBegin(gestureJudgeFunc);
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.SetX(-100);
    touchEvent.SetY(200);
    TouchEvent touchEvent2;
    touchEvent2.id = 2;
    touchEvent2.SetX(0);
    touchEvent2.SetY(0);
    rotationRecognizerPtr->targetComponent_ = targetComponent;

    rotationRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    rotationRecognizerPtr->currentFingers_ = 2;
    rotationRecognizerPtr->fingers_ = 2;
    rotationRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    rotationRecognizerPtr->activeFingers_.push_back(touchEvent2.id);
    rotationRecognizerPtr->angle_ = 0;
    rotationRecognizerPtr->lastAngle_ = 10;

    rotationRecognizerPtr->touchPoints_[touchEvent2.id] = touchEvent2;
    rotationRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    rotationRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizerPtr->angleSignChanged_, false);

    touchEvent.SetX(100);
    rotationRecognizerPtr->lastAngle_ = -10;
    rotationRecognizerPtr->activeFingers_.clear();
    rotationRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    rotationRecognizerPtr->activeFingers_.push_back(touchEvent2.id);
    rotationRecognizerPtr->touchPoints_.clear();
    rotationRecognizerPtr->touchPoints_[touchEvent2.id] = touchEvent2;
    rotationRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    rotationRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    rotationRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizerPtr->angleSignChanged_, false);
}

/**
 * @tc.name: RotationRecognizerPtrHandleTouchUpEventTest005
 * @tc.desc: Test RotationRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerPtrHandleTouchUpEventTest005, TestSize.Level1)
{
    RefPtr<RotationRecognizer> rotationRecognizerPtr =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;};
    targetComponent->SetOnGestureJudgeBegin(gestureJudgeFunc);
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.SetX(-100);
    touchEvent.SetY(200);
    TouchEvent touchEvent2;
    touchEvent2.id = 2;
    touchEvent2.SetX(0);
    touchEvent2.SetY(0);
    rotationRecognizerPtr->targetComponent_ = targetComponent;

    rotationRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizerPtr->currentFingers_ = 2;
    rotationRecognizerPtr->fingers_ = 1;
    rotationRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    rotationRecognizerPtr->activeFingers_.push_back(touchEvent2.id);
    rotationRecognizerPtr->isLimitFingerCount_ = true;
    rotationRecognizerPtr->lastAngle_ = 10;

    rotationRecognizerPtr->touchPoints_[touchEvent2.id] = touchEvent2;
    rotationRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    rotationRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizerPtr->angleSignChanged_, false);

    rotationRecognizerPtr->fingers_ = 2;
    rotationRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizerPtr->angleSignChanged_, false);

    rotationRecognizerPtr->isLimitFingerCount_ = false;
    rotationRecognizerPtr->fingers_ = 1;
    rotationRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizerPtr->angleSignChanged_, false);

    rotationRecognizerPtr->isLimitFingerCount_ = false;
    rotationRecognizerPtr->fingers_ = 2;
    rotationRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizerPtr->angleSignChanged_, false);
}

/**
 * @tc.name: HandleTouchCancelEvent001
 * @tc.desc: Test RotationRecognizer function: HandleTouchCancelEvent
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, HandleTouchCancelEvent001, TestSize.Level1)
{
    int32_t DEFAULT_ROTATION_FINGERS = 2;
    RefPtr<RotationRecognizer> rotationRecognizerPtr =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;};
    targetComponent->SetOnGestureJudgeBegin(gestureJudgeFunc);
    TouchEvent touchEvent;
    rotationRecognizerPtr->targetComponent_ = targetComponent;
    rotationRecognizerPtr->refereeState_ = RefereeState::FAIL;
    rotationRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    rotationRecognizerPtr->activeFingers_.push_back(1);
    rotationRecognizerPtr->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(rotationRecognizerPtr->activeFingers_.size(), DEFAULT_ROTATION_FINGERS);

    rotationRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    rotationRecognizerPtr->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(rotationRecognizerPtr->angleSignChanged_, false);

    rotationRecognizerPtr->refereeState_ = RefereeState::FAIL;
    rotationRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    rotationRecognizerPtr->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(rotationRecognizerPtr->angleSignChanged_, false);
}

/**
 * @tc.name: HandleTouchCancelEvent002
 * @tc.desc: Test RotationRecognizer function: HandleTouchCancelEvent
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, HandleTouchCancelEvent002, TestSize.Level1)
{
    RefPtr<RotationRecognizer> rotationRecognizerPtr =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;};
    targetComponent->SetOnGestureJudgeBegin(gestureJudgeFunc);
    AxisEvent axisEvent;
    rotationRecognizerPtr->targetComponent_ = targetComponent;
    rotationRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    rotationRecognizerPtr->HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(rotationRecognizerPtr->angleSignChanged_, false);
}

/**
 * @tc.name: SendCallbackMsg001
 * @tc.desc: Test RotationRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, SendCallbackMsg001, TestSize.Level1)
{
    RefPtr<RotationRecognizer> rotationRecognizerPtr =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    OHOS::Ace::GestureEventFunc onActionCancel1;
    std::unique_ptr<GestureEventFunc> onActionCancel =  std::make_unique<GestureEventFunc>();
    rotationRecognizerPtr->SetOnActionCancel(onActionCancel1);
    rotationRecognizerPtr->SendCallbackMsg(onActionCancel, GestureCallbackType::CANCEL);
    EXPECT_NE(rotationRecognizerPtr->onActionCancel_, nullptr);

    auto gestureInfo = AceType::MakeRefPtr<GestureInfo>();
    rotationRecognizerPtr->SetGestureInfo(gestureInfo);
    rotationRecognizerPtr->SendCallbackMsg(onActionCancel, GestureCallbackType::CANCEL);
    EXPECT_FALSE(gestureInfo->disposeTag_);

    gestureInfo->SetDisposeTag(true);
    rotationRecognizerPtr->SetGestureInfo(gestureInfo);
    rotationRecognizerPtr->SendCallbackMsg(onActionCancel, GestureCallbackType::CANCEL);
    EXPECT_TRUE(gestureInfo->disposeTag_);
}

/**
 * @tc.name: RotationRecognizerBasicInfoTest001
 * @tc.desc: Test case basic input info check.
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerBasicInfoTest001, TestSize.Level1)
{
    /**
      * @tc.steps: step1. Create basic info testCases.
      * @tc.expected: set rotationRecognizer basic info correct.
      */
    const std::vector<MockRotationRecognizerCase> mockRotationRecognizerCases = {
        {2, 1, RefereeState::READY, 2, 1, RefereeState::READY, {}},
        {2, -1, RefereeState::READY, 2, -1, RefereeState::READY, {}},
        {-1, 1, RefereeState::READY, 2, 1, RefereeState::READY, {}},
    };
    for (auto i = 0; i < mockRotationRecognizerCases.size(); i++) {
        RefPtr<RotationRecognizer> rotationRecognizer = AceType::MakeRefPtr<RotationRecognizer>(mockRotationRecognizerCases[i].fingers, mockRotationRecognizerCases[i].angle);
        rotationRecognizer->refereeState_ = mockRotationRecognizerCases[i].refereeState;
        EXPECT_EQ(rotationRecognizer->angle_, mockRotationRecognizerCases[i].expectedAngle);
        EXPECT_EQ(rotationRecognizer->fingers_, mockRotationRecognizerCases[i].expectedFingers);
        EXPECT_EQ(rotationRecognizer->refereeState_, mockRotationRecognizerCases[i].expectedRefereeState);
    }
}
 
/**
  * @tc.name: RotationRecognizerInjectEventsTest001
  * @tc.desc: Test case inject events.
  * @tc.type: FUNC
  */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerInjectEventsTest001, TestSize.Level1)
{
    /**
      * @tc.steps: step1. Create basic info testCases.
      * @tc.expected: set rotationRecognizer basic info correct.
      */
    TouchEvent downEventFinger0 = TouchEvent();
    downEventFinger0.type = TouchType::DOWN;
    downEventFinger0.id = 0;
     
    TouchEvent moveEventFinger0 = TouchEvent();
    moveEventFinger0.type = TouchType::MOVE;
    moveEventFinger0.id = 0;
     
    TouchEvent upEventFinger0 = TouchEvent();
    upEventFinger0.type = TouchType::UP;
    upEventFinger0.id = 0;
 
    const std::vector<MockRotationRecognizerCase> mockRotationRecognizerCases = {
        {2, 1, RefereeState::READY, 2, 1, RefereeState::READY, {downEventFinger0}},
        {2, -1, RefereeState::READY, 2, -1, RefereeState::READY, {downEventFinger0, moveEventFinger0}},
        {2, 1, RefereeState::READY, 2, 1, RefereeState::FAIL, {downEventFinger0, moveEventFinger0, upEventFinger0}},
    };
    for (auto i = 0; i < mockRotationRecognizerCases.size(); i++) {
        RefPtr<RotationRecognizer> rotationRecognizer = AceType::MakeRefPtr<RotationRecognizer>(mockRotationRecognizerCases[i].fingers, mockRotationRecognizerCases[i].angle);
        rotationRecognizer->refereeState_ = mockRotationRecognizerCases[i].refereeState;
        for (auto j = 0; j < mockRotationRecognizerCases[i].inputTouchEvents.size(); j++) {
            rotationRecognizer->ProcessTouchEvent(mockRotationRecognizerCases[i].inputTouchEvents[j]);
        }
        EXPECT_EQ(rotationRecognizer->angle_, mockRotationRecognizerCases[i].expectedAngle);
        EXPECT_EQ(rotationRecognizer->fingers_, mockRotationRecognizerCases[i].expectedFingers);
        EXPECT_EQ(rotationRecognizer->refereeState_, mockRotationRecognizerCases[i].expectedRefereeState);
    }
}
  
/**
  * @tc.name: RotationRecognizerInjectEventsTest002
  * @tc.desc: Test case inject events.
  * @tc.type: FUNC
  */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerInjectEventsTest002, TestSize.Level1)
{
    /**
      * @tc.steps: step1. Create basic info testCases.
      * @tc.expected: set rotationRecognizer basic info correct.
      */
    TouchEvent downEventFinger0 = TouchEvent();
    TouchEvent downEventFinger1 = TouchEvent();
    downEventFinger0.type = TouchType::DOWN;
    downEventFinger1.type = TouchType::DOWN;
    downEventFinger0.id = 0; 
    downEventFinger1.id = 1;
      
    TouchEvent moveEventFinger0 = TouchEvent();
    TouchEvent moveEventFinger1 = TouchEvent();
    moveEventFinger0.type = TouchType::MOVE;
    moveEventFinger1.type = TouchType::MOVE;
    moveEventFinger0.id = 0;
    moveEventFinger1.id = 1;
  
    TouchEvent upEventFinger0 = TouchEvent();
    TouchEvent upEventFinger1 = TouchEvent();
    upEventFinger0.type = TouchType::UP;
    upEventFinger1.type = TouchType::UP;
    upEventFinger0.id = 0;
    upEventFinger1.id = 1;
  
    const std::vector<MockRotationRecognizerCase> mockRotationRecognizerCases = {
        {2, 1, RefereeState::READY, 2, 1, RefereeState::DETECTING, {downEventFinger0, downEventFinger1}},
        {2, 1, RefereeState::READY, 2, 1, RefereeState::DETECTING,
            {downEventFinger0, downEventFinger1, moveEventFinger0, moveEventFinger1}},
        {2, 1, RefereeState::READY, 2, 1, RefereeState::FAIL,
            {downEventFinger0, downEventFinger1, moveEventFinger0, moveEventFinger1, upEventFinger0, upEventFinger1}},
        {2, -1, RefereeState::READY, 2, -1, RefereeState::SUCCEED,
            {downEventFinger0, downEventFinger1, moveEventFinger0, moveEventFinger1}},
    };
    for (auto i = 0; i < mockRotationRecognizerCases.size(); i++) {
        RefPtr<RotationRecognizer> rotationRecognizer = AceType::MakeRefPtr<RotationRecognizer>(
            mockRotationRecognizerCases[i].fingers, mockRotationRecognizerCases[i].angle);
        rotationRecognizer->refereeState_ = mockRotationRecognizerCases[i].refereeState;
        for (auto j = 0; j < mockRotationRecognizerCases[i].inputTouchEvents.size(); j++) {
            rotationRecognizer->ProcessTouchEvent(mockRotationRecognizerCases[i].inputTouchEvents[j]);
        }
        EXPECT_EQ(rotationRecognizer->angle_, mockRotationRecognizerCases[i].expectedAngle);
        EXPECT_EQ(rotationRecognizer->fingers_, mockRotationRecognizerCases[i].expectedFingers);
        EXPECT_EQ(rotationRecognizer->refereeState_, mockRotationRecognizerCases[i].expectedRefereeState);
    }
}

/**
 * @tc.name: RotationRecognizerTypeTest001
 * @tc.desc: Test RotationRecognizerType
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, RotationRecognizerTypeTest001, TestSize.Level1)
{
    RefPtr<RotationRecognizer> rotationRecognizerPtr =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    rotationRecognizerPtr->AttachFrameNode(frameNode);
    rotationRecognizerPtr->SetRecognizerType(GestureTypeName::ROTATION_GESTURE);
    
    GestureEvent info;
    rotationRecognizerPtr->HandleReports(info, GestureCallbackType::END);
    EXPECT_EQ(rotationRecognizerPtr->GetRecognizerType(), GestureTypeName::ROTATION_GESTURE);
}

/*
 * @tc.name: GetGestureEventInfoTest001
 * @tc.desc: Test GetGestureEventInfo
 * @tc.type: FUNC
 */
HWTEST_F(RotationRecognizerTestNg, GetGestureEventInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<RotationRecognizer> rotationRecognizerPtr =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    rotationRecognizerPtr->AttachFrameNode(frameNode);
    /**
     * @tc.steps: step2. call GetGestureEventInfo function and compare result.
     * @tc.steps: case: touchEvent is not default.
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    axisEvent.sourceTool = SourceTool::MOUSE;
    rotationRecognizerPtr->lastAxisEvent_ = axisEvent;
    rotationRecognizerPtr->inputEventType_ = InputEventType::TOUCH_SCREEN;
    GestureEvent info;
    rotationRecognizerPtr->GetGestureEventInfo(info);
    EXPECT_NE(info.GetSourceTool(), SourceTool::MOUSE);

    rotationRecognizerPtr->inputEventType_ = InputEventType::AXIS;
    rotationRecognizerPtr->GetGestureEventInfo(info);
    EXPECT_EQ(info.GetSourceTool(), SourceTool::MOUSE);
}
} // namespace OHOS::Ace::NG