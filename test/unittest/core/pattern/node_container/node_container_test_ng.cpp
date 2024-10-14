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
#include "test/mock/core/render/mock_canvas_image.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/gauge/gauge_pattern.h"
#include "core/components_ng/pattern/image/image_paint_method.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/node_container/node_container_layout_algorithm.h"
#include "core/components_ng/pattern/node_container/node_container_model_ng.h"
#include "core/components_ng/pattern/node_container/node_container_node.h"
#include "core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/components_ng/pattern/render_node/render_node_pattern.h"
#include "core/components_ng/render/paint_wrapper.h"

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

    /**
     * @tc.steps: step7.Fire RemakeNode return with nullptr. When oldNode is not null.
     * @tc.expected: process success without crash.
     */
    auto childNode_three = FrameNode::CreateFrameNode(CHILD_NODE, 3, AceType::MakeRefPtr<Pattern>());
    childNode_three->SetIsRootBuilderNode(false);
    childNode_three->SetIsArkTsFrameNode(true);
    pattern->SetMakeFunction([childNode_three]() -> RefPtr<UINode> { return childNode_three; });
    pattern->RemakeNode();
    ASSERT_EQ(nodeContainerNode->GetChildAtIndex(0)->GetId(), childNode_three->GetId());
    pattern->SetMakeFunction([childNode]() -> RefPtr<UINode> { return nullptr; });
    pattern->RemakeNode();
    ASSERT_EQ(nodeContainerNode->GetChildAtIndex(0), nullptr);
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
    nodeContainerNode->PushDestroyCallbackWithTag([&flag]() { flag = !flag; }, "");
    nodeContainerNode->OnRecycle();
    SystemProperties::developerModeOn_ = true;
    auto pattern = nodeContainerNode->pattern_;
    nodeContainerNode->pattern_ = nullptr;
    nodeContainerNode->OnReuse();
    nodeContainerNode->pattern_ = pattern;
    SystemProperties::developerModeOn_ = false;
    EXPECT_EQ(flag, true);
}

/**
 * @tc.name: NodeContainerPatternOnDirtyLayoutWrapperSwap001
 * @tc.desc: Test the OnDirtyLayoutWrapperSwap function of NodeContainerPattern.
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, NodeContainerPatternOnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create node and get pattern.
     */
    RefPtr<FrameNode> node = FrameNode::CreateFrameNode("node", 1, AceType::MakeRefPtr<NodeContainerPattern>());
    ASSERT_NE(node, nullptr);
    auto pattern = AceType::DynamicCast<NodeContainerPattern>(node->GetPattern());
    ASSERT_NE(pattern, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper = node->CreateLayoutWrapper(true, true);

    /**
     * @tc.steps: step2: call the function OnDirtyLayoutWrapperSwap.
     * @tc.expected: Value returned as expected.
     */
    DirtySwapConfig config;
    config.skipLayout = true;
    config.skipMeasure = true;
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    config.skipLayout = false;
    config.frameSizeChange = false;
    pattern->surfaceId_ = 1U;
    auto testNode = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    pattern->exportTextureNode_ = AceType::WeakClaim(AceType::RawPtr(testNode));
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: NodeContainerPatternOnDirtyLayoutWrapperSwap002
 * @tc.desc: Test the OnDirtyLayoutWrapperSwap function of NodeContainerPattern.
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, NodeContainerPatternOnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create node and get pattern.
     */
    RefPtr<FrameNode> node = FrameNode::CreateFrameNode("node", 1, AceType::MakeRefPtr<NodeContainerPattern>());
    ASSERT_NE(node, nullptr);
    auto pattern = AceType::DynamicCast<NodeContainerPattern>(node->GetPattern());
    ASSERT_NE(pattern, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper = node->CreateLayoutWrapper(true, true);

    /**
     * @tc.steps: step2: call the function OnDirtyLayoutWrapperSwap.
     * @tc.expected: Value returned as expected.
     */
    pattern->CleanChild();
    DirtySwapConfig config;
    config.skipLayout = false;
    config.skipMeasure = false;
    pattern->surfaceId_ = 0U;
    config.frameSizeChange = true;
    auto testNode = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    pattern->exportTextureNode_ = AceType::WeakClaim(AceType::RawPtr(testNode));
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    pattern->OnAddBaseNode();
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: NodeContainerPatternOnDirtyLayoutWrapperSwap003
 * @tc.desc: Test the OnDirtyLayoutWrapperSwap function of NodeContainerPattern.
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, NodeContainerPatternOnDirtyLayoutWrapperSwap003, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create node and get pattern.
     */
    RefPtr<FrameNode> node = FrameNode::CreateFrameNode("node", 1, AceType::MakeRefPtr<NodeContainerPattern>());
    ASSERT_NE(node, nullptr);
    auto pattern = AceType::DynamicCast<NodeContainerPattern>(node->GetPattern());
    ASSERT_NE(pattern, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper = node->CreateLayoutWrapper(true, true);
    auto child = AceType::MakeRefPtr<FrameNode>("child", -1, AceType::MakeRefPtr<Pattern>());
    node->AddChild(child);
    RefPtr<FrameNode> parent =
        FrameNode::CreateFrameNode(V2::NODE_CONTAINER_ETS_TAG, 1, AceType::MakeRefPtr<NodeContainerPattern>());
    parent->AddChild(node);
    node->exportTextureInfo_ = AceType::MakeRefPtr<ExportTextureInfo>();

    /**
     * @tc.steps: step2: call the function OnDirtyLayoutWrapperSwap.
     * @tc.expected: Value returned as expected.
     */
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = false;
    config.frameSizeChange = false;
    pattern->surfaceId_ = 1U;
    pattern->exportTextureNode_ = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: NodeContainerPatternOnDirtyLayoutWrapperSwap004
 * @tc.desc: Test the OnDirtyLayoutWrapperSwap function of NodeContainerPattern.
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, NodeContainerPatternOnDirtyLayoutWrapperSwap004, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create node and get pattern.
     */
    RefPtr<FrameNode> node = FrameNode::CreateFrameNode("node", 1, AceType::MakeRefPtr<NodeContainerPattern>());
    ASSERT_NE(node, nullptr);
    auto pattern = AceType::DynamicCast<NodeContainerPattern>(node->GetPattern());
    ASSERT_NE(pattern, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper = node->CreateLayoutWrapper(true, true);
    auto child = AceType::MakeRefPtr<FrameNode>("child", -1, AceType::MakeRefPtr<Pattern>());
    node->AddChild(child);
    RefPtr<FrameNode> parent =
        FrameNode::CreateFrameNode(V2::NODE_CONTAINER_ETS_TAG, 1, AceType::MakeRefPtr<NodeContainerPattern>());
    parent->AddChild(node);
    node->exportTextureInfo_ = AceType::MakeRefPtr<ExportTextureInfo>();
    node->exportTextureInfo_->curRenderType_ = NodeRenderType::RENDER_TYPE_TEXTURE;
    child->exportTextureInfo_ = AceType::MakeRefPtr<ExportTextureInfo>();
    child->exportTextureInfo_->curRenderType_ = NodeRenderType::RENDER_TYPE_TEXTURE;

    /**
     * @tc.steps: step2: call the function OnDirtyLayoutWrapperSwap.
     * @tc.expected: Value returned as expected.
     */
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = false;
    config.frameSizeChange = false;
    pattern->surfaceId_ = 1U;
    auto testNode = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    pattern->exportTextureNode_ = AceType::WeakClaim(AceType::RawPtr(testNode));
    pattern->OnAddBaseNode();
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: NodeContainerPatternOnDirtyLayoutWrapperSwap005
 * @tc.desc: Test the OnDirtyLayoutWrapperSwap function of NodeContainerPattern.
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, NodeContainerPatternOnDirtyLayoutWrapperSwap005, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create node and get pattern.
     */
    RefPtr<FrameNode> node = FrameNode::CreateFrameNode("node", 1, AceType::MakeRefPtr<NodeContainerPattern>());
    ASSERT_NE(node, nullptr);
    auto pattern = AceType::DynamicCast<NodeContainerPattern>(node->GetPattern());
    ASSERT_NE(pattern, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper = node->CreateLayoutWrapper(true, true);
    auto child = AceType::MakeRefPtr<FrameNode>("child", -1, AceType::MakeRefPtr<Pattern>());
    node->AddChild(child);
    RefPtr<FrameNode> parent =
        FrameNode::CreateFrameNode(V2::NODE_CONTAINER_ETS_TAG, 1, AceType::MakeRefPtr<NodeContainerPattern>());
    parent->AddChild(node);
    node->exportTextureInfo_ = AceType::MakeRefPtr<ExportTextureInfo>();
    node->exportTextureInfo_->curRenderType_ = NodeRenderType::RENDER_TYPE_DISPLAY;
    child->exportTextureInfo_ = AceType::MakeRefPtr<ExportTextureInfo>();
    child->exportTextureInfo_->curRenderType_ = NodeRenderType::RENDER_TYPE_TEXTURE;

    /**
     * @tc.steps: step2: call the function OnDirtyLayoutWrapperSwap.
     * @tc.expected: Value returned as expected.
     */
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = false;
    config.frameSizeChange = false;
    pattern->surfaceId_ = 1U;
    auto testNode = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    pattern->exportTextureNode_ = AceType::WeakClaim(AceType::RawPtr(testNode));
    pattern->OnAddBaseNode();
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: NodeContainerPatternOnDirtyLayoutWrapperSwap006
 * @tc.desc: Test the OnDirtyLayoutWrapperSwap function of NodeContainerPattern.
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, NodeContainerPatternOnDirtyLayoutWrapperSwap006, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create node and get pattern.
     */
    RefPtr<FrameNode> node = FrameNode::CreateFrameNode("node", 1, AceType::MakeRefPtr<NodeContainerPattern>());
    ASSERT_NE(node, nullptr);
    auto pattern = AceType::DynamicCast<NodeContainerPattern>(node->GetPattern());
    ASSERT_NE(pattern, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper = node->CreateLayoutWrapper(true, true);
    auto child = AceType::MakeRefPtr<FrameNode>("child", -1, AceType::MakeRefPtr<Pattern>());
    node->AddChild(child);
    RefPtr<FrameNode> parent =
        FrameNode::CreateFrameNode(V2::NODE_CONTAINER_ETS_TAG, 1, AceType::MakeRefPtr<NodeContainerPattern>());
    parent->AddChild(node);
    child->exportTextureInfo_ = AceType::MakeRefPtr<ExportTextureInfo>();
    child->exportTextureInfo_->curRenderType_ = NodeRenderType::RENDER_TYPE_TEXTURE;

    /**
     * @tc.steps: step2: call the function OnDirtyLayoutWrapperSwap.
     * @tc.expected: Value returned as expected.
     */
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = false;
    config.frameSizeChange = false;
    pattern->surfaceId_ = 1U;
    auto testNode = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    pattern->exportTextureNode_ = AceType::WeakClaim(AceType::RawPtr(testNode));
    pattern->OnAddBaseNode();
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: NodeContainerPatternOnDirtyLayoutWrapperSwap007
 * @tc.desc: Test the OnDirtyLayoutWrapperSwap function of NodeContainerPattern.
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, NodeContainerPatternOnDirtyLayoutWrapperSwap007, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create node and get pattern.
     */
    RefPtr<FrameNode> node = FrameNode::CreateFrameNode("node", 1, AceType::MakeRefPtr<NodeContainerPattern>());
    ASSERT_NE(node, nullptr);
    auto pattern = AceType::DynamicCast<NodeContainerPattern>(node->GetPattern());
    ASSERT_NE(pattern, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper = node->CreateLayoutWrapper(true, true);
    auto child = AceType::MakeRefPtr<FrameNode>("child", -1, AceType::MakeRefPtr<Pattern>());
    node->AddChild(child);
    RefPtr<FrameNode> parent = FrameNode::CreateFrameNode("parent", 1, AceType::MakeRefPtr<NodeContainerPattern>());
    parent->AddChild(node);
    child->exportTextureInfo_ = AceType::MakeRefPtr<ExportTextureInfo>();
    child->exportTextureInfo_->curRenderType_ = NodeRenderType::RENDER_TYPE_TEXTURE;

    /**
     * @tc.steps: step2: call the function OnDirtyLayoutWrapperSwap.
     * @tc.expected: Value returned as expected.
     */
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = false;
    config.frameSizeChange = false;
    pattern->surfaceId_ = 1U;
    auto testNode = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    pattern->exportTextureNode_ = AceType::WeakClaim(AceType::RawPtr(testNode));
    pattern->OnAddBaseNode();
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: NodeContainerPatternOnDirtyLayoutWrapperSwap008
 * @tc.desc: Test the OnDirtyLayoutWrapperSwap function of NodeContainerPattern.
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, NodeContainerPatternOnDirtyLayoutWrapperSwap008, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create node and get pattern.
     */
    RefPtr<FrameNode> node = FrameNode::CreateFrameNode("node", 1, AceType::MakeRefPtr<NodeContainerPattern>());
    ASSERT_NE(node, nullptr);
    auto pattern = AceType::DynamicCast<NodeContainerPattern>(node->GetPattern());
    ASSERT_NE(pattern, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper = node->CreateLayoutWrapper(true, true);
    auto child = AceType::MakeRefPtr<FrameNode>("child", -1, AceType::MakeRefPtr<Pattern>());
    node->AddChild(child);
    child->exportTextureInfo_ = AceType::MakeRefPtr<ExportTextureInfo>();
    child->exportTextureInfo_->curRenderType_ = NodeRenderType::RENDER_TYPE_TEXTURE;

    /**
     * @tc.steps: step2: call the function OnDirtyLayoutWrapperSwap.
     * @tc.expected: Value returned as expected.
     */
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = false;
    config.frameSizeChange = false;
    pattern->surfaceId_ = 1U;
    auto testNode = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    pattern->exportTextureNode_ = AceType::WeakClaim(AceType::RawPtr(testNode));
    pattern->OnAddBaseNode();
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: PaintWrapperTest001
 * @tc.desc: Test cast to PaintWrapper
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, PaintWrapperTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a framenode and paintwrapper.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<ListPattern>());
    auto pattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    auto paintMethod = pattern->CreateNodePaintMethod();
    RefPtr<ScrollablePaintProperty> paintProperty;
    RefPtr<RenderContext> renderContext = AceType::MakeRefPtr<RenderContext>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    paintWrapper->extensionHandler_ = AceType::MakeRefPtr<ExtensionHandler>();
    auto listModifier = paintMethod->GetContentModifier(AceType::RawPtr(paintWrapper));
    listModifier = AceType::MakeRefPtr<ListContentModifier>(OffsetF(1.0, 1.0), SizeF(1.0, 1.0));

    /**
     * @tc.steps: step2. call the function SetNodePaintMethod.
     */
    paintWrapper->SetNodePaintMethod(paintMethod);
    paintWrapper->FlushRender();
    paintWrapper->FlushContentModifier();
    auto contentModifier =
        AceType::DynamicCast<ContentModifier>(paintMethod->GetContentModifier(AceType::RawPtr(paintWrapper)));
    EXPECT_NE(contentModifier->extensionHandler_, nullptr);
}

/**
 * @tc.name: PaintWrapperTest002
 * @tc.desc: Test cast to PaintWrapper
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, PaintWrapperTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a framenode and paintwrapper.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<GaugePattern>());
    RefPtr<GaugePattern> pattern = AceType::DynamicCast<GaugePattern>(frameNode->GetPattern());
    pattern->gaugeModifier_ = AceType::MakeRefPtr<GaugeModifier>(nullptr);
    auto paintMethod = pattern->CreateNodePaintMethod();
    RefPtr<GaugePaintProperty> paintProperty;
    RefPtr<RenderContext> renderContext = AceType::MakeRefPtr<RenderContext>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    paintWrapper->extensionHandler_ = AceType::MakeRefPtr<ExtensionHandler>();
    auto context = paintWrapper->renderContext_.Upgrade();
    context->UpdateAccessibilityFocus(true);
    auto gaugeModifier = paintMethod->GetForegroundModifier(AceType::RawPtr(paintWrapper));
    gaugeModifier = AceType::MakeRefPtr<GaugeModifier>(nullptr);

    /**
     * @tc.steps: step2. call the function SetNodePaintMethod.
     */
    paintWrapper->SetNodePaintMethod(paintMethod);
    paintWrapper->FlushRender();
    auto foregroundModifier =
        AceType::DynamicCast<ForegroundModifier>(paintMethod->GetForegroundModifier(AceType::RawPtr(paintWrapper)));
    EXPECT_NE(foregroundModifier->extensionHandler_, nullptr);
}

/**
 * @tc.name: PaintWrapperTest003
 * @tc.desc: Test cast to PaintWrapper
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, PaintWrapperTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a framenode and paintwrapper.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<ImagePattern>());
    RefPtr<ImagePattern> pattern = AceType::DynamicCast<ImagePattern>(frameNode->GetPattern());
    pattern->image_ = AceType::MakeRefPtr<NG::MockCanvasImage>();
    auto paintMethod = pattern->CreateNodePaintMethod();
    auto imageMethod = AceType::DynamicCast<ImagePaintMethod>(paintMethod);
    imageMethod->canvasImage_ = AceType::MakeRefPtr<NG::MockCanvasImage>();
    RefPtr<ImageRenderProperty> paintProperty = AceType::MakeRefPtr<ImageRenderProperty>();
    RefPtr<RenderContext> renderContext = AceType::MakeRefPtr<RenderContext>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    paintWrapper->extensionHandler_ = AceType::MakeRefPtr<ExtensionHandler>();
    auto imageModifier = imageMethod->GetOverlayModifier(AceType::RawPtr(paintWrapper));
    imageModifier = AceType::MakeRefPtr<ImageOverlayModifier>(Color::BLACK);

    /**
     * @tc.steps: step2. call the function SetNodePaintMethod.
     */
    paintWrapper->SetNodePaintMethod(imageMethod);
    paintWrapper->FlushRender();
    paintWrapper->FlushOverlayModifier();
    auto overlayModifier =
        AceType::DynamicCast<OverlayModifier>(imageMethod->GetOverlayModifier(AceType::RawPtr(paintWrapper)));
    EXPECT_NE(overlayModifier->extensionHandler_, nullptr);
}

/**
 * @tc.name: PaintWrapperTest004
 * @tc.desc: Test cast to PaintWrapper
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, PaintWrapperTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a framenode and paintwrapper.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<ListPattern>());
    auto pattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    auto paintMethod = pattern->CreateNodePaintMethod();
    RefPtr<ScrollablePaintProperty> paintProperty;
    RefPtr<RenderContext> renderContext = AceType::MakeRefPtr<RenderContext>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    paintWrapper->extensionHandler_ = nullptr;
    auto listModifier = paintMethod->GetContentModifier(AceType::RawPtr(paintWrapper));
    listModifier = AceType::MakeRefPtr<ListContentModifier>(OffsetF(1.0, 1.0), SizeF(1.0, 1.0));

    /**
     * @tc.steps: step2. call the function SetNodePaintMethod.
     */
    paintWrapper->SetNodePaintMethod(paintMethod);
    paintWrapper->FlushRender();
    auto contentModifier =
        AceType::DynamicCast<ContentModifier>(paintMethod->GetContentModifier(AceType::RawPtr(paintWrapper)));
    EXPECT_EQ(contentModifier->extensionHandler_, nullptr);
}

/**
 * @tc.name: PaintWrapperTest005
 * @tc.desc: Test cast to PaintWrapper
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, PaintWrapperTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a framenode and paintwrapper.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<GaugePattern>());
    RefPtr<GaugePattern> pattern = AceType::DynamicCast<GaugePattern>(frameNode->GetPattern());
    pattern->gaugeModifier_ = AceType::MakeRefPtr<GaugeModifier>(nullptr);
    auto paintMethod = pattern->CreateNodePaintMethod();
    RefPtr<GaugePaintProperty> paintProperty;
    RefPtr<RenderContext> renderContext = AceType::MakeRefPtr<RenderContext>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    paintWrapper->extensionHandler_ = nullptr;
    auto context = paintWrapper->renderContext_.Upgrade();
    context->UpdateAccessibilityFocus(true);
    auto gaugeModifier = paintMethod->GetForegroundModifier(AceType::RawPtr(paintWrapper));
    gaugeModifier = AceType::MakeRefPtr<GaugeModifier>(nullptr);

    /**
     * @tc.steps: step2. call the function SetNodePaintMethod.
     */
    paintWrapper->SetNodePaintMethod(paintMethod);
    paintWrapper->FlushRender();
    auto foregroundModifier =
        AceType::DynamicCast<ForegroundModifier>(paintMethod->GetForegroundModifier(AceType::RawPtr(paintWrapper)));
    EXPECT_EQ(foregroundModifier->extensionHandler_, nullptr);
}

/**
 * @tc.name: PaintWrapperTest006
 * @tc.desc: Test cast to PaintWrapper
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerTestNg, PaintWrapperTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a framenode and paintwrapper.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<ImagePattern>());
    RefPtr<ImagePattern> pattern = AceType::DynamicCast<ImagePattern>(frameNode->GetPattern());
    pattern->image_ = AceType::MakeRefPtr<NG::MockCanvasImage>();
    auto paintMethod = pattern->CreateNodePaintMethod();
    auto imageMethod = AceType::DynamicCast<ImagePaintMethod>(paintMethod);
    imageMethod->canvasImage_ = AceType::MakeRefPtr<NG::MockCanvasImage>();
    RefPtr<ImageRenderProperty> paintProperty = AceType::MakeRefPtr<ImageRenderProperty>();
    RefPtr<RenderContext> renderContext = AceType::MakeRefPtr<RenderContext>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    paintWrapper->extensionHandler_ = nullptr;
    auto imageModifier = imageMethod->GetOverlayModifier(AceType::RawPtr(paintWrapper));
    imageModifier = AceType::MakeRefPtr<ImageOverlayModifier>(Color::BLACK);

    /**
     * @tc.steps: step2. call the function SetNodePaintMethod.
     */
    paintWrapper->SetNodePaintMethod(imageMethod);
    paintWrapper->FlushRender();
    auto overlayModifier =
        AceType::DynamicCast<OverlayModifier>(imageMethod->GetOverlayModifier(AceType::RawPtr(paintWrapper)));
    EXPECT_EQ(overlayModifier->extensionHandler_, nullptr);
}
} // namespace OHOS::Ace::NG
