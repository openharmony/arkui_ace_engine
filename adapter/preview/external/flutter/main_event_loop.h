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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_EVENT_LOOP_MAIN_EVENT_LOOP_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_EVENT_LOOP_MAIN_EVENT_LOOP_H

#include <condition_variable>
#include <mutex>
#include <thread>

#include "flutter/fml/delayed_task.h"

namespace flutter {
class MainEventLoop {
public:
    static MainEventLoop& GetInstance();
    ~MainEventLoop();
    // Determine whether the thread that post the task is the same as the thread where the event loop is located.
    bool RunsTasksOnCurrentThread() const;
    // Post a tasks to the event loop.
    void PostTask(fml::closure task, fml::TimePoint targetTime);
    // Execute all tasks in the task queue
    void Run();

private:
    MainEventLoop(std::thread::id mainThreadId);
    MainEventLoop(const MainEventLoop&) = delete;
    MainEventLoop& operator=(const MainEventLoop&) = delete;
    std::thread::id mainThreadId_;
    std::mutex taskQueueMutex_;
    fml::DelayedTaskQueue taskQueue_;
};

} // namespace flutter

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_EVENT_LOOP_MAIN_EVENT_LOOP_H
