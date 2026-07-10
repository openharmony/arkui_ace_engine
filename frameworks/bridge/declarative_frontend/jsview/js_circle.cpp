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

#include "frameworks/bridge/declarative_frontend/jsview/js_circle.h"
#include <memory>
#include "core/common/container.h"

namespace OHOS::Ace::Framework {

void JSCircle::ConstructorCallback(const JSCallbackInfo& info)
{
    auto circle = AceType::MakeRefPtr<Circle>();
    if (info.Length() == 1 && info[0]->IsObject()) {
        JSRef<JSObject> params = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> width = params->GetProperty("width");
        CalcDimension dimWidth;
        JSRef<JSVal> height = params->GetProperty("height");
        CalcDimension dimHeight;
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            if (ParseJsDimensionVp(width, dimWidth)) {
                circle->SetWidth(dimWidth);
            }
            if (ParseJsDimensionVp(height, dimHeight)) {
                circle->SetHeight(dimHeight);
            }
        } else {
            if (ParseJsDimensionVpNG(width, dimWidth) && dimWidth.IsValid()) {
                circle->SetWidth(dimWidth);
            }
            if (ParseJsDimensionVpNG(height, dimHeight) && dimHeight.IsValid()) {
                circle->SetHeight(dimHeight);
            }
        }
    }
    auto jsCircle = AceType::MakeRefPtr<JSCircle>();
    jsCircle->SetBasicShape(circle);
    jsCircle->IncRefCount();
    info.SetReturnValue(AceType::RawPtr(jsCircle));
}

void JSCircle::DestructorCallback(JSCircle* jsCircle)
{
    if (jsCircle != nullptr) {
        jsCircle->DecRefCount();
    }
}

void JSCircle::JSBind(BindingTarget globalObj)
{
    JSClass<JSCircle>::Declare("__Circle__");
    JSClass<JSCircle>::CustomMethod("width", &JSShapeAbstract::ObjectWidth);
    JSClass<JSCircle>::CustomMethod("height", &JSShapeAbstract::ObjectHeight);
    JSClass<JSCircle>::CustomMethod("size", &JSShapeAbstract::ObjectSize);
    JSClass<JSCircle>::CustomMethod("offset", &JSShapeAbstract::ObjectOffset);
    JSClass<JSCircle>::CustomMethod("fill", &JSShapeAbstract::ObjectFill);
    JSClass<JSCircle>::CustomMethod("position", &JSShapeAbstract::ObjectPosition);

    JSClass<JSCircle>::InheritAndBind<JSShapeAbstract>(
        globalObj, JSCircle::ConstructorCallback, JSCircle::DestructorCallback);
}

} // namespace OHOS::Ace::Framework
