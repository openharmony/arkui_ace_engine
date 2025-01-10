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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_CALENDAR_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_CALENDAR_MODEL_H

#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/calendar/calendar_data.h"

namespace OHOS::Ace {
class CalendarModel {
public:
    static CalendarModel* GetInstance();
    virtual ~CalendarModel() = default;
    
    virtual void Create(const CalendarModelData& calendarModelData) = 0;
    virtual void SetOffDays(const std::string& offDays) = 0;
    virtual void SetShowHoliday(const bool showHoliday) = 0;
    virtual void SetShowLunar(const bool showLunar) = 0;
    virtual void SetStartOfWeek(const int32_t startOfWeek) = 0;
    virtual void SetNeedSlide(const bool needSlide) = 0;
    virtual void SetSelectedChangeEvent(std::function<void(const std::string&)>&& selectedChangeEvent) = 0;
    virtual void SetOnRequestDataEvent(std::function<void(const std::string&)>&& requestData) = 0;
    virtual void SetDirection(const int32_t dir) = 0;
    virtual void SetCurrentDayStyle(const CurrentDayStyleData& currentDayStyleData,
        const CurrentDayStyleData& CurrentDayStyleDataImpl) = 0;
    virtual void SetNonCurrentDayStyle(const NonCurrentDayStyleData& nonCurrentDayStyleData) = 0;
    virtual void SetTodayStyle(const TodayStyleData& style) = 0;
    virtual void SetWeekStyle(const WeekStyleData& style) = 0;
    virtual void SetWorkStateStyle(const WorkStateStyleData& style) = 0;

private:
    static std::unique_ptr<CalendarModel> instance_;
    static std::once_flag onceFlag_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_CALENDAR_MODEL_H