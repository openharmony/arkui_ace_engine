/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/button/button_model_ng.h"

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
void ButtonModelNG::SetFontSize(const Dimension& fontSize)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontSize, fontSize);
}

void ButtonModelNG::SetFontWeight(const Ace::FontWeight& fontWeight)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontWeight, fontWeight);
}

void ButtonModelNG::SetFontStyle(const Ace::FontStyle& fontStyle)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontStyle, fontStyle);
}

void ButtonModelNG::SetFontFamily(const std::vector<std::string>& fontFamily)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontFamily, fontFamily);
}

void ButtonModelNG::SetFontColor(const Color& textColor)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontColor, textColor);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, textColor);
}

void ButtonModelNG::SetType(const int value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, Type, static_cast<ButtonType>(value));
}

void ButtonModelNG::SetStateEffect(const bool stateEffect)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto buttonEventHub = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);
    buttonEventHub->SetStateEffect(stateEffect);
}

void ButtonModelNG::SetLableStyle(ButtonParameters& buttonParameters)
{
    if (buttonParameters.textOverflow.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, TextOverflow, buttonParameters.textOverflow.value());
    }
    if (buttonParameters.maxLines.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, MaxLines, buttonParameters.maxLines.value());
    }
    if (buttonParameters.minFontSize.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, MinFontSize, buttonParameters.minFontSize.value());
    }
    if (buttonParameters.maxFontSize.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, MaxFontSize, buttonParameters.maxFontSize.value());
    }
    if (buttonParameters.heightAdaptivePolicy.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(
            ButtonLayoutProperty, HeightAdaptivePolicy, buttonParameters.heightAdaptivePolicy.value());
    }
    if (buttonParameters.fontSize.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontSize, buttonParameters.fontSize.value());
    }
    if (buttonParameters.fontWeight.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontWeight, buttonParameters.fontWeight.value());
    }
    if (buttonParameters.fontFamily.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontFamily, buttonParameters.fontFamily.value());
    }
    if (buttonParameters.fontStyle.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontStyle, buttonParameters.fontStyle.value());
    }
}

void ButtonModelNG::CreateWithLabel(const CreateWithPara& para, std::list<RefPtr<Component>>& buttonChildren)
{
    CreateWithLabel(para.label.value());
    if (para.labelSetInfoFirst.value()) {
        SetTypeAndStateEffect(para.typeFirst, para.stateEffectFirst);
    }
    if (para.labelSetInfoSecond.value()) {
        SetTypeAndStateEffect(para.typeSecond, para.stateEffectSecond);
    }
}

void ButtonModelNG::CreateWithLabel(const std::string& label)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    if (buttonNode->GetChildren().empty()) {
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_VOID(textNode);
        textNode->SetInternal();
        SetTextDefaultStyle(textNode, label);
        buttonNode->AddChild(textNode);
    }
    auto buttonAccessibilityProperty = buttonNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(buttonAccessibilityProperty);
    buttonAccessibilityProperty->SetText(label);
    stack->Push(buttonNode);
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, Label, label);
    auto layoutProperty = buttonNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetPaddingProperty()) {
        return;
    }
    auto buttonTheme = PipelineBase::GetCurrentContext()->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    auto padding = buttonTheme->GetPadding();
    PaddingProperty defaultPadding = { CalcLength(padding.Left()), CalcLength(padding.Right()),
        CalcLength(padding.Top()), CalcLength(padding.Bottom()) };
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, Padding, defaultPadding);
}

void ButtonModelNG::Create(const CreateWithPara& para, std::list<RefPtr<Component>>& buttonChildren) {}

void ButtonModelNG::CreateWithChild(const CreateWithPara& para)
{
    std::string tagName = "Button";
    Create(tagName);
    if (para.labelSetInfoFirst.value()) {
        SetTypeAndStateEffect(para.typeFirst, para.stateEffectFirst);
    }
}

void ButtonModelNG::Create(const std::string& tagName)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(tagName, nodeId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    stack->Push(frameNode);
}

void ButtonModelNG::Padding(const PaddingProperty& paddingNew, const Edge& paddingOld)
{
    NG::ViewAbstract::SetPadding(paddingNew);
}

void ButtonModelNG::OnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc)
{
    ViewAbstract::SetOnClick(std::move(tapEventFunc));
}

void ButtonModelNG::BackgroundColor(const Color& color, const bool& colorFlag)
{
    ViewAbstract::SetBackgroundColor(color);
}

void ButtonModelNG::SetSize(const std::optional<Dimension>& width, const std::optional<Dimension>& height)
{
    if (width.has_value()) {
        NG::ViewAbstract::SetWidth(NG::CalcLength(width.value()));
    }

    if (height.has_value()) {
        NG::ViewAbstract::SetHeight(NG::CalcLength(height.value()));
    }
}

void ButtonModelNG::SetBorderRadius(const Dimension& radius)
{
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = radius;
    borderRadius.radiusTopRight = radius;
    borderRadius.radiusBottomLeft = radius;
    borderRadius.radiusBottomRight = radius;
    borderRadius.multiValued = true;
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, BorderRadius, borderRadius);
}

void ButtonModelNG::SetBorderRadius(const std::optional<Dimension>& radiusTopLeft,
    const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
    const std::optional<Dimension>& radiusBottomRight)
{
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = radiusTopLeft;
    borderRadius.radiusTopRight = radiusTopRight;
    borderRadius.radiusBottomLeft = radiusBottomLeft;
    borderRadius.radiusBottomRight = radiusBottomRight;
    borderRadius.multiValued = true;
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, BorderRadius, borderRadius);
}

void ButtonModelNG::SetHoverEffect(const int32_t& hoverEffectNum)
{
    NG::ViewAbstract::SetHoverEffect(static_cast<HoverEffectType>(hoverEffectNum));
}

void ButtonModelNG::SetTypeAndStateEffect(const std::optional<ButtonType>& type, const std::optional<bool>& stateEffect)
{
    if (type.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, Type, type.value());
    } else {
        // undefined use capsule type.
        ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, Type, ButtonType::CAPSULE);
    }

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto buttonEventHub = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);
    buttonEventHub->SetStateEffect(stateEffect.value_or(true));
}

void ButtonModelNG::SetTextDefaultStyle(const RefPtr<FrameNode>& textNode, const std::string& label)
{
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto buttonTheme = PipelineBase::GetCurrentContext()->GetTheme<ButtonTheme>();
    auto textStyle = buttonTheme->GetTextStyle();
    textLayoutProperty->UpdateContent(label);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::CLIP);
    textLayoutProperty->UpdateMaxLines(buttonTheme->GetTextMaxLines());
    textLayoutProperty->UpdateFontSize(textStyle.GetFontSize());
    textLayoutProperty->UpdateTextColor(textStyle.GetTextColor());
    textLayoutProperty->UpdateFontWeight(textStyle.GetFontWeight());
}
} // namespace OHOS::Ace::NG
