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
#include "core/components_ng/pattern/bubble/bubble_view.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/color.h"
#include "core/components/popup/popup_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/render/paint_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
OffsetF GetDisplayWindowRectOffset()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, OffsetF());
    auto overlayManager = pipelineContext->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, OffsetF());
    auto displayWindowOffset = OffsetF(pipelineContext->GetDisplayWindowRectInfo().GetOffset().GetX(),
        pipelineContext->GetDisplayWindowRectInfo().GetOffset().GetY());
    return displayWindowOffset;
}

RefPtr<PopupTheme> GetPopupTheme()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto popupTheme = pipeline->GetTheme<PopupTheme>();
    CHECK_NULL_RETURN(popupTheme, nullptr);
    return popupTheme;
}

Dimension GetMaxWith()
{
    auto gridColumnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::BUBBLE_TYPE);
    auto parent = gridColumnInfo->GetParent();
    if (parent) {
        parent->BuildColumnWidth();
    }
    auto maxWidth = Dimension(gridColumnInfo->GetMaxWidth());
    return maxWidth;
}

void UpdateTextProperties(const RefPtr<PopupParam>& param, const RefPtr<TextLayoutProperty>& textLayoutProps)
{
    auto textColor = param->GetTextColor();
    if (textColor.has_value()) {
        textLayoutProps->UpdateTextColor(textColor.value());
    }
    auto fontSize = param->GetFontSize();
    if (fontSize.has_value()) {
        textLayoutProps->UpdateFontSize(fontSize.value());
    }
    auto fontWeight = param->GetFontWeight();
    if (fontWeight.has_value()) {
        textLayoutProps->UpdateFontWeight(fontWeight.value());
    }
    auto fontStyle = param->GetFontStyle();
    if (fontStyle.has_value()) {
        textLayoutProps->UpdateItalicFontStyle(fontStyle.value());
    }
}
} // namespace

RefPtr<FrameNode> BubbleView::CreateBubbleNode(
    const std::string& targetTag, int32_t targetId, const RefPtr<PopupParam>& param)
{
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    auto popupProp = AceType::DynamicCast<BubbleLayoutProperty>(popupNode->GetLayoutProperty());
    auto popupPaintProp = popupNode->GetPaintProperty<BubbleRenderProperty>();
    auto useCustom = param->IsUseCustom();

    // onstateChange.
    auto bubbleHub = popupNode->GetEventHub<BubbleEventHub>();
    if (bubbleHub) {
        bubbleHub->SetOnStateChange(param->GetOnStateChange());
    }

    auto message = param->GetMessage();
    auto primaryButton = param->GetPrimaryButtonProperties();
    auto secondaryButton = param->GetSecondaryButtonProperties();
    // Update props
    popupProp->UpdateUseCustom(useCustom);
    popupProp->UpdateEnableArrow(param->EnableArrow());
    popupProp->UpdatePlacement(param->GetPlacement());
    popupProp->UpdateShowInSubWindow(param->IsShowInSubWindow());
    popupProp->UpdatePositionOffset(OffsetF(param->GetTargetOffset().GetX(), param->GetTargetOffset().GetY()));
    popupProp->UpdateBlockEvent(param->IsBlockEvent());
    if (param->GetTargetSpace().has_value()) {
        popupProp->UpdateTargetSpace(param->GetTargetSpace().value());
    }
    auto displayWindowOffset = GetDisplayWindowRectOffset();
    popupProp->UpdateDisplayWindowOffset(displayWindowOffset);
    popupPaintProp->UpdateEnableArrow(param->EnableArrow());
    if (param->GetArrowOffset().has_value()) {
        popupPaintProp->UpdateArrowOffset(param->GetArrowOffset().value());
    }
    if (param->IsMaskColorSetted()) {
        popupPaintProp->UpdateMaskColor(param->GetMaskColor());
    }
    if (param->IsBackgroundColorSetted()) {
        popupPaintProp->UpdateBackgroundColor(param->GetBackgroundColor());
    }
    popupPaintProp->UpdateAutoCancel(!param->HasAction());
    popupPaintProp->UpdatePlacement(param->GetPlacement());

    auto bubbleAccessibilityProperty = popupNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_RETURN(bubbleAccessibilityProperty, nullptr);
    bubbleAccessibilityProperty->SetText(message);
    auto bobblePattern = popupNode->GetPattern<BubblePattern>();
    // Create child
    RefPtr<FrameNode> child;
    if (primaryButton.showButton || secondaryButton.showButton) {
        child = CreateCombinedChild(param, popupId, targetId, popupNode);
        popupPaintProp->UpdatePrimaryButtonShow(primaryButton.showButton);
        popupPaintProp->UpdateSecondaryButtonShow(secondaryButton.showButton);
        popupPaintProp->UpdateAutoCancel(false);
    } else {
        auto textNode = CreateMessage(message, useCustom);
        bobblePattern->SetMessageNode(textNode);
        auto popupTheme = GetPopupTheme();
        auto padding = popupTheme->GetPadding();
        auto layoutProps = textNode->GetLayoutProperty<TextLayoutProperty>();
        PaddingProperty textPadding;
        textPadding.left = CalcLength(padding.Left());
        textPadding.right = CalcLength(padding.Right());
        textPadding.top = CalcLength(padding.Top());
        textPadding.bottom = CalcLength(padding.Bottom());
        layoutProps->UpdatePadding(textPadding);
        layoutProps->UpdateAlignment(Alignment::CENTER);
        UpdateTextProperties(param, layoutProps);
        auto buttonMiniMumHeight = popupTheme->GetBubbleMiniMumHeight().ConvertToPx();
        layoutProps->UpdateCalcMinSize(CalcSize(std::nullopt, CalcLength(buttonMiniMumHeight)));
        textNode->MarkModifyDone();
        child = textNode;
    }
    // TODO: GridSystemManager is not completed, need to check later.
    auto maxWidth = GetMaxWith();
    auto childLayoutProperty = child->GetLayoutProperty();
    CHECK_NULL_RETURN(childLayoutProperty, nullptr);
    childLayoutProperty->UpdateCalcMaxSize(CalcSize(NG::CalcLength(maxWidth), std::nullopt));
    child->MountToParent(popupNode);
    return popupNode;
}
RefPtr<FrameNode> BubbleView::CreateCustomBubbleNode(
    const std::string& targetTag, int32_t targetId, const RefPtr<UINode>& customNode, const RefPtr<PopupParam>& param)
{
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    auto bubbleHub = popupNode->GetEventHub<BubbleEventHub>();
    if (bubbleHub) {
        bubbleHub->SetOnStateChange(param->GetOnStateChange());
    }
    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    popupPattern->SetCustomPopupTag(true);
    // update bubble props
    auto layoutProps = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    layoutProps->UpdateUseCustom(param->IsUseCustom());
    layoutProps->UpdateEnableArrow(param->EnableArrow());
    layoutProps->UpdatePlacement(param->GetPlacement());
    layoutProps->UpdateShowInSubWindow(param->IsShowInSubWindow());
    layoutProps->UpdateBlockEvent(param->IsBlockEvent());
    auto displayWindowOffset = GetDisplayWindowRectOffset();
    layoutProps->UpdateDisplayWindowOffset(displayWindowOffset);
    layoutProps->UpdatePositionOffset(OffsetF(param->GetTargetOffset().GetX(), param->GetTargetOffset().GetY()));
    if (param->GetTargetSpace().has_value()) {
        layoutProps->UpdateTargetSpace(param->GetTargetSpace().value());
    }
    auto popupPaintProps = popupNode->GetPaintProperty<BubbleRenderProperty>();
    popupPaintProps->UpdateUseCustom(param->IsUseCustom());
    popupPaintProps->UpdateEnableArrow(param->EnableArrow());
    if (param->GetArrowOffset().has_value()) {
        popupPaintProps->UpdateArrowOffset(param->GetArrowOffset().value());
    }
    if (param->IsMaskColorSetted()) {
        popupPaintProps->UpdateMaskColor(param->GetMaskColor());
    }
    if (param->IsBackgroundColorSetted()) {
        popupPaintProps->UpdateBackgroundColor(param->GetBackgroundColor());
    }
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    customNode->MountToParent(columnNode);
    auto renderContext = columnNode->GetRenderContext();
    if (renderContext) {
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    }
    popupPaintProps->UpdateAutoCancel(!param->HasAction());
    popupPaintProps->UpdatePlacement(param->GetPlacement());
    columnNode->MountToParent(popupNode);
    return popupNode;
}

void BubbleView::UpdatePopupParam(int32_t popupId, const RefPtr<PopupParam>& param, const RefPtr<FrameNode>& targetNode)
{
    UpdateCommonParam(popupId, param);
    auto popupNode = FrameNode::GetFrameNode(V2::POPUP_ETS_TAG, popupId);
    CHECK_NULL_VOID(popupNode);
    auto popupProp = AceType::DynamicCast<BubbleLayoutProperty>(popupNode->GetLayoutProperty());
    auto popupPaintProp = popupNode->GetPaintProperty<BubbleRenderProperty>();
    auto message = param->GetMessage();
    auto primaryButton = param->GetPrimaryButtonProperties();
    auto secondaryButton = param->GetSecondaryButtonProperties();
    // Update layout props
    popupProp->UpdateUseCustom(param->IsUseCustom());
    popupProp->UpdateEnableArrow(param->EnableArrow());
    popupProp->UpdatePlacement(param->GetPlacement());
    auto displayWindowOffset = GetDisplayWindowRectOffset();
    popupProp->UpdateDisplayWindowOffset(displayWindowOffset);
    // Update paint props
    popupPaintProp->UpdatePlacement(param->GetPlacement());
    popupPaintProp->UpdateUseCustom(param->IsUseCustom());
    popupPaintProp->UpdateEnableArrow(param->EnableArrow());
}

void BubbleView::UpdateCustomPopupParam(int32_t popupId, const RefPtr<PopupParam>& param)
{
    UpdateCommonParam(popupId, param);
    auto popupNode = FrameNode::GetFrameNode(V2::POPUP_ETS_TAG, popupId);
    CHECK_NULL_VOID(popupNode);
    auto popupLayoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    CHECK_NULL_VOID(popupLayoutProp);
    auto popupPaintProp = popupNode->GetPaintProperty<BubbleRenderProperty>();
    CHECK_NULL_VOID(popupPaintProp);
    popupLayoutProp->UpdatePlacement(param->GetPlacement());
    popupPaintProp->UpdatePlacement(param->GetPlacement());
    if (param->IsBackgroundColorSetted()) {
        popupPaintProp->UpdateBackgroundColor(param->GetBackgroundColor());
    }
    popupLayoutProp->UpdateEnableArrow(param->EnableArrow());
    popupPaintProp->UpdateAutoCancel(!param->HasAction());
}

void BubbleView::UpdateCommonParam(int32_t popupId, const RefPtr<PopupParam>& param)
{
    auto popupNode = FrameNode::GetFrameNode(V2::POPUP_ETS_TAG, popupId);
    CHECK_NULL_VOID(popupNode);
    auto bubbleHub = popupNode->GetEventHub<BubbleEventHub>();
    if (bubbleHub) {
        bubbleHub->SetOnStateChange(param->GetOnStateChange());
    }
    auto popupLayoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    CHECK_NULL_VOID(popupLayoutProp);
    auto popupPaintProp = popupNode->GetPaintProperty<BubbleRenderProperty>();
    CHECK_NULL_VOID(popupPaintProp);
    if (param->GetArrowOffset().has_value()) {
        popupPaintProp->UpdateArrowOffset(param->GetArrowOffset().value());
    }
    popupLayoutProp->UpdateShowInSubWindow(param->IsShowInSubWindow());
    popupLayoutProp->UpdateBlockEvent(param->IsBlockEvent());
    popupLayoutProp->UpdatePositionOffset(OffsetF(param->GetTargetOffset().GetX(), param->GetTargetOffset().GetY()));
    if (param->IsMaskColorSetted()) {
        popupPaintProp->UpdateMaskColor(param->GetMaskColor());
    }
    if (param->GetTargetSpace().has_value()) {
        popupLayoutProp->UpdateTargetSpace(param->GetTargetSpace().value());
    }
}

RefPtr<FrameNode> BubbleView::CreateMessage(const std::string& message, bool IsUseCustom)
{
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->UpdateContent(message);
    auto popupTheme = GetPopupTheme();
    layoutProperty->UpdateFontSize(popupTheme->GetFontSize());
    if (IsUseCustom) {
        layoutProperty->UpdateTextColor(Color::BLACK);
    } else {
        layoutProperty->UpdateTextColor(popupTheme->GetFontColor());
    }
    textNode->MarkModifyDone();
    return textNode;
}

RefPtr<FrameNode> BubbleView::CreateCombinedChild(
    const RefPtr<PopupParam>& param, int32_t popupId, int32_t targetId, const RefPtr<FrameNode>& bobbleNode)
{
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto layoutProps = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    layoutProps->UpdateMainAxisAlign(FlexAlign::FLEX_START); // mainAxisAlign
    auto message = BubbleView::CreateMessage(param->GetMessage(), param->IsUseCustom());
    auto bubblePattern = bobbleNode->GetPattern<BubblePattern>();
    CHECK_NULL_RETURN(bubblePattern, nullptr);
    bubblePattern->SetMessageNode(message);
    auto popupTheme = GetPopupTheme();
    auto padding = popupTheme->GetPadding();
    auto textLayoutProps = message->GetLayoutProperty<TextLayoutProperty>();
    PaddingProperty textPadding;
    textPadding.left = CalcLength(padding.Left());
    textPadding.right = CalcLength(padding.Right());
    textPadding.top = CalcLength(padding.Top());
    textLayoutProps->UpdatePadding(textPadding);
    textLayoutProps->UpdateAlignSelf(FlexAlign::FLEX_START);
    UpdateTextProperties(param, textLayoutProps);
    message->MarkModifyDone();
    message->MountToParent(columnNode);

    auto buttonRow = BubbleView::CreateButtons(param, popupId, targetId);
    auto buttonRowLayoutProperty = buttonRow->GetLayoutProperty<LinearLayoutProperty>();
    buttonRowLayoutProperty->UpdateAlignSelf(FlexAlign::FLEX_END);
    buttonRow->MarkModifyDone();
    auto maxWidth = GetMaxWith();
    auto childLayoutProperty = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(childLayoutProperty, nullptr);
    childLayoutProperty->UpdateCalcMaxSize(CalcSize(NG::CalcLength(maxWidth), std::nullopt));
    buttonRow->MountToParent(columnNode);

    columnNode->MarkModifyDone();
    return columnNode;
}

RefPtr<FrameNode> BubbleView::CreateButtons(const RefPtr<PopupParam>& param, int32_t popupId, int32_t targetId)
{
    auto rowId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rowNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, rowId, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto layoutProps = rowNode->GetLayoutProperty<LinearLayoutProperty>();
    layoutProps->UpdateSpace(GetPopupTheme()->GetButtonSpacing());
    auto primaryButtonProp = param->GetPrimaryButtonProperties();
    auto primaryButton = BubbleView::CreateButton(primaryButtonProp, popupId, targetId, param);
    if (primaryButton) {
        primaryButton->MountToParent(rowNode);
        primaryButton->MarkModifyDone();
    }
    auto secondaryButtonProp = param->GetSecondaryButtonProperties();
    auto secondaryButton = BubbleView::CreateButton(secondaryButtonProp, popupId, targetId, param);
    if (secondaryButton) {
        secondaryButton->MountToParent(rowNode);
        secondaryButton->MarkModifyDone();
    }
    auto popupTheme = GetPopupTheme();
    auto littlePadding = popupTheme->GetLittlePadding();
    PaddingProperty rowPadding;
    rowPadding.right = CalcLength(littlePadding);
    rowPadding.bottom = CalcLength(littlePadding);
    layoutProps->UpdatePadding(rowPadding);

    rowNode->MarkModifyDone();
    return rowNode;
}

RefPtr<FrameNode> BubbleView::CreateButton(
    ButtonProperties& buttonParam, int32_t popupId, int32_t targetId, const RefPtr<PopupParam>& param)
{
    if (!buttonParam.showButton) {
        return nullptr;
    }
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto buttonTheme = pipelineContext->GetTheme<ButtonTheme>();
    CHECK_NULL_RETURN(buttonTheme, nullptr);
    auto popupTheme = GetPopupTheme();
    auto focusColor = popupTheme->GetFocusColor();
    auto buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    auto buttonPattern = AceType::MakeRefPtr<NG::ButtonPattern>();
    CHECK_NULL_RETURN(buttonPattern, nullptr);
    // set button focus color
    buttonPattern->setComponentButtonType(ComponentButtonType::POPUP);
    buttonPattern->SetFocusBorderColor(focusColor);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, buttonId, buttonPattern);
    CHECK_NULL_RETURN(buttonPattern, nullptr);

    auto buttonProp = AceType::DynamicCast<ButtonLayoutProperty>(buttonNode->GetLayoutProperty());
    auto isUseCustom = param->IsUseCustom();
    auto isShow = param->IsShow();

    auto buttonTextNode = BubbleView::CreateMessage(buttonParam.value, isUseCustom);
    auto textLayoutProperty = buttonTextNode->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateFontSize(popupTheme->GetButtonFontSize());
    auto buttonTextInsideMargin = popupTheme->GetButtonTextInsideMargin();
    buttonTextNode->MountToParent(buttonNode);

    PaddingProperty buttonPadding;
    auto padding = buttonTheme->GetPadding();
    buttonPadding.left = CalcLength(buttonTextInsideMargin);
    buttonPadding.right = CalcLength(buttonTextInsideMargin);
    buttonProp->UpdatePadding(buttonPadding);
    buttonProp->UpdateType(ButtonType::CAPSULE);
    buttonProp->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(buttonTheme->GetHeight())));
    buttonProp->UpdateAlignment(Alignment::CENTER);
    auto buttonMiniMumWidth = popupTheme->GetButtonMiniMumWidth().ConvertToPx();
    buttonProp->UpdateCalcMinSize(CalcSize(CalcLength(buttonMiniMumWidth), std::nullopt));
    auto renderContext = buttonNode->GetRenderContext();
    if (renderContext) {
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    }
    buttonNode->MarkModifyDone();

    auto buttonEventHub = buttonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(buttonEventHub, nullptr);
    buttonEventHub->AddClickEvent(buttonParam.action);
    auto popupNode = FrameNode::GetFrameNode(V2::POPUP_ETS_TAG, popupId);
    auto closeCallback = [popupNode, targetId, isShow](GestureEvent& /* info */) {
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineContext);
        auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
        CHECK_NULL_VOID(context);
        auto overlayManager = context->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        auto popupInfo = overlayManager->GetPopupInfo(targetId);
        popupInfo.markNeedUpdate = true;
        popupInfo.popupId = -1;
        popupInfo.markNeedUpdate = isShow;
        overlayManager->UpdatePopupNode(targetId, popupInfo);
    };
    if (buttonParam.action) {
        buttonEventHub->AddClickEvent(buttonParam.action);
    } else {
        buttonEventHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(closeCallback));
    }

    return buttonNode;
}
} // namespace OHOS::Ace::NG
