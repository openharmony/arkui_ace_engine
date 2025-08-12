/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/button/button_model_static.h"
#include "ui/base/utils/utils.h"

#include "base/utils/utils.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {

void ButtonModelStatic::SetRole(FrameNode* frameNode, const std::optional<ButtonRole>& optButtonRole)
{
    if (optButtonRole.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, ButtonRole, optButtonRole.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, ButtonRole, frameNode);
    }
    auto context = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
    auto buttonTheme = context->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    ButtonStyleMode buttonStyleMode = layoutProperty->GetButtonStyle().value_or(ButtonStyleMode::EMPHASIZE);
    ButtonRole buttonRole = layoutProperty->GetButtonRole().value_or(ButtonRole::NORMAL);
    auto bgColor = buttonTheme->GetBgColor(buttonStyleMode, buttonRole);
    auto textColor = buttonTheme->GetTextColor(buttonStyleMode, buttonRole);
    BackgroundColor(frameNode, bgColor, true);
    SetFontColor(frameNode, textColor);
}

void ButtonModelStatic::SetButtonStyle(FrameNode* frameNode, const std::optional<ButtonStyleMode>& buttonStyle)
{
    if (buttonStyle.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, ButtonStyle, buttonStyle.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, ButtonStyle, frameNode);
    }
    auto context = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
    auto buttonTheme = context->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    ButtonStyleMode buttonStyleMode = layoutProperty->GetButtonStyle().value_or(ButtonStyleMode::EMPHASIZE);
    ButtonRole buttonRole = layoutProperty->GetButtonRole().value_or(ButtonRole::NORMAL);
    auto bgColor = buttonTheme->GetBgColor(buttonStyleMode, buttonRole);
    auto textColor = buttonTheme->GetTextColor(buttonStyleMode, buttonRole);
    BackgroundColor(frameNode, bgColor, true);
    SetFontColor(frameNode, textColor);
}

void ButtonModelStatic::SetButtonSize(FrameNode* frameNode, const std::optional<ControlSize>& controlSize,
    RefPtr<ButtonTheme> buttonTheme)
{
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto padding = buttonTheme->GetPadding(controlSize.value());
    ButtonStyleMode buttonStyle = layoutProperty->GetButtonStyle().value_or(ButtonStyleMode::EMPHASIZE);
    PaddingProperty defaultPadding;
    if (buttonStyle == ButtonStyleMode::TEXT && controlSize.value() == ControlSize::SMALL) {
        float leftPadding =  buttonTheme->GetPaddingText().ConvertToPx();
        float rightPadding = buttonTheme->GetPaddingText().ConvertToPx();
        defaultPadding = { CalcLength(leftPadding), CalcLength(rightPadding),
        CalcLength(padding.Top()), CalcLength(padding.Bottom()) };
    } else {
        defaultPadding = { CalcLength(padding.Left()), CalcLength(padding.Right()),
            CalcLength(padding.Top()), CalcLength(padding.Bottom()) };
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, Padding, defaultPadding, frameNode);
}

void ButtonModelStatic::SetControlSize(FrameNode* frameNode, const std::optional<ControlSize>& controlSize)
{
    CHECK_NULL_VOID(frameNode);
    if (controlSize.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, ControlSize, controlSize.value(), frameNode);
        auto context = frameNode->GetContext();
        CHECK_NULL_VOID(context);
        auto buttonTheme = context->GetTheme<ButtonTheme>();
        CHECK_NULL_VOID(buttonTheme);
        SetButtonSize(frameNode, controlSize, buttonTheme);
        Dimension fontSize = buttonTheme->GetTextSize(controlSize.value());
        SetFontSize(frameNode, fontSize);
    }
}

void ButtonModelStatic::SetLabel(FrameNode* frameNode, const char* label)
{
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetChildren().empty()) {
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_VOID(textNode);
        textNode->SetInternal();
        SetTextDefaultStyle(textNode, label);
        frameNode->AddChild(textNode);
    }
    auto buttonAccessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(buttonAccessibilityProperty);
    buttonAccessibilityProperty->SetText(label);
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateLabel(label);
    if (layoutProperty->GetPaddingProperty()) {
        return;
    }
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto buttonTheme = context->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    auto padding = buttonTheme->GetPadding();
    PaddingProperty defaultPadding = { CalcLength(padding.Left()), CalcLength(padding.Right()),
        CalcLength(padding.Top()), CalcLength(padding.Bottom()), std::nullopt, std::nullopt };
    layoutProperty->UpdatePadding(defaultPadding);
}

RefPtr<FrameNode> ButtonModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, nodeId, AceType::MakeRefPtr<ButtonPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    return frameNode;
}

void ButtonModelStatic::BackgroundColor(FrameNode* frameNode, const Color& color, const bool& colorFlag)
{
    ViewAbstract::SetBackgroundColor(frameNode, color);
}

void ButtonModelStatic::SetBorderRadius(FrameNode* frameNode, const Dimension& radius)
{
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = radius;
    borderRadius.radiusTopRight = radius;
    borderRadius.radiusBottomLeft = radius;
    borderRadius.radiusBottomRight = radius;
    borderRadius.multiValued = true;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, BorderRadius, borderRadius, frameNode);
}

void ButtonModelStatic::SetBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& radiusTopLeft,
    const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
    const std::optional<Dimension>& radiusBottomRight)
{
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = radiusTopLeft;
    borderRadius.radiusTopRight = radiusTopRight;
    borderRadius.radiusBottomLeft = radiusBottomLeft;
    borderRadius.radiusBottomRight = radiusBottomRight;
    borderRadius.multiValued = true;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, BorderRadius, borderRadius, frameNode);
}

void ButtonModelStatic::SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& fontSize)
{
    if (fontSize) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontSize, fontSize.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontSize, frameNode);
    }
    CHECK_NULL_VOID(frameNode);
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->ResetAdaptMinFontSize();
    textLayoutProperty->ResetAdaptMaxFontSize();
}

void ButtonModelStatic::SetFontWeight(FrameNode* frameNode, const std::optional<Ace::FontWeight>& fontWeight)
{
    if (fontWeight) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontWeight, fontWeight.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontWeight, frameNode);
    }
}

void ButtonModelStatic::SetFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& fontStyle)
{
    if (fontStyle) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontStyle, fontStyle.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontStyle, frameNode);
    }
}

void ButtonModelStatic::SetFontFamily(FrameNode* frameNode, const std::optional<std::vector<std::string>>& fontFamily)
{
    if (fontFamily && fontFamily->size() > 0) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontFamily, fontFamily.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontFamily, frameNode);
    }
}

void ButtonModelStatic::SetFontColor(FrameNode* frameNode, const std::optional<Color>& textColor)
{
    if (textColor) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontColor, textColor.value(), frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, textColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontColor, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
    }
}

void ButtonModelStatic::SetType(FrameNode* frameNode, const std::optional<int> value)
{
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, Type, static_cast<ButtonType>(value.value()), frameNode);
    } else {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
            // undefined use ROUNDED_RECTANGLE type.
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, Type, ButtonType::ROUNDED_RECTANGLE, frameNode);
        } else {
            // undefined use capsule type.
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, Type, ButtonType::CAPSULE, frameNode);
        }
    }
    auto buttonLayoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    if (buttonLayoutProperty->HasLabel()) {
        auto layoutProperty = frameNode->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        auto context = frameNode->GetContext();
        CHECK_NULL_VOID(context);
        auto buttonTheme = context->GetTheme<ButtonTheme>();
        CHECK_NULL_VOID(buttonTheme);
        auto padding = buttonTheme->GetPadding();
        PaddingProperty defaultPadding = { CalcLength(padding.Left()), CalcLength(padding.Right()),
            CalcLength(padding.Top()), CalcLength(padding.Bottom()), std::nullopt, std::nullopt };
        layoutProperty->UpdatePadding(defaultPadding);
    }
}

void ButtonModelStatic::SetStateEffect(FrameNode* frameNode, const std::optional<bool> stateEffect)
{
    CHECK_NULL_VOID(frameNode);
    auto buttonEventHub = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);
    if (stateEffect) {
        buttonEventHub->SetStateEffect(stateEffect.value());
    } else {
        buttonEventHub->SetStateEffect(false);
    }
}

void ButtonModelStatic::SetLabelStyle(FrameNode* frameNode, const std::optional<ButtonParameters>& buttonParameters)
{
    if (buttonParameters && buttonParameters->textOverflow.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            ButtonLayoutProperty, TextOverflow, buttonParameters->textOverflow.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, TextOverflow, frameNode);
    }
    if (buttonParameters && buttonParameters->maxLines.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, MaxLines,
            buttonParameters->maxLines.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, MaxLines, frameNode);
    }
    if (buttonParameters && buttonParameters->minFontSize.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            ButtonLayoutProperty, MinFontSize, buttonParameters->minFontSize.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, MinFontSize, frameNode);
    }
    if (buttonParameters && buttonParameters->maxFontSize.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            ButtonLayoutProperty, MaxFontSize, buttonParameters->maxFontSize.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, MaxFontSize, frameNode);
    }
    if (buttonParameters && buttonParameters->heightAdaptivePolicy.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            ButtonLayoutProperty, HeightAdaptivePolicy, buttonParameters->heightAdaptivePolicy.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, HeightAdaptivePolicy, frameNode);
    }
    if (buttonParameters) {
        SetFontSize(frameNode, buttonParameters->fontSize);
        SetFontWeight(frameNode, buttonParameters->fontWeight);
        SetFontFamily(frameNode, buttonParameters->fontFamily);
        SetFontStyle(frameNode, buttonParameters->fontStyle);
    } else {
        SetFontSize(frameNode, std::nullopt);
        SetFontWeight(frameNode, std::nullopt);
        SetFontFamily(frameNode, std::nullopt);
        SetFontStyle(frameNode, std::nullopt);
    }
}

void ButtonModelStatic::SetSize(
    FrameNode* frameNode, const std::optional<Dimension>& width, const std::optional<Dimension>& height)
{
    if (width.has_value()) {
        NG::ViewAbstract::SetWidth(frameNode, NG::CalcLength(width.value()));
    }

    if (height.has_value()) {
        NG::ViewAbstract::SetHeight(frameNode, NG::CalcLength(height.value()));
    }
}

std::string ButtonModelStatic::GetLabel(FrameNode* frameNode)
{
    std::string value;
    ACE_GET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, Label, value, frameNode);
    return value;
}

Dimension ButtonModelStatic::GetFontSize(FrameNode* frameNode)
{
    Dimension value;
    ACE_GET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontSize, value, frameNode);
    return value;
}

Ace::FontWeight ButtonModelStatic::GetFontWeight(FrameNode* frameNode)
{
    Ace::FontWeight value = Ace::FontWeight::NORMAL;
    ACE_GET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontWeight, value, frameNode);
    return value;
}

Color ButtonModelStatic::GetFontColor(FrameNode* frameNode)
{
    Color value;
    ACE_GET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontColor, value, frameNode);
    return value;
}

bool ButtonModelStatic::GetAutoDisable(FrameNode* frameNode)
{
    bool value = false;
    ACE_GET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, AutoDisable, value, frameNode);
    return value;
}

void ButtonModelStatic::TriggerClick(FrameNode* frameNode, double xPos, double yPos)
{
    auto pattern = frameNode->GetPattern<ButtonPattern>();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    if (!gestureEventHub->IsClickable()) {
        return;
    }
    pattern->SetButtonPress(xPos, yPos);
}

ButtonType ButtonModelStatic::GetType(FrameNode* frameNode)
{
    ButtonType value = ButtonType::CAPSULE;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        value = ButtonType::ROUNDED_RECTANGLE;
        ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ButtonLayoutProperty, Type, value,
                                                        frameNode, ButtonType::ROUNDED_RECTANGLE);
    } else {
        ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ButtonLayoutProperty, Type, value,
                                                        frameNode, ButtonType::CAPSULE);
    }

    return value;
}

void ButtonModelStatic::ApplyTheme(FrameNode* frameNode, ButtonStyleMode buttonStyle, ButtonRole buttonRole)
{
    auto context = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
    auto buttonTheme = context->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    auto bgColor = buttonTheme->GetBgColor(buttonStyle, buttonRole);
    auto textColor = buttonTheme->GetTextColor(buttonStyle, buttonRole);
    BackgroundColor(frameNode, bgColor, true);
    auto property = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(property);
    if (!property->GetCreateWithLabelValue(false)) {
        return;
    }
    SetFontColor(frameNode, textColor);
}

void ButtonModelStatic::SetLabelWithCheck(FrameNode* frameNode, const char* label)
{
    auto property = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(property);
    if (!property->GetCreateWithLabelValue(false)) {
        return;
    }
    SetLabel(frameNode, label);
}

void ButtonModelStatic::SetCreateWithLabel(FrameNode* frameNode, bool createWithLabel)
{
    auto property = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(property);
    if (property->HasCreateWithLabel()) {
        return;
    }
    property->UpdateCreateWithLabel(createWithLabel);
}

void ButtonModelStatic::SetMinFontScale(FrameNode* frameNode, const std::optional<float>& optValue)
{
    CHECK_NULL_VOID(frameNode);
    if (optValue) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, MinFontScale, optValue.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, MinFontScale, frameNode);
    }
}

void ButtonModelStatic::SetMaxFontScale(FrameNode* frameNode, const std::optional<float>& optValue)
{
    CHECK_NULL_VOID(frameNode);
    if (optValue) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, MaxFontScale, optValue.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, MaxFontScale, frameNode);
    }
}

float ButtonModelStatic::GetMinFontScale(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0.0f);
    float minFontScale = 0.0f;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ButtonLayoutProperty, MinFontScale, minFontScale, frameNode, 0.0f);
    return minFontScale;
}

float ButtonModelStatic::GetMaxFontScale(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0.0f);
    float maxFontScale = 0.0f;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ButtonLayoutProperty, MaxFontScale, maxFontScale, frameNode,
        static_cast<float>(INT32_MAX));
    return maxFontScale;
}

void ButtonModelStatic::SetTextDefaultStyle(const RefPtr<FrameNode>& textNode, const std::string& label)
{
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto context = textNode->GetContext();
    CHECK_NULL_VOID(context);
    auto buttonTheme = context->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    auto textStyle = buttonTheme->GetTextStyle();
    textLayoutProperty->UpdateContent(label);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateMaxLines(buttonTheme->GetTextMaxLines());
    textLayoutProperty->UpdateFontWeight(textStyle.GetFontWeight());
    textLayoutProperty->UpdateAdaptFontSizeStep(Dimension(1.0, DimensionUnit::FP));
}
} // namespace OHOS::Ace::NG
