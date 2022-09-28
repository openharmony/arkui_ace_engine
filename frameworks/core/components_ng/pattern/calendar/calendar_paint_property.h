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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_PAINT_PROPERTY_H

#include <stdint.h>
#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {

struct CurrentDayStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DayColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LunarColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MarkLunarColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DayFontSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LunarDayFontSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DayHeight, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DayWidth, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(GregorianCalendarHeight, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DayYAxisOffset, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LunarDayYAxisOffset, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(UnderscoreXAxisOffset, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(UnderscoreYAxisOffset, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ScheduleMarkerXAxisOffset, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ScheduleMarkerYAxisOffset, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ColSpace, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DailyFiveRowSpace, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DailySixRowSpace, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LunarHeight, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(UnderscoreWidth, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(UnderscoreLength, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ScheduleMarkerRadius, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BoundaryRowOffset, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BoundaryColOffset, Dimension);
};

struct NonCurrentDayStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(NonCurrentMonthDayColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(NonCurrentMonthLunarColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(NonCurrentMonthWorkDayMarkColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(NonCurrentMonthOffDayMarkColor, Color);
};

struct TodayStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FocusedDayColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FocusedLunarColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FocusedAreaBackgroundColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FocusedAreaRadius, Dimension);
};

struct WeekStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WeekColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WeekendDayColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WeekendLunarColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WeekFontSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WeekHeight, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WeekWidth, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WeekAndDayRowSpace, Dimension);
};

struct WorkStateStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WorkDayMarkColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OffDayMarkColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WorkDayMarkSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OffDayMarkSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WorkStateWidth, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WorkStateHorizontalMovingDistance, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WorkStateVerticalMovingDistance, Dimension);
};

enum class Week {
    Mon = 0,
    Tue,
    Wed,
    Thur,
    Fri,
    Sat,
    Sun,
};

class ACE_EXPORT CalendarPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(CalendarPaintProperty, PaintProperty);

public:
    CalendarPaintProperty() = default;

    ~CalendarPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto value = MakeRefPtr<CalendarPaintProperty>();
        value->PaintProperty::UpdatePaintProperty(DynamicCast<PaintProperty>(this));
        value->propCurrentDayStyle_ = CloneCurrentDayStyle();
        value->propNonCurrentDayStyle_ = CloneNonCurrentDayStyle();
        value->propTodayStyle_ = CloneTodayStyle();
        value->propWeekStyle_ = CloneWeekStyle();
        value->propWorkStateStyle_ = CloneWorkStateStyle();
        value->propShowLunar_ = CloneShowLunar();
        value->propShowHoliday_ = CloneShowHoliday();
        value->propStartOfWeek_ = CloneStartOfWeek();
        value->propOffDays_ = CloneOffDays();
        return value;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetCurrentDayStyle();
        ResetNonCurrentDayStyle();
        ResetTodayStyle();
        ResetWeekStyle();
        ResetWorkStateStyle();
        ResetShowLunar();
        ResetShowHoliday();
        ResetStartOfWeek();
        ResetOffDays();
    }

    ACE_DEFINE_PROPERTY_GROUP(CurrentDayStyle, CurrentDayStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, DayColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, LunarColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, MarkLunarColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, DayFontSize, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, LunarDayFontSize, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, DayHeight, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, DayWidth, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, GregorianCalendarHeight, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, DayYAxisOffset, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, LunarDayYAxisOffset, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, UnderscoreXAxisOffset, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, UnderscoreYAxisOffset, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, ScheduleMarkerXAxisOffset, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, ScheduleMarkerYAxisOffset, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, ColSpace, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, DailyFiveRowSpace, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, DailySixRowSpace, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, LunarHeight, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, UnderscoreWidth, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, UnderscoreLength, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, ScheduleMarkerRadius, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, BoundaryRowOffset, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, BoundaryColOffset, Dimension, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_GROUP(NonCurrentDayStyle, NonCurrentDayStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(NonCurrentDayStyle, NonCurrentMonthDayColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(NonCurrentDayStyle, NonCurrentMonthLunarColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        NonCurrentDayStyle, NonCurrentMonthWorkDayMarkColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        NonCurrentDayStyle, NonCurrentMonthOffDayMarkColor, Color, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_GROUP(TodayStyle, TodayStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TodayStyle, FocusedDayColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TodayStyle, FocusedLunarColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TodayStyle, FocusedAreaBackgroundColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TodayStyle, FocusedAreaRadius, Dimension, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_GROUP(WeekStyle, WeekStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(WeekStyle, WeekColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(WeekStyle, WeekendDayColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(WeekStyle, WeekendLunarColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(WeekStyle, WeekFontSize, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(WeekStyle, WeekHeight, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(WeekStyle, WeekWidth, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(WeekStyle, WeekAndDayRowSpace, Dimension, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_GROUP(WorkStateStyle, WorkStateStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(WorkStateStyle, WorkDayMarkColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(WorkStateStyle, OffDayMarkColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(WorkStateStyle, WorkDayMarkSize, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(WorkStateStyle, OffDayMarkSize, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(WorkStateStyle, WorkStateWidth, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        WorkStateStyle, WorkStateHorizontalMovingDistance, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        WorkStateStyle, WorkStateVerticalMovingDistance, Dimension, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowLunar, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowHoliday, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StartOfWeek, Week, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(OffDays, std::string, PROPERTY_UPDATE_RENDER);

    ACE_DISALLOW_COPY_AND_MOVE(CalendarPaintProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_PAINT_PROPERTY_H