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
namespace {
constexpr Dimension UNDERLINE_NORMAL_HEIGHT = 48.0_vp;
constexpr Dimension UNDERLINE_NORMAL_PADDING = 12.0_vp;
} // namespace
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
    } else {
        textFieldLayoutProperty->UpdatePlaceholderMaxLines(Infinity<uint32_t>());
    }
    pattern->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    pattern->GetTextFieldController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    pattern->SetTextEditController(AceType::MakeRefPtr<TextEditController>());
    pattern->InitSurfaceChangedCallback();
    pattern->InitSurfacePositionChangedCallback();
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
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
    AddDragFrameNodeToManager();
    PaddingProperty paddings;
    ProcessDefaultPadding(paddings);
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Padding, paddings);
}

void TextFieldModelNG::SetShowUnderline(bool showUnderLine)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    auto rendercontext = frameNode->GetRenderContext();
    auto pipeline = frameNode->GetContext();
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    textFieldLayoutProperty->UpdateShowUnderline(showUnderLine);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    if (showUnderLine) {
        rendercontext->UpdateBackgroundColor(Color::TRANSPARENT);
        CalcSize idealSize;
        PaddingProperty paddings;
        ProcessDefaultPadding(paddings);
        ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Padding, paddings);
        if (textFieldLayoutProperty->GetPropertyChangeFlag() == PROPERTY_UPDATE_NORMAL) {
            std::optional<CalcLength> height(UNDERLINE_NORMAL_HEIGHT);
            idealSize.SetHeight(height);
            textFieldLayoutProperty->UpdateUserDefinedIdealSize(idealSize);
        }
        textFieldLayoutProperty->UpdateFontSize(textFieldTheme->GetUnderlineFontSize());
        if (!textFieldLayoutProperty->HasTextColor()) {
            textFieldLayoutProperty->UpdateTextColor(textFieldTheme->GetUnderlineTextColor());
        }
        Radius radius;
        rendercontext->UpdateBorderRadius({ radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() });
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowUnderline, showUnderLine);
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
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    if (layoutProperty->GetShowUnderlineValue(false)) {
        paddings.top = NG::CalcLength(UNDERLINE_NORMAL_PADDING);
        paddings.bottom = NG::CalcLength(UNDERLINE_NORMAL_PADDING);
        paddings.left = NG::CalcLength(0);
        paddings.right = NG::CalcLength(0);
    } else {
        paddings.top = NG::CalcLength(themePadding.Top().ConvertToPx());
        paddings.bottom = NG::CalcLength(themePadding.Top().ConvertToPx());
        paddings.left = NG::CalcLength(themePadding.Left().ConvertToPx());
        paddings.right = NG::CalcLength(themePadding.Left().ConvertToPx());
    }
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

void TextFieldModelNG::RequestKeyboardOnFocus(bool needToRequest)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->SetNeedToRequestKeyboardOnFocus(needToRequest);
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

void TextFieldModelNG::SetCaretStyle(const CaretStyle& value)
{
    if (value.caretWidth.has_value()) {
        ACE_UPDATE_PAINT_PROPERTY(TextFieldPaintProperty, CursorWidth, value.caretWidth.value());
    }
}

void TextFieldModelNG::SetCaretPosition(const int32_t& value)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    auto caretPosition = layoutProperty->GetPlaceholderValue() == "" ? value : 0;
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, CaretPosition, caretPosition);
    pattern->SetCaretPosition(caretPosition);
    pattern->UpdateCaretPositionByTextEdit();
}

void TextFieldModelNG::SetSelectedBackgroundColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(TextFieldPaintProperty, SelectedBackgroundColor, value);
}

void TextFieldModelNG::SetTextAlign(TextAlign value)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    if (layoutProperty->GetTextAlignValue(TextAlign::START) != value) {
        layoutProperty->UpdateTextAlignChanged(true);
    }
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
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, value);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorFlag, true);
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
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->InitEditingValueTextWithFilter();
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

void TextFieldModelNG::SetOnTextSelectionChange(std::function<void(int32_t, int32_t)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelectionChange(std::move(func));
}

void TextFieldModelNG::SetOnScroll(std::function<void(float, float)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollChangeEvent(std::move(func));
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

void TextFieldModelNG::SetMenuOptionItems(std::vector<MenuOptionsParam>&& menuOptionsItems)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    textFieldPattern->SetMenuOptionItems(std::move(menuOptionsItems));
}

void TextFieldModelNG::AddDragFrameNodeToManager() const
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    dragDropManager->AddTextFieldDragFrameNode(AceType::WeakClaim(AceType::RawPtr(frameNode)));
}

void TextFieldModelNG::SetForegroundColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextColor, value);
}

void TextFieldModelNG::SetPasswordIcon(const PasswordIcon& passwordIcon)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    if (passwordIcon.showResult == "") {
        pattern->SetShowUserDefinedIcon(false);
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowPasswordSourceInfo,
            ImageSourceInfo(passwordIcon.showResult, passwordIcon.showBundleName, passwordIcon.showModuleName));
        pattern->SetShowUserDefinedIcon(true);
    }
    if (passwordIcon.hideResult == "") {
        pattern->SetHideUserDefinedIcon(false);
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, HidePasswordSourceInfo,
            ImageSourceInfo(passwordIcon.hideResult, passwordIcon.hideBundleName, passwordIcon.hideModuleName));
        pattern->SetHideUserDefinedIcon(true);
    }
}

void TextFieldModelNG::SetShowUnit(std::function<void()>&& unitFunction)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    RefPtr<NG::UINode> unitNode;
    if (unitFunction) {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        unitFunction();
        unitNode = NG::ViewStackProcessor::GetInstance()->Finish();
    }
    if (unitNode) {
        pattern->SetUnitNode(unitNode);
    }
}

void TextFieldModelNG::SetShowError(const std::string& errorText, bool visible)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ErrorText, errorText);
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowErrorText, visible);
}

void TextFieldModelNG::SetShowCounter(bool value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowCounter, value);
}

void TextFieldModelNG::SetBarState(OHOS::Ace::DisplayMode value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, DisplayMode, value);
}

void TextFieldModelNG::SetMaxViewLines(uint32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, MaxViewLines, value);
}

void TextFieldModelNG::SetBackgroundColor(const Color& color, bool tmp)
{
    Color backgroundColor;
    if (tmp) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID_NOLOG(pipeline);
        auto themeManager = pipeline->GetThemeManager();
        CHECK_NULL_VOID_NOLOG(themeManager);
        auto theme = themeManager->GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID_NOLOG(theme);
        backgroundColor = theme->GetBgColor();
        return;
    }

    NG::ViewAbstract::SetBackgroundColor(color);
}

void TextFieldModelNG::SetHeight(const Dimension& value) {}

void TextFieldModelNG::SetPadding(NG::PaddingProperty& newPadding, Edge oldPadding, bool tmp)
{
    if (tmp) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID_NOLOG(theme);
        auto textFieldPadding = theme->GetPadding();
        auto top = textFieldPadding.Top();
        auto bottom = textFieldPadding.Bottom();
        auto left = textFieldPadding.Left();
        auto right = textFieldPadding.Right();

        NG::PaddingProperty paddings;
        if (top.Value()) {
            if (top.Unit() == DimensionUnit::CALC) {
                paddings.top = NG::CalcLength(top.IsNonNegative() ? top.CalcValue() : CalcDimension().CalcValue());
            } else {
                paddings.top = NG::CalcLength(top.IsNonNegative() ? top : CalcDimension());
            }
        }
        if (bottom.Value()) {
            if (bottom.Unit() == DimensionUnit::CALC) {
                paddings.bottom =
                    NG::CalcLength(bottom.IsNonNegative() ? bottom.CalcValue() : CalcDimension().CalcValue());
            } else {
                paddings.bottom = NG::CalcLength(bottom.IsNonNegative() ? bottom : CalcDimension());
            }
        }
        if (left.Value()) {
            if (left.Unit() == DimensionUnit::CALC) {
                paddings.left = NG::CalcLength(left.IsNonNegative() ? left.CalcValue() : CalcDimension().CalcValue());
            } else {
                paddings.left = NG::CalcLength(left.IsNonNegative() ? left : CalcDimension());
            }
        }
        if (right.Value()) {
            if (right.Unit() == DimensionUnit::CALC) {
                paddings.right =
                    NG::CalcLength(right.IsNonNegative() ? right.CalcValue() : CalcDimension().CalcValue());
            } else {
                paddings.right = NG::CalcLength(right.IsNonNegative() ? right : CalcDimension());
            }
        }
        ViewAbstract::SetPadding(paddings);
        return;
    }
    NG::ViewAbstract::SetPadding(newPadding);
}

void TextFieldModelNG::SetHoverEffect(HoverEffectType hoverEffect)
{
    NG::ViewAbstract::SetHoverEffect(hoverEffect);
}

void TextFieldModelNG::SetOnChangeEvent(std::function<void(const std::string&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(func));
}

void TextFieldModelNG::SetSelectionMenuHidden(bool selectionMenuHidden)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, SelectionMenuHidden, selectionMenuHidden);
}
} // namespace OHOS::Ace::NG
