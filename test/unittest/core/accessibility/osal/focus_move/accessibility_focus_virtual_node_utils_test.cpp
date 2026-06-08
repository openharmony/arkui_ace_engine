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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_virtual_node_utils.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_frame_node_utils.h"
#include "base/log/dump_log.h"
#include "frameworks/core/accessibility/utils/accessibility_manager_utils.h"
#include "frameworks/core/components_ng/property/accessibility_property.h"

using namespace OHOS::Ace::NG;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Framework {
namespace {
constexpr int32_t TEST_ACCESSIBILITY_ELEMENT_ID = 100;
constexpr int32_t TEST_PARENT_ACCESSIBILITY_ID = 200;
constexpr int32_t TEST_CHILD_NODE_ID_1 = 101;
constexpr int32_t TEST_CHILD_NODE_ID_2 = 102;
const std::string ACCESSIBILITY_FOCUS_ACTION_STR = "accessibilityFocus";
} // namespace

class VirtualAccessibilityNodeRulesCheckNodeTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
        MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
        MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;

        std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
        ASSERT_NE(ostream, nullptr);
        DumpLog::GetInstance().SetDumpFile(std::move(ostream));
    }

    static void TearDownTestSuite()
    {
        VirtualNodeContainerIdManager::GetInstance().Clear();
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }

    void SetUp() override
    {
        VirtualNodeContainerIdManager::GetInstance().Clear();
    }

    void TearDown() override
    {
        VirtualNodeContainerIdManager::GetInstance().Clear();
    }
};

// ==================== IsVirtualNode ====================

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeIsVirtualNode001
 * @tc.desc: Test IsVirtualNode returns true
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeIsVirtualNode001, TestSize.Level1)
{
    auto virtualNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(virtualNode, nullptr);
    VirtualAccessibilityNodeRulesCheckNode checkNode(virtualNode, TEST_ACCESSIBILITY_ELEMENT_ID);
    EXPECT_TRUE(checkNode.IsVirtualNode());
}

// ==================== GetPropText with nullptr node ====================

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropText001
 * @tc.desc: Test GetPropText with nullptr node returns false
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropText001, TestSize.Level1)
{
    VirtualAccessibilityNodeRulesCheckNode checkNode(nullptr, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_FALSE(checkNode.GetPropText(value));
}

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropText002
 * @tc.desc: Test GetPropText with valid node returns accessibility text
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropText002, TestSize.Level1)
{
    auto virtualNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(virtualNode, nullptr);
    virtualNode->SetAccessibilityText("hello_world");
    VirtualAccessibilityNodeRulesCheckNode checkNode(virtualNode, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_TRUE(checkNode.GetPropText(value));
    EXPECT_EQ(value.valueType, Accessibility::ValueType::STRING);
    EXPECT_EQ(value.valueStr, "hello_world");
}

// ==================== GetPropHintText ====================

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropHintText001
 * @tc.desc: Test GetPropHintText with nullptr node still returns true with empty string
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropHintText001, TestSize.Level1)
{
    VirtualAccessibilityNodeRulesCheckNode checkNode(nullptr, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_TRUE(checkNode.GetPropHintText(value));
    EXPECT_EQ(value.valueType, Accessibility::ValueType::STRING);
    EXPECT_EQ(value.valueStr, "");
}

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropHintText002
 * @tc.desc: Test GetPropHintText with valid node returns empty string
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropHintText002, TestSize.Level1)
{
    auto virtualNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(virtualNode, nullptr);
    VirtualAccessibilityNodeRulesCheckNode checkNode(virtualNode, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_TRUE(checkNode.GetPropHintText(value));
    EXPECT_EQ(value.valueType, Accessibility::ValueType::STRING);
    EXPECT_EQ(value.valueStr, "");
}

// ==================== GetPropDesc ====================

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropDesc001
 * @tc.desc: Test GetPropDesc with nullptr node still returns true with empty string
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropDesc001, TestSize.Level1)
{
    VirtualAccessibilityNodeRulesCheckNode checkNode(nullptr, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_TRUE(checkNode.GetPropDesc(value));
    EXPECT_EQ(value.valueType, Accessibility::ValueType::STRING);
    EXPECT_EQ(value.valueStr, "");
}

// ==================== GetPropAccessibilityText ====================

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropAccessibilityText001
 * @tc.desc: Test GetPropAccessibilityText with nullptr node returns false
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropAccessibilityText001, TestSize.Level1)
{
    VirtualAccessibilityNodeRulesCheckNode checkNode(nullptr, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_FALSE(checkNode.GetPropAccessibilityText(value));
}

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropAccessibilityText002
 * @tc.desc: Test GetPropAccessibilityText returns the node's accessibilityText
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropAccessibilityText002, TestSize.Level1)
{
    auto virtualNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(virtualNode, nullptr);
    virtualNode->SetAccessibilityText("acc_text_value");
    VirtualAccessibilityNodeRulesCheckNode checkNode(virtualNode, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_TRUE(checkNode.GetPropAccessibilityText(value));
    EXPECT_EQ(value.valueType, Accessibility::ValueType::STRING);
    EXPECT_EQ(value.valueStr, "acc_text_value");
}

// ==================== GetPropType ====================

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropType001
 * @tc.desc: Test GetPropType with nullptr node returns false
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropType001, TestSize.Level1)
{
    VirtualAccessibilityNodeRulesCheckNode checkNode(nullptr, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_FALSE(checkNode.GetPropType(value));
}

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropType002
 * @tc.desc: Test GetPropType returns the node's role
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropType002, TestSize.Level1)
{
    auto virtualNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(virtualNode, nullptr);
    virtualNode->SetRole("button");
    VirtualAccessibilityNodeRulesCheckNode checkNode(virtualNode, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_TRUE(checkNode.GetPropType(value));
    EXPECT_EQ(value.valueType, Accessibility::ValueType::STRING);
    EXPECT_EQ(value.valueStr, "button");
}

// ==================== GetPropAccessibilityLevel ====================

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropAccessibilityLevel001
 * @tc.desc: Test GetPropAccessibilityLevel with nullptr node returns false
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropAccessibilityLevel001, TestSize.Level1)
{
    VirtualAccessibilityNodeRulesCheckNode checkNode(nullptr, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_FALSE(checkNode.GetPropAccessibilityLevel(value));
}

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropAccessibilityLevel002
 * @tc.desc: Test GetPropAccessibilityLevel returns the node's level
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropAccessibilityLevel002, TestSize.Level1)
{
    auto virtualNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(virtualNode, nullptr);
    virtualNode->SetAccessibilityLevel("yes");
    VirtualAccessibilityNodeRulesCheckNode checkNode(virtualNode, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_TRUE(checkNode.GetPropAccessibilityLevel(value));
    EXPECT_EQ(value.valueType, Accessibility::ValueType::STRING);
    EXPECT_EQ(value.valueStr, "yes");
}

// ==================== GetPropAccessibilityGroup ====================

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropAccessibilityGroup001
 * @tc.desc: Test GetPropAccessibilityGroup with nullptr node returns false
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropAccessibilityGroup001, TestSize.Level1)
{
    VirtualAccessibilityNodeRulesCheckNode checkNode(nullptr, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_FALSE(checkNode.GetPropAccessibilityGroup(value));
}

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropAccessibilityGroup002
 * @tc.desc: Test GetPropAccessibilityGroup returns the node's group
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropAccessibilityGroup002, TestSize.Level1)
{
    auto virtualNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(virtualNode, nullptr);
    virtualNode->SetAccessibilityGroup(true);
    VirtualAccessibilityNodeRulesCheckNode checkNode(virtualNode, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_TRUE(checkNode.GetPropAccessibilityGroup(value));
    EXPECT_EQ(value.valueType, Accessibility::ValueType::BOOL);
    EXPECT_TRUE(value.valueBool);
}

// ==================== GetPropIsEnable ====================

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropIsEnable001
 * @tc.desc: Test GetPropIsEnable with nullptr node returns false
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropIsEnable001, TestSize.Level1)
{
    VirtualAccessibilityNodeRulesCheckNode checkNode(nullptr, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_FALSE(checkNode.GetPropIsEnable(value));
}

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropIsEnable002
 * @tc.desc: Test GetPropIsEnable returns the node's enabled state
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropIsEnable002, TestSize.Level1)
{
    auto virtualNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(virtualNode, nullptr);
    virtualNode->SetEnabled(false);
    VirtualAccessibilityNodeRulesCheckNode checkNode(virtualNode, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_TRUE(checkNode.GetPropIsEnable(value));
    EXPECT_EQ(value.valueType, Accessibility::ValueType::BOOL);
    EXPECT_FALSE(value.valueBool);
}

// ==================== GetPropChildrenCount ====================

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropChildrenCount001
 * @tc.desc: Test GetPropChildrenCount with nullptr node returns false
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropChildrenCount001, TestSize.Level1)
{
    VirtualAccessibilityNodeRulesCheckNode checkNode(nullptr, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_FALSE(checkNode.GetPropChildrenCount(value));
}

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropChildrenCount002
 * @tc.desc: Test GetPropChildrenCount returns correct child count
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropChildrenCount002, TestSize.Level1)
{
    auto virtualNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(virtualNode, nullptr);
    auto child1 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto child2 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    virtualNode->AddChild(child1);
    virtualNode->AddChild(child2);
    VirtualAccessibilityNodeRulesCheckNode checkNode(virtualNode, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_TRUE(checkNode.GetPropChildrenCount(value));
    EXPECT_EQ(value.valueType, Accessibility::ValueType::NUMBER);
    EXPECT_EQ(value.valueNum, 2);
}

// ==================== GetPropActionNames ====================

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropActionNames001
 * @tc.desc: Test GetPropActionNames returns accessibilityFocus action
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropActionNames001, TestSize.Level1)
{
    VirtualAccessibilityNodeRulesCheckNode checkNode(nullptr, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_TRUE(checkNode.GetPropActionNames(value));
    EXPECT_EQ(value.valueType, Accessibility::ValueType::ARRAY);
    EXPECT_GT(value.valueArray.size(), 0u);
    EXPECT_NE(value.valueArray.find(ACCESSIBILITY_FOCUS_ACTION_STR), value.valueArray.end());
}

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetPropActionNames002
 * @tc.desc: Test GetPropActionNames with valid node also returns accessibilityFocus
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetPropActionNames002, TestSize.Level1)
{
    auto virtualNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(virtualNode, nullptr);
    VirtualAccessibilityNodeRulesCheckNode checkNode(virtualNode, TEST_ACCESSIBILITY_ELEMENT_ID);
    Accessibility::PropValue value;
    EXPECT_TRUE(checkNode.GetPropActionNames(value));
    EXPECT_EQ(value.valueType, Accessibility::ValueType::ARRAY);
    EXPECT_NE(value.valueArray.find(ACCESSIBILITY_FOCUS_ACTION_STR), value.valueArray.end());
}

// ==================== GetAceChildren / GetChildren ====================

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetAceChildren001
 * @tc.desc: Test GetAceChildren with nullptr node returns empty
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetAceChildren001, TestSize.Level1)
{
    VirtualAccessibilityNodeRulesCheckNode checkNode(nullptr, TEST_ACCESSIBILITY_ELEMENT_ID);
    auto children = checkNode.GetAceChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetAceChildren002
 * @tc.desc: Test GetAceChildren with nullptr hostFrameNode returns empty
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetAceChildren002, TestSize.Level1)
{
    auto virtualNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(virtualNode, nullptr);
    auto child = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    virtualNode->AddChild(child);
    VirtualAccessibilityNodeRulesCheckNode checkNode(virtualNode, TEST_ACCESSIBILITY_ELEMENT_ID);
    auto children = checkNode.GetAceChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetAceChildren003
 * @tc.desc: Test GetAceChildren with valid node and host returns children
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetAceChildren003, TestSize.Level1)
{
    auto hostNode = FrameNode::CreateFrameNode("host",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(hostNode, nullptr);
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    auto containerId = mgr.AllocateContainerId(hostNode);
    ASSERT_NE(containerId, 0);

    auto virtualNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(virtualNode, nullptr);
    auto child1 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto child2 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    child1->SetNodeId(TEST_CHILD_NODE_ID_1);
    child2->SetNodeId(TEST_CHILD_NODE_ID_2);
    virtualNode->AddChild(child1);
    virtualNode->AddChild(child2);

    VirtualAccessibilityNodeRulesCheckNode checkNode(virtualNode, TEST_ACCESSIBILITY_ELEMENT_ID, hostNode);
    auto children = checkNode.GetAceChildren();
    ASSERT_EQ(children.size(), 2u);
}

// ==================== GetAceParent / GetParent ====================

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetAceParent001
 * @tc.desc: Test GetAceParent with nullptr node returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetAceParent001, TestSize.Level1)
{
    VirtualAccessibilityNodeRulesCheckNode checkNode(nullptr, TEST_ACCESSIBILITY_ELEMENT_ID);
    auto parent = checkNode.GetAceParent();
    EXPECT_EQ(parent, nullptr);
}

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetAceParent002
 * @tc.desc: Test GetAceParent with nullptr hostFrameNode returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetAceParent002, TestSize.Level1)
{
    auto virtualNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(virtualNode, nullptr);
    VirtualAccessibilityNodeRulesCheckNode checkNode(virtualNode, TEST_ACCESSIBILITY_ELEMENT_ID);
    auto parent = checkNode.GetAceParent();
    EXPECT_EQ(parent, nullptr);
}

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetAceParent003
 * @tc.desc: Test GetAceParent with node that has parent virtual node returns VirtualAccessibilityNodeRulesCheckNode
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetAceParent003, TestSize.Level1)
{
    auto hostNode = FrameNode::CreateFrameNode("host",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(hostNode, nullptr);
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    auto containerId = mgr.AllocateContainerId(hostNode);
    ASSERT_NE(containerId, 0);

    auto parentVNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto childVNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(parentVNode, nullptr);
    ASSERT_NE(childVNode, nullptr);
    parentVNode->SetNodeId(1);
    childVNode->SetNodeId(2);
    parentVNode->AddChild(childVNode);

    VirtualAccessibilityNodeRulesCheckNode checkNode(childVNode, TEST_PARENT_ACCESSIBILITY_ID, hostNode);
    auto parent = checkNode.GetAceParent();
    ASSERT_NE(parent, nullptr);
    EXPECT_TRUE(parent->IsVirtualNode());
}

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetAceParent004
 * @tc.desc: Test GetAceParent with root virtual node returns FrameNodeRulesCheckNode
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetAceParent004, TestSize.Level1)
{
    auto hostNode = FrameNode::CreateFrameNode("host",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(hostNode, nullptr);
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    auto containerId = mgr.AllocateContainerId(hostNode);
    ASSERT_NE(containerId, 0);

    auto rootVNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(rootVNode, nullptr);
    rootVNode->SetNodeId(1);

    VirtualAccessibilityNodeRulesCheckNode checkNode(rootVNode, TEST_ACCESSIBILITY_ELEMENT_ID, hostNode);
    auto parent = checkNode.GetAceParent();
    ASSERT_NE(parent, nullptr);
    EXPECT_FALSE(parent->IsVirtualNode());
}

// ==================== GetAccessibilityNode / GetHostFrameNode ====================

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetAccessibilityNode001
 * @tc.desc: Test GetAccessibilityNode returns the underlying node
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetAccessibilityNode001, TestSize.Level1)
{
    auto virtualNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(virtualNode, nullptr);
    VirtualAccessibilityNodeRulesCheckNode checkNode(virtualNode, TEST_ACCESSIBILITY_ELEMENT_ID);
    auto result = checkNode.GetAccessibilityNode();
    EXPECT_EQ(result, virtualNode);
}

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetHostFrameNode001
 * @tc.desc: Test GetHostFrameNode returns the host node
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetHostFrameNode001, TestSize.Level1)
{
    auto virtualNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto hostNode = FrameNode::CreateFrameNode("host",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(virtualNode, nullptr);
    ASSERT_NE(hostNode, nullptr);
    VirtualAccessibilityNodeRulesCheckNode checkNode(virtualNode, TEST_ACCESSIBILITY_ELEMENT_ID, hostNode);
    auto result = checkNode.GetHostFrameNode();
    EXPECT_EQ(result, hostNode);
}

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetHostFrameNode002
 * @tc.desc: Test GetHostFrameNode with no host returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetHostFrameNode002, TestSize.Level1)
{
    auto virtualNode = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(virtualNode, nullptr);
    VirtualAccessibilityNodeRulesCheckNode checkNode(virtualNode, TEST_ACCESSIBILITY_ELEMENT_ID);
    auto result = checkNode.GetHostFrameNode();
    EXPECT_EQ(result, nullptr);
}

// ==================== GetChildren (ReadableRulesNode) ====================

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetChildren001
 * @tc.desc: Test GetChildren with nullptr node returns empty
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetChildren001, TestSize.Level1)
{
    VirtualAccessibilityNodeRulesCheckNode checkNode(nullptr, TEST_ACCESSIBILITY_ELEMENT_ID);
    auto children = checkNode.GetChildren();
    EXPECT_TRUE(children.empty());
}

// ==================== GetParent (ReadableRulesNode) ====================

/**
 * @tc.name: VirtualAccessibilityNodeRulesCheckNodeGetParent001
 * @tc.desc: Test GetParent with nullptr node returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(VirtualAccessibilityNodeRulesCheckNodeTest,
    VirtualAccessibilityNodeRulesCheckNodeGetParent001, TestSize.Level1)
{
    VirtualAccessibilityNodeRulesCheckNode checkNode(nullptr, TEST_ACCESSIBILITY_ELEMENT_ID);
    auto parent = checkNode.GetParent();
    EXPECT_EQ(parent, nullptr);
}

} // namespace OHOS::Ace::Framework
