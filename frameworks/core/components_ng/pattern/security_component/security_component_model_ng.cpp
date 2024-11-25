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

#include "core/components_ng/pattern/security_component/security_component_model_ng.h"

#include "core/components/common/properties/text_style.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#ifdef SECURITY_COMPONENT_ENABLE
#include "core/components_ng/pattern/security_component/security_component_handler.h"
#endif
#include "core/components_ng/pattern/security_component/security_component_log.h"
#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
const static uint8_t DEFAULT_TRANSPARENCY_THRESHOLD = 0x1A;
const static uint8_t FULL_TRANSPARENCY_VALUE = 0xFF;
const static std::set<uint32_t> RELEASE_ATTRIBUTE_LIST = {
    0x0C000000,
};
RefPtr<SecurityComponentTheme> SecurityComponentModelNG::GetTheme()
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetTheme<SecurityComponentTheme>();
}

void SecurityComponentModelNG::InitLayoutProperty(RefPtr<FrameNode>& node, int32_t text, int32_t icon,
    int32_t backgroundType)
{
    auto property = node->GetLayoutProperty<SecurityComponentLayoutProperty>();
    CHECK_NULL_VOID(property);
    auto secCompTheme = GetTheme();
    CHECK_NULL_VOID(secCompTheme);
    property->UpdateSecurityComponentDescription(text);
    property->UpdateIconStyle(icon);
    property->UpdateBackgroundType(backgroundType);

    if ((text == static_cast<int32_t>(SecurityComponentDescription::TEXT_NULL)) ||
        (icon == static_cast<int32_t>(SecurityComponentIconStyle::ICON_NULL))) {
        property->UpdateTextIconSpace(Dimension(0.0));
    }

    if (backgroundType == BUTTON_TYPE_NULL) {
        property->UpdateBackgroundLeftPadding(secCompTheme->GetPaddingWithoutBg());
        property->UpdateBackgroundRightPadding(secCompTheme->GetPaddingWithoutBg());
        property->UpdateBackgroundTopPadding(secCompTheme->GetPaddingWithoutBg());
        property->UpdateBackgroundBottomPadding(secCompTheme->GetPaddingWithoutBg());
    }

    property->UpdateTextIconLayoutDirection(SecurityComponentLayoutDirection::HORIZONTAL);
}

RefPtr<FrameNode> SecurityComponentModelNG::CreateNode(const std::string& tag, int32_t nodeId,
    SecurityComponentElementStyle& style,
    const std::function<RefPtr<Pattern>(void)>& patternCreator, bool isArkuiComponent)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", tag.c_str(), nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(tag, nodeId, patternCreator);
    CHECK_NULL_RETURN(frameNode, nullptr);

    if (frameNode->GetChildren().empty()) {
        bool isButtonVisible = (style.backgroundType != BUTTON_TYPE_NULL);
        auto buttonNode = FrameNode::CreateFrameNode(
            V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<ButtonPattern>());
        buttonNode->SetInternal();

        if (isButtonVisible) {
            SetDefaultBackgroundButton(buttonNode, style.backgroundType);
        } else {
            SetInvisibleBackgroundButton(buttonNode);
        }
        frameNode->AddChild(buttonNode);

        if (style.icon != static_cast<int32_t>(SecurityComponentIconStyle::ICON_NULL)) {
            auto imageIcon = FrameNode::CreateFrameNode(
                V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
            imageIcon->SetInternal();
            InternalResource::ResourceId iconId;
            if (GetIconResource(style.icon, iconId)) {
                SetDefaultIconStyle(imageIcon, iconId, isButtonVisible);
            }
            frameNode->AddChild(imageIcon);
        }

        if (style.text != static_cast<int32_t>(SecurityComponentDescription::TEXT_NULL)) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_RETURN(textNode, nullptr);
            textNode->SetInternal();
            std::string textStr = "";
            GetTextResource(style.text, textStr);
            SetDefaultTextStyle(textNode, textStr, isButtonVisible);
            frameNode->AddChild(textNode);
        }
        InitLayoutProperty(frameNode, style.text, style.icon, style.backgroundType);
    }
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    CHECK_NULL_RETURN(property, nullptr);
    property->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    property->UpdateIsArkuiComponent(isArkuiComponent);
    auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContextSafely());
    CHECK_NULL_RETURN(pipeline, nullptr);
    pipeline->AddWindowStateChangedCallback(nodeId);
    return frameNode;
}

void SecurityComponentModelNG::CreateCommon(const std::string& tag, int32_t text, int32_t icon,
    int32_t backgroundType, const std::function<RefPtr<Pattern>(void)>& patternCreator, bool isArkuiComponent)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    SecurityComponentElementStyle style = {
        .text = text,
        .icon = icon,
        .backgroundType = backgroundType
    };
    auto frameNode = CreateNode(tag, nodeId, style, patternCreator, isArkuiComponent);
    CHECK_NULL_VOID(frameNode);
    stack->Push(frameNode);
}

void SecurityComponentModelNG::SetDefaultTextStyle(const RefPtr<FrameNode>& textNode, const std::string& text,
    bool isButtonVisible)
{
    auto secCompTheme = GetTheme();
    CHECK_NULL_VOID(secCompTheme);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(text);
    textLayoutProperty->UpdateMaxLines(secCompTheme->GetDefaultTextMaxLines());
    textLayoutProperty->UpdateFontSize(secCompTheme->GetFontSize());
    textLayoutProperty->UpdateItalicFontStyle(Ace::FontStyle::NORMAL);
    textLayoutProperty->UpdateFontWeight(FontWeight::MEDIUM);
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);

    if (isButtonVisible) {
        textLayoutProperty->UpdateTextColor(secCompTheme->GetFontColor());
    } else {
        textLayoutProperty->UpdateTextColor(secCompTheme->GetFontColorNoBg());
    }
}

void SecurityComponentModelNG::SetDefaultIconStyle(const RefPtr<FrameNode>& imageNode, InternalResource::ResourceId id,
    bool isButtonVisible)
{
    auto secCompTheme = GetTheme();
    CHECK_NULL_VOID(secCompTheme);
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(id);
    if (isButtonVisible) {
        imageSourceInfo.SetFillColor(secCompTheme->GetIconColor());
    } else {
        imageSourceInfo.SetFillColor(secCompTheme->GetIconColorNoBg());
    }

    auto iconProp = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(iconProp);
    iconProp->UpdateImageSourceInfo(imageSourceInfo);
    iconProp->UpdateUserDefinedIdealSize(
        CalcSize(NG::CalcLength(secCompTheme->GetIconSize()), NG::CalcLength(secCompTheme->GetIconSize())));
    // default follow text direction
    ImageModelNG::SetMatchTextDirection(Referenced::RawPtr(imageNode), true);
}

void SecurityComponentModelNG::SetDefaultBackgroundButton(const RefPtr<FrameNode>& buttonNode,
    int32_t type)
{
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    const auto& renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto secCompTheme = GetTheme();
    CHECK_NULL_VOID(secCompTheme);

    BorderColorProperty borderColor;
    borderColor.SetColor(secCompTheme->GetBorderColor());
    renderContext->UpdateBorderColor(borderColor);
    BorderWidthProperty widthProp;
    widthProp.SetBorderWidth(secCompTheme->GetBorderWidth());
    buttonLayoutProperty->UpdateBorderWidth(widthProp);
    BorderStyleProperty style;
    style.SetBorderStyle(BorderStyle::NONE);
    renderContext->UpdateBorderStyle(style);
    auto buttonRadius = secCompTheme->GetBorderRadius();
    buttonLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(buttonRadius));
    renderContext->UpdateBackgroundColor(secCompTheme->GetBackgroundColor());
    buttonLayoutProperty->UpdateType(static_cast<ButtonType>(type));
}

void SecurityComponentModelNG::SetInvisibleBackgroundButton(const RefPtr<FrameNode>& buttonNode)
{
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    const auto& renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    buttonLayoutProperty->UpdateType(ButtonType::NORMAL);
}

template<typename T>
RefPtr<T> GetChildLayoutProprty(const std::string& tag)
{
    auto node = GetCurSecCompChildNode(tag);
    CHECK_NULL_RETURN(node, nullptr);
    return node->GetLayoutProperty<T>();
}

bool SecurityComponentModelNG::IsBackgroundVisible()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    if (prop) {
        return (prop->GetBackgroundType() != BUTTON_TYPE_NULL);
    }
    return false;
}

bool SecurityComponentModelNG::IsArkuiComponent()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    if (prop && prop->GetIsArkuiComponent().has_value()) {
        return prop->GetIsArkuiComponent().value();
    }
    return false;
}

void SecurityComponentModelNG::NotifyFontColorSet()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    CHECK_NULL_VOID(prop);
    prop->UpdateIsFontColorSet(true);
}

bool SecurityComponentModelNG::IsInReleaseList(uint32_t value)
{
    return (RELEASE_ATTRIBUTE_LIST.find(value) != RELEASE_ATTRIBUTE_LIST.end());
}

bool SecurityComponentModelNG::IsBelowThreshold(const Color& value)
{
    return value.GetAlpha() < DEFAULT_TRANSPARENCY_THRESHOLD;
}

void SecurityComponentModelNG::SetIconSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, IconSize, value);
}

void SecurityComponentModelNG::SetIconColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(SecurityComponentPaintProperty, IconColor, value);
}

void SecurityComponentModelNG::SetFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, FontSize, value);
}

void SecurityComponentModelNG::SetFontStyle(const Ace::FontStyle& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, FontStyle, value);
}

void SecurityComponentModelNG::SetFontWeight(const FontWeight& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, FontWeight, value);
}

void SecurityComponentModelNG::SetFontFamily(const std::vector<std::string>& fontFamilies)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, FontFamily, fontFamilies);
}

void SecurityComponentModelNG::SetFontColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(SecurityComponentPaintProperty, FontColor, value);
    NotifyFontColorSet();
}

void SecurityComponentModelNG::SetBackgroundColor(const Color& value)
{
    if (!IsBackgroundVisible()) {
        SC_LOG_WARN("background is not exist");
        return;
    }

    bool res = false;
#ifdef SECURITY_COMPONENT_ENABLE
    res = SecurityComponentHandler::IsSystemAppCalling();
#endif
    Color resColor = value;
    if (!res && !IsInReleaseList(resColor.GetValue()) && !IsArkuiComponent() && IsBelowThreshold(value)) {
        resColor = value.ChangeAlpha(FULL_TRANSPARENCY_VALUE);
    }
    ACE_UPDATE_PAINT_PROPERTY(SecurityComponentPaintProperty, BackgroundColor, resColor);
}

void SecurityComponentModelNG::SetBackgroundBorderWidth(const Dimension& value)
{
    if (!IsBackgroundVisible()) {
        SC_LOG_WARN("background is not exist");
        return;
    }

    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, BackgroundBorderWidth, value);
}

void SecurityComponentModelNG::SetBackgroundBorderColor(const Color& value)
{
    if (!IsBackgroundVisible()) {
        SC_LOG_WARN("background is not exist");
        return;
    }
    ACE_UPDATE_PAINT_PROPERTY(SecurityComponentPaintProperty, BackgroundBorderColor, value);
}

void SecurityComponentModelNG::SetBackgroundBorderStyle(const BorderStyle& value)
{
    if (!IsBackgroundVisible()) {
        SC_LOG_WARN("background is not exist");
        return;
    }
    ACE_UPDATE_PAINT_PROPERTY(SecurityComponentPaintProperty, BackgroundBorderStyle, value);
}

void SecurityComponentModelNG::SetBackgroundBorderRadius(const Dimension& value)
{
    if (!IsBackgroundVisible()) {
        SC_LOG_WARN("background is not exist");
        return;
    }

    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, BackgroundBorderRadius, value);
}

void SecurityComponentModelNG::SetBackgroundPadding(const std::optional<Dimension>& left,
    const std::optional<Dimension>& right, const std::optional<Dimension>& top,
    const std::optional<Dimension>& bottom)
{
    if (!IsBackgroundVisible()) {
        SC_LOG_WARN("Can not set background padding without background");
        return;
    }

    auto secCompTheme = GetTheme();
    CHECK_NULL_VOID(secCompTheme);
    if (left.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty,
            BackgroundLeftPadding, left.value());
    }

    if (right.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty,
            BackgroundRightPadding, right.value());
    }
    if (top.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty,
            BackgroundTopPadding, top.value());
    }

    if (bottom.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty,
            BackgroundBottomPadding, bottom.value());
    }
}

void SecurityComponentModelNG::SetBackgroundPadding(const std::optional<Dimension>& padding)
{
    SetBackgroundPadding(padding, padding, padding, padding);
}

void SecurityComponentModelNG::SetTextIconSpace(const Dimension& value)
{
    if ((GetCurSecCompChildNode(V2::TEXT_ETS_TAG) == nullptr) ||
        (GetCurSecCompChildNode(V2::IMAGE_ETS_TAG) == nullptr)) {
        SC_LOG_WARN("Can not set text icon padding without text and icon");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, TextIconSpace, value);
}

void SecurityComponentModelNG::SetTextIconLayoutDirection(const SecurityComponentLayoutDirection& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, TextIconLayoutDirection, value);
}
} // namespace OHOS::Ace::NG
