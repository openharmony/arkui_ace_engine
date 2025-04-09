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
class SequencedRecognizerTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void SequencedRecognizerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void SequencedRecognizerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: SequencedRecognizerBatchAdjudicateTest001
 * @tc.desc: Test SequencedRecognizer function: BatchAdjudicate, and GestureDisposal
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerBatchAdjudicateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case1: disposal: ACCEPT, refereeState: SUCCEED
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    sequencedRecognizer->refereeState_ = RefereeState::PENDING;
    sequencedRecognizer->currentIndex_ = -9;
    sequencedRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case2: disposal: ACCEPT, refereeState: PENDING, currentIndex = 0
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->refereeState_ = RefereeState::PENDING;
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    sequencedRecognizer->currentIndex_ = -10;
    sequencedRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case3: disposal: REJECT, refereeState: FAIL
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->refereeState_ = RefereeState::FAIL;
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    sequencedRecognizer->currentIndex_ = -9;
    sequencedRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::REJECT);
    EXPECT_NE(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case4: disposal: REJECT, refereeState: SUCCESS, refereeState_ = FAIL
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->refereeState_ = RefereeState::FAIL;
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    sequencedRecognizer->currentIndex_ = -10;
    sequencedRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::REJECT);
    EXPECT_NE(clickRecognizerPtr->refereeState_, RefereeState::PENDING);
}

/**
 * @tc.name: SequencedRecognizerTest001
 * @tc.desc: Test SequencedRecognizer function: OnAccepted
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case1: recognizers_ is empty
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->OnAccepted();
    EXPECT_EQ(sequencedRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case2: recognizers_ is not empty, have nullptr
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->recognizers_.push_back(nullptr);
    sequencedRecognizer->OnAccepted();
    EXPECT_EQ(sequencedRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case3: recognizers_ is not empty, have click ptr
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizer->OnAccepted();
    EXPECT_EQ(sequencedRecognizer->refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: SequencedRecognizerTest002
 * @tc.desc: Test SequencedRecognizer function: OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call OnRejected function and compare result.
     * @tc.steps: case1: recognizers_ is empty
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->OnRejected();
    EXPECT_EQ(sequencedRecognizer->refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step2. call OnRejected function and compare result.
     * @tc.steps: case2: recognizers_ is not empty, have nullptr
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->currentIndex_ = -1;
    sequencedRecognizer->recognizers_.push_back(nullptr);
    sequencedRecognizer->OnRejected();
    EXPECT_EQ(sequencedRecognizer->refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case3: recognizers_ is not empty, have click ptr
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer->currentIndex_ = 0;
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizer->OnRejected();
    EXPECT_EQ(sequencedRecognizer->refereeState_, RefereeState::FAIL);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: SequencedRecognizerTest003
 * @tc.desc: Test SequencedRecognizer function: OnPending
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call OnPending function and compare result.
     * @tc.steps: case1: recognizers_ is empty
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->OnPending();
    EXPECT_EQ(sequencedRecognizer->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call OnPending function and compare result.
     * @tc.steps: case2: recognizers_ is not empty, have nullptr
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->recognizers_.push_back(nullptr);
    sequencedRecognizer->OnPending();
    EXPECT_EQ(sequencedRecognizer->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call OnPending function and compare result.
     * @tc.steps: case3: recognizers_ is not empty, have click ptr, ACCEPT
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr->disposal_ = GestureDisposal::ACCEPT;
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizer->OnPending();
    EXPECT_EQ(sequencedRecognizer->refereeState_, RefereeState::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnPending function and compare result.
     * @tc.steps: case4: recognizers_ is not empty, have click ptr, PENDING
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->disposal_ = GestureDisposal::PENDING;
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizer->OnPending();
    EXPECT_EQ(sequencedRecognizer->refereeState_, RefereeState::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);
}

/**
 * @tc.name: SequencedRecognizerTest004
 * @tc.desc: Test SequencedRecognizer function: OnBlocked
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call OnBlocked function and compare result.
     * @tc.steps: case1: recognizers_ is empty
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->OnBlocked();
    EXPECT_EQ(sequencedRecognizer->refereeState_, RefereeState::READY);

    /**
     * @tc.steps: step2. call OnBlocked function and compare result.
     * @tc.steps: case2: recognizers_ is not empty, have nullptr
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->recognizers_.push_back(nullptr);
    sequencedRecognizer->OnBlocked();
    EXPECT_EQ(sequencedRecognizer->refereeState_, RefereeState::READY);

    /**
     * @tc.steps: step2. call OnBlocked function and compare result.
     * @tc.steps: case3: recognizers_ is not empty, disposal is ACCEPT
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer->disposal_ = GestureDisposal::ACCEPT;
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizer->OnBlocked();
    EXPECT_EQ(sequencedRecognizer->refereeState_, RefereeState::SUCCEED_BLOCKED);

    /**
     * @tc.steps: step2. call OnBlocked function and compare result.
     * @tc.steps: case4: recognizers_ is not empty, disposal is PENDING
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->disposal_ = GestureDisposal::PENDING;
    sequencedRecognizer->OnBlocked();
    EXPECT_EQ(sequencedRecognizer->refereeState_, RefereeState::PENDING_BLOCKED);

    /**
     * @tc.steps: step2. call OnBlocked function and compare result.
     * @tc.steps: case5: recognizers_ is not empty nullptr, disposal is ACCEPT
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->disposal_ = GestureDisposal::ACCEPT;
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(nullptr);
    sequencedRecognizer->OnBlocked();
    EXPECT_EQ(sequencedRecognizer->refereeState_, RefereeState::SUCCEED_BLOCKED);

    /**
     * @tc.steps: step2. call OnBlocked function and compare result.
     * @tc.steps: case6: recognizers_ is not empty nullptr, disposal is PENDING
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->disposal_ = GestureDisposal::PENDING;
    sequencedRecognizer->OnBlocked();
    EXPECT_EQ(sequencedRecognizer->refereeState_, RefereeState::PENDING_BLOCKED);
}

/**
 * @tc.name: SequencedRecognizerTest005
 * @tc.desc: Test SequencedRecognizer function: HandleEvent
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    bool result = false;
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case1: currentIndex = 0
     * @tc.expected: step2. result equals.
     */
    result = sequencedRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
    //  * @tc.steps: step2. call HandleEvent function and compare result.
    //  * @tc.steps: case2: currentIndex = 1, prevState = SUCCESS
    //  * @tc.expected: step2. result equals.
    //  */
    sequencedRecognizer->currentIndex_ = 1;
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    result = sequencedRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case3: currentIndex = 1, prevState = READY
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->currentIndex_ = 1;
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    result = sequencedRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: SequencedRecognizerTest006
 * @tc.desc: Test SequencedRecognizer function: HandleEvent
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    bool result = false;
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case4: point.type = DOWN, size = 1
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::DOWN;
    result = sequencedRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case5: point.type = MOVE
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::MOVE;
    result = sequencedRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case6: point.type = UP
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::UP;
    result = sequencedRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case7: point.type = CANCEL
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::CANCEL;
    result = sequencedRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: SequencedRecognizerTest007
 * @tc.desc: Test SequencedRecognizer function: HandleEvent
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    bool result = false;
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case8: point.type = UNKOWN
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::UNKNOWN;
    result = sequencedRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case9: point.type = UP and refereeState = PENDING
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::UP;
    sequencedRecognizer->refereeState_ = RefereeState::PENDING;
    result = sequencedRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case10: point.type != UP and refereeState = PENDING
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::DOWN;
    sequencedRecognizer->refereeState_ = RefereeState::PENDING;
    result = sequencedRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case11: point.type = DOWN, size > 1
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::DOWN;
    sequencedRecognizer->touchPoints_[0] = touchEvent;
    sequencedRecognizer->touchPoints_[1] = touchEvent;
    result = sequencedRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: SequencedRecognizerTest008
 * @tc.desc: Test SequencedRecognizer function: BatchAdjudicate, and GestureDisposal
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case1: disposal: ACCEPT, refereeState: SUCCEED
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    sequencedRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case2: disposal: ACCEPT, refereeState: PENDING, currentIndex = 0
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->currentIndex_ = 0;
    sequencedRecognizer->refereeState_ = RefereeState::PENDING;
    sequencedRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case3: disposal: REJECT, refereeState: FAIL
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    sequencedRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::REJECT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case4: disposal: REJECT, refereeState: SUCCESS, refereeState_ = FAIL
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->refereeState_ = RefereeState::FAIL;
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    sequencedRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::REJECT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case5: disposal: PENDING, refereeState: PENDING
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    sequencedRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case5: disposal: PENDING, refereeState: SUCCESS, refereeState_: PENDING
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    sequencedRecognizer->refereeState_ = RefereeState::PENDING;
    sequencedRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);
}

/**
 * @tc.name: SequencedRecognizerHandleOverdueDeadlineTest001
 * @tc.desc: Test SequencedRecognizer function: HandleOverdueDeadline
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerHandleOverdueDeadlineTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call UpdateCurrentIndex function and compare result.
     * @tc.steps: case1: currentIndex != size - 1
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->currentIndex_ = 0;
    sequencedRecognizer->refereeState_ = RefereeState::SUCCEED;
    sequencedRecognizer->HandleOverdueDeadline();
    EXPECT_EQ(sequencedRecognizer->currentIndex_, 0);
}

/**
 * @tc.name: SequencedRecognizerTest009
 * @tc.desc: Test SequencedRecognizer function: UpdateCurrentIndex
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call UpdateCurrentIndex function and compare result.
     * @tc.steps: case1: currentIndex == size - 1
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->currentIndex_ = -1;
    sequencedRecognizer->UpdateCurrentIndex();
    EXPECT_EQ(sequencedRecognizer->currentIndex_, -1);

    /**
     * @tc.steps: step2. call UpdateCurrentIndex function and compare result.
     * @tc.steps: case1: currentIndex != size - 1
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->currentIndex_ = 0;
    sequencedRecognizer->UpdateCurrentIndex();
    EXPECT_EQ(sequencedRecognizer->currentIndex_, 1);
}

/**
 * @tc.name: SequencedRecognizerTest010
 * @tc.desc: Test SequencedRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<SequencedRecognizer> sequencedRecognizerPtr = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    bool result = false;

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case1: recognizer is nullptr
     * @tc.expected: step2. result equals.
     */
    result = sequencedRecognizer->ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case2: size not same, priorityMask not same
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(nullptr);
    sequencedRecognizer->priorityMask_ = GestureMask::Begin;
    result = sequencedRecognizer->ReconcileFrom(sequencedRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case3: size not same, priorityMask same
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(nullptr);
    sequencedRecognizer->priorityMask_ = GestureMask::Normal;
    result = sequencedRecognizer->ReconcileFrom(sequencedRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case4: size same, priorityMask not same
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->priorityMask_ = GestureMask::Begin;
    result = sequencedRecognizer->ReconcileFrom(sequencedRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case4: size same, priorityMask same, child is nullptr
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(nullptr);
    sequencedRecognizerPtr->recognizers_.clear();
    sequencedRecognizerPtr->recognizers_.push_back(nullptr);
    sequencedRecognizer->priorityMask_ = GestureMask::Normal;
    result = sequencedRecognizer->ReconcileFrom(sequencedRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case4: size same, priorityMask same, child is ptr
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizerPtr->recognizers_.clear();
    sequencedRecognizerPtr->recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizer->priorityMask_ = GestureMask::Normal;
    result = sequencedRecognizer->ReconcileFrom(sequencedRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case4: size same, priorityMask same, child is ptr and nullptr
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizerPtr->recognizers_.clear();
    sequencedRecognizerPtr->recognizers_.push_back(nullptr);
    sequencedRecognizer->priorityMask_ = GestureMask::Normal;
    result = sequencedRecognizer->ReconcileFrom(sequencedRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: SequencedRecognizerTest011
 * @tc.desc: Test HandleEvent
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest011, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<SequencedRecognizer> sequencedRecognizerPtr = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    AxisEvent point;
    point.action = AxisAction::BEGIN;
    auto result = sequencedRecognizerPtr->HandleEvent(point);
    EXPECT_EQ(result, true);
    point.action = AxisAction::UPDATE;
    result = sequencedRecognizerPtr->HandleEvent(point);
    EXPECT_EQ(result, true);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    result = sequencedRecognizerPtr->HandleEvent(point);
    EXPECT_EQ(result, true);
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(nullptr);
    result = sequencedRecognizerPtr->HandleEvent(point);
    EXPECT_EQ(result, true);
    sequencedRecognizer->currentIndex_ = 0;
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    result = sequencedRecognizerPtr->HandleEvent(point);
    EXPECT_EQ(result, true);
    sequencedRecognizer->currentIndex_ = 2;
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    result = sequencedRecognizerPtr->HandleEvent(point);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: SequencedRecognizerTest012
 * @tc.desc: Test HandleEvent
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest012, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<SequencedRecognizer> sequencedRecognizerPtr = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    AxisEvent point;
    point.action = AxisAction::NONE;
    auto result = sequencedRecognizerPtr->HandleEvent(point);
    EXPECT_EQ(result, true);
    sequencedRecognizerPtr->refereeState_ = RefereeState::PENDING;
    point.action = AxisAction::END;
    result = sequencedRecognizerPtr->HandleEvent(point);
    EXPECT_EQ(result, true);
    sequencedRecognizerPtr->refereeState_ = RefereeState::PENDING;
    point.action = AxisAction::UPDATE;
    result = sequencedRecognizerPtr->HandleEvent(point);
    EXPECT_EQ(result, true);
    sequencedRecognizerPtr->refereeState_ = RefereeState::PENDING_BLOCKED;
    point.action = AxisAction::END;
    result = sequencedRecognizerPtr->HandleEvent(point);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: SequencedRecognizerTest013
 * @tc.desc: Test CleanRecognizerState
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest013, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<SequencedRecognizer> sequencedRecognizerPtr = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    AxisEvent point;
    point.action = AxisAction::NONE;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizer->CleanRecognizerState();
    sequencedRecognizer->refereeState_ = RefereeState::SUCCEED;
    sequencedRecognizer->currentFingers_ = 0;
    sequencedRecognizer->CleanRecognizerState();
    sequencedRecognizer->refereeState_ = RefereeState::FAIL;
    sequencedRecognizer->currentFingers_ = 0;
    sequencedRecognizer->CleanRecognizerState();
    sequencedRecognizer->refereeState_ = RefereeState::DETECTING;
    sequencedRecognizer->currentFingers_ = 0;
    sequencedRecognizer->CleanRecognizerState();
    sequencedRecognizer->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    sequencedRecognizer->currentFingers_ = 0;
    sequencedRecognizer->CleanRecognizerState();
    sequencedRecognizer->refereeState_ = RefereeState::FAIL;
    sequencedRecognizer->currentFingers_ = 1;
    sequencedRecognizer->CleanRecognizerState();
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->CleanRecognizerState();
    EXPECT_EQ(sequencedRecognizerPtr->currentIndex_, 0);
}

/**
 * @tc.name: SequencedRecognizerTest014
 * @tc.desc: Test ForceCleanRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest014, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<SequencedRecognizer> sequencedRecognizerPtr = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    AxisEvent point;
    point.action = AxisAction::NONE;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizer->ForceCleanRecognizer();
    EXPECT_EQ(sequencedRecognizerPtr->currentIndex_, 0);
}

/**
 * @tc.name: SequencedRecognizerTest015
 * @tc.desc: Test ForceCleanRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest015, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<SequencedRecognizer> sequencedRecognizerPtr = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    AxisEvent point;
    point.action = AxisAction::NONE;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->ForceCleanRecognizer();
    EXPECT_EQ(sequencedRecognizerPtr->currentIndex_, 0);
}

/**
 * @tc.name: SequencedRecognizerTest016
 * @tc.desc: Test CleanRecognizerState
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {clickRecognizerPtr};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);

    /**
     * @tc.steps: step3. set child recognizer state and call cleanRecognizerState function and compare result.
     * @tc.steps: case1: touchPoints size is 1, clean success.
     * @tc.expected: step3. clickRecognizer state set ready.
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    sequencedRecognizer->CleanRecognizerState();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);

    /**
     * @tc.steps: step3. set child recognizer state and call cleanRecognizerState function and compare result.
     * @tc.steps: case2: touchPoints size is 2, clean fail.
     * @tc.expected: step3. clickRecognizer state set ready.
     */
    clickRecognizerPtr->touchPoints_[0] = {};
    clickRecognizerPtr->touchPoints_[1] = {};
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    sequencedRecognizer->CleanRecognizerState();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: SequencedRecognizerTest017
 * @tc.desc: Test SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case1: onAction is no, *onAction is no.
     * @tc.expected: step2. result equals.
     */
    std::unique_ptr<GestureEventFunc> onAction;
    sequencedRecognizer->SendCallbackMsg(onAction);
    EXPECT_EQ(sequencedRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case2: onAction is yes, *onAction is no.
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    onAction = std::make_unique<GestureEventFunc>();
    sequencedRecognizer->SendCallbackMsg(onAction);
    EXPECT_EQ(sequencedRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, disposeTag_ is false.
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    sequencedRecognizer->SendCallbackMsg(onAction);
    EXPECT_EQ(sequencedRecognizer->touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: onAction is yes, *onAction is yes, disposeTag_ is true.
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->gestureInfo_->SetDisposeTag(true);
    sequencedRecognizer->SendCallbackMsg(onAction);
    EXPECT_EQ(sequencedRecognizer->touchPoints_.size(), 0);
}

/**
 * @tc.name: SequencedRecognizerTest018
 * @tc.desc: Test CheckGroupState
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call CheckGroupState function and compare result.
     * @tc.steps: case1: currentIndex_ is -1.
     * @tc.expected: step2. result is false.
     */
    sequencedRecognizer->currentIndex_ = -1;
    bool result = sequencedRecognizer->CheckGroupState();
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step2. call CheckGroupState function and compare result.
     * @tc.steps: case2: currentIndex_ is 0.
     * @tc.expected: step2. result is false.
     */
    sequencedRecognizer->currentIndex_ = 0;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    result = sequencedRecognizer->CheckGroupState();
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step2. call CheckGroupState function and compare result.
     * @tc.steps: case3: refereeState_ is RefereeState::PENDING.
     * @tc.expected: step2. result is true.
     */
    sequencedRecognizer->refereeState_ = RefereeState::PENDING;
    result = sequencedRecognizer->CheckGroupState();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SequencedRecognizerTest019
 * @tc.desc: Test CheckStates
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case1: currentIndex_ is -1.
     * @tc.expected: step2. result is equal to RefereeState::READY.
     */
    size_t touchId = 100;
    sequencedRecognizer->currentIndex_ = -1;
    RefereeState result = sequencedRecognizer->CheckStates(touchId);
    EXPECT_EQ(result, RefereeState::READY);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case2: currentIndex_ is 0.
     * @tc.expected: step2. result is equal to RefereeState::READY.
     */
    sequencedRecognizer->currentIndex_ = 0;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    result = sequencedRecognizer->CheckStates(touchId);
    EXPECT_EQ(result, RefereeState::READY);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case3: refereeState_ is RefereeState::PENDING.
     * @tc.expected: step2. result is equal to RefereeState::PENDING.
     */
    sequencedRecognizer->refereeState_ = RefereeState::PENDING;
    result = sequencedRecognizer->CheckStates(touchId);
    EXPECT_EQ(result, RefereeState::PENDING);
}

/**
 * @tc.name: SequencedRecognizerTest020
 * @tc.desc: Test HandleEvent
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case1: currentIndex_ is 0.
     * @tc.expected: step2. result is true.
     */
    AxisEvent point;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    bool result = sequencedRecognizer->HandleEvent(point);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case2: action is AxisAction::NONE.
     * @tc.expected: step2. result is true.
     */
    point.action = AxisAction::NONE;
    result = sequencedRecognizer->HandleEvent(point);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case3: action is AxisAction::END.
     * @tc.expected: step2. result is true.
     */
    point.action = AxisAction::END;
    result = sequencedRecognizer->HandleEvent(point);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case4: refereeState_ is RefereeState::PENDING.
     * @tc.expected: step2. result is true.
     */
    sequencedRecognizer->refereeState_ = RefereeState::PENDING;
    result = sequencedRecognizer->HandleEvent(point);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SequencedRecognizerTest021
 * @tc.desc: Test HandleEvent
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case1: currentIndex_ is 1.
     * @tc.expected: step2. result is true.
     */
    AxisEvent point;
    RefPtr<ClickRecognizer> clickRecognizerPtr1 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr1);
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr2);
    sequencedRecognizer->currentIndex_ = 1;
    bool result = sequencedRecognizer->HandleEvent(point);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case2: clickRecognizerPtr2->refereeState_ is RefereeState::PENDING.
     * @tc.expected: step2. result is true.
     */
    clickRecognizerPtr2->refereeState_ = RefereeState::PENDING;
    result = sequencedRecognizer->HandleEvent(point);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SequencedRecognizerTest022
 * @tc.desc: Test UpdateCurrentIndex
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call UpdateCurrentIndex function and compare result.
     * @tc.steps: case1: inputEventType_ is InputEventType::MOUSE_BUTTON.
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->currentIndex_ = 0;
    sequencedRecognizer->inputEventType_ = InputEventType::MOUSE_BUTTON;
    RefPtr<ClickRecognizer> clickRecognizerPtr1 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr1);
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr2);
    sequencedRecognizer->UpdateCurrentIndex();
    EXPECT_EQ(sequencedRecognizer->currentIndex_, 1);

    /**
     * @tc.steps: step2. call UpdateCurrentIndex function and compare result.
     * @tc.steps: case2: isEventHandoverNeeded_ is true.
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->currentIndex_ = 0;
    sequencedRecognizer->isEventHandoverNeeded_ = true;
    sequencedRecognizer->UpdateCurrentIndex();
    EXPECT_EQ(sequencedRecognizer->currentIndex_, 1);

    /**
     * @tc.steps: step2. call UpdateCurrentIndex function and compare result.
     * @tc.steps: case3: isEventHandoverNeeded_ is false.
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->currentIndex_ = 0;
    sequencedRecognizer->isEventHandoverNeeded_ = false;
    RefPtr<LongPressRecognizer> longPressRecognizer1 =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    RefPtr<LongPressRecognizer> longPressRecognizer2 =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    sequencedRecognizer->recognizers_.push_back(longPressRecognizer1);
    sequencedRecognizer->recognizers_.push_back(longPressRecognizer2);
    sequencedRecognizer->UpdateCurrentIndex();
    EXPECT_EQ(sequencedRecognizer->currentIndex_, 1);
}

/**
 * @tc.name: SequencedRecognizerTest023
 * @tc.desc: Test CheckBetweenTwoLongPressRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call CheckBetweenTwoLongPressRecognizer function and compare result.
     * @tc.steps: case1: currentIndex_ is 2.
     * @tc.expected: step2. result is false.
     */
    sequencedRecognizer->currentIndex_ = 2;
    RefPtr<LongPressRecognizer> longPressRecognizer1 =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    RefPtr<LongPressRecognizer> longPressRecognizer2 =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    sequencedRecognizer->recognizers_.push_back(longPressRecognizer1);
    sequencedRecognizer->recognizers_.push_back(longPressRecognizer2);
    int32_t currentIndex = 1;
    bool result = sequencedRecognizer->CheckBetweenTwoLongPressRecognizer(currentIndex);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step2. call CheckBetweenTwoLongPressRecognizer function and compare result.
     * @tc.steps: case2: currentIndex_ is -1.
     * @tc.expected: step2. result is false.
     */
    currentIndex = -1;
    result = sequencedRecognizer->CheckBetweenTwoLongPressRecognizer(currentIndex);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SequencedRecognizerTest024
 * @tc.desc: Test CheckAndSetRecognizerCleanFlag
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call CheckAndSetRecognizerCleanFlag function and compare result.
     * @tc.steps: case1: currentIndex_ is -1.
     * @tc.expected: step2. isNeedResetRecognizerState_ is false.
     */
    RefPtr<NGGestureRecognizer> recognizer = nullptr;
    sequencedRecognizer->CheckAndSetRecognizerCleanFlag(recognizer);
    EXPECT_FALSE(sequencedRecognizer->IsNeedResetRecognizerState());

    /**
     * @tc.steps: step2. call CheckAndSetRecognizerCleanFlag function and compare result.
     * @tc.steps: case1: currentIndex_ is -1.
     * @tc.expected: step2. isNeedResetRecognizerState_ is true.
     */
    sequencedRecognizer->currentIndex_ = -1;
    sequencedRecognizer->CheckAndSetRecognizerCleanFlag(recognizer);
    EXPECT_TRUE(sequencedRecognizer->IsNeedResetRecognizerState());
}

/**
 * @tc.name: SequencedRecognizerTest025
 * @tc.desc: Test CleanRecognizerStateVoluntarily
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<SequencedRecognizer> sequencedRecognizerPtr = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call CleanRecognizerStateVoluntarily function and compare result.
     * @tc.steps: case1: recognizers_ is not empty nullptr.
     * @tc.expected: step2. isNeedResetRecognizerState_ is false.
     */
    sequencedRecognizer->recognizers_.push_back(nullptr);
    sequencedRecognizer->recognizers_.push_back(sequencedRecognizerPtr);
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizer->CleanRecognizerStateVoluntarily();
    EXPECT_FALSE(sequencedRecognizer->IsNeedResetRecognizerState());

    /**
     * @tc.steps: step2. call CleanRecognizerStateVoluntarily function and compare result.
     * @tc.steps: case2: isNeedResetRecognizerState_ is true.
     * @tc.expected: step2. isNeedResetRecognizerState_ is false.
     */
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->SetIsNeedResetRecognizer(true);
    sequencedRecognizer->CleanRecognizerStateVoluntarily();
    EXPECT_FALSE(sequencedRecognizer->IsNeedResetRecognizerState());
}

/**
 * @tc.name: SequencedRecognizerTest026
 * @tc.desc: Test ForceCleanRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call ForceCleanRecognizer function and compare result.
     * @tc.steps: case: recognizers_ is not empty, have nullptr.
     * @tc.expected: step2. currentIndex_ is equal to 0.
     */
    sequencedRecognizer->recognizers_.push_back(nullptr);
    sequencedRecognizer->ForceCleanRecognizer();
    EXPECT_EQ(sequencedRecognizer->currentIndex_, 0);
}

/**
 * @tc.name: SequencedRecognizerTest027
 * @tc.desc: Test NeedStartDeadlineTimerInner
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call NeedStartDeadlineTimerInner function and compare result.
     * @tc.steps: case: currentIndex_ is 1.
     * @tc.expected: step2. result is true.
     */
    SourceTool sourceTool = SourceTool::UNKNOWN;
    sequencedRecognizer->currentIndex_ = 1;
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    bool result = sequencedRecognizer->NeedStartDeadlineTimerInner(clickRecognizerPtr, sourceTool);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SequencedRecognizerTest028
 * @tc.desc: Test HandleEvent
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case1: recognizers_ is not empty, have nullptr.
     * @tc.expected: step2. result is true.
     */
    TouchEvent point;
    sequencedRecognizer->recognizers_.push_back(nullptr);
    bool result = sequencedRecognizer->HandleEvent(point);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case2: point.type is TouchType::DOWN.
     * @tc.expected: step2. result is true.
     */
    point.type = TouchType::DOWN;
    result = sequencedRecognizer->HandleEvent(point);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case3: point.childTouchTestListis not empty.
     * @tc.expected: step2. result equals.
     */
    std::string childTouchTest = "childTouchTest";
    point.childTouchTestList.push_back(childTouchTest);
    sequencedRecognizer->recognizers_.clear();
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    result = sequencedRecognizer->HandleEvent(point);
    EXPECT_EQ(sequencedRecognizer->childTouchTestList_, point.childTouchTestList);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SequencedRecognizerTest029
 * @tc.desc: Test BatchAdjudicate
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call BatchAdjudicate function and compare result.
     * @tc.steps: case1: disposal: ACCEPT.
     * @tc.expected: step2. result equals.
     */
    GestureDisposal disposal = GestureDisposal::ACCEPT;
    sequencedRecognizer->recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizer->BatchAdjudicate(clickRecognizerPtr, disposal);
    EXPECT_EQ(sequencedRecognizer->disposal_, GestureDisposal::ACCEPT);

    /**
     * @tc.steps: step2. call BatchAdjudicate function and compare result.
     * @tc.steps: case2: disposal: ACCEPT, refereeState: READY.
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->recognizers_.clear();
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    sequencedRecognizer->BatchAdjudicate(clickRecognizerPtr, disposal);
    EXPECT_EQ(sequencedRecognizer->disposal_, GestureDisposal::PENDING);

    /**
     * @tc.steps: step2. call BatchAdjudicate function and compare result.
     * @tc.steps: case3: disposal: REJECT.
     * @tc.expected: step2. result equals.
     */
    disposal = GestureDisposal::REJECT;
    sequencedRecognizer->BatchAdjudicate(clickRecognizerPtr, disposal);
    EXPECT_EQ(sequencedRecognizer->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step2. call BatchAdjudicate function and compare result.
     * @tc.steps: case4: disposal: NONE.
     * @tc.expected: step2. result equals.
     */
    disposal = GestureDisposal::NONE;
    sequencedRecognizer->BatchAdjudicate(clickRecognizerPtr, disposal);
    EXPECT_EQ(sequencedRecognizer->disposal_, GestureDisposal::PENDING);
}

/**
 * @tc.name: SequencedRecognizerTest030
 * @tc.desc: Test SendTouchEventToNextRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    TouchEvent touchEvent;
    std::string childTouchTest = "childTouchTest";

    /**
     * @tc.steps: step2. call SendTouchEventToNextRecognizer function and compare result.
     * @tc.steps: case1: inputEventType_ is InputEventType::AXIS.
     * @tc.expected: step2. result equals.
     */
    int64_t beforeDuration = 0;
    sequencedRecognizer->inputEventType_ = InputEventType::AXIS;
    sequencedRecognizer->SendTouchEventToNextRecognizer(clickRecognizerPtr, beforeDuration);
    EXPECT_EQ(clickRecognizerPtr->inputEventType_, InputEventType::AXIS);

    /**
     * @tc.steps: step2. call SendTouchEventToNextRecognizer function and compare result.
     * @tc.steps: case2: inputEventType_ is InputEventType::TOUCH_SCREEN.
     * @tc.expected: step2. result equals.
     */
    beforeDuration = 1;
    sequencedRecognizer->inputEventType_ = InputEventType::TOUCH_SCREEN;
    sequencedRecognizer->touchPoints_[0] = touchEvent;
    sequencedRecognizer->touchPoints_[1] = touchEvent;
    sequencedRecognizer->childTouchTestList_.push_back(childTouchTest);
    sequencedRecognizer->SendTouchEventToNextRecognizer(clickRecognizerPtr, beforeDuration);
    EXPECT_EQ(sequencedRecognizer->touchPoints_[0].childTouchTestList, sequencedRecognizer->childTouchTestList_);
}

/**
 * @tc.name: SequencedRecognizerTest031
 * @tc.desc: Test HandleOverdueDeadline
 * @tc.type: FUNC
 */
HWTEST_F(SequencedRecognizerTestNg, SequencedRecognizerTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<SequencedRecognizer> sequencedRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call HandleOverdueDeadline function and compare result.
     * @tc.steps: case: refereeState_ is RefereeState::PENDING.
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer->refereeState_ = RefereeState::PENDING;
    sequencedRecognizer->HandleOverdueDeadline();
    EXPECT_EQ(sequencedRecognizer->disposal_, GestureDisposal::REJECT);
}
} // namespace OHOS::Ace::NG