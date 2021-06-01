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

#include "core/components/calendar/calendar_component.h"

#include "base/i18n/localization.h"
#include "core/components/box/box_component.h"
#include "core/components/button/button_component.h"
#include "core/components/calendar/calendar_element.h"
#include "core/components/calendar/render_calendar.h"
#include "core/components/display/display_component.h"
#include "core/components/flex/flex_item_component.h"
#include "core/components/image/image_component.h"
#include "core/components/text/text_component.h"
#include "core/event/ace_event_helper.h"
#include "core/event/back_end_event_manager.h"

namespace OHOS::Ace {
namespace {

constexpr double MAX_OPACITY = 255.0;
constexpr int32_t MAX_MONTH_CACHE_NUM = 3;
constexpr int32_t DISTANCE_FORM_LAST = MAX_MONTH_CACHE_NUM - 1;
constexpr int32_t TODAY_MONTH_INDEX_OF_CONTAINER = 1;
constexpr int32_t NEXT_TO_TODAY_MONTH_INDEX_OF_CONTAINER = 2;
constexpr int32_t LAST_TO_TODAY_MONTH_INDEX_OF_CONTAINER = 0;
constexpr Dimension UPPER_AND_LOWER_MARGIN = 16.0_vp;
constexpr Dimension LEFT_AND_RIGHT_MARGIN = 24.0_vp;

} // namespace

CalendarController::CalendarController(
    const CalendarDataAdapterAction& dataAdapterAction, const WeakPtr<PipelineContext>& pipelineContext)
    : dataAdapter_(AceType::MakeRefPtr<CalendarDataAdapter>(dataAdapterAction, pipelineContext)) {}

void CalendarController::Initialize()
{
    currentCalendarMonth_ = dataAdapter_->GetToday().month;
    dataAdapter_->SetCurrentMonth(currentCalendarMonth_);
    dataAdapter_->SetSelectedChanged(dataAdapter_->GetToday().day, TODAY_MONTH_INDEX_OF_CONTAINER);
    dataAdapter_->RequestData({ currentCalendarMonth_, TODAY_MONTH_INDEX_OF_CONTAINER });
    dataAdapter_->AddPendingRequest(
        CalendarMonth::GetNextMonth(currentCalendarMonth_), NEXT_TO_TODAY_MONTH_INDEX_OF_CONTAINER);
    dataAdapter_->AddPendingRequest(
        CalendarMonth::GetLastMonth(currentCalendarMonth_), LAST_TO_TODAY_MONTH_INDEX_OF_CONTAINER);
}

void CalendarController::GoToPrevMonth(int32_t selected)
{
    GoToMonth(SwipeDirection::PREV, selected);
}

void CalendarController::GoToNextMonth(int32_t selected)
{
    GoToMonth(SwipeDirection::NEXT, selected);
}

void CalendarController::GoToMonth(SwipeDirection direction, int32_t selected)
{
    int32_t index;
    CalendarMonth calendarMonth;
    CalendarMonth cacheMonth;
    bool reverse = false;
    if (direction == SwipeDirection::PREV) {
        index = (currentMonthIndex_ + 1) % MAX_MONTH_CACHE_NUM;
        if (--currentMonthIndex_ < 0) {
            reverse = true;
            currentMonthIndex_ = MAX_MONTH_CACHE_NUM - 1;
        }
        calendarMonth = CalendarMonth::GetLastMonth(currentCalendarMonth_);
        cacheMonth = CalendarMonth::GetLastMonth(calendarMonth);
    } else if (direction == SwipeDirection::NEXT) {
        index = (currentMonthIndex_ + DISTANCE_FORM_LAST) % MAX_MONTH_CACHE_NUM;
        if (++currentMonthIndex_ >= MAX_MONTH_CACHE_NUM) {
            reverse = true;
            currentMonthIndex_ = 0;
        }
        calendarMonth = CalendarMonth::GetNextMonth(currentCalendarMonth_);
        cacheMonth = CalendarMonth::GetNextMonth(calendarMonth);
    } else {
        return;
    }

    swiperReverseCache_.push({ currentMonthIndex_, reverse });
    dataAdapter_->SetSelectedChanged(selected, currentMonthIndex_);
    currentCalendarMonth_ = calendarMonth;
    dataAdapter_->SetCurrentMonth(currentCalendarMonth_);
    dataAdapter_->RequestData({ cacheMonth, index });
}

void CalendarController::JumpToMonth(const CalendarMonth& calendarMonth, int32_t selected, SwipeDirection direction)
{
    if (direction == SwipeDirection::PREV) {
        // target -- last(replaced by target) -- current -- next
        int32_t destIndex = (currentMonthIndex_ + DISTANCE_FORM_LAST) % MAX_MONTH_CACHE_NUM;
        dataAdapter_->RequestData({ calendarMonth, destIndex });
        CalculateNextIndex(currentMonthIndex_ - 1);
        dataAdapter_->SetSelectedChanged(selected, currentMonthIndex_);

        int32_t lastIndex = (destIndex + DISTANCE_FORM_LAST) % MAX_MONTH_CACHE_NUM;
        dataAdapter_->AddPendingRequest(CalendarMonth::GetLastMonth(calendarMonth), lastIndex);

        // cache the next month date after the animation ends, otherwise the content of the animation page will be
        // changed
        int32_t nextIndex = (destIndex + 1) % MAX_MONTH_CACHE_NUM;
        dataAdapter_->AddPendingRequest(CalendarMonth::GetNextMonth(calendarMonth), nextIndex);
    } else if (direction == SwipeDirection::NEXT) {
        // last -- current -- next(replaced by target) -- target
        int32_t destIndex = (currentMonthIndex_ + 1) % MAX_MONTH_CACHE_NUM;
        dataAdapter_->RequestData({ calendarMonth, destIndex });
        CalculateNextIndex(currentMonthIndex_ + 1);
        dataAdapter_->SetSelectedChanged(selected, currentMonthIndex_);

        int32_t nextIndex = (destIndex + 1) % MAX_MONTH_CACHE_NUM;
        dataAdapter_->AddPendingRequest(CalendarMonth::GetNextMonth(calendarMonth), nextIndex);

        // cache the previous month date after the animation ends, otherwise the content of the animation page will be
        // changed
        int32_t lastIndex = (destIndex + DISTANCE_FORM_LAST) % MAX_MONTH_CACHE_NUM;
        dataAdapter_->AddPendingRequest(CalendarMonth::GetLastMonth(calendarMonth), lastIndex);
    } else {
        // ignore
    }
}

void CalendarController::GoTo(int32_t year, int32_t month, int32_t day)
{
    if (!dataAdapter_) {
        LOGE("calendar data adapter is nullptr");
        return;
    }
    if (!swiperController_) {
        LOGE("swiper controller is nullptr");
        return;
    }

    LOGD("go to: year=%{private}d, month=%{private}d, day=%{private}d", year, month, day);
    CalendarMonth calendarMonth { year, month };
    auto nextMonth = CalendarMonth::GetNextMonth(currentCalendarMonth_);
    auto lastMonth = CalendarMonth::GetLastMonth(currentCalendarMonth_);
    if (calendarMonth == lastMonth) {
        GoToPrevMonth(day);
    } else if (calendarMonth == nextMonth) {
        GoToNextMonth(day);
    } else if (calendarMonth < lastMonth) {
        currentCalendarMonth_ = calendarMonth;
        dataAdapter_->SetCurrentMonth(currentCalendarMonth_);
        JumpToMonth(calendarMonth, day, SwipeDirection::PREV);
    } else if (calendarMonth > nextMonth) {
        currentCalendarMonth_ = calendarMonth;
        dataAdapter_->SetCurrentMonth(currentCalendarMonth_);
        JumpToMonth(calendarMonth, day, SwipeDirection::NEXT);
    } else {
        dataAdapter_->SetSelectedChanged(day, currentMonthIndex_);
        dataAdapter_->NotifySelectedChanged();
    }
}

void CalendarController::RequestMonthData(int32_t index)
{
    auto tmpPreIndex = (currentMonthIndex_ + 1) % MAX_MONTH_CACHE_NUM;
    auto tmpNextIndex = (currentMonthIndex_ + DISTANCE_FORM_LAST) % MAX_MONTH_CACHE_NUM;
    auto nextIndex = currentMonthIndex_;
    auto preIndex = currentMonthIndex_;
    CalendarMonth calendarMonth;
    CalendarMonth cacheMonth;
    static const int32_t selectedDay = 1;
    if (++nextIndex >= MAX_MONTH_CACHE_NUM) {
        nextIndex = 0;
    }
    if (--preIndex < 0) {
        preIndex = MAX_MONTH_CACHE_NUM - 1;
    }
    if (nextIndex == index) {
        currentMonthIndex_ = nextIndex;
        calendarMonth = CalendarMonth::GetNextMonth(currentCalendarMonth_);
        cacheMonth = CalendarMonth::GetNextMonth(calendarMonth);

        dataAdapter_->SetSelectedChanged(selectedDay, currentMonthIndex_);
        dataAdapter_->RequestData({ cacheMonth, tmpNextIndex });
    } else if (preIndex == index) {
        currentMonthIndex_ = preIndex;
        calendarMonth = CalendarMonth::GetLastMonth(currentCalendarMonth_);
        cacheMonth = CalendarMonth::GetLastMonth(calendarMonth);

        dataAdapter_->SetSelectedChanged(selectedDay, currentMonthIndex_);
        dataAdapter_->RequestData({ cacheMonth, tmpPreIndex });
    } else {
        return;
    }
    currentCalendarMonth_ = calendarMonth;
    dataAdapter_->SetCurrentMonth(currentCalendarMonth_);
}

void CalendarController::CalculateNextIndex(int32_t index)
{
    bool reverse = false;
    if (index >= MAX_MONTH_CACHE_NUM) {
        reverse = true;
        index = 0;
    } else if (index < 0) {
        reverse = true;
        index = MAX_MONTH_CACHE_NUM - 1;
    }
    currentMonthIndex_ = index;
    swiperReverseCache_.push({ currentMonthIndex_, reverse });
}

void CalendarController::UpdateTheme()
{
    if (!renderText_) {
        return;
    }
    auto theme = renderText_->GetTheme<CalendarTheme>();
    if (!leftImage_ || !leftImageComponent_ || !rightImageComponent_ || !rightImage_ || !theme) {
        return;
    }
    TextStyle style;
    style.SetFontSize(theme->GetCardCalendarTheme().titleFontSize);
    style.SetTextColor(theme->GetCardCalendarTheme().titleTextColor);
    style.SetFontWeight(FontWeight::W500);
    renderText_->SetTextStyle(style);
    renderText_->MarkNeedMeasure();
    renderText_->MarkNeedLayout();
    leftImageComponent_->SetColor(theme->GetCardCalendarTheme().titleTextColor);
    leftImage_->Update(leftImageComponent_);
    leftImage_->MarkNeedLayout();
    rightImageComponent_->SetColor(theme->GetCardCalendarTheme().titleTextColor);
    rightImage_->Update(rightImageComponent_);
    rightImage_->MarkNeedLayout();
}

void CalendarController::UpdateTitle(const CalendarDay& today)
{
    if (!renderText_) {
        return;
    }
    DateTime dateTime;
    dateTime.year = today.month.year;
    dateTime.month = today.month.month;
    auto date = Localization::GetInstance()->FormatDateTime(dateTime, "yyyyMMM");
    renderText_->SetTextData(date);
    renderText_->MarkNeedMeasure();
    renderText_->MarkNeedLayout();
}

CalendarComponent::CalendarComponent(const ComposeId& id, const std::string& name) : ComposedComponent(id, name) {}

RefPtr<Component> CalendarComponent::Build(
    const WeakPtr<PipelineContext>& pipelineContext, const RefPtr<CalendarController>& calendarController)
{
    auto context = pipelineContext.Upgrade();
    if (!context || !calendarController) {
        return nullptr;
    }
    calendarController_ = calendarController;
    auto themeManager = context->GetThemeManager();
    if (!themeManager) {
        return nullptr;
    }
    auto calendarTheme = themeManager->GetTheme<CalendarTheme>();
    if (!calendarTheme) {
        return nullptr;
    }

    auto direction = GetTextDirection();

    std::list<RefPtr<Component>> monthChildren;
    for (int32_t index = 0; index < MAX_MONTH_CACHE_NUM; index++) {
        auto calendarMonth = AceType::MakeRefPtr<CalendarMonthComponent>(index, calendarController_);
        auto display = AceType::MakeRefPtr<DisplayComponent>(calendarMonth);
        calendarMonth->SetSelectedChangeEvent(selectedChangeEvent_);
        calendarMonth->SetCalendarTheme(calendarTheme);
        calendarMonth->SetCardCalendar(cardCalendar_);
        calendarMonth->SetTextDirection(direction);
        display->SetOpacity(MAX_OPACITY);
        monthChildren.emplace_back(display);
    }
    if (!swiperContainer_) {
        swiperContainer_ = AceType::MakeRefPtr<SwiperComponent>(monthChildren);
    }
    swiperContainer_->SetLoop(false);
    swiperContainer_->SetAxis(axis_);
    swiperContainer_->SetIndex(TODAY_MONTH_INDEX_OF_CONTAINER);
    swiperContainer_->SetTextDirection(direction);
    swiperContainer_->SetSlideContinue(true);
    calendarController_->SetSwiperController(swiperContainer_->GetSwiperController());
    swiperContainer_->SetMoveCallback([calendarComponent = AceType::WeakClaim(this)](int32_t index) {
        auto calendar = calendarComponent.Upgrade();
        if (calendar && calendar->calendarController_) {
            calendar->calendarController_->RequestMonthData(index);
        }
    });
    if (!cardCalendar_) {
        return swiperContainer_;
    } else {
        swiperContainer_->DisableSwipe(true);
        RefPtr<ColumnComponent> colComponent;
        BuildCardCalendarTitle(calendarTheme, colComponent);
        return colComponent;
    }
}

RefPtr<Element> CalendarComponent::CreateElement()
{
    return AceType::MakeRefPtr<CalendarElement>(GetId());
}

void CalendarComponent::GoTo(int32_t year, int32_t month, int32_t day)
{
    if (day < 0) {
        calendarController_->GoTo(year, month, 1);
    } else {
        calendarController_->SetNeedFocus(true);
        calendarController_->GoTo(year, month, day);
    }
}

void CalendarComponent::BuildCardCalendarTitle(const RefPtr<CalendarTheme>& theme, RefPtr<ColumnComponent>& col)
{
    auto preButton = InitCardButton(theme, true);
    auto nextButton = InitCardButton(theme, false);
    DateTime dateTime;
    dateTime.year = calendarController_->GetCurrentMonth().year;
    dateTime.month = calendarController_->GetCurrentMonth().month;
    auto date = Localization::GetInstance()->FormatDateTime(dateTime, "yyyyMMM");
    auto text = AceType::MakeRefPtr<TextComponent>(date);
    TextStyle style;
    auto calendarTheme = theme->GetCardCalendarTheme();
    style.SetFontSize(calendarTheme.titleFontSize);
    style.SetTextColor(calendarTheme.titleTextColor);
    style.SetFontWeight(FontWeight::W500);
    text->SetTextStyle(style);

    auto box = AceType::MakeRefPtr<BoxComponent>();
    Edge edge(LEFT_AND_RIGHT_MARGIN, UPPER_AND_LOWER_MARGIN, LEFT_AND_RIGHT_MARGIN, UPPER_AND_LOWER_MARGIN);
    box->SetMargin(edge);
    box->SetChild(text);

    std::list<RefPtr<Component>> rowChildren;
    rowChildren.emplace_back(preButton);
    rowChildren.emplace_back(box);
    rowChildren.emplace_back(nextButton);
    auto rowComponent = AceType::MakeRefPtr<RowComponent>(FlexAlign::CENTER, FlexAlign::CENTER, rowChildren);
    std::list<RefPtr<Component>> colChildren;
    colChildren.emplace_back(rowComponent);
    colChildren.emplace_back(swiperContainer_);
    col = AceType::MakeRefPtr<ColumnComponent>(FlexAlign::FLEX_START, FlexAlign::CENTER, colChildren);
}

const EventMarker& CalendarComponent::GetSelectedChangeEvent() const
{
    return selectedChangeEvent_;
}

const EventMarker& CalendarComponent::GetRequestDataEvent() const
{
    return requestDataEvent_;
}

CalendarMonthComponent::CalendarMonthComponent(
    int32_t indexOfContainer, const RefPtr<CalendarController>& calendarController)
    : indexOfContainer_(indexOfContainer), calendarController_(calendarController) {}

RefPtr<RenderNode> CalendarMonthComponent::CreateRenderNode()
{
    return RenderCalendar::Create();
}

RefPtr<Element> CalendarMonthComponent::CreateElement()
{
    return AceType::MakeRefPtr<CalendarMonthElement>();
}

void CalendarComponent::SetCalendarData(const std::string& value)
{
    if (calendarController_) {
        calendarData_ = value;
        auto dataAdapter = calendarController_->GetDataAdapter();
        if (dataAdapter) {
            dataAdapter->SetOffDays(offDays_);
            dataAdapter->ParseCardCalendarData(calendarData_);
        }
        calendarController_->UpdateTheme();
    } else {
        calendarData_ = value;
    }
}

RefPtr<ButtonComponent> CalendarComponent::InitCardButton(const RefPtr<CalendarTheme>& theme, bool isPreArrow)
{
    auto Arrow = isPreArrow ? AceType::MakeRefPtr<ImageComponent>(InternalResource::ResourceId::LEFT_ARROW_SVG)
                            : AceType::MakeRefPtr<ImageComponent>(InternalResource::ResourceId::RIGHT_ARROW_SVG);
    isPreArrow ? calendarController_->SetLeftRowImage(Arrow) : calendarController_->SetRightRowImage(Arrow);
    auto calendarTheme = theme->GetCardCalendarTheme();
    Arrow->SetWidth(calendarTheme.arrowWidth);
    Arrow->SetHeight(calendarTheme.arrowHeight);
    std::list<RefPtr<Component>> children;
    children.emplace_back(Arrow);
    auto button = AceType::MakeRefPtr<ButtonComponent>(children);
    button->SetBackgroundColor(Color::TRANSPARENT);
    button->SetClickedColor(Color::TRANSPARENT);
    button->SetWidth(calendarTheme.buttonWidth);
    button->SetHeight(calendarTheme.buttonHeight);
    isPreArrow ? preClickId_ = BackEndEventManager<void()>::GetInstance().GetAvailableMarker()
               : nextClickId_ = BackEndEventManager<void()>::GetInstance().GetAvailableMarker();
    isPreArrow ? button->SetClickedEventId(preClickId_) : button->SetClickedEventId(nextClickId_);

    return button;
}

} // namespace OHOS::Ace
