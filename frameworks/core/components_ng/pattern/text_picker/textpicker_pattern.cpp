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

#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"

#include <cstdint>
#include <securec.h>

#include "base/i18n/localization.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_layout_property.h"
#include "core/components_ng/pattern/text_picker/toss_animation_controller.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
namespace {
// Datepicker style modification
const Dimension PRESS_INTERVAL = 4.0_vp;
const Dimension PRESS_RADIUS = 8.0_vp;
constexpr uint32_t RATE = 2;
const Dimension DIALOG_OFFSET = 1.0_vp;
const Dimension DIALOG_OFFSET_LENGTH = 1.0_vp;
constexpr uint32_t HALF = 2;
const Dimension FOCUS_WIDTH = 2.0_vp;
const Dimension FOCUS_INTERVAL = 2.0_vp;
const Dimension LINE_WIDTH = 1.5_vp;
constexpr float DISABLE_ALPHA = 0.6f;
constexpr float MAX_PERCENT = 100.0f;
const int32_t UNOPTION_COUNT = 2;
} // namespace

void TextPickerPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
    host->GetRenderContext()->UpdateClipEdge(true);
}

void TextPickerPattern::SetLayoutDirection(TextDirection textDirection)
{
    auto textPickerNode = GetHost();
    std::function<void (decltype(textPickerNode))> updateDirectionFunc = [&](decltype(textPickerNode) node) {
        CHECK_NULL_VOID(node);
        auto updateProperty = node->GetLayoutProperty();
        updateProperty->UpdateLayoutDirection(textDirection);
        for (auto child : node->GetAllChildrenWithBuild()) {
            auto frameNode = AceType::DynamicCast<FrameNode>(child);
            if (!frameNode) {
                continue;
            }
            updateDirectionFunc(frameNode);
        }
    };
    updateDirectionFunc(textPickerNode);
}

bool TextPickerPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    CHECK_NULL_RETURN(dirty, false);
    SetButtonIdeaSize();
    if (GetIsShowInDialog()) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto parentNode = host->GetParent();
        CHECK_NULL_RETURN(parentNode, false);
        parentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    }
    return true;
}

void TextPickerPattern::UpdateButtonMargin(
    const RefPtr<FrameNode>& buttonNode, const RefPtr<DialogTheme>& dialogTheme, const bool isConfirmOrNextNode)
{
    MarginProperty margin;
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    isRtl = isConfirmOrNextNode ? isRtl : !isRtl;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        margin.top = CalcLength(dialogTheme->GetDividerHeight());
        margin.bottom = CalcLength(dialogTheme->GetDividerPadding().Bottom());
        if (isRtl) {
            margin.right = CalcLength(0.0_vp);
            margin.left = CalcLength(dialogTheme->GetDividerPadding().Left());
        } else {
            margin.right = CalcLength(dialogTheme->GetDividerPadding().Right());
            margin.left = CalcLength(0.0_vp);
        }
    } else {
        margin.top = CalcLength(dialogTheme->GetActionsPadding().Top());
        margin.bottom = CalcLength(dialogTheme->GetActionsPadding().Bottom());
        if (isRtl) {
            margin.right = CalcLength(0.0_vp);
            margin.left = CalcLength(dialogTheme->GetActionsPadding().Left());
        } else {
            margin.right = CalcLength(dialogTheme->GetActionsPadding().Right());
            margin.left = CalcLength(0.0_vp);
        }
    }
    buttonNode->GetLayoutProperty()->UpdateMargin(margin);
}

void TextPickerPattern::UpdateDialogAgingButton(const RefPtr<FrameNode>& buttonNode, const bool isNext)
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
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    buttonLayoutProperty->UpdateLabel(lettersStr);

    UpdateButtonMargin(buttonNode, dialogTheme, isNext);
    updateNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TextPickerPattern::OnLanguageConfigurationUpdate()
{
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
    auto buttonConfirmLayoutProperty = buttonConfirmNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonConfirmLayoutProperty);
    buttonConfirmLayoutProperty->UpdateLabel(dialogTheme->GetConfirmText());
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
    auto buttonCancelLayoutProperty = buttonCancelNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonCancelLayoutProperty);
    buttonCancelLayoutProperty->UpdateLabel(dialogTheme->GetCancelText());
    cancelNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    auto buttonForwardNode = weakButtonForward_.Upgrade();
    UpdateDialogAgingButton(buttonForwardNode, true);
    auto buttonBackwardNode = weakButtonBackward_.Upgrade();
    UpdateDialogAgingButton(buttonBackwardNode, false);
}

void TextPickerPattern::OnFontConfigurationUpdate()
{
    CHECK_NULL_VOID(closeDialogEvent_);
    closeDialogEvent_();
}

void TextPickerPattern::OnFontScaleConfigurationUpdate()
{
    CHECK_NULL_VOID(closeDialogEvent_);
    closeDialogEvent_();
}

void TextPickerPattern::SetButtonIdeaSize()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto children = host->GetChildren();
    auto currentFocusButtonNode = GetFocusButtonNode();
    CHECK_NULL_VOID(currentFocusButtonNode);
    for (const auto& child : children) {
        auto stackNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(stackNode);
        auto width = stackNode->GetGeometryNode()->GetFrameSize().Width();
        auto buttonNode = DynamicCast<FrameNode>(child->GetFirstChild());
        CHECK_NULL_VOID(buttonNode);
        auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_VOID(buttonLayoutProperty);
        buttonLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
        buttonLayoutProperty->UpdateType(ButtonType::NORMAL);
        buttonLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(selectorItemRadius_));
        auto buttonHeight = CalculateHeight() - PRESS_INTERVAL.ConvertToPx() * (useButtonFocusArea_ ? 1 : RATE);
        if (resizeFlag_) {
            buttonHeight = resizePickerItemHeight_ - PRESS_INTERVAL.ConvertToPx() * RATE;
        }

        auto buttonSpace = useButtonFocusArea_ ? pickerTheme->GetSelectorItemSpace() : PRESS_INTERVAL * RATE;
        if (children.size() == 1 && useButtonFocusArea_) {
            buttonSpace = PRESS_INTERVAL * RATE;
        }
        buttonLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(width - buttonSpace.ConvertToPx()), CalcLength(buttonHeight)));
        auto buttonConfirmRenderContext = buttonNode->GetRenderContext();
        CHECK_NULL_VOID(buttonConfirmRenderContext);
        auto blendNode = DynamicCast<FrameNode>(stackNode->GetLastChild());
        CHECK_NULL_VOID(blendNode);
        auto columnNode = DynamicCast<FrameNode>(blendNode->GetLastChild());
        CHECK_NULL_VOID(columnNode);
        auto columnPattern = columnNode->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(columnPattern);
        if (!useButtonFocusArea_) {
            if (!columnPattern->isHover()) {
                buttonConfirmRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
            }
        } else {
            UpdateColumnButtonStyles(columnNode, haveFocus_ && (currentFocusButtonNode == buttonNode), false);
        }
        buttonNode->MarkModifyDone();
        buttonNode->MarkDirtyNode();
    }
}

void TextPickerPattern::InitSelectorProps()
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

void TextPickerPattern::InitFocusEvent()
{
    CHECK_NULL_VOID(!focusEventInitialized_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto focusTask = [weak = WeakClaim(this)](FocusReason reason) {
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

void TextPickerPattern::SetHaveFocus(bool haveFocus)
{
    haveFocus_ = haveFocus;
}

void TextPickerPattern::HandleFocusEvent()
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

void TextPickerPattern::HandleBlurEvent()
{
    SetHaveFocus(false);
    RemoveIsFocusActiveUpdateEvent();
    UpdateFocusButtonState();
}

void TextPickerPattern::AddIsFocusActiveUpdateEvent()
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

void TextPickerPattern::RemoveIsFocusActiveUpdateEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveIsFocusActiveUpdateEvent(host);
}

void TextPickerPattern::UpdateFocusButtonState()
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

const RefPtr<FrameNode> TextPickerPattern::GetFocusButtonNode() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto currentFocusStackChild = DynamicCast<FrameNode>(host->GetChildAtIndex(focusKeyID_));
    CHECK_NULL_RETURN(currentFocusStackChild, nullptr);
    auto currentFocusButtonNode = DynamicCast<FrameNode>(currentFocusStackChild->GetFirstChild());
    return currentFocusButtonNode;
}

void TextPickerPattern::UpdateColumnButtonStyles(
    const RefPtr<FrameNode>& columnNode, bool haveFocus, bool needMarkDirty)
{
    CHECK_NULL_VOID(columnNode);

    auto textPickerColumnPattern = columnNode->GetPattern<TextPickerColumnPattern>();
    CHECK_NULL_VOID(textPickerColumnPattern);
    textPickerColumnPattern->UpdateColumnButtonFocusState(haveFocus, needMarkDirty);
}

void TextPickerPattern::GetInnerFocusButtonPaintRect(RoundRect& paintRect, float focusButtonXOffset)
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
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(selectorItemRadius_);
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto radius = renderContext->GetBorderRadius().value_or(borderRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS,
        static_cast<float>(radius.radiusTopLeft->ConvertToPx() + focusSpace),
        static_cast<float>(radius.radiusTopLeft->ConvertToPx() + focusSpace));
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS,
        static_cast<float>(radius.radiusTopRight->ConvertToPx() + focusSpace),
        static_cast<float>(radius.radiusTopRight->ConvertToPx() + focusSpace));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS,
        static_cast<float>(radius.radiusBottomLeft->ConvertToPx() + focusSpace),
        static_cast<float>(radius.radiusBottomLeft->ConvertToPx() + focusSpace));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS,
        static_cast<float>(radius.radiusBottomRight->ConvertToPx() + focusSpace),
        static_cast<float>(radius.radiusBottomRight->ConvertToPx() + focusSpace));
}

void TextPickerPattern::CalcLeftTotalColumnWidth(
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

void TextPickerPattern::ColumnPatternInitHapticController()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (host->LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        return;
    }
    if (!isHapticChanged_) {
        return;
    }

    isHapticChanged_ = false;
    auto frameNodes = GetColumnNodes();
    for (auto iter : frameNodes) {
        auto columnNode = iter.second;
        if (!columnNode) {
            continue;
        }
        auto columnPattern = columnNode->GetPattern<TextPickerColumnPattern>();
        if (!columnPattern) {
            continue;
        }
        columnPattern->InitHapticController(columnNode);
    }
}


bool TextPickerPattern::IsCircle()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, false);

    return pickerTheme->IsCircleDial();
}

void TextPickerPattern::ClearFocus()
{
    if (!IsCircle()) {
        return;
    }

    if (selectedColumnId_ == INVALID_SELECTED_COLUMN_INDEX) {
        return;
    }
    const auto& frameNodes = GetColumnNodes();
    auto it = frameNodes.find(selectedColumnId_);
    if (it != frameNodes.end()) {
        auto textPickerColumnPattern = it->second->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(textPickerColumnPattern);
        textPickerColumnPattern->SetSelectedMark(false, false);
    }
    selectedColumnId_ = INVALID_SELECTED_COLUMN_INDEX;
}

void TextPickerPattern::SetDefaultFocus()
{
    if (!IsCircle()) {
        return;
    }

    std::function<void(int32_t& focusId)>  call = [weak = WeakClaim(this)](int32_t& focusId) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->selectedColumnId_ < 0) {
            pattern->selectedColumnId_ = focusId;
            return;
        }

        const auto& frameNodes = pattern->GetColumnNodes();
        auto it = frameNodes.find(pattern->selectedColumnId_);
        if (it != frameNodes.end()) {
            auto textPickerColumnPattern = it->second->GetPattern<TextPickerColumnPattern>();
            CHECK_NULL_VOID(textPickerColumnPattern);
            textPickerColumnPattern->SetSelectedMark(false, false);
            pattern->selectedColumnId_ = focusId;
        }
    };

    const auto& frameNodes = GetColumnNodes();
    int32_t index = 0;
    for (const auto& it : frameNodes) {
        CHECK_NULL_VOID(it.second);
        auto textPickerColumnPattern = it.second->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(textPickerColumnPattern);
        textPickerColumnPattern->SetSelectedMarkId(index);
        textPickerColumnPattern->SetSelectedMarkListener(call);
        if (index == 0) {
            textPickerColumnPattern->SetSelectedMark(true, false);
            selectedColumnId_ = 0;
        }
        index++;
    }
}

#ifdef SUPPORT_DIGITAL_CROWN
void TextPickerPattern::InitOnCrownEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onCrowEvent = [wp = WeakClaim(this)](const CrownEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        if (pattern) {
            return pattern->OnCrownEvent(event);
        }
        return false;
    };

    focusHub->SetOnCrownEventInternal(std::move(onCrowEvent));
}

bool TextPickerPattern::OnCrownEvent(const CrownEvent& event)
{
    if (event.action == OHOS::Ace::CrownAction::BEGIN ||
        event.action == OHOS::Ace::CrownAction::UPDATE ||
        event.action == OHOS::Ace::CrownAction::END) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto focusHub = host->GetFocusHub();
        CHECK_NULL_RETURN(focusHub, false);

        RefPtr<TextPickerColumnPattern> crownPickerColumnPattern;
        auto&& children = host->GetChildren();
        for (const auto& child : children) {
            auto stackNode = DynamicCast<FrameNode>(child);
            if (!stackNode) {
                continue;
            }
            auto blendNode = DynamicCast<FrameNode>(stackNode->GetLastChild());
            if (!blendNode) {
                continue;
            }
            auto childNode = DynamicCast<FrameNode>(blendNode->GetLastChild());
            if (!childNode) {
                continue;
            }
            auto pickerColumnPattern = childNode->GetPattern<TextPickerColumnPattern>();
            if (!pickerColumnPattern) {
                continue;
            }
            auto columnID =  pickerColumnPattern->GetSelectedColumnId();
            if (!pickerColumnPattern->IsCrownEventEnded()) {
                crownPickerColumnPattern = pickerColumnPattern;
                break;
            } else if (columnID == selectedColumnId_) {
                crownPickerColumnPattern= pickerColumnPattern;
            }
        }
        if (crownPickerColumnPattern != nullptr) {
            return crownPickerColumnPattern->OnCrownEvent(event);
        }
    }
    return false;
}
#endif

void TextPickerPattern::SetDigitalCrownSensitivity(int32_t crownSensitivity)
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
        auto pickerColumnPattern = childNode->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(pickerColumnPattern);
        pickerColumnPattern->SetDigitalCrownSensitivity(crownSensitivity);
    }
#endif
}

void TextPickerPattern::InitCrownAndKeyEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);
#ifdef SUPPORT_DIGITAL_CROWN
    InitOnCrownEvent(focusHub);
#endif
}

void TextPickerPattern::SetCallBack()
{
    if (cascadeOptions_.size() > 0) {
        SetChangeCallback([weak = WeakClaim(this)](const RefPtr<FrameNode>& tag,
            bool add, uint32_t index, bool notify) {
                auto refPtr = weak.Upgrade();
                CHECK_NULL_VOID(refPtr);
                refPtr->HandleColumnChange(tag, add, index, notify);
            });
    }
    SetEventCallback([weak = WeakClaim(this)](bool refresh) {
        auto refPtr = weak.Upgrade();
        CHECK_NULL_VOID(refPtr);
        refPtr->FireChangeEvent(refresh);
    });
    SetScrollStopEventCallback([weak = WeakClaim(this)](bool refresh) {
        auto refPtr = weak.Upgrade();
        CHECK_NULL_VOID(refPtr);
        refPtr->FireScrollStopEvent(refresh);
    });
    SetEnterSelectedAreaEventCallback([weak = WeakClaim(this)](bool refresh) {
        auto refPtr = weak.Upgrade();
        CHECK_NULL_VOID(refPtr);
        refPtr->FireEnterSelectedAreaEvent(refresh);
    });
}

void TextPickerPattern::OnModifyDone()
{
    Pattern::CheckLocalized();
    if (isFiredSelectsChange_) {
        isFiredSelectsChange_ = false;
        ColumnPatternInitHapticController();
        return;
    }
    isHapticChanged_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto layoutDirection = layoutProperty->GetLayoutDirection();
    if (layoutDirection != TextDirection::AUTO) {
        SetLayoutDirection(layoutDirection);
    }
    ClearFocus();
    OnColumnsBuilding();
    FlushOptions();
    CalculateHeight();
    SetCallBack();
    InitFocusEvent();
    InitDisabled();
    InitCrownAndKeyEvent();
    InitSelectorProps();
    isNeedUpdateSelectedIndex_ = true;
    SetDefaultFocus();
}

void TextPickerPattern::SetEventCallback(EventCallback&& value)
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
        auto pickerColumnPattern = childNode->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(pickerColumnPattern);
        pickerColumnPattern->SetEventCallback(std::move(value));
    }
}

void TextPickerPattern::FireChangeEvent(bool refresh)
{
    auto frameNodes = GetColumnNodes();
    std::vector<std::string> value;
    std::vector<double> index;
    std::vector<uint32_t> selectedIdx;
    for (auto it : frameNodes) {
        CHECK_NULL_VOID(it.second);
        auto textPickerColumnPattern = it.second->GetPattern<TextPickerColumnPattern>();
        if (refresh) {
            auto currentIndex = textPickerColumnPattern->GetCurrentIndex();
            index.emplace_back(currentIndex);
            selectedIdx.emplace_back(currentIndex);
            auto currentValue = textPickerColumnPattern->GetOption(currentIndex);
            value.emplace_back(currentValue);
        }
    }
    auto textPickerEventHub = GetOrCreateEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(textPickerEventHub);
    textPickerEventHub->FireChangeEvent(value, index);
    textPickerEventHub->FireDialogChangeEvent(GetSelectedObject(true, 1));
    std::string idx_str;
    idx_str.assign(selectedIdx.begin(), selectedIdx.end());
    firedSelectsStr_ = idx_str;
}

void TextPickerPattern::SetScrollStopEventCallback(EventCallback&& value)
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
        auto pickerColumnPattern = childNode->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(pickerColumnPattern);
        pickerColumnPattern->SetScrollStopEventCallback(std::move(value));
    }
}

void TextPickerPattern::FireScrollStopEvent(bool refresh)
{
    auto frameNodes = GetColumnNodes();
    std::vector<std::string> value;
    std::vector<double> index;
    for (auto it : frameNodes) {
        CHECK_NULL_VOID(it.second);
        auto textPickerColumnPattern = it.second->GetPattern<TextPickerColumnPattern>();
        if (refresh) {
            auto currentIndex = textPickerColumnPattern->GetCurrentIndex();
            index.emplace_back(currentIndex);
            auto currentValue = textPickerColumnPattern->GetOption(currentIndex);
            value.emplace_back(currentValue);
        }
    }
    auto textPickerEventHub = GetOrCreateEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(textPickerEventHub);
    textPickerEventHub->FireScrollStopEvent(value, index);
    textPickerEventHub->FireDialogScrollStopEvent(GetSelectedObject(true, 1));
}

void TextPickerPattern::SetEnterSelectedAreaEventCallback(EventCallback&& value)
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
        auto pickerColumnPattern = childNode->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(pickerColumnPattern);
        pickerColumnPattern->SetEnterSelectedAreaEventCallback(std::move(value));
    }
}

void TextPickerPattern::FireEnterSelectedAreaEvent(bool refresh)
{
    auto frameNodes = GetColumnNodes();
    std::vector<std::string> value;
    std::vector<double> index;
    for (auto it : frameNodes) {
        CHECK_NULL_VOID(it.second);
        auto textPickerColumnPattern = it.second->GetPattern<TextPickerColumnPattern>();
        if (refresh) {
            auto enterIndex = textPickerColumnPattern->GetEnterIndex();
            index.emplace_back(enterIndex);
            auto enterValue = textPickerColumnPattern->GetOption(enterIndex);
            value.emplace_back(enterValue);
        }
    }
    auto textPickerEventHub = GetOrCreateEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(textPickerEventHub);
    textPickerEventHub->FireEnterSelectedAreaEvent(value, index);
    textPickerEventHub->FireDialogEnterSelectedAreaEvent(GetSelectedObject(true, 1, true));
}

void TextPickerPattern::InitDisabled()
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
    } else if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
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

RefPtr<FrameNode> TextPickerPattern::GetColumnNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);

    auto stackNode = host->GetChildAtIndex(focusKeyID_);
    CHECK_NULL_RETURN(stackNode, nullptr);

    auto blendNode = stackNode->GetLastChild();
    CHECK_NULL_RETURN(blendNode, nullptr);

    auto columnNode = blendNode->GetLastChild();
    CHECK_NULL_RETURN(columnNode, nullptr);

    return DynamicCast<FrameNode>(columnNode);
}

std::map<uint32_t, RefPtr<FrameNode>> TextPickerPattern::GetColumnNodes()
{
    std::map<uint32_t, RefPtr<FrameNode>> allChildNode;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, allChildNode);
    auto children = host->GetChildren();
    uint32_t index = 0;
    for (auto iter = children.begin(); iter != children.end(); iter++) {
        CHECK_NULL_RETURN(*iter, allChildNode);
        auto stackNode = DynamicCast<FrameNode>(*iter);
        auto blendNode = DynamicCast<FrameNode>(stackNode->GetLastChild());
        CHECK_NULL_RETURN(blendNode, allChildNode);
        auto currentNode = DynamicCast<FrameNode>(blendNode->GetLastChild());
        allChildNode[index] = currentNode;
        index++;
    }
    return allChildNode;
}

void TextPickerPattern::OnColumnsBuildingCascade()
{
    auto frameNodes = GetColumnNodes();
    auto count = frameNodes.size();
    for (size_t index = 0; index < count; index++) {
        CHECK_NULL_VOID(frameNodes[index]);
        auto textPickerColumnPattern = frameNodes[index]->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(textPickerColumnPattern);
        if (cascadeOptions_.size() > index) {
            selectedIndex_ = selecteds_.size() <= index || cascadeOptions_[index].rangeResult.empty()
                                 ? 0 : selecteds_[index] % cascadeOptions_[index].rangeResult.size();
            textPickerColumnPattern->SetCurrentIndex(
                isNeedUpdateSelectedIndex_ ? selectedIndex_ : textPickerColumnPattern->GetCurrentIndex());
            textPickerColumnPattern->SetEnterIndex(
                isNeedUpdateSelectedIndex_ ? selectedIndex_ : textPickerColumnPattern->GetCurrentIndex());
            std::vector<NG::RangeContent> rangeContents;
            for (uint32_t i = 0; i < cascadeOptions_[index].rangeResult.size(); i++) {
                NG::RangeContent rangeContent;
                rangeContent.text_ = cascadeOptions_[index].rangeResult[i];
                rangeContents.emplace_back(rangeContent);
            }
            textPickerColumnPattern->SetOptions(rangeContents);
            textPickerColumnPattern->SetColumnKind(NG::TEXT);
            optionsWithNode_[frameNodes[index]] = rangeContents;
            frameNodes[index]->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    }
}

void TextPickerPattern::OnColumnsBuildingUnCascade()
{
    auto frameNodes = GetColumnNodes();
    for (auto it : frameNodes) {
        CHECK_NULL_VOID(it.second);
        auto textPickerColumnPattern = it.second->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(textPickerColumnPattern);
        if (cascadeOptions_.size() > it.first) {
            selectedIndex_ = selecteds_.size() <= it.first || cascadeOptions_[it.first].rangeResult.empty()
                                 ? 0 : selecteds_[it.first] % cascadeOptions_[it.first].rangeResult.size();
            textPickerColumnPattern->SetCurrentIndex(
                isNeedUpdateSelectedIndex_ ? selectedIndex_ : textPickerColumnPattern->GetCurrentIndex());
            textPickerColumnPattern->SetEnterIndex(
                isNeedUpdateSelectedIndex_ ? selectedIndex_ : textPickerColumnPattern->GetCurrentIndex());
            std::vector<NG::RangeContent> rangeContents;
            for (uint32_t i = 0; i < cascadeOptions_[it.first].rangeResult.size(); i++) {
                NG::RangeContent rangeContent;
                rangeContent.text_ = cascadeOptions_[it.first].rangeResult[i];
                rangeContents.emplace_back(rangeContent);
            }
            textPickerColumnPattern->SetOptions(rangeContents);
            textPickerColumnPattern->SetColumnKind(NG::TEXT);
            optionsWithNode_[it.second] = rangeContents;
            it.second->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        } else {
            ClearOption();
            for (const auto& item : range_) {
                AppendOption(item);
            }
            selectedIndex_ = range_.empty() ? 0 : GetSelected() % range_.size();
            textPickerColumnPattern->SetCurrentIndex(
                isNeedUpdateSelectedIndex_ ? selectedIndex_ : textPickerColumnPattern->GetCurrentIndex());
            textPickerColumnPattern->SetEnterIndex(
                isNeedUpdateSelectedIndex_ ? selectedIndex_ : textPickerColumnPattern->GetCurrentIndex());
            textPickerColumnPattern->SetOptions(options_);
            textPickerColumnPattern->SetColumnKind(columnsKind_);
            it.second->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    }
}

void TextPickerPattern::OnColumnsBuilding()
{
    if (!isCascade_) {
        OnColumnsBuildingUnCascade();
    } else {
        OnColumnsBuildingCascade();
    }
}

void TextPickerPattern::SetSelecteds(const std::vector<uint32_t>& values)
{
    std::string values_str;
    values_str.assign(values.begin(), values.end());
    isFiredSelectsChange_ = firedSelectsStr_.has_value() && firedSelectsStr_.value() == values_str;
    firedSelectsStr_.reset();
    selecteds_.clear();
    for (auto& value : values) {
        selecteds_.emplace_back(value);
    }
    if (isCascade_) {
        auto columnCount = cascadeOptions_.size();
        cascadeOptions_.clear();
        ProcessCascadeOptions(cascadeOriginptions_, cascadeOptions_, 0);
        if (cascadeOptions_.size() < columnCount) {
            auto differ = columnCount - cascadeOptions_.size();
            for (uint32_t i = 0; i < differ; i++) {
                NG::TextCascadePickerOptions differOption;
                memset_s(&differOption, sizeof(differOption), 0, sizeof(differOption));
                cascadeOptions_.emplace_back(differOption);
            }
        }
    }
}

void TextPickerPattern::FlushOptions()
{
    auto frameNodes = GetColumnNodes();
    for (auto it : frameNodes) {
        CHECK_NULL_VOID(it.second);
        auto columnPattern = it.second->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(columnPattern);
        columnPattern->FlushCurrentOptions();
        it.second->MarkModifyDone();
        it.second->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

double TextPickerPattern::CalculateHeight()
{
    double height = 0.0;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, height);
    auto textPickerLayoutProperty = host->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_RETURN(textPickerLayoutProperty, height);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, height);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, height);
    if (textPickerLayoutProperty->HasDefaultPickerItemHeight()) {
        auto defaultPickerItemHeightValue = textPickerLayoutProperty->GetDefaultPickerItemHeightValue();
        if (LessOrEqual(context->NormalizeToPx(defaultPickerItemHeightValue), 0.0f)) {
            height = pickerTheme->GetDividerSpacing().ConvertToPx();
            if (!NearEqual(defaultPickerItemHeight_, height)) {
                defaultPickerItemHeight_ = height;
                PaintFocusState();
                SetButtonIdeaSize();
            }
            return height;
        }
        if (defaultPickerItemHeightValue.Unit() == DimensionUnit::PERCENT) {
            height = pickerTheme->GetGradientHeight().ConvertToPx() * defaultPickerItemHeightValue.Value();
        } else {
            height = context->NormalizeToPx(defaultPickerItemHeightValue);
        }
    } else {
        height = pickerTheme->GetDividerSpacing().ConvertToPx();
    }
    if (!NearEqual(defaultPickerItemHeight_, height)) {
        defaultPickerItemHeight_ = height;
        PaintFocusState();
        SetButtonIdeaSize();
    }
    auto frameNodes = GetColumnNodes();
    for (auto it : frameNodes) {
        CHECK_NULL_RETURN(it.second, height);
        auto textPickerColumnPattern = it.second->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_RETURN(textPickerColumnPattern, height);
        textPickerColumnPattern->SetDefaultPickerItemHeight(height);
        textPickerColumnPattern->ResetOptionPropertyHeight();
        textPickerColumnPattern->NeedResetOptionPropertyHeight(true);
    }
    return height;
}

void TextPickerPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
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

void TextPickerPattern::PaintFocusState()
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

void TextPickerPattern::SetFocusCornerRadius(RoundRect& paintRect)
{
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
}

RectF TextPickerPattern::CalculatePaintRect(int32_t currentFocusIndex,
    float centerX, float centerY, float paintRectWidth, float paintRectHeight, float columnWidth)
{
    if (!GetIsShowInDialog()) {
        paintRectWidth = columnWidth - FOCUS_WIDTH.ConvertToPx() - PRESS_RADIUS.ConvertToPx();
        centerX = currentFocusIndex * columnWidth + (columnWidth - paintRectWidth) / HALF;
        AdjustFocusBoxOffset(centerX, centerY);
    } else {
        paintRectHeight = paintRectHeight - DIALOG_OFFSET.ConvertToPx();
        centerY = centerY + DIALOG_OFFSET_LENGTH.ConvertToPx();
        paintRectWidth = columnWidth - FOCUS_WIDTH.ConvertToPx() - PRESS_RADIUS.ConvertToPx();
        centerX = currentFocusIndex * columnWidth + (columnWidth - paintRectWidth) / HALF;
    }
    return RectF(centerX, centerY, paintRectWidth, paintRectHeight);
}

void TextPickerPattern::AdjustFocusBoxOffset(float& centerX, float& centerY)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    if (geometryNode->GetPadding()) {
        centerX += geometryNode->GetPadding()->left.value_or(0.0);
        centerY += geometryNode->GetPadding()->top.value_or(0.0);
    }
}

void TextPickerPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childSize = static_cast<int32_t>(host->GetChildren().size());
    if (childSize == 0) {
        return;
    }
    if (useButtonFocusArea_) {
        auto leftTotalColumnWidth = 0.0f;
        CalcLeftTotalColumnWidth(host, leftTotalColumnWidth, childSize);
        return GetInnerFocusButtonPaintRect(paintRect, leftTotalColumnWidth);
    }
    auto columnNode = GetColumnNode();
    CHECK_NULL_VOID(columnNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto stackChild = DynamicCast<FrameNode>(host->GetChildAtIndex(focusKeyID_));
    CHECK_NULL_VOID(stackChild);
    auto blendChild = DynamicCast<FrameNode>(stackChild->GetLastChild());
    CHECK_NULL_VOID(blendChild);
    auto pickerChild = DynamicCast<FrameNode>(blendChild->GetLastChild());
    CHECK_NULL_VOID(pickerChild);
    auto columnWidth = pickerChild->GetGeometryNode()->GetFrameSize().Width();
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetPaddingSize();
    auto dividerSpacing = pipeline->NormalizeToPx(pickerTheme->GetDividerSpacing());
    auto pickerThemeWidth = dividerSpacing * RATE;
    auto currentFocusIndex = focusKeyID_;
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (isRtl) {
        currentFocusIndex = childSize - 1 - focusKeyID_;
    }
    auto itemHeight = GreatNotEqual(defaultPickerItemHeight_, 0.0f) ? defaultPickerItemHeight_ : dividerSpacing;
    auto centerX = (frameSize.Width() / childSize - pickerThemeWidth) / RATE +
                   columnNode->GetGeometryNode()->GetFrameRect().Width() * currentFocusIndex +
                   PRESS_INTERVAL.ConvertToPx() * RATE;
    auto centerY = (frameSize.Height() - itemHeight) / RATE +
                   FOCUS_INTERVAL.ConvertToPx() + LINE_WIDTH.ConvertToPx();
    float paintRectWidth = columnWidth - FOCUS_INTERVAL.ConvertToPx() * RATE - LINE_WIDTH.ConvertToPx() * RATE;
    float paintRectHeight = itemHeight - FOCUS_INTERVAL.ConvertToPx() * RATE - LINE_WIDTH.ConvertToPx() * RATE;
    if (LessNotEqual(paintRectHeight, 0.0f)) {
        paintRectHeight = 0.0f;
    }
    auto focusPaintRect = CalculatePaintRect(currentFocusIndex,
        centerX, centerY, paintRectWidth, paintRectHeight, columnWidth);
    paintRect.SetRect(focusPaintRect);
    SetFocusCornerRadius(paintRect);
}

bool TextPickerPattern::OnKeyEvent(const KeyEvent& event)
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

void TextPickerPattern::SetChangeCallback(ColumnChangeCallback&& value)
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
        auto textPickerColumnPattern = childNode->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(textPickerColumnPattern);
        textPickerColumnPattern->SetChangeCallback(std::move(value));
    }
}

size_t TextPickerPattern::ProcessCascadeOptionDepth(const NG::TextCascadePickerOptions& option)
{
    size_t depth = 1;
    if (option.children.empty()) {
        return depth;
    }

    for (auto& pos : option.children) {
        size_t tmpDep = 1;
        tmpDep += ProcessCascadeOptionDepth(pos);
        if (tmpDep > depth) {
            depth = tmpDep;
        }
    }
    return depth;
}

bool TextPickerPattern::ChangeCurrentOptionValue(NG::TextCascadePickerOptions& option,
    uint32_t value, uint32_t curColumn, uint32_t replaceColumn)
{
    if (curColumn >= replaceColumn) {
        selecteds_[curColumn] = value;
        values_[curColumn] = "";
    }

    for (uint32_t valueIndex = 0; valueIndex < option.children.size(); valueIndex++) {
        if (curColumn >= replaceColumn) {
            if (ChangeCurrentOptionValue(option.children[valueIndex], 0, curColumn + 1, replaceColumn)) {
                return true;
            }
        } else {
            if (ChangeCurrentOptionValue(option.children[valueIndex], value, curColumn + 1, replaceColumn)) {
                return true;
            }
        }
    }
    return false;
}

void TextPickerPattern::ProcessCascadeOptionsValues(const std::vector<std::string>& rangeResultValue,
    uint32_t index)
{
    auto valueIterator = std::find(rangeResultValue.begin(), rangeResultValue.end(), values_[index]);
    if (valueIterator != rangeResultValue.end()) {
        if (index < selecteds_.size()) {
            selecteds_[index] = static_cast<uint32_t>(std::distance(rangeResultValue.begin(), valueIterator));
        } else {
            selecteds_.emplace_back(std::distance(rangeResultValue.begin(), valueIterator));
        }
    } else {
        if (index < selecteds_.size()) {
            selecteds_[index] = 0;
        } else {
            selecteds_.emplace_back(0);
        }
    }
}

void TextPickerPattern::ProcessCascadeOptions(const std::vector<NG::TextCascadePickerOptions>& options,
    std::vector<NG::TextCascadePickerOptions>& reOptions, uint32_t index)
{
    std::vector<std::string> rangeResultValue;
    NG::TextCascadePickerOptions option;
    for (size_t i = 0; i < options.size(); i++) {
        if (!options[i].rangeResult.empty()) {
            rangeResultValue.emplace_back(options[i].rangeResult[0]);
        }
    }
    option.rangeResult = rangeResultValue;
    for (size_t i = 0; i < options.size(); i++) {
        if (index < selecteds_.size() &&
            ((selecteds_[index] != 0 && !isHasSelectAttr_) || isHasSelectAttr_)) {
            if (selecteds_[index] < 0 && selecteds_[index] > options.size()) {
                selecteds_[index] = 0;
            }
            option.children = options[selecteds_[index]].children;
            reOptions.emplace_back(option);
            return ProcessCascadeOptions(options[selecteds_[index]].children, reOptions, index + 1);
        }
        if (index < values_.size() && values_[index] != "") {
            ProcessCascadeOptionsValues(rangeResultValue, index);
            option.children = options[selecteds_[index]].children;
            reOptions.emplace_back(option);
            return ProcessCascadeOptions(options[selecteds_[index]].children, reOptions, index + 1);
        }
        if (options.size() > 0 && options.size() == i + 1) {
            option.children = options[0].children;
            reOptions.emplace_back(option);
            return ProcessCascadeOptions(options[0].children, reOptions, index + 1);
        }
    }
}

void TextPickerPattern::SupplementOption(const std::vector<NG::TextCascadePickerOptions>& reOptions,
    std::vector<NG::RangeContent>& rangeContents, uint32_t patterIndex)
{
    for (uint32_t i = 0; i < reOptions[patterIndex].rangeResult.size(); i++) {
        NG::RangeContent rangeContent;
        rangeContent.text_ = reOptions[patterIndex].rangeResult[i];
        rangeContents.emplace_back(rangeContent);
    }
}

void TextPickerPattern::HandleColumnChange(const RefPtr<FrameNode>& tag, bool isAdd,
    uint32_t index, bool needNotify)
{
    if (isCascade_) {
        auto frameNodes = GetColumnNodes();
        uint32_t columnIndex = 0;
        for (auto iter = frameNodes.begin(); iter != frameNodes.end(); iter++) {
            if (iter->second->GetId() == tag->GetId()) {
                break;
            }
            columnIndex++;
        }
        for (uint32_t valueIndex = 0; valueIndex < cascadeOriginptions_.size(); valueIndex++) {
            ChangeCurrentOptionValue(cascadeOriginptions_[valueIndex], index, 0, columnIndex);
        }

        std::vector<NG::TextCascadePickerOptions> reOptions;
        ProcessCascadeOptions(cascadeOriginptions_, reOptions, 0);
        // Next Column Update Value
        columnIndex = columnIndex + 1;
        for (uint32_t patterIndex = columnIndex; patterIndex < frameNodes.size(); patterIndex++) {
            auto patternNode = frameNodes[patterIndex];
            CHECK_NULL_VOID(patternNode);
            auto textPickerColumnPattern = patternNode->GetPattern<TextPickerColumnPattern>();
            CHECK_NULL_VOID(textPickerColumnPattern);
            if (patterIndex < reOptions.size()) {
                auto currentSelectedIndex = reOptions[patterIndex].rangeResult.empty() ? 0 :
                             selecteds_[patterIndex] % reOptions[patterIndex].rangeResult.size();
                std::vector<NG::RangeContent> rangeContents;
                SupplementOption(reOptions, rangeContents, patterIndex);
                textPickerColumnPattern->SetCurrentIndex(currentSelectedIndex);
                textPickerColumnPattern->SetOptions(rangeContents);
                textPickerColumnPattern->FlushCurrentOptions();
            } else {
                textPickerColumnPattern->ClearOptions();
                textPickerColumnPattern->SetCurrentIndex(0);
                textPickerColumnPattern->FlushCurrentOptions(false, false, true);
            }
        }
    }
}

void TextPickerPattern::CheckFocusID(int32_t childSize)
{
    if (focusKeyID_ > childSize - 1) {
        focusKeyID_ = childSize - 1;
    } else if (focusKeyID_ < 0) {
        focusKeyID_ = 0;
    }
}

bool TextPickerPattern::ParseDirectionKey(RefPtr<TextPickerColumnPattern>& textPickerColumnPattern,
    KeyCode& code, uint32_t totalOptionCount, int32_t childSize)
{
    bool result = true;
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    switch (code) {
        case KeyCode::KEY_DPAD_UP:
            if (textPickerColumnPattern->InnerHandleScroll(false, false)) {
                textPickerColumnPattern->HandleScrollStopEventCallback(true);
            }
            break;

        case KeyCode::KEY_DPAD_DOWN:
            if (textPickerColumnPattern->InnerHandleScroll(true, false)) {
                textPickerColumnPattern->HandleScrollStopEventCallback(true);
            }
            break;

        case KeyCode::KEY_MOVE_HOME:
            textPickerColumnPattern->SetCurrentIndex(1);
            if (textPickerColumnPattern->InnerHandleScroll(false, false)) {
                textPickerColumnPattern->HandleScrollStopEventCallback(true);
            }
            break;

        case KeyCode::KEY_MOVE_END:
            textPickerColumnPattern->SetCurrentIndex(totalOptionCount - UNOPTION_COUNT);
            if (textPickerColumnPattern->InnerHandleScroll(true, false)) {
                textPickerColumnPattern->HandleScrollStopEventCallback(true);
            }
            break;

        case KeyCode::KEY_DPAD_LEFT:
            focusKeyID_ = isRtl ? (focusKeyID_ + 1) : (focusKeyID_ - 1);
            CheckFocusID(childSize);
            PaintFocusState();
            break;

        case KeyCode::KEY_DPAD_RIGHT:
            focusKeyID_ = isRtl ? (focusKeyID_ - 1) : (focusKeyID_ + 1);
            CheckFocusID(childSize);
            PaintFocusState();
            break;

        default:
            result = false;
            break;
    }
    return result;
}

bool TextPickerPattern::HandleDirectionKey(KeyCode code)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto childSize = host->GetChildren().size();
    auto frameNode = GetColumnNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto textPickerColumnPattern = frameNode->GetPattern<TextPickerColumnPattern>();
    CHECK_NULL_RETURN(textPickerColumnPattern, false);
    auto totalOptionCount = textPickerColumnPattern->GetOptionCount();
    if (totalOptionCount == 0) {
        return false;
    }
    return ParseDirectionKey(textPickerColumnPattern, code, totalOptionCount, static_cast<int32_t>(childSize));
}

std::string TextPickerPattern::GetSelectedObjectMulti(const std::vector<std::string>& values,
    const std::vector<uint32_t>& indexs, int32_t status) const
{
    std::string result = "";
    result = std::string("{\"value\":") + "[";
    const size_t valueSize = values.size();
    for (uint32_t i = 0; i < valueSize; i++) {
        result += "\"" + values[i];
        if (valueSize > 0 && i != valueSize - 1) {
            result += "\",";
        } else {
            result += "\"]";
        }
    }
    result += std::string(",\"index\":") + "[";
    const size_t indexSize = indexs.size();
    for (uint32_t i = 0; i < indexSize; i++) {
        result += std::to_string(indexs[i]);
        if (indexSize > 0 && indexSize != i + 1) {
            result += ",";
        } else {
            result += "]";
        }
    }
    result += ",\"status\":" + std::to_string(status) + "}";
    return result;
}

std::string TextPickerPattern::GetSelectedObject(
    bool isColumnChange, int32_t status, bool isEnterSelectedAreaEvent) const
{
    std::vector<std::string> values;
    std::vector<uint32_t> indexs;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "");
    auto children = host->GetChildren();
    for (const auto& child : children) {
        CHECK_NULL_RETURN(child, "");
        auto stackNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_RETURN(stackNode, "");
        auto blendNode = DynamicCast<FrameNode>(stackNode->GetLastChild());
        CHECK_NULL_RETURN(blendNode, "");
        auto currentNode = DynamicCast<FrameNode>(blendNode->GetLastChild());
        CHECK_NULL_RETURN(currentNode, "");
        auto textPickerColumnPattern = currentNode->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_RETURN(textPickerColumnPattern, "");
        auto value = textPickerColumnPattern->GetOption(textPickerColumnPattern->GetSelected());
        auto index = textPickerColumnPattern->GetSelected();
        if (isColumnChange) {
            value = textPickerColumnPattern->GetCurrentText();
            index = textPickerColumnPattern->GetCurrentIndex();
        }
        if (isEnterSelectedAreaEvent) {
            value = textPickerColumnPattern->GetEnterText();
            index = textPickerColumnPattern->GetEnterIndex();
        }
        values.emplace_back(value);
        indexs.emplace_back(index);
    }

    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, "");
    if (context->GetIsDeclarative()) {
        if (values.size() == 1) {
            return std::string("{\"value\":") + "\"" + values[0] + "\"" + ",\"index\":" + std::to_string(indexs[0]) +
                   ",\"status\":" + std::to_string(status) + "}";
        } else {
            return GetSelectedObjectMulti(values, indexs, status);
        }
    } else {
        return std::string("{\"newValue\":") + "\"" +
                values[0] + "\"" + ",\"newSelected\":" + std::to_string(indexs[0]) +
               ",\"status\":" + std::to_string(status) + "}";
    }
}

void TextPickerPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    if (!range_.empty()) {
        json->PutExtAttr("range", GetRangeStr().c_str(), filter);
    } else {
        if (!cascadeOriginptions_.empty()) {
            if (!isCascade_) {
                json->PutExtAttr("range", GetOptionsMultiStr().c_str(), filter);
            } else {
                json->PutExtAttr("range", GetOptionsCascadeStr(cascadeOriginptions_).c_str(), filter);
            }
        }
    }
    json->PutExtAttr("enableHapticFeedback", isEnableHaptic_, filter);
    if (!columnWidths_.empty()) {
        json->PutExtAttr("columnWidths", GetColumnWidthsStr().c_str(), filter);
    }
}

std::string TextPickerPattern::GetRangeStr() const
{
    if (!range_.empty()) {
        std::string result = "[";
        for (const auto& item : range_) {
            result += "\"";
            result += "icon:";
            result += item.icon_;
            result += ",";
            result += "text:";
            result += item.text_;
            result += "\"";
            result += ",";
        }
        result.pop_back();
        result += "]";
        return result;
    }
    return "";
}

std::string TextPickerPattern::GetOptionsCascadeStr(
    const std::vector<NG::TextCascadePickerOptions>& options) const
{
    std::string result = "[";
    for (uint32_t i = 0; i < options.size(); i++) {
        result += std::string("{\"text\":\"");
        result += options[i].rangeResult[0];
        result += "\"";
        if (options[i].children.size() > 0) {
            result += std::string(", \"children\":");
            result += GetOptionsCascadeStr(options[i].children);
        }
        if (options.size() > 0 && options.size() != i + 1) {
            result += "},";
        } else {
            result += "}]";
        }
    }
    return result;
}

std::string TextPickerPattern::GetOptionsMultiStrInternal() const
{
    std::string result = "[";
    const size_t size = cascadeOptions_.size();
    for (uint32_t i = 0; i < size; i++) {
        result += "[";
        for (uint32_t j = 0; j < cascadeOptions_[i].rangeResult.size(); j++) {
            result += "\"" + cascadeOptions_[i].rangeResult[j];
            if (j + 1 != cascadeOptions_[i].rangeResult.size()) {
                result += "\",";
            } else {
                result += "\"]";
            }
        }
        if (size > 0 && i != size - 1) {
            result += ",";
        } else {
            result += "]";
        }
    }
    return result;
}

std::string TextPickerPattern::GetOptionsMultiStr() const
{
    std::string result = "";
    if (!cascadeOptions_.empty()) {
        result = GetOptionsMultiStrInternal();
    }
    return result;
}

std::string TextPickerPattern::GetColumnWidthsStr() const
{
    std::string result = "";
    for (const auto& item : columnWidths_) {
        result += item.ToString();
        result += ",";
    }
    result.pop_back();
    return result;
}

void TextPickerPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetNeedCallChildrenUpdate(false);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(pickerTheme);
    auto disappearStyle = pickerTheme->GetDisappearOptionStyle();
    auto normalStyle = pickerTheme->GetOptionStyle(false, false);
    auto selectedStyle = pickerTheme->GetOptionStyle(true, false);
    auto pickerProperty = host->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_VOID(pickerProperty);
    pickerProperty->UpdateColor(GetTextProperties().normalTextStyle_.textColor.value_or(normalStyle.GetTextColor()));
    pickerProperty->UpdateDisappearColor(
        GetTextProperties().disappearTextStyle_.textColor.value_or(disappearStyle.GetTextColor()));
    pickerProperty->UpdateSelectedColor(
        GetTextProperties().selectedTextStyle_.textColor.value_or(selectedStyle.GetTextColor()));
    if (isPicker_) {
        return;
    }
    auto dialogTheme = context->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    SetBackgroundColor(dialogTheme->GetBackgroundColor());
    auto contentRowNode = contentRowNode_.Upgrade();
    if (contentRowNode) {
        auto layoutRenderContext = contentRowNode->GetRenderContext();
        CHECK_NULL_VOID(layoutRenderContext);
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) ||
            !layoutRenderContext->IsUniRenderEnabled()) {
            layoutRenderContext->UpdateBackgroundColor(dialogTheme->GetButtonBackgroundColor());
        }
    }
    auto frameNode = DynamicCast<FrameNode>(host);
    CHECK_NULL_VOID(frameNode);
    FrameNode::ProcessOffscreenNode(frameNode);
    host->MarkModifyDone();
}

bool TextPickerPattern::OnThemeScopeUpdate(int32_t themeScopeId)
{
    bool result = false;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, result);
    host->SetNeedCallChildrenUpdate(false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, result);
    auto pickerProperty = host->GetLayoutProperty<TextPickerLayoutProperty>();
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

void TextPickerPattern::OnDirectionConfigurationUpdate()
{
    isNeedUpdateSelectedIndex_ = false;
}

void TextPickerPattern::CheckAndUpdateColumnSize(SizeF& size, RefPtr<FrameNode>& frameNode, bool isNeedAdaptForAging)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pickerNode = DynamicCast<FrameNode>(host);
    CHECK_NULL_VOID(pickerNode);
    auto stackNode = DynamicCast<FrameNode>(pickerNode->GetFirstChild());
    CHECK_NULL_VOID(stackNode);

    auto pickerLayoutProperty = pickerNode->GetLayoutProperty();
    CHECK_NULL_VOID(pickerLayoutProperty);
    auto pickerLayoutConstraint = pickerLayoutProperty->GetLayoutConstraint();

    auto stackLayoutProperty = stackNode->GetLayoutProperty();
    CHECK_NULL_VOID(stackLayoutProperty);
    auto stackLayoutConstraint = stackLayoutProperty->GetLayoutConstraint();

    auto childCount = static_cast<float>(pickerNode->GetChildren().size());
    auto pickerContentSize = SizeF(size.Width() * childCount, size.Height());
    auto parentIdealSize = stackLayoutConstraint->parentIdealSize;
    if (parentIdealSize.Width().has_value()) {
        pickerContentSize.SetWidth(parentIdealSize.Width().value());
    }
    if (parentIdealSize.Height().has_value()) {
        pickerContentSize.SetHeight(parentIdealSize.Height().value());
    }

    PaddingPropertyF padding = pickerLayoutProperty->CreatePaddingAndBorder();
    auto minSize = SizeF(pickerLayoutConstraint->minSize.Width(), pickerLayoutConstraint->minSize.Height());
    MinusPaddingToSize(padding, minSize);
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    auto version10OrLarger = context->GetMinPlatformVersion() > 9;
    if (!(minSize.Width() == 0 && minSize.Height() == 0 &&
        stackLayoutConstraint->maxSize.Width() == 0 && stackLayoutConstraint->maxSize.Height() == 0)) {
            pickerContentSize.Constrain(minSize, stackLayoutConstraint->maxSize, version10OrLarger);
    }

    if (isNeedAdaptForAging && GetIsShowInDialog()) {
        size.SetWidth(pickerContentSize.Width());
    } else {
        auto index = CalculateIndex(frameNode);
        if (index < 0 || index >= static_cast<int32_t>(childCount)) {
            return;
        }
        float width = CalculateColumnSize(index, childCount, pickerContentSize);
        size.SetWidth(width);
    }
    size.SetHeight(std::min(pickerContentSize.Height(), size.Height()));
}

int32_t TextPickerPattern::CalculateIndex(RefPtr<FrameNode>& frameNode)
{
    auto allChildNode = GetColumnNodes();
    int32_t index = -1;
    for (const auto& child : allChildNode) {
        if (child.second == frameNode) {
            index = child.first;
            break;
        }
    }
    return index;
}

float TextPickerPattern::CalculateColumnSize(int32_t index, float childCount, const SizeF& pickerContentSize)
{
    float widthSum = 0.0f;
    for (size_t i = 0; i < std::min(columnWidths_.size(), static_cast<size_t>(childCount)); i++) {
        columnWidths_[i] = columnWidths_[i].Unit() != DimensionUnit::PERCENT ?
            Dimension(columnWidths_[i].ConvertToPx(), DimensionUnit::PX) :
            Dimension(pickerContentSize.Width() * columnWidths_[i].Value() / MAX_PERCENT, DimensionUnit::PX);

        if (LessNotEqual(columnWidths_[i].Value(), 0.0f) && !NearZero(childCount)) {
            columnWidths_[i].SetValue(pickerContentSize.Width() / childCount);
        }

        widthSum += columnWidths_[i].Value();
    }

    if (GreatNotEqual(widthSum, pickerContentSize.Width())) {
        return pickerContentSize.Width() / std::max(childCount, 1.0f);
    }

    if (static_cast<size_t>(index) >= columnWidths_.size()) {
        columnWidths_.emplace_back(Dimension((pickerContentSize.Width() - widthSum) /
            (childCount - columnWidths_.size()), DimensionUnit::PX));
    }
    return columnWidths_.size() == 0 ?
        pickerContentSize.Width() / std::max(childCount, 1.0f) : columnWidths_[index].Value();
}

void TextPickerPattern::SetCanLoop(bool isLoop)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    canloop_ = isLoop;
    for (const auto& child : children) {
        auto stackNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(stackNode);
        auto blendNode = DynamicCast<FrameNode>(stackNode->GetLastChild());
        CHECK_NULL_VOID(blendNode);
        auto childNode = DynamicCast<FrameNode>(blendNode->GetLastChild());
        CHECK_NULL_VOID(childNode);
        auto pickerColumnPattern = childNode->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(pickerColumnPattern);
        pickerColumnPattern->SetCanLoop(isLoop);
    }
}

bool TextPickerPattern::NeedAdaptForAging()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, false);

    if (GreatOrEqual(pipeline->GetFontScale(), pickerTheme->GetMaxOneFontScale())) {
        return true;
    }
    return false;
}

void TextPickerPattern::SetDisableTextStyleAnimation(bool isDisableTextStyleAnimation)
{
    isDisableTextStyleAnimation_ = isDisableTextStyleAnimation;

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
        auto pickerColumnPattern = childNode->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(pickerColumnPattern);
        pickerColumnPattern->SetDisableTextStyleAnimation(isDisableTextStyleAnimation);
    }
}

void TextPickerPattern::UpdateUserSetSelectColor()
{
    CHECK_EQUAL_VOID(IsCircle(), false);
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
        auto pickerColumnPattern = childNode->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(pickerColumnPattern);
        pickerColumnPattern->UpdateUserSetSelectColor();
    }
}

std::string TextPickerPattern::GetTextPickerRange() const
{
    std::string result;
    if (isSingleRange_) {
        for (auto range : range_) {
            result.append(range.text_ + ";");
        }
        if (result.length() > 0) {
            result = result.substr(0, result.length() > 0 ? result.length() - 1 : 0);
        }
    } else {
        for (auto option : cascadeOriginptions_) {
            for (auto range : option.rangeResult) {
                result.append(range + ",");
            }
            result = result.substr(0, result.length() > 0 ? result.length() - 1 : 0);
            result.append(";");
        }
        if (result.length() > 0) {
            result = result.substr(0, result.length() - 1);
        }
    }
    return result;
}
} // namespace OHOS::Ace::NG
