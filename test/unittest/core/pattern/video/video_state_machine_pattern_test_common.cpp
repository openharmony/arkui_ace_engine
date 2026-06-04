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

using ::testing::Return;
using ::testing::_;

namespace OHOS::Ace::NG {

void VideoStateMachinePatternTestNg::SetUpTestSuite()
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

void VideoStateMachinePatternTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void VideoStateMachinePatternTestNg::SetUp()
{
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<FrameNode> VideoStateMachinePatternTestNg::CreateVideoNode(TestProperty& testProperty)
{
    WeakPtr<VideoStateMachinePattern> emptyPattern;
    auto videoControllerAsync = AceType::MakeRefPtr<VideoControllerAsync>(emptyPattern);
    VideoModelNG().Create(videoControllerAsync);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto videoPattern = AceType::DynamicCast<VideoStateMachinePattern>(frameNode->GetPattern());
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

} // namespace OHOS::Ace::NG
