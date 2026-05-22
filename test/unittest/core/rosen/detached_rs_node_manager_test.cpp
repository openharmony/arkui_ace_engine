/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_ROSEN_ROSEN_RENDER_CONTEXT_TEST_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_ROSEN_ROSEN_RENDER_CONTEXT_TEST_H

#include <memory>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "render_service_client/core/ui/rs_canvas_node.h"
#include "render_service_client/core/ui/rs_ui_director.h"

#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/detached_rs_node_manager.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_window.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#undef private
#undef protected

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class DetachedRsNodeManagerTest : public testing::Test {
public:
    void SetUp() override
    {
        auto& mgr = DetachedRsNodeManager::GetInstance();
        std::lock_guard<std::mutex> lock(mgr.registeredMutex_);
        mgr.registeredInstances_.clear();
    }
    void TearDown() override
    {
        auto& mgr = DetachedRsNodeManager::GetInstance();
        std::lock_guard<std::mutex> lock(mgr.registeredMutex_);
        mgr.registeredInstances_.clear();
    }

    static void SetUpFullEnvironment(bool withWindow)
    {
        MockPipelineContext::SetUp();
        auto pipeline = MockPipelineContext::GetCurrent();
        if (withWindow) {
            pipeline->window_ = std::make_shared<NiceMock<MockWindow>>();
        }
        auto pipelineBase = AceType::DynamicCast<PipelineBase>(pipeline);
        MockContainer::SetUp(pipelineBase);
        auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
        MockContainer::Current()->SetTaskExecutor(taskExecutor);
    }

    static void TearDownFullEnvironment()
    {
        MockContainer::TearDown();
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: DetachedRsNodeManagerTest001
 * @tc.desc: Test the basic func.
 * @tc.type: FUNC
 */
HWTEST_F(DetachedRsNodeManagerTest, DetachedRsNodeManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get the member of the DetachedRsNodeManager.
     *@tc.expected: step1. The member of the DetachedRsNodeManager works right;
     */
    EXPECT_TRUE(DetachedRsNodeManager::GetInstance().rsUIContexts_.empty());
    EXPECT_NE(DetachedRsNodeManager::GetInstance().taskExecutor_, nullptr);

    auto rsUIDirector = OHOS::Rosen::RSUIDirector::Create(nullptr);
    auto rsContext = rsUIDirector->GetRSUIContext();
    EXPECT_NE(rsContext, nullptr);
    auto rsNode = Rosen::RSCanvasNode::Create(false, false, rsContext);

    DetachedRsNodeManager::GetInstance().rsUIContexts_.emplace(rsContext.get());
    EXPECT_FALSE(DetachedRsNodeManager::GetInstance().rsUIContexts_.empty());
    DetachedRsNodeManager::GetInstance().PostDestructorTask(rsNode);
    EXPECT_FALSE(DetachedRsNodeManager::GetInstance().rsUIContexts_.empty());
    DetachedRsNodeManager::GetInstance().RemoveRSUIContext(rsContext);
    EXPECT_TRUE(DetachedRsNodeManager::GetInstance().rsUIContexts_.empty());

    DetachedRsNodeManager::GetInstance().PostDestructorTask(rsNode);
    EXPECT_TRUE(DetachedRsNodeManager::GetInstance().rsUIContexts_.empty());

    rsContext->AttachFromUI();
    DetachedRsNodeManager::GetInstance().PostDestructorTask(rsNode);
    DetachedRsNodeManager::GetInstance().FlushImplicitTransaction(rsContext);
    EXPECT_TRUE(DetachedRsNodeManager::GetInstance().rsUIContexts_.empty());

    rsContext->DetachFromUI();
    DetachedRsNodeManager::GetInstance().PostDestructorTask(rsNode);
    EXPECT_TRUE(DetachedRsNodeManager::GetInstance().rsUIContexts_.empty());

    rsContext->rsTransactionHandler_ = nullptr;
    DetachedRsNodeManager::GetInstance().FlushImplicitTransaction(rsContext);
    EXPECT_TRUE(DetachedRsNodeManager::GetInstance().rsUIContexts_.empty());

    DetachedRsNodeManager::GetInstance().PostDestructorTask(nullptr);
    EXPECT_TRUE(DetachedRsNodeManager::GetInstance().rsUIContexts_.empty());
}

/**
 * @tc.name: PreFreezeFlushForAllContexts_NullCheckPaths
 * @tc.desc: Test all null-check branches of PreFreezeFlushForAllContexts: empty set, null container,
 *           null taskExecutor, null window, and normal path with ForceFlushVsync.
 * @tc.type: FUNC
 */
HWTEST_F(DetachedRsNodeManagerTest, PreFreezeFlushForAllContexts_NullCheckPaths, TestSize.Level1)
{
    auto& mgr = DetachedRsNodeManager::GetInstance();
    constexpr int32_t testId = 100;

    // Branch C1: registeredIds empty, loop should not execute
    DetachedRsNodeManager::PreFreezeFlushForAllContexts();
    EXPECT_TRUE(mgr.registeredInstances_.empty());

    // Branch C2: container==null (MockContainer::Current() returns nullptr when not set up)
    mgr.RegisterPreFreezeInstance(testId);
    ASSERT_EQ(mgr.registeredInstances_.size(), 1);

    // CHECK_NULL_VOID(container) skips this instanceId, no side effect
    DetachedRsNodeManager::PreFreezeFlushForAllContexts();
    EXPECT_EQ(mgr.registeredInstances_.size(), 1);

    mgr.UnregisterPreFreezeInstance(testId);
    EXPECT_TRUE(mgr.registeredInstances_.empty());

    // Branch C3: taskExecutor==null
    MockPipelineContext::SetUp();
    auto pipelineBase = AceType::DynamicCast<PipelineBase>(MockPipelineContext::GetCurrent());
    MockContainer::SetUp(pipelineBase);
    MockContainer::Current()->SetTaskExecutor(nullptr);

    mgr.RegisterPreFreezeInstance(testId);
    ASSERT_EQ(mgr.registeredInstances_.size(), 1);

    // CHECK_NULL_VOID(taskExecutor) skips this instanceId
    DetachedRsNodeManager::PreFreezeFlushForAllContexts();
    EXPECT_EQ(mgr.registeredInstances_.size(), 1);

    mgr.UnregisterPreFreezeInstance(testId);
    MockContainer::TearDown();
    MockPipelineContext::TearDown();

    // Branch D3: window==null
    SetUpFullEnvironment(false);
    ASSERT_EQ(MockPipelineContext::GetCurrent()->window_, nullptr);

    mgr.RegisterPreFreezeInstance(testId);
    ASSERT_EQ(mgr.registeredInstances_.size(), 1);

    // FlushInstance: CHECK_NULL_VOID(window) returns, no ForceFlushVsync call
    DetachedRsNodeManager::PreFreezeFlushForAllContexts();
    EXPECT_EQ(mgr.registeredInstances_.size(), 1);

    mgr.UnregisterPreFreezeInstance(testId);
    TearDownFullEnvironment();

    // Branch D4: normal path, ForceFlushVsync called once
    SetUpFullEnvironment(true);
    auto* mockWindow = static_cast<MockWindow*>(MockPipelineContext::GetCurrent()->window_.get());
    ASSERT_NE(mockWindow, nullptr);

    mgr.RegisterPreFreezeInstance(testId);
    ASSERT_EQ(mgr.registeredInstances_.size(), 1);

    EXPECT_CALL(*mockWindow, ForceFlushVsync(_, _)).Times(1);
    DetachedRsNodeManager::PreFreezeFlushForAllContexts();

    mgr.UnregisterPreFreezeInstance(testId);
    TearDownFullEnvironment();
    EXPECT_TRUE(mgr.registeredInstances_.empty());
}

/**
 * @tc.name: RegisterPreFreezeInstance_AllBranches
 * @tc.desc: Test all branches of RegisterPreFreezeInstance: duplicate id, multiple ids, externalClearRegistered_ true.
 * @tc.type: FUNC
 */
HWTEST_F(DetachedRsNodeManagerTest, RegisterPreFreezeInstance_AllBranches, TestSize.Level1)
{
    auto& mgr = DetachedRsNodeManager::GetInstance();
    constexpr int32_t id1 = 100;
    constexpr int32_t id2 = 200;
    constexpr int32_t id3 = 300;

    // Branch 1: Duplicate id should only have one entry
    mgr.RegisterPreFreezeInstance(id1);
    mgr.RegisterPreFreezeInstance(id1);
    EXPECT_EQ(mgr.registeredInstances_.size(), 1);
    EXPECT_EQ(mgr.registeredInstances_.count(id1), 1);

    // Branch 2: Multiple distinct ids
    mgr.RegisterPreFreezeInstance(id2);
    mgr.RegisterPreFreezeInstance(id3);
    EXPECT_EQ(mgr.registeredInstances_.size(), 3);
    EXPECT_EQ(mgr.registeredInstances_.count(id1), 1);
    EXPECT_EQ(mgr.registeredInstances_.count(id2), 1);
    EXPECT_EQ(mgr.registeredInstances_.count(id3), 1);

    // Cleanup for next test
    mgr.UnregisterPreFreezeInstance(id1);
    mgr.UnregisterPreFreezeInstance(id2);
    mgr.UnregisterPreFreezeInstance(id3);
    EXPECT_TRUE(mgr.registeredInstances_.empty());

    // Branch 3: externalClearRegistered_ already true, should skip callback registration
    mgr.externalClearRegistered_ = true;
    mgr.RegisterPreFreezeInstance(id1);
    EXPECT_EQ(mgr.registeredInstances_.count(id1), 1);
    EXPECT_TRUE(mgr.externalClearRegistered_);

    // Final cleanup
    mgr.UnregisterPreFreezeInstance(id1);
    EXPECT_TRUE(mgr.registeredInstances_.empty());
    mgr.externalClearRegistered_ = false;
}

/**
 * @tc.name: UnregisterPreFreezeInstance_AllBranches
 * @tc.desc: Test all branches of UnregisterPreFreezeInstance: remove one of many, unregister non-existent id.
 * @tc.type: FUNC
 */
HWTEST_F(DetachedRsNodeManagerTest, UnregisterPreFreezeInstance_AllBranches, TestSize.Level1)
{
    auto& mgr = DetachedRsNodeManager::GetInstance();
    constexpr int32_t id1 = 100;
    constexpr int32_t id2 = 200;
    constexpr int32_t nonExistentId = 999;

    // Branch 1: Remove one of many, verify remaining
    mgr.RegisterPreFreezeInstance(id1);
    mgr.RegisterPreFreezeInstance(id2);
    EXPECT_EQ(mgr.registeredInstances_.size(), 2);

    mgr.UnregisterPreFreezeInstance(id1);
    EXPECT_EQ(mgr.registeredInstances_.size(), 1);
    EXPECT_EQ(mgr.registeredInstances_.count(id1), 0);
    EXPECT_EQ(mgr.registeredInstances_.count(id2), 1);

    // Branch 2: Unregister non-existent id, should have no effect
    mgr.UnregisterPreFreezeInstance(nonExistentId);
    EXPECT_EQ(mgr.registeredInstances_.size(), 1);
    EXPECT_EQ(mgr.registeredInstances_.count(id2), 1);

    // Final cleanup
    mgr.UnregisterPreFreezeInstance(id2);
    EXPECT_TRUE(mgr.registeredInstances_.empty());
}

/**
 * @tc.name: PreFreezeFlushForAllContexts_MultipleInstances
 * @tc.desc: Test PreFreezeFlushForAllContexts with multiple registered instanceIds.
 * @tc.type: FUNC
 */
HWTEST_F(DetachedRsNodeManagerTest, PreFreezeFlushForAllContexts_MultipleInstances, TestSize.Level1)
{
    SetUpFullEnvironment(true);
    auto pipeline = MockPipelineContext::GetCurrent();
    auto* mockWindow = static_cast<MockWindow*>(pipeline->window_.get());
    ASSERT_NE(mockWindow, nullptr);

    auto& mgr = DetachedRsNodeManager::GetInstance();
    constexpr int32_t id1 = 100;
    constexpr int32_t id2 = 101;

    mgr.RegisterPreFreezeInstance(id1);
    mgr.RegisterPreFreezeInstance(id2);

    EXPECT_CALL(*mockWindow, ForceFlushVsync(_, _)).Times(2);

    DetachedRsNodeManager::PreFreezeFlushForAllContexts();

    mgr.UnregisterPreFreezeInstance(id1);
    mgr.UnregisterPreFreezeInstance(id2);
    TearDownFullEnvironment();
}
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_ROSEN_ROSEN_RENDER_CONTEXT_TEST_H
