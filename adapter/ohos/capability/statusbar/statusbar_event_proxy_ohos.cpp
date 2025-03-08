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
#include "adapter/ohos/capability/statusbar/statusbar_event_proxy_ohos.h"

#include "common_event_manager.h"
#include "common_event_support.h"

#include "frameworks/core/common/container.h"

namespace OHOS::Ace {
std::unique_ptr<StatusBarEventProxy> StatusBarEventProxy::instance_;
std::mutex StatusBarEventProxy::mutex_;

StatusBarEventProxy* StatusBarEventProxy::GetInstance()
{
    if (!instance_) {
        std::scoped_lock lock(mutex_);
        if (!instance_) {
            instance_ = std::make_unique<StatusBarEventProxyOhos>();
        }
    }
    return instance_.get();
}

using OHOS::EventFwk::CommonEventManager;
using OHOS::EventFwk::CommonEventSubscribeInfo;
using OHOS::EventFwk::CommonEventSupport;
using OHOS::EventFwk::MatchingSkills;

void StatusBarEventSubscriber::OnReceiveEvent(const CommonEventData& /* data */)
{
    StatusBarEventProxy::GetInstance()->OnStatusBarClick();
}

StatusBarEventProxyOhos::StatusBarEventProxyOhos()
{
    MatchingSkills matchingSkills;
    matchingSkills.AddEvent("usual.event.CLICK_STATUSBAR");
    CommonEventSubscribeInfo subscribeInfo(matchingSkills);
    subscribeInfo.SetThreadMode(CommonEventSubscribeInfo::ThreadMode::HANDLER);

    eventFwkSubscriber_ = std::make_shared<StatusBarEventSubscriber>(subscribeInfo);
}

StatusBarEventProxyOhos::~StatusBarEventProxyOhos()
{
    CommonEventManager::UnSubscribeCommonEvent(eventFwkSubscriber_);
}

namespace {
void NotifyCard(const RefPtr<StatusBarClickListener>& listener)
{
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    if (taskExecutor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
        listener->OnStatusBarClick();
    } else {
        taskExecutor->PostTask(
            [listener, id = Container::CurrentId()] {
                ContainerScope scope(id);
                listener->OnStatusBarClick();
            },
            TaskExecutor::TaskType::UI, "ArkUINotifyCardStatusBarClick");
    }
}
} // namespace

void StatusBarEventProxyOhos::OnStatusBarClick()
{
    for (auto it = listeners_.begin(); it != listeners_.end();) {
        auto listener = it->first.Upgrade();
        if (listener) {
            ContainerScope scope(it->second);
            auto container = Container::Current();
            if (container && container->IsFRSCardContainer()) {
                NotifyCard(listener);
            } else {
                listener->OnStatusBarClick();
            }
            ++it;
        } else {
            it = listeners_.erase(it);
        }
    }
}

void StatusBarEventProxyOhos::Register(const WeakPtr<StatusBarClickListener>& listener)
{
    if (listeners_.empty()) {
        CommonEventManager::SubscribeCommonEvent(eventFwkSubscriber_);
    }
    listeners_.insert({ listener, Container::CurrentId() });
}

void StatusBarEventProxyOhos::UnRegister(const WeakPtr<StatusBarClickListener>& listener)
{
    if (listeners_.empty()) {
        return;
    }
    for (auto it = listeners_.begin(); it != listeners_.end(); ++it) {
        if (it->first == listener) {
            listeners_.erase(it);
            break;
        }
    }
}
} // namespace OHOS::Ace
