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

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_textfield.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/text_field/text_field_component.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace::Framework {
namespace {
const std::vector<std::string> INPUT_FONT_FAMILY_VALUE = { "sans-serif" };
constexpr Dimension INNER_PADDING = 0.0_vp;
} // namespace

RefPtr<TextFieldControllerBase> TextFieldModelImpl::CreateTextInput(
    const std::optional<std::string>& placeholder, const std::optional<std::string>& value)
{
    auto textInputComponent = AceType::MakeRefPtr<TextFieldComponent>();
    if (placeholder) {
        textInputComponent->SetPlaceholder(placeholder.value());
    }
    if (value) {
        textInputComponent->SetValue(value.value());
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
    if (value.fontSize) {
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
    const std::string& value, const std::function<void(const std::string&)>& onError)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetInputFilter(value);

    if (onError) {
        component->SetOnError(onError);
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

void TextFieldModelImpl::SetOnChange(std::function<void(const std::string&)>&& func)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetOnChange(std::move(func));
}

void TextFieldModelImpl::SetOnCopy(std::function<void(const std::string&)>&& func)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetOnCopy(std::move(func));
}

void TextFieldModelImpl::SetOnCut(std::function<void(const std::string&)>&& func)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetOnCut(std::move(func));
}

void TextFieldModelImpl::SetOnPaste(std::function<void(const std::string&)>&& func)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetOnPaste(std::move(func));
}

void TextFieldModelImpl::SetCopyOption(CopyOptions copyOption)
{
    JSViewSetProperty(&TextFieldComponent::SetCopyOption, copyOption);
}

} // namespace OHOS::Ace::Framework
