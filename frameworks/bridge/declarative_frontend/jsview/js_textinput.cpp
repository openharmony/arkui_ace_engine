/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_textinput.h"

#include <vector>

#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_clipboard_function.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_textfield.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/core/common/ime/text_input_action.h"
#include "frameworks/core/common/ime/text_input_type.h"
#include "frameworks/core/components/text_field/text_field_component.h"
#include "frameworks/core/components/text_field/textfield_theme.h"

namespace OHOS::Ace::Framework {

namespace {

const std::vector<std::string> INPUT_FONT_FAMILY_VALUE = { "sans-serif" };
constexpr Dimension INNER_PADDING = 0.0_vp;

} // namespace

void JSTextInput::InitDefaultStyle()
{
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto stack = ViewStackProcessor::GetInstance();
    auto textInputComponent = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    auto theme = GetTheme<TextFieldTheme>();
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

void JSTextInput::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextInput>::Declare("TextInput");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSTextInput>::StaticMethod("create", &JSTextInput::Create, opt);
    JSClass<JSTextInput>::StaticMethod("type", &JSTextField::SetType);
    JSClass<JSTextInput>::StaticMethod("placeholderColor", &JSTextField::SetPlaceholderColor);
    JSClass<JSTextInput>::StaticMethod("placeholderFont", &JSTextField::SetPlaceholderFont);
    JSClass<JSTextInput>::StaticMethod("backgroundColor", &JSTextField::SetBackgroundColor);
    JSClass<JSTextInput>::StaticMethod("enterKeyType", &JSTextField::SetEnterKeyType);
    JSClass<JSTextInput>::StaticMethod("caretColor", &JSTextField::SetCaretColor);
    JSClass<JSTextInput>::StaticMethod("maxLength", &JSTextField::SetMaxLength);
    JSClass<JSTextInput>::StaticMethod("height", &JSTextField::JsHeight);
    JSClass<JSTextInput>::StaticMethod("padding", &JSTextField::JsPadding);
    JSClass<JSTextInput>::StaticMethod("border", &JSTextField::JsBorder);
    JSClass<JSTextInput>::StaticMethod("borderWidth", &JSTextField::JsBorderWidth);
    JSClass<JSTextInput>::StaticMethod("borderColor", &JSTextField::JsBorderColor);
    JSClass<JSTextInput>::StaticMethod("borderStyle", &JSTextField::JsBorderStyle);
    JSClass<JSTextInput>::StaticMethod("borderRadius", &JSTextField::JsBorderRadius);
    JSClass<JSTextInput>::StaticMethod("fontSize", &JSTextField::SetFontSize);
    JSClass<JSTextInput>::StaticMethod("fontColor", &JSTextField::SetTextColor);
    JSClass<JSTextInput>::StaticMethod("fontWeight", &JSTextField::SetFontWeight);
    JSClass<JSTextInput>::StaticMethod("fontStyle", &JSTextField::SetFontStyle);
    JSClass<JSTextInput>::StaticMethod("fontFamily", &JSTextField::SetFontFamily);
    JSClass<JSTextInput>::StaticMethod("inputFilter", &JSTextField::SetInputFilter);
    JSClass<JSTextInput>::StaticMethod("showPasswordIcon", &JSTextField::SetShowPasswordIcon);
    JSClass<JSTextInput>::StaticMethod("textAlign", &JSTextField::SetTextAlign);
    JSClass<JSTextInput>::StaticMethod("style", &JSTextField::SetInputStyle);
    JSClass<JSTextInput>::StaticMethod("hoverEffect", &JSTextField::JsHoverEffect);
    JSClass<JSTextInput>::StaticMethod("copyOption", &JSTextField::SetCopyOption);
    // API7 onEditChanged deprecated
    JSClass<JSTextInput>::StaticMethod("onEditChanged", &JSTextField::SetOnEditChanged);
    JSClass<JSTextInput>::StaticMethod("onEditChange", &JSTextField::SetOnEditChanged);
    JSClass<JSTextInput>::StaticMethod("onSubmit", &JSTextField::SetOnSubmit);
    JSClass<JSTextInput>::StaticMethod("onChange", &JSTextField::SetOnChange);
    JSClass<JSTextInput>::StaticMethod("onCopy", &JSTextField::SetOnCopy);
    JSClass<JSTextInput>::StaticMethod("onCut", &JSTextField::SetOnCut);
    JSClass<JSTextInput>::StaticMethod("onPaste", &JSTextField::SetOnPaste);
    JSClass<JSTextInput>::StaticMethod("onClick", &JSTextField::SetOnClick);
    JSClass<JSTextInput>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSTextInput>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSTextInput>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSTextInput>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSTextInput>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSTextInput>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSTextInput>::Inherit<JSViewAbstract>();
    JSClass<JSTextInput>::Bind(globalObj);
}

void JSTextInput::Create(const JSCallbackInfo& info)
{
    RefPtr<TextFieldComponent> textInputComponent = AceType::MakeRefPtr<TextFieldComponent>();
    ViewStackProcessor::GetInstance()->ClaimElementId(textInputComponent);
    textInputComponent->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    // default type is text, default action is done.
    textInputComponent->SetTextInputType(TextInputType::TEXT);
    textInputComponent->SetAction(TextInputAction::DONE);
    textInputComponent->SetInspectorTag("TextInput");
    textInputComponent->SetHoverAnimationType(HoverAnimationType::BOARD);
    ViewStackProcessor::GetInstance()->Push(textInputComponent);
    InitDefaultStyle();
    Border boxBorder;
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto theme = GetTheme<TextFieldTheme>();
    if (boxComponent->GetBackDecoration()) {
        boxBorder = boxComponent->GetBackDecoration()->GetBorder();
    }
    JSTextField::UpdateDecoration(boxComponent, textInputComponent, boxBorder, theme);

    JSInteractableView::SetFocusable(true);
    JSInteractableView::SetFocusNode(true);

    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGI("TextInput create without argument");
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);

    std::string placeholder;
    if (ParseJsString(paramObject->GetProperty("placeholder"), placeholder)) {
        textInputComponent->SetPlaceholder(placeholder);
    }

    std::string text;
    if (ParseJsString(paramObject->GetProperty("text"), text)) {
        textInputComponent->SetValue(text);
    }

    auto controllerObj = paramObject->GetProperty("controller");
    if (!controllerObj->IsUndefined() && !controllerObj->IsNull()) {
        JSTextInputController* jsController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSTextInputController>();
        if (jsController) {
            jsController->SetController(textInputComponent->GetTextFieldController());
        }
    } else {
        LOGI("controller do not configured");
    }
}

void JSTextInputController::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextInputController>::Declare("TextInputController");
    JSClass<JSTextInputController>::Method("caretPosition", &JSTextInputController::CaretPosition);
    JSClass<JSTextInputController>::Bind(globalObj, JSTextInputController::Constructor,
                                         JSTextInputController::Destructor);
}

void JSTextInputController::Constructor(const JSCallbackInfo& args)
{
    auto scroller = Referenced::MakeRefPtr<JSTextInputController>();
    scroller->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(scroller));
}

void JSTextInputController::Destructor(JSTextInputController* scroller)
{
    if (scroller != nullptr) {
        scroller->DecRefCount();
    }
}

void JSTextInputController::CaretPosition(int32_t caretPosition)
{
    if (controller_) {
        controller_->CaretPosition(caretPosition);
    }
}

} // namespace OHOS::Ace::Framework