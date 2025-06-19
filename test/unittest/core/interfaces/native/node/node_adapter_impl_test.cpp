/*
 * Copyright (c) 2025 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include "test/mock/core/pattern/mock_pattern.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/interfaces/native/node/node_adapter_impl.h"
#include "core/interfaces/arkoala/arkoala_api.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto node = MakeRefPtr<TestNode>(nodeId);
        return node;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
    ~TestNode() override = default;
};
}
class NodeAdapterImplTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: AttachHostNode001
 * @tc.desc: handle is null, AttachHostNode return true.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAdapterImplTest, AttachHostNode001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a frameNode.
     */
    const ArkUINodeAdapterAPI* node = NodeAdapter::GetNodeAdapterAPI();
    ASSERT_NE(node, nullptr);
    ArkUINodeAdapterHandle handle = nullptr;
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode1, nullptr);
    ArkUINodeHandle host = reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(frameNode1));
    /**
     * @tc.steps2: handle is null, the result is true.
     * @tc.expected: true
     */
    auto attachResult = node->attachHostNode(handle, host);
    EXPECT_TRUE(attachResult);
}

/**
 * @tc.name: AttachHostNode002
 * @tc.desc: host is null, AttachHostNode return true.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAdapterImplTest, AttachHostNode002, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a handle.
     */
    const ArkUINodeAdapterAPI* node = NodeAdapter::GetNodeAdapterAPI();
    ASSERT_NE(node, nullptr);
    ArkUINodeAdapterHandle handle = node->create();
    ArkUINodeHandle host = nullptr;

    /**
     * @tc.steps2: handle is null, the result is true.
     * @tc.expected: true
     */
    auto attachResult = node->attachHostNode(handle, host);
    EXPECT_TRUE(attachResult);
}

/**
 * @tc.name: AttachHostNode003
 * @tc.desc: OnAttachAdapter return true, AttachHostNode return true.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAdapterImplTest, AttachHostNode003, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a handle.
     */
    const ArkUINodeAdapterAPI* node = NodeAdapter::GetNodeAdapterAPI();
    ASSERT_NE(node, nullptr);
    ArkUINodeAdapterHandle handle = node->create();
    auto frameNode1 = FrameNode::GetOrCreateFrameNode(
        V2::WATERFLOW_ETS_TAG, 2, []() { return AceType::MakeRefPtr<WaterFlowPattern>(); });
    ASSERT_NE(frameNode1, nullptr);
    ArkUINodeHandle host = reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(frameNode1));

    /**
     * @tc.steps2: OnAttachAdapter return true, the result is true.
     * @tc.expected: true
     */
    auto attachResult = node->attachHostNode(handle, host);
    EXPECT_TRUE(attachResult);
}

/**
 * @tc.name: AttachHostNode004
 * @tc.desc: OnAttachAtapper returns true, frameNode has no child node, and AttachHostNode returns false.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAdapterImplTest, AttachHostNode004, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a handle.
     */
    const ArkUINodeAdapterAPI* node = NodeAdapter::GetNodeAdapterAPI();
    ASSERT_NE(node, nullptr);
    ArkUINodeAdapterHandle handle = node->create();
    auto frameNode1 = FrameNode::CreateFrameNode("parent", 1, AceType::MakeRefPtr<Pattern>());
    ArkUINodeHandle host = reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(frameNode1));

    /**
     * @tc.steps2: OnAttachAtapper is true, frameNode has no child node.
     * @tc.expected: true
     */
    auto attachResult = node->attachHostNode(handle, host);
    EXPECT_TRUE(attachResult);
}

/**
 * @tc.name: AttachHostNode005
 * @tc.desc: OnAttachAtapper returns true, frameNode has child node, and AttachHostNode returns false.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAdapterImplTest, AttachHostNode005, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a handle.
     */
    const ArkUINodeAdapterAPI* node = NodeAdapter::GetNodeAdapterAPI();
    ASSERT_NE(node, nullptr);
    ArkUINodeAdapterHandle handle = node->create();
    RefPtr<FrameNode> frameNode1 = FrameNode::CreateFrameNode("parent", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> frameNode2 = FrameNode::CreateFrameNode("child1", 2, AceType::MakeRefPtr<Pattern>());
    frameNode1->AddChild(frameNode2);
    ArkUINodeHandle host = reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(frameNode1));

    /**
     * @tc.steps2: OnAttachAtapper is true, frameNode has child node.
     * @tc.expected: false
     */
    auto attachResult = node->attachHostNode(handle, host);
    EXPECT_FALSE(attachResult);
}

/**
 * @tc.name: AttachHostNode006
 * @tc.desc: OnAttachAtapper returns false, frameNode has child exist lazyForEach node.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAdapterImplTest, AttachHostNode006, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a handle.
     */
    const ArkUINodeAdapterAPI* node = NodeAdapter::GetNodeAdapterAPI();
    ASSERT_NE(node, nullptr);
    ArkUINodeAdapterHandle handle = node->create();
    RefPtr<FrameNode> frameNode1 = FrameNode::CreateFrameNode("parent", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<UINode> frameNode2 = NG::LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    frameNode1->AddChild(frameNode2);
    ArkUINodeHandle host = reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(frameNode1));

    /**
     * @tc.steps2: OnAttachAtapper is false, frameNode child exist lazyForEach node.
     * @tc.expected: false
     */
    auto attachResult = node->attachHostNode(handle, host);
    EXPECT_FALSE(attachResult);
}

/**
 * @tc.name: DetachHostNode001
 * @tc.desc: host is null, DetachHostNode does not perform any operations.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAdapterImplTest, DetachHostNode001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a frameNode.
     */
    const ArkUINodeAdapterAPI* node = NodeAdapter::GetNodeAdapterAPI();
    ASSERT_NE(node, nullptr);
    ArkUINodeHandle host = nullptr;
    /**
     * @tc.steps2: handle is null, the result is true.
     * @tc.expected: true
     */
    node->detachHostNode(host);
}

/**
 * @tc.name: DetachHostNode002
 * @tc.desc: When the child node LazyForEach, DetachHostNode moves out the child node.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAdapterImplTest, DetachHostNode002, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a frameNode.
     */
    const ArkUINodeAdapterAPI* node = NodeAdapter::GetNodeAdapterAPI();
    ASSERT_NE(node, nullptr);
    ArkUINodeAdapterHandle handle = node->create();
    ASSERT_NE(handle, nullptr);
    RefPtr<FrameNode> frameNode1 = FrameNode::CreateFrameNode("parent", 1, AceType::MakeRefPtr<Pattern>());
    ArkUINodeHandle host = reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(frameNode1));
    /**
     * @tc.steps2: OnAttachAtapper.
     * @tc.expected: true
     */
    auto attachResult = node->attachHostNode(handle, host);
    EXPECT_TRUE(attachResult);
    /**
     * @tc.steps3: DetachHostNode.
     * @tc.expected: DetachHostNode moves out the child node.
     */
    node->detachHostNode(host);
}

/**
 * @tc.name: DetachHostNode003
 * @tc.desc: When the child node is not LazyForEach, DetachHostNode do nothing.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAdapterImplTest, DetachHostNode003, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a frameNode.
     */
    const ArkUINodeAdapterAPI* node = NodeAdapter::GetNodeAdapterAPI();
    ASSERT_NE(node, nullptr);
    ArkUINodeAdapterHandle handle = node->create();
    ASSERT_NE(handle, nullptr);
    RefPtr<FrameNode> frameNode1 = FrameNode::CreateFrameNode("parent", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> frameNode2 = FrameNode::CreateFrameNode("child1", 2, AceType::MakeRefPtr<Pattern>());
    frameNode1->AddChild(frameNode2);
    ArkUINodeHandle host = reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(frameNode1));
    /**
     * @tc.steps2: DetachHostNode.
     * @tc.expected: DetachHostNode not moves out the child node.
     */
    node->detachHostNode(host);
}

/**
 * @tc.name: DetachHostNode004
 * @tc.desc: The first node is not a FrameNode, DetachHostNode do nothing.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAdapterImplTest, DetachHostNode004, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a frameNode.
     */
    const ArkUINodeAdapterAPI* node = NodeAdapter::GetNodeAdapterAPI();
    ASSERT_NE(node, nullptr);
    ArkUINodeAdapterHandle handle = node->create();
    ASSERT_NE(handle, nullptr);
    auto testNode = TestNode::CreateTestNode(1);
    RefPtr<UINode> frameNode2 = NG::LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    testNode->AddChild(frameNode2);
    ArkUINodeHandle host = reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(testNode));
    /**
     * @tc.steps2: OnAttachAtapper.
     * @tc.expected: true
     */
    auto attachResult = node->attachHostNode(handle, host);
    EXPECT_FALSE(attachResult);
    /**
     * @tc.steps3: DetachHostNode.
     * @tc.expected: DetachHostNode do nothing.
     */
    node->detachHostNode(host);
}

/**
 * @tc.name: GetNodeAdapter002
 * @tc.desc: When the child node LazyForEach, return hostHandle.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAdapterImplTest, GetNodeAdapter002, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a frameNode.
     */
    const ArkUINodeAdapterAPI* node = NodeAdapter::GetNodeAdapterAPI();
    ASSERT_NE(node, nullptr);
    ArkUINodeAdapterHandle handle = node->create();
    ASSERT_NE(handle, nullptr);
    RefPtr<FrameNode> frameNode1 = FrameNode::CreateFrameNode("parent", 1, AceType::MakeRefPtr<Pattern>());
    ArkUINodeHandle host = reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(frameNode1));
    /**
     * @tc.steps2: OnAttachAtapper.
     * @tc.expected: true
     */
    auto attachResult = node->attachHostNode(handle, host);
    EXPECT_TRUE(attachResult);
    /**
     * @tc.steps3: GetNodeAdapter.
     * @tc.expected: GetNodeAdapter hostHandle.
     */
    auto hostHandle = node->getNodeAdapter(host);
    EXPECT_EQ(hostHandle, handle);
}

/**
 * @tc.name: GetNodeAdapter003
 * @tc.desc: When the child node not is LazyForEach, return hostHandle nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAdapterImplTest, GetNodeAdapter003, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a frameNode.
     */
    const ArkUINodeAdapterAPI* node = NodeAdapter::GetNodeAdapterAPI();
    ASSERT_NE(node, nullptr);
    ArkUINodeAdapterHandle handle = node->create();
    ASSERT_NE(handle, nullptr);
    RefPtr<FrameNode> frameNode1 = FrameNode::CreateFrameNode("parent", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> frameNode2 = FrameNode::CreateFrameNode("child1", 2, AceType::MakeRefPtr<Pattern>());
    frameNode1->AddChild(frameNode2);
    ArkUINodeHandle host = reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(frameNode1));
    /**
     * @tc.steps2: GetNodeAdapter.
     * @tc.expected: nullptr.
     */
    auto hostHandle = node->getNodeAdapter(host);
    EXPECT_EQ(hostHandle, nullptr);
}

/**
 * @tc.name: GetNodeAdapter004
 * @tc.desc: When the child node not is LazyForEach, return hostHandle nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAdapterImplTest, GetNodeAdapter004, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a frameNode.
     */
    const ArkUINodeAdapterAPI* node = NodeAdapter::GetNodeAdapterAPI();
    ASSERT_NE(node, nullptr);
    ArkUINodeAdapterHandle handle = node->create();
    ASSERT_NE(handle, nullptr);
    auto testNode = TestNode::CreateTestNode(1);
    RefPtr<UINode> frameNode2 = NG::LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    testNode->AddChild(frameNode2);
    ArkUINodeHandle host = reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(testNode));
    /**
     * @tc.steps2: OnAttachAtapper.
     * @tc.expected: true
     */
    auto attachResult = node->attachHostNode(handle, host);
    EXPECT_FALSE(attachResult);
    /**
     * @tc.steps3: GetNodeAdapter.
     * @tc.expected: nullptr.
     */
    auto hostHandle = node->getNodeAdapter(host);
    EXPECT_EQ(hostHandle, nullptr);
}
} // namespace OHOS::Ace::NG
