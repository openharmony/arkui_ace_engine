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

#include "frameworks/bridge/declarative_frontend/jsview/js_circle_shape.h"

namespace OHOS::Ace::Framework {

void JSCircleShape::ConstructorCallback(const JSCallbackInfo& info)
{
    auto circle = AceType::MakeRefPtr<Circle>();

    if (info.Length() == 1 && info[0]->IsObject()) {
        JSRef<JSObject> params = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> width = params->GetProperty("width");
        CalcDimension dimWidth;

        if (ParseJsDimensionVpNG(width, dimWidth) && dimWidth.IsValid()) {
            circle->SetWidth(dimWidth);
        }

        JSRef<JSVal> height = params->GetProperty("height");
        CalcDimension dimHeight;

        if (ParseJsDimensionVpNG(height, dimHeight) && dimHeight.IsValid()) {
            circle->SetHeight(dimHeight);
        }
    }

    auto jsCircle = AceType::MakeRefPtr<JSCircleShape>();
    jsCircle->SetBasicShape(circle);
    jsCircle->IncRefCount();
    info.SetReturnValue(AceType::RawPtr(jsCircle));
}

void JSCircleShape::DestructorCallback(JSCircleShape* jsCircleShape)
{
    if (jsCircleShape != nullptr) {
        jsCircleShape->DecRefCount();
    }
}

void JSCircleShape::JSBind(BindingTarget globalObj)
{
    JSClass<JSCircleShape>::Declare("__CircleShape__");

    JSClass<JSCircleShape>::CustomMethod("width", &JSShapeAbstract::ObjectWidth);
    JSClass<JSCircleShape>::CustomMethod("height", &JSShapeAbstract::ObjectHeight);
    JSClass<JSCircleShape>::CustomMethod("size", &JSShapeAbstract::ObjectSize);
    JSClass<JSCircleShape>::CustomMethod("offset", &JSShapeAbstract::ObjectOffset);
    JSClass<JSCircleShape>::CustomMethod("fill", &JSShapeAbstract::ObjectFill);
    JSClass<JSCircleShape>::CustomMethod("position", &JSShapeAbstract::ObjectPosition);

    JSClass<JSCircleShape>::InheritAndBind<JSShapeAbstract>(
        globalObj, JSCircleShape::ConstructorCallback, JSCircleShape::DestructorCallback);
}

} // namespace OHOS::Ace::Framework
