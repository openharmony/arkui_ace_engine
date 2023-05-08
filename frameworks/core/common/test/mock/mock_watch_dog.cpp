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

#include <queue>
#include <shared_mutex>

#include "base/memory/ace_type.h"
#include "core/common/watch_dog.h"
#include "base/thread/task_executor.h"
#include "base/test/mock/mock_task_executor.h"

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

ThreadWatcher::ThreadWatcher(int32_t instanceId, TaskExecutor::TaskType type, bool useUIAsJSThread)
    : instanceId_(instanceId), type_(type), useUIAsJSThread_(useUIAsJSThread)
{
    {
        std::unique_lock<std::shared_mutex> lock(mutex_);
    }
    instanceId_ = 0;
    type_ = TaskExecutor::TaskType::JS;
    threadName_ = "JS";
    loopTime_ = 0;
    threadTag_ = 0;
    lastLoopTime_ = 0;
    lastThreadTag_ = 0;
    freezeCount_ = 0;
    lastTaskId_ = -1;
    state_ = State::NORMAL;
    taskExecutor_ = AceType::WeakClaim<MockTaskExecutor>(new MockTaskExecutor());
    canShowDialog_ = true;
    showDialogCount_ = 0;
    useUIAsJSThread_ = false;
}

ThreadWatcher::~ThreadWatcher() {}

void ThreadWatcher::SetTaskExecutor(const RefPtr<TaskExecutor>& taskExecutor) {}

void ThreadWatcher::BuriedBomb(uint64_t bombId) {}

void ThreadWatcher::DefusingBomb() {}

void ThreadWatcher::DefusingTopBomb() {}

void ThreadWatcher::InitThreadName() {}

void ThreadWatcher::DetonatedBomb() {}

void ThreadWatcher::Check() {}

void ThreadWatcher::CheckAndResetIfNeeded() {}

bool ThreadWatcher::IsThreadStuck()
{
    bool res = false;
    return res;
}

void ThreadWatcher::HiviewReport() const {}

void ThreadWatcher::RawReport(RawEventType type) const {}

void ThreadWatcher::ShowDialog() const {}

void ThreadWatcher::PostCheckTask() {}

void ThreadWatcher::TagIncrease() {}

WatchDog::WatchDog() {}

WatchDog::~WatchDog() {}

void WatchDog::Register(int32_t instanceId, const RefPtr<TaskExecutor>& taskExecutor, bool useUIAsJSThread) {}

void WatchDog::Unregister(int32_t instanceId) {}

void WatchDog::BuriedBomb(int32_t instanceId, uint64_t bombId) {}

void WatchDog::DefusingBomb(int32_t instanceId) {}
} // namespace OHOS::Ace
