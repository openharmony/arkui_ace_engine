/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_COMMON_UPDATE_CONFIG_MANAGER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_COMMON_UPDATE_CONFIG_MANAGER_H

#include <mutex>
#include <string>
#include <thread>

#include "base/memory/ace_type.h"
#include "base/thread/cancelable_callback.h"
#include "base/thread/task_executor.h"
#include "core/common/container.h"

namespace OHOS::Ace {
template<class T>
class UpdateConfigManager : public virtual AceType {
    DECLARE_ACE_TYPE(UpdateConfigManager<T>, AceType);
public:
    struct UpdateTask {
        CancelableCallback<void()> updateTask;
        T target;
    };

    void UpdateConfig(const T& config, const RefPtr<Container>& container, std::function<void()> &&task,
        const std::string& taskName)
    {
        auto cancelableTask = CancelableCallback<void()>([config, task, weakMgr = WeakClaim(this)] () {
            task();
            auto configManager = weakMgr.Upgrade();
            CHECK_NULL_VOID(configManager);
            configManager->OnUpdateTaskDone(config);
        });

        std::lock_guard<std::mutex> taskLock(updateTaskMutex_);
        if (config == currentConfig_ || config == currentTask_.target) {
            return;
        } else {
            // Try to cancel useless task.
            CancelUselessTaskLocked();
            // Post new task.
            PostUpdateConfigTaskLocked(config, container, std::move(cancelableTask), taskName);
        }
    }

private:
    void PostUpdateConfigTaskLocked(const T& config, const RefPtr<Container>& container,
        CancelableCallback<void()> &&task, const std::string& taskName)
    {
        currentTask_ = {
            .target = config,
            .updateTask = std::move(task),
        };
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(currentTask_.updateTask, TaskExecutor::TaskType::PLATFORM, taskName);
    }

    void CancelUselessTaskLocked()
    {
        currentTask_.updateTask.Cancel();
    }

    void OnUpdateTaskDone(const T& config)
    {
        std::lock_guard<std::mutex> tasksLock(updateTaskMutex_);
        currentConfig_ = config;
    }

    std::mutex updateTaskMutex_;

    T currentConfig_;

    UpdateTask currentTask_;
};
} // OHOS::Ace
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_COMMON_UPDATE_CONFIG_MANAGER_H
