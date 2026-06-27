/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATE_PICKER_PICKER_CHANGE_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATE_PICKER_PICKER_CHANGE_EVENT_H

#include <string>

#include "ui/event/ace_events.h"

namespace OHOS::Ace::NG {

class ACE_FORCE_EXPORT DatePickerChangeEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(DatePickerChangeEvent, BaseEventInfo);

public:
    explicit DatePickerChangeEvent(const std::string& str) : BaseEventInfo
        ("DatePickerChangeEvent"), selectedStr_(str) {}
    ~DatePickerChangeEvent() = default;

    const std::string& GetSelectedStr() const
    {
        return selectedStr_;
    }

private:
    std::string selectedStr_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATE_PICKER_PICKER_CHANGE_EVENT_H
