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
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/render/paint_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double DOUBLENESS = 2.0;
constexpr Dimension BUBBLE_MAX_HEIGHT = 480.0_vp;
constexpr Dimension BUBBLE_MAX_WIDTH = 400.0_vp;
constexpr Dimension OUT_RANGE_SPACE = 40.0_vp;
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

void SetHitTestMode(RefPtr<FrameNode>& popupNode, bool isBlockEvent)
{
    auto hub = popupNode->GetEventHub<BubbleEventHub>();
    if (hub) {
        auto ges = hub->GetOrCreateGestureEventHub();
        if (!isBlockEvent) {
            ges->SetHitTestMode(HitTestMode::HTMTRANSPARENT_SELF);
        } else {
            ges->SetHitTestMode(HitTestMode::HTMDEFAULT);
        }
    }
}

RefPtr<FrameNode> BubbleView::CreateBubbleNode(
    const std::string& targetTag, int32_t targetId, const RefPtr<PopupParam>& param)
{
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::POPUP_ETS_TAG, popupId);
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
    if (param->GetArrowHeight().has_value()) {
        popupProp->UpdateArrowHeight(param->GetArrowHeight().value());
    }
    if (param->GetArrowWidth().has_value()) {
        popupProp->UpdateArrowWidth(param->GetArrowWidth().value());
    }
    if (param->GetRadius().has_value()) {
        popupProp->UpdateRadius(param->GetRadius().value());
    }
    SetHitTestMode(popupNode, param->IsBlockEvent());
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
    } else {
        auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(true));
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
        auto scrollNode = FrameNode::CreateFrameNode(
            V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
        CHECK_NULL_RETURN(scrollNode, nullptr);
        auto scrollProps = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
        scrollProps->UpdateAxis(Axis::VERTICAL);
        scrollProps->UpdateAlignment(Alignment::CENTER_LEFT);
        scrollNode->MarkModifyDone();
        textNode->MountToParent(scrollNode);
        scrollNode->MountToParent(columnNode);
        child = columnNode;
    }
    // TODO: GridSystemManager is not completed, need to check later.
    auto childLayoutProperty = child->GetLayoutProperty();
    CHECK_NULL_RETURN(childLayoutProperty, nullptr);
    float popupMaxWidth = 0.0f;
    float popupMaxHeight = 0.0f;
    GetPopupMaxWidthAndHeight(param, popupMaxWidth, popupMaxHeight);
    childLayoutProperty->UpdateCalcMaxSize(
        CalcSize(NG::CalcLength(Dimension(popupMaxWidth)), NG::CalcLength(Dimension(popupMaxHeight))));
    if (param->GetChildWidth().has_value()) {
        childLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(param->GetChildWidth().value()), std::nullopt));
    }
    auto renderContext = child->GetRenderContext();
    if (renderContext) {
        BlurStyleOption styleOption;
        styleOption.blurStyle = BlurStyle::COMPONENT_ULTRA_THICK;
        renderContext->UpdateBackBlurStyle(styleOption);
        auto backgroundColor = popupPaintProp->GetBackgroundColor().value_or(GetPopupTheme()->GetBackgroundColor());
        renderContext->UpdateBackgroundColor(backgroundColor);
        renderContext->UpdateBackShadow(ShadowConfig::DefaultShadowM);
        if (param->GetShadow().has_value()) {
            renderContext->UpdateBackShadow(param->GetShadow().value());
        }
    }
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
    if (param->GetArrowHeight().has_value()) {
        layoutProps->UpdateArrowHeight(param->GetArrowHeight().value());
    }
    if (param->GetArrowWidth().has_value()) {
        layoutProps->UpdateArrowWidth(param->GetArrowWidth().value());
    }
    if (param->GetRadius().has_value()) {
        layoutProps->UpdateRadius(param->GetRadius().value());
    }
    SetHitTestMode(popupNode, param->IsBlockEvent());
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
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    customNode->MountToParent(columnNode);
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_ULTRA_THICK;
    auto columnRenderContext = columnNode->GetRenderContext();
    auto columnLayoutProperty = columnNode->GetLayoutProperty();
    CHECK_NULL_RETURN(columnLayoutProperty, nullptr);
    auto customFrameNode = AceType::DynamicCast<FrameNode>(customNode);
    float popupMaxWidth = 0.0f;
    float popupMaxHeight = 0.0f;
    GetPopupMaxWidthAndHeight(param, popupMaxWidth, popupMaxHeight);
    columnLayoutProperty->UpdateCalcMaxSize(
        CalcSize(NG::CalcLength(Dimension(popupMaxWidth)), NG::CalcLength(Dimension(popupMaxHeight))));
    if (param->GetChildWidth().has_value()) {
        columnLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(param->GetChildWidth().value()), std::nullopt));
    }
    auto backgroundColor = popupPaintProps->GetBackgroundColor().value_or(GetPopupTheme()->GetBackgroundColor());
    RefPtr<RenderContext> customRenderContext;
    if (columnRenderContext) {
        if (customFrameNode) {
            customRenderContext = customFrameNode->GetRenderContext();
        } else {
            columnRenderContext->UpdateBackgroundColor(backgroundColor);
        }
        columnRenderContext->UpdateBackBlurStyle(styleOption);
        columnRenderContext->UpdateBackShadow(ShadowConfig::DefaultShadowM);
        if (param->GetShadow().has_value()) {
            columnRenderContext->UpdateBackShadow(param->GetShadow().value());
        }
    }
    if (customRenderContext) {
        if (customRenderContext->HasBackgroundColor()) {
            columnRenderContext->UpdateBackgroundColor(customRenderContext->GetBackgroundColorValue());
            customRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        } else {
            columnRenderContext->UpdateBackgroundColor(backgroundColor);
        }
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
    if (primaryButton.showButton || secondaryButton.showButton) {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        float popupMaxWidth = 0.0f;
        float popupMaxHeight = 0.0f;
        GetPopupMaxWidthAndHeight(param, popupMaxWidth, popupMaxHeight);
        auto buttonTheme = pipelineContext->GetTheme<ButtonTheme>();
        CHECK_NULL_VOID(buttonTheme);
        auto childNode = AceType::DynamicCast<FrameNode>(popupNode->GetFirstChild());
        CHECK_NULL_VOID(childNode);
        const auto& children = childNode->GetChildren();
        for (const auto& uinode : children) {
            if (uinode->GetTag() == V2::SCROLL_ETS_TAG) {
                auto scrollNode = AceType::DynamicCast<FrameNode>(uinode);
                CHECK_NULL_VOID(scrollNode);
                auto scrollProps = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
                scrollProps->UpdateCalcMaxSize(CalcSize(
                    std::nullopt, CalcLength(Dimension(popupMaxHeight) - buttonTheme->GetHeight() * DOUBLENESS)));
            }
        }
    }
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
    if (param->IsBackgroundColorSetted()) {
        popupPaintProp->UpdateBackgroundColor(param->GetBackgroundColor());
    }
    auto childNode = AceType::DynamicCast<FrameNode>(popupNode->GetFirstChild());
    CHECK_NULL_VOID(childNode);
    auto renderContext = childNode->GetRenderContext();
    if (renderContext) {
        BlurStyleOption styleOption;
        styleOption.blurStyle = BlurStyle::COMPONENT_ULTRA_THICK;
        renderContext->UpdateBackBlurStyle(styleOption);
        auto backgroundColor = popupPaintProp->GetBackgroundColor().value_or(GetPopupTheme()->GetBackgroundColor());
        renderContext->UpdateBackgroundColor(backgroundColor);
    }
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
    popupLayoutProp->UpdateEnableArrow(param->EnableArrow());
    popupPaintProp->UpdateAutoCancel(!param->HasAction());
    popupPaintProp->UpdateEnableArrow(param->EnableArrow());
    auto backgroundColor = popupPaintProp->GetBackgroundColor().value_or(GetPopupTheme()->GetBackgroundColor());
    auto childNode = AceType::DynamicCast<FrameNode>(popupNode->GetFirstChild());
    CHECK_NULL_VOID(childNode);
    auto customFrameNode = AceType::DynamicCast<FrameNode>(childNode->GetFirstChild());
    auto columnRenderContext = childNode->GetRenderContext();
    RefPtr<RenderContext> customRenderContext;
    if (columnRenderContext) {
        BlurStyleOption styleOption;
        styleOption.blurStyle = BlurStyle::COMPONENT_ULTRA_THICK;
        columnRenderContext->UpdateBackBlurStyle(styleOption);
        if (customFrameNode) {
            customRenderContext = customFrameNode->GetRenderContext();
        } else {
            columnRenderContext->UpdateBackgroundColor(backgroundColor);
        }
    }
    if (customRenderContext) {
        if (!customRenderContext->HasBackgroundColor()) {
            columnRenderContext->UpdateBackgroundColor(backgroundColor);
        }
    }
}

void BubbleView::GetPopupMaxWidthAndHeight(const RefPtr<PopupParam>& param, float& popupMaxWidth, float& popupMaxHeight)
{
    auto pipelineContext = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    auto bottom = safeAreaManager->GetSystemSafeArea().bottom_.Length();
    auto top = safeAreaManager->GetSystemSafeArea().top_.Length();
    auto maxHeight = windowGlobalRect.Height();
    auto maxWidth = windowGlobalRect.Width();
    if (param->IsShowInSubWindow()) {
        maxHeight = SystemProperties::GetDeviceHeight();
        maxWidth = SystemProperties::GetDeviceWidth();
    }
    if (maxHeight > BUBBLE_MAX_HEIGHT.ConvertToPx()) {
        popupMaxHeight = BUBBLE_MAX_HEIGHT.ConvertToPx();
    } else {
        popupMaxHeight = maxHeight - OUT_RANGE_SPACE.ConvertToPx() - OUT_RANGE_SPACE.ConvertToPx() - bottom - top;
    }
    if (maxWidth > BUBBLE_MAX_WIDTH.ConvertToPx()) {
        popupMaxWidth = BUBBLE_MAX_WIDTH.ConvertToPx();
    } else {
        popupMaxWidth = maxWidth - OUT_RANGE_SPACE.ConvertToPx() - OUT_RANGE_SPACE.ConvertToPx();
    }
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
    if (param->GetErrorArrowHeight()) {
        popupLayoutProp->ResetArrowHeight();
    }
    if (param->GetErrorArrowWidth()) {
        popupLayoutProp->ResetArrowWidth();
    }
    if (param->GetErrorRadius()) {
        popupLayoutProp->ResetRadius();
    }
    if (param->GetArrowHeight().has_value()) {
        popupLayoutProp->UpdateArrowHeight(param->GetArrowHeight().value());
    }
    if (param->GetArrowWidth().has_value()) {
        popupLayoutProp->UpdateArrowWidth(param->GetArrowWidth().value());
    }
    if (param->GetRadius().has_value()) {
        popupLayoutProp->UpdateRadius(param->GetRadius().value());
    }
    SetHitTestMode(popupNode, param->IsBlockEvent());
    popupLayoutProp->UpdatePositionOffset(OffsetF(param->GetTargetOffset().GetX(), param->GetTargetOffset().GetY()));
    if (param->IsMaskColorSetted()) {
        popupPaintProp->UpdateMaskColor(param->GetMaskColor());
    } else {
        popupPaintProp->UpdateMaskColor(Color::TRANSPARENT);
    }
    if (param->GetTargetSpace().has_value()) {
        popupLayoutProp->UpdateTargetSpace(param->GetTargetSpace().value());
    }
    if (param->IsBackgroundColorSetted()) {
        popupPaintProp->UpdateBackgroundColor(param->GetBackgroundColor());
    }
    auto childNode = AceType::DynamicCast<FrameNode>(popupNode->GetFirstChild());
    CHECK_NULL_VOID(childNode);
    auto renderContext = childNode->GetRenderContext();
    if (renderContext && param->GetShadow().has_value()) {
        renderContext->UpdateBackShadow(param->GetShadow().value());
    }
    auto childLayoutProperty = childNode->GetLayoutProperty();
    CHECK_NULL_VOID(childLayoutProperty);
    float popupMaxWidth = 0.0f;
    float popupMaxHeight = 0.0f;
    GetPopupMaxWidthAndHeight(param, popupMaxWidth, popupMaxHeight);
    childLayoutProperty->UpdateCalcMaxSize(
        CalcSize(NG::CalcLength(Dimension(popupMaxWidth)), NG::CalcLength(Dimension(popupMaxHeight))));
    if (param->GetChildWidth().has_value()) {
        childLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(param->GetChildWidth().value()), std::nullopt));
    }
}

RefPtr<FrameNode> BubbleView::CreateMessage(const std::string& message, bool IsUseCustom)
{
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    // The buttons in popupNode can not get focus, if the textNode in the button is not focusable
    textNode->GetOrCreateFocusHub()->SetFocusable(true);
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
    layoutProps->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
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
    textLayoutProps->UpdateTextColor(popupTheme->GetFontSecondaryColor());
    UpdateTextProperties(param, textLayoutProps);
    message->MarkModifyDone();
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    float popupMaxWidth = 0.0f;
    float popupMaxHeight = 0.0f;
    GetPopupMaxWidthAndHeight(param, popupMaxWidth, popupMaxHeight);
    auto buttonTheme = pipelineContext->GetTheme<ButtonTheme>();
    CHECK_NULL_RETURN(buttonTheme, nullptr);
    auto scrollNode = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    CHECK_NULL_RETURN(scrollNode, nullptr);
    auto scrollProps = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
    scrollProps->UpdateAxis(Axis::VERTICAL);
    scrollProps->UpdateAlignment(Alignment::CENTER_LEFT);
    scrollProps->UpdateCalcMaxSize(
        CalcSize(std::nullopt, CalcLength(Dimension(popupMaxHeight) - buttonTheme->GetHeight() * DOUBLENESS)));
    scrollNode->MarkModifyDone();
    message->MountToParent(scrollNode);
    scrollNode->MountToParent(columnNode);
    auto buttonFlex = BubbleView::CreateButtons(param, popupId, targetId);
    auto buttonFlexLayoutProperty = buttonFlex->GetLayoutProperty<FlexLayoutProperty>();
    buttonFlexLayoutProperty->UpdateAlignSelf(FlexAlign::FLEX_END);
    buttonFlex->MarkModifyDone();
    auto childLayoutProperty = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(childLayoutProperty, nullptr);
    childLayoutProperty->UpdateCalcMaxSize(
        CalcSize(NG::CalcLength(Dimension(popupMaxWidth)), NG::CalcLength(Dimension(popupMaxHeight))));
    buttonFlex->MountToParent(columnNode);
    columnNode->MarkModifyDone();
    return columnNode;
}

RefPtr<FrameNode> BubbleView::CreateButtons(const RefPtr<PopupParam>& param, int32_t popupId, int32_t targetId)
{
    auto rowId = ElementRegister::GetInstance()->MakeUniqueId();
    auto flexNode = FrameNode::CreateFrameNode(V2::FLEX_ETS_TAG, rowId, AceType::MakeRefPtr<FlexLayoutPattern>(false));
    flexNode->GetPattern<FlexLayoutPattern>()->SetIsWrap(true);
    auto layoutProps = flexNode->GetLayoutProperty<FlexLayoutProperty>();
    auto primaryButtonProp = param->GetPrimaryButtonProperties();
    auto primaryButton = BubbleView::CreateButton(primaryButtonProp, popupId, targetId, param);
    if (primaryButton) {
        primaryButton->MountToParent(flexNode);
    }
    auto secondaryButtonProp = param->GetSecondaryButtonProperties();
    auto secondaryButton = BubbleView::CreateButton(secondaryButtonProp, popupId, targetId, param);
    if (secondaryButton) {
        secondaryButton->MountToParent(flexNode);
    }
    auto popupTheme = GetPopupTheme();
    auto littlePadding = popupTheme->GetLittlePadding();
    PaddingProperty rowPadding;
    rowPadding.right = CalcLength(littlePadding);
    rowPadding.bottom = CalcLength(littlePadding);
    layoutProps->UpdatePadding(rowPadding);

    flexNode->MarkModifyDone();
    return flexNode;
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

    auto buttonTextNode = BubbleView::CreateMessage(buttonParam.value, isUseCustom);
    auto textLayoutProperty = buttonTextNode->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateFontSize(popupTheme->GetButtonFontSize());
    textLayoutProperty->UpdateTextColor(popupTheme->GetButtonFontColor());
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

    auto buttonEventHub = buttonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(buttonEventHub, nullptr);
    buttonEventHub->AddClickEvent(buttonParam.action);
    auto popupNode = FrameNode::GetFrameNode(V2::POPUP_ETS_TAG, popupId);
    auto closeCallback = [popupNode, targetId](GestureEvent& /* info */) {
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
        overlayManager->HidePopup(targetId, popupInfo);
    };
    if (buttonParam.action) {
        buttonEventHub->AddClickEvent(buttonParam.action);
    } else {
        buttonEventHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(closeCallback));
    }

    return buttonNode;
}
} // namespace OHOS::Ace::NG
