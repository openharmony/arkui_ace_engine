/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
    std::optional<bool> showFirstFrame;
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
constexpr bool SHOW_FIRST_FRAME = false;
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

class VideoTestAddNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp();
    void TearDown() {}

protected:
    static RefPtr<FrameNode> CreateVideoNode(TestProperty& g_testProperty);
};

void VideoTestAddNg::SetUpTestSuite()
{
    g_testProperty.progressRate = VIDEO_PROGRESS_RATE;
    g_testProperty.showFirstFrame = SHOW_FIRST_FRAME;
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

void VideoTestAddNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}
void VideoTestAddNg::SetUp()
{
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<FrameNode> VideoTestAddNg::CreateVideoNode(TestProperty& g_testProperty)
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
    if (g_testProperty.showFirstFrame.has_value()) {
        VideoModelNG().SetShowFirstFrame(g_testProperty.showFirstFrame.value());
    }

    auto element = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    return AceType::Claim(element);
}

/**
 * @tc.name: VideoPropertyTest001
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest001, TestSize.Level1)
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
    pattern->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case1: controls = true
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    auto videoLayoutProperty = pattern->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
    pattern->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case2: controls = false
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    pattern->OnPlayerStatus(PlaybackStatus::ERROR);
    pattern->OnPlayerStatus(PlaybackStatus::IDLE);
    pattern->OnPlayerStatus(PlaybackStatus::PREPARED);
    pattern->OnPlayerStatus(PlaybackStatus::PAUSED);
    pattern->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
    pattern->OnPlayerStatus(PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoPropertyTest002
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest002, TestSize.Level1)
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
    pattern2->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case1: controls = true
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    auto videoLayoutProperty = pattern2->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
    pattern2->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case2: controls = false
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    pattern2->OnPlayerStatus(PlaybackStatus::ERROR);
    pattern2->OnPlayerStatus(PlaybackStatus::IDLE);
    pattern2->OnPlayerStatus(PlaybackStatus::PREPARED);
    pattern2->OnPlayerStatus(PlaybackStatus::PAUSED);
    pattern2->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
    pattern2->OnPlayerStatus(PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoPropertyTest003
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest003, TestSize.Level1)
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
    pattern3->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case1: controls = true
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    auto videoLayoutProperty = pattern3->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
    pattern3->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case2: controls = false
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    pattern3->OnPlayerStatus(PlaybackStatus::ERROR);
    pattern3->OnPlayerStatus(PlaybackStatus::IDLE);
    pattern3->OnPlayerStatus(PlaybackStatus::PREPARED);
    pattern3->OnPlayerStatus(PlaybackStatus::PAUSED);
    pattern3->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
    pattern3->OnPlayerStatus(PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoPropertyTest004
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest004, TestSize.Level1)
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
    pattern4->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case1: controls = true
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    auto videoLayoutProperty = pattern4->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
    pattern4->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case2: controls = false
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    pattern4->OnPlayerStatus(PlaybackStatus::ERROR);
    pattern4->OnPlayerStatus(PlaybackStatus::IDLE);
    pattern4->OnPlayerStatus(PlaybackStatus::PREPARED);
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
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest005, TestSize.Level1)
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
    ASSERT_TRUE(videoEventHub5);
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

    // case1: MediaPlayer is valid & isPlaying = false
    pattern5->isPlaying_ = false;
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is invalid
    pattern5->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    pattern5->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case1: controls = true
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    auto videoLayoutProperty = pattern5->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
    pattern5->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case2: controls = false
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    pattern5->OnPlayerStatus(PlaybackStatus::ERROR);
    pattern5->OnPlayerStatus(PlaybackStatus::IDLE);
    pattern5->OnPlayerStatus(PlaybackStatus::PREPARED);
    pattern5->OnPlayerStatus(PlaybackStatus::PAUSED);
    pattern5->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
    pattern5->OnPlayerStatus(PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoPropertyTest006
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest006, TestSize.Level1)
{
    auto themeManager6 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager6);
    EXPECT_CALL(*themeManager6, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern6 = frameNode->GetPattern<VideoPattern>();

    /**
     * @tc.steps: step2. Prepare the childNode & videoEvent
     */
    auto controlBar = frameNode->GetChildAtIndex(2);
    auto playBtn = AceType::DynamicCast<FrameNode>(controlBar->GetChildAtIndex(0));
    auto playBtnGestureEventHub = playBtn->GetOrCreateGestureEventHub();

    // set videoEvent
    auto videoEventHub6 = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub6);
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub6->SetOnStart(std::move(onStart));
    videoEventHub6->SetOnPause(std::move(onPause));
    videoEventHub6->SetOnFinish(std::move(onFinish));
    videoEventHub6->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern6->Pause()
     */
    pattern6->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern6->Pause()
    EXPECT_TRUE(pattern6->isPlaying_);

    // case1: MediaPlayer is valid & isPlaying = false
    pattern6->isPlaying_ = false;
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is valid
    pauseCheck.clear();
    pattern6->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    pattern6->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case1: controls = true
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    auto videoLayoutProperty = pattern6->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
    pattern6->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case2: controls = false
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    pattern6->OnPlayerStatus(PlaybackStatus::ERROR);
    pattern6->OnPlayerStatus(PlaybackStatus::IDLE);
    pattern6->OnPlayerStatus(PlaybackStatus::PREPARED);
    pattern6->OnPlayerStatus(PlaybackStatus::PAUSED);
    pattern6->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
    pattern6->OnPlayerStatus(PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoPropertyTest007
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest007, TestSize.Level1)
{
    auto themeManager7 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager7);
    EXPECT_CALL(*themeManager7, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern7 = frameNode->GetPattern<VideoPattern>();

    /**
     * @tc.steps: step2. Prepare the childNode & videoEvent
     */
    auto controlBar = frameNode->GetChildAtIndex(2);
    auto playBtn = AceType::DynamicCast<FrameNode>(controlBar->GetChildAtIndex(0));
    ASSERT_TRUE(playBtn);
    auto playBtnGestureEventHub = playBtn->GetOrCreateGestureEventHub();
    ASSERT_TRUE(playBtnGestureEventHub);

    // set videoEvent
    auto videoEventHub7 = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub7);
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub7->SetOnStart(std::move(onStart));
    videoEventHub7->SetOnPause(std::move(onPause));
    videoEventHub7->SetOnFinish(std::move(onFinish));
    videoEventHub7->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern7->Pause()
     */
    pattern7->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern7->Pause()
    EXPECT_TRUE(pattern7->isPlaying_);
    // case1: MediaPlayer is invalid
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);
    // case2: MediaPlayer is valid & isPlaying = true
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern7->mediaPlayer_)),
                  Pause()).Times(2).WillOnce(Return(0));
    flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);
    // case3: MediaPlayer is valid & isPlaying = false
    pattern7->isPlaying_ = false;
    flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is invalid
    pattern7->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    // case1: MediaPlayer is valid
    pauseCheck.clear();
    pattern7->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    pattern7->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case1: controls = true
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    auto videoLayoutProperty = pattern7->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
}

/**
 * @tc.name: VideoPropertyTest008
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest008, TestSize.Level1)
{
    auto themeManager8 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager8);
    EXPECT_CALL(*themeManager8, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern8 = frameNode->GetPattern<VideoPattern>();

    /**
     * @tc.steps: step2. Prepare the childNode & videoEvent
     */
    auto controlBar = frameNode->GetChildAtIndex(2);
    auto playBtn = AceType::DynamicCast<FrameNode>(controlBar->GetChildAtIndex(0));
    auto playBtnGestureEventHub = playBtn->GetOrCreateGestureEventHub();

    // set videoEvent
    auto videoEventHub8 = frameNode->GetEventHub<VideoEventHub>();
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub8->SetOnStart(std::move(onStart));
    videoEventHub8->SetOnPause(std::move(onPause));
    videoEventHub8->SetOnFinish(std::move(onFinish));
    videoEventHub8->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern8->Pause()
     */
    pattern8->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern8->Pause()
    EXPECT_TRUE(pattern8->isPlaying_);
    // case1: MediaPlayer is invalid
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);
    // case2: MediaPlayer is valid & isPlaying = true
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern8->mediaPlayer_)),
                  Pause()).Times(1).WillOnce(Return(0));
    // case3: MediaPlayer is valid & isPlaying = false
    pattern8->isPlaying_ = false;
    flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is invalid
    pattern8->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    // case1: MediaPlayer is valid
    pauseCheck.clear();
    pattern8->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    auto videoLayoutProperty = pattern8->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
    pattern8->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case2: controls = false
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    pattern8->OnPlayerStatus(PlaybackStatus::ERROR);
    pattern8->OnPlayerStatus(PlaybackStatus::IDLE);
    pattern8->OnPlayerStatus(PlaybackStatus::PREPARED);
    pattern8->OnPlayerStatus(PlaybackStatus::PAUSED);
    pattern8->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
    pattern8->OnPlayerStatus(PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoPropertyTest009
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest009, TestSize.Level1)
{
    auto themeManager9 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager9);
    EXPECT_CALL(*themeManager9, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern9 = frameNode->GetPattern<VideoPattern>();

    /**
     * @tc.steps: step2. Prepare the childNode & videoEvent
     */
    auto controlBar = frameNode->GetChildAtIndex(2);
    auto playBtn = AceType::DynamicCast<FrameNode>(controlBar->GetChildAtIndex(0));
    auto playBtnGestureEventHub = playBtn->GetOrCreateGestureEventHub();

    // set videoEvent
    auto videoEventHub9 = frameNode->GetEventHub<VideoEventHub>();
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub9->SetOnStart(std::move(onStart));
    videoEventHub9->SetOnPause(std::move(onPause));
    videoEventHub9->SetOnFinish(std::move(onFinish));
    videoEventHub9->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern9->Pause()
     */
    pattern9->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern9->Pause()
    EXPECT_TRUE(pattern9->isPlaying_);
    // case1: MediaPlayer is invalid
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is invalid
    pattern9->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    pattern9->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case1: controls = true
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    auto videoLayoutProperty = pattern9->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
}

/**
 * @tc.name: VideoPropertyTest010
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest010, TestSize.Level1)
{
    auto themeManager10 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager10);
    EXPECT_CALL(*themeManager10, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern10 = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern10);

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
    auto videoEventHub10 = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub10);
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub10->SetOnStart(std::move(onStart));
    videoEventHub10->SetOnPause(std::move(onPause));
    videoEventHub10->SetOnFinish(std::move(onFinish));
    videoEventHub10->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern10->Pause()
     */
    pattern10->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern10->Pause()
    EXPECT_TRUE(pattern10->isPlaying_);
    // case1: MediaPlayer is invalid
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is valid
    pauseCheck.clear();
    pattern10->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    pattern10->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case1: controls = true
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    auto videoLayoutProperty = pattern10->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
}

/**
 * @tc.name: VideoPropertyTest011
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest011, TestSize.Level1)
{
    auto themeManager11 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager11);
    EXPECT_CALL(*themeManager11, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern11 = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern11);

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
    auto videoEventHub11 = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub11);
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub11->SetOnStart(std::move(onStart));
    videoEventHub11->SetOnPause(std::move(onPause));
    videoEventHub11->SetOnFinish(std::move(onFinish));
    videoEventHub11->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern11->Pause()
     */
    pattern11->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern11->Pause()
    EXPECT_TRUE(pattern11->isPlaying_);
    // case1: MediaPlayer is invalid
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is invalid
    pattern11->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    auto videoLayoutProperty = pattern11->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
    pattern11->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case1: controls = false
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    pattern11->OnPlayerStatus(PlaybackStatus::ERROR);
    pattern11->OnPlayerStatus(PlaybackStatus::IDLE);
    pattern11->OnPlayerStatus(PlaybackStatus::PREPARED);
    pattern11->OnPlayerStatus(PlaybackStatus::PAUSED);
    pattern11->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
    pattern11->OnPlayerStatus(PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoPropertyTest012
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest012, TestSize.Level1)
{
    auto themeManager12 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager12);
    EXPECT_CALL(*themeManager12, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern12 = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern12);

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
    auto videoEventHub12 = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub12);
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub12->SetOnStart(std::move(onStart));
    videoEventHub12->SetOnPause(std::move(onPause));
    videoEventHub12->SetOnFinish(std::move(onFinish));
    videoEventHub12->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern12->Pause()
     */
    pattern12->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern12->Pause()
    EXPECT_TRUE(pattern12->isPlaying_);
    // case1: MediaPlayer is invalid
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is valid
    pauseCheck.clear();
    pattern12->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    auto videoLayoutProperty = pattern12->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
    pattern12->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case1: controls = false
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    pattern12->OnPlayerStatus(PlaybackStatus::ERROR);
    pattern12->OnPlayerStatus(PlaybackStatus::IDLE);
    pattern12->OnPlayerStatus(PlaybackStatus::PREPARED);
    pattern12->OnPlayerStatus(PlaybackStatus::PAUSED);
    pattern12->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
    pattern12->OnPlayerStatus(PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoPropertyTest013
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest013, TestSize.Level1)
{
    auto themeManager13 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager13);
    EXPECT_CALL(*themeManager13, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern13 = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern13);

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
    auto videoEventHub13 = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub13);
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub13->SetOnStart(std::move(onStart));
    videoEventHub13->SetOnPause(std::move(onPause));
    videoEventHub13->SetOnFinish(std::move(onFinish));
    videoEventHub13->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern13->Pause()
     */
    pattern13->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern13->Pause()
    EXPECT_TRUE(pattern13->isPlaying_);
    pattern13->isPlaying_ = false;
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is invalid
    pattern13->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    pattern13->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case1: controls = true
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    auto videoLayoutProperty = pattern13->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
}

/**
 * @tc.name: VideoPropertyTest014
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest014, TestSize.Level1)
{
    auto themeManager14 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager14);
    EXPECT_CALL(*themeManager14, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern14 = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern14);

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
    auto videoEventHub14 = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub14);
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub14->SetOnStart(std::move(onStart));
    videoEventHub14->SetOnPause(std::move(onPause));
    videoEventHub14->SetOnFinish(std::move(onFinish));
    videoEventHub14->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern14->Pause()
     */
    pattern14->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern14->Pause()
    EXPECT_TRUE(pattern14->isPlaying_);
    // case1: MediaPlayer is valid & isPlaying = false
    pattern14->isPlaying_ = false;
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is valid
    pauseCheck.clear();
    pattern14->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    pattern14->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case1: controls = true
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    auto videoLayoutProperty = pattern14->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
}

/**
 * @tc.name: VideoPropertyTest015
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest015, TestSize.Level1)
{
    auto themeManager15 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager15);
    EXPECT_CALL(*themeManager15, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern15 = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern15);

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
    auto videoEventHub15 = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub15);
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub15->SetOnStart(std::move(onStart));
    videoEventHub15->SetOnPause(std::move(onPause));
    videoEventHub15->SetOnFinish(std::move(onFinish));
    videoEventHub15->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern15->Pause()
     */
    pattern15->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern15->Pause()
    EXPECT_TRUE(pattern15->isPlaying_);
    pattern15->isPlaying_ = false;
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is invalid
    pattern15->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    auto videoLayoutProperty = pattern15->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
    pattern15->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case2: controls = false
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    pattern15->OnPlayerStatus(PlaybackStatus::ERROR);
    pattern15->OnPlayerStatus(PlaybackStatus::IDLE);
    pattern15->OnPlayerStatus(PlaybackStatus::PREPARED);
    pattern15->OnPlayerStatus(PlaybackStatus::PAUSED);
    pattern15->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
    pattern15->OnPlayerStatus(PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoPropertyTest016
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest016, TestSize.Level1)
{
    auto themeManager16 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager16);
    EXPECT_CALL(*themeManager16, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern16 = frameNode->GetPattern<VideoPattern>();
    
    /**
     * @tc.steps: step2. Prepare the childNode & videoEvent
     */
    auto controlBar = frameNode->GetChildAtIndex(2);
    auto playBtn = AceType::DynamicCast<FrameNode>(controlBar->GetChildAtIndex(0));
    auto playBtnGestureEventHub = playBtn->GetOrCreateGestureEventHub();

    // set videoEvent
    auto videoEventHub16 = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub16);
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub16->SetOnStart(std::move(onStart));
    videoEventHub16->SetOnPause(std::move(onPause));
    videoEventHub16->SetOnFinish(std::move(onFinish));
    videoEventHub16->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern16->Pause()
     */
    pattern16->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern16->Pause()
    EXPECT_TRUE(pattern16->isPlaying_);
    pattern16->isPlaying_ = false;
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is invalid
    pattern16->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    // case1: MediaPlayer is valid
    pauseCheck.clear();
    pattern16->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    auto videoLayoutProperty = pattern16->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
    pattern16->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case2: controls = false
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    pattern16->OnPlayerStatus(PlaybackStatus::ERROR);
    pattern16->OnPlayerStatus(PlaybackStatus::IDLE);
    pattern16->OnPlayerStatus(PlaybackStatus::PREPARED);
    pattern16->OnPlayerStatus(PlaybackStatus::PAUSED);
    pattern16->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
    pattern16->OnPlayerStatus(PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoPropertyTest017
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest017, TestSize.Level1)
{
    auto themeManager17 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager17);
    EXPECT_CALL(*themeManager17, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern17 = frameNode->GetPattern<VideoPattern>();

    /**
     * @tc.steps: step2. Prepare the childNode & videoEvent
     */
    auto controlBar = frameNode->GetChildAtIndex(2);
    auto playBtn = AceType::DynamicCast<FrameNode>(controlBar->GetChildAtIndex(0));
    auto playBtnGestureEventHub = playBtn->GetOrCreateGestureEventHub();
    ASSERT_TRUE(playBtnGestureEventHub);

    // set videoEvent
    auto videoEventHub17 = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub17);
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub17->SetOnStart(std::move(onStart));
    videoEventHub17->SetOnPause(std::move(onPause));
    videoEventHub17->SetOnFinish(std::move(onFinish));
    videoEventHub17->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern17->Pause()
     */
    pattern17->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern17->Pause()
    EXPECT_TRUE(pattern17->isPlaying_);
    // case1: MediaPlayer is valid & isPlaying = true
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern17->mediaPlayer_)),
                  Pause()).Times(1).WillOnce(Return(0));
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is invalid
    pattern17->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    pattern17->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case1: controls = true
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    auto videoLayoutProperty = pattern17->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
    pattern17->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case2: controls = false
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    pattern17->OnPlayerStatus(PlaybackStatus::ERROR);
    pattern17->OnPlayerStatus(PlaybackStatus::IDLE);
    pattern17->OnPlayerStatus(PlaybackStatus::PREPARED);
    pattern17->OnPlayerStatus(PlaybackStatus::PAUSED);
    pattern17->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
    pattern17->OnPlayerStatus(PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoPropertyTest018
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest018, TestSize.Level1)
{
    auto themeManager18 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager18);
    EXPECT_CALL(*themeManager18, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern18 = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern18);

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
    auto videoEventHub18 = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub18);
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub18->SetOnStart(std::move(onStart));
    videoEventHub18->SetOnPause(std::move(onPause));
    videoEventHub18->SetOnFinish(std::move(onFinish));
    videoEventHub18->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern18->Pause()
     */
    pattern18->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern18->Pause()
    EXPECT_TRUE(pattern18->isPlaying_);
    // case1: MediaPlayer is valid & isPlaying = true
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern18->mediaPlayer_)),
                  Pause()).Times(1).WillOnce(Return(0));
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is invalid
    pattern18->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    auto videoLayoutProperty = pattern18->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
    pattern18->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case2: controls = false
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    pattern18->OnPlayerStatus(PlaybackStatus::ERROR);
    pattern18->OnPlayerStatus(PlaybackStatus::IDLE);
    pattern18->OnPlayerStatus(PlaybackStatus::PREPARED);
    pattern18->OnPlayerStatus(PlaybackStatus::PAUSED);
    pattern18->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
    pattern18->OnPlayerStatus(PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoPropertyTest019
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest019, TestSize.Level1)
{
    auto themeManager19 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager19);
    EXPECT_CALL(*themeManager19, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern19 = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern19);

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
    auto videoEventHub19 = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub19);
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub19->SetOnStart(std::move(onStart));
    videoEventHub19->SetOnPause(std::move(onPause));
    videoEventHub19->SetOnFinish(std::move(onFinish));
    videoEventHub19->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern19->Pause()
     */
    pattern19->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern19->Pause()
    EXPECT_TRUE(pattern19->isPlaying_);
    // case1: MediaPlayer is valid & isPlaying = true
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern19->mediaPlayer_)),
                  Pause()).Times(1).WillOnce(Return(0));
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is valid
    pauseCheck.clear();
    pattern19->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    pattern19->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case1: controls = true
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    auto videoLayoutProperty = pattern19->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
}

/**
 * @tc.name: VideoPropertyTest020
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest020, TestSize.Level1)
{
auto themeManager20 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager20);
    EXPECT_CALL(*themeManager20, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern20 = frameNode->GetPattern<VideoPattern>();

    /**
     * @tc.steps: step2. Prepare the childNode & videoEvent
     */
    auto controlBar = frameNode->GetChildAtIndex(2);
    auto playBtn = AceType::DynamicCast<FrameNode>(controlBar->GetChildAtIndex(0));
    auto playBtnGestureEventHub = playBtn->GetOrCreateGestureEventHub();

    // set videoEvent
    auto videoEventHub20 = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub20);
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub20->SetOnStart(std::move(onStart));
    videoEventHub20->SetOnPause(std::move(onPause));
    videoEventHub20->SetOnFinish(std::move(onFinish));
    videoEventHub20->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern20->Pause()
     */
    pattern20->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern20->Pause()
    EXPECT_TRUE(pattern20->isPlaying_);
    // case1: MediaPlayer is valid & isPlaying = true
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern20->mediaPlayer_)),
                  Pause()).Times(1).WillOnce(Return(0));
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. Call OnPlayerStatus status == PREPARED
     * @tc.expected: step4. FirePauseEvent & mediaPlayer->GetDuration() has called
     */
    // case1: MediaPlayer is valid
    pauseCheck.clear();
    pattern20->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    auto videoLayoutProperty = pattern20->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
    pattern20->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case2: controls = false
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    pattern20->OnPlayerStatus(PlaybackStatus::ERROR);
    pattern20->OnPlayerStatus(PlaybackStatus::IDLE);
    pattern20->OnPlayerStatus(PlaybackStatus::PREPARED);
    pattern20->OnPlayerStatus(PlaybackStatus::PAUSED);
    pattern20->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
    pattern20->OnPlayerStatus(PlaybackStatus::NONE);
}

/**
 * @tc.name: VideoPropertyTest021
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestAddNg, OnPlayerStatusTest021, TestSize.Level1)
{
    auto themeManager21 = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager21);
    EXPECT_CALL(*themeManager21, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(g_testProperty);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern21 = frameNode->GetPattern<VideoPattern>();

    /**
     * @tc.steps: step2. Prepare the childNode & videoEvent
     */
    auto controlBar = frameNode->GetChildAtIndex(2);
    auto playBtn = AceType::DynamicCast<FrameNode>(controlBar->GetChildAtIndex(0));
    auto playBtnGestureEventHub = playBtn->GetOrCreateGestureEventHub();

    // set videoEvent
    auto videoEventHub21 = frameNode->GetEventHub<VideoEventHub>();
    std::string startCheck;
    VideoEventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    VideoEventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub21->SetOnStart(std::move(onStart));
    videoEventHub21->SetOnPause(std::move(onPause));
    videoEventHub21->SetOnFinish(std::move(onFinish));
    videoEventHub21->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern21->Pause()
     */
    pattern21->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    // will call pattern21->Pause()
    EXPECT_TRUE(pattern21->isPlaying_);
    // case1: MediaPlayer is invalid
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);
    // case2: MediaPlayer is valid & isPlaying = true
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern21->mediaPlayer_)),
                  Pause()).Times(2).WillOnce(Return(0));
    flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);
    // case3: MediaPlayer is valid & isPlaying = false
    pattern21->isPlaying_ = false;
    flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);
    pattern21->OnPlayerStatus(PlaybackStatus::PAUSED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    /**
     * @tc.steps: step5. Call OnPlayerStatus status == PLAYBACK_COMPLETE
     * @tc.expected: step5. FireFinishEvent & OnUpdateTime(pos = CURRENT_POS) will be called
     */
    pattern21->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case1: controls = true
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    auto videoLayoutProperty = pattern21->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
    pattern21->OnPlayerStatus(PlaybackStatus::PLAYBACK_COMPLETE); // case2: controls = false
    EXPECT_EQ(finishCheck, VIDEO_FINISH_EVENT);
    pattern21->OnPlayerStatus(PlaybackStatus::ERROR);
    pattern21->OnPlayerStatus(PlaybackStatus::IDLE);
    pattern21->OnPlayerStatus(PlaybackStatus::PREPARED);
    pattern21->OnPlayerStatus(PlaybackStatus::PAUSED);
    pattern21->OnPlayerStatus(PlaybackStatus::STOPPED);
    EXPECT_EQ(stopCheck, VIDEO_STOP_EVENT);
}
} // namespace OHOS::Ace::NG