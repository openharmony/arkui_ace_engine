/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <memory>
#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock-actions.h"

#define private public
#define protected public
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_media_player.h"

#include "core/components_ng/pattern/video/video_controller_async.h"
#include "core/components_ng/pattern/video/video_state_machine_pattern.h"
#include "core/components_ng/pattern/video/video_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/video/video_layout_property.h"
#include "core/components_ng/pattern/video/video_theme.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class VideoControllerAsyncTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp();
    void TearDown() {}

protected:
    static RefPtr<FrameNode> CreateVideoNodeWithController(RefPtr<VideoControllerAsync>& controller);
};

void VideoControllerAsyncTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MockPipelineContext::GetCurrent()->rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
}

void VideoControllerAsyncTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void VideoControllerAsyncTestNg::SetUp()
{
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<FrameNode> VideoControllerAsyncTestNg::CreateVideoNodeWithController(RefPtr<VideoControllerAsync>& controller)
{
    WeakPtr<VideoStateMachinePattern> emptyPattern;
    controller = AceType::MakeRefPtr<VideoControllerAsync>(emptyPattern);
    VideoModelNG().Create(controller);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto videoPattern = AceType::DynamicCast<VideoStateMachinePattern>(frameNode->GetPattern());
    CHECK_NULL_RETURN(videoPattern, nullptr);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(videoPattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(true));
    return AceType::Claim(frameNode);
}

/**
 * @tc.name: VideoControllerAsyncConstructor001
 * @tc.desc: Test VideoControllerAsync constructor stores pattern.
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAsyncTestNg, VideoControllerAsyncConstructor001, TestSize.Level1)
{
    WeakPtr<VideoStateMachinePattern> emptyPattern;
    auto controller = AceType::MakeRefPtr<VideoControllerAsync>(emptyPattern);
    ASSERT_NE(controller, nullptr);
    EXPECT_TRUE(controller->pattern_.Invalid());
}

/**
 * @tc.name: VideoControllerAsyncSetPattern001
 * @tc.desc: Test SetPattern updates pattern reference.
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAsyncTestNg, VideoControllerAsyncSetPattern001, TestSize.Level1)
{
    RefPtr<VideoControllerAsync> controller;
    auto frameNode = CreateVideoNodeWithController(controller);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(controller, nullptr);

    auto pattern = frameNode->GetPattern<VideoStateMachinePattern>();
    ASSERT_NE(pattern, nullptr);

    controller->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    EXPECT_FALSE(controller->pattern_.Invalid());
}

/**
 * @tc.name: VideoControllerAsyncStart001
 * @tc.desc: Test Start with null pattern calls callback with failure.
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAsyncTestNg, VideoControllerAsyncStart001, TestSize.Level1)
{
    WeakPtr<VideoStateMachinePattern> emptyPattern;
    auto controller = AceType::MakeRefPtr<VideoControllerAsync>(emptyPattern);
    
    bool callbackCalled = false;
    bool callbackSuccess = false;
    std::string callbackReason;
    
    controller->Start([&callbackCalled, &callbackSuccess, &callbackReason](bool success, const std::string& reason) {
        callbackCalled = true;
        callbackSuccess = success;
        callbackReason = reason;
    });
    
    EXPECT_TRUE(callbackCalled);
    EXPECT_FALSE(callbackSuccess);
    EXPECT_EQ(callbackReason, "pattern is null");
}

/**
 * @tc.name: VideoControllerAsyncPause001
 * @tc.desc: Test Pause with null pattern calls callback with failure.
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAsyncTestNg, VideoControllerAsyncPause001, TestSize.Level1)
{
    WeakPtr<VideoStateMachinePattern> emptyPattern;
    auto controller = AceType::MakeRefPtr<VideoControllerAsync>(emptyPattern);
    
    bool callbackCalled = false;
    controller->Pause([&callbackCalled](bool success, const std::string& reason) {
        callbackCalled = true;
        EXPECT_FALSE(success);
        EXPECT_EQ(reason, "pattern is null");
    });
    
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: VideoControllerAsyncStop001
 * @tc.desc: Test Stop with null pattern calls callback with failure.
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAsyncTestNg, VideoControllerAsyncStop001, TestSize.Level1)
{
    WeakPtr<VideoStateMachinePattern> emptyPattern;
    auto controller = AceType::MakeRefPtr<VideoControllerAsync>(emptyPattern);
    
    bool callbackCalled = false;
    controller->Stop([&callbackCalled](bool success, const std::string& reason) {
        callbackCalled = true;
        EXPECT_FALSE(success);
        EXPECT_EQ(reason, "pattern is null");
    });
    
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: VideoControllerAsyncReset001
 * @tc.desc: Test Reset with null pattern calls callback with failure.
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAsyncTestNg, VideoControllerAsyncReset001, TestSize.Level1)
{
    WeakPtr<VideoStateMachinePattern> emptyPattern;
    auto controller = AceType::MakeRefPtr<VideoControllerAsync>(emptyPattern);
    
    bool callbackCalled = false;
    controller->Reset([&callbackCalled](bool success, const std::string& reason) {
        callbackCalled = true;
        EXPECT_FALSE(success);
        EXPECT_EQ(reason, "pattern is null");
    });
    
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: VideoControllerAsyncClearPattern001
 * @tc.desc: Test ClearPattern resets pattern reference.
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAsyncTestNg, VideoControllerAsyncClearPattern001, TestSize.Level1)
{
    RefPtr<VideoControllerAsync> controller;
    auto frameNode = CreateVideoNodeWithController(controller);
    ASSERT_NE(frameNode, nullptr);
    
    EXPECT_FALSE(controller->pattern_.Invalid());
    controller->ClearPattern();
    EXPECT_TRUE(controller->pattern_.Invalid());
}

} // namespace OHOS::Ace::NG
