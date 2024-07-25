/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/canvas/js_matrix2d.h"

#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/render/adapter/matrix2d.h"

namespace OHOS::Ace::Framework {
constexpr int JS_MATRIX2D_PARAMETER_COUNTS_0 = 0;
constexpr int JS_MATRIX2D_PARAMETER_COUNTS_1 = 1;
constexpr int JS_MATRIX2D_PARAMETER_COUNTS_2 = 2;
constexpr int JS_MATRIX2D_PARAMETER_COUNTS_3 = 3;

void JSMatrix2d::Constructor(const JSCallbackInfo& info)
{
    auto matrix2d = Referenced::MakeRefPtr<JSMatrix2d>();
    matrix2d->IncRefCount();
    info.SetReturnValue(Referenced::RawPtr(matrix2d));
    int32_t unit = 0;
    if (info.GetInt32Arg(0, unit) && (static_cast<CanvasUnit>(unit) == CanvasUnit::PX)) {
        matrix2d->SetUnit(CanvasUnit::PX);
    }
}

void JSMatrix2d::Destructor(JSMatrix2d* matrix2d)
{
    if (matrix2d != nullptr) {
        matrix2d->DecRefCount();
    }
}

TransformParam JSMatrix2d::GetTransformInfo(const JSRef<JSObject>& obj)
{
    auto scaleXVal = obj->GetProperty("scaleX");
    auto rotateXVal = obj->GetProperty("rotateX");
    auto rotateYVal = obj->GetProperty("rotateY");
    auto scaleYVal = obj->GetProperty("scaleY");
    auto translateXVal = obj->GetProperty("translateX");
    auto translateYVal = obj->GetProperty("translateY");

    TransformParam param;
    JSViewAbstract::ParseJsDouble(scaleXVal, param.scaleX);
    JSViewAbstract::ParseJsDouble(rotateXVal, param.skewX);
    JSViewAbstract::ParseJsDouble(rotateYVal, param.skewY);
    JSViewAbstract::ParseJsDouble(scaleYVal, param.scaleY);
    JSViewAbstract::ParseJsDouble(translateXVal, param.translateX);
    JSViewAbstract::ParseJsDouble(translateYVal, param.translateY);
    return param;
}

void JSMatrix2d::JSBind(BindingTarget globalObj)
{
    JSClass<JSMatrix2d>::Declare("Matrix2D");
    JSClass<JSMatrix2d>::CustomProperty("scaleX", &JSMatrix2d::JsGetScaleX, &JSMatrix2d::JsSetScaleX);
    JSClass<JSMatrix2d>::CustomProperty("rotateY", &JSMatrix2d::JsGetRotateY, &JSMatrix2d::JsSetRotateY);
    JSClass<JSMatrix2d>::CustomProperty("rotateX", &JSMatrix2d::JsGetRotateX, &JSMatrix2d::JsSetRotateX);
    JSClass<JSMatrix2d>::CustomProperty("scaleY", &JSMatrix2d::JsGetScaleY, &JSMatrix2d::JsSetScaleY);
    JSClass<JSMatrix2d>::CustomProperty("translateX", &JSMatrix2d::JsGetTranslateX, &JSMatrix2d::JsSetTranslateX);
    JSClass<JSMatrix2d>::CustomProperty("translateY", &JSMatrix2d::JsGetTranslateY, &JSMatrix2d::JsSetTranslateY);
    JSClass<JSMatrix2d>::CustomMethod("identity", &JSMatrix2d::JsIdentity);
    JSClass<JSMatrix2d>::CustomMethod("invert", &JSMatrix2d::JsInvert);
    JSClass<JSMatrix2d>::CustomMethod("rotate", &JSMatrix2d::JsRotate);
    JSClass<JSMatrix2d>::CustomMethod("translate", &JSMatrix2d::JsTranslate);
    JSClass<JSMatrix2d>::CustomMethod("scale", &JSMatrix2d::JsScale);
    JSClass<JSMatrix2d>::CustomMethod("multiply", &JSMatrix2d::JSMultiply);

    JSClass<JSMatrix2d>::Bind(globalObj, JSMatrix2d::Constructor, JSMatrix2d::Destructor);
}

void JSMatrix2d::JsSetScaleX(const JSCallbackInfo& info)
{
    if (info.Length() != JS_MATRIX2D_PARAMETER_COUNTS_1) {
        return;
    }
    if (info[JS_MATRIX2D_PARAMETER_COUNTS_0]->IsNumber()) {
        double scaleX = 0;
        JSViewAbstract::ParseJsDouble(info[JS_MATRIX2D_PARAMETER_COUNTS_0], scaleX);
        transform_.scaleX = scaleX;
    }
}

void JSMatrix2d::JsSetRotateY(const JSCallbackInfo& info)
{
    if (info.Length() != JS_MATRIX2D_PARAMETER_COUNTS_1) {
        return;
    }
    if (info[JS_MATRIX2D_PARAMETER_COUNTS_0]->IsNumber()) {
        double rotateY = 0;
        JSViewAbstract::ParseJsDouble(info[JS_MATRIX2D_PARAMETER_COUNTS_0], rotateY);
        transform_.skewY = rotateY;
    }
}

void JSMatrix2d::JsSetRotateX(const JSCallbackInfo& info)
{
    if (info.Length() != JS_MATRIX2D_PARAMETER_COUNTS_1) {
        return;
    }
    if (info[JS_MATRIX2D_PARAMETER_COUNTS_0]->IsNumber()) {
        double rotateX = 0;
        JSViewAbstract::ParseJsDouble(info[JS_MATRIX2D_PARAMETER_COUNTS_0], rotateX);
        transform_.skewX = rotateX;
    }
}

void JSMatrix2d::JsSetScaleY(const JSCallbackInfo& info)
{
    if (info.Length() != JS_MATRIX2D_PARAMETER_COUNTS_1) {
        return;
    }
    if (info[JS_MATRIX2D_PARAMETER_COUNTS_0]->IsNumber()) {
        double scaleY = 0;
        JSViewAbstract::ParseJsDouble(info[JS_MATRIX2D_PARAMETER_COUNTS_0], scaleY);
        transform_.scaleY = scaleY;
    }
}

void JSMatrix2d::JsSetTranslateX(const JSCallbackInfo& info)
{
    if (info.Length() != JS_MATRIX2D_PARAMETER_COUNTS_1) {
        return;
    }
    if (info[JS_MATRIX2D_PARAMETER_COUNTS_0]->IsNumber()) {
        double translateX = 0;
        JSViewAbstract::ParseJsDouble(info[JS_MATRIX2D_PARAMETER_COUNTS_0], translateX);
        double density = GetDensity();
        translateX *= density;
        transform_.translateX = translateX;
    }
}

void JSMatrix2d::JsSetTranslateY(const JSCallbackInfo& info)
{
    if (info.Length() != JS_MATRIX2D_PARAMETER_COUNTS_1) {
        return;
    }
    if (info[JS_MATRIX2D_PARAMETER_COUNTS_0]->IsNumber()) {
        double translateY = 0;
        JSViewAbstract::ParseJsDouble(info[JS_MATRIX2D_PARAMETER_COUNTS_0], translateY);
        double density = GetDensity();
        translateY *= density;
        transform_.translateY = translateY;
    }
}

void JSMatrix2d::JsGetScaleX(const JSCallbackInfo& info)
{
    auto returnValue = JSVal(ToJSValue(transform_.scaleX));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSMatrix2d::JsGetRotateY(const JSCallbackInfo& info)
{
    auto returnValue = JSVal(ToJSValue(transform_.skewY));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSMatrix2d::JsGetRotateX(const JSCallbackInfo& info)
{
    auto returnValue = JSVal(ToJSValue(transform_.skewX));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSMatrix2d::JsGetScaleY(const JSCallbackInfo& info)
{
    auto returnValue = JSVal(ToJSValue(transform_.scaleY));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSMatrix2d::JsGetTranslateX(const JSCallbackInfo& info)
{
    double translateX = transform_.translateX;
    double density = GetDensity();
    translateX /= density;
    auto returnValue = JSVal(ToJSValue(translateX));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSMatrix2d::JsGetTranslateY(const JSCallbackInfo& info)
{
    double translateY = transform_.translateY;
    double density = GetDensity();
    translateY /= density;
    auto returnValue = JSVal(ToJSValue(translateY));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSMatrix2d::JsIdentity(const JSCallbackInfo& info)
{
    if (info.Length() > JS_MATRIX2D_PARAMETER_COUNTS_0) {
        return;
    }
    NG::Matrix2D::Identity(transform_);
    info.SetReturnValue(info.This());
}

void JSMatrix2d::JsInvert(const JSCallbackInfo& info)
{
    if (info.Length() > JS_MATRIX2D_PARAMETER_COUNTS_0) {
        return;
    }
    bool retValue = NG::Matrix2D::Invert(transform_);
    if (!retValue) {
        transform_.scaleX = NAN;
        transform_.scaleY = NAN;
        transform_.skewX = NAN;
        transform_.skewY = NAN;
        transform_.translateX = NAN;
        transform_.translateY = NAN;
    }
    info.SetReturnValue(info.This());
}

void JSMatrix2d::JsRotate(const JSCallbackInfo& info)
{
    if (info.Length() < JS_MATRIX2D_PARAMETER_COUNTS_1 || info.Length() > JS_MATRIX2D_PARAMETER_COUNTS_3) {
        return;
    }
    double degree = 0;
    double rx = 0;
    double ry = 0;
    if (info.Length() > JS_MATRIX2D_PARAMETER_COUNTS_0 && info[JS_MATRIX2D_PARAMETER_COUNTS_0]->IsNumber()) {
        JSViewAbstract::ParseJsDouble(info[JS_MATRIX2D_PARAMETER_COUNTS_0], degree);
    }
    if (info.Length() > JS_MATRIX2D_PARAMETER_COUNTS_1 && info[JS_MATRIX2D_PARAMETER_COUNTS_1]->IsNumber()) {
        JSViewAbstract::ParseJsDouble(info[JS_MATRIX2D_PARAMETER_COUNTS_1], rx);
    }
    if (info.Length() > JS_MATRIX2D_PARAMETER_COUNTS_2 && info[JS_MATRIX2D_PARAMETER_COUNTS_2]->IsNumber()) {
        JSViewAbstract::ParseJsDouble(info[JS_MATRIX2D_PARAMETER_COUNTS_2], ry);
    }
    double density = GetDensity();
    rx *= density;
    ry *= density;
    NG::Matrix2D::Rotate(transform_, degree, rx, ry);
    info.SetReturnValue(info.This());
}

void JSMatrix2d::JsTranslate(const JSCallbackInfo& info)
{
    if (info.Length() > JS_MATRIX2D_PARAMETER_COUNTS_2) {
        return;
    }
    double tx = 0;
    double ty = 0;
    if (info.Length() > JS_MATRIX2D_PARAMETER_COUNTS_0 && info[JS_MATRIX2D_PARAMETER_COUNTS_0]->IsNumber()) {
        JSViewAbstract::ParseJsDouble(info[JS_MATRIX2D_PARAMETER_COUNTS_0], tx);
    }
    if (info.Length() > JS_MATRIX2D_PARAMETER_COUNTS_1 && info[JS_MATRIX2D_PARAMETER_COUNTS_1]->IsNumber()) {
        JSViewAbstract::ParseJsDouble(info[JS_MATRIX2D_PARAMETER_COUNTS_1], ty);
    }
    double density = GetDensity();
    tx *= density;
    ty *= density;
    NG::Matrix2D::Translate(transform_, tx, ty);
    info.SetReturnValue(info.This());
}

void JSMatrix2d::JsScale(const JSCallbackInfo& info)
{
    if (info.Length() > JS_MATRIX2D_PARAMETER_COUNTS_2) {
        return;
    }
    double sx = 1.0f;
    double sy = 1.0f;
    if (info.Length() > JS_MATRIX2D_PARAMETER_COUNTS_0 && info[JS_MATRIX2D_PARAMETER_COUNTS_0]->IsNumber()) {
        JSViewAbstract::ParseJsDouble(info[JS_MATRIX2D_PARAMETER_COUNTS_0], sx);
    }
    if (info.Length() > JS_MATRIX2D_PARAMETER_COUNTS_1 && info[JS_MATRIX2D_PARAMETER_COUNTS_1]->IsNumber()) {
        JSViewAbstract::ParseJsDouble(info[JS_MATRIX2D_PARAMETER_COUNTS_1], sy);
    }
    NG::Matrix2D::Scale(transform_, sx, sy);
    info.SetReturnValue(info.This());
}

std::string JSMatrix2d::ToString() const
{
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("scaleX", transform_.scaleX);
    jsonValue->Put("scaleY", transform_.scaleY);
    jsonValue->Put("skewX", transform_.skewX);
    jsonValue->Put("skewY", transform_.skewY);
    jsonValue->Put("translateX", transform_.translateX);
    jsonValue->Put("translateY", transform_.translateY);
    return jsonValue->ToString();
}
} // namespace OHOS::Ace::Framework
