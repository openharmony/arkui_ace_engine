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

#include "js_host_window_scene.h"

#include "frameworks/core/components_ng/pattern/window_scene/host/host_window_scene_view.h"

namespace OHOS::Ace::Framework {
void JSHostWindowSceneView::Create(const JSCallbackInfo &info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        LOGE("Window scene is only supported on new pipeline!");
        return;
    }

    // auto sceneSession = CreateSceneSessionFromNapiValue(info[0]);
    NG::HostWindowSceneView::Create(/*sceneSession*/);
}

void JSHostWindowSceneView::JSBind(BindingTarget globalObj)
{
    JSClass<JSHostWindowSceneView>::Declare("WindowSceneView");
    JSClass<JSHostWindowSceneView>::StaticMethod("create", &JSHostWindowSceneView::Create, MethodOptions::NONE);
    JSClass<JSHostWindowSceneView>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSHostWindowSceneView>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSHostWindowSceneView>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSHostWindowSceneView>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSHostWindowSceneView>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSHostWindowSceneView>::Inherit<JSViewAbstract>();
    JSClass<JSHostWindowSceneView>::Bind<>(globalObj);
}
} // namespace OHOS::Ace::Framework
