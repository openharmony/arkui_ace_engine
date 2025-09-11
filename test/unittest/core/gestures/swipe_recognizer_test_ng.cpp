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

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class SwipeRecognizerTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void SwipeRecognizerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void SwipeRecognizerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: SwipeRecognizerTest001
 * @tc.desc: Test SwipeRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer->OnAccepted();
    EXPECT_EQ(swipeRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.expected: step3. result equals.
     */
    swipeRecognizer->OnRejected();
    EXPECT_EQ(swipeRecognizer->refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: SwipeRecognizerTest002
 * @tc.desc: Test SwipeRecognizer function: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchDown function
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    swipeRecognizer->fingers_ = 1;
    swipeRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->lastTouchEvent_.id, touchEvent.id);
    EXPECT_EQ(swipeRecognizer->refereeState_, RefereeState::DETECTING);

    AxisEvent axisEvent;
    swipeRecognizer->HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->axisOffset_.GetX(), 0.0);
    EXPECT_EQ(swipeRecognizer->axisOffset_.GetY(), 0.0);
    EXPECT_EQ(swipeRecognizer->refereeState_, RefereeState::DETECTING);
}

/**
 * @tc.name: SwipeRecognizerTest003
 * @tc.desc: Test SwipeRecognizer function: HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchUp function
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    swipeRecognizer->refereeState_ = RefereeState::FAIL;
    swipeRecognizer->downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(swipeRecognizer->lastTouchEvent_.id, touchEvent.id);

    AxisEvent axisEvent;
    swipeRecognizer->refereeState_ = RefereeState::FAIL;
    swipeRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), axisEvent.x);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetY(), axisEvent.y);
}

/**
 * @tc.name: SwipeRecognizerHandleTouchUpEventTest001
 * @tc.desc: Test SwipeRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerHandleTouchUpEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    swipeRecognizer->refereeState_ = RefereeState::FAIL;
    swipeRecognizer->downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer->currentFingers_ = swipeRecognizer->fingers_;
    swipeRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(swipeRecognizer->lastTouchEvent_.id, touchEvent.id);

    swipeRecognizer->refereeState_ = RefereeState::FAIL;
    swipeRecognizer->downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer->currentFingers_ = swipeRecognizer->fingers_;
    swipeRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(swipeRecognizer->lastTouchEvent_.id, touchEvent.id);
}

/**
 * @tc.name: SwipeRecognizerHandleTouchUpEventTest002
 * @tc.desc: Test SwipeRecognizer function: HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerHandleTouchUpEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchUp function
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    swipeRecognizer->refereeState_ = RefereeState::FAIL;
    swipeRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), axisEvent.x);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetY(), axisEvent.y);

    swipeRecognizer->refereeState_ = RefereeState::FAIL;
    swipeRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), axisEvent.x);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetY(), axisEvent.y);
}

/**
 * @tc.name: SwipeRecognizerHandleTouchCancelEventTest001
 * @tc.desc: Test SwipeRecognizer function: HandleTouchCancelEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerHandleTouchCancelEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchUp function
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    swipeRecognizer->refereeState_ = RefereeState::FAIL;
    swipeRecognizer->HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), axisEvent.x);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetY(), axisEvent.y);
}

/**
 * @tc.name: SwipeRecognizerSendCallbackMsgTest001
 * @tc.desc: Test SwipeRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerSendCallbackMsgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case1: onAction is no, *onAction is no
     * @tc.expected: step2. result equals.
     */
    std::unique_ptr<GestureEventFunc> onAction;
    swipeRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(swipeRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case2: onAction is yes, *onAction is no
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>();
    swipeRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(swipeRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    swipeRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(swipeRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    swipeRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    swipeRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(swipeRecognizer->touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    touchEvent.tiltX = 0.0f;
    touchEvent.tiltY = 0.0f;
    swipeRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    swipeRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(swipeRecognizer->touchPoints_.size(), 1);
}

/**
 * @tc.name: SwipeRecognizerSendCallbackMsgTest002
 * @tc.desc: Test SwipeRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerSendCallbackMsgTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);
    std::unique_ptr<GestureEventFunc> onAction;

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    swipeRecognizer->deviceType_ = SourceType::MOUSE;
    swipeRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(swipeRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    swipeRecognizer->prevAngle_ = std::make_optional(VERTICAL_ANGLE);
    swipeRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    swipeRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(swipeRecognizer->touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    touchEvent.tiltX = 0.0f;
    touchEvent.tiltY = 0.0f;
    TouchEvent touchEvent1;
    swipeRecognizer->deviceType_ = SourceType::MOUSE;
    swipeRecognizer->lastTouchEvent_ = touchEvent1;
    swipeRecognizer->lastTouchEvent_.tiltX = std::make_optional(0.0f);
    swipeRecognizer->lastTouchEvent_.tiltY = std::make_optional(0.0f);
    swipeRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    swipeRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(swipeRecognizer->touchPoints_.size(), 1);
}

/**
 * @tc.name: SwipeRecognizerHandleTouchMoveEventTest001
 * @tc.desc: Test SwipeRecognizer function: HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerHandleTouchMoveEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchMove function
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    swipeRecognizer->refereeState_ = RefereeState::FAIL;
    swipeRecognizer->currentFingers_ = swipeRecognizer->fingers_;
    swipeRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->axisOffset_.GetX(), 0);
    EXPECT_EQ(swipeRecognizer->axisOffset_.GetY(), 0);
}

/**
 * @tc.name: SwipeRecognizerTest004
 * @tc.desc: Test SwipeRecognizer function: HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchMove function
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    touchEvent.x = 0;
    touchEvent.y = 1;
    swipeRecognizer->refereeState_ = RefereeState::FAIL;
    swipeRecognizer->downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetY(), 0);
    EXPECT_EQ(swipeRecognizer->lastTouchEvent_.id, touchEvent.id);

    swipeRecognizer->refereeState_ = RefereeState::DETECTING;
    swipeRecognizer->downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetY(), 0);
    EXPECT_EQ(swipeRecognizer->lastTouchEvent_.id, touchEvent.id);

    AxisEvent axisEvent;
    swipeRecognizer->refereeState_ = RefereeState::DETECTING;
    swipeRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), axisEvent.x);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetY(), axisEvent.y);
    EXPECT_EQ(swipeRecognizer->axisOffset_.GetX(), 0);
    EXPECT_EQ(swipeRecognizer->axisOffset_.GetY(), 0);
}

/**
 * @tc.name: SwipeRecognizerTest005
 * @tc.desc: Test SwipeRecognizer function: CheckAngle
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call CheckAngle function
     * @tc.steps: case1: prevAngle has value, prevAngle - angle > 45
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer->prevAngle_ = std::make_optional(VERTICAL_ANGLE);
    auto result = swipeRecognizer->CheckAngle(0);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call CheckAngle function
     * @tc.steps: case2: prevAngle has value, prevAngle - angle < 45
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer->prevAngle_ = std::make_optional(VERTICAL_ANGLE);
    result = swipeRecognizer->CheckAngle(VERTICAL_ANGLE);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call CheckAngle function
     * @tc.steps: case2: prevAngle has no value, direction is HORIZONTAL, angle > 45
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer->prevAngle_ = std::optional<double>();
    swipeRecognizer->direction_.type = SwipeDirection::HORIZONTAL;
    result = swipeRecognizer->CheckAngle(VERTICAL_ANGLE);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call CheckAngle function
     * @tc.steps: case3: prevAngle has no value, direction is HORIZONTAL, angle < 45
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer->prevAngle_ = std::optional<double>();
    swipeRecognizer->direction_.type = SwipeDirection::HORIZONTAL;
    result = swipeRecognizer->CheckAngle(0);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call CheckAngle function
     * @tc.steps: case4: prevAngle has no value, direction is VERTICAL, angle > 135
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer->prevAngle_ = std::make_optional(VERTICAL_ANGLE);
    swipeRecognizer->direction_.type = SwipeDirection::VERTICAL;
    result = swipeRecognizer->CheckAngle(HORIZONTAL_ANGLE);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call CheckAngle function
     * @tc.steps: case5: prevAngle has no value, direction is VERTICAL, angle < 135
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer->prevAngle_ = std::make_optional(VERTICAL_ANGLE);
    swipeRecognizer->direction_.type = SwipeDirection::VERTICAL;
    result = swipeRecognizer->CheckAngle(VERTICAL_ANGLE);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: SwipeRecognizerHandleTouchMoveEventTest002
 * @tc.desc: Test SwipeRecognizer function: HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerHandleTouchMoveEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchMove function
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    touchEvent.x = 0;
    touchEvent.y = 1;
    swipeRecognizer->refereeState_ = RefereeState::FAIL;
    swipeRecognizer->downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer->currentFingers_ = swipeRecognizer->fingers_;
    swipeRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetY(), 0);
    EXPECT_EQ(swipeRecognizer->lastTouchEvent_.id, touchEvent.id);

    swipeRecognizer->refereeState_ = RefereeState::DETECTING;
    swipeRecognizer->downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer->currentFingers_ = swipeRecognizer->fingers_;
    swipeRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->lastTouchEvent_.id, touchEvent.id);

    AxisEvent axisEvent;
    swipeRecognizer->refereeState_ = RefereeState::FAIL;
    swipeRecognizer->currentFingers_ = swipeRecognizer->fingers_;
    swipeRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->axisOffset_.GetX(), 0);
    EXPECT_EQ(swipeRecognizer->axisOffset_.GetY(), 0);
}

/**
 * @tc.name: SwipeRecognizerHandleTouchMoveEventTest003
 * @tc.desc: Test SwipeRecognizer function: HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerHandleTouchMoveEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchMove function
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    touchEvent.x = 0;
    touchEvent.y = -1;
    swipeRecognizer->refereeState_ = RefereeState::FAIL;
    swipeRecognizer->downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer->currentFingers_ = swipeRecognizer->fingers_;
    swipeRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetY(), 0);
    EXPECT_EQ(swipeRecognizer->lastTouchEvent_.id, touchEvent.id);

    swipeRecognizer->refereeState_ = RefereeState::DETECTING;
    swipeRecognizer->downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer->currentFingers_ = swipeRecognizer->fingers_;
    swipeRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->lastTouchEvent_.id, touchEvent.id);

    AxisEvent axisEvent;
    swipeRecognizer->refereeState_ = RefereeState::FAIL;
    swipeRecognizer->currentFingers_ = swipeRecognizer->fingers_;
    swipeRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->axisOffset_.GetX(), 0);
    EXPECT_EQ(swipeRecognizer->axisOffset_.GetY(), 0);
}

/**
 * @tc.name: SwipeRecognizerHandleTouchMoveEventTest004
 * @tc.desc: Test SwipeRecognizer function: HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerHandleTouchMoveEventTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchMove function
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    touchEvent.x = -1;
    touchEvent.y = -1;
    swipeRecognizer->refereeState_ = RefereeState::FAIL;
    swipeRecognizer->downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer->currentFingers_ = swipeRecognizer->fingers_;
    swipeRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->lastTouchEvent_.id, touchEvent.id);

    swipeRecognizer->refereeState_ = RefereeState::DETECTING;
    swipeRecognizer->downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer->currentFingers_ = swipeRecognizer->fingers_;
    swipeRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->lastTouchEvent_.id, touchEvent.id);

    AxisEvent axisEvent;
    swipeRecognizer->refereeState_ = RefereeState::FAIL;
    swipeRecognizer->currentFingers_ = swipeRecognizer->fingers_;
    swipeRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->axisOffset_.GetX(), 0);
    EXPECT_EQ(swipeRecognizer->axisOffset_.GetY(), 0);
}

/**
 * @tc.name: SwipeRecognizerTest006
 * @tc.desc: Test SwipeRecognizer function: OnResetStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call OnResetStatus function
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer->OnResetStatus();
    EXPECT_EQ(swipeRecognizer->axisOffset_.GetX(), 0.0);
    EXPECT_EQ(swipeRecognizer->axisOffset_.GetY(), 0.0);
    EXPECT_EQ(swipeRecognizer->resultSpeed_, 0.0);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0.0);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetY(), 0.0);
}

/**
 * @tc.name: SwipeRecognizerTest007
 * @tc.desc: Test SwipeRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);
    RefPtr<SwipeRecognizer> swipeRecognizerPtr =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case1: input is nullptr
     * @tc.expected: step2. result equals.
     */
    auto result = swipeRecognizer->ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case2: input is same
     * @tc.expected: step2. result equals.
     */
    result = swipeRecognizer->ReconcileFrom(swipeRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case3: curr->fingers != fingers
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer->fingers_ = swipeRecognizerPtr->fingers_ + 1;
    result = swipeRecognizer->ReconcileFrom(swipeRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case4: curr->fingers = fingers, direction type not same
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer->fingers_ = swipeRecognizerPtr->fingers_;
    swipeRecognizer->direction_.type = SwipeDirection::HORIZONTAL;
    result = swipeRecognizer->ReconcileFrom(swipeRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case5:direction type is same, speed is not same
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer->fingers_ = swipeRecognizerPtr->fingers_;
    swipeRecognizer->direction_.type = swipeRecognizerPtr->direction_.type;
    swipeRecognizer->speed_ = Dimension(1, DimensionUnit::PX);
    result = swipeRecognizer->ReconcileFrom(swipeRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: SwipeRecognizerTest008
 * @tc.desc: Test SwipeRecognizer function: HandleTouchCancelEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchCancelEvent function
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer->refereeState_ = RefereeState::SUCCEED;
    TouchEvent touchEvent;
    swipeRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: SwipeRecognizerTest009
 * @tc.desc: Test SwipeRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case1: callback is null
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer->SendCallbackMsg(nullptr, GestureCallbackType::ACTION);
    EXPECT_EQ(swipeRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case2: callback is ptr, have no tiltX and tileY
     * @tc.expected: step2. result equals.
     */
    std::unique_ptr<GestureEventFunc> onAction;
    TouchEvent touchEvent1;
    swipeRecognizer->deviceType_ = SourceType::MOUSE;
    swipeRecognizer->lastTouchEvent_ = touchEvent1;
    swipeRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(swipeRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: callback is ptr, have tiltX and no tileY
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent2;
    touchEvent2.tiltX = 0;
    swipeRecognizer->deviceType_ = SourceType::TOUCH;
    swipeRecognizer->lastTouchEvent_ = touchEvent2;
    swipeRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(swipeRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: callback is ptr, have tiltX and tileY
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent3;
    touchEvent3.tiltX = 0;
    touchEvent3.tiltY = 0;
    swipeRecognizer->deviceType_ = SourceType::TOUCH;
    swipeRecognizer->lastTouchEvent_ = touchEvent3;
    swipeRecognizer->prevAngle_ = std::make_optional(0);
    swipeRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(swipeRecognizer->touchPoints_.size(), 0);
}

/**
 * @tc.name: SwipeRecognizerTest010
 * @tc.desc: Test SwipeRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER,
        swipeDirection, SWIPE_SPEED);
    ASSERT_NE(swipeRecognizer, nullptr);
    /**
     * @tc.steps: step3. test with HandleTouchDownEvent(AxisEvent).
     * @tc.expect: swipeRecognizer->lastAxisEvent_ is equal to axisEvent
     * @tc.expect: swipeRecognizer->touchPoints_[axisEvent.id].originalId is equal to axisEvent.originalId
     * @tc.expect: swipeRecognizer->touchPoints_[axisEvent.id].screenX is equal to axisEvent.screenX
     * @tc.expect: swipeRecognizer->touchPoints_[axisEvent.id].screenY is equal to axisEvent.screenY
     */
    AxisEvent axisEvent;
    axisEvent.id = TEST_EVENT_ID;
    axisEvent.originalId = TEST_EVENT_ID;

    swipeRecognizer->refereeState_ = RefereeState::SUCCEED;
    swipeRecognizer->fingers_ = FINGER_NUMBER;
    swipeRecognizer->direction_.type = SwipeDirection::HORIZONTAL;
    swipeRecognizer->HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->lastAxisEvent_.id, axisEvent.id);
    EXPECT_EQ(swipeRecognizer->touchPoints_[axisEvent.id].originalId, axisEvent.originalId);
    EXPECT_EQ(swipeRecognizer->touchPoints_[axisEvent.id].screenX, axisEvent.screenX);
    EXPECT_EQ(swipeRecognizer->touchPoints_[axisEvent.id].screenY, axisEvent.screenY);
}

/**
 * @tc.name: SwipeRecognizerTest011
 * @tc.desc: Test SwipeRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER,
        swipeDirection, SWIPE_SPEED);
    ASSERT_NE(swipeRecognizer, nullptr);

    /**
     * @tc.steps: step3. test with HandleTouchUpEvent(AxisEvent).
     * @tc.expect: swipeRecognizer->lastAxisEvent_ is equal to axisEvent
     */
    AxisEvent axisEvent;
    axisEvent.id = TEST_EVENT_ID;
    swipeRecognizer->refereeState_ = RefereeState::SUCCEED;
    swipeRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->lastAxisEvent_.id, axisEvent.id);
}

/**
 * @tc.name: SwipeGestureTest001
 * @tc.desc: Test SwipeGesture CreateRecognizer function
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeGestureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeGesture.
     */
    int32_t fingersNum = DEFAULT_PAN_FINGER;
    double speedNum = DEFAULT_SLIDE_SPEED;
    SwipeDirection slideDirection;
    SwipeGestureModelNG swipeGestureModelNG;
    swipeGestureModelNG.Create(fingersNum, slideDirection, Dimension(speedNum, DimensionUnit::PX));

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto swipeGestureNG = AceType::DynamicCast<NG::SwipeRecognizer>(gestureProcessor->TopGestureNG());

    SwipeGesture swipeGesture = SwipeGesture(fingersNum, slideDirection, Dimension(speedNum, DimensionUnit::PX));
    EXPECT_EQ(swipeGesture.speed_, Dimension(DEFAULT_SLIDE_SPEED, DimensionUnit::PX));

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     */
    auto swipeRecognizer = AceType::DynamicCast<SwipeRecognizer>(swipeGesture.CreateRecognizer());
    EXPECT_EQ(swipeGesture.speed_, Dimension(DEFAULT_SLIDE_SPEED, DimensionUnit::PX));

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case2: onActionId, onActionEndId, onActionCancelId existed
     */
    std::unique_ptr<GestureEventFunc> onActionId;
    std::unique_ptr<GestureEventFunc> onActionEndId;
    std::unique_ptr<GestureEventFunc> onActionCancelId;
    swipeGesture.onActionId_ = std::move(onActionId);
    swipeGesture.onActionEndId_ = std::move(onActionEndId);
    swipeGesture.onActionCancelId_ = std::move(onActionCancelId);
    swipeRecognizer = AceType::DynamicCast<SwipeRecognizer>(swipeGesture.CreateRecognizer());
    EXPECT_EQ(swipeGesture.speed_, Dimension(DEFAULT_SLIDE_SPEED, DimensionUnit::PX));
}

/**
 * @tc.name: SwipeGestureCreateRecognizerTest001
 * @tc.desc: Test SwipeGesture CreateRecognizer function
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeGestureCreateRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeGesture.
     */
    int32_t fingersNum = DEFAULT_PAN_FINGER;
    double speedNum = DEFAULT_SLIDE_SPEED;
    SwipeDirection slideDirection;
    SwipeGestureModelNG swipeGestureModelNG;
    swipeGestureModelNG.Create(fingersNum, slideDirection, Dimension(speedNum, DimensionUnit::PX));

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto swipeGestureNG = AceType::DynamicCast<NG::SwipeRecognizer>(gestureProcessor->TopGestureNG());

    SwipeGesture swipeGesture = SwipeGesture(fingersNum, slideDirection, Dimension(speedNum, DimensionUnit::PX));
    EXPECT_EQ(swipeGesture.speed_, Dimension(DEFAULT_SLIDE_SPEED, DimensionUnit::PX));

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     */
    auto swipeRecognizer = AceType::DynamicCast<SwipeRecognizer>(swipeGesture.CreateRecognizer());
    EXPECT_EQ(swipeGesture.speed_, Dimension(DEFAULT_SLIDE_SPEED, DimensionUnit::PX));

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case2: onActionId, onActionEndId, onActionCancelId existed
     */
    std::unique_ptr<GestureEventFunc> onActionId;
    std::unique_ptr<GestureEventFunc> onActionEndId;
    std::unique_ptr<GestureEventFunc> onActionCancelId;
    swipeGesture.onActionId_ = std::move(onActionId);
    swipeGesture.onActionEndId_ = std::move(onActionEndId);
    swipeGesture.onActionCancelId_ = std::move(onActionCancelId);
    auto onActionStart = [](GestureEvent& info) { return true; };
    swipeGesture.SetOnActionId(onActionStart);
    swipeRecognizer = AceType::DynamicCast<SwipeRecognizer>(swipeGesture.CreateRecognizer());
    EXPECT_EQ(swipeGesture.speed_, Dimension(DEFAULT_SLIDE_SPEED, DimensionUnit::PX));
}

/**
 * @tc.name: SwipeRecognizerHandleTouchDownEventTest001
 * @tc.desc: Test SwipeRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerHandleTouchDownEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER,
        swipeDirection, SWIPE_SPEED);
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;
    touchEvent.sourceType = SourceType::MOUSE;

    swipeRecognizer->refereeState_ = RefereeState::DETECTING;
    swipeRecognizer->fingers_ = 11;
    swipeRecognizer->direction_.type = SwipeDirection::NONE;
    swipeRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);

    swipeRecognizer->refereeState_ = RefereeState::DETECTING;
    swipeRecognizer->fingers_ = FINGER_NUMBER;
    swipeRecognizer->direction_.type = SwipeDirection::NONE;
    swipeRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);
}

/**
 * @tc.name: SwipeRecognizerHandleTouchDownEventTest002
 * @tc.desc: Test SwipeRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerHandleTouchDownEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER,
        swipeDirection, SWIPE_SPEED);
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;
    touchEvent.sourceType = SourceType::MOUSE;

    AxisEvent axisEvent;
    swipeRecognizer->refereeState_ = RefereeState::DETECTING;
    swipeRecognizer->fingers_ = 11;
    swipeRecognizer->direction_.type = SwipeDirection::NONE;
    swipeRecognizer->HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);

    swipeRecognizer->refereeState_ = RefereeState::DETECTING;
    swipeRecognizer->fingers_ = FINGER_NUMBER;
    swipeRecognizer->direction_.type = SwipeDirection::NONE;
    swipeRecognizer->HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);
}

/**
 * @tc.name: SwipeRecognizerHandleTouchUpEventTest003
 * @tc.desc: Test SwipeRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerHandleTouchUpEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER,
        swipeDirection, SWIPE_SPEED);
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;
    touchEvent.sourceType = SourceType::MOUSE;

    swipeRecognizer->refereeState_ = RefereeState::SUCCEED;
    swipeRecognizer->fingers_ = 11;
    swipeRecognizer->direction_.type = SwipeDirection::NONE;
    swipeRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);
}


/**
 * @tc.name: SwipeRecognizerHandleTouchUpEventTest006
 * @tc.desc: Test SwipeRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerHandleTouchUpEventTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER,
        swipeDirection, SWIPE_SPEED);
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;
    touchEvent.sourceType = SourceType::MOUSE;
    swipeRecognizer->OnResetStatus();
    touchEvent.time = swipeRecognizer->touchDownTime_;

    swipeRecognizer->refereeState_ = RefereeState::SUCCEED;
    swipeRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), touchEvent.x);

    swipeRecognizer->refereeState_ = RefereeState::DETECTING;
    swipeRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), touchEvent.x);

    swipeRecognizer->refereeState_ = RefereeState::READY;
    swipeRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), touchEvent.x);

    swipeRecognizer->refereeState_ = RefereeState::PENDING;
    swipeRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), touchEvent.x);

    swipeRecognizer->refereeState_ = RefereeState::PENDING_BLOCKED;
    swipeRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), touchEvent.x);

    swipeRecognizer->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    swipeRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), touchEvent.x);

    swipeRecognizer->refereeState_ = RefereeState::FAIL;
    swipeRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), touchEvent.x);
}

/**
 * @tc.name: SwipeRecognizerHandleTouchUpEventTest005
 * @tc.desc: Test SwipeRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerHandleTouchUpEventTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER,
        swipeDirection, SWIPE_SPEED);
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;
    touchEvent.sourceType = SourceType::MOUSE;

    AxisEvent axisEvent;
    swipeRecognizer->refereeState_ = RefereeState::SUCCEED;
    swipeRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);

    swipeRecognizer->refereeState_ = RefereeState::DETECTING;
    swipeRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);

    swipeRecognizer->refereeState_ = RefereeState::READY;
    swipeRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);

    swipeRecognizer->refereeState_ = RefereeState::PENDING;
    swipeRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);

    swipeRecognizer->refereeState_ = RefereeState::PENDING_BLOCKED;
    swipeRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);

    swipeRecognizer->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    swipeRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);

    swipeRecognizer->refereeState_ = RefereeState::FAIL;
    swipeRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);
}

/**
 * @tc.name: SwipeRecognizerHandleTouchCancelEventTest005
 * @tc.desc: Test SwipeRecognizer function: HandleTouchCancelEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerHandleTouchCancelEventTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizer =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER,
        swipeDirection, SWIPE_SPEED);
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;
    touchEvent.sourceType = SourceType::MOUSE;

    swipeRecognizer->refereeState_ = RefereeState::SUCCEED;
    swipeRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);

    swipeRecognizer->refereeState_ = RefereeState::DETECTING;
    swipeRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);

    swipeRecognizer->refereeState_ = RefereeState::READY;
    swipeRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);

    swipeRecognizer->refereeState_ = RefereeState::PENDING;
    swipeRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);

    swipeRecognizer->refereeState_ = RefereeState::PENDING_BLOCKED;
    swipeRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);

    swipeRecognizer->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    swipeRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);

    swipeRecognizer->refereeState_ = RefereeState::FAIL;
    swipeRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer->globalPoint_.GetX(), 0);
}

/**
 * @tc.name: SwipeRecognizerPtrHandleTouchUpEventTest001
 * @tc.desc: Test SwipeRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerPtrHandleTouchUpEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and set Recognizer、TargetComponent.
     */
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizerPtr =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    DimensionRect area;
    DimensionOffset origin;
    EventTarget target = {"", "", area, origin};
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;};
    targetComponent->SetOnGestureJudgeBegin(gestureJudgeFunc);
    TouchEvent touchEvent;
    AxisEvent axisEvent;
    touchEvent.tiltX.emplace(1.0f);
    touchEvent.tiltY.emplace(1.0f);
    swipeRecognizerPtr->targetComponent_ = targetComponent;
    /**
     * @tc.steps: step2. test the function who calls TriggerGestureJudgeCallback.
     * @tc.expected: step2. result equals REJECT.
     */
    swipeRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    swipeRecognizerPtr->speed_ = Dimension(-1, DimensionUnit::PX);
    swipeRecognizerPtr->fingers_ = 1;
    swipeRecognizerPtr->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(swipeRecognizerPtr->disposal_, GestureDisposal::REJECT);

    swipeRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    swipeRecognizerPtr->deviceType_ = SourceType::MOUSE;
    swipeRecognizerPtr->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(swipeRecognizerPtr->disposal_, GestureDisposal::REJECT);
}

/**
 * @tc.name: SwipeGestureLimitFingerTest001
 * @tc.desc: Test SwipeGesture CreateRecognizer function
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeGestureLimitFingerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeGestureGesture.
     */
    int32_t fingersNum = DEFAULT_PAN_FINGER;
    double speedNum = DEFAULT_SLIDE_SPEED;
    SwipeDirection slideDirection;
    SwipeGestureModelNG swipeGestureModelNG;
    swipeGestureModelNG.Create(
        fingersNum, slideDirection, Dimension(speedNum, DimensionUnit::PX), IS_LIMIT_FINGER_COUNT);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto swipeGestureNG = AceType::DynamicCast<NG::SwipeGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(swipeGestureNG->isLimitFingerCount_, IS_LIMIT_FINGER_COUNT);
    

    SwipeGesture swipeGesture = SwipeGesture(
        fingersNum, slideDirection, Dimension(speedNum, DimensionUnit::PX), IS_LIMIT_FINGER_COUNT);
    EXPECT_EQ(swipeGesture.speed_, Dimension(DEFAULT_SLIDE_SPEED, DimensionUnit::PX));
    EXPECT_EQ(swipeGesture.isLimitFingerCount_, IS_LIMIT_FINGER_COUNT);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: functions are not existed
     */
    swipeGesture.priority_ = GesturePriority::Low;
    swipeGesture.gestureMask_ = GestureMask::Normal;
    auto swipeRecognizer = AceType::DynamicCast<SwipeRecognizer>(swipeGesture.CreateRecognizer());
    EXPECT_NE(swipeRecognizer, nullptr);
    EXPECT_EQ(swipeRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(swipeRecognizer->GetPriorityMask(), GestureMask::Normal);
    EXPECT_EQ(swipeRecognizer->isLimitFingerCount_, IS_LIMIT_FINGER_COUNT);

    // /**
    //  * @tc.steps: step2. call CreateRecognizer function and compare result
    //  * @tc.steps: case2: functions are existed
    //  */
    std::unique_ptr<GestureEventFunc> onActionStartId;
    std::unique_ptr<GestureEventFunc> onActionUpdateId;
    std::unique_ptr<GestureEventFunc> onActionEndId;
    std::unique_ptr<GestureEventFunc> onActionCancelId;
    swipeGesture.onActionStartId_ = std::move(onActionStartId);
    swipeGesture.onActionUpdateId_ = std::move(onActionUpdateId);
    swipeGesture.onActionEndId_ = std::move(onActionEndId);
    swipeGesture.onActionCancelId_ = std::move(onActionCancelId);
    swipeRecognizer = AceType::DynamicCast<SwipeRecognizer>(swipeGesture.CreateRecognizer());
    EXPECT_EQ(swipeRecognizer->priority_, swipeGesture.priority_);
    EXPECT_EQ(swipeRecognizer->priorityMask_, swipeGesture.gestureMask_);
    EXPECT_EQ(swipeRecognizer->isLimitFingerCount_, IS_LIMIT_FINGER_COUNT);
}

/**
 * @tc.name: SwipeGestureLimitFingerTest002
 * @tc.desc: Test SwipeGesture CreateRecognizer function
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeGestureLimitFingerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeGestureGesture.
     */
    int32_t fingersNum = DEFAULT_PAN_FINGER;
    double speedNum = DEFAULT_SLIDE_SPEED;
    SwipeDirection slideDirection;
    SwipeGestureModelNG swipeGestureModelNG;
    swipeGestureModelNG.Create(
        fingersNum, slideDirection, Dimension(speedNum, DimensionUnit::PX), IS_NOT_LIMIT_FINGER_COUNT);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto swipeGestureNG = AceType::DynamicCast<NG::SwipeGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(swipeGestureNG->isLimitFingerCount_, IS_NOT_LIMIT_FINGER_COUNT);
    

    SwipeGesture swipeGesture = SwipeGesture(
        fingersNum, slideDirection, Dimension(speedNum, DimensionUnit::PX), IS_NOT_LIMIT_FINGER_COUNT);
    EXPECT_EQ(swipeGesture.speed_, Dimension(DEFAULT_SLIDE_SPEED, DimensionUnit::PX));
    EXPECT_EQ(swipeGesture.isLimitFingerCount_, IS_NOT_LIMIT_FINGER_COUNT);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: functions are not existed
     */
    swipeGesture.priority_ = GesturePriority::Low;
    swipeGesture.gestureMask_ = GestureMask::Normal;
    auto swipeRecognizer = AceType::DynamicCast<SwipeRecognizer>(swipeGesture.CreateRecognizer());
    EXPECT_NE(swipeRecognizer, nullptr);
    EXPECT_EQ(swipeRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(swipeRecognizer->GetPriorityMask(), GestureMask::Normal);
    EXPECT_EQ(swipeRecognizer->isLimitFingerCount_, IS_NOT_LIMIT_FINGER_COUNT);

    // /**
    //  * @tc.steps: step2. call CreateRecognizer function and compare result
    //  * @tc.steps: case2: functions are existed
    //  */
    std::unique_ptr<GestureEventFunc> onActionStartId;
    std::unique_ptr<GestureEventFunc> onActionUpdateId;
    std::unique_ptr<GestureEventFunc> onActionEndId;
    std::unique_ptr<GestureEventFunc> onActionCancelId;
    swipeGesture.onActionStartId_ = std::move(onActionStartId);
    swipeGesture.onActionUpdateId_ = std::move(onActionUpdateId);
    swipeGesture.onActionEndId_ = std::move(onActionEndId);
    swipeGesture.onActionCancelId_ = std::move(onActionCancelId);
    swipeRecognizer = AceType::DynamicCast<SwipeRecognizer>(swipeGesture.CreateRecognizer());
    EXPECT_EQ(swipeRecognizer->priority_, swipeGesture.priority_);
    EXPECT_EQ(swipeRecognizer->priorityMask_, swipeGesture.gestureMask_);
    EXPECT_EQ(swipeRecognizer->isLimitFingerCount_, IS_NOT_LIMIT_FINGER_COUNT);
}
/**
 * @tc.name: SwipeRecognizerTypeTest001
 * @tc.desc: Test SwipeRecognizerType
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerTestNg, SwipeRecognizerTypeTest001, TestSize.Level1)
{
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizerPtr =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    swipeRecognizerPtr->AttachFrameNode(frameNode);
    swipeRecognizerPtr->SetRecognizerType(GestureTypeName::SWIPE_GESTURE);
    
    GestureEvent info;
    swipeRecognizerPtr->HandleReports(info, GestureCallbackType::END);
    EXPECT_EQ(swipeRecognizerPtr->GetRecognizerType(), GestureTypeName::SWIPE_GESTURE);
}
} // namespace OHOS::Ace::NG