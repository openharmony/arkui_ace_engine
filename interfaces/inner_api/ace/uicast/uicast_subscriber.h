/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UICAST_UICAST_SUBSCRIBER_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UICAST_UICAST_SUBSCRIBER_H

#include <string>

#include "common_event_manager.h"
#include "common_event_subscriber.h"
#include "interfaces/inner_api/ace/ui_content.h"
#include "singleton.h"

namespace OHOS::Ace {
using OHOS::EventFwk::CommonEventData;
using OHOS::EventFwk::CommonEventManager;
using OHOS::EventFwk::CommonEventSubscribeInfo;
using OHOS::EventFwk::CommonEventSubscriber;
using OHOS::EventFwk::MatchingSkills;

class UICastEventSubscriber : public CommonEventSubscriber {
public:
    explicit UICastEventSubscriber(const CommonEventSubscribeInfo& info, UIContent* context)
        : CommonEventSubscriber(info), context_(context)
    {}

    ~UICastEventSubscriber() {}

    void UICastProxyStart(int castSessionId, UIContent* context);
    void UICastProxyStop();
    void UICastProxyUpdateContext(UIContent* context);

    void OnReceiveEvent(const CommonEventData& data) override;

private:
    UIContent* context_;
    void* handle_ { nullptr };
};

class UICastEventSubscribeProxy : public DelayedSingleton<UICastEventSubscribeProxy> {
public:
    ~UICastEventSubscribeProxy()
    {
        UnSubscribeStartEvent();
    }
    void SubscribeStartEvent(UIContent* context);
    void UnSubscribeStartEvent(void);

private:
    std::shared_ptr<CommonEventSubscriber> eventReceiver_;
    std::shared_ptr<UICastEventSubscriber> uicastEventReceiver_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UICAST_UICAST_SUBSCRIBER_H
