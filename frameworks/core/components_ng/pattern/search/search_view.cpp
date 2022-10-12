/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/search/search_view.h"

#include <string>

#include "core/components/common/properties/color.h"
#include "core/components/search/search_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

RefPtr<TextFieldControllerBase> SearchView::Create(
    std::optional<std::string>& value, std::optional<std::string>& placeholder, std::optional<std::string>& icon)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    auto frameNode =
        GetOrCreateSearchNode(V2::SEARCH_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SearchPattern>(); });

    const Color TRANSPARENT_COLOR = Color(0x00000000);
    constexpr Dimension FONT_SIZE(20);

    bool hasTextFieldNode = frameNode->HasTextFieldNode();
    bool hasImageNode = frameNode->HasImageNode();
    bool hasButtonNode = frameNode->HasButtonNode();

    // TextField frameNode
    auto textFieldFrameNode = CreateTextField(frameNode, placeholder, value);
    auto pattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    pattern->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    pattern->SetTextEditController(AceType::MakeRefPtr<TextEditController>());
    auto textInputRenderContext = textFieldFrameNode->GetRenderContext();
    textInputRenderContext->UpdateBackgroundColor(TRANSPARENT_COLOR);
    if (!hasTextFieldNode) {
        textFieldFrameNode->MountToParent(frameNode);
        textFieldFrameNode->MarkModifyDone();
    }

    // Image frameNode
    std::string src;
    if (icon.has_value()) {
        src = icon.value();
    }
    auto imageFrameNode = CreateImage(frameNode, src);
    if (!hasImageNode) {
        imageFrameNode->MountToParent(frameNode);
        imageFrameNode->MarkModifyDone();
    }

    // Button frameNode
    auto buttonFrameNode = CreateButtonWithLabel(frameNode, "");
    auto buttonRenderContext = buttonFrameNode->GetRenderContext();
    buttonRenderContext->UpdateBackgroundColor(TRANSPARENT_COLOR);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(buttonFrameNode->GetChildren().front());
    auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateTextColor(Color::BLUE);
    textLayoutProperty->UpdateFontSize(FONT_SIZE);
    if (!hasButtonNode) {
        buttonFrameNode->MountToParent(frameNode);
        buttonFrameNode->MarkModifyDone();
    }

    // Set search background
    auto renderContext = frameNode->GetRenderContext();
    auto textFieldTheme = textFieldFrameNode->GetContext()->GetThemeManager()->GetTheme<TextFieldTheme>();
    renderContext->UpdateBackgroundColor(textFieldTheme->GetBgColor());
    auto radius = textFieldTheme->GetBorderRadius();
    BorderRadiusProperty borderRadius { radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() };
    renderContext->UpdateBorderRadius(borderRadius);

    ViewStackProcessor::GetInstance()->Push(frameNode);

    return pattern->GetTextFieldController();
}

void SearchView::SetSearchButton(const std::string& text)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SearchLayoutProperty, SearchButton, text);
    ACE_UPDATE_PAINT_PROPERTY(SearchPaintProperty, SearchButton, text);
}

void SearchView::SetPlaceholderColor(const Color& color)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdatePlaceholderTextColor(color);
}

void SearchView::SetPlaceholderFont(const Font& font)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    if (font.fontSize) {
        textFieldLayoutProperty->UpdatePlaceholderFontSize(font.fontSize.value());
    }
    if (font.fontStyle) {
        textFieldLayoutProperty->UpdatePlaceholderItalicFontStyle(font.fontStyle.value());
    }
    if (font.fontWeight) {
        textFieldLayoutProperty->UpdatePlaceholderFontWeight(font.fontWeight.value());
    }
    if (!font.fontFamilies.empty()) {
        textFieldLayoutProperty->UpdatePlaceholderFontFamily(font.fontFamilies);
    }
}

void SearchView::SetTextFont(const Font& font)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    if (font.fontSize) {
        textFieldLayoutProperty->UpdateFontSize(font.fontSize.value());
    }
    if (font.fontStyle) {
        textFieldLayoutProperty->UpdateItalicFontStyle(font.fontStyle.value());
    }
    if (font.fontWeight) {
        textFieldLayoutProperty->UpdateFontWeight(font.fontWeight.value());
    }
    if (!font.fontFamilies.empty()) {
        textFieldLayoutProperty->UpdateFontFamily(font.fontFamilies);
    }
}

void SearchView::SetCopyOption(const CopyOptions& copyOptions)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateCopyOptions(copyOptions);
}

void SearchView::SetOnSubmit(ChangeAndSubmitEvent&& onSubmit)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SearchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSubmit(std::move(onSubmit));
}

void SearchView::SetOnChange(ChangeAndSubmitEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SearchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void SearchView::SetOnCopy(std::function<void(const std::string&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<SearchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCopy(std::move(func));
}

void SearchView::SetOnCut(std::function<void(const std::string&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<SearchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCut(std::move(func));
}

void SearchView::SetOnPaste(std::function<void(const std::string&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<SearchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPaste(std::move(func));
}

RefPtr<FrameNode> SearchView::CreateTextField(const RefPtr<SearchNode>& parentNode,
    const std::optional<std::string>& placeholder, const std::optional<std::string>& value)
{
    auto nodeId = parentNode->GetTextFieldId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    if (textFieldLayoutProperty) {
        if (value && !value.value().empty()) {
            textFieldLayoutProperty->UpdateValue(value.value());
        }
        if (placeholder) {
            textFieldLayoutProperty->UpdatePlaceholder(placeholder.value());
        }
        textFieldLayoutProperty->UpdateMaxLines(1);
        textFieldLayoutProperty->UpdatePlaceholderMaxLines(1);
    }
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    pattern->SetTextEditController(AceType::MakeRefPtr<TextEditController>());
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    renderContext->UpdateBackgroundColor(textFieldTheme->GetBgColor());
    auto radius = textFieldTheme->GetBorderRadius();
    auto textFieldPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    textFieldPaintProperty->UpdateCursorColor(textFieldTheme->GetCursorColor());
    BorderRadiusProperty borderRadius { radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() };
    renderContext->UpdateBorderRadius(borderRadius);

    return frameNode;
};

RefPtr<FrameNode> SearchView::CreateImage(const RefPtr<SearchNode>& parentNode, const std::string& src)
{
    auto nodeId = parentNode->GetImageId();
    ImageSourceInfo imageSourceInfo(src);
    if (src.empty()) {
        auto pipeline = parentNode->GetContext();
        CHECK_NULL_RETURN(pipeline, nullptr);
        auto themeManager = pipeline->GetThemeManager();
        CHECK_NULL_RETURN(themeManager, nullptr);
        auto iconTheme = themeManager->GetTheme<IconTheme>();
        CHECK_NULL_RETURN(iconTheme, nullptr);
        auto iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::SEARCH_SVG);
        imageSourceInfo.SetSrc(iconPath);
    }
    // else{TODO: Display system picture}
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    return frameNode;
}

RefPtr<FrameNode> SearchView::CreateButtonWithLabel(const RefPtr<SearchNode>& parentNode, const std::string& label)
{
    auto nodeId = parentNode->GetButtonId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(frameNode, nullptr);
    if (frameNode->GetChildren().empty()) {
        auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_RETURN(textNode, nullptr);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_RETURN(textLayoutProperty, nullptr);
        textLayoutProperty->UpdateContent(label);
        frameNode->AddChild(textNode);
    } else {
        auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
        CHECK_NULL_RETURN(textChild, nullptr);
        auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_RETURN(textLayoutProperty, nullptr);
        textLayoutProperty->UpdateContent(label);
    }
    return frameNode;
}

RefPtr<SearchNode> SearchView::GetOrCreateSearchNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto searchNode = ElementRegister::GetInstance()->GetSpecificItemById<SearchNode>(nodeId);
    if (searchNode) {
        if (searchNode->GetTag() == tag) {
            return searchNode;
        }
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = searchNode->GetParent();
        if (parent) {
            parent->RemoveChild(searchNode);
        }
    }

    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    searchNode = AceType::MakeRefPtr<SearchNode>(tag, nodeId, pattern, false);
    searchNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(searchNode);
    return searchNode;
}

} // namespace OHOS::Ace::NG
