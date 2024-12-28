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

#include "frameworks/bridge/declarative_frontend/jsview/js_textinput.h"

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "core/common/container.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_clipboard_function.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_text_editable_controller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_textfield.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/ark_theme/theme_apply/js_textinput_theme.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/core/common/ime/text_input_action.h"
#include "frameworks/core/common/ime/text_input_type.h"
#include "frameworks/core/components/text_field/text_field_component.h"
#include "frameworks/core/components/text_field/textfield_theme.h"
#include "frameworks/core/components_ng/pattern/text_field/text_content_type.h"

namespace OHOS::Ace::Framework {

void JSTextInput::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextInput>::Declare("TextInput");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSTextInput>::StaticMethod("create", &JSTextInput::Create, opt);
    JSClass<JSTextInput>::StaticMethod("type", &JSTextField::SetType);
    JSClass<JSTextInput>::StaticMethod("contentType", &JSTextField::SetContentType);
    JSClass<JSTextInput>::StaticMethod("placeholderColor", &JSTextField::SetPlaceholderColor);
    JSClass<JSTextInput>::StaticMethod("placeholderFont", &JSTextField::SetPlaceholderFont);
    JSClass<JSTextInput>::StaticMethod("backgroundColor", &JSTextField::SetBackgroundColor);
    JSClass<JSTextInput>::StaticMethod("enterKeyType", &JSTextField::SetEnterKeyType);
    JSClass<JSTextInput>::StaticMethod("caretColor", &JSTextField::SetCaretColor);
    JSClass<JSTextInput>::StaticMethod("caretPosition", &JSTextField::SetCaretPosition);
    JSClass<JSTextInput>::StaticMethod("selectedBackgroundColor", &JSTextField::SetSelectedBackgroundColor);
    JSClass<JSTextInput>::StaticMethod("caretStyle", &JSTextField::SetCaretStyle);
    JSClass<JSTextInput>::StaticMethod("maxLength", &JSTextField::SetMaxLength);
    JSClass<JSTextInput>::StaticMethod("width", &JSTextField::JsWidth);
    JSClass<JSTextInput>::StaticMethod("height", &JSTextField::JsHeight);
    JSClass<JSTextInput>::StaticMethod("padding", &JSTextField::JsPadding);
    JSClass<JSTextInput>::StaticMethod("margin", &JSTextField::JsMargin);
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
    JSClass<JSTextInput>::StaticMethod("minFontScale", &JSTextField::SetMinFontScale);
    JSClass<JSTextInput>::StaticMethod("maxFontScale", &JSTextField::SetMaxFontScale);
    JSClass<JSTextInput>::StaticMethod("inputFilter", &JSTextField::SetInputFilter);
    JSClass<JSTextInput>::StaticMethod("showPasswordIcon", &JSTextField::SetShowPasswordIcon);
    JSClass<JSTextInput>::StaticMethod("textAlign", &JSTextField::SetTextAlign);
    JSClass<JSTextInput>::StaticMethod("style", &JSTextField::SetInputStyle);
    JSClass<JSTextInput>::StaticMethod("hoverEffect", &JSTextField::JsHoverEffect);
    JSClass<JSTextInput>::StaticMethod("copyOption", &JSTextField::SetCopyOption);
    JSClass<JSTextInput>::StaticMethod("foregroundColor", &JSTextField::SetForegroundColor);
    JSClass<JSTextInput>::StaticMethod("showUnit", &JSTextField::SetShowUnit);
    JSClass<JSTextInput>::StaticMethod("showError", &JSTextField::SetShowError);
    JSClass<JSTextInput>::StaticMethod("barState", &JSTextField::SetBarState);
    JSClass<JSTextInput>::StaticMethod("maxLines", &JSTextField::SetMaxLines);
    JSClass<JSTextInput>::StaticMethod("wordBreak", &JSTextField::SetWordBreak);
    JSClass<JSTextInput>::StaticMethod("ellipsisMode", &JSTextField::SetEllipsisMode);
    // API7 onEditChanged deprecated
    JSClass<JSTextInput>::StaticMethod("onEditChanged", &JSTextField::SetOnEditChanged);
    JSClass<JSTextInput>::StaticMethod("onEditChange", &JSTextField::SetOnEditChanged);
    JSClass<JSTextInput>::StaticMethod("onSecurityStateChange", &JSTextField::SetOnSecurityStateChange);
    JSClass<JSTextInput>::StaticMethod("onSubmit", &JSTextField::SetOnSubmit);
    JSClass<JSTextInput>::StaticMethod("onChange", &JSTextField::SetOnChange);
    JSClass<JSTextInput>::StaticMethod("onTextSelectionChange", &JSTextField::SetOnTextSelectionChange);
    JSClass<JSTextInput>::StaticMethod("onContentScroll", &JSTextField::SetOnContentScroll);
    JSClass<JSTextInput>::StaticMethod("onCopy", &JSTextField::SetOnCopy);
    JSClass<JSTextInput>::StaticMethod("onCut", &JSTextField::SetOnCut);
    JSClass<JSTextInput>::StaticMethod("onPaste", &JSTextField::SetOnPaste);
    JSClass<JSTextInput>::StaticMethod("onClick", &JSTextField::SetOnClick);
    JSClass<JSTextInput>::StaticMethod("requestKeyboardOnFocus", &JSTextField::SetEnableKeyboardOnFocus);
    JSClass<JSTextInput>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSTextInput>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSTextInput>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSTextInput>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSTextInput>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSTextInput>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSTextInput>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSTextInput>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSTextInput>::StaticMethod("passwordIcon", &JSTextField::SetPasswordIcon);
    JSClass<JSTextInput>::StaticMethod("showUnderline", &JSTextField::SetShowUnderline);
    JSClass<JSTextInput>::StaticMethod("underlineColor", &JSTextField::SetUnderlineColor);
    JSClass<JSTextInput>::StaticMethod("enableKeyboardOnFocus", &JSTextField::SetEnableKeyboardOnFocus);
    JSClass<JSTextInput>::StaticMethod("selectionMenuHidden", &JSTextField::SetSelectionMenuHidden);
    JSClass<JSTextInput>::StaticMethod("customKeyboard", &JSTextField::SetCustomKeyboard);
    JSClass<JSTextInput>::StaticMethod("passwordRules", &JSTextField::SetPasswordRules);
    JSClass<JSTextInput>::StaticMethod("enableAutoFill", &JSTextField::SetEnableAutoFill);
    JSClass<JSTextInput>::StaticMethod("cancelButton", &JSTextField::SetCancelButton);
    JSClass<JSTextInput>::StaticMethod("selectAll", &JSTextField::SetSelectAllValue);
    JSClass<JSTextInput>::StaticMethod("lineBreakStrategy", &JSTextField::SetLineBreakStrategy);
    JSClass<JSTextInput>::StaticMethod("showCounter", &JSTextField::SetShowCounter);
    JSClass<JSTextInput>::StaticMethod("fontFeature", &JSTextField::SetFontFeature);
    JSClass<JSTextInput>::StaticMethod("decoration", &JSTextField::SetDecoration);
    JSClass<JSTextInput>::StaticMethod("minFontSize", &JSTextField::SetMinFontSize);
    JSClass<JSTextInput>::StaticMethod("maxFontSize", &JSTextField::SetMaxFontSize);
    JSClass<JSTextInput>::StaticMethod("heightAdaptivePolicy", &JSTextField::SetHeightAdaptivePolicy);
    JSClass<JSTextInput>::StaticMethod("letterSpacing", &JSTextField::SetLetterSpacing);
    JSClass<JSTextInput>::StaticMethod("lineHeight", &JSTextField::SetLineHeight);
    JSClass<JSTextInput>::StaticMethod("halfLeading", &JSTextField::SetHalfLeading);
    JSClass<JSTextInput>::StaticMethod("textOverflow", &JSTextField::SetTextOverflow);
    JSClass<JSTextInput>::StaticMethod("textIndent", &JSTextField::SetTextIndent);
    JSClass<JSTextInput>::StaticMethod("showPassword", &JSTextField::ShowPasswordText);

    JSClass<JSTextInput>::StaticMethod("onWillInsert", &JSTextField::OnWillInsertValue);
    JSClass<JSTextInput>::StaticMethod("onDidInsert", &JSTextField::OnDidInsertValue);
    JSClass<JSTextInput>::StaticMethod("onWillDelete", &JSTextField::OnWillDelete);
    JSClass<JSTextInput>::StaticMethod("onDidDelete", &JSTextField::OnDidDelete);
    JSClass<JSTextInput>::StaticMethod("editMenuOptions", &JSTextField::EditMenuOptions);
    JSClass<JSTextInput>::StaticMethod("enablePreviewText", &JSTextField::SetEnablePreviewText);
    JSClass<JSTextInput>::StaticMethod("enableHapticFeedback", &JSTextField::SetEnableHapticFeedback);
    JSClass<JSTextInput>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSTextInput::Create(const JSCallbackInfo& info)
{
    JSTextField::CreateTextInput(info);
    JSTextInputTheme::ApplyTheme();
}

void JSTextInputController::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextEditableController>::Declare("TextInputController");
    JSTextEditableController::JSBind(globalObj);
}
} // namespace OHOS::Ace::Framework
