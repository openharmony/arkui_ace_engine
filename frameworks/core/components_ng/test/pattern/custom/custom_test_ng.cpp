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
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

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
    MockPipelineBase::SetUp();
}

void CustomTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "CustomTestNg TearDownTestCase";
    MockPipelineBase::TearDown();
}

void CustomTestNg::SetUp()
{
    MockPipelineBase::SetUp();
}

void CustomTestNg::TearDown()
{
    MockPipelineBase::TearDown();
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
    customNode->Build();
    customNode->AdjustLayoutWrapperTree(parentLayoutWrapper, false, false);
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_0);

    RefPtr<AceType> view;
    auto renderFunc = [&view]() -> RefPtr<AceType> { return nullptr; };
    auto renderFunction = [internalRender = std::move(renderFunc)]() -> RefPtr<UINode> {
        auto uiNode = internalRender();
        return AceType::DynamicCast<UINode>(uiNode);
    };
    customNode->SetRenderFunction(std::move(renderFunction));
    customNode->Build();
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
    customNode->Build();
    customNode->AdjustLayoutWrapperTree(parentLayoutWrapper, false, false);
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_0);

    RefPtr<AceType> view;
    auto renderFunc = [&view]() -> RefPtr<AceType> { return nullptr; };
    auto renderFunction = [internalRender = std::move(renderFunc)]() -> RefPtr<UINode> {
        auto uiNode = internalRender();
        return AceType::DynamicCast<UINode>(uiNode);
    };
    customNode->SetRenderFunction(std::move(renderFunction));
    customNode->Build();
    customNode->AdjustLayoutWrapperTree(parentLayoutWrapper, false, false);
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), CHILD_COUNT_1);
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
    layoutAlgorithm->Measure(AceType::RawPtr(parentLayoutWrapper));

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
    EXPECT_TRUE(customNode->needRebuild_ = true);
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
    EXPECT_TRUE(customNode->needRebuild_ = true);
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
} // namespace OHOS::Ace::NG