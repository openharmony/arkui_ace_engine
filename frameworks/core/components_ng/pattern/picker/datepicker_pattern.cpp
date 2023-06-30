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

#include "core/components_ng/pattern/picker/datepicker_pattern.h"

#include <stdint.h>
#include <string>
#include <utility>
#include <vector>

#include "base/utils/utils.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_column_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SINGLE_CHILD_SIZE = 1;
constexpr int32_t CHILD_SIZE = 3;
constexpr uint32_t MIN_MONTH = 1;
constexpr uint32_t MAX_MONTH = 12;
constexpr uint32_t MIN_DAY = 1;
const Dimension PRESS_INTERVAL = 4.0_vp;
const Dimension PRESS_RADIUS = 8.0_vp;
} // namespace
bool DatePickerPattern::inited_ = false;
const std::string DatePickerPattern::empty_;
std::vector<std::string> DatePickerPattern::years_;       // year from 1900 to 2100,count is 201
std::vector<std::string> DatePickerPattern::solarMonths_; // solar month from 1 to 12,count is 12
std::vector<std::string> DatePickerPattern::solarDays_;   // solar day from 1 to 31, count is 31
std::vector<std::string> DatePickerPattern::lunarMonths_; // lunar month from 1 to 24, count is 24
std::vector<std::string> DatePickerPattern::lunarDays_;   // lunar day from 1 to 30, count is 30
std::vector<std::string> DatePickerPattern::tagOrder_;    // order of year month day

void DatePickerPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

bool DatePickerPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    CHECK_NULL_RETURN_NOLOG(config.frameSizeChange, false);
    CHECK_NULL_RETURN(dirty, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, false);
    auto children = host->GetChildren();
    auto heigth = pickerTheme->GetDividerSpacing();
    for (const auto& child : children) {
        auto columnNode = DynamicCast<FrameNode>(child->GetLastChild());
        auto width = columnNode->GetGeometryNode()->GetFrameSize().Width();
        auto buttonNode = DynamicCast<FrameNode>(child->GetFirstChild());
        auto buttonConfirmLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        buttonConfirmLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
        buttonConfirmLayoutProperty->UpdateType(ButtonType::NORMAL);
        buttonConfirmLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(PRESS_RADIUS));
        buttonConfirmLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(width - PRESS_INTERVAL.ConvertToPx()), CalcLength(heigth - PRESS_INTERVAL)));
        auto buttonConfirmRenderContext = buttonNode->GetRenderContext();
        buttonConfirmRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        buttonNode->MarkModifyDone();
        buttonNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    return true;
}

void DatePickerPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    InitDisabled();
    if (ShowMonthDays()) {
        FlushMonthDaysColumn();
    } else {
        FlushColumn();
    }
    ShowTitle(GetTitleId());
    SetChangeCallback([weak = WeakClaim(this)](const RefPtr<FrameNode>& tag, bool add, uint32_t index, bool notify) {
        auto refPtr = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(refPtr);
        refPtr->HandleColumnChange(tag, add, index, notify);
    });
    SetEventCallback([weak = WeakClaim(this), titleId = GetTitleId()](bool refresh) {
        auto refPtr = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(refPtr);
        refPtr->FireChangeEvent(refresh);
        if (refresh) {
            refPtr->ShowTitle(titleId);
        }
    });
    auto focusHub = host->GetFocusHub();
    if (focusHub) {
        InitOnKeyEvent(focusHub);
    }
}

void DatePickerPattern::InitDisabled()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto renderContext = host->GetRenderContext();
    enabled_ = eventHub->IsEnabled();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void DatePickerPattern::HandleColumnChange(const RefPtr<FrameNode>& tag, bool isAdd, uint32_t index, bool needNotify)
{
    CHECK_NULL_VOID(GetHost());
    std::vector<RefPtr<FrameNode>> tags;
    if (ShowMonthDays()) {
        HandleMonthDaysChange(tag, isAdd, index, tags);
    } else {
        OnDataLinking(tag, isAdd, index, tags);
    }
    for (const auto& tag : tags) {
        auto iter = std::find_if(datePickerColumns_.begin(), datePickerColumns_.end(),
            [&tag](const RefPtr<FrameNode>& column) { return column->GetId() == tag->GetId(); });
        if (iter != datePickerColumns_.end()) {
            auto datePickerColumnPattern = (*iter)->GetPattern<DatePickerColumnPattern>();
            CHECK_NULL_VOID(datePickerColumnPattern);
            datePickerColumnPattern->FlushCurrentOptions(isAdd, true, false);
        }
    }
}

void DatePickerPattern::SetEventCallback(EventCallback&& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    for (const auto& child : children) {
        auto stackNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(stackNode);
        auto childNode = stackNode->GetChildAtIndex(1);
        CHECK_NULL_VOID(childNode);
        auto datePickerColumnPattern = DynamicCast<FrameNode>(childNode)->GetPattern<DatePickerColumnPattern>();
        CHECK_NULL_VOID(datePickerColumnPattern);
        datePickerColumnPattern->SetEventCallback(std::move(value));
    }
}

void DatePickerPattern::SetChangeCallback(ColumnChangeCallback&& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    for (const auto& child : children) {
        auto stackNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(stackNode);
        auto childNode = stackNode->GetChildAtIndex(1);
        CHECK_NULL_VOID(childNode);
        auto datePickerColumnPattern = DynamicCast<FrameNode>(childNode)->GetPattern<DatePickerColumnPattern>();
        CHECK_NULL_VOID(datePickerColumnPattern);
        datePickerColumnPattern->SetChangeCallback(std::move(value));
    }
}

void DatePickerPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN_NOLOG(pattern, false);
        return pattern->OnKeyEvent(event);
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

void DatePickerPattern::PaintFocusState()
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

void DatePickerPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childSize = static_cast<float>(host->GetChildren().size());
    auto stackChild = DynamicCast<FrameNode>(host->GetChildAtIndex(focusKeyID_));
    CHECK_NULL_VOID(stackChild);
    auto pickerChild = DynamicCast<FrameNode>(stackChild->GetLastChild());
    CHECK_NULL_VOID(pickerChild);
    auto columnWidth = pickerChild->GetGeometryNode()->GetFrameSize().Width();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto frameWidth = host->GetGeometryNode()->GetFrameSize().Width();
    auto dividerSpacing = pickerTheme->GetDividerSpacing().ConvertToPx();
    auto pickerThemeWidth = dividerSpacing * 2;

    auto centerX = (frameWidth / childSize - pickerThemeWidth) / 2 +
                   pickerChild->GetGeometryNode()->GetFrameRect().Width() * focusKeyID_ +
                   PRESS_INTERVAL.ConvertToPx() * 2;
    auto centerY =
        (host->GetGeometryNode()->GetFrameSize().Height() - dividerSpacing) / 2 + PRESS_INTERVAL.ConvertToPx();
    float piantRectWidth = (dividerSpacing - PRESS_INTERVAL.ConvertToPx()) * 2;
    float piantRectHeight = dividerSpacing - PRESS_INTERVAL.ConvertToPx() * 2;
    if (piantRectWidth > columnWidth) {
        piantRectWidth = columnWidth;
        centerX = focusKeyID_ * columnWidth;
    }
    paintRect.SetRect(RectF(centerX, centerY, piantRectWidth, piantRectHeight));
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
}

bool DatePickerPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (event.code == KeyCode::KEY_DPAD_UP || event.code == KeyCode::KEY_DPAD_DOWN ||
        event.code == KeyCode::KEY_DPAD_LEFT || event.code == KeyCode::KEY_DPAD_RIGHT) {
        HandleDirectionKey(event.code);
        return true;
    }
    return false;
}

bool DatePickerPattern::HandleDirectionKey(KeyCode code)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);

    auto stackChild = DynamicCast<FrameNode>(host->GetChildAtIndex(focusKeyID_));
    auto pickerChild = DynamicCast<FrameNode>(stackChild->GetChildAtIndex(1));
    auto pattern = pickerChild->GetPattern<DatePickerColumnPattern>();
    auto currernIndex = pattern->GetCurrentIndex();
    auto totalOptionCount = GetOptionCount(pickerChild);
    if (code == KeyCode::KEY_DPAD_UP && totalOptionCount != 0) {
        pattern->SetCurrentIndex((totalOptionCount + currernIndex - 1) % totalOptionCount);
        pattern->FlushCurrentOptions();
        pattern->HandleChangeCallback(false, true);
        pattern->HandleEventCallback(true);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return true;
    }
    if (code == KeyCode::KEY_DPAD_DOWN && totalOptionCount != 0) {
        pattern->SetCurrentIndex((totalOptionCount + currernIndex + 1) % totalOptionCount);
        pattern->FlushCurrentOptions();
        pattern->HandleChangeCallback(true, true);
        pattern->HandleEventCallback(true);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return true;
    }
    if (code == KeyCode::KEY_DPAD_LEFT) {
        focusKeyID_ -= 1;
        if (focusKeyID_ < 0) {
            focusKeyID_ = 0;
        }
        PaintFocusState();
        return true;
    }
    if (code == KeyCode::KEY_DPAD_RIGHT) {
        focusKeyID_ += 1;
        auto childSize = static_cast<int32_t>(host->GetChildren().size());
        if (focusKeyID_ > childSize -1) {
            focusKeyID_ = childSize -1;
        }
        PaintFocusState();
        return true;
    }
    return false;
}

std::unordered_map<std::string, RefPtr<FrameNode>> DatePickerPattern::GetAllChildNode()
{
    std::unordered_map<std::string, RefPtr<FrameNode>> allChildNode;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, allChildNode);
    auto children = host->GetChildren();
    if (children.size() != CHILD_SIZE) {
        return allChildNode;
    }
    auto iter = children.begin();
    auto year = (*iter);
    CHECK_NULL_RETURN(year, allChildNode);
    iter++;
    auto month = *iter;
    CHECK_NULL_RETURN(month, allChildNode);
    iter++;
    auto day = *iter;
    CHECK_NULL_RETURN(day, allChildNode);
    auto stackYear = DynamicCast<FrameNode>(year);
    auto yearNode = DynamicCast<FrameNode>(stackYear->GetChildAtIndex(1));
    auto stackMonth = DynamicCast<FrameNode>(month);
    auto monthNode = DynamicCast<FrameNode>(stackMonth->GetChildAtIndex(1));
    auto stackDay = DynamicCast<FrameNode>(day);
    auto dayNode = DynamicCast<FrameNode>(stackDay->GetChildAtIndex(1));

    CHECK_NULL_RETURN(yearNode, allChildNode);
    CHECK_NULL_RETURN(monthNode, allChildNode);
    CHECK_NULL_RETURN(dayNode, allChildNode);
    allChildNode["year"] = yearNode;
    allChildNode["month"] = monthNode;
    allChildNode["day"] = dayNode;
    return allChildNode;
}

void DatePickerPattern::FlushColumn()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto allChildNode = GetAllChildNode();

    auto dataPickerRowLayoutProperty = host->GetLayoutProperty<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(dataPickerRowLayoutProperty);
    auto lunarDate = dataPickerRowLayoutProperty->GetSelectedDate().value_or(SolarToLunar(GetSelectedDate()));
    AdjustLunarDate(lunarDate);
    if (dataPickerRowLayoutProperty->GetLunar().value_or(false)) {
        LunarColumnsBuilding(lunarDate);
    } else {
        SolarColumnsBuilding(LunarToSolar(lunarDate));
    }

    auto yearNode = allChildNode["year"];
    auto monthNode = allChildNode["month"];
    auto dayNode = allChildNode["day"];
    CHECK_NULL_VOID(yearNode);
    CHECK_NULL_VOID(monthNode);
    CHECK_NULL_VOID(dayNode);
    auto yearColumnPattern = yearNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(yearColumnPattern);
    auto monthColumnPattern = monthNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(monthColumnPattern);
    auto dayColumnPattern = dayNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(dayColumnPattern);

    yearColumnPattern->SetShowCount(GetShowCount());
    monthColumnPattern->SetShowCount(GetShowCount());
    dayColumnPattern->SetShowCount(GetShowCount());
    yearColumnPattern->FlushCurrentOptions();
    monthColumnPattern->FlushCurrentOptions();
    dayColumnPattern->FlushCurrentOptions();
}

void DatePickerPattern::FlushMonthDaysColumn()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto children = host->GetChildren();
    if (children.size() <= SINGLE_CHILD_SIZE) {
        return;
    }
    auto iter = children.begin();
    auto monthDays = (*iter);
    CHECK_NULL_VOID(monthDays);
    iter++;
    auto year = *iter;
    CHECK_NULL_VOID(year);
    auto stackMonthDays = DynamicCast<FrameNode>(monthDays);
    auto monthDaysNode = DynamicCast<FrameNode>(stackMonthDays->GetChildAtIndex(1));
    auto stackYear = DynamicCast<FrameNode>(year);
    auto yearDaysNode = DynamicCast<FrameNode>(stackYear->GetChildAtIndex(1));
    CHECK_NULL_VOID(monthDaysNode);
    CHECK_NULL_VOID(yearDaysNode);
    auto dataPickerRowLayoutProperty = host->GetLayoutProperty<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(dataPickerRowLayoutProperty);
    if (dataPickerRowLayoutProperty->GetLunar().value_or(false)) {
        LunarMonthDaysColumnBuilding(
            dataPickerRowLayoutProperty->GetSelectedDate().value_or(SolarToLunar(GetSelectedDate())));
    } else {
        SolarMonthDaysColumnsBuilding(
            LunarToSolar(dataPickerRowLayoutProperty->GetSelectedDate().value_or(SolarToLunar(GetSelectedDate()))));
    }

    auto monthDaysColumnPattern = monthDaysNode->GetPattern<DatePickerColumnPattern>();
    auto yearColumnPattern = yearDaysNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(monthDaysColumnPattern);
    CHECK_NULL_VOID(yearColumnPattern);

    monthDaysColumnPattern->SetShowCount(GetShowCount());
    yearColumnPattern->SetShowCount(GetShowCount());
    monthDaysColumnPattern->FlushCurrentOptions();
    yearColumnPattern->FlushCurrentOptions();
}

void DatePickerPattern::FireChangeEvent(bool refresh) const
{
    if (refresh) {
        auto datePickerEventHub = GetEventHub<DatePickerEventHub>();
        CHECK_NULL_VOID(datePickerEventHub);
        auto str = GetSelectedObject(true);
        auto info = std::make_shared<DatePickerChangeEvent>(str);
        datePickerEventHub->FireChangeEvent(info.get());
        datePickerEventHub->FireDialogChangeEvent(str);
    }
}

void DatePickerPattern::ShowTitle(int32_t titleId)
{
    if (HasTitleNode()) {
        auto textTitleNode = FrameNode::GetOrCreateFrameNode(
            V2::TEXT_ETS_TAG, titleId, []() { return AceType::MakeRefPtr<TextPattern>(); });
        auto dateStr = GetCurrentDate();
        CHECK_NULL_VOID(textTitleNode);
        auto textLayoutProperty = textTitleNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateContent(dateStr.ToString(false));
        textTitleNode->MarkModifyDone();
    }
}

void DatePickerPattern::OnDataLinking(
    const RefPtr<FrameNode>& tag, bool isAdd, uint32_t index, std::vector<RefPtr<FrameNode>>& resultTags)
{
    auto allChildNode = GetAllChildNode();
    auto yearNode = allChildNode["year"];
    auto monthNode = allChildNode["month"];
    auto dayNode = allChildNode["day"];
    CHECK_NULL_VOID(yearNode);
    CHECK_NULL_VOID(monthNode);
    CHECK_NULL_VOID(dayNode);
    if (tag == yearNode) {
        HandleYearChange(isAdd, index, resultTags);
        return;
    }

    if (tag == monthNode) {
        HandleMonthChange(isAdd, index, resultTags);
        return;
    }

    if (tag == dayNode) {
        HandleDayChange(isAdd, index, resultTags);
        return;
    }
    LOGE("unknown tag[%{private}d] of column.", tag->GetId());
}

void DatePickerPattern::HandleMonthDaysChange(
    const RefPtr<FrameNode>& tag, bool isAdd, uint32_t index, std::vector<RefPtr<FrameNode>>& resultTags)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto children = host->GetChildren();
    if (children.size() <= SINGLE_CHILD_SIZE) {
        return;
    }
    auto iter = children.begin();
    auto monthDays = (*iter);
    CHECK_NULL_VOID(monthDays);

    auto stackMonthDays = DynamicCast<FrameNode>(monthDays);
    auto monthDaysNode = DynamicCast<FrameNode>(stackMonthDays->GetChildAtIndex(1));
    if (tag != monthDaysNode) {
        LOGE("unknown tag[%{private}d] of column.", tag->GetId());
        return;
    }

    if (IsShowLunar()) {
        HandleLunarMonthDaysChange(isAdd, index);
    } else {
        HandleSolarMonthDaysChange(isAdd, index);
    }

    resultTags.emplace_back(monthDaysNode);
}

void DatePickerPattern::HandleDayChange(bool isAdd, uint32_t index, std::vector<RefPtr<FrameNode>>& resultTags)
{
    auto allChildNode = GetAllChildNode();
    auto yearNode = allChildNode["year"];
    auto monthNode = allChildNode["month"];
    auto dayNode = allChildNode["day"];
    CHECK_NULL_VOID(yearNode);
    CHECK_NULL_VOID(monthNode);
    CHECK_NULL_VOID(dayNode);
    if (IsShowLunar()) {
        HandleLunarDayChange(isAdd, index);
    } else {
        HandleSolarDayChange(isAdd, index);
    }
    resultTags.emplace_back(yearNode);
    resultTags.emplace_back(monthNode);
    resultTags.emplace_back(dayNode);
}

void DatePickerPattern::HandleSolarDayChange(bool isAdd, uint32_t index)
{
    auto allChildNode = GetAllChildNode();
    auto yearNode = allChildNode["year"];
    auto monthNode = allChildNode["month"];
    auto dayNode = allChildNode["day"];

    CHECK_NULL_VOID(yearNode);
    CHECK_NULL_VOID(monthNode);
    CHECK_NULL_VOID(dayNode);
    auto yearDatePickerColumnPattern = yearNode->GetPattern<DatePickerColumnPattern>();
    auto monthDatePickerColumnPattern = monthNode->GetPattern<DatePickerColumnPattern>();
    auto dayDatePickerColumnPattern = dayNode->GetPattern<DatePickerColumnPattern>();
    if (!yearDatePickerColumnPattern || !monthDatePickerColumnPattern || !dayDatePickerColumnPattern) {
        LOGE("year or month or day column pattern is null.");
        return;
    }

    auto date = GetCurrentDate();
    if (isAdd && index == 0) {
        date.SetMonth(date.GetMonth() + 1);   // add to next month
        if (date.GetMonth() > 12) {           // invalidate month, max month is 12
            date.SetMonth(1);                 // first month is 1
            date.SetYear(date.GetYear() + 1); // add to next year
            if (date.GetYear() > endDateSolar_.GetYear()) {
                date.SetYear(startDateSolar_.GetYear());
            }
        }
    }
    if (!isAdd &&
        dayDatePickerColumnPattern->GetCurrentIndex() == GetOptionCount(dayNode) - 1) { // last index is count - 1
        date.SetMonth(date.GetMonth() - 1);                                             // reduce to previous month
        if (date.GetMonth() == 0) {                                                     // min month is 1, invalidate
            date.SetMonth(12);                                                          // set to be the last month
            date.SetYear(date.GetYear() - 1);                                           // reduce to previous year
            if (date.GetYear() < startDateSolar_.GetYear()) {
                date.SetYear(endDateSolar_.GetYear());
            }
        }
        date.SetDay(PickerDate::GetMaxDay(date.GetYear(), date.GetMonth())); // reduce to previous month's last day
    }
    uint32_t maxDay = PickerDate::GetMaxDay(date.GetYear(), date.GetMonth());
    if (date.GetDay() > maxDay) {
        date.SetDay(maxDay);
    }
    AdjustSolarDate(date);
    SolarColumnsBuilding(date);
}

void DatePickerPattern::HandleLunarDayChange(bool isAdd, uint32_t index)
{
    if (isAdd) {
        HandleAddLunarDayChange(index);
    } else {
        HandleReduceLunarDayChange(index);
    }
}

void DatePickerPattern::HandleReduceLunarDayChange(uint32_t index)
{
    auto allChildNode = GetAllChildNode();
    auto yearNode = allChildNode["year"];
    auto monthNode = allChildNode["month"];
    auto dayNode = allChildNode["day"];

    CHECK_NULL_VOID(yearNode);
    CHECK_NULL_VOID(monthNode);
    CHECK_NULL_VOID(dayNode);

    auto yearDatePickerColumnPattern = yearNode->GetPattern<DatePickerColumnPattern>();
    auto monthDatePickerColumnPattern = monthNode->GetPattern<DatePickerColumnPattern>();
    auto dayDatePickerColumnPattern = dayNode->GetPattern<DatePickerColumnPattern>();

    uint32_t nowLunarYear = startDateLunar_.year + yearDatePickerColumnPattern->GetCurrentIndex();
    auto lunarDate = GetCurrentLunarDate(nowLunarYear);
    uint32_t lunarLeapMonth = 0;
    bool hasLeapMonth = GetLunarLeapMonth(lunarDate.year, lunarLeapMonth);
    if (dayDatePickerColumnPattern->GetCurrentIndex() == GetOptionCount(dayNode) - 1) { // max index is count - 1
        if (monthDatePickerColumnPattern->GetCurrentIndex() == 0) {
            lunarDate.year = lunarDate.year - 1; // reduce to previous year
            if (lunarDate.year < startDateLunar_.year) {
                lunarDate.year = endDateLunar_.year;
            }
            lunarDate.month = 12; // set to be previous year's max month
            lunarDate.isLeapMonth = false;
            if (LunarCalculator::GetLunarLeapMonth(lunarDate.year) == 12) { // leap 12th month
                lunarDate.isLeapMonth = true;
            }
            lunarDate.day = GetLunarMaxDay(lunarDate.year, lunarDate.month, lunarDate.isLeapMonth);
        } else {
            if (lunarDate.isLeapMonth) {
                lunarDate.isLeapMonth = false;
            } else if (!hasLeapMonth) {
                lunarDate.month = lunarDate.month - 1;          // reduce to previous month
            } else if (lunarLeapMonth == lunarDate.month - 1) { // leap month is previous month
                lunarDate.isLeapMonth = true;
                lunarDate.month = lunarLeapMonth;
            } else {
                lunarDate.month = lunarDate.month - 1; // reduce to previous month
            }
            lunarDate.day = GetLunarMaxDay(lunarDate.year, lunarDate.month, lunarDate.isLeapMonth);
        }
    }

    AdjustLunarDate(lunarDate);
    LunarColumnsBuilding(lunarDate);
}

void DatePickerPattern::HandleAddLunarDayChange(uint32_t index)
{
    auto allChildNode = GetAllChildNode();
    auto yearNode = allChildNode["year"];
    auto monthNode = allChildNode["month"];
    auto dayNode = allChildNode["day"];

    CHECK_NULL_VOID(yearNode);
    CHECK_NULL_VOID(monthNode);
    CHECK_NULL_VOID(dayNode);

    auto yearDatePickerColumnPattern = yearNode->GetPattern<DatePickerColumnPattern>();
    auto monthDatePickerColumnPattern = monthNode->GetPattern<DatePickerColumnPattern>();
    auto dayDatePickerColumnPattern = dayNode->GetPattern<DatePickerColumnPattern>();

    uint32_t nowLunarYear = startDateLunar_.year + yearDatePickerColumnPattern->GetCurrentIndex();
    auto lunarDate = GetCurrentLunarDate(nowLunarYear);
    uint32_t lunarLeapMonth = 0;
    bool hasLeapMonth = GetLunarLeapMonth(lunarDate.year, lunarLeapMonth);
    if (index == 0) {
        if (monthDatePickerColumnPattern->GetCurrentIndex() ==
            GetOptionCount(monthNode) - 1) {     // max index is count - 1
            lunarDate.year = lunarDate.year + 1; // add to next year
            if (lunarDate.year > endDateLunar_.year) {
                lunarDate.year = startDateLunar_.year;
            }
            lunarDate.month = 1; // first month
            lunarDate.isLeapMonth = false;
        } else {
            if (lunarDate.isLeapMonth) {
                lunarDate.month = lunarDate.month + 1; // add to next month
                lunarDate.isLeapMonth = false;
            } else if (!hasLeapMonth) {
                lunarDate.month = lunarDate.month + 1; // add to next month
            } else if (lunarLeapMonth == lunarDate.month) {
                lunarDate.isLeapMonth = true;
            } else {
                lunarDate.month = lunarDate.month + 1; // add to next month
            }
        }
    }

    AdjustLunarDate(lunarDate);
    LunarColumnsBuilding(lunarDate);
}

void DatePickerPattern::HandleSolarMonthDaysChange(bool isAdd, uint32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto children = host->GetChildren();
    if (children.size() <= SINGLE_CHILD_SIZE) {
        return;
    }
    auto iter = children.begin();
    auto monthDays = (*iter);
    CHECK_NULL_VOID(monthDays);
    auto stackMonthDays = DynamicCast<FrameNode>(monthDays);
    CHECK_NULL_VOID(stackMonthDays);
    auto monthDaysNode = DynamicCast<FrameNode>(stackMonthDays->GetChildAtIndex(1));
    CHECK_NULL_VOID(monthDaysNode);
    auto monthDaysDatePickerColumnPattern = monthDaysNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(monthDaysDatePickerColumnPattern);

    auto date = GetCurrentDate();

    if (isAdd && index == 0) {
        // add to next year
        date.SetYear(date.GetYear() + 1); // add to next year
        if (date.GetYear() > endDateSolar_.GetYear()) {
            date.SetYear(startDateSolar_.GetYear());
        }
    }
    if (!isAdd &&
        monthDaysDatePickerColumnPattern->GetCurrentIndex() == GetOptionCount(monthDaysNode) - 1) {
            // reduce to previous year
            date.SetYear(date.GetYear() - 1);
            if (date.GetYear() < startDateSolar_.GetYear()) {
                date.SetYear(endDateSolar_.GetYear());
            }
            // reduce to previous year's last day
            date.SetMonth(MAX_MONTH);
            date.SetDay(PickerDate::GetMaxDay(date.GetYear(), date.GetMonth()));
        }
    uint32_t maxDay = PickerDate::GetMaxDay(date.GetYear(), date.GetMonth());
    if (date.GetDay() > maxDay) {
        date.SetDay(maxDay);
    }
    AdjustSolarDate(date);
    SolarMonthDaysColumnsBuilding(date);
}

void DatePickerPattern::HandleLunarMonthDaysChange(bool isAdd, uint32_t index)
{
    if (isAdd) {
        HandleAddLunarMonthDaysChange(index);
    } else {
        HandleReduceLunarMonthDaysChange(index);
    }
}

void DatePickerPattern::HandleAddLunarMonthDaysChange(uint32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto children = host->GetChildren();
    if (children.size() <= SINGLE_CHILD_SIZE) {
        return;
    }
    auto iter = children.begin();
    auto monthDays = (*iter);
    CHECK_NULL_VOID(monthDays);
    iter++;
    auto year = *iter;
    CHECK_NULL_VOID(year);
    auto stackMonthDays = DynamicCast<FrameNode>(monthDays);
    auto monthDaysNode = DynamicCast<FrameNode>(stackMonthDays->GetChildAtIndex(1));
    auto stackYear = DynamicCast<FrameNode>(year);
    auto yearDaysNode = DynamicCast<FrameNode>(stackYear->GetChildAtIndex(1));
    CHECK_NULL_VOID(monthDaysNode);
    CHECK_NULL_VOID(yearDaysNode);

    auto monthDaysDatePickerColumnPattern = monthDaysNode->GetPattern<DatePickerColumnPattern>();
    auto yearDatePickerColumnPattern = yearDaysNode->GetPattern<DatePickerColumnPattern>();

    uint32_t nowLunarYear = startDateLunar_.year + yearDatePickerColumnPattern->GetCurrentIndex();
    auto lunarDate = GetCurrentLunarDateByMonthDaysColumn(nowLunarYear);
    if (index == 0) {
        lunarDate.year = lunarDate.year + 1; // add to next year
        if (lunarDate.year > endDateLunar_.year) {
            lunarDate.year = startDateLunar_.year;
        }
        lunarDate.month = 1;
        lunarDate.isLeapMonth = false;
    }

    AdjustLunarDate(lunarDate);
    LunarMonthDaysColumnBuilding(lunarDate);
}

void DatePickerPattern::HandleReduceLunarMonthDaysChange(uint32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto children = host->GetChildren();
    if (children.size() <= SINGLE_CHILD_SIZE) {
        return;
    }
    auto iter = children.begin();
    auto monthDays = (*iter);
    CHECK_NULL_VOID(monthDays);
    iter++;
    auto year = *iter;
    CHECK_NULL_VOID(year);
    auto stackMonthDays = DynamicCast<FrameNode>(monthDays);
    auto monthDaysNode = DynamicCast<FrameNode>(stackMonthDays->GetChildAtIndex(1));
    auto stackYear = DynamicCast<FrameNode>(year);
    auto yearDaysNode = DynamicCast<FrameNode>(stackYear->GetChildAtIndex(1));
    CHECK_NULL_VOID(monthDaysNode);
    CHECK_NULL_VOID(yearDaysNode);

    auto monthDaysDatePickerColumnPattern = monthDaysNode->GetPattern<DatePickerColumnPattern>();
    auto yearDatePickerColumnPattern = yearDaysNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(monthDaysDatePickerColumnPattern);
    CHECK_NULL_VOID(yearDatePickerColumnPattern);

    uint32_t nowLunarYear = startDateLunar_.year + yearDatePickerColumnPattern->GetCurrentIndex();
    auto lunarDate = GetCurrentLunarDateByMonthDaysColumn(nowLunarYear);
    if (monthDaysDatePickerColumnPattern->GetCurrentIndex() == GetOptionCount(monthDaysNode) - 1) {
        lunarDate.year = lunarDate.year - 1; // reduce to previous year
        if (lunarDate.year < startDateLunar_.year) {
            lunarDate.year = endDateLunar_.year;
        }
        lunarDate.month = MAX_MONTH; // set to be previous year's max month
        lunarDate.isLeapMonth = false;
        if (LunarCalculator::GetLunarLeapMonth(lunarDate.year) == 12) { // leap 12th month
            lunarDate.isLeapMonth = true;
        }
        lunarDate.day = GetLunarMaxDay(lunarDate.year, lunarDate.month, lunarDate.isLeapMonth);
    }

    AdjustLunarDate(lunarDate);
    LunarMonthDaysColumnBuilding(lunarDate);
}

void DatePickerPattern::HandleYearChange(bool isAdd, uint32_t index, std::vector<RefPtr<FrameNode>>& resultTags)
{
    auto allChildNode = GetAllChildNode();
    auto yearNode = allChildNode["year"];
    auto monthNode = allChildNode["month"];
    auto dayNode = allChildNode["day"];

    CHECK_NULL_VOID(yearNode);
    CHECK_NULL_VOID(monthNode);
    CHECK_NULL_VOID(dayNode);
    if (IsShowLunar()) {
        HandleLunarYearChange(isAdd, index);
    } else {
        HandleSolarYearChange(isAdd, index);
    }
    resultTags.emplace_back(yearNode);
    resultTags.emplace_back(monthNode);
    resultTags.emplace_back(dayNode);
}

void DatePickerPattern::HandleMonthChange(bool isAdd, uint32_t index, std::vector<RefPtr<FrameNode>>& resultTags)
{
    auto allChildNode = GetAllChildNode();
    auto yearNode = allChildNode["year"];
    auto monthNode = allChildNode["month"];
    auto dayNode = allChildNode["day"];

    CHECK_NULL_VOID(yearNode);
    CHECK_NULL_VOID(monthNode);
    CHECK_NULL_VOID(dayNode);
    if (IsShowLunar()) {
        HandleLunarMonthChange(isAdd, index);
    } else {
        HandleSolarMonthChange(isAdd, index);
    }
    resultTags.emplace_back(yearNode);
    resultTags.emplace_back(monthNode);
    resultTags.emplace_back(dayNode);
}

void DatePickerPattern::HandleSolarMonthChange(bool isAdd, uint32_t index)
{
    auto date = GetCurrentDate();
    if (isAdd && date.GetMonth() == 1) {  // first month is 1
        date.SetYear(date.GetYear() + 1); // add 1 year, the next year
        if (date.GetYear() > endDateSolar_.GetYear()) {
            date.SetYear(startDateSolar_.GetYear());
        }
    }
    if (!isAdd && date.GetMonth() == 12) { // the last month is 12
        date.SetYear(date.GetYear() - 1);  // reduce 1 year, the previous year
        if (date.GetYear() < startDateSolar_.GetYear()) {
            date.SetYear(endDateSolar_.GetYear());
        }
    }
    uint32_t maxDay = PickerDate::GetMaxDay(date.GetYear(), date.GetMonth());
    if (date.GetDay() > maxDay) {
        date.SetDay(maxDay);
    }
    AdjustSolarDate(date);
    SolarColumnsBuilding(date);
}

void DatePickerPattern::HandleLunarMonthChange(bool isAdd, uint32_t index)
{
    auto allChildNode = GetAllChildNode();
    auto yearNode = allChildNode["year"];
    auto monthNode = allChildNode["month"];
    auto dayNode = allChildNode["day"];

    CHECK_NULL_VOID(yearNode);
    CHECK_NULL_VOID(monthNode);
    CHECK_NULL_VOID(dayNode);

    auto yearColumn = yearNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(yearColumn);
    uint32_t nowLunarYear = startDateLunar_.year + yearColumn->GetCurrentIndex();
    auto lunarDate = GetCurrentLunarDate(nowLunarYear);
    if (isAdd && index == 0) {
        lunarDate.year = lunarDate.year + 1; // add to next year
        if (lunarDate.year > endDateLunar_.year) {
            lunarDate.year = startDateLunar_.year;
        }
    }
    if (!isAdd && index == GetOptionCount(monthNode) - 1) {
        lunarDate.year = lunarDate.year - 1; // reduce to previous year
        if (lunarDate.year < startDateLunar_.year) {
            lunarDate.year = endDateLunar_.year;
        }
    }
    uint32_t lunarLeapMonth = 0;
    bool hasLeapMonth = GetLunarLeapMonth(lunarDate.year, lunarLeapMonth);
    if (!hasLeapMonth && lunarDate.isLeapMonth) {
        lunarDate.isLeapMonth = false;
    }
    uint32_t maxDay = GetLunarMaxDay(lunarDate.year, lunarDate.month, lunarDate.isLeapMonth);
    if (lunarDate.day > maxDay) {
        lunarDate.day = maxDay;
    }

    AdjustLunarDate(lunarDate);
    LunarColumnsBuilding(lunarDate);
}

void DatePickerPattern::HandleLunarYearChange(bool isAdd, uint32_t index)
{
    auto allChildNode = GetAllChildNode();
    auto yearNode = allChildNode["year"];
    CHECK_NULL_VOID(yearNode);
    auto yearColumn = DynamicCast<FrameNode>(yearNode);
    uint32_t lastYearIndex = index;
    auto optionCount = GetOptionCount(yearColumn);
    if (isAdd) { // need reduce one index
        lastYearIndex = optionCount != 0 ? (GetOptionCount(yearColumn) + lastYearIndex - 1) % optionCount : 0;
    } else { // need add one index
        lastYearIndex = optionCount != 0 ? (GetOptionCount(yearColumn) + lastYearIndex + 1) % optionCount : 0;
    }
    uint32_t lastLunarYear = startDateLunar_.year + lastYearIndex;
    auto lunarDate = GetCurrentLunarDate(lastLunarYear);
    uint32_t nowLeapMonth = 0;
    bool hasLeapMonth = GetLunarLeapMonth(lunarDate.year, nowLeapMonth);
    if (!hasLeapMonth && lunarDate.isLeapMonth) {
        lunarDate.isLeapMonth = false;
    }
    uint32_t nowMaxDay = GetLunarMaxDay(lunarDate.year, lunarDate.month, lunarDate.isLeapMonth);
    if (lunarDate.day > nowMaxDay) {
        lunarDate.day = nowMaxDay;
    }

    AdjustLunarDate(lunarDate);
    LunarColumnsBuilding(lunarDate);
}

LunarDate DatePickerPattern::GetCurrentLunarDate(uint32_t lunarYear) const
{
    LunarDate lunarResult;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, lunarResult);
    auto children = host->GetChildren();
    auto iter = children.begin();
    auto year = (*iter);
    CHECK_NULL_RETURN(year, lunarResult);
    std::advance(iter, 1);
    auto month = *iter;
    CHECK_NULL_RETURN(month, lunarResult);
    std::advance(iter, 1);
    auto day = *iter;
    CHECK_NULL_RETURN(day, lunarResult);

    auto stackYear = DynamicCast<FrameNode>(year);
    auto yearColumn = DynamicCast<FrameNode>(stackYear->GetChildAtIndex(1));
    auto stackMonth = DynamicCast<FrameNode>(month);
    auto monthColumn = DynamicCast<FrameNode>(stackMonth->GetChildAtIndex(1));
    auto stackDay = DynamicCast<FrameNode>(day);
    auto dayColumn = DynamicCast<FrameNode>(stackDay->GetChildAtIndex(1));
    CHECK_NULL_RETURN_NOLOG(yearColumn, lunarResult);
    CHECK_NULL_RETURN_NOLOG(monthColumn, lunarResult);
    CHECK_NULL_RETURN_NOLOG(dayColumn, lunarResult);

    auto yearDatePickerColumnPattern = yearColumn->GetPattern<DatePickerColumnPattern>();
    auto monthDatePickerColumnPattern = monthColumn->GetPattern<DatePickerColumnPattern>();
    auto dayDatePickerColumnPattern = dayColumn->GetPattern<DatePickerColumnPattern>();

    if (!yearDatePickerColumnPattern || !monthDatePickerColumnPattern || !dayDatePickerColumnPattern) {
        LOGE("year or month or day pattern is null.");
        return lunarResult;
    }

    uint32_t lunarLeapMonth = 0;
    bool hasLeapMonth = GetLunarLeapMonth(lunarYear, lunarLeapMonth);
    lunarResult.isLeapMonth = false;
    if (!hasLeapMonth) {
        lunarResult.month =
            monthDatePickerColumnPattern->GetCurrentIndex() + 1; // month from 1 to 12, index from 0 to 11
    } else {
        if (monthDatePickerColumnPattern->GetCurrentIndex() == lunarLeapMonth) {
            lunarResult.isLeapMonth = true;
            lunarResult.month = lunarLeapMonth;
        } else if (monthDatePickerColumnPattern->GetCurrentIndex() < lunarLeapMonth) {
            lunarResult.month =
                monthDatePickerColumnPattern->GetCurrentIndex() + 1; // month start from 1, index start from 0
        } else {
            lunarResult.month = monthDatePickerColumnPattern->GetCurrentIndex();
        }
    }
    lunarResult.year = startDateLunar_.year + yearDatePickerColumnPattern->GetCurrentIndex();
    lunarResult.day = dayDatePickerColumnPattern->GetCurrentIndex() + 1; // day start form 1, index start from 0
    return lunarResult;
}

void DatePickerPattern::HandleSolarYearChange(bool isAdd, uint32_t index)
{
    auto date = GetCurrentDate();
    bool leapYear = PickerDate::IsLeapYear(date.GetYear());

    if (date.GetMonth() == 2 && !leapYear && date.GetDay() > 28) { // invalidate of 2th month
        date.SetDay(28); // the max day of the 2th month of none leap year is 28
    }

    AdjustSolarDate(date);
    SolarColumnsBuilding(date);
}

PickerDate DatePickerPattern::GetCurrentDate() const
{
    if (ShowMonthDays()) {
        return GetCurrentDateByMonthDaysColumn();
    } else {
        return GetCurrentDateByYearMonthDayColumn();
    }
}

PickerDate DatePickerPattern::GetCurrentDateByYearMonthDayColumn() const
{
    PickerDate currentDate;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, currentDate);
    auto children = host->GetChildren();
    if (children.size() != CHILD_SIZE) {
        return currentDate;
    }
    auto iter = children.begin();
    auto year = (*iter);
    CHECK_NULL_RETURN(year, currentDate);
    iter++;
    auto month = *iter;
    CHECK_NULL_RETURN(month, currentDate);
    iter++;
    auto day = *iter;
    CHECK_NULL_RETURN(day, currentDate);

    auto stackYear = DynamicCast<FrameNode>(year);
    auto yearColumn = DynamicCast<FrameNode>(stackYear->GetChildAtIndex(1));
    auto stackMonth = DynamicCast<FrameNode>(month);
    auto monthColumn = DynamicCast<FrameNode>(stackMonth->GetChildAtIndex(1));
    auto stackDay = DynamicCast<FrameNode>(day);
    auto dayColumn = DynamicCast<FrameNode>(stackDay->GetChildAtIndex(1));
    CHECK_NULL_RETURN_NOLOG(yearColumn, currentDate);
    CHECK_NULL_RETURN_NOLOG(monthColumn, currentDate);
    CHECK_NULL_RETURN_NOLOG(dayColumn, currentDate);
    auto yearDatePickerColumnPattern = yearColumn->GetPattern<DatePickerColumnPattern>();
    auto monthDatePickerColumnPattern = monthColumn->GetPattern<DatePickerColumnPattern>();
    auto dayDatePickerColumnPattern = dayColumn->GetPattern<DatePickerColumnPattern>();

    if (!yearDatePickerColumnPattern || !monthDatePickerColumnPattern || !dayDatePickerColumnPattern) {
        LOGE("year or month or day pattern is null.");
        return currentDate;
    }
    if (!IsShowLunar()) {
        currentDate.SetYear(startDateSolar_.GetYear() + yearDatePickerColumnPattern->GetCurrentIndex());
        currentDate.SetMonth(
            monthDatePickerColumnPattern->GetCurrentIndex() + 1); // month from 1 to 12, index from 0 to 11.
        currentDate.SetDay(dayDatePickerColumnPattern->GetCurrentIndex() + 1); // day from 1 to 31, index from 0 to 30.
        return currentDate;
    }

    uint32_t lunarYear = startDateLunar_.year + yearDatePickerColumnPattern->GetCurrentIndex();
    return LunarToSolar(GetCurrentLunarDate(lunarYear));
}

PickerDate DatePickerPattern::GetCurrentDateByMonthDaysColumn() const
{
    PickerDate currentDate;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, currentDate);

    auto children = host->GetChildren();
    if (children.size() <= SINGLE_CHILD_SIZE) {
        return currentDate;
    }
    auto iter = children.begin();
    auto monthDays = (*iter);
    CHECK_NULL_RETURN(monthDays, currentDate);
    iter++;
    auto year = *iter;
    CHECK_NULL_RETURN(year, currentDate);
    auto stackMonthDays = DynamicCast<FrameNode>(monthDays);
    auto monthDaysNode = DynamicCast<FrameNode>(stackMonthDays->GetChildAtIndex(1));
    auto stackYear = DynamicCast<FrameNode>(year);
    auto yearDaysNode = DynamicCast<FrameNode>(stackYear->GetChildAtIndex(1));
    CHECK_NULL_RETURN_NOLOG(monthDaysNode, currentDate);
    CHECK_NULL_RETURN_NOLOG(yearDaysNode, currentDate);

    auto monthDaysDatePickerColumnPattern = monthDaysNode->GetPattern<DatePickerColumnPattern>();
    auto yearDatePickerColumnPattern = yearDaysNode->GetPattern<DatePickerColumnPattern>();
    if (!yearDatePickerColumnPattern || !monthDaysDatePickerColumnPattern) {
        LOGE("year or monthDays pattern is null.");
        return currentDate;
    }

    if (!IsShowLunar()) {
        currentDate.SetYear(startDateSolar_.GetYear() + yearDatePickerColumnPattern->GetCurrentIndex());
        auto monthDaysIndex = monthDaysDatePickerColumnPattern->GetCurrentIndex();

        uint32_t month = 1;
        for (; month <= 12; ++month) { // month start from 1 to 12
            uint32_t daysInMonth = PickerDate::GetMaxDay(currentDate.GetYear(), month);
            if (monthDaysIndex < daysInMonth) {
                break;
            } else {
                monthDaysIndex -= daysInMonth;
            }
        }
        currentDate.SetMonth(month);
        currentDate.SetDay(monthDaysIndex + 1); // days is index start form 0 and day start form 1.
        return currentDate;
    }

    uint32_t lunarYear = startDateLunar_.year + yearDatePickerColumnPattern->GetCurrentIndex();
    return LunarToSolar(GetCurrentLunarDateByMonthDaysColumn(lunarYear));
}

LunarDate DatePickerPattern::GetCurrentLunarDateByMonthDaysColumn(uint32_t lunarYear) const
{
    LunarDate lunarResult;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, lunarResult);

    auto children = host->GetChildren();
    if (children.size() <= SINGLE_CHILD_SIZE) {
        return lunarResult;
    }
    auto iter = children.begin();
    auto monthDays = (*iter);
    CHECK_NULL_RETURN(monthDays, lunarResult);
    iter++;
    auto year = *iter;
    CHECK_NULL_RETURN(year, lunarResult);
    auto stackMonthDays = DynamicCast<FrameNode>(monthDays);
    auto monthDaysNode = DynamicCast<FrameNode>(stackMonthDays->GetChildAtIndex(1));
    auto stackYear = DynamicCast<FrameNode>(year);
    auto yearDaysNode = DynamicCast<FrameNode>(stackYear->GetChildAtIndex(1));
    CHECK_NULL_RETURN_NOLOG(monthDaysNode, lunarResult);
    CHECK_NULL_RETURN_NOLOG(yearDaysNode, lunarResult);

    auto monthDaysDatePickerColumnPattern = monthDaysNode->GetPattern<DatePickerColumnPattern>();
    auto yearDatePickerColumnPattern = yearDaysNode->GetPattern<DatePickerColumnPattern>();
    if (!yearDatePickerColumnPattern || !monthDaysDatePickerColumnPattern) {
        LOGE("year or month or day pattern is null.");
        return lunarResult;
    }

    uint32_t lunarLeapMonth = 0;
    bool hasLeapMonth = GetLunarLeapMonth(lunarYear, lunarLeapMonth);
    auto monthDaysIndex = monthDaysDatePickerColumnPattern->GetCurrentIndex();
    uint32_t month = 1;
    for (; month <= 12; ++month) { // month start from 1 to 12
        auto flag = hasLeapMonth && lunarLeapMonth == month;
        uint32_t daysInMonth = GetLunarMaxDay(lunarYear, month, flag && lunarResult.isLeapMonth);
        if (monthDaysIndex < daysInMonth) {
            break;
        } else {
            monthDaysIndex -= daysInMonth;
        }
        if (flag && !lunarResult.isLeapMonth) {
            --month;
            lunarResult.isLeapMonth = true;
        }
    }
    lunarResult.month = month;
    lunarResult.day = monthDaysIndex + 1; // day start form 1, index start from 0
    lunarResult.year = startDateLunar_.year + yearDatePickerColumnPattern->GetCurrentIndex();

    return lunarResult;
}

void DatePickerPattern::AdjustLunarDate(LunarDate& date)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto dataPickerRowLayoutProperty = host->GetLayoutProperty<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(dataPickerRowLayoutProperty);
    startDateLunar_ = dataPickerRowLayoutProperty->GetStartDate().value_or(SolarToLunar(startDateSolar_));
    endDateLunar_ = dataPickerRowLayoutProperty->GetEndDate().value_or(SolarToLunar(endDateSolar_));

    if (LunarDateCompare(date, startDateLunar_) < 0) {
        date = startDateLunar_;
        return;
    }
    if (LunarDateCompare(date, endDateLunar_) > 0) {
        date = endDateLunar_;
    }
}

int DatePickerPattern::LunarDateCompare(const LunarDate& left, const LunarDate& right) const
{
    static const int leftEqualRight = 0;   // means left = right
    static const int leftGreatRight = 1;   // means left > right
    static const int leftLessRight = -1;   // means left < right
    static const double addingValue = 0.5; // adding value for leap month.
    if (left.year > right.year) {
        return leftGreatRight;
    }
    if (left.year < right.year) {
        return leftLessRight;
    }
    double leftMonth = (left.isLeapMonth ? left.month + addingValue : left.month);
    double rightMonth = (right.isLeapMonth ? right.month + addingValue : right.month);
    if (GreatNotEqual(leftMonth, rightMonth)) {
        return leftGreatRight;
    }
    if (LessNotEqual(leftMonth, rightMonth)) {
        return leftLessRight;
    }
    if (left.day > right.day) {
        return leftGreatRight;
    }
    if (left.day < right.day) {
        return leftLessRight;
    }
    return leftEqualRight;
}

void DatePickerPattern::LunarColumnsBuilding(const LunarDate& current)
{
    RefPtr<FrameNode> yearColumn;
    RefPtr<FrameNode> monthColumn;
    RefPtr<FrameNode> dayColumn;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int index = 0;
    for (const auto& stackChild : host->GetChildren()) {
        CHECK_NULL_VOID(stackChild);
        auto child = stackChild->GetChildAtIndex(1);
        CHECK_NULL_VOID(child);
        if (index == 0) {
            yearColumn = GetColumn(child->GetId());
        }
        if (index == 1) {
            monthColumn = GetColumn(child->GetId());
        }
        if (index == 2) {
            dayColumn = GetColumn(child->GetId());
        }
        index++;
    }
    CHECK_NULL_VOID(yearColumn);
    CHECK_NULL_VOID(monthColumn);
    CHECK_NULL_VOID(dayColumn);

    AdjustLunarStartEndDate();
    auto startYear = startDateLunar_.year;
    auto endYear = endDateLunar_.year;
    auto startMonth = startDateLunar_.month;
    auto endMonth = endDateLunar_.month;
    auto startDay = startDateLunar_.day;
    auto endDay = endDateLunar_.day;
    uint32_t maxDay = GetLunarMaxDay(current.year, current.month, current.isLeapMonth);
    if (startYear < endYear) {
        startMonth = 1;
        endMonth = 12;
        startDay = 1;
        endDay = maxDay;
    }
    if (startYear == endYear && startMonth < endMonth) {
        startDay = 1;
        endDay = maxDay;
    }

    options_[yearColumn].clear();
    for (uint32_t index = startYear; index <= endYear; ++index) {
        if (current.year == index) {
            auto datePickerColumnPattern = yearColumn->GetPattern<DatePickerColumnPattern>();
            CHECK_NULL_VOID(datePickerColumnPattern);
            datePickerColumnPattern->SetCurrentIndex(options_[yearColumn].size());
        }
        auto yearTextValue = GetYearFormatString(index);
        options_[yearColumn].emplace_back(yearTextValue);
    }

    uint32_t lunarLeapMonth = 0;
    bool hasLeapMonth = GetLunarLeapMonth(current.year, lunarLeapMonth);
    options_[monthColumn].clear();
    if (startYear == endYear) {
        options_[monthColumn].resize(startMonth - 1, "");
    }
    // lunar's month start form startMonth to endMonth
    for (uint32_t index = startMonth; index <= endMonth; ++index) {
        if (!current.isLeapMonth && current.month == index) {
            auto datePickerColumnPattern = monthColumn->GetPattern<DatePickerColumnPattern>();
            CHECK_NULL_VOID(datePickerColumnPattern);
            datePickerColumnPattern->SetCurrentIndex(options_[monthColumn].size());
        }
        auto monthTextValue = GetMonthFormatString(index, true, false);
        options_[monthColumn].emplace_back(monthTextValue);

        if (hasLeapMonth && lunarLeapMonth == index) {
            if (current.isLeapMonth && current.month == index) {
                auto datePickerColumnPattern = monthColumn->GetPattern<DatePickerColumnPattern>();
                CHECK_NULL_VOID(datePickerColumnPattern);
                datePickerColumnPattern->SetCurrentIndex(options_[monthColumn].size());
            }
            auto monthTextValue = GetMonthFormatString(index, true, true);
            options_[monthColumn].emplace_back(monthTextValue);
        }
    }

    options_[dayColumn].clear();
    if (startYear == endYear && startMonth == endMonth) {
        options_[dayColumn].resize(startDay - 1, "");
    }
    // lunar's day start from startDay
    for (uint32_t index = startDay; index <= endDay; ++index) {
        if (current.day == index) {
            auto datePickerColumnPattern = dayColumn->GetPattern<DatePickerColumnPattern>();
            CHECK_NULL_VOID(datePickerColumnPattern);
            datePickerColumnPattern->SetCurrentIndex(options_[dayColumn].size());
        }
        auto dayTextValue = GetDayFormatString(index, true);
        options_[dayColumn].emplace_back(dayTextValue);
    }
    auto yearColumnPattern = yearColumn->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(yearColumnPattern);
    auto monthColumnPattern = monthColumn->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(monthColumnPattern);
    auto dayColumnPattern = dayColumn->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(dayColumnPattern);
    yearColumnPattern->SetOptions(GetOptions());
    monthColumnPattern->SetOptions(GetOptions());
    dayColumnPattern->SetOptions(GetOptions());

    SetShowLunar(true);
}

void DatePickerPattern::SolarColumnsBuilding(const PickerDate& current)
{
    RefPtr<FrameNode> yearColumn;
    RefPtr<FrameNode> monthColumn;
    RefPtr<FrameNode> dayColumn;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int index = 0;
    for (const auto& stackChild : host->GetChildren()) {
        CHECK_NULL_VOID(stackChild);
        auto child = stackChild->GetChildAtIndex(1);
        if (index == 0) {
            yearColumn = GetColumn(child->GetId());
        }
        if (index == 1) {
            monthColumn = GetColumn(child->GetId());
        }
        if (index == 2) {
            dayColumn = GetColumn(child->GetId());
        }
        index++;
    }
    CHECK_NULL_VOID(yearColumn);
    CHECK_NULL_VOID(monthColumn);
    CHECK_NULL_VOID(dayColumn);

    AdjustSolarStartEndDate();
    auto startYear = startDateSolar_.GetYear();
    auto endYear = endDateSolar_.GetYear();
    auto startMonth = startDateSolar_.GetMonth();
    auto endMonth = endDateSolar_.GetMonth();
    auto startDay = startDateSolar_.GetDay();
    auto endDay = endDateSolar_.GetDay();

    uint32_t maxDay = PickerDate::GetMaxDay(current.GetYear(), current.GetMonth());
    if (startYear < endYear) {
        startMonth = 1;
        endMonth = 12;
        startDay = 1;
        endDay = maxDay;
    }
    if (startYear == endYear && startMonth < endMonth) {
        startDay = 1;
        endDay = maxDay;
    }

    options_[yearColumn].clear();
    for (uint32_t year = startYear; year <= endYear; ++year) {
        if (year == current.GetYear()) {
            auto datePickerColumnPattern = yearColumn->GetPattern<DatePickerColumnPattern>();
            CHECK_NULL_VOID(datePickerColumnPattern);
            datePickerColumnPattern->SetCurrentIndex(options_[yearColumn].size());
        }
        auto yearTextValue = GetYearFormatString(year);
        options_[yearColumn].emplace_back(yearTextValue);
    }

    options_[monthColumn].clear();
    if (startYear == endYear) {
        options_[monthColumn].resize(startMonth - 1, "");
    }
    // solar's month start form 1 to 12
    for (uint32_t month = startMonth; month <= endMonth; month++) {
        if (month == current.GetMonth()) {
            auto datePickerColumnPattern = monthColumn->GetPattern<DatePickerColumnPattern>();
            CHECK_NULL_VOID(datePickerColumnPattern);
            // back index = size - 1
            datePickerColumnPattern->SetCurrentIndex(options_[monthColumn].size());
        }

        auto monthTextValue = GetMonthFormatString(month, false, false);
        options_[monthColumn].emplace_back(monthTextValue);
    }

    options_[dayColumn].clear();
    if (startYear == endYear && startMonth == endMonth) {
        options_[dayColumn].resize(startDay - 1, "");
    }
    // solar's day start from 1
    for (uint32_t day = startDay; day <= endDay; day++) {
        if (day == current.GetDay()) {
            auto datePickerColumnPattern = dayColumn->GetPattern<DatePickerColumnPattern>();
            CHECK_NULL_VOID(datePickerColumnPattern);
            datePickerColumnPattern->SetCurrentIndex(options_[dayColumn].size());
        }
        auto dayTextValue = GetDayFormatString(day, false);
        options_[dayColumn].emplace_back(dayTextValue);
    }

    auto yearColumnPattern = yearColumn->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(yearColumnPattern);
    auto monthColumnPattern = monthColumn->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(monthColumnPattern);
    auto dayColumnPattern = dayColumn->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(dayColumnPattern);
    yearColumnPattern->SetOptions(GetOptions());
    monthColumnPattern->SetOptions(GetOptions());
    dayColumnPattern->SetOptions(GetOptions());

    SetShowLunar(false);
}

void DatePickerPattern::LunarMonthDaysColumnBuilding(const LunarDate& current)
{
    RefPtr<FrameNode> monthDaysColumn;
    RefPtr<FrameNode> yearColumn;
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto children = host->GetChildren();
    if (children.size() <= SINGLE_CHILD_SIZE) {
        return;
    }

    auto iter = children.begin();
    auto monthDays = (*iter);
    CHECK_NULL_VOID(monthDays);
    iter++;
    auto year = *iter;
    CHECK_NULL_VOID(year);
    auto stackMonthDays = DynamicCast<FrameNode>(monthDays);
    auto monthDaysNode = DynamicCast<FrameNode>(stackMonthDays->GetChildAtIndex(1));
    auto stackYear = DynamicCast<FrameNode>(year);
    auto yearDaysNode = DynamicCast<FrameNode>(stackYear->GetChildAtIndex(1));
    CHECK_NULL_VOID(monthDaysNode);
    CHECK_NULL_VOID(yearDaysNode);

    monthDaysColumn = GetColumn(monthDaysNode->GetId());
    yearColumn = GetColumn(yearDaysNode->GetId());
    CHECK_NULL_VOID(monthDaysColumn);
    CHECK_NULL_VOID(yearColumn);

    AdjustLunarStartEndDate();

    auto startYear = startDateLunar_.year;
    auto endYear = endDateLunar_.year;

    options_[yearColumn].clear();
    for (uint32_t index = startYear; index <= endYear; ++index) {
        if (current.year == index) {
            auto datePickerColumnPattern = yearColumn->GetPattern<DatePickerColumnPattern>();
            CHECK_NULL_VOID(datePickerColumnPattern);
            datePickerColumnPattern->SetCurrentIndex(options_[yearColumn].size());
        }
        auto yearTextValue = GetYearFormatString(index);
        options_[yearColumn].emplace_back(yearTextValue);
    }

    FillLunarMonthDaysOptions(current, monthDaysColumn);

    auto yearColumnPattern = yearColumn->GetPattern<DatePickerColumnPattern>();
    auto monthDaysColumnPattern = monthDaysColumn->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(yearColumnPattern);
    CHECK_NULL_VOID(monthDaysColumnPattern);
    yearColumnPattern->SetOptions(GetOptions());
    monthDaysColumnPattern->SetOptions(GetOptions());

    SetShowLunar(true);
}

void DatePickerPattern::SolarMonthDaysColumnsBuilding(const PickerDate& current)
{
    RefPtr<FrameNode> monthDaysColumn;
    RefPtr<FrameNode> yearColumn;
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto children = host->GetChildren();
    if (children.size() <= SINGLE_CHILD_SIZE) {
        return;
    }
    auto iter = children.begin();
    auto monthDays = (*iter);
    CHECK_NULL_VOID(monthDays);
    iter++;
    auto year = *iter;
    CHECK_NULL_VOID(year);
    auto stackMonthDays = DynamicCast<FrameNode>(monthDays);
    auto monthDaysNode = DynamicCast<FrameNode>(stackMonthDays->GetChildAtIndex(1));
    auto stackYear = DynamicCast<FrameNode>(year);
    auto yearDaysNode = DynamicCast<FrameNode>(stackYear->GetChildAtIndex(1));
    monthDaysColumn = GetColumn(monthDaysNode->GetId());
    yearColumn = GetColumn(yearDaysNode->GetId());
    CHECK_NULL_VOID(monthDaysColumn);
    CHECK_NULL_VOID(yearColumn);

    AdjustSolarStartEndDate();
    FillSolarYearOptions(current, yearColumn);

    options_[monthDaysColumn].clear();
    for (uint32_t index = MIN_MONTH; index <= MAX_MONTH; ++index) {
        uint32_t maxDay = PickerDate::GetMaxDay(current.GetYear(), index);
        auto monthTextValue = GetMonthFormatString(index, false, false);
        for (uint32_t dayIndex = MIN_DAY; dayIndex <= maxDay; ++dayIndex) {
            if (index == current.GetMonth() && dayIndex == current.GetDay()) {
                auto datePickerColumnPattern = monthDaysColumn->GetPattern<DatePickerColumnPattern>();
                CHECK_NULL_VOID(datePickerColumnPattern);
                datePickerColumnPattern->SetCurrentIndex(options_[monthDaysColumn].size());
            }
            auto dayTextValue = GetDayFormatString(dayIndex, false);
            options_[monthDaysColumn].emplace_back(monthTextValue + dayTextValue);
        }
    }

    auto yearColumnPattern = yearColumn->GetPattern<DatePickerColumnPattern>();
    auto monthDaysColumnPattern = monthDaysColumn->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(yearColumnPattern);
    CHECK_NULL_VOID(monthDaysColumnPattern);
    yearColumnPattern->SetOptions(GetOptions());
    monthDaysColumnPattern->SetOptions(GetOptions());

    SetShowLunar(false);
}

void DatePickerPattern::FillSolarYearOptions(const PickerDate& current, RefPtr<FrameNode>& yearColumn)
{
    options_[yearColumn].clear();
    for (uint32_t year = startDateSolar_.GetYear(); year <= endDateSolar_.GetYear(); ++year) {
        if (year == current.GetYear()) {
            auto datePickerColumnPattern = yearColumn->GetPattern<DatePickerColumnPattern>();
            CHECK_NULL_VOID(datePickerColumnPattern);
            datePickerColumnPattern->SetCurrentIndex(options_[yearColumn].size());
        }
        auto yearTextValue = GetYearFormatString(year);
        options_[yearColumn].emplace_back(yearTextValue);
    }
}

void DatePickerPattern::FillLunarMonthDaysOptions(const LunarDate& current, RefPtr<FrameNode>& monthDaysColumn)
{
    uint32_t startMonth = 1;
    uint32_t endMonth = 12;
    uint32_t startDay = 1;

    uint32_t lunarLeapMonth = 0;
    bool hasLeapMonth = GetLunarLeapMonth(current.year, lunarLeapMonth);
    options_[monthDaysColumn].clear();

    for (uint32_t index = startMonth; index <= endMonth; ++index) {
        uint32_t maxDay = GetLunarMaxDay(current.year, index, false);
        auto monthTextValue = GetMonthFormatString(index, true, false);
        for (uint32_t dayIndex = startDay; dayIndex <= maxDay; ++dayIndex) {
            if (!current.isLeapMonth && current.month == index && current.day == dayIndex) {
                auto datePickerColumnPattern = monthDaysColumn->GetPattern<DatePickerColumnPattern>();
                CHECK_NULL_VOID(datePickerColumnPattern);
                datePickerColumnPattern->SetCurrentIndex(options_[monthDaysColumn].size());
            }
            auto dayTextValue = GetDayFormatString(dayIndex, true);
            options_[monthDaysColumn].emplace_back(monthTextValue + dayTextValue);
        }

        if (!hasLeapMonth || lunarLeapMonth != index) {
            continue;
        }

        maxDay = GetLunarMaxDay(current.year, index, true);
        monthTextValue = GetMonthFormatString(index, true, true);
        for (uint32_t dayIndex = startDay; dayIndex <= maxDay; ++dayIndex) {
            if (current.isLeapMonth && current.month == index && current.day == dayIndex) {
                auto datePickerColumnPattern = monthDaysColumn->GetPattern<DatePickerColumnPattern>();
                CHECK_NULL_VOID(datePickerColumnPattern);
                datePickerColumnPattern->SetCurrentIndex(options_[monthDaysColumn].size());
            }
            auto dayTextValue = GetDayFormatString(dayIndex, true);
            options_[monthDaysColumn].emplace_back(monthTextValue + dayTextValue);
        }
    }
}

void DatePickerPattern::AdjustSolarStartEndDate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto dataPickerRowLayoutProperty = host->GetLayoutProperty<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(dataPickerRowLayoutProperty);
    startDateSolar_ = LunarToSolar(dataPickerRowLayoutProperty->GetStartDate().value_or(SolarToLunar(startDateSolar_)));
    endDateSolar_ = LunarToSolar(dataPickerRowLayoutProperty->GetEndDate().value_or(SolarToLunar(endDateSolar_)));

    if (startDateSolar_.GetYear() > endDateSolar_.GetYear()) {
        startDateSolar_ = startDefaultDateSolar_;
        endDateSolar_ = endDefaultDateSolar_;
    }
    if (startDateSolar_.GetYear() == endDateSolar_.GetYear() && startDateSolar_.GetMonth() > endDateSolar_.GetMonth()) {
        startDateSolar_ = startDefaultDateSolar_;
        endDateSolar_ = endDefaultDateSolar_;
    }
    if (startDateSolar_.GetYear() == endDateSolar_.GetYear() &&
        startDateSolar_.GetMonth() == endDateSolar_.GetMonth() && startDateSolar_.GetDay() > endDateSolar_.GetDay()) {
        startDateSolar_ = startDefaultDateSolar_;
        endDateSolar_ = endDefaultDateSolar_;
    }
}

void DatePickerPattern::AdjustLunarStartEndDate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto dataPickerRowLayoutProperty = host->GetLayoutProperty<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(dataPickerRowLayoutProperty);
    startDateLunar_ = dataPickerRowLayoutProperty->GetStartDate().value_or(SolarToLunar(startDateSolar_));
    endDateLunar_ = dataPickerRowLayoutProperty->GetEndDate().value_or(SolarToLunar(endDateSolar_));

    if (GetStartDateLunar().year > GetEndDateLunar().year) {
        startDateLunar_ = SolarToLunar(startDefaultDateSolar_);
        endDateLunar_ = SolarToLunar(endDefaultDateSolar_);
    }
    if (GetStartDateLunar().year == GetEndDateLunar().year && GetStartDateLunar().month > GetEndDateLunar().month) {
        startDateLunar_ = SolarToLunar(startDefaultDateSolar_);
        endDateLunar_ = SolarToLunar(endDefaultDateSolar_);
    }
    if (GetStartDateLunar().year == GetEndDateLunar().year && GetStartDateLunar().month == GetEndDateLunar().month &&
        GetStartDateLunar().day > GetEndDateLunar().day) {
        startDateLunar_ = SolarToLunar(startDefaultDateSolar_);
        endDateLunar_ = SolarToLunar(endDefaultDateSolar_);
    }
}

bool DatePickerPattern::GetLunarLeapMonth(uint32_t year, uint32_t& outLeapMonth) const
{
    auto leapMonth = LunarCalculator::GetLunarLeapMonth(year);
    if (leapMonth <= 0) {
        return false;
    }

    outLeapMonth = static_cast<uint32_t>(leapMonth);
    return true;
}

uint32_t DatePickerPattern::GetLunarMaxDay(uint32_t year, uint32_t month, bool isLeap) const
{
    if (isLeap) {
        return static_cast<uint32_t>(LunarCalculator::GetLunarLeapDays(year));
    } else {
        return static_cast<uint32_t>(LunarCalculator::GetLunarMonthDays(year, month));
    }
}

LunarDate DatePickerPattern::SolarToLunar(const PickerDate& date) const
{
    Date result;
    result.year = date.GetYear();
    result.month = date.GetMonth();
    result.day = date.GetDay();
    return Localization::GetInstance()->GetLunarDate(result);
}

PickerDate DatePickerPattern::LunarToSolar(const LunarDate& date) const
{
    uint32_t days = date.day - 1; // calculate days from 1900.1.1 to this date
    if (date.isLeapMonth) {
        days += LunarCalculator::GetLunarMonthDays(date.year, date.month);
    } else {
        uint32_t leapMonth = LunarCalculator::GetLunarLeapMonth(date.year);
        if (leapMonth < date.month) {
            days += LunarCalculator::GetLunarLeapDays(date.year);
        }
    }
    for (uint32_t month = 1; month < date.month; ++month) { // month start from 1
        days += LunarCalculator::GetLunarMonthDays(date.year, month);
    }
    for (uint32_t year = 1900; year < date.year; ++year) { // year start from 1900
        days += LunarCalculator::GetLunarYearDays(year);
    }
    days += 30; // days from solar's 1900.1.1 to lunar's 1900.1.1 is 30
    PickerDate result;
    result.FromDays(days);
    return result;
}

void DatePickerPattern::Init()
{
    CHECK_NULL_VOID_NOLOG(!inited_);
    years_.resize(201);      // year from 1900 to 2100,count is 201
    solarMonths_.resize(12); // solar month from 1 to 12,count is 12
    solarDays_.resize(31);   // solar day from 1 to 31, count is 31
    lunarMonths_.resize(24); // lunar month from 1 to 24, count is 24
    lunarDays_.resize(30);   // lunar day from 1 to 30, count is 30
    // init year from 1900 to 2100
    for (uint32_t year = 1900; year <= 2100; ++year) {
        DateTime date;
        date.year = year;
        years_[year - 1900] = Localization::GetInstance()->FormatDateTime(date, "y"); // index start from 0
    }
    // init solar month from 1 to 12
    auto months = Localization::GetInstance()->GetMonths(true);
    for (uint32_t month = 1; month <= 12; ++month) {
        if (month - 1 < months.size()) {
            solarMonths_[month - 1] = months[month - 1];
            continue;
        }
        DateTime date;
        date.month = month - 1; // W3C's month start from 0 to 11
        solarMonths_[month - 1] = Localization::GetInstance()->FormatDateTime(date, "M"); // index start from 0
    }
    // init solar day from 1 to 31
    for (uint32_t day = 1; day <= 31; ++day) {
        DateTime date;
        date.day = day;
        solarDays_[day - 1] = Localization::GetInstance()->FormatDateTime(date, "d"); // index start from 0
    }
    // init lunar month from 1 to 24 which is 1th, 2th, ... leap 1th, leap 2th ...
    for (uint32_t index = 1; index <= 24; ++index) {
        uint32_t month = (index > 12 ? index - 12 : index);
        bool isLeap = (index > 12);
        lunarMonths_[index - 1] = Localization::GetInstance()->GetLunarMonth(month, isLeap); // index start from 0
    }
    // init lunar day from 1 to 30
    for (uint32_t day = 1; day <= 30; ++day) {
        lunarDays_[day - 1] = Localization::GetInstance()->GetLunarDay(day); // index start from 0
    }
    inited_ = true;
    Localization::GetInstance()->SetOnChange([]() { inited_ = false; });
}

const std::string& DatePickerPattern::GetYear(uint32_t year)
{
    Init();
    if (!(1900 <= year && year <= 2100)) { // year in [1900,2100]
        return empty_;
    }
    return years_[year - 1900]; // index in [0, 200]
}

const std::string& DatePickerPattern::GetSolarMonth(uint32_t month)
{
    Init();
    if (!(1 <= month && month <= 12)) { // solar month in [1,12]
        return empty_;
    }
    return solarMonths_[month - 1]; // index in [0,11]
}

const std::string& DatePickerPattern::GetSolarDay(uint32_t day)
{
    Init();
    if (!(1 <= day && day <= 31)) { // solar day in [1,31]
        return empty_;
    }
    return solarDays_[day - 1]; // index in [0,30]
}

const std::string& DatePickerPattern::GetLunarMonth(uint32_t month, bool isLeap)
{
    Init();
    uint32_t index = (isLeap ? month + 12 : month); // leap month is behind 12 index
    if (!(1 <= index && index <= 24)) {             // lunar month need in [1,24]
        return empty_;
    }
    return lunarMonths_[index - 1]; // index in [0,23]
}

const std::string& DatePickerPattern::GetLunarDay(uint32_t day)
{
    Init();
    if (!(1 <= day && day <= 30)) { // lunar day need in [1,30]
        return empty_;
    }
    return lunarDays_[day - 1]; // index in [0,29]
}

void DatePickerPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    auto GetDateString = [](const PickerDate& pickerDate) {
        std::string ret;
        ret += std::to_string(pickerDate.GetYear());
        ret += "-";
        ret += std::to_string(pickerDate.GetMonth());
        ret += "-";
        ret += std::to_string(pickerDate.GetDay());
        return ret;
    };
    auto rowLayoutProperty = GetLayoutProperty<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(rowLayoutProperty);
    auto jsonConstructor = JsonUtil::Create(true);
    auto isLunar = rowLayoutProperty->GetLunarValue(false);
    if (isLunar) {
        jsonConstructor->Put("start", rowLayoutProperty->GetDateStart().c_str());
        jsonConstructor->Put("end", rowLayoutProperty->GetDateEnd().c_str());
        jsonConstructor->Put("selected", rowLayoutProperty->GetDateSelected().c_str());
    } else {
        jsonConstructor->Put("start", GetDateString(startDateSolar_).c_str());
        jsonConstructor->Put("end", GetDateString(endDateSolar_).c_str());
        jsonConstructor->Put("selected", GetDateString(selectedDate_).c_str());
    }
    json->Put("constructor", jsonConstructor);
}

} // namespace OHOS::Ace::NG
