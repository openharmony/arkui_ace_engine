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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_EVENT_PASS_THROUGH_SUBSCRIBER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_EVENT_PASS_THROUGH_SUBSCRIBER_H

#include "common_event_manager.h"
#include "common_event_subscriber.h"
#include "singleton.h"
#include "adapter/ohos/entrance/ui_content_impl.h"

namespace OHOS::Ace {
using OHOS::EventFwk::CommonEventData;
using OHOS::EventFwk::CommonEventManager;
using OHOS::EventFwk::CommonEventSubscribeInfo;
using OHOS::EventFwk::CommonEventSubscriber;
using OHOS::EventFwk::MatchingSkills;

class EventPassThroughSubscriber : public CommonEventSubscriber {
public:
    explicit EventPassThroughSubscriber(const CommonEventSubscribeInfo& info)
        : CommonEventSubscriber(info)
    {}

    ~EventPassThroughSubscriber() {}
    void OnReceiveEvent(const CommonEventData& data) override;
    void AddInstanceId(int32_t instanceId);
    bool EraseContainerAddCheckUnSubscribe(int32_t instanceId);
private:
    std::set<int32_t> instanceMap_;
};

class EventPassThroughSubscribeProxy : public DelayedSingleton<EventPassThroughSubscribeProxy> {
public:
    ~EventPassThroughSubscribeProxy()
    {
        UnSubscribeEvent();
    }
    void SubscribeEvent(int32_t instanceId);
    void UnSubscribeEvent();
    void UnSubscribeEvent(int32_t instanceId);

private:
    std::shared_ptr<CommonEventSubscriber> eventReceiver_;
    std::shared_ptr<EventPassThroughSubscriber> eventPassThroughReceiver_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_EVENT_PASS_THROUGH_SUBSCRIBER_H
