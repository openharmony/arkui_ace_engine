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
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double DOUBLENESS = 2.0;
constexpr Dimension OUT_RANGE_SPACE = 40.0_vp;
constexpr Dimension MAX_WIDTH = 480.0_vp;
constexpr Dimension MIN_BUTTON_FONT_SIZE = 9.0_vp;
constexpr int32_t BUTTON_MAX_LINE = 2;
constexpr float AGE_FONT_MAX_SIZE_SCALE = 2.0f;
constexpr float AGE_SCALE_NUMBER = 1.0f;
constexpr float AGE_BUTTONS_LAYOUT_HEIGHT_RATE = 15.0f;
const int32_t PRIMARY_BUTTON_NUMBER = 1;
const int32_t SECONDARY_BUTTON_NUMBER = 2;

OffsetF GetDisplayWindowRectOffset(int32_t popupNodeId)
{
    auto popupNode = FrameNode::GetFrameNode(V2::POPUP_ETS_TAG, popupNodeId);
    CHECK_NULL_RETURN(popupNode, OffsetF());
    auto pipelineContext = popupNode->GetContextRefPtr();
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
    auto popupTheme = GetPopupTheme();
    CHECK_NULL_RETURN(popupTheme, maxWidth);
    uint32_t maxColumns = popupTheme->GetMaxColumns();
    if (maxColumns > 0) {
        maxWidth = Dimension(gridColumnInfo->GetWidth(maxColumns));
    }
    return maxWidth;
}

static Dimension GetAgeFontSize(const std::optional<Dimension>& originalFontSize, const RefPtr<FrameNode>& bubbleNode)
{
    auto fontSize = Dimension(originalFontSize->Value(), originalFontSize->Unit());
    CHECK_NULL_RETURN(bubbleNode, fontSize);
    auto pipeline = bubbleNode->GetContext();
    CHECK_NULL_RETURN(pipeline, fontSize);
    auto fontSizeScale = pipeline->GetFontScale();
    auto fontScale = fontSizeScale > AGE_FONT_MAX_SIZE_SCALE ? AGE_FONT_MAX_SIZE_SCALE : fontSizeScale;
    fontSize.SetValue((originalFontSize->Value()) * fontScale);
    return fontSize;
}

void UpdateTextProperties(const RefPtr<PopupParam>& param, const RefPtr<TextLayoutProperty>& textLayoutProps,
    const RefPtr<FrameNode>& popupNode)
{
    auto textColor = param->GetTextColor();
    if (textColor.has_value()) {
        textLayoutProps->UpdateTextColor(textColor.value());
    }
    CHECK_NULL_VOID(popupNode);
    auto pipelineContext = popupNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    double maxAppFontScale = pipelineContext->GetMaxAppFontScale();
    auto fontSize = param->GetFontSize();
    if (fontSize.has_value()) {
        if (!param->IsUseCustom()) {
            textLayoutProps->UpdateMaxFontScale(std::min<double>(AGE_FONT_MAX_SIZE_SCALE, maxAppFontScale));
            textLayoutProps->UpdateFontSize(fontSize.value());
        } else {
            textLayoutProps->UpdateFontSize(fontSize.value());
        }
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
    auto hub = popupNode->GetOrCreateEventHub<BubbleEventHub>();
    if (hub) {
        auto ges = hub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(ges);
        if (!isBlockEvent) {
            ges->SetHitTestMode(HitTestMode::HTMTRANSPARENT_SELF);
        } else {
            ges->SetHitTestMode(HitTestMode::HTMDEFAULT);
        }
    }
}

int32_t GetTextLineHeight(const RefPtr<FrameNode>& textNode)
{
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, 0);
    auto layoutConstraint = textLayoutProperty->GetLayoutConstraint();
    auto textLayoutWrapper = textNode->CreateLayoutWrapper();
    CHECK_NULL_RETURN(textLayoutWrapper, 0);
    textLayoutWrapper->Measure(layoutConstraint);
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(textLayoutWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, 0);
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(textLayoutAlgorithm, 0);
    auto paragraph = textLayoutAlgorithm->GetSingleParagraph();
    CHECK_NULL_RETURN(paragraph, 0);
    auto paragHeight = paragraph->GetHeight();
    auto paragLineCount = paragraph->GetLineCount();
    int32_t paragLineHeight = 0;
    if (paragLineCount > 0) {
        paragLineHeight = static_cast<int32_t>(paragHeight / paragLineCount);
    }
    return paragLineHeight;
}

RefPtr<FrameNode> BubbleView::CreateBubbleNode(const std::string& targetTag, int32_t targetId,
    const RefPtr<PopupParam>& param, const RefPtr<SpanString>& spanString)
{
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::POPUP_ETS_TAG, popupId);
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    auto popupProp = AceType::DynamicCast<BubbleLayoutProperty>(popupNode->GetLayoutProperty());
    auto popupPaintProp = popupNode->GetPaintProperty<BubbleRenderProperty>();
    auto useCustom = param->IsUseCustom();

    // onstateChange.
    auto bubbleHub = popupNode->GetOrCreateEventHub<BubbleEventHub>();
    if (bubbleHub) {
        bubbleHub->SetOnStateChange(param->GetOnStateChange());
    }

    auto message = param->GetMessage();
    auto primaryButton = param->GetPrimaryButtonProperties();
    auto secondaryButton = param->GetSecondaryButtonProperties();
    // Update props
    popupProp->UpdateIsTips(param->IsTips());
    popupProp->UpdateUseCustom(useCustom);
    popupProp->UpdateEnableArrow(param->EnableArrow());
    popupProp->UpdatePlacement(param->GetPlacement());
    popupProp->UpdateShowInSubWindow(param->IsShowInSubWindow());
    popupProp->UpdatePositionOffset(OffsetF(param->GetTargetOffset().GetX(), param->GetTargetOffset().GetY()));
    popupProp->UpdateBlockEvent(param->IsBlockEvent());
    popupProp->UpdateIsCaretMode(param->IsCaretMode());
    popupProp->UpdateShowAtAnchor(param->GetAnchorType());
    if (param->HasEnableHoverMode()) {
        popupProp->UpdateEnableHoverMode(param->EnableHoverMode());
    } else {
        popupProp->ResetEnableHoverMode();
    }

    if (param->GetArrowHeight().has_value()) {
        popupProp->UpdateArrowHeight(param->GetArrowHeight().value());
    }
    if (param->GetArrowWidth().has_value()) {
        popupProp->UpdateArrowWidth(param->GetArrowWidth().value());
    }
    if (param->GetRadius().has_value()) {
        popupProp->UpdateRadius(param->GetRadius().value());
    }
    popupProp->UpdateFollowTransformOfTarget(param->IsFollowTransformOfTarget());
    SetHitTestMode(popupNode, param->IsBlockEvent());
    if (param->GetTargetSpace().has_value()) {
        popupProp->UpdateTargetSpace(param->GetTargetSpace().value());
    }
    auto displayWindowOffset = GetDisplayWindowRectOffset(popupId);
    popupProp->UpdateDisplayWindowOffset(displayWindowOffset);
    popupPaintProp->UpdateEnableArrow(param->EnableArrow());
    popupPaintProp->UpdateIsTips(param->IsTips());
    popupPaintProp->UpdateShowAtAnchor(param->GetAnchorType());
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
    if (param->GetHasTransition()) {
        popupNode->GetRenderContext()->UpdateChainedTransition(param->GetTransitionEffects());
    }

    auto bubbleAccessibilityProperty = popupNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_RETURN(bubbleAccessibilityProperty, nullptr);
    bubbleAccessibilityProperty->SetText(message);
    auto bubblePattern = popupNode->GetPattern<BubblePattern>();
    auto textColor = param->GetTextColor();
    bubblePattern->SetMessageColor(textColor.has_value());
    bubblePattern->SetHasTransition(param->GetHasTransition());
    bubblePattern->SetAvoidKeyboard(param->GetKeyBoardAvoidMode() == PopupKeyboardAvoidMode::DEFAULT);
    bubblePattern->SetAvoidTarget(param->GetAvoidTarget());
    bubblePattern->SetHasWidth(param->GetChildWidth().has_value());
    bubblePattern->SetHasPlacement(param->HasPlacement());
    bubblePattern->SetOutlineLinearGradient(param->GetOutlineLinearGradient());
    bubblePattern->SetOutlineWidth(param->GetOutlineWidth());
    bubblePattern->SetInnerBorderLinearGradient(param->GetInnerBorderLinearGradient());
    bubblePattern->SetInnerBorderWidth(param->GetInnerBorderWidth());
    if (param->IsTips()) {
        bubblePattern->SetTipsTag(true);
    }
    auto popupTheme = GetPopupTheme();
    CHECK_NULL_RETURN(popupTheme, nullptr);
    // Create child
    RefPtr<FrameNode> child;
    int textLineHeight = 0;
    RefPtr<TextLayoutProperty> layoutProps;
    if (primaryButton.showButton || secondaryButton.showButton) {
        auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(true));
        auto columnLayoutProperty = columnNode->GetLayoutProperty<LinearLayoutProperty>();
        columnLayoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER); // mainAxisAlign
        columnLayoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
        auto combinedChild = CreateCombinedChild(param, popupId, targetId, popupNode);
        popupPaintProp->UpdatePrimaryButtonShow(primaryButton.showButton);
        popupPaintProp->UpdateSecondaryButtonShow(secondaryButton.showButton);
        if ((Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN))) {
            popupPaintProp->UpdateAutoCancel(false);
        }
        combinedChild->MountToParent(columnNode);
        child = columnNode;
    } else {
        auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(true));
        auto columnLayoutProperty = columnNode->GetLayoutProperty<LinearLayoutProperty>();
        columnLayoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER); // mainAxisAlign
        columnLayoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
        auto textNode = CreateMessage(message, useCustom);
        bubblePattern->SetMessageNode(textNode);
        auto popupTheme = GetPopupTheme();
        auto padding = param->IsTips() ? popupTheme->GetTipsPadding() : popupTheme->GetPadding();
        layoutProps = textNode->GetLayoutProperty<TextLayoutProperty>();
        PaddingProperty textPadding;
        textPadding.left = CalcLength(padding.Left());
        textPadding.right = CalcLength(padding.Right());
        textPadding.top = CalcLength(padding.Top());
        textPadding.bottom = CalcLength(padding.Bottom());
        bubblePattern->SetTextPadding(textPadding);
        layoutProps->UpdatePadding(textPadding);
        layoutProps->UpdateAlignment(Alignment::CENTER);
        UpdateTextProperties(param, layoutProps, columnNode);
        if (!param->IsTips()) {
            auto buttonMiniMumHeight = popupTheme->GetBubbleMiniMumHeight().ConvertToPx();
            layoutProps->UpdateCalcMinSize(CalcSize(std::nullopt, CalcLength(buttonMiniMumHeight)));
        }
        textNode->MarkModifyDone();
        if ((Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN))) {
            textNode->MountToParent(columnNode);
        } else if (param->IsTips()) {
            textNode->MountToParent(columnNode);
            textLineHeight = GetTextLineHeight(textNode);
        } else {
            auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
            CHECK_NULL_RETURN(scrollNode, nullptr);
            auto scrollProps = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
            scrollProps->UpdateAxis(Axis::VERTICAL);
            scrollProps->UpdateAlignment(Alignment::CENTER_LEFT);
            scrollNode->MarkModifyDone();
            textNode->MountToParent(scrollNode);
            scrollNode->MountToParent(columnNode);
        }
        child = columnNode;
    }
    // GridSystemManager is not completed, need to check later.
    auto childLayoutProperty = child->GetLayoutProperty();
    CHECK_NULL_RETURN(childLayoutProperty, nullptr);
    float popupMaxWidth = 0.0f;
    float popupMaxHeight = 0.0f;
    GetPopupMaxWidthAndHeight(param, popupMaxWidth, popupMaxHeight, popupId);
    if (param->IsTips()) {
        layoutProps->UpdateTextOverflow(TextOverflow::ELLIPSIS);
        if (textLineHeight > 0) {
            auto maxLines = static_cast<int32_t>(std::floor(popupMaxHeight / textLineHeight)) - 1;
            layoutProps->UpdateMaxLines(maxLines);
        }
    }
    if (GreatNotEqual(popupMaxWidth, 0.0f) && GreatNotEqual(popupMaxHeight, 0.0f)) {
        childLayoutProperty->UpdateCalcMaxSize(
            CalcSize(NG::CalcLength(Dimension(popupMaxWidth)), NG::CalcLength(Dimension(popupMaxHeight))));
    }
    if (param->GetChildWidth().has_value()) {
        childLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(param->GetChildWidth().value()), std::nullopt));
    }
    auto renderContext = child->GetRenderContext();
    if (renderContext) {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) &&
            IsSupportBlurStyle(renderContext, param->IsShowInSubWindow(), param->IsTips())) {
            auto backgroundColor = popupPaintProp->GetBackgroundColor().value_or(popupTheme->GetDefaultBGColor());
            renderContext->UpdateBackgroundColor(backgroundColor);
            BlurStyleOption styleOption;
            if (param->IsTips()) {
                styleOption.blurStyle = BlurStyle::COMPONENT_REGULAR;
            } else {
                styleOption.blurStyle = param->GetBlurStyle();
            }
            styleOption.colorMode = static_cast<ThemeColorMode>(popupTheme->GetBgThemeColorMode());
            renderContext->UpdateBackBlurStyle(styleOption);
        } else {
            renderContext->UpdateBackgroundColor(
                popupPaintProp->GetBackgroundColor().value_or(popupTheme->GetBackgroundColor()));
        }
        if (param->GetShadow().has_value()) {
            renderContext->UpdateBackShadow(param->GetShadow().value());
        }
        if (param->IsTips()) {
            do {
                auto pipelineContext = popupNode->GetContextRefPtr();
                CHECK_NULL_BREAK(pipelineContext);
                auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
                CHECK_NULL_BREAK(shadowTheme);
                Shadow shadow = shadowTheme->GetShadow(ShadowStyle::OuterDefaultSM, Container::CurrentColorMode());
                renderContext->UpdateBackShadow(shadow);
            } while (false);
        }
    }
    if (spanString) {
        auto messageNode = bubblePattern->GetMessageNode();
        if (messageNode) {
            auto textPattern = messageNode->GetPattern<TextPattern>();
            textPattern->SetStyledString(spanString, false);
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
    auto bubbleHub = popupNode->GetOrCreateEventHub<BubbleEventHub>();
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
    if (param->HasEnableHoverMode()) {
        layoutProps->UpdateEnableHoverMode(param->EnableHoverMode());
    } else {
        layoutProps->ResetEnableHoverMode();
    }
    
    if (param->GetArrowHeight().has_value()) {
        layoutProps->UpdateArrowHeight(param->GetArrowHeight().value());
    }
    if (param->GetArrowWidth().has_value()) {
        layoutProps->UpdateArrowWidth(param->GetArrowWidth().value());
    }
    if (param->GetRadius().has_value()) {
        layoutProps->UpdateRadius(param->GetRadius().value());
    }
    layoutProps->UpdateFollowTransformOfTarget(param->IsFollowTransformOfTarget());
    SetHitTestMode(popupNode, param->IsBlockEvent());
    auto displayWindowOffset = GetDisplayWindowRectOffset(popupId);
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
    if (param->GetHasTransition()) {
        popupNode->GetRenderContext()->UpdateChainedTransition(param->GetTransitionEffects());
    }
    popupPattern->SetHasTransition(param->GetHasTransition());
    popupPattern->SetAvoidKeyboard(param->GetKeyBoardAvoidMode() == PopupKeyboardAvoidMode::DEFAULT);
    popupPattern->SetAvoidTarget(param->GetAvoidTarget());
    popupPattern->SetHasWidth(param->GetChildWidth().has_value());
    popupPattern->SetHasPlacement(param->HasPlacement());
    popupPattern->SetOutlineLinearGradient(param->GetOutlineLinearGradient());
    popupPattern->SetOutlineWidth(param->GetOutlineWidth());
    popupPattern->SetInnerBorderLinearGradient(param->GetInnerBorderLinearGradient());
    popupPattern->SetInnerBorderWidth(param->GetInnerBorderWidth());

    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto columnNodeClip = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto clipContext = columnNodeClip->GetRenderContext();
    clipContext->SetClipToBounds(true);
    customNode->MountToParent(columnNodeClip);
    columnNodeClip->MountToParent(columnNode);
    auto columnRenderContext = columnNode->GetRenderContext();
    auto columnLayoutProperty = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(columnLayoutProperty, nullptr);
    columnLayoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER); // mainAxisAlign
    columnLayoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    auto customFrameNode = AceType::DynamicCast<FrameNode>(customNode);
    float popupMaxWidth = 0.0f;
    float popupMaxHeight = 0.0f;
    GetPopupMaxWidthAndHeight(param, popupMaxWidth, popupMaxHeight, popupId);
    columnLayoutProperty->UpdateCalcMaxSize(CalcSize(std::nullopt, NG::CalcLength(Dimension(popupMaxHeight))));
    if (param->GetChildWidth().has_value()) {
        columnLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(param->GetChildWidth().value()), std::nullopt));
    }
    if (columnRenderContext) {
        auto popupTheme = GetPopupTheme();
        CHECK_NULL_RETURN(popupTheme, nullptr);
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) &&
            IsSupportBlurStyle(columnRenderContext, param->IsShowInSubWindow(), param->IsTips())) {
            auto backgroundColor = popupPaintProps->GetBackgroundColor().value_or(popupTheme->GetDefaultBGColor());
            columnRenderContext->UpdateBackgroundColor(backgroundColor);
            BlurStyleOption styleOption;
            styleOption.blurStyle = param->GetBlurStyle();
            styleOption.colorMode = static_cast<ThemeColorMode>(popupTheme->GetBgThemeColorMode());
            columnRenderContext->UpdateBackBlurStyle(styleOption);
        } else {
            columnRenderContext->UpdateBackgroundColor(
                popupPaintProps->GetBackgroundColor().value_or(popupTheme->GetBackgroundColor()));
        }
        if (param->GetShadow().has_value()) {
            columnRenderContext->UpdateBackShadow(param->GetShadow().value());
        }
    }
    popupPaintProps->UpdateAutoCancel(!param->HasAction());
    popupPaintProps->UpdatePlacement(param->GetPlacement());
    columnNode->MountToParent(popupNode);
    return popupNode;
}

void BubbleView::UpdateBubbleButtons(std::list<RefPtr<UINode>>& buttons, const RefPtr<PopupParam>& param)
{
    auto primaryButton = param->GetPrimaryButtonProperties();
    auto secondaryButton = param->GetSecondaryButtonProperties();
    if (primaryButton.showButton) {
        auto button = AceType::DynamicCast<FrameNode>(buttons.front());
        buttons.pop_front();
        auto textNode = AceType::DynamicCast<FrameNode>(button->GetFirstChild());
        CHECK_NULL_VOID(textNode);
        auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateContent(primaryButton.value);
        textNode->MarkModifyDone();
        auto buttonEventHub = button->GetOrCreateGestureEventHub();
        if (primaryButton.action) {
            buttonEventHub->AddClickEvent(primaryButton.action);
        }
    }
    if (secondaryButton.showButton) {
        auto button = AceType::DynamicCast<FrameNode>(buttons.front());
        buttons.pop_front();
        auto textNode = AceType::DynamicCast<FrameNode>(button->GetFirstChild());
        CHECK_NULL_VOID(textNode);
        auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateContent(secondaryButton.value);
        textNode->MarkModifyDone();
        auto buttonEventHub = button->GetOrCreateGestureEventHub();
        if (secondaryButton.action) {
            buttonEventHub->AddClickEvent(secondaryButton.action);
        }
    }
}

void BubbleView::UpdateBubbleContent(int32_t popupId, const RefPtr<PopupParam>& param)
{
    auto popupNode = FrameNode::GetFrameNode(V2::POPUP_ETS_TAG, popupId);
    CHECK_NULL_VOID(popupNode);
    auto message = param->GetMessage();
    auto primaryButton = param->GetPrimaryButtonProperties();
    auto secondaryButton = param->GetSecondaryButtonProperties();
    auto columnNode = popupNode->GetFirstChild();
    if (primaryButton.showButton || secondaryButton.showButton) {
        CHECK_NULL_VOID(columnNode);
        auto combinedChild = columnNode->GetFirstChild();
        CHECK_NULL_VOID(combinedChild);
        const auto& children = combinedChild->GetChildren();
        for (const auto& child : children) {
            if (child->GetTag() == V2::TEXT_ETS_TAG) { // API10
                auto textNode = AceType::DynamicCast<FrameNode>(child);
                auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
                CHECK_NULL_VOID(layoutProperty);
                layoutProperty->UpdateContent(message);
                UpdateTextProperties(param, layoutProperty, popupNode);
                textNode->MarkModifyDone();
            } else if (child->GetTag() == V2::SCROLL_ETS_TAG) {
                auto textNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
                CHECK_NULL_VOID(textNode);
                auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
                CHECK_NULL_VOID(layoutProperty);
                layoutProperty->UpdateContent(message);
                UpdateTextProperties(param, layoutProperty, popupNode);
                textNode->MarkModifyDone();
            } else {
                auto buttons = child->GetChildren();
                UpdateBubbleButtons(buttons, param);
            }
        }
    } else {
        CHECK_NULL_VOID(columnNode);
        auto childNode = columnNode->GetFirstChild();
        if (!(Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN))) {
            childNode = childNode->GetFirstChild();
        }
        auto textNode = AceType::DynamicCast<FrameNode>(childNode);
        CHECK_NULL_VOID(textNode);
        auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateContent(message);
        UpdateTextProperties(param, layoutProperty, popupNode);
        textNode->MarkModifyDone();
    }
}

void BubbleView::UpdatePopupParam(int32_t popupId, const RefPtr<PopupParam>& param, const RefPtr<FrameNode>& targetNode)
{
    UpdateCommonParam(popupId, param, false);
    UpdateBubbleContent(popupId, param);
    auto popupNode = FrameNode::GetFrameNode(V2::POPUP_ETS_TAG, popupId);
    CHECK_NULL_VOID(popupNode);
    auto popupProp = AceType::DynamicCast<BubbleLayoutProperty>(popupNode->GetLayoutProperty());
    auto popupPaintProp = popupNode->GetPaintProperty<BubbleRenderProperty>();
    auto message = param->GetMessage();
    auto primaryButton = param->GetPrimaryButtonProperties();
    auto secondaryButton = param->GetSecondaryButtonProperties();
    if (!(Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN))) {
        if (primaryButton.showButton || secondaryButton.showButton) {
            auto pipelineContext = popupNode->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            float popupMaxWidth = 0.0f;
            float popupMaxHeight = 0.0f;
            GetPopupMaxWidthAndHeight(param, popupMaxWidth, popupMaxHeight, popupId);
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
    }
    // Update layout props
    popupProp->UpdateUseCustom(param->IsUseCustom());
    popupProp->UpdateIsTips(param->IsTips());
    popupProp->UpdateEnableArrow(param->EnableArrow());
    popupProp->UpdatePlacement(param->GetPlacement());
    auto displayWindowOffset = GetDisplayWindowRectOffset(popupId);
    popupProp->UpdateDisplayWindowOffset(displayWindowOffset);
    // Update paint props
    popupPaintProp->UpdatePlacement(param->GetPlacement());
    popupPaintProp->UpdateUseCustom(param->IsUseCustom());
    popupPaintProp->UpdateIsTips(param->IsTips());
    popupPaintProp->UpdateEnableArrow(param->EnableArrow());
    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    popupPattern->SetOutlineLinearGradient(param->GetOutlineLinearGradient());
    popupPattern->SetOutlineWidth(param->GetOutlineWidth());
    popupPattern->SetInnerBorderLinearGradient(param->GetInnerBorderLinearGradient());
    popupPattern->SetInnerBorderWidth(param->GetInnerBorderWidth());
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
    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    popupPattern->SetOutlineLinearGradient(param->GetOutlineLinearGradient());
    popupPattern->SetOutlineWidth(param->GetOutlineWidth());
    popupPattern->SetInnerBorderLinearGradient(param->GetInnerBorderLinearGradient());
    popupPattern->SetInnerBorderWidth(param->GetInnerBorderWidth());
}

void BubbleView::GetPopupMaxWidthAndHeight(
    const RefPtr<PopupParam>& param, float& popupMaxWidth, float& popupMaxHeight, int32_t popupNodeId)
{
    auto popupNode = FrameNode::GetFrameNode(V2::POPUP_ETS_TAG, popupNodeId);
    CHECK_NULL_VOID(popupNode);
    auto pipelineContext = popupNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "popup GetDisplayWindowRectInfo: %{public}s", windowGlobalRect.ToString().c_str());
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    auto bottom = safeAreaManager->GetSystemSafeArea().bottom_.Length();
    auto top = safeAreaManager->GetSystemSafeArea().top_.Length();
    auto maxHeight = windowGlobalRect.Height();
    auto theme = pipelineContext->GetTheme<PopupTheme>();
    CHECK_NULL_VOID(theme);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto isFreeMultiWindow = container->IsFreeMultiWindow();
    bool isExpandDisplay;
    if (param->IsTips()) {
        isExpandDisplay = theme->GetTipsDoubleBorderEnable() || isFreeMultiWindow;
    } else {
        isExpandDisplay = theme->GetPopupDoubleBorderEnable() || isFreeMultiWindow;
    }
    if (param->IsShowInSubWindow()) {
        if (isExpandDisplay) {
            maxHeight = SystemProperties::GetDeviceHeight();
        } else if (container->IsUIExtensionWindow()) {
            auto rect = container->GetUIExtensionHostWindowRect();
            TAG_LOGI(AceLogTag::ACE_OVERLAY, "popup GetUIExtensionHostWindowRect: %{public}s",
                rect.ToString().c_str());
            maxHeight = rect.Height();
        }
    }
    popupMaxHeight = maxHeight - OUT_RANGE_SPACE.ConvertToPx() - OUT_RANGE_SPACE.ConvertToPx() - bottom - top;
    popupMaxWidth = GetMaxWith().Value();
    if (param->IsTips()) {
        popupMaxWidth = (popupMaxWidth > MAX_WIDTH.ConvertToPx()) ? MAX_WIDTH.ConvertToPx() : popupMaxWidth;
        popupMaxHeight = maxHeight - bottom - top;
    }
}

void BubbleView::UpdateCommonParam(int32_t popupId, const RefPtr<PopupParam>& param, bool custom)
{
    auto popupNode = FrameNode::GetFrameNode(V2::POPUP_ETS_TAG, popupId);
    CHECK_NULL_VOID(popupNode);
    auto bubbleHub = popupNode->GetOrCreateEventHub<BubbleEventHub>();
    if (bubbleHub && (!(param->GetIsPartialUpdate().has_value()))) {
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
    popupLayoutProp->UpdateIsCaretMode(param->IsCaretMode());
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
    popupLayoutProp->UpdateFollowTransformOfTarget(param->IsFollowTransformOfTarget());
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
    GetPopupMaxWidthAndHeight(param, popupMaxWidth, popupMaxHeight, popupId);
    if (custom) {
        childLayoutProperty->UpdateCalcMaxSize(CalcSize(std::nullopt, NG::CalcLength(Dimension(popupMaxHeight))));
    } else if (GreatNotEqual(popupMaxWidth, 0.0f) && GreatNotEqual(popupMaxHeight, 0.0f)) {
        childLayoutProperty->UpdateCalcMaxSize(
            CalcSize(NG::CalcLength(Dimension(popupMaxWidth)), NG::CalcLength(Dimension(popupMaxHeight))));
    }
    if (param->GetChildWidth().has_value()) {
        childLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(param->GetChildWidth().value()), std::nullopt));
    } else {
        childLayoutProperty->ClearUserDefinedIdealSize(true, false);
    }
    if (renderContext) {
        auto popupTheme = GetPopupTheme();
        CHECK_NULL_VOID(popupTheme);
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) &&
            IsSupportBlurStyle(renderContext, param->IsShowInSubWindow(), param->IsTips())) {
            auto defaultBGcolor = popupTheme->GetDefaultBGColor();
            auto backgroundColor = popupPaintProp->GetBackgroundColor().value_or(defaultBGcolor);
            renderContext->UpdateBackgroundColor(backgroundColor);
            BlurStyleOption styleOption;
            if (param->IsTips()) {
                styleOption.blurStyle = BlurStyle::COMPONENT_REGULAR;
            } else {
                styleOption.blurStyle = param->GetBlurStyle();
            }
            styleOption.colorMode = static_cast<ThemeColorMode>(popupTheme->GetBgThemeColorMode());
            renderContext->UpdateBackBlurStyle(styleOption);
        } else {
            renderContext->UpdateBackgroundColor(
                popupPaintProp->GetBackgroundColor().value_or(popupTheme->GetBackgroundColor()));
        }
        if (param->IsTips()) {
            do {
                auto pipelineContext = popupNode->GetContextRefPtr();
                CHECK_NULL_BREAK(pipelineContext);
                auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
                CHECK_NULL_BREAK(shadowTheme);
                Shadow shadow = shadowTheme->GetShadow(ShadowStyle::OuterDefaultSM, Container::CurrentColorMode());
                renderContext->UpdateBackShadow(shadow);
            } while (false);
        }
    }
    RefPtr<BubblePattern> bubblePattern = popupNode->GetPattern<BubblePattern>();
    bubblePattern->SetAvoidKeyboard(param->GetKeyBoardAvoidMode() == PopupKeyboardAvoidMode::DEFAULT);
    bubblePattern->SetAvoidTarget(param->GetAvoidTarget());
    bubblePattern->SetHasWidth(param->GetChildWidth().has_value());
    bubblePattern->SetHasPlacement(param->HasPlacement());

    if (!(param->GetIsPartialUpdate().has_value())) {
        bubblePattern->SetHasTransition(param->GetHasTransition());
        if (param->GetHasTransition()) {
            popupNode->GetRenderContext()->UpdateChainedTransition(param->GetTransitionEffects());
        }
    }
}

void BubbleView::ResetBubbleProperty(int32_t popupId)
{
    auto popupNode = FrameNode::GetFrameNode(V2::POPUP_ETS_TAG, popupId);
    CHECK_NULL_VOID(popupNode);
    auto popupLayoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    CHECK_NULL_VOID(popupLayoutProp);
    popupLayoutProp->ResetEnableArrow();
    popupLayoutProp->ResetPlacement();
    popupLayoutProp->ResetTargetSpace();
    popupLayoutProp->ResetPositionOffset();
    popupLayoutProp->ResetArrowHeight();
    popupLayoutProp->ResetArrowWidth();
    popupLayoutProp->ResetRadius();
    popupLayoutProp->ResetFollowTransformOfTarget();

    auto popupPaintProp = popupNode->GetPaintProperty<BubbleRenderProperty>();
    CHECK_NULL_VOID(popupPaintProp);
    popupPaintProp->ResetAutoCancel();
    popupPaintProp->ResetBackgroundColor();
    popupPaintProp->ResetEnableArrow();
    popupPaintProp->ResetMaskColor();
    popupPaintProp->ResetPlacement();
    popupPaintProp->ResetArrowOffset();

    auto childNode = AceType::DynamicCast<FrameNode>(popupNode->GetFirstChild());
    CHECK_NULL_VOID(childNode);
    auto renderContext = childNode->GetRenderContext();
    if (renderContext) {
        renderContext->ResetBackShadow();
    }
    auto childLayoutProperty = childNode->GetLayoutProperty();
    CHECK_NULL_VOID(childLayoutProperty);
    childLayoutProperty->ClearUserDefinedIdealSize(true, false);
}

RefPtr<FrameNode> BubbleView::CreateMessage(const std::string& message, bool IsUseCustom)
{
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    // The buttons in popupNode can not get focus, if the textNode in the button is not focusable
    textNode->GetOrCreateFocusHub()->SetFocusable(true);
    auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    layoutProperty->UpdateContent(message);
    auto popupTheme = GetPopupTheme();
    CHECK_NULL_RETURN(popupTheme, nullptr);
    if (!IsUseCustom) {
        auto pipelineContext = textNode->GetContextRefPtr();
        CHECK_NULL_RETURN(pipelineContext, nullptr);
        double maxAppFontScale = pipelineContext->GetMaxAppFontScale();
        layoutProperty->UpdateMaxFontScale(std::min<double>(AGE_FONT_MAX_SIZE_SCALE, maxAppFontScale));
        layoutProperty->UpdateFontSize(popupTheme->GetFontSize());
    } else {
        layoutProperty->UpdateFontSize(popupTheme->GetFontSize());
    }
    if (IsUseCustom) {
        layoutProperty->UpdateTextColor(Color::BLACK);
    } else {
        if ((Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN))) {
            layoutProperty->UpdateTextColor(popupTheme->GetFontColor());
        } else {
            layoutProperty->UpdateTextColor(popupTheme->GetFontPrimaryColor());
        }
    }
    textNode->MarkModifyDone();
    return textNode;
}

RefPtr<FrameNode> BubbleView::CreateCombinedChild(
    const RefPtr<PopupParam>& param, int32_t popupId, int32_t targetId, const RefPtr<FrameNode>& bubbleNode)
{
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto layoutProps = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    layoutProps->UpdateMainAxisAlign(FlexAlign::FLEX_START); // mainAxisAlign
    layoutProps->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    auto message = BubbleView::CreateMessage(param->GetMessage(), param->IsUseCustom());
    CHECK_NULL_RETURN(bubbleNode, nullptr);
    auto bubblePattern = bubbleNode->GetPattern<BubblePattern>();
    CHECK_NULL_RETURN(bubblePattern, nullptr);
    bubblePattern->SetMessageNode(message);
    auto popupTheme = GetPopupTheme();
    CHECK_NULL_RETURN(popupTheme, nullptr);
    auto padding = popupTheme->GetPadding();
    auto textLayoutProps = message->GetLayoutProperty<TextLayoutProperty>();
    PaddingProperty textPadding;
    textPadding.left = CalcLength(padding.Left());
    textPadding.right = CalcLength(padding.Right());
    textPadding.top = CalcLength(padding.Top());
    if (!param->IsUseCustom()) {
        textPadding.left = CalcLength(popupTheme->GetAgingTextLeftPadding());
        textPadding.right = CalcLength(popupTheme->GetAgingTextRightPadding());
    }
    bubblePattern->SetTextPadding(textPadding);
    textLayoutProps->UpdatePadding(textPadding);
    textLayoutProps->UpdateAlignSelf(FlexAlign::FLEX_START);
    UpdateTextProperties(param, textLayoutProps, columnNode);
    message->MarkModifyDone();
    auto pipelineContext = bubbleNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    float popupMaxWidth = 0.0f;
    float popupMaxHeight = 0.0f;
    if ((Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN))) {
        message->MountToParent(columnNode);
    } else {
        GetPopupMaxWidthAndHeight(param, popupMaxWidth, popupMaxHeight, popupId);
        auto buttonTheme = pipelineContext->GetTheme<ButtonTheme>();
        CHECK_NULL_RETURN(buttonTheme, nullptr);
        auto scrollNode = FrameNode::CreateFrameNode(
            V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
        CHECK_NULL_RETURN(scrollNode, nullptr);
        auto scrollProps = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
        scrollProps->UpdateAxis(Axis::VERTICAL);
        scrollProps->UpdateAlignment(Alignment::CENTER_LEFT);
        auto buttonFontSize = popupTheme->GetButtonFontSize();
        auto fontScale = pipelineContext->GetFontScale();
        if (fontScale == AGE_SCALE_NUMBER) {
            scrollProps->UpdateCalcMaxSize(CalcSize(
                std::nullopt, CalcLength(Dimension(popupMaxHeight) - GetAgeFontSize(buttonFontSize, bubbleNode) *
                                                                         AGE_BUTTONS_LAYOUT_HEIGHT_RATE * DOUBLENESS)));
        } else {
            scrollProps->UpdateCalcMaxSize(
                CalcSize(std::nullopt, CalcLength(Dimension(popupMaxHeight) -
                                         GetAgeFontSize(buttonFontSize, bubbleNode) * AGE_BUTTONS_LAYOUT_HEIGHT_RATE)));
        }
        scrollNode->MarkModifyDone();
        message->MountToParent(scrollNode);
        scrollNode->MountToParent(columnNode);
    }
    auto buttonLayout = BubbleView::CreateButtons(param, popupId, targetId);
    if ((Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN))) {
        auto buttonRowLayoutProperty = buttonLayout->GetLayoutProperty<LinearLayoutProperty>();
        buttonRowLayoutProperty->UpdateAlignSelf(FlexAlign::FLEX_END);
    } else {
        auto buttonFlexLayoutProperty = buttonLayout->GetLayoutProperty<FlexLayoutProperty>();
        buttonFlexLayoutProperty->UpdateAlignSelf(FlexAlign::FLEX_END);
    }
    buttonLayout->MarkModifyDone();
    auto childLayoutProperty = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(childLayoutProperty, nullptr);
    if ((Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN))) {
        popupMaxWidth = GetMaxWith().Value();
        childLayoutProperty->UpdateCalcMaxSize(CalcSize(NG::CalcLength(popupMaxWidth), std::nullopt));
    } else if (GreatNotEqual(popupMaxWidth, 0.0f) && GreatNotEqual(popupMaxHeight, 0.0f)) {
        childLayoutProperty->UpdateCalcMaxSize(
            CalcSize(NG::CalcLength(Dimension(popupMaxWidth)), NG::CalcLength(Dimension(popupMaxHeight))));
    }
    buttonLayout->MountToParent(columnNode);
    columnNode->MarkModifyDone();
    return columnNode;
}

RefPtr<FrameNode> BubbleView::CreateButtons(const RefPtr<PopupParam>& param, int32_t popupId, int32_t targetId)
{
    auto rowId = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> layoutNode;
    if ((Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN))) {
        layoutNode =
            FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, rowId, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    } else {
        layoutNode = FrameNode::CreateFrameNode(V2::FLEX_ETS_TAG, rowId, AceType::MakeRefPtr<FlexLayoutPattern>(false));
        layoutNode->GetPattern<FlexLayoutPattern>()->SetIsWrap(true);
    }

    auto primaryButtonProp = param->GetPrimaryButtonProperties();
    auto primaryButton = BubbleView::CreateButton(primaryButtonProp, popupId, targetId, param, PRIMARY_BUTTON_NUMBER);
    if (primaryButton) {
        primaryButton->MountToParent(layoutNode);
    }
    auto secondaryButtonProp = param->GetSecondaryButtonProperties();
    auto secondaryButton = BubbleView::CreateButton(secondaryButtonProp, popupId,
        targetId, param, SECONDARY_BUTTON_NUMBER);
    if (secondaryButton) {
        secondaryButton->MountToParent(layoutNode);
    }
    auto popupTheme = GetPopupTheme();
    CHECK_NULL_RETURN(popupTheme, nullptr);
    auto littlePadding = popupTheme->GetLittlePadding();
    PaddingProperty rowPadding;
    rowPadding.top = CalcLength(popupTheme->GetButtonTopMargin());
    rowPadding.left = CalcLength(popupTheme->GetButtonLeftMargin());
    rowPadding.right = CalcLength(littlePadding);
    rowPadding.bottom = CalcLength(popupTheme->GetButtonBottomMargin());
    if ((Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN))) {
        auto layoutProps = layoutNode->GetLayoutProperty<LinearLayoutProperty>();
        layoutProps->UpdateSpace(GetPopupTheme()->GetButtonSpacing());
        layoutProps->UpdatePadding(rowPadding);
    } else {
        auto layoutProps = layoutNode->GetLayoutProperty<FlexLayoutProperty>();
        layoutProps->UpdateSpace(GetPopupTheme()->GetButtonSpacingNewVersion());
        layoutProps->UpdatePadding(rowPadding);
    }
    layoutNode->MarkModifyDone();
    return layoutNode;
}

void UpdateButtonFontSize(RefPtr<TextLayoutProperty>& textLayoutProps,
    const RefPtr<FrameNode>& buttonTextNode)
{
    CHECK_NULL_VOID(textLayoutProps);
    auto host = textLayoutProps->GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto popupTheme = GetPopupTheme();
    CHECK_NULL_VOID(popupTheme);
    auto fontSize = popupTheme->GetButtonFontSize();
    auto fontSizeScale = pipeline->GetFontScale();
    auto fontScale = fontSizeScale > AGE_FONT_MAX_SIZE_SCALE ? AGE_FONT_MAX_SIZE_SCALE : fontSizeScale;
    if (fontScale == AGE_SCALE_NUMBER) {
        textLayoutProps->UpdateAdaptMaxFontSize(popupTheme->GetButtonFontSize());
        textLayoutProps->UpdateAdaptMinFontSize(MIN_BUTTON_FONT_SIZE);
    } else {
        CHECK_NULL_VOID(buttonTextNode);
        auto pipelineContext = buttonTextNode->GetContextRefPtr();
        CHECK_NULL_VOID(pipelineContext);
        double maxAppFontScale = pipelineContext->GetMaxAppFontScale();
        textLayoutProps->UpdateMaxFontScale(std::min<double>(AGE_FONT_MAX_SIZE_SCALE, maxAppFontScale));
    }
    textLayoutProps->UpdateFontSize(fontSize);
}

void UpdateButtonTextColorForDiff(const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const int32_t buttonNumber)
{
    auto popupTheme = GetPopupTheme();
    CHECK_NULL_VOID(popupTheme);
    if (buttonNumber == PRIMARY_BUTTON_NUMBER) {
        textLayoutProperty->UpdateTextColor(popupTheme->GetPrimaryButtonFontColor());
    } else if (buttonNumber == SECONDARY_BUTTON_NUMBER) {
        textLayoutProperty->UpdateTextColor(popupTheme->GetSecondaryButtonFontColor());
    } else {
        textLayoutProperty->UpdateTextColor(popupTheme->GetButtonFontColor());
    }
}

RefPtr<FrameNode> BubbleView::CreateButton(ButtonProperties& buttonParam, int32_t popupId,
    int32_t targetId, const RefPtr<PopupParam>& param, const int32_t buttonNumber)
{
    if (!buttonParam.showButton) {
        return nullptr;
    }
    auto popupNode = FrameNode::GetFrameNode(V2::POPUP_ETS_TAG, popupId);
    CHECK_NULL_RETURN(popupNode, nullptr);
    auto pipelineContext = popupNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto buttonTheme = pipelineContext->GetTheme<ButtonTheme>();
    CHECK_NULL_RETURN(buttonTheme, nullptr);
    auto popupTheme = GetPopupTheme();
    CHECK_NULL_RETURN(popupTheme, nullptr);
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
    UpdateButtonFontSize(textLayoutProperty, buttonTextNode);
    textLayoutProperty->UpdateMaxLines(BUTTON_MAX_LINE);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    auto buttonTextFontWeight = static_cast<FontWeight>(popupTheme->GetButtonTextFontWeight());
    textLayoutProperty->UpdateFontWeight(buttonTextFontWeight);
    PaddingProperty buttonTextPadding;
    buttonTextPadding.left = CalcLength(popupTheme->GetAgingButtonTextLeftPadding());
    buttonTextPadding.right = CalcLength(popupTheme->GetAgingButtonTextRightPadding());
    textLayoutProperty->UpdatePadding(buttonTextPadding);
    if (!(Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN))) {
        if (!popupTheme->GetPopupDoubleButtonIsSameStyle()) {
            UpdateButtonTextColorForDiff(textLayoutProperty, buttonNumber);
        } else {
            textLayoutProperty->UpdateTextColor(popupTheme->GetButtonFontColor());
        }
    }
    auto buttonTextInsideMargin = popupTheme->GetButtonTextInsideMargin();
    buttonTextNode->MountToParent(buttonNode);

    PaddingProperty buttonPadding;
    auto padding = buttonTheme->GetPadding();
    buttonPadding.left = CalcLength(buttonTextInsideMargin);
    buttonPadding.right = CalcLength(buttonTextInsideMargin);
    if (!param->IsUseCustom()) {
        buttonPadding.left = CalcLength(popupTheme->GetAgingButtonLeftPadding());
        buttonPadding.right = CalcLength(popupTheme->GetAgingButtonRightPadding());
        buttonProp->UpdatePadding(buttonPadding);
    } else {
        buttonProp->UpdatePadding(buttonPadding);
    }
    if (buttonNode->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        buttonProp->UpdateType(ButtonType::ROUNDED_RECTANGLE);
    } else {
        auto popupButtonType = static_cast<ButtonType>(popupTheme->GetPopupButtonType());
        buttonProp->UpdateType(popupButtonType);
    }
    auto fontScale = pipelineContext->GetFontScale();
    if (fontScale == AGE_SCALE_NUMBER) {
        buttonProp->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(popupTheme->GetButtonHeight())));
    }
    buttonProp->UpdateAlignment(Alignment::CENTER);
    auto buttonMiniMumWidth = popupTheme->GetButtonMiniMumWidth().ConvertToPx();
    buttonProp->UpdateCalcMinSize(CalcSize(CalcLength(buttonMiniMumWidth), std::nullopt));
    auto renderContext = buttonNode->GetRenderContext();
    if (renderContext) {
        if (buttonNumber == PRIMARY_BUTTON_NUMBER) {
            renderContext->UpdateBackgroundColor(popupTheme->GetPrimaryButtonBackgroundColor());
        } else if (buttonNumber == SECONDARY_BUTTON_NUMBER) {
            renderContext->UpdateBackgroundColor(popupTheme->GetSecondaryButtonBackgroundColor());
        } else {
            renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        }
    }

    auto buttonEventHub = buttonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(buttonEventHub, nullptr);
    buttonEventHub->AddClickEvent(buttonParam.action);
    auto closeCallback = [weak = AceType::WeakClaim(AceType::RawPtr(popupNode)), targetId](GestureEvent& /* info */) {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        auto context = node->GetContext();
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
    buttonNode->MarkModifyDone();
    return buttonNode;
}

bool BubbleView::IsSupportBlurStyle(RefPtr<RenderContext>& renderContext, bool isShowInSubWindow, bool isTips)
{
    if (isTips) {
        return true;
    }
    if (isShowInSubWindow) {
        return renderContext->IsUniRenderEnabled();
    }
    return true;
}

PopupInfo GetPopupInfoHelper(
    const RefPtr<UINode>& customNode, const std::function<PopupInfo(const RefPtr<OverlayManager>&)>& getPopupInfoFunc)
{
    PopupInfo popupInfoError;
    auto context = customNode->GetContextWithCheck();
    CHECK_NULL_RETURN(context, popupInfoError);
    auto instanceId = context->GetInstanceId();
    auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(instanceId, SubwindowType::TYPE_POPUP);
    if (subwindow) {
        auto overlayManager = subwindow->GetOverlayManager();
        if (overlayManager) {
            auto popupInfo = getPopupInfoFunc(overlayManager);
            if (popupInfo.popupNode) {
                return popupInfo;
            }
        }
    }
    auto overlayManager = context->GetOverlayManager();
    if (overlayManager) {
        auto popupInfo = getPopupInfoFunc(overlayManager);
        if (popupInfo.popupNode) {
            return popupInfo;
        }
    }
    return popupInfoError;
}

PopupInfo BubbleView::GetPopupInfoWithCustomNode(const RefPtr<UINode>& customNode)
{
    return GetPopupInfoHelper(customNode, [customNode](const RefPtr<OverlayManager>& overlayManager) {
        return overlayManager->GetPopupInfoWithExistContent(customNode);
    });
}

PopupInfo BubbleView::GetPopupInfoWithTargetId(const RefPtr<UINode>& customNode, const int32_t targetId)
{
    return GetPopupInfoHelper(customNode,
        [targetId](const RefPtr<OverlayManager>& overlayManager) { return overlayManager->GetPopupInfo(targetId); });
}

RefPtr<OverlayManager> BubbleView::GetPopupOverlayManager(const RefPtr<UINode>& customNode, const int32_t targetId)
{
    auto context = customNode->GetContextWithCheck();
    CHECK_NULL_RETURN(context, nullptr);
    auto instanceId = context->GetInstanceId();
    auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(instanceId, SubwindowType::TYPE_POPUP);
    if (subwindow) {
        auto overlayManager = subwindow->GetOverlayManager();
        if (overlayManager) {
            auto popupInfo = overlayManager->GetPopupInfo(targetId);
            if (popupInfo.popupNode) {
                return overlayManager;
            }
        }
    }
    auto overlayManager = context->GetOverlayManager();
    if (overlayManager) {
        auto popupInfo = overlayManager->GetPopupInfo(targetId);
        if (popupInfo.popupNode) {
            return overlayManager;
        }
    }
    return nullptr;
}
} // namespace OHOS::Ace::NG
