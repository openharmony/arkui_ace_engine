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
namespace {
constexpr double DEFAULT_DOUBLE_50 = 50.0;
constexpr double DEFAULT_DOUBLE_100 = 100.0;

struct MockClickRecognizerCase {
    int32_t fingers;
    int32_t count;
    Dimension distanceThreshold;
    double moveDistance;
    RefereeState refereeState;
    int32_t expectedFingers;
    int32_t expectedCount;
    Dimension expectedDistanceThreshold;
    RefereeState expectedRefereeState;
    std::vector<TouchEvent> inputTouchEvents;
};
} // namespace

class ClickRecognizerTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void ClickRecognizerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void ClickRecognizerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: GestureRecognizerTest001
 * @tc.desc: Test ClickRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case1: onClick and remoteMessage is no
     * @tc.expected: step2. result equals.
     */
    ClickCallback onClick;
    clickRecognizer->onClick_ = onClick;
    ClickCallback remoteMessage;
    clickRecognizer->remoteMessage_ = remoteMessage;

    clickRecognizer->OnAccepted();
    EXPECT_EQ(clickRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case2: onClick and remoteMessage is yes, touchPoints is empty
     * @tc.expected: step2. result equals.
     */
    onClick = [](ClickInfo) {};
    clickRecognizer->onClick_ = onClick;
    clickRecognizer->touchPoints_.clear();
    remoteMessage = [](ClickInfo) {};
    clickRecognizer->remoteMessage_ = remoteMessage;

    clickRecognizer->OnAccepted();
    EXPECT_EQ(clickRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case3: onClick and remoteMessage is yes, touchPoints is not empty
     * @tc.expected: step2. result equals.
     */
    onClick = [](ClickInfo) {};
    clickRecognizer->onClick_ = onClick;
    clickRecognizer->touchPoints_.clear();
    remoteMessage = [](ClickInfo) {};
    clickRecognizer->remoteMessage_ = remoteMessage;
    TouchEvent touchEvent;
    clickRecognizer->touchPoints_[0] = touchEvent;

    clickRecognizer->OnAccepted();
    EXPECT_EQ(clickRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case4: onClick and remoteMessage is yes, touchPoints has tiltX and tiltY
     * @tc.expected: step2. result equals.
     */
    onClick = [](ClickInfo) {};
    clickRecognizer->onClick_ = onClick;
    clickRecognizer->touchPoints_.clear();
    remoteMessage = [](ClickInfo) {};
    clickRecognizer->remoteMessage_ = remoteMessage;
    touchEvent.tiltX = 0;
    touchEvent.tiltY = 0;
    clickRecognizer->touchPoints_[0] = touchEvent;

    clickRecognizer->OnAccepted();
    EXPECT_EQ(clickRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.expected: step3. result equals.
     */
    clickRecognizer->OnRejected();
    EXPECT_EQ(clickRecognizer->refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: GestureRecognizerTest002
 * @tc.desc: Test ClickRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case2: refereeState is SUCCESS,return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer->refereeState_ = RefereeState::SUCCEED;
    clickRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->fingers_ = FINGER_NUMBER_OVER_MAX;
    clickRecognizer->touchPoints_.clear();
    clickRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    clickRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->disposal_, GestureDisposal::NONE);
}

/**
 * @tc.name: GestureRecognizerTest003
 * @tc.desc: Test ClickRecognizer function: ComputeFocusPoint
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call ComputeFocusPoint function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer->touchPoints_.clear();
    clickRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    auto focusPoint = clickRecognizer->ComputeFocusPoint();
    EXPECT_EQ(focusPoint.GetX(), 0);
    EXPECT_EQ(focusPoint.GetY(), 0);
}

/**
 * @tc.name: GestureRecognizerTest004
 * @tc.desc: Test ClickRecognizer function: ExceedSlop
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call ComputeFocusPoint function and compare result.
     * @tc.steps: case1: not enter
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer->touchPoints_.clear();
    clickRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    auto result = clickRecognizer->ExceedSlop();
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ComputeFocusPoint function and compare result.
     * @tc.steps: case2: tappedCount_ > 0 && tappedCount_ < count_, distance >= TAP_SLOP
     * @tc.expected: step2. result equals.
     */
    touchEvent.x = CLICK_MULTI_TAP_SLOP;
    touchEvent.y = CLICK_MULTI_TAP_SLOP;
    clickRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    clickRecognizer->tappedCount_ = TAPPED_COUNT;
    clickRecognizer->count_ = COUNT;
    result = clickRecognizer->ExceedSlop();
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ComputeFocusPoint function and compare result.
     * @tc.steps: case3: tappedCount_ > 0 && tappedCount_ < count_, distance < TAP_SLOP
     * @tc.expected: step2. result equals.
     */
    touchEvent.x = 0;
    touchEvent.y = 0;
    clickRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    clickRecognizer->tappedCount_ = TAPPED_COUNT;
    clickRecognizer->count_ = COUNT;
    result = clickRecognizer->ExceedSlop();
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ComputeFocusPoint function and compare result.
     * @tc.steps: case4: tappedCount_ = count_ = 0
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->tappedCount_ = 0;
    clickRecognizer->count_ = 0;
    result = clickRecognizer->ExceedSlop();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: GestureRecognizerTest005
 * @tc.desc: Test ClickRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer->touchPoints_.clear();
    clickRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    auto result = clickRecognizer->ReconcileFrom(clickRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is nullptr
     * @tc.expected: step2. result equals.
     */
    result = clickRecognizer->ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case3: recognizerPtr count != count
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->count_ = 1;
    clickRecognizer->count_ = 0;
    result = clickRecognizer->ReconcileFrom(clickRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case4: recognizerPtr count same, fingers not same
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->count_ = clickRecognizer->count_;
    clickRecognizerPtr->fingers_ = clickRecognizer->fingers_ + 1;
    result = clickRecognizer->ReconcileFrom(clickRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case5: recognizerPtr count same, fingers same, priorityMask not same
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->count_ = clickRecognizer->count_;
    clickRecognizerPtr->fingers_ = clickRecognizer->fingers_;
    clickRecognizer->priorityMask_ = GestureMask::End;
    result = clickRecognizer->ReconcileFrom(clickRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: GestureRecognizerTest006
 * @tc.desc: Test ClickRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: refereeState is SUCCESS,return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer->refereeState_ = RefereeState::SUCCEED;
    clickRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: refereeState is PENDING, tappedCount_ = 1, fingers > PointsNum
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->refereeState_ = RefereeState::PENDING;
    clickRecognizer->fingers_ = FINGER_NUMBER;
    clickRecognizer->tappedCount_ = 1;
    clickRecognizer->currentTouchPointsNum_ = 0;
    clickRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->currentTouchPointsNum_, 1);
    EXPECT_EQ(clickRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: refereeState is PENDING, tappedCount_ = 1, fingers = 1
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->refereeState_ = RefereeState::PENDING;
    clickRecognizer->fingers_ = 1;
    clickRecognizer->tappedCount_ = 1;
    clickRecognizer->currentTouchPointsNum_ = 0;
    clickRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->equalsToFingers_, false);
}

/**
 * @tc.name: GestureRecognizerTest007
 * @tc.desc: Test ClickRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case1: refereeState is SUCCESS,return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer->currentTouchPointsNum_ = 0;
    clickRecognizer->refereeState_ = RefereeState::SUCCEED;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case2: equalsToFingers = true, currentTouchPointsNum = 1, tap != count
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->useCatchMode_ = false;
    clickRecognizer->refereeState_ = RefereeState::PENDING;
    clickRecognizer->fingersId_.insert(0);
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_FALSE(clickRecognizer->equalsToFingers_);
    EXPECT_EQ(clickRecognizer->currentTouchPointsNum_, 0);
    EXPECT_EQ(clickRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case3: equalsToFingers = true, currentTouchPointsNum = 1,
     * @tc.steps: tap == count, useCatchMode_ = false
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->useCatchMode_ = false;
    clickRecognizer->tappedCount_ = 0;
    clickRecognizer->count_ = 0;
    clickRecognizer->fingersId_.insert(0);
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_FALSE(clickRecognizer->equalsToFingers_);
    EXPECT_EQ(clickRecognizer->currentTouchPointsNum_, 0);
    EXPECT_EQ(clickRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case3: equalsToFingers = true, currentTouchPointsNum = fingers,
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = FINGER_NUMBER;
    clickRecognizer->fingers_ = FINGER_NUMBER;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->equalsToFingers_, true);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case4: equalsToFingers = false, currentTouchPointsNum = 1,
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = false;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->equalsToFingers_, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case5: equalsToFingers = false, currentTouchPointsNum = 0,
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = 0;
    clickRecognizer->equalsToFingers_ = false;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->equalsToFingers_, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case6: equalsToFingers = true, currentTouchPointsNum = 1,
     * @tc.steps: tap == count, useCatchMode_ = false
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->useCatchMode_ = false;
    clickRecognizer->tappedCount_ = -1;
    clickRecognizer->count_ = 0;
    clickRecognizer->fingersId_.insert(0);
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->equalsToFingers_, true);
    EXPECT_EQ(clickRecognizer->currentTouchPointsNum_, 0);
    EXPECT_EQ(clickRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
}

/**
 * @tc.name: GestureRecognizerTest008
 * @tc.desc: Test ClickRecognizer function: HandleTouchCancelEvent
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case1: refereeState is SUCCESS,return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer->currentTouchPointsNum_ = 0;
    clickRecognizer->refereeState_ = RefereeState::SUCCEED;
    clickRecognizer->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->touchPoints_.size(), 0);

    clickRecognizer->refereeState_ = RefereeState::FAIL;
}

/**
 * @tc.name: GestureRecognizerTest009
 * @tc.desc: Test ClickRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case1: onAction is no, *onAction is no
     * @tc.expected: step2. result equals.
     */
    std::unique_ptr<GestureEventFunc> onAction;
    clickRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(clickRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case2: onAction is yes, *onAction is no
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>();
    clickRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(clickRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    clickRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(clickRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    clickRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(clickRecognizer->touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    touchEvent.tiltX = 0.0f;
    touchEvent.tiltY = 0.0f;
    clickRecognizer->touchPoints_[touchEvent.id] = touchEvent;
    clickRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(clickRecognizer->touchPoints_.size(), 1);
}

/**
 * @tc.name: GestureRecognizerTest010
 * @tc.desc: Test ClickRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: event.sourceType == TOUCH
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->refereeState_ = RefereeState::PENDING;
    clickRecognizer->fingers_ = FINGER_NUMBER;
    clickRecognizer->tappedCount_ = 1;
    clickRecognizer->currentTouchPointsNum_ = 0;
    touchEvent.sourceType = SourceType::TOUCH;
    clickRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->currentTouchPointsNum_, 1);
    EXPECT_EQ(clickRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: event.sourceType == MOUSE
     * @tc.expected: step2. result equals.
     */
    touchEvent.sourceType = SourceType::MOUSE;
    clickRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: event.sourceType == TOUCH_PAD
     * @tc.expected: step2. result equals.
     */
    touchEvent.sourceType = SourceType::TOUCH_PAD;
    clickRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.step4: case3: event.sourceType == OTHER
     * @tc.expected: step2. result equals.
     */
    touchEvent.sourceType = SourceType::KEYBOARD;
    clickRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
}

/*
 * @tc.name: GestureRecognizerTest011
 * @tc.desc: Test ClickRecognizer function: IsPointInRegion
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    clickRecognizer->AttachFrameNode(frameNode);
    clickRecognizer->responseRegionBuffer_.emplace_back(RectF(0, 0, 200, 200));
    clickRecognizer->SetDistanceThreshold(200);
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call IsInResponseRegion function and compare result.
     * @tc.steps: case1: event.sourceType == TOUCH, x == 100, y == 100
     * @tc.expected: step2. result equals.
     */
    touchEvent.x = 100.0f;
    touchEvent.y = 100.0f;
    touchEvent.sourceType = SourceType::TOUCH;
    auto result = clickRecognizer->IsPointInRegion(touchEvent);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: ClickRecognizerTest012
 * @tc.desc: Test ClickRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case1: refereeState is SUCCESS,return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer->currentTouchPointsNum_ = 0;
    clickRecognizer->refereeState_ = RefereeState::SUCCEED;
    clickRecognizer->currentFingers_ = FINGER_NUMBER;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case2: equalsToFingers = true, currentTouchPointsNum = 1, tap != count
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->useCatchMode_ = false;
    clickRecognizer->refereeState_ = RefereeState::PENDING;
    clickRecognizer->currentFingers_ = FINGER_NUMBER;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case3: equalsToFingers = true, currentTouchPointsNum = 1,
     * @tc.steps: tap == count, useCatchMode_ = false
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->useCatchMode_ = false;
    clickRecognizer->tappedCount_ = 0;
    clickRecognizer->count_ = 0;
    clickRecognizer->currentFingers_ = FINGER_NUMBER;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case3: equalsToFingers = true, currentTouchPointsNum = fingers,
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = FINGER_NUMBER;
    clickRecognizer->fingers_ = FINGER_NUMBER;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->currentFingers_ = FINGER_NUMBER;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->equalsToFingers_, true);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case4: equalsToFingers = false, currentTouchPointsNum = 1,
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = false;
    clickRecognizer->currentFingers_ = FINGER_NUMBER;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->equalsToFingers_, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case5: equalsToFingers = false, currentTouchPointsNum = 0,
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = 0;
    clickRecognizer->equalsToFingers_ = false;
    clickRecognizer->currentFingers_ = FINGER_NUMBER;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->equalsToFingers_, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case6: equalsToFingers = true, currentTouchPointsNum = 1,
     * @tc.steps: tap == count, useCatchMode_ = false
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->useCatchMode_ = false;
    clickRecognizer->tappedCount_ = -1;
    clickRecognizer->count_ = 0;
    clickRecognizer->currentFingers_ = FINGER_NUMBER;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
}

/**
 * @tc.name: ClickRecognizerTest013
 * @tc.desc: Test GestureRecognizer function: HandleEvent
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureRecognizer.
     */
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizer->refereeState_ = RefereeState::SUCCEED;
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call TouchEvent function and compare result.
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::MOVE;
    clickRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->refereeState_, RefereeState::SUCCEED);

    touchEvent.type = TouchType::DOWN;
    clickRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->refereeState_, RefereeState::SUCCEED);

    touchEvent.type = TouchType::UP;
    clickRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->refereeState_, RefereeState::SUCCEED);

    touchEvent.type = TouchType::CANCEL;
    clickRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->refereeState_, RefereeState::SUCCEED);

    touchEvent.type = TouchType::UNKNOWN;
    clickRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(clickRecognizer->inputEventType_, InputEventType::TOUCH_SCREEN);

    /**
     * @tc.steps: step2. call AxisEvent function and compare result.
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    axisEvent.action = AxisAction::BEGIN;
    clickRecognizer->HandleEvent(axisEvent);
    EXPECT_EQ(clickRecognizer->refereeState_, RefereeState::SUCCEED);

    axisEvent.action = AxisAction::UPDATE;
    clickRecognizer->HandleEvent(axisEvent);
    EXPECT_EQ(clickRecognizer->refereeState_, RefereeState::SUCCEED);

    axisEvent.action = AxisAction::END;
    clickRecognizer->HandleEvent(axisEvent);
    EXPECT_EQ(clickRecognizer->refereeState_, RefereeState::SUCCEED);

    axisEvent.action = AxisAction::NONE;
    clickRecognizer->HandleEvent(axisEvent);
    EXPECT_EQ(clickRecognizer->refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(clickRecognizer->inputEventType_, InputEventType::AXIS);
}

/**
 * @tc.name: GestureRecognizerTest014
 * @tc.desc: Test ClickRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case7: equalsToFingers = true, currentTouchPointsNum = 1,
     * @tc.steps: tap != count, useCatchMode_ = false, refereeState = DETECTING.
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->useCatchMode_ = false;
    clickRecognizer->tappedCount_ = 0;
    clickRecognizer->count_ = 1;
    clickRecognizer->fingersId_.insert(0);
    clickRecognizer->refereeState_ = RefereeState::DETECTING;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case7: equalsToFingers = false, currentTouchPointsNum = 1,
     * @tc.steps: tap != count, useCatchMode_ = false, refereeState = DETECTING.
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->useCatchMode_ = false;
    clickRecognizer->tappedCount_ = 0;
    clickRecognizer->count_ = 1;
    clickRecognizer->fingersId_.insert(0);
    clickRecognizer->refereeState_ = RefereeState::DETECTING;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: ClickRecognizerHandleTouchUpEventTest101
 * @tc.desc: Test ClickRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerHandleTouchUpEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case1: refereeState is SUCCESS,return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer->currentTouchPointsNum_ = 0;
    clickRecognizer->refereeState_ = RefereeState::SUCCEED;
    clickRecognizer->currentTouchPointsNum_ = clickRecognizer->fingers_;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case2: equalsToFingers = true, currentTouchPointsNum = 1, tap != count
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->useCatchMode_ = false;
    clickRecognizer->refereeState_ = RefereeState::PENDING;
    clickRecognizer->currentTouchPointsNum_ = clickRecognizer->fingers_;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_TRUE(clickRecognizer->equalsToFingers_);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case3: equalsToFingers = true, currentTouchPointsNum = 1,
     * @tc.steps: tap == count, useCatchMode_ = false
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->useCatchMode_ = false;
    clickRecognizer->tappedCount_ = 0;
    clickRecognizer->count_ = 0;
    clickRecognizer->currentTouchPointsNum_ = clickRecognizer->fingers_;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_TRUE(clickRecognizer->equalsToFingers_);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case3: equalsToFingers = true, currentTouchPointsNum = fingers,
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = FINGER_NUMBER;
    clickRecognizer->fingers_ = FINGER_NUMBER;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->currentTouchPointsNum_ = clickRecognizer->fingers_;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->equalsToFingers_, true);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case4: equalsToFingers = false, currentTouchPointsNum = 1,
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = false;
    clickRecognizer->currentTouchPointsNum_ = clickRecognizer->fingers_;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->equalsToFingers_, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case5: equalsToFingers = false, currentTouchPointsNum = 0,
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = 0;
    clickRecognizer->equalsToFingers_ = false;
    clickRecognizer->currentTouchPointsNum_ = clickRecognizer->fingers_;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->equalsToFingers_, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case6: equalsToFingers = true, currentTouchPointsNum = 1,
     * @tc.steps: tap == count, useCatchMode_ = false
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->useCatchMode_ = false;
    clickRecognizer->tappedCount_ = -1;
    clickRecognizer->count_ = 0;
    clickRecognizer->currentTouchPointsNum_ = clickRecognizer->fingers_;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->equalsToFingers_, true);
}

/**
 * @tc.name: GestureRecognizerHandleTouchMoveEventTest001
 * @tc.desc: Test ClickRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, GestureRecognizerHandleTouchMoveEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case1: refereeState is SUCCESS,return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer->currentTouchPointsNum_ = 0;
    clickRecognizer->refereeState_ = RefereeState::SUCCEED;
    clickRecognizer->currentFingers_ = FINGER_NUMBER;
    clickRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->touchPoints_.size(), 0);
}

/**
 * @tc.name: ClickRecognizerHandleTouchUpEventTest102
 * @tc.desc: Test ClickRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerHandleTouchUpEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case1: refereeState is SUCCESS,return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer->currentTouchPointsNum_ = 0;
    clickRecognizer->refereeState_ = RefereeState::SUCCEED;
    clickRecognizer->currentFingers_ = FINGER_NUMBER;
    clickRecognizer->currentTouchPointsNum_ = clickRecognizer->fingers_;
    clickRecognizer->HandleTouchUpEvent(touchEvent);

    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->useCatchMode_ = false;
    clickRecognizer->refereeState_ = RefereeState::PENDING;
    clickRecognizer->currentFingers_ = FINGER_NUMBER;
    clickRecognizer->currentTouchPointsNum_ = clickRecognizer->fingers_;
    clickRecognizer->HandleTouchUpEvent(touchEvent);

    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->useCatchMode_ = false;
    clickRecognizer->tappedCount_ = 0;
    clickRecognizer->count_ = 0;
    clickRecognizer->currentFingers_ = FINGER_NUMBER;
    clickRecognizer->currentTouchPointsNum_ = clickRecognizer->fingers_;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case3: equalsToFingers = true, currentTouchPointsNum = fingers,
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = FINGER_NUMBER;
    clickRecognizer->fingers_ = FINGER_NUMBER;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->currentFingers_ = FINGER_NUMBER;
    clickRecognizer->currentTouchPointsNum_ = clickRecognizer->fingers_;

    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = false;
    clickRecognizer->currentFingers_ = FINGER_NUMBER;
    clickRecognizer->currentTouchPointsNum_ = clickRecognizer->fingers_;

    clickRecognizer->currentTouchPointsNum_ = 0;
    clickRecognizer->equalsToFingers_ = false;
    clickRecognizer->currentFingers_ = FINGER_NUMBER;
    clickRecognizer->currentTouchPointsNum_ = clickRecognizer->fingers_;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->equalsToFingers_, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case6: equalsToFingers = true, currentTouchPointsNum = 1,
     * @tc.steps: tap == count, useCatchMode_ = false
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->useCatchMode_ = false;
    clickRecognizer->tappedCount_ = -1;
    clickRecognizer->count_ = 0;
    clickRecognizer->currentFingers_ = FINGER_NUMBER;
    clickRecognizer->currentTouchPointsNum_ = clickRecognizer->fingers_;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->touchPoints_[touchEvent.id].id, touchEvent.id);
}

/**
 * @tc.name: GestureRecognizerHandleOverdueDeadlineTest001
 * @tc.desc: Test ClickRecognizer function: HandleOverdueDeadline
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, GestureRecognizerHandleOverdueDeadlineTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case1: refereeState is SUCCESS,return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer->currentTouchPointsNum_ = FINGER_NUMBER;
    clickRecognizer->refereeState_ = RefereeState::SUCCEED;
    clickRecognizer->currentFingers_ = FINGER_NUMBER;
    clickRecognizer->tappedCount_ = FINGER_NUMBER;
    clickRecognizer->count_ = FINGER_NUMBER;
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    clickRecognizer->AttachFrameNode(frameNode);
    clickRecognizer->HandleOverdueDeadline();
    EXPECT_EQ(clickRecognizer->touchPoints_.size(), 0);
}

/**
 * @tc.name: ClickRecognizerClickRecognizerTest101
 * @tc.desc: Test ClickRecognizer function: ClickRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerClickRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr1 = AceType::MakeRefPtr<ClickRecognizer>(0, COUNT);
    EXPECT_EQ(clickRecognizerPtr1->fingers_, 1);

    /**
     * @tc.steps: step1. create ClickRecognizer
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER_OVER_MAX, COUNT);
    EXPECT_EQ(clickRecognizerPtr2->fingers_, 1);

    /**
     * @tc.steps: step1. create ClickRecognizer
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr3 = AceType::MakeRefPtr<ClickRecognizer>(10, COUNT);
    EXPECT_EQ(clickRecognizerPtr3->fingers_, 10);

    /**
     * @tc.steps: step1. create ClickRecognizer
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr4 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    EXPECT_EQ(clickRecognizerPtr4->fingers_, FINGER_NUMBER);
}

/**
 * @tc.name: ClickRecognizerSendCallbackMsgTest001
 * @tc.desc: Test ClickRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerSendCallbackMsgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create clickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(SINGLE_FINGER_NUMBER, TAPPED_COUNT);
    std::unique_ptr<GestureEventFunc> onAction;

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty, type is AXIS
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    clickRecognizer->SendCallbackMsg(onAction, GestureCallbackType::ACTION);
    EXPECT_EQ(clickRecognizer->touchPoints_.size(), 0);
}

/**
 * @tc.name: ClickRecognizerHandleTouchMoveEventTest002
 * @tc.desc: Test ClickRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerHandleTouchMoveEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case2: refereeState is SUCCESS,return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer->refereeState_ = RefereeState::PENDING;
    clickRecognizer->currentFingers_ = clickRecognizer->fingers_;
    clickRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->touchPoints_.size(), 0);
}

/**
 * @tc.name: ClickRecognizerHandleTouchDownEventTest003
 * @tc.desc: Test ClickRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerHandleTouchDownEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;
    touchEvent.sourceType = SourceType::MOUSE;

    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    clickRecognizerPtr->fingers_ = 0;
    clickRecognizerPtr->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);
}

/**
 * @tc.name: ClickRecognizerHandleOverdueDeadlineTest001
 * @tc.desc: Test HandleOverdueDeadline in ClickRecognizer
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerHandleOverdueDeadlineTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create clickRecognizerPtr.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. set HandleOverdueDeadline function.
     */
    clickRecognizerPtr->currentTouchPointsNum_ = clickRecognizerPtr->fingers_ - 1;
    clickRecognizerPtr->HandleOverdueDeadline();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step2. set HandleOverdueDeadline function.
     */
    clickRecognizerPtr->currentTouchPointsNum_ = clickRecognizerPtr->fingers_;
    clickRecognizerPtr->tappedCount_ = clickRecognizerPtr->count_ - 1;
    clickRecognizerPtr->HandleOverdueDeadline();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: ClickRecognizerExceedSlopTest001
 * @tc.desc: Test ExceedSlop in ClickRecognizer
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerExceedSlopTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create clickRecognizerPtr.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    TouchEvent touchEvent;

    clickRecognizerPtr->tappedCount_ = -1;
    clickRecognizerPtr->ExceedSlop();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);
    clickRecognizerPtr->tappedCount_ = 1;
    clickRecognizerPtr->count_ = 0;
    clickRecognizerPtr->ExceedSlop();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);
    clickRecognizerPtr->tappedCount_ = 1;
    clickRecognizerPtr->count_ = 2;
    clickRecognizerPtr->ExceedSlop();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: ClickRecognizerHandleTouchCancelEventTest001
 * @tc.desc: Test HandleTouchCancelEvent in ClickRecognizer
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerHandleTouchCancelEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create clickRecognizerPtr.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    TouchEvent touchEvent;

    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    clickRecognizerPtr->HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: ClickRecognizerHandleOverdueDeadlineTest002
 * @tc.desc: Test HandleOverdueDeadline in ClickRecognizer
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerHandleOverdueDeadlineTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create clickRecognizerPtr.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. set HandleOverdueDeadline function.
     */
    clickRecognizerPtr->currentTouchPointsNum_ = clickRecognizerPtr->fingers_ - 1;
    clickRecognizerPtr->HandleOverdueDeadline();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step2. set HandleOverdueDeadline function.
     */
    clickRecognizerPtr->currentTouchPointsNum_ = clickRecognizerPtr->fingers_;
    clickRecognizerPtr->tappedCount_ = clickRecognizerPtr->count_ - 1;
    clickRecognizerPtr->HandleOverdueDeadline();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: ClickRecognizerHandleOverdueDeadlineTest012
 * @tc.desc: Test HandleOverdueDeadline in ClickRecognizer
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerHandleOverdueDeadlineTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create clickRecognizerPtr.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. set HandleOverdueDeadline function.
     */
    clickRecognizerPtr->AttachFrameNode(nullptr);

    PointF f1 = PointF(1.0, 0.0);
    NGGestureRecognizer::Transform(f1, clickRecognizerPtr->GetAttachedNode());
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: ClickRecognizerHandleOverdueDeadlineTest013
 * @tc.desc: Test HandleOverdueDeadline in ClickRecognizer
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerHandleOverdueDeadlineTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create clickRecognizerPtr.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. set HandleOverdueDeadline function.
     */
    clickRecognizerPtr->AttachFrameNode(nullptr);

    PointF f1 = PointF(1.0, 0.0);
    NGGestureRecognizer::Transform(f1, clickRecognizerPtr->GetAttachedNode());
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: ClickRecognizerHandleOverdueDeadlineTest014
 * @tc.desc: Test HandleOverdueDeadline in ClickRecognizer
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerHandleOverdueDeadlineTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create clickRecognizerPtr.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. set HandleOverdueDeadline function.
     */
    clickRecognizerPtr->AttachFrameNode(nullptr);

    PointF f1 = PointF(1.0, 0.0);
    NGGestureRecognizer::Transform(f1, clickRecognizerPtr->GetAttachedNode());
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: GestureAccessibilityEventTest001
 * @tc.desc: Test SetOnAccessibility in ClickRecognizer
 */
HWTEST_F(ClickRecognizerTestNg, GestureAccessibilityEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create clickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(SINGLE_FINGER_NUMBER, TAPPED_COUNT);

    /**
     * @tc.steps: step2. set callback function.
     */
    auto onAccessibilityEvent = [](AccessibilityEventType eventType) {};
    clickRecognizer->SetOnAccessibility(onAccessibilityEvent);
    ASSERT_NE(clickRecognizer->onAccessibilityEventFunc_, nullptr);

    /**
     * @tc.steps: step3. call callback function.
     * @tc.expected: refereeState_ is SUCCEED.
     */
    clickRecognizer->OnAccepted();
    EXPECT_EQ(clickRecognizer->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: ClickRecognizerHandleTouchUpEvent001
 * @tc.desc: Test ClickRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerHandleTouchUpEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and set Recognizer、TargetComponent.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    DimensionRect area;
    DimensionOffset origin;
    EventTarget target = { "", "", area, origin };
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;
    };
    targetComponent->SetOnGestureJudgeBegin(gestureJudgeFunc);
    TouchEvent touchEvent;
    touchEvent.tiltX.emplace(1.0f);
    touchEvent.tiltY.emplace(1.0f);
    clickRecognizerPtr->targetComponent_ = targetComponent;
    /**
     * @tc.steps: step2. test the function who calls TriggerGestureJudgeCallback.
     * @tc.expected: step2. result equals REJECT.
     */
    clickRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    clickRecognizerPtr->currentTouchPointsNum_ = 1;
    clickRecognizerPtr->equalsToFingers_ = true;
    clickRecognizerPtr->useCatchMode_ = true;
    clickRecognizerPtr->tappedCount_ = -1;
    clickRecognizerPtr->count_ = 0;
    clickRecognizerPtr->fingersId_.insert(0);
    clickRecognizerPtr->SetIsSystemGesture(false);
    clickRecognizerPtr->gestureInfo_->SetTag("test");
    clickRecognizerPtr->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizerPtr->disposal_, GestureDisposal::REJECT);
}

/**
 * @tc.name: ClickRecognizerHandleTouchUpEvent002
 * @tc.desc: Test ClickRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerHandleTouchUpEvent002, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizer->refereeState_ = RefereeState::SUCCEED;
    clickRecognizer->currentFingers_ = 0;
    clickRecognizer->CleanRecognizerState();
    clickRecognizer->refereeState_ = RefereeState::FAIL;
    clickRecognizer->currentFingers_ = 0;
    clickRecognizer->CleanRecognizerState();
    clickRecognizer->refereeState_ = RefereeState::DETECTING;
    clickRecognizer->currentFingers_ = 0;
    clickRecognizer->CleanRecognizerState();
    clickRecognizer->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    clickRecognizer->currentFingers_ = 0;
    clickRecognizer->CleanRecognizerState();
    clickRecognizer->refereeState_ = RefereeState::DETECTING;
    clickRecognizer->currentFingers_ = 1;
    clickRecognizer->CleanRecognizerState();
    clickRecognizer->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    clickRecognizer->currentFingers_ = 1;
    clickRecognizer->CleanRecognizerState();
    EXPECT_EQ(clickRecognizer->refereeState_, RefereeState::SUCCEED_BLOCKED);
}

/**
 * @tc.name: ClickEventRecordTest001
 * @tc.desc: test RecordClickEventIfNeed.
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickEventRecordTest001, TestSize.Level1)
{
    int32_t componentIndex = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_COMPONENT);
    int32_t rectIndex = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_RECT);
    Recorder::EventRecorder::Get().eventSwitch_[componentIndex] = true;
    Recorder::EventRecorder::Get().eventSwitch_[rectIndex] = true;
    Recorder::EventRecorder::Get().globalSwitch_[componentIndex] = true;
    Recorder::EventRecorder::Get().globalSwitch_[rectIndex] = true;
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    GestureEvent info = GestureEvent();
    clickRecognizer->RecordClickEventIfNeed(info);
    EXPECT_TRUE(clickRecognizer->GetAttachedNode().Upgrade() == nullptr);
}

/**
 * @tc.name: TapGestureLimit001
 * @tc.desc: Test TapGesture with isFingerCountLimited
 */

HWTEST_F(ClickRecognizerTestNg, TapGestureLimit001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TapGestureGesture.
     */
    TapGestureModelNG tapGestureModelNG;
    tapGestureModelNG.Create(COUNT, FINGER_NUMBER, 10, IS_LIMIT_FINGER_COUNT);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto tapGestureNG = AceType::DynamicCast<NG::TapGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(tapGestureNG->isLimitFingerCount_, IS_LIMIT_FINGER_COUNT);

    TapGesture tapGesture = TapGesture(COUNT, FINGER_NUMBER, 10, IS_LIMIT_FINGER_COUNT);
    EXPECT_EQ(tapGesture.isLimitFingerCount_, IS_LIMIT_FINGER_COUNT);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: compare isLimitFingerCount_
     */
    tapGesture.priority_ = GesturePriority::Low;
    tapGesture.gestureMask_ = GestureMask::Normal;
    auto tapRecognizer = AceType::DynamicCast<ClickRecognizer>(tapGesture.CreateRecognizer());
    EXPECT_EQ(tapRecognizer->isLimitFingerCount_, IS_LIMIT_FINGER_COUNT);
}

/**
 * @tc.name: TapGestureLimit002
 * @tc.desc: Test TapGesture with isFingerCountLimited
 */

HWTEST_F(ClickRecognizerTestNg, TapGestureLimit002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TapGestureGesture.
     */
    TapGestureModelNG tapGestureModelNG;
    tapGestureModelNG.Create(COUNT, FINGER_NUMBER, 10, IS_NOT_LIMIT_FINGER_COUNT);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto tapGestureNG = AceType::DynamicCast<NG::TapGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(tapGestureNG->isLimitFingerCount_, IS_NOT_LIMIT_FINGER_COUNT);

    TapGesture tapGesture = TapGesture(COUNT, FINGER_NUMBER, 10, IS_NOT_LIMIT_FINGER_COUNT);
    EXPECT_EQ(tapGesture.isLimitFingerCount_, IS_NOT_LIMIT_FINGER_COUNT);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: compare isLimitFingerCount_
     */
    tapGesture.priority_ = GesturePriority::Low;
    tapGesture.gestureMask_ = GestureMask::Normal;
    auto tapRecognizer = AceType::DynamicCast<ClickRecognizer>(tapGesture.CreateRecognizer());
    EXPECT_EQ(tapRecognizer->isLimitFingerCount_, IS_NOT_LIMIT_FINGER_COUNT);
}

/**
 * @tc.name: HandleTouchUpEventTest001
 * @tc.desc: Test HandleTouchUpEvent
 */
HWTEST_F(ClickRecognizerTestNg, HandleTouchUpEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case1: refereeState is READY.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer->currentTouchPointsNum_ = 1;
    clickRecognizer->equalsToFingers_ = true;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->disposal_, GestureDisposal::PENDING);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case2: touchEvent.sourceType is SourceType::MOUSE.
     * @tc.expected: step2. result equals.
     */
    touchEvent.sourceType = SourceType::MOUSE;
    clickRecognizer->HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer->disposal_, GestureDisposal::PENDING);

    /**
     * @tc.steps: step3. call AboutToAddToPendingRecognizers function and compare result.
     * @tc.steps: case1: refereeState is PENDING_BLOCKED.
     * @tc.expected: step3. result equals.
     */
    clickRecognizer->refereeState_ = RefereeState::PENDING_BLOCKED;
    clickRecognizer->AboutToAddToPendingRecognizers(touchEvent);
    EXPECT_EQ(clickRecognizer->disposal_, GestureDisposal::PENDING);

    /**
     * @tc.steps: step3. call AboutToAddToPendingRecognizers function and compare result.
     * @tc.steps: case2: refereeState is PENDING.
     * @tc.expected: step3. result equals.
     */
    clickRecognizer->refereeState_ = RefereeState::PENDING;
    clickRecognizer->AboutToAddToPendingRecognizers(touchEvent);
    EXPECT_EQ(clickRecognizer->disposal_, GestureDisposal::PENDING);
}

/*
 * @tc.name: IsPointInRegionTest001
 * @tc.desc: Test IsPointInRegion
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, IsPointInRegionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT, 0);
    auto frameNode = FrameNode::CreateFrameNode("myButton", 0, AceType::MakeRefPtr<Pattern>());
    TouchEvent touchEvent;
    double distanceThreshold = 1.0;

    /**
     * @tc.steps: step2. call IsPointInRegion function and compare result.
     * @tc.steps: case1: distanceThreshold is 1.0.
     * @tc.expected: step2. result equals.
     */
    touchEvent.SetScreenX(DEFAULT_DOUBLE_100);
    touchEvent.SetScreenY(DEFAULT_DOUBLE_100);
    clickRecognizer->SetDistanceThreshold(distanceThreshold);
    bool result = clickRecognizer->IsPointInRegion(touchEvent);
    EXPECT_FALSE(result);
    EXPECT_EQ(clickRecognizer->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step2. call IsPointInRegion function and compare result.
     * @tc.steps: case2: distanceThreshold is 0.0.
     * @tc.expected: step2. result equals.
     */
    distanceThreshold = 0.0;
    clickRecognizer->SetDistanceThreshold(distanceThreshold);
    clickRecognizer->AttachFrameNode(frameNode);
    result = clickRecognizer->IsPointInRegion(touchEvent);
    EXPECT_FALSE(result);
}

/*
 * @tc.name: GetClickInfoTest001
 * @tc.desc: Test GetClickInfo
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, GetClickInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    auto frameNode = FrameNode::CreateFrameNode("myButton", 0, AceType::MakeRefPtr<Pattern>());
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call GetClickInfo function and compare result.
     * @tc.steps: case: rollAngle has value.
     * @tc.expected: step2. result equals.
     */
    touchEvent.rollAngle = 0;
    clickRecognizer->AttachFrameNode(frameNode);
    clickRecognizer->touchPoints_[0] = touchEvent;
    ClickInfo result = clickRecognizer->GetClickInfo();
    EXPECT_EQ(result.GetPatternName(), "myButton");
    EXPECT_EQ(result.GetRollAngle(), 0);
}

/*
 * @tc.name: IsFormRenderClickRejectedTest001
 * @tc.desc: Test IsFormRenderClickRejected
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, IsFormRenderClickRejectedTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    TouchEvent touchEvent;
    TouchEvent testTouchEvent;

    /**
     * @tc.steps: step2. call IsFormRenderClickRejected function and compare result.
     * @tc.steps: case1: touchEvent is default.
     * @tc.expected: step2. result is false.
     */
    bool result = clickRecognizer->IsFormRenderClickRejected(touchEvent);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step2. call IsFormRenderClickRejected function and compare result.
     * @tc.steps: case2: touchEvent is not default.
     * @tc.expected: step2. result is true.
     */
    touchEvent.SetScreenX(DEFAULT_DOUBLE_100);
    touchEvent.SetScreenY(DEFAULT_DOUBLE_100);
    testTouchEvent.SetScreenX(DEFAULT_DOUBLE_50);
    testTouchEvent.SetScreenY(DEFAULT_DOUBLE_50);
    clickRecognizer->touchPoints_[0] = testTouchEvent;
    result = clickRecognizer->IsFormRenderClickRejected(touchEvent);
    EXPECT_TRUE(result);
}

/*
 * @tc.name: GetGestureEventInfoTest001
 * @tc.desc: Test GetGestureEventInfo
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, GetGestureEventInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    auto frameNode = FrameNode::CreateFrameNode("myButton", 0, AceType::MakeRefPtr<Pattern>());
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call GetGestureEventInfo function and compare result.
     * @tc.steps: case: touchEvent is not default.
     * @tc.expected: step2. result equals.
     */
    touchEvent.sourceType = SourceType::MOUSE;
    touchEvent.SetTiltX(0);
    touchEvent.SetTiltY(0);
    touchEvent.rollAngle = 0;
    touchEvent.convertInfo.first = UIInputEventType::AXIS;
    touchEvent.convertInfo.second = UIInputEventType::TOUCH;
    clickRecognizer->AttachFrameNode(frameNode);
    clickRecognizer->touchPoints_[0] = touchEvent;
    GestureEvent result = clickRecognizer->GetGestureEventInfo();
    EXPECT_EQ(result.GetPatternName(), "myButton");
    EXPECT_EQ(result.GetTiltX(), 0);
    EXPECT_EQ(result.GetTiltY(), 0);
    EXPECT_EQ(result.GetRollAngle(), 0);
    EXPECT_EQ(result.GetOriginUIInputEventType(), UIInputEventType::AXIS);
    EXPECT_EQ(result.GetCurrentUIInputEventType(), UIInputEventType::TOUCH);
}

/**
 * @tc.name: TriggerGestureJudgeCallbackTest001
 * @tc.desc: Test TriggerGestureJudgeCallback
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, TriggerGestureJudgeCallbackTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;
    };
    auto func = [](const std::shared_ptr<BaseGestureEvent>& info, const RefPtr<NGGestureRecognizer>& current,
                    const std::list<RefPtr<NGGestureRecognizer>>& others) { return GestureJudgeResult::REJECT; };
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call TriggerGestureJudgeCallback function and compare result.
     * @tc.steps: case1: targetComponent is default.
     * @tc.expected: step2. result equals.
     */
    touchEvent.rollAngle = 0;
    clickRecognizer->touchPoints_[0] = touchEvent;
    clickRecognizer->targetComponent_ = targetComponent;
    GestureJudgeResult result = clickRecognizer->TriggerGestureJudgeCallback();
    EXPECT_EQ(result, GestureJudgeResult::CONTINUE);

    /**
     * @tc.steps: step2. call TriggerGestureJudgeCallback function and compare result.
     * @tc.steps: case2: gestureRecognizerJudgeFunc is not null.
     * @tc.expected: step2. result equals.
     */
    targetComponent->SetOnGestureRecognizerJudgeBegin(func);
    result = clickRecognizer->TriggerGestureJudgeCallback();
    EXPECT_EQ(result, GestureJudgeResult::REJECT);

    /**
     * @tc.steps: step2. call TriggerGestureJudgeCallback function and compare result.
     * @tc.steps: case3: sysJudge_ is not null.
     * @tc.expected: step2. result equals.
     */
    clickRecognizer->sysJudge_ = gestureJudgeFunc;
    result = clickRecognizer->TriggerGestureJudgeCallback();
    EXPECT_EQ(result, GestureJudgeResult::REJECT);
}

/**
 * @tc.name: TriggerGestureJudgeCallbackTest003
 * @tc.desc: Test TriggerGestureJudgeCallback
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, TriggerGestureJudgeCallbackTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(2, COUNT, 0, true);
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;
    };
    auto func = [](const std::shared_ptr<BaseGestureEvent>& info, const RefPtr<NGGestureRecognizer>& current,
                    const std::list<RefPtr<NGGestureRecognizer>>& others) { return GestureJudgeResult::REJECT; };
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call TriggerGestureJudgeCallback function and compare result.
     * @tc.steps: case1: targetComponent is default.
     * @tc.expected: step2. result equals.
     */

    targetComponent->SetOnGestureRecognizerJudgeBegin(func);
    touchEvent.rollAngle = 0;
    clickRecognizer->touchPoints_[0] = touchEvent;
    clickRecognizer->touchPoints_[1] = touchEvent;
    clickRecognizer->touchPoints_[2] = touchEvent;
    clickRecognizer->targetComponent_ = targetComponent;
    clickRecognizer->TriggerClickAccepted(touchEvent);
    targetComponent->SetOnGestureJudgeBegin(gestureJudgeFunc);
    EXPECT_EQ(clickRecognizer->disposal_, GestureDisposal::REJECT);
}

/**
 * @tc.name: OnAcceptedTest001
 * @tc.desc: Test OnAccepted
 */
HWTEST_F(ClickRecognizerTestNg, OnAcceptedTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create clickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, TAPPED_COUNT);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.expected: result equals.
     */
    TimeStamp timeStape = std::chrono::high_resolution_clock::now();
    clickRecognizer->firstInputTime_ = timeStape;
    clickRecognizer->OnAccepted();
    EXPECT_FALSE(clickRecognizer->firstInputTime_.has_value());
}

/**
 * @tc.name: UpdateInfoWithDownEventTest001
 * @tc.desc: Test UpdateInfoWithDownEvent
 */
HWTEST_F(ClickRecognizerTestNg, UpdateInfoWithDownEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create clickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, TAPPED_COUNT);
    auto frameNode = FrameNode::CreateFrameNode("myButton", 0, AceType::MakeRefPtr<Pattern>());
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call UpdateInfoWithDownEvent function and compare result.
     * @tc.expected: result equals.
     */
    clickRecognizer->AttachFrameNode(frameNode);
    clickRecognizer->UpdateInfoWithDownEvent(touchEvent);
    EXPECT_FALSE(clickRecognizer->equalsToFingers_);
}


/**
 * @tc.name: ClickRecognizerBasicInfoTest001
 * @tc.desc: Test case basic input info check.
 * @tc.type: FUNC
 */
 HWTEST_F(ClickRecognizerTestNg, ClickRecognizerBasicInfoTest001, TestSize.Level1)
 {
    /**
      * @tc.steps: step1. Create basic info testCases.
      * @tc.expected: set clickRecognizer basic info correct.
      */
    const std::vector<MockClickRecognizerCase> mockClickRecognizerCases = {
        {1, 1, Dimension(std::numeric_limits<double>::infinity()), 1, RefereeState::READY, 1, 1,
            Dimension(std::numeric_limits<double>::infinity()), RefereeState::READY, {}},
        {-1, 1, Dimension(std::numeric_limits<double>::infinity()), 1, RefereeState::READY, 1, 1,
            Dimension(std::numeric_limits<double>::infinity()), RefereeState::READY, {}},
        {1, -1, Dimension(std::numeric_limits<double>::infinity()), 1, RefereeState::READY, 1, -1,
            Dimension(std::numeric_limits<double>::infinity()), RefereeState::READY, {}},
        {1, 1, Dimension(-1), 1, RefereeState::READY, 1, 1,
            Dimension(std::numeric_limits<double>::infinity()), RefereeState::READY, {}}
    };
    for (auto i = 0; i < mockClickRecognizerCases.size(); i++) {
        RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(
            mockClickRecognizerCases[i].fingers, mockClickRecognizerCases[i].count,
            mockClickRecognizerCases[i].distanceThreshold);
        clickRecognizer->refereeState_ = mockClickRecognizerCases[i].refereeState;
        EXPECT_EQ(clickRecognizer->fingers_, mockClickRecognizerCases[i].expectedFingers);
        EXPECT_EQ(clickRecognizer->count_, mockClickRecognizerCases[i].expectedCount);
        EXPECT_EQ(clickRecognizer->distanceThreshold_.ConvertToPx(),
            mockClickRecognizerCases[i].expectedDistanceThreshold.ConvertToPx());
        EXPECT_EQ(clickRecognizer->refereeState_, mockClickRecognizerCases[i].expectedRefereeState);
    }
}

/**
 * @tc.name: ClickRecognizerInjectEventsTest001
 * @tc.desc: Test case inject events.
 * @tc.type: FUNC
 */
 HWTEST_F(ClickRecognizerTestNg, ClickRecognizerInjectEventsTest001, TestSize.Level1)
 {
    /**
      * @tc.steps: step1. Create basic info testCases.
      * @tc.expected: set clickRecognizer basic info correct.
      */
    TouchEvent downEvent = TouchEvent();
    downEvent.type = TouchType::DOWN;
    TouchEvent upEvent = TouchEvent();
    upEvent.type = TouchType::UP;

    const std::vector<MockClickRecognizerCase> mockClickRecognizerCases = {
        {1, 1, Dimension(std::numeric_limits<double>::infinity()), 1, RefereeState::READY, 1, 1,
            Dimension(std::numeric_limits<double>::infinity()), RefereeState::SUCCEED, {downEvent, upEvent}},
        {-1, 1, Dimension(std::numeric_limits<double>::infinity()), 1, RefereeState::READY, 1, 1,
            Dimension(std::numeric_limits<double>::infinity()), RefereeState::SUCCEED, {downEvent, upEvent}},
        {1, -1, Dimension(std::numeric_limits<double>::infinity()), 1, RefereeState::READY, 1, -1,
            Dimension(std::numeric_limits<double>::infinity()), RefereeState::PENDING, {downEvent, upEvent}},
        {1, 1, Dimension(-1), 1, RefereeState::READY, 1, 1,
            Dimension(std::numeric_limits<double>::infinity()), RefereeState::SUCCEED, {downEvent, upEvent}},
        {1, 2, Dimension(std::numeric_limits<double>::infinity()), 1, RefereeState::READY, 1, 2,
            Dimension(std::numeric_limits<double>::infinity()), RefereeState::PENDING, {downEvent, upEvent}},
        {1, 2, Dimension(std::numeric_limits<double>::infinity()), 1, RefereeState::READY, 1, 2,
            Dimension(std::numeric_limits<double>::infinity()), RefereeState::SUCCEED,
            {downEvent, upEvent, downEvent, upEvent}},
    };
    for (auto i = 0; i < mockClickRecognizerCases.size(); i++) {
        RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(
            mockClickRecognizerCases[i].fingers, mockClickRecognizerCases[i].count,
            mockClickRecognizerCases[i].distanceThreshold);
        clickRecognizer->refereeState_ = mockClickRecognizerCases[i].refereeState;
        for (auto j = 0; j < mockClickRecognizerCases[i].inputTouchEvents.size(); j++) {
            clickRecognizer->ProcessTouchEvent(mockClickRecognizerCases[i].inputTouchEvents[j]);
        }
        EXPECT_EQ(clickRecognizer->fingers_, mockClickRecognizerCases[i].expectedFingers);
        EXPECT_EQ(clickRecognizer->count_, mockClickRecognizerCases[i].expectedCount);
        EXPECT_EQ(clickRecognizer->distanceThreshold_.ConvertToPx(),
            mockClickRecognizerCases[i].expectedDistanceThreshold.ConvertToPx());
        EXPECT_EQ(clickRecognizer->refereeState_, mockClickRecognizerCases[i].expectedRefereeState);
    }
}

/**
 * @tc.name: ClickRecognizerInjectEventsTest002
 * @tc.desc: Test case inject events.
 * @tc.type: FUNC
 */
 HWTEST_F(ClickRecognizerTestNg, ClickRecognizerInjectEventsTest002, TestSize.Level1)
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

    TouchEvent upEventFinger0 = TouchEvent();
    TouchEvent upEventFinger1 = TouchEvent();
    upEventFinger0.type = TouchType::UP;
    upEventFinger1.type = TouchType::UP;
    upEventFinger0.id = 0;
    upEventFinger1.id = 1;

    const std::vector<MockClickRecognizerCase> mockClickRecognizerCases = {
        {2, 1, Dimension(std::numeric_limits<double>::infinity()), 1, RefereeState::READY, 2, 1,
            Dimension(std::numeric_limits<double>::infinity()), RefereeState::FAIL,
            {downEventFinger0, upEventFinger0}},
        {2, -1, Dimension(std::numeric_limits<double>::infinity()), 1, RefereeState::READY, 2, -1,
            Dimension(std::numeric_limits<double>::infinity()), RefereeState::FAIL,
            {downEventFinger0, upEventFinger0}},
        {2, 1, Dimension(-1), 1, RefereeState::READY, 2, 1,
            Dimension(std::numeric_limits<double>::infinity()), RefereeState::FAIL,
            {downEventFinger0, upEventFinger0}},
        {2, 2, Dimension(std::numeric_limits<double>::infinity()), 1, RefereeState::READY, 2, 2,
            Dimension(std::numeric_limits<double>::infinity()), RefereeState::FAIL,
            {downEventFinger0, upEventFinger0}},
        {2, 2, Dimension(std::numeric_limits<double>::infinity()), 1, RefereeState::READY, 2, 2,
            Dimension(std::numeric_limits<double>::infinity()), RefereeState::FAIL,
            {downEventFinger0, upEventFinger0, downEventFinger0, upEventFinger0}},
        {2, 1, Dimension(std::numeric_limits<double>::infinity()), 1, RefereeState::READY, 2, 1,
            Dimension(std::numeric_limits<double>::infinity()), RefereeState::SUCCEED,
            {downEventFinger0, downEventFinger1, upEventFinger0, upEventFinger1}},
    };
    for (auto i = 0; i < mockClickRecognizerCases.size(); i++) {
        RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(
            mockClickRecognizerCases[i].fingers, mockClickRecognizerCases[i].count,
            mockClickRecognizerCases[i].distanceThreshold);
        clickRecognizer->refereeState_ = mockClickRecognizerCases[i].refereeState;
        for (auto j = 0; j < mockClickRecognizerCases[i].inputTouchEvents.size(); j++) {
            clickRecognizer->ProcessTouchEvent(mockClickRecognizerCases[i].inputTouchEvents[j]);
        }
        EXPECT_EQ(clickRecognizer->fingers_, mockClickRecognizerCases[i].expectedFingers);
        EXPECT_EQ(clickRecognizer->count_, mockClickRecognizerCases[i].expectedCount);
        EXPECT_EQ(clickRecognizer->distanceThreshold_.ConvertToPx(),
            mockClickRecognizerCases[i].expectedDistanceThreshold.ConvertToPx());
        EXPECT_EQ(clickRecognizer->refereeState_, mockClickRecognizerCases[i].expectedRefereeState);
    }
}

/**
 * @tc.name: ClickRecognizerTypeTest001
 * @tc.desc: Test ClickRecognizer Type function: ClickRecognizerTypeTest001
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerTypeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create clickRecognizer.
     */
    GestureEvent info = GestureEvent();
    /**
     * @tc.steps: step2. call SetGestureTypeName
     * @tc.expected: result equals.
     */
    info.SetGestureTypeName(GestureTypeName::TAP_GESTURE);
    EXPECT_EQ(info.GetGestureTypeName(), GestureTypeName::TAP_GESTURE);
}

/**
 * @tc.name: ClickRecognizerTypeTest002
 * @tc.desc: Test ClickRecognizerType
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerTypeTest002, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, TAPPED_COUNT);
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    clickRecognizer->AttachFrameNode(frameNode);
    clickRecognizer->SetRecognizerType(GestureTypeName::CLICK);
    GestureEvent info = GestureEvent();
    clickRecognizer->HandleReports(info, GestureCallbackType::START);
    EXPECT_EQ(clickRecognizer->GetRecognizerType(), GestureTypeName::CLICK);
}

/**
 * @tc.name: ClickRecognizerTypeTest003
 * @tc.desc: Test ClickRecognizerType
 */
HWTEST_F(ClickRecognizerTestNg, ClickRecognizerTypeTest003, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, TAPPED_COUNT);
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    clickRecognizer->AttachFrameNode(frameNode);
    clickRecognizer->SetRecognizerType(GestureTypeName::TAP_GESTURE);
    GestureEvent info = GestureEvent();
    clickRecognizer->HandleReports(info, GestureCallbackType::START);
    EXPECT_EQ(clickRecognizer->GetRecognizerType(), GestureTypeName::TAP_GESTURE);
}

/**
 * @tc.name: TriggerGestureJudgeCallbackTest002
 * @tc.desc: Test TriggerGestureJudgeCallback
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, TriggerGestureJudgeCallbackTest002, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    clickRecognizer->inputEventType_ = InputEventType::KEYBOARD;
    clickRecognizer->deviceId_ = 1;

    auto func = [](const std::shared_ptr<BaseGestureEvent>& info, const RefPtr<NGGestureRecognizer>& current,
                    const std::list<RefPtr<NGGestureRecognizer>>& others) {
        EXPECT_EQ(info->rawInputEventType_, InputEventType::KEYBOARD);
        EXPECT_EQ(info->rawInputDeviceId_, 1);
        return GestureJudgeResult::REJECT;
    };
    TouchEvent touchEvent;
    touchEvent.rollAngle = 0;
    clickRecognizer->touchPoints_[0] = touchEvent;
    clickRecognizer->targetComponent_ = targetComponent;
    targetComponent->SetOnGestureRecognizerJudgeBegin(func);
    clickRecognizer->TriggerGestureJudgeCallback();
}

/**
 * @tc.name: ResetStatusInHandleOverdueDeadlineTest001
 * @tc.desc: Test ResetStatusInHandleOverdueDeadline
 * @tc.type: FUNC
 */
HWTEST_F(ClickRecognizerTestNg, ResetStatusInHandleOverdueDeadlineTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create clickRecognizer and SetResponseLinkRecognizers.
     */
    RefPtr<ClickRecognizer> triggerClickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::list<RefPtr<NGGestureRecognizer>> responseLinkResult;
    responseLinkResult.push_back(triggerClickRecognizer);
    RefPtr<NGGestureRecognizer> targetPtr1 = nullptr;
    responseLinkResult.push_back(targetPtr1);
    RefPtr<NGGestureRecognizer> targetPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    responseLinkResult.push_back(targetPtr2);
    triggerClickRecognizer->SetResponseLinkRecognizers(responseLinkResult);
    targetPtr2->SetResponseLinkRecognizers(responseLinkResult);

    /**
     * @tc.steps: step2. Do ResetStatusInHandleOverdueDeadline.
     * @tc.expected: responseLinkRecognizer_ is empty().
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->eventManager_ = eventManager;
    triggerClickRecognizer->ResetStatusInHandleOverdueDeadline();
    EXPECT_EQ(triggerClickRecognizer->responseLinkRecognizer_.size(), 0);
    EXPECT_EQ(targetPtr2->responseLinkRecognizer_.size(), 0);

    /**
     * @tc.steps: step3. Do ResetStatusInHandleOverdueDeadline with not QueryAllDone.
     * @tc.expected: responseLinkRecognizer_ is same as before.
     */
    RefPtr<GestureScope> gestureScope = AceType::MakeRefPtr<GestureScope>(0);
    ASSERT_NE(gestureScope, nullptr);
    triggerClickRecognizer->refereeState_ = RefereeState::PENDING;
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), triggerClickRecognizer);
    ASSERT_NE(context->eventManager_, nullptr);
    ASSERT_NE(context->eventManager_->refereeNG_, nullptr);
    context->eventManager_->refereeNG_->gestureScopes_.insert(std::make_pair(0, gestureScope));
    targetPtr2->SetResponseLinkRecognizers(responseLinkResult);
    triggerClickRecognizer->ResetStatusInHandleOverdueDeadline();
    EXPECT_EQ(targetPtr2->responseLinkRecognizer_.size(), 3);
}
} // namespace OHOS::Ace::NG