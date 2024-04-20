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

#include "base/utils/utils.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_image.h"
#include "frameworks/bridge/declarative_frontend/style_string/js_span_object.h"
#include "bridge/declarative_frontend/jsview/js_richeditor.h"
namespace OHOS::Ace::Framework {
const std::unordered_set<SpanType> types = { SpanType::Font, SpanType::Gesture, SpanType::BaselineOffset,
    SpanType::Decoration, SpanType::LetterSpacing, SpanType::TextShadow, SpanType::Image };

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
                auto spanBases = JSSpanString::ParseJsSpanBaseVector(args[1], StringUtils::ToWstring(data).length());
                spanString->BindWithSpans(spanBases);
            }
        } else {
            auto attachment = JSSpanString::ParseJsImageAttachment(args[0]);
            spanString = AceType::MakeRefPtr<SpanString>(attachment);
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
    JSRef<JSObject> obj;
    switch (spanObject->GetSpanType()) {
        case SpanType::Font: {
            obj = CreateJsFontSpan(spanObject);
            break;
        }
        case SpanType::Decoration: {
            obj = CreateJsDecorationSpan(spanObject);
            break;
        }
        case SpanType::BaselineOffset: {
            obj = CreateJsBaselineOffsetSpan(spanObject);
            break;
        }
        case SpanType::LetterSpacing: {
            obj = CreateJsLetterSpacingSpan(spanObject);
            break;
        }
        case SpanType::Gesture: {
            obj = CreateJsGestureSpan(spanObject);
            break;
        }
        case SpanType::TextShadow: {
            obj = CreateJsTextShadowSpan(spanObject);
            break;
        }
        case SpanType::Image: {
            obj = CreateJsImageSpan(spanObject);
            break;
        }
        default:
            break;
    }
    resultObj->SetPropertyObject("styledValue", obj);
    return resultObj;
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

JSRef<JSObject> JSSpanString::CreateJsImageSpan(const RefPtr<SpanBase>& spanObject)
{
    auto span = AceType::DynamicCast<ImageSpan>(spanObject);
    CHECK_NULL_RETURN(span, JSRef<JSObject>::New());
    JSRef<JSObject> obj = JSClass<JSImageAttachment>::NewInstance();
    auto imageSpan = Referenced::Claim(obj->Unwrap<JSImageAttachment>());
    imageSpan->SetImageSpan(span);
    return obj;
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
        case SpanType::Image:
            return GetImageAttachment(start, length, obj);
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

RefPtr<SpanBase> JSSpanString::ParseJsDecorationSpan(int32_t start, int32_t length, const JSRef<JSObject>& obj)
{
    auto* base = obj->Unwrap<AceType>();
    auto* decorationSpan = AceType::DynamicCast<JSDecorationSpan>(base);
    if (decorationSpan && decorationSpan->GetDecorationSpan()) {
        return AceType::MakeRefPtr<DecorationSpan>(decorationSpan->GetDecorationSpan()->GetTextDecorationType(),
            decorationSpan->GetDecorationSpan()->GetColor(), start, start + length);
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

bool JSSpanString::CheckSpanType(int32_t spanType)
{
    if (types.find(static_cast<SpanType>(spanType)) == types.end()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input span type check failed.");
        return false;
    }
    return true;
}

bool JSSpanString::CheckParameters(int32_t start, int32_t length)
{
    // The input parameter must not cross the boundary.
    if (!spanString_->CheckRange(start, length)) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return false;
    }
    return true;
}

std::vector<RefPtr<SpanBase>> JSSpanString::ParseJsSpanBaseVector(const JSRef<JSObject>& obj, int32_t maxLength)
{
    std::vector<RefPtr<SpanBase>> spanBaseVector;
    auto arrays = JSRef<JSArray>::Cast(obj);
    for (size_t i = 0; i < arrays->Length(); i++) {
        JSRef<JSVal> value = arrays->GetValueAt(i);
        if (value->IsNull() || value->IsUndefined()) {
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
    auto* imageAttachment = JSRef<JSObject>::Cast(info)->Unwrap<JSImageAttachment>();
    if (!imageAttachment) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return options;
    }
    return imageAttachment->GetImageOptions();
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
                auto spanBases = JSSpanString::ParseJsSpanBaseVector(args[1], StringUtils::ToWstring(data).length());
                spanString->BindWithSpans(spanBases);
            }
        } else {
            auto attachment = JSSpanString::ParseJsImageAttachment(args[0]);
            spanString = AceType::MakeRefPtr<MutableSpanString>(attachment);
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
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
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
    return mutableSpanString->IsImageNode(location);
}

bool JSMutableSpanString::VerifyImageParameters(int32_t start, int32_t length)
{
    if (length != 1) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input span type check failed.");
        return false;
    }
    if (!IsImageNode(start)) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input span type check failed.");
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
    auto spanBase = ParseJsSpanBase(start, length, type, JSRef<JSObject>::Cast(styleValueObj));
    if (!spanBase) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto controller = GetMutableController().Upgrade();
    CHECK_NULL_VOID(controller);
    if (!CheckParameters(start, length)) {
        return;
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
    if (!CheckSpanType(spanType)) {
        return;
    }
    auto start = startObj->ToNumber<int32_t>();
    auto length = lengthObj->ToNumber<int32_t>();
    auto type = static_cast<SpanType>(spanType);
    if (type == SpanType::Image && !VerifyImageParameters(start, length)) {
        return;
    }
    auto spanBase = ParseJsSpanBase(start, length, type, JSRef<JSObject>::Cast(styleValueObj));
    if (!spanBase) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto controller = GetMutableController().Upgrade();
    CHECK_NULL_VOID(controller);
    if (!CheckParameters(start, length)) {
        return;
    }
    if (type == SpanType::Image) {
        controller->RemoveSpan(start, length, SpanType::Image);
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
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto spanStringController = spanString->GetController();
    CHECK_NULL_VOID(spanStringController);
    auto controller = GetMutableController().Upgrade();
    CHECK_NULL_VOID(controller);
    if (!CheckParameters(start, length)) {
        return;
    }
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
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto spanStringController = spanString->GetController();
    CHECK_NULL_VOID(spanStringController);
    auto controller = GetMutableController().Upgrade();
    CHECK_NULL_VOID(controller);
    // The input parameter must not cross the boundary.
    auto characterLength = controller->GetLength();
    if (start < 0 || start > characterLength) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
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
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto spanStringController = spanString->GetController();
    CHECK_NULL_VOID(spanStringController);
    auto controller = GetMutableController().Upgrade();
    CHECK_NULL_VOID(controller);
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