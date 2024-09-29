/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/components/calendar/rosen_render_calendar.h"

#ifndef USE_GRAPHIC_TEXT_GINE
#include "txt/paragraph_builder.h"
#include "txt/paragraph_style.h"
#else
#include "rosen_text/typography_create.h"
#include "rosen_text/typography_style.h"
#endif

#include "base/i18n/localization.h"
#include "core/components/font/rosen_font_collection.h"
#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {
namespace {

const char ELLIPSIS[] = "...";
constexpr double CURRENT_MONTH_TRANSPARENT = 0xFF;
constexpr double NON_CURRENT_MONTH_TRANSPARENT = 0x32;
constexpr double WEEKEND_TRANSPARENT = 0x7D;
constexpr double SCHEDULE_MARKER_TRANSPARENT = 0x4B;
constexpr Dimension CARD_CALENDAR_TITLE_HEIGHT = 68.0_vp;

#ifndef USE_GRAPHIC_TEXT_GINE
std::unique_ptr<txt::Paragraph> GetTextParagraph(const std::string& text, const txt::TextStyle& textStyle)
{
    txt::ParagraphStyle style;
#else
std::unique_ptr<Rosen::Typography> GetTextParagraph(const std::string& text, const Rosen::TextStyle& textStyle)
{
    Rosen::TypographyStyle style;
#endif
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        LOGW("MeasureText: fontCollection is null");
        return nullptr;
    }
#ifndef USE_GRAPHIC_TEXT_GINE
    std::unique_ptr<txt::ParagraphBuilder> builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);
    builder->PushStyle(textStyle);
    builder->AddText(StringUtils::Str8ToStr16(text));
    return builder->Build();
#else
    std::unique_ptr<Rosen::TypographyCreate> builder = Rosen::TypographyCreate::Create(style, fontCollection);
    builder->PushStyle(textStyle);
    builder->AppendText(StringUtils::Str8ToStr16(text));
    return builder->CreateTypography();
#endif
}

#ifndef USE_ROSEN_DRAWING
#ifndef USE_GRAPHIC_TEXT_GINE
void DrawCalendarText(
    SkCanvas* canvas, const std::string& text, const txt::TextStyle& textStyle, const Rect& boxRect, Rect& textRect)
#else
void DrawCalendarText(
    SkCanvas* canvas, const std::string& text, const Rosen::TextStyle& textStyle, const Rect& boxRect, Rect& textRect)
#endif
#else
#ifndef USE_GRAPHIC_TEXT_GINE
void DrawCalendarText(RSCanvas* canvas,
    const std::string& text, const txt::TextStyle& textStyle, const Rect& boxRect, Rect& textRect)
#else
void DrawCalendarText(RSCanvas* canvas,
    const std::string& text, const Rosen::TextStyle& textStyle, const Rect& boxRect, Rect& textRect)
#endif
#endif
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
    paragraph->Paint(canvas, offset.GetX() + textPaintOffsetX, offset.GetY() + textPaintOffsetY);
    textRect.SetRect(offset.GetX() + textPaintOffsetX, offset.GetY() + textPaintOffsetY, textWidth, textHeight);
}

#ifndef USE_ROSEN_DRAWING
#ifndef USE_GRAPHIC_TEXT_GINE
void DrawCalendarText(SkCanvas* canvas, const std::string& text, const txt::TextStyle& textStyle, const Rect& boxRect)
#else
void DrawCalendarText(SkCanvas* canvas, const std::string& text, const Rosen::TextStyle& textStyle, const Rect& boxRect)
#endif
#else
#ifndef USE_GRAPHIC_TEXT_GINE
void DrawCalendarText(RSCanvas* canvas,
    const std::string& text, const txt::TextStyle& textStyle, const Rect& boxRect)
#else
void DrawCalendarText(RSCanvas* canvas,
    const std::string& text, const Rosen::TextStyle& textStyle, const Rect& boxRect)
#endif
#endif
{
    Rect textRect;
    DrawCalendarText(canvas, text, textStyle, boxRect, textRect);
}
} // namespace

void RosenRenderCalendar::Update(const RefPtr<Component>& component)
{
    auto calendarMonth = AceType::DynamicCast<CalendarMonthComponent>(component);
    if (!calendarMonth) {
        LOGE("calendar component is null");
        return;
    }

    textDirection_ = calendarMonth->GetTextDirection();
    auto calendarTheme = calendarMonth->GetCalendarTheme();
    cardCalendar_ = calendarMonth->IsCardCalendar();
    if (!isV2Component_) {
        calendarTheme_ = cardCalendar_ ? calendarTheme->GetCardCalendarTheme() : calendarTheme->GetCalendarTheme();
    }
    RenderCalendar::Update(component);
    if (auto rsNode = GetRSNode()) {
        rsNode->SetClipToFrame(true);
    }
}

void RosenRenderCalendar::Paint(RenderContext& context, const Offset& offset)
{
    if (isV2Component_ && !isNeedRepaint_) {
        AddContentLayer(context);
        DrawTouchedArea(context, offset);
        return;
    }
    SetCalendarTheme();
    if (isV2Component_) {
#ifdef OHOS_PLATFORM
        const Size& layout = GetLayoutSize();
#ifndef USE_ROSEN_DRAWING
        OHOS::Rosen::RSRecordingCanvas canvas(layout.Width(), layout.Height());
#else
        RSRecordingCanvas canvas(layout.Width(), layout.Height());
#endif
        DrawWeekAndDates(&canvas, offset);
        drawCmdList_ = canvas.GetDrawCmdList();
        isNeedRepaint_ = false;
        AddContentLayer(context);
        DrawTouchedArea(context, offset);
#endif
    } else {
        auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
        if (!canvas) {
            LOGE("paint canvas is null");
            return;
        }
        DrawWeekAndDates(canvas, offset);
    }
}

void RosenRenderCalendar::PerformLayout()
{
    RenderCalendar::PerformLayout();
    topPadding_ = type_ == CalendarType::SIMPLE ? 0.0 : NormalizeToPx(calendarTheme_.topPadding);
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
    weekAndDayRowSpace_ = NormalizeToPx(calendarTheme_.weekAndDayRowSpace);
    touchCircleStrokeWidth_ = NormalizeToPx(calendarTheme_.touchCircleStrokeWidth);
    double titleHeight = topPadding_ + weekHeight_ + weekAndDayRowSpace_;
    double boundaryRowOffset = NormalizeToPx(calendarTheme_.boundaryRowOffset);
    double boundaryColOffset = NormalizeToPx(calendarTheme_.boundaryColOffset);
    const static int32_t daysOfWeek = 7;
    const static int32_t fiveRow = 5;
    const static int32_t sixRow = 6;
    const static float heightOffset = 1.5f;
    weekAndDayRowSpace_ = NormalizeToPx(calendarTheme_.weekAndDayRowSpace);
    if (cardCalendar_ || isV2Component_) {
        colSpace_ = (maxWidth_ - dayWidth_ * daysOfWeek - boundaryRowOffset) / (daysOfWeek - 1);
        dailyFiveRowSpace_ = (maxHeight_ - titleHeight - dayHeight_ * fiveRow - boundaryColOffset) / (fiveRow - 1);
        dailySixRowSpace_ = (maxHeight_ - titleHeight - dayHeight_ * sixRow - boundaryColOffset) / (sixRow - 1);
    } else if (type_ == CalendarType::SIMPLE) {
        colSpace_ = (maxWidth_ - boundaryRowOffset - dayWidth_ * daysOfWeek) / (daysOfWeek - 1);
        dailyFiveRowSpace_ =
            (maxHeight_ - boundaryColOffset - weekAndDayRowSpace_ - weekHeight_ - dayHeight_ * fiveRow) / (fiveRow - 1);
        dailySixRowSpace_ =
            (maxHeight_ - boundaryColOffset - weekAndDayRowSpace_ - weekHeight_ - dayHeight_ * sixRow) / (sixRow - 1);
    } else {
        colSpace_ = NormalizeToPx(calendarTheme_.colSpace);
        dailyFiveRowSpace_ = NormalizeToPx(calendarTheme_.dailyFiveRowSpace);
        dailySixRowSpace_ = NormalizeToPx(calendarTheme_.dailySixRowSpace);
    }
    gregorianCalendarHeight_ = NormalizeToPx(calendarTheme_.gregorianCalendarHeight);
    workStateWidth_ = NormalizeToPx(calendarTheme_.workStateWidth);
    workStateHorizontalMovingDistance_ = NormalizeToPx(calendarTheme_.workStateHorizontalMovingDistance);
    workStateVerticalMovingDistance_ = NormalizeToPx(calendarTheme_.workStateVerticalMovingDistance);
    auto dayHeight = rowCount_ ? (maxHeight_ - NormalizeToPx(CARD_CALENDAR_TITLE_HEIGHT)) / rowCount_ : 0.0;
    auto heightDifference = dayWidth_ - dayHeight;
    if (cardCalendar_ && GreatNotEqual(dayWidth_, dayHeight) && GreatNotEqual(heightDifference, heightOffset)) {
        needShrink_ = true;
        focusedAreaRadius_ = (maxHeight_ - NormalizeToPx(CARD_CALENDAR_TITLE_HEIGHT)) / (rowCount_ * 2);
    } else {
        needShrink_ = false;
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderCalendar::DrawWeekAndDates(SkCanvas* canvas, Offset offset)
#else
void RosenRenderCalendar::DrawWeekAndDates(RSCanvas* canvas, Offset offset)
#endif
{
    uint32_t totalWeek = weekNumbers_.size();
    uint32_t daysCount = static_cast<uint32_t>(rowCount_) * totalWeek;
    if (calendarDays_.size() < daysCount) {
        return;
    }

    if (isV2Component_) {
        offset += { touchCircleStrokeWidth_, 0 };
    }
    DrawWeek(canvas, offset);

    int32_t dateNumber = 0;
    double dailyRowSpace = 0.0;
    static const Dimension dateOffset = 4.0_vp;
    double dayNumberStartY = topPadding_ + weekHeight_ + weekAndDayRowSpace_;
    if (rowCount_ == 5) { // five line calendar
        dailyRowSpace = dailyFiveRowSpace_;
    } else if (rowCount_ == 6) { // six line calendar
        dailyRowSpace = dailySixRowSpace_;
    }
    for (int32_t row = 0; row < rowCount_; row++) {
        double y = row * (dayHeight_ + dailyRowSpace) + dayNumberStartY;
        for (uint32_t column = 0; column < totalWeek; column++) {
            const auto& day = calendarDays_[dateNumber++];
            double x = textDirection_ == TextDirection::LTR ? column * (dayWidth_ + colSpace_)
                                                            : (totalWeek - column - 1) * (dayWidth_ + colSpace_);
            auto dayOffset = Offset(x, y);
            if (cardCalendar_ || isV2Component_) {
                DrawCardCalendar(canvas, offset + Offset(0, NormalizeToPx(dateOffset)), dayOffset, day, dateNumber);
            } else {
                DrawTvCalendar(canvas, offset, dayOffset, day, dateNumber);
            }
        }
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderCalendar::DrawFocusedArea(
    SkCanvas* canvas, const Offset& offset, const CalendarDay& day, double x, double y) const
#else
void RosenRenderCalendar::DrawFocusedArea(
    RSCanvas* canvas, const Offset& offset, const CalendarDay& day, double x, double y) const
#endif
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
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    paint.setAntiAlias(true);

    if (SystemProperties::GetDeviceType() == DeviceType::WATCH || type_ == CalendarType::SIMPLE) {
        if (day.dayMark == "work" && showHoliday_) {
            paint.setColor(workDayMarkColor_);
        } else if (day.dayMark == "off" && showHoliday_) {
            paint.setColor(offDayMarkColor_);
        } else {
            paint.setColor(focusedAreaBackgroundColor_);
        }
    } else {
        paint.setColor(focusedAreaBackgroundColor_);
    }
    Offset circleCenter =
        type_ == CalendarType::SIMPLE
            ? Offset(x - (focusedAreaRadius_ * 2 - dayWidth_) / 2 + focusedAreaRadius_, y + focusedAreaRadius_)
            : Offset(x - (focusedAreaRadius_ * 2 - dayWidth_) / 2 + focusedAreaRadius_,
                y - NormalizeToPx(1.0_vp) + focusedAreaRadius_);
    Offset bgCircleStart = offset + circleCenter;
    canvas->drawCircle(bgCircleStart.GetX(), bgCircleStart.GetY(), focusedAreaRadius_, paint);
#else
    RSBrush brush;
    brush.SetAntiAlias(true);

    if (SystemProperties::GetDeviceType() == DeviceType::WATCH || type_ == CalendarType::SIMPLE) {
        if (day.dayMark == "work" && showHoliday_) {
            brush.SetColor(workDayMarkColor_);
        } else if (day.dayMark == "off" && showHoliday_) {
            brush.SetColor(offDayMarkColor_);
        } else {
            brush.SetColor(focusedAreaBackgroundColor_);
        }
    } else {
        brush.SetColor(focusedAreaBackgroundColor_);
    }
    Offset circleCenter =
        type_ == CalendarType::SIMPLE
            ? Offset(x - (focusedAreaRadius_ * 2 - dayWidth_) / 2 + focusedAreaRadius_, y + focusedAreaRadius_)
            : Offset(x - (focusedAreaRadius_ * 2 - dayWidth_) / 2 + focusedAreaRadius_,
                y - NormalizeToPx(1.0_vp) + focusedAreaRadius_);
    Offset bgCircleStart = offset + circleCenter;
    canvas->AttachBrush(brush);
    canvas->DrawCircle(RSPoint(bgCircleStart.GetX(), bgCircleStart.GetY()), focusedAreaRadius_);
    canvas->DetachBrush();
#endif
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderCalendar::DrawWeek(SkCanvas* canvas, const Offset& offset) const
#else
void RosenRenderCalendar::DrawWeek(RSCanvas* canvas, const Offset& offset) const
#endif
{
    uint32_t totalWeek = weekNumbers_.size();
#ifndef USE_GRAPHIC_TEXT_GINE
    txt::TextStyle weekTextStyle;
    weekTextStyle.color = weekColor_;
    weekTextStyle.font_size = weekFontSize_;
    if (cardCalendar_) {
        weekTextStyle.font_weight = static_cast<txt::FontWeight>(FontWeight::W500);
    }
#else
    Rosen::TextStyle weekTextStyle;
    weekTextStyle.color = weekColor_;
    weekTextStyle.fontSize = weekFontSize_;
    if (cardCalendar_) {
        weekTextStyle.fontWeight = static_cast<Rosen::FontWeight>(FontWeight::W500);
    }
#endif
    weekTextStyle.locale = Localization::GetInstance()->GetFontLocale();
    static const int32_t daysOfWeek = 7;
    auto startDayOfWeek = dataAdapter_->GetStartDayOfWeek();
    for (uint32_t column = 0; column < totalWeek; column++) {
        double x = textDirection_ == TextDirection::LTR ? column * (weekWidth_ + colSpace_)
                                                        : (totalWeek - column - 1) * (weekWidth_ + colSpace_);
        Offset weekNumberOffset = offset + Offset(x, topPadding_);
        Rect boxRect { weekNumberOffset.GetX(), weekNumberOffset.GetY(), weekWidth_, weekHeight_ };
        std::string newText { weekNumbers_[(startDayOfWeek + 1) % daysOfWeek] };
        auto wText = StringUtils::ToWstring(newText);
        if (wText.size() > 3) {
            wText = wText.substr(0, 3);
            newText = StringUtils::ToString(wText);
        }
        DrawCalendarText(canvas, newText, weekTextStyle, boxRect);
        ++startDayOfWeek;
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderCalendar::DrawBlurArea(SkCanvas* canvas, const Offset& offset, double x, double y) const
#else
void RosenRenderCalendar::DrawBlurArea(RSCanvas* canvas, const Offset& offset, double x, double y) const
#endif
{
    auto pipelineContext = GetContext().Upgrade();
    if (!pipelineContext) {
        LOGE("pipeline context is null");
        return;
    }
    // start focus animation
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setColor(blurAreaBackgroundColor_);
    Offset circleCenter = Offset(x - (focusedAreaRadius_ * 2 - dayWidth_) / 2 + focusedAreaRadius_,
        y - NormalizeToPx(1.0_vp) + focusedAreaRadius_);
    Offset bgCircleStart = offset + circleCenter;
    canvas->drawCircle(bgCircleStart.GetX(), bgCircleStart.GetY(), focusedAreaRadius_, paint);
#else
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(blurAreaBackgroundColor_);
    Offset circleCenter = Offset(x - (focusedAreaRadius_ * 2 - dayWidth_) / 2 + focusedAreaRadius_,
        y - NormalizeToPx(1.0_vp) + focusedAreaRadius_);
    Offset bgCircleStart = offset + circleCenter;
    canvas->AttachBrush(brush);
    canvas->DrawCircle(RSPoint(bgCircleStart.GetX(), bgCircleStart.GetY()), focusedAreaRadius_);
    canvas->DetachBrush();
#endif
}

#ifndef USE_ROSEN_DRAWING
#ifndef USE_GRAPHIC_TEXT_GINE
void RosenRenderCalendar::PaintDay(
    SkCanvas* canvas, const Offset& offset, const CalendarDay& day, txt::TextStyle& textStyle) const
#else
void RosenRenderCalendar::PaintDay(
    SkCanvas* canvas, const Offset& offset, const CalendarDay& day, Rosen::TextStyle& textStyle) const
#endif
#else
#ifndef USE_GRAPHIC_TEXT_GINE
void RosenRenderCalendar::PaintDay(
    RSCanvas* canvas, const Offset& offset, const CalendarDay& day, txt::TextStyle& textStyle) const
#else
void RosenRenderCalendar::PaintDay(
    RSCanvas* canvas, const Offset& offset, const CalendarDay& day, Rosen::TextStyle& textStyle) const
#endif
#endif
{
    // paint day
    Rect boxRect { offset.GetX(), offset.GetY(), dayWidth_, gregorianCalendarHeight_ };
    Rect textRect;
#ifndef USE_GRAPHIC_TEXT_GINE
    txt::TextStyle workStateStyle;
#else
    Rosen::TextStyle workStateStyle;
#endif
    if (!day.dayMark.empty() && showHoliday_ && type_ == CalendarType::SIMPLE) {
#ifndef USE_ROSEN_DRAWING
        if (day.dayMark == "work") {
            textStyle.color = SkColor(calendarTheme_.simpleWorkTextColor.GetValue());
        } else if (day.dayMark == "off") {
            textStyle.color = SkColor(calendarTheme_.simpleOffTextColor.GetValue());
        }
#else
        if (day.dayMark == "work") {
            textStyle.color = RSColorQuad(calendarTheme_.simpleWorkTextColor.GetValue());
        } else if (day.dayMark == "off") {
            textStyle.color = RSColorQuad(calendarTheme_.simpleOffTextColor.GetValue());
        }
#endif
    }
    if ((SystemProperties::GetDeviceType() == DeviceType::WATCH || type_ == CalendarType::SIMPLE) && IsToday(day) &&
        !day.dayMark.empty() && showHoliday_) {
        auto workStateOffset = offset + Offset(0, NormalizeToPx(calendarTheme_.workStateOffset));
        boxRect.SetOffset(workStateOffset);
        workStateStyle.color = Color::WHITE.GetValue();
#ifndef USE_GRAPHIC_TEXT_GINE
        workStateStyle.font_size = dayFontSize_;
#else
        workStateStyle.fontSize = dayFontSize_;
#endif
        DrawCalendarText(canvas, day.dayMarkValue, workStateStyle, boxRect, textRect);
        return;
    }
    if ((SystemProperties::GetDeviceType() == DeviceType::WATCH || type_ == CalendarType::SIMPLE) &&
        day.month.month != currentMonth_.month) {
        return;
    }
    auto dayStr = std::to_string(day.day);
    dayStr = Localization::GetInstance()->NumberFormat(day.day);
    DrawCalendarText(canvas, dayStr, textStyle, boxRect, textRect);

    if (!day.dayMark.empty() && showHoliday_ && type_ != CalendarType::SIMPLE) {
        if (cardCalendar_) {
            InitWorkStateStyle(day, offset, workStateStyle, boxRect);
        } else {
#ifndef USE_GRAPHIC_TEXT_GINE
            workStateStyle.font_weight = static_cast<txt::FontWeight>(workStateFontWeight_);
#else
            workStateStyle.fontWeight = static_cast<Rosen::FontWeight>(workStateFontWeight_);
#endif
            workStateStyle.locale = Localization::GetInstance()->GetFontLocale();
            boxRect = { textRect.GetOffset().GetX() + textRect.Width() - workStateHorizontalMovingDistance_,
                textRect.GetOffset().GetY() + textRect.Height() - workStateVerticalMovingDistance_, workStateWidth_,
                workStateWidth_ };
            if (day.month.month == currentMonth_.month) {
                if (day.dayMark == "work") {
#ifndef USE_GRAPHIC_TEXT_GINE
                    workStateStyle.font_size = workDayMarkSize_;
#else
                    workStateStyle.fontSize = workDayMarkSize_;
#endif
                    workStateStyle.color = workDayMarkColor_;
                } else if (day.dayMark == "off") {
#ifndef USE_GRAPHIC_TEXT_GINE
                    workStateStyle.font_size = offDayMarkSize_;
#else
                    workStateStyle.fontSize = offDayMarkSize_;
#endif
                    workStateStyle.color = offDayMarkColor_;
                }
            } else {
#ifndef USE_ROSEN_DRAWING
                if (day.dayMark == "work") {
#ifndef USE_GRAPHIC_TEXT_GINE
                    workStateStyle.font_size = workDayMarkSize_;
#else
                    workStateStyle.fontSize = workDayMarkSize_;
#endif
                    workStateStyle.color = isV2Component_ ? SkColorSetA(workDayMarkColor_, WEEKEND_TRANSPARENT)
                                                          : nonCurrentMonthWorkDayMarkColor_;
                } else if (day.dayMark == "off") {
#ifndef USE_GRAPHIC_TEXT_GINE
                    workStateStyle.font_size = offDayMarkSize_;
#else
                    workStateStyle.fontSize = offDayMarkSize_;
#endif
                    workStateStyle.color = isV2Component_ ? SkColorSetA(offDayMarkColor_, WEEKEND_TRANSPARENT)
                                                          : nonCurrentMonthOffDayMarkColor_;
                }
#else
                if (day.dayMark == "work") {
#ifndef USE_GRAPHIC_TEXT_GINE
                    workStateStyle.font_size = workDayMarkSize_;
#else
                    workStateStyle.fontSize = workDayMarkSize_;
#endif
                    workStateStyle.color = isV2Component_ ?
                        RSColor::ColorQuadSetARGB(WEEKEND_TRANSPARENT, RSColor::ColorQuadGetR(workDayMarkColor_),
                        RSColor::ColorQuadGetG(workDayMarkColor_), RSColor::ColorQuadGetB(workDayMarkColor_))
                        : nonCurrentMonthWorkDayMarkColor_;
                } else if (day.dayMark == "off") {
#ifndef USE_GRAPHIC_TEXT_GINE
                    workStateStyle.font_size = offDayMarkSize_;
#else
                    workStateStyle.fontSize = offDayMarkSize_;
#endif
                    workStateStyle.color = isV2Component_ ?
                        RSColor::ColorQuadSetARGB(WEEKEND_TRANSPARENT, RSColor::ColorQuadGetR(offDayMarkColor_),
                        RSColor::ColorQuadGetG(offDayMarkColor_), RSColor::ColorQuadGetB(offDayMarkColor_))
                        : nonCurrentMonthOffDayMarkColor_;
                }
#endif
            }
            if (day.focused) {
                workStateStyle.color = Color::BLACK.GetValue();
            }
            if (isV2Component_ && IsToday(day) && day.touched) {
                workStateStyle.color = focusedDayColor_;
            }
        }
        DrawCalendarText(canvas, day.dayMarkValue, workStateStyle, boxRect);
    }
}

#ifndef USE_ROSEN_DRAWING
#ifndef USE_GRAPHIC_TEXT_GINE
void RosenRenderCalendar::PaintLunarDay(
    SkCanvas* canvas, const Offset& offset, const CalendarDay& day, const txt::TextStyle& textStyle) const
#else
void RosenRenderCalendar::PaintLunarDay(
    SkCanvas* canvas, const Offset& offset, const CalendarDay& day, const Rosen::TextStyle& textStyle) const
#endif
#else
#ifndef USE_GRAPHIC_TEXT_GINE
void RosenRenderCalendar::PaintLunarDay(
    RSCanvas* canvas, const Offset& offset, const CalendarDay& day, const txt::TextStyle& textStyle) const
#else
void RosenRenderCalendar::PaintLunarDay(
    RSCanvas* canvas, const Offset& offset, const CalendarDay& day, const Rosen::TextStyle& textStyle) const
#endif
#endif
{
    Rect boxRect;
    cardCalendar_ || isV2Component_
        ? boxRect = { offset.GetX(), offset.GetY(), dayWidth_, NormalizeToPx(calendarTheme_.lunarHeight) }
        : boxRect = { offset.GetX(), offset.GetY(), dayWidth_, dayHeight_ - gregorianCalendarHeight_ };
    DrawCalendarText(canvas, day.lunarDay, textStyle, boxRect);
}

#ifndef USE_GRAPHIC_TEXT_GINE
void RosenRenderCalendar::SetNonFocusStyle(
    const CalendarDay& day, txt::TextStyle& dateTextStyle, txt::TextStyle& lunarTextStyle)
#else
void RosenRenderCalendar::SetNonFocusStyle(
    const CalendarDay& day, Rosen::TextStyle& dateTextStyle, Rosen::TextStyle& lunarTextStyle)
#endif
{
#ifndef USE_ROSEN_DRAWING
    SkColor dateTextColor;
    SkColor lunarTextColor;
    if (day.month.month != currentMonth_.month) {
        dateTextColor = nonCurrentMonthDayColor_;
        lunarTextColor =
            day.markLunarDay ? SkColorSetA(markLunarColor_, WEEKEND_TRANSPARENT) : nonCurrentMonthLunarColor_;
#else
    RSColorQuad dateTextColor;
    RSColorQuad lunarTextColor;
    if (day.month.month != currentMonth_.month) {
        dateTextColor = nonCurrentMonthDayColor_;
        lunarTextColor = day.markLunarDay ? RSColor::ColorQuadSetARGB(WEEKEND_TRANSPARENT,
            RSColor::ColorQuadGetR(markLunarColor_), RSColor::ColorQuadGetG(markLunarColor_),
            RSColor::ColorQuadGetB(markLunarColor_)) : nonCurrentMonthLunarColor_;
#endif
    } else if (IsToday(day)) {
        dateTextColor = todayDayColor_;
        lunarTextColor = todayLunarColor_;
    } else if (IsOffDay(day)) {
        dateTextColor = weekendDayColor_;
        lunarTextColor = day.markLunarDay ? markLunarColor_ : weekendLunarColor_;
    } else {
        dateTextColor = dayColor_;
        lunarTextColor = day.markLunarDay ? markLunarColor_ : lunarColor_;
    }

    dateTextStyle.color = dateTextColor;
    lunarTextStyle.color = lunarTextColor;
}

void RosenRenderCalendar::DrawTouchedArea(RenderContext& context, Offset offset) const
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("paint canvas is null");
        return;
    }
    if (IsValid(touchIndex_) && IsToday(calendarDays_[touchIndex_])) {
        return;
    }
    offset += { touchCircleStrokeWidth_, 0 };
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setColor(focusedAreaBackgroundColor_);
    paint.setStrokeWidth(touchCircleStrokeWidth_);
    paint.setStyle(SkPaint::kStroke_Style);
#else
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetColor(focusedAreaBackgroundColor_);
    pen.SetWidth(touchCircleStrokeWidth_);
#endif
    static const Dimension dateOffset = 4.0_vp;
    const static int32_t totalWeek = 7;
    int32_t column = touchIndex_ % totalWeek;
    double dailyRowSpace = rowCount_ == 5 ? dailyFiveRowSpace_ : dailySixRowSpace_;
    double dayNumberStartY = topPadding_ + weekHeight_ + weekAndDayRowSpace_ + NormalizeToPx(dateOffset);
    double x = textDirection_ == TextDirection::LTR ? column * (dayWidth_ + colSpace_)
                                                    : (totalWeek - column - 1) * (dayWidth_ + colSpace_);
    double y = (touchIndex_ / 7) * (dayHeight_ + dailyRowSpace) + dayNumberStartY;
    Offset circleCenter = Offset(x - (focusedAreaRadius_ * 2 - dayWidth_) / 2 + focusedAreaRadius_,
        y - NormalizeToPx(1.0_vp) + focusedAreaRadius_);
    Offset bgCircleStart = offset + circleCenter;
#ifndef USE_ROSEN_DRAWING
    canvas->drawCircle(bgCircleStart.GetX(), bgCircleStart.GetY(), focusedAreaRadius_, paint);
#else
    canvas->AttachPen(pen);
    canvas->DrawCircle(RSPoint(bgCircleStart.GetX(), bgCircleStart.GetY()), focusedAreaRadius_);
    canvas->DetachPen();
#endif
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderCalendar::DrawCardCalendar(
    SkCanvas* canvas, const Offset& offset, const Offset& dayOffset, const CalendarDay& day, int32_t dateNumber)
#else
void RosenRenderCalendar::DrawCardCalendar(
    RSCanvas* canvas, const Offset& offset, const Offset& dayOffset, const CalendarDay& day, int32_t dateNumber)
#endif
{
#ifndef USE_GRAPHIC_TEXT_GINE
    txt::TextStyle dateTextStyle;
    txt::TextStyle lunarTextStyle;
#else
    Rosen::TextStyle dateTextStyle;
    Rosen::TextStyle lunarTextStyle;
#endif
    InitTextStyle(dateTextStyle, lunarTextStyle);
    SetNonFocusStyle(day, dateTextStyle, lunarTextStyle);
    dateTextStyle.locale = Localization::GetInstance()->GetFontLocale();
    auto x = dayOffset.GetX();
    auto y = dayOffset.GetY();
    if (isV2Component_) {
        if (calendarController_->FirstSetToday() && IsToday(day) && (day.month.month == currentMonth_.month)) {
            calendarDays_[day.index].touched = true;
            touchIndex_ = day.index;
            calendarController_->SetFirstSetToday(false);
        }
    }
    if (IsToday(day) && (day.month.month == currentMonth_.month)) {
        dateTextStyle.color = isV2Component_ ? focusedAreaBackgroundColor_ : focusedDayColor_;
        lunarTextStyle.color = isV2Component_ ? focusedAreaBackgroundColor_ : focusedDayColor_;
        if (!isV2Component_) {
            DrawFocusedArea(canvas, offset, day, x, y);
        }
    }

    if (isV2Component_ && day.touched) {
        if (IsToday(day) && (day.month.month == currentMonth_.month)) {
            dateTextStyle.color = focusedDayColor_;
            lunarTextStyle.color = focusedDayColor_;
            DrawFocusedArea(canvas, offset, day, x, y);
        }
    }

    if (needShrink_) {
        Offset dateNumberOffset = offset + Offset(x, y + (focusedAreaRadius_ - gregorianCalendarHeight_ / 2));
        PaintDay(canvas, dateNumberOffset, day, dateTextStyle);
        return;
    }

    auto dayYAxisOffset = calendarTheme_.dayYAxisOffset;
    Offset dateNumberOffset = offset + Offset(x, y + NormalizeToPx(dayYAxisOffset));
    PaintDay(canvas, dateNumberOffset, day, dateTextStyle);

    if (dataAdapter_->ShowLunar() && !day.lunarDay.empty()) {
        auto lunarDayYAxisOffset = calendarTheme_.lunarDayYAxisOffset;
        Offset lunarDayOffset = offset + Offset(x, y + NormalizeToPx(lunarDayYAxisOffset));
        PaintLunarDay(canvas, lunarDayOffset, day, lunarTextStyle);
    }

    if (day.isFirstOfLunar) {
        auto underscoreXAxisOffset = calendarTheme_.underscoreXAxisOffset;
        auto underscoreYAxisOffset = calendarTheme_.underscoreYAxisOffset;
        Offset underscoreOffset =
            offset + Offset(x + NormalizeToPx(underscoreXAxisOffset), y + NormalizeToPx(underscoreYAxisOffset));
        PaintUnderscore(canvas, underscoreOffset, day);
    }

    if (day.hasSchedule) {
        auto scheduleMarkerXAxisOffset = calendarTheme_.scheduleMarkerXAxisOffset;
        auto scheduleMarkerYAxisOffset = calendarTheme_.scheduleMarkerYAxisOffset;
        Offset scheduleMarkerOffset =
            offset + Offset(x + NormalizeToPx(scheduleMarkerXAxisOffset), y + NormalizeToPx(scheduleMarkerYAxisOffset));
        PaintScheduleMarker(canvas, scheduleMarkerOffset, day);
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderCalendar::DrawTvCalendar(
    SkCanvas* canvas, const Offset& offset, const Offset& dayOffset, const CalendarDay& day, int32_t dateNumber)
#else
void RosenRenderCalendar::DrawTvCalendar(RSCanvas* canvas,
    const Offset& offset, const Offset& dayOffset, const CalendarDay& day, int32_t dateNumber)
#endif
{
    if ((SystemProperties::GetDeviceType() == DeviceType::WATCH || type_ == CalendarType::SIMPLE) &&
        day.month.month != currentMonth_.month) {
        return;
    }
#ifndef USE_GRAPHIC_TEXT_GINE
    txt::TextStyle dateTextStyle;
    txt::TextStyle lunarTextStyle;
#else
    Rosen::TextStyle dateTextStyle;
    Rosen::TextStyle lunarTextStyle;
#endif
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
    if (SystemProperties::GetDeviceType() == DeviceType::WATCH || type_ == CalendarType::SIMPLE) {
        if (IsToday(day) && (day.month.month == currentMonth_.month)) {
            dateTextStyle.color = focusedDayColor_;
            lunarTextStyle.color = focusedDayColor_;
            DrawFocusedArea(canvas, offset, day, x, y);
        } else {
            SetNonFocusStyle(day, dateTextStyle, lunarTextStyle);
        }
    } else {
        if (day.focused && day.month.month == currentMonth_.month && !renderSwiper->GetMoveStatus() &&
            indexOfContainer_ == calendarController_->GetCurrentIndex()) {
            dateTextStyle.color = focusedDayColor_;
            lunarTextStyle.color = focusedLunarColor_;
            DrawFocusedArea(canvas, offset, day, x, y);
        } else {
            SetNonFocusStyle(day, dateTextStyle, lunarTextStyle);
        }
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

#ifndef USE_GRAPHIC_TEXT_GINE
void RosenRenderCalendar::InitTextStyle(txt::TextStyle& dateTextStyle, txt::TextStyle& lunarTextStyle)
{
    dateTextStyle.font_size = dayFontSize_;
    dateTextStyle.font_weight = static_cast<txt::FontWeight>(dayFontWeight_);

    lunarTextStyle.font_size = lunarDayFontSize_;
    lunarTextStyle.font_weight = static_cast<txt::FontWeight>(lunarDayFontWeight_);
}
#else
void RosenRenderCalendar::InitTextStyle(Rosen::TextStyle& dateTextStyle, Rosen::TextStyle& lunarTextStyle)
{
    dateTextStyle.fontSize = dayFontSize_;
    dateTextStyle.fontWeight = static_cast<Rosen::FontWeight>(dayFontWeight_);

    lunarTextStyle.fontSize = lunarDayFontSize_;
    lunarTextStyle.fontWeight = static_cast<Rosen::FontWeight>(lunarDayFontWeight_);
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderCalendar::PaintUnderscore(SkCanvas* canvas, const Offset& offset, const CalendarDay& day)
{
    auto underscoreWidth = calendarTheme_.underscoreWidth;
    auto underscoreLength = calendarTheme_.underscoreLength;
    SkPaint paint;
    SkColor color;
    if (day.month.month != currentMonth_.month) {
        color = SkColorSetA(focusedAreaBackgroundColor_, NON_CURRENT_MONTH_TRANSPARENT);
    } else if (IsToday(day)) {
        color = isV2Component_ && !day.touched ? SkColorSetA(focusedAreaBackgroundColor_, CURRENT_MONTH_TRANSPARENT)
                                               : focusedDayColor_;
    } else if (day.weekend) {
        color = SkColorSetA(focusedAreaBackgroundColor_, WEEKEND_TRANSPARENT);
    } else {
        color = SkColorSetA(focusedAreaBackgroundColor_, CURRENT_MONTH_TRANSPARENT);
    }
    paint.setAntiAlias(true);
    paint.setColor(color);
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setStrokeWidth(NormalizeToPx(underscoreWidth));
    canvas->drawLine(offset.GetX(), offset.GetY() + NormalizeToPx(underscoreWidth) / 2,
        offset.GetX() + NormalizeToPx(underscoreLength), offset.GetY() + NormalizeToPx(underscoreWidth) / 2, paint);
}
#else
void RosenRenderCalendar::PaintUnderscore(RSCanvas* canvas, const Offset& offset, const CalendarDay& day)
{
    auto underscoreWidth = calendarTheme_.underscoreWidth;
    auto underscoreLength = calendarTheme_.underscoreLength;
    RSPen pen;
    RSColorQuad color;
    if (day.month.month != currentMonth_.month) {
        color = RSColor::ColorQuadSetARGB(NON_CURRENT_MONTH_TRANSPARENT,
            RSColor::ColorQuadGetR(focusedAreaBackgroundColor_), RSColor::ColorQuadGetG(focusedAreaBackgroundColor_),
            RSColor::ColorQuadGetB(focusedAreaBackgroundColor_));
    } else if (IsToday(day)) {
        color = isV2Component_ && !day.touched
            ? RSColor::ColorQuadSetARGB(CURRENT_MONTH_TRANSPARENT, RSColor::ColorQuadGetR(focusedAreaBackgroundColor_),
            RSColor::ColorQuadGetG(focusedAreaBackgroundColor_), RSColor::ColorQuadGetB(focusedAreaBackgroundColor_))
            : focusedDayColor_;
    } else if (day.weekend) {
        color = RSColor::ColorQuadSetARGB(WEEKEND_TRANSPARENT, RSColor::ColorQuadGetR(focusedAreaBackgroundColor_),
            RSColor::ColorQuadGetG(focusedAreaBackgroundColor_), RSColor::ColorQuadGetB(focusedAreaBackgroundColor_));
    } else {
        color = RSColor::ColorQuadSetARGB(CURRENT_MONTH_TRANSPARENT,
            RSColor::ColorQuadGetR(focusedAreaBackgroundColor_), RSColor::ColorQuadGetG(focusedAreaBackgroundColor_),
            RSColor::ColorQuadGetB(focusedAreaBackgroundColor_));
    }
    pen.SetAntiAlias(true);
    pen.SetColor(color);
    pen.SetWidth(NormalizeToPx(underscoreWidth));
    canvas->AttachPen(pen);
    canvas->DrawLine(RSPoint(offset.GetX(), offset.GetY() + NormalizeToPx(underscoreWidth) / 2),
        RSPoint(
            offset.GetX() + NormalizeToPx(underscoreLength), offset.GetY() + NormalizeToPx(underscoreWidth) / 2));
    canvas->DetachPen();
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderCalendar::PaintScheduleMarker(SkCanvas* canvas, const Offset& offset, const CalendarDay& day)
{
    auto scheduleMarkerRadius = calendarTheme_.scheduleMarkerRadius;
    SkPaint paint;
    SkColor color;
    if (day.month.month != currentMonth_.month) {
        color = SkColorSetA(focusedAreaBackgroundColor_, NON_CURRENT_MONTH_TRANSPARENT);
    } else if (IsToday(day)) {
        color = isV2Component_ && !day.touched ? SkColorSetA(focusedAreaBackgroundColor_, SCHEDULE_MARKER_TRANSPARENT)
                                               : focusedDayColor_;
    } else {
        color = SkColorSetA(focusedAreaBackgroundColor_, SCHEDULE_MARKER_TRANSPARENT);
    }
    paint.setAntiAlias(true);
    paint.setColor(color);
    canvas->drawCircle(offset.GetX(), offset.GetY(), NormalizeToPx(scheduleMarkerRadius), paint);
}
#else
void RosenRenderCalendar::PaintScheduleMarker(RSCanvas* canvas, const Offset& offset, const CalendarDay& day)
{
    auto scheduleMarkerRadius = calendarTheme_.scheduleMarkerRadius;
    RSBrush brush;
    RSColorQuad color;
    if (day.month.month != currentMonth_.month) {
        color = RSColor::ColorQuadSetARGB(NON_CURRENT_MONTH_TRANSPARENT,
            RSColor::ColorQuadGetR(focusedAreaBackgroundColor_), RSColor::ColorQuadGetG(focusedAreaBackgroundColor_),
            RSColor::ColorQuadGetB(focusedAreaBackgroundColor_));
    } else if (IsToday(day)) {
        color = isV2Component_ && !day.touched
            ? RSColor::ColorQuadSetARGB(SCHEDULE_MARKER_TRANSPARENT,
            RSColor::ColorQuadGetR(focusedAreaBackgroundColor_), RSColor::ColorQuadGetG(focusedAreaBackgroundColor_),
            RSColor::ColorQuadGetB(focusedAreaBackgroundColor_)) : focusedDayColor_;
    } else {
        color = RSColor::ColorQuadSetARGB(SCHEDULE_MARKER_TRANSPARENT,
            RSColor::ColorQuadGetR(focusedAreaBackgroundColor_), RSColor::ColorQuadGetG(focusedAreaBackgroundColor_),
            RSColor::ColorQuadGetB(focusedAreaBackgroundColor_));
    }
    brush.SetAntiAlias(true);
    brush.SetColor(color);
    canvas->AttachBrush(brush);
    canvas->DrawCircle(RSPoint(offset.GetX(), offset.GetY()), NormalizeToPx(scheduleMarkerRadius));
    canvas->DetachBrush();
}
#endif

#ifndef USE_GRAPHIC_TEXT_GINE
void RosenRenderCalendar::InitWorkStateStyle(
    const CalendarDay& day, const Offset& offset, txt::TextStyle& workStateStyle, Rect& boxRect) const
{
    workStateStyle.font_weight = static_cast<txt::FontWeight>(FontWeight::W500);
#else
void RosenRenderCalendar::InitWorkStateStyle(
    const CalendarDay& day, const Offset& offset, Rosen::TextStyle& workStateStyle, Rect& boxRect) const
{
    workStateStyle.fontWeight = static_cast<Rosen::FontWeight>(FontWeight::W500);
#endif
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

#ifndef USE_GRAPHIC_TEXT_GINE
    workStateStyle.font_size = NormalizeToPx(workStateWidth);
#else
    workStateStyle.fontSize = NormalizeToPx(workStateWidth);
#endif

    if (day.month.month != currentMonth_.month) {
#ifndef USE_ROSEN_DRAWING
        auto offColor = SkColorSetA(markLunarColor_, WEEKEND_TRANSPARENT);
        auto workColor = SkColorSetA(workDayMarkColor_, WEEKEND_TRANSPARENT);
#else
        auto offColor = RSColor::ColorQuadSetARGB(WEEKEND_TRANSPARENT, RSColor::ColorQuadGetR(markLunarColor_),
            RSColor::ColorQuadGetG(markLunarColor_), RSColor::ColorQuadGetB(markLunarColor_));
        auto workColor = RSColor::ColorQuadSetARGB(WEEKEND_TRANSPARENT, RSColor::ColorQuadGetR(workDayMarkColor_),
            RSColor::ColorQuadGetG(workDayMarkColor_), RSColor::ColorQuadGetB(workDayMarkColor_));
#endif
        SetWorkStateStyle(day, workColor, offColor, workStateStyle);
    } else if (IsToday(day)) {
        SetWorkStateStyle(day, focusedDayColor_, focusedDayColor_, workStateStyle);
    } else if (IsOffDay(day)) {
        auto offColor = markLunarColor_;
        auto workColor = workDayMarkColor_;
        SetWorkStateStyle(day, workColor, offColor, workStateStyle);
    } else {
        SetWorkStateStyle(day, workDayMarkColor_, markLunarColor_, workStateStyle);
    }
}

#ifndef USE_ROSEN_DRAWING
#ifndef USE_GRAPHIC_TEXT_GINE
void RosenRenderCalendar::SetWorkStateStyle(
    const CalendarDay& day, SkColor workColor, SkColor offColor, txt::TextStyle& workStateStyle) const
#else
void RosenRenderCalendar::SetWorkStateStyle(
    const CalendarDay& day, SkColor workColor, SkColor offColor, Rosen::TextStyle& workStateStyle) const
#endif
#else
#ifndef USE_GRAPHIC_TEXT_GINE
void RosenRenderCalendar::SetWorkStateStyle(const CalendarDay& day, RSColorQuad workColor,
    RSColorQuad offColor, txt::TextStyle& workStateStyle) const
#else
void RosenRenderCalendar::SetWorkStateStyle(
    const CalendarDay& day, SkColor workColor, RSColorQuad offColor, Rosen::TextStyle& workStateStyle) const
#endif
#endif
{
    if (day.dayMark == "work") {
        workStateStyle.color = workColor;
    } else if (day.dayMark == "off") {
        workStateStyle.color = offColor;
    }
}

void RosenRenderCalendar::SetCalendarTheme()
{
    auto theme = GetTheme<CalendarTheme>();
    if (cardCalendar_ && theme) {
        calendarTheme_ = theme->GetCardCalendarTheme();
    }
#ifndef USE_ROSEN_DRAWING
    touchColor_ = SkColor(calendarTheme_.touchColor.GetValue());
    weekColor_ = SkColor(calendarTheme_.weekColor.GetValue());
    dayColor_ = SkColor(calendarTheme_.dayColor.GetValue());
    lunarColor_ = SkColor(calendarTheme_.lunarColor.GetValue());
    weekendDayColor_ = SkColor(calendarTheme_.weekendDayColor.GetValue());
    weekendLunarColor_ = SkColor(calendarTheme_.weekendLunarColor.GetValue());
    todayDayColor_ = SkColor(calendarTheme_.todayColor.GetValue());
    todayLunarColor_ = SkColor(calendarTheme_.todayLunarColor.GetValue());
    nonCurrentMonthDayColor_ = SkColor(calendarTheme_.nonCurrentMonthDayColor.GetValue());
    nonCurrentMonthLunarColor_ = SkColor(calendarTheme_.nonCurrentMonthLunarColor.GetValue());
    workDayMarkColor_ = SkColor(calendarTheme_.workDayMarkColor.GetValue());
    offDayMarkColor_ = SkColor(calendarTheme_.offDayMarkColor.GetValue());
    nonCurrentMonthWorkDayMarkColor_ = SkColor(calendarTheme_.nonCurrentMonthWorkDayMarkColor.GetValue());
    nonCurrentMonthOffDayMarkColor_ = SkColor(calendarTheme_.nonCurrentMonthOffDayMarkColor.GetValue());
    focusedDayColor_ = SkColor(calendarTheme_.focusedDayColor.GetValue());
    focusedLunarColor_ = SkColor(calendarTheme_.focusedLunarColor.GetValue());
    focusedAreaBackgroundColor_ = SkColor(calendarTheme_.focusedAreaBackgroundColor.GetValue());
    blurAreaBackgroundColor_ = SkColor(calendarTheme_.blurAreaBackgroundColor.GetValue());
    markLunarColor_ = SkColor(calendarTheme_.markLunarColor.GetValue());
#else
    touchColor_ = RSColorQuad(calendarTheme_.touchColor.GetValue());
    weekColor_ = RSColorQuad(calendarTheme_.weekColor.GetValue());
    dayColor_ = RSColorQuad(calendarTheme_.dayColor.GetValue());
    lunarColor_ = RSColorQuad(calendarTheme_.lunarColor.GetValue());
    weekendDayColor_ = RSColorQuad(calendarTheme_.weekendDayColor.GetValue());
    weekendLunarColor_ = RSColorQuad(calendarTheme_.weekendLunarColor.GetValue());
    todayDayColor_ = RSColorQuad(calendarTheme_.todayColor.GetValue());
    todayLunarColor_ = RSColorQuad(calendarTheme_.todayLunarColor.GetValue());
    nonCurrentMonthDayColor_ = RSColorQuad(calendarTheme_.nonCurrentMonthDayColor.GetValue());
    nonCurrentMonthLunarColor_ = RSColorQuad(calendarTheme_.nonCurrentMonthLunarColor.GetValue());
    workDayMarkColor_ = RSColorQuad(calendarTheme_.workDayMarkColor.GetValue());
    offDayMarkColor_ = RSColorQuad(calendarTheme_.offDayMarkColor.GetValue());
    nonCurrentMonthWorkDayMarkColor_ = RSColorQuad(calendarTheme_.nonCurrentMonthWorkDayMarkColor.GetValue());
    nonCurrentMonthOffDayMarkColor_ = RSColorQuad(calendarTheme_.nonCurrentMonthOffDayMarkColor.GetValue());
    focusedDayColor_ = RSColorQuad(calendarTheme_.focusedDayColor.GetValue());
    focusedLunarColor_ = RSColorQuad(calendarTheme_.focusedLunarColor.GetValue());
    focusedAreaBackgroundColor_ = RSColorQuad(calendarTheme_.focusedAreaBackgroundColor.GetValue());
    blurAreaBackgroundColor_ = RSColorQuad(calendarTheme_.blurAreaBackgroundColor.GetValue());
    markLunarColor_ = RSColorQuad(calendarTheme_.markLunarColor.GetValue());
#endif
    dayFontWeight_ = StringUtils::StringToFontWeight(calendarTheme_.dayFontWeight);
    lunarDayFontWeight_ = StringUtils::StringToFontWeight(calendarTheme_.lunarDayFontWeight);
    workStateFontWeight_ = StringUtils::StringToFontWeight(calendarTheme_.workStateFontWeight);
}

bool RosenRenderCalendar::IsOffDay(const CalendarDay& dayInfo) const
{
    auto weekday = Date::CalculateWeekDay(dayInfo.month.year, dayInfo.month.month + 1, dayInfo.day);
    std::vector<std::string> days;
    StringUtils::StringSplitter(offDays_, ',', days);
    bool setOffDay = true;
    for (const auto& day : days) {
        auto num = StringUtils::StringToInt(day);
        if (num < 0 || num > 6) {
            setOffDay = false;
            break;
        }
        if (num == weekday) {
            return true;
        }
    }
    if (!setOffDay) {
        if (weekday == 5 || weekday == 6) { // set default weekend
            return true;
        }
    }
    return false;
}

void RosenRenderCalendar::AddContentLayer(RenderContext& context)
{
#ifdef OHOS_PLATFORM
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!drawCmdList_) {
        return;
    }
    drawCmdList_->Playback(*canvas);
#endif
}

} // namespace OHOS::Ace
