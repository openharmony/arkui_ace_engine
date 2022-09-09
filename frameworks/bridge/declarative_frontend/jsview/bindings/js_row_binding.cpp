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

#include "frameworks/bridge/declarative_frontend/jsview/js_row.h"

namespace OHOS::Ace::Framework {

void JSRow::JSBind(BindingTarget globalObj)
{
    JSClass<JSRow>::Declare("Row");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSRow>::StaticMethod("create", &JSRow::Create, opt);
    JSClass<JSRow>::StaticMethod("createWithWrap", &JSRow::CreateWithWrap, opt);
    JSClass<JSRow>::StaticMethod("fillParent", &JSFlex::SetFillParent, opt);
    JSClass<JSRow>::StaticMethod("wrapContent", &JSFlex::SetWrapContent, opt);
    JSClass<JSRow>::StaticMethod("justifyContent", &JSRow::SetJustifyContent, opt);
    JSClass<JSRow>::StaticMethod("alignItems", &JSRow::SetAlignItems, opt);
    JSClass<JSRow>::StaticMethod("alignContent", &JSFlex::SetAlignContent, opt);
    JSClass<JSRow>::StaticMethod("height", &JSFlex::JsHeight, opt);
    JSClass<JSRow>::StaticMethod("width", &JSFlex::JsWidth, opt);
    JSClass<JSRow>::StaticMethod("size", &JSFlex::JsSize, opt);
    JSClass<JSRow>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSRow>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSRow>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSRow>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSRow>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSRow>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSRow>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSRow>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSRow>::Inherit<JSContainerBase>();
    JSClass<JSRow>::Inherit<JSViewAbstract>();
    JSClass<JSRow>::Bind<>(globalObj);

    JSClass<VerticalAlignDeclaration>::Declare("VerticalAlignDeclaration");
    JSClass<VerticalAlignDeclaration>::Bind(
        globalObj, VerticalAlignDeclaration::ConstructorCallback, VerticalAlignDeclaration::DestructorCallback);
}

} // namespace OHOS::Ace::Framework
