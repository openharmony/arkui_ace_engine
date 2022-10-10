/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ABILITY_COMPONENT_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ABILITY_COMPONENT_EVENT_HUB_H

#include "frameworks/base/memory/ace_type.h"
#include "frameworks/base/utils/noncopyable.h"
#include "frameworks/core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

using ConnectEvent = std::function<void()>;
using DisConnectEvent = std::function<void()>;
class AbilityComponentEventHub : public EventHub {
    DECLARE_ACE_TYPE(AbilityComponentEventHub, EventHub)

public:
    AbilityComponentEventHub() = default;
    ~AbilityComponentEventHub() override = default;

    void SetOnConnect(ConnectEvent&& connectEvent)
    {
        connectEvent_ = std::move(connectEvent);
    }

    void FireOnConnect() const
    {
        if (connectEvent_) {
            connectEvent_();
        }
    }
    void SetOnDisConnect(DisConnectEvent&& disConnectEvent)
    {
        disconnectEvent_ = std::move(disConnectEvent);
    }

    void FireOnDisConnect() const
    {
        if (disconnectEvent_) {
            disconnectEvent_();
        }
    }

private:
    ConnectEvent connectEvent_;
    DisConnectEvent disconnectEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(AbilityComponentEventHub);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ABILITY_COMPONENT_EVENT_HUB_H