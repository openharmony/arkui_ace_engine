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

#include "frameworks/bridge/declarative_frontend/jsview/js_effect_view.h"

#include "bridge/declarative_frontend/jsview/models/effect_view_model_impl.h"
#include "core/components_ng/pattern/effect_view/effect_view_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"

namespace OHOS::Ace {
std::unique_ptr<EffectViewModel> EffectViewModel::instance_ = nullptr;
std::mutex EffectViewModel::mutex_;

EffectViewModel* EffectViewModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::EffectViewModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::EffectViewModelNG());
            } else {
                // empty implementation
                instance_.reset(new Framework::EffectViewModelImpl());
            }
        }
#endif
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSEffectView::Create()
{
    EffectViewModel::GetInstance()->Create();
}

void JSEffectView::JSBind(BindingTarget globalObj)
{
    JSClass<JSEffectView>::Declare("EffectView");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSEffectView>::StaticMethod("create", &JSEffectView::Create, opt);

    JSClass<JSEffectView>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework
