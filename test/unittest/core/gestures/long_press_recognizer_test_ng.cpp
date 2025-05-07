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
#include "test/mock/base/mock_task_executor.h"
#include "test/unittest/core/gestures/gestures_common_test_ng.h"
#include "ui/base/referenced.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float GESTURE_EVENT_PROPERTY_DEFAULT_VALUE = 0.0;
constexpr float GESTURE_EVENT_PROPERTY_VALUE = 10.0;
constexpr int64_t DEFAULT_MOVE_TIME = 1000000000;
const std::string TEST_EXTRA_INFO = "Reject: received cancel and succeed.";
constexpr double DEFAULT_LONGPRESS_DURATION = 500.0;
struct MockLongPressRecognizerCase {
    int32_t fingers;
    double duration;
    int32_t time;
    RefereeState refereeState;
    int32_t expectedFingers;
    double expectedDuration;
    RefereeState expectedRefereeState;
    std::vector<TouchEvent> inputTouchEvents;
};
} // namespace

class LongPressRecognizerTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void LongPressRecognizerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void LongPressRecognizerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: LongPressRecognizerTest001
 * @tc.desc: Test LongPressRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    OnLongPress onLongPress;
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case1: !onLongPress, !empty, repeat
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer->repeat_ = true;
    longPressRecognizer->OnAccepted();
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case2: !onLongPress, empty, !repeat
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->touchPoints_.clear();
    longPressRecognizer->repeat_ = false;
    longPressRecognizer->OnAccepted();
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case3: onLongPress, empty, !repeat
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->touchPoints_.clear();
    longPressRecognizer->repeat_ = false;
    longPressRecognizer->OnAccepted();
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case4: onLongPress, !empty, !repeat
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->touchPoints_.clear();
    longPressRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer->repeat_ = false;
    longPressRecognizer->OnAccepted();
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.expected: step3. result equals.
     */
    longPressRecognizer->OnRejected();
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: LongPressRecognizerTest002
 * @tc.desc: Test LongPressRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case1: referee is not SUCCEED
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    longPressRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->time_, touchEvent.time);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case2: referee is SUCCEED
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->time_, touchEvent.time);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case2: referee is SUCCEED
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->currentFingers_ = longPressRecognizer->fingers_;
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->time_, touchEvent.time);
}

/**
 * @tc.name: LongPressRecognizerTest003
 * @tc.desc: Test LongPressRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case1: pointsCount == fingers, useCatchMode_ is true
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    longPressRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case2: pointsCount == fingers, useCatchMode_ is true
     * @tc.expected: step2. result equals.
     */
    touchEvent.sourceType = SourceType::MOUSE;
    longPressRecognizer->isForDrag_ = true;
    longPressRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer->fingers_ = 1;
    longPressRecognizer->useCatchMode_ = true;
    longPressRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(longPressRecognizer->globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::READY);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case3: pointsCount == fingers, useCatchMode_ is false
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->useCatchMode_ = false;
    longPressRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::READY);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case4: referee is SUCCEED
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case5: change SourceType to KEYBOARD
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->refereeState_ = RefereeState::PENDING;
    touchEvent.sourceType = SourceType::KEYBOARD;
    longPressRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case6: change isForDrag
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->isForDrag_ = !longPressRecognizer->isForDrag_;
    longPressRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case7: change isDisableMouseLeft_
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->isDisableMouseLeft_ = !longPressRecognizer->isDisableMouseLeft_;
    longPressRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 1);
}

/**
 * @tc.name: LongPressRecognizerTest004
 * @tc.desc: Test LongPressRecognizer function: HandleTouchCancelEvent UpEvent
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: refereeState == RefereeState::SUCCEED
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer->HandleTouchUpEvent(touchEvent);
    longPressRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: refereeState == RefereeState::SUCCEED
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer->currentFingers_ = longPressRecognizer->fingers_;
    longPressRecognizer->HandleTouchUpEvent(touchEvent);
    longPressRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 0);
}

/**
 * @tc.name: LongPressRecognizerDoRepeatTest001
 * @tc.desc: Test LongPressRecognizer function: DoRepeat
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerDoRepeatTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call DoRepeat
     * @tc.steps: refereeState == RefereeState::SUCCEED
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer->fingers_ = 0;
    longPressRecognizer->DoRepeat();
    longPressRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call DoRepeat
     * @tc.steps: refereeState == RefereeState::SUCCEED
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->refereeState_ = RefereeState::DETECTING;
    longPressRecognizer->currentFingers_ = longPressRecognizer->fingers_;
    longPressRecognizer->fingers_ = 0;
    longPressRecognizer->DoRepeat();
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 0);
}

/**
 * @tc.name: LongPressRecognizerTest005
 * @tc.desc: Test LongPressRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    bool isRepeat = false;

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case1: onAction is no, *onAction is no
     * @tc.expected: step2. result equals.
     */
    std::unique_ptr<GestureEventFunc> onAction;
    longPressRecognizer->SendCallbackMsg(onAction, isRepeat, GestureCallbackType::START);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case2: onAction is yes, *onAction is no
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>();
    longPressRecognizer->SendCallbackMsg(onAction, isRepeat, GestureCallbackType::START);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    longPressRecognizer->SendCallbackMsg(onAction, isRepeat, GestureCallbackType::START);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    longPressRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer->SendCallbackMsg(onAction, isRepeat, GestureCallbackType::START);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    touchEvent.tiltX = 0.0f;
    touchEvent.tiltY = 0.0f;
    longPressRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer->SendCallbackMsg(onAction, isRepeat, GestureCallbackType::START);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 1);
}

/**
 * @tc.name: LongPressRecognizerTest006
 * @tc.desc: Test LongPressRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    RefPtr<LongPressRecognizer> longPressRecognizerPtr =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    auto result = longPressRecognizer->ReconcileFrom(longPressRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is nullptr
     * @tc.expected: step2. result equals.
     */
    result = longPressRecognizer->ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case3: recognizerPtr, duration not same
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->duration_ = 0;
    result = longPressRecognizer->ReconcileFrom(longPressRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case4: recognizerPtr, duration same, fingers not same
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->duration_ = longPressRecognizerPtr->duration_;
    longPressRecognizer->fingers_ = longPressRecognizerPtr->fingers_ + 1;
    result = longPressRecognizer->ReconcileFrom(longPressRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case5: recognizerPtr, fingers same, repeat not same
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->fingers_ = longPressRecognizerPtr->fingers_;
    longPressRecognizer->repeat_ = !longPressRecognizerPtr->repeat_;
    result = longPressRecognizer->ReconcileFrom(longPressRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case5: recognizerPtr, repeat same, priorityMask not same
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->repeat_ = longPressRecognizerPtr->repeat_;
    longPressRecognizer->priorityMask_ = GestureMask::End;
    result = longPressRecognizer->ReconcileFrom(longPressRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: LongPressRecognizerTestGetLongPressActionFunc001
 * @tc.desc: Test LongPressRecognizer function: GetLongPressActionFunc
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerTestGetLongPressActionFunc001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    bool isCatchMode = false;

    /**
     * @tc.steps: step2. call GetLongPressActionFunc function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    longPressRecognizer->AttachFrameNode(frameNode);
    longPressRecognizer->HandleOverdueDeadline(isCatchMode);
    longPressRecognizer->DoRepeat();
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::SUCCEED);
    auto result = longPressRecognizer->GetLongPressActionFunc();
}

/**
 * @tc.name: LongPressRecognizerTestGetLongPressActionFunc003
 * @tc.desc: Test LongPressRecognizer function: GetLongPressActionFunc
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerTestGetLongPressActionFunc003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    bool isCatchMode = false;

    /**
     * @tc.steps: step2. call GetLongPressActionFunc function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    longPressRecognizer->AttachFrameNode(frameNode);
    longPressRecognizer->HandleOverdueDeadline(isCatchMode);
    longPressRecognizer->DoRepeat();
    GestureEventFunc click;
    GestureEvent info;
    click = longPressRecognizer->GetLongPressActionFunc();
    click(info);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: LongPressRecognizerTestGetLongPressActionFunc004
 * @tc.desc: Test LongPressRecognizer function: GetLongPressActionFunc
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerTestGetLongPressActionFunc004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    bool isCatchMode = false;

    /**
     * @tc.steps: step2. call GetLongPressActionFunc function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    longPressRecognizer->AttachFrameNode(frameNode);
    longPressRecognizer->HandleOverdueDeadline(isCatchMode);
    longPressRecognizer->DoRepeat();
    GestureEventFunc click;
    GestureEvent info;
    auto onActionStart = [](GestureEvent& info) { return true; };
    auto onActionUpdate = [](GestureEvent& info) { return true; };
    auto onActionEnd = [](GestureEvent& info) { return true; };
    longPressRecognizer->SetOnActionUpdate(onActionUpdate);
    longPressRecognizer->SetOnAction(onActionStart);
    longPressRecognizer->SetOnActionEnd(onActionEnd);
    click = longPressRecognizer->GetLongPressActionFunc();
    click(info);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: LongPressRecognizerTestGetLongPressActionFunc002
 * @tc.desc: Test LongPressRecognizer function: GetLongPressActionFunc
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerTestGetLongPressActionFunc002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    bool isCatchMode = false;

    /**
     * @tc.steps: step2. call GetLongPressActionFunc function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer->fingers_ = SINGLE_FINGER_NUMBER;
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    longPressRecognizer->AttachFrameNode(frameNode);
    longPressRecognizer->HandleOverdueDeadline(isCatchMode);
    longPressRecognizer->DoRepeat();
    auto result = longPressRecognizer->GetLongPressActionFunc();
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call GetLongPressActionFunc function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->refereeState_ = RefereeState::DETECTING;
    longPressRecognizer->fingers_ = SINGLE_FINGER_NUMBER;
    longPressRecognizer->HandleOverdueDeadline(isCatchMode);
    longPressRecognizer->DoRepeat();
    result = longPressRecognizer->GetLongPressActionFunc();
    EXPECT_NE(longPressRecognizer->refereeState_, RefereeState::DETECTING);
}

/**
 * @tc.name: LongPressRecognizerConvertPxToVpTest001
 * @tc.desc: Test LongPressRecognizer function: ConvertPxToVp
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerConvertPxToVpTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call ConvertPxToVp function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    double result = longPressRecognizer->ConvertPxToVp(0.0);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: LongPressRecognizerTest007
 * @tc.desc: Test LongPressRecognizer function: HandleOverdueDeadline  DoRepeat
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    bool isCatchMode = false;

    /**
     * @tc.steps: step2. call HandleOverdueDeadline function and compare result.
     * @tc.steps: case1: refereeState is SUCCESS, return
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    longPressRecognizer->AttachFrameNode(frameNode);
    longPressRecognizer->HandleOverdueDeadline(isCatchMode);
    longPressRecognizer->DoRepeat();
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call HandleOverdueDeadline function and compare result.
     * @tc.steps: case1: refereeState is DETECTING, isCatchMode is false
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->refereeState_ = RefereeState::DETECTING;
    longPressRecognizer->HandleOverdueDeadline(isCatchMode);
    longPressRecognizer->DoRepeat();
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: LongPressRecognizerSendCallbackMsgTest001
 * @tc.desc: Test LongPressRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerSendCallbackMsgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create longPressRecognizer->
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    std::unique_ptr<GestureEventFunc> onAction;

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty, type is AXIS
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    longPressRecognizer->SendCallbackMsg(onAction, true, GestureCallbackType::START);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 0);
}

/**
 * @tc.name: LongPressGestureTest001
 * @tc.desc: Test LongPressGesture CreateRecognizer function
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressGestureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressGesture.
     */
    LongPressGestureModelNG longPressGestureModelNG;
    longPressGestureModelNG.Create(FINGER_NUMBER, false, LONG_PRESS_DURATION);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto longPressGestureNG = AceType::DynamicCast<NG::LongPressGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(longPressGestureNG->duration_, LONG_PRESS_DURATION);

    LongPressGesture longPressGesture = LongPressGesture(FINGER_NUMBER, false, LONG_PRESS_DURATION, false, false);
    EXPECT_EQ(longPressGesture.repeat_, false);
    EXPECT_EQ(longPressGesture.duration_, LONG_PRESS_DURATION);
    EXPECT_EQ(longPressGesture.isForDrag_, false);
    EXPECT_EQ(longPressGesture.isDisableMouseLeft_, false);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     */
    auto longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(longPressGesture.CreateRecognizer());
    EXPECT_NE(longPressRecognizer, nullptr);
    EXPECT_EQ(longPressRecognizer->repeat_, false);
    EXPECT_EQ(longPressRecognizer->duration_, LONG_PRESS_DURATION);
    EXPECT_EQ(longPressRecognizer->isForDrag_, false);
    EXPECT_EQ(longPressRecognizer->isDisableMouseLeft_, false);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case2: onActionId, onActionEndId, onActionCancelId existed
     */
    std::unique_ptr<GestureEventFunc> onActionId;
    std::unique_ptr<GestureEventFunc> onActionEndId;
    std::unique_ptr<GestureEventFunc> onActionCancelId;
    longPressGesture.onActionId_ = std::move(onActionId);
    longPressGesture.onActionEndId_ = std::move(onActionEndId);
    longPressGesture.onActionCancelId_ = std::move(onActionCancelId);
    longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(longPressGesture.CreateRecognizer());
    EXPECT_NE(longPressRecognizer, nullptr);
    EXPECT_EQ(longPressRecognizer->repeat_, false);
    EXPECT_EQ(longPressRecognizer->duration_, LONG_PRESS_DURATION);
    EXPECT_EQ(longPressRecognizer->isForDrag_, false);
    EXPECT_EQ(longPressRecognizer->isDisableMouseLeft_, false);
}

/**
 * @tc.name: LongPressGestureCreateRecognizerTest001
 * @tc.desc: Test LongPressGesture CreateRecognizer function
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressGestureCreateRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressGesture.
     */
    LongPressGestureModelNG longPressGestureModelNG;
    longPressGestureModelNG.Create(FINGER_NUMBER, false, LONG_PRESS_DURATION);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto longPressGestureNG = AceType::DynamicCast<NG::LongPressGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(longPressGestureNG->duration_, LONG_PRESS_DURATION);

    LongPressGesture longPressGesture = LongPressGesture(FINGER_NUMBER, false, LONG_PRESS_DURATION, false, false);
    EXPECT_EQ(longPressGesture.repeat_, false);
    EXPECT_EQ(longPressGesture.duration_, LONG_PRESS_DURATION);
    EXPECT_EQ(longPressGesture.isForDrag_, false);
    EXPECT_EQ(longPressGesture.isDisableMouseLeft_, false);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     */
    longPressGesture.fingers_ = FINGER_NUMBER_OVER_MAX;
    longPressGesture.duration_ = 0;
    auto longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(longPressGesture.CreateRecognizer());
    EXPECT_NE(longPressRecognizer, nullptr);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     */
    longPressGesture.fingers_ = 0;
    longPressGesture.duration_ = 0;
    longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(longPressGesture.CreateRecognizer());
    EXPECT_NE(longPressRecognizer, nullptr);
}


/**
 * @tc.name: LongPressGestureCreateRecognizerTest002
 * @tc.desc: Test LongPressGesture CreateRecognizer function
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressGestureCreateRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressGesture.
     */
    LongPressGestureModelNG longPressGestureModelNG;
    longPressGestureModelNG.Create(FINGER_NUMBER, false, LONG_PRESS_DURATION);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto longPressGestureNG = AceType::DynamicCast<NG::LongPressGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(longPressGestureNG->duration_, LONG_PRESS_DURATION);

    LongPressGesture longPressGesture = LongPressGesture(FINGER_NUMBER, false, LONG_PRESS_DURATION, false, false);
    EXPECT_EQ(longPressGesture.repeat_, false);
    EXPECT_EQ(longPressGesture.duration_, LONG_PRESS_DURATION);
    EXPECT_EQ(longPressGesture.isForDrag_, false);
    EXPECT_EQ(longPressGesture.isDisableMouseLeft_, false);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     */
    longPressGesture.fingers_ = FINGER_NUMBER_OVER_MAX;
    longPressGesture.duration_ = 0;
    auto onActionStart = [](GestureEvent& info) { return true; };
    auto onActionEnd = [](GestureEvent& info) { return true; };
    auto onActionCancel = [](GestureEvent& info) { return true; };
    longPressGesture.SetOnActionId(onActionStart);
    longPressGesture.SetOnActionEndId(onActionEnd);
    longPressGesture.SetOnActionCancelId(onActionCancel);
    auto longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(longPressGesture.CreateRecognizer());
    EXPECT_NE(longPressRecognizer, nullptr);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     */
    longPressGesture.fingers_ = 0;
    longPressGesture.duration_ = 0;
    longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(longPressGesture.CreateRecognizer());
    EXPECT_NE(longPressRecognizer, nullptr);
}

/**
 * @tc.name: LongPressRecognizerHandleTouchUpEventTest009
 * @tc.desc: Test LongPressRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerHandleTouchUpEventTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;

    longPressRecognizer->refereeState_ = RefereeState::DETECTING;
    longPressRecognizer->currentFingers_ = longPressRecognizer->fingers_;
    longPressRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->repeat_, false);
}

/**
 * @tc.name: LongPressRecognizerHandleTouchCancelEventTest001
 * @tc.desc: Test LongPressRecognizer function: HandleTouchCancelEvent
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerHandleTouchCancelEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;

    longPressRecognizer->refereeState_ = RefereeState::DETECTING;
    longPressRecognizer->currentFingers_ = longPressRecognizer->fingers_;
    longPressRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->repeat_, false);
}

/**
 * @tc.name: LongPressRecognizerHandleTouchDownEventTest001
 * @tc.desc: Test LongPressRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerHandleTouchDownEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;
    touchEvent.sourceType = SourceType::MOUSE;

    longPressRecognizer->refereeState_ = RefereeState::DETECTING;
    longPressRecognizer->isDisableMouseLeft_ = true;
    longPressRecognizer->currentFingers_ = longPressRecognizer->fingers_;
    longPressRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->repeat_, false);
}

/**
 * @tc.name: LongPressRecognizerHandleTouchMoveEventTest001
 * @tc.desc: Test LongPressRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerHandleTouchMoveEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;
    touchEvent.sourceType = SourceType::MOUSE;

    longPressRecognizer->refereeState_ = RefereeState::DETECTING;
    longPressRecognizer->isDisableMouseLeft_ = true;
    longPressRecognizer->currentFingers_ = longPressRecognizer->fingers_;
    longPressRecognizer->isForDrag_ = true;
    longPressRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->repeat_, false);

    longPressRecognizer->refereeState_ = RefereeState::DETECTING;
    longPressRecognizer->isDisableMouseLeft_ = false;
    longPressRecognizer->currentFingers_ = longPressRecognizer->fingers_;
    longPressRecognizer->isForDrag_ = false;
    longPressRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->repeat_, false);
}

/**
 * @tc.name: LongPressRecognizerHandleOverdueDeadlineTest001
 * @tc.desc: Test LongPressRecognizer function: HandleOverdueDeadline
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerHandleOverdueDeadlineTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;
    touchEvent.sourceType = SourceType::MOUSE;

    longPressRecognizer->refereeState_ = RefereeState::DETECTING;
    longPressRecognizer->HandleOverdueDeadline(true);
    EXPECT_EQ(longPressRecognizer->repeat_, false);
}

/**
 * @tc.name: LongPressRecognizerThumbnailTimerTest001
 * @tc.desc: Test ThumbnailTimer in LongPressRecognizer
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerThumbnailTimerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. set callback function.
     */
    auto callback = [](Offset offset) {};
    longPressRecognizer->callback_ = callback;
    longPressRecognizer->ThumbnailTimer(0);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: LongPressRecognizerTestGetLongPressActionFunc005
 * @tc.desc: Test LongPressRecognizer function: GetLongPressActionFunc
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerTestGetLongPressActionFunc005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);
    bool isCatchMode = false;
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer->HandleOverdueDeadline(isCatchMode);
    longPressRecognizer->DoRepeat();
    GestureEventFunc click;
    GestureEvent info;

    /**
     * @tc.steps: step2. call GetLongPressActionFunc function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    click = longPressRecognizer->GetLongPressActionFunc();
    click(info);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::SUCCEED);

    auto onActionStart = [](GestureEvent& info) { return true; };
    auto onActionUpdate = [](GestureEvent& info) { return true; };
    auto onActionEnd = [](GestureEvent& info) { return true; };
    longPressRecognizer->SetOnActionUpdate(onActionUpdate);
    longPressRecognizer->SetOnAction(onActionStart);
    longPressRecognizer->SetOnActionEnd(onActionEnd);
    click = longPressRecognizer->GetLongPressActionFunc();
    click(info);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: LongPressRecognizerTestGetLongPressActionFunc006
 * @tc.desc: Test LongPressRecognizer function: GetLongPressActionFunc
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerTestGetLongPressActionFunc006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);
    GestureEventFunc click;
    GestureEvent info;

    /**
     * @tc.steps: step2. call GetLongPressActionFunc function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    click = longPressRecognizer->GetLongPressActionFunc();
    click(info);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::READY);

    auto onActionStart = [](GestureEvent& info) { return true; };
    auto onActionUpdate = [](GestureEvent& info) { return true; };
    auto onActionEnd = [](GestureEvent& info) { return true; };
    longPressRecognizer->SetOnActionUpdate(onActionUpdate);
    longPressRecognizer->SetOnAction(onActionStart);
    longPressRecognizer->SetOnActionEnd(onActionEnd);
    click = longPressRecognizer->GetLongPressActionFunc();
    click(info);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: LongPressRecognizerHandleTouchUpEventTest001
 * @tc.desc: Test HandleTouchUpEvent in LongPressRecognizer
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerHandleTouchUpEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. set callback function.
     */
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer->currentFingers_ = longPressRecognizer->fingers_ + 1;
    auto callback = [](Offset offset) {};
    longPressRecognizer->callback_ = callback;
    longPressRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: LongPressRecognizerThumbnailTimerTest002
 * @tc.desc: Test ThumbnailTimer in LongPressRecognizer
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerThumbnailTimerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. set callback function.
     */
    auto callback = [](Offset offset) {};
    longPressRecognizer->callback_ = callback;
    longPressRecognizer->ThumbnailTimer(0);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: LongPressRecognizerTestGetLongPressActionFunc008
 * @tc.desc: Test LongPressRecognizer function: GetLongPressActionFunc
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerTestGetLongPressActionFunc008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);
    bool isCatchMode = false;
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer->HandleOverdueDeadline(isCatchMode);
    longPressRecognizer->DoRepeat();
    GestureEventFunc click;
    GestureEvent info;

    /**
     * @tc.steps: step2. call GetLongPressActionFunc function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    click = longPressRecognizer->GetLongPressActionFunc();
    click(info);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::SUCCEED);

    auto onActionStart = [](GestureEvent& info) { return true; };
    auto onActionUpdate = [](GestureEvent& info) { return true; };
    auto onActionEnd = [](GestureEvent& info) { return true; };
    longPressRecognizer->SetOnActionUpdate(onActionUpdate);
    longPressRecognizer->SetOnAction(onActionStart);
    longPressRecognizer->SetOnActionEnd(onActionEnd);
    click = longPressRecognizer->GetLongPressActionFunc();
    click(info);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: LongPressRecognizerTestGetLongPressActionFunc009
 * @tc.desc: Test LongPressRecognizer function: GetLongPressActionFunc
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerTestGetLongPressActionFunc009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);
    GestureEventFunc click;
    GestureEvent info;

    /**
     * @tc.steps: step2. call GetLongPressActionFunc function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    click = longPressRecognizer->GetLongPressActionFunc();
    click(info);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::READY);

    auto onActionStart = [](GestureEvent& info) { return true; };
    auto onActionUpdate = [](GestureEvent& info) { return true; };
    auto onActionEnd = [](GestureEvent& info) { return true; };
    longPressRecognizer->SetOnActionUpdate(onActionUpdate);
    longPressRecognizer->SetOnAction(onActionStart);
    longPressRecognizer->SetOnActionEnd(onActionEnd);
    click = longPressRecognizer->GetLongPressActionFunc();
    click(info);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: LongPressRecognizerHandleTouchUpEventTest002
 * @tc.desc: Test HandleTouchUpEvent in LongPressRecognizer
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerHandleTouchUpEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. set callback function.
     */
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer->currentFingers_ = longPressRecognizer->fingers_ + 1;
    auto callback = [](Offset offset) {};
    longPressRecognizer->callback_ = callback;
    longPressRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: GestureAccessibilityEventTest002
 * @tc.desc: Test SetOnAccessibility in LongPressRecognizer
 */
HWTEST_F(LongPressRecognizerTestNg, GestureAccessibilityEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create longPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. set callback function.
     */
    auto onAccessibilityEvent = [](AccessibilityEventType eventType) {};
    longPressRecognizer->SetOnAccessibility(onAccessibilityEvent);
    ASSERT_NE(longPressRecognizer->onAccessibilityEventFunc_, nullptr);

    /**
     * @tc.steps: step3. call callback function.
     * @tc.expected: refereeState_ is SUCCEED.
     */
    longPressRecognizer->OnAccepted();
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: LongPressRecognizerHandleOverdueDeadlineTest002
 * @tc.desc: Test LongPressRecognizer function: HandleOverdueDeadline
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerHandleOverdueDeadlineTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Recognizer、TargetComponent.
     */
    RefPtr<LongPressRecognizer> longPressRecognizerPtr = AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;};
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    PanDirection panDirection;
    targetComponent->SetOnGestureJudgeBegin(gestureJudgeFunc);
    longPressRecognizerPtr->targetComponent_ = targetComponent;
    longPressRecognizerPtr->targetComponent_->node_ = frameNode;
    TouchEvent touchEvent;
    touchEvent.tiltX.emplace(1.0f);
    touchEvent.tiltY.emplace(1.0f);
    longPressRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    /**
     * @tc.steps: step2. call HandleOverdueDeadline function and compare result.
     * @tc.steps: case1: gestureInfo_ is nullptr
     * @tc.expected: step2. result equals REJECT.
     */
    longPressRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    longPressRecognizerPtr->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    longPressRecognizerPtr->HandleOverdueDeadline(true);
    EXPECT_EQ(longPressRecognizerPtr->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step2. call HandleOverdueDeadline function and compare result.
     * @tc.steps: case2: gestureInfo_ is not nullptr, gestureInfo_->type_ = DRAG
     *                   isDragUserReject_ = true
     * @tc.expected: step2. result equals REJECT.
     */
    longPressRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    longPressRecognizerPtr->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    longPressRecognizerPtr->gestureInfo_->type_ = GestureTypeName::DRAG;
    guestureEventHub->dragEventActuator_ = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(guestureEventHub)), panDirection, 1, 50.0f);
    guestureEventHub->dragEventActuator_->isDragUserReject_ = true;
    longPressRecognizerPtr->HandleOverdueDeadline(true);
    EXPECT_EQ(longPressRecognizerPtr->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step2. call HandleOverdueDeadline function and compare result.
     * @tc.steps: case3: gestureInfo_ is not nullptr, gestureInfo_->type_ = DRAG
     *                   isDragUserReject_ = false
     * @tc.expected: step2. isDragUserReject_ = true.
     */
    longPressRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    guestureEventHub->dragEventActuator_->isDragUserReject_ = false;
    longPressRecognizerPtr->HandleOverdueDeadline(true);
    EXPECT_TRUE(guestureEventHub->dragEventActuator_->isDragUserReject_);
}

/**
 * @tc.name: LongPressRecognizerLongPressRecognizerTest
 * @tc.desc: Test LongPressRecognizer function: LongPressRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerLongPressRecognizerTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Recognizer、TargetComponent.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer1 =
        AceType::MakeRefPtr<LongPressRecognizer>(100, 9, false, false, false);
    RefPtr<LongPressRecognizer> longPressRecognizer2 =
        AceType::MakeRefPtr<LongPressRecognizer>(100, 11, false, false, false);
    RefPtr<LongPressRecognizer> longPressRecognizer3 =
        AceType::MakeRefPtr<LongPressRecognizer>(0, 10, false, false, false);
    EXPECT_EQ(longPressRecognizer1->fingers_, 9);
    EXPECT_EQ(longPressRecognizer2->fingers_, 1);
    EXPECT_EQ(longPressRecognizer3->duration_, 500);
}

/**
 * @tc.name: DeadlineTimerTest
 * @tc.desc: Test LongPressRecognizer function: DeadlineTimer
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, DeadlineTimerTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Recognizer、TargetComponent.
     */
    RefPtr<LongPressRecognizer> longPressRecognizerPtr = AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);
    longPressRecognizerPtr->DeadlineTimer(1, true);
    EXPECT_NE(longPressRecognizerPtr, nullptr);
}

/**
 * @tc.name: SetOnActionCancelTest001
 * @tc.desc: Test SendCallbackMsg function in the HandleTouchCancelEvent with touch event input. The onActionCancel
 * function will return GestureEvent info.
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, SetOnActionCancelTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. Call SetOnActionCancel.
     * @tc.expected: LongPressRecognizer's callback onActionCancel is not nullptr.
     */
    longPressRecognizer->deviceId_ = GESTURE_EVENT_PROPERTY_VALUE;
    float unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    auto onActionCancel = [&unknownPropertyValue](
                                GestureEvent& info) { unknownPropertyValue = info.GetDeviceId(); };
    longPressRecognizer->SetOnActionCancel(onActionCancel);
    
    EXPECT_NE(longPressRecognizer->onActionCancel_, nullptr);

    /**
     * @tc.steps: step3. Invoke HandleTouchCancelEvent when onActionCancel_ is not null.
     * @tc.expected: The functions have been executed and the unknownPropertyValue has been assigned the correct
     * value. LongPressRecognizer.refereeState_ = RefereeState::READY
     */
    TouchEvent touchEvent;
    longPressRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(unknownPropertyValue, 0);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: SetOnActionCancelTest002
 * @tc.desc: Test SendCallbackMsg function in the ReconcileFrom. The onActionCancel function will return
 * GestureEvent info.
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, SetOnActionCancelTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    RefPtr<LongPressRecognizer> longPressRecognizerPtr =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. Call SetOnActionCancel.
     * @tc.expected: LongPressRecognizer's callback onActionCancel is not nullptr.
     */
    longPressRecognizer->deviceId_ = GESTURE_EVENT_PROPERTY_VALUE;
    float unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    auto onActionCancel = [&unknownPropertyValue](
                                GestureEvent& info) { unknownPropertyValue = info.GetDeviceId(); };
    longPressRecognizer->SetOnActionCancel(onActionCancel);
    EXPECT_NE(longPressRecognizer->onActionCancel_, nullptr);

    /**
     * @tc.steps: step3. Invoke ReconcileFrom when onActionCancel_ is not null.
     * @tc.expected: The functions have been executed and the unknownPropertyValue has been assigned the correct
     * value.
     */
    TouchEvent touchEvent;
    longPressRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer->duration_ = 0;
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    auto result = longPressRecognizer->ReconcileFrom(longPressRecognizerPtr);
    EXPECT_EQ(unknownPropertyValue, 0);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: LongPressGestureLimitFingerTest001
 * @tc.desc: Test LongPressGesture CreateRecognizer function
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressGestureLimitFingerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressGesture.
     */
    LongPressGestureModelNG longPressGestureModelNG;
    longPressGestureModelNG.Create(FINGER_NUMBER, false, 0, IS_LIMIT_FINGER_COUNT);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto longPressGestureNG = AceType::DynamicCast<NG::LongPressGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(longPressGestureNG->isLimitFingerCount_, IS_LIMIT_FINGER_COUNT);

    LongPressGesture longPressGesture = LongPressGesture(
        FINGER_NUMBER, false, LONG_PRESS_DURATION, false, false, IS_LIMIT_FINGER_COUNT);
    EXPECT_EQ(longPressGesture.repeat_, false);
    EXPECT_EQ(longPressGesture.duration_, LONG_PRESS_DURATION);
    EXPECT_EQ(longPressGesture.isForDrag_, false);
    EXPECT_EQ(longPressGesture.isDisableMouseLeft_, false);
    EXPECT_EQ(longPressGesture.isLimitFingerCount_, true);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     */
    auto longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(longPressGesture.CreateRecognizer());
    EXPECT_NE(longPressRecognizer, nullptr);
    EXPECT_EQ(longPressRecognizer->repeat_, false);
    EXPECT_EQ(longPressRecognizer->duration_, LONG_PRESS_DURATION);
    EXPECT_EQ(longPressRecognizer->isForDrag_, false);
    EXPECT_EQ(longPressRecognizer->isDisableMouseLeft_, false);
    EXPECT_EQ(longPressRecognizer->isLimitFingerCount_, true);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case2: onActionId, onActionEndId, onActionCancelId existed
     */
    std::unique_ptr<GestureEventFunc> onActionId;
    std::unique_ptr<GestureEventFunc> onActionEndId;
    std::unique_ptr<GestureEventFunc> onActionCancelId;
    longPressGesture.onActionId_ = std::move(onActionId);
    longPressGesture.onActionEndId_ = std::move(onActionEndId);
    longPressGesture.onActionCancelId_ = std::move(onActionCancelId);
    longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(longPressGesture.CreateRecognizer());
    EXPECT_NE(longPressRecognizer, nullptr);
    EXPECT_EQ(longPressRecognizer->isLimitFingerCount_, true);
}

/**
 * @tc.name: LongPressGestureLimitFingerTest002
 * @tc.desc: Test LongPressGesture CreateRecognizer function
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressGestureLimitFingerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressGesture.
     */
    LongPressGestureModelNG longPressGestureModelNG;
    longPressGestureModelNG.Create(FINGER_NUMBER, false, 0, IS_NOT_LIMIT_FINGER_COUNT);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto longPressGestureNG = AceType::DynamicCast<NG::LongPressGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(longPressGestureNG->isLimitFingerCount_, IS_NOT_LIMIT_FINGER_COUNT);

    LongPressGesture longPressGesture = LongPressGesture(
        FINGER_NUMBER, false, LONG_PRESS_DURATION, false, false, IS_NOT_LIMIT_FINGER_COUNT);
    EXPECT_EQ(longPressGesture.repeat_, false);
    EXPECT_EQ(longPressGesture.duration_, LONG_PRESS_DURATION);
    EXPECT_EQ(longPressGesture.isForDrag_, false);
    EXPECT_EQ(longPressGesture.isDisableMouseLeft_, false);
    EXPECT_EQ(longPressGesture.isLimitFingerCount_, false);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     */
    auto longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(longPressGesture.CreateRecognizer());
    EXPECT_NE(longPressRecognizer, nullptr);
    EXPECT_EQ(longPressRecognizer->repeat_, false);
    EXPECT_EQ(longPressRecognizer->duration_, LONG_PRESS_DURATION);
    EXPECT_EQ(longPressRecognizer->isForDrag_, false);
    EXPECT_EQ(longPressRecognizer->isDisableMouseLeft_, false);
    EXPECT_EQ(longPressRecognizer->isLimitFingerCount_, false);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case2: onActionId, onActionEndId, onActionCancelId existed
     */
    std::unique_ptr<GestureEventFunc> onActionId;
    std::unique_ptr<GestureEventFunc> onActionEndId;
    std::unique_ptr<GestureEventFunc> onActionCancelId;
    longPressGesture.onActionId_ = std::move(onActionId);
    longPressGesture.onActionEndId_ = std::move(onActionEndId);
    longPressGesture.onActionCancelId_ = std::move(onActionCancelId);
    longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(longPressGesture.CreateRecognizer());
    EXPECT_NE(longPressRecognizer, nullptr);
    EXPECT_EQ(longPressRecognizer->isLimitFingerCount_, false);
}

/**
 * @tc.name: HandleTouchDownEvent001
 * @tc.desc: Test LongPressRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, HandleTouchDownEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: eventTimeStamp is greater than currentTimeStamp.
     * @tc.expected: step2. result equals.
     */
    auto eventTimeStamp = GetSysTimestamp() + DEFAULT_MOVE_TIME;
    touchEvent.time = TimeStamp(std::chrono::nanoseconds(eventTimeStamp));
    longPressRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::READY);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: isPostEventResult_ is true.
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->SetIsPostEventResult(true);
    longPressRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::READY);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: useCatchMode_ is false.
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::DOWN;
    longPressRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer->fingers_ = 1;
    longPressRecognizer->useCatchMode_ = false;
    longPressRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::DETECTING);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case4: forbiddenType is TouchRestrict::LONG_PRESS.
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->touchRestrict_.forbiddenType = TouchRestrict::LONG_PRESS;
    longPressRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->disposal_, GestureDisposal::REJECT);
}

/**
 * @tc.name: HandleTouchUpEventTest001
 * @tc.desc: Test LongPressRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, HandleTouchUpEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case1: refereeState_ is not SUCCEED.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    longPressRecognizer->fingersId_.insert(0);
    longPressRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->fingersId_.size(), 0);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case2: refereeState_ is SUCCEED.
     * @tc.expected: step2. result equals.
     */
    TimeStamp timeStape = std::chrono::high_resolution_clock::now();
    longPressRecognizer->firstInputTime_ = timeStape;
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer->isLimitFingerCount_ = true;
    longPressRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 0);
    EXPECT_FALSE(longPressRecognizer->hasRepeated_);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case3: fingers_ is 1.
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->fingers_ = 1;
    longPressRecognizer->touchPoints_[1] = touchEvent;
    longPressRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 1);
}

/**
 * @tc.name: HandleTouchMoveEventTest001
 * @tc.desc: Test LongPressRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, HandleTouchMoveEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case1: referee is not SUCCEED.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    TouchEvent event;
    touchEvent.x = 100.0f;;
    touchEvent.y = 100.0f;;
    longPressRecognizer->touchPoints_[event.id] = event;
    longPressRecognizer->fingers_ = 0;
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->disposal_, GestureDisposal::NONE);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case2: referee is READY.
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->refereeState_ = RefereeState::READY;
    longPressRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->disposal_, GestureDisposal::REJECT);
}

/**
 * @tc.name: HandleTouchCancelEventTest001
 * @tc.desc: Test LongPressRecognizer function: HandleTouchCancelEvent
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, HandleTouchCancelEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call HandleTouchCancelEvent function and compare result.
     * @tc.steps: case1: referee is FAIL.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    TouchEvent event;
    event.id = 1;
    longPressRecognizer->touchPoints_[event.id] = event;
    longPressRecognizer->refereeState_ = RefereeState::FAIL;
    longPressRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->extraInfo_, "");
    EXPECT_EQ(longPressRecognizer->disposal_, GestureDisposal::NONE);

    /**
     * @tc.steps: step2. call HandleTouchCancelEvent function and compare result.
     * @tc.steps: case2: referee is SUCCEED.
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->extraInfo_, TEST_EXTRA_INFO);
    EXPECT_EQ(longPressRecognizer->disposal_, GestureDisposal::REJECT);
}

/**
 * @tc.name: DoRepeatTest001
 * @tc.desc: Test LongPressRecognizer function: DoRepeat
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, DoRepeatTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call DoRepeat function and compare result.
     * @tc.steps: case1: isLimitFingerCount_ is false.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    longPressRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer->fingers_ = 0;
    longPressRecognizer->DoRepeat();
    longPressRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call DoRepeat function and compare result.
     * @tc.steps: case2: isLimitFingerCount_ is true.
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->isLimitFingerCount_ = true;
    longPressRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer->DoRepeat();
    longPressRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 1);
}

/**
 * @tc.name: SendCallbackMsgTest001
 * @tc.desc: Test LongPressRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, SendCallbackMsgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case1: longPressRecorder is yes, *longPressRecorder is no.
     * @tc.expected: step2. result equals.
     */
    bool isRepeat = false;
    TouchEvent touchEvent;
    std::unique_ptr<GestureEventFunc> onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    std::unique_ptr<GestureEventFunc> longPressRecorder = std::make_unique<GestureEventFunc>();;
    touchEvent.rollAngle = 0;
    longPressRecognizer->lastTouchEvent_ = touchEvent;
    longPressRecognizer->longPressRecorder_ = std::move(longPressRecorder);
    longPressRecognizer->SendCallbackMsg(onAction, isRepeat, GestureCallbackType::START);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case2: longPressRecorder is yes, *longPressRecorder is yes.
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->longPressRecorder_ = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    longPressRecognizer->SendCallbackMsg(onAction, isRepeat, GestureCallbackType::START);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: gestureInfo_ is not nullptr.
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    longPressRecognizer->SendCallbackMsg(onAction, isRepeat, GestureCallbackType::START);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: gestureInfo_ is not nullptr, gestureInfo_->disposeTag_ is true.
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->gestureInfo_->SetDisposeTag(true);
    longPressRecognizer->SendCallbackMsg(onAction, isRepeat, GestureCallbackType::START);
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 0);
}

/**
 * @tc.name: TriggerGestureJudgeCallbackTest001
 * @tc.desc: Test LongPressRecognizer function: TriggerGestureJudgeCallback
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, TriggerGestureJudgeCallbackTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;
    };
    auto func = [](const std::shared_ptr<BaseGestureEvent>& info, const RefPtr<NGGestureRecognizer>& current,
                    const std::list<RefPtr<NGGestureRecognizer>>& others) { return GestureJudgeResult::REJECT; };

    /**
     * @tc.steps: step2. call TriggerGestureJudgeCallback function and compare result.
     * @tc.steps: case1: targetComponent is default.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    touchEvent.rollAngle = 0;
    longPressRecognizer->touchPoints_[0] = touchEvent;
    longPressRecognizer->targetComponent_ = targetComponent;
    GestureJudgeResult result = longPressRecognizer->TriggerGestureJudgeCallback();
    EXPECT_EQ(result, GestureJudgeResult::CONTINUE);

    /**
     * @tc.steps: step2. call TriggerGestureJudgeCallback function and compare result.
     * @tc.steps: case2: gestureRecognizerJudgeFunc is not null.
     * @tc.expected: step2. result equals.
     */
    targetComponent->SetOnGestureRecognizerJudgeBegin(func);
    result = longPressRecognizer->TriggerGestureJudgeCallback();
    EXPECT_EQ(result, GestureJudgeResult::REJECT);

    /**
     * @tc.steps: step2. call TriggerGestureJudgeCallback function and compare result.
     * @tc.steps: case3: callback is not null.
     * @tc.expected: step2. result equals.
     */
    targetComponent->SetOnGestureJudgeBegin(gestureJudgeFunc);
    result = longPressRecognizer->TriggerGestureJudgeCallback();
    EXPECT_EQ(result, GestureJudgeResult::REJECT);
}

/**
 * @tc.name: HandleOverdueDeadlineTest001
 * @tc.desc: Test LongPressRecognizer function: HandleOverdueDeadline
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, HandleOverdueDeadlineTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Recognizer、TargetComponent.
     */
    RefPtr<LongPressRecognizer> longPressRecognizerPtr = AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call HandleOverdueDeadline function and compare result.
     * @tc.steps: case: limitFingerCount is true.
     * @tc.expected: step2. result equals REJECT.
     */
    bool isCatchMode = true;
    TouchEvent touchEvent;
    longPressRecognizerPtr->SetLimitFingerCount(true);
    longPressRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    longPressRecognizerPtr->HandleOverdueDeadline(isCatchMode);
    EXPECT_EQ(longPressRecognizerPtr->disposal_, GestureDisposal::REJECT);
}

/**
 * @tc.name: ReconcileFromTest001
 * @tc.desc: Test LongPressRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, ReconcileFromTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    RefPtr<LongPressRecognizer> longPressRecognizerPtr =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case: referee is SUCCEED.
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->duration_ = 0;
    longPressRecognizer->refereeState_ = RefereeState::SUCCEED;
    bool result = longPressRecognizer->ReconcileFrom(longPressRecognizerPtr);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ThumbnailTimerTest001
 * @tc.desc: Test LongPressRecognizer function: ThumbnailTimer
 */
HWTEST_F(LongPressRecognizerTestNg, ThumbnailTimerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call ThumbnailTimer function and compare result.
     * @tc.steps: case1: taskExecutor is not null.
     * @tc.expected: step2. result equals.
     */
    int32_t time = 0;
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    auto callback = [](Offset offset) {};
    longPressRecognizer->callback_ = callback;
    longPressRecognizer->ThumbnailTimer(time);
    EXPECT_EQ(longPressRecognizer->refereeState_, RefereeState::READY);

    /**
     * @tc.steps: step2. call ThumbnailTimer function and compare result.
     * @tc.steps: case2: referee is DETECTING.
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer->refereeState_ = RefereeState::DETECTING;
    longPressRecognizer->ThumbnailTimer(time);
    EXPECT_EQ(longPressRecognizer->globalPoint_.GetX(), 0);
    EXPECT_EQ(longPressRecognizer->globalPoint_.GetY(), 0);
}

/**
 * @tc.name: StartRepeatTimerTest001
 * @tc.desc: Test LongPressRecognizer function: StartRepeatTimer
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, StartRepeatTimerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call StartRepeatTimer function and compare result.
     * @tc.steps: case: taskExecutor is not null.
     * @tc.expected: step2. result equals.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    longPressRecognizer->StartRepeatTimer();
    EXPECT_EQ(longPressRecognizer->touchPoints_.size(), 0);
}
/**
 * @tc.name: GetOnAccessibilityEventFunc001
 * @tc.desc: Test LongPressRecognizer function: GetOnAccessibilityEventFunc
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, GetOnAccessibilityEventFunc001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. check callback function.
     * @tc.expected: callback function is not null.
     */
    ASSERT_NE(longPressRecognizer->onAccessibilityEventFunc_, nullptr);
}

/**
 * @tc.name: LongPressRecognizerBasicInfoTest001
 * @tc.desc: Test case basic input info check.
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerBasicInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create basic info testCases.
     * @tc.expected: set longPressRecognizer basic info correct.
     */
    const std::vector<MockLongPressRecognizerCase> mockLongPressRecognizerCases = {
        {1, DEFAULT_LONGPRESS_DURATION, DEFAULT_LONGPRESS_DURATION, RefereeState::READY,
            1, DEFAULT_LONGPRESS_DURATION, RefereeState::READY, {}},
        {1, -1, DEFAULT_LONGPRESS_DURATION, RefereeState::READY,
            1, DEFAULT_LONGPRESS_DURATION, RefereeState::READY, {}},
        {-1, DEFAULT_LONGPRESS_DURATION, DEFAULT_LONGPRESS_DURATION, RefereeState::READY,
            1, DEFAULT_LONGPRESS_DURATION, RefereeState::READY, {}},
    };
    for (auto i = 0; i < mockLongPressRecognizerCases.size(); i++) {
        RefPtr<LongPressRecognizer> longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(
            mockLongPressRecognizerCases[i].duration, mockLongPressRecognizerCases[i].fingers);
        longPressRecognizer->refereeState_ = mockLongPressRecognizerCases[i].refereeState;
        EXPECT_EQ(longPressRecognizer->duration_, mockLongPressRecognizerCases[i].expectedDuration);
        EXPECT_EQ(longPressRecognizer->fingers_, mockLongPressRecognizerCases[i].expectedFingers);
        EXPECT_EQ(longPressRecognizer->refereeState_, mockLongPressRecognizerCases[i].expectedRefereeState);
    }
}
 
/**
 * @tc.name: LongPressRecognizerInjectEventsTest001
 * @tc.desc: Test case inject events.
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerInjectEventsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create basic info testCases.
     * @tc.expected: set clickRecognizer basic info correct.
     */
    TouchEvent downEvent = TouchEvent();
    downEvent.type = TouchType::DOWN;
    TouchEvent moveEvent = TouchEvent();
    moveEvent.type = TouchType::MOVE;
    TouchEvent upEvent = TouchEvent();
    upEvent.type = TouchType::UP;
 
    const std::vector<MockLongPressRecognizerCase> mockLongPressRecognizerCases = {
        {1, DEFAULT_LONGPRESS_DURATION, DEFAULT_LONGPRESS_DURATION, RefereeState::READY,
            1, DEFAULT_LONGPRESS_DURATION, RefereeState::DETECTING, {downEvent}},
        {1, DEFAULT_LONGPRESS_DURATION, DEFAULT_LONGPRESS_DURATION, RefereeState::READY,
            1, DEFAULT_LONGPRESS_DURATION, RefereeState::DETECTING, {downEvent, moveEvent}},
        {1, -1, DEFAULT_LONGPRESS_DURATION, RefereeState::READY,
            1, DEFAULT_LONGPRESS_DURATION, RefereeState::FAIL, {downEvent, moveEvent, upEvent}},
        {-1, DEFAULT_LONGPRESS_DURATION, DEFAULT_LONGPRESS_DURATION, RefereeState::READY,
            1, DEFAULT_LONGPRESS_DURATION, RefereeState::FAIL, {downEvent, moveEvent, upEvent}},
    };
    for (auto i = 0; i < mockLongPressRecognizerCases.size(); i++) {
        RefPtr<LongPressRecognizer> longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(
            mockLongPressRecognizerCases[i].duration, mockLongPressRecognizerCases[i].fingers, true);
        longPressRecognizer->refereeState_ = mockLongPressRecognizerCases[i].refereeState;
        for (auto j = 0; j < mockLongPressRecognizerCases[i].inputTouchEvents.size(); j++) {
            longPressRecognizer->ProcessTouchEvent(mockLongPressRecognizerCases[i].inputTouchEvents[j]);
            std::this_thread::sleep_for(std::chrono::milliseconds(mockLongPressRecognizerCases[i].time));
        }
        EXPECT_EQ(longPressRecognizer->duration_, mockLongPressRecognizerCases[i].expectedDuration);
        EXPECT_EQ(longPressRecognizer->fingers_, mockLongPressRecognizerCases[i].expectedFingers);
        EXPECT_EQ(longPressRecognizer->refereeState_, mockLongPressRecognizerCases[i].expectedRefereeState);
    }
}
 
/**
 * @tc.name: LongPressRecognizerInjectEventsTest002
 * @tc.desc: Test case inject events.
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerTestNg, LongPressRecognizerInjectEventsTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create basic info testCases.
     * @tc.expected: set clickRecognizer basic info correct.
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
 
    const std::vector<MockLongPressRecognizerCase> mockLongPressRecognizerCases = {
        {2, DEFAULT_LONGPRESS_DURATION, DEFAULT_LONGPRESS_DURATION, RefereeState::READY,
            2, DEFAULT_LONGPRESS_DURATION, RefereeState::DETECTING, {downEventFinger0, downEventFinger1}},
        {2, DEFAULT_LONGPRESS_DURATION, DEFAULT_LONGPRESS_DURATION, RefereeState::READY, 2, DEFAULT_LONGPRESS_DURATION,
            RefereeState::DETECTING, {downEventFinger0, downEventFinger1, moveEventFinger0, moveEventFinger1}},
        {2, DEFAULT_LONGPRESS_DURATION, DEFAULT_LONGPRESS_DURATION, RefereeState::READY,
            2, DEFAULT_LONGPRESS_DURATION, RefereeState::FAIL,
            {downEventFinger0, downEventFinger1, moveEventFinger0, moveEventFinger1, upEventFinger0, upEventFinger1}},
        {2, -1, DEFAULT_LONGPRESS_DURATION, RefereeState::READY, 2, DEFAULT_LONGPRESS_DURATION, RefereeState::FAIL,
            {downEventFinger0, downEventFinger1, moveEventFinger0, moveEventFinger1, upEventFinger0, upEventFinger1}},
        {-1, DEFAULT_LONGPRESS_DURATION, DEFAULT_LONGPRESS_DURATION, RefereeState::READY,
            1, DEFAULT_LONGPRESS_DURATION, RefereeState::FAIL,
            {downEventFinger0, downEventFinger1, moveEventFinger0, moveEventFinger1, upEventFinger0, upEventFinger1}},
    };
    for (auto i = 0; i < mockLongPressRecognizerCases.size(); i++) {
        RefPtr<LongPressRecognizer> longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(
            mockLongPressRecognizerCases[i].duration, mockLongPressRecognizerCases[i].fingers, false);
        longPressRecognizer->refereeState_ = mockLongPressRecognizerCases[i].refereeState;
        for (auto j = 0; j < mockLongPressRecognizerCases[i].inputTouchEvents.size(); j++) {
            longPressRecognizer->ProcessTouchEvent(mockLongPressRecognizerCases[i].inputTouchEvents[j]);
            std::this_thread::sleep_for(std::chrono::milliseconds(mockLongPressRecognizerCases[i].time));
        }
        EXPECT_EQ(longPressRecognizer->duration_, mockLongPressRecognizerCases[i].expectedDuration);
        EXPECT_EQ(longPressRecognizer->fingers_, mockLongPressRecognizerCases[i].expectedFingers);
        EXPECT_EQ(longPressRecognizer->refereeState_, mockLongPressRecognizerCases[i].expectedRefereeState);
    }
}
} // namespace OHOS::Ace::NG