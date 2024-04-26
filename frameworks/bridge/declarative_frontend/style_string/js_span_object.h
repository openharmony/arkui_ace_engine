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

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/bindings_defines.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"
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

    const RefPtr<FontSpan>& GetFontSpan();
    void SetFontSpan(const RefPtr<FontSpan>& fontSpan);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSFontSpan);
    RefPtr<FontSpan> fontSpan_;
};

class JSDecorationSpan : public virtual AceType {
    DECLARE_ACE_TYPE(JSDecorationSpan, AceType)

public:
    JSDecorationSpan() = default;
    ~JSDecorationSpan() override = default;
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSDecorationSpan* decorationSpan);
    static void JSBind(BindingTarget globalObj);
    static RefPtr<DecorationSpan> ParseJsDecorationSpan(const JSRef<JSObject>& obj);
    void GetTextDecorationType(const JSCallbackInfo& info);
    void SetTextDecorationType(const JSCallbackInfo& info);
    void GetTextDecorationColor(const JSCallbackInfo& info);
    void SetTextDecorationColor(const JSCallbackInfo& info);
    void GetTextDecorationStyle(const JSCallbackInfo& info);
    void SetTextDecorationStyle(const JSCallbackInfo& info);

    RefPtr<DecorationSpan>& GetDecorationSpan();
    void SetDecorationSpan(const RefPtr<DecorationSpan>& decorationSpan);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSDecorationSpan);
    RefPtr<DecorationSpan> decorationSpan_;
};

class JSBaselineOffsetSpan : public virtual AceType {
    DECLARE_ACE_TYPE(JSBaselineOffsetSpan, AceType)

public:
    JSBaselineOffsetSpan() = default;
    ~JSBaselineOffsetSpan() override = default;
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSBaselineOffsetSpan* baselineOffsetSpan);
    static void JSBind(BindingTarget globalObj);
    static RefPtr<BaselineOffsetSpan> ParseJSBaselineOffsetSpan(const JSRef<JSObject>& obj);
    void GetBaselineOffset(const JSCallbackInfo& info);
    void SetBaselineOffset(const JSCallbackInfo& info);

    RefPtr<BaselineOffsetSpan>& GetBaselineOffsetSpan();
    void SetBaselineOffsetSpan(const RefPtr<BaselineOffsetSpan>& baselineOffsetSpan);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSBaselineOffsetSpan);
    RefPtr<BaselineOffsetSpan> baselineOffsetSpan_;
};

class JSLetterSpacingSpan : public virtual AceType {
    DECLARE_ACE_TYPE(JSLetterSpacingSpan, AceType)

public:
    JSLetterSpacingSpan() = default;
    ~JSLetterSpacingSpan() override = default;
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSLetterSpacingSpan* letterSpacingSpan);
    static void JSBind(BindingTarget globalObj);
    static RefPtr<LetterSpacingSpan> ParseJSLetterSpacingSpan(const JSRef<JSObject>& obj);
    void GetLetterSpacing(const JSCallbackInfo& info);
    void SetLetterSpacing(const JSCallbackInfo& info);

    RefPtr<LetterSpacingSpan>& GetLetterSpacingSpan();
    void SetLetterSpacingSpan(const RefPtr<LetterSpacingSpan>& letterSpacingSpan);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSLetterSpacingSpan);
    RefPtr<LetterSpacingSpan> letterSpacingSpan_;
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

class JSImageAttachment : public virtual AceType {
    DECLARE_ACE_TYPE(JSImageAttachment, AceType)

public:
    JSImageAttachment() = default;
    ~JSImageAttachment() override = default;
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSImageAttachment* imageSpan);
    static void JSBind(BindingTarget globalObj);
    static RefPtr<ImageSpan> ParseJsImageSpan(const JSRef<JSObject>& obj);
    void GetImageSrc(const JSCallbackInfo& info);
    void SetImageSrc(const JSCallbackInfo& info) {}
    void GetImageSize(const JSCallbackInfo& info);
    void SetImageSize(const JSCallbackInfo& info) {}
    void GetImageVerticalAlign(const JSCallbackInfo& info);
    void SetImageVerticalAlign(const JSCallbackInfo& info) {}
    void GetImageObjectFit(const JSCallbackInfo& info);
    void SetImageObjectFit(const JSCallbackInfo& info) {}
    void GetImageLayoutStyle(const JSCallbackInfo& info);
    void SetImageLayoutStyle(const JSCallbackInfo& info) {}

    const RefPtr<ImageSpan>& GetImageSpan();
    void SetImageSpan(const RefPtr<ImageSpan>& imageSpan);
    const ImageSpanOptions& GetImageOptions() const;

private:
    static ImageSpanOptions CreateImageOptions(const JSRef<JSObject>& obj);
    static ImageSpanAttribute ParseJsImageSpanAttribute(const JSRef<JSObject>& obj);
    static JSRef<JSObject> CreateEdge(const NG::PaddingPropertyT<NG::CalcLength>& edge);
    static JSRef<JSObject> CreateBorderRadius(const NG::BorderRadiusProperty& borderRadius);

    ACE_DISALLOW_COPY_AND_MOVE(JSImageAttachment);
    RefPtr<ImageSpan> imageSpan_;
};

class JSCustomSpan : public CustomSpan {
    DECLARE_ACE_TYPE(JSCustomSpan, CustomSpan)

public:
    JSCustomSpan() = default;
    JSCustomSpan(JSRef<JSObject> customSpanObj, const JSCallbackInfo& args);
    JSCustomSpan(JSRef<JSObject> customSpanObj,
        std::optional<std::function<CustomSpanMetrics(CustomSpanMeasureInfo)>> onMeasure,
        std::optional<std::function<void(NG::DrawingContext&, CustomSpanOptions)>> onDraw, int32_t start, int32_t end);
    ~JSCustomSpan() override = default;
    static std::function<CustomSpanMetrics(CustomSpanMeasureInfo)> ParseOnMeasureFunc(
        const RefPtr<JsFunction>& jsDraw, const JSExecutionContext& execCtx);
    static std::function<void(NG::DrawingContext&, CustomSpanOptions)> ParseOnDrawFunc(
        const RefPtr<JsFunction>& jsDraw, const JSExecutionContext& execCtx);

    bool IsAttributesEqual(const RefPtr<SpanBase>& other) const override;
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override;
    void SetJsCustomSpanObject(const JSRef<JSObject>& customSpanObj);
    JSRef<JSObject>& GetJsCustomSpanObject();

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSCustomSpan);
    JSRef<JSObject> customSpanObj_;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_STYLE_STRING_JS_SPAN_OBJECT_H