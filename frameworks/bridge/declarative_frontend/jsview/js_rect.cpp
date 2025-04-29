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

#include "frameworks/bridge/declarative_frontend/jsview/js_rect.h"

#include "base/log/ace_trace.h"
#include "bridge/declarative_frontend/jsview/models/rect_model_impl.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/shape/rect_model.h"
#include "core/components_ng/pattern/shape/rect_model_ng.h"

namespace OHOS::Ace {
RectModel* RectModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::RectModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::RectModelNG instance;
        return &instance;
    } else {
        static Framework::RectModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
constexpr uint32_t HAS_RADIUS_WIDTH = 1;
constexpr uint32_t HAS_RADIUS_HEIGHT = 1 << 1;
constexpr uint32_t HAS_RADIUS = 1 << 2;
} // namespace

void JSRect::Create(const JSCallbackInfo& info)
{
    RectModel::GetInstance()->Create();
    JSShapeAbstract::SetSize(info);
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        auto propertyNames = obj->GetPropertyNames();
        if (!propertyNames->IsArray()) {
            return;
        }
        auto propertyFlag = 0U;
        for (size_t i = 0; i < propertyNames->Length(); i++) {
            JSRef<JSVal> value = propertyNames->GetValueAt(i);
            if (!value->IsString()) {
                continue;
            }
            auto propertyName = value->ToString();
            if (propertyName == "radiusWidth") {
                propertyFlag = propertyFlag | HAS_RADIUS_WIDTH;
            } else if (propertyName == "radiusHeight") {
                propertyFlag = propertyFlag | HAS_RADIUS_HEIGHT;
            } else if (propertyName == "radius") {
                propertyFlag = propertyFlag | HAS_RADIUS;
            }
        }
        if ((propertyFlag & HAS_RADIUS_WIDTH) == HAS_RADIUS_WIDTH) {
            JSRef<JSVal> radiusWidth = obj->GetProperty("radiusWidth");
            SetRadiusWidth(radiusWidth);
        }
        if ((propertyFlag & HAS_RADIUS_HEIGHT) == HAS_RADIUS_HEIGHT) {
            JSRef<JSVal> radiusHeight = obj->GetProperty("radiusHeight");
            SetRadiusHeight(radiusHeight);
        }
        if ((propertyFlag & HAS_RADIUS) == HAS_RADIUS) {
            JSRef<JSVal> radius = obj->GetProperty("radius");
            if (radius->IsNumber() || radius->IsString()) {
                SetRadiusWithJsVal(nullptr, radius);
            } else if (radius->IsArray()) {
                SetRadiusWithArrayValue(nullptr, radius);
            }
        }
        info.SetReturnValue(info.This());
    }
}

void JSRect::JsRadiusWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    SetRadiusWidth(info[0]);
}

void JSRect::JsRadiusHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    SetRadiusHeight(info[0]);
}

void JSRect::SetRadiusWidth(const JSRef<JSVal>& jsVal)
{
    CalcDimension value(0.0f);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        ParseJsDimensionVp(jsVal, value);
    } else {
        if (!ParseJsDimensionVpNG(jsVal, value)) {
            value.SetValue(0.0f);
        }
    }
    RectModel::GetInstance()->SetRadiusWidth(value);
}

void JSRect::SetRadiusHeight(const JSRef<JSVal>& jsVal)
{
    CalcDimension value(0.0f);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        ParseJsDimensionVp(jsVal, value);
    } else {
        if (!ParseJsDimensionVpNG(jsVal, value)) {
            value.SetValue(0.0f);
        }
    }
    RectModel::GetInstance()->SetRadiusHeight(value);
}

void JSRect::SetRadius(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension value(0.0f);
    RectModel::GetInstance()->SetRadiusWidth(value);
    RectModel::GetInstance()->SetRadiusHeight(value);
    if (info[0]->IsArray()) {
        SetRadiusWithArrayValue(nullptr, info[0]);
        info.SetReturnValue(info.This());
        return;
    }
    if (info[0]->IsNumber() || info[0]->IsString() || info[0]->IsObject()) {
        SetRadiusWithJsVal(nullptr, info[0]);
        info.SetReturnValue(info.This());
    }
}

void JSRect::SetRadiusWithJsVal(const RefPtr<ShapeRect>& shapeRect, const JSRef<JSVal>& jsVal)
{
    CalcDimension value(0.0f);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        ParseJsDimensionVp(jsVal, value);
    } else {
        if (!ParseJsDimensionVpNG(jsVal, value)) {
            value.SetValue(0.0f);
        }
    }
    if (shapeRect) {
        AnimationOption option = ViewStackModel::GetInstance()->GetImplicitAnimationOption();
        shapeRect->SetRadiusWidth(value, option);
        shapeRect->SetRadiusHeight(value, option);
        return;
    }
    RectModel::GetInstance()->SetRadiusWidth(value);
    RectModel::GetInstance()->SetRadiusHeight(value);
}

void JSRect::SetRadiusWithArrayValue(const RefPtr<ShapeRect>& shapeRect, const JSRef<JSVal>& jsVal)
{
    if (!jsVal->IsArray()) {
        return;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(jsVal);
    auto length = static_cast<int32_t>(array->Length());
    if (length <= 0) {
        return;
    }
    length = std::min(length, 4);
    for (int32_t i = 0; i < length; i++) {
        JSRef<JSVal> radiusItem = array->GetValueAt(i);
        if (!radiusItem->IsArray()) {
            break;
        }
        JSRef<JSArray> radiusArray = JSRef<JSArray>::Cast(radiusItem);
        if (radiusArray->Length() != 2) {
            break;
        }
        JSRef<JSVal> radiusX = radiusArray->GetValueAt(0);
        JSRef<JSVal> radiusY = radiusArray->GetValueAt(1);
        CalcDimension radiusXValue(0.0f);
        CalcDimension radiusYValue(0.0f);
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            if (ParseJsDimensionVp(radiusX, radiusXValue)) {
                ParseJsDimensionVp(radiusY, radiusYValue);
            }
        } else {
            if (!ParseJsDimensionVpNG(radiusX, radiusXValue)) {
                radiusXValue.SetValue(0.0f);
            }
            if (!ParseJsDimensionVpNG(radiusY, radiusYValue)) {
                radiusYValue.SetValue(0.0f);
            }
        }
        SetRadiusValue(shapeRect, radiusXValue, radiusYValue, i);
    }
}

void JSRect::SetRadiusValue(
    const RefPtr<ShapeRect>& shapeRect, const CalcDimension& radiusX, const CalcDimension& radiusY, int32_t index)
{
    if (shapeRect) {
        RectModel::GetInstance()->SetShapeRectRadius(shapeRect, radiusX, radiusY, index);
    } else {
        RectModel::GetInstance()->SetRadiusValue(radiusX, radiusY, index);
    }
}

void JSRect::ObjectRadiusWidth(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() < 1) {
        return;
    }
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        return;
    }
    auto rect = AceType::DynamicCast<ShapeRect>(basicShape_);
    if (rect) {
        rect->SetRadiusWidth(value);
    }
}

void JSRect::ObjectRadiusHeight(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() < 1) {
        return;
    }
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        return;
    }
    auto rect = AceType::DynamicCast<ShapeRect>(basicShape_);
    if (rect) {
        rect->SetRadiusHeight(value);
    }
}

void JSRect::ObjectRadius(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() < 1) {
        return;
    }
    auto rect = AceType::DynamicCast<ShapeRect>(basicShape_);
    if (!rect) {
        return;
    }
    if (info[0]->IsNumber() || info[0]->IsString()) {
        SetRadiusWithJsVal(rect, info[0]);
    }
    if (info[0]->IsArray()) {
        SetRadiusWithArrayValue(rect, info[0]);
    }
}

void JSRect::ParseRectObjBelowApi12(const RefPtr<ShapeRect>& rect, const JSRef<JSObject>& obj)
{
    CalcDimension width;
    CalcDimension height;
    CalcDimension radiusWidth;
    CalcDimension radiusHeight;
    if (ParseJsDimensionVp(obj->GetProperty("width"), width) && width.IsValid()) {
        rect->SetWidth(width);
    }
    if (ParseJsDimensionVp(obj->GetProperty("height"), height) && height.IsValid()) {
        rect->SetHeight(height);
    }
    if (ParseJsDimensionVp(obj->GetProperty("radiusWidth"), radiusWidth) && radiusWidth.IsValid()) {
        rect->SetRadiusWidth(radiusWidth);
    }
    if (ParseJsDimensionVp(obj->GetProperty("radiusHeight"), radiusHeight) && radiusHeight.IsValid()) {
        rect->SetRadiusHeight(radiusHeight);
    }
}

void JSRect::ParseRectObjAboveApi12(const RefPtr<ShapeRect>& rect, const JSRef<JSObject>& obj)
{
    CalcDimension width;
    CalcDimension height;
    CalcDimension radiusWidth;
    CalcDimension radiusHeight;
    if (ParseJsDimensionVpNG(obj->GetProperty("width"), width) && width.IsValid()) {
        rect->SetWidth(width);
    }
    if (ParseJsDimensionVpNG(obj->GetProperty("height"), height) && height.IsValid()) {
        rect->SetHeight(height);
    }
    if (ParseJsDimensionVpNG(obj->GetProperty("radiusWidth"), radiusWidth) && radiusWidth.IsValid()) {
        rect->SetRadiusWidth(radiusWidth);
    }
    if (ParseJsDimensionVpNG(obj->GetProperty("radiusHeight"), radiusHeight) && radiusHeight.IsValid()) {
        rect->SetRadiusHeight(radiusHeight);
    }
}

void JSRect::ConstructorCallback(const JSCallbackInfo& info)
{
    auto jsRect = AceType::MakeRefPtr<JSRect>();
    auto rect = AceType::MakeRefPtr<ShapeRect>();
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            ParseRectObjBelowApi12(rect, obj);
        } else {
            ParseRectObjAboveApi12(rect, obj);
        }
        JSRef<JSVal> radius = obj->GetProperty("radius");
        if (radius->IsNumber() || radius->IsString()) {
            SetRadiusWithJsVal(rect, radius);
        } else if (radius->IsArray()) {
            SetRadiusWithArrayValue(rect, radius);
        }
        info.SetReturnValue(info.This());
    }
    jsRect->SetBasicShape(rect);
    jsRect->IncRefCount();
    info.SetReturnValue(AceType::RawPtr(jsRect));
}

void JSRect::DestructorCallback(JSRect* jsRect)
{
    if (jsRect != nullptr) {
        jsRect->DecRefCount();
    }
}

void JSRect::JSBind(BindingTarget globalObj)
{
    JSClass<JSRect>::Declare("Rect");
    JSClass<JSRect>::StaticMethod("create", &JSRect::Create);
    JSClass<JSRect>::StaticMethod("radiusWidth", &JSRect::JsRadiusWidth);
    JSClass<JSRect>::StaticMethod("radiusHeight", &JSRect::JsRadiusHeight);
    JSClass<JSRect>::StaticMethod("radius", &JSRect::SetRadius);

    JSClass<JSRect>::CustomMethod("width", &JSShapeAbstract::ObjectWidth);
    JSClass<JSRect>::CustomMethod("height", &JSShapeAbstract::ObjectHeight);
    JSClass<JSRect>::CustomMethod("size", &JSShapeAbstract::ObjectSize);
    JSClass<JSRect>::CustomMethod("offset", &JSShapeAbstract::ObjectOffset);
    JSClass<JSRect>::CustomMethod("radiusWidth", &JSRect::ObjectRadiusWidth);
    JSClass<JSRect>::CustomMethod("radiusHeight", &JSRect::ObjectRadiusHeight);
    JSClass<JSRect>::CustomMethod("radius", &JSRect::ObjectRadius);
    JSClass<JSRect>::CustomMethod("fill", &JSShapeAbstract::ObjectFill);
    JSClass<JSRect>::CustomMethod("position", &JSShapeAbstract::ObjectPosition);

    JSClass<JSRect>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSRect>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSRect>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSRect>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSRect>::StaticMethod("onClick", &JSInteractableView::JsOnClick);

    JSClass<JSRect>::InheritAndBind<JSShapeAbstract>(
        globalObj, JSRect::ConstructorCallback, JSRect::DestructorCallback);
}

} // namespace OHOS::Ace::Framework
