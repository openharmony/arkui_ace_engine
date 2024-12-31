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

#include "canvas_napi/js_canvas.h"

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "base/log/ace_scoring_log.h"
#include "base/memory/ace_type.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_richeditor.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/render/paragraph.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_span.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_image.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {
namespace {
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END, TextAlign::JUSTIFY };
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };
const int32_t WORD_BREAK_TYPES_DEFAULT = 2;
const std::vector<float> DEFAULT_COLORFILTER_MATRIX = {
    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f
};
} // namespace

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
        if (!args[0]->IsObject()) {
            return;
        }
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
    if (args.Length() <= 0 || !args[0]->IsObject()) {
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
    if (args.Length() <= 0 || !args[0]->IsObject()) {
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
    if (args.Length() <= 0 || !args[0]->IsObject()) {
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
    JSClass<JSGestureSpan>::Declare("NativeGestureStyle");
    JSClass<JSGestureSpan>::Bind(globalObj, JSGestureSpan::Constructor, JSGestureSpan::Destructor);
}

RefPtr<GestureSpan> JSGestureSpan::ParseJSGestureSpan(const JSCallbackInfo& args)
{
    GestureStyle gestureInfo;
    if (args.Length() <= 0 || !args[0]->IsObject()) {
        gestureInfo.onClick = std::nullopt;
        gestureInfo.onLongPress = std::nullopt;
        return AceType::MakeRefPtr<GestureSpan>(gestureInfo);
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(args[0]);

    auto clickFunc = object->GetProperty("onClick");
    if (!clickFunc->IsFunction() || clickFunc->IsUndefined()) {
        gestureInfo.onClick = std::nullopt;
    } else {
        auto jsOnClickFunc = AceType::MakeRefPtr<JsWeakClickFunction>(JSRef<JSFunc>::Cast(clickFunc));
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
        auto jsOnLongPressFunc = AceType::MakeRefPtr<JsWeakClickFunction>(JSRef<JSFunc>::Cast(longPressFunc));
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
    if (args.Length() <= 0 || !args[0]->IsObject()) {
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
    if (args.Length() <= 0 || !args[0]->IsObject()) {
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
    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, options);
    auto context = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_RETURN(context, options);
    bool isCard = context->IsFormRender() && !container->IsDynamicRender();

    std::string imageSrc;
    std::string bundleName;
    std::string moduleName;
    int32_t resId = 0;
    auto srcValid = obj->HasProperty("resourceValue");
    auto imageValue = srcValid ? obj->GetProperty("resourceValue") : obj->GetProperty("value");
    JSViewAbstract::ParseJsMediaWithBundleName(imageValue, imageSrc, bundleName, moduleName, resId);
    if (isCard && imageValue->IsString()) {
        SrcType srcType = ImageSourceInfo::ResolveURIType(imageSrc);
        bool notSupport = (srcType == SrcType::NETWORK || srcType == SrcType::FILE || srcType == SrcType::DATA_ABILITY);
        if (notSupport) {
            imageSrc.clear();
        }
    }
    options.image = imageSrc;
    options.bundleName = bundleName;
    options.moduleName = moduleName;
    options.isUriPureNumber = (resId == -1);
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
    ParseJsImageSpanSizeAttribute(obj, imageStyle);
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
        if (fit < ImageFit::FILL || fit > ImageFit::BOTTOM_END) {
            fit = ImageFit::COVER;
        }
        imageStyle.objectFit = fit;
    } else {
        imageStyle.objectFit = ImageFit::COVER;
    }
    auto layoutStyleObj = obj->GetProperty("layoutStyle");
    if (layoutStyleObj->IsObject()) {
        auto layoutStyleObject = JSRef<JSObject>::Cast(layoutStyleObj);
        if (!layoutStyleObject->IsUndefined()) {
            auto marginAttr = layoutStyleObject->GetProperty("margin");
            imageStyle.marginProp = JSRichEditor::ParseMarginAttr(marginAttr);
            auto paddingAttr = layoutStyleObject->GetProperty("padding");
            imageStyle.paddingProp = JSRichEditor::ParseMarginAttr(paddingAttr);
            auto borderRadiusAttr = layoutStyleObject->GetProperty("borderRadius");
            imageStyle.borderRadius = JSRichEditor::ParseBorderRadiusAttr(borderRadiusAttr);
        }
    }

    auto syncLoadObj = obj->GetProperty("syncLoad");
    if (!syncLoadObj->IsNull() && syncLoadObj->IsBoolean()) {
        imageStyle.syncLoad = syncLoadObj->ToBoolean();
    }

    ParseJsImageSpanColorFilterAttribute(obj, imageStyle);
    return imageStyle;
}

void JSImageAttachment::ParseJsImageSpanColorFilterAttribute(const JSRef<JSObject>& obj, ImageSpanAttribute& imageStyle)
{
    auto colorFilterObj = obj->GetProperty("colorFilter");
    if (colorFilterObj->IsNull()) {
        return;
    }
    if (!colorFilterObj->IsArray() && !colorFilterObj->IsObject()) {
        SetImageSpanColorFilterAttribute(imageStyle, DEFAULT_COLORFILTER_MATRIX);
        return;
    }
    if (colorFilterObj->IsObject() && !colorFilterObj->IsArray()) {
        auto drawingColorFilter = CreateDrawingColorFilter(colorFilterObj);
        if (drawingColorFilter) {
            imageStyle.colorFilterMatrix = std::nullopt;
            imageStyle.drawingColorFilter = drawingColorFilter;
            return;
        }
        JSColorFilter* colorFilter;
        if (!colorFilterObj->IsUndefined() && !colorFilterObj->IsNull()) {
            colorFilter = JSRef<JSObject>::Cast(colorFilterObj)->Unwrap<JSColorFilter>();
        } else {
            SetImageSpanColorFilterAttribute(imageStyle, DEFAULT_COLORFILTER_MATRIX);
            return;
        }
        if (colorFilter && colorFilter->GetColorFilterMatrix().size() == COLOR_FILTER_MATRIX_SIZE) {
            SetImageSpanColorFilterAttribute(imageStyle, colorFilter->GetColorFilterMatrix());
            return;
        }
        SetImageSpanColorFilterAttribute(imageStyle, DEFAULT_COLORFILTER_MATRIX);
        return;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(colorFilterObj);
    if (array->Length() != COLOR_FILTER_MATRIX_SIZE) {
        SetImageSpanColorFilterAttribute(imageStyle, DEFAULT_COLORFILTER_MATRIX);
        return;
    }
    std::vector<float> colorfilter;
    for (size_t i = 0; i < array->Length(); i++) {
        JSRef<JSVal> value = array->GetValueAt(i);
        if (!value->IsNumber()) {
            SetImageSpanColorFilterAttribute(imageStyle, DEFAULT_COLORFILTER_MATRIX);
            return;
        }
        colorfilter.emplace_back(value->ToNumber<float>());
    }
    SetImageSpanColorFilterAttribute(imageStyle, colorfilter);
}

void JSImageAttachment::SetImageSpanColorFilterAttribute(ImageSpanAttribute& imageStyle,
    const std::vector<float>& matrix)
{
    imageStyle.colorFilterMatrix = matrix;
    imageStyle.drawingColorFilter = std::nullopt;
}

void JSImageAttachment::ParseJsImageSpanSizeAttribute(const JSRef<JSObject>& obj, ImageSpanAttribute& imageStyle)
{
    auto sizeObj = obj->GetProperty("size");
    if (sizeObj->IsObject()) {
        ImageSpanSize imageSize;
        auto size = JSRef<JSObject>::Cast(sizeObj);
        JSRef<JSVal> width = size->GetProperty("width");
        CalcDimension imageSpanWidth;
        if (!width->IsNull() && JSContainerBase::ParseJsDimensionVpNG(width, imageSpanWidth, false) &&
            GreatNotEqual(imageSpanWidth.Value(), 0.0)) {
            imageSize.width = imageSpanWidth;
        }
        JSRef<JSVal> height = size->GetProperty("height");
        CalcDimension imageSpanHeight;
        if (!height->IsNull() && JSContainerBase::ParseJsDimensionVpNG(height, imageSpanHeight, false) &&
            GreatNotEqual(imageSpanHeight.Value(), 0.0)) {
            imageSize.height = imageSpanHeight;
        }
        imageStyle.size = imageSize;
    }
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
    auto size = imageAttr->size;
    if (size->width.has_value()) {
        imageSize->SetProperty<float>("width", size->width->ConvertToVp());
    } else {
        imageSize->SetProperty<float>("width", 0.0);
    }

    if (size->height.has_value()) {
        imageSize->SetProperty<float>("height", size->height->ConvertToVp());
    } else {
        imageSize->SetProperty<float>("height", 0.0);
    }
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

// JSNativeCustomSpan
void JSNativeCustomSpan::Constructor(const JSCallbackInfo& args)
{
    auto customSpan = Referenced::MakeRefPtr<JSNativeCustomSpan>();
    customSpan->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(customSpan));
}

void JSNativeCustomSpan::Destructor(JSNativeCustomSpan* customSpan)
{
    if (customSpan != nullptr) {
        customSpan->DecRefCount();
    }
}

void JSNativeCustomSpan::Invalidate(const JSCallbackInfo& info)
{
    for (const auto& styledStringWeakPtr : spanStringBaseSet_) {
        auto styledString = AceType::DynamicCast<SpanString>(styledStringWeakPtr.Upgrade());
        if (!styledString) {
            continue;
        }
        styledString->MarkDirtyFrameNode();
    }
}

void JSNativeCustomSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSNativeCustomSpan>::Declare("NativeCustomSpan");
    JSClass<JSNativeCustomSpan>::CustomMethod("invalidate", &JSNativeCustomSpan::Invalidate);
    JSClass<JSNativeCustomSpan>::Bind(globalObj, JSNativeCustomSpan::Constructor, JSNativeCustomSpan::Destructor);
}

void JSNativeCustomSpan::AddStyledString(const WeakPtr<SpanStringBase>& spanString)
{
    spanStringBaseSet_.insert(spanString);
}

void JSNativeCustomSpan::RemoveStyledString(const WeakPtr<SpanStringBase>& spanString)
{
    spanStringBaseSet_.erase(spanString);
}

// JSCustomSpan
void JSCustomSpan::AddStyledString(const WeakPtr<SpanStringBase>& spanString)
{
    CHECK_NULL_VOID(customSpan_);
    customSpan_->AddStyledString(spanString);
}

void JSCustomSpan::RemoveStyledString(const WeakPtr<SpanStringBase>& spanString)
{
    CHECK_NULL_VOID(customSpan_);
    customSpan_->RemoveStyledString(spanString);
}

JSCustomSpan::JSCustomSpan(JSRef<JSObject> customSpanObj, const JSCallbackInfo& args) : customSpanObj_(customSpanObj)
{
    auto obj = JSRef<JSObject>::Cast(customSpanObj);
    if (obj->IsUndefined()) {
        return;
    }
    JSRef<JSVal> onMeasure = obj->GetProperty("onMeasure");
    if (onMeasure->IsFunction()) {
        auto jsDrawFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(obj), JSRef<JSFunc>::Cast(onMeasure));
        auto onMeasureFunc = JSCustomSpan::ParseOnMeasureFunc(jsDrawFunc, args.GetExecutionContext());
        CustomSpan::SetOnMeasure(onMeasureFunc);
    }
    JSRef<JSVal> onDraw = obj->GetProperty("onDraw");
    if (onDraw->IsFunction()) {
        auto jsDrawFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(obj), JSRef<JSFunc>::Cast(onDraw));
        auto onDrawFunc = JSCustomSpan::ParseOnDrawFunc(jsDrawFunc, args.GetExecutionContext());
        CustomSpan::SetOnDraw(onDrawFunc);
    }
    auto type = customSpanObj->Unwrap<AceType>();
    CHECK_NULL_VOID(type);
    auto* nativeCustomSpan = AceType::DynamicCast<JSNativeCustomSpan>(type);
    customSpan_ = nativeCustomSpan;
}

JSCustomSpan::JSCustomSpan(JSRef<JSObject> customSpanObj,
    std::optional<std::function<CustomSpanMetrics(CustomSpanMeasureInfo)>> onMeasure,
    std::optional<std::function<void(NG::DrawingContext&, CustomSpanOptions)>> onDraw, int32_t start, int32_t end)
    : CustomSpan(onMeasure, onDraw, start, end), customSpanObj_(customSpanObj)
{
    auto type = customSpanObj->Unwrap<AceType>();
    CHECK_NULL_VOID(type);
    auto* nativeCustomSpan = AceType::DynamicCast<JSNativeCustomSpan>(type);
    customSpan_ = nativeCustomSpan;
}

void JSCustomSpan::SetJsCustomSpanObject(const JSRef<JSObject>& customSpanObj)
{
    customSpanObj_ = customSpanObj;
}

JSRef<JSObject>& JSCustomSpan::GetJsCustomSpanObject()
{
    return customSpanObj_;
}
RefPtr<SpanBase> JSCustomSpan::GetSubSpan(int32_t start, int32_t end)
{
    if (end - start > 1) {
        return nullptr;
    }
    RefPtr<SpanBase> spanBase = MakeRefPtr<JSCustomSpan>(customSpanObj_, GetOnMeasure(), GetOnDraw(), start, end);
    return spanBase;
}

bool JSCustomSpan::IsAttributesEqual(const RefPtr<SpanBase>& other) const
{
    auto customSpan = DynamicCast<JSCustomSpan>(other);
    if (!customSpan) {
        return false;
    }
    return (customSpan->customSpanObj_)
        ->GetLocalHandle()
        ->IsStrictEquals(customSpanObj_->GetEcmaVM(), customSpanObj_->GetLocalHandle());
}

std::function<CustomSpanMetrics(CustomSpanMeasureInfo)> JSCustomSpan::ParseOnMeasureFunc(
    const RefPtr<JsFunction>& jsDraw, const JSExecutionContext& execCtx)
{
    std::function<CustomSpanMetrics(CustomSpanMeasureInfo)> drawCallback =
        [func = std::move(jsDraw), execCtx](CustomSpanMeasureInfo customSpanMeasureInfo) -> CustomSpanMetrics {
        JAVASCRIPT_EXECUTION_SCOPE(execCtx);
        JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
        objectTemplate->SetInternalFieldCount(1);
        JSRef<JSObject> contextObj = objectTemplate->NewInstance();
        contextObj->SetProperty<float>("fontSize", customSpanMeasureInfo.fontSize);
        auto jsVal = JSRef<JSVal>::Cast(contextObj);
        auto obj = func->ExecuteJS(1, &jsVal);
        if (obj->IsObject()) {
            JSRef<JSObject> result = JSRef<JSObject>::Cast(obj);
            float width = 0;
            if (result->HasProperty("width")) {
                auto widthObj = result->GetProperty("width");
                width = widthObj->ToNumber<float>();
                if (LessNotEqual(width, 0.0)) {
                    width = 0;
                }
            }
            std::optional<float> heightOpt;
            if (result->HasProperty("height")) {
                auto heightObj = result->GetProperty("height");
                auto height = heightObj->ToNumber<float>();
                if (GreatOrEqual(height, 0.0)) {
                    heightOpt = height;
                }
            }
            return { width, heightOpt };
        }
        return { 0, 0 };
    };
    return drawCallback;
}

std::function<void(NG::DrawingContext&, CustomSpanOptions)> JSCustomSpan::ParseOnDrawFunc(
    const RefPtr<JsFunction>& jsDraw, const JSExecutionContext& execCtx)
{
    std::function<void(NG::DrawingContext&, CustomSpanOptions)> drawCallback =
        [func = std::move(jsDraw), execCtx](NG::DrawingContext& context, CustomSpanOptions customSpanOptions) -> void {
        JAVASCRIPT_EXECUTION_SCOPE(execCtx);

        JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
        objectTemplate->SetInternalFieldCount(1);
        JSRef<JSObject> contextObj = objectTemplate->NewInstance();
        JSRef<JSObject> sizeObj = objectTemplate->NewInstance();
        sizeObj->SetProperty<float>("height", PipelineBase::Px2VpWithCurrentDensity(context.height));
        sizeObj->SetProperty<float>("width", PipelineBase::Px2VpWithCurrentDensity(context.width));
        contextObj->SetPropertyObject("size", sizeObj);

        JSRef<JSObject> sizeInPxObj = objectTemplate->NewInstance();
        sizeInPxObj->SetProperty<float>("height", context.height);
        sizeInPxObj->SetProperty<float>("width", context.width);
        contextObj->SetPropertyObject("sizeInPixel", sizeInPxObj);

        auto engine = EngineHelper::GetCurrentEngine();
        CHECK_NULL_VOID(engine);
        NativeEngine* nativeEngine = engine->GetNativeEngine();
        napi_env env = reinterpret_cast<napi_env>(nativeEngine);
        ScopeRAII scope(env);
        auto jsCanvas = OHOS::Rosen::Drawing::JsCanvas::CreateJsCanvas(env, &context.canvas);
        OHOS::Rosen::Drawing::JsCanvas* unwrapCanvas = nullptr;
        napi_unwrap(env, jsCanvas, reinterpret_cast<void**>(&unwrapCanvas));
        if (unwrapCanvas) {
            unwrapCanvas->SaveCanvas();
            unwrapCanvas->ClipCanvas(context.width, context.height);
        }
        JsiRef<JsiValue> jsCanvasVal = JsConverter::ConvertNapiValueToJsVal(jsCanvas);
        contextObj->SetPropertyObject("canvas", jsCanvasVal);

        auto jsVal = JSRef<JSVal>::Cast(contextObj);
        panda::Local<JsiValue> value = jsVal.Get().GetLocalHandle();
        JSValueWrapper valueWrapper = value;
        napi_value nativeValue = nativeEngine->ValueToNapiValue(valueWrapper);

        napi_wrap(env, nativeValue, &context.canvas, [](napi_env, void*, void*) {}, nullptr, nullptr);
        JSRef<JSObject> customSpanOptionsObj = objectTemplate->NewInstance();
        customSpanOptionsObj->SetProperty<float>("x", customSpanOptions.x);
        customSpanOptionsObj->SetProperty<float>("lineTop", customSpanOptions.lineTop);
        customSpanOptionsObj->SetProperty<float>("lineBottom", customSpanOptions.lineBottom);
        customSpanOptionsObj->SetProperty<float>("baseline", customSpanOptions.baseline);
        auto customSpanOptionsVal = JSRef<JSVal>::Cast(customSpanOptionsObj);
        JSRef<JSVal> params[] = { jsVal, customSpanOptionsVal };
        func->ExecuteJS(2, params);
        if (unwrapCanvas) {
            unwrapCanvas->RestoreCanvas();
            unwrapCanvas->ResetCanvas();
        }
    };
    return drawCallback;
}

void JSLineHeightSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSLineHeightSpan>::Declare("LineHeightStyle");
    JSClass<JSLineHeightSpan>::CustomProperty(
        "lineHeight", &JSLineHeightSpan::GetLineHeight, &JSLineHeightSpan::SetLineHeight);
    JSClass<JSLineHeightSpan>::Bind(globalObj, JSLineHeightSpan::Constructor, JSLineHeightSpan::Destructor);
}

void JSLineHeightSpan::Constructor(const JSCallbackInfo& args)
{
    auto lineHeightSpan = Referenced::MakeRefPtr<JSLineHeightSpan>();
    lineHeightSpan->IncRefCount();

    RefPtr<LineHeightSpan> span;
    if (args.Length() <= 0 || !args[0]->IsObject()) {
        span = AceType::MakeRefPtr<LineHeightSpan>();
    } else {
        span = JSLineHeightSpan::ParseJSLineHeightSpan(JSRef<JSObject>::Cast(args[0]));
    }
    lineHeightSpan->lineHeightSpan_ = span;
    args.SetReturnValue(Referenced::RawPtr(lineHeightSpan));
}

void JSLineHeightSpan::Destructor(JSLineHeightSpan* lineHeightSpan)
{
    if (lineHeightSpan != nullptr) {
        lineHeightSpan->DecRefCount();
    }
}

RefPtr<LineHeightSpan> JSLineHeightSpan::ParseJSLineHeightSpan(const JSRef<JSObject>& obj)
{
    if (obj->IsUndefined()) {
        return AceType::MakeRefPtr<LineHeightSpan>(CalcDimension(0, DimensionUnit::VP));
    }
    return AceType::MakeRefPtr<LineHeightSpan>(ParseLengthMetrics(obj));
}

void JSLineHeightSpan::GetLineHeight(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(lineHeightSpan_);
    auto ret = JSRef<JSVal>::Make(JSVal(ToJSValue(lineHeightSpan_->GetLineHeight().ConvertToVp())));
    info.SetReturnValue(ret);
}

void JSLineHeightSpan::SetLineHeight(const JSCallbackInfo& info) {}

RefPtr<LineHeightSpan>& JSLineHeightSpan::GetLineHeightSpan()
{
    return lineHeightSpan_;
}

void JSLineHeightSpan::SetLineHeightSpan(const RefPtr<LineHeightSpan>& lineHeightSpan)
{
    lineHeightSpan_ = lineHeightSpan;
}

void JSParagraphStyleSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSParagraphStyleSpan>::Declare("ParagraphStyle");
    JSClass<JSParagraphStyleSpan>::CustomProperty(
        "textAlign", &JSParagraphStyleSpan::GetTextAlign, &JSParagraphStyleSpan::SetTextAlign);
    JSClass<JSParagraphStyleSpan>::CustomProperty(
        "textIndent", &JSParagraphStyleSpan::GetTextIndent, &JSParagraphStyleSpan::SetTextIndent);
    JSClass<JSParagraphStyleSpan>::CustomProperty(
        "maxLines", &JSParagraphStyleSpan::GetMaxLines, &JSParagraphStyleSpan::SetMaxLines);
    JSClass<JSParagraphStyleSpan>::CustomProperty(
        "overflow", &JSParagraphStyleSpan::GetOverflow, &JSParagraphStyleSpan::SetOverflow);
    JSClass<JSParagraphStyleSpan>::CustomProperty(
        "wordBreak", &JSParagraphStyleSpan::GetWordBreak, &JSParagraphStyleSpan::SetWordBreak);
    JSClass<JSParagraphStyleSpan>::CustomProperty(
        "leadingMargin", &JSParagraphStyleSpan::GetLeadingMargin, &JSParagraphStyleSpan::SetLeadingMargin);
    JSClass<JSParagraphStyleSpan>::Bind(globalObj, JSParagraphStyleSpan::Constructor, JSParagraphStyleSpan::Destructor);
}

void JSParagraphStyleSpan::Constructor(const JSCallbackInfo& args)
{
    auto paragraphSpan = Referenced::MakeRefPtr<JSParagraphStyleSpan>();
    paragraphSpan->IncRefCount();

    RefPtr<ParagraphStyleSpan> span;
    if (args.Length() <= 0 || !args[0]->IsObject()) {
        SpanParagraphStyle paragraphStyle;
        span = AceType::MakeRefPtr<ParagraphStyleSpan>(paragraphStyle);
    } else {
        span = JSParagraphStyleSpan::ParseJsParagraphStyleSpan(JSRef<JSObject>::Cast(args[0]));
    }
    paragraphSpan->paragraphStyleSpan_ = span;
    args.SetReturnValue(Referenced::RawPtr(paragraphSpan));
}

void JSParagraphStyleSpan::Destructor(JSParagraphStyleSpan* paragragrahSpan)
{
    if (paragragrahSpan != nullptr) {
        paragragrahSpan->DecRefCount();
    }
}

RefPtr<ParagraphStyleSpan> JSParagraphStyleSpan::ParseJsParagraphStyleSpan(const JSRef<JSObject>& obj)
{
    SpanParagraphStyle paragraphStyle;
    ParseJsTextAlign(obj, paragraphStyle);
    ParseJsTextIndent(obj, paragraphStyle);
    ParseJsMaxLines(obj, paragraphStyle);
    ParseJsTextOverflow(obj, paragraphStyle);
    ParseJsWordBreak(obj, paragraphStyle);
    ParseJsLeadingMargin(obj, paragraphStyle);
    return AceType::MakeRefPtr<ParagraphStyleSpan>(paragraphStyle);
}

void JSParagraphStyleSpan::ParseJsTextAlign(const JSRef<JSObject>& obj, SpanParagraphStyle& paragraphStyle)
{
    if (!obj->HasProperty("textAlign")) {
        return;
    }
    auto textAlignObj = obj->GetProperty("textAlign");
    int32_t value = 0;
    if (!textAlignObj->IsNull() && textAlignObj->IsNumber()) {
        value = textAlignObj->ToNumber<int32_t>();
    }
    if (value < 0 || value >= static_cast<int32_t>(TEXT_ALIGNS.size())) {
        value = 0;
    }
    paragraphStyle.align = TEXT_ALIGNS[value];
}

void JSParagraphStyleSpan::ParseJsTextIndent(const JSRef<JSObject>& obj, SpanParagraphStyle& paragraphStyle)
{
    if (!obj->HasProperty("textIndent")) {
        return;
    }
    auto textIndent = obj->GetProperty("textIndent");
    CalcDimension size;
    if (!textIndent->IsNull() && textIndent->IsObject()) {
        auto textIndentObj = JSRef<JSObject>::Cast(textIndent);
        auto value = 0.0;
        auto textIndentVal = textIndentObj->GetProperty("value");
        if (!textIndentVal->IsNull() && textIndentVal->IsNumber()) {
            value = textIndentVal->ToNumber<float>();
        }
        auto unit = DimensionUnit::VP;
        auto textIndentUnit = textIndentObj->GetProperty("unit");
        if (!textIndentUnit->IsNull() && textIndentUnit->IsNumber()) {
            unit = static_cast<DimensionUnit>(textIndentUnit->ToNumber<int32_t>());
        }
        if (value >= 0 && unit != DimensionUnit::PERCENT) {
            size = CalcDimension(value, unit);
        }
    }
    paragraphStyle.textIndent = size;
}

void JSParagraphStyleSpan::ParseJsMaxLines(const JSRef<JSObject>& obj, SpanParagraphStyle& paragraphStyle)
{
    if (!obj->HasProperty("maxLines")) {
        return;
    }
    JSRef<JSVal> args = obj->GetProperty("maxLines");
    int32_t value = Infinity<int32_t>();
    if (args->ToString() != "Infinity") {
        JSContainerBase::ParseJsInt32(args, value);
    }
    if (!args->IsUndefined()) {
        paragraphStyle.maxLines = value;
    }
}

void JSParagraphStyleSpan::ParseJsTextOverflow(const JSRef<JSObject>& obj, SpanParagraphStyle& paragraphStyle)
{
    if (!obj->HasProperty("overflow")) {
        return;
    }
    int32_t overflow = 0;
    JSRef<JSVal> overflowValue = obj->GetProperty("overflow");
    if (overflowValue->IsNumber()) {
        overflow = overflowValue->ToNumber<int32_t>();
    }
    if (overflowValue->IsUndefined() || overflow < 0 || overflow >= static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
        overflow = 0;
    }
    paragraphStyle.textOverflow = TEXT_OVERFLOWS[overflow];
}
void JSParagraphStyleSpan::ParseJsWordBreak(const JSRef<JSObject>& obj, SpanParagraphStyle& paragraphStyle)
{
    if (!obj->HasProperty("wordBreak")) {
        return;
    }
    JSRef<JSVal> args = obj->GetProperty("wordBreak");
    int32_t index = WORD_BREAK_TYPES_DEFAULT;
    if (args->IsNumber()) {
        index = args->ToNumber<int32_t>();
    }
    if (index < 0 || index >= static_cast<int32_t>(WORD_BREAK_TYPES.size())) {
        index = 0;
    }
    paragraphStyle.wordBreak = WORD_BREAK_TYPES[index];
}

bool JSParagraphStyleSpan::IsPixelMap(const JSRef<JSVal>& jsValue)
{
    if (!jsValue->IsObject()) {
        return false;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    if (jsObj->IsUndefined()) {
        return false;
    }
    JSRef<JSVal> func = jsObj->GetProperty("readPixelsToBuffer");
    return (!func->IsNull() && func->IsFunction());
}

void JSParagraphStyleSpan::ParseJsLeadingMargin(const JSRef<JSObject>& obj, SpanParagraphStyle& paragraphStyle)
{
    if (!obj->HasProperty("leadingMargin")) {
        return;
    }
    auto margin = std::make_optional<NG::LeadingMargin>();
    auto leadingMargin = obj->GetProperty("leadingMargin");
    if (!leadingMargin->IsNull() && leadingMargin->IsObject()) {
        JSRef<JSObject> leadingMarginObject = JSRef<JSObject>::Cast(leadingMargin);
        // LeadingMarginPlaceholder
        if (leadingMarginObject->HasProperty("pixelMap")) {
            ParseLeadingMarginPixelMap(leadingMarginObject, margin, leadingMargin);
        } else { // LengthMetrics
            CalcDimension width;
            auto value = 0.0;
            auto widthVal = leadingMarginObject->GetProperty("value");
            if (!widthVal->IsNull() && widthVal->IsNumber()) {
                value = widthVal->ToNumber<float>();
            }
            auto unit = DimensionUnit::VP;
            auto widthUnit = leadingMarginObject->GetProperty("unit");
            if (!widthUnit->IsNull() && widthUnit->IsNumber()) {
                unit = static_cast<DimensionUnit>(widthUnit->ToNumber<int32_t>());
            }
            if (value >= 0 && unit != DimensionUnit::PERCENT) {
                width = CalcDimension(value, unit);
            }
            margin->size = NG::LeadingMarginSize(width, Dimension(0.0, width.Unit()));
        }
    }
    paragraphStyle.leadingMargin = margin;
}

void JSParagraphStyleSpan::ParseLeadingMarginPixelMap(const JSRef<JSObject>& leadingMarginObject,
    std::optional<NG::LeadingMargin>& margin, const JsiRef<JsiValue>& leadingMargin)
{
    JSRef<JSVal> placeholder = leadingMarginObject->GetProperty("pixelMap");
    if (IsPixelMap(placeholder)) {
#if defined(PIXEL_MAP_SUPPORTED)
        auto pixelMap = CreatePixelMapFromNapiValue(placeholder);
        margin->pixmap = pixelMap;
#endif
    }
    JSRef<JSVal> sizeVal = leadingMarginObject->GetProperty("size");
    if (!sizeVal->IsUndefined() && sizeVal->IsArray()) {
        auto rangeArray = JSRef<JSArray>::Cast(sizeVal);
        JSRef<JSVal> widthVal = rangeArray->GetValueAt(0);
        JSRef<JSVal> heightVal = rangeArray->GetValueAt(1);
        CalcDimension width;
        CalcDimension height;
        JSContainerBase::ParseJsDimensionVp(widthVal, width);
        JSContainerBase::ParseJsDimensionVp(heightVal, height);
        if (LessNotEqual(width.Value(), 0.0)) {
            width = Dimension(0.0, width.Unit());
        }
        if (LessNotEqual(height.Value(), 0.0)) {
            height = Dimension(0.0, height.Unit());
        }
        margin->size = NG::LeadingMarginSize(width, height);
    } else if (sizeVal->IsUndefined()) {
        std::string resWidthStr;
        if (JSContainerBase::ParseJsString(leadingMargin, resWidthStr)) {
            CalcDimension width;
            JSContainerBase::ParseJsDimensionVp(leadingMargin, width);
            margin->size = NG::LeadingMarginSize(width, Dimension(0.0, width.Unit()));
        }
    }
}

void JSParagraphStyleSpan::GetTextAlign(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(paragraphStyleSpan_);
    if (!paragraphStyleSpan_->GetParagraphStyle().align.has_value()) {
        return;
    }
    auto ret = JSRef<JSVal>::Make(
        JSVal(ToJSValue(static_cast<int32_t>(paragraphStyleSpan_->GetParagraphStyle().align.value()))));
    info.SetReturnValue(ret);
}

void JSParagraphStyleSpan::SetTextAlign(const JSCallbackInfo& info) {}

void JSParagraphStyleSpan::GetTextIndent(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(paragraphStyleSpan_);
    if (!paragraphStyleSpan_->GetParagraphStyle().textIndent.has_value()) {
        return;
    }
    auto ret =
        JSRef<JSVal>::Make(JSVal(ToJSValue(paragraphStyleSpan_->GetParagraphStyle().textIndent.value().ConvertToVp())));
    info.SetReturnValue(ret);
}

void JSParagraphStyleSpan::SetTextIndent(const JSCallbackInfo& info) {}

void JSParagraphStyleSpan::GetMaxLines(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(paragraphStyleSpan_);
    if (!paragraphStyleSpan_->GetParagraphStyle().maxLines.has_value()) {
        return;
    }
    auto ret = JSRef<JSVal>::Make(JSVal(ToJSValue(paragraphStyleSpan_->GetParagraphStyle().maxLines.value())));
    info.SetReturnValue(ret);
}
void JSParagraphStyleSpan::SetMaxLines(const JSCallbackInfo& info) {}

void JSParagraphStyleSpan::GetOverflow(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(paragraphStyleSpan_);
    if (!paragraphStyleSpan_->GetParagraphStyle().textOverflow.has_value()) {
        return;
    }
    auto ret = JSRef<JSVal>::Make(
        JSVal(ToJSValue(static_cast<int32_t>(paragraphStyleSpan_->GetParagraphStyle().textOverflow.value()))));
    info.SetReturnValue(ret);
}
void JSParagraphStyleSpan::SetOverflow(const JSCallbackInfo& info) {}

void JSParagraphStyleSpan::GetWordBreak(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(paragraphStyleSpan_);
    if (!paragraphStyleSpan_->GetParagraphStyle().wordBreak.has_value()) {
        return;
    }
    auto ret = JSRef<JSVal>::Make(
        JSVal(ToJSValue(static_cast<int32_t>(paragraphStyleSpan_->GetParagraphStyle().wordBreak.value()))));
    info.SetReturnValue(ret);
}
void JSParagraphStyleSpan::SetWordBreak(const JSCallbackInfo& info) {}

void JSParagraphStyleSpan::GetLeadingMargin(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(paragraphStyleSpan_);
    if (!paragraphStyleSpan_->GetParagraphStyle().leadingMargin.has_value()) {
        return;
    }
    auto leadingMargin = paragraphStyleSpan_->GetParagraphStyle().leadingMargin.value();
    JSRef<JSVal> ret;
#ifdef PIXEL_MAP_SUPPORTED
    if (leadingMargin.pixmap) {
        auto lmObj = JSRef<JSObject>::New();
        auto size = JSRef<JSArray>::New();
        size->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(Dimension(leadingMargin.size.Width()).ConvertToVp())));
        size->SetValueAt(1, JSRef<JSVal>::Make(ToJSValue(Dimension(leadingMargin.size.Height()).ConvertToVp())));
        lmObj->SetPropertyObject("pixelMap", ConvertPixmap(leadingMargin.pixmap));
        lmObj->SetPropertyObject("size", size);
        ret = JSRef<JSVal>::Cast(lmObj);
    } else {
        ret = JSRef<JSVal>::Make(JSVal(ToJSValue(Dimension(leadingMargin.size.Width()).ConvertToVp())));
    }
#else
    ret = JSRef<JSVal>::Make(JSVal(ToJSValue(Dimension(leadingMargin.size.Width()).ConvertToVp())));
#endif
    info.SetReturnValue(ret);
}

void JSParagraphStyleSpan::SetLeadingMargin(const JSCallbackInfo& info) {}

RefPtr<ParagraphStyleSpan>& JSParagraphStyleSpan::GetParagraphStyleSpan()
{
    return paragraphStyleSpan_;
}

void JSParagraphStyleSpan::SetParagraphStyleSpan(const RefPtr<ParagraphStyleSpan>& paragraphStyleSpan)
{
    paragraphStyleSpan_ = paragraphStyleSpan;
}

// JSExtSpan
JSExtSpan::JSExtSpan(JSRef<JSObject> extSpanObj) : extSpanObj_(extSpanObj) {}

JSExtSpan::JSExtSpan(JSRef<JSObject> extSpanObj, int32_t start, int32_t end)
    : ExtSpan(start, end), extSpanObj_(extSpanObj)
{}

RefPtr<SpanBase> JSExtSpan::GetSubSpan(int32_t start, int32_t end)
{
    RefPtr<SpanBase> spanBase = MakeRefPtr<JSExtSpan>(extSpanObj_, start, end);
    return spanBase;
}

bool JSExtSpan::IsAttributesEqual(const RefPtr<SpanBase>& other) const
{
    auto extSpan = DynamicCast<JSExtSpan>(other);
    if (!extSpan) {
        return false;
    }
    return (extSpan->extSpanObj_)
        ->GetLocalHandle()
        ->IsStrictEquals(extSpanObj_->GetEcmaVM(), extSpanObj_->GetLocalHandle());
}

void JSExtSpan::SetJsExtSpanObject(const JSRef<JSObject>& extSpanObj)
{
    extSpanObj_ = extSpanObj;
}

JSRef<JSObject>& JSExtSpan::GetJsExtSpanObject()
{
    return extSpanObj_;
}

void JSBackgroundColorSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSBackgroundColorSpan>::Declare("BackgroundColorStyle");
    JSClass<JSBackgroundColorSpan>::CustomProperty(
        "textBackgroundStyle", &JSBackgroundColorSpan::GetBackgroundColor, &JSBackgroundColorSpan::SetBackgroundColor);
    JSClass<JSBackgroundColorSpan>::Bind(
        globalObj, JSBackgroundColorSpan::Constructor, JSBackgroundColorSpan::Destructor);
}

void JSBackgroundColorSpan::Constructor(const JSCallbackInfo& args)
{
    auto backgroundColor = Referenced::MakeRefPtr<JSBackgroundColorSpan>();
    CHECK_NULL_VOID(backgroundColor);
    backgroundColor->IncRefCount();
    RefPtr<BackgroundColorSpan> span;
    if (args.Length() <= 0 || !args[0]->IsObject()) {
        span = AceType::MakeRefPtr<BackgroundColorSpan>();
    } else {
        span = JSBackgroundColorSpan::ParseJSBackgroundColorSpan(args);
    }
    CHECK_NULL_VOID(span);
    backgroundColor->backgroundColorSpan_ = span;
    args.SetReturnValue(Referenced::RawPtr(backgroundColor));
}

void JSBackgroundColorSpan::Destructor(JSBackgroundColorSpan* backgroundColor)
{
    if (backgroundColor != nullptr) {
        backgroundColor->DecRefCount();
    }
}

RefPtr<BackgroundColorSpan> JSBackgroundColorSpan::ParseJSBackgroundColorSpan(const JSCallbackInfo& info)
{
    auto textBackgroundValue = JSContainerSpan::ParseTextBackgroundStyle(info);
    return AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundValue);
}

void JSBackgroundColorSpan::GetBackgroundColor(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(backgroundColorSpan_);
    auto backgroundColorStyle = backgroundColorSpan_->GetBackgroundColor();
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    objectTemplate->SetInternalFieldCount(1);
    JSRef<JSObject> backgroundColorObj = objectTemplate->NewInstance();
    backgroundColorObj->SetProperty<std::string>("color", backgroundColorStyle.backgroundColor->ColorToString());
    backgroundColorObj->SetProperty<std::string>(
        "BorderRadiusProperty", backgroundColorStyle.backgroundRadius->ToString());
    info.SetReturnValue(backgroundColorObj);
}

void JSBackgroundColorSpan::SetBackgroundColor(const JSCallbackInfo& info) {};

RefPtr<BackgroundColorSpan>& JSBackgroundColorSpan::GetBackgroundColorSpan()
{
    return backgroundColorSpan_;
}

void JSBackgroundColorSpan::SetBackgroundColorSpan(const RefPtr<BackgroundColorSpan>& backgroundColorSpan)
{
    backgroundColorSpan_ = backgroundColorSpan;
}

// JSUrlSpan
void JSUrlSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSUrlSpan>::Declare("UrlStyle");
    JSClass<JSUrlSpan>::CustomProperty(
        "url", &JSUrlSpan::GetUrlContext, &JSUrlSpan::SetUrlContext);
    JSClass<JSUrlSpan>::Bind(globalObj, JSUrlSpan::Constructor, JSUrlSpan::Destructor);
}

void JSUrlSpan::Constructor(const JSCallbackInfo& args)
{
    auto urlSpan = Referenced::MakeRefPtr<JSUrlSpan>();
    urlSpan->IncRefCount();
    RefPtr<UrlSpan> span;
    if (args.Length() > 0 && args[0]->IsString()) {
        auto address = args[0]->ToString();
        span = AceType::MakeRefPtr<UrlSpan>(address);
    } else {
        span = AceType::MakeRefPtr<UrlSpan>();
    }
    CHECK_NULL_VOID(span);
    urlSpan->urlContextSpan_ = span;
    args.SetReturnValue(Referenced::RawPtr(urlSpan));
}

void JSUrlSpan::Destructor(JSUrlSpan* urlSpan)
{
    if (urlSpan != nullptr) {
        urlSpan->DecRefCount();
    }
}

void JSUrlSpan::GetUrlContext(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(urlContextSpan_);
    auto ret = JSRef<JSVal>::Make(JSVal(ToJSValue(urlContextSpan_->GetUrlSpanAddress())));
    info.SetReturnValue(ret);
}

void JSUrlSpan::SetUrlContext(const JSCallbackInfo& info) {}

const RefPtr<UrlSpan>& JSUrlSpan::GetUrlSpan()
{
    return urlContextSpan_;
}

void JSUrlSpan::SetUrlSpan(const RefPtr<UrlSpan>& urlSpan)
{
    urlContextSpan_ = urlSpan;
}
} // namespace OHOS::Ace::Framework