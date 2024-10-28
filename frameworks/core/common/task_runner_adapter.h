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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMMON_TASK_RUNNER_ADAPTER_H
#define FOUNDATION_ACE_FRAMEWORKS_COMMON_TASK_RUNNER_ADAPTER_H

#include <functional>
#include <string>

#include "base/memory/ace_type.h"
#include "base/thread/task_executor.h"

namespace OHOS::Ace {
class TaskRunnerAdapter : public virtual AceType {
    DECLARE_ACE_TYPE(TaskRunnerAdapter, AceType);

public:
    TaskRunnerAdapter() = default;
    ~TaskRunnerAdapter() override = default;

    virtual void PostTask(
        std::function<void()> task, const std::string& name, PriorityType priorityType = PriorityType::LOW)
    {}
    virtual void PostTaskForTime(std::function<void()> task, uint32_t targetTime, const std::string& caller) {}
    virtual void PostDelayedTask(std::function<void()> task, uint32_t delay, const std::string& name,
        PriorityType priorityType = PriorityType::LOW)
    {}
    virtual bool RunsTasksOnCurrentThread() = 0;
    virtual void Initialize(bool useCurrentEventRunner = false, const std::string& name = "") {}
    virtual void RemoveTask(const std::string &name) {}
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_COMMON_TASK_RUNNER_ADAPTER_H
