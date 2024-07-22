/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/unittest/core/rosen/rosen_render_context_test.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

void RosenRenderContextTest::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void RosenRenderContextTest::TearDown()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<RosenRenderContext> RosenRenderContextTest::InitRosenRenderContext(const RefPtr<FrameNode>& frameNode)
{
    auto rosenRenderContext = AceType::MakeRefPtr<RosenRenderContext>();
    RenderContext::ContextParam contextParam;
    contextParam.type = RenderContext::ContextType::CANVAS;
    contextParam.surfaceName.emplace("test");
    std::optional<RenderContext::ContextParam> contextParamValue = std::make_optional(contextParam);
    rosenRenderContext->InitContext(false, contextParamValue);
    rosenRenderContext->SetHostNode(frameNode);
    return rosenRenderContext;
}

/**
 * @tc.name: RosenRenderContextTest001
 * @tc.desc: SetPivot().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    float xPivot = 10.0;
    float yPivot = 10.0;
    float zPivot = 10.0;
    rosenRenderContext->SetPivot(xPivot, yPivot, zPivot);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivot().x_, 10.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivot().y_, 10.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivotZ(), 10.0);
    xPivot = 5.0;
    rosenRenderContext->SetPivot(xPivot, yPivot, zPivot);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivot().x_, 5.0);
}

/**
 * @tc.name: RosenRenderContextTest002
 * @tc.desc: SetTransitionPivot().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest002, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->SetTransitionPivot(SizeF(100.0, 100.0), true);
    ScaleOptions scaleOptions;
    scaleOptions.centerX = CalcDimension(50.0, DimensionUnit::PX);
    scaleOptions.centerY = CalcDimension(50.0, DimensionUnit::PX);
    rosenRenderContext->GetOrCreateTransitionAppearing()->UpdateScale(scaleOptions);
    rosenRenderContext->SetTransitionPivot(SizeF(100.0, 100.0), true);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivot().x_, 0.5);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivot().y_, 0.5);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivotZ(), 0);
    RotateOptions rotateOptions;
    rotateOptions.centerX = CalcDimension(50.0, DimensionUnit::PX);
    rotateOptions.centerY = CalcDimension(50.0, DimensionUnit::PX);
    rotateOptions.centerZ = CalcDimension(50.0, DimensionUnit::PX);
    rosenRenderContext->GetOrCreateTransitionAppearing()->UpdateRotate(rotateOptions);
    rosenRenderContext->SetTransitionPivot(SizeF(100.0, 100.0), true);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivot().x_, 0.5);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivot().y_, 0.5);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivotZ(), 50.0);
}

/**
 * @tc.name: RosenRenderContextTest003
 * @tc.desc: SetSandBox().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest003, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    std::optional<OffsetF> parentPosition = std::make_optional(OffsetF(100.0, 100.0));
    rosenRenderContext->SetSandBox(parentPosition, false);
    EXPECT_EQ(rosenRenderContext->sandBoxCount_, 1);
    rosenRenderContext->SetSandBox(parentPosition, true);
    EXPECT_EQ(rosenRenderContext->sandBoxCount_, 1);
    rosenRenderContext->SetSandBox(std::nullopt, true);
    EXPECT_EQ(rosenRenderContext->sandBoxCount_, 0);
    rosenRenderContext->sandBoxCount_ = 2;
    rosenRenderContext->SetSandBox(std::nullopt, true);
    EXPECT_EQ(rosenRenderContext->sandBoxCount_, 0);
}

/**
 * @tc.name: RosenRenderContextTest004
 * @tc.desc: SetFrameWithoutAnimation().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest004, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    RectF paintRect = { 10.0f, 10.0f, 10.0f, 10.0f };
    rosenRenderContext->SetFrameWithoutAnimation(paintRect);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[0], paintRect.GetX());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[1], paintRect.GetY());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[2], paintRect.Width());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[3], paintRect.Height());
}

/**
 * @tc.name: RosenRenderContextTest005
 * @tc.desc: SyncGeometryFrame().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest005, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    RectF paintRect = { 10.0f, 10.0f, 10.0f, 10.0f };
    rosenRenderContext->SyncGeometryFrame(paintRect);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[0], paintRect.GetX());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[1], paintRect.GetY());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[2], paintRect.Width());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[3], paintRect.Height());
    rosenRenderContext->DoTextureExport(1);
    rosenRenderContext->SyncGeometryFrame(paintRect);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetBounds()[0], paintRect.GetX());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetBounds()[1], paintRect.GetY());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetBounds()[2], paintRect.Width());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetBounds()[3], paintRect.Height());
}

/**
 * @tc.name: RosenRenderContextTest006
 * @tc.desc: SetChildBounds().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest006, TestSize.Level1)
{
    auto hostNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(hostNode);
    RectF paintRect = { 10.0f, 10.0f, 10.0f, 10.0f };
    rosenRenderContext->SetChildBounds(paintRect);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetChildren().size(), 0);
    auto rosenRenderContextChild = AceType::MakeRefPtr<RosenRenderContext>();
    RenderContext::ContextParam contextParam;
    contextParam.type = RenderContext::ContextType::CANVAS;
    contextParam.surfaceName.emplace("test1");
    std::optional<RenderContext::ContextParam> contextParamValue = std::make_optional(contextParam);
    rosenRenderContextChild->InitContext(false, contextParamValue);
    auto frameNode = FrameNode::GetOrCreateFrameNode("child", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    rosenRenderContextChild->SetHostNode(frameNode);
    rosenRenderContext->AddChild(rosenRenderContextChild, 10);
    rosenRenderContext->SetChildBounds(paintRect);
    EXPECT_EQ(rosenRenderContextChild->GetRSNode()->GetStagingProperties().GetBounds()[0], 0.0);
    EXPECT_EQ(rosenRenderContextChild->GetRSNode()->GetStagingProperties().GetBounds()[1], 0.0);
    EXPECT_EQ(rosenRenderContextChild->GetRSNode()->GetStagingProperties().GetBounds()[2], paintRect.Width());
    EXPECT_EQ(rosenRenderContextChild->GetRSNode()->GetStagingProperties().GetBounds()[3], paintRect.Height());
}

/**
 * @tc.name: RosenRenderContextTest008
 * @tc.desc: SyncGeometryFrame().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest008, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->OnForegroundEffectUpdate(1.0f);
    EXPECT_TRUE(rosenRenderContext->GetRSNode()->GetStagingProperties().GetForegroundEffectRadius() - 1.0 < 1);
}

/**
 * @tc.name: RosenRenderContextTest011
 * @tc.desc: SyncGeometryFrame().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest011, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->OnOpacityUpdate(10.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetAlpha(), 10.0);
}
} // namespace OHOS::Ace::NG