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

#include "core/components_ng/pattern/text_field/text_field_model_ng.h"

#include <cstddef>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/ime/text_edit_controller.h"
#include "core/common/ime/text_input_type.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/components_ng/pattern/text_field/text_field_model_static.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
namespace {
const auto DEFAULT_KEYBOARD_APPERANCE = KeyboardAppearance::NONE_IMMERSIVE;
constexpr uint32_t MAX_LINES = 3;
constexpr double DEFAULT_OPACITY = 0.2;
constexpr int32_t DEFAULT_ALPHA = 255;
}

void TextFieldModelStatic::SetShowUnit(FrameNode* frameNode, std::function<RefPtr<UINode>()>&& builder)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    RefPtr<UINode> unitNode;
    if (builder) {
        unitNode = builder();
    }
    CHECK_NULL_VOID(unitNode);
    pattern->SetUnitNode(unitNode);
    pattern->ProcessResponseArea();
}

void TextFieldModelStatic::SetShowCounterBorder(FrameNode* frameNode, const std::optional<bool>& optValue)
{
    TextFieldModelNG::SetShowCounterBorder(frameNode, optValue.value_or(true));
}

void TextFieldModelStatic::SetBackgroundColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    NG::ViewAbstractModelStatic::SetBackgroundColor(frameNode, color);
    if (color) {
        TextFieldModelNG::SetBackgroundColor(frameNode, *color);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(TextFieldPaintProperty, BackgroundColor, frameNode);
    }
}

void TextFieldModelStatic::SetAdaptMinFontSize(FrameNode* frameNode, const std::optional<Dimension>& valueOpt)
{
    if (valueOpt) {
        TextFieldModelNG::SetAdaptMinFontSize(frameNode, valueOpt.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, AdaptMinFontSize, frameNode);
    }
}

void TextFieldModelStatic::SetAdaptMaxFontSize(FrameNode* frameNode, const std::optional<Dimension>& valueOpt)
{
    if (valueOpt) {
        TextFieldModelNG::SetAdaptMaxFontSize(frameNode, valueOpt.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, AdaptMaxFontSize, frameNode);
    }
}

void TextFieldModelStatic::SetHeightAdaptivePolicy(FrameNode* frameNode,
    const std::optional<TextHeightAdaptivePolicy>& valueOpt)
{
    if (valueOpt) {
        TextFieldModelNG::SetHeightAdaptivePolicy(frameNode, valueOpt.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, HeightAdaptivePolicy, frameNode);
    }
}

void TextFieldModelStatic::SetTextOverflow(FrameNode* frameNode, const std::optional<Ace::TextOverflow>& valueOpt)
{
    if (valueOpt) {
        TextFieldModelNG::SetTextOverflow(frameNode, valueOpt.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextOverflow, frameNode);
    }
}

void TextFieldModelStatic::SetTextIndent(FrameNode* frameNode, const std::optional<Dimension>& valueOpt)
{
    if (valueOpt) {
        TextFieldModelNG::SetTextIndent(frameNode, valueOpt.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextIndent, frameNode);
    }
}

void TextFieldModelStatic::SetInputStyle(FrameNode* frameNode, const std::optional<InputStyle>& valueOpt)
{
    if (valueOpt) {
        TextFieldModelNG::SetInputStyle(frameNode, valueOpt.value());
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(TextFieldPaintProperty, InputStyle, frameNode);
    }
}

void TextFieldModelStatic::SetBarState(FrameNode* frameNode, const std::optional<OHOS::Ace::DisplayMode>& valueOpt)
{
    if (valueOpt) {
        TextFieldModelNG::SetBarState(frameNode, valueOpt.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, DisplayMode, frameNode);
    }
}

void TextFieldModelStatic::SetPasswordIcon(FrameNode* frameNode, const std::optional<PasswordIcon>& passwordIconOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    // when not call SetPasswordIcon() and api >= 13, use symbol format image, else use image format.
    pattern->SetIsPasswordSymbol(false);
    PasswordIcon passwordIcon {};
    if (passwordIconOpt) {
        passwordIcon = passwordIconOpt.value();
    }
    if (passwordIcon.showResult != "") {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowPasswordSourceInfo,
            ImageSourceInfo(passwordIcon.showResult,
                passwordIcon.showBundleName, passwordIcon.showModuleName), frameNode);
    } else {
        ImageSourceInfo showSystemSourceInfo;
        showSystemSourceInfo.SetResourceId(InternalResource::ResourceId::SHOW_PASSWORD_SVG);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowPasswordSourceInfo,
            showSystemSourceInfo, frameNode);
    }
    if (passwordIcon.hideResult != "") {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, HidePasswordSourceInfo,
            ImageSourceInfo(passwordIcon.hideResult,
                passwordIcon.hideBundleName, passwordIcon.hideModuleName), frameNode);
    } else {
        ImageSourceInfo hideSystemSourceInfo;
        hideSystemSourceInfo.SetResourceId(InternalResource::ResourceId::HIDE_PASSWORD_SVG);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, HidePasswordSourceInfo,
            hideSystemSourceInfo, frameNode);
    }
}

void TextFieldModelStatic::SetSelectedBackgroundColor(FrameNode* frameNode, const std::optional<Color>& colorOpt)
{
    if (colorOpt) {
        auto selectedColor = colorOpt.value();
        // Alpha = 255 means opaque
        if (selectedColor.GetAlpha() == DEFAULT_ALPHA) {
            // Default setting of 20% opacity
            selectedColor = selectedColor.ChangeOpacity(DEFAULT_OPACITY);
        }
        TextFieldModelNG::SetSelectedBackgroundColor(frameNode, selectedColor);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(TextFieldPaintProperty, SelectedBackgroundColor, frameNode);
    }
}

void TextFieldModelStatic::SetMaxViewLines(FrameNode* frameNode, const std::optional<uint32_t>& valueOpt)
{
    if (valueOpt.has_value() && valueOpt.value() <= 0) {
        TextFieldModelNG::SetMaxViewLines(frameNode, MAX_LINES);
        return;
    }
    TextFieldModelNG::SetMaxViewLines(frameNode, valueOpt.value_or(MAX_LINES));
}

void TextFieldModelStatic::SetNormalMaxViewLines(FrameNode* frameNode, const std::optional<uint32_t>& valueOpt)
{
    TextFieldModelNG::SetNormalMaxViewLines(frameNode, valueOpt.value_or(Infinity<uint32_t>()));
}

void TextFieldModelStatic::SetType(FrameNode* frameNode, const std::optional<TextInputType>& valueOpt)
{
    if (valueOpt.has_value()) {
        TextFieldModelNG::SetType(frameNode, valueOpt.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->HasTextInputType() && layoutProperty->GetTextInputTypeValue() != TextInputType::UNSPECIFIED) {
        auto pattern = frameNode->GetPattern<TextFieldPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetIsFilterChanged(true);
        layoutProperty->UpdateTypeChanged(true);
    }
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextInputType, frameNode);
}

void TextFieldModelStatic::SetContentType(const FrameNode* frameNode, const std::optional<TextContentType>& valueOpt)
{
    if (valueOpt.has_value()) {
        TextFieldModelNG::SetContentType(frameNode, valueOpt.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->HasTextContentType() &&
        layoutProperty->GetTextContentTypeValue() != TextContentType::UNSPECIFIED) {
        layoutProperty->UpdateTextContentTypeChanged(true);
    }
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextContentType, frameNode);
}

void TextFieldModelStatic::SetCopyOption(FrameNode* frameNode,  const std::optional<CopyOptions>& copyOptionOpt)
{
    if (copyOptionOpt) {
        TextFieldModelNG::SetCopyOption(frameNode, copyOptionOpt.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, CopyOptions, frameNode);
    }
}

void TextFieldModelStatic::SetShowPassword(FrameNode* frameNode, const std::optional<bool>& valueOpt)
{
    if (valueOpt) {
        TextFieldModelNG::SetShowPassword(frameNode, valueOpt.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowPasswordText, frameNode);
    }
}

void TextFieldModelStatic::SetTextAlign(FrameNode* frameNode, const std::optional<TextAlign>& valueOpt)
{
    if (valueOpt.has_value()) {
        TextFieldModelNG::SetTextAlign(frameNode, valueOpt.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetTextAlignValue(TextAlign::START) != TextAlign::START) {
        layoutProperty->UpdateTextAlignChanged(true);
    }
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextAlign, frameNode);
}

void TextFieldModelStatic::SetTextColor(FrameNode* frameNode, const std::optional<Color>& colorOpt)
{
    if (colorOpt) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextColor, colorOpt.value(), frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, colorOpt.value(), frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, TextColorFlagByUser, colorOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(TextFieldLayoutProperty, TextColor,
            PROPERTY_UPDATE_MEASURE_SELF, frameNode);
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(TextFieldPaintProperty, TextColorFlagByUser,
            PROPERTY_UPDATE_MEASURE_SELF, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorFlag, frameNode);
    }
}

void TextFieldModelStatic::SetCaretPosition(FrameNode* frameNode, const std::optional<int32_t>& optValue)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCaretPosition(optValue.value_or(0));
}

void TextFieldModelStatic::SetFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& valueOpt)
{
    if (valueOpt.has_value()) {
        TextFieldModelNG::SetFontStyle(frameNode, valueOpt.value());
        return;
    }
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ItalicFontStyle, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PreferredTextLineHeightNeedToUpdate, true, frameNode);
}

void TextFieldModelStatic::SetCaretStyle(FrameNode* frameNode, const std::optional<CaretStyle>& valueOpt)
{
    if (valueOpt.has_value()) {
        TextFieldModelNG::SetCaretStyle(frameNode, valueOpt.value());
        return;
    }
    ACE_RESET_NODE_PAINT_PROPERTY(TextFieldPaintProperty, CursorWidth, frameNode);
}

void TextFieldModelStatic::SetPlaceholderColor(FrameNode* frameNode, const std::optional<Color>& colorOpt)
{
    if (colorOpt.has_value()) {
        TextFieldModelNG::SetPlaceholderColor(frameNode, colorOpt.value());
        return;
    }
    TextFieldModelNG::ResetPlaceholderColor(frameNode);
}

void TextFieldModelStatic::SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& valueOpt)
{
    if (valueOpt.has_value()) {
        TextFieldModelNG::SetFontWeight(frameNode, valueOpt.value());
        return;
    }
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, FontWeight, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PreferredTextLineHeightNeedToUpdate, true, frameNode);
}

void TextFieldModelStatic::SetUserUnderlineColor(FrameNode* frameNode,
    const std::optional<UserUnderlineColor>& userColor)
{
    auto pattern = AceType::DynamicCast<TextFieldPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->SetUserUnderlineColor(userColor.value_or(UserUnderlineColor()));
}

void TextFieldModelStatic::SetNormalUnderlineColor(FrameNode* frameNode, const std::optional<Color>& normalColor)
{
    TextFieldModelNG::SetNormalUnderlineColor(frameNode, normalColor.value_or(Color()));
}

void TextFieldModelStatic::SetEnterKeyType(FrameNode* frameNode, const std::optional<TextInputAction>& valueOpt)
{
    if (valueOpt.has_value()) {
        TextFieldModelNG::SetEnterKeyType(frameNode, valueOpt.value());
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto pattern = AceType::DynamicCast<TextFieldPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    TextInputAction defaultInputAction = pattern->IsTextArea() ? TextInputAction::NEW_LINE : TextInputAction::DONE;
    pattern->UpdateTextInputAction(defaultInputAction);
}

void TextFieldModelStatic::SetFontFamily(FrameNode* frameNode,
    const std::optional<std::vector<std::string>>& fontFamilies)
{
    if (fontFamilies.has_value()) {
        TextFieldModelNG::SetFontFamily(frameNode, fontFamilies.value());
        return;
    }
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, FontFamily, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PreferredTextLineHeightNeedToUpdate, true, frameNode);
}

void TextFieldModelStatic::SetPlaceholderFont(FrameNode* frameNode, const std::optional<Font>& valueOpt)
{
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    if (valueOpt && valueOpt.value().fontSize.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextFieldLayoutProperty, PlaceholderFontSize, valueOpt.value().fontSize.value(), frameNode);
    } else {
        if (textFieldLayoutProperty->GetPlaceholderFontStyle()) {
            textFieldLayoutProperty->GetPlaceholderFontStyle()->ResetFontSize();
        }
    }
    if (valueOpt && valueOpt.value().fontStyle) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextFieldLayoutProperty, PlaceholderItalicFontStyle, valueOpt.value().fontStyle.value(), frameNode);
    } else {
        if (textFieldLayoutProperty->GetPlaceholderFontStyle()) {
            textFieldLayoutProperty->GetPlaceholderFontStyle()->ResetItalicFontStyle();
        }
    }
    if (valueOpt && valueOpt.value().fontWeight) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextFieldLayoutProperty, PlaceholderFontWeight, valueOpt.value().fontWeight.value(), frameNode);
    } else {
        if (textFieldLayoutProperty->GetPlaceholderFontStyle()) {
            textFieldLayoutProperty->GetPlaceholderFontStyle()->ResetFontWeight();
        }
    }
    if (valueOpt && !valueOpt.value().fontFamilies.empty()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextFieldLayoutProperty, PlaceholderFontFamily, valueOpt.value().fontFamilies, frameNode);
    } else {
        if (textFieldLayoutProperty->GetPlaceholderFontStyle()) {
            textFieldLayoutProperty->GetPlaceholderFontStyle()->ResetFontFamily();
        }
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextFieldLayoutProperty, PreferredPlaceholderLineHeightNeedToUpdate, true, frameNode);
}

void TextFieldModelStatic::SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& valueOpt)
{
    if (valueOpt.has_value()) {
        TextFieldModelNG::SetFontSize(frameNode, valueOpt.value());
        return;
    }
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, FontSize, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PreferredTextLineHeightNeedToUpdate, true, frameNode);
}

void TextFieldModelStatic::SetCaretColor(FrameNode* frameNode, const std::optional<Color>& colorOpt)
{
    if (colorOpt) {
        TextFieldModelNG::SetCaretColor(frameNode, colorOpt.value());
    } else {
        TextFieldModelNG::ResetCaretColor(frameNode);
    }
}

void TextFieldModelStatic::SetPasswordRules(FrameNode* frameNode, const std::optional<std::string>& passwordRules)
{
    if (passwordRules) {
        TextFieldModelNG::SetPasswordRules(frameNode, passwordRules.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PasswordRules, frameNode);
    }
}

void TextFieldModelStatic::SetShowError(FrameNode* frameNode, const std::optional<std::u16string>& errorText,
    bool visible)
{
    if (errorText) {
        TextFieldModelNG::SetShowError(frameNode, errorText.value(), visible);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ErrorText, frameNode);
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowErrorText, frameNode);
    }
}

void TextFieldModelStatic::SetCounterType(FrameNode* frameNode, const std::optional<int32_t>& optValue)
{
    if (optValue) {
        TextFieldModelNG::SetCounterType(frameNode, optValue.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, SetCounter, frameNode);
    }
}

void TextFieldModelStatic::SetOnSecurityStateChange(FrameNode* frameNode, std::function<void(bool)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSecurityStateChange(std::move(func));
}

void TextFieldModelStatic::SetTextFieldText(FrameNode* frameNode, const std::optional<std::u16string>& optValue)
{
    TextFieldModelNG::SetTextFieldText(frameNode, optValue.value_or(u""));
}

void TextFieldModelStatic::SetTextFieldPlaceHolder(FrameNode* frameNode,
    const std::optional<std::u16string>& placeholder)
{
    if (placeholder) {
        TextFieldModelNG::SetTextFieldPlaceHolder(frameNode, placeholder.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, Placeholder, frameNode);
    }
}

void TextFieldModelStatic::SetOnPaste(FrameNode* frameNode, std::function<void(const std::u16string&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPaste(std::move(func));
}

void TextFieldModelStatic::SetOnChangeEvent(FrameNode* frameNode, std::function<void(const std::u16string&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(func));
}

void TextFieldModelStatic::SetCleanNodeStyle(FrameNode* frameNode, const std::optional<CleanNodeStyle>& cleanNodeStyle)
{
    TextFieldModelNG::SetCleanNodeStyle(frameNode, cleanNodeStyle.value_or(CleanNodeStyle::INPUT));
}

void TextFieldModelStatic::SetCancelIconSize(FrameNode* frameNode, const std::optional<CalcDimension>& iconSizeOpt)
{
    if (iconSizeOpt) {
        if (GreatOrEqual(iconSizeOpt.value().Value(), 0.0) && iconSizeOpt.value().Unit() != DimensionUnit::PERCENT) {
            TextFieldModelNG::SetCancelIconSize(frameNode, iconSizeOpt.value());
            return;
        }
    }
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto textFieldTheme = pattern->GetTheme();
    CHECK_NULL_VOID(textFieldTheme);
    TextFieldModelNG::SetCancelIconSize(frameNode, textFieldTheme->GetCancelIconSize());
}

void TextFieldModelStatic::SetCanacelIconSrc(FrameNode* frameNode,
    const std::string& iconSrc, const std::string& bundleName, const std::string& moduleName)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, IconSrc, iconSrc, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, BundleName, bundleName, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ModuleName, moduleName, frameNode);
}

void TextFieldModelStatic::SetCancelIconColor(FrameNode* frameNode, const std::optional<Color>& iconColor)
{
    if (iconColor) {
        TextFieldModelNG::SetCancelIconColor(frameNode, iconColor.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, IconColor, frameNode);
    }
}

void TextFieldModelStatic::SetTextDecoration(FrameNode* frameNode, const std::optional<TextDecoration>& valueOpt)
{
    if (valueOpt) {
        TextFieldModelNG::SetTextDecoration(frameNode, valueOpt.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextDecoration, frameNode);
    }
}

void TextFieldModelStatic::SetTextDecorationColor(FrameNode* frameNode, const std::optional<Color>& valueOpt)
{
    if (valueOpt) {
        TextFieldModelNG::SetTextDecorationColor(frameNode, valueOpt.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextDecorationColor, frameNode);
    }
}

void TextFieldModelStatic::SetTextDecorationStyle(FrameNode* frameNode,
    const std::optional<TextDecorationStyle>& valueOpt)
{
    if (valueOpt) {
        TextFieldModelNG::SetTextDecorationStyle(frameNode, valueOpt.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextDecorationStyle, frameNode);
    }
}

void TextFieldModelStatic::SetLetterSpacing(FrameNode* frameNode, const std::optional<Dimension>& valueOpt)
{
    if (valueOpt) {
        TextFieldModelNG::SetLetterSpacing(frameNode, valueOpt.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, LetterSpacing, frameNode);
    }
}

void TextFieldModelStatic::SetLineHeight(FrameNode* frameNode, const std::optional<Dimension>& valueOpt)
{
    if (valueOpt) {
        TextFieldModelNG::SetLineHeight(frameNode, valueOpt.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, LineHeight, frameNode);
    }
}

void TextFieldModelStatic::SetLineSpacing(FrameNode* frameNode, const std::optional<Dimension>& valueOpt)
{
    if (valueOpt) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, LineSpacing, valueOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, LineSpacing, frameNode);
    }
}

void TextFieldModelStatic::SetWordBreak(FrameNode* frameNode, const std::optional<Ace::WordBreak>& valueOpt)
{
    if (valueOpt) {
        TextFieldModelNG::SetWordBreak(frameNode, valueOpt.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, WordBreak, frameNode);
    }
}

void TextFieldModelStatic::SetLineBreakStrategy(FrameNode* frameNode, const std::optional<LineBreakStrategy>& valueOpt)
{
    if (valueOpt) {
        TextFieldModelNG::SetLineBreakStrategy(frameNode, valueOpt.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, LineBreakStrategy, frameNode);
    }
}

RefPtr<TextFieldControllerBase> TextFieldModelStatic::GetController(FrameNode* frameNode,
    const std::optional<std::u16string>& placeholder, const std::optional<std::u16string>& value)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);

    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, nullptr);
    textFieldLayoutProperty->UpdatePlaceholder(placeholder.value_or(u""));

    auto textValue = pattern->GetTextUtf16Value();
    if (value.has_value() && value.value() != textValue) {
        auto changed = pattern->InitValueText(value.value());
        pattern->SetTextChangedAtCreation(changed);
    }

    return pattern->GetTextFieldController();
}

void TextFieldModelStatic::SetStopBackPress(FrameNode* frameNode, const std::optional<bool>& isStopBackPress)
{
    TextFieldModelNG::SetStopBackPress(frameNode, isStopBackPress.value_or(true));
}

void TextFieldModelStatic::SetKeyboardAppearance(FrameNode* frameNode,
    const std::optional<KeyboardAppearance>& valueOpt)
{
    TextFieldModelNG::SetKeyboardAppearance(frameNode, valueOpt.value_or(DEFAULT_KEYBOARD_APPERANCE));
}

void TextFieldModelStatic::RequestKeyboardOnFocus(FrameNode* frameNode, const std::optional<bool>& needToRequest)
{
    TextFieldModelNG::RequestKeyboardOnFocus(frameNode, needToRequest.value_or(true));
}

void TextFieldModelStatic::SetSelectionMenuHidden(FrameNode* frameNode, const std::optional<bool>& selectionMenuHidden)
{
    TextFieldModelNG::SetSelectionMenuHidden(frameNode, selectionMenuHidden.value_or(false));
}

void TextFieldModelStatic::SetEnablePreviewText(FrameNode* frameNode, const std::optional<bool>& enablePreviewText)
{
    TextFieldModelNG::SetEnablePreviewText(frameNode, enablePreviewText.value_or(true));
}

void TextFieldModelStatic::SetEnableHapticFeedback(FrameNode* frameNode, const std::optional<bool>& state)
{
    TextFieldModelNG::SetEnableHapticFeedback(frameNode, state.value_or(true));
}

void TextFieldModelStatic::SetEnableAutoFill(FrameNode* frameNode, const std::optional<bool>& state)
{
    TextFieldModelNG::SetEnableAutoFill(frameNode, state.value_or(true));
}

void TextFieldModelStatic::SetEllipsisMode(FrameNode* frameNode, const std::optional<EllipsisMode>& optValue)
{
    if (optValue) {
        TextFieldModelNG::SetEllipsisMode(frameNode, optValue.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, EllipsisMode, frameNode);
    }
}

void TextFieldModelStatic::SetMinFontScale(FrameNode* frameNode, const std::optional<float>& optValue)
{
    if (optValue) {
        TextFieldModelNG::SetMinFontScale(frameNode, optValue.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, MinFontScale, frameNode);
    }
}

void TextFieldModelStatic::SetMaxFontScale(FrameNode* frameNode, const std::optional<float>& optValue)
{
    if (optValue) {
        TextFieldModelNG::SetMaxFontScale(frameNode, optValue.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, MaxFontScale, frameNode);
    }
}

void TextFieldModelStatic::SetHalfLeading(FrameNode* frameNode, const std::optional<bool>& valueOpt)
{
    if (valueOpt) {
        TextFieldModelNG::SetHalfLeading(frameNode, valueOpt.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, HalfLeading, frameNode);
    }
}

void TextFieldModelStatic::SetSelectionMenuOptions(FrameNode* frameNode,
    const NG::OnCreateMenuCallback&& onCreateMenuCallback, const NG::OnMenuItemClickCallback&& onMenuItemClick)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->OnSelectionMenuOptionsUpdate(std::move(onCreateMenuCallback), std::move(onMenuItemClick),
        nullptr);
}

void TextFieldModelStatic::SetShowPasswordIcon(FrameNode* frameNode, const std::optional<bool>& value)
{
    TextFieldModelNG::SetShowPasswordIcon(frameNode, value.value_or(true));
}

void TextFieldModelStatic::SetShowUnderline(FrameNode* frameNode, const std::optional<bool>& showUnderLine)
{
    TextFieldModelNG::SetShowUnderline(frameNode, showUnderLine.value_or(false));
}

void TextFieldModelStatic::SetSelectAllValue(FrameNode* frameNode, const std::optional<bool>& isSelectAllValue)
{
    TextFieldModelNG::SetSelectAllValue(frameNode, isSelectAllValue.value_or(false));
}

void TextFieldModelStatic::SetDefaultCancelIcon(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);

    CalcDimension iconSize = theme->GetCancelIconSize();
    Color color = theme->GetCancelButtonIconColor();
    std::string srcStr = "";

    TextFieldModelNG::SetCancelIconSize(frameNode, iconSize);
    TextFieldModelNG::SetCancelIconColor(frameNode, color);
    TextFieldModelNG::SetCanacelIconSrc(frameNode, srcStr);
}

void TextFieldModelStatic::SetWidthAuto(FrameNode* frameNode, bool val)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateWidthAuto(val);
}

void TextFieldModelStatic::SetPadding(FrameNode* frameNode, const NG::PaddingProperty& newPadding,
    bool tmp)
{
    CHECK_NULL_VOID(frameNode);
    if (tmp) {
        auto pattern = frameNode->GetPattern<TextFieldPattern>();
        CHECK_NULL_VOID(pattern);
        auto theme = pattern->GetTheme();
        CHECK_NULL_VOID(theme);
        auto themePadding = theme->GetPadding();
        PaddingProperty paddings;
        paddings.top = NG::CalcLength(themePadding.Top().ConvertToPx());
        paddings.bottom = NG::CalcLength(themePadding.Bottom().ConvertToPx());
        paddings.left = NG::CalcLength(themePadding.Left().ConvertToPx());
        paddings.right = NG::CalcLength(themePadding.Right().ConvertToPx());
        ViewAbstract::SetPadding(paddings);
        ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, PaddingByUser, paddings, frameNode);
        return;
    }
    NG::ViewAbstract::SetPadding(frameNode, newPadding);
    ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, PaddingByUser, newPadding, frameNode);
}

void TextFieldModelStatic::SetMargin(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    const auto& margin = layoutProperty->GetMarginProperty();
    CHECK_NULL_VOID(margin);
    bool isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;

    MarginProperty userMargin;
    userMargin.top = margin->top;
    userMargin.bottom = margin->bottom;
    userMargin.left = margin->left.has_value() ? margin->left :
        (isRTL ? margin->end : margin->start);
    userMargin.right = margin->right.has_value() ? margin->right :
        (isRTL ? margin->start : margin->end);
    ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, MarginByUser, userMargin, frameNode);
}

void TextFieldModelStatic::SetBackBorder(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderContext->HasBorderRadius()) {
        auto renderContext = frameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);

        bool isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
        auto radius = renderContext->GetBorderRadius().value();

        radius.radiusTopLeft = radius.radiusTopLeft.has_value() ? radius.radiusTopLeft :
            (isRTL ? radius.radiusTopEnd : radius.radiusTopStart);
        radius.radiusTopRight = radius.radiusTopRight.has_value() ? radius.radiusTopRight :
            (isRTL ? radius.radiusTopStart : radius.radiusTopEnd);
        radius.radiusBottomLeft = radius.radiusBottomLeft.has_value() ? radius.radiusBottomLeft :
            (isRTL ? radius.radiusBottomEnd : radius.radiusBottomStart);
        radius.radiusBottomRight = radius.radiusBottomRight.has_value() ? radius.radiusBottomRight :
            (isRTL ? radius.radiusBottomStart : radius.radiusBottomEnd);

        ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, BorderRadiusFlagByUser, radius, frameNode);
    }
    if (renderContext->HasBorderColor()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            TextFieldPaintProperty, BorderColorFlagByUser, renderContext->GetBorderColor().value(), frameNode);
    }
    if (renderContext->HasBorderWidth()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            TextFieldPaintProperty, BorderWidthFlagByUser, renderContext->GetBorderWidth().value(), frameNode);
    }
    if (renderContext->HasBorderStyle()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            TextFieldPaintProperty, BorderStyleFlagByUser, renderContext->GetBorderStyle().value(), frameNode);
    }
}
} // namespace OHOS::Ace::NG
