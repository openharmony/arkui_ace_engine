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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_STYLE_STRING_JS_SPAN_STRING_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_STYLE_STRING_JS_SPAN_STRING_H

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/bindings_defines.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::Framework {

class JSSpanString : public virtual AceType {
    DECLARE_ACE_TYPE(JSSpanString, AceType)

public:
    JSSpanString() = default;
    ~JSSpanString() override = default;
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSSpanString* spanString);
    static void JSBind(BindingTarget globalObj);
    void GetString(const JSCallbackInfo& info);
    void GetLength(const JSCallbackInfo& info);
    void SetLength(const JSCallbackInfo& info);
    void IsEqualToSpanString(const JSCallbackInfo& info);
    void GetSubSpanString(const JSCallbackInfo& info);
    static std::vector<RefPtr<SpanBase>> ParseJsSpanBaseVector(JSRef<JSObject> obj, int32_t maxLength);
    static JSRef<JSObject> CreateJsSpanBaseObject(const RefPtr<SpanBase>& spanObject);
    static JSRef<JSObject> CreateJsFontSpan(const RefPtr<SpanBase>& spanObject);
    static JSRef<JSObject> CreateJsDecorationSpan(const RefPtr<SpanBase>& spanObject);
    static JSRef<JSObject> CreateJsLetterSpacingSpan(const RefPtr<SpanBase>& spanObject);
    static JSRef<JSObject> CreateJsBaselineOffsetSpan(const RefPtr<SpanBase>& spanObject);
    static JSRef<JSObject> CreateJsGestureSpan(const RefPtr<SpanBase>& spanObject);
    static JSRef<JSObject> CreateJsTextShadowSpan(const RefPtr<SpanBase>& spanObject);
    static RefPtr<SpanBase> ParseJsSpanBase(int32_t start, int32_t length, SpanType type, JSRef<JSObject> obj);
    static RefPtr<SpanBase> ParseJsFontSpan(int32_t start, int32_t length, JSRef<JSObject> obj);
    static RefPtr<SpanBase> ParseJsDecorationSpan(int32_t start, int32_t length, JSRef<JSObject> obj);
    static RefPtr<SpanBase> ParseJsLetterSpacingSpan(int32_t start, int32_t length, JSRef<JSObject> obj);
    static RefPtr<SpanBase> ParseJsBaselineOffsetSpan(int32_t start, int32_t length, JSRef<JSObject> obj);
    static RefPtr<SpanBase> ParseJsGestureSpan(int32_t start, int32_t length, JSRef<JSObject> obj);
    static RefPtr<SpanBase> ParseJsTextShadowSpan(int32_t start, int32_t length, JSRef<JSObject> obj);
    static bool CheckSpanType(const int32_t& type);
    bool CheckParameters(const int32_t& start, const int32_t& length);
    void GetSpans(const JSCallbackInfo& info);
    const RefPtr<SpanString>& GetController();
    void SetController(const RefPtr<SpanString>& spanString);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSSpanString);
    RefPtr<SpanString> spanString_;
};

class JSMutableSpanString final : public JSSpanString {
    DECLARE_ACE_TYPE(JSMutableSpanString, AceType)

public:
    JSMutableSpanString() = default;
    ~JSMutableSpanString() override = default;
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSMutableSpanString* spanString);
    static void JSBind(BindingTarget globalObj);

    void ReplaceString(const JSCallbackInfo& info);
    void InsertString(const JSCallbackInfo& info);
    void RemoveString(const JSCallbackInfo& info);
    void ReplaceSpan(const JSCallbackInfo& info);
    void AddSpan(const JSCallbackInfo& info);
    void RemoveSpan(const JSCallbackInfo& info);
    void RemoveSpans(const JSCallbackInfo& info);
    void ClearAllSpans();
    void ReplaceSpanString(const JSCallbackInfo& info);
    void InsertSpanString(const JSCallbackInfo& info);
    void AppendSpanString(const JSCallbackInfo& info);
    WeakPtr<MutableSpanString>& GetMutableController();
    void SetMutableController(const RefPtr<MutableSpanString>& mutableSpanString);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSMutableSpanString);
    WeakPtr<MutableSpanString> mutableSpanString_;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_STYLE_STRING_JS_SPAN_STRING_H