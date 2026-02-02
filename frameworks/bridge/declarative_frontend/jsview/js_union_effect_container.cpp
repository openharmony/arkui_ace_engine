
/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_union_effect_container.h"

#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components_ng/pattern/union_effect_container/union_effect_container_model.h"
#include "core/components_ng/pattern/union_effect_container/union_effect_container_model_ng.h"
#include "core/components_ng/property/union_effect_container_options.h"

namespace OHOS::Ace {
std::unique_ptr<UnionEffectContainerModel> UnionEffectContainerModel::instance_ = nullptr;
std::mutex UnionEffectContainerModel::mutex_;

UnionEffectContainerModel* UnionEffectContainerModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            instance_.reset(new NG::UnionEffectContainerModelNG());
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSUnionEffectContainer::Create(const JSCallbackInfo& info)
{
    NG::UnionEffectContainerOptions options { .spacing = 0.0f };
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(info[0]);
        auto spacingProperty = obj->GetProperty("spacing");
        if (spacingProperty->IsNumber()) {
            options.spacing = spacingProperty->ToNumber<float>();
        }
    }
    UnionEffectContainerModel::GetInstance()->Create(options);
}

void JSUnionEffectContainer::JSBind(BindingTarget globalObj)
{
    JSClass<JSUnionEffectContainer>::Declare("UnionEffectContainer");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSUnionEffectContainer>::StaticMethod("create", &JSUnionEffectContainer::Create, opt);
    JSClass<JSUnionEffectContainer>::StaticMethod("pointLight", &JSViewAbstract::JsPointLight, opt);

    JSClass<JSUnionEffectContainer>::InheritAndBind<JSContainerBase>(globalObj);
}
} // namespace OHOS::Ace::Framework
