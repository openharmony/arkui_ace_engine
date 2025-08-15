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

#include "base/utils/utils.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

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
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontColorSetByUser, true);
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
    auto buttonEventHub = frameNode->GetOrCreateEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);
    buttonEventHub->SetStateEffect(stateEffect);
}

void ButtonModelNG::SetLabelStyle(ButtonParameters& buttonParameters)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetLabelStyle(frameNode, buttonParameters);
}

void ButtonModelNG::SetButtonStyle(const std::optional<ButtonStyleMode>& buttonStyle)
{
    if (buttonStyle.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, ButtonStyle, buttonStyle.value());
        auto context = PipelineBase::GetCurrentContextSafely();
        CHECK_NULL_VOID(context);
        auto buttonTheme = context->GetTheme<ButtonTheme>();
        CHECK_NULL_VOID(buttonTheme);
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        ButtonRole buttonRole = layoutProperty->GetButtonRole().value_or(ButtonRole::NORMAL);
        auto bgColor = buttonTheme->GetBgColor(buttonStyle.value(), buttonRole);
        auto textColor = buttonTheme->GetTextColor(buttonStyle.value(), buttonRole);
        BackgroundColor(bgColor, true);
        SetFontColor(textColor);
    }
}

void ButtonModelNG::ParseButtonResColor(
    const RefPtr<ResourceObject>& resObj, Color& result, const ButtonColorType buttonColorType)
{
    auto parseFlag = ResourceParseUtils::ParseResColor(resObj, result);
    CHECK_EQUAL_VOID(parseFlag, true);
    auto context = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
    auto buttonTheme = context->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    switch (buttonColorType) {
        case ButtonColorType::FONT_COLOR:
            result = buttonTheme->GetTextStyle().GetTextColor();
            break;
        case ButtonColorType::BACKGROUND_COLOR:
            result = buttonTheme->GetBgColor();
            break;
        default:
            break;
    }
}

void ButtonModelNG::CreateWithColorResourceObj(const RefPtr<ResourceObject>& resObj,
    const ButtonColorType buttonColorType)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithColorResourceObj(frameNode, resObj, buttonColorType);
}

void ButtonModelNG::UpdateResColor(FrameNode* frameNode, Color result, const ButtonColorType buttonColorType)
{
    CHECK_NULL_VOID(frameNode);
    switch (buttonColorType) {
        case ButtonColorType::FONT_COLOR:
            SetFontColor(frameNode, result);
            break;
        case ButtonColorType::BACKGROUND_COLOR:
            BackgroundColor(frameNode, result, true);
            break;
        default:
            break;
    }
    frameNode->MarkModifyDone();
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_NORMAL);
}

void ButtonModelNG::CreateWithColorResourceObj(
    FrameNode* frameNode, const RefPtr<ResourceObject>& resObj, const ButtonColorType buttonColorType)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ButtonPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "button" + ColorTypeToString(buttonColorType);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [buttonColorType, weak = AceType::WeakClaim(frameNode)](
        const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        Color result;
        ParseButtonResColor(resObj, result, buttonColorType);
        UpdateResColor(AceType::RawPtr(frameNode), result, buttonColorType);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ButtonModelNG::CreateWithStringResourceObj(const RefPtr<ResourceObject>& resObj,
    const ButtonStringType buttonStringType)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ButtonPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "button" + StringTypeToStr(buttonStringType);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [buttonStringType, weak = AceType::WeakClaim(AceType::RawPtr(pattern))](
        const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        std::string result;
        if (ResourceParseUtils::ParseResString(resObj, result)) {
            pattern->UpdateComponentString(result, buttonStringType);
        }
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ButtonModelNG::CreateWithFamiliesResourceObj(const RefPtr<ResourceObject>& resObj,
    const ButtonStringType buttonStringType)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithFamiliesResourceObj(frameNode, resObj, buttonStringType);
}

void ButtonModelNG::UpdateDefaultFamilies(
    FrameNode* frameNode, std::vector<std::string>& value, const ButtonStringType buttonStringType)
{
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto buttonTheme = pipelineContext->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    value = buttonTheme->GetTextStyle().GetFontFamilies();

    if (pipelineContext->IsSystmColorChange()) {
        switch (buttonStringType) {
            case ButtonStringType::FONT_FAMILY:
                SetFontFamily(frameNode, value);
                break;
            default:
                break;
        }
    }
    if (frameNode->GetRerenderable()) {
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_NORMAL);
    }
}

void ButtonModelNG::UpdateComponentFamilies(
    FrameNode* frameNode, const std::vector<std::string>& value, const ButtonStringType buttonStringType)
{
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto buttonTheme = pipelineContext->GetTheme<ButtonTheme>();
    if (pipelineContext->IsSystmColorChange()) {
        switch (buttonStringType) {
            case ButtonStringType::FONT_FAMILY:
                SetFontFamily(frameNode, value);
                break;
            default:
                break;
        }
    }
    if (frameNode->GetRerenderable()) {
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void ButtonModelNG::CreateWithFamiliesResourceObj(
    FrameNode* frameNode, const RefPtr<ResourceObject>& resObj, const ButtonStringType buttonStringType)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ButtonPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "button" + StringTypeToStr(buttonStringType);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [buttonStringType, weak = AceType::WeakClaim(AceType::RawPtr(pattern))](
                            const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        std::vector<std::string> result;
        result.clear();
        auto frameNode = pattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        auto flag = ResourceParseUtils::ParseResFontFamilies(resObj, result);
        if (!flag || result.empty()) {
            UpdateDefaultFamilies(AceType::RawPtr(frameNode), result, buttonStringType);
            return;
        }
        ButtonModelNG::UpdateComponentFamilies(AceType::RawPtr(frameNode), result, buttonStringType);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ButtonModelNG::CreateWithDimensionFpResourceObj(const RefPtr<ResourceObject>& resObj,
    const ButtonDimensionType buttonDimensionType)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithDimensionFpResourceObj(frameNode, resObj, buttonDimensionType);
}
void ButtonModelNG::CreateWithDimensionFpResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj,
    const ButtonDimensionType buttonDimensionType)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ButtonPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "button" + DimensionTypeToString(buttonDimensionType);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [buttonDimensionType, weak = AceType::WeakClaim(AceType::RawPtr(pattern))](
        const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        CalcDimension result;
        if (ResourceParseUtils::ParseResDimensionFpNG(resObj, result, false)) {
            pattern->UpdateComponentDimension(result, buttonDimensionType);
        }
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ButtonModelNG::CreateWithDoubleResourceObj(const RefPtr<ResourceObject>& resObj,
    const ButtonDoubleType buttonDoubleType)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithDoubleResourceObj(frameNode, resObj, buttonDoubleType);
}

bool ButtonModelNG::CheckFontScale(bool resultFlag, double result, const ButtonDoubleType buttonDoubleType)
{
    switch (buttonDoubleType) {
        case ButtonDoubleType::MIN_FONT_SCALE:
            if (LessNotEqual(result, 0.0f) || GreatNotEqual(result, 1.0f)) {
                resultFlag = true;
            }
            break;
        case ButtonDoubleType::MAX_FONT_SCALE:
            resultFlag = LessNotEqual(result, 1.0f);
            break;
    }
    return resultFlag;
}

void ButtonModelNG::CreateWithDoubleResourceObj(
    FrameNode* frameNode, const RefPtr<ResourceObject>& resObj, const ButtonDoubleType buttonDoubleType)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ButtonPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "button" + DoubleTypeToString(buttonDoubleType);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [buttonDoubleType, weak = AceType::WeakClaim(AceType::RawPtr(pattern))](
        const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        double result;
        if (ResourceParseUtils::ParseResDouble(resObj, result)) {
            bool resultFlag = false;
            CHECK_EQUAL_VOID(CheckFontScale(resultFlag, result, buttonDoubleType), true);
            pattern->UpdateComponentDouble(result, buttonDoubleType);
        }
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

std::string ButtonModelNG::ColorTypeToString(const ButtonColorType buttonColorType)
{
    std::string rst;
    switch (buttonColorType) {
        case ButtonColorType::FONT_COLOR:
            rst = "FontColor";
            break;
        case ButtonColorType::BACKGROUND_COLOR:
            rst = "BackgroundColor";
            break;
        default:
            rst = "Unknown";
            break;
    }
    return rst;
}

std::string ButtonModelNG::StringTypeToStr(const ButtonStringType buttonStringType)
{
    std::string rst;
    switch (buttonStringType) {
        case ButtonStringType::LABEL:
            rst = "Label";
            break;
        case ButtonStringType::FONT_FAMILY:
            rst = "FontFamily";
            break;
        default:
            rst = "Unknown";
            break;
    }
    return rst;
}

std::string ButtonModelNG::DimensionTypeToString(const ButtonDimensionType buttonDimensionType)
{
    std::string rst;
    switch (buttonDimensionType) {
        case ButtonDimensionType::MIN_FONT_SIZE:
            rst = "MinFontSize";
            break;
        case ButtonDimensionType::MAX_FONT_SIZE:
            rst = "MaxFontSize";
            break;
        default:
            rst = "Unknown";
            break;
    }
    return rst;
}

std::string ButtonModelNG::DoubleTypeToString(const ButtonDoubleType buttonDoubleType)
{
    std::string rst;
    switch (buttonDoubleType) {
        case ButtonDoubleType::MIN_FONT_SCALE:
            rst = "MinFontScale";
            break;
        case ButtonDoubleType::MAX_FONT_SCALE:
            rst = "MaxFontScale";
            break;
        default:
            rst = "Unknown";
            break;
    }
    return rst;
}

void ButtonModelNG::SetRole(const std::optional<ButtonRole>& buttonRole)
{
    if (buttonRole.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, ButtonRole, buttonRole.value());
        auto context = PipelineBase::GetCurrentContextSafely();
        CHECK_NULL_VOID(context);
        auto buttonTheme = context->GetTheme<ButtonTheme>();
        CHECK_NULL_VOID(buttonTheme);
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        ButtonStyleMode buttonStyleMode = layoutProperty->GetButtonStyle().value_or(ButtonStyleMode::EMPHASIZE);
        auto bgColor = buttonTheme->GetBgColor(buttonStyleMode, buttonRole.value());
        auto textColor = buttonTheme->GetTextColor(buttonStyleMode, buttonRole.value());
        BackgroundColor(bgColor, true);
        SetFontColor(textColor);
    }
}

void ButtonModelNG::SetControlSize(const std::optional<ControlSize>& controlSize)
{
    if (controlSize.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, ControlSize, controlSize.value());
        auto context = PipelineBase::GetCurrentContextSafely();
        CHECK_NULL_VOID(context);
        auto buttonTheme = context->GetTheme<ButtonTheme>();
        CHECK_NULL_VOID(buttonTheme);
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(frameNode);
        SetButtonSize(frameNode, controlSize, buttonTheme);
        Dimension fontSize = buttonTheme->GetTextSize(controlSize.value());
        SetFontSize(fontSize);
    }
}

void ButtonModelNG::SetRole(FrameNode* frameNode, const std::optional<ButtonRole>& buttonRole)
{
    if (buttonRole.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, ButtonRole, buttonRole.value(), frameNode);
        auto context = PipelineBase::GetCurrentContextSafely();
        CHECK_NULL_VOID(context);
        auto buttonTheme = context->GetTheme<ButtonTheme>();
        CHECK_NULL_VOID(buttonTheme);
        auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        ButtonStyleMode buttonStyleMode = layoutProperty->GetButtonStyle().value_or(ButtonStyleMode::EMPHASIZE);
        auto bgColor = buttonTheme->GetBgColor(buttonStyleMode, buttonRole.value());
        auto textColor = buttonTheme->GetTextColor(buttonStyleMode, buttonRole.value());
        BackgroundColor(frameNode, bgColor, true);
        SetFontColor(frameNode, textColor);
    }
}

void ButtonModelNG::SetButtonStyle(FrameNode* frameNode, const std::optional<ButtonStyleMode>& buttonStyle)
{
    if (buttonStyle.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, ButtonStyle, buttonStyle.value(), frameNode);
        auto context = PipelineBase::GetCurrentContextSafely();
        CHECK_NULL_VOID(context);
        auto buttonTheme = context->GetTheme<ButtonTheme>();
        CHECK_NULL_VOID(buttonTheme);
        auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        ButtonRole buttonRole = layoutProperty->GetButtonRole().value_or(ButtonRole::NORMAL);
        auto bgColor = buttonTheme->GetBgColor(buttonStyle.value(), buttonRole);
        auto textColor = buttonTheme->GetTextColor(buttonStyle.value(), buttonRole);
        BackgroundColor(frameNode, bgColor, true);
        SetFontColor(frameNode, textColor);
    }
}

void ButtonModelNG::SetButtonSize(FrameNode* frameNode, const std::optional<ControlSize>& controlSize,
    RefPtr<ButtonTheme> buttonTheme)
{
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (controlSize.has_value()) {
        auto padding = buttonTheme->GetPadding(controlSize.value());
        ButtonStyleMode buttonStyle = layoutProperty->GetButtonStyle().value_or(ButtonStyleMode::EMPHASIZE);
        PaddingProperty defaultPadding;
        if (buttonStyle == ButtonStyleMode::TEXT && controlSize.value() == ControlSize::SMALL) {
            float leftPadding = buttonTheme->GetPaddingText().ConvertToPx();
            float rightPadding = buttonTheme->GetPaddingText().ConvertToPx();
            defaultPadding = { CalcLength(leftPadding), CalcLength(rightPadding), CalcLength(padding.Top()),
                CalcLength(padding.Bottom()) };
        } else {
            defaultPadding = { CalcLength(padding.Left()), CalcLength(padding.Right()), CalcLength(padding.Top()),
                CalcLength(padding.Bottom()) };
        }
        ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, Padding, defaultPadding);
    }
}

void ButtonModelNG::SetControlSize(FrameNode* frameNode, const std::optional<ControlSize>& controlSize)
{
    if (controlSize.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, ControlSize, controlSize.value(), frameNode);
        auto context = PipelineBase::GetCurrentContextSafely();
        CHECK_NULL_VOID(context);
        auto buttonTheme = context->GetTheme<ButtonTheme>();
        CHECK_NULL_VOID(buttonTheme);
        SetButtonSize(frameNode, controlSize, buttonTheme);
        Dimension fontSize = buttonTheme->GetTextSize(controlSize.value());
        SetFontSize(frameNode, fontSize);
    }
}

void ButtonModelNG::CreateWithLabel(const CreateWithPara& para, std::list<RefPtr<Component>>& buttonChildren)
{
    CreateWithLabel(para.label.value_or(""));
    SetTypeAndStateEffect(para.type, para.stateEffect);
    SetButtonStyle(para.buttonStyleMode);
    SetControlSize(para.controlSize);
    SetRole(para.buttonRole);
}

void ButtonModelNG::CreateWithLabel(const std::string& label)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::BUTTON_ETS_TAG, nodeId);
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
    auto context = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
    auto buttonTheme = context->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    auto padding = buttonTheme->GetPadding();
    PaddingProperty defaultPadding = { CalcLength(padding.Left()), CalcLength(padding.Right()),
        CalcLength(padding.Top()), CalcLength(padding.Bottom()), std::nullopt, std::nullopt };
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, Padding, defaultPadding);
}

void ButtonModelNG::SetLabel(FrameNode* frameNode, const char* label)
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

void ButtonModelNG::Create(const CreateWithPara& para, std::list<RefPtr<Component>>& buttonChildren) {}

void ButtonModelNG::CreateWithChild(const CreateWithPara& para)
{
    std::string tagName = "Button";
    Create(tagName);
    if (para.optionSetFirst.has_value() && para.optionSetFirst.value()) {
        SetTypeAndStateEffect(para.type, para.stateEffect);
        SetButtonStyle(para.buttonStyleMode);
        SetControlSize(para.controlSize);
        SetRole(para.buttonRole);
    } else if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, Type, ButtonType::ROUNDED_RECTANGLE);
    }
}

void ButtonModelNG::Create(const std::string& tagName)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", tagName.c_str(), nodeId);
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(tagName, nodeId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    stack->Push(frameNode);

    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->ResetFontColorSetByUser();
}

RefPtr<FrameNode> ButtonModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, nodeId, AceType::MakeRefPtr<ButtonPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    if (layoutProperty->GetPaddingProperty()) {
        return frameNode;
    }
    auto context = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_RETURN(context, nullptr);
    auto buttonTheme = context->GetTheme<ButtonTheme>();
    CHECK_NULL_RETURN(buttonTheme, nullptr);
    auto padding = buttonTheme->GetPadding();
    PaddingProperty defaultPadding = { CalcLength(padding.Left()), CalcLength(padding.Right()),
        CalcLength(padding.Top()), CalcLength(padding.Bottom()), std::nullopt, std::nullopt };
    layoutProperty->UpdatePadding(defaultPadding);

    if (frameNode->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        // undefined use ROUNDED_RECTANGLE type.
        layoutProperty->UpdateType(ButtonType::ROUNDED_RECTANGLE);
    } else {
        // undefined use capsule type.
        layoutProperty->UpdateType(ButtonType::CAPSULE);
    }
    return frameNode;
}

void ButtonModelNG::Padding(const PaddingProperty& paddingNew, const Edge& paddingOld)
{
    NG::ViewAbstract::SetPadding(paddingNew);
    auto button = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(button);
    auto pattern = button->GetPattern<ButtonPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetHasCustomPadding(true);
}

void ButtonModelNG::OnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc, double distanceThreshold)
{
    ViewAbstract::SetOnClick(std::move(tapEventFunc), distanceThreshold);
}

void ButtonModelNG::BackgroundColor(const Color& color, const bool& colorFlag)
{
    ViewAbstract::SetBackgroundColor(color);
}

void ButtonModelNG::BackgroundColor(FrameNode* frameNode, const Color& color, const bool& colorFlag)
{
    ViewAbstract::SetBackgroundColor(frameNode, color);
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

void ButtonModelNG::SetBorderRadius(FrameNode* frameNode, const Dimension& radius)
{
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = radius;
    borderRadius.radiusTopRight = radius;
    borderRadius.radiusBottomLeft = radius;
    borderRadius.radiusBottomRight = radius;
    borderRadius.multiValued = true;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, BorderRadius, borderRadius, frameNode);
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

void ButtonModelNG::SetLocalizedBorderRadius(const std::optional<Dimension>& radiusTopStart,
    const std::optional<Dimension>& radiusTopEnd, const std::optional<Dimension>& radiusBottomStart,
    const std::optional<Dimension>& radiusBottomEnd)
{
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopStart = radiusTopStart;
    borderRadius.radiusTopEnd = radiusTopEnd;
    borderRadius.radiusBottomStart = radiusBottomStart;
    borderRadius.radiusBottomEnd = radiusBottomEnd;
    borderRadius.multiValued = true;
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, BorderRadius, borderRadius);
}

void ButtonModelNG::SetBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& radiusTopLeft,
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

void ButtonModelNG::SetTypeAndStateEffect(const std::optional<ButtonType>& type, const std::optional<bool>& stateEffect)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    if (type.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, Type, type.value());
    } else {
        if (frameNode->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
            // undefined use ROUNDED_RECTANGLE type.
            ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, Type, ButtonType::ROUNDED_RECTANGLE);
        } else {
            // undefined use capsule type.
            ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, Type, ButtonType::CAPSULE);
        }
    }

    auto buttonEventHub = frameNode->GetOrCreateEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);
    buttonEventHub->SetStateEffect(stateEffect.value_or(true));
}

void ButtonModelNG::SetTextDefaultStyle(const RefPtr<FrameNode>& textNode, const std::string& label)
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

void ButtonModelNG::SetFontSize(FrameNode* frameNode, const Dimension& fontSize)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontSize, fontSize, frameNode);
    CHECK_NULL_VOID(frameNode);
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->ResetAdaptMinFontSize();
    textLayoutProperty->ResetAdaptMaxFontSize();
}

void ButtonModelNG::SetFontWeight(FrameNode* frameNode, const Ace::FontWeight& fontWeight)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontWeight, fontWeight, frameNode);
}

void ButtonModelNG::SetFontStyle(FrameNode* frameNode, const Ace::FontStyle& fontStyle)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontStyle, fontStyle, frameNode);
}

void ButtonModelNG::SetFontFamily(FrameNode* frameNode, const std::vector<std::string>& fontFamily)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontFamily, fontFamily, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontColorSetByUser, true, frameNode);
}

void ButtonModelNG::SetFontColor(FrameNode* frameNode, const Color& textColor)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontColor, textColor, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, textColor, frameNode);
}

void ButtonModelNG::SetType(FrameNode* frameNode, const int value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, Type, static_cast<ButtonType>(value), frameNode);
}

void ButtonModelNG::SetStateEffect(FrameNode* frameNode, const bool stateEffect)
{
    CHECK_NULL_VOID(frameNode);
    auto buttonEventHub = frameNode->GetOrCreateEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);
    buttonEventHub->SetStateEffect(stateEffect);
}

void ButtonModelNG::SetLabelStyle(FrameNode* frameNode, const ButtonParameters& buttonParameters)
{
    if (buttonParameters.textOverflow.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            ButtonLayoutProperty, TextOverflow, buttonParameters.textOverflow.value(), frameNode);
    }
    if (buttonParameters.maxLines.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, MaxLines, buttonParameters.maxLines.value(), frameNode);
    }
    if (buttonParameters.minFontSize.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            ButtonLayoutProperty, MinFontSize, buttonParameters.minFontSize.value(), frameNode);
    }
    if (buttonParameters.maxFontSize.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            ButtonLayoutProperty, MaxFontSize, buttonParameters.maxFontSize.value(), frameNode);
    }
    if (buttonParameters.heightAdaptivePolicy.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            ButtonLayoutProperty, HeightAdaptivePolicy, buttonParameters.heightAdaptivePolicy.value(), frameNode);
    }
    if (buttonParameters.fontSize.has_value()) {
        auto fontSize = buttonParameters.fontSize.value();
        if (GreatOrEqual(fontSize.Value(), 0.0)) {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontSize, fontSize, frameNode);
        } else {
            auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
            CHECK_NULL_VOID(layoutProperty);
            auto context = PipelineBase::GetCurrentContextSafely();
            CHECK_NULL_VOID(context);
            auto buttonTheme = context->GetTheme<ButtonTheme>();
            CHECK_NULL_VOID(buttonTheme);
            auto themeFontSize = buttonTheme->GetTextSize(layoutProperty->GetControlSizeValue(ControlSize::NORMAL));
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontSize, themeFontSize, frameNode);
        }
    }
    if (buttonParameters.fontWeight.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            ButtonLayoutProperty, FontWeight, buttonParameters.fontWeight.value(), frameNode);
    }
    if (buttonParameters.fontFamily.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            ButtonLayoutProperty, FontFamily, buttonParameters.fontFamily.value(), frameNode);
    }
    if (buttonParameters.fontStyle.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontStyle, buttonParameters.fontStyle.value(), frameNode);
    }
}

void ButtonModelNG::SetSize(
    FrameNode* frameNode, const std::optional<Dimension>& width, const std::optional<Dimension>& height)
{
    if (width.has_value()) {
        NG::ViewAbstract::SetWidth(frameNode, NG::CalcLength(width.value()));
    }

    if (height.has_value()) {
        NG::ViewAbstract::SetHeight(frameNode, NG::CalcLength(height.value()));
    }
}

std::string ButtonModelNG::GetLabel(FrameNode* frameNode)
{
    std::string value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ButtonLayoutProperty, Label, value, frameNode, value);
    return value;
}

Dimension ButtonModelNG::GetFontSize(FrameNode* frameNode)
{
    Dimension value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ButtonLayoutProperty, FontSize, value, frameNode, value);
    return value;
}

Ace::FontWeight ButtonModelNG::GetFontWeight(FrameNode* frameNode)
{
    Ace::FontWeight value = Ace::FontWeight::NORMAL;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        ButtonLayoutProperty, FontWeight, value, frameNode, Ace::FontWeight::NORMAL);
    return value;
}

Color ButtonModelNG::GetFontColor(FrameNode* frameNode)
{
    Color value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ButtonLayoutProperty, FontColor, value, frameNode, value);
    return value;
}

bool ButtonModelNG::GetAutoDisable(FrameNode* frameNode)
{
    bool value = false;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ButtonLayoutProperty, AutoDisable, value, frameNode, false);
    return value;
}

void ButtonModelNG::SetBuilderFunc(FrameNode* frameNode, NG::ButtonMakeCallback&& makeFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ButtonPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetBuilderFunc(std::move(makeFunc));
}

void ButtonModelNG::TriggerClick(FrameNode* frameNode, double xPos, double yPos)
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

void ButtonModelNG::ResetBorderRadius()
{
    ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(ButtonLayoutProperty, BorderRadius, PROPERTY_UPDATE_MEASURE);
}

ButtonType ButtonModelNG::GetType(FrameNode* frameNode)
{
    ButtonType value = ButtonType::CAPSULE;
    if (frameNode->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        value = ButtonType::ROUNDED_RECTANGLE;
        ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ButtonLayoutProperty, Type, value,
                                                        frameNode, ButtonType::ROUNDED_RECTANGLE);
    } else {
        ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ButtonLayoutProperty, Type, value,
                                                        frameNode, ButtonType::CAPSULE);
    }

    return value;
}

void ButtonModelNG::ApplyTheme(FrameNode* frameNode, ButtonStyleMode buttonStyle, ButtonRole buttonRole)
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

void ButtonModelNG::SetLabelWithCheck(FrameNode* frameNode, const char* label)
{
    auto property = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(property);
    if (!property->GetCreateWithLabelValue(false)) {
        return;
    }
    SetLabel(frameNode, label);
}

void ButtonModelNG::SetCreateWithLabel(bool createWithLabel)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, CreateWithLabel, createWithLabel);
}

void ButtonModelNG::SetMinFontScale(float minFontScale)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, MinFontScale, minFontScale);
}

void ButtonModelNG::SetMaxFontScale(float maxFontScale)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, MaxFontScale, maxFontScale);
}

void ButtonModelNG::SetCreateWithLabel(FrameNode* frameNode, bool createWithLabel)
{
    auto property = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(property);
    if (property->HasCreateWithLabel()) {
        return;
    }
    property->UpdateCreateWithLabel(createWithLabel);
}

void ButtonModelNG::SetMinFontScale(FrameNode* frameNode, float minFontScale)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, MinFontScale, minFontScale, frameNode);
}

void ButtonModelNG::SetMaxFontScale(FrameNode* frameNode, float maxFontScale)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, MaxFontScale, maxFontScale, frameNode);
}

float ButtonModelNG::GetMinFontScale(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0.0f);
    float minFontScale = 0.0f;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ButtonLayoutProperty, MinFontScale, minFontScale, frameNode, 0.0f);
    return minFontScale;
}

float ButtonModelNG::GetMaxFontScale(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0.0f);
    float maxFontScale = 0.0f;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ButtonLayoutProperty, MaxFontScale, maxFontScale, frameNode,
        static_cast<float>(INT32_MAX));
    return maxFontScale;
}
} // namespace OHOS::Ace::NG
