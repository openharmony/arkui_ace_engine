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
    JSClass<JSTextArea>::StaticMethod("maxLength", &JSTextField::SetMaxLength);
    JSClass<JSTextArea>::StaticMethod("showCounter", &JSTextField::SetShowCounter);
    JSClass<JSTextArea>::StaticMethod("barState", &JSTextField::SetBarState);
    JSClass<JSTextArea>::StaticMethod("maxLines", &JSTextField::SetMaxLines);
    JSClass<JSTextArea>::StaticMethod("style", &JSTextField::SetInputStyle);
    JSClass<JSTextArea>::StaticMethod("onChange", &JSTextField::SetOnChange);
    JSClass<JSTextArea>::StaticMethod("onTextSelectionChange", &JSTextField::SetOnTextSelectionChange);
    JSClass<JSTextArea>::StaticMethod("onContentScroll", &JSTextField::SetOnContentScroll);
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
    JSClass<JSTextArea>::StaticMethod("onEditChange", &JSTextField::SetOnEditChanged);
    JSClass<JSTextArea>::StaticMethod("copyOption", &JSTextField::SetCopyOption);
    JSClass<JSTextArea>::StaticMethod("textMenuOptions", &JSTextField::JsMenuOptionsExtension);
    JSClass<JSTextArea>::StaticMethod("foregroundColor", &JSTextField::SetForegroundColor);
    JSClass<JSTextArea>::StaticMethod("enableKeyboardOnFocus", &JSTextField::SetEnableKeyboardOnFocus);
    JSClass<JSTextArea>::StaticMethod("selectionMenuHidden", &JSTextField::SetSelectionMenuHidden);
    JSClass<JSTextArea>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSTextArea::Create(const JSCallbackInfo& info)
{
    JSTextField::CreateTextArea(info);
}

void JSTextAreaController::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextAreaController>::Declare("TextAreaController");
    JSClass<JSTextAreaController>::Method("caretPosition", &JSTextAreaController::CaretPosition);
    JSClass<JSTextAreaController>::Method("setTextSelection", &JSTextAreaController::SetTextSelection);
    JSClass<JSTextAreaController>::Method("stopEditing", &JSTextAreaController::StopEditing);
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
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        controller->CaretPosition(caretPosition);
    }
}

void JSTextAreaController::SetTextSelection(int32_t selectionStart, int32_t selectionEnd)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        controller->SetTextSelection(selectionStart, selectionEnd);
    }
}

void JSTextAreaController::StopEditing()
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        controller->StopEditing();
    }
}
} // namespace OHOS::Ace::Framework
