/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_CPP_FAKE_TASK_EXECUTOR_H
#define FOUNDATION_ACE_ADAPTER_OHOS_CPP_FAKE_TASK_EXECUTOR_H

#include "base/thread/background_task_executor.h"
#include "base/thread/task_executor.h"

namespace OHOS::Ace {

class FakeTaskExecutor final : public TaskExecutor {
public:
    bool WillRunOnCurrentThread(TaskType type) const final
    {
        switch (type) {
            case TaskType::PLATFORM:
            case TaskType::UI:
            case TaskType::IO:
            case TaskType::GPU:
            case TaskType::JS:
                return false;
            case TaskType::BACKGROUND:
                // Always return false for background tasks.
                return false;
            default:
                return false;
        }
    }

    void AddTaskObserver(Task&& callback) {}
    void RemoveTaskObserver() {}

private:
    bool OnPostTask(Task&& task, TaskType type, uint32_t delayTime) const final
    {
        switch (type) {
            case TaskType::PLATFORM:
            case TaskType::UI:
            case TaskType::IO:
            case TaskType::GPU:
            case TaskType::JS:
                return false;
            case TaskType::BACKGROUND:
                // Ignore delay time
                return BackgroundTaskExecutor::GetInstance().PostTask(std::move(task));
            default:
                return false;
        }
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_CPP_FAKE_TASK_EXECUTOR_H
