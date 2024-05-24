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

#include "frameworks/bridge/declarative_frontend/jsview/js_navigator.h"

#include "core/components/box/box_component.h"
#include "core/components/navigator/navigator_component.h"
#include "core/components_ng/pattern/navigator/navigator_model.h"
#include "core/components_ng/pattern/navigator/navigator_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/navigator_model_impl.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace {

std::unique_ptr<NavigatorModel> NavigatorModel::instance_ = nullptr;
std::mutex NavigatorModel::mutex_;

NavigatorModel* NavigatorModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::NavigatorModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::NavigatorModelNG());
            } else {
                instance_.reset(new Framework::NavigatorModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSNavigator::Create(const JSCallbackInfo& info)
{
    NavigatorModel::GetInstance()->Create();
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> target = obj->GetProperty("target");
        if (target->IsString()) {
            NavigatorModel::GetInstance()->SetUri(target->ToString());
        }

        JSRef<JSVal> type = obj->GetProperty("type");
        if (type->IsNumber()) {
            auto navigatorType = NavigatorType(type->ToNumber<uint32_t>());
            if (navigatorType == NavigatorType::DEFAULT) {
                NavigatorModel::GetInstance()->SetType(NavigatorType::PUSH);
            } else {
                NavigatorModel::GetInstance()->SetType(navigatorType);
            }
        }
    } else {
        NavigatorModel::GetInstance()->SetType(NavigatorType::BACK);
    }
}

void JSNavigator::SetTarget(const std::string& value)
{
    NavigatorModel::GetInstance()->SetUri(value);
}

void JSNavigator::SetType(int32_t value)
{
    auto navigatorType = NavigatorType(value);
    if (navigatorType == NavigatorType::DEFAULT) {
        NavigatorModel::GetInstance()->SetType(NavigatorType::PUSH);
    } else {
        NavigatorModel::GetInstance()->SetType(navigatorType);
    }
}

void JSNavigator::JSBind(BindingTarget globalObj)
{
    JSClass<JSNavigator>::Declare("Navigator");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSNavigator>::StaticMethod("create", &JSNavigator::Create, opt);
    JSClass<JSNavigator>::StaticMethod("target", &JSNavigator::SetTarget, opt);
    JSClass<JSNavigator>::StaticMethod("type", &JSNavigator::SetType, opt);
    JSClass<JSNavigator>::StaticMethod("active", &JSNavigator::SetActive, opt);
    JSClass<JSNavigator>::StaticMethod("params", &JSNavigator::SetParams, opt);
    JSClass<JSNavigator>::StaticMethod("width", &JSNavigator::JsWidth);
    JSClass<JSNavigator>::StaticMethod("height", &JSNavigator::JsHeight);
    JSClass<JSNavigator>::StaticMethod("size", &JSNavigator::JsSize);
    JSClass<JSNavigator>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSNavigator>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSNavigator>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSNavigator>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSNavigator>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSNavigator>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSNavigator>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSNavigator>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSNavigator>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSNavigator>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSNavigator>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSNavigator::SetActive(bool active)
{
    NavigatorModel::GetInstance()->SetActive(active);
}

void JSNavigator::SetParams(const JSCallbackInfo& args)
{
    JSRef<JSVal> val = JSRef<JSVal>::Cast(args[0]);
    NavigatorModel::GetInstance()->SetParams(val->ToString());
}

void JSNavigator::JsWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    JsWidth(info[0]);
}

void JSNavigator::JsWidth(const JSRef<JSVal>& jsValue)
{
    NavigatorModel::GetInstance()->SetIsDefWidth(true);
    JSViewAbstract::JsWidth(jsValue);
}

void JSNavigator::JsHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    JsHeight(info[0]);
}

void JSNavigator::JsHeight(const JSRef<JSVal>& jsValue)
{
    NavigatorModel::GetInstance()->SetIsDefHeight(true);
    JSViewAbstract::JsHeight(jsValue);
}

void JSNavigator::JsSize(const JSCallbackInfo& info)
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

} // namespace OHOS::Ace::Framework
