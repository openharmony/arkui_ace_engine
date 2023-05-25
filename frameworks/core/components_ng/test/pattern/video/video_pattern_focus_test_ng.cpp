/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include <string>

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
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
struct TestProperty {
    std::optional<std::string> src;
    std::optional<double> progressRate;
    std::optional<std::string> posterUrl;
    std::optional<bool> muted;
    std::optional<bool> autoPlay;
    std::optional<bool> controls;
    std::optional<bool> loop;
    std::optional<RefPtr<VideoControllerV2>> videoController;
};
constexpr bool MUTED_VALUE = false;
constexpr bool AUTO_PLAY = false;
constexpr bool CONTROL_VALUE = true;
constexpr bool LOOP_VALUE = false;
constexpr int32_t SLIDER_INDEX = 2;
constexpr double VIDEO_PROGRESS_RATE = 1.0;
const std::string VIDEO_SRC = "common/video.mp4";
const std::string VIDEO_POSTER_URL = "common/img2.png";

// Size
constexpr float VIDEO_WIDTH = 300.0f;
constexpr float VIDEO_HEIGHT = 300.0f;
const SizeF VIDEO_SIZE(VIDEO_WIDTH, VIDEO_HEIGHT);
TestProperty testProperty;
} // namespace

class VideoPatternFocusTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateVideoNode(TestProperty& testProperty);
};

void VideoPatternFocusTestNg::SetUpTestSuite()
{
    testProperty.progressRate = VIDEO_PROGRESS_RATE;
    testProperty.muted = MUTED_VALUE;
    testProperty.autoPlay = AUTO_PLAY;
    testProperty.controls = CONTROL_VALUE;
    testProperty.loop = LOOP_VALUE;
    MockPipelineBase::SetUp();
}

void VideoPatternFocusTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

RefPtr<FrameNode> VideoPatternFocusTestNg::CreateVideoNode(TestProperty& testProperty)
{
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    VideoModelNG().Create(videoController);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    CHECK_NULL_RETURN(videoPattern, nullptr);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(true));

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
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: VideoFocusTest001
 * @tc.desc: Create Video, and test focus.
 * @tc.type: FUNC
 */
HWTEST_F(VideoPatternFocusTestNg, VideoFocusTest001, TestSize.Level1)
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
HWTEST_F(VideoPatternFocusTestNg, VideoFocusTest002, TestSize.Level1)
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
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
} // namespace OHOS::Ace::NG
