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

#include "frameworks/bridge/declarative_frontend/jsview/js_recycle_view.h"

#include "bridge/declarative_frontend/engine/bindings_implementation.h"
#include "frameworks/core/components_ng/pattern/recycle_view/recycle_view_model.h"
#include "frameworks/core/components_ng/pattern/recycle_view/recycle_view_model_ng.h"

namespace OHOS::Ace {
std::unique_ptr<RecycleViewModel> RecycleViewModel::instance_ = nullptr;
std::mutex RecycleViewModel::mutex_;

RecycleViewModel* RecycleViewModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::RecycleViewModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::RecycleViewModelNG());
            } else {
                instance_.reset(nullptr);
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSRecycleView::Create(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        RecycleViewModel::GetInstance()->Create();
    }
    return;
}

void JSRecycleView::Pop(const JSCallbackInfo& info)
{
    return;
}

void JSRecycleView::JSBind(BindingTarget globalObj)
{
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSRecycleView>::Declare("__Recycle__");
    JSClass<JSRecycleView>::StaticMethod("create", &JSRecycleView::Create, opt);
    JSClass<JSRecycleView>::StaticMethod("pop", &JSRecycleView::Pop, opt);

    JSClass<JSRecycleView>::InheritAndBind<JSContainerBase>(globalObj);
}
} // namespace OHOS::Ace::Framework
