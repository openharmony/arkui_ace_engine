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

#include "rosen_task_executor.h"

#include <cstring>

#include "base/log/log.h"
#include "core/common/container_scope.h"

#define _UVERR(call, err) LOGE("%s failed because %s", call, uv_strerror(err))
#define UVERR(call, err) { if (err) { _UVERR(call, err); } }
#define UVERRRET(call, err) { if (err) { _UVERR(call, err); return; } }
#define UVERRRETVAL(call, err) { if (err) { _UVERR(call, err); return err; } }
#define UVCALL(call, ...) { if (auto err = call(__VA_ARGS__)) { UVERR(#call, err); } }
#define UVCALLRET(call, ...) { if (auto err = call(__VA_ARGS__)) { UVERRRET(#call, err); } }
#define UVCALLRETVAL(call, ...) { if (auto err = call(__VA_ARGS__)) { UVERRRETVAL(#call, err); } }

#ifdef DEBUG_RS_TASK_EXECUTOR
#define DEBUGLOG(fmt, ...) LOGD("rste" fmt, ##__VA_ARGS__)
#else
#define DEBUGLOG(...)
#endif

namespace OHOS::Ace {
void Semaphore::Active()
{
    std::unique_lock<std::mutex> lock(mutex_);
    valid_ = true;
    cv_.notify_all();
}

void Semaphore::WaitingActive()
{
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this] { return valid_; });
    valid_ = false;
}

RSTaskExecutor::RSTaskExecutor()
{
    UVCALLRET(uv_loop_init, &loop_);
    UVCALLRET(uv_idle_init, &loop_, &idle_);
    mainThread_ = std::make_unique<std::thread>(
        std::bind(&RSTaskExecutor::RSTaskExecutorMain, this));
}

RSTaskExecutor::~RSTaskExecutor()
{
    for (auto &[_, taskThread] : threads_) {
        UVCALL(uv_timer_stop, &taskThread.waitingTimer);
        taskThread.runningTasks.Push(nullptr);
    }
    UVCALL(uv_idle_stop, &idle_);
    UVCALL(uv_signal_stop, &signal_);

    uv_stop(&loop_);
    for (auto &[_, taskThread] : threads_) {
        taskThread.thread->join();
    }

    mainThread_->join();
}

void RSTaskExecutor::InitPlatformThread(bool useCurrentEventRunner)
{
    (void)useCurrentEventRunner;
}

void RSTaskExecutor::InitJsThread(bool newThread)
{
    jsNewThread_ = newThread;
}

void RSTaskExecutor::AddTaskObserver(Task&& callback)
{
    callbacks_.push_back(callback);
}

void RSTaskExecutor::RemoveTaskObserver()
{
    callbacks_.clear();
}

bool RSTaskExecutor::WillRunOnCurrentThread(TaskType type) const
{
    auto it = threads_.find(static_cast<uint32_t>(type));
    if (it == threads_.end()) {
        return true;
    }

    return std::this_thread::get_id() == it->second.thread->get_id();
}

bool RSTaskExecutor::OnPostTask(Task&& task, TaskType type, uint32_t delayTime) const
{
    if (type == TaskType::JS && jsNewThread_ == false) {
        type = TaskType::UI;
    }

    RSTaskExecutor *that = const_cast<RSTaskExecutor *>(this);
    auto &taskThread = that->threads_[static_cast<uint32_t>(type)];
    if (taskThread.thread == nullptr) {
        taskThread.thread = std::make_unique<std::thread>(
            std::bind(&RSTaskExecutor::TaskMain, that, type));
        if (taskThread.thread == nullptr) {
            LOGE("make_unique thread failed with %s", strerror(errno));
            return false;
        }
    }

    if (delayTime == 0) {
        taskThread.runningTasks.Push(task);
    } else {
        return that->PostDelayTask(task, type, delayTime);
    }

    return true;
}

RSTaskExecutor::Task RSTaskExecutor::WrapTaskWithTraceId(Task&& task, int32_t id) const
{
    auto wrappedTask = [originTask = std::move(task), id]() {
        ContainerScope scope(id);
        originTask();
    };
    return wrappedTask;
}

void RSTaskExecutor::RSTaskExecutorMain()
{
    UVCALLRET(uv_signal_init, &loop_, &signal_);
    UVCALLRET(uv_signal_start, &signal_, OnSignal, SIGINT);
    StartIdleIfNeed();
    UVCALLRET(uv_run, &loop_, UV_RUN_DEFAULT);
}

void RSTaskExecutor::TaskMain(const TaskType &tasktype)
{
    auto &taskThread = threads_[static_cast<uint32_t>(tasktype)];
    while (true) {
        Task task;
        taskThread.runningTasks.PopFront(task);
        if (task == nullptr) {
            break;
        }
        task();
        for (auto &callback : callbacks_) {
            callback();
        }
    }
}

void RSTaskExecutor::StartIdleIfNeed()
{
    for (auto &[id, thread] : threads_) {
        std::lock_guard lock(thread.waitingMutex);
        if (!thread.waitingTasks.empty()) {
            return;
        }
    }

    DEBUGLOG("goto Idle");
    UVCALL(uv_idle_start, &idle_, OnIdle);
}

int32_t RSTaskExecutor::PostDelayTask(const Task &task, const TaskType &tasktype, int32_t timeoutMs)
{
    auto targetMs = GetNow() + timeoutMs;
    auto &taskThread = threads_[static_cast<uint32_t>(tasktype)];
    std::lock_guard lock(taskThread.waitingMutex);
    auto nowMs = GetNow();
    if (targetMs <= nowMs) {
        taskThread.runningTasks.Push(task);
        return 0;
    }

    auto it = taskThread.waitingTasks.find(targetMs);
    if (it == taskThread.waitingTasks.end()) {
        if (taskThread.waitingTime == 0) {
            UVCALL(uv_timer_init, &loop_, &taskThread.waitingTimer);
            taskThread.waitingTimer.data = &taskThread;
            taskThread.executor = this;
        }

        bool needUpdate = taskThread.waitingTime > nowMs && taskThread.waitingTime > targetMs;
        needUpdate = needUpdate || taskThread.waitingTime < nowMs;
        if (needUpdate) {
            DEBUGLOG("Waiting task");
            taskThread.waitingTime = targetMs;
            UVCALL(uv_timer_start, &taskThread.waitingTimer, OnTimer, targetMs - nowMs, 0);
            sem_.Active();
        }
    }

    taskThread.waitingTasks[targetMs].push_back(task);
    return 0;
}

inline int64_t RSTaskExecutor::GetNow()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
}

void RSTaskExecutor::OnTimer(uv_timer_t *timer)
{
    DEBUGLOG("OnTimer");
    auto taskThread = reinterpret_cast<struct TaskThread *>(timer->data);
    {
        std::lock_guard lock(taskThread->waitingMutex);
        const auto &nowMs = GetNow();

        std::vector<int64_t> eraseTimes;
        for (const auto &[time, tasks] : taskThread->waitingTasks) {
            if (time > nowMs) {
                DEBUGLOG("Rewaiting %{public}dms", static_cast<int32_t>(time - nowMs));
                taskThread->waitingTime = time;
                UVCALL(uv_timer_start, timer, OnTimer, time - nowMs, 0);
                break;
            }

            DEBUGLOG("Moving %{public}d tasks", static_cast<int32_t>(tasks.size()));
            for (const auto &task : tasks) {
                taskThread->runningTasks.Push(task);
            }
            eraseTimes.push_back(time);
        }

        DEBUGLOG("Removing %{public}d times", static_cast<int32_t>(eraseTimes.size()));
        for (const auto &time : eraseTimes) {
            taskThread->waitingTasks.erase(time);
        }
    }

    taskThread->executor->StartIdleIfNeed();
}

void RSTaskExecutor::OnIdle(uv_idle_t *idle)
{
    auto &that = *reinterpret_cast<RSTaskExecutor *>(idle->data);

    DEBUGLOG("Enter Idle");
    that.sem_.WaitingActive();
    DEBUGLOG("Exit Idle");

    UVCALL(uv_idle_stop, idle);
}

void RSTaskExecutor::OnSignal(uv_signal_t *signal, int32_t signum)
{
    if (signum == SIGINT) {
        UVCALL(uv_signal_stop, signal);
    }
}
} // namespace OHOS::Ace
