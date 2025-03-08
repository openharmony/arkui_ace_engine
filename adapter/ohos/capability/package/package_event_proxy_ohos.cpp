/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "adapter/ohos/capability/package/package_event_proxy_ohos.h"

#include "common_event_manager.h"
#include "common_event_support.h"

#include "frameworks/core/common/container.h"

namespace OHOS::Ace {
std::unique_ptr<PackageEventProxy> PackageEventProxy::instance_;
std::mutex PackageEventProxy::mutex_;

PackageEventProxy* PackageEventProxy::GetInstance()
{
    if (!instance_) {
        std::scoped_lock lock(mutex_);
        if (!instance_) {
            instance_ = std::make_unique<PackageEventProxyOhos>();
        }
    }
    return instance_.get();
}

using OHOS::EventFwk::CommonEventManager;
using OHOS::EventFwk::CommonEventSubscribeInfo;
using OHOS::EventFwk::CommonEventSupport;
using OHOS::EventFwk::MatchingSkills;

void PackageEventSubscriber::OnReceiveEvent(const CommonEventData& /* data */)
{
    LOGI("Package Change Common Event Received");
    PackageEventProxy::GetInstance()->OnPackageChange();
}

PackageEventProxyOhos::PackageEventProxyOhos()
{
    MatchingSkills matchingSkills;
    matchingSkills.AddEvent(CommonEventSupport::COMMON_EVENT_PACKAGE_CHANGED);
    matchingSkills.AddEvent(CommonEventSupport::COMMON_EVENT_PACKAGE_REMOVED);

    CommonEventSubscribeInfo subscribeInfo(matchingSkills);
    subscribeInfo.SetThreadMode(CommonEventSubscribeInfo::ThreadMode::HANDLER);

    packageEventSubscriber_ = std::make_shared<PackageEventSubscriber>(subscribeInfo);
}

PackageEventProxyOhos::~PackageEventProxyOhos()
{
    CommonEventManager::UnSubscribeCommonEvent(packageEventSubscriber_);
}

void PackageEventProxyOhos::OnPackageChange()
{
    auto it = listeners_.begin();
    while (it != listeners_.end()) {
        auto listener = it->first.Upgrade();
        if (listener) {
            ContainerScope scope(it->second);
            listener->OnPackageChange();
            ++it;
        } else {
            it = listeners_.erase(it);
            if (listeners_.empty()) {
                CommonEventManager::UnSubscribeCommonEvent(packageEventSubscriber_);
            }
        }
    }
}

void PackageEventProxyOhos::Register(const WeakPtr<PackageChangeListener>& listener)
{
    if (listeners_.empty()) {
        CommonEventManager::SubscribeCommonEvent(packageEventSubscriber_);
    }
    listeners_.insert({ listener, Container::CurrentId() });
}
} // namespace OHOS::Ace