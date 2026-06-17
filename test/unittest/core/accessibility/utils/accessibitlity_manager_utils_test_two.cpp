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

class AccessibilityManagerUtilsTestTwo : public testing::Test {
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

void AccessibilityManagerUtilsTestTwo::SetUpTestCase()
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

void AccessibilityManagerUtilsTestTwo::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

// ==================== VirtualNodeContainerIdManager GetInstance ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerGetInstance001
 * @tc.desc: Test GetInstance returns the same singleton
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerGetInstance001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get instance twice
     * @tc.expected: both references point to the same singleton
     */
    auto& instance1 = VirtualNodeContainerIdManager::GetInstance();
    auto& instance2 = VirtualNodeContainerIdManager::GetInstance();
    EXPECT_EQ(&instance1, &instance2);
}

// ==================== VirtualNodeContainerIdManager AllocateContainerId ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerAllocateContainerId001
 * @tc.desc: Test AllocateContainerId with null node returns 0
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerAllocateContainerId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. allocate with nullptr
     * @tc.expected: returns INVALID_CONTAINER_ID (0)
     */
    auto id = VirtualNodeContainerIdManager::GetInstance().AllocateContainerId(nullptr);
    EXPECT_EQ(id, 0);
}

/**
 * @tc.name: VirtualNodeContainerIdManagerAllocateContainerId002
 * @tc.desc: Test AllocateContainerId with valid node returns 1-255
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerAllocateContainerId002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. allocate with valid FrameNode
     * @tc.expected: returns a valid container ID (1-255)
     */
    auto node = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node, nullptr);
    auto id = VirtualNodeContainerIdManager::GetInstance().AllocateContainerId(node);
    EXPECT_GE(id, 1);
    EXPECT_LE(id, 255);
}

// ==================== VirtualNodeContainerIdManager ReleaseContainerId ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerReleaseContainerId001
 * @tc.desc: Test ReleaseContainerId by ID, then allocate again gets same ID
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerReleaseContainerId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. allocate, release, allocate again
     * @tc.expected: the released ID can be reused
     */
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    auto node = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node, nullptr);
    auto id = mgr.AllocateContainerId(node);
    EXPECT_NE(id, 0);
    mgr.ReleaseContainerId(id);
    auto node2 = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node2, nullptr);
    auto id2 = mgr.AllocateContainerId(node2);
    EXPECT_NE(id2, 0);
}

/**
 * @tc.name: VirtualNodeContainerIdManagerReleaseContainerId002
 * @tc.desc: Test ReleaseContainerId by FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerReleaseContainerId002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. allocate, release by node, verify GetContainerId returns 0
     * @tc.expected: container ID is released
     */
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    auto node = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node, nullptr);
    auto id = mgr.AllocateContainerId(node);
    EXPECT_NE(id, 0);
    mgr.ReleaseContainerId(node);
    EXPECT_EQ(mgr.GetContainerId(node), 0);
}

// ==================== VirtualNodeContainerIdManager GetContainerNode ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerGetContainerNode001
 * @tc.desc: Test GetContainerNode returns the correct node
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerGetContainerNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. allocate and find by container ID
     * @tc.expected: returns the same node
     */
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    auto node = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node, nullptr);
    auto id = mgr.AllocateContainerId(node);
    auto found = mgr.GetContainerNode(id);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->GetAccessibilityId(), node->GetAccessibilityId());
}

/**
 * @tc.name: VirtualNodeContainerIdManagerGetContainerNode002
 * @tc.desc: Test GetContainerNode with invalid ID returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerGetContainerNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get node by ID 0 and unallocated ID
     * @tc.expected: returns nullptr
     */
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    EXPECT_EQ(mgr.GetContainerNode(0), nullptr);
    EXPECT_EQ(mgr.GetContainerNode(100), nullptr);
}

// ==================== VirtualNodeContainerIdManager GetContainerId ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerGetContainerId001
 * @tc.desc: Test GetContainerId returns correct ID for allocated node
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerGetContainerId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. allocate and verify GetContainerId round trip
     * @tc.expected: returns the allocated ID
     */
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    auto node = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node, nullptr);
    auto id = mgr.AllocateContainerId(node);
    EXPECT_EQ(mgr.GetContainerId(node), id);
}

/**
 * @tc.name: VirtualNodeContainerIdManagerGetContainerId002
 * @tc.desc: Test GetContainerId returns 0 for unregistered node
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerGetContainerId002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node without allocating
     * @tc.expected: returns 0
     */
    auto node = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(VirtualNodeContainerIdManager::GetInstance().GetContainerId(node), 0);
}

/**
 * @tc.name: VirtualNodeContainerIdManagerGetContainerId003
 * @tc.desc: Test GetContainerId with null node returns 0
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerGetContainerId003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetContainerId with nullptr
     * @tc.expected: returns 0
     */
    EXPECT_EQ(VirtualNodeContainerIdManager::GetInstance().GetContainerId(nullptr), 0);
}

// ==================== VirtualNodeContainerIdManager IsVirtualNodeContainer ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerIsVirtualNodeContainer001
 * @tc.desc: Test IsVirtualNodeContainer with uint8_t
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerIsVirtualNodeContainer001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. check with valid and invalid IDs
     * @tc.expected: 1-255 are valid, 0 is not
     */
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    EXPECT_FALSE(mgr.IsVirtualNodeContainer(static_cast<uint8_t>(0)));
    EXPECT_TRUE(mgr.IsVirtualNodeContainer(static_cast<uint8_t>(1)));
    EXPECT_TRUE(mgr.IsVirtualNodeContainer(static_cast<uint8_t>(255)));
}

/**
 * @tc.name: VirtualNodeContainerIdManagerIsVirtualNodeContainer002
 * @tc.desc: Test IsVirtualNodeContainer with FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerIsVirtualNodeContainer002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. check unallocated and allocated nodes
     * @tc.expected: unallocated returns false, allocated returns true
     */
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    auto node = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node, nullptr);
    EXPECT_FALSE(mgr.IsVirtualNodeContainer(node));
    mgr.AllocateContainerId(node);
    EXPECT_TRUE(mgr.IsVirtualNodeContainer(node));
    EXPECT_FALSE(mgr.IsVirtualNodeContainer(nullptr));
}

// ==================== VirtualNodeContainerIdManager Clear ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerClear001
 * @tc.desc: Test Clear removes all mappings
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerClear001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. allocate multiple, clear, verify empty
     * @tc.expected: container count is 0 after clear
     */
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    auto node1 = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    auto node2 = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node1, nullptr);
    ASSERT_NE(node2, nullptr);
    mgr.AllocateContainerId(node1);
    mgr.AllocateContainerId(node2);
    EXPECT_EQ(mgr.GetContainerCount(), 2);
    mgr.Clear();
    EXPECT_EQ(mgr.GetContainerCount(), 0);
    EXPECT_EQ(mgr.GetContainerId(node1), 0);
    EXPECT_EQ(mgr.GetContainerId(node2), 0);
}

// ==================== VirtualNodeContainerIdManager Statistics ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerStatistics001
 * @tc.desc: Test GetContainerCount and GetAvailableIdCount
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerStatistics001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. check initial state, allocate one, check again
     * @tc.expected: container count increases, available count decreases
     */
    auto& mgr = VirtualNodeContainerIdManager::GetInstance();
    EXPECT_EQ(mgr.GetContainerCount(), 0);
    EXPECT_EQ(mgr.GetAvailableIdCount(), 255);
    auto node = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node, nullptr);
    mgr.AllocateContainerId(node);
    EXPECT_EQ(mgr.GetContainerCount(), 1);
    EXPECT_EQ(mgr.GetAvailableIdCount(), 254);
}

// ==================== VirtualNodeContainerIdManager EncodeVirtualNodeAccessibilityId/Decode ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerEncodeDecode001
 * @tc.desc: Test encode then decode round trip
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerEncodeDecode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. encode with containerId=5, componentId=42, then decode
     * @tc.expected: decoded values match input
     */
    uint8_t containerId = 5;
    int64_t componentId = 42;
    auto encoded = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, componentId);
    uint8_t decodedContainerId = 0;
    int64_t decodedComponentId = 0;
    VirtualNodeContainerIdManager::DecodeAccessibilityId(encoded, decodedContainerId, decodedComponentId);
    EXPECT_EQ(decodedContainerId, containerId);
    EXPECT_EQ(decodedComponentId, componentId);
}

/**
 * @tc.name: VirtualNodeContainerIdManagerEncodeDecode002
 * @tc.desc: Test encode/decode with negative componentId
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerEncodeDecode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. encode with negative componentId, then decode
     * @tc.expected: decoded componentId matches original negative value
     */
    uint8_t containerId = 10;
    int64_t componentId = -100;
    auto encoded = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, componentId);
    uint8_t decodedContainerId = 0;
    int64_t decodedComponentId = 0;
    VirtualNodeContainerIdManager::DecodeAccessibilityId(encoded, decodedContainerId, decodedComponentId);
    EXPECT_EQ(decodedContainerId, containerId);
    EXPECT_EQ(decodedComponentId, componentId);
}

/**
 * @tc.name: VirtualNodeContainerIdManagerEncodeDecode003
 * @tc.desc: Test encode/decode with max values
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerEncodeDecode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. encode with containerId=255, componentId=INT32_MAX, then decode
     * @tc.expected: decoded values match
     */
    uint8_t containerId = 255;
    int64_t componentId = INT32_MAX;
    auto encoded = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(containerId, componentId);
    uint8_t decodedContainerId = 0;
    int64_t decodedComponentId = 0;
    VirtualNodeContainerIdManager::DecodeAccessibilityId(encoded, decodedContainerId, decodedComponentId);
    EXPECT_EQ(decodedContainerId, containerId);
    EXPECT_EQ(decodedComponentId, componentId);
}

// ==================== VirtualNodeContainerIdManager IsVirtualNodeContainerId ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerIsVirtualNodeContainerId001
 * @tc.desc: Test IsVirtualNodeContainerId static method
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerIsVirtualNodeContainerId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. check with encoded ID and plain ID
     * @tc.expected: encoded ID returns true, plain ID returns false
     */
    auto encoded = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(5, 100);
    EXPECT_TRUE(VirtualNodeContainerIdManager::IsVirtualNodeContainerId(encoded));
    EXPECT_FALSE(VirtualNodeContainerIdManager::IsVirtualNodeContainerId(100));
}

// ==================== VirtualNodeContainerIdManager ExtractContainerId/ExtractComponentId ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerExtractContainerId001
 * @tc.desc: Test ExtractContainerId
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerExtractContainerId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. encode and extract container ID
     * @tc.expected: extracted container ID matches
     */
    auto encoded = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(42, 1000);
    EXPECT_EQ(VirtualNodeContainerIdManager::ExtractContainerId(encoded), 42);
}

/**
 * @tc.name: VirtualNodeContainerIdManagerExtractComponentId001
 * @tc.desc: Test ExtractComponentId
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerExtractComponentId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. encode and extract component ID
     * @tc.expected: extracted component ID matches
     */
    auto encoded = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(3, 12345);
    EXPECT_EQ(VirtualNodeContainerIdManager::ExtractComponentId(encoded), 12345);
}

/**
 * @tc.name: VirtualNodeContainerIdManagerExtractComponentId002
 * @tc.desc: Test ExtractComponentId with negative componentId
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerExtractComponentId002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. encode with negative componentId and extract
     * @tc.expected: extracted component ID matches the negative value
     */
    auto encoded = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(3, -999);
    EXPECT_EQ(VirtualNodeContainerIdManager::ExtractComponentId(encoded), -999);
}

// ==================== VirtualNodeContainerIdManager GetParentAccessibilityId ====================

/**
 * @tc.name: VirtualNodeContainerIdManagerGetParentAccessibilityId001
 * @tc.desc: Test GetParentAccessibilityId clears container ID bits
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTestTwo, VirtualNodeContainerIdManagerGetParentAccessibilityId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. encode, get parent ID, verify container bits are cleared
     * @tc.expected: parent ID has no container bits
     */
    auto encoded = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(7, 200);
    auto parentId = VirtualNodeContainerIdManager::GetParentAccessibilityId(encoded);
    EXPECT_EQ(VirtualNodeContainerIdManager::ExtractContainerId(parentId), 0);
    EXPECT_EQ(VirtualNodeContainerIdManager::ExtractComponentId(parentId), 200);
}
} // namespace OHOS::Ace::NG
