/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "uv_task_wrapper_impl.h"

#include <queue>
#include <unordered_map>
 
#include "base/log/ace_trace.h"

#include "base/utils/time_util.h"
#include "core/common/container_scope.h"

namespace OHOS::Ace::NG {
// main thread
std::thread::id mainThreadId = std::this_thread::get_id();
// global high priority queue
std::unordered_map<pthread_t, std::unordered_map<PriorityType,
                            std::queue<TaskExecutor::Task>>> globalTaskPriorityQueue_;
static std::mutex queueMutex;
 
static bool IsMainThread()
{
    return std::this_thread::get_id() == mainThreadId;
}
 
// Enqueue high priority task
static void EnqueueUVPriorityTask(
    const TaskExecutor::Task& task, PriorityType priorityType, pthread_t targetThread)
{
    ACE_SCOPED_TRACE("EnqueueUVPriorityTask PriorityType [%d], targetThread[%lu]",
        static_cast<int32_t>(priorityType), static_cast<uint64_t>(targetThread));
    std::lock_guard<std::mutex> lock(queueMutex);
    globalTaskPriorityQueue_[targetThread][priorityType].push(task);
}
 
// Handle high priority tasks
static void PostTaskToUV(uv_loop_t* loop)
{
    auto curThread = pthread_self();
    std::unordered_map<PriorityType, std::queue<TaskExecutor::Task>> temp;
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        auto it = globalTaskPriorityQueue_.find(curThread);
        if (it == globalTaskPriorityQueue_.end()) {
            return;
        }
        if (it->second.empty()) {
            return;
        }
        for (auto it1 = globalTaskPriorityQueue_[curThread].begin();
            it1 != globalTaskPriorityQueue_[curThread].end(); it1++) {
            while (!it1->second.empty()) {
                auto value = it1->second.front();
                temp[it1->first].push(value);
                it1->second.pop();
            }
        }
    }
    if (temp.empty()) {
        return;
    }
    ACE_SCOPED_TRACE("PostTaskToUV curThread [%lu], curThreadSize [%zu]",
        static_cast<uint64_t>(curThread), temp.size());
    for (int32_t i = 0; i < static_cast<int32_t>(PriorityType::LOW); i++) {
        PriorityType priority = static_cast<PriorityType>(i);
        while (!temp[priority].empty()) {
            auto curTask = temp[priority].front();
            temp[priority].pop();
            auto work = std::make_shared<UVWorkWrapper>(curTask);
            if (work) {
                ACE_SCOPED_TRACE("PostHighPriorityTaskQueue PriorityType [%d]",
                    static_cast<int32_t>(priority));
                (*work)();
            }
        }
    }
}

UVTaskWrapperImpl::UVTaskWrapperImpl(napi_env env)
    :env_(env)
{
    if (env == nullptr) {
        LOGE("env is null");
        return;
    }
    auto engine = reinterpret_cast<NativeEngine*>(env);
    if (engine == nullptr) {
        LOGE("native engine is null");
        return;
    }
    threadId_ = engine->GetTid();
    auto uvLoop = engine->GetUVLoop();
    if (uvLoop && !IsMainThread()) {
        uv_register_task_to_worker(uvLoop, (uv_execute_specify_task)PostTaskToUV);
        uv_async_send(&uvLoop->wq_async);
    }
}

bool UVTaskWrapperImpl::WillRunOnCurrentThread()
{
    return pthread_self() == threadId_;
}

void UVTaskWrapperImpl::Call(
    const TaskExecutor::Task& task, PriorityType priorityType)
{
    if ((priorityType < PriorityType::LOW)) {
        auto engine = reinterpret_cast<NativeEngine*>(env_);
        if (engine == nullptr) {
            LOGE("native engine is null");
            return;
        }
 
        auto uvLoop = engine->GetUVLoop();
        EnqueueUVPriorityTask(task, priorityType, threadId_);
        if (uvLoop) {
            // send signal here to trigger uv tasks generated during initialization.
            uv_async_send(&uvLoop->wq_async);
        }
        return;
    }
    napi_send_event(env_, [work = std::make_shared<UVWorkWrapper>(task)] {
        ContainerScope scope(ContainerScope::CurrentLocalId());
        (*work)();
    }, napi_eprio_high);
}

void UVTaskWrapperImpl::Call(
    const TaskExecutor::Task& task, uint32_t delayTime, PriorityType priorityType)
{
    if (delayTime <= 0) {
        Call(task, priorityType);
        return;
    }

    auto callInWorkerTask = [task, delayTime, env = env_] () {
        UVTaskWrapperImpl::CallInWorker(task, delayTime, env);
    };

    Call(callInWorkerTask, priorityType);
}

void UVTaskWrapperImpl::CallInWorker(const TaskExecutor::Task& task, uint32_t delayTime, napi_env env)
{
    LOGD("CallInWorker delayTime: %{public}u", delayTime);
    uv_loop_t *loop = nullptr;
    napi_get_uv_event_loop(env, &loop);
    if (loop == nullptr) {
        LOGW("loop is null");
        return;
    }
    uv_update_time(loop);
    uv_timer_t *timer = new uv_timer_t;
    uv_timer_init(loop, timer);
    timer->data = new UVTimerWorkWrapper(task, delayTime, GetCurrentTimestamp());
    uv_timer_start(
        timer,
        [](uv_timer_t *timer) {
            UVTimerWorkWrapper* workWrapper = reinterpret_cast<UVTimerWorkWrapper*>(timer->data);
            if (workWrapper) {
                LOGD("Start work delayTime: %{public}u, taskTime: %{public}" PRId64 ", curTime: %{public}" PRId64,
                    workWrapper->GetDelayTime(), workWrapper->GetTaskTime(), GetCurrentTimestamp());
                (*workWrapper)();
                delete workWrapper;
            }
            uv_timer_stop(timer);
            uv_close(
                reinterpret_cast<uv_handle_t *>(timer),
                [](uv_handle_t *timer) {
                    delete reinterpret_cast<uv_timer_t *>(timer);
            });
        },
        delayTime, 0);
}
} // namespace OHOS::Ace::NG
