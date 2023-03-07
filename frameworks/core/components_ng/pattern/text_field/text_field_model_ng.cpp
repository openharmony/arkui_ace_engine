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

#include "core/components_ng/pattern/text_field/text_field_model_ng.h"

#include <cstddef>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/ime/text_edit_controller.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void TextFieldModelNG::CreateNode(
    const std::optional<std::string>& placeholder, const std::optional<std::string>& value, bool isTextArea)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(isTextArea ? V2::TEXTAREA_ETS_TAG : V2::TEXTINPUT_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    stack->Push(frameNode);
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    auto textEditingValue = pattern->GetTextEditingValue();
    if (value.has_value() && value.value() != textEditingValue.text) {
        pattern->InitEditingValueText(value.value());
    }
    textFieldLayoutProperty->UpdatePlaceholder(placeholder.value_or(""));
    if (!isTextArea) {
        textFieldLayoutProperty->UpdateMaxLines(1);
        textFieldLayoutProperty->UpdatePlaceholderMaxLines(1);
    }
    pattern->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    pattern->GetTextFieldController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    pattern->SetTextEditController(AceType::MakeRefPtr<TextEditController>());
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (!pattern->HasSurfaceChangedCallback()) {
        auto callbackId = pipeline->RegisterSurfaceChangedCallback(
            [weakPattern = AceType::WeakClaim(AceType::RawPtr(pattern))](
                int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight) {
                auto pattern = weakPattern.Upgrade();
                if (pattern) {
                    pattern->HandleSurfaceChanged(newWidth, newHeight, prevWidth, prevHeight);
                }
            });
        LOGI("Add surface changed callback id %{public}d", callbackId);
        pattern->UpdateSurfaceChangedCallbackId(callbackId);
    }
    if (!pattern->HasSurfacePositionChangedCallback()) {
        auto callbackId = pipeline->RegisterSurfacePositionChangedCallback(
            [weakPattern = AceType::WeakClaim(AceType::RawPtr(pattern))](int32_t posX, int32_t posY) {
                auto pattern = weakPattern.Upgrade();
                if (pattern) {
                    pattern->HandleSurfacePositionChanged(posX, posY);
                }
            });
        LOGI("Add position changed callback id %{public}d", callbackId);
        pattern->UpdateSurfacePositionChangedCallbackId(callbackId);
    }
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto textfieldPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textfieldPaintProperty);
    textfieldPaintProperty->UpdateBackgroundColor(textFieldTheme->GetBgColor());
    textfieldPaintProperty->UpdatePressBgColor(textFieldTheme->GetPressColor());
    textfieldPaintProperty->UpdateHoverBgColor(textFieldTheme->GetHoverColor());
    auto renderContext = frameNode->GetRenderContext();
    renderContext->UpdateBackgroundColor(textFieldTheme->GetBgColor());
    auto radius = textFieldTheme->GetBorderRadius();
    SetCaretColor(textFieldTheme->GetCursorColor());
    BorderRadiusProperty borderRadius { radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() };
    renderContext->UpdateBorderRadius(borderRadius);
    textFieldLayoutProperty->UpdateCopyOptions(CopyOptions::Distributed);
    PaddingProperty paddings;
    ProcessDefaultPadding(paddings);
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Padding, paddings);
}

void TextFieldModelNG::ProcessDefaultPadding(PaddingProperty& paddings)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto themePadding = textFieldTheme->GetPadding();
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    paddings.top = NG::CalcLength(themePadding.Top().ConvertToPx());
    paddings.bottom = NG::CalcLength(themePadding.Top().ConvertToPx());
    paddings.left = NG::CalcLength(themePadding.Left().ConvertToPx());
    paddings.right = NG::CalcLength(themePadding.Left().ConvertToPx());
}

RefPtr<TextFieldControllerBase> TextFieldModelNG::CreateTextInput(
    const std::optional<std::string>& placeholder, const std::optional<std::string>& value)
{
    CreateNode(placeholder, value, false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetTextFieldController();
};

RefPtr<TextFieldControllerBase> TextFieldModelNG::CreateTextArea(
    const std::optional<std::string>& placeholder, const std::optional<std::string>& value)
{
    CreateNode(placeholder, value, true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetTextFieldController();
}

void TextFieldModelNG::SetWidthAuto(bool isAuto)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == V2::TEXTAREA_ETS_TAG) {
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, WidthAuto, isAuto);
}

void TextFieldModelNG::SetType(TextInputType value)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    if (layoutProperty->HasTextInputType() && layoutProperty->GetTextInputTypeValue() != value) {
        layoutProperty->UpdateTypeChanged(true);
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextInputType, value);
}

void TextFieldModelNG::SetPlaceholderColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PlaceholderTextColor, value);
}

void TextFieldModelNG::SetPlaceholderFont(const Font& value)
{
    if (value.fontSize.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PlaceholderFontSize, value.fontSize.value());
    }
    if (value.fontStyle) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PlaceholderItalicFontStyle, value.fontStyle.value());
    }
    if (value.fontWeight) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PlaceholderFontWeight, value.fontWeight.value());
    }
    if (!value.fontFamilies.empty()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PlaceholderFontFamily, value.fontFamilies);
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PreferredPlaceholderLineHeightNeedToUpdate, true);
}

void TextFieldModelNG::SetEnterKeyType(TextInputAction value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateTextInputAction(value);
}

void TextFieldModelNG::SetCaretColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(TextFieldPaintProperty, CursorColor, value);
}

void TextFieldModelNG::SetTextAlign(TextAlign value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextAlign, value);
}
void TextFieldModelNG::SetMaxLength(uint32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, MaxLength, value);
}
void TextFieldModelNG::ResetMaxLength()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    if (textFieldLayoutProperty) {
        textFieldLayoutProperty->ResetMaxLength();
    }
}
void TextFieldModelNG::SetMaxLines(uint32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, MaxLines, value);
}
void TextFieldModelNG::SetFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, FontSize, value);
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PreferredTextLineHeightNeedToUpdate, true);
}
void TextFieldModelNG::SetFontWeight(FontWeight value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, FontWeight, value);
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PreferredTextLineHeightNeedToUpdate, true);
}
void TextFieldModelNG::SetTextColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextColor, value);
}
void TextFieldModelNG::SetFontStyle(Ace::FontStyle value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ItalicFontStyle, value);
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PreferredTextLineHeightNeedToUpdate, true);
}
void TextFieldModelNG::SetFontFamily(const std::vector<std::string>& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, FontFamily, value);
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PreferredTextLineHeightNeedToUpdate, true);
}

void TextFieldModelNG::SetInputFilter(const std::string& value, const std::function<void(const std::string&)>& onError)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, InputFilter, value);
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnInputFilterError(onError);
}

void TextFieldModelNG::SetInputStyle(InputStyle value)
{
    ACE_UPDATE_PAINT_PROPERTY(TextFieldPaintProperty, InputStyle, value);
}

void TextFieldModelNG::SetShowPasswordIcon(bool value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowPasswordIcon, value);
}

void TextFieldModelNG::SetOnEditChanged(std::function<void(bool)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnEditChanged(std::move(func));
}

void TextFieldModelNG::SetOnSubmit(std::function<void(int32_t)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSubmit(std::move(func));
}

void TextFieldModelNG::SetOnChange(std::function<void(const std::string&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(func));
}

void TextFieldModelNG::SetOnCopy(std::function<void(const std::string&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCopy(std::move(func));
}

void TextFieldModelNG::SetOnCut(std::function<void(const std::string&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCut(std::move(func));
}

void TextFieldModelNG::SetOnPaste(std::function<void(const std::string&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPaste(std::move(func));
}

void TextFieldModelNG::SetCopyOption(CopyOptions copyOption)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, CopyOptions, copyOption);
}

} // namespace OHOS::Ace::NG