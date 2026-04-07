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

#include "core/components_ng/relaxed_interaction/relaxed_interaction_manager.h"

#include "base/json/json_util.h"
#include "base/log/log.h"
#include "core/components_ng/relaxed_interaction/base_command_parser.h"
#include "core/components_ng/relaxed_interaction/executor_choreographer.h"
#include "core/components_ng/relaxed_interaction/executor_generator.h"
#include "core/components_ng/relaxed_interaction/executors/backpress_executor.h"
#include "core/components_ng/relaxed_interaction/utils/workflow_dumper.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

RelaxedInteractionManager::RelaxedInteractionManager(WeakPtr<PipelineContext> context) : context_(context)
{
    executorGenerator_ = std::make_unique<ExecutorGenerator>(context);
    choreographer_ = std::make_unique<ExecutorChoreographer>();
}

ProcessResult RelaxedInteractionManager::ProcessCommand(const std::string& jsonStr)
{
    WorkflowDumper::GetInstance().AddLog(jsonStr);
    auto json = JsonUtil::ParseJsonString(jsonStr);
    if (!json || !json->IsValid() || !json->IsObject()) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Invalid command format");
        return ProcessResult::PARSE_ERROR;
    }

    std::vector<std::unique_ptr<BaseExecutor>> executors = executorGenerator_->ParseCommand(json);
    if (executors.empty()) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "No valid executor parsed from command");
        return ProcessResult::VALIDATION_ERROR;
    }

    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "executors size: %{public}zu, types: %{public}s", executors.size(),
            ExecutorsToString(executors).c_str());
    }

    WorkflowDumper::GetInstance().AddLog(ExecutorsToString(executors));
    choreographer_->Enqueue(std::move(executors));
    return ProcessResult::SUCCESS;
}

ExecutionState RelaxedInteractionManager::ExecuteNextStep()
{
    ExecutionState state = DoExecuteNextStep();
    WorkflowDumper::GetInstance().AddLog("Executor '" + choreographer_->GetCurrentExecutorDescription() +
        "' workflow state changed to: " + ExecutionStateToString(state));
    return state;
}

ExecutionState RelaxedInteractionManager::DoExecuteNextStep()
{
    ExecutorResult result = choreographer_->ExecuteNext();

    switch (result) {
        case ExecutorResult::PENDING:
            return ExecutionState::RUNNING;

        case ExecutorResult::SUCCESS:
            // Successful execution, empty all the executors to be executed.
            choreographer_->Clear();
            return ExecutionState::SUCCESS;

        case ExecutorResult::FAILED:
            // Failed execution, check if there are other executors to be executed.
            if (choreographer_->HasNext()) {
                return ExecutionState::RUNNING;
            } else {
                return ExecutionState::FAILED;
            }
    }

    return ExecutionState::FAILED;
}

void RelaxedInteractionManager::Clear()
{
    if (choreographer_) {
        choreographer_->Clear();
    }
}

std::string RelaxedInteractionManager::ExecutorsToString(
    const std::vector<std::unique_ptr<BaseExecutor>>& executors)
{
    std::ostringstream oss;
    for (size_t i = 0; i < executors.size(); ++i) {
        if (i != 0) {
            oss << ",";
        }
        oss << executors[i]->GetDescription();
    }
    return oss.str();
}

std::string RelaxedInteractionManager::ExecutionStateToString(ExecutionState state)
{
    switch (state) {
        case ExecutionState::NONE:
            return "NONE";
        case ExecutionState::RUNNING:
            return "RUNNING";
        case ExecutionState::SUCCESS:
            return "SUCCESS";
        case ExecutionState::FAILED:
            return "FAILED";
        default:
            return "UNKNOWN";
    }
}

} // namespace OHOS::Ace::NG
