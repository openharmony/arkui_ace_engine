/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/custom/custom_node_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/custom/custom_title_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TEST_TAG("test");
constexpr int32_t CHILD_COUNT_0 = 0;
constexpr int32_t CHILD_COUNT_1 = 1;
} // namespace

class CustomTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> CreateNode(const std::string& tag);
};

void CustomTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "CustomTestNg SetUpTestCase";
    MockPipelineContext::SetUp();
}

void CustomTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "CustomTestNg TearDownTestCase";
    MockPipelineContext::TearDown();
}

void CustomTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void CustomTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> CustomTestNg::CreateNode(const std::string& tag)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, -1, pattern);
    pattern->AttachToFrameNode(frameNode);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    return frameNode;
}

/**
 * @tc.name: CustomTest001
 * @tc.desc: Create Custom node and parent is not tabContent.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text and push it to view stack processor.
     * @tc.expected: Make Text as CustomNode parent.
     */
    auto frameNode = CreateNode(V2::TEXT_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke CustomNode Create function.
     * @tc.expected: Create CustomNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step3. Create Parent LayoutWrapperNode.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    /**
     * @tc.steps: step4. Invoke Build and AdjustLayoutWrapperTree.
     * @tc.expected: parentLayoutWrapper's childCount is zero.
     */
    customNode->Build(nullptr);
    customNode->AdjustLayoutWrapperTree(parentLayoutWrapper, false, false);
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_0);

    RefPtr<AceType> view;
    auto renderFunc = [&view]() -> RefPtr<AceType> { return nullptr; };
    auto renderFunction = [internalRender = std::move(renderFunc)]() -> RefPtr<UINode> {
        auto uiNode = internalRender();
        return AceType::DynamicCast<UINode>(uiNode);
    };
    customNode->SetRenderFunction(std::move(renderFunction));
    customNode->Build(nullptr);
    customNode->AdjustLayoutWrapperTree(parentLayoutWrapper, false, false);
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_0);
}

/**
 * @tc.name: CustomTest002
 * @tc.desc: Create Custom node and parent is tabContent.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabContent and push it to view stack processor.
     * @tc.expected: Make TabContent as CustomNode parent.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke CustomNode Create function.
     * @tc.expected: Create CustomNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step3. Create Parent LayoutWrapperNode.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    /**
     * @tc.steps: step4. Invoke Build and AdjustLayoutWrapperTree.
     * @tc.expected: parentLayoutWrapper's childCount is zero.
     */
    customNode->Build(nullptr);
    customNode->AdjustLayoutWrapperTree(parentLayoutWrapper, false, false);
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_0);

    RefPtr<AceType> view;
    auto renderFunc = [&view]() -> RefPtr<AceType> { return nullptr; };
    auto renderFunction = [internalRender = std::move(renderFunc)]() -> RefPtr<UINode> {
        auto uiNode = internalRender();
        return AceType::DynamicCast<UINode>(uiNode);
    };
    customNode->SetRenderFunction(std::move(renderFunction));
    customNode->Build(nullptr);
    customNode->AdjustLayoutWrapperTree(parentLayoutWrapper, false, false);
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_0);
}

/**
 * @tc.name: CustomTest003
 * @tc.desc: Create CustomMeasureLayoutNode and test fireOnMeasure and fireOnLayout.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabContent and push it to view stack processor.
     * @tc.expected: Make TabContent as CustomNode parent.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke CustomNode Create function.
     * @tc.expected: Create CustomNode.
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
    auto renderFunction = [internalRender = std::move(renderFunc)]() -> RefPtr<UINode> {
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
 * @tc.name: CustomTest004
 * @tc.desc: Create Custom node and test MarkNeedUpdate and Update.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabContent and push it to view stack processor.
     * @tc.expected: Make TabContent as CustomNode parent.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke CustomNode Create function.
     * @tc.expected: Create CustomNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step3. Create Parent LayoutWrapperNode.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    /**
     * @tc.steps: step4. set DestroyFunction and UpdateFunction, invoke Update and MarkNeedUpdate function.
     * @tc.expected: parentLayoutWrapper's childCount is zero.
     */
    bool destroyFunc = false;
    customNode->SetDestroyFunction([&destroyFunc]() { destroyFunc = true; });
    customNode->Update();
    bool updateFunc = false;
    customNode->SetUpdateFunction([&updateFunc]() { updateFunc = true; });
    customNode->Update();
    customNode->MarkNeedUpdate();
    customNode->MarkNeedUpdate();
    customNode->AdjustLayoutWrapperTree(parentLayoutWrapper, false, false);
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_0);
}

/**
 * @tc.name: CustomTest005
 * @tc.desc: Create Custom node.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabContent and push it to view stack processor.
     * @tc.expected: Make TabContent as CustomNode parent.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke CustomNode Create function.
     * @tc.expected: Create CustomNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step3. Create Parent LayoutWrapperNode.
     */
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    /**
     * @tc.steps: step4. set renderFunction, add child to customNode and invoke Measure function.
     * @tc.expected: parentLayoutWrapper's childCount is one.
     */
    RefPtr<AceType> view;
    auto renderFunc = [&view]() -> RefPtr<AceType> { return nullptr; };
    auto renderFunction = [internalRender = std::move(renderFunc)]() -> RefPtr<UINode> {
        auto uiNode = internalRender();
        return AceType::DynamicCast<UINode>(uiNode);
    };
    customNode->SetRenderFunction(std::move(renderFunction));
    customNode->AdjustLayoutWrapperTree(parentLayoutWrapper, false, false);

    auto textFrameNode = CreateNode(V2::TEXT_ETS_TAG);
    textFrameNode->MountToParent(customNode);
    layoutAlgorithm->Measure(AceType::RawPtr(parentLayoutWrapper));
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_1);
}

/**
 * @tc.name: CustomTest006
 * @tc.desc: Create CustomNode and child node is CustomNode and test AdjustLayoutWrapperTree.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabContent and push it to view stack processor.
     * @tc.expected: Make TabContent as CustomNode parent.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke CustomNode Create function and another CustomNode mount to CustomNode.
     * @tc.expected: Create CustomNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    auto childCustomNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(childCustomNode != nullptr && childCustomNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    childCustomNode->MountToParent(customNode);

    /**
     * @tc.steps: step3. Create Parent LayoutWrapperNode.
     */
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    customNode = nullptr;
    customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    /**
     * @tc.steps: step4. set renderFunction, add child to customNode and invoke Measure function.
     * @tc.expected: parentLayoutWrapper's childCount is one.
     */
    RefPtr<AceType> view;
    auto renderFunc = [&view]() -> RefPtr<AceType> { return nullptr; };
    auto renderFunction = [internalRender = std::move(renderFunc)]() -> RefPtr<UINode> {
        auto uiNode = internalRender();
        return AceType::DynamicCast<UINode>(uiNode);
    };
    customNode->SetRenderFunction(std::move(renderFunction));
    customNode->AdjustLayoutWrapperTree(parentLayoutWrapper, false, false);
    auto textFrameNode = CreateNode(V2::TEXT_ETS_TAG);
    textFrameNode->MountToParent(customNode);
    layoutAlgorithm->Measure(AceType::RawPtr(parentLayoutWrapper));
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_1);
}

/**
 * @tc.name: CustomTest007
 * @tc.desc: Create CustomNode and child node is CustomNode and grandChild node is CustomNode and test
 * AdjustLayoutWrapperTree.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabContent and push it to view stack processor.
     * @tc.expected: Make TabContent as CustomNode parent.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke CustomNode Create function and another CustomNode mount to CustomNode.
     * @tc.expected: Create CustomNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    auto childCustomNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(childCustomNode != nullptr && childCustomNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    childCustomNode->MountToParent(customNode);

    auto grandChildCustomNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(grandChildCustomNode != nullptr && grandChildCustomNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    grandChildCustomNode->MountToParent(childCustomNode);

    /**
     * @tc.steps: step3. Create Parent LayoutWrapperNode.
     */
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    customNode = nullptr;
    customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    /**
     * @tc.steps: step4. set renderFunction, add child to customNode and invoke Measure function.
     * @tc.expected: parentLayoutWrapper's childCount is one.
     */
    RefPtr<AceType> view;
    auto renderFunc = [&view]() -> RefPtr<AceType> { return nullptr; };
    auto renderFunction = [internalRender = std::move(renderFunc)]() -> RefPtr<UINode> {
        auto uiNode = internalRender();
        return AceType::DynamicCast<UINode>(uiNode);
    };
    customNode->SetRenderFunction(std::move(renderFunction));
    customNode->AdjustLayoutWrapperTree(parentLayoutWrapper, false, false);
    auto textFrameNode = CreateNode(V2::TEXT_ETS_TAG);
    textFrameNode->MountToParent(customNode);
    layoutAlgorithm->Measure(AceType::RawPtr(parentLayoutWrapper));
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_1);
}

/**
 * @tc.name: CustomTest008
 * @tc.desc: Create CustomMeasureLayoutNode and test measure and layout.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabContent and push it to view stack processor.
     * @tc.expected: Make TabContent as CustomNode parent.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke CustomNode Create function and create textNode mount to CustomNode.
     * @tc.expected: Create CustomNode.
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
    /**
     * @tc.steps: step4. set renderFunction, add child to customNode and invoke Measure function.
     * @tc.expected: parentLayoutWrapper's childCount is one.
     */
    RefPtr<AceType> view;
    auto renderFunc = [&view]() -> RefPtr<AceType> { return nullptr; };
    auto renderFunction = [internalRender = std::move(renderFunc)]() -> RefPtr<UINode> {
        auto uiNode = internalRender();
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

    layoutAlgorithm->Measure(AceType::RawPtr(parentLayoutWrapper));
    layoutAlgorithm->Layout(AceType::RawPtr(parentLayoutWrapper));
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_1);
}

/**
 * @tc.name: CustomTest009
 * @tc.desc: Create Custom node.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text and push it to view stack processor.
     * @tc.expected: Make Text as CustomNode parent.
     */
    auto frameNode = CreateNode(V2::TEXT_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke CustomNode Create function.
     * @tc.expected: Create CustomNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);
    bool needRebuild = true;

    /**
     * @tc.steps: step3. set needMarkParent_ and needRebuild_ and invoke MarkNeedSyncRenderTree.
     * @tc.expected: the related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            customNode->MarkNeedSyncRenderTree(needRebuild);
            customNode->needMarkParent_ = false;
        }
        customNode->needMarkParent_ = true;
        customNode->needRebuild_ = false;
    }
    EXPECT_TRUE(customNode != nullptr);
}

/**
 * @tc.name: CustomTest010
 * @tc.desc: Create Custom node.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text and push it to view stack processor.
     * @tc.expected: Make Text as CustomNode parent.
     */
    auto frameNode = CreateNode(V2::TEXT_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke CustomNode Create function.
     * @tc.expected: Create CustomNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);
    /**
     * @tc.steps: step3. set recycleCustomNodeFunc and invoke FireRecycleSelf.
     * @tc.expected: the related function runs ok.
     */
    bool recycleCustomNodeFunc = true;
    customNode->SetRecycleFunction([&recycleCustomNodeFunc](RefPtr<CustomNodeBase>) { recycleCustomNodeFunc = true; });
    customNode->FireRecycleSelf();
    EXPECT_TRUE(customNode->needRebuild_ = true);
    customNode->needRebuild_ = false;
    customNode->SetRecycleFunction(nullptr);
    customNode->FireRecycleSelf();
    bool test = customNode->needRebuild_;
    EXPECT_EQ(test, false);
}

/**
 * @tc.name: CustomTest011
 * @tc.desc: Create Custom node and test MarkNeedUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabContent and push it to view stack processor.
     * @tc.expected: Make TabContent as CustomNode parent.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke CustomNode Create function.
     * @tc.expected: Create CustomNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step3. Create Parent LayoutWrapperNode.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    /**
     * @tc.steps: step4. set recycleRender, invoke MarkNeedUpdata function.
     * @tc.expected: parentLayoutWrapper's childCount is zero.
     */
    bool destroyFunc = false;
    customNode->SetDestroyFunction([&destroyFunc]() { destroyFunc = true; });
    customNode->Update();
    bool updateFunc = false;
    customNode->SetUpdateFunction([&updateFunc]() { updateFunc = true; });
    customNode->Update();
    bool recycleRenderFunc = false;
    customNode->SetRecycleRenderFunc([&recycleRenderFunc]() { recycleRenderFunc = true; });
    customNode->MarkNeedUpdate();
    customNode->MarkNeedUpdate();
    bool test = customNode->needRebuild_;
    EXPECT_NE(test, true);
}

/**
 * @tc.name: CustomTest012
 * @tc.desc: Create Custom node.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomNodeLayoutAlgorithm and frameNode.
     * @tc.expected: Make Text as CustomNode parent.
     */
    CustomNodeLayoutAlgorithm test = CustomNodeLayoutAlgorithm(
        []() { return AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>()); });
    auto frameNode = CreateNode(V2::TEXT_ETS_TAG);

    /**
     * @tc.steps: step2. Create CustomNode and set active.
     * @tc.expected: Create CustomNode.
     */
    auto customNodetest = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNodetest != nullptr && customNodetest->GetTag() == V2::JS_VIEW_ETS_TAG);
    /**
     * @tc.steps: step3. set RenderFunction and invoke Mersure.
     * @tc.expected: the related function runs ok.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = customNode->CreateLayoutWrapper();
    auto renderfunction = []() { return AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>()); };
    test.renderFunction_ = renderfunction;
    test.Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_NE(renderfunction(), nullptr);
}

/**
 * @tc.name: CustomTest013
 * @tc.desc: Create Custom node.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create test.
     * @tc.expected: Make Text as CustomNode parent.
     */
    CustomNodeLayoutAlgorithm test = CustomNodeLayoutAlgorithm(
        []() { return AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>()); });

    /**
     * @tc.steps: step2. Create frameNode.
     * @tc.expected: Make TabContent as CustomNode parent.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);

    /**
     * @tc.steps: step3. Create LayoutWrapper, customNode, set measureFuncion and invoke Measure.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = customNode->CreateLayoutWrapper();
    auto renderfunction = []() { return AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>()); };
    test.renderFunction_ = renderfunction;
    NG::LayoutWrapper* testMeasureFun;
    auto measureFuncation = [&testMeasureFun](
                                NG::LayoutWrapper* layoutWrapper = nullptr) { testMeasureFun = layoutWrapper; };
    customNode->SetMeasureFunction(std::move(measureFuncation));

    test.Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_NE(renderfunction(), nullptr);
}

/**
 * @tc.name: CustomTest014
 * @tc.desc: Create Custom node.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create test.
     * @tc.expected: Make Text as CustomNode parent.
     */
    CustomNodeLayoutAlgorithm test = CustomNodeLayoutAlgorithm(
        []() { return AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>()); });

    /**
     * @tc.steps: step2. Create frameNode.
     * @tc.expected: Make TabContent as CustomNode parent.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);

    /**
     * @tc.steps: step3. Create LayoutWrapper, customNode, set LayoutFunction and invoke Layout.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = customNode->CreateLayoutWrapper();
    auto renderfunction = []() { return AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>()); };
    test.renderFunction_ = renderfunction;
    NG::LayoutWrapper* testLayoutFunction;
    auto LayoutFunction = [&testLayoutFunction](
                              NG::LayoutWrapper* layoutWrapper = nullptr) { testLayoutFunction = layoutWrapper; };
    customNode->SetLayoutFunction(std::move(LayoutFunction));
    test.Layout(AceType::RawPtr(layoutWrapper));
    auto host = AceType::DynamicCast<CustomMeasureLayoutNode>(layoutWrapper->GetHostNode());
    ASSERT_NE(host, nullptr);
}

/**
 * @tc.name: CustomTest015
 * @tc.desc: Build Custom node.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    /**
     * @tc.steps: step2. Create ExtraInfo and Call Build.
     * @tc.expected: Build Seccuss
     */
    ExtraInfo extraTemp;
    extraTemp.line = CHILD_COUNT_0;
    extraTemp.page = TEST_TAG;
    std::list<ExtraInfo> ListextraInfos;
    ListextraInfos.push_back(extraTemp);
    std::shared_ptr<std::list<ExtraInfo>> extraInfos = std::make_unique<std::list<ExtraInfo>>(ListextraInfos);
    customNode->Build(extraInfos);
    EXPECT_EQ(customNode->extraInfos_.size(), 1);
    EXPECT_EQ(customNode->extraInfos_.front().line, CHILD_COUNT_0);
    EXPECT_EQ(customNode->extraInfos_.front().page, TEST_TAG);
}

/**
 * @tc.name: CustomTest016
 * @tc.desc: Build Render.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    /**
     * @tc.steps: step2. Create renderFunction and Call Render.
     * @tc.expected: Add Child Success
     */
    auto renderFunction = [&]() -> RefPtr<UINode> {
        RefPtr<UINode> uiNode =
            CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId() + 1, TEST_TAG);
        return uiNode;
    };
    customNode->renderFunction_ = renderFunction;
    customNode->Render();
    EXPECT_EQ(customNode->GetChildren().size(), 1);
}

/**
 * @tc.name: CustomTest017
 * @tc.desc: FlushReload.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create customNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    /**
     * @tc.steps: step2. Create completeReloadFunc_ and Call FlushReload.
     * @tc.expected: Add Child Success
     */
    auto renderFunction = [&]() -> RefPtr<UINode> {
        RefPtr<UINode> uiNode =
            CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId() + 1, TEST_TAG);
        return uiNode;
    };
    customNode->completeReloadFunc_ = renderFunction;
    customNode->FlushReload();
    EXPECT_EQ(customNode->GetChildren().size(), 1);
}

/**
 * @tc.name: CustomTest018
 * @tc.desc: AdjustLayoutWrapperTree.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabContent and push it to view stack processor.
     * @tc.expected: Make TabContent as CustomNode parent.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke CustomNode Create function.
     * @tc.expected: Create CustomNode.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    EXPECT_TRUE(customNode != nullptr && customNode->GetTag() == V2::JS_VIEW_ETS_TAG);

    /**
     * @tc.steps: step3. Create Parent LayoutWrapperNode.
     */
    auto pattern = frameNode->GetPattern<Pattern>();
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step4. set renderFunction, add child to customNode and invoke Measure function.
     * @tc.expected: parentLayoutWrapper's childCount is one.
     */
    RefPtr<AceType> view;
    auto renderFunc = [&view]() -> RefPtr<AceType> { return nullptr; };
    auto renderFunction = [internalRender = std::move(renderFunc)]() -> RefPtr<UINode> {
        auto uiNode = internalRender();
        return AceType::DynamicCast<UINode>(uiNode);
    };
    auto customNode2 = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId() + 1, TEST_TAG);
    auto customNode3 = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId() + 2, TEST_TAG);
    customNode2->AddChild(customNode3);
    customNode->AddChild(customNode2);
    customNode->SetRenderFunction(std::move(renderFunction));
    customNode->AdjustLayoutWrapperTree(parentLayoutWrapper, false, false);

    auto textFrameNode = CreateNode(V2::TEXT_ETS_TAG);
    textFrameNode->MountToParent(customNode);
    layoutAlgorithm->Measure(AceType::RawPtr(parentLayoutWrapper));
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_1);
}

/**
 * @tc.name: CustomTest019
 * @tc.desc: CreateLayoutWrapper.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = CreateNode(V2::TAB_CONTENT_ITEM_ETS_TAG);

    /**
     * @tc.steps: step2. Create CustomNode and Call CreateLayoutWrapper.
     * @tc.expected: Create successful.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    auto node = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    node->isLayoutDirtyMarked_ = true;
    customNode->AddChild(node);
    RefPtr<LayoutWrapperNode> layoutWrapperNode = customNode->CreateLayoutWrapper(true, true);
    EXPECT_NE(layoutWrapperNode, nullptr);
    EXPECT_FALSE(node->isLayoutDirtyMarked_);
}

/**
 * @tc.name: CustomTest020
 * @tc.desc: Test cast of FireRecycleSelf.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomNodeBase through customNode.
     */
    RefPtr<CustomNode> customNode =
        CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    /**
     * @tc.steps: step2. Create frameNode and frameNode2 and Add Child to customNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    customNode->AddChild(frameNode);
    auto frameNode2 = AceType::MakeRefPtr<FrameNode>("test2", 2, AceType::MakeRefPtr<Pattern>());
    frameNode2->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    auto geo = AceType::MakeRefPtr<GeometryTransition>(TEST_TAG, true);
    frameNode2->layoutProperty_->geometryTransition_ = AceType::WeakClaim(AceType::RawPtr(geo));
    customNode->AddChild(frameNode2);

    /**
     * @tc.steps: step3. Create customBase and Call FireRecycleSelf.
     * @tc.expected: Excute successful.
     */
    RefPtr<CustomNodeBase> customBase = customNode;
    std::string strTest = "";
    auto callback = [&]() { strTest = "test"; };
    customBase->SetAppearFunction(callback);
    customBase->FireRecycleSelf();
    EXPECT_EQ(customBase->recyclePatterns_.size(), 2);
}

/**
 * @tc.name: CustomTest021
 * @tc.desc: Test cast of SetOnDumpInfoFunc.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomNodeBase through customNode.
     */
    RefPtr<CustomNodeBase> customNode =
        CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);

    /**
     * @tc.steps: step2. Create CallBack.
     */
    std::vector<std::string> vctOut;
    auto callback = [&](const std::vector<std::string>& vctTemp) { vctOut.assign(vctTemp.begin(), vctTemp.end()); };

    /**
     * @tc.steps: step3. Call SetOnDumpInfoFunc.
     * @tc.expected: Excute successful and return is equal tith vctTemp.
     */
    customNode->SetOnDumpInfoFunc(callback);
    std::vector<std::string> vctTemp = { "test1", "test2" };
    customNode->onDumpInfoFunc_(vctTemp);
    EXPECT_EQ(vctOut.size(), 2);
}

/**
 * @tc.name: CustomTest022
 * @tc.desc: Test cast of CustomNodeLayoutAlgorithm.Measure.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create test.
     * @tc.expected: Make Text as CustomNode parent.
     */
    CustomNodeLayoutAlgorithm test = CustomNodeLayoutAlgorithm(
        []() { return AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>()); });

    /**
     * @tc.steps: step2. Create LayoutWrapper, customNode.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    auto layoutWrapper = customNode->CreateLayoutWrapper();
    auto renderfunction = []() { return AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>()); };
    test.renderFunction_ = renderfunction;

    /**
     * @tc.steps: step3. Create frameNode and add two Children.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = static_cast<ElementIdType>(1);
    stack->reservedNodeId_ = static_cast<ElementIdType>(1);
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("dummyNode", nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto frameChild1 =
        FrameNode::GetOrCreateFrameNode("Child1", nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto frameChild2 =
        FrameNode::GetOrCreateFrameNode("Child2", nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    frameNode->AddChild(frameChild1);
    frameNode->AddChild(frameChild2);

    /**
     * @tc.steps: step4. Set up the created frameNode.
     */
    ElementRegister::GetInstance()->itemMap_[nodeId] = frameNode;

    /**
     * @tc.steps: step5. Call Measure.
     * @tc.expected: customNode add a Child and buildItem is equal with child
     */
    test.Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(customNode->GetChildren().size(), 2);
    EXPECT_EQ(test.buildItem_, frameChild1);
}

/**
 * @tc.name: CustomTest023
 * @tc.desc: Test cast of CustomNodeLayoutAlgorithm.Layout.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create test.
     */
    CustomNodeLayoutAlgorithm test = CustomNodeLayoutAlgorithm(
        []() { return AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>()); });

    /**
     * @tc.steps: step2. Create LayoutWrapper, customNode, set LayoutFunction and invoke Layout.
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
        ElementRegister::GetInstance()->MakeUniqueId(), TEST_TAG);
    auto layoutWrapper = customNode->CreateLayoutWrapper();

    /**
     * @tc.steps: step3. Create LayoutWrapperNode and add to layoutWrapper.
     */
    auto node = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(node, geometryNode, node->GetLayoutProperty());
    layoutWrapper->AppendChild(layoutNode);

    /**
     * @tc.steps: step4. Call Layout.
     * @tc.expected: cachedList_ size is equal with layoutWrapper and active set success.
     */
    test.Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->cachedList_.size(), 1);
    for (const auto& child : layoutWrapper->cachedList_) {
        EXPECT_TRUE(child->IsActive());
    }
}

/**
 * @tc.name: CustomTest024
 * @tc.desc: Test cast of CustomNodePattern.OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and CustomNodePattern.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<FrameNode> weakNode1 = AceType::WeakClaim(AceType::RawPtr(frameNode));
    RefPtr<CustomNodePattern> pattern = AceType::MakeRefPtr<CustomNodePattern>();
    pattern->AttachToFrameNode(weakNode1);
    EXPECT_NE(pattern->GetHost(), nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapperNode and SetLayoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto rowLayoutAlgorithm1 = AceType::MakeRefPtr<LayoutAlgorithm>();
    RefPtr<CustomNodeLayoutAlgorithm> rowLayoutAlgorithm2 = AceType::MakeRefPtr<CustomNodeLayoutAlgorithm>(nullptr);
    auto frameNode2 = AceType::MakeRefPtr<FrameNode>("test2", 2, AceType::MakeRefPtr<Pattern>());
    rowLayoutAlgorithm2->buildItem_ = frameNode2;

    auto temp = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm1);
    temp->SetLayoutAlgorithm(rowLayoutAlgorithm2);
    layoutNode->SetLayoutAlgorithm(temp);

    /**
     * @tc.steps: step3. Call OnDirtyLayoutWrapperSwap.
     * @tc.expected: result id false and framenode add a child seccuss
     */
    DirtySwapConfig dirtyConfig;
    bool bResult = pattern->OnDirtyLayoutWrapperSwap(layoutNode, dirtyConfig);
    EXPECT_FALSE(bResult);
    EXPECT_EQ(frameNode->GetChildren().size(), 1);
}

/**
 * @tc.name: CustomTest025
 * @tc.desc: Test cast of CustomTitleNode.CreateCustomTitleNode.
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, CustomTest025, TestSize.Level1)
{
    RefPtr<CustomTitleNode> customTitleNode = CustomTitleNode::CreateCustomTitleNode(1, "test");
    EXPECT_EQ(customTitleNode->tag_, V2::JS_VIEW_ETS_TAG);
    EXPECT_EQ(customTitleNode->nodeId_, 1);
    EXPECT_EQ(customTitleNode->viewKey_, "test");
}
} // namespace OHOS::Ace::NG