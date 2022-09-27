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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_CHECKBOX_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_CHECKBOX_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {

using ChangeEvent = std::function<void(const bool)>;

class CheckBoxEventHub : public EventHub {
    DECLARE_ACE_TYPE(CheckBoxEventHub, EventHub)

public:
    CheckBoxEventHub() = default;

    ~CheckBoxEventHub() override = default;

    void SetOnChange(ChangeEvent&& changeEvent)
    {
        changeEvent_ = std::move(changeEvent);
    }

    void UpdateChangeEvent(bool select) const
    {
        if (changeEvent_) {
            changeEvent_(select);
        }
    }

    const std::string& GetName()
    {
        return name_;
    }

    const std::string& GetGroupName()
    {
        return groupname_;
    }

    void SetName(const std::string& name)
    {
        name_ = name;
    }

    void SetGroupName(const std::string& groupname)
    {
        groupname_ = groupname;
    }

private:
    ChangeEvent changeEvent_;
    std::string name_;
    std::string groupname_;

    ACE_DISALLOW_COPY_AND_MOVE(CheckBoxEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_CHECKBOX_EVENT_HUB_H