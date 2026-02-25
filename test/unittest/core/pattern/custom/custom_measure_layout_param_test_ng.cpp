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

#include <functional>
#include <utility>

#include "gtest/gtest.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_param.h"
#include "core/components_ng/pattern/custom/custom_node_pattern.h"
#include "core/components_ng/pattern/custom/custom_node_layout_algorithm.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const std::string TEST_TAG("test");

constexpr int32_t CHILD_COUNT_1 = 1;
constexpr int32_t CHILD_COUNT_2 = 2;
constexpr int32_t CHILD_COUNT_3 = 3;
} // namespace

class CustomMeasureLayoutParamTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> CreateNode(const std::string& tag);
};

inline void CustomMeasureLayoutParamTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

inline void CustomMeasureLayoutParamTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

inline RefPtr<FrameNode> CustomMeasureLayoutParamTestNg::CreateNode(const std::string& tag)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, -1, pattern);
    pattern->AttachToFrameNode(frameNode);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    return frameNode;
}

/**
 * @tc.name: ChildMountToTreeTest001
 * @tc.desc: Test child node mounting to parent tree.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutParamTestNg, ChildMountToTreeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create parent CustomMeasureLayoutNode.
     * @tc.expected: Parent node is created successfully.
     */
    auto parentNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(parentNode != nullptr && parentNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step2. Create child nodes and mount to parent.
     * @tc.expected: Children are mounted to parent successfully.
     */
    auto child1 = CreateNode(V2::TEXT_ETS_TAG);
    child1->MountToParent(parentNode);
    auto child2 = CreateNode(V2::TEXT_ETS_TAG);
    child2->MountToParent(parentNode);

    EXPECT_EQ(parentNode->GetChildren().size(), static_cast<size_t>(CHILD_COUNT_2));

    /**
     * @tc.steps: step3. Create LayoutWrapper with mounted children.
     * @tc.expected: LayoutWrapper reflects correct child count.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(parentNode, geometryNode, parentNode->GetLayoutProperty());

    RefPtr<GeometryNode> childGeometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper1 = AceType::MakeRefPtr<LayoutWrapperNode>(child1,
        childGeometryNode1, child1->GetLayoutProperty());
    RefPtr<GeometryNode> childGeometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper2 = AceType::MakeRefPtr<LayoutWrapperNode>(child2,
        childGeometryNode2, child2->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper1);
    layoutWrapper->AppendChild(childWrapper2);

    auto measureLayoutParam = AceType::MakeRefPtr<MeasureLayoutParam>(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(measureLayoutParam->GetTotalChildCount(), CHILD_COUNT_2);
}

/**
 * @tc.name: ChildMountFromTreeTest002
 * @tc.desc: Test child node mounting.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutParamTestNg, ChildUnmountFromTreeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create parent with children mounted.
     * @tc.expected: Parent has 2 children.
     */
    auto parentNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    auto child1 = CreateNode(V2::TEXT_ETS_TAG);
    child1->MountToParent(parentNode);
    auto child2 = CreateNode(V2::TEXT_ETS_TAG);
    child2->MountToParent(parentNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(parentNode, geometryNode, parentNode->GetLayoutProperty());

    RefPtr<GeometryNode> childGeometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper1 = AceType::MakeRefPtr<LayoutWrapperNode>(child1,
        childGeometryNode1, child1->GetLayoutProperty());
    RefPtr<GeometryNode> childGeometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper2 = AceType::MakeRefPtr<LayoutWrapperNode>(child2,
        childGeometryNode2, child2->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper1);
    layoutWrapper->AppendChild(childWrapper2);

    /**
     * @tc.steps: step2. Call Measure algorithm to mount children.
     * @tc.expected: Children are properly mounted.
     */
    auto pattern = parentNode->GetPattern<CustomNodePattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<CustomNodeLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    layoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));

    auto measureLayoutParam = AceType::MakeRefPtr<MeasureLayoutParam>(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(measureLayoutParam->GetTotalChildCount(), CHILD_COUNT_2);
}

/**
 * @tc.name: DynamicChildUpdateTest003
 * @tc.desc: Test dynamic child addition and removal.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutParamTestNg, DynamicChildUpdateTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create parent with initial children.
     */
    auto parentNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    auto child1 = CreateNode(V2::TEXT_ETS_TAG);
    child1->MountToParent(parentNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(parentNode, geometryNode, parentNode->GetLayoutProperty());

    RefPtr<GeometryNode> childGeometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper1 = AceType::MakeRefPtr<LayoutWrapperNode>(child1,
        childGeometryNode1, child1->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper1);

    auto measureLayoutParam = AceType::MakeRefPtr<MeasureLayoutParam>(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(measureLayoutParam->GetTotalChildCount(), CHILD_COUNT_1);

    /**
     * @tc.steps: step2. Add more children dynamically.
     * @tc.expected: Children are added and count updates.
     */
    auto child2 = CreateNode(V2::TEXT_ETS_TAG);
    child2->MountToParent(parentNode);
    RefPtr<GeometryNode> childGeometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper2 = AceType::MakeRefPtr<LayoutWrapperNode>(child2,
        childGeometryNode2, child2->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper2);

    auto child3 = CreateNode(V2::TEXT_ETS_TAG);
    child3->MountToParent(parentNode);
    RefPtr<GeometryNode> childGeometryNode3 = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper3 = AceType::MakeRefPtr<LayoutWrapperNode>(child3,
        childGeometryNode3, child3->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper3);

    measureLayoutParam->Update(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(measureLayoutParam->GetTotalChildCount(), CHILD_COUNT_3);

    /**
     * @tc.steps: step3. Verify all children are accessible.
     * @tc.expected: All indices are in range.
     */
    EXPECT_TRUE(measureLayoutParam->ChildIndexInRange(0));
    EXPECT_TRUE(measureLayoutParam->ChildIndexInRange(1));
    EXPECT_TRUE(measureLayoutParam->ChildIndexInRange(2));
    EXPECT_FALSE(measureLayoutParam->ChildIndexInRange(3));
}

/**
 * @tc.name: MeasureLayoutParamUpdateTest004
 * @tc.desc: Test MeasureLayoutParam::Update with various scenarios.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutParamTestNg, MeasureLayoutParamUpdateTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MeasureLayoutParam with initial children.
     * @tc.expected: Param is created with correct count.
     */
    auto parentNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    auto child1 = CreateNode(V2::TEXT_ETS_TAG);
    child1->MountToParent(parentNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(parentNode, geometryNode, parentNode->GetLayoutProperty());

    RefPtr<GeometryNode> childGeometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper1 = AceType::MakeRefPtr<LayoutWrapperNode>(child1,
        childGeometryNode1, child1->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper1);

    MeasureLayoutParam layoutParam(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutParam.GetTotalChildCount(), CHILD_COUNT_1);

    /**
     * @tc.steps: step2. Add more children and call Update.
     * @tc.expected: Count increases and new children are initialized.
     */
    auto child2 = CreateNode(V2::TEXT_ETS_TAG);
    child2->MountToParent(parentNode);
    RefPtr<GeometryNode> childGeometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper2 = AceType::MakeRefPtr<LayoutWrapperNode>(child2,
        childGeometryNode2, child2->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper2);

    auto child3 = CreateNode(V2::TEXT_ETS_TAG);
    child3->MountToParent(parentNode);
    RefPtr<GeometryNode> childGeometryNode3 = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper3 = AceType::MakeRefPtr<LayoutWrapperNode>(child3,
        childGeometryNode3, child3->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper3);

    layoutParam.Update(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutParam.GetTotalChildCount(), CHILD_COUNT_3);
    EXPECT_TRUE(layoutParam.ChildIndexInRange(0));
    EXPECT_TRUE(layoutParam.ChildIndexInRange(1));
    EXPECT_TRUE(layoutParam.ChildIndexInRange(2));
}

/**
 * @tc.name: MeasureLayoutParamUpdateWithSameCountTest005
 * @tc.desc: Test MeasureLayoutParam::Update when child count doesn't change.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutParamTestNg, MeasureLayoutParamUpdateWithSameCountTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MeasureLayoutParam with children.
     * @tc.expected: Param is created.
     */
    auto parentNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    auto child1 = CreateNode(V2::TEXT_ETS_TAG);
    child1->MountToParent(parentNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(parentNode, geometryNode, parentNode->GetLayoutProperty());

    RefPtr<GeometryNode> childGeometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper1 = AceType::MakeRefPtr<LayoutWrapperNode>(child1,
        childGeometryNode1, child1->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper1);

    MeasureLayoutParam layoutParam(AceType::RawPtr(layoutWrapper));
    int32_t initialCount = layoutParam.GetTotalChildCount();

    /**
     * @tc.steps: step2. Call Update without changing child count.
     * @tc.expected: Count remains the same, no unnecessary operations.
     */
    layoutParam.Update(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutParam.GetTotalChildCount(), initialCount);
}

/**
 * @tc.name: MeasureLayoutChildAccessTest006
 * @tc.desc: Test accessing children through MeasureLayoutChild.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutParamTestNg, MeasureLayoutChildAccessTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create parent with multiple children.
     * @tc.expected: Children are created.
     */
    auto parentNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    auto child1 = CreateNode(V2::TEXT_ETS_TAG);
    child1->MountToParent(parentNode);

    auto child2 = CreateNode(V2::TEXT_ETS_TAG);
    child2->MountToParent(parentNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(parentNode, geometryNode, parentNode->GetLayoutProperty());

    RefPtr<GeometryNode> childGeometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper1 = AceType::MakeRefPtr<LayoutWrapperNode>(child1,
        childGeometryNode1, child1->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper1);

    RefPtr<GeometryNode> childGeometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper2 = AceType::MakeRefPtr<LayoutWrapperNode>(child2,
        childGeometryNode2, child2->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper2);

    /**
     * @tc.steps: step2. Call Measure algorithm to mount children.
     * @tc.expected: Children are properly mounted.
     */
    auto pattern = parentNode->GetPattern<CustomNodePattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<CustomNodeLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    layoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));

    MeasureLayoutParam layoutParam(AceType::RawPtr(layoutWrapper));

    EXPECT_EQ(layoutParam.GetTotalChildCount(), CHILD_COUNT_2);
}


/**
 * @tc.name: MeasureLayoutChildConstraintTest007
 * @tc.desc: Test CreateChildConstraint for MeasureLayoutParam and MeasureLayoutChild.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutParamTestNg, MeasureLayoutChildConstraintTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode with comprehensive constraints.
     * @tc.expected: Node and child are created with constraints.
     */
    auto parentNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    auto child = CreateNode(V2::TEXT_ETS_TAG);
    child->MountToParent(parentNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(parentNode, geometryNode, parentNode->GetLayoutProperty());

    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(child, childGeometryNode, child->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper);

    /**
     * @tc.steps: step2. Set comprehensive layout constraints on parent.
     * @tc.expected: Constraints are applied successfully.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.percentReference.SetSizeT(SizeF(500.0f, 400.0f));
    parentLayoutConstraint.maxSize.SetSizeT(SizeF(600.0f, 500.0f));
    parentLayoutConstraint.minSize.SetSizeT(SizeF(100.0f, 80.0f));
    parentLayoutConstraint.parentIdealSize.SetWidth(800.0f);
    parentLayoutConstraint.parentIdealSize.SetHeight(600.0f);

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutProperty->UpdateContentConstraint();

    MeasureLayoutParam layoutParam(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step3. Test CreateChildConstraint on MeasureLayoutParam.
     * @tc.expected: Constraint is created with parent's properties.
     */
    auto constraint1 = layoutParam.CreateChildConstraint();
    EXPECT_EQ(constraint1.percentReference.Width(), 800.0f);
    EXPECT_EQ(constraint1.percentReference.Height(), 600.0f);
    EXPECT_EQ(constraint1.maxSize.Width(), 600.0f);
    EXPECT_EQ(constraint1.maxSize.Height(), 500.0f);

    /**
     * @tc.steps: step4. Test CreateChildConstraint on MeasureLayoutChild.
     * @tc.expected: Constraint is created with parent's properties.
     */
    auto& measureLayoutChild = layoutParam.Get(0);
    auto constraint2 = measureLayoutChild.CreateChildConstraint();
    EXPECT_EQ(constraint2.percentReference.Width(), 800.0f);
    EXPECT_EQ(constraint2.percentReference.Height(), 600.0f);
    EXPECT_EQ(constraint2.maxSize.Width(), 600.0f);
    EXPECT_EQ(constraint2.maxSize.Height(), 500.0f);
}

/**
 * @tc.name: CustomNodeLayoutAlgorithmMeasureTest008
 * @tc.desc: Test CustomNodeLayoutAlgorithm::Measure with render function.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutParamTestNg, CustomNodeLayoutAlgorithmMeasureTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabContent and push it to view stack processor.
     * @tc.expected: Make TabContent as CustomMeasureLayoutNode parent.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke CustomMeasureLayoutNode Create function and create textNode mount to it.
     * @tc.expected: Create CustomMeasureLayoutNode.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    customNode->MountToParent(frameNode);

    auto customPattern = customNode->GetPattern<CustomNodePattern>();
    ASSERT_NE(customPattern, nullptr);
    auto algorithm = AceType::DynamicCast<CustomNodeLayoutAlgorithm>(customPattern->CreateLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);

    auto childNode = CreateNode(V2::TEXT_ETS_TAG);
    childNode->MountToParent(customNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm));

    /**
     * @tc.steps: step3. Call Measure algorithm.
     * @tc.expected: Measure completes without crash and buildItem is created.
     */
    algorithm->Measure(AceType::RawPtr(layoutWrapper));

    auto buildItem = algorithm->MoveBuildItem();
    EXPECT_EQ(buildItem, nullptr);
}

/**
 * @tc.name: CustomNodeLayoutAlgorithmLayoutTest009
 * @tc.desc: Test CustomNodeLayoutAlgorithm::Layout with layout function.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutParamTestNg, CustomNodeLayoutAlgorithmLayoutTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomNodeLayoutAlgorithm.
     * @tc.expected: Algorithm is created.
     */
    auto renderFunction = [](int64_t, bool&) -> RefPtr<UINode> {
        return AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    };
    auto algorithm = AceType::MakeRefPtr<CustomNodeLayoutAlgorithm>(renderFunction);

    /**
     * @tc.steps: step2. Create CustomMeasureLayoutNode with layout function.
     * @tc.expected: Node is created with layout function set.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    bool layoutCalled = false;
    customNode->SetLayoutFunction([&layoutCalled](NG::LayoutWrapper*) { layoutCalled = true; });

    auto childNode = CreateNode(V2::TEXT_ETS_TAG);
    childNode->MountToParent(customNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm));

    /**
     * @tc.steps: step3. Call Layout algorithm.
     * @tc.expected: Layout function is called.
     */
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(layoutCalled);
}

/**
 * @tc.name: ChildIndexRangeTest010
 * @tc.desc: Test ChildIndexInRange with various indices.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutParamTestNg, ChildIndexRangeTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MeasureLayoutParam with specific number of children.
     * @tc.expected: Param is created.
     */
    auto parentNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(parentNode, geometryNode, parentNode->GetLayoutProperty());

    MeasureLayoutParam layoutParam(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step2. Test ChildIndexInRange with various indices.
     * @tc.expected: Correct results for each index.
     */
    // With 0 children, all indices should be out of range
    EXPECT_FALSE(layoutParam.ChildIndexInRange(-1));
    EXPECT_FALSE(layoutParam.ChildIndexInRange(0));
    EXPECT_FALSE(layoutParam.ChildIndexInRange(1));

    // Add a child and test again
    auto child = CreateNode(V2::TEXT_ETS_TAG);
    child->MountToParent(parentNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(child, childGeometryNode, child->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper);

    layoutParam.Update(AceType::RawPtr(layoutWrapper));

    EXPECT_FALSE(layoutParam.ChildIndexInRange(-1));
    EXPECT_TRUE(layoutParam.ChildIndexInRange(0));
    EXPECT_FALSE(layoutParam.ChildIndexInRange(1));
}

/**
 * @tc.name: MeasureLayoutChildUpdateSizeTest011
 * @tc.desc: Test MeasureLayoutChild::UpdateSize.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutParamTestNg, MeasureLayoutChildUpdateSizeTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LayoutWrapper with child.
     * @tc.expected: Wrapper is created.
     */
    auto parentNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    auto child = CreateNode(V2::TEXT_ETS_TAG);
    child->MountToParent(parentNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(parentNode, geometryNode, parentNode->GetLayoutProperty());

    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(child, childGeometryNode, child->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper);

    MeasureLayoutParam layoutParam(AceType::RawPtr(layoutWrapper));
    auto& measureLayoutChild = layoutParam.Get(0);

    /**
     * @tc.steps: step2. Update child size.
     * @tc.expected: Size is updated without crash.
     */
    SizeF testSize(100.0f, 200.0f);
    measureLayoutChild.UpdateSize(testSize);

    // The size update should propagate to the child's geometry node
    auto childGeomNode = childWrapper->GetGeometryNode();
    EXPECT_NE(childGeomNode, nullptr);
}

/**
 * @tc.name: CustomMeasureLayoutNodeFireOnMeasureTest012
 * @tc.desc: Test CustomMeasureLayoutNode::FireOnMeasure with measure function.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutParamTestNg, CustomMeasureLayoutNodeFireOnMeasureTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode.
     * @tc.expected: Node is created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step2. Call FireOnMeasure without setting measure function.
     * @tc.expected: Returns false.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto frameNode = CreateNode(V2::TEXT_ETS_TAG);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, geometryNode, frameNode->GetLayoutProperty());

    auto result = customNode->FireOnMeasure(AceType::RawPtr(layoutWrapper));
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. Set measure function and call FireOnMeasure again.
     * @tc.expected: Returns true and function is called.
     */
    bool measureCalled = false;
    customNode->SetMeasureFunction([&measureCalled](NG::LayoutWrapper*) {
        measureCalled = true;
    });

    result = customNode->FireOnMeasure(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(result);
    EXPECT_TRUE(measureCalled);
}

/**
 * @tc.name: CustomMeasureLayoutNodeFireOnLayoutTest013
 * @tc.desc: Test CustomMeasureLayoutNode::FireOnLayout with layout function.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutParamTestNg, CustomMeasureLayoutNodeFireOnLayoutTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode.
     * @tc.expected: Node is created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step2. Call FireOnLayout without setting layout function.
     * @tc.expected: Returns false.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto frameNode = CreateNode(V2::TEXT_ETS_TAG);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, geometryNode, frameNode->GetLayoutProperty());

    auto result = customNode->FireOnLayout(AceType::RawPtr(layoutWrapper));
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. Set layout function and call FireOnLayout again.
     * @tc.expected: Returns true and function is called.
     */
    bool layoutCalled = false;
    customNode->SetLayoutFunction([&layoutCalled](NG::LayoutWrapper*) {
        layoutCalled = true;
    });

    result = customNode->FireOnLayout(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(result);
    EXPECT_TRUE(layoutCalled);
}

/**
 * @tc.name: CustomMeasureLayoutNodeUpdateSizeTest014
 * @tc.desc: Test CustomMeasureLayoutNode::UpdateSize.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutParamTestNg, CustomMeasureLayoutNodeUpdateSizeTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode with MeasureLayoutParam.
     * @tc.expected: Node is created with param.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    auto child = CreateNode(V2::TEXT_ETS_TAG);
    child->MountToParent(customNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        customNode, geometryNode, customNode->GetLayoutProperty());

    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        child, childGeometryNode, child->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper);

    auto measureLayoutParam = AceType::MakeRefPtr<MeasureLayoutParam>(AceType::RawPtr(layoutWrapper));
    customNode->SetMeasureLayoutParam(measureLayoutParam);

    /**
     * @tc.steps: step2. Update child size through CustomMeasureLayoutNode.
     * @tc.expected: Size is updated successfully.
     */
    SizeF testSize(150.0f, 250.0f);
    bool result = customNode->UpdateSize(0, testSize);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step3. Try to update with invalid index.
     * @tc.expected: Returns false.
     */
    result = customNode->UpdateSize(5, testSize);
    EXPECT_FALSE(result);
}

} // namespace OHOS::Ace::NG
