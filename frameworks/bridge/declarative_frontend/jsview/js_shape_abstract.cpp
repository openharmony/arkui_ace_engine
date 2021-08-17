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

#include "frameworks/bridge/declarative_frontend/jsview/js_shape_abstract.h"

#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void JSShapeAbstract::SetStrokeDashArray(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsArray()) {
        LOGE("info is not array");
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("component is null");
        return;
    }

    JSRef<JSArray> array = JSRef<JSArray>::Cast(info[0]);
    int32_t length = array->Length();
    if (length <= 0) {
        LOGE("info is invalid");
        return;
    }
    std::vector<Dimension> dashArray;
    for (int32_t i = 0; i < length; i++) {
        JSRef<JSVal> value = array->GetValueAt(i);
        dashArray.emplace_back(ToDimension(value));
    }
    // if odd,add twice
    if ((length & 1)) {
        for (int32_t i = 0; i < length; i++) {
            JSRef<JSVal> value = array->GetValueAt(i);
            dashArray.emplace_back(ToDimension(value));
        }
    }
    component->SetStrokeDashArray(dashArray);
    info.SetReturnValue(info.This());
}

void JSShapeAbstract::SetStroke(const std::string& color)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (component) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetStroke(Color::FromString(color), option);
    }
}

void JSShapeAbstract::SetFill(const std::string& color)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("component is null");
        return;
    }
    AnimationOption option = stack->GetImplicitAnimationOption();
    if (color == "none") {
        component->SetFill(Color::TRANSPARENT, option);
    } else {
        component->SetFill(Color::FromString(color), option);
    }
}

void JSShapeAbstract::SetStrokeDashOffset(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    if (!info[0]->IsNumber() && !info[0]->IsString()) {
        LOGE("arg is not Number or String.");
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (component) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetStrokeDashOffset(ToDimension(info[0]), option);
    }
}

void JSShapeAbstract::SetStrokeLineCap(int lineCap)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("ShapeComponent is null");
        return;
    }
    if (static_cast<int>(LineCapStyle::SQUARE) == lineCap) {
        component->SetStrokeLineCap(LineCapStyle::SQUARE);
    } else if (static_cast<int>(LineCapStyle::ROUND) == lineCap) {
        component->SetStrokeLineCap(LineCapStyle::ROUND);
    } else {
        component->SetStrokeLineCap(LineCapStyle::BUTT);
    }
}

void JSShapeAbstract::SetStrokeLineJoin(int lineJoin)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("ShapeComponent is null");
        return;
    }
    if (static_cast<int>(LineJoinStyle::BEVEL) == lineJoin) {
        component->SetStrokeLineJoin(LineJoinStyle::BEVEL);
    } else if (static_cast<int>(LineJoinStyle::ROUND) == lineJoin) {
        component->SetStrokeLineJoin(LineJoinStyle::ROUND);
    } else {
        component->SetStrokeLineJoin(LineJoinStyle::MITER);
    }
}

void JSShapeAbstract::SetStrokeMiterLimit(const std::string& strokeMiterLimit)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("ShapeComponent is null");
        return;
    }
    double miterLimit = StringUtils::StringToDouble(strokeMiterLimit);
    if (GreatOrEqual(miterLimit, 1.0)) {
        component->SetStrokeMiterLimit(miterLimit);
    }
}

void JSShapeAbstract::SetStrokeOpacity(const std::string& strokeOpacity)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (component) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetStrokeOpacity(StringUtils::StringToDouble(strokeOpacity), option);
    }
}

void JSShapeAbstract::SetFillOpacity(const std::string& fillOpacity)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (component) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetFillOpacity(StringUtils::StringToDouble(fillOpacity), option);
    }
}

void JSShapeAbstract::SetStrokeWidth(const std::string& strokeWidth)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("ShapeComponent is null");
        return;
    }
    Dimension lineWidth = StringUtils::StringToDimension(strokeWidth, true);
    if (GreatOrEqual(lineWidth.Value(), 0.0)) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetStrokeWidth(lineWidth, option);
    }
}

void JSShapeAbstract::SetAntiAlias(bool antiAlias)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (component) {
        component->SetAntiAlias(antiAlias);
    }
}

void JSShapeAbstract::JsWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    if (!info[0]->IsNumber() && !info[0]->IsString()) {
        LOGE("arg is not Number or String.");
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("ShapeComponent is null");
        return;
    }

    Dimension value = ToDimension(info[0]);
    AnimationOption option = stack->GetImplicitAnimationOption();
    component->SetWidth(value, option);
}

void JSShapeAbstract::JsHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    if (!info[0]->IsNumber() && !info[0]->IsString()) {
        LOGE("arg is not Number or String.");
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("ShapeComponent is null");
        return;
    }

    Dimension value = ToDimension(info[0]);
    AnimationOption option = stack->GetImplicitAnimationOption();
    component->SetHeight(value, option);
}

void JSShapeAbstract::ObjectWidth(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() > 0 && (info[0]->IsNumber() || info[0]->IsString())) {
        auto value = ToDimension(info[0]);
        if (LessNotEqual(value.Value(), 0.0)) {
            LOGE("Value is less than zero");
            return;
        }

        if (basicShape_) {
            basicShape_->SetWidth(value);
        }
    }
}

void JSShapeAbstract::ObjectHeight(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() > 0 && (info[0]->IsNumber() || info[0]->IsString())) {
        auto value = ToDimension(info[0]);
        if (LessNotEqual(value.Value(), 0.0)) {
            LOGE("Value is less than zero");
            return;
        }

        if (basicShape_) {
            basicShape_->SetHeight(value);
        }
    }
}

void JSShapeAbstract::ObjectOffset(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> xVal = sizeObj->GetProperty("x");
        auto x = ToDimension(xVal);
        JSRef<JSVal> yVal = sizeObj->GetProperty("y");
        auto y = ToDimension(yVal);

        if (basicShape_) {
            basicShape_->SetOffset(DimensionOffset(x, y));
        }
    }
}

void JSShapeAbstract::ObjectFill(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsString() && !info[0]->IsNumber()) {
        LOGE("arg is not a string or number.");
        return;
    }

    if (basicShape_) {
        Color color;
        if (info[0]->IsString()) {
            color = Color::FromString(info[0]->ToString());
        } else if (info[0]->IsNumber()) {
            color = Color(ColorAlphaAdapt(info[0]->ToNumber<uint32_t>()));
        }

        basicShape_->SetColor(color);
    }
}

void JSShapeAbstract::JSBind()
{
    JSClass<JSShapeAbstract>::Declare("JSShapeAbstract");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSShapeAbstract>::StaticMethod("stroke", &JSShapeAbstract::SetStroke, opt);
    JSClass<JSShapeAbstract>::StaticMethod("fill", &JSShapeAbstract::SetFill, opt);
    JSClass<JSShapeAbstract>::StaticMethod("strokeDashOffset", &JSShapeAbstract::SetStrokeDashOffset, opt);
    JSClass<JSShapeAbstract>::StaticMethod("strokeDashArray", &JSShapeAbstract::SetStrokeDashArray);
    JSClass<JSShapeAbstract>::StaticMethod("strokeLineCap", &JSShapeAbstract::SetStrokeLineCap, opt);
    JSClass<JSShapeAbstract>::StaticMethod("strokeLineJoin", &JSShapeAbstract::SetStrokeLineJoin, opt);
    JSClass<JSShapeAbstract>::StaticMethod("strokeMiterLimit", &JSShapeAbstract::SetStrokeMiterLimit, opt);
    JSClass<JSShapeAbstract>::StaticMethod("strokeOpacity", &JSShapeAbstract::SetStrokeOpacity, opt);
    JSClass<JSShapeAbstract>::StaticMethod("fillOpacity", &JSShapeAbstract::SetFillOpacity, opt);
    JSClass<JSShapeAbstract>::StaticMethod("strokeWidth", &JSShapeAbstract::SetStrokeWidth, opt);
    JSClass<JSShapeAbstract>::StaticMethod("antiAlias", &JSShapeAbstract::SetAntiAlias, opt);
    JSClass<JSShapeAbstract>::StaticMethod("width", &JSShapeAbstract::JsWidth, opt);
    JSClass<JSShapeAbstract>::StaticMethod("height", &JSShapeAbstract::JsHeight, opt);
    JSClass<JSShapeAbstract>::Inherit<JSViewAbstract>();
}

void JSShapeAbstract::SetSize(const JSCallbackInfo& info)
{
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto stack = ViewStackProcessor::GetInstance();
        auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
        if (!component) {
            LOGE("ShapeComponent is null");
            return;
        }
        AnimationOption option = stack->GetImplicitAnimationOption();
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> width = obj->GetProperty("width");
        component->SetWidth(ToDimension(width), option);
        JSRef<JSVal> height = obj->GetProperty("height");
        component->SetHeight(ToDimension(height), option);
    }
}

} // namespace OHOS::Ace::Framework
