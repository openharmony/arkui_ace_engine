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

#include "base/watch_dog/watch_dog.h"

#include "base/log/event_report.h"
#include "base/log/log.h"

namespace OHOS::Ace {
namespace {

const int32_t WAIT_SECOND = 10;

} // namespace

WatchDog::WatchDog()
{
    checkThread_ = std::thread(&WatchDog::CheckLoop, this);
}

WatchDog::~WatchDog()
{
    sleeper_.Interrupt();
    if (checkThread_.joinable()) {
        checkThread_.join();
    }
}

void WatchDog::CheckLoop()
{
    while (!sleeper_.WaitFor(std::chrono::seconds(WAIT_SECOND))) {
        CheckStuckThread();
        CheckAndResetIfNeeded();

        mutex_.lock();
        for (auto iter = taskExecutorMap_.begin(); iter != taskExecutorMap_.end();) {
            auto taskExecutor = iter->second.Upgrade();
            if (taskExecutor) {
                // send task to UI thread for checking it
                taskExecutor->PostTask(
                    [instanceId = iter->first, weak = Referenced::WeakClaim(this)]() {
                        auto me = weak.Upgrade();
                        if (me) {
                            me->TriggerThreadTagIncrease(instanceId, TaskExecutor::TaskType::UI);
                        }
                    },
                    TaskExecutor::TaskType::UI);

                // send task to JS thread for checking it
                taskExecutor->PostTask(
                    [instanceId = iter->first, weak = Referenced::WeakClaim(this)]() {
                        auto me = weak.Upgrade();
                        if (me) {
                            me->TriggerThreadTagIncrease(instanceId, TaskExecutor::TaskType::JS);
                        }
                    },
                    TaskExecutor::TaskType::JS);

                ++iter;
            } else {
                int32_t num = threadTagMap_.erase(iter->first);
                if (num == 0) {
                    LOGW("find no item in threadTagMap_ with instanceID %{public}d when delete it from this map\n",
                        iter->first);
                }
                iter = taskExecutorMap_.erase(iter);
            }
        }
        loopTime_++;
        mutex_.unlock();
    }
}

void WatchDog::RegisterTaskExecutor(int32_t instanceId, const RefPtr<TaskExecutor>& taskExecutor)
{
    std::lock_guard<std::mutex> lock(mutex_);
    const auto resExecutor = taskExecutorMap_.try_emplace(instanceId, taskExecutor);
    if (!resExecutor.second) {
        LOGW("taskExecutor with instance id: %{public}d has been registered, and not effected", instanceId);
    }

    std::unordered_map<TaskExecutor::TaskType, int32_t> tagMap = { { TaskExecutor::TaskType::UI, loopTime_ },
        { TaskExecutor::TaskType::JS, loopTime_ } };
    const auto resThreadTag = threadTagMap_.try_emplace(instanceId, tagMap);
    if (!resThreadTag.second) {
        LOGW(
            "taskExecutor with instanceId: %{public}d inserted to threadTagMap_ repeats, it's not normal.", instanceId);
    }
}

void WatchDog::TriggerThreadTagIncrease(int32_t instanceId, TaskExecutor::TaskType type)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto tagMap = threadTagMap_.find(instanceId);
    if (tagMap == threadTagMap_.end()) {
        LOGW("no item with instanceId %{public}d in map", instanceId);
        return;
    }

    int32_t val = tagMap->second.at(type);
    tagMap->second.at(type) = ++val;
}

void WatchDog::CheckAndResetIfNeeded()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (loopTime_ < INT32_MAX) {
        return;
    }

    loopTime_ = 0;

    if (threadTagMap_.empty()) {
        return;
    }

    for (auto& iter : threadTagMap_) {
        iter.second.at(TaskExecutor::TaskType::UI) = loopTime_;
        iter.second.at(TaskExecutor::TaskType::JS) = loopTime_;
    }
}

void WatchDog::CheckStuckThread()
{
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto& iter : threadTagMap_) {
        for (auto& iterThread : iter.second) {
            if (iterThread.second == loopTime_) {
                continue;
            }
            LOGW("thread stuck, container instanceId: %{public}d, threadId: %{public}d", iter.first,
                iterThread.first);
            if (iterThread.first == TaskExecutor::TaskType::JS) {
                EventInfo eventInfo;
                eventInfo.eventType = EXCEPTION_JS_RUNTIME;
                eventInfo.errorType = JS_THREAD_STUCK;
                EventReport::SendEvent(eventInfo);
            } else if (iterThread.first == TaskExecutor::TaskType::UI) {
                EventInfo eventInfo;
                eventInfo.eventType = EXCEPTION_RENDER;
                eventInfo.errorType = UI_THREAD_STUCK;
                EventReport::SendEvent(eventInfo);
            }
        }
    }
}

} // namespace OHOS::Ace