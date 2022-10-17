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

#include "bridge/declarative_frontend/jsview/models/shape_abstract_model_impl.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/shape/shape_abstract_model.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace {

std::unique_ptr<ShapeAbstractModel> ShapeAbstractModel::instance_ = nullptr;

ShapeAbstractModel* ShapeAbstractModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::ShapeAbstractModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::ShapeAbstractModelNG());
        } else {
            instance_.reset(new Framework::ShapeAbstractModelImpl());
        }
#endif
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSShapeAbstract::SetStrokeDashArray(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsArray()) {
        LOGE("info is not array");
        return;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(info[0]);
    int32_t length = static_cast<int32_t>(array->Length());
    std::vector<Dimension> dashArray;
    for (int32_t i = 0; i < length; i++) {
        JSRef<JSVal> value = array->GetValueAt(i);
        Dimension dim;
        if (ParseJsDimensionVp(value, dim)) {
            dashArray.emplace_back(dim);
        }
    }
    if (length != static_cast<int32_t>(dashArray.size())) {
        LOGE("ParseJsDimensionVp failed");
        return;
    }
    // if odd,add twice
    if ((static_cast<uint32_t>(length) & 1)) {
        for (int32_t i = 0; i < length; i++) {
            dashArray.emplace_back(dashArray[i]);
        }
    }
    ShapeAbstractModel::GetInstance()->SetStrokeDashArray(dashArray);
}

void JSShapeAbstract::SetStroke(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color strokeColor;
    if (!ParseJsColor(info[0], strokeColor)) {
        return;
    }
    ShapeAbstractModel::GetInstance()->SetStroke(strokeColor);
}

void JSShapeAbstract::SetFill(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    if (info[0]->IsString() && info[0]->ToString() == "none") {
        ShapeAbstractModel::GetInstance()->SetFill(Color::TRANSPARENT);
    } else {
        Color fillColor;
        if (ParseJsColor(info[0], fillColor)) {
            ShapeAbstractModel::GetInstance()->SetFill(fillColor);
        }
    }
}

void JSShapeAbstract::SetStrokeDashOffset(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension offset;
    if (!ParseJsDimensionVp(info[0], offset)) {
        return;
    }
    ShapeAbstractModel::GetInstance()->SetStrokeDashOffset(offset);
}

void JSShapeAbstract::SetStrokeLineCap(int lineCap)
{
    ShapeAbstractModel::GetInstance()->SetStrokeLineCap(lineCap);
}

void JSShapeAbstract::SetStrokeLineJoin(int lineJoin)
{
    ShapeAbstractModel::GetInstance()->SetStrokeLineJoin(lineJoin);
}

void JSShapeAbstract::SetStrokeMiterLimit(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    double miterLimit;
    if (!ParseJsDouble(info[0], miterLimit)) {
        return;
    }
    if (GreatOrEqual(miterLimit, 1.0)) {
        ShapeAbstractModel::GetInstance()->SetStrokeMiterLimit(miterLimit);
    }
}

void JSShapeAbstract::SetStrokeOpacity(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    double strokeOpacity;
    if (!ParseJsDouble(info[0], strokeOpacity)) {
        return;
    }
    ShapeAbstractModel::GetInstance()->SetStrokeOpacity(strokeOpacity);
}

void JSShapeAbstract::SetFillOpacity(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    double fillOpacity;
    if (!ParseJsDouble(info[0], fillOpacity)) {
        return;
    }
    ShapeAbstractModel::GetInstance()->SetFillOpacity(fillOpacity);
}

void JSShapeAbstract::SetStrokeWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension lineWidth;
    if (!ParseJsDimensionVp(info[0], lineWidth)) {
        return;
    }
    if (GreatOrEqual(lineWidth.Value(), 0.0)) {
        ShapeAbstractModel::GetInstance()->SetStrokeWidth(lineWidth);
    }
}

void JSShapeAbstract::SetAntiAlias(bool antiAlias)
{
    ShapeAbstractModel::GetInstance()->SetAntiAlias(antiAlias);
}

void JSShapeAbstract::JsWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    SetWidth(info[0]);
}

void JSShapeAbstract::SetWidth(const JSRef<JSVal>& jsValue)
{
    Dimension dimWidth;
    if (!ParseJsDimensionVp(jsValue, dimWidth)) {
        return;
    }
    if (LessNotEqual(dimWidth.Value(), 0.0)) {
        dimWidth.SetValue(0.0);
    }
    ShapeAbstractModel::GetInstance()->SetWidth(dimWidth);
}

void JSShapeAbstract::JsHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    SetHeight(info[0]);
}

void JSShapeAbstract::SetHeight(const JSRef<JSVal>& jsValue)
{
    Dimension dimHeight;
    if (!ParseJsDimensionVp(jsValue, dimHeight)) {
        return;
    }
    if (LessNotEqual(dimHeight.Value(), 0.0)) {
        dimHeight.SetValue(0.0);
    }
    ShapeAbstractModel::GetInstance()->SetHeight(dimHeight);
}

void JSShapeAbstract::JsSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("arg is not Object or String.");
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    SetWidth(sizeObj->GetProperty("width"));
    SetHeight(sizeObj->GetProperty("height"));
}

void JSShapeAbstract::ObjectWidth(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    ObjectWidth(info[0]);
}

void JSShapeAbstract::ObjectWidth(const JSRef<JSVal>& jsValue)
{
    Dimension value;
    if (!ParseJsDimensionVp(jsValue, value)) {
        return;
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        LOGE("Value is less than zero");
        return;
    }
    if (basicShape_) {
        basicShape_->SetWidth(value);
    }
}

void JSShapeAbstract::ObjectHeight(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    ObjectHeight(info[0]);
}

void JSShapeAbstract::ObjectHeight(const JSRef<JSVal>& jsValue)
{
    Dimension value;
    if (!ParseJsDimensionVp(jsValue, value)) {
        return;
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        LOGE("Value is less than zero");
        return;
    }
    if (basicShape_) {
        basicShape_->SetHeight(value);
    }
}

void JSShapeAbstract::ObjectSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("arg is not Object or String.");
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    ObjectWidth(sizeObj->GetProperty("width"));
    ObjectHeight(sizeObj->GetProperty("height"));
}

void JSShapeAbstract::ObjectOffset(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> xVal = sizeObj->GetProperty("x");
        JSRef<JSVal> yVal = sizeObj->GetProperty("y");
        Dimension x;
        Dimension y;
        if (basicShape_ && ParseJsDimensionVp(xVal, x) && ParseJsDimensionVp(yVal, y)) {
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

    Color color;
    if (ParseJsColor(info[0], color) && basicShape_) {
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
    JSClass<JSShapeAbstract>::StaticMethod("size", &JSShapeAbstract::JsSize, opt);
    JSClass<JSShapeAbstract>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSShapeAbstract>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSShapeAbstract>::Inherit<JSViewAbstract>();
}

void JSShapeAbstract::SetSize(const JSCallbackInfo& info)
{
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> width = obj->GetProperty("width");
        JSRef<JSVal> height = obj->GetProperty("height");
        Dimension dimWidth;
        if (ParseJsDimensionVp(width, dimWidth)) {
            ShapeAbstractModel::GetInstance()->SetWidth(dimWidth);
        }
        Dimension dimHeight;
        if (ParseJsDimensionVp(height, dimHeight)) {
            ShapeAbstractModel::GetInstance()->SetHeight(dimHeight);
        }
    }
}

} // namespace OHOS::Ace::Framework
