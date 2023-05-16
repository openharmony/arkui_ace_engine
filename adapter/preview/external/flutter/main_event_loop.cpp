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

#include "adapter/preview/external/flutter/main_event_loop.h"

namespace flutter {

MainEventLoop& MainEventLoop::GetInstance()
{
    static MainEventLoop eventLoop(std::this_thread::get_id());
    return eventLoop;
}

MainEventLoop::MainEventLoop(std::thread::id mainThreadId) : mainThreadId_(mainThreadId) {}

MainEventLoop::~MainEventLoop() = default;

bool MainEventLoop::RunsTasksOnCurrentThread() const
{
    return std::this_thread::get_id() == mainThreadId_;
}

void MainEventLoop::Run()
{
    const auto now = fml::TimePoint::Now();
    std::vector<fml::closure> expiredTasks;

    // Process expired tasks.
    {
        std::lock_guard<std::mutex> lock(taskQueueMutex_);
        while (!taskQueue_.empty()) {
            const auto& top = taskQueue_.top();
            // If the task at the top of task queue has not yet expired, there is nothing more to do.
            if (top.GetTargetTime() > now) {
                break;
            }

            // Only record tasks without executing them when the task queue mutex is hold.
            expiredTasks.push_back(top.GetTask());
            taskQueue_.pop();
        }
    }

    {
        // Flushing tasks here without holing onto the task queue mutex.
        for (const auto& task : expiredTasks) {
            task();
        }
    }
}

void MainEventLoop::PostTask(fml::closure task, fml::TimePoint targetTime)
{
    static size_t globalTaskOrder = 0;
    std::lock_guard<std::mutex> lock(taskQueueMutex_);
    size_t order = globalTaskOrder++;
    taskQueue_.push({ order, std::move(task), targetTime });
}

} // namespace flutter
