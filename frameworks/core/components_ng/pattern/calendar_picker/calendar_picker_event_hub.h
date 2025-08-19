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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_PICKER_CALENDAR_PICKER_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_PICKER_CALENDAR_PICKER_EVENT_HUB_H

#include <string>

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {
using SelectedChangeEvent = std::function<void(const std::string&)>;
using LayoutChangeEvent = std::function<void()>;

class CalendarPickerEventHub : public EventHub {
    DECLARE_ACE_TYPE(CalendarPickerEventHub, EventHub);

public:
    CalendarPickerEventHub() = default;
    ~CalendarPickerEventHub() override = default;

    void SetInputChangeEvent(const SelectedChangeEvent& selectedChangeEvent)
    {
        inputChangeEvent_ = selectedChangeEvent;
    }

    void UpdateInputChangeEvent(const std::string& info) const
    {
        if (inputChangeEvent_) {
            inputChangeEvent_(info);
        }
    }

    void UpdateOnChangeEvent(const std::string& info) const
    {
        if (onChangeEvent_) {
            onChangeEvent_(info);
        }
    }

    void SetOnChangeEvent(const SelectedChangeEvent& onChangeEvent)
    {
        onChangeEvent_ = onChangeEvent;
    }

    void UpdateChangeEvent(const std::string& info) const
    {
        if (changeEvent_) {
            changeEvent_(info);
        }
    }

    void SetChangeEvent(const SelectedChangeEvent& changeEvent)
    {
        changeEvent_ = changeEvent;
    }

    void FireLayoutChangeEvent() const
    {
        if (layoutChangeEvent_) {
            layoutChangeEvent_();
        }
    }

    void SetLayoutChangeEvent(const LayoutChangeEvent& event)
    {
        layoutChangeEvent_ = event;
    }
private:
    SelectedChangeEvent inputChangeEvent_;
    SelectedChangeEvent onChangeEvent_;
    SelectedChangeEvent changeEvent_;
    LayoutChangeEvent layoutChangeEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(CalendarPickerEventHub);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_PICKER_CALENDAR_PICKER_EVENT_HUB_H
