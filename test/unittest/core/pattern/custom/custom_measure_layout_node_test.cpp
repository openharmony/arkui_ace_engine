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

/**
 * @tc.name: CustomMeasureLayoutTest008
 * @tc.desc: Test FireOnUpdateParam callback execution.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest008, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TabContent and push it to view stack processor.
     * @tc.expected: TabContent node created.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);

    /**
     * @tc.steps: step2. Create CustomMeasureLayoutNode and mount to parent.
     * @tc.expected: CustomMeasureLayoutNode created and mounted.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);
    customNode->MountToParent(frameNode);

    /**
     * @tc.steps: step3. Create parent LayoutWrapperNode.
     * @tc.expected: LayoutWrapperNode created.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    EXPECT_FALSE(parentLayoutWrapper == nullptr);

    /**
     * @tc.steps: step4. Set updateParamFunc and verify FireOnUpdateParam.
     * @tc.expected: FireOnUpdateParam returns true when function is set, false otherwise.
     */
    // 未设置时返回 false
    auto fireResult = customNode->FireOnUpdateParam(AceType::RawPtr(parentLayoutWrapper));
    EXPECT_FALSE(fireResult);

    // 设置后返回 true
    NG::LayoutWrapper* capturedWrapper = nullptr;
    auto updateParamFunc = [&capturedWrapper](
                                NG::LayoutWrapper* layoutWrapper = nullptr) {
        capturedWrapper = layoutWrapper;
    };
    customNode->SetUpdateParamFunc(std::move(updateParamFunc));

    fireResult = customNode->FireOnUpdateParam(AceType::RawPtr(parentLayoutWrapper));
    EXPECT_TRUE(fireResult);
    EXPECT_EQ(capturedWrapper, AceType::RawPtr(parentLayoutWrapper));
}

/**
 * @tc.name: CustomMeasureLayoutTest009
 * @tc.desc: Test UpdateSize method - valid index scenario
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest009, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode with MeasureLayoutParam.
     * @tc.expected: CustomMeasureLayoutNode created successfully.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step2. Create MeasureLayoutParam with one child.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    RefPtr<GeometryNode> childGeometry = AceType::MakeRefPtr<GeometryNode>();
    auto childNode = FrameNode::CreateFrameNode("child", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childNode, childGeometry, childNode->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper);

    auto measureLayoutParam = AceType::MakeRefPtr<MeasureLayoutParam>(AceType::RawPtr(layoutWrapper));
    customNode->SetMeasureLayoutParam(measureLayoutParam);

    /**
     * @tc.steps: step3. Call UpdateSize with valid index.
     * @tc.expected: UpdateSize returns true and size is updated.
     */
    SizeF testSize(100.0f, 200.0f);
    bool updateResult = customNode->UpdateSize(0, testSize);
    EXPECT_TRUE(updateResult);
}

/**
 * @tc.name: CustomMeasureLayoutTest010
 * @tc.desc: Test UpdateSize method - invalid index scenarios
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest010, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode with MeasureLayoutParam.
     * @tc.expected: CustomMeasureLayoutNode created successfully.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    RefPtr<GeometryNode> childGeometry = AceType::MakeRefPtr<GeometryNode>();
    auto childNode = FrameNode::CreateFrameNode("child", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childNode, childGeometry, childNode->GetLayoutProperty());
    layoutWrapper->AppendChild(childWrapper);

    auto measureLayoutParam = AceType::MakeRefPtr<MeasureLayoutParam>(AceType::RawPtr(layoutWrapper));
    customNode->SetMeasureLayoutParam(measureLayoutParam);

    /**
     * @tc.steps: step2. Call UpdateSize with negative index.
     * @tc.expected: UpdateSize returns false.
     */
    SizeF testSize(100.0f, 200.0f);
    bool updateResult = customNode->UpdateSize(-1, testSize);
    EXPECT_FALSE(updateResult);

    /**
     * @tc.steps: step3. Call UpdateSize with index equal to child count.
     * @tc.expected: UpdateSize returns false (out of range).
     */
    updateResult = customNode->UpdateSize(1, testSize);
    EXPECT_FALSE(updateResult);
}

/**
 * @tc.name: CustomMeasureLayoutTest011
 * @tc.desc: Test UpdateSize method - no MeasureLayoutParam set
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest011, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode without MeasureLayoutParam.
     * @tc.expected: CustomMeasureLayoutNode created successfully.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step2. Call UpdateSize when MeasureLayoutParam is null.
     * @tc.expected: UpdateSize returns false (CHECK_NULL_RETURN false in implementation).
     */
    SizeF testSize(100.0f, 200.0f);
    bool updateResult = customNode->UpdateSize(0, testSize);
    EXPECT_FALSE(updateResult);

    updateResult = customNode->UpdateSize(1, testSize);
    EXPECT_FALSE(updateResult);
}

/**
 * @tc.name: CustomMeasureLayoutTest012
 * @tc.desc: Test GetMeasureLayoutParam and SetMeasureLayoutParam
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest012, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode.
     * @tc.expected: CustomMeasureLayoutNode created successfully.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step2. Check initial MeasureLayoutParam (should be null).
     */
    auto initialParam = customNode->GetMeasureLayoutParam();
    EXPECT_EQ(initialParam, nullptr);

    /**
     * @tc.steps: step3. Set MeasureLayoutParam and retrieve it.
     * @tc.expected: GetMeasureLayoutParam returns same RefPtr.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    auto measureLayoutParam = AceType::MakeRefPtr<MeasureLayoutParam>(AceType::RawPtr(layoutWrapper));
    customNode->SetMeasureLayoutParam(measureLayoutParam);

    auto retrievedParam = customNode->GetMeasureLayoutParam();
    EXPECT_NE(retrievedParam, nullptr);
    EXPECT_EQ(retrievedParam, measureLayoutParam);
}

/**
 * @tc.name: CustomMeasureLayoutTest013
 * @tc.desc: Test Render method timeout scenario
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest013, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode.
     * @tc.expected: CustomMeasureLayoutNode created successfully.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step2. Set recycle render function and call Render with past deadline.
     * @tc.expected: Render returns false, FireRecycleRenderFunc is NOT called.
     * Logic explanation:
     * - Render() checks: if (deadline > 0 && GetSysTimestamp() > deadline) return false
     * - When deadline is in the past, condition is true, so it returns false immediately
     * - FireRecycleRenderFunc() is inside a scope that only executes when Render() returns true
     * - Since we return false at timeout check, FireRecycleRenderFunc() is never called
     * Fix: Use larger time offset (1 second = 1000000 microseconds) to ensure
     *   the past deadline is truly in the past, avoiding timing precision issues
     */
    int recycleCallCount = 0;
    auto recycleRenderFunc = [&recycleCallCount]() { recycleCallCount++; };
    customNode->SetRecycleRenderFunc(std::move(recycleRenderFunc));

    int64_t pastDeadline = GetSysTimestamp() - 1000000; // 1 second in the past
    bool renderResult = customNode->Render(pastDeadline);
    EXPECT_FALSE(renderResult);
    EXPECT_EQ(recycleCallCount, 0);
}

/**
 * @tc.name: CustomMeasureLayoutTest014
 * @tc.desc: Test Render method with zero deadline (no timeout check)
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest014, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode.
     * @tc.expected: CustomMeasureLayoutNode created successfully.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step2. Set recycle render function and call Render with deadline=0.
     * @tc.expected: Render returns true, FireRecycleRenderFunc is called.
     * Logic explanation:
     * - Render() checks: if (deadline > 0 && GetSysTimestamp() > deadline) return false
     * - When deadline is 0, the first condition (deadline > 0) is false
     * - With && operator, the entire condition is false without evaluating second part
     * - So Render() proceeds to call FireRecycleRenderFunc()
     */
    int recycleCallCount = 0;
    auto recycleRenderFunc = [&recycleCallCount]() { recycleCallCount++; };
    customNode->SetRecycleRenderFunc(std::move(recycleRenderFunc));

    bool renderResult = customNode->Render(0);
    EXPECT_TRUE(renderResult);
    EXPECT_EQ(recycleCallCount, 1);
}

/**
 * @tc.name: CustomMeasureLayoutTest017
 * @tc.desc: Test FireOnUpdateParam with null LayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest017, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode and parent wrapper.
     * @tc.expected: CustomMeasureLayoutNode created successfully.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);
    customNode->MountToParent(frameNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. Set updateParamFunc and call FireOnUpdateParam with null.
     * @tc.expected: Function is called, receives null, returns true.
     * Logic: FireOnUpdateParam doesn't validate layoutWrapper, just passes it through
     */
    NG::LayoutWrapper* capturedWrapper = nullptr;
    bool updateCalled = false;
    auto updateParamFunc = [&updateCalled, &capturedWrapper](
        NG::LayoutWrapper* layoutWrapper) {
        updateCalled = true;
        capturedWrapper = layoutWrapper;
    };
    customNode->SetUpdateParamFunc(std::move(updateParamFunc));

    auto fireResult = customNode->FireOnUpdateParam(nullptr);
    EXPECT_TRUE(fireResult);
    EXPECT_TRUE(updateCalled);
    EXPECT_EQ(capturedWrapper, nullptr);
}

/**
 * @tc.name: CustomMeasureLayoutTest017
 * @tc.desc: Test FireOnUpdateParam with null LayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest017, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode and parent wrapper.
     * @tc.expected: CustomMeasureLayoutNode created successfully.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);
    customNode->MountToParent(frameNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. Set updateParamFunc and call FireOnUpdateParam with null.
     * @tc.expected: Function is called, receives null, returns true.
     * Logic: FireOnUpdateParam doesn't validate layoutWrapper, just passes it through
     */
    NG::LayoutWrapper* capturedWrapper = nullptr;
    bool updateCalled = false;
    auto updateParamFunc = [&updateCalled, &capturedWrapper](
        NG::LayoutWrapper* layoutWrapper) {
        updateCalled = true;
        capturedWrapper = layoutWrapper;
    };
    customNode->SetUpdateParamFunc(std::move(updateParamFunc));

    auto fireResult = customNode->FireOnUpdateParam(nullptr);
    EXPECT_TRUE(fireResult);
    EXPECT_TRUE(updateCalled);
    EXPECT_EQ(capturedWrapper, nullptr);
}

/**
 * @tc.name: CustomMeasureLayoutTest017
 * @tc.desc: Test FireOnLayout with null LayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest017, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode and parent wrapper.
     * @tc.expected: CustomMeasureLayoutNode created successfully.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);
    customNode->MountToParent(frameNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. Set layout function and call with null wrapper.
     * @tc.expected: Function is called, receives null, returns true.
     * Logic: FireOnLayout doesn't validate layoutWrapper, just passes it through
     */
    bool layoutCalled = false;
    NG::LayoutWrapper* receivedWrapper = nullptr;
    auto layoutFunc = [&layoutCalled, &receivedWrapper](
        NG::LayoutWrapper* layoutWrapper) {
        layoutCalled = true;
        receivedWrapper = layoutWrapper;
    };
    customNode->SetLayoutFunction(std::move(layoutFunc));

    auto fireResult = customNode->FireOnLayout(nullptr);
    EXPECT_TRUE(fireResult);
    EXPECT_TRUE(layoutCalled);
    EXPECT_EQ(receivedWrapper, nullptr);
}

/**
 * @tc.name: CustomMeasureLayoutTest018
 * @tc.desc: Test FireOnUpdateParam with null LayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest018, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode and parent wrapper.
     * @tc.expected: CustomMeasureLayoutNode created successfully.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);
    customNode->MountToParent(frameNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. Set updateParamFunc and call FireOnUpdateParam with null.
     * @tc.expected: Function is called, receives null, returns true.
     * Logic: FireOnUpdateParam doesn't validate layoutWrapper, just passes it through
     */
    NG::LayoutWrapper* capturedWrapper = nullptr;
    bool updateCalled = false;
    auto updateParamFunc = [&updateCalled, &capturedWrapper](
        NG::LayoutWrapper* layoutWrapper) {
        updateCalled = true;
        capturedWrapper = layoutWrapper;
    };
    customNode->SetUpdateParamFunc(std::move(updateParamFunc));

    auto fireResult = customNode->FireOnUpdateParam(nullptr);
    EXPECT_TRUE(fireResult);
    EXPECT_TRUE(updateCalled);
    EXPECT_EQ(capturedWrapper, nullptr);
}

/**
 * @tc.name: CustomMeasureLayoutTest019
 * @tc.desc: Test FireOnMeasure/FireOnLayout without setting function
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest019, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode and parent wrapper.
     * @tc.expected: CustomMeasureLayoutNode created successfully.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);
    customNode->MountToParent(frameNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. Call FireOnMeasure without setting measure function.
     * @tc.expected: Returns false (function_ is null).
     */
    auto fireResult = customNode->FireOnMeasure(AceType::RawPtr(parentLayoutWrapper));
    EXPECT_FALSE(fireResult);

    /**
     * @tc.steps: step3. Call FireOnLayout without setting layout function.
     * @tc.expected: Returns false (function_ is null).
     */
    fireResult = customNode->FireOnLayout(AceType::RawPtr(parentLayoutWrapper));
    EXPECT_FALSE(fireResult);
}

/**
 * @tc.name: CustomMeasureLayoutTest020
 * @tc.desc: Test RenderCustomChild timeout behavior
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest020, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode with child.
     * @tc.expected: CustomMeasureLayoutNode created successfully.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);
    customNode->MountToParent(frameNode);

    auto textFrameNode = CreateNode(V2::TEXT_ETS_TAG);
    textFrameNode->MountToParent(customNode);

    /**
     * @tc.steps: step2. Call RenderCustomChild with immediate timeout.
     * @tc.expected: Returns false due to timeout.
     * Logic: RenderCustomChild first checks if (GetSysTimestamp() > deadline)
     */
    int64_t immediateDeadline = GetSysTimestamp() - 1000;
    bool result = customNode->RenderCustomChild(immediateDeadline);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CustomMeasureLayoutTest021
 * @tc.desc: Test RenderCustomChild calls Render then FrameNode::RenderCustomChild
 * @tc.type: FUNC
 */
HWTEST_F(CustomMeasureLayoutTestNg, CustomMeasureLayoutTest021, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode with child.
     * @tc.expected: CustomMeasureLayoutNode created successfully.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);
    customNode->MountToParent(frameNode);

    auto textFrameNode = CreateNode(V2::TEXT_ETS_TAG);
    textFrameNode->MountToParent(customNode);

    /**
     * @tc.steps: step2. Set recycle render function and call RenderCustomChild.
     * @tc.expected: Returns true, FireRecycleRenderFunc is called.
     * Logic: RenderCustomChild calls Render() which calls FireRecycleRenderFunc()
     * Fix: Use 1 second (1000000 microseconds) instead of 1ms (1000)
     *   to avoid timing precision issues with small time offsets
     */
    int recycleCallCount = 0;
    auto recycleRenderFunc = [&recycleCallCount]() { recycleCallCount++; };
    customNode->SetRecycleRenderFunc(std::move(recycleRenderFunc));

    int64_t futureDeadline = GetSysTimestamp() + 1000000; // 1 second in future
    bool result = customNode->RenderCustomChild(futureDeadline);
    EXPECT_TRUE(result);
    EXPECT_EQ(recycleCallCount, 1);
}

} // namespace OHOS::Ace::NG