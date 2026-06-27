/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/manager/gesture/active_recognizer_manager.h"
#undef private
#undef protected

#include "test/mock/frameworks/base/thread/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TOUCH_ID_0 = 0;
constexpr int32_t TOUCH_ID_1 = 1;
constexpr int32_t TOUCH_ID_DEFAULT = -1;

class TestGestureRecognizer : public NGGestureRecognizer {
    DECLARE_ACE_TYPE(TestGestureRecognizer, NGGestureRecognizer);

public:
    TestGestureRecognizer() = default;
    ~TestGestureRecognizer() override = default;

    MOCK_METHOD(void, ResetStatusOnFinish, (bool isBlocked), (override));
    MOCK_METHOD(void, BatchAdjudicate, (const RefPtr<NGGestureRecognizer>&, GestureDisposal), ());
    MOCK_METHOD(void, OnBeginGestureReferee, (int32_t, int32_t, bool), ());
    MOCK_METHOD(void, HandleTouchDownEvent, (const TouchEvent&), ());
    MOCK_METHOD(void, HandleTouchUpEvent, (const TouchEvent&), ());
    MOCK_METHOD(void, HandleTouchMoveEvent, (const TouchEvent&), ());
    MOCK_METHOD(void, HandleTouchCancelEvent, (const TouchEvent&), ());
    MOCK_METHOD(void, HandleTouchDownEvent, (const AxisEvent&), ());
    MOCK_METHOD(void, HandleTouchUpEvent, (const AxisEvent&), ());
    MOCK_METHOD(void, HandleTouchMoveEvent, (const AxisEvent&), ());
    MOCK_METHOD(void, HandleTouchCancelEvent, (const AxisEvent&), ());
    MOCK_METHOD(void, OnResetStatus, (), ());
    MOCK_METHOD(void, OnSucceedCancel, (), ());
    MOCK_METHOD(void, OnAccepted, (), ());
    MOCK_METHOD(void, OnRejected, (), ());
    MOCK_METHOD(void, OnPending, (), ());
    MOCK_METHOD(void, OnBlocked, (), ());
    MOCK_METHOD(bool, CheckTouchId, (int32_t), ());
    MOCK_METHOD((std::map<int32_t, TouchEvent>), GetTouchPoints, (), ());
    MOCK_METHOD(void, CheckCurrentFingers, (), (const));

    MOCK_METHOD(bool, HandleEvent, (const TouchEvent&), (override));

    void SetTestRefereeState(RefereeState state)
    {
        refereeState_ = state;
    }

    void SetTestCallbackState(CurrentCallbackState state)
    {
        currentCallbackState_ = state;
    }
};
} // namespace

class ActiveRecognizerManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrent();
        MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
        MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }

    void SetUp() override
    {
        manager_ = AceType::MakeRefPtr<ActiveRecognizerManager>();
    }

    void TearDown() override
    {
        manager_ = nullptr;
    }

    RefPtr<ActiveRecognizerManager> manager_;
};

/**
 * @tc.name: RegisterRecognizer_NullRecognizer
 * @tc.desc: Test RegisterRecognizer with null recognizer — early return branch
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, RegisterRecognizer_NullRecognizer, TestSize.Level1)
{
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
    manager_->RegisterRecognizer(nullptr, TOUCH_ID_0);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
    EXPECT_FALSE(manager_->HasActiveRecognizers());
}

/**
 * @tc.name: RegisterRecognizer_NewRecognizer
 * @tc.desc: Test RegisterRecognizer with valid recognizer — insert new entry
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, RegisterRecognizer_NewRecognizer, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 1);
    EXPECT_TRUE(manager_->HasActiveRecognizers());
    EXPECT_TRUE(manager_->activeTouchIds_.count(TOUCH_ID_0) > 0);
}

/**
 * @tc.name: RegisterRecognizer_DuplicateRecognizer
 * @tc.desc: Test RegisterRecognizer with same recognizer twice — duplicate branch, should not insert again
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, RegisterRecognizer_DuplicateRecognizer, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 1);
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_1);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 1);
    EXPECT_TRUE(manager_->activeTouchIds_.count(TOUCH_ID_0) > 0);
}

/**
 * @tc.name: RegisterRecognizer_MultipleRecognizers
 * @tc.desc: Test RegisterRecognizer with two different recognizers
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, RegisterRecognizer_MultipleRecognizers, TestSize.Level1)
{
    auto recognizer1 = AceType::MakeRefPtr<TestGestureRecognizer>();
    auto recognizer2 = AceType::MakeRefPtr<TestGestureRecognizer>();
    manager_->RegisterRecognizer(recognizer1, TOUCH_ID_0);
    manager_->RegisterRecognizer(recognizer2, TOUCH_ID_1);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 2);
    EXPECT_TRUE(manager_->activeTouchIds_.count(TOUCH_ID_0) > 0);
    EXPECT_TRUE(manager_->activeTouchIds_.count(TOUCH_ID_1) > 0);
}

/**
 * @tc.name: RegisterRecognizer_RecognizerInfoFields
 * @tc.desc: Test RegisterRecognizer sets RecognizerInfo fields correctly (touchId, recognizerType, lastUpdateTime)
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, RegisterRecognizer_RecognizerInfoFields, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_1);
    auto weakKey = WeakPtr<NGGestureRecognizer>(recognizer);
    auto iter = manager_->activeRecognizers_.find(weakKey);
    ASSERT_TRUE(iter != manager_->activeRecognizers_.end());
    EXPECT_EQ(iter->second.touchId, TOUCH_ID_1);
    EXPECT_EQ(iter->second.recognizerType, AceType::TypeName(recognizer));
    EXPECT_TRUE(iter->second.lastUpdateTime.time_since_epoch().count() > 0);
}

/**
 * @tc.name: UpdateRecognizerState_NullRecognizer
 * @tc.desc: Test UpdateRecognizerState with null recognizer — early return branch
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, UpdateRecognizerState_NullRecognizer, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);
    auto oldCount = manager_->GetActiveRecognizerCount();
    manager_->UpdateRecognizerState(nullptr, RefereeState::SUCCEED);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), oldCount);
}

/**
 * @tc.name: UpdateRecognizerState_NotFound
 * @tc.desc: Test UpdateRecognizerState with recognizer not in map — early return branch
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, UpdateRecognizerState_NotFound, TestSize.Level1)
{
    auto recognizer1 = AceType::MakeRefPtr<TestGestureRecognizer>();
    auto recognizer2 = AceType::MakeRefPtr<TestGestureRecognizer>();
    manager_->RegisterRecognizer(recognizer1, TOUCH_ID_0);

    auto weakKey1 = WeakPtr<NGGestureRecognizer>(recognizer1);
    auto iter1 = manager_->activeRecognizers_.find(weakKey1);
    ASSERT_TRUE(iter1 != manager_->activeRecognizers_.end());
    auto oldTime = iter1->second.lastUpdateTime;

    manager_->UpdateRecognizerState(recognizer2, RefereeState::SUCCEED);
    iter1 = manager_->activeRecognizers_.find(weakKey1);
    EXPECT_EQ(iter1->second.lastUpdateTime, oldTime);
}

/**
 * @tc.name: UpdateRecognizerState_Found
 * @tc.desc: Test UpdateRecognizerState with recognizer in map — updates lastUpdateTime
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, UpdateRecognizerState_Found, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);

    auto weakKey = WeakPtr<NGGestureRecognizer>(recognizer);
    auto iter = manager_->activeRecognizers_.find(weakKey);
    ASSERT_TRUE(iter != manager_->activeRecognizers_.end());
    auto oldTime = iter->second.lastUpdateTime;

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    manager_->UpdateRecognizerState(recognizer, RefereeState::SUCCEED);

    iter = manager_->activeRecognizers_.find(weakKey);
    EXPECT_TRUE(iter->second.lastUpdateTime > oldTime);
}

/**
 * @tc.name: CheckAndCleanBeforeNewTouch_NoPendingCleansAll
 * @tc.desc: Test CheckAndCleanBeforeNewTouch when no recognizers are pending — should clean all
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, CheckAndCleanBeforeNewTouch_NoPendingCleansAll, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::SUCCEED);
    recognizer->SetTestCallbackState(CurrentCallbackState::END);
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 1);

    manager_->CheckAndCleanBeforeNewTouch(TOUCH_ID_1);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
    EXPECT_TRUE(manager_->activeTouchIds_.empty());
}

/**
 * @tc.name: CheckAndCleanBeforeNewTouch_UnclosedStartSendsCancel
 * @tc.desc: Test CheckAndCleanBeforeNewTouch with START callback state — should send cancel before clean
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, CheckAndCleanBeforeNewTouch_UnclosedStartSendsCancel, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::SUCCEED);
    recognizer->SetTestCallbackState(CurrentCallbackState::START);
    EXPECT_CALL(*recognizer, HandleEvent(_)).Times(AtLeast(1));
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);

    manager_->CheckAndCleanBeforeNewTouch(TOUCH_ID_1);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
}

/**
 * @tc.name: CheckAndCleanBeforeNewTouch_UnclosedUpdateSendsCancel
 * @tc.desc: Test CheckAndCleanBeforeNewTouch with UPDATE callback state — should send cancel
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, CheckAndCleanBeforeNewTouch_UnclosedUpdateSendsCancel, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::SUCCEED);
    recognizer->SetTestCallbackState(CurrentCallbackState::UPDATE);
    EXPECT_CALL(*recognizer, HandleEvent(_)).Times(AtLeast(1));
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);

    manager_->CheckAndCleanBeforeNewTouch(TOUCH_ID_1);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
}

/**
 * @tc.name: CheckAndCleanBeforeNewTouch_ClosedCallbackNoCancel
 * @tc.desc: Test CheckAndCleanBeforeNewTouch with END/CANCEL callback state — no cancel event sent
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, CheckAndCleanBeforeNewTouch_ClosedCallbackNoCancel, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::SUCCEED);
    recognizer->SetTestCallbackState(CurrentCallbackState::END);
    EXPECT_CALL(*recognizer, HandleEvent(_)).Times(0);
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);

    manager_->CheckAndCleanBeforeNewTouch(TOUCH_ID_1);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
}

/**
 * @tc.name: CheckAndCleanBeforeNewTouch_PendingTimeoutNotClean
 * @tc.desc: Test CheckAndCleanBeforeNewTouch when recognizer is PENDING and timeout not expired — should NOT clean
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, CheckAndCleanBeforeNewTouch_PendingTimeoutNotClean, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::PENDING);
    recognizer->SetTestCallbackState(CurrentCallbackState::START);
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);

    manager_->CheckAndCleanBeforeNewTouch(TOUCH_ID_1);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 1);
}

/**
 * @tc.name: CheckAndCleanBeforeNewTouch_PendingBlockedTimeoutNotClean
 * @tc.desc: Test CheckAndCleanBeforeNewTouch when recognizer is PENDING_BLOCKED
 *           and timeout not expired — should NOT clean
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, CheckAndCleanBeforeNewTouch_PendingBlockedTimeoutNotClean, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::PENDING_BLOCKED);
    recognizer->SetTestCallbackState(CurrentCallbackState::UPDATE);
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);

    manager_->CheckAndCleanBeforeNewTouch(TOUCH_ID_1);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 1);
}

/**
 * @tc.name: CheckAndCleanBeforeNewTouch_PendingTimeoutExpiredCleansAll
 * @tc.desc: Test CheckAndCleanBeforeNewTouch when recognizer is PENDING but timeout expired — should clean
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, CheckAndCleanBeforeNewTouch_PendingTimeoutExpiredCleansAll, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::PENDING);
    recognizer->SetTestCallbackState(CurrentCallbackState::END);
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);

    auto weakKey = WeakPtr<NGGestureRecognizer>(recognizer);
    auto iter = manager_->activeRecognizers_.find(weakKey);
    ASSERT_TRUE(iter != manager_->activeRecognizers_.end());
    iter->second.lastUpdateTime = std::chrono::high_resolution_clock::now() - std::chrono::milliseconds(500);

    EXPECT_CALL(*recognizer, HandleEvent(_)).Times(0);
    manager_->CheckAndCleanBeforeNewTouch(TOUCH_ID_1);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
}

/**
 * @tc.name: CheckAndCleanBeforeNewTouch_MixedPendingAndNonPending
 * @tc.desc: Test with one pending (not expired) and one non-pending — pending prevents clean
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, CheckAndCleanBeforeNewTouch_MixedPendingAndNonPending, TestSize.Level1)
{
    auto recognizer1 = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer1->SetTestRefereeState(RefereeState::PENDING);
    recognizer1->SetTestCallbackState(CurrentCallbackState::READY);
    manager_->RegisterRecognizer(recognizer1, TOUCH_ID_0);

    auto recognizer2 = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer2->SetTestRefereeState(RefereeState::SUCCEED);
    recognizer2->SetTestCallbackState(CurrentCallbackState::END);
    manager_->RegisterRecognizer(recognizer2, TOUCH_ID_1);

    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 2);
    manager_->CheckAndCleanBeforeNewTouch(2);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 2);
}

/**
 * @tc.name: CheckPendingTimeout_NullRecognizer
 * @tc.desc: Test CheckPendingTimeout with null recognizer — returns false
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, CheckPendingTimeout_NullRecognizer, TestSize.Level1)
{
    ActiveRecognizerManager::RecognizerInfo info;
    auto result = manager_->CheckPendingTimeout(nullptr, info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckPendingTimeout_NonPendingState
 * @tc.desc: Test CheckPendingTimeout with READY state — returns false (not PENDING/PENDING_BLOCKED)
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, CheckPendingTimeout_NonPendingState, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::READY);
    ActiveRecognizerManager::RecognizerInfo info(WeakPtr<NGGestureRecognizer>(recognizer), TOUCH_ID_0);
    info.lastUpdateTime = std::chrono::high_resolution_clock::now();
    auto result = manager_->CheckPendingTimeout(recognizer, info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckPendingTimeout_PendingStateWithinTimeout
 * @tc.desc: Test CheckPendingTimeout with PENDING state and duration < timeout — returns true
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, CheckPendingTimeout_PendingStateWithinTimeout, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::PENDING);
    ActiveRecognizerManager::RecognizerInfo info(WeakPtr<NGGestureRecognizer>(recognizer), TOUCH_ID_0);
    info.lastUpdateTime = std::chrono::high_resolution_clock::now();
    auto result = manager_->CheckPendingTimeout(recognizer, info);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckPendingTimeout_PendingStateTimeoutExpired
 * @tc.desc: Test CheckPendingTimeout with PENDING state and duration >= timeout — returns false
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, CheckPendingTimeout_PendingStateTimeoutExpired, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::PENDING);
    ActiveRecognizerManager::RecognizerInfo info(WeakPtr<NGGestureRecognizer>(recognizer), TOUCH_ID_0);
    info.lastUpdateTime = std::chrono::high_resolution_clock::now() - std::chrono::milliseconds(400);
    auto result = manager_->CheckPendingTimeout(recognizer, info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckPendingTimeout_PendingBlockedWithinTimeout
 * @tc.desc: Test CheckPendingTimeout with PENDING_BLOCKED state within timeout — returns true
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, CheckPendingTimeout_PendingBlockedWithinTimeout, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::PENDING_BLOCKED);
    ActiveRecognizerManager::RecognizerInfo info(WeakPtr<NGGestureRecognizer>(recognizer), TOUCH_ID_0);
    info.lastUpdateTime = std::chrono::high_resolution_clock::now();
    auto result = manager_->CheckPendingTimeout(recognizer, info);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckPendingTimeout_AllNonPendingStatesReturnFalse
 * @tc.desc: Test CheckPendingTimeout for all non-pending states (READY, DETECTING, SUCCEED_BLOCKED, SUCCEED, FAIL)
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, CheckPendingTimeout_AllNonPendingStatesReturnFalse, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    ActiveRecognizerManager::RecognizerInfo info(WeakPtr<NGGestureRecognizer>(recognizer), TOUCH_ID_0);
    info.lastUpdateTime = std::chrono::high_resolution_clock::now();

    RefereeState nonPendingStates[] = {
        RefereeState::READY, RefereeState::DETECTING,
        RefereeState::SUCCEED_BLOCKED, RefereeState::SUCCEED, RefereeState::FAIL
    };
    for (auto state : nonPendingStates) {
        recognizer->SetTestRefereeState(state);
        EXPECT_FALSE(manager_->CheckPendingTimeout(recognizer, info));
    }
}

/**
 * @tc.name: SendCancelToRecognizer_ValidRecognizer
 * @tc.desc: Test SendCancelToRecognizer with valid recognizer — calls HandleEvent with CANCEL
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, SendCancelToRecognizer_ValidRecognizer, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    EXPECT_CALL(*recognizer, HandleEvent(_)).Times(1);
    manager_->SendCancelToRecognizer(recognizer);
}

/**
 * @tc.name: RemoveRecognizer_NullRecognizer
 * @tc.desc: Test RemoveRecognizer with null — early return
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, RemoveRecognizer_NullRecognizer, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 1);
    manager_->RemoveRecognizer(nullptr);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 1);
}

/**
 * @tc.name: RemoveRecognizer_NotFound
 * @tc.desc: Test RemoveRecognizer with recognizer not in map — no change
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, RemoveRecognizer_NotFound, TestSize.Level1)
{
    auto recognizer1 = AceType::MakeRefPtr<TestGestureRecognizer>();
    auto recognizer2 = AceType::MakeRefPtr<TestGestureRecognizer>();
    manager_->RegisterRecognizer(recognizer1, TOUCH_ID_0);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 1);
    EXPECT_TRUE(manager_->activeTouchIds_.count(TOUCH_ID_0) > 0);

    manager_->RemoveRecognizer(recognizer2);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 1);
    EXPECT_TRUE(manager_->activeTouchIds_.count(TOUCH_ID_0) > 0);
}

/**
 * @tc.name: RemoveRecognizer_FoundWithValidTouchId
 * @tc.desc: Test RemoveRecognizer found in map with touchId != -1 — removes from both maps
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, RemoveRecognizer_FoundWithValidTouchId, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 1);
    EXPECT_TRUE(manager_->activeTouchIds_.count(TOUCH_ID_0) > 0);

    manager_->RemoveRecognizer(recognizer);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
    EXPECT_TRUE(manager_->activeTouchIds_.count(TOUCH_ID_0) == 0);
}

/**
 * @tc.name: RemoveRecognizer_FoundWithDefaultTouchId
 * @tc.desc: Test RemoveRecognizer found in map with touchId == -1 — does NOT erase from activeTouchIds_
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, RemoveRecognizer_FoundWithDefaultTouchId, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_DEFAULT);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 1);

    manager_->RemoveRecognizer(recognizer);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
    EXPECT_FALSE(manager_->activeTouchIds_.empty());
}

/**
 * @tc.name: RemoveRecognizer_MultipleThenRemoveOne
 * @tc.desc: Test RemoveRecognizer removes only the specified recognizer
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, RemoveRecognizer_MultipleThenRemoveOne, TestSize.Level1)
{
    auto recognizer1 = AceType::MakeRefPtr<TestGestureRecognizer>();
    auto recognizer2 = AceType::MakeRefPtr<TestGestureRecognizer>();
    manager_->RegisterRecognizer(recognizer1, TOUCH_ID_0);
    manager_->RegisterRecognizer(recognizer2, TOUCH_ID_1);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 2);

    manager_->RemoveRecognizer(recognizer1);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 1);
    EXPECT_TRUE(manager_->activeTouchIds_.count(TOUCH_ID_0) == 0);
    EXPECT_TRUE(manager_->activeTouchIds_.count(TOUCH_ID_1) > 0);
}

/**
 * @tc.name: HasActiveRecognizers_Empty
 * @tc.desc: Test HasActiveRecognizers when empty — returns false
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, HasActiveRecognizers_Empty, TestSize.Level1)
{
    EXPECT_FALSE(manager_->HasActiveRecognizers());
}

/**
 * @tc.name: HasActiveRecognizers_NonEmpty
 * @tc.desc: Test HasActiveRecognizers when non-empty — returns true
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, HasActiveRecognizers_NonEmpty, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);
    EXPECT_TRUE(manager_->HasActiveRecognizers());
}

/**
 * @tc.name: GetActiveRecognizerCount_EmptyAndAfterRegister
 * @tc.desc: Test GetActiveRecognizerCount returns correct count
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, GetActiveRecognizerCount_EmptyAndAfterRegister, TestSize.Level1)
{
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
    auto recognizer1 = AceType::MakeRefPtr<TestGestureRecognizer>();
    auto recognizer2 = AceType::MakeRefPtr<TestGestureRecognizer>();
    manager_->RegisterRecognizer(recognizer1, TOUCH_ID_0);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 1);
    manager_->RegisterRecognizer(recognizer2, TOUCH_ID_1);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 2);
}

/**
 * @tc.name: ClearAllRecognizers_WithActiveRecognizers
 * @tc.desc: Test ClearAllRecognizers with recognizers not finished — calls ForceCleanRecognizer on each
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, ClearAllRecognizers_WithActiveRecognizers, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::SUCCEED);
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 1);

    manager_->ClearAllRecognizers();
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
    EXPECT_TRUE(manager_->activeTouchIds_.empty());
}

/**
 * @tc.name: ClearAllRecognizers_WithFinishedRecognizer
 * @tc.desc: Test ClearAllRecognizers with finished recognizer (SUCCEED state) — ForceCleanRecognizer not called
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, ClearAllRecognizers_WithFinishedRecognizer, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::SUCCEED);
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);

    auto weakKey = WeakPtr<NGGestureRecognizer>(recognizer);
    auto iter = manager_->activeRecognizers_.find(weakKey);
    ASSERT_TRUE(iter != manager_->activeRecognizers_.end());

    manager_->ClearAllRecognizers();
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
}

/**
 * @tc.name: ClearAllRecognizers_WithNotFinishedRecognizer
 * @tc.desc: Test ClearAllRecognizers with not-finished recognizer (PENDING state) — ForceCleanRecognizer called
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, ClearAllRecognizers_WithNotFinishedRecognizer, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::PENDING);
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);

    manager_->ClearAllRecognizers();
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
}

/**
 * @tc.name: ClearAllRecognizers_FailStateIsFinished
 * @tc.desc: Test ClearAllRecognizers with FAIL state — IsRefereeFinished returns true, ForceCleanRecognizer not called
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, ClearAllRecognizers_FailStateIsFinished, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::FAIL);
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);

    manager_->ClearAllRecognizers();
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
}

/**
 * @tc.name: ClearAllRecognizers_SucceedBlockedIsFinished
 * @tc.desc: Test ClearAllRecognizers with SUCCEED_BLOCKED state — IsRefereeFinished returns true
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, ClearAllRecognizers_SucceedBlockedIsFinished, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::SUCCEED_BLOCKED);
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);

    manager_->ClearAllRecognizers();
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
}

/**
 * @tc.name: ClearAllRecognizers_Empty
 * @tc.desc: Test ClearAllRecognizers when no recognizers — no crash
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, ClearAllRecognizers_Empty, TestSize.Level1)
{
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
    manager_->ClearAllRecognizers();
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
    EXPECT_TRUE(manager_->activeTouchIds_.empty());
}

/**
 * @tc.name: DumpRecognizerStates_NullWeakPtr
 * @tc.desc: Test DumpRecognizerStates with expired weak ptr — skips null recognizers
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, DumpRecognizerStates_NullWeakPtr, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::READY);
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);

    auto weakKey = WeakPtr<NGGestureRecognizer>(recognizer);
    auto iter = manager_->activeRecognizers_.find(weakKey);
    ASSERT_TRUE(iter != manager_->activeRecognizers_.end());

    recognizer = nullptr;
    manager_->DumpRecognizerStates();
}

/**
 * @tc.name: RecognizerInfo_DefaultConstructor
 * @tc.desc: Test RecognizerInfo default constructor — touchId is -1, recognizerType empty
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, RecognizerInfo_DefaultConstructor, TestSize.Level1)
{
    ActiveRecognizerManager::RecognizerInfo info;
    EXPECT_EQ(info.touchId, -1);
    EXPECT_TRUE(info.recognizerType.empty());
    EXPECT_EQ(info.recognizer.Upgrade(), nullptr);
}

/**
 * @tc.name: RecognizerInfo_ExplicitConstructor
 * @tc.desc: Test RecognizerInfo explicit constructor — sets recognizer and touchId, populates recognizerType
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, RecognizerInfo_ExplicitConstructor, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    auto weakPtr = WeakPtr<NGGestureRecognizer>(recognizer);
    ActiveRecognizerManager::RecognizerInfo info(weakPtr, TOUCH_ID_1);
    EXPECT_EQ(info.touchId, TOUCH_ID_1);
    EXPECT_EQ(info.recognizerType, AceType::TypeName(recognizer));
}

/**
 * @tc.name: RecognizerInfo_ExplicitConstructorNullWeak
 * @tc.desc: Test RecognizerInfo explicit constructor with expired weak ptr — recognizerType empty
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, RecognizerInfo_ExplicitConstructorNullWeak, TestSize.Level1)
{
    WeakPtr<NGGestureRecognizer> nullWeak;
    ActiveRecognizerManager::RecognizerInfo info(nullWeak, TOUCH_ID_0);
    EXPECT_EQ(info.touchId, TOUCH_ID_0);
    EXPECT_TRUE(info.recognizerType.empty());
}

/**
 * @tc.name: CheckAndCleanBeforeNewTouch_NullWeakPtrSkips
 * @tc.desc: Test CheckAndCleanBeforeNewTouch with expired weak ptr in map — skips null Upgrade()
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, CheckAndCleanBeforeNewTouch_NullWeakPtrSkips, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::DETECTING);
    recognizer->SetTestCallbackState(CurrentCallbackState::END);
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);

    auto weakKey = WeakPtr<NGGestureRecognizer>(recognizer);
    auto iter = manager_->activeRecognizers_.find(weakKey);
    ASSERT_TRUE(iter != manager_->activeRecognizers_.end());

    recognizer = nullptr;

    manager_->CheckAndCleanBeforeNewTouch(TOUCH_ID_1);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
}

/**
 * @tc.name: CheckAndCleanBeforeNewTouch_CancelCallbackNoCancel
 * @tc.desc: Test CheckAndCleanBeforeNewTouch with CANCEL callback state — not hasUnclosedStart, no cancel sent
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, CheckAndCleanBeforeNewTouch_CancelCallbackNoCancel, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::SUCCEED);
    recognizer->SetTestCallbackState(CurrentCallbackState::CANCEL);
    EXPECT_CALL(*recognizer, HandleEvent(_)).Times(0);
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);

    manager_->CheckAndCleanBeforeNewTouch(TOUCH_ID_1);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
}

/**
 * @tc.name: CheckAndCleanBeforeNewTouch_ReadyCallbackNoCancel
 * @tc.desc: Test CheckAndCleanBeforeNewTouch with READY callback state — not hasUnclosedStart, no cancel sent
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, CheckAndCleanBeforeNewTouch_ReadyCallbackNoCancel, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::SUCCEED);
    recognizer->SetTestCallbackState(CurrentCallbackState::READY);
    EXPECT_CALL(*recognizer, HandleEvent(_)).Times(0);
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);

    manager_->CheckAndCleanBeforeNewTouch(TOUCH_ID_1);
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
}

/**
 * @tc.name: CheckPendingTimeout_ExactBoundary
 * @tc.desc: Test CheckPendingTimeout with duration exactly == 300ms (DEFAULT_PENDING_TIMEOUT_MS) — returns false
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, CheckPendingTimeout_ExactBoundary, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::PENDING);
    ActiveRecognizerManager::RecognizerInfo info(WeakPtr<NGGestureRecognizer>(recognizer), TOUCH_ID_0);
    info.lastUpdateTime = std::chrono::high_resolution_clock::now() - std::chrono::milliseconds(300);
    auto result = manager_->CheckPendingTimeout(recognizer, info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ClearAllRecognizers_NullWeakPtrSkips
 * @tc.desc: Test ClearAllRecognizers with expired weak ptr — skips null Upgrade(), no ForceCleanRecognizer call
 * @tc.type: FUNC
 */
HWTEST_F(ActiveRecognizerManagerTestNg, ClearAllRecognizers_NullWeakPtrSkips, TestSize.Level1)
{
    auto recognizer = AceType::MakeRefPtr<TestGestureRecognizer>();
    recognizer->SetTestRefereeState(RefereeState::PENDING);
    manager_->RegisterRecognizer(recognizer, TOUCH_ID_0);

    auto weakKey = WeakPtr<NGGestureRecognizer>(recognizer);
    auto iter = manager_->activeRecognizers_.find(weakKey);
    ASSERT_TRUE(iter != manager_->activeRecognizers_.end());

    recognizer = nullptr;

    manager_->ClearAllRecognizers();
    EXPECT_EQ(manager_->GetActiveRecognizerCount(), 0);
    EXPECT_TRUE(manager_->activeTouchIds_.empty());
}
} // namespace OHOS::Ace::NG
