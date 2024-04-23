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

#include "frameworks/bridge/declarative_frontend/style_string/js_span_object.h"

#include <numeric>
#include <string>

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "base/log/ace_scoring_log.h"
#include "base/memory/ace_type.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_richeditor.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_image.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

CalcDimension ParseLengthMetrics(const JSRef<JSObject>& obj, bool withoutPercent = true)
{
    auto value = 0.0;
    auto valueObj = obj->GetProperty("value");
    if (!valueObj->IsNull() && valueObj->IsNumber()) {
        value = valueObj->ToNumber<float>();
    }
    auto unit = DimensionUnit::VP;
    auto unitObj = obj->GetProperty("unit");
    if (!unitObj->IsNull() && unitObj->IsNumber()) {
        unit = static_cast<DimensionUnit>(unitObj->ToNumber<int32_t>());
    }
    CalcDimension size = CalcDimension(value, unit);
    if (withoutPercent && unit == DimensionUnit::PERCENT) {
        size = CalcDimension(0, DimensionUnit::VP);
    }
    return size;
}

void JSFontSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSFontSpan>::Declare("TextStyle");
    JSClass<JSFontSpan>::CustomProperty("fontColor", &JSFontSpan::GetFontColor, &JSFontSpan::SetFontColor);
    JSClass<JSFontSpan>::CustomProperty("fontSize", &JSFontSpan::GetFontSize, &JSFontSpan::SetFontSize);
    JSClass<JSFontSpan>::CustomProperty("fontStyle", &JSFontSpan::GetFontStyle, &JSFontSpan::SetFontStyle);
    JSClass<JSFontSpan>::CustomProperty("fontWeight", &JSFontSpan::GetFontWeight, &JSFontSpan::SetFontWeight);
    JSClass<JSFontSpan>::CustomProperty("fontFamily", &JSFontSpan::GetFontFamily, &JSFontSpan::SetFontFamily);
    JSClass<JSFontSpan>::Bind(globalObj, JSFontSpan::Constructor, JSFontSpan::Destructor);
}

void JSFontSpan::Constructor(const JSCallbackInfo& args)
{
    auto fontSpan = Referenced::MakeRefPtr<JSFontSpan>();
    fontSpan->IncRefCount();

    RefPtr<FontSpan> span;
    if (args.Length() <= 0) {
        Font font;
        span = AceType::MakeRefPtr<FontSpan>(font);
    } else {
        span = JSFontSpan::ParseJsFontSpan(JSRef<JSObject>::Cast(args[0]));
    }
    fontSpan->fontSpan_ = span;
    args.SetReturnValue(Referenced::RawPtr(fontSpan));
}

void JSFontSpan::Destructor(JSFontSpan* fontSpan)
{
    if (fontSpan != nullptr) {
        fontSpan->DecRefCount();
    }
}

RefPtr<FontSpan> JSFontSpan::ParseJsFontSpan(const JSRef<JSObject>& obj)
{
    Font font;
    ParseJsFontColor(obj, font);
    ParseJsFontSize(obj, font);
    ParseJsFontWeight(obj, font);
    ParseJsFontFamily(obj, font);
    ParseJsFontStyle(obj, font);
    return AceType::MakeRefPtr<FontSpan>(font);
}

void JSFontSpan::ParseJsFontColor(const JSRef<JSObject>& obj, Font& font)
{
    if (obj->HasProperty("fontColor")) {
        JSRef<JSVal> colorObj = JSRef<JSVal>::Cast(obj->GetProperty("fontColor"));
        Color color;
        if (!colorObj->IsNull() && !JSViewAbstract::ParseJsColor(colorObj, color)) {
            auto context = PipelineBase::GetCurrentContextSafely();
            CHECK_NULL_VOID(context);
            auto theme = context->GetTheme<TextTheme>();
            CHECK_NULL_VOID(theme);
            color = theme->GetTextStyle().GetTextColor();
        }
        font.fontColor = color;
    }
}

void JSFontSpan::ParseJsFontSize(const JSRef<JSObject>& obj, Font& font)
{
    if (obj->HasProperty("fontSize")) {
        auto context = PipelineBase::GetCurrentContextSafely();
        CHECK_NULL_VOID(context);
        auto theme = context->GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        auto fontSize = obj->GetProperty("fontSize");
        CalcDimension size = theme->GetTextStyle().GetFontSize();
        if (!fontSize->IsNull() && fontSize->IsObject()) {
            auto sizeTmp = ParseLengthMetrics(fontSize, false);
            if (sizeTmp.Value() >= 0 && sizeTmp.Unit() != DimensionUnit::PERCENT) {
                size = sizeTmp;
            }
        }
        font.fontSize = size;
    }
}

void JSFontSpan::ParseJsFontWeight(const JSRef<JSObject>& obj, Font& font)
{
    if (obj->HasProperty("fontWeight")) {
        auto fontWeight = obj->GetProperty("fontWeight");
        std::string weight = "";
        if (fontWeight->IsNumber()) {
            weight = std::to_string(fontWeight->ToNumber<int32_t>());
        } else {
            JSViewAbstract::ParseJsString(fontWeight, weight);
        }
        if (weight != "") {
            font.fontWeight = ConvertStrToFontWeight(weight);
        } else {
            auto context = PipelineBase::GetCurrentContextSafely();
            CHECK_NULL_VOID(context);
            auto theme = context->GetTheme<TextTheme>();
            CHECK_NULL_VOID(theme);
            font.fontWeight = theme->GetTextStyle().GetFontWeight();
        }
    }
}

void JSFontSpan::ParseJsFontFamily(const JSRef<JSObject>& obj, Font& font)
{
    if (obj->HasProperty("fontFamily")) {
        auto fontFamily = obj->GetProperty("fontFamily");
        std::vector<std::string> fontFamilies;
        if (JSViewAbstract::ParseJsFontFamilies(fontFamily, fontFamilies)) {
            font.fontFamiliesNG = fontFamilies;
        } else {
            auto context = PipelineBase::GetCurrentContextSafely();
            CHECK_NULL_VOID(context);
            auto theme = context->GetTheme<TextTheme>();
            CHECK_NULL_VOID(theme);
            font.fontFamiliesNG = theme->GetTextStyle().GetFontFamilies();
        }
    }
}

void JSFontSpan::ParseJsFontStyle(const JSRef<JSObject>& obj, Font& font)
{
    if (obj->HasProperty("fontStyle")) {
        auto style = obj->GetProperty("fontStyle");
        OHOS::Ace::FontStyle fontStyle = FontStyle::NORMAL;
        if (!style->IsNull() && style->IsNumber()) {
            auto value = style->ToNumber<int32_t>();
            if (value >= 0 && value < static_cast<int32_t>(FontStyle::NONE)) {
                fontStyle = static_cast<FontStyle>(value);
            }
        }
        font.fontStyle = fontStyle;
    }
}

void JSFontSpan::GetFontColor(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(fontSpan_);
    if (!fontSpan_->GetFont().fontColor.has_value()) {
        return;
    }
    auto ret = JSRef<JSVal>::Make(JSVal(ToJSValue(fontSpan_->GetFont().fontColor.value().ColorToString())));
    info.SetReturnValue(ret);
}

void JSFontSpan::SetFontColor(const JSCallbackInfo& info) {}

void JSFontSpan::GetFontSize(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(fontSpan_);
    if (!fontSpan_->GetFont().fontSize.has_value()) {
        return;
    }
    auto ret = JSRef<JSVal>::Make(JSVal(ToJSValue(fontSpan_->GetFont().fontSize.value().ConvertToVp())));
    info.SetReturnValue(ret);
}

void JSFontSpan::SetFontSize(const JSCallbackInfo& info) {}

void JSFontSpan::GetFontStyle(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(fontSpan_);
    if (!fontSpan_->GetFont().fontStyle.has_value()) {
        return;
    }
    auto ret = JSRef<JSVal>::Make(
        JSVal(ToJSValue(std::to_string(static_cast<int32_t>(fontSpan_->GetFont().fontStyle.value())))));
    info.SetReturnValue(ret);
}

void JSFontSpan::SetFontStyle(const JSCallbackInfo& info) {}

void JSFontSpan::GetFontWeight(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(fontSpan_);
    if (!fontSpan_->GetFont().fontWeight.has_value()) {
        return;
    }
    auto ret = JSRef<JSVal>::Make(
        JSVal(ToJSValue(std::to_string(static_cast<int32_t>(fontSpan_->GetFont().fontWeight.value())))));
    info.SetReturnValue(ret);
}

void JSFontSpan::SetFontWeight(const JSCallbackInfo& info) {}

void JSFontSpan::GetFontFamily(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(fontSpan_);
    if (!fontSpan_->GetFont().fontFamiliesNG.has_value()) {
        return;
    }
    auto fontFamilies = fontSpan_->GetFont().fontFamiliesNG.value();
    auto retStr = std::accumulate(fontFamilies.begin(), fontFamilies.end(), std::string());
    auto ret = JSRef<JSVal>::Make(JSVal(ToJSValue(retStr)));
    info.SetReturnValue(ret);
}

void JSFontSpan::SetFontFamily(const JSCallbackInfo& info) {}

const RefPtr<FontSpan>& JSFontSpan::GetFontSpan()
{
    return fontSpan_;
}

void JSFontSpan::SetFontSpan(const RefPtr<FontSpan>& fontSpan)
{
    fontSpan_ = fontSpan;
}

void JSDecorationSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSDecorationSpan>::Declare("DecorationStyle");
    JSClass<JSDecorationSpan>::CustomProperty(
        "type", &JSDecorationSpan::GetTextDecorationType, &JSDecorationSpan::SetTextDecorationType);
    JSClass<JSDecorationSpan>::CustomProperty(
        "color", &JSDecorationSpan::GetTextDecorationColor, &JSDecorationSpan::SetTextDecorationColor);
    JSClass<JSDecorationSpan>::CustomProperty(
        "style", &JSDecorationSpan::GetTextDecorationStyle, &JSDecorationSpan::SetTextDecorationStyle);
    JSClass<JSDecorationSpan>::Bind(globalObj, JSDecorationSpan::Constructor, JSDecorationSpan::Destructor);
}

void JSDecorationSpan::Constructor(const JSCallbackInfo& args)
{
    auto decorationSpan = Referenced::MakeRefPtr<JSDecorationSpan>();
    decorationSpan->IncRefCount();

    RefPtr<DecorationSpan> span;
    if (args.Length() <= 0) {
        span = AceType::MakeRefPtr<DecorationSpan>();
    } else {
        span = JSDecorationSpan::ParseJsDecorationSpan(JSRef<JSObject>::Cast(args[0]));
    }
    decorationSpan->decorationSpan_ = span;
    args.SetReturnValue(Referenced::RawPtr(decorationSpan));
}

void JSDecorationSpan::Destructor(JSDecorationSpan* decorationSpan)
{
    if (decorationSpan != nullptr) {
        decorationSpan->DecRefCount();
    }
}

RefPtr<DecorationSpan> JSDecorationSpan::ParseJsDecorationSpan(const JSRef<JSObject>& obj)
{
    std::optional<Color> colorOption;
    Color color;
    JSRef<JSVal> colorObj = JSRef<JSVal>::Cast(obj->GetProperty("color"));
    if (!colorObj->IsNull() && JSViewAbstract::ParseJsColor(colorObj, color)) {
        colorOption = color;
    }
    std::optional<TextDecorationStyle> styleOption;
    JSRef<JSVal> styleObj = JSRef<JSVal>::Cast(obj->GetProperty("style"));
    if (!styleObj->IsNull() && styleObj->IsNumber()) {
        styleOption = static_cast<TextDecorationStyle>(styleObj->ToNumber<int32_t>());
    }
    TextDecoration type = TextDecoration::NONE;
    JSRef<JSVal> typeObj = JSRef<JSVal>::Cast(obj->GetProperty("type"));
    if (!typeObj->IsNull() && typeObj->IsNumber()) {
        type = static_cast<TextDecoration>(typeObj->ToNumber<int32_t>());
    }
    return AceType::MakeRefPtr<DecorationSpan>(type, colorOption, styleOption);
}

void JSDecorationSpan::GetTextDecorationType(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(decorationSpan_);
    auto ret = JSRef<JSVal>::Make(JSVal(ToJSValue(static_cast<int32_t>(decorationSpan_->GetTextDecorationType()))));
    info.SetReturnValue(ret);
}

void JSDecorationSpan::SetTextDecorationType(const JSCallbackInfo& info) {}

void JSDecorationSpan::GetTextDecorationColor(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(decorationSpan_);
    if (!decorationSpan_->GetColor().has_value()) {
        return;
    }
    auto ret = JSRef<JSVal>::Make(JSVal(ToJSValue(decorationSpan_->GetColor()->ColorToString())));
    info.SetReturnValue(ret);
}

void JSDecorationSpan::SetTextDecorationColor(const JSCallbackInfo& info) {}

void JSDecorationSpan::GetTextDecorationStyle(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(decorationSpan_);
    if (!decorationSpan_->GetTextDecorationStyle().has_value()) {
        return;
    }
    auto ret =
        JSRef<JSVal>::Make(JSVal(ToJSValue(static_cast<int32_t>(decorationSpan_->GetTextDecorationStyle().value()))));
    info.SetReturnValue(ret);
}

void JSDecorationSpan::SetTextDecorationStyle(const JSCallbackInfo& info) {}

RefPtr<DecorationSpan>& JSDecorationSpan::GetDecorationSpan()
{
    return decorationSpan_;
}

void JSDecorationSpan::SetDecorationSpan(const RefPtr<DecorationSpan>& decorationSpan)
{
    decorationSpan_ = decorationSpan;
}

void JSBaselineOffsetSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSBaselineOffsetSpan>::Declare("BaselineOffsetStyle");
    JSClass<JSBaselineOffsetSpan>::CustomProperty(
        "baselineOffset", &JSBaselineOffsetSpan::GetBaselineOffset, &JSBaselineOffsetSpan::SetBaselineOffset);
    JSClass<JSBaselineOffsetSpan>::Bind(globalObj, JSBaselineOffsetSpan::Constructor, JSBaselineOffsetSpan::Destructor);
}

void JSBaselineOffsetSpan::Constructor(const JSCallbackInfo& args)
{
    auto baselineOffsetSpan = Referenced::MakeRefPtr<JSBaselineOffsetSpan>();
    baselineOffsetSpan->IncRefCount();
    RefPtr<BaselineOffsetSpan> span;
    if (args.Length() <= 0) {
        span = AceType::MakeRefPtr<BaselineOffsetSpan>();
    } else {
        span = JSBaselineOffsetSpan::ParseJSBaselineOffsetSpan(JSRef<JSObject>::Cast(args[0]));
    }
    baselineOffsetSpan->baselineOffsetSpan_ = span;
    args.SetReturnValue(Referenced::RawPtr(baselineOffsetSpan));
}

void JSBaselineOffsetSpan::Destructor(JSBaselineOffsetSpan* baselineOffsetSpan)
{
    if (baselineOffsetSpan != nullptr) {
        baselineOffsetSpan->DecRefCount();
    }
}

RefPtr<BaselineOffsetSpan> JSBaselineOffsetSpan::ParseJSBaselineOffsetSpan(const JSRef<JSObject>& obj)
{
    if (obj->IsUndefined()) {
        return AceType::MakeRefPtr<BaselineOffsetSpan>(CalcDimension(0, DimensionUnit::VP));
    }
    return AceType::MakeRefPtr<BaselineOffsetSpan>(ParseLengthMetrics(obj));
}

void JSBaselineOffsetSpan::GetBaselineOffset(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(baselineOffsetSpan_);
    auto ret = JSRef<JSVal>::Make(JSVal(ToJSValue(baselineOffsetSpan_->GetBaselineOffset().ConvertToVp())));
    info.SetReturnValue(ret);
}

void JSBaselineOffsetSpan::SetBaselineOffset(const JSCallbackInfo& info) {}

RefPtr<BaselineOffsetSpan>& JSBaselineOffsetSpan::GetBaselineOffsetSpan()
{
    return baselineOffsetSpan_;
}

void JSBaselineOffsetSpan::SetBaselineOffsetSpan(const RefPtr<BaselineOffsetSpan>& baselineOffsetSpan)
{
    baselineOffsetSpan_ = baselineOffsetSpan;
}

void JSLetterSpacingSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSLetterSpacingSpan>::Declare("LetterSpacingStyle");
    JSClass<JSLetterSpacingSpan>::CustomProperty(
        "letterSpacing", &JSLetterSpacingSpan::GetLetterSpacing, &JSLetterSpacingSpan::SetLetterSpacing);
    JSClass<JSLetterSpacingSpan>::Bind(globalObj, JSLetterSpacingSpan::Constructor, JSLetterSpacingSpan::Destructor);
}

void JSLetterSpacingSpan::Constructor(const JSCallbackInfo& args)
{
    auto letterSpacingSpan = Referenced::MakeRefPtr<JSLetterSpacingSpan>();
    letterSpacingSpan->IncRefCount();

    RefPtr<LetterSpacingSpan> span;
    if (args.Length() <= 0) {
        span = AceType::MakeRefPtr<LetterSpacingSpan>();
    } else {
        span = JSLetterSpacingSpan::ParseJSLetterSpacingSpan(JSRef<JSObject>::Cast(args[0]));
    }
    letterSpacingSpan->letterSpacingSpan_ = span;
    args.SetReturnValue(Referenced::RawPtr(letterSpacingSpan));
}

void JSLetterSpacingSpan::Destructor(JSLetterSpacingSpan* letterSpacingSpan)
{
    if (letterSpacingSpan != nullptr) {
        letterSpacingSpan->DecRefCount();
    }
}

RefPtr<LetterSpacingSpan> JSLetterSpacingSpan::ParseJSLetterSpacingSpan(const JSRef<JSObject>& obj)
{
    if (obj->IsUndefined()) {
        return AceType::MakeRefPtr<LetterSpacingSpan>(CalcDimension(0, DimensionUnit::VP));
    }
    return AceType::MakeRefPtr<LetterSpacingSpan>(ParseLengthMetrics(obj));
}

void JSLetterSpacingSpan::GetLetterSpacing(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(letterSpacingSpan_);
    auto ret = JSRef<JSVal>::Make(JSVal(ToJSValue(letterSpacingSpan_->GetLetterSpacing().ConvertToVp())));
    info.SetReturnValue(ret);
}

void JSLetterSpacingSpan::SetLetterSpacing(const JSCallbackInfo& info) {}

RefPtr<LetterSpacingSpan>& JSLetterSpacingSpan::GetLetterSpacingSpan()
{
    return letterSpacingSpan_;
}

void JSLetterSpacingSpan::SetLetterSpacingSpan(const RefPtr<LetterSpacingSpan>& letterSpacingSpan)
{
    letterSpacingSpan_ = letterSpacingSpan;
}

void JSGestureSpan::Constructor(const JSCallbackInfo& args)
{
    auto gestureSpan = Referenced::MakeRefPtr<JSGestureSpan>();
    gestureSpan->IncRefCount();

    RefPtr<GestureSpan> span;
    if (args.Length() <= 0) {
        GestureStyle gestureInfo;
        span = AceType::MakeRefPtr<GestureSpan>(gestureInfo);
    } else {
        span = JSGestureSpan::ParseJSGestureSpan(args);
    }
    gestureSpan->gestureSpan_ = span;
    args.SetReturnValue(Referenced::RawPtr(gestureSpan));
}

void JSGestureSpan::Destructor(JSGestureSpan* gestureSpan)
{
    if (gestureSpan != nullptr) {
        gestureSpan->DecRefCount();
    }
}

void JSGestureSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSGestureSpan>::Declare("GestureStyle");
    JSClass<JSGestureSpan>::Bind(globalObj, JSGestureSpan::Constructor, JSGestureSpan::Destructor);
}

RefPtr<GestureSpan> JSGestureSpan::ParseJSGestureSpan(const JSCallbackInfo& args)
{
    JSRef<JSObject> object = JSRef<JSObject>::Cast(args[0]);
    GestureStyle gestureInfo;

    auto clickFunc = object->GetProperty("onClick");
    if (!clickFunc->IsFunction() || clickFunc->IsUndefined()) {
        gestureInfo.onClick = std::nullopt;
    } else {
        auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(clickFunc));
        auto onClick = [execCtx = args.GetExecutionContext(), func = jsOnClickFunc](BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto* clickInfo = TypeInfoHelper::DynamicCast<GestureEvent>(info);
            ACE_SCORING_EVENT("SpanString.onClick");
            func->Execute(*clickInfo);
        };
        auto tmpClickFunc = [func = std::move(onClick)](GestureEvent& info) { func(&info); };
        gestureInfo.onClick = std::move(tmpClickFunc);
    }

    auto longPressFunc = object->GetProperty("onLongPress");
    if (!longPressFunc->IsFunction() || longPressFunc->IsUndefined()) {
        gestureInfo.onLongPress = std::nullopt;
    } else {
        auto jsOnLongPressFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(longPressFunc));
        auto onLongPress = [execCtx = args.GetExecutionContext(), func = jsOnLongPressFunc](BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto* longPressInfo = TypeInfoHelper::DynamicCast<GestureEvent>(info);
            ACE_SCORING_EVENT("SpanString.onLongPress");
            func->Execute(*longPressInfo);
        };
        auto tmpLongPressFunc = [func = std::move(onLongPress)](GestureEvent& info) { func(&info); };
        gestureInfo.onLongPress = std::move(tmpLongPressFunc);
    }

    return AceType::MakeRefPtr<GestureSpan>(gestureInfo);
}

RefPtr<GestureSpan>& JSGestureSpan::GetGestureSpan()
{
    return gestureSpan_;
}

void JSGestureSpan::SetGestureSpan(const RefPtr<GestureSpan>& gestureSpan)
{
    gestureSpan_ = gestureSpan;
}
void JSTextShadowSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextShadowSpan>::Declare("TextShadowStyle");
    JSClass<JSTextShadowSpan>::CustomProperty(
        "textShadow", &JSTextShadowSpan::GetTextShadow, &JSTextShadowSpan::SetTextShadow);
    JSClass<JSTextShadowSpan>::Bind(globalObj, JSTextShadowSpan::Constructor, JSTextShadowSpan::Destructor);
}

void JSTextShadowSpan::Constructor(const JSCallbackInfo& args)
{
    auto textShadowSpan = Referenced::MakeRefPtr<JSTextShadowSpan>();
    textShadowSpan->IncRefCount();

    RefPtr<TextShadowSpan> span;
    if (args.Length() <= 0) {
        std::vector<Shadow> shadows;
        span = AceType::MakeRefPtr<TextShadowSpan>(shadows);
    } else {
        span = JSTextShadowSpan::ParseJSTextShadowSpan(JSRef<JSObject>::Cast(args[0]));
    }
    textShadowSpan->textShadowSpan_ = span;
    args.SetReturnValue(Referenced::RawPtr(textShadowSpan));
}

void JSTextShadowSpan::Destructor(JSTextShadowSpan* textShadowSpan)
{
    if (textShadowSpan != nullptr) {
        textShadowSpan->DecRefCount();
    }
}

RefPtr<TextShadowSpan> JSTextShadowSpan::ParseJSTextShadowSpan(const JSRef<JSObject>& obj)
{
    std::vector<Shadow> shadows;
    ParseTextShadowFromShadowObject(obj, shadows);
    return AceType::MakeRefPtr<TextShadowSpan>(shadows);
}

void JSTextShadowSpan::GetTextShadow(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(textShadowSpan_);
    auto shadows = textShadowSpan_->GetTextShadow();

    JSRef<JSArray> result = JSRef<JSArray>::New();
    uint32_t index = 0;
    for (auto iterator = shadows.begin(); iterator != shadows.end(); ++iterator) {
        auto shadow = *iterator;
        JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
        objectTemplate->SetInternalFieldCount(1);
        JSRef<JSObject> shadowObj = objectTemplate->NewInstance();
        shadowObj->SetProperty<double>("radius", shadow.GetBlurRadius());
        shadowObj->SetProperty<double>("offsetX", shadow.GetOffset().GetX());
        shadowObj->SetProperty<double>("offsetY", shadow.GetOffset().GetY());
        shadowObj->SetProperty<std::string>("color", shadow.GetColor().ColorToString());
        shadowObj->SetProperty<int32_t>("type", static_cast<int32_t>(shadow.GetShadowType()));
        result->SetValueAt(index++, shadowObj);
    }
    info.SetReturnValue(result);
}

void JSTextShadowSpan::SetTextShadow(const JSCallbackInfo& info) {}

RefPtr<TextShadowSpan>& JSTextShadowSpan::GetTextShadowSpan()
{
    return textShadowSpan_;
}

void JSTextShadowSpan::SetTextShadowSpan(const RefPtr<TextShadowSpan>& textShadowSpan)
{
    textShadowSpan_ = textShadowSpan;
}

// JSImageAttachment
void JSImageAttachment::Constructor(const JSCallbackInfo& args)
{
    auto imageAttachment = Referenced::MakeRefPtr<JSImageAttachment>();
    imageAttachment->IncRefCount();

    RefPtr<ImageSpan> span;
    if (args.Length() <= 0) {
        ImageSpanOptions imageOption;
        span = AceType::MakeRefPtr<ImageSpan>(imageOption);
    } else {
        span = JSImageAttachment::ParseJsImageSpan(JSRef<JSObject>::Cast(args[0]));
    }
    imageAttachment->imageSpan_ = span;
    args.SetReturnValue(Referenced::RawPtr(imageAttachment));
}

void JSImageAttachment::Destructor(JSImageAttachment* imageSpan)
{
    if (imageSpan != nullptr) {
        imageSpan->DecRefCount();
    }
}

void JSImageAttachment::JSBind(BindingTarget globalObj)
{
    JSClass<JSImageAttachment>::Declare("ImageAttachment");
    JSClass<JSImageAttachment>::CustomProperty(
        "value", &JSImageAttachment::GetImageSrc, &JSImageAttachment::SetImageSrc);
    JSClass<JSImageAttachment>::CustomProperty(
        "size", &JSImageAttachment::GetImageSize, &JSImageAttachment::SetImageSize);
    JSClass<JSImageAttachment>::CustomProperty(
        "verticalAlign", &JSImageAttachment::GetImageVerticalAlign, &JSImageAttachment::SetImageVerticalAlign);
    JSClass<JSImageAttachment>::CustomProperty(
        "objectFit", &JSImageAttachment::GetImageObjectFit, &JSImageAttachment::SetImageObjectFit);
    JSClass<JSImageAttachment>::CustomProperty(
        "layoutStyle", &JSImageAttachment::GetImageLayoutStyle, &JSImageAttachment::SetImageLayoutStyle);
    JSClass<JSImageAttachment>::Bind(globalObj, JSImageAttachment::Constructor, JSImageAttachment::Destructor);
}

RefPtr<ImageSpan> JSImageAttachment::ParseJsImageSpan(const JSRef<JSObject>& obj)
{
    auto imageOptions = JSImageAttachment::CreateImageOptions(obj);
    auto imageAttribute = JSImageAttachment::ParseJsImageSpanAttribute(obj);
    imageOptions.imageAttribute = imageAttribute;
    auto imageSpan = MakeRefPtr<ImageSpan>(imageOptions);
    return imageSpan;
}

ImageSpanOptions JSImageAttachment::CreateImageOptions(const JSRef<JSObject>& obj)
{
    ImageSpanOptions options;
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, options);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, options);
    bool isCard = context->IsFormRender() && !container->IsDynamicRender();

    std::string imageSrc;
    std::string bundleName;
    std::string moduleName;
    auto imageValue = obj->GetProperty("value");
    bool srcValid = JSContainerBase::ParseJsMedia(imageValue, imageSrc);
    if (isCard && imageValue->IsString()) {
        SrcType srcType = ImageSourceInfo::ResolveURIType(imageSrc);
        bool notSupport = (srcType == SrcType::NETWORK || srcType == SrcType::FILE || srcType == SrcType::DATA_ABILITY);
        if (notSupport) {
            imageSrc.clear();
        }
    }
    JSImage::GetJsMediaBundleInfo(imageValue, bundleName, moduleName);
    options.image = imageSrc;
    options.bundleName = bundleName;
    options.moduleName = moduleName;
    if (!srcValid) {
#if defined(PIXEL_MAP_SUPPORTED)
        if (!isCard) {
            if (JSImage::IsDrawable(imageValue)) {
                options.imagePixelMap = GetDrawablePixmap(imageValue);
            } else {
                options.imagePixelMap = CreatePixelMapFromNapiValue(imageValue);
            }
        }
#endif
    }
    return options;
}

ImageSpanAttribute JSImageAttachment::ParseJsImageSpanAttribute(const JSRef<JSObject>& obj)
{
    ImageSpanAttribute imageStyle;
    auto sizeObj = obj->GetProperty("size");
    if (sizeObj->IsObject()) {
        ImageSpanSize imageSize;
        JSRef<JSArray> size = JSRef<JSArray>::Cast(sizeObj);
        JSRef<JSVal> width = size->GetProperty("width");
        CalcDimension imageSpanWidth;
        if (!width->IsNull() && JSContainerBase::ParseJsDimensionVp(width, imageSpanWidth)) {
            imageSize.width = imageSpanWidth;
        }
        JSRef<JSVal> height = size->GetProperty("height");
        CalcDimension imageSpanHeight;
        if (!height->IsNull() && JSContainerBase::ParseJsDimensionVp(height, imageSpanHeight)) {
            imageSize.height = imageSpanHeight;
        }
        imageStyle.size = imageSize;
    }
    JSRef<JSVal> verticalAlign = obj->GetProperty("verticalAlign");
    if (!verticalAlign->IsNull()) {
        auto align = static_cast<VerticalAlign>(verticalAlign->ToNumber<int32_t>());
        if (align < VerticalAlign::TOP || align > VerticalAlign::NONE) {
            align = VerticalAlign::BOTTOM;
        }
        imageStyle.verticalAlign = align;
    }
    JSRef<JSVal> objectFit = obj->GetProperty("objectFit");
    if (!objectFit->IsNull() && objectFit->IsNumber()) {
        auto fit = static_cast<ImageFit>(objectFit->ToNumber<int32_t>());
        if (fit < ImageFit::FILL || fit > ImageFit::SCALE_DOWN) {
            fit = ImageFit::COVER;
        }
        imageStyle.objectFit = fit;
    } else {
        imageStyle.objectFit = ImageFit::COVER;
    }
    auto layoutStyleObj = obj->GetProperty("layoutStyle");
    auto layoutStyleObject = JSRef<JSObject>::Cast(layoutStyleObj);
    if (!layoutStyleObject->IsUndefined()) {
        auto marginAttr = layoutStyleObject->GetProperty("margin");
        imageStyle.marginProp = JSRichEditor::ParseMarginAttr(marginAttr);
        auto paddingAttr = layoutStyleObject->GetProperty("padding");
        imageStyle.paddingProp = JSRichEditor::ParseMarginAttr(paddingAttr);
        auto borderRadiusAttr = layoutStyleObject->GetProperty("borderRadius");
        imageStyle.borderRadius = JSRichEditor::ParseBorderRadiusAttr(borderRadiusAttr);
    }
    return imageStyle;
}

void JSImageAttachment::GetImageSrc(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(imageSpan_);
    auto imageOptions = imageSpan_->GetImageSpanOptions();
    JSRef<JSVal> ret;
    if (imageOptions.image.has_value()) {
        ret = JSRef<JSVal>::Make(ToJSValue(imageOptions.image.value()));
    }
    if (imageOptions.imagePixelMap.has_value()) {
#ifdef PIXEL_MAP_SUPPORTED
        ret = ConvertPixmap(imageOptions.imagePixelMap.value());
#endif
    }
    info.SetReturnValue(ret);
}

void JSImageAttachment::GetImageSize(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(imageSpan_);
    auto imageAttr = imageSpan_->GetImageAttribute();
    if (!imageAttr.has_value() || !imageAttr->size.has_value()) {
        return;
    }
    auto imageSize = JSRef<JSObject>::New();
    imageSize->SetProperty<float>("width", imageAttr->size->width.ConvertToPx());
    imageSize->SetProperty<float>("height", imageAttr->size->height.ConvertToPx());
    info.SetReturnValue(imageSize);
}

void JSImageAttachment::GetImageVerticalAlign(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(imageSpan_);
    auto imageAttr = imageSpan_->GetImageAttribute();
    if (!imageAttr.has_value() || !imageAttr->verticalAlign.has_value()) {
        return;
    }
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(static_cast<int32_t>(imageAttr->verticalAlign.value()))));
}

void JSImageAttachment::GetImageObjectFit(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(imageSpan_);
    auto imageAttr = imageSpan_->GetImageAttribute();
    if (!imageAttr.has_value() || !imageAttr->objectFit.has_value()) {
        return;
    }
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(static_cast<int32_t>(imageAttr->objectFit.value()))));
}

JSRef<JSObject> JSImageAttachment::CreateEdge(const NG::PaddingPropertyT<NG::CalcLength>& edge)
{
    auto obj = JSRef<JSObject>::New();
    if (edge.top.has_value()) {
        obj->SetProperty("top", edge.top->GetDimension().ConvertToVp());
    }
    if (edge.bottom.has_value()) {
        obj->SetProperty("bottom", edge.bottom->GetDimension().ConvertToVp());
    }
    if (edge.left.has_value()) {
        obj->SetProperty("left", edge.left->GetDimension().ConvertToVp());
    }
    if (edge.right.has_value()) {
        obj->SetProperty("right", edge.right->GetDimension().ConvertToVp());
    }
    return obj;
}

JSRef<JSObject> JSImageAttachment::CreateBorderRadius(const NG::BorderRadiusProperty& borderRadius)
{
    auto jsBorderRadius = JSRef<JSObject>::New();
    if (borderRadius.radiusTopLeft.has_value()) {
        jsBorderRadius->SetProperty("topLeft", borderRadius.radiusTopLeft->ConvertToVp());
    }
    if (borderRadius.radiusTopRight.has_value()) {
        jsBorderRadius->SetProperty("topRight", borderRadius.radiusTopRight->ConvertToVp());
    }
    if (borderRadius.radiusBottomLeft.has_value()) {
        jsBorderRadius->SetProperty("bottomLeft", borderRadius.radiusBottomLeft->ConvertToVp());
    }
    if (borderRadius.radiusBottomRight.has_value()) {
        jsBorderRadius->SetProperty("bottomRight", borderRadius.radiusBottomRight->ConvertToVp());
    }
    return jsBorderRadius;
}

void JSImageAttachment::GetImageLayoutStyle(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(imageSpan_);
    auto imageAttr = imageSpan_->GetImageAttribute();
    if (!imageAttr.has_value()) {
        return;
    }
    auto layoutStyle = JSRef<JSObject>::New();
    if (imageAttr->marginProp.has_value()) {
        layoutStyle->SetPropertyObject("margin", CreateEdge(imageAttr->marginProp.value()));
    }
    if (imageAttr->paddingProp.has_value()) {
        layoutStyle->SetPropertyObject("padding", CreateEdge(imageAttr->paddingProp.value()));
    }
    if (imageAttr->borderRadius.has_value()) {
        layoutStyle->SetPropertyObject("borderRadius", CreateBorderRadius(imageAttr->borderRadius.value()));
    }
    info.SetReturnValue(layoutStyle);
}

const RefPtr<ImageSpan>& JSImageAttachment::GetImageSpan()
{
    return imageSpan_;
}

void JSImageAttachment::SetImageSpan(const RefPtr<ImageSpan>& imageSpan)
{
    imageSpan_ = imageSpan;
}

const ImageSpanOptions& JSImageAttachment::GetImageOptions() const
{
    return imageSpan_->GetImageSpanOptions();
}
} // namespace OHOS::Ace::Framework