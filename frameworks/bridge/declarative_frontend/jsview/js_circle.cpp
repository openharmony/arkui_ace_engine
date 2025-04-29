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

#include "bridge/declarative_frontend/jsview/models/circle_model_impl.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/shape/circle_model.h"
#include "core/components_ng/pattern/shape/circle_model_ng.h"

namespace OHOS::Ace {
CircleModel* CircleModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::CircleModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::CircleModelNG instance;
        return &instance;
    } else {
        static Framework::CircleModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSCircle::Create(const JSCallbackInfo& info)
{
    CircleModel::GetInstance()->Create();
    JSShapeAbstract::SetSize(info);
}

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
    JSClass<JSCircle>::Declare("Circle");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSCircle>::StaticMethod("create", &JSCircle::Create, opt);

    JSClass<JSCircle>::CustomMethod("width", &JSShapeAbstract::ObjectWidth);
    JSClass<JSCircle>::CustomMethod("height", &JSShapeAbstract::ObjectHeight);
    JSClass<JSCircle>::CustomMethod("size", &JSShapeAbstract::ObjectSize);
    JSClass<JSCircle>::CustomMethod("offset", &JSShapeAbstract::ObjectOffset);
    JSClass<JSCircle>::CustomMethod("fill", &JSShapeAbstract::ObjectFill);
    JSClass<JSCircle>::CustomMethod("position", &JSShapeAbstract::ObjectPosition);

    JSClass<JSCircle>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSCircle>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSCircle>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSCircle>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSCircle>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSCircle>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);

    JSClass<JSCircle>::InheritAndBind<JSShapeAbstract>(
        globalObj, JSCircle::ConstructorCallback, JSCircle::DestructorCallback);
}

} // namespace OHOS::Ace::Framework
