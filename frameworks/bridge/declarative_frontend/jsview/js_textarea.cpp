/*
 * Copyright (c) 20212022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_textarea.h"

#include <vector>

#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_clipboard_function.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_textfield.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

namespace {

const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END };
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<std::string> INPUT_FONT_FAMILY_VALUE = { "sans-serif" };
constexpr uint32_t TEXTAREA_MAXLENGTH_VALUE_DEFAULT = std::numeric_limits<uint32_t>::max();

}; // namespace

void JSTextArea::InitDefaultStyle()
{
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto stack = ViewStackProcessor::GetInstance();
    auto textAreaComponent = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    auto theme = GetTheme<TextFieldTheme>();
    if (!boxComponent || !textAreaComponent || !theme) {
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

void JSTextArea::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextArea>::Declare("TextArea");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSTextArea>::StaticMethod("create", &JSTextArea::Create, opt);
    JSClass<JSTextArea>::StaticMethod("placeholderColor", &JSTextField::SetPlaceholderColor);
    JSClass<JSTextArea>::StaticMethod("placeholderFont", &JSTextField::SetPlaceholderFont);
    JSClass<JSTextArea>::StaticMethod("backgroundColor", &JSTextField::SetBackgroundColor);
    JSClass<JSTextArea>::StaticMethod("textAlign", &JSTextField::SetTextAlign);
    JSClass<JSTextArea>::StaticMethod("caretColor", &JSTextField::SetCaretColor);
    JSClass<JSTextArea>::StaticMethod("height", &JSTextField::JsHeight);
    JSClass<JSTextArea>::StaticMethod("padding", &JSTextField::JsPadding);
    JSClass<JSTextArea>::StaticMethod("border", &JSTextField::JsBorder);
    JSClass<JSTextArea>::StaticMethod("borderWidth", &JSTextField::JsBorderWidth);
    JSClass<JSTextArea>::StaticMethod("borderColor", &JSTextField::JsBorderColor);
    JSClass<JSTextArea>::StaticMethod("borderStyle", &JSTextField::JsBorderStyle);
    JSClass<JSTextArea>::StaticMethod("borderRadius", &JSTextField::JsBorderRadius);
    JSClass<JSTextArea>::StaticMethod("fontSize", &JSTextField::SetFontSize);
    JSClass<JSTextArea>::StaticMethod("fontColor", &JSTextField::SetTextColor);
    JSClass<JSTextArea>::StaticMethod("fontWeight", &JSTextField::SetFontWeight);
    JSClass<JSTextArea>::StaticMethod("fontStyle", &JSTextField::SetFontStyle);
    JSClass<JSTextArea>::StaticMethod("fontFamily", &JSTextField::SetFontFamily);
    JSClass<JSTextArea>::StaticMethod("inputFilter", &JSTextField::SetInputFilter);
    JSClass<JSTextArea>::StaticMethod("hoverEffect", &JSTextField::JsHoverEffect);
    JSClass<JSTextArea>::StaticMethod("onChange", &JSTextField::SetOnChange);
    JSClass<JSTextArea>::StaticMethod("onCopy", &JSTextField::SetOnCopy);
    JSClass<JSTextArea>::StaticMethod("onCut", &JSTextField::SetOnCut);
    JSClass<JSTextArea>::StaticMethod("onPaste", &JSTextField::SetOnPaste);
    JSClass<JSTextArea>::StaticMethod("onClick", &JSTextField::SetOnClick);
    JSClass<JSTextArea>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSTextArea>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSTextArea>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSTextArea>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSTextArea>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSTextArea>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSTextArea>::StaticMethod("copyOption", &JSTextField::SetCopyOption);
    JSClass<JSTextArea>::Inherit<JSViewAbstract>();
    JSClass<JSTextArea>::Bind(globalObj);
}

void JSTextArea::Create(const JSCallbackInfo& info)
{
    RefPtr<TextFieldComponent> textAreaComponent = AceType::MakeRefPtr<TextFieldComponent>();
    textAreaComponent->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    textAreaComponent->SetTextInputType(TextInputType::MULTILINE);
    textAreaComponent->SetHoverAnimationType(HoverAnimationType::BOARD);
    auto paramObject = JSRef<JSObject>::Cast(info[0]);

    ViewStackProcessor::GetInstance()->ClaimElementId(textAreaComponent);
    ViewStackProcessor::GetInstance()->Push(textAreaComponent);
    InitDefaultStyle();
    Border boxBorder;
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto theme = GetTheme<TextFieldTheme>();
    if (boxComponent->GetBackDecoration()) {
        boxBorder = boxComponent->GetBackDecoration()->GetBorder();
    }
    JSTextField::UpdateDecoration(boxComponent, textAreaComponent, boxBorder, theme);

    JSInteractableView::SetFocusable(true);
    JSInteractableView::SetFocusNode(true);

    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGI("TextArea create without argument");
        return;
    }

    std::string placeholder;
    if (ParseJsString(paramObject->GetProperty("placeholder"), placeholder)) {
        textAreaComponent->SetPlaceholder(placeholder);
    }
    std::string text;
    if (ParseJsString(paramObject->GetProperty("text"), text)) {
        textAreaComponent->SetValue(text);
    }

    auto controllerObj = paramObject->GetProperty("controller");
    if (!controllerObj->IsUndefined() && !controllerObj->IsNull()) {
        JSTextAreaController* jsController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSTextAreaController>();
        if (jsController) {
            jsController->SetController(textAreaComponent->GetTextFieldController());
        }
    }
}

void JSTextAreaController::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextAreaController>::Declare("TextAreaController");
    JSClass<JSTextAreaController>::Method("caretPosition", &JSTextAreaController::CaretPosition);
    JSClass<JSTextAreaController>::Bind(globalObj, JSTextAreaController::Constructor, JSTextAreaController::Destructor);
}

void JSTextAreaController::Constructor(const JSCallbackInfo& args)
{
    auto scroller = Referenced::MakeRefPtr<JSTextAreaController>();
    scroller->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(scroller));
}

void JSTextAreaController::Destructor(JSTextAreaController* scroller)
{
    if (scroller != nullptr) {
        scroller->DecRefCount();
    }
}

void JSTextAreaController::CaretPosition(int32_t caretPosition)
{
    if (controller_) {
        controller_->CaretPosition(caretPosition);
    }
}

} // namespace OHOS::Ace::Framework