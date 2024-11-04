/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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
ShapeModel* ShapeModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::ShapeModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::ShapeModelNG instance;
        return &instance;
    } else {
        static Framework::ShapeModelImpl instance;
        return &instance;
    }
#endif
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
#if !defined(PREVIEW) && defined(PIXEL_MAP_SUPPORTED)
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
    std::vector<Dimension> dashArray;
    if (info.Length() < 1 || !info[0]->IsArray()) {
        ShapeModel::GetInstance()->SetStrokeDashArray(dashArray);
        return;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(info[0]);
    int32_t length = static_cast<int32_t>(array->Length());
    if (length <= 0) {
        ShapeModel::GetInstance()->SetStrokeDashArray(dashArray);
        return;
    }
    for (int32_t i = 0; i < length; i++) {
        JSRef<JSVal> value = array->GetValueAt(i);
        CalcDimension dim;
        bool paramIsValid = false;
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            paramIsValid = ParseJsDimensionVp(value, dim);
        } else {
            paramIsValid = ParseJsDimensionVpNG(value, dim);
        }
        if (paramIsValid) {
            dashArray.emplace_back(dim);
        } else {
            dashArray.clear();
            break;
        }
    }
    // if odd,add twice
    if (static_cast<uint32_t>(length) == dashArray.size() && (static_cast<uint32_t>(length) & 1)) {
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
        } else {
            ShapeModel::GetInstance()->SetFill(Color::BLACK);
        }
    }
}

void JSShape::SetStrokeDashOffset(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension offset(0.0f);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!ParseJsDimensionVp(info[0], offset)) {
            return;
        }
    } else {
        if (!ParseJsDimensionVpNG(info[0], offset)) {
            // set to default value(0.0f)
            offset.SetValue(0.0f);
        }
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
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            lineWidth = StringUtils::StringToDimensionWithUnit(value, DimensionUnit::VP, 1.0);
        } else {
            if (!StringUtils::StringToDimensionWithUnitNG(value, lineWidth, DimensionUnit::VP, 1.0)) {
                // unit is invalid, use default value(1.0vp) instead.
                lineWidth = 1.0_vp;
            }
        }
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
    std::vector<float> mesh;
    uint32_t column = 0;
    uint32_t row = 0;
    JSRef<JSVal> columnValue = info[1];
    JSRef<JSVal> rowValue = info[2];
    if (!ParseJsInteger(columnValue, column)) {
        ShapeModel::GetInstance()->SetBitmapMesh(mesh, 0, 0);
        return;
    }
    if (!ParseJsInteger(rowValue, row)) {
        ShapeModel::GetInstance()->SetBitmapMesh(mesh, 0, 0);
        return;
    }
    if (info[0]->IsArray()) {
        auto meshValue = JSRef<JSArray>::Cast(info[0]);
        auto meshSize = meshValue->Length();
        auto tempMeshSize = static_cast<uint64_t>(column + 1) * (row + 1) * 2;
        if (tempMeshSize != meshSize) {
            ShapeModel::GetInstance()->SetBitmapMesh(mesh, 0, 0);
            return;
        }
        for (size_t i = 0; i < meshSize; i++) {
            JSRef<JSVal> value = meshValue->GetValueAt(i);
            // only support number
            if (value->IsNumber()) {
                auto vert = value->ToNumber<float>();
                mesh.emplace_back(vert);
            } else {
                ShapeModel::GetInstance()->SetBitmapMesh(std::vector<float>(), 0, 0);
                return;
            }
        }
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
    JSClass<JSShape>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSShape>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSShape>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSShape>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSShape>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSShape>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework
