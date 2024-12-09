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
#include <cmath>
#include <cstdint>
#include <string>

#include "gtest/gtest.h"
#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/render_node/render_node_pattern.h"
#include "core/components_ng/pattern/render_node/render_node_paint_property.h"
#include "core/components_ng/pattern/render_node/render_node_paint_method.h"
#include "core/components_ng/pattern/render_node/render_node_modifier.h"
#include "core/components_ng/pattern/render_node/render_node_layout_property.h"
#include "core/components_ng/pattern/render_node/render_node_layout_algorithm.h"
#include "core/components_ng/base/frame_node.h"
#include "test/mock/core/render/mock_render_context.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components_ng/render/paint_wrapper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class RenderNodeTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void RenderNodeTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void RenderNodeTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: RatingCreateTest001
 * @tc.desc: Create Rating.
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestNg, RenderNodePattern001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("Pattern", 0, AceType::MakeRefPtr<RenderNodePattern>());
    auto renderNodePattern = frameNode->GetPattern<RenderNodePattern>();

    auto layoutAlgorithm = renderNodePattern->CreateLayoutAlgorithm();
    EXPECT_NE(layoutAlgorithm, nullptr);

    auto layoutProperty = renderNodePattern->CreateLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);

    auto paintProperty = renderNodePattern->CreatePaintProperty();
    EXPECT_NE(paintProperty, nullptr);

    auto paintMethod = renderNodePattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);

    renderNodePattern->Invalidate();
    EXPECT_EQ(renderNodePattern->renderNodeModifier_->renderNodeFlag_->Get(), 1);
    
    renderNodePattern->SetLabel("LabelOne");

    const NG::InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    renderNodePattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("label"), "LabelOne");
}

/**
 * @tc.name: RatingCreateTest001
 * @tc.desc: Create Rating.
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestNg, RenderNodePaintMethod001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("PaintMethod", 0, AceType::MakeRefPtr<RenderNodePattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto renderNodePattern = frameNode->GetPattern<RenderNodePattern>();
    ASSERT_NE(renderNodePattern, nullptr);
    auto renderNodeLayoutProperty = renderNodePattern->GetLayoutProperty<RenderNodeLayoutProperty>();
    ASSERT_NE(renderNodeLayoutProperty, nullptr);

    auto drawCallback = [](DrawingContext& context) {};
    auto renderNodeModifier = AceType::MakeRefPtr<RenderNodeModifier>(drawCallback);
    RenderNodePaintMethod renderNodePaintMethod(renderNodeModifier);

    RefPtr<RenderContext> renderContext = RenderContext::Create();
    auto paintProperty = renderNodePattern->CreatePaintProperty();
    auto renderNodePaintProperty = AceType::DynamicCast<RenderNodePaintProperty>(paintProperty);
    renderNodePaintProperty->UpdateRenderNodeFlag(1);
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    auto modifier = renderNodePaintMethod.GetContentModifier(AceType::RawPtr(paintWrapper));
    EXPECT_NE(modifier, nullptr);

    renderNodePaintMethod.UpdateContentModifier(AceType::RawPtr(paintWrapper));
    EXPECT_EQ(renderNodePaintMethod.renderNodeFlag_, 1);
}

/**
 * @tc.name: RatingCreateTest001
 * @tc.desc: Create Rating.
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestNg, RenderNodeLayoutAlgorithm001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("LayoutAlgorithm", 0, AceType::MakeRefPtr<RenderNodePattern>());
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    SizeF contentSize(100, 100);
    geometryNode->SetContentSize(contentSize);
    ASSERT_NE(geometryNode, nullptr);
    auto renderNodePattern = frameNode->GetPattern<RenderNodePattern>();
    ASSERT_NE(renderNodePattern, nullptr);
    auto renderNodeLayoutProperty = renderNodePattern->GetLayoutProperty<RenderNodeLayoutProperty>();
    ASSERT_NE(renderNodeLayoutProperty, nullptr);

    auto renderNodeLayoutAlgorithm = AceType::MakeRefPtr<RenderNodeLayoutAlgorithm>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    renderNodeLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(geometryNode->GetFrameSize(), SizeF(0, 0));

    SizeF frameSize(200, 200);
    geometryNode->SetFrameSize(frameSize);
    renderNodeLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(geometryNode->GetContentOffset(), OffsetF(0, 0));
}

/**
 * @tc.name: RenderNodeLayoutAlgorithmTest001
 * @tc.desc: RenderNodeLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestNg, RenderNodeLayoutAlgorithmTest001, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
    };
    auto frameNode = FrameNode::CreateFrameNode("frame", 0, AceType::MakeRefPtr<RenderNodePattern>());
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto childOne = FrameNode::CreateFrameNode("RenderNode", 0, AceType::MakeRefPtr<RenderNodePattern>());
    auto childTwo = FrameNode::CreateFrameNode("child", 0, AceType::MakeRefPtr<RenderNodePattern>());
    auto childThree = FrameNode::CreateFrameNode("childThree", 0, AceType::MakeRefPtr<RenderNodePattern>());
    auto renderNodeLayoutAlgorithm = AceType::MakeRefPtr<RenderNodeLayoutAlgorithm>();
    auto childLayoutWrapperOne = childOne->CreateLayoutWrapper();
    auto childLayoutWrapperTwo = childTwo->CreateLayoutWrapper();
    auto childLayoutWrapperThree = childThree->CreateLayoutWrapper();
    layoutWrapper->cachedList_ = std::list<RefPtr<LayoutWrapper>>();
    layoutWrapper->cachedList_.push_back(childLayoutWrapperOne);
    layoutWrapper->cachedList_.push_back(childLayoutWrapperTwo);
    childLayoutWrapperTwo->GetLayoutProperty()->UpdateParentLayoutConstraint(layoutConstraintF);
    layoutWrapper->cachedList_.push_back(childLayoutWrapperThree);
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_->selfIdealSize =
        CalcSize(CalcLength(1.0), CalcLength(0.0));
    renderNodeLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().ToString(), "[1.00 x 0.00]");
}

/**
 * @tc.name: RenderNodeLayoutAlgorithmTest002
 * @tc.desc: RenderNodeLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestNg, RenderNodeLayoutAlgorithmTest002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("frame", 0, AceType::MakeRefPtr<RenderNodePattern>());
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto renderNodeLayoutAlgorithm = AceType::MakeRefPtr<RenderNodeLayoutAlgorithm>();
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    std::optional<CalcLength> width = CalcLength(1.0);
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_->selfIdealSize = CalcSize(width, std::nullopt);
    renderNodeLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().ToString(), "[0.00 x 0.00]");
}

/**
 * @tc.name: RenderNodeLayoutAlgorithmTest003
 * @tc.desc: RenderNodeLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestNg, RenderNodeLayoutAlgorithmTest003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("frame", 0, AceType::MakeRefPtr<RenderNodePattern>());
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto renderNodeLayoutAlgorithm = AceType::MakeRefPtr<RenderNodeLayoutAlgorithm>();
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_->selfIdealSize = std::nullopt;
    renderNodeLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().ToString(), "[0.00 x 0.00]");
}

/**
 * @tc.name: RenderNodeLayoutAlgorithmTest004
 * @tc.desc: RenderNodeLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestNg, RenderNodeLayoutAlgorithmTest004, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
        .selfIdealSize = OptionalSizeF(std::nullopt, std::nullopt),
    };
    auto frameNode = FrameNode::CreateFrameNode("frame", 0, AceType::MakeRefPtr<RenderNodePattern>());
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto renderNodeLayoutAlgorithm = AceType::MakeRefPtr<RenderNodeLayoutAlgorithm>();
    renderNodeLayoutAlgorithm->MeasureContent(layoutConstraintF, AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().ToString(), "[0.00 x 0.00]");
}

/**
 * @tc.name: RenderNodeLayoutAlgorithmTest005
 * @tc.desc: RenderNodeLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestNg, RenderNodeLayoutAlgorithmTest005, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("frame", 0, AceType::MakeRefPtr<RenderNodePattern>());
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto childOne = FrameNode::CreateFrameNode("RenderNode", 0, AceType::MakeRefPtr<RenderNodePattern>());
    auto childTwo = FrameNode::CreateFrameNode("child", 0, AceType::MakeRefPtr<RenderNodePattern>());
    auto renderNodeLayoutAlgorithm = AceType::MakeRefPtr<RenderNodeLayoutAlgorithm>();
    auto childLayoutWrapperOne = childOne->CreateLayoutWrapper();
    auto childLayoutWrapperTwo = childTwo->CreateLayoutWrapper();
    layoutWrapper->cachedList_ = std::list<RefPtr<LayoutWrapper>>();
    layoutWrapper->cachedList_.push_back(childLayoutWrapperOne);
    layoutWrapper->cachedList_.push_back(childLayoutWrapperTwo);
    layoutWrapper->GetLayoutProperty()->positionProperty_ = std::make_unique<PositionProperty>();
    Alignment align;
    align.horizontal_ = 0.0f;
    layoutWrapper->GetLayoutProperty()->positionProperty_->UpdateAlignment(align);
    layoutWrapper->GetGeometryNode()->content_ = nullptr;
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_->selfIdealSize =
        CalcSize(CalcLength(1.0), CalcLength(0.0));
    renderNodeLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().ToString(), "[0.00 x 0.00]");
}

/**
 * @tc.name: RenderNodeLayoutAlgorithmTest006
 * @tc.desc: RenderNodeLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestNg, RenderNodeLayoutAlgorithmTest006, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
    };
    auto frameNode = FrameNode::CreateFrameNode("frame", 0, AceType::MakeRefPtr<RenderNodePattern>());
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto childOne = FrameNode::CreateFrameNode("frame", 0, AceType::MakeRefPtr<RenderNodePattern>());
    auto childTwo =
        FrameNode::CreateFrameNode(V2::CUSTOM_FRAME_NODE_ETS_TAG, 0, AceType::MakeRefPtr<RenderNodePattern>());
    auto childThree = FrameNode::CreateFrameNode("childThree", 0, AceType::MakeRefPtr<RenderNodePattern>());
    auto renderNodeLayoutAlgorithm = AceType::MakeRefPtr<RenderNodeLayoutAlgorithm>();
    auto childLayoutWrapperOne = childOne->CreateLayoutWrapper();
    auto childLayoutWrapperTwo = childTwo->CreateLayoutWrapper();
    auto childLayoutWrapperThree = childThree->CreateLayoutWrapper();
    layoutWrapper->cachedList_ = std::list<RefPtr<LayoutWrapper>>();
    layoutWrapper->cachedList_.push_back(childLayoutWrapperOne);
    layoutWrapper->cachedList_.push_back(childLayoutWrapperTwo);
    childLayoutWrapperTwo->GetLayoutProperty()->UpdateParentLayoutConstraint(layoutConstraintF);
    layoutWrapper->cachedList_.push_back(childLayoutWrapperThree);
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_->selfIdealSize =
        CalcSize(CalcLength(1.0), CalcLength(0.0));
    renderNodeLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().ToString(), "[1.00 x 0.00]");
}
}
