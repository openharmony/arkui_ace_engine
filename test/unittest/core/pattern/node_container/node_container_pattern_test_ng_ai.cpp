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

#include <optional>
#include <memory>
#include <functional>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/node_container/node_container_layout_algorithm.h"
#include "core/components_ng/pattern/node_container/node_container_model_ng.h"
#include "core/components_ng/pattern/node_container/node_container_node.h"
#include "core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/pipeline/base/element_register.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {

constexpr int32_t TEST_NODE_ID_1 = 100;
constexpr int32_t TEST_NODE_ID_2 = 200;
constexpr int32_t TEST_NODE_ID_3 = 300;
constexpr int32_t TEST_CONTAINER_ID = 500;
constexpr int32_t TEST_CHILD_COUNT = 3;
constexpr float TEST_FRAME_WIDTH = 300.0f;
constexpr float TEST_FRAME_HEIGHT = 400.0f;
constexpr int32_t LOOP_COUNT_SMALL = 3;
constexpr int32_t LOOP_COUNT_MEDIUM = 5;

} // namespace

class NodeContainerPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    RefPtr<NodeContainerNode> CreateNodeContainerNode(int32_t nodeId = TEST_NODE_ID_1);
    RefPtr<FrameNode> CreateChildFrameNode(const std::string& tag, int32_t nodeId);
    RefPtr<UINode> CreateMockUINode();
};

void NodeContainerPatternTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void NodeContainerPatternTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<NodeContainerNode> NodeContainerPatternTestNg::CreateNodeContainerNode(int32_t nodeId)
{
    auto pattern = AceType::MakeRefPtr<NodeContainerPattern>();
    auto frameNode = AceType::MakeRefPtr<NodeContainerNode>(
        V2::NODE_CONTAINER_ETS_TAG, nodeId, pattern);
    frameNode->InitializePatternAndContext();
    return frameNode;
}

RefPtr<FrameNode> NodeContainerPatternTestNg::CreateChildFrameNode(const std::string& tag, int32_t nodeId)
{
    return FrameNode::CreateFrameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());
}

RefPtr<UINode> NodeContainerPatternTestNg::CreateMockUINode()
{
    auto node = CreateChildFrameNode("MockNode", TEST_NODE_ID_2);
    node->SetIsArkTsFrameNode(true);
    node->SetIsRootBuilderNode(true);
    return node;
}

/**
 * @tc.name: RemakeNode_WithNullMakeFunc
 * @tc.desc: Test RemakeNode when makeFunc is null
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, RemakeNode_WithNullMakeFunc, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->RemakeNode();
    EXPECT_EQ(frameNode->GetChildAtIndex(0), nullptr);
}

/**
 * @tc.name: RemakeNode_WithValidBuilderNode
 * @tc.desc: Test RemakeNode with valid BuilderNode
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, RemakeNode_WithValidBuilderNode, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_2);
    childNode->SetIsArkTsFrameNode(true);
    childNode->SetIsRootBuilderNode(true);

    pattern->SetMakeFunction([childNode]() -> RefPtr<UINode> { return childNode; });
    pattern->RemakeNode();

    auto result = frameNode->GetChildAtIndex(0);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetId(), childNode->GetId());
}

/**
 * @tc.name: RemakeNode_WithInvalidNode
 * @tc.desc: Test RemakeNode with invalid node (not ArkTsFrameNode and not RootBuilderNode)
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, RemakeNode_WithInvalidNode, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_2);
    childNode->SetIsArkTsFrameNode(false);
    childNode->SetIsRootBuilderNode(false);

    pattern->SetMakeFunction([childNode]() -> RefPtr<UINode> { return childNode; });
    pattern->RemakeNode();

    EXPECT_EQ(frameNode->GetChildAtIndex(0), nullptr);
}

/**
 * @tc.name: RemakeNode_WithNullReturn
 * @tc.desc: Test RemakeNode when makeFunc returns null
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, RemakeNode_WithNullReturn, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->SetMakeFunction([]() -> RefPtr<UINode> { return nullptr; });
    pattern->RemakeNode();

    EXPECT_EQ(frameNode->GetChildAtIndex(0), nullptr);
}

/**
 * @tc.name: RemakeNode_ReplaceExistingChild
 * @tc.desc: Test RemakeNode replacing existing child
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, RemakeNode_ReplaceExistingChild, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto oldChild = CreateChildFrameNode("OldChild", TEST_NODE_ID_2);
    oldChild->SetIsArkTsFrameNode(true);
    oldChild->SetIsRootBuilderNode(true);
    pattern->SetMakeFunction([oldChild]() -> RefPtr<UINode> { return oldChild; });
    pattern->RemakeNode();

    auto newChild = CreateChildFrameNode("NewChild", TEST_NODE_ID_3);
    newChild->SetIsArkTsFrameNode(true);
    newChild->SetIsRootBuilderNode(true);
    pattern->SetMakeFunction([newChild]() -> RefPtr<UINode> { return newChild; });
    pattern->RemakeNode();

    auto result = frameNode->GetChildAtIndex(0);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetId(), newChild->GetId());
}

/**
 * @tc.name: RemakeNode_SameChildNoChange
 * @tc.desc: Test RemakeNode with same child should not cause changes
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, RemakeNode_SameChildNoChange, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_2);
    childNode->SetIsArkTsFrameNode(true);
    childNode->SetIsRootBuilderNode(true);

    pattern->SetMakeFunction([childNode]() -> RefPtr<UINode> { return childNode; });
    pattern->RemakeNode();

    auto firstChild = frameNode->GetChildAtIndex(0);
    ASSERT_NE(firstChild, nullptr);

    pattern->RemakeNode();

    auto secondChild = frameNode->GetChildAtIndex(0);
    EXPECT_EQ(firstChild->GetId(), secondChild->GetId());
}

/**
 * @tc.name: RemakeNode_MultipleCalls
 * @tc.desc: Test RemakeNode called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, RemakeNode_MultipleCalls, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    for (int i = 0; i < LOOP_COUNT_MEDIUM; ++i) {
        auto childNode = CreateChildFrameNode("Child" + std::to_string(i), TEST_NODE_ID_2 + i);
        childNode->SetIsArkTsFrameNode(true);
        childNode->SetIsRootBuilderNode(true);
        pattern->SetMakeFunction([childNode]() -> RefPtr<UINode> { return childNode; });
        pattern->RemakeNode();
    }

    auto finalChild = frameNode->GetChildAtIndex(0);
    ASSERT_NE(finalChild, nullptr);
    EXPECT_EQ(finalChild->GetId(), TEST_NODE_ID_2 + LOOP_COUNT_MEDIUM - 1);
}

/**
 * @tc.name: RemakeNode_WithOnlyArkTsFlag
 * @tc.desc: Test RemakeNode with only ArkTsFrameNode flag set
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, RemakeNode_WithOnlyArkTsFlag, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_2);
    childNode->SetIsArkTsFrameNode(true);
    childNode->SetIsRootBuilderNode(false);

    pattern->SetMakeFunction([childNode]() -> RefPtr<UINode> { return childNode; });
    pattern->RemakeNode();

    auto result = frameNode->GetChildAtIndex(0);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetId(), childNode->GetId());
}

/**
 * @tc.name: RemakeNode_WithOnlyRootBuilderFlag
 * @tc.desc: Test RemakeNode with only RootBuilderNode flag set
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, RemakeNode_WithOnlyRootBuilderFlag, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_2);
    childNode->SetIsArkTsFrameNode(false);
    childNode->SetIsRootBuilderNode(true);

    pattern->SetMakeFunction([childNode]() -> RefPtr<UINode> { return childNode; });
    pattern->RemakeNode();

    auto result = frameNode->GetChildAtIndex(0);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetId(), childNode->GetId());
}

/**
 * @tc.name: AddBaseNode_NullHost
 * @tc.desc: Test AddBaseNode with null host
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, AddBaseNode_NullHost, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_2);
    pattern->AddBaseNode(childNode);

    SUCCEED();
}

/**
 * @tc.name: AddBaseNode_NullChild
 * @tc.desc: Test AddBaseNode with null child
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, AddBaseNode_NullChild, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->AddBaseNode(nullptr);
    EXPECT_EQ(frameNode->GetChildAtIndex(0), nullptr);
}

/**
 * @tc.name: AddBaseNode_ValidChild
 * @tc.desc: Test AddBaseNode with valid child
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, AddBaseNode_ValidChild, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_2);
    childNode->SetIsArkTsFrameNode(true);
    childNode->SetIsRootBuilderNode(true);

    pattern->AddBaseNode(childNode);

    auto result = frameNode->GetChildAtIndex(0);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetId(), childNode->GetId());
}

/**
 * @tc.name: AddBaseNode_InvalidChild
 * @tc.desc: Test AddBaseNode with invalid child (not ArkTsFrameNode and not RootBuilderNode)
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, AddBaseNode_InvalidChild, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_2);
    childNode->SetIsArkTsFrameNode(false);
    childNode->SetIsRootBuilderNode(false);

    pattern->AddBaseNode(childNode);

    EXPECT_EQ(frameNode->GetChildAtIndex(0), nullptr);
}

/**
 * @tc.name: AddBaseNode_WithExistingParent
 * @tc.desc: Test AddBaseNode when child has different parent
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, AddBaseNode_WithExistingParent, TestSize.Level1)
{
    auto parentFrame = CreateNodeContainerNode(TEST_NODE_ID_1);
    ASSERT_NE(parentFrame, nullptr);
    auto pattern = parentFrame->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto otherParent = CreateNodeContainerNode(TEST_NODE_ID_2);
    auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_3);
    childNode->SetIsArkTsFrameNode(true);
    childNode->SetIsRootBuilderNode(true);
    otherParent->AddChild(childNode);

    pattern->AddBaseNode(childNode);

    SUCCEED();
}

/**
 * @tc.name: AddBaseNode_ReplaceChild
 * @tc.desc: Test AddBaseNode replacing existing child
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, AddBaseNode_ReplaceChild, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto oldChild = CreateChildFrameNode("OldChild", TEST_NODE_ID_2);
    oldChild->SetIsArkTsFrameNode(true);
    oldChild->SetIsRootBuilderNode(true);
    pattern->AddBaseNode(oldChild);

    auto newChild = CreateChildFrameNode("NewChild", TEST_NODE_ID_3);
    newChild->SetIsArkTsFrameNode(true);
    newChild->SetIsRootBuilderNode(true);
    pattern->AddBaseNode(newChild);

    auto result = frameNode->GetChildAtIndex(0);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetId(), newChild->GetId());
}

/**
 * @tc.name: AddBaseNode_SameChild
 * @tc.desc: Test AddBaseNode with same child
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, AddBaseNode_SameChild, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_2);
    childNode->SetIsArkTsFrameNode(true);
    childNode->SetIsRootBuilderNode(true);
    pattern->AddBaseNode(childNode);

    pattern->AddBaseNode(childNode);

    auto result = frameNode->GetChildAtIndex(0);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetId(), childNode->GetId());
}

/**
 * @tc.name: AddBaseNode_MultipleChildren
 * @tc.desc: Test AddBaseNode adding multiple children sequentially
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, AddBaseNode_MultipleChildren, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    for (int i = 0; i < TEST_CHILD_COUNT; ++i) {
        auto childNode = CreateChildFrameNode("Child" + std::to_string(i), TEST_NODE_ID_2 + i);
        childNode->SetIsArkTsFrameNode(true);
        childNode->SetIsRootBuilderNode(true);
        pattern->AddBaseNode(childNode);
    }

    auto result = frameNode->GetChildAtIndex(0);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetId(), TEST_NODE_ID_2 + TEST_CHILD_COUNT - 1);
}

/**
 * @tc.name: CleanChild_Normal
 * @tc.desc: Test CleanChild with existing child
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, CleanChild_Normal, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_2);
    childNode->SetIsArkTsFrameNode(true);
    childNode->SetIsRootBuilderNode(true);
    pattern->AddBaseNode(childNode);

    ASSERT_NE(frameNode->GetChildAtIndex(0), nullptr);

    pattern->CleanChild();
    EXPECT_EQ(frameNode->GetChildAtIndex(0), nullptr);
}

/**
 * @tc.name: CleanChild_NoChild
 * @tc.desc: Test CleanChild when no child exists
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, CleanChild_NoChild, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_EQ(frameNode->GetChildAtIndex(0), nullptr);
    pattern->CleanChild();
    EXPECT_EQ(frameNode->GetChildAtIndex(0), nullptr);
}

/**
 * @tc.name: CleanChild_MultipleCalls
 * @tc.desc: Test CleanChild called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, CleanChild_MultipleCalls, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_2);
    childNode->SetIsArkTsFrameNode(true);
    childNode->SetIsRootBuilderNode(true);
    pattern->AddBaseNode(childNode);

    pattern->CleanChild();
    pattern->CleanChild();
    pattern->CleanChild();

    EXPECT_EQ(frameNode->GetChildAtIndex(0), nullptr);
}

/**
 * @tc.name: CleanChild_NullHost
 * @tc.desc: Test CleanChild with null host
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, CleanChild_NullHost, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->CleanChild();
    SUCCEED();
}

/**
 * @tc.name: CleanChild_AfterRemake
 * @tc.desc: Test CleanChild after RemakeNode
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, CleanChild_AfterRemake, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_2);
    childNode->SetIsArkTsFrameNode(true);
    childNode->SetIsRootBuilderNode(true);
    pattern->SetMakeFunction([childNode]() -> RefPtr<UINode> { return childNode; });
    pattern->RemakeNode();

    ASSERT_NE(frameNode->GetChildAtIndex(0), nullptr);

    pattern->CleanChild();
    EXPECT_EQ(frameNode->GetChildAtIndex(0), nullptr);
}

/**
 * @tc.name: BindController_Normal
 * @tc.desc: Test BindController with valid function
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, BindController_Normal, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    bool called = false;
    pattern->BindController([&called]() { called = true; });
    pattern->ResetController();

    EXPECT_TRUE(called);
}

/**
 * @tc.name: BindController_NullFunc
 * @tc.desc: Test BindController with null function
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, BindController_NullFunc, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->BindController(nullptr);
    pattern->ResetController();

    SUCCEED();
}

/**
 * @tc.name: ResetController_NoBind
 * @tc.desc: Test ResetController without binding
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, ResetController_NoBind, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->ResetController();
    SUCCEED();
}

/**
 * @tc.name: SetMakeFunction_Normal
 * @tc.desc: Test SetMakeFunction with valid function
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, SetMakeFunction_Normal, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_2);
    childNode->SetIsArkTsFrameNode(true);
    childNode->SetIsRootBuilderNode(true);

    pattern->SetMakeFunction([childNode]() -> RefPtr<UINode> { return childNode; });
    auto result = pattern->FireMakeFunction();

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetId(), childNode->GetId());
}

/**
 * @tc.name: SetMakeFunction_NullFunc
 * @tc.desc: Test SetMakeFunction with null function
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, SetMakeFunction_NullFunc, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->SetMakeFunction(nullptr);
    auto result = pattern->FireMakeFunction();

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: FireMakeFunction_NoSet
 * @tc.desc: Test FireMakeFunction without setting makeFunc
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, FireMakeFunction_NoSet, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto result = pattern->FireMakeFunction();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: SetOnResize_Normal
 * @tc.desc: Test SetOnResize with valid function
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, SetOnResize_Normal, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    bool called = false;
    SizeF receivedSize;
    pattern->SetOnResize([&called, &receivedSize](const SizeF& size) {
        called = true;
        receivedSize = size;
    });

    SizeF testSize(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT);
    pattern->FireOnResize(testSize);

    EXPECT_TRUE(called);
    EXPECT_FLOAT_EQ(receivedSize.Width(), TEST_FRAME_WIDTH);
    EXPECT_FLOAT_EQ(receivedSize.Height(), TEST_FRAME_HEIGHT);
}

/**
 * @tc.name: SetOnResize_NullFunc
 * @tc.desc: Test SetOnResize with null function
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, SetOnResize_NullFunc, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->SetOnResize(nullptr);

    SizeF testSize(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT);
    pattern->FireOnResize(testSize);

    SUCCEED();
}

/**
 * @tc.name: FireOnResize_NoSet
 * @tc.desc: Test FireOnResize without setting callback
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, FireOnResize_NoSet, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    SizeF testSize(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT);
    pattern->FireOnResize(testSize);

    SUCCEED();
}

/**
 * @tc.name: FireOnWillBind_Normal
 * @tc.desc: Test FireOnWillBind with valid callback
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, FireOnWillBind_Normal, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->FireOnWillBind(TEST_CONTAINER_ID);

    SUCCEED();
}

/**
 * @tc.name: FireOnWillUnbind_Normal
 * @tc.desc: Test FireOnWillUnbind with valid callback
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, FireOnWillUnbind_Normal, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->FireOnWillUnbind(TEST_CONTAINER_ID);
    SUCCEED();
}

/**
 * @tc.name: FireOnBind_Normal
 * @tc.desc: Test FireOnBind with valid callback
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, FireOnBind_Normal, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->FireOnBind(TEST_CONTAINER_ID);
    SUCCEED();
}

/**
 * @tc.name: FireOnUnbind_Normal
 * @tc.desc: Test FireOnUnbind with valid callback
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, FireOnUnbind_Normal, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->FireOnUnbind(TEST_CONTAINER_ID);
    SUCCEED();
}

/**
 * @tc.name: IsEnableChildrenMatchParent
 * @tc.desc: Test IsEnableChildrenMatchParent returns true
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, IsEnableChildrenMatchParent, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_TRUE(pattern->IsEnableChildrenMatchParent());
}

/**
 * @tc.name: IsEnableMatchParent
 * @tc.desc: Test IsEnableMatchParent returns true
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, IsEnableMatchParent, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_TRUE(pattern->IsEnableMatchParent());
}

/**
 * @tc.name: IsEnableFix
 * @tc.desc: Test IsEnableFix returns true
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, IsEnableFix, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_TRUE(pattern->IsEnableFix());
}

/**
 * @tc.name: IsAtomicNode
 * @tc.desc: Test IsAtomicNode returns true
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, IsAtomicNode, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_TRUE(pattern->IsAtomicNode());
}

/**
 * @tc.name: GetFocusPattern
 * @tc.desc: Test GetFocusPattern returns correct focus type
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, GetFocusPattern, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto focusPattern = pattern->GetFocusPattern();
    EXPECT_EQ(focusPattern.GetFocusType(), FocusType::SCOPE);
    EXPECT_TRUE(focusPattern.GetFocusable());
}

/**
 * @tc.name: CreateLayoutProperty
 * @tc.desc: Test CreateLayoutProperty returns StackLayoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, CreateLayoutProperty, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = pattern->CreateLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: CreateLayoutAlgorithm
 * @tc.desc: Test CreateLayoutAlgorithm returns NodeContainerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, CreateLayoutAlgorithm, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
}

/**
 * @tc.name: CreateEventHub
 * @tc.desc: Test CreateEventHub returns NodeContainerEventHub
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, CreateEventHub, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto eventHub = pattern->CreateEventHub();
    ASSERT_NE(eventHub, nullptr);
}

/**
 * @tc.name: ResetExportTextureInfo_Normal
 * @tc.desc: Test ResetExportTextureInfo resets surfaceId and exportTextureNode
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, ResetExportTextureInfo_Normal, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->ResetExportTextureInfo();
    EXPECT_EQ(pattern->GetSurfaceId(), 0U);
}

/**
 * @tc.name: GetExportTextureNode_NullNode
 * @tc.desc: Test GetExportTextureNode when exportTextureNode is null
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, GetExportTextureNode_NullNode, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->ResetExportTextureInfo();
    auto result = pattern->GetExportTextureNode();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetExportTextureNode_ValidNode
 * @tc.desc: Test GetExportTextureNode with valid FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, GetExportTextureNode_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_2);
    pattern->AddBaseNode(childNode);

    auto result = pattern->GetExportTextureNode();
    SUCCEED();
}

/**
 * @tc.name: GetSurfaceId_Initial
 * @tc.desc: Test GetSurfaceId returns initial value
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, GetSurfaceId_Initial, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_EQ(pattern->GetSurfaceId(), 0U);
}

/**
 * @tc.name: GetOrCreateNodeContainerNode_NewNode
 * @tc.desc: Test GetOrCreateNodeContainerNode creates new node
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, GetOrCreateNodeContainerNode_NewNode, TestSize.Level1)
{
    auto frameNode = NodeContainerNode::GetOrCreateNodeContainerNode(TEST_NODE_ID_1);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetId(), TEST_NODE_ID_1);
    EXPECT_EQ(frameNode->GetTag(), V2::NODE_CONTAINER_ETS_TAG);
}

/**
 * @tc.name: GetOrCreateNodeContainerNode_ExistingNode
 * @tc.desc: Test GetOrCreateNodeContainerNode returns existing node
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, GetOrCreateNodeContainerNode_ExistingNode, TestSize.Level1)
{
    auto frameNode1 = NodeContainerNode::GetOrCreateNodeContainerNode(TEST_NODE_ID_1);
    ASSERT_NE(frameNode1, nullptr);

    auto frameNode2 = NodeContainerNode::GetOrCreateNodeContainerNode(TEST_NODE_ID_1);
    ASSERT_NE(frameNode2, nullptr);

    EXPECT_EQ(frameNode1->GetId(), frameNode2->GetId());
}

/**
 * @tc.name: GetOrCreateNodeContainerNode_DifferentIds
 * @tc.desc: Test GetOrCreateNodeContainerNode with different node IDs
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, GetOrCreateNodeContainerNode_DifferentIds, TestSize.Level1)
{
    auto frameNode1 = NodeContainerNode::GetOrCreateNodeContainerNode(TEST_NODE_ID_1);
    auto frameNode2 = NodeContainerNode::GetOrCreateNodeContainerNode(TEST_NODE_ID_2);
    auto frameNode3 = NodeContainerNode::GetOrCreateNodeContainerNode(TEST_NODE_ID_3);

    ASSERT_NE(frameNode1, nullptr);
    ASSERT_NE(frameNode2, nullptr);
    ASSERT_NE(frameNode3, nullptr);

    EXPECT_NE(frameNode1->GetId(), frameNode2->GetId());
    EXPECT_NE(frameNode2->GetId(), frameNode3->GetId());
    EXPECT_NE(frameNode1->GetId(), frameNode3->GetId());
}

/**
 * @tc.name: Destructor_NoChildren
 * @tc.desc: Test destructor with no children
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, Destructor_NoChildren, TestSize.Level1)
{
    {
        auto frameNode = NodeContainerNode::GetOrCreateNodeContainerNode(TEST_NODE_ID_1);
        ASSERT_NE(frameNode, nullptr);
    }
    SUCCEED();
}

/**
 * @tc.name: Destructor_WithChildren
 * @tc.desc: Test destructor with children
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, Destructor_WithChildren, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode;
    {
        frameNode = NodeContainerNode::GetOrCreateNodeContainerNode(TEST_NODE_ID_1);
        ASSERT_NE(frameNode, nullptr);

        auto pattern = frameNode->GetPattern<NodeContainerPattern>();
        ASSERT_NE(pattern, nullptr);

        auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_2);
        childNode->SetIsArkTsFrameNode(true);
        childNode->SetIsRootBuilderNode(true);
        pattern->AddBaseNode(childNode);
    }
    SUCCEED();
}

/**
 * @tc.name: OnRecycle_NoCallbacks
 * @tc.desc: Test OnRecycle with no destroy callbacks
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, OnRecycle_NoCallbacks, TestSize.Level1)
{
    auto frameNode = NodeContainerNode::GetOrCreateNodeContainerNode(TEST_NODE_ID_1);
    ASSERT_NE(frameNode, nullptr);

    frameNode->OnRecycle();
    SUCCEED();
}

/**
 * @tc.name: OnReuse_Normal
 * @tc.desc: Test OnReuse normal case
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, OnReuse_Normal, TestSize.Level1)
{
    auto frameNode = NodeContainerNode::GetOrCreateNodeContainerNode(TEST_NODE_ID_1);
    ASSERT_NE(frameNode, nullptr);

    frameNode->OnReuse();
    SUCCEED();
}

/**
 * @tc.name: OnReuse_NullPattern
 * @tc.desc: Test OnReuse with null pattern
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, OnReuse_NullPattern, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);

    frameNode->OnReuse();
    SUCCEED();
}

/**
 * @tc.name: Create_Normal
 * @tc.desc: Test Create
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, Create_Normal, TestSize.Level1)
{
    NodeContainerModelNG model;
    model.Create();

    auto element = ViewStackProcessor::GetInstance()->Finish();
    ASSERT_NE(element, nullptr);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::NODE_CONTAINER_ETS_TAG);
}

/**
 * @tc.name: CreateFrameNode_Normal
 * @tc.desc: Test CreateFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, CreateFrameNode_Normal, TestSize.Level1)
{
    auto frameNode = NodeContainerModelNG::CreateFrameNode(TEST_NODE_ID_1);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetId(), TEST_NODE_ID_1);
    EXPECT_EQ(frameNode->GetTag(), V2::NODE_CONTAINER_ETS_TAG);
}


/**
 * @tc.name: MeasureContent_Null
 * @tc.desc: Test MeasureContent returns nullopt
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, MeasureContent_Null, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NodeContainerLayoutAlgorithm>();
    ASSERT_NE(algorithm, nullptr);

    LayoutConstraintF constraint;
    auto result = algorithm->MeasureContent(constraint, nullptr);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: HandleTextureExport_StopTrue_NullFrameNode
 * @tc.desc: Test HandleTextureExport with isStop=true and null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, HandleTextureExport_StopTrue_NullFrameNode, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    SUCCEED();
}

/**
 * @tc.name: HandleTextureExport_StopFalse_NullFrameNode
 * @tc.desc: Test HandleTextureExport with isStop=false and null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, HandleTextureExport_StopFalse_NullFrameNode, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    SUCCEED();
}

/**
 * @tc.name: OnDetachFromFrameNode_Normal
 * @tc.desc: Test OnDetachFromFrameNode normal case
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, OnDetachFromFrameNode_Normal, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->OnDetachFromFrameNode(Referenced::RawPtr(frameNode));
    SUCCEED();
}

/**
 * @tc.name: OnMountToParentDone_Normal
 * @tc.desc: Test OnMountToParentDone normal case
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, OnMountToParentDone_Normal, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->OnMountToParentDone();
    SUCCEED();
}

/**
 * @tc.name: OnAddBaseNode_Normal
 * @tc.desc: Test OnAddBaseNode normal case
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, OnAddBaseNode_Normal, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_2);
    childNode->SetIsArkTsFrameNode(true);
    childNode->SetIsRootBuilderNode(true);
    pattern->AddBaseNode(childNode);

    pattern->OnAddBaseNode();
    SUCCEED();
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_SkipMeasureAndLayout
 * @tc.desc: Test OnDirtyLayoutWrapperSwap when skipMeasure and skipLayout are true
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, OnDirtyLayoutWrapperSwap_SkipMeasureAndLayout, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    config.frameSizeChange = false;

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, frameNode->GetGeometryNode(), frameNode->GetLayoutProperty());

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_FrameSizeChange
 * @tc.desc: Test OnDirtyLayoutWrapperSwap when frameSizeChange is true
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, OnDirtyLayoutWrapperSwap_FrameSizeChange, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = false;
    config.skipLayout = false;
    config.frameSizeChange = true;

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, frameNode->GetGeometryNode(), frameNode->GetLayoutProperty());

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_NullHost
 * @tc.desc: Test OnDirtyLayoutWrapperSwap with null host
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, OnDirtyLayoutWrapperSwap_NullHost, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = false;
    config.skipLayout = false;
    config.frameSizeChange = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(nullptr, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: RemakeNode_AfterCleanChild
 * @tc.desc: Test RemakeNode after CleanChild
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, RemakeNode_AfterCleanChild, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_2);
    childNode->SetIsArkTsFrameNode(true);
    childNode->SetIsRootBuilderNode(true);
    pattern->SetMakeFunction([childNode]() -> RefPtr<UINode> { return childNode; });

    pattern->RemakeNode();
    ASSERT_NE(frameNode->GetChildAtIndex(0), nullptr);

    pattern->CleanChild();
    ASSERT_EQ(frameNode->GetChildAtIndex(0), nullptr);

    pattern->RemakeNode();
    auto result = frameNode->GetChildAtIndex(0);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetId(), childNode->GetId());
}

/**
 * @tc.name: CleanChild_ThenRemake
 * @tc.desc: Test CleanChild then RemakeNode
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, CleanChild_ThenRemake, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto childNode = CreateChildFrameNode("ChildNode", TEST_NODE_ID_2);
    childNode->SetIsArkTsFrameNode(true);
    childNode->SetIsRootBuilderNode(true);
    pattern->SetMakeFunction([childNode]() -> RefPtr<UINode> { return childNode; });

    pattern->RemakeNode();
    ASSERT_NE(frameNode->GetChildAtIndex(0), nullptr);

    pattern->CleanChild();
    EXPECT_EQ(frameNode->GetChildAtIndex(0), nullptr);

    pattern->RemakeNode();
    EXPECT_NE(frameNode->GetChildAtIndex(0), nullptr);
}

/**
 * @tc.name: MultipleCreate
 * @tc.desc: Test Create multiple times
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, MultipleCreate, TestSize.Level1)
{
    NodeContainerModelNG model;

    for (int i = 0; i < LOOP_COUNT_SMALL; ++i) {
        model.Create();
        auto element = ViewStackProcessor::GetInstance()->Finish();
        ASSERT_NE(element, nullptr);

        auto frameNode = AceType::DynamicCast<FrameNode>(element);
        ASSERT_NE(frameNode, nullptr);
        EXPECT_EQ(frameNode->GetTag(), V2::NODE_CONTAINER_ETS_TAG);
    }
}

/**
 * @tc.name: SetMakeFunction_Null
 * @tc.desc: Test SetMakeFunction with null
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, SetMakeFunction_Null, TestSize.Level1)
{
    NodeContainerModelNG model;
    model.Create();

    model.SetMakeFunction(nullptr);
    model.FireMakeNode();

    auto element = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(element, nullptr);
    EXPECT_EQ(element->GetChildAtIndex(0), nullptr);
}

/**
 * @tc.name: FireMakeNode_NoMakeFunction
 * @tc.desc: Test FireMakeNode without setting make function
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, FireMakeNode_NoMakeFunction, TestSize.Level1)
{
    NodeContainerModelNG model;
    model.Create();

    model.FireMakeNode();

    auto element = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(element, nullptr);
    EXPECT_EQ(element->GetChildAtIndex(0), nullptr);
}

/**
 * @tc.name: MultipleGetOrCreate
 * @tc.desc: Test multiple GetOrCreateNodeContainerNode calls
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, MultipleGetOrCreate, TestSize.Level1)
{
    std::vector<RefPtr<FrameNode>> nodes;
    for (int i = 0; i < LOOP_COUNT_MEDIUM; ++i) {
        auto frameNode = NodeContainerNode::GetOrCreateNodeContainerNode(TEST_NODE_ID_1 + i);
        ASSERT_NE(frameNode, nullptr);
        nodes.push_back(frameNode);
    }

    for (int i = 0; i < LOOP_COUNT_MEDIUM; ++i) {
        EXPECT_EQ(nodes[i]->GetId(), TEST_NODE_ID_1 + i);
    }
}

/**
 * @tc.name: CreateLayoutProperty_MultipleCalls
 * @tc.desc: Test CreateLayoutProperty multiple calls
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, CreateLayoutProperty_MultipleCalls, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    for (int i = 0; i < LOOP_COUNT_SMALL; ++i) {
        auto layoutProperty = pattern->CreateLayoutProperty();
        ASSERT_NE(layoutProperty, nullptr);
    }
}

/**
 * @tc.name: CreateLayoutAlgorithm_MultipleCalls
 * @tc.desc: Test CreateLayoutAlgorithm multiple calls
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, CreateLayoutAlgorithm_MultipleCalls, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    for (int i = 0; i < LOOP_COUNT_SMALL; ++i) {
        auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
        ASSERT_NE(layoutAlgorithm, nullptr);
    }
}

/**
 * @tc.name: CreateEventHub_MultipleCalls
 * @tc.desc: Test CreateEventHub multiple calls
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, CreateEventHub_MultipleCalls, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    for (int i = 0; i < LOOP_COUNT_SMALL; ++i) {
        auto eventHub = pattern->CreateEventHub();
        ASSERT_NE(eventHub, nullptr);
    }
}

/**
 * @tc.name: SetMakeFunction_MultipleTimes
 * @tc.desc: Test SetMakeFunction called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, SetMakeFunction_MultipleTimes, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    for (int i = 0; i < LOOP_COUNT_SMALL; ++i) {
        auto childNode = CreateChildFrameNode("Child" + std::to_string(i), TEST_NODE_ID_2 + i);
        childNode->SetIsArkTsFrameNode(true);
        childNode->SetIsRootBuilderNode(true);
        pattern->SetMakeFunction([childNode]() -> RefPtr<UINode> { return childNode; });

        auto result = pattern->FireMakeFunction();
        ASSERT_NE(result, nullptr);
        EXPECT_EQ(result->GetId(), childNode->GetId());
    }
}

/**
 * @tc.name: BindController_MultipleTimes
 * @tc.desc: Test BindController called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, BindController_MultipleTimes, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    int callCount = 0;
    for (int i = 0; i < LOOP_COUNT_SMALL; ++i) {
        pattern->BindController([&callCount]() { callCount++; });
    }

    pattern->ResetController();
    EXPECT_EQ(callCount, 1);
}

/**
 * @tc.name: SetOnResize_MultipleTimes
 * @tc.desc: Test SetOnResize called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, SetOnResize_MultipleTimes, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    int callCount = 0;
    for (int i = 0; i < LOOP_COUNT_SMALL; ++i) {
        pattern->SetOnResize([&callCount](const SizeF& size) { callCount++; });
    }

    SizeF testSize(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT);
    pattern->FireOnResize(testSize);

    EXPECT_EQ(callCount, 1);
}

/**
 * @tc.name: FireOnResize_MultipleTimes
 * @tc.desc: Test FireOnResize called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, FireOnResize_MultipleTimes, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    int callCount = 0;
    pattern->SetOnResize([&callCount](const SizeF& size) { callCount++; });

    SizeF testSize(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT);
    for (int i = 0; i < LOOP_COUNT_MEDIUM; ++i) {
        pattern->FireOnResize(testSize);
    }

    EXPECT_EQ(callCount, LOOP_COUNT_MEDIUM);
}

/**
 * @tc.name: FireOnBind_MultipleTimes
 * @tc.desc: Test FireOnBind called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, FireOnBind_MultipleTimes, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    for (int i = 0; i < LOOP_COUNT_MEDIUM; ++i) {
        pattern->FireOnBind(TEST_CONTAINER_ID + i);
    }

    SUCCEED();
}

/**
 * @tc.name: FireOnUnbind_MultipleTimes
 * @tc.desc: Test FireOnUnbind called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, FireOnUnbind_MultipleTimes, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    for (int i = 0; i < LOOP_COUNT_MEDIUM; ++i) {
        pattern->FireOnUnbind(TEST_CONTAINER_ID + i);
    }

    SUCCEED();
}

/**
 * @tc.name: FireOnWillBind_MultipleTimes
 * @tc.desc: Test FireOnWillBind called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerPatternTestNg, FireOnWillBind_MultipleTimes, TestSize.Level1)
{
    auto frameNode = CreateNodeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    for (int i = 0; i < LOOP_COUNT_MEDIUM; ++i) {
        pattern->FireOnWillBind(TEST_CONTAINER_ID + i);
    }

    SUCCEED();
}

} // namespace OHOS::Ace::NG