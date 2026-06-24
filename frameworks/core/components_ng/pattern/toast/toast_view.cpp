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
#include "core/components_ng/pattern/toast/toast_view.h"

#include "core/components/common/properties/ui_material.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components/toast/toast_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "interfaces/inner_api/ace_kit/include/ui/view/theme/token_colors.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"
#include "core/components_ng/render/render_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/toast/toast_layout_property.h"

namespace OHOS::Ace::NG {
constexpr float MAX_TOAST_SCALE = 2.0f;
RefPtr<FrameNode> ToastView::CreateToastNode(const ToastInfo& toastInfo)
{
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toastId = ElementRegister::GetInstance()->MakeUniqueId();
    // make toast node
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TOAST_ETS_TAG, toastId);
    auto toastNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, toastId, AceType::MakeRefPtr<ToastPattern>());
    CHECK_NULL_RETURN(toastNode, nullptr);
    ACE_UINODE_TRACE(toastNode);
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    CHECK_NULL_RETURN(toastProperty, nullptr);
    auto toastContext = toastNode->GetRenderContext();
    CHECK_NULL_RETURN(toastContext, nullptr);
    auto context = toastNode->GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto toastTheme = context->GetTheme<ToastTheme>();
    CHECK_NULL_RETURN(toastTheme, nullptr);
    auto toastAccessibilityProperty = toastNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_RETURN(toastAccessibilityProperty, nullptr);
    toastAccessibilityProperty->SetUserTextValue(toastInfo.message);
    toastAccessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::NO_HIDE_DESCENDANTS);
    // create text in toast
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    auto pattern = toastNode->GetPattern<ToastPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    pattern->SetToastInfo(toastInfo);
    pattern->SetTextNode(textNode);
    UpdateTextLayoutProperty(textNode, toastInfo.message, toastInfo.isRightToLeft, toastInfo.textColor);
    UpdateToastContext(toastNode);
    textNode->MountToParent(toastNode);
    auto align = Alignment::ParseAlignment(toastInfo.alignment);
    if (align.has_value()) {
        toastProperty->UpdateToastAlignment(align.value());
    } else {
        toastProperty->ResetToastAlignment();
    }
    if (toastInfo.offset.has_value()) {
        toastProperty->UpdateToastOffset(toastInfo.offset.value());
    } else {
        toastProperty->ResetToastOffset();
    }
    toastProperty->UpdateBottom(
        StringUtils::StringToDimensionWithThemeValue(toastInfo.bottom, true, toastTheme->GetBottom()));
    toastProperty->UpdateShowMode(toastInfo.showMode);
    toastProperty->UpdateHoverModeArea(toastInfo.hoverModeArea);
    toastNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()
        ->SetHitTestMode(HitTestMode::HTMTRANSPARENT);
    toastNode->MarkModifyDone();
    return toastNode;
}

void ToastView::UpdateTextLayoutProperty(
    const RefPtr<FrameNode>& textNode, const std::string& message,
    bool isRightToLeft, const std::optional<Color>& textColor)
{
    ACE_UINODE_TRACE(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto context = textNode->GetContext();
    CHECK_NULL_VOID(context);
    auto toastTheme = context->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    auto fontSize = toastTheme->GetTextStyle().GetFontSize();
    auto padding = toastTheme->GetPadding();
    auto fontWeight = toastTheme->GetTextStyle().GetFontWeight();
    auto defaultColor = toastTheme->GetTextStyle().GetTextColor();
    textLayoutProperty->UpdateEnableSmallLanguageTruncation(true);
    textLayoutProperty->UpdatePunctuationOverflow(true);
    if (textNode->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
        textLayoutProperty->UpdateOrphanCharOptimization(true);
    }
    textLayoutProperty->UpdateMaxFontScale(std::min(MAX_TOAST_SCALE, context->GetMaxAppFontScale()));
    PaddingProperty paddings;
    paddings.top = NG::CalcLength(padding.Top());
    paddings.bottom = NG::CalcLength(padding.Bottom());
    paddings.left = NG::CalcLength(padding.Left());
    paddings.right = NG::CalcLength(padding.Right());

    textLayoutProperty->UpdateContent(message);
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    textLayoutProperty->UpdateFontSize(fontSize);
    textLayoutProperty->UpdatePadding(paddings);
    textLayoutProperty->UpdateTextColor(textColor.value_or(defaultColor));
    textLayoutProperty->UpdateFontWeight(fontWeight);
    auto textContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textContext);
    textContext->UpdateClipEdge(false);

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
        textLayoutProperty->UpdateEllipsisMode(EllipsisMode::TAIL);
    }
}

bool ToastView::SetToastSystemMaterial(const RefPtr<FrameNode>& toastNode, const ToastInfo& toastInfo)
{
    if (MaterialUtils::IsMaterialDisabled()) {
        return false;
    }
    if (toastInfo.systemMaterial && !MaterialUtils::IsEnableMaterialParam(toastInfo.systemMaterial)) {
        return false;
    }
    CHECK_NULL_RETURN(toastNode, false);
    auto renderContext = toastNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);

    // Handle low-end devices with IMMERSIVE material
    if (HandleLowEndImmersiveMaterial(toastNode, toastInfo, renderContext)) {
        return true;
    }

    // Handle user explicitly set systemMaterial
    if (HandleUserSetMaterial(toastNode, toastInfo, renderContext)) {
        return true;
    }

    // Apply default material for API 26+
    return ApplyDefaultMaterial(toastNode, toastInfo, renderContext);
}

bool ToastView::HandleLowEndImmersiveMaterial(
    const RefPtr<FrameNode>& toastNode,
    const ToastInfo& toastInfo,
    const RefPtr<RenderContext>& renderContext)
{
    if (SystemProperties::GetUiMaterialLevel() != UiMaterialLevel::SMOOTH) {
        return false;
    }

    if (!toastInfo.systemMaterial ||
        toastInfo.systemMaterial->GetType() != static_cast<int32_t>(Ace::MaterialType::IMMERSIVE)) {
        return false;
    }

    auto pipelineContext = toastNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, false);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_RETURN(themeConstants, false);

    SetLowEndImmersiveBackground(renderContext, themeConstants);
    SetLowEndImmersiveShadow(toastNode, toastInfo, renderContext, pipelineContext);

    return true;
}

void ToastView::SetLowEndImmersiveBackground(
    const RefPtr<RenderContext>& renderContext,
    const RefPtr<ThemeConstants>& themeConstants)
{
    auto resId = Ace::TokenColors::GetSystemColorResIdByIndex(Ace::TokenColors::COMP_BACKGROUND_PRIMARY);
    auto backgroundColor = themeConstants->GetColor(resId);
    renderContext->UpdateBackgroundColor(backgroundColor);
}

void ToastView::SetLowEndImmersiveShadow(
    const RefPtr<FrameNode>& toastNode,
    const ToastInfo& toastInfo,
    const RefPtr<RenderContext>& renderContext,
    const RefPtr<PipelineContext>& pipelineContext)
{
    // Check if shadow should be applied
    bool applyShadow = false;
    if (toastInfo.systemMaterial) {
        auto immersiveOptions = toastInfo.systemMaterial->GetImmersiveOptions();
        applyShadow = immersiveOptions && immersiveOptions->applyShadow;
    } else {
        // For default material case, apply shadow
        applyShadow = true;
    }

    if (!applyShadow) {
        return;
    }

    auto dipScale = pipelineContext->GetDipScale();
    auto shadow = Ace::MaterialUtils::GetImmersiveShadow(dipScale);
    renderContext->UpdateBackShadow(shadow);
}

bool ToastView::HandleUserSetMaterial(
    const RefPtr<FrameNode>& toastNode,
    const ToastInfo& toastInfo,
    const RefPtr<RenderContext>& renderContext)
{
    if (!toastInfo.systemMaterial) {
        return false;
    }

    renderContext->UpdateBackBlurStyle(std::nullopt);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    ViewAbstract::SetSystemMaterial(AceType::RawPtr(toastNode), AceType::RawPtr(toastInfo.systemMaterial));
    return true;
}

bool ToastView::ApplyDefaultMaterial(
    const RefPtr<FrameNode>& toastNode,
    const ToastInfo& toastInfo,
    const RefPtr<RenderContext>& renderContext)
{
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX) ||
        (!SystemProperties::IsDeviceSystemMaterialSupported() &&
        MaterialUtils::GetConfiguredMaterialState() == MaterialState::DEFAULT)) {
        return false;
    }

    bool hasCustomStyle = toastInfo.backgroundColor.has_value() ||
                          toastInfo.backgroundBlurStyle.has_value() ||
                          toastInfo.shadow.has_value();
    if (hasCustomStyle) {
        return false;
    }

    // Handle low-end devices
    if (SystemProperties::GetUiMaterialLevel() == UiMaterialLevel::SMOOTH) {
        auto pipelineContext = toastNode->GetContextRefPtr();
        CHECK_NULL_RETURN(pipelineContext, false);
        auto themeManager = pipelineContext->GetThemeManager();
        CHECK_NULL_RETURN(themeManager, false);
        auto themeConstants = themeManager->GetThemeConstants();
        CHECK_NULL_RETURN(themeConstants, false);

        SetLowEndImmersiveBackground(renderContext, themeConstants);
        SetLowEndImmersiveShadow(toastNode, toastInfo, renderContext, pipelineContext);
        return true;
    }

    auto defaultMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::THICK);
    renderContext->UpdateBackBlurStyle(std::nullopt);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    ViewAbstract::SetSystemMaterial(AceType::RawPtr(toastNode), AceType::RawPtr(defaultMaterial));
    return true;
}

void ToastView::UpdateToastContext(const RefPtr<FrameNode>& toastNode)
{
    ACE_UINODE_TRACE(toastNode);
    auto toastContext = toastNode->GetRenderContext();
    CHECK_NULL_VOID(toastContext);
    auto pattern = toastNode->GetPattern<ToastPattern>();
    CHECK_NULL_VOID(pattern);
    auto pipelineContext = toastNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto toastTheme = pipelineContext->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    auto radius = toastTheme->GetRadius();
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(radius.GetX().ConvertToPx()));
    toastContext->UpdateBorderRadius(borderRadius);
    if (toastTheme->GetToastDoubleBorderEnable()) {
        toastContext->UpdateOuterBorderRadius(borderRadius);
        auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
        CHECK_NULL_VOID(toastProperty);

        BorderWidthProperty innerWidthProp;
        innerWidthProp.SetBorderWidth(Dimension(toastTheme->GetToastInnerBorderWidth()));
        toastContext->UpdateBorderWidth(innerWidthProp);
        BorderColorProperty innerColorProp;
        innerColorProp.SetColor(toastTheme->GetToastInnerBorderColor());
        toastContext->UpdateBorderColor(innerColorProp);
        toastProperty->UpdateBorderWidth(innerWidthProp);

        BorderWidthProperty outerWidthProp;
        outerWidthProp.SetBorderWidth(Dimension(toastTheme->GetToastOuterBorderWidth()));
        toastContext->UpdateOuterBorderWidth(outerWidthProp);
        BorderColorProperty outerColorProp;
        outerColorProp.SetColor(toastTheme->GetToastOuterBorderColor());
        toastContext->UpdateOuterBorderColor(outerColorProp);
    }
    auto toastInfo = pattern->GetToastInfo();
    ToastView::UpdateToastNodeStyle(toastNode);
}

void ToastView::UpdateToastNodeStyle(const RefPtr<FrameNode>& toastNode)
{
    ACE_UINODE_TRACE(toastNode);
    auto toastContext = toastNode->GetRenderContext();
    CHECK_NULL_VOID(toastContext);
    auto pattern = toastNode->GetPattern<ToastPattern>();
    CHECK_NULL_VOID(pattern);
    auto pipelineContext = toastNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto toastTheme = pipelineContext->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    auto toastInfo = pattern->GetToastInfo();

    // Set SystemMaterial first, before updating background color, blur style and shadow
    bool isUserSetMaterial = SetToastSystemMaterial(toastNode, toastInfo);

    // Update background color and blur style only if SystemMaterial is not set
    UpdateToastBackgroundAndBlur(toastContext, toastInfo, toastTheme, isUserSetMaterial);

    // Update shadow based on SystemMaterial and applyShadow
    UpdateToastShadow(toastContext, toastInfo, toastTheme, pipelineContext, isUserSetMaterial);
}

void ToastView::UpdateToastBackgroundAndBlur(
    const RefPtr<RenderContext>& renderContext,
    const ToastInfo& toastInfo,
    const RefPtr<ToastTheme>& toastTheme,
    bool isUserSetMaterial)
{
    if (isUserSetMaterial) {
        return;  // Don't update background color and blur when material is set
    }

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        renderContext->UpdateBackgroundColor(toastInfo.backgroundColor.value_or(toastTheme->GetDefaultBGColor()));
        BlurStyleOption styleOption;
        styleOption.blurStyle = static_cast<BlurStyle>(
            toastInfo.backgroundBlurStyle.value_or(toastTheme->GetToastBackgroundBlurStyle()));
        styleOption.policy = BlurStyleActivePolicy::ALWAYS_ACTIVE;
        if (!toastInfo.backgroundColor.has_value()) {
            styleOption.colorMode = static_cast<ThemeColorMode>(toastTheme->GetBgThemeColorMode());
        }
        renderContext->UpdateBackBlurStyle(styleOption);
    } else {
        auto toastBackgroundColor = toastTheme->GetBackgroundColor();
        renderContext->UpdateBackgroundColor(toastBackgroundColor);
    }
}

bool ToastView::ShouldSkipShadowUpdate(const ToastInfo& toastInfo, bool isUserSetMaterial)
{
    if (!isUserSetMaterial) {
        return false;
    }

    auto systemMaterial = toastInfo.systemMaterial;
    if (!systemMaterial) {
        return false;
    }

    auto materialType = static_cast<Ace::MaterialType>(systemMaterial->GetType());
    if (materialType != Ace::MaterialType::IMMERSIVE) {
        return true;
    }

    auto immersiveOptions = systemMaterial->GetImmersiveOptions();
    return immersiveOptions && immersiveOptions->applyShadow;
}

Shadow ToastView::GetToastShadow(
    const ToastInfo& toastInfo,
    const RefPtr<ToastTheme>& toastTheme,
    const RefPtr<PipelineContext>& pipelineContext)
{
    // Get shadow from theme if user hasn't set it
    Shadow shadow;
    if (toastInfo.shadow.has_value()) {
        shadow = toastInfo.shadow.value();
    } else {
        auto shadowStyle = toastTheme->GetToastShadowStyle();
        auto colorMode = pipelineContext->GetColorMode();
        auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
        if (shadowTheme) {
            shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
        }
    }

    if (toastInfo.isTypeStyleShadow) {
        auto colorMode = pipelineContext->GetColorMode();
        auto shadowStyle = shadow.GetStyle();
        auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
        if (shadowTheme) {
            shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
        }
    }

    return shadow;
}

void ToastView::UpdateToastShadow(
    const RefPtr<RenderContext>& renderContext,
    const ToastInfo& toastInfo,
    const RefPtr<ToastTheme>& toastTheme,
    const RefPtr<PipelineContext>& pipelineContext,
    bool isUserSetMaterial)
{
    if (ShouldSkipShadowUpdate(toastInfo, isUserSetMaterial)) {
        return;
    }

    auto shadow = GetToastShadow(toastInfo, toastTheme, pipelineContext);
    renderContext->UpdateBackShadow(shadow);
}
} // namespace OHOS::Ace::NG
