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

#include "base/i18n/date_time_sequence.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/picker/datepicker_column_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SINGLE_CHILD_SIZE = 1;
constexpr int32_t CHILD_SIZE = 3;
constexpr uint32_t MIN_MONTH = 1;
constexpr uint32_t MAX_MONTH = 12;
constexpr uint32_t MIN_DAY = 1;
const Dimension PRESS_INTERVAL = 4.0_vp;
const Dimension PRESS_RADIUS = 8.0_vp;
const int32_t UNOPTION_COUNT = 2;
const int32_t COLUMNS_SIZE = 3;
const int32_t COLUMNS_ZERO = 0;
const int32_t COLUMNS_ONE = 1;
const int32_t COLUMNS_TWO = 2;
const int32_t INDEX_YEAR = 0;
const int32_t INDEX_MONTH = 1;
const int32_t INDEX_DAY = 2;
constexpr float DISABLE_ALPHA = 0.6f;
const Dimension FOCUS_OFFSET = 2.0_vp;
const int32_t RATE = 2;
const int32_t MONTH_DECEMBER = 12;
constexpr int32_t RATIO_ZERO = 0;
constexpr int32_t RATIO_ONE = 1;
constexpr int32_t SECOND_PAGE = 1;
} // namespace
bool DatePickerPattern::inited_ = false;
const std::string DatePickerPattern::empty_;
const PickerDateF DatePickerPattern::emptyPickerDate_;
std::unordered_map<uint32_t, std::string> DatePickerPattern::years_;       // year from 1900 to 2100,count is 201
std::unordered_map<uint32_t, std::string> DatePickerPattern::solarMonths_; // solar month from 1 to 12,count is 12
std::unordered_map<uint32_t, std::string> DatePickerPattern::solarDays_;   // solar day from 1 to 31, count is 31
std::unordered_map<uint32_t, std::string> DatePickerPattern::lunarMonths_; // lunar month from 1 to 24, count is 24
std::unordered_map<uint32_t, std::string> DatePickerPattern::lunarDays_;   // lunar day from 1 to 30, count is 30
std::vector<std::string> DatePickerPattern::tagOrder_;    // order of year month day
std::vector<std::string> DatePickerPattern::localizedMonths_;

void DatePickerPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
    host->GetRenderContext()->UpdateClipEdge(true);
}

bool DatePickerPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    CHECK_NULL_RETURN(dirty, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, false);
    auto children = host->GetChildren();
    auto height = pickerTheme->GetDividerSpacing();
    auto buttonSpace = pickerTheme->GetSelectorItemSpace();
    auto currentFocusStackChild = DynamicCast<FrameNode>(host->GetChildAtIndex(focusKeyID_));
    CHECK_NULL_RETURN(currentFocusStackChild, false);
    auto currentFocusButtonNode = DynamicCast<FrameNode>(currentFocusStackChild->GetFirstChild());
    CHECK_NULL_RETURN(currentFocusButtonNode, false);
    for (const auto& child : children) {
        auto columnNode = DynamicCast<FrameNode>(child->GetLastChild()->GetLastChild());
        CHECK_NULL_RETURN(columnNode, false);
        auto width = columnNode->GetGeometryNode()->GetFrameSize().Width();
        auto datePickerColumnNode = DynamicCast<FrameNode>(child->GetLastChild());
        CHECK_NULL_RETURN(datePickerColumnNode, false);
        auto buttonNode = DynamicCast<FrameNode>(child->GetFirstChild());
        CHECK_NULL_RETURN(buttonNode, false);
        auto buttonConfirmLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        buttonConfirmLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
        buttonConfirmLayoutProperty->UpdateType(ButtonType::NORMAL);
        buttonConfirmLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(selectorItemRadius_));
        auto standardButtonHeight = static_cast<float>((height - PRESS_INTERVAL).ConvertToPx());
        auto maxButtonHeight = static_cast<float>(datePickerColumnNode->GetGeometryNode()->GetFrameSize().Height());
        auto buttonHeight = Dimension(std::min(standardButtonHeight, maxButtonHeight), DimensionUnit::PX);
        buttonConfirmLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(width - buttonSpace.ConvertToPx()), CalcLength(buttonHeight)));
        auto buttonConfirmRenderContext = buttonNode->GetRenderContext();
        if (!useButtonFocusArea_) {
            buttonConfirmRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        } else {
            auto isFocusButton = haveFocus_ && (currentFocusButtonNode == buttonNode);
            UpdateColumnButtonStyles(columnNode, isFocusButton, false);
        }
        buttonNode->MarkModifyDone();
        buttonNode->MarkDirtyNode();
        if (GetIsShowInDialog() && GreatNotEqual(standardButtonHeight, maxButtonHeight) &&
            GreatNotEqual(maxButtonHeight, 0.0f)) {
            auto parentNode = DynamicCast<FrameNode>(host->GetParent());
            CHECK_NULL_RETURN(parentNode, false);
            parentNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
        }
    }
    return true;
}

void DatePickerPattern::InitSelectorProps()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);

    selectorItemRadius_ = pickerTheme->GetSelectorItemRadius();
    useButtonFocusArea_ = pickerTheme->NeedButtonFocusAreaType();
}

void DatePickerPattern::InitFocusEvent()
{
    CHECK_NULL_VOID(!focusEventInitialized_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto focusTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleFocusEvent();
    };
    focusHub->SetOnFocusInternal(focusTask);

    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurEvent();
    };
    focusHub->SetOnBlurInternal(blurTask);

    focusEventInitialized_ = true;
}

void DatePickerPattern::AddIsFocusActiveUpdateEvent()
{
    if (!isFocusActiveUpdateEvent_) {
        isFocusActiveUpdateEvent_ = [weak = WeakClaim(this)](bool isFocusAcitve) {
            auto pickerPattern = weak.Upgrade();
            CHECK_NULL_VOID(pickerPattern);
            pickerPattern->SetHaveFocus(isFocusAcitve);
            pickerPattern->UpdateFocusButtonState();
        };
    }

    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->AddIsFocusActiveUpdateEvent(GetHost(), isFocusActiveUpdateEvent_);
}

void DatePickerPattern::RemoveIsFocusActiveUpdateEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveIsFocusActiveUpdateEvent(host);
}

void DatePickerPattern::SetHaveFocus(bool haveFocus)
{
    haveFocus_ = haveFocus;
}

void DatePickerPattern::HandleFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);

    AddIsFocusActiveUpdateEvent();
    if (context->GetIsFocusActive()) {
        SetHaveFocus(true);
        UpdateFocusButtonState();
    }
}

void DatePickerPattern::HandleBlurEvent()
{
    SetHaveFocus(false);
    RemoveIsFocusActiveUpdateEvent();
    UpdateFocusButtonState();
}

void DatePickerPattern::UpdateFocusButtonState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (useButtonFocusArea_) {
        auto currentFocusStackNode = DynamicCast<FrameNode>(host->GetChildAtIndex(focusKeyID_));
        CHECK_NULL_VOID(currentFocusStackNode);
        auto blendColumnNode = currentFocusStackNode->GetLastChild();
        CHECK_NULL_VOID(blendColumnNode);
        auto currentFocusColumnNode = DynamicCast<FrameNode>(blendColumnNode->GetLastChild());
        CHECK_NULL_VOID(currentFocusColumnNode);

        UpdateColumnButtonStyles(currentFocusColumnNode, haveFocus_, true);
    }
}

void DatePickerPattern::UpdateColumnButtonStyles(
    const RefPtr<FrameNode>& columnNode, bool haveFocus, bool needMarkDirty)
{
    CHECK_NULL_VOID(columnNode);

    auto datePickerColumnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(datePickerColumnPattern);
    datePickerColumnPattern->UpdateColumnButtonFocusState(haveFocus, needMarkDirty);
}

void DatePickerPattern::GetInnerFocusButtonPaintRect(RoundRect& paintRect, float focusButtonXOffset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto stackNode = DynamicCast<FrameNode>(host->GetChildAtIndex(focusKeyID_));
    CHECK_NULL_VOID(stackNode);
    auto buttonNode = DynamicCast<FrameNode>(stackNode->GetFirstChild());
    CHECK_NULL_VOID(buttonNode);
    auto focusButtonRect = buttonNode->GetGeometryNode()->GetFrameRect();
    auto focusSpace = pickerTheme->GetFocusPadding().ConvertToPx();
    auto stackRenderContext = stackNode->GetRenderContext();
    CHECK_NULL_VOID(stackRenderContext);
    auto leftPadding = 0.0f;
    if (geometryNode->GetPadding()) {
        leftPadding = geometryNode->GetPadding()->left.value_or(0.0f);
    }
    focusButtonRect -=
        OffsetF(focusSpace - leftPadding, focusSpace - stackRenderContext->GetPaintRectWithoutTransform().GetY());
    focusButtonRect += SizeF(focusSpace + focusSpace, focusSpace + focusSpace);
    focusButtonRect += OffsetF(focusButtonXOffset, 0);

    paintRect.SetRect(focusButtonRect);
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS,
        static_cast<RSScalar>(selectorItemRadius_.ConvertToPx()),
        static_cast<RSScalar>(selectorItemRadius_.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS,
        static_cast<RSScalar>(selectorItemRadius_.ConvertToPx()),
        static_cast<RSScalar>(selectorItemRadius_.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS,
        static_cast<RSScalar>(selectorItemRadius_.ConvertToPx()),
        static_cast<RSScalar>(selectorItemRadius_.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS,
        static_cast<RSScalar>(selectorItemRadius_.ConvertToPx()),
        static_cast<RSScalar>(selectorItemRadius_.ConvertToPx()));
}

void DatePickerPattern::ColumnPatternInitHapticController()
{
    if (!isHapticChanged_) {
        return;
    }
    isHapticChanged_ = false;
    auto frameNodes = GetAllChildNode();
    for (auto iter : frameNodes) {
        auto columnNode = iter.second;
        if (!columnNode) {
            continue;
        }
        auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
        if (!columnPattern) {
            continue;
        }
        columnPattern->InitHapticController();
    }
}

void DatePickerPattern::ColumnPatternInitHapticController(const RefPtr<FrameNode>& columnNode)
{
    CHECK_NULL_VOID(columnNode);
    if (!isHapticChanged_) {
        return;
    }
    isHapticChanged_ = false;
    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(columnPattern);
    columnPattern->InitHapticController();
}

void DatePickerPattern::OnModifyDone()
{
    Pattern::CheckLocalized();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto datePickerRowLayoutProperty = host->GetLayoutProperty<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(datePickerRowLayoutProperty);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
        ColumnPatternInitHapticController();
        isHapticChanged_ = false;
    }
    if (isFiredDateChange_ && !isForceUpdate_ && (lunar_ == datePickerRowLayoutProperty->GetLunar().value_or(false))) {
        isFiredDateChange_ = false;
        return;
    }

    isForceUpdate_ = false;
    InitDisabled();
    if (ShowMonthDays()) {
        FlushMonthDaysColumn();
    } else {
        FlushColumn();
    }
    ShowTitle(GetTitleId());
    SetChangeCallback([weak = WeakClaim(this)](const RefPtr<FrameNode>& tag, bool add, uint32_t index, bool notify) {
        auto refPtr = weak.Upgrade();
        CHECK_NULL_VOID(refPtr);
        refPtr->HandleColumnChange(tag, add, index, notify);
    });
    SetEventCallback([weak = WeakClaim(this), titleId = GetTitleId()](bool refresh) {
        auto refPtr = weak.Upgrade();
        CHECK_NULL_VOID(refPtr);
        refPtr->FireChangeEvent(refresh);
        if (refresh) {
            refPtr->ShowTitle(titleId);
        }
    });
    auto focusHub = host->GetFocusHub();
    if (focusHub) {
        InitOnKeyEvent(focusHub);
    }
    InitFocusEvent();
    InitSelectorProps();
}

void DatePickerPattern::InitDisabled()
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
    } else if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
        renderContext->UpdateOpacity(curOpacity_);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void DatePickerPattern::UpdateConfirmButtonMargin(
    const RefPtr<FrameNode>& buttonConfirmNode, const RefPtr<DialogTheme>& dialogTheme)
{
    MarginProperty margin;
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        DialogTypeMargin::UpdateDialogMargin(isRtl, margin, dialogTheme, true, ModuleDialogType::DATEPICKER_DIALOG);
    } else {
        DialogTypeMargin::UpdateDialogMargin(isRtl, margin, dialogTheme, false, ModuleDialogType::DATEPICKER_DIALOG);
    }
    buttonConfirmNode->GetLayoutProperty()->UpdateMargin(margin);
}

void DatePickerPattern::UpdateCancelButtonMargin(
    const RefPtr<FrameNode>& buttonCancelNode, const RefPtr<DialogTheme>& dialogTheme)
{
    MarginProperty margin;
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        DialogTypeMargin::UpdateDialogMargin(!isRtl, margin, dialogTheme, true, ModuleDialogType::DATEPICKER_DIALOG);
    } else {
        DialogTypeMargin::UpdateDialogMargin(!isRtl, margin, dialogTheme, false,
            ModuleDialogType::DATEPICKER_DIALOG);
    }
    buttonCancelNode->GetLayoutProperty()->UpdateMargin(margin);
}

void DatePickerPattern::OnFontConfigurationUpdate()
{
    CHECK_NULL_VOID(closeDialogEvent_);
    closeDialogEvent_();
}

void DatePickerPattern::OnFontScaleConfigurationUpdate()
{
    CHECK_NULL_VOID(closeDialogEvent_);
    closeDialogEvent_();
}

void DatePickerPattern::OnLanguageConfigurationUpdate()
{
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

    auto lunarSwitchNode = weakLunarSwitchText_.Upgrade();
    CHECK_NULL_VOID(lunarSwitchNode);
    auto lunarSwitchTextLayoutProperty = lunarSwitchNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(lunarSwitchTextLayoutProperty);
    lunarSwitchTextLayoutProperty->UpdateContent(
        Localization::GetInstance()->GetEntryLetters("datepicker.lunarSwitch"));
    lunarSwitchNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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
        auto iter = std::find_if(datePickerColumns_.begin(), datePickerColumns_.end(), [&tag](const auto& c) {
            auto column = c.Upgrade();
            return column && column->GetId() == tag->GetId();
        });
        if (iter != datePickerColumns_.end()) {
            auto datePickerColumn = (*iter).Upgrade();
            CHECK_NULL_VOID(datePickerColumn);
            auto datePickerColumnPattern = datePickerColumn->GetPattern<DatePickerColumnPattern>();
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
        auto blendNode = DynamicCast<FrameNode>(stackNode->GetLastChild());
        CHECK_NULL_VOID(blendNode);
        auto childNode = blendNode->GetLastChild();
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
        auto blendNode = DynamicCast<FrameNode>(stackNode->GetLastChild());
        CHECK_NULL_VOID(blendNode);
        auto childNode = blendNode->GetLastChild();
        CHECK_NULL_VOID(childNode);
        auto datePickerColumnPattern = DynamicCast<FrameNode>(childNode)->GetPattern<DatePickerColumnPattern>();
        CHECK_NULL_VOID(datePickerColumnPattern);
        datePickerColumnPattern->SetChangeCallback(std::move(value));
    }
}

void DatePickerPattern::OnColorConfigurationUpdate()
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
    auto pickerProperty = host->GetLayoutProperty<DataPickerRowLayoutProperty>();
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
    auto titleLayoutRenderContext = buttonTitleNode->GetRenderContext();
    CHECK_NULL_VOID(titleLayoutRenderContext);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) ||
        !titleLayoutRenderContext->IsUniRenderEnabled()) {
        titleLayoutRenderContext->UpdateBackgroundColor(dialogTheme->GetButtonBackgroundColor());
    }
    UpdateTitleTextColor(buttonTitleNode, pickerTheme);
    OnModifyDone();
}

bool DatePickerPattern::OnThemeScopeUpdate(int32_t themeScopeId)
{
    bool result = false;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, result);
    host->SetNeedCallChildrenUpdate(false);
    auto pickerProperty = host->GetLayoutProperty<DataPickerRowLayoutProperty>();
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

void DatePickerPattern::UpdateTitleTextColor(
    const RefPtr<FrameNode>& buttonTitleNode, const RefPtr<PickerTheme>& pickerTheme)
{
    auto childButton = buttonTitleNode->GetFirstChild();
    CHECK_NULL_VOID(childButton);
    auto ButtonNode = DynamicCast<FrameNode>(childButton);
    CHECK_NULL_VOID(ButtonNode);
    auto buttonTitleRenderContext = ButtonNode->GetRenderContext();
    CHECK_NULL_VOID(buttonTitleRenderContext);
    buttonTitleRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    auto childColumn = ButtonNode->GetFirstChild();
    CHECK_NULL_VOID(childColumn);
    auto childText = childColumn->GetFirstChild();
    CHECK_NULL_VOID(childText);
    auto textTitleNode = DynamicCast<FrameNode>(childText);
    CHECK_NULL_VOID(textTitleNode);
    auto textLayoutProperty = textTitleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateTextColor(pickerTheme->GetTitleStyle().GetTextColor());
    if (childColumn->GetChildren().size() > 1) {
        auto spinner = childColumn->GetLastChild();
        CHECK_NULL_VOID(spinner);
        auto spinnerNode = DynamicCast<FrameNode>(spinner);
        CHECK_NULL_VOID(spinnerNode);
        auto spinnerRenderProperty = spinnerNode->GetPaintProperty<ImageRenderProperty>();
        CHECK_NULL_VOID(spinnerRenderProperty);
        spinnerRenderProperty->UpdateSvgFillColor(pickerTheme->GetTitleStyle().GetTextColor());
    }
}

void DatePickerPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
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
    UpdateFocusButtonState();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void DatePickerPattern::CalcLeftTotalColumnWidth(
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

void DatePickerPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childSize = 1.0f;
    if (!ShowMonthDays()) {
        childSize = static_cast<float>(host->GetChildren().size());
    }
    auto leftTotalColumnWidth = 0.0f;
    CalcLeftTotalColumnWidth(host, leftTotalColumnWidth, childSize);
    auto stackChild = DynamicCast<FrameNode>(host->GetChildAtIndex(focusKeyID_));
    CHECK_NULL_VOID(stackChild);
    auto blendChild = DynamicCast<FrameNode>(stackChild->GetLastChild());
    CHECK_NULL_VOID(blendChild);
    auto pickerChild = DynamicCast<FrameNode>(blendChild->GetLastChild());
    CHECK_NULL_VOID(pickerChild);
    auto columnWidth = pickerChild->GetGeometryNode()->GetFrameSize().Width();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    if (useButtonFocusArea_) {
        return GetInnerFocusButtonPaintRect(paintRect, leftTotalColumnWidth);
    }
    auto dividerSpacing = pickerTheme->GetDividerSpacing().ConvertToPx();
    auto pickerThemeWidth = dividerSpacing * RATE;

    auto centerX = (columnWidth - pickerThemeWidth)/ RATE + leftTotalColumnWidth + PRESS_INTERVAL.ConvertToPx();
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

bool DatePickerPattern::OnKeyEvent(const KeyEvent& event)
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

bool DatePickerPattern::CheckFocusID(int32_t childSize)
{
    if (focusKeyID_ > childSize - 1) {
        focusKeyID_ = childSize - 1;
        return false;
    }

    if (NeedAdaptForAging()) {
        if (GetCurrentPage() == SECOND_PAGE) {
            if (focusKeyID_ < INDEX_MONTH) {
                focusKeyID_ = INDEX_MONTH;
                return false;
            }
        } else {
            if (focusKeyID_ != INDEX_YEAR) {
                focusKeyID_ = INDEX_YEAR;
                return false;
            }
        }
    } else {
        if (focusKeyID_ < INDEX_YEAR) {
            focusKeyID_ = INDEX_YEAR;
            return false;
        }
    }
    return true;
}

bool DatePickerPattern::ParseDirectionKey(
    RefPtr<DatePickerColumnPattern>& pattern, KeyCode& code, uint32_t totalOptionCount, int32_t childSize)
{
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (code == KeyCode::KEY_DPAD_UP) {
        pattern->InnerHandleScroll(false, false);
        return true;
    }
    if (code == KeyCode::KEY_DPAD_DOWN) {
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
        if (ShowMonthDays()) {
            childSize = 1;
        }
        if (!CheckFocusID(childSize)) {
            return false;
        }
        PaintFocusState();
        return true;
    }
    return false;
}

bool DatePickerPattern::HandleDirectionKey(KeyCode code)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto stackChild = DynamicCast<FrameNode>(host->GetChildAtIndex(focusKeyID_));
    CHECK_NULL_RETURN(stackChild, false);
    auto childSize = host->GetChildren().size();
    auto pickerChild = DynamicCast<FrameNode>(stackChild->GetLastChild()->GetLastChild());
    CHECK_NULL_RETURN(pickerChild, false);
    auto pattern = pickerChild->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto totalOptionCount = GetOptionCount(pickerChild);
    if (totalOptionCount == 0) {
        return false;
    }
    return ParseDirectionKey(pattern, code, totalOptionCount, static_cast<int32_t>(childSize));
}

std::unordered_map<std::string, RefPtr<FrameNode>> DatePickerPattern::GetAllChildNode()
{
    std::unordered_map<std::string, RefPtr<FrameNode>> allChildNode;
    RefPtr<FrameNode> stackYear;
    RefPtr<FrameNode> stackMonth;
    RefPtr<FrameNode> stackDay;
    OrderAllChildNode(stackYear, stackMonth, stackDay);
    CHECK_NULL_RETURN(stackYear, allChildNode);
    CHECK_NULL_RETURN(stackMonth, allChildNode);
    CHECK_NULL_RETURN(stackDay, allChildNode);
    auto blendYear = DynamicCast<FrameNode>(stackYear->GetLastChild());
    CHECK_NULL_RETURN(blendYear, allChildNode);
    auto blendMonth = DynamicCast<FrameNode>(stackMonth->GetLastChild());
    CHECK_NULL_RETURN(blendMonth, allChildNode);
    auto blendDay = DynamicCast<FrameNode>(stackDay->GetLastChild());
    CHECK_NULL_RETURN(blendDay, allChildNode);
    auto yearNode = DynamicCast<FrameNode>(blendYear->GetLastChild());
    CHECK_NULL_RETURN(yearNode, allChildNode);
    auto monthNode = DynamicCast<FrameNode>(blendMonth->GetLastChild());
    CHECK_NULL_RETURN(monthNode, allChildNode);
    auto dayNode = DynamicCast<FrameNode>(blendDay->GetLastChild());
    CHECK_NULL_RETURN(dayNode, allChildNode);
    allChildNode["year"] = yearNode;
    allChildNode["month"] = monthNode;
    allChildNode["day"] = dayNode;
    return allChildNode;
}

void DatePickerPattern::OrderAllChildNode(
    RefPtr<FrameNode>& stackYear, RefPtr<FrameNode>& stackMonth, RefPtr<FrameNode>& stackDay)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    if (children.size() != CHILD_SIZE) {
        return;
    }

    auto processDateNode = [&children](RefPtr<UINode>& first, RefPtr<UINode>& second, RefPtr<UINode>& third) {
        auto iter = children.begin();
        first = *iter++;
        CHECK_NULL_VOID(first);
        second = *iter++;
        CHECK_NULL_VOID(second);
        third = *iter;
        CHECK_NULL_VOID(third);
    };

    RefPtr<UINode> year;
    RefPtr<UINode> month;
    RefPtr<UINode> day;
    if (dateOrder_ == "M-d-y") {
        processDateNode(month, day, year);
    } else if (dateOrder_ == "y-d-M") {
        processDateNode(year, day, month);
    } else {
        processDateNode(year, month, day);
    }
    stackYear = DynamicCast<FrameNode>(year);
    stackMonth = DynamicCast<FrameNode>(month);
    stackDay = DynamicCast<FrameNode>(day);
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
    std::string language = Localization::GetInstance()->GetLanguage();
    if (dataPickerRowLayoutProperty->GetLunar().value_or(false) && (strcmp(language.c_str(), "zh") == 0)) {
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
    yearNode->MarkModifyDone();
    monthNode->MarkModifyDone();
    dayNode->MarkModifyDone();
    yearNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    monthNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    dayNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    ShowColumnByDatePickMode();
}

void DatePickerPattern::ShowColumnByDatePickMode()
{
    RefPtr<FrameNode> stackYear;
    RefPtr<FrameNode> stackMonth;
    RefPtr<FrameNode> stackDay;
    OrderAllChildNode(stackYear, stackMonth, stackDay);
    CHECK_NULL_VOID(stackYear);
    CHECK_NULL_VOID(stackMonth);
    CHECK_NULL_VOID(stackDay);

    if (datePickerMode_ == DatePickerMode::DATE) {
        UpdateStackPropVisibility(stackYear, VisibleType::VISIBLE, RATIO_ONE);
        UpdateStackPropVisibility(stackMonth, VisibleType::VISIBLE, RATIO_ONE);
        UpdateStackPropVisibility(stackDay, VisibleType::VISIBLE, RATIO_ONE);
    } else if (datePickerMode_ == DatePickerMode::YEAR_AND_MONTH) {
        UpdateStackPropVisibility(stackYear, VisibleType::VISIBLE, RATIO_ONE);
        UpdateStackPropVisibility(stackMonth, VisibleType::VISIBLE, RATIO_ONE);
        UpdateStackPropVisibility(stackDay, VisibleType::GONE, RATIO_ZERO);
    } else if (datePickerMode_ == DatePickerMode::MONTH_AND_DAY) {
        UpdateStackPropVisibility(stackYear, VisibleType::GONE, RATIO_ZERO);
        UpdateStackPropVisibility(stackMonth, VisibleType::VISIBLE, RATIO_ONE);
        UpdateStackPropVisibility(stackDay, VisibleType::VISIBLE, RATIO_ONE);
    }
}

void DatePickerPattern::UpdateStackPropVisibility(const RefPtr<FrameNode>& stackNode,
    const VisibleType visibleType, const int32_t weight)
{
    for (const auto& child : stackNode->GetChildren()) {
        auto frameNodeChild = AceType::DynamicCast<NG::FrameNode>(child);
        CHECK_NULL_VOID(frameNodeChild);
        auto layoutProperty = frameNodeChild->GetLayoutProperty();
        layoutProperty->UpdateVisibility(visibleType);
    }
    auto stackNodeLayoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(stackNodeLayoutProperty);
    if ((datePickerMode_ != DatePickerMode::DATE) || !GetIsShowInDialog()) {
        stackNodeLayoutProperty->UpdateLayoutWeight(weight);
    }
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
    auto blendMonthDays = DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    CHECK_NULL_VOID(blendMonthDays);
    auto monthDaysNode = DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    auto stackYear = DynamicCast<FrameNode>(year);
    auto blendYear = DynamicCast<FrameNode>(stackYear->GetLastChild());
    CHECK_NULL_VOID(blendYear);
    auto yearDaysNode = DynamicCast<FrameNode>(blendYear->GetLastChild());
    CHECK_NULL_VOID(monthDaysNode);
    CHECK_NULL_VOID(yearDaysNode);
    auto dataPickerRowLayoutProperty = host->GetLayoutProperty<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(dataPickerRowLayoutProperty);
    std::string language = Localization::GetInstance()->GetLanguage();
    if (dataPickerRowLayoutProperty->GetLunar().value_or(false) && (strcmp(language.c_str(), "zh") == 0)) {
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
    monthDaysNode->MarkModifyDone();
    yearDaysNode->MarkModifyDone();
    monthDaysNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    yearDaysNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

bool DatePickerPattern::ReportDateChangeEvent(int32_t nodeId, const std::string& compName,
    const std::string& eventName, const std::string& eventData)
{
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
    auto dataJson = JsonUtil::ParseJsonString(eventData);
    CHECK_NULL_RETURN(dataJson, false);
    auto value = InspectorJsonUtil::Create();
    CHECK_NULL_RETURN(value, false);
    value->Put(compName.c_str(), eventName.c_str());
    value->Put("year", dataJson->GetUInt("year"));
    value->Put("month", dataJson->GetUInt("month") + 1); // month: 1-12
    value->Put("day", dataJson->GetUInt("day"));
    value->Put("hour", dataJson->GetUInt("hour"));
    value->Put("minute", dataJson->GetUInt("minute"));
    UiSessionManager::GetInstance().ReportComponentChangeEvent(nodeId, "event", value);
#endif
    return true;
}

bool DatePickerPattern::ReportDateChangeEvent(const std::string& compName,
    const std::string& eventName, const std::string& eventData)
{
    auto datePickerEventHub = GetEventHub<DatePickerEventHub>();
    if ((datePickerEventHub != nullptr) && datePickerEventHub->HasSetDialogChange()) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    return ReportDateChangeEvent(host->GetId(), compName, eventName, eventData);
}

void DatePickerPattern::FireChangeEvent(bool refresh)
{
    if (refresh) {
        ReportDateChangeEvent("DatePicker", "onDateChange", GetSelectedObject(true));
        auto datePickerEventHub = GetEventHub<DatePickerEventHub>();
        CHECK_NULL_VOID(datePickerEventHub);
        auto str = GetSelectedObject(true);
        auto info = std::make_shared<DatePickerChangeEvent>(str);
        datePickerEventHub->FireChangeEvent(info.get());
        datePickerEventHub->FireDialogChangeEvent(str);
        firedDateStr_ = str;
    }
}

void DatePickerPattern::ShowTitle(int32_t titleId)
{
    if (HasTitleNode() && isFocus_) {
        auto textTitleNode = FrameNode::GetOrCreateFrameNode(
            V2::TEXT_ETS_TAG, titleId, []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_VOID(textTitleNode);
        auto textLayoutProperty = textTitleNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);

        if (ShowMonthDays() || (datePickerMode_ == DatePickerMode::DATE)) {
            auto dateStr = GetCurrentDate();
            textLayoutProperty->UpdateContent(dateStr.ToString(false));
        } else {
            auto dateStr = GetVisibleColumnsText();
            textLayoutProperty->UpdateContent(dateStr);
        }
        textTitleNode->MarkModifyDone();
        textTitleNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

std::string DatePickerPattern::GetVisibleColumnsText()
{
    std::string result = "";
    auto allChildNode = GetAllChildNode();
    auto yearNode = allChildNode["year"];
    auto monthNode = allChildNode["month"];
    auto dayNode = allChildNode["day"];
    CHECK_NULL_RETURN(yearNode, "");
    CHECK_NULL_RETURN(monthNode, "");
    CHECK_NULL_RETURN(dayNode, "");
    if (datePickerMode_ == DatePickerMode::YEAR_AND_MONTH) {
        GetColumnText(yearNode, result);
    }
    GetColumnText(monthNode, result);
    if (datePickerMode_ == DatePickerMode::MONTH_AND_DAY) {
        GetColumnText(dayNode, result);
    }
    return result;
}

void DatePickerPattern::GetColumnText(const RefPtr<FrameNode>& columnNode, std::string& result)
{
    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(columnPattern);
    auto index = columnPattern->GetCurrentIndex();
    auto options = columnPattern->GetOptions();
    auto it = options.find(columnNode);
    if (it != options.end() && index >= 0 && index < it->second.size()) {
        auto date = it->second.at(index);
        result.append(GetFormatString(date));
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
    auto blendMonthDays = DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    CHECK_NULL_VOID(blendMonthDays);
    auto monthDaysNode = DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    if (tag != monthDaysNode) {
        return;
    }

    if (IsShowLunar()) {
        HandleLunarMonthDaysChange(isAdd, index);
    } else {
        HandleSolarMonthDaysChange(isAdd, index);
    }

    resultTags.emplace_back(monthDaysNode);
}

std::string DatePickerPattern::GetSelectedObject(bool isColumnChange, int status) const
{
    auto date = selectedDate_;
    if (isColumnChange) {
        date = GetCurrentDate();
    }
    // W3C's month is between 0 to 11, need to reduce one.
    auto getMonth = date.GetMonth();
    getMonth = getMonth > 0 ? getMonth - 1 : 0;
    date.SetMonth(getMonth);

    auto dateTimeString = std::string("{\"year\":") + std::to_string(date.GetYear()) +
                          ",\"month\":" + std::to_string(date.GetMonth()) + ",\"day\":" + std::to_string(date.GetDay());
    auto pickTime = PickerTime::Current();
    if (showTime_) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, date.ToString(true, status));
        if (showMonthDays_) {
            auto pickerRow = host->GetParent();
            CHECK_NULL_RETURN(pickerRow, date.ToString(true, status));
            auto timeNode = AceType::DynamicCast<FrameNode>(pickerRow->GetChildAtIndex(1));
            CHECK_NULL_RETURN(timeNode, date.ToString(true, status));
            auto timePickerPattern = timeNode->GetPattern<TimePickerRowPattern>();
            CHECK_NULL_RETURN(timePickerPattern, date.ToString(true, status));
            pickTime = timePickerPattern->GetCurrentTime();
        } else {
            auto pickerStack = host->GetParent();
            CHECK_NULL_RETURN(pickerStack, date.ToString(true, status));
            auto pickerRow = pickerStack->GetLastChild();
            CHECK_NULL_RETURN(pickerRow, date.ToString(true, status));
            auto timeNode = AceType::DynamicCast<FrameNode>(pickerRow->GetChildAtIndex(1));
            CHECK_NULL_RETURN(timeNode, date.ToString(true, status));
            auto timePickerPattern = timeNode->GetPattern<TimePickerRowPattern>();
            CHECK_NULL_RETURN(timePickerPattern, date.ToString(true, status));
            pickTime = timePickerPattern->GetCurrentTime();
        }
    }
    dateTimeString += std::string(",\"hour\":") + std::to_string(pickTime.GetHour()) +
                      ",\"minute\":" + std::to_string(pickTime.GetMinute()) + ",\"status\":" + std::to_string(status) +
                      "}";
    return dateTimeString;
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
    CHECK_NULL_VOID(yearDatePickerColumnPattern);
    CHECK_NULL_VOID(monthDatePickerColumnPattern);
    CHECK_NULL_VOID(dayDatePickerColumnPattern);

    auto date = GetCurrentDate();
    if (isAdd && index == 0) {
        IncreaseLinkageYearMonth(date);
    }
    auto getOptionCount = GetOptionCount(dayNode);
    getOptionCount = getOptionCount > 0 ? getOptionCount - 1 : 0;
    if (!isAdd &&
        dayDatePickerColumnPattern->GetCurrentIndex() == getOptionCount) { // last index is count - 1
        ReduceLinkageYearMonth(date);
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

void DatePickerPattern::IncreaseLinkageYearMonth(PickerDate& date)
{
    date.SetMonth(date.GetMonth() + 1); // add to next month
    if (date.GetMonth() > 12) {         // invalidate month, max month is 12
        date.SetMonth(1);               // first month is 1
        if (datePickerMode_ != DatePickerMode::MONTH_AND_DAY) {
            date.SetYear(date.GetYear() + 1); // add to next year
            if (date.GetYear() > endDateSolar_.GetYear()) {
                date.SetYear(startDateSolar_.GetYear());
            }
        }
    }
}

void DatePickerPattern::ReduceLinkageYearMonth(PickerDate& date)
{
    auto getMonth = date.GetMonth();
    getMonth = getMonth > 0 ? getMonth - 1 : 0;
    date.SetMonth(getMonth);           // reduce to previous month
    if (date.GetMonth() == 0) {        // min month is 1, invalidate
        date.SetMonth(MONTH_DECEMBER); // set to be the last month
        if (datePickerMode_ != DatePickerMode::MONTH_AND_DAY) {
            auto getYear = date.GetYear();
            getYear = getYear > 0 ? getYear - 1 : 0;
            date.SetYear(getYear); // reduce to previous year
            if (date.GetYear() < startDateSolar_.GetYear()) {
                date.SetYear(endDateSolar_.GetYear());
            }
        }
    }
    date.SetDay(PickerDate::GetMaxDay(date.GetYear(), date.GetMonth())); // reduce to previous month's last day
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
    auto getOptionCount = GetOptionCount(dayNode);
    getOptionCount = getOptionCount > 0 ? getOptionCount - 1 : 0;
    if (dayDatePickerColumnPattern->GetCurrentIndex() == getOptionCount) { // max index is count - 1
        if (monthDatePickerColumnPattern->GetCurrentIndex() == 0) {
            lunarDate.year = lunarDate.year > 0 ? lunarDate.year - 1 : 0; // reduce to previous year
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
        auto getOptionCount = GetOptionCount(monthNode);
        getOptionCount = getOptionCount > 0 ? getOptionCount - 1 : 0;
        if (monthDatePickerColumnPattern->GetCurrentIndex() == getOptionCount) {     // max index is count - 1
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
    auto blendMonthDays = DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    CHECK_NULL_VOID(blendMonthDays);
    auto monthDaysNode = DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
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
    auto getOptionCount = GetOptionCount(monthDaysNode);
    getOptionCount = getOptionCount > 0 ? getOptionCount - 1 : 0;
    if (!isAdd && monthDaysDatePickerColumnPattern->GetCurrentIndex() == getOptionCount) {
        // reduce to previous year
        auto getYear = date.GetYear();
        getYear = getYear > 0 ? getYear - 1 : 0;
        date.SetYear(getYear);
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
    auto blendMonthDays = DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    CHECK_NULL_VOID(blendMonthDays);
    auto monthDaysNode = DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    auto stackYear = DynamicCast<FrameNode>(year);
    auto blendYear = DynamicCast<FrameNode>(stackYear->GetLastChild());
    CHECK_NULL_VOID(blendYear);
    auto yearDaysNode = DynamicCast<FrameNode>(blendYear->GetLastChild());
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
    auto blendMonthDays = DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    CHECK_NULL_VOID(blendMonthDays);
    auto monthDaysNode = DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    auto stackYear = DynamicCast<FrameNode>(year);
    auto blendYear = DynamicCast<FrameNode>(stackYear->GetLastChild());
    CHECK_NULL_VOID(blendYear);
    auto yearDaysNode = DynamicCast<FrameNode>(blendYear->GetLastChild());
    CHECK_NULL_VOID(monthDaysNode);
    CHECK_NULL_VOID(yearDaysNode);

    auto monthDaysDatePickerColumnPattern = monthDaysNode->GetPattern<DatePickerColumnPattern>();
    auto yearDatePickerColumnPattern = yearDaysNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_VOID(monthDaysDatePickerColumnPattern);
    CHECK_NULL_VOID(yearDatePickerColumnPattern);

    uint32_t nowLunarYear = startDateLunar_.year + yearDatePickerColumnPattern->GetCurrentIndex();
    auto lunarDate = GetCurrentLunarDateByMonthDaysColumn(nowLunarYear);
    auto getOptionCount = GetOptionCount(monthDaysNode);
    getOptionCount = getOptionCount > 0 ? getOptionCount - 1 : 0;
    if (monthDaysDatePickerColumnPattern->GetCurrentIndex() == getOptionCount) {
        lunarDate.year = lunarDate.year > 0 ? lunarDate.year - 1 : 0; // reduce to previous year
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
    if (datePickerMode_ != DatePickerMode::MONTH_AND_DAY) {
        if (isAdd && date.GetMonth() == 1) {  // first month is 1
            date.SetYear(date.GetYear() + 1); // add 1 year, the next year
            if (date.GetYear() > endDateSolar_.GetYear()) {
                date.SetYear(startDateSolar_.GetYear());
            }
        }
        if (!isAdd && date.GetMonth() == 12) { // the last month is 12
            auto getYear = date.GetYear();
            getYear = getYear > 0 ? getYear - 1 : 0;
            date.SetYear(getYear);  // reduce 1 year, the previous year
            if (date.GetYear() < startDateSolar_.GetYear()) {
                date.SetYear(endDateSolar_.GetYear());
            }
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
    auto getOptionCount = GetOptionCount(monthNode);
    getOptionCount = getOptionCount > 0 ? getOptionCount - 1 : 0;
    if (!isAdd && index == getOptionCount) {
        lunarDate.year = lunarDate.year > 0 ? lunarDate.year - 1 : 0; // reduce to previous year
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
        auto countAndIndex = optionCount + lastYearIndex;
        countAndIndex = countAndIndex > 0 ? countAndIndex - 1 : 0;
        lastYearIndex = optionCount != 0 ? countAndIndex % optionCount : 0;
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
    RefPtr<FrameNode> stackYear;
    RefPtr<FrameNode> stackMonth;
    RefPtr<FrameNode> stackDay;
    OrderCurrentLunarDate(stackYear, stackMonth, stackDay);
    CHECK_NULL_RETURN(stackYear, lunarResult);
    CHECK_NULL_RETURN(stackMonth, lunarResult);
    CHECK_NULL_RETURN(stackDay, lunarResult);
    auto yearColumn = DynamicCast<FrameNode>(stackYear->GetLastChild()->GetLastChild());
    CHECK_NULL_RETURN(yearColumn, lunarResult);
    auto monthColumn = DynamicCast<FrameNode>(stackMonth->GetLastChild()->GetLastChild());
    CHECK_NULL_RETURN(monthColumn, lunarResult);
    auto dayColumn = DynamicCast<FrameNode>(stackDay->GetLastChild()->GetLastChild());
    CHECK_NULL_RETURN(dayColumn, lunarResult);
    auto yearDatePickerColumnPattern = yearColumn->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_RETURN(yearDatePickerColumnPattern, lunarResult);
    auto monthDatePickerColumnPattern = monthColumn->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_RETURN(monthDatePickerColumnPattern, lunarResult);
    auto dayDatePickerColumnPattern = dayColumn->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_RETURN(dayDatePickerColumnPattern, lunarResult);
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

void DatePickerPattern::OrderCurrentLunarDate(
    RefPtr<FrameNode>& stackYear, RefPtr<FrameNode>& stackMonth, RefPtr<FrameNode>& stackDay) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    auto processDateNode = [&children](RefPtr<UINode>& first, RefPtr<UINode>& second, RefPtr<UINode>& third) {
        auto iter = children.begin();
        first = *iter++;
        CHECK_NULL_VOID(first);
        second = *iter++;
        CHECK_NULL_VOID(second);
        third = *iter;
        CHECK_NULL_VOID(third);
    };
    RefPtr<UINode> year;
    RefPtr<UINode> month;
    RefPtr<UINode> day;
    if (dateOrder_ == "M-d-y") {
        processDateNode(month, day, year);
    } else if (dateOrder_ == "y-d-M") {
        processDateNode(year, day, month);
    } else {
        processDateNode(year, month, day);
    }
    stackYear = DynamicCast<FrameNode>(year);
    stackMonth = DynamicCast<FrameNode>(month);
    stackDay = DynamicCast<FrameNode>(day);
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
    RefPtr<FrameNode> stackYear;
    RefPtr<FrameNode> stackMonth;
    RefPtr<FrameNode> stackDay;
    OrderCurrentDateByYearMonthDayColumn(stackYear, stackMonth, stackDay);
    CHECK_NULL_RETURN(stackYear, currentDate);
    CHECK_NULL_RETURN(stackMonth, currentDate);
    CHECK_NULL_RETURN(stackDay, currentDate);
    auto blendYear = DynamicCast<FrameNode>(stackYear->GetLastChild());
    CHECK_NULL_RETURN(blendYear, currentDate);
    auto yearColumn = DynamicCast<FrameNode>(blendYear->GetLastChild());
    CHECK_NULL_RETURN(yearColumn, currentDate);
    auto blendMonth = DynamicCast<FrameNode>(stackMonth->GetLastChild());
    CHECK_NULL_RETURN(blendMonth, currentDate);
    auto monthColumn = DynamicCast<FrameNode>(blendMonth->GetLastChild());
    CHECK_NULL_RETURN(monthColumn, currentDate);
    auto blendDay = DynamicCast<FrameNode>(stackDay->GetLastChild());
    CHECK_NULL_RETURN(blendDay, currentDate);
    auto dayColumn = DynamicCast<FrameNode>(blendDay->GetLastChild());
    CHECK_NULL_RETURN(dayColumn, currentDate);
    auto yearDatePickerColumnPattern = yearColumn->GetPattern<DatePickerColumnPattern>();
    auto monthDatePickerColumnPattern = monthColumn->GetPattern<DatePickerColumnPattern>();
    auto dayDatePickerColumnPattern = dayColumn->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_RETURN(yearDatePickerColumnPattern, currentDate);
    CHECK_NULL_RETURN(monthDatePickerColumnPattern, currentDate);
    CHECK_NULL_RETURN(dayDatePickerColumnPattern, currentDate);
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

void DatePickerPattern::OrderCurrentDateByYearMonthDayColumn(
    RefPtr<FrameNode>& stackYear, RefPtr<FrameNode>& stackMonth, RefPtr<FrameNode>& stackDay) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    if (children.size() != CHILD_SIZE) {
        return;
    }
    auto processDateNode = [&children](RefPtr<UINode>& first, RefPtr<UINode>& second, RefPtr<UINode>& third) {
        auto iter = children.begin();
        first = *iter++;
        CHECK_NULL_VOID(first);
        second = *iter++;
        CHECK_NULL_VOID(second);
        third = *iter;
        CHECK_NULL_VOID(third);
    };
    RefPtr<UINode> year;
    RefPtr<UINode> month;
    RefPtr<UINode> day;
    if (dateOrder_ == "M-d-y") {
        processDateNode(month, day, year);
    } else if (dateOrder_ == "y-d-M") {
        processDateNode(year, day, month);
    } else {
        processDateNode(year, month, day);
    }
    stackYear = DynamicCast<FrameNode>(year);
    stackMonth = DynamicCast<FrameNode>(month);
    stackDay = DynamicCast<FrameNode>(day);
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
    auto blendMonthDays = DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    CHECK_NULL_RETURN(blendMonthDays, currentDate);
    auto monthDaysNode = DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    auto stackYear = DynamicCast<FrameNode>(year);
    auto blendYear = DynamicCast<FrameNode>(stackYear->GetLastChild());
    CHECK_NULL_RETURN(blendYear, currentDate);
    auto yearDaysNode = DynamicCast<FrameNode>(blendYear->GetLastChild());
    CHECK_NULL_RETURN(monthDaysNode, currentDate);
    CHECK_NULL_RETURN(yearDaysNode, currentDate);

    auto monthDaysDatePickerColumnPattern = monthDaysNode->GetPattern<DatePickerColumnPattern>();
    auto yearDatePickerColumnPattern = yearDaysNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_RETURN(yearDatePickerColumnPattern, currentDate);
    CHECK_NULL_RETURN(monthDaysDatePickerColumnPattern, currentDate);

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
    auto monthDaysNode = DynamicCast<FrameNode>(stackMonthDays->GetLastChild()->GetLastChild());
    auto stackYear = DynamicCast<FrameNode>(year);
    auto blendYear = DynamicCast<FrameNode>(stackYear->GetLastChild());
    CHECK_NULL_RETURN(blendYear, lunarResult);
    auto yearDaysNode = DynamicCast<FrameNode>(blendYear->GetLastChild());
    CHECK_NULL_RETURN(monthDaysNode, lunarResult);
    CHECK_NULL_RETURN(yearDaysNode, lunarResult);

    auto monthDaysDatePickerColumnPattern = monthDaysNode->GetPattern<DatePickerColumnPattern>();
    auto yearDatePickerColumnPattern = yearDaysNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_RETURN(monthDaysDatePickerColumnPattern, lunarResult);
    CHECK_NULL_RETURN(yearDatePickerColumnPattern, lunarResult);


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
    lunarResult.isLeapMonth = (lunarResult.month == lunarLeapMonth && hasLeapMonth);
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
    RefPtr<FrameNode> columns[COLUMNS_SIZE];
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int index = 0;
    int order[COLUMNS_SIZE];
    if (dateOrder_ == "M-d-y") {
        order[COLUMNS_ZERO] = INDEX_MONTH;
        order[COLUMNS_ONE] = INDEX_DAY;
        order[COLUMNS_TWO] = INDEX_YEAR;
    } else if (dateOrder_ == "y-d-M") {
        order[COLUMNS_ZERO] = INDEX_YEAR;
        order[COLUMNS_ONE] = INDEX_DAY;
        order[COLUMNS_TWO] = INDEX_MONTH;
    } else {
        order[COLUMNS_ZERO] = INDEX_YEAR;
        order[COLUMNS_ONE] = INDEX_MONTH;
        order[COLUMNS_TWO] = INDEX_DAY;
    }
    for (const auto& stackChild : host->GetChildren()) {
        CHECK_NULL_VOID(stackChild);
        auto blendChild = stackChild->GetLastChild();
        CHECK_NULL_VOID(blendChild);
        auto child = blendChild->GetLastChild();
        columns[order[index]] = GetColumn(child->GetId());
        index++;
    }
    yearColumn = columns[COLUMNS_ZERO];
    monthColumn = columns[COLUMNS_ONE];
    dayColumn = columns[COLUMNS_TWO];
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
        options_[yearColumn].emplace_back(PickerDateF::CreateYear(index));
    }

    uint32_t lunarLeapMonth = 0;
    bool hasLeapMonth = GetLunarLeapMonth(current.year, lunarLeapMonth);
    options_[monthColumn].clear();
    if (startYear == endYear) {
        options_[monthColumn].resize(startMonth > 0 ? startMonth - 1 : 0, emptyPickerDate_);
    }
    // lunar's month start form startMonth to endMonth
    for (uint32_t index = startMonth; index <= endMonth; ++index) {
        if (!current.isLeapMonth && current.month == index) {
            auto datePickerColumnPattern = monthColumn->GetPattern<DatePickerColumnPattern>();
            CHECK_NULL_VOID(datePickerColumnPattern);
            datePickerColumnPattern->SetCurrentIndex(options_[monthColumn].size());
        }
        options_[monthColumn].emplace_back(PickerDateF::CreateMonth(index, true, false));

        if (hasLeapMonth && lunarLeapMonth == index) {
            if (current.isLeapMonth && current.month == index) {
                auto datePickerColumnPattern = monthColumn->GetPattern<DatePickerColumnPattern>();
                CHECK_NULL_VOID(datePickerColumnPattern);
                datePickerColumnPattern->SetCurrentIndex(options_[monthColumn].size());
            }
            options_[monthColumn].emplace_back(PickerDateF::CreateMonth(index, true, true));
        }
    }

    options_[dayColumn].clear();
    if (startYear == endYear && startMonth == endMonth) {
        options_[dayColumn].resize(startDay - 1, emptyPickerDate_);
    }
    // lunar's day start from startDay
    for (uint32_t index = startDay; index <= endDay; ++index) {
        if (current.day == index) {
            auto datePickerColumnPattern = dayColumn->GetPattern<DatePickerColumnPattern>();
            CHECK_NULL_VOID(datePickerColumnPattern);
            datePickerColumnPattern->SetCurrentIndex(options_[dayColumn].size());
        }
        options_[dayColumn].emplace_back(PickerDateF::CreateDay(index, true));
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

    RefPtr<FrameNode> columns[COLUMNS_SIZE];
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int index = 0;
    int order[COLUMNS_SIZE];
    if (dateOrder_ == "M-d-y") {
        order[COLUMNS_ZERO] = INDEX_MONTH;
        order[COLUMNS_ONE] = INDEX_DAY;
        order[COLUMNS_TWO] = INDEX_YEAR;
    } else if (dateOrder_ == "y-d-M") {
        order[COLUMNS_ZERO] = INDEX_YEAR;
        order[COLUMNS_ONE] = INDEX_DAY;
        order[COLUMNS_TWO] = INDEX_MONTH;
    } else {
        order[COLUMNS_ZERO] = INDEX_YEAR;
        order[COLUMNS_ONE] = INDEX_MONTH;
        order[COLUMNS_TWO] = INDEX_DAY;
    }
    for (const auto& stackChild : host->GetChildren()) {
        CHECK_NULL_VOID(stackChild);
        auto blendChild = stackChild->GetLastChild();
        CHECK_NULL_VOID(blendChild);
        auto child = blendChild->GetLastChild();
        columns[order[index]] = GetColumn(child->GetId());
        index++;
    }
    yearColumn = columns[COLUMNS_ZERO];
    monthColumn = columns[COLUMNS_ONE];
    dayColumn = columns[COLUMNS_TWO];

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
        options_[yearColumn].emplace_back(PickerDateF::CreateYear(year));
    }

    options_[monthColumn].clear();
    if (startYear == endYear) {
        options_[monthColumn].resize(startMonth > 0 ? startMonth - 1 : 0, emptyPickerDate_);
    }
    // solar's month start form 1 to 12
    for (uint32_t month = startMonth; month <= endMonth; month++) {
        if (month == current.GetMonth()) {
            auto datePickerColumnPattern = monthColumn->GetPattern<DatePickerColumnPattern>();
            CHECK_NULL_VOID(datePickerColumnPattern);
            // back index = size - 1
            datePickerColumnPattern->SetCurrentIndex(options_[monthColumn].size());
        }

        options_[monthColumn].emplace_back(PickerDateF::CreateMonth(month, false, false));
    }

    options_[dayColumn].clear();
    if (startYear == endYear && startMonth == endMonth) {
        options_[dayColumn].resize(startDay - 1, emptyPickerDate_);
    }
    // solar's day start from 1
    for (uint32_t day = startDay; day <= endDay; day++) {
        if (day == current.GetDay()) {
            auto datePickerColumnPattern = dayColumn->GetPattern<DatePickerColumnPattern>();
            CHECK_NULL_VOID(datePickerColumnPattern);
            datePickerColumnPattern->SetCurrentIndex(options_[dayColumn].size());
        }
        options_[dayColumn].emplace_back(PickerDateF::CreateDay(day, false));
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
    auto blendMonthDays = DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    CHECK_NULL_VOID(blendMonthDays);
    auto monthDaysNode = DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    auto stackYear = DynamicCast<FrameNode>(year);
    auto blendYear = DynamicCast<FrameNode>(stackYear->GetLastChild());
    CHECK_NULL_VOID(blendYear);
    auto yearDaysNode = DynamicCast<FrameNode>(blendYear->GetLastChild());
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
        options_[yearColumn].emplace_back(PickerDateF::CreateYear(index));
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
    auto blendMonthDays = DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    CHECK_NULL_VOID(blendMonthDays);
    auto monthDaysNode = DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    auto stackYear = DynamicCast<FrameNode>(year);
    auto blendYear = DynamicCast<FrameNode>(stackYear->GetLastChild());
    CHECK_NULL_VOID(blendYear);
    auto yearDaysNode = DynamicCast<FrameNode>(blendYear->GetLastChild());
    monthDaysColumn = GetColumn(monthDaysNode->GetId());
    yearColumn = GetColumn(yearDaysNode->GetId());
    CHECK_NULL_VOID(monthDaysColumn);
    CHECK_NULL_VOID(yearColumn);

    AdjustSolarStartEndDate();
    FillSolarYearOptions(current, yearColumn);

    options_[monthDaysColumn].clear();
    for (uint32_t index = MIN_MONTH; index <= MAX_MONTH; ++index) {
        uint32_t maxDay = PickerDate::GetMaxDay(current.GetYear(), index);
        for (uint32_t dayIndex = MIN_DAY; dayIndex <= maxDay; ++dayIndex) {
            if (index == current.GetMonth() && dayIndex == current.GetDay()) {
                auto datePickerColumnPattern = monthDaysColumn->GetPattern<DatePickerColumnPattern>();
                CHECK_NULL_VOID(datePickerColumnPattern);
                datePickerColumnPattern->SetCurrentIndex(options_[monthDaysColumn].size());
            }
            options_[monthDaysColumn].emplace_back(PickerDateF::CreateMonthDay(index, dayIndex, false, false));
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
        options_[yearColumn].emplace_back(PickerDateF::CreateYear(year));
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
        for (uint32_t dayIndex = startDay; dayIndex <= maxDay; ++dayIndex) {
            if (!current.isLeapMonth && current.month == index && current.day == dayIndex) {
                auto datePickerColumnPattern = monthDaysColumn->GetPattern<DatePickerColumnPattern>();
                CHECK_NULL_VOID(datePickerColumnPattern);
                datePickerColumnPattern->SetCurrentIndex(options_[monthDaysColumn].size());
            }
            options_[monthDaysColumn].emplace_back(PickerDateF::CreateMonthDay(index, dayIndex, true, false));
        }

        if (!hasLeapMonth || lunarLeapMonth != index) {
            continue;
        }

        maxDay = GetLunarMaxDay(current.year, index, true);
        for (uint32_t dayIndex = startDay; dayIndex <= maxDay; ++dayIndex) {
            if (current.isLeapMonth && current.month == index && current.day == dayIndex) {
                auto datePickerColumnPattern = monthDaysColumn->GetPattern<DatePickerColumnPattern>();
                CHECK_NULL_VOID(datePickerColumnPattern);
                datePickerColumnPattern->SetCurrentIndex(options_[monthDaysColumn].size());
            }
            options_[monthDaysColumn].emplace_back(PickerDateF::CreateMonthDay(index, dayIndex, true, true));
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
    uint32_t days = date.day > 0 ? date.day - 1 : 0; // calculate days from 1900.1.1 to this date
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
    if (inited_) {
        return;
    }
    years_.clear();
    solarMonths_.clear();
    solarDays_.clear();
    lunarMonths_.clear();
    lunarDays_.clear();
    localizedMonths_ = Localization::GetInstance()->GetMonths(true);

    inited_ = true;
    Localization::GetInstance()->SetOnChange([]() { inited_ = false; });
}

const std::string& DatePickerPattern::GetYear(uint32_t year)
{
    Init();
    if (!(1900 <= year && year <= 2100)) { // year in [1900,2100]
        return empty_;
    }
    auto index = year - 1900;
    auto it = years_.find(index);
    if (it == years_.end()) {
        DateTime date;
        date.year = year;
        auto& dateYear = years_[index];
        dateYear = Localization::GetInstance()->FormatDateTime(date, "y");
        return dateYear;
    }
    return it->second; // index in [0, 200]
}

const std::string& DatePickerPattern::GetSolarMonth(uint32_t month)
{
    Init();
    if (!(1 <= month && month <= 12)) { // solar month in [1,12]
        return empty_;
    }
    auto index = month - 1;
    auto it = solarMonths_.find(index);
    if (it == solarMonths_.end()) {
        auto& dateMonth = solarMonths_[index];
        if (index < localizedMonths_.size()) {
            dateMonth = localizedMonths_[index];
        } else {
            DateTime date;
            date.month = month - 1; // W3C's month start from 0 to 11
            dateMonth = Localization::GetInstance()->FormatDateTime(date, "M");
        }
        return dateMonth;
    }
    return it->second; // index in [0,11]
}

const std::string& DatePickerPattern::GetSolarDay(uint32_t day)
{
    Init();
    if (!(1 <= day && day <= 31)) { // solar day in [1,31]
        return empty_;
    }
    auto index = day - 1;
    auto it = solarDays_.find(index);
    if (it == solarDays_.end()) {
        auto& dateDay = solarDays_[index];
        DateTime date;
        date.day = day;
        dateDay = Localization::GetInstance()->FormatDateTime(date, "d");
        return dateDay;
    }
    return it->second; // index in [0,30]
}

const std::string& DatePickerPattern::GetLunarMonth(uint32_t month, bool isLeap)
{
    Init();
    uint32_t index = (isLeap ? month + 12 : month); // leap month is behind 12 index
    if (!(1 <= index && index <= 24)) {             // lunar month need in [1,24]
        return empty_;
    }
    auto it = lunarMonths_.find(index - 1);
    if (it == lunarMonths_.end()) {
        auto& dateMonth = lunarMonths_[index - 1];
        dateMonth = Localization::GetInstance()->GetLunarMonth(month, isLeap);
        return dateMonth;
    }
    return it->second; // index in [0,23]
}

const std::string& DatePickerPattern::GetLunarDay(uint32_t day)
{
    Init();
    if (!(1 <= day && day <= 30)) { // lunar day need in [1,30]
        return empty_;
    }
    auto index = day - 1;
    auto it = lunarDays_.find(index);
    if (it == lunarDays_.end()) {
        auto& dateDay = lunarDays_[index];
        dateDay = Localization::GetInstance()->GetLunarDay(day);
        return dateDay;
    }
    return it->second; // index in [0,29]
}

const std::string DatePickerPattern::GetText()
{
    auto pickerDate = GetCurrentDate();
    std::string result = std::to_string(pickerDate.GetYear()) + "-" + std::to_string(pickerDate.GetMonth()) + "-" +
                     std::to_string(pickerDate.GetDay());
    return result;
}

const std::string DatePickerPattern::GetFormatString(PickerDateF date)
{
    if (date.year.has_value()) {
        return GetYear(date.year.value());
    }

    std::string monthStr;
    if (date.month.has_value()) {
        monthStr = date.lunar ? GetLunarMonth(date.month.value(), date.leap) : GetSolarMonth(date.month.value());
        if (!date.day.has_value()) {
            return monthStr;
        }
    }

    std::string dayStr;
    if (date.day.has_value()) {
        dayStr = date.lunar ? GetLunarDay(date.day.value()) : GetSolarDay(date.day.value());
        DateTimeSequence sequence;
        auto language = AceApplicationInfo::GetInstance().GetLanguage();
        OrderResult orderResult = sequence.GetDateOrder(language);
        if (language == "ug") {
            return date.month.has_value() ? (dayStr + "-" + monthStr) : dayStr;
        } else if (language == "en") {
            return date.month.has_value() ? (monthStr + " " + dayStr) : dayStr;
        } else {
            return date.month.has_value() ? (monthStr + dayStr) : dayStr;
        }
    }

    return "";
}

void DatePickerPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
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
    jsonConstructor->Put("mode", rowLayoutProperty->GetDatePickerMode().c_str());
    json->PutExtAttr("constructor", jsonConstructor, filter);
    json->PutExtAttr("enableHapticFeedback", isEnableHaptic_, filter);
}

void DatePickerPattern::SetFocusDisable()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);

    isFocus_ = false;
    focusHub->SetFocusable(false);
}

void DatePickerPattern::SetFocusEnable()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);

    isFocus_ = true;
    focusHub->SetFocusable(true);
}

bool DatePickerPattern::NeedAdaptForAging()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, false);

    if (GreatOrEqual(pipeline->GetFontScale(), pickerTheme->GetMaxOneFontScale()) &&
        GreatOrEqual(Dimension(pipeline->GetRootHeight()).ConvertToVp(), pickerTheme->GetDeviceHeightLimit())) {
        return true;
    }
    return false;
}
} // namespace OHOS::Ace::NG
