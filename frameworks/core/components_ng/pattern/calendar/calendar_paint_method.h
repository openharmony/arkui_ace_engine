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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_PAINT_METHOD_H

#include <utility>

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components/calendar/calendar_data_adapter.h"
#include "core/components/calendar/calendar_theme.h"
#include "core/components_ng/pattern/calendar/calendar_paint_property.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

class CalendarPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(CalendarPaintMethod, NodePaintMethod)

public:
    CalendarPaintMethod(ObtainedMonth& obtainedMonth, CalendarDay& calendarDay, bool isCalendarDialog = false)
        : obtainedMonth_(obtainedMonth), calendarDay_(calendarDay), isCalendarDialog_(isCalendarDialog) {};
    ~CalendarPaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;

private:
    void DrawWeekAndDates(RSCanvas& canvas, Offset offset);
    void DrawWeek(RSCanvas& canvas, const Offset& offset) const;
    void DrawDates(RSCanvas& canvas, const Offset& offset);
    void SetCalendarTheme(const RefPtr<CalendarPaintProperty>& paintProperty);
    void DrawCalendar(RSCanvas& canvas, const Offset& offset, const Offset& dayOffset, const CalendarDay& day);
    void DrawTodayArea(RSCanvas& canvas, const Offset& offset, double x, double y) const;
    void DrawFocusedArea(RSCanvas& canvas, const Offset& offset, double x, double y) const;
    void DrawCalendarPickerBackgroundArea(const CalendarDay& day, RSCanvas& canvas, double x, double y) const;
    void InitTextStyle(RSTextStyle& dateTextStyle, RSTextStyle& lunarTextStyle);
    void SetDayTextStyle(RSTextStyle& dateTextStyle, RSTextStyle& lunarTextStyle, const CalendarDay& day);
    void SetCalendarPickerDayTextStyle(RSTextStyle& dateTextStyle, const CalendarDay& day);
    void SetOffWorkTextStyle(RSTextStyle& offWorkTextStyle, const CalendarDay& day) const;
    void PaintDay(RSCanvas& canvas, const Offset& offset, const CalendarDay& day, RSTextStyle& textStyle) const;
    void PaintLunarDay(
        RSCanvas& canvas, const Offset& offset, const CalendarDay& day, const RSTextStyle& textStyle) const;
    void PaintContent(RSCanvas& canvas, const RefPtr<CalendarPaintProperty>& paintProperty);
    bool IsOffDay(const CalendarDay& dayInfo) const;
    bool IsToday(const CalendarDay& day) const;

    Offset offset_;
    std::string offDays_ = "5,6";
    ObtainedMonth obtainedMonth_;
    CalendarDay calendarDay_;
    std::vector<std::string> weekNumbers_;
    std::vector<CalendarDay> calendarDays_;
    CalendarMonth currentMonth_;
    TextDirection textDirection_ = TextDirection::LTR;
    bool showHoliday_ = true;
    bool showLunar_ = false;
    bool isCalendarDialog_ = false;
    int32_t startOfWeek_ = 64;

    // Default it exists 5 weeks in a month.
    int32_t rowCount_ = 5;

    // Day style
    double dayWidth_ = 0.0;
    double dayHeight_ = 0.0;
    double dayFontSize_ = 0.0;

    // Week style
    double weekWidth_ = 0.0;
    double weekHeight_ = 0.0;
    double weekFontSize_ = 0.0;

    double lunarDayFontSize_ = 0.0;
    double workDayMarkSize_ = 0.0;
    double offDayMarkSize_ = 0.0;
    double focusedAreaRadius_ = 0.0;
    double topPadding_ = 0.0;
    double weekAndDayRowSpace_ = 0.0;

    double workStateWidth_ = 0.0;
    double workStateHorizontalMovingDistance_ = 0.0;
    double workStateVerticalMovingDistance_ = 0.0;
    double touchCircleStrokeWidth_ = 0.0;

    // GregorianDay YAxis Offset and Height.
    double gregorianDayYAxisOffset_ = 0.0;
    double gregorianDayHeight_ = 0.0;

    // LunarDay YAxis Offset and Height.
    double lunarDayYAxisOffset_ = 0.0;
    double lunarDayHeight_ = 0.0;

    // Space for days of calendar, when the days cross 5 weeks, it needs 6 rows.
    // So use dailyFiveRowSpace_ for 5 rows and dailySixRowSpace_ for 6 rows.
    // The column is always 7 from Monday to Sunday. So just set colSpace_.
    double colSpace_ = 0.0;
    double dailyFourRowSpace_ = 0.0;
    double dailyFiveRowSpace_ = 0.0;
    double dailySixRowSpace_ = 0.0;

    double dayRadius_ = 0.0;

    double calendarDayKeyFocusedWidth_ = 0.0;
    double calendarDayKeyFocusedPenWidth_ = 0.0;

    RSColor weekColor_;
    RSColor dayColor_;
    RSColor lunarColor_;
    RSColor weekendDayColor_;
    RSColor weekendLunarColor_;
    RSColor todayDayColor_;
    RSColor todayLunarColor_;
    RSColor nonCurrentMonthDayColor_;
    RSColor nonCurrentMonthLunarColor_;
    RSColor workDayMarkColor_;
    RSColor offDayMarkColor_;
    RSColor nonCurrentMonthWorkDayMarkColor_;
    RSColor nonCurrentMonthOffDayMarkColor_;
    RSColor focusedDayColor_;
    RSColor focusedLunarColor_;
    RSColor focusedAreaBackgroundColor_;
    RSColor markLunarColor_;
    RSColor textNonCurrentMonthColor_;
    RSColor textSelectedDayColor_;
    RSColor textCurrentDayColor_;
    RSColor textCurrentMonthColor_;
    RSColor backgroundKeyFocusedColor_;
    RSColor backgroundSelectedTodayColor_;
    RSColor backgroundSelectedNotTodayColor_;
    RSColor backgroundHoverColor_;
    RSColor backgroundPressColor_;
    FontWeight dayFontWeight_ = FontWeight::W500;
    FontWeight lunarDayFontWeight_ = FontWeight::W500;
    FontWeight workStateFontWeight_ = FontWeight::W400;
    SizeF frameSize_;

    std::vector<std::string> appFontFamilies_;

    ACE_DISALLOW_COPY_AND_MOVE(CalendarPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_PAINT_METHOD_H
