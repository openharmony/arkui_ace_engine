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

#include "web_statusbar_click.h"

#include <memory>
#include <mutex>
#include <set>

#include "common_event_manager.h"
#include "common_event_support.h"
#include "frameworks/core/common/container.h"

namespace OHOS::Ace {
std::unique_ptr<WebStatusBarEventProxy> WebStatusBarEventProxy::webInstance_;
std::mutex WebStatusBarEventProxy::webMutex_;

WebStatusBarEventProxy::WebStatusBarEventProxy()
{
    EventFwk::MatchingSkills matchingSkills;
    matchingSkills.AddEvent("usual.event.CLICK_STATUSBAR");
    EventFwk::CommonEventSubscribeInfo subscribeInfo(matchingSkills);
    subscribeInfo.SetThreadMode(EventFwk::CommonEventSubscribeInfo::ThreadMode::HANDLER);
    eventFwkSubscriber_ = std::make_shared<WebStatusBarEventSubscriber>(subscribeInfo);
}

WebStatusBarEventProxy::~WebStatusBarEventProxy()
{
    EventFwk::CommonEventManager::UnSubscribeCommonEvent(eventFwkSubscriber_);
}

WebStatusBarEventProxy* WebStatusBarEventProxy::GetWebInstance()
{
    std::scoped_lock lock(webMutex_);
    if (!webInstance_) {
        webInstance_ = std::make_unique<WebStatusBarEventProxy>();
    }
    return webInstance_.get();
}

void WebStatusBarEventProxy::Register(const WeakPtr<StatusBarClickListener> &listener)
{
    std::scoped_lock lock(listenersMutex_);

    if (listeners_.empty()) {
        EventFwk::CommonEventManager::SubscribeCommonEvent(eventFwkSubscriber_);
    }
    auto result = listeners_.insert({listener, Container::CurrentId()});
    if (!result.second) {
        TAG_LOGD(AceLogTag::ACE_WEB, "WebStatusBarEventProxy Register Unsuccessful");
    }
}

void WebStatusBarEventProxy::UnRegister(const WeakPtr<StatusBarClickListener> &listener)
{
    std::scoped_lock lock(listenersMutex_);
    if (listeners_.empty()) {
        return;
    }
    for (auto it = listeners_.begin(); it != listeners_.end();) {
        if (it->first == listener) {
            listeners_.erase(it);
            break;
        } else {
            ++it;
        }
    }
}

void WebStatusBarEventProxy::OnStatusBarClick()
{
    TAG_LOGD(AceLogTag::ACE_WEB, "WebStatusBarEventProxy::OnStatusBarClick");
    std::scoped_lock lock(listenersMutex_);
    for (auto it = listeners_.begin(); it != listeners_.end();) {
        auto listener = it->first.Upgrade();
        if (listener) {
            ContainerScope scope(it->second);
            auto container = Container::Current();
            if (!container) {
                return;
            } else {
                listener->OnStatusBarClick();
            }
            ++it;
        } else {
            it = listeners_.erase(it);
        }
    }
}

void WebStatusBarEventSubscriber::OnReceiveEvent(const EventFwk::CommonEventData &data)
{
    WebStatusBarEventProxy::GetWebInstance()->OnStatusBarClick();
}
}  // namespace OHOS::Ace
