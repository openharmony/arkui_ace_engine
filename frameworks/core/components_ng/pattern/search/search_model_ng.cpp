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

#include "base/utils/utf_helper.h"
#include "base/utils/utils.h"
#include "core/common/udmf/udmf_client.h"
#include "core/components/common/properties/color.h"
#include "core/components/search/search_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/search/search_text_field.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEXTFIELD_INDEX = 0;
constexpr int32_t IMAGE_INDEX = 1;
constexpr int32_t CANCEL_IMAGE_INDEX = 2;
constexpr int32_t CANCEL_BUTTON_INDEX = 3;
constexpr int32_t BUTTON_INDEX = 4;
constexpr int32_t DIVIDER_INDEX = 5;
constexpr float MAX_FONT_SCALE = 2.0f;
const std::string INSPECTOR_PREFIX = "__SearchField__";
const std::vector<std::string> SPECICALIZED_INSPECTOR_INDEXS = { "", "Image__", "CancelImage__", "CancelButton__",
    "Button__", "Divider__" };
const std::string DROP_TYPE_STYLED_STRING = "ApplicationDefinedType";
constexpr Dimension ICON_HEIGHT = 16.0_vp;

void UpdateInnerInspector(FrameNode* frameNode, const std::string& key)
{
    auto updateInspectorCallback = [id = key](FrameNode* parentNode, int32_t index) {
        auto currentNode = AceType::DynamicCast<FrameNode>(parentNode->GetChildAtIndex(index));
        if (currentNode) {
            auto test = INSPECTOR_PREFIX + SPECICALIZED_INSPECTOR_INDEXS[index] + id;
            currentNode->UpdateInspectorId(INSPECTOR_PREFIX + SPECICALIZED_INSPECTOR_INDEXS[index] + id);
        }
    };
    updateInspectorCallback(frameNode, TEXTFIELD_INDEX);
    updateInspectorCallback(frameNode, IMAGE_INDEX);
    updateInspectorCallback(frameNode, CANCEL_IMAGE_INDEX);
    updateInspectorCallback(frameNode, CANCEL_BUTTON_INDEX);
    updateInspectorCallback(frameNode, BUTTON_INDEX);
    updateInspectorCallback(frameNode, DIVIDER_INDEX);
}
} // namespace

RefPtr<TextFieldControllerBase> SearchModelNG::Create(const std::optional<std::u16string>& value,
    const std::optional<std::u16string>& placeholder, const std::optional<std::string>& icon)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::SEARCH_ETS_TAG, nodeId);
    auto searchNode = CreateSearchNode(nodeId, value, placeholder, icon);
    ViewStackProcessor::GetInstance()->Push(searchNode);
    auto pattern = searchNode->GetPattern<SearchPattern>();

    return pattern->GetSearchController();
}

RefPtr<SearchTheme> SearchModelNG::GetTheme(const RefPtr<SearchNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(searchTheme, nullptr);
    return searchTheme;
}

void SearchModelNG::UpdateSearchNodeBorderProps(const RefPtr<SearchNode>& frameNode,
    const RefPtr<SearchTheme>& searchTheme)
{
    CHECK_NULL_VOID(searchTheme);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (searchTheme->GetCancelButtonStyle() != CancelButtonStyle::INPUT) {
        layoutProperty->UpdateCancelButtonStyle(searchTheme->GetCancelButtonStyle());
    }
    if (!layoutProperty->GetBorderWidthProperty()) {
        if (!renderContext->HasBorderWidth()) {
            BorderWidthProperty borderWidth;
            borderWidth.SetBorderWidth(searchTheme->GetBorderWidth());
            layoutProperty->UpdateBorderWidth(borderWidth);
        }
        if (!renderContext->HasBorderColor()) {
            BorderColorProperty borderColor;
            borderColor.SetColor(searchTheme->GetBorderColor());
            renderContext->UpdateBorderColor(borderColor);
        }
    }
}

RefPtr<SearchNode> SearchModelNG::CreateSearchNode(int32_t nodeId, const std::optional<std::u16string>& value,
    const std::optional<std::u16string>& placeholder, const std::optional<std::string>& icon)
{
    auto frameNode =
        GetOrCreateSearchNode(V2::SEARCH_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SearchPattern>(); });

    auto pattern = frameNode->GetPattern<SearchPattern>();
    pattern->SetSearchNode(frameNode);

    bool hasTextFieldNode = frameNode->HasTextFieldNode();
    bool hasButtonNode = frameNode->HasButtonNode();
    bool hasCancelButtonNode = frameNode->HasCancelButtonNode();
    bool hasDividerNode = frameNode->HasDividerNode();
    auto searchTheme = GetTheme(frameNode);
    CreateTextField(frameNode, placeholder, value, hasTextFieldNode, searchTheme);

    std::string src;
    if (icon.has_value()) {
        src = icon.value();
    }
    pattern->InitIconColorSize();
    pattern->CreateSearchIcon(src);
    pattern->CreateCancelIcon();
    CreateCancelButton(frameNode, hasCancelButtonNode, searchTheme);
    CreateButton(frameNode, hasButtonNode, searchTheme);
    CreateDivider(frameNode, hasDividerNode);

    // Set search background
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, frameNode);
    auto textFieldTheme = context->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, frameNode);
    auto radius = textFieldTheme->GetBorderRadius();
    BorderRadiusProperty borderRadius { radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() };
    renderContext->UpdateBorderRadius(borderRadius);

    UpdateSearchNodeBorderProps(frameNode, searchTheme);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_RETURN(textFieldFrameNode, frameNode);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, frameNode);
    pattern->SetSearchController(textFieldPattern->GetTextFieldController());
    pattern->UpdateChangeEvent(textFieldPattern->GetTextUtf16Value());

    return frameNode;
}

void SearchModelNG::SetDragPreviewOptions(const NG::DragPreviewOption option)
{
    auto searchTextField = GetSearchTextFieldFrameNode();
    CHECK_NULL_VOID(searchTextField);
    searchTextField->SetDragPreviewOptions(option);
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
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
            ACE_RESET_LAYOUT_PROPERTY(SearchLayoutProperty, SearchButton);
        }
    }

    buttonFrameNode->MarkModifyDone();
    buttonFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetSearchIconSize(const Dimension& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSearchIconSize(value);
    ACE_UPDATE_LAYOUT_PROPERTY(SearchLayoutProperty, SearchIconUDSize, value);
}

void SearchModelNG::SetSearchIconColor(const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSearchIconColor(color);
}

void SearchModelNG::SetSearchSrcPath(
    const std::string& src, const std::string& bundleName, const std::string& moduleName)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSearchSrcPath(src, bundleName, moduleName);
}

void SearchModelNG::SetSearchDefaultIcon()
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->InitSearchIconColorSize();
    pattern->CreateSearchIcon("");
}

void SearchModelNG::SetSearchImageIcon(IconOptions &iconOptions)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSearchImageIcon(iconOptions);
    ACE_UPDATE_LAYOUT_PROPERTY(
        SearchLayoutProperty, SearchIconUDSize, pattern->ConvertImageIconSizeValue(iconOptions.GetSize().value()));
}

void SearchModelNG::SetSearchSymbolIcon(std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->SetSearchIconSymbol(iconSymbol);
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSearchSymbolIcon();
}

void SearchModelNG::SetRightIconSrcPath(const std::string& src)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetRightIconSrcPath(src);
}

void SearchModelNG::SetCancelButtonStyle(CancelButtonStyle style)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCancelButtonStyle(style);
    ACE_UPDATE_LAYOUT_PROPERTY(SearchLayoutProperty, CancelButtonStyle, style);
}

void SearchModelNG::SetCancelIconSize(const Dimension& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCancelIconSize(value);
    ACE_UPDATE_LAYOUT_PROPERTY(SearchLayoutProperty, CancelButtonUDSize, value);
}

void SearchModelNG::SetCancelIconColor(const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCancelIconColor(color);
}

void SearchModelNG::SetCancelDefaultIcon()
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->InitCancelIconColorSize();
    pattern->CreateCancelIcon();
}

void SearchModelNG::SetCancelImageIcon(IconOptions &iconOptions)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCancelImageIcon(iconOptions);
    ACE_UPDATE_LAYOUT_PROPERTY(
        SearchLayoutProperty, CancelButtonUDSize, pattern->ConvertImageIconSizeValue(iconOptions.GetSize().value()));
}

void SearchModelNG::SetCancelSymbolIcon(std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->SetCancelIconSymbol(iconSymbol);
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCancelSymbolIcon();
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

void SearchModelNG::SetSearchButtonAutoDisable(bool needToDisable)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    CHECK_NULL_VOID(buttonFrameNode);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    buttonLayoutProperty->UpdateAutoDisable(needToDisable);
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

void SearchModelNG::SetSelectedBackgroundColor(const Color& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldPaintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textFieldPaintProperty);
    textFieldPaintProperty->UpdateSelectedBackgroundColor(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetInputFilter(
    FrameNode* frameNode, const std::string& value, const std::function<void(const std::u16string&)>& onError)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateInputFilter(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(textFieldEventHub);
    textFieldEventHub->SetOnInputFilterError(onError);
}

void SearchModelNG::SetInputFilter(const std::string& value, const std::function<void(const std::u16string&)>& onError)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateInputFilter(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(textFieldEventHub);
    textFieldEventHub->SetOnInputFilterError(onError);
}

void SearchModelNG::SetOnEditChanged(std::function<void(bool)>&& func)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(textFieldEventHub);
    textFieldEventHub->SetOnEditChanged(std::move(func));
}

void SearchModelNG::SetTextIndent(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateTextIndent(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetTextIndent(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateTextIndent(value);
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
    if (textFieldLayoutProperty->GetTextAlignValue(TextAlign::START) != textAlign) {
        textFieldLayoutProperty->UpdateTextAlignChanged(true);
    }
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

void SearchModelNG::SetHeight(const Dimension& height)
{
    NG::ViewAbstract::SetHeight(NG::CalcLength(height));
}

void SearchModelNG::SetOnSubmit(std::function<void(const std::u16string&, NG::TextFieldCommonEvent&)>&& onSubmit)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SearchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSubmit(std::move(onSubmit));
}

void SearchModelNG::SetOnChange(std::function<void(const std::u16string&, PreviewText&)>&& onChange)
{
    auto searchTextField = GetSearchTextFieldFrameNode();
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    auto searchChangeFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)),
        onChange](const std::u16string& value, PreviewText& previewText) {
        if (onChange) {
            onChange(value, previewText);
        }
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto searchPattern = AceType::DynamicCast<SearchPattern>(pattern);
        CHECK_NULL_VOID(searchPattern);
        searchPattern->UpdateChangeEvent(value + previewText.value);
    };
    eventHub->SetOnChange(std::move(searchChangeFunc));
}

void SearchModelNG::SetOnTextSelectionChange(std::function<void(int32_t, int32_t)>&& func)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(textFieldEventHub);
    textFieldEventHub->SetOnSelectionChange(std::move(func));
}

void SearchModelNG::SetOnScroll(std::function<void(float, float)>&& func)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(textFieldEventHub);
    textFieldEventHub->SetOnScrollChangeEvent(std::move(func));
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

void SearchModelNG::SetOnCopy(std::function<void(const std::u16string&)>&& func)
{
    auto searchTextField = GetSearchTextFieldFrameNode();
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCopy(std::move(func));
}

void SearchModelNG::SetOnCut(std::function<void(const std::u16string&)>&& func)
{
    auto searchTextField = GetSearchTextFieldFrameNode();
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto searchPasteFunc = [weak = AceType::WeakClaim(AceType::RawPtr(searchTextField)), func](
                               const std::u16string& value) {
        if (func) {
            func(value);
        }
        auto node = weak.Upgrade();
        if (node) {
            node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    };
    eventHub->SetOnCut(std::move(searchPasteFunc));
}

void SearchModelNG::SetOnPasteWithEvent(std::function<void(const std::u16string&, NG::TextCommonEvent&)>&& func)
{
    auto searchTextField = GetSearchTextFieldFrameNode();
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto searchPasteFunc = [weak = AceType::WeakClaim(AceType::RawPtr(searchTextField)), func](
                               const std::u16string& value, NG::TextCommonEvent& info) {
        if (func) {
            func(value, info);
        }
        auto node = weak.Upgrade();
        if (node) {
            node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    };
    eventHub->SetOnPasteWithEvent(std::move(searchPasteFunc));
}

void SearchModelNG::SetOnWillInsertValueEvent(std::function<bool(const InsertValueInfo&)>&& func)
{
    auto searchTextField = GetSearchTextFieldFrameNode();
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillInsertValueEvent(std::move(func));
}

void SearchModelNG::SetOnDidInsertValueEvent(std::function<void(const InsertValueInfo&)>&& func)
{
    auto searchTextField = GetSearchTextFieldFrameNode();
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidInsertValueEvent(std::move(func));
}

void SearchModelNG::SetOnWillDeleteEvent(std::function<bool(const DeleteValueInfo&)>&& func)
{
    auto searchTextField = GetSearchTextFieldFrameNode();
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillDeleteEvent(std::move(func));
}

void SearchModelNG::SetOnDidDeleteEvent(std::function<void(const DeleteValueInfo&)>&& func)
{
    auto searchTextField = GetSearchTextFieldFrameNode();
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidDeleteEvent(std::move(func));
}

void SearchModelNG::SetSelectionMenuOptions(
    const NG::OnCreateMenuCallback&& onCreateMenuCallback, const NG::OnMenuItemClickCallback&& onMenuItemClick)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->OnSelectionMenuOptionsUpdate(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

void SearchModelNG::SetEnablePreviewText(bool enablePreviewText)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSupportPreviewText(enablePreviewText);
}

void SearchModelNG::SetEnableHapticFeedback(bool state)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetEnableHapticFeedback(state);
}

void SearchModelNG::SetOnPaste(std::function<void(const std::u16string&)>&& func)
{
    auto searchTextField = GetSearchTextFieldFrameNode();
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto searchPasteFunc = [weak = AceType::WeakClaim(AceType::RawPtr(searchTextField)), func](
                               const std::u16string& value) {
        if (func) {
            func(value);
        }
        auto node = weak.Upgrade();
        if (node) {
            node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    };
    eventHub->SetOnPaste(std::move(searchPasteFunc));
}

void SearchModelNG::SetCustomKeyboard(const std::function<void()>&& buildFunc, bool supportAvoidance)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();
    if (textFieldPattern) {
        textFieldPattern->SetCustomKeyboard(std::move(buildFunc));
        textFieldPattern->SetCustomKeyboardOption(supportAvoidance);
    }
}

void SearchModelNG::SetType(TextInputType value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldHost);
    auto layoutProperty = textFieldHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->HasTextInputType() && layoutProperty->GetTextInputTypeValue() != value) {
        layoutProperty->UpdateTypeChanged(true);
    }
    layoutProperty->UpdateTextInputType(value);
    textFieldHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::CreateTextField(const RefPtr<SearchNode>& parentNode,
    const std::optional<std::u16string>& placeholder, const std::optional<std::u16string>& value, bool hasTextFieldNode,
    const RefPtr<SearchTheme>& searchTheme)
{
    CHECK_NULL_VOID(searchTheme);
    auto nodeId = parentNode->GetTextFieldId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SEARCH_Field_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SearchTextFieldPattern>(); });
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    auto textFieldPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    std::set<std::string> allowDropSet({ DROP_TYPE_PLAIN_TEXT, DROP_TYPE_HYPERLINK, DROP_TYPE_STYLED_STRING });
    frameNode->SetAllowDrop(allowDropSet);
    auto parentInspector = parentNode->GetInspectorIdValue("");
    frameNode->UpdateInspectorId(INSPECTOR_PREFIX + SPECICALIZED_INSPECTOR_INDEXS[TEXTFIELD_INDEX] + parentInspector);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    auto textValue = pattern->GetTextUtf16Value();
    if (textFieldLayoutProperty) {
        if (value.has_value() && value.value() != textValue) {
            auto changed = pattern->InitValueText(value.value());
            pattern->SetTextChangedAtCreation(changed);
        }
        textFieldLayoutProperty->UpdatePlaceholder(placeholder.value_or(u""));
        textFieldLayoutProperty->UpdateMaxLines(1);
        textFieldLayoutProperty->UpdatePlaceholderMaxLines(1);
        if (!hasTextFieldNode) {
            textFieldLayoutProperty->UpdateTextColor(searchTheme->GetTextColor());
            textFieldLayoutProperty->UpdatePlaceholderTextColor(searchTheme->GetPlaceholderColor());
        }
    }
    pattern->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    pattern->GetTextFieldController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    pattern->SetTextEditController(AceType::MakeRefPtr<TextEditController>());
    pattern->InitSurfaceChangedCallback();
    pattern->RegisterWindowSizeCallback();
    pattern->SetTextFadeoutCapacity(true);
    pattern->InitSurfacePositionChangedCallback();
    auto colorMode = SystemProperties::GetColorMode();
    pattern->SetOriginCursorColor(colorMode == ColorMode::DARK ? Color(0x4DFFFFFF) : Color(0x4D000000));
    if (pipeline->GetHasPreviewTextOption()) {
        pattern->SetSupportPreviewText(pipeline->GetSupportPreviewText());
    }
    TextFieldUpdateContext(frameNode);
    if (!hasTextFieldNode) {
        auto pattern = parentNode->GetPattern<SearchPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetTextFieldNode(frameNode);
        frameNode->MountToParent(parentNode);
    }
    textFieldLayoutProperty->UpdateMaxFontScale(MAX_FONT_SCALE);
}

void SearchModelNG::TextFieldUpdateContext(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto textFieldPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textFieldPaintProperty);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);

    auto renderContext = frameNode->GetRenderContext();
    textFieldPaintProperty->UpdateCursorColor(textFieldTheme->GetCursorColor());
    textFieldPaintProperty->UpdateCursorWidth(textFieldTheme->GetCursorWidth());
    PaddingProperty padding({ CalcLength(0.0), CalcLength(0.0), CalcLength(0.0), CalcLength(0.0) });
    textFieldLayoutProperty->UpdatePadding(padding);
    BorderRadiusProperty borderRadius;
    textFieldPaintProperty->UpdateBorderRadiusFlagByUser(borderRadius);
    pattern->SetEnableTouchAndHoverEffect(true);
    textFieldPaintProperty->UpdateBackgroundColor(Color::TRANSPARENT);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
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

void SearchModelNG::CreateButton(const RefPtr<SearchNode>& parentNode, bool hasButtonNode,
    const RefPtr<SearchTheme>& searchTheme)
{
    if (hasButtonNode) {
        return;
    }
    CHECK_NULL_VOID(searchTheme);
    auto parentInspector = parentNode->GetInspectorIdValue("");
    auto nodeId = parentNode->GetButtonId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (frameNode->GetChildren().empty()) {
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_VOID(textNode);
        frameNode->AddChild(textNode);
    }

    auto buttonRenderContext = frameNode->GetRenderContext();
    buttonRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    buttonRenderContext->UpdateClipEdge(true);
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    CHECK_NULL_VOID(buttonPattern);
    buttonPattern->SetApplyShadow(false);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    std::u16string defaultText = u"Search";
    textLayoutProperty->UpdateContent(defaultText);
    textLayoutProperty->UpdateTextColor(searchTheme->GetSearchButtonTextColor());
    textLayoutProperty->UpdateFontSize(searchTheme->GetFontSize());
    textLayoutProperty->UpdateMaxFontScale(MAX_FONT_SCALE);
    textLayoutProperty->UpdateMaxLines(1);

    PaddingProperty padding;
    padding.left = CalcLength(searchTheme->GetSearchButtonTextPadding());
    padding.right = CalcLength(searchTheme->GetSearchButtonTextPadding());
    textLayoutProperty->UpdatePadding(padding);

    auto searchButtonEvent = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(searchButtonEvent);
    searchButtonEvent->SetEnabled(false);
    auto pattern = parentNode->GetPattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    frameNode->UpdateInspectorId(INSPECTOR_PREFIX + SPECICALIZED_INSPECTOR_INDEXS[BUTTON_INDEX] + parentInspector);
    pattern->SetButtonNode(frameNode);
    frameNode->MountToParent(parentNode);
    frameNode->MarkModifyDone();
}

void SearchModelNG::CreateDivider(const RefPtr<SearchNode>& parentNode, bool hasDividerNode)
{
    if (hasDividerNode) {
        return;
    }
    auto parentInspector = parentNode->GetInspectorIdValue("");
    auto nodeId = parentNode->GetDividerId();
    auto dividerNode = FrameNode::GetOrCreateFrameNode(
        V2::DIVIDER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<DividerPattern>(); });
    CHECK_NULL_VOID(dividerNode);

    auto pipeline = dividerNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(searchTheme);
    auto searchDividerColor = searchTheme->GetSearchDividerColor();
    auto dividerRenderProperty = dividerNode->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_VOID(dividerRenderProperty);
    dividerRenderProperty->UpdateDividerColor(searchDividerColor);
    auto searchDividerWidth = Dimension(searchTheme->GetSearchDividerWidth().ConvertToPx());
    auto dividerLayoutProperty = dividerNode->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_VOID(dividerLayoutProperty);
    dividerLayoutProperty->UpdateVertical(true);
    dividerLayoutProperty->UpdateStrokeWidth(searchDividerWidth);

    dividerNode->UpdateInspectorId(INSPECTOR_PREFIX + SPECICALIZED_INSPECTOR_INDEXS[DIVIDER_INDEX] + parentInspector);
    dividerNode->MountToParent(parentNode);
    dividerNode->MarkModifyDone();
}

void SearchModelNG::CreateCancelButton(const RefPtr<SearchNode>& parentNode, bool hasCancelButtonNode,
    const RefPtr<SearchTheme>& searchTheme)
{
    if (hasCancelButtonNode) {
        return;
    }
    CHECK_NULL_VOID(searchTheme);
    auto parentInspector = parentNode->GetInspectorIdValue("");
    auto nodeId = parentNode->GetCancelButtonId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (frameNode->GetChildren().empty()) {
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_VOID(textNode);
        frameNode->AddChild(textNode);
    }
    frameNode->UpdateInspectorId(INSPECTOR_PREFIX + SPECICALIZED_INSPECTOR_INDEXS[CANCEL_BUTTON_INDEX] +
        parentInspector);
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
    auto pattern = parentNode->GetPattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCancelButtonNode(frameNode);
    frameNode->MountToParent(parentNode);
    frameNode->MarkModifyDone();
}

void SearchModelNG::UpdateInspectorId(const std::string& key)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    UpdateInnerInspector(frameNode, key);
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

void SearchModelNG::SetOnChangeEvent(std::function<void(const std::u16string&)>&& onChangeEvent)
{
    auto searchTextField = GetSearchTextFieldFrameNode();
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    auto searchChangeFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), onChangeEvent](
                                const std::u16string& value) {
        if (onChangeEvent) {
            onChangeEvent(value);
        }
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto searchPattern = AceType::DynamicCast<SearchPattern>(pattern);
        CHECK_NULL_VOID(searchPattern);
        searchPattern->UpdateChangeEvent(value);
    };
    eventHub->SetOnChangeEvent(std::move(searchChangeFunc));
}

RefPtr<FrameNode> SearchModelNG::GetSearchTextFieldFrameNode() const
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_RETURN(textFieldChild, nullptr);
    return textFieldChild;
}

void SearchModelNG::SetSearchEnterKeyType(TextInputAction value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    if (value == TextInputAction::UNSPECIFIED) {
        value = TextInputAction::SEARCH;
    }
    pattern->UpdateTextInputAction(value);
}

void SearchModelNG::SetMaxLength(uint32_t value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateMaxLength(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::ResetMaxLength()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->ResetMaxLength();
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

RefPtr<SearchNode> SearchModelNG::CreateFrameNode(int32_t nodeId)
{
    auto searchNode = CreateSearchNode(nodeId, u"", u"", "");

    return searchNode;
}

void SearchModelNG::SetTextValue(FrameNode* frameNode, const std::optional<std::string>& value)
{
    CHECK_NULL_VOID(frameNode);
    auto searchNode = AceType::Claim(AceType::DynamicCast<SearchNode>(frameNode));
    if (!searchNode->HasTextFieldNode()) {
        return;
    }

    auto textField = FrameNode::GetFrameNode(V2::SEARCH_Field_ETS_TAG, searchNode->GetTextFieldId());
    CHECK_NULL_VOID(textField);
    auto textFieldLayoutProperty = textField->GetLayoutProperty<TextFieldLayoutProperty>();
    auto pattern = textField->GetPattern<TextFieldPattern>();
    auto textValue = pattern->GetTextUtf16Value();
    if (textFieldLayoutProperty) {
        if (value.has_value()) {
            auto u16Value = UtfUtils::Str8ToStr16(value.value());
            if (u16Value != textValue) {
                pattern->InitValueText(u16Value);
            }
        }
    }
}

void SearchModelNG::SetIcon(FrameNode* frameNode, const std::optional<std::string>& icon)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->CreateSearchIcon(icon.value_or(""), true);
}

void SearchModelNG::SetPlaceholder(FrameNode* frameNode, const std::optional<std::string>& placeholder)
{
    CHECK_NULL_VOID(frameNode);
    auto searchNode = AceType::Claim(AceType::DynamicCast<SearchNode>(frameNode));
    if (!searchNode->HasTextFieldNode()) {
        return;
    }

    auto textField = FrameNode::GetFrameNode(V2::SEARCH_Field_ETS_TAG, searchNode->GetTextFieldId());
    CHECK_NULL_VOID(textField);
    auto textFieldLayoutProperty = textField->GetLayoutProperty<TextFieldLayoutProperty>();
    if (textFieldLayoutProperty) {
        textFieldLayoutProperty->UpdatePlaceholder(UtfUtils::Str8ToStr16(placeholder.value_or("")));
    }
}

void SearchModelNG::SetCaretPosition(FrameNode* frameNode, const int32_t& value)
{
    CHECK_NULL_VOID(frameNode);
    auto searchNode = AceType::Claim(AceType::DynamicCast<SearchNode>(frameNode));
    auto pattern = searchNode->GetPattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    auto controller = pattern->GetSearchController();
    CHECK_NULL_VOID(controller);
    controller->CaretPosition(value);
}

void SearchModelNG::RequestKeyboardOnFocus(FrameNode* frameNode, bool needToRequest)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNeedToRequestKeyboardOnFocus(needToRequest);
}

void SearchModelNG::SetPlaceholderFont(FrameNode* frameNode, const Font& font)
{
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

void SearchModelNG::SetSearchIconSize(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSearchIconSize(value);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SearchLayoutProperty, SearchIconUDSize, value, frameNode);
}

void SearchModelNG::SetSearchSrcPath(FrameNode* frameNode, const std::string& src)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSearchSrcPath(src, "", "");
}

void SearchModelNG::SetSearchIconColor(FrameNode* frameNode, const Color& color)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSearchIconColor(color);
}

void SearchModelNG::SetSearchImageIcon(FrameNode *frameNode, IconOptions &iconOptions)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSearchImageIcon(iconOptions);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SearchLayoutProperty, SearchIconUDSize,
        pattern->ConvertImageIconSizeValue(iconOptions.GetSize().value_or(ICON_HEIGHT)), frameNode);
}

void SearchModelNG::SetSearchButton(FrameNode* frameNode, const std::string& text)
{
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
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SearchLayoutProperty, SearchButton, text, frameNode);
    } else {
        searchButtonEvent->SetEnabled(false);
        searchButtonRenderContext->UpdateOpacity(0.0);
    }

    buttonFrameNode->MarkModifyDone();
    buttonFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetSearchButtonFontSize(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    CHECK_NULL_VOID(buttonFrameNode);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);

    buttonLayoutProperty->UpdateFontSize(value);
    buttonFrameNode->MarkModifyDone();
    buttonFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SearchLayoutProperty, SearchButtonFontSize, value, frameNode);
}

void SearchModelNG::SetSearchButtonFontColor(FrameNode* frameNode, const Color& color)
{
    CHECK_NULL_VOID(frameNode);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    CHECK_NULL_VOID(buttonFrameNode);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);

    buttonLayoutProperty->UpdateFontColor(color);
    buttonFrameNode->MarkModifyDone();
    buttonFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetSearchButtonAutoDisable(FrameNode* frameNode, bool needToDisable)
{
    CHECK_NULL_VOID(frameNode);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    CHECK_NULL_VOID(buttonFrameNode);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    buttonLayoutProperty->UpdateAutoDisable(needToDisable);
    buttonFrameNode->MarkModifyDone();
    buttonFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetTextColor(FrameNode* frameNode, const Color& color)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, TextColorFlagByUser, color, textFieldChild);
    textFieldLayoutProperty->UpdateTextColor(color);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetCopyOption(FrameNode* frameNode, const CopyOptions& copyOptions)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateCopyOptions(copyOptions);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetTextFont(FrameNode* frameNode, const Font& font)
{
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

void SearchModelNG::SetPlaceholderColor(FrameNode* frameNode, const Color& color)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdatePlaceholderTextColor(color);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetSelectionMenuHidden(FrameNode* frameNode, bool selectionMenuHidden)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateSelectionMenuHidden(selectionMenuHidden);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetCaretWidth(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFrameNode);
    auto textPaintProperty = textFrameNode->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textPaintProperty);
    textPaintProperty->UpdateCursorWidth(value);
    textFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetCaretColor(FrameNode* frameNode, const Color& color)
{
    CHECK_NULL_VOID(frameNode);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFrameNode);
    auto textPaintProperty = textFrameNode->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textPaintProperty);
    textPaintProperty->UpdateCursorColor(color);
    textFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetTextAlign(FrameNode* frameNode, const TextAlign& textAlign)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    if (textFieldLayoutProperty->GetTextAlignValue(TextAlign::START) != textAlign) {
        textFieldLayoutProperty->UpdateTextAlignChanged(true);
    }
    textFieldLayoutProperty->UpdateTextAlign(textAlign);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetCancelButtonStyle(FrameNode* frameNode, CancelButtonStyle style)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetCancelButtonStyle(style);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SearchLayoutProperty, CancelButtonStyle, style, frameNode);
}

void SearchModelNG::SetCancelIconSize(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetCancelIconSize(value);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SearchLayoutProperty, CancelButtonUDSize, value, frameNode);
}

void SearchModelNG::SetCancelIconColor(FrameNode* frameNode, const Color& color)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetCancelIconColor(color);
}

void SearchModelNG::SetRightIconSrcPath(FrameNode* frameNode, const std::string& src)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetRightIconSrcPath(src);
}

void SearchModelNG::SetCancelImageIcon(FrameNode *frameNode, IconOptions &iconOptions)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetCancelImageIcon(iconOptions);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SearchLayoutProperty, CancelButtonUDSize,
        pattern->ConvertImageIconSizeValue(iconOptions.GetSize().value_or(ICON_HEIGHT)), frameNode);
}

void SearchModelNG::SetSearchEnterKeyType(FrameNode* frameNode, TextInputAction value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    if (value == TextInputAction::UNSPECIFIED) {
        value = TextInputAction::SEARCH;
    }
    pattern->UpdateTextInputAction(value);
}

void SearchModelNG::SetHeight(FrameNode* frameNode, const Dimension& height)
{
    NG::ViewAbstract::SetHeight(frameNode, NG::CalcLength(height));
}

void SearchModelNG::SetFontFeature(const FONT_FEATURES_LIST& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SearchLayoutProperty, FontFeature, value);
}

void SearchModelNG::SetFontFeature(FrameNode* frameNode, const FONT_FEATURES_LIST& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SearchLayoutProperty, FontFeature, value, frameNode);
}

void SearchModelNG::SetId(FrameNode* frameNode, const std::string& id)
{
    NG::ViewAbstract::SetInspectorId(frameNode, id);
    UpdateInnerInspector(frameNode, id);
}

void SearchModelNG::SetLetterSpacing(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateLetterSpacing(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetAdaptMinFontSize(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateAdaptMinFontSize(value);
    textFieldLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetAdaptMaxFontSize(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateAdaptMaxFontSize(value);
    textFieldLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetMinFontScale(const float value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateMinFontScale(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetMaxFontScale(const float value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateMaxFontScale(std::min(value, MAX_FONT_SCALE));
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetMinFontScale(FrameNode* frameNode, const float value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateMinFontScale(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetMaxFontScale(FrameNode* frameNode, const float value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateMaxFontScale(std::min(value, MAX_FONT_SCALE));
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetLineHeight(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateLineHeight(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetHalfLeading(bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateHalfLeading(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetAdaptMinFontSize(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateAdaptMinFontSize(value);
    textFieldLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetAdaptMaxFontSize(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateAdaptMaxFontSize(value);
    textFieldLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetLetterSpacing(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateLetterSpacing(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}
void SearchModelNG::SetLineHeight(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateLineHeight(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetHalfLeading(FrameNode* frameNode, const bool& value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateHalfLeading(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetTextDecoration(Ace::TextDecoration value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateTextDecoration(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetTextDecoration(FrameNode* frameNode, Ace::TextDecoration value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateTextDecoration(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetTextDecorationColor(const Color& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateTextDecorationColor(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetTextDecorationColor(FrameNode* frameNode, const Color& value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateTextDecorationColor(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetTextDecorationStyle(Ace::TextDecorationStyle value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateTextDecorationStyle(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetSelectedBackgroundColor(FrameNode* frameNode, const Color& value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldPaintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textFieldPaintProperty);
    textFieldPaintProperty->UpdateSelectedBackgroundColor(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SearchModelNG::SetTextDecorationStyle(FrameNode* frameNode, Ace::TextDecorationStyle value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateTextDecorationStyle(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetOnSubmit(
    FrameNode* frameNode, std::function<void(const std::u16string&, NG::TextFieldCommonEvent&)>&& onSubmit)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SearchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSubmit(std::move(onSubmit));
}

void SearchModelNG::SetOnChange(FrameNode* frameNode,
    std::function<void(const std::u16string&, PreviewText&)>&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto searchTextField = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    auto searchChangeFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)),
        onChange](const std::u16string& value, PreviewText& previewText) {
        if (onChange) {
            onChange(value, previewText);
        }
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto searchPattern = AceType::DynamicCast<SearchPattern>(pattern);
        CHECK_NULL_VOID(searchPattern);
        searchPattern->UpdateChangeEvent(value + previewText.value);
    };
    eventHub->SetOnChange(std::move(searchChangeFunc));
}

void SearchModelNG::SetOnCopy(FrameNode* frameNode, std::function<void(const std::u16string&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto searchTextField = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCopy(std::move(func));
}

void SearchModelNG::SetOnCut(FrameNode* frameNode, std::function<void(const std::u16string&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto searchTextField = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto searchPasteFunc = [weak = AceType::WeakClaim(AceType::RawPtr(searchTextField)), func](
                               const std::u16string& value) {
        if (func) {
            func(value);
        }
        auto node = weak.Upgrade();
        if (node) {
            node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    };
    eventHub->SetOnCut(std::move(searchPasteFunc));
}

void SearchModelNG::SetOnPasteWithEvent(FrameNode* frameNode,
    std::function<void(const std::u16string&, NG::TextCommonEvent&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto searchTextField = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto searchPasteFunc = [weak = AceType::WeakClaim(AceType::RawPtr(searchTextField)), func](
                               const std::u16string& value, NG::TextCommonEvent& info) {
        if (func) {
            func(value, info);
        }
        auto node = weak.Upgrade();
        if (node) {
            node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    };
    eventHub->SetOnPasteWithEvent(std::move(searchPasteFunc));
}

void SearchModelNG::SetMaxLength(FrameNode* frameNode, uint32_t value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateMaxLength(value);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::ResetMaxLength(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->ResetMaxLength();
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetType(FrameNode* frameNode, TextInputType value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldHost);
    auto layoutProperty = textFieldHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->HasTextInputType() && layoutProperty->GetTextInputTypeValue() != value) {
        layoutProperty->UpdateTypeChanged(true);
    }
    layoutProperty->UpdateTextInputType(value);
    textFieldHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetOnEditChange(FrameNode* frameNode, std::function<void(bool)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(textFieldEventHub);
    textFieldEventHub->SetOnEditChanged(std::move(func));
}

void SearchModelNG::SetOnTextSelectionChange(FrameNode* frameNode, std::function<void(int32_t, int32_t)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(textFieldEventHub);
    textFieldEventHub->SetOnSelectionChange(std::move(func));
}

void SearchModelNG::SetOnContentScroll(FrameNode* frameNode, std::function<void(float, float)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(textFieldEventHub);
    textFieldEventHub->SetOnScrollChangeEvent(std::move(func));
}

void SearchModelNG::SetShowCounter(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCounterState(false);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowCounter, value, textFieldChild);
}

void SearchModelNG::SetCounterType(FrameNode* frameNode, int32_t value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, SetCounter, value, textFieldChild);
}

void SearchModelNG::SetShowCounterBorder(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCounterState(false);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowHighlightBorder, value, textFieldChild);
}

RefPtr<TextFieldControllerBase> SearchModelNG::GetSearchController(FrameNode* frameNode)
{
    auto pattern = frameNode->GetPattern<SearchPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetSearchController();
}

void SearchModelNG::SetOnWillInsertValueEvent(FrameNode* frameNode, std::function<bool(const InsertValueInfo&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto searchTextField = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillInsertValueEvent(std::move(func));
}

void SearchModelNG::SetOnDidInsertValueEvent(FrameNode* frameNode, std::function<void(const InsertValueInfo&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto searchTextField = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidInsertValueEvent(std::move(func));
}

void SearchModelNG::SetOnWillDeleteEvent(FrameNode* frameNode, std::function<bool(const DeleteValueInfo&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto searchTextField = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillDeleteEvent(std::move(func));
}

void SearchModelNG::SetOnDidDeleteEvent(FrameNode* frameNode, std::function<void(const DeleteValueInfo&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto searchTextField = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidDeleteEvent(std::move(func));
}

void SearchModelNG::OnCreateMenuCallbackUpdate(
    FrameNode* frameNode, const NG::OnCreateMenuCallback&& onCreateMenuCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->OnCreateMenuCallbackUpdate(std::move(onCreateMenuCallback));
}

void SearchModelNG::OnMenuItemClickCallbackUpdate(
    FrameNode* frameNode, const NG::OnMenuItemClickCallback&& onMenuItemClick)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->OnMenuItemClickCallbackUpdate(std::move(onMenuItemClick));
}

void SearchModelNG::SetEnablePreviewText(FrameNode* frameNode, bool enablePreviewText)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSupportPreviewText(enablePreviewText);
}

void SearchModelNG::SetBackBorderRadius()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);

    bool isRTL = textFieldLayoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    auto radius = renderContext->GetBorderRadius().value();

    radius.radiusTopLeft = radius.radiusTopLeft.has_value() ? radius.radiusTopLeft :
        (isRTL ? radius.radiusTopEnd : radius.radiusTopStart);
    radius.radiusTopRight = radius.radiusTopRight.has_value() ? radius.radiusTopRight :
        (isRTL ? radius.radiusTopStart : radius.radiusTopEnd);
    radius.radiusBottomLeft = radius.radiusBottomLeft.has_value() ? radius.radiusBottomLeft :
        (isRTL ? radius.radiusBottomEnd : radius.radiusBottomStart);
    radius.radiusBottomRight = radius.radiusBottomRight.has_value() ? radius.radiusBottomRight :
        (isRTL ? radius.radiusBottomStart : radius.radiusBottomEnd);


    auto textFieldPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textFieldPaintProperty);
    textFieldPaintProperty->UpdateBorderRadiusFlagByUser(radius);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelNG::SetEnableHapticFeedback(FrameNode* frameNode, bool state)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetEnableHapticFeedback(state);
}

void SearchModelNG::SetStopBackPress(bool isStopBackPress)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, StopBackPress, isStopBackPress, textFieldChild);
}

void SearchModelNG::SetStopBackPress(FrameNode* frameNode, bool isStopBackPress)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, StopBackPress, isStopBackPress, textFieldChild);
}
} // namespace OHOS::Ace::NG
