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

#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_state_machine.h"

#include "ui/base/utils/utils.h"

#include "base/thread/task_executor.h"
#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_detector.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

DragDropSpringLoadingStateMachine::DragDropSpringLoadingStateMachine()
{
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    taskExecutor_ = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
}

bool DragDropSpringLoadingStateMachine::DragDropSpringLoadingStateMachinePool::IsAllowedTransition(
    DragDropSpringLoadingState from, DragDropSpringLoadingState to) const
{
    auto it = states_.find(from);
    if (it != states_.end()) {
        const auto& transitions = it->second.transitions;
        return std::find(transitions.begin(), transitions.end(), to) != transitions.end();
    }
    return false;
}

bool DragDropSpringLoadingStateMachine::RequestStatusTransition(
    DragDropSpringLoadingState nextState, std::string_view extraInfo)
{
    CHECK_NULL_RETURN(stateMachinePool_, false);
    TAG_LOGI(AceLogTag::ACE_DRAG, "RequestStatusTransition from %{public}d to %{public}d.",
        static_cast<int32_t>(currentState_), static_cast<int32_t>(nextState));
    if (!stateMachinePool_->IsAllowedTransition(currentState_, nextState)) {
        return false;
    }
    auto originalState = currentState_;
    currentState_ = nextState;
    if (auto nextStateHandler = stateMachinePool_->GetStateHandler(currentState_)) {
        nextStateHandler->OnEnter(extraInfo);
        return true;
    } else {
        currentState_ = originalState;
        return false;
    }
}

void DragDropSpringLoadingStateMachine::ResetMachine()
{
    timer_.Cancel();
    currentState_ = DragDropSpringLoadingState::IDLE;
    isWaitingForIdleFinish_ = false;
    currentNotifySequence_ = -1;
    currentUpdateNotifyCount_ = 0;
    userConfig_.Reset();
}

void DragDropSpringLoadingStateMachine::PostDelayedTask(
    const std::function<void()>&& task, uint32_t delay, const std::string& name)
{
    CHECK_NULL_VOID(taskExecutor_);
    timer_.Reset(std::move(task));
    taskExecutor_->PostDelayedTask(timer_, delay, name);
}

void DragDropSpringLoadingStateMachine::Begin(std::string_view extraInfo)
{
    currentState_ = DragDropSpringLoadingState::IDLE;
    if (auto handler = stateMachinePool_->GetStateHandler(currentState_)) {
        isWaitingForIdleFinish_ = true;
        handler->OnEnter(extraInfo);
    }
}

Point DragDropSpringLoadingStateMachine::GetPoint()
{
    auto detector = detector_.Upgrade();
    CHECK_NULL_RETURN(detector, Point(0, 0));
    return detector->GetPoint();
}

RefPtr<FrameNode> DragDropSpringLoadingStateMachine::GetFrameNode()
{
    auto detector = detector_.Upgrade();
    CHECK_NULL_RETURN(detector, nullptr);
    return detector->GetFrameNode();
}

} // namespace OHOS::Ace::NG