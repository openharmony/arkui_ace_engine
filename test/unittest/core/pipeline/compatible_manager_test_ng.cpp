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

#include <gtest/gtest.h>

#include <chrono>
#include <cmath>
#include <optional>

#define private public
#define protected public
#include "core/pipeline_ng/compatible_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
// Forward-declare free functions (defined in compatible_manager.cpp, not declared in header).
std::chrono::milliseconds CalculateDurationTime(const TimeStamp& begin, const TimeStamp& end);
bool IsTimeout(const CompatibleManager& manager);
bool IsReachEnd(float remain, float threshold);
float GetNextStep(float remainingDistance, float endThreshold, const std::chrono::milliseconds& durationTime);

namespace {
constexpr float TEST_Y_DOWN = 100.0f;
constexpr float TEST_Y_MOVE = 200.0f;
constexpr float TEST_Y_LARGE = 500.0f;
constexpr float TEST_THRESHOLD = 0.1f;
} // namespace

class CompatibleManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}

    TouchEvent MakeEvent(TouchType type, float y = 0.0f)
    {
        TouchEvent event;
        event.type = type;
        event.y = y;
        event.SetTime(std::chrono::high_resolution_clock::now());
        return event;
    }

    TouchEvent MakeEventWithOffset(TouchType type, float y, int64_t offsetMs)
    {
        TouchEvent event;
        event.type = type;
        event.y = y;
        event.SetTime(std::chrono::high_resolution_clock::now() - std::chrono::milliseconds(offsetMs));
        return event;
    }

    void GoToReadyState(CompatibleManager& mgr)
    {
        mgr.NotifyNewEvent(MakeEvent(TouchType::DOWN, TEST_Y_DOWN));
    }

    void GoToOngoingState(CompatibleManager& mgr, float downY = TEST_Y_DOWN, float moveY = TEST_Y_MOVE)
    {
        mgr.NotifyNewEvent(MakeEvent(TouchType::DOWN, downY));
        mgr.NotifyNewEvent(MakeEvent(TouchType::MOVE, moveY));
    }

    void GoToEndState(CompatibleManager& mgr)
    {
        // downY == moveY keeps remainingDistance_ at 0, so IsReachEnd triggers EndState.
        GoToOngoingState(mgr, TEST_Y_DOWN, TEST_Y_DOWN);
        mgr.EventGenerate();
    }
};

// ===========================================================================
// Group A: CalculateDurationTime
// ===========================================================================

/**
 * @tc.name: CalculateDurationTimeNegative001
 * @tc.desc: Returns zero when end is before begin (negative duration).
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, CalculateDurationTimeNegative001, TestSize.Level1)
{
    auto begin = std::chrono::high_resolution_clock::now();
    auto end = begin - std::chrono::milliseconds(100);
    auto result = CalculateDurationTime(begin, end);
    EXPECT_EQ(result, std::chrono::milliseconds::zero());
}

/**
 * @tc.name: CalculateDurationTimePositive001
 * @tc.desc: Returns duration when end is after begin.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, CalculateDurationTimePositive001, TestSize.Level1)
{
    auto begin = std::chrono::high_resolution_clock::now();
    auto end = begin + std::chrono::milliseconds(100);
    auto result = CalculateDurationTime(begin, end);
    EXPECT_GE(result.count(), 99); // allow minor clock skew
    EXPECT_LE(result.count(), 101);
}

// ===========================================================================
// Group B: IsTimeout
// ===========================================================================

/**
 * @tc.name: IsTimeoutNoRawDown001
 * @tc.desc: Returns false when rawDownEvent is null.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, IsTimeoutNoRawDown001, TestSize.Level1)
{
    CompatibleManager mgr;
    EXPECT_FALSE(IsTimeout(mgr));
}

/**
 * @tc.name: IsTimeoutWithRawMove001
 * @tc.desc: Returns true when rawMoveEvent timestamp is older than 300ms.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, IsTimeoutWithRawMove001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawDownEvent_ = MakeEventWithOffset(TouchType::DOWN, TEST_Y_DOWN, 400);
    mgr.rawMoveEvent_ = MakeEventWithOffset(TouchType::MOVE, TEST_Y_MOVE, 400);
    EXPECT_TRUE(IsTimeout(mgr));
}

/**
 * @tc.name: IsTimeoutWithoutRawMove001
 * @tc.desc: Uses rawDownEvent timestamp when rawMoveEvent is absent; false within 300ms.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, IsTimeoutWithoutRawMove001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawDownEvent_ = MakeEvent(TouchType::DOWN, TEST_Y_DOWN);
    EXPECT_FALSE(IsTimeout(mgr));
}

/**
 * @tc.name: IsTimeoutExceedsThreshold001
 * @tc.desc: Returns true when rawDownEvent timestamp exceeds 300ms (no rawMove).
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, IsTimeoutExceedsThreshold001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawDownEvent_ = MakeEventWithOffset(TouchType::DOWN, TEST_Y_DOWN, 400);
    EXPECT_TRUE(IsTimeout(mgr));
}

// ===========================================================================
// Group C: IsReachEnd
// ===========================================================================

/**
 * @tc.name: IsReachEndTrue001
 * @tc.desc: Returns true when abs(remain) <= threshold.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, IsReachEndTrue001, TestSize.Level1)
{
    EXPECT_TRUE(IsReachEnd(0.05f, TEST_THRESHOLD));
    EXPECT_TRUE(IsReachEnd(-0.05f, TEST_THRESHOLD));
    EXPECT_TRUE(IsReachEnd(TEST_THRESHOLD, TEST_THRESHOLD));
}

/**
 * @tc.name: IsReachEndFalse001
 * @tc.desc: Returns false when abs(remain) > threshold.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, IsReachEndFalse001, TestSize.Level1)
{
    EXPECT_FALSE(IsReachEnd(1.0f, TEST_THRESHOLD));
    EXPECT_FALSE(IsReachEnd(-1.0f, TEST_THRESHOLD));
}

// ===========================================================================
// Group D: GetNextStep
// ===========================================================================

/**
 * @tc.name: GetNextStepWithinThreshold001
 * @tc.desc: Returns remainingDistance directly when within threshold.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, GetNextStepWithinThreshold001, TestSize.Level1)
{
    auto result = GetNextStep(0.05f, TEST_THRESHOLD, std::chrono::milliseconds(33));
    EXPECT_FLOAT_EQ(result, 0.05f);
}

/**
 * @tc.name: GetNextStepBeyondThreshold001
 * @tc.desc: Returns damped step when beyond threshold.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, GetNextStepBeyondThreshold001, TestSize.Level1)
{
    float remaining = 100.0f;
    auto result = GetNextStep(remaining, TEST_THRESHOLD, std::chrono::milliseconds(33));
    float alpha = 1.0f - std::exp(-0.040f * 33);
    EXPECT_FLOAT_EQ(result, alpha * remaining);
}

// ===========================================================================
// Group E: Constructor & GetType
// ===========================================================================

/**
 * @tc.name: Constructor001
 * @tc.desc: Constructor creates IdleState.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, Constructor001, TestSize.Level1)
{
    CompatibleManager mgr;
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::IDLE);
}

// ===========================================================================
// Group F: IdleState::NotifyNewEvent
// ===========================================================================

/**
 * @tc.name: IdleStateNotifyDown001
 * @tc.desc: IdleState DOWN transitions to READY and returns NOT_INTERCEPT_EVENT.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, IdleStateNotifyDown001, TestSize.Level1)
{
    CompatibleManager mgr;
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::DOWN, TEST_Y_DOWN));
    EXPECT_FALSE(result); // NOT_INTERCEPT_EVENT
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::READY);
}

/**
 * @tc.name: IdleStateNotifyMove001
 * @tc.desc: IdleState MOVE is unexpected, resets to IDLE, returns INTERCEPT_EVENT.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, IdleStateNotifyMove001, TestSize.Level1)
{
    CompatibleManager mgr;
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::MOVE, TEST_Y_MOVE));
    EXPECT_TRUE(result); // INTERCEPT_EVENT
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::IDLE);
}

/**
 * @tc.name: IdleStateNotifyUp001
 * @tc.desc: IdleState UP is unexpected, resets to IDLE, returns INTERCEPT_EVENT.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, IdleStateNotifyUp001, TestSize.Level1)
{
    CompatibleManager mgr;
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::UP));
    EXPECT_TRUE(result);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::IDLE);
}

/**
 * @tc.name: IdleStateNotifyDefault001
 * @tc.desc: IdleState default/unexpected event resets to IDLE, returns INTERCEPT_EVENT.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, IdleStateNotifyDefault001, TestSize.Level1)
{
    CompatibleManager mgr;
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::CANCEL));
    EXPECT_TRUE(result);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::IDLE);
}

// ===========================================================================
// Group G-I: IdleState EventGenerate, start, GetType
// ===========================================================================

/**
 * @tc.name: IdleStateEventGenerate001
 * @tc.desc: IdleState::EventGenerate returns nullopt.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, IdleStateEventGenerate001, TestSize.Level1)
{
    CompatibleManager mgr;
    EXPECT_FALSE(mgr.EventGenerate().has_value());
}

/**
 * @tc.name: IdleStateStartClearsState001
 * @tc.desc: IdleState::start calls ClearAllState.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, IdleStateStartClearsState001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawDownEvent_ = MakeEvent(TouchType::DOWN, TEST_Y_DOWN);
    mgr.rawMoveEvent_ = MakeEvent(TouchType::MOVE, TEST_Y_MOVE);
    mgr.rawUpEvent_ = MakeEvent(TouchType::UP);
    mgr.generatedMoveEvent_ = MakeEvent(TouchType::MOVE, TEST_Y_MOVE);
    mgr.remainingDistance_ = 42.0f;
    // Trigger transition back to Idle (ReadyState + CANCEL -> Idle, which calls ClearAllState via start())
    GoToReadyState(mgr);
    mgr.NotifyNewEvent(MakeEvent(TouchType::CANCEL));
    EXPECT_FALSE(mgr.rawDownEvent_.has_value());
    EXPECT_FALSE(mgr.rawMoveEvent_.has_value());
    EXPECT_FALSE(mgr.rawUpEvent_.has_value());
    EXPECT_FALSE(mgr.generatedMoveEvent_.has_value());
    EXPECT_FLOAT_EQ(mgr.remainingDistance_, 0.0f);
}

// ===========================================================================
// Group J: ReadyState::NotifyNewEvent
// ===========================================================================

/**
 * @tc.name: ReadyStateNotifyDown001
 * @tc.desc: ReadyState DOWN is unexpected, resets to IDLE.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, ReadyStateNotifyDown001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToReadyState(mgr);
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::DOWN, TEST_Y_DOWN));
    EXPECT_TRUE(result);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::IDLE);
}

/**
 * @tc.name: ReadyStateNotifyMove001
 * @tc.desc: ReadyState MOVE transitions to ONGOING.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, ReadyStateNotifyMove001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToReadyState(mgr);
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::MOVE, TEST_Y_MOVE));
    EXPECT_TRUE(result);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::ONGOING);
}

/**
 * @tc.name: ReadyStateNotifyUp001
 * @tc.desc: ReadyState UP is unexpected, resets to IDLE.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, ReadyStateNotifyUp001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToReadyState(mgr);
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::UP));
    EXPECT_TRUE(result);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::IDLE);
}

/**
 * @tc.name: ReadyStateNotifyCancel001
 * @tc.desc: ReadyState CANCEL transitions to IDLE and returns NOT_INTERCEPT_EVENT.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, ReadyStateNotifyCancel001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToReadyState(mgr);
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::CANCEL));
    EXPECT_FALSE(result);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::IDLE);
}

/**
 * @tc.name: ReadyStateNotifyDefault001
 * @tc.desc: ReadyState default/unexpected event resets to IDLE.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, ReadyStateNotifyDefault001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToReadyState(mgr);
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::UNKNOWN));
    EXPECT_TRUE(result);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::IDLE);
}

// ===========================================================================
// Group K-M: ReadyState EventGenerate, start, GetType
// ===========================================================================

/**
 * @tc.name: ReadyStateEventGenerate001
 * @tc.desc: ReadyState::EventGenerate returns nullopt.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, ReadyStateEventGenerate001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToReadyState(mgr);
    EXPECT_FALSE(mgr.EventGenerate().has_value());
}

/**
 * @tc.name: ReadyStateStartClearsEvents001
 * @tc.desc: ReadyState::start clears rawUpEvent and rawMoveEvent but not rawDownEvent.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, ReadyStateStartClearsEvents001, TestSize.Level1)
{
    CompatibleManager mgr;
    // ReadyState::start is called during Idle->Ready transition (DOWN).
    mgr.rawUpEvent_ = MakeEvent(TouchType::UP);
    mgr.rawMoveEvent_ = MakeEvent(TouchType::MOVE, TEST_Y_MOVE);
    GoToReadyState(mgr);
    EXPECT_FALSE(mgr.rawUpEvent_.has_value());
    EXPECT_FALSE(mgr.rawMoveEvent_.has_value());
    EXPECT_TRUE(mgr.rawDownEvent_.has_value());
}

/**
 * @tc.name: ReadyStateGetType001
 * @tc.desc: ReadyState GetType returns READY.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, ReadyStateGetType001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToReadyState(mgr);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::READY);
}

// ===========================================================================
// Group N: OngoingState::NotifyNewEvent
// ===========================================================================

/**
 * @tc.name: OngoingStateNotifyDown001
 * @tc.desc: OngoingState DOWN transitions to READY.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, OngoingStateNotifyDown001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToOngoingState(mgr);
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::DOWN, TEST_Y_DOWN));
    EXPECT_TRUE(result);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::READY);
}

/**
 * @tc.name: OngoingStateNotifyMove001
 * @tc.desc: OngoingState MOVE stays ONGOING.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, OngoingStateNotifyMove001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToOngoingState(mgr);
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::MOVE, TEST_Y_LARGE));
    EXPECT_TRUE(result);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::ONGOING);
}

/**
 * @tc.name: OngoingStateNotifyUp001
 * @tc.desc: OngoingState UP stays ONGOING.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, OngoingStateNotifyUp001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToOngoingState(mgr);
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::UP));
    EXPECT_TRUE(result);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::ONGOING);
}

/**
 * @tc.name: OngoingStateNotifyCancel001
 * @tc.desc: OngoingState CANCEL transitions to IDLE and returns NOT_INTERCEPT_EVENT.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, OngoingStateNotifyCancel001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToOngoingState(mgr);
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::CANCEL));
    EXPECT_FALSE(result);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::IDLE);
}

/**
 * @tc.name: OngoingStateNotifyDefault001
 * @tc.desc: OngoingState default/unexpected event stays ONGOING.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, OngoingStateNotifyDefault001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToOngoingState(mgr);
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::UNKNOWN));
    EXPECT_TRUE(result);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::ONGOING);
}

// ===========================================================================
// Group O-Q: OngoingState EventGenerate, start, GetType
// ===========================================================================

/**
 * @tc.name: OngoingStateEventGenerateReachEnd001
 * @tc.desc: OngoingState::EventGenerate with IsReachEnd true transitions to END.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, OngoingStateEventGenerateReachEnd001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToOngoingState(mgr, TEST_Y_DOWN, TEST_Y_DOWN); // remainingDistance_ = 0
    auto event = mgr.EventGenerate();
    EXPECT_TRUE(event.has_value());
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::END);
}

/**
 * @tc.name: OngoingStateEventGenerateNotReachEnd001
 * @tc.desc: OngoingState::EventGenerate with large remaining distance stays ONGOING.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, OngoingStateEventGenerateNotReachEnd001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToOngoingState(mgr, TEST_Y_DOWN, TEST_Y_LARGE); // remainingDistance_ = 400
    auto event = mgr.EventGenerate();
    EXPECT_TRUE(event.has_value());
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::ONGOING);
}

/**
 * @tc.name: OngoingStateStartNoOp001
 * @tc.desc: OngoingState::start does not clear state (rawDownEvent preserved).
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, OngoingStateStartNoOp001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToOngoingState(mgr);
    // After entering Ongoing, rawDownEvent should still be set (start is noop).
    EXPECT_TRUE(mgr.rawDownEvent_.has_value());
    EXPECT_TRUE(mgr.rawMoveEvent_.has_value());
}

/**
 * @tc.name: OngoingStateGetType001
 * @tc.desc: OngoingState GetType returns ONGOING.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, OngoingStateGetType001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToOngoingState(mgr);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::ONGOING);
}

// ===========================================================================
// Group R: EndState::NotifyNewEvent
// ===========================================================================

/**
 * @tc.name: EndStateNotifyDown001
 * @tc.desc: EndState DOWN transitions to READY.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, EndStateNotifyDown001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToEndState(mgr);
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::DOWN, TEST_Y_DOWN));
    EXPECT_TRUE(result);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::READY);
}

/**
 * @tc.name: EndStateNotifyMove001
 * @tc.desc: EndState MOVE transitions to ONGOING.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, EndStateNotifyMove001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToEndState(mgr);
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::MOVE, TEST_Y_MOVE));
    EXPECT_TRUE(result);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::ONGOING);
}

/**
 * @tc.name: EndStateNotifyUp001
 * @tc.desc: EndState UP stays END.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, EndStateNotifyUp001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToEndState(mgr);
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::UP));
    EXPECT_TRUE(result);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::END);
}

/**
 * @tc.name: EndStateNotifyCancel001
 * @tc.desc: EndState CANCEL transitions to IDLE and returns NOT_INTERCEPT_EVENT.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, EndStateNotifyCancel001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToEndState(mgr);
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::CANCEL));
    EXPECT_FALSE(result);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::IDLE);
}

/**
 * @tc.name: EndStateNotifyDefault001
 * @tc.desc: EndState default/unexpected event stays END.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, EndStateNotifyDefault001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToEndState(mgr);
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::UNKNOWN));
    EXPECT_TRUE(result);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::END);
}

// ===========================================================================
// Group S: EndState::EventGenerate
// ===========================================================================

/**
 * @tc.name: EndStateEventGenerateWithRawUp001
 * @tc.desc: EndState::EventGenerate with rawUpEvent generates UP event and transitions to IDLE.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, EndStateEventGenerateWithRawUp001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToEndState(mgr);
    mgr.NotifyNewEvent(MakeEvent(TouchType::UP)); // stays END, sets rawUpEvent
    ASSERT_TRUE(mgr.GetRawUpEvent().has_value());
    auto event = mgr.EventGenerate();
    EXPECT_TRUE(event.has_value());
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::IDLE);
}

/**
 * @tc.name: EndStateEventGenerateMove001
 * @tc.desc: EndState::EventGenerate without rawUp or timeout generates MOVE event, stays END.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, EndStateEventGenerateMove001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToEndState(mgr);
    // Immediate call, no timeout (within 300ms), no rawUpEvent.
    auto event = mgr.EventGenerate();
    EXPECT_TRUE(event.has_value());
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::END);
}

// ===========================================================================
// Group T-U: EndState start, GetType
// ===========================================================================

/**
 * @tc.name: EndStateStartNoOp001
 * @tc.desc: EndState::start does not clear state.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, EndStateStartNoOp001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToEndState(mgr);
    EXPECT_TRUE(mgr.rawDownEvent_.has_value());
}

/**
 * @tc.name: EndStateGetType001
 * @tc.desc: EndState GetType returns END.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, EndStateGetType001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToEndState(mgr);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::END);
}

// ===========================================================================
// Group V: GenerateUpEvent
// ===========================================================================

/**
 * @tc.name: GenerateUpEventBothPresent001
 * @tc.desc: GenerateUpEvent with rawUpEvent and generatedMoveEvent uses rawUp y.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, GenerateUpEventBothPresent001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawUpEvent_ = MakeEvent(TouchType::UP, 50.0f);
    mgr.generatedMoveEvent_ = MakeEvent(TouchType::MOVE, 80.0f);
    auto event = mgr.GenerateUpEvent();
    ASSERT_TRUE(event.has_value());
    EXPECT_EQ(event->type, TouchType::UP);
    EXPECT_FLOAT_EQ(event->y, 80.0f);
}

/**
 * @tc.name: GenerateUpEventGeneratedMoveOnly001
 * @tc.desc: GenerateUpEvent with only generatedMoveEvent converts it to UP.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, GenerateUpEventGeneratedMoveOnly001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.generatedMoveEvent_ = MakeEvent(TouchType::MOVE, 80.0f);
    auto event = mgr.GenerateUpEvent();
    ASSERT_TRUE(event.has_value());
    EXPECT_EQ(event->type, TouchType::UP);
}

/**
 * @tc.name: GenerateUpEventRawDownOnly001
 * @tc.desc: GenerateUpEvent with only rawDownEvent converts it to UP.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, GenerateUpEventRawDownOnly001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawDownEvent_ = MakeEvent(TouchType::DOWN, TEST_Y_DOWN);
    auto event = mgr.GenerateUpEvent();
    ASSERT_TRUE(event.has_value());
    EXPECT_EQ(event->type, TouchType::UP);
}

/**
 * @tc.name: GenerateUpEventNoneReturnsNullopt001
 * @tc.desc: GenerateUpEvent with no events returns nullopt.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, GenerateUpEventNoneReturnsNullopt001, TestSize.Level1)
{
    CompatibleManager mgr;
    auto event = mgr.GenerateUpEvent();
    EXPECT_FALSE(event.has_value());
}

// ===========================================================================
// Group W: CompatibleManager::NotifyNewEvent (integration)
// ===========================================================================

/**
 * @tc.name: NotifyNewEventUpdatesRawEvent001
 * @tc.desc: NotifyNewEvent updates rawDownEvent via UpdateRawEvent then delegates to state.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, NotifyNewEventUpdatesRawEvent001, TestSize.Level1)
{
    CompatibleManager mgr;
    bool result = mgr.NotifyNewEvent(MakeEvent(TouchType::DOWN, TEST_Y_DOWN));
    EXPECT_FALSE(result);
    EXPECT_TRUE(mgr.rawDownEvent_.has_value());
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::READY);
}

// ===========================================================================
// Group X: CompatibleManager::EventGenerate
// ===========================================================================

/**
 * @tc.name: EventGenerateSetsIsGenerate001
 * @tc.desc: EventGenerate sets isGenerate flag on the returned event.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, EventGenerateSetsIsGenerate001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToOngoingState(mgr);
    auto event = mgr.EventGenerate();
    ASSERT_TRUE(event.has_value());
    EXPECT_TRUE(event->isGenerate);
}

/**
 * @tc.name: EventGenerateReturnsNullopt001
 * @tc.desc: EventGenerate in IDLE returns nullopt (no isGenerate flag path).
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, EventGenerateReturnsNullopt001, TestSize.Level1)
{
    CompatibleManager mgr;
    EXPECT_FALSE(mgr.EventGenerate().has_value());
}

// ===========================================================================
// Group Y: CompatibleManager::BreakGenerate
// ===========================================================================

/**
 * @tc.name: BreakGenerateIdleReturnsNullopt001
 * @tc.desc: BreakGenerate in IDLE returns nullopt.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, BreakGenerateIdleReturnsNullopt001, TestSize.Level1)
{
    CompatibleManager mgr;
    auto event = mgr.BreakGenerate();
    EXPECT_FALSE(event.has_value());
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::IDLE);
}

/**
 * @tc.name: BreakGenerateOngoingReturnsUpEvent001
 * @tc.desc: BreakGenerate in ONGOING generates UP event with isGenerate and resets to IDLE.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, BreakGenerateOngoingReturnsUpEvent001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToOngoingState(mgr);
    auto event = mgr.BreakGenerate();
    ASSERT_TRUE(event.has_value());
    EXPECT_TRUE(event->isGenerate);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::IDLE);
}

/**
 * @tc.name: BreakGenerateNoEventsReturnsNullopt001
 * @tc.desc: BreakGenerate in non-IDLE without events returns nullopt but resets state.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, BreakGenerateNoEventsReturnsNullopt001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.SetState(std::make_unique<CompatibleManager::OngoingState>(mgr));
    auto event = mgr.BreakGenerate();
    EXPECT_FALSE(event.has_value());
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::IDLE);
}

// ===========================================================================
// Group Z: UpdateRawEvent
// ===========================================================================

/**
 * @tc.name: UpdateRawEventDown001
 * @tc.desc: UpdateRawEvent with DOWN sets rawDownEvent.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, UpdateRawEventDown001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.UpdateRawEvent(MakeEvent(TouchType::DOWN, TEST_Y_DOWN));
    ASSERT_TRUE(mgr.rawDownEvent_.has_value());
    EXPECT_FLOAT_EQ(mgr.rawDownEvent_->y, TEST_Y_DOWN);
}

/**
 * @tc.name: UpdateRawEventMove001
 * @tc.desc: UpdateRawEvent with MOVE updates distance and sets rawMoveEvent.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, UpdateRawEventMove001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawDownEvent_ = MakeEvent(TouchType::DOWN, TEST_Y_DOWN);
    mgr.UpdateRawEvent(MakeEvent(TouchType::MOVE, TEST_Y_MOVE));
    ASSERT_TRUE(mgr.rawMoveEvent_.has_value());
    EXPECT_FLOAT_EQ(mgr.remainingDistance_, TEST_Y_MOVE - TEST_Y_DOWN);
}

/**
 * @tc.name: UpdateRawEventUp001
 * @tc.desc: UpdateRawEvent with UP sets rawUpEvent.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, UpdateRawEventUp001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.UpdateRawEvent(MakeEvent(TouchType::UP));
    ASSERT_TRUE(mgr.rawUpEvent_.has_value());
}

/**
 * @tc.name: UpdateRawEventDefault001
 * @tc.desc: UpdateRawEvent with default type (CANCEL) does nothing.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, UpdateRawEventDefault001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.UpdateRawEvent(MakeEvent(TouchType::CANCEL));
    EXPECT_FALSE(mgr.rawDownEvent_.has_value());
    EXPECT_FALSE(mgr.rawMoveEvent_.has_value());
    EXPECT_FALSE(mgr.rawUpEvent_.has_value());
}

// ===========================================================================
// Group AA: UpdateDistance
// ===========================================================================

/**
 * @tc.name: UpdateDistanceNoRawDown001
 * @tc.desc: UpdateDistance returns early without rawDownEvent.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, UpdateDistanceNoRawDown001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.UpdateDistance(TEST_Y_MOVE);
    EXPECT_FLOAT_EQ(mgr.remainingDistance_, 0.0f);
}

/**
 * @tc.name: UpdateDistanceWithRawMove001
 * @tc.desc: UpdateDistance uses rawMoveEvent y when available.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, UpdateDistanceWithRawMove001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawDownEvent_ = MakeEvent(TouchType::DOWN, TEST_Y_DOWN);
    mgr.rawMoveEvent_ = MakeEvent(TouchType::MOVE, 150.0f);
    mgr.remainingDistance_ = 50.0f;
    mgr.UpdateDistance(TEST_Y_LARGE);
    // 50 + (500 - 150) = 400
    EXPECT_FLOAT_EQ(mgr.remainingDistance_, 400.0f);
}

/**
 * @tc.name: UpdateDistanceWithoutRawMove001
 * @tc.desc: UpdateDistance uses rawDownEvent y when rawMoveEvent absent.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, UpdateDistanceWithoutRawMove001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawDownEvent_ = MakeEvent(TouchType::DOWN, TEST_Y_DOWN);
    mgr.remainingDistance_ = 0.0f;
    mgr.UpdateDistance(TEST_Y_MOVE);
    // 0 + (200 - 100) = 100
    EXPECT_FLOAT_EQ(mgr.remainingDistance_, TEST_Y_MOVE - TEST_Y_DOWN);
}

// ===========================================================================
// Group AB: SetState
// ===========================================================================

/**
 * @tc.name: SetStateCallsStart001
 * @tc.desc: SetState calls start() on the new state.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, SetStateCallsStart001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawUpEvent_ = MakeEvent(TouchType::UP);
    mgr.rawMoveEvent_ = MakeEvent(TouchType::MOVE, TEST_Y_MOVE);
    mgr.SetState(std::make_unique<CompatibleManager::ReadyState>(mgr));
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::READY);
    // ReadyState::start clears rawUp and rawMove.
    EXPECT_FALSE(mgr.rawUpEvent_.has_value());
    EXPECT_FALSE(mgr.rawMoveEvent_.has_value());
}

// ===========================================================================
// Group AC: InitGeneratedMoveEvent
// ===========================================================================

/**
 * @tc.name: InitGeneratedMoveAlreadyInitialized001
 * @tc.desc: InitGeneratedMoveEvent returns early if already initialized.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, InitGeneratedMoveAlreadyInitialized001, TestSize.Level1)
{
    CompatibleManager mgr;
    auto original = MakeEvent(TouchType::MOVE, 77.0f);
    mgr.generatedMoveEvent_ = original;
    mgr.InitGeneratedMoveEvent();
    ASSERT_TRUE(mgr.generatedMoveEvent_.has_value());
    EXPECT_FLOAT_EQ(mgr.generatedMoveEvent_->y, 77.0f);
}

/**
 * @tc.name: InitGeneratedMoveNoRawMove001
 * @tc.desc: InitGeneratedMoveEvent fails without rawMoveEvent.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, InitGeneratedMoveNoRawMove001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawDownEvent_ = MakeEvent(TouchType::DOWN, TEST_Y_DOWN);
    mgr.InitGeneratedMoveEvent();
    EXPECT_FALSE(mgr.generatedMoveEvent_.has_value());
}

/**
 * @tc.name: InitGeneratedMoveNoRawDown001
 * @tc.desc: InitGeneratedMoveEvent fails without rawDownEvent.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, InitGeneratedMoveNoRawDown001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawMoveEvent_ = MakeEvent(TouchType::MOVE, TEST_Y_MOVE);
    mgr.InitGeneratedMoveEvent();
    EXPECT_FALSE(mgr.generatedMoveEvent_.has_value());
}

/**
 * @tc.name: InitGeneratedMoveNoEvents001
 * @tc.desc: InitGeneratedMoveEvent fails without any events.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, InitGeneratedMoveNoEvents001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.InitGeneratedMoveEvent();
    EXPECT_FALSE(mgr.generatedMoveEvent_.has_value());
}

/**
 * @tc.name: InitGeneratedMoveSuccess001
 * @tc.desc: InitGeneratedMoveEvent initializes with rawDownEvent y.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, InitGeneratedMoveSuccess001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawDownEvent_ = MakeEvent(TouchType::DOWN, TEST_Y_DOWN);
    mgr.rawMoveEvent_ = MakeEvent(TouchType::MOVE, TEST_Y_LARGE);
    mgr.InitGeneratedMoveEvent();
    ASSERT_TRUE(mgr.generatedMoveEvent_.has_value());
    EXPECT_FLOAT_EQ(mgr.generatedMoveEvent_->y, TEST_Y_DOWN);
}

// ===========================================================================
// Group AD: GenerateMoveEvent
// ===========================================================================

/**
 * @tc.name: GenerateMoveEventCapsDuration001
 * @tc.desc: GenerateMoveEvent updates generatedMoveEvent and remainingDistance.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, GenerateMoveEventCapsDuration001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawDownEvent_ = MakeEvent(TouchType::DOWN, TEST_Y_DOWN);
    mgr.rawMoveEvent_ = MakeEventWithOffset(TouchType::MOVE, TEST_Y_LARGE, 50);
    mgr.remainingDistance_ = TEST_Y_LARGE - TEST_Y_DOWN;
    mgr.GenerateMoveEvent();
    ASSERT_TRUE(mgr.generatedMoveEvent_.has_value());
    EXPECT_NE(mgr.remainingDistance_, TEST_Y_LARGE - TEST_Y_DOWN);
}

// ===========================================================================
// Group AE: Clear methods
// ===========================================================================

/**
 * @tc.name: ClearAllState001
 * @tc.desc: ClearAllState resets all members.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, ClearAllState001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawDownEvent_ = MakeEvent(TouchType::DOWN, TEST_Y_DOWN);
    mgr.rawMoveEvent_ = MakeEvent(TouchType::MOVE, TEST_Y_MOVE);
    mgr.rawUpEvent_ = MakeEvent(TouchType::UP);
    mgr.generatedMoveEvent_ = MakeEvent(TouchType::MOVE, TEST_Y_MOVE);
    mgr.remainingDistance_ = 42.0f;
    mgr.ClearAllState();
    EXPECT_FALSE(mgr.rawDownEvent_.has_value());
    EXPECT_FALSE(mgr.rawMoveEvent_.has_value());
    EXPECT_FALSE(mgr.rawUpEvent_.has_value());
    EXPECT_FALSE(mgr.generatedMoveEvent_.has_value());
    EXPECT_FLOAT_EQ(mgr.remainingDistance_, 0.0f);
}

/**
 * @tc.name: ClearRawUpEvent001
 * @tc.desc: ClearRawUpEvent resets only rawUpEvent.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, ClearRawUpEvent001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawDownEvent_ = MakeEvent(TouchType::DOWN, TEST_Y_DOWN);
    mgr.rawMoveEvent_ = MakeEvent(TouchType::MOVE, TEST_Y_MOVE);
    mgr.rawUpEvent_ = MakeEvent(TouchType::UP);
    mgr.ClearRawUpEvent();
    EXPECT_FALSE(mgr.rawUpEvent_.has_value());
    EXPECT_TRUE(mgr.rawDownEvent_.has_value());
    EXPECT_TRUE(mgr.rawMoveEvent_.has_value());
}

/**
 * @tc.name: ClearRawMoveEvent001
 * @tc.desc: ClearRawMoveEvent resets only rawMoveEvent.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, ClearRawMoveEvent001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawDownEvent_ = MakeEvent(TouchType::DOWN, TEST_Y_DOWN);
    mgr.rawMoveEvent_ = MakeEvent(TouchType::MOVE, TEST_Y_MOVE);
    mgr.rawUpEvent_ = MakeEvent(TouchType::UP);
    mgr.ClearRawMoveEvent();
    EXPECT_FALSE(mgr.rawMoveEvent_.has_value());
    EXPECT_TRUE(mgr.rawDownEvent_.has_value());
    EXPECT_TRUE(mgr.rawUpEvent_.has_value());
}

// ===========================================================================
// Group AF: Getters
// ===========================================================================

/**
 * @tc.name: GetRawDownEvent001
 * @tc.desc: GetRawDownEvent returns the stored value.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, GetRawDownEvent001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawDownEvent_ = MakeEvent(TouchType::DOWN, TEST_Y_DOWN);
    auto event = mgr.GetRawDownEvent();
    ASSERT_TRUE(event.has_value());
    EXPECT_FLOAT_EQ(event->y, TEST_Y_DOWN);
}

/**
 * @tc.name: GetRawDownEvent002
 * @tc.desc: GetRawDownEvent returns nullopt when not set.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, GetRawDownEvent002, TestSize.Level1)
{
    CompatibleManager mgr;
    EXPECT_FALSE(mgr.GetRawDownEvent().has_value());
}

/**
 * @tc.name: GetRawMoveEvent001
 * @tc.desc: GetRawMoveEvent returns the stored value.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, GetRawMoveEvent001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawMoveEvent_ = MakeEvent(TouchType::MOVE, TEST_Y_MOVE);
    auto event = mgr.GetRawMoveEvent();
    ASSERT_TRUE(event.has_value());
    EXPECT_FLOAT_EQ(event->y, TEST_Y_MOVE);
}

/**
 * @tc.name: GetRawMoveEvent002
 * @tc.desc: GetRawMoveEvent returns nullopt when not set.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, GetRawMoveEvent002, TestSize.Level1)
{
    CompatibleManager mgr;
    EXPECT_FALSE(mgr.GetRawMoveEvent().has_value());
}

/**
 * @tc.name: GetRawUpEvent001
 * @tc.desc: GetRawUpEvent returns the stored value.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, GetRawUpEvent001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.rawUpEvent_ = MakeEvent(TouchType::UP);
    EXPECT_TRUE(mgr.GetRawUpEvent().has_value());
}

/**
 * @tc.name: GetRawUpEvent002
 * @tc.desc: GetRawUpEvent returns nullopt when not set.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, GetRawUpEvent002, TestSize.Level1)
{
    CompatibleManager mgr;
    EXPECT_FALSE(mgr.GetRawUpEvent().has_value());
}

/**
 * @tc.name: GetGeneratedMoveEvent001
 * @tc.desc: GetGeneratedMoveEvent returns the stored value.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, GetGeneratedMoveEvent001, TestSize.Level1)
{
    CompatibleManager mgr;
    mgr.generatedMoveEvent_ = MakeEvent(TouchType::MOVE, TEST_Y_MOVE);
    auto event = mgr.GetGeneratedMoveEvent();
    ASSERT_TRUE(event.has_value());
    EXPECT_FLOAT_EQ(event->y, TEST_Y_MOVE);
}

/**
 * @tc.name: GetGeneratedMoveEvent002
 * @tc.desc: GetGeneratedMoveEvent returns nullopt when not set.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, GetGeneratedMoveEvent002, TestSize.Level1)
{
    CompatibleManager mgr;
    EXPECT_FALSE(mgr.GetGeneratedMoveEvent().has_value());
}

// ===========================================================================
// Group AG: Integration / Full Lifecycle
// ===========================================================================

/**
 * @tc.name: FullLifecycle001
 * @tc.desc: Full lifecycle Idle -> Ready -> Ongoing -> End -> Idle with UP event.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, FullLifecycle001, TestSize.Level1)
{
    CompatibleManager mgr;
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::IDLE);

    // Idle -> Ready
    EXPECT_FALSE(mgr.NotifyNewEvent(MakeEvent(TouchType::DOWN, TEST_Y_DOWN)));
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::READY);

    // Ready -> Ongoing
    EXPECT_TRUE(mgr.NotifyNewEvent(MakeEvent(TouchType::MOVE, TEST_Y_DOWN)));
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::ONGOING);

    // Ongoing -> End (remainingDistance is 0)
    EXPECT_TRUE(mgr.EventGenerate().has_value());
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::END);

    // End -> Idle (via UP event -> EventGenerate)
    mgr.NotifyNewEvent(MakeEvent(TouchType::UP));
    EXPECT_TRUE(mgr.EventGenerate().has_value());
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::IDLE);
}

/**
 * @tc.name: FullLifecycleBreakGenerate001
 * @tc.desc: Full lifecycle with BreakGenerate returning to IDLE.
 * @tc.type: FUNC
 */
HWTEST_F(CompatibleManagerTestNg, FullLifecycleBreakGenerate001, TestSize.Level1)
{
    CompatibleManager mgr;
    GoToOngoingState(mgr);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::ONGOING);
    auto event = mgr.BreakGenerate();
    EXPECT_TRUE(event.has_value());
    EXPECT_TRUE(event->isGenerate);
    EXPECT_EQ(mgr.GetCurrentStateType(), StateType::IDLE);
}
} // namespace OHOS::Ace::NG
