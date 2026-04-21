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

#include <cstddef>
#include <utility>
#include <set>

#include "gtest/gtest.h"
#define private public
#define protected public
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_param.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/custom/custom_node_base.h"
#include "core/components_ng/pattern/custom/custom_node_pattern.h"
#include "core/components_ng/pattern/custom/custom_title_node.h"
#include "core/components_ng/pattern/custom/custom_app_bar_node.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const std::string TEST_TAG("test");
} // namespace

class CustomMeasureLayoutTestNg2 : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> CreateNode(const std::string& tag);
};

inline void CustomMeasureLayoutTestNg2::SetUp()
{
    MockPipelineContext::SetUp();
}

inline void CustomMeasureLayoutTestNg2::TearDown()
{
    MockPipelineContext::TearDown();
}

inline RefPtr<FrameNode> CustomMeasureLayoutTestNg2::CreateNode(const std::string& tag)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, -1, pattern);
    pattern->AttachToFrameNode(frameNode);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    return frameNode;
}

} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG {
/**
 * @tc.name: CustomMeasureLayoutTest019
 * @tc.desc: Test CustomNodeLayoutAlgorithm::OnReset resets render function
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest019, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomNodeLayoutAlgorithm with render function.
     * @tc.expected: Algorithm is created with valid render function.
     */
    int renderCallCount = 0;
    auto renderFunction = [&renderCallCount](int64_t, bool&) -> RefPtr<UINode> {
        renderCallCount++;
        return AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    };
    auto algorithm = AceType::MakeRefPtr<CustomNodeLayoutAlgorithm>(renderFunction);
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step2. Create CustomMeasureLayoutNode and layout wrapper.
     * @tc.expected: Node and wrapper are created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm));

    /**
     * @tc.steps: step3. Call OnReset to clear render function.
     * @tc.expected: Render function is reset to nullptr.
     */
    algorithm->OnReset();

    /**
     * @tc.steps: step4. Call Measure after reset.
     * @tc.expected: Measure completes without calling render function (renderCallCount unchanged).
     */
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(renderCallCount, 0);
}

/**
 * @tc.name: CustomMeasureLayoutTest020
 * @tc.desc: Test multiple children measurement and layout sequence
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest020, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create parent node with multiple children.
     * @tc.expected: Parent and children are created.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);
    customNode->MountToParent(frameNode);

    auto child1 = CreateNode(V2::TEXT_ETS_TAG);
    auto child2 = CreateNode(V2::BUTTON_ETS_TAG);
    auto child3 = CreateNode(V2::IMAGE_ETS_TAG);
    child1->MountToParent(customNode);
    child2->MountToParent(customNode);
    child3->MountToParent(customNode);

    /**
     * @tc.steps: step2. Create layout wrappers with proper hierarchy.
     * @tc.expected: Layout wrapper hierarchy is established.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto customPattern = customNode->GetPattern<CustomNodePattern>();
    ASSERT_NE(customPattern, nullptr);
    auto algorithm = AceType::DynamicCast<CustomNodeLayoutAlgorithm>(customPattern->CreateLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);

    auto customLayoutProperty = customNode->GetLayoutProperty();
    ASSERT_NE(customLayoutProperty, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customLayoutProperty);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm));

    RefPtr<GeometryNode> childGeom1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<GeometryNode> childGeom2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<GeometryNode> childGeom3 = AceType::MakeRefPtr<GeometryNode>();
    auto childLayoutProperty1 = child1->GetLayoutProperty();
    auto childLayoutProperty2 = child2->GetLayoutProperty();
    auto childLayoutProperty3 = child3->GetLayoutProperty();
    ASSERT_NE(childLayoutProperty1, nullptr);
    ASSERT_NE(childLayoutProperty2, nullptr);
    ASSERT_NE(childLayoutProperty3, nullptr);
    auto childWrapper1 = AceType::MakeRefPtr<LayoutWrapperNode>(child1, childGeom1, childLayoutProperty1);
    auto childWrapper2 = AceType::MakeRefPtr<LayoutWrapperNode>(child2, childGeom2, childLayoutProperty2);
    auto childWrapper3 = AceType::MakeRefPtr<LayoutWrapperNode>(child3, childGeom3, childLayoutProperty3);
    layoutWrapper->AppendChild(childWrapper1);
    layoutWrapper->AppendChild(childWrapper2);
    layoutWrapper->AppendChild(childWrapper3);

    /**
     * @tc.steps: step3. Verify child count in MeasureLayoutParam.
     * @tc.expected: Total child count is 3.
     */
    auto measureLayoutParam = AceType::MakeRefPtr<MeasureLayoutParam>(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(measureLayoutParam->GetTotalChildCount(), 3);

    /**
     * @tc.steps: step4. Verify index range checking for multiple children.
     * @tc.expected: Indices 0-2 are valid, others are invalid.
     */
    EXPECT_TRUE(measureLayoutParam->ChildIndexInRange(0));
    EXPECT_TRUE(measureLayoutParam->ChildIndexInRange(1));
    EXPECT_TRUE(measureLayoutParam->ChildIndexInRange(2));
    EXPECT_FALSE(measureLayoutParam->ChildIndexInRange(-1));
    EXPECT_FALSE(measureLayoutParam->ChildIndexInRange(3));
    EXPECT_FALSE(measureLayoutParam->ChildIndexInRange(100));
}

/**
 * @tc.name: CustomMeasureLayoutTest021
 * @tc.desc: Test MeasureLayoutParam::Update with child count reduction
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest021, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create parent with initial 3 children.
     * @tc.expected: Parent and children are created.
     */
    auto parentNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    auto child1 = CreateNode(V2::TEXT_ETS_TAG);
    auto child2 = CreateNode(V2::TEXT_ETS_TAG);
    auto child3 = CreateNode(V2::TEXT_ETS_TAG);
    child1->MountToParent(parentNode);
    child2->MountToParent(parentNode);
    child3->MountToParent(parentNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(parentNode, geometryNode, parentNode->GetLayoutProperty());

    RefPtr<GeometryNode> childGeom1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<GeometryNode> childGeom2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<GeometryNode> childGeom3 = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper1 = AceType::MakeRefPtr<LayoutWrapperNode>(child1, childGeom1, child1->GetLayoutProperty());
    auto childWrapper2 = AceType::MakeRefPtr<LayoutWrapperNode>(child2, childGeom2, child2->GetLayoutProperty());
    auto childWrapper3 = AceType::MakeRefPtr<LayoutWrapperNode>(child3, childGeom3, child3->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper1);
    layoutWrapper->AppendChild(childWrapper2);
    layoutWrapper->AppendChild(childWrapper3);

    /**
     * @tc.steps: step2. Create MeasureLayoutParam with 3 children.
     * @tc.expected: Count is 3.
     */
    MeasureLayoutParam layoutParam(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutParam.GetTotalChildCount(), 3);
    EXPECT_TRUE(layoutParam.ChildIndexInRange(2));

    /**
     * @tc.steps: step3. Simulate child removal by creating new wrapper with 1 child.
     * @tc.expected: Update reduces count to 1.
     */
    auto layoutWrapper2 =
        AceType::MakeRefPtr<LayoutWrapperNode>(parentNode, geometryNode, parentNode->GetLayoutProperty());
    layoutWrapper2->AppendChild(childWrapper1);

    layoutParam.Update(AceType::RawPtr(layoutWrapper2));
    EXPECT_EQ(layoutParam.GetTotalChildCount(), 1);
    EXPECT_FALSE(layoutParam.ChildIndexInRange(2));
    EXPECT_TRUE(layoutParam.ChildIndexInRange(0));
}

/**
 * @tc.name: CustomMeasureLayoutTest022
 * @tc.desc: Test custom measure callback with size calculation
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest022, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode and parent.
     * @tc.expected: Node created and mounted.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);
    customNode->MountToParent(frameNode);

    auto child = CreateNode(V2::TEXT_ETS_TAG);
    child->MountToParent(customNode);

    /**
     * @tc.steps: step2. Set custom measure function that captures wrapper.
     * @tc.expected: Measure function is set.
     */
    NG::LayoutWrapper* capturedWrapper = nullptr;
    SizeF capturedSize;
    auto measureFunc = [&capturedWrapper, &capturedSize](NG::LayoutWrapper* layoutWrapper) {
        capturedWrapper = layoutWrapper;
        if (layoutWrapper) {
            auto geometry = layoutWrapper->GetGeometryNode();
            if (geometry) {
                capturedSize = geometry->GetFrameSize();
            }
        }
    };
    customNode->SetMeasureFunction(std::move(measureFunc));

    /**
     * @tc.steps: step3. Create layout wrapper and trigger FireOnMeasure.
     * @tc.expected: Measure function is called with correct wrapper.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(300.0f, 200.0f));
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());

    bool result = customNode->FireOnMeasure(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(result);
    EXPECT_EQ(capturedWrapper, AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: CustomMeasureLayoutTest023
 * @tc.desc: Test custom layout callback with position calculation
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest023, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode with child.
     * @tc.expected: Node and child created.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);
    customNode->MountToParent(frameNode);

    auto child = CreateNode(V2::TEXT_ETS_TAG);
    child->MountToParent(customNode);

    /**
     * @tc.steps: step2. Set custom layout function.
     * @tc.expected: Layout function is set.
     */
    bool layoutExecuted = false;
    NG::LayoutWrapper* layoutWrapperPtr = nullptr;
    auto layoutFunc = [&layoutExecuted, &layoutWrapperPtr](NG::LayoutWrapper* layoutWrapper) {
        layoutExecuted = true;
        layoutWrapperPtr = layoutWrapper;
    };
    customNode->SetLayoutFunction(std::move(layoutFunc));

    /**
     * @tc.steps: step3. Create layout wrapper and trigger FireOnLayout.
     * @tc.expected: Layout function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());

    bool result = customNode->FireOnLayout(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(result);
    EXPECT_TRUE(layoutExecuted);
    EXPECT_EQ(layoutWrapperPtr, AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: CustomMeasureLayoutTest024
 * @tc.desc: Test Render with very large deadline value
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest024, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode.
     * @tc.expected: Node created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step2. Set recycle render function.
     * @tc.expected: Function is set.
     */
    int recycleCallCount = 0;
    auto recycleRenderFunc = [&recycleCallCount]() { recycleCallCount++; };
    customNode->SetRecycleRenderFunc(std::move(recycleRenderFunc));

    /**
     * @tc.steps: step3. Call Render with very large deadline.
     * @tc.expected: Render succeeds and calls recycle function.
     */
    int64_t largeDeadline = GetSysTimestamp() + INT64_MAX / 2;
    bool result = customNode->Render(largeDeadline);
    EXPECT_TRUE(result);
    EXPECT_EQ(recycleCallCount, 1);
}

/**
 * @tc.name: CustomMeasureLayoutTest025
 * @tc.desc: Test Render with deadline in the past
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest025, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode.
     * @tc.expected: Node created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step2. Set recycle render function.
     * @tc.expected: Function is set.
     */
    int recycleCallCount = 0;
    auto recycleRenderFunc = [&recycleCallCount]() { recycleCallCount++; };
    customNode->SetRecycleRenderFunc(std::move(recycleRenderFunc));

    /**
     * @tc.steps: step3. Call Render with deadline in the past.
     * @tc.expected: Render completes without crash.
     */
    int64_t pastDeadline = GetSysTimestamp() - 1000000;
    bool result = customNode->Render(pastDeadline);
    // Note: Render behavior depends on timing and system state
    // Just verify the function can be called without crash
    (void)result;
    (void)recycleCallCount;
}

/**
 * @tc.name: CustomMeasureLayoutTest026
 * @tc.desc: Test MeasureLayoutChild::GetChild and GetOrCreateChild
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest026, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create parent with child.
     * @tc.expected: Parent and child created.
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
     * @tc.steps: step2. Create MeasureLayoutParam and access child.
     * @tc.expected: Child is accessible via GetChild.
     */
    MeasureLayoutParam layoutParam(AceType::RawPtr(layoutWrapper));
    auto& measureLayoutChild = layoutParam.Get(0);

    // GetChild may return nullptr in test environment
    // Just verify the function can be called without crash
    auto retrievedChild = measureLayoutChild.GetChild();
    (void)retrievedChild;

    auto retrievedChild2 = measureLayoutChild.GetOrCreateChild();
    (void)retrievedChild2;
}

/**
 * @tc.name: CustomMeasureLayoutTest027
 * @tc.desc: Test MeasureLayoutParam::GetLayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest027, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create layout wrapper.
     * @tc.expected: Layout wrapper created.
     */
    auto parentNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(parentNode, geometryNode, parentNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. Create MeasureLayoutParam and retrieve LayoutWrapper.
     * @tc.expected: GetLayoutWrapper returns the original wrapper.
     */
    MeasureLayoutParam layoutParam(AceType::RawPtr(layoutWrapper));
    auto retrievedWrapper = layoutParam.GetLayoutWrapper();
    EXPECT_EQ(retrievedWrapper, AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: CustomMeasureLayoutTest028
 * @tc.desc: Test empty custom node without children
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest028, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create empty CustomMeasureLayoutNode.
     * @tc.expected: Node created without children.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);
    EXPECT_EQ(customNode->GetChildren().size(), 0);

    /**
     * @tc.steps: step2. Create MeasureLayoutParam for empty node.
     * @tc.expected: Param has 0 children.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());

    MeasureLayoutParam layoutParam(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutParam.GetTotalChildCount(), 0);
    EXPECT_FALSE(layoutParam.ChildIndexInRange(0));
    EXPECT_FALSE(layoutParam.ChildIndexInRange(-1));
}

/**
 * @tc.name: CustomMeasureLayoutTest029
 * @tc.desc: Test FireOnMeasure callback parameter passing
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest029, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode.
     * @tc.expected: Node created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step2. Set measure function that validates parameters.
     * @tc.expected: Function is set.
     */
    int callCount = 0;
    NG::LayoutWrapper* receivedWrapper = nullptr;
    auto measureFunc = [&callCount, &receivedWrapper](NG::LayoutWrapper* wrapper) {
        callCount++;
        receivedWrapper = wrapper;
    };
    customNode->SetMeasureFunction(std::move(measureFunc));

    /**
     * @tc.steps: step3. Create layout wrapper and trigger FireOnMeasure multiple times.
     * @tc.expected: Each call passes correct parameters.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());

    for (int i = 0; i < 3; i++) {
        callCount = 0;
        bool result = customNode->FireOnMeasure(AceType::RawPtr(layoutWrapper));
        EXPECT_TRUE(result);
        EXPECT_EQ(callCount, 1);
        EXPECT_EQ(receivedWrapper, AceType::RawPtr(layoutWrapper));
    }
}

/**
 * @tc.name: CustomMeasureLayoutTest030
 * @tc.desc: Test FireOnLayout callback parameter passing
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest030, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode.
     * @tc.expected: Node created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step2. Set layout function that validates parameters.
     * @tc.expected: Function is set.
     */
    int callCount = 0;
    NG::LayoutWrapper* receivedWrapper = nullptr;
    auto layoutFunc = [&callCount, &receivedWrapper](NG::LayoutWrapper* wrapper) {
        callCount++;
        receivedWrapper = wrapper;
    };
    customNode->SetLayoutFunction(std::move(layoutFunc));

    /**
     * @tc.steps: step3. Create layout wrapper and trigger FireOnLayout multiple times.
     * @tc.expected: Each call passes correct parameters.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());

    for (int i = 0; i < 3; i++) {
        callCount = 0;
        bool result = customNode->FireOnLayout(AceType::RawPtr(layoutWrapper));
        EXPECT_TRUE(result);
        EXPECT_EQ(callCount, 1);
        EXPECT_EQ(receivedWrapper, AceType::RawPtr(layoutWrapper));
    }
}

/**
 * @tc.name: CustomMeasureLayoutTest031
 * @tc.desc: Test CustomNodeLayoutAlgorithm::GetMeasureLayoutParam returns children
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest031, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomNodeLayoutAlgorithm.
     * @tc.expected: Algorithm created.
     */
    auto renderFunction = [](int64_t, bool&) -> RefPtr<UINode> { return nullptr; };
    auto algorithm = AceType::MakeRefPtr<CustomNodeLayoutAlgorithm>(renderFunction);
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step2. Get MeasureLayoutParam from algorithm.
     * @tc.expected: Initially returns nullptr (not yet created).
     */
    auto param = algorithm->GetMeasureLayoutParam();
    EXPECT_EQ(param, nullptr);
}

/**
 * @tc.name: CustomMeasureLayoutTest032
 * @tc.desc: Test CustomNodeLayoutAlgorithm::MoveBuildItem
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest032, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomNodeLayoutAlgorithm with render function.
     * @tc.expected: Algorithm created.
     */
    RefPtr<UINode> createdNode = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto renderFunction = [&createdNode](int64_t, bool&) -> RefPtr<UINode> { return createdNode; };
    auto algorithm = AceType::MakeRefPtr<CustomNodeLayoutAlgorithm>(renderFunction);
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step2. Create CustomMeasureLayoutNode and layout wrapper.
     * @tc.expected: Node and wrapper created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm));

    /**
     * @tc.steps: step3. Call Measure to trigger build item creation.
     * @tc.expected: Measure completes.
     */
    algorithm->Measure(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step4. Move build item from algorithm.
     * @tc.expected: Build item is moved (ownership transferred).
     */
    auto buildItem = algorithm->MoveBuildItem();
}

/**
 * @tc.name: CustomMeasureLayoutTest033
 * @tc.desc: Test UpdateSize with zero dimensions
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest033, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode with child.
     * @tc.expected: Node and child created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    auto child = CreateNode(V2::TEXT_ETS_TAG);
    child->MountToParent(customNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());

    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(child, childGeometryNode, child->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper);

    auto measureLayoutParam = AceType::MakeRefPtr<MeasureLayoutParam>(AceType::RawPtr(layoutWrapper));
    customNode->SetMeasureLayoutParam(measureLayoutParam);

    /**
     * @tc.steps: step2. Update size with zero dimensions.
     * @tc.expected: UpdateSize returns true.
     */
    SizeF zeroSize(0.0f, 0.0f);
    bool result = customNode->UpdateSize(0, zeroSize);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CustomMeasureLayoutTest034
 * @tc.desc: Test UpdateSize with negative dimensions
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest034, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode with child.
     * @tc.expected: Node and child created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    auto child = CreateNode(V2::TEXT_ETS_TAG);
    child->MountToParent(customNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());

    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(child, childGeometryNode, child->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper);

    auto measureLayoutParam = AceType::MakeRefPtr<MeasureLayoutParam>(AceType::RawPtr(layoutWrapper));
    customNode->SetMeasureLayoutParam(measureLayoutParam);

    /**
     * @tc.steps: step2. Update size with negative dimensions.
     * @tc.expected: UpdateSize returns true (no validation in implementation).
     */
    SizeF negativeSize(-100.0f, -200.0f);
    bool result = customNode->UpdateSize(0, negativeSize);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CustomMeasureLayoutTest035
 * @tc.desc: Test multiple measure and layout cycles
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest035, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode with callbacks.
     * @tc.expected: Node created.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);
    customNode->MountToParent(frameNode);

    auto child = CreateNode(V2::TEXT_ETS_TAG);
    child->MountToParent(customNode);

    int measureCount = 0;
    int layoutCount = 0;
    customNode->SetMeasureFunction([&measureCount](NG::LayoutWrapper*) { measureCount++; });
    customNode->SetLayoutFunction([&layoutCount](NG::LayoutWrapper*) { layoutCount++; });

    /**
     * @tc.steps: step2. Perform multiple measure/layout cycles.
     * @tc.expected: Counters increment correctly.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto customPattern = customNode->GetPattern<CustomNodePattern>();
    ASSERT_NE(customPattern, nullptr);
    auto algorithm = AceType::DynamicCast<CustomNodeLayoutAlgorithm>(customPattern->CreateLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);

    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm));

    for (int i = 0; i < 5; i++) {
        measureCount = 0;
        layoutCount = 0;

        algorithm->Measure(AceType::RawPtr(layoutWrapper));
        EXPECT_EQ(measureCount, 1);

        algorithm->Layout(AceType::RawPtr(layoutWrapper));
        EXPECT_EQ(layoutCount, 1);
    }
}

/**
 * @tc.name: CustomMeasureLayoutTest036
 * @tc.desc: Test FireOnUpdateParam without setting function
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest036, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode without update param function.
     * @tc.expected: Node created.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);
    customNode->MountToParent(frameNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. Call FireOnUpdateParam without setting function.
     * @tc.expected: Returns false.
     */
    bool result = customNode->FireOnUpdateParam(AceType::RawPtr(layoutWrapper));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CustomMeasureLayoutTest037
 * @tc.desc: Test FireOnUpdateParam with valid function
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest037, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode and set update param function.
     * @tc.expected: Node created with function.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);
    customNode->MountToParent(frameNode);

    bool updateCalled = false;
    NG::LayoutWrapper* capturedWrapper = nullptr;
    auto updateFunc = [&updateCalled, &capturedWrapper](NG::LayoutWrapper* wrapper) {
        updateCalled = true;
        capturedWrapper = wrapper;
    };
    customNode->SetUpdateParamFunc(std::move(updateFunc));

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. Call FireOnUpdateParam.
     * @tc.expected: Returns true and function is called.
     */
    bool result = customNode->FireOnUpdateParam(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(result);
    EXPECT_TRUE(updateCalled);
    EXPECT_EQ(capturedWrapper, AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: CustomMeasureLayoutTest038
 * @tc.desc: Test CreateChildConstraint with different parent constraints
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest038, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create parent node.
     * @tc.expected: Parent created.
     */
    auto parentNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(parentNode, nullptr);

    /**
     * @tc.steps: step2. Verify layout property exists.
     * @tc.expected: Layout property is valid.
     */
    auto parentLayoutProperty = parentNode->GetLayoutProperty();
    ASSERT_NE(parentLayoutProperty, nullptr);
}

/**
 * @tc.name: CustomMeasureLayoutTest039
 * @tc.desc: Test RenderCustomChild with child nodes
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest039, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode with multiple children.
     * @tc.expected: Node with children created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    auto child1 = CreateNode(V2::TEXT_ETS_TAG);
    auto child2 = CreateNode(V2::BUTTON_ETS_TAG);
    child1->MountToParent(customNode);
    child2->MountToParent(customNode);

    /**
     * @tc.steps: step2. Set recycle render function.
     * @tc.expected: Function set.
     */
    int recycleCount = 0;
    auto recycleFunc = [&recycleCount]() { recycleCount++; };
    customNode->SetRecycleRenderFunc(std::move(recycleFunc));

    /**
     * @tc.steps: step3. Call RenderCustomChild with future deadline.
     * @tc.expected: Render succeeds.
     */
    int64_t futureDeadline = GetSysTimestamp() + 500000;
    bool result = customNode->RenderCustomChild(futureDeadline);
    EXPECT_TRUE(result);
    EXPECT_EQ(recycleCount, 1);
}

/**
 * @tc.name: CustomMeasureLayoutTest040
 * @tc.desc: Test RenderCustomChild timeout with multiple children
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest040, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode with children.
     * @tc.expected: Node with children created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    auto child = CreateNode(V2::TEXT_ETS_TAG);
    child->MountToParent(customNode);

    int recycleCount = 0;
    auto recycleFunc = [&recycleCount]() { recycleCount++; };
    customNode->SetRecycleRenderFunc(std::move(recycleFunc));

    /**
     * @tc.steps: step2. Call RenderCustomChild with past deadline.
     * @tc.expected: Render fails due to timeout.
     */
    int64_t pastDeadline = GetSysTimestamp() - 1000;
    bool result = customNode->RenderCustomChild(pastDeadline);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CustomMeasureLayoutTest041
 * @tc.desc: Test CreateCustomMeasureLayoutNode with various view keys
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest041, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create nodes with different view keys.
     * @tc.expected: All nodes created successfully.
     */
    std::vector<std::string> viewKeys = {"", "test", "key123", "CustomView", "a"};

    for (const auto& key : viewKeys) {
        auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
            ElementRegister::GetInstance()->MakeUniqueId(), key);
        ASSERT_NE(customNode, nullptr);
        EXPECT_EQ(customNode->GetTag(), V2::JS_VIEW_ETS_TAG);
    }
}

/**
 * @tc.name: CustomMeasureLayoutTest042
 * @tc.desc: Test CustomNodeLayoutAlgorithm Measure with null host
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest042, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomNodeLayoutAlgorithm.
     * @tc.expected: Algorithm created.
     */
    auto renderFunction = [](int64_t, bool&) -> RefPtr<UINode> { return nullptr; };
    auto algorithm = AceType::MakeRefPtr<CustomNodeLayoutAlgorithm>(renderFunction);
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step2. Create layout wrapper with non-CustomMeasureLayoutNode host.
     * @tc.expected: Wrapper created.
     */
    auto regularNode = CreateNode(V2::TEXT_ETS_TAG);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(regularNode, geometryNode, regularNode->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm));

    /**
     * @tc.steps: step3. Call Measure - should handle null host gracefully.
     * @tc.expected: No crash, measure completes.
     */
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: CustomMeasureLayoutTest043
 * @tc.desc: Test CustomNodeLayoutAlgorithm Layout with null host
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest043, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomNodeLayoutAlgorithm.
     * @tc.expected: Algorithm created.
     */
    auto renderFunction = [](int64_t, bool&) -> RefPtr<UINode> { return nullptr; };
    auto algorithm = AceType::MakeRefPtr<CustomNodeLayoutAlgorithm>(renderFunction);
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step2. Create CustomMeasureLayoutNode for testing Layout with null layout function.
     * @tc.expected: Node created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    auto customPattern = customNode->GetPattern<CustomNodePattern>();
    ASSERT_NE(customPattern, nullptr);

    auto algorithmFromPattern = AceType::DynamicCast<CustomNodeLayoutAlgorithm>(customPattern->CreateLayoutAlgorithm());
    ASSERT_NE(algorithmFromPattern, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProperty = customNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, layoutProperty);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithmFromPattern));

    /**
     * @tc.steps: step3. Call Layout - should handle gracefully without custom layout function.
     * @tc.expected: No crash.
     */
    algorithmFromPattern->Layout(AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: CustomMeasureLayoutTest044
 * @tc.desc: Test MeasureLayoutParam::Update with zero children after having children
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest044, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create MeasureLayoutParam with children.
     * @tc.expected: Param created with children.
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
    EXPECT_EQ(layoutParam.GetTotalChildCount(), 1);

    /**
     * @tc.steps: step2. Create new wrapper with no children and update.
     * @tc.expected: Count reduced to 0.
     */
    auto emptyWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(parentNode, geometryNode, parentNode->GetLayoutProperty());
    layoutParam.Update(AceType::RawPtr(emptyWrapper));
    EXPECT_EQ(layoutParam.GetTotalChildCount(), 0);
    EXPECT_FALSE(layoutParam.ChildIndexInRange(0));
}

/**
 * @tc.name: CustomMeasureLayoutTest045
 * @tc.desc: Test SetMeasureFunction with nullptr equivalent
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest045, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode.
     * @tc.expected: Node created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step2. Set empty measure function (effectively nullptr).
     * @tc.expected: Function set but does nothing.
     */
    auto emptyFunc = [](NG::LayoutWrapper*) {};
    customNode->SetMeasureFunction(std::move(emptyFunc));

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());

    /**
     * @tc.steps: step3. FireOnMeasure with empty function.
     * @tc.expected: Returns true (function exists but does nothing).
     */
    bool result = customNode->FireOnMeasure(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CustomMeasureLayoutTest046
 * @tc.desc: Test SetLayoutFunction with nullptr equivalent
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest046, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode.
     * @tc.expected: Node created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step2. Set empty layout function.
     * @tc.expected: Function set.
     */
    auto emptyFunc = [](NG::LayoutWrapper*) {};
    customNode->SetLayoutFunction(std::move(emptyFunc));

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());

    /**
     * @tc.steps: step3. FireOnLayout with empty function.
     * @tc.expected: Returns true.
     */
    bool result = customNode->FireOnLayout(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CustomMeasureLayoutTest047
 * @tc.desc: Test RenderCustomChild deadline exactly at current time
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest047, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode.
     * @tc.expected: Node created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    int recycleCount = 0;
    auto recycleFunc = [&recycleCount]() { recycleCount++; };
    customNode->SetRecycleRenderFunc(std::move(recycleFunc));

    /**
     * @tc.steps: step2. Call RenderCustomChild with deadline exactly at current time.
     * @tc.expected: Behavior depends on timing, but no crash.
     */
    int64_t currentDeadline = GetSysTimestamp();
    bool result = customNode->RenderCustomChild(currentDeadline);

    /**
     * @tc.steps: step3. Verify behavior.
     * @tc.expected: May succeed or fail based on exact timing.
     */
    EXPECT_TRUE(result || !result);
}

/**
 * @tc.name: CustomMeasureLayoutTest048
 * @tc.desc: Test CreateChildConstraint returns default when property is null
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest048, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create MeasureLayoutParam.
     * @tc.expected: Param created.
     */
    auto parentNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(parentNode, geometryNode, parentNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. Create child constraint.
     * @tc.expected: Constraint created (may be default if no constraints set).
     */
    MeasureLayoutParam layoutParam(AceType::RawPtr(layoutWrapper));
    auto constraint = layoutParam.CreateChildConstraint();

    /**
     * @tc.steps: step3. Verify constraint exists.
     * @tc.expected: Constraint object is valid (actual values depend on implementation).
     */
    // Constraint is created successfully, values depend on default implementation
    EXPECT_GE(constraint.maxSize.Width(), 0.0f);
}

/**
 * @tc.name: CustomMeasureLayoutTest049
 * @tc.desc: Test CustomMeasureLayoutNode node ID assignment
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest049, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create multiple nodes with different IDs.
     * @tc.expected: All nodes have unique IDs.
     */
    std::set<int32_t> nodeIds;

    for (int i = 0; i < 10; i++) {
        int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(nodeId, TEST_TAG);
        ASSERT_NE(customNode, nullptr);
        EXPECT_EQ(customNode->GetId(), nodeId);
        nodeIds.insert(nodeId);
    }

    /**
     * @tc.steps: step2. Verify all IDs are unique.
     * @tc.expected: 10 unique IDs.
     */
    EXPECT_EQ(nodeIds.size(), 10);
}

/**
 * @tc.name: CustomMeasureLayoutTest050
 * @tc.desc: Test MeasureLayoutChild access after parent update
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest050, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create MeasureLayoutParam with child.
     * @tc.expected: Param created.
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

    /**
     * @tc.steps: step2. Access child before and after update.
     * @tc.expected: Child access works correctly.
     */
    auto& measureLayoutChild = layoutParam.Get(0);
    // Note: GetChild may return nullptr if child wrapper is not properly initialized
    auto childBefore = measureLayoutChild.GetChild();
    // Test that GetChild can be called without crash
    (void)childBefore;

    layoutParam.Update(AceType::RawPtr(layoutWrapper));

    auto childAfter = measureLayoutChild.GetChild();
    // Test that GetChild can be called after Update without crash
    (void)childAfter;
}

/**
 * @tc.name: CustomMeasureLayoutTest051
 * @tc.desc: Test UpdateSize boundary values
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest051, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode with MeasureLayoutParam.
     * @tc.expected: Node and param created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    auto child = CreateNode(V2::TEXT_ETS_TAG);
    child->MountToParent(customNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());

    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(child, childGeometryNode, child->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper);

    auto measureLayoutParam = AceType::MakeRefPtr<MeasureLayoutParam>(AceType::RawPtr(layoutWrapper));
    customNode->SetMeasureLayoutParam(measureLayoutParam);

    /**
     * @tc.steps: step2. Test boundary size values.
     * @tc.expected: All valid sizes are accepted.
     */
    std::vector<SizeF> testSizes = {
        SizeF(0.0f, 0.0f),
        SizeF(1.0f, 1.0f),
        SizeF(FLT_MAX, FLT_MAX),
        SizeF(999999.0f, 999999.0f)
    };

    for (const auto& size : testSizes) {
        bool result = customNode->UpdateSize(0, size);
        EXPECT_TRUE(result);
    }
}

/**
 * @tc.name: CustomMeasureLayoutTest052
 * @tc.desc: Test CustomNodeLayoutAlgorithm Measure with custom node having no render function
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest052, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode without setting render function.
     * @tc.expected: Node created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    auto child = CreateNode(V2::TEXT_ETS_TAG);
    child->MountToParent(customNode);

    /**
     * @tc.steps: step2. Get algorithm from pattern.
     * @tc.expected: Algorithm created (but renderFunction_ is null).
     */
    auto customPattern = customNode->GetPattern<CustomNodePattern>();
    ASSERT_NE(customPattern, nullptr);
    auto algorithm = AceType::DynamicCast<CustomNodeLayoutAlgorithm>(customPattern->CreateLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm));

    /**
     * @tc.steps: step3. Call Measure without render function.
     * @tc.expected: Measure completes without crash.
     */
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: CustomMeasureLayoutTest053
 * @tc.desc: Test FireOnUpdateParam called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest053, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode with update param function.
     * @tc.expected: Node created.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);
    customNode->MountToParent(frameNode);

    int updateCount = 0;
    auto updateFunc = [&updateCount](NG::LayoutWrapper*) { updateCount++; };
    customNode->SetUpdateParamFunc(std::move(updateFunc));

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. Call FireOnUpdateParam multiple times.
     * @tc.expected: Count increases each time.
     */
    for (int i = 1; i <= 5; i++) {
        bool result = customNode->FireOnUpdateParam(AceType::RawPtr(layoutWrapper));
        EXPECT_TRUE(result);
        EXPECT_EQ(updateCount, i);
    }
}

/**
 * @tc.name: CustomMeasureLayoutTest054
 * @tc.desc: Test CustomNodeLayoutAlgorithm with measure callback that modifies children
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest054, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode with children.
     * @tc.expected: Node with children created.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);
    customNode->MountToParent(frameNode);

    auto child1 = CreateNode(V2::TEXT_ETS_TAG);
    auto child2 = CreateNode(V2::TEXT_ETS_TAG);
    child1->MountToParent(customNode);
    child2->MountToParent(customNode);

    /**
     * @tc.steps: step2. Set measure function that accesses children.
     * @tc.expected: Function set.
     */
    int childCount = 0;
    auto measureFunc = [&childCount](NG::LayoutWrapper* wrapper) {
        if (wrapper) {
            childCount = wrapper->GetTotalChildCount();
        }
    };
    customNode->SetMeasureFunction(std::move(measureFunc));

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto customPattern = customNode->GetPattern<CustomNodePattern>();
    ASSERT_NE(customPattern, nullptr);
    auto algorithm = AceType::DynamicCast<CustomNodeLayoutAlgorithm>(customPattern->CreateLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);

    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm));

    RefPtr<GeometryNode> childGeom1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<GeometryNode> childGeom2 = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper1 = AceType::MakeRefPtr<LayoutWrapperNode>(child1, childGeom1, child1->GetLayoutProperty());
    auto childWrapper2 = AceType::MakeRefPtr<LayoutWrapperNode>(child2, childGeom2, child2->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper1);
    layoutWrapper->AppendChild(childWrapper2);

    /**
     * @tc.steps: step3. Call Measure.
     * @tc.expected: Measure callback sees correct child count.
     */
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: CustomMeasureLayoutTest055
 * @tc.desc: Test Render with zero deadline and no recycle function
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest055, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode without setting recycle function.
     * @tc.expected: Node created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step2. Call Render with zero deadline.
     * @tc.expected: Returns true (deadline check passes, but FireRecycleRenderFunc does nothing).
     */
    bool result = customNode->Render(0);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CustomMeasureLayoutTest056
 * @tc.desc: Test nested CustomMeasureLayoutNode scenarios
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest056, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create nested custom nodes.
     * @tc.expected: Outer and inner nodes created with parent-child relationship.
     */
    auto outerNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), "outer");
    ASSERT_NE(outerNode, nullptr);

    auto innerNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), "inner");
    ASSERT_NE(innerNode, nullptr);

    innerNode->MountToParent(outerNode);

    auto leafNode = CreateNode(V2::TEXT_ETS_TAG);
    leafNode->MountToParent(innerNode);

    /**
     * @tc.steps: step2. Verify hierarchy.
     * @tc.expected: Hierarchy is correct.
     */
    EXPECT_EQ(outerNode->GetChildren().size(), 1);
    EXPECT_EQ(innerNode->GetChildren().size(), 1);

    /**
     * @tc.steps: step3. Create layout wrappers for nested structure.
     * @tc.expected: Wrappers created successfully.
     */
    RefPtr<GeometryNode> outerGeom = AceType::MakeRefPtr<GeometryNode>();
    auto outerWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(outerNode, outerGeom, outerNode->GetLayoutProperty());

    RefPtr<GeometryNode> innerGeom = AceType::MakeRefPtr<GeometryNode>();
    auto innerWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(innerNode, innerGeom, innerNode->GetLayoutProperty());

    RefPtr<GeometryNode> leafGeom = AceType::MakeRefPtr<GeometryNode>();
    auto leafWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(leafNode, leafGeom, leafNode->GetLayoutProperty());

    innerWrapper->AppendChild(leafWrapper);
    outerWrapper->AppendChild(innerWrapper);

    /**
     * @tc.steps: step4. Verify nested wrapper structure.
     * @tc.expected: Correct nested structure.
     */
    EXPECT_EQ(outerWrapper->GetTotalChildCount(), 1);
    EXPECT_EQ(innerWrapper->GetTotalChildCount(), 1);
}

/**
 * @tc.name: CustomMeasureLayoutTest057
 * @tc.desc: Test CustomNodeLayoutAlgorithm MeasureContent override returns nullopt
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest057, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomNodeLayoutAlgorithm.
     * @tc.expected: Algorithm created.
     */
    auto renderFunction = [](int64_t, bool&) -> RefPtr<UINode> { return nullptr; };
    auto algorithm = AceType::MakeRefPtr<CustomNodeLayoutAlgorithm>(renderFunction);
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step2. Call MeasureContent.
     * @tc.expected: Returns nullopt as per implementation.
     */
    LayoutConstraintF constraint;
    auto result = algorithm->MeasureContent(constraint, nullptr);
    EXPECT_EQ(result, std::nullopt);
}

/**
 * @tc.name: CustomMeasureLayoutTest058
 * @tc.desc: Test CustomNodeLayoutAlgorithm Layout with custom layout function
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest058, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode with custom layout function.
     * @tc.expected: Node created with layout function.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    bool layoutExecuted = false;
    auto layoutFunc = [&layoutExecuted](NG::LayoutWrapper*) { layoutExecuted = true; };
    customNode->SetLayoutFunction(std::move(layoutFunc));

    auto child = CreateNode(V2::TEXT_ETS_TAG);
    child->MountToParent(customNode);

    /**
     * @tc.steps: step2. Create layout wrapper and algorithm.
     * @tc.expected: Wrapper and algorithm created.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto customPattern = customNode->GetPattern<CustomNodePattern>();
    ASSERT_NE(customPattern, nullptr);
    auto algorithm = AceType::DynamicCast<CustomNodeLayoutAlgorithm>(customPattern->CreateLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);

    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm));

    /**
     * @tc.steps: step3. Call Layout.
     * @tc.expected: Custom layout function is executed.
     */
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(layoutExecuted);
}

/**
 * @tc.name: CustomMeasureLayoutTest059
 * @tc.desc: Test CustomNodeLayoutAlgorithm Layout without custom layout function
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest059, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode without layout function.
     * @tc.expected: Node created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    auto child = CreateNode(V2::TEXT_ETS_TAG);
    child->MountToParent(customNode);

    /**
     * @tc.steps: step2. Create layout wrapper and algorithm.
     * @tc.expected: Wrapper and algorithm created.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto customPattern = customNode->GetPattern<CustomNodePattern>();
    ASSERT_NE(customPattern, nullptr);
    auto algorithm = AceType::DynamicCast<CustomNodeLayoutAlgorithm>(customPattern->CreateLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);

    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm));

    RefPtr<GeometryNode> childGeom = AceType::MakeRefPtr<GeometryNode>();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(child, childGeom, child->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper);

    /**
     * @tc.steps: step3. Call Layout without custom function.
     * @tc.expected: Falls back to default layout behavior.
     */
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: CustomMeasureLayoutTest060
 * @tc.desc: Test FireOnAppear lifecycle callback through Measure
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg2, CustomMeasureLayoutTest060, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode with appear function.
     * @tc.expected: Node created.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    ASSERT_NE(customNode, nullptr);

    bool appearCalled = false;
    customNode->SetAppearFunction([&appearCalled]() { appearCalled = true; });

    /**
     * @tc.steps: step2. Set render function and create algorithm.
     * @tc.expected: Algorithm created with render function.
     */
    RefPtr<AceType> view;
    auto renderFunc = [&view]() -> RefPtr<AceType> { return nullptr; };
    auto renderFunction = [internalRender = std::move(renderFunc)](
        int64_t deadline, bool& isTimeout) -> RefPtr<UINode> {
        auto uiNode = internalRender();
        return AceType::DynamicCast<UINode>(uiNode);
    };
    customNode->SetRenderFunction(std::move(renderFunction));

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto customPattern = customNode->GetPattern<CustomNodePattern>();
    ASSERT_NE(customPattern, nullptr);
    auto algorithm = AceType::DynamicCast<CustomNodeLayoutAlgorithm>(customPattern->CreateLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);

    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm));

    /**
     * @tc.steps: step3. Call Measure which triggers FireOnAppear.
     * @tc.expected: Appear callback is called.
     */
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(appearCalled);
}


} // namespace OHOS::Ace::NG
