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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WATCH_DOG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WATCH_DOG_H

#include <atomic>
#include <unordered_map>

#include "base/thread/task_executor.h"

namespace OHOS::Ace {

class InterruptibleSleeper {
public:
    template<typename R, typename P>
    bool WaitFor(std::chrono::duration<R, P> const & time)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        return cv_.wait_for(lock, time, [&] { return terminate_; });
    }

    void Interrupt()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        terminate_ = true;
        cv_.notify_all();
    }

private:
    std::condition_variable cv_;
    std::mutex mutex_;
    bool terminate_ = false;
};

class WatchDog : public Referenced {
public:
    WatchDog();
    ~WatchDog();

    void RegisterTaskExecutor(int32_t instanceId, const RefPtr<TaskExecutor>& taskExecutor);
    void TriggerThreadTagIncrease(int32_t instanceId, TaskExecutor::TaskType type);

private:
    void CheckAndResetIfNeeded();
    void CheckStuckThread();
    void CheckLoop();

    std::thread checkThread_;
    int32_t loopTime_ = 0;
    std::mutex mutex_;
    std::unordered_map<int32_t, WeakPtr<TaskExecutor>> taskExecutorMap_;
    std::unordered_map<int32_t, std::unordered_map<TaskExecutor::TaskType, int32_t>> threadTagMap_;
    InterruptibleSleeper sleeper_;

    ACE_DISALLOW_COPY_AND_MOVE(WatchDog);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WATCH_DOG_H
