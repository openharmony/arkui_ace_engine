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

#include "base/thread/task_executor.h"

#include <chrono>

#include "base/utils/system_properties.h"

namespace OHOS::Ace {

bool TaskExecutor::PostDelayedTask(
    Task&& task, TaskType type, uint32_t delayTime, const std::string& name, PriorityType priorityType) const
{
    if (delayTime > 0 && type == TaskType::BACKGROUND) {
        return false;
    }
    return OnPostTask(std::move(task), type, delayTime, name, priorityType);
}

bool TaskExecutor::PostSyncTask(Task&& task, TaskType type, const std::string& name, PriorityType priorityType) const
{
    if (!task || type == TaskType::BACKGROUND) {
        return false;
    } else if (WillRunOnCurrentThread(type)) {
        task();
        return true;
    }
    return PostTaskAndWait(CancelableTask(std::move(task)), type, name, 0ms, priorityType);
}

bool TaskExecutor::PostSyncTaskTimeout(
    const Task& task, TaskType type, uint32_t timeoutMs, const std::string& name) const
{
    if (!task || type == TaskType::BACKGROUND) {
        return false;
    } else if (WillRunOnCurrentThread(type)) {
        task();
        return true;
    }
    return PostTaskAndWait(CancelableTask(std::move(task)), type, name, std::chrono::milliseconds(timeoutMs));
}

bool TaskExecutor::PostSyncTask(CancelableTask&& task, TaskType type, const std::string& name) const
{
    if (!task || type == TaskType::BACKGROUND) {
        return false;
    } else if (WillRunOnCurrentThread(type)) {
        CancelableTask avatar(task);
        task();
        return avatar.WaitUntilComplete();
    }
    return PostTaskAndWait(std::move(task), type, name, 0ms);
}

bool TaskExecutor::PostDelayedTaskWithoutTraceId(
    Task&& task, TaskType type, uint32_t delayTime, const std::string& name, PriorityType priorityType) const
{
    if (delayTime > 0 && type == TaskType::BACKGROUND) {
        return false;
    }
    return OnPostTaskWithoutTraceId(std::move(task), type, delayTime, name, priorityType);
}

PriorityType TaskExecutor::GetPriorityTypeWithCheck(PriorityType priorityType, PriorityType defaultPriority)
{
    // Temporary interface, used to control whether priority adjustment takes effect.
    return SystemProperties::GetTaskPriorityAdjustmentEnable() ? priorityType : defaultPriority;
}

bool TaskExecutor::PostTaskAndWait(CancelableTask&& task, TaskType type, const std::string& name,
    std::chrono::milliseconds timeoutMs, PriorityType priorityType) const
{
#ifdef ACE_DEBUG
    bool result = false;
    if (OnPreSyncTask(type)) {
        result = OnPostTask(Task(task), type, 0, name, priorityType) && task.WaitUntilComplete(timeoutMs);
        OnPostSyncTask();
    }
    return result;
#else
    return OnPostTask(Task(task), type, 0, name, priorityType) && task.WaitUntilComplete(timeoutMs);
#endif
}

} // namespace OHOS::Ace
