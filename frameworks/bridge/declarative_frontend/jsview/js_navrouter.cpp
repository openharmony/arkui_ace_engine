/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_navrouter.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navrouter/navrouter_view.h"

namespace OHOS::Ace::Framework {

void JSNavRouter::Create()
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    NG::NavRouterView::Create();
}

void JSNavRouter::SetOnStateChange(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least one argument");
        return;
    }
    if (info[0]->IsFunction()) {
        auto onStateChangeCallback =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onStateChange = [execCtx = info.GetExecutionContext(),
                                        func = std::move(onStateChangeCallback)](bool isActivated) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("OnStateChange");
            JSRef<JSVal> param = JSRef<JSVal>::Make(ToJSValue(isActivated));
            func->ExecuteJS(1, &param);
        };
        NG::NavRouterView::SetOnStateChange(std::move(onStateChange));
        return;
    }
    info.ReturnSelf();
}

void JSNavRouter::JSBind(BindingTarget globalObj)
{
    JSClass<JSNavRouter>::Declare("NavRouter");
    JSClass<JSNavRouter>::StaticMethod("create", &JSNavRouter::Create);
    JSClass<JSNavRouter>::StaticMethod("onStateChange", &JSNavRouter::SetOnStateChange);
    JSClass<JSNavRouter>::Inherit<JSContainerBase>();
    JSClass<JSNavRouter>::Inherit<JSViewAbstract>();
    JSClass<JSNavRouter>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework