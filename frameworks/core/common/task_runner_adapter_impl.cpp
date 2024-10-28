/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/common/task_runner_adapter_impl.h"

namespace OHOS::Ace {
TaskRunnerAdapterImpl::~TaskRunnerAdapterImpl()
{
    if (eventHandler_) {
        eventHandler_->RemoveAllEvents();
    }
}

void TaskRunnerAdapterImpl::Initialize(bool useCurrentEventRunner, const std::string& name)
{
    if (useCurrentEventRunner) {
        eventRunner_ = OHOS::AppExecFwk::EventRunner::Current();
    } else if (name == "") {
        eventRunner_ = OHOS::AppExecFwk::EventRunner::GetMainEventRunner();
    } else {
        eventRunner_ = OHOS::AppExecFwk::EventRunner::Create(name);
    }
    eventHandler_ = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner_);
}

void TaskRunnerAdapterImpl::PostTask(std::function<void()> task, const std::string& name, PriorityType priorityType)
{
    eventHandler_->PostTask(std::move(task), name, 0, ConvertPriority(priorityType));
}

void TaskRunnerAdapterImpl::PostTaskForTime(std::function<void()> task, uint32_t targetTime, const std::string& caller)
{
    eventHandler_->PostTimingTask(std::move(task), targetTime, "");
}

void TaskRunnerAdapterImpl::PostDelayedTask(
    std::function<void()> task, uint32_t delay, const std::string& name, PriorityType priorityType)
{
    eventHandler_->PostTask(std::move(task), name, delay, ConvertPriority(priorityType));
}

bool TaskRunnerAdapterImpl::RunsTasksOnCurrentThread()
{
    return eventRunner_->IsCurrentRunnerThread();
}

void TaskRunnerAdapterImpl::RemoveTask(const std::string &name)
{
    eventHandler_->RemoveTask(name);
}

AppExecFwk::EventQueue::Priority TaskRunnerAdapterImpl::ConvertPriority(PriorityType priorityType)
{
    switch (priorityType) {
        case PriorityType::VIP:
            return AppExecFwk::EventQueue::Priority::VIP;
        case PriorityType::IMMEDIATE:
            return AppExecFwk::EventQueue::Priority::IMMEDIATE;
        case PriorityType::HIGH:
            return AppExecFwk::EventQueue::Priority::HIGH;
        case PriorityType::LOW:
            return AppExecFwk::EventQueue::Priority::LOW;
        case PriorityType::IDLE:
            return AppExecFwk::EventQueue::Priority::IDLE;
        default:
            LOGW("unknown priority type");
            return AppExecFwk::EventQueue::Priority::LOW;
    }
}
} // namespace OHOS::Ace
