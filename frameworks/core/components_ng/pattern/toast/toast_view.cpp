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

#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
constexpr float MAX_TOAST_SCALE = 2.0f;
RefPtr<FrameNode> ToastView::CreateToastNode(const ToastInfo& toastInfo)
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto toastTheme = context->GetTheme<ToastTheme>();
    CHECK_NULL_RETURN(toastTheme, nullptr);

    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toastId = ElementRegister::GetInstance()->MakeUniqueId();
    // make toast node
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TOAST_ETS_TAG, toastId);
    auto toastNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, toastId, AceType::MakeRefPtr<ToastPattern>());
    CHECK_NULL_RETURN(toastNode, nullptr);
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    CHECK_NULL_RETURN(toastProperty, nullptr);
    auto toastContext = toastNode->GetRenderContext();
    CHECK_NULL_RETURN(toastContext, nullptr);
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
    toastNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(HitTestMode::HTMTRANSPARENT);
    toastNode->MarkModifyDone();
    return toastNode;
}

void ToastView::UpdateTextLayoutProperty(
    const RefPtr<FrameNode>& textNode, const std::string& message,
    bool isRightToLeft, const std::optional<Color>& textColor)
{
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto toastTheme = context->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    auto fontSize = toastTheme->GetTextStyle().GetFontSize();
    auto padding = toastTheme->GetPadding();
    auto fontWeight = toastTheme->GetTextStyle().GetFontWeight();
    auto defaultColor = toastTheme->GetTextStyle().GetTextColor();
    textLayoutProperty->UpdateMaxFontScale(MAX_TOAST_SCALE);
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

void ToastView::UpdateToastContext(const RefPtr<FrameNode>& toastNode)
{
    auto toastContext = toastNode->GetRenderContext();
    CHECK_NULL_VOID(toastContext);
    auto pattern = toastNode->GetPattern<ToastPattern>();
    CHECK_NULL_VOID(pattern);
    auto pipelineContext = PipelineBase::GetCurrentContext();
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
    auto toastContext = toastNode->GetRenderContext();
    CHECK_NULL_VOID(toastContext);
    auto pattern = toastNode->GetPattern<ToastPattern>();
    CHECK_NULL_VOID(pattern);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto toastTheme = pipelineContext->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    auto toastInfo = pattern->GetToastInfo();
    auto shadowStyle = toastTheme->GetToastShadowStyle();
    auto shadow = toastInfo.shadow.value_or(Shadow::CreateShadow(shadowStyle));

    if (toastInfo.isTypeStyleShadow) {
        auto colorMode = pipelineContext->GetColorMode();
        auto shadowStyle = shadow.GetStyle();
        auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
        if (shadowTheme) {
            shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
        }
    }
    toastContext->UpdateBackShadow(shadow);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        toastContext->UpdateBackgroundColor(toastInfo.backgroundColor.value_or(toastTheme->GetDefaultBGColor()));
        BlurStyleOption styleOption;
        styleOption.blurStyle = static_cast<BlurStyle>(
            toastInfo.backgroundBlurStyle.value_or(toastTheme->GetToastBackgroundBlurStyle()));
        styleOption.policy = BlurStyleActivePolicy::ALWAYS_ACTIVE;
        if (!toastInfo.backgroundColor.has_value()) {
            styleOption.colorMode = static_cast<ThemeColorMode>(toastTheme->GetBgThemeColorMode());
        }
        toastContext->UpdateBackBlurStyle(styleOption);
    } else {
        auto toastBackgroundColor = toastTheme->GetBackgroundColor();
        toastContext->UpdateBackgroundColor(toastBackgroundColor);
    }
}
} // namespace OHOS::Ace::NG
