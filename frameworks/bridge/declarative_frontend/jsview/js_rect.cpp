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

std::unique_ptr<RectModel> RectModel::instance_ = nullptr;
std::mutex RectModel::mutex_;

RectModel* RectModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::RectModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::RectModelNG());
            } else {
                instance_.reset(new Framework::RectModelImpl());
            }
#endif
        }
    }
    return instance_.get();
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
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    SetRadiusWidth(info[0]);
}

void JSRect::JsRadiusHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    SetRadiusHeight(info[0]);
}

void JSRect::SetRadiusWidth(const JSRef<JSVal>& jsVal)
{
    CalcDimension value(0.0f);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!ParseJsDimensionVp(jsVal, value)) {
            LOGW("value is invalid, use default value(0.0) instead.");
        }
    } else {
        if (!ParseJsDimensionVpNG(jsVal, value)) {
            LOGW("value is invalid, use default value(0.0) instead.");
            value.SetValue(0.0f);
        }
    }
    RectModel::GetInstance()->SetRadiusWidth(value);
}

void JSRect::SetRadiusHeight(const JSRef<JSVal>& jsVal)
{
    CalcDimension value(0.0f);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!ParseJsDimensionVp(jsVal, value)) {
            LOGW("value is invalid, use default value(0.0) instead.");
        }
    } else {
        if (!ParseJsDimensionVpNG(jsVal, value)) {
            LOGW("value is invalid, use default value(0.0) instead.");
            value.SetValue(0.0f);
        }
    }
    RectModel::GetInstance()->SetRadiusHeight(value);
}

void JSRect::SetRadius(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
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
        if (!ParseJsDimensionVp(jsVal, value)) {
            LOGW("value is invalid, use default value(0.0) instead.");
        }
    } else {
        if (!ParseJsDimensionVpNG(jsVal, value)) {
            LOGW("value is invalid, use default value(0.0) instead.");
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
        LOGE("The arg is not array.");
        return;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(jsVal);
    auto length = static_cast<int32_t>(array->Length());
    if (length <= 0) {
        LOGE("info is invalid");
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
            if (!ParseJsDimensionVp(radiusX, radiusXValue) || !ParseJsDimensionVp(radiusY, radiusYValue)) {
                LOGW("value is invalid, use default value(0.0) instead.");
            }
        } else {
            if (!ParseJsDimensionVpNG(radiusX, radiusXValue)) {
                LOGW("radiusX is invalid, use default value(0.0) instead.");
                radiusXValue.SetValue(0.0f);
            }
            if (!ParseJsDimensionVpNG(radiusY, radiusYValue)) {
                LOGW("radiusY is invalid, use default value(0.0) instead.");
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
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        LOGE("Value is less than zero");
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
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        LOGE("Value is less than zero");
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
        LOGE("arg is invalid");
        return;
    }
    auto rect = AceType::DynamicCast<ShapeRect>(basicShape_);
    if (!rect) {
        LOGE("rect is null");
        return;
    }
    if (info[0]->IsNumber() || info[0]->IsString()) {
        SetRadiusWithJsVal(rect, info[0]);
    }
    if (info[0]->IsArray()) {
        SetRadiusWithArrayValue(rect, info[0]);
    }
}

void JSRect::ConstructorCallback(const JSCallbackInfo& info)
{
    auto jsRect = AceType::MakeRefPtr<JSRect>();
    auto rect = AceType::MakeRefPtr<ShapeRect>();
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        CalcDimension width;
        if (ParseJsDimensionVp(obj->GetProperty("width"), width) && width.IsValid()) {
            rect->SetWidth(width);
        }
        CalcDimension height;
        if (ParseJsDimensionVp(obj->GetProperty("height"), height) && height.IsValid()) {
            rect->SetHeight(height);
        }
        CalcDimension radiusWidth;
        if (ParseJsDimensionVp(obj->GetProperty("radiusWidth"), radiusWidth) && radiusWidth.IsValid()) {
            rect->SetRadiusWidth(radiusWidth);
        }
        CalcDimension radiusHeight;
        if (ParseJsDimensionVp(obj->GetProperty("radiusHeight"), radiusHeight) && radiusHeight.IsValid()) {
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
