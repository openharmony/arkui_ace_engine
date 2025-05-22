/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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
#include "frameworks/bridge/declarative_frontend/jsview/js_text_editable_controller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_textfield.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {
constexpr uint32_t MAX_LINES = 3;
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
    JSClass<JSTextArea>::StaticMethod("width", &JSTextField::JsWidth);
    JSClass<JSTextArea>::StaticMethod("padding", &JSTextField::JsPadding);
    JSClass<JSTextArea>::StaticMethod("margin", &JSTextField::JsMargin);
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
    JSClass<JSTextArea>::StaticMethod("minFontScale", &JSTextField::SetMinFontScale);
    JSClass<JSTextArea>::StaticMethod("maxFontScale", &JSTextField::SetMaxFontScale);
    JSClass<JSTextArea>::StaticMethod("inputFilter", &JSTextField::SetInputFilter);
    JSClass<JSTextArea>::StaticMethod("hoverEffect", &JSTextField::JsHoverEffect);
    JSClass<JSTextArea>::StaticMethod("maxLength", &JSTextField::SetMaxLength);
    JSClass<JSTextArea>::StaticMethod("showCounter", &JSTextField::SetShowCounter);
    JSClass<JSTextArea>::StaticMethod("barState", &JSTextField::SetBarState);
    JSClass<JSTextArea>::StaticMethod("maxLines", &JSTextArea::SetMaxLines);
    JSClass<JSTextArea>::StaticMethod("style", &JSTextField::SetInputStyle);
    JSClass<JSTextArea>::StaticMethod("onWillChange", &JSTextField::SetOnWillChange);
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
    JSClass<JSTextArea>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSTextArea>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSTextArea>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSTextArea>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSTextArea>::StaticMethod("onEditChange", &JSTextField::SetOnEditChanged);
    JSClass<JSTextArea>::StaticMethod("copyOption", &JSTextField::SetCopyOption);
    JSClass<JSTextArea>::StaticMethod("foregroundColor", &JSTextField::SetForegroundColor);
    JSClass<JSTextArea>::StaticMethod("enableKeyboardOnFocus", &JSTextField::SetEnableKeyboardOnFocus);
    JSClass<JSTextArea>::StaticMethod("selectionMenuHidden", &JSTextField::SetSelectionMenuHidden);
    JSClass<JSTextArea>::StaticMethod("customKeyboard", &JSTextField::SetCustomKeyboard);
    JSClass<JSTextArea>::StaticMethod("onSubmit", &JSTextField::SetOnSubmit);
    JSClass<JSTextArea>::StaticMethod("enterKeyType", &JSTextField::SetEnterKeyType);
    JSClass<JSTextArea>::StaticMethod("type", &JSTextField::SetType);
    JSClass<JSTextArea>::StaticMethod("fontFeature", &JSTextField::SetFontFeature);
    JSClass<JSTextArea>::StaticMethod("lineBreakStrategy", &JSTextField::SetLineBreakStrategy);
    JSClass<JSTextArea>::StaticMethod("decoration", &JSTextField::SetDecoration);
    JSClass<JSTextArea>::StaticMethod("minFontSize", &JSTextField::SetMinFontSize);
    JSClass<JSTextArea>::StaticMethod("maxFontSize", &JSTextField::SetMaxFontSize);
    JSClass<JSTextArea>::StaticMethod("heightAdaptivePolicy", &JSTextField::SetHeightAdaptivePolicy);
    JSClass<JSTextArea>::StaticMethod("letterSpacing", &JSTextField::SetLetterSpacing);
    JSClass<JSTextArea>::StaticMethod("lineHeight", &JSTextField::SetLineHeight);
    JSClass<JSTextArea>::StaticMethod("halfLeading", &JSTextField::SetHalfLeading);
    JSClass<JSTextArea>::StaticMethod("lineSpacing", &JSTextField::SetLineSpacing);
    JSClass<JSTextArea>::StaticMethod("wordBreak", &JSTextField::SetWordBreak);
    JSClass<JSTextArea>::StaticMethod("contentType", &JSTextField::SetContentType);
    JSClass<JSTextArea>::StaticMethod("enableAutoFill", &JSTextField::SetEnableAutoFill);
    JSClass<JSTextArea>::StaticMethod("selectedBackgroundColor", &JSTextField::SetSelectedBackgroundColor);
    JSClass<JSTextArea>::StaticMethod("caretStyle", &JSTextField::SetCaretStyle);
    JSClass<JSTextArea>::StaticMethod("textIndent", &JSTextField::SetTextIndent);
    JSClass<JSTextArea>::StaticMethod("textOverflow", &JSTextField::SetTextOverflow);
    JSClass<JSTextArea>::StaticMethod("onWillInsert", &JSTextField::OnWillInsertValue);
    JSClass<JSTextArea>::StaticMethod("onDidInsert", &JSTextField::OnDidInsertValue);
    JSClass<JSTextArea>::StaticMethod("onWillDelete", &JSTextField::OnWillDelete);
    JSClass<JSTextArea>::StaticMethod("onDidDelete", &JSTextField::OnDidDelete);
    JSClass<JSTextArea>::StaticMethod("editMenuOptions", &JSTextField::EditMenuOptions);
    JSClass<JSTextArea>::StaticMethod("enablePreviewText", &JSTextField::SetEnablePreviewText);
    JSClass<JSTextArea>::StaticMethod("enableHapticFeedback", &JSTextField::SetEnableHapticFeedback);
    JSClass<JSTextArea>::StaticMethod("ellipsisMode", &JSTextField::SetEllipsisMode);
    JSClass<JSTextArea>::StaticMethod("stopBackPress", &JSTextField::SetStopBackPress);
    JSClass<JSTextArea>::StaticMethod("keyboardAppearance", &JSTextField::SetKeyboardAppearance);
    JSClass<JSTextArea>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSTextArea::Create(const JSCallbackInfo& info)
{
    JSTextField::CreateTextArea(info);
}

void JSTextArea::SetMaxLines(const JSCallbackInfo& info)
{
    auto normalMaxViewLines = Infinity<uint32_t>();
    auto inlineMaxViewLines = MAX_LINES;
    auto isValid = !(info.Length() < 1 || !info[0]->IsNumber() || info[0]->ToNumber<int32_t>() <= 0);
    if (isValid) {
        inlineMaxViewLines = info[0]->ToNumber<uint32_t>();
        normalMaxViewLines = info[0]->ToNumber<uint32_t>();
    }
    TextFieldModel::GetInstance()->SetNormalMaxViewLines(normalMaxViewLines);
    TextFieldModel::GetInstance()->SetMaxViewLines(inlineMaxViewLines);
}

void JSTextAreaController::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextEditableController>::Declare("TextAreaController");
    JSTextEditableController::JSBind(globalObj);
}
} // namespace OHOS::Ace::Framework
