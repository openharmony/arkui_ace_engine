/*
 * Copyright (c) 2022-2026 Huawei Device Co., Ltd.
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
#include "test/mock/frameworks/core/common/mock_image_analyzer_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {

class PlatformVersionGuard {
public:
    explicit PlatformVersionGuard(int32_t targetVersion)
    {
        original_ = MockPipelineContext::GetCurrent()->GetMinPlatformVersion();
        MockPipelineContext::GetCurrent()->SetMinPlatformVersion(targetVersion);
    }
    ~PlatformVersionGuard()
    {
        MockPipelineContext::GetCurrent()->SetMinPlatformVersion(original_);
    }
private:
    int32_t original_ = 0;
};

constexpr uint32_t TEST_TIME_OVER_HOUR = 3661;
constexpr uint32_t TEST_TIME_UNDER_HOUR = 61;
constexpr float TEST_VIDEO_WIDTH = 200.0f;
constexpr float TEST_VIDEO_HEIGHT = 100.0f;

constexpr double TEST_PROGRESS_RATE_LOW = 0.1;
constexpr double TEST_PROGRESS_RATE_HIGH = 9.0;
constexpr int32_t ERROR_CODE_SUCCESS = 0;
constexpr int32_t ERROR_CODE_INVALID_VAL = 401;
constexpr int32_t ERROR_CODE_INVALID_OPERATION = 5400102;
constexpr int32_t ERROR_CODE_UNKNOWN = 999;
constexpr float TEST_NEGATIVE_TIME = -1.0f;
constexpr float TEST_VALID_TIME = 5.0f;

constexpr uint32_t POS_CURRENT = 1;
constexpr uint32_t POS_DURATION = 3;
constexpr uint32_t POS_FULL_SCREEN = 4;
constexpr int32_t MEDIA_TYPE_AUDIO = 0;
constexpr int32_t SLIDER_MODE_BEGIN = 0;
constexpr int32_t SLIDER_MODE_MOVING = 1;
constexpr int32_t SLIDER_MODE_END = 2;
} // namespace


/**
 * @tc.name: OnUpdateTime_TimeOverHour001
 * @tc.desc: Test IntTimeToText formats time >= 3600 as HH:MM:SS.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnUpdateTime_TimeOverHour001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->OnUpdateTime(TEST_TIME_OVER_HOUR, POS_DURATION);
}

/**
 * @tc.name: OnUpdateTime_TimeUnderHour001
 * @tc.desc: Test IntTimeToText formats time < 3600 as MM:SS.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnUpdateTime_TimeUnderHour001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->OnUpdateTime(TEST_TIME_UNDER_HOUR, POS_DURATION);
}


/**
 * @tc.name: OnDirtyLayoutWrapperSwap_Cover001
 * @tc.desc: Test MeasureVideoContentLayout with ImageFit::COVER.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_Cover001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateVideoSize(SizeF(TEST_VIDEO_WIDTH, TEST_VIDEO_HEIGHT));
    videoLayoutProperty->UpdateObjectFit(ImageFit::COVER);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_None001
 * @tc.desc: Test MeasureVideoContentLayout with ImageFit::NONE.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_None001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateVideoSize(SizeF(TEST_VIDEO_WIDTH, TEST_VIDEO_HEIGHT));
    videoLayoutProperty->UpdateObjectFit(ImageFit::NONE);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_ScaleDown001
 * @tc.desc: Test MeasureVideoContentLayout with ImageFit::SCALE_DOWN (layout larger than video).
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_ScaleDown001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateVideoSize(SizeF(TEST_VIDEO_WIDTH, TEST_VIDEO_HEIGHT));
    videoLayoutProperty->UpdateObjectFit(ImageFit::SCALE_DOWN);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_ScaleDown002
 * @tc.desc: Test MeasureVideoContentLayout with ImageFit::SCALE_DOWN (layout smaller than video).
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_ScaleDown002, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateVideoSize(SizeF(800.0f, 800.0f));
    videoLayoutProperty->UpdateObjectFit(ImageFit::SCALE_DOWN);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_TopLeft001
 * @tc.desc: Test MeasureVideoContentLayout with ImageFit::TOP_LEFT.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_TopLeft001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateVideoSize(SizeF(TEST_VIDEO_WIDTH, TEST_VIDEO_HEIGHT));
    videoLayoutProperty->UpdateObjectFit(ImageFit::TOP_LEFT);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_Top001
 * @tc.desc: Test MeasureVideoContentLayout with ImageFit::TOP.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_Top001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateVideoSize(SizeF(TEST_VIDEO_WIDTH, TEST_VIDEO_HEIGHT));
    videoLayoutProperty->UpdateObjectFit(ImageFit::TOP);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_TopEnd001
 * @tc.desc: Test MeasureVideoContentLayout with ImageFit::TOP_END.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_TopEnd001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateVideoSize(SizeF(TEST_VIDEO_WIDTH, TEST_VIDEO_HEIGHT));
    videoLayoutProperty->UpdateObjectFit(ImageFit::TOP_END);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_Start001
 * @tc.desc: Test MeasureVideoContentLayout with ImageFit::START.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_Start001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateVideoSize(SizeF(TEST_VIDEO_WIDTH, TEST_VIDEO_HEIGHT));
    videoLayoutProperty->UpdateObjectFit(ImageFit::START);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_Center001
 * @tc.desc: Test MeasureVideoContentLayout with ImageFit::CENTER.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_Center001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateVideoSize(SizeF(TEST_VIDEO_WIDTH, TEST_VIDEO_HEIGHT));
    videoLayoutProperty->UpdateObjectFit(ImageFit::CENTER);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_End001
 * @tc.desc: Test MeasureVideoContentLayout with ImageFit::END.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_End001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateVideoSize(SizeF(TEST_VIDEO_WIDTH, TEST_VIDEO_HEIGHT));
    videoLayoutProperty->UpdateObjectFit(ImageFit::END);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_BottomStart001
 * @tc.desc: Test MeasureVideoContentLayout with ImageFit::BOTTOM_START.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_BottomStart001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateVideoSize(SizeF(TEST_VIDEO_WIDTH, TEST_VIDEO_HEIGHT));
    videoLayoutProperty->UpdateObjectFit(ImageFit::BOTTOM_START);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_Bottom001
 * @tc.desc: Test MeasureVideoContentLayout with ImageFit::BOTTOM.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_Bottom001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateVideoSize(SizeF(TEST_VIDEO_WIDTH, TEST_VIDEO_HEIGHT));
    videoLayoutProperty->UpdateObjectFit(ImageFit::BOTTOM);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_BottomEnd001
 * @tc.desc: Test MeasureVideoContentLayout with ImageFit::BOTTOM_END.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_BottomEnd001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateVideoSize(SizeF(TEST_VIDEO_WIDTH, TEST_VIDEO_HEIGHT));
    videoLayoutProperty->UpdateObjectFit(ImageFit::BOTTOM_END);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_DefaultFit001
 * @tc.desc: Test MeasureVideoContentLayout with unsupported ImageFit falls back to COVER.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_DefaultFit001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateVideoSize(SizeF(TEST_VIDEO_WIDTH, TEST_VIDEO_HEIGHT));
    videoLayoutProperty->UpdateObjectFit(ImageFit::FILL);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_NearZeroContain001
 * @tc.desc: Test CalculateFitContain NearZero branches (zero layout height).
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_NearZeroContain001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateVideoSize(SizeF(TEST_VIDEO_WIDTH, TEST_VIDEO_HEIGHT));
    videoLayoutProperty->UpdateObjectFit(ImageFit::CONTAIN);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_SourceRatioLessThanLayoutRatio001
 * @tc.desc: Test CalculateFitContain when sourceRatio < layoutRatio.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_SourceRatioLessThanLayoutRatio001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateVideoSize(SizeF(TEST_VIDEO_HEIGHT, TEST_VIDEO_WIDTH));
    videoLayoutProperty->UpdateObjectFit(ImageFit::CONTAIN);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}


/**
 * @tc.name: OnDirtyLayoutWrapperSwap_VersionTwelve001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap with VERSION_TWELVE AdjustPaintRect branch.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_VersionTwelve001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateObjectFit(ImageFit::COVER);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_NonCoverNoneImageFit001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap with non-COVER/NONE imageFit branch for analyzer rect.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_NonCoverNoneImageFit001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->UpdateObjectFit(ImageFit::CONTAIN);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}


/**
 * @tc.name: OnPlayerStatus_DefaultBranch001
 * @tc.desc: Test OnPlayerStatus with unknown status exercises StatusToString default branch.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnPlayerStatus_DefaultBranch001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->OnPlayerStatus(static_cast<PlaybackStatus>(999));
}


/**
 * @tc.name: OnCreatedStateEntered_PrepareAsyncFail001
 * @tc.desc: Test OnCreatedStateEntered clears pending command when PrepareAsync fails.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnCreatedStateEntered_PrepareAsyncFail001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, PrepareAsync()).WillRepeatedly(Return(-1));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->ClearPendingCommand();
    pattern->OnCreatedStateEntered();
    EXPECT_EQ(pattern->stateManager_->GetPendingCommand(), VideoPlaybackCommand::NONE);
}


/**
 * @tc.name: OnPreparedStateEntered_OriginalIntentPlay001
 * @tc.desc: Test OnPreparedStateEntered originalIntent==PLAY async branch.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnPreparedStateEntered_OriginalIntentPlay001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, GetDuration(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*mockMediaPlayer, Play()).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::PREPARED;
    pattern->stateManager_->originalIntent_ = VideoPlaybackCommand::PLAY;
    pattern->stateManager_->previousState_ = VideoPlaybackState::CREATED;
    pattern->stateManager_->ClearPendingCommand();

    pattern->OnPreparedStateEntered();
    EXPECT_EQ(pattern->stateManager_->GetPendingCommand(), VideoPlaybackCommand::PLAY);
}

/**
 * @tc.name: OnPreparedStateEntered_FromStopped001
 * @tc.desc: Test OnPreparedStateEntered previousState==STOPPED branch triggers Start.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnPreparedStateEntered_FromStopped001, TestSize.Level0)
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
 * @tc.name: OnPreparedStateEntered_AutoPlay001
 * @tc.desc: Test OnPreparedStateEntered autoPlay branch triggers Start.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnPreparedStateEntered_AutoPlay001, TestSize.Level0)
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
 * @tc.name: RegisterMediaPlayerEvent_EmptySrc001
 * @tc.desc: Test RegisterMediaPlayerEvent returns early when src is empty.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, RegisterMediaPlayerEvent_EmptySrc001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));

    WeakPtr<VideoStateMachinePattern> weak(pattern);
    VideoStateMachinePattern::RegisterMediaPlayerEvent(weak, mockMediaPlayer, "", pattern->instanceId_);
}

/**
 * @tc.name: RegisterMediaPlayerEvent_NullMediaPlayer001
 * @tc.desc: Test RegisterMediaPlayerEvent returns early when mediaPlayer is null.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, RegisterMediaPlayerEvent_NullMediaPlayer001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    WeakPtr<VideoStateMachinePattern> weak(pattern);
    VideoStateMachinePattern::RegisterMediaPlayerEvent(weak, nullptr, "test.mp4", pattern->instanceId_);
}


/**
 * @tc.name: OnCurrentTimeChange_DurationZero001
 * @tc.desc: Test OnCurrentTimeChange fetches duration when duration_ is 0.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnCurrentTimeChange_DurationZero001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, GetDuration(_)).WillRepeatedly([](int32_t& duration) {
        duration = 60000;
        return 0;
    });
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->duration_ = 0;
    pattern->currentPos_ = 0;
    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;
    pattern->isSeeking_ = false;

    pattern->OnCurrentTimeChange(10);
    EXPECT_EQ(pattern->duration_, 60);
}


/**
 * @tc.name: HandleSetPlaybackRateResult_Success001
 * @tc.desc: Test HandleSetPlaybackRateResult with SUCCESS error code.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, HandleSetPlaybackRateResult_Success001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    std::string errorMsg = "";
    pattern->HandleSetPlaybackRateResult(1.0, ERROR_CODE_SUCCESS, errorMsg);
}

/**
 * @tc.name: HandleSetPlaybackRateResult_InvalidVal001
 * @tc.desc: Test HandleSetPlaybackRateResult with MSERR_INVALID_VAL error code.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, HandleSetPlaybackRateResult_InvalidVal001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, SetPlaybackRate(_, _, _)).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    std::string errorMsg = "";
    pattern->HandleSetPlaybackRateResult(1.0, ERROR_CODE_INVALID_VAL, errorMsg);
}

/**
 * @tc.name: HandleSetPlaybackRateResult_InvalidOperation001
 * @tc.desc: Test HandleSetPlaybackRateResult with MSERR_INVALID_OPERATION error code.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, HandleSetPlaybackRateResult_InvalidOperation001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    std::string errorMsg = "";
    pattern->HandleSetPlaybackRateResult(1.0, ERROR_CODE_INVALID_OPERATION, errorMsg);
}

/**
 * @tc.name: HandleSetPlaybackRateResult_Default001
 * @tc.desc: Test HandleSetPlaybackRateResult with default/unknown error code.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, HandleSetPlaybackRateResult_Default001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, SetPlaybackRate(_, _, _)).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    std::string errorMsg = "";
    pattern->HandleSetPlaybackRateResult(1.0, ERROR_CODE_UNKNOWN, errorMsg);
}


/**
 * @tc.name: UpdateLooping_BackgroundTask001
 * @tc.desc: Test UpdateLooping posts background task when mediaPlayer is valid.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, UpdateLooping_BackgroundTask001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, SetLooping(_)).Times(AtLeast(0));
    pattern->mediaPlayer_ = mockMediaPlayer;
    pattern->loop_ = true;

    pattern->UpdateLooping();
    EXPECT_TRUE(pattern->loop_);
}


/**
 * @tc.name: UpdateSpeed_BackgroundTask001
 * @tc.desc: Test UpdateSpeed posts background task with out-of-range progress rate.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, UpdateSpeed_BackgroundTask001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, SetPlaybackRate(_, _, _)).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;
    pattern->progressRate_ = TEST_PROGRESS_RATE_HIGH;

    pattern->UpdateSpeed();
    EXPECT_EQ(pattern->progressRate_, TEST_PROGRESS_RATE_HIGH);
}

/**
 * @tc.name: UpdateSpeed_BackgroundTaskLowRate001
 * @tc.desc: Test UpdateSpeed posts background task with low progress rate.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, UpdateSpeed_BackgroundTaskLowRate001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, SetPlaybackRate(_, _, _)).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;
    pattern->progressRate_ = TEST_PROGRESS_RATE_LOW;

    pattern->UpdateSpeed();
    EXPECT_EQ(pattern->progressRate_, TEST_PROGRESS_RATE_LOW);
}


/**
 * @tc.name: UpdateMuted_BackgroundTask001
 * @tc.desc: Test UpdateMuted posts background task when mediaPlayer is valid.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, UpdateMuted_BackgroundTask001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, SetMediaMuted(_, _)).Times(AtLeast(0));
    pattern->mediaPlayer_ = mockMediaPlayer;
    pattern->muted_ = true;

    pattern->UpdateMuted();
    EXPECT_TRUE(pattern->muted_);
}


/**
 * @tc.name: OnUpdateTime_SliderUpdate001
 * @tc.desc: Test OnUpdateTime updates slider when pos==CURRENT_POS and not seeking.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnUpdateTime_SliderUpdate001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    pattern->isSeeking_ = false;

    pattern->OnUpdateTime(30, POS_CURRENT);
}

/**
 * @tc.name: OnUpdateTime_SliderUpdateSeeking001
 * @tc.desc: Test OnUpdateTime skips slider update when seeking.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnUpdateTime_SliderUpdateSeeking001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);
    pattern->isSeeking_ = true;

    pattern->OnUpdateTime(30, POS_CURRENT);
}


/**
 * @tc.name: OnAttachToMainTree_ImagePerf001
 * @tc.desc: Test OnAttachToMainTree with showFirstFrame=true triggers ImagePerf.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnAttachToMainTree_ImagePerf001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->showFirstFrame_ = true;
    pattern->OnAttachToMainTree();
}

/**
 * @tc.name: OnAttachToMainTree_VideoControllerAsync001
 * @tc.desc: Test OnAttachToMainTree sets videoControllerAsync pattern for non-fullscreen.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnAttachToMainTree_VideoControllerAsync001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    ASSERT_TRUE(pattern->videoControllerAsync_);
    pattern->OnAttachToMainTree();
}


/**
 * @tc.name: OnDetachFromMainTree_BuilderNodeOffMainTree001
 * @tc.desc: Test OnDetachFromMainTree with BUILDER_NODE_OFF_MAINTREE pauses video.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDetachFromMainTree_BuilderNodeOffMainTree001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    frameNode->UpdateNodeStatus(NodeStatus::BUILDER_NODE_OFF_MAINTREE);
    pattern->OnDetachFromMainTree();
}

/**
 * @tc.name: OnDetachFromMainTree_PipelineCallbackRemoval001
 * @tc.desc: Test OnDetachFromMainTree removes window state changed callback.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDetachFromMainTree_PipelineCallbackRemoval001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    frameNode->UpdateNodeStatus(NodeStatus::NORMAL_NODE);
    pattern->OnDetachFromMainTree();
}


/**
 * @tc.name: OnModifyDone_VersionTwelve001
 * @tc.desc: Test OnModifyDone with VERSION_TWELVE platform.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnModifyDone_VersionTwelve001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    pattern->OnModifyDone();
}

/**
 * @tc.name: OnModifyDone_HiddenChangeEvent001
 * @tc.desc: Test OnModifyDone creates hiddenChangeEvent.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnModifyDone_HiddenChangeEvent001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->hiddenChangeEvent_ = nullptr;
    pattern->OnModifyDone();
    EXPECT_NE(pattern->hiddenChangeEvent_, nullptr);
}

/**
 * @tc.name: OnModifyDone_FullScreenNodeIdRecovery001
 * @tc.desc: Test OnModifyDone recovers fullScreenNodeId when valid.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnModifyDone_FullScreenNodeIdRecovery001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->fullScreenNodeId_ = frameNode->GetId();
    pattern->OnModifyDone();
    EXPECT_TRUE(pattern->fullScreenNodeId_.has_value());
}

/**
 * @tc.name: OnModifyDone_ImageAnalyzerNotSupported001
 * @tc.desc: Test OnModifyDone destroys analyzer when not supported.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnModifyDone_ImageAnalyzerNotSupported001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableAnalyzer_ = true;
    pattern->OnModifyDone();
}


/**
 * @tc.name: InitKeyEvent_Registration001
 * @tc.desc: Test InitKeyEvent registers key event handler.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, InitKeyEvent_Registration001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->InitKeyEvent();
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_TRUE(focusHub);
}

/**
 * @tc.name: OnKeyEvent_DpadLeft001
 * @tc.desc: Test OnKeyEvent handles KEY_DPAD_LEFT.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnKeyEvent_DpadLeft001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableShortcutKey_ = true;
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_DPAD_LEFT;

    auto result = pattern->OnKeyEvent(event);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnKeyEvent_DpadRight001
 * @tc.desc: Test OnKeyEvent handles KEY_DPAD_RIGHT.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnKeyEvent_DpadRight001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableShortcutKey_ = true;
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_DPAD_RIGHT;

    auto result = pattern->OnKeyEvent(event);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnKeyEvent_DpadUp001
 * @tc.desc: Test OnKeyEvent handles KEY_DPAD_UP.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnKeyEvent_DpadUp001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableShortcutKey_ = true;
    pattern->currentVolume_ = 0.5f;
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_DPAD_UP;

    auto result = pattern->OnKeyEvent(event);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnKeyEvent_DpadDown001
 * @tc.desc: Test OnKeyEvent handles KEY_DPAD_DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnKeyEvent_DpadDown001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableShortcutKey_ = true;
    pattern->currentVolume_ = 0.5f;
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_DPAD_DOWN;

    auto result = pattern->OnKeyEvent(event);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnKeyEvent_KeySpace001
 * @tc.desc: Test OnKeyEvent handles KEY_SPACE.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnKeyEvent_KeySpace001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableShortcutKey_ = true;
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_SPACE;

    auto result = pattern->OnKeyEvent(event);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnKeyEvent_Disabled001
 * @tc.desc: Test OnKeyEvent returns false when shortcut key is disabled.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnKeyEvent_Disabled001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableShortcutKey_ = false;
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_SPACE;

    auto result = pattern->OnKeyEvent(event);
    EXPECT_FALSE(result);
}


/**
 * @tc.name: HandleSliderKeyEvent_KeySpace001
 * @tc.desc: Test HandleSliderKeyEvent handles KEY_SPACE.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, HandleSliderKeyEvent_KeySpace001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableShortcutKey_ = true;
    KeyEventInfo eventInfo(KeyEvent(KeyCode::KEY_SPACE, KeyAction::DOWN));

    auto result = pattern->HandleSliderKeyEvent(eventInfo);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HandleSliderKeyEvent_NotSpace001
 * @tc.desc: Test HandleSliderKeyEvent returns false for non-space keys.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, HandleSliderKeyEvent_NotSpace001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableShortcutKey_ = true;
    KeyEventInfo eventInfo(KeyEvent(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN));

    auto result = pattern->HandleSliderKeyEvent(eventInfo);
    EXPECT_FALSE(result);
}


/**
 * @tc.name: UpdatePreviewImage_PosterNotValid001
 * @tc.desc: Test UpdatePreviewImage with invalid poster source.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, UpdatePreviewImage_PosterNotValid001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto layoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(layoutProperty);
    ImageSourceInfo invalidPoster("");
    layoutProperty->UpdatePosterImageInfo(invalidPoster);
    pattern->showFirstFrame_ = false;
    pattern->isInitialState_ = true;

    pattern->UpdatePreviewImage();
}

/**
 * @tc.name: UpdatePreviewImage_ContentTransition001
 * @tc.desc: Test UpdatePreviewImage with contentTransition != IDENTITY.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, UpdatePreviewImage_ContentTransition001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto layoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(layoutProperty);
    ImageSourceInfo poster("common/poster.png");
    layoutProperty->UpdatePosterImageInfo(poster);
    pattern->showFirstFrame_ = false;
    pattern->isInitialState_ = true;
    pattern->contentTransition_ = ContentTransitionType::OPACITY;

    pattern->UpdatePreviewImage();
}


/**
 * @tc.name: UpdateControllerBar_NoControlBar001
 * @tc.desc: Test UpdateControllerBar with controls=false.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, UpdateControllerBar_NoControlBar001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto layoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(layoutProperty);
    layoutProperty->UpdateControls(false);

    pattern->UpdateControllerBar();
}


/**
 * @tc.name: Start_InvalidMediaPlayer001
 * @tc.desc: Test Start returns early when mediaPlayer is invalid.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, Start_InvalidMediaPlayer001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto invalidMock = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*invalidMock, IsMediaPlayerValid()).WillRepeatedly(Return(false));
    pattern->mediaPlayer_ = invalidMock;

    pattern->Start();
}

/**
 * @tc.name: Start_InvalidState001
 * @tc.desc: Test Start returns early when state transition is invalid.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, Start_InvalidState001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::ERROR;
    pattern->stateManager_->ClearPendingCommand();

    pattern->Start();
}

/**
 * @tc.name: Start_CannotSetPending001
 * @tc.desc: Test Start returns early when cannot set pending command.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, Start_CannotSetPending001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;
    pattern->stateManager_->SetPendingCommand(VideoPlaybackCommand::PLAY, nullptr);

    pattern->Start();
}

/**
 * @tc.name: Start_FromStopped001
 * @tc.desc: Test Start from STOPPED state triggers PrepareAsync.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, Start_FromStopped001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, PrepareAsync()).WillRepeatedly(Return(0));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::STOPPED;
    pattern->stateManager_->ClearPendingCommand();

    pattern->Start();
    EXPECT_EQ(pattern->stateManager_->GetPendingCommand(), VideoPlaybackCommand::PREPARE);
}

/**
 * @tc.name: Start_PrepareAsyncFail001
 * @tc.desc: Test Start from STOPPED clears pending when PrepareAsync fails.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, Start_PrepareAsyncFail001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, PrepareAsync()).WillRepeatedly(Return(-1));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::STOPPED;
    pattern->stateManager_->ClearPendingCommand();

    pattern->Start();
    EXPECT_EQ(pattern->stateManager_->GetPendingCommand(), VideoPlaybackCommand::NONE);
}


/**
 * @tc.name: Pause_InvalidMediaPlayer001
 * @tc.desc: Test Pause returns early when mediaPlayer is invalid.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, Pause_InvalidMediaPlayer001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto invalidMock = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*invalidMock, IsMediaPlayerValid()).WillRepeatedly(Return(false));
    pattern->mediaPlayer_ = invalidMock;

    pattern->Pause();
}

/**
 * @tc.name: Pause_InvalidState001
 * @tc.desc: Test Pause returns early when state transition is invalid.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, Pause_InvalidState001, TestSize.Level0)
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

    pattern->Pause();
}

/**
 * @tc.name: Pause_CannotSetPending001
 * @tc.desc: Test Pause returns early when cannot set pending command.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, Pause_CannotSetPending001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::PAUSED;
    pattern->stateManager_->SetPendingCommand(VideoPlaybackCommand::PAUSE, nullptr);

    pattern->Pause();
}


/**
 * @tc.name: Stop_InvalidMediaPlayer001
 * @tc.desc: Test Stop returns early when mediaPlayer is invalid.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, Stop_InvalidMediaPlayer001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto invalidMock = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*invalidMock, IsMediaPlayerValid()).WillRepeatedly(Return(false));
    pattern->mediaPlayer_ = invalidMock;

    pattern->Stop();
}

/**
 * @tc.name: Stop_InvalidState001
 * @tc.desc: Test Stop returns early when state transition is invalid.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, Stop_InvalidState001, TestSize.Level0)
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

    pattern->Stop();
}

/**
 * @tc.name: Stop_CannotSetPending001
 * @tc.desc: Test Stop returns early when cannot set pending command.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, Stop_CannotSetPending001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::STOPPED;
    pattern->stateManager_->SetPendingCommand(VideoPlaybackCommand::STOP, nullptr);

    pattern->Stop();
}


/**
 * @tc.name: FireError_UiThreadExecution001
 * @tc.desc: Test FireError executes on UI thread when not already on UI thread.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, FireError_UiThreadExecution001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->FireError(ERROR_CODE_VIDEO_SOURCE_INVALID, "test error");
}


/**
 * @tc.name: ChangePlayButtonTag_ClickCallback001
 * @tc.desc: Test ChangePlayButtonTag sets click callback for play/pause toggle.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, ChangePlayButtonTag_ClickCallback001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto host = frameNode;
    const auto& children = host->GetChildren();
    for (const auto& child : children) {
        if (child->GetTag() == V2::ROW_ETS_TAG) {
            auto playBtn = AceType::DynamicCast<FrameNode>(child->GetChildAtIndex(0));
            if (playBtn) {
                pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;
                pattern->ChangePlayButtonTag(playBtn);
                auto gestureHub = playBtn->GetOrCreateGestureEventHub();
                EXPECT_TRUE(gestureHub);
                break;
            }
        }
    }
}

/**
 * @tc.name: ChangePlayButtonTag_ClickCallbackPause001
 * @tc.desc: Test ChangePlayButtonTag click callback triggers Pause when playing.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, ChangePlayButtonTag_ClickCallbackPause001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;
    pattern->stateManager_->ClearPendingCommand();

    auto host = frameNode;
    const auto& children = host->GetChildren();
    for (const auto& child : children) {
        if (child->GetTag() == V2::ROW_ETS_TAG) {
            auto playBtn = AceType::DynamicCast<FrameNode>(child->GetChildAtIndex(0));
            if (playBtn) {
                pattern->ChangePlayButtonTag(playBtn);
                break;
            }
        }
    }
}


/**
 * @tc.name: SetFullScreenButtonCallBack_Enter001
 * @tc.desc: Test SetFullScreenButtonCallBack for normal video pattern (enter full screen).
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, SetFullScreenButtonCallBack_Enter001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto host = frameNode;
    const auto& children = host->GetChildren();
    for (const auto& child : children) {
        if (child->GetTag() == V2::ROW_ETS_TAG) {
            auto fsBtn = AceType::DynamicCast<FrameNode>(child->GetChildAtIndex(POS_FULL_SCREEN));
            if (fsBtn) {
                pattern->SetFullScreenButtonCallBack(fsBtn);
                auto gestureHub = fsBtn->GetOrCreateGestureEventHub();
                EXPECT_TRUE(gestureHub);
                break;
            }
        }
    }
}


/**
 * @tc.name: SetCurrentTime_NegativeTime001
 * @tc.desc: Test SetCurrentTime returns early when currentPos is negative.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, SetCurrentTime_NegativeTime001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;
    pattern->SetCurrentTime(TEST_NEGATIVE_TIME, OHOS::Ace::SeekMode::SEEK_CLOSEST);
    EXPECT_FALSE(pattern->isSeeking_);
}

/**
 * @tc.name: SetCurrentTime_ShowFirstFrameFalse001
 * @tc.desc: Test SetCurrentTime with showFirstFrame=false updates video size.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, SetCurrentTime_ShowFirstFrameFalse001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, GetVideoWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*mockMediaPlayer, GetVideoHeight()).WillRepeatedly(Return(100));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->showFirstFrame_ = false;
    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;
    pattern->SetCurrentTime(TEST_VALID_TIME, OHOS::Ace::SeekMode::SEEK_CLOSEST);
    EXPECT_TRUE(pattern->isSeeking_);
}


/**
 * @tc.name: OnFullScreenChange_ExitFullScreen001
 * @tc.desc: Test OnFullScreenChange when isFullScreen=false updates video size.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnFullScreenChange_ExitFullScreen001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, GetVideoWidth()).WillRepeatedly(Return(200));
    EXPECT_CALL(*mockMediaPlayer, GetVideoHeight()).WillRepeatedly(Return(100));
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->OnFullScreenChange(false);
}

/**
 * @tc.name: OnFullScreenChange_AnalyzerEnabled001
 * @tc.desc: Test OnFullScreenChange with analyzer enabled.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnFullScreenChange_AnalyzerEnabled001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->isEnableAnalyzer_ = true;
    pattern->OnFullScreenChange(true);
}


/**
 * @tc.name: UpdateFsState_NoFullScreenNode001
 * @tc.desc: Test UpdateFsState returns early when no full screen node exists.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, UpdateFsState_NoFullScreenNode001, TestSize.Level0)
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
 * @tc.name: GetTargetVideoPattern_SameState001
 * @tc.desc: Test GetTargetVideoPattern returns this when state matches.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, GetTargetVideoPattern_SameState001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->fullScreenNodeId_.reset();
    auto result = pattern->GetTargetVideoPattern();
    EXPECT_EQ(result.GetRawPtr(), pattern.GetRawPtr());
}

/**
 * @tc.name: GetTargetVideoPattern_FullScreenPattern001
 * @tc.desc: Test GetTargetVideoPattern with full screen pattern mismatch.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, GetTargetVideoPattern_FullScreenPattern001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->fullScreenNodeId_.reset();
    auto result = pattern->GetTargetVideoPattern();
    EXPECT_NE(result, nullptr);
}


/**
 * @tc.name: CreateHiddenChangeEvent_FullScreenNode001
 * @tc.desc: Test CreateHiddenChangeEvent delegates to fullScreenNode when available.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, CreateHiddenChangeEvent_FullScreenNode001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto event = pattern->CreateHiddenChangeEvent();
    event(true);
}


/**
 * @tc.name: ResetMediaPlayerOnBg_CannotSetPending001
 * @tc.desc: Test ResetMediaPlayerOnBg returns early when cannot set pending.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, ResetMediaPlayerOnBg_CannotSetPending001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->stateManager_->SetPendingCommand(VideoPlaybackCommand::RESET, nullptr);
    pattern->ResetMediaPlayerOnBg();
}

/**
 * @tc.name: ResetMediaPlayerOnBg_MediaPlayerInvalid001
 * @tc.desc: Test ResetMediaPlayerOnBg handles invalid mediaPlayer in bg task.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, ResetMediaPlayerOnBg_MediaPlayerInvalid001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto invalidMock = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*invalidMock, IsMediaPlayerValid()).WillRepeatedly(Return(false));
    pattern->mediaPlayer_ = invalidMock;
    pattern->stateManager_->ClearPendingCommand();

    pattern->ResetMediaPlayerOnBg();
}

/**
 * @tc.name: ResetMediaPlayerOnBg_SetSourceFail001
 * @tc.desc: Test ResetMediaPlayerOnBg handles SetSource failure.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, ResetMediaPlayerOnBg_SetSourceFail001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, SetSource(_, _, _)).WillRepeatedly(Return(false));
    pattern->mediaPlayer_ = mockMediaPlayer;
    pattern->stateManager_->ClearPendingCommand();

    pattern->ResetMediaPlayerOnBg();
}


/**
 * @tc.name: ReportChangeEventOnUIThread_Normal001
 * @tc.desc: Test ReportChangeEventOnUIThread posts task to UI thread.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, ReportChangeEventOnUIThread_Normal001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->ReportChangeEventOnUIThread(PlaybackStatus::STARTED, 1.0, 0);
}


/**
 * @tc.name: OnSliderChange_BeginMode001
 * @tc.desc: Test OnSliderChange with BEGIN mode fires seeking event.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnSliderChange_BeginMode001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;
    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;

    pattern->OnSliderChange(5.0f, SLIDER_MODE_BEGIN);
}

/**
 * @tc.name: OnSliderChange_MovingMode001
 * @tc.desc: Test OnSliderChange with MOVING mode fires seeking event.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnSliderChange_MovingMode001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;
    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;

    pattern->OnSliderChange(5.0f, SLIDER_MODE_MOVING);
}

/**
 * @tc.name: OnSliderChange_EndMode001
 * @tc.desc: Test OnSliderChange with END mode fires seeked event.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnSliderChange_EndMode001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    pattern->mediaPlayer_ = mockMediaPlayer;
    pattern->stateManager_->state_ = VideoPlaybackState::PLAYING;

    pattern->OnSliderChange(5.0f, SLIDER_MODE_END);
}


/**
 * @tc.name: AdjustVolume_NearZero001
 * @tc.desc: Test AdjustVolume calls SetMediaMuted when targetVolume is near zero.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, AdjustVolume_NearZero001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto mockMediaPlayer = AceType::MakeRefPtr<TestableMockMediaPlayer>();
    EXPECT_CALL(*mockMediaPlayer, IsMediaPlayerValid()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockMediaPlayer, SetMediaMuted(MEDIA_TYPE_AUDIO, true)).WillRepeatedly(Return());
    EXPECT_CALL(*mockMediaPlayer, SetVolume(_, _)).WillRepeatedly(Return());
    pattern->mediaPlayer_ = mockMediaPlayer;

    pattern->currentVolume_ = 0.1f;
    pattern->AdjustVolume(-2);
    EXPECT_NEAR(pattern->currentVolume_, 0.0f, 0.001f);
    testing::Mock::VerifyAndClearExpectations(&(*mockMediaPlayer));
}

/**
 * @tc.name: AdjustVolume_OutOfRange001
 * @tc.desc: Test AdjustVolume returns early when targetVolume is out of range.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, AdjustVolume_OutOfRange001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->currentVolume_ = 1.0f;
    pattern->AdjustVolume(1);
    EXPECT_FLOAT_EQ(pattern->currentVolume_, 1.0f);
}


/**
 * @tc.name: OnWindowHide_BackgroundTask001
 * @tc.desc: Test OnWindowHide with background task present does not pause.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnWindowHide_BackgroundTask001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    pattern->autoPlay_ = true;
    pattern->OnWindowHide();
}


/**
 * @tc.name: OnDirtyLayoutWrapperSwap_NoVideoSize001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap when video size is not set.
 * @tc.type: FUNC
 */
HWTEST_F(VideoStateMachinePatternTestNg, OnDirtyLayoutWrapperSwap_NoVideoSize001, TestSize.Level0)
{
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_TRUE(pattern);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_TRUE(videoLayoutProperty);
    videoLayoutProperty->ResetVideoSize();

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_TRUE(layoutWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

} // namespace OHOS::Ace::NG
