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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {

using SelectEvent = std::function<void(int32_t, const std::string&)>;
using SelectChangeEvent = std::function<void(int32_t)>;
using ValueChangeEvent = std::function<void(const std::string&)>;

class SelectEventHub : public EventHub {
    DECLARE_ACE_TYPE(SelectEventHub, EventHub);
public:
    SelectEventHub() = default;

    ~SelectEventHub() override = default;

    void SetSelectEvent(SelectEvent&& onSelect)
    {
        onSelect_ = std::move(onSelect);
    }

    const SelectEvent& GetSelectEvent()
    {
        return onSelect_;
    }

    void SetSelectChangeEvent(SelectChangeEvent&& selectChangeEvent)
    {
        selectChangeEvent_ = std::move(selectChangeEvent);
    }

    const SelectChangeEvent& GetSelectChangeEvent()
    {
        return selectChangeEvent_;
    }

    void SetValueChangeEvent(ValueChangeEvent&& valueChangeEvent)
    {
        valueChangeEvent_ = std::move(valueChangeEvent);
    }

    const ValueChangeEvent& GetValueChangeEvent()
    {
        return valueChangeEvent_;
    }

private:
    SelectEvent onSelect_;
    SelectChangeEvent selectChangeEvent_;
    ValueChangeEvent valueChangeEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(SelectEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_EVENT_HUB_H
 
