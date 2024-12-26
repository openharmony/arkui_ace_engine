/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SEARCH_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SEARCH_H

#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components/text_field/text_field_controller.h"
#include "frameworks/core/components_ng/pattern/search/search_model_ng.h"

namespace OHOS::Ace::Framework {

class JSSearch : public JSViewAbstract, public JSInteractableView {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);
    static void JSBindMore();

    static void SetEnableKeyboardOnFocus(const JSCallbackInfo& info);
    static void SetSearchButton(const JSCallbackInfo& info);
    static void SetSearchIcon(const JSCallbackInfo& info);
    static void SetCancelButton(const JSCallbackInfo& info);
    static void SetTextColor(const JSCallbackInfo& info);
    static void SetCaret(const JSCallbackInfo& info);
    static void SetPlaceholderColor(const JSCallbackInfo& info);
    static void SetPlaceholderFont(const JSCallbackInfo& info);
    static void SetTextFont(const JSCallbackInfo& info);
    static void SetMinFontScale(const JSCallbackInfo& info);
    static void SetMaxFontScale(const JSCallbackInfo& info);
    static void SetTextAlign(int32_t value);
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
    static void OnSubmit(const JSCallbackInfo& info);
    static JSRef<JSVal> CreateJsOnChangeObj(const PreviewText& previewText);
    static void OnChange(const JSCallbackInfo& info);
    static void SetOnTextSelectionChange(const JSCallbackInfo& info);
    static void SetOnScroll(const JSCallbackInfo& info);
    static void SetHeight(const JSCallbackInfo& info);
    static void SetOnCopy(const JSCallbackInfo& info);
    static void SetOnCut(const JSCallbackInfo& info);
    static void SetOnPaste(const JSCallbackInfo& info);
    static void SetCopyOption(const JSCallbackInfo& info);
    static JSRef<JSVal> CreateJsAboutToIMEInputObj(const InsertValueInfo& insertValue);
    static JSRef<JSVal> CreateJsDeleteToIMEObj(const DeleteValueInfo& deleteValueInfo);
    static void OnWillInsertValue(const JSCallbackInfo& info);
    static void OnDidInsertValue(const JSCallbackInfo& info);
    static void OnWillDelete(const JSCallbackInfo& info);
    static void OnDidDelete(const JSCallbackInfo& info);
    static void SetIconStyle(const JSCallbackInfo& info);
    static void SetSelectionMenuHidden(const JSCallbackInfo& info);
    static void SetCustomKeyboard(const JSCallbackInfo& info);
    static void SetEnterKeyType(const JSCallbackInfo& info);
    static void SetMaxLength(const JSCallbackInfo& info);
    static void SetFontFeature(const JSCallbackInfo& info);
    static void SetType(const JSCallbackInfo& info);
    static void SetDecoration(const JSCallbackInfo& info);
    static void SetMinFontSize(const JSCallbackInfo& info);
    static void SetMaxFontSize(const JSCallbackInfo& info);
    static void SetLetterSpacing(const JSCallbackInfo& info);
    static void SetLineHeight(const JSCallbackInfo& info);
    static void SetHalfLeading(const JSCallbackInfo& info);
    static void SetId(const JSCallbackInfo& info);
    static void SetKey(const std::string& key);
    static void SetSelectedBackgroundColor(const JSCallbackInfo& info);
    static void SetInputFilter(const JSCallbackInfo& info);
    static void SetOnEditChange(const JSCallbackInfo& info);
    static void SetTextIndent(const JSCallbackInfo& info);
    static JSRef<JSVal> CreateJSTextCommonEvent(NG::TextCommonEvent& event);
    static void SetDragPreviewOptions(const JSCallbackInfo& info);
    static void EditMenuOptions(const JSCallbackInfo& info);
    static void SetEnablePreviewText(const JSCallbackInfo& info);
    static void SetSearchDefaultIcon();
    static void SetSearchSymbolIcon(const JSCallbackInfo& info);
    static void SetSearchImageIcon(const JSCallbackInfo& info);
    static void SetCancelDefaultIcon();
    static void SetCancelSymbolIcon(const JSCallbackInfo& info);
    static void SetCancelImageIcon(const JSCallbackInfo& info);
    static void SetEnableHapticFeedback(const JSCallbackInfo& info);
    static void CreateJsSearchCommonEvent(const JSCallbackInfo& info);
};

class JSSearchController final : public Referenced {
public:
    JSSearchController() = default;
    ~JSSearchController() override = default;

    static void JSBind(BindingTarget globalObj);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSSearchController);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SEARCH_H
