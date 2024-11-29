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
class ExclusiveRecognizerTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void ExclusiveRecognizerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void ExclusiveRecognizerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: ExclusiveRecognizerHandleRejectDisposalTest002
 * @tc.desc: Test ExclusiveRecognizer HandleRejectDisposal function
 */
HWTEST_F(ExclusiveRecognizerTestNg, ExclusiveRecognizerHandleRejectDisposalTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizerPtr = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is FAIL
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    exclusiveRecognizerPtr->HandleRejectDisposal(clickRecognizerPtr);
    EXPECT_EQ(exclusiveRecognizerPtr->recognizers_.size(), 0);
}

/**
 * @tc.name: ExclusiveRecognizerHandleRejectDisposalTest003
 * @tc.desc: Test ExclusiveRecognizer HandleRejectDisposal function
 */
HWTEST_F(ExclusiveRecognizerTestNg, ExclusiveRecognizerHandleRejectDisposalTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizerPtr = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is FAIL
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    exclusiveRecognizerPtr->HandleRejectDisposal(clickRecognizerPtr);
    EXPECT_EQ(exclusiveRecognizerPtr->recognizers_.size(), 0);
}

/**
 * @tc.name: ExclusiveRecognizerHandleRejectDisposalTest005
 * @tc.desc: Test ExclusiveRecognizer HandleRejectDisposal function
 */
HWTEST_F(ExclusiveRecognizerTestNg, ExclusiveRecognizerHandleRejectDisposalTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizerPtr = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is FAIL
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    exclusiveRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    exclusiveRecognizerPtr->HandleRejectDisposal(clickRecognizerPtr);
    EXPECT_EQ(exclusiveRecognizerPtr->recognizers_.size(), 0);
}

/**
 * @tc.name: ExclusiveRecognizerHandleRejectDisposalTest006
 * @tc.desc: Test ExclusiveRecognizer HandleRejectDisposal function
 */
HWTEST_F(ExclusiveRecognizerTestNg, ExclusiveRecognizerHandleRejectDisposalTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizerPtr = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is FAIL
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    exclusiveRecognizerPtr->refereeState_ = RefereeState::PENDING;
    exclusiveRecognizerPtr->HandleRejectDisposal(clickRecognizerPtr);
    EXPECT_EQ(exclusiveRecognizerPtr->recognizers_.size(), 0);
}

/**
 * @tc.name: ExclusiveRecognizerHandlePendingDisposalTest001
 * @tc.desc: Test ExclusiveRecognizer HandlePendingDisposal function
 */
HWTEST_F(ExclusiveRecognizerTestNg, ExclusiveRecognizerHandlePendingDisposalTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr2->refereeState_ = RefereeState::PENDING;
    recognizers.insert(recognizers.end(), clickRecognizerPtr2);
    RefPtr<ExclusiveRecognizer> exclusiveRecognizerPtr = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is FAIL
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    exclusiveRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    exclusiveRecognizerPtr->HandlePendingDisposal(clickRecognizerPtr);
    EXPECT_EQ(exclusiveRecognizerPtr->recognizers_.size(), 1);
}

/**
 * @tc.name: ExclusiveRecognizerHandleAcceptDisposalTest001
 * @tc.desc: Test ExclusiveRecognizer HandleAcceptDisposal function
 */
HWTEST_F(ExclusiveRecognizerTestNg, ExclusiveRecognizerHandleAcceptDisposalTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr2->refereeState_ = RefereeState::PENDING;
    recognizers.insert(recognizers.end(), clickRecognizerPtr2);
    RefPtr<ExclusiveRecognizer> exclusiveRecognizerPtr = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is FAIL
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    exclusiveRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    exclusiveRecognizerPtr->HandleAcceptDisposal(clickRecognizerPtr);
    EXPECT_EQ(exclusiveRecognizerPtr->recognizers_.size(), 1);
}

/**
 * @tc.name: ExclusiveRecognizerHandlePendingDisposalTest002
 * @tc.desc: Test ExclusiveRecognizer HandlePendingDisposal function
 */
HWTEST_F(ExclusiveRecognizerTestNg, ExclusiveRecognizerHandlePendingDisposalTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr2->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    recognizers.insert(recognizers.end(), clickRecognizerPtr2);
    RefPtr<ExclusiveRecognizer> exclusiveRecognizerPtr = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is FAIL
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    exclusiveRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    exclusiveRecognizerPtr->HandlePendingDisposal(clickRecognizerPtr);
    EXPECT_EQ(exclusiveRecognizerPtr->recognizers_.size(), 1);
}

/**
 * @tc.name: ExclusiveRecognizerHandleAcceptDisposalTest002
 * @tc.desc: Test ExclusiveRecognizer HandleAcceptDisposal function
 */
HWTEST_F(ExclusiveRecognizerTestNg, ExclusiveRecognizerHandleAcceptDisposalTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr2->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    recognizers.insert(recognizers.end(), clickRecognizerPtr2);
    RefPtr<ExclusiveRecognizer> exclusiveRecognizerPtr = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is FAIL
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    exclusiveRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    exclusiveRecognizerPtr->HandleAcceptDisposal(clickRecognizerPtr);
    EXPECT_EQ(exclusiveRecognizerPtr->recognizers_.size(), 1);
}

/**
 * @tc.name: ExclusiveRecognizerHandleRejectDisposalTest008
 * @tc.desc: Test ExclusiveRecognizer HandleRejectDisposal function
 */
HWTEST_F(ExclusiveRecognizerTestNg, ExclusiveRecognizerHandleRejectDisposalTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr2->refereeState_ = RefereeState::PENDING_BLOCKED;
    recognizers.insert(recognizers.end(), clickRecognizerPtr2);
    RefPtr<ExclusiveRecognizer> exclusiveRecognizerPtr = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is FAIL
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    exclusiveRecognizerPtr->refereeState_ = RefereeState::PENDING;
    exclusiveRecognizerPtr->HandleRejectDisposal(clickRecognizerPtr);
    EXPECT_EQ(exclusiveRecognizerPtr->recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is FAIL
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    exclusiveRecognizerPtr->refereeState_ = RefereeState::PENDING;
    clickRecognizerPtr2->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    exclusiveRecognizerPtr->HandleRejectDisposal(clickRecognizerPtr);
    EXPECT_EQ(exclusiveRecognizerPtr->recognizers_.size(), 1);
}

/**
 * @tc.name: ExclusiveRecognizerTest001
 * @tc.desc: Test ExclusiveRecognizer function: OnAccepted OnRejected OnPending OnBlocked
 * @tc.type: FUNC
 */
HWTEST_F(ExclusiveRecognizerTestNg, ExclusiveRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<ClickRecognizer> clickRecognizerPtrNotSame = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case1: no active, no recognizers
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.OnAccepted();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case2: has active, recognizers has nullptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    exclusiveRecognizer.recognizers_.push_back(nullptr);
    exclusiveRecognizer.OnAccepted();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case3: has active, recognizers has ptr not same
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtrNotSame);
    exclusiveRecognizer.OnAccepted();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case4: has active, recognizers has ptr same
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer.OnAccepted();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.steps: case1: no recognizers
     * @tc.expected: step3. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.OnRejected();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.steps: case2: recognizers has nullptr
     * @tc.expected: step3. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(nullptr);
    exclusiveRecognizer.OnRejected();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.steps: case3: recognizers has ptr, referee is not FAIL
     * @tc.expected: step3. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer.OnRejected();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.steps: case4: recognizers has ptr, referee is FAIL
     * @tc.expected: step3. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer.OnRejected();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: ExclusiveRecognizerTest002
 * @tc.desc: Test ExclusiveRecognizer function: HandleEvent OnResetStatus
 * @tc.type: FUNC
 */
HWTEST_F(ExclusiveRecognizerTestNg, ExclusiveRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);

    /**
     * @tc.steps: step2. create touchEvent and call HandleEvent function and compare result.
     * @tc.steps: case1: active is nullptr, recognizers is empty
     * @tc.expected: step2. result equals.
     */
    bool result = false;
    TouchEvent touchEvent;
    touchEvent.type = TouchType::MOVE;
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);
    touchEvent.type = TouchType::DOWN;
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);
    touchEvent.type = TouchType::UP;
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);
    touchEvent.type = TouchType::CANCEL;
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);
    touchEvent.type = TouchType::UNKNOWN;
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. create touchEvent and call HandleEvent function and compare result.
     * @tc.steps: case2: active is not nullptr, checkTouchId is false
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    touchEvent.type = TouchType::DOWN;
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. create touchEvent and call HandleEvent function and compare result.
     * @tc.steps: case3: active is not nullptr, checkTouchId is true
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. create touchEvent and call HandleEvent function and compare result.
     * @tc.steps: case4: active is nullptr, recognizers have nullptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.activeRecognizer_ = nullptr;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(nullptr);
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. create touchEvent and call HandleEvent function and compare result.
     * @tc.steps: case5: active is nullptr, recognizers have ptr, ptr not check
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->touchPoints_.clear();
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. create touchEvent and call HandleEvent function and compare result.
     * @tc.steps: case6: active is nullptr, recognizers have ptr, ptr check
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->touchPoints_.clear();
    clickRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: ExclusiveRecognizerTest003
 * @tc.desc: Test ExclusiveRecognizer function: CheckNeedBlocked
 * @tc.type: FUNC
 */
HWTEST_F(ExclusiveRecognizerTestNg, ExclusiveRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);

    /**
     * @tc.steps: step2. call CheckNeedBlocked function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    auto result = exclusiveRecognizer.CheckNeedBlocked(clickRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call CheckNeedBlocked function and compare result.
     * @tc.steps: case2: recognizers is not empty, child == recognizer
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    result = exclusiveRecognizer.CheckNeedBlocked(clickRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call CheckNeedBlocked function and compare result.
     * @tc.steps: case3: recognizers is not empty, child is nullptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(nullptr);
    result = exclusiveRecognizer.CheckNeedBlocked(clickRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call CheckNeedBlocked function and compare result.
     * @tc.steps: case3: recognizers is not empty, child is ptr, refeeState not PENDING
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtrNotSame = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtrNotSame->refereeState_ = RefereeState::SUCCEED;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtrNotSame);
    result = exclusiveRecognizer.CheckNeedBlocked(clickRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call CheckNeedBlocked function and compare result.
     * @tc.steps: case4: recognizers is not empty, child is ptr, refeeState PENDING
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtrNotSame->refereeState_ = RefereeState::PENDING;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtrNotSame);
    result = exclusiveRecognizer.CheckNeedBlocked(clickRecognizerPtr);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: ExclusiveRecognizerTest004
 * @tc.desc: Test ExclusiveRecognizer function: UnBlockGesture
 * @tc.type: FUNC
 */
HWTEST_F(ExclusiveRecognizerTestNg, ExclusiveRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);

    /**
     * @tc.steps: step2. call UnBlockGesture function and compare result.
     * @tc.expected: step2. result equals.
     */
    auto result = exclusiveRecognizer.UnBlockGesture();
    EXPECT_EQ(result, nullptr);

    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    result = exclusiveRecognizer.UnBlockGesture();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: ExclusiveRecognizerTest005
 * @tc.desc: Test ExclusiveRecognizer function: BatchAdjudicate, and GestureDisposal
 * @tc.type: FUNC
 */
HWTEST_F(ExclusiveRecognizerTestNg, ExclusiveRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case1: refereeState_ is SUCCESS, return
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.refereeState_ = RefereeState::SUCCEED;
    exclusiveRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(exclusiveRecognizer.activeRecognizer_, nullptr);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case2: GestureDisposal::ACCEPT, recognizer is SUCCESS
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.refereeState_ = RefereeState::PENDING;
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    exclusiveRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(exclusiveRecognizer.activeRecognizer_, nullptr);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case3: GestureDisposal::PENDING, recognizer is PENDING
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.refereeState_ = RefereeState::PENDING;
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    exclusiveRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(exclusiveRecognizer.activeRecognizer_, nullptr);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case4: GestureDisposal::REJECT, recognizer is FAIL
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.refereeState_ = RefereeState::PENDING;
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    exclusiveRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::NONE);
    EXPECT_EQ(exclusiveRecognizer.activeRecognizer_, nullptr);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case4: GestureDisposal::REJECT, recognizer is FAIL
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.refereeState_ = RefereeState::PENDING;
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    exclusiveRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::REJECT);
    EXPECT_EQ(exclusiveRecognizer.activeRecognizer_, nullptr);
}

/**
 * @tc.name: ExclusiveRecognizerTest006
 * @tc.desc: Test ExclusiveRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(ExclusiveRecognizerTestNg, ExclusiveRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);
    RefPtr<ExclusiveRecognizer> exclusiveRecognizerPtr = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    auto result = exclusiveRecognizer.ReconcileFrom(exclusiveRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is nullptr
     * @tc.expected: step2. result equals.
     */
    result = exclusiveRecognizer.ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case3: recognizerPtr size not same
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.push_back(nullptr);
    result = exclusiveRecognizer.ReconcileFrom(exclusiveRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case4: recognizerPtr size not same, priorityMask not same
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.priorityMask_ = GestureMask::End;
    result = exclusiveRecognizer.ReconcileFrom(exclusiveRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case5: recognizerPtr size same, priorityMask not same
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizerPtr->recognizers_.clear();
    result = exclusiveRecognizer.ReconcileFrom(exclusiveRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case6: recognizerPtr same, child is nullptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.priorityMask_ = exclusiveRecognizerPtr->priorityMask_;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(nullptr);
    exclusiveRecognizerPtr->recognizers_.clear();
    exclusiveRecognizerPtr->recognizers_.push_back(nullptr);
    result = exclusiveRecognizer.ReconcileFrom(exclusiveRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case6: recognizerPtr same, child is nullptr
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    exclusiveRecognizer.priorityMask_ = exclusiveRecognizerPtr->priorityMask_;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizerPtr->recognizers_.clear();
    exclusiveRecognizerPtr->recognizers_.push_back(clickRecognizerPtr);
    result = exclusiveRecognizer.ReconcileFrom(exclusiveRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case6: recognizerPtr same, child is nullptr
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtrNotSame =
        AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER - 1, COUNT - 1);
    exclusiveRecognizer.priorityMask_ = exclusiveRecognizerPtr->priorityMask_;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizerPtr->recognizers_.clear();
    exclusiveRecognizerPtr->recognizers_.push_back(clickRecognizerPtrNotSame);
    result = exclusiveRecognizer.ReconcileFrom(exclusiveRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: ExclusiveRecognizerTest007
 * @tc.desc: Test ExclusiveRecognizer function: OnPending OnBlocked
 * @tc.type: FUNC
 */
HWTEST_F(ExclusiveRecognizerTestNg, ExclusiveRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<ClickRecognizer> clickRecognizerPtrNotSame = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.steps: case4: recognizers has ptr, referee is FAIL
     * @tc.expected: step3. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer.OnRejected();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step4. call OnPending function and compare result.
     * @tc.steps: case1: no active
     * @tc.expected: step4. result equals.
     */
    exclusiveRecognizer.activeRecognizer_ = nullptr;
    exclusiveRecognizer.OnPending();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step4. call OnPending function and compare result.
     * @tc.steps: case2: has active
     * @tc.expected: step4. result equals.
     */
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    exclusiveRecognizer.OnPending();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case1: ACCEPT, no active
     * @tc.expected: step5. result equals.
     */
    exclusiveRecognizer.disposal_ = GestureDisposal::ACCEPT;
    exclusiveRecognizer.activeRecognizer_ = nullptr;
    exclusiveRecognizer.OnBlocked();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::SUCCEED_BLOCKED);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case2: ACCEPT, active
     * @tc.expected: step5. result equals.
     */
    exclusiveRecognizer.disposal_ = GestureDisposal::ACCEPT;
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    exclusiveRecognizer.OnBlocked();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::SUCCEED_BLOCKED);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case3: PENDING, no active
     * @tc.expected: step5. result equals.
     */
    exclusiveRecognizer.disposal_ = GestureDisposal::PENDING;
    exclusiveRecognizer.activeRecognizer_ = nullptr;
    exclusiveRecognizer.OnBlocked();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::PENDING_BLOCKED);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case3: PENDING, active
     * @tc.expected: step5. result equals.
     */
    exclusiveRecognizer.disposal_ = GestureDisposal::REJECT;
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    exclusiveRecognizer.OnBlocked();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::PENDING_BLOCKED);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case3: PENDING, active
     * @tc.expected: step5. result equals.
     */
    exclusiveRecognizer.disposal_ = GestureDisposal::PENDING;
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    exclusiveRecognizer.OnBlocked();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::PENDING_BLOCKED);
}

/**
 * @tc.name: ExclusiveRecognizerTest008
 * @tc.desc: Test ExclusiveRecognizer function: HandleEvent OnResetStatus
 * @tc.type: FUNC
 */
HWTEST_F(ExclusiveRecognizerTestNg, ExclusiveRecognizerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);
    bool result = false;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step3. create axisEvent and call HandleEvent function and compare result.
     * @tc.steps: case1: active is nullptr, recognizers is empty
     * @tc.expected: step3. result equals.
     */
    AxisEvent axisEvent;
    axisEvent.action = AxisAction::BEGIN;
    result = exclusiveRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(result, true);
    axisEvent.action = AxisAction::UPDATE;
    result = exclusiveRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(result, true);
    axisEvent.action = AxisAction::END;
    result = exclusiveRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(result, true);
    axisEvent.action = AxisAction::NONE;
    result = exclusiveRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step3. create axisEvent and call HandleEvent function and compare result.
     * @tc.steps: case2: active is ptr
     * @tc.expected: step3. result equals.
     */
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    result = exclusiveRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step3. create axisEvent and call HandleEvent function and compare result.
     * @tc.steps: case3: active is nullptr, recognizers have nullptr
     * @tc.expected: step3. result equals.
     */
    exclusiveRecognizer.activeRecognizer_ = nullptr;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(nullptr);
    result = exclusiveRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step3. create axisEvent and call HandleEvent function and compare result.
     * @tc.steps: case4: active is nullptr, recognizers have ptr
     * @tc.expected: step3. result equals.
     */
    exclusiveRecognizer.activeRecognizer_ = nullptr;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    result = exclusiveRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step4. call OnResetStatus function and compare result.
     * @tc.expected: step4. result equals.
     */
    exclusiveRecognizer.OnResetStatus();
    EXPECT_EQ(exclusiveRecognizer.activeRecognizer_, nullptr);
    axisEvent.action = AxisAction::CANCEL;
    result = exclusiveRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: ExclusiveRecognizerTest009
 * @tc.desc: Test ExclusiveRecognizer function: CleanRecognizerState
 * @tc.type: FUNC
 */
HWTEST_F(ExclusiveRecognizerTestNg, ExclusiveRecognizerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {clickRecognizerPtr};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);

    /**
     * @tc.steps: step3. set child recognizer state and call cleanRecognizerState function and compare result.
     * @tc.steps: case1: touchPoints size is 1, clean success.
     * @tc.expected: step3. clickRecognizer state set ready.
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    exclusiveRecognizer.CleanRecognizerState();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);

    /**
     * @tc.steps: step3. set child recognizer state and call cleanRecognizerState function and compare result.
     * @tc.steps: case2: touchPoints size is 2, clean fail.
     * @tc.expected: step3. clickRecognizer state set ready.
     */
    clickRecognizerPtr->touchPoints_[0] = {};
    clickRecognizerPtr->touchPoints_[1] = {};
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    exclusiveRecognizer.CleanRecognizerState();
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);
}
} // namespace OHOS::Ace::NG