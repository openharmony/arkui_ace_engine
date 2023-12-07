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

#include "bridge/declarative_frontend/jsview/window_scene/js_screen.h"

#include "core/components_ng/pattern/window_scene/screen/screen_model.h"

namespace OHOS::Ace::Framework {
void JSScreen::JSBind(BindingTarget globalObj)
{
    JSClass<JSScreen>::Declare("Screen");
    JSClass<JSScreen>::StaticMethod("create", &JSScreen::Create, MethodOptions::NONE);

    JSClass<JSScreen>::Inherit<JSInteractableView>();
    JSClass<JSScreen>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSScreen::Create(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }

    if (info.Length() != 1) {
        return;
    }

    if (!info[0]->IsNumber()) {
        return;
    }

    auto screenId = static_cast<uint64_t>(info[0]->ToNumber<double>());
    NG::ScreenModel::Create(screenId);
}
} // namespace OHOS::Ace::Framework
