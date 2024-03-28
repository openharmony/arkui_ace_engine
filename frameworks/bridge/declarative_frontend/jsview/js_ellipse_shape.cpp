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

#include "frameworks/bridge/declarative_frontend/jsview/js_ellipse_shape.h"

namespace OHOS::Ace::Framework {

void JSEllipseShape::ConstructorCallback(const JSCallbackInfo& info)
{
    auto ellipse = AceType::MakeRefPtr<Ellipse>();

    if (info.Length() == 1 && info[0]->IsObject()) {
        JSRef<JSObject> params = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> width = params->GetProperty("width");
        CalcDimension dimWidth;
        if (ParseJsDimensionVpNG(width, dimWidth) && dimWidth.IsValid()) {
            ellipse->SetWidth(dimWidth);
        }
        JSRef<JSVal> height = params->GetProperty("height");
        CalcDimension dimHeight;
        if (ParseJsDimensionVpNG(height, dimHeight) && dimHeight.IsValid()) {
            ellipse->SetHeight(dimHeight);
        }
    }

    auto jsEllipse = AceType::MakeRefPtr<JSEllipseShape>();
    jsEllipse->SetBasicShape(ellipse);
    jsEllipse->IncRefCount();
    info.SetReturnValue(AceType::RawPtr(jsEllipse));
}

void JSEllipseShape::DestructorCallback(JSEllipseShape* jsEllipseShape)
{
    if (jsEllipseShape != nullptr) {
        jsEllipseShape->DecRefCount();
    }
}

void JSEllipseShape::JSBind(BindingTarget globalObj)
{
    JSClass<JSEllipseShape>::Declare("__EllipseShape__");

    JSClass<JSEllipseShape>::CustomMethod("width", &JSShapeAbstract::ObjectWidth);
    JSClass<JSEllipseShape>::CustomMethod("height", &JSShapeAbstract::ObjectHeight);
    JSClass<JSEllipseShape>::CustomMethod("size", &JSShapeAbstract::ObjectSize);
    JSClass<JSEllipseShape>::CustomMethod("offset", &JSShapeAbstract::ObjectOffset);
    JSClass<JSEllipseShape>::CustomMethod("fill", &JSShapeAbstract::ObjectFill);
    JSClass<JSEllipseShape>::CustomMethod("position", &JSShapeAbstract::ObjectPosition);

    JSClass<JSEllipseShape>::InheritAndBind<JSShapeAbstract>(
        globalObj, JSEllipseShape::ConstructorCallback, JSEllipseShape::DestructorCallback);
}

} // namespace OHOS::Ace::Framework
