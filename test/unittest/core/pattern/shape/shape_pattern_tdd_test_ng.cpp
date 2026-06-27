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

#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/common/mock_resource_adapter_v2.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "core/accessibility/accessibility_manager.h"
#include "core/common/container.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/shape/circle_model_ng.h"
#include "core/components_ng/pattern/shape/circle_pattern.h"
#include "core/components_ng/pattern/shape/ellipse_model_ng.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_container_layout_algorithm.h"
#include "core/components_ng/pattern/shape/shape_container_paint_property.h"
#include "core/components_ng/pattern/shape/shape_container_pattern.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/components_ng/pattern/shape/shape_pattern.h"
#include "core/components_ng/property/layout_constraint.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class ShapePatternTddTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
};

namespace {
constexpr float TEST_FRAME_WIDTH = 300.0f;
constexpr float TEST_FRAME_HEIGHT = 200.0f;
} // namespace

/**
 * @tc.name: ShapeContainerMeasure001
 * @tc.desc: ShapeContainerLayoutAlgorithm::Measure sets FrameWidth when IsWidthFix is true
 *           and FrameHeight when IsHeightFix is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapePatternTddTestNg, ShapeContainerMeasure001, TestSize.Level1)
{
    ShapeModelNG().Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT));

    CircleModelNG().Create();
    auto childNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(childNode, nullptr);
    frameNode->AddChild(childNode);
    RefPtr<GeometryNode> childGeometry = AceType::MakeRefPtr<GeometryNode>();
    childGeometry->SetFrameSize(SizeF(100, 50));
    RefPtr<LayoutWrapperNode> childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childNode, childGeometry, childNode->GetLayoutProperty());
    ASSERT_NE(childWrapper, nullptr);

    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);

    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, layoutProperty);
    layoutWrapper.AppendChild(childWrapper);
    layoutWrapper.ApplyConstraint(LayoutConstraintF());
    layoutProperty->UpdateContentConstraint();

    auto layoutAlgorithm =
        AceType::DynamicCast<ShapeContainerLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);

    layoutAlgorithm->Measure(&layoutWrapper);

    auto resultGeometry = layoutWrapper.GetGeometryNode();
    ASSERT_NE(resultGeometry, nullptr);
    EXPECT_GE(resultGeometry->GetFrameSize().Width(), 0.0f);
    EXPECT_GE(resultGeometry->GetFrameSize().Height(), 0.0f);
}

/**
 * @tc.name: ShapeContainerMeasure002
 * @tc.desc: ShapeContainerLayoutAlgorithm::Measure returns early at CHECK_NULL_VOID when layoutPolicy has no value
 * @tc.type: FUNC
 */
HWTEST_F(ShapePatternTddTestNg, ShapeContainerMeasure002, TestSize.Level1)
{
    ShapeModelNG().Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->layoutPolicy_.reset();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT));

    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, layoutProperty);
    layoutWrapper.ApplyConstraint(LayoutConstraintF());
    layoutProperty->UpdateContentConstraint();

    auto layoutAlgorithm =
        AceType::DynamicCast<ShapeContainerLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);

    layoutAlgorithm->Measure(&layoutWrapper);

    auto resultGeometry = layoutWrapper.GetGeometryNode();
    ASSERT_NE(resultGeometry, nullptr);
}

/**
 * @tc.name: GetChildrenSize003
 * @tc.desc: GetChildrenSize sets parentIdealSize.SetWidth(0) when widthLayoutPolicy is adaptive (not NO_MATCH)
 * @tc.type: FUNC
 */
HWTEST_F(ShapePatternTddTestNg, GetChildrenSize003, TestSize.Level1)
{
    ShapeModelNG().Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);

    CircleModelNG().Create();
    auto childNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(childNode, nullptr);
    frameNode->AddChild(childNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT));

    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, layoutProperty);

    RefPtr<GeometryNode> childGeometry = AceType::MakeRefPtr<GeometryNode>();
    childGeometry->SetFrameSize(SizeF(50, 50));
    childGeometry->GetMarginFrameSize().SetMainSize(50, Axis::HORIZONTAL);

    LayoutConstraintF parentLayoutConstrain;
    parentLayoutConstrain.selfIdealSize = OptionalSize<float>(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT);
    parentLayoutConstrain.percentReference = SizeF(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT);
    childNode->GetGeometryNode()->SetParentLayoutConstraint(parentLayoutConstrain);

    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childNode, childGeometry, childNode->GetLayoutProperty());
    ASSERT_NE(childLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(childLayoutWrapper);

    auto layoutAlgorithm =
        AceType::DynamicCast<ShapeContainerLayoutAlgorithm>(
            frameNode->GetPattern<ShapeContainerPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto childFrame = layoutAlgorithm->GetChildrenSize(&layoutWrapper, SizeF(0, 0));
    EXPECT_TRUE(childFrame.IsNonNegative());
}

/**
 * @tc.name: GetChildrenSize004
 * @tc.desc: GetChildrenSize sets parentIdealSize.SetHeight(0) when heightLayoutPolicy is adaptive (not NO_MATCH)
 * @tc.type: FUNC
 */
HWTEST_F(ShapePatternTddTestNg, GetChildrenSize004, TestSize.Level1)
{
    ShapeModelNG().Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);

    CircleModelNG().Create();
    auto childNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(childNode, nullptr);
    frameNode->AddChild(childNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT));

    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, layoutProperty);

    RefPtr<GeometryNode> childGeometry = AceType::MakeRefPtr<GeometryNode>();
    childGeometry->SetFrameSize(SizeF(50, 50));
    childGeometry->GetMarginFrameSize().SetMainSize(50, Axis::VERTICAL);

    LayoutConstraintF parentLayoutConstrain;
    parentLayoutConstrain.selfIdealSize = OptionalSize<float>(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT);
    parentLayoutConstrain.percentReference = SizeF(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT);
    childNode->GetGeometryNode()->SetParentLayoutConstraint(parentLayoutConstrain);

    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childNode, childGeometry, childNode->GetLayoutProperty());
    ASSERT_NE(childLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(childLayoutWrapper);

    auto layoutAlgorithm =
        AceType::DynamicCast<ShapeContainerLayoutAlgorithm>(
            frameNode->GetPattern<ShapeContainerPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto childFrame = layoutAlgorithm->GetChildrenSize(&layoutWrapper, SizeF(0, 0));
    EXPECT_TRUE(childFrame.IsNonNegative());
}

/**
 * @tc.name: GetChildrenSize005
 * @tc.desc: GetChildrenSize applies child RenderContext offset when HasOffset returns true
 * @tc.type: FUNC
 */
HWTEST_F(ShapePatternTddTestNg, GetChildrenSize005, TestSize.Level1)
{
    ShapeModelNG().Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);

    CircleModelNG().Create();
    auto childNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(childNode, nullptr);
    frameNode->AddChild(childNode);
    childNode->AttachToMainTree();

    auto renderContext = childNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateOffset(OffsetT<Dimension>(Dimension(10.0f), Dimension(20.0f)));
    EXPECT_TRUE(renderContext->HasOffset());

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT));

    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());

    RefPtr<GeometryNode> childGeometry = AceType::MakeRefPtr<GeometryNode>();
    childGeometry->SetFrameSize(SizeF(50, 50));
    childGeometry->GetMarginFrameSize().SetMainSize(50, Axis::HORIZONTAL);

    LayoutConstraintF parentLayoutConstrain;
    parentLayoutConstrain.selfIdealSize = OptionalSize<float>(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT);
    parentLayoutConstrain.percentReference = SizeF(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT);
    childNode->GetGeometryNode()->SetParentLayoutConstraint(parentLayoutConstrain);

    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childNode, childGeometry, childNode->GetLayoutProperty());
    ASSERT_NE(childLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(childLayoutWrapper);

    auto layoutAlgorithm =
        AceType::DynamicCast<ShapeContainerLayoutAlgorithm>(
            frameNode->GetPattern<ShapeContainerPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto childFrame = layoutAlgorithm->GetChildrenSize(&layoutWrapper, SizeF(0, 0));
    EXPECT_TRUE(childFrame.IsNonNegative());
}

/**
 * @tc.name: GetChildrenSize006
 * @tc.desc: GetChildrenSize skips offset conversion when child RenderContext HasOffset returns false
 * @tc.type: FUNC
 */
HWTEST_F(ShapePatternTddTestNg, GetChildrenSize006, TestSize.Level1)
{
    ShapeModelNG().Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);

    CircleModelNG().Create();
    auto childNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(childNode, nullptr);
    frameNode->AddChild(childNode);

    auto renderContext = childNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_FALSE(renderContext->HasOffset());

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT));

    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());

    RefPtr<GeometryNode> childGeometry = AceType::MakeRefPtr<GeometryNode>();
    childGeometry->SetFrameSize(SizeF(50, 50));
    childGeometry->GetMarginFrameSize().SetMainSize(50, Axis::HORIZONTAL);

    LayoutConstraintF parentLayoutConstrain;
    parentLayoutConstrain.selfIdealSize = OptionalSize<float>(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT);
    parentLayoutConstrain.percentReference = SizeF(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT);
    childNode->GetGeometryNode()->SetParentLayoutConstraint(parentLayoutConstrain);

    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childNode, childGeometry, childNode->GetLayoutProperty());
    ASSERT_NE(childLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(childLayoutWrapper);

    auto layoutAlgorithm =
        AceType::DynamicCast<ShapeContainerLayoutAlgorithm>(
            frameNode->GetPattern<ShapeContainerPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto childFrame = layoutAlgorithm->GetChildrenSize(&layoutWrapper, SizeF(0, 0));
    EXPECT_TRUE(childFrame.IsNonNegative());
}

} // namespace OHOS::Ace::NG
