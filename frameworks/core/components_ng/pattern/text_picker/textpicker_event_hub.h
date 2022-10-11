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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

using TextChangeEvent = std::function<void(const std::string&, double)>;
using DailogTextChangeEvent = std::function<void(const std::string&)>;

class TextPickerEventHub : public EventHub {
    DECLARE_ACE_TYPE(TextPickerEventHub, EventHub)

public:
    TextPickerEventHub() = default;
    ~TextPickerEventHub() override = default;

    void SetOnChange(TextChangeEvent&& TextChangeEvent)
    {
        TextChangeEvent_ = std::move(TextChangeEvent);
    }

    void FireChangeEvent(const std::string& value, double index) const
    {
        if (TextChangeEvent_) {
            TextChangeEvent_(value, index);
        }
    }

    void SetDailogChange(DailogTextChangeEvent&& onChange)
    {
        dailogChangeEvent_ = std::move(onChange);
    }

    void FireDailogChangeEvent(const std::string& info) const
    {
        if (dailogChangeEvent_) {
            dailogChangeEvent_(info);
        }
    }

private:
    TextChangeEvent TextChangeEvent_;
    DailogTextChangeEvent dailogChangeEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(TextPickerEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_EVENT_HUB_H