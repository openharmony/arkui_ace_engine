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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXTFIELD_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXTFIELD_H

#include "bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/core/components/text_field/text_field_component.h"
#include "frameworks/core/components/text_field/text_field_controller.h"
#include "frameworks/core/components/text_field/textfield_theme.h"
#include "frameworks/core/components_ng/pattern/text/text_menu_extension.h"

namespace OHOS::Ace::Framework {

class JSTextField : public JSViewAbstract {
public:
    static void CreateTextInput(const JSCallbackInfo& info);
    static void CreateTextArea(const JSCallbackInfo& info);
    static void SetType(const JSCallbackInfo& info);
    static void SetPlaceholderColor(const JSCallbackInfo& info);
    static void SetPlaceholderFont(const JSCallbackInfo& info);
    static void SetEnterKeyType(const JSCallbackInfo& info);
    static void SetTextAlign(int32_t value);
    static void SetCaretColor(const JSCallbackInfo& info);
    static void SetCaretStyle(const JSCallbackInfo &info);
    static void SetCaretPosition(const JSCallbackInfo& info);
    static void SetSelectedBackgroundColor(const JSCallbackInfo& info);
    static void SetMaxLength(const JSCallbackInfo& info);
    static void SetFontSize(const JSCallbackInfo& info);
    static void SetFontWeight(const std::string& value);
    static void SetTextColor(const JSCallbackInfo& info);
    static void SetFontStyle(int32_t value);
    static void SetFontFamily(const JSCallbackInfo& info);
    static void SetInputFilter(const JSCallbackInfo& info);
    static void SetInputStyle(const JSCallbackInfo& info);
    static void SetShowPasswordIcon(const JSCallbackInfo& info);
    static void SetBackgroundColor(const JSCallbackInfo& info);
    static void JsHeight(const JSCallbackInfo& info);
    static void JsWidth(const JSCallbackInfo& info);
    static void JsPadding(const JSCallbackInfo& info);
    static Edge GetOldPadding(const JSCallbackInfo& info);
    static NG::PaddingProperty GetNewPadding(const JSCallbackInfo& info);
    static NG::PaddingProperty SetPaddings(const std::optional<CalcDimension>& top,
        const std::optional<CalcDimension>& bottom, const std::optional<CalcDimension>& left,
        const std::optional<CalcDimension>& right);
    static void JsBorder(const JSCallbackInfo& info);
    static void JsBorderWidth(const JSCallbackInfo& info);
    static void JsBorderColor(const JSCallbackInfo& info);
    static void JsBorderStyle(const JSCallbackInfo& info);
    static void JsBorderRadius(const JSCallbackInfo& info);
    static void JsHoverEffect(const JSCallbackInfo& info);
    static void SetOnEditChanged(const JSCallbackInfo& info);
    static void SetOnSubmit(const JSCallbackInfo& info);
    static void SetOnChange(const JSCallbackInfo& info);
    static void SetOnTextSelectionChange(const JSCallbackInfo& info);
    static void SetOnContentScroll(const JSCallbackInfo& info);
    static void SetOnCopy(const JSCallbackInfo& info);
    static void SetOnCut(const JSCallbackInfo& info);
    static void SetOnPaste(const JSCallbackInfo& info);
    static void SetOnClick(const JSCallbackInfo& info);
    static void SetCopyOption(const JSCallbackInfo& info);
    static void UpdateDecoration(const RefPtr<BoxComponent>& boxComponent, const RefPtr<TextFieldComponent>& component,
        const Border& boxBorder, const RefPtr<TextFieldTheme>& textFieldTheme);
    static void JsMenuOptionsExtension(const JSCallbackInfo& info);
    static void SetForegroundColor(const JSCallbackInfo& info);
    static void SetPasswordIcon(const JSCallbackInfo& info);
    static void SetShowUnit(const JSCallbackInfo& info);
    static void SetShowCounter(const JSCallbackInfo& info);
    static void SetShowError(const JSCallbackInfo& info);
    static void SetBarState(const JSCallbackInfo& info);
    static void SetMaxLines(const JSCallbackInfo& info);

    static void SetShowUnderline(const JSCallbackInfo& info);
    static void SetEnableKeyboardOnFocus(const JSCallbackInfo& info);
    static void SetSelectionMenuHidden(const JSCallbackInfo& info);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXTINPUT_H
