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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components/checkable/checkable_component.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {

using GroupChangeEvent = std::function<void(const CheckboxGroupResult& info)>;

class CheckBoxGroupEventHub : public EventHub {
    DECLARE_ACE_TYPE(CheckBoxGroupEventHub, EventHub)

public:
    CheckBoxGroupEventHub() = default;
    ~CheckBoxGroupEventHub() override = default;

    void SetOnChange(GroupChangeEvent&& changeEvent)
    {
        changeEvent_ = std::move(changeEvent);
    }

    void UpdateChangeEvent(const CheckboxGroupResult& info) const
    {
        if (changeEvent_) {
            changeEvent_(info);
        }
    }

    const std::string& GetGroupName()
    {
        return groupname_;
    }

    void SetGroupName(const std::string& groupname)
    {
        groupname_ = groupname;
    }

private:
    GroupChangeEvent changeEvent_;
    std::string groupname_;

    ACE_DISALLOW_COPY_AND_MOVE(CheckBoxGroupEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_CHECKBOX_EVENT_HUB_H