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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/node_container/node_container_layout_algorithm.h"
#include "core/components_ng/pattern/node_container/node_container_model_ng.h"
#include "core/components_ng/pattern/node_container/node_container_pattern.h"

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

} // namespace OHOS::Ace::NG
