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

#include "frameworks/bridge/declarative_frontend/jsview/js_rect_shape.h"
#include "core/components_ng/base/view_stack_model.h"

namespace OHOS::Ace::Framework {
namespace {
const int32_t LENGTH_RADIUS_ARRAY = 2;
const int32_t LENGTH_ARRAY = 4;
}
void JSRectShape::ObjectRadiusWidth(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() < 1) {
        return;
    }

    CalcDimension radiusWidth;
    if (!ParseJsDimensionVp(info[0], radiusWidth)) {
        return;
    }
    if (LessNotEqual(radiusWidth.Value(), 0.0)) {
        return;
    }

    auto rect = AceType::DynamicCast<ShapeRect>(basicShape_);
    if (rect) {
        rect->SetRadiusWidth(radiusWidth);
    }
}

void JSRectShape::ObjectRadiusHeight(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() < 1) {
        return;
    }

    CalcDimension radiusHeight;
    if (!ParseJsDimensionVp(info[0], radiusHeight)) {
        return;
    }
    if (LessNotEqual(radiusHeight.Value(), 0.0)) {
        return;
    }

    auto rect = AceType::DynamicCast<ShapeRect>(basicShape_);
    if (rect) {
        rect->SetRadiusHeight(radiusHeight);
    }
}

void JSRectShape::ObjectRadius(const JSCallbackInfo& info)
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

void JSRectShape::SetRadiusWithJsVal(const RefPtr<ShapeRect>& shapeRect, const JSRef<JSVal>& jsVal)
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
}

void JSRectShape::SetRadiusWithArrayValue(const RefPtr<ShapeRect>& shapeRect, const JSRef<JSVal>& jsVal)
{
    if (!jsVal->IsArray() || !shapeRect) {
        return;
    }

    JSRef<JSArray> array = JSRef<JSArray>::Cast(jsVal);

    auto length = static_cast<int32_t>(array->Length());
    if (length <= 0) {
        return;
    }
    length = std::min(length, LENGTH_ARRAY);

    for (int32_t i = 0; i < length; i++) {
        JSRef<JSVal> radiusItem = array->GetValueAt(i);
        if (!radiusItem->IsArray()) {
            CalcDimension radiusXYValue(0.0f);
            if (!ParseJsDimensionVpNG(radiusItem, radiusXYValue)) {
                radiusXYValue.SetValue(0.0f);
            }
            SetRadiusValue(shapeRect, radiusXYValue, radiusXYValue, i);
            continue;
        }
        
        JSRef<JSArray> radiusArray = JSRef<JSArray>::Cast(radiusItem);
        if (radiusArray->Length() != LENGTH_RADIUS_ARRAY) {
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

void JSRectShape::SetRadiusValue(
    const RefPtr<ShapeRect>& shapeRect, const CalcDimension& radiusX, const CalcDimension& radiusY, int32_t index)
{
    CHECK_NULL_VOID(shapeRect);
    auto newRadius = Ace::Radius(Dimension(radiusX), Dimension(radiusY));
    switch (index) {
        case TOP_LEFT_RADIUS:
            shapeRect->SetTopLeftRadius(newRadius);
            break;
        case TOP_RIGHT_RADIUS:
            shapeRect->SetTopRightRadius(newRadius);
            break;
        case BOTTOM_RIGHT_RADIUS:
            shapeRect->SetBottomRightRadius(newRadius);
            break;
        case BOTTOM_LEFT_RADIUS:
            shapeRect->SetBottomLeftRadius(newRadius);
            break;
        default:
            break;
    }
}

void JSRectShape::ConstructorCallback(const JSCallbackInfo& info)
{
    auto jsRectShape = AceType::MakeRefPtr<JSRectShape>();
    auto rect = AceType::MakeRefPtr<ShapeRect>();

    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        CalcDimension width;
        if (ParseJsDimensionVpNG(obj->GetProperty("width"), width) && width.IsValid()) {
            rect->SetWidth(width);
        }

        CalcDimension height;
        if (ParseJsDimensionVpNG(obj->GetProperty("height"), height) && height.IsValid()) {
            rect->SetHeight(height);
        }

        CalcDimension radiusWidth;
        if (ParseJsDimensionVpNG(obj->GetProperty("radiusWidth"), radiusWidth) && radiusWidth.IsValid()) {
            rect->SetRadiusWidth(radiusWidth);
        }

        CalcDimension radiusHeight;
        if (ParseJsDimensionVpNG(obj->GetProperty("radiusHeight"), radiusHeight) && radiusHeight.IsValid()) {
            rect->SetRadiusHeight(radiusHeight);
        }

        JSRef<JSVal> radius = obj->GetProperty("radius");
        if (radius->IsNumber() || radius->IsString()) {
            SetRadiusWithJsVal(rect, radius);
        }
        if (radius->IsArray()) {
            SetRadiusWithArrayValue(rect, radius);
        }
        info.SetReturnValue(info.This());
    }

    jsRectShape->SetBasicShape(rect);
    jsRectShape->IncRefCount();
    info.SetReturnValue(AceType::RawPtr(jsRectShape));
}

void JSRectShape::DestructorCallback(JSRectShape* jsRectShape)
{
    if (jsRectShape != nullptr) {
        jsRectShape->DecRefCount();
    }
}

void JSRectShape::JSBind(BindingTarget globalObj)
{
    JSClass<JSRectShape>::Declare("__RectShape__");

    JSClass<JSRectShape>::CustomMethod("width", &JSShapeAbstract::ObjectWidth);
    JSClass<JSRectShape>::CustomMethod("height", &JSShapeAbstract::ObjectHeight);
    JSClass<JSRectShape>::CustomMethod("size", &JSShapeAbstract::ObjectSize);
    JSClass<JSRectShape>::CustomMethod("offset", &JSShapeAbstract::ObjectOffset);
    JSClass<JSRectShape>::CustomMethod("radiusWidth", &JSRectShape::ObjectRadiusWidth);
    JSClass<JSRectShape>::CustomMethod("radiusHeight", &JSRectShape::ObjectRadiusHeight);
    JSClass<JSRectShape>::CustomMethod("radius", &JSRectShape::ObjectRadius);
    JSClass<JSRectShape>::CustomMethod("fill", &JSShapeAbstract::ObjectFill);
    JSClass<JSRectShape>::CustomMethod("position", &JSShapeAbstract::ObjectPosition);

    JSClass<JSRectShape>::InheritAndBind<JSShapeAbstract>(
        globalObj, JSRectShape::ConstructorCallback, JSRectShape::DestructorCallback);
}

} // namespace OHOS::Ace::Framework
