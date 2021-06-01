/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/calendar/flutter_render_calendar.h"

#include "flutter/lib/ui/text/font_collection.h"
#include "flutter/lib/ui/text/paragraph_builder.h"

#include "base/i18n/localization.h"
#include "base/utils/string_utils.h"
#include "core/common/ace_application_info.h"
#include "core/components/calendar/flutter_render_calendar.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/font/flutter_font_collection.h"
#include "core/pipeline/base/scoped_canvas_state.h"

namespace OHOS::Ace {
namespace {

const char ELLIPSIS[] = "...";
constexpr double CURRENT_MONTH_TRANSPARENT = 0xFF;
constexpr double NON_CURRENT_MONTH_TRANSPARENT = 0x32;
constexpr double WEEKEND_TRANSPARENT = 0x7D;
constexpr double SCHEDULE_MARKER_TRANSPARENT = 0x4B;
constexpr Dimension CARD_CALENDAR_TITLE_HEIGHT = 88.0_vp;

std::unique_ptr<txt::Paragraph> GetTextParagraph(const std::string& text, const txt::TextStyle& textStyle)
{
    txt::ParagraphStyle style;
    auto fontCollection = FlutterFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        LOGW("MeasureText: fontCollection is null");
        return nullptr;
    }
    std::unique_ptr<txt::ParagraphBuilder> builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);
    builder->PushStyle(textStyle);
    builder->AddText(StringUtils::Str8ToStr16(text));
    return builder->Build();
}

void DrawCalendarText(
    ScopedCanvas& canvas, const std::string& text, const txt::TextStyle& textStyle, const Rect& boxRect, Rect& textRect)
{
    // The lunar calendar description is truncated by more than three characters.
    std::string newText { text };
    auto wText = StringUtils::ToWstring(text);
    if (wText.size() > 3) {
        wText = wText.substr(0, 2);
        newText = StringUtils::ToString(wText);
        newText += ELLIPSIS;
    }

    auto paragraph = GetTextParagraph(newText, textStyle);
    if (!paragraph) {
        return;
    }
    const auto& offset = boxRect.GetOffset();
    paragraph->Layout(boxRect.Width());
    double textWidth = paragraph->GetMaxIntrinsicWidth();
    double textHeight = paragraph->GetHeight();
    // paint text in center of item
    double textPaintOffsetX = (boxRect.Width() - textWidth) / 2.0;
    double textPaintOffsetY = (boxRect.Height() - textHeight) / 2.0;
    paragraph->Paint(canvas->canvas(), offset.GetX() + textPaintOffsetX, offset.GetY() + textPaintOffsetY);
    textRect.SetRect(offset.GetX() + textPaintOffsetX, offset.GetY() + textPaintOffsetY, textWidth, textHeight);
}

void DrawCalendarText(
    ScopedCanvas& canvas, const std::string& text, const txt::TextStyle& textStyle, const Rect& boxRect)
{
    Rect textRect;
    DrawCalendarText(canvas, text, textStyle, boxRect, textRect);
}

} // namespace

RefPtr<RenderNode> RenderCalendar::Create()
{
    return AceType::MakeRefPtr<FlutterRenderCalendar>();
}

RenderLayer FlutterRenderCalendar::GetRenderLayer()
{
    if (!layer_) {
        layer_ = AceType::MakeRefPtr<Flutter::ClipLayer>(
            0, GetLayoutSize().Width(), 0, GetLayoutSize().Height(), Flutter::Clip::HARD_EDGE);
        lastLayoutSize_ = GetLayoutSize();
    } else if (lastLayoutSize_ != GetLayoutSize()) {
        layer_->SetClip(0, GetLayoutSize().Width(), 0, GetLayoutSize().Height(), Flutter::Clip::HARD_EDGE);
        lastLayoutSize_ = GetLayoutSize();
    }
    return AceType::RawPtr(layer_);
}

void FlutterRenderCalendar::Update(const RefPtr<Component>& component)
{
    auto calendarMonth = AceType::DynamicCast<CalendarMonthComponent>(component);
    if (!calendarMonth) {
        LOGE("calendar component is null");
        return;
    }

    textDirection_ = calendarMonth->GetTextDirection();
    auto calendarTheme = calendarMonth->GetCalendarTheme();
    calendarTheme_ = AceApplicationInfo::GetInstance().GetIsCardType() ? calendarTheme->GetCardCalendarTheme()
                                                                       : calendarTheme->GetCalendarTheme();
    cardCalendar_ = calendarMonth->IsCardCalendar();
    RenderCalendar::Update(component);
}

void FlutterRenderCalendar::Paint(RenderContext& context, const Offset& offset)
{
    SetCalendarTheme();
    auto canvas = ScopedCanvas::Create(context);
    if (!canvas) {
        LOGE("paint canvas is null");
        return;
    }
    if (indexOfContainer_ != calendarController_->GetCurrentIndex()) {
        selectedDayNumber_ = 1;
    }
    DrawWeekAndDates(canvas, offset);
}

void FlutterRenderCalendar::PerformLayout()
{
    RenderCalendar::PerformLayout();
    topPadding_ = NormalizeToPx(calendarTheme_.topPadding);
    weekFontSize_ = NormalizeToPx(calendarTheme_.weekFontSize);
    dayFontSize_ = NormalizeToPx(calendarTheme_.dayFontSize);
    lunarDayFontSize_ = NormalizeToPx(calendarTheme_.lunarDayFontSize);
    workDayMarkSize_ = NormalizeToPx(calendarTheme_.workDayMarkSize);
    offDayMarkSize_ = NormalizeToPx(calendarTheme_.offDayMarkSize);
    focusedAreaRadius_ = NormalizeToPx(calendarTheme_.focusedAreaRadius);
    weekHeight_ = NormalizeToPx(calendarTheme_.weekHeight);
    dayHeight_ = NormalizeToPx(calendarTheme_.dayHeight);
    weekWidth_ = NormalizeToPx(calendarTheme_.weekWidth);
    dayWidth_ = NormalizeToPx(calendarTheme_.dayWidth);
    const static int32_t daysOfWeek = 7;
    const static int32_t fiveRow = 5;
    const static int32_t sixRow = 6;
    colSpace_ = cardCalendar_ ? (maxWidth_ - weekWidth_ * daysOfWeek) / (daysOfWeek - 1)
                              : NormalizeToPx(calendarTheme_.colSpace);
    weekAndDayRowSpace_ = NormalizeToPx(calendarTheme_.weekAndDayRowSpace);
    dailyFiveRowSpace_ =
        cardCalendar_ ? (maxHeight_ - NormalizeToPx(CARD_CALENDAR_TITLE_HEIGHT) - weekWidth_ * fiveRow) / (fiveRow - 1)
                      : NormalizeToPx(calendarTheme_.dailyFiveRowSpace);
    dailySixRowSpace_ =
        cardCalendar_ ? (maxHeight_ - NormalizeToPx(CARD_CALENDAR_TITLE_HEIGHT) - weekWidth_ * sixRow) / (sixRow - 1)
                      : NormalizeToPx(calendarTheme_.dailySixRowSpace);
    gregorianCalendarHeight_ = NormalizeToPx(calendarTheme_.gregorianCalendarHeight);
    workStateWidth_ = NormalizeToPx(calendarTheme_.workStateWidth);
    workStateHorizontalMovingDistance_ = NormalizeToPx(calendarTheme_.workStateHorizontalMovingDistance);
    workStateVerticalMovingDistance_ = NormalizeToPx(calendarTheme_.workStateVerticalMovingDistance);
    if (cardCalendar_ && (maxHeight_ - NormalizeToPx(CARD_CALENDAR_TITLE_HEIGHT)) < (dayWidth_ * rowCount_)) {
        needShrink_ = true;
        focusedAreaRadius_ = (maxHeight_ - NormalizeToPx(CARD_CALENDAR_TITLE_HEIGHT)) / (rowCount_ * 2);
    } else {
        needShrink_ = false;
    }
}

void FlutterRenderCalendar::DrawWeekAndDates(ScopedCanvas& canvas, const Offset& offset)
{
    uint32_t totalWeek = weekNumbers_.size();
    uint32_t daysCount = rowCount_ * totalWeek;
    if (calendarDays_.size() < daysCount) {
        LOGD("not full data");
        return;
    }

    DrawWeek(canvas, offset);

    int32_t dateNumber = 0;
    double dailyRowSpace = 0.0;
    static const Dimension dateOffset = 4.0_vp;
    double dayNumberStartY = topPadding_ + weekHeight_ + weekAndDayRowSpace_;
    if (rowCount_ == 5) {
        dailyRowSpace = dailyFiveRowSpace_;
    } else if (rowCount_ == 6) {
        dailyRowSpace = dailySixRowSpace_;
    }
    for (int32_t row = 0; row < rowCount_; row++) {
        double y = row * (dayHeight_ + dailyRowSpace) + dayNumberStartY;
        for (uint32_t column = 0; column < totalWeek; column++) {
            const auto& day = calendarDays_[dateNumber++];
            double x = textDirection_ == TextDirection::LTR ? column * (dayWidth_ + colSpace_)
                                                            : (totalWeek - column - 1) * (dayWidth_ + colSpace_);
            auto dayOffset = Offset(x, y);
            cardCalendar_
                ? DrawCardCalendar(canvas, offset + Offset(0, NormalizeToPx(dateOffset)), dayOffset, day, dateNumber)
                : DrawTvCalendar(canvas, offset, dayOffset, day, dateNumber);
        }
    }
}

void FlutterRenderCalendar::DrawFocusedArea(ScopedCanvas& canvas, const Offset& offset, double x, double y) const
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("pipeline context");
        return;
    }
    // start focus animation
    Offset circleStart =
        GetGlobalOffset() + Offset(x - (focusedAreaRadius_ * 2 - dayWidth_) / 2, y - NormalizeToPx(1.0_vp));
    RRect focusAnimationRRect =
        RRect::MakeRRect(Rect(0.0, 0.0, focusedAreaRadius_ * 2, focusedAreaRadius_ * 2), Radius(focusedAreaRadius_));
    pipelineContext->ShowFocusAnimation(focusAnimationRRect, Color::WHITE, circleStart);

    // draw focus background circle
    flutter::Paint paint;
    flutter::PaintData paintData;
    paint.paint()->setAntiAlias(true);
    paint.paint()->setColor(focusedAreaBackgroundColor_);
    Offset circleCenter = Offset(x - (focusedAreaRadius_ * 2 - dayWidth_) / 2 + focusedAreaRadius_,
        y - NormalizeToPx(1.0_vp) + focusedAreaRadius_);
    Offset bgCircleStart = offset + circleCenter;
    canvas->drawCircle(bgCircleStart.GetX(), bgCircleStart.GetY(), focusedAreaRadius_, paint, paintData);
}

void FlutterRenderCalendar::DrawWeek(ScopedCanvas& canvas, const Offset& offset) const
{
    uint32_t totalWeek = weekNumbers_.size();
    txt::TextStyle weekTextStyle;
    weekTextStyle.color = weekColor_;
    weekTextStyle.font_size = weekFontSize_;
    if (cardCalendar_) {
        weekTextStyle.font_weight = static_cast<txt::FontWeight>(FontWeight::W500);
    }
    weekTextStyle.locale = Localization::GetInstance()->GetFontLocale();
    static const int32_t daysOfWeek = 7;
    auto startDayOfWeek = dataAdapter_->GetStartDayOfWeek();
    for (uint32_t column = 0; column < totalWeek; column++) {
        double x = textDirection_ == TextDirection::LTR ? column * (weekWidth_ + colSpace_)
                                                        : (totalWeek - column - 1) * (weekWidth_ + colSpace_);
        Offset weekNumberOffset = offset + Offset(x, topPadding_);
        Rect boxRect { weekNumberOffset.GetX(), weekNumberOffset.GetY(), weekWidth_, weekHeight_ };
        std::string newText { weekNumbers_[(startDayOfWeek + 1) % daysOfWeek] };
        auto wText = StringUtils::ToWstring(weekNumbers_[column]);
        if (wText.size() > 3) {
            wText = wText.substr(0, 3);
            newText = StringUtils::ToString(wText);
        }
        DrawCalendarText(canvas, newText, weekTextStyle, boxRect);
        ++startDayOfWeek;
    }
}

void FlutterRenderCalendar::DrawBlurArea(ScopedCanvas& canvas, const Offset& offset, double x, double y) const
{
    auto pipelineContext = GetContext().Upgrade();
    if (!pipelineContext) {
        LOGE("pipeline context is null");
        return;
    }
    // start focus animation
    flutter::Paint paint;
    flutter::PaintData paintData;
    paint.paint()->setAntiAlias(true);
    paint.paint()->setColor(blurAreaBackgroundColor_);
    Offset circleCenter = Offset(x - (focusedAreaRadius_ * 2 - dayWidth_) / 2 + focusedAreaRadius_,
        y - NormalizeToPx(1.0_vp) + focusedAreaRadius_);
    Offset bgCircleStart = offset + circleCenter;
    canvas->drawCircle(bgCircleStart.GetX(), bgCircleStart.GetY(), focusedAreaRadius_, paint, paintData);
}

void FlutterRenderCalendar::PaintDay(
    ScopedCanvas& canvas, const Offset& offset, const CalendarDay& day, const txt::TextStyle& textStyle) const
{
    // paint day
    Rect boxRect { offset.GetX(), offset.GetY(), dayWidth_, gregorianCalendarHeight_ };
    Rect textRect;
    auto dayStr = std::to_string(day.day);
    dayStr = Localization::GetInstance()->NumberFormat(day.day);
    DrawCalendarText(canvas, dayStr, textStyle, boxRect, textRect);

    txt::TextStyle workStateStyle;
    if (!day.dayMark.empty() && showHoliday_) {
        if (cardCalendar_) {
            InitWorkStateStyle(day, offset, workStateStyle, boxRect);
        } else {
            workStateStyle.font_weight = static_cast<txt::FontWeight>(workStateFontWeight_);
            workStateStyle.locale = Localization::GetInstance()->GetFontLocale();
            boxRect = { textRect.GetOffset().GetX() + textRect.Width() - workStateHorizontalMovingDistance_,
                textRect.GetOffset().GetY() + textRect.Height() - workStateVerticalMovingDistance_, workStateWidth_,
                workStateWidth_ };
            if (day.month.month == currentMonth_.month) {
                if (day.dayMark == "work") {
                    workStateStyle.font_size = workDayMarkSize_;
                    workStateStyle.color = workDayMarkColor_;
                } else if (day.dayMark == "off") {
                    workStateStyle.font_size = offDayMarkSize_;
                    workStateStyle.color = offDayMarkColor_;
                }
            } else {
                if (day.dayMark == "work") {
                    workStateStyle.font_size = workDayMarkSize_;
                    workStateStyle.color = nonCurrentMonthWorkDayMarkColor_;
                } else if (day.dayMark == "off") {
                    workStateStyle.font_size = offDayMarkSize_;
                    workStateStyle.color = nonCurrentMonthOffDayMarkColor_;
                }
            }
            if (day.focused) {
                workStateStyle.color = Color::BLACK.GetValue();
            }
        }
        DrawCalendarText(canvas, day.dayMarkValue, workStateStyle, boxRect);
    }
}

void FlutterRenderCalendar::PaintLunarDay(
    ScopedCanvas& canvas, const Offset& offset, const CalendarDay& day, const txt::TextStyle& textStyle) const
{
    Rect boxRect;
    static const Dimension cardLunarHeight = 14.0_vp;
    cardCalendar_ ? boxRect = { offset.GetX(), offset.GetY(), dayWidth_, NormalizeToPx(cardLunarHeight) }
                  : boxRect = { offset.GetX(), offset.GetY(), dayWidth_, dayHeight_ - gregorianCalendarHeight_ };
    DrawCalendarText(canvas, day.lunarDay, textStyle, boxRect);
}

void FlutterRenderCalendar::SetNonFocusStyle(
    const CalendarDay& day, txt::TextStyle& dateTextStyle, txt::TextStyle& lunarTextStyle)
{
    SkColor dateTextColor;
    SkColor lunarTextColor;
    if (day.month.month != currentMonth_.month) {
        dateTextColor = nonCurrentMonthDayColor_;
        lunarTextColor = day.markLunarDay ? SkColorSetA(markLunarColor_, WEEKEND_TRANSPARENT)
                                          : nonCurrentMonthLunarColor_;
    } else if (IsToday(day)) {
        dateTextColor = todayDayColor_;
        lunarTextColor = todayLunarColor_;
    } else if (day.weekend) {
        dateTextColor = weekendDayColor_;
        lunarTextColor =
            day.markLunarDay ? markLunarColor_ : weekendLunarColor_;
    } else {
        dateTextColor = dayColor_;
        lunarTextColor = day.markLunarDay ? markLunarColor_ : lunarColor_;
    }

    dateTextStyle.color = dateTextColor;
    lunarTextStyle.color = lunarTextColor;
}

void FlutterRenderCalendar::DrawTouchedArea(ScopedCanvas& canvas, const Offset& offset, double x, double y) const
{
    flutter::Paint paint;
    flutter::PaintData paintData;
    paint.paint()->setAntiAlias(true);
    paint.paint()->setColor(touchColor_);
    Offset circleCenter = Offset(x - (focusedAreaRadius_ * 2 - dayWidth_) / 2 + focusedAreaRadius_,
        y - NormalizeToPx(1.0_vp) + focusedAreaRadius_);
    Offset bgCircleStart = offset + circleCenter;
    canvas->drawCircle(bgCircleStart.GetX(), bgCircleStart.GetY(), focusedAreaRadius_, paint, paintData);
}

void FlutterRenderCalendar::DrawCardCalendar(
    ScopedCanvas& canvas, const Offset& offset, const Offset& dayOffset, const CalendarDay& day, int32_t dateNumber)
{
    txt::TextStyle dateTextStyle;
    txt::TextStyle lunarTextStyle;
    InitTextStyle(dateTextStyle, lunarTextStyle);
    SetNonFocusStyle(day, dateTextStyle, lunarTextStyle);
    dateTextStyle.locale = Localization::GetInstance()->GetFontLocale();
    auto x = dayOffset.GetX();
    auto y = dayOffset.GetY();
    if (IsToday(day) && (day.month.month == currentMonth_.month)) {
        dateTextStyle.color = focusedDayColor_;
        lunarTextStyle.color = focusedDayColor_;
        DrawFocusedArea(canvas, offset, x, y);
    }

    if (day.touched) {
        DrawTouchedArea(canvas, offset, x, y);
    }

    if (needShrink_) {
        Offset dateNumberOffset = offset + Offset(x, y + (focusedAreaRadius_ - gregorianCalendarHeight_ / 2));
        PaintDay(canvas, dateNumberOffset, day, dateTextStyle);
        return;
    }

    static const Dimension dayYAxisOffset = 4.0_vp;
    Offset dateNumberOffset = offset + Offset(x, y + NormalizeToPx(dayYAxisOffset));
    PaintDay(canvas, dateNumberOffset, day, dateTextStyle);

    static const Dimension lunarDayYAxisOffset = 23.0_vp;
    Offset lunarDayOffset = offset + Offset(x, y + NormalizeToPx(lunarDayYAxisOffset));
    PaintLunarDay(canvas, lunarDayOffset, day, lunarTextStyle);

    if (day.isFirstOfLunar) {
        static const Dimension underscoreXAxisOffset = 12.0_vp;
        static const Dimension underscoreYAxisOffset = 36.0_vp;
        Offset underscoreOffset =
            offset + Offset(x + NormalizeToPx(underscoreXAxisOffset), y + NormalizeToPx(underscoreYAxisOffset));
        PaintUnderscore(canvas, underscoreOffset, day);
    }

    if (day.hasSchedule) {
        static const Dimension scheduleMarkerXAxisOffset = 22.0_vp;
        static const Dimension scheduleMarkerYAxisOffset = 40.0_vp;
        Offset scheduleMarkerOffset =
            offset + Offset(x + NormalizeToPx(scheduleMarkerXAxisOffset), y + NormalizeToPx(scheduleMarkerYAxisOffset));
        PaintScheduleMarker(canvas, scheduleMarkerOffset, day);
    }
}

void FlutterRenderCalendar::DrawTvCalendar(
    ScopedCanvas& canvas, const Offset& offset, const Offset& dayOffset, const CalendarDay& day, int32_t dateNumber)
{
    txt::TextStyle dateTextStyle;
    txt::TextStyle lunarTextStyle;
    InitTextStyle(dateTextStyle, lunarTextStyle);
    dateTextStyle.locale = Localization::GetInstance()->GetFontLocale();
    lunarTextStyle.locale = Localization::GetInstance()->GetFontLocale();

    auto renderSwiper = calendarController_->GetRenderSwiper();
    if (!renderSwiper) {
        return;
    }
    int32_t selectedDay = selectedDayNumber_ + firstDayIndex_ - 1;
    auto x = dayOffset.GetX();
    auto y = dayOffset.GetY();
    if (day.focused && day.month.month == currentMonth_.month && !renderSwiper->GetMoveStatus() &&
        indexOfContainer_ == calendarController_->GetCurrentIndex()) {
        dateTextStyle.color = focusedDayColor_;
        lunarTextStyle.color = focusedLunarColor_;
        DrawFocusedArea(canvas, offset, x, y);
    } else {
        SetNonFocusStyle(day, dateTextStyle, lunarTextStyle);
    }

    if (selectedDay == (dateNumber - 1) && !calendarFocusStatus_ && !renderSwiper->GetMoveStatus() &&
        hasRequestFocus_) {
        DrawBlurArea(canvas, offset, x, y);
    }

    if (dataAdapter_->ShowLunar() && !day.lunarDay.empty()) {
        // paint day
        Offset dateNumberOffset = offset + Offset(x, y);
        PaintDay(canvas, dateNumberOffset, day, dateTextStyle);

        // paint lunar day
        Offset lunarDayOffset = offset + Offset(x, y + gregorianCalendarHeight_);
        PaintLunarDay(canvas, lunarDayOffset, day, lunarTextStyle);
    } else {
        // when there is no lunar calendar, the date is displayed in the center
        Offset dateNumberOffset = offset + Offset(x, y + (focusedAreaRadius_ - gregorianCalendarHeight_ / 2));
        PaintDay(canvas, dateNumberOffset, day, dateTextStyle);
    }
}

void FlutterRenderCalendar::InitTextStyle(txt::TextStyle& dateTextStyle, txt::TextStyle& lunarTextStyle)
{
    dateTextStyle.font_size = dayFontSize_;
    dateTextStyle.font_weight = static_cast<txt::FontWeight>(dayFontWeight_);

    lunarTextStyle.font_size = lunarDayFontSize_;
    lunarTextStyle.font_weight = static_cast<txt::FontWeight>(lunarDayFontWeight_);
}

bool FlutterRenderCalendar::IsToday(const CalendarDay& day) const
{
    auto today = dataAdapter_->GetToday();
    return today.month == day.month && today.day == day.day;
}

void FlutterRenderCalendar::PaintUnderscore(ScopedCanvas& canvas, const Offset& offset, const CalendarDay& day)
{
    static const Dimension underscoreWidth = 1.0_vp;
    static const Dimension underscoreLength = 20.0_vp;
    auto skCanvas = canvas.GetSkCanvas();
    SkPaint paint;
    SkColor color;
    if (day.month.month != currentMonth_.month) {
        color = SkColorSetA(focusedAreaBackgroundColor_, NON_CURRENT_MONTH_TRANSPARENT);
    } else if (IsToday(day)) {
        color = focusedDayColor_;
    } else if (day.weekend) {
        color = SkColorSetA(focusedAreaBackgroundColor_, WEEKEND_TRANSPARENT);
    } else {
        color = SkColorSetA(focusedAreaBackgroundColor_, CURRENT_MONTH_TRANSPARENT);
    }
    paint.setColor(color);
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setStrokeWidth(NormalizeToPx(underscoreWidth));
    skCanvas->drawLine(offset.GetX(), offset.GetY() + NormalizeToPx(underscoreWidth) / 2,
        offset.GetX() + NormalizeToPx(underscoreLength), offset.GetY() + NormalizeToPx(underscoreWidth) / 2, paint);
}

void FlutterRenderCalendar::PaintScheduleMarker(ScopedCanvas& canvas, const Offset& offset, const CalendarDay& day)
{
    static const Dimension scheduleMarkerRadius = 2.0_vp;
    auto skCanvas = canvas.GetSkCanvas();
    SkPaint paint;
    SkColor color;
    if (day.month.month != currentMonth_.month) {
        color = SkColorSetA(focusedAreaBackgroundColor_, NON_CURRENT_MONTH_TRANSPARENT);
    } else if (IsToday(day)) {
        color = focusedDayColor_;
    } else if (day.weekend) {
        color = SkColorSetA(focusedAreaBackgroundColor_, SCHEDULE_MARKER_TRANSPARENT);
    } else {
        color = SkColorSetA(focusedAreaBackgroundColor_, SCHEDULE_MARKER_TRANSPARENT);
    }
    paint.setColor(color);
    skCanvas->drawCircle(offset.GetX(), offset.GetY(), NormalizeToPx(scheduleMarkerRadius), paint);
}

void FlutterRenderCalendar::InitWorkStateStyle(
    const CalendarDay& day, const Offset& offset, txt::TextStyle& workStateStyle, Rect& boxRect) const
{
    workStateStyle.font_weight = static_cast<txt::FontWeight>(FontWeight::W500);
    workStateStyle.locale = Localization::GetInstance()->GetFontLocale();
    static const Dimension workStateWidth = 8.0_vp;
    static const int32_t twoDigitMaker = 10;
    static const Dimension OneDigitXAxisOffset = 26.0_vp;
    static const Dimension workStateYAxisOffset = 6.0_vp;
    static const Dimension twoDigitXAxisOffset = 31.0_vp;
    if (day.day < twoDigitMaker) {
        boxRect = { offset.GetX() + NormalizeToPx(OneDigitXAxisOffset),
            offset.GetY() + NormalizeToPx(workStateYAxisOffset), NormalizeToPx(workStateWidth),
            NormalizeToPx(workStateWidth) };
    } else {
        boxRect = { offset.GetX() + NormalizeToPx(twoDigitXAxisOffset),
            offset.GetY() + NormalizeToPx(workStateYAxisOffset), NormalizeToPx(workStateWidth),
            NormalizeToPx(workStateWidth) };
    }

    workStateStyle.font_size = NormalizeToPx(workStateWidth);

    if (day.month.month != currentMonth_.month) {
        auto offColor = SkColorSetA(markLunarColor_, WEEKEND_TRANSPARENT);
        auto workColor = SkColorSetA(workDayMarkColor_, WEEKEND_TRANSPARENT);
        SetWorkStateStyle(day, workColor, offColor, workStateStyle);
    } else if (IsToday(day)) {
        SetWorkStateStyle(day, focusedDayColor_, focusedDayColor_, workStateStyle);
    } else if (day.weekend) {
        auto offColor = markLunarColor_;
        auto workColor = workDayMarkColor_;
        SetWorkStateStyle(day, workColor, offColor, workStateStyle);
    } else {
        SetWorkStateStyle(day, workDayMarkColor_, focusedAreaBackgroundColor_, workStateStyle);
    }
}

void FlutterRenderCalendar::SetWorkStateStyle(
    const CalendarDay& day, SkColor workColor, SkColor offColor, txt::TextStyle& workStateStyle) const
{
    if (day.dayMark == "work") {
        workStateStyle.color = workColor;
    } else if (day.dayMark == "off") {
        workStateStyle.color = offColor;
    }
}

void FlutterRenderCalendar::SetCalendarTheme()
{
    auto theme = GetTheme<CalendarTheme>();
    auto calendarTheme = cardCalendar_ ? theme->GetCardCalendarTheme() : theme->GetCalendarTheme();
    touchColor_ = SkColor(calendarTheme.touchColor.GetValue());
    weekColor_ = SkColor(calendarTheme.weekColor.GetValue());
    dayColor_ = SkColor(calendarTheme.dayColor.GetValue());
    lunarColor_ = SkColor(calendarTheme.lunarColor.GetValue());
    weekendDayColor_ = SkColor(calendarTheme.weekendDayColor.GetValue());
    weekendLunarColor_ = SkColor(calendarTheme.weekendLunarColor.GetValue());
    todayDayColor_ = SkColor(calendarTheme.todayColor.GetValue());
    todayLunarColor_ = SkColor(calendarTheme.todayLunarColor.GetValue());
    nonCurrentMonthDayColor_ = SkColor(calendarTheme.nonCurrentMonthDayColor.GetValue());
    nonCurrentMonthLunarColor_ = SkColor(calendarTheme.nonCurrentMonthLunarColor.GetValue());
    workDayMarkColor_ = SkColor(calendarTheme.workDayMarkColor.GetValue());
    offDayMarkColor_ = SkColor(calendarTheme.offDayMarkColor.GetValue());
    nonCurrentMonthWorkDayMarkColor_ = SkColor(calendarTheme.nonCurrentMonthOffDayMarkColor.GetValue());
    nonCurrentMonthOffDayMarkColor_ = SkColor(calendarTheme.nonCurrentMonthOffDayMarkColor.GetValue());
    focusedDayColor_ = SkColor(calendarTheme.focusedDayColor.GetValue());
    focusedLunarColor_ = SkColor(calendarTheme.focusedLunarColor.GetValue());
    focusedAreaBackgroundColor_ = SkColor(calendarTheme.focusedAreaBackgroundColor.GetValue());
    blurAreaBackgroundColor_ = SkColor(calendarTheme.blurAreaBackgroundColor.GetValue());
    markLunarColor_ = SkColor(calendarTheme.markLunarColor.GetValue());
    dayFontWeight_ = StringUtils::StringToFontWeight(calendarTheme.dayFontWeight);
    lunarDayFontWeight_ = StringUtils::StringToFontWeight(calendarTheme.lunarDayFontWeight);
    workStateFontWeight_ = StringUtils::StringToFontWeight(calendarTheme.workStateFontWeight);
}

} // namespace OHOS::Ace
