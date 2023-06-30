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
namespace {
constexpr int32_t TEXTFIELD_INDEX = 0;
constexpr int32_t IMAGE_INDEX = 1;
constexpr int32_t CANCEL_IMAGE_INDEX = 2;
constexpr int32_t CANCEL_BUTTON_INDEX = 3;
constexpr int32_t BUTTON_INDEX = 4;
} // namespace

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

    CreateTextField(frameNode, placeholder, value, hasTextFieldNode);

    std::string src;
    if (icon.has_value()) {
        src = icon.value();
    }
    CreateImage(frameNode, src, hasImageNode);
    CreateCancelImage(frameNode, hasCancelImageNode);
    CreateCancelButton(frameNode, hasCancelButtonNode);
    CreateButton(frameNode, hasButtonNode);

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
    pattern->UpdateChangeEvent(value.value_or(""));
    return pattern->GetSearchController();
}

void SearchModelNG::SetCaretWidth(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFrameNode);
    auto textPaintProperty = textFrameNode->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textPaintProperty);

    textPaintProperty->UpdateCursorWidth(value);
    textFrameNode->MarkModifyDone();
    textFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetCaretColor(const Color& color)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFrameNode);
    auto textPaintProperty = textFrameNode->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textPaintProperty);

    textPaintProperty->UpdateCursorColor(color);
    textFrameNode->MarkModifyDone();
    textFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetSearchButton(const std::string& text)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    CHECK_NULL_VOID(buttonFrameNode);

    auto searchButtonRenderContext = buttonFrameNode->GetRenderContext();
    CHECK_NULL_VOID(searchButtonRenderContext);

    auto searchButtonEvent = buttonFrameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(searchButtonEvent);

    if (!text.empty()) {
        searchButtonEvent->SetEnabled(true);
        searchButtonRenderContext->UpdateOpacity(1.0);
        ACE_UPDATE_LAYOUT_PROPERTY(SearchLayoutProperty, SearchButton, text);
    } else {
        searchButtonEvent->SetEnabled(false);
        searchButtonRenderContext->UpdateOpacity(0.0);
    }

    buttonFrameNode->MarkModifyDone();
    buttonFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetSearchIconSize(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    CHECK_NULL_VOID(imageFrameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(searchTheme);

    auto imageRenderContext = imageFrameNode->GetRenderContext();
    CHECK_NULL_VOID(imageRenderContext);
    auto imageOriginHeight = searchTheme->GetIconHeight().ConvertToPx();
    double imageScale = 0.0;
    if (!NearZero(imageOriginHeight)) {
        imageScale = value.ConvertToPx() / imageOriginHeight;
    }
    imageRenderContext->UpdateTransformScale(VectorF(imageScale, imageScale));

    imageFrameNode->MarkModifyDone();
    imageFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    ACE_UPDATE_LAYOUT_PROPERTY(SearchLayoutProperty, SearchIconUDSize, value);
}

void SearchModelNG::SetSearchIconColor(const Color& color)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    CHECK_NULL_VOID(imageFrameNode);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value();
    if (imageSourceInfo.IsSvg()) {
        imageSourceInfo.SetFillColor(color);
        imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);

        auto imageRenderProperty = imageFrameNode->GetPaintProperty<ImageRenderProperty>();
        CHECK_NULL_VOID(imageRenderProperty);
        imageRenderProperty->UpdateSvgFillColor(color);

        imageFrameNode->MarkModifyDone();
        imageFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void SearchModelNG::SetSearchSrcPath(const std::string& src)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    CHECK_NULL_VOID(imageFrameNode);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto iconTheme = pipeline->GetTheme<IconTheme>();

    auto imageRenderProperty = imageFrameNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(imageRenderProperty);
    auto color = imageRenderProperty->GetSvgFillColor();

    if (src.empty()) {
        imageSourceInfo.SetResourceId(InternalResource::ResourceId::SEARCH_SVG);
        auto iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::SEARCH_SVG);
        imageSourceInfo.SetSrc(iconPath, color);
    } else {
        imageSourceInfo.SetSrc(src, color);
    }
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imageFrameNode->MarkModifyDone();
    imageFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetRightIconSrcPath(const std::string& src)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    CHECK_NULL_VOID(imageFrameNode);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    auto imageRenderProperty = imageFrameNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(imageRenderProperty);
    auto color = imageRenderProperty->GetSvgFillColor();

    if (src.empty()) {
        imageSourceInfo.SetResourceId(InternalResource::ResourceId::CLOSE_SVG);
        auto iconTheme = pipeline->GetTheme<IconTheme>();
        auto iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::CLOSE_SVG);
        imageSourceInfo.SetSrc(iconPath, color);
    } else {
        imageSourceInfo.SetSrc(src, color);
    }
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imageFrameNode->MarkModifyDone();
    imageFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetCancelButtonStyle(CancelButtonStyle style)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto buttonHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    CHECK_NULL_VOID(buttonHost);
    auto imageHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    CHECK_NULL_VOID(imageHost);
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textHost);

    auto cancelButtonRenderContext = buttonHost->GetRenderContext();
    CHECK_NULL_VOID(cancelButtonRenderContext);
    auto cancelImageRenderContext = imageHost->GetRenderContext();
    CHECK_NULL_VOID(cancelImageRenderContext);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto cancelButtonEvent = buttonHost->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(cancelButtonEvent);
    auto imageEvent = imageHost->GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(imageEvent);

    if ((style == CancelButtonStyle::CONSTANT) ||
        ((style == CancelButtonStyle::INPUT) &&
          textLayoutProperty->HasValue() && !textLayoutProperty->GetValue()->empty())) {
        cancelButtonRenderContext->UpdateOpacity(1.0);
        cancelImageRenderContext->UpdateOpacity(1.0);
        cancelButtonEvent->SetEnabled(true);
        imageEvent->SetEnabled(true);
    } else {
        cancelButtonRenderContext->UpdateOpacity(0.0);
        cancelImageRenderContext->UpdateOpacity(0.0);
        cancelButtonEvent->SetEnabled(false);
        imageEvent->SetEnabled(false);
    }
    buttonHost->MarkModifyDone();
    imageHost->MarkModifyDone();
    buttonHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    imageHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    ACE_UPDATE_LAYOUT_PROPERTY(SearchLayoutProperty, CancelButtonStyle, style);
}

void SearchModelNG::SetCancelIconSize(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    CHECK_NULL_VOID(imageFrameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(searchTheme);
    auto imageRenderContext = imageFrameNode->GetRenderContext();
    CHECK_NULL_VOID(imageRenderContext);

    auto imageOriginHeight = searchTheme->GetIconHeight().ConvertToPx();
    double imageScale = 0.0;
    if (!NearZero(imageOriginHeight)) {
        imageScale = value.ConvertToPx() / imageOriginHeight;
    }
    imageRenderContext->UpdateTransformScale(VectorF(imageScale, imageScale));

    imageFrameNode->MarkModifyDone();
    imageFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    ACE_UPDATE_LAYOUT_PROPERTY(SearchLayoutProperty, CancelButtonUDSize, value);
}

void SearchModelNG::SetCancelIconColor(const Color& color)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    CHECK_NULL_VOID(imageFrameNode);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value();
    if (imageSourceInfo.IsSvg()) {
        imageSourceInfo.SetFillColor(color);
        imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);

        auto imageRenderProperty = imageFrameNode->GetPaintProperty<ImageRenderProperty>();
        CHECK_NULL_VOID(imageRenderProperty);
        imageRenderProperty->UpdateSvgFillColor(color);
        imageFrameNode->MarkModifyDone();
        imageFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void SearchModelNG::SetSearchButtonFontSize(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    CHECK_NULL_VOID(buttonFrameNode);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);

    buttonLayoutProperty->UpdateFontSize(value);
    buttonFrameNode->MarkModifyDone();
    buttonFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    ACE_UPDATE_LAYOUT_PROPERTY(SearchLayoutProperty, SearchButtonFontSize, value);
}

void SearchModelNG::SetSearchButtonFontColor(const Color& color)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    CHECK_NULL_VOID(buttonFrameNode);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);

    buttonLayoutProperty->UpdateFontColor(color);
    buttonFrameNode->MarkModifyDone();
    buttonFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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
    textFieldLayoutProperty->UpdatePreferredPlaceholderLineHeightNeedToUpdate(true);
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
    textFieldLayoutProperty->UpdatePreferredTextLineHeightNeedToUpdate(true);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetTextColor(const Color& color)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);

    textFieldLayoutProperty->UpdateTextColor(color);
    textFieldChild->MarkModifyDone();
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

void SearchModelNG::SetMenuOptionItems(std::vector<MenuOptionsParam>&& menuOptionsItems)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->SetMenuOptionItems(std::move(menuOptionsItems));
}

void SearchModelNG::SetHeight(const Dimension& height)
{
    NG::ViewAbstract::SetHeight(NG::CalcLength(height));
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

void SearchModelNG::SetOnTextSelectionChange(std::function<void(int32_t, int32_t)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<SearchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelectionChange(std::move(func));
}

void SearchModelNG::SetOnScroll(std::function<void(float, float)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<SearchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollChangeEvent(std::move(func));
}

void SearchModelNG::SetSelectionMenuHidden(bool selectionMenuHidden)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateSelectionMenuHidden(selectionMenuHidden);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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

void SearchModelNG::CreateTextField(const RefPtr<SearchNode>& parentNode,
    const std::optional<std::string>& placeholder, const std::optional<std::string>& value, bool hasTextFieldNode)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(searchTheme);
    auto nodeId = parentNode->GetTextFieldId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    auto textEditingValue = pattern->GetTextEditingValue();
    if (textFieldLayoutProperty) {
        if (value.has_value() && value.value() != textEditingValue.text) {
            pattern->InitEditingValueText(value.value());
        }
        textFieldLayoutProperty->UpdatePlaceholder(placeholder.value_or(""));
        textFieldLayoutProperty->UpdateMaxLines(1);
        textFieldLayoutProperty->UpdatePlaceholderMaxLines(1);
        textFieldLayoutProperty->UpdateTextColor(searchTheme->GetTextColor());
    }
    pattern->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    pattern->GetTextFieldController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    pattern->SetTextEditController(AceType::MakeRefPtr<TextEditController>());
    pattern->InitSurfaceChangedCallback();
    pattern->InitSurfacePositionChangedCallback();
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto renderContext = frameNode->GetRenderContext();
    renderContext->UpdateBackgroundColor(textFieldTheme->GetBgColor());
    auto textFieldPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    textFieldPaintProperty->UpdateCursorColor(textFieldTheme->GetCursorColor());
    textFieldPaintProperty->UpdateCursorWidth(textFieldTheme->GetCursorWidth());
    PaddingProperty padding;
    padding.left = CalcLength(0.0);
    padding.right = CalcLength(0.0);
    textFieldLayoutProperty->UpdatePadding(padding);
    pattern->SetEnableTouchAndHoverEffect(false);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    if (!hasTextFieldNode) {
        frameNode->MountToParent(parentNode);
    }
    frameNode->MarkModifyDone();
}

void SearchModelNG::CreateImage(const RefPtr<SearchNode>& parentNode, const std::string& src, bool hasImageNode)
{
    auto nodeId = parentNode->GetImageId();
    ImageSourceInfo imageSourceInfo(src);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(searchTheme);
    if (src.empty()) {
        imageSourceInfo.SetResourceId(InternalResource::ResourceId::SEARCH_SVG);
        auto iconTheme = pipeline->GetTheme<IconTheme>();
        CHECK_NULL_VOID(iconTheme);
        auto iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::SEARCH_SVG);
        imageSourceInfo.SetSrc(iconPath, searchTheme->GetSearchIconColor());
    }
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    auto iconHeight = searchTheme->GetIconHeight();
    CalcSize imageCalcSize((CalcLength(iconHeight)), CalcLength(iconHeight));
    imageLayoutProperty->UpdateUserDefinedIdealSize(imageCalcSize);

    if (!hasImageNode) {
        frameNode->MountToParent(parentNode);
        frameNode->MarkModifyDone();
    }
}

void SearchModelNG::RequestKeyboardOnFocus(bool needToRequest)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNeedToRequestKeyboardOnFocus(needToRequest);
}

void SearchModelNG::CreateCancelImage(const RefPtr<SearchNode>& parentNode, bool hasCancelImageNode)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto nodeId = parentNode->GetCancelImageId();
    ImageSourceInfo imageSourceInfo("");
    imageSourceInfo.SetResourceId(InternalResource::ResourceId::CLOSE_SVG);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    CHECK_NULL_VOID(iconTheme);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(searchTheme);
    auto iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::CLOSE_SVG);
    imageSourceInfo.SetSrc(iconPath, searchTheme->GetSearchIconColor());
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    auto iconHeight = searchTheme->GetIconHeight();
    CalcSize imageCalcSize((CalcLength(iconHeight)), CalcLength(iconHeight));
    imageLayoutProperty->UpdateUserDefinedIdealSize(imageCalcSize);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(imageRenderProperty);
    imageRenderProperty->UpdateSvgFillColor(searchTheme->GetSearchIconColor());

    if (!hasCancelImageNode) {
        frameNode->MountToParent(parentNode);
        auto cancelButtonEvent = frameNode->GetEventHub<ButtonEventHub>();
        CHECK_NULL_VOID(cancelButtonEvent);
        cancelButtonEvent->SetEnabled(false);
        frameNode->MarkModifyDone();
    }
}

void SearchModelNG::CreateButton(const RefPtr<SearchNode>& parentNode, bool hasButtonNode)
{
    if (hasButtonNode) {
        return;
    }

    auto searchTheme = PipelineBase::GetCurrentContext()->GetTheme<SearchTheme>();
    auto nodeId = parentNode->GetButtonId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetChildren().empty()) {
        auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_VOID(textNode);
        frameNode->AddChild(textNode);
    }

    auto buttonRenderContext = frameNode->GetRenderContext();
    buttonRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    std::string defaultText = "Search";
    textLayoutProperty->UpdateContent(defaultText);
    textLayoutProperty->UpdateTextColor(searchTheme->GetSearchButtonTextColor());
    textLayoutProperty->UpdateFontSize(searchTheme->GetFontSize());
    textLayoutProperty->UpdateMaxLines(1);

    PaddingProperty padding;
    padding.left = CalcLength(searchTheme->GetSearchButtonTextPadding());
    padding.right = CalcLength(searchTheme->GetSearchButtonTextPadding());
    textLayoutProperty->UpdatePadding(padding);

    auto searchButtonEvent = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(searchButtonEvent);
    searchButtonEvent->SetEnabled(false);
    frameNode->MountToParent(parentNode);
    frameNode->MarkModifyDone();
}

void SearchModelNG::CreateCancelButton(const RefPtr<SearchNode>& parentNode, bool hasCancelButtonNode)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(searchTheme);
    if (hasCancelButtonNode) {
        return;
    }
    auto nodeId = parentNode->GetCancelButtonId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetChildren().empty()) {
        auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_VOID(textNode);
        frameNode->AddChild(textNode);
    }
    auto cancelButtonRenderContext = frameNode->GetRenderContext();
    cancelButtonRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateFontSize(searchTheme->GetFontSize());
    auto cancelButtonLayoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    cancelButtonLayoutProperty->UpdateType(ButtonType::CIRCLE);
    auto cancelButtonEvent = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(cancelButtonEvent);
    cancelButtonEvent->SetEnabled(false);
    frameNode->MountToParent(parentNode);
    frameNode->MarkModifyDone();
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

void SearchModelNG::SetOnChangeEvent(std::function<void(const std::string&)>&& onChangeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SearchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChangeEvent));
}
} // namespace OHOS::Ace::NG
