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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SPAN_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SPAN_H

#include "core/components/text_span/text_span_component.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

class JSSpan : public JSContainerBase {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);
    static void SetFont(const JSCallbackInfo& info);
    static void SetFontSize(const JSCallbackInfo& info);
    static void SetFontWeight(const JSCallbackInfo& info);
    static void SetTextColor(const JSCallbackInfo& info);
    static void SetTextShadow(const JSCallbackInfo& info);
    static void SetFontStyle(int32_t value);
    static void SetFontFamily(const JSCallbackInfo& info);
    static void SetLetterSpacing(const JSCallbackInfo& info);
    static void SetTextCase(int32_t value);
    static void SetDecoration(const JSCallbackInfo& info);
    static void SetBaselineOffset(const JSCallbackInfo& info);
    static void JsOnClick(const JSCallbackInfo& info);
    static void JsRemoteMessage(const JSCallbackInfo& info);
    static void SetLineHeight(const JSCallbackInfo& info);
    static void SetAccessibilityText(const JSCallbackInfo& info);
    static void SetAccessibilityDescription(const JSCallbackInfo& info);
    static void SetAccessibilityLevel(const JSCallbackInfo& info);
    static void SetOnHover(const JSCallbackInfo& info);

    static void RegisterSpanFontInfo(const JSCallbackInfo& info, Font& font);
    static void RegisterDecorationColorResource(JSRef<JSVal>& colorValue);
    template<typename T>
    static void RegisterSpanResource(const std::string& key, const RefPtr<ResourceObject>& resObj, T value);
    static void UnregisterSpanResource(const std::string& key);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SPAN_H
