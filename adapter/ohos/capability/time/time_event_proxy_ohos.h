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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_CAPABILITY_EVENT_PROXY_TIME_H
#define FOUNDATION_ACE_ADAPTER_OHOS_CAPABILITY_EVENT_PROXY_TIME_H

#include <memory>
#include <mutex>
#include <set>

#include "common_event_subscriber.h"

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/event/time/time_event_proxy.h"

namespace OHOS::Ace {
using EventFwk::CommonEventData;
using EventFwk::CommonEventSubscribeInfo;
using EventFwk::CommonEventSubscriber;

/**
 * @brief The TimeEventSubscriber class is a subclass of CommonEventSubscriber.
 * It represents a subscriber for time events.
 */
class TimeEventSubscriber : public CommonEventSubscriber {
public:
    explicit TimeEventSubscriber(const CommonEventSubscribeInfo& subscribeInfo) : CommonEventSubscriber(subscribeInfo)
    {}
    void OnReceiveEvent(const CommonEventData& data) override;
};

class TimeEventProxyOhos : public TimeEventProxy {
public:
    TimeEventProxyOhos();
    ~TimeEventProxyOhos() override;

    void Register(const WeakPtr<TimeChangeListener>& listener) override;

    void OnTimeChange() override;

private:
    /**
     * @brief A set of time change listeners paired with their Container IDs.
     * 
     * Need to switch to the correct container ID before notifying the listener.
     */
    std::set<std::pair<WeakPtr<TimeChangeListener>, int32_t>> listeners_;

    std::shared_ptr<TimeEventSubscriber> eventFwkSubscriber_;

    ACE_DISALLOW_COPY_AND_MOVE(TimeEventProxyOhos);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_CAPABILITY_EVENT_PROXY_TIME_H
