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
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/shape/rect_model_ng.h"

namespace {
OHOS::Ace::NG::RectModelNG* GetRectModel()
{
    static OHOS::Ace::NG::RectModelNG* cachedModel = nullptr;
    if (cachedModel == nullptr) {
        auto* module = OHOS::Ace::DynamicModuleHelper::GetInstance().GetDynamicModule("Rect");
        if (module == nullptr) {
            LOGF_ABORT("Can't find rect dynamic module");
        }
        cachedModel = reinterpret_cast<OHOS::Ace::NG::RectModelNG*>(module->GetModel());
    }
    return cachedModel;
}
} // namespace

namespace OHOS::Ace::Framework {

void JSRect::SetRadiusWithJsVal(const RefPtr<ShapeRect>& shapeRect, const JSRef<JSVal>& jsVal)
{
    CalcDimension value(0.0f);
    RefPtr<ResourceObject> radiusResObj;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        ParseJsDimensionVp(jsVal, value, radiusResObj);
    } else {
        if (!ParseJsDimensionVpNG(jsVal, value, radiusResObj)) {
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

void JSRect::SetRadiusWithArrayValue(const RefPtr<ShapeRect>& shapeRect, const JSRef<JSVal>& jsVal)
{
    static std::vector<std::string> RADIUS_TYPES = { "TopLeft", "TopRight", "BottomRight", "BottomLeft" };
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
        RefPtr<ResourceObject> radiusXResObj;
        RefPtr<ResourceObject> radiusYResObj;
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            if (ParseJsDimensionVp(radiusX, radiusXValue)) {
                ParseJsDimensionVp(radiusY, radiusYValue);
            }
        } else {
            if (!ParseJsDimensionVpNG(radiusX, radiusXValue, radiusXResObj)) {
                radiusXValue.SetValue(0.0f);
            }
            if (!ParseJsDimensionVpNG(radiusY, radiusYValue, radiusYResObj)) {
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
        GetRectModel()->SetShapeRectRadius(shapeRect, radiusX, radiusY, index);
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
    JSClass<JSRect>::Declare("__Rect__");

    JSClass<JSRect>::CustomMethod("width", &JSShapeAbstract::ObjectWidth);
    JSClass<JSRect>::CustomMethod("height", &JSShapeAbstract::ObjectHeight);
    JSClass<JSRect>::CustomMethod("size", &JSShapeAbstract::ObjectSize);
    JSClass<JSRect>::CustomMethod("offset", &JSShapeAbstract::ObjectOffset);
    JSClass<JSRect>::CustomMethod("radiusWidth", &JSRect::ObjectRadiusWidth);
    JSClass<JSRect>::CustomMethod("radiusHeight", &JSRect::ObjectRadiusHeight);
    JSClass<JSRect>::CustomMethod("radius", &JSRect::ObjectRadius);
    JSClass<JSRect>::CustomMethod("fill", &JSShapeAbstract::ObjectFill);
    JSClass<JSRect>::CustomMethod("position", &JSShapeAbstract::ObjectPosition);

    JSClass<JSRect>::InheritAndBind<JSShapeAbstract>(
        globalObj, JSRect::ConstructorCallback, JSRect::DestructorCallback);
}

} // namespace OHOS::Ace::Framework
