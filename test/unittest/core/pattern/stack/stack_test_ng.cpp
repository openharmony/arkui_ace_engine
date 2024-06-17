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

#include "gtest/gtest.h"

#define private public
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"
#include "core/components_ng/pattern/stack/stack_layout_algorithm.h"
#include "core/components_ng/pattern/stack/stack_layout_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr float ZERO = 0.0f;
const OffsetF ORIGIN_POINT(ZERO, ZERO);
constexpr float STACK_HEIGHT = 120.0f;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);

constexpr float SMALL_ITEM_WIDTH = 100.0f;
constexpr float SMALL_ITEM_HEIGHT = 40.0f;
const SizeF SMALL_ITEM_SIZE(SMALL_ITEM_WIDTH, SMALL_ITEM_HEIGHT);

const float HALF_PERCENT_WIDTH = 0.5f * FULL_SCREEN_WIDTH;
} // namespace
class StackTestNg : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::TearDown();
    }

protected:
    // std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> CreateStack(const Alignment alignment);
    std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> CreateSmallChild(
        const LayoutConstraintF& childLayoutConstraint);
    PaddingProperty CreatePadding(float left, float top, float right, float bottom);
};

PaddingProperty StackTestNg::CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}


std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> StackTestNg::CreateSmallChild(
    const LayoutConstraintF& childLayoutConstraint)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, firstGeometryNode, frameNode->GetLayoutProperty());
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SMALL_ITEM_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    auto pattern = frameNode->GetPattern<Pattern>();
    EXPECT_NE(pattern, nullptr);

    auto boxLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(boxLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));

    return { frameNode, layoutWrapper };
}

/**
 * @tc.name: StackTestNgTest001
 * @tc.desc: Test stack Layout with Alignment
 * @tc.type: FUNC
 */
HWTEST_F(StackTestNg, StackTestNgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create stack and get frameNode.
    */
    StackModelNG stackModelNG;
    stackModelNG.Create();
    stackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<StackLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ASSERT_NE(layoutProperty->GetPositionProperty(), nullptr);
    auto alignment = layoutProperty->GetPositionProperty()->GetAlignment();
    ASSERT_EQ(alignment, Alignment::TOP_LEFT);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto stackPattern = frameNode->GetPattern<StackPattern>();
    ASSERT_NE(stackPattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<StackLayoutAlgorithm>(stackPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(STACK_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    auto firstChild = CreateSmallChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    frameNode->AddChild(firstChildFrameNode);
    layoutWrapper->AppendChild(firstChildLayoutWrapper);

    /**
     * @tc.steps: step4. use layoutAlgorithm to layout.
     * @tc.expected: check whether the value of geometry frameSize and frameOffset is correct.
     */
    layoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    layoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutWrapper->GetGeometryNode()->GetMarginFrameSize(), SizeF(FULL_SCREEN_WIDTH, STACK_HEIGHT));
    ASSERT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, ZERO));
    ASSERT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    ASSERT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), ORIGIN_POINT);
}

/**
 * @tc.name: StackTestNgTest002
 * @tc.desc: Test stack Layout with AlignmentContent
 * @tc.type: FUNC
 */
HWTEST_F(StackTestNg, StackTestNgTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create stack and get frameNode.
    */
    StackModelNG stackModelNG;
    stackModelNG.Create();
    stackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<StackLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ASSERT_NE(layoutProperty->GetPositionProperty(), nullptr);
    auto alignmentContent = layoutProperty->GetPositionProperty()->GetAlignment();
    ASSERT_EQ(alignmentContent, Alignment::TOP_LEFT);
    layoutProperty->UpdateLayoutDirection(TextDirection::LTR);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: related function is called.
     */

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto stackPattern = frameNode->GetPattern<StackPattern>();
    ASSERT_NE(stackPattern, nullptr);
    auto layoutAlgorithm = stackPattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(STACK_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step4. use layoutAlgorithm to layout.
     * @tc.expected: check whether the value of geometry frameSize and frameOffset is correct.
     */
    layoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    layoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(FULL_SCREEN_WIDTH, STACK_HEIGHT));
    ASSERT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, ZERO));
}

/**
 * @tc.name: StackTestNgTest003
 * @tc.desc: Test stack Layout with Alignment and TextDirection is RTL
 * @tc.type: FUNC
 */
HWTEST_F(StackTestNg, StackTestNgTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create stack and get frameNode.
    */
    StackModelNG stackModelNG;
    stackModelNG.Create();
    stackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto stackPattern = frameNode->GetPattern<StackPattern>();
    ASSERT_NE(stackPattern, nullptr);

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(STACK_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    layoutWrapper->GetLayoutProperty()->UpdateAlignment(Alignment::BOTTOM_LEFT);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutDirection(TextDirection::RTL);
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = SizeF(HALF_PERCENT_WIDTH, STACK_HEIGHT);
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    
    /**
     * @tc.steps: step4. create child node
     */
    auto itemFrameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    itemGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> itemLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
    itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(HALF_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
    itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    itemLayoutWrapper->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_CENTER);
    auto textLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(textLayoutAlgorithm == nullptr);
    itemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(textLayoutAlgorithm));
    frameNode->AddChild(itemFrameNode);
    layoutWrapper->AppendChild(itemLayoutWrapper);

    /**
     * @tc.steps: step5. use layoutAlgorithm to layout.
     * @tc.expected: check whether the value of geometry frameSize and frameOffset is correct.
     */
    auto layoutAlgorithm = stackPattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    layoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step6. get child node
     * @tc.expected: check whether the value of child frameOffset is correct when text direction is RTL.
     */
    auto firstChildWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    EXPECT_EQ(firstChildWrapper->GetGeometryNode()->GetFrameOffset(),
        OffsetF(HALF_PERCENT_WIDTH, STACK_HEIGHT - SMALL_ITEM_HEIGHT));
}
} // namespace OHOS::Ace::NG
