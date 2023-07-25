/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

using TimeChangeEvent = std::function<void(const BaseEventInfo* info)>;
using DialogEvent = std::function<void(const std::string&)>;
using DialogCancelEvent = std::function<void()>;
using DialogGestureEvent = std::function<void(const GestureEvent& info)>;
using TimeChangeEventForDatePicker = std::function<void()>;

class TimePickerEventHub : public EventHub {
    DECLARE_ACE_TYPE(TimePickerEventHub, EventHub)

public:
    TimePickerEventHub() = default;
    ~TimePickerEventHub() override = default;

    void SetOnChange(TimeChangeEvent&& changeEvent)
    {
        changeEvent_ = std::move(changeEvent);
    }

    void SetOnChangeForDatePicker(TimeChangeEventForDatePicker&& changeEvent)
    {
        changeEventForDatePicker_ = std::move(changeEvent);
    }

    void FireChangeEvent(const BaseEventInfo* info) const
    {
        if (selectedTimeChangeEvent_) {
            selectedTimeChangeEvent_(info);
        }
        if (changeEvent_) {
            changeEvent_(info);
        }
        if (changeEventForDatePicker_) {
            changeEventForDatePicker_();
        }
    }

    void SetDialogChange(DialogEvent&& onChange)
    {
        DialogChangeEvent_ = std::move(onChange);
    }

    void FireDialogChangeEvent(const std::string& info) const
    {
        if (DialogChangeEvent_) {
            DialogChangeEvent_(info);
        }
    }

    void SetDialogAcceptEvent(DialogEvent&& onChange)
    {
        DialogAcceptEvent_ = std::move(onChange);
    }

    void FireDialogAcceptEvent(const std::string& info) const
    {
        if (DialogAcceptEvent_) {
            DialogAcceptEvent_(info);
        }
    }

    void SetChangeEvent(TimeChangeEvent&& changeEvent)
    {
        selectedTimeChangeEvent_ = std::move(changeEvent);
    }

private:
    TimeChangeEvent changeEvent_;
    DialogEvent DialogChangeEvent_;
    DialogEvent DialogAcceptEvent_;
    TimeChangeEvent selectedTimeChangeEvent_;
    TimeChangeEventForDatePicker changeEventForDatePicker_;

    ACE_DISALLOW_COPY_AND_MOVE(TimePickerEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_EVENT_HUB_H
