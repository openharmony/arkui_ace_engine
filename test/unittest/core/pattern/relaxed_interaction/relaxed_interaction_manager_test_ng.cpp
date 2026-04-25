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

#include "relaxed_interaction_manager_test_ng.h"

#include "core/components_ng/relaxed_interaction/executor_choreographer.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string VALID_BACKPRESS_JSON = R"({
  "cmd": {
    "type": "backpress"
  }
})";

const std::string INVALID_JSON_EMPTY = "{}";

const std::string INVALID_JSON_SYNTAX = "{invalid json}";

const std::string INVALID_CMD_MISSING_TYPE = R"({
  "cmd": {}
})";

const std::string INVALID_CMD_UNKNOWN_TYPE = R"({
  "cmd": {
    "type": "unknown_type"
  }
})";

const std::string VALID_BACKPRESS_JSON_WITH_FALLBACK = R"({
  "cmd": {
    "type": "backpress"
  },
  "fallback_cmd": {}
})";

const std::string VALID_TAP_JSON = R"({
  "cmd": {
    "type": "tap"
  }
})";

const std::string VALID_SLIDE_JSON = R"({
  "cmd": {
    "type": "slide"
  }
})";

// Mock executor that returns configurable results
class MockExecutor : public BaseExecutor {
public:
    explicit MockExecutor(ExecutorResult result, bool isSingleStep = true)
        : BaseExecutor(nullptr), result_(result), isSingleStep_(isSingleStep)
    {}
    ExecutorResult ExecuteStep() override
    {
        return result_;
    }
    std::string GetType() const override
    {
        return "mock";
    }
    bool IsSingleStep() const override
    {
        return isSingleStep_;
    }
    void SetResult(ExecutorResult result)
    {
        result_ = result;
    }

private:
    ExecutorResult result_;
    bool isSingleStep_;
};

} // namespace

class RelaxedInteractionManagerConstructorTest : public RelaxedInteractionManagerTestBase {};
class RelaxedInteractionManagerProcessCommandTest : public RelaxedInteractionManagerTestBase {};
class RelaxedInteractionManagerExecuteNextStepTest : public RelaxedInteractionManagerTestBase {};
class RelaxedInteractionManagerClearTest : public RelaxedInteractionManagerTestBase {};
class RelaxedInteractionManagerExecutorsToStringTest : public RelaxedInteractionManagerTestBase {};
class RelaxedInteractionManagerExecutionStateToStringTest : public RelaxedInteractionManagerTestBase {};

/**
 * @tc.name: RelaxedInteractionManager_Constructor
 * @tc.desc: Test RelaxedInteractionManager constructor initializes executorGenerator_ and choreographer_
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerConstructorTest, RelaxedInteractionManager_Constructor, TestSize.Level1)
{
    ASSERT_NE(manager_->executorGenerator_, nullptr);
    ASSERT_NE(manager_->choreographer_, nullptr);
}

/**
 * @tc.name: RelaxedInteractionManager_Constructor_NullContext
 * @tc.desc: Test RelaxedInteractionManager constructor with null context
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerConstructorTest, Constructor_NullContext, TestSize.Level1)
{
    auto mgr = AceType::MakeRefPtr<RelaxedInteractionManager>(WeakPtr<PipelineContext>());
    ASSERT_NE(mgr, nullptr);
    ASSERT_NE(mgr->executorGenerator_, nullptr);
    ASSERT_NE(mgr->choreographer_, nullptr);
}

/**
 * @tc.name: ProcessCommand_ValidBackpressJson
 * @tc.desc: Test ProcessCommand returns SUCCESS when valid backpress JSON is provided
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerProcessCommandTest, ProcessCommand_ValidBackpressJson, TestSize.Level1)
{
    auto result = manager_->ProcessCommand(VALID_BACKPRESS_JSON);
    EXPECT_EQ(result, ProcessResult::SUCCESS);
}

/**
 * @tc.name: ProcessCommand_InvalidJsonSyntax
 * @tc.desc: Test ProcessCommand returns PARSE_ERROR when JSON has syntax error
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerProcessCommandTest, ProcessCommand_InvalidJsonSyntax, TestSize.Level1)
{
    auto result = manager_->ProcessCommand(INVALID_JSON_SYNTAX);
    EXPECT_EQ(result, ProcessResult::PARSE_ERROR);
}

/**
 * @tc.name: ProcessCommand_InvalidJsonEmpty
 * @tc.desc: Test ProcessCommand returns VALIDATION_ERROR when JSON is empty object
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerProcessCommandTest, ProcessCommand_InvalidJsonEmpty, TestSize.Level1)
{
    auto result = manager_->ProcessCommand(INVALID_JSON_EMPTY);
    EXPECT_EQ(result, ProcessResult::VALIDATION_ERROR);
}

/**
 * @tc.name: ProcessCommand_InvalidCmdMissingType
 * @tc.desc: Test ProcessCommand returns VALIDATION_ERROR when cmd is missing type field
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerProcessCommandTest, ProcessCommand_InvalidCmdMissingType, TestSize.Level1)
{
    auto result = manager_->ProcessCommand(INVALID_CMD_MISSING_TYPE);
    EXPECT_EQ(result, ProcessResult::VALIDATION_ERROR);
}

/**
 * @tc.name: ProcessCommand_InvalidCmdUnknownType
 * @tc.desc: Test ProcessCommand returns VALIDATION_ERROR when cmd has unknown type
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerProcessCommandTest, ProcessCommand_InvalidCmdUnknownType, TestSize.Level1)
{
    auto result = manager_->ProcessCommand(INVALID_CMD_UNKNOWN_TYPE);
    EXPECT_EQ(result, ProcessResult::VALIDATION_ERROR);
}

/**
 * @tc.name: ProcessCommand_ValidTapJson
 * @tc.desc: Test ProcessCommand returns SUCCESS when valid tap JSON is provided
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerProcessCommandTest, ProcessCommand_ValidTapJson, TestSize.Level1)
{
    auto result = manager_->ProcessCommand(VALID_TAP_JSON);
    EXPECT_EQ(result, ProcessResult::SUCCESS);
}

/**
 * @tc.name: ProcessCommand_ValidSlideJson
 * @tc.desc: Test ProcessCommand returns SUCCESS when valid slide JSON is provided
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerProcessCommandTest, ProcessCommand_ValidSlideJson, TestSize.Level1)
{
    auto result = manager_->ProcessCommand(VALID_SLIDE_JSON);
    EXPECT_EQ(result, ProcessResult::SUCCESS);
}

/**
 * @tc.name: ProcessCommand_FallbackCmdPath
 * @tc.desc: Test ProcessCommand with fallback_cmd key takes fallback path but returns VALIDATION_ERROR for empty
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerProcessCommandTest, ProcessCommand_FallbackCmdPath, TestSize.Level1)
{
    auto result = manager_->ProcessCommand(VALID_BACKPRESS_JSON_WITH_FALLBACK);
    // When "fallback_cmd" key is present, only ParseFallbackCmd path is taken (cmd is ignored).
    // The fallback_cmd value is "{}" which produces no executor, so VALIDATION_ERROR is returned.
    EXPECT_EQ(result, ProcessResult::VALIDATION_ERROR);
}

/**
 * @tc.name: ProcessCommand_EmptyString
 * @tc.desc: Test ProcessCommand returns PARSE_ERROR when empty string is provided
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerProcessCommandTest, ProcessCommand_EmptyString, TestSize.Level1)
{
    auto result = manager_->ProcessCommand("");
    EXPECT_EQ(result, ProcessResult::PARSE_ERROR);
}

/**
 * @tc.name: ProcessCommand_SequentialCalls
 * @tc.desc: Test ProcessCommand called sequentially replaces choreographer state correctly
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerProcessCommandTest, ProcessCommand_SequentialCalls, TestSize.Level1)
{
    auto result1 = manager_->ProcessCommand(VALID_BACKPRESS_JSON);
    EXPECT_EQ(result1, ProcessResult::SUCCESS);
    // Second call should also succeed and enqueue new executors
    auto result2 = manager_->ProcessCommand(VALID_TAP_JSON);
    EXPECT_EQ(result2, ProcessResult::SUCCESS);
}

/**
 * @tc.name: ProcessCommand_NullContext
 * @tc.desc: Test ProcessCommand with null context manager does not crash
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerProcessCommandTest, ProcessCommand_NullContext, TestSize.Level1)
{
    auto mgr = AceType::MakeRefPtr<RelaxedInteractionManager>(WeakPtr<PipelineContext>());
    auto result = mgr->ProcessCommand(VALID_BACKPRESS_JSON);
    // Executor generation with null context should still succeed (executors may fail at execution time)
    EXPECT_EQ(result, ProcessResult::SUCCESS);
}

/**
 * @tc.name: ExecuteNextStep_NoExecutors_ReturnsFailed
 * @tc.desc: Test ExecuteNextStep returns FAILED when no executors are queued
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerExecuteNextStepTest, ExecuteNextStep_NoExecutors_ReturnsFailed, TestSize.Level1)
{
    auto state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::FAILED);
}

/**
 * @tc.name: ExecuteNextStep_ExecutorFailed_NoNext_ReturnsFailed
 * @tc.desc: Test ExecuteNextStep returns FAILED when executor fails and no next executor
 * @tc.type: FUNC
 */
HWTEST_F(
    RelaxedInteractionManagerExecuteNextStepTest, ExecuteNextStep_ExecutorFailed_NoNext_ReturnsFailed, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.emplace_back(std::make_unique<MockExecutor>(ExecutorResult::FAILED));
    manager_->choreographer_->Enqueue(std::move(executors));

    auto state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::FAILED);
}

/**
 * @tc.name: ExecuteNextStep_ExecutorSuccess_ClearsAll
 * @tc.desc: Test ExecuteNextStep returns SUCCESS and clears all executors when executor succeeds
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerExecuteNextStepTest, ExecuteNextStep_ExecutorSuccess_ClearsAll, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.emplace_back(std::make_unique<MockExecutor>(ExecutorResult::SUCCESS));
    manager_->choreographer_->Enqueue(std::move(executors));

    auto state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::SUCCESS);

    // After success, choreographer should be cleared, next call returns FAILED
    state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::FAILED);
}

/**
 * @tc.name: ExecuteNextStep_ExecutorPending_ReturnsRunning
 * @tc.desc: Test ExecuteNextStep returns RUNNING when executor returns PENDING
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerExecuteNextStepTest, ExecuteNextStep_ExecutorPending_ReturnsRunning, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.emplace_back(std::make_unique<MockExecutor>(ExecutorResult::PENDING));
    manager_->choreographer_->Enqueue(std::move(executors));

    auto state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::RUNNING);
}

/**
 * @tc.name: ExecuteNextStep_ExecutorFailed_HasNext_ReturnsRunning
 * @tc.desc: Test ExecuteNextStep returns RUNNING when executor fails but has next executor
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerExecuteNextStepTest, ExecuteNextStep_ExecutorFailed_HasNext_ReturnsRunning,
    TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.emplace_back(std::make_unique<MockExecutor>(ExecutorResult::FAILED));
    executors.emplace_back(std::make_unique<MockExecutor>(ExecutorResult::SUCCESS));
    manager_->choreographer_->Enqueue(std::move(executors));

    // First executor fails, but there's a next one
    auto state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::RUNNING);

    // Second executor succeeds
    state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::SUCCESS);
}

/**
 * @tc.name: ExecuteNextStep_PendingThenSuccess
 * @tc.desc: Test ExecuteNextStep transitions from PENDING to SUCCESS
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerExecuteNextStepTest, ExecuteNextStep_PendingThenSuccess, TestSize.Level1)
{
    auto mockExec = std::make_unique<MockExecutor>(ExecutorResult::PENDING);
    auto rawPtr = mockExec.get();
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.emplace_back(std::move(mockExec));
    manager_->choreographer_->Enqueue(std::move(executors));

    // First call returns RUNNING (PENDING)
    auto state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::RUNNING);

    // Change executor result to SUCCESS
    rawPtr->SetResult(ExecutorResult::SUCCESS);

    // Next call returns SUCCESS
    state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::SUCCESS);
}

/**
 * @tc.name: ExecuteNextStep_PendingThenFailed_NoNext
 * @tc.desc: Test ExecuteNextStep transitions from PENDING to FAILED with no next executor
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerExecuteNextStepTest, ExecuteNextStep_PendingThenFailed_NoNext, TestSize.Level1)
{
    auto mockExec = std::make_unique<MockExecutor>(ExecutorResult::PENDING);
    auto rawPtr = mockExec.get();
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.emplace_back(std::move(mockExec));
    manager_->choreographer_->Enqueue(std::move(executors));

    // First call returns RUNNING (PENDING)
    auto state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::RUNNING);

    // Change executor result to FAILED
    rawPtr->SetResult(ExecutorResult::FAILED);

    // Next call returns FAILED (no more executors)
    state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::FAILED);
}

/**
 * @tc.name: ExecuteNextStep_MultipleFailuresThenSuccess
 * @tc.desc: Test multiple executors fail before one succeeds
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerExecuteNextStepTest, ExecuteNextStep_MultipleFailuresThenSuccess, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.emplace_back(std::make_unique<MockExecutor>(ExecutorResult::FAILED));
    executors.emplace_back(std::make_unique<MockExecutor>(ExecutorResult::FAILED));
    executors.emplace_back(std::make_unique<MockExecutor>(ExecutorResult::SUCCESS));
    manager_->choreographer_->Enqueue(std::move(executors));

    // First fails, has next
    auto state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::RUNNING);

    // Second fails, has next
    state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::RUNNING);

    // Third succeeds, clears all
    state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::SUCCESS);
}

/**
 * @tc.name: ExecuteNextStep_AllFail_ReturnsFailed
 * @tc.desc: Test all executors fail returns FAILED
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerExecuteNextStepTest, ExecuteNextStep_AllFail_ReturnsFailed, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.emplace_back(std::make_unique<MockExecutor>(ExecutorResult::FAILED));
    executors.emplace_back(std::make_unique<MockExecutor>(ExecutorResult::FAILED));
    manager_->choreographer_->Enqueue(std::move(executors));

    // First fails, has next
    auto state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::RUNNING);

    // Second fails, no next
    state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::FAILED);
}

/**
 * @tc.name: ExecuteNextStep_NullContext
 * @tc.desc: Test ExecuteNextStep with null context manager does not crash
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerExecuteNextStepTest, ExecuteNextStep_NullContext, TestSize.Level1)
{
    auto mgr = AceType::MakeRefPtr<RelaxedInteractionManager>(WeakPtr<PipelineContext>());
    auto state = mgr->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::FAILED);
}

/**
 * @tc.name: ExecuteNextStep_EnqueueEmptyVector
 * @tc.desc: Test ExecuteNextStep after Enqueue with empty vector returns FAILED
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerExecuteNextStepTest, ExecuteNextStep_EnqueueEmptyVector, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    manager_->choreographer_->Enqueue(std::move(executors));

    auto state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::FAILED);
}

/**
 * @tc.name: Clear_ResetsChoreographer
 * @tc.desc: Test Clear method clears choreographer_ internal state
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerClearTest, Clear_ResetsChoreographer, TestSize.Level1)
{
    manager_->ProcessCommand(VALID_BACKPRESS_JSON);
    manager_->Clear();

    // After clear, ExecuteNextStep should return FAILED
    auto state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::FAILED);
}

/**
 * @tc.name: Clear_AfterSuccessfulExecution
 * @tc.desc: Test Clear after successful execution
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerClearTest, Clear_AfterSuccessfulExecution, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.emplace_back(std::make_unique<MockExecutor>(ExecutorResult::SUCCESS));
    manager_->choreographer_->Enqueue(std::move(executors));

    auto state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::SUCCESS);

    manager_->Clear();
    state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::FAILED);
}

/**
 * @tc.name: Clear_NoopWhenEmpty
 * @tc.desc: Test Clear on empty manager resets state, subsequent ExecuteNextStep returns FAILED
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerClearTest, Clear_NoopWhenEmpty, TestSize.Level1)
{
    manager_->Clear();
    manager_->Clear();

    // Verify Clear actually cleared state by checking ExecuteNextStep
    auto state = manager_->ExecuteNextStep();
    EXPECT_EQ(state, ExecutionState::FAILED);
}

/**
 * @tc.name: ExecutorsToString_SingleExecutor_NoComma
 * @tc.desc: Test ExecutorsToString with single executor contains exactly one executor description
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerExecutorsToStringTest, ExecutorsToString_SingleExecutor_NoComma, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.emplace_back(std::make_unique<MockExecutor>(ExecutorResult::SUCCESS));
    auto result = manager_->ExecutorsToString(executors);
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, executors[0]->GetDescription());
}

/**
 * @tc.name: ExecutorsToString_MultipleExecutors_WithComma
 * @tc.desc: Test ExecutorsToString with multiple executors produces comma-separated descriptions
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerExecutorsToStringTest, ExecutorsToString_MultipleExecutors_WithComma, TestSize.Level1)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.emplace_back(std::make_unique<MockExecutor>(ExecutorResult::FAILED));
    executors.emplace_back(std::make_unique<MockExecutor>(ExecutorResult::SUCCESS));
    auto result = manager_->ExecutorsToString(executors);
    std::string expected = executors[0]->GetDescription() + "," + executors[1]->GetDescription();
    EXPECT_EQ(result, expected);
}

/**
 * @tc.name: ExecutionStateToString_NONE
 * @tc.desc: Test ExecutionStateToString with NONE returns "NONE"
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerExecutionStateToStringTest, ExecutionStateToString_NONE, TestSize.Level1)
{
    auto result = manager_->ExecutionStateToString(ExecutionState::NONE);
    EXPECT_EQ(result, "NONE");
}

/**
 * @tc.name: ExecutionStateToString_InvalidValue_ReturnsUnknown
 * @tc.desc: Test ExecutionStateToString with invalid enum value returns "UNKNOWN"
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerExecutionStateToStringTest, ExecutionStateToString_InvalidValue_ReturnsUnknown,
    TestSize.Level1)
{
    constexpr int invalidExecutionStateValue = 999;
    auto invalidState = static_cast<ExecutionState>(invalidExecutionStateValue);
    auto result = manager_->ExecutionStateToString(invalidState);
    EXPECT_EQ(result, "UNKNOWN");
}

} // namespace OHOS::Ace::NG
