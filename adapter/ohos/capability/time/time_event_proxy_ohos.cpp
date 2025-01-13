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
#include "adapter/ohos/capability/time/time_event_proxy_ohos.h"

#include "common_event_manager.h"
#include "common_event_support.h"

#include "base/thread/task_executor.h"
#include "frameworks/core/common/container.h"

namespace OHOS::Ace {
std::unique_ptr<TimeEventProxy> TimeEventProxy::instance_;
std::mutex TimeEventProxy::mutex_;

TimeEventProxy* TimeEventProxy::GetInstance()
{
    if (!instance_) {
        std::scoped_lock lock(mutex_);
        if (!instance_) {
            instance_ = std::make_unique<TimeEventProxyOhos>();
        }
    }
    return instance_.get();
}

using OHOS::EventFwk::CommonEventManager;
using OHOS::EventFwk::CommonEventSubscribeInfo;
using OHOS::EventFwk::CommonEventSupport;
using OHOS::EventFwk::MatchingSkills;

void TimeEventSubscriber::OnReceiveEvent(const CommonEventData& /* data */)
{
    TimeEventProxy::GetInstance()->OnTimeChange();
}

TimeEventProxyOhos::TimeEventProxyOhos()
{
    MatchingSkills matchingSkills;
    matchingSkills.AddEvent(CommonEventSupport::COMMON_EVENT_TIME_CHANGED);
    matchingSkills.AddEvent(CommonEventSupport::COMMON_EVENT_TIMEZONE_CHANGED);
    matchingSkills.AddEvent(CommonEventSupport::COMMON_EVENT_SCREEN_ON);
    auto container = Container::Current();
    if (container && container->IsFRSCardContainer()) {
        matchingSkills.AddEvent(CommonEventSupport::COMMON_EVENT_TIME_TICK);
    }

    CommonEventSubscribeInfo subscribeInfo(matchingSkills);
    subscribeInfo.SetThreadMode(CommonEventSubscribeInfo::ThreadMode::HANDLER);

    eventFwkSubscriber_ = std::make_shared<TimeEventSubscriber>(subscribeInfo);
}

TimeEventProxyOhos::~TimeEventProxyOhos()
{
    CommonEventManager::UnSubscribeCommonEvent(eventFwkSubscriber_);
}

namespace {
void NotifyCard(const RefPtr<TimeChangeListener>& listener)
{
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    if (taskExecutor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
        listener->OnTimeChange();
    } else {
        taskExecutor->PostTask(
            [listener, id = Container::CurrentId()] {
                ContainerScope scope(id);
                listener->OnTimeChange();
            },
            TaskExecutor::TaskType::UI, "ArkUINotifyCardTimeChange",
            TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
    }
}
} // namespace

void TimeEventProxyOhos::OnTimeChange()
{
    for (auto it = listeners_.begin(); it != listeners_.end();) {
        auto listener = it->first.Upgrade();
        if (listener) {
            ContainerScope scope(it->second);
            auto container = Container::Current();
            if (container && container->IsFRSCardContainer()) {
                NotifyCard(listener);
            } else {
                listener->OnTimeChange();
            }
            ++it;
        } else {
            it = listeners_.erase(it);
        }
    }
}

void TimeEventProxyOhos::Register(const WeakPtr<TimeChangeListener>& listener)
{
    if (listeners_.empty()) {
        CommonEventManager::SubscribeCommonEvent(eventFwkSubscriber_);
    }
    listeners_.insert({ listener, Container::CurrentId() });
}
} // namespace OHOS::Ace
