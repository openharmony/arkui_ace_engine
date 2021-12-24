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

#include "frameworks/bridge/declarative_frontend/jsview/js_web.h"

#include <string>
#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components/web/web_component.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_web_controller.h"

namespace OHOS::Ace::Framework {
void JSWeb::JSBind(BindingTarget globalObj)
{
    JSClass<JSWeb>::Declare("Web");
    JSClass<JSWeb>::StaticMethod("create", &JSWeb::Create);
    JSClass<JSWeb>::StaticMethod("onPageStart", &JSWeb::OnPageStart);
    JSClass<JSWeb>::StaticMethod("onPageFinish", &JSWeb::OnPageFinish);
    JSClass<JSWeb>::StaticMethod("onError", &JSWeb::OnError);
    JSClass<JSWeb>::StaticMethod("onMessage", &JSWeb::OnMessage);
    JSClass<JSWeb>::Inherit<JSViewAbstract>();
    JSClass<JSWeb>::Bind(globalObj);
}

void JSWeb::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGI("web create error, info is non-vaild");
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto src = paramObject->GetProperty("src");
    RefPtr<WebComponent> webComponent = AceType::MakeRefPtr<OHOS::Ace::WebComponent>(src->ToString());
    if (!src->IsString()) {
        LOGI("web create error, src is non-vaild");
        return;
    }
    webComponent->SetSrc(src->ToString());
    auto controllerObj = paramObject->GetProperty("controller");
    if (!controllerObj->IsObject()) {
        LOGI("web create error, controller is non-vaild");
        return;
    }
    auto controller = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSWebController>();
    if (controller) {
        webComponent->SetWebController(controller->GetController());
    }
    ViewStackProcessor::GetInstance()->Push(webComponent);
}

void JSWeb::OnPageStart(const JSCallbackInfo& args)
{
    if (!JSViewBindEvent(&WebComponent::SetOnPageStart, args)) {
        LOGW("Failed to bind start event");
    }

    args.ReturnSelf();
}

void JSWeb::OnPageFinish(const JSCallbackInfo& args)
{
    if (!JSViewBindEvent(&WebComponent::SetOnPageFinish, args)) {
        LOGW("Failed to bind finish event");
    }

    args.ReturnSelf();
}

void JSWeb::OnError(const JSCallbackInfo& args)
{
    if (!JSViewBindEvent(&WebComponent::SetOnError, args)) {
        LOGW("Failed to bind error event");
    }

    args.ReturnSelf();
}

void JSWeb::OnMessage(const JSCallbackInfo& args)
{
    if (!JSViewBindEvent(&WebComponent::SetOnMessage, args)) {
        LOGW("Failed to bind message event");
    }

    args.ReturnSelf();
}
} // namespace OHOS::Ace::Framework