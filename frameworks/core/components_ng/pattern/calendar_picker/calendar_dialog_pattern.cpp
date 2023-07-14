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

#include "core/components_ng/pattern/calendar_picker/calendar_dialog_pattern.h"

#include "base/utils/date_util.h"
#include "core/components/calendar/calendar_data_adapter.h"
#include "core/components_ng/pattern/calendar/calendar_model_ng.h"
#include "core/components_ng/pattern/calendar/calendar_month_pattern.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_layout_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TITLE_NODE_INDEX = 0;
constexpr int32_t CALENDAR_NODE_INDEX = 1;
constexpr int32_t OPTIONS_NODE_INDEX = 2;
constexpr int32_t TITLE_LAST_YEAR_BUTTON_NODE_INDEX = 0;
constexpr int32_t TITLE_LAST_MONTH_BUTTON_NODE_INDEX = 1;
constexpr int32_t TITLE_TEXT_NODE_INDEX = 2;
constexpr int32_t TITLE_NEXT_MONTH_BUTTON_NODE_INDEX = 3;
constexpr int32_t TITLE_NEXT_YEAR_BUTTON_NODE_INDEX = 4;
constexpr int32_t OPTIONS_DIVIDER_NODE_INDEX = 1;
constexpr int32_t SWIPER_CHILDREN_SIZE = 3;
constexpr int32_t WEEK_DAYS = 7;
constexpr int32_t MAX_MONTH = 12;
constexpr int32_t MIN_YEAR = 1;
constexpr int32_t MAX_YEAR = 5000;
} // namespace
void CalendarDialogPattern::OnModifyDone()
{
    LinearLayoutPattern::OnModifyDone();
    InitClickEvent();
    InitOnKeyEvent();
    InitOnTouchEvent();
    InitTitleArrowsEvent();
    InitEntryChangeEvent();
}

void CalendarDialogPattern::InitClickEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleClickEvent(info);
    };
    auto onClick = AceType::MakeRefPtr<ClickEvent>(clickCallback);
    gesture->AddClickEvent(onClick);
}

void CalendarDialogPattern::HandleClickEvent(const GestureEvent& info)
{
    CHECK_NULL_VOID_NOLOG(entryNode_);
    auto geometryNode = entryNode_->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    geometryNode->SetFrameOffset(entryNode_->GetPaintRectOffset());
    auto clickGlobalPosition = info.GetGlobalLocation();
    auto clickPoint = PointF(clickGlobalPosition.GetX(), clickGlobalPosition.GetY());
    if (geometryNode->GetFrameRect().IsInRegion(clickPoint)) {
        auto pattern = entryNode_->GetPattern<CalendarPickerPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->HandleClickEvent(info);
    }
}

void CalendarDialogPattern::InitOnTouchEvent()
{
    if (touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            if (!pattern->isFocused_) {
                return;
            }
            pattern->isFocused_ = false;
            pattern->isCalendarFirstFocused_ = false;
            pattern->ClearCalendarFocusedState();
        }
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void CalendarDialogPattern::InitOnKeyEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);

    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN_NOLOG(pattern, false);
        if (event.IsNumberKey()&& event.action == KeyAction::DOWN) {
            CHECK_NULL_RETURN(pattern->entryNode_, false);
            auto entryPattern = pattern->entryNode_->GetPattern<CalendarPickerPattern>();
            CHECK_NULL_RETURN(entryPattern, false);
            entryPattern->HandleNumberKeyEvent(event);
        }
        if (pattern->isFocused_ && !pattern->isCalendarFirstFocused_ &&
            pattern->focusAreaID_ == CALENDAR_NODE_INDEX) {
            pattern->isCalendarFirstFocused_ = true;
            pattern->FocusedLastFocusedDay();
            return true;
        }
        if (pattern->isFocused_ && event.action == KeyAction::DOWN) {
            return pattern->HandleKeyEvent(event);
        }
        return false;
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));

    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        if (pattern) {
            pattern->GetInnerFocusPaintRect(paintRect);
        }
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);
}

void CalendarDialogPattern::InitEntryChangeEvent()
{
    CHECK_NULL_VOID_NOLOG(entryNode_);
    auto eventHub = entryNode_->GetEventHub<CalendarPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto callback = [weak = WeakClaim(this)](const std::string& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleEntryChange(info);
    };
    eventHub->SetInputChangeEvent(std::move(callback));
    auto layoutChangeEvent = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleEntryLayoutChange();
    };
    eventHub->SetLayoutChangeEvent(layoutChangeEvent);
}

bool CalendarDialogPattern::HandleKeyEvent(const KeyEvent& event)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);

    if (event.code == KeyCode::KEY_TAB) {
        return HandleTabKeyEvent(event);
    }
    if (focusAreaID_ == CALENDAR_NODE_INDEX) {
        return HandleCalendarNodeKeyEvent(event);
    }
    if (focusAreaID_ != TITLE_NODE_INDEX && focusAreaID_ != OPTIONS_NODE_INDEX) {
        return false;
    }

    switch (event.code) {
        case KeyCode::KEY_DPAD_LEFT: {
            if ((focusAreaID_ == TITLE_NODE_INDEX && focusAreaChildID_ == TITLE_TEXT_NODE_INDEX + 1) ||
                (focusAreaID_ == OPTIONS_NODE_INDEX && focusAreaChildID_ == OPTIONS_DIVIDER_NODE_INDEX + 1)) {
                focusAreaChildID_--;
            }
            focusAreaChildID_--;
            if (focusAreaChildID_ < 0) {
                focusAreaChildID_ = 0;
            }
            PaintFocusState();
            ChangeEntryState();
            return true;
        }
        case KeyCode::KEY_DPAD_RIGHT: {
            if ((focusAreaID_ == TITLE_NODE_INDEX && focusAreaChildID_ == TITLE_TEXT_NODE_INDEX - 1) ||
                (focusAreaID_ == OPTIONS_NODE_INDEX && focusAreaChildID_ == OPTIONS_DIVIDER_NODE_INDEX - 1)) {
                focusAreaChildID_++;
            }
            focusAreaChildID_++;
            auto childSize = static_cast<int32_t>(host->GetChildAtIndex(focusAreaID_)->GetChildren().size());
            if (focusAreaChildID_ > childSize - 1) {
                focusAreaChildID_ = childSize - 1;
            }
            PaintFocusState();
            ChangeEntryState();
            return true;
        }
        case KeyCode::KEY_MOVE_HOME: {
            focusAreaChildID_ = 0;
            PaintFocusState();
            ChangeEntryState();
            return true;
        }
        case KeyCode::KEY_MOVE_END: {
            focusAreaChildID_ = static_cast<int32_t>(host->GetChildAtIndex(focusAreaID_)->GetChildren().size()) - 1;
            PaintFocusState();
            ChangeEntryState();
            return true;
        }
        case KeyCode::KEY_SPACE: {
            return ActClick(focusAreaID_, focusAreaChildID_);
        }
        case KeyCode::KEY_NUMPAD_ENTER:
        case KeyCode::KEY_ENTER: {
            if (focusAreaID_ == OPTIONS_NODE_INDEX) {
                return ActClick(focusAreaID_, focusAreaChildID_);
            }
            return false;
        }
        default:
            break;
    }
    return false;
}

bool CalendarDialogPattern::HandleCalendarNodeKeyEvent(const KeyEvent& event)
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_RETURN(swiperPattern, false);
    swiperPattern->GetSwiperController()->FinishAnimation();
    auto calendarPattern = GetCalendarPattern();
    CHECK_NULL_RETURN(calendarPattern, false);
    ObtainedMonth currentMonthData = calendarPattern->GetCurrentMonthData();

    int32_t focusedDayIndex = GetIndexByFocusedDay();
    switch (event.code) {
        case KeyCode::KEY_DPAD_LEFT: {
            focusedDayIndex--;
            if (IsIndexInCurrentMonth(focusedDayIndex, currentMonthData)) {
                focusedDay_ = currentMonthData.days[focusedDayIndex];
                PaintCurrentMonthFocusState();
            } else {
                PaintNonCurrentMonthFocusState(focusedDayIndex);
            }
            return true;
        }
        case KeyCode::KEY_DPAD_RIGHT: {
            focusedDayIndex++;
            if (IsIndexInCurrentMonth(focusedDayIndex, currentMonthData)) {
                focusedDay_ = currentMonthData.days[focusedDayIndex];
                PaintCurrentMonthFocusState();
            } else {
                PaintNonCurrentMonthFocusState(focusedDayIndex);
            }
            return true;
        }
        case KeyCode::KEY_DPAD_UP: {
            focusedDayIndex -= WEEK_DAYS;
            if (IsIndexInCurrentMonth(focusedDayIndex, currentMonthData)) {
                focusedDay_ = currentMonthData.days[focusedDayIndex];
                PaintCurrentMonthFocusState();
                return true;
            }
            break;
        }
        case KeyCode::KEY_DPAD_DOWN: {
            focusedDayIndex += WEEK_DAYS;
            if (IsIndexInCurrentMonth(focusedDayIndex, currentMonthData)) {
                focusedDay_ = currentMonthData.days[focusedDayIndex];
                PaintCurrentMonthFocusState();
                return true;
            }
            break;
        }
        case KeyCode::KEY_MOVE_HOME: {
            auto it = std::find_if(currentMonthData.days.begin(), currentMonthData.days.end(),
                [currentMonthData](CalendarDay day) {
                    return day.month.year == currentMonthData.year && day.month.month == currentMonthData.month;
                });
            if (it != currentMonthData.days.end()) {
                focusedDay_ = currentMonthData.days[it->index];
                PaintCurrentMonthFocusState();
                return true;
            }
            break;
        }
        case KeyCode::KEY_MOVE_END: {
            auto it = std::find_if(currentMonthData.days.rbegin(), currentMonthData.days.rend(),
                [currentMonthData](CalendarDay day) {
                    return day.month.year == currentMonthData.year && day.month.month == currentMonthData.month;
                });
            if (it != currentMonthData.days.rend()) {
                focusedDay_ = currentMonthData.days[it->index];
                PaintCurrentMonthFocusState();
                return true;
            }
            break;
        }
        case KeyCode::KEY_SPACE:
        case KeyCode::KEY_NUMPAD_ENTER:
        case KeyCode::KEY_ENTER: {
            PickerDate selectedDay(focusedDay_.month.year, focusedDay_.month.month, focusedDay_.day);
            calendarPattern->SetSelectedDay(selectedDay);
            auto calendarFrameNode = GetCalendarFrameNode();
            CHECK_NULL_RETURN(calendarFrameNode, false);
            calendarFrameNode->MarkModifyDone();
            FireChangeByKeyEvent(selectedDay);
            return true;
        }
        default:
            break;
    }
    return false;
}

bool CalendarDialogPattern::IsIndexInCurrentMonth(int32_t focusedDayIndex, const ObtainedMonth& currentMonthData)
{
    return focusedDayIndex >= 0 && focusedDayIndex < static_cast<int32_t>(currentMonthData.days.size()) &&
           currentMonthData.days[focusedDayIndex].month.year == currentMonthData.year &&
           currentMonthData.days[focusedDayIndex].month.month == currentMonthData.month;
}

bool CalendarDialogPattern::HandleTabKeyEvent(const KeyEvent& event)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
        auto childSize = static_cast<int32_t>(host->GetChildren().size());
    if (event.IsShiftWith(KeyCode::KEY_TAB)) {
        focusAreaID_ = (focusAreaID_ + childSize - 1) % childSize;
    } else {
        focusAreaID_ = (focusAreaID_ + 1) % childSize;
    }

    if (focusAreaID_ == CALENDAR_NODE_INDEX) {
        isCalendarFirstFocused_ = true;
        FocusedLastFocusedDay();
    } else {
        ClearCalendarFocusedState();
        focusAreaChildID_ = 0;
        PaintFocusState();
    }
    ChangeEntryState();
    return true;
}

void CalendarDialogPattern::FocusedLastFocusedDay()
{
    auto calendarPattern = GetCalendarPattern();
    CHECK_NULL_VOID(calendarPattern);
    if (focusedDay_.day < 0) {
        PickerDate selectedDay = calendarPattern->GetSelectedDay();
        focusedDay_.month.year = static_cast<int32_t>(selectedDay.GetYear());
        focusedDay_.month.month = static_cast<int32_t>(selectedDay.GetMonth());
        focusedDay_.day = static_cast<int32_t>(selectedDay.GetDay());
    }

    ObtainedMonth currentMonthData = calendarPattern->GetCurrentMonthData();
    if (currentMonthData.year == focusedDay_.month.year && currentMonthData.month == focusedDay_.month.month) {
        PaintCurrentMonthFocusState();
        return;
    }
    ObtainedMonth monthData;
    GetCalendarMonthData(focusedDay_.month.year, focusedDay_.month.month, monthData);
    auto isPrev = currentMonthData.year > focusedDay_.month.year ||
        (currentMonthData.year == focusedDay_.month.year && currentMonthData.month > focusedDay_.month.month);
    auto it = std::find_if(monthData.days.begin(), monthData.days.end(),
        [this](CalendarDay day) {
            return day.day == focusedDay_.day && day.month == focusedDay_.month;
        });
    if (it != monthData.days.end()) {
        focusedDay_ = *it;
        it->isKeyFocused = true;
        UpdateSwiperNode(monthData, isPrev);
    }
}

void CalendarDialogPattern::UpdateSwiperNode(const ObtainedMonth& monthData, bool isPrev)
{
    auto calendarPattern = GetCalendarPattern();
    CHECK_NULL_VOID(calendarPattern);
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_VOID(swiperPattern);
    int32_t currentIndex = swiperPattern->GetCurrentIndex();
    int32_t targetIndex = (currentIndex + SWIPER_CHILDREN_SIZE + (isPrev ? -1 : 1)) % SWIPER_CHILDREN_SIZE;

    auto swiperNode = GetSwiperFrameNode();
    CHECK_NULL_VOID(swiperNode);
    auto monthFrameNode = AceType::DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(targetIndex));
    CHECK_NULL_VOID(monthFrameNode);
    auto monthPattern = monthFrameNode->GetPattern<CalendarMonthPattern>();
    CHECK_NULL_VOID(monthPattern);

    if (isPrev) {
        monthPattern->SetMonthData(monthData, MonthState::PRE_MONTH);
        calendarPattern->SetPreMonthData(monthData);
    } else {
        monthPattern->SetMonthData(monthData, MonthState::NEXT_MONTH);
        calendarPattern->SetNextMonthData(monthData);
    }

    monthFrameNode->MarkModifyDone();
    monthFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    if (isPrev) {
        swiperPattern->ShowPrevious();
    } else {
        swiperPattern->ShowNext();
    }
}

void CalendarDialogPattern::UpdateSwiperNodeFocusedDay(const CalendarDay& focusedDay, bool isPrev)
{
    auto calendarPattern = GetCalendarPattern();
    CHECK_NULL_VOID(calendarPattern);
    ObtainedMonth targetMonthData = isPrev ? calendarPattern->GetPreMonthData() : calendarPattern->GetNextMonthData();
    if (focusedDay.month.year != targetMonthData.year || focusedDay.month.month != targetMonthData.month) {
        return;
    }

    auto it = std::find_if(targetMonthData.days.begin(), targetMonthData.days.end(),
        [focusedDay](CalendarDay day) {
            return day.day == focusedDay.day && day.month == focusedDay.month;
        });
    if (it != targetMonthData.days.end()) {
        focusedDay_ = *it;
        it->isKeyFocused = true;
        auto swiperPattern = GetSwiperPattern();
        CHECK_NULL_VOID(swiperPattern);
        if (isPrev) {
            calendarPattern->SetPreMonthData(targetMonthData);
            swiperPattern->ShowPrevious();
        } else {
            calendarPattern->SetNextMonthData(targetMonthData);
            swiperPattern->ShowNext();
        }
    }
}

bool CalendarDialogPattern::ActClick(int32_t focusAreaID, int32_t focusAreaChildID)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto focusArea = host->GetChildAtIndex(focusAreaID);
    CHECK_NULL_RETURN(focusArea, false);
    auto child = focusArea->GetChildAtIndex(focusAreaChildID);
    CHECK_NULL_RETURN(child, false);
    auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
    CHECK_NULL_RETURN(childFrameNode, false);
    auto gestureEventHub = childFrameNode->GetOrCreateGestureEventHub();
    return gestureEventHub->ActClick();
}

void CalendarDialogPattern::PaintCurrentMonthFocusState()
{
    auto calendarFrameNode = GetCalendarFrameNode();
    CHECK_NULL_VOID(calendarFrameNode);
    auto calendarPattern = calendarFrameNode->GetPattern<CalendarPattern>();
    CHECK_NULL_VOID(calendarPattern);
    ObtainedMonth currentMonthData = calendarPattern->GetCurrentMonthData();
    for (auto& day : currentMonthData.days) {
        if (currentMonthData.year == focusedDay_.month.year && currentMonthData.month == focusedDay_.month.month &&
            day.month == focusedDay_.month && day.day == focusedDay_.day) {
            day.isKeyFocused = true;
        } else {
            day.isKeyFocused = false;
        }
    }
    calendarPattern->SetCurrentMonthData(currentMonthData);
    calendarFrameNode->MarkModifyDone();
}

void CalendarDialogPattern::PaintNonCurrentMonthFocusState(int32_t focusedDayIndex)
{
    auto calendarPattern = GetCalendarPattern();
    CHECK_NULL_VOID(calendarPattern);
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_VOID(swiperPattern);

    ObtainedMonth currentMonthData = calendarPattern->GetCurrentMonthData();
    ObtainedMonth preMonthData = calendarPattern->GetPreMonthData();
    ObtainedMonth nextMonthData = calendarPattern->GetNextMonthData();

    for (auto& day : currentMonthData.days) {
        day.isKeyFocused = false;
    }
    calendarPattern->SetCurrentMonthData(currentMonthData);

    if (focusedDayIndex == -1) {
        focusedDay_ = preMonthData.days[preMonthData.days.size() - 1];
        preMonthData.days[preMonthData.days.size() - 1].isKeyFocused = true;
        calendarPattern->SetPreMonthData(preMonthData);
        swiperPattern->ShowPrevious();
        return;
    } else if (focusedDayIndex == static_cast<int32_t>(currentMonthData.days.size())) {
        focusedDay_ = nextMonthData.days[0];
        nextMonthData.days[0].isKeyFocused = true;
        calendarPattern->SetNextMonthData(nextMonthData);
        swiperPattern->ShowNext();
        return;
    }

    if (focusedDayIndex < 0 || focusedDayIndex >= static_cast<int32_t>(currentMonthData.days.size())) {
        return;
    }

    CalendarDay focusedDay = currentMonthData.days[focusedDayIndex];
    if (focusedDay.month.year == preMonthData.year && focusedDay.month.month == preMonthData.month) {
        return UpdateSwiperNodeFocusedDay(focusedDay, true);
    }

    if (focusedDay.month.year == nextMonthData.year && focusedDay.month.month == nextMonthData.month) {
        return UpdateSwiperNodeFocusedDay(focusedDay, false);
    }
}

void CalendarDialogPattern::PaintFocusState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RoundRect focusRect;
    GetInnerFocusPaintRect(focusRect);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->PaintInnerFocusState(focusRect);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CalendarDialogPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    isFocused_ = true;
    if (focusAreaID_ == CALENDAR_NODE_INDEX) {
        paintRect.SetRect(RectF());
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusArea = DynamicCast<FrameNode>(host->GetChildAtIndex(focusAreaID_));
    CHECK_NULL_VOID(focusArea);
    auto focusAreaOffset = focusArea->GetGeometryNode()->GetFrameOffset();
    auto child = DynamicCast<FrameNode>(focusArea->GetChildAtIndex(focusAreaChildID_));
    CHECK_NULL_VOID(child);
    auto childOffset = child->GetGeometryNode()->GetFrameOffset() + focusAreaOffset;
    auto childSize = child->GetGeometryNode()->GetFrameSize();
    paintRect.SetRect(RectF(childOffset, childSize));
    auto renderContext = child->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto radius = renderContext->GetBorderRadius();
    if (radius.has_value()) {
        if (radius->radiusTopLeft.has_value()) {
            paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS,
                static_cast<float>(radius->radiusTopLeft->ConvertToPx()),
                static_cast<float>(radius->radiusTopLeft->ConvertToPx()));
        }
        if (radius->radiusTopRight.has_value()) {
            paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS,
                static_cast<float>(radius->radiusTopRight->ConvertToPx()),
                static_cast<float>(radius->radiusTopRight->ConvertToPx()));
        }
        if (radius->radiusBottomLeft.has_value()) {
            paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS,
                static_cast<float>(radius->radiusBottomLeft->ConvertToPx()),
                static_cast<float>(radius->radiusBottomLeft->ConvertToPx()));
        }
        if (radius->radiusBottomRight.has_value()) {
            paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS,
                static_cast<float>(radius->radiusBottomRight->ConvertToPx()),
                static_cast<float>(radius->radiusBottomRight->ConvertToPx()));
        }
    }
    ChangeEntryState();
}

void CalendarDialogPattern::ClearCalendarFocusedState()
{
    auto calendarFrameNode = GetCalendarFrameNode();
    CHECK_NULL_VOID(calendarFrameNode);
    auto calendarPattern = calendarFrameNode->GetPattern<CalendarPattern>();
    CHECK_NULL_VOID(calendarPattern);
    ObtainedMonth currentMonthData = calendarPattern->GetCurrentMonthData();
    for (auto& day : currentMonthData.days) {
        day.isKeyFocused = false;
    }
    calendarPattern->SetCurrentMonthData(currentMonthData);
    calendarFrameNode->MarkModifyDone();
}

void CalendarDialogPattern::ChangeEntryState()
{
    CHECK_NULL_VOID_NOLOG(entryNode_);
    auto enrtyPattern = entryNode_->GetPattern<CalendarPickerPattern>();
    CHECK_NULL_VOID(enrtyPattern);
    if (focusAreaID_ == TITLE_NODE_INDEX) {
        if (focusAreaChildID_ == TITLE_LAST_YEAR_BUTTON_NODE_INDEX ||
            focusAreaChildID_ == TITLE_NEXT_YEAR_BUTTON_NODE_INDEX) {
            enrtyPattern->SetSelectedType(CalendarPickerSelectedType::YEAR);
        } else if (focusAreaChildID_ == TITLE_LAST_MONTH_BUTTON_NODE_INDEX ||
                   focusAreaChildID_ == TITLE_NEXT_MONTH_BUTTON_NODE_INDEX) {
            enrtyPattern->SetSelectedType(CalendarPickerSelectedType::MONTH);
        }
    } else if (focusAreaID_ == CALENDAR_NODE_INDEX) {
        enrtyPattern->SetSelectedType(CalendarPickerSelectedType::DAY);
    }
}

void CalendarDialogPattern::InitTitleArrowsEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto title = host->GetChildAtIndex(TITLE_NODE_INDEX);
    CHECK_NULL_VOID(title);
    for (const auto& child : title->GetChildren()) {
        CHECK_NULL_VOID(child);
        if (child->GetTag() == V2::TEXT_ETS_TAG) {
            continue;
        }
        int32_t childIndex = title->GetChildIndex(child);
        auto buttonNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(buttonNode);
        auto event = [buttonNode, childIndex, wp = WeakClaim(this)](GestureEvent& /* info */) {
            auto pattern = wp.Upgrade();
            if (pattern) {
                pattern->HandleTitleArrowsClickEvent(buttonNode, childIndex);
            }
        };
        auto gestureHub = buttonNode->GetOrCreateGestureEventHub();
        auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(event));
        CHECK_NULL_VOID(gestureHub);
        gestureHub->AddClickEvent(clickEvent);
    }
}

void CalendarDialogPattern::HandleTitleArrowsClickEvent(const RefPtr<FrameNode>& buttonNode, int32_t nodeIndex)
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_VOID(swiperPattern);
    swiperPattern->GetSwiperController()->FinishAnimation();

    auto calendarPattern = GetCalendarPattern();
    CHECK_NULL_VOID(calendarPattern);
    ObtainedMonth currentObtainedMonth = calendarPattern->GetCurrentMonthData();
    CalendarMonth currentMonth { .year = currentObtainedMonth.year, .month = currentObtainedMonth.month };

    switch (nodeIndex) {
        case TITLE_LAST_YEAR_BUTTON_NODE_INDEX: {
            currentMonth.year = currentMonth.year == MIN_YEAR ? MAX_YEAR : currentMonth.year - 1;
            ObtainedMonth monthData;
            GetCalendarMonthData(currentMonth.year, currentMonth.month, monthData);
            UpdateSwiperNode(monthData, true);
            break;
        }
        case TITLE_LAST_MONTH_BUTTON_NODE_INDEX: {
            swiperPattern->ShowPrevious();
            break;
        }
        case TITLE_NEXT_MONTH_BUTTON_NODE_INDEX: {
            swiperPattern->ShowNext();
            break;
        }
        case TITLE_NEXT_YEAR_BUTTON_NODE_INDEX: {
            currentMonth.year = currentMonth.year == MAX_YEAR ? MIN_YEAR : currentMonth.year + 1;
            ObtainedMonth monthData;
            GetCalendarMonthData(currentMonth.year, currentMonth.month, monthData);
            UpdateSwiperNode(monthData, false);
            break;
        }
        default:
            break;
    }
}

void CalendarDialogPattern::GetCalendarMonthData(int32_t year, int32_t month, ObtainedMonth& calendarMonthData)
{
    calendarMonthData.year = year;
    calendarMonthData.month = month;
    calendarMonthData.firstDayIndex = 0;

    CalendarMonth currentMonth { .year = year, .month = month };

    int32_t currentMonthMaxDay = PickerDate::GetMaxDay(year, month);
    int32_t preMonthMaxDay = PickerDate::GetMaxDay(GetLastMonth(currentMonth).year, GetLastMonth(currentMonth).month);
    int32_t preMonthDaysCount = (Date::CalculateWeekDay(year, month, 1) + 1) % WEEK_DAYS;
    int32_t nextMonthDaysCount = 6 - ((Date::CalculateWeekDay(year, month, currentMonthMaxDay) + 1) % WEEK_DAYS);

    int32_t index = 0;
    for (int32_t i = 0; i < preMonthDaysCount; i++, index++) {
        calendarMonthData.days.emplace_back(CalendarDay { .index = index,
            .day = preMonthMaxDay - preMonthDaysCount + index + 1,
            .month = GetLastMonth(currentMonth) });
    }

    for (int32_t i = 0; i < currentMonthMaxDay; i++, index++) {
        calendarMonthData.days.emplace_back(CalendarDay { .index = index, .day = i + 1, .month = currentMonth });
    }

    for (int32_t i = 0; i < nextMonthDaysCount; i++, index++) {
        calendarMonthData.days.emplace_back(
            CalendarDay { .index = index, .day = i + 1, .month = GetNextMonth(currentMonth) });
    }

    auto calendarPattern = GetCalendarPattern();
    CHECK_NULL_VOID_NOLOG(calendarPattern);
    PickerDate selectedDay = calendarPattern->GetSelectedDay();
    for (size_t i = 0; i < calendarMonthData.days.size(); i++) {
        calendarMonthData.days[i].isKeyFocused = (focusedDay_.month.year == calendarMonthData.year) &&
                                                 (focusedDay_.month.month == calendarMonthData.month) &&
                                                 (focusedDay_.month == calendarMonthData.days[i].month) &&
                                                 (focusedDay_.day == calendarMonthData.days[i].day);
        calendarMonthData.days[i].isSelected =
            (selectedDay.GetYear() == static_cast<uint32_t>(calendarMonthData.year)) &&
            (selectedDay.GetMonth() == static_cast<uint32_t>(calendarMonthData.month)) &&
            (selectedDay.GetYear() == static_cast<uint32_t>(calendarMonthData.days[i].month.year)) &&
            (selectedDay.GetMonth() == static_cast<uint32_t>(calendarMonthData.days[i].month.month)) &&
            (selectedDay.GetDay() == static_cast<uint32_t>(calendarMonthData.days[i].day));
    }
}

void CalendarDialogPattern::AddHotZoneRect()
{
    CHECK_NULL_VOID_NOLOG(entryNode_);
    auto rect = entryNode_->GetPaintRectWithTransform();
    rect.SetOffset(entryNode_->GetPaintRectOffsetToPage());
    DimensionRect hotZoneRegion;
    hotZoneRegion.SetSize(DimensionSize(
        Dimension(rect.Width()), Dimension(rect.Height())));
    hotZoneRegion.SetOffset(DimensionOffset(
        Dimension(rect.Left() - dialogOffset_.GetX()), Dimension(rect.Top() - dialogOffset_.GetY())));

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    DimensionRect hotZoneRegionHost;
    hotZoneRegionHost.SetSize(DimensionSize(
        Dimension(geometryNode->GetFrameRect().Width()), Dimension(geometryNode->GetFrameRect().Height())));

    host->AddHotZoneRect(hotZoneRegion);
    host->AddHotZoneRect(hotZoneRegionHost);
}

void CalendarDialogPattern::FireChangeByKeyEvent(PickerDate& selectedDay)
{
    auto calendarNode = GetCalendarFrameNode();
    CHECK_NULL_VOID(calendarNode);

    auto swiperNode = AceType::DynamicCast<FrameNode>(calendarNode->GetFirstChild());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto monthNode = AceType::DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(swiperPattern->GetCurrentIndex()));
    CHECK_NULL_VOID(monthNode);
    auto eventHub = monthNode->GetEventHub<CalendarEventHub>();
    eventHub->UpdateSelectedChangeEvent(selectedDay.ToString(true));
}

CalendarMonth CalendarDialogPattern::GetNextMonth(const CalendarMonth& calendarMonth)
{
    CalendarMonth nextMonth = calendarMonth;
    if (calendarMonth.month + 1 > MAX_MONTH) {
        nextMonth.month = 1;
        nextMonth.year = nextMonth.year == MAX_YEAR ? MIN_YEAR : nextMonth.year + 1;
    } else {
        ++nextMonth.month;
    }
    return nextMonth;
}

CalendarMonth CalendarDialogPattern::GetLastMonth(const CalendarMonth& calendarMonth)
{
    CalendarMonth lastMonth = calendarMonth;
    if (calendarMonth.month - 1 <= 0) {
        lastMonth.month = MAX_MONTH;
        lastMonth.year = lastMonth.year == MIN_YEAR ? MAX_YEAR : lastMonth.year - 1;
    } else {
        --lastMonth.month;
    }
    return lastMonth;
}

int32_t CalendarDialogPattern::GetIndexByFocusedDay()
{
    ObtainedMonth monthData;
    GetCalendarMonthData(focusedDay_.month.year, focusedDay_.month.month, monthData);
    auto it = std::find_if(monthData.days.begin(), monthData.days.end(),
        [this](CalendarDay day) {
            return day.day == focusedDay_.day && day.month == focusedDay_.month;
        });
    if (it != monthData.days.end()) {
        return it->index;
    }
    return -1;
}

void CalendarDialogPattern::HandleEntryLayoutChange()
{
    CHECK_NULL_VOID_NOLOG(entryNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto wrapperNode = host->GetParent();
    CHECK_NULL_VOID(wrapperNode);
    auto dialogNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetParent());
    CHECK_NULL_VOID(dialogNode);
    auto dialogLayoutProp = dialogNode->GetLayoutProperty<DialogLayoutProperty>();
    CHECK_NULL_VOID(dialogLayoutProp);
    auto pattern = entryNode_->GetPattern<CalendarPickerPattern>();
    CHECK_NULL_VOID(pattern);
    dialogLayoutProp->UpdateDialogOffset(DimensionOffset(pattern->CalculateDialogOffset()));
    dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    isFirstAddhotZoneRect_ = false;
}

void CalendarDialogPattern::HandleEntryChange(const std::string& info)
{
    auto calendarNode = GetCalendarFrameNode();
    CHECK_NULL_VOID(calendarNode);
    auto calendarPattern = calendarNode->GetPattern<CalendarPattern>();
    CHECK_NULL_VOID(calendarPattern);

    auto calendarJson = JsonUtil::ParseJsonString(calendarPattern->GetSelectDate());
    auto entryJson = JsonUtil::ParseJsonString(info);
    auto entryYear = entryJson->GetUInt("year");
    auto entryMonth = entryJson->GetUInt("month");
    auto entryDay = entryJson->GetUInt("day");

    PickerDate selectedDay = PickerDate(entryYear, entryMonth, entryDay);
    if (entryYear != calendarJson->GetUInt("year") || entryMonth != calendarJson->GetUInt("month")) {
        CalendarData calendarData;
        CalendarMonth calendarMonth { .year = entryYear, .month = entryMonth };

        GetCalendarMonthData(entryYear, entryMonth, calendarData.currentData);
        calendarPattern->SetCurrentMonthData(calendarData.currentData);
        GetCalendarMonthData(
            GetLastMonth(calendarMonth).year, GetLastMonth(calendarMonth).month, calendarData.preData);
        calendarPattern->SetPreMonthData(calendarData.preData);
        GetCalendarMonthData(
            GetNextMonth(calendarMonth).year, GetNextMonth(calendarMonth).month, calendarData.nextData);
        calendarPattern->SetNextMonthData(calendarData.nextData);
    }

    calendarPattern->SetSelectedDay(selectedDay);
    calendarNode->MarkModifyDone();
}

RefPtr<FrameNode> CalendarDialogPattern::GetCalendarFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN_NOLOG(host, nullptr);
    auto calendarNode = host->GetChildAtIndex(CALENDAR_NODE_INDEX);
    return AceType::DynamicCast<FrameNode>(calendarNode);
}

RefPtr<CalendarPattern> CalendarDialogPattern::GetCalendarPattern()
{
    auto calendarFrameNode = GetCalendarFrameNode();
    CHECK_NULL_RETURN_NOLOG(calendarFrameNode, nullptr);
    return calendarFrameNode->GetPattern<CalendarPattern>();
}

RefPtr<FrameNode> CalendarDialogPattern::GetSwiperFrameNode()
{
    auto calendarFrameNode = GetCalendarFrameNode();
    CHECK_NULL_RETURN_NOLOG(calendarFrameNode, nullptr);
    if (calendarFrameNode->GetChildren().empty()) {
        return nullptr;
    }
    auto swiperNode = calendarFrameNode->GetChildren().front();
    CHECK_NULL_RETURN_NOLOG(swiperNode, nullptr);
    return AceType::DynamicCast<FrameNode>(swiperNode);
}

RefPtr<SwiperPattern> CalendarDialogPattern::GetSwiperPattern()
{
    auto swiperFrameNode = GetSwiperFrameNode();
    CHECK_NULL_RETURN_NOLOG(swiperFrameNode, nullptr);
    return swiperFrameNode->GetPattern<SwiperPattern>();
}
} // namespace OHOS::Ace::NG
