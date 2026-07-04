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
#include "base/log/dump_log.h"
#include "frameworks/core/accessibility/utils/accessibility_manager_utils.h"

using namespace testing;
using namespace testing::ext;

namespace {
const char* const TEST_TAG_CUSTOM = "customNode";
} // namespace

namespace OHOS::Ace::NG {

class AccessibilityManagerUtilsTestThree : public testing::Test {
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

void AccessibilityManagerUtilsTestThree::SetUpTestCase()
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

void AccessibilityManagerUtilsTestThree::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

// ==================== VirtualNodeContainerIdManager AllocateContainerId same node returns same ID ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerAllocateContainerId001
 * @tc.desc: Test AllocateContainerId returns same ID for same node
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerAllocateContainerId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. allocate twice for the same node
     * @tc.expected: both allocations return the same ID
     */
    auto node = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node, nullptr);
    auto id1 = VirtualNodeContainerIdManager::GetInstance().AllocateContainerId(node);
    auto id2 = VirtualNodeContainerIdManager::GetInstance().AllocateContainerId(node);
    EXPECT_EQ(id1, id2);
    EXPECT_NE(id1, 0);
}

/**
 * @tc.name: VirtualNodeContainerIdManagerReleaseContainerId001
 * @tc.desc: Test ReleaseContainerId by unallocated FrameNode does nothing
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerReleaseContainerId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a node without allocating, then release by node
     * @tc.expected: no crash, count stays 0
     */
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    auto node = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node, nullptr);
    mgr.ReleaseContainerId(node);
    EXPECT_EQ(mgr.GetContainerCount(), 0);
}

// ==================== VirtualNodeContainerIdManager AllocateContainerId reuse released ID ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerAllocateContainerId002
 * @tc.desc: Test that released ID is reused by next allocation
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerAllocateContainerId002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. allocate one node, get ID, release it, allocate another
     * @tc.expected: the second allocation reuses the released ID
     */
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    auto node1 = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node1, nullptr);
    auto id1 = mgr.AllocateContainerId(node1);
    EXPECT_NE(id1, 0);
    mgr.ReleaseContainerId(id1);

    auto node2 = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node2, nullptr);
    auto id2 = mgr.AllocateContainerId(node2);
    EXPECT_EQ(id1, id2);
}

// ==================== VirtualNodeContainerIdManager multiple nodes sequential ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerAllocateContainerId003
 * @tc.desc: Test allocating multiple nodes returns sequential IDs
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerAllocateContainerId003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. allocate 3 different nodes
     * @tc.expected: all get unique IDs, count is 3
     */
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    auto node1 = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    auto node2 = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    auto node3 = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node1, nullptr);
    ASSERT_NE(node2, nullptr);
    ASSERT_NE(node3, nullptr);
    auto id1 = mgr.AllocateContainerId(node1);
    auto id2 = mgr.AllocateContainerId(node2);
    auto id3 = mgr.AllocateContainerId(node3);
    EXPECT_NE(id1, 0);
    EXPECT_NE(id2, 0);
    EXPECT_NE(id3, 0);
    EXPECT_EQ(mgr.GetContainerCount(), 3);
}

// ==================== VirtualNodeContainerIdManager ExtractContainerId ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerExtractContainerId001
 * @tc.desc: Test ExtractContainerId from encoded ID
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerExtractContainerId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. encode and extract container ID
     * @tc.expected: extracted container ID matches the original
     */
    uint8_t containerId = 42;
    int64_t componentId = 100;
    auto encoded = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, componentId);
    auto extracted = VirtualNodeContainerIdManager::ExtractContainerId(encoded);
    EXPECT_EQ(extracted, containerId);
}

// ==================== VirtualNodeContainerIdManager ExtractComponentId ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerExtractComponentId001
 * @tc.desc: Test ExtractComponentId from encoded ID
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerExtractComponentId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. encode and extract component ID
     * @tc.expected: extracted component ID matches the original
     */
    uint8_t containerId = 5;
    int64_t componentId = 999;
    auto encoded = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, componentId);
    auto extracted = VirtualNodeContainerIdManager::ExtractComponentId(encoded);
    EXPECT_EQ(extracted, componentId);
}

/**
 * @tc.name: VirtualNodeContainerIdManagerExtractComponentId002
 * @tc.desc: Test ExtractComponentId with negative component ID
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerExtractComponentId002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. encode with negative component ID, extract it
     * @tc.expected: negative component ID is preserved via sign extension
     */
    uint8_t containerId = 10;
    int64_t componentId = -42;
    auto encoded = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, componentId);
    auto extracted = VirtualNodeContainerIdManager::ExtractComponentId(encoded);
    EXPECT_EQ(extracted, componentId);
}

/**
 * @tc.name: VirtualNodeContainerIdManagerExtractComponentId003
 * @tc.desc: Test ExtractComponentId with INT32_MIN
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerExtractComponentId003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. encode with INT32_MIN, extract component ID
     * @tc.expected: INT32_MIN is correctly preserved
     */
    uint8_t containerId = 1;
    int64_t componentId = INT32_MIN;
    auto encoded = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, componentId);
    auto extracted = VirtualNodeContainerIdManager::ExtractComponentId(encoded);
    EXPECT_EQ(extracted, componentId);
}

// ==================== VirtualNodeContainerIdManager GetParentAccessibilityId ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerGetParentAccessibilityId001
 * @tc.desc: Test GetParentAccessibilityId clears container ID bits
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerGetParentAccessibilityId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. encode an ID, get parent accessibility ID
     * @tc.expected: parent ID has container ID bits cleared, component ID preserved
     */
    uint8_t containerId = 5;
    int64_t componentId = 42;
    auto encoded = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, componentId);
    auto parentId = VirtualNodeContainerIdManager::GetParentAccessibilityId(encoded);
    auto extractedComponent = VirtualNodeContainerIdManager::ExtractComponentId(parentId);
    EXPECT_EQ(extractedComponent, componentId);
    EXPECT_FALSE(VirtualNodeContainerIdManager::IsVirtualNodeContainerId(parentId));
}

/**
 * @tc.name: VirtualNodeContainerIdManagerGetParentAccessibilityId002
 * @tc.desc: Test GetParentAccessibilityId with negative component ID
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerGetParentAccessibilityId002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. encode with negative componentId, get parent
     * @tc.expected: component ID preserved, container bits cleared
     */
    uint8_t containerId = 128;
    int64_t componentId = -100;
    auto encoded = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, componentId);
    auto parentId = VirtualNodeContainerIdManager::GetParentAccessibilityId(encoded);
    EXPECT_FALSE(VirtualNodeContainerIdManager::IsVirtualNodeContainerId(parentId));
}

// ==================== VirtualNodeContainerIdManager EncodeDecode edge cases ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerEncodeDecode001
 * @tc.desc: Test encode/decode with containerId=1 and componentId=0
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerEncodeDecode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. encode with containerId=1, componentId=0
     * @tc.expected: decoded values match
     */
    uint8_t containerId = 1;
    int64_t componentId = 0;
    auto encoded = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, componentId);
    uint8_t decodedContainerId = 0;
    int64_t decodedComponentId = 0;
    VirtualNodeContainerIdManager::DecodeAccessibilityId(encoded, decodedContainerId, decodedComponentId);
    EXPECT_EQ(decodedContainerId, containerId);
    EXPECT_EQ(decodedComponentId, componentId);
}

/**
 * @tc.name: VirtualNodeContainerIdManagerEncodeDecode002
 * @tc.desc: Test encode/decode with INT32_MIN componentId
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerEncodeDecode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. encode with containerId=128, componentId=INT32_MIN
     * @tc.expected: decoded values match
     */
    uint8_t containerId = 128;
    int64_t componentId = INT32_MIN;
    auto encoded = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, componentId);
    uint8_t decodedContainerId = 0;
    int64_t decodedComponentId = 0;
    VirtualNodeContainerIdManager::DecodeAccessibilityId(encoded, decodedContainerId, decodedComponentId);
    EXPECT_EQ(decodedContainerId, containerId);
    EXPECT_EQ(decodedComponentId, componentId);
}

// ==================== VirtualNodeContainerIdManager IsVirtualNodeContainerId edge cases ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerIsVirtualNodeContainerId001
 * @tc.desc: Test IsVirtualNodeContainerId with zero accessibilityId
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerIsVirtualNodeContainerId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. check with 0
     * @tc.expected: returns false
     */
    EXPECT_FALSE(VirtualNodeContainerIdManager::IsVirtualNodeContainerId(0));
}

/**
 * @tc.name: VirtualNodeContainerIdManagerIsVirtualNodeContainerId002
 * @tc.desc: Test IsVirtualNodeContainerId with various encoded IDs
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerIsVirtualNodeContainerId002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. check encoded IDs with container 1, 128, 255
     * @tc.expected: all return true
     */
    EXPECT_TRUE(VirtualNodeContainerIdManager::IsVirtualNodeContainerId(
        VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(1, 0)));
    EXPECT_TRUE(VirtualNodeContainerIdManager::IsVirtualNodeContainerId(
        VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(128, 0)));
    EXPECT_TRUE(VirtualNodeContainerIdManager::IsVirtualNodeContainerId(
        VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(255, 0)));
}

// ==================== VirtualNodeContainerIdManager GetContainerNode after node destroyed ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerGetContainerNode001
 * @tc.desc: Test GetContainerNode returns nullptr when node has been released
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerGetContainerNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. allocate, release, then try to get node
     * @tc.expected: returns nullptr
     */
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    auto node = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node, nullptr);
    auto id = mgr.AllocateContainerId(node);
    EXPECT_NE(id, 0);
    mgr.ReleaseContainerId(id);
    EXPECT_EQ(mgr.GetContainerNode(id), nullptr);
}

// ==================== VirtualAccessibilityNode geometry tests ====================

/**
 * @tc.name: VirtualAccessibilityNodeSetRectAndGet001
 * @tc.desc: Test SetRect and GetRect with NG::RectT
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeSetRectAndGet001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node, set rect with RectT, verify all getters
     * @tc.expected: all position/size getters return correct values
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    NG::RectT<int32_t> rect(10, 20, 100, 50);
    node->SetRect(rect);
    EXPECT_EQ(node->GetLeft(), 10);
    EXPECT_EQ(node->GetTop(), 20);
    EXPECT_EQ(node->GetWidth(), 100);
    EXPECT_EQ(node->GetHeight(), 50);
    EXPECT_EQ(node->GetRight(), 110);
    EXPECT_EQ(node->GetBottom(), 70);
}

/**
 * @tc.name: VirtualAccessibilityNodeSetRectAndGet002
 * @tc.desc: Test SetRect with individual parameters
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeSetRectAndGet002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set rect by left, top, width, height
     * @tc.expected: rect values are set correctly
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    node->SetRect(5, 15, 200, 300);
    auto& rect = node->GetRect();
    EXPECT_EQ(rect.Left(), 5);
    EXPECT_EQ(rect.Top(), 15);
    EXPECT_EQ(rect.Width(), 200);
    EXPECT_EQ(rect.Height(), 300);
}

// ==================== VirtualAccessibilityNode ContainsPoint ====================

/**
 * @tc.name: VirtualAccessibilityNodeContainsPoint001
 * @tc.desc: Test ContainsPoint with point inside rect
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeContainsPoint001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set rect (0,0,100,100), check point (50,50)
     * @tc.expected: returns true
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    node->SetRect(0, 0, 100, 100);
    EXPECT_TRUE(node->ContainsPoint(50, 50));
}

/**
 * @tc.name: VirtualAccessibilityNodeContainsPoint002
 * @tc.desc: Test ContainsPoint with point outside rect
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeContainsPoint002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set rect (0,0,100,100), check point (200,200)
     * @tc.expected: returns false
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    node->SetRect(0, 0, 100, 100);
    EXPECT_FALSE(node->ContainsPoint(200, 200));
}

/**
 * @tc.name: VirtualAccessibilityNodeContainsPoint003
 * @tc.desc: Test ContainsPoint at rect boundary
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeContainsPoint003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set rect (10,10,100,100), check points at edges
     * @tc.expected: boundary behavior is consistent
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    node->SetRect(10, 10, 100, 100);
    EXPECT_TRUE(node->ContainsPoint(10, 10));
    EXPECT_TRUE(node->ContainsPoint(109, 109));
    EXPECT_FALSE(node->ContainsPoint(110, 110));
}

// ==================== VirtualAccessibilityNode Intersects ====================

/**
 * @tc.name: VirtualAccessibilityNodeIntersects001
 * @tc.desc: Test Intersects with overlapping rect
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeIntersects001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set rect (0,0,100,100), check intersection with (50,50,100,100)
     * @tc.expected: returns true
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    node->SetRect(0, 0, 100, 100);
    NG::RectT<int32_t> other(50, 50, 100, 100);
    EXPECT_TRUE(node->Intersects(other));
}

/**
 * @tc.name: VirtualAccessibilityNodeIntersects002
 * @tc.desc: Test Intersects with non-overlapping rect
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeIntersects002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set rect (0,0,100,100), check intersection with (200,200,100,100)
     * @tc.expected: returns false
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    node->SetRect(0, 0, 100, 100);
    NG::RectT<int32_t> other(200, 200, 100, 100);
    EXPECT_FALSE(node->Intersects(other));
}

// ==================== VirtualAccessibilityNode HitTest ====================

/**
 * @tc.name: VirtualAccessibilityNodeHitTest001
 * @tc.desc: Test HitTest with point inside single node (no children)
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeHitTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node with rect (0,0,100,100), hit test at (50,50)
     * @tc.expected: returns the node itself
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    node->SetRect(0, 0, 100, 100);
    node->SetNodeId(1);
    auto result = node->HitTest(50, 50);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetNodeId(), 1);
}

/**
 * @tc.name: VirtualAccessibilityNodeHitTest002
 * @tc.desc: Test HitTest with point outside returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeHitTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node with rect (0,0,100,100), hit test at (200,200)
     * @tc.expected: returns nullptr
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    node->SetRect(0, 0, 100, 100);
    auto result = node->HitTest(200, 200);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: VirtualAccessibilityNodeHitTest003
 * @tc.desc: Test HitTest with children returns deepest match (last child priority)
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeHitTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. parent (0,0,200,200), child1 (0,0,100,100), child2 (100,0,100,100)
     *             hit test at (50,50)
     * @tc.expected: returns child1
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    parent->SetRect(0, 0, 200, 200);
    parent->SetNodeId(1);

    auto child1 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    child1->SetRect(0, 0, 100, 100);
    child1->SetNodeId(2);

    auto child2 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    child2->SetRect(100, 0, 100, 100);
    child2->SetNodeId(3);

    parent->AddChild(child1);
    parent->AddChild(child2);

    auto result = parent->HitTest(50, 50);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetNodeId(), 2);
}

/**
 * @tc.name: VirtualAccessibilityNodeHitTest004
 * @tc.desc: Test HitTest with overlapping children returns last child (right-reversed order)
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeHitTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. parent (0,0,200,200), child1 (0,0,200,200), child2 (0,0,200,200)
     *             hit test at (100,100)
     * @tc.expected: returns child2 (last in rbegin iteration)
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    parent->SetRect(0, 0, 200, 200);
    parent->SetNodeId(1);

    auto child1 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    child1->SetRect(0, 0, 200, 200);
    child1->SetNodeId(2);

    auto child2 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    child2->SetRect(0, 0, 200, 200);
    child2->SetNodeId(3);

    parent->AddChild(child1);
    parent->AddChild(child2);

    auto result = parent->HitTest(100, 100);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetNodeId(), 3);
}

/**
 * @tc.name: VirtualAccessibilityNodeHitTest005
 * @tc.desc: Test HitTest with float coordinates
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeHitTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. hit test with float x=50.5, y=50.5
     * @tc.expected: truncates to int and returns the node
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    node->SetRect(0, 0, 100, 100);
    node->SetNodeId(1);
    auto result = node->HitTest(50.5f, 50.5f);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetNodeId(), 1);
}

/**
 * @tc.name: VirtualAccessibilityNodeHitTest006
 * @tc.desc: Test HitTest with PointF
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeHitTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. hit test with PointF
     * @tc.expected: returns the node
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    node->SetRect(0, 0, 100, 100);
    node->SetNodeId(1);
    NG::PointF point(50.0f, 50.0f);
    auto result = node->HitTest(point);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetNodeId(), 1);
}

/**
 * @tc.name: VirtualAccessibilityNodeHitTest007
 * @tc.desc: Test HitTest with parent containing point but no children at that point
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeHitTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. parent (0,0,200,200), child (0,0,50,50), hit at (100,100)
     * @tc.expected: child doesn't contain point, returns parent
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    parent->SetRect(0, 0, 200, 200);
    parent->SetNodeId(1);

    auto child = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    child->SetRect(0, 0, 50, 50);
    child->SetNodeId(2);

    parent->AddChild(child);

    auto result = parent->HitTest(100, 100);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetNodeId(), 1);
}

// ==================== VirtualAccessibilityNode GetGlobalRect ====================

/**
 * @tc.name: VirtualAccessibilityNodeGetGlobalRect001
 * @tc.desc: Test GetGlobalRect with no parent returns own rect
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeGetGlobalRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node with rect, no parent
     * @tc.expected: global rect equals local rect
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    node->SetRect(10, 20, 100, 50);
    auto globalRect = node->GetGlobalRect();
    EXPECT_EQ(globalRect.Left(), 10);
    EXPECT_EQ(globalRect.Top(), 20);
    EXPECT_EQ(globalRect.Width(), 100);
    EXPECT_EQ(globalRect.Height(), 50);
}

/**
 * @tc.name: VirtualAccessibilityNodeGetGlobalRect002
 * @tc.desc: Test GetGlobalRect with parent offset
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeGetGlobalRect002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. parent at (100,200,300,300), child at (10,20,50,50)
     * @tc.expected: child global rect is (110, 220, 50, 50)
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    parent->SetRect(100, 200, 300, 300);

    auto child = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    child->SetRect(10, 20, 50, 50);
    parent->AddChild(child);

    auto globalRect = child->GetGlobalRect();
    EXPECT_EQ(globalRect.Left(), 110);
    EXPECT_EQ(globalRect.Top(), 220);
    EXPECT_EQ(globalRect.Width(), 50);
    EXPECT_EQ(globalRect.Height(), 50);
}

/**
 * @tc.name: VirtualAccessibilityNodeGetGlobalRect003
 * @tc.desc: Test GetGlobalRect with multi-level nesting
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeGetGlobalRect003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. root at (10,10,500,500), child at (20,20,200,200), grandchild at (5,5,50,50)
     * @tc.expected: grandchild global rect is (35, 35, 50, 50)
     */
    auto root = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    root->SetRect(10, 10, 500, 500);

    auto child = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    child->SetRect(20, 20, 200, 200);
    root->AddChild(child);

    auto grandChild = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    grandChild->SetRect(5, 5, 50, 50);
    child->AddChild(grandChild);

    auto globalRect = grandChild->GetGlobalRect();
    EXPECT_EQ(globalRect.Left(), 35);
    EXPECT_EQ(globalRect.Top(), 35);
}

// ==================== VirtualAccessibilityNode FindNodeByPoint ====================

/**
 * @tc.name: VirtualAccessibilityNodeFindNodeByPoint001
 * @tc.desc: Test FindNodeByPoint with point outside returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeFindNodeByPoint001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set rect (0,0,100,100), find by point (200,200)
     * @tc.expected: returns nullptr
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    node->SetRect(0, 0, 100, 100);
    auto result = node->FindNodeByPoint(200, 200);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: VirtualAccessibilityNodeFindNodeByPoint002
 * @tc.desc: Test FindNodeByPoint returns last matching child (left-to-right iteration)
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeFindNodeByPoint002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. parent (0,0,200,200), child1 (0,0,200,200), child2 (0,0,200,200)
     *             find by point (100,100)
     * @tc.expected: returns child2 (last matching child in forward order)
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    parent->SetRect(0, 0, 200, 200);
    parent->SetNodeId(1);

    auto child1 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    child1->SetRect(0, 0, 200, 200);
    child1->SetNodeId(2);

    auto child2 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    child2->SetRect(0, 0, 200, 200);
    child2->SetNodeId(3);

    parent->AddChild(child1);
    parent->AddChild(child2);

    auto result = parent->FindNodeByPoint(100, 100);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetNodeId(), 3);
}

/**
 * @tc.name: VirtualAccessibilityNodeFindNodeByPoint003
 * @tc.desc: Test FindNodeByPoint with no children returns self
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeFindNodeByPoint003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. single node, find by point inside
     * @tc.expected: returns self
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    node->SetRect(0, 0, 100, 100);
    node->SetNodeId(42);
    auto result = node->FindNodeByPoint(50, 50);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetNodeId(), 42);
}

// ==================== VirtualAccessibilityNode RemoveChild ====================

/**
 * @tc.name: VirtualAccessibilityNodeRemoveChild001
 * @tc.desc: Test RemoveChild removes child and resets parent
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeRemoveChild001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add child, remove child, verify parent is null and child count is 0
     * @tc.expected: child removed, parent reset
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    parent->SetNodeId(1);
    auto child = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    child->SetNodeId(2);
    parent->AddChild(child);
    EXPECT_EQ(parent->GetChildCount(), 1u);
    EXPECT_NE(child->GetParent(), nullptr);

    parent->RemoveChild(child);
    EXPECT_EQ(parent->GetChildCount(), 0u);
    EXPECT_EQ(child->GetParent(), nullptr);
}

/**
 * @tc.name: VirtualAccessibilityNodeRemoveChild002
 * @tc.desc: Test RemoveChild with null child does not crash
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeRemoveChild002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call RemoveChild with nullptr
     * @tc.expected: no crash
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    parent->RemoveChild(nullptr);
    EXPECT_EQ(parent->GetChildCount(), 0u);
}

/**
 * @tc.name: VirtualAccessibilityNodeRemoveChild003
 * @tc.desc: Test RemoveChild with non-child does nothing
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeRemoveChild003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. try to remove a node that is not a child
     * @tc.expected: no crash, child count unchanged
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto child1 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto child2 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    parent->AddChild(child1);
    parent->RemoveChild(child2);
    EXPECT_EQ(parent->GetChildCount(), 1u);
}

// ==================== VirtualAccessibilityNode ClearChildren ====================

/**
 * @tc.name: VirtualAccessibilityNodeClearChildren001
 * @tc.desc: Test ClearChildren removes all children and resets their parents
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeClearChildren001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add 3 children, clear them
     * @tc.expected: no children remain, all parents reset
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto c1 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto c2 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto c3 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    parent->AddChild(c1);
    parent->AddChild(c2);
    parent->AddChild(c3);
    EXPECT_EQ(parent->GetChildCount(), 3u);

    parent->ClearChildren();
    EXPECT_EQ(parent->GetChildCount(), 0u);
    EXPECT_FALSE(parent->HasChildren());
    EXPECT_EQ(c1->GetParent(), nullptr);
    EXPECT_EQ(c2->GetParent(), nullptr);
    EXPECT_EQ(c3->GetParent(), nullptr);
}

// ==================== VirtualAccessibilityNode GetChild ====================

/**
 * @tc.name: VirtualAccessibilityNodeGetChild001
 * @tc.desc: Test GetChild with valid index
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeGetChild001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add 2 children, get by index
     * @tc.expected: returns correct child at each index
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto c1 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    c1->SetNodeId(10);
    auto c2 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    c2->SetNodeId(20);
    parent->AddChild(c1);
    parent->AddChild(c2);

    auto child0 = parent->GetChild(0);
    ASSERT_NE(child0, nullptr);
    EXPECT_EQ(child0->GetNodeId(), 10);
    auto child1 = parent->GetChild(1);
    ASSERT_NE(child1, nullptr);
    EXPECT_EQ(child1->GetNodeId(), 20);
}

/**
 * @tc.name: VirtualAccessibilityNodeGetChild002
 * @tc.desc: Test GetChild with out-of-bounds index returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeGetChild002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get child at index 5 from node with 0 children
     * @tc.expected: returns nullptr
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    EXPECT_EQ(parent->GetChild(0), nullptr);
    EXPECT_EQ(parent->GetChild(5), nullptr);
}

// ==================== VirtualAccessibilityNode FindChild ====================

/**
 * @tc.name: VirtualAccessibilityNodeFindChild001
 * @tc.desc: Test FindChild finds matching child
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeFindChild001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add children with different IDs, find by predicate
     * @tc.expected: returns the matching child
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto c1 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    c1->SetNodeId(10);
    auto c2 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    c2->SetNodeId(20);
    parent->AddChild(c1);
    parent->AddChild(c2);

    auto found = parent->FindChild([](const RefPtr<VirtualAccessibilityNode>& node) {
        return node->GetNodeId() == 20;
    });
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->GetNodeId(), 20);
}

/**
 * @tc.name: VirtualAccessibilityNodeFindChild002
 * @tc.desc: Test FindChild returns nullptr when no match
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeFindChild002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. search for non-existent ID
     * @tc.expected: returns nullptr
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto c1 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    c1->SetNodeId(10);
    parent->AddChild(c1);

    auto found = parent->FindChild([](const RefPtr<VirtualAccessibilityNode>& node) {
        return node->GetNodeId() == 999;
    });
    EXPECT_EQ(found, nullptr);
}

/**
 * @tc.name: VirtualAccessibilityNodeFindChild003
 * @tc.desc: Test FindChild with depth-first search
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeFindChild003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create 2-level tree, search for grandchild
     * @tc.expected: finds the grandchild via DFS
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto child = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    child->SetNodeId(10);
    auto grandChild = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    grandChild->SetNodeId(20);
    child->AddChild(grandChild);
    parent->AddChild(child);

    auto found = parent->FindChild([](const RefPtr<VirtualAccessibilityNode>& node) {
        return node->GetNodeId() == 20;
    });
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->GetNodeId(), 20);
}

// ==================== VirtualAccessibilityNode FindNodeById ====================

/**
 * @tc.name: VirtualAccessibilityNodeFindNodeById001
 * @tc.desc: Test FindNodeById finds self
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeFindNodeById001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. search for own ID
     * @tc.expected: returns self
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    node->SetNodeId(42);
    auto found = node->FindNodeById(42);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->GetNodeId(), 42);
}

/**
 * @tc.name: VirtualAccessibilityNodeFindNodeById002
 * @tc.desc: Test FindNodeById finds child
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeFindNodeById002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. search for child ID from parent
     * @tc.expected: returns the child
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    parent->SetNodeId(1);
    auto child = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    child->SetNodeId(42);
    parent->AddChild(child);

    auto found = parent->FindNodeById(42);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->GetNodeId(), 42);
}

/**
 * @tc.name: VirtualAccessibilityNodeFindNodeById003
 * @tc.desc: Test FindNodeById returns nullptr for non-existent ID
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeFindNodeById003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. search for non-existent ID
     * @tc.expected: returns nullptr
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    node->SetNodeId(1);
    EXPECT_EQ(node->FindNodeById(999), nullptr);
}

// ==================== VirtualAccessibilityNode TraverseChildren ====================

/**
 * @tc.name: VirtualAccessibilityNodeTraverseChildren001
 * @tc.desc: Test TraverseChildren visits all children depth-first
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeTraverseChildren001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create 2-level tree, traverse and collect node IDs
     * @tc.expected: all child and grandchild IDs are visited
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    parent->SetNodeId(1);
    auto c1 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    c1->SetNodeId(10);
    auto c2 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    c2->SetNodeId(20);
    auto gc1 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    gc1->SetNodeId(100);
    c1->AddChild(gc1);
    parent->AddChild(c1);
    parent->AddChild(c2);

    std::vector<int32_t> visitedIds;
    parent->TraverseChildren([&visitedIds](const RefPtr<VirtualAccessibilityNode>& node) {
        visitedIds.push_back(node->GetNodeId());
    });
    ASSERT_EQ(visitedIds.size(), 3u);
    EXPECT_EQ(visitedIds[0], 10);
    EXPECT_EQ(visitedIds[1], 100);
    EXPECT_EQ(visitedIds[2], 20);
}

/**
 * @tc.name: VirtualAccessibilityNodeTraverseChildren002
 * @tc.desc: Test TraverseChildren with no children does nothing
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeTraverseChildren002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. traverse node with no children
     * @tc.expected: visitor never called
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    int callCount = 0;
    node->TraverseChildren([&callCount](const RefPtr<VirtualAccessibilityNode>&) {
        callCount++;
    });
    EXPECT_EQ(callCount, 0);
}

// ==================== VirtualAccessibilityNode default values ====================

/**
 * @tc.name: VirtualAccessibilityNodeDefaultValues001
 * @tc.desc: Test default values of VirtualAccessibilityNode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeDefaultValues001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create default VirtualAccessibilityNode, check defaults
     * @tc.expected: nodeId is INVALID_NODE_ID (-1), no children, no parent, not focused
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetNodeId(), VirtualAccessibilityNode::INVALID_NODE_ID);
    EXPECT_FALSE(node->HasChildren());
    EXPECT_EQ(node->GetChildCount(), 0u);
    EXPECT_EQ(node->GetParent(), nullptr);
    EXPECT_FALSE(node->GetAccessibilityFocused());
}

// ==================== VirtualAccessibilityNode SetAccessibilityFocused ====================

/**
 * @tc.name: VirtualAccessibilityNodeSetFocused001
 * @tc.desc: Test SetAccessibilityFocused/GetAccessibilityFocused round trip
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeSetFocused001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set focused true, then false
     * @tc.expected: getter matches setter each time
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    node->SetAccessibilityFocused(true);
    EXPECT_TRUE(node->GetAccessibilityFocused());
    node->SetAccessibilityFocused(false);
    EXPECT_FALSE(node->GetAccessibilityFocused());
}

// ==================== VirtualAccessibilityNode AddChild null check ====================

/**
 * @tc.name: VirtualAccessibilityNodeAddChild001
 * @tc.desc: Test AddChild with null does not crash
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualAccessibilityNodeAddChild001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call AddChild with nullptr
     * @tc.expected: no crash, child count remains 0
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    parent->AddChild(nullptr);
    EXPECT_EQ(parent->GetChildCount(), 0u);
}

// ==================== VirtualNodeContainerIdManager AllocateContainerId pool exhaustion ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerAllocateContainerId004
 * @tc.desc: Test AllocateContainerId returns INVALID_CONTAINER_ID (0) when pool exhausted
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerAllocateContainerId004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. allocate 255 IDs to exhaust the pool, then try one more
     * @tc.expected: the 256th allocation returns 0
     */
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    std::vector<RefPtr<FrameNode>> nodes;
    for (int32_t i = 0; i < 255; ++i) {
        auto node = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
        ASSERT_NE(node, nullptr);
        nodes.push_back(node);
        auto id = mgr.AllocateContainerId(node);
        ASSERT_NE(id, 0);
    }
    EXPECT_EQ(mgr.GetContainerCount(), 255u);
    EXPECT_EQ(mgr.GetAvailableIdCount(), 0u);

    auto extraNode = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(extraNode, nullptr);
    auto extraId = mgr.AllocateContainerId(extraNode);
    EXPECT_EQ(extraId, 0);
}

// ==================== VirtualNodeContainerIdManager GetContainerNode out-of-range ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerGetContainerNode002
 * @tc.desc: Test GetContainerNode with out-of-range ID returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerGetContainerNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetContainerNode with ID > MAX_CONTAINER_ID
     * @tc.expected: returns nullptr without checking the map
     */
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    EXPECT_EQ(mgr.GetContainerNode(static_cast<uint8_t>(0)), nullptr);
}

// ================= VirtualNodeContainerIdManager ReleaseContainerId(uint8_t) valid but unallocated =================

/**
 * @tc.name: VirtualNodeContainerIdManagerReleaseContainerId002
 * @tc.desc: Test ReleaseContainerId(uint8_t) with valid range ID but unallocated returns silently
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerReleaseContainerId002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. release ID 100 (within range but not allocated)
     * @tc.expected: no crash, count remains 0
     */
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    mgr.ReleaseContainerId(static_cast<uint8_t>(100));
    EXPECT_EQ(mgr.GetContainerCount(), 0u);
}

// ==================== VirtualNodeContainerIdManager release after weak ptr cleared ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerReleaseContainerId003
 * @tc.desc: Test ReleaseContainerId(uint8_t) when WeakPtr to FrameNode has been cleared
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerReleaseContainerId003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. allocate, drop the FrameNode reference, release by ID
     * @tc.expected: nodeToContainerMap_ entry remains but container is released without crash
     */
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    uint8_t allocatedId = 0;
    int64_t nodeAccessibilityId = 0;
    {
        auto node = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
        ASSERT_NE(node, nullptr);
        nodeAccessibilityId = node->GetAccessibilityId();
        allocatedId = mgr.AllocateContainerId(node);
        EXPECT_NE(allocatedId, 0);
        // node goes out of scope here, WeakPtr inside manager becomes dangling
    }
    EXPECT_EQ(mgr.GetContainerCount(), 1u);
    // Should not crash even though WeakPtr cannot be upgraded
    mgr.ReleaseContainerId(allocatedId);
    EXPECT_EQ(mgr.GetContainerCount(), 0u);
    (void)nodeAccessibilityId;
}

// ================= VirtualNodeContainerIdManager IsVirtualNodeContainerId with negative componentId =================

/**
 * @tc.name: VirtualNodeContainerIdManagerIsVirtualNodeContainerId003
 * @tc.desc: Test IsVirtualNodeContainerId with parent ID (container bits cleared)
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestThree, VirtualNodeContainerIdManagerIsVirtualNodeContainerId003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a parent ID by clearing container bits, verify false
     * @tc.expected: parent ID is not a virtual node container ID
     */
    uint8_t containerId = 7;
    int64_t componentId = 42;
    auto encoded = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, componentId);
    auto parentId = VirtualNodeContainerIdManager::GetParentAccessibilityId(encoded);
    EXPECT_FALSE(VirtualNodeContainerIdManager::IsVirtualNodeContainerId(parentId));
}

} // namespace OHOS::Ace::NG
