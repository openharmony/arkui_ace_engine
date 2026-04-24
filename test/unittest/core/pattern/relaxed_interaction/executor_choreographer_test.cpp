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

#include "core/components_ng/relaxed_interaction/executor_choreographer.h"
#include "core/components_ng/relaxed_interaction/relaxed_interaction_types.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t INVALID_EXECUTOR_RESULT_VALUE = 999;
constexpr size_t EXPECTED_SINGLE_EXECUTOR_COUNT = 1u;
constexpr size_t EXPECTED_THREE_EXECUTOR_COUNT = 3u;

class MockExecutor : public BaseExecutor {
public:
    explicit MockExecutor(ExecutorResult result, bool singleStep = true)
        : BaseExecutor(nullptr), result_(result), singleStep_(singleStep), stepCount_(0)
    {}

    ExecutorResult ExecuteStep() override
    {
        stepCount_++;
        return result_;
    }

    std::string GetType() const override
    {
        return "mock";
    }

    bool IsSingleStep() const override
    {
        return singleStep_;
    }

    int GetStepCount() const
    {
        return stepCount_;
    }

private:
    ExecutorResult result_;
    bool singleStep_;
    int stepCount_;
};
} // namespace

class ExecutorChoreographerTest : public testing::Test {
public:
    void SetUp() override
    {
        choreographer_ = std::make_unique<ExecutorChoreographer>();
        ASSERT_NE(choreographer_, nullptr);
    }

    void TearDown() override
    {
        choreographer_.reset();
    }

protected:
    std::unique_ptr<ExecutorChoreographer> choreographer_;
};

class ExecutorChoreographerEnqueueTest : public ExecutorChoreographerTest {};
class ExecutorChoreographerExecuteNextTest : public ExecutorChoreographerTest {};
class ExecutorChoreographerClearTest : public ExecutorChoreographerTest {};

// ============ Enqueue Tests ============

HWTEST_F(ExecutorChoreographerEnqueueTest, Enqueue_SingleExecutor, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.push_back(std::make_unique<MockExecutor>(ExecutorResult::SUCCESS));
    choreographer_->Enqueue(std::move(executors));
    EXPECT_EQ(choreographer_->GetQueueSize(), EXPECTED_SINGLE_EXECUTOR_COUNT);
    EXPECT_TRUE(choreographer_->HasNext());
}

HWTEST_F(ExecutorChoreographerEnqueueTest, Enqueue_MultipleExecutors, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.push_back(std::make_unique<MockExecutor>(ExecutorResult::SUCCESS));
    executors.push_back(std::make_unique<MockExecutor>(ExecutorResult::FAILED));
    executors.push_back(std::make_unique<MockExecutor>(ExecutorResult::PENDING));
    choreographer_->Enqueue(std::move(executors));
    EXPECT_EQ(choreographer_->GetQueueSize(), EXPECTED_THREE_EXECUTOR_COUNT);
}

HWTEST_F(ExecutorChoreographerEnqueueTest, Enqueue_EmptyVector, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    choreographer_->Enqueue(std::move(executors));
    EXPECT_EQ(choreographer_->GetQueueSize(), 0u);
    EXPECT_FALSE(choreographer_->HasNext());
}

HWTEST_F(ExecutorChoreographerEnqueueTest, Enqueue_AppendToNonEmptyQueue, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors1;
    executors1.push_back(std::make_unique<MockExecutor>(ExecutorResult::SUCCESS));
    choreographer_->Enqueue(std::move(executors1));
    EXPECT_EQ(choreographer_->GetQueueSize(), EXPECTED_SINGLE_EXECUTOR_COUNT);

    std::vector<std::unique_ptr<BaseExecutor>> executors2;
    executors2.push_back(std::make_unique<MockExecutor>(ExecutorResult::FAILED));
    executors2.push_back(std::make_unique<MockExecutor>(ExecutorResult::PENDING));
    choreographer_->Enqueue(std::move(executors2));
    EXPECT_EQ(choreographer_->GetQueueSize(), EXPECTED_THREE_EXECUTOR_COUNT);
}

// ============ ExecuteNext Tests ============

HWTEST_F(ExecutorChoreographerExecuteNextTest, ExecuteNext_EmptyQueue, TestSize.Level1)
{
    EXPECT_EQ(choreographer_->ExecuteNext(), ExecutorResult::FAILED);
    EXPECT_FALSE(choreographer_->HasCurrent());
}

HWTEST_F(ExecutorChoreographerExecuteNextTest, ExecuteNext_SuccessResetsCurrent, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.push_back(std::make_unique<MockExecutor>(ExecutorResult::SUCCESS));
    choreographer_->Enqueue(std::move(executors));
    EXPECT_EQ(choreographer_->ExecuteNext(), ExecutorResult::SUCCESS);
    EXPECT_FALSE(choreographer_->HasCurrent());
}

HWTEST_F(ExecutorChoreographerExecuteNextTest, ExecuteNext_FailedResetsCurrent, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.push_back(std::make_unique<MockExecutor>(ExecutorResult::FAILED));
    choreographer_->Enqueue(std::move(executors));
    EXPECT_EQ(choreographer_->ExecuteNext(), ExecutorResult::FAILED);
    EXPECT_FALSE(choreographer_->HasCurrent());
}

HWTEST_F(ExecutorChoreographerExecuteNextTest, ExecuteNext_PendingKeepsCurrent, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.push_back(std::make_unique<MockExecutor>(ExecutorResult::PENDING));
    choreographer_->Enqueue(std::move(executors));
    EXPECT_EQ(choreographer_->ExecuteNext(), ExecutorResult::PENDING);
    EXPECT_TRUE(choreographer_->HasCurrent());
}

HWTEST_F(ExecutorChoreographerExecuteNextTest, ExecuteNext_PendingRetainsSameExecutor, TestSize.Level1)
{
    auto mockExecutor = std::make_unique<MockExecutor>(ExecutorResult::PENDING);
    MockExecutor* rawPtr = mockExecutor.get();
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.push_back(std::move(mockExecutor));
    choreographer_->Enqueue(std::move(executors));

    EXPECT_EQ(choreographer_->ExecuteNext(), ExecutorResult::PENDING);
    EXPECT_EQ(rawPtr->GetStepCount(), 1);

    // PENDING retains current executor, next call continues on same one
    EXPECT_EQ(choreographer_->ExecuteNext(), ExecutorResult::PENDING);
    EXPECT_TRUE(choreographer_->HasCurrent());
    EXPECT_EQ(rawPtr->GetStepCount(), 2);
}

HWTEST_F(ExecutorChoreographerExecuteNextTest, ExecuteNext_SequentialExecutors, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.push_back(std::make_unique<MockExecutor>(ExecutorResult::SUCCESS));
    executors.push_back(std::make_unique<MockExecutor>(ExecutorResult::FAILED));
    choreographer_->Enqueue(std::move(executors));

    EXPECT_EQ(choreographer_->ExecuteNext(), ExecutorResult::SUCCESS);
    EXPECT_FALSE(choreographer_->HasCurrent());
    EXPECT_EQ(choreographer_->GetQueueSize(), EXPECTED_SINGLE_EXECUTOR_COUNT);

    EXPECT_EQ(choreographer_->ExecuteNext(), ExecutorResult::FAILED);
    EXPECT_FALSE(choreographer_->HasCurrent());
    EXPECT_EQ(choreographer_->GetQueueSize(), 0u);

    // Queue exhausted, further calls return FAILED
    EXPECT_EQ(choreographer_->ExecuteNext(), ExecutorResult::FAILED);
}

HWTEST_F(ExecutorChoreographerExecuteNextTest, ExecuteNext_PendingWithNextInQueue, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.push_back(std::make_unique<MockExecutor>(ExecutorResult::PENDING));
    executors.push_back(std::make_unique<MockExecutor>(ExecutorResult::SUCCESS));
    choreographer_->Enqueue(std::move(executors));

    // PENDING keeps current executor even when next executor is in queue
    EXPECT_EQ(choreographer_->ExecuteNext(), ExecutorResult::PENDING);
    EXPECT_TRUE(choreographer_->HasCurrent());
    EXPECT_EQ(choreographer_->GetQueueSize(), EXPECTED_SINGLE_EXECUTOR_COUNT);
}

// ============ Clear Tests ============

HWTEST_F(ExecutorChoreographerClearTest, Clear_EmptyChoreographer, TestSize.Level1)
{
    choreographer_->Clear();
    EXPECT_EQ(choreographer_->GetQueueSize(), 0u);
    EXPECT_FALSE(choreographer_->HasCurrent());
    EXPECT_FALSE(choreographer_->HasNext());
}

HWTEST_F(ExecutorChoreographerClearTest, Clear_WithQueuedExecutors, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.push_back(std::make_unique<MockExecutor>(ExecutorResult::SUCCESS));
    executors.push_back(std::make_unique<MockExecutor>(ExecutorResult::FAILED));
    choreographer_->Enqueue(std::move(executors));

    choreographer_->Clear();
    EXPECT_EQ(choreographer_->GetQueueSize(), 0u);
    EXPECT_FALSE(choreographer_->HasCurrent());
    EXPECT_FALSE(choreographer_->HasNext());
}

HWTEST_F(ExecutorChoreographerClearTest, Clear_WithCurrentExecutor, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.push_back(std::make_unique<MockExecutor>(ExecutorResult::PENDING));
    executors.push_back(std::make_unique<MockExecutor>(ExecutorResult::SUCCESS));
    choreographer_->Enqueue(std::move(executors));

    choreographer_->ExecuteNext();
    EXPECT_TRUE(choreographer_->HasCurrent());

    choreographer_->Clear();
    EXPECT_EQ(choreographer_->GetQueueSize(), 0u);
    EXPECT_FALSE(choreographer_->HasCurrent());
}

HWTEST_F(ExecutorChoreographerClearTest, Clear_ThenEnqueue, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors1;
    executors1.push_back(std::make_unique<MockExecutor>(ExecutorResult::SUCCESS));
    choreographer_->Enqueue(std::move(executors1));
    choreographer_->Clear();

    std::vector<std::unique_ptr<BaseExecutor>> executors2;
    executors2.push_back(std::make_unique<MockExecutor>(ExecutorResult::FAILED));
    choreographer_->Enqueue(std::move(executors2));
    EXPECT_EQ(choreographer_->GetQueueSize(), 1u);
    EXPECT_EQ(choreographer_->ExecuteNext(), ExecutorResult::FAILED);
}

// ============ ExecutorResultToString Tests ============

HWTEST_F(ExecutorChoreographerTest, ExecutorResultToString_Success, TestSize.Level1)
{
    EXPECT_EQ(choreographer_->ExecutorResultToString(ExecutorResult::SUCCESS), "SUCCESS");
}

HWTEST_F(ExecutorChoreographerTest, ExecutorResultToString_Failed, TestSize.Level1)
{
    EXPECT_EQ(choreographer_->ExecutorResultToString(ExecutorResult::FAILED), "FAILED");
}

HWTEST_F(ExecutorChoreographerTest, ExecutorResultToString_Pending, TestSize.Level1)
{
    EXPECT_EQ(choreographer_->ExecutorResultToString(ExecutorResult::PENDING), "PENDING");
}

HWTEST_F(ExecutorChoreographerTest, ExecutorResultToString_Default, TestSize.Level1)
{
    auto invalidValue = static_cast<ExecutorResult>(INVALID_EXECUTOR_RESULT_VALUE);
    EXPECT_EQ(choreographer_->ExecutorResultToString(invalidValue), "UNKNOWN");
}

} // namespace OHOS::Ace::NG
