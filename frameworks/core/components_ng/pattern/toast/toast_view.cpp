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

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/toast/toast_theme.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/toast/toast_layout_property.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
float GetTextHeight(const RefPtr<FrameNode>& textNode)
{
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, 0.0f);
    auto layoutConstraint = textLayoutProperty->GetLayoutConstraint();

    auto textLayoutWrapper = textNode->CreateLayoutWrapper();
    CHECK_NULL_RETURN(textLayoutWrapper, 0.0f);
    textLayoutWrapper->Measure(layoutConstraint);
    auto textGeometry = textLayoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(textGeometry, 0.0f);
    auto textSize = textGeometry->GetMarginFrameSize();
    return textSize.Height();
}
} // namespace
RefPtr<FrameNode> ToastView::CreateToastNode(const std::string& message, const std::string& bottom, bool isRightToLeft)
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto toastTheme = context->GetTheme<ToastTheme>();
    CHECK_NULL_RETURN(toastTheme, nullptr);

    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toastId = ElementRegister::GetInstance()->MakeUniqueId();
    // make toast node
    auto toastNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, toastId, AceType::MakeRefPtr<ToastPattern>());
    CHECK_NULL_RETURN(toastNode, nullptr);
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    CHECK_NULL_RETURN(toastProperty, nullptr);

    auto toastAccessibilityProperty = toastNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_RETURN(toastAccessibilityProperty, nullptr);
    toastAccessibilityProperty->SetText(message);
    // create text in toast
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);

    UpdateTextLayoutProperty(textNode, message, isRightToLeft);
    UpdateTextContext(textNode);
    auto textHeight = GetTextHeight(textNode);
    if (textHeight > toastTheme->GetMinHeight().ConvertToPx()) {
        textLayoutProperty->UpdateTextAlign(TextAlign::START);
        textHeight = GetTextHeight(textNode);
    }
    textNode->MountToParent(toastNode);

    toastProperty->UpdateBottom(StringUtils::StringToDimensionWithThemeValue(bottom, true, toastTheme->GetBottom()));
    toastNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(HitTestMode::HTMTRANSPARENT);
    toastNode->MarkModifyDone();
    return toastNode;
}

void ToastView::UpdateTextLayoutProperty(
    const RefPtr<FrameNode>& textNode, const std::string& message, bool isRightToLeft)
{
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto toastTheme = context->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    auto fontWeight = toastTheme->GetTextStyle().GetFontWeight();
    auto textColor = toastTheme->GetTextStyle().GetTextColor();
    auto fontSize = toastTheme->GetTextStyle().GetFontSize();
    auto padding = toastTheme->GetPadding();
    PaddingProperty paddings;
    paddings.top = NG::CalcLength(padding.Top());
    paddings.bottom = NG::CalcLength(padding.Bottom());
    paddings.left = NG::CalcLength(padding.Left());
    paddings.right = NG::CalcLength(padding.Right());

    textLayoutProperty->UpdateContent(message);
    textLayoutProperty->UpdateTextColor(textColor);
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    textLayoutProperty->UpdateFontWeight(fontWeight);
    textLayoutProperty->UpdateFontSize(fontSize);
    textLayoutProperty->UpdateLayoutDirection((isRightToLeft ? TextDirection::RTL : TextDirection::LTR));
    textLayoutProperty->UpdatePadding(paddings);
}
void ToastView::UpdateTextContext(const RefPtr<FrameNode>& textNode)
{
    auto textContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textContext);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto toastTheme = pipelineContext->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    auto radius = toastTheme->GetRadius();
    auto toastBackgroundColor = toastTheme->GetBackgroundColor();
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(radius.GetX().ConvertToPx()));
    textContext->UpdateBackgroundColor(toastBackgroundColor);
    textContext->UpdateBorderRadius(borderRadius);
    textContext->UpdateBackShadow(ShadowConfig::DefaultShadowL);
}
} // namespace OHOS::Ace::NG
