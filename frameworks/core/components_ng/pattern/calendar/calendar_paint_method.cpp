/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/calendar/calendar_paint_method.h"

#include <cstdint>

#include "base/geometry/ng/rect_t.h"
#include "base/geometry/offset.h"
#include "base/geometry/point.h"
#include "base/i18n/localization.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/common/font_manager.h"
#include "core/components/calendar/calendar_theme.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/calendar/calendar_pattern.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {

namespace {

const char ELLIPSIS[] = "...";
constexpr int32_t ROW_COUNT_FOUR = 4;
constexpr int32_t ROW_COUNT_FIVE = 5;
constexpr int32_t ROW_COUNT_SIX = 6;
constexpr int32_t TEXT_MAX_LENGTH = 3;
constexpr int32_t TEXT_END_INDEX = 2;
constexpr int32_t WEEK_TEXT_END_INDEX = 3;
constexpr double WEEKEND_TRANSPARENT = 0x7D;
constexpr Dimension CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT = 4.0_vp;
constexpr double DEVICE_HEIGHT_LIMIT = 640.0;

std::unique_ptr<RSParagraph> GetTextParagraph(const std::string& text, const RSTextStyle& textStyle)
{
    RSParagraphStyle style;
#ifndef USE_GRAPHIC_TEXT_GINE
    auto fontCollection = RSFontCollection::GetInstance(false);
#else
    auto fontCollection = RSFontCollection::Create();
#endif
    CHECK_NULL_RETURN(fontCollection, nullptr);
#ifndef USE_GRAPHIC_TEXT_GINE
    std::unique_ptr<RSParagraphBuilder> builder = RSParagraphBuilder::CreateRosenBuilder(style, fontCollection);
#else
    std::unique_ptr<RSParagraphBuilder> builder = RSParagraphBuilder::Create(style, fontCollection);
#endif
    builder->PushStyle(textStyle);
#ifndef USE_GRAPHIC_TEXT_GINE
    builder->AddText(StringUtils::Str8ToStr16(text));
    return builder->Build();
#else
    builder->AppendText(StringUtils::Str8ToStr16(text));
    return builder->CreateTypography();
#endif
}

void DrawCalendarText(
    RSCanvas* canvas, const std::string& text, const RSTextStyle& textStyle, const Rect& boxRect, Rect& textRect)
{
    // The lunar calendar description is truncated by more than three characters.
    std::string newText { text };
    auto wText = StringUtils::ToWstring(text);
    if (wText.size() > TEXT_MAX_LENGTH) {
        wText = wText.substr(0, TEXT_END_INDEX);
        newText = StringUtils::ToString(wText);
        newText += ELLIPSIS;
    }

    auto paragraph = GetTextParagraph(newText, textStyle);
    CHECK_NULL_VOID(paragraph);
    const auto& offset = boxRect.GetOffset();
    paragraph->Layout(boxRect.Width());
    double textWidth = paragraph->GetMaxIntrinsicWidth();
    double textHeight = paragraph->GetHeight();
    // paint text in center of item
    double textPaintOffsetX = (boxRect.Width() - textWidth) / 2.0;
    double textPaintOffsetY = (boxRect.Height() - textHeight) / 2.0;
    paragraph->Paint(canvas, offset.GetX() + textPaintOffsetX, offset.GetY() + textPaintOffsetY);
    textRect.SetRect(offset.GetX() + textPaintOffsetX, offset.GetY() + textPaintOffsetY, textWidth, textHeight);
}

void DrawCalendarText(RSCanvas* canvas, const std::string& text, const RSTextStyle& textStyle, const Rect& boxRect)
{
    Rect textRect;
    DrawCalendarText(canvas, text, textStyle, boxRect, textRect);
}

} // namespace

CanvasDrawFunction CalendarPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    auto calendarNode = renderContext->GetHost();
    CHECK_NULL_RETURN(calendarNode, nullptr);
    textDirection_ = calendarNode->GetLayoutProperty()->GetNonAutoLayoutDirection();

    auto paintProperty = DynamicCast<CalendarPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_RETURN(paintProperty, nullptr);
    frameSize_ = paintWrapper->GetGeometryNode()->GetFrameSize();
    auto paintFunc = [weak = WeakClaim(this), paintProperty](RSCanvas& canvas) {
        auto calendar_ = weak.Upgrade();
        if (calendar_) {
            calendar_->PaintContent(canvas, paintProperty);
        }
    };
    return paintFunc;
}

void CalendarPaintMethod::PaintContent(RSCanvas& canvas, const RefPtr<CalendarPaintProperty>& paintProperty)
{
    SetCalendarTheme(paintProperty);
    DrawWeekAndDates(canvas, offset_);
}

void CalendarPaintMethod::DrawWeekAndDates(RSCanvas& canvas, Offset offset)
{
    weekNumbers_ = Localization::GetInstance()->GetWeekdays(true);
    if (!obtainedMonth_.days.empty()) {
        calendarDays_.assign(obtainedMonth_.days.begin(), obtainedMonth_.days.end());
    }
    offset += (isCalendarDialog_ ? Offset(CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT.ConvertToPx(), 0)
                                 : Offset(touchCircleStrokeWidth_, 0));
    if (calendarDays_.empty()) {
        return;
    }
    DrawDates(canvas, offset);
}

void CalendarPaintMethod::DrawDates(RSCanvas& canvas, const Offset& offset)
{
    uint32_t totalWeek = weekNumbers_.size();
    int32_t dateNumber = 0;
    double dailyRowSpace = 0.0;
    double dayNumberStartY = 0.0;
    bool isTextHeightSmaller = IsTextHeightSmaller();
    if (isTextHeightSmaller) {
        dayNumberStartY = weekHeight_ + weekAndDayRowSpace_ - gregorianDayHeight_;
    } else {
        dayNumberStartY = weekAndDayRowSpace_;
    }
    // Set the rowCount.
    if (totalWeek != 0) {
        rowCount_ = static_cast<int32_t>(calendarDays_.size() / totalWeek);
    }

    // Set dailyFourRowSpace_ for four line calendar.
    // Set dailyFiveRowSpace_ for five line calendar.
    // Set dailySixRowSpace_ for six line calendar.
    switch (rowCount_) {
        case ROW_COUNT_FOUR: {
            dailyRowSpace = dailyFourRowSpace_;
            break;
        }
        case ROW_COUNT_SIX: {
            dailyRowSpace = dailySixRowSpace_;
            break;
        }
        case ROW_COUNT_FIVE:
        default:
            dailyRowSpace = dailyFiveRowSpace_;
            break;
    }

    for (int32_t row = 0; row < rowCount_; row++) {
        double y = row * (dayHeight_ + dailyRowSpace) + dayNumberStartY;
        for (uint32_t column = 0; column < totalWeek; column++) {
            const auto& day = calendarDays_[dateNumber++];
            double x = textDirection_ == TextDirection::LTR ? column * (dayWidth_ + colSpace_)
                                                            : (totalWeek - column - 1) * (dayWidth_ + colSpace_);
            auto dayOffset = Offset(x, y);
            DrawCalendar(canvas, offset, dayOffset, day);
        }
    }
}

bool CalendarPaintMethod::IsTextHeightSmaller()
{
    uint32_t totalWeek = weekNumbers_.size();
    int32_t dateNumber = 0;
    double dailyRowSpace = 0.0;
    if (totalWeek == 0) {
        return false;
    }
    auto rowCount = static_cast<int32_t>(calendarDays_.size() / totalWeek);
    switch (rowCount) {
        case ROW_COUNT_FOUR: {
            dailyRowSpace = dailyFourRowSpace_;
            break;
        }
        case ROW_COUNT_SIX: {
            dailyRowSpace = dailySixRowSpace_;
            break;
        }
        case ROW_COUNT_FIVE:
        default:
            dailyRowSpace = dailyFiveRowSpace_;
            break;
    }

    double y = dayHeight_ + dailyRowSpace;
    double x = 0.0;
    if (calendarDays_.size() == 0) {
        return false;
    }
    const auto& day = calendarDays_[dateNumber];
    auto dayOffset = Offset(x, y);
    return CalTextHeight(dayOffset, day);
}

bool CalendarPaintMethod::CalTextHeight(const Offset& dayOffset, const CalendarDay& day)
{
    double x = dayOffset.GetX();
    double y = dayOffset.GetY();
    RSTextStyle dateTextStyle;
    RSTextStyle lunarTextStyle;
    InitTextStyle(dateTextStyle, lunarTextStyle);
#ifndef USE_GRAPHIC_TEXT_GINE
    dateTextStyle.locale_ = Localization::GetInstance()->GetFontLocale();
    lunarTextStyle.locale_ = Localization::GetInstance()->GetFontLocale();
#else
    dateTextStyle.locale = Localization::GetInstance()->GetFontLocale();
    lunarTextStyle.locale = Localization::GetInstance()->GetFontLocale();
#endif
    Offset dateNumberOffset = Offset(x, y + (dayHeight_ / 2 - gregorianDayHeight_ / 2));
    Rect boxRect { dateNumberOffset.GetX(), dateNumberOffset.GetY(), dayWidth_, gregorianDayHeight_ };
    auto dayStr = std::to_string(day.day);
    dayStr = Localization::GetInstance()->NumberFormat(day.day);
    std::string newText { dayStr };
    auto wText = StringUtils::ToWstring(dayStr);
    if (wText.size() > TEXT_MAX_LENGTH) {
        wText = wText.substr(0, TEXT_END_INDEX);
        newText = StringUtils::ToString(wText);
        newText += ELLIPSIS;
    }
    bool isTextHeightSmaller = true;
    auto paragraph = GetTextParagraph(newText, dateTextStyle);
    CHECK_NULL_RETURN(paragraph, isTextHeightSmaller);
    const auto& offset = boxRect.GetOffset();
    paragraph->Layout(boxRect.Width());
    double textHeight = paragraph->GetHeight();
    double textPaintOffsetY = boxRect.Height() - textHeight;
    if (textPaintOffsetY < 0) {
        isTextHeightSmaller = false;
    }
    return isTextHeightSmaller;
}

void CalendarPaintMethod::DrawCalendar(
    RSCanvas& canvas, const Offset& offset, const Offset& dayOffset, const CalendarDay& day)
{
    RSTextStyle dateTextStyle;
    RSTextStyle lunarTextStyle;
    InitTextStyle(dateTextStyle, lunarTextStyle);
#ifndef USE_GRAPHIC_TEXT_GINE
    dateTextStyle.locale_ = Localization::GetInstance()->GetFontLocale();
    lunarTextStyle.locale_ = Localization::GetInstance()->GetFontLocale();
#else
    dateTextStyle.locale = Localization::GetInstance()->GetFontLocale();
    lunarTextStyle.locale = Localization::GetInstance()->GetFontLocale();
#endif

    auto x = dayOffset.GetX();
    auto y = dayOffset.GetY();

    if (isCalendarDialog_) {
        x += CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT.ConvertToPx();
        SetCalendarPickerDayTextStyle(dateTextStyle, day);
        DrawCalendarPickerBackgroundArea(day, canvas, x, y);

        Offset dateNumberOffset = Offset(x, y + (dayHeight_ / 2 - gregorianDayHeight_ / 2));
        PaintDay(canvas, dateNumberOffset, day, dateTextStyle);
        return;
    }

    // First of all, check whether the day is current month or not, and set text style.
    SetDayTextStyle(dateTextStyle, lunarTextStyle, day);

    if (day.focused && day.month.month == currentMonth_.month) {
        if (IsToday(day)) {
            DrawTodayArea(canvas, offset, x, y);
        } else {
            DrawFocusedArea(canvas, offset, x, y);
        }
    }

    if (showLunar_ && !day.lunarDay.empty()) {
        // paint day
        Offset dateNumberOffset = offset + Offset(x, y + gregorianDayYAxisOffset_);
        PaintDay(canvas, dateNumberOffset, day, dateTextStyle);

        // paint lunar day
        Offset lunarDayOffset = offset + Offset(x, y + lunarDayYAxisOffset_);
        PaintLunarDay(canvas, lunarDayOffset, day, lunarTextStyle);
    } else {
        // when there is no lunar calendar, the date is displayed in the center
        Offset dateNumberOffset = offset + Offset(x, y + (focusedAreaRadius_ - gregorianDayHeight_ / 2));
        PaintDay(canvas, dateNumberOffset, day, dateTextStyle);
    }
}

void CalendarPaintMethod::DrawTodayArea(RSCanvas& canvas, const Offset& offset, double x, double y) const
{
    // draw Today background circle
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(focusedAreaBackgroundColor_);
    canvas.AttachBrush(brush);

    Offset circleCenter = Offset(x - (focusedAreaRadius_ * 2 - dayWidth_) / 2 + focusedAreaRadius_,
        y - (1.0_vp).ConvertToPx() + focusedAreaRadius_);
    Offset bgCircleStart = offset + circleCenter;
    canvas.DrawCircle(RSPoint(static_cast<float>(bgCircleStart.GetX()), static_cast<float>(bgCircleStart.GetY())),
        static_cast<float>(focusedAreaRadius_));
    canvas.DetachBrush();
}

void CalendarPaintMethod::DrawFocusedArea(RSCanvas& canvas, const Offset& offset, double x, double y) const
{
    // draw focus background circle
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetColor(focusedAreaBackgroundColor_);
    canvas.AttachPen(pen);

    Offset circleCenter = Offset(x - (focusedAreaRadius_ * 2 - dayWidth_) / 2 + focusedAreaRadius_,
        y - (1.0_vp).ConvertToPx() + focusedAreaRadius_);
    Offset bgCircleStart = offset + circleCenter;
    canvas.DrawCircle(RSPoint(static_cast<float>(bgCircleStart.GetX()), static_cast<float>(bgCircleStart.GetY())),
        static_cast<float>(focusedAreaRadius_));
    canvas.DetachPen();
}

void CalendarPaintMethod::DrawCalendarPickerBackgroundArea(
    const CalendarDay& day, RSCanvas& canvas, double x, double y) const
{
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(Color::TRANSPARENT));
    if (day.month.year == obtainedMonth_.year && day.month.month == obtainedMonth_.month) {
        if (day.isSelected) {
            brush.SetColor(IsToday(day) ? backgroundSelectedTodayColor_ : backgroundSelectedNotTodayColor_);
        } else if (day.isPressing) {
            brush.SetColor(backgroundPressColor_);
        } else if (day.isHovering) {
            brush.SetColor(backgroundHoverColor_);
        }
    }

    canvas.AttachBrush(brush);
    RSRect rect(static_cast<float>(x), static_cast<float>(y), static_cast<float>(x + dayWidth_),
        static_cast<float>(y + dayHeight_));
    auto rrect = RSRoundRect(rect, dayRadius_, dayRadius_);
    canvas.DrawRoundRect(rrect);
    canvas.DetachBrush();

    if (day.isKeyFocused) {
        RSPen pen;
        pen.SetAntiAlias(true);
        pen.SetColor(backgroundKeyFocusedColor_);
        pen.SetWidth(calendarDayKeyFocusedPenWidth_);
        canvas.AttachPen(pen);

        auto focusedX = x - (calendarDayKeyFocusedWidth_ - dayWidth_) / 2 - calendarDayKeyFocusedPenWidth_ / 2;
        auto focusedY = y - (calendarDayKeyFocusedWidth_ - dayWidth_) / 2 - calendarDayKeyFocusedPenWidth_ / 2;
        RSRect keyFocusedrect(static_cast<float>(focusedX), static_cast<float>(focusedY),
            static_cast<float>(focusedX + calendarDayKeyFocusedWidth_ + calendarDayKeyFocusedPenWidth_),
            static_cast<float>(focusedY + calendarDayKeyFocusedWidth_ + calendarDayKeyFocusedPenWidth_));
        auto keyFocusedrrect = RSRoundRect(keyFocusedrect,
            dayRadius_ / dayWidth_ * (calendarDayKeyFocusedWidth_ + calendarDayKeyFocusedPenWidth_),
            dayRadius_ / dayWidth_ * (calendarDayKeyFocusedWidth_ + calendarDayKeyFocusedPenWidth_));
        canvas.DrawRoundRect(keyFocusedrrect);
        canvas.DetachPen();
    }
}

void CalendarPaintMethod::InitTextStyle(RSTextStyle& dateTextStyle, RSTextStyle& lunarTextStyle)
{
#ifndef USE_GRAPHIC_TEXT_GINE
    dateTextStyle.fontSize_ = dayFontSize_;
    dateTextStyle.fontWeight_ = static_cast<RSFontWeight>(dayFontWeight_);

    lunarTextStyle.fontSize_ = lunarDayFontSize_;
    lunarTextStyle.fontWeight_ = static_cast<RSFontWeight>(lunarDayFontWeight_);

    if (!appFontFamilies_.empty()) {
        dateTextStyle.fontFamilies_ = appFontFamilies_;
        lunarTextStyle.fontFamilies_ = appFontFamilies_;
    }
#else
    dateTextStyle.fontSize = dayFontSize_;
    dateTextStyle.fontWeight = static_cast<RSFontWeight>(dayFontWeight_);

    lunarTextStyle.fontSize = lunarDayFontSize_;
    lunarTextStyle.fontWeight = static_cast<RSFontWeight>(lunarDayFontWeight_);

    if (!appFontFamilies_.empty()) {
        dateTextStyle.fontFamilies = appFontFamilies_;
        lunarTextStyle.fontFamilies = appFontFamilies_;
    }
#endif
}

void CalendarPaintMethod::SetDayTextStyle(
    RSTextStyle& dateTextStyle, RSTextStyle& lunarTextStyle, const CalendarDay& day)
{
    // Set the noncurrent month style and current month style.
    if (day.month.month != currentMonth_.month) {
#ifndef USE_GRAPHIC_TEXT_GINE
        dateTextStyle.color_ = nonCurrentMonthDayColor_;
        lunarTextStyle.color_ = day.markLunarDay ? RSColor(markLunarColor_.GetRed(), markLunarColor_.GetGreen(),
            markLunarColor_.GetBlue(), WEEKEND_TRANSPARENT) : nonCurrentMonthLunarColor_;
#else
        dateTextStyle.color = nonCurrentMonthDayColor_;
        lunarTextStyle.color = day.markLunarDay ? RSColor(markLunarColor_.GetRed(), markLunarColor_.GetGreen(),
            markLunarColor_.GetBlue(), WEEKEND_TRANSPARENT) : nonCurrentMonthLunarColor_;
#endif
    } else {
#ifndef USE_GRAPHIC_TEXT_GINE
        dateTextStyle.color_ = (IsToday(day) && day.focused) ? focusedDayColor_
                               : IsToday(day)                ? todayDayColor_
                               : IsOffDay(day)               ? weekendDayColor_
                                                             : dayColor_;
        lunarTextStyle.color_ =
            (IsToday(day) && day.focused) ? focusedLunarColor_
            : IsToday(day)                ? todayLunarColor_
                           : (day.markLunarDay ? markLunarColor_ : (IsOffDay(day) ? weekendLunarColor_ : lunarColor_));
#else
        dateTextStyle.color = (IsToday(day) && day.focused) ? focusedDayColor_
                               : IsToday(day)                ? todayDayColor_
                               : IsOffDay(day)               ? weekendDayColor_
                                                             : dayColor_;
        lunarTextStyle.color =
            (IsToday(day) && day.focused) ? focusedLunarColor_
            : IsToday(day)                ? todayLunarColor_
                           : (day.markLunarDay ? markLunarColor_ : (IsOffDay(day) ? weekendLunarColor_ : lunarColor_));
#endif
    }
}

void CalendarPaintMethod::SetCalendarPickerDayTextStyle(RSTextStyle& dateTextStyle, const CalendarDay& day)
{
    if (day.month.month != currentMonth_.month) {
#ifndef USE_GRAPHIC_TEXT_GINE
        dateTextStyle.color_ = textNonCurrentMonthColor_;
#else
        dateTextStyle.color = textNonCurrentMonthColor_;
#endif
    } else {
        if (IsToday(day)) {
#ifndef USE_GRAPHIC_TEXT_GINE
            dateTextStyle.color_ = day.isSelected ? textSelectedDayColor_ : textCurrentDayColor_;
#else
            dateTextStyle.color = day.isSelected ? textSelectedDayColor_ : textCurrentDayColor_;
#endif
        } else {
#ifndef USE_GRAPHIC_TEXT_GINE
            dateTextStyle.color_ = textCurrentMonthColor_;
#else
            dateTextStyle.color = textCurrentMonthColor_;
#endif
        }
    }
}

void CalendarPaintMethod::SetOffWorkTextStyle(RSTextStyle& offWorkTextStyle, const CalendarDay& day) const
{
    // Paint off or work mark value.
#ifndef USE_GRAPHIC_TEXT_GINE
    offWorkTextStyle.fontWeight_ = static_cast<RSFontWeight>(workStateFontWeight_);
    offWorkTextStyle.locale_ = Localization::GetInstance()->GetFontLocale();

    if (!appFontFamilies_.empty()) {
        offWorkTextStyle.fontFamilies_ = appFontFamilies_;
    }
#else
    offWorkTextStyle.fontWeight = static_cast<RSFontWeight>(workStateFontWeight_);
    offWorkTextStyle.locale = Localization::GetInstance()->GetFontLocale();

    if (!appFontFamilies_.empty()) {
        offWorkTextStyle.fontFamilies = appFontFamilies_;
    }
#endif
    if (day.month.month == currentMonth_.month) {
        if (day.dayMark == "work") {
#ifndef USE_GRAPHIC_TEXT_GINE
            offWorkTextStyle.fontSize_ = workDayMarkSize_;
            offWorkTextStyle.color_ = workDayMarkColor_;
#else
            offWorkTextStyle.fontSize = workDayMarkSize_;
            offWorkTextStyle.color = workDayMarkColor_;
#endif
        } else if (day.dayMark == "off") {
#ifndef USE_GRAPHIC_TEXT_GINE
            offWorkTextStyle.fontSize_ = offDayMarkSize_;
            offWorkTextStyle.color_ = offDayMarkColor_;
#else
            offWorkTextStyle.fontSize = offDayMarkSize_;
            offWorkTextStyle.color = offDayMarkColor_;
#endif
        }
    } else {
        if (day.dayMark == "work") {
#ifndef USE_GRAPHIC_TEXT_GINE
            offWorkTextStyle.fontSize_ = workDayMarkSize_;
            offWorkTextStyle.color_ =
                RSColor(nonCurrentMonthWorkDayMarkColor_.GetRed(), nonCurrentMonthWorkDayMarkColor_.GetGreen(),
                    nonCurrentMonthWorkDayMarkColor_.GetBlue(), WEEKEND_TRANSPARENT);
#else
            offWorkTextStyle.fontSize = workDayMarkSize_;
            offWorkTextStyle.color =
                RSColor(nonCurrentMonthWorkDayMarkColor_.GetRed(), nonCurrentMonthWorkDayMarkColor_.GetGreen(),
                    nonCurrentMonthWorkDayMarkColor_.GetBlue(), WEEKEND_TRANSPARENT);
#endif
        } else if (day.dayMark == "off") {
#ifndef USE_GRAPHIC_TEXT_GINE
            offWorkTextStyle.fontSize_ = offDayMarkSize_;
            offWorkTextStyle.color_ =
                RSColor(nonCurrentMonthOffDayMarkColor_.GetRed(), nonCurrentMonthOffDayMarkColor_.GetGreen(),
                    nonCurrentMonthOffDayMarkColor_.GetBlue(), WEEKEND_TRANSPARENT);
#else
            offWorkTextStyle.fontSize = offDayMarkSize_;
            offWorkTextStyle.color =
                RSColor(nonCurrentMonthOffDayMarkColor_.GetRed(), nonCurrentMonthOffDayMarkColor_.GetGreen(),
                    nonCurrentMonthOffDayMarkColor_.GetBlue(), WEEKEND_TRANSPARENT);
#endif
        }
    }

    // If it is today and it is focused, workState color is same as focused day color.
    if (IsToday(day) && day.focused) {
#ifndef USE_GRAPHIC_TEXT_GINE
        offWorkTextStyle.color_ = focusedDayColor_;
#else
        offWorkTextStyle.color = focusedDayColor_;
#endif
    }
}

void CalendarPaintMethod::PaintDay(
    RSCanvas& canvas, const Offset& offset, const CalendarDay& day, RSTextStyle& textStyle) const
{
    // Paint day value.
    Rect boxRect { offset.GetX(), offset.GetY(), dayWidth_, gregorianDayHeight_ };
    Rect textRect;

    auto dayStr = std::to_string(day.day);
    dayStr = Localization::GetInstance()->NumberFormat(day.day);
    DrawCalendarText(&canvas, dayStr, textStyle, boxRect, textRect);

    // Paint off and work mark value.
    if (!day.dayMark.empty() && showHoliday_) {
        RSTextStyle workStateStyle;
        boxRect = { textRect.GetOffset().GetX() + textRect.Width() - workStateHorizontalMovingDistance_,
            textRect.GetOffset().GetY() + textRect.Height() - workStateVerticalMovingDistance_, workStateWidth_,
            workStateWidth_ };
        SetOffWorkTextStyle(workStateStyle, day);
        DrawCalendarText(&canvas, day.dayMarkValue, workStateStyle, boxRect);
    }
}

void CalendarPaintMethod::PaintLunarDay(
    RSCanvas& canvas, const Offset& offset, const CalendarDay& day, const RSTextStyle& textStyle) const
{
    Rect boxRect = { offset.GetX(), offset.GetY(), dayWidth_, lunarDayHeight_ };
    DrawCalendarText(&canvas, day.lunarDay, textStyle, boxRect);
}

void CalendarPaintMethod::DrawWeek(RSCanvas& canvas, const Offset& offset) const
{
    uint32_t totalWeek = weekNumbers_.size();
    RSTextStyle weekTextStyle;
#ifndef USE_GRAPHIC_TEXT_GINE
    weekTextStyle.color_ = weekColor_;
    weekTextStyle.fontSize_ = weekFontSize_;
    weekTextStyle.locale_ = Localization::GetInstance()->GetFontLocale();

    if (!appFontFamilies_.empty()) {
        weekTextStyle.fontFamilies_ = appFontFamilies_;
    }
#else
    weekTextStyle.color = weekColor_;
    weekTextStyle.fontSize = weekFontSize_;
    weekTextStyle.locale = Localization::GetInstance()->GetFontLocale();

    if (!appFontFamilies_.empty()) {
        weekTextStyle.fontFamilies = appFontFamilies_;
    }
#endif
    static const int32_t daysOfWeek = 7;

    auto startDayOfWeek = startOfWeek_;
    for (uint32_t column = 0; column < totalWeek; column++) {
        double x = textDirection_ == TextDirection::LTR ? column * (weekWidth_ + colSpace_)
                                                        : (totalWeek - column - 1) * (weekWidth_ + colSpace_);
        Offset weekNumberOffset = offset + Offset(x, topPadding_);
        Rect boxRect { weekNumberOffset.GetX(), weekNumberOffset.GetY(), weekWidth_, weekHeight_ };
        std::string newText { weekNumbers_[(startDayOfWeek + 1) % daysOfWeek] };
        auto wText = StringUtils::ToWstring(newText);
        if (wText.size() > TEXT_MAX_LENGTH) {
            wText = wText.substr(0, WEEK_TEXT_END_INDEX);
            newText = StringUtils::ToString(wText);
        }
        DrawCalendarText(&canvas, newText, weekTextStyle, boxRect);
        ++startDayOfWeek;
    }
}

void CalendarPaintMethod::SetCalendarTheme(const RefPtr<CalendarPaintProperty>& paintProperty)
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);

    auto fontManager = pipelineContext->GetFontManager();
    if (fontManager && !(fontManager->GetAppCustomFont().empty())) {
        appFontFamilies_ = Framework::ConvertStrToFontFamilies(fontManager->GetAppCustomFont());
    }

    weekColor_ = ToRSColor(paintProperty->GetWeekColor().value_or(theme->GetCalendarTheme().weekColor));
    dayColor_ = ToRSColor(paintProperty->GetDayColor().value_or(theme->GetCalendarTheme().dayColor));
    lunarColor_ = ToRSColor(paintProperty->GetLunarColor().value_or(theme->GetCalendarTheme().lunarColor));
    weekendDayColor_ =
        ToRSColor(paintProperty->GetWeekendDayColor().value_or(theme->GetCalendarTheme().weekendDayColor));
    weekendLunarColor_ =
        ToRSColor(paintProperty->GetWeekendLunarColor().value_or(theme->GetCalendarTheme().weekendLunarColor));
    nonCurrentMonthDayColor_ = ToRSColor(
        paintProperty->GetNonCurrentMonthDayColor().value_or(theme->GetCalendarTheme().nonCurrentMonthDayColor));
    nonCurrentMonthLunarColor_ = ToRSColor(
        paintProperty->GetNonCurrentMonthLunarColor().value_or(theme->GetCalendarTheme().nonCurrentMonthLunarColor));
    workDayMarkColor_ =
        ToRSColor(paintProperty->GetWorkDayMarkColor().value_or(theme->GetCalendarTheme().workDayMarkColor));
    offDayMarkColor_ =
        ToRSColor(paintProperty->GetOffDayMarkColor().value_or(theme->GetCalendarTheme().offDayMarkColor));
    nonCurrentMonthWorkDayMarkColor_ = ToRSColor(paintProperty->GetNonCurrentMonthWorkDayMarkColor().value_or(
        theme->GetCalendarTheme().nonCurrentMonthWorkDayMarkColor));
    nonCurrentMonthOffDayMarkColor_ = ToRSColor(paintProperty->GetNonCurrentMonthOffDayMarkColor().value_or(
        theme->GetCalendarTheme().nonCurrentMonthOffDayMarkColor));
    focusedDayColor_ =
        ToRSColor(paintProperty->GetFocusedDayColor().value_or(theme->GetCalendarTheme().focusedDayColor));
    focusedLunarColor_ =
        ToRSColor(paintProperty->GetFocusedLunarColor().value_or(theme->GetCalendarTheme().focusedLunarColor));
    focusedAreaBackgroundColor_ = ToRSColor(
        paintProperty->GetFocusedAreaBackgroundColor().value_or(theme->GetCalendarTheme().focusedAreaBackgroundColor));
    markLunarColor_ = ToRSColor(paintProperty->GetMarkLunarColor().value_or(theme->GetCalendarTheme().markLunarColor));

    todayDayColor_ = RSColor(theme->GetCalendarTheme().todayColor.GetValue());
    todayLunarColor_ = RSColor(theme->GetCalendarTheme().todayLunarColor.GetValue());

    dayFontWeight_ = StringUtils::StringToFontWeight(theme->GetCalendarTheme().dayFontWeight);
    lunarDayFontWeight_ = StringUtils::StringToFontWeight(theme->GetCalendarTheme().lunarDayFontWeight);
    workStateFontWeight_ = StringUtils::StringToFontWeight(theme->GetCalendarTheme().workStateFontWeight);

    topPadding_ = isCalendarDialog_ ? 0.0 : theme->GetCalendarTheme().topPadding.ConvertToPx();
    weekFontSize_ = paintProperty->GetWeekFontSize().value_or(theme->GetCalendarTheme().weekFontSize).ConvertToPx();
    dayFontSize_ = paintProperty->GetDayFontSize().value_or(theme->GetCalendarTheme().dayFontSize).ConvertToPx();
    lunarDayFontSize_ =
        paintProperty->GetLunarDayFontSize().value_or(theme->GetCalendarTheme().lunarDayFontSize).ConvertToPx();
    workDayMarkSize_ =
        paintProperty->GetWorkDayMarkSize().value_or(theme->GetCalendarTheme().workDayMarkSize).ConvertToPx();
    offDayMarkSize_ =
        paintProperty->GetOffDayMarkSize().value_or(theme->GetCalendarTheme().offDayMarkSize).ConvertToPx();
    focusedAreaRadius_ = paintProperty->GetFocusedAreaRadiusValue({}).ConvertToPx() <= 0
                             ? theme->GetCalendarTheme().focusedAreaRadius.ConvertToPx()
                             : paintProperty->GetFocusedAreaRadiusValue({}).ConvertToPx();

    weekHeight_ = paintProperty->GetWeekHeightValue({}).ConvertToPx() <= 0
                      ? theme->GetCalendarTheme().weekHeight.ConvertToPx()
                      : paintProperty->GetWeekHeightValue({}).ConvertToPx();
    dayHeight_ = paintProperty->GetDayHeightValue({}).ConvertToPx() <= 0
                     ? theme->GetCalendarTheme().dayHeight.ConvertToPx()
                     : paintProperty->GetDayHeightValue({}).ConvertToPx();
    weekWidth_ = paintProperty->GetWeekWidthValue({}).ConvertToPx() <= 0
                     ? theme->GetCalendarTheme().weekWidth.ConvertToPx()
                     : paintProperty->GetWeekWidthValue({}).ConvertToPx();
    dayWidth_ = paintProperty->GetDayWidthValue({}).ConvertToPx() <= 0
                    ? theme->GetCalendarTheme().dayWidth.ConvertToPx()
                    : paintProperty->GetDayWidthValue({}).ConvertToPx();
    weekAndDayRowSpace_ =
        paintProperty->GetWeekAndDayRowSpace().value_or(theme->GetCalendarTheme().weekAndDayRowSpace).ConvertToPx();

    touchCircleStrokeWidth_ = theme->GetCalendarTheme().touchCircleStrokeWidth.ConvertToPx();

    colSpace_ = paintProperty->GetColSpaceValue({}).ConvertToPx() <= 0
                    ? theme->GetCalendarTheme().colSpace.ConvertToPx()
                    : paintProperty->GetColSpaceValue({}).ConvertToPx();
    dailyFourRowSpace_ = NonPositive(paintProperty->GetDailyFourRowSpaceValue({}).ConvertToPx())
                             ? theme->GetCalendarTheme().dailySixRowSpace.ConvertToPx()
                             : paintProperty->GetDailyFourRowSpaceValue({}).ConvertToPx();
    dailyFiveRowSpace_ = paintProperty->GetDailyFiveRowSpaceValue({}).ConvertToPx() <= 0
                             ? theme->GetCalendarTheme().dailyFiveRowSpace.ConvertToPx()
                             : paintProperty->GetDailyFiveRowSpaceValue({}).ConvertToPx();

    dailySixRowSpace_ = paintProperty->GetDailySixRowSpaceValue({}).ConvertToPx() <= 0
                            ? theme->GetCalendarTheme().dailySixRowSpace.ConvertToPx()
                            : paintProperty->GetDailySixRowSpaceValue({}).ConvertToPx();

    gregorianDayHeight_ = paintProperty->GetGregorianCalendarHeightValue({}).ConvertToPx() <= 0
                                   ? theme->GetCalendarTheme().gregorianCalendarHeight.ConvertToPx()
                                   : paintProperty->GetGregorianCalendarHeightValue({}).ConvertToPx();

    lunarDayHeight_ = paintProperty->GetLunarHeight().value_or(theme->GetCalendarTheme().lunarHeight).ConvertToPx();

    gregorianDayYAxisOffset_ =
        paintProperty->GetDayYAxisOffset().value_or(theme->GetCalendarTheme().dayYAxisOffset).ConvertToPx();
    lunarDayYAxisOffset_ =
        paintProperty->GetLunarDayYAxisOffset().value_or(theme->GetCalendarTheme().lunarDayYAxisOffset).ConvertToPx();

    workStateWidth_ = paintProperty->GetWorkStateWidthValue({}).ConvertToPx() <= 0
                          ? theme->GetCalendarTheme().workStateWidth.ConvertToPx()
                          : paintProperty->GetWorkStateWidthValue({}).ConvertToPx();

    workStateHorizontalMovingDistance_ = paintProperty->GetWorkStateHorizontalMovingDistance()
                                             .value_or(theme->GetCalendarTheme().workStateHorizontalMovingDistance)
                                             .ConvertToPx();
    workStateVerticalMovingDistance_ = paintProperty->GetWorkStateVerticalMovingDistance()
                                           .value_or(theme->GetCalendarTheme().workStateVerticalMovingDistance)
                                           .ConvertToPx();
    dayRadius_ = paintProperty->GetDayRadiusValue(theme->GetCalendarDayRadius()).ConvertToPx();
    textNonCurrentMonthColor_ = ToRSColor(theme->GetTextNonCurrentMonthColor());
    textSelectedDayColor_ = ToRSColor(theme->GetTextSelectedDayColor());
    textCurrentDayColor_ = ToRSColor(theme->GetTextCurrentDayColor());
    textCurrentMonthColor_ = ToRSColor(theme->GetTextCurrentMonthColor());
    backgroundKeyFocusedColor_ = ToRSColor(theme->GetBackgroundKeyFocusedColor());
    backgroundSelectedTodayColor_ = ToRSColor(theme->GetBackgroundSelectedTodayColor());
    backgroundSelectedNotTodayColor_ = ToRSColor(theme->GetBackgroundSelectedNotTodayColor());
    backgroundHoverColor_ = ToRSColor(theme->GetBackgroundHoverColor());
    backgroundPressColor_ = ToRSColor(theme->GetBackgroundPressColor());

    auto fontSizeScale = pipelineContext->GetFontScale();
    if (fontSizeScale < theme->GetCalendarPickerLargeScale() ||
        Dimension(pipelineContext->GetRootHeight()).ConvertToVp() < DEVICE_HEIGHT_LIMIT) {
        calendarDayKeyFocusedWidth_ = theme->GetCalendarDayKeyFocusedWidth().ConvertToPx();
    } else {
        calendarDayKeyFocusedWidth_ = theme->GetCalendarLargeDayKeyFocusedWidth().ConvertToPx();
    }

    calendarDayKeyFocusedPenWidth_ = theme->GetCalendarDayKeyFocusedPenWidth().ConvertToPx();
    if (paintProperty->HasShowLunar()) {
        showLunar_ = paintProperty->GetShowLunarValue();
    }
    showHoliday_ = paintProperty->GetShowHolidayValue(true);
    if (paintProperty->HasStartOfWeek()) {
        startOfWeek_ = static_cast<int32_t>(paintProperty->GetStartOfWeekValue());
    }
    startOfWeek_ = static_cast<int32_t>(log2(startOfWeek_));
    if (paintProperty->HasOffDays()) {
        offDays_ = paintProperty->GetOffDaysValue();
    }
    currentMonth_.month = obtainedMonth_.month;
}

bool CalendarPaintMethod::IsToday(const CalendarDay& day) const
{
    auto today = calendarDay_;
    return today.month == day.month && today.day == day.day;
}

bool CalendarPaintMethod::IsOffDay(const CalendarDay& dayInfo) const
{
    std::vector<std::string> days;
    StringUtils::StringSplitter(offDays_, ',', days);
    int32_t daysOfWeek = 7;
    for (const auto& day : days) {
        auto num = (StringUtils::StringToInt(day) + (daysOfWeek - static_cast<int32_t>(startOfWeek_))) % daysOfWeek;
        if ((dayInfo.index % daysOfWeek) == num) {
            return true;
        }
    }
    return false;
}
} // namespace OHOS::Ace::NG