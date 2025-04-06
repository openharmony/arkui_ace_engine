/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/window_scene/js_root_scene.h"

#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/window_scene/root/root_scene_model.h"

namespace OHOS::Ace::Framework {
void JSRootScene::JSBind(BindingTarget globalObj)
{
    JSClass<JSRootScene>::Declare("RootScene");
    JSClass<JSRootScene>::StaticMethod("create", &JSRootScene::Create, MethodOptions::NONE);
    JSClass<JSRootScene>::StaticMethod("pop", &JSRootScene::Pop, MethodOptions::NONE);
    JSClass<JSRootScene>::Bind(globalObj);
}

void JSRootScene::Create(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        LOGE("Window scene is only supported on new pipeline!");
        return;
    }

    NG::RootSceneModel::Create();
}

void JSRootScene::Pop()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSRootScene][pop]", &JSRootScene::Pop);
    }
    ViewStackModel::GetInstance()->PopContainer();
}
} // namespace OHOS::Ace::Framework
