/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#include <cstdint>

#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/time_picker/toss_animation_controller.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CHILD_WITH_AMPM_SIZE = 3;
constexpr int32_t CHILD_WITHOUT_AMPM_SIZE = 2;
constexpr uint32_t AM_PM_HOUR_12 = 12;
constexpr uint32_t AM_PM_HOUR_11 = 11;
const int32_t AM_PM_COUNT = 3;
const Dimension PRESS_INTERVAL = 4.0_vp;
const Dimension PRESS_RADIUS = 8.0_vp;
const int32_t UNOPTION_COUNT = 2;
const int32_t AMPMDEFAULTPOSITION = 0;
const int32_t AMPM_FORWARD_WITHSECOND = 3;
const int32_t AMPM_FORWARD_WITHOUTSECOND = 2;
const int32_t AMPM_BACKWARD_WITHSECOND = -3;
const int32_t AMPM_BACKWARD_WITHOUTSECOND = -2;
const int32_t CHILD_INDEX_FIRST = 0;
const int32_t CHILD_INDEX_SECOND = 1;
const int32_t CHILD_INDEX_THIRD = 2;
const int32_t CHILD_INDEX_FOURTH = 3;
constexpr float DISABLE_ALPHA = 0.6f;
const Dimension FOCUS_OFFSET = 2.0_vp;
const int32_t RATE = 2;
} // namespace

void TimePickerRowPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
    host->GetRenderContext()->UpdateClipEdge(true);
}

bool TimePickerRowPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    CHECK_NULL_RETURN(dirty, false);
    SetButtonIdeaSize();
    return true;
}

void TimePickerRowPattern::SetButtonIdeaSize()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto children = host->GetChildren();
    auto height = pickerTheme->GetDividerSpacing();
    for (const auto& child : children) {
        auto childNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(childNode);
        auto width = childNode->GetGeometryNode()->GetFrameSize().Width();
        auto defaultWidth = height.ConvertToPx() * 2;
        if (width > defaultWidth) {
            width = static_cast<float>(defaultWidth);
        }
        auto timePickerColumnNode = DynamicCast<FrameNode>(childNode->GetLastChild());
        CHECK_NULL_VOID(timePickerColumnNode);
        auto columnNodeHeight = timePickerColumnNode->GetGeometryNode()->GetFrameSize().Height();
        auto buttonNode = DynamicCast<FrameNode>(child->GetFirstChild());
        auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        buttonLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
        buttonLayoutProperty->UpdateType(ButtonType::NORMAL);
        buttonLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(PRESS_RADIUS));
        auto standardButtonHeight = static_cast<float>((height - PRESS_INTERVAL).ConvertToPx());
        auto maxButtonHeight = static_cast<float>(columnNodeHeight);
        auto buttonHeight = Dimension(std::min(standardButtonHeight, maxButtonHeight), DimensionUnit::PX);
        buttonLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(width - PRESS_INTERVAL.ConvertToPx()), CalcLength(buttonHeight)));
        auto buttonConfirmRenderContext = buttonNode->GetRenderContext();
        buttonConfirmRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        buttonNode->MarkModifyDone();
        buttonNode->MarkDirtyNode();
        if (GetIsShowInDialog() && GreatNotEqual(standardButtonHeight, maxButtonHeight) &&
            GreatNotEqual(maxButtonHeight, 0.0f)) {
            auto parentNode = DynamicCast<FrameNode>(host->GetParent());
            CHECK_NULL_VOID(parentNode);
            parentNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
        }
    }
}

void TimePickerRowPattern::ColumnPatternInitHapticController()
{
    if (!isHapticChanged_) {
        return;
    }

    isHapticChanged_ = false;
    for (auto iter = allChildNode_.begin(); iter != allChildNode_.end(); iter++) {
        auto columnNode = iter->second.Upgrade();
        if (!columnNode) {
            continue;
        }
        auto pattern = columnNode->GetPattern<TimePickerColumnPattern>();
        if (!pattern) {
            continue;
        }
        pattern->InitHapticController(columnNode);
    }
}

void TimePickerRowPattern::OnModifyDone()
{
    Pattern::CheckLocalized();
    if (isFiredTimeChange_ && !isForceUpdate_ && !isDateTimeOptionUpdate_) {
        isFiredTimeChange_ = false;
        ColumnPatternInitHapticController();
        return;
    }

    isHapticChanged_ = false;
    isForceUpdate_ = false;
    isDateTimeOptionUpdate_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pickerProperty = host->GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_VOID(pickerProperty);
    wheelModeEnabled_ = pickerProperty->GetLoopValue(true);
    UpdateLanguageAndAmPmTimeOrder();
    CreateOrDeleteSecondNode();
    CreateAmPmNode();
    OnColumnsBuilding();
    FlushColumn();
    InitDisabled();
    SetChangeCallback([weak = WeakClaim(this)](const RefPtr<FrameNode>& tag, bool add, uint32_t index, bool notify) {
        auto refPtr = weak.Upgrade();
        CHECK_NULL_VOID(refPtr);
        refPtr->HandleColumnChange(tag, add, index, notify);
    });
    SetEventCallback([weak = WeakClaim(this)](bool refresh) {
        auto refPtr = weak.Upgrade();
        CHECK_NULL_VOID(refPtr);
        refPtr->FireChangeEvent(refresh);
    });
    auto focusHub = host->GetFocusHub();
    if (focusHub) {
        InitOnKeyEvent(focusHub);
    }
    if (HasTitleNode()) {
        auto textTitleNode = FrameNode::GetOrCreateFrameNode(
            V2::TEXT_ETS_TAG, GetTitleId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        auto str = GetDialogTitleDate();
        CHECK_NULL_VOID(textTitleNode);
        auto textLayoutProperty = textTitleNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateContent(str.ToString(false));
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TimePickerRowPattern::InitDisabled()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    enabled_ = eventHub->IsEnabled();
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (!enabled_) {
        renderContext->UpdateOpacity(curOpacity_ * DISABLE_ALPHA);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TimePickerRowPattern::CreateAmPmNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto height = pickerTheme->GetDividerSpacing();
    if (!GetHour24() && !HasAmPmNode()) {
        auto amPmColumnNode = FrameNode::GetOrCreateFrameNode(
            V2::COLUMN_ETS_TAG, GetAmPmId(), []() { return AceType::MakeRefPtr<TimePickerColumnPattern>(); });
        CHECK_NULL_VOID(amPmColumnNode);
        for (uint32_t index = 0; index < AM_PM_COUNT; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_VOID(textNode);
            textNode->MountToParent(amPmColumnNode);
        }
        SetColumn(amPmColumnNode);
        auto stackAmPmNode = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<StackPattern>(); });
        auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        auto blendNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto columnBlendNode = FrameNode::GetOrCreateFrameNode(
            V2::COLUMN_ETS_TAG, blendNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        buttonNode->MountToParent(stackAmPmNode);
        auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        amPmColumnNode->MountToParent(columnBlendNode);
        columnBlendNode->MountToParent(stackAmPmNode);
        auto layoutProperty = stackAmPmNode->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        layoutProperty->UpdateLayoutWeight(1);
        amPmTimeOrder_ == "01" ? stackAmPmNode->MountToParent(host) : stackAmPmNode->MountToParent(host, 0);
        if (SetAmPmButtonIdeaSize() > 0) {
            auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
            buttonLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
            buttonLayoutProperty->UpdateType(ButtonType::NORMAL);
            buttonLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(PRESS_RADIUS));
            buttonLayoutProperty->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(SetAmPmButtonIdeaSize()), CalcLength(height - PRESS_INTERVAL)));
            buttonNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
            buttonNode->MarkModifyDone();
            buttonNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
        host->MarkModifyDone();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void TimePickerRowPattern::CreateOrDeleteSecondNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!HasSecondNode()) {
        if (hasSecond_) {
            auto secondColumnNode = FrameNode::GetOrCreateFrameNode(
                V2::COLUMN_ETS_TAG, GetSecondId(), []() { return AceType::MakeRefPtr<TimePickerColumnPattern>(); });
            CHECK_NULL_VOID(secondColumnNode);
            for (uint32_t index = 0; index < GetShowCount(); index++) {
                auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
                    ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
                CHECK_NULL_VOID(textNode);
                textNode->MarkModifyDone();
                textNode->MountToParent(secondColumnNode);
            }
            SetColumn(secondColumnNode);
            auto stackSecondNode = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<StackPattern>(); });
            auto buttonSecondNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
            auto blendNodeId = ElementRegister::GetInstance()->MakeUniqueId();
            auto columnBlendNode = FrameNode::GetOrCreateFrameNode(
                V2::COLUMN_ETS_TAG, blendNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
            buttonSecondNode->MarkModifyDone();
            buttonSecondNode->MountToParent(stackSecondNode);
            secondColumnNode->MarkModifyDone();
            secondColumnNode->MountToParent(columnBlendNode);
            columnBlendNode->MarkModifyDone();
            columnBlendNode->MountToParent(stackSecondNode);
            auto layoutProperty = stackSecondNode->GetLayoutProperty<LayoutProperty>();
            layoutProperty->UpdateAlignment(Alignment::CENTER);
            layoutProperty->UpdateLayoutWeight(1);
            stackSecondNode->MarkModifyDone();
            MountSecondNode(stackSecondNode);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    } else {
        if (!hasSecond_) {
            RemoveSecondNode();
            secondId_.reset();
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    }
}

void TimePickerRowPattern::MountSecondNode(const RefPtr<FrameNode>& stackSecondNode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int32_t secondNodePosition = static_cast<int32_t>(host->GetChildren().size()) - 1;
    if (!HasAmPmNode()) {
        if (language_ == "ug") {
            secondNodePosition = CHILD_INDEX_FIRST;
        }
    } else {
        if (amPmTimeOrder_ == "01") {
            secondNodePosition = CHILD_INDEX_THIRD;
        } else if (language_ == "ug") {
            secondNodePosition = CHILD_INDEX_SECOND;
        }
    }
    stackSecondNode->MountToParent(host, secondNodePosition);
}

void TimePickerRowPattern::RemoveSecondNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int32_t secondNodePosition = static_cast<int32_t>(host->GetChildren().size()) - 1;
    if (!HasAmPmNode()) {
        if (language_ == "ug") {
            secondNodePosition = CHILD_INDEX_FIRST;
        }
    } else {
        if (amPmTimeOrder_ == "01") {
            secondNodePosition = CHILD_INDEX_THIRD;
        } else if (language_ == "ug") {
            secondNodePosition = CHILD_INDEX_SECOND;
        }
    }
    host->RemoveChildAtIndex(secondNodePosition);
}

double TimePickerRowPattern::SetAmPmButtonIdeaSize()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0);
    auto children = host->GetChildren();
    float width = 0.0f;
    for (const auto& child : children) {
        auto buttonNode = DynamicCast<FrameNode>(child->GetFirstChild());
        CHECK_NULL_RETURN(buttonNode, 0);
        width = buttonNode->GetGeometryNode()->GetFrameSize().Width();
    }
    if (width > 0) {
        return width;
    }
    return 0;
}
void TimePickerRowPattern::SetEventCallback(EventCallback&& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    for (const auto& child : children) {
        auto stackNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(stackNode);
        auto columnBlendNode = DynamicCast<FrameNode>(stackNode->GetLastChild());
        CHECK_NULL_VOID(columnBlendNode);
        auto childNode = DynamicCast<FrameNode>(columnBlendNode->GetLastChild());
        CHECK_NULL_VOID(childNode);
        auto timePickerColumnPattern = childNode->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(timePickerColumnPattern);
        timePickerColumnPattern->SetEventCallback(std::move(value));
    }
}

void TimePickerRowPattern::FireChangeEvent(bool refresh)
{
    if (refresh) {
        auto timePickerEventHub = GetEventHub<TimePickerEventHub>();
        CHECK_NULL_VOID(timePickerEventHub);
        auto str = GetSelectedObject(true);
        auto info = std::make_shared<DatePickerChangeEvent>(str);
        timePickerEventHub->FireChangeEvent(info.get());
        timePickerEventHub->FireDialogChangeEvent(str);
        firedTimeStr_ = str;
    }
}

std::string TimePickerRowPattern::GetSelectedObject(bool isColumnChange, int32_t status)
{
    auto time = selectedTime_;
    if (isColumnChange) {
        time = GetCurrentTime();
    }
    return time.ToString(true, hasSecond_, status);
}

PickerTime TimePickerRowPattern::GetCurrentTime()
{
    PickerTime time;
    UpdateAllChildNode();
    auto amPmColumn = allChildNode_["amPm"].Upgrade();
    auto hourColumn = allChildNode_["hour"].Upgrade();
    auto minuteColumn = allChildNode_["minute"].Upgrade();
    CHECK_NULL_RETURN(hourColumn, time);
    CHECK_NULL_RETURN(minuteColumn, time);
    auto hourPickerColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(hourPickerColumnPattern, time);
    auto minutePickerColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(minutePickerColumnPattern, time);

    if (GetHour24()) {
        time.SetHour(hourPickerColumnPattern->GetCurrentIndex()); // hour from 0 to 23, index from 0 to 23
    } else if (amPmColumn) {
        auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_RETURN(amPmPickerColumnPattern, time);
        time.SetHour(GetHourFromAmPm(
            amPmPickerColumnPattern->GetCurrentIndex() == 0, hourPickerColumnPattern->GetCurrentIndex() + 1));
    }

    time.SetMinute(minutePickerColumnPattern->GetCurrentIndex()); // minute from 0 to 59, index from 0 to 59
    if (hasSecond_) {
        auto secondColumn = allChildNode_["second"].Upgrade();
        CHECK_NULL_RETURN(secondColumn, time);
        auto secondPickerColumnPattern = secondColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_RETURN(secondPickerColumnPattern, time);
        time.SetSecond(secondPickerColumnPattern->GetCurrentIndex()); // second from 0 to 59, index from 0 to 59
    }
    return time;
}

uint32_t TimePickerRowPattern::GetHourFromAmPm(bool isAm, uint32_t amPmhour) const
{
    if (isAm) {
        if (amPmhour == AM_PM_HOUR_12) { // AM 12:00 means 00:00
            return 0;
        }
        return amPmhour;
    }
    if (amPmhour == AM_PM_HOUR_12) { // PM 12 means 12:00
        return AM_PM_HOUR_12;
    }
    return amPmhour + AM_PM_HOUR_12; // need add 12 hour to 24 hours style
}

void TimePickerRowPattern::HandleColumnChange(const RefPtr<FrameNode>& tag, bool isAdd, uint32_t index, bool needNotify)
{
    std::vector<RefPtr<FrameNode>> tags;
    for (const auto& tag : tags) {
        auto iter = std::find_if(timePickerColumns_.begin(), timePickerColumns_.end(), [&tag](const auto& c) {
                auto column = c.Upgrade();
                return column && column->GetId() == tag->GetId();
            });
        if (iter != timePickerColumns_.end()) {
            auto timePickerColumn = (*iter).Upgrade();
            CHECK_NULL_VOID(timePickerColumn);
            auto timePickerColumnPattern = timePickerColumn->GetPattern<TimePickerColumnPattern>();
            CHECK_NULL_VOID(timePickerColumnPattern);
            timePickerColumnPattern->FlushCurrentOptions();
        }
    }
}

void TimePickerRowPattern::OnFontConfigurationUpdate()
{
    CHECK_NULL_VOID(closeDialogEvent_);
    closeDialogEvent_();
}

void TimePickerRowPattern::OnFontScaleConfigurationUpdate()
{
    CHECK_NULL_VOID(closeDialogEvent_);
    closeDialogEvent_();
}

void TimePickerRowPattern::UpdateConfirmButtonMargin(
    const RefPtr<FrameNode>& buttonConfirmNode, const RefPtr<DialogTheme>& dialogTheme)
{
    MarginProperty margin;
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        DialogTypeMargin::UpdateDialogMargin(isRtl, margin, dialogTheme, true, ModuleDialogType::TIMEPICKER_DIALOG);
    } else {
        DialogTypeMargin::UpdateDialogMargin(isRtl, margin, dialogTheme, false, ModuleDialogType::TIMEPICKER_DIALOG);
    }
    buttonConfirmNode->GetLayoutProperty()->UpdateMargin(margin);
}

void TimePickerRowPattern::UpdateCancelButtonMargin(
    const RefPtr<FrameNode>& buttonCancelNode, const RefPtr<DialogTheme>& dialogTheme)
{
    MarginProperty margin;
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        DialogTypeMargin::UpdateDialogMargin(!isRtl, margin, dialogTheme, true, ModuleDialogType::TIMEPICKER_DIALOG);
    } else {
        DialogTypeMargin::UpdateDialogMargin(!isRtl, margin, dialogTheme, false,
            ModuleDialogType::TIMEPICKER_DIALOG);
    }
    buttonCancelNode->GetLayoutProperty()->UpdateMargin(margin);
}

void TimePickerRowPattern::OnLanguageConfigurationUpdate()
{
    FlushAmPmFormatString();
    UpdateLanguageAndAmPmTimeOrder();
    if (!GetHour24()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto children = host->GetChildren();
        auto iter = children.begin();
        CHECK_NULL_VOID(*iter);
        auto amPmNode = *iter;
        CHECK_NULL_VOID(amPmNode);
        if (amPmTimeOrder_ == "01" && isAmPmTimeOrderUpdate_) {
            // if hasSecond_ is true, then amPmNode should be moved from slot 0 to 3, otherwise from slot 0 to 2
            hasSecond_ ? amPmNode->MovePosition(3) : amPmNode->MovePosition(2);
        } else if (amPmTimeOrder_ == "10" && isAmPmTimeOrderUpdate_) {
            // if hasSecond_ is true, then amPmNode should be moved from slot 3 to 0, otherwise form slot 2 to 0
            hasSecond_ ? std::advance(iter, 3) : std::advance(iter, 2);
            amPmNode = *iter;
            CHECK_NULL_VOID(amPmNode);
            amPmNode->MovePosition(0);
        }
        UpdateNodePositionForUg();
        auto layoutProperty = AceType::DynamicCast<FrameNode>(amPmNode)->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        layoutProperty->UpdateLayoutWeight(1);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    auto buttonConfirmNode = weakButtonConfirm_.Upgrade();
    CHECK_NULL_VOID(buttonConfirmNode);
    auto confirmNode = AceType::DynamicCast<FrameNode>(buttonConfirmNode->GetFirstChild());
    CHECK_NULL_VOID(confirmNode);
    auto confirmNodeLayout = confirmNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(confirmNodeLayout);
    confirmNodeLayout->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.ok"));
    auto pipeline = confirmNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    UpdateConfirmButtonMargin(buttonConfirmNode, dialogTheme);
    confirmNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    auto buttonCancelNode = weakButtonCancel_.Upgrade();
    CHECK_NULL_VOID(buttonCancelNode);
    auto cancelNode = AceType::DynamicCast<FrameNode>(buttonCancelNode->GetFirstChild());
    CHECK_NULL_VOID(cancelNode);
    auto cancelNodeLayout = cancelNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(cancelNodeLayout);
    cancelNodeLayout->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.cancel"));
    UpdateCancelButtonMargin(buttonCancelNode, dialogTheme);
    cancelNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TimePickerRowPattern::UpdateNodePositionForUg()
{
    if (!isPreLanguageUg_ && language_ != "ug") {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // ug's node order is S:M:H, need to change it to H:M:S
    if (isPreLanguageUg_ && isAmPmTimeOrderUpdate_) {
        if (hasSecond_) {
            auto secondNode = host->GetChildAtIndex(CHILD_INDEX_FIRST);
            CHECK_NULL_VOID(secondNode);
            secondNode->MovePosition(CHILD_INDEX_THIRD);

            auto minuteNode = host->GetChildAtIndex(CHILD_INDEX_FIRST);
            CHECK_NULL_VOID(minuteNode);
            minuteNode->MovePosition(CHILD_INDEX_SECOND);
        } else {
            auto minuteNode = host->GetChildAtIndex(CHILD_INDEX_FIRST);
            CHECK_NULL_VOID(minuteNode);
            minuteNode->MovePosition(CHILD_INDEX_SECOND);
        }
    } else if ((isPreLanguageUg_ && !isAmPmTimeOrderUpdate_) || (language_ == "ug")) {
        if (hasSecond_) {
            auto hourNode = host->GetChildAtIndex(CHILD_INDEX_FOURTH);
            CHECK_NULL_VOID(hourNode);
            hourNode->MovePosition(CHILD_INDEX_SECOND);
            auto minuteNode = host->GetChildAtIndex(CHILD_INDEX_FOURTH);
            CHECK_NULL_VOID(minuteNode);
            minuteNode->MovePosition(CHILD_INDEX_THIRD);
        } else {
            auto hourNode = host->GetChildAtIndex(CHILD_INDEX_THIRD);
            CHECK_NULL_VOID(hourNode);
            hourNode->MovePosition(CHILD_INDEX_SECOND);
        }
    }
    if (isPreLanguageUg_) {
        isPreLanguageUg_ = false;
    }
}

void TimePickerRowPattern::FlushAmPmFormatString()
{
    auto amPmStrings = Localization::GetInstance()->GetAmPmStrings();
    if (amPmStrings.size() > 1) {
        vecAmPm_.clear();
        std::string am = amPmStrings[0];
        vecAmPm_.emplace_back(am);
        std::string pm = amPmStrings[1];
        vecAmPm_.emplace_back(pm);
    }
}

void TimePickerRowPattern::SetChangeCallback(ColumnChangeCallback&& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    for (const auto& child : children) {
        auto stackNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(stackNode);
        auto columnBlendNode = DynamicCast<FrameNode>(stackNode->GetLastChild());
        CHECK_NULL_VOID(columnBlendNode);
        auto childNode = DynamicCast<FrameNode>(columnBlendNode->GetLastChild());
        CHECK_NULL_VOID(childNode);
        auto timePickerColumnPattern = childNode->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(timePickerColumnPattern);
        timePickerColumnPattern->SetChangeCallback(std::move(value));
    }
}

void TimePickerRowPattern::FlushColumn()
{
    UpdateAllChildNode();
    auto amPmColumn = allChildNode_["amPm"].Upgrade();
    auto hourColumn = allChildNode_["hour"].Upgrade();
    if (GetHour24()) {
        CHECK_NULL_VOID(hourColumn);
        auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(hourColumnPattern);
        hourColumnPattern->SetOptions(GetOptionsCount());
        hourColumnPattern->SetShowCount(GetShowCount());
        hourColumnPattern->FlushCurrentOptions();
    } else if (amPmColumn) {
        auto amPmColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(amPmColumnPattern);
        amPmColumnPattern->SetShowCount(AM_PM_COUNT);
        amPmColumnPattern->FlushCurrentOptions();

        CHECK_NULL_VOID(hourColumn);
        auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(hourColumnPattern);
        hourColumnPattern->SetOptions(GetOptionsCount());
        hourColumnPattern->SetShowCount(GetShowCount());
        hourColumnPattern->FlushCurrentOptions();
    }

    auto minuteColumn = allChildNode_["minute"].Upgrade();
    CHECK_NULL_VOID(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_VOID(minuteColumnPattern);
    minuteColumnPattern->SetShowCount(GetShowCount());
    minuteColumnPattern->FlushCurrentOptions();
    if (hasSecond_) {
        auto secondColumn = allChildNode_["second"].Upgrade();
        CHECK_NULL_VOID(secondColumn);
        auto secondColumnPattern = secondColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(secondColumnPattern);
        secondColumnPattern->SetOptions(GetOptionsCount());
        secondColumnPattern->SetShowCount(GetShowCount());
        secondColumnPattern->FlushCurrentOptions();
    }
}

void TimePickerRowPattern::OnDataLinking(
    const RefPtr<FrameNode>& tag, bool isAdd, uint32_t index, std::vector<RefPtr<FrameNode>>& resultTags)
{
    CHECK_NULL_VOID(tag);
    auto hourNode = allChildNode_["hour"].Upgrade();
    CHECK_NULL_VOID(hourNode);
    if (tag->GetId() != hourNode->GetId()) {
        return;
    }

    if (!GetHour24()) {
        HandleHour12Change(isAdd, index, resultTags);
    }
}

const std::string& TimePickerRowPattern::GetOptionsValue(const RefPtr<FrameNode>& frameNode, uint32_t optionIndex)
{
    UpdateAllChildNode();
    if (frameNode == allChildNode_["amPm"]) {
        return options_[allChildNode_["amPm"]][optionIndex];
    }
    bool isHour12 = !GetHour24();
    auto isHourNode = frameNode == allChildNode_["hour"];
    if (options_.find(frameNode) == options_.end()) {
        options_[frameNode] = std::unordered_map<uint32_t, std::string>();
    }
    if (options_[frameNode].find(optionIndex) == options_[frameNode].end()) {
        options_[frameNode][optionIndex] =
            isHourNode ? GetHourFormatString(optionIndex + isHour12) : GetMinuteFormatString(optionIndex);
    }
    return options_[frameNode][optionIndex];
}

void TimePickerRowPattern::OnColumnsBuilding()
{
    HandleHourColumnBuilding();
    HandleMinAndSecColumnBuilding();
}

void TimePickerRowPattern::HandleHourColumnBuilding()
{
    UpdateAllChildNode();
    auto amPmColumn = allChildNode_["amPm"].Upgrade();
    auto hourColumn = allChildNode_["hour"].Upgrade();
    optionsTotalCount_[hourColumn] = 0;
    if (GetHour24()) {
        CHECK_NULL_VOID(hourColumn);
        auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(hourColumnPattern);
        for (uint32_t hour = 0; hour <= 23; ++hour) { // time's hour from 0 to 23.
            if (hour == selectedTime_.GetHour()) {
                hourColumnPattern->SetCurrentIndex(hour);
            }
            optionsTotalCount_[hourColumn]++;
        }
        hourColumnPattern->SetOptions(GetOptionsCount());
        hourColumnPattern->SetWheelModeEnabled(wheelModeEnabled_);
        hourColumn->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    } else if (amPmColumn) {
        CHECK_NULL_VOID(amPmColumn);
        CHECK_NULL_VOID(hourColumn);
        auto amPmColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(amPmColumnPattern);
        auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(hourColumnPattern);
        options_[amPmColumn][0] = GetAmFormatString();
        options_[amPmColumn][1] = GetPmFormatString();

        if (IsAmHour(selectedTime_.GetHour())) {
            amPmColumnPattern->SetCurrentIndex(0); // AM's index
        } else {
            amPmColumnPattern->SetCurrentIndex(1); // PM's index
        }
        optionsTotalCount_[amPmColumn] = CHILD_WITHOUT_AMPM_SIZE;
        auto selectedHour = GetAmPmHour(selectedTime_.GetHour());
        for (uint32_t hour = 1; hour <= AM_PM_HOUR_12; ++hour) { // AM_PM hour start from 1 to 12
            if (hour == selectedHour) {
                hourColumnPattern->SetCurrentIndex(hour - 1);
            }
            optionsTotalCount_[hourColumn]++;
        }
        amPmColumnPattern->SetOptions(GetOptionsCount());
        hourColumnPattern->SetOptions(GetOptionsCount());
        amPmColumnPattern->SetWheelModeEnabled(wheelModeEnabled_);
        hourColumnPattern->SetWheelModeEnabled(wheelModeEnabled_);
    }
}

void TimePickerRowPattern::HandleMinAndSecColumnBuilding()
{
    UpdateAllChildNode();
    auto minuteColumn = allChildNode_["minute"].Upgrade();
    CHECK_NULL_VOID(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_VOID(minuteColumnPattern);
    optionsTotalCount_[minuteColumn] = 0;

    for (uint32_t minute = 0; minute <= 59; ++minute) { // time's minute from 0 to 59
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) &&
            GetPrefixMinute() == ZeroPrefixType::HIDE) {
            options_[minuteColumn][minute] = std::to_string(minute);
        } else {
            if (minute < 10) { // time's minute less than 10
                options_[minuteColumn][minute] = std::string("0") + std::to_string(minute);
            }
        }
        if (minute == selectedTime_.GetMinute()) {
            minuteColumnPattern->SetCurrentIndex(minute);
        }
        optionsTotalCount_[minuteColumn]++;
    }
    minuteColumnPattern->SetOptions(GetOptionsCount());
    minuteColumnPattern->SetWheelModeEnabled(wheelModeEnabled_);

    auto secondColumn = allChildNode_["second"].Upgrade();
    CHECK_NULL_VOID(secondColumn);
    auto secondColumnPattern = secondColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_VOID(secondColumnPattern);
    optionsTotalCount_[secondColumn] = 0;

    for (uint32_t second = 0; second <= 59; ++second) { // time's second from 0 to 59
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) &&
            GetPrefixSecond() == ZeroPrefixType::HIDE) {
            options_[secondColumn][second] = std::to_string(second);
        } else {
            if (second < 10) { // time's second less than 10
                options_[secondColumn][second] = std::string("0") + std::to_string(second);
            }
        }
        if (second == selectedTime_.GetSecond()) {
            secondColumnPattern->SetCurrentIndex(second);
        }
        optionsTotalCount_[secondColumn]++;
    }
    secondColumnPattern->SetOptions(GetOptionsCount());
    secondColumnPattern->SetWheelModeEnabled(wheelModeEnabled_);
}

void TimePickerRowPattern::UpdateAllChildNode()
{
    if (hasSecond_) {
        GetAllChildNodeWithSecond();
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (GetHour24() && host->GetChildren().size() == CHILD_WITH_AMPM_SIZE) {
        // if amPmTimeOrder is "10", amPm node is in slot 0, otherwise in slot 2
        host->RemoveChildAtIndex(amPmTimeOrder_ == "10" ? AMPMDEFAULTPOSITION : AMPM_FORWARD_WITHOUTSECOND);
        amPmId_.reset();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        host->MarkModifyDone();
    } else if (!GetHour24() && host->GetChildren().size() == CHILD_WITHOUT_AMPM_SIZE) {
        CreateAmPmNode();
    }
    if (GetHour24() && host->GetChildren().size() != CHILD_WITHOUT_AMPM_SIZE) {
        return;
    }

    if (!GetHour24() && host->GetChildren().size() != CHILD_WITH_AMPM_SIZE) {
        return;
    }
    if (language_ == "ug") {
        UpdateAllChildNodeForUg();
        return;
    }
    auto children = host->GetChildren();
    auto iter = children.begin();
    CHECK_NULL_VOID(*iter);
    auto amPmNode = GetAmPmNode(iter);
    auto hourNode = GetHourNode(iter);
    auto minuteNode = GetMinuteNode(iter);
    allChildNode_["amPm"] = amPmNode;
    allChildNode_["hour"] = hourNode;
    allChildNode_["minute"] = minuteNode;
}

void TimePickerRowPattern::GetAllChildNodeWithSecond()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (GetHour24() && host->GetChildren().size() == CHILD_WITH_AMPM_SIZE + 1) {
        host->RemoveChildAtIndex(amPmTimeOrder_ == "10" ? AMPMDEFAULTPOSITION : AMPM_FORWARD_WITHSECOND);
        amPmId_.reset();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        host->MarkModifyDone();
    } else if (!GetHour24() && host->GetChildren().size() == CHILD_WITHOUT_AMPM_SIZE + 1) {
        CreateAmPmNode();
    }
    if ((GetHour24() && host->GetChildren().size() != CHILD_WITHOUT_AMPM_SIZE + 1) ||
        (!GetHour24() && host->GetChildren().size() != CHILD_WITH_AMPM_SIZE + 1)) {
        return;
    }
    if (language_ == "ug") {
        UpdateAllChildNodeForUg();
        return;
    }
    auto children = host->GetChildren();
    auto iter = children.begin();
    CHECK_NULL_VOID(*iter);
    auto amPmNode = GetAmPmNode(iter);
    auto hourNode = GetHourNode(iter);
    auto minuteNode = GetMinuteNode(iter);
    auto secondNode = GetSecondNode(iter);
    allChildNode_["amPm"] = amPmNode;
    allChildNode_["hour"] = hourNode;
    allChildNode_["minute"] = minuteNode;
    allChildNode_["second"] = secondNode;
}

RefPtr<FrameNode> TimePickerRowPattern::GetAmPmNode(std::list<RefPtr<UINode>>::iterator& iter)
{
    if (GetHour24()) {
        return nullptr;
    }
    auto amPm = (*iter);
    if (amPmTimeOrder_ == "01") {
        if (!hasSecond_) {
            std::advance(iter, AMPM_FORWARD_WITHOUTSECOND);
            amPm = (*iter);
            std::advance(iter, AMPM_BACKWARD_WITHOUTSECOND);
        } else {
            std::advance(iter, AMPM_FORWARD_WITHSECOND);
            amPm = (*iter);
            std::advance(iter, AMPM_BACKWARD_WITHSECOND);
        }
    } else {
        iter++;
    }
    CHECK_NULL_RETURN(amPm, nullptr);
    auto amPmStackNode = DynamicCast<FrameNode>(amPm);
    auto amPmBlendNode = DynamicCast<FrameNode>(amPmStackNode->GetLastChild());
    CHECK_NULL_RETURN(amPmBlendNode, nullptr);
    auto amPmNode = DynamicCast<FrameNode>(amPmBlendNode->GetLastChild());
    CHECK_NULL_RETURN(amPmNode, nullptr);
    return amPmNode;
}

RefPtr<FrameNode> TimePickerRowPattern::GetHourNode(std::list<RefPtr<UINode>>::iterator& iter)
{
    auto hour = *iter;
    CHECK_NULL_RETURN(hour, nullptr);
    auto hourStackNode = DynamicCast<FrameNode>(hour);
    auto hourBlendNode = DynamicCast<FrameNode>(hourStackNode->GetLastChild());
    CHECK_NULL_RETURN(hourBlendNode, nullptr);
    auto hourNode = DynamicCast<FrameNode>(hourBlendNode->GetLastChild());
    CHECK_NULL_RETURN(hourNode, nullptr);
    iter++;
    return hourNode;
}

RefPtr<FrameNode> TimePickerRowPattern::GetMinuteNode(std::list<RefPtr<UINode>>::iterator& iter)
{
    auto minute = *iter;
    CHECK_NULL_RETURN(minute, nullptr);
    auto minuteStackNode = DynamicCast<FrameNode>(minute);
    auto minuteBlendNode = DynamicCast<FrameNode>(minuteStackNode->GetLastChild());
    CHECK_NULL_RETURN(minuteBlendNode, nullptr);
    auto minuteNode = DynamicCast<FrameNode>(minuteBlendNode->GetLastChild());
    CHECK_NULL_RETURN(minuteNode, nullptr);
    iter++;
    return minuteNode;
}

RefPtr<FrameNode> TimePickerRowPattern::GetSecondNode(std::list<RefPtr<UINode>>::iterator& iter)
{
    if (!hasSecond_) {
        return nullptr;
    }
    auto second = *iter;
    CHECK_NULL_RETURN(second, nullptr);
    auto secondStackNode = DynamicCast<FrameNode>(second);
    auto secondBlendNode = DynamicCast<FrameNode>(secondStackNode->GetLastChild());
    CHECK_NULL_RETURN(secondBlendNode, nullptr);
    auto secondNode = DynamicCast<FrameNode>(secondBlendNode->GetLastChild());
    CHECK_NULL_RETURN(secondNode, nullptr);
    if (language_ == "ug") {
        iter++;
    }
    return secondNode;
}

void TimePickerRowPattern::UpdateAllChildNodeForUg()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    auto iter = children.begin();
    CHECK_NULL_VOID(*iter);
    RefPtr<FrameNode> amPmNode;
    if (!GetHour24()) {
        auto amPm = (*iter);
        CHECK_NULL_VOID(amPm);
        auto amPmStackNode = DynamicCast<FrameNode>(amPm);
        amPmNode = DynamicCast<FrameNode>(amPmStackNode->GetLastChild()->GetLastChild());
        CHECK_NULL_VOID(amPmNode);
        iter++;
    }
    auto secondNode = GetSecondNode(iter);
    auto minuteNode = GetMinuteNode(iter);
    auto hourNode = GetHourNode(iter);
    allChildNode_["amPm"] = amPmNode;
    allChildNode_["hour"] = hourNode;
    allChildNode_["minute"] = minuteNode;
    allChildNode_["second"] = secondNode;
}

void TimePickerRowPattern::HandleHour12Change(bool isAdd, uint32_t index, std::vector<RefPtr<FrameNode>>& resultTags)
{
    UpdateAllChildNode();
    auto amPm = allChildNode_["amPm"].Upgrade();
    CHECK_NULL_VOID(amPm);
    auto amPmPickerColumnPattern = amPm->GetPattern<TimePickerColumnPattern>();

    if (amPmPickerColumnPattern->GetCurrentIndex() == 0 && isAdd && index == 11) { // hour index start from 0 to 11
        amPmPickerColumnPattern->SetCurrentIndex(1);                               // add to PM's index
        resultTags.emplace_back(amPm);
        return;
    }
    if (amPmPickerColumnPattern->GetCurrentIndex() == 1 && !isAdd && index == 10) { // reduce to 11 hour (index is 10)
        amPmPickerColumnPattern->SetCurrentIndex(0);                                // change to AM whose index is 0
        resultTags.emplace_back(amPm);
        return;
    }
    if (amPmPickerColumnPattern->GetCurrentIndex() == 1 && isAdd && index == 11) {
        amPmPickerColumnPattern->SetCurrentIndex(0); // is PM (index is 1) and last hour (index is 11)
        resultTags.emplace_back(amPm);               // change to PM (index is 0)
        return;
    }
    if (amPmPickerColumnPattern->GetCurrentIndex() == 0 && !isAdd && index == 10) { // reduce to 11 hour(index is 10)
        amPmPickerColumnPattern->SetCurrentIndex(1);                                // change to PM
        resultTags.emplace_back(amPm);
        return;
    }
}

uint32_t TimePickerRowPattern::GetAmPmHour(uint32_t hourOf24) const
{
    if (hourOf24 == 0) {
        return AM_PM_HOUR_12;                         // AM 12:00 means 00:00 in 24 hour style
    }
    if (1 <= hourOf24 && hourOf24 <= AM_PM_HOUR_11) { // 00:00 to 11:00 is the same for any hour style
        return hourOf24;
    }
    if (hourOf24 == AM_PM_HOUR_12) { // 12:00 means PM start hour
        return AM_PM_HOUR_12;        // 12 PM
    }                                // hour from 13 to 23
    return hourOf24 - AM_PM_HOUR_12; // need reduce 12 to 12 hours style
}

bool TimePickerRowPattern::IsAmHour(uint32_t hourOf24) const
{
    return (0 <= hourOf24 && hourOf24 <= AM_PM_HOUR_11); // 00:00 to 11:00 is AM hour
}

std::string TimePickerRowPattern::GetAmFormatString() const
{
    if (vecAmPm_.empty()) {
        return "AM";
    }
    return vecAmPm_[0]; // first index is AM
}

std::string TimePickerRowPattern::GetPmFormatString() const
{
    if (vecAmPm_.size() < 2) { // size need to be 2 for AM and PM
        return "PM";
    }
    return vecAmPm_[1]; // second index is PM
}

std::string TimePickerRowPattern::GetHourFormatString(uint32_t hour) const
{
    DateTime time;
    time.minute = hour; // minute range [0, 59], hour range [0, 23]; hour range is in minute range.
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        if (Localization::GetInstance()->HasZeroHour()) {
            return AddZeroPrefix(Localization::GetInstance()->FormatDateTime(time, "m"));
        }
    } else {
        if (((GetPrefixHour() == ZeroPrefixType::AUTO) && GetHour24()) ||
            GetPrefixHour() == ZeroPrefixType::SHOW) {
            return AddZeroPrefix(Localization::GetInstance()->FormatDateTime(time, "m"));
        }
    }
    return Localization::GetInstance()->FormatDateTime(time, "m");
}

std::string TimePickerRowPattern::GetMinuteFormatString(uint32_t minute) const
{
    DateTime time;
    time.minute = minute;
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        return AddZeroPrefix(Localization::GetInstance()->FormatDateTime(time, "m"));
    } else {
        return Localization::GetInstance()->FormatDateTime(time, "m");
    }
}

std::string TimePickerRowPattern::GetSecondFormatString(uint32_t second) const
{
    DateTime time;
    time.second = second;
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        return AddZeroPrefix(Localization::GetInstance()->FormatDateTime(time, "s"));
    } else {
        return Localization::GetInstance()->FormatDateTime(time, "s");
    }
}

std::string TimePickerRowPattern::AddZeroPrefix(const std::string& value) const
{
    if (value.size() == 1 && '0' <= value[0] && value[0] <= '9') { // value is number in range [0, 9]
        return std::string("0") + value;                           // add prefix '0'
    }
    return value;
}

void TimePickerRowPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        if (pattern) {
            return pattern->OnKeyEvent(event);
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

void TimePickerRowPattern::PaintFocusState()
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

void TimePickerRowPattern::CalcLeftTotalColumnWidth(
    const RefPtr<FrameNode>& host, float& leftTotalColumnWidth, float childSize)
{
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (isRtl) {
        for (int32_t index = childSize - 1; index > focusKeyID_; --index) {
            auto stackChild = DynamicCast<FrameNode>(host->GetChildAtIndex(index));
            CHECK_NULL_VOID(stackChild);
            auto geometryNode = stackChild->GetGeometryNode();
            CHECK_NULL_VOID(geometryNode);
            leftTotalColumnWidth += geometryNode->GetFrameSize().Width();
        }
    } else {
        for (int32_t index = 0; index < focusKeyID_; ++index) {
            auto stackChild = DynamicCast<FrameNode>(host->GetChildAtIndex(index));
            CHECK_NULL_VOID(stackChild);
            auto geometryNode = stackChild->GetGeometryNode();
            CHECK_NULL_VOID(geometryNode);
            leftTotalColumnWidth += geometryNode->GetFrameSize().Width();
        }
    }
}

void TimePickerRowPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childSize = static_cast<float>(host->GetChildren().size());
    auto leftTotalColumnWidth = 0.0f;
    CalcLeftTotalColumnWidth(host, leftTotalColumnWidth, childSize);
    auto stackChild = DynamicCast<FrameNode>(host->GetChildAtIndex(focusKeyID_));
    CHECK_NULL_VOID(stackChild);
    auto columnBlendChild = DynamicCast<FrameNode>(stackChild->GetLastChild());
    CHECK_NULL_VOID(columnBlendChild);
    auto pickerChild = DynamicCast<FrameNode>(columnBlendChild->GetLastChild());
    CHECK_NULL_VOID(pickerChild);
    auto columnWidth = pickerChild->GetGeometryNode()->GetFrameSize().Width();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto dividerSpacing = pipeline->NormalizeToPx(pickerTheme->GetDividerSpacing());
    auto pickerThemeWidth = dividerSpacing * RATE;

    CHECK_EQUAL_VOID(childSize, 0);
    auto centerX = (columnWidth - pickerThemeWidth) / RATE + leftTotalColumnWidth + PRESS_INTERVAL.ConvertToPx();
    auto centerY =
        (host->GetGeometryNode()->GetFrameSize().Height() - dividerSpacing) / RATE + PRESS_INTERVAL.ConvertToPx();
    float piantRectWidth = (dividerSpacing - PRESS_INTERVAL.ConvertToPx()) * RATE;
    float piantRectHeight = dividerSpacing - PRESS_INTERVAL.ConvertToPx() * RATE;
    if (piantRectWidth > columnWidth) {
        piantRectWidth = columnWidth - FOCUS_OFFSET.ConvertToPx() * RATE;
        centerX = leftTotalColumnWidth + FOCUS_OFFSET.ConvertToPx();
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

bool TimePickerRowPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (event.code == KeyCode::KEY_DPAD_UP || event.code == KeyCode::KEY_DPAD_DOWN ||
        event.code == KeyCode::KEY_DPAD_LEFT || event.code == KeyCode::KEY_DPAD_RIGHT ||
        event.code == KeyCode::KEY_MOVE_HOME || event.code == KeyCode::KEY_MOVE_END) {
        return HandleDirectionKey(event.code);
    }
    return false;
}

void TimePickerRowPattern::SetFocusDisable()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);

    focusHub->SetFocusable(false);
}

void TimePickerRowPattern::SetFocusEnable()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);

    focusHub->SetFocusable(true);
}

bool TimePickerRowPattern::CheckFocusID(int32_t childSize)
{
    if (focusKeyID_ > childSize - 1) {
        focusKeyID_ = childSize - 1;
        return false;
    }
    if (NeedAdaptForAging()) {
        if (GetCurrentPage() == 1) {
            if (focusKeyID_ < 1) {
                focusKeyID_ = 1;
                return false;
            }
        } else {
            if (focusKeyID_ != 0) {
                focusKeyID_ = 0;
                return false;
            }
        }
    } else {
        if (focusKeyID_ < 0) {
            focusKeyID_ = 0;
            return false;
        }
    }
    return true;
}

bool TimePickerRowPattern::ParseDirectionKey(RefPtr<FrameNode>& host, RefPtr<TimePickerColumnPattern>& pattern,
    KeyCode& code, int32_t currentIndex, uint32_t totalOptionCount, int32_t childSize)
{
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (code == KeyCode::KEY_DPAD_UP || code == KeyCode::KEY_DPAD_DOWN) {
        auto index = (code == KeyCode::KEY_DPAD_UP) ? -1 : 1;
        pattern->SetCurrentIndex((totalOptionCount + currentIndex + index) % totalOptionCount);
        pattern->FlushCurrentOptions();
        pattern->HandleChangeCallback((code == KeyCode::KEY_DPAD_UP) ? false : true, true);
        pattern->HandleEventCallback(true);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return true;
    }
    if (code == KeyCode::KEY_MOVE_HOME) {
        pattern->SetCurrentIndex(1);
        pattern->InnerHandleScroll(false, false);
        return true;
    }
    if (code == KeyCode::KEY_MOVE_END) {
        pattern->SetCurrentIndex(totalOptionCount - UNOPTION_COUNT);
        pattern->InnerHandleScroll(true, false);
        return true;
    }
    if (code == KeyCode::KEY_DPAD_LEFT) {
        focusKeyID_ = isRtl ? (focusKeyID_ + 1) : (focusKeyID_ - 1);
        if (!CheckFocusID(childSize)) {
            return false;
        }
        PaintFocusState();
        return true;
    }
    if (code == KeyCode::KEY_DPAD_RIGHT) {
        focusKeyID_ = isRtl ? (focusKeyID_ - 1) : (focusKeyID_ + 1);
        if (!CheckFocusID(childSize)) {
            return false;
        }
        PaintFocusState();
        return true;
    }
    return false;
}

bool TimePickerRowPattern::HandleDirectionKey(KeyCode code)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto stackChild = DynamicCast<FrameNode>(host->GetChildAtIndex(focusKeyID_));
    CHECK_NULL_RETURN(stackChild, false);
    auto childSize = host->GetChildren().size();
    auto pickerChild = DynamicCast<FrameNode>(stackChild->GetLastChild()->GetLastChild());
    CHECK_NULL_RETURN(pickerChild, false);
    auto pattern = pickerChild->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto currentIndex = pattern->GetCurrentIndex();
    auto totalOptionCount = GetOptionCount(pickerChild);
    if (totalOptionCount == 0) {
        return false;
    }
    return ParseDirectionKey(host, pattern, code, currentIndex, totalOptionCount, static_cast<int32_t>(childSize));
}

void TimePickerRowPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetNeedCallChildrenUpdate(false);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto dialogTheme = context->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    auto disappearStyle = pickerTheme->GetDisappearOptionStyle();
    auto normalStyle = pickerTheme->GetOptionStyle(false, false);
    auto pickerProperty = host->GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_VOID(pickerProperty);
    pickerProperty->UpdateColor(GetTextProperties().normalTextStyle_.textColor.value_or(normalStyle.GetTextColor()));
    pickerProperty->UpdateDisappearColor(
        GetTextProperties().disappearTextStyle_.textColor.value_or(disappearStyle.GetTextColor()));
    if (isPicker_) {
        return;
    }
    SetBackgroundColor(dialogTheme->GetBackgroundColor());
    auto buttonTitleNode = buttonTitleNode_.Upgrade();
    CHECK_NULL_VOID(buttonTitleNode);
    auto buttonTitleRenderContext = buttonTitleNode->GetRenderContext();
    CHECK_NULL_VOID(buttonTitleRenderContext);
    buttonTitleRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    auto childText = buttonTitleNode->GetFirstChild();
    CHECK_NULL_VOID(childText);
    auto textTitleNode = DynamicCast<FrameNode>(childText);
    CHECK_NULL_VOID(textTitleNode);
    auto textLayoutProperty = textTitleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateTextColor(pickerTheme->GetTitleStyle().GetTextColor());
    auto contentRowNode = contentRowNode_.Upgrade();
    CHECK_NULL_VOID(contentRowNode);
    auto layoutRenderContext = contentRowNode->GetRenderContext();
    CHECK_NULL_VOID(layoutRenderContext);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) || !layoutRenderContext->IsUniRenderEnabled()) {
        layoutRenderContext->UpdateBackgroundColor(dialogTheme->GetButtonBackgroundColor());
    }
    host->MarkModifyDone();
}

bool TimePickerRowPattern::NeedAdaptForAging()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, false);

    if (GreatOrEqual(pipeline->GetFontScale(), pickerTheme->GetMaxOneFontScale()) &&
        Dimension(pipeline->GetRootHeight()).ConvertToVp() > pickerTheme->GetDeviceHeightLimit()) {
        return true;
    }
    return false;
}
} // namespace OHOS::Ace::NG
