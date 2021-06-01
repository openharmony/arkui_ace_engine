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

#include "core/components/calendar/render_calendar.h"

#include "base/i18n/localization.h"
#include "base/log/event_report.h"
#include "core/components/calendar/calendar_component.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t CALENDAR_MIN_WIDTH = 350;
constexpr int32_t CALENDAR_MIN_HEIGHT = 230;
constexpr int32_t DAYS_PER_WEEK = 7;

} // namespace

RenderCalendar::RenderCalendar()
{
    weekNumbers_ = Localization::GetInstance()->GetWeekdays(true);
}

void RenderCalendar::Update(const RefPtr<Component>& component)
{
    auto calendarMonth = AceType::DynamicCast<CalendarMonthComponent>(component);
    if (!calendarMonth) {
        LOGE("calendar month component is null");
        EventReport::SendRenderException(RenderExcepType::RENDER_COMPONENT_ERR);
        return;
    }

    auto context = context_.Upgrade();
    if (!context) {
        return;
    }

    selectedChangeEvent_ =
        AceAsyncEvent<void(const std::string&)>::Create(calendarMonth->GetSelectedChangeEvent(), context_);
    indexOfContainer_ = calendarMonth->GetIndexOfContainer();
    calendarController_ = calendarMonth->GetCalendarController();
    dataAdapter_ = calendarController_->GetDataAdapter();
    colCount_ = weekNumbers_.size();
    dataAdapter_->RegisterDataListener(AceType::Claim(this));
    clickDetector_ = AceType::MakeRefPtr<ClickRecognizer>();
    clickDetector_->SetOnClick([weak = WeakClaim(this)](const ClickInfo& info) {
        auto calendar = weak.Upgrade();
        if (calendar) {
            calendar->HandleClick(info.GetLocalLocation());
        }
    });
    OnDataChanged(dataAdapter_->GetDayOfMonthCache()[indexOfContainer_]);
    MarkNeedLayout();
}

void RenderCalendar::OnPaintFinish()
{
    UpdateAccessibility();
}

void RenderCalendar::UpdateAccessibility()
{
    auto node = GetAccessibilityNode().Upgrade();
    if (!node) {
        return;
    }
    if (!calendarController_) {
        return;
    }
    auto today = calendarController_->GetDataAdapter()->GetToday();
    DateTime dateTime;
    dateTime.year = today.month.year;
    dateTime.month = today.month.month;
    dateTime.day = today.day;
    auto dateText = Localization::GetInstance()->FormatDateTime(dateTime, "yyyyMMdd");
    node->SetText(dateText);
}

void RenderCalendar::PerformLayout()
{
    Size calendarMinSize(CALENDAR_MIN_WIDTH, CALENDAR_MIN_HEIGHT);
    LayoutParam innerLayout = GetLayoutParam();
    Size maxSize = innerLayout.GetMaxSize();
    Size layoutSize;
    if (maxSize.IsInfinite()) {
        Size minSize = innerLayout.GetMinSize();
        layoutSize = Size(
            std::max(minSize.Width(), calendarMinSize.Width()), std::max(minSize.Height(), calendarMinSize.Height()));
    } else {
        layoutSize = Size(
            std::max(maxSize.Width(), calendarMinSize.Width()), std::max(maxSize.Height(), calendarMinSize.Height()));
    }

    SetLayoutSize(layoutSize);
    maxWidth_ = maxSize.Width();
    maxHeight_ = maxSize.Height();
}

void RenderCalendar::OnDataChanged(const CalendarDaysOfMonth& daysOfMonth)
{
    if (currentMonth_ == daysOfMonth.month) {
        if (!cardCalendar_ && focusIndex_ >= 0 && focusIndex_ < static_cast<int32_t>(calendarDays_.size()) &&
            calendarDays_[focusIndex_].focused) {
            calendarDays_ = daysOfMonth.days;
            calendarDays_[focusIndex_].focused = true;
        } else {
            calendarDays_ = daysOfMonth.days;
        }
        MarkNeedRender();
        return;
    }
    calendarDays_ = daysOfMonth.days;
    currentMonth_ = daysOfMonth.month;
    firstDayIndex_ = daysOfMonth.firstDayIndex;
    lastDayIndex_ = daysOfMonth.lastDayIndex;
    if (GetCalendarController()->GetFirstEnter()) {
        selectedDayNumber_ = daysOfMonth.today - firstDayIndex_ + 1;
        GetCalendarController()->SetFirstEnter(false);
        OnStatusChanged(RenderStatus::FOCUS);
    }
    // the number of rows will be 5 or 6, and week number height is half of the date number
    rowCount_ = colCount_ ? daysOfMonth.days.size() / colCount_ : 0;
    calendarController_->JumpMonth();
    hasRequestFocus_ = false;
    cardCalendar_ ? MarkNeedLayout() : MarkNeedRender();
}

void RenderCalendar::OnSelectedDay(int32_t selected)
{
    selectedDayNumber_ = selected;
    CalendarDay day;
    if (selected < 0) {
        day.index = lastDayIndex_;
    } else {
        day.index = selectedDayNumber_ + firstDayIndex_ - 1;
    }
    if (!cardCalendar_) {
        if (calendarController_->GetFirstLoad()) {
            calendarController_->SetFirstLoad(false);
        } else {
            OnDateSelected(day);
        }
    }
    if (calendarController_->IsNeedFocus()) {
        calendarController_->RequestFocus();
        calendarController_->SetNeedFocus(false);
    }
    hasRequestFocus_ = true;
    MarkNeedRender();
}

void RenderCalendar::OnStatusChanged(RenderStatus renderStatus)
{
    int32_t calendarDaysSize = calendarDays_.size();
    if (renderStatus == RenderStatus::FOCUS) {
        int32_t focusedIndex = selectedDayNumber_ + firstDayIndex_ - 1;
        if (selectedDayNumber_ < 0) {
            focusedIndex = lastDayIndex_;
        }
        focusRow_ = focusedIndex / DAYS_PER_WEEK;
        focusCol_ = focusedIndex % DAYS_PER_WEEK;
        selectedDayNumber_ = focusedIndex - firstDayIndex_ + 1;
        focusIndex_ = focusedIndex;
        if (focusIndex_ >= 0 && focusIndex_ < calendarDaysSize) {
            calendarDays_[focusedIndex].focused = true;
            if (!cardCalendar_) {
                OnDateSelected(calendarDays_[focusedIndex]);
            }
        }
    } else if (renderStatus == RenderStatus::BLUR) {
        focusRow_ = -1;
        focusCol_ = -1;
        if (focusIndex_ >= 0 && focusIndex_ < calendarDaysSize) {
            calendarDays_[focusIndex_].focused = false;
        }
    }
    MarkNeedRender();
}

int32_t RenderCalendar::GetIndexByGrid(int32_t row, int32_t column)
{
    return (row * colCount_) + column;
}

void RenderCalendar::OnDateSelected(const CalendarDay& date)
{
    if (!cardCalendar_) {
        auto calendarCache = calendarController_->GetDataAdapter()->GetCalendarCache()[indexOfContainer_];
        if (selectedChangeEvent_ && date.index >= 0 && date.index < static_cast<int32_t>(calendarCache.size())) {
            std::string result = std::string("\"selectedchange\",").append(calendarCache[date.index]).append(",null");
            selectedChangeEvent_(result);
        }
    } else if (date.index >= 0 && date.index < static_cast<int32_t>(calendarDays_.size())) {
        auto result = JsonUtil::ParseJsonString(calendarDays_[date.index].ToString());
        if (selectedChangeEvent_) {
            selectedChangeEvent_(result->ToString());
        }
    }
}

void RenderCalendar::FocusChanged(int32_t oldIndex, int32_t newIndex)
{
    int32_t calendarDaysSize = calendarDays_.size();
    if (oldIndex < 0 || oldIndex >= calendarDaysSize) {
        LOGW("lost focus index is out of calendar days array");
        return;
    }
    calendarDays_[oldIndex].focused = false;

    auto pipelineContext = GetContext().Upgrade();
    if (!pipelineContext) {
        LOGE("pipeline context is null");
        return;
    }
    pipelineContext->CancelFocusAnimation();
    if (newIndex < 0) {
        calendarController_->GoToPrevMonth(-1);
        return;
    }
    if (newIndex >= calendarDaysSize) {
        calendarController_->GoToNextMonth(1);
        return;
    }

    auto& onFocusDay = calendarDays_[newIndex];
    if (onFocusDay.month < currentMonth_) {
        LOGD("focus move to last month");
        calendarController_->GoToPrevMonth(onFocusDay.day);
        return;
    } else if (calendarDays_[newIndex].month > currentMonth_) {
        LOGD("focus move to next month");
        calendarController_->GoToNextMonth(onFocusDay.day);
        return;
    }

    onFocusDay.focused = true;
    if (!cardCalendar_) {
        OnDateSelected(onFocusDay);
    }
}

void RenderCalendar::OnFocusChanged(bool focusStatus)
{
    calendarFocusStatus_ = focusStatus;
}

void RenderCalendar::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    clickDetector_->SetCoordinateOffset(coordinateOffset);
    result.emplace_back(clickDetector_);
}

void RenderCalendar::HandleClick(const Offset& offset)
{
    if (!cardCalendar_) {
        return;
    }
    auto index = JudgeArea(offset);
    if (index < 0 || index >= static_cast<int32_t>(calendarDays_.size())) {
        return;
    }
    CalendarDay day;
    day.index = index;
    OnDateSelected(day);
}

int32_t RenderCalendar::JudgeArea(const Offset& offset)
{
    const static int32_t rowsOfData = 5;
    auto rowSpace = rowCount_ == rowsOfData ? dailyFiveRowSpace_ : dailySixRowSpace_;
    auto topPadding = NormalizeToPx(calendarTheme_.topPadding);
    auto maxHeight = weekHeight_ + topPadding + rowCount_ * dayHeight_ + (rowCount_ - 1) * rowSpace;
    if ((offset.GetX() < 0) || (offset.GetX() > maxWidth_) || (offset.GetY() < weekHeight_) ||
        (offset.GetY() > maxHeight) || LessOrEqual(dayHeight_, 0.0) || LessOrEqual(dayWidth_, 0.0)) {
        return -1;
    }
    auto height = offset.GetY() - weekHeight_ - topPadding;
    int32_t y =
        height < (dayHeight_ + rowSpace / 2) ? 0 : (height - dayHeight_ - rowSpace / 2) / (dayHeight_ + rowSpace) + 1;
    int32_t x = offset.GetX() < (dayWidth_ + colSpace_ / 2)
                ? 0
                : (offset.GetX() - dayWidth_ - colSpace_ / 2) / (dayWidth_ + colSpace_) + 1;
    return (y * colCount_ + x);
}

void RenderCalendar::UpdateCardCalendarAttr(const CardCalendarAttr& attr)
{
    textDirection_ = attr.textDirection;
    showHoliday_ = attr.showHoliday;
    MarkNeedRender();
}

} // namespace OHOS::Ace
