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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/log/dump_log.h"
#include "adapter/ohos/osal/accessibility/hover/accessibility_hover_virtual_node_utils.h"
#include "adapter/ohos/osal/js_accessibility_manager.h"
#include "frameworks/core/accessibility/utils/accessibility_manager_utils.h"
#include "frameworks/core/components_ng/property/accessibility_property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {

const char* const TEST_TAG_CONTAINER = "virtualNodeContainer";
constexpr int32_t TEST_ROOT_NODE_ID = 1;
constexpr int32_t TEST_CHILD1_NODE_ID = 2;
constexpr int32_t TEST_CHILD2_NODE_ID = 3;
constexpr int32_t TEST_WINDOW_ID = 100;
constexpr int32_t TEST_PARENT_ACCESSIBILITY_ID = 99;
constexpr int32_t TEST_NONEXISTENT_NODE_ID = 999;

// Rect constants: left, top, width, height
constexpr int32_t TEST_ROOT_RECT_LEFT = 0;
constexpr int32_t TEST_ROOT_RECT_TOP = 0;
constexpr int32_t TEST_ROOT_RECT_WIDTH = 200;
constexpr int32_t TEST_ROOT_RECT_HEIGHT = 200;
constexpr int32_t TEST_CHILD1_RECT_LEFT = 10;
constexpr int32_t TEST_CHILD1_RECT_TOP = 10;
constexpr int32_t TEST_CHILD1_RECT_WIDTH = 80;
constexpr int32_t TEST_CHILD1_RECT_HEIGHT = 80;
constexpr int32_t TEST_CHILD2_RECT_LEFT = 100;
constexpr int32_t TEST_CHILD2_RECT_TOP = 10;
constexpr int32_t TEST_CHILD2_RECT_WIDTH = 80;
constexpr int32_t TEST_CHILD2_RECT_HEIGHT = 80;

class JsAccessibilityManagerVirtualNodeTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

    void SetUp() override
    {
        VirtualNodeContainerIdManager::GetInstance().Clear();
    }

    void TearDown() override
    {
        VirtualNodeContainerIdManager::GetInstance().Clear();
    }
};

void JsAccessibilityManagerVirtualNodeTest::SetUpTestCase()
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

void JsAccessibilityManagerVirtualNodeTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<NG::VirtualAccessibilityNode> CreateVirtualNodeTree()
{
    auto root = AceType::MakeRefPtr<NG::VirtualAccessibilityNode>();
    root->SetNodeId(TEST_ROOT_NODE_ID);
    root->SetRect(TEST_ROOT_RECT_LEFT, TEST_ROOT_RECT_TOP, TEST_ROOT_RECT_WIDTH, TEST_ROOT_RECT_HEIGHT);
    root->SetAccessibilityText("root");
    root->SetRole("container");
    root->SetAccessibilityLevel("yes");
    root->SetAccessibilityGroup(true);
    root->SetEnabled(true);

    auto child1 = AceType::MakeRefPtr<NG::VirtualAccessibilityNode>();
    child1->SetNodeId(TEST_CHILD1_NODE_ID);
    child1->SetRect(TEST_CHILD1_RECT_LEFT, TEST_CHILD1_RECT_TOP, TEST_CHILD1_RECT_WIDTH, TEST_CHILD1_RECT_HEIGHT);
    child1->SetAccessibilityText("child1");
    child1->SetRole("button");
    child1->SetEnabled(true);
    child1->SetCheckable(true);
    child1->SetChecked(false);

    auto child2 = AceType::MakeRefPtr<NG::VirtualAccessibilityNode>();
    child2->SetNodeId(TEST_CHILD2_NODE_ID);
    child2->SetRect(TEST_CHILD2_RECT_LEFT, TEST_CHILD2_RECT_TOP, TEST_CHILD2_RECT_WIDTH, TEST_CHILD2_RECT_HEIGHT);
    child2->SetAccessibilityText("child2");
    child2->SetRole("text");
    child2->SetEnabled(true);
    child2->SetSelected(true);

    root->AddChild(child1);
    root->AddChild(child2);
    return root;
}

} // namespace

// ==================== UpdateAccessibilityElementInfoForVirtualNode ====================

/**
 * @tc.name: UpdateAccessibilityElementInfoForVirtualNode001
 * @tc.desc: Test with null hostNode, should not crash
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, UpdateAccessibilityElementInfoForVirtualNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create manager and call with null hostNode
     * @tc.expected: no crash, nodeInfo remains default
     */
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto virtualNode = AceType::MakeRefPtr<NG::VirtualAccessibilityNode>();
    virtualNode->SetNodeId(TEST_ROOT_NODE_ID);
    Accessibility::AccessibilityElementInfo nodeInfo;
    CommonProperty commonProperty;
    manager->UpdateAccessibilityElementInfoForVirtualNode(
        nullptr, virtualNode, commonProperty, nodeInfo, 0);
    EXPECT_EQ(nodeInfo.GetAccessibilityId(), 0);
}

/**
 * @tc.name: UpdateAccessibilityElementInfoForVirtualNode002
 * @tc.desc: Test with null virtualNode, should not crash
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, UpdateAccessibilityElementInfoForVirtualNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create manager and call with null virtualNode
     * @tc.expected: no crash, nodeInfo remains default
     */
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto hostNode = NG::FrameNode::CreateFrameNode(TEST_TAG_CONTAINER,
        NG::ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>(), true);
    Accessibility::AccessibilityElementInfo nodeInfo;
    CommonProperty commonProperty;
    manager->UpdateAccessibilityElementInfoForVirtualNode(
        hostNode, nullptr, commonProperty, nodeInfo, 0);
    EXPECT_EQ(nodeInfo.GetAccessibilityId(), 0);
}

/**
 * @tc.name: UpdateAccessibilityElementInfoForVirtualNode003
 * @tc.desc: Test normal case, properties correctly transferred
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, UpdateAccessibilityElementInfoForVirtualNode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set up hostNode with container ID and virtual node tree
     * @tc.expected: nodeInfo has correct accessibility properties from virtualNode
     */
    auto& mgr = NG::VirtualNodeContainerIdManager::GetInstance();
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto hostNode = NG::FrameNode::CreateFrameNode(TEST_TAG_CONTAINER,
        NG::ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>(), true);
    auto containerId = mgr.AllocateContainerId(hostNode);
    ASSERT_NE(containerId, 0);

    auto virtualNode = AceType::MakeRefPtr<NG::VirtualAccessibilityNode>();
    virtualNode->SetNodeId(10);
    virtualNode->SetRect(5, 10, 100, 50);
    virtualNode->SetAccessibilityText("testText");
    virtualNode->SetRole("button");
    virtualNode->SetAccessibilityLevel("yes");
    virtualNode->SetAccessibilityGroup(true);
    virtualNode->SetCheckable(true);
    virtualNode->SetChecked(true);
    virtualNode->SetEnabled(true);
    virtualNode->SetSelected(true);
    virtualNode->SetAccessibilityFocused(true);

    auto accessibilityProperty = hostNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetVirtualNodeTreeRoot(virtualNode);

    Accessibility::AccessibilityElementInfo nodeInfo;
    CommonProperty commonProperty;
    commonProperty.windowId = TEST_WINDOW_ID;
    commonProperty.windowLeft = 0;
    commonProperty.windowTop = 0;

    manager->UpdateAccessibilityElementInfoForVirtualNode(
        hostNode, virtualNode, commonProperty, nodeInfo, TEST_PARENT_ACCESSIBILITY_ID);

    EXPECT_EQ(nodeInfo.GetComponentType(), "button");
    EXPECT_EQ(nodeInfo.GetContent(), "testText");
    EXPECT_EQ(nodeInfo.GetAccessibilityLevel(), "yes");
    EXPECT_EQ(nodeInfo.GetAccessibilityGroup(), true);
    EXPECT_EQ(nodeInfo.GetCheckable(), true);
    EXPECT_EQ(nodeInfo.GetChecked(), true);
    EXPECT_EQ(nodeInfo.GetEnabled(), true);
    EXPECT_EQ(nodeInfo.GetSelected(), true);
    EXPECT_EQ(nodeInfo.GetAccessibilityFocus(), true);
    EXPECT_EQ(nodeInfo.GetParent(), TEST_PARENT_ACCESSIBILITY_ID);
    EXPECT_EQ(nodeInfo.GetWindowId(), TEST_WINDOW_ID);
    EXPECT_EQ(nodeInfo.GetVisible(), true);
}

/**
 * @tc.name: UpdateAccessibilityElementInfoForVirtualNode004
 * @tc.desc: Test screen bounds calculation with hostNode rect
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, UpdateAccessibilityElementInfoForVirtualNode004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set virtualNode rect and verify screen bounds
     * @tc.expected: bounds are calculated from host rect + virtualNode rect + window offset
     */
    auto& mgr = NG::VirtualNodeContainerIdManager::GetInstance();
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto hostNode = NG::FrameNode::CreateFrameNode(TEST_TAG_CONTAINER,
        NG::ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>(), true);
    mgr.AllocateContainerId(hostNode);

    auto virtualNode = AceType::MakeRefPtr<NG::VirtualAccessibilityNode>();
    virtualNode->SetNodeId(TEST_ROOT_NODE_ID);
    virtualNode->SetRect(10, 20, 100, 50);
    virtualNode->SetRole("text");
    virtualNode->SetEnabled(true);

    auto accessibilityProperty = hostNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetVirtualNodeTreeRoot(virtualNode);

    Accessibility::AccessibilityElementInfo nodeInfo;
    CommonProperty commonProperty;
    commonProperty.windowLeft = 5;
    commonProperty.windowTop = 5;

    manager->UpdateAccessibilityElementInfoForVirtualNode(hostNode, virtualNode, commonProperty, nodeInfo, 0);

    auto bounds = nodeInfo.GetBoundsInScreen();
    int32_t hostLeft = static_cast<int32_t>(hostNode->GetTransformRectRelativeToWindow().Left());
    int32_t hostTop = static_cast<int32_t>(hostNode->GetTransformRectRelativeToWindow().Top());
    EXPECT_EQ(bounds.GetLeftTopXScreenPos(), hostLeft + 10 + 5);
    EXPECT_EQ(bounds.GetLeftTopYScreenPos(), hostTop + 20 + 5);
    EXPECT_EQ(bounds.GetRightBottomXScreenPos(), hostLeft + 10 + 5 + 100);
    EXPECT_EQ(bounds.GetRightBottomYScreenPos(), hostTop + 20 + 5 + 50);
}

/**
 * @tc.name: UpdateAccessibilityElementInfoForVirtualNode005
 * @tc.desc: Test child IDs are correctly added
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, UpdateAccessibilityElementInfoForVirtualNode005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create virtualNode with children, verify child IDs in nodeInfo
     * @tc.expected: child IDs match encoded virtual node accessibility IDs
     */
    auto& mgr = NG::VirtualNodeContainerIdManager::GetInstance();
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto hostNode = NG::FrameNode::CreateFrameNode(TEST_TAG_CONTAINER,
        NG::ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>(), true);
    auto containerId = mgr.AllocateContainerId(hostNode);

    auto root = CreateVirtualNodeTree();
    auto accessibilityProperty = hostNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetVirtualNodeTreeRoot(root);

    Accessibility::AccessibilityElementInfo nodeInfo;
    CommonProperty commonProperty;

    manager->UpdateAccessibilityElementInfoForVirtualNode(hostNode, root, commonProperty, nodeInfo, 0);
    auto childIds = nodeInfo.GetChildIds();
    ASSERT_EQ(childIds.size(), 2U);
    EXPECT_EQ(childIds[0],
        NG::VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, TEST_CHILD1_NODE_ID));
    EXPECT_EQ(childIds[1],
        NG::VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, TEST_CHILD2_NODE_ID));
}

// ==================== AddVirtualNodeChildrenToInfos ====================

/**
 * @tc.name: AddVirtualNodeChildrenToInfos001
 * @tc.desc: Test with null hostNode, should not crash
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, AddVirtualNodeChildrenToInfos001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call with null hostNode
     * @tc.expected: no crash, infos remains empty
     */
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto virtualNode = AceType::MakeRefPtr<NG::VirtualAccessibilityNode>();
    std::list<Accessibility::AccessibilityElementInfo> infos;
    CommonProperty commonProperty;

    manager->AddVirtualNodeChildrenToInfos(infos, nullptr, virtualNode, commonProperty, 0);
    EXPECT_TRUE(infos.empty());
}

/**
 * @tc.name: AddVirtualNodeChildrenToInfos002
 * @tc.desc: Test with null virtualNode, should not crash
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, AddVirtualNodeChildrenToInfos002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call with null virtualNode
     * @tc.expected: no crash, infos remains empty
     */
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto hostNode = NG::FrameNode::CreateFrameNode(TEST_TAG_CONTAINER,
        NG::ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>(), true);
    std::list<Accessibility::AccessibilityElementInfo> infos;
    CommonProperty commonProperty;

    manager->AddVirtualNodeChildrenToInfos(
        infos, hostNode, nullptr, commonProperty, 0);
    EXPECT_TRUE(infos.empty());
}

/**
 * @tc.name: AddVirtualNodeChildrenToInfos003
 * @tc.desc: Test with no children, infos remains empty
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, AddVirtualNodeChildrenToInfos003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call with virtualNode that has no children
     * @tc.expected: infos remains empty
     */
    auto& mgr = NG::VirtualNodeContainerIdManager::GetInstance();
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto hostNode = NG::FrameNode::CreateFrameNode(TEST_TAG_CONTAINER,
        NG::ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>(), true);
    mgr.AllocateContainerId(hostNode);

    auto virtualNode = AceType::MakeRefPtr<NG::VirtualAccessibilityNode>();
    virtualNode->SetNodeId(TEST_ROOT_NODE_ID);
    auto accessibilityProperty = hostNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetVirtualNodeTreeRoot(virtualNode);

    std::list<Accessibility::AccessibilityElementInfo> infos;
    CommonProperty commonProperty;

    manager->AddVirtualNodeChildrenToInfos(
        infos, hostNode, virtualNode, commonProperty, 0);
    EXPECT_TRUE(infos.empty());
}

/**
 * @tc.name: AddVirtualNodeChildrenToInfos004
 * @tc.desc: Test with children, infos populated correctly
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, AddVirtualNodeChildrenToInfos004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create virtual node with 2 children, call AddVirtualNodeChildrenToInfos
     * @tc.expected: infos has 2 entries, one per child
     */
    auto& mgr = NG::VirtualNodeContainerIdManager::GetInstance();
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto hostNode = NG::FrameNode::CreateFrameNode(TEST_TAG_CONTAINER,
        NG::ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>(), true);
    mgr.AllocateContainerId(hostNode);

    auto root = CreateVirtualNodeTree();
    auto accessibilityProperty = hostNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetVirtualNodeTreeRoot(root);

    std::list<Accessibility::AccessibilityElementInfo> infos;
    CommonProperty commonProperty;

    manager->AddVirtualNodeChildrenToInfos(infos, hostNode, root, commonProperty, 100);

    ASSERT_EQ(infos.size(), 2U);
    auto it = infos.begin();
    EXPECT_EQ(it->GetContent(), "child1");
    EXPECT_EQ(it->GetParent(), 100);
    ++it;
    EXPECT_EQ(it->GetContent(), "child2");
}

/**
 * @tc.name: AddVirtualNodeChildrenToInfos005
 * @tc.desc: Test with nested children (multi-level tree), all levels added
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, AddVirtualNodeChildrenToInfos005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create 3-level tree, call AddVirtualNodeChildrenToInfos
     * @tc.expected: infos has entries for all descendants (children + grandchildren)
     */
    auto& mgr = NG::VirtualNodeContainerIdManager::GetInstance();
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto hostNode = NG::FrameNode::CreateFrameNode(TEST_TAG_CONTAINER,
        NG::ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>(), true);
    mgr.AllocateContainerId(hostNode);

    auto root = AceType::MakeRefPtr<NG::VirtualAccessibilityNode>();
    root->SetNodeId(TEST_ROOT_NODE_ID);
    root->SetRect(TEST_ROOT_RECT_LEFT, TEST_ROOT_RECT_TOP, TEST_ROOT_RECT_WIDTH, TEST_ROOT_RECT_HEIGHT);
    root->SetRole("container");
    root->SetEnabled(true);

    auto child = AceType::MakeRefPtr<NG::VirtualAccessibilityNode>();
    child->SetNodeId(TEST_CHILD1_NODE_ID);
    child->SetRect(0, 0, 100, 100);
    child->SetRole("button");
    child->SetEnabled(true);

    auto grandChild = AceType::MakeRefPtr<NG::VirtualAccessibilityNode>();
    grandChild->SetNodeId(TEST_CHILD2_NODE_ID);
    grandChild->SetRect(0, 0, 50, 50);
    grandChild->SetRole("text");
    grandChild->SetEnabled(true);

    child->AddChild(grandChild);
    root->AddChild(child);

    auto accessibilityProperty = hostNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetVirtualNodeTreeRoot(root);

    std::list<Accessibility::AccessibilityElementInfo> infos;
    CommonProperty commonProperty;

    manager->AddVirtualNodeChildrenToInfos(infos, hostNode, root, commonProperty, 0);

    EXPECT_EQ(infos.size(), 2U);
}

// ==================== GetAllVirtualNodeElementId ====================

/**
 * @tc.name: GetAllVirtualNodeElementId001
 * @tc.desc: Test with node that has no accessibility property
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, GetAllVirtualNodeElementId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create hostNode without virtual node tree, call GetAllVirtualNodeElementId
     * @tc.expected: returns false (no HasVirtualNodeTreeRoot)
     */
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto hostNode = NG::FrameNode::CreateFrameNode(TEST_TAG_CONTAINER,
        NG::ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>(), true);

    std::list<Accessibility::AccessibilityElementInfo> infos;
    CommonProperty commonProperty;
    Accessibility::AccessibilityElementInfo parentNodeInfo;
    bool result = manager->GetAllVirtualNodeElementId(infos, commonProperty, hostNode, parentNodeInfo);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetAllVirtualNodeElementId002
 * @tc.desc: Test with node that has virtual node tree root
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, GetAllVirtualNodeElementId002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set up hostNode with virtual node tree, call GetAllVirtualNodeElementId
     * @tc.expected: returns true, infos populated with root + children, old children removed from parent
     */
    auto& mgr = NG::VirtualNodeContainerIdManager::GetInstance();
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto hostNode = NG::FrameNode::CreateFrameNode(TEST_TAG_CONTAINER,
        NG::ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>(), true);
    mgr.AllocateContainerId(hostNode);

    auto root = CreateVirtualNodeTree();
    auto accessibilityProperty = hostNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetVirtualNodeTreeRoot(root);

    std::list<Accessibility::AccessibilityElementInfo> infos;
    CommonProperty commonProperty;
    Accessibility::AccessibilityElementInfo parentNodeInfo;
    parentNodeInfo.AddChild(111);
    parentNodeInfo.AddChild(222);

    bool result = manager->GetAllVirtualNodeElementId(infos, commonProperty, hostNode, parentNodeInfo);
    EXPECT_TRUE(result);
    EXPECT_EQ(infos.size(), 3U);
    auto childIds = parentNodeInfo.GetChildIds();
    ASSERT_EQ(childIds.size(), 1U);
}

/**
 * @tc.name: GetAllVirtualNodeElementId003
 * @tc.desc: Test that old children are removed and virtual root is added
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, GetAllVirtualNodeElementId003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set parentNodeInfo with children, call GetAllVirtualNodeElementId
     * @tc.expected: old children removed, virtual root ID added as only child
     */
    auto& mgr = NG::VirtualNodeContainerIdManager::GetInstance();
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto hostNode = NG::FrameNode::CreateFrameNode(TEST_TAG_CONTAINER,
        NG::ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>(), true);
    auto containerId = mgr.AllocateContainerId(hostNode);
    auto virtualRoot = AceType::MakeRefPtr<NG::VirtualAccessibilityNode>();
    virtualRoot->SetNodeId(5);
    virtualRoot->SetRect(0, 0, 100, 100);
    virtualRoot->SetRole("container");
    virtualRoot->SetEnabled(true);
    auto accessibilityProperty = hostNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetVirtualNodeTreeRoot(virtualRoot);

    std::list<Accessibility::AccessibilityElementInfo> infos;
    CommonProperty commonProperty;
    Accessibility::AccessibilityElementInfo parentNodeInfo;
    parentNodeInfo.AddChild(10);
    parentNodeInfo.AddChild(20);
    parentNodeInfo.AddChild(30);
    ASSERT_EQ(parentNodeInfo.GetChildIds().size(), 3U);

    bool result = manager->GetAllVirtualNodeElementId(
        infos, commonProperty, hostNode, parentNodeInfo);

    EXPECT_TRUE(result);
    auto childIds = parentNodeInfo.GetChildIds();
    ASSERT_EQ(childIds.size(), 1U);
    int64_t expectedRootId =
        NG::VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, 5);
    EXPECT_EQ(childIds[0], expectedRootId);
}

// ==================== SearchAccessibilityVirtualNode ====================

/**
 * @tc.name: SearchAccessibilityVirtualNode001
 * @tc.desc: Test with non-virtual-node container ID, returns false
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, SearchAccessibilityVirtualNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call SearchAccessibilityVirtualNode with plain element ID
     * @tc.expected: returns false for non-virtual-node ID
     */
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    std::list<Accessibility::AccessibilityElementInfo> infos;
    auto ngPipeline = NG::MockPipelineContext::GetCurrentContext();
    bool result = manager->SearchAccessibilityVirtualNode(100, infos, ngPipeline);
    EXPECT_FALSE(result);
    EXPECT_TRUE(infos.empty());
}

/**
 * @tc.name: SearchAccessibilityVirtualNode002
 * @tc.desc: Test with valid virtual node container ID but node not found
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, SearchAccessibilityVirtualNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create virtual node, encode ID with non-existing node ID
     * @tc.expected: returns false because CheckAndGetVirtualNode fails
     */
    auto& mgr = NG::VirtualNodeContainerIdManager::GetInstance();
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto hostNode = NG::FrameNode::CreateFrameNode(TEST_TAG_CONTAINER,
        NG::ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>(), true);
    auto containerId = mgr.AllocateContainerId(hostNode);
    auto virtualRoot = AceType::MakeRefPtr<NG::VirtualAccessibilityNode>();
    virtualRoot->SetNodeId(TEST_ROOT_NODE_ID);
    virtualRoot->SetRect(0, 0, 100, 100);
    virtualRoot->SetRole("text");
    virtualRoot->SetEnabled(true);
    auto accessibilityProperty = hostNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetVirtualNodeTreeRoot(virtualRoot);
    int64_t elementId =
        NG::VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, TEST_NONEXISTENT_NODE_ID);
    std::list<Accessibility::AccessibilityElementInfo> infos;
    auto ngPipeline = NG::MockPipelineContext::GetCurrentContext();
    bool result = manager->SearchAccessibilityVirtualNode(elementId, infos, ngPipeline);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SearchAccessibilityVirtualNode003
 * @tc.desc: Test with valid virtual node container ID and node found
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, SearchAccessibilityVirtualNode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create virtual node tree, search for existing child node
     * @tc.expected: returns true, infos has one entry with correct properties
     */
    auto& mgr = NG::VirtualNodeContainerIdManager::GetInstance();
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto hostNode = NG::FrameNode::CreateFrameNode(TEST_TAG_CONTAINER,
        NG::ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>(), true);
    auto containerId = mgr.AllocateContainerId(hostNode);

    auto root = CreateVirtualNodeTree();
    auto accessibilityProperty = hostNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetVirtualNodeTreeRoot(root);

    int64_t elementId =
        NG::VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, TEST_CHILD1_NODE_ID);
    std::list<Accessibility::AccessibilityElementInfo> infos;
    auto ngPipeline = NG::MockPipelineContext::GetCurrentContext();

    bool result = manager->SearchAccessibilityVirtualNode(elementId, infos, ngPipeline);
    EXPECT_TRUE(result);
    ASSERT_EQ(infos.size(), 1U);
    auto& info = infos.front();
    EXPECT_EQ(info.GetComponentType(), "button");
    EXPECT_EQ(info.GetContent(), "child1");
}

// ==================== CheckAndGetVirtualNode ====================

/**
 * @tc.name: CheckAndGetVirtualNode001
 * @tc.desc: Test CheckAndGetVirtualNode with non-virtual-node ID returns false
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, CheckAndGetVirtualNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call with plain element ID (not a virtual container ID)
     * @tc.expected: returns false
     */
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    RefPtr<NG::VirtualAccessibilityNode> virtualNode;
    RefPtr<NG::FrameNode> parentNode;

    // The function is static and file-local in js_accessibility_manager.cpp,
    // so we test it indirectly through SearchAccessibilityVirtualNode
    std::list<Accessibility::AccessibilityElementInfo> infos;
    auto ngPipeline = NG::MockPipelineContext::GetCurrentContext();
    bool result = manager->SearchAccessibilityVirtualNode(42, infos, ngPipeline);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckAndGetVirtualNode002
 * @tc.desc: Test with virtual ID but container node has no virtual tree root
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, CheckAndGetVirtualNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. allocate container ID but don't set virtual tree root
     * @tc.expected: SearchAccessibilityVirtualNode returns false
     */
    auto& mgr = NG::VirtualNodeContainerIdManager::GetInstance();
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto hostNode = NG::FrameNode::CreateFrameNode(TEST_TAG_CONTAINER,
        NG::ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>(), true);
    auto containerId = mgr.AllocateContainerId(hostNode);

    int64_t elementId = NG::VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, 1);
    std::list<Accessibility::AccessibilityElementInfo> infos;
    auto ngPipeline = NG::MockPipelineContext::GetCurrentContext();

    bool result = manager->SearchAccessibilityVirtualNode(elementId, infos, ngPipeline);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckAndGetVirtualNode003
 * @tc.desc: Test with valid virtual ID and matching node in tree
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, CheckAndGetVirtualNode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set up virtual tree and search for root node by ID
     * @tc.expected: SearchAccessibilityVirtualNode returns true and correct info
     */
    auto& mgr = NG::VirtualNodeContainerIdManager::GetInstance();
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto hostNode = NG::FrameNode::CreateFrameNode(TEST_TAG_CONTAINER,
        NG::ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>(), true);
    auto containerId = mgr.AllocateContainerId(hostNode);

    auto root = AceType::MakeRefPtr<NG::VirtualAccessibilityNode>();
    root->SetNodeId(42);
    root->SetRect(0, 0, 100, 100);
    root->SetRole("button");
    root->SetAccessibilityText("foundMe");
    root->SetEnabled(true);
    root->SetAccessibilityFocused(true);

    auto accessibilityProperty = hostNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetVirtualNodeTreeRoot(root);

    int64_t elementId = NG::VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, 42);
    std::list<Accessibility::AccessibilityElementInfo> infos;
    auto ngPipeline = NG::MockPipelineContext::GetCurrentContext();

    bool result = manager->SearchAccessibilityVirtualNode(elementId, infos, ngPipeline);
    EXPECT_TRUE(result);
    ASSERT_EQ(infos.size(), 1U);
    EXPECT_EQ(infos.front().GetContent(), "foundMe");
    EXPECT_EQ(infos.front().GetComponentType(), "button");
    EXPECT_EQ(infos.front().GetAccessibilityFocus(), true);
}

// ================= AccessibilityFocused propagation in UpdateAccessibilityElementInfoForVirtualNode =================

/**
 * @tc.name: UpdateAccessibilityElementInfoForVirtualNodeFocused001
 * @tc.desc: Test AccessibilityFocused=false correctly propagated
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerVirtualNodeTest, UpdateAccessibilityElementInfoForVirtualNodeFocused001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create virtualNode with AccessibilityFocused=false
     * @tc.expected: nodeInfo AccessibilityFocus is false
     */
    auto& mgr = NG::VirtualNodeContainerIdManager::GetInstance();
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto hostNode = NG::FrameNode::CreateFrameNode(TEST_TAG_CONTAINER,
        NG::ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>(), true);
    mgr.AllocateContainerId(hostNode);

    auto virtualNode = AceType::MakeRefPtr<NG::VirtualAccessibilityNode>();
    virtualNode->SetNodeId(TEST_ROOT_NODE_ID);
    virtualNode->SetRect(0, 0, 100, 100);
    virtualNode->SetRole("text");
    virtualNode->SetEnabled(true);
    virtualNode->SetAccessibilityFocused(false);

    auto accessibilityProperty = hostNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetVirtualNodeTreeRoot(virtualNode);

    Accessibility::AccessibilityElementInfo nodeInfo;
    CommonProperty commonProperty;

    manager->UpdateAccessibilityElementInfoForVirtualNode(hostNode, virtualNode, commonProperty, nodeInfo, 0);

    EXPECT_EQ(nodeInfo.GetAccessibilityFocus(), false);
}

} // namespace OHOS::Ace
