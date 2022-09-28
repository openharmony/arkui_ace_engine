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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_VIEW_H

#include <string>

#include "base/utils/macros.h"
#include "core/components/calendar/calendar_data_adapter.h"
#include "core/components_ng/pattern/calendar/calendar_controller_ng.h"
#include "core/components_ng/pattern/calendar/calendar_paint_property.h"

namespace OHOS::Ace::NG {

struct CalendarData {
    CalendarDay date;
    ObtainedMonth currentData;
    ObtainedMonth preData;
    ObtainedMonth nextData;
    RefPtr<CalendarControllerNg> controller = nullptr;
};

class ACE_EXPORT CalendarView {
public:
    static void Create(const CalendarData& calendarData);
    static void SetShowLunar(bool showLunar);
    static void SetShowHoliday(bool showHoliday);
    static void SetNeedSlide(bool needSlide);
    static void SetStartOfWeek(Week startOfWeek);
    static void SetOffDays(const std::string& offDays);
    static void SetDirection(Axis direction);
    static void SetCurrentDayStyle(const CurrentDayStyle& currentDayStyle);
    static void SetNonCurrentDayStyle(const NonCurrentDayStyle& nonCurrentDayStyle);
    static void SetTodayStyle(const TodayStyle& todayStyle);
    static void SetWeekStyle(const WeekStyle& weekStyle);
    static void SetWorkStateStyle(const WorkStateStyle& workStateStyle);
    static void SetSelectedChangeEvent(std::function<void(const std::string&)>&& selectedChangeEvent);
    static void SetOnRequestDataEvent(std::function<void(const std::string&)>&& requestDataEvent);
    static void SetCurrentData(ObtainedMonth& currentData);
    static void SetPreData(ObtainedMonth& preData);
    static void SetNextData(ObtainedMonth& nextData);
    static void SetCalendarDay(CalendarDay& calendarDay);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_VIEW_H