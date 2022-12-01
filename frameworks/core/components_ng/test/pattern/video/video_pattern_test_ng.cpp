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
#include "core/components_ng/pattern/video/video_layout_property.h"
#include "core/components_ng/pattern/video/video_model_ng.h"
#include "core/components_ng/pattern/video/video_pattern.h"
#include "core/components_ng/test/mock/render/mock_media_player.h"
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
constexpr uint32_t VIDEO_CHILDREN_NUM = 2;
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
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    VideoModelNG().Create(videoController);
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
    frameNode->AddChild(nodeRedundant);

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
    frameNode->AddChild(nodeRedundant);
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
     *            case: IsMediaPlayerValid is always true & has set VideoSource & src_ has set
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
     *                      other function will be called once and return right value when preparing MediaPlayer firstly
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
     * @tc.expected: step7. IsMediaPlayerValid will be called three times
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
}
} // namespace OHOS::Ace::NG
