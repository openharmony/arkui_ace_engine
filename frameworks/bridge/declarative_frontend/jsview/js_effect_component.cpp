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

#include "frameworks/bridge/declarative_frontend/jsview/js_effect_component.h"

#include "bridge/declarative_frontend/jsview/models/effect_component_model_impl.h"
#include "core/components_ng/pattern/effect_component/effect_component_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"

namespace OHOS::Ace {
std::unique_ptr<EffectComponentModel> EffectComponentModel::instance_ = nullptr;
std::mutex EffectComponentModel::mutex_;

EffectComponentModel* EffectComponentModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::EffectComponentModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::EffectComponentModelNG());
            } else {
                // empty implementation
                instance_.reset(new Framework::EffectComponentModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSEffectComponent::Create()
{
    EffectComponentModel::GetInstance()->Create();
}

void JSEffectComponent::AlwaysSnapshot(const JSCallbackInfo& info)
{
    if (info[0]->IsBoolean()) {
        EffectComponentModel::GetInstance()->AlwaysSnapshot(info[0]->ToBoolean());
        return;
    }
    EffectComponentModel::GetInstance()->AlwaysSnapshot(false);
}

void JSEffectComponent::JSBind(BindingTarget globalObj)
{
    JSClass<JSEffectComponent>::Declare("EffectComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSEffectComponent>::StaticMethod("create", &JSEffectComponent::Create, opt);
    JSClass<JSEffectComponent>::StaticMethod("alwaysSnapshot", &JSEffectComponent::AlwaysSnapshot, opt);

    JSClass<JSEffectComponent>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework
