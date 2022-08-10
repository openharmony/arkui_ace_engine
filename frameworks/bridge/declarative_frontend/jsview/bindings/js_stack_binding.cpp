/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_stack.h"

namespace OHOS::Ace::Framework {

void JSStack::JSBind(BindingTarget globalObj)
{
    JSClass<JSStack>::Declare("Stack");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSStack>::StaticMethod("create", &JSStack::Create, opt);
    JSClass<JSStack>::StaticMethod("stackFit", &JSStack::SetStackFit, opt);
    JSClass<JSStack>::StaticMethod("overflow", &JSStack::SetOverflow, opt);
    JSClass<JSStack>::StaticMethod("alignContent", &JSStack::SetAlignment, opt);
    JSClass<JSStack>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSStack>::StaticMethod("width", SetWidth);
    JSClass<JSStack>::StaticMethod("height", SetHeight);
    JSClass<JSStack>::StaticMethod("size", SetSize);
    JSClass<JSStack>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSStack>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSStack>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSStack>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSStack>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSStack>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSStack>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSStack>::Inherit<JSContainerBase>();
    JSClass<JSStack>::Inherit<JSViewAbstract>();
    JSClass<JSStack>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
