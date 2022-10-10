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

#include "frameworks/bridge/declarative_frontend/jsview/js_common_view.h"

#include "core/components/proxy/proxy_component.h"
#include "core/components_ng/pattern/common_view/common_view.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
void JSCommonView::Create(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::CommonView::Create();
        return;
    }
    auto specializedBox = AceType::MakeRefPtr<OHOS::Ace::ProxyComponent>();
    specializedBox->SetPassMinSize(false);
    ViewStackProcessor::GetInstance()->Push(specializedBox);
}

void JSCommonView::JSBind(BindingTarget globalObj)
{
    JSClass<JSCommonView>::Declare("__Common__");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSCommonView>::StaticMethod("create", &JSCommonView::Create, opt);
    JSClass<JSCommonView>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSCommonView>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSCommonView>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSCommonView>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSCommonView>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSCommonView>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSCommonView>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSCommonView>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);

    JSClass<JSCommonView>::Inherit<JSContainerBase>();
    JSClass<JSCommonView>::Bind<>(globalObj);
}
} // namespace OHOS::Ace::Framework
