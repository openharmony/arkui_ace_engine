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

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/log/dump_log.h"
#include "core/accessibility/node_utils/accessibility_frame_node_utils.h"
#include "core/components_ng/property/accessibility_property.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace {
const char* const TEST_TAG_CUSTOM = "customNode";
} // namespace

namespace OHOS::Ace::NG {

// Same fixture as accessibility_frame_node_utils_test.cpp, SetUp/TearDown defined there
class AccessibilityFrameNodeUtilsTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

// ==================== GetFramenodeByCondition ====================

/**
 * @tc.name: GetFramenodeByCondition001
 * @tc.desc: Test GetFramenodeByCondition with null root
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, GetFramenodeByCondition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetFramenodeByCondition with null root
     * @tc.expected: return nullptr
     */
    auto result = AccessibilityFrameNodeUtils::GetFramenodeByCondition(
        nullptr, [](const RefPtr<NG::FrameNode>&) { return true; });
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetFramenodeByCondition002
 * @tc.desc: Test GetFramenodeByCondition when condition matches child node
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, GetFramenodeByCondition002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create parent with two children
     */
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto root = context->GetRootElement();
    ASSERT_NE(root, nullptr);

    auto parent = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(parent, nullptr);
    root->AddChild(parent);

    auto child1 = FrameNode::CreateFrameNode("child1",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(child1, nullptr);
    auto child2 = FrameNode::CreateFrameNode("child2",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(child2, nullptr);
    parent->AddChild(child1);
    parent->AddChild(child2);

    /**
     * @tc.steps: step2. condition matches child2
     * @tc.expected: return child2
     */
    auto targetId = child2->GetAccessibilityId();
    auto result = AccessibilityFrameNodeUtils::GetFramenodeByCondition(
        parent, [targetId](const RefPtr<NG::FrameNode>& node) {
            return node->GetAccessibilityId() == targetId;
        });
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetAccessibilityId(), targetId);

    root->RemoveChild(parent);
}

/**
 * @tc.name: GetFramenodeByCondition003
 * @tc.desc: Test GetFramenodeByCondition when no node matches condition
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, GetFramenodeByCondition003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a node with children
     */
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto root = context->GetRootElement();
    ASSERT_NE(root, nullptr);

    auto parent = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(parent, nullptr);
    root->AddChild(parent);

    auto child = FrameNode::CreateFrameNode("child",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(child, nullptr);
    parent->AddChild(child);

    /**
     * @tc.steps: step2. condition never matches any node
     * @tc.expected: return nullptr
     */
    auto result = AccessibilityFrameNodeUtils::GetFramenodeByCondition(
        parent, [](const RefPtr<NG::FrameNode>&) { return false; });
    EXPECT_EQ(result, nullptr);

    root->RemoveChild(parent);
}

/**
 * @tc.name: GetFramenodeByCondition004
 * @tc.desc: Test GetFramenodeByCondition with virtual node
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, GetFramenodeByCondition004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create parent with virtual accessibility node
     */
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto root = context->GetRootElement();
    ASSERT_NE(root, nullptr);

    auto parent = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(parent, nullptr);
    root->AddChild(parent);

    auto virtualNode = FrameNode::CreateFrameNode("virtualNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(virtualNode, nullptr);
    virtualNode->SetAccessibilityNodeVirtual();
    virtualNode->SetAccessibilityVirtualNodeParent(parent);
    virtualNode->SetFirstAccessibilityVirtualNode();
    parent->HasAccessibilityVirtualNode(true);
    auto accessibilityProperty = parent->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SaveAccessibilityVirtualNode(virtualNode);

    /**
     * @tc.steps: step2. condition matches virtual node
     * @tc.expected: return virtualNode
     */
    auto targetId = virtualNode->GetAccessibilityId();
    auto result = AccessibilityFrameNodeUtils::GetFramenodeByCondition(
        parent, [targetId](const RefPtr<NG::FrameNode>& node) {
            return node->GetAccessibilityId() == targetId;
        });
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetAccessibilityId(), targetId);

    root->RemoveChild(parent);
}

/**
 * @tc.name: GetFramenodeByCondition005
 * @tc.desc: Test GetFramenodeByCondition with overlay node
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, GetFramenodeByCondition005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create parent with overlay node
     */
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto root = context->GetRootElement();
    ASSERT_NE(root, nullptr);

    auto parent = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(parent, nullptr);
    root->AddChild(parent);

    auto overlayNode = FrameNode::CreateFrameNode("overlayNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(overlayNode, nullptr);
    parent->SetOverlayNode(overlayNode);

    /**
     * @tc.steps: step2. condition matches overlay node
     * @tc.expected: return overlayNode
     */
    auto targetId = overlayNode->GetAccessibilityId();
    auto result = AccessibilityFrameNodeUtils::GetFramenodeByCondition(
        parent, [targetId](const RefPtr<NG::FrameNode>& node) {
            return node->GetAccessibilityId() == targetId;
        });
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetAccessibilityId(), targetId);

    root->RemoveChild(parent);
}

// ==================== IsValidEmbedTarget ====================

/**
 * @tc.name: IsValidEmbedTarget001
 * @tc.desc: Test IsValidEmbedTarget with valid node and null manager
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, IsValidEmbedTarget001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frame node and call with null manager
     * @tc.expected: return false because manager is null
     */
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto result = AccessibilityFrameNodeUtils::IsValidEmbedTarget(frameNode, nullptr);
    EXPECT_FALSE(result);
}

// ==================== GetChildrenFromFrameNode ====================

/**
 * @tc.name: GetChildrenFromFrameNode001
 * @tc.desc: Test GetChildrenFromFrameNode with null manager
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, GetChildrenFromFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create parent with children and null manager
     * @tc.expected: children vector still gets populated
     */
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto parent = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(parent, nullptr);

    auto child = FrameNode::CreateFrameNode("child",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(child, nullptr);
    parent->AddChild(child);

    std::vector<RefPtr<FrameNode>> children;
    FrameNodeHandleParam handleParam;
    AccessibilityFrameNodeUtils::GetChildrenFromFrameNode(parent, children, handleParam, nullptr);
    EXPECT_GE(children.size(), static_cast<size_t>(1));
}

// ==================== GetLastestPageNodes ====================

/**
 * @tc.name: GetLastestPageNodes001
 * @tc.desc: Test GetLastestPageNodes with null node
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, GetLastestPageNodes001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetLastestPageNodes with null node
     * @tc.expected: pageNodes remains empty
     */
    std::vector<WeakPtr<FrameNode>> pageNodes;
    AccessibilityFrameNodeUtils::GetLastestPageNodes(nullptr, pageNodes);
    EXPECT_TRUE(pageNodes.empty());
}

/**
 * @tc.name: GetLastestPageNodes002
 * @tc.desc: Test GetLastestPageNodes with node that has no context
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, GetLastestPageNodes002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frame node without pipeline context attached
     * @tc.expected: pageNodes remains empty because GetContextRefPtr returns null
     */
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    frameNode->DetachContext();

    std::vector<WeakPtr<FrameNode>> pageNodes;
    AccessibilityFrameNodeUtils::GetLastestPageNodes(frameNode, pageNodes);
    EXPECT_TRUE(pageNodes.empty());
}
} // namespace OHOS::Ace::NG
