/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_shape.h"

#include "base/geometry/ng/image_mesh.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/models/shape_model_impl.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/shape/shape_abstract_model.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"

namespace OHOS::Ace {
namespace {
constexpr double DEFAULT_OPACITY = 1.0;
constexpr double STROKE_MITERLIMIT_DEFAULT = 4.0f;
} // namespace
std::unique_ptr<ShapeModel> ShapeModel::instance_;

ShapeModel* ShapeModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::ShapeModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::ShapeModelNG());
        } else {
            instance_.reset(new Framework::ShapeModelImpl());
        }
#endif
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSShape::Create(const JSCallbackInfo& info)
{
    ShapeModel::GetInstance()->Create();
    JSInteractableView::SetFocusable(true);
    InitBox(info);
}

void JSShape::InitBox(const JSCallbackInfo& info)
{
    RefPtr<PixelMap> pixMap = nullptr;
    if (info.Length() == 1 && info[0]->IsObject()) {
#if !defined(PREVIEW)
        pixMap = CreatePixelMapFromNapiValue(info[0]);
#endif
    }
    ShapeModel::GetInstance()->InitBox(pixMap);
}

void JSShape::SetViewPort(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> leftValue = obj->GetProperty("x");
        JSRef<JSVal> topValue = obj->GetProperty("y");
        JSRef<JSVal> widthValue = obj->GetProperty("width");
        JSRef<JSVal> heightValue = obj->GetProperty("height");
        ShapeViewBox viewBox;
        CalcDimension dimLeft;
        ParseJsDimensionVp(leftValue, dimLeft);
        CalcDimension dimTop;
        ParseJsDimensionVp(topValue, dimTop);
        CalcDimension dimWidth;
        ParseJsDimensionVp(widthValue, dimWidth);
        CalcDimension dimHeight;
        ParseJsDimensionVp(heightValue, dimHeight);
        ShapeModel::GetInstance()->SetViewPort(dimLeft, dimTop, dimWidth, dimHeight);
    }
    info.SetReturnValue(info.This());
}

void JSShape::JsWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    JsWidth(info[0]);
}

void JSShape::JsWidth(const JSRef<JSVal>& jsValue)
{
    JSViewAbstract::JsWidth(jsValue);
    ShapeModel::GetInstance()->SetWidth();
}

void JSShape::JsHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    JsHeight(info[0]);
}

void JSShape::JsHeight(const JSRef<JSVal>& jsValue)
{
    JSViewAbstract::JsHeight(jsValue);
    ShapeModel::GetInstance()->SetHeight();
}

void JSShape::JsSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (!info[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JsWidth(sizeObj->GetProperty("width"));
    JsHeight(sizeObj->GetProperty("height"));
}

void JSShape::SetStrokeDashArray(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsArray()) {
        return;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(info[0]);
    int32_t length = static_cast<int32_t>(array->Length());
    if (length <= 0) {
        return;
    }
    std::vector<Dimension> dashArray;
    for (int32_t i = 0; i < length; i++) {
        JSRef<JSVal> value = array->GetValueAt(i);
        CalcDimension dim;
        if (ParseJsDimensionVp(value, dim)) {
            dashArray.emplace_back(dim);
        }
    }
    if (length != static_cast<int32_t>(dashArray.size())) {
        return;
    }
    // if odd,add twice
    if ((static_cast<uint32_t>(length) & 1)) {
        for (int32_t i = 0; i < length; i++) {
            dashArray.emplace_back(dashArray[i]);
        }
    }
    ShapeModel::GetInstance()->SetStrokeDashArray(dashArray);
    info.SetReturnValue(info.This());
}

void JSShape::SetStroke(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color strokeColor = Color::TRANSPARENT;
    ParseJsColor(info[0], strokeColor);
    ShapeModel::GetInstance()->SetStroke(strokeColor);
}

void JSShape::SetFill(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (info[0]->IsString() && info[0]->ToString() == "none") {
        ShapeModel::GetInstance()->SetFill(Color::TRANSPARENT);
    } else {
        Color fillColor;
        if (ParseJsColor(info[0], fillColor)) {
            ShapeModel::GetInstance()->SetFill(fillColor);
        }
    }
}

void JSShape::SetStrokeDashOffset(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension offset;
    if (!ParseJsDimensionVp(info[0], offset)) {
        return;
    }
    ShapeModel::GetInstance()->SetStrokeDashOffset(offset);
}

void JSShape::SetStrokeLineCap(int lineCap)
{
    ShapeModel::GetInstance()->SetStrokeLineCap(lineCap);
}

void JSShape::SetStrokeLineJoin(int lineJoin)
{
    ShapeModel::GetInstance()->SetStrokeLineJoin(lineJoin);
}

void JSShape::SetStrokeMiterLimit(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    double miterLimit = STROKE_MITERLIMIT_DEFAULT;
    ParseJsDouble(info[0], miterLimit);
    ShapeModel::GetInstance()->SetStrokeMiterLimit(miterLimit);
}

void JSShape::SetStrokeOpacity(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    double strokeOpacity = DEFAULT_OPACITY;
    ParseJsDouble(info[0], strokeOpacity);
    ShapeModel::GetInstance()->SetStrokeOpacity(strokeOpacity);
}

void JSShape::SetFillOpacity(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    double fillOpacity = DEFAULT_OPACITY;
    ParseJsDouble(info[0], fillOpacity);
    ShapeModel::GetInstance()->SetFillOpacity(fillOpacity);
}

void JSShape::SetStrokeWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    // the default value is 1.0_vp
    CalcDimension lineWidth = 1.0_vp;
    if (info[0]->IsString()) {
        const std::string& value = info[0]->ToString();
        lineWidth = StringUtils::StringToDimensionWithUnit(value, DimensionUnit::VP, 1.0);
    } else {
        ParseJsDimensionVp(info[0], lineWidth);
    }
    if (lineWidth.IsNegative()) {
        lineWidth = 1.0_vp;
    }
    ShapeModel::GetInstance()->SetStrokeWidth(lineWidth);
}

void JSShape::SetAntiAlias(bool antiAlias)
{
    ShapeModel::GetInstance()->SetAntiAlias(antiAlias);
}

void JSShape::SetBitmapMesh(const JSCallbackInfo& info)
{
    if (info.Length() != 3) {
        return;
    }
    std::vector<double> mesh;
    JSRef<JSVal> meshValue = info[0];

    if (meshValue->IsObject()) {
        JSRef<JSObject> meshObj = JSRef<JSObject>::Cast(meshValue);
        JSRef<JSArray> array = meshObj->GetPropertyNames();
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> value = array->GetValueAt(i);
            if (value->IsString()) {
                std::string valueStr;
                if (ParseJsString(value, valueStr)) {
                    double vert;
                    if (ParseJsDouble(meshObj->GetProperty(valueStr.c_str()), vert)) {
                        mesh.push_back(vert);
                    }
                }
            }
        }
    }
    uint32_t column = 0;
    uint32_t row = 0;
    JSRef<JSVal> columnValue = info[1];
    JSRef<JSVal> rowValue = info[2];
    if (!ParseJsInteger(columnValue, column)) {
        return;
    }
    if (!ParseJsInteger(rowValue, row)) {
        return;
    }
    ShapeModel::GetInstance()->SetBitmapMesh(mesh, static_cast<int32_t>(column), static_cast<int32_t>(row));
}

void JSShape::SetForegroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color foregroundColor;
    ForegroundColorStrategy strategy;
    if (ParseJsColorStrategy(info[0], strategy)) {
        ShapeModel::GetInstance()->SetFill(Color::FOREGROUND);
        ViewAbstractModel::GetInstance()->SetForegroundColorStrategy(strategy);
        return;
    }
    if (!ParseJsColor(info[0], foregroundColor)) {
        return;
    }
    ShapeModel::GetInstance()->SetFill(foregroundColor);
    ViewAbstractModel::GetInstance()->SetForegroundColor(foregroundColor);
}

void JSShape::JSBind(BindingTarget globalObj)
{
    JSClass<JSShape>::Declare("Shape");
    JSClass<JSShape>::StaticMethod("create", &JSShape::Create);
    JSClass<JSShape>::StaticMethod("viewPort", &JSShape::SetViewPort);

    JSClass<JSShape>::StaticMethod("width", &JSShape::JsWidth);
    JSClass<JSShape>::StaticMethod("height", &JSShape::JsHeight);
    JSClass<JSShape>::StaticMethod("size", &JSShape::JsSize);

    JSClass<JSShape>::StaticMethod("stroke", &JSShape::SetStroke);
    JSClass<JSShape>::StaticMethod("fill", &JSShape::SetFill);
    JSClass<JSShape>::StaticMethod("strokeDashOffset", &JSShape::SetStrokeDashOffset);
    JSClass<JSShape>::StaticMethod("strokeDashArray", &JSShape::SetStrokeDashArray);
    JSClass<JSShape>::StaticMethod("strokeLineCap", &JSShape::SetStrokeLineCap);
    JSClass<JSShape>::StaticMethod("strokeLineJoin", &JSShape::SetStrokeLineJoin);
    JSClass<JSShape>::StaticMethod("strokeMiterLimit", &JSShape::SetStrokeMiterLimit);
    JSClass<JSShape>::StaticMethod("strokeOpacity", &JSShape::SetStrokeOpacity);
    JSClass<JSShape>::StaticMethod("fillOpacity", &JSShape::SetFillOpacity);
    JSClass<JSShape>::StaticMethod("strokeWidth", &JSShape::SetStrokeWidth);
    JSClass<JSShape>::StaticMethod("antiAlias", &JSShape::SetAntiAlias);
    JSClass<JSShape>::StaticMethod("mesh", &JSShape::SetBitmapMesh);
    JSClass<JSShape>::StaticMethod("foregroundColor", &JSShape::SetForegroundColor);

    JSClass<JSShape>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSShape>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSShape>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSShape>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSShape>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSShape>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSShape>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSShape>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSShape>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework
