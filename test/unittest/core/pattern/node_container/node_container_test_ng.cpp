/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <optional>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/node_container/node_container_layout_algorithm.h"
#include "core/components_ng/pattern/node_container/node_container_model_ng.h"
#include "core/components_ng/pattern/node_container/node_container_node.h"
#include "core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/components_ng/pattern/render_node/render_node_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string CHILD_NODE = "ChildNode";
} // namespace

class NodeContainerTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateNode();
};

void NodeContainerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void NodeContainerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> NodeContainerTestNg::CreateNode()
{
    NodeContainerModelNG modelNg;
    modelNg.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: NodeContainerFrameNodeCreator001
 * @tc.desc: Test the create of NodeContainer.
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, NodeContainerFrameNodeCreator001, TestSize.Level1)
{
    RefPtr<FrameNode> nodeContainerNode = CreateNode();
    ASSERT_NE(nodeContainerNode, nullptr);
}

/**
 * @tc.name: NodeContainerRemakeNode001
 * @tc.desc: Test the RemakeNode function of NodeContainer.
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, NodeContainerRemakeNode001, TestSize.Level1)
{
    RefPtr<FrameNode> nodeContainerNode = CreateNode();
    ASSERT_NE(nodeContainerNode, nullptr);
    RefPtr<FrameNode> childNode = FrameNode::CreateFrameNode(CHILD_NODE, 0, AceType::MakeRefPtr<Pattern>());
    auto pattern = nodeContainerNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step1. do nothing, fire RemakeNode without makeFunc_.
     * @tc.expected: process success without crash
     */
    pattern->RemakeNode();
    ASSERT_EQ(nodeContainerNode->GetChildAtIndex(0), nullptr);

    /**
     * @tc.steps: step2.Fire RemakeNode return with a normal node.
     * @tc.expected: process success without crash, and does not change the child of NodeContainer.
     */
    pattern->SetMakeFunction([childNode]() -> RefPtr<UINode> { return childNode; });
    pattern->RemakeNode();
    ASSERT_EQ(nodeContainerNode->GetChildAtIndex(0), nullptr);

    /**
     * @tc.steps: step3.Fire RemakeNode return with a root node of BuilderNode.
     * @tc.expected: process success without crash, and change the child of NodeContainer.
     */
    childNode->SetIsRootBuilderNode(false);
    childNode->SetIsArkTsFrameNode(true);
    pattern->RemakeNode();
    ASSERT_EQ(nodeContainerNode->GetChildAtIndex(0)->GetId(), childNode->GetId());

    /**
     * @tc.steps: step4.Fire RemakeNode without return with a same node of BuilderNode.
     * @tc.expected: process success without crash, and does not change the child of NodeContainer.
     */
    pattern->RemakeNode();
    ASSERT_EQ(nodeContainerNode->GetChildAtIndex(0)->GetId(), childNode->GetId());

    /**
     * @tc.steps: step5.Fire RemakeNode without return with a different node of BuilderNode.
     * @tc.expected: process success without crash, and does change the child of NodeContainer.
     */
    auto childNode_one = FrameNode::CreateFrameNode(CHILD_NODE, 1, AceType::MakeRefPtr<Pattern>());
    childNode_one->SetIsRootBuilderNode(false);
    childNode_one->SetIsArkTsFrameNode(true);
    pattern->SetMakeFunction([childNode_one]() -> RefPtr<UINode> { return childNode_one; });
    pattern->RemakeNode();
    ASSERT_EQ(nodeContainerNode->GetChildAtIndex(0)->GetId(), childNode_one->GetId());

    /**
     * @tc.steps: step6.Fire RemakeNode without return with a frame node.
     * @tc.expected: process success without crash, and does change the child of NodeContainer.
     */
    auto childNode_two = FrameNode::CreateFrameNode(V2::CUSTOM_FRAME_NODE_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    childNode_two->SetIsRootBuilderNode(false);
    childNode_two->SetIsArkTsFrameNode(true);
    pattern->SetMakeFunction([childNode_two]() -> RefPtr<UINode> { return childNode_two; });
    pattern->RemakeNode();
    ASSERT_EQ(nodeContainerNode->GetChildAtIndex(0)->GetId(), childNode_two->GetId());
}

/**
 * @tc.name: NodeContainerLayoutAlgorithmMeasure001
 * @tc.desc: Test the Measure function of NodeContainerLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, NodeContainerLayoutAlgorithmMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<FrameNode> nodeContainerNode = CreateNode();
    ASSERT_NE(nodeContainerNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = LayoutWrapperNode(nodeContainerNode, geometryNode, nodeContainerNode->GetLayoutProperty());
    auto contentChanges = layoutWrapper.GetContentChanges();
    contentChanges.UpdateFlags(std::nullopt, std::nullopt);
    layoutWrapper.GetContentChanges().ToString();
    auto layoutAlgorithm = AceType::MakeRefPtr<NodeContainerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<FrameNode> childNodeOne = FrameNode::CreateFrameNode("RenderNode", 0, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> childNodeTwo = FrameNode::CreateFrameNode("ChildNode", 0, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. update layoutWrapper.
     */
    auto childLayoutWrapperOne = childNodeOne->CreateLayoutWrapper();
    ASSERT_NE(childLayoutWrapperOne, nullptr);
    auto childLayoutWrapperTwo = childNodeTwo->CreateLayoutWrapper();
    ASSERT_NE(childLayoutWrapperTwo, nullptr);
    layoutWrapper.cachedList_ = std::list<RefPtr<LayoutWrapper>>();
    layoutWrapper.cachedList_.push_back(childLayoutWrapperOne);
    layoutWrapper.cachedList_.push_back(childLayoutWrapperTwo);

    /**
     * @tc.steps: step3. call the function Measure.
     */
    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize().Width(), 0.0);
}

/**
 * @tc.name: NodeContainerModelNGSetMakeFunction001
 * @tc.desc: Test the SetMakeFunction function of NodeContainerModelNG.
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, NodeContainerModelNGSetMakeFunction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create modelNg.
     */
    NodeContainerModelNG modelNg;
    modelNg.Create();
    auto builderFunc = []() -> RefPtr<UINode> {
        auto node = FrameNode::CreateFrameNode("node", 0, AceType::MakeRefPtr<Pattern>(), true);
        auto childNode = FrameNode::CreateFrameNode("child", 1, AceType::MakeRefPtr<Pattern>(), true);
        node->AddChild(childNode);
        return node;
    };

    /**
     * @tc.steps: step2. call the function SetMakeFunction.
     */
    modelNg.SetMakeFunction(builderFunc);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = AceType::DynamicCast<NodeContainerPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    auto node = pattern->FireMakeFunction();
    EXPECT_EQ(node->GetChildren().size(), 1);
}

/**
 * @tc.name: NodeContainerModelNGSetOnResize001
 * @tc.desc: Test the SetOnResize function of NodeContainerModelNG.
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, NodeContainerModelNGSetOnResize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create modelNg.
     */
    NodeContainerModelNG modelNg;
    modelNg.Create();
    uint32_t flag = 0;
    auto builderFunc = [&flag](const SizeF& size) { flag = 1; };

    /**
     * @tc.steps: step2. call the function SetOnResize.
     */
    modelNg.SetOnResize(std::move(builderFunc));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = AceType::DynamicCast<NodeContainerPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->FireOnResize(SizeF(1.0f, 1.0f));
    EXPECT_EQ(flag, 1);
}

/**
 * @tc.name: NodeContainerModelNGSetOnTouchEvent001
 * @tc.desc: Test the SetOnTouchEvent function of NodeContainerModelNG.
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, NodeContainerModelNGSetOnTouchEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create modelNg.
     */
    NodeContainerModelNG modelNg;
    modelNg.Create();
    TouchEventFunc touchEventFunc = [](TouchEventInfo& info) {};

    /**
     * @tc.steps: step2. call the function SetOnTouchEvent.
     */
    auto gestureEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    modelNg.SetOnTouchEvent(std::move(touchEventFunc));
    EXPECT_NE(gestureEventHub->touchEventActuator_, nullptr);
}

/**
 * @tc.name: NodeContainerModelNGBindController001
 * @tc.desc: Test the BindController function of NodeContainerModelNG.
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, NodeContainerModelNGBindController001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create modelNg.
     */
    NodeContainerModelNG modelNg;
    modelNg.Create();
    uint32_t flag = 0;
    auto builderFunc = [&flag]() { flag = 1; };

    /**
     * @tc.steps: step2. call the function BindController ResetController.
     */
    modelNg.BindController(std::move(builderFunc));
    modelNg.ResetController();
    modelNg.FireMakeNode();
    EXPECT_EQ(flag, 1);
}

/**
 * @tc.name: NodeContainerNodeGetOrCreateNodeContainerNode001
 * @tc.desc: Test the GetOrCreateNodeContainerNode function of NodeContainerNode.
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, NodeContainerNodeGetOrCreateNodeContainerNode001, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
    };
    /**
     * @tc.steps: step1: create commonNode.
     */
    RefPtr<FrameNode> node = FrameNode::CreateFrameNode(V2::NODE_CONTAINER_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto layoutWrapper = node->CreateLayoutWrapper();
    auto contentChanges = layoutWrapper->GetContentChanges();
    auto constraintChanges = layoutWrapper->GetConstraintChanges();
    contentChanges.UpdateFlags(layoutConstraintF, layoutConstraintF);
    constraintChanges.UpdateFlags(layoutConstraintF, std::nullopt);
    contentChanges.UpdateFlags(std::nullopt, layoutConstraintF);

    /**
     * @tc.steps: step2: call the function GetOrCreateNodeContainerNode.
     * @tc.expected: Value returned as expected.
     */
    auto blankNode = NodeContainerNode::GetOrCreateNodeContainerNode(1);
    EXPECT_EQ(strcmp(blankNode->GetTag().c_str(), V2::NODE_CONTAINER_ETS_TAG), 0);
}

/**
 * @tc.name: NodeContainerNodeOnRecycle001
 * @tc.desc: Test the OnRecycle function of NodeContainerNode.
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, NodeContainerNodeOnRecycle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create commonNode.
     */
    RefPtr<FrameNode> nodeContainerNode = CreateNode();
    ASSERT_NE(nodeContainerNode, nullptr);
    bool flag = false;
    /**
     * @tc.steps: step2: call the function OnRecycle.
     * @tc.expected: Value returned as expected.
     */
    nodeContainerNode->OnRecycle();
    nodeContainerNode->OnReuse();
    EXPECT_EQ(flag, false);
    nodeContainerNode->PushDestroyCallback([&flag]() { flag = !flag; });
    nodeContainerNode->OnRecycle();
    SystemProperties::developerModeOn_ = true;
    auto pattern = nodeContainerNode->pattern_;
    nodeContainerNode->pattern_ = nullptr;
    nodeContainerNode->OnReuse();
    nodeContainerNode->pattern_ = pattern;
    SystemProperties::developerModeOn_ = false;
    EXPECT_EQ(flag, true);
}
} // namespace OHOS::Ace::NG
