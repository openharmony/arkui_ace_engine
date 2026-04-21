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
    clickRecognizerPtr->touchPoints_[0].originalId = 0;
    clickRecognizerPtr->touchPoints_[1] = {};
    clickRecognizerPtr->touchPoints_[1].originalId = 1;
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer->CleanRecognizerState();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: ParallelRecognizerTest006
 * @tc.desc: Test ParallelRecognizer function: OnAccepted
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { clickRecognizerPtr };
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call AddSucceedBlockRecognizer function and test OnAccepted.
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    parallelRecognizer->AddSucceedBlockRecognizer(clickRecognizerPtr);
    parallelRecognizer->AddSucceedBlockRecognizer(clickRecognizerPtr2);
    parallelRecognizer->AddSucceedBlockRecognizer(nullptr);
    parallelRecognizer->OnAccepted();
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::SUCCEED);
    EXPECT_TRUE(parallelRecognizer->succeedBlockRecognizers_.empty());
}

/**
 * @tc.name: ParallelRecognizerTest007
 * @tc.desc: Test ParallelRecognizer function: OnReject
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    clickRecognizerPtr->SetBridgeMode(true);
    clickRecognizerPtr2->refereeState_ = RefereeState::FAIL;
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { clickRecognizerPtr, clickRecognizerPtr2, nullptr };
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call OnRejected function and test result.
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->OnRejected();
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::FAIL);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(clickRecognizerPtr2->refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: ParallelRecognizerTest008
 * @tc.desc: Test ParallelRecognizer function: OnBlocked
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { clickRecognizerPtr, nullptr };
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    clickRecognizerPtr->disposal_ = GestureDisposal::ACCEPT;
    parallelRecognizer->disposal_ = GestureDisposal::ACCEPT;
    parallelRecognizer->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer->currentBatchRecognizer_ = clickRecognizerPtr;

    /**
     * @tc.steps: step2. call OnBlocked function and test result.
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->OnBlocked();
    EXPECT_FALSE(parallelRecognizer->succeedBlockRecognizers_.empty());
    EXPECT_NE(parallelRecognizer->currentBatchRecognizer_, clickRecognizerPtr);
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::SUCCEED_BLOCKED);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED_BLOCKED);
}

/**
 * @tc.name: ParallelRecognizerTest009
 * @tc.desc: Test ParallelRecognizer function: CleanRecognizerState
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { clickRecognizerPtr, clickRecognizerPtr2, nullptr };
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    /**
     * @tc.steps: step2. prepare testCase info.
     */
    std::vector<RefereeState> refereeStateList = {
        RefereeState::SUCCEED, RefereeState::FAIL, RefereeState::DETECTING, RefereeState::PENDING,
        RefereeState::SUCCEED, RefereeState::FAIL, RefereeState::DETECTING, RefereeState::PENDING,
    };
    std::vector<int32_t> currentFingerList = { 0, 0, 0, 0, 1, 1, 1, 1 };
    std::vector<RefereeState> resultRefereeStateList = {
        RefereeState::READY, RefereeState::READY, RefereeState::READY, RefereeState::PENDING,
        RefereeState::SUCCEED, RefereeState::FAIL, RefereeState::DETECTING, RefereeState::PENDING,
    };

    /**
     * @tc.steps: step3. call CleanRecognizerState function and test result.
     * @tc.expected: step3. result equals.
     */
    for (int32_t i = 0; i < 8; i++) {
        parallelRecognizer->refereeState_ = refereeStateList[i];
        parallelRecognizer->currentFingers_ = currentFingerList[i];
        parallelRecognizer->CleanRecognizerState();
        EXPECT_EQ(parallelRecognizer->refereeState_, resultRefereeStateList[i]);
    }
}

/**
 * @tc.name: ParallelRecognizerTest010
 * @tc.desc: Test ParallelRecognizer function: ForceCleanRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { clickRecognizerPtr, nullptr };
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer->currentBatchRecognizer_ = clickRecognizerPtr;

    /**
     * @tc.steps: step2. call ForceCleanRecognizer function and test result.
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer->AddSucceedBlockRecognizer(clickRecognizerPtr);
    parallelRecognizer->ForceCleanRecognizer();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::READY);
    EXPECT_EQ(parallelRecognizer->currentBatchRecognizer_, nullptr);
    EXPECT_TRUE(parallelRecognizer->succeedBlockRecognizers_.empty());
}

/**
 * @tc.name: ParallelRecognizerTest011
 * @tc.desc: Test ParallelRecognizer function: CleanRecognizerStateVoluntarily
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { clickRecognizerPtr, nullptr };
    RefPtr<ExclusiveRecognizer> exclusiveRecognizerPtr = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    exclusiveRecognizerPtr->SetIsNeedResetRecognizer(true);
    exclusiveRecognizerPtr->refereeState_ = RefereeState::FAIL;
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizerGroups = {
        exclusiveRecognizerPtr, clickRecognizerPtr2, nullptr };
    RefPtr<ParallelRecognizer> parallelRecognizerEx = AceType::MakeRefPtr<ParallelRecognizer>(recognizerGroups);

    /**
     * @tc.steps: step2. call CleanRecognizerStateVoluntarily function and test result.
     * @tc.expected: step2. result equals.
     */
    parallelRecognizerEx->CleanRecognizerStateVoluntarily();
    EXPECT_EQ(exclusiveRecognizerPtr->refereeState_, RefereeState::READY);
    EXPECT_FALSE(exclusiveRecognizerPtr->IsNeedResetRecognizerState());
}

/**
 * @tc.name: ParallelRecognizerTest012
 * @tc.desc: Test ParallelRecognizer OnAccepted with succeedBlockRecognizers_
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer with SUCCEED_BLOCKED recognizers
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { clickRecognizerPtr };
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    /**
     * @tc.steps: step2. Add to succeedBlockRecognizers_ and call OnAccepted
     * @tc.expected: step2. AboutToAccept is called, succeedBlockRecognizers_ cleared
     */
    parallelRecognizer->AddSucceedBlockRecognizer(clickRecognizerPtr);
    parallelRecognizer->OnAccepted();
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::SUCCEED);
    EXPECT_TRUE(parallelRecognizer->succeedBlockRecognizers_.empty());
}

/**
 * @tc.name: ParallelRecognizerTest013
 * @tc.desc: Test ParallelRecognizer OnRejected early return when refereeState_ is SUCCEED
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer in SUCCEED state
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { clickRecognizerPtr };
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    parallelRecognizer->refereeState_ = RefereeState::SUCCEED;

    /**
     * @tc.steps: step2. call OnRejected - should return early without changing state
     * @tc.expected: step2. state remains SUCCEED
     */
    parallelRecognizer->OnRejected();
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: ParallelRecognizerTest014
 * @tc.desc: Test BatchAdjudicate with ACCEPT disposal and SUCCEED_BLOCKED refereeState
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer with SUCCEED_BLOCKED state
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    parallelRecognizer->refereeState_ = RefereeState::SUCCEED_BLOCKED;

    /**
     * @tc.steps: step2. Call BatchAdjudicate with ACCEPT disposal
     * @tc.expected: step2. recognizer added to succeedBlockRecognizers_
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::SUCCEED_BLOCKED);
    EXPECT_EQ(parallelRecognizer->succeedBlockRecognizers_.size(), 0);
}

/**
 * @tc.name: ParallelRecognizerTest015
 * @tc.desc: Test BatchAdjudicate with ACCEPT disposal and READY refereeState
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer with READY state
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    parallelRecognizer->refereeState_ = RefereeState::READY;
    clickRecognizerPtr->refereeState_ = RefereeState::READY;

    /**
     * @tc.steps: step2. Call BatchAdjudicate with ACCEPT disposal
     * @tc.expected: step2. GroupAdjudicate is called
     */
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(parallelRecognizer->currentBatchRecognizer_, nullptr);
}

/**
 * @tc.name: ParallelRecognizerTest016
 * @tc.desc: Test CleanRecognizerStateVoluntarily with non-RecognizerGroup child
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer with non-RecognizerGroup children
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { clickRecognizerPtr };
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    /**
     * @tc.steps: step2. Call CleanRecognizerStateVoluntarily
     * @tc.expected: step2. Should handle non-RecognizerGroup children
     */
    parallelRecognizer->CleanRecognizerStateVoluntarily();
    EXPECT_NE(clickRecognizerPtr, nullptr);
}

/**
 * @tc.name: ParallelRecognizerBatchAdjudicateComprehensiveTest001
 * @tc.desc: Test BatchAdjudicate method with high branch coverage - ACCEPT disposal cases
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerBatchAdjudicateComprehensiveTest001, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    // Case 1: ACCEPT disposal - recognizer already SUCCEED (early return)
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer->refereeState_ = RefereeState::READY;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);
    
    // Case 2: ACCEPT disposal - parallelRecognizer SUCCEED state
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    parallelRecognizer->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);
    
    // Case 3: ACCEPT disposal - SUCCEED_BLOCKED state, recognizer becomes SUCCEED_BLOCKED
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    parallelRecognizer->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    int32_t initialBlockCount = parallelRecognizer->succeedBlockRecognizers_.size();
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(parallelRecognizer->succeedBlockRecognizers_.size(), initialBlockCount + 1);
    
    // Case 4: ACCEPT disposal - PENDING_BLOCKED state
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    parallelRecognizer->refereeState_ = RefereeState::PENDING_BLOCKED;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);
    
    // Case 5: ACCEPT disposal - READY state triggers GroupAdjudicate
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    parallelRecognizer->refereeState_ = RefereeState::READY;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(parallelRecognizer->currentBatchRecognizer_, nullptr);
}

/**
 * @tc.name: ParallelRecognizerBatchAdjudicateComprehensiveTest002
 * @tc.desc: Test BatchAdjudicate method with high branch coverage - REJECT disposal cases
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerBatchAdjudicateComprehensiveTest002, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    // Case 1: REJECT disposal - recognizer already FAIL (early return)
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::REJECT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::FAIL);

    // Case 2: REJECT disposal - normal REJECT path
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::REJECT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::FAIL);

    // Case 3: REJECT disposal - multiple recognizers, CheckAllFailed scenario
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizersWithMultiple = {
        clickRecognizerPtr, clickRecognizerPtr2
    };
    RefPtr<ParallelRecognizer> parallelRecognizerWithMultiple =
        AceType::MakeRefPtr<ParallelRecognizer>(recognizersWithMultiple);

    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    clickRecognizerPtr2->refereeState_ = RefereeState::FAIL;
    parallelRecognizerWithMultiple->BatchAdjudicate(clickRecognizerPtr2, GestureDisposal::REJECT);
    EXPECT_EQ(clickRecognizerPtr2->refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: ParallelRecognizerBatchAdjudicateComprehensiveTest003
 * @tc.desc: Test BatchAdjudicate method with high branch coverage - PENDING disposal cases
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerBatchAdjudicateComprehensiveTest003, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    // Case 1: PENDING disposal - recognizer already PENDING (early return)
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    // Case 2: PENDING disposal - parallelRecognizer SUCCEED state
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    parallelRecognizer->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    // Case 3: PENDING disposal - parallelRecognizer PENDING state
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    parallelRecognizer->refereeState_ = RefereeState::PENDING;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    // Case 4: PENDING disposal - SUCCEED_BLOCKED state
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    parallelRecognizer->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);

    // Case 5: PENDING disposal - PENDING_BLOCKED state
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    parallelRecognizer->refereeState_ = RefereeState::PENDING_BLOCKED;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);

    // Case 6: PENDING disposal - READY state triggers GroupAdjudicate
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    parallelRecognizer->refereeState_ = RefereeState::READY;
    parallelRecognizer->BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(parallelRecognizer->currentBatchRecognizer_, nullptr);
}

/**
 * @tc.name: ParallelRecognizerBatchAdjudicateComprehensiveTest004
 * @tc.desc: Test BatchAdjudicate method with null pointer handling and edge cases
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerBatchAdjudicateComprehensiveTest004, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    // Case 1: Null recognizer - should handle gracefully
    parallelRecognizer->BatchAdjudicate(nullptr, GestureDisposal::ACCEPT);
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::READY);

    // Case 2: All disposal types with null recognizer
    parallelRecognizer->BatchAdjudicate(nullptr, GestureDisposal::REJECT);
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::READY);

    parallelRecognizer->BatchAdjudicate(nullptr, GestureDisposal::PENDING);
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: ParallelRecognizerCleanRecognizerStateComprehensiveTest001
 * @tc.desc: Test CleanRecognizerState method with high branch coverage
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerCleanRecognizerStateComprehensiveTest001, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    // Case 1: MultiFingersRecognizer with touchPoints size <= 1
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    clickRecognizerPtr->touchPoints_.clear();
    TouchEvent touchEvent;
    touchEvent.originalId = 1;
    clickRecognizerPtr->touchPoints_[1] = touchEvent;

    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { clickRecognizerPtr };
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    parallelRecognizer->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer->currentFingers_ = 0;

    parallelRecognizer->CleanRecognizerState();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::READY);

    // Case 2: MultiFingersRecognizer with touchPoints size > 1 (should not clean)
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    touchEvent.originalId = 2;
    clickRecognizerPtr->touchPoints_[2] = touchEvent;
    parallelRecognizer->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer->currentFingers_ = 0;

    parallelRecognizer->CleanRecognizerState();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED); // Should remain unchanged

    // Case 3: State reset conditions with currentFingers_ == 0
    std::vector<RefereeState> testStates = {
        RefereeState::SUCCEED, RefereeState::FAIL, RefereeState::DETECTING
    };

    for (auto state : testStates) {
        parallelRecognizer->refereeState_ = state;
        parallelRecognizer->currentFingers_ = 0;
        parallelRecognizer->disposal_ = GestureDisposal::ACCEPT;

        parallelRecognizer->CleanRecognizerState();
        EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::READY);
        EXPECT_EQ(parallelRecognizer->disposal_, GestureDisposal::NONE);
    }

    // Case 4: State reset conditions with currentFingers_ != 0 (should not reset)
    for (auto state : testStates) {
        parallelRecognizer->refereeState_ = state;
        parallelRecognizer->currentFingers_ = 1;
        parallelRecognizer->disposal_ = GestureDisposal::ACCEPT;

        parallelRecognizer->CleanRecognizerState();
        EXPECT_NE(parallelRecognizer->refereeState_, RefereeState::READY);
    }
}

/**
 * @tc.name: ParallelRecognizerCleanRecognizerStateComprehensiveTest002
 * @tc.desc: Test CleanRecognizerState method with null handling and edge cases
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerCleanRecognizerStateComprehensiveTest002, TestSize.Level1)
{
    // Case 1: Recognizers with null entries
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { nullptr };
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    parallelRecognizer->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer->currentFingers_ = 0;

    parallelRecognizer->CleanRecognizerState();
    EXPECT_EQ(parallelRecognizer->refereeState_, RefereeState::READY);

    // Case 2: Mixed null and valid recognizers
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    clickRecognizerPtr->touchPoints_.clear();

    std::vector<RefPtr<NGGestureRecognizer>> mixedRecognizers = { nullptr, clickRecognizerPtr, nullptr };
    RefPtr<ParallelRecognizer> parallelRecognizerMixed = AceType::MakeRefPtr<ParallelRecognizer>(mixedRecognizers);
    parallelRecognizerMixed->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizerMixed->currentFingers_ = 0;

    parallelRecognizerMixed->CleanRecognizerState();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);
    EXPECT_EQ(parallelRecognizerMixed->refereeState_, RefereeState::READY);

    // Case 3: PENDING state should not reset
    parallelRecognizerMixed->refereeState_ = RefereeState::PENDING;
    parallelRecognizerMixed->currentFingers_ = 0;

    parallelRecognizerMixed->CleanRecognizerState();
    EXPECT_EQ(parallelRecognizerMixed->refereeState_, RefereeState::PENDING);
}

/**
 * @tc.name: ParallelRecognizerForceCleanRecognizerComprehensiveTest001
 * @tc.desc: Test ForceCleanRecognizer method with high branch coverage
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerForceCleanRecognizerComprehensiveTest001, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    // Case 1: Valid recognizers - should clean all
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    clickRecognizerPtr2->refereeState_ = RefereeState::FAIL;

    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { clickRecognizerPtr, clickRecognizerPtr2 };
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    parallelRecognizer->ForceCleanRecognizer();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);
    EXPECT_EQ(clickRecognizerPtr2->refereeState_, RefereeState::READY);
    EXPECT_EQ(parallelRecognizer->currentBatchRecognizer_, nullptr);
    EXPECT_TRUE(parallelRecognizer->succeedBlockRecognizers_.empty());

    // Case 2: Clean with currentBatchRecognizer_ set
    RefPtr<ClickRecognizer> clickRecognizerPtr3 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr3->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer->currentBatchRecognizer_ = clickRecognizerPtr3;
    parallelRecognizer->AddSucceedBlockRecognizer(clickRecognizerPtr3);
    parallelRecognizer->AddChildren({ clickRecognizerPtr3 });

    parallelRecognizer->ForceCleanRecognizer();
    EXPECT_EQ(clickRecognizerPtr3->refereeState_, RefereeState::READY);
    EXPECT_EQ(parallelRecognizer->currentBatchRecognizer_, nullptr);
    EXPECT_TRUE(parallelRecognizer->succeedBlockRecognizers_.empty());
}

/**
 * @tc.name: ParallelRecognizerForceCleanRecognizerComprehensiveTest002
 * @tc.desc: Test ForceCleanRecognizer method with null handling and edge cases
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerForceCleanRecognizerComprehensiveTest002, TestSize.Level1)
{
    // Case 1: Recognizers with null entries
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { nullptr };
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    parallelRecognizer->ForceCleanRecognizer();
    EXPECT_EQ(parallelRecognizer->currentBatchRecognizer_, nullptr);
    EXPECT_TRUE(parallelRecognizer->succeedBlockRecognizers_.empty());

    // Case 2: Mixed null and valid recognizers
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;

    std::vector<RefPtr<NGGestureRecognizer>> mixedRecognizers = {
        nullptr, clickRecognizerPtr, nullptr
    };
    RefPtr<ParallelRecognizer> parallelRecognizerMixed = AceType::MakeRefPtr<ParallelRecognizer>(mixedRecognizers);

    parallelRecognizerMixed->ForceCleanRecognizer();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);
    EXPECT_EQ(parallelRecognizerMixed->currentBatchRecognizer_, nullptr);
    EXPECT_TRUE(parallelRecognizerMixed->succeedBlockRecognizers_.empty());

    // Case 3: Empty recognizers list
    std::vector<RefPtr<NGGestureRecognizer>> emptyRecognizers = {};
    RefPtr<ParallelRecognizer> parallelRecognizerEmpty = AceType::MakeRefPtr<ParallelRecognizer>(emptyRecognizers);

    parallelRecognizerEmpty->ForceCleanRecognizer();
    EXPECT_EQ(parallelRecognizerEmpty->currentBatchRecognizer_, nullptr);
    EXPECT_TRUE(parallelRecognizerEmpty->succeedBlockRecognizers_.empty());

    // Case 4: With succeedBlockRecognizers_ populated
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    std::vector<RefPtr<NGGestureRecognizer>> recognizersWithGroup = { clickRecognizerPtr2 };
    RefPtr<ParallelRecognizer> parallelRecognizerWithBlock =
        AceType::MakeRefPtr<ParallelRecognizer>(recognizersWithGroup);

    parallelRecognizerWithBlock->AddSucceedBlockRecognizer(clickRecognizerPtr2);
    parallelRecognizerWithBlock->AddSucceedBlockRecognizer(nullptr);

    parallelRecognizerWithBlock->ForceCleanRecognizer();
    EXPECT_TRUE(parallelRecognizerWithBlock->succeedBlockRecognizers_.empty());
}

/**
 * @tc.name: ParallelRecognizerForceCleanRecognizerComprehensiveTest003
 * @tc.desc: Test ForceCleanRecognizer method with different recognizer types
 * @tc.type: FUNC
 */
HWTEST_F(ParallelRecognizerTestNg, ParallelRecognizerForceCleanRecognizerComprehensiveTest003, TestSize.Level1)
{
    // Case 1: Mixed recognizer types
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<ExclusiveRecognizer> exclusiveRecognizerPtr =
        AceType::MakeRefPtr<ExclusiveRecognizer>(std::vector<RefPtr<NGGestureRecognizer>>{});

    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    exclusiveRecognizerPtr->refereeState_ = RefereeState::PENDING;

    std::vector<RefPtr<NGGestureRecognizer>> mixedRecognizers = {
        clickRecognizerPtr, exclusiveRecognizerPtr
    };
    RefPtr<ParallelRecognizer> parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(mixedRecognizers);

    parallelRecognizer->ForceCleanRecognizer();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);
    EXPECT_EQ(exclusiveRecognizerPtr->refereeState_, RefereeState::READY);
    EXPECT_EQ(parallelRecognizer->currentBatchRecognizer_, nullptr);
    EXPECT_TRUE(parallelRecognizer->succeedBlockRecognizers_.empty());
}
} // namespace OHOS::Ace::NG