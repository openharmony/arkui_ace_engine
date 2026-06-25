/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "video_state_machine_pattern_test_common.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

/**
 * @tc.name: VideoStateMachinePatternOnPreparedStateEntered003
 * @tc.desc: Test OnPreparedStateEntered autoPlay branch triggers Start.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnPreparedStateEntered003, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, GetDuration(_)).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->autoPlay_ = true;
    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;
    pattern->stateManager_->originalIntent_ = VideoPlaybackCommand::NONE;
    pattern->stateManager_->previousState_ = VideoPlaybackState::CREATED;
    pattern->stateManager_->ClearPendingCommand();

    pattern->OnPreparedStateEntered();
    EXPECT_EQ(pattern->stateManager_->GetPendingCommand(), VideoPlaybackCommand::PLAY);
}

/**
 * @tc.name: VideoStateMachinePatternOnPreparedStateEntered004
 * @tc.desc: Test OnPreparedStateEntered originalIntent=PLAY branch.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnPreparedStateEntered004, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, GetDuration(_)).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;
    pattern->stateManager_->originalIntent_ = VideoPlaybackCommand::PLAY;
    pattern->stateManager_->SetPendingCommand(VideoPlaybackCommand::PREPARE, nullptr, VideoPlaybackCommand::PLAY);

    pattern->OnPreparedStateEntered();
    EXPECT_EQ(pattern->stateManager_->GetPendingCommand(), VideoPlaybackCommand::PLAY);
}

/**
 * @tc.name: VideoStateMachinePatternOnPreparedStateEntered005
 * @tc.desc: Test OnPreparedStateEntered previousState=STOPPED branch triggers Start.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnPreparedStateEntered005, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, GetDuration(_)).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;
    pattern->stateManager_->originalIntent_ = VideoPlaybackCommand::NONE;
    pattern->stateManager_->previousState_ = VideoPlaybackState::STOPPED;
    pattern->stateManager_->ClearPendingCommand();

    pattern->OnPreparedStateEntered();
    EXPECT_EQ(pattern->stateManager_->GetPendingCommand(), VideoPlaybackCommand::PLAY);
}

/**
 * @tc.name: VideoStateMachinePatternOnPreparedStateEntered006
 * @tc.desc: Test OnPreparedStateEntered does not update video size when showFirstFrame is false.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnPreparedStateEntered006, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, GetDuration(_)).WillRepeatedly(Return(0));
    mockMediaPlayer->videoWidth_ = 1280;
    mockMediaPlayer->videoHeight_ = 720;
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->showFirstFrame_ = false;
    videoLayoutProperty->ResetVideoSize();
    pattern->OnPreparedStateEntered();
    EXPECT_FALSE(videoLayoutProperty->HasVideoSize());
}

/**
 * @tc.name: VideoStateMachinePatternOnPlayerStatus003
 * @tc.desc: Test OnPlayerStatus handles PLAYBACK_COMPLETE.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnPlayerStatus003, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;
    pattern->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE);
    EXPECT_EQ(pattern->currentPlaybackStatus_, PlaybackStatus::PLAYBACK_COMPLETE);
    EXPECT_TRUE(pattern->stateManager_->IsCompleted());
}

/**
 * @tc.name: VideoStateMachinePatternOnPlayerStatus004
 * @tc.desc: Test OnPlayerStatus handles various statuses.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnPlayerStatus004, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->OnPlayerStatus(PlaybackStatus::IDLE);
    EXPECT_EQ(pattern->currentPlaybackStatus_, PlaybackStatus::IDLE);

    pattern->OnPlayerStatus(PlaybackStatus::INITIALIZED);
    EXPECT_EQ(pattern->currentPlaybackStatus_, PlaybackStatus::INITIALIZED);

    pattern->OnPlayerStatus(PlaybackStatus::ERROR);
    EXPECT_EQ(pattern->currentPlaybackStatus_, PlaybackStatus::ERROR);

    pattern->OnPlayerStatus(PlaybackStatus::NONE);
    EXPECT_EQ(pattern->currentPlaybackStatus_, PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoStateMachinePatternOnKeyEvent002
 * @tc.desc: Test OnKeyEvent handles KEY_DPAD_LEFT.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnKeyEvent002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableShortcutKey_ = true;
    pattern->currentPos_ = 50;
    pattern->duration_ = 100;

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_DPAD_LEFT;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_DPAD_LEFT);

    EXPECT_TRUE(pattern->OnKeyEvent(keyEvent));
}

/**
 * @tc.name: VideoStateMachinePatternOnKeyEvent003
 * @tc.desc: Test OnKeyEvent handles KEY_DPAD_RIGHT.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnKeyEvent003, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableShortcutKey_ = true;
    pattern->currentPos_ = 50;
    pattern->duration_ = 100;

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_DPAD_RIGHT);

    EXPECT_TRUE(pattern->OnKeyEvent(keyEvent));
}

/**
 * @tc.name: VideoStateMachinePatternOnKeyEvent004
 * @tc.desc: Test OnKeyEvent handles KEY_DPAD_UP.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnKeyEvent004, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableShortcutKey_ = true;
    pattern->currentVolume_ = 0.5f;

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_DPAD_UP;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_DPAD_UP);

    EXPECT_TRUE(pattern->OnKeyEvent(keyEvent));
}

/**
 * @tc.name: VideoStateMachinePatternOnKeyEvent005
 * @tc.desc: Test OnKeyEvent handles KEY_DPAD_DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnKeyEvent005, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableShortcutKey_ = true;
    pattern->currentVolume_ = 0.5f;

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_DPAD_DOWN);

    EXPECT_TRUE(pattern->OnKeyEvent(keyEvent));
}

/**
 * @tc.name: VideoStateMachinePatternOnKeyEvent006
 * @tc.desc: Test OnKeyEvent returns false when shortcut key is disabled.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnKeyEvent006, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableShortcutKey_ = false;

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_SPACE;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_SPACE);

    EXPECT_FALSE(pattern->OnKeyEvent(keyEvent));
}

/**
 * @tc.name: VideoStateMachinePatternOnKeyEvent007
 * @tc.desc: Test OnKeyEvent returns false when action is not DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnKeyEvent007, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableShortcutKey_ = true;

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_SPACE;
    keyEvent.action = KeyAction::UP;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_SPACE);

    EXPECT_FALSE(pattern->OnKeyEvent(keyEvent));
}

/**
 * @tc.name: VideoStateMachinePatternOnVisibleChange002
 * @tc.desc: Test OnVisibleChange with visible=false triggers hiddenChangeEvent.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnVisibleChange002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    bool called = false;
    bool hiddenValue = true;
    pattern->SetHiddenChangeEvent([&called, &hiddenValue](bool hidden) {
        called = true;
        hiddenValue = hidden;
    });

    pattern->OnVisibleChange(false);
    EXPECT_TRUE(called);
    EXPECT_TRUE(hiddenValue);
}

/**
 * @tc.name: VideoStateMachinePatternHiddenChange002
 * @tc.desc: Test HiddenChange resumes playback when hidden=false and pastPlayingStatus=true.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternHiddenChange002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->pastPlayingStatus_ = true;
    pattern->HiddenChange(false);
    EXPECT_FALSE(pattern->pastPlayingStatus_);
}

/**
 * @tc.name: VideoStateMachinePatternHiddenChange003
 * @tc.desc: Test HiddenChange does nothing when hidden=true but not playing.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternHiddenChange003, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->stateManager_->state_ = VideoPlaybackState::PAUSED;
    pattern->pastPlayingStatus_ = false;
    pattern->HiddenChange(true);
    EXPECT_FALSE(pattern->pastPlayingStatus_);
}

/**
 * @tc.name: VideoStateMachinePatternOnError003
 * @tc.desc: Test OnError with empty string sets default error message.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnError003, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->OnError("");
    EXPECT_EQ(pattern->lastErrorCode_, ERROR_CODE_VIDEO_SOURCE_INVALID);
    EXPECT_EQ(pattern->lastErrorMessage_, "Unknown error");
    EXPECT_TRUE(pattern->stateManager_->IsError());
}

/**
 * @tc.name: VideoStateMachinePatternOnError004
 * @tc.desc: Test OnError(int32_t, std::string) with specific code.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnError004, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->OnError(500, "Internal Server Error");
    EXPECT_EQ(pattern->lastErrorCode_, 500);
    EXPECT_EQ(pattern->lastErrorMessage_, "Internal Server Error");
    EXPECT_TRUE(pattern->stateManager_->IsError());
}

/**
 * @tc.name: VideoStateMachinePatternToJsonValue002
 * @tc.desc: Test ToJsonValue serializes enableShortcutKey and surfaceBackgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternToJsonValue002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableShortcutKey_ = true;
    pattern->SetSurfaceBackgroundColor(Color::RED);

    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    pattern->ToJsonValue(json, filter);

    EXPECT_EQ(json->GetString("enableShortcutKey"), "true");
    auto surfaceBgColor = json->GetString("surfaceBackgroundColor");
    EXPECT_FALSE(surfaceBgColor.empty());
}

/**
 * @tc.name: VideoStateMachinePatternToJsonValue003
 * @tc.desc: Test ToJsonValue with fast filter returns early.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternToJsonValue003, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    filter.filterFixed = 1; // Make IsFastFilter() true
    pattern->ToJsonValue(json, filter);

    EXPECT_TRUE(json->GetString("enableShortcutKey").empty());
}

/**
 * @tc.name: VideoStateMachinePatternSetCurrentTime006
 * @tc.desc: Test SetCurrentTime updates isInitialState_ via OnCurrentTimeChange.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternSetCurrentTime006, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isInitialState_ = true;
    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;
    pattern->OnCurrentTimeChange(0);
    EXPECT_TRUE(pattern->isInitialState_);

    pattern->OnCurrentTimeChange(10);
    EXPECT_FALSE(pattern->isInitialState_);
}

/**
 * @tc.name: VideoStateMachinePatternGetInstanceId001
 * @tc.desc: Test GetInstanceId returns valid instance ID.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternGetInstanceId001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_NE(pattern->GetInstanceId(), -1);
}

/**
 * @tc.name: VideoStateMachinePatternOnWindowHide002
 * @tc.desc: Test OnWindowHide when not in playing state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnWindowHide002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, Pause()).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::PAUSED;
    pattern->OnWindowHide();
    EXPECT_EQ(pattern->stateManager_->state_, VideoPlaybackState::PAUSED);
}

/**
 * @tc.name: VideoStateMachinePatternUpdateFsState001
 * @tc.desc: Test UpdateFsState when no fullscreen node.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternUpdateFsState001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->fullScreenNodeId_.reset();
    pattern->UpdateFsState();
    EXPECT_FALSE(pattern->fullScreenNodeId_.has_value());
}

/**
 * @tc.name: VideoStateMachinePatternOnCreatedStateEntered001
 * @tc.desc: Test OnCreatedStateEntered with valid mediaPlayer triggers PrepareAsync.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnCreatedStateEntered001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, PrepareAsync()).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::CREATED;
    pattern->stateManager_->ClearPendingCommand();

    pattern->OnCreatedStateEntered();
    EXPECT_EQ(pattern->stateManager_->GetPendingCommand(), VideoPlaybackCommand::PREPARE);
}

/**
 * @tc.name: VideoStateMachinePatternOnCreatedStateEntered002
 * @tc.desc: Test OnCreatedStateEntered with invalid mediaPlayer does nothing.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnCreatedStateEntered002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(false));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::CREATED;
    pattern->stateManager_->ClearPendingCommand();

    pattern->OnCreatedStateEntered();
    EXPECT_EQ(pattern->stateManager_->GetPendingCommand(), VideoPlaybackCommand::NONE);
}
} // namespace OHOS::Ace::NG
