/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/core/components/text_field/text_field_component.h"
#include "frameworks/core/components/text_field/text_field_controller.h"
#include "frameworks/core/components/text_field/textfield_theme.h"
#include "frameworks/core/components_ng/pattern/text/text_menu_extension.h"
#include "frameworks/core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_keyboard_common_type.h"

namespace OHOS::Ace::Framework {

class JSTextField : public JSViewAbstract {
public:
    static bool ParseText(const JSRef<JSObject>& textValue, std::optional<std::u16string>& value,
    JSRef<JSVal>& changeEventVal, std::u16string& text, RefPtr<ResourceObject>& textObject);
    static void CreateTextInput(const JSCallbackInfo& info);
    static void CreateTextArea(const JSCallbackInfo& info);
    static void SetType(const JSCallbackInfo& info);
    static void SetContentType(const JSCallbackInfo& info);
    static void SetPlaceholderColor(const JSCallbackInfo& info);
    static void SetPlaceholderFont(const JSCallbackInfo& info);
    static void SetEnterKeyType(const JSCallbackInfo& info);
    static void SetTextAlign(int32_t value);
    static void SetLineBreakStrategy(const JSCallbackInfo& info);
    static void SetCaretColor(const JSCallbackInfo& info);
    static void SetCaretStyle(const JSCallbackInfo& info);
    static void SetCaretPosition(const JSCallbackInfo& info);
    static void SetSelectedBackgroundColor(const JSCallbackInfo& info);
    static void SetMaxLength(const JSCallbackInfo& info);
    static void SetEllipsisMode(const JSCallbackInfo& info);
    static void SetFontSize(const JSCallbackInfo& info);
    static void SetFontWeight(const JSCallbackInfo& info);
    static void SetMinFontScale(const JSCallbackInfo& info);
    static void SetMaxFontScale(const JSCallbackInfo& info);
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
    static void JsMargin(const JSCallbackInfo& info);
    static Edge GetOldPadding(const JSCallbackInfo& info);
    static NG::PaddingProperty GetNewPadding(const JSCallbackInfo& info, bool& hasRegist);
    static NG::PaddingProperty SetPaddings(const std::optional<CalcDimension>& top,
        const std::optional<CalcDimension>& bottom, const std::optional<CalcDimension>& left,
        const std::optional<CalcDimension>& right);
    static void JsBorder(const JSCallbackInfo& info);
    static void JsBorderWidth(const JSCallbackInfo& info);
    static void JsBorderColor(const JSCallbackInfo& info);
    static void JsBorderStyle(const JSCallbackInfo& info);

    static void GetBorderRadiusByLengthMetrics(const char* key,
        JSRef<JSObject>& object, std::optional<CalcDimension>& radius);
    static bool ParseAllBorderRadiuses(JSRef<JSObject>& object, CalcDimension& topLeft,
        CalcDimension& topRight, CalcDimension& bottomLeft, CalcDimension& bottomRight);
    static void ParseBorderRadius(const JSRef<JSVal>& args);
    static void JsBorderRadius(const JSCallbackInfo& info);
    static void JsHoverEffect(const JSCallbackInfo& info);
    static void SetOnEditChanged(const JSCallbackInfo& info);
    static void SetOnSubmit(const JSCallbackInfo& info);
    static JSRef<JSVal> CreateJsOnChangeObj(const PreviewText& previewText);
    static void SetOnChange(const JSCallbackInfo& info);
    static void SetOnTextSelectionChange(const JSCallbackInfo& info);
    static void SetOnSecurityStateChange(const JSCallbackInfo& info);
    static void SetOnContentScroll(const JSCallbackInfo& info);
    static void SetOnCopy(const JSCallbackInfo& info);
    static void SetOnCut(const JSCallbackInfo& info);
    static void SetOnPaste(const JSCallbackInfo& info);
    static void SetOnClick(const JSCallbackInfo& info);
    static void SetCopyOption(const JSCallbackInfo& info);
    static JSRef<JSVal> CreateJsAboutToIMEInputObj(const InsertValueInfo& insertValue);
    static JSRef<JSVal> CreateJsDeleteToIMEObj(const DeleteValueInfo& deleteValueInfo);
    static void OnWillInsertValue(const JSCallbackInfo& info);
    static void OnDidInsertValue(const JSCallbackInfo& info);
    static void OnWillDelete(const JSCallbackInfo& info);
    static void OnDidDelete(const JSCallbackInfo& info);
    static void UpdateDecoration(const RefPtr<BoxComponent>& boxComponent, const RefPtr<TextFieldComponent>& component,
        const Border& boxBorder, const RefPtr<TextFieldTheme>& textFieldTheme);
    static void SetForegroundColor(const JSCallbackInfo& info);
    static void SetPasswordIcon(const JSCallbackInfo& info);
    static void SetShowUnit(const JSCallbackInfo& info);
    static void SetShowCounter(const JSCallbackInfo& info);
    static void SetShowError(const JSCallbackInfo& info);
    static void SetBarState(const JSCallbackInfo& info);
    static void SetMaxLines(const JSCallbackInfo& info);
    static void SetWordBreak(const JSCallbackInfo& info);

    static void SetShowUnderline(const JSCallbackInfo& info);
    static void SetUnderlineColor(const JSCallbackInfo& info);
    static void SetEnableKeyboardOnFocus(const JSCallbackInfo& info);
    static void SetSelectionMenuHidden(const JSCallbackInfo& info);
    static bool ParseJsCustomKeyboardBuilder(
        const JSCallbackInfo& info, int32_t index, std::function<void()>& buildFunc);
    static void SetCustomKeyboard(const JSCallbackInfo& info);

    static void SetPasswordRules(const JSCallbackInfo& info);
    static void SetEnableAutoFill(const JSCallbackInfo& info);
    static void SetEnableAutoFillAnimation(const JSCallbackInfo& info);
    static void ShowPasswordText(const JSCallbackInfo& info);
    static JSRef<JSVal> CreateJSTextCommonEvent(NG::TextCommonEvent& event);
    static void CreateJsTextFieldCommonEvent(const JSCallbackInfo& info);
    static Local<JSValueRef> JsKeepEditableState(panda::JsiRuntimeCallInfo *info);
    static void SetCancelButton(const JSCallbackInfo& info);
    static void SetSelectAllValue(const JSCallbackInfo& info);
    static void SetFontFeature(const JSCallbackInfo& info);
    static void SetDecoration(const JSCallbackInfo& info);
    static void SetMinFontSize(const JSCallbackInfo& info);
    static void SetMaxFontSize(const JSCallbackInfo& info);
    static void SetHeightAdaptivePolicy(int32_t value);
    static void SetLetterSpacing(const JSCallbackInfo& info);
    static void SetLineHeight(const JSCallbackInfo& info);
    static void SetHalfLeading(const JSCallbackInfo& info);
    static void SetLineSpacing(const JSCallbackInfo& info);
    static void SetTextOverflow(const JSCallbackInfo& info);
    static void SetTextIndent(const JSCallbackInfo& info);
    static void EditMenuOptions(const JSCallbackInfo& info);
    static void SetEnablePreviewText(const JSCallbackInfo& info);
    static void SetEnableHapticFeedback(const JSCallbackInfo& info);
    static void SetCapitalizationMode(const JSCallbackInfo& info);
    static void SetStopBackPress(const JSCallbackInfo& info);
    static void SetKeyboardAppearance(const JSCallbackInfo& info);
    static JSRef<JSVal> CreateJsOnWillChangeObj(const ChangeValueInfo& changeValueInfo);
    static void SetOnWillChange(const JSCallbackInfo& info);
    static void SetStrokeWidth(const JSCallbackInfo& info);
    static void SetStrokeColor(const JSCallbackInfo& info);
    static void SetEnableAutoSpacing(const JSCallbackInfo& info);
    static NG::KeyboardAppearanceConfig ParseKeyboardAppearanceConfig(const JSRef<JSObject>& obj);
    static void SetOnWillAttachIME(const JSCallbackInfo& info);
    static void SetKeyboardAppearanceConfig(const JSCallbackInfo& info);
    static void ParseOnIconSrc(const JSRef<JSVal>& showVal, PasswordIcon& passwordIcon);
    static void ParseOffIconSrc(const JSRef<JSVal>& showVal, PasswordIcon& passwordIcon);
    static void SetUnderlineColorObject(const JSRef<JSVal>& jsValue);
    static void UnregisterResource(const std::string& key);

private:
    static void SetCancelIconColorAndIconSrc(const JSRef<JSObject>& iconParam);
    static void SetCancelDefaultIcon();
    static void ResetCancelIcon();
    static void SetCancelSymbolIcon(const JSCallbackInfo& info);
    static void SetLayoutPolicy(const JSRef<JSVal>& jsValue, bool isWidth);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXTINPUT_H
