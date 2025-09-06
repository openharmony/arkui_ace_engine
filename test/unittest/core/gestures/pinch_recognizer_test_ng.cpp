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
constexpr float GESTURE_EVENT_PROPERTY_DEFAULT_VALUE = 0.0;
constexpr float GESTURE_EVENT_PROPERTY_VALUE = 10.0;
class PinchRecognizerTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void PinchRecognizerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void PinchRecognizerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void funtest(GestureEvent& info) {}

/**
 * @tc.name: PinchRecognizerTest001
 * @tc.desc: Test PinchRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->OnAccepted();
    EXPECT_EQ(pinchRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.expected: step3. result equals.
     */
    pinchRecognizer->OnRejected();
    EXPECT_EQ(pinchRecognizer->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: PinchRecognizerTest002
 * @tc.desc: Test PinchRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: input is TouchEvent. refereeState_ is SUCCESS.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(static_cast<int32_t>(pinchRecognizer->touchPoints_.size()), 1);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: input is TouchEvent. refereeState_ is PENDING.
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::PENDING;
    pinchRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: input is TouchEvent. refereeState_ is PENDING. fingers_ > size
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::PENDING;
    pinchRecognizer->fingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(static_cast<int32_t>(pinchRecognizer->touchPoints_.size()), 1);
    EXPECT_EQ(pinchRecognizer->refereeState_, RefereeState::PENDING);
}

/**
 * @tc.name: PinchRecognizerHandleTouchDownEventTest001
 * @tc.desc: Test PinchRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerHandleTouchDownEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: input is TouchEvent. refereeState_ is SUCCESS.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->fingers_ = 0;
    pinchRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(static_cast<int32_t>(pinchRecognizer->touchPoints_.size()), 1);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: input is TouchEvent. refereeState_ is PENDING.
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::PENDING;
    pinchRecognizer->fingers_ = 0;
    pinchRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: input is TouchEvent. refereeState_ is PENDING. fingers_ > size
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::PENDING;
    pinchRecognizer->fingers_ = 0;
    pinchRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(static_cast<int32_t>(pinchRecognizer->touchPoints_.size()), 1);
    EXPECT_EQ(pinchRecognizer->refereeState_, RefereeState::PENDING);
}

/**
 * @tc.name: PinchRecognizerTest003
 * @tc.desc: Test PinchRecognizer function: HandleMove HandleUp HandleCancel
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    auto pinchRecognizer = AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case1: input is TouchEvent
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->HandleTouchMoveEvent(touchEvent);
    pinchRecognizer->HandleTouchUpEvent(touchEvent);
    pinchRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case2: input is AxisEvent
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case3: input is TouchEvent, isFlushTouchEventsEnd_
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->isFlushTouchEventsEnd_ = true;
    pinchRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case4: input is TouchEvent, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::FAIL;
    pinchRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case5: input is AxisEvent
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::FAIL;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchCancelEvent function and compare result.
     * @tc.steps: case6: input is TouchEvent, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::FAIL;
    pinchRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);
}

/**
 * @tc.name: PinchRecognizerTest004
 * @tc.desc: Test PinchRecognizer function: OnFlushTouchEvent begin end
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. call OnFlushTouchEvent function and compare result.
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->OnFlushTouchEventsBegin();
    EXPECT_EQ(pinchRecognizer->isFlushTouchEventsEnd_, false);
    pinchRecognizer->OnFlushTouchEventsEnd();
    EXPECT_EQ(pinchRecognizer->isFlushTouchEventsEnd_, true);
}

/**
 * @tc.name: PinchRecognizerTest005
 * @tc.desc: Test PinchRecognizer function: ComputeAverageDeviation
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. call ComputeAverageDeviation function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    auto result = pinchRecognizer->ComputeAverageDeviation();
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: PinchRecognizerComputePinchCenterTest001
 * @tc.desc: Test PinchRecognizer function: ComputePinchCenter
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerComputePinchCenterTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. call ComputePinchCenter function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    auto result = pinchRecognizer->ComputePinchCenter();
    pinchRecognizer->OnFlushTouchEventsEnd();
    EXPECT_EQ(pinchRecognizer->isFlushTouchEventsEnd_, true);
}

/**
 * @tc.name: PinchRecognizerTest006
 * @tc.desc: Test PinchRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case1: onAction is no, *onAction is no
     * @tc.expected: step2. result equals.
     */
    std::unique_ptr<GestureEventFunc> onAction;
    pinchRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(pinchRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case2: onAction is yes, *onAction is no
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>();
    pinchRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(pinchRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    pinchRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(pinchRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer->lastTouchEvent_ = touchEvent;
    pinchRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(pinchRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    touchEvent.tiltX = 0.0f;
    touchEvent.tiltY = 0.0f;
    pinchRecognizer->lastTouchEvent_ = touchEvent;
    pinchRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(pinchRecognizer->touchPoints_.size(), 0);
}

/**
 * @tc.name: PinchRecognizerTest007
 * @tc.desc: Test PinchRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    bool result = false;

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    result = pinchRecognizer->ReconcileFrom(pinchRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is nullptr
     * @tc.expected: step2. result equals.
     */
    result = pinchRecognizer->ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case3: fingers_ != curr->fingers_;
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->fingers_ = 1;
    pinchRecognizerPtr->fingers_ = 0;
    result = pinchRecognizer->ReconcileFrom(pinchRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case4: fingers_ same, distance not same
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->fingers_ = pinchRecognizerPtr->fingers_;
    pinchRecognizer->distance_ = pinchRecognizerPtr->distance_ + 1;
    result = pinchRecognizer->ReconcileFrom(pinchRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case5: fingers_ same, distance same, priorityMask not same
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->fingers_ = pinchRecognizerPtr->fingers_;
    pinchRecognizer->distance_ = pinchRecognizerPtr->distance_;
    pinchRecognizer->priorityMask_ = GestureMask::End;
    result = pinchRecognizer->ReconcileFrom(pinchRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PinchRecognizerSendCallbackMsgTest001
 * @tc.desc: Test PinchRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerSendCallbackMsgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer = AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, -1);
    std::unique_ptr<GestureEventFunc> onAction;

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty, type is AXIS
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    pinchRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(pinchRecognizer->touchPoints_.size(), 0);
}

/**
 * @tc.name: PinchRecognizerHandleTouchMoveEventTest102
 * @tc.desc: Test PinchRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerHandleTouchMoveEventTest102, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    auto pinchRecognizer = AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    AxisEvent axisEvent;
    axisEvent.pinchAxisScale = 0.0;

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case1: input is TouchEvent
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->HandleTouchMoveEvent(touchEvent);
    pinchRecognizer->HandleTouchUpEvent(touchEvent);
    pinchRecognizer->HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case2: input is AxisEvent
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case3: input is TouchEvent, isFlushTouchEventsEnd_
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->isFlushTouchEventsEnd_ = true;
    pinchRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case4: input is TouchEvent, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::FAIL;
    pinchRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case5: input is AxisEvent
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::FAIL;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);
}

/**
 * @tc.name: PinchGestureTest001
 * @tc.desc: Test PinchGesture CreateRecognizer function
 */
HWTEST_F(PinchRecognizerTestNg, PinchGestureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchGestureGesture.
     */
    PinchGestureModelNG pinchGestureModelNG;
    pinchGestureModelNG.Create(FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto pinchGesture = AceType::DynamicCast<NG::PinchGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(pinchGesture->distance_, PINCH_GESTURE_DISTANCE);
}

/**
 * @tc.name: PinchGestureTest002
 * @tc.desc: Test PinchGesture CreateRecognizer function
 */
HWTEST_F(PinchRecognizerTestNg, PinchGestureTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchGesture.
     */
    auto pinchGesture = AceType::MakeRefPtr<PinchGesture>(FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchGesture, nullptr);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.expect: pinchRecognizer create successfully, use the same Option as pinchGesture.
     */
    pinchGesture->priority_ = GesturePriority::Low;
    pinchGesture->gestureMask_ = GestureMask::Normal;
    auto onActionStart = [](GestureEvent& info) { return true; };
    auto onActionUpdate = [](GestureEvent& info) { return true; };
    auto onActionEnd = [](GestureEvent& info) { return true; };
    auto onActionCancel = [](GestureEvent& info) { return true; };
    pinchGesture->SetOnActionStartId(onActionStart);
    pinchGesture->SetOnActionUpdateId(onActionUpdate);
    pinchGesture->SetOnActionEndId(onActionEnd);
    pinchGesture->SetOnActionCancelId(onActionCancel);
    EXPECT_TRUE(pinchGesture->onActionStartId_);
    EXPECT_TRUE(pinchGesture->onActionUpdateId_);
    EXPECT_TRUE(pinchGesture->onActionEndId_);
    EXPECT_TRUE(pinchGesture->onActionCancelId_);
    auto pinchRecognizer = AceType::DynamicCast<PinchRecognizer>(pinchGesture->CreateRecognizer());
    ASSERT_NE(pinchRecognizer, nullptr);
    EXPECT_EQ(pinchRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(pinchRecognizer->GetPriorityMask(), GestureMask::Normal);
    EXPECT_EQ(pinchRecognizer->distance_, PINCH_GESTURE_DISTANCE);
}

/**
 * @tc.name: PinchGestureCreateRecognizerTest001
 * @tc.desc: Test PinchGesture CreateRecognizer function
 */
HWTEST_F(PinchRecognizerTestNg, PinchGestureCreateRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchGesture.
     */
    auto pinchGesture = AceType::MakeRefPtr<PinchGesture>(FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchGesture, nullptr);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.expect: pinchRecognizer create successfully, use the same Option as pinchGesture.
     */
    pinchGesture->priority_ = GesturePriority::Low;
    pinchGesture->gestureMask_ = GestureMask::Normal;
    auto pinchRecognizer = AceType::DynamicCast<PinchRecognizer>(pinchGesture->CreateRecognizer());
    ASSERT_NE(pinchRecognizer, nullptr);
    EXPECT_EQ(pinchRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(pinchRecognizer->GetPriorityMask(), GestureMask::Normal);
    EXPECT_EQ(pinchRecognizer->distance_, PINCH_GESTURE_DISTANCE);
}

/**
 * @tc.name: PinchRecognizerTest009
 * @tc.desc: Test PinchRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchRecognizer, nullptr);

    /**
     * @tc.steps: step2. use fingers_ > MAX_PINCH_FINGERS in HandleTouchDownEvent(TouchEvent).
     * @tc.expect: pinchRecognizer->disposal_ is not equal to GestureDisposal::REJECT.
     */
    TouchEvent touchEvent;
    pinchRecognizer->fingers_ = FINGER_NUMBER_OVER_MAX;
    pinchRecognizer->refereeState_ = RefereeState::READY;
    pinchRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_NE(pinchRecognizer->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step3. test with HandleTouchDownEvent(AxisEvent).
     */
    pinchRecognizer->fingers_ = SINGLE_FINGER_NUMBER;
    AxisEvent axisEvent;

    /**
     * @tc.steps: step3.1. axisEvent NearZero.
     * @tc.expect: pinchRecognizer->disposal_ is not equal to GestureDisposal::REJECT.
     */
    axisEvent.pinchAxisScale = 0.0;
    pinchRecognizer->HandleTouchDownEvent(axisEvent);
    EXPECT_NE(pinchRecognizer->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step3.2. axisEvent not NearZero and IsRefereeFinished() is true.
     * @tc.expect: pinchRecognizer->disposal_ is not equal to GestureDisposal::REJECT.
     */
    axisEvent.pinchAxisScale = 2.0;
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->HandleTouchDownEvent(axisEvent);
    EXPECT_NE(pinchRecognizer->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step3.2. axisEvent with refereeState_ = RefereeState::READY.
     * @tc.expect: pinchRecognizer->scale_ is equal to 1.0f.
     */
    pinchRecognizer->refereeState_ = RefereeState::READY;
    pinchRecognizer->HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->scale_, 1.0);
}

/**
 * @tc.name: PinchRecognizerTest010
 * @tc.desc: Test PinchRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchRecognizer, nullptr);

    /**
     * @tc.steps: step2. use refereeState_ != RefereeState::SUCCEED and refereeState_ != RefereeState::FAIL.
     * @tc.expect: pinchRecognizer->disposal_ is equal to GestureDisposal::REJECT.
     */
    TouchEvent touchEvent;
    pinchRecognizer->isPinchEnd_ = false;
    pinchRecognizer->refereeState_ = RefereeState::FAIL;
    pinchRecognizer->HandleTouchDownEvent(touchEvent);
    pinchRecognizer->refereeState_ = RefereeState::READY;
    pinchRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->disposal_, GestureDisposal::NONE);

    /**
     * @tc.steps: step3. test with HandleTouchDownEvent(AxisEvent).
     */
    AxisEvent axisEvent;
    /**
     * @tc.steps: step3.1. test with isPinchEnd_ is true.
     */
    pinchRecognizer->isPinchEnd_ = true;
    pinchRecognizer->HandleTouchUpEvent(axisEvent);

    /**
     * @tc.steps: step3.2. test with refereeState_ != RefereeState::SUCCEED and refereeState_ != RefereeState::FAIL.
     * @tc.expect: pinchRecognizer->disposal_ is equal to GestureDisposal::REJECT.
     */
    pinchRecognizer->isPinchEnd_ = false;
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    pinchRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step3.2. test with refereeState_ != RefereeState::SUCCEED.
     * @tc.expect: pinchRecognizer->isPinchEnd_ is true.
     */
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->isPinchEnd_, true);
}

/**
 * @tc.name: PinchRecognizerTest012
 * @tc.desc: Test PinchRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchRecognizer, nullptr);
    /**
     * @tc.steps: step2. test with HandleTouchDownEvent(AxisEvent).
     * @tc.expect: pinchRecognizer->lastAxisEvent_ is equal to axisEvent
     * @tc.expect: pinchRecognizer->touchPoints_[axisEvent.id].originalId is equal to axisEvent.originalId
     * @tc.expect: pinchRecognizer->touchPoints_[axisEvent.id].screenX is equal to axisEvent.screenX
     * @tc.expect: pinchRecognizer->touchPoints_[axisEvent.id].screenY is equal to axisEvent.screenY
     */
    AxisEvent axisEvent;
    axisEvent.id = TEST_EVENT_ID;
    axisEvent.originalId = TEST_EVENT_ID;
    pinchRecognizer->fingers_ = FINGER_NUMBER_OVER_MAX;
    pinchRecognizer->refereeState_ = RefereeState::READY;
    pinchRecognizer->HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->lastAxisEvent_.id, axisEvent.id);
    EXPECT_EQ(pinchRecognizer->touchPoints_[axisEvent.id].originalId, axisEvent.originalId);
    EXPECT_EQ(pinchRecognizer->touchPoints_[axisEvent.id].screenX, axisEvent.screenX);
    EXPECT_EQ(pinchRecognizer->touchPoints_[axisEvent.id].screenY, axisEvent.screenY);
}

/**
 * @tc.name: PinchRecognizerTest012
 * @tc.desc: Test PinchRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchRecognizer, nullptr);

    /**
     * @tc.steps: step2. test with HandleTouchUpEvent(AxisEvent).
     * @tc.expect: pinchRecognizer->lastAxisEvent_ is equal to axisEvent
     */
    AxisEvent axisEvent;
    axisEvent.id = TEST_EVENT_ID;
    pinchRecognizer->fingers_ = FINGER_NUMBER_OVER_MAX;
    pinchRecognizer->refereeState_ = RefereeState::READY;
    pinchRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->lastAxisEvent_.id, axisEvent.id);
}

/**
 * @tc.name: PinchRecognizerTest012
 * @tc.desc: Test PinchRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchRecognizer, nullptr);
    /**
     * @tc.steps: step2. test with HandleTouchMoveEvent(AxisEvent).
     * @tc.expect: pinchRecognizer->lastAxisEvent_ is equal to axisEvent
     * @tc.expect: pinchRecognizer->touchPoints_[axisEvent.id].originalId is equal to axisEvent.originalId
     * @tc.expect: pinchRecognizer->touchPoints_[axisEvent.id].screenX is equal to axisEvent.screenX
     * @tc.expect: pinchRecognizer->touchPoints_[axisEvent.id].screenY is equal to axisEvent.screenY
     */
    AxisEvent axisEvent;
    axisEvent.id = TEST_EVENT_ID;
    axisEvent.originalId = TEST_EVENT_ID;
    pinchRecognizer->fingers_ = FINGER_NUMBER_OVER_MAX;
    pinchRecognizer->refereeState_ = RefereeState::READY;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);

    EXPECT_EQ(pinchRecognizer->lastAxisEvent_.id, axisEvent.id);
    EXPECT_EQ(pinchRecognizer->touchPoints_[axisEvent.id].originalId, axisEvent.originalId);
    EXPECT_EQ(pinchRecognizer->touchPoints_[axisEvent.id].screenX, axisEvent.screenX);
    EXPECT_EQ(pinchRecognizer->touchPoints_[axisEvent.id].screenY, axisEvent.screenY);
}

/**
 * @tc.name: PinchRecognizerHandleTouchUpEventTest001
 * @tc.desc: Test PinchRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerHandleTouchUpEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchRecognizer, nullptr);

    /**
     * @tc.steps: step2. use refereeState_ != RefereeState::SUCCEED and refereeState_ != RefereeState::FAIL.
     * @tc.expect: pinchRecognizer->disposal_ is equal to GestureDisposal::REJECT.
     */
    TouchEvent touchEvent;
    pinchRecognizer->isPinchEnd_ = false;
    pinchRecognizer->refereeState_ = RefereeState::FAIL;
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchDownEvent(touchEvent);
    pinchRecognizer->refereeState_ = RefereeState::READY;
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->disposal_, GestureDisposal::NONE);

    /**
     * @tc.steps: step3. test with HandleTouchDownEvent(AxisEvent).
     */
    AxisEvent axisEvent;
    /**
     * @tc.steps: step3.1. test with isPinchEnd_ is true.
     */
    pinchRecognizer->isPinchEnd_ = true;
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchUpEvent(axisEvent);

    /**
     * @tc.steps: step3.2. test with refereeState_ != RefereeState::SUCCEED and refereeState_ != RefereeState::FAIL.
     * @tc.expect: pinchRecognizer->disposal_ is equal to GestureDisposal::REJECT.
     */
    pinchRecognizer->isPinchEnd_ = false;
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step3.2. test with refereeState_ != RefereeState::SUCCEED.
     * @tc.expect: pinchRecognizer->isPinchEnd_ is true.
     */
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->isPinchEnd_, true);
}

/**
 * @tc.name: PinchRecognizerHandleTouchMoveEventTest001
 * @tc.desc: Test PinchRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerHandleTouchMoveEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchRecognizer, nullptr);

    /**
     * @tc.steps: step2. test HandleTouchMoveEvent(TouchEvent).
     */
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    std::vector<TouchEvent> touchEvents;
    for (std::size_t i = 0; i < 5; ++i) {
        TouchEvent touchEvent;
        touchEvent.x = 100.0 * (i + 1);
        touchEvent.y = 100.0 * (i + 1);
        pinchRecognizer->touchPoints_[i] = touchEvent;
    }
    pinchRecognizer->initialDev_ = 1.0;
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;

    /**
     * @tc.steps: step2.1. test HandleTouchMoveEvent(TouchEvent) with fabs(currentDev_ - initialDev_) >= distance_.
     * @tc.expect: scale_ = pinchRecognizer->ComputeAverageDeviation() / initialDev_.
     */
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchMoveEvent(touchEvent);

    /**
     * @tc.steps: step2.2. test HandleTouchMoveEvent(TouchEvent) with refereeState_ == RefereeState::SUCCEED.
     * @tc.expect: scale_ = pinchRecognizer->ComputeAverageDeviation() / initialDev_
     */
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->initialDev_ = 2.0;
    pinchRecognizer->OnFlushTouchEventsEnd();
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchMoveEvent(touchEvent);

    /**
     * @tc.steps: step3. test HandleTouchMoveEvent(AxisEvent).
     */
    AxisEvent axisEvent;
    pinchRecognizer->isPinchEnd_ = false;

    /**
     * @tc.steps: step3.1. axisEvent NearZero.
     * @tc.expect: pinchRecognizer->disposal_ is equal to GestureDisposal::REJECT.
     */
    axisEvent.pinchAxisScale = 0.0;
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->eventManager_ = nullptr;
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step3.2. test with refereeState_ = RefereeState::SUCCEED.
     * @tc.expect: pinchRecognizer->refereeState_ is equal to RefereeState::READY.
     */
    pinchRecognizer->isPinchEnd_ = false;
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->isPinchEnd_, true);

    /**
     * @tc.steps: step3.3. test with axisEvent not NearZero .
     * @tc.expect: pinchRecognizer->scale_ is equal to axisEvent.pinchAxisScale.
     */
    pinchRecognizer->isPinchEnd_ = false;
    axisEvent.pinchAxisScale = 1.0;
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->scale_, axisEvent.pinchAxisScale);
}

/**
 * @tc.name: PinchRecognizerHandleTouchMoveEventTest002
 * @tc.desc: Test PinchRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerHandleTouchMoveEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. test HandleTouchMoveEvent(TouchEvent).
     */
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    std::vector<TouchEvent> touchEvents;
    for (std::size_t i = 0; i < 5; ++i) {
        TouchEvent touchEvent;
        touchEvent.x = 100.0 * (i + 1);
        touchEvent.y = 100.0 * (i + 1);
        pinchRecognizer->touchPoints_[i] = touchEvent;
    }
    pinchRecognizer->initialDev_ = 1.0;
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;

    /**
     * @tc.steps: step2.1. test HandleTouchMoveEvent(TouchEvent) with fabs(currentDev_ - initialDev_) >= distance_.
     * @tc.expect: scale_ = pinchRecognizer->ComputeAverageDeviation() / initialDev_.
     */
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchMoveEvent(touchEvent);
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->initialDev_ = 2.0;
    pinchRecognizer->OnFlushTouchEventsEnd();

    /**
     * @tc.steps: step3. test HandleTouchMoveEvent(AxisEvent).
     */
    AxisEvent axisEvent;
    pinchRecognizer->isPinchEnd_ = false;

    /**
     * @tc.steps: step3.1. axisEvent NearZero.
     * @tc.expect: pinchRecognizer->disposal_ is equal to GestureDisposal::REJECT.
     */
    auto context = PipelineContext::GetCurrentContext();
    context->eventManager_ = nullptr;
    pinchRecognizer->isPinchEnd_ = false;
    axisEvent.pinchAxisScale = 1.0;
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    pinchRecognizer->refereeState_ = RefereeState::FAIL;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->scale_, axisEvent.pinchAxisScale);

    axisEvent.pinchAxisScale = 0;
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    pinchRecognizer->HandleTouchCancelEvent(axisEvent);
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    pinchRecognizer->HandleTouchCancelEvent(touchEvent);
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    pinchRecognizer->currentFingers_ = pinchRecognizer->fingers_;
    pinchRecognizer->HandleTouchUpEvent(touchEvent);
    pinchRecognizer->refereeState_ = RefereeState::FAIL;
    pinchRecognizer->isPinchEnd_ = false;
    pinchRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->scale_, 1);
}

/**
 * @tc.name: PinchRecognizerHandleTouchCancelEventTest001
 * @tc.desc: Test PinchRecognizer function: HandleTouchCancelEvent
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerHandleTouchCancelEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    auto pinchRecognizer = AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    AxisEvent axisEvent;
    axisEvent.pinchAxisScale = 0.0;

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case1: input is TouchEvent
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->HandleTouchMoveEvent(touchEvent);
    pinchRecognizer->HandleTouchUpEvent(touchEvent);
    pinchRecognizer->HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case2: input is AxisEvent
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case3: input is TouchEvent, isFlushTouchEventsEnd_
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->isFlushTouchEventsEnd_ = true;
    pinchRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case4: input is TouchEvent, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::FAIL;
    pinchRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case5: input is AxisEvent
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::FAIL;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchCancelEvent function and compare result.
     * @tc.steps: case6: input is TouchEvent, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::FAIL;
    pinchRecognizer->HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);
}

/**
 * @tc.name: PinchRecognizerHandleTouchCancelEventTest003
 * @tc.desc: Test PinchRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerHandleTouchCancelEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    auto pinchRecognizer = AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    AxisEvent axisEvent;
    axisEvent.pinchAxisScale = 0.0;

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case1: input is TouchEvent
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->currentFingers_ = pinchRecognizer->fingers_;
    pinchRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchCancelEvent function and compare result.
     * @tc.steps: case6: input is TouchEvent, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->isPinchEnd_ = true;
    pinchRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchCancelEvent function and compare result.
     * @tc.steps: case6: input is TouchEvent, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::FAIL;
    pinchRecognizer->isPinchEnd_ = false;
    pinchRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);
}

/**
 * @tc.name: PinchRecognizerHandleTouchCancelEventTest002
 * @tc.desc: Test PinchRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerHandleTouchCancelEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    auto pinchRecognizer = AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    AxisEvent axisEvent;
    axisEvent.pinchAxisScale = 0.0;

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case1: input is TouchEvent
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->HandleTouchMoveEvent(touchEvent);
    pinchRecognizer->currentFingers_ = pinchRecognizer->fingers_;
    pinchRecognizer->HandleTouchUpEvent(touchEvent);
    pinchRecognizer->HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchCancelEvent function and compare result.
     * @tc.steps: case6: input is TouchEvent, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->isPinchEnd_ = true;
    pinchRecognizer->HandleTouchUpEvent(touchEvent);
    pinchRecognizer->HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchCancelEvent function and compare result.
     * @tc.steps: case6: input is TouchEvent, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer->refereeState_ = RefereeState::FAIL;
    pinchRecognizer->isPinchEnd_ = false;
    pinchRecognizer->HandleTouchUpEvent(touchEvent);
    pinchRecognizer->HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer->lastTouchEvent_.id, touchEvent.id);
}

/**
 * @tc.name: PinchRecognizerTest011
 * @tc.desc: Test PinchRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchRecognizer, nullptr);

    /**
     * @tc.steps: step2. test HandleTouchMoveEvent(TouchEvent).
     */
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    std::vector<TouchEvent> touchEvents;
    for (std::size_t i = 0; i < 5; ++i) {
        TouchEvent touchEvent;
        touchEvent.x = 100.0 * (i + 1);
        touchEvent.y = 100.0 * (i + 1);
        pinchRecognizer->touchPoints_[i] = touchEvent;
    }
    pinchRecognizer->initialDev_ = 1.0;
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;

    /**
     * @tc.steps: step2.1. test HandleTouchMoveEvent(TouchEvent) with fabs(currentDev_ - initialDev_) >= distance_.
     * @tc.expect: scale_ = pinchRecognizer->ComputeAverageDeviation() / initialDev_.
     */
    pinchRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->scale_, 1);
    EXPECT_EQ(pinchRecognizer->disposal_, GestureDisposal::NONE);
    /**
     * @tc.steps: step2.2. test HandleTouchMoveEvent(TouchEvent) with refereeState_ == RefereeState::SUCCEED.
     * @tc.expect: scale_ = pinchRecognizer->ComputeAverageDeviation() / initialDev_
     */
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->initialDev_ = 2.0;
    pinchRecognizer->OnFlushTouchEventsEnd();
    pinchRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->scale_, 1);

    /**
     * @tc.steps: step3. test HandleTouchMoveEvent(AxisEvent).
     */
    AxisEvent axisEvent;
    pinchRecognizer->isPinchEnd_ = false;

    /**
     * @tc.steps: step3.1. axisEvent NearZero.
     * @tc.expect: pinchRecognizer->disposal_ is equal to GestureDisposal::REJECT.
     */
    axisEvent.pinchAxisScale = 0.0;
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->eventManager_ = nullptr;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step3.2. test with refereeState_ = RefereeState::SUCCEED.
     * @tc.expect: pinchRecognizer->refereeState_ is equal to RefereeState::READY.
     */
    pinchRecognizer->isPinchEnd_ = false;
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->refereeState_, RefereeState::READY);
    EXPECT_EQ(pinchRecognizer->isPinchEnd_, true);

    /**
     * @tc.steps: step3.3. test with axisEvent not NearZero .
     * @tc.expect: pinchRecognizer->scale_ is equal to axisEvent.pinchAxisScale.
     */
    pinchRecognizer->isPinchEnd_ = false;
    axisEvent.pinchAxisScale = 1.0;
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->scale_, axisEvent.pinchAxisScale);
}

/**
 * @tc.name: PinchRecognizerPtrHandleTouchMoveEventTest002
 * @tc.desc: Test PinchRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerPtrHandleTouchMoveEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and set Recognizer、TargetComponent.
     */
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;
    };
    targetComponent->SetOnGestureJudgeBegin(gestureJudgeFunc);
    TouchEvent touchEvent;
    AxisEvent axisEvent;
    touchEvent.tiltX.emplace(1.0f);
    touchEvent.tiltY.emplace(1.0f);
    pinchRecognizerPtr->targetComponent_ = targetComponent;
    /**
     * @tc.steps: step2. test the function who calls TriggerGestureJudgeCallback.
     * @tc.expected: step2. result equals REJECT.
     */
    pinchRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    pinchRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    pinchRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    pinchRecognizerPtr->fingers_ = 1;
    pinchRecognizerPtr->distance_ = -1;
    pinchRecognizerPtr->initialDev_ = 1;
    pinchRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->disposal_, GestureDisposal::REJECT);

    axisEvent.pinchAxisScale = 1.0;
    pinchRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    pinchRecognizerPtr->isPinchEnd_ = false;
    pinchRecognizerPtr->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizerPtr->disposal_, GestureDisposal::REJECT);
}

class MockPinchRecognizer : public PinchRecognizer {
public:
    MockPinchRecognizer(int32_t fingers, double distance) : PinchRecognizer(fingers, distance) {}
    MOCK_METHOD(void, BatchAdjudicate, (const RefPtr<NGGestureRecognizer>&, GestureDisposal), ());
};

/**
 * @tc.name: PinchRecognizerPtrHandleTouchMoveEventTest003
 * @tc.desc: Test PinchRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerPtrHandleTouchMoveEventTest003, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    TouchEvent event;
    event.id = 1;
    pinchRecognizerPtr->fingersId_.insert(1);
    pinchRecognizerPtr->activeFingers_.push_back(1);
    pinchRecognizerPtr->activeFingers_.push_back(2);
    pinchRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizerPtr->HandleTouchUpEvent(event);
    event.id = 3;
    pinchRecognizerPtr->fingersId_.insert(1);
    pinchRecognizerPtr->activeFingers_.push_back(1);
    pinchRecognizerPtr->activeFingers_.push_back(2);
    pinchRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizerPtr->HandleTouchUpEvent(event);
    EXPECT_EQ(event.id, 3);
}

/**
 * @tc.name: PinchRecognizerPtrHandleTouchMoveEventTest004
 * @tc.desc: Test HandleTouchCancelEvent
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerPtrHandleTouchMoveEventTest004, TestSize.Level1)
{
    MockPinchRecognizer recognizerTest(FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    TouchEvent event;
    event.id = 1;
    recognizerTest.activeFingers_.push_back(1);
    recognizerTest.activeFingers_.push_back(2);
    recognizerTest.refereeState_ = RefereeState::SUCCEED;
    recognizerTest.HandleTouchCancelEvent(event);
    EXPECT_EQ(event.id, 1);
}

/**
 * @tc.name: PinchRecognizerPtrHandleTouchMoveEventTest005
 * @tc.desc: Test SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerPtrHandleTouchMoveEventTest005, TestSize.Level1)
{
    MockPinchRecognizer recognizerTest(FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    recognizerTest.activeFingers_.push_back(1);
    recognizerTest.activeFingers_.push_back(2);
    recognizerTest.refereeState_ = RefereeState::SUCCEED;
    GestureEvent info;
    auto callback = std::make_unique<GestureEventFunc>(funtest);
    recognizerTest.inputEventType_ = InputEventType::AXIS;
    recognizerTest.SendCallbackMsg(callback, GestureCallbackType::ACTION);
    EXPECT_EQ(recognizerTest.inputEventType_, InputEventType::AXIS);
}

/**
 * @tc.name: SetOnActionCancelTest001
 * @tc.desc: Test SendCallbackMsg function in the HandleTouchCancelEvent with touch event input. The onActionCancel
 * function will return GestureEvent info.
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, SetOnActionCancelTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PinchRecognizerTestNg.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. Call SetOnActionCancel.
     * @tc.expected: pinchRecognizer's callback onActionCancel is not nullptr.
     */
    pinchRecognizer->deviceId_ = GESTURE_EVENT_PROPERTY_VALUE;
    double unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    auto onActionCancel = [&unknownPropertyValue](GestureEvent& info) { unknownPropertyValue = info.GetDeviceId(); };
    pinchRecognizer->SetOnActionCancel(onActionCancel);
    EXPECT_NE(pinchRecognizer->onActionCancel_, nullptr);

    /**
     * @tc.steps: step3. Invoke HandleTouchCancelEvent when onActionCancel_ is not null.
     * @tc.expected: The functions have been executed and the unknownPropertyValue has been assigned the correct
     * value. pinchRecognizer->refereeState_ = RefereeState::READY
     */
    TouchEvent touchEvent;
    pinchRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->activeFingers_.push_back(touchEvent.id);
    pinchRecognizer->fingers_ = 1;
    pinchRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
    EXPECT_EQ(pinchRecognizer->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: SetOnActionCancelTest002
 * @tc.desc: Test SendCallbackMsg function in the HandleTouchCancelEvent with axis event input. The onActionCancel
 * function will return GestureEvent info.
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, SetOnActionCancelTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PinchRecognizerTestNg.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. Call SetOnActionCancel.
     * @tc.expected: pinchRecognizer's callback onActionCancel is not nullptr.
     */
    pinchRecognizer->deviceId_ = GESTURE_EVENT_PROPERTY_VALUE;
    double unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    auto onActionCancel = [&unknownPropertyValue](GestureEvent& info) { unknownPropertyValue = info.GetDeviceId(); };
    pinchRecognizer->SetOnActionCancel(onActionCancel);
    EXPECT_NE(pinchRecognizer->onActionCancel_, nullptr);

    /**
     * @tc.steps: step3. Invoke HandleTouchCancelEvent when onActionCancel_ is not null.
     * @tc.expected: The functions have been executed and the unknownPropertyValue has been assigned the correct
     * value.
     */
    AxisEvent axisEvent;
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
}

/**
 * @tc.name: SetOnActionCancelTest003
 * @tc.desc: Test SendCallbackMsg function in the ReconcileFrom. The onActionCancel function will return
 * GestureEvent info.
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, SetOnActionCancelTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. Call SetOnActionCancel.
     * @tc.expected: pinchRecognizer's callback onActionCancel is not nullptr.
     */
    pinchRecognizer->deviceId_ = GESTURE_EVENT_PROPERTY_VALUE;
    double unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    auto onActionCancel = [&unknownPropertyValue](GestureEvent& info) { unknownPropertyValue = info.GetDeviceId(); };
    pinchRecognizer->SetOnActionCancel(onActionCancel);
    EXPECT_NE(pinchRecognizer->onActionCancel_, nullptr);

    /**
     * @tc.steps: step3. Invoke ReconcileFrom when onActionCancel_ is not null.
     * @tc.expected: The functions have been executed and the unknownPropertyValue has been assigned the correct
     * value.
     */
    pinchRecognizer->fingers_ = 0;
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    auto result = pinchRecognizer->ReconcileFrom(pinchRecognizerPtr);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PinchGestureLimitFingerTest001
 * @tc.desc: Test PinchGesture CreateRecognizer function
 */
HWTEST_F(PinchRecognizerTestNg, PinchGestureLimitFingerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchGesture.
     */
    auto pinchGesture = AceType::MakeRefPtr<PinchGesture>(FINGER_NUMBER, PINCH_GESTURE_DISTANCE, IS_LIMIT_FINGER_COUNT);
    ASSERT_NE(pinchGesture, nullptr);
    EXPECT_EQ(pinchGesture->isLimitFingerCount_, IS_LIMIT_FINGER_COUNT);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     * @tc.expect: pinchRecognizer create successfully without the OnActionCall.
     */
    pinchGesture->priority_ = GesturePriority::Low;
    pinchGesture->gestureMask_ = GestureMask::Normal;
    auto pinchRecognizer = AceType::DynamicCast<PinchRecognizer>(pinchGesture->CreateRecognizer());
    ASSERT_NE(pinchRecognizer, nullptr);
    EXPECT_EQ(pinchRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(pinchRecognizer->GetPriorityMask(), GestureMask::Normal);
    EXPECT_EQ(pinchRecognizer->distance_, PINCH_GESTURE_DISTANCE);
    EXPECT_EQ(pinchRecognizer->isLimitFingerCount_, IS_LIMIT_FINGER_COUNT);
}

/**
 * @tc.name: PinchGestureLimitFingerTest002
 * @tc.desc: Test PinchGesture CreateRecognizer function
 */
HWTEST_F(PinchRecognizerTestNg, PinchGestureLimitFingerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchGesture.
     */
    auto pinchGesture =
        AceType::MakeRefPtr<PinchGesture>(FINGER_NUMBER, PINCH_GESTURE_DISTANCE, IS_NOT_LIMIT_FINGER_COUNT);
    ASSERT_NE(pinchGesture, nullptr);
    EXPECT_EQ(pinchGesture->isLimitFingerCount_, IS_NOT_LIMIT_FINGER_COUNT);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId existed
     * @tc.expect: pinchRecognizer create successfully with the OnActionCall.
     */
    pinchGesture->priority_ = GesturePriority::Low;
    pinchGesture->gestureMask_ = GestureMask::Normal;
    auto onActionStart = [](GestureEvent& info) { return true; };
    auto onActionUpdate = [](GestureEvent& info) { return true; };
    auto onActionEnd = [](GestureEvent& info) { return true; };
    auto onActionCancel = [](GestureEvent& info) { return true; };
    pinchGesture->SetOnActionStartId(onActionStart);
    pinchGesture->SetOnActionUpdateId(onActionUpdate);
    pinchGesture->SetOnActionEndId(onActionEnd);
    pinchGesture->SetOnActionCancelId(onActionCancel);
    EXPECT_TRUE(pinchGesture->onActionStartId_);
    EXPECT_TRUE(pinchGesture->onActionUpdateId_);
    EXPECT_TRUE(pinchGesture->onActionEndId_);
    EXPECT_TRUE(pinchGesture->onActionCancelId_);
    auto pinchRecognizer = AceType::DynamicCast<PinchRecognizer>(pinchGesture->CreateRecognizer());
    ASSERT_NE(pinchRecognizer, nullptr);
    EXPECT_EQ(pinchRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(pinchRecognizer->GetPriorityMask(), GestureMask::Normal);
    EXPECT_EQ(pinchRecognizer->distance_, PINCH_GESTURE_DISTANCE);
    EXPECT_EQ(pinchRecognizer->isLimitFingerCount_, IS_NOT_LIMIT_FINGER_COUNT);
}

/**
 * @tc.name: OnAccepted001
 * @tc.desc: Test OnAccepted function
 */
HWTEST_F(PinchRecognizerTestNg, OnAccepted001, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    TimeStamp timeStape = std::chrono::high_resolution_clock::now();
    pinchRecognizerPtr->firstInputTime_ = timeStape;
    SystemProperties::traceInputEventEnable_ = true;
    pinchRecognizerPtr->OnAccepted();
    EXPECT_EQ(pinchRecognizerPtr->firstInputTime_.has_value(), true);
}

/**
 * @tc.name: HandleTouchDownEvent001
 * @tc.desc: Test HandleTouchDownEvent function
 */
HWTEST_F(PinchRecognizerTestNg, HandleTouchDownEvent001, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.SetX(-100);
    touchEvent.SetY(200);
    pinchRecognizerPtr->refereeState_ = RefereeState::FAIL;
    pinchRecognizerPtr->currentFingers_ = 2;
    pinchRecognizerPtr->fingers_ = 0;
    pinchRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    pinchRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    pinchRecognizerPtr->HandleTouchDownEvent(touchEvent);

    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: HandleTouchDownEvent002
 * @tc.desc: Test HandleTouchDownEvent function
 */
HWTEST_F(PinchRecognizerTestNg, HandleTouchDownEvent002, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    AxisEvent event;
    TimeStamp timeStape = std::chrono::high_resolution_clock::now();
    event.isRotationEvent = true;
    event.time = timeStape;
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->firstInputTime_, timeStape);
}

/**
 * @tc.name: HandleTouchDownEvent003
 * @tc.desc: Test HandleTouchDownEvent function
 */
HWTEST_F(PinchRecognizerTestNg, HandleTouchDownEvent003, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    AxisEvent event;
    TimeStamp timeStape = std::chrono::high_resolution_clock::now();
    event.time = timeStape;
    event.pinchAxisScale = 1.0;
    int32_t apiVersion = 1018;
    event.pressedCodes = {KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A};
    pinchRecognizerPtr->refereeState_ = RefereeState::READY;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(apiVersion);
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);

    pinchRecognizerPtr->refereeState_ = RefereeState::READY;
    event.pinchAxisScale = 1.0;
    event.sourceTool = SourceTool::FINGER;
    event.pressedCodes.clear();
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);

    pinchRecognizerPtr->refereeState_ = RefereeState::READY;
    event.pinchAxisScale = 1.0;
    event.pressedCodes = {KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A};
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);

    pinchRecognizerPtr->refereeState_ = RefereeState::READY;
    event.pinchAxisScale = 1.0;
    event.pressedCodes.clear();
    event.sourceTool = SourceTool::TOUCHPAD;
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);

    pinchRecognizerPtr->refereeState_ = RefereeState::READY;
    event.pinchAxisScale = 100.0;
    event.pressedCodes = {KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A};
    event.sourceTool = SourceTool::FINGER;
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);

    pinchRecognizerPtr->refereeState_ = RefereeState::READY;
    event.pinchAxisScale = 100.0;
    event.pressedCodes.clear();
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::READY);

    event.pinchAxisScale = 100.0;
    event.sourceTool = SourceTool::TOUCHPAD;
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::READY);

    event.pinchAxisScale = 100.0;
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: HandleTouchDownEvent004
 * @tc.desc: Test HandleTouchDownEvent function
 */
HWTEST_F(PinchRecognizerTestNg, HandleTouchDownEvent004, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    AxisEvent event;
    TimeStamp timeStape = std::chrono::high_resolution_clock::now();
    event.time = timeStape;
    event.pinchAxisScale = 1.0;
    int32_t apiVersion = 1018;
    event.pressedCodes = {KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A};
    pinchRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(apiVersion);
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);

    event.pinchAxisScale = 1.0;
    event.sourceTool = SourceTool::FINGER;
    event.pressedCodes.clear();
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);

    event.pinchAxisScale = 1.0;
    event.pressedCodes = {KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A};
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);

    event.pinchAxisScale = 1.0;
    event.pressedCodes.clear();
    event.sourceTool = SourceTool::TOUCHPAD;
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);

    event.pinchAxisScale = 100.0;
    event.pressedCodes = {KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A};
    event.sourceTool = SourceTool::FINGER;
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);

    event.pinchAxisScale = 100.0;
    event.pressedCodes.clear();
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);

    event.pinchAxisScale = 100.0;
    event.sourceTool = SourceTool::TOUCHPAD;
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);

    event.pinchAxisScale = 100.0;
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);
}

/**
 * @tc.name: HandleTouchDownEvent005
 * @tc.desc: Test HandleTouchDownEvent function
 */
HWTEST_F(PinchRecognizerTestNg, HandleTouchDownEvent005, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    int32_t apiVersion = 1000;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(apiVersion);
    AxisEvent event;
    TimeStamp timeStape = std::chrono::high_resolution_clock::now();
    event.time = timeStape;
    event.pinchAxisScale = 1.0;
    event.pressedCodes = {KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A};
    pinchRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);

    event.pinchAxisScale = 1.0;
    event.pressedCodes.clear();
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);

    event.pinchAxisScale = 100.0;
    event.pressedCodes = {KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A};
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);

    event.pinchAxisScale = 100.0;
    event.pressedCodes.clear();
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);
}

/**
 * @tc.name: HandleTouchDownEvent006
 * @tc.desc: Test HandleTouchDownEvent function
 */
HWTEST_F(PinchRecognizerTestNg, HandleTouchDownEvent006, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    AxisEvent event;
    TimeStamp timeStape = std::chrono::high_resolution_clock::now();
    event.time = timeStape;
    event.pinchAxisScale = 1.0;
    event.pressedCodes = {KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A};
    pinchRecognizerPtr->refereeState_ = RefereeState::READY;
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);

    pinchRecognizerPtr->refereeState_ = RefereeState::READY;
    event.pinchAxisScale = 1.0;
    event.pressedCodes.clear();
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);

    pinchRecognizerPtr->refereeState_ = RefereeState::READY;
    event.pinchAxisScale = 100.0;
    event.pressedCodes = {KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A};
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::DETECTING);

    pinchRecognizerPtr->refereeState_ = RefereeState::READY;
    event.pinchAxisScale = 100.0;
    event.pressedCodes.clear();
    pinchRecognizerPtr->HandleTouchDownEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: HandleTouchUpEvent001
 * @tc.desc: Test HandleTouchUpEvent function
 */
HWTEST_F(PinchRecognizerTestNg, HandleTouchUpEvent001, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    TouchEvent touchEvent;
    touchEvent.id = 1;
    pinchRecognizerPtr->isNeedResetVoluntarily_ = true;
    pinchRecognizerPtr->currentFingers_ = 1;
    pinchRecognizerPtr->fingers_ = 0;
    pinchRecognizerPtr->fingersId_.clear();
    pinchRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    pinchRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    pinchRecognizerPtr->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->isLastPinchFinished_, true);
}

/**
 * @tc.name: HandleTouchUpEvent002
 * @tc.desc: Test HandleTouchUpEvent function
 */
HWTEST_F(PinchRecognizerTestNg, HandleTouchUpEvent002, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    TouchEvent touchEvent;
    touchEvent.id = 1;
    pinchRecognizerPtr->isNeedResetVoluntarily_ = false;
    pinchRecognizerPtr->currentFingers_ = 1;
    pinchRecognizerPtr->fingersId_.clear();

    pinchRecognizerPtr->fingers_ = 2;
    pinchRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    pinchRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    pinchRecognizerPtr->refereeState_ = RefereeState::FAIL;
    pinchRecognizerPtr->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->activeFingers_.size(), 0);

    pinchRecognizerPtr->fingers_ = 0;
    pinchRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    pinchRecognizerPtr->refereeState_ = RefereeState::FAIL;
    pinchRecognizerPtr->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->activeFingers_.size(), 0);

    pinchRecognizerPtr->fingers_ = 2;
    pinchRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    pinchRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizerPtr->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->activeFingers_.size(), 0);

    pinchRecognizerPtr->fingers_ = 0;
    pinchRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    pinchRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizerPtr->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->activeFingers_.size(), 0);
}

/**
 * @tc.name: HandleTouchUpEvent003
 * @tc.desc: Test HandleTouchUpEvent function
 */
HWTEST_F(PinchRecognizerTestNg, HandleTouchUpEvent003, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    TouchEvent touchEvent;
    touchEvent.id = 1;
    pinchRecognizerPtr->isNeedResetVoluntarily_ = false;
    pinchRecognizerPtr->currentFingers_ = 1;
    pinchRecognizerPtr->fingersId_.clear();

    TimeStamp timeStape = std::chrono::high_resolution_clock::now();
    pinchRecognizerPtr->firstInputTime_ = timeStape;
    SystemProperties::traceInputEventEnable_ = true;
    pinchRecognizerPtr->fingers_ = 1;
    pinchRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    pinchRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    pinchRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizerPtr->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->activeFingers_.size(), 0);

    pinchRecognizerPtr->fingers_ = 0;
    pinchRecognizerPtr->isNeedResetVoluntarily_ = false;
    pinchRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    pinchRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    pinchRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizerPtr->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->activeFingers_.size(), 0);

    pinchRecognizerPtr->fingers_ = 1;
    pinchRecognizerPtr->isNeedResetVoluntarily_ = false;
    pinchRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    pinchRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    pinchRecognizerPtr->refereeState_ = RefereeState::FAIL;
    pinchRecognizerPtr->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->activeFingers_.size(), 0);

    pinchRecognizerPtr->fingers_ = 0;
    pinchRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    pinchRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    pinchRecognizerPtr->refereeState_ = RefereeState::FAIL;
    pinchRecognizerPtr->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->activeFingers_.size(), 0);
}

/**
 * @tc.name: HandleTouchUpEvent004
 * @tc.desc: Test HandleTouchUpEvent function
 */
HWTEST_F(PinchRecognizerTestNg, HandleTouchUpEvent004, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    AxisEvent event;
    pinchRecognizerPtr->isNeedResetVoluntarily_ = false;
    pinchRecognizerPtr->currentFingers_ = 1;
    pinchRecognizerPtr->fingersId_.clear();

    TimeStamp timeStape = std::chrono::high_resolution_clock::now();
    pinchRecognizerPtr->firstInputTime_ = timeStape;
    SystemProperties::traceInputEventEnable_ = true;
    pinchRecognizerPtr->fingers_ = 1;
    pinchRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizerPtr->HandleTouchUpEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->activeFingers_.size(), 0);
}

/**
 * @tc.name: HandleTouchMoveEvent001
 * @tc.desc: Test HandleTouchMoveEvent function
 */
HWTEST_F(PinchRecognizerTestNg, HandleTouchMoveEvent001, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    TouchEvent touchEvent;
    touchEvent.id = 1;
    pinchRecognizerPtr->isNeedResetVoluntarily_ = false;
    pinchRecognizerPtr->currentFingers_ = 1;
    pinchRecognizerPtr->fingersId_.clear();

    TimeStamp timeStape = std::chrono::high_resolution_clock::now();
    pinchRecognizerPtr->firstInputTime_ = timeStape;
    touchEvent.time = timeStape;
    SystemProperties::traceInputEventEnable_ = true;
    pinchRecognizerPtr->fingers_ = 3;
    pinchRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    pinchRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    pinchRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->time_, timeStape);

    pinchRecognizerPtr->fingers_ = 3;
    pinchRecognizerPtr->activeFingers_.clear();
    pinchRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    pinchRecognizerPtr->activeFingers_.push_back(1);
    pinchRecognizerPtr->activeFingers_.push_back(2);
    pinchRecognizerPtr->touchPoints_.clear();
    pinchRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->time_, timeStape);

    pinchRecognizerPtr->fingers_ = 2;
    pinchRecognizerPtr->activeFingers_.clear();
    pinchRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    pinchRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    pinchRecognizerPtr->touchPoints_[2] = touchEvent;
    pinchRecognizerPtr->touchPoints_[3] = touchEvent;
    pinchRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->time_, timeStape);

    pinchRecognizerPtr->fingers_ = 1;
    pinchRecognizerPtr->activeFingers_.clear();
    pinchRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    pinchRecognizerPtr->activeFingers_.push_back(1);
    pinchRecognizerPtr->activeFingers_.push_back(2);
    pinchRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    pinchRecognizerPtr->touchPoints_[2] = touchEvent;
    pinchRecognizerPtr->touchPoints_[3] = touchEvent;
    pinchRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->time_, timeStape);
}

/**
 * @tc.name: HandleTouchMoveEvent002
 * @tc.desc: Test HandleTouchMoveEvent function
 */
HWTEST_F(PinchRecognizerTestNg, HandleTouchMoveEvent002, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    TouchEvent touchEvent;
    touchEvent.id = 1;
    pinchRecognizerPtr->isNeedResetVoluntarily_ = false;
    pinchRecognizerPtr->currentFingers_ = 1;
    pinchRecognizerPtr->fingersId_.clear();

    TimeStamp timeStape = std::chrono::high_resolution_clock::now();
    pinchRecognizerPtr->firstInputTime_ = timeStape;
    touchEvent.time = timeStape;
    SystemProperties::traceInputEventEnable_ = true;
    pinchRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    pinchRecognizerPtr->fingers_ = 0;
    pinchRecognizerPtr->initialDev_ = pinchRecognizerPtr->ComputeAverageDeviation()-1;
    pinchRecognizerPtr->distance_ = 1;
    pinchRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    pinchRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    pinchRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->time_, timeStape);
}

/**
 * @tc.name: HandleTouchMoveEvent003
 * @tc.desc: Test HandleTouchMoveEvent function
 */
HWTEST_F(PinchRecognizerTestNg, HandleTouchMoveEvent003, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    TouchEvent touchEvent;
    touchEvent.id = 1;
    pinchRecognizerPtr->isNeedResetVoluntarily_ = false;
    pinchRecognizerPtr->currentFingers_ = 1;
    pinchRecognizerPtr->fingersId_.clear();

    TimeStamp timeStape = std::chrono::high_resolution_clock::now();
    pinchRecognizerPtr->firstInputTime_ = timeStape;
    touchEvent.time = timeStape;

    pinchRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizerPtr->fingers_ = 0;
    pinchRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    pinchRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    pinchRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->time_, timeStape);

    pinchRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizerPtr->fingers_ = 0;
    pinchRecognizerPtr->isLimitFingerCount_ = true;
    pinchRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->time_, timeStape);

    pinchRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizerPtr->fingers_ = 3;
    pinchRecognizerPtr->activeFingers_.push_back(2);
    pinchRecognizerPtr->activeFingers_.push_back(3);
    pinchRecognizerPtr->isLimitFingerCount_ = true;
    pinchRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->time_, timeStape);

    pinchRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizerPtr->fingers_ = 3;
    pinchRecognizerPtr->isLimitFingerCount_ = false;
    pinchRecognizerPtr->isFlushTouchEventsEnd_ = true;
    pinchRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->time_, timeStape);
}

/**
 * @tc.name: HandleTouchMoveEvent004
 * @tc.desc: Test HandleTouchMoveEvent function
 */
HWTEST_F(PinchRecognizerTestNg, HandleTouchMoveEvent004, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    int32_t apiVersion = 1000;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(apiVersion);

    AxisEvent event;
    event.pressedCodes = {KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A};
    TimeStamp timeStape = std::chrono::high_resolution_clock::now();
    event.time = timeStape;
    event.pinchAxisScale = 0.0;
    event.verticalAxis = 1.0;
    event.horizontalAxis = 1.0;
    pinchRecognizerPtr->scale_ = 0.0;
    pinchRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizerPtr->HandleTouchMoveEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->time_, timeStape);

    event.pinchAxisScale = 0.0;
    event.verticalAxis = - 1.0;
    event.horizontalAxis = - 1.0;
    pinchRecognizerPtr->scale_ = 0.0;
    pinchRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizerPtr->HandleTouchMoveEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->time_, timeStape);

    event.pinchAxisScale = 0.0;
    event.verticalAxis = 1.0;
    event.horizontalAxis = - 1.0;
    pinchRecognizerPtr->scale_ = 0.0;
    pinchRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizerPtr->HandleTouchMoveEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->time_, timeStape);

    event.pinchAxisScale = 0.0;
    event.verticalAxis = - 1.0;
    event.horizontalAxis = 1.0;
    pinchRecognizerPtr->scale_ = 0.0;
    pinchRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizerPtr->HandleTouchMoveEvent(event);
    EXPECT_EQ(pinchRecognizerPtr->time_, timeStape);
}

/**
 * @tc.name: HandleTouchCancelEvent001
 * @tc.desc: Test HandleTouchCancelEvent function
 */
HWTEST_F(PinchRecognizerTestNg, HandleTouchCancelEvent001, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    TouchEvent touchEvent;
    touchEvent.id = 1;
    pinchRecognizerPtr->isNeedResetVoluntarily_ = false;
    pinchRecognizerPtr->currentFingers_ = 1;
    pinchRecognizerPtr->activeFingers_.push_back(touchEvent.id);
    pinchRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;

    pinchRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizerPtr->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->IsActiveFinger(touchEvent.id), true);

    pinchRecognizerPtr->refereeState_ = RefereeState::FAIL;
    pinchRecognizerPtr->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->IsActiveFinger(touchEvent.id), true);

    pinchRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    pinchRecognizerPtr->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(pinchRecognizerPtr->IsActiveFinger(touchEvent.id), true);
}

/**
 * @tc.name: ComputePinchCenter001
 * @tc.desc: Test ComputePinchCenter function
 */
HWTEST_F(PinchRecognizerTestNg, ComputePinchCenter001, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    auto ret = pinchRecognizerPtr->ComputePinchCenter();
    EXPECT_EQ(ret, Offset());
}

/**
 * @tc.name: SendCallbackMsg001
 * @tc.desc: Test SendCallbackMsg function
 */
HWTEST_F(PinchRecognizerTestNg, SendCallbackMsg001, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    auto callback = std::make_unique<GestureEventFunc>(funtest);
    RefPtr<GestureInfo> gestureInfo = AceType::MakeRefPtr<GestureInfo>();
    gestureInfo->disposeTag_ = true;
    pinchRecognizerPtr->SetGestureInfo(gestureInfo);
    pinchRecognizerPtr->SendCallbackMsg(callback, GestureCallbackType::ACTION);

    pinchRecognizerPtr->lastTouchEvent_.SetRollAngle(10.0);
    gestureInfo->disposeTag_ = false;
    pinchRecognizerPtr->SendCallbackMsg(callback, GestureCallbackType::ACTION);
    EXPECT_EQ(pinchRecognizerPtr->lastTouchEvent_.rollAngle.has_value(), true);

    pinchRecognizerPtr->lastTouchEvent_.SetRollAngle(10.0);
    gestureInfo->disposeTag_ = false;
    pinchRecognizerPtr->SetGestureInfo(nullptr);
    pinchRecognizerPtr->SendCallbackMsg(callback, GestureCallbackType::ACTION);
    EXPECT_EQ(pinchRecognizerPtr->lastTouchEvent_.rollAngle.has_value(), true);
}

/**
 * @tc.name: TriggerGestureJudgeCallback001
 * @tc.desc: Test TriggerGestureJudgeCallback function
 */
HWTEST_F(PinchRecognizerTestNg, TriggerGestureJudgeCallback001, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    GestureRecognizerJudgeFunc judgeFunc1;
    GestureJudgeFunc judgeFunc2;

    judgeFunc1 = [](const std::shared_ptr<BaseGestureEvent>& info,
        const RefPtr<NGGestureRecognizer>& current,
        const std::list<RefPtr<NGGestureRecognizer>>& others) -> GestureJudgeResult {
        return GestureJudgeResult::REJECT;
    };
    judgeFunc2 = [](const RefPtr<GestureInfo>& gestureInfo,
        const std::shared_ptr<BaseGestureEvent>& info) -> GestureJudgeResult {
        return GestureJudgeResult::REJECT;
    };

    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<NG::TargetComponent>();
    pinchRecognizerPtr->SetTargetComponent(targetComponent);
    EXPECT_EQ(pinchRecognizerPtr->TriggerGestureJudgeCallback(), GestureJudgeResult::CONTINUE);

    targetComponent->SetOnGestureRecognizerJudgeBegin(std::move(judgeFunc1));
    pinchRecognizerPtr->SetTargetComponent(targetComponent);
    EXPECT_NE(pinchRecognizerPtr->TriggerGestureJudgeCallback(), GestureJudgeResult::CONTINUE);

    targetComponent->onGestureJudgeBegin_ = judgeFunc2;
    pinchRecognizerPtr->SetTargetComponent(targetComponent);
    EXPECT_NE(pinchRecognizerPtr->TriggerGestureJudgeCallback(), GestureJudgeResult::CONTINUE);

    pinchRecognizerPtr->inputEventType_ = InputEventType::AXIS;
    AxisEvent axisEvent;
    pinchRecognizerPtr->lastAxisEvent_ = axisEvent;
    EXPECT_EQ(pinchRecognizerPtr->TriggerGestureJudgeCallback(), GestureJudgeResult::REJECT);

    pinchRecognizerPtr->inputEventType_ = InputEventType::TOUCH_SCREEN;
    TouchEvent touchEvent;
    pinchRecognizerPtr->lastTouchEvent_ = touchEvent;
    EXPECT_EQ(pinchRecognizerPtr->TriggerGestureJudgeCallback(), GestureJudgeResult::REJECT);

    RefPtr<PinchRecognizer> pinchRecognizerPtr2 =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    RefPtr<NG::TargetComponent> targetComponent2 = AceType::MakeRefPtr<NG::TargetComponent>();
    targetComponent2->onGestureJudgeBegin_ = judgeFunc2;
    pinchRecognizerPtr2->lastTouchEvent_.SetRollAngle(10.0);
    pinchRecognizerPtr2->SetTargetComponent(targetComponent2);
    EXPECT_EQ(pinchRecognizerPtr2->lastTouchEvent_.rollAngle.has_value(), true);
    EXPECT_NE(pinchRecognizerPtr2->TriggerGestureJudgeCallback(), GestureJudgeResult::CONTINUE);
}

/**
 * @tc.name: ProcessAxisAbnormalCondition001
 * @tc.desc: Test ProcessAxisAbnormalCondition function
 */
HWTEST_F(PinchRecognizerTestNg, ProcessAxisAbnormalCondition001, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    int32_t apiVersion = 1018;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(apiVersion);
    AxisEvent axisEvent;
    axisEvent.pinchAxisScale = 1.0;
    auto ret = pinchRecognizerPtr->ProcessAxisAbnormalCondition(axisEvent);
    EXPECT_EQ(ret, false);

    axisEvent.sourceTool = SourceTool::TOUCHPAD;
    ret = pinchRecognizerPtr->ProcessAxisAbnormalCondition(axisEvent);
    EXPECT_EQ(ret, false);

    AxisEvent axisEvent2;
    axisEvent2.pinchAxisScale = 1.0;
    axisEvent2.pressedCodes = {KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A};
    ret = pinchRecognizerPtr->ProcessAxisAbnormalCondition(axisEvent2);
    EXPECT_EQ(ret, false);

    axisEvent.pressedCodes = {KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A};
    ret = pinchRecognizerPtr->ProcessAxisAbnormalCondition(axisEvent);
    EXPECT_EQ(ret, false);

    AxisEvent axisEvent3;
    axisEvent3.pinchAxisScale = 0.0;
    ret = pinchRecognizerPtr->ProcessAxisAbnormalCondition(axisEvent3);
    EXPECT_EQ(ret, false);

    axisEvent3.sourceTool = SourceTool::TOUCHPAD;
    pinchRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    ret = pinchRecognizerPtr->ProcessAxisAbnormalCondition(axisEvent3);
    EXPECT_EQ(ret, true);

    AxisEvent axisEvent4;
    axisEvent4.pinchAxisScale = 0.0;
    axisEvent4.pressedCodes = {KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A};
    pinchRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    ret = pinchRecognizerPtr->ProcessAxisAbnormalCondition(axisEvent4);
    EXPECT_EQ(ret, false);

    axisEvent3.pressedCodes = {KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A};
    pinchRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    ret = pinchRecognizerPtr->ProcessAxisAbnormalCondition(axisEvent3);
    EXPECT_EQ(ret, true);
}
/**
 * @tc.name: PinchRecognizerTypeTest001
 * @tc.desc: Test PinchRecognizerTypeTest
 */
HWTEST_F(PinchRecognizerTestNg, PinchRecognizerTypeTest001, TestSize.Level1)
{
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    pinchRecognizerPtr->AttachFrameNode(frameNode);

    pinchRecognizerPtr->SetRecognizerType(GestureTypeName::PINCH_GESTURE);
    GestureEvent info;
    pinchRecognizerPtr->HandleReports(info, GestureCallbackType::END);
    EXPECT_EQ(pinchRecognizerPtr->GetRecognizerType(), GestureTypeName::PINCH_GESTURE);
}

/*
 * @tc.name: GetGestureEventInfoTest001
 * @tc.desc: Test GetGestureEventInfo
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerTestNg, GetGestureEventInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    pinchRecognizerPtr->AttachFrameNode(frameNode);
    /**
     * @tc.steps: step2. call GetGestureEventInfo function and compare result.
     * @tc.steps: case: touchEvent is not default.
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    axisEvent.sourceTool = SourceTool::MOUSE;
    axisEvent.pinchAxisScale = 0.5f;
    pinchRecognizerPtr->lastAxisEvent_ = axisEvent;
    pinchRecognizerPtr->inputEventType_ = InputEventType::AXIS;
    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::PEN;
    pinchRecognizerPtr->lastTouchEvent_ = touchEvent;
    
    GestureEvent info;
    info.SetPinchAxisScale(1.0f);
    pinchRecognizerPtr->GetGestureEventInfo(info);
    EXPECT_EQ(info.GetSourceTool(), SourceTool::MOUSE);
    EXPECT_EQ(info.GetPinchAxisScale(), 0.5f);

    pinchRecognizerPtr->inputEventType_ = InputEventType::TOUCH_SCREEN;
    pinchRecognizerPtr->GetGestureEventInfo(info);
    EXPECT_EQ(info.GetSourceTool(), SourceTool::PEN);
}
} // namespace OHOS::Ace::NG