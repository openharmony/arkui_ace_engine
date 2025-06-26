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

#include "gtest/gtest.h"

#include "core/common/builder_util.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const std::string TEST_NODE_TAG = "TestNode";
static int32_t UNIQUED_ID_OF_TEST_NODE = 0;
} // namespace
// namespace
class BuilderUtilsTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: BuilderUtilsTest001
 * @tc.desc: Test Func of  IsBuilderRootNode and IsBuilderContainer.
 * @tc.type: FUNC
 */
HWTEST_F(BuilderUtilsTest, BuilderUtilsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create an UINode.
     * @tc.expected: step1. The return value is not null.
     */
    auto firstNode = NG::FrameNode::GetOrCreateFrameNode(
        TEST_NODE_TAG, UNIQUED_ID_OF_TEST_NODE++, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    EXPECT_NE(firstNode, nullptr);
    auto contentSlot = NG::FrameNode::GetOrCreateFrameNode(
        V2::JS_NODE_SLOT_ETS_TAG, UNIQUED_ID_OF_TEST_NODE++, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    EXPECT_NE(contentSlot, nullptr);
    auto nodeContainer = NG::FrameNode::GetOrCreateFrameNode(
        V2::NODE_CONTAINER_ETS_TAG, UNIQUED_ID_OF_TEST_NODE++, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    EXPECT_NE(nodeContainer, nullptr);
    /**
     * @tc.steps: step2. Call IsBuilderRootNode and send nullptr.
     * @tc.expected: step2. The return value as false.
     */
    EXPECT_FALSE(BuilderUtils::IsBuilderRootNode(nullptr));
    /**
     * @tc.steps: step3. Call IsBuilderRootNode and send firstNode.
     * @tc.expected: step3. The return value as false.
     */
    EXPECT_FALSE(BuilderUtils::IsBuilderRootNode(firstNode));
    /**
     * @tc.steps: step4. SetJsBuilderNodeId to firstNode and Call IsBuilderRootNode again.
     * @tc.expected: step4. The return value as true.
     */
    firstNode->SetJsBuilderNodeId(firstNode->GetId());
    EXPECT_TRUE(BuilderUtils::IsBuilderRootNode(firstNode));

    /**
     * @tc.steps: step4. IsBuilderContainer to firstNode.
     * @tc.expected: step4. The return value as false.
     */
    EXPECT_FALSE(BuilderUtils::IsBuilderContainer(firstNode));
    EXPECT_TRUE(BuilderUtils::IsBuilderContainer(contentSlot) && BuilderUtils::IsBuilderContainer(nodeContainer));
}

/**
 * @tc.name: BuilderUtilsTest002
 * @tc.desc: Test GetBuilderNodes.
 * @tc.type: FUNC
 */
HWTEST_F(BuilderUtilsTest, BuilderUtilsTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some UINode. And Set Second Node as BuilderRootNode;
     * @tc.expected: step1. The return value is not null.
     */
    auto firstNode = NG::FrameNode::GetOrCreateFrameNode(
        TEST_NODE_TAG, UNIQUED_ID_OF_TEST_NODE++, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    EXPECT_NE(firstNode, nullptr);
    auto seconedNode = NG::FrameNode::GetOrCreateFrameNode(
        TEST_NODE_TAG, UNIQUED_ID_OF_TEST_NODE++, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    EXPECT_NE(seconedNode, nullptr);
    auto thirdNode = NG::FrameNode::GetOrCreateFrameNode(
        TEST_NODE_TAG, UNIQUED_ID_OF_TEST_NODE++, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    EXPECT_NE(thirdNode, nullptr);
    auto forthNode = NG::FrameNode::GetOrCreateFrameNode(
        TEST_NODE_TAG, UNIQUED_ID_OF_TEST_NODE++, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    EXPECT_NE(forthNode, nullptr);
    auto fifthNode = NG::FrameNode::GetOrCreateFrameNode(
        TEST_NODE_TAG, UNIQUED_ID_OF_TEST_NODE++, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    EXPECT_NE(fifthNode, nullptr);

    /**
     * @tc.steps: step2. Make a tree by the previous Node.
     *├─ firstNode
     *│ ├─ seconedNode (true)
     *│ │  └─ thirdNode (true)
     *│ ├─ forthNode (true)
     *| └─ fifthNode
     */
    firstNode->AddChild(seconedNode);
    seconedNode->AddChild(thirdNode);
    firstNode->AddChild(forthNode);
    firstNode->AddChild(fifthNode);
    seconedNode->SetJsBuilderNodeId(firstNode->GetId());
    thirdNode->SetJsBuilderNodeId(seconedNode->GetId());
    forthNode->SetJsBuilderNodeId(firstNode->GetId());

    /**
     * @tc.steps: step3. Call GetBuilderNodes.
     * @tc.expected: step3. Get the true count of those node.
     */
    std::list<RefPtr<NG::UINode>> nodes;
    BuilderUtils::GetBuilderNodes(nullptr, nodes);
    EXPECT_TRUE(nodes.empty());
    BuilderUtils::GetBuilderNodes(firstNode, nodes);
    EXPECT_EQ(nodes.size(), 2);
    nodes.clear();
    BuilderUtils::GetBuilderNodes(seconedNode, nodes);
    EXPECT_EQ(nodes.size(), 1);
    nodes.clear();
    BuilderUtils::GetBuilderNodes(thirdNode, nodes);
    EXPECT_EQ(nodes.size(), 1);
    nodes.clear();
    BuilderUtils::GetBuilderNodes(forthNode, nodes);
    EXPECT_EQ(nodes.size(), 1);
    nodes.clear();
    BuilderUtils::GetBuilderNodes(fifthNode, nodes);
    EXPECT_TRUE(nodes.empty());
}
} // namespace OHOS::Ace
