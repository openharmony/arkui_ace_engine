/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_STYLE_STRING_JS_SPAN_OBJECT_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_STYLE_STRING_JS_SPAN_OBJECT_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/bindings_defines.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "core/components_ng/pattern/text/span/span_object.h"

namespace OHOS::Ace::Framework {

class JSFontSpan : public virtual AceType {
    DECLARE_ACE_TYPE(JSFontSpan, AceType)

public:
    JSFontSpan() = default;
    ~JSFontSpan() override = default;
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSFontSpan* fontSpan);
    static void JSBind(BindingTarget globalObj);
    static RefPtr<FontSpan> ParseJsFontSpan(const JSRef<JSObject>& obj);
    static void ParseJsFontColor(const JSRef<JSObject>& obj, Font& font);
    static void ParseJsFontSize(const JSRef<JSObject>& obj, Font& font);
    static void ParseJsFontWeight(const JSRef<JSObject>& obj, Font& font);
    static void ParseJsFontFamily(const JSRef<JSObject>& obj, Font& font);
    static void ParseJsFontStyle(const JSRef<JSObject>& obj, Font& font);
    void GetFontColor(const JSCallbackInfo& info);
    void SetFontColor(const JSCallbackInfo& info);
    void GetFontFamily(const JSCallbackInfo& info);
    void SetFontFamily(const JSCallbackInfo& info);
    void GetFontSize(const JSCallbackInfo& info);
    void SetFontSize(const JSCallbackInfo& info);
    void GetFontWeight(const JSCallbackInfo& info);
    void SetFontWeight(const JSCallbackInfo& info);
    void GetFontStyle(const JSCallbackInfo& info);
    void SetFontStyle(const JSCallbackInfo& info);

    RefPtr<FontSpan>& GetFontSpan();
    void SetFontSpan(const RefPtr<FontSpan>& fontSpan);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSFontSpan);
    RefPtr<FontSpan> fontSpan_;
};

class JSGestureSpan : public virtual AceType {
    DECLARE_ACE_TYPE(JSGestureSpan, AceType)

public:
    JSGestureSpan() = default;
    ~JSGestureSpan() override = default;
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSGestureSpan* gestureSpan);
    static void JSBind(BindingTarget globalObj);
    static RefPtr<GestureSpan> ParseJSGestureSpan(const JSCallbackInfo& args);

    RefPtr<GestureSpan>& GetGestureSpan();
    void SetGestureSpan(const RefPtr<GestureSpan>& gestureSpan);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSGestureSpan);
    RefPtr<GestureSpan> gestureSpan_;
};
class JSTextShadowSpan : public virtual AceType {
    DECLARE_ACE_TYPE(JSTextShadowSpan, AceType)

public:
    JSTextShadowSpan() = default;
    ~JSTextShadowSpan() override = default;
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSTextShadowSpan* textShadowSpan);
    static void JSBind(BindingTarget globalObj);
    static RefPtr<TextShadowSpan> ParseJSTextShadowSpan(const JSRef<JSObject>& obj);
    void GetTextShadow(const JSCallbackInfo& info);
    void SetTextShadow(const JSCallbackInfo& info);

    RefPtr<TextShadowSpan>& GetTextShadowSpan();
    void SetTextShadowSpan(const RefPtr<TextShadowSpan>& textShadowSpan);
private:
    ACE_DISALLOW_COPY_AND_MOVE(JSTextShadowSpan);
    RefPtr<TextShadowSpan> textShadowSpan_;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_STYLE_STRING_JS_SPAN_OBJECT_H