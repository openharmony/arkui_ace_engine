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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_STATUSBAR_CLICK_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_STATUSBAR_CLICK_H

#include <memory>
#include <mutex>
#include <set>

#include "core/event/statusbar/statusbar_event_proxy.h"
#include "common_event_subscriber.h"

namespace OHOS::Ace {
class WebStatusBarEventSubscriber : public EventFwk::CommonEventSubscriber {
public:
    explicit WebStatusBarEventSubscriber(const EventFwk::CommonEventSubscribeInfo &subscribeInfo)
        : CommonEventSubscriber(subscribeInfo)
    {}
    void OnReceiveEvent(const EventFwk::CommonEventData &data) override;

private:
    friend class WebPattern;
};

class WebStatusBarEventProxy : public StatusBarEventProxy {
public:
    WebStatusBarEventProxy();
    ~WebStatusBarEventProxy();
    static WebStatusBarEventProxy* GetWebInstance();
    void Register(const WeakPtr<StatusBarClickListener> &listener) override;
    void UnRegister(const WeakPtr<StatusBarClickListener> &listener) override;
    void OnStatusBarClick() override;
    std::set<std::pair<WeakPtr<StatusBarClickListener>, int32_t>> GetStatusBarClickListener() override
    {
        return listeners_;
    }

private:
    friend class WebPattern;
    std::set<std::pair<WeakPtr<StatusBarClickListener>, int32_t>> listeners_;
    std::shared_ptr<WebStatusBarEventSubscriber> eventFwkSubscriber_;
    std::mutex listenersMutex_;
    static std::unique_ptr<WebStatusBarEventProxy> webInstance_;
    static std::mutex webMutex_;
};
}  // namespace OHOS::Ace

#endif  // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_STATUSBAR_CLICK_H
