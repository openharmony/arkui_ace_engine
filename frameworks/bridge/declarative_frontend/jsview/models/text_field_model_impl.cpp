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

#include "bridge/declarative_frontend/jsview/models/text_field_model_impl.h"

#include "base/utils/utf_helper.h"
#include "bridge/declarative_frontend/jsview/js_textfield.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {
namespace {
const std::vector<std::string> INPUT_FONT_FAMILY_VALUE = { "sans-serif" };
constexpr Dimension INNER_PADDING = 0.0_vp;
constexpr uint32_t TEXTAREA_MAXLENGTH_VALUE_DEFAULT = std::numeric_limits<uint32_t>::max();
} // namespace

RefPtr<TextFieldControllerBase> TextFieldModelImpl::CreateTextInput(
    const std::optional<std::u16string>& placeholder, const std::optional<std::u16string>& value)
{
    auto textInputComponent = AceType::MakeRefPtr<TextFieldComponent>();
    if (placeholder) {
        textInputComponent->SetPlaceholder(UtfUtils::Str16DebugToStr8(placeholder.value()));
    }
    if (value) {
        textInputComponent->SetValue(UtfUtils::Str16DebugToStr8(value.value()));
    }
    ViewStackProcessor::GetInstance()->ClaimElementId(textInputComponent);
    textInputComponent->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    // default type is text, default action is done.
    textInputComponent->SetTextInputType(TextInputType::TEXT);
    textInputComponent->SetAction(TextInputAction::DONE);
    textInputComponent->SetInspectorTag("TextInput");
    textInputComponent->SetHoverAnimationType(HoverAnimationType::BOARD);
    ViewStackProcessor::GetInstance()->Push(textInputComponent);
    InitTextInputDefaultStyle();
    Border boxBorder;
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline) {
        auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
        if (boxComponent->GetBackDecoration()) {
            boxBorder = boxComponent->GetBackDecoration()->GetBorder();
        }
        JSTextField::UpdateDecoration(boxComponent, textInputComponent, boxBorder, theme);
    }

    return textInputComponent->GetTextFieldController();
}

void InitTextAreaDefaultStyle()
{
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto* stack = ViewStackProcessor::GetInstance();
    auto textAreaComponent = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
    if (!boxComponent || !textAreaComponent || !theme) {
        LOGI("boxComponent or textAreaComponent or theme is null");
        return;
    }

    textAreaComponent->SetTextMaxLines(TEXTAREA_MAXLENGTH_VALUE_DEFAULT);
    textAreaComponent->SetCursorColor(theme->GetCursorColor());
    textAreaComponent->SetPlaceholderColor(theme->GetPlaceholderColor());
    textAreaComponent->SetFocusBgColor(theme->GetFocusBgColor());
    textAreaComponent->SetFocusPlaceholderColor(theme->GetFocusPlaceholderColor());
    textAreaComponent->SetFocusTextColor(theme->GetFocusTextColor());
    textAreaComponent->SetBgColor(theme->GetBgColor());
    textAreaComponent->SetTextColor(theme->GetTextColor());
    textAreaComponent->SetSelectedColor(theme->GetSelectedColor());
    textAreaComponent->SetHoverColor(theme->GetHoverColor());
    textAreaComponent->SetPressColor(theme->GetPressColor());

    TextStyle textStyle = textAreaComponent->GetTextStyle();
    textStyle.SetTextColor(theme->GetTextColor());
    textStyle.SetFontSize(theme->GetFontSize());
    textStyle.SetFontWeight(theme->GetFontWeight());
    textStyle.SetFontFamilies(INPUT_FONT_FAMILY_VALUE);
    textAreaComponent->SetTextStyle(textStyle);
    textAreaComponent->SetEditingStyle(textStyle);
    textAreaComponent->SetPlaceHoldStyle(textStyle);

    textAreaComponent->SetCountTextStyle(theme->GetCountTextStyle());
    textAreaComponent->SetOverCountStyle(theme->GetOverCountStyle());
    textAreaComponent->SetCountTextStyleOuter(theme->GetCountTextStyleOuter());
    textAreaComponent->SetOverCountStyleOuter(theme->GetOverCountStyleOuter());
    textAreaComponent->SetErrorBorderWidth(theme->GetErrorBorderWidth());
    textAreaComponent->SetErrorBorderColor(theme->GetErrorBorderColor());

    RefPtr<Decoration> backDecoration = AceType::MakeRefPtr<Decoration>();
    backDecoration->SetPadding(theme->GetPadding());
    backDecoration->SetBackgroundColor(theme->GetBgColor());
    backDecoration->SetBorderRadius(theme->GetBorderRadius());
    const auto& boxDecoration = boxComponent->GetBackDecoration();
    if (boxDecoration) {
        backDecoration->SetImage(boxDecoration->GetImage());
        backDecoration->SetGradient(boxDecoration->GetGradient());
    }
    textAreaComponent->SetOriginBorder(backDecoration->GetBorder());
    textAreaComponent->SetDecoration(backDecoration);
    textAreaComponent->SetIconSize(theme->GetIconSize());
    textAreaComponent->SetIconHotZoneSize(theme->GetIconHotZoneSize());
    textAreaComponent->SetHeight(theme->GetHeight());

    // text area need to extend height.
    textAreaComponent->SetExtend(true);
    boxComponent->SetHeight(-1.0, DimensionUnit::VP);
}

RefPtr<TextFieldControllerBase> TextFieldModelImpl::CreateTextArea(
    const std::optional<std::u16string>& placeholder, const std::optional<std::u16string>& value)
{
    RefPtr<TextFieldComponent> textAreaComponent = AceType::MakeRefPtr<TextFieldComponent>();
    textAreaComponent->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    textAreaComponent->SetTextInputType(TextInputType::MULTILINE);
    textAreaComponent->SetHoverAnimationType(HoverAnimationType::BOARD);

    ViewStackProcessor::GetInstance()->ClaimElementId(textAreaComponent);
    ViewStackProcessor::GetInstance()->Push(textAreaComponent);
    InitTextAreaDefaultStyle();
    Border boxBorder;
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto theme = JSViewAbstract::GetTheme<TextFieldTheme>();
    if (boxComponent->GetBackDecoration()) {
        boxBorder = boxComponent->GetBackDecoration()->GetBorder();
    }
    if (value) {
        textAreaComponent->SetValue(UtfUtils::Str16DebugToStr8(value.value()));
    }
    if (placeholder) {
        textAreaComponent->SetPlaceholder(UtfUtils::Str16DebugToStr8(placeholder.value()));
    }
    UpdateDecoration(boxComponent, textAreaComponent, boxBorder, theme);

    return textAreaComponent->GetTextFieldController();
}

void TextFieldModelImpl::InitTextInputDefaultStyle()
{
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto* stack = ViewStackProcessor::GetInstance();
    auto textInputComponent = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    auto theme = JSViewAbstract::GetTheme<TextFieldTheme>();
    if (!boxComponent || !textInputComponent || !theme) {
        return;
    }

    textInputComponent->SetCursorColor(theme->GetCursorColor());
    textInputComponent->SetCursorRadius(theme->GetCursorRadius());
    textInputComponent->SetPlaceholderColor(theme->GetPlaceholderColor());
    textInputComponent->SetFocusBgColor(theme->GetFocusBgColor());
    textInputComponent->SetFocusPlaceholderColor(theme->GetFocusPlaceholderColor());
    textInputComponent->SetFocusTextColor(theme->GetFocusTextColor());
    textInputComponent->SetBgColor(theme->GetBgColor());
    textInputComponent->SetTextColor(theme->GetTextColor());
    textInputComponent->SetSelectedColor(theme->GetSelectedColor());
    textInputComponent->SetHoverColor(theme->GetHoverColor());
    textInputComponent->SetPressColor(theme->GetPressColor());
    textInputComponent->SetNeedFade(theme->NeedFade());
    textInputComponent->SetShowEllipsis(theme->ShowEllipsis());

    TextStyle textStyle = textInputComponent->GetTextStyle();
    textStyle.SetTextColor(theme->GetTextColor());
    textStyle.SetFontSize(theme->GetFontSize());
    textStyle.SetFontWeight(theme->GetFontWeight());
    textStyle.SetFontFamilies(INPUT_FONT_FAMILY_VALUE);
    textInputComponent->SetTextStyle(textStyle);
    textInputComponent->SetEditingStyle(textStyle);
    textInputComponent->SetPlaceHoldStyle(textStyle);

    textInputComponent->SetCountTextStyle(theme->GetCountTextStyle());
    textInputComponent->SetOverCountStyle(theme->GetOverCountStyle());
    textInputComponent->SetCountTextStyleOuter(theme->GetCountTextStyleOuter());
    textInputComponent->SetOverCountStyleOuter(theme->GetOverCountStyleOuter());

    textInputComponent->SetErrorTextStyle(theme->GetErrorTextStyle());
    textInputComponent->SetErrorSpacing(theme->GetErrorSpacing());
    textInputComponent->SetErrorIsInner(theme->GetErrorIsInner());
    textInputComponent->SetErrorBorderWidth(theme->GetErrorBorderWidth());
    textInputComponent->SetErrorBorderColor(theme->GetErrorBorderColor());

    RefPtr<Decoration> decoration = AceType::MakeRefPtr<Decoration>();
    // Need to update when UX of PC supported.
    auto edge = theme->GetPadding();
    edge.SetTop(INNER_PADDING);
    edge.SetBottom(INNER_PADDING);
    decoration->SetPadding(edge);
    decoration->SetBackgroundColor(theme->GetBgColor());
    decoration->SetBorderRadius(theme->GetBorderRadius());
    const auto& boxDecoration = boxComponent->GetBackDecoration();
    if (boxDecoration) {
        decoration->SetImage(boxDecoration->GetImage());
        decoration->SetGradient(boxDecoration->GetGradient());
    }
    textInputComponent->SetOriginBorder(decoration->GetBorder());
    textInputComponent->SetDecoration(decoration);
    textInputComponent->SetIconSize(theme->GetIconSize());
    textInputComponent->SetIconHotZoneSize(theme->GetIconHotZoneSize());
    textInputComponent->SetHeight(theme->GetHeight());
}

void TextFieldModelImpl::SetType(TextInputType value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetTextInputType(value);
    component->SetObscure(value == TextInputType::VISIBLE_PASSWORD);
}

void TextFieldModelImpl::SetPlaceholderColor(const Color& value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetPlaceholderColor(value);
    component->SetFocusPlaceholderColor(value);
}

void TextFieldModelImpl::SetPlaceholderFont(const Font& value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetPlaceHoldStyle();
    if (value.fontSize && value.fontSize->IsNonNegative()) {
        textStyle.SetFontSize(value.fontSize.value());
    }
    if (value.fontWeight) {
        textStyle.SetFontWeight(value.fontWeight.value());
    }
    if (value.fontStyle) {
        textStyle.SetFontStyle(value.fontStyle.value());
    }
    if (!value.fontFamilies.empty()) {
        textStyle.SetFontFamilies(value.fontFamilies);
    }
    component->SetPlaceHoldStyle(textStyle);
}

void TextFieldModelImpl::SetEnterKeyType(TextInputAction value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetAction(value);
}

void TextFieldModelImpl::SetTextAlign(TextAlign value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetTextAlign(value);
}

void TextFieldModelImpl::SetInputStyle(InputStyle value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetInputStyle(value);
}

void TextFieldModelImpl::SetCaretColor(const Color& value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetCursorColor(value);
}

void TextFieldModelImpl::SetCaretStyle(const CaretStyle& value) {};
void TextFieldModelImpl::SetCaretPosition(const int32_t& value) {};
void TextFieldModelImpl::SetSelectedBackgroundColor(const Color& value) {};

void TextFieldModelImpl::SetMaxLength(uint32_t value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetMaxLength(value);
}

void TextFieldModelImpl::SetMaxLines(uint32_t value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetTextMaxLines(value);
}

void TextFieldModelImpl::SetFontSize(const Dimension& value)
{
    if (value.IsNegative()) {
        return;
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetEditingStyle();
    textStyle.SetFontSize(value);
    component->SetEditingStyle(textStyle);
}

void TextFieldModelImpl::SetFontWeight(FontWeight value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetEditingStyle();
    textStyle.SetFontWeight(value);
    component->SetEditingStyle(textStyle);
}

void TextFieldModelImpl::SetMinFontScale(const float value) {}

void TextFieldModelImpl::SetMaxFontScale(const float value) {}

void TextFieldModelImpl::SetTextColor(const Color& value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetEditingStyle();
    textStyle.SetTextColor(value);
    component->SetEditingStyle(textStyle);
}

void TextFieldModelImpl::SetFontStyle(FontStyle value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetEditingStyle();
    textStyle.SetFontStyle(value);
    component->SetEditingStyle(textStyle);
}

void TextFieldModelImpl::SetFontFamily(const std::vector<std::string>& value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetEditingStyle();
    textStyle.SetFontFamilies(value);
    component->SetEditingStyle(textStyle);
}

void TextFieldModelImpl::SetInputFilter(
    const std::string& value, const std::function<void(const std::u16string&)>&& func)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetInputFilter(value);
    if (func) {
        auto onError = [func] (const std::string& value) {
            func(UtfUtils::Str8DebugToStr16(value));
        };
        component->SetOnError(std::move(onError));
    }
}

void TextFieldModelImpl::SetShowPasswordIcon(bool value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetShowPasswordIcon(value);
}

void TextFieldModelImpl::SetOnEditChanged(std::function<void(bool)>&& func)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetOnEditChanged(std::move(func));
}

void TextFieldModelImpl::SetOnSubmit(std::function<void(int32_t)>&& func)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetOnSubmit(std::move(func));
}

void TextFieldModelImpl::SetOnChange(std::function<void(const ChangeValueInfo&)>&& func)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto onChange = [func] (const std::string& info) {
        if (!func) {
            ChangeValueInfo info;
            func(info);
        }
    };
    component->SetOnChange(std::move(onChange));
}

void TextFieldModelImpl::SetOnCopy(std::function<void(const std::u16string&)>&& func)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto onCopy = [func] (const std::string& value) {
        if (func) {
            func(UtfUtils::Str8DebugToStr16(value));
        }
    };
    component->SetOnCopy(std::move(onCopy));
}

void TextFieldModelImpl::SetOnCut(std::function<void(const std::u16string&)>&& func)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto onCut = [func] (const std::string& value) {
        if (func) {
            func(UtfUtils::Str8DebugToStr16(value));
        }
    };
    component->SetOnCut(std::move(onCut));
}

void TextFieldModelImpl::SetOnPaste(std::function<void(const std::u16string&)>&& func)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto onPaste = [func] (const std::string& value) {
        if (func) {
            func(UtfUtils::Str8DebugToStr16(value));
        }
    };
    component->SetOnPaste(std::move(onPaste));
}

void TextFieldModelImpl::SetCopyOption(CopyOptions copyOption)
{
    JSViewSetProperty(&TextFieldComponent::SetCopyOption, copyOption);
}

void TextFieldModelImpl::SetBackgroundColor(const Color& color, bool tmp)
{
    if (tmp) {
        return;
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetBgColor(color);
}

void TextFieldModelImpl::SetHeight(const Dimension& value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto textInputComponent = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(textInputComponent);
    textInputComponent->SetHeight(value);
}

void TextFieldModelImpl::SetPadding(const NG::PaddingProperty& newPadding, Edge oldPadding, bool tmp, bool hasRegist)
{
    if (tmp) {
        return;
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto decoration = component->GetDecoration();
    CHECK_NULL_VOID(decoration);
    decoration->SetPadding(oldPadding);
}

void TextFieldModelImpl::SetBackBorder()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto decoration = component->GetDecoration();
    CHECK_NULL_VOID(decoration);
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto boxDecoration = box->GetBackDecoration();
    CHECK_NULL_VOID(boxDecoration);
    decoration->SetBorder(boxDecoration->GetBorder());
    Border border = {};
    boxDecoration->SetBorder(border);
    component->SetOriginBorder(decoration->GetBorder());
}

void TextFieldModelImpl::SetHoverEffect(HoverEffectType value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetHoverAnimationType(static_cast<HoverAnimationType>(value));
}

void TextFieldModelImpl::SetOnClick(std::function<void(const ClickInfo&)>&& func)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetOnClick(std::move(func));
}

void TextFieldModelImpl::SetFocusableAndFocusNode()
{
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
    if (focusableComponent) {
        focusableComponent->SetFocusable(true);
    }

    auto focusNodeComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(false);
    if (focusNodeComponent) {
        focusNodeComponent->SetFocusNode(false);
    }
}

void TextFieldModelImpl::UpdateDecoration(const RefPtr<BoxComponent>& boxComponent,
    const RefPtr<TextFieldComponent>& component, const Border& boxBorder,
    const OHOS::Ace::RefPtr<OHOS::Ace::TextFieldTheme>& textFieldTheme)
{
    if (!textFieldTheme) {
        LOGI("UpdateDecoration: textFieldTheme is null.");
        return;
    }

    RefPtr<Decoration> decoration = component->GetDecoration();
    RefPtr<Decoration> boxDecoration = boxComponent->GetBackDecoration();
    if (!decoration) {
        decoration = AceType::MakeRefPtr<Decoration>();
    }
    if (boxDecoration) {
        Border border = decoration->GetBorder();
        border.SetLeftEdge(boxBorder.Left());
        border.SetRightEdge(boxBorder.Right());
        border.SetTopEdge(boxBorder.Top());
        border.SetBottomEdge(boxBorder.Bottom());
        border.SetBorderRadius(textFieldTheme->GetBorderRadius());
        decoration->SetBorder(border);
        component->SetOriginBorder(decoration->GetBorder());

        if (boxDecoration->GetImage() || boxDecoration->GetGradient().IsValid()) {
            // clear box properties except background image and radius.
            boxDecoration->SetBackgroundColor(Color::TRANSPARENT);
            Border border;
            border.SetBorderRadius(textFieldTheme->GetBorderRadius());
            boxDecoration->SetBorder(border);
        }
    } else {
        boxDecoration = AceType::MakeRefPtr<Decoration>();
        boxDecoration->SetBorderRadius(textFieldTheme->GetBorderRadius());
        boxComponent->SetBackDecoration(boxDecoration);
    }
}
} // namespace OHOS::Ace::Framework
