/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#define private public
#define protected public
#include "core/components_ng/pattern/overlay/accessibility_focus_paint_node_pattern.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const NG::OffsetF OFFSET_F = { 1.0, 2.0 };
} // namespace

class AccessibilityFocusPaintNodeTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void AccessibilityFocusPaintNodeTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void AccessibilityFocusPaintNodeTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: UpdateFocusNode001
 * @tc.desc: Verify update node correctly.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusPaintNodeTestNg, UpdateFocusNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create focus node.
     */
    auto focusFrameNode = NG::FrameNode::CreateFrameNode("focusNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusFrameNode, nullptr);

    /**
     * @tc.steps: step2. create paint node.
     */
    auto paintNode = NG::FrameNode::CreateFrameNode(V2::ACCESSIBILITY_FOCUS_PAINT_NODE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::AccessibilityFocusPaintNodePattern>(focusFrameNode));
    ASSERT_NE(paintNode, nullptr);

    /**
     * @tc.steps: step3. get AccessibilityFocusPaintNodePattern from paint node.
     */
    auto pattern = paintNode->GetPattern<NG::AccessibilityFocusPaintNodePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. call UpdateFocusNode.
     */
    pattern->UpdateFocusNode(focusFrameNode);

    /**
     * @tc.expected: pattern->GetFocusNode() == WeakPtr<FrameNode>(focusFrameNode)
     */
    EXPECT_EQ(pattern->GetFocusNode(), WeakPtr<FrameNode>(focusFrameNode));
    /**
     * @tc.expected: focusFrameNode->GetPaintNode() == pattern->GetHost()
     */
    EXPECT_EQ(focusFrameNode->GetPaintNode(), pattern->GetHost());
}

/**
 * @tc.name: UpdateRootNode001
 * @tc.desc: Verify update root node correctly.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusPaintNodeTestNg, UpdateRootNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create focus node.
     */
    auto focusFrameNode = NG::FrameNode::CreateFrameNode("focusNode", 2, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusFrameNode, nullptr);

    /**
     * @tc.steps: step2. create paint node.
     */
    auto paintNode = NG::FrameNode::CreateFrameNode(V2::ACCESSIBILITY_FOCUS_PAINT_NODE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::AccessibilityFocusPaintNodePattern>(focusFrameNode));
    ASSERT_NE(paintNode, nullptr);

    /**
     * @tc.steps: step3. get AccessibilityFocusPaintNodePattern from paint node.
     */
    auto pattern = paintNode->GetPattern<NG::AccessibilityFocusPaintNodePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. get overlayManager.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    focusFrameNode->AttachContext(AceType::RawPtr(pipelineContext));

    /**
     * @tc.steps: step5. create root node.
     */
    auto rootNode = AceType::DynamicCast<NG::FrameNode>(overlayManager->FindWindowScene(focusFrameNode));
    /**
     * @tc.steps: step6. call UpdateRootNode.
     */
    pattern->UpdateRootNode(rootNode);

    /**
     * @tc.expected: pattern->GetRootNode() == WeakPtr<FrameNode>(rootNode)
     */
    EXPECT_EQ(pattern->GetRootNode(), WeakPtr<FrameNode>(rootNode));
}

/**
 * @tc.name: UpdateRenderWithFocusNode001
 * @tc.desc: Verify update render correctly.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusPaintNodeTestNg, UpdateRenderWithFocusNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create focus node.
     */
    auto focusFrameNode = NG::FrameNode::CreateFrameNode("focusNode", 3, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusFrameNode, nullptr);

    /**
     * @tc.steps: step2. create paint node.
     */
    auto paintNode = NG::FrameNode::CreateFrameNode(V2::ACCESSIBILITY_FOCUS_PAINT_NODE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::AccessibilityFocusPaintNodePattern>(focusFrameNode));
    ASSERT_NE(paintNode, nullptr);

    /**
     * @tc.steps: step3. get AccessibilityFocusPaintNodePattern from paint node.
     */
    auto pattern = paintNode->GetPattern<NG::AccessibilityFocusPaintNodePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. call UpdateRenderWithFocusNode().
     */
    pattern->UpdateRenderWithFocusNode();

    /**
     * @tc.steps: step5. get geometry node from focusFrameNode.
     */
    auto focusGeometryNode = focusFrameNode->GetGeometryNode();
    ASSERT_NE(focusGeometryNode, nullptr);

    /**
     * @tc.steps: step6. get geometry node from host.
     */
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto hostGeometryNode = host->GetGeometryNode();
    ASSERT_NE(hostGeometryNode, nullptr);

    /**
     * @tc.expected: focusGeometryNode->GetFrameOffset() == hostGeometryNode->GetFrameOffset()
     */
    EXPECT_EQ(focusGeometryNode->GetFrameOffset(), hostGeometryNode->GetFrameOffset());
}

/**
 * @tc.name: SetPosition001
 * @tc.desc: Verify set position correctly.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusPaintNodeTestNg, SetPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create focus node.
     */
    auto focusFrameNode = NG::FrameNode::CreateFrameNode("focusNode", 4, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusFrameNode, nullptr);

    /**
     * @tc.steps: step2. create paint node.
     */
    auto paintNode = NG::FrameNode::CreateFrameNode(V2::ACCESSIBILITY_FOCUS_PAINT_NODE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::AccessibilityFocusPaintNodePattern>(focusFrameNode));
    ASSERT_NE(paintNode, nullptr);

    /**
     * @tc.steps: step3. get AccessibilityFocusPaintNodePattern from paint node.
     */
    auto pattern = paintNode->GetPattern<NG::AccessibilityFocusPaintNodePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. call SetPosition.
     */
    pattern->SetPosition(OFFSET_F, focusFrameNode);

    /**
     * @tc.steps: step5. get renderContext from focusFrameNode.
     */
    auto renderContext = focusFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.expected: renderContext->GetPosition() == OFFSET_F
     */
    auto pos = OffsetT<Dimension>(Dimension(OFFSET_F.GetX()), Dimension(OFFSET_F.GetY()));
    EXPECT_EQ(renderContext->GetPosition(), pos);
}

/**
 * @tc.name: ChangeSize001
 * @tc.desc: Verify change size correctly.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusPaintNodeTestNg, ChangeSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create focus node.
     */
    auto focusFrameNode = NG::FrameNode::CreateFrameNode("focusNode", 5, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusFrameNode, nullptr);

    /**
     * @tc.steps: step2. create paint node.
     */
    auto paintNode = NG::FrameNode::CreateFrameNode(V2::ACCESSIBILITY_FOCUS_PAINT_NODE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::AccessibilityFocusPaintNodePattern>(focusFrameNode));
    ASSERT_NE(paintNode, nullptr);

    /**
     * @tc.steps: step3. get AccessibilityFocusPaintNodePattern from paint node.
     */
    auto pattern = paintNode->GetPattern<NG::AccessibilityFocusPaintNodePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. call ChangeSize.
     */
    pattern->ChangeSize(0.1, 0.1, focusFrameNode);

    /**
     * @tc.steps: step5. get layoutProperty from focusFrameNode.
     */
    auto layoutProperty = focusFrameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step6. get LayoutConstraint from layoutProperty.
     */
    auto &&layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    ASSERT_NE(layoutConstraint, nullptr);
    NG::CalcSize calcSize = { NG::CalcLength(0.1), NG::CalcLength(0.1) };

    /**
     * @tc.expected: layoutConstraint.selfIdealSize == calcSize
     */
    EXPECT_EQ(layoutConstraint->selfIdealSize, calcSize);

    /**
     * @tc.expected: layoutConstraint.maxSize == calcSize
     */
    EXPECT_EQ(layoutConstraint->maxSize, calcSize);
}

/**
 * @tc.name: ChangelRotate001
 * @tc.desc: Verify change rotate correctly.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusPaintNodeTestNg, ChangelRotate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create focus node.
     */
    auto focusFrameNode = NG::FrameNode::CreateFrameNode("focusNode", 6, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusFrameNode, nullptr);

    /**
     * @tc.steps: step2. create paint node.
     */
    auto paintNode = NG::FrameNode::CreateFrameNode(V2::ACCESSIBILITY_FOCUS_PAINT_NODE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::AccessibilityFocusPaintNodePattern>(focusFrameNode));
    ASSERT_NE(paintNode, nullptr);

    /**
     * @tc.steps: step3. get AccessibilityFocusPaintNodePattern from paint node.
     */
    auto pattern = paintNode->GetPattern<NG::AccessibilityFocusPaintNodePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. call ChangelRotate.
     */
    pattern->ChangelRotate(0.1, focusFrameNode);

    /**
     * @tc.steps: step5. get renderContext from focusFrameNode.
     */
    auto renderContext = focusFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.expected: renderContext->GetTransformRotate() == 0.1
     */
    auto value = NG::Vector5F(0, 0, 1, 0.1, 0);
    EXPECT_EQ(renderContext->GetTransformRotate(), value);
}

/**
 * @tc.name: GetPaintRectCenter001
 * @tc.desc: Verify get paint rect center correctly.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusPaintNodeTestNg, GetPaintRectCenter001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create focus node.
     */
    auto focusFrameNode = NG::FrameNode::CreateFrameNode("focusNode", 7, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusFrameNode, nullptr);

    /**
     * @tc.steps: step2. create paint node.
     */
    auto paintNode = NG::FrameNode::CreateFrameNode(V2::ACCESSIBILITY_FOCUS_PAINT_NODE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::AccessibilityFocusPaintNodePattern>(focusFrameNode));
    ASSERT_NE(paintNode, nullptr);

    /**
     * @tc.steps: step3. get AccessibilityFocusPaintNodePattern from paint node.
     */
    auto pattern = paintNode->GetPattern<NG::AccessibilityFocusPaintNodePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. get renderContext from focusFrameNode.
     */
    auto renderContext = focusFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    auto offset = paintRect.GetOffset();
    PointF pointNode(offset.GetX() + paintRect.Width() / CENTER_DIVISOR,
        offset.GetY() + paintRect.Height() / CENTER_DIVISOR);

    /**
     * @tc.expected: pattern->GetPaintRectCenter return correctly.
     */
    EXPECT_EQ(pattern->GetPaintRectCenter(focusFrameNode), OffsetF(pointNode.GetX(), pointNode.GetY()));
}

/**
 * @tc.name: IsScrollable001
 * @tc.desc: Verify IsScrollable correctly.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusPaintNodeTestNg, IsScrollable001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create focus node.
     */
    auto focusFrameNode = NG::FrameNode::CreateFrameNode("List", 8, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusFrameNode, nullptr);

    /**
     * @tc.steps: step2. create paint node.
     */
    auto paintNode = NG::FrameNode::CreateFrameNode(V2::ACCESSIBILITY_FOCUS_PAINT_NODE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::AccessibilityFocusPaintNodePattern>(focusFrameNode));
    ASSERT_NE(paintNode, nullptr);

    /**
     * @tc.steps: step3. get AccessibilityFocusPaintNodePattern from paint node.
     */
    auto pattern = paintNode->GetPattern<NG::AccessibilityFocusPaintNodePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.expected: pattern->IsScrollable return true.
     */
    EXPECT_TRUE(pattern->IsScrollable(focusFrameNode));
}

/**
 * @tc.name: IsScrollable002
 * @tc.desc: Verify IsScrollable correctly.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusPaintNodeTestNg, IsScrollable002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create focus node.
     */
    auto focusFrameNode = NG::FrameNode::CreateFrameNode("focusNode", 9, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusFrameNode, nullptr);

    /**
     * @tc.steps: step2. create paint node.
     */
    auto paintNode = NG::FrameNode::CreateFrameNode(V2::ACCESSIBILITY_FOCUS_PAINT_NODE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::AccessibilityFocusPaintNodePattern>(focusFrameNode));
    ASSERT_NE(paintNode, nullptr);

    /**
     * @tc.steps: step3. get AccessibilityFocusPaintNodePattern from paint node.
     */
    auto pattern = paintNode->GetPattern<NG::AccessibilityFocusPaintNodePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.expected: pattern->IsScrollable return false.
     */
    EXPECT_FALSE(pattern->IsScrollable(focusFrameNode));
}

/**
 * @tc.name: GetScrollableAncestorClip001
 * @tc.desc: Verify get scrollable ancestor clip correctly.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusPaintNodeTestNg, GetScrollableAncestorClip001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create focus node.
     */
    auto focusFrameNode = NG::FrameNode::CreateFrameNode("focusNode", 10, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusFrameNode, nullptr);

    /**
     * @tc.steps: step2. create paint node.
     */
    auto paintNode = NG::FrameNode::CreateFrameNode(V2::ACCESSIBILITY_FOCUS_PAINT_NODE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::AccessibilityFocusPaintNodePattern>(focusFrameNode));
    ASSERT_NE(paintNode, nullptr);

    /**
     * @tc.steps: step3. get AccessibilityFocusPaintNodePattern from paint node.
     */
    auto pattern = paintNode->GetPattern<NG::AccessibilityFocusPaintNodePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. get pipeline from focus node.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    /**
     * @tc.expected: pattern->GetScrollableAncestorClip == pipeline->GetRootRect.
     */
    focusFrameNode->AttachContext(AceType::RawPtr(pipeline));
    EXPECT_EQ(pattern->GetScrollableAncestorClip(focusFrameNode), pipeline->GetRootRect());
}

/**
 * @tc.name: OnDetachFromFocusNode001
 * @tc.desc: Verify detach from focus node correctly.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusPaintNodeTestNg, OnDetachFromFocusNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create focus node.
     */
    auto focusFrameNode = NG::FrameNode::CreateFrameNode("focusNode", 11, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusFrameNode, nullptr);

    /**
     * @tc.steps: step2. create paint node.
     */
    auto paintNode = NG::FrameNode::CreateFrameNode(V2::ACCESSIBILITY_FOCUS_PAINT_NODE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::AccessibilityFocusPaintNodePattern>(focusFrameNode));
    ASSERT_NE(paintNode, nullptr);

    /**
     * @tc.steps: step3. get AccessibilityFocusPaintNodePattern from paint node.
     */
    auto pattern = paintNode->GetPattern<NG::AccessibilityFocusPaintNodePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step4. call OnDetachFromFocusNode.
     */
    pattern->OnDetachFromFocusNode();

    /**
     * @tc.expected: (pattern->GetFocusNode()).Upgrade() == nullptr.
     */
    EXPECT_TRUE((pattern->GetFocusNode()).Upgrade() == nullptr);
}
} // namespace OHOS::Ace::NG