/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_common_view.h"

#include "bridge/declarative_frontend/jsview/models/common_view_model_impl.h"
#include "core/components_ng/pattern/common_view/common_view_model_ng.h"

namespace OHOS::Ace {
std::unique_ptr<CommonViewModel> CommonViewModel::instance_ = nullptr;
std::mutex CommonViewModel::mutex_;

CommonViewModel* CommonViewModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::CommonViewModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::CommonViewModelNG());
            } else {
                instance_.reset(new Framework::CommonViewModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSCommonView::Create(const JSCallbackInfo& info)
{
    CommonViewModel::GetInstance()->Create(false);
}

void JSCommonView::JSBind(BindingTarget globalObj)
{
    JSClass<JSCommonView>::Declare("__Common__");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSCommonView>::StaticMethod("create", &JSCommonView::Create, opt);
    JSClass<JSCommonView>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSCommonView>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSCommonView>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSCommonView>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSCommonView>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSCommonView>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSCommonView>::StaticMethod("onHoverMove", &JSInteractableView::JsOnHoverMove);
    JSClass<JSCommonView>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSCommonView>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSCommonView>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSCommonView>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);

    JSClass<JSCommonView>::InheritAndBind<JSContainerBase>(globalObj);
}
} // namespace OHOS::Ace::Framework
