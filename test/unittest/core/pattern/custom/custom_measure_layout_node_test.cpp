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

#include "gtest/gtest.h"
#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

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
constexpr int32_t CHILD_COUNT_0 = 0;
constexpr int32_t CHILD_COUNT_1 = 1;
} // namespace

class CustomMeasureLayoutTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> CreateNode(const std::string& tag);
};

inline void CustomMeasureLayoutTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

inline void CustomMeasureLayoutTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

inline RefPtr<FrameNode> CustomMeasureLayoutTestNg::CreateNode(const std::string& tag)
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
 * @tc.name: CustomMeasureLayoutTest001
 * @tc.desc: Create CustomMeasureLayoutNode and test fireOnMeasure and fireOnLayout.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TabContent and push it to view stack processor.
     * @tc.expected: Make TabContent as CustomMeasureLayoutNode parent.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke CustomMeasureLayoutNode Create function.
     * @tc.expected: Create CustomMeasureLayoutNode.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    customNode->MountToParent(frameNode);

    auto textFrameNode = CreateNode(V2::TEXT_ETS_TAG);
    textFrameNode->MountToParent(customNode);

    /**
     * @tc.steps: step3. Create Parent LayoutWrapperNode.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto parentLayoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    /**
     * @tc.steps: step4. set measureFuncation and layoutFuncation and FireOnMeasure and FireOnLayout.
     * @tc.expected: FireOnMeasure and FireOnLayout return correct value.
     */
    RefPtr<AceType> view;
    auto renderFunc = [&view]() -> RefPtr<AceType> { return nullptr; };
    auto renderFunction =
        [internalRender = std::move(renderFunc)](int64_t deadline, bool& isTimeout) -> RefPtr<UINode> {
        auto uiNode = internalRender();
        return AceType::DynamicCast<UINode>(uiNode);
    };
    customNode->SetRenderFunction(std::move(renderFunction));

    RefPtr<GeometryNode> customGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto pattern = customNode->GetPattern<CustomNodePattern>();
    ASSERT_NE(pattern, nullptr);
    auto customLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(customLayoutAlgorithm, nullptr);
    auto customLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());

    EXPECT_FALSE(customLayoutWrapper == nullptr);
    customLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(customLayoutAlgorithm));
    parentLayoutWrapper.AppendChild(customLayoutWrapper);

    auto fireOnMeasure = customNode->FireOnMeasure(&parentLayoutWrapper);
    auto fireOnLayout = customNode->FireOnLayout(&parentLayoutWrapper);
    EXPECT_EQ(fireOnMeasure, false);
    EXPECT_EQ(fireOnLayout, false);

    NG::LayoutWrapper* testMeasureFun;
    NG::LayoutWrapper* testLayoutFunc;

    auto measureFuncation = [&testMeasureFun](
                                NG::LayoutWrapper* layoutWrapper = nullptr) { testMeasureFun = layoutWrapper; };
    auto layoutFuncation = [&testLayoutFunc](
                               NG::LayoutWrapper* layoutWrapper = nullptr) { testLayoutFunc = layoutWrapper; };
    customNode->SetMeasureFunction(std::move(measureFuncation));
    customNode->SetLayoutFunction(std::move(layoutFuncation));
    fireOnMeasure = customNode->FireOnMeasure(&parentLayoutWrapper);
    fireOnLayout = customNode->FireOnLayout(&parentLayoutWrapper);
    EXPECT_EQ(fireOnMeasure, true);
    EXPECT_EQ(fireOnLayout, true);
}

/**
 * @tc.name: CustomMeasureLayoutTest002
 * @tc.desc: RenderCustomChild
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Invoke CustomMeasureLayoutNode Create function.
     * @tc.expected: Create CustomMeasureLayoutNode.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    /**
     * @tc.steps: step2. Define timestamp deadline and n.
     * @tc.expected: Deadline And N.
     */
    int64_t n = 1000000000;
    int64_t deadline = GetSysTimestamp() + n;
    /**
     * @tc.steps: step3. When he is greater than the deadline, the assertion fails.
     * @tc.expected: GetSysTimestamp.
     */
    if (GetSysTimestamp() > deadline) {
        EXPECT_FALSE(false);
    }
    customNode->Render();
    /**
     * @tc.steps: step4. Invoke RenderCustomChild function.
     * @tc.expected: Render CustomChild.
     */
    customNode->RenderCustomChild(deadline);
    bool test = customNode->RenderCustomChild(deadline);
    EXPECT_EQ(test, true);
    EXPECT_TRUE(test);
    /**
     * @tc.steps: step5. Another branch returned successful.
     * @tc.expected: RenderCustomChild.
     */
    int64_t deadlines = 0;
    bool result = customNode->RenderCustomChild(deadlines);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CustomMeasureLayoutTest003
 * @tc.desc: Create CustomMeasureLayoutNode.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step2. call the function FireRecycleRenderFunc.
     */
    bool recycleRenderFuncFlag = true;
    auto recycleRenderFunc = [&recycleRenderFuncFlag]() { recycleRenderFuncFlag = !recycleRenderFuncFlag; };
    customNode->SetRecycleRenderFunc(std::move(recycleRenderFunc));
    customNode->FireRecycleRenderFunc();
    customNode.Reset();
    EXPECT_FALSE(recycleRenderFuncFlag);
}

/**
 * @tc.name: CustomMeasureLayoutTest004
 * @tc.desc: Create CustomMeasureLayoutNode.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest004, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step2. call the function FireRecycleRenderFunc.
     */
    int recycleRenderFuncFlag = 0;
    auto recycleRenderFunc = [&recycleRenderFuncFlag]() { recycleRenderFuncFlag++; };
    customNode->SetRecycleRenderFunc(std::move(recycleRenderFunc));
    customNode->FireRecycleRenderFunc();
    customNode->FireRecycleRenderFunc();
    customNode->FireRecycleRenderFunc();
    EXPECT_EQ(recycleRenderFuncFlag, 1);
}

/**
 * @tc.name: CustomMeasureLayoutTest005
 * @tc.desc: Create CustomMeasureLayoutNode and test measure and layout and renderFunction
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest005, TestSize.Level0)
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

    auto textFrameNode = CreateNode(V2::TEXT_ETS_TAG);
    textFrameNode->MountToParent(customNode);

    /**
     * @tc.steps: step3. Create Parent LayoutWrapperNode.
     */
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    EXPECT_FALSE(parentLayoutWrapper == nullptr);
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_0);
    /**
     * @tc.steps: step4. set renderFunction, add child to customNode and invoke Measure function.
     * @tc.expected: parentLayoutWrapper's childCount is one.
     */
    bool renderFunctionFlag = false;
    RefPtr<AceType> view;
    auto renderFunc = [&view]() -> RefPtr<AceType> { return nullptr; };
    auto renderFunction = [internalRender = std::move(renderFunc), &renderFunctionFlag](
                              int64_t deadline, bool& isTimeout) -> RefPtr<UINode> {
        auto uiNode = internalRender();
        renderFunctionFlag = true;
        return AceType::DynamicCast<UINode>(uiNode);
    };
    customNode->SetRenderFunction(std::move(renderFunction));

    RefPtr<GeometryNode> customGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto customPattern = customNode->GetPattern<CustomNodePattern>();
    ASSERT_NE(customPattern, nullptr);
    auto customLayoutAlgorithm = customPattern->CreateLayoutAlgorithm();
    ASSERT_NE(customLayoutAlgorithm, nullptr);
    auto customLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());
    EXPECT_FALSE(customLayoutWrapper == nullptr);
    customLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(customLayoutAlgorithm));
    parentLayoutWrapper->AppendChild(customLayoutWrapper);
    EXPECT_FALSE(renderFunctionFlag);

    layoutAlgorithm->Measure(AceType::RawPtr(parentLayoutWrapper));
    layoutAlgorithm->Layout(AceType::RawPtr(parentLayoutWrapper));
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_1);
    EXPECT_TRUE(renderFunctionFlag);
}

/**
 * @tc.name: CustomMeasureLayoutTest006
 * @tc.desc: Create CustomMeasureLayoutNode and test measure and layout renderRecycleFunc.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest006, TestSize.Level0)
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

    auto textFrameNode = CreateNode(V2::TEXT_ETS_TAG);
    textFrameNode->MountToParent(customNode);

    /**
     * @tc.steps: step3. Create Parent LayoutWrapperNode.
     */
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    EXPECT_FALSE(parentLayoutWrapper == nullptr);
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_0);
    /**
     * @tc.steps: step4. set renderFunction, add child to customNode and invoke Measure function.
     * @tc.expected: parentLayoutWrapper's childCount is one and recycleRender is executed once.
     */
    int renderFunctionFlag = 0;
    RefPtr<AceType> view;
    auto renderFunc = [&view]() -> RefPtr<AceType> {
        return AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    };
    auto renderFunction = [internalRender = std::move(renderFunc), &renderFunctionFlag](
                              int64_t deadline, bool& isTimeout) -> RefPtr<UINode> {
        auto uiNode = internalRender();
        renderFunctionFlag++;
        return AceType::DynamicCast<UINode>(uiNode);
    };
    customNode->SetRenderFunction(std::move(renderFunction));
    EXPECT_EQ(renderFunctionFlag, 0);

    int recycleRenderFuncFlag = 0;
    auto recycleRenderFunc = [&recycleRenderFuncFlag]() { recycleRenderFuncFlag++; };
    customNode->SetRecycleRenderFunc(std::move(recycleRenderFunc));
    EXPECT_EQ(recycleRenderFuncFlag, 0);

    RefPtr<GeometryNode> customGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto customPattern = customNode->GetPattern<CustomNodePattern>();
    ASSERT_NE(customPattern, nullptr);
    auto customLayoutAlgorithm = customPattern->CreateLayoutAlgorithm();
    ASSERT_NE(customLayoutAlgorithm, nullptr);
    auto customLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());
    EXPECT_FALSE(customLayoutWrapper == nullptr);
    customLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(customLayoutAlgorithm));
    parentLayoutWrapper->AppendChild(customLayoutWrapper);
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_1);
    EXPECT_EQ(renderFunctionFlag, 0);
    EXPECT_EQ(recycleRenderFuncFlag, 0);

    layoutAlgorithm->Measure(AceType::RawPtr(parentLayoutWrapper));
    layoutAlgorithm->Layout(AceType::RawPtr(parentLayoutWrapper));
    EXPECT_EQ(renderFunctionFlag, 1);
    EXPECT_EQ(recycleRenderFuncFlag, 1);
}

/**
 * @tc.name: CustomMeasureLayoutTest007
 * @tc.desc: Create CustomMeasureLayoutNode and test measure and layout renderRecycleFunc.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest007, TestSize.Level0)
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

    auto textFrameNode = CreateNode(V2::TEXT_ETS_TAG);
    textFrameNode->MountToParent(customNode);

    /**
     * @tc.steps: step3. Create Parent LayoutWrapperNode.
     */
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    EXPECT_FALSE(parentLayoutWrapper == nullptr);
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_0);
    /**
     * @tc.steps: step4. set renderFunction, add child to customNode and invoke Measure function.
     * @tc.expected: parentLayoutWrapper's childCount is one and recycleRender is executed once.
     */
    int renderFunctionFlag = 0;
    RefPtr<AceType> view;
    auto renderFunc = [&view]() -> RefPtr<AceType> {
        return AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    };
    auto renderFunction = [internalRender = std::move(renderFunc), &renderFunctionFlag](
                              int64_t deadline, bool& isTimeout) -> RefPtr<UINode> {
        auto uiNode = internalRender();
        renderFunctionFlag++;
        return AceType::DynamicCast<UINode>(uiNode);
    };
    customNode->SetRenderFunction(std::move(renderFunction));
    EXPECT_EQ(renderFunctionFlag, 0);

    int recycleRenderFuncFlag = 0;
    auto recycleRenderFunc = [&recycleRenderFuncFlag]() { recycleRenderFuncFlag++; };
    customNode->SetRecycleRenderFunc(std::move(recycleRenderFunc));
    EXPECT_EQ(recycleRenderFuncFlag, 0);

    RefPtr<GeometryNode> customGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto customPattern = customNode->GetPattern<CustomNodePattern>();
    ASSERT_NE(customPattern, nullptr);
    auto customLayoutAlgorithm = customPattern->CreateLayoutAlgorithm();
    ASSERT_NE(customLayoutAlgorithm, nullptr);
    auto customLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(customNode, geometryNode, customNode->GetLayoutProperty());
    EXPECT_FALSE(customLayoutWrapper == nullptr);
    customLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(customLayoutAlgorithm));
    parentLayoutWrapper->AppendChild(customLayoutWrapper);
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_1);
    EXPECT_EQ(renderFunctionFlag, 0);
    EXPECT_EQ(recycleRenderFuncFlag, 0);

    int64_t n = 1000000000;
    int64_t deadline = GetSysTimestamp() + n;
    bool result = frameNode->RenderCustomChild(deadline);
    EXPECT_TRUE(result);
    EXPECT_EQ(renderFunctionFlag, 0);
    EXPECT_EQ(recycleRenderFuncFlag, 1);

    layoutAlgorithm->Measure(AceType::RawPtr(parentLayoutWrapper));
    layoutAlgorithm->Layout(AceType::RawPtr(parentLayoutWrapper));
    EXPECT_EQ(renderFunctionFlag, 1);
    EXPECT_EQ(recycleRenderFuncFlag, 1);
}

} // namespace OHOS::Ace::NG