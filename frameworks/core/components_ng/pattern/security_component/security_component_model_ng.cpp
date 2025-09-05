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
#include "core/components_ng/pattern/security_component/save_button/save_button_common.h"
#include "core/components_ng/pattern/security_component/save_button/save_button_model_ng.h"
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
const static double DEFAULT_ICON_FONT_SIZE = 24;
static inline RefPtr<FrameNode> GetSecCompChildNode(const FrameNode* parent, const std::string& tag)
{
    CHECK_NULL_RETURN(parent, nullptr);
    for (const auto& child : parent->GetChildren()) {
        auto node = AceType::DynamicCast<FrameNode, UINode>(child);
        CHECK_NULL_RETURN(node, nullptr);
        if (node->GetTag() == tag) {
            return node;
        }
    }
    return nullptr;
}

RefPtr<SecurityComponentTheme> SecurityComponentModelNG::GetTheme()
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetTheme<SecurityComponentTheme>();
}

void SecurityComponentModelNG::InitLayoutProperty(RefPtr<FrameNode>& node, int32_t text, int32_t icon,
    uint32_t symbolIcon, int32_t backgroundType)
{
    auto property = node->GetLayoutProperty<SecurityComponentLayoutProperty>();
    CHECK_NULL_VOID(property);
    auto secCompTheme = GetTheme();
    CHECK_NULL_VOID(secCompTheme);
    property->UpdateSecurityComponentDescription(text);
    property->UpdateIconStyle(icon);
    property->UpdateSymbolIconStyle(symbolIcon);
    property->UpdateBackgroundType(backgroundType);

    if (backgroundType == BUTTON_TYPE_NULL) {
        property->UpdateBackgroundLeftPadding(secCompTheme->GetPaddingWithoutBg());
        property->UpdateBackgroundRightPadding(secCompTheme->GetPaddingWithoutBg());
        property->UpdateBackgroundTopPadding(secCompTheme->GetPaddingWithoutBg());
        property->UpdateBackgroundBottomPadding(secCompTheme->GetPaddingWithoutBg());
    }

    property->UpdateTextIconLayoutDirection(SecurityComponentLayoutDirection::HORIZONTAL);
    bool hasCustomPermission = false;
#ifdef SECURITY_COMPONENT_ENABLE
    hasCustomPermission = SecurityComponentHandler::HasCustomPermissionForSecComp();
#endif
    property->UpdateHasCustomPermissionForSecComp(hasCustomPermission);
}

void SecurityComponentModelNG::InitChildNode(FrameNode* frameNode, const SecurityComponentElementStyle& style,
    GetIconResourceFuncType getIconResource, GetTextResourceFuncType getTextResource)
{
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

    if (style.symbolIcon && style.symbolIcon != static_cast<uint32_t>(SecurityComponentIconStyle::ICON_NULL)) {
        auto symbolIcon = FrameNode::CreateFrameNode(
            V2::SYMBOL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        SetDefaultSymbolIconStyle(symbolIcon, style.symbolIcon, isButtonVisible);
        frameNode->AddChild(symbolIcon);
    } else if (style.icon != static_cast<int32_t>(SecurityComponentIconStyle::ICON_NULL)) {
        auto imageIcon = FrameNode::CreateFrameNode(
            V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        imageIcon->SetInternal();
        InternalResource::ResourceId iconId;
        if (getIconResource(style.icon, iconId)) {
            SetDefaultIconStyle(imageIcon, iconId, isButtonVisible);
        }
        frameNode->AddChild(imageIcon);
    }

    if (style.text != static_cast<int32_t>(SecurityComponentDescription::TEXT_NULL)) {
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        textNode->SetInternal();
        std::string textStr = "";
        getTextResource(style.text, textStr);
        SetDefaultTextStyle(textNode, textStr, isButtonVisible);
        frameNode->AddChild(textNode);
    }
    auto refPtr = AceType::Claim(frameNode);
    InitLayoutProperty(refPtr, style.text, style.icon, style.symbolIcon, style.backgroundType);
}

bool SecurityComponentModelNG::InitSecurityComponent(FrameNode* frameNode,
    const SecurityComponentElementStyle& style, bool isArkuiComponent,
    GetIconResourceFuncType getIconResource, GetTextResourceFuncType getTextResource)
{
    CHECK_NULL_RETURN(frameNode, false);
    if (frameNode->GetChildren().empty()) {
        InitChildNode(frameNode, style, getIconResource, getTextResource);
    }
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    CHECK_NULL_RETURN(property, false);
    property->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    property->UpdateIsArkuiComponent(isArkuiComponent);
    property->UpdateTextStyle(style.text);
    auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContextSafelyWithCheck());
    CHECK_NULL_RETURN(pipeline, false);
    pipeline->AddWindowStateChangedCallback(frameNode->GetId());
    return true;
}

RefPtr<FrameNode> SecurityComponentModelNG::CreateNode(const std::string& tag, int32_t nodeId,
    SecurityComponentElementStyle& style, const std::function<RefPtr<Pattern>(void)>& patternCreator,
    bool isArkuiComponent)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", tag.c_str(), nodeId);
    auto frameNode = InitChild(tag, nodeId, style, patternCreator);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    CHECK_NULL_RETURN(property, nullptr);
    property->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    property->UpdateIsArkuiComponent(isArkuiComponent);
    property->UpdateTextStyle(style.text);
    auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContextSafelyWithCheck());
    CHECK_NULL_RETURN(pipeline, nullptr);
    pipeline->AddWindowStateChangedCallback(nodeId);
    return frameNode;
}

RefPtr<FrameNode> SecurityComponentModelNG::InitChild(const std::string& tag, int32_t nodeId,
    SecurityComponentElementStyle& style, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
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
        if (style.symbolIcon && style.symbolIcon != static_cast<uint32_t>(SecurityComponentIconStyle::ICON_NULL)) {
            if (style.icon != static_cast<int32_t>(SecurityComponentIconStyle::ICON_NULL)) {
                SC_LOG_ERROR("Image icon and symbol icon cannot be set at same time.");
                return nullptr;
            }
            auto symbolIcon = FrameNode::CreateFrameNode(
                V2::SYMBOL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            SetDefaultSymbolIconStyle(symbolIcon, style.symbolIcon, isButtonVisible);
            frameNode->AddChild(symbolIcon);
        } else if (style.icon != static_cast<int32_t>(SecurityComponentIconStyle::ICON_NULL)) {
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
        InitLayoutProperty(frameNode, style.text, style.icon, style.symbolIcon, style.backgroundType);
    }
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
        CalcSize(NG::CalcLength(secCompTheme->GetIconSize()), std::nullopt));
    // default follow text direction
    ImageModelNG::SetMatchTextDirection(Referenced::RawPtr(imageNode), true);
}

void SecurityComponentModelNG::SetDefaultSymbolIconStyle(
    const RefPtr<FrameNode> &symbolNode, uint32_t symbolId, bool isButtonVisible)
{
    CHECK_NULL_VOID(symbolNode);
    auto secCompTheme = GetTheme();
    CHECK_NULL_VOID(secCompTheme);
    auto iconProp = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(iconProp);
    SymbolSourceInfo symbolSourceInfo(symbolId);
    if (isButtonVisible) {
        iconProp->UpdateSymbolColorList({secCompTheme->GetDefaultSymbolIconColor()});
    } else {
        iconProp->UpdateSymbolColorList({secCompTheme->GetIconColorNoBg()});
    }
    iconProp->UpdateSymbolSourceInfo(symbolSourceInfo);
    iconProp->UpdateFontSize(Dimension(DEFAULT_ICON_FONT_SIZE, DimensionUnit::VP));
    symbolNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    symbolNode->MarkModifyDone();
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
    if (type == static_cast<int32_t>(ButtonType::ROUNDED_RECTANGLE)) {
        buttonRadius = secCompTheme->GetDefaultBorderRadius();
    }
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

bool SecurityComponentModelNG::IsBackgroundVisible(FrameNode* frameNode)
{
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

bool SecurityComponentModelNG::IsArkuiComponent(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    if (prop && prop->GetIsArkuiComponent().has_value()) {
        return prop->GetIsArkuiComponent().value();
    }
    return false;
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

void SecurityComponentModelNG::SetIconSize(const NG::CalcSize& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, IconCalcSize, value);
}

void SecurityComponentModelNG::SetIconBorderRadius(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    CHECK_NULL_VOID(prop);
    auto hasPermission = prop->GetHasCustomPermissionForSecComp();
    if (hasPermission.value_or(false)) {
        NG::BorderRadiusProperty borderRadius = BorderRadiusProperty(value);
        ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, IconBorderRadius, borderRadius);
    }
}

void SecurityComponentModelNG::SetIconBorderRadius(const std::optional<Dimension>& topLeft,
    const std::optional<Dimension>& topRight, const std::optional<Dimension>& bottomLeft,
    const std::optional<Dimension>& bottomRight)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    CHECK_NULL_VOID(prop);
    auto hasPermission = prop->GetHasCustomPermissionForSecComp();
    if (hasPermission.value_or(false)) {
        NG::BorderRadiusProperty borderRadius;
        borderRadius.radiusTopLeft = topLeft;
        borderRadius.radiusTopRight = topRight;
        borderRadius.radiusBottomLeft = bottomLeft;
        borderRadius.radiusBottomRight = bottomRight;
        ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, IconBorderRadius, borderRadius);
    }
}

void SecurityComponentModelNG::SetIcon(const ImageSourceInfo& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    CHECK_NULL_VOID(prop);
    auto hasPermission = prop->GetHasCustomPermissionForSecComp();
    if (hasPermission.value_or(false)) {
        auto secCompTheme = GetTheme();
        CHECK_NULL_VOID(secCompTheme);
        bool isButtonVisible = false;
        if (prop) {
            isButtonVisible = (prop->GetBackgroundType() != BUTTON_TYPE_NULL);
        }
        RefPtr<FrameNode> iconNode = GetSecCompChildNode(frameNode, V2::IMAGE_ETS_TAG);
        if (iconNode == nullptr) {
            iconNode = FrameNode::CreateFrameNode(
                V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
            iconNode->SetInternal();
            InternalResource::ResourceId iconId;
            int32_t iconStyle = static_cast<int32_t>(SaveButtonIconStyle::ICON_FULL_FILLED);
            if (SaveButtonModelNG::GetInstance()->GetIconResource(iconStyle, iconId)) {
                SetDefaultIconStyle(iconNode, iconId, isButtonVisible);
            }
            CHECK_NULL_VOID(iconNode);
            frameNode->AddChild(iconNode);

            prop->UpdateIconStyle(iconStyle);
        }

        ImageSourceInfo imageSourceInfo = value;
        if (isButtonVisible) {
            imageSourceInfo.SetFillColor(secCompTheme->GetIconColor());
        } else {
            imageSourceInfo.SetFillColor(secCompTheme->GetIconColorNoBg());
        }
        ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, ImageSourceInfo, imageSourceInfo);
    }
}

void SecurityComponentModelNG::SetText(const std::string& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    CHECK_NULL_VOID(prop);
    auto hasPermission = prop->GetHasCustomPermissionForSecComp();
    if (hasPermission.value_or(false)) {
        RefPtr<FrameNode> textNode = GetSecCompChildNode(frameNode, V2::TEXT_ETS_TAG);
        if (textNode == nullptr) {
            textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_VOID(textNode);
            textNode->SetInternal();
            std::string textStr = value;
            bool isButtonVisible = false;
            if (prop) {
                isButtonVisible = (prop->GetBackgroundType() != BUTTON_TYPE_NULL);
            }
            SetDefaultTextStyle(textNode, textStr, isButtonVisible);
            CHECK_NULL_VOID(textNode);
            frameNode->AddChild(textNode);

            prop->UpdateSecurityComponentDescription(static_cast<int32_t>(SaveButtonSaveDescription::DOWNLOAD));
        }
        ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, TextContent, value);
    }
}

void SecurityComponentModelNG::SetIconSize(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, IconSize, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, IconSize, frameNode);
    }
}

void SecurityComponentModelNG::SetIconColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(SecurityComponentPaintProperty, IconColor, value);
}

void SecurityComponentModelNG::SetIconColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SecurityComponentPaintProperty, IconColor, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(SecurityComponentPaintProperty, IconColor, frameNode);
    }
}

void SecurityComponentModelNG::SetSymbolIconSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, SymbolIconSize, value);
}

void SecurityComponentModelNG::SetSymbolIconColor(const std::vector<Color>& value)
{
    ACE_UPDATE_PAINT_PROPERTY(SecurityComponentPaintProperty, SymbolIconColor, value);
}

void SecurityComponentModelNG::SetFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, FontSize, value);
}

void SecurityComponentModelNG::SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, FontSize, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, FontSize, frameNode);
    }
}

void SecurityComponentModelNG::SetFontStyle(const Ace::FontStyle& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, FontStyle, value);
}

void SecurityComponentModelNG::SetFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, FontStyle, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, FontStyle, frameNode);
    }
}

void SecurityComponentModelNG::SetFontWeight(const FontWeight& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, FontWeight, value);
}

void SecurityComponentModelNG::SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, FontWeight, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, FontWeight, frameNode);
    }
}

void SecurityComponentModelNG::SetFontFamily(const std::vector<std::string>& fontFamilies)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, FontFamily, fontFamilies);
}

void SecurityComponentModelNG::SetFontFamily(FrameNode* frameNode,
    const std::optional<std::vector<std::string>>& fontFamilies)
{
    CHECK_NULL_VOID(frameNode);
    if (fontFamilies) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, FontFamily, fontFamilies.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, FontFamily, frameNode);
    }
}

void SecurityComponentModelNG::SetFontColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(SecurityComponentPaintProperty, FontColor, value);
    NotifyFontColorSet();
}

void SecurityComponentModelNG::SetStateEffect(const bool& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    CHECK_NULL_VOID(prop);
    auto hasPermission = prop->GetHasCustomPermissionForSecComp();
    if (hasPermission.value_or(false)) {
        ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, StateEffect, value);
    }
}

void SecurityComponentModelNG::SetTipPosition(const TipPosition& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    CHECK_NULL_VOID(prop);
    auto hasPermission = prop->GetHasCustomPermissionForSecComp();
    if (hasPermission.value_or(false)) {
        ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, TipPosition, value);
    }
}

void SecurityComponentModelNG::SetUserCancelEvent(const bool& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, UserCancelEvent, value);
}

void SecurityComponentModelNG::SetFontColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SecurityComponentPaintProperty, FontColor, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(SecurityComponentPaintProperty, FontColor, frameNode);
    }
}

void SecurityComponentModelNG::SetBackgroundColor(const Color& value)
{
    if (!IsBackgroundVisible()) {
        SC_LOG_WARN("background is not exist");
        return;
    }

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    CHECK_NULL_VOID(prop);
    bool res = prop->GetHasCustomPermissionForSecComp().value_or(false);
#ifdef SECURITY_COMPONENT_ENABLE
    res |= SecurityComponentHandler::IsSystemAppCalling();
#endif
    Color resColor = value;
    if (!res && !IsInReleaseList(resColor.GetValue()) && !IsArkuiComponent() && IsBelowThreshold(value)) {
        resColor = value.ChangeAlpha(FULL_TRANSPARENCY_VALUE);
    }
    ACE_UPDATE_PAINT_PROPERTY(SecurityComponentPaintProperty, BackgroundColor, resColor);
}

void SecurityComponentModelNG::SetBackgroundColor(FrameNode* frameNode, const std::optional<Color>& valueOpt)
{
    CHECK_NULL_VOID(frameNode);
    if (!IsBackgroundVisible(frameNode)) {
        SC_LOG_WARN("background is not exist");
        return;
    }

    if (!valueOpt.has_value()) {
        ACE_RESET_NODE_PAINT_PROPERTY(SecurityComponentPaintProperty, BackgroundColor, frameNode);
        return;
    }

    bool res = false;
#ifdef SECURITY_COMPONENT_ENABLE
    res = SecurityComponentHandler::IsSystemAppCalling();
#endif
    const Color value = valueOpt.value();
    Color resColor = value;
    if (!res && !IsInReleaseList(resColor.GetValue()) && !IsArkuiComponent(frameNode) && IsBelowThreshold(value)) {
        resColor = value.ChangeAlpha(FULL_TRANSPARENCY_VALUE);
    }
    ACE_UPDATE_NODE_PAINT_PROPERTY(SecurityComponentPaintProperty, BackgroundColor, resColor, frameNode);
}

void SecurityComponentModelNG::SetBackgroundBorderWidth(const Dimension& value)
{
    if (!IsBackgroundVisible()) {
        SC_LOG_WARN("background is not exist");
        return;
    }

    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, BackgroundBorderWidth, value);
}

void SecurityComponentModelNG::SetBackgroundBorderWidth(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (!IsBackgroundVisible(frameNode)) {
        SC_LOG_WARN("background is not exist");
        return;
    }

    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, BackgroundBorderWidth, value.value(),
            frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, BackgroundBorderWidth, frameNode);
    }
}

void SecurityComponentModelNG::SetBackgroundBorderColor(const Color& value)
{
    if (!IsBackgroundVisible()) {
        SC_LOG_WARN("background is not exist");
        return;
    }
    ACE_UPDATE_PAINT_PROPERTY(SecurityComponentPaintProperty, BackgroundBorderColor, value);
}

void SecurityComponentModelNG::SetBackgroundBorderColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (!IsBackgroundVisible(frameNode)) {
        SC_LOG_WARN("background is not exist");
        return;
    }
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SecurityComponentPaintProperty, BackgroundBorderColor, value.value(),
            frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(SecurityComponentPaintProperty, BackgroundBorderColor, frameNode);
    }
}

void SecurityComponentModelNG::SetBackgroundBorderStyle(const BorderStyle& value)
{
    if (!IsBackgroundVisible()) {
        SC_LOG_WARN("background is not exist");
        return;
    }
    ACE_UPDATE_PAINT_PROPERTY(SecurityComponentPaintProperty, BackgroundBorderStyle, value);
}

void SecurityComponentModelNG::SetBackgroundBorderStyle(FrameNode* frameNode, const std::optional<BorderStyle>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (!IsBackgroundVisible(frameNode)) {
        SC_LOG_WARN("background is not exist");
        return;
    }
    BorderStyle borderStyle = value.value_or(BorderStyle::NONE);
    ACE_UPDATE_NODE_PAINT_PROPERTY(SecurityComponentPaintProperty, BackgroundBorderStyle, borderStyle, frameNode);
}

void SecurityComponentModelNG::SetBackgroundBorderRadius(const Dimension& value)
{
    if (!IsBackgroundVisible()) {
        SC_LOG_WARN("background is not exist");
        return;
    }

    NG::BorderRadiusProperty borderRadius = BorderRadiusProperty(value);
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, BackgroundBorderRadius, borderRadius);
}

void SecurityComponentModelNG::SetBackgroundBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (!IsBackgroundVisible(frameNode)) {
        SC_LOG_WARN("background is not exist");
        return;
    }

    if (value) {
        NG::BorderRadiusProperty borderRadius = BorderRadiusProperty(value.value());
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, BackgroundBorderRadius, borderRadius,
            frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, BackgroundBorderRadius, frameNode);
    }
}

void SecurityComponentModelNG::SetBackgroundBorderRadius(const std::optional<Dimension>& topLeft,
    const std::optional<Dimension>& topRight, const std::optional<Dimension>& bottomLeft,
    const std::optional<Dimension>& bottomRight)
{
    if (!IsBackgroundVisible()) {
        SC_LOG_WARN("Can not set background padding without background");
        return;
    }
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = topLeft;
    borderRadius.radiusTopRight = topRight;
    borderRadius.radiusBottomLeft = bottomLeft;
    borderRadius.radiusBottomRight = bottomRight;
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, BackgroundBorderRadius, borderRadius);
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

void SecurityComponentModelNG::SetBackgroundPadding(
    FrameNode* frameNode,
    const std::optional<Dimension>& left, const std::optional<Dimension>& right,
    const std::optional<Dimension>& top, const std::optional<Dimension>& bottom)
{
    if (!IsBackgroundVisible(frameNode)) {
        SC_LOG_WARN("Can not set background padding without background");
        return;
    }

    auto secCompTheme = GetTheme();
    CHECK_NULL_VOID(secCompTheme);
    if (left.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty,
            BackgroundLeftPadding, left.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty,
            BackgroundLeftPadding, frameNode);
    }

    if (right.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty,
            BackgroundRightPadding, right.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty,
            BackgroundRightPadding, frameNode);
    }
    if (top.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty,
            BackgroundTopPadding, top.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty,
            BackgroundTopPadding, frameNode);
    }

    if (bottom.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty,
            BackgroundBottomPadding, bottom.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty,
            BackgroundBottomPadding, frameNode);
    }
}

void SecurityComponentModelNG::SetBackgroundPadding(const std::optional<Dimension>& padding)
{
    SetBackgroundPadding(padding, padding, padding, padding);
}

void SecurityComponentModelNG::SetTextIconSpace(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, TextIconSpace, value);
}

void SecurityComponentModelNG::SetTextIconSpace(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    CHECK_NULL_VOID(frameNode);
    auto refPtr = AceType::Claim(frameNode);
    if ((GetSecCompChildNode(refPtr, V2::TEXT_ETS_TAG) == nullptr) ||
        (GetSecCompChildNode(refPtr, V2::IMAGE_ETS_TAG) == nullptr)) {
        SC_LOG_WARN("Can not set text icon padding without text and icon");
        return;
    }
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, TextIconSpace, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, TextIconSpace, frameNode);
    }
}

void SecurityComponentModelNG::SetTextIconLayoutDirection(const SecurityComponentLayoutDirection& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, TextIconLayoutDirection, value);
}

void SecurityComponentModelNG::SetTextIconLayoutDirection(FrameNode* frameNode,
    const std::optional<SecurityComponentLayoutDirection>& value)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutDirection = value.value_or(SecurityComponentLayoutDirection::HORIZONTAL);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, TextIconLayoutDirection, layoutDirection,
        frameNode);
}

void SecurityComponentModelNG::SetAlign(const Alignment alignment)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, Alignment, alignment);
}

void SecurityComponentModelNG::SetMaxFontScale(const float value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, MaxFontScale, value);
}

void SecurityComponentModelNG::SetMinFontScale(const float value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, MinFontScale, value);
}

void SecurityComponentModelNG::SetMaxLines(const int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, MaxLines, value);
}

void SecurityComponentModelNG::SetAdaptMaxFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, AdaptMaxFontSize, value);
}

void SecurityComponentModelNG::SetAdaptMinFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, AdaptMinFontSize, value);
}

void SecurityComponentModelNG::SetHeightAdaptivePolicy(TextHeightAdaptivePolicy value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, HeightAdaptivePolicy, value);
}
} // namespace OHOS::Ace::NG
