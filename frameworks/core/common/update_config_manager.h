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
        std::unordered_map<int32_t, CancelableCallback<void()>> promiseTaskMap;
        T target;
    };

    void UpdateConfigSync(const T& config, std::function<void()> &&task)
    {
        // Update current state
        {
            std::lock_guard<std::mutex> taskLock(updateTaskMutex_);
            currentTask_.updateTask.Cancel();
            currentTask_.target = config;
        }

        task();
    }

    void UpdateViewConfigTaskDone(int32_t taskId)
    {
        std::lock_guard<std::mutex> taskLock(updateTaskMutex_);
        currentTask_.promiseTaskMap.erase(taskId);
    }

    void CancelAllPromiseTaskLocked()
    {
        std::lock_guard<std::mutex> taskLock(updateTaskMutex_);
        for (auto it = currentTask_.promiseTaskMap.begin(); it != currentTask_.promiseTaskMap.end();) {
            it = it->second.Cancel() ? currentTask_.promiseTaskMap.erase(it) : ++it;
        }
    }

    void CancelUselessTaskLocked()
    {
        currentTask_.updateTask.Cancel();
    }

    void UpdatePromiseConfig(const T& config, std::function<void()> &&task, const RefPtr<Container>& container,
        int32_t taskId, const std::string& taskName, TaskExecutor::TaskType type = TaskExecutor::TaskType::PLATFORM)
    {
        std::lock_guard<std::mutex> taskLock(updateTaskMutex_);
        CancelUselessTaskLocked();
        CancelableCallback<void()> promiseTask(std::move(task));
        currentTask_.promiseTaskMap[taskId] = promiseTask;
        currentTask_.target = config;

        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(std::move(promiseTask), type, taskName);
    }

    void UpdateConfig(const T& config, std::function<void()> &&task, const RefPtr<Container>& container,
        const std::string& taskName, TaskExecutor::TaskType type = TaskExecutor::TaskType::PLATFORM)
    {
        CancelableCallback<void()> cancelableTask(std::move(task));

        std::lock_guard<std::mutex> taskLock(updateTaskMutex_);
        if (config == currentTask_.target) {
            // If config is same as current/next state, return directely.
            return;
        } else {
            // Try to cancel useless task.
            CancelUselessTaskLocked();
            // Post new task.
            PostUpdateConfigTaskLocked(config, std::move(cancelableTask), container, taskName, type);
        }
    }

    void StoreConfig(T& config)
    {
        aceConfig_ = config;
    }

    bool IsConfigsEqual(const ViewportConfig& other)
    {
        return aceConfig_.config_ == other;
    }

    int32_t MakeTaskId()
    {
        return nextTaskId_.fetch_add(1);
    }
private:
    void PostUpdateConfigTaskLocked(const T& config, CancelableCallback<void()> &&task,
        const RefPtr<Container>& container, const std::string& taskName, TaskExecutor::TaskType type)
    {
        currentTask_ = {
            .updateTask = std::move(task),
            .target = config,
        };
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(currentTask_.updateTask, type, taskName);
    }

    std::mutex updateTaskMutex_;

    UpdateTask currentTask_;

    std::atomic<int32_t> nextTaskId_ = 0;

    T aceConfig_;
};
} // OHOS::Ace
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_COMMON_UPDATE_CONFIG_MANAGER_H
