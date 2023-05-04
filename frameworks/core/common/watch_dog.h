/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include <shared_mutex>
#include <unordered_map>
#include <queue>

#include "base/thread/task_executor.h"
#include "base/utils/utils.h"
#include "base/log/event_report.h"
#include "base/log/log.h"

namespace OHOS::Ace {
namespace {

enum class State { NORMAL, WARNING, FREEZE };
}
class ThreadWatcher final : public Referenced {
public:
    ThreadWatcher(int32_t instanceId, TaskExecutor::TaskType type, bool useUIAsJSThread = false);
    ~ThreadWatcher() override;

    void SetTaskExecutor(const RefPtr<TaskExecutor>& taskExecutor);

    void BuriedBomb(uint64_t bombId);
    void DefusingBomb();

private:
    void InitThreadName();
    void CheckAndResetIfNeeded();
    bool IsThreadStuck();
    void HiviewReport() const;
    void RawReport(RawEventType type) const;
    void PostCheckTask();
    void TagIncrease();
    void Check();
    void ShowDialog() const;
    void DefusingTopBomb();
    void DetonatedBomb();

    mutable std::shared_mutex mutex_;
    int32_t instanceId_ = 0;
    TaskExecutor::TaskType type_;
    std::string threadName_;
    int32_t loopTime_ = 0;
    int32_t threadTag_ = 0;
    int32_t lastLoopTime_ = 0;
    int32_t lastThreadTag_ = 0;
    int32_t freezeCount_ = 0;
    int64_t lastTaskId_ = -1;
    State state_ = State::NORMAL;
    WeakPtr<TaskExecutor> taskExecutor_;
    std::queue<uint64_t> inputTaskIds_;
    bool canShowDialog_ = true;
    int32_t showDialogCount_ = 0;
    bool useUIAsJSThread_ = false;
};

struct Watchers {
    RefPtr<ThreadWatcher> jsWatcher;
    RefPtr<ThreadWatcher> uiWatcher;
};

class WatchDog final : public Referenced {
public:
    WatchDog();
    ~WatchDog() override;

    void Register(int32_t instanceId, const RefPtr<TaskExecutor>& taskExecutor, bool useUIAsJSThread);
    void Unregister(int32_t instanceId);
    void BuriedBomb(int32_t instanceId, uint64_t bombId);
    void DefusingBomb(int32_t instanceId);

private:
    std::unordered_map<int32_t, Watchers> watchMap_;

    ACE_DISALLOW_COPY_AND_MOVE(WatchDog);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WATCH_DOG_H
