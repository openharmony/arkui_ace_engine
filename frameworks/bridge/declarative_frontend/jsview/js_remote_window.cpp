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

#include "frameworks/bridge/declarative_frontend/jsview/js_remote_window.h"

#include "core/components/remote_window/remote_window_component.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
void JSRemoteWindow::Create(const JSCallbackInfo& info)
{
    // specialized component should be firstly pushed.
    auto specializedComponent = AceType::MakeRefPtr<OHOS::Ace::RemoteWindowComponent>();
    ViewStackProcessor::GetInstance()->Push(specializedComponent);

    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

#ifdef ENABLE_ROSEN_BACKEND
    auto rsNode = CreateRSNodeFromNapiValue(info[0]);
    specializedComponent->SetExternalRSNode(rsNode);
#endif
}

void JSRemoteWindow::JSBind(BindingTarget globalObj)
{
    JSClass<JSRemoteWindow>::Declare("RemoteWindow");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSRemoteWindow>::StaticMethod("create", &JSRemoteWindow::Create, opt);

    JSClass<JSRemoteWindow>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSRemoteWindow>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSRemoteWindow>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSRemoteWindow>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSRemoteWindow>::StaticMethod("onClick", &JSInteractableView::JsOnClick);

    JSClass<JSRemoteWindow>::Inherit<JSViewAbstract>();
    JSClass<JSRemoteWindow>::Bind<>(globalObj);
}
} // namespace OHOS::Ace::Framework
