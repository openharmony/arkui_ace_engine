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

#include "frameworks/bridge/declarative_frontend/jsview/js_column.h"

namespace OHOS::Ace::Framework {

void JSColumn::JSBind(BindingTarget globalObj)
{
    JSClass<JSColumn>::Declare("Column");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSColumn>::StaticMethod("create", &JSColumn::Create, opt);
    JSClass<JSColumn>::StaticMethod("createWithWrap", &JSColumn::CreateWithWrap, opt);
    JSClass<JSColumn>::StaticMethod("fillParent", &JSFlex::SetFillParent, opt);
    JSClass<JSColumn>::StaticMethod("wrapContent", &JSFlex::SetWrapContent, opt);
    JSClass<JSColumn>::StaticMethod("justifyContent", &JSColumn::SetJustifyContent, opt);
    JSClass<JSColumn>::StaticMethod("alignItems", &JSColumn::SetAlignItems, opt);
    JSClass<JSColumn>::StaticMethod("alignContent", &JSFlex::SetAlignContent, opt);
    JSClass<JSColumn>::StaticMethod("height", &JSFlex::JsHeight, opt);
    JSClass<JSColumn>::StaticMethod("width", &JSFlex::JsWidth, opt);
    JSClass<JSColumn>::StaticMethod("size", &JSFlex::JsSize, opt);
    JSClass<JSColumn>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSColumn>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSColumn>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSColumn>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSColumn>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSColumn>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSColumn>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSColumn>::StaticMethod("onPan", &JSInteractableView::JsOnPan);
    JSClass<JSColumn>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSColumn>::Inherit<JSContainerBase>();
    JSClass<JSColumn>::Inherit<JSViewAbstract>();
    JSClass<JSColumn>::Bind<>(globalObj);

    JSClass<HorizontalAlignDeclaration>::Declare("HorizontalAlignDeclaration");
    JSClass<HorizontalAlignDeclaration>::Bind(
        globalObj, HorizontalAlignDeclaration::ConstructorCallback, HorizontalAlignDeclaration::DestructorCallback);
}

} // namespace OHOS::Ace::Framework
