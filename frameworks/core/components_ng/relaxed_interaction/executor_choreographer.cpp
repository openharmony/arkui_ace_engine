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

#include "core/components_ng/relaxed_interaction/executor_choreographer.h"
#include "core/components_ng/relaxed_interaction/utils/workflow_dumper.h"

namespace OHOS::Ace::NG {

void ExecutorChoreographer::Enqueue(std::vector<std::unique_ptr<BaseExecutor>>&& executors)
{
    for (auto& executor : executors) {
        executorQueue_.push_back(std::move(executor));
    }
}

ExecutorResult ExecutorChoreographer::ExecuteNext()
{
    // If no current executor, try to move to the next one.
    if (!currentExecutor_) {
        if (!MoveToNext() || !currentExecutor_) {
            return ExecutorResult::FAILED;
        }
    }

    ExecutorResult result = currentExecutor_->ExecuteStep();
    WorkflowDumper::GetInstance().AddLog("Executor '" + currentExecutor_->GetDescription() + "' execution result: " +
        ExecutorResultToString(result));
    if (result != ExecutorResult::PENDING) {
        currentExecutor_.reset();
    }

    return result;
}

void ExecutorChoreographer::Clear()
{
    executorQueue_.clear();
    currentExecutor_.reset();
}

bool ExecutorChoreographer::MoveToNext()
{
    if (executorQueue_.empty()) {
        return false;
    }

    currentExecutor_ = std::move(executorQueue_.front());
    executorQueue_.pop_front();
    return true;
}

std::string ExecutorChoreographer::ExecutorResultToString(ExecutorResult result)
{
    switch (result) {
        case ExecutorResult::SUCCESS:
            return "SUCCESS";
        case ExecutorResult::FAILED:
            return "FAILED";
        case ExecutorResult::PENDING:
            return "PENDING";
        default:
            return "UNKNOWN";
    }
}

} // namespace OHOS::Ace::NG
