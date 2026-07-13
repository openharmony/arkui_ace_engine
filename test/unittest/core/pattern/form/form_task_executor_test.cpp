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

#include "core/components_ng/pattern/form/form_task_executor.h"
#include "base/thread/task_executor.h"
#include "core/components_ng/base/frame_node.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

class FormTaskExecutorTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

protected:
    RefPtr<FrameNode> frameNode_;
};

void FormTaskExecutorTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto pipeline = NG::MockPipelineContext::GetCurrent();
    MockContainer::SetUp(pipeline);
    auto mockTaskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->SetTaskExecutor(mockTaskExecutor);
    pipeline->SetTaskExecutor(mockTaskExecutor);
}

void FormTaskExecutorTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void FormTaskExecutorTest::SetUp()
{
    frameNode_ = FrameNode::CreateFrameNode("Form", 1, nullptr);
}

void FormTaskExecutorTest::TearDown()
{
    frameNode_ = nullptr;
}

/**
 * @tc.name: FormTaskExecutor_PostUITask_001
 * @tc.desc: Verify PostUITask executes task synchronously via MockTaskExecutor
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskExecutorTest, FormTaskExecutor_PostUITask_001, TestSize.Level1)
{
    auto executor = AceType::MakeRefPtr<FormTaskExecutor>(WeakPtr<FrameNode>(frameNode_));
    ASSERT_NE(executor, nullptr);

    // Verify FrameNode can access mock pipeline context through GetContext() fallback
    auto* context = frameNode_->GetContext();
    ASSERT_NE(context, nullptr);

    bool taskExecuted = false;
    executor->PostUITask([&taskExecuted]() { taskExecuted = true; }, "TestUITask");
    EXPECT_TRUE(taskExecuted);
}

/**
 * @tc.name: FormTaskExecutor_PostBgTask_001
 * @tc.desc: Verify PostBgTask executes task synchronously
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskExecutorTest, FormTaskExecutor_PostBgTask_001, TestSize.Level1)
{
    auto executor = AceType::MakeRefPtr<FormTaskExecutor>(WeakPtr<FrameNode>(frameNode_));
    ASSERT_NE(executor, nullptr);

    bool taskExecuted = false;
    executor->PostBgTask([&taskExecuted]() { taskExecuted = true; }, "TestBgTask");
    EXPECT_TRUE(taskExecuted);
}

/**
 * @tc.name: FormTaskExecutor_PostDelayedUITask_001
 * @tc.desc: Verify PostDelayedUITask with delay=0 executes task synchronously
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskExecutorTest, FormTaskExecutor_PostDelayedUITask_001, TestSize.Level1)
{
    auto executor = AceType::MakeRefPtr<FormTaskExecutor>(WeakPtr<FrameNode>(frameNode_));
    ASSERT_NE(executor, nullptr);

    bool taskExecuted = false;
    executor->PostDelayedUITask([&taskExecuted]() { taskExecuted = true; }, 0, "TestDelayedUITask");
    EXPECT_TRUE(taskExecuted);
}

/**
 * @tc.name: FormTaskExecutor_PostDelayedTask_001
 * @tc.desc: Verify PostDelayedTask with UI type and delay=0
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskExecutorTest, FormTaskExecutor_PostDelayedTask_001, TestSize.Level1)
{
    auto executor = AceType::MakeRefPtr<FormTaskExecutor>(WeakPtr<FrameNode>(frameNode_));
    ASSERT_NE(executor, nullptr);

    bool taskExecuted = false;
    executor->PostDelayedTask([&taskExecuted]() { taskExecuted = true; },
        TaskExecutor::TaskType::UI, 0, "TestDelayedTask");
    EXPECT_TRUE(taskExecuted);
}

/**
 * @tc.name: FormTaskExecutor_RemoveUITask_001
 * @tc.desc: Verify RemoveUITask does not crash
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskExecutorTest, FormTaskExecutor_RemoveUITask_001, TestSize.Level1)
{
    auto executor = AceType::MakeRefPtr<FormTaskExecutor>(WeakPtr<FrameNode>(frameNode_));
    ASSERT_NE(executor, nullptr);
    executor->RemoveUITask("TaskToRemove");
}

/**
 * @tc.name: FormTaskExecutor_IsRunOnUIThread_001
 * @tc.desc: Verify IsRunOnUIThread returns true in mock environment
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskExecutorTest, FormTaskExecutor_IsRunOnUIThread_001, TestSize.Level1)
{
    auto executor = AceType::MakeRefPtr<FormTaskExecutor>(WeakPtr<FrameNode>(frameNode_));
    ASSERT_NE(executor, nullptr);
    // MockTaskExecutor's WillRunOnCurrentThread returns true for all task types
    EXPECT_TRUE(executor->IsRunOnUIThread());
}

/**
 * @tc.name: FormTaskExecutor_NullHost_001
 * @tc.desc: Verify all methods handle null host (FrameNode destroyed) gracefully
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskExecutorTest, FormTaskExecutor_NullHost_001, TestSize.Level1)
{
    // Create executor with null host
    auto executor = AceType::MakeRefPtr<FormTaskExecutor>(WeakPtr<FrameNode>(nullptr));
    ASSERT_NE(executor, nullptr);

    bool taskExecuted = false;
    executor->PostUITask([&taskExecuted]() { taskExecuted = true; }, "NullHostTest");
    EXPECT_FALSE(taskExecuted);

    taskExecuted = false;
    executor->PostBgTask([&taskExecuted]() { taskExecuted = true; }, "NullHostTest");
    EXPECT_FALSE(taskExecuted);

    taskExecuted = false;
    executor->PostDelayedUITask([&taskExecuted]() { taskExecuted = true; }, 0, "NullHostTest");
    EXPECT_FALSE(taskExecuted);

    executor->RemoveUITask("NullHostTest");
    EXPECT_FALSE(executor->IsRunOnUIThread());
    EXPECT_FALSE(executor->PostSyncUITask([]() {}, "NullHostTest"));
}

/**
 * @tc.name: FormTaskExecutor_NullTaskExecutor_001
 * @tc.desc: Verify methods handle null task executor gracefully
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskExecutorTest, FormTaskExecutor_NullTaskExecutor_001, TestSize.Level1)
{
    // Temporarily clear task executor on mock pipeline
    auto pipeline = NG::MockPipelineContext::GetCurrent();
    auto savedExecutor = pipeline->GetTaskExecutor();
    pipeline->SetTaskExecutor(RefPtr<TaskExecutor>());

    auto executor = AceType::MakeRefPtr<FormTaskExecutor>(WeakPtr<FrameNode>(frameNode_));
    ASSERT_NE(executor, nullptr);

    bool taskExecuted = false;
    executor->PostUITask([&taskExecuted]() { taskExecuted = true; }, "NullTaskExecutorTest");
    EXPECT_FALSE(taskExecuted);

    EXPECT_FALSE(executor->IsRunOnUIThread());

    // Restore task executor for subsequent tests
    pipeline->SetTaskExecutor(savedExecutor);
}

} // namespace OHOS::Ace::NG
