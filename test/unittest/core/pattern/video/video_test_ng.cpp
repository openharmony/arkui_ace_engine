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
#include "test/mock/core/render/mock_render_surface.h"

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
const int32_t VIDEO_CODE = 1;
const std::string VIDEO_MESSAGE = "message";
const std::string VIDEO_CALLBACK_RESULT = "result_ok";
const std::string VIDEO_STOP_EVENT = "stop";
const std::string JSON_VALUE_FALSE = "false";
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
constexpr uint32_t VIDEO_CHILDREN_NUM = 3;
constexpr uint32_t DURATION = 100;
constexpr uint32_t CURRENT_TIME = 100;
constexpr int32_t SLIDER_INDEX = 2;
constexpr int32_t VIDEO_NODE_ID_1 = 1;
constexpr int32_t VIDEO_NODE_ID_2 = 2;
TestProperty testProperty;
} // namespace

class VideoTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp();
    void TearDown() {}

protected:
    static RefPtr<FrameNode> CreateVideoNode(TestProperty& testProperty);
};

void VideoTestNg::SetUpTestSuite()
{
    testProperty.progressRate = VIDEO_PROGRESS_RATE;
    testProperty.showFirstFrame = SHOW_FIRST_FRAME;
    testProperty.muted = MUTED_VALUE;
    testProperty.autoPlay = AUTO_PLAY;
    testProperty.controls = CONTROL_VALUE;
    testProperty.loop = LOOP_VALUE;
    testProperty.objectFit = VIDEO_IMAGE_FIT;
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MockPipelineContext::GetCurrent()->rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
}

void VideoTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}
void VideoTestNg::SetUp()
{
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<FrameNode> VideoTestNg::CreateVideoNode(TestProperty& testProperty)
{
    if (testProperty.videoController.has_value()) {
        VideoModelNG().Create(testProperty.videoController.value());
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

    if (testProperty.src.has_value()) {
        VideoModelNG().SetSrc(testProperty.src.value(), "", "");
    }
    if (testProperty.progressRate.has_value()) {
        VideoModelNG().SetProgressRate(testProperty.progressRate.value());
    }
    if (testProperty.posterUrl.has_value()) {
        VideoModelNG().SetPosterSourceInfo(testProperty.posterUrl.value(), "", "");
    }
    if (testProperty.muted.has_value()) {
        VideoModelNG().SetMuted(testProperty.muted.value());
    }
    if (testProperty.autoPlay.has_value()) {
        VideoModelNG().SetAutoPlay(testProperty.autoPlay.value());
    }
    if (testProperty.controls.has_value()) {
        VideoModelNG().SetControls(testProperty.controls.value());
    }
    if (testProperty.loop.has_value()) {
        VideoModelNG().SetLoop(testProperty.loop.value());
    }
    if (testProperty.objectFit.has_value()) {
        VideoModelNG().SetObjectFit(testProperty.objectFit.value());
    }
    if (testProperty.showFirstFrame.has_value()) {
        VideoModelNG().SetShowFirstFrame(testProperty.showFirstFrame.value());
    }

    auto element = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    return AceType::Claim(element);
}

/**
 * @tc.name: VideoPropertyTest001
 * @tc.desc: Create Video.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(testProperty);
    EXPECT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
}

/**
 * @tc.name: VideoPatternTest006
 * @tc.desc: Test AddPreviewNode
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoPatternTest006, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));

    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. check the children size.
     */
    auto children = frameNode->GetChildren();
    auto childrenSize = static_cast<int32_t>(children.size());
    EXPECT_EQ(childrenSize, VIDEO_CHILDREN_NUM);
    auto image = frameNode->GetChildAtIndex(1);
    EXPECT_EQ(image->GetTag(), V2::IMAGE_ETS_TAG);
}

/**
 * @tc.name: VideoPatternTest007
 * @tc.desc: Test AddControlBarNode
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. Add a child, in order to go to some branches
     */
    auto children = frameNode->GetChildren();
    auto childrenSize = static_cast<int32_t>(children.size());
    EXPECT_EQ(childrenSize, VIDEO_CHILDREN_NUM);
    auto row = frameNode->GetChildAtIndex(2);
    EXPECT_EQ(row->GetTag(), V2::ROW_ETS_TAG);
}

/**
 * @tc.name: VideoPatternTest008
 * @tc.desc: Test UpdateMediaPlayerOnBg
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. Call UpdateMediaPlayerOnBg
     *            case: IsMediaPlayerValid is always false
     * @tc.expected: step2. IsMediaPlayerValid will be called 3 times
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(3)
        .WillRepeatedly(Return(false));
    pattern->UpdateMediaPlayerOnBg();

    /**
     * @tc.steps: step3. Call UpdateMediaPlayerOnBg
     *            case: IsMediaPlayerValid is always true & has not set VideoSource
     * @tc.expected: step3. IsMediaPlayerValid will be called 3 times.
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(3)
        .WillRepeatedly(Return(true));
    pattern->UpdateMediaPlayerOnBg();

    /**
     * @tc.steps: step4. Call UpdateMediaPlayerOnBg
     *            case: IsMediaPlayerValid is always true & has set VideoSource
     * @tc.expected: step4. IsMediaPlayerValid will be called 5 times
     */
    auto videoLayoutProperty = pattern->GetLayoutProperty<VideoLayoutProperty>();
    auto videoSrcInfo = videoLayoutProperty->GetVideoSourceValue(VideoSourceInfo());
    videoSrcInfo.src_ = VIDEO_SRC;
    videoLayoutProperty->UpdateVideoSource(videoSrcInfo);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(5)
        .WillRepeatedly(Return(true));

    pattern->UpdateMediaPlayerOnBg();

    /**
     * @tc.steps: step5. Call UpdateMediaPlayerOnBg
     *            case: IsMediaPlayerValid is always true & has set VideoSource & has set videoSrcInfo_.src_
     * @tc.expected: step5. IsMediaPlayerValid will be called 3 times.
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(3)
        .WillRepeatedly(Return(true));
    pattern->UpdateMediaPlayerOnBg();

    /**
     * @tc.steps: step6. Call UpdateMediaPlayerOnBg
     *            case: first prepare and UpdateMediaPlayerOnBg successfully
     * @tc.expected: step6. IsMediaPlayerValid will be called 5 times
     *                      other function will be called once and return right value when preparing MediaPlayer
     *                      firstly
     */
    pattern->videoSrcInfo_.src_.clear();
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(5)
        .WillOnce(Return(false))
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillOnce(Return(true));

    pattern->UpdateMediaPlayerOnBg();

    /**
     * @tc.steps: step7. Call UpdateMediaPlayerOnBg several times
     *            cases: first prepare and UpdateMediaPlayerOnBg fail
     * @tc.expected: step7. IsMediaPlayerValid will be called 5 + 5 + 5 times totally.
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(15)
        // 1st time.
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillOnce(Return(true))

        // 2nd time.
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillOnce(Return(true))

        // 3rd time.
        .WillOnce(Return(false))
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillOnce(Return(true));
    pattern->videoSrcInfo_.src_.clear();
    pattern->UpdateMediaPlayerOnBg();
    pattern->videoSrcInfo_.src_.clear();
    pattern->UpdateMediaPlayerOnBg();
    pattern->videoSrcInfo_.src_.clear();
    pattern->UpdateMediaPlayerOnBg();

    // CreateMediaPlayer success but PrepareMediaPlayer fail for mediaPlayer is invalid
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(5)
        .WillOnce(Return(false))
        .WillOnce(Return(true))
        .WillOnce(Return(false))
        .WillOnce(Return(false))
        .WillOnce(Return(false));
    pattern->videoSrcInfo_.src_.clear();
    pattern->UpdateMediaPlayerOnBg();
}

/**
 * @tc.name: VideoPatternTest009
 * @tc.desc: Test functions in UpdateMediaPlayerOnBg
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. Call UpdateSpeed
     *            cases: MediaPlayer is valid and MediaPlayer is invalid
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(2)
        .WillOnce(Return(false))
        .WillOnce(Return(true));
    pattern->UpdateSpeed();
    pattern->UpdateSpeed();

    /**
     * @tc.steps: step3. Call UpdateLooping
     *            cases: MediaPlayer is valid and MediaPlayer is invalid
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(2)
        .WillOnce(Return(false))
        .WillOnce(Return(true));
    pattern->UpdateLooping();
    pattern->UpdateLooping();

    /**
     * @tc.steps: step4. Call UpdateMuted
     *            cases: MediaPlayer is valid (with muted and not muted) and MediaPlayer is invalid
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(3)
        .WillOnce(Return(false))
        .WillOnce(Return(true))
        .WillOnce(Return(true));
    pattern->UpdateMuted();
    pattern->muted_ = false;
    pattern->UpdateMuted();
    pattern->muted_ = true;
    pattern->UpdateMuted();
}

/**
 * @tc.name: VideoPatternTest010
 * @tc.desc: Test OnPlayerStatus
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoPatternTest010, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(testProperty);
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
    auto videoEventHub = frameNode->GetOrCreateEventHub<VideoEventHub>();
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
 * @tc.name: VideoPatternTest011
 * @tc.desc: Test OnPrepared
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoPatternTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern);

    // set videoEvent
    auto videoEventHub = frameNode->GetOrCreateEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub);
    std::string preparedCheck;
    VideoEventCallback onPrepared = [&preparedCheck](
                                        const std::string& /* param */) { preparedCheck = VIDEO_PREPARED_EVENT; };
    videoEventHub->SetOnPrepared(std::move(onPrepared));
    auto videoLayoutProperty = pattern->GetLayoutProperty<VideoLayoutProperty>();

    /**
     * @tc.steps: step2. Call OnPrepared
     *            case1: needControlBar & needFireEvent = true, isStop_ & autoPlay_ = false
     * @tc.expected: step2. FirePreparedEvent will be called & duration_ has changed
     */
    EXPECT_TRUE(videoLayoutProperty->GetControlsValue(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(3)
        .WillRepeatedly(Return(true));
    pattern->OnPrepared(DURATION, 0, true);
    EXPECT_EQ(pattern->duration_, DURATION);
    EXPECT_EQ(preparedCheck, VIDEO_PREPARED_EVENT);

    /**
     * @tc.steps: step3. Call OnPrepared
     *            case2: needControlBar & needFireEvent = false, isStop_ & autoPlay_ = true
     * @tc.expected: step3. FirePreparedEvent will not be called & duration_ has changed
     */
    preparedCheck.clear();
    pattern->duration_ = 0;
    pattern->isStop_ = true;
    pattern->autoPlay_ = true;
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(8)
        .WillRepeatedly(Return(true));
    pattern->OnPrepared(DURATION, 0, false);
    EXPECT_EQ(pattern->duration_, DURATION);
    EXPECT_TRUE(preparedCheck.empty());
    pattern->isStop_ = false;
    pattern->OnPrepared(DURATION, 0, false);
    EXPECT_EQ(pattern->duration_, DURATION);
    EXPECT_TRUE(preparedCheck.empty());
}

/**
 * @tc.name: VideoPatternTest012
 * @tc.desc: Test Start & Stop
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoPatternTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern);

    auto imageFrameNode = frameNode->GetChildAtIndex(0);
    auto rawChildNum = static_cast<int32_t>(frameNode->GetChildren().size());

    // set video event
    auto videoEventHub = pattern->GetOrCreateEventHub<VideoEventHub>();
    std::string pauseCheck;
    VideoEventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    videoEventHub->SetOnPause(std::move(onPause));
    std::string updateCheck;
    VideoEventCallback onUpdate = [&updateCheck](const std::string& /* param */) { updateCheck = VIDEO_UPDATE_EVENT; };
    videoEventHub->SetOnUpdate(std::move(onUpdate));
    std::string stopCheck;
    VideoEventCallback onStop = [&stopCheck](const std::string& /* param */) { stopCheck = VIDEO_STOP_EVENT; };
    videoEventHub->SetOnStop(std::move(onStop));

    /**
     * @tc.steps: step2. Call Start
     * @tc.expected: step2. relevant functions called correctly
     */
    bool isStops[2] { true, false };
    int32_t prepareReturns[2] { -1, 0 };
    for (bool isStop : isStops) {
        for (int prepareReturn : prepareReturns) {
            pattern->isStop_ = isStop;
            if (isStop) {
                EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), PrepareAsync())
                    .WillOnce(Return(prepareReturn));
            }
            if (isStop && prepareReturn != 0) {
                pattern->Start();
            } else if (isStop && prepareReturn == 0) {
                pattern->isPlaying_ = true;
                pattern->Start();
                auto childNum = static_cast<int32_t>(frameNode->GetChildren().size());
                EXPECT_EQ(childNum, rawChildNum);
            }
        }
    }

    /**
     * @tc.steps: step3. Call Stop when the mediaplayer is not valid.
     * @tc.expected: step3. relevant functions called correctly
     */
    pattern->currentPos_ = 10;
    pattern->isStop_ = false;
    pattern->Stop();
    EXPECT_EQ(static_cast<int32_t>(pattern->currentPos_), 0);
    EXPECT_TRUE(pattern->isStop_);

    /**
     * @tc.steps: step3. Call Stop when the mediaplayer is valid.
     * @tc.expected: step3. relevant functions called correctly
     */
    pattern->currentPos_ = 10;
    pattern->isStop_ = false;
    pattern->duration_ = 20;
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), Stop()).WillOnce(Return(0));
    pattern->Stop();
    EXPECT_EQ(static_cast<int32_t>(pattern->currentPos_), 0);
    EXPECT_TRUE(pattern->isStop_);

    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), Stop()).WillOnce(Return(0));
    EXPECT_EQ(static_cast<int32_t>(pattern->currentPos_), 0);
    pattern->Stop(); // case2: media player is valid & currentPos = currentPos_ = 0
    EXPECT_TRUE(pattern->isStop_);

    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), Stop())
        .Times(2)
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), GetDuration(_)).Times(0);
    updateCheck.clear();
    pattern->currentPos_ = 1;
    pattern->Stop(); // case3: media player is valid & currentPos != currentPos_ & duration_ = 0 &
                     // mediaPlayer_->GetDuration return ok
                     // this will call OnUpdateTime(pos=DURATION_POS)
    EXPECT_EQ(static_cast<int32_t>(pattern->currentPos_), 1);
    EXPECT_EQ(updateCheck, "");
    EXPECT_TRUE(pattern->isStop_);
    updateCheck.clear();
    pattern->currentPos_ = 1;
    pattern->Stop(); // case4: media player is valid & currentPos != currentPos_ & duration_ = 0 &
                     // mediaPlayer_->GetDuration return err
    EXPECT_EQ(static_cast<int32_t>(pattern->currentPos_), 1);
    EXPECT_EQ(updateCheck, "");
    EXPECT_TRUE(pattern->isStop_);
}

/**
 * @tc.name: VideoPatternTest013
 * @tc.desc: Test function related to full screen and slider
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoPatternTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    testProperty.videoController = videoController;
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern);

    // Add a redundant node to go other branch
    auto tempFrameNode = AceType::MakeRefPtr<FrameNode>("TEMP", -1, AceType::MakeRefPtr<Pattern>());
    frameNode->AddChild(tempFrameNode, 0);

    // set video event
    auto videoEventHub = frameNode->GetOrCreateEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub);
    std::string seekingCheck;
    VideoEventCallback onSeeking = [&seekingCheck](
                                       const std::string& /* param */) { seekingCheck = VIDEO_SEEKING_EVENT; };
    videoEventHub->SetOnSeeking(std::move(onSeeking));
    std::string seekedCheck;
    VideoEventCallback onSeeked = [&seekedCheck](const std::string& /* param */) { seekedCheck = VIDEO_SEEKED_EVENT; };
    videoEventHub->SetOnSeeked(std::move(onSeeked));

    /**
     * @tc.steps: step2. call OnSliderChange
     * @tc.expected: step2. onSeeking/onSeeked & SetCurrentTime  will be called
     */
    std::vector<int32_t> sliderChangeModes { 0, 1, 2 };
    for (int i = 0; i < 3; i++) {
        auto sliderChangeMode = sliderChangeModes[i];
        if (i == 1) {
            EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), Seek(_, _)).Times(0);
        }
        if (i < 2) {
            seekingCheck.clear();
            pattern->OnSliderChange(0, sliderChangeMode);
            EXPECT_EQ(seekingCheck, VIDEO_SEEKING_EVENT);
        } else {
            seekedCheck.clear();
            pattern->OnSliderChange(-1, sliderChangeMode); // currentPos(-1) < 0
            EXPECT_EQ(seekedCheck, VIDEO_SEEKED_EVENT);

            seekedCheck.clear();
            pattern->OnSliderChange(1, sliderChangeMode); // currentPos(1) > duration_(0)
            EXPECT_EQ(seekedCheck, VIDEO_SEEKED_EVENT);
        }
    }
}

/**
 * @tc.name: VideoPatternTest014
 * @tc.desc: Test OnResolutionChange
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoPatternTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. Call OnResolutionChange
     * @tc.expected: step2. related functions will be called
     */
    pattern->OnResolutionChange();

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    EXPECT_TRUE(videoLayoutProperty->HasVideoSize());
    EXPECT_EQ(videoLayoutProperty->GetVideoSizeValue(SizeF(0, 0)).Width(), 100);
    EXPECT_EQ(videoLayoutProperty->GetVideoSizeValue(SizeF(0, 0)).Height(), 100);
}

/**
 * @tc.name: VideoFocusTest001
 * @tc.desc: Create Video, and test focus.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoFocusTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(testProperty);
    EXPECT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    frameNode->GetOrCreateFocusHub()->currentFocus_ = true;
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern);
    EXPECT_EQ(pattern->GetFocusPattern().focusType_, FocusType::SCOPE);
}

/**
 * @tc.name: VideoFocusTest002
 * @tc.desc: Create Video, and test focus and children node focus.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoFocusTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(testProperty);
    EXPECT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    frameNode->GetOrCreateFocusHub()->currentFocus_ = true;
    auto videoPattern = frameNode->GetPattern<VideoPattern>();
    CHECK_NULL_VOID(videoPattern);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(true));

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_NE(videoLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapper and set videoLayoutAlgorithm.
     * @tc.expected: step2. Create video pattern and node successfully.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto videoLayoutAlgorithm = videoPattern->CreateLayoutAlgorithm();
    ASSERT_NE(videoLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(videoLayoutAlgorithm));

    /**
     * @tc.steps: step3. Set source size and layout size.
     * @tc.expected: step3. Set successfully.
     */
    LayoutConstraintF layoutConstraint;
    videoLayoutProperty->UpdateVideoSize(VIDEO_SIZE);
    layoutConstraint.selfIdealSize.SetSize(VIDEO_SIZE);
    auto videoSize1 =
        videoLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value_or(SizeF(0.0f, 0.0f));
    EXPECT_EQ(videoSize1, SizeF(VIDEO_WIDTH, VIDEO_WIDTH));
    layoutWrapper.GetGeometryNode()->SetContentSize(videoSize1);

    /**
     * @tc.steps: step4. Set the framenode tree, and test the focus.
     * @tc.expected: step4. Test focus on child successfully.
     */
    frameNode->GetOrCreateFocusHub()->RequestFocusImmediately();

    for (const auto& child : frameNode->GetChildren()) {
        if (child->GetTag() == V2::ROW_ETS_TAG) {
            auto slider = AceType::DynamicCast<FrameNode>(child->GetChildAtIndex(SLIDER_INDEX));
            EXPECT_EQ(slider->GetOrCreateFocusHub()->IsFocusable(), true);
            break;
        }
    }
}

/**
 * @tc.name: VideoAccessibilityPropertyTest001
 * @tc.desc: Test the text property of VideoAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoAccessibilityPropertyTest001, TestSize.Level1)
{
    VideoModelNG video;
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    ASSERT_NE(videoController, nullptr);
    video.Create(videoController);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));

    auto videoAccessibilitProperty = frameNode->GetAccessibilityProperty<VideoAccessibilityProperty>();
    ASSERT_NE(videoAccessibilitProperty, nullptr);
    EXPECT_EQ(videoAccessibilitProperty->GetText(), "");

    video.SetSrc(VIDEO_SRC, "", "");
    EXPECT_EQ(videoAccessibilitProperty->GetText(), VIDEO_SRC);
}

/**
 * @tc.name: VideoAccessibilityPropertyTest002
 * @tc.desc: Test the rangeInfo property of VideoAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoAccessibilityPropertyTest002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto videoAccessibilitProperty = frameNode->GetAccessibilityProperty<VideoAccessibilityProperty>();
    ASSERT_NE(videoAccessibilitProperty, nullptr);
    EXPECT_TRUE(videoAccessibilitProperty->HasRange());
    auto accessibilityValue = videoAccessibilitProperty->GetAccessibilityValue();
    EXPECT_EQ(accessibilityValue.min, 0);
    EXPECT_EQ(accessibilityValue.max, 0);
    EXPECT_EQ(accessibilityValue.current, 0);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(true));
    pattern->OnPrepared(DURATION, 0, true);
    EXPECT_EQ(pattern->duration_, DURATION);
    pattern->currentPos_ = CURRENT_TIME;
    accessibilityValue = videoAccessibilitProperty->GetAccessibilityValue();
    EXPECT_EQ(accessibilityValue.min, 0);
    EXPECT_EQ(accessibilityValue.max, DURATION);
    EXPECT_EQ(accessibilityValue.current, CURRENT_TIME);

    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), Stop()).WillOnce(Return(0));
    pattern->Stop();
    accessibilityValue = videoAccessibilitProperty->GetAccessibilityValue();
    EXPECT_EQ(accessibilityValue.current, 0);

    /**
     * @tc.steps: step2. call FullScreen
     * @tc.expected: step2. GetAccessibilityValue (pattern->IsFullScreen() == true) will be called
     */
    pattern->FullScreen();
    EXPECT_TRUE(pattern->GetFullScreenNode() != nullptr);
    accessibilityValue = videoAccessibilitProperty->GetAccessibilityValue();
}

/**
 * @tc.name: VideoPatternTest016
 * @tc.desc: Test full screen button click event
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoPatternTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    testProperty.videoController = videoController;
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern);

    // Add a redundant node to go other branch
    auto tempFrameNode = AceType::MakeRefPtr<FrameNode>("TEMP", -1, AceType::MakeRefPtr<Pattern>());
    frameNode->AddChild(tempFrameNode, 0);

    // set video event
    auto videoEventHub = frameNode->GetOrCreateEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub);

    std::string fullScreenCheck;
    VideoEventCallback onFullScreenChange = [&fullScreenCheck](const std::string& param) { fullScreenCheck = param; };
    videoEventHub->SetOnFullScreenChange(std::move(onFullScreenChange));

    /**
     * @tc.steps: step2. call FullScreen & ExitFullScreen
     * @tc.expected: step3. onFullScreenChange(true / false)  will be called
     */
    auto json = JsonUtil::Create(true);
    json->Put("fullscreen", true);
    auto fullScreenTrue = json->ToString();
    pattern->FullScreen(); // will called onFullScreenChange(true)
    EXPECT_TRUE(pattern->GetFullScreenNode() != nullptr);
    EXPECT_EQ(fullScreenCheck, fullScreenTrue);

    fullScreenCheck.clear();
    pattern->FullScreen(); // call again, nothing will happen
    EXPECT_TRUE(pattern->GetFullScreenNode() != nullptr);
    EXPECT_TRUE(fullScreenCheck.empty());

    // get the full screen svg node & get its gestureEventHub
    auto fullScreenNode = pattern->GetFullScreenNode();
    const auto& children = fullScreenNode->GetChildren();
    RefPtr<UINode> controlBar = nullptr;
    for (const auto& child : children) {
        if (child->GetTag() == V2::ROW_ETS_TAG) {
            controlBar = child;
        }
    }
    ASSERT_TRUE(controlBar);
    auto fsBtn = AceType::DynamicCast<FrameNode>(controlBar->GetChildAtIndex(4));
    ASSERT_TRUE(fsBtn);
    auto fsEvent = fsBtn->GetOrCreateGestureEventHub();

    fsEvent->ActClick(); // this will call ExitFullScreen()
    json = JsonUtil::Create(true);
    json->Put("fullscreen", false);
    auto fullScreenFalse = json->ToString();
    EXPECT_TRUE(pattern->GetFullScreenNode() == nullptr);
    EXPECT_EQ(fullScreenCheck, fullScreenFalse);

    fullScreenCheck.clear();

    const auto& videoChildren = frameNode->GetChildren();
    RefPtr<UINode> videoControlBar = nullptr;
    for (const auto& child : videoChildren) {
        if (child->GetTag() == V2::ROW_ETS_TAG) {
            videoControlBar = child;
        }
    }
    ASSERT_TRUE(videoControlBar);
    auto videoBtn = AceType::DynamicCast<FrameNode>(videoControlBar->GetChildAtIndex(4));
    ASSERT_TRUE(videoBtn);
    auto videoEvent = videoBtn->GetOrCreateGestureEventHub();
    videoEvent->ActClick(); // this will call FullScreen()
    EXPECT_TRUE(pattern->GetFullScreenNode() != nullptr);

    /**
     * @tc.steps: step4. call OnBackPressed
     * @tc.expected: step4. ExitFullScreen() will be called
     */
    // construct a FullScreenManager
    auto rootNode = MockPipelineContext::GetCurrent()->rootNode_;
    auto fullScreenManager = AceType::MakeRefPtr<FullScreenManager>(rootNode);

    auto flag = fullScreenManager->OnBackPressed(); // will on videoPattern->OnBackPressed()
    EXPECT_TRUE(flag);
    EXPECT_TRUE(pattern->GetFullScreenNode() == nullptr);
    EXPECT_EQ(fullScreenCheck, fullScreenFalse);

    rootNode->AddChild(tempFrameNode);
    flag = fullScreenManager->OnBackPressed(); // call again, nothing happen
    EXPECT_FALSE(flag);

    pattern->OnBackPressed(); // nothing will happen
    EXPECT_TRUE(pattern->GetFullScreenNode() == nullptr);

    /**
     * @tc.steps: step5. call FullScreen & ExitFullScreen in videoController
     *                   note: just test ExitFullscreen(issync = true), other functions are async
     * @tc.expected: step5. onFullScreenChange(true / false)  will be called
     */
    pattern->FullScreen();
    EXPECT_TRUE(pattern->GetFullScreenNode() != nullptr);
    EXPECT_EQ(fullScreenCheck, fullScreenTrue);
    videoController->ExitFullscreen(false); // nothing will happen for it's async
    EXPECT_TRUE(pattern->GetFullScreenNode() != nullptr);
    videoController->ExitFullscreen(true);
    EXPECT_FALSE(pattern->GetFullScreenNode() != nullptr);
    EXPECT_EQ(fullScreenCheck, fullScreenFalse);
}

/**
 * @tc.name: VideoNodeTest001
 * @tc.desc: Create Video.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    auto videoNode = VideoNode::GetOrCreateVideoNode(V2::VIDEO_ETS_TAG, VIDEO_NODE_ID_1,
        [videoController]() { return AceType::MakeRefPtr<VideoPattern>(videoController); });
    EXPECT_TRUE(videoNode);
    EXPECT_EQ(videoNode->GetTag(), V2::VIDEO_ETS_TAG);

    auto secondVideoNode = VideoNode::GetOrCreateVideoNode(V2::VIDEO_ETS_TAG, VIDEO_NODE_ID_1,
        [videoController]() { return AceType::MakeRefPtr<VideoPattern>(videoController); });
    EXPECT_TRUE(secondVideoNode);
    EXPECT_EQ(videoNode->GetTag(), secondVideoNode->GetTag());
    EXPECT_EQ(videoNode->GetId(), secondVideoNode->GetId());

    /**
     * @tc.steps: step2. Create Video again
     * @tc.expected: step2. Create Video node successfully
     */
    auto thirdVideoNode = VideoNode::GetOrCreateVideoNode(V2::VIDEO_ETS_TAG, VIDEO_NODE_ID_2,
        [videoController]() { return AceType::MakeRefPtr<VideoPattern>(videoController); });
    EXPECT_TRUE(secondVideoNode);
    EXPECT_EQ(videoNode->GetTag(), thirdVideoNode->GetTag());
    EXPECT_NE(videoNode->GetId(), thirdVideoNode->GetId());

    /**
     * @tc.steps: step3. Create Video again
     * @tc.expected: step3. Get tag is different
     */
    auto fourthVideoNode = VideoNode::GetOrCreateVideoNode("test", VIDEO_NODE_ID_2,
        [videoController]() { return AceType::MakeRefPtr<VideoPattern>(videoController); });
    ASSERT_TRUE(fourthVideoNode);
    EXPECT_NE(fourthVideoNode->GetTag(), thirdVideoNode->GetTag());
    EXPECT_EQ(fourthVideoNode->GetId(), thirdVideoNode->GetId());
}

/**
 * @tc.name: VideoPatternEventTest001
 * @tc.desc: Create Video and test onerror event.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoPatternEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    VideoModelNG video;
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    ASSERT_NE(videoController, nullptr);
    video.Create(videoController);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));

    /**
     * @tc.steps: step2. Execute onerror
     * @tc.expected: step1. Execute onerror successfully
     */
    std::string result;
    auto errorCallback = [&result](const std::string& error) { result = VIDEO_CALLBACK_RESULT; };
    auto eventHub = pattern->GetOrCreateEventHub<VideoEventHub>();
    eventHub->SetOnError(std::move(errorCallback));
    pattern->OnError(VIDEO_ERROR_ID);
    EXPECT_EQ(result, VIDEO_CALLBACK_RESULT);
    result = "";
    pattern->OnError(VIDEO_CODE, VIDEO_MESSAGE);
    EXPECT_EQ(result, VIDEO_CALLBACK_RESULT);
}

/**
 * @tc.name: VideoPatternEventTest002
 * @tc.desc: Create Video and test onvisiblechange event.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoPatternEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    VideoModelNG video;
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    ASSERT_NE(videoController, nullptr);
    video.Create(videoController);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));

    bool result;

    /**
     * @tc.steps: step2. Make video visible
     * @tc.expected: step2. Video callback result is false.
     */
    auto visibleChangeCallback = [&result](bool visible) { result = visible; };
    pattern->SetHiddenChangeEvent(std::move(visibleChangeCallback));
    pattern->OnVisibleChange(true);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. Make video visible false
     * @tc.expected: step3. Video callback result is true.
     */
    pattern->OnVisibleChange(false);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step4. Make hiddenChangeEvent_ nullptr
     * @tc.expected: step4. hiddenChangeEvent_ is nullptr.
     */
    pattern->SetHiddenChangeEvent(nullptr);
    pattern->OnVisibleChange(false);
    EXPECT_FALSE(pattern->hiddenChangeEvent_);
}

/**
 * @tc.name: VideoPatternPlayerTest001
 * @tc.desc: Create Video and test HasPlayer() func.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, VideoPatternPlayerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    VideoModelNG video;
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    ASSERT_NE(videoController, nullptr);
    video.Create(videoController);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(true));

    /**
     * @tc.steps: step2. Make video
     * @tc.expected: step2. Video HasPlayer Func result is true.
     */
    bool result = pattern->HasPlayer();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CallVideoPatternOnWindowHide
 * @tc.desc: Test VideoPattern OnWindowHide() func.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, CallVideoPatternOnWindowHide, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. call OnWindowHide
     * @tc.expected: step2. video will pause, isPaused_ is true.
     */
    pattern->OnWindowHide();
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(true));
    EXPECT_TRUE(pattern->isPaused_);
}

/**
 * @tc.name: CallVideoPatternToJsonValue
 * @tc.desc: Test VideoPattern ToJsonValue() func.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, CallVideoPatternToJsonValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. call ToJsonValue
     * @tc.expected: step2. filter.IsFastFilter() is false.
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    pattern->ToJsonValue(json, filter);
    EXPECT_FALSE(filter.IsFastFilter());
    EXPECT_EQ(json->GetValue("enableAnalyzer")->GetString().c_str(), JSON_VALUE_FALSE);

    /**
     * @tc.steps: step3. call ToJsonValue
     * @tc.expected: step3. filter.IsFastFilter() is true.
     */
    auto jsonSecond = JsonUtil::Create(true);
    filter.AddFilterAttr("id");
    pattern->ToJsonValue(jsonSecond, filter);
    EXPECT_TRUE(filter.IsFastFilter());
    EXPECT_FALSE(jsonSecond->Contains("enableAnalyzer"));
}

/**
 * @tc.name: CallVideoPatternOnStartRenderFrameCb
 * @tc.desc: Test VideoPattern OnStartRenderFrameCb() func.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, CallVideoPatternOnStartRenderFrameCb, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. call OnStartRenderFrameCb
     * @tc.expected: step2. call IsMediaPlayerValid() once.
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(true));
    pattern->OnStartRenderFrameCb();
}

/**
 * @tc.name: CallVideoPatternMoveByStepFunc
 * @tc.desc: Test VideoPattern MoveByStep() func.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, CallVideoPatternMoveByStepFunc, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: Create Video successfully
     */
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. call MoveByStep, parameter is abnormal
     * @tc.expected: currentPos_ will not change.
     */
    int32_t step = -1;
    pattern->currentPos_ = 0;
    pattern->MoveByStep(step);
    EXPECT_EQ(pattern->currentPos_, 0);
    step = pattern->duration_ + 1;
    pattern->MoveByStep(step);
    EXPECT_EQ(pattern->currentPos_, 0);
}

/**
 * @tc.name: CallVideoPatternAdjustVolumeFunc
 * @tc.desc: Test VideoPattern AdjustVolume() func.
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, CallVideoPatternAdjustVolumeFunc, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: Create Video successfully
     */
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. call AdjustVolume, parameter is abnormal
     * @tc.expected: currentVolume_ will not change.
     */
    int32_t step = 0;
    pattern->currentVolume_ = 0.0f;
    pattern->AdjustVolume(step);
    EXPECT_EQ(pattern->currentVolume_, 0);
    step = 1;
    pattern->currentVolume_ = 1.0f;
    pattern->AdjustVolume(step);
    EXPECT_EQ(pattern->currentVolume_, 1);
}

/**
 * @tc.name: Test VideoPattern SetVideoController
 * @tc.desc: Test VideoPattern SetVideoController() func
 * @tc.type: FUNC
 */
HWTEST_F(VideoTestNg, CallVideoPatternSetVideoControllerFunc, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: Create Video successfully
     */
    testProperty.videoController = nullptr;
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. call SetVideoController
     * @tc.expected: SetVideoController successfully
     */
    auto videoControllerInit = AceType::MakeRefPtr<VideoControllerV2>();
    pattern->SetVideoController(videoControllerInit);
    EXPECT_EQ(pattern->GetVideoController(), videoControllerInit);

    /**
     * @tc.steps: step3. call SetVideoController to update videoController
     * @tc.expected: VideoController is not updated.
     */
    auto videoControllerUpdate = AceType::MakeRefPtr<VideoControllerV2>();
    pattern->SetVideoController(videoControllerUpdate);
    EXPECT_NE(pattern->GetVideoController(), videoControllerUpdate);
}
} // namespace OHOS::Ace::NG
