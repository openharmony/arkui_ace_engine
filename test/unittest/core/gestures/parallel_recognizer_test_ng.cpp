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
class ParallelRecognizerTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void ParallelRecognizerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void ParallelRecognizerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: ParallelRecognizerOnRejectedTest001
 * @tc.desc: Test ParallelRecognizer function: OnAccepted OnRejected OnPending OnBlock
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerOnRejectedTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr2->refereeState_ = RefereeState::PENDING_BLOCKED;
    recognizers.insert(recognizers.end(), clickRecognizerPtr2);
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call OnRejected function and compare result.
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->OnRejected();
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step2. call OnRejected function and compare result.
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->OnRejected();
    clickRecognizerPtr2->refereeState_ = RefereeState::FAIL;
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: ParallelRecognizerOnRejectedTest002
 * @tc.desc: Test ParallelRecognizer function: OnAccepted OnRejected OnPending OnBlock
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerOnRejectedTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr2->refereeState_ = RefereeState::PENDING_BLOCKED;


    std::vector<RefPtr<NGGestureRecognizer>> recognizers2 = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizerPtr = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers2);
    exclusiveRecognizerPtr->refereeState_ = RefereeState::PENDING_BLOCKED;
    recognizers.insert(recognizers.end(), exclusiveRecognizerPtr);
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call OnRejected function and compare result.
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->OnRejected();
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step2. call OnRejected function and compare result.
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->OnRejected();
    exclusiveRecognizerPtr->refereeState_ = RefereeState::FAIL;
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: ParallelRecognizerTest001
 * @tc.desc: Test ParallelRecognizer function: OnAccepted OnRejected OnPending OnBlock
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case1: recognizer is nullptr
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->currentBatchRecognizer_ = nullptr;
    parallelRecognizer->OnAccepted();
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case2: recognizer is not nullptr
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->currentBatchRecognizer_ = clickRecognizerPtr;
    parallelRecognizer->OnAccepted();
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.expected: step3. result equals.
     */
    parallelRecognizer->OnRejected();
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step4. call OnPending function and compare result.
     * @tc.steps: case1: recognizer is nullptr
     * @tc.expected: step4. result equals.
     */
    parallelRecognizer->currentBatchRecognizer_ = nullptr;
    parallelRecognizer->OnPending();
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step4. call OnPending function and compare result.
     * @tc.steps: case2: recognizer is not nullptr
     * @tc.expected: step4. result equals.
     */
    parallelRecognizer->currentBatchRecognizer_ = clickRecognizerPtr;
    parallelRecognizer->OnPending();
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case1: disposal is ACCEPT, current is nullptr
     * @tc.expected: step5. result equals.
     */
    parallelRecognizer->currentBatchRecognizer_ = nullptr;
    parallelRecognizer->disposal_ = GestureDisposal::ACCEPT;
    parallelRecognizer->OnBlocked();
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::SUCCEED_BLOCKED);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case2: disposal is ACCEPT, current is not nullptr
     * @tc.expected: step5. result equals.
     */
    parallelRecognizer->currentBatchRecognizer_ = clickRecognizerPtr;
    parallelRecognizer->disposal_ = GestureDisposal::ACCEPT;
    parallelRecognizer->OnBlocked();
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::SUCCEED_BLOCKED);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case3: disposal is PENDING, current is nullptr
     * @tc.expected: step5. result equals.
     */
    parallelRecognizer->currentBatchRecognizer_ = nullptr;
    parallelRecognizer->disposal_ = GestureDisposal::PENDING;
    parallelRecognizer->OnBlocked();
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::PENDING_BLOCKED);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case4: disposal is PENDING, current is not nullptr
     * @tc.expected: step5. result equals.
     */
    parallelRecognizer->currentBatchRecognizer_ = clickRecognizerPtr;
    parallelRecognizer->disposal_ = GestureDisposal::NONE;
    parallelRecognizer->OnBlocked();
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::PENDING_BLOCKED);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case4: disposal is PENDING, current is not nullptr
     * @tc.expected: step5. result equals.
     */
    parallelRecognizer->currentBatchRecognizer_ = clickRecognizerPtr;
    parallelRecognizer->disposal_ = GestureDisposal::PENDING;
    parallelRecognizer->OnBlocked();
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::PENDING_BLOCKED);
}

/**
 * @tc.name: ParallelRecognizerTest002
 * @tc.desc: Test ParallelRecognizer function: HandleEvent
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case1: refereeState is READY, recognizers is empty
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->refereeState_ = RefereeState::READY;
    TouchEvent touchEvent;
    auto result = parallelRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::DETECTING);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case2: refereeState is PENDING, recognizers have nullptr
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->refereeState_ = RefereeState::PENDING;
    parallelRecognizer->recognizers_.clear();
    parallelRecognizer->recognizers_.push_back(nullptr);
    result = parallelRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::PENDING);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case3: refereeState is PENDING, recognizers have ptr, not check
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->refereeState_ = RefereeState::PENDING;
    parallelRecognizer->recognizers_.clear();
    parallelRecognizer->recognizers_.push_back(clickRecognizerPtr);
    result = parallelRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::PENDING);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case4: refereeState is PENDING, recognizers have ptr, check
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    parallelRecognizer->refereeState_ = RefereeState::PENDING;
    parallelRecognizer->recognizers_.clear();
    parallelRecognizer->recognizers_.push_back(clickRecognizerPtr);
    result = parallelRecognizer->HandleEvent(touchEvent);
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::PENDING);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: ParallelRecognizerHandleEventTest001
 * @tc.desc: Test ParallelRecognizer function: HandleEvent
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerHandleEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case1: refereeState is READY, recognizers is empty
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->refereeState_ = RefereeState::READY;
    TouchEvent touchEvent;
    AxisEvent axisEvent;
    auto result = parallelRecognizer->HandleEvent(axisEvent);
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::DETECTING);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case2: refereeState is PENDING, recognizers have nullptr
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->refereeState_ = RefereeState::PENDING;
    parallelRecognizer->recognizers_.clear();
    parallelRecognizer->recognizers_.push_back(nullptr);
    result = parallelRecognizer->HandleEvent(axisEvent);
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::PENDING);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case3: refereeState is PENDING, recognizers have ptr, not check
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->refereeState_ = RefereeState::PENDING;
    parallelRecognizer->recognizers_.clear();
    parallelRecognizer->recognizers_.push_back(clickRecognizerPtr);
    result = parallelRecognizer->HandleEvent(axisEvent);
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::PENDING);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case4: refereeState is PENDING, recognizers have ptr, check
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    parallelRecognizer->refereeState_ = RefereeState::PENDING;
    parallelRecognizer->recognizers_.clear();
    parallelRecognizer->recognizers_.push_back(clickRecognizerPtr);
    result = parallelRecognizer->HandleEvent(axisEvent);
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::PENDING);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: ParallelRecognizerTest003
 * @tc.desc: Test ParallelRecognizer function: BatchAdjudicate
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case1: disposal is ACCEPT, refereeState is SUCCEED
     * @tc.expected: step2. expect return
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case2: disposal is ACCEPT, refereeState is PENDING, refereeState_ is SUCCEED
     * @tc.expected: step2. expect SUCCESS
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    parallelRecognizer->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case3: disposal is ACCEPT, refereeState is PENDING, refereeState_ is PENDING_BLOCKED
     * @tc.expected: step2. expect PENDING
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    parallelRecognizer->refereeState_ = RefereeState::PENDING_BLOCKED;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case4: disposal is REJECT, refereeState is FAIL
     * @tc.expected: step2. expect FAIL
     */
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    parallelRecognizer->refereeState_ = RefereeState::FAIL;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::REJECT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case5: disposal is PENDING, refereeState is PENDING, refereeState_ is PENDING
     * @tc.expected: step2. expect PENDING
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    parallelRecognizer->refereeState_ = RefereeState::PENDING;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case6: disposal is PENDING, refereeState is READY, refereeState_ is PENDING
     * @tc.expected: step2. expect PENDING
     */
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    parallelRecognizer->refereeState_ = RefereeState::PENDING;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case7: disposal is PENDING, refereeState is READY, refereeState_ is PENDING_BLOCKED
     * @tc.expected: step2. expect PENDING_CLOCKED
     */
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    parallelRecognizer->refereeState_ = RefereeState::PENDING_BLOCKED;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: ParallelRecognizerBatchAdjudicateTest001
 * @tc.desc: Test ParallelRecognizer function: BatchAdjudicate
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerBatchAdjudicateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case1: disposal is ACCEPT, refereeState is SUCCEED
     * @tc.expected: step2. expect return
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case2: disposal is ACCEPT, refereeState is PENDING, refereeState_ is SUCCEED
     * @tc.expected: step2. expect SUCCESS
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    parallelRecognizer->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case3: disposal is ACCEPT, refereeState is PENDING, refereeState_ is PENDING_BLOCKED
     * @tc.expected: step2. expect PENDING
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    parallelRecognizer->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case4: disposal is REJECT, refereeState is FAIL
     * @tc.expected: step2. expect FAIL
     */
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    parallelRecognizer->refereeState_ = RefereeState::FAIL;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::REJECT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case5: disposal is PENDING, refereeState is PENDING, refereeState_ is PENDING
     * @tc.expected: step2. expect PENDING
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    parallelRecognizer->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case6: disposal is PENDING, refereeState is READY, refereeState_ is PENDING
     * @tc.expected: step2. expect PENDING
     */
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    parallelRecognizer->refereeState_ = RefereeState::PENDING;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case7: disposal is PENDING, refereeState is READY, refereeState_ is PENDING_BLOCKED
     * @tc.expected: step2. expect PENDING_CLOCKED
     */
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    parallelRecognizer->refereeState_ = RefereeState::PENDING_BLOCKED;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: ParallelRecognizerTest004
 * @tc.desc: Test ParallelRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    RefPtr<ParallelRecognizer> parallelRecognizerPtr = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    bool result = false;

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    result = parallelRecognizer->ReconcileFrom(parallelRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is nullptr
     * @tc.expected: step2. result equals.
     */
    result = parallelRecognizer->ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case3: recognizers_ = {nullptr};
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->recognizers_ = { nullptr };
    result = parallelRecognizer->ReconcileFrom(parallelRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case4: recognizers_ = {};
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->recognizers_ = {};
    result = parallelRecognizer->ReconcileFrom(parallelRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case5: curr->priorityMask_ != priorityMask_
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->priorityMask_ = GestureMask::Normal;
    parallelRecognizerPtr->priorityMask_ = GestureMask::Begin;
    result = parallelRecognizer->ReconcileFrom(parallelRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case6: size and Mask is same, child is nullptr
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->priorityMask_ = parallelRecognizerPtr->priorityMask_;
    parallelRecognizer->recognizers_.clear();
    parallelRecognizerPtr->recognizers_.clear();
    parallelRecognizer->recognizers_.push_back(nullptr);
    parallelRecognizerPtr->recognizers_.push_back(nullptr);
    result = parallelRecognizer->ReconcileFrom(parallelRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case7: size and Mask is same, child is ptr
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->recognizers_.clear();
    parallelRecognizerPtr->recognizers_.clear();
    parallelRecognizer->recognizers_.push_back(clickRecognizerPtr);
    parallelRecognizerPtr->recognizers_.push_back(clickRecognizerPtr);
    result = parallelRecognizer->ReconcileFrom(parallelRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case8: size and Mask is same, child is ptr and nullptr
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->recognizers_.clear();
    parallelRecognizerPtr->recognizers_.clear();
    parallelRecognizer->recognizers_.push_back(clickRecognizerPtr);
    parallelRecognizerPtr->recognizers_.push_back(nullptr);
    result = parallelRecognizer->ReconcileFrom(parallelRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: ParallelRecognizerTest005
 * @tc.desc: Test ParallelRecognizer function: CleanRecognizerState
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {clickRecognizerPtr};
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    /**
     * @tc.steps: step3. set child recognizer state and call cleanRecognizerState function and compare result.
     * @tc.steps: case1: touchPoints size is 1, clean success.
     * @tc.expected: step3. clickRecognizer state set ready.
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer->CleanRecognizerState();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);

    /**
     * @tc.steps: step3. set child recognizer state and call cleanRecognizerState function and compare result.
     * @tc.steps: case2: touchPoints size is 2, clean fail.
     * @tc.expected: step3. clickRecognizer state set ready.
     */
    clickRecognizerPtr->touchPoints_[0] = {};
    clickRecognizerPtr->touchPoints_[1] = {};
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer->CleanRecognizerState();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);
}
} // namespace OHOS::Ace::NG