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
const std::string VIDEO_START_EVENT = R"({"start":""})";
const std::string VIDEO_PAUSE_EVENT = R"({"pause":""})";
const std::string VIDEO_FINISH_EVENT = R"({"finish":""})";
const std::string VIDEO_ERROR_EVENT = R"({"error":""})";
const std::string VIDEO_ERROR_EVENT_WITH_PARAM = R"({"code":1,"name":"BusinessError","message":"message"})";
const std::string VIDEO_PREPARED_EVENT = R"({"duration":0})";
const std::string VIDEO_SEEKING_EVENT = R"({"time":0})";
const std::string VIDEO_SEEKED_EVENT = R"({"time":0})";
const std::string VIDEO_UPDATE_EVENT = R"({"time":0})";
const std::string VIDEO_FULLSCREEN_EVENT = R"({"fullscreen":true})";
const std::string EXTRA_INFO_KEY = "extraInfo";
const std::string VIDEO_ERROR_ID = "";
const int32_t VIDEO_CODE = 1;
const std::string VIDEO_MESSAGE = "message";
const std::string VIDEO_CALLBACK_RESULT = "result_ok";
const std::string VIDEO_STOP_EVENT = R"({"stop":""})";
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
constexpr uint32_t VIDEO_DURATION = 10u;
constexpr uint32_t VIDEO_CURRENT_TIME = 5u;
constexpr float VOLUME_STEP = 0.05f;
constexpr int32_t MILLISECONDS_TO_SECONDS = 1000;
TestProperty testProperty;
} // namespace

class VideoPropertyTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp();
    void TearDown() {}

protected:
    static RefPtr<FrameNode> CreateVideoNode(TestProperty& testProperty);
};

void VideoPropertyTestNg::SetUpTestSuite()
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

void VideoPropertyTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}
void VideoPropertyTestNg::SetUp()
{
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<FrameNode> VideoPropertyTestNg::CreateVideoNode(TestProperty& testProperty)
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
 * @tc.name: VideoPropertyTest002
 * @tc.desc: Create Vdeo, and set its properties.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPropertyTest002, TestSize.Level1)
{
    VideoModelNG video;
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    video.Create(videoController);

    auto frameNodeTemp = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNodeTemp);
    auto videoPatternTemp = AceType::DynamicCast<VideoPattern>(frameNodeTemp->GetPattern());
    CHECK_NULL_VOID(videoPatternTemp);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPatternTemp->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));

    video.SetSrc(VIDEO_SRC, "", "");
    video.SetProgressRate(VIDEO_PROGRESS_RATE);
    video.SetPosterSourceInfo(VIDEO_POSTER_URL, "", "");
    video.SetMuted(MUTED_VALUE);
    video.SetAutoPlay(AUTO_PLAY);
    video.SetControls(CONTROL_VALUE);
    video.SetLoop(LOOP_VALUE);
    video.SetObjectFit(VIDEO_IMAGE_FIT);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::VIDEO_ETS_TAG);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_NE(videoLayoutProperty, nullptr);
    auto videoPattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_NE(videoPattern, nullptr);

    EXPECT_EQ(videoLayoutProperty->GetVideoSourceValue(VideoSourceInfo()).src_, VIDEO_SRC);
    EXPECT_EQ(videoPattern->GetProgressRate(), VIDEO_PROGRESS_RATE);
    EXPECT_EQ(videoLayoutProperty->GetPosterImageInfoValue(ImageSourceInfo("")), ImageSourceInfo(VIDEO_POSTER_URL));
    EXPECT_EQ(videoPattern->GetMuted(), MUTED_VALUE);
    EXPECT_EQ(videoPattern->GetAutoPlay(), AUTO_PLAY);
    EXPECT_EQ(videoLayoutProperty->GetControlsValue(true), CONTROL_VALUE);
    EXPECT_EQ(videoPattern->GetLoop(), LOOP_VALUE);
    EXPECT_EQ(videoLayoutProperty->GetObjectFitValue(ImageFit::COVER), VIDEO_IMAGE_FIT);
}

/**
 * @tc.name: VideoEventTest003
 * @tc.desc: Create Video, and set its callback functions.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoEventTest003, TestSize.Level1)
{
    VideoModelNG video;
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    video.Create(videoController);

    auto frameNodeTemp = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNodeTemp);
    auto videoPatternTemp = AceType::DynamicCast<VideoPattern>(frameNodeTemp->GetPattern());
    CHECK_NULL_VOID(videoPatternTemp);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPatternTemp->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));

    std::string unknownVideoEvent;
    auto videoEvent = [&unknownVideoEvent](const std::string& videoEvent) { unknownVideoEvent = videoEvent; };

    video.SetOnStart(videoEvent);
    video.SetOnPause(videoEvent);
    video.SetOnFinish(videoEvent);
    video.SetOnError(videoEvent);
    video.SetOnPrepared(videoEvent);
    video.SetOnSeeking(videoEvent);
    video.SetOnSeeked(videoEvent);
    video.SetOnUpdate(videoEvent);
    video.SetOnStop(videoEvent);
    video.SetOnFullScreenChange(videoEvent);

    auto frameNode =ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::VIDEO_ETS_TAG);
    auto videoEventHub = frameNode->GetOrCreateEventHub<VideoEventHub>();
    EXPECT_TRUE(videoEventHub != nullptr);

    videoEventHub->FireStartEvent();
    EXPECT_EQ(unknownVideoEvent, VIDEO_START_EVENT);
    videoEventHub->FirePauseEvent();
    EXPECT_EQ(unknownVideoEvent, VIDEO_PAUSE_EVENT);
    videoEventHub->FireFinishEvent();
    EXPECT_EQ(unknownVideoEvent, VIDEO_FINISH_EVENT);
    videoEventHub->FireErrorEvent();
    EXPECT_EQ(unknownVideoEvent, VIDEO_ERROR_EVENT);
    videoEventHub->FireErrorEvent(VIDEO_CODE, VIDEO_MESSAGE);
    EXPECT_EQ(unknownVideoEvent, VIDEO_ERROR_EVENT_WITH_PARAM);
    videoEventHub->FirePreparedEvent(0.0);
    EXPECT_EQ(unknownVideoEvent, VIDEO_PREPARED_EVENT);
    videoEventHub->FireSeekingEvent(0.0);
    EXPECT_EQ(unknownVideoEvent, VIDEO_SEEKING_EVENT);
    videoEventHub->FireSeekedEvent(0.0);
    EXPECT_EQ(unknownVideoEvent, VIDEO_SEEKED_EVENT);
    videoEventHub->FireUpdateEvent(0.0);
    EXPECT_EQ(unknownVideoEvent, VIDEO_UPDATE_EVENT);
    videoEventHub->FireFullScreenChangeEvent(true);
    EXPECT_EQ(unknownVideoEvent, VIDEO_FULLSCREEN_EVENT);
    videoEventHub->FireStopEvent();
    EXPECT_EQ(unknownVideoEvent, VIDEO_STOP_EVENT);
}

/**
 * @tc.name: VideoMeasureContentTest004
 * @tc.desc: Create Video, and invoke its MeasureContent function to calculate the content size
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoMeasureContentTest004, TestSize.Level1)
{
    VideoModelNG video;
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    video.Create(videoController);

    auto frameNodeTemp = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNodeTemp, nullptr);
    auto videoPatternTemp = AceType::DynamicCast<VideoPattern>(frameNodeTemp->GetPattern());
    ASSERT_NE(videoPatternTemp, nullptr);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPatternTemp->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));

    auto frameNode =AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::VIDEO_ETS_TAG);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    EXPECT_NE(videoLayoutProperty, nullptr);

    // Create LayoutWrapper and set videoLayoutAlgorithm.
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto videoPattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_NE(videoPattern, nullptr);
    auto videoLayoutAlgorithm = videoPattern->CreateLayoutAlgorithm();
    EXPECT_NE(videoLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(videoLayoutAlgorithm));

    // Test MeasureContent.
    /**
    //     corresponding ets code:
    //         Video({ previewUri: this.previewUri, controller: this.controller })
    */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = MAX_SIZE;
    auto videoDefaultSize =
        videoLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value_or(SizeF(0.0f, 0.0f));
    EXPECT_EQ(videoDefaultSize, MAX_SIZE);

    /**
    //     corresponding ets code:
    //         Video({ src: this.videoSrc, previewUri: this.previewUri, controller: this.controller })
    //             .height(400).width(400)
    */
    // Set layout size.
    layoutConstraint.selfIdealSize.SetSize(VIDEO_SIZE);
    auto videoSize1 =
        videoLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value_or(SizeF(0.0f, 0.0f));
    EXPECT_EQ(videoSize1, VIDEO_SIZE);
}

/**
 * @tc.name: VideoMeasureTest005
 * @tc.desc: Create Video, and invoke its Measure and layout function, and test its child/children layout algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoMeasureTest005, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetRootSize(SCREEN_WIDTH_MEDIUM, SCREEN_HEIGHT_MEDIUM);
    VideoModelNG video;
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    video.Create(videoController);

    auto frameNodeTemp = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNodeTemp);
    auto videoPatternTemp = AceType::DynamicCast<VideoPattern>(frameNodeTemp->GetPattern());
    CHECK_NULL_VOID(videoPatternTemp);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPatternTemp->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));

    // when video set preview image and control, it will contains two children which are image and row respectively.
    video.SetPosterSourceInfo(VIDEO_POSTER_URL, "", "");
    video.SetControls(CONTROL_VALUE);

    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::VIDEO_ETS_TAG);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    EXPECT_FALSE(videoLayoutProperty == nullptr);

    // Create LayoutWrapper and set videoLayoutAlgorithm.
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto videoPattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_NE(videoPattern, nullptr);
    auto videoLayoutAlgorithm = videoPattern->CreateLayoutAlgorithm();
    ASSERT_NE(videoLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(videoLayoutAlgorithm));

    // Set video source size and layout size.
    LayoutConstraintF layoutConstraint;
    videoLayoutProperty->UpdateVideoSize(VIDEO_SIZE);
    layoutConstraint.selfIdealSize.SetSize(VIDEO_SIZE);
    auto videoSize1 =
        videoLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value_or(SizeF(0.0f, 0.0f));
    EXPECT_EQ(videoSize1, SizeF(VIDEO_WIDTH, VIDEO_WIDTH));
    layoutWrapper.GetGeometryNode()->SetContentSize(videoSize1);

    const auto& children = frameNode->GetChildren();
    for (const auto& child : children) {
        auto frameNodeChild = AceType::DynamicCast<FrameNode>(child);
        RefPtr<GeometryNode> geometryNodeChild = AceType::MakeRefPtr<GeometryNode>();
        auto childLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(AceType::WeakClaim(AceType::RawPtr(frameNodeChild)),
                geometryNodeChild, frameNodeChild->GetLayoutProperty());
        layoutWrapper.AppendChild(childLayoutWrapper);
    }

    videoLayoutAlgorithm->Measure(&layoutWrapper);
    videoLayoutAlgorithm->Layout(&layoutWrapper);

    auto layoutWrapperChildren = layoutWrapper.GetAllChildrenWithBuild();
    EXPECT_EQ(layoutWrapperChildren.size(), VIDEO_CHILDREN_NUM);
    for (auto&& child : layoutWrapperChildren) {
        if (child->GetHostTag() == V2::IMAGE_ETS_TAG) {
            EXPECT_EQ(child->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(0.0, 0.0));
        } else if (child->GetHostTag() == V2::ROW_ETS_TAG) {
            // controlBarHeight is 40 defined in theme, but pipeline context is null in UT which cannot get the value
            // when invoking video Measure function. So we assume the value is 0.0 here.
            float const controlBarHeight = 0.0;
            EXPECT_EQ(child->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(0.0, VIDEO_WIDTH - controlBarHeight));
        }
    }

    //Call Measure and Layout while video in full screen mode.
    videoPattern->FullScreen();
    ASSERT_TRUE(videoPattern->GetFullScreenNode());
    videoLayoutAlgorithm->Measure(&layoutWrapper);
    videoLayoutAlgorithm->Layout(&layoutWrapper);
    // check size.
    auto fullScreenNode = videoPattern->GetFullScreenNode();
    auto fullScreenPattern = fullScreenNode->GetPattern();
    ASSERT_TRUE(fullScreenPattern);
    auto fullScreenLayout = fullScreenPattern->CreateLayoutAlgorithm();
    auto fullScreenGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode fullScreenLayoutWrapper =
        LayoutWrapperNode(fullScreenNode, fullScreenGeometryNode, fullScreenNode->GetLayoutProperty());
    fullScreenLayoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(fullScreenLayout));
    auto videoSize =
        fullScreenLayout->MeasureContent(layoutConstraint, &fullScreenLayoutWrapper).value_or(SizeF(0.0f, 0.0f));
    EXPECT_EQ(videoSize, SCREEN_SIZE_MEDIUM);
}

/**
 * @tc.name: VideoFullScreenTest015
 * @tc.desc: Create Video, and invoke its MeasureContent function to calculate the content size when it is fullscreen.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoFullScreenTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    MockPipelineContext::GetCurrent()->SetRootSize(SCREEN_WIDTH_MEDIUM, SCREEN_HEIGHT_MEDIUM);
    VideoModelNG video;
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    video.Create(videoController);

    auto frameNodeTemp = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNodeTemp);
    auto videoPatternTemp = AceType::DynamicCast<VideoPattern>(frameNodeTemp->GetPattern());
    CHECK_NULL_VOID(videoPatternTemp);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPatternTemp->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));

    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::VIDEO_ETS_TAG);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    EXPECT_FALSE(videoLayoutProperty == nullptr);

    // Create LayoutWrapper and set videoLayoutAlgorithm.
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto videoPattern = frameNode->GetPattern<VideoPattern>();
    EXPECT_FALSE(videoPattern == nullptr);
    auto videoLayoutAlgorithm = videoPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(videoLayoutAlgorithm == nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(videoLayoutAlgorithm));
    videoPattern->FullScreen(); // will called onFullScreenChange(true)
    EXPECT_TRUE(videoPattern->GetFullScreenNode() != nullptr);

    // Test MeasureContent when it is fullScreen.
    /**
        corresponding ets code:
            Video({ src: this.videoSrc, previewUri: this.previewUri, controller: this.controller })
                .height(400).width(400)
    */

    // Set layout size.
    LayoutConstraintF layoutConstraint;
    videoLayoutProperty->UpdateVideoSize(VIDEO_SIZE);
    layoutConstraint.selfIdealSize.SetSize(VIDEO_SIZE);

    /**
     * @tc.steps: step2. change to full screen, check size.
     * @tc.expected: step2. Video size is same to rootsize.
     */
    auto fullScreenNode = videoPattern->GetFullScreenNode();
    auto fullScreenPattern = fullScreenNode->GetPattern();
    EXPECT_FALSE(fullScreenPattern == nullptr);
    auto fullScreenLayout = fullScreenPattern->CreateLayoutAlgorithm();
    auto fullScreenGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode fullScreenLayoutWrapper =
        LayoutWrapperNode(fullScreenNode, fullScreenGeometryNode, fullScreenNode->GetLayoutProperty());
    fullScreenLayoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(fullScreenLayout));
    auto videoSize =
        fullScreenLayout->MeasureContent(layoutConstraint, &fullScreenLayoutWrapper).value_or(SizeF(0.0f, 0.0f));
    EXPECT_EQ(videoSize, SCREEN_SIZE_MEDIUM);

    // Change the root size to small
    MockPipelineContext::GetCurrent()->SetRootSize(SCREEN_WIDTH_SMALL, SCREEN_HEIGHT_SMALL);
    auto size =
        fullScreenLayout->MeasureContent(layoutConstraint, &fullScreenLayoutWrapper).value_or(SizeF(0.0f, 0.0f));
    EXPECT_EQ(size, SCREEN_SIZE_SMALL);

    // Change the root size to large
    MockPipelineContext::GetCurrent()->SetRootSize(SCREEN_WIDTH_LARGE, SCREEN_HEIGHT_LARGE);
    videoSize =
        fullScreenLayout->MeasureContent(layoutConstraint, &fullScreenLayoutWrapper).value_or(SizeF(0.0f, 0.0f));
    EXPECT_EQ(videoSize, SCREEN_SIZE_LARGE);

    /**
     * @tc.steps: step3. change from full screen to normal size, check size.
     * @tc.expected: step2. Video size is same to origional size.
     */
    auto videoFullScreenNode1 = videoPattern->GetFullScreenNode();
    EXPECT_FALSE(videoFullScreenNode1 == nullptr);
    auto fullScreenPattern1 = AceType::DynamicCast<VideoFullScreenPattern>(videoFullScreenNode1->GetPattern());
    EXPECT_FALSE(fullScreenPattern1 == nullptr);
    fullScreenPattern1->ExitFullScreen(); // will called onFullScreenChange(true)
    EXPECT_TRUE(videoPattern->GetFullScreenNode() == nullptr);

    videoSize = videoLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value_or(SizeF(0.0f, 0.0f));
    EXPECT_EQ(videoSize, SizeF(VIDEO_WIDTH, VIDEO_HEIGHT));
}

/**
 * @tc.name: VideoPropertyTest016
 * @tc.desc: Create Video, and check the pixelmap.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPropertyTest016, TestSize.Level1)
{
    VideoModelNG video;
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    video.Create(videoController);

    /**
     * @tc.steps: step1. Create a video.
     * @tc.expected: step1. Create successfully.
     */
    auto frameNodeTemp = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNodeTemp);
    auto videoPatternTemp = AceType::DynamicCast<VideoPattern>(frameNodeTemp->GetPattern());
    CHECK_NULL_VOID(videoPatternTemp);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPatternTemp->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));

    /**
     * @tc.steps: step3. Set the preview by pixelmap.
     * @tc.expected: step2. Set the pixelmap successfully.
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    void* secondVoidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    RefPtr<PixelMap> secondPixelMap = PixelMap::CreatePixelMap(secondVoidPtr);

    // Default image and pixelmap image and url image.
    ImageSourceInfo defaultImage = ImageSourceInfo("");
    ImageSourceInfo pixelMapImage = ImageSourceInfo(pixelMap);
    ImageSourceInfo secondPixelMapImage = ImageSourceInfo(secondPixelMap);
    ImageSourceInfo urlImage = ImageSourceInfo(VIDEO_POSTER_URL);

    video.SetSrc(VIDEO_SRC, "", "");
    video.SetProgressRate(VIDEO_PROGRESS_RATE);
    video.SetPosterSourceByPixelMap(pixelMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::VIDEO_ETS_TAG);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    EXPECT_FALSE(videoLayoutProperty == nullptr);

    EXPECT_EQ(videoLayoutProperty->GetVideoSourceValue(VideoSourceInfo()).src_, VIDEO_SRC);
    EXPECT_EQ(videoLayoutProperty->GetPosterImageInfoValue(defaultImage), pixelMapImage);

    /**
     * @tc.steps: step3. Reset preview by another pixelmap.
     * @tc.expected: step2. Reset the pixelmap successfully.
     */
    video.SetPosterSourceByPixelMap(secondPixelMap);
    EXPECT_EQ(videoLayoutProperty->GetPosterImageInfoValue(defaultImage), secondPixelMapImage);

    video.SetPosterSourceInfo(VIDEO_POSTER_URL, "", "");
    EXPECT_EQ(videoLayoutProperty->GetPosterImageInfoValue(defaultImage), urlImage);

    video.SetPosterSourceByPixelMap(pixelMap);
    EXPECT_EQ(videoLayoutProperty->GetPosterImageInfoValue(defaultImage), pixelMapImage);
}

/**
 * @tc.name: VideoPatternTest017
 * @tc.desc: Test VideoPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a video and get the videoPattern.
     * @tc.expected: step1. Create and get successfully.
     */
    VideoModelNG videoModelNG;
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    videoModelNG.Create(videoController);
    auto frameNode = AceType::Claim<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    ASSERT_NE(videoPattern, nullptr);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));

    /**
     * @tc.steps: step2. Set skipMeasure property of drawSwapConfig.
     * @tc.expected: step2. LayoutWrapper swap failed.
     */
    DirtySwapConfig config;
    config.skipMeasure = true;
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_NE(videoLayoutProperty, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, videoLayoutProperty);
    layoutWrapper->skipMeasureContent_ = true;
    EXPECT_FALSE(videoPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    config.skipMeasure = false;
    EXPECT_FALSE(videoPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));

    /**
     * @tc.steps: step3. Set skipMeasure property of layoutAlgorithm.
     * @tc.expected: step3. LayoutWrapper swap failed.
     */
    config.skipMeasure = true;
    layoutWrapper->skipMeasureContent_ = false;
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(AceType::MakeRefPtr<LayoutAlgorithm>());
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithm;
    layoutWrapper->layoutAlgorithm_->skipMeasure_ = false;
    EXPECT_FALSE(videoPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));

    /**
     * @tc.steps: step4. Call function while videoSize is null.
     * @tc.expected: step4. LayoutWrapper swap failed.
     */
    config.skipMeasure = false;
    std::optional<SizeF> videoSize;
    std::unique_ptr<VideoStyle> tempPtr = std::make_unique<VideoStyle>();
    videoLayoutProperty->propVideoStyle_ = std::move(tempPtr);
    videoLayoutProperty->propVideoStyle_->propVideoSize = videoSize;
    geometryNode->SetContentSize(SizeF(SCREEN_WIDTH_SMALL, SCREEN_HEIGHT_SMALL));
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    videoPattern->renderContextForMediaPlayer_ = mockRenderContext;
    EXPECT_FALSE(videoPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: VideoPatternTest018
 * @tc.desc: Test VideoPattern OnAreaChangedInner
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a video and get the videoPattern.
     * @tc.expected: step1. Create and get successfully.
     */
    VideoModelNG videoModelNG;
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    videoModelNG.Create(videoController);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    ASSERT_NE(videoPattern, nullptr);

    /**
     * @tc.steps: step2. Set lastBoundsRect property.
     * @tc.expected: step1. Property set successfully.
     */
    SystemProperties::SetExtSurfaceEnabled(false);
    videoPattern->OnAreaChangedInner();
    videoPattern->fullScreenNodeId_ = std::make_optional<int32_t>(1);
    videoPattern->OnAreaChangedInner();
    SystemProperties::SetExtSurfaceEnabled(true);
    videoPattern->fullScreenNodeId_ = std::make_optional<int32_t>();
    videoPattern->OnAreaChangedInner();
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_NE(videoLayoutProperty, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    videoPattern->fullScreenNodeId_ = std::make_optional<int32_t>(1);
    videoLayoutProperty->UpdateObjectFit(ImageFit::CONTAIN);
    geometryNode->SetContentSize(SizeF(SCREEN_WIDTH_SMALL, 0.0f));
    videoLayoutProperty->propVideoStyle_->propVideoSize = SizeF(VIDEO_WIDTH, 0.0f);
    videoPattern->OnAreaChangedInner();
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Width(), SCREEN_WIDTH_SMALL);
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Height(), 0.0f);
    videoPattern->OnAreaChangedInner();
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Width(), SCREEN_WIDTH_SMALL);
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Height(), 0.0f);

    /**
     * @tc.steps: step3. Call function with different objectFit status.
     * @tc.expected: step3. VideoPattern lastBoundsRect_'s width and height set correctly.
     */
    videoLayoutProperty->UpdateObjectFit(ImageFit::CONTAIN);
    videoLayoutProperty->propVideoStyle_->propVideoSize = SizeF(VIDEO_WIDTH, VIDEO_HEIGHT);
    videoPattern->OnAreaChangedInner();
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Width(), SCREEN_WIDTH_SMALL);
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Height(), 0.0f);
    geometryNode->SetContentSize(SizeF(SCREEN_WIDTH_SMALL, SCREEN_HEIGHT_SMALL));
    videoLayoutProperty->propVideoStyle_->propVideoSize = SizeF(VIDEO_WIDTH, 0.0f);
    videoPattern->OnAreaChangedInner();
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Width(), SCREEN_WIDTH_SMALL);
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Height(), SCREEN_HEIGHT_SMALL);
    videoLayoutProperty->propVideoStyle_->propVideoSize = SizeF(VIDEO_WIDTH * 2, VIDEO_HEIGHT);
    videoPattern->OnAreaChangedInner();
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Width(), SCREEN_WIDTH_SMALL);
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Height(), SCREEN_WIDTH_SMALL / 2);
    geometryNode->SetContentSize(SizeF(SCREEN_WIDTH_SMALL * 6, SCREEN_HEIGHT_SMALL));
    videoPattern->OnAreaChangedInner();
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Width(), SCREEN_HEIGHT_SMALL * 2);
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Height(), SCREEN_HEIGHT_SMALL);

    videoLayoutProperty->UpdateObjectFit(ImageFit::FILL);
    geometryNode->SetContentSize(SizeF(SCREEN_WIDTH_SMALL, SCREEN_HEIGHT_SMALL));
    videoPattern->OnAreaChangedInner();
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Width(), SCREEN_WIDTH_SMALL);
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Height(), SCREEN_HEIGHT_SMALL);

    videoLayoutProperty->UpdateObjectFit(ImageFit::COVER);
    geometryNode->SetContentSize(SizeF(SCREEN_WIDTH_SMALL, 0.0f));
    videoLayoutProperty->propVideoStyle_->propVideoSize = SizeF(VIDEO_WIDTH, VIDEO_HEIGHT);
    videoPattern->OnAreaChangedInner();
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Width(), SCREEN_WIDTH_SMALL);
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Height(), 0.0f);
    geometryNode->SetContentSize(SizeF(SCREEN_WIDTH_SMALL, SCREEN_HEIGHT_SMALL));
    videoLayoutProperty->propVideoStyle_->propVideoSize = SizeF(VIDEO_WIDTH, 0.0f);
    videoPattern->OnAreaChangedInner();
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Width(), SCREEN_WIDTH_SMALL);
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Height(), SCREEN_HEIGHT_SMALL);
    videoLayoutProperty->propVideoStyle_->propVideoSize = SizeF(VIDEO_WIDTH * 2, VIDEO_HEIGHT);
    videoPattern->OnAreaChangedInner();
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Width(), SCREEN_HEIGHT_SMALL * 2);
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Height(), SCREEN_HEIGHT_SMALL);
    geometryNode->SetContentSize(SizeF(SCREEN_WIDTH_SMALL * 6, SCREEN_HEIGHT_SMALL));
    videoPattern->OnAreaChangedInner();
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Width(), SCREEN_WIDTH_SMALL * 6);
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Height(), SCREEN_WIDTH_SMALL * 3);

    videoLayoutProperty->UpdateObjectFit(ImageFit::NONE);
    videoLayoutProperty->propVideoStyle_->propVideoSize = SizeF(VIDEO_WIDTH, VIDEO_HEIGHT);
    videoPattern->OnAreaChangedInner();
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Width(), VIDEO_WIDTH);
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Height(), VIDEO_HEIGHT);

    videoLayoutProperty->UpdateObjectFit(ImageFit::SCALE_DOWN);
    geometryNode->SetContentSize(SizeF(SCREEN_WIDTH_SMALL, SCREEN_HEIGHT_SMALL));
    videoPattern->OnAreaChangedInner();
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Width(), VIDEO_WIDTH);
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Height(), VIDEO_HEIGHT);
    videoLayoutProperty->propVideoStyle_->propVideoSize = SizeF(VIDEO_WIDTH * 2, VIDEO_HEIGHT);
    videoPattern->OnAreaChangedInner();
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Width(), SCREEN_WIDTH_SMALL);
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Height(), SCREEN_WIDTH_SMALL / 2);

    videoLayoutProperty->UpdateObjectFit(ImageFit::FITHEIGHT);
    videoPattern->OnAreaChangedInner();
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Width(), SCREEN_WIDTH_SMALL * 4);
    EXPECT_FLOAT_EQ(videoPattern->lastBoundsRect_.Height(), SCREEN_HEIGHT_SMALL);
}

/**
 * @tc.name: VideoPatternTest019
 * @tc.desc: Test VideoPattern requestFullscreenImpl
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a video and get the videoPattern.
     * @tc.expected: step1. Create and get successfully.
     */
    VideoModelNG videoModelNG;
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    videoModelNG.Create(videoController);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    ASSERT_NE(videoPattern, nullptr);

    /**
     * @tc.steps: step2. Set controlBar Property.
     * @tc.expected: step2. Property set successfully.
     */
    frameNode->children_.clear();
    videoPattern->isPlaying_ = false;
    auto controlBar = videoPattern->CreateControlBar();
    auto playButton = AceType::DynamicCast<FrameNode>(controlBar->GetFirstChild());
    auto playBtnEvent = playButton->GetOrCreateGestureEventHub();
    auto playClickCallback = playBtnEvent->clickEventActuator_->userCallback_->callback_;
    GestureEvent gestureEvent;
    playClickCallback(gestureEvent);

    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto videoTheme = pipelineContext->GetTheme<VideoTheme>();
    ASSERT_NE(videoTheme, nullptr);
    EXPECT_EQ(controlBar->GetRenderContext()->GetBackgroundColorValue(), videoTheme->GetBkgColor());
    auto controlBarLayoutProperty = controlBar->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_EQ(controlBarLayoutProperty->GetMainAxisAlignValue(FlexAlign::AUTO), FlexAlign::SPACE_BETWEEN);
}

/**
 * @tc.name: VideoFullScreenTest001
 * @tc.desc: Test VideoFullScreenPattern UpdateState.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoFullScreenTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video and get fullScreenPattern.
     * @tc.expected: Create Video successfully.
     */
    MockPipelineContext::GetCurrent()->SetRootSize(SCREEN_WIDTH_MEDIUM, SCREEN_HEIGHT_MEDIUM);
    VideoModelNG video;
    video.Create(AceType::MakeRefPtr<VideoControllerV2>());
    auto videoNode =ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(videoNode, nullptr);
    auto videoPattern = videoNode->GetPattern<VideoPattern>();
    ASSERT_NE(videoPattern, nullptr);
    videoPattern->FullScreen();
    auto fullScreenNode = videoPattern->GetFullScreenNode();
    ASSERT_NE(fullScreenNode, nullptr);
    auto fullScreenPattern = fullScreenNode->GetPattern<VideoFullScreenPattern>();
    ASSERT_NE(fullScreenPattern, nullptr);

    /**
     * @tc.steps: step2. Call UpdateState when videoLayout's properties is equal or not equal to fullScreenLayout.
     * @tc.expected: FullScreenLayout's properties is set same to videoLayout.
     */
    auto videoLayout = videoNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_NE(videoLayout, nullptr);
    auto fullScreenLayout = fullScreenNode->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_NE(fullScreenLayout, nullptr);
    fullScreenPattern->UpdateState();
    EXPECT_FALSE(videoLayout->HasObjectFit());
    EXPECT_FALSE(videoLayout->HasVideoSource());
    EXPECT_FALSE(videoLayout->HasPosterImageInfo());
    EXPECT_FALSE(videoLayout->HasControls());
    videoLayout->UpdateObjectFit(ImageFit::COVER);
    fullScreenLayout->UpdateObjectFit(ImageFit::CONTAIN);
    auto videoSrcInfo = videoLayout->GetVideoSourceValue(VideoSourceInfo());
    videoSrcInfo.src_ = VIDEO_SRC;
    videoLayout->UpdateVideoSource(videoSrcInfo);
    videoSrcInfo.src_ = "";
    fullScreenLayout->UpdateVideoSource(videoSrcInfo);
    videoLayout->UpdatePosterImageInfo(ImageSourceInfo(VIDEO_POSTER_URL));
    fullScreenLayout->UpdatePosterImageInfo(ImageSourceInfo(""));
    videoLayout->UpdateControls(true);
    fullScreenLayout->UpdateControls(false);
    fullScreenPattern->UpdateState();
    EXPECT_EQ(fullScreenLayout->GetObjectFit().value(), ImageFit::COVER);
    EXPECT_EQ(fullScreenLayout->GetVideoSource().value().src_, VIDEO_SRC);
    EXPECT_EQ(fullScreenLayout->GetPosterImageInfo().value(), ImageSourceInfo(VIDEO_POSTER_URL));
    EXPECT_TRUE(fullScreenLayout->GetControls().value());
    fullScreenPattern->UpdateState();
}

/**
 * @tc.name: VideoPatternTest021
 * @tc.desc: Test VideoPattern ResetMediaPlayer.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video and get videoPattern.
     */
    VideoModelNG video;
    video.Create(AceType::MakeRefPtr<VideoControllerV2>());
    auto videoNode =ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(videoNode, nullptr);
    auto videoPattern = videoNode->GetPattern<VideoPattern>();
    ASSERT_NE(videoPattern, nullptr);

    /**
     * @tc.steps: step2. Call ResetMediaPlayer when mediaPlayer_ in different status.
     * @tc.expected: mediaPlayer_'s functions is called.
     */
    videoPattern->videoSrcInfo_.src_ = VIDEO_SRC;
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), SetSource(_, _, _))
        .WillOnce(Return(true))
        .WillOnce(Return(false))
        .WillOnce(Return(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), PrepareAsync())
        .WillOnce(Return(0))
        .WillOnce(Return(-1));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), SetRenderFirstFrame(false))
        .WillOnce(Return(0));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), SetRenderFirstFrame(true))
        .WillOnce(Return(0));
    videoPattern->showFirstFrame_ = false;
    videoPattern->ResetMediaPlayer();
    videoPattern->ResetMediaPlayer();
    videoPattern->showFirstFrame_ = true;
    videoPattern->ResetMediaPlayer();
    videoPattern->mediaPlayer_ = nullptr;
    videoPattern->SetSourceForMediaPlayer();
}

/**
 * @tc.name: VideoPatternTest022
 * @tc.desc: Test VideoPattern UpdateMediaPlayerOnBg.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video and get videoPattern.
     */
    VideoModelNG video;
    video.Create(AceType::MakeRefPtr<VideoControllerV2>());
    auto videoNode =ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(videoNode, nullptr);
    auto videoPattern = videoNode->GetPattern<VideoPattern>();
    ASSERT_NE(videoPattern, nullptr);

    /**
     * @tc.steps: step2. Call ResetMediaPlayer while autoPlay_ and isInitialState_ in different status.
     * @tc.expected: PrepareAsync is called only once.
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), PrepareAsync())
        .WillOnce(Return(-1));
    videoPattern->isStop_ = true;
    videoPattern->isInitialState_ = false;
    videoPattern->UpdateMediaPlayerOnBg();
    videoPattern->autoPlay_ = true;
    videoPattern->UpdateMediaPlayerOnBg();
    videoPattern->isInitialState_ = true;
    videoPattern->UpdateMediaPlayerOnBg();
}

/**
 * @tc.name: VideoPatternTest023
 * @tc.desc: Test VideoPattern OnCurrentTimeChange.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video and get videoPattern.
     */
    VideoModelNG video;
    video.Create(AceType::MakeRefPtr<VideoControllerV2>());
    auto videoNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(videoNode, nullptr);
    auto videoPattern = videoNode->GetPattern<VideoPattern>();
    ASSERT_NE(videoPattern, nullptr);

    /**
     * @tc.steps: step2. Call OnCurrentTimeChange with different duration.
     * @tc.expected: GetDuration is called twice.
     */
    videoPattern->duration_ = 0;
    videoPattern->currentPos_ = 0;
    videoPattern->isStop_ = false;
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), GetDuration(_))
        .WillOnce(Return(-1))
        .WillOnce(Return(0));
    videoPattern->OnCurrentTimeChange(1);
    videoPattern->duration_ = 0;
    videoPattern->currentPos_ = 0;
    videoPattern->isStop_ = false;
    videoPattern->OnCurrentTimeChange(1);

    /**
     * @tc.steps: step3. Call OnCurrentTimeChange while mediaPlayer_ is nullptr.
     * @tc.expected: GetDuration will not be called.
     */
    videoPattern->duration_ = 0;
    videoPattern->mediaPlayer_ = nullptr;
    videoPattern->OnCurrentTimeChange(2);
    EXPECT_EQ(videoPattern->duration_, 0);

    /**
     * @tc.steps: step4. Call OnCurrentTimeChange while isPrepared_ is true.
     * @tc.expected: isInitialState_ is false.
     */
    videoPattern->isInitialState_ = true;
    videoPattern->isPrepared_ = true;
    videoPattern->OnCurrentTimeChange(2);
    EXPECT_EQ(videoPattern->isInitialState_, false);

    /**
     * @tc.steps: step5. Call OnCurrentTimeChange while isPrepared_ is false.
     * @tc.expected: isInitialState_ is true.
     */
    videoPattern->isInitialState_ = true;
    videoPattern->isPrepared_ = false;
    videoPattern->OnCurrentTimeChange(2);
    EXPECT_EQ(videoPattern->isInitialState_, true);
}

/**
 * @tc.name: VideoPatternTest024
 * @tc.desc: Test VideoPattern HiddenChange.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video and get videoPattern.
     */
    VideoModelNG video;
    video.Create(AceType::MakeRefPtr<VideoControllerV2>());
    auto videoNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(videoNode, nullptr);
    auto videoPattern = videoNode->GetPattern<VideoPattern>();
    ASSERT_NE(videoPattern, nullptr);

    /**
     * @tc.steps: step2. Call OnCurrentTimeChange in different status.
     * @tc.expected: pastPlayingStatus_ is set.
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), Pause()).Times(1);
    videoPattern->isPlaying_ = false;
    videoPattern->pastPlayingStatus_ = false;
    videoPattern->HiddenChange(true);
    videoPattern->pastPlayingStatus_ = true;
    videoPattern->HiddenChange(true);
    videoPattern->pastPlayingStatus_ = false;
    videoPattern->HiddenChange(false);
    videoPattern->pastPlayingStatus_ = true;
    videoPattern->HiddenChange(false);
    EXPECT_FALSE(videoPattern->pastPlayingStatus_);

    videoPattern->isPlaying_ = true;
    videoPattern->HiddenChange(false);
    videoPattern->HiddenChange(true);
    EXPECT_TRUE(videoPattern->pastPlayingStatus_);
    videoPattern->mediaPlayer_ = nullptr;
    videoPattern->HiddenChange(false);
    videoPattern->HiddenChange(true);
    videoPattern->isPlaying_ = false;
    videoPattern->HiddenChange(false);
    videoPattern->HiddenChange(true);
}

/**
 * @tc.name: VideoPatternTest025
 * @tc.desc: Test VideoPattern PrepareSurface.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video and get videoPattern.
     */
    VideoModelNG video;
    video.Create(AceType::MakeRefPtr<VideoControllerV2>());
    auto videoNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(videoNode, nullptr);
    auto videoPattern = videoNode->GetPattern<VideoPattern>();
    ASSERT_NE(videoPattern, nullptr);

    /**
     * @tc.steps: step2. Call PrepareSurface in different status.
     * @tc.expected: SetSurface function is called.
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockRenderSurface>(videoPattern->renderSurface_)), IsSurfaceValid())
        .WillOnce(Return(true))
        .WillOnce(Return(false));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), SetSurface())
        .WillOnce(Return(-1));
    videoPattern->PrepareSurface();
    SystemProperties::SetExtSurfaceEnabled(false);
    videoPattern->PrepareSurface();
}

/**
 * @tc.name: VideoPatternTest026
 * @tc.desc: Test VideoPattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully
     */
    auto frameNode = CreateVideoNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto videoPattern = frameNode->GetPattern<VideoPattern>();
    ASSERT_TRUE(videoPattern);

    /**
     * @tc.steps: step2. Call hiddenChangeEvent while video not in full screen mode.
     * @tc.expected: pastPlayingStatus_ is set.
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), Pause()).Times(1);
    EXPECT_CALL(*(AceType::DynamicCast<MockRenderSurface>(videoPattern->renderSurface_)), IsSurfaceValid())
        .WillRepeatedly(Return(false));
    videoPattern->OnModifyDone();
    auto hiddenChangeEvent = videoPattern->hiddenChangeEvent_;
    ASSERT_NE(hiddenChangeEvent, nullptr);
    videoPattern->isPlaying_ = true;
    hiddenChangeEvent(true);
    EXPECT_TRUE(videoPattern->pastPlayingStatus_);

    /**
     * @tc.steps: step2. Call hiddenChangeEvent while video in full screen mode.
     * @tc.expected: pastPlayingStatus_ is set.
     */
    videoPattern->FullScreen();
    videoPattern->isPlaying_ = true;
    hiddenChangeEvent(true);
    EXPECT_TRUE(videoPattern->pastPlayingStatus_);
    videoPattern->OnModifyDone();
}

/**
 * @tc.name: VideoPatternTest027
 * @tc.desc: Test VideoPattern UpdateControllerBar.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video and get videoPattern.
     */
    VideoModelNG video;
    video.Create(AceType::MakeRefPtr<VideoControllerV2>());
    auto videoNode = AceType::DynamicCast<VideoNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(videoNode, nullptr);
    auto videoPattern = videoNode->GetPattern<VideoPattern>();
    ASSERT_NE(videoPattern, nullptr);
    auto layoutProperty = videoPattern->GetLayoutProperty<VideoLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Update Video controllerBar while controllerBar is show or not.
     * @tc.expected: Visibility value is changed.
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockRenderSurface>(videoPattern->renderSurface_)), IsSurfaceValid())
        .WillOnce(Return(false));
    layoutProperty->UpdateControls(false);
    auto controller = AceType::DynamicCast<FrameNode>(videoNode->GetControllerRow());
    ASSERT_NE(controller, nullptr);
    auto controllerLayoutProperty = controller->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(controllerLayoutProperty, nullptr);
    videoPattern->UpdateControllerBar();
    EXPECT_EQ(controllerLayoutProperty->GetVisibilityValue(), VisibleType::INVISIBLE);
    layoutProperty->UpdateControls(true);
    videoNode->children_.clear();
    videoPattern->UpdateControllerBar();
}

/**
 * @tc.name: VideoPatternTest028
 * @tc.desc: Test VideoPattern UpdateVideoProperty and OnRebuildFrame.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video and get videoPattern.
     */
    VideoModelNG video;
    video.Create(AceType::MakeRefPtr<VideoControllerV2>());
    auto videoNode = AceType::DynamicCast<VideoNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(videoNode, nullptr);
    auto videoPattern = videoNode->GetPattern<VideoPattern>();
    ASSERT_NE(videoPattern, nullptr);

    /**
     * @tc.steps: step2. Update Video property while isInitialState_ and autoPlay_ changes.
     * @tc.expected: PrepareAsync function is called only once.
     */
    videoPattern->isStop_ = true;
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), PrepareAsync())
        .Times(1)
        .WillOnce(Return(-1));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(true));
    videoPattern->isInitialState_ = false;
    videoPattern->autoPlay_ = false;
    videoPattern->UpdateVideoProperty();
    videoPattern->autoPlay_ = true;
    videoPattern->UpdateVideoProperty();
    videoPattern->isInitialState_ = true;
    videoPattern->autoPlay_ = false;
    videoPattern->UpdateVideoProperty();
    videoPattern->autoPlay_ = true;
    videoPattern->UpdateVideoProperty();

    /**
     * @tc.steps: step2. Call OnRebuildFrame while renderSurface_ in different status.
     * @tc.expected: IsSurfaceValid function is called only once.
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockRenderSurface>(videoPattern->renderSurface_)), IsSurfaceValid())
        .Times(1)
        .WillOnce(Return(true));
    videoPattern->OnRebuildFrame();
    videoPattern->renderSurface_ = nullptr;
    videoPattern->OnRebuildFrame();
}

/**
 * @tc.name: VideoPatternTest029
 * @tc.desc: Test VideoPattern OnColorConfigurationUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video and get videoPattern.
     */
    VideoModelNG video;
    video.Create(AceType::MakeRefPtr<VideoControllerV2>());
    auto videoNode = AceType::DynamicCast<VideoNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(videoNode, nullptr);
    auto videoPattern = videoNode->GetPattern<VideoPattern>();
    ASSERT_NE(videoPattern, nullptr);

    /**
     * @tc.steps: step2. Call OnColorConfigurationUpdate with different childNode in controlBar_.
     * @tc.expected: BackgroundColor of renderContext is set.
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockRenderSurface>(videoPattern->renderSurface_)), IsSurfaceValid())
        .Times(1)
        .WillOnce(Return(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));
    ASSERT_NE(videoPattern->controlBar_, nullptr);
    auto renderContext = videoPattern->controlBar_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto videoTheme = PipelineBase::GetCurrentContext()->GetTheme<VideoTheme>();
    ASSERT_NE(videoTheme, nullptr);
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    textNode->layoutProperty_ = nullptr;
    videoPattern->controlBar_->children_.emplace_back(textNode);
    videoPattern->OnColorConfigurationUpdate();
    EXPECT_FALSE(videoNode->needCallChildrenUpdate_);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), videoTheme->GetBkgColor());
}

/**
 * @tc.name: VideoPatternTest030
 * @tc.desc: VideoImageAnalyzerTest.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video and get videoPattern.
     */
    VideoModelNG video;
    video.Create(AceType::MakeRefPtr<VideoControllerV2>());
    auto videoNode = AceType::DynamicCast<VideoNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(videoNode, nullptr);
    auto videoPattern = videoNode->GetPattern<VideoPattern>();
    ASSERT_NE(videoPattern, nullptr);

    /**
     * @tc.steps: step2. Call EnableAnalyzer and set true.
     * @tc.expected: step2. videoPattern->isEnableAnalyzer_ will be true
     */
    videoPattern->EnableAnalyzer(true);
    EXPECT_TRUE(videoPattern->isEnableAnalyzer_);

    if (ImageAnalyzerMgr::GetInstance().IsImageAnalyzerSupported()) {
        EXPECT_TRUE(videoPattern->IsSupportImageAnalyzer());
    } else {
        EXPECT_FALSE(videoPattern->IsSupportImageAnalyzer());
    }

    /**
     * @tc.steps: step3. Call EnableAnalyzer and set false.
     * @tc.expected: step3. videoPattern->isEnableAnalyzer_ will be false
     */
    videoPattern->EnableAnalyzer(false);
    EXPECT_FALSE(videoPattern->isEnableAnalyzer_);

    videoPattern->imageAnalyzerManager_ = nullptr;
    EXPECT_FALSE(videoPattern->IsSupportImageAnalyzer());
}

/**
 * @tc.name: VideoPatternTest031
 * @tc.desc: VideoEnableShortcutKeyTest.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video and get videoPattern.
     */
    VideoModelNG video;
    video.Create(AceType::MakeRefPtr<VideoControllerV2>());
    auto videoNode = AceType::DynamicCast<VideoNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(videoNode, nullptr);
    auto videoPattern = videoNode->GetPattern<VideoPattern>();
    videoPattern->duration_ = VIDEO_DURATION;
    videoPattern->currentPos_ = VIDEO_CURRENT_TIME;
    ASSERT_NE(videoPattern, nullptr);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(true));

    /**
     * @tc.steps: step2. call onKeyEvent when isEnableShortcutKey_ is false/code is incorrect/action is incorrect
     * @tc.expected: will not response
     */
    KeyEvent keyEvent0 { KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN };
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), Seek(_, _)).Times(0);
    videoPattern->OnKeyEvent(keyEvent0);
    videoPattern->isEnableShortcutKey_ = true;
    keyEvent0.code = KeyCode::KEY_CTRL_LEFT;
    videoPattern->OnKeyEvent(keyEvent0);
    keyEvent0.action = KeyAction::UP;
    videoPattern->OnKeyEvent(keyEvent0);

    /**
     * @tc.steps: step3. call onKeyEvent when isEnableShortcutKey_ is true and code&action is right
     * @tc.expected: response as expected
     */
    videoPattern->isPrepared_ = true;
    KeyEvent keyEvent1 { KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN };
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)),
        Seek((VIDEO_CURRENT_TIME - 1) * MILLISECONDS_TO_SECONDS, _))
        .Times(1);
    videoPattern->OnKeyEvent(keyEvent1);
    KeyEvent keyEvent2 { KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN };
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)),
        Seek((VIDEO_CURRENT_TIME + 1) * MILLISECONDS_TO_SECONDS, _))
        .Times(1);
    videoPattern->OnKeyEvent(keyEvent2);
    KeyEvent keyEvent3 { KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN };
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)),
        SetVolume(1.0f - VOLUME_STEP, 1.0f - VOLUME_STEP))
        .Times(1);
    videoPattern->OnKeyEvent(keyEvent3);
    KeyEvent keyEvent4 { KeyCode::KEY_DPAD_UP, KeyAction::DOWN };
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), SetVolume(1.0f, 1.0f)).Times(1);
    videoPattern->OnKeyEvent(keyEvent4);
    KeyEvent keyEvent5 { KeyCode::KEY_SPACE, KeyAction::DOWN };
    videoPattern->isPaused_ = true;
    videoPattern->OnKeyEvent(keyEvent5);
    EXPECT_FALSE(videoPattern->isPaused_);
    videoPattern->isPlaying_ = true;
    KeyEvent keyEvent6 { KeyCode::KEY_SPACE, KeyAction::DOWN };
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), Pause()).Times(1);
    videoPattern->OnKeyEvent(keyEvent6);
}
} // namespace OHOS::Ace::NG
