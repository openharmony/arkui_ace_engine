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
#include "core/components_ng/pattern/picker_utils/toss_animation_controller.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CHILD_WITH_AMPM_SIZE = 3;
constexpr int32_t CHILD_WITHOUT_AMPM_SIZE = 2;
constexpr uint32_t AM_PM_HOUR_12 = 12;
constexpr uint32_t AM_PM_HOUR_11 = 11;
constexpr uint32_t MINUTE_10 = 10;
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
const Dimension FOCUS_INTERVAL = 2.0_vp;
const Dimension LINE_WIDTH = 1.5_vp;
const int32_t RATE = 2;
const PickerTime START_DEFAULT_TIME = PickerTime(0, 0, 0);
const PickerTime END_DEFAULT_TIME = PickerTime(23, 59, 59);
const uint32_t INDEX_AM_0 = 0;
const uint32_t INDEX_PM_1 = 1;
const uint32_t INDEX_HOUR_STRAT = 0;
const uint32_t INDEX_MINUTE_STRAT = 0;
const uint32_t INDEX_MINUTE_END = 59;
const uint32_t INDEX_SECOND_STRAT = 0;
const uint32_t INDEX_SECOND_ADD_ZERO = 10;
const uint32_t INDEX_SECOND_END = 59;
const uint32_t SIZE_OF_AMPM_COLUMN_OPTION = 2;
constexpr float PICKER_MAXFONTSCALE = 1.0f;
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
    if (config.skipLayout || config.skipMeasure) {
        return false;
    }

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

void TimePickerRowPattern::ColumnPatternStopHaptic()
{
    if (!isEnableHaptic_) {
        return;
    }
    for (auto iter = allChildNode_.begin(); iter != allChildNode_.end(); iter++) {
        auto columnNode = iter->second.Upgrade();
        if (!columnNode) {
            continue;
        }
        auto timePickerColumnPattern = columnNode->GetPattern<TimePickerColumnPattern>();
        if (!timePickerColumnPattern) {
            continue;
        }
        timePickerColumnPattern->StopHaptic();
    }
}

bool TimePickerRowPattern::IsCircle()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, false);

    return pickerTheme->IsCircleDial();
}

void TimePickerRowPattern::SetDefaultColoumnFocus(std::unordered_map<std::string, WeakPtr<FrameNode>>::iterator& it,
    const std::string &id, bool& focus, const std::function<void(const std::string&)>& call)
{
    auto column = it->second.Upgrade();
    CHECK_NULL_VOID(column);
    auto tmpPattern = column->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_VOID(tmpPattern);
    tmpPattern->SetSelectedMarkId(id);
    tmpPattern->SetSelectedMarkListener(call);
    if (focus) {
        tmpPattern->SetSelectedMark(true, false);
        selectedColumnId_ = id;
        focus = false;
    }
}

void TimePickerRowPattern::ClearFocus()
{
    CHECK_EQUAL_VOID(IsCircle(), false);
    if (!isClearFocus_ && (HasSecondNode() == hasSecond_)) {
        return ;
    }
    isClearFocus_ = true;
    if (!selectedColumnId_.empty()) {
        auto it = allChildNode_.find(selectedColumnId_);
        if (it != allChildNode_.end()) {
            auto column = it->second.Upgrade();
            CHECK_NULL_VOID(column);
            auto tmpPattern = column->GetPattern<TimePickerColumnPattern>();
            CHECK_NULL_VOID(tmpPattern);
            tmpPattern->SetSelectedMark(false, false);
        }

        selectedColumnId_ = "";
    }
}

void TimePickerRowPattern::SetDefaultFocus()
{
    CHECK_EQUAL_VOID(IsCircle(), false);
    CHECK_EQUAL_VOID(isClearFocus_, false);
    isClearFocus_ = false;
    std::function<void(const std::string &focusId)> call =  [weak = WeakClaim(this)](const std::string &focusId) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->selectedColumnId_.empty()) {
            pattern->selectedColumnId_ = focusId;
            return;
        }
        auto it = pattern->allChildNode_.find(pattern->selectedColumnId_);
        if (it != pattern->allChildNode_.end()) {
            auto tmpColumn = it->second.Upgrade();
            if (tmpColumn) {
                auto tmpPattern = tmpColumn->GetPattern<TimePickerColumnPattern>();
                CHECK_NULL_VOID(tmpPattern);
                tmpPattern->SetSelectedMark(false, false);
            }
        }
        pattern->selectedColumnId_ = focusId;
    };
    static const std::string columnName[] = {"amPm", "hour", "minute", "second"};
    bool setFocus = true;
    for (size_t i = 0; i < sizeof(columnName) / sizeof(columnName[0]); i++) {
        auto it = allChildNode_.find(columnName[i]);
        if (it != allChildNode_.end()) {
            SetDefaultColoumnFocus(it, columnName[i], setFocus, call);
        }
    }
}

#ifdef SUPPORT_DIGITAL_CROWN
void TimePickerRowPattern::InitOnCrownEvent(const RefPtr<FocusHub>& focusHub)
{
    CHECK_NULL_VOID(focusHub);
    auto onCrowEvent = [wp = WeakClaim(this)](const CrownEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnCrownEvent(event);
    };
    focusHub->SetOnCrownEventInternal(std::move(onCrowEvent));
}

bool TimePickerRowPattern::OnCrownEvent(const CrownEvent& event)
{
    if (event.action == OHOS::Ace::CrownAction::BEGIN ||
        event.action == OHOS::Ace::CrownAction::UPDATE ||
        event.action == OHOS::Ace::CrownAction::END) {
        RefPtr<TimePickerColumnPattern> crownPickerColumnPattern;
        for (auto& iter : timePickerColumns_) {
            auto column = iter.Upgrade();
            if (!column) {
                continue;
            }
            auto pickerColumnPattern = column->GetPattern<TimePickerColumnPattern>();
            CHECK_NULL_RETURN(pickerColumnPattern, false);
            auto columnID =  pickerColumnPattern->GetSelectedColumnId();
            if (!pickerColumnPattern->IsCrownEventEnded()) {
                crownPickerColumnPattern = pickerColumnPattern;
                break;
            } else if (columnID == selectedColumnId_) {
                crownPickerColumnPattern = pickerColumnPattern;
            }
        }
        if (crownPickerColumnPattern != nullptr) {
            return crownPickerColumnPattern->OnCrownEvent(event);
        }
    }
    return false;
}
#endif

void TimePickerRowPattern::InitFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    if (focusHub) {
        InitOnKeyEvent(focusHub);
#ifdef SUPPORT_DIGITAL_CROWN
        InitOnCrownEvent(focusHub);
#endif
    }
}

void TimePickerRowPattern::UpdateTitleNodeContent()
{
    if (HasTitleNode()) {
        auto textTitleNode = FrameNode::GetOrCreateFrameNode(
            V2::TEXT_ETS_TAG, GetTitleId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        auto str = GetDialogTitleDate();
        CHECK_NULL_VOID(textTitleNode);
        auto textLayoutProperty = textTitleNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateContent(str.ToString(false));
        textTitleNode->MarkModifyDone();
        textTitleNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void TimePickerRowPattern::SetCallBack()
{
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
    SetEnterSelectedAreaEventCallback([weak = WeakClaim(this)](bool refresh) {
        auto refPtr = weak.Upgrade();
        CHECK_NULL_VOID(refPtr);
        refPtr->FireEnterSelectedAreaEvent(refresh);
    });
}

void TimePickerRowPattern::OnModifyDone()
{
    Pattern::CheckLocalized();
    if (isFiredTimeChange_ && !isForceUpdate_ && !isDateTimeOptionUpdate_) {
        isFiredTimeChange_ = false;
        ColumnPatternInitHapticController();
        return;
    }
    LimitSelectedTimeInRange();
    isHapticChanged_ = false;
    isForceUpdate_ = false;
    isDateTimeOptionUpdate_ = false;
    ClearFocus();
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
    SetCallBack();
    InitFocusEvent();
    UpdateTitleNodeContent();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    if (isUserSetSelectColor_) {
        UpdateUserSetSelectColor();
    }
    SetDefaultFocus();
}

void TimePickerRowPattern::LimitSelectedTimeInRange()
{
    if (IsStartEndTimeDefined()) {
        selectedTime_ = AdjustTime(selectedTime_);
    }
}

void TimePickerRowPattern::InitDisabled()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    enabled_ = eventHub->IsEnabled();
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto opacity = curOpacity_;
    if (!enabled_) {
        opacity *= DISABLE_ALPHA;
        renderContext->UpdateOpacity(opacity);
    } else if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        renderContext->UpdateOpacity(opacity);
    }

    if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        for (const auto& child : host->GetChildren()) {
            auto stackNode = DynamicCast<FrameNode>(child);
            CHECK_NULL_VOID(stackNode);
            auto renderContext = stackNode->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateOpacity(opacity);
        }
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
        auto timePickerEventHub = GetOrCreateEventHub<TimePickerEventHub>();
        CHECK_NULL_VOID(timePickerEventHub);
        auto str = GetSelectedObject(true);
        auto info = std::make_shared<DatePickerChangeEvent>(str);
        timePickerEventHub->FireChangeEvent(info.get());
        timePickerEventHub->FireDialogChangeEvent(str);
        firedTimeStr_ = str;
    }
}

void TimePickerRowPattern::SetEnterSelectedAreaEventCallback(EventCallback&& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    for (const auto& child : children) {
        auto stackNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(stackNode);
        auto blendNode = DynamicCast<FrameNode>(stackNode->GetLastChild());
        CHECK_NULL_VOID(blendNode);
        auto childNode = DynamicCast<FrameNode>(blendNode->GetLastChild());
        CHECK_NULL_VOID(childNode);
        auto pickerColumnPattern = childNode->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(pickerColumnPattern);
        pickerColumnPattern->SetEnterSelectedAreaEventCallback(std::move(value));
    }
}

void TimePickerRowPattern::FireEnterSelectedAreaEvent(bool refresh)
{
    if (refresh) {
        auto timePickerEventHub = GetOrCreateEventHub<TimePickerEventHub>();
        CHECK_NULL_VOID(timePickerEventHub);
        auto str = GetEnterObject(true);
        auto info = std::make_shared<DatePickerChangeEvent>(str);
        timePickerEventHub->FireEnterSelectedAreaEvent(info.get());
        timePickerEventHub->FireDialogEnterSelectedAreaEvent(str);
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
    auto hourPickerColumnIndex = hourPickerColumnPattern->GetCurrentIndex();
    auto hour = GetOptionsValue(hourColumn, hourPickerColumnIndex);
    auto minutePickerColumnIdex = minutePickerColumnPattern->GetCurrentIndex();
    auto minute = GetOptionsValue(minuteColumn, minutePickerColumnIdex);

    if (startTime_.ToMinutes() == START_DEFAULT_TIME.ToMinutes() &&
        endTime_.ToMinutes() == END_DEFAULT_TIME.ToMinutes()) {
        if (GetHour24()) {
            time.SetHour(hourPickerColumnPattern->GetCurrentIndex()); // hour from 0 to 23, index from 0 to 23
        } else if (amPmColumn) {
            auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
            CHECK_NULL_RETURN(amPmPickerColumnPattern, time);
            time.SetHour(GetHourFromAmPm(
                amPmPickerColumnPattern->GetCurrentIndex() == 0, hourPickerColumnPattern->GetCurrentIndex() + 1));
        }
        time.SetMinute(minutePickerColumnPattern->GetCurrentIndex()); // minute from 0 to 59, index from 0 to 59
    } else {
        if (GetHour24()) {
            time.SetHour(hourPickerColumnPattern->GetCurrentIndex() + startTime_.GetHour());
        } else if (amPmColumn) {
            auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
            CHECK_NULL_RETURN(amPmPickerColumnPattern, time);
            time.SetHour(
                GetHourFromAmPm(amPmPickerColumnPattern->GetCurrentIndex() == 0, StringUtils::StringToUint(hour)));
        }
        time.SetMinute(StringUtils::StringToUint(minute));
    }

    if (hasSecond_) {
        auto secondColumn = allChildNode_["second"].Upgrade();
        CHECK_NULL_RETURN(secondColumn, time);
        auto secondPickerColumnPattern = secondColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_RETURN(secondPickerColumnPattern, time);
        time.SetSecond(secondPickerColumnPattern->GetCurrentIndex()); // second from 0 to 59, index from 0 to 59
    }
    return time;
}

std::string TimePickerRowPattern::GetEnterObject(bool isColumnChange, int32_t status)
{
    auto time = selectedTime_;
    if (isColumnChange) {
        time = GetCurrentEnterTime();
    }
    return time.ToString(true, hasSecond_, status);
}

PickerTime TimePickerRowPattern::GetCurrentEnterTime()
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
        if (IsStartEndTimeDefined()) {
            time.SetHour(hourPickerColumnPattern->GetEnterIndex() + startTime_.GetHour());
        } else {
            time.SetHour(hourPickerColumnPattern->GetEnterIndex()); // hour from 0 to 23, index from 0 to 23
        }
    } else if (amPmColumn) {
        auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_RETURN(amPmPickerColumnPattern, time);
        if (IsStartEndTimeDefined()) {
            auto hourPickerColumnIndex = hourPickerColumnPattern->GetEnterIndex();
            auto hour = GetOptionsValue(hourColumn, hourPickerColumnIndex);
            time.SetHour(
                GetHourFromAmPm(amPmPickerColumnPattern->GetEnterIndex() == 0, StringUtils::StringToUint(hour)));
        } else {
            time.SetHour(GetHourFromAmPm(
                amPmPickerColumnPattern->GetEnterIndex() == 0, hourPickerColumnPattern->GetEnterIndex() + 1));
        }
    }

    time.SetMinute(minutePickerColumnPattern->GetEnterIndex()); // minute from 0 to 59, index from 0 to 59
    if (hasSecond_) {
        auto secondColumn = allChildNode_["second"].Upgrade();
        CHECK_NULL_RETURN(secondColumn, time);
        auto secondPickerColumnPattern = secondColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_RETURN(secondPickerColumnPattern, time);
        time.SetSecond(secondPickerColumnPattern->GetEnterIndex()); // second from 0 to 59, index from 0 to 59
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
    if (wheelModeEnabled_ && isEnableCascade_ && !IsStartEndTimeDefined()) {
        OnDataLinking(tag, isAdd, index, tags);
    }
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

    HandleColumnsChangeTimeRange(tag);
}

bool TimePickerRowPattern::IsStartEndTimeDefined()
{
    auto isStartEndTimeDefined = startTime_.ToMinutes() != START_DEFAULT_TIME.ToMinutes() ||
                                 endTime_.ToMinutes() != END_DEFAULT_TIME.ToMinutes();
    return isStartEndTimeDefined;
}

void TimePickerRowPattern::HandleColumnsChangeTimeRange(const RefPtr<FrameNode>& tag)
{
    if (IsStartEndTimeDefined()) {
        auto hourColumn = allChildNode_["hour"].Upgrade();
        CHECK_NULL_VOID(hourColumn);
        auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(hourColumnPattern);

        auto minuteColumn = allChildNode_["minute"].Upgrade();
        CHECK_NULL_VOID(minuteColumn);
        auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(minuteColumnPattern);
        auto amPmColumn = allChildNode_["amPm"].Upgrade();
        auto secondColumn = allChildNode_["second"].Upgrade();
        if (!GetHour24() && tag == amPmColumn) {
            options_[hourColumn].clear();
            options_[minuteColumn].clear();
            UpdateHourAndMinuteTimeRange(tag);
            UpdateSecondTimeRange();
            hourColumnPattern->FlushCurrentOptions();
            minuteColumnPattern->FlushCurrentOptions();
            auto amPmColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
            CHECK_NULL_VOID(amPmColumnPattern);
            amPmColumnPattern->FlushCurrentOptions();
            if (hasSecond_ && secondColumn) {
                HandleSecondsChangeTimeRange(secondColumn);
            }
        } else if (tag == hourColumn || tag == minuteColumn) {
            options_[hourColumn].clear();
            options_[minuteColumn].clear();
            UpdateHourAndMinuteTimeRange(tag);
            hourColumnPattern->FlushCurrentOptions();
            minuteColumnPattern->FlushCurrentOptions();
            if (hasSecond_ && secondColumn) {
                HandleSecondsChangeTimeRange(secondColumn);
            }
        } else if (tag == secondColumn) {
            HandleSecondsChangeTimeRange(secondColumn);
        }
        oldHourValue_ = GetOptionsCurrentValue(hourColumn);
        oldMinuteValue_ = GetOptionsCurrentValue(minuteColumn);
    }
}

void TimePickerRowPattern::HandleSecondsChangeTimeRange(const RefPtr<FrameNode>& secondColumn)
{
    if (hasSecond_ && secondColumn) {
        options_[secondColumn].clear();
        UpdateSecondTimeRange();
        auto secondColumnPattern = secondColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(secondColumnPattern);
        secondColumnPattern->SetOptions(GetOptionsCount());
        secondColumnPattern->SetShowCount(GetShowCount());
        secondColumnPattern->FlushCurrentOptions();
        secondColumn->MarkModifyDone();
        secondColumn->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void TimePickerRowPattern::UpdateHourAndMinuteTimeRange(const RefPtr<FrameNode>& tag)
{
    auto hourColumn = allChildNode_["hour"].Upgrade();
    CHECK_NULL_VOID(hourColumn);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_VOID(hourColumnPattern);
    auto minuteColumn = allChildNode_["minute"].Upgrade();
    CHECK_NULL_VOID(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_VOID(minuteColumnPattern);
    auto amPmColumn = allChildNode_["amPm"].Upgrade();

    // update hour column's options
    HourChangeBuildTimeRange();
    if (!GetHour24() && tag == amPmColumn) {
        // update Hour column option after changing ampm column
        // and set corresponding new index based on old value
        uint32_t newIndex = INDEX_HOUR_STRAT;
        if (!GetOptionsIndex(hourColumn, oldHourValue_, newIndex)) {
            auto uintOldHour = StringUtils::StringToUint(oldHourValue_);
            if (((IsAmJudgeByAmPmColumn(amPmColumn) && uintOldHour == AM_PM_HOUR_12) ? INDEX_HOUR_STRAT : uintOldHour) <
                startTime_.GetHour()) {
                newIndex = INDEX_HOUR_STRAT;
            } else {
                newIndex = options_[hourColumn].size() - 1;
            }
        }
        hourColumnPattern->SetCurrentIndex(newIndex);
        hourColumnPattern->SetEnterIndex(newIndex);
    }
    oldHourValue_ = GetOptionsCurrentValue(hourColumn);

    // update minute column's options
    auto currentHourOf24 = StringUtils::StringToUint(oldHourValue_);
    if (!GetHour24()) {
        currentHourOf24 = GetHourFromAmPm(IsAmJudgeByAmPmColumn(amPmColumn), StringUtils::StringToUint(oldHourValue_));
    }
    MinuteChangeBuildTimeRange(currentHourOf24);
    if (tag != minuteColumn) {
        uint32_t newIndex = INDEX_MINUTE_STRAT;
        if (!GetOptionsIndex(minuteColumn, oldMinuteValue_, newIndex)) {
            if (StringUtils::StringToUint(oldMinuteValue_) < startTime_.GetMinute()) {
                newIndex = INDEX_MINUTE_STRAT;
            } else {
                newIndex = options_[minuteColumn].size() - 1;
            }
        }
        minuteColumnPattern->SetCurrentIndex(newIndex);
        minuteColumnPattern->SetEnterIndex(newIndex);
    }
    oldMinuteValue_ = GetOptionsCurrentValue(minuteColumn);
}

bool TimePickerRowPattern::IsAmJudgeByAmPmColumn(const RefPtr<FrameNode>& amPmColumn)
{
    auto isAm = false;
    CHECK_NULL_RETURN(amPmColumn, isAm);
    auto amPmColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(amPmColumnPattern, false);
    isAm = (options_[amPmColumn].size() == SIZE_OF_AMPM_COLUMN_OPTION && amPmColumnPattern->GetCurrentIndex() == 0) ||
           (options_[amPmColumn].size() < SIZE_OF_AMPM_COLUMN_OPTION && IsAmHour(startTime_.GetHour()));
    return isAm;
}

void TimePickerRowPattern::UpdateSecondTimeRange()
{
    auto secondColumn = allChildNode_["second"].Upgrade();
    CHECK_NULL_VOID(secondColumn);
    auto secondColumnPattern = secondColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_VOID(secondColumnPattern);
    optionsTotalCount_[secondColumn] = 0;

    for (uint32_t second = INDEX_SECOND_STRAT; second <= INDEX_SECOND_END; second++) { // time's second from 0 to 59
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) &&
            GetPrefixSecond() == ZeroPrefixType::HIDE) {
            options_[secondColumn][second] = std::to_string(second);
        } else {
            if (second < INDEX_SECOND_ADD_ZERO) { // time's second less than 10
                options_[secondColumn][second] = std::string("0") + std::to_string(second);
            } else {
                options_[secondColumn][second] = std::to_string(second);
            }
        }
        optionsTotalCount_[secondColumn]++;
    }
    secondColumnPattern->SetOptions(GetOptionsCount());
    IsStartEndTimeDefined() ? secondColumnPattern->SetWheelModeEnabled(false)
                            : secondColumnPattern->SetWheelModeEnabled(wheelModeEnabled_);
}

void TimePickerRowPattern::HourChangeBuildTimeRange()
{
    if (GetHour24()) {
        Hour24ChangeBuildTimeRange();
    } else {
        Hour12ChangeBuildTimeRange();
    }
}

void TimePickerRowPattern::Hour24ChangeBuildTimeRange()
{
    auto hourColumn = allChildNode_["hour"].Upgrade();
    CHECK_NULL_VOID(hourColumn);
    optionsTotalCount_[hourColumn] = 0;
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_VOID(hourColumnPattern);
    for (uint32_t index = 0; index < defined24Hours_.size(); index++) {
        options_[hourColumn][index] = defined24Hours_[index];
        optionsTotalCount_[hourColumn]++;
    }
    hourColumnPattern->SetOptions(GetOptionsCount());
    IsStartEndTimeDefined() ? hourColumnPattern->SetWheelModeEnabled(false)
                            : hourColumnPattern->SetWheelModeEnabled(wheelModeEnabled_);
    hourColumn->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TimePickerRowPattern::Hour12ChangeBuildTimeRange()
{
    auto amPmColumn = allChildNode_["amPm"].Upgrade();
    CHECK_NULL_VOID(amPmColumn);
    auto hourColumn = allChildNode_["hour"].Upgrade();
    CHECK_NULL_VOID(hourColumn);
    optionsTotalCount_[hourColumn] = 0;
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_VOID(hourColumnPattern);

    if (IsAmJudgeByAmPmColumn(amPmColumn)) {
        for (uint32_t index = 0; index < definedAMHours_.size(); index++) {
            options_[hourColumn][index] = definedAMHours_[index];
            optionsTotalCount_[hourColumn]++;
        }
    } else {
        for (uint32_t index = 0; index < definedPMHours_.size(); index++) {
            options_[hourColumn][index] = definedPMHours_[index];
            optionsTotalCount_[hourColumn]++;
        }
    }

    hourColumnPattern->SetOptions(GetOptionsCount());
    IsStartEndTimeDefined() ? hourColumnPattern->SetWheelModeEnabled(false)
                            : hourColumnPattern->SetWheelModeEnabled(wheelModeEnabled_);
}

void TimePickerRowPattern::MinuteChangeBuildTimeRange(uint32_t hourOf24)
{
    uint32_t startMinute = (hourOf24 == startTime_.GetHour()) ? startTime_.GetMinute() : INDEX_MINUTE_STRAT;
    uint32_t endMinute = (hourOf24 == endTime_.GetHour()) ? endTime_.GetMinute() : INDEX_MINUTE_END;
    auto minuteColumn = allChildNode_["minute"].Upgrade();
    CHECK_NULL_VOID(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_VOID(minuteColumnPattern);
    optionsTotalCount_[minuteColumn] = 0;
    uint32_t index = 0;
    for (uint32_t minute = startMinute; minute <= endMinute; minute++) {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) &&
            GetPrefixMinute() == ZeroPrefixType::HIDE) {
            options_[minuteColumn][index] = std::to_string(minute);
        } else {
            options_[minuteColumn][index] =
                (minute < MINUTE_10) ? std::string("0") + std::to_string(minute) : std::to_string(minute);
        }
        optionsTotalCount_[minuteColumn]++;
        index++;
    }

    minuteColumnPattern->SetOptions(GetOptionsCount());
    IsStartEndTimeDefined() ? minuteColumnPattern->SetWheelModeEnabled(false)
                            : minuteColumnPattern->SetWheelModeEnabled(wheelModeEnabled_);
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

void TimePickerRowPattern::UpdateButtonMargin(
    const RefPtr<FrameNode>& buttonNode, const RefPtr<DialogTheme>& dialogTheme, const bool isConfirmOrNextNode)
{
    MarginProperty margin;
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    isRtl = isConfirmOrNextNode ? isRtl : !isRtl;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        DialogTypeMargin::UpdateDialogMargin(isRtl, margin, dialogTheme, true, ModuleDialogType::TIMEPICKER_DIALOG);
    } else {
        DialogTypeMargin::UpdateDialogMargin(isRtl, margin, dialogTheme, false, ModuleDialogType::TIMEPICKER_DIALOG);
    }
    buttonNode->GetLayoutProperty()->UpdateMargin(margin);
}

void TimePickerRowPattern::UpdateDialogAgingButton(const RefPtr<FrameNode>& buttonNode, const bool isNext)
{
    CHECK_NULL_VOID(buttonNode);
    auto updateNode = AceType::DynamicCast<FrameNode>(buttonNode->GetFirstChild());
    CHECK_NULL_VOID(updateNode);
    auto updateNodeLayout = updateNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(updateNodeLayout);

    auto pipeline = updateNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    std::string lettersStr = isNext ? pickerTheme->GetNextText() : pickerTheme->GetPrevText();
    updateNodeLayout->UpdateContent(lettersStr);

    UpdateButtonMargin(buttonNode, dialogTheme, isNext);
    updateNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    auto buttonConfirmNode = weakButtonConfirm_.Upgrade();
    CHECK_NULL_VOID(buttonConfirmNode);
    auto confirmNode = AceType::DynamicCast<FrameNode>(buttonConfirmNode->GetFirstChild());
    CHECK_NULL_VOID(confirmNode);
    auto confirmNodeLayout = confirmNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(confirmNodeLayout);
    auto pipeline = confirmNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    confirmNodeLayout->UpdateContent(dialogTheme->GetConfirmText());
    UpdateButtonMargin(buttonConfirmNode, dialogTheme, true);
    confirmNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    auto buttonCancelNode = weakButtonCancel_.Upgrade();
    CHECK_NULL_VOID(buttonCancelNode);
    auto cancelNode = AceType::DynamicCast<FrameNode>(buttonCancelNode->GetFirstChild());
    CHECK_NULL_VOID(cancelNode);
    auto cancelNodeLayout = cancelNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(cancelNodeLayout);
    cancelNodeLayout->UpdateContent(dialogTheme->GetCancelText());
    UpdateButtonMargin(buttonCancelNode, dialogTheme, false);
    cancelNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    auto nextPrevButton = nextPrevButtonNode_.Upgrade();
    UpdateDialogAgingButton(nextPrevButton, isNext_);
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
        hourColumn->MarkModifyDone();
        hourColumn->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    } else if (amPmColumn) {
        auto amPmColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(amPmColumnPattern);
        amPmColumnPattern->SetShowCount(AM_PM_COUNT);
        amPmColumnPattern->FlushCurrentOptions();
        amPmColumn->MarkModifyDone();
        amPmColumn->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

        CHECK_NULL_VOID(hourColumn);
        auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(hourColumnPattern);
        hourColumnPattern->SetOptions(GetOptionsCount());
        hourColumnPattern->SetShowCount(GetShowCount());
        hourColumnPattern->FlushCurrentOptions();
        hourColumn->MarkModifyDone();
        hourColumn->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }

    auto minuteColumn = allChildNode_["minute"].Upgrade();
    CHECK_NULL_VOID(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_VOID(minuteColumnPattern);
    minuteColumnPattern->SetShowCount(GetShowCount());
    minuteColumnPattern->FlushCurrentOptions();
    minuteColumn->MarkModifyDone();
    minuteColumn->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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

bool TimePickerRowPattern::GetOptionsIndex(
    const RefPtr<FrameNode>& frameNode, const std::string& value, uint32_t& columnIndex)
{
    CHECK_NULL_RETURN(frameNode, false);
    bool result = false;
    auto columnFound = options_.find(frameNode);
    if (columnFound != options_.end()) {
        for (const auto& option : columnFound->second) {
            if (option.second == value) {
                columnIndex = option.first;
                result = true;
            }
        }
    }
    return result;
}

std::string TimePickerRowPattern::GetOptionsCurrentValue(const RefPtr<FrameNode>& frameNode)
{
    std::string result = "";
    CHECK_NULL_RETURN(frameNode, result);
    auto columnFound = options_.find(frameNode);
    if (columnFound != options_.end()) {
        auto columnPattern = frameNode->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_RETURN(columnPattern, result);
        auto currentIndex = columnPattern->GetCurrentIndex();
        for (const auto& option : columnFound->second) {
            if (option.first == currentIndex) {
                result = option.second;
            }
        }
    }
    return result;
}

std::string TimePickerRowPattern::GetOptionsValueWithIndex(const RefPtr<FrameNode>& frameNode, uint32_t optionIndex)
{
    std::string result = "";
    CHECK_NULL_RETURN(frameNode, result);
    auto columnFound = options_.find(frameNode);
    if (columnFound != options_.end()) {
        auto currentIndex = optionIndex;
        for (const auto& option : columnFound->second) {
            if (option.first == currentIndex) {
                result = option.second;
            }
        }
    }
    return result;
}

void TimePickerRowPattern::OnColumnsBuilding()
{
    if (IsStartEndTimeDefined()) {
        HandleHourColumnBuildingRange(GetSelectedTime());
        HandleMinAndSecColumnBuildingRange();
        RecordHourAndMinuteOptions();
    } else {
        HandleHourColumnBuilding();
        HandleMinAndSecColumnBuilding();
    }
}

void TimePickerRowPattern::HandleHourColumnBuilding()
{
    UpdateAllChildNode();
    auto hourColumn = allChildNode_["hour"].Upgrade();
    CHECK_NULL_VOID(hourColumn);
    optionsTotalCount_[hourColumn] = 0;
    if (GetHour24()) {
        auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(hourColumnPattern);
        for (uint32_t hour = 0; hour <= 23; ++hour) { // time's hour from 0 to 23.
            if (hour == selectedTime_.GetHour()) {
                hourColumnPattern->SetCurrentIndex(hour);
                hourColumnPattern->SetEnterIndex(hour);
            }
            optionsTotalCount_[hourColumn]++;
        }
        hourColumnPattern->SetOptions(GetOptionsCount());
        hourColumnPattern->SetWheelModeEnabled(wheelModeEnabled_);
        hourColumn->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    } else {
        auto amPmColumn = allChildNode_["amPm"].Upgrade();
        CHECK_NULL_VOID(amPmColumn);
        auto amPmColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(amPmColumnPattern);
        auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(hourColumnPattern);
        options_[amPmColumn][INDEX_AM_0] = GetAmFormatString();
        options_[amPmColumn][INDEX_PM_1] = GetPmFormatString();

        if (IsAmHour(selectedTime_.GetHour())) {
            amPmColumnPattern->SetCurrentIndex(0); // AM's index
            amPmColumnPattern->SetEnterIndex(0);
        } else {
            amPmColumnPattern->SetCurrentIndex(1); // PM's index
            amPmColumnPattern->SetEnterIndex(1);
        }
        optionsTotalCount_[amPmColumn] = CHILD_WITHOUT_AMPM_SIZE;
        auto selectedHour = GetAmPmHour(selectedTime_.GetHour());
        for (uint32_t hour = 1; hour <= AM_PM_HOUR_12; ++hour) { // AM_PM hour start from 1 to 12
            if (hour == selectedHour) {
                hourColumnPattern->SetCurrentIndex(hour - 1);
                hourColumnPattern->SetEnterIndex(hour - 1);
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
    MinOrSecColumnBuilding(minuteColumn, GetPrefixMinute() == ZeroPrefixType::HIDE, selectedTime_.GetMinute());
    auto secondColumn = allChildNode_["second"].Upgrade();
    CHECK_NULL_VOID(secondColumn);
    MinOrSecColumnBuilding(secondColumn, GetPrefixSecond() == ZeroPrefixType::HIDE, selectedTime_.GetSecond());
}

void TimePickerRowPattern::MinOrSecColumnBuilding(
    const RefPtr<FrameNode>& columnFrameNode, bool isZeroPrefixTypeHide, uint32_t selectedTime)
{
    CHECK_NULL_VOID(columnFrameNode);
    auto columnPattern = columnFrameNode->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_VOID(columnPattern);
    optionsTotalCount_[columnFrameNode] = 0;

    for (uint32_t time = 0; time <= 59; ++time) { // time's minute or second from 0 to 59
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) && isZeroPrefixTypeHide) {
            options_[columnFrameNode][time] = std::to_string(time);
        } else {
            if (time < 10) { // time's minute or second less than 10
                options_[columnFrameNode][time] = std::string("0") + std::to_string(time);
            }
        }
        if (time == selectedTime) {
            columnPattern->SetCurrentIndex(time);
            columnPattern->SetEnterIndex(time);
        }
        optionsTotalCount_[columnFrameNode]++;
    }
    columnPattern->SetOptions(GetOptionsCount());
    columnPattern->SetWheelModeEnabled(wheelModeEnabled_);
}

void TimePickerRowPattern::RecordHourAndMinuteOptions()
{
    RecordHourOptions();
    RecordHourMinuteValues();
}

void TimePickerRowPattern::RecordHourOptions()
{
    uint32_t startHour = startTime_.GetHour();
    uint32_t endHour = endTime_.GetHour();
    definedAMHours_.clear();
    definedAMHours_.shrink_to_fit();
    definedPMHours_.clear();
    definedPMHours_.shrink_to_fit();
    defined24Hours_.clear();
    defined24Hours_.shrink_to_fit();
    if (GetHour24()) {
        for (uint32_t hour = startHour; hour <= endHour; ++hour) {
            defined24Hours_.emplace_back(GetHourFormatString(hour));
        }
    } else {
        bool isAmStart = IsAmHour(startHour);
        bool isAmEnd = IsAmHour(endHour);
        if (isAmStart && !isAmEnd) {
            // start time is in the morning and end time is in the afternoon
            for (uint32_t hour = startHour; hour <= AM_PM_HOUR_11; hour++) {
                definedAMHours_.emplace_back(GetHourFormatString(GetAmPmHour(hour)));
            }
            for (uint32_t hour = AM_PM_HOUR_12; hour <= endHour; hour++) {
                definedPMHours_.emplace_back(GetHourFormatString(GetAmPmHour(hour)));
            }
        } else if (isAmStart) {
            // both start time and end time are in the morning
            for (uint32_t hour = startHour; hour <= endHour; hour++) {
                definedAMHours_.emplace_back(GetHourFormatString(GetAmPmHour(hour)));
            }
        } else {
            // both start time and end time are in the afternoon
            for (uint32_t hour = startHour; hour <= endHour; hour++) {
                definedPMHours_.emplace_back(GetHourFormatString(GetAmPmHour(hour)));
            }
        }
    }
}

void TimePickerRowPattern::RecordHourMinuteValues()
{
    auto hourColumn = allChildNode_["hour"].Upgrade();
    CHECK_NULL_VOID(hourColumn);
    oldHourValue_ = GetOptionsCurrentValue(hourColumn);

    auto minuteColumn = allChildNode_["minute"].Upgrade();
    CHECK_NULL_VOID(minuteColumn);
    oldMinuteValue_ = GetOptionsCurrentValue(minuteColumn);
}

void TimePickerRowPattern::HandleHourColumnBuildingRange(const PickerTime& value)
{
    UpdateAllChildNode();
    uint32_t startHour = startTime_.GetHour();
    uint32_t endHour = endTime_.GetHour();
    auto amPmColumn = allChildNode_["amPm"].Upgrade();
    auto hourColumn = allChildNode_["hour"].Upgrade();
    optionsTotalCount_[hourColumn] = 0;
    if (GetHour24()) {
        CHECK_NULL_VOID(hourColumn);
        auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(hourColumnPattern);
        for (uint32_t hour = startHour; hour <= endHour; ++hour) {
            options_[hourColumn][hour - startHour] = GetHourFormatString(hour);
            if (hour == value.GetHour()) {
                hourColumnPattern->SetCurrentIndex(hour - startHour);
                hourColumnPattern->SetEnterIndex(hour - startHour);
            }
            optionsTotalCount_[hourColumn]++;
        }
        hourColumnPattern->SetOptions(GetOptionsCount());
        IsStartEndTimeDefined() ? hourColumnPattern->SetWheelModeEnabled(false)
                                : hourColumnPattern->SetWheelModeEnabled(wheelModeEnabled_);
        hourColumn->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    } else {
        HandleAmPmColumnBuilding(value);
    }
}

void TimePickerRowPattern::HandleAmPmColumnBuilding(const PickerTime& value)
{
    UpdateAllChildNode();
    auto amPmColumn = allChildNode_["amPm"].Upgrade();
    auto hourColumn = allChildNode_["hour"].Upgrade();
    CHECK_NULL_VOID(amPmColumn);
    CHECK_NULL_VOID(hourColumn);
    auto amPmColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_VOID(amPmColumnPattern);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_VOID(hourColumnPattern);
    options_[amPmColumn][INDEX_AM_0] = GetAmFormatString();
    options_[amPmColumn][INDEX_PM_1] = GetPmFormatString();

    if (IsAmHour(value.GetHour())) {
        amPmColumnPattern->SetCurrentIndex(0); // AM's index
        amPmColumnPattern->SetEnterIndex(0);
    } else {
        amPmColumnPattern->SetCurrentIndex(1); // PM's index
        amPmColumnPattern->SetEnterIndex(1);
    }
    optionsTotalCount_[amPmColumn] = CHILD_WITHOUT_AMPM_SIZE;
    if (startTime_.ToMinutes() == START_DEFAULT_TIME.ToMinutes() &&
        endTime_.ToMinutes() == END_DEFAULT_TIME.ToMinutes()) {
        auto selectedHour = GetAmPmHour(selectedTime_.GetHour());
        for (uint32_t hour = 1; hour <= AM_PM_HOUR_12; ++hour) {
            if (hour == selectedHour) {
                hourColumnPattern->SetCurrentIndex(hour - 1);
                hourColumnPattern->SetEnterIndex(hour - 1);
            }
            optionsTotalCount_[hourColumn]++;
        }
    } else {
        HandleAmPmColumnChange(value.GetHour());
    }
    amPmColumnPattern->SetOptions(GetOptionsCount());
    hourColumnPattern->SetOptions(GetOptionsCount());
    amPmColumnPattern->SetWheelModeEnabled(wheelModeEnabled_);
    IsStartEndTimeDefined() ? hourColumnPattern->SetWheelModeEnabled(false)
                            : hourColumnPattern->SetWheelModeEnabled(wheelModeEnabled_);
}

void TimePickerRowPattern::HandleAmPmColumnChange(uint32_t selectedHour)
{
    auto amPmColumn = allChildNode_["amPm"].Upgrade();
    auto hourColumn = allChildNode_["hour"].Upgrade();
    CHECK_NULL_VOID(amPmColumn);
    CHECK_NULL_VOID(hourColumn);
    uint32_t startHour = startTime_.GetHour();
    uint32_t endHour = endTime_.GetHour();
    bool isAmStart = IsAmHour(startHour);
    bool isAmEnd = IsAmHour(endHour);
    if (isAmStart && !isAmEnd) {
        endHour = ParseHourOf24(endHour);
        if (IsAmHour(selectedHour)) {
            endHour = AM_PM_HOUR_11;
        } else {
            startHour = 0;
        }
    } else {
        options_[amPmColumn][INDEX_AM_0] = isAmStart ? GetAmFormatString() : GetPmFormatString();
        optionsTotalCount_[amPmColumn] = 1;
        startHour = ParseHourOf24(startHour);
        endHour = ParseHourOf24(endHour);
    }
    HandleAmToPmHourColumnBuilding(selectedHour, startHour, endHour);
}

void TimePickerRowPattern::HandleAmToPmHourColumnBuilding(uint32_t selectedHour, uint32_t startHour, uint32_t endHour)
{
    auto hourColumn = allChildNode_["hour"].Upgrade();
    CHECK_NULL_VOID(hourColumn);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_VOID(hourColumnPattern);
    uint32_t selectedParseHour = ParseHourOf24(selectedHour);
    for (uint32_t hour = startHour; hour <= endHour; ++hour) {
        if (hour == 0) {
            options_[hourColumn][INDEX_HOUR_STRAT] = GetHourFormatString(AM_PM_HOUR_12);
        } else {
            options_[hourColumn][hour - startHour] = GetHourFormatString(hour);
        }
        if (hour == selectedParseHour) {
            hourColumnPattern->SetCurrentIndex(hour - startHour);
            hourColumnPattern->SetEnterIndex(hour - startHour);
        }
        optionsTotalCount_[hourColumn]++;
    }
}

void TimePickerRowPattern::HandleMinAndSecColumnBuildingRange()
{
    UpdateAllChildNode();
    HandleMinColumnChange(selectedTime_);
    UpdateSecondTimeRange();
    auto secondColumn = allChildNode_["second"].Upgrade();
    CHECK_NULL_VOID(secondColumn);
    auto secondColumnPattern = secondColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_VOID(secondColumnPattern);
    secondColumnPattern->SetCurrentIndex(selectedTime_.GetSecond());
    secondColumnPattern->SetEnterIndex(selectedTime_.GetSecond());
}

void TimePickerRowPattern::HandleMinColumnChange(const PickerTime& value)
{
    uint32_t startMinue = (startTime_.GetHour() == value.GetHour()) ? startTime_.GetMinute() : 0;
    uint32_t endMinute = (endTime_.GetHour() == value.GetHour()) ? endTime_.GetMinute() : 59;
    auto minuteColumn = allChildNode_["minute"].Upgrade();
    CHECK_NULL_VOID(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_VOID(minuteColumnPattern);
    optionsTotalCount_[minuteColumn] = 0;

    for (uint32_t minute = startMinue; minute <= endMinute; ++minute) {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) &&
            GetPrefixMinute() == ZeroPrefixType::HIDE) {
            options_[minuteColumn][minute - startMinue] = std::to_string(minute);
        } else {
            options_[minuteColumn][minute - startMinue] =
                (minute < MINUTE_10) ? std::string("0") + std::to_string(minute) : std::to_string(minute);
        }
        if (minute == value.GetMinute()) {
            minuteColumnPattern->SetCurrentIndex(minute - startMinue);
            minuteColumnPattern->SetEnterIndex(minute - startMinue);
        }
        optionsTotalCount_[minuteColumn]++;
    }
    minuteColumnPattern->SetOptions(GetOptionsCount());
    IsStartEndTimeDefined() ? minuteColumnPattern->SetWheelModeEnabled(false)
                            : minuteColumnPattern->SetWheelModeEnabled(wheelModeEnabled_);
}

void TimePickerRowPattern::SetSelectedTime(const PickerTime& value)
{
    selectedTime_ = AdjustTime(value);
    isFiredTimeChange_ = firedTimeStr_.has_value() && firedTimeStr_.value() == selectedTime_.ToString(true, hasSecond_);
    firedTimeStr_.reset();
}


PickerTime TimePickerRowPattern::AdjustTime(const PickerTime& time)
{
    if (time.ToMinutes() < startTime_.ToMinutes()) {
        return startTime_;
    }
    if (time.ToMinutes() > endTime_.ToMinutes()) {
        return endTime_;
    }
    return time;
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

uint32_t TimePickerRowPattern::ParseHourOf24(uint32_t hourOf24) const
{
    return (hourOf24 <= AM_PM_HOUR_11)? hourOf24 : (hourOf24 - AM_PM_HOUR_12);
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

void TimePickerRowPattern::SetDigitalCrownSensitivity(int32_t crownSensitivity)
{
#ifdef SUPPORT_DIGITAL_CROWN
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto&& children = host->GetChildren();
    for (const auto& child : children) {
        auto stackNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(stackNode);
        auto blendNode = DynamicCast<FrameNode>(stackNode->GetLastChild());
        CHECK_NULL_VOID(blendNode);
        auto childNode = DynamicCast<FrameNode>(blendNode->GetLastChild());
        CHECK_NULL_VOID(childNode);
        auto pickerColumnPattern = childNode->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(pickerColumnPattern);
        pickerColumnPattern->SetDigitalCrownSensitivity(crownSensitivity);
    }
#endif
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
    CHECK_EQUAL_VOID(childSize, 0);
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

    float paintRectWidth = columnWidth - FOCUS_INTERVAL.ConvertToPx() * RATE - LINE_WIDTH.ConvertToPx() * RATE;
    float paintRectHeight = dividerSpacing - FOCUS_INTERVAL.ConvertToPx() * RATE - LINE_WIDTH.ConvertToPx() * RATE;
    auto centerX = leftTotalColumnWidth + FOCUS_INTERVAL.ConvertToPx() + LINE_WIDTH.ConvertToPx();
    auto centerY = (host->GetGeometryNode()->GetFrameSize().Height() - dividerSpacing) / RATE +
        FOCUS_INTERVAL.ConvertToPx() + LINE_WIDTH.ConvertToPx();
    AdjustFocusBoxOffset(centerX);
    paintRect.SetRect(RectF(centerX, centerY, paintRectWidth, paintRectHeight));
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
}

void TimePickerRowPattern::AdjustFocusBoxOffset(double& centerX)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    if (geometryNode->GetPadding()) {
        centerX += geometryNode->GetPadding()->left.value_or(0.0);
    }
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
    if (NeedAdaptForAging() && !GetIsShowInDatePickerDialog()) {
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
    if (code == KeyCode::KEY_DPAD_UP) {
        pattern->StopHaptic();
        pattern->InnerHandleScroll(false, false);
        return true;
    }
    if (code == KeyCode::KEY_DPAD_DOWN) {
        pattern->StopHaptic();
        pattern->InnerHandleScroll(true, false);
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
    auto pickerTheme = context->GetTheme<PickerTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(pickerTheme);
    auto dialogTheme = context->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    auto disappearStyle = pickerTheme->GetDisappearOptionStyle();
    auto normalStyle = pickerTheme->GetOptionStyle(false, false);
    auto pickerProperty = host->GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_VOID(pickerProperty);
    pickerProperty->UpdateColor(
        GetTextProperties().normalTextStyle_.textColor.value_or(normalStyle.GetTextColor()));
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

bool TimePickerRowPattern::OnThemeScopeUpdate(int32_t themeScopeId)
{
    bool result = false;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, result);
    host->SetNeedCallChildrenUpdate(false);
    auto pickerProperty = host->GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_RETURN(pickerProperty, result);
    // The following three attributes will be affected by withTheme.
    // If they are setted by user, then use the value by user set; Otherwise use the value from withTheme
    // When the "result" is true, mean to notify the framework to Re-render
    if ((!pickerProperty->HasColor()) || (!pickerProperty->HasDisappearColor()) ||
        (!pickerProperty->HasSelectedColor())) {
        result = true;
    }
    OnModifyDone();
    return result;
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

void TimePickerRowPattern::UpdateUserSetSelectColor()
{
    CHECK_EQUAL_VOID(IsCircle(), false);
    isUserSetSelectColor_ = true;
    for (auto iter = allChildNode_.begin(); iter != allChildNode_.end(); iter++) {
        auto columnNode = iter->second.Upgrade();
        if (columnNode) {
            auto pattern = columnNode->GetPattern<TimePickerColumnPattern>();
            if (pattern) {
                pattern->UpdateUserSetSelectColor();
            }
        }
    }
}

Dimension TimePickerRowPattern::ConvertFontScaleValue(const Dimension& fontSizeValue)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, fontSizeValue);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);

    auto maxAppFontScale = pipeline->GetMaxAppFontScale();
    auto follow = pipeline->IsFollowSystem();
    float fontScale = pipeline->GetFontScale();
    if (NearZero(fontScale) || (fontSizeValue.Unit() == DimensionUnit::VP)) {
        return fontSizeValue;
    }
    if (GreatOrEqualCustomPrecision(fontScale, PICKER_MAXFONTSCALE) && follow) {
        fontScale = std::clamp(fontScale, 0.0f, maxAppFontScale);
        if (!NearZero(fontScale)) {
            return Dimension(fontSizeValue / fontScale);
        }
    }
    return fontSizeValue;
}

void TimePickerRowPattern::UpdateTextStyleCommon(
    const PickerTextStyle& textStyle,
    const TextStyle& defaultTextStyle,
    std::function<void(const Color&)> updateTextColorFunc,
    std::function<void(const Dimension&)> updateFontSizeFunc,
    std::function<void(const std::vector<std::string>&)> updateFontFamilyFunc
)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pickerProperty = GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_VOID(pickerProperty);

    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);

    if (pipelineContext->IsSystmColorChange()) {
        updateTextColorFunc(textStyle.textColor.value_or(defaultTextStyle.GetTextColor()));

        Dimension fontSize = defaultTextStyle.GetFontSize();
        if (textStyle.fontSize.has_value() && textStyle.fontSize->IsValid()) {
            fontSize = textStyle.fontSize.value();
        }
        updateFontSizeFunc(ConvertFontScaleValue(fontSize));

        updateFontFamilyFunc(textStyle.fontFamily.value_or(defaultTextStyle.GetFontFamilies()));
    }

    if (host->GetRerenderable()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void TimePickerRowPattern::UpdateDisappearTextStyle(const PickerTextStyle& textStyle)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(pickerTheme);
    auto defaultTextStyle = pickerTheme->GetDisappearOptionStyle();
    auto pickerProperty = GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_VOID(pickerProperty);
    UpdateTextStyleCommon(
        textStyle,
        defaultTextStyle,
        [&](const Color& color) { pickerProperty->UpdateDisappearColor(color); },
        [&](const Dimension& fontSize) { pickerProperty->UpdateDisappearFontSize(fontSize); },
        [&](const std::vector<std::string>& fontFamily) { pickerProperty->UpdateDisappearFontFamily(fontFamily); }
    );
}

void TimePickerRowPattern::UpdateNormalTextStyle(const PickerTextStyle& textStyle)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(pickerTheme);
    auto defaultTextStyle = pickerTheme->GetOptionStyle(false, false);
    auto pickerProperty = GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_VOID(pickerProperty);
    UpdateTextStyleCommon(
        textStyle,
        defaultTextStyle,
        [&](const Color& color) { pickerProperty->UpdateColor(color); },
        [&](const Dimension& fontSize) { pickerProperty->UpdateFontSize(fontSize); },
        [&](const std::vector<std::string>& fontFamily) { pickerProperty->UpdateFontFamily(fontFamily); }
    );
}

void TimePickerRowPattern::UpdateSelectedTextStyle(const PickerTextStyle& textStyle)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(pickerTheme);
    auto defaultTextStyle = pickerTheme->GetOptionStyle(true, false);
    auto pickerProperty = GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_VOID(pickerProperty);
    UpdateTextStyleCommon(
        textStyle,
        defaultTextStyle,
        [&](const Color& color) { pickerProperty->UpdateSelectedColor(color); },
        [&](const Dimension& fontSize) { pickerProperty->UpdateSelectedFontSize(fontSize); },
        [&](const std::vector<std::string>& fontFamily) { pickerProperty->UpdateSelectedFontFamily(fontFamily); }
    );
}

} // namespace OHOS::Ace::NG
