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
#include "core/components_ng/pattern/video/video_state_machine_full_screen_pattern.h"
#include "test/mock/frameworks/core/common/mock_image_analyzer_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t RET_SUCCESS_VAL = 10;
constexpr int32_t RET_FAILED_VAL = 11;
const std::string VIDEO_START_EVENT = "start";
const std::string VIDEO_PAUSE_EVENT = "pause";
const std::string VIDEO_FINISH_EVENT = "finish";
const std::string VIDEO_STOP_EVENT = "stop";
const std::string VIDEO_SEEKING_EVENT = "seeking";
const std::string VIDEO_SEEKED_EVENT = "seeked";
const std::string VIDEO_SRC_TEST = "common/video.mp4";
const std::string VIDEO_POSTER_TEST = "common/img2.png";
} // namespace

// Group 1: Media Control and Surface (1-10)

/**
 * @tc.name: UpdateLooping001
 * @tc.desc: Test UpdateLooping valid/invalid mediaPlayer branches.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, UpdateLooping001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // Invalid branch
    auto invalidMock = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*invalidMock, IsMediaPlayerValid()).WillRepeatedly(Return(false));
    pattern->mediaPlayer_ = invalidMock;
    pattern->loop_ = true;
    pattern->UpdateLooping();
    EXPECT_EQ(pattern->loop_, true); // loop_ should not be modified

    // Valid branch
    auto validMock = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*validMock, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = validMock;
    pattern->UpdateLooping();
    EXPECT_TRUE(pattern->loop_);
}

/**
 * @tc.name: UpdateMutedPrivate001
 * @tc.desc: Test private UpdateMuted method branches.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, UpdateMutedPrivate001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, SetVolume(_, _)).Times(AnyNumber());
    pattern->mediaPlayer_ = mockMediaPlayer;

    // muted=true branch
    pattern->muted_ = true;
    pattern->currentVolume_ = 0.5f;
    pattern->UpdateMuted();

    // volume=0 branch
    pattern->muted_ = false;
    pattern->currentVolume_ = 0.0f;
    pattern->UpdateMuted();

    // normal branch
    pattern->muted_ = false;
    pattern->currentVolume_ = 0.5f;
    pattern->UpdateMuted();
    EXPECT_FLOAT_EQ(pattern->GetCurrentVolume(), 0.5f);
}

/**
 * @tc.name: PrepareSurface001
 * @tc.desc: Test PrepareSurface surface setup branches.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, PrepareSurface001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // Case 1: mediaPlayer null => returns early
    pattern->mediaPlayer_.Reset();
    pattern->PrepareSurface();
    EXPECT_FALSE(pattern->mediaPlayer_);

    // Case 2: valid mediaPlayer, surface invalid => init surface
    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, SetRenderSurface(_)).Times(AnyNumber());
    EXPECT_CALL(*mockMediaPlayer, SetSurface()).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    auto mockRenderSurface = AceType::MakeRefPtr<MockRenderSurface>();
    EXPECT_CALL(*mockRenderSurface, IsSurfaceValid()).WillOnce(Return(false)).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockRenderSurface, InitSurface()).Times(1);
    EXPECT_CALL(*mockRenderSurface, SetRenderContext(_)).Times(AnyNumber());
    pattern->renderSurface_ = mockRenderSurface;
    pattern->PrepareSurface();
    EXPECT_TRUE(pattern->renderSurface_);
}

/**
 * @tc.name: OnSliderChange001
 * @tc.desc: Test OnSliderChange BEGIN/MOVING/END modes.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnSliderChange001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.src = VIDEO_SRC_TEST;
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, Seek(_, _)).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;
    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;

    auto eventHub = pattern->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(eventHub);
    std::string seekingCheck;
    std::string seekedCheck;
    eventHub->SetOnSeeking([&seekingCheck](const std::string& /* param */) { seekingCheck = VIDEO_SEEKING_EVENT; });
    eventHub->SetOnSeeked([&seekedCheck](const std::string& /* param */) { seekedCheck = VIDEO_SEEKED_EVENT; });

    // BEGIN mode
    pattern->OnSliderChange(10.0f, 0); // BEGIN
    pattern->OnSliderChange(20.0f, 1); // MOVING
    pattern->OnSliderChange(30.0f, 2); // END
    EXPECT_EQ(seekedCheck, VIDEO_SEEKED_EVENT);
}

/**
 * @tc.name: ChangePlayerStatus001
 * @tc.desc: Test ChangePlayerStatus for PREPARED and STOPPED states.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, ChangePlayerStatus001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;

    // PREPARED with invalid mediaPlayer => returns early, no transition
    pattern->stateManager_->state_ = VideoPlaybackState::CREATED;
    pattern->mediaPlayer_.Reset();
    pattern->ChangePlayerStatus(PlaybackStatus::PREPARED);
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), VideoPlaybackState::CREATED);

    // PREPARED with valid mediaPlayer => transitions to PREPARED
    pattern->mediaPlayer_ = mockMediaPlayer;
    pattern->stateManager_->state_ = VideoPlaybackState::CREATED;
    pattern->ChangePlayerStatus(PlaybackStatus::PREPARED);
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), VideoPlaybackState::PREPARED);

    // STOPPED => transitions to STOPPED
    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;
    pattern->ChangePlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), VideoPlaybackState::STOPPED);
}

/**
 * @tc.name: SetSourceForMediaPlayer001
 * @tc.desc: Test SetSourceForMediaPlayer.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, SetSourceForMediaPlayer001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // Null mediaPlayer => false
    pattern->mediaPlayer_.Reset();
    EXPECT_FALSE(pattern->SetSourceForMediaPlayer());

    // Valid mediaPlayer => returns SetSource result
    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, SetSource(_, _, _)).WillOnce(Return(true)).WillOnce(Return(false));
    pattern->mediaPlayer_ = mockMediaPlayer;
    pattern->videoSrcInfo_.src_ = VIDEO_SRC_TEST;

    EXPECT_TRUE(pattern->SetSourceForMediaPlayer());
    EXPECT_FALSE(pattern->SetSourceForMediaPlayer());
}

// Group 2: UI/Layout/Lifecycle (11-20)

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test OnModifyDone hiddenChangeEvent registration and fullscreen recovery.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnModifyDone001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // hiddenChangeEvent should be created if null
    pattern->hiddenChangeEvent_ = nullptr;
    pattern->OnModifyDone();
    EXPECT_NE(pattern->hiddenChangeEvent_, nullptr);

    // FullScreen state recovery
    pattern->fullScreenNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    pattern->OnModifyDone();
    EXPECT_TRUE(pattern->fullScreenNodeId_.has_value());
}

/**
 * @tc.name: OnAreaChangedInner001
 * @tc.desc: Test OnAreaChangedInner with different ObjectFit.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnAreaChangedInner001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_TRUE(geometryNode);

    auto oldExtSurface = SystemProperties::GetExtSurfaceEnabled();
    SystemProperties::SetExtSurfaceEnabled(true);

    geometryNode->SetContentSize(SizeF(400.0f, 300.0f));
    videoLayoutProperty->UpdateVideoSize(SizeF(200.0f, 100.0f));
    videoLayoutProperty->UpdateObjectFit(ImageFit::CONTAIN);
    pattern->OnAreaChangedInner();
    EXPECT_FLOAT_EQ(pattern->lastBoundsRect_.Width(), 400.0f);

    videoLayoutProperty->UpdateObjectFit(ImageFit::FILL);
    pattern->OnAreaChangedInner();
    EXPECT_FLOAT_EQ(pattern->lastBoundsRect_.Height(), 300.0f);

    SystemProperties::SetExtSurfaceEnabled(oldExtSurface);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test OnColorConfigurationUpdate control bar background color.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto controlBar = pattern->CreateControlBar();
    ASSERT_TRUE(controlBar);
    pattern->controlBar_ = controlBar;

    auto videoTheme = PipelineBase::GetCurrentContext()->GetTheme<VideoTheme>();
    ASSERT_TRUE(videoTheme);

    pattern->OnColorConfigurationUpdate();
    auto renderContext = controlBar->GetRenderContext();
    ASSERT_TRUE(renderContext);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), videoTheme->GetBkgColor());
}

/**
 * @tc.name: UpdateVideoProperty001
 * @tc.desc: Test UpdateVideoProperty autoPlay + isInitialState combination.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, UpdateVideoProperty001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;

    // isInitialState=false, autoPlay=true => Start() not called
    pattern->stateManager_->ClearPendingCommand();
    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;
    pattern->isInitialState_ = false;
    pattern->autoPlay_ = true;
    pattern->UpdateVideoProperty();
    EXPECT_EQ(pattern->stateManager_->GetPendingCommand(), VideoPlaybackCommand::NONE);

    // isInitialState=true, autoPlay=false => Start() not called
    pattern->stateManager_->ClearPendingCommand();
    pattern->isInitialState_ = true;
    pattern->autoPlay_ = false;
    pattern->UpdateVideoProperty();
    EXPECT_EQ(pattern->stateManager_->GetPendingCommand(), VideoPlaybackCommand::NONE);

    // isInitialState=true, autoPlay=true => Start() called
    pattern->stateManager_->ClearPendingCommand();
    pattern->isInitialState_ = true;
    pattern->autoPlay_ = true;
    pattern->UpdateVideoProperty();
    EXPECT_EQ(pattern->stateManager_->GetPendingCommand(), VideoPlaybackCommand::PLAY);
}

/**
 * @tc.name: OnRebuildFrame001
 * @tc.desc: Test OnRebuildFrame with valid/invalid surface.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnRebuildFrame001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // renderSurface_ null => returns early
    pattern->renderSurface_.Reset();
    pattern->OnRebuildFrame();
    EXPECT_FALSE(pattern->renderSurface_);

    // renderSurface_ valid but IsSurfaceValid false => returns early
    auto mockRenderSurface = AceType::MakeRefPtr<MockRenderSurface>();
    EXPECT_CALL(*mockRenderSurface, IsSurfaceValid()).WillRepeatedly(Return(false));
    pattern->renderSurface_ = mockRenderSurface;
    pattern->OnRebuildFrame();
    EXPECT_TRUE(pattern->renderSurface_);

    // renderSurface_ valid and IsSurfaceValid true => calls AddChild
    EXPECT_CALL(*mockRenderSurface, IsSurfaceValid()).WillRepeatedly(Return(true));
    pattern->OnRebuildFrame();
    EXPECT_TRUE(pattern->renderSurface_);
}

/**
 * @tc.name: UpdatePreviewImage001
 * @tc.desc: Test UpdatePreviewImage poster visibility switching.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, UpdatePreviewImage001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.posterUrl = VIDEO_POSTER_TEST;
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(layoutProperty);

    auto video = AceType::DynamicCast<VideoNode>(frameNode);
    ASSERT_TRUE(video);
    auto image = AceType::DynamicCast<FrameNode>(video->GetPreviewImage());
    ASSERT_TRUE(image);
    auto posterLayoutProperty = image->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_TRUE(posterLayoutProperty);

    // showFirstFrame=true => poster invisible
    pattern->showFirstFrame_ = true;
    pattern->UpdatePreviewImage();
    EXPECT_EQ(posterLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);

    // showFirstFrame=false, isInitialState=false => poster invisible
    pattern->showFirstFrame_ = false;
    pattern->isInitialState_ = false;
    pattern->UpdatePreviewImage();
    EXPECT_EQ(posterLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
}

/**
 * @tc.name: OnDetachFromMainTree001
 * @tc.desc: Test OnDetachFromMainTree.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDetachFromMainTree001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // Normal detach => no crash, stateManager_ state unchanged, Pause() not called
    auto originalState = pattern->stateManager_->GetCurrentState();
    pattern->OnDetachFromMainTree();
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), originalState);

    // BUILDER_NODE_OFF_MAINTREE => Pause() called
    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;
    frameNode->UpdateNodeStatus(NodeStatus::BUILDER_NODE_OFF_MAINTREE);
    pattern->OnDetachFromMainTree();
    EXPECT_TRUE(pattern->stateManager_->IsPaused() || pattern->stateManager_->HasPendingCommand());
}

/**
 * @tc.name: IsEnableMatchParent001
 * @tc.desc: Test IsEnableMatchParent returns true.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, IsEnableMatchParent001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_TRUE(pattern->IsEnableMatchParent());
}

/**
 * @tc.name: ResetLastBoundsRect001
 * @tc.desc: Test ResetLastBoundsRect.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, ResetLastBoundsRect001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->lastBoundsRect_ = Rect(10.0f, 20.0f, 100.0f, 200.0f);
    pattern->ResetLastBoundsRect();
    EXPECT_FLOAT_EQ(pattern->lastBoundsRect_.Width(), 0.0f);
    EXPECT_FLOAT_EQ(pattern->lastBoundsRect_.Height(), 0.0f);
}

/**
 * @tc.name: SetContentTransition001
 * @tc.desc: Test SetContentTransition.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, SetContentTransition001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_EQ(pattern->contentTransition_, ContentTransitionType::IDENTITY);
    pattern->SetContentTransition(ContentTransitionType::OPACITY);
    EXPECT_EQ(pattern->contentTransition_, ContentTransitionType::OPACITY);
}

// Group 3: FullScreen (21-25)

/**
 * @tc.name: FullScreen001
 * @tc.desc: Test FullScreen creates fullscreen node.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, FullScreen001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_FALSE(pattern->IsFullScreen());
    pattern->FullScreen();
    EXPECT_TRUE(pattern->IsFullScreen());
    EXPECT_NE(pattern->GetFullScreenNode(), nullptr);

    // Call again => should not create another
    pattern->FullScreen();
    EXPECT_TRUE(pattern->IsFullScreen());
}

/**
 * @tc.name: OnBackPressed001
 * @tc.desc: Test OnBackPressed returns true for fullscreen pattern.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnBackPressed001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // Base pattern returns false
    EXPECT_FALSE(pattern->OnBackPressed());

    // Fullscreen pattern returns true
    pattern->FullScreen();
    auto fullScreenNode = pattern->GetFullScreenNode();
    ASSERT_TRUE(fullScreenNode);
    auto fsPattern = AceType::DynamicCast<VideoStateMachineFullScreenPattern>(fullScreenNode->GetPattern());
    ASSERT_TRUE(fsPattern);
    EXPECT_TRUE(fsPattern->OnBackPressed());
}

/**
 * @tc.name: GetFullScreenNode001
 * @tc.desc: Test GetFullScreenNode.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, GetFullScreenNode001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // No fullscreen => nullptr
    EXPECT_EQ(pattern->GetFullScreenNode(), nullptr);

    // After FullScreen => non-null
    pattern->FullScreen();
    EXPECT_NE(pattern->GetFullScreenNode(), nullptr);
}

/**
 * @tc.name: RecoverState001
 * @tc.desc: Test RecoverState copies state.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, RecoverState001, TestSize.Level1)
{
    auto frameNode1 = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode1);
    auto pattern1 = frameNode1->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern1);

    auto frameNode2 = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode2);
    auto pattern2 = frameNode2->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern2);

    pattern1->duration_ = 120;
    pattern1->currentPos_ = 60;
    pattern1->muted_ = true;
    pattern1->loop_ = true;
    pattern1->autoPlay_ = true;
    pattern1->progressRate_ = 1.5;
    pattern1->isEnableAnalyzer_ = true;
    auto imageAnalyzerManager1 =
        std::make_shared<MockImageAnalyzerManager>(frameNode1, ImageAnalyzerHolder::VIDEO_CUSTOM);
    imageAnalyzerManager1->SetOverlayCreated(true);
    pattern1->imageAnalyzerManager_ = imageAnalyzerManager1;

    pattern2->RecoverState(pattern1);
    EXPECT_EQ(pattern2->duration_, 120);
    EXPECT_EQ(pattern2->currentPos_, 60);
    EXPECT_TRUE(pattern2->muted_);
    EXPECT_TRUE(pattern2->loop_);
    EXPECT_TRUE(pattern2->autoPlay_);
    EXPECT_DOUBLE_EQ(pattern2->progressRate_, 1.5);
    EXPECT_TRUE(pattern2->isAnalyzerCreated_);
    EXPECT_TRUE(pattern2->isEnableAnalyzer_);
}

// Group 4: Image Analysis (26-35)

/**
 * @tc.name: IsSupportImageAnalyzer001
 * @tc.desc: Test IsSupportImageAnalyzer returns value based on conditions.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, IsSupportImageAnalyzer001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(layoutProperty);

    // Default: false
    EXPECT_FALSE(pattern->IsSupportImageAnalyzer());

    // Enable analyzer but no manager => false
    pattern->EnableAnalyzer(true);
    EXPECT_FALSE(pattern->IsSupportImageAnalyzer());

    // With manager and controls disabled
    auto imageAnalyzerManager =
        std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::VIDEO_CUSTOM);
    imageAnalyzerManager->SetSupportImageAnalyzerFeature(true);
    pattern->imageAnalyzerManager_ = imageAnalyzerManager;
    layoutProperty->UpdateControls(false);
    EXPECT_TRUE(pattern->IsSupportImageAnalyzer());

    // Controls enabled => false
    layoutProperty->UpdateControls(true);
    EXPECT_FALSE(pattern->IsSupportImageAnalyzer());
}

/**
 * @tc.name: ShouldUpdateImageAnalyzer001
 * @tc.desc: Test ShouldUpdateImageAnalyzer with different selfIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, ShouldUpdateImageAnalyzer001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(layoutProperty);

    // No calc constraint => false
    EXPECT_FALSE(pattern->ShouldUpdateImageAnalyzer());

    MeasureProperty constraint;
    layoutProperty->UpdateCalcLayoutProperty(constraint);
    EXPECT_FALSE(pattern->ShouldUpdateImageAnalyzer());

    // Percent width only, COVER => true
    constraint.selfIdealSize = CalcSize(CalcLength(10, DimensionUnit::PERCENT), CalcLength(10));
    layoutProperty->UpdateCalcLayoutProperty(constraint);
    layoutProperty->UpdateObjectFit(ImageFit::COVER);
    EXPECT_TRUE(pattern->ShouldUpdateImageAnalyzer());

    // FILL => false
    layoutProperty->UpdateObjectFit(ImageFit::FILL);
    EXPECT_FALSE(pattern->ShouldUpdateImageAnalyzer());

    // NONE => true
    layoutProperty->UpdateObjectFit(ImageFit::NONE);
    EXPECT_TRUE(pattern->ShouldUpdateImageAnalyzer());
}

/**
 * @tc.name: StartImageAnalyzer001
 * @tc.desc: Test StartImageAnalyzer overlayCreated branch.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, StartImageAnalyzer001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(layoutProperty);

    auto imageAnalyzerManager =
        std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::VIDEO_CUSTOM);
    imageAnalyzerManager->SetSupportImageAnalyzerFeature(true);
    pattern->imageAnalyzerManager_ = imageAnalyzerManager;
    pattern->EnableAnalyzer(true);
    layoutProperty->UpdateControls(false);

    // overlayCreated=false => posts delayed task
    imageAnalyzerManager->SetOverlayCreated(false);
    pattern->StartImageAnalyzer();
    EXPECT_TRUE(pattern->isEnableAnalyzer_);

    // overlayCreated=true => calls DestroyAnalyzerOverlay
    imageAnalyzerManager->SetOverlayCreated(true);
    pattern->StartImageAnalyzer();
    EXPECT_TRUE(pattern->isEnableAnalyzer_);
}

/**
 * @tc.name: StartUpdateImageAnalyzer001
 * @tc.desc: Test StartUpdateImageAnalyzer.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, StartUpdateImageAnalyzer001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto imageAnalyzerManager =
        std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::VIDEO_CUSTOM);
    pattern->imageAnalyzerManager_ = imageAnalyzerManager;
    pattern->EnableAnalyzer(true);

    // overlayCreated=false => returns early
    imageAnalyzerManager->SetOverlayCreated(false);
    pattern->isContentSizeChanged_ = false;
    pattern->StartUpdateImageAnalyzer();
    EXPECT_FALSE(pattern->isContentSizeChanged_);

    // overlayCreated=true => sets isContentSizeChanged_
    imageAnalyzerManager->SetOverlayCreated(true);
    pattern->StartUpdateImageAnalyzer();
    EXPECT_TRUE(pattern->isContentSizeChanged_);
}

/**
 * @tc.name: UpdateAnalyzerUIConfig001
 * @tc.desc: Test UpdateAnalyzerUIConfig.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, UpdateAnalyzerUIConfig001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(layoutProperty);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_TRUE(geometryNode);

    // Not supported => returns early
    pattern->UpdateAnalyzerUIConfig(geometryNode);

    // Supported => updates config
    auto imageAnalyzerManager =
        std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::VIDEO_CUSTOM);
    imageAnalyzerManager->SetSupportImageAnalyzerFeature(true);
    pattern->imageAnalyzerManager_ = imageAnalyzerManager;
    pattern->EnableAnalyzer(true);
    layoutProperty->UpdateControls(false);
    pattern->UpdateAnalyzerUIConfig(geometryNode);
    EXPECT_TRUE(pattern->isEnableAnalyzer_);
}

/**
 * @tc.name: SetImageAnalyzerConfig001
 * @tc.desc: Test SetImageAnalyzerConfig.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, SetImageAnalyzerConfig001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // No manager => no-op
    pattern->SetImageAnalyzerConfig(nullptr);

    // Enable analyzer => config set
    pattern->EnableAnalyzer(true);
    pattern->SetImageAnalyzerConfig(nullptr);
    EXPECT_TRUE(pattern->isEnableAnalyzer_);
}

/**
 * @tc.name: SetImageAIOptions001
 * @tc.desc: Test SetImageAIOptions.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, SetImageAIOptions001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // No manager => creates one
    EXPECT_EQ(pattern->imageAnalyzerManager_, nullptr);
    pattern->SetImageAIOptions(nullptr);
    EXPECT_NE(pattern->imageAnalyzerManager_, nullptr);

    // Existing manager => uses same manager
    auto existingManager = pattern->imageAnalyzerManager_;
    pattern->SetImageAIOptions(nullptr);
    EXPECT_EQ(pattern->imageAnalyzerManager_, existingManager);
}

/**
 * @tc.name: GetAnalyzerState001
 * @tc.desc: Test GetAnalyzerState.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, GetAnalyzerState001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // No manager => false
    EXPECT_FALSE(pattern->GetAnalyzerState());

    auto imageAnalyzerManager =
        std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::VIDEO_CUSTOM);
    pattern->imageAnalyzerManager_ = imageAnalyzerManager;

    imageAnalyzerManager->SetOverlayCreated(false);
    EXPECT_FALSE(pattern->GetAnalyzerState());

    imageAnalyzerManager->SetOverlayCreated(true);
    EXPECT_TRUE(pattern->GetAnalyzerState());
}

/**
 * @tc.name: UpdateAnalyzerState001
 * @tc.desc: Test UpdateAnalyzerState.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, UpdateAnalyzerState001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_FALSE(pattern->isAnalyzerCreated_);
    pattern->UpdateAnalyzerState(true);
    EXPECT_TRUE(pattern->isAnalyzerCreated_);
    pattern->UpdateAnalyzerState(false);
    EXPECT_FALSE(pattern->isAnalyzerCreated_);
}

/**
 * @tc.name: UpdateAnalyzerOverlay001
 * @tc.desc: Test UpdateAnalyzerOverlay returns early when no thumbnail.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, UpdateAnalyzerOverlay001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // No thumbnail pixelMap => returns early, no crash
    auto imageAnalyzerManager =
        std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::VIDEO_CUSTOM);
    pattern->imageAnalyzerManager_ = imageAnalyzerManager;
    pattern->EnableAnalyzer(true);
    pattern->UpdateAnalyzerOverlay();
    EXPECT_TRUE(pattern->isEnableAnalyzer_);
}

// Group 5: Inject/Other (36-45)

/**
 * @tc.name: GetCurrentPlaybackStatus001
 * @tc.desc: Test GetCurrentPlaybackStatus.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, GetCurrentPlaybackStatus001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->currentPlaybackStatus_ = PlaybackStatus::STARTED;
    EXPECT_EQ(pattern->GetCurrentPlaybackStatus(), PlaybackStatus::STARTED);

    pattern->currentPlaybackStatus_ = PlaybackStatus::PAUSED;
    EXPECT_EQ(pattern->GetCurrentPlaybackStatus(), PlaybackStatus::PAUSED);
}

/**
 * @tc.name: GetsIsProgressInjectCmd001
 * @tc.desc: Test GetsIsProgressInjectCmd.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, GetsIsProgressInjectCmd001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_FALSE(pattern->GetsIsProgressInjectCmd());
    pattern->isProgressInjectCmd_ = true;
    EXPECT_TRUE(pattern->GetsIsProgressInjectCmd());
}

/**
 * @tc.name: GetLastProgressRate001
 * @tc.desc: Test GetLastProgressRate.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, GetLastProgressRate001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_DOUBLE_EQ(pattern->GetLastProgressRate(), 0.0);
    pattern->lastProgressRate_ = 1.5;
    EXPECT_DOUBLE_EQ(pattern->GetLastProgressRate(), 1.5);
}

/**
 * @tc.name: GetLastSetProgressRate001
 * @tc.desc: Test GetLastSetProgressRate.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, GetLastSetProgressRate001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    EXPECT_DOUBLE_EQ(pattern->GetLastSetProgressRate(), 1.0);
    pattern->lastSetProgressRate_ = 2.0;
    EXPECT_DOUBLE_EQ(pattern->GetLastSetProgressRate(), 2.0);
}

/**
 * @tc.name: SetIsProgressInjectCmd001
 * @tc.desc: Test SetIsProgressInjectCmd.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, SetIsProgressInjectCmd001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->SetIsProgressInjectCmd(true);
    EXPECT_TRUE(pattern->isProgressInjectCmd_);
    pattern->SetIsProgressInjectCmd(false);
    EXPECT_FALSE(pattern->isProgressInjectCmd_);
}

/**
 * @tc.name: SetLastProgressRate001
 * @tc.desc: Test SetLastProgressRate.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, SetLastProgressRate001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->SetLastProgressRate(1.25);
    EXPECT_DOUBLE_EQ(pattern->lastProgressRate_, 1.25);
}

/**
 * @tc.name: SetLastSetProgressRate001
 * @tc.desc: Test SetLastSetProgressRate.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, SetLastSetProgressRate001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->SetLastSetProgressRate(0.5);
    EXPECT_DOUBLE_EQ(pattern->lastSetProgressRate_, 0.5);
}

/**
 * @tc.name: ParseCommand001
 * @tc.desc: Test ParseCommand different command parsing.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, ParseCommand001, TestSize.Level1)
{
    PlaybackStatus status = PlaybackStatus::NONE;
    double speed = 0.0;

    // Invalid JSON
    EXPECT_EQ(VideoStateMachinePattern::ParseCommand("invalid json", status, speed), RET_FAILED_VAL);

    // Unsupported cmdType
    EXPECT_EQ(VideoStateMachinePattern::ParseCommand(
        R"({"cmd":"unsupported","value":"play"})", status, speed), RET_FAILED_VAL);

    // Missing value
    EXPECT_EQ(VideoStateMachinePattern::ParseCommand(
        R"({"cmd":"setVideoPlayerStatus"})", status, speed), RET_FAILED_VAL);

    // setVideoPlayerStatus "play"
    EXPECT_EQ(VideoStateMachinePattern::ParseCommand(
        R"({"cmd":"setVideoPlayerStatus","value":"play"})", status, speed), RET_SUCCESS_VAL);
    EXPECT_EQ(status, PlaybackStatus::STARTED);

    // setVideoPlayerStatus "paused"
    EXPECT_EQ(VideoStateMachinePattern::ParseCommand(
        R"({"cmd":"setVideoPlayerStatus","value":"paused"})", status, speed), RET_SUCCESS_VAL);
    EXPECT_EQ(status, PlaybackStatus::PAUSED);

    // setVideoPlayerStatus invalid
    EXPECT_EQ(VideoStateMachinePattern::ParseCommand(
        R"({"cmd":"setVideoPlayerStatus","value":"invalid"})", status, speed), RET_FAILED_VAL);

    // setVideoPlaybackSpeed valid number
    EXPECT_EQ(VideoStateMachinePattern::ParseCommand(
        R"({"cmd":"setVideoPlaybackSpeed","value":1.5})", status, speed), RET_SUCCESS_VAL);
    EXPECT_DOUBLE_EQ(speed, 1.5);

    // setVideoPlaybackSpeed out of range
    EXPECT_EQ(VideoStateMachinePattern::ParseCommand(
        R"({"cmd":"setVideoPlaybackSpeed","value":10.0})", status, speed), RET_FAILED_VAL);

    // setVideoPlaybackSpeed non-number
    EXPECT_EQ(VideoStateMachinePattern::ParseCommand(
        R"({"cmd":"setVideoPlaybackSpeed","value":"fast"})", status, speed), RET_FAILED_VAL);
}

// Group 6: State Machine Callbacks (46-53)

/**
 * @tc.name: OnPlayingStateEntered001
 * @tc.desc: Test OnPlayingStateEntered fires start event.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnPlayingStateEntered001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto eventHub = pattern->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(eventHub);
    std::string startCheck;
    eventHub->SetOnStart([&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; });

    pattern->OnPlayingStateEntered();
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
}

/**
 * @tc.name: OnPausedStateEntered001
 * @tc.desc: Test OnPausedStateEntered fires pause event.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnPausedStateEntered001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto eventHub = pattern->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(eventHub);
    std::string pauseCheck;
    eventHub->SetOnPause([&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; });

    pattern->OnPausedStateEntered();
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);
}

/**
 * @tc.name: OnStoppedStateEntered001
 * @tc.desc: Test OnStoppedStateEntered resets position and fires stop event.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnStoppedStateEntered001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto eventHub = pattern->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(eventHub);
    std::string stopCheck;
    eventHub->SetOnStop([&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; });

    pattern->currentPos_ = 50;
    pattern->OnStoppedStateEntered();
    EXPECT_EQ(pattern->currentPos_, 0);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
}

/**
 * @tc.name: OnCompletedStateEntered001
 * @tc.desc: Test OnCompletedStateEntered sets currentPos to duration and fires finish event.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnCompletedStateEntered001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto eventHub = pattern->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(eventHub);
    std::string finishCheck;
    eventHub->SetOnFinish([&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; });

    pattern->duration_ = 120;
    pattern->currentPos_ = 50;
    pattern->OnCompletedStateEntered();
    EXPECT_EQ(pattern->currentPos_, 120);
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
}

/**
 * @tc.name: OnErrorStateEntered001
 * @tc.desc: Test OnErrorStateEntered fires error event.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnErrorStateEntered001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto eventHub = pattern->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(eventHub);
    std::string errorCheck;
    int32_t errorCode = 0;
    eventHub->SetOnError([&errorCheck, &errorCode](const std::string& param) {
        auto json = JsonUtil::ParseJsonString(param);
        if (json) {
            errorCode = json->GetInt("code");
            errorCheck = json->GetString("message");
        }
    });

    pattern->lastErrorCode_ = 404;
    pattern->lastErrorMessage_ = "Not Found";
    pattern->OnErrorStateEntered();
    EXPECT_EQ(errorCode, 404);
    EXPECT_EQ(errorCheck, "Not Found");
}

/**
 * @tc.name: TransitionTo001
 * @tc.desc: Test TransitionTo valid state transition.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, TransitionTo001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->stateManager_->state_ = VideoPlaybackState::CREATED;
    // CREATED -> PREPARED is valid
    EXPECT_TRUE(pattern->TransitionTo(VideoPlaybackState::PREPARED));
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), VideoPlaybackState::PREPARED);
}

/**
 * @tc.name: TransitionToIfAllowed001
 * @tc.desc: Test TransitionToIfAllowed allow/reject transitions.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, TransitionToIfAllowed001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // CREATED -> PREPARED is allowed
    pattern->stateManager_->state_ = VideoPlaybackState::CREATED;
    EXPECT_TRUE(pattern->TransitionToIfAllowed(VideoPlaybackState::PREPARED, "test"));
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), VideoPlaybackState::PREPARED);

    // PREPARED -> CREATED is allowed (reset scenario)
    EXPECT_TRUE(pattern->TransitionToIfAllowed(VideoPlaybackState::CREATED, "test"));
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), VideoPlaybackState::CREATED);
}

/**
 * @tc.name: OnAttachToFrameNodeMultiThread001
 * @tc.desc: Test OnAttachToFrameNodeMultiThread sets hostId.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnAttachToFrameNodeMultiThread001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    int32_t originalHostId = pattern->hostId_;
    pattern->OnAttachToFrameNodeMultiThread(frameNode);
    EXPECT_EQ(pattern->hostId_, frameNode->GetId());
    // hostId_ is already set by CreateVideoNode, so it won't change
    EXPECT_EQ(pattern->hostId_, originalHostId);
}
/**
 * @tc.name: ResetMediaPlayerOnBg001
 * @tc.desc: Test ResetMediaPlayerOnBg with valid mediaPlayer and callback.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, ResetMediaPlayerOnBg001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::CREATED;
    pattern->stateManager_->ClearPendingCommand();

    bool callbackCalled = false;
    bool callbackResult = false;
    auto callback = [&callbackCalled, &callbackResult](bool success, const std::string& msg) {
        callbackCalled = true;
        callbackResult = success;
    };

    pattern->ResetMediaPlayerOnBg(callback);
    EXPECT_EQ(pattern->stateManager_->GetPendingCommand(), VideoPlaybackCommand::RESET);
}

/**
 * @tc.name: ResetMediaPlayerOnBg002
 * @tc.desc: Test ResetMediaPlayerOnBg rejects when another reset is pending.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, ResetMediaPlayerOnBg002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::CREATED;
    pattern->stateManager_->SetPendingCommand(VideoPlaybackCommand::RESET, nullptr, VideoPlaybackCommand::RESET);

    bool callbackCalled = false;
    auto callback = [&callbackCalled](bool success, const std::string& msg) {
        callbackCalled = true;
    };

    pattern->ResetMediaPlayerOnBg(callback);
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap with skipMeasure true returns false.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    DirtySwapConfig config;
    config.skipMeasure = true;
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, nullptr, nullptr);
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(dirty, config));
}

/**
 * @tc.name: PrepareMediaPlayer001
 * @tc.desc: Test PrepareMediaPlayer when source has not changed.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, PrepareMediaPlayer001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);

    // No video source set
    videoLayoutProperty->ResetVideoSource();
    pattern->stateManager_->state_ = VideoPlaybackState::CREATED;
    pattern->PrepareMediaPlayer();
    // Should return early without changing state
    EXPECT_EQ(pattern->stateManager_->state_, VideoPlaybackState::CREATED);
}

/**
 * @tc.name: InitKeyEvent001
 * @tc.desc: Test InitKeyEvent registers key event handler.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, InitKeyEvent001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->InitKeyEvent();
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_TRUE(focusHub);
    // Key event handler should be registered
    EXPECT_TRUE(focusHub->FindContextMenuOnKeyEvent(OnKeyEventType::DEFAULT));
}

/**
 * @tc.name: MoveByStep001
 * @tc.desc: Test MoveByStep within valid range.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, MoveByStep001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->currentPos_ = 50;
    pattern->duration_ = 100;
    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;
    pattern->SetIsSeeking(false);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, Seek(60000, _)).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->MoveByStep(10);
    EXPECT_TRUE(pattern->GetIsSeeking());
    testing::Mock::VerifyAndClearExpectations(&(*mockMediaPlayer));
}

/**
 * @tc.name: MoveByStep002
 * @tc.desc: Test MoveByStep out of bounds does nothing.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, MoveByStep002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->currentPos_ = 0;
    pattern->duration_ = 100;

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, Seek(_, _)).Times(0);
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->MoveByStep(-10);
    EXPECT_EQ(pattern->currentPos_, 0);
}

/**
 * @tc.name: AdjustVolume001
 * @tc.desc: Test AdjustVolume within valid range.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, AdjustVolume001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->currentVolume_ = 0.5f;
    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, SetVolume(testing::_, testing::_)).Times(AnyNumber());
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->AdjustVolume(1);
    EXPECT_GT(pattern->currentVolume_, 0.5f);
}

/**
 * @tc.name: AdjustVolume002
 * @tc.desc: Test AdjustVolume out of bounds does nothing.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, AdjustVolume002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->currentVolume_ = 0.99f;
    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, SetVolume(_, _)).Times(0);
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->AdjustVolume(1);
    EXPECT_FLOAT_EQ(pattern->currentVolume_, 0.99f);
    // Should be clamped to max 1.0
}

// Group: Branch Coverage Supplement (69-83)

/**
 * @tc.name: OnPlayerStatus001
 * @tc.desc: Test OnPlayerStatus covers all PlaybackStatus branches.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnPlayerStatus001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;

    // STARTED from PREPARED
    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;
    pattern->isInitialState_ = true;
    pattern->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), VideoPlaybackState::PLAYING);
    EXPECT_FALSE(pattern->isInitialState_);
    EXPECT_EQ(pattern->GetCurrentPlaybackStatus(), PlaybackStatus::STARTED);

    // PAUSED from PLAYING
    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;
    pattern->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), VideoPlaybackState::PAUSED);
    EXPECT_EQ(pattern->GetCurrentPlaybackStatus(), PlaybackStatus::PAUSED);

    // STOPPED from PLAYING
    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;
    pattern->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), VideoPlaybackState::STOPPED);
    EXPECT_EQ(pattern->GetCurrentPlaybackStatus(), PlaybackStatus::STOPPED);

    // PLAYBACK_COMPLETE from PLAYING
    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;
    pattern->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE);
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), VideoPlaybackState::COMPLETED);
    EXPECT_EQ(pattern->GetCurrentPlaybackStatus(), PlaybackStatus::PLAYBACK_COMPLETE);

    // PREPARED from CREATED
    pattern->stateManager_->state_ = VideoPlaybackState::CREATED;
    pattern->OnPlayerStatus(PlaybackStatus::PREPARED);
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), VideoPlaybackState::PREPARED);
    EXPECT_EQ(pattern->GetCurrentPlaybackStatus(), PlaybackStatus::PREPARED);

    // ERROR (default branch)
    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;
    pattern->OnPlayerStatus(PlaybackStatus::ERROR);
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), VideoPlaybackState::PREPARED);
    EXPECT_EQ(pattern->GetCurrentPlaybackStatus(), PlaybackStatus::ERROR);

    // IDLE (default branch)
    pattern->OnPlayerStatus(PlaybackStatus::IDLE);
    EXPECT_EQ(pattern->GetCurrentPlaybackStatus(), PlaybackStatus::IDLE);

    // NONE (default branch)
    pattern->OnPlayerStatus(PlaybackStatus::NONE);
    EXPECT_EQ(pattern->GetCurrentPlaybackStatus(), PlaybackStatus::NONE);
}

/**
 * @tc.name: ChangePlayerStatus002
 * @tc.desc: Test ChangePlayerStatus for STARTED, PAUSED, PLAYBACK_COMPLETE, default.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, ChangePlayerStatus002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;

    // STARTED => PLAYING (from PREPARED state)
    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;
    pattern->ChangePlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), VideoPlaybackState::PLAYING);

    // PAUSED => PAUSED
    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;
    pattern->ChangePlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), VideoPlaybackState::PAUSED);

    // PLAYBACK_COMPLETE => COMPLETED
    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;
    pattern->ChangePlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE);
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), VideoPlaybackState::COMPLETED);

    // Default (NONE) => no state change
    pattern->stateManager_->state_ = VideoPlaybackState::CREATED;
    pattern->ChangePlayerStatus(PlaybackStatus::NONE);
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), VideoPlaybackState::CREATED);
}

/**
 * @tc.name: OnPreparedStateEntered001
 * @tc.desc: Test OnPreparedStateEntered with showFirstFrame and controlBar.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnPreparedStateEntered001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, GetDuration(_)).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->showFirstFrame_ = true;
    pattern->autoPlay_ = false;
    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;
    pattern->stateManager_->ClearPendingCommand();
    pattern->isInitialState_ = false;

    auto eventHub = pattern->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(eventHub);
    std::string preparedCheck;
    eventHub->SetOnPrepared([&preparedCheck](const std::string& /* param */) { preparedCheck = "prepared"; });

    pattern->OnPreparedStateEntered();
    EXPECT_EQ(preparedCheck, "prepared");
    EXPECT_TRUE(pattern->isInitialState_);
    EXPECT_EQ(pattern->stateManager_->GetPendingCommand(), VideoPlaybackCommand::NONE);
}

/**
 * @tc.name: OnPreparedStateEntered002
 * @tc.desc: Test OnPreparedStateEntered autoPlay and previousState=STOPPED branches.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnPreparedStateEntered002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, GetDuration(_)).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    // autoPlay=true branch
    pattern->autoPlay_ = true;
    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;
    pattern->stateManager_->ClearPendingCommand();
    pattern->OnPreparedStateEntered();
    EXPECT_EQ(pattern->stateManager_->GetPendingCommand(), VideoPlaybackCommand::PLAY);

    // previousState=STOPPED branch
    pattern->stateManager_->ClearPendingCommand();
    pattern->autoPlay_ = false;
    pattern->stateManager_->previousState_ = VideoPlaybackState::STOPPED;
    pattern->OnPreparedStateEntered();
    EXPECT_EQ(pattern->stateManager_->GetPendingCommand(), VideoPlaybackCommand::PLAY);
}

/**
 * @tc.name: OnKeyEvent001
 * @tc.desc: Test OnKeyEvent covers all key branches.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnKeyEvent001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableShortcutKey_ = true;
    pattern->currentPos_ = 50;
    pattern->duration_ = 100;

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, Seek(_, _)).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;
    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;

    // DPAD_LEFT
    KeyEvent leftEvent(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    EXPECT_TRUE(pattern->OnKeyEvent(leftEvent));

    // DPAD_RIGHT
    KeyEvent rightEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    EXPECT_TRUE(pattern->OnKeyEvent(rightEvent));

    // DPAD_UP
    KeyEvent upEvent(KeyCode::KEY_DPAD_UP, KeyAction::DOWN);
    EXPECT_TRUE(pattern->OnKeyEvent(upEvent));

    // DPAD_DOWN
    KeyEvent downEvent(KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN);
    EXPECT_TRUE(pattern->OnKeyEvent(downEvent));

    // KEY_SPACE
    KeyEvent spaceEvent(KeyCode::KEY_SPACE, KeyAction::DOWN);
    EXPECT_TRUE(pattern->OnKeyEvent(spaceEvent));

    // disabled shortcut key
    pattern->isEnableShortcutKey_ = false;
    EXPECT_FALSE(pattern->OnKeyEvent(leftEvent));

    // UP action
    pattern->isEnableShortcutKey_ = true;
    KeyEvent upActionEvent(KeyCode::KEY_DPAD_LEFT, KeyAction::UP);
    EXPECT_FALSE(pattern->OnKeyEvent(upActionEvent));
}

/**
 * @tc.name: HiddenChange001
 * @tc.desc: Test HiddenChange hidden=true/false and pastPlayingStatus_ branches.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, HiddenChange001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, Pause()).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    // hidden=true while playing
    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;
    pattern->pastPlayingStatus_ = false;
    pattern->HiddenChange(true);
    EXPECT_TRUE(pattern->pastPlayingStatus_);

    // hidden=false with pastPlayingStatus_=true
    pattern->HiddenChange(false);
    EXPECT_FALSE(pattern->pastPlayingStatus_);

    // hidden=true while not playing
    pattern->stateManager_->state_ = VideoPlaybackState::PAUSED;
    pattern->pastPlayingStatus_ = false;
    pattern->HiddenChange(true);
    EXPECT_FALSE(pattern->pastPlayingStatus_);
}

/**
 * @tc.name: OnVisibleChange001
 * @tc.desc: Test OnVisibleChange visible=true/false.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnVisibleChange001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    bool visibleResult = false;
    pattern->SetHiddenChangeEvent([&visibleResult](bool hidden) { visibleResult = hidden; });

    // visible=true => hidden=false
    pattern->OnVisibleChange(true);
    EXPECT_FALSE(visibleResult);

    // visible=false => hidden=true
    pattern->OnVisibleChange(false);
    EXPECT_TRUE(visibleResult);

    // null event
    pattern->SetHiddenChangeEvent(nullptr);
    pattern->OnVisibleChange(true);
    EXPECT_TRUE(pattern->hiddenChangeEvent_ == nullptr);
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Test ToJsonValue with enableShortcutKey and IsFastFilter.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, ToJsonValue001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableShortcutKey_ = true;
    pattern->progressRate_ = 1.5;

    // Normal case
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    pattern->ToJsonValue(json, filter);
    EXPECT_FALSE(filter.IsFastFilter());
    EXPECT_EQ(json->GetValue("enableShortcutKey")->GetString(), "true");

    // Fast filter case
    InspectorFilter fastFilter;
    fastFilter.AddFilterAttr("id");
    auto jsonFast = JsonUtil::Create(true);
    pattern->ToJsonValue(jsonFast, fastFilter);
    EXPECT_TRUE(fastFilter.IsFastFilter());
    EXPECT_FALSE(jsonFast->Contains("enableShortcutKey"));
}

/**
 * @tc.name: OnError001
 * @tc.desc: Test OnError with empty string and custom error code.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnError001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // Empty string => "Unknown error"
    pattern->stateManager_->state_ = VideoPlaybackState::CREATED;
    pattern->OnError("");
    EXPECT_EQ(pattern->lastErrorMessage_, "Unknown error");
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), VideoPlaybackState::ERROR);

    // Custom error code and message
    pattern->stateManager_->state_ = VideoPlaybackState::CREATED;
    pattern->OnError(404, "Not Found");
    EXPECT_EQ(pattern->lastErrorCode_, 404);
    EXPECT_EQ(pattern->lastErrorMessage_, "Not Found");
    EXPECT_EQ(pattern->stateManager_->GetCurrentState(), VideoPlaybackState::ERROR);
}

/**
 * @tc.name: SetCurrentTime001
 * @tc.desc: Test SetCurrentTime with negative time and showFirstFrame=false.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, SetCurrentTime001, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, Seek(_, _)).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;

    // Negative time => should not seek
    pattern->SetIsSeeking(false);
    pattern->SetCurrentTime(-1.0f, OHOS::Ace::SeekMode::SEEK_CLOSEST);
    EXPECT_FALSE(pattern->GetIsSeeking());

    // Positive time with showFirstFrame=false => UpdatePreparedVideoSize + Seek
    mockMediaPlayer->videoWidth_ = 100;
    mockMediaPlayer->videoHeight_ = 100;
    pattern->showFirstFrame_ = false;
    pattern->SetCurrentTime(10.0f, OHOS::Ace::SeekMode::SEEK_CLOSEST);
    EXPECT_TRUE(pattern->GetIsSeeking());
    testing::Mock::VerifyAndClearExpectations(&(*mockMediaPlayer));
}

/**
 * @tc.name: PrepareMediaPlayer002
 * @tc.desc: Test PrepareMediaPlayer when source has changed.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, PrepareMediaPlayer002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);

    // Set source in layout property different from videoSrcInfo_
    VideoSourceInfo srcInfo;
    srcInfo.src_ = "new_video.mp4";
    videoLayoutProperty->UpdateVideoSource(srcInfo);
    pattern->videoSrcInfo_.src_ = "old_video.mp4";
    pattern->stateManager_->state_ = VideoPlaybackState::CREATED;
    pattern->stateManager_->ClearPendingCommand();

    // Source changed => should trigger reset
    pattern->PrepareMediaPlayer();
    EXPECT_EQ(pattern->videoSrcInfo_.src_, "new_video.mp4");
    EXPECT_EQ(pattern->stateManager_->GetPendingCommand(), VideoPlaybackCommand::RESET);
}

/**
 * @tc.name: UpdateMediaPlayerOnBg002
 * @tc.desc: Test UpdateMediaPlayerOnBg with autoPlay + isInitialState_.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, UpdateMediaPlayerOnBg002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->isInitialState_ = true;
    pattern->autoPlay_ = true;
    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;
    pattern->stateManager_->ClearPendingCommand();

    pattern->UpdateMediaPlayerOnBg();
    EXPECT_EQ(pattern->stateManager_->GetPendingCommand(), VideoPlaybackCommand::PLAY);
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: Test OnModifyDone image analyzer branch.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnModifyDone002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(layoutProperty);

    // Set up image analyzer
    auto imageAnalyzerManager =
        std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::VIDEO_CUSTOM);
    imageAnalyzerManager->SetSupportImageAnalyzerFeature(true);
    pattern->imageAnalyzerManager_ = imageAnalyzerManager;
    pattern->EnableAnalyzer(true);
    layoutProperty->UpdateControls(false);

    // Set state to PAUSED to trigger StartImageAnalyzer branch
    pattern->stateManager_->state_ = VideoPlaybackState::PAUSED;
    pattern->OnModifyDone();
    EXPECT_TRUE(pattern->isEnableAnalyzer_);
}

/**
 * @tc.name: OnAreaChangedInner002
 * @tc.desc: Test OnAreaChangedInner with ExtSurface disabled.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnAreaChangedInner002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    // With ExtSurface disabled => should return early
    auto oldExtSurface = SystemProperties::GetExtSurfaceEnabled();
    SystemProperties::SetExtSurfaceEnabled(false);
    pattern->lastBoundsRect_ = Rect();
    pattern->OnAreaChangedInner();
    EXPECT_FLOAT_EQ(pattern->lastBoundsRect_.Width(), 0.0f);
    SystemProperties::SetExtSurfaceEnabled(oldExtSurface);
}

} // namespace OHOS::Ace::NG
