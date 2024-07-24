/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#include "component_test/idle_watcher.h"

#include "component_test/component_test_manager_impl.h"

#include "base/log/log.h"
#include "base/thread/task_executor.h"
#include "core/common/task_runner_adapter.h"
#include "core/common/task_runner_adapter_factory.h"

namespace OHOS::Ace::ComponentTest {

constexpr uint32_t period = 2000 / 4;
constexpr uint32_t delay_next_check = 1000 / 4;
constexpr uint32_t delay_double_confirm = 2000 / 4;
constexpr uint32_t delay_after_change = 5000 / 4;

constexpr uint8_t max_idle_check_retry = 10;

void UpdatePipelineStatus()
{
    ComponentTestManagerImpl::Get()->pipelineStatusHolder.Update();
}

void IdleMonitorThread::VsyncCountFirstCheck()
{
    if (ComponentTestManagerImpl::Get()->pipelineStatusHolder.Check()) {
        PostCheckTask([this]() { VsyncCountSecondCheck(); }, delay_double_confirm);
    } else {
        if (ComponentTestManagerImpl::Get()->pipelineStatusHolder.RetryCounterReached(max_idle_check_retry)) {
            LOGI("IdleMonitorThread wait pipeline idle timeout");
            ComponentTestManagerImpl::Get()->pipelineStatusHolder.RetryCounterClear();
            callback_();
        }
        PostCheckTask([this]() { VsyncCountFirstCheck(); }, delay_next_check);
    }
}

void IdleMonitorThread::VsyncCountSecondCheck()
{
    if (ComponentTestManagerImpl::Get()->pipelineStatusHolder.Check()) {
        ComponentTestManagerImpl::Get()->pipelineStatusHolder.RetryCounterClear();
        callback_();
        IdleMonitorThread::PostCheckTask([this]() { VsyncCountFirstCheck(); }, period);
    } else {
        IdleMonitorThread::PostCheckTask([this]() { VsyncCountFirstCheck(); }, delay_after_change);
    }
}

RefPtr<IdleMonitorThread> IdleMonitorThread::Create()
{
    auto idleMonitorThread = MakeRefPtr<IdleMonitorThread>();
    idleMonitorThread->thread = TaskRunnerAdapterFactory::Create(false, "IdleMonitorThread");
    return idleMonitorThread;
}

void IdleMonitorThread::Stop()
{
    thread.Reset();
}

void IdleMonitorThread::SetIdleNotifycallback(IdleNotifycallback callback)
{
    callback_ = callback;
}

void IdleMonitorThread::SetTaskExecutor(RefPtr<TaskExecutor> taskExecutor)
{
    taskExecutor_ = taskExecutor;
}

void IdleMonitorThread::PostInitializeTask()
{
    thread->PostDelayedTask([this]() { PostCheckTask([this]() { VsyncCountFirstCheck(); }, period); }, period, {});
}

void IdleMonitorThread::PostCheckTask(std::function<void()>&& task, uint32_t delay)
{
    thread->PostDelayedTask(std::move(task), delay, {});
}

IdleWatcher::IdleWatcher(RefPtr<TaskExecutor> taskExecutor)
{
    keepingIdle_ = false;
    idleMonitorThread_ = IdleMonitorThread::Create();
    idleMonitorThread_->SetIdleNotifycallback([this] { TriggerIdleNotification(); });
    idleMonitorThread_->SetTaskExecutor(taskExecutor);
    idleMonitorThread_->PostInitializeTask();
}

void IdleWatcher::Destroy()
{
    idleMonitorThread_->Stop();
    std::lock_guard<std::mutex> lock(observersMutex_);
    pendingIdleObservers_.clear();
}

void IdleWatcher::TriggerIdleNotification()
{
    LOGI("Triggering idle notification");
    keepingIdle_ = true;
    if (pendingIdleObservers_.empty()) {
        ComponentTestManagerImpl::Get()->pipelineStatusHolder.IdleCounterAdd();
        if (ComponentTestManagerImpl::Get()->pipelineStatusHolder.IdleCounterReached(CONTINUOUS_IDLE_TIME) &&
            continuousIdleCallback_) {
            continuousIdleCallback_();
            continuousIdleCallback_ = nullptr;
        }
    } else {
        std::lock_guard<std::mutex> lock(observersMutex_);
        for (IdleNotifycallback& notifycallback : pendingIdleObservers_) {
            notifycallback();
        }
        pendingIdleObservers_.clear();
    }
}

void IdleWatcher::RequestNextIdleStatusNotification(IdleNotifycallback&& notifycallback, bool haveUIChange)
{
    ComponentTestManagerImpl::Get()->pipelineStatusHolder.IdleCounterClear();
    if (haveUIChange) {
        notifycallback = [this, notifycallback]() {
            keepingIdle_ = false;
            notifycallback();
        };
    }
    if (keepingIdle_) {
        notifycallback();
    } else {
        std::lock_guard<std::mutex> lock(observersMutex_);
        pendingIdleObservers_.emplace_back(notifycallback);
    }
}

void IdleWatcher::RequestContinuousIdleStatusNotification(IdleNotifycallback&& continuousIdleCallback)
{
    continuousIdleCallback_ = std::move(continuousIdleCallback);
}

void IdleWatcher::ClaimLongOperation()
{
    ComponentTestManagerImpl::Get()->pipelineStatusHolder.IncreaseLongOpt();
}

void IdleWatcher::LongOperationComplete()
{
    ComponentTestManagerImpl::Get()->pipelineStatusHolder.DecreaseLongOpt();
}
} // namespace OHOS::Ace::ComponentTest
