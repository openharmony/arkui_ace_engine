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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CALENDAR_ROSEN_RENDER_CALENDAR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CALENDAR_ROSEN_RENDER_CALENDAR_H

#ifndef USE_GRAPHIC_TEXT_GINE
#include "third_party/txt/src/txt/text_style.h"
#else
#include "rosen_text/text_style.h"
#endif

#include "core/components/calendar/render_calendar.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Rosen {
    class DrawCmdList;
}
namespace OHOS::Ace {

class ScopedCanvas;

class RosenRenderCalendar : public RenderCalendar {
    DECLARE_ACE_TYPE(RosenRenderCalendar, RenderCalendar);

public:
    RosenRenderCalendar() = default;
    ~RosenRenderCalendar() override = default;

    void Update(const RefPtr<Component>& component) override;
    void Paint(RenderContext& context, const Offset& offset) override;
    void PerformLayout() override;

private:
    void DrawWeekAndDates(RSCanvas* canvas, Offset offset);
    void DrawFocusedArea(
        RSCanvas* canvas, const Offset& offset, const CalendarDay& day, double x, double y) const;
    void DrawWeek(RSCanvas* canvas, const Offset& offset) const;
    void DrawBlurArea(RSCanvas* canvas, const Offset& offset, double x, double y) const;
    void DrawTouchedArea(RenderContext& context, Offset offset) const;
#ifndef USE_GRAPHIC_TEXT_GINE
    void PaintDay(
        RSCanvas* canvas, const Offset& offset, const CalendarDay& day, txt::TextStyle& textStyle) const;
    void PaintLunarDay(RSCanvas* canvas, const Offset& offset, const CalendarDay& day,
        const txt::TextStyle& textStyle) const;
    void HandleAdditionalConditions(RSCanvas* canvas, const Offset& offset, const Offset& dayOffset,
         const CalendarDay& day, txt::TextStyle& lunarTextStyle);
    void SetTextStyleColor(txt::TextStyle& dateTextStyle, txt::TextStyle& lunarTextStyle);
#else
    void PaintDay(
        RSCanvas* canvas, const Offset& offset, const CalendarDay& day, Rosen::TextStyle& textStyle) const;
    void PaintLunarDay(RSCanvas* canvas, const Offset& offset, const CalendarDay& day,
        const Rosen::TextStyle& textStyle) const;
    void HandleAdditionalConditions(RSCanvas* canvas, const Offset& offset, const Offset& dayOffset,
         const CalendarDay& day, Rosen::TextStyle& lunarTextStyle);
    void SetTextStyleColor(Rosen::TextStyle& dateTextStyle, Rosen::TextStyle& lunarTextStyle);
#endif
#ifndef USE_GRAPHIC_TEXT_GINE
    void SetNonFocusStyle(const CalendarDay& day, txt::TextStyle& dateTextStyle, txt::TextStyle& lunarTextStyle);
#else
    void SetNonFocusStyle(const CalendarDay& day, Rosen::TextStyle& dateTextStyle, Rosen::TextStyle& lunarTextStyle);
#endif
    void DrawCardCalendar(RSCanvas* canvas, const Offset& offset, const Offset& dayOffset,
        const CalendarDay& day, int32_t dateNumber);
    void DrawTvCalendar(RSCanvas* canvas, const Offset& offset, const Offset& dayOffset,
        const CalendarDay& day, int32_t dateNumber);
#ifndef USE_GRAPHIC_TEXT_GINE
    void InitTextStyle(txt::TextStyle& dateTextStyle, txt::TextStyle& lunarTextStyle);
#else
    void InitTextStyle(Rosen::TextStyle& dateTextStyle, Rosen::TextStyle& lunarTextStyle);
#endif
    void PaintUnderscore(RSCanvas* canvas, const Offset& offset, const CalendarDay& day);
    void PaintScheduleMarker(RSCanvas* canvas, const Offset& offset, const CalendarDay& day);
#ifndef USE_GRAPHIC_TEXT_GINE
    void InitWorkStateStyle(
        const CalendarDay& day, const Offset& offset, txt::TextStyle& workStateStyle, Rect& boxRect) const;
#else
    void InitWorkStateStyle(
        const CalendarDay& day, const Offset& offset, Rosen::TextStyle& workStateStyle, Rect& boxRect) const;
#endif
#ifndef USE_GRAPHIC_TEXT_GINE
    void SetWorkStateStyle(const CalendarDay& day, RSColorQuad workColor,
        RSColorQuad offColor, txt::TextStyle& workStateStyle) const;
#else
    void SetWorkStateStyle(const CalendarDay& day, RSColorQuad workColor,
        RSColorQuad offColor, Rosen::TextStyle& workStateStyle) const;
#endif
    void SetCalendarTheme();
    bool IsOffDay(const CalendarDay& day) const;
    void AddContentLayer(RenderContext& context);

    bool needShrink_ = false;
    double weekFontSize_ = 0.0;
    double dayFontSize_ = 0.0;
    double lunarDayFontSize_ = 0.0;
    double workDayMarkSize_ = 0.0;
    double offDayMarkSize_ = 0.0;
    double focusedAreaRadius_ = 0.0;
    double topPadding_ = 0.0;
    double weekWidth_ = 0.0;
    double weekAndDayRowSpace_ = 0.0;
    double gregorianCalendarHeight_ = 0.0;
    double workStateWidth_ = 0.0;
    double workStateHorizontalMovingDistance_ = 0.0;
    double workStateVerticalMovingDistance_ = 0.0;
    double touchCircleStrokeWidth_ = 0.0;

    RSColorQuad weekColor_;
    RSColorQuad touchColor_;
    RSColorQuad dayColor_;
    RSColorQuad lunarColor_;
    RSColorQuad weekendDayColor_;
    RSColorQuad weekendLunarColor_;
    RSColorQuad todayDayColor_;
    RSColorQuad todayLunarColor_;
    RSColorQuad nonCurrentMonthDayColor_;
    RSColorQuad nonCurrentMonthLunarColor_;
    RSColorQuad workDayMarkColor_;
    RSColorQuad offDayMarkColor_;
    RSColorQuad nonCurrentMonthWorkDayMarkColor_;
    RSColorQuad nonCurrentMonthOffDayMarkColor_;
    RSColorQuad focusedDayColor_;
    RSColorQuad focusedLunarColor_;
    RSColorQuad focusedAreaBackgroundColor_;
    RSColorQuad blurAreaBackgroundColor_;
    RSColorQuad markLunarColor_;

    Size lastLayoutSize_;
    FontWeight dayFontWeight_ = FontWeight::W500;
    FontWeight lunarDayFontWeight_ = FontWeight::W500;
    FontWeight workStateFontWeight_ = FontWeight::W400;
    std::shared_ptr<RSDrawCmdList> drawCmdList_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CALENDAR_ROSEN_RENDER_CALENDAR_H
