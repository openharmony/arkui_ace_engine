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
#include "core/components_ng/pattern/relative_container/relative_container_view.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/core/components/relative_container/relative_container_component.h"

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
#ifdef NG_BUILD
    NG::RelativeContainerView::Create();
#else
    if (Container::IsCurrentUseNewPipeline()) {
        NG::RelativeContainerView::Create();
        return;
    }
    std::list<RefPtr<Component>> children;
    RefPtr<OHOS::Ace::RelativeContainerComponent> component = AceType::MakeRefPtr<RelativeContainerComponent>(children);
    ViewStackProcessor::GetInstance()->Push(component);
    JSInteractableView::SetFocusNode(true);
#endif
}

} // namespace OHOS::Ace::Framework
