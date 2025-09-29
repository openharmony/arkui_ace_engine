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

#include "core/components_ng/pattern/calendar/calendar_month_pattern.h"

#include "base/geometry/offset.h"
#include "base/i18n/localization.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/calendar/calendar_paint_method.h"
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_view.h"
#include "core/components/slider/slider_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CALENDAR_WEEK_DAYS = 7;
constexpr int32_t DAILY_FOUR_ROWSPACE = 4;
constexpr int32_t DAILY_FIVE_ROWSPACE = 5;
constexpr int32_t CALENDAR_DISTANCE_ADJUST_FOCUSED_SIZE = 2;
constexpr Dimension CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT = 4.0_vp;
constexpr int32_t MONDAY_INDEX = 1;
constexpr int32_t TUESDAY_INDEX = 2;
constexpr int32_t WEDNESDAY_INDEX = 3;
constexpr int32_t THURSDAY_INDEX = 4;
constexpr int32_t FRIDAY_INDEX = 5;
constexpr int32_t SATURDAY_INDEX = 6;
constexpr int32_t WEEK_ROW_INDEX = 1;
} // namespace

RefPtr<NodePaintMethod> CalendarMonthPattern::CreateNodePaintMethod()
{
    if (AceApplicationInfo::GetInstance().IsAccessibilityEnabled()) {
        InitCurrentVirtualNode();
    }
    CalendarPaintParams params;
    params.startDate = startDate_;
    params.endDate = endDate_;
    params.markToday = markToday_;
    params.disabledDateRange = disabledDateRange_;
    return MakeRefPtr<CalendarPaintMethod>(obtainedMonth_, calendarDay_, params, isCalendarDialog_);
}

void CalendarMonthPattern::SetCalendarDay(const CalendarDay& calendarDay)
{
    calendarDay_ = calendarDay;
    if (monthState_ == MonthState::CUR_MONTH && !obtainedMonth_.days.empty()) {
        for (auto& day : obtainedMonth_.days) {
            if (day.month.year == calendarDay.month.year && day.month.month == calendarDay.month.month &&
                day.day == calendarDay.day) {
                day.focused = true;
            }
        }
    }
}

void CalendarMonthPattern::InitFoldState()
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    container->InitIsFoldable();
    if (container->IsFoldable()) {
        currentFoldStatus_ = container->GetCurrentFoldStatus();
    }
}

void CalendarMonthPattern::FireIsFoldStatusChanged()
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if (!container->IsFoldable()) {
        return;
    }
    auto foldStatus = container->GetCurrentFoldStatus();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<CalendarPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto colSpace = paintProperty->GetColSpaceValue({}).ConvertToPx();
    if (foldStatus != currentFoldStatus_ && colSpace_ != colSpace && monthState_ == MonthState::CUR_MONTH) {
        currentFoldStatus_ = foldStatus;
        InitCalendarVirtualNode();
        SetFocusNode(focusedCalendarDay_.index, true);
    }
}

void CalendarMonthPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
    InitFoldState();
}

bool CalendarMonthPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (IsCalendarDialog()) {
        SetColRowSpace();
    }

    return !(config.skipMeasure || dirty->SkipMeasureContent());
}

CalendarMonthPattern::~CalendarMonthPattern()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->DeregisterAccessibilitySAObserverCallback(host->GetAccessibilityId());
}

Dimension CalendarMonthPattern::GetDaySize(const RefPtr<CalendarTheme>& theme)
{
    auto pipeline = GetHost()->GetContext();
    CHECK_NULL_RETURN(pipeline, theme->GetCalendarPickerDayWidthOrHeight());
    auto fontSizeScale = pipeline->GetFontScale();
#ifndef ARKUI_WEARABLE
    if (fontSizeScale < theme->GetCalendarPickerLargeScale() || CalendarDialogView::CheckOrientationChange()) {
#else
    if (fontSizeScale < theme->GetCalendarPickerLargeScale()) {
#endif
        return theme->GetCalendarPickerDayWidthOrHeight();
    } else {
        return theme->GetCalendarPickerDayLargeWidthOrHeight();
    }
}

bool CalendarMonthPattern::IsLargeSize(const RefPtr<CalendarTheme>& theme)
{
    auto pipeline = GetHost()->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto fontSizeScale = pipeline->GetFontScale();
#ifndef ARKUI_WEARABLE
    if ((fontSizeScale < theme->GetCalendarPickerLargeScale() || CalendarDialogView::CheckOrientationChange())
        && theme->GetCalendarPickerDayLargeWidthOrHeight() > theme->GetCalendarPickerDayWidthOrHeight()) {
#else
    if (fontSizeScale < theme->GetCalendarPickerLargeScale()
        && theme->GetCalendarPickerDayLargeWidthOrHeight() > theme->GetCalendarPickerDayWidthOrHeight()) {
#endif
        return false;
    } else {
        return true;
    }
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

    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    auto selfWidth = constraint.selfIdealSize.Width();
    if (!selfWidth.has_value()) {
        return;
    }
    auto width = selfWidth.value() - CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT.ConvertToPx() * 2;
    auto paintProperty = GetPaintProperty<CalendarPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto gregorianDayHeight = paintProperty->GetGregorianCalendarHeightValue({}).ConvertToPx() <= 0
                    ? theme->GetCalendarTheme().gregorianCalendarHeight.ConvertToPx()
                    : paintProperty->GetGregorianCalendarHeightValue({}).ConvertToPx();
    if (IsLargeSize(theme)) {
        gregorianDayHeight = GetDaySize(theme).ConvertToPx();
    }
    auto selfHeight = constraint.selfIdealSize.Height();
    if (!selfHeight.has_value()) {
        return;
    }
    auto height = selfHeight.value()
        - CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT.ConvertToPx() + gregorianDayHeight;
    auto calendarDaySize = GetDaySize(theme);
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
    InitAccessibilityHoverEvent();
    InitializeCalendarAccessibility();
}

void CalendarMonthPattern::SetVirtualNodeUserSelected(int32_t index)
{
    if (accessibilityPropertyVec_.size() < 1) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto textDirection = layoutProperty->GetNonAutoLayoutDirection();
    auto remainderWeek = index % CALENDAR_WEEK_DAYS;
    int32_t selectedIndex = (textDirection == TextDirection::RTL ?
        CALENDAR_WEEK_DAYS - remainderWeek * 2 + index - 1 : index);
    std::string selectMessage;
    for (int i = 0; i < static_cast<int32_t>(accessibilityPropertyVec_.size()); i++) {
        if (i == selectedIndex &&
            obtainedMonth_.days[i].month.month == obtainedMonth_.month &&
            obtainedMonth_.days[i].month.year == obtainedMonth_.year) {
            selectMessage += accessibilityPropertyVec_[index]->GetAccessibilityText();
            continue;
        }
        accessibilityPropertyVec_[i]->SetUserSelected(false);
    }
    if (!obtainedMonth_.days.empty()) {
        for (auto& day : obtainedMonth_.days) {
            day.focused = false;
        }
        auto calendarEventHub = GetOrCreateEventHub<CalendarEventHub>();
        CHECK_NULL_VOID(calendarEventHub);
        if (selectedIndex >= 0 && selectedIndex < static_cast<int32_t>(obtainedMonth_.days.size())) {
            obtainedMonth_.days[selectedIndex].focused = true;
            auto json = JsonUtil::Create(true);
            json->Put("day", obtainedMonth_.days[selectedIndex].day);
            json->Put("month", obtainedMonth_.days[selectedIndex].month.month);
            json->Put("year", obtainedMonth_.days[selectedIndex].month.year);
            calendarEventHub->UpdateSelectedChangeEvent(json->ToString());
        }
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    if (!selectMessage.empty()) {
        host->OnAccessibilityEvent(AccessibilityEventType::ANNOUNCE_FOR_ACCESSIBILITY, selectedTxt_ + selectMessage);
        selectedIndex_ = index;
    }
}

void CalendarMonthPattern::InitVirtualButtonClickEvent(RefPtr<FrameNode> frameNode, int32_t index)
{
    CHECK_NULL_VOID(frameNode);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto clickCallback = [weak = WeakClaim(this), index](GestureEvent& info) {
        auto calendarPattern = weak.Upgrade();
        CHECK_NULL_VOID(calendarPattern);
        calendarPattern->SetVirtualNodeUserSelected(index);
    };
    auto clickListener = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickAfterEvent(clickListener);
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

float CalendarMonthPattern::GetWidth(const RefPtr<FrameNode>& host)
{
    auto width = 0.0f;
    auto contentConstraint = host->GetLayoutProperty()->GetLayoutConstraint();
    if (!contentConstraint.has_value()) {
        return width;
    }
    auto constraint = contentConstraint.value();
    auto selfWidth = constraint.selfIdealSize.Width();
    if (!selfWidth.has_value()) {
        return width;
    }
    width = selfWidth.value()
        - CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT.ConvertToPx() * CALENDAR_DISTANCE_ADJUST_FOCUSED_SIZE;
    return width;
}

void CalendarMonthPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    auto swiperNode = host->GetParent();
    CHECK_NULL_VOID(swiperNode);
    auto calendarNode = swiperNode->GetParent();
    CHECK_NULL_VOID(calendarNode);
    auto scrollNode = calendarNode->GetParent();
    CHECK_NULL_VOID(scrollNode);
    auto columnNode = scrollNode->GetParent();
    CHECK_NULL_VOID(columnNode);
    auto rowNode = columnNode->GetChildAtIndex(WEEK_ROW_INDEX);
    CHECK_NULL_VOID(rowNode);
    auto textNodes = rowNode->GetChildren();
    for (auto textNode : textNodes) {
        auto textFrameNode = AceType::DynamicCast<NG::FrameNode>(textNode);
        CHECK_NULL_VOID(textFrameNode);
        auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateTextColor(theme->GetCalendarTheme().weekColor);
    }

    if (SystemProperties::ConfigChangePerform()) {
        rowNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        swiperNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void CalendarMonthPattern::OnLanguageConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    auto swiperNode = host->GetParent();
    CHECK_NULL_VOID(swiperNode);
    auto calendarNode = swiperNode->GetParent();
    CHECK_NULL_VOID(calendarNode);
    auto scrollNode = calendarNode->GetParent();
    CHECK_NULL_VOID(scrollNode);
    auto columnNode = scrollNode->GetParent();
    CHECK_NULL_VOID(columnNode);
    auto rowNode = columnNode->GetChildAtIndex(WEEK_ROW_INDEX);
    CHECK_NULL_VOID(rowNode);
    auto textNodes = rowNode->GetChildren();
    std::vector<std::string> weekNumbers = Localization::GetInstance()->GetWeekdays(true);
    int32_t column = 0;
    for (auto textNode : textNodes) {
        std::string weekContent { weekNumbers[column % CALENDAR_WEEK_DAYS] };
        auto textFrameNode = AceType::DynamicCast<NG::FrameNode>(textNode);
        CHECK_NULL_VOID(textFrameNode);
        auto calendarPaintProperty = host->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        auto fontSize = calendarPaintProperty->GetWeekFontSize().value_or(theme->GetCalendarTheme().weekFontSize);
        auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateContent(weekContent);
        textLayoutProperty->UpdateFontSize(fontSize);
        ++column;
    }
}

void CalendarMonthPattern::BeforeSyncGeometryProperties(const DirtySwapConfig& config)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto width = GetWidth(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    auto calendarDaySize = GetDaySize(theme);
    auto space = (width - calendarDaySize.ConvertToPx() * CALENDAR_WEEK_DAYS) / (CALENDAR_WEEK_DAYS - 1);
    Dimension colSpace = 0.0_px;
    if (Positive(space)) {
        colSpace.SetValue(space);
    }
    auto swiperNode = host->GetParent();
    CHECK_NULL_VOID(swiperNode);
    auto calendarNode = swiperNode->GetParent();
    CHECK_NULL_VOID(calendarNode);
    auto scrollNode = calendarNode->GetParent();
    CHECK_NULL_VOID(scrollNode);
    auto columnNode = scrollNode->GetParent();
    CHECK_NULL_VOID(columnNode);
    auto rowNode = columnNode->GetChildAtIndex(WEEK_ROW_INDEX);
    CHECK_NULL_VOID(rowNode);
    auto textNodes = rowNode->GetChildren();
    for (auto textNode : textNodes) {
        auto textFrameNode = AceType::DynamicCast<NG::FrameNode>(textNode);
        CHECK_NULL_VOID(textFrameNode);
        auto calendarPaintProperty = host->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        auto fontSize = calendarPaintProperty->GetWeekFontSize().value_or(theme->GetCalendarTheme().weekFontSize);
        auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateFontSize(fontSize);
        textLayoutProperty->UpdateTextColor(theme->GetCalendarTheme().weekColor);
        textLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(calendarDaySize), std::nullopt));
    }

    auto rowFrameNode = AceType::DynamicCast<NG::FrameNode>(rowNode);
    CHECK_NULL_VOID(rowFrameNode);
    auto weekLayoutProperty = rowFrameNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(weekLayoutProperty);
    weekLayoutProperty->UpdateSpace(colSpace);
    rowFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
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
        if (info.GetTouches().empty()) {
            return;
        }
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
    auto eventHub = GetOrCreateEventHub<CalendarEventHub>();
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

bool CalendarMonthPattern::IsDateInRange(const CalendarDay& day)
{
    PickerDate date;
    date.SetYear(day.month.year);
    date.SetMonth(day.month.month);
    date.SetDay(day.day);
    for (const auto& range : disabledDateRange_) {
        if (PickerDate::IsDateInRange(date, range.first, range.second)) {
            return false;
        }
    }
    return PickerDate::IsDateInRange(date, startDate_, endDate_);
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
        if (!IsDateInRange(obtainedMonth_.days[index])) {
            return;
        }
        for (auto& day : pattern->obtainedMonth_.days) {
            day.focused = false;
        }
        auto calendarEventHub = GetOrCreateEventHub<CalendarEventHub>();
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
    if (!(index < 0 || index >= static_cast<int32_t>(obtainedMonth_.days.size())) && isPressed &&
        IsDateInRange(obtainedMonth_.days[index])) {
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
    if (index < 0 || index >= static_cast<int32_t>(obtainedMonth_.days.size())) {
        return;
    }
    for (auto& day : obtainedMonth_.days) {
        day.isHovering = false;
    }
    if (state && IsDateInRange(obtainedMonth_.days[index])) {
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
    auto pipelineContext = host->GetContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_RETURN(theme, false);
    auto gregorianDayHeight = paintProperty->GetGregorianCalendarHeightValue({}).ConvertToPx() <= 0
                                ? theme->GetCalendarTheme().gregorianCalendarHeight.ConvertToPx()
                                : paintProperty->GetGregorianCalendarHeightValue({}).ConvertToPx();
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
    if (IsLargeSize(theme)) {
        gregorianDayHeight = GetDaySize(theme).ConvertToPx();
    }
    auto browHeight = weekHeight + weekAndDayRowSpace - gregorianDayHeight;
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
    auto textDirection = host->GetLayoutProperty()->GetNonAutoLayoutDirection();
    if (textDirection == TextDirection::RTL) {
        x = columnsOfData - x - 1;
    }
    return (y * columnsOfData + x);
}

class CalendarAccessibilitySAObserverCallback : public AccessibilitySAObserverCallback {
public:
    CalendarAccessibilitySAObserverCallback(
        const WeakPtr<CalendarMonthPattern> &weakCalendarPattern, int64_t accessibilityId)
        : AccessibilitySAObserverCallback(accessibilityId), weakCalendarPattern_(weakCalendarPattern)
    {}

    ~CalendarAccessibilitySAObserverCallback() override = default;

    bool OnState(bool state) override
    {
        auto calendarPattern = weakCalendarPattern_.Upgrade();
        CHECK_NULL_RETURN(calendarPattern, false);
        if (state) {
            calendarPattern->InitCurrentVirtualNode();
        } else {
            calendarPattern->ClearCalendarVirtualNode();
        }
        return true;
    }
private:
    WeakPtr<CalendarMonthPattern> weakCalendarPattern_;
};

void CalendarMonthPattern::InitializeCalendarAccessibility()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilitySAObserverCallback_ = std::make_shared<CalendarAccessibilitySAObserverCallback>(
        WeakClaim(this), host->GetAccessibilityId());
    accessibilityManager->RegisterAccessibilitySAObserverCallback(host->GetAccessibilityId(),
        accessibilitySAObserverCallback_);
    if (margin_ == 0) {
        auto paintProperty = host->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        dayHeight_ = paintProperty->GetDayHeight().value_or(Dimension(0.0f)).ConvertToPx();
        dayWidth_ = paintProperty->GetDayWidth().value_or(Dimension(0.0f)).ConvertToPx();
        RefPtr<CalendarTheme> theme = pipeline->GetTheme<CalendarTheme>();
        CHECK_NULL_VOID(theme);
        auto sliderTheme = pipeline->GetTheme<SliderTheme>();
        CHECK_NULL_VOID(sliderTheme);
        margin_ = theme->GetDialogMargin().ConvertToPx();
        selectedTxt_ = sliderTheme->GetSelectedTxt();
        disabledDesc_ = sliderTheme->GetDisabelDesc();
        deviceOrientation_ = SystemProperties::GetDeviceOrientation();
    }
}

void CalendarMonthPattern::InitCurrentVirtualNode()
{
    auto deviceOrientation = SystemProperties::GetDeviceOrientation();
    if ((!isInitVirtualNode_ || buttonAccessibilityNodeVec_.size() != obtainedMonth_.days.size() ||
        deviceOrientation_ != deviceOrientation) &&
        monthState_ == MonthState::CUR_MONTH) {
        isInitVirtualNode_ = InitCalendarVirtualNode();
    } else {
        FireModifyAccessibilityVirtualNode(obtainedMonth_);
    }
}

void CalendarMonthPattern::ClearFocusCalendarDay()
{
    focusedCalendarDay_.index = 0;
    deviceOrientation_ = SystemProperties::GetDeviceOrientation();
    CHECK_NULL_VOID(lineNode_);
    auto lineNodeProp = lineNode_->GetLayoutProperty();
    CHECK_NULL_VOID(lineNodeProp);
    if (monthState_ == MonthState::CUR_MONTH) {
        lineNodeProp->UpdateVisibility(VisibleType::VISIBLE);
    } else {
        lineNodeProp->UpdateVisibility(VisibleType::GONE);
    }
}

void CalendarMonthPattern::ClearCalendarVirtualNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    buttonAccessibilityNodeVec_.clear();
    accessibilityPropertyVec_.clear();
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SaveAccessibilityVirtualNode(nullptr);
}

void CalendarMonthPattern::SetLineNodeSize(RefPtr<FrameNode> lineNode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostLayoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(hostLayoutProperty);
    auto width = hostLayoutProperty->GetLayoutConstraint()->selfIdealSize.Width().value_or(Infinity<float>());
    auto height = hostLayoutProperty->GetLayoutConstraint()->selfIdealSize.Height().value_or(Infinity<float>());
    CHECK_NULL_VOID(lineNode);
    auto layoutProperty = lineNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width), CalcLength(height)));
}

void CalendarMonthPattern::SetFocusNode(int32_t index, bool isDeviceOrientation)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto textDirection = layoutProperty->GetNonAutoLayoutDirection();
    auto remainderWeek = index % CALENDAR_WEEK_DAYS;
    int32_t selectedIndex = (textDirection == TextDirection::RTL ?
        CALENDAR_WEEK_DAYS - remainderWeek * 2 + index - 1 : index);
    if (isDeviceOrientation) {
        selectedIndex = index;
    }
    if (selectedIndex >= static_cast<int32_t>(buttonAccessibilityNodeVec_.size()) || selectedIndex < 0) {
        return;
    }
    buttonAccessibilityNodeVec_[selectedIndex]->OnAccessibilityEvent(AccessibilityEventType::REQUEST_FOCUS);
    selectedIndex_ = selectedIndex;
}

bool CalendarMonthPattern::InitCalendarVirtualNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    buttonAccessibilityNodeVec_.clear();
    accessibilityPropertyVec_.clear();
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    accessibilityProperty->SaveAccessibilityVirtualNode(nullptr);
    auto lineNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    for (auto& day : obtainedMonth_.days) {
        auto buttonNode = AddButtonNodeIntoVirtual(day);
        lineNode->AddChild(buttonNode);
        buttonAccessibilityNodeVec_.emplace_back(buttonNode);
        ChangeVirtualNodeContent(day);
    }
    SetLineNodeSize(lineNode);
    SetCalendarAccessibilityLevel(AccessibilityProperty::Level::NO_STR);
    accessibilityProperty->SetAccessibilityText(" ");
    auto virtualFrameNode = AceType::DynamicCast<NG::FrameNode>(lineNode);
    CHECK_NULL_RETURN(virtualFrameNode, false);
    virtualFrameNode->SetAccessibilityNodeVirtual();
    virtualFrameNode->SetAccessibilityVirtualNodeParent(AceType::DynamicCast<NG::UINode>(host));
    virtualFrameNode->SetFirstAccessibilityVirtualNode();
    FrameNode::ProcessOffscreenNode(virtualFrameNode);
    accessibilityProperty->SaveAccessibilityVirtualNode(lineNode);
    lineNode_ = lineNode;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    auto deviceOrientation = SystemProperties::GetDeviceOrientation();
    if (deviceOrientation_ != deviceOrientation && !isFirstEnter_) {
        SetFocusNode(focusedCalendarDay_.index, true);
        deviceOrientation_ = deviceOrientation;
    }
    if (!isFirstEnter_) {
        return true;
    }
    for (auto &day : obtainedMonth_.days) {
        if (day.isSelected) {
            SetFocusNode(day.index);
            isFirstEnter_ = false;
            focusedCalendarDay_ = day;
            break;
        }
    }
    return true;
}

std::pair<int32_t, int32_t> GetXYByIndex(const int32_t index)
{
    if (index < CALENDAR_WEEK_DAYS - 1) {
        return {index, 0};
    } else {
        return {(index % CALENDAR_WEEK_DAYS), (index / CALENDAR_WEEK_DAYS)};
    }
}

void CalendarMonthPattern::ChangeVirtualNodeState(const CalendarDay& calendarDay)
{
    if (selectedIndex_ >= static_cast<int32_t>(accessibilityPropertyVec_.size()) || selectedIndex_ < 0) {
        return;
    }
    if (calendarDay.index != selectedIndex_ &&
        calendarDay.month.month == obtainedMonth_.month && calendarDay.month.month == obtainedMonth_.month) {
        accessibilityPropertyVec_[selectedIndex_]->SetUserSelected(true);
    }
}

RefPtr<FrameNode> CalendarMonthPattern::AddButtonNodeIntoVirtual(const CalendarDay& calendarDay)
{
    auto buttonNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    auto buttonAccessibilityProperty = buttonNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_RETURN(buttonAccessibilityProperty, nullptr);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto pipeline = host->GetContext();
    if (pipeline) {
        UpdateAccessibilityButtonNode(buttonNode, calendarDay.index);
    } else {
        UpdateButtonNodeWithoutTheme(buttonNode, calendarDay.index);
    }
    accessibilityPropertyVec_.emplace_back(buttonAccessibilityProperty);
    InitVirtualButtonClickEvent(buttonNode, calendarDay.index);
    buttonAccessibilityProperty->SetOnAccessibilityFocusCallback([weak = WeakClaim(this), calendarDay](bool focus) {
        if (focus) {
            auto calendar = weak.Upgrade();
            CHECK_NULL_VOID(calendar);
            calendar->focusedCalendarDay_ = calendarDay;
            calendar->ChangeVirtualNodeState(calendarDay);
        }
    });
    return buttonNode;
}

float GetRowSpace(RefPtr<CalendarPaintProperty> paintProperty, RefPtr<CalendarTheme> theme, size_t daySize)
{
    auto dailyFourRowSpace = NonPositive(paintProperty->GetDailyFourRowSpaceValue({}).ConvertToPx())
                                 ? theme->GetCalendarTheme().dailySixRowSpace.ConvertToPx()
                                 : paintProperty->GetDailyFourRowSpaceValue({}).ConvertToPx();
    auto dailyFiveRowSpace = paintProperty->GetDailyFiveRowSpaceValue({}).ConvertToPx() <= 0
                                 ? theme->GetCalendarTheme().dailyFiveRowSpace.ConvertToPx()
                                 : paintProperty->GetDailyFiveRowSpaceValue({}).ConvertToPx();
    auto dailySixRowSpace = paintProperty->GetDailySixRowSpaceValue({}).ConvertToPx() <= 0
                                ? theme->GetCalendarTheme().dailySixRowSpace.ConvertToPx()
                                : paintProperty->GetDailySixRowSpaceValue({}).ConvertToPx();
    auto rows = (static_cast<int32_t>(daySize) / CALENDAR_WEEK_DAYS);
    auto rowSpace = dailySixRowSpace;
    switch (rows) {
        case DAILY_FOUR_ROWSPACE: {
            rowSpace = dailyFourRowSpace;
            break;
        }
        case DAILY_FIVE_ROWSPACE: {
            rowSpace = dailyFiveRowSpace;
            break;
        }
        default:
            break;
    }
    return rowSpace;
}

void CalendarMonthPattern::SetCalendarAccessibilityLevel(const std::string& level)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetAccessibilityLevel(level);
    auto parent = host->GetParent();
    while (parent && parent->GetTag() != V2::DIALOG_ETS_TAG) {
        auto parentNode = AceType::DynamicCast<NG::FrameNode>(parent);
        CHECK_NULL_VOID(parentNode);
        auto parentAccessibilityProperty = parentNode->GetAccessibilityProperty<AccessibilityProperty>();
        CHECK_NULL_VOID(parentAccessibilityProperty);
        parentAccessibilityProperty->SetAccessibilityLevel(level);
        parent = parent->GetParent();
    }
}

void CalendarMonthPattern::InitAccessibilityHoverEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetAccessibilityHoverEvent([weak = WeakClaim(this)](bool isHover, AccessibilityHoverInfo& info) {
        auto calendar = weak.Upgrade();
        CHECK_NULL_VOID(calendar);
        calendar->HandleAccessibilityHoverEvent(isHover, info);
    });
}

void CalendarMonthPattern::HandleAccessibilityHoverEvent(bool isHover, AccessibilityHoverInfo& info)
{
    if (isHover) {
        isOnHover_ = true;
    } else if (!isHover) {
        isOnHover_ = false;
    }
}

float GetRowSpaceWithoutTheme(RefPtr<CalendarPaintProperty> paintProperty, size_t daySize)
{
    auto dailyFourRowSpace = NonPositive(paintProperty->GetDailyFourRowSpaceValue({}).ConvertToPx())
                                 ? 0.0f
                                 : paintProperty->GetDailyFourRowSpaceValue({}).ConvertToPx();
    auto dailyFiveRowSpace = paintProperty->GetDailyFiveRowSpaceValue({}).ConvertToPx() <= 0
                                 ? 0.0f
                                 : paintProperty->GetDailyFiveRowSpaceValue({}).ConvertToPx();
    auto dailySixRowSpace = paintProperty->GetDailySixRowSpaceValue({}).ConvertToPx() <= 0
                                ? 0.0f
                                : paintProperty->GetDailySixRowSpaceValue({}).ConvertToPx();
    auto rows = (static_cast<int32_t>(daySize) / CALENDAR_WEEK_DAYS);
    auto rowSpace = dailySixRowSpace;
    switch (rows) {
        case DAILY_FOUR_ROWSPACE: {
            rowSpace = dailyFourRowSpace;
            break;
        }
        case DAILY_FIVE_ROWSPACE: {
            rowSpace = dailyFiveRowSpace;
            break;
        }
        default:
            break;
    }
    return rowSpace;
}

void CalendarMonthPattern::UpdateButtonNodeWithoutTheme(RefPtr<FrameNode> frameNode, int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<CalendarPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto dayHeight = paintProperty->GetDayHeight().value_or(Dimension(0.0f)).ConvertToPx();
    auto dayWidth = paintProperty->GetDayWidth().value_or(Dimension(0.0f)).ConvertToPx();
    CHECK_NULL_VOID(frameNode);
    auto buttonLayoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    buttonLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(dayWidth), CalcLength(dayHeight)));
    auto pos = GetXYByIndex(index);
    auto colSpace = paintProperty->GetColSpaceValue({}).ConvertToPx() <= 0
                    ? 0.0f
                    : paintProperty->GetColSpaceValue({}).ConvertToPx();
    Dimension buttonOffsetX = Dimension(margin_ / 2 + (colSpace + dayWidth) * pos.first);
    auto weekHeight = paintProperty->GetWeekHeight().value_or(Dimension(0.0f)).ConvertToPx();
    auto rowSpace = GetRowSpaceWithoutTheme(paintProperty, obtainedMonth_.days.size());
    auto weekAndDayRowSpace =
        paintProperty->GetWeekAndDayRowSpace().value_or(Dimension(0.0f)).ConvertToPx();
    auto gregorianDayHeight = paintProperty->GetGregorianCalendarHeightValue({}).ConvertToPx();
    auto browHeight = weekHeight + weekAndDayRowSpace - gregorianDayHeight;
    Dimension buttonOffsetY = Dimension(browHeight + (dayHeight + rowSpace) * pos.second);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdatePosition(OffsetT(buttonOffsetX, buttonOffsetY));
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void CalendarMonthPattern::UpdateAccessibilityButtonNode(RefPtr<FrameNode> frameNode, int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<CalendarPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    auto dayHeight = paintProperty->GetDayHeight().value_or(theme->GetCalendarTheme().dayHeight).ConvertToPx();
    auto dayWidth = paintProperty->GetDayWidth().value_or(theme->GetCalendarTheme().dayWidth).ConvertToPx();
    CHECK_NULL_VOID(frameNode);
    auto buttonLayoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    buttonLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(dayWidth), CalcLength(dayHeight)));
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pos = GetXYByIndex(index);
    auto colSpace = paintProperty->GetColSpaceValue({}).ConvertToPx() <= 0
                    ? theme->GetCalendarTheme().colSpace.ConvertToPx()
                    : paintProperty->GetColSpaceValue({}).ConvertToPx();
    colSpace_ = colSpace;
    Dimension buttonOffsetX = Dimension(margin_ / 2 + (colSpace + dayWidth) * pos.first);
    auto gregorianDayHeight = paintProperty->GetGregorianCalendarHeightValue({}).ConvertToPx() <= 0
                            ? theme->GetCalendarTheme().gregorianCalendarHeight.ConvertToPx()
                            : paintProperty->GetGregorianCalendarHeightValue({}).ConvertToPx();
    auto weekHeight = paintProperty->GetWeekHeight().value_or(theme->GetCalendarTheme().weekHeight).ConvertToPx();
    auto rowSpace = GetRowSpace(paintProperty, theme, obtainedMonth_.days.size());
    auto weekAndDayRowSpace =
        paintProperty->GetWeekAndDayRowSpace().value_or(theme->GetCalendarTheme().weekAndDayRowSpace).ConvertToPx();
    if (IsLargeSize(theme)) {
        gregorianDayHeight = GetDaySize(theme).ConvertToPx();
    }
    auto browHeight = weekHeight + weekAndDayRowSpace - gregorianDayHeight;
    Dimension buttonOffsetY = Dimension(browHeight + (dayHeight + rowSpace) * pos.second);
    renderContext->UpdatePosition(OffsetT(buttonOffsetX, buttonOffsetY));
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

std::string CalendarMonthPattern::GetDayStr(int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "");
    auto pipelineContext = host->GetContext();
    CHECK_NULL_RETURN(pipelineContext, "");
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_RETURN(theme, "");
    switch (index) {
        case MONDAY_INDEX:
            return theme->GetCalendarTheme().monday;
        case TUESDAY_INDEX:
            return theme->GetCalendarTheme().tuesday;
        case WEDNESDAY_INDEX:
            return theme->GetCalendarTheme().wednesday;
        case THURSDAY_INDEX:
            return theme->GetCalendarTheme().thursday;
        case FRIDAY_INDEX:
            return theme->GetCalendarTheme().friday;
        case SATURDAY_INDEX:
            return theme->GetCalendarTheme().saturday;
        default:
            return theme->GetCalendarTheme().sunday;
    }
}

std::string CalendarMonthPattern::GetTodayStr()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "");
    auto pipelineContext = host->GetContext();
    CHECK_NULL_RETURN(pipelineContext, "");
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_RETURN(theme, "");
    return theme->GetCalendarTheme().today;
}

void CalendarMonthPattern::ChangeVirtualNodeContent(const CalendarDay& calendarDay)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto textDirection = layoutProperty->GetNonAutoLayoutDirection();
    auto remainderWeek = calendarDay.index % CALENDAR_WEEK_DAYS;
    int32_t index = (textDirection == TextDirection::RTL ?
        CALENDAR_WEEK_DAYS - remainderWeek * 2 + calendarDay.index - 1 : calendarDay.index);
    if (index >= static_cast<int32_t>(buttonAccessibilityNodeVec_.size()) || index < 0) {
        return;
    }
    std::string message;
    if (calendarDay.month.year == calendarDay_.month.year && calendarDay.month.month == calendarDay_.month.month &&
                      calendarDay.day == calendarDay_.day) {
        message += GetTodayStr();
    }
    message += std::to_string(calendarDay.month.year) + "/";
    message += std::to_string(calendarDay.month.month) + "/";
    message += std::to_string(calendarDay.day);
    message += GetDayStr(remainderWeek);
    auto node = buttonAccessibilityNodeVec_[index];
    auto buttonAccessibilityProperty = node->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(buttonAccessibilityProperty);
    if (calendarDay.month.month != obtainedMonth_.month) {
        buttonAccessibilityProperty->SetAccessibilityDescription(disabledDesc_);
    } else if (index == selectedIndex_) {
        // Delete the description of the selected node
        buttonAccessibilityProperty->SetAccessibilityDescription(" ");
    } else {
        // Set the default description to other nodes
        buttonAccessibilityProperty->SetAccessibilityDescription("");
    }
    buttonAccessibilityProperty->SetUserDisabled(calendarDay.month.month != obtainedMonth_.month ? true : false);
    buttonAccessibilityProperty->SetUserSelected(false);
    buttonAccessibilityProperty->SetAccessibilityText(message);
}

void CalendarMonthPattern::FireModifyAccessibilityVirtualNode(const ObtainedMonth& currentData)
{
    if (isInitVirtualNode_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->AddAfterRenderTask([weak = WeakClaim(this), currentData]() {
            auto calendarMonthPattern = weak.Upgrade();
            CHECK_NULL_VOID(calendarMonthPattern);
            calendarMonthPattern->ModifyAccessibilityVirtualNode(currentData);
        });
    }
}

void CalendarMonthPattern::ModifyAccessibilityVirtualNode(const ObtainedMonth& currentData)
{
    if (buttonAccessibilityNodeVec_.size() < 1) {
        return;
    }
    for (auto& day : currentData.days) {
        ChangeVirtualNodeContent(day);
    }
}

void CalendarMonthPattern::UpdateDayRadius(const CalcDimension& dayRadius)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<CalendarPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);

    if (pipelineContext->IsSystmColorChange()) {
        paintProperty->UpdateDayRadius(dayRadius);
    }

    if (host->GetRerenderable()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}
} // namespace OHOS::Ace::NG
