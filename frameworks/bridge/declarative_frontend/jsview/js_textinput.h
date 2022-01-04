/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXTINPUT_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXTINPUT_H

namespace OHOS::Ace::Framework {

class JSTextInput : public JSViewAbstract {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);
    static void SetType(const JSCallbackInfo& info);
    static void SetPlaceholderColor(const JSCallbackInfo& info);
    static void SetPlaceholderFont(const JSCallbackInfo& info);
    static void SetEnterKeyType(const JSCallbackInfo& info);
    static void SetCaretColor(const JSCallbackInfo& info);
    static void SetFontSize(const JSCallbackInfo& info);
    static void SetFontWeight(const std::string& value);
    static void SetTextColor(const JSCallbackInfo& info);
    static void SetFontStyle(int32_t value);
    static void SetFontFamily(const JSCallbackInfo& info);
    static void SetOnEditChanged(const JSCallbackInfo& info);
    static void SetOnSubmit(const JSCallbackInfo& info);
    static void SetOnChange(const JSCallbackInfo& info);
    static void SetMaxLength(uint32_t value);
    static void JsHeight(const JSCallbackInfo& info);
    static void JsPadding(const JSCallbackInfo& info);
    static void SetOnCopy(const JSCallbackInfo& info);
    static void SetOnCut(const JSCallbackInfo& info);
    static void SetOnPaste(const JSCallbackInfo& info);

private:
    static void InitDefaultStyle();
};

} // namespace OHOS::Ace::Fremawork
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXTINPUT_H