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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ROSEN_ROSEN_TASK_EXECUTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ROSEN_ROSEN_TASK_EXECUTOR_H

#include <condition_variable>
#include <map>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include <uv.h>

#include "base/thread/task_executor.h"
#include "base/utils/macros.h"

namespace OHOS::Ace {

class Semaphore {
public:
    void Active();
    void WaitingActive();

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    bool valid_ = false;
};

template<class T>
class SemQueue {
public:
    void PopFront(T &t)
    {
        std::unique_lock lock(mutex_);
        if (queue_.empty()) {
            const auto &func = [this]() {
                return !queue_.empty();
            };
            cv_.wait(lock, func);
        }
        t = queue_.front();
        queue_.pop();
    }

    void Push(const T &t)
    {
        std::unique_lock lock(mutex_);
        queue_.push(std::move(t));
        cv_.notify_all();
    }

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
};

class ACE_EXPORT RSTaskExecutor final : public TaskExecutor {
    DECLARE_ACE_TYPE(RSTaskExecutor, TaskExecutor);

public:
    RSTaskExecutor();
    ~RSTaskExecutor() override;
    void InitPlatformThread(bool useCurrentEventRunner = false);
    void InitJsThread(bool newThread = true);

    void AddTaskObserver(Task&& callback) override;
    void RemoveTaskObserver() override;
    bool WillRunOnCurrentThread(TaskType type) const final;

private:
    bool OnPostTask(Task&& task, TaskType type, uint32_t delayTime) const final;
    Task WrapTaskWithTraceId(Task&& task, int32_t id) const final;
    int32_t PostDelayTask(const Task &task, const TaskType &tasktype, int32_t timeoutMs);
    void RSTaskExecutorMain();
    void TaskMain(const TaskType &tasktype);
    void StartIdleIfNeed();
    static inline int64_t GetNow();
    static void OnTimer(uv_timer_t *timer);
    static void OnIdle(uv_idle_t *idle);
    static void OnSignal(uv_signal_t *signal, int32_t signum);

    struct TaskThread {
        SemQueue<Task> runningTasks;
        std::unique_ptr<std::thread> thread = nullptr;

        // waitingTasks Props
        std::mutex waitingMutex;
        std::map<int64_t, std::vector<Task>> waitingTasks;
        int64_t waitingTime = 0;
        uv_timer_t waitingTimer = { .data = nullptr };
        RSTaskExecutor *executor = nullptr;
    };

    uv_loop_t loop_ = {.data = this};
    uv_signal_t signal_ = {.data = this};
    uv_idle_t idle_ = {.data = this};
    std::map<uint32_t, struct TaskThread> threads_;
    Semaphore sem_;
    std::unique_ptr<std::thread> mainThread_ = nullptr;
    std::vector<Task> callbacks_;
    bool jsNewThread_ = true;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ROSEN_ROSEN_TASK_EXECUTOR_H
