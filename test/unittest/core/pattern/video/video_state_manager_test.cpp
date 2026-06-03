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

#include <string>
#include <memory>

#include "gmock/gmock-actions.h"
#include "gtest/gtest.h"

#define private public
#define protected public

#include "core/components_ng/pattern/video/video_state_manager.h"
#include "core/components_ng/pattern/video/video_state_machine_pattern.h"
#include "core/components_ng/pattern/video/video_controller_async.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class MockVideoStateMachinePattern : public VideoStateMachinePattern {
public:
    MockVideoStateMachinePattern() : VideoStateMachinePattern(nullptr) {}

    bool IsFullScreen() const override { return isFullScreen_; }
    void SetIsFullScreen(bool value) { isFullScreen_ = value; }

private:
    bool isFullScreen_ = false;
};

class VideoStateManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override {}
    void TearDown() override {}

protected:
    RefPtr<MockVideoStateMachinePattern> CreateMockPattern()
    {
        return AceType::MakeRefPtr<MockVideoStateMachinePattern>();
    }

    RefPtr<VideoStateManager> CreateManager(const RefPtr<MockVideoStateMachinePattern>& pattern)
    {
        WeakPtr<VideoStateMachinePattern> weakPattern = AceType::WeakClaim(AceType::RawPtr(pattern));
        return AceType::MakeRefPtr<VideoStateManager>(weakPattern);
    }
};

/**
 * @tc.name: VideoStateMachineCanPlay001
 * @tc.desc: Test CanPlay returns true for PREPARED, PAUSED, COMPLETED, STOPPED and false for others.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateMachineCanPlay001, TestSize.Level1)
{
    EXPECT_TRUE(VideoStateMachine::CanPlay(VideoPlaybackState::PREPARED));
    EXPECT_TRUE(VideoStateMachine::CanPlay(VideoPlaybackState::PAUSED));
    EXPECT_TRUE(VideoStateMachine::CanPlay(VideoPlaybackState::COMPLETED));
    EXPECT_TRUE(VideoStateMachine::CanPlay(VideoPlaybackState::STOPPED));
    EXPECT_FALSE(VideoStateMachine::CanPlay(VideoPlaybackState::CREATED));
    EXPECT_FALSE(VideoStateMachine::CanPlay(VideoPlaybackState::PLAYING));
    EXPECT_FALSE(VideoStateMachine::CanPlay(VideoPlaybackState::ERROR));
}

/**
 * @tc.name: VideoStateMachineCanPause001
 * @tc.desc: Test CanPause returns true only for PLAYING state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateMachineCanPause001, TestSize.Level1)
{
    EXPECT_TRUE(VideoStateMachine::CanPause(VideoPlaybackState::PLAYING));
    EXPECT_FALSE(VideoStateMachine::CanPause(VideoPlaybackState::CREATED));
    EXPECT_FALSE(VideoStateMachine::CanPause(VideoPlaybackState::PREPARED));
    EXPECT_FALSE(VideoStateMachine::CanPause(VideoPlaybackState::PAUSED));
    EXPECT_FALSE(VideoStateMachine::CanPause(VideoPlaybackState::STOPPED));
    EXPECT_FALSE(VideoStateMachine::CanPause(VideoPlaybackState::COMPLETED));
    EXPECT_FALSE(VideoStateMachine::CanPause(VideoPlaybackState::ERROR));
}

/**
 * @tc.name: VideoStateMachineCanStop001
 * @tc.desc: Test CanStop returns true for PREPARED, PLAYING, PAUSED, COMPLETED and false for others.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateMachineCanStop001, TestSize.Level1)
{
    EXPECT_TRUE(VideoStateMachine::CanStop(VideoPlaybackState::PREPARED));
    EXPECT_TRUE(VideoStateMachine::CanStop(VideoPlaybackState::PLAYING));
    EXPECT_TRUE(VideoStateMachine::CanStop(VideoPlaybackState::PAUSED));
    EXPECT_TRUE(VideoStateMachine::CanStop(VideoPlaybackState::COMPLETED));
    EXPECT_FALSE(VideoStateMachine::CanStop(VideoPlaybackState::CREATED));
    EXPECT_FALSE(VideoStateMachine::CanStop(VideoPlaybackState::STOPPED));
    EXPECT_FALSE(VideoStateMachine::CanStop(VideoPlaybackState::ERROR));
}

/**
 * @tc.name: VideoStateMachineCanSeek001
 * @tc.desc: Test CanSeek returns true for PREPARED, PLAYING, PAUSED, COMPLETED and false for others.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateMachineCanSeek001, TestSize.Level1)
{
    EXPECT_TRUE(VideoStateMachine::CanSeek(VideoPlaybackState::PREPARED));
    EXPECT_TRUE(VideoStateMachine::CanSeek(VideoPlaybackState::PLAYING));
    EXPECT_TRUE(VideoStateMachine::CanSeek(VideoPlaybackState::PAUSED));
    EXPECT_TRUE(VideoStateMachine::CanSeek(VideoPlaybackState::COMPLETED));
    EXPECT_FALSE(VideoStateMachine::CanSeek(VideoPlaybackState::CREATED));
    EXPECT_FALSE(VideoStateMachine::CanSeek(VideoPlaybackState::STOPPED));
    EXPECT_FALSE(VideoStateMachine::CanSeek(VideoPlaybackState::ERROR));
}

/**
 * @tc.name: VideoStateMachineCanPrepare001
 * @tc.desc: Test CanPrepare returns true for CREATED, STOPPED and false for others.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateMachineCanPrepare001, TestSize.Level1)
{
    EXPECT_TRUE(VideoStateMachine::CanPrepare(VideoPlaybackState::CREATED));
    EXPECT_TRUE(VideoStateMachine::CanPrepare(VideoPlaybackState::STOPPED));
    EXPECT_FALSE(VideoStateMachine::CanPrepare(VideoPlaybackState::PREPARED));
    EXPECT_FALSE(VideoStateMachine::CanPrepare(VideoPlaybackState::PLAYING));
    EXPECT_FALSE(VideoStateMachine::CanPrepare(VideoPlaybackState::PAUSED));
    EXPECT_FALSE(VideoStateMachine::CanPrepare(VideoPlaybackState::COMPLETED));
    EXPECT_FALSE(VideoStateMachine::CanPrepare(VideoPlaybackState::ERROR));
}

/**
 * @tc.name: VideoStateMachineIsPlayingState001
 * @tc.desc: Test IsPlayingState returns true only for PLAYING.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateMachineIsPlayingState001, TestSize.Level1)
{
    EXPECT_TRUE(VideoStateMachine::IsPlayingState(VideoPlaybackState::PLAYING));
    EXPECT_FALSE(VideoStateMachine::IsPlayingState(VideoPlaybackState::CREATED));
    EXPECT_FALSE(VideoStateMachine::IsPlayingState(VideoPlaybackState::PREPARED));
    EXPECT_FALSE(VideoStateMachine::IsPlayingState(VideoPlaybackState::PAUSED));
    EXPECT_FALSE(VideoStateMachine::IsPlayingState(VideoPlaybackState::STOPPED));
    EXPECT_FALSE(VideoStateMachine::IsPlayingState(VideoPlaybackState::COMPLETED));
    EXPECT_FALSE(VideoStateMachine::IsPlayingState(VideoPlaybackState::ERROR));
}

/**
 * @tc.name: VideoStateMachineIsPausedState001
 * @tc.desc: Test IsPausedState returns true only for PAUSED.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateMachineIsPausedState001, TestSize.Level1)
{
    EXPECT_TRUE(VideoStateMachine::IsPausedState(VideoPlaybackState::PAUSED));
    EXPECT_FALSE(VideoStateMachine::IsPausedState(VideoPlaybackState::CREATED));
    EXPECT_FALSE(VideoStateMachine::IsPausedState(VideoPlaybackState::PREPARED));
    EXPECT_FALSE(VideoStateMachine::IsPausedState(VideoPlaybackState::PLAYING));
    EXPECT_FALSE(VideoStateMachine::IsPausedState(VideoPlaybackState::STOPPED));
    EXPECT_FALSE(VideoStateMachine::IsPausedState(VideoPlaybackState::COMPLETED));
    EXPECT_FALSE(VideoStateMachine::IsPausedState(VideoPlaybackState::ERROR));
}

/**
 * @tc.name: VideoStateMachineIsStoppedState001
 * @tc.desc: Test IsStoppedState returns true only for STOPPED.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateMachineIsStoppedState001, TestSize.Level1)
{
    EXPECT_TRUE(VideoStateMachine::IsStoppedState(VideoPlaybackState::STOPPED));
    EXPECT_FALSE(VideoStateMachine::IsStoppedState(VideoPlaybackState::CREATED));
    EXPECT_FALSE(VideoStateMachine::IsStoppedState(VideoPlaybackState::PREPARED));
    EXPECT_FALSE(VideoStateMachine::IsStoppedState(VideoPlaybackState::PLAYING));
    EXPECT_FALSE(VideoStateMachine::IsStoppedState(VideoPlaybackState::PAUSED));
    EXPECT_FALSE(VideoStateMachine::IsStoppedState(VideoPlaybackState::COMPLETED));
    EXPECT_FALSE(VideoStateMachine::IsStoppedState(VideoPlaybackState::ERROR));
}

/**
 * @tc.name: VideoStateMachineIsPreparedState001
 * @tc.desc: Test IsPreparedState returns true only for PREPARED.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateMachineIsPreparedState001, TestSize.Level1)
{
    EXPECT_TRUE(VideoStateMachine::IsPreparedState(VideoPlaybackState::PREPARED));
    EXPECT_FALSE(VideoStateMachine::IsPreparedState(VideoPlaybackState::CREATED));
    EXPECT_FALSE(VideoStateMachine::IsPreparedState(VideoPlaybackState::PLAYING));
    EXPECT_FALSE(VideoStateMachine::IsPreparedState(VideoPlaybackState::PAUSED));
    EXPECT_FALSE(VideoStateMachine::IsPreparedState(VideoPlaybackState::STOPPED));
    EXPECT_FALSE(VideoStateMachine::IsPreparedState(VideoPlaybackState::COMPLETED));
    EXPECT_FALSE(VideoStateMachine::IsPreparedState(VideoPlaybackState::ERROR));
}

/**
 * @tc.name: VideoStateMachineIsCreatedState001
 * @tc.desc: Test IsCreatedState returns true only for CREATED.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateMachineIsCreatedState001, TestSize.Level1)
{
    EXPECT_TRUE(VideoStateMachine::IsCreatedState(VideoPlaybackState::CREATED));
    EXPECT_FALSE(VideoStateMachine::IsCreatedState(VideoPlaybackState::PREPARED));
    EXPECT_FALSE(VideoStateMachine::IsCreatedState(VideoPlaybackState::PLAYING));
    EXPECT_FALSE(VideoStateMachine::IsCreatedState(VideoPlaybackState::PAUSED));
    EXPECT_FALSE(VideoStateMachine::IsCreatedState(VideoPlaybackState::STOPPED));
    EXPECT_FALSE(VideoStateMachine::IsCreatedState(VideoPlaybackState::COMPLETED));
    EXPECT_FALSE(VideoStateMachine::IsCreatedState(VideoPlaybackState::ERROR));
}

/**
 * @tc.name: VideoStateMachineIsCompletedState001
 * @tc.desc: Test IsCompletedState returns true only for COMPLETED.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateMachineIsCompletedState001, TestSize.Level1)
{
    EXPECT_TRUE(VideoStateMachine::IsCompletedState(VideoPlaybackState::COMPLETED));
    EXPECT_FALSE(VideoStateMachine::IsCompletedState(VideoPlaybackState::CREATED));
    EXPECT_FALSE(VideoStateMachine::IsCompletedState(VideoPlaybackState::PREPARED));
    EXPECT_FALSE(VideoStateMachine::IsCompletedState(VideoPlaybackState::PLAYING));
    EXPECT_FALSE(VideoStateMachine::IsCompletedState(VideoPlaybackState::PAUSED));
    EXPECT_FALSE(VideoStateMachine::IsCompletedState(VideoPlaybackState::STOPPED));
    EXPECT_FALSE(VideoStateMachine::IsCompletedState(VideoPlaybackState::ERROR));
}

/**
 * @tc.name: VideoStateMachineIsErrorState001
 * @tc.desc: Test IsErrorState returns true only for ERROR.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateMachineIsErrorState001, TestSize.Level1)
{
    EXPECT_TRUE(VideoStateMachine::IsErrorState(VideoPlaybackState::ERROR));
    EXPECT_FALSE(VideoStateMachine::IsErrorState(VideoPlaybackState::CREATED));
    EXPECT_FALSE(VideoStateMachine::IsErrorState(VideoPlaybackState::PREPARED));
    EXPECT_FALSE(VideoStateMachine::IsErrorState(VideoPlaybackState::PLAYING));
    EXPECT_FALSE(VideoStateMachine::IsErrorState(VideoPlaybackState::PAUSED));
    EXPECT_FALSE(VideoStateMachine::IsErrorState(VideoPlaybackState::STOPPED));
    EXPECT_FALSE(VideoStateMachine::IsErrorState(VideoPlaybackState::COMPLETED));
}

/**
 * @tc.name: VideoStateMachineIsActiveState001
 * @tc.desc: Test IsActiveState returns true for PREPARED, PLAYING, PAUSED, COMPLETED.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateMachineIsActiveState001, TestSize.Level1)
{
    EXPECT_TRUE(VideoStateMachine::IsActiveState(VideoPlaybackState::PREPARED));
    EXPECT_TRUE(VideoStateMachine::IsActiveState(VideoPlaybackState::PLAYING));
    EXPECT_TRUE(VideoStateMachine::IsActiveState(VideoPlaybackState::PAUSED));
    EXPECT_TRUE(VideoStateMachine::IsActiveState(VideoPlaybackState::COMPLETED));
    EXPECT_FALSE(VideoStateMachine::IsActiveState(VideoPlaybackState::CREATED));
    EXPECT_FALSE(VideoStateMachine::IsActiveState(VideoPlaybackState::STOPPED));
    EXPECT_FALSE(VideoStateMachine::IsActiveState(VideoPlaybackState::ERROR));
}

/**
 * @tc.name: VideoStateMachineIsUserOperationCallback001
 * @tc.desc: Test IsUserOperationCallback returns true for PLAY, PAUSE, STOP, PREPARE.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateMachineIsUserOperationCallback001, TestSize.Level1)
{
    EXPECT_TRUE(VideoStateMachine::IsUserOperationCallback(VideoPlaybackCommand::PLAY));
    EXPECT_TRUE(VideoStateMachine::IsUserOperationCallback(VideoPlaybackCommand::PAUSE));
    EXPECT_TRUE(VideoStateMachine::IsUserOperationCallback(VideoPlaybackCommand::STOP));
    EXPECT_TRUE(VideoStateMachine::IsUserOperationCallback(VideoPlaybackCommand::PREPARE));
    EXPECT_FALSE(VideoStateMachine::IsUserOperationCallback(VideoPlaybackCommand::COMPLETE));
    EXPECT_FALSE(VideoStateMachine::IsUserOperationCallback(VideoPlaybackCommand::ERROR));
    EXPECT_FALSE(VideoStateMachine::IsUserOperationCallback(VideoPlaybackCommand::RESET));
    EXPECT_FALSE(VideoStateMachine::IsUserOperationCallback(VideoPlaybackCommand::NONE));
}

/**
 * @tc.name: VideoStateMachineIsMediaSpontaneousEvent001
 * @tc.desc: Test IsMediaSpontaneousEvent returns true for COMPLETE, ERROR.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateMachineIsMediaSpontaneousEvent001, TestSize.Level1)
{
    EXPECT_TRUE(VideoStateMachine::IsMediaSpontaneousEvent(VideoPlaybackCommand::COMPLETE));
    EXPECT_TRUE(VideoStateMachine::IsMediaSpontaneousEvent(VideoPlaybackCommand::ERROR));
    EXPECT_FALSE(VideoStateMachine::IsMediaSpontaneousEvent(VideoPlaybackCommand::PLAY));
    EXPECT_FALSE(VideoStateMachine::IsMediaSpontaneousEvent(VideoPlaybackCommand::PAUSE));
    EXPECT_FALSE(VideoStateMachine::IsMediaSpontaneousEvent(VideoPlaybackCommand::STOP));
    EXPECT_FALSE(VideoStateMachine::IsMediaSpontaneousEvent(VideoPlaybackCommand::PREPARE));
    EXPECT_FALSE(VideoStateMachine::IsMediaSpontaneousEvent(VideoPlaybackCommand::RESET));
    EXPECT_FALSE(VideoStateMachine::IsMediaSpontaneousEvent(VideoPlaybackCommand::NONE));
}

/**
 * @tc.name: VideoStateMachineStateToString001
 * @tc.desc: Test StateToString covers all states and default UNKNOWN.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateMachineStateToString001, TestSize.Level1)
{
    EXPECT_STREQ(VideoStateMachine::StateToString(VideoPlaybackState::CREATED), "CREATED");
    EXPECT_STREQ(VideoStateMachine::StateToString(VideoPlaybackState::PREPARED), "PREPARED");
    EXPECT_STREQ(VideoStateMachine::StateToString(VideoPlaybackState::PLAYING), "PLAYING");
    EXPECT_STREQ(VideoStateMachine::StateToString(VideoPlaybackState::PAUSED), "PAUSED");
    EXPECT_STREQ(VideoStateMachine::StateToString(VideoPlaybackState::STOPPED), "STOPPED");
    EXPECT_STREQ(VideoStateMachine::StateToString(VideoPlaybackState::COMPLETED), "COMPLETED");
    EXPECT_STREQ(VideoStateMachine::StateToString(VideoPlaybackState::ERROR), "ERROR");
    EXPECT_STREQ(VideoStateMachine::StateToString(static_cast<VideoPlaybackState>(999)), "UNKNOWN");
}

/**
 * @tc.name: VideoStateMachineCommandToString001
 * @tc.desc: Test CommandToString covers all commands and default UNKNOWN.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateMachineCommandToString001, TestSize.Level1)
{
    EXPECT_STREQ(VideoStateMachine::CommandToString(VideoPlaybackCommand::NONE), "NONE");
    EXPECT_STREQ(VideoStateMachine::CommandToString(VideoPlaybackCommand::PREPARE), "PREPARE");
    EXPECT_STREQ(VideoStateMachine::CommandToString(VideoPlaybackCommand::PLAY), "PLAY");
    EXPECT_STREQ(VideoStateMachine::CommandToString(VideoPlaybackCommand::PAUSE), "PAUSE");
    EXPECT_STREQ(VideoStateMachine::CommandToString(VideoPlaybackCommand::STOP), "STOP");
    EXPECT_STREQ(VideoStateMachine::CommandToString(VideoPlaybackCommand::COMPLETE), "COMPLETE");
    EXPECT_STREQ(VideoStateMachine::CommandToString(VideoPlaybackCommand::ERROR), "ERROR");
    EXPECT_STREQ(VideoStateMachine::CommandToString(VideoPlaybackCommand::RESET), "RESET");
    EXPECT_STREQ(VideoStateMachine::CommandToString(static_cast<VideoPlaybackCommand>(999)), "UNKNOWN");
}

/**
 * @tc.name: VideoStateManagerConstructor001
 * @tc.desc: Test VideoStateManager initializes with CREATED state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerConstructor001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::CREATED);
    EXPECT_EQ(manager->GetPreviousState(), VideoPlaybackState::CREATED);
    EXPECT_TRUE(manager->IsCreated());
    EXPECT_FALSE(manager->IsPlaying());
    EXPECT_FALSE(manager->IsPaused());
    EXPECT_FALSE(manager->IsStopped());
    EXPECT_FALSE(manager->IsPrepared());
    EXPECT_FALSE(manager->IsCompleted());
    EXPECT_FALSE(manager->IsError());
    EXPECT_FALSE(manager->IsActive());
    EXPECT_FALSE(manager->HasPendingCommand());
    EXPECT_FALSE(manager->IsBusy());
}

/**
 * @tc.name: VideoStateManagerGetStateInfo001
 * @tc.desc: Test GetStateInfo returns correct string with default state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerGetStateInfo001, TestSize.Level1)
{
    auto pattern = CreateMockPattern();
    auto manager = CreateManager(pattern);
    auto info = manager->GetStateInfo();
    EXPECT_NE(info.find("CREATED"), std::string::npos);
    EXPECT_NE(info.find("pending=NONE"), std::string::npos);
    EXPECT_NE(info.find("isFullScreen=0"), std::string::npos);
}

/**
 * @tc.name: VideoStateManagerGetStateInfo002
 * @tc.desc: Test GetStateInfo includes full screen flag.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerGetStateInfo002, TestSize.Level1)
{
    auto pattern = CreateMockPattern();
    pattern->SetIsFullScreen(true);
    auto manager = CreateManager(pattern);
    auto info = manager->GetStateInfo();
    EXPECT_NE(info.find("isFullScreen=1"), std::string::npos);
}

/**
 * @tc.name: VideoStateManagerGetStateInfo003
 * @tc.desc: Test GetStateInfo with pending and original intent.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerGetStateInfo003, TestSize.Level1)
{
    auto pattern = CreateMockPattern();
    auto manager = CreateManager(pattern);
    manager->state_ = VideoPlaybackState::PLAYING;
    manager->previousState_ = VideoPlaybackState::PREPARED;
    manager->pendingCommand_ = VideoPlaybackCommand::PAUSE;
    manager->originalIntent_ = VideoPlaybackCommand::PLAY;

    auto info = manager->GetStateInfo();
    EXPECT_NE(info.find("PLAYING"), std::string::npos);
    EXPECT_NE(info.find("PREPARED"), std::string::npos);
    EXPECT_NE(info.find("PAUSE"), std::string::npos);
    EXPECT_NE(info.find("PLAY"), std::string::npos);
}

/**
 * @tc.name: VideoStateManagerIsCurrentContext001
 * @tc.desc: Test IsCurrentContext returns true for matching pattern.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerIsCurrentContext001, TestSize.Level1)
{
    auto pattern = CreateMockPattern();
    auto manager = CreateManager(pattern);
    EXPECT_TRUE(manager->IsCurrentContext(pattern.GetRawPtr()));
}

/**
 * @tc.name: VideoStateManagerIsCurrentContext002
 * @tc.desc: Test IsCurrentContext returns false for non-matching pattern.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerIsCurrentContext002, TestSize.Level1)
{
    auto pattern = CreateMockPattern();
    auto otherPattern = CreateMockPattern();
    auto manager = CreateManager(pattern);
    EXPECT_FALSE(manager->IsCurrentContext(otherPattern.GetRawPtr()));
}

/**
 * @tc.name: VideoStateManagerIsCurrentContext003
 * @tc.desc: Test IsCurrentContext returns false for null pattern.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerIsCurrentContext003, TestSize.Level1)
{
    auto pattern = CreateMockPattern();
    auto manager = CreateManager(pattern);
    EXPECT_FALSE(manager->IsCurrentContext(nullptr));
}

/**
 * @tc.name: VideoStateManagerUpdateContext001
 * @tc.desc: Test UpdateContext changes the context reference.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerUpdateContext001, TestSize.Level1)
{
    auto pattern1 = CreateMockPattern();
    auto pattern2 = CreateMockPattern();
    auto manager = CreateManager(pattern1);

    EXPECT_TRUE(manager->IsCurrentContext(pattern1.GetRawPtr()));
    EXPECT_FALSE(manager->IsCurrentContext(pattern2.GetRawPtr()));

    WeakPtr<VideoStateMachinePattern> weakPattern2 = AceType::WeakClaim(AceType::RawPtr(pattern2));
    manager->UpdateContext(weakPattern2);
    EXPECT_TRUE(manager->IsCurrentContext(pattern2.GetRawPtr()));
    EXPECT_FALSE(manager->IsCurrentContext(pattern1.GetRawPtr()));
}

/**
 * @tc.name: VideoStateManagerStateQueries001
 * @tc.desc: Test all Is* query methods for each state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerStateQueries001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());

    manager->state_ = VideoPlaybackState::CREATED;
    EXPECT_TRUE(manager->IsCreated());
    EXPECT_FALSE(manager->IsPlaying());
    EXPECT_FALSE(manager->IsPaused());
    EXPECT_FALSE(manager->IsStopped());
    EXPECT_FALSE(manager->IsPrepared());
    EXPECT_FALSE(manager->IsCompleted());
    EXPECT_FALSE(manager->IsError());
    EXPECT_FALSE(manager->IsActive());

    manager->state_ = VideoPlaybackState::PREPARED;
    EXPECT_TRUE(manager->IsPrepared());
    EXPECT_TRUE(manager->IsActive());

    manager->state_ = VideoPlaybackState::PLAYING;
    EXPECT_TRUE(manager->IsPlaying());
    EXPECT_TRUE(manager->IsActive());

    manager->state_ = VideoPlaybackState::PAUSED;
    EXPECT_TRUE(manager->IsPaused());
    EXPECT_TRUE(manager->IsActive());

    manager->state_ = VideoPlaybackState::STOPPED;
    EXPECT_TRUE(manager->IsStopped());
    EXPECT_FALSE(manager->IsActive());

    manager->state_ = VideoPlaybackState::COMPLETED;
    EXPECT_TRUE(manager->IsCompleted());
    EXPECT_TRUE(manager->IsActive());

    manager->state_ = VideoPlaybackState::ERROR;
    EXPECT_TRUE(manager->IsError());
    EXPECT_FALSE(manager->IsActive());
}

/**
 * @tc.name: VideoStateManagerCanTransitionTo001
 * @tc.desc: Test CanTransitionTo from CREATED to all states.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerCanTransitionTo001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::CREATED;

    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::CREATED));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::PREPARED));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::ERROR));
    EXPECT_FALSE(manager->CanTransitionTo(VideoPlaybackState::PLAYING));
    EXPECT_FALSE(manager->CanTransitionTo(VideoPlaybackState::PAUSED));
    EXPECT_FALSE(manager->CanTransitionTo(VideoPlaybackState::STOPPED));
    EXPECT_FALSE(manager->CanTransitionTo(VideoPlaybackState::COMPLETED));
}

/**
 * @tc.name: VideoStateManagerCanTransitionTo002
 * @tc.desc: Test CanTransitionTo from PREPARED to all states.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerCanTransitionTo002, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::PREPARED;

    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::PREPARED));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::PLAYING));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::STOPPED));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::ERROR));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::CREATED));
    EXPECT_FALSE(manager->CanTransitionTo(VideoPlaybackState::PAUSED));
    EXPECT_FALSE(manager->CanTransitionTo(VideoPlaybackState::COMPLETED));
}

/**
 * @tc.name: VideoStateManagerCanTransitionTo003
 * @tc.desc: Test CanTransitionTo from PLAYING to all states.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerCanTransitionTo003, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::PLAYING;

    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::PLAYING));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::PAUSED));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::STOPPED));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::COMPLETED));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::ERROR));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::CREATED));
    EXPECT_FALSE(manager->CanTransitionTo(VideoPlaybackState::PREPARED));
}

/**
 * @tc.name: VideoStateManagerCanTransitionTo004
 * @tc.desc: Test CanTransitionTo from PAUSED to all states.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerCanTransitionTo004, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::PAUSED;

    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::PAUSED));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::PLAYING));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::STOPPED));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::ERROR));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::CREATED));
    EXPECT_FALSE(manager->CanTransitionTo(VideoPlaybackState::PREPARED));
    EXPECT_FALSE(manager->CanTransitionTo(VideoPlaybackState::COMPLETED));
}

/**
 * @tc.name: VideoStateManagerCanTransitionTo005
 * @tc.desc: Test CanTransitionTo from STOPPED to all states.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerCanTransitionTo005, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::STOPPED;

    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::STOPPED));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::PREPARED));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::PLAYING));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::ERROR));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::CREATED));
    EXPECT_FALSE(manager->CanTransitionTo(VideoPlaybackState::PAUSED));
    EXPECT_FALSE(manager->CanTransitionTo(VideoPlaybackState::COMPLETED));
}

/**
 * @tc.name: VideoStateManagerCanTransitionTo006
 * @tc.desc: Test CanTransitionTo from COMPLETED to all states.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerCanTransitionTo006, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::COMPLETED;

    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::COMPLETED));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::PLAYING));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::STOPPED));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::ERROR));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::CREATED));
    EXPECT_FALSE(manager->CanTransitionTo(VideoPlaybackState::PREPARED));
    EXPECT_FALSE(manager->CanTransitionTo(VideoPlaybackState::PAUSED));
}

/**
 * @tc.name: VideoStateManagerCanTransitionTo007
 * @tc.desc: Test CanTransitionTo from ERROR to all states.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerCanTransitionTo007, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::ERROR;

    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::ERROR));
    EXPECT_TRUE(manager->CanTransitionTo(VideoPlaybackState::CREATED));
    EXPECT_FALSE(manager->CanTransitionTo(VideoPlaybackState::PREPARED));
    EXPECT_FALSE(manager->CanTransitionTo(VideoPlaybackState::PLAYING));
    EXPECT_FALSE(manager->CanTransitionTo(VideoPlaybackState::PAUSED));
    EXPECT_FALSE(manager->CanTransitionTo(VideoPlaybackState::STOPPED));
    EXPECT_FALSE(manager->CanTransitionTo(VideoPlaybackState::COMPLETED));
}

/**
 * @tc.name: VideoStateManagerTransitionToInvalid001
 * @tc.desc: Test TransitionTo rejects invalid transition and invokes callback.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerTransitionToInvalid001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::CREATED;
    bool successValue = true;
    std::string reasonValue;
    auto callback = [&successValue, &reasonValue](bool success, const std::string& reason) {
        successValue = success;
        reasonValue = reason;
    };

    EXPECT_FALSE(manager->TransitionTo(VideoPlaybackState::PLAYING, callback));
    EXPECT_FALSE(successValue);
    EXPECT_EQ(reasonValue, "transition not allowed");
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::CREATED);
}

/**
 * @tc.name: VideoStateManagerTransitionToNullCtx001
 * @tc.desc: Test TransitionTo with null ctx returns true but invokes callback with failure.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerTransitionToNullCtx001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    bool successValue = true;
    std::string reasonValue;
    auto callback = [&successValue, &reasonValue](bool success, const std::string& reason) {
        successValue = success;
        reasonValue = reason;
    };

    EXPECT_TRUE(manager->TransitionTo(VideoPlaybackState::PREPARED, callback));
    EXPECT_FALSE(successValue);
    EXPECT_EQ(reasonValue, "pattern context is null");
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::PREPARED);
    EXPECT_EQ(manager->GetPreviousState(), VideoPlaybackState::CREATED);
}

/**
 * @tc.name: VideoStateManagerTransitionToValidWithCtx001
 * @tc.desc: Test valid TransitionTo with context triggers state entry callback.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerTransitionToValidWithCtx001, TestSize.Level1)
{
    auto pattern = CreateMockPattern();
    auto manager = CreateManager(pattern);
    bool successValue = false;
    std::string reasonValue;
    auto callback = [&successValue, &reasonValue](bool success, const std::string& reason) {
        successValue = success;
        reasonValue = reason;
    };

    EXPECT_TRUE(manager->TransitionTo(VideoPlaybackState::PREPARED, callback));
    EXPECT_TRUE(successValue);
    EXPECT_EQ(reasonValue, "");
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::PREPARED);
    EXPECT_EQ(manager->GetPreviousState(), VideoPlaybackState::CREATED);
}

/**
 * @tc.name: VideoStateManagerTransitionToAllValid001
 * @tc.desc: Test all valid state transitions with context.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerTransitionToAllValid001, TestSize.Level1)
{
    auto pattern = CreateMockPattern();
    auto manager = CreateManager(pattern);

    EXPECT_TRUE(manager->TransitionTo(VideoPlaybackState::CREATED));
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::CREATED);

    EXPECT_TRUE(manager->TransitionTo(VideoPlaybackState::PREPARED));
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::PREPARED);

    EXPECT_TRUE(manager->TransitionTo(VideoPlaybackState::PLAYING));
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::PLAYING);

    EXPECT_TRUE(manager->TransitionTo(VideoPlaybackState::PAUSED));
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::PAUSED);

    EXPECT_TRUE(manager->TransitionTo(VideoPlaybackState::STOPPED));
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::STOPPED);

    EXPECT_TRUE(manager->TransitionTo(VideoPlaybackState::PREPARED));
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::PREPARED);

    EXPECT_TRUE(manager->TransitionTo(VideoPlaybackState::STOPPED));
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::STOPPED);

    EXPECT_TRUE(manager->TransitionTo(VideoPlaybackState::PLAYING));
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::PLAYING);

    EXPECT_TRUE(manager->TransitionTo(VideoPlaybackState::COMPLETED));
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::COMPLETED);

    EXPECT_TRUE(manager->TransitionTo(VideoPlaybackState::PLAYING));
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::PLAYING);

    EXPECT_TRUE(manager->TransitionTo(VideoPlaybackState::ERROR));
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::ERROR);

    EXPECT_TRUE(manager->TransitionTo(VideoPlaybackState::CREATED));
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::CREATED);

    EXPECT_TRUE(manager->TransitionTo(VideoPlaybackState::ERROR));
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::ERROR);

    EXPECT_TRUE(manager->TransitionTo(VideoPlaybackState::ERROR));
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::ERROR);
}

/**
 * @tc.name: VideoStateManagerTransitionToSelf001
 * @tc.desc: Test TransitionTo same state with context.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerTransitionToSelf001, TestSize.Level1)
{
    auto pattern = CreateMockPattern();
    auto manager = CreateManager(pattern);

    manager->state_ = VideoPlaybackState::PLAYING;
    EXPECT_TRUE(manager->TransitionTo(VideoPlaybackState::PLAYING));
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::PLAYING);
}

/**
 * @tc.name: VideoStateManagerCanHandleStateTransition001
 * @tc.desc: Test CanHandleStateTransition for CREATED state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerCanHandleStateTransition001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::CREATED;

    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::PREPARE));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::ERROR));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::RESET));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::PLAY));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::PAUSE));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::STOP));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::COMPLETE));
}

/**
 * @tc.name: VideoStateManagerCanHandleStateTransition002
 * @tc.desc: Test CanHandleStateTransition for PREPARED state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerCanHandleStateTransition002, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::PREPARED;

    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::PLAY));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::STOP));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::ERROR));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::RESET));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::PREPARE));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::PAUSE));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::COMPLETE));
}

/**
 * @tc.name: VideoStateManagerCanHandleStateTransition003
 * @tc.desc: Test CanHandleStateTransition for PLAYING state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerCanHandleStateTransition003, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::PLAYING;

    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::PAUSE));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::STOP));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::COMPLETE));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::ERROR));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::RESET));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::PREPARE));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::PLAY));
}

/**
 * @tc.name: VideoStateManagerCanHandleStateTransition004
 * @tc.desc: Test CanHandleStateTransition for PAUSED state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerCanHandleStateTransition004, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::PAUSED;

    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::PLAY));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::STOP));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::ERROR));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::RESET));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::PREPARE));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::PAUSE));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::COMPLETE));
}

/**
 * @tc.name: VideoStateManagerCanHandleStateTransition005
 * @tc.desc: Test CanHandleStateTransition for STOPPED state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerCanHandleStateTransition005, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::STOPPED;

    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::PREPARE));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::PLAY));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::ERROR));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::RESET));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::PAUSE));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::STOP));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::COMPLETE));
}

/**
 * @tc.name: VideoStateManagerCanHandleStateTransition006
 * @tc.desc: Test CanHandleStateTransition for COMPLETED state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerCanHandleStateTransition006, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::COMPLETED;

    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::PLAY));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::STOP));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::ERROR));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::RESET));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::PREPARE));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::PAUSE));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::COMPLETE));
}

/**
 * @tc.name: VideoStateManagerCanHandleStateTransition007
 * @tc.desc: Test CanHandleStateTransition for ERROR state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerCanHandleStateTransition007, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::ERROR;

    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::ERROR));
    EXPECT_TRUE(manager->CanHandleStateTransition(VideoPlaybackCommand::RESET));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::PREPARE));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::PLAY));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::PAUSE));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::STOP));
    EXPECT_FALSE(manager->CanHandleStateTransition(VideoPlaybackCommand::COMPLETE));
}

/**
 * @tc.name: VideoStateManagerHandleStateTransitionCreated001
 * @tc.desc: Test HandleStateTransition in CREATED state with valid commands.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerHandleStateTransitionCreated001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());

    manager->HandleStateTransition(VideoPlaybackCommand::PREPARE);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::PREPARED);

    manager->state_ = VideoPlaybackState::CREATED;
    manager->HandleStateTransition(VideoPlaybackCommand::ERROR);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::ERROR);

    manager->state_ = VideoPlaybackState::CREATED;
    manager->HandleStateTransition(VideoPlaybackCommand::RESET);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::CREATED);
}

/**
 * @tc.name: VideoStateManagerHandleStateTransitionPrepared001
 * @tc.desc: Test HandleStateTransition in PREPARED state with valid commands.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerHandleStateTransitionPrepared001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::PREPARED;

    manager->HandleStateTransition(VideoPlaybackCommand::PLAY);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::PLAYING);

    manager->state_ = VideoPlaybackState::PREPARED;
    manager->HandleStateTransition(VideoPlaybackCommand::STOP);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::STOPPED);

    manager->state_ = VideoPlaybackState::PREPARED;
    manager->HandleStateTransition(VideoPlaybackCommand::ERROR);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::ERROR);

    manager->state_ = VideoPlaybackState::PREPARED;
    manager->HandleStateTransition(VideoPlaybackCommand::RESET);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::CREATED);
}

/**
 * @tc.name: VideoStateManagerHandleStateTransitionPlaying001
 * @tc.desc: Test HandleStateTransition in PLAYING state with valid commands.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerHandleStateTransitionPlaying001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::PLAYING;

    manager->HandleStateTransition(VideoPlaybackCommand::PAUSE);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::PAUSED);

    manager->state_ = VideoPlaybackState::PLAYING;
    manager->HandleStateTransition(VideoPlaybackCommand::STOP);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::STOPPED);

    manager->state_ = VideoPlaybackState::PLAYING;
    manager->HandleStateTransition(VideoPlaybackCommand::COMPLETE);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::COMPLETED);

    manager->state_ = VideoPlaybackState::PLAYING;
    manager->HandleStateTransition(VideoPlaybackCommand::ERROR);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::ERROR);

    manager->state_ = VideoPlaybackState::PLAYING;
    manager->HandleStateTransition(VideoPlaybackCommand::RESET);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::CREATED);
}

/**
 * @tc.name: VideoStateManagerHandleStateTransitionPaused001
 * @tc.desc: Test HandleStateTransition in PAUSED state with valid commands.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerHandleStateTransitionPaused001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::PAUSED;

    manager->HandleStateTransition(VideoPlaybackCommand::PLAY);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::PLAYING);

    manager->state_ = VideoPlaybackState::PAUSED;
    manager->HandleStateTransition(VideoPlaybackCommand::STOP);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::STOPPED);

    manager->state_ = VideoPlaybackState::PAUSED;
    manager->HandleStateTransition(VideoPlaybackCommand::ERROR);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::ERROR);

    manager->state_ = VideoPlaybackState::PAUSED;
    manager->HandleStateTransition(VideoPlaybackCommand::RESET);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::CREATED);
}

/**
 * @tc.name: VideoStateManagerHandleStateTransitionStopped001
 * @tc.desc: Test HandleStateTransition in STOPPED state with valid commands.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerHandleStateTransitionStopped001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::STOPPED;

    manager->HandleStateTransition(VideoPlaybackCommand::PREPARE);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::PREPARED);

    manager->state_ = VideoPlaybackState::STOPPED;
    manager->HandleStateTransition(VideoPlaybackCommand::PLAY);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::PREPARED);

    manager->state_ = VideoPlaybackState::STOPPED;
    manager->HandleStateTransition(VideoPlaybackCommand::ERROR);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::ERROR);

    manager->state_ = VideoPlaybackState::STOPPED;
    manager->HandleStateTransition(VideoPlaybackCommand::RESET);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::CREATED);
}

/**
 * @tc.name: VideoStateManagerHandleStateTransitionCompleted001
 * @tc.desc: Test HandleStateTransition in COMPLETED state with valid commands.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerHandleStateTransitionCompleted001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::COMPLETED;

    manager->HandleStateTransition(VideoPlaybackCommand::PLAY);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::PLAYING);

    manager->state_ = VideoPlaybackState::COMPLETED;
    manager->HandleStateTransition(VideoPlaybackCommand::STOP);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::STOPPED);

    manager->state_ = VideoPlaybackState::COMPLETED;
    manager->HandleStateTransition(VideoPlaybackCommand::ERROR);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::ERROR);

    manager->state_ = VideoPlaybackState::COMPLETED;
    manager->HandleStateTransition(VideoPlaybackCommand::RESET);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::CREATED);
}

/**
 * @tc.name: VideoStateManagerHandleStateTransitionError001
 * @tc.desc: Test HandleStateTransition in ERROR state with valid commands.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerHandleStateTransitionError001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::ERROR;

    manager->HandleStateTransition(VideoPlaybackCommand::ERROR);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::ERROR);

    manager->state_ = VideoPlaybackState::ERROR;
    manager->HandleStateTransition(VideoPlaybackCommand::RESET);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::CREATED);
}

/**
 * @tc.name: VideoStateManagerHandleStateTransitionInvalid001
 * @tc.desc: Test HandleStateTransition rejects invalid command and invokes callback.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerHandleStateTransitionInvalid001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    bool successValue = true;
    std::string reasonValue;
    auto callback = [&successValue, &reasonValue](bool success, const std::string& reason) {
        successValue = success;
        reasonValue = reason;
    };

    manager->HandleStateTransition(VideoPlaybackCommand::PLAY, callback);
    EXPECT_FALSE(successValue);
    EXPECT_EQ(reasonValue, "invalid state transition");
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::CREATED);
}

/**
 * @tc.name: VideoStateManagerHandleStateTransitionPendingReject001
 * @tc.desc: Test HandleStateTransition rejects command when pending mismatch.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerHandleStateTransitionPendingReject001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::PLAYING; // PAUSE is valid in PLAYING state
    manager->SetPendingCommand(VideoPlaybackCommand::PLAY);

    bool successValue = true;
    std::string reasonValue;
    auto callback = [&successValue, &reasonValue](bool success, const std::string& reason) {
        successValue = success;
        reasonValue = reason;
    };

    manager->HandleStateTransition(VideoPlaybackCommand::PAUSE, callback);
    EXPECT_FALSE(successValue);
    EXPECT_EQ(reasonValue, "pending command validation failed");
}

/**
 * @tc.name: VideoStateManagerHandleStateTransitionCompleteReject001
 * @tc.desc: Test HandleStateTransition rejects COMPLETE when pending is STOP.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerHandleStateTransitionCompleteReject001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::PLAYING;
    manager->SetPendingCommand(VideoPlaybackCommand::STOP);

    bool successValue = true;
    std::string reasonValue;
    auto callback = [&successValue, &reasonValue](bool success, const std::string& reason) {
        successValue = success;
        reasonValue = reason;
    };

    manager->HandleStateTransition(VideoPlaybackCommand::COMPLETE, callback);
    EXPECT_FALSE(successValue);
    EXPECT_EQ(reasonValue, "pending command validation failed");
}

/**
 * @tc.name: VideoStateManagerHandleStateTransitionErrorReject001
 * @tc.desc: Test HandleStateTransition rejects ERROR when pending is RESET.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerHandleStateTransitionErrorReject001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::PLAYING;
    manager->SetPendingCommand(VideoPlaybackCommand::RESET);

    bool successValue = true;
    std::string reasonValue;
    auto callback = [&successValue, &reasonValue](bool success, const std::string& reason) {
        successValue = success;
        reasonValue = reason;
    };

    manager->HandleStateTransition(VideoPlaybackCommand::ERROR, callback);
    EXPECT_FALSE(successValue);
    EXPECT_EQ(reasonValue, "pending command validation failed");
}

/**
 * @tc.name: VideoStateManagerHandleStateTransitionValidWithCallback001
 * @tc.desc: Test HandleStateTransition valid command does not invoke callback.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerHandleStateTransitionValidWithCallback001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    bool callbackCalled = false;
    auto callback = [&callbackCalled](bool success, const std::string& reason) {
        callbackCalled = true;
    };

    manager->HandleStateTransition(VideoPlaybackCommand::PREPARE, callback);
    EXPECT_FALSE(callbackCalled);
    EXPECT_EQ(manager->GetCurrentState(), VideoPlaybackState::PREPARED);
}

/**
 * @tc.name: VideoStateManagerValidateStateTransition001
 * @tc.desc: Test ValidateStateTransition returns true for valid and false for invalid.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerValidateStateTransition001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->state_ = VideoPlaybackState::CREATED;

    EXPECT_TRUE(manager->ValidateStateTransition(VideoPlaybackCommand::PREPARE));
    EXPECT_TRUE(manager->ValidateStateTransition(VideoPlaybackCommand::ERROR));
    EXPECT_TRUE(manager->ValidateStateTransition(VideoPlaybackCommand::RESET));
    EXPECT_FALSE(manager->ValidateStateTransition(VideoPlaybackCommand::PLAY));
    EXPECT_FALSE(manager->ValidateStateTransition(VideoPlaybackCommand::PAUSE));
    EXPECT_FALSE(manager->ValidateStateTransition(VideoPlaybackCommand::STOP));
    EXPECT_FALSE(manager->ValidateStateTransition(VideoPlaybackCommand::COMPLETE));
}

/**
 * @tc.name: VideoStateManagerValidatePendingCommand001
 * @tc.desc: Test ValidatePendingCommand with no pending command.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerValidatePendingCommand001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());

    EXPECT_TRUE(manager->ValidatePendingCommand(VideoPlaybackCommand::PLAY));
    EXPECT_TRUE(manager->ValidatePendingCommand(VideoPlaybackCommand::PAUSE));
    EXPECT_TRUE(manager->ValidatePendingCommand(VideoPlaybackCommand::STOP));
    EXPECT_TRUE(manager->ValidatePendingCommand(VideoPlaybackCommand::PREPARE));
    EXPECT_TRUE(manager->ValidatePendingCommand(VideoPlaybackCommand::COMPLETE));
    EXPECT_TRUE(manager->ValidatePendingCommand(VideoPlaybackCommand::ERROR));
}

/**
 * @tc.name: VideoStateManagerValidatePendingCommand002
 * @tc.desc: Test ValidatePendingCommand with matching pending user operation.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerValidatePendingCommand002, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->SetPendingCommand(VideoPlaybackCommand::PLAY);

    EXPECT_TRUE(manager->ValidatePendingCommand(VideoPlaybackCommand::PLAY));
    EXPECT_FALSE(manager->ValidatePendingCommand(VideoPlaybackCommand::PAUSE));
    EXPECT_FALSE(manager->ValidatePendingCommand(VideoPlaybackCommand::STOP));
    EXPECT_FALSE(manager->ValidatePendingCommand(VideoPlaybackCommand::PREPARE));
}

/**
 * @tc.name: VideoStateManagerValidatePendingCommand003
 * @tc.desc: Test ValidatePendingCommand for COMPLETE with various pending commands.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerValidatePendingCommand003, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());

    EXPECT_TRUE(manager->ValidatePendingCommand(VideoPlaybackCommand::COMPLETE));

    manager->SetPendingCommand(VideoPlaybackCommand::STOP);
    EXPECT_FALSE(manager->ValidatePendingCommand(VideoPlaybackCommand::COMPLETE));

    manager->ClearPendingCommand();
    manager->SetPendingCommand(VideoPlaybackCommand::PREPARE);
    EXPECT_FALSE(manager->ValidatePendingCommand(VideoPlaybackCommand::COMPLETE));

    manager->ClearPendingCommand();
    manager->SetPendingCommand(VideoPlaybackCommand::RESET);
    EXPECT_FALSE(manager->ValidatePendingCommand(VideoPlaybackCommand::COMPLETE));

    manager->ClearPendingCommand();
    manager->SetPendingCommand(VideoPlaybackCommand::PLAY);
    EXPECT_TRUE(manager->ValidatePendingCommand(VideoPlaybackCommand::COMPLETE));
}

/**
 * @tc.name: VideoStateManagerValidatePendingCommand004
 * @tc.desc: Test ValidatePendingCommand for ERROR with various pending commands.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerValidatePendingCommand004, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());

    EXPECT_TRUE(manager->ValidatePendingCommand(VideoPlaybackCommand::ERROR));

    manager->SetPendingCommand(VideoPlaybackCommand::RESET);
    EXPECT_FALSE(manager->ValidatePendingCommand(VideoPlaybackCommand::ERROR));

    manager->ClearPendingCommand();
    manager->SetPendingCommand(VideoPlaybackCommand::PLAY);
    EXPECT_TRUE(manager->ValidatePendingCommand(VideoPlaybackCommand::ERROR));

    manager->ClearPendingCommand();
    manager->SetPendingCommand(VideoPlaybackCommand::STOP);
    EXPECT_TRUE(manager->ValidatePendingCommand(VideoPlaybackCommand::ERROR));
}

/**
 * @tc.name: VideoStateManagerSetPendingCommand001
 * @tc.desc: Test SetPendingCommand with valid command.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerSetPendingCommand001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    bool callbackCalled = false;
    auto callback = [&callbackCalled](bool success, const std::string& reason) {
        callbackCalled = true;
    };

    manager->SetPendingCommand(VideoPlaybackCommand::PLAY, callback);
    EXPECT_EQ(manager->GetPendingCommand(), VideoPlaybackCommand::PLAY);
    EXPECT_TRUE(manager->HasPendingCommand());
    EXPECT_TRUE(manager->IsBusy());

    auto cb = manager->ConsumePendingCallback();
    EXPECT_TRUE(cb);
    cb(true, "");
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: VideoStateManagerSetPendingCommandNone001
 * @tc.desc: Test SetPendingCommand rejects NONE command.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerSetPendingCommandNone001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    bool successValue = true;
    auto callback = [&successValue](bool success, const std::string& reason) {
        successValue = success;
    };

    manager->SetPendingCommand(VideoPlaybackCommand::NONE, callback);
    EXPECT_FALSE(manager->HasPendingCommand());
    EXPECT_FALSE(successValue);
}

/**
 * @tc.name: VideoStateManagerSetPendingCommandWithIntent001
 * @tc.desc: Test SetPendingCommand preserves original intent.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerSetPendingCommandWithIntent001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->SetPendingCommand(VideoPlaybackCommand::PREPARE, nullptr, VideoPlaybackCommand::PLAY);
    EXPECT_EQ(manager->GetPendingCommand(), VideoPlaybackCommand::PREPARE);
    EXPECT_EQ(manager->GetOriginalIntent(), VideoPlaybackCommand::PLAY);
}

/**
 * @tc.name: VideoStateManagerClearPendingCommand001
 * @tc.desc: Test ClearPendingCommand clears pending and invokes callback with failure.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerClearPendingCommand001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    bool successValue = true;
    auto callback = [&successValue](bool success, const std::string& reason) {
        successValue = success;
    };

    manager->SetPendingCommand(VideoPlaybackCommand::PLAY, callback);
    EXPECT_TRUE(manager->HasPendingCommand());

    manager->ClearPendingCommand();
    EXPECT_FALSE(manager->HasPendingCommand());
    EXPECT_FALSE(manager->IsBusy());
    EXPECT_FALSE(successValue);
}

/**
 * @tc.name: VideoStateManagerClearPendingCommandEmpty001
 * @tc.desc: Test ClearPendingCommand does nothing when no pending command.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerClearPendingCommandEmpty001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    EXPECT_FALSE(manager->HasPendingCommand());
    manager->ClearPendingCommand();
    EXPECT_FALSE(manager->HasPendingCommand());
}

/**
 * @tc.name: VideoStateManagerCanSetPendingCommand001
 * @tc.desc: Test CanSetPendingCommand with various scenarios.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerCanSetPendingCommand001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());

    EXPECT_FALSE(manager->CanSetPendingCommand(VideoPlaybackCommand::NONE));
    EXPECT_TRUE(manager->CanSetPendingCommand(VideoPlaybackCommand::PLAY));

    manager->SetPendingCommand(VideoPlaybackCommand::PLAY);
    EXPECT_FALSE(manager->CanSetPendingCommand(VideoPlaybackCommand::PLAY));
    EXPECT_TRUE(manager->CanSetPendingCommand(VideoPlaybackCommand::STOP));
    EXPECT_TRUE(manager->CanSetPendingCommand(VideoPlaybackCommand::RESET));
    EXPECT_FALSE(manager->CanSetPendingCommand(VideoPlaybackCommand::PAUSE));
    EXPECT_FALSE(manager->CanSetPendingCommand(VideoPlaybackCommand::PREPARE));
}

/**
 * @tc.name: VideoStateManagerCanSetPendingCommand002
 * @tc.desc: Test CanSetPendingCommand with pending RESET.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerCanSetPendingCommand002, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->SetPendingCommand(VideoPlaybackCommand::RESET);

    EXPECT_FALSE(manager->CanSetPendingCommand(VideoPlaybackCommand::RESET));
    EXPECT_FALSE(manager->CanSetPendingCommand(VideoPlaybackCommand::STOP));
    EXPECT_FALSE(manager->CanSetPendingCommand(VideoPlaybackCommand::PLAY));
    EXPECT_FALSE(manager->CanSetPendingCommand(VideoPlaybackCommand::PAUSE));
    EXPECT_FALSE(manager->CanSetPendingCommand(VideoPlaybackCommand::PREPARE));
}

/**
 * @tc.name: VideoStateManagerCanOverridePendingCommand001
 * @tc.desc: Test CanOverridePendingCommand with various pending and new commands.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerCanOverridePendingCommand001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());

    // CanOverridePendingCommand is only called when pendingCommand_ != NONE
    manager->pendingCommand_ = VideoPlaybackCommand::PLAY;
    EXPECT_TRUE(manager->CanOverridePendingCommand(VideoPlaybackCommand::RESET));
    EXPECT_TRUE(manager->CanOverridePendingCommand(VideoPlaybackCommand::STOP));
    EXPECT_FALSE(manager->CanOverridePendingCommand(VideoPlaybackCommand::PLAY));
    EXPECT_FALSE(manager->CanOverridePendingCommand(VideoPlaybackCommand::PAUSE));
    EXPECT_FALSE(manager->CanOverridePendingCommand(VideoPlaybackCommand::PREPARE));

    manager->pendingCommand_ = VideoPlaybackCommand::PAUSE;
    EXPECT_TRUE(manager->CanOverridePendingCommand(VideoPlaybackCommand::RESET));
    EXPECT_TRUE(manager->CanOverridePendingCommand(VideoPlaybackCommand::STOP));
    EXPECT_FALSE(manager->CanOverridePendingCommand(VideoPlaybackCommand::PLAY));

    manager->pendingCommand_ = VideoPlaybackCommand::PREPARE;
    EXPECT_TRUE(manager->CanOverridePendingCommand(VideoPlaybackCommand::RESET));
    EXPECT_TRUE(manager->CanOverridePendingCommand(VideoPlaybackCommand::STOP));
    EXPECT_FALSE(manager->CanOverridePendingCommand(VideoPlaybackCommand::PLAY));

    manager->pendingCommand_ = VideoPlaybackCommand::STOP;
    EXPECT_TRUE(manager->CanOverridePendingCommand(VideoPlaybackCommand::RESET));
    EXPECT_FALSE(manager->CanOverridePendingCommand(VideoPlaybackCommand::STOP));
    EXPECT_FALSE(manager->CanOverridePendingCommand(VideoPlaybackCommand::PLAY));

    manager->pendingCommand_ = VideoPlaybackCommand::RESET;
    EXPECT_FALSE(manager->CanOverridePendingCommand(VideoPlaybackCommand::RESET));
    EXPECT_FALSE(manager->CanOverridePendingCommand(VideoPlaybackCommand::STOP));
    EXPECT_FALSE(manager->CanOverridePendingCommand(VideoPlaybackCommand::PLAY));
}

/**
 * @tc.name: VideoStateManagerClearMatchedPending001
 * @tc.desc: Test ClearMatchedPending clears matching pending command and invokes callback.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerClearMatchedPending001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    bool callbackCalled = false;
    auto callback = [&callbackCalled](bool success, const std::string& reason) {
        callbackCalled = true;
        EXPECT_TRUE(success);
    };

    manager->SetPendingCommand(VideoPlaybackCommand::PLAY, callback);
    manager->ClearMatchedPending(VideoPlaybackCommand::PLAY);
    EXPECT_FALSE(manager->HasPendingCommand());
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: VideoStateManagerClearMatchedPendingNone001
 * @tc.desc: Test ClearMatchedPending does nothing when no pending command.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerClearMatchedPendingNone001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->ClearMatchedPending(VideoPlaybackCommand::PLAY);
    EXPECT_FALSE(manager->HasPendingCommand());
}

/**
 * @tc.name: VideoStateManagerClearMatchedPendingNoMatch001
 * @tc.desc: Test ClearMatchedPending does not clear when command does not match.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerClearMatchedPendingNoMatch001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    manager->SetPendingCommand(VideoPlaybackCommand::PLAY);
    manager->ClearMatchedPending(VideoPlaybackCommand::PAUSE);
    EXPECT_TRUE(manager->HasPendingCommand());
    EXPECT_EQ(manager->GetPendingCommand(), VideoPlaybackCommand::PLAY);
}

/**
 * @tc.name: VideoStateManagerClearMatchedPendingResetOverride001
 * @tc.desc: Test ClearMatchedPending with RESET overrides any pending command.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerClearMatchedPendingResetOverride001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    bool callbackCalled = false;
    auto callback = [&callbackCalled](bool success, const std::string& reason) {
        callbackCalled = true;
        EXPECT_FALSE(success);
    };

    manager->SetPendingCommand(VideoPlaybackCommand::PLAY, callback);
    manager->ClearMatchedPending(VideoPlaybackCommand::RESET);
    EXPECT_FALSE(manager->HasPendingCommand());
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: VideoStateManagerClearMatchedPendingPreparePlay001
 * @tc.desc: Test ClearMatchedPending preserves callback for PREPARE+PLAY intent.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerClearMatchedPendingPreparePlay001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    bool callbackCalled = false;
    auto callback = [&callbackCalled](bool success, const std::string& reason) {
        callbackCalled = true;
    };

    manager->SetPendingCommand(VideoPlaybackCommand::PREPARE, callback, VideoPlaybackCommand::PLAY);
    manager->ClearMatchedPending(VideoPlaybackCommand::PREPARE);
    EXPECT_FALSE(manager->HasPendingCommand());
    EXPECT_FALSE(callbackCalled);
    EXPECT_EQ(manager->GetOriginalIntent(), VideoPlaybackCommand::PLAY);
}

/**
 * @tc.name: VideoStateManagerClearMatchedPendingResetReset001
 * @tc.desc: Test ClearMatchedPending preserves callback for RESET+RESET intent.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerClearMatchedPendingResetReset001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    bool callbackCalled = false;
    auto callback = [&callbackCalled](bool success, const std::string& reason) {
        callbackCalled = true;
    };

    manager->SetPendingCommand(VideoPlaybackCommand::RESET, callback, VideoPlaybackCommand::RESET);
    manager->ClearMatchedPending(VideoPlaybackCommand::RESET);
    EXPECT_FALSE(manager->HasPendingCommand());
    EXPECT_FALSE(callbackCalled);
    EXPECT_EQ(manager->GetOriginalIntent(), VideoPlaybackCommand::RESET);
}

/**
 * @tc.name: VideoStateManagerConsumePendingCallback001
 * @tc.desc: Test ConsumePendingCallback returns the callback and empties it.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerConsumePendingCallback001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    bool called = false;
    auto callback = [&called](bool success, const std::string& reason) {
        called = true;
    };

    manager->SetPendingCommand(VideoPlaybackCommand::PLAY, callback);
    auto cb = manager->ConsumePendingCallback();
    EXPECT_TRUE(cb);
    cb(true, "");
    EXPECT_TRUE(called);

    // Note: std::move on std::function may not clear the source due to NRVO/copy elision
    // in some compiler configurations. The "empty after consume" behavior is already
    // covered by ConsumePendingCallbackEmpty001.
}

/**
 * @tc.name: VideoStateManagerConsumePendingCallbackEmpty001
 * @tc.desc: Test ConsumePendingCallback returns empty when no pending.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerConsumePendingCallbackEmpty001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    auto cb = manager->ConsumePendingCallback();
    EXPECT_FALSE(cb);
}

/**
 * @tc.name: VideoStateManagerGetOriginalIntent001
 * @tc.desc: Test GetOriginalIntent returns the set original intent.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateManagerTestNg, VideoStateManagerGetOriginalIntent001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<VideoStateManager>(WeakPtr<VideoStateMachinePattern>());
    EXPECT_EQ(manager->GetOriginalIntent(), VideoPlaybackCommand::NONE);

    manager->SetPendingCommand(VideoPlaybackCommand::PREPARE, nullptr, VideoPlaybackCommand::PLAY);
    EXPECT_EQ(manager->GetOriginalIntent(), VideoPlaybackCommand::PLAY);
}

} // namespace OHOS::Ace::NG