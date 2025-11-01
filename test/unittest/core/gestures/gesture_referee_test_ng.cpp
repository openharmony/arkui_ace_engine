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
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class GestureRefereeTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void GestureRefereeTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void GestureRefereeTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: GestureRefereeTest001
 * @tc.desc: Test GestureReferee Existed function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call Existed function and compare result
     * @tc.steps: case1: input is ptr, have input
     * @tc.steps: expected equal
     */
    auto result = gestureScope.Existed(clickRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call Existed function and compare result
     * @tc.steps: case2: input is nullptr
     * @tc.steps: expected equal
     */
    result = gestureScope.Existed(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call Existed function and compare result
     * @tc.steps: case3: recognizers is empty
     * @tc.steps: expected equal
     */
    gestureScope.recognizers_.clear();
    result = gestureScope.Existed(clickRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: GestureRefereeTest002
 * @tc.desc: Test GestureReferee CheckNeedBlocked function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call Existed function and compare result
     * @tc.steps: case1: member == input
     * @tc.steps: expected equal
     */
    auto result = gestureScope.CheckNeedBlocked(clickRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call Existed function and compare result
     * @tc.steps: case1: member != input, refereeState is PENDING
     * @tc.steps: expected equal
     */
    RefPtr<ClickRecognizer> clickRecognizerPtrNotInsert = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    result = gestureScope.CheckNeedBlocked(clickRecognizerPtrNotInsert);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call Existed function and compare result
     * @tc.steps: case3: recognizers is empty
     * @tc.steps: expected equal
     */
    gestureScope.recognizers_.clear();
    result = gestureScope.CheckNeedBlocked(clickRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: GestureRefereeCheckNeedBlockedTest001
 * @tc.desc: Test GestureReferee CheckNeedBlocked function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeCheckNeedBlockedTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call Existed function and compare result
     * @tc.steps: case1: member == input
     * @tc.steps: expected equal
     */
    auto result = gestureScope.CheckNeedBlocked(clickRecognizerPtr);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step2. call Existed function and compare result
     * @tc.steps: case1: member != input, refereeState is PENDING
     * @tc.steps: expected equal
     */
    RefPtr<ClickRecognizer> clickRecognizerPtrNotInsert = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING_BLOCKED;
    result = gestureScope.CheckNeedBlocked(clickRecognizerPtrNotInsert);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step2. call Existed function and compare result
     * @tc.steps: case3: recognizers is empty
     * @tc.steps: expected equal
     */
    gestureScope.recognizers_.clear();
    result = gestureScope.CheckNeedBlocked(clickRecognizerPtr);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GestureRefereeOnAcceptGestureTest001
 * @tc.desc: Test GestureReferee OnAcceptGesture function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeOnAcceptGestureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call OnAcceptGesture function and compare result
     * @tc.steps: case1: gesture == recognizer
     * @tc.steps: expected equal
     */
    auto onActionStart = [](size_t info) { return; };
    gestureScope.queryStateFunc_ = onActionStart;
    gestureScope.OnAcceptGesture(clickRecognizerPtr);
    EXPECT_EQ(gestureScope.hasGestureAccepted_, true);

    /**
     * @tc.steps: step2. call OnAcceptGesture function and compare result
     * @tc.steps: case2: gesture != recognizer
     * @tc.steps: expected equal
     */
    RefPtr<ClickRecognizer> clickRecognizerPtrNotInsert = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.OnAcceptGesture(clickRecognizerPtrNotInsert);
    EXPECT_EQ(gestureScope.hasGestureAccepted_, true);

    /**
     * @tc.steps: step2. call OnAcceptGesture function and compare result
     * @tc.steps: case3: recognizers is empty
     * @tc.steps: expected equal
     */
    gestureScope.recognizers_.clear();
    gestureScope.OnAcceptGesture(clickRecognizerPtr);
    EXPECT_EQ(gestureScope.hasGestureAccepted_, true);

    /**
     * @tc.steps: step2. call OnAcceptGesture function and compare result
     * @tc.steps: case4: recognizers have nullptr
     * @tc.steps: expected equal
     */
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), nullptr);
    gestureScope.OnAcceptGesture(clickRecognizerPtr);
    EXPECT_EQ(gestureScope.hasGestureAccepted_, true);
}

/**
 * @tc.name: GestureRefereeTest003
 * @tc.desc: Test GestureReferee OnAcceptGesture function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call OnAcceptGesture function and compare result
     * @tc.steps: case1: gesture == recognizer
     * @tc.steps: expected equal
     */
    gestureScope.OnAcceptGesture(clickRecognizerPtr);
    EXPECT_EQ(gestureScope.hasGestureAccepted_, true);

    /**
     * @tc.steps: step2. call OnAcceptGesture function and compare result
     * @tc.steps: case2: gesture != recognizer
     * @tc.steps: expected equal
     */
    RefPtr<ClickRecognizer> clickRecognizerPtrNotInsert = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.OnAcceptGesture(clickRecognizerPtrNotInsert);
    EXPECT_EQ(gestureScope.hasGestureAccepted_, true);

    /**
     * @tc.steps: step2. call OnAcceptGesture function and compare result
     * @tc.steps: case3: recognizers is empty
     * @tc.steps: expected equal
     */
    gestureScope.recognizers_.clear();
    gestureScope.OnAcceptGesture(clickRecognizerPtr);
    EXPECT_EQ(gestureScope.hasGestureAccepted_, true);

    /**
     * @tc.steps: step2. call OnAcceptGesture function and compare result
     * @tc.steps: case4: recognizers have nullptr
     * @tc.steps: expected equal
     */
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), nullptr);
    gestureScope.OnAcceptGesture(clickRecognizerPtr);
    EXPECT_EQ(gestureScope.hasGestureAccepted_, true);
}

/**
 * @tc.name: GestureRefereeTest004
 * @tc.desc: Test GestureReferee OnBlockGesture function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call UnBlockGesture function and compare result
     * @tc.steps: expected equal
     */
    auto result = gestureScope.UnBlockGesture();
    EXPECT_EQ(result, nullptr);

    clickRecognizerPtr->refereeState_ = RefereeState::PENDING_BLOCKED;
    result = gestureScope.UnBlockGesture();
    EXPECT_EQ(result, clickRecognizerPtr);
}

/**
 * @tc.name: GestureRefereeTest005
 * @tc.desc: Test GestureReferee IsPending function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call IsPending function and compare result
     * @tc.steps: expected equal
     */
    auto result = gestureScope.IsPending(0);
    EXPECT_EQ(result, false);

    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    result = gestureScope.IsPending(0);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: GestureRefereeIsPendingTest001
 * @tc.desc: Test GestureReferee IsPending function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeIsPendingTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizerPtr = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), exclusiveRecognizerPtr);
    gestureScope.recognizers_.push_back(nullptr);

    gestureScope.AddMember(clickRecognizerPtr);
    gestureScope.AddMember(exclusiveRecognizerPtr);

    /**
     * @tc.steps: step2. call IsPending function and compare result
     * @tc.steps: expected equal
     */
    auto result = gestureScope.IsPending(0);
    EXPECT_EQ(result, false);

    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    result = gestureScope.IsPending(0);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: GestureRefereeTest006
 * @tc.desc: Test GestureReferee AddGestureToScope function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureReferee.
     */
    GestureReferee gestureReferee;

    /**
     * @tc.steps: step2. call AddGestureToScope function and compare result
     * @tc.steps: case1: cannot find touchId
     * @tc.steps: expected equal
     */
    TouchTestResult touchTestResult;
    gestureReferee.AddGestureToScope(0, touchTestResult);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call AddGestureToScope function and compare result
     * @tc.steps: case2: can find touchId, result is empty
     * @tc.steps: expected equal
     */
    gestureReferee.gestureScopes_.clear();
    gestureReferee.gestureScopes_[0] = AceType::MakeRefPtr<GestureScope>(0);
    gestureReferee.AddGestureToScope(0, touchTestResult);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call AddGestureToScope function and compare result
     * @tc.steps: case3: can find touchId, result have nullptr
     * @tc.steps: expected equal
     */
    touchTestResult.insert(touchTestResult.end(), nullptr);
    gestureReferee.AddGestureToScope(0, touchTestResult);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call AddGestureToScope function and compare result
     * @tc.steps: case4: can find touchId, result have ptr
     * @tc.steps: expected equal
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    touchTestResult.clear();
    touchTestResult.insert(touchTestResult.end(), clickRecognizerPtr);
    gestureReferee.AddGestureToScope(0, touchTestResult);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);
}

/**
 * @tc.name: GestureRefereeTest007
 * @tc.desc: Test GestureReferee CleanGestureScope function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureReferee.
     */
    GestureReferee gestureReferee;

    /**
     * @tc.steps: step2. call CleanGestureScope function and compare result
     * @tc.steps: case1: gestureScope is empty
     * @tc.steps: expected equal
     */
    gestureReferee.CleanGestureScope(0);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call CleanGestureScope function and compare result
     * @tc.steps: case2: gestureScope is not empty, scope is not PENDING
     * @tc.steps: expected equal
     */
    RefPtr<GestureScope> gestureScope = AceType::MakeRefPtr<GestureScope>(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.CleanGestureScope(0);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call CleanGestureScope function and compare result
     * @tc.steps: case3: gestureScope is not empty, scope is PENDING
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    gestureScope->recognizers_.clear();
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.CleanGestureScope(0);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);
}

/**
 * @tc.name: GestureRefereeTest008
 * @tc.desc: Test GestureReferee AddMember function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call AddMember function and compare result
     * @tc.steps: case1: is existed
     * @tc.steps: expected equal
     */
    gestureScope.AddMember(clickRecognizerPtr);
    EXPECT_EQ(gestureScope.recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call AddMember function and compare result
     * @tc.steps: expected equal
     */
    gestureScope.recognizers_.clear();
    gestureScope.AddMember(clickRecognizerPtr);
    EXPECT_EQ(gestureScope.recognizers_.size(), 1);
}

/**
 * @tc.name: GestureRefereeTest009
 * @tc.desc: Test GestureReferee Close function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call Close function and compare result
     * @tc.steps: case1: have ptr
     * @tc.steps: expected equal
     */
    gestureScope.Close();
    EXPECT_EQ(gestureScope.recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call OnAcceptGesture function and compare result
     * @tc.steps: case2: recognizers_ is empty
     * @tc.steps: expected equal
     */
    gestureScope.recognizers_.clear();
    gestureScope.Close();
    EXPECT_EQ(gestureScope.recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call OnAcceptGesture function and compare result
     * @tc.steps: case3: recognizers_ have nullptr
     * @tc.steps: expected equal
     */
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), nullptr);
    gestureScope.Close();
    EXPECT_EQ(gestureScope.recognizers_.size(), 1);
}

/**
 * @tc.name: GestureRefereeTest010
 * @tc.desc: Test GestureReferee Adjudicate function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureReferee gestureReferee;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: disposal is ACCEPT
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    gestureReferee.Adjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case2: disposal is PENDING
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    gestureReferee.Adjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case3: disposal is REJECT
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    gestureReferee.Adjudicate(clickRecognizerPtr, GestureDisposal::REJECT);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case4: disposal is NONE
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    gestureReferee.Adjudicate(clickRecognizerPtr, GestureDisposal::NONE);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);
}

/**
 * @tc.name: GestureRefereeTest011
 * @tc.desc: Test GestureReferee HandleAcceptDisposal function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureReferee gestureReferee;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is SUCCEED
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    gestureReferee.HandleAcceptDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case2: refereeState is PENDING, gestureScopes_ is empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    gestureReferee.HandleAcceptDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case3: refereeState is PENDING, gestureScopes_ is not empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    RefPtr<GestureScope> gestureScope = AceType::MakeRefPtr<GestureScope>(0);
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.HandleAcceptDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case4: refereeState is PENDING, gestureScopes_ is not empty, isDelay
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    gestureScope->isDelay_ = true;
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.HandleAcceptDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case5: refereeState is PENDING, gestureScopes_ is not empty, !isDelay
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    gestureScope->isDelay_ = false;
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.HandleAcceptDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case6: refereeState is FAIL
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    gestureReferee.HandleAcceptDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);
}

/**
 * @tc.name: GestureRefereeHandleRejectDisposalTest001
 * @tc.desc: Test GestureReferee HandleRejectDisposal function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeHandleRejectDisposalTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureReferee gestureReferee;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr2->refereeState_ = RefereeState::PENDING;

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is FAIL
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING_BLOCKED;
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case2: refereeState is PENDING, gestureScopes_ is empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING_BLOCKED;
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case3: refereeState is PENDING, gestureScopes_ is not empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING_BLOCKED;
    RefPtr<GestureScope> gestureScope = AceType::MakeRefPtr<GestureScope>(0);
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureScope->AddMember(clickRecognizerPtr);
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr2);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case4: refereeState is PENDING_BLOCKED, gestureScopes_ is not empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING_BLOCKED;
    gestureScope->recognizers_.clear();
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureScope->AddMember(clickRecognizerPtr);
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr2);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case5: refereeState is SUCCEED_BLOCKED, gestureScopes_ is not empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING_BLOCKED;
    gestureScope->recognizers_.clear();
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureScope->AddMember(clickRecognizerPtr);
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr2);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case6: refereeState is PENDING, gestureScopes_ is not empty, isDelay
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING_BLOCKED;
    gestureScope->recognizers_.clear();
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureScope->isDelay_ = true;
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureScope->AddMember(clickRecognizerPtr);
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr2);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case7: refereeState is PENDING, gestureScopes_ is not empty, isDelay
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    gestureScope->recognizers_.clear();
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureScope->isDelay_ = false;
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureScope->AddMember(clickRecognizerPtr);
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr2);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);
}

/**
 * @tc.name: GestureRefereeHandleRejectDisposalTest002
 * @tc.desc: Test GestureReferee HandleRejectDisposal function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeHandleRejectDisposalTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureReferee gestureReferee;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr2->refereeState_ = RefereeState::PENDING;

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is FAIL
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case2: refereeState is PENDING, gestureScopes_ is empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case3: refereeState is PENDING, gestureScopes_ is not empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    RefPtr<GestureScope> gestureScope = AceType::MakeRefPtr<GestureScope>(0);
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureScope->AddMember(clickRecognizerPtr);
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr2);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case4: refereeState is PENDING_BLOCKED, gestureScopes_ is not empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    gestureScope->recognizers_.clear();
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureScope->AddMember(clickRecognizerPtr);
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr2);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case5: refereeState is SUCCEED_BLOCKED, gestureScopes_ is not empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    gestureScope->recognizers_.clear();
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureScope->AddMember(clickRecognizerPtr);
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr2);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case6: refereeState is PENDING, gestureScopes_ is not empty, isDelay
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    gestureScope->recognizers_.clear();
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureScope->isDelay_ = true;
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureScope->AddMember(clickRecognizerPtr);
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr2);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case7: refereeState is PENDING, gestureScopes_ is not empty, isDelay
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    gestureScope->recognizers_.clear();
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureScope->isDelay_ = false;
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureScope->AddMember(clickRecognizerPtr);
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr2);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);
}

/**
 * @tc.name: GestureRefereeHandlePendingDisposalTest012
 * @tc.desc: Test GestureReferee HandlePendingDisposal function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeHandlePendingDisposalTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureReferee gestureReferee;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is PENDING
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    gestureReferee.HandlePendingDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case2: refereeState is SUCCEED, gestureScopes_ is empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    gestureReferee.HandlePendingDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case3: refereeState is SUCCEED, gestureScopes_ is not empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    RefPtr<GestureScope> gestureScope = AceType::MakeRefPtr<GestureScope>(0);
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.HandlePendingDisposal(clickRecognizerPtr2);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);
}

/**
 * @tc.name: GestureRefereeTestHandleAcceptDisposal005
 * @tc.desc: Test GestureReferee HandleAcceptDisposal function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeTestHandleAcceptDisposal005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureReferee gestureReferee;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is PENDING
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    gestureReferee.HandleAcceptDisposal(clickRecognizerPtr2);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case2: refereeState is SUCCEED, gestureScopes_ is empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    gestureReferee.HandleAcceptDisposal(clickRecognizerPtr2);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case3: refereeState is SUCCEED, gestureScopes_ is not empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    RefPtr<GestureScope> gestureScope = AceType::MakeRefPtr<GestureScope>(0);
    gestureScope->recognizers_.clear();
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureScope->AddMember(clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.HandleAcceptDisposal(clickRecognizerPtr2);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);
}

/**
 * @tc.name: GestureRefereeHandleAcceptDisposalTest006
 * @tc.desc: Test GestureReferee HandleAcceptDisposal function
 */
HWTEST_F(GestureRefereeTestNg, GestureRefereeHandleAcceptDisposalTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureReferee gestureReferee;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is PENDING
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    gestureReferee.HandleAcceptDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case2: refereeState is SUCCEED, gestureScopes_ is empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    gestureReferee.HandleAcceptDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case3: refereeState is SUCCEED, gestureScopes_ is not empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    RefPtr<GestureScope> gestureScope = AceType::MakeRefPtr<GestureScope>(0);
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.HandleAcceptDisposal(clickRecognizerPtr2);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);
}
} // namespace OHOS::Ace::NG