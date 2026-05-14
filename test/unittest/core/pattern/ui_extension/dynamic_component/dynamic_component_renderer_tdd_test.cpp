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

#include <cstdint>
#include <string>

#include "gtest/gtest.h"
#include "base/memory/ace_type.h"
#define private public
#define protected public
#include "adapter/ohos/entrance/dynamic_component/dynamic_component_renderer_impl.h"
#include "adapter/ohos/entrance/dynamic_component/arkts_dynamic_component_renderer_impl.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const int32_t TEST_NODE_ID = 1;
    const std::string TEST_TAG = "TestNode";
}

class DynamicComponentRendererTddTest : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestCase();
    static void TearDownTestCase();
    RefPtr<FrameNode> CreateTestFrameNode();
};

void DynamicComponentRendererTddTest::SetUp() {}

void DynamicComponentRendererTddTest::TearDown() {}

void DynamicComponentRendererTddTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
}

void DynamicComponentRendererTddTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> DynamicComponentRendererTddTest::CreateTestFrameNode()
{
    return FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, AceType::MakeRefPtr<Pattern>(), true);
}

/**
 * @tc.name: DynamicComponentRenderer_CheckWorkerMaxConstraint_NullWorker
 * @tc.desc: Test CheckWorkerMaxConstraint returns true when worker is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentRendererTddTest,
    DynamicComponentRenderer_CheckWorkerMaxConstraint_NullWorker, TestSize.Level1)
{
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    IsolatedInfo info;
    auto renderer = AceType::MakeRefPtr<DynamicComponentRendererImpl>(frameNode, nullptr, info);
    ASSERT_NE(renderer, nullptr);
    EXPECT_TRUE(renderer->CheckWorkerMaxConstraint(nullptr));
}

/**
 * @tc.name: DynamicComponentRenderer_CheckWorkerMaxConstraint_NoWorkersUsing
 * @tc.desc: Test CheckWorkerMaxConstraint when no workers are in use
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentRendererTddTest,
    DynamicComponentRenderer_CheckWorkerMaxConstraint_NoWorkersUsing, TestSize.Level1)
{
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    IsolatedInfo info;
    auto renderer = AceType::MakeRefPtr<DynamicComponentRendererImpl>(frameNode, nullptr, info);
    ASSERT_NE(renderer, nullptr);
    int workerVar = 1;
    void* worker = &workerVar;
    DynamicComponentRendererImpl::usingWorkers_.clear();
    EXPECT_TRUE(renderer->CheckWorkerMaxConstraint(worker));
}

/**
 * @tc.name: DynamicComponentRenderer_CheckWorkerMaxConstraint_WorkerAlreadyExists
 * @tc.desc: Test CheckWorkerMaxConstraint when worker already exists in usingWorkers_
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentRendererTddTest,
    DynamicComponentRenderer_CheckWorkerMaxConstraint_WorkerAlreadyExists, TestSize.Level1)
{
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    IsolatedInfo info;
    auto renderer = AceType::MakeRefPtr<DynamicComponentRendererImpl>(frameNode, nullptr, info);
    ASSERT_NE(renderer, nullptr);
    int workerVar = 2;
    void* worker = &workerVar;
    DynamicComponentRendererImpl::usingWorkers_.clear();
    DynamicComponentRendererImpl::usingWorkers_[worker] = 1;
    EXPECT_TRUE(renderer->CheckWorkerMaxConstraint(worker));
}

/**
 * @tc.name: DynamicComponentRenderer_CheckDCMaxConstraintInWorker_NullWorker
 * @tc.desc: Test CheckDCMaxConstraintInWorker returns true when worker is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentRendererTddTest,
    DynamicComponentRenderer_CheckDCMaxConstraintInWorker_NullWorker, TestSize.Level1)
{
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    IsolatedInfo info;
    auto renderer = AceType::MakeRefPtr<DynamicComponentRendererImpl>(frameNode, nullptr, info);
    ASSERT_NE(renderer, nullptr);
    EXPECT_TRUE(renderer->CheckDCMaxConstraintInWorker(nullptr));
}

/**
 * @tc.name: DynamicComponentRenderer_CheckDCMaxConstraintInWorker_WorkerNotExists
 * @tc.desc: Test CheckDCMaxConstraintInWorker returns true when worker not in usingWorkers_
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentRendererTddTest,
    DynamicComponentRenderer_CheckDCMaxConstraintInWorker_WorkerNotExists, TestSize.Level1)
{
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    IsolatedInfo info;
    auto renderer = AceType::MakeRefPtr<DynamicComponentRendererImpl>(frameNode, nullptr, info);
    ASSERT_NE(renderer, nullptr);
    int workerVar = 3;
    void* worker = &workerVar;
    DynamicComponentRendererImpl::usingWorkers_.clear();
    EXPECT_TRUE(renderer->CheckDCMaxConstraintInWorker(worker));
}

/**
 * @tc.name: DynamicComponentRenderer_CheckDCMaxConstraintInWorker_BelowMaxLimit
 * @tc.desc: Test CheckDCMaxConstraintInWorker returns true when DC count below max in worker
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentRendererTddTest,
    DynamicComponentRenderer_CheckDCMaxConstraintInWorker_BelowMaxLimit, TestSize.Level1)
{
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    IsolatedInfo info;
    auto renderer = AceType::MakeRefPtr<DynamicComponentRendererImpl>(frameNode, nullptr, info);
    ASSERT_NE(renderer, nullptr);
    int workerVar = 4;
    void* worker = &workerVar;
    DynamicComponentRendererImpl::usingWorkers_.clear();
    DynamicComponentRendererImpl::usingWorkers_[worker] = 2;
    EXPECT_TRUE(renderer->CheckDCMaxConstraintInWorker(worker));
}

/**
 * @tc.name: DynamicComponentRenderer_CheckDCMaxConstraintInWorker_ReachesMaxLimit
 * @tc.desc: Test CheckDCMaxConstraintInWorker returns false when DC count reaches max in worker
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentRendererTddTest,
    DynamicComponentRenderer_CheckDCMaxConstraintInWorker_ReachesMaxLimit, TestSize.Level1)
{
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    IsolatedInfo info;
    auto renderer = AceType::MakeRefPtr<DynamicComponentRendererImpl>(frameNode, nullptr, info);
    ASSERT_NE(renderer, nullptr);
    int workerVar = 5;
    void* worker = &workerVar;
    DynamicComponentRendererImpl::usingWorkers_.clear();
    DynamicComponentRendererImpl::usingWorkers_[worker] = 4;
    EXPECT_FALSE(renderer->CheckDCMaxConstraintInWorker(worker));
}

/**
 * @tc.name: ArktsDynamicRenderer_HasWorkerUsingByWorkerId_InvalidId
 * @tc.desc: Test HasWorkerUsingByWorkerId returns false when workerId is invalid
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentRendererTddTest,
    ArktsDynamicRenderer_HasWorkerUsingByWorkerId_InvalidId, TestSize.Level1)
{
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    DynamicParam param;
    auto renderer = AceType::MakeRefPtr<ArktsDynamicComponentRendererImpl>(frameNode, param);
    ASSERT_NE(renderer, nullptr);
    EXPECT_FALSE(renderer->HasWorkerUsingByWorkerId(-1));
}

/**
 * @tc.name: ArktsDynamicRenderer_HasWorkerUsingByWorkerId_NotExists
 * @tc.desc: Test HasWorkerUsingByWorkerId returns false when workerId not in usingWorkers_
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentRendererTddTest,
    ArktsDynamicRenderer_HasWorkerUsingByWorkerId_NotExists, TestSize.Level1)
{
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    DynamicParam param;
    auto renderer = AceType::MakeRefPtr<ArktsDynamicComponentRendererImpl>(frameNode, param);
    ASSERT_NE(renderer, nullptr);
    ArktsDynamicComponentRendererImpl::usingWorkers_.clear();
    EXPECT_FALSE(renderer->HasWorkerUsingByWorkerId(100));
}

/**
 * @tc.name: ArktsDynamicRenderer_HasWorkerUsingByWorkerId_Exists
 * @tc.desc: Test HasWorkerUsingByWorkerId returns true when workerId exists in usingWorkers_
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentRendererTddTest,
    ArktsDynamicRenderer_HasWorkerUsingByWorkerId_Exists, TestSize.Level1)
{
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    DynamicParam param;
    auto renderer = AceType::MakeRefPtr<ArktsDynamicComponentRendererImpl>(frameNode, param);
    ASSERT_NE(renderer, nullptr);
    ArktsDynamicComponentRendererImpl::usingWorkers_.clear();
    ArktsDynamicComponentRendererImpl::usingWorkers_[200] = 1;
    EXPECT_TRUE(renderer->HasWorkerUsingByWorkerId(200));
}

} // namespace OHOS::Ace::NG
