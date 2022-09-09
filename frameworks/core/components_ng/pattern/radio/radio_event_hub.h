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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RADIO_RADIO_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RADIO_RADIO_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {

using ChangeEvent = std::function<void(const bool)>;

class RadioEventHub : public EventHub {
    DECLARE_ACE_TYPE(RadioEventHub, EventHub)

public:
    RadioEventHub() = default;
    ~RadioEventHub() override = default;

    void SetOnChange(ChangeEvent&& changeEvent)
    {
        changeEvent_ = std::move(changeEvent);
    }

    void UpdateChangeEvent(bool check) const
    {
        if (changeEvent_) {
            changeEvent_(check);
        }
    }

    const std::string& GetValue()
    {
        return value_;
    }

    const std::string& GetGroup()
    {
        return group_;
    }

    void SetValue(const std::string& value)
    {
        value_ = value;
    }

    void SetGroup(const std::string& group)
    {
        group_ = group;
    }

private:
    ChangeEvent changeEvent_;
    std::string value_;
    std::string group_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RADIO_RADIO_EVENT_HUB_H