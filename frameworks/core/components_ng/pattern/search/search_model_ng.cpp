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

#include "core/components_ng/pattern/search/search_model_ng.h"

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

RefPtr<TextFieldControllerBase> SearchModelNG::Create(const std::optional<std::string>& value,
    const std::optional<std::string>& placeholder, const std::optional<std::string>& icon)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    auto frameNode =
        GetOrCreateSearchNode(V2::SEARCH_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SearchPattern>(); });

    bool hasTextFieldNode = frameNode->HasTextFieldNode();
    bool hasImageNode = frameNode->HasImageNode();
    bool hasButtonNode = frameNode->HasButtonNode();
    bool hasCancelImageNode = frameNode->HasCancelImageNode();
    bool hasCancelButtonNode = frameNode->HasCancelButtonNode();

    // TextField frameNode
    auto searchTheme = PipelineBase::GetCurrentContext()->GetTheme<SearchTheme>();
    auto textFieldFrameNode = CreateTextField(frameNode, placeholder, value);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    textFieldPattern->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    textFieldPattern->SetTextEditController(AceType::MakeRefPtr<TextEditController>());
    auto textInputRenderContext = textFieldFrameNode->GetRenderContext();
    textInputRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
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

    // CancelImage frameNode
    auto cancelImageFrameNode = CreateCancelImage(frameNode);
    if (!hasCancelImageNode) {
        cancelImageFrameNode->MountToParent(frameNode);
        cancelImageFrameNode->MarkModifyDone();
    }
    // CancelButton frameNode
    if (!hasCancelButtonNode) {
        auto cancelButtonFrameNode = CreateCancelButton(frameNode);
        auto cancelButtonRenderContext = cancelButtonFrameNode->GetRenderContext();
        cancelButtonRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        auto textFrameNode = AceType::DynamicCast<FrameNode>(cancelButtonFrameNode->GetChildren().front());
        auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateFontSize(searchTheme->GetFontSize());
        auto cancelButtonlayoutProperty = cancelButtonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
        cancelButtonlayoutProperty->UpdateType(ButtonType::CIRCLE);
        cancelButtonFrameNode->MountToParent(frameNode);
        cancelButtonFrameNode->MarkModifyDone();
    }

    // Button frameNode
    if (!hasButtonNode) {
        auto buttonFrameNode = CreateButton(frameNode);
        auto buttonRenderContext = buttonFrameNode->GetRenderContext();
        buttonRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        auto textFrameNode = AceType::DynamicCast<FrameNode>(buttonFrameNode->GetChildren().front());
        auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateTextColor(searchTheme->GetSearchButtonTextColor());
        textLayoutProperty->UpdateFontSize(searchTheme->GetFontSize());
        buttonFrameNode->MountToParent(frameNode);
        buttonFrameNode->MarkModifyDone();
    }

    // Set search background
    auto renderContext = frameNode->GetRenderContext();
    auto textFieldTheme = PipelineBase::GetCurrentContext()->GetTheme<TextFieldTheme>();
    renderContext->UpdateBackgroundColor(textFieldTheme->GetBgColor());
    auto radius = textFieldTheme->GetBorderRadius();
    BorderRadiusProperty borderRadius { radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() };
    renderContext->UpdateBorderRadius(borderRadius);

    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    pattern->SetSearchController(AceType::MakeRefPtr<TextFieldController>());
    return pattern->GetSearchController();
}

void SearchModelNG::SetSearchButton(const std::string& text)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SearchLayoutProperty, SearchButton, text);
}

void SearchModelNG::SetPlaceholderColor(const Color& color)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdatePlaceholderTextColor(color);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetPlaceholderFont(const Font& font)
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
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetTextFont(const Font& font)
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
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetTextAlign(const TextAlign& textAlign)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateTextAlign(textAlign);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetCopyOption(const CopyOptions& copyOptions)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateCopyOptions(copyOptions);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetOnSubmit(std::function<void(const std::string&)>&& onSubmit)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SearchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSubmit(std::move(onSubmit));
}

void SearchModelNG::SetOnChange(std::function<void(const std::string&)>&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SearchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void SearchModelNG::SetOnCopy(std::function<void(const std::string&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<SearchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCopy(std::move(func));
}

void SearchModelNG::SetOnCut(std::function<void(const std::string&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<SearchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCut(std::move(func));
}

void SearchModelNG::SetOnPaste(std::function<void(const std::string&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<SearchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPaste(std::move(func));
}

RefPtr<FrameNode> SearchModelNG::CreateTextField(const RefPtr<SearchNode>& parentNode,
    const std::optional<std::string>& placeholder, const std::optional<std::string>& value)
{
    auto nodeId = parentNode->GetTextFieldId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    if (textFieldLayoutProperty) {
        if (value) {
            if (!textFieldLayoutProperty->HasLastValue() || textFieldLayoutProperty->GetLastValue() != value.value()) {
                pattern->InitEditingValueText(value.value());
                textFieldLayoutProperty->UpdateLastValue(value.value());
                textFieldLayoutProperty->UpdateValue(value.value());
            }
        }
        if (placeholder) {
            textFieldLayoutProperty->UpdatePlaceholder(placeholder.value());
        }
        textFieldLayoutProperty->UpdateMaxLines(1);
        textFieldLayoutProperty->UpdatePlaceholderMaxLines(1);
    }
    pattern->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    pattern->GetTextFieldController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    pattern->SetTextEditController(AceType::MakeRefPtr<TextEditController>());
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    renderContext->UpdateBackgroundColor(textFieldTheme->GetBgColor());
    auto radius = textFieldTheme->GetBorderRadius();
    auto textFieldPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    textFieldPaintProperty->UpdateCursorColor(textFieldTheme->GetCursorColor());
    PaddingProperty padding;
    padding.left = CalcLength(0.0);
    padding.right = CalcLength(0.0);
    textFieldLayoutProperty->UpdatePadding(padding);
    pattern->SetEnableTouchAndHoverEffect(false);
    return frameNode;
};

RefPtr<FrameNode> SearchModelNG::CreateImage(const RefPtr<SearchNode>& parentNode, const std::string& src)
{
    auto nodeId = parentNode->GetImageId();
    ImageSourceInfo imageSourceInfo(src);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(searchTheme, nullptr);
    if (src.empty()) {
        imageSourceInfo.SetResourceId(InternalResource::ResourceId::SEARCH_SVG);
        auto iconTheme = pipeline->GetTheme<IconTheme>();
        CHECK_NULL_RETURN(iconTheme, nullptr);
        auto iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::SEARCH_SVG);
        imageSourceInfo.SetSrc(iconPath, searchTheme->GetSearchIconColor());
    }
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    auto iconHeigth = searchTheme->GetIconHeight();
    CalcSize idealSize = { CalcLength(iconHeigth), CalcLength(iconHeigth) };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    layoutConstraint.maxSize = idealSize;
    frameNode->UpdateLayoutConstraint(layoutConstraint);
    return frameNode;
}

RefPtr<FrameNode> SearchModelNG::CreateCancelImage(const RefPtr<SearchNode>& parentNode)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto nodeId = parentNode->GetCancelImageId();
    ImageSourceInfo imageSourceInfo("");
    imageSourceInfo.SetResourceId(InternalResource::ResourceId::CLOSE_SVG);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    CHECK_NULL_RETURN(iconTheme, nullptr);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(searchTheme, nullptr);
    auto iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::CLOSE_SVG);
    imageSourceInfo.SetSrc(iconPath, searchTheme->GetSearchIconColor());
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    auto iconHeigth = searchTheme->GetIconHeight();
    CalcSize idealSize = { CalcLength(iconHeigth), CalcLength(iconHeigth) };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    layoutConstraint.maxSize = idealSize;
    frameNode->UpdateLayoutConstraint(layoutConstraint);
    return frameNode;
}

RefPtr<FrameNode> SearchModelNG::CreateButton(const RefPtr<SearchNode>& parentNode)
{
    auto nodeId = parentNode->GetButtonId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(frameNode, nullptr);
    if (frameNode->GetChildren().empty()) {
        auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_RETURN(textNode, nullptr);
        frameNode->AddChild(textNode);
    }
    return frameNode;
}

RefPtr<FrameNode> SearchModelNG::CreateCancelButton(const RefPtr<SearchNode>& parentNode)
{
    auto nodeId = parentNode->GetCancelButtonId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(frameNode, nullptr);
    if (frameNode->GetChildren().empty()) {
        auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_RETURN(textNode, nullptr);
        frameNode->AddChild(textNode);
    }
    return frameNode;
}

RefPtr<SearchNode> SearchModelNG::GetOrCreateSearchNode(
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
