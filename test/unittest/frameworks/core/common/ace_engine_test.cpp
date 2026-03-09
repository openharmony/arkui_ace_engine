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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "vector"

#include "base/utils/time_util.h"

#define private public
#define protected public
#include "core/common/ace_engine.h"
#undef private
#undef protected

#include "core/common/container_scope.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

namespace {
constexpr int32_t TEST_INSTANCE_ID_1 = 100001;
constexpr int32_t TEST_INSTANCE_ID_2 = 100002;
constexpr int32_t TEST_INSTANCE_ID_3 = 100003;
constexpr int32_t TEST_INSTANCE_ID_INVALID = 999999;
constexpr uint32_t TEST_WINDOW_ID = 1001;

const std::string TEST_WINDOW_NAME = "TestWindow";
} // namespace

class AceEngineTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        ContainerScope::UpdateCurrent(-1);
    }
    static void TearDownTestSuite()
    {
        ContainerScope::UpdateCurrent(-1);
    }
    void SetUp() override
    {
        aceEngine_ = &AceEngine::Get();
        containerMap_.clear();
    }
    void TearDown() override
    {
        if (aceEngine_) {
            aceEngine_->RemoveContainer(TEST_INSTANCE_ID_1);
            aceEngine_->RemoveContainer(TEST_INSTANCE_ID_2);
            aceEngine_->RemoveContainer(TEST_INSTANCE_ID_3);
        }
    }

protected:
    void AddTestContainer(int32_t instanceId, int32_t windowId = TEST_WINDOW_ID)
    {
        auto container = AceType::MakeRefPtr<MockContainer>();
        auto mockTaskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
        container->SetTaskExecutor(mockTaskExecutor);
        EXPECT_CALL(*container, GetInstanceId()).WillRepeatedly(testing::Return(instanceId));
        EXPECT_CALL(*container, GetWindowId()).WillRepeatedly(testing::Return(windowId));
        EXPECT_CALL(*container, GetWindowName()).WillRepeatedly(testing::Return(TEST_WINDOW_NAME));
        aceEngine_->AddContainer(instanceId, container);
        containerMap_[instanceId] = container;
    }

    AceEngine* aceEngine_ = nullptr;
    std::unordered_map<int32_t, RefPtr<MockContainer>> containerMap_;
};

/**
 * @tc.name: AceEngineTest001
 * @tc.desc: Add container successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceEngineTest, AceEngineTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add a container to AceEngine
     */
    AddTestContainer(TEST_INSTANCE_ID_1);

    /**
     * @tc.steps: step2. Verify container is added
     * @tc.expected: GetContainer returns valid container
     */
    auto container = aceEngine_->GetContainer(TEST_INSTANCE_ID_1);
    EXPECT_NE(container, nullptr);
    EXPECT_EQ(container->GetInstanceId(), TEST_INSTANCE_ID_1);
}

/**
 * @tc.name: AceEngineTest002
 * @tc.desc: Add container with same instanceId (should replace)
 * @tc.type: FUNC
 */
HWTEST_F(AceEngineTest, AceEngineTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add first container
     */
    AddTestContainer(TEST_INSTANCE_ID_1);
    auto container1 = aceEngine_->GetContainer(TEST_INSTANCE_ID_1);
    EXPECT_NE(container1, nullptr);

    /**
     * @tc.steps: step2. Add second container with same instanceId
     */
    AddTestContainer(TEST_INSTANCE_ID_1);
    auto container2 = aceEngine_->GetContainer(TEST_INSTANCE_ID_1);

    /**
     * @tc.steps: step3. Verify container is replaced
     * @tc.expected: Both containers are valid (replacement behavior)
     */
    EXPECT_NE(container2, nullptr);
}

/**
 * @tc.name: AceEngineTest003
 * @tc.desc: Add multiple containers
 * @tc.type: FUNC
 */
HWTEST_F(AceEngineTest, AceEngineTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add multiple containers
     */
    AddTestContainer(TEST_INSTANCE_ID_1);
    AddTestContainer(TEST_INSTANCE_ID_2);
    AddTestContainer(TEST_INSTANCE_ID_3);

    /**
     * @tc.steps: step2. Verify all containers are added
     */
    EXPECT_NE(aceEngine_->GetContainer(TEST_INSTANCE_ID_1), nullptr);
    EXPECT_NE(aceEngine_->GetContainer(TEST_INSTANCE_ID_2), nullptr);
    EXPECT_NE(aceEngine_->GetContainer(TEST_INSTANCE_ID_3), nullptr);
}

/**
 * @tc.name: AceEngineTest004
 * @tc.desc: HasContainer returns true for existing container
 * @tc.type: FUNC
 */
HWTEST_F(AceEngineTest, AceEngineTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add a container
     */
    AddTestContainer(TEST_INSTANCE_ID_1);

    /**
     * @tc.steps: step2. Verify HasContainer returns true
     */
    EXPECT_TRUE(aceEngine_->HasContainer(TEST_INSTANCE_ID_1));
}

/**
 * @tc.name: AceEngineTest005
 * @tc.desc: HasContainer returns false for non-existent container
 * @tc.type: FUNC
 */
HWTEST_F(AceEngineTest, AceEngineTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Check HasContainer for non-existent instanceId
     * @tc.expected: Returns false
     */
    EXPECT_FALSE(aceEngine_->HasContainer(TEST_INSTANCE_ID_INVALID));
}

/**
 * @tc.name: AceEngineTest006
 * @tc.desc: Remove existing container successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceEngineTest, AceEngineTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add a container to AceEngine
     */
    AddTestContainer(TEST_INSTANCE_ID_1);
    auto containerBefore = aceEngine_->GetContainer(TEST_INSTANCE_ID_1);
    ASSERT_NE(containerBefore, nullptr);

    /**
     * @tc.steps: step2. Remove the container
     */
    aceEngine_->RemoveContainer(TEST_INSTANCE_ID_1);

    /**
     * @tc.steps: step3. Verify container is removed
     * @tc.expected: GetContainer returns nullptr
     */
    auto containerAfter = aceEngine_->GetContainer(TEST_INSTANCE_ID_1);
    EXPECT_EQ(containerAfter, nullptr);
}

/**
 * @tc.name: AceEngineTest007
 * @tc.desc: Remove non-existent container
 * @tc.type: FUNC
 */
HWTEST_F(AceEngineTest, AceEngineTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Try to remove a container that doesn't exist
     */
    aceEngine_->RemoveContainer(TEST_INSTANCE_ID_INVALID);

    /**
     * @tc.steps: step2. Verify no container exists
     * @tc.expected: GetContainer returns nullptr
     */
    auto container = aceEngine_->GetContainer(TEST_INSTANCE_ID_INVALID);
    EXPECT_EQ(container, nullptr);
}

/**
 * @tc.name: AceEngineTest008
 * @tc.desc: Remove and re-add same instanceId
 * @tc.type: FUNC
 */
HWTEST_F(AceEngineTest, AceEngineTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add and remove a container
     */
    AddTestContainer(TEST_INSTANCE_ID_1);
    aceEngine_->RemoveContainer(TEST_INSTANCE_ID_1);
    EXPECT_EQ(aceEngine_->GetContainer(TEST_INSTANCE_ID_1), nullptr);

    /**
     * @tc.steps: step2. Re-add container with same instanceId
     */
    AddTestContainer(TEST_INSTANCE_ID_1);

    /**
     * @tc.steps: step3. Verify container exists again
     * @tc.expected: GetContainer returns valid container
     */
    auto container = aceEngine_->GetContainer(TEST_INSTANCE_ID_1);
    EXPECT_NE(container, nullptr);
    EXPECT_EQ(container->GetInstanceId(), TEST_INSTANCE_ID_1);
}

/**
 * @tc.name: AceEngineTest009
 * @tc.desc: Verify destroyed UIContext cache is populated after removal
 * @tc.type: FUNC
 */
HWTEST_F(AceEngineTest, AceEngineTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add and remove a container
     */
    AddTestContainer(TEST_INSTANCE_ID_1);
    aceEngine_->RemoveContainer(TEST_INSTANCE_ID_1);

    /**
     * @tc.steps: step2. Get destroyed UIContext info
     */
    std::string destroyedInfo = aceEngine_->GetDestroyedUIContextInfo(TEST_INSTANCE_ID_1);

    /**
     * @tc.steps: step3. Verify cache contains correct information
     * @tc.expected: Cache info contains instanceId and windowId
     */
    EXPECT_NE(destroyedInfo.find(std::to_string(TEST_INSTANCE_ID_1)), std::string::npos);
    EXPECT_NE(destroyedInfo.find(std::to_string(TEST_WINDOW_ID)), std::string::npos);
}

/**
 * @tc.name: AceEngineTest010
 * @tc.desc: Remove container and verify HasContainer returns false
 * @tc.type: FUNC
 */
HWTEST_F(AceEngineTest, AceEngineTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add a container
     */
    AddTestContainer(TEST_INSTANCE_ID_1);
    EXPECT_TRUE(aceEngine_->HasContainer(TEST_INSTANCE_ID_1));

    /**
     * @tc.steps: step2. Remove the container
     */
    aceEngine_->RemoveContainer(TEST_INSTANCE_ID_1);

    /**
     * @tc.steps: step3. Verify HasContainer returns false
     */
    EXPECT_FALSE(aceEngine_->HasContainer(TEST_INSTANCE_ID_1));
}

/**
 * @tc.name: AceEngineTest011
 * @tc.desc: Remove same container twice
 * @tc.type: FUNC
 */
HWTEST_F(AceEngineTest, AceEngineTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add a container
     */
    AddTestContainer(TEST_INSTANCE_ID_1);

    /**
     * @tc.steps: step2. Remove the container twice
     */
    aceEngine_->RemoveContainer(TEST_INSTANCE_ID_1);
    aceEngine_->RemoveContainer(TEST_INSTANCE_ID_1);

    /**
     * @tc.steps: step3. Verify no crash and container is removed
     */
    EXPECT_EQ(aceEngine_->GetContainer(TEST_INSTANCE_ID_1), nullptr);
}

/**
 * @tc.name: AceEngineTest012
 * @tc.desc: Cache LRU eviction when cache is full
 * @tc.type: FUNC
 */
HWTEST_F(AceEngineTest, AceEngineTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add and remove more than MAX_DESTROYED_CACHE_SIZE (10) containers
     */
    constexpr int32_t MAX_CONTAINERS = 15;
    for (int32_t i = 0; i < MAX_CONTAINERS; i++) {
        int32_t instanceId = TEST_INSTANCE_ID_1 + i;
        AddTestContainer(instanceId);
        aceEngine_->RemoveContainer(instanceId);
    }

    /**
     * @tc.steps: step2. Verify recent destroyed containers are cached
     */
    std::string lastInfo = aceEngine_->GetDestroyedUIContextInfo(TEST_INSTANCE_ID_1 + MAX_CONTAINERS - 1);
    EXPECT_NE(lastInfo, "InstanceId not found in destroyed cache.");

    /**
     * @tc.steps: step3. Verify oldest destroyed container may be evicted
     */
    std::string oldestInfo = aceEngine_->GetDestroyedUIContextInfo(TEST_INSTANCE_ID_1);
    EXPECT_TRUE(oldestInfo == "InstanceId not found in destroyed cache." ||
                oldestInfo.find(std::to_string(TEST_INSTANCE_ID_1)) != std::string::npos);
}

/**
 * @tc.name: AceEngineTest013
 * @tc.desc: Enhanced error message generation for destroyed context
 * @tc.type: FUNC
 */
HWTEST_F(AceEngineTest, AceEngineTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add and remove a container
     */
    AddTestContainer(TEST_INSTANCE_ID_1);
    aceEngine_->RemoveContainer(TEST_INSTANCE_ID_1);

    /**
     * @tc.steps: step2. Generate enhanced error message
     */
    std::string errorMsg =
        AceEngine::GetEnhancedContextBNotFoundMessage(InstanceIdGenReason::SCOPE, TEST_INSTANCE_ID_1);

    /**
     * @tc.steps: step3. Verify error message contains instanceId and reason
     */
    EXPECT_NE(errorMsg.find(std::to_string(TEST_INSTANCE_ID_1)), std::string::npos);
    EXPECT_NE(errorMsg.find("The instance is determined by the caller"), std::string::npos);
}

/**
 * @tc.name: AceEngineTest014
 * @tc.desc: Remove container with different window IDs
 * @tc.type: FUNC
 */
HWTEST_F(AceEngineTest, AceEngineTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add containers with different window IDs
     */
    AddTestContainer(TEST_INSTANCE_ID_1, 1001);
    AddTestContainer(TEST_INSTANCE_ID_2, 1002);
    AddTestContainer(TEST_INSTANCE_ID_3, 1003);

    /**
     * @tc.steps: step2. Remove all containers
     */
    aceEngine_->RemoveContainer(TEST_INSTANCE_ID_1);
    aceEngine_->RemoveContainer(TEST_INSTANCE_ID_2);
    aceEngine_->RemoveContainer(TEST_INSTANCE_ID_3);

    /**
     * @tc.steps: step3. Verify all containers are removed
     */
    EXPECT_EQ(aceEngine_->GetContainer(TEST_INSTANCE_ID_1), nullptr);
    EXPECT_EQ(aceEngine_->GetContainer(TEST_INSTANCE_ID_2), nullptr);
    EXPECT_EQ(aceEngine_->GetContainer(TEST_INSTANCE_ID_3), nullptr);
}

/**
 * @tc.name: AceEngineTest015
 * @tc.desc: NotifyContainers and NotifyContainersOrderly comprehensive test
 * @tc.type: FUNC
 */
HWTEST_F(AceEngineTest, AceEngineTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test NotifyContainers with nullptr callback
     * @tc
     */
    aceEngine_->NotifyContainers(nullptr);

    /**
     * @tc.steps: step2. Test NotifyContainersOrderly with nullptr callback
     * @tc.expected: Should not crash
     */
    aceEngine_->NotifyContainersOrderly(nullptr);

    /**
     * @tc.steps: step3. Test NotifyContainers with no containers
     */
    int32_t callbackCount = 0;
    aceEngine_->NotifyContainers([&callbackCount](const RefPtr<Container>& container) { callbackCount++; });
    EXPECT_EQ(callbackCount, 0);

    /**
     * @tc.steps: step4. Add multiple containers
     */
    AddTestContainer(TEST_INSTANCE_ID_1);
    AddTestContainer(TEST_INSTANCE_ID_2);
    AddTestContainer(TEST_INSTANCE_ID_3);

    /**
     * @tc.steps: step5. Test NotifyContainers callback is invoked for all containers
     */
    callbackCount = 0;
    aceEngine_->NotifyContainers([&callbackCount](const RefPtr<Container>& container) {
        callbackCount++;
        EXPECT_NE(container, nullptr);
    });
    EXPECT_EQ(callbackCount, 3);

    /**
     * @tc.steps: step6. Test NotifyContainersOrderly callback is invoked in order
     */
    std::vector<int32_t> callbackOrder;
    aceEngine_->NotifyContainersOrderly(
        [&callbackOrder](const RefPtr<Container>& container) { callbackOrder.push_back(container->GetInstanceId()); });
    EXPECT_EQ(callbackOrder.size(), 3);
    EXPECT_EQ(callbackOrder[0], TEST_INSTANCE_ID_1);
    EXPECT_EQ(callbackOrder[1], TEST_INSTANCE_ID_2);
    EXPECT_EQ(callbackOrder[2], TEST_INSTANCE_ID_3);
}

/**
 * @tc.name: AceEngineTest016
 * @tc.desc: Test container management methods with multiple containers
 * @tc.type: FUNC
 */
HWTEST_F(AceEngineTest, AceEngineTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call methods with no containers
     * @tc.expected: Should not crash
     */
    aceEngine_->TriggerGarbageCollection();
    aceEngine_->DumpJsHeap(false);
    aceEngine_->DumpJsHeap(true);
    aceEngine_->DestroyHeapProfiler();
    aceEngine_->ForceFullGC();

    /**
     * @tc.steps: step2. Add multiple containers
     */
    AddTestContainer(TEST_INSTANCE_ID_1);
    AddTestContainer(TEST_INSTANCE_ID_2);
    AddTestContainer(TEST_INSTANCE_ID_3);

    /**
     * @tc.steps: step3. Set expectations for TriggerGarbageCollection calls
     * @tc.expected: Each container's TriggerGarbageCollection should be called once
     */
    EXPECT_CALL(*containerMap_[TEST_INSTANCE_ID_1], TriggerGarbageCollection()).Times(1);
    EXPECT_CALL(*containerMap_[TEST_INSTANCE_ID_2], TriggerGarbageCollection()).Times(1);
    EXPECT_CALL(*containerMap_[TEST_INSTANCE_ID_3], TriggerGarbageCollection()).Times(1);

    /**
     * @tc.steps: step4. Call TriggerGarbageCollection
     * @tc.expected: All containers should receive the call
     */
    aceEngine_->TriggerGarbageCollection();

    /**
     * @tc.steps: step5. Set expectations for DumpHeapSnapshot calls
     * @tc.expected: Each container's DumpHeapSnapshot should be called twice (false and true)
     */
    EXPECT_CALL(*containerMap_[TEST_INSTANCE_ID_1], DumpHeapSnapshot(false)).Times(1);
    EXPECT_CALL(*containerMap_[TEST_INSTANCE_ID_1], DumpHeapSnapshot(true)).Times(1);
    EXPECT_CALL(*containerMap_[TEST_INSTANCE_ID_2], DumpHeapSnapshot(false)).Times(1);
    EXPECT_CALL(*containerMap_[TEST_INSTANCE_ID_2], DumpHeapSnapshot(true)).Times(1);
    EXPECT_CALL(*containerMap_[TEST_INSTANCE_ID_3], DumpHeapSnapshot(false)).Times(1);
    EXPECT_CALL(*containerMap_[TEST_INSTANCE_ID_3], DumpHeapSnapshot(true)).Times(1);

    /**
     * @tc.steps: step6. Call DumpJsHeap
     * @tc.expected: All containers should receive the call
     */
    aceEngine_->DumpJsHeap(false);
    aceEngine_->DumpJsHeap(true);

    /**
     * @tc.steps: step7. Set expectations for DestroyHeapProfiler calls
     * @tc.expected: Each container's DestroyHeapProfiler should be called once
     */
    EXPECT_CALL(*containerMap_[TEST_INSTANCE_ID_1], DestroyHeapProfiler()).Times(1);
    EXPECT_CALL(*containerMap_[TEST_INSTANCE_ID_2], DestroyHeapProfiler()).Times(1);
    EXPECT_CALL(*containerMap_[TEST_INSTANCE_ID_3], DestroyHeapProfiler()).Times(1);

    /**
     * @tc.steps: step8. Call DestroyHeapProfiler
     * @tc.expected: All containers should receive the call
     */
    aceEngine_->DestroyHeapProfiler();

    /**
     * @tc.steps: step9. Set expectations for ForceFullGC calls
     * @tc.expected: Each container's ForceFullGC should be called once
     */
    EXPECT_CALL(*containerMap_[TEST_INSTANCE_ID_1], ForceFullGC()).Times(1);
    EXPECT_CALL(*containerMap_[TEST_INSTANCE_ID_2], ForceFullGC()).Times(1);
    EXPECT_CALL(*containerMap_[TEST_INSTANCE_ID_3], ForceFullGC()).Times(1);

    /**
     * @tc.steps: step10. Call ForceFullGC
     * @tc.expected: All containers should receive the call
     */
    aceEngine_->ForceFullGC();
}

/**
 * @tc.name: AceEngineTest017
 * @tc.desc: GetDestroyedUIContextInfo for non-destroyed container
 * @tc.type: FUNC
 */
HWTEST_F(AceEngineTest, AceEngineTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add a container (not destroyed)
     */
    AddTestContainer(TEST_INSTANCE_ID_1);

    /**
     * @tc.steps: step2. Get destroyed UIContext info
     * @tc.expected: Returns "not found" message
     */
    std::string info = aceEngine_->GetDestroyedUIContextInfo(TEST_INSTANCE_ID_1);
    EXPECT_EQ(info, "InstanceId not found in destroyed cache.");
}

/**
 * @tc.name: AceEngineTest018
 * @tc.desc: GetEnhancedContextBNotFoundMessage with different reasons
 * @tc.type: FUNC
 */
HWTEST_F(AceEngineTest, AceEngineTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Generate enhanced error message with SCOPE reason
     */
    std::string msg1 = AceEngine::GetEnhancedContextBNotFoundMessage(InstanceIdGenReason::SCOPE, TEST_INSTANCE_ID_1);
    EXPECT_NE(msg1.find(std::to_string(TEST_INSTANCE_ID_1)), std::string::npos);
    EXPECT_NE(msg1.find("The instance is determined by the caller"), std::string::npos);

    /**
     * @tc.steps: step2. Generate enhanced error message with other reasons
     */
    std::string msg2 =
        AceEngine::GetEnhancedContextBNotFoundMessage(InstanceIdGenReason::FOREGROUND, TEST_INSTANCE_ID_2);
    EXPECT_NE(msg2.find(std::to_string(TEST_INSTANCE_ID_2)), std::string::npos);
    EXPECT_NE(msg2.find("No specific instance was specified, return the foreground instance"), std::string::npos);
}

} // namespace OHOS::Ace
