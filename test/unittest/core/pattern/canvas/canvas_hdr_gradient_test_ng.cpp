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

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
class CanvasHdrTestRenderContext final : public RenderContext {
    DECLARE_ACE_TYPE(CanvasHdrTestRenderContext, RenderContext);
public:
    void SetHDRColorHeadRoom(float headRoom) override
    {
        ++hdrHeadRoomCallCount_;
        lastHdrHeadRoom_ = headRoom;
    }

    int32_t hdrHeadRoomCallCount_ = 0;
    float lastHdrHeadRoom_ = 0.0f;
};
} // namespace

class CanvasHdrGradientTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }

    static RefPtr<FrameNode> CreateCanvasNode()
    {
        auto* stack = ViewStackProcessor::GetInstance();
        auto nodeId = stack->ClaimNodeId();
        return FrameNode::GetOrCreateFrameNode(
            V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    }
};

/**
 * @tc.name: CanvasPatternNotifyGradientHDRColorHeadRoom001
 * @tc.desc: Verify max HDR headroom is reported for mixed gradient stops.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasHdrGradientTestNg, CanvasPatternNotifyGradientHDRColorHeadRoom001, TestSize.Level0)
{
    auto frameNode = CreateCanvasNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CanvasPattern>();
    ASSERT_NE(pattern, nullptr);
    auto testRenderContext = AceType::MakeRefPtr<CanvasHdrTestRenderContext>();
    frameNode->renderContext_ = testRenderContext;

    auto gradient = std::make_shared<Gradient>();
    GradientColor stop1;
    stop1.SetColor(Color::FromFloat(1.0f, 0.0f, 0.0f, 1.0f, 2.0f));
    gradient->AddColor(stop1);
    GradientColor stop2;
    stop2.SetColor(Color::FromFloat(0.0f, 1.0f, 0.0f, 1.0f, 3.5f));
    gradient->AddColor(stop2);

    pattern->NotifyGradientHDRColorHeadRoom(gradient);
    EXPECT_EQ(testRenderContext->hdrHeadRoomCallCount_, 1);
    EXPECT_FLOAT_EQ(testRenderContext->lastHdrHeadRoom_, 3.5f);
}

/**
 * @tc.name: CanvasPatternNotifyGradientHDRColorHeadRoom002
 * @tc.desc: Verify no call when gradient has no HDR stop.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasHdrGradientTestNg, CanvasPatternNotifyGradientHDRColorHeadRoom002, TestSize.Level0)
{
    auto frameNode = CreateCanvasNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CanvasPattern>();
    ASSERT_NE(pattern, nullptr);
    auto testRenderContext = AceType::MakeRefPtr<CanvasHdrTestRenderContext>();
    frameNode->renderContext_ = testRenderContext;

    auto gradient = std::make_shared<Gradient>();
    GradientColor normalStop;
    normalStop.SetColor(Color::RED);
    gradient->AddColor(normalStop);

    pattern->NotifyGradientHDRColorHeadRoom(gradient);
    EXPECT_EQ(testRenderContext->hdrHeadRoomCallCount_, 0);
}

/**
 * @tc.name: CanvasPatternSetGradientHDRColorHeadRoom001
 * @tc.desc: Verify SetFillGradient/SetStrokeGradient still report HDR headroom when paintMethod_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasHdrGradientTestNg, CanvasPatternSetGradientHDRColorHeadRoom001, TestSize.Level0)
{
    auto frameNode = CreateCanvasNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CanvasPattern>();
    ASSERT_NE(pattern, nullptr);
    auto testRenderContext = AceType::MakeRefPtr<CanvasHdrTestRenderContext>();
    frameNode->renderContext_ = testRenderContext;

    auto gradient = std::make_shared<Gradient>();
    GradientColor hdrStop;
    hdrStop.SetColor(Color::FromFloat(1.0f, 1.0f, 1.0f, 1.0f, 2.2f));
    gradient->AddColor(hdrStop);

    ASSERT_EQ(pattern->paintMethod_, nullptr);
    pattern->SetFillGradient(gradient);
    pattern->SetStrokeGradient(gradient);
    EXPECT_EQ(testRenderContext->hdrHeadRoomCallCount_, 2);
    EXPECT_FLOAT_EQ(testRenderContext->lastHdrHeadRoom_, 2.2f);
}

/**
 * @tc.name: CanvasPatternSetGradientHDRColorHeadRoom002
 * @tc.desc: Verify null gradient is ignored safely.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasHdrGradientTestNg, CanvasPatternSetGradientHDRColorHeadRoom002, TestSize.Level0)
{
    auto frameNode = CreateCanvasNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CanvasPattern>();
    ASSERT_NE(pattern, nullptr);
    auto testRenderContext = AceType::MakeRefPtr<CanvasHdrTestRenderContext>();
    frameNode->renderContext_ = testRenderContext;

    std::shared_ptr<Gradient> emptyGradient;
    pattern->SetFillGradient(emptyGradient);
    pattern->SetStrokeGradient(emptyGradient);
    pattern->NotifyGradientHDRColorHeadRoom(emptyGradient);
    EXPECT_EQ(testRenderContext->hdrHeadRoomCallCount_, 0);
}
} // namespace OHOS::Ace::NG
