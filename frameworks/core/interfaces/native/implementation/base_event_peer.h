/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "core/event/ace_events.h"
#include "arkoala_api_generated.h"

struct BaseEventPeer {
    virtual ~BaseEventPeer() = default;

    virtual OHOS::Ace::BaseEventInfo* GetBaseInfo() = 0;
};

namespace OHOS::Ace::NG::GeneratedModifier {
template<typename AceInfo>
class EventPeer : public BaseEventPeer {
public:
    ~EventPeer() override = default;

    BaseEventInfo* GetBaseInfo() override
    {
        return GetEventInfo();
    }

    AceInfo* GetEventInfo()
    {
        CHECK_NULL_RETURN(eventInfo, nullptr);
        return &eventInfo.value();
    }

    void SetEventInfo(const AceInfo& info)
    {
        eventInfo = info;
    }

private:
    std::optional<AceInfo> eventInfo;
};

using BaseEventPeerImpl = EventPeer<BaseEventInfo>;
} // namespace OHOS::Ace::NG::GeneratedModifier
