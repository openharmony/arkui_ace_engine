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

#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/video/video_model_ng.h"
#include "core/components_ng/pattern/video/video_pattern.h"
#include "core/components_ng/test/mock/render/mock_media_player.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string VIDEO_SRC = "common/video.mp4";
constexpr float VIDEO_WIDTH = 300.0f;
constexpr float VIDEO_HEIGHT = 300.0f;
constexpr uint32_t DURATION = 100;
constexpr uint32_t CURRENTTIME = 100;
} // namespace

class VideoAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateVideoNode();
};

void VideoAccessibilityPropertyTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
}

void VideoAccessibilityPropertyTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

RefPtr<FrameNode> VideoAccessibilityPropertyTestNg::CreateVideoNode()
{
    auto videoController = AceType::MakeRefPtr<VideoControllerV2>();
    CHECK_NULL_RETURN(videoController, nullptr);
    VideoModelNG().Create(videoController);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_RETURN(element, nullptr);
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: VideoAccessibilityPropertyTest001
 * @tc.desc: Test the text property of VideoAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(VideoAccessibilityPropertyTestNg, VideoAccessibilityPropertyTest001, TestSize.Level1)
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

    video.SetSrc(VIDEO_SRC);
    EXPECT_EQ(videoAccessibilitProperty->GetText(), VIDEO_SRC);
}

/**
 * @tc.name: VideoAccessibilityPropertyTest002
 * @tc.desc: Test the rangeInfo property of VideoAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(VideoAccessibilityPropertyTestNg, VideoAccessibilityPropertyTest002, TestSize.Level1)
{
    auto frameNode = CreateVideoNode();
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
    pattern->OnPrepared(VIDEO_WIDTH, VIDEO_HEIGHT, DURATION, 0, true);
    EXPECT_EQ(pattern->duration_, DURATION);
    pattern->currentPos_ = CURRENTTIME;
    accessibilityValue = videoAccessibilitProperty->GetAccessibilityValue();
    EXPECT_EQ(accessibilityValue.min, 0);
    EXPECT_EQ(accessibilityValue.max, DURATION);
    EXPECT_EQ(accessibilityValue.current, CURRENTTIME);

    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), Stop()).WillOnce(Return(0));
    pattern->Stop();
    accessibilityValue = videoAccessibilitProperty->GetAccessibilityValue();
    EXPECT_EQ(accessibilityValue.current, 0);
}
} // namespace OHOS::Ace::NG