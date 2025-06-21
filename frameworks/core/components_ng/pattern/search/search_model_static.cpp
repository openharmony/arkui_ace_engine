/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/search/search_model_static.h"

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
#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/search/search_text_field.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"

namespace OHOS::Ace::NG {
namespace {
const auto DEFAULT_KEYBOARD_APPERANCE = KeyboardAppearance::NONE_IMMERSIVE;
constexpr int32_t TEXTFIELD_INDEX = 0;
constexpr int32_t BUTTON_INDEX = 4;
constexpr double DEFAULT_OPACITY = 0.2;
constexpr int32_t DEFAULT_ALPHA = 255;
} // namespace

RefPtr<SearchTheme> SearchModelStatic::GetTheme(const FrameNode *frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetTheme<SearchTheme>();
}

void SearchModelStatic::SetTextIndent(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value.has_value()) {
        SearchModelNG::SetTextIndent(frameNode, value.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextIndent, textFieldChild);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::SetCustomKeyboard(FrameNode* frameNode,
    const std::function<void()>&& buildFunc, bool supportAvoidance)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();
    if (textFieldPattern) {
        textFieldPattern->SetCustomKeyboard(std::move(buildFunc));
        textFieldPattern->SetCustomKeyboardOption(supportAvoidance);
    }
}

void SearchModelStatic::SetPlaceholderFont(FrameNode* frameNode, const std::optional<Font>& font)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    if (font && font->fontSize) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PlaceholderFontSize,
            font->fontSize.value(), textFieldChild);
    } else {
        if (textFieldLayoutProperty->GetPlaceholderFontStyle()) {
            textFieldLayoutProperty->GetPlaceholderFontStyle()->ResetFontSize();
        }
    }
    if (font && font->fontStyle) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PlaceholderItalicFontStyle,
            font->fontStyle.value(), textFieldChild);
    } else {
        if (textFieldLayoutProperty->GetPlaceholderFontStyle()) {
            textFieldLayoutProperty->GetPlaceholderFontStyle()->ResetItalicFontStyle();
        }
    }
    if (font && font->fontWeight) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PlaceholderFontWeight,
            font->fontWeight.value(), textFieldChild);
    } else {
        if (textFieldLayoutProperty->GetPlaceholderFontStyle()) {
            textFieldLayoutProperty->GetPlaceholderFontStyle()->ResetFontWeight();
        }
    }
    if (font && !font->fontFamilies.empty()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PlaceholderFontFamily,
            font->fontFamilies, textFieldChild);
    } else {
        if (textFieldLayoutProperty->GetPlaceholderFontStyle()) {
            textFieldLayoutProperty->GetPlaceholderFontStyle()->ResetFontFamily();
        }
    }
    textFieldLayoutProperty->UpdatePreferredPlaceholderLineHeightNeedToUpdate(true);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::SetSearchDefaultIcon(FrameNode *frameNode)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->InitSearchIconColorSize();
    pattern->CreateSearchIcon("");
}

void SearchModelStatic::SetSearchImageIcon(FrameNode *frameNode, std::optional<IconOptions>& iconOptions)
{
    auto theme = SearchModelStatic::GetTheme(frameNode);
    CHECK_NULL_VOID(theme);
    if (iconOptions.has_value()) {
        if (!iconOptions.value().GetColor().has_value()) {
            iconOptions.value().UpdateColor(theme->GetSearchIconColor());
        }
        if (!iconOptions.value().GetSize().has_value()) {
            iconOptions.value().UpdateSize(theme->GetIconHeight());
        }
    } else {
        iconOptions = IconOptions(theme->GetSearchIconColor(), theme->GetIconHeight(), "", "", "");
    }
    SearchModelNG::SetSearchImageIcon(frameNode, iconOptions.value());
}

void SearchModelStatic::SetSearchButtonFontSize(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value.has_value()) {
        SearchModelNG::SetSearchButtonFontSize(frameNode, value.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    CHECK_NULL_VOID(buttonFrameNode);
    ACE_RESET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontSize, buttonFrameNode);
    ACE_RESET_NODE_LAYOUT_PROPERTY(SearchLayoutProperty, SearchButtonFontSize, frameNode);
    buttonFrameNode->MarkModifyDone();
    buttonFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::SetSearchButtonFontColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color.has_value()) {
        SearchModelNG::SetSearchButtonFontColor(frameNode, color.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    CHECK_NULL_VOID(buttonFrameNode);
    ACE_RESET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontColor, buttonFrameNode);
    buttonFrameNode->MarkModifyDone();
    buttonFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::SetSearchButtonAutoDisable(FrameNode* frameNode, const std::optional<bool>& needToDisable)
{
    SearchModelNG::SetSearchButtonAutoDisable(frameNode, needToDisable.value_or(false));
}

void SearchModelStatic::SetTextColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color.has_value()) {
        SearchModelNG::SetTextColor(frameNode, color.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    ACE_RESET_NODE_PAINT_PROPERTY(TextFieldPaintProperty, TextColorFlagByUser, textFieldChild);
    textFieldLayoutProperty->ResetTextColor();
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SearchModelStatic::SetCopyOption(FrameNode* frameNode,  const std::optional<CopyOptions>& copyOptionOpt)
{
    if (copyOptionOpt.has_value()) {
        SearchModelNG::SetCopyOption(frameNode, copyOptionOpt.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, CopyOptions, textFieldChild);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::SetTextFont(FrameNode* frameNode, const std::optional<Font>& font)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    if (font && font->fontSize) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, FontSize, font->fontSize.value(), textFieldChild);
    } else {
        if (textFieldLayoutProperty->GetFontStyle()) {
            textFieldLayoutProperty->GetFontStyle()->ResetFontSize();
        }
    }
    if (font && font->fontStyle) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ItalicFontStyle,
            font->fontStyle.value(), textFieldChild);
    } else {
        if (textFieldLayoutProperty->GetFontStyle()) {
            textFieldLayoutProperty->GetFontStyle()->ResetItalicFontStyle();
        }
    }
    if (font && font->fontWeight) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, FontWeight, font->fontWeight.value(), textFieldChild);
    } else {
        if (textFieldLayoutProperty->GetFontStyle()) {
            textFieldLayoutProperty->GetFontStyle()->ResetFontWeight();
        }
    }
    if (font && !font->fontFamilies.empty()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, FontFamily, font->fontFamilies, textFieldChild);
    } else {
        if (textFieldLayoutProperty->GetFontStyle()) {
            textFieldLayoutProperty->GetFontStyle()->ResetFontFamily();
        }
    }
    textFieldLayoutProperty->UpdatePreferredTextLineHeightNeedToUpdate(true);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::SetPlaceholderColor(FrameNode* frameNode, const std::optional<Color>& optColor)
{
    if (optColor.has_value()) {
        SearchModelNG::SetPlaceholderColor(frameNode, optColor.value());
        return;
    }
    TextFieldModelNG::ResetPlaceholderColor(frameNode);
}

void SearchModelStatic::SetCaretWidth(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value.has_value()) {
        SearchModelNG::SetCaretWidth(frameNode, value.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFrameNode);
    ACE_RESET_NODE_PAINT_PROPERTY(TextFieldPaintProperty, CursorWidth, textFrameNode);
    textFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::ResetCaretColor(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFrameNode);
    auto textPaintProperty = textFrameNode->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textPaintProperty);
    textPaintProperty->ResetCursorColor();
    textPaintProperty->ResetCaretColorFlagByUser();
    textFrameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SearchModelStatic::SetCaretColor(FrameNode* frameNode, const std::optional<Color>& optColor)
{
    if (optColor.has_value()) {
        SearchModelNG::SetCaretColor(frameNode, optColor.value());
        return;
    }
    SearchModelStatic::ResetCaretColor(frameNode);
}

void SearchModelStatic::SetTextAlign(FrameNode* frameNode, const std::optional<TextAlign>& valueOpt)
{
    if (valueOpt.has_value()) {
        SearchModelNG::SetTextAlign(frameNode, valueOpt.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateTextAlignChanged(true);
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextAlign, textFieldChild);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::SetCancelDefaultIcon(FrameNode* frameNode)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SearchPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->InitCancelIconColorSize();
    pattern->CreateCancelIcon();
}

void SearchModelStatic::SetCancelButtonStyle(FrameNode* frameNode, const std::optional<CancelButtonStyle>& style)
{
    if (style.has_value()) {
        SearchModelNG::SetCancelButtonStyle(frameNode, style.value());
        return;
    }
    ACE_RESET_NODE_LAYOUT_PROPERTY(SearchLayoutProperty, CancelButtonStyle, frameNode);
}

void SearchModelStatic::SetCancelImageIcon(FrameNode *frameNode, std::optional<NG::IconOptions>& iconOptions)
{
    auto theme = SearchModelStatic::GetTheme(frameNode);
    CHECK_NULL_VOID(theme);
    if (iconOptions.has_value()) {
        if (!iconOptions.value().GetColor().has_value()) {
            iconOptions.value().UpdateColor(theme->GetSearchIconColor());
        }
        if (!iconOptions.value().GetSize().has_value()) {
            iconOptions.value().UpdateSize(theme->GetIconHeight());
        }
    } else {
        iconOptions = IconOptions(theme->GetSearchIconColor(), theme->GetIconHeight(), "", "", "");
    }
    SearchModelNG::SetCancelImageIcon(frameNode, iconOptions.value());
}

void SearchModelStatic::SetSearchEnterKeyType(FrameNode* frameNode, const std::optional<TextInputAction>& valueOpt)
{
    if (valueOpt.has_value()) {
        SearchModelNG::SetSearchEnterKeyType(frameNode, valueOpt.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateTextInputAction(TextInputAction::SEARCH);
}

void SearchModelStatic::SetMinFontScale(FrameNode* frameNode, const std::optional<float>& valueOpt)
{
    if (valueOpt.has_value()) {
        SearchModelNG::SetMinFontScale(frameNode, valueOpt.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->ResetMinFontScale();
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::SetMaxFontScale(FrameNode* frameNode, const std::optional<float>& valueOpt)
{
    if (valueOpt.has_value()) {
        SearchModelNG::SetMaxFontScale(frameNode, valueOpt.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->ResetMaxFontScale();
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::SetAdaptMinFontSize(FrameNode* frameNode, const std::optional<Dimension>& valueOpt)
{
    if (valueOpt.has_value()) {
        SearchModelNG::SetAdaptMinFontSize(frameNode, valueOpt.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, AdaptMinFontSize, textFieldChild);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::SetAdaptMaxFontSize(FrameNode* frameNode, const std::optional<Dimension>& valueOpt)
{
    if (valueOpt.has_value()) {
        SearchModelNG::SetAdaptMaxFontSize(frameNode, valueOpt.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, AdaptMaxFontSize, textFieldChild);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::SetLetterSpacing(FrameNode* frameNode, const std::optional<Dimension>& valueOpt)
{
    if (valueOpt.has_value()) {
        SearchModelNG::SetLetterSpacing(frameNode, valueOpt.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, LetterSpacing, textFieldChild);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::SetLineHeight(FrameNode* frameNode, const std::optional<Dimension>& valueOpt)
{
    if (valueOpt.has_value()) {
        SearchModelNG::SetLineHeight(frameNode, valueOpt.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, LineHeight, textFieldChild);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::SetHalfLeading(FrameNode* frameNode, const std::optional<bool>& valueOpt)
{
    if (valueOpt.has_value()) {
        SearchModelNG::SetHalfLeading(frameNode, valueOpt.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->ResetHalfLeading();
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::SetTextDecoration(FrameNode* frameNode, const std::optional<Ace::TextDecoration>& valueOpt)
{
    if (valueOpt.has_value()) {
        SearchModelNG::SetTextDecoration(frameNode, valueOpt.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextDecoration, textFieldChild);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::SetTextDecorationColor(FrameNode* frameNode, const std::optional<Color>& valueOpt)
{
    if (valueOpt.has_value()) {
        SearchModelNG::SetTextDecorationColor(frameNode, valueOpt.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextDecorationColor, textFieldChild);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::SetSelectedBackgroundColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    if (value.has_value()) {
        auto selectedColor = value.value();
        if (selectedColor.GetAlpha() == DEFAULT_ALPHA) {
            // Default setting of 20% opacity
            selectedColor = selectedColor.ChangeOpacity(DEFAULT_OPACITY);
        }
        SearchModelNG::SetSelectedBackgroundColor(frameNode, selectedColor);
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldPaintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();
    ACE_RESET_NODE_PAINT_PROPERTY(TextFieldPaintProperty, SelectedBackgroundColor, textFieldChild);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SearchModelStatic::SetTextDecorationStyle(FrameNode* frameNode,
    const std::optional<Ace::TextDecorationStyle>& valueOpt)
{
    if (valueOpt.has_value()) {
        SearchModelNG::SetTextDecorationStyle(frameNode, valueOpt.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextDecorationStyle, textFieldChild);
    textFieldChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::SetType(FrameNode* frameNode, const std::optional<TextInputType>& valueOpt)
{
    if (valueOpt.has_value()) {
        SearchModelNG::SetType(frameNode, valueOpt.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFieldHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldHost);
    auto layoutProperty = textFieldHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->HasTextInputType() && layoutProperty->GetTextInputTypeValue() != TextInputType::UNSPECIFIED) {
        layoutProperty->UpdateTypeChanged(true);
        auto pattern = textFieldHost->GetPattern<TextFieldPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetIsFilterChanged(true);
    }
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextInputType, textFieldHost);
    textFieldHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SearchModelStatic::SetStopBackPress(FrameNode* frameNode, const std::optional<bool>& isStopBackPress)
{
    if (isStopBackPress.has_value()) {
        SearchModelNG::SetStopBackPress(frameNode, isStopBackPress.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, StopBackPress, textFieldChild);
}

void SearchModelStatic::SetKeyboardAppearance(FrameNode* frameNode, const std::optional<KeyboardAppearance>& valueOpt)
{
    SearchModelNG::SetKeyboardAppearance(frameNode, valueOpt.value_or(DEFAULT_KEYBOARD_APPERANCE));
}

void SearchModelStatic::SetSelectionMenuOptions(FrameNode* frameNode,
    const NG::OnCreateMenuCallback&& onCreateMenuCallback, const NG::OnMenuItemClickCallback&& onMenuItemClick)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldChild);
    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->OnSelectionMenuOptionsUpdate(std::move(onCreateMenuCallback), std::move(onMenuItemClick),
        nullptr);
}

void SearchModelStatic::RequestKeyboardOnFocus(FrameNode* frameNode, std::optional<bool>& needToRequest)
{
    SearchModelNG::RequestKeyboardOnFocus(frameNode, needToRequest.value_or(true));
}

void SearchModelStatic::SetSelectionMenuHidden(FrameNode* frameNode, std::optional<bool>& selectionMenuHidden)
{
    SearchModelNG::SetSelectionMenuHidden(frameNode, selectionMenuHidden.value_or(false));
}

void SearchModelStatic::SetEnablePreviewText(FrameNode* frameNode, std::optional<bool>& enablePreviewText)
{
    SearchModelNG::SetEnablePreviewText(frameNode, enablePreviewText.value_or(true));
}

void SearchModelStatic::SetEnableHapticFeedback(FrameNode* frameNode, std::optional<bool>& state)
{
    SearchModelNG::SetEnableHapticFeedback(frameNode, state.value_or(true));
}

void SearchModelStatic::SetOnChangeEvent(FrameNode* frameNode,
    std::function<void(const std::u16string&)>&& onChangeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto searchTextField = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
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
} // namespace OHOS::Ace::NG
