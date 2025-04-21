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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMMON_TASK_RUNNERS_H
#define FOUNDATION_ACE_FRAMEWORKS_COMMON_TASK_RUNNERS_H

#include <string>

#include "core/common/task_runner_adapter.h"

namespace OHOS::Ace {
class TaskRunners {
public:
    TaskRunners(const std::string& label, const RefPtr<TaskRunnerAdapter>& platform,
        const RefPtr<TaskRunnerAdapter>& gpu, const RefPtr<TaskRunnerAdapter>& ui, const RefPtr<TaskRunnerAdapter>& io);
    TaskRunners(const TaskRunners& other) = default;
    ~TaskRunners() = default;

    RefPtr<TaskRunnerAdapter> GetPlatformTaskRunner() const;
    RefPtr<TaskRunnerAdapter> GetUITaskRunner() const;
    RefPtr<TaskRunnerAdapter> GetIOTaskRunner() const;
    RefPtr<TaskRunnerAdapter> GetGPUTaskRunner() const;
    const std::string& GetLabel() const;
    bool IsValid() const;

private:
    const std::string label_;
    RefPtr<TaskRunnerAdapter> platform_;
    RefPtr<TaskRunnerAdapter> gpu_;
    RefPtr<TaskRunnerAdapter> ui_;
    RefPtr<TaskRunnerAdapter> io_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_COMMON_TASK_RUNNERS_H
