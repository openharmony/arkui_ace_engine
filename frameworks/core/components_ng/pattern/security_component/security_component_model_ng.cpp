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

#include "base/i18n/localization.h"
#include "base/log/ace_scoring_log.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
RefPtr<SecurityComponentTheme> SecurityComponentModelNG::GetTheme()
{
    auto pipeline = PipelineContext::GetCurrentContext();
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

    if ((text != static_cast<int32_t>(SecurityComponentDescription::TEXT_NULL)) &&
        (icon != static_cast<int32_t>(SecurityComponentIconStyle::ICON_NULL))) {
        property->UpdateTextIconSpace(secCompTheme->GetTextIconSpace());
    } else {
        property->UpdateTextIconSpace(Dimension(0.0F));
    }

    if (backgroundType == BUTTON_TYPE_NULL) {
        property->UpdateBackgroundLeftPadding(secCompTheme->GetPaddingWithoutBg());
        property->UpdateBackgroundRightPadding(secCompTheme->GetPaddingWithoutBg());
        property->UpdateBackgroundTopPadding(secCompTheme->GetPaddingWithoutBg());
        property->UpdateBackgroundBottomPadding(secCompTheme->GetPaddingWithoutBg());
    } else {
        property->UpdateBackgroundLeftPadding(secCompTheme->GetBackgroundLeftPadding());
        property->UpdateBackgroundRightPadding(secCompTheme->GetBackgroundRightPadding());
        property->UpdateBackgroundTopPadding(secCompTheme->GetBackgroundTopPadding());
        property->UpdateBackgroundBottomPadding(secCompTheme->GetBackgroundBottomPadding());
    }

    property->UpdateTextIconLayoutDirection(SecurityComponentLayoutDirection::HORIZONTAL);
}

void SecurityComponentModelNG::CreateCommon(const std::string& tag, int32_t text, int32_t icon,
    int32_t backgroundType, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(tag, nodeId, patternCreator);
    CHECK_NULL_VOID(frameNode);

    if (frameNode->GetChildren().empty()) {
        bool isButtonVisible = (backgroundType != BUTTON_TYPE_NULL);
        auto buttonNode = FrameNode::CreateFrameNode(
            V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<ButtonPattern>());
        buttonNode->SetInternal();

        if (isButtonVisible) {
            SetDefaultBackgroundButton(buttonNode, backgroundType);
        } else {
            SetInvisibleBackgroundButton(buttonNode);
        }
        frameNode->AddChild(buttonNode);

        if (icon != static_cast<int32_t>(SecurityComponentIconStyle::ICON_NULL)) {
            auto imageIcon = FrameNode::CreateFrameNode(
                V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
            imageIcon->SetInternal();
            InternalResource::ResourceId iconId;
            if (GetIconResource(icon, iconId)) {
                SetDefaultIconStyle(imageIcon, iconId, isButtonVisible);
            }
            frameNode->AddChild(imageIcon);
        }

        if (text != static_cast<int32_t>(SecurityComponentDescription::TEXT_NULL)) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            textNode->SetInternal();
            std::string textStr = "";
            GetTextResource(text, textStr);
            SetDefaultTextStyle(textNode, textStr, isButtonVisible);
            frameNode->AddChild(textNode);
        }
    }

    InitLayoutProperty(frameNode, text, icon, backgroundType);
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
    textLayoutProperty->UpdateMaxLines(1);
    textLayoutProperty->UpdateFontSize(secCompTheme->GetFontSize());
    textLayoutProperty->UpdateItalicFontStyle(Ace::FontStyle::NORMAL);
    textLayoutProperty->UpdateFontWeight(FontWeight::MEDIUM);
    std::vector<std::string> defaultFontFamily = { "HarmonyOS Sans" };
    textLayoutProperty->UpdateFontFamily(defaultFontFamily);

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

void SecurityComponentModelNG::SetIconSize(const Dimension& value)
{
    auto iconProp = GetChildLayoutProprty<ImageLayoutProperty>(V2::IMAGE_ETS_TAG);
    CHECK_NULL_VOID(iconProp);
    iconProp->UpdateUserDefinedIdealSize(CalcSize(NG::CalcLength(value), NG::CalcLength(value)));
}

void SecurityComponentModelNG::SetIconColor(const Color& value)
{
    auto iconProp = GetChildLayoutProprty<ImageLayoutProperty>(V2::IMAGE_ETS_TAG);
    CHECK_NULL_VOID(iconProp);
    auto iconSrcInfo = iconProp->GetImageSourceInfo().value();
    iconSrcInfo.SetFillColor(value);
    iconProp->UpdateImageSourceInfo(iconSrcInfo);
}

void SecurityComponentModelNG::SetFontSize(const Dimension& value)
{
    auto textProp = GetChildLayoutProprty<TextLayoutProperty>(V2::TEXT_ETS_TAG);
    CHECK_NULL_VOID(textProp);
    textProp->UpdateFontSize(value);
}

void SecurityComponentModelNG::SetFontStyle(const Ace::FontStyle& value)
{
    auto textProp = GetChildLayoutProprty<TextLayoutProperty>(V2::TEXT_ETS_TAG);
    CHECK_NULL_VOID(textProp);
    textProp->UpdateItalicFontStyle(value);
}

void SecurityComponentModelNG::SetFontWeight(const FontWeight& value)
{
    auto textProp = GetChildLayoutProprty<TextLayoutProperty>(V2::TEXT_ETS_TAG);
    CHECK_NULL_VOID(textProp);
    textProp->UpdateFontWeight(value);
}

void SecurityComponentModelNG::SetFontFamily(const std::vector<std::string>& fontFamilies)
{
    auto textProp = GetChildLayoutProprty<TextLayoutProperty>(V2::TEXT_ETS_TAG);
    CHECK_NULL_VOID(textProp);
    textProp->UpdateFontFamily(fontFamilies);
}

void SecurityComponentModelNG::SetFontColor(const Color& value)
{
    auto textProp = GetChildLayoutProprty<TextLayoutProperty>(V2::TEXT_ETS_TAG);
    CHECK_NULL_VOID(textProp);
    textProp->UpdateTextColor(value);
}

void SecurityComponentModelNG::SetBackgroundColor(const Color& value)
{
    if (!IsBackgroundVisible()) {
        LOGW("background is not exist");
        return;
    }
    auto bgNode = GetCurSecCompChildNode(V2::BUTTON_ETS_TAG);
    CHECK_NULL_VOID(bgNode);
    const auto& renderContext = bgNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(value);
}

void SecurityComponentModelNG::SetBackgroundBorderWidth(const Dimension& value)
{
    if (!IsBackgroundVisible()) {
        LOGW("background is not exist");
        return;
    }

    auto bgProp = GetChildLayoutProprty<ButtonLayoutProperty>(V2::BUTTON_ETS_TAG);
    CHECK_NULL_VOID(bgProp);
    BorderWidthProperty widthProp;
    widthProp.SetBorderWidth(value);
    bgProp->UpdateBorderWidth(widthProp);
}

void SecurityComponentModelNG::SetBackgroundBorderColor(const Color& value)
{
    if (!IsBackgroundVisible()) {
        LOGW("background is not exist");
        return;
    }

    auto bgNode = GetCurSecCompChildNode(V2::BUTTON_ETS_TAG);
    CHECK_NULL_VOID(bgNode);
    const auto& renderContext = bgNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    BorderColorProperty borderColor;
    borderColor.SetColor(value);
    renderContext->UpdateBorderColor(borderColor);
}

void SecurityComponentModelNG::SetBackgroundBorderStyle(const BorderStyle& value)
{
    if (!IsBackgroundVisible()) {
        LOGW("background is not exist");
        return;
    }

    auto bgNode = GetCurSecCompChildNode(V2::BUTTON_ETS_TAG);
    CHECK_NULL_VOID(bgNode);
    const auto& renderContext = bgNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    BorderStyleProperty style;
    style.SetBorderStyle(value);
    renderContext->UpdateBorderStyle(style);
}

void SecurityComponentModelNG::SetBackgroundBorderRadius(const Dimension& value)
{
    if (!IsBackgroundVisible()) {
        LOGW("background is not exist");
        return;
    }
    auto bgProp = GetChildLayoutProprty<ButtonLayoutProperty>(V2::BUTTON_ETS_TAG);
    CHECK_NULL_VOID(bgProp);
    bgProp->UpdateBorderRadius(BorderRadiusProperty(value));
}

void SecurityComponentModelNG::SetBackgroundPadding(const std::optional<Dimension>& left,
    const std::optional<Dimension>& right, const std::optional<Dimension>& top,
    const std::optional<Dimension>& bottom)
{
    if (!IsBackgroundVisible()) {
        LOGW("Can not set background padding without background");
        return;
    }

    auto secCompTheme = GetTheme();
    CHECK_NULL_VOID(secCompTheme);
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty,
        BackgroundLeftPadding, left.value_or(secCompTheme->GetBackgroundLeftPadding()));
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty,
        BackgroundRightPadding, right.value_or(secCompTheme->GetBackgroundRightPadding()));
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty,
        BackgroundTopPadding, top.value_or(secCompTheme->GetBackgroundTopPadding()));
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty,
        BackgroundBottomPadding, bottom.value_or(secCompTheme->GetBackgroundBottomPadding()));
}

void SecurityComponentModelNG::SetBackgroundPadding(const std::optional<Dimension>& padding)
{
    SetBackgroundPadding(padding, padding, padding, padding);
}

void SecurityComponentModelNG::SetTextIconSpace(const Dimension& value)
{
    if ((GetCurSecCompChildNode(V2::TEXT_ETS_TAG) == nullptr) ||
        (GetCurSecCompChildNode(V2::IMAGE_ETS_TAG) == nullptr)) {
        LOGW("Can not set text icon padding without text and icon");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, TextIconSpace, value);
}

void SecurityComponentModelNG::SetTextIconLayoutDirection(const SecurityComponentLayoutDirection& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SecurityComponentLayoutProperty, TextIconLayoutDirection, value);
}
} // namespace OHOS::Ace::NG
