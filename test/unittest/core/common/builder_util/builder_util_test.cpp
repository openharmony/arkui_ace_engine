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

#define private public
#define protected public
#include "interfaces/inner_api/ace_kit/src/view/ui_context_impl.h"
#include "test/mock/core/common/mock_frontend.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

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
    auto secondedNode = NG::FrameNode::GetOrCreateFrameNode(
        TEST_NODE_TAG, UNIQUED_ID_OF_TEST_NODE++, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    EXPECT_NE(secondedNode, nullptr);
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
     *│ ├─ secondedNode (true)
     *│ │  └─ thirdNode (true)
     *│ ├─ forthNode (true)
     *| └─ fifthNode
     */
    firstNode->AddChild(secondedNode);
    secondedNode->AddChild(thirdNode);
    firstNode->AddChild(forthNode);
    firstNode->AddChild(fifthNode);
    secondedNode->SetJsBuilderNodeId(firstNode->GetId());
    thirdNode->SetJsBuilderNodeId(secondedNode->GetId());
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
    BuilderUtils::GetBuilderNodes(secondedNode, nodes);
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

    /**
     * @tc.steps: step4. Call GetBuilderNodes when contains CNode.
     * @tc.expected: step4. Get the true count of those node.
     */
    nodes.clear();
    secondedNode->SetJsBuilderNodeId(-1);
    secondedNode->setIsCNode(true);
    BuilderUtils::GetBuilderNodes(firstNode, nodes);
    EXPECT_EQ(nodes.size(), 1);
}

/**
 * @tc.name: BuilderUtilsTest003
 * @tc.desc: Test ClearChildInBuilderContainer.
 * @tc.type: FUNC
 */
HWTEST_F(BuilderUtilsTest, BuilderUtilsTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some UINode. And Set Second Node as BuilderRootNode;
     * @tc.expected: step1. The return value is not null.
     */
    auto firstNode = NG::FrameNode::GetOrCreateFrameNode(
        V2::JS_NODE_SLOT_ETS_TAG, UNIQUED_ID_OF_TEST_NODE++, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    EXPECT_NE(firstNode, nullptr);
    auto secondedNode = NG::FrameNode::GetOrCreateFrameNode(
        TEST_NODE_TAG, UNIQUED_ID_OF_TEST_NODE++, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    EXPECT_NE(secondedNode, nullptr);
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
     *│ ├─ secondedNode (true)
     *│ │  └─ thirdNode (true)
     *│ ├─ forthNode (true)
     *| └─ fifthNode
     */
    firstNode->AddChild(secondedNode);
    secondedNode->AddChild(thirdNode);
    firstNode->AddChild(forthNode);
    firstNode->AddChild(fifthNode);
    secondedNode->SetJsBuilderNodeId(firstNode->GetId());
    thirdNode->SetJsBuilderNodeId(secondedNode->GetId());
    forthNode->SetJsBuilderNodeId(firstNode->GetId());

    auto context = AceType::MakeRefPtr<NG::MockPipelineContext>();
    EXPECT_NE(context, nullptr);
    firstNode->context_ = AceType::RawPtr(context);
    secondedNode->context_ = AceType::RawPtr(context);
    thirdNode->context_ = AceType::RawPtr(context);
    forthNode->context_ = AceType::RawPtr(context);
    fifthNode->context_ = AceType::RawPtr(context);
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    context->weakFrontend_ = AceType::WeakClaim(AceType::RawPtr(frontend));

    /**
     * @tc.steps: step3. Call ClearChildInBuilderContainer.
     * @tc.expected: step3. Call BuilderNodeFunc with "__deleteBuilderNode__".
     */
    std::list<RefPtr<NG::UINode>> nodes;
    BuilderUtils::ClearChildInBuilderContainer(UNIQUED_ID_OF_TEST_NODE, nodes);
    BuilderUtils::GetBuilderNodes(firstNode, nodes);
    EXPECT_EQ(nodes.size(), 2);
    EXPECT_CALL(*frontend, BuilderNodeFunc("__deleteBuilderNode__", _)).Times(1);
    BuilderUtils::ClearChildInBuilderContainer(firstNode->GetId(), nodes);

    /**
     * @tc.steps: step4. Call AddBuilderToParent.
     * @tc.expected: step4. Call BuilderNodeFunc with "__deleteBuilderNode__".
     */
    EXPECT_CALL(*frontend, BuilderNodeFunc("__addBuilderNodeToBuilder__", _)).Times(1);
    BuilderUtils::AddBuilderToParent(secondedNode, thirdNode);
    EXPECT_CALL(*frontend, BuilderNodeFunc("__addBuilderNode__", _)).Times(1);
    BuilderUtils::AddBuilderToParent(firstNode, secondedNode);

    /**
     * @tc.steps: step4. Call AddBuilderToParent.
     * @tc.expected: step4. Call BuilderNodeFunc with "__deleteBuilderNode__".
     */
    EXPECT_CALL(*frontend, BuilderNodeFunc("__deleteBuilderNodeFromBuilder__", _)).Times(1);
    BuilderUtils::RemoveBuilderFromParent(secondedNode, thirdNode);
    EXPECT_CALL(*frontend, BuilderNodeFunc("__deleteBuilderNode__", _)).Times(1);
    BuilderUtils::RemoveBuilderFromParent(firstNode, secondedNode);

    /**
     * @tc.steps: step5. Call AddBuilderToParent or RemoveBuilderFromParent with C Node.
     */
    secondedNode->setIsCNode(true);
    EXPECT_CALL(*frontend, BuilderNodeFunc("__addBuilderNode__", _)).Times(0);
    EXPECT_CALL(*frontend, BuilderNodeFunc("__addBuilderNodeToBuilder__", _)).Times(0);
    BuilderUtils::AddBuilderToParent(secondedNode, thirdNode);
    BuilderUtils::AddBuilderToParent(nullptr, thirdNode);
    BuilderUtils::AddBuilderToParent(nullptr, nullptr);
    BuilderUtils::AddBuilderToParent(secondedNode, nullptr);

    EXPECT_CALL(*frontend, BuilderNodeFunc("__deleteBuilderNodeFromBuilder__", _)).Times(0);
    EXPECT_CALL(*frontend, BuilderNodeFunc("__deleteBuilderNode__", _)).Times(0);
    BuilderUtils::RemoveBuilderFromParent(secondedNode, thirdNode);
    BuilderUtils::RemoveBuilderFromParent(nullptr, thirdNode);
    BuilderUtils::RemoveBuilderFromParent(nullptr, nullptr);
    BuilderUtils::RemoveBuilderFromParent(secondedNode, nullptr);
}

/**
 * @tc.name: BuilderUtilsTest004
 * @tc.desc: Test when the Tree does not contains valid parent.
 * @tc.type: FUNC
 */
HWTEST_F(BuilderUtilsTest, BuilderUtilsTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some UINode. And Set Second Node as BuilderRootNode;
     * @tc.expected: step1. The return value is not null.
     */
    auto firstNode = NG::FrameNode::GetOrCreateFrameNode(
        TEST_NODE_TAG, UNIQUED_ID_OF_TEST_NODE++, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    EXPECT_NE(firstNode, nullptr);
    auto secondedNode = NG::FrameNode::GetOrCreateFrameNode(
        TEST_NODE_TAG, UNIQUED_ID_OF_TEST_NODE++, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    EXPECT_NE(secondedNode, nullptr);
    auto thirdNode = NG::FrameNode::GetOrCreateFrameNode(
        TEST_NODE_TAG, UNIQUED_ID_OF_TEST_NODE++, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    /**
     * @tc.steps: step2. Make a tree by the previous Node.
     *├─ firstNode
     *│ ├─ secondedNode
     *│ │  └─ thirdNode (true)
     */
    firstNode->AddChild(secondedNode);
    secondedNode->AddChild(thirdNode);
    thirdNode->SetJsBuilderNodeId(secondedNode->GetId());

    auto context = AceType::MakeRefPtr<NG::MockPipelineContext>();
    EXPECT_NE(context, nullptr);
    firstNode->context_ = AceType::RawPtr(context);
    secondedNode->context_ = AceType::RawPtr(context);
    thirdNode->context_ = AceType::RawPtr(context);
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    context->weakFrontend_ = AceType::WeakClaim(AceType::RawPtr(frontend));

    /**
     * @tc.steps: step3. Call AddBuilderToParent or RemoveBuilderFromParent without valid parent.
     */
    EXPECT_CALL(*frontend, BuilderNodeFunc("__addBuilderNode__", _)).Times(0);
    EXPECT_CALL(*frontend, BuilderNodeFunc("__addBuilderNodeToBuilder__", _)).Times(0);
    BuilderUtils::AddBuilderToParent(secondedNode, thirdNode);
    BuilderUtils::AddBuilderToParent(nullptr, thirdNode);
    BuilderUtils::AddBuilderToParent(nullptr, nullptr);
    BuilderUtils::AddBuilderToParent(secondedNode, nullptr);

    EXPECT_CALL(*frontend, BuilderNodeFunc("__deleteBuilderNodeFromBuilder__", _)).Times(0);
    EXPECT_CALL(*frontend, BuilderNodeFunc("__deleteBuilderNode__", _)).Times(0);
    BuilderUtils::RemoveBuilderFromParent(secondedNode, thirdNode);
    BuilderUtils::RemoveBuilderFromParent(nullptr, thirdNode);
    BuilderUtils::RemoveBuilderFromParent(nullptr, nullptr);
    BuilderUtils::RemoveBuilderFromParent(secondedNode, nullptr);
}
} // namespace OHOS::Ace
