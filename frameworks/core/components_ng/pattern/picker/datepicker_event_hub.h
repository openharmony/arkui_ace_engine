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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS__DATE_PICKER_DATE_PICKER_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS__DATE_PICKER_DATE_PICKER_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/picker/datepicker_event_types.h"
#include "core/components_ng/pattern/picker_utils/dialog_event_types.h"

namespace OHOS::Ace::NG {

class DatePickerEventHub : public EventHub {
    DECLARE_ACE_TYPE(DatePickerEventHub, EventHub);

public:
    DatePickerEventHub() = default;
    ~DatePickerEventHub() override = default;
    void SetOnChange(DateChangeEvent&& onChange);

    void SetOnDateChange(DateChangeEvent&& onChange);

    void FireChangeEvent(const BaseEventInfo* info) const;

    void SetDialogChange(DialogEvent&& onChange);

    void FireDialogChangeEvent(const std::string& info) const;

    void SetDialogAcceptEvent(DialogEvent&& onChange);

    void FireDialogAcceptEvent(const std::string& info) const;

    void SetDialogDateChange(DialogEvent&& onChange);

    void SetDialogDateAcceptEvent(DialogEvent&& onChange);

    void SetChangeEvent(DateChangeEvent&& onChange);

private:
    DateChangeEvent changeEvent_;
    DateChangeEvent dateChangeEvent_;
    DialogEvent dialogChangeEvent_;
    DialogEvent dialogAcceptEvent_;
    DialogEvent dialogDateChangeEvent_;
    DialogEvent dialogDateAcceptEvent_;
    DateChangeEvent selectedChangeEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(DatePickerEventHub);
};

} // namespace OHOS::Ace::NG

// Inline implementations to ensure availability across translation units.
inline void OHOS::Ace::NG::DatePickerEventHub::SetOnChange(DateChangeEvent&& onChange)
{
    changeEvent_ = std::move(onChange);
}

inline void OHOS::Ace::NG::DatePickerEventHub::SetOnDateChange(DateChangeEvent&& onChange)
{
    dateChangeEvent_ = std::move(onChange);
}

inline void OHOS::Ace::NG::DatePickerEventHub::FireChangeEvent(const BaseEventInfo* info) const
{
    if (selectedChangeEvent_) {
        selectedChangeEvent_(info);
    }
    if (changeEvent_) {
        changeEvent_(info);
    }
    if (dateChangeEvent_) {
        dateChangeEvent_(info);
    }
}

inline void OHOS::Ace::NG::DatePickerEventHub::SetDialogChange(DialogEvent&& onChange)
{
    dialogChangeEvent_ = std::move(onChange);
}

inline void OHOS::Ace::NG::DatePickerEventHub::FireDialogChangeEvent(const std::string& info) const
{
    if (dialogChangeEvent_) {
        dialogChangeEvent_(info);
    }
    if (dialogDateChangeEvent_) {
        dialogDateChangeEvent_(info);
    }
}

inline void OHOS::Ace::NG::DatePickerEventHub::SetDialogAcceptEvent(DialogEvent&& onChange)
{
    dialogAcceptEvent_ = std::move(onChange);
}

inline void OHOS::Ace::NG::DatePickerEventHub::FireDialogAcceptEvent(const std::string& info) const
{
    if (dialogAcceptEvent_) {
        dialogAcceptEvent_(info);
    }
    if (dialogDateAcceptEvent_) {
        dialogDateAcceptEvent_(info);
    }
}

inline void OHOS::Ace::NG::DatePickerEventHub::SetDialogDateChange(DialogEvent&& onChange)
{
    dialogDateChangeEvent_ = std::move(onChange);
}

inline void OHOS::Ace::NG::DatePickerEventHub::SetDialogDateAcceptEvent(DialogEvent&& onChange)
{
    dialogDateAcceptEvent_ = std::move(onChange);
}

inline void OHOS::Ace::NG::DatePickerEventHub::SetChangeEvent(DateChangeEvent&& onChange)
{
    selectedChangeEvent_ = std::move(onChange);
}


#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS__DATE_PICKER_DATE_PICKER_EVENT_HUB_H
