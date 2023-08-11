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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_CALENDAR_CONTROLLER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_CALENDAR_CONTROLLER_MODEL_H

#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/calendar/calendar_data.h"

namespace OHOS::Ace {
class CalendarControllerModel {
public:
    static CalendarControllerModel* GetInstance();
    virtual ~CalendarControllerModel() = default;
    
    virtual RefPtr<AceType> GetController() = 0;
    virtual void BackToToday(RefPtr<AceType>& controller) = 0;
    virtual void GoTo(const int32_t& year, const int32_t& month,
        const int32_t& day, RefPtr<AceType>& controller) = 0;

private:
    static std::unique_ptr<CalendarControllerModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_CALENDAR_CONTROLLER_MODEL_H
