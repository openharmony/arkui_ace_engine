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

#include "frameworks/bridge/declarative_frontend/jsview/js_remote_window.h"

#include "bridge/declarative_frontend/jsview/models/remote_window_model_impl.h"
#include "core/components_ng/pattern/remote_window/remote_window_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"

namespace OHOS::Ace {
std::unique_ptr<RemoteWindowModel> RemoteWindowModel::instance_ = nullptr;
std::mutex RemoteWindowModel::mutex_;

RemoteWindowModel* RemoteWindowModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::RemoteWindowModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::RemoteWindowModelNG());
            } else {
                instance_.reset(new Framework::RemoteWindowModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSRemoteWindow::Create(const JSCallbackInfo& info)
{
    std::shared_ptr<Rosen::RSNode> rsNode;
#ifdef ENABLE_ROSEN_BACKEND
    if (info.Length() < 1) {
        return;
    }
    rsNode = CreateRSNodeFromNapiValue(info[0]);
#endif
    RemoteWindowModel::GetInstance()->Create(rsNode);
}

void JSRemoteWindow::JSBind(BindingTarget globalObj)
{
    JSClass<JSRemoteWindow>::Declare("RemoteWindow");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSRemoteWindow>::StaticMethod("create", &JSRemoteWindow::Create, opt);

    JSClass<JSRemoteWindow>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSRemoteWindow>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSRemoteWindow>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSRemoteWindow>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSRemoteWindow>::StaticMethod("onClick", &JSInteractableView::JsOnClick);

    JSClass<JSRemoteWindow>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework
