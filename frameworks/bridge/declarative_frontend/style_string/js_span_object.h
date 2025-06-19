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

#include <optional>

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/bindings_defines.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/text_model.h"

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
    static void ParseJsStrokeWidth(const JSRef<JSObject>& obj, Font& font);
    static void ParseJsStrokeColor(const JSRef<JSObject>& obj, Font& font);
    static void GetStrokeColorFallback(const JSRef<JSObject>& obj,
        const RefPtr<TextTheme>& theme, Color& color);
    static void ParseJsSuperscript(const JSRef<JSObject>& obj, Font& font);
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
    void GetStrokeWidth(const JSCallbackInfo& info);
    void SetStrokeWidth(const JSCallbackInfo& info);
    void GetStrokeColor(const JSCallbackInfo& info);
    void SetStrokeColor(const JSCallbackInfo& info);
    void GetSuperscript(const JSCallbackInfo& info);
    void SetSuperscript(const JSCallbackInfo& info);

    const RefPtr<FontSpan>& GetFontSpan();
    void SetFontSpan(const RefPtr<FontSpan>& fontSpan);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSFontSpan);
    RefPtr<FontSpan> fontSpan_;
};

class JSParagraphStyleSpan : public virtual AceType {
    DECLARE_ACE_TYPE(JSParagraphStyleSpan, AceType)

public:
    JSParagraphStyleSpan() = default;
    ~JSParagraphStyleSpan() override = default;
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSParagraphStyleSpan* paragraphStyleSpan);
    static void JSBind(BindingTarget globalObj);
    static RefPtr<ParagraphStyleSpan> ParseJsParagraphStyleSpan(const JSRef<JSObject>& obj);
    static void ParseJsTextAlign(const JSRef<JSObject>& obj, SpanParagraphStyle& paragraphStyle);
    static void ParseJsTextVerticalAlign(const JSRef<JSObject>& obj, SpanParagraphStyle& paragraphStyle);
    static void ParseJsTextIndent(const JSRef<JSObject>& obj, SpanParagraphStyle& paragraphStyle);
    static void ParseJsMaxLines(const JSRef<JSObject>& obj, SpanParagraphStyle& paragraphStyle);
    static void ParseJsTextOverflow(const JSRef<JSObject>& obj, SpanParagraphStyle& paragraphStyle);
    static void ParseJsWordBreak(const JSRef<JSObject>& obj, SpanParagraphStyle& paragraphStyle);
    static void ParseJsLeadingMargin(const JSRef<JSObject>& obj, SpanParagraphStyle& paragraphStyle);
    static void ParseParagraphSpacing(const JSRef<JSObject>& obj, SpanParagraphStyle& paragraphStyle);
    static void ParseLeadingMarginPixelMap(const JSRef<JSObject>& leadingMarginObject,
        std::optional<NG::LeadingMargin>& margin, const JsiRef<JsiValue>& leadingMargin);
    void GetTextAlign(const JSCallbackInfo& info);
    void SetTextAlign(const JSCallbackInfo& info);
    void GetTextVerticalAlign(const JSCallbackInfo& info);
    void SetTextVerticalAlign(const JSCallbackInfo& info);
    void SetTextIndent(const JSCallbackInfo& info);
    void GetTextIndent(const JSCallbackInfo& info);
    void SetMaxLines(const JSCallbackInfo& info);
    void GetMaxLines(const JSCallbackInfo& info);
    void SetOverflow(const JSCallbackInfo& info);
    void GetOverflow(const JSCallbackInfo& info);
    void SetWordBreak(const JSCallbackInfo& info);
    void GetWordBreak(const JSCallbackInfo& info);
    void SetLeadingMargin(const JSCallbackInfo& info);
    void GetLeadingMargin(const JSCallbackInfo& info);
    void GetParagraphSpacing(const JSCallbackInfo& info);
    void SetParagraphSpacing(const JSCallbackInfo& info);

    static bool IsPixelMap(const JSRef<JSVal>& jsValue);

    RefPtr<ParagraphStyleSpan>& GetParagraphStyleSpan();
    void SetParagraphStyleSpan(const RefPtr<ParagraphStyleSpan>& paragraphStyleSpan);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSParagraphStyleSpan);
    RefPtr<ParagraphStyleSpan> paragraphStyleSpan_;
};

class JSDecorationSpan : public virtual AceType {
    DECLARE_ACE_TYPE(JSDecorationSpan, AceType)

public:
    JSDecorationSpan() = default;
    ~JSDecorationSpan() override = default;
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSDecorationSpan* decorationSpan);
    static void JSBind(BindingTarget globalObj);
    static RefPtr<DecorationSpan> ParseJsDecorationSpan(const JSCallbackInfo& args);
    static TextDecorationOptions ParseJsDecorationOptions(const JSRef<JSObject>& obj);
    void GetTextDecorationType(const JSCallbackInfo& info);
    void SetTextDecorationType(const JSCallbackInfo& info);
    void GetTextDecorationColor(const JSCallbackInfo& info);
    void SetTextDecorationColor(const JSCallbackInfo& info);
    void GetTextDecorationStyle(const JSCallbackInfo& info);
    void SetTextDecorationStyle(const JSCallbackInfo& info);
    void GetLineThicknessScale(const JSCallbackInfo& info);
    void SetLineThicknessScale(const JSCallbackInfo& info);
    void GetTextDecorationOptions(const JSCallbackInfo& info);
    void SetTextDecorationOptions(const JSCallbackInfo& info);

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
class JSBackgroundColorSpan : public virtual AceType {
    DECLARE_ACE_TYPE(JSBackgroundColorSpan, AceType)

public:
    JSBackgroundColorSpan() = default;
    ~JSBackgroundColorSpan() override = default;
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSBackgroundColorSpan* backgroundColorSpan);
    static void JSBind(BindingTarget globalObj);
    static RefPtr<BackgroundColorSpan> ParseJSBackgroundColorSpan(const JSCallbackInfo& info);
    void GetBackgroundColor(const JSCallbackInfo& info);
    void SetBackgroundColor(const JSCallbackInfo& info);

    RefPtr<BackgroundColorSpan>& GetBackgroundColorSpan();
    void SetBackgroundColorSpan(const RefPtr<BackgroundColorSpan>& backgroundColorSpan);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSBackgroundColorSpan);
    RefPtr<BackgroundColorSpan> backgroundColorSpan_;
};
class JSLineHeightSpan : public virtual AceType {
    DECLARE_ACE_TYPE(JSLineHeightSpan, AceType)

public:
    JSLineHeightSpan() = default;
    ~JSLineHeightSpan() override = default;
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSLineHeightSpan* textShadowSpan);
    static void JSBind(BindingTarget globalObj);
    static RefPtr<LineHeightSpan> ParseJSLineHeightSpan(const JSRef<JSObject>& obj);
    void GetLineHeight(const JSCallbackInfo& info);
    void SetLineHeight(const JSCallbackInfo& info);

    RefPtr<LineHeightSpan>& GetLineHeightSpan();
    void SetLineHeightSpan(const RefPtr<LineHeightSpan>& lineHeightSpan);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSLineHeightSpan);
    RefPtr<LineHeightSpan> lineHeightSpan_;
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
    void GetImageColorFilter(const JSCallbackInfo& info);
    void SetImageColorFilter(const JSCallbackInfo& info) {}

    const RefPtr<ImageSpan>& GetImageSpan();
    void SetImageSpan(const RefPtr<ImageSpan>& imageSpan);
    const ImageSpanOptions& GetImageOptions() const;

private:
    static ImageSpanOptions CreateImageOptions(const JSRef<JSObject>& obj);
    static ImageSpanAttribute ParseJsImageSpanAttribute(const JSRef<JSObject>& obj);
    static JSRef<JSObject> CreateEdge(const NG::PaddingPropertyT<NG::CalcLength>& edge);
    static JSRef<JSObject> CreateBorderRadius(const NG::BorderRadiusProperty& borderRadius);
    static void ParseJsImageSpanSizeAttribute(const JSRef<JSObject>& obj, ImageSpanAttribute& imageStyle);
    static void ParseJsImageSpanColorFilterAttribute(const JSRef<JSObject>& obj, ImageSpanAttribute& imageStyle);
    static void SetImageSpanColorFilterAttribute(ImageSpanAttribute& imageStyle, const std::vector<float>& matrix);

    ACE_DISALLOW_COPY_AND_MOVE(JSImageAttachment);
    RefPtr<ImageSpan> imageSpan_;
};

class JSNativeCustomSpan : public virtual AceType {
    DECLARE_ACE_TYPE(JSNativeCustomSpan, AceType)

public:
    JSNativeCustomSpan() = default;
    ~JSNativeCustomSpan() override = default;
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSNativeCustomSpan* imageSpan);
    static void JSBind(BindingTarget globalObj);
    void Invalidate(const JSCallbackInfo& info);
    void AddStyledString(const WeakPtr<SpanStringBase>& spanString);
    void RemoveStyledString(const WeakPtr<SpanStringBase>& spanString);

private:
    std::set<WeakPtr<SpanStringBase>> spanStringBaseSet_;
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
    void AddStyledString(const WeakPtr<SpanStringBase>& spanString) override;
    void RemoveStyledString(const WeakPtr<SpanStringBase>& spanString) override;

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSCustomSpan);
    RefPtr<JSNativeCustomSpan> customSpan_;
    JSRef<JSObject> customSpanObj_;
};

class JSExtSpan : public ExtSpan {
    DECLARE_ACE_TYPE(JSExtSpan, ExtSpan)

public:
    JSExtSpan() = default;
    JSExtSpan(JSRef<JSObject> customSpanObj);
    JSExtSpan(JSRef<JSObject> customSpanObj, int32_t start, int32_t end);
    ~JSExtSpan() override = default;

    bool IsAttributesEqual(const RefPtr<SpanBase>& other) const override;
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override;
    void SetJsExtSpanObject(const JSRef<JSObject>& extSpanObj);
    JSRef<JSObject>& GetJsExtSpanObject();

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSExtSpan);
    JSRef<JSObject> extSpanObj_;
};

class JSUrlSpan : public virtual AceType {
    DECLARE_ACE_TYPE(JSUrlSpan, AceType)

public:
    JSUrlSpan() = default;
    ~JSUrlSpan() override = default;
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSUrlSpan* urlSpan);
    static void JSBind(BindingTarget globalObj);
    void GetUrlContext(const JSCallbackInfo& info);
    void SetUrlContext(const JSCallbackInfo& info);

    const RefPtr<UrlSpan>& GetUrlSpan();
    void SetUrlSpan(const RefPtr<UrlSpan>& urlSpan);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSUrlSpan);
    RefPtr<UrlSpan> urlContextSpan_;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_STYLE_STRING_JS_SPAN_OBJECT_H