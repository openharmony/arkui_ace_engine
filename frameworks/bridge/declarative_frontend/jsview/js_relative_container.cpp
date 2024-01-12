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

#include "frameworks/bridge/declarative_frontend/jsview/js_relative_container.h"

#include "base/log/ace_trace.h"
#include "bridge/declarative_frontend/jsview/models/relative_container_model_impl.h"
#include "core/components_ng/pattern/relative_container/relative_container_model_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace {

std::unique_ptr<RelativeContainerModel> RelativeContainerModel::instance_ = nullptr;
std::mutex RelativeContainerModel::mutex_;

RelativeContainerModel* RelativeContainerModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::RelativeContainerModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::RelativeContainerModelNG());
            } else {
                instance_.reset(new Framework::RelativeContainerModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSRelativeContainer::JSBind(BindingTarget globalObj)
{
    JSClass<JSRelativeContainer>::Declare("RelativeContainer");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSRelativeContainer>::StaticMethod("create", &JSRelativeContainer::Create, opt);
    JSClass<JSRelativeContainer>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSRelativeContainer>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSRelativeContainer>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSRelativeContainer>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSRelativeContainer>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSRelativeContainer>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSRelativeContainer>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSRelativeContainer>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSRelativeContainer>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSRelativeContainer::Create(const JSCallbackInfo& info)
{
    RelativeContainerModel::GetInstance()->Create();
}

} // namespace OHOS::Ace::Framework
