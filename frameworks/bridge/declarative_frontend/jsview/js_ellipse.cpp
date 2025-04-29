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

#include "frameworks/bridge/declarative_frontend/jsview/js_ellipse.h"

#include "bridge/declarative_frontend/jsview/models/ellipse_model_impl.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/shape/ellipse_model.h"
#include "core/components_ng/pattern/shape/ellipse_model_ng.h"

namespace OHOS::Ace {
EllipseModel* EllipseModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::EllipseModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::EllipseModelNG instance;
        return &instance;
    } else {
        static Framework::EllipseModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSEllipse::Create(const JSCallbackInfo& info)
{
    EllipseModel::GetInstance()->Create();
    JSShapeAbstract::SetSize(info);
}

void JSEllipse::ConstructorCallback(const JSCallbackInfo& info)
{
    auto ellipse = AceType::MakeRefPtr<Ellipse>();
    if (info.Length() == 1 && info[0]->IsObject()) {
        JSRef<JSObject> params = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> width = params->GetProperty("width");
        CalcDimension dimWidth;
        JSRef<JSVal> height = params->GetProperty("height");
        CalcDimension dimHeight;
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            if (ParseJsDimensionVp(width, dimWidth)) {
                ellipse->SetWidth(dimWidth);
            }
            if (ParseJsDimensionVp(height, dimHeight)) {
                ellipse->SetHeight(dimHeight);
            }
        } else {
            if (ParseJsDimensionVpNG(width, dimWidth) && dimWidth.IsValid()) {
                ellipse->SetWidth(dimWidth);
            }
            if (ParseJsDimensionVpNG(height, dimHeight) && dimHeight.IsValid()) {
                ellipse->SetHeight(dimHeight);
            }
        }
    }
    auto jsEllipse = AceType::MakeRefPtr<JSEllipse>();
    jsEllipse->SetBasicShape(ellipse);
    jsEllipse->IncRefCount();
    info.SetReturnValue(AceType::RawPtr(jsEllipse));
}

void JSEllipse::DestructorCallback(JSEllipse* jsEllipse)
{
    if (jsEllipse != nullptr) {
        jsEllipse->DecRefCount();
    }
}

void JSEllipse::JSBind(BindingTarget globalObj)
{
    JSClass<JSEllipse>::Declare("Ellipse");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSEllipse>::StaticMethod("create", &JSEllipse::Create, opt);

    JSClass<JSEllipse>::CustomMethod("width", &JSShapeAbstract::ObjectWidth);
    JSClass<JSEllipse>::CustomMethod("height", &JSShapeAbstract::ObjectHeight);
    JSClass<JSEllipse>::CustomMethod("size", &JSShapeAbstract::ObjectSize);
    JSClass<JSEllipse>::CustomMethod("offset", &JSShapeAbstract::ObjectOffset);
    JSClass<JSEllipse>::CustomMethod("fill", &JSShapeAbstract::ObjectFill);
    JSClass<JSEllipse>::CustomMethod("position", &JSShapeAbstract::ObjectPosition);

    JSClass<JSEllipse>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSEllipse>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSEllipse>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSEllipse>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSEllipse>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSEllipse>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);

    JSClass<JSEllipse>::InheritAndBind<JSShapeAbstract>(
        globalObj, JSEllipse::ConstructorCallback, JSEllipse::DestructorCallback);
}

} // namespace OHOS::Ace::Framework
