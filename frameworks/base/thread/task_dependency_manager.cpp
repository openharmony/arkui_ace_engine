/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "base/thread/background_task_executor.h"
#include "base/thread/task_dependency_manager.h"
#include "base/utils/utils.h"

#include "base/utils/system_properties.h"

namespace OHOS::Ace {
std::mutex g_mutexTaskDependencyManager;
RefPtr<TaskDependencyManager> TaskDependencyManager::instance_ = nullptr;

void TaskDependencyManager::PostTaskToBg(std::function<void()>&& task, const std::string& taskName,
    std::function<void(TaskDependencyManager::ErrorCode, std::function<void()>&&,
        const std::string&)>&& errorHandler)
{
    if (!SystemProperties::GetAsyncInitializeEnabled()) {
        task();
        return;
    }
    std::shared_ptr<std::packaged_task<void()>> package = std::make_shared<std::packaged_task<void()>>(task);
    if (taskName == "") {
        errorHandler(TaskDependencyManager::ErrorCode::TASK_ERROR_KEY_ILLEGAL,
            [package] () { (*package)(); },
            taskName);
        return;
    }
    auto wrappedTask = [package, taskName, weak = WeakClaim(this)] () {
        (*package)();
        auto manager = weak.Upgrade();
        CHECK_NULL_VOID(manager);
        manager->Delete(taskName);
    };
    bool result;
    lock_.lock();
    if (futures_.find(taskName) != futures_.end()) {
        result = false;
    } else {
        result = true;
        futures_.emplace(taskName, std::make_shared<std::future<void>>(package->get_future()));
    }
    lock_.unlock();
    if (result) {
        BackgroundTaskExecutor::GetInstance().PostTask(std::move(wrappedTask));
    } else {
        errorHandler(TaskDependencyManager::ErrorCode::TASK_ERROR_KEY_CONFLICT,
            [package] () { (*package)(); },
            taskName);
    }
}

void TaskDependencyManager::Wait(const std::string& dependencyName,
    std::function<void(TaskDependencyManager::ErrorCode, const std::string&)>&& errorHandler)
{
    if (!SystemProperties::GetAsyncInitializeEnabled()) {
        return;
    }
    bool result;
    std::shared_ptr<std::future<void>> future;
    lock_.lock();
    if (futures_.find(dependencyName) != futures_.end()) {
        result = true;
        future = futures_[dependencyName];
    } else {
        result = false;
    }
    lock_.unlock();
    if (result) {
        future->wait();
    } else {
        errorHandler(
            TaskDependencyManager::ErrorCode::TASK_ERROR_UNRECORDED_DEPENDENCY,
            dependencyName);
    }
}

void TaskDependencyManager::Sync()
{
    if (!SystemProperties::GetAsyncInitializeEnabled()) {
        return;
    }
    std::shared_ptr<std::future<void>> future;
    bool breakFlag = false;
    while (!breakFlag) {
        lock_.lock();
        if (futures_.size() > 0) {
            future = std::shared_ptr<std::future<void>>(futures_.begin()->second);
        } else {
            breakFlag = true;
        }
        lock_.unlock();
        if (breakFlag) {
            break;
        }
        future->wait();
    }
}

RefPtr<TaskDependencyManager> TaskDependencyManager::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(g_mutexTaskDependencyManager);
        if (!instance_) {
            instance_ = MakeRefPtr<TaskDependencyManager>();
        }
    }
    return instance_;
}

void TaskDependencyManager::Delete(const std::string& taskName)
{
    if (!SystemProperties::GetAsyncInitializeEnabled()) {
        return;
    }
    lock_.lock();
    if (futures_.find(taskName) != futures_.end()) {
        futures_.erase(taskName);
    }
    lock_.unlock();
}
} //OHOS::Ace
