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

#include "core/components_ng/pattern/form/form_task_executor.h"

#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t FORM_TASK_PRIORITY_VIP = 0;
constexpr int32_t FORM_TASK_PRIORITY_IMMEDIATE = 1;

PriorityType GetFormTaskPriorityType()
{
    const int32_t formTaskPriority = SystemProperties::GetFormTaskPriority();
    switch (formTaskPriority) {
        case FORM_TASK_PRIORITY_VIP:
            return PriorityType::VIP;
        case FORM_TASK_PRIORITY_IMMEDIATE:
            return PriorityType::IMMEDIATE;
        default:
            return PriorityType::HIGH;
    }
}
} // namespace

FormTaskExecutor::FormTaskExecutor(int32_t instanceId) : instanceId_(instanceId) {}

PriorityType FormTaskExecutor::GetFormTaskPriority()
{
    static PriorityType formTaskPriority = GetFormTaskPriorityType();
    return formTaskPriority;
}

RefPtr<TaskExecutor> FormTaskExecutor::GetTaskExecutor() const
{
    auto pipeline = PipelineContext::GetContextByContainerId(instanceId_);
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetTaskExecutor();
}

void FormTaskExecutor::PostUITask(const TaskExecutor::Task& task, const std::string& name)
{
    auto taskExecutor = GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(task, TaskExecutor::TaskType::UI, 0, name, GetFormTaskPriority());
}

void FormTaskExecutor::PostBgTask(const TaskExecutor::Task& task, const std::string& name)
{
    auto taskExecutor = GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(task, TaskExecutor::TaskType::BACKGROUND, 0, name, GetFormTaskPriority());
}

void FormTaskExecutor::PostDelayedUITask(const TaskExecutor::Task& task, int32_t delayTime, const std::string& name)
{
    PostDelayedTask(task, TaskExecutor::TaskType::UI, delayTime, name);
}

void FormTaskExecutor::PostDelayedTask(const TaskExecutor::Task& task, TaskExecutor::TaskType type,
    int32_t delayTime, const std::string& name)
{
    auto taskExecutor = GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(task, type, delayTime, name, GetFormTaskPriority());
}

bool FormTaskExecutor::PostSyncUITask(const TaskExecutor::Task& task, const std::string& name)
{
    auto taskExecutor = GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    return taskExecutor->PostSyncTask(task, TaskExecutor::TaskType::UI, name);
}

void FormTaskExecutor::RemoveUITask(const std::string& name)
{
    auto taskExecutor = GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->RemoveTask(TaskExecutor::TaskType::UI, name);
}

bool FormTaskExecutor::IsRunOnUIThread() const
{
    auto taskExecutor = GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    return taskExecutor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI);
}


} // namespace OHOS::Ace::NG
