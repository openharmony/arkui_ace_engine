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

#include "bridge/declarative_frontend/jsview/window_scene/js_window_scene.h"

#include "core/components_ng/pattern/window_scene/scene/window_scene_model.h"

namespace OHOS::Ace::Framework {
void JSWindowScene::JSBind(BindingTarget globalObj)
{
    JSClass<JSWindowScene>::Declare("WindowScene");
    JSClass<JSWindowScene>::StaticMethod("create", &JSWindowScene::Create, MethodOptions::NONE);
    JSClass<JSWindowScene>::StaticMethod("attractionEffect", &JSWindowScene::JsAttractionEffect);

    JSClass<JSWindowScene>::Inherit<JSInteractableView>();
    JSClass<JSWindowScene>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSWindowScene::Create(const JSCallbackInfo& info)
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

    auto persistentId = static_cast<int32_t>(info[0]->ToNumber<double>());
    NG::WindowSceneModel::Create(persistentId);
}

void JSWindowScene::JsAttractionEffect(const JSCallbackInfo& info)
{
    if (info.Length() < 2) {
        return;
    }
    NG::AttractionEffect property;
    if (info[0]->IsObject()) {
        auto point = JSRef<JSObject>::Cast(info[0]);
        if (!JSViewAbstract::ParseJsDimensionVpNG(point->GetProperty("x"), property.destinationX, false)) {
            property.destinationX.Reset();
        }
        if (!JSViewAbstract::ParseJsDimensionVpNG(point->GetProperty("y"), property.destinationY, false)) {
            property.destinationY.Reset();
        }
    }
    if (info[1]->IsNumber()) {
        auto fraction = info[1]->ToNumber<float>();
        property.fraction = std::clamp(fraction, 0.0f, 1.0f);
    }
    NG::WindowSceneModel::SetAttractionEffect(property);
}
} // namespace OHOS::Ace::Framework
