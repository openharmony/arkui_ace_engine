/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/video/video_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/video/video_layout_algorithm.h"
#include "core/components_ng/pattern/video/video_layout_property.h"
#include "core/components_ng/pattern/video/video_model_ng.h"
#include "core/components_ng/pattern/video/video_pattern.h"
#include "core/components_ng/test/mock/render/mock_media_player.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_ng/test/mock/render/mock_render_surface.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/image/image_source_info.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
AnimatableDimension& AnimatableDimension::operator=(const AnimatableDimension& newDimension)
{
    return *this;
}
} // namespace OHOS::Ace
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
const std::string VIDEO_SRC = "common/video.mp4";
constexpr double VIDEO_PROGRESS_RATE = 1.0;
const std::string VIDEO_POSTER_URL = "common/img2.png";
constexpr bool MUTED_VALUE = false;
constexpr bool AUTO_PLAY = false;
constexpr bool CONTROL_VALUE = true;
constexpr bool LOOP_VALUE = false;
const ImageFit VIDEO_IMAGE_FIT = ImageFit::COVER;
const std::string VIDEO_START_EVENT = "start";
const std::string VIDEO_PAUSE_EVENT = "pause";
const std::string VIDEO_FINISH_EVENT = "finish";
const std::string VIDEO_ERROR_EVENT = "error";
const std::string VIDEO_PREPARED_EVENT = "prepared";
const std::string VIDEO_SEEKING_EVENT = "seeking";
const std::string VIDEO_SEEKED_EVENT = "seeked";
const std::string VIDEO_UPDATE_EVENT = "update";
const std::string VIDEO_FULLSCREEN_EVENT = "fullScreen";
constexpr float MAX_WIDTH = 400.0f;
constexpr float MAX_HEIGHT = 400.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
constexpr float VIDEO_WIDTH = 300.0f;
constexpr float VIDEO_HEIGHT = 300.0f;
const SizeF VIDEO_SIZE(VIDEO_WIDTH, VIDEO_HEIGHT);
const SizeF LAYOUT_SIZE_RATIO_GREATER_THAN_1(MAX_WIDTH, VIDEO_HEIGHT);
const SizeF LAYOUT_SIZE_RATIO_LESS_THAN_1(VIDEO_WIDTH, MAX_HEIGHT);
const SizeF INVALID_SIZE(MAX_WIDTH, 0.0f);
constexpr uint32_t VIDEO_CHILDREN_NUM = 2;
constexpr uint32_t DURATION = 100;
TestProperty testProperty;
} // namespace

class VideoPropertyTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateVideoNode(TestProperty& testProperty);
};

void VideoPropertyTestNg::SetUpTestSuite()
{
    testProperty.progressRate = VIDEO_PROGRESS_RATE;
    testProperty.muted = MUTED_VALUE;
    testProperty.autoPlay = AUTO_PLAY;
    testProperty.controls = CONTROL_VALUE;
    testProperty.loop = LOOP_VALUE;
    testProperty.objectFit = VIDEO_IMAGE_FIT;
    MockPipelineBase::SetUp();
}

void VideoPropertyTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
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
        .WillRepeatedly(Return(false));

    if (testProperty.src.has_value()) {
        VideoModelNG().SetSrc(testProperty.src.value());
    }
    if (testProperty.progressRate.has_value()) {
        VideoModelNG().SetProgressRate(testProperty.progressRate.value());
    }
    if (testProperty.posterUrl.has_value()) {
        VideoModelNG().SetPosterSourceInfo(testProperty.posterUrl.value());
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

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // pop
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: VideoPropertyTest001
 * @tc.desc: Create Video.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPropertyTest001, TestSize.Level1)
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

    video.SetSrc(VIDEO_SRC);
    video.SetProgressRate(VIDEO_PROGRESS_RATE);
    video.SetPosterSourceInfo(VIDEO_POSTER_URL);
    video.SetMuted(MUTED_VALUE);
    video.SetAutoPlay(AUTO_PLAY);
    video.SetControls(CONTROL_VALUE);
    video.SetLoop(LOOP_VALUE);
    video.SetObjectFit(VIDEO_IMAGE_FIT);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::VIDEO_ETS_TAG);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    EXPECT_FALSE(videoLayoutProperty == nullptr);
    auto videoPattern = frameNode->GetPattern<VideoPattern>();
    EXPECT_FALSE(videoPattern == nullptr);

    EXPECT_EQ(videoLayoutProperty->GetVideoSource().value_or(""), VIDEO_SRC);
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
    video.SetOnFullScreenChange(videoEvent);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::VIDEO_ETS_TAG);
    auto videoEventHub = frameNode->GetEventHub<VideoEventHub>();
    EXPECT_TRUE(videoEventHub != nullptr);

    videoEventHub->FireStartEvent(VIDEO_START_EVENT);
    EXPECT_EQ(unknownVideoEvent, VIDEO_START_EVENT);
    videoEventHub->FirePauseEvent(VIDEO_PAUSE_EVENT);
    EXPECT_EQ(unknownVideoEvent, VIDEO_PAUSE_EVENT);
    videoEventHub->FireFinishEvent(VIDEO_FINISH_EVENT);
    EXPECT_EQ(unknownVideoEvent, VIDEO_FINISH_EVENT);
    videoEventHub->FireErrorEvent(VIDEO_ERROR_EVENT);
    EXPECT_EQ(unknownVideoEvent, VIDEO_ERROR_EVENT);
    videoEventHub->FirePreparedEvent(VIDEO_PREPARED_EVENT);
    EXPECT_EQ(unknownVideoEvent, VIDEO_PREPARED_EVENT);
    videoEventHub->FireSeekingEvent(VIDEO_SEEKING_EVENT);
    EXPECT_EQ(unknownVideoEvent, VIDEO_SEEKING_EVENT);
    videoEventHub->FireSeekedEvent(VIDEO_SEEKED_EVENT);
    EXPECT_EQ(unknownVideoEvent, VIDEO_SEEKED_EVENT);
    videoEventHub->FireUpdateEvent(VIDEO_UPDATE_EVENT);
    EXPECT_EQ(unknownVideoEvent, VIDEO_UPDATE_EVENT);
    videoEventHub->FireFullScreenChangeEvent(VIDEO_FULLSCREEN_EVENT);
    EXPECT_EQ(unknownVideoEvent, VIDEO_FULLSCREEN_EVENT);
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
    CHECK_NULL_VOID(frameNodeTemp);
    auto videoPatternTemp = AceType::DynamicCast<VideoPattern>(frameNodeTemp->GetPattern());
    CHECK_NULL_VOID(videoPatternTemp);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPatternTemp->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::VIDEO_ETS_TAG);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    EXPECT_FALSE(videoLayoutProperty == nullptr);

    // Create LayoutWrapper and set videoLayoutAlgorithm.
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto videoPattern = frameNode->GetPattern<VideoPattern>();
    EXPECT_FALSE(videoPattern == nullptr);
    auto videoLayoutAlgorithm = videoPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(videoLayoutAlgorithm == nullptr);
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
    video.SetPosterSourceInfo(VIDEO_POSTER_URL);
    video.SetControls(CONTROL_VALUE);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::VIDEO_ETS_TAG);
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    EXPECT_FALSE(videoLayoutProperty == nullptr);

    // Create LayoutWrapper and set videoLayoutAlgorithm.
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto videoPattern = frameNode->GetPattern<VideoPattern>();
    EXPECT_FALSE(videoPattern == nullptr);
    auto videoLayoutAlgorithm = videoPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(videoLayoutAlgorithm == nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(videoLayoutAlgorithm));

    // Set video source size and layout size.
    LayoutConstraintF layoutConstraint;
    videoLayoutProperty->UpdateVideoSize(VIDEO_SIZE);
    layoutConstraint.selfIdealSize.SetSize(VIDEO_SIZE);
    auto videoSize1 =
        videoLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value_or(SizeF(0.0f, 0.0f));
    EXPECT_EQ(videoSize1, SizeF(VIDEO_WIDTH, VIDEO_WIDTH));
    layoutWrapper.GetGeometryNode()->SetContentSize(videoSize1);

    auto frameNodeRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->AddChild(frameNodeRow);
    const auto& children = frameNode->GetChildren();
    for (const auto& child : children) {
        auto frameNodeChild = AceType::DynamicCast<FrameNode>(child);
        RefPtr<GeometryNode> geometryNodeChild = AceType::MakeRefPtr<GeometryNode>();
        auto childLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(AceType::WeakClaim(AceType::RawPtr(frameNodeChild)), geometryNodeChild,
                frameNodeChild->GetLayoutProperty());
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
}

/**
 * @tc.name: VideoPatternTest006
 * @tc.desc: Test AddPreviewNode
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest006, TestSize.Level1)
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
    auto nodeRedundant = AceType::MakeRefPtr<FrameNode>("redundant", -1, AceType::MakeRefPtr<Pattern>());
    frameNode->AddChild(nodeRedundant, 0);

    /**
     * @tc.steps: step3. call AddPreviewNodeIfNeeded
     *            case1: isInitialState_ = true, has not PosterImageInfo
     *            case2: isInitialState_ = false, has not PosterImageInfo
     *            case3: isInitialState_ = false, has PosterImageInfo
     *            case4: isInitialState_ = true, has PosterImageInfo(), previewNode not exist
     *            case5: isInitialState_ = true, has PosterImageInfo(), previewNode exists
     * @tc.expected: step3. previewNode create successfully
     */
    pattern->AddPreviewNodeIfNeeded(); // case1
    auto children = frameNode->GetChildren();
    auto childrenSize = static_cast<int32_t>(children.size());
    EXPECT_EQ(childrenSize, 1);

    pattern->isInitialState_ = false;
    pattern->AddPreviewNodeIfNeeded(); // case2
    children = frameNode->GetChildren();
    childrenSize = static_cast<int32_t>(children.size());
    EXPECT_EQ(childrenSize, 1);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdatePosterImageInfo(ImageSourceInfo(VIDEO_POSTER_URL));
    pattern->AddPreviewNodeIfNeeded(); // case3
    children = frameNode->GetChildren();
    childrenSize = static_cast<int32_t>(children.size());
    EXPECT_EQ(childrenSize, 1);

    pattern->isInitialState_ = true;
    pattern->AddPreviewNodeIfNeeded(); // case4
    children = frameNode->GetChildren();
    childrenSize = static_cast<int32_t>(children.size());
    EXPECT_EQ(childrenSize, 2);

    pattern->AddPreviewNodeIfNeeded(); // case5
    children = frameNode->GetChildren();
    childrenSize = static_cast<int32_t>(children.size());
    EXPECT_EQ(childrenSize, 2);
}

/**
 * @tc.name: VideoPatternTest007
 * @tc.desc: Test AddControlBarNode
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest007, TestSize.Level1)
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
    auto nodeRedundant = AceType::MakeRefPtr<FrameNode>("redundant", -1, AceType::MakeRefPtr<Pattern>());
    frameNode->AddChild(nodeRedundant, 0);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    EXPECT_CALL(*(AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_)), IsSurfaceValid())
        .WillOnce(Return(false));

    /**
     * @tc.steps: step3. call AddControlBarNodeIfNeeded
     *            case1: ControlsValue = true, controlBar not exist
     *            case2: ControlsValue = true, controlBar exists
     *            case3: ControlsValue = false, controlBar exists
     * @tc.expected: step3. controlBarNode create and destroy successfully
     */
    pattern->AddControlBarNodeIfNeeded(); // case1
    auto children = frameNode->GetChildren();
    auto childrenSize = static_cast<int32_t>(children.size());
    EXPECT_EQ(childrenSize, 2);

    pattern->AddControlBarNodeIfNeeded(); // case2
    children = frameNode->GetChildren();
    childrenSize = static_cast<int32_t>(children.size());
    EXPECT_EQ(childrenSize, 2);

    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateControls(false);
    pattern->AddControlBarNodeIfNeeded(); // case3
    children = frameNode->GetChildren();
    childrenSize = static_cast<int32_t>(children.size());
    EXPECT_EQ(childrenSize, 1);
}

/**
 * @tc.name: VideoPatternTest008
 * @tc.desc: Test UpdateMediaPlayer
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest008, TestSize.Level1)
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
     * @tc.steps: step2. Call UpdateMediaPlayer
     *            case: IsMediaPlayerValid is always false
     * @tc.expected: step2. IsMediaPlayerValid will be called two times
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(2)
        .WillRepeatedly(Return(false));
    pattern->UpdateMediaPlayer();

    /**
     * @tc.steps: step3. Call UpdateMediaPlayer
     *            case: IsMediaPlayerValid is always true & has not set VideoSource
     * @tc.expected: step3. IsMediaPlayerValid will be called once
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(1)
        .WillOnce(Return(true));
    pattern->UpdateMediaPlayer();

    /**
     * @tc.steps: step4. Call UpdateMediaPlayer
     *            case: IsMediaPlayerValid is always true & has set VideoSource
     * @tc.expected: step4. IsMediaPlayerValid will be called two times and SetSource will be called once
     */
    auto videoLayoutProperty = pattern->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateVideoSource(VIDEO_SRC);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(2)
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), SetSource(_))
        .Times(1)
        .WillOnce(Return(false));
    pattern->UpdateMediaPlayer();

    /**
     * @tc.steps: step5. Call UpdateMediaPlayer
     *            case: IsMediaPlayerValid is always true & has set VideoSource & has set src_
     * @tc.expected: step5. IsMediaPlayerValid will be called once
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(1)
        .WillOnce(Return(true));
    pattern->UpdateMediaPlayer();

    /**
     * @tc.steps: step6. Call UpdateMediaPlayer
     *            case: first prepare and UpdateMediaPlayer successfully
     * @tc.expected: step6. IsMediaPlayerValid will be called three times
     *                      other function will be called once and return right value when preparing MediaPlayer
     *                      firstly
     */
    pattern->src_.clear();
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(3)
        .WillOnce(Return(false))
        .WillOnce(Return(true))
        .WillOnce(Return(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), SetSource(_))
        .Times(1)
        .WillOnce(Return(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_)), IsSurfaceValid())
        .Times(1)
        .WillOnce(Return(false));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), SetSurface())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), PrepareAsync())
        .Times(1)
        .WillOnce(Return(0));
    pattern->UpdateMediaPlayer();

    /**
     * @tc.steps: step7. Call UpdateMediaPlayer several times
     *            cases: first prepare and UpdateMediaPlayer fail
     * @tc.expected: step7. IsMediaPlayerValid will be called three times per case
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(9)
        .WillOnce(Return(false))
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillOnce(Return(false))
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillOnce(Return(false))
        .WillOnce(Return(true))
        .WillOnce(Return(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), SetSource(_))
        .Times(3)
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_)), IsSurfaceValid())
        .Times(3)
        .WillOnce(Return(false))
        .WillOnce(Return(false))
        .WillOnce(Return(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), SetSurface())
        .Times(2)
        .WillOnce(Return(0))
        .WillOnce(Return(-1));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), PrepareAsync())
        .Times(3)
        .WillRepeatedly(Return(-1));
    pattern->src_.clear();
    pattern->UpdateMediaPlayer();
    pattern->src_.clear();
    pattern->UpdateMediaPlayer();
    pattern->src_.clear();
    pattern->UpdateMediaPlayer();

    // CreateMediaPlayer success but PrepareMediaPlayer fail for mediaPlayer is invalid
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(3)
        .WillOnce(Return(false))
        .WillOnce(Return(true))
        .WillOnce(Return(false));
    pattern->src_.clear();
    pattern->UpdateMediaPlayer();
}

/**
 * @tc.name: VideoPatternTest009
 * @tc.desc: Test functions in UpdateMediaPlayer
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest009, TestSize.Level1)
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
     * @tc.steps: step2. Call SetSpeed
     *            cases: MediaPlayer is valid and MediaPlayer is invalid
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(2)
        .WillOnce(Return(false))
        .WillOnce(Return(true));
    pattern->SetSpeed();
    pattern->SetSpeed();

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
HWTEST_F(VideoPropertyTestNg, VideoPatternTest010, TestSize.Level1)
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
     * @tc.steps: step2. Prepare the childNode & videoEvent
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    frameNode->RemoveChildAtIndex(0); // remove the controlBar created in onModifyDone
    auto controlBar = pattern->CreateControlBar();
    ASSERT_TRUE(controlBar);
    auto tempFrameNode = AceType::MakeRefPtr<FrameNode>("TEMP", -1, AceType::MakeRefPtr<Pattern>());
    frameNode->AddChild(controlBar);       // Add ControlBar
    frameNode->AddChild(tempFrameNode, 0); // Add a redundant node to go other branch

    auto playBtn = AceType::DynamicCast<FrameNode>(controlBar->GetChildAtIndex(0));
    ASSERT_TRUE(playBtn);
    auto playBtnGestureEventHub = playBtn->GetOrCreateGestureEventHub();
    ASSERT_TRUE(playBtnGestureEventHub);

    // set videoEvent
    auto videoEventHub = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub);
    std::string startCheck;
    EventCallback onStart = [&startCheck](const std::string& /* param */) { startCheck = VIDEO_START_EVENT; };
    std::string pauseCheck;
    EventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    std::string finishCheck;
    EventCallback onFinish = [&finishCheck](const std::string& /* param */) { finishCheck = VIDEO_FINISH_EVENT; };
    videoEventHub->SetOnStart(std::move(onStart));
    videoEventHub->SetOnPause(std::move(onPause));
    videoEventHub->SetOnFinish(std::move(onFinish));

    /**
     * @tc.steps: step3. Call OnPlayerStatus status == STARTED
     * @tc.expected: step3. FireStartEvent has called and playBtn event will call pattern->Pause()
     */
    pattern->OnPlayerStatus(PlaybackStatus::STARTED);
    EXPECT_EQ(startCheck, VIDEO_START_EVENT);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(3)
        .WillOnce(Return(false))
        .WillOnce(Return(true))
        .WillOnce(Return(true));
    // will call pattern->Pause()
    EXPECT_TRUE(pattern->isPlaying_);
    // case1: MediaPlayer is invalid
    auto flag = playBtnGestureEventHub->ActClick();
    EXPECT_TRUE(flag);

    // case2: MediaPlayer is valid & isPlaying = true
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), Pause()).Times(1).WillOnce(Return(0));
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
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(2)
        .WillOnce(Return(false))
        .WillOnce(Return(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), GetVideoWidth()).Times(1);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), GetVideoHeight()).Times(1);
    // case1: MediaPlayer is invalid
    pattern->OnPlayerStatus(PlaybackStatus::PREPARED);
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);

    // case1: MediaPlayer is valid
    pauseCheck.clear();
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), GetDuration(_))
        .Times(1)
        .WillOnce(Return(1));
    pattern->OnPlayerStatus(PlaybackStatus::PREPARED);
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
}

/**
 * @tc.name: VideoPatternTest011
 * @tc.desc: Test OnPrepared
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest011, TestSize.Level1)
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

    auto tempFrameNode = AceType::MakeRefPtr<FrameNode>("TEMP", -1, AceType::MakeRefPtr<Pattern>());
    frameNode->AddChild(tempFrameNode, 0); // Add a redundant node to go other branch

    // set videoEvent
    auto videoEventHub = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub);
    std::string preparedCheck;
    EventCallback onPrepared = [&preparedCheck](
                                   const std::string& /* param */) { preparedCheck = VIDEO_PREPARED_EVENT; };
    videoEventHub->SetOnPrepared(std::move(onPrepared));
    auto videoLayoutProperty = pattern->GetLayoutProperty<VideoLayoutProperty>();

    /**
     * @tc.steps: step2. Call OnPrepared
     *            case1: needControlBar & needFireEvent = true, isStop_ & autoPlay_ = false
     * @tc.expected: step2. FirePreparedEvent will be called & duration_ has changed
     */
    EXPECT_TRUE(videoLayoutProperty->GetControlsValue(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid()).Times(2);
    pattern->OnPrepared(VIDEO_WIDTH, VIDEO_HEIGHT, DURATION, 0, true);
    EXPECT_EQ(pattern->duration_, DURATION);
    EXPECT_EQ(preparedCheck, VIDEO_PREPARED_EVENT);

    /**
     * @tc.steps: step3. Call OnPrepared
     *            case2: needControlBar & needFireEvent = false, isStop_ & autoPlay_ = true
     * @tc.expected: step3. FirePreparedEvent will not be called & duration_ has changed
     */
    videoLayoutProperty->UpdateControls(false);
    preparedCheck.clear();
    pattern->duration_ = 0;
    pattern->isStop_ = true;
    pattern->autoPlay_ = true;
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid()).Times(4);
    pattern->OnPrepared(VIDEO_WIDTH, VIDEO_HEIGHT, DURATION, 0, false);
    EXPECT_EQ(pattern->duration_, DURATION);
    EXPECT_TRUE(preparedCheck.empty());
}

/**
 * @tc.name: VideoPatternTest012
 * @tc.desc: Test Start & Stop
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest012, TestSize.Level1)
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

    auto tempFrameNode = AceType::MakeRefPtr<FrameNode>("TEMP", -1, AceType::MakeRefPtr<Pattern>());
    frameNode->AddChild(tempFrameNode, 0); // Add a redundant node to go other branch
    auto imageFrameNode = AceType::MakeRefPtr<FrameNode>(V2::IMAGE_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->AddChild(imageFrameNode); // Add a image node to go other branch
    auto rawChildNum = static_cast<int32_t>(frameNode->GetChildren().size());

    // set video event
    auto videoEventHub = pattern->GetEventHub<VideoEventHub>();
    std::string pauseCheck;
    EventCallback onPause = [&pauseCheck](const std::string& /* param */) { pauseCheck = VIDEO_PAUSE_EVENT; };
    videoEventHub->SetOnPause(std::move(onPause));
    std::string updateCheck;
    EventCallback onUpdate = [&updateCheck](const std::string& /* param */) { updateCheck = VIDEO_UPDATE_EVENT; };
    videoEventHub->SetOnUpdate(std::move(onUpdate));

    /**
     * @tc.steps: step2. Call Start
     * @tc.expected: step2. relevant functions called correctly
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(4)
        .WillRepeatedly(Return(true));
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
            } else {
                EXPECT_CALL(*(AceType::DynamicCast<MockRenderSurface>(pattern->renderSurface_)), IsSurfaceValid())
                    .Times(1)
                    .WillOnce(Return(prepareReturn == 0));
                if (prepareReturn == 0) {
                    frameNode->AddChild(imageFrameNode);
                }
                pattern->isPlaying_ = false;
                pattern->Start(); // will remove the imageFrameNode
                auto childNum = static_cast<int32_t>(frameNode->GetChildren().size());
                EXPECT_EQ(childNum, rawChildNum - 1);
            }
        }
    }

    /**
     * @tc.steps: step3. Call Stop
     * @tc.expected: step3. relevant functions called correctly
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillOnce(Return(false));
    pattern->Stop(); // case1: media player is invalid

    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillOnce(Return(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), Stop()).WillOnce(Return(0));
    EXPECT_EQ(static_cast<int32_t>(pattern->currentPos_), 0);
    pattern->Stop(); // case2: media player is valid & currentPos = currentPos_ = 0
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);
    EXPECT_TRUE(updateCheck.empty());

    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(2)
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), Stop())
        .Times(2)
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), GetDuration(_))
        .Times(2)
        .WillOnce(Return(0))
        .WillOnce(Return(-1));
    updateCheck.clear();
    pattern->currentPos_ = 1;
    pattern->Stop(); // case3: media player is valid & currentPos != currentPos_ & duration_ = 0 &
                     // mediaPlayer_->GetDuration return ok
                     // this will call OnUpdateTime(pos=DURATION_POS)
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);
    EXPECT_EQ(static_cast<int32_t>(pattern->currentPos_), 0);
    EXPECT_EQ(updateCheck, VIDEO_UPDATE_EVENT);

    updateCheck.clear();
    pattern->currentPos_ = 1;
    pattern->Stop(); // case4: media player is valid & currentPos != currentPos_ & duration_ = 0 &
                     // mediaPlayer_->GetDuration return err
    EXPECT_EQ(pauseCheck, VIDEO_PAUSE_EVENT);
    EXPECT_EQ(static_cast<int32_t>(pattern->currentPos_), 0);
    EXPECT_EQ(updateCheck, VIDEO_UPDATE_EVENT);
}

/**
 * @tc.name: VideoPatternTest013
 * @tc.desc: Test function related to full screen and slider
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest013, TestSize.Level1)
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
    auto videoEventHub = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(videoEventHub);
    std::string seekingCheck;
    EventCallback onSeeking = [&seekingCheck](const std::string& /* param */) { seekingCheck = VIDEO_SEEKING_EVENT; };
    videoEventHub->SetOnSeeking(std::move(onSeeking));
    std::string seekedCheck;
    EventCallback onSeeked = [&seekedCheck](const std::string& /* param */) { seekedCheck = VIDEO_SEEKED_EVENT; };
    videoEventHub->SetOnSeeked(std::move(onSeeked));
    std::string fullScreenCheck;
    EventCallback onFullScreenChange = [&fullScreenCheck](const std::string& param) { fullScreenCheck = param; };
    videoEventHub->SetOnFullScreenChange(std::move(onFullScreenChange));

    /**
     * @tc.steps: step2. call OnSliderChange
     * @tc.expected: step2. onSeeking/onSeeked & SetCurrentTime  will be called
     */
    std::vector<int32_t> sliderChangeModes { 0, 1, 2 };
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(4)
        .WillOnce(Return(false))
        .WillRepeatedly(Return(true));
    for (int i = 0; i < 3; i++) {
        auto sliderChangeMode = sliderChangeModes[i];
        if (i == 1) {
            EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), Seek(_, _))
                .Times(1)
                .WillOnce(Return(0)); // 0 <= currentPos(0) <= duration_(0) will call mediaPlayer's Seek()
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

    /**
     * @tc.steps: step3. call FullScreen & ExitFullScreen
     * @tc.expected: step3. onFullScreenChange(true / false)  will be called
     */
    auto json = JsonUtil::Create(true);
    json->Put("fullscreen", true);
    auto fullScreenTrue = json->ToString();
    pattern->FullScreen(); // will called onFullScreenChange(true)
    EXPECT_TRUE(pattern->isFullScreen_);
    EXPECT_EQ(fullScreenCheck, fullScreenTrue);

    fullScreenCheck.clear();
    pattern->FullScreen(); // call again, nothing will happen
    EXPECT_TRUE(pattern->isFullScreen_);
    EXPECT_TRUE(fullScreenCheck.empty());

    // get the full screen svg node & get its gestureEventHub
    const auto& children = frameNode->GetChildren();
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
    EXPECT_FALSE(pattern->isFullScreen_);
    EXPECT_EQ(fullScreenCheck, fullScreenFalse);

    fullScreenCheck.clear();
    pattern->ExitFullScreen(); // call again, nothing will happen
    EXPECT_FALSE(pattern->isFullScreen_);
    EXPECT_TRUE(fullScreenCheck.empty());

    fsEvent->ActClick(); // this will call FullScreen()
    EXPECT_TRUE(pattern->isFullScreen_);

    /**
     * @tc.steps: step4. call OnBackPressed
     * @tc.expected: step4. ExitFullScreen() will be called
     */
    // construct a FullScreenManager
    auto root = AceType::MakeRefPtr<FrameNode>("ROOT", -1, AceType::MakeRefPtr<Pattern>(), true);
    auto fullScreenManager = AceType::MakeRefPtr<FullScreenManager>(root);
    root->AddChild(frameNode);

    auto flag = fullScreenManager->OnBackPressed(); // will on videoPattern->OnBackPressed()
    EXPECT_TRUE(flag);
    EXPECT_FALSE(pattern->isFullScreen_);
    EXPECT_EQ(fullScreenCheck, fullScreenFalse);

    root->AddChild(tempFrameNode);
    flag = fullScreenManager->OnBackPressed(); // call again, nothing happen
    EXPECT_FALSE(flag);

    pattern->OnBackPressed(); // nothing will happen
    EXPECT_FALSE(pattern->isFullScreen_);

    /**
     * @tc.steps: step5. call FullScreen & ExitFullScreen in videoController
     *                   note: just test ExitFullscreen(issync = true), other functions are async
     * @tc.expected: step5. onFullScreenChange(true / false)  will be called
     */
    pattern->FullScreen();
    EXPECT_TRUE(pattern->isFullScreen_);
    EXPECT_EQ(fullScreenCheck, fullScreenTrue);
    videoController->ExitFullscreen(false); // nothing will happen for it's async
    EXPECT_TRUE(pattern->isFullScreen_);
    videoController->ExitFullscreen(true);
    EXPECT_FALSE(pattern->isFullScreen_);
    EXPECT_EQ(fullScreenCheck, fullScreenFalse);
}

/**
 * @tc.name: VideoPatternTest014
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest014, TestSize.Level1)
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

    // prepare the param for OnDirtyLayoutWrapperSwap
    DirtySwapConfig config;
    auto videoLayoutAlgorithm = AceType::MakeRefPtr<VideoLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetContentSize(MAX_SIZE);
    auto layoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    EXPECT_TRUE(layoutProperty);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(videoLayoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap several times
     *            case: skipMeasure is true
     */
    bool skipMeasures[2] { true, false };
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (i == 1 && j == 1) {
                break;
            }
            layoutWrapper->skipMeasureContent_ = skipMeasures[i];
            config.skipMeasure = skipMeasures[j];
            pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
        }
    }

    /**
     * @tc.steps: step3. call OnDirtyLayoutWrapperSwap several times
     *            case: skipMeasure is false
     */
    layoutWrapper->skipMeasureContent_ = false;
    config.skipMeasure = false;
    EXPECT_CALL(*(AceType::DynamicCast<MockRenderContext>(pattern->renderContextForMediaPlayer_)),
        SetBounds(0.0f, 0.0f, MAX_WIDTH, MAX_HEIGHT))
        .Times(1);
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config); // case: layoutProperty has not VideoSize()

    vector<ImageFit> objectFits { ImageFit::FILL, ImageFit::CONTAIN, ImageFit::COVER, ImageFit::FITWIDTH,
        ImageFit::SCALE_DOWN };
    layoutProperty->UpdateVideoSize(VIDEO_SIZE);
    vector<SizeF> idealSizes { MAX_SIZE, MAX_SIZE, MAX_SIZE, MAX_SIZE, VIDEO_SIZE, MAX_SIZE };

    // case: layoutSize = {400, 400}, videoSize = {300, 300}
    for (ImageFit& objectFit : objectFits) {
        layoutProperty->UpdateObjectFit(objectFit);
        if (objectFit != ImageFit::SCALE_DOWN) {
            EXPECT_CALL(*(AceType::DynamicCast<MockRenderContext>(pattern->renderContextForMediaPlayer_)),
                SetBounds(0.0f, 0.0f, MAX_WIDTH, MAX_HEIGHT))
                .Times(1);
        } else {
            EXPECT_CALL(*(AceType::DynamicCast<MockRenderContext>(pattern->renderContextForMediaPlayer_)),
                SetBounds(50.0f, 50.0f, VIDEO_WIDTH, VIDEO_HEIGHT))
                .Times(1);
        }
        pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    }

    // case: layoutSize or VideoSize is inValid (near 0)
    vector<SizeF> videoSizes { VIDEO_SIZE, INVALID_SIZE, INVALID_SIZE };
    vector<SizeF> layoutSizes { INVALID_SIZE, MAX_SIZE, INVALID_SIZE };
    for (int i = 0; i < 3; i++) {
        layoutProperty->UpdateVideoSize(videoSizes[i]);
        geometryNode->SetContentSize(layoutSizes[i]);
        EXPECT_CALL(*(AceType::DynamicCast<MockRenderContext>(pattern->renderContextForMediaPlayer_)),
            SetBounds(0.0f, 0.0f, layoutSizes[i].width_, layoutSizes[i].height_))
            .Times(2);
        layoutProperty->UpdateObjectFit(ImageFit::CONTAIN);
        pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
        layoutProperty->UpdateObjectFit(ImageFit::COVER);
        pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    }

    // case: objectFit = COVER, sourceRatio < layoutRatio, widthRatio <= 1
    layoutProperty->UpdateObjectFit(ImageFit::SCALE_DOWN);
    layoutProperty->UpdateVideoSize(VIDEO_SIZE);
    geometryNode->SetContentSize(SizeF(300.0f, 200.0f));
    EXPECT_CALL(*(AceType::DynamicCast<MockRenderContext>(pattern->renderContextForMediaPlayer_)),
        SetBounds(50.0f, 0.0f, 200.0f, 200.0f))
        .Times(1);
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);

    // case: objectFit = SCALE_DOWN, layout.width < video.width, sourceRatio < layoutRatio
    layoutProperty->UpdateObjectFit(ImageFit::SCALE_DOWN);
    layoutProperty->UpdateVideoSize(VIDEO_SIZE);
    geometryNode->SetContentSize(SizeF(200.0f, 100.0f));
    EXPECT_CALL(*(AceType::DynamicCast<MockRenderContext>(pattern->renderContextForMediaPlayer_)),
        SetBounds(50.0f, 0.0f, 100.0f, 100.0f))
        .Times(1);
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);

    // case: objectFit = NONE, heightRatio <= 1
    layoutProperty->UpdateObjectFit(ImageFit::SCALE_DOWN);
    geometryNode->SetContentSize(MAX_SIZE); // layoutSize = (400, 400)
    layoutProperty->UpdateVideoSize(SizeF(500.0f, 400.0f));
    EXPECT_CALL(*(AceType::DynamicCast<MockRenderContext>(pattern->renderContextForMediaPlayer_)),
        SetBounds(0.0f, 40.0f, 400.0f, 320.0f))
        .Times(1);
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);

    // case: objectFit = NONE, widthRatio & heightRatio >= 1
    layoutProperty->UpdateObjectFit(ImageFit::SCALE_DOWN);
    geometryNode->SetContentSize(MAX_SIZE); // layoutSize = (400, 400)
    layoutProperty->UpdateVideoSize(SizeF(500.0f, 800.0f));
    EXPECT_CALL(*(AceType::DynamicCast<MockRenderContext>(pattern->renderContextForMediaPlayer_)),
        SetBounds(75.0f, 0.0f, 250.0f, 400.0f))
        .Times(1);
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
}

/**
 * @tc.name: VideoPatternTest015
 * @tc.desc: Test OnResolutionChange & OnHiddenChange
 * @tc.type: FUNC
 */
HWTEST_F(VideoPropertyTestNg, VideoPatternTest015, TestSize.Level1)
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
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .Times(2)
        .WillOnce(Return(false))
        .WillOnce(Return(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), GetVideoWidth()).Times(1);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), GetVideoHeight()).Times(1);
    pattern->OnResolutionChange();
    pattern->OnResolutionChange();

    /**
     * @tc.steps: step3. Call OnVisibleChange several times
     * @tc.expected: step3. related functions will be called
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));
    pattern->OnModifyDone();

    pattern->hiddenChangeEvent_ = nullptr;
    pattern->OnVisibleChange(false); // case: hiddenChangeEvent_ is null

    pattern->OnModifyDone(); // after that, hiddenChangeEvent is not null

    pattern->isPlaying_ = false;
    pattern->OnVisibleChange(false); // case: isPlaying_=false, hidden=true, mediaPlayer is not null
    EXPECT_FALSE(pattern->pastPlayingStatus_);

    pattern->isPlaying_ = true;
    pattern->OnVisibleChange(false); // case: isPlaying_=true, hidden=true, mediaPlayer is not null
    EXPECT_TRUE(pattern->pastPlayingStatus_);

    pattern->isPlaying_ = false;
    pattern->OnVisibleChange(false); // // case: isPlaying_=false, hidden = true, pastPlayingStatus_ = true

    pattern->isPlaying_ = true;
    pattern->OnVisibleChange(true); // case: isPlaying_=true, hidden = false, pastPlayingStatus_ = true
    EXPECT_FALSE(pattern->pastPlayingStatus_);

    pattern->OnVisibleChange(true); // case: isPlaying_=true, hidden = false, pastPlayingStatus_ = false
    EXPECT_FALSE(pattern->pastPlayingStatus_);

    pattern->mediaPlayer_ = nullptr;
    pattern->isPlaying_ = true;
    pattern->OnVisibleChange(false); // case: isPlaying_=true, hidden=true, mediaPlayer is null
    pattern->OnVisibleChange(true);  // case: isPlaying_=true, hidden=false, mediaPlayer is null
    EXPECT_FALSE(pattern->pastPlayingStatus_);
}
} // namespace OHOS::Ace::NG
