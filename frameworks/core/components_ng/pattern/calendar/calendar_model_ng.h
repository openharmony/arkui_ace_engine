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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_CALENDAR_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_CALENDAR_MODEL_NG_H

#include "base/utils/macros.h"
#include "core/components/calendar/calendar_data_adapter.h"
#include "core/components_ng/pattern/calendar/calendar_controller_ng.h"
#include "core/components_ng/pattern/calendar/calendar_model.h"
#include "core/components_ng/pattern/calendar/calendar_paint_property.h"

namespace OHOS::Ace::NG {
struct CalendarData {
    CalendarDay date;
    ObtainedMonth currentData;
    ObtainedMonth preData;
    ObtainedMonth nextData;
    RefPtr<CalendarControllerNg> controller = nullptr;
};

class ACE_EXPORT CalendarModelNG: public OHOS::Ace::CalendarModel {
public:
    void Create(const CalendarModelData& calendarModelData) override;
    void SetOffDays(const std::string& offDays) override;
    void SetShowHoliday(const bool showHoliday) override;
    void SetShowLunar(const bool showLunar) override;
    void SetStartOfWeek(const int32_t startOfWeek) override;
    void SetNeedSlide(const bool needSlide) override;
    void SetSelectedChangeEvent(std::function<void(const std::string&)>&& selectedChangeEvent) override;
    void SetOnRequestDataEvent(std::function<void(const std::string&)>&& requestData) override;
    void SetDirection(const int32_t dir) override;
    void SetCurrentDayStyle(const CurrentDayStyleData& currentDayStyleData,
        const CurrentDayStyleData& CurrentDayStyleDataImpl) override;
    void SetNonCurrentDayStyle(const NonCurrentDayStyleData& nonCurrentDayStyleData) override;
    void SetTodayStyle(const TodayStyleData& style) override;
    void SetWeekStyle(const WeekStyleData& style) override;
    void SetWorkStateStyle(const WorkStateStyleData& style) override;

    static void SetCurrentData(const ObtainedMonth& currentData);
    static void SetPreData(const ObtainedMonth& preData);
    static void SetNextData(const ObtainedMonth& nextData);
    static void SetCalendarDay(const CalendarDay& calendarDay);

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetOptions(FrameNode* frameNode, const CalendarData& calendarData);
    static void SetShowLunar(FrameNode* frameNode, bool showLunar);
    static void SetShowHoliday(FrameNode* frameNode, bool showHoliday);
    static void SetNeedSlide(FrameNode* frameNode, bool needSlide);
    static void SetStartOfWeek(FrameNode* frameNode, int32_t startOfWeek);
    static void SetOffDays(FrameNode* frameNode, const std::optional<std::string>& offDays);
    static void SetDirection(FrameNode* frameNode, const std::optional<Axis>& dir);
    static void SetCurrentDayStyle(FrameNode* frameNode, const CurrentDayStyleData& dataStyle);
    static void SetNonCurrentDayStyle(FrameNode* frameNode, const NonCurrentDayStyleData& dataStyle);
    static void SetTodayStyle(FrameNode* frameNode, const TodayStyleData& dataStyle);
    static void SetWeekStyle(FrameNode* frameNode, const WeekStyleData& dataStyle);
    static void SetWorkStateStyle(FrameNode* frameNode, const WorkStateStyleData& dataStyle);
    static void SetOnSelectChange(FrameNode* frameNode, std::function<void(const std::string&)>&& selectedChangeEvent);
    static void SetOnRequestData(FrameNode* frameNode, std::function<void(const std::string&)>&& requestData);

private:
    static void Create(const CalendarData& calendarData);
    static RefPtr<FrameNode> Create();
    static void SetCurrentDayStyle(const CurrentDayStyle& currentDayStyle);
    static void SetNonCurrentDayStyle(const NonCurrentDayStyle& nonCurrentDayStyle);
    static void SetTodayStyle(const TodayStyle& todayStyle);
    static void SetWeekStyle(const WeekStyle& weekStyle);
    static void SetWorkStateStyle(const WorkStateStyle& workStateStyle);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_CALENDAR_MODEL_NG_H
