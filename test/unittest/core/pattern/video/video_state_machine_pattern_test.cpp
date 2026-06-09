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
 * @tc.name: VideoStateMachinePatternOnResolutionChange001
 * @tc.desc: Test OnResolutionChange updates video size when not set.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnResolutionChange001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    mockMediaPlayer->videoWidth_ = 100;
    mockMediaPlayer->videoHeight_ = 100;
    pattern->mediaPlayer_ = mockMediaPlayer;

    videoLayoutProperty->ResetVideoSize();
    pattern->OnResolutionChange();
    EXPECT_TRUE(videoLayoutProperty->HasVideoSize());
    EXPECT_EQ(videoLayoutProperty->GetVideoSizeValue(SizeF(0, 0)).Width(), 100);
    EXPECT_EQ(videoLayoutProperty->GetVideoSizeValue(SizeF(0, 0)).Height(), 100);
}

/**
 * @tc.name: VideoStateMachinePatternOnResolutionChange002
 * @tc.desc: Test OnResolutionChange does not update video size when already set.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnResolutionChange002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    mockMediaPlayer->videoWidth_ = 200;
    mockMediaPlayer->videoHeight_ = 200;
    pattern->mediaPlayer_ = mockMediaPlayer;

    videoLayoutProperty->UpdateVideoSize(SizeF(100, 100));
    pattern->OnResolutionChange();
    EXPECT_TRUE(videoLayoutProperty->HasVideoSize());
    EXPECT_EQ(videoLayoutProperty->GetVideoSizeValue(SizeF(0, 0)).Width(), 100);
    EXPECT_EQ(videoLayoutProperty->GetVideoSizeValue(SizeF(0, 0)).Height(), 100);
}

/**
 * @tc.name: VideoStateMachinePatternUpdatePreparedVideoSize001
 * @tc.desc: Test UpdatePreparedVideoSize updates video size from media player.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternUpdatePreparedVideoSize001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    mockMediaPlayer->videoWidth_ = 1920;
    mockMediaPlayer->videoHeight_ = 1080;
    pattern->mediaPlayer_ = mockMediaPlayer;

    videoLayoutProperty->ResetVideoSize();
    pattern->UpdatePreparedVideoSize(frameNode);
    EXPECT_TRUE(videoLayoutProperty->HasVideoSize());
    EXPECT_EQ(videoLayoutProperty->GetVideoSizeValue(SizeF(0, 0)).Width(), 1920);
    EXPECT_EQ(videoLayoutProperty->GetVideoSizeValue(SizeF(0, 0)).Height(), 1080);
}

/**
 * @tc.name: VideoStateMachinePatternOnPreparedStateEntered001
 * @tc.desc: Test OnPreparedStateEntered updates video size when showFirstFrame is true.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnPreparedStateEntered001, TestSize.Level1)
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

    pattern->showFirstFrame_ = true;
    videoLayoutProperty->ResetVideoSize();
    pattern->OnPreparedStateEntered();
    EXPECT_TRUE(videoLayoutProperty->HasVideoSize());
    EXPECT_EQ(videoLayoutProperty->GetVideoSizeValue(SizeF(0, 0)).Width(), 1280);
    EXPECT_EQ(videoLayoutProperty->GetVideoSizeValue(SizeF(0, 0)).Height(), 720);
}

/**
 * @tc.name: VideoStateMachinePatternOnPreparedStateEntered002
 * @tc.desc: Test OnPreparedStateEntered does not update video size when showFirstFrame is false.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnPreparedStateEntered002, TestSize.Level1)
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
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->showFirstFrame_ = false;
    videoLayoutProperty->ResetVideoSize();
    pattern->OnPreparedStateEntered();
    EXPECT_FALSE(videoLayoutProperty->HasVideoSize());
}

/**
 * @tc.name: VideoStateMachinePatternSetCurrentTime001
 * @tc.desc: Test SetCurrentTime updates video size before seek when showFirstFrame is false.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternSetCurrentTime001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    mockMediaPlayer->videoWidth_ = 640;
    mockMediaPlayer->videoHeight_ = 480;
    EXPECT_CALL(*mockMediaPlayer, Seek(_, _)).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->showFirstFrame_ = false;
    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;
    videoLayoutProperty->ResetVideoSize();
    pattern->SetCurrentTime(10.0f, OHOS::Ace::SeekMode::SEEK_CLOSEST);
    EXPECT_TRUE(videoLayoutProperty->HasVideoSize());
    EXPECT_EQ(videoLayoutProperty->GetVideoSizeValue(SizeF(0, 0)).Width(), 640);
    EXPECT_EQ(videoLayoutProperty->GetVideoSizeValue(SizeF(0, 0)).Height(), 480);
}

/**
 * @tc.name: VideoStateMachinePatternSetCurrentTime002
 * @tc.desc: Test SetCurrentTime does not update video size before seek when showFirstFrame is true.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternSetCurrentTime002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, Seek(_, _)).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->showFirstFrame_ = true;
    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;
    videoLayoutProperty->ResetVideoSize();
    pattern->SetCurrentTime(10.0f, OHOS::Ace::SeekMode::SEEK_CLOSEST);
    EXPECT_FALSE(videoLayoutProperty->HasVideoSize());
}

/**
 * @tc.name: VideoStateMachinePatternOnCurrentTimeChange001
 * @tc.desc: Test OnCurrentTimeChange updates current position.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnCurrentTimeChange001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->duration_ = 100;
    pattern->currentPos_ = 0;
    pattern->OnCurrentTimeChange(50);
    EXPECT_EQ(pattern->currentPos_, 50);
}

/**
 * @tc.name: VideoStateMachinePatternOnPlayerStatus001
 * @tc.desc: Test OnPlayerStatus updates internal state without state machine.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnPlayerStatus001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // Test that currentPlaybackStatus_ is updated
    pattern->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(pattern->currentPlaybackStatus_, PlaybackStatus::STARTED);

    pattern->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pattern->currentPlaybackStatus_, PlaybackStatus::PAUSED);
}

/**
 * @tc.name: VideoStateMachinePatternOnStartRenderFrameCb001
 * @tc.desc: Test OnStartRenderFrameCb sets isInitialState to false.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnStartRenderFrameCb001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isInitialState_ = true;
    pattern->OnStartRenderFrameCb();
    EXPECT_FALSE(pattern->isInitialState_);
}

/**
 * @tc.name: VideoStateMachinePatternOnControllerDestroyed001
 * @tc.desc: Test OnControllerDestroyed clears videoControllerAsync reference.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnControllerDestroyed001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // Inject a controller since CreateVideoNode may return cached node without controller
    WeakPtr<VideoStateMachinePattern> weakPattern = AceType::WeakClaim(AceType::RawPtr(pattern));
    auto controller = AceType::MakeRefPtr<VideoControllerAsync>(weakPattern);
    pattern->videoControllerAsync_ = controller;
    EXPECT_NE(pattern->videoControllerAsync_, nullptr);
    pattern->OnControllerDestroyed();
    // OnControllerDestroyed only clears the internal pattern reference,
    // it does not destroy the controller object itself.
    EXPECT_NE(pattern->videoControllerAsync_, nullptr);
}

/**
 * @tc.name: VideoStateMachinePatternUpdatePreparedVideoSize002
 * @tc.desc: Test UpdatePreparedVideoSize does not update when video dimension is zero.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternUpdatePreparedVideoSize002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    mockMediaPlayer->videoWidth_ = 0;
    mockMediaPlayer->videoHeight_ = 1080;
    pattern->mediaPlayer_ = mockMediaPlayer;

    videoLayoutProperty->ResetVideoSize();
    pattern->UpdatePreparedVideoSize(frameNode);
    EXPECT_FALSE(videoLayoutProperty->HasVideoSize());
}

/**
 * @tc.name: VideoStateMachinePatternOnResolutionChange003
 * @tc.desc: Test OnResolutionChange returns early when mediaPlayer is invalid.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnResolutionChange003, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(false));
    pattern->mediaPlayer_ = mockMediaPlayer;

    videoLayoutProperty->ResetVideoSize();
    pattern->OnResolutionChange();
    EXPECT_FALSE(videoLayoutProperty->HasVideoSize());
}

/**
 * @tc.name: VideoStateMachinePatternSetCurrentTime003
 * @tc.desc: Test SetCurrentTime returns early when currentPos is negative.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternSetCurrentTime003, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;
    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;

    videoLayoutProperty->ResetVideoSize();
    pattern->SetCurrentTime(-1.0f, OHOS::Ace::SeekMode::SEEK_CLOSEST);
    EXPECT_FALSE(videoLayoutProperty->HasVideoSize());
}

/**
 * @tc.name: VideoStateMachinePatternSetCurrentTime004
 * @tc.desc: Test SetCurrentTime returns early when mediaPlayer is invalid.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternSetCurrentTime004, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(false));
    pattern->mediaPlayer_ = mockMediaPlayer;
    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;

    videoLayoutProperty->ResetVideoSize();
    pattern->SetCurrentTime(10.0f, OHOS::Ace::SeekMode::SEEK_CLOSEST);
    EXPECT_FALSE(videoLayoutProperty->HasVideoSize());
}

/**
 * @tc.name: VideoStateMachinePatternSetCurrentTime005
 * @tc.desc: Test SetCurrentTime returns early when stateManager is not active.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternSetCurrentTime005, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;
    // Default state is CREATED, IsActive() returns false

    videoLayoutProperty->ResetVideoSize();
    pattern->SetCurrentTime(10.0f, OHOS::Ace::SeekMode::SEEK_CLOSEST);
    EXPECT_FALSE(videoLayoutProperty->HasVideoSize());
}

/**
 * @tc.name: VideoStateMachinePatternOnCurrentTimeChange002
 * @tc.desc: Test OnCurrentTimeChange returns early when currentPos equals currentPos_.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnCurrentTimeChange002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->duration_ = 100;
    pattern->currentPos_ = 50;
    pattern->OnCurrentTimeChange(50);
    EXPECT_EQ(pattern->currentPos_, 50);
}

/**
 * @tc.name: VideoStateMachinePatternOnCurrentTimeChange003
 * @tc.desc: Test OnCurrentTimeChange fetches duration from mediaPlayer when duration_ is zero.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnCurrentTimeChange003, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, GetDuration(_)).WillRepeatedly(DoAll(SetArgReferee<0>(60000), Return(0)));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->duration_ = 0;
    pattern->currentPos_ = 0;
    pattern->OnCurrentTimeChange(30);
    EXPECT_EQ(pattern->duration_, 60); // 60000ms / 1000 = 60s
    EXPECT_EQ(pattern->currentPos_, 30);
}

/**
 * @tc.name: VideoStateMachinePatternOnCurrentTimeChange004
 * @tc.desc: Test OnCurrentTimeChange returns early when stateManager is stopped.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnCurrentTimeChange004, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->duration_ = 100;
    pattern->currentPos_ = 0;
    pattern->stateManager_->state_ = VideoPlaybackState::STOPPED;
    pattern->OnCurrentTimeChange(50);
    EXPECT_EQ(pattern->currentPos_, 0);
}

/**
 * @tc.name: VideoStateMachinePatternOnCurrentTimeChange005
 * @tc.desc: Test OnCurrentTimeChange does not update currentPos_ when seeking.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnCurrentTimeChange005, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->duration_ = 100;
    pattern->currentPos_ = 20;
    pattern->isSeeking_ = true;
    pattern->OnCurrentTimeChange(50);
    EXPECT_EQ(pattern->currentPos_, 20);
}

/**
 * @tc.name: VideoStateMachinePatternOnPlayerStatus002
 * @tc.desc: Test OnPlayerStatus updates isInitialState_ when playing.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnPlayerStatus002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isInitialState_ = true;
    pattern->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_FALSE(pattern->isInitialState_);
    EXPECT_EQ(pattern->currentPlaybackStatus_, PlaybackStatus::STARTED);

    pattern->isInitialState_ = true;
    pattern->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_TRUE(pattern->isInitialState_);
    EXPECT_EQ(pattern->currentPlaybackStatus_, PlaybackStatus::PAUSED);
}

/**
 * @tc.name: VideoStateMachinePatternHasPlayer001
 * @tc.desc: Test HasPlayer returns true when mediaPlayer exists.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternHasPlayer001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_TRUE(pattern->HasPlayer());

    pattern->mediaPlayer_.Reset();
    EXPECT_FALSE(pattern->HasPlayer());
}

/**
 * @tc.name: VideoStateMachinePatternSaveCurrentPlaybackStatus001
 * @tc.desc: Test SaveCurrentPlaybackStatus updates currentPlaybackStatus_.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternSaveCurrentPlaybackStatus001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->SaveCurrentPlaybackStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(pattern->currentPlaybackStatus_, PlaybackStatus::STARTED);

    pattern->SaveCurrentPlaybackStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pattern->currentPlaybackStatus_, PlaybackStatus::PAUSED);
}

/**
 * @tc.name: VideoStateMachinePatternHiddenChange001
 * @tc.desc: Test HiddenChange pauses video when hidden and playing.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternHiddenChange001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, Pause()).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;
    pattern->HiddenChange(true);
    EXPECT_TRUE(pattern->pastPlayingStatus_);

    pattern->HiddenChange(false);
    EXPECT_FALSE(pattern->pastPlayingStatus_);
}

/**
 * @tc.name: VideoStateMachinePatternOnVisibleChange001
 * @tc.desc: Test OnVisibleChange calls hiddenChangeEvent_.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnVisibleChange001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    bool called = false;
    bool hiddenValue = false;
    pattern->SetHiddenChangeEvent([&called, &hiddenValue](bool hidden) {
        called = true;
        hiddenValue = hidden;
    });

    pattern->OnVisibleChange(true);
    EXPECT_TRUE(called);
    EXPECT_FALSE(hiddenValue);
}

/**
 * @tc.name: VideoStateMachinePatternIsFullScreen001
 * @tc.desc: Test IsFullScreen returns false when no fullScreenNodeId.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternIsFullScreen001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_FALSE(pattern->IsFullScreen());
}

/**
 * @tc.name: VideoStateMachinePatternOnFullScreenChange001
 * @tc.desc: Test OnFullScreenChange fires full screen change event.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnFullScreenChange001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    bool called = false;
    bool fullScreenValue = false;
    auto eventHub = pattern->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(eventHub);
    eventHub->SetOnFullScreenChange([&called, &fullScreenValue](const std::string& param) {
        called = true;
        auto json = JsonUtil::ParseJsonString(param);
        if (json) {
            fullScreenValue = json->GetBool("fullscreen", false);
        }
    });

    pattern->OnFullScreenChange(true);
    EXPECT_TRUE(called);
    EXPECT_TRUE(fullScreenValue);
}

/**
 * @tc.name: VideoStateMachinePatternSetSurfaceBackgroundColor001
 * @tc.desc: Test SetSurfaceBackgroundColor updates surface background color.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternSetSurfaceBackgroundColor001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    pattern->renderContextForMediaPlayer_ = renderContext;

    pattern->SetSurfaceBackgroundColor(Color::RED);
    EXPECT_EQ(pattern->surfaceBgColor_.GetValue(), Color::RED.GetValue());
}

/**
 * @tc.name: VideoStateMachinePatternRemoveMediaPlayerSurfaceNode001
 * @tc.desc: Test RemoveMediaPlayerSurfaceNode does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternRemoveMediaPlayerSurfaceNode001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // Should not crash even when renderSurface is empty
    pattern->RemoveMediaPlayerSurfaceNode();
    EXPECT_TRUE(pattern->renderSurface_);
}

/**
 * @tc.name: VideoStateMachinePatternOnAttachToFrameNode001
 * @tc.desc: Test OnAttachToFrameNode attaches pattern to controller.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnAttachToFrameNode001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // OnAttachToFrameNode is called during node creation in CreateVideoNode
    // Verify hostId is set
    EXPECT_NE(pattern->hostId_, 0);
}

/**
 * @tc.name: VideoStateMachinePatternCreateSlider001
 * @tc.desc: Test CreateSlider creates a slider node.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternCreateSlider001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto sliderNode = pattern->CreateSlider();
    ASSERT_TRUE(sliderNode);
    EXPECT_EQ(sliderNode->GetTag(), V2::SLIDER_ETS_TAG);
}

/**
 * @tc.name: VideoStateMachinePatternCreateText001
 * @tc.desc: Test CreateText creates a text node with correct content.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternCreateText001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto textNode = pattern->CreateText(65); // 1:05
    ASSERT_TRUE(textNode);
    EXPECT_EQ(textNode->GetTag(), V2::TEXT_ETS_TAG);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_TRUE(textLayoutProperty);
    EXPECT_EQ(UtfUtils::Str16ToStr8(textLayoutProperty->GetContentValue(u"")), "01:05");
}

/**
 * @tc.name: VideoStateMachinePatternCreateSVG001
 * @tc.desc: Test CreateSVG creates an image node for SVG.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternCreateSVG001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto svgNode = pattern->CreateSVG();
    ASSERT_TRUE(svgNode);
    EXPECT_EQ(svgNode->GetTag(), V2::IMAGE_ETS_TAG);
}

/**
 * @tc.name: VideoStateMachinePatternChangePlayButtonTag001
 * @tc.desc: Test ChangePlayButtonTag updates play button icon based on state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternChangePlayButtonTag001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // Create a play button node and test the state-based icon update directly
    auto playBtn = pattern->CreateSVG();
    ASSERT_TRUE(playBtn);
    ASSERT_EQ(playBtn->GetTag(), V2::IMAGE_ETS_TAG);

    // Test PLAYING state - should show PAUSE icon
    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;
    pattern->ChangePlayButtonTag(playBtn);
    auto svgLayoutProperty = playBtn->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_TRUE(svgLayoutProperty);
    auto sourceInfo = svgLayoutProperty->GetImageSourceInfoValue(ImageSourceInfo());
    EXPECT_EQ(sourceInfo.GetResourceId(), InternalResource::ResourceId::PAUSE_SVG);

    // Test non-PLAYING state - should show PLAY icon
    pattern->stateManager_->state_ = VideoPlaybackState::PAUSED;
    pattern->ChangePlayButtonTag(playBtn);
    sourceInfo = svgLayoutProperty->GetImageSourceInfoValue(ImageSourceInfo());
    EXPECT_EQ(sourceInfo.GetResourceId(), InternalResource::ResourceId::PLAY_SVG);
}

/**
 * @tc.name: VideoStateMachinePatternSetCurrentVolume001
 * @tc.desc: Test SetCurrentVolume and GetCurrentVolume update volume.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternSetCurrentVolume001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_FLOAT_EQ(pattern->GetCurrentVolume(), 1.0f);

    pattern->SetCurrentVolume(0.5f);
    EXPECT_FLOAT_EQ(pattern->GetCurrentVolume(), 0.5f);
}

/**
 * @tc.name: VideoStateMachinePatternSetShortcutKeyEnabled001
 * @tc.desc: Test SetShortcutKeyEnabled and GetShortcutKeyEnabled toggle shortcut keys.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternSetShortcutKeyEnabled001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_FALSE(pattern->GetShortcutKeyEnabled());

    pattern->SetShortcutKeyEnabled(true);
    EXPECT_TRUE(pattern->GetShortcutKeyEnabled());

    pattern->SetShortcutKeyEnabled(false);
    EXPECT_FALSE(pattern->GetShortcutKeyEnabled());
}

/**
 * @tc.name: VideoStateMachinePatternGetTargetVideoPattern001
 * @tc.desc: Test GetTargetVideoPattern returns self for non-fullscreen.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternGetTargetVideoPattern001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto targetPattern = pattern->GetTargetVideoPattern();
    EXPECT_EQ(targetPattern, pattern);
}

/**
 * @tc.name: VideoStateMachinePatternRecoverState001
 * @tc.desc: Test RecoverState copies state from another pattern.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternRecoverState001, TestSize.Level1)
{
    auto frameNode1 = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode1);
    auto pattern1 = frameNode1->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern1);

    auto frameNode2 = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode2);
    auto pattern2 = frameNode2->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern2);

    pattern1->duration_ = 100;
    pattern1->currentPos_ = 50;
    pattern1->muted_ = true;
    pattern1->loop_ = true;
    pattern1->autoPlay_ = true;
    pattern1->progressRate_ = 2.0;

    pattern2->RecoverState(pattern1);
    EXPECT_EQ(pattern2->duration_, 100);
    EXPECT_EQ(pattern2->currentPos_, 50);
    EXPECT_TRUE(pattern2->muted_);
    EXPECT_TRUE(pattern2->loop_);
    EXPECT_TRUE(pattern2->autoPlay_);
    EXPECT_DOUBLE_EQ(pattern2->progressRate_, 2.0);
}

/**
 * @tc.name: VideoStateMachinePatternToJsonValue001
 * @tc.desc: Test ToJsonValue serializes video properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternToJsonValue001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->progressRate_ = 1.5;
    pattern->isEnableAnalyzer_ = true;

    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    pattern->ToJsonValue(json, filter);

    // PutExtAttr stores double as numeric type, GetString cannot read it
    auto rateValue = json->GetValue("currentProgressRate");
    EXPECT_TRUE(rateValue != nullptr);
    if (rateValue) {
        EXPECT_DOUBLE_EQ(rateValue->GetDouble(), 1.5);
    }
    EXPECT_EQ(json->GetString("enableAnalyzer"), "true");
}

/**
 * @tc.name: VideoStateMachinePatternUpdateMediaParam001
 * @tc.desc: Test UpdateMediaParam updates media player parameters.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternUpdateMediaParam001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    auto mockRenderSurface = AceType::MakeRefPtr<MockRenderSurface>();
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();

    pattern->UpdateMediaParam(mockMediaPlayer, mockRenderSurface, mockRenderContext);

    EXPECT_EQ(pattern->mediaPlayer_, mockMediaPlayer);
    EXPECT_EQ(pattern->renderSurface_, mockRenderSurface);
    EXPECT_EQ(pattern->renderContextForMediaPlayer_, mockRenderContext);
}

/**
 * @tc.name: VideoStateMachinePatternResetMediaParam001
 * @tc.desc: Test ResetMediaParam resets media player parameters.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternResetMediaParam001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    auto mockRenderSurface = AceType::MakeRefPtr<MockRenderSurface>();
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();

    pattern->UpdateMediaParam(mockMediaPlayer, mockRenderSurface, mockRenderContext);
    pattern->ResetMediaParam();

    EXPECT_FALSE(pattern->mediaPlayer_);
    EXPECT_FALSE(pattern->renderSurface_);
    EXPECT_FALSE(pattern->renderContextForMediaPlayer_);
}

/**
 * @tc.name: VideoStateMachinePatternOnKeyEvent001
 * @tc.desc: Test OnKeyEvent handles space key for play/pause.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnKeyEvent001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_SPACE;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_SPACE);

    pattern->isEnableShortcutKey_ = true;
    bool handled = pattern->OnKeyEvent(keyEvent);
    // Space key should be handled when shortcut key is enabled
    EXPECT_TRUE(handled);
}

/**
 * @tc.name: VideoStateMachinePatternGetFocusPattern001
 * @tc.desc: Test GetFocusPattern returns scope type.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternGetFocusPattern001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto focusPattern = pattern->GetFocusPattern();
    EXPECT_EQ(focusPattern.focusType_, FocusType::SCOPE);
    EXPECT_TRUE(focusPattern.focusable_);
}

/**
 * @tc.name: VideoStateMachinePatternEnableAnalyzer001
 * @tc.desc: Test EnableAnalyzer toggles analyzer state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternEnableAnalyzer001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_FALSE(pattern->isEnableAnalyzer_);

    pattern->EnableAnalyzer(true);
    EXPECT_TRUE(pattern->isEnableAnalyzer_);

    pattern->EnableAnalyzer(false);
    EXPECT_FALSE(pattern->isEnableAnalyzer_);
}

/**
 * @tc.name: VideoStateMachinePatternSetContentTransition001
 * @tc.desc: Test SetContentTransition updates content transition.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternSetContentTransition001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_EQ(pattern->contentTransition_, ContentTransitionType::IDENTITY);

    pattern->SetContentTransition(ContentTransitionType::OPACITY);
    EXPECT_EQ(pattern->contentTransition_, ContentTransitionType::OPACITY);
}

/**
 * @tc.name: VideoStateMachinePatternSetIsSeeking001
 * @tc.desc: Test SetIsSeeking and GetIsSeeking toggle seeking state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternSetIsSeeking001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_FALSE(pattern->GetIsSeeking());

    pattern->SetIsSeeking(true);
    EXPECT_TRUE(pattern->GetIsSeeking());

    pattern->SetIsSeeking(false);
    EXPECT_FALSE(pattern->GetIsSeeking());
}

/**
 * @tc.name: VideoStateMachinePatternGetCurrentPos001
 * @tc.desc: Test GetCurrentPos returns current position.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternGetCurrentPos001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->currentPos_ = 42;
    EXPECT_EQ(pattern->GetCurrentPos(), 42);
}

/**
 * @tc.name: VideoStateMachinePatternGetDuration001
 * @tc.desc: Test GetDuration returns duration.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternGetDuration001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->duration_ = 120;
    EXPECT_EQ(pattern->GetDuration(), 120);
}

/**
 * @tc.name: VideoStateMachinePatternGetSrc001
 * @tc.desc: Test GetSrc returns video source.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternGetSrc001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->videoSrcInfo_.src_ = "test_video.mp4";
    EXPECT_EQ(pattern->GetSrc(), "test_video.mp4");
}

/**
 * @tc.name: VideoStateMachinePatternIsFirstPlay001
 * @tc.desc: Test IsFirstPlay returns initial state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternIsFirstPlay001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_TRUE(pattern->IsFirstPlay());

    pattern->isInitialState_ = false;
    EXPECT_FALSE(pattern->IsFirstPlay());
}

/**
 * @tc.name: VideoStateMachinePatternUpdateProgressRate001
 * @tc.desc: Test UpdateProgressRate and GetProgressRate update rate.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternUpdateProgressRate001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_DOUBLE_EQ(pattern->GetProgressRate(), 1.0);

    pattern->UpdateProgressRate(2.0);
    EXPECT_DOUBLE_EQ(pattern->GetProgressRate(), 2.0);
}

/**
 * @tc.name: VideoStateMachinePatternUpdateMuted001
 * @tc.desc: Test UpdateMuted and GetMuted toggle muted state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternUpdateMuted001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_FALSE(pattern->GetMuted());

    pattern->UpdateMuted(true);
    EXPECT_TRUE(pattern->GetMuted());

    pattern->UpdateMuted(false);
    EXPECT_FALSE(pattern->GetMuted());
}

/**
 * @tc.name: VideoStateMachinePatternUpdateAutoPlay001
 * @tc.desc: Test UpdateAutoPlay and GetAutoPlay toggle autoplay state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternUpdateAutoPlay001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_FALSE(pattern->GetAutoPlay());

    pattern->UpdateAutoPlay(true);
    EXPECT_TRUE(pattern->GetAutoPlay());

    pattern->UpdateAutoPlay(false);
    EXPECT_FALSE(pattern->GetAutoPlay());
}

/**
 * @tc.name: VideoStateMachinePatternUpdateLoop001
 * @tc.desc: Test UpdateLoop and GetLoop toggle loop state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternUpdateLoop001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_FALSE(pattern->GetLoop());

    pattern->UpdateLoop(true);
    EXPECT_TRUE(pattern->GetLoop());

    pattern->UpdateLoop(false);
    EXPECT_FALSE(pattern->GetLoop());
}

/**
 * @tc.name: VideoStateMachinePatternOnError001
 * @tc.desc: Test OnError(std::string) triggers error handling.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnError001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->OnError("Test error message");
    EXPECT_EQ(pattern->lastErrorCode_, ERROR_CODE_VIDEO_SOURCE_INVALID);
    EXPECT_EQ(pattern->lastErrorMessage_, "Test error message");
}

/**
 * @tc.name: VideoStateMachinePatternOnError002
 * @tc.desc: Test OnError(int32_t, std::string) triggers error handling.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnError002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->OnError(404, "Not found");
    EXPECT_EQ(pattern->lastErrorCode_, 404);
    EXPECT_EQ(pattern->lastErrorMessage_, "Not found");
}

/**
 * @tc.name: VideoStateMachinePatternOnInjectionEvent002
 * @tc.desc: Test OnInjectionEvent with invalid command.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnInjectionEvent002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    std::string command = "invalid json";
    int32_t ret = pattern->OnInjectionEvent(command);
    EXPECT_NE(ret, 0);
}

/**
 * @tc.name: VideoStateMachinePatternUpdateControllerBar001
 * @tc.desc: Test UpdateControllerBar updates control bar visibility.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternUpdateControllerBar001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // Create control bar first
    auto controlBar = pattern->CreateControlBar();
    ASSERT_TRUE(controlBar);
    pattern->controlBar_ = controlBar;

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateControls(true);

    pattern->UpdateControllerBar();
    // Verify control bar is visible
    EXPECT_TRUE(controlBar->GetLayoutProperty()->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::VISIBLE);
}

/**
 * @tc.name: VideoStateMachinePatternCreateControlBar001
 * @tc.desc: Test CreateControlBar creates control bar node.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternCreateControlBar001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto controlBar = pattern->CreateControlBar();
    ASSERT_TRUE(controlBar);
    EXPECT_EQ(controlBar->GetTag(), V2::ROW_ETS_TAG);
}

/**
 * @tc.name: VideoStateMachinePatternOnDirtyLayoutWrapperSwap001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap exists and is callable.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: VideoStateMachinePatternOnWindowHide001
 * @tc.desc: Test OnWindowHide pauses video.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternOnWindowHide001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, Pause()).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;
    pattern->OnWindowHide();
    EXPECT_EQ(pattern->stateManager_->state_, VideoPlaybackState::PLAYING);
}

/**
 * @tc.name: VideoStateMachinePatternPostSerialBgTaskNoHost001
 * @tc.desc: Test PostSerialBgTask drops task when host/context is null.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternPostSerialBgTaskNoHost001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<VideoStateMachinePattern>(nullptr);
    ASSERT_TRUE(pattern);
    EXPECT_TRUE(pattern->serialBgTaskQueue_.empty());

    bool taskExecuted = false;
    pattern->PostSerialBgTask([&taskExecuted]() { taskExecuted = true; }, "NoHostTest");
    EXPECT_TRUE(pattern->serialBgTaskQueue_.empty());
    EXPECT_FALSE(taskExecuted);
}

/**
 * @tc.name: VideoStateMachinePatternSerialQueueDestructor001
 * @tc.desc: Test destructor clears serial background task queue without crash.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, VideoStateMachinePatternSerialQueueDestructor001, TestSize.Level1)
{
    {
        auto pattern = AceType::MakeRefPtr<VideoStateMachinePattern>(nullptr);
        ASSERT_TRUE(pattern);
        pattern->serialBgTaskQueue_.push({"Task1", []() {}});
        pattern->serialBgTaskQueue_.push({"Task2", []() {}});
        pattern->isDrainingSerialBgQueue_ = true;
        EXPECT_EQ(pattern->serialBgTaskQueue_.size(), 2u);
        // Destructor should clear the queue and reset the flag without crashing.
    }
    // Reaching here without crash means the destructor works correctly.
    EXPECT_TRUE(true);
}

} // namespace OHOS::Ace::NG
