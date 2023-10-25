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

#include "core/components_ng/pattern/calendar/calendar_month_pattern.h"

#include "base/geometry/offset.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CALENDAR_WEEK_DAYS = 7;
constexpr Dimension CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT = 4.0_vp;
} // namespace
void CalendarMonthPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

bool CalendarMonthPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (IsCalendarDialog()) {
        SetColRowSpace();
    }

    return !(config.skipMeasure || dirty->SkipMeasureContent());
}

void CalendarMonthPattern::SetColRowSpace()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto contentConstraint = host->GetLayoutProperty()->GetLayoutConstraint();
    if (!contentConstraint.has_value()) {
        return;
    }
    auto constraint = contentConstraint.value();

    auto dataSize = GetMonthData().days.size();
    if (dataSize <= 0) {
        return;
    }

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    auto width = constraint.selfIdealSize.Width().value() - CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT.ConvertToPx() * 2;
    auto height = constraint.selfIdealSize.Height().value() - CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT.ConvertToPx();
    auto paintProperty = GetPaintProperty<CalendarPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    auto calendarDaySize = theme->GetCalendarPickerDayWidthOrHeight();
    auto space = (width - calendarDaySize.ConvertToPx() * CALENDAR_WEEK_DAYS) / (CALENDAR_WEEK_DAYS - 1);
    if (Positive(space)) {
        Dimension colSpace = 0.0_px;
        colSpace.SetValue(space);
        paintProperty->UpdateColSpace(colSpace);
    }

    auto rowCount = dataSize / CALENDAR_WEEK_DAYS;
    space = (height - calendarDaySize.ConvertToPx() * (rowCount + 1)) / rowCount;
    if (!Positive(space)) {
        return;
    }
    Dimension rowSpace = 0.0_px;
    rowSpace.SetValue(space);
    paintProperty->UpdateWeekAndDayRowSpace(rowSpace);
    switch (rowCount) {
        case 4:
            paintProperty->UpdateDailyFourRowSpace(rowSpace);
            break;
        case 6:
            paintProperty->UpdateDailySixRowSpace(rowSpace);
            break;
        case 5:
        default:
            paintProperty->UpdateDailyFiveRowSpace(rowSpace);
            break;
    }
}

void CalendarMonthPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    InitClickEvent();
    InitTouchEvent();
    InitHoverEvent();
}

void CalendarMonthPattern::InitClickEvent()
{
    if (clickListener_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto obtainedMonth = obtainedMonth_;
    auto clickCallback = [weak = WeakClaim(this), obtainedMonth](GestureEvent& info) {
        auto calendarPattern = weak.Upgrade();
        CHECK_NULL_VOID(calendarPattern);
        auto localLocation = info.GetFingerList().begin()->localLocation_;
        calendarPattern->OnClick(localLocation, calendarPattern->obtainedMonth_);
    };
    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

void CalendarMonthPattern::InitTouchEvent()
{
    if (touchListener_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto calendarPattern = weak.Upgrade();
        CHECK_NULL_VOID(calendarPattern);
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            calendarPattern->OnTouchEvent(info.GetTouches().front().GetLocalLocation(), true);
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP ||
            info.GetTouches().front().GetTouchType() == TouchType::CANCEL) {
            calendarPattern->OnTouchEvent(info.GetTouches().front().GetLocalLocation(), false);
        }
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void CalendarMonthPattern::InitHoverEvent()
{
    if (hoverListener_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = GetEventHub<CalendarEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto hoverCallback = [weak = WeakClaim(this)](bool state) {
        auto calendarPattern = weak.Upgrade();
        CHECK_NULL_VOID(calendarPattern);
        calendarPattern->SetHoverState(state);
        if (!state) {
            Offset localLocation;
            calendarPattern->OnHoverEvent(localLocation, false);
        }
    };
    hoverListener_ = MakeRefPtr<InputEvent>(std::move(hoverCallback));
    inputHub->AddOnHoverEvent(hoverListener_);
    auto mouseCallback = [weak = WeakClaim(this)](MouseInfo& info) {
        auto calendarPattern = weak.Upgrade();
        CHECK_NULL_VOID(calendarPattern);
        calendarPattern->OnHoverEvent(info.GetLocalLocation(), calendarPattern->GetHoverState());
    };
    inputHub->SetMouseEvent(std::move(mouseCallback));
}

void CalendarMonthPattern::OnClick(Offset& localLocation, const ObtainedMonth& obtainedMonth)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<CalendarMonthPattern>();
    CHECK_NULL_VOID(pattern);
    auto index = JudgeArea(localLocation);
    pattern->obtainedMonth_ = obtainedMonth;
    if (!obtainedMonth_.days.empty()) {
        for (auto& day : pattern->obtainedMonth_.days) {
            day.focused = false;
        }
        auto calendarEventHub = GetEventHub<CalendarEventHub>();
        CHECK_NULL_VOID(calendarEventHub);
        if (index >= 0 && index < static_cast<int32_t>(obtainedMonth.days.size())) {
            pattern->obtainedMonth_.days[index].focused = true;
            auto json = JsonUtil::Create(true);
            json->Put("day", obtainedMonth.days[index].day);
            json->Put("month", obtainedMonth.days[index].month.month);
            json->Put("year", obtainedMonth.days[index].month.year);
            calendarEventHub->UpdateSelectedChangeEvent(json->ToString());
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void CalendarMonthPattern::OnTouchEvent(const Offset& localLocation, bool isPressed)
{
    if (!isCalendarDialog_ || obtainedMonth_.days.empty()) {
        return;
    }
    auto index = JudgeArea(localLocation);
    if (index < 0 || index >= obtainedMonth_.days.size()) {
        return;
    }
    if (isPressed) {
        obtainedMonth_.days[index].isPressing = true;
    } else {
        for (auto& day : obtainedMonth_.days) {
            day.isPressing = false;
        }
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CalendarMonthPattern::OnHoverEvent(const Offset& localLocation, bool state)
{
    if (!isCalendarDialog_ || obtainedMonth_.days.empty()) {
        return;
    }
    int32_t index = JudgeArea(localLocation);
    if (index < 0 || index >= obtainedMonth_.days.size()) {
        return;
    }
    for (auto& day : obtainedMonth_.days) {
        day.isHovering = false;
    }
    if (state) {
        obtainedMonth_.days[index].isHovering = true;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

int32_t CalendarMonthPattern::JudgeArea(const Offset& offset)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto paintProperty = host->GetPaintProperty<CalendarPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, false);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_RETURN(theme, false);
    auto topPadding = isCalendarDialog_ ? 0.0 : theme->GetCalendarTheme().topPadding.ConvertToPx();
    auto weekHeight = paintProperty->GetWeekHeight().value_or(theme->GetCalendarTheme().weekHeight).ConvertToPx();
    auto weekAndDayRowSpace =
        paintProperty->GetWeekAndDayRowSpace().value_or(theme->GetCalendarTheme().weekAndDayRowSpace).ConvertToPx();
    auto dayHeight = paintProperty->GetDayHeight().value_or(theme->GetCalendarTheme().dayHeight).ConvertToPx();
    auto dayWidth = paintProperty->GetDayWidth().value_or(theme->GetCalendarTheme().dayWidth).ConvertToPx();
    const static int32_t columnsOfData = 7;
    auto colSpace = paintProperty->GetColSpaceValue({}).ConvertToPx() <= 0
                        ? theme->GetCalendarTheme().colSpace.ConvertToPx()
                        : paintProperty->GetColSpaceValue({}).ConvertToPx();
    auto dailyFourRowSpace = NonPositive(paintProperty->GetDailyFourRowSpaceValue({}).ConvertToPx())
                                 ? theme->GetCalendarTheme().dailySixRowSpace.ConvertToPx()
                                 : paintProperty->GetDailyFourRowSpaceValue({}).ConvertToPx();
    auto dailyFiveRowSpace = paintProperty->GetDailyFiveRowSpaceValue({}).ConvertToPx() <= 0
                                 ? theme->GetCalendarTheme().dailyFiveRowSpace.ConvertToPx()
                                 : paintProperty->GetDailyFiveRowSpaceValue({}).ConvertToPx();
    auto dailySixRowSpace = paintProperty->GetDailySixRowSpaceValue({}).ConvertToPx() <= 0
                                ? theme->GetCalendarTheme().dailySixRowSpace.ConvertToPx()
                                : paintProperty->GetDailySixRowSpaceValue({}).ConvertToPx();
    auto rows = (static_cast<int32_t>(obtainedMonth_.days.size()) / columnsOfData);
    auto rowSpace = dailySixRowSpace;
    switch (rows) {
        case 4: {
            rowSpace = dailyFourRowSpace;
            break;
        }
        case 5: {
            rowSpace = dailyFiveRowSpace;
            break;
        }
        default:
            break;
    }
    auto browHeight = weekHeight + topPadding + weekAndDayRowSpace;
    auto maxHeight = host->GetGeometryNode()->GetFrameSize().Height();
    auto maxWidth = host->GetGeometryNode()->GetFrameSize().Width();
    if ((offset.GetX() < 0) || (offset.GetX() > maxWidth) || (offset.GetY() < browHeight) ||
        (offset.GetY() > maxHeight) || LessOrEqual(dayHeight, 0.0) || LessOrEqual(dayWidth, 0.0)) {
        return -1;
    }
    auto height = offset.GetY() - browHeight;
    int32_t y =
        height < (dayHeight + rowSpace / 2) ? 0 : (height - dayHeight - rowSpace / 2) / (dayHeight + rowSpace) + 1;
    int32_t x = offset.GetX() < (dayWidth + colSpace / 2)
                    ? 0
                    : (offset.GetX() - dayWidth - colSpace / 2) / (dayWidth + colSpace) + 1;
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        x = columnsOfData - x - 1;
    }
    return (y * columnsOfData + x);
}
} // namespace OHOS::Ace::NG
