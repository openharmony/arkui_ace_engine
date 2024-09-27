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

#include "frameworks/bridge/declarative_frontend/style_string/js_span_string.h"

#include <unordered_set>
#include "securec.h"

#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/text/html_utils.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/js_converter.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_image.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/bridge/declarative_frontend/style_string/js_span_object.h"

namespace OHOS::Ace::Framework {
namespace {
struct HtmlConverterAsyncCtx {
    napi_env env = nullptr;
    napi_deferred deferred = nullptr;
    int32_t errCode = -1;
    int32_t instanceId = -1;
};
struct AsyncContext {
    napi_env env = nullptr;
    napi_deferred deferred = nullptr;
    napi_async_work asyncWork;
    std::vector<uint8_t> buffer;
    RefPtr<SpanString> spanString;
    int32_t status = -1;
};

std::unordered_map<int32_t, std::string> ASYNC_ERROR_MAP = {
    { ERROR_CODE_FROM_HTML_CONVERT_ERROR, "Convert error." },
    { ERROR_CODE_STYLED_STRING_CONVERT_ERROR, "Styled string decode error."},
    { ERROR_CODE_PARAM_INVALID, "Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;"
        "2. Incorrect parameter types; 3. Parameter verification failed." }
};

napi_value CreateErrorValue(napi_env env, int32_t errCode, const std::string& errMsg = "")
{
    napi_value code = nullptr;
    std::string codeStr = std::to_string(errCode);
    napi_create_string_utf8(env, codeStr.c_str(), codeStr.length(), &code);
    napi_value msg = nullptr;
    napi_create_string_utf8(env, errMsg.c_str(), errMsg.length(), &msg);
    napi_value error = nullptr;
    napi_create_error(env, code, msg, &error);
    return error;
}

void ProcessPromiseCallback(std::shared_ptr<HtmlConverterAsyncCtx> asyncContext,
    int32_t callbackCode, napi_value spanStr = nullptr)
{
    CHECK_NULL_VOID(asyncContext);
    CHECK_NULL_VOID(asyncContext->env);
    CHECK_NULL_VOID(asyncContext->deferred);
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(asyncContext->env, &scope);
    if (status != napi_ok) {
        return;
    }
    CHECK_NULL_VOID(scope);
    if (callbackCode == ERROR_CODE_NO_ERROR) {
        napi_resolve_deferred(asyncContext->env, asyncContext->deferred, spanStr);
    } else {
        napi_value error = CreateErrorValue(asyncContext->env, callbackCode, ASYNC_ERROR_MAP[callbackCode]);
        napi_reject_deferred(asyncContext->env, asyncContext->deferred, error);
    }
    napi_close_handle_scope(asyncContext->env, scope);
}

void ReturnPromise(const JSCallbackInfo& info, int32_t errCode)
{
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    napi_deferred deferred = nullptr;
    napi_value promise = nullptr;
    napi_create_promise(env, &deferred, &promise);

    if (errCode != ERROR_CODE_NO_ERROR) {
        napi_value result = CreateErrorValue(env, errCode, ASYNC_ERROR_MAP[errCode]);
        napi_reject_deferred(env, deferred, result);
    } else {
        napi_value result = nullptr;
        napi_get_undefined(env, &result);
        napi_resolve_deferred(env, deferred, result);
    }
    CHECK_NULL_VOID(promise);
    auto jsPromise = JsConverter::ConvertNapiValueToJsVal(promise);
    if (!jsPromise->IsObject()) {
        TAG_LOGE(AceLogTag::ACE_TEXT, "Return promise failed.");
        return;
    }
    info.SetReturnValue(JSRef<JSObject>::Cast(jsPromise));
}

static std::atomic<int32_t> gestureStyleStoreIndex_;
static std::atomic<int32_t> spanStringStoreIndex_;
};

const std::unordered_set<SpanType> types = { SpanType::Font, SpanType::Gesture, SpanType::BaselineOffset,
    SpanType::Decoration, SpanType::LetterSpacing, SpanType::TextShadow, SpanType::LineHeight, SpanType::Image,
    SpanType::CustomSpan, SpanType::ParagraphStyle, SpanType::ExtSpan, SpanType::BackgroundColor, SpanType::Url };

const std::unordered_map<SpanType, std::function<JSRef<JSObject>(const RefPtr<SpanBase>&)>> spanCreators = {
    { SpanType::Font, JSSpanString::CreateJsFontSpan }, { SpanType::Decoration, JSSpanString::CreateJsDecorationSpan },
    { SpanType::BaselineOffset, JSSpanString::CreateJsBaselineOffsetSpan },
    { SpanType::LetterSpacing, JSSpanString::CreateJsLetterSpacingSpan },
    { SpanType::Gesture, JSSpanString::CreateJsGestureSpan },
    { SpanType::TextShadow, JSSpanString::CreateJsTextShadowSpan },
    { SpanType::BackgroundColor, JSSpanString::CreateJSBackgroundColorSpan },
    { SpanType::LineHeight, JSSpanString::CreateJsLineHeightSpan },
    { SpanType::Image, JSSpanString::CreateJsImageSpan },
    { SpanType::ParagraphStyle, JSSpanString::CreateJsParagraphStyleSpan },
    { SpanType::Url, JSSpanString::CreateJsUrlSpan },
};

void JSSpanString::Constructor(const JSCallbackInfo& args)
{
    auto jsSpanString = Referenced::MakeRefPtr<JSSpanString>();
    jsSpanString->IncRefCount();
    std::string data;
    RefPtr<SpanString> spanString;
    if (args.Length() == 0) {
        spanString = AceType::MakeRefPtr<SpanString>(data);
    } else {
        if (args[0]->IsString()) {
            JSViewAbstract::ParseJsString(args[0], data);
            spanString = AceType::MakeRefPtr<SpanString>(data);
            if (args.Length() > 1) {
                auto thisObj = args.This();
                auto spanBases = JSSpanString::ParseJsSpanBaseVector(args[1], StringUtils::ToWstring(data).length(),
                    thisObj);
                spanString->BindWithSpans(spanBases);
            }
        } else {
            auto* base = JSRef<JSObject>::Cast(args[0])->Unwrap<AceType>();
            auto* imageAttachment = AceType::DynamicCast<JSImageAttachment>(base);
            if (imageAttachment) {
                auto attachment = JSSpanString::ParseJsImageAttachment(args[0]);
                spanString = AceType::MakeRefPtr<SpanString>(attachment);
            } else {
                RefPtr<CustomSpan> customSpan = JSSpanString::ParseJsCustomSpan(args);
                spanString = AceType::MakeRefPtr<SpanString>(customSpan);
            }
            if (args.Length() > 1) {
                TAG_LOGW(ACE_TEXT, "initialization of styledstring with image or custom span will only use first arg");
            }
        }
    }
    jsSpanString->SetController(spanString);
    args.SetReturnValue(Referenced::RawPtr(jsSpanString));
}

void JSSpanString::Destructor(JSSpanString* spanString)
{
    if (spanString != nullptr) {
        spanString->DecRefCount();
    }
}

void JSSpanString::JSBind(BindingTarget globalObj)
{
    JSClass<JSSpanString>::Declare("StyledString");
    JSClass<JSSpanString>::CustomMethod("getString", &JSSpanString::GetString);
    JSClass<JSSpanString>::CustomProperty("length", &JSSpanString::GetLength, &JSSpanString::SetLength);
    JSClass<JSSpanString>::CustomMethod("equals", &JSSpanString::IsEqualToSpanString);
    JSClass<JSSpanString>::CustomMethod("subStyledString", &JSSpanString::GetSubSpanString);
    JSClass<JSSpanString>::CustomMethod("getStyles", &JSSpanString::GetSpans);
    JSClass<JSSpanString>::StaticMethod("fromHtml", &JSSpanString::FromHtml);
    JSClass<JSSpanString>::StaticMethod("marshalling", &JSSpanString::Marshalling);
    JSClass<JSSpanString>::StaticMethod("unmarshalling", &JSSpanString::Unmarshalling);
    JSClass<JSSpanString>::Bind(globalObj, JSSpanString::Constructor, JSSpanString::Destructor);
}

void JSSpanString::GetString(const JSCallbackInfo& info)
{
    auto ret = JSRef<JSVal>::Make(JSVal(ToJSValue(spanString_->GetString())));
    info.SetReturnValue(ret);
}

void JSSpanString::GetLength(const JSCallbackInfo& info)
{
    auto ret = JSRef<JSVal>::Make(JSVal(ToJSValue(spanString_->GetLength())));
    info.SetReturnValue(ret);
}

void JSSpanString::SetLength(const JSCallbackInfo& info) {}

void JSSpanString::IsEqualToSpanString(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsObject()) {
        info.SetReturnValue(JSRef<JSVal>::Make(JSVal(ToJSValue(false))));
        return;
    }
    auto jsSpanString = JSRef<JSObject>::Cast(info[0])->Unwrap<JSSpanString>();
    if (!jsSpanString || !jsSpanString->GetController()) {
        info.SetReturnValue(JSRef<JSVal>::Make(JSVal(ToJSValue(false))));
        return;
    }
    auto spanString = jsSpanString->GetController();
    auto ret = JSRef<JSVal>::Make(JSVal(ToJSValue(spanString_->IsEqualToSpanString(spanString))));
    info.SetReturnValue(ret);
}

void JSSpanString::GetSubSpanString(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsNumber() || (info.Length() == 2 && !info[1]->IsNumber())) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto start = info[0]->ToNumber<int32_t>();
    auto length = spanString_->GetLength() - start;
    if (info.Length() == 2) {
        length = info[1]->ToNumber<int32_t>();
    }
    if (!CheckParameters(start, length)) {
        return;
    }
    auto spanString = spanString_->GetSubSpanString(start, length);
    CHECK_NULL_VOID(spanString);
    JSRef<JSObject> obj = JSClass<JSSpanString>::NewInstance();
    auto jsSpanString = Referenced::Claim(obj->Unwrap<JSSpanString>());
    jsSpanString->SetController(spanString);
    info.SetReturnValue(obj);
}

void JSSpanString::GetSpans(const JSCallbackInfo& info)
{
    if (info.Length() < 2 || !info[0]->IsNumber() || !info[1]->IsNumber() ||
        (info.Length() == 3 && !info[2]->IsNumber())) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto start = info[0]->ToNumber<int32_t>();
    auto length = info[1]->ToNumber<int32_t>();
    if (!CheckParameters(start, length)) {
        return;
    }
    std::vector<RefPtr<SpanBase>> spans;
    if (info.Length() >= 3) {
        auto spanType = info[2]->ToNumber<int32_t>();
        if (!CheckSpanType(spanType)) {
            return;
        }
        auto type = static_cast<SpanType>(spanType);
        spans = spanString_->GetSpans(start, length, type);
    } else {
        spans = spanString_->GetSpans(start, length);
    }

    JSRef<JSArray> spanObjectArray = JSRef<JSArray>::New();
    uint32_t idx = 0;
    for (const RefPtr<SpanBase>& spanObject : spans) {
        spanObjectArray->SetValueAt(idx++, CreateJsSpanBaseObject(spanObject));
    }
    info.SetReturnValue(JSRef<JSVal>::Cast(spanObjectArray));
}

JSRef<JSObject> JSSpanString::CreateJsSpanBaseObject(const RefPtr<SpanBase>& spanObject)
{
    JSRef<JSObject> resultObj = JSRef<JSObject>::New();
    resultObj->SetProperty<int32_t>("start", spanObject->GetStartIndex());
    resultObj->SetProperty<int32_t>("length", spanObject->GetLength());
    resultObj->SetProperty<int32_t>("styledKey", static_cast<int32_t>(spanObject->GetSpanType()));
    JSRef<JSObject> obj = CreateJsSpanObject(spanObject);
    resultObj->SetPropertyObject("styledValue", obj);
    return resultObj;
}

JSRef<JSObject> JSSpanString::CreateJsSpanObject(const RefPtr<SpanBase>& spanObject)
{
    JSRef<JSObject> obj;
    auto type = spanObject->GetSpanType();
    auto it = spanCreators.find(type);
    if (it != spanCreators.end()) {
        obj = it->second(spanObject);
    } else if (type == SpanType::CustomSpan) {
        obj = AceType::DynamicCast<JSCustomSpan>(spanObject)->GetJsCustomSpanObject();
    } else if (type == SpanType::ExtSpan) {
        obj = AceType::DynamicCast<JSExtSpan>(spanObject)->GetJsExtSpanObject();
    }
    return obj;
}

JSRef<JSObject> JSSpanString::CreateJsParagraphStyleSpan(const RefPtr<SpanBase>& spanObject)
{
    auto span = AceType::DynamicCast<ParagraphStyleSpan>(spanObject);
    CHECK_NULL_RETURN(span, JSRef<JSObject>::New());
    JSRef<JSObject> obj = JSClass<JSParagraphStyleSpan>::NewInstance();
    auto paragraphSpan = Referenced::Claim(obj->Unwrap<JSParagraphStyleSpan>());
    paragraphSpan->SetParagraphStyleSpan(span);
    return obj;
}

JSRef<JSObject> JSSpanString::CreateJsUrlSpan(const RefPtr<SpanBase>& spanObject)
{
    auto span = AceType::DynamicCast<UrlSpan>(spanObject);
    CHECK_NULL_RETURN(span, JSRef<JSObject>::New());
    JSRef<JSObject> obj = JSClass<JSUrlSpan>::NewInstance();
    auto urlSpan = Referenced::Claim(obj->Unwrap<JSUrlSpan>());
    urlSpan->SetUrlSpan(span);
    return obj;
}

JSRef<JSObject> JSSpanString::CreateJsFontSpan(const RefPtr<SpanBase>& spanObject)
{
    auto span = AceType::DynamicCast<FontSpan>(spanObject);
    CHECK_NULL_RETURN(span, JSRef<JSObject>::New());
    JSRef<JSObject> obj = JSClass<JSFontSpan>::NewInstance();
    auto fontSpan = Referenced::Claim(obj->Unwrap<JSFontSpan>());
    fontSpan->SetFontSpan(span);
    return obj;
}

JSRef<JSObject> JSSpanString::CreateJsDecorationSpan(const RefPtr<SpanBase>& spanObject)
{
    auto span = AceType::DynamicCast<DecorationSpan>(spanObject);
    CHECK_NULL_RETURN(span, JSRef<JSObject>::New());
    JSRef<JSObject> obj = JSClass<JSDecorationSpan>::NewInstance();
    auto decorationSpan = Referenced::Claim(obj->Unwrap<JSDecorationSpan>());
    decorationSpan->SetDecorationSpan(span);
    return obj;
}

JSRef<JSObject> JSSpanString::CreateJsBaselineOffsetSpan(const RefPtr<SpanBase>& spanObject)
{
    auto span = AceType::DynamicCast<BaselineOffsetSpan>(spanObject);
    CHECK_NULL_RETURN(span, JSRef<JSObject>::New());
    JSRef<JSObject> obj = JSClass<JSBaselineOffsetSpan>::NewInstance();
    auto baselineOffsetSpan = Referenced::Claim(obj->Unwrap<JSBaselineOffsetSpan>());
    baselineOffsetSpan->SetBaselineOffsetSpan(span);
    return obj;
}

JSRef<JSObject> JSSpanString::CreateJsLetterSpacingSpan(const RefPtr<SpanBase>& spanObject)
{
    auto span = AceType::DynamicCast<LetterSpacingSpan>(spanObject);
    CHECK_NULL_RETURN(span, JSRef<JSObject>::New());
    JSRef<JSObject> obj = JSClass<JSLetterSpacingSpan>::NewInstance();
    auto letterSpacingSpan = Referenced::Claim(obj->Unwrap<JSLetterSpacingSpan>());
    letterSpacingSpan->SetLetterSpacingSpan(span);
    return obj;
}

JSRef<JSObject> JSSpanString::CreateJsGestureSpan(const RefPtr<SpanBase>& spanObject)
{
    auto span = AceType::DynamicCast<GestureSpan>(spanObject);
    CHECK_NULL_RETURN(span, JSRef<JSObject>::New());
    JSRef<JSObject> obj = JSClass<JSGestureSpan>::NewInstance();
    auto gestureSpan = Referenced::Claim(obj->Unwrap<JSGestureSpan>());
    gestureSpan->SetGestureSpan(span);
    return obj;
}

JSRef<JSObject> JSSpanString::CreateJsTextShadowSpan(const RefPtr<SpanBase>& spanObject)
{
    auto span = AceType::DynamicCast<TextShadowSpan>(spanObject);
    CHECK_NULL_RETURN(span, JSRef<JSObject>::New());
    JSRef<JSObject> obj = JSClass<JSTextShadowSpan>::NewInstance();
    auto textShadowSpan = Referenced::Claim(obj->Unwrap<JSTextShadowSpan>());
    textShadowSpan->SetTextShadowSpan(span);
    return obj;
}

JSRef<JSObject> JSSpanString::CreateJSBackgroundColorSpan(const RefPtr<SpanBase>& spanObject)
{
    auto span = AceType::DynamicCast<BackgroundColorSpan>(spanObject);
    CHECK_NULL_RETURN(span, JSRef<JSObject>::New());
    JSRef<JSObject> obj = JSClass<JSBackgroundColorSpan>::NewInstance();
    auto backgroundColorSpan = Referenced::Claim(obj->Unwrap<JSBackgroundColorSpan>());
    backgroundColorSpan->SetBackgroundColorSpan(span);
    return obj;
}

JSRef<JSObject> JSSpanString::CreateJsLineHeightSpan(const RefPtr<SpanBase>& spanObject)
{
    auto span = AceType::DynamicCast<LineHeightSpan>(spanObject);
    CHECK_NULL_RETURN(span, JSRef<JSObject>::New());
    JSRef<JSObject> obj = JSClass<JSLineHeightSpan>::NewInstance();
    auto lineHeightSpan = Referenced::Claim(obj->Unwrap<JSLineHeightSpan>());
    lineHeightSpan->SetLineHeightSpan(span);
    return obj;
}

JSRef<JSObject> JSSpanString::CreateJsImageSpan(const RefPtr<SpanBase>& spanObject)
{
    auto span = AceType::DynamicCast<ImageSpan>(spanObject);
    CHECK_NULL_RETURN(span, JSRef<JSObject>::New());
    JSRef<JSObject> obj = JSClass<JSImageAttachment>::NewInstance();
    auto imageSpan = Referenced::Claim(obj->Unwrap<JSImageAttachment>());
    imageSpan->SetImageSpan(span);
    return obj;
}

RefPtr<SpanBase> JSSpanString::ParseJsSpanBaseWithoutSpecialSpan(
    int32_t start, int32_t length, SpanType type, const JSRef<JSObject>& obj, const JSCallbackInfo& info)
{
    if (type == SpanType::CustomSpan) {
        return ParseJsCustomSpan(start, length, info);
    }
    return JSSpanString::ParseJsSpanBase(start, length, type, obj);
}

RefPtr<SpanBase> JSSpanString::ParseJsSpanBase(int32_t start, int32_t length, SpanType type, const JSRef<JSObject>& obj)
{
    switch (type) {
        case SpanType::Font:
            return ParseJsFontSpan(start, length, obj);
        case SpanType::Decoration:
            return ParseJsDecorationSpan(start, length, obj);
        case SpanType::LetterSpacing:
            return ParseJsLetterSpacingSpan(start, length, obj);
        case SpanType::BaselineOffset:
            return ParseJsBaselineOffsetSpan(start, length, obj);
        case SpanType::Gesture:
            return ParseJsGestureSpan(start, length, obj);
        case SpanType::TextShadow:
            return ParseJsTextShadowSpan(start, length, obj);
        case SpanType::LineHeight:
            return ParseJsLineHeightSpan(start, length, obj);
        case SpanType::Image:
            return GetImageAttachment(start, length, obj);
        case SpanType::ParagraphStyle:
            return ParseJsParagraphStyleSpan(start, length, obj);
        case SpanType::ExtSpan:
            return ParseJsExtSpan(start, length, obj);
        case SpanType::BackgroundColor:
            return ParseJSBackgroundColorSpan(start, length, obj);
        case SpanType::Url:
            return ParseJsUrlSpan(start, length, obj);
        default:
            break;
    }
    return nullptr;
}

RefPtr<SpanBase> JSSpanString::ParseJsFontSpan(int32_t start, int32_t length, const JSRef<JSObject>& obj)
{
    auto* base = obj->Unwrap<AceType>();
    auto* fontSpan = AceType::DynamicCast<JSFontSpan>(base);
    if (fontSpan && fontSpan->GetFontSpan()) {
        return AceType::MakeRefPtr<FontSpan>(fontSpan->GetFontSpan()->GetFont(), start, start + length);
    }
    return nullptr;
}

RefPtr<SpanBase> JSSpanString::ParseJsParagraphStyleSpan(int32_t start, int32_t length, const JSRef<JSObject>& obj)
{
    auto* base = obj->Unwrap<AceType>();
    auto* paragraphStyleSpan = AceType::DynamicCast<JSParagraphStyleSpan>(base);
    if (paragraphStyleSpan && paragraphStyleSpan->GetParagraphStyleSpan()) {
        return AceType::MakeRefPtr<ParagraphStyleSpan>(
            paragraphStyleSpan->GetParagraphStyleSpan()->GetParagraphStyle(), start, start + length);
    }
    return nullptr;
}

RefPtr<SpanBase> JSSpanString::ParseJsDecorationSpan(int32_t start, int32_t length, const JSRef<JSObject>& obj)
{
    auto* base = obj->Unwrap<AceType>();
    auto* decorationSpan = AceType::DynamicCast<JSDecorationSpan>(base);
    if (decorationSpan && decorationSpan->GetDecorationSpan()) {
        return AceType::MakeRefPtr<DecorationSpan>(decorationSpan->GetDecorationSpan()->GetTextDecorationType(),
            decorationSpan->GetDecorationSpan()->GetColor(),
            decorationSpan->GetDecorationSpan()->GetTextDecorationStyle(), start, start + length);
    }
    return nullptr;
}

RefPtr<SpanBase> JSSpanString::ParseJsBaselineOffsetSpan(int32_t start, int32_t length, const JSRef<JSObject>& obj)
{
    auto* base = obj->Unwrap<AceType>();
    auto* baselineOffsetSpan = AceType::DynamicCast<JSBaselineOffsetSpan>(base);
    if (baselineOffsetSpan && baselineOffsetSpan->GetBaselineOffsetSpan()) {
        return AceType::MakeRefPtr<BaselineOffsetSpan>(
            baselineOffsetSpan->GetBaselineOffsetSpan()->GetBaselineOffset(), start, start + length);
    }
    return nullptr;
}

RefPtr<SpanBase> JSSpanString::ParseJsLetterSpacingSpan(int32_t start, int32_t length, const JSRef<JSObject>& obj)
{
    auto* base = obj->Unwrap<AceType>();
    auto* letterSpacingSpan = AceType::DynamicCast<JSLetterSpacingSpan>(base);
    if (letterSpacingSpan && letterSpacingSpan->GetLetterSpacingSpan()) {
        return AceType::MakeRefPtr<LetterSpacingSpan>(
            letterSpacingSpan->GetLetterSpacingSpan()->GetLetterSpacing(), start, start + length);
    }
    return nullptr;
}

RefPtr<SpanBase> JSSpanString::ParseJsGestureSpan(int32_t start, int32_t length, const JSRef<JSObject>& obj)
{
    auto* base = obj->Unwrap<AceType>();
    auto* gestureSpan = AceType::DynamicCast<JSGestureSpan>(base);
    if (gestureSpan && gestureSpan->GetGestureSpan()) {
        return AceType::MakeRefPtr<GestureSpan>(
            gestureSpan->GetGestureSpan()->GetGestureStyle(), start, start + length);
    }
    return nullptr;
}

RefPtr<SpanBase> JSSpanString::ParseJsTextShadowSpan(int32_t start, int32_t length, const JSRef<JSObject>& obj)
{
    auto* base = obj->Unwrap<AceType>();
    auto* textShadowSpan = AceType::DynamicCast<JSTextShadowSpan>(base);
    if (textShadowSpan && textShadowSpan->GetTextShadowSpan()) {
        return AceType::MakeRefPtr<TextShadowSpan>(
            textShadowSpan->GetTextShadowSpan()->GetTextShadow(), start, start + length);
    }
    return nullptr;
}

RefPtr<SpanBase> JSSpanString::ParseJSBackgroundColorSpan(int32_t start, int32_t length, const JSRef<JSObject>& obj)
{
    auto* base = obj->Unwrap<AceType>();
    auto* backgroundColorSpan = AceType::DynamicCast<JSBackgroundColorSpan>(base);
    if (backgroundColorSpan && backgroundColorSpan->GetBackgroundColorSpan()) {
        return AceType::MakeRefPtr<BackgroundColorSpan>(
            backgroundColorSpan->GetBackgroundColorSpan()->GetBackgroundColor(), start, start + length);
    }
    return nullptr;
}

RefPtr<SpanBase> JSSpanString::ParseJsLineHeightSpan(int32_t start, int32_t length, const JSRef<JSObject>& obj)
{
    auto* base = obj->Unwrap<AceType>();
    auto* lineHeightSpan = AceType::DynamicCast<JSLineHeightSpan>(base);
    if (lineHeightSpan && lineHeightSpan->GetLineHeightSpan()) {
        return AceType::MakeRefPtr<LineHeightSpan>(
            lineHeightSpan->GetLineHeightSpan()->GetLineHeight(), start, start + length);
    }
    return nullptr;
}

RefPtr<SpanBase> JSSpanString::GetImageAttachment(int32_t start, int32_t length, const JSRef<JSObject>& obj)
{
    auto* base = obj->Unwrap<AceType>();
    auto* imageAttachment = AceType::DynamicCast<JSImageAttachment>(base);
    if (imageAttachment && imageAttachment->GetImageSpan()) {
        auto imageSpan = imageAttachment->GetImageSpan();
        imageSpan->UpdateStartIndex(start);
        imageSpan->UpdateEndIndex(start + length);
        return imageSpan;
    }
    return nullptr;
}

RefPtr<SpanBase> JSSpanString::ParseJsCustomSpan(int32_t start, int32_t length, const JSCallbackInfo& args)
{
    if (args.Length() == 0) {
        return nullptr;
    }
    auto paramObj = args[0];
    if (paramObj->IsUndefined()) {
        return nullptr;
    }
    if (!paramObj->IsObject()) {
        return nullptr;
    }
    auto styledValueObj = JSRef<JSObject>::Cast(paramObj)->GetProperty("styledValue");
    if (!styledValueObj->IsObject()) {
        return nullptr;
    }
    auto styleStringValue = JSRef<JSObject>::Cast(styledValueObj);
    if (styleStringValue->IsUndefined()) {
        return nullptr;
    }
    auto typeObj = styleStringValue->GetProperty("type_");
    if (!typeObj->IsString() || typeObj->ToString() != "CustomSpan") {
        return nullptr;
    }
    auto spanBase = AceType::MakeRefPtr<JSCustomSpan>(JSRef<JSObject>(styleStringValue), args);
    spanBase->UpdateStartIndex(start);
    spanBase->UpdateEndIndex(start + length);
    return spanBase;
}

RefPtr<SpanBase> JSSpanString::ParseJsExtSpan(int32_t start, int32_t length, const JSRef<JSObject>& obj)
{
    auto typeObj = obj->GetProperty("type_");
    if (!typeObj->IsString() || typeObj->ToString() != "ExtSpan") {
        return nullptr;
    }
    auto spanBase = AceType::MakeRefPtr<JSExtSpan>(obj, start, start + length);
    return spanBase;
}

RefPtr<SpanBase> JSSpanString::ParseJsUrlSpan(int32_t start, int32_t length, const JSRef<JSObject>& obj)
{
    auto* base = obj->Unwrap<AceType>();
    auto* urlSpan = AceType::DynamicCast<JSUrlSpan>(base);
    if (urlSpan && urlSpan->GetUrlSpan()) {
        return AceType::MakeRefPtr<UrlSpan>(
            urlSpan->GetUrlSpan()->GetUrlSpanAddress(), start, start + length);
    }
    return nullptr;
}

bool JSSpanString::CheckSpanType(int32_t spanType)
{
    if (types.find(static_cast<SpanType>(spanType)) == types.end()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "CheckSpanType failed: Ilegal span type");
        return false;
    }
    return true;
}

bool JSSpanString::CheckParameters(int32_t start, int32_t length)
{
    // The input parameter must not cross the boundary.
    if (!spanString_->CheckRange(start, length)) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s start:%d length:%d", "CheckBoundary failed:", start, length);
        return false;
    }
    return true;
}

std::vector<RefPtr<SpanBase>> JSSpanString::ParseJsSpanBaseVector(const JSRef<JSObject>& obj, int32_t maxLength,
    JsiRef<JsiObject> thisObj)
{
    std::vector<RefPtr<SpanBase>> spanBaseVector;
    auto arrays = JSRef<JSArray>::Cast(obj);
    for (size_t i = 0; i < arrays->Length(); i++) {
        JSRef<JSVal> value = arrays->GetValueAt(i);
        if (value->IsNull() || value->IsUndefined() || (!value->IsObject())) {
            continue;
        }
        auto valueObj = JSRef<JSObject>::Cast(value);
        auto startProperty = valueObj->GetProperty("start");
        auto lengthProperty = valueObj->GetProperty("length");
        int32_t start = 0;
        if (!startProperty->IsNull() && startProperty->IsNumber()) {
            start = startProperty->ToNumber<int32_t>();
            start = start < 0 || start >= maxLength ? 0 : start;
        }
        int32_t length = maxLength - start;
        if (!lengthProperty->IsNull() && lengthProperty->IsNumber()) {
            length = lengthProperty->ToNumber<int32_t>();
            length = length > maxLength - start || length <= 0 ? maxLength - start : length;
        }
        auto styleKey = valueObj->GetProperty("styledKey");
        if (styleKey->IsNull() || !styleKey->IsNumber()) {
            continue;
        }
        auto styleStringValue = valueObj->GetProperty("styledValue");
        if (!styleStringValue->IsObject()) {
            continue;
        }
        auto type = static_cast<SpanType>(styleKey->ToNumber<int32_t>());
        if (type == SpanType::Image || type == SpanType::CustomSpan) {
            continue;
        }
        if (type == SpanType::Gesture) {
            auto newIndex = gestureStyleStoreIndex_.fetch_add(1);
            std::string key = "STYLED_STRING_GESTURESTYLE_STORE_" + std::to_string(newIndex);
            thisObj->SetPropertyObject(key.c_str(), styleStringValue);
        }
        auto spanBase = ParseJsSpanBase(start, length, type, JSRef<JSObject>::Cast(styleStringValue));
        if (spanBase) {
            spanBaseVector.emplace_back(spanBase);
        }
    }
    return spanBaseVector;
}

const RefPtr<SpanString>& JSSpanString::GetController()
{
    return spanString_;
}

void JSSpanString::SetController(const RefPtr<SpanString>& spanString)
{
    spanString_ = spanString;
}

ImageSpanOptions JSSpanString::ParseJsImageAttachment(const JSRef<JSObject>& info)
{
    ImageSpanOptions options;
    auto* base = info->Unwrap<AceType>();
    auto* imageAttachment = AceType::DynamicCast<JSImageAttachment>(base);
    if (!imageAttachment) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Parse JsImageAttachment Failed");
        return options;
    }
    return imageAttachment->GetImageOptions();
}

RefPtr<CustomSpan> JSSpanString::ParseJsCustomSpan(const JSCallbackInfo& args)
{
    return AceType::MakeRefPtr<JSCustomSpan>(args[0], args);
}

void JSSpanString::FromHtml(const JSCallbackInfo& info)
{
    ContainerScope scope(Container::CurrentIdSafely());
    if (info.Length() != 1 || !info[0]->IsString()) {
        ReturnPromise(info, ERROR_CODE_PARAM_INVALID);
        return;
    }
    std::string arg = info[0]->ToString();
    auto container = Container::CurrentSafely();
    if (!container) {
        ReturnPromise(info, ERROR_CODE_PARAM_INVALID);
        return;
    }
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    auto asyncContext = std::make_shared<HtmlConverterAsyncCtx>();
    asyncContext->instanceId = Container::CurrentIdSafely();
    asyncContext->env = reinterpret_cast<napi_env>(nativeEngine);
    napi_value result = nullptr;
    napi_create_promise(asyncContext->env, &asyncContext->deferred, &result);
    taskExecutor->PostTask(
        [htmlStr = arg, asyncContext]() mutable {
            ContainerScope scope(asyncContext->instanceId);
            // FromHtml may cost much time because of pixelmap.
            // Therefore this function should be called in Background thread.
            auto styledString = HtmlUtils::FromHtml(htmlStr);
            auto container = AceEngine::Get().GetContainer(asyncContext->instanceId);
            CHECK_NULL_VOID(container);
            auto taskExecutor = container->GetTaskExecutor();
            taskExecutor->PostTask(
                [styledString, asyncContext]() mutable {
                    ContainerScope scope(asyncContext->instanceId);
                    if (!styledString) {
                        ProcessPromiseCallback(asyncContext, ERROR_CODE_FROM_HTML_CONVERT_ERROR);
                        return;
                    }
                    JSRef<JSObject> obj = JSClass<JSSpanString>::NewInstance();
                    auto jsSpanString = Referenced::Claim(obj->Unwrap<JSSpanString>());
                    jsSpanString->SetController(styledString);
                    auto spanStrNapi = JsConverter::ConvertJsValToNapiValue(obj);
                    ProcessPromiseCallback(asyncContext, ERROR_CODE_NO_ERROR, spanStrNapi);
                },
                TaskExecutor::TaskType::UI, "FromHtmlReturnPromise", PriorityType::IMMEDIATE);
        },
        TaskExecutor::TaskType::BACKGROUND, "FromHtml", PriorityType::IMMEDIATE);
    auto jsPromise = JsConverter::ConvertNapiValueToJsVal(result);
    CHECK_NULL_VOID(jsPromise->IsObject());
    info.SetReturnValue(JSRef<JSObject>::Cast(jsPromise));
}

void JSSpanString::Marshalling(const JSCallbackInfo& info)
{
    auto arg = info[0];
    if (info.Length() != 1 || !arg->IsObject()) {
        ReturnPromise(info, ERROR_CODE_PARAM_INVALID);
        return;
    }

    auto* spanString = JSRef<JSObject>::Cast(arg)->Unwrap<JSSpanString>();
    CHECK_NULL_VOID(spanString);
    auto spanStringController = spanString->GetController();
    CHECK_NULL_VOID(spanStringController);
    std::vector<uint8_t> buff;
    spanStringController->EncodeTlv(buff);

    size_t bufferSize = buff.size();
    JSRef<JSArrayBuffer> arrayBuffer = JSRef<JSArrayBuffer>::New(bufferSize);
    auto* buffer = static_cast<uint8_t*>(arrayBuffer->GetBuffer());
    if (memcpy_s(buffer, bufferSize, buff.data(), bufferSize) != 0) {
        return;
    }
    info.SetReturnValue(arrayBuffer);
}
    
void JSSpanString::UnmarshallingExec(napi_env env, void *data)
{
    CHECK_NULL_VOID(data);
    auto asyncContext = static_cast<AsyncContext*>(data);
    asyncContext->spanString = SpanString::DecodeTlv(asyncContext->buffer);
    CHECK_NULL_VOID(asyncContext->spanString);
    asyncContext->status = napi_ok; 
}

void JSSpanString::UnmarshallingComplete(napi_env env, napi_status status, void *data)
{
    CHECK_NULL_VOID(data);
    auto asyncContext = static_cast<AsyncContext*>(data);
    JSRef<JSObject> obj = JSClass<JSSpanString>::NewInstance();
    auto jsSpanString = Referenced::Claim(obj->Unwrap<JSSpanString>());
    CHECK_NULL_VOID(jsSpanString);
    jsSpanString->SetController(asyncContext->spanString);
    auto spanStrNapi = JsConverter::ConvertJsValToNapiValue(obj);

    if (status == napi_ok && asyncContext->status == napi_ok) {
        napi_resolve_deferred(env, asyncContext->deferred, spanStrNapi);
    } else {
        napi_value error = CreateErrorValue(asyncContext->env, ERROR_CODE_STYLED_STRING_CONVERT_ERROR,
            ASYNC_ERROR_MAP[ERROR_CODE_STYLED_STRING_CONVERT_ERROR]);
        napi_reject_deferred(env, asyncContext->deferred, error);
    }
    delete asyncContext;
}

void JSSpanString::Unmarshalling(const JSCallbackInfo& info)
{
    auto arg = info[0];
    if (info.Length() != 1 || !arg->IsArrayBuffer()) {
        ReturnPromise(info, ERROR_CODE_PARAM_INVALID);
        return;
    }
    JSRef<JSArrayBuffer> arrayBuffer = JSRef<JSArrayBuffer>::Cast(arg);
    size_t bufferSize = static_cast<size_t>(arrayBuffer->ByteLength());
    void* buffer = arrayBuffer->GetBuffer();
    std::vector<uint8_t> buff(static_cast<uint8_t*>(buffer), static_cast<uint8_t*>(buffer) + bufferSize);
    auto asyncContext = new AsyncContext();
    asyncContext->buffer = buff;

    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    asyncContext->env = reinterpret_cast<napi_env>(nativeEngine);
    napi_value promise = nullptr;
    napi_create_promise(asyncContext->env, &asyncContext->deferred, &promise);
    napi_value resourceName = nullptr;
    napi_create_string_utf8(asyncContext->env, "ArkUISpanStringUnmarshalling", NAPI_AUTO_LENGTH, &resourceName);
    napi_create_async_work(asyncContext->env, nullptr, resourceName, UnmarshallingExec, UnmarshallingComplete,
        asyncContext, &asyncContext->asyncWork);
    napi_queue_async_work(asyncContext->env, asyncContext->asyncWork);

    auto jsPromise = JsConverter::ConvertNapiValueToJsVal(promise);
    CHECK_NULL_VOID(jsPromise->IsObject());
    info.SetReturnValue(JSRef<JSObject>::Cast(jsPromise));
}

// JSMutableSpanString
void JSMutableSpanString::Constructor(const JSCallbackInfo& args)
{
    auto jsSpanString = Referenced::MakeRefPtr<JSMutableSpanString>();
    jsSpanString->IncRefCount();
    std::string data;

    RefPtr<MutableSpanString> spanString;
    if (args.Length() == 0) {
        spanString = AceType::MakeRefPtr<MutableSpanString>(data);
    } else {
        if (args[0]->IsString()) {
            JSViewAbstract::ParseJsString(args[0], data);
            spanString = AceType::MakeRefPtr<MutableSpanString>(data);
            if (args.Length() > 1) {
                auto thisObj = args.This();
                auto spanBases = JSSpanString::ParseJsSpanBaseVector(args[1],
                    StringUtils::ToWstring(data).length(), thisObj);
                spanString->BindWithSpans(spanBases);
            }
        } else {
            if (!args[0]->IsObject()) {
                return;
            }
            auto* base = JSRef<JSObject>::Cast(args[0])->Unwrap<AceType>();
            auto* imageAttachment = AceType::DynamicCast<JSImageAttachment>(base);
            if (imageAttachment) {
                auto attachment = JSSpanString::ParseJsImageAttachment(args[0]);
                spanString = AceType::MakeRefPtr<MutableSpanString>(attachment);
            } else {
                RefPtr<CustomSpan> customSpan = JSSpanString::ParseJsCustomSpan(args);
                spanString = AceType::MakeRefPtr<MutableSpanString>(customSpan);
            }
        }
    }
    jsSpanString->SetController(spanString);
    jsSpanString->SetMutableController(spanString);
    args.SetReturnValue(Referenced::RawPtr(jsSpanString));
}

void JSMutableSpanString::Destructor(JSMutableSpanString* spanString)
{
    if (spanString != nullptr) {
        spanString->DecRefCount();
    }
}

void JSMutableSpanString::JSBind(BindingTarget globalObj)
{
    JSClass<JSMutableSpanString>::Declare("MutableStyledString");
    JSClass<JSMutableSpanString>::CustomMethod("getString", &JSSpanString::GetString);
    JSClass<JSMutableSpanString>::CustomProperty("length", &JSSpanString::GetLength, &JSSpanString::SetLength);
    JSClass<JSMutableSpanString>::CustomMethod("equals", &JSSpanString::IsEqualToSpanString);
    JSClass<JSMutableSpanString>::CustomMethod("subStyledString", &JSSpanString::GetSubSpanString);
    JSClass<JSMutableSpanString>::CustomMethod("getStyles", &JSSpanString::GetSpans);

    JSClass<JSMutableSpanString>::CustomMethod("replaceString", &JSMutableSpanString::ReplaceString);
    JSClass<JSMutableSpanString>::CustomMethod("insertString", &JSMutableSpanString::InsertString);
    JSClass<JSMutableSpanString>::CustomMethod("removeString", &JSMutableSpanString::RemoveString);
    JSClass<JSMutableSpanString>::CustomMethod("replaceStyle", &JSMutableSpanString::ReplaceSpan);
    JSClass<JSMutableSpanString>::CustomMethod("setStyle", &JSMutableSpanString::AddSpan);
    JSClass<JSMutableSpanString>::CustomMethod("removeStyle", &JSMutableSpanString::RemoveSpan);
    JSClass<JSMutableSpanString>::CustomMethod("removeStyles", &JSMutableSpanString::RemoveSpans);
    JSClass<JSMutableSpanString>::Method("clearStyles", &JSMutableSpanString::ClearAllSpans);
    JSClass<JSMutableSpanString>::CustomMethod("replaceStyledString", &JSMutableSpanString::ReplaceSpanString);
    JSClass<JSMutableSpanString>::CustomMethod("insertStyledString", &JSMutableSpanString::InsertSpanString);
    JSClass<JSMutableSpanString>::CustomMethod("appendStyledString", &JSMutableSpanString::AppendSpanString);
    JSClass<JSMutableSpanString>::Bind(globalObj, JSMutableSpanString::Constructor, JSMutableSpanString::Destructor);
}

void JSMutableSpanString::ReplaceString(const JSCallbackInfo& info)
{
    if (info.Length() != 3 || !info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsString()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    int32_t start = info[0]->ToNumber<int32_t>();
    int32_t length = info[1]->ToNumber<int32_t>();
    auto controller = GetMutableController().Upgrade();
    CHECK_NULL_VOID(controller);
    if (!CheckParameters(start, length)) {
        return;
    }
    std::string data = info[2]->ToString();
    controller->ReplaceString(start, length, data);
}

void JSMutableSpanString::InsertString(const JSCallbackInfo& info)
{
    if (info.Length() != 2 || !info[0]->IsNumber() || !info[1]->IsString()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto start = info[0]->ToNumber<int32_t>();
    std::string data = info[1]->ToString();
    auto controller = GetMutableController().Upgrade();
    CHECK_NULL_VOID(controller);
    // The input parameter must not cross the boundary.
    auto characterLength = controller->GetLength();
    if (start < 0 || start > characterLength) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s start: %d StyledStringLength: %d",
            "Out of bounds", start, characterLength);
        return;
    }
    controller->InsertString(start, data);
}

void JSMutableSpanString::RemoveString(const JSCallbackInfo& info)
{
    if (info.Length() != 2 || !info[0]->IsNumber() || !info[1]->IsNumber()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto start = info[0]->ToNumber<int32_t>();
    auto length = info[1]->ToNumber<int32_t>();
    auto controller = GetMutableController().Upgrade();
    CHECK_NULL_VOID(controller);
    if (!CheckParameters(start, length)) {
        return;
    }
    controller->RemoveString(start, length);
}

bool JSMutableSpanString::IsImageNode(int32_t location)
{
    auto mutableSpanString = mutableSpanString_.Upgrade();
    CHECK_NULL_RETURN(mutableSpanString, false);
    return mutableSpanString->IsSpeicalNode(location, SpanType::Image);
}

bool JSMutableSpanString::IsCustomSpanNode(int32_t location)
{
    auto mutableSpanString = mutableSpanString_.Upgrade();
    CHECK_NULL_RETURN(mutableSpanString, false);
    return mutableSpanString->IsSpeicalNode(location, SpanType::CustomSpan);
}

bool JSMutableSpanString::VerifyImageParameters(int32_t start, int32_t length)
{
    if (length != 1) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "VerifyImageParameters failed: length should be one");
        return false;
    }
    if (!IsImageNode(start)) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "VerifyCustomSpanParameters failed: Not ImageNode");
        return false;
    }
    return true;
}

bool JSMutableSpanString::VerifyCustomSpanParameters(int32_t start, int32_t length)
{
    if (length != 1) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "VerifyCustomSpanParameters failed: length should be one");
        return false;
    }
    if (!IsCustomSpanNode(start)) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "VerifyCustomSpanParameters failed: Not CustomSpanNode");
        return false;
    }
    return true;
}

void JSMutableSpanString::ReplaceSpan(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsObject()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto startObj = paramObject->GetProperty("start");
    auto lengthObj = paramObject->GetProperty("length");
    auto styleKeyObj = paramObject->GetProperty("styledKey");
    auto styleValueObj = paramObject->GetProperty("styledValue");
    if (!startObj->IsNumber() || !lengthObj->IsNumber() || !styleKeyObj->IsNumber() || !styleValueObj->IsObject()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto spanType = styleKeyObj->ToNumber<int32_t>();
    if (!CheckSpanType(spanType)) {
        return;
    }
    auto start = startObj->ToNumber<int32_t>();
    auto length = lengthObj->ToNumber<int32_t>();
    auto type = static_cast<SpanType>(spanType);
    if (type == SpanType::Image && !VerifyImageParameters(start, length)) {
        return;
    }
    if (type == SpanType::CustomSpan && !VerifyCustomSpanParameters(start, length)) {
        return;
    }
    if (!styleValueObj->IsObject()) {
        return;
    }
    auto spanBase = ParseJsSpanBaseWithoutSpecialSpan(start, length, type, JSRef<JSObject>::Cast(styleValueObj), info);
    if (!spanBase) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s",
            "ReplaceSpan failed: maybe styledKey & corresponding value not match");
        return;
    }
    auto controller = GetMutableController().Upgrade();
    CHECK_NULL_VOID(controller);
    if (!CheckParameters(start, length)) {
        return;
    }
    if (type == SpanType::Gesture) {
        auto thisObj = info.This();
        auto newIndex = gestureStyleStoreIndex_.fetch_add(1);
        std::string key = "STYLED_STRING_GESTURESTYLE_STORE_" + std::to_string(newIndex);
        thisObj->SetPropertyObject(key.c_str(), styleValueObj);
    }
    controller->ReplaceSpan(start, length, spanBase);
}

void JSMutableSpanString::AddSpan(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsObject()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto startObj = paramObject->GetProperty("start");
    auto lengthObj = paramObject->GetProperty("length");
    auto styleKeyObj = paramObject->GetProperty("styledKey");
    auto styleValueObj = paramObject->GetProperty("styledValue");
    if (!startObj->IsNumber() || !lengthObj->IsNumber() || !styleKeyObj->IsNumber() || !styleValueObj->IsObject()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto spanType = styleKeyObj->ToNumber<int32_t>();
    CHECK_NULL_VOID(CheckSpanType(spanType));
    auto start = startObj->ToNumber<int32_t>();
    auto length = lengthObj->ToNumber<int32_t>();
    auto type = static_cast<SpanType>(spanType);
    if (type == SpanType::Image && !VerifyImageParameters(start, length)) {
        return;
    }
    if (type == SpanType::CustomSpan && !VerifyCustomSpanParameters(start, length)) {
        return;
    }
    CHECK_NULL_VOID(styleValueObj->IsObject());
    auto spanBase = ParseJsSpanBaseWithoutSpecialSpan(start, length, type, JSRef<JSObject>::Cast(styleValueObj), info);
    if (!spanBase) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s",
            "AddSpan failed: maybe styledKey & corresponding value not match");
        return;
    }
    auto controller = GetMutableController().Upgrade();
    CHECK_NULL_VOID(controller);
    if (!CheckParameters(start, length)) {
        return;
    }
    if (type == SpanType::Image) {
        controller->RemoveSpan(start, length, SpanType::Image);
    } else if (type == SpanType::CustomSpan) {
        controller->RemoveSpan(start, length, SpanType::CustomSpan);
    } else if (type == SpanType::Gesture) {
        auto thisObj = info.This();
        auto newIndex = gestureStyleStoreIndex_.fetch_add(1);
        std::string key = "STYLED_STRING_GESTURESTYLE_STORE_" + std::to_string(newIndex);
        thisObj->SetPropertyObject(key.c_str(), styleValueObj);
    }
    controller->AddSpan(spanBase);
}

void JSMutableSpanString::RemoveSpan(const JSCallbackInfo& info)
{
    if (info.Length() != 3 || !info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto start = info[0]->ToNumber<int32_t>();
    auto length = info[1]->ToNumber<int32_t>();
    auto spanType = info[2]->ToNumber<int32_t>();
    if (!CheckSpanType(spanType)) {
        return;
    }
    auto type = static_cast<SpanType>(spanType);
    auto controller = GetMutableController().Upgrade();
    CHECK_NULL_VOID(controller);
    if (!CheckParameters(start, length)) {
        return;
    }
    controller->RemoveSpan(start, length, type);
}

void JSMutableSpanString::RemoveSpans(const JSCallbackInfo& info)
{
    if (info.Length() != 2 || !info[0]->IsNumber() || !info[1]->IsNumber()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto controller = GetMutableController().Upgrade();
    CHECK_NULL_VOID(controller);
    auto start = info[0]->ToNumber<int32_t>();
    auto length = info[1]->ToNumber<int32_t>();
    if (!CheckParameters(start, length)) {
        return;
    }
    controller->RemoveSpans(start, length);
}

void JSMutableSpanString::ClearAllSpans()
{
    auto controller = GetMutableController().Upgrade();
    CHECK_NULL_VOID(controller);
    controller->ClearAllSpans();
}

void JSMutableSpanString::ReplaceSpanString(const JSCallbackInfo& info)
{
    if (info.Length() != 3 || !info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsObject()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto start = info[0]->ToNumber<int32_t>();
    auto length = info[1]->ToNumber<int32_t>();
    auto* spanString = JSRef<JSObject>::Cast(info[2])->Unwrap<JSSpanString>();
    if (!spanString) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Failed To Parse StyledString");
        return;
    }
    auto spanStringController = spanString->GetController();
    CHECK_NULL_VOID(spanStringController);
    auto controller = GetMutableController().Upgrade();
    CHECK_NULL_VOID(controller);
    if (!CheckParameters(start, length)) {
        return;
    }
    auto thisObj = info.This();
    auto newIndex = spanStringStoreIndex_.fetch_add(1);
    std::string key = "STYLED_STRING_SPANSTRING_STORE_" + std::to_string(newIndex);
    thisObj->SetPropertyObject(key.c_str(), info[0]);
    controller->ReplaceSpanString(start, length, spanStringController);
}

void JSMutableSpanString::InsertSpanString(const JSCallbackInfo& info)
{
    if (info.Length() != 2 || !info[0]->IsNumber() || !info[1]->IsObject()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto start = info[0]->ToNumber<int32_t>();
    auto* spanString = JSRef<JSObject>::Cast(info[1])->Unwrap<JSSpanString>();
    if (!spanString) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Failed To Parse StyledString");
        return;
    }
    auto spanStringController = spanString->GetController();
    CHECK_NULL_VOID(spanStringController);
    auto controller = GetMutableController().Upgrade();
    CHECK_NULL_VOID(controller);
    // The input parameter must not cross the boundary.
    auto characterLength = controller->GetLength();
    if (start < 0 || start > characterLength) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s start: %d StyledStringLength: %d",
            "Out of bounds", start, characterLength);
        return;
    }
    auto thisObj = info.This();
    auto newIndex = spanStringStoreIndex_.fetch_add(1);
    std::string key = "STYLED_STRING_SPANSTRING_STORE_" + std::to_string(newIndex);
    thisObj->SetPropertyObject(key.c_str(), info[0]);
    controller->InsertSpanString(start, spanStringController);
}

void JSMutableSpanString::AppendSpanString(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsObject()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto* spanString = JSRef<JSObject>::Cast(info[0])->Unwrap<JSSpanString>();
    if (!spanString) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Failed To Parse StyledString");
        return;
    }
    auto spanStringController = spanString->GetController();
    CHECK_NULL_VOID(spanStringController);
    auto controller = GetMutableController().Upgrade();
    CHECK_NULL_VOID(controller);
    auto thisObj = info.This();
    auto newIndex = spanStringStoreIndex_.fetch_add(1);
    std::string key = "STYLED_STRING_SPANSTRING_STORE_" + std::to_string(newIndex);
    thisObj->SetPropertyObject(key.c_str(), info[0]);
    controller->AppendSpanString(spanStringController);
}

WeakPtr<MutableSpanString>& JSMutableSpanString::GetMutableController()
{
    return mutableSpanString_;
}

void JSMutableSpanString::SetMutableController(const RefPtr<MutableSpanString>& mutableSpanString)
{
    mutableSpanString_ = mutableSpanString;
}

} // namespace OHOS::Ace::Framework