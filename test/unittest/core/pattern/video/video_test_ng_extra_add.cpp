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

#include <cmath>
#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "gmock/gmock-actions.h"
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_media_player.h"
#include "test/mock/core/render/mock_render_context.h"

#include "base/geometry/ng/size_t.h"
#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "base/resource/internal_resource.h"
#include "core/common/ai/image_analyzer_mgr.h"
#include "core/components/common/layout/constants.h"
#include "core/components/video/video_theme.h"
#include "core/components/video/video_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/drag_event.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/video/video_full_screen_node.h"
#include "core/components_ng/pattern/video/video_full_screen_pattern.h"
#include "core/components_ng/pattern/video/video_layout_algorithm.h"
#include "core/components_ng/pattern/video/video_layout_property.h"
#include "core/components_ng/pattern/video/video_model_ng.h"
#include "core/components_ng/pattern/video/video_node.h"
#include "core/components_ng/pattern/video/video_pattern.h"
#include "core/components_ng/pattern/video/video_styles.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/image/image_source_info.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct TestProperty {
    std::optional<std::string> src;
    std::optional<double> progressRate;
    std::optional<std::string> posterUrl;
    std::optional<bool> muted;
    std::optional<bool> autoPlay;
    std::optional<bool> controls;
    std::optional<bool> loop;
    std::optional<ImageFit> objectFit;
    std::optional<RefPtr<VideoControllerV2>> videoController;
};
namespace {
constexpr double VIDEO_PROGRESS_RATE = 1.0;
constexpr bool MUTED_VALUE = false;
constexpr bool AUTO_PLAY = false;
constexpr bool CONTROL_VALUE = true;
constexpr bool LOOP_VALUE = false;
const ImageFit VIDEO_IMAGE_FIT = ImageFit::COVER;
const std::string VIDEO_SRC = "common/video.mp4";
const std::string VIDEO_POSTER_URL = "common/img2.png";
const std::string VIDEO_START_EVENT = "start";
const std::string VIDEO_PAUSE_EVENT = "pause";
const std::string VIDEO_FINISH_EVENT = "finish";
const std::string VIDEO_ERROR_EVENT = "error";
const std::string VIDEO_PREPARED_EVENT = "prepared";
const std::string VIDEO_SEEKING_EVENT = "seeking";
const std::string VIDEO_SEEKED_EVENT = "seeked";
const std::string VIDEO_UPDATE_EVENT = "update";
const std::string VIDEO_FULLSCREEN_EVENT = "fullScreen";
const std::string EXTRA_INFO_KEY = "extraInfo";
const std::string VIDEO_ERROR_ID = "";
const std::string VIDEO_CALLBACK_RESULT = "result_ok";
const std::string VIDEO_STOP_EVENT = "stop";
constexpr float MAX_WIDTH = 400.0f;
constexpr float MAX_HEIGHT = 400.0f;
constexpr float VIDEO_WIDTH = 300.0f;
constexpr float VIDEO_HEIGHT = 300.0f;
constexpr float SCREEN_WIDTH_SMALL = 500.0f;
constexpr float SCREEN_HEIGHT_SMALL = 1000.0f;
constexpr float SCREEN_WIDTH_MEDIUM = 1000.0f;
constexpr float SCREEN_HEIGHT_MEDIUM = 2000.0f;
constexpr float SCREEN_WIDTH_LARGE = 1500.0f;
constexpr float SCREEN_HEIGHT_LARGE = 2500.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
const SizeF SCREEN_SIZE_SMALL(SCREEN_WIDTH_SMALL, SCREEN_HEIGHT_SMALL);
const SizeF SCREEN_SIZE_MEDIUM(SCREEN_WIDTH_MEDIUM, SCREEN_HEIGHT_MEDIUM);
const SizeF SCREEN_SIZE_LARGE(SCREEN_WIDTH_LARGE, SCREEN_HEIGHT_LARGE);
const SizeF VIDEO_SIZE(VIDEO_WIDTH, VIDEO_HEIGHT);
const SizeF LAYOUT_SIZE_RATIO_GREATER_THAN_1(MAX_WIDTH, VIDEO_HEIGHT);
const SizeF LAYOUT_SIZE_RATIO_LESS_THAN_1(VIDEO_WIDTH, MAX_HEIGHT);
const SizeF INVALID_SIZE(MAX_WIDTH, 0.0f);
TestProperty g_testProperty;
} // namespace

class VideoTestExtraAddNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp();
    void TearDown() {}

protected:
    static RefPtr<FrameNode> CreateVideoNode(TestProperty& g_testProperty);
};

void VideoTestExtraAddNg::SetUpTestSuite()
{
    g_testProperty.progressRate = VIDEO_PROGRESS_RATE;
    g_testProperty.muted = MUTED_VALUE;
    g_testProperty.autoPlay = AUTO_PLAY;
    g_testProperty.controls = CONTROL_VALUE;
    g_testProperty.loop = LOOP_VALUE;
    g_testProperty.objectFit = VIDEO_IMAGE_FIT;
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MockPipelineContext::GetCurrent()->rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
}

void VideoTestExtraAddNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}
void VideoTestExtraAddNg::SetUp()
{
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<FrameNode> VideoTestExtraAddNg::CreateVideoNode(TestProperty& g_testProperty)
{
    if (g_testProperty.videoController.has_value()) {
        VideoModelNG().Create(g_testProperty.videoController.value());
    } else {
        auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
        VideoModelNG().Create(videoController);
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    CHECK_NULL_RETURN(videoPattern, nullptr);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(true));

    if (g_testProperty.src.has_value()) {
        VideoModelNG().SetSrc(g_testProperty.src.value(), "", "");
    }
    if (g_testProperty.progressRate.has_value()) {
        VideoModelNG().SetProgressRate(g_testProperty.progressRate.value());
    }
    if (g_testProperty.posterUrl.has_value()) {
        VideoModelNG().SetPosterSourceInfo(g_testProperty.posterUrl.value(), "", "");
    }
    if (g_testProperty.muted.has_value()) {
        VideoModelNG().SetMuted(g_testProperty.muted.value());
    }
    if (g_testProperty.autoPlay.has_value()) {
        VideoModelNG().SetAutoPlay(g_testProperty.autoPlay.value());
    }
    if (g_testProperty.controls.has_value()) {
        VideoModelNG().SetControls(g_testProperty.controls.value());
    }
    if (g_testProperty.loop.has_value()) {
        VideoModelNG().SetLoop(g_testProperty.loop.value());
    }
    if (g_testProperty.objectFit.has_value()) {
        VideoModelNG().SetObjectFit(g_testProperty.objectFit.value());
    }

    auto element = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    return AceType::Claim(element);
}

/**
 * @tc.name: VideoPropertyTest001
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestExtraAddNg, OnPlayerStatusTest001, TestSize.Level1)
{
    auto themeManager1 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager1);
    EXPECT_CALL(*themeManager1, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. Prepare the childNode & videoEvent
     */
    auto controlBar = frameNode->GetChildAtIndex(2);
    ASSERT_TRUE(controlBar);

    auto playBtn = AceType::DynamicCast<FrameNode>(controlBar->GetChildAtIndex(0));
    ASSERT_TRUE(playBtn);
    auto playBtnGestureEventHub = playBtn->GetOrCreateGestureEventHub();
    ASSERT_TRUE(playBtnGestureEventHub);

    // set videoEvent
    auto videoEventHub = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub);
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub->SetOnStart(std::move(onStart));
    videoEventHub->SetOnPause(std::move(onPause));
    videoEventHub->SetOnFinish(std::move(onFinish));
    videoEventHub->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern->Pause()
     */
    pattern->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern->Pause()
    EXPECT_TRUE(pattern->isPlaying_);
    // case1: MediaPlayer is invalid
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is invalid
    pattern->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    pattern->OnPlayerStatus(PlaybackStatus::ERROR);
    pattern->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
    pattern->OnPlayerStatus(PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoPropertyTest002
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestExtraAddNg, OnPlayerStatusTest002, TestSize.Level1)
{
    auto themeManager2 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager2);
    EXPECT_CALL(*themeManager2, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern2 = frameNode->GetPattern<VideoPattern>();

    /**
     * @tc.steps: step2. Prepare the childNode & videoEvent
     */
    auto controlBar = frameNode->GetChildAtIndex(2);
    auto playBtn = AceType::DynamicCast<FrameNode>(controlBar->GetChildAtIndex(0));
    auto playBtnGestureEventHub = playBtn->GetOrCreateGestureEventHub();

    // set videoEvent
    auto videoEventHub2 = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub2);
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub2->SetOnStart(std::move(onStart));
    videoEventHub2->SetOnPause(std::move(onPause));
    videoEventHub2->SetOnFinish(std::move(onFinish));
    videoEventHub2->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern2->Pause()
     */
    pattern2->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern2->Pause()
    EXPECT_TRUE(pattern2->isPlaying_);
    // case1: MediaPlayer is invalid
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is valid
    pauseCheck.clear();
    pattern2->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    pattern2->OnPlayerStatus(PlaybackStatus::IDLE);
    pattern2->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
    pattern2->OnPlayerStatus(PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoPropertyTest003
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestExtraAddNg, OnPlayerStatusTest003, TestSize.Level1)
{
    auto themeManager3 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager3);
    EXPECT_CALL(*themeManager3, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern3 = frameNode->GetPattern<VideoPattern>();

    /**
     * @tc.steps: step2. Prepare the childNode & videoEvent
     */
    auto controlBar = frameNode->GetChildAtIndex(2);
    auto playBtn = AceType::DynamicCast<FrameNode>(controlBar->GetChildAtIndex(0));
    auto playBtnGestureEventHub = playBtn->GetOrCreateGestureEventHub();

    // set videoEvent
    auto videoEventHub3 = frameNode->GetEventHub<VideoEventHub>();
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub3->SetOnStart(std::move(onStart));
    videoEventHub3->SetOnPause(std::move(onPause));
    videoEventHub3->SetOnFinish(std::move(onFinish));
    videoEventHub3->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern3->Pause()
     */
    pattern3->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern3->Pause()
    EXPECT_TRUE(pattern3->isPlaying_);
    // case1: MediaPlayer is valid & isPlaying = true
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern3->mediaPlayer_)),
                  Pause()).Times(1).WillOnce(Return(0));
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is invalid
    pattern3->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    pattern3->OnPlayerStatus(PlaybackStatus::PREPARED);
    pattern3->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
    pattern3->OnPlayerStatus(PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoPropertyTest004
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestExtraAddNg, OnPlayerStatusTest004, TestSize.Level1)
{
    auto themeManager4 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager4);
    EXPECT_CALL(*themeManager4, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern4 = frameNode->GetPattern<VideoPattern>();

    /**
     * @tc.steps: step2. Prepare the childNode & videoEvent
     */
    auto controlBar = frameNode->GetChildAtIndex(2);
    auto playBtn = AceType::DynamicCast<FrameNode>(controlBar->GetChildAtIndex(0));
    auto playBtnGestureEventHub = playBtn->GetOrCreateGestureEventHub();

    // set videoEvent
    auto videoEventHub4 = frameNode->GetEventHub<VideoEventHub>();
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub4->SetOnStart(std::move(onStart));
    videoEventHub4->SetOnPause(std::move(onPause));
    videoEventHub4->SetOnFinish(std::move(onFinish));
    videoEventHub4->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern4->Pause()
     */
    pattern4->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern4->Pause()
    EXPECT_TRUE(pattern4->isPlaying_);
    // case1: MediaPlayer is valid & isPlaying = true
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern4->mediaPlayer_)),
                  Pause()).Times(1).WillOnce(Return(0));
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is valid
    pauseCheck.clear();
    pattern4->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    pattern4->OnPlayerStatus(PlaybackStatus::PAUSED);
    pattern4->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
    pattern4->OnPlayerStatus(PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoPropertyTest005
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestExtraAddNg, OnPlayerStatusTest005, TestSize.Level1)
{
    auto themeManager5 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager5);
    EXPECT_CALL(*themeManager5, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern5 = frameNode->GetPattern<VideoPattern>();

    /**
     * @tc.steps: step2. Prepare the childNode & videoEvent
     */
    auto controlBar = frameNode->GetChildAtIndex(2);
    auto playBtn = AceType::DynamicCast<FrameNode>(controlBar->GetChildAtIndex(0));
    auto playBtnGestureEventHub = playBtn->GetOrCreateGestureEventHub();

    // set videoEvent
    auto videoEventHub5 = frameNode->GetEventHub<VideoEventHub>();
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub5->SetOnStart(std::move(onStart));
    videoEventHub5->SetOnPause(std::move(onPause));
    videoEventHub5->SetOnFinish(std::move(onFinish));
    videoEventHub5->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern5->Pause()
     */
    pattern5->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern5->Pause()
    EXPECT_TRUE(pattern5->isPlaying_);
    // case1: MediaPlayer is valid & isPlaying = true
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern5->mediaPlayer_)),
                  Pause()).Times(1).WillOnce(Return(0));
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is valid
    pauseCheck.clear();
    pattern5->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    pattern5->OnPlayerStatus(PlaybackStatus::PAUSED);
    pattern5->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
    pattern5->OnPlayerStatus(PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoPatternTest006
 * @tc.desc: Test OnPlayerStatus
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestExtraAddNg, VideoPatternTest006, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. Prepare the childNode & videoEvent
     */
    auto controlBar = frameNode->GetChildAtIndex(2);
    ASSERT_TRUE(controlBar);

    auto playBtn = AceType::DynamicCast<FrameNode>(controlBar->GetChildAtIndex(0));
    ASSERT_TRUE(playBtn);
    auto playBtnGestureEventHub = playBtn->GetOrCreateGestureEventHub();
    ASSERT_TRUE(playBtnGestureEventHub);

    // set videoEvent
    auto videoEventHub = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub);
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub->SetOnStart(std::move(onStart));
    videoEventHub->SetOnPause(std::move(onPause));
    videoEventHub->SetOnFinish(std::move(onFinish));
    videoEventHub->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern->Pause()
     */
    pattern->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern->Pause()
    EXPECT_TRUE(pattern->isPlaying_);
    // case1: MediaPlayer is invalid
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);
    // case2: MediaPlayer is valid & isPlaying = true
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), Pause()).Times(2).WillOnce(Return(0));
    flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);
    // case3: MediaPlayer is valid & isPlaying = false
    pattern->isPlaying_ = false;
    flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is invalid
    pattern->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    // case1: MediaPlayer is valid
    pauseCheck.clear();
    pattern->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    pattern->OnPlayerStatus(PlaybackStatus::ERROR);
    pattern->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
}

} // namespace OHOS::Ace::NG