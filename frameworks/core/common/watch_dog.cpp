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

#include "core/common/watch_dog.h"

#include <shared_mutex>

#include "flutter/fml/thread.h"

#include "base/log/event_report.h"
#include "base/log/log.h"
#include "frameworks/core/common/ace_engine.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t NORMAL_CHECK_PERIOD = 3;
constexpr int32_t WARNING_CHECK_PERIOD = 2;
constexpr int32_t FREEZE_CHECK_PERIOD = 1;
constexpr char JS_THREAD_NAME[] = "JS";
constexpr char UI_THREAD_NAME[] = "UI";
constexpr char UNKNOWN_THREAD_NAME[] = "unknown thread";

enum class State { NORMAL, WARNING, FREEZE };

using Task = std::function<void()>;
std::unique_ptr<fml::Thread> g_anrThread;

bool PostTaskToTaskRunner(Task&& task, uint32_t delayTime)
{
    if (!g_anrThread || !task) {
        return false;
    }

    auto anrTaskRunner = g_anrThread->GetTaskRunner();
    if (delayTime > 0) {
        anrTaskRunner->PostDelayedTask(std::move(task), fml::TimeDelta::FromSeconds(delayTime));
    } else {
        anrTaskRunner->PostTask(std::move(task));
    }
    return true;
}

} // namespace

class ThreadWatcher final : public Referenced {
public:
    ThreadWatcher(int32_t instanceId, TaskExecutor::TaskType type);
    ~ThreadWatcher() override;

    void SetTaskExecutor(const RefPtr<TaskExecutor>& taskExecutor);

private:
    void InitThreadName();
    void CheckAndResetIfNeeded();
    bool IsThreadStuck();
    void HiviewReport() const;
    void RawReport(RawEventType type) const;
    void PostCheckTask();
    void TagIncrease();
    void Check();

    mutable std::shared_mutex mutex_;
    int32_t instanceId_;
    TaskExecutor::TaskType type_;
    std::string threadName_;
    int32_t loopTime_ = 0;
    int32_t threadTag_ = 0;
    int32_t freezeCount_ = 0;
    State state_ = State::NORMAL;
    WeakPtr<TaskExecutor> taskExecutor_;
};

ThreadWatcher::ThreadWatcher(int32_t instanceId, TaskExecutor::TaskType type) : instanceId_(instanceId), type_(type)
{
    InitThreadName();
    PostTaskToTaskRunner(
        [weak = Referenced::WeakClaim(this)]() {
            auto sp = weak.Upgrade();
            if (sp) {
                sp->Check();
            }
        },
        NORMAL_CHECK_PERIOD);
}

ThreadWatcher::~ThreadWatcher() {}

void ThreadWatcher::SetTaskExecutor(const RefPtr<TaskExecutor>& taskExecutor)
{
    taskExecutor_ = taskExecutor;
}

void ThreadWatcher::InitThreadName()
{
    switch (type_) {
        case TaskExecutor::TaskType::JS:
            threadName_ = JS_THREAD_NAME;
            break;
        case TaskExecutor::TaskType::UI:
            threadName_ = UI_THREAD_NAME;
            break;
        default:
            threadName_ = UNKNOWN_THREAD_NAME;
            break;
    }
}

void ThreadWatcher::Check()
{
    int32_t period = NORMAL_CHECK_PERIOD;
    if (!IsThreadStuck()) {
        if (state_ == State::FREEZE) {
            RawReport(RawEventType::RECOVER);
        }
        freezeCount_ = 0;
        state_ = State::NORMAL;
    } else {
        if (state_ == State::NORMAL) {
            HiviewReport();
            RawReport(RawEventType::WARNING);
            state_ = State::WARNING;
            period = WARNING_CHECK_PERIOD;
        } else if (state_ == State::WARNING) {
            RawReport(RawEventType::FREEZE);
            state_ = State::FREEZE;
            period = FREEZE_CHECK_PERIOD;
        } else {
            if (++freezeCount_ >= 5) {
                RawReport(RawEventType::FREEZE);
                freezeCount_ = 0;
            }
            period = FREEZE_CHECK_PERIOD;
        }
    }

    PostTaskToTaskRunner(
        [weak = Referenced::WeakClaim(this)]() {
            auto sp = weak.Upgrade();
            if (sp) {
                sp->Check();
            }
        },
        period);
}

void ThreadWatcher::CheckAndResetIfNeeded()
{
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        if (loopTime_ < INT32_MAX) {
            return;
        }
    }

    std::unique_lock<std::shared_mutex> lock(mutex_);
    loopTime_ = 0;
    threadTag_ = 0;
}

bool ThreadWatcher::IsThreadStuck()
{
    bool res = false;
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        if (threadTag_ != loopTime_) {
            std::string abilityName;
            if (AceEngine::Get().GetContainer(instanceId_) != nullptr) {
                abilityName = AceEngine::Get().GetContainer(instanceId_)->GetHostClassName();
            }
            LOGE("thread stuck, ability: %{public}s, instanceId: %{public}d, thread: %{public}s", abilityName.c_str(),
                instanceId_, threadName_.c_str());
            res = true;
        }
    }
    CheckAndResetIfNeeded();
    PostCheckTask();
    return res;
}

void ThreadWatcher::HiviewReport() const
{
    if (type_ == TaskExecutor::TaskType::JS) {
        EventReport::SendJsException(JsExcepType::JS_THREAD_STUCK);
    } else if (type_ == TaskExecutor::TaskType::UI) {
        EventReport::SendRenderException(RenderExcepType::UI_THREAD_STUCK);
    }
}

void ThreadWatcher::RawReport(RawEventType type) const
{
    EventReport::ANRRawReport(
        type, AceEngine::Get().GetUid(), AceEngine::Get().GetPackageName(), AceEngine::Get().GetProcessName());
}

void ThreadWatcher::PostCheckTask()
{
    auto taskExecutor = taskExecutor_.Upgrade();
    if (taskExecutor) {
        // post task to specified thread to check it
        taskExecutor->PostTask(
            [weak = Referenced::WeakClaim(this)]() {
                auto sp = weak.Upgrade();
                if (sp) {
                    sp->TagIncrease();
                }
            },
            type_);
        std::unique_lock<std::shared_mutex> lock(mutex_);
        ++loopTime_;
    } else {
        LOGW("task executor with instanceId %{public}d invalid when check %{public}s thread whether stuck or not",
            instanceId_, threadName_.c_str());
    }
}

void ThreadWatcher::TagIncrease()
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    ++threadTag_;
}

WatchDog::WatchDog()
{
    if (!g_anrThread) {
        g_anrThread = std::make_unique<fml::Thread>("anr");
    }
}

WatchDog::~WatchDog()
{
    g_anrThread.reset();
}

void WatchDog::Register(int32_t instanceId, const RefPtr<TaskExecutor>& taskExecutor)
{
    Watchers watchers = {
        .jsWatcher = AceType::MakeRefPtr<ThreadWatcher>(instanceId, TaskExecutor::TaskType::JS),
        .uiWatcher = AceType::MakeRefPtr<ThreadWatcher>(instanceId, TaskExecutor::TaskType::UI),
    };
    watchers.jsWatcher->SetTaskExecutor(taskExecutor);
    watchers.uiWatcher->SetTaskExecutor(taskExecutor);
    const auto resExecutor = watchMap_.try_emplace(instanceId, watchers);
    if (!resExecutor.second) {
        LOGW("Duplicate instance id: %{public}d when register to watch dog", instanceId);
    }
}

void WatchDog::Unregister(int32_t instanceId)
{
    int32_t num = watchMap_.erase(instanceId);
    if (num == 0) {
        LOGW("Unregister from watch dog failed with instanceID %{public}d", instanceId);
    }
    if (watchMap_.empty()) {
        g_anrThread.reset();
    }
}

} // namespace OHOS::Ace