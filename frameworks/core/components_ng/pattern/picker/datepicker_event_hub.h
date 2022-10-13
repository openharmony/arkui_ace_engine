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

#include <utility>

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {

using DateChangeEvent = std::function<void(const BaseEventInfo* info)>;
using DailogEvent = std::function<void(const std::string&)>;
using DailogCancelEvent = std::function<void()>;
using DailogGestureEvent = std::function<void(const GestureEvent& info)>;

class DatePickerEventHub : public EventHub {
    DECLARE_ACE_TYPE(DatePickerEventHub, EventHub)

public:
    DatePickerEventHub() = default;
    ~DatePickerEventHub() override = default;

    void SetOnChange(DateChangeEvent&& onChange)
    {
        changeEvent_ = std::move(onChange);
    }

    void FireChangeEvent(const BaseEventInfo* info) const
    {
        if (changeEvent_) {
            changeEvent_(info);
        }
    }

    void SetDailogChange(DailogEvent&& onChange)
    {
        dailogChangeEvent_ = std::move(onChange);
    }

    void FireDailogChangeEvent(const std::string& info) const
    {
        if (dailogChangeEvent_) {
            dailogChangeEvent_(info);
        }
    }

    void SetDailogAcceptEvent(DailogEvent&& onChange)
    {
        dailogAcceptEvent_ = std::move(onChange);
    }

    void FireDailogAcceptEvent(const std::string& info) const
    {
        if (dailogAcceptEvent_) {
            dailogAcceptEvent_(info);
        }
    }

private:
    DateChangeEvent changeEvent_;
    DailogEvent dailogChangeEvent_;
    DailogEvent dailogAcceptEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(DatePickerEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS__DATE_PICKER_DATE_PICKER_EVENT_HUB_H