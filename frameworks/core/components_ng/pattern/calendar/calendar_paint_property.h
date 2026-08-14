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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_PAINT_PROPERTY_H

#include <cstdint>
#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/inspector_filter.h"
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
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DailyFourRowSpace, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DailyFiveRowSpace, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DailySixRowSpace, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LunarHeight, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(UnderscoreWidth, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(UnderscoreLength, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ScheduleMarkerRadius, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BoundaryRowOffset, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BoundaryColOffset, Dimension);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
    {
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("dayColor", propDayColor.value_or(Color()).ColorToString().c_str(), filter);
        json->PutExtAttr("lunarColor", propLunarColor.value_or(Color()).ColorToString().c_str(), filter);
        json->PutExtAttr("markLunarColor", propMarkLunarColor.value_or(Color()).ColorToString().c_str(), filter);
        json->PutExtAttr("dayFontSize",
            propDayFontSize.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("lunarDayFontSize",
            propLunarDayFontSize.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("dayHeight",
            propDayHeight.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("dayWidth",
            propDayWidth.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("gregorianCalendarHeight",
            propGregorianCalendarHeight.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("dayYAxisOffset",
            propDayYAxisOffset.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("lunarDayYAxisOffset",
            propLunarDayYAxisOffset.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("underscoreXAxisOffset",
            propUnderscoreXAxisOffset.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("underscoreYAxisOffset",
            propUnderscoreYAxisOffset.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("scheduleMarkerXAxisOffset",
            propScheduleMarkerXAxisOffset.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("scheduleMarkerYAxisOffset",
            propScheduleMarkerYAxisOffset.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("colSpace",
            propColSpace.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("dailyFiveRowSpace",
            propDailyFiveRowSpace.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("dailySixRowSpace",
            propDailySixRowSpace.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("lunarHeight",
            propLunarHeight.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("underscoreWidth",
            propUnderscoreWidth.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("underscoreLength",
            propUnderscoreLength.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("scheduleMarkerRadius",
            propScheduleMarkerRadius.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("boundaryRowOffset",
            propBoundaryRowOffset.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("boundaryColOffset",
            propBoundaryColOffset.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
    }
};

struct NonCurrentDayStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(NonCurrentMonthDayColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(NonCurrentMonthLunarColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(NonCurrentMonthWorkDayMarkColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(NonCurrentMonthOffDayMarkColor, Color);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
    {
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("nonCurrentMonthDayColor",
            propNonCurrentMonthDayColor.value_or(Color()).ColorToString().c_str(), filter);
        json->PutExtAttr("nonCurrentMonthLunarColor",
            propNonCurrentMonthLunarColor.value_or(Color()).ColorToString().c_str(), filter);
        json->PutExtAttr("nonCurrentMonthWorkDayMarkColor",
            propNonCurrentMonthWorkDayMarkColor.value_or(Color()).ColorToString().c_str(), filter);
        json->PutExtAttr("nonCurrentMonthOffDayMarkColor",
            propNonCurrentMonthOffDayMarkColor.value_or(Color()).ColorToString().c_str(), filter);
    }
};

struct TodayStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FocusedDayColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FocusedLunarColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FocusedAreaBackgroundColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FocusedAreaRadius, Dimension);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
    {
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("focusedDayColor", propFocusedDayColor.value_or(Color()).ColorToString().c_str(), filter);
        json->PutExtAttr("focusedLunarColor",
            propFocusedLunarColor.value_or(Color()).ColorToString().c_str(), filter);
        json->PutExtAttr("focusedAreaBackgroundColor",
            propFocusedAreaBackgroundColor.value_or(Color()).ColorToString().c_str(), filter);
        json->PutExtAttr("focusedAreaRadius",
            propFocusedAreaRadius.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
    }
};

struct WeekStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WeekColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WeekendDayColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WeekendLunarColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WeekFontSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WeekHeight, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WeekWidth, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WeekAndDayRowSpace, Dimension);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
    {
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("weekColor", propWeekColor.value_or(Color()).ColorToString().c_str(), filter);
        json->PutExtAttr("weekendDayColor", propWeekendDayColor.value_or(Color()).ColorToString().c_str(), filter);
        json->PutExtAttr("weekendLunarColor",
            propWeekendLunarColor.value_or(Color()).ColorToString().c_str(), filter);
        json->PutExtAttr("weekFontSize",
            propWeekFontSize.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("weekHeight",
            propWeekHeight.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("weekWidth",
            propWeekWidth.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("weekAndDayRowSpace",
            propWeekAndDayRowSpace.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
    }
};

struct WorkStateStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WorkDayMarkColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OffDayMarkColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WorkDayMarkSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OffDayMarkSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WorkStateWidth, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WorkStateHorizontalMovingDistance, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WorkStateVerticalMovingDistance, Dimension);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
    {
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("workDayMarkColor",
            propWorkDayMarkColor.value_or(Color()).ColorToString().c_str(), filter);
        json->PutExtAttr("offDayMarkColor", propOffDayMarkColor.value_or(Color()).ColorToString().c_str(), filter);
        json->PutExtAttr("workDayMarkSize",
            propWorkDayMarkSize.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("offDayMarkSize",
            propOffDayMarkSize.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("workStateWidth",
            propWorkStateWidth.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("workStateHorizontalMovingDistance", propWorkStateHorizontalMovingDistance.value_or(
            Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("workStateVerticalMovingDistance", propWorkStateVerticalMovingDistance.value_or(
            Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
    }
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
        value->propDayRadius_ = CloneDayRadius();
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
        ResetDayRadius();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        ACE_PROPERTY_TO_JSON_VALUE(propCurrentDayStyle_, CurrentDayStyle);
        ACE_PROPERTY_TO_JSON_VALUE(propNonCurrentDayStyle_, NonCurrentDayStyle);
        ACE_PROPERTY_TO_JSON_VALUE(propTodayStyle_, TodayStyle);
        ACE_PROPERTY_TO_JSON_VALUE(propWeekStyle_, WeekStyle);
        ACE_PROPERTY_TO_JSON_VALUE(propWorkStateStyle_, WorkStateStyle);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("showLunar", propShowLunar_.value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("showHoliday", propShowHoliday_.value_or(false) ? "true" : "false", filter);
        static const char* WEEK[] = { "Week.Mon", "Week.Tue", "Week.Wed", "Week.Tur", "Week.Fri", "Week.Sat",
            "Week.Sun" };
        json->PutExtAttr("startOfWeek", WEEK[static_cast<int32_t>(GetStartOfWeek().value_or(Week::Mon))], filter);
        const std::string DEFAULT_OFFDAYS = "5,6";
        json->PutExtAttr("offDays", propOffDays_.value_or(DEFAULT_OFFDAYS).c_str(), filter);
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
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CurrentDayStyle, DailyFourRowSpace, Dimension, PROPERTY_UPDATE_RENDER);
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
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DayRadius, Dimension, PROPERTY_UPDATE_RENDER);

    ACE_DISALLOW_COPY_AND_MOVE(CalendarPaintProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_PAINT_PROPERTY_H
