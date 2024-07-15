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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_navigation_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_navigation_stack.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_navdestination_context.h"

namespace OHOS::Ace::Framework {

void JsNavigationTransitionProxy::JSBind(BindingTarget globalObj)
{
    JSClass<JsNavigationTransitionProxy>::Declare("NavigationTransitionProxy");
    JSClass<JsNavigationTransitionProxy>::CustomProperty(
        "from", &JsNavigationTransitionProxy::GetFromContentInfo, &JsNavigationTransitionProxy::SetFromContentInfo);
    JSClass<JsNavigationTransitionProxy>::CustomProperty(
        "to", &JsNavigationTransitionProxy::GetToContentInfo, &JsNavigationTransitionProxy::SetToContentInfo);
    JSClass<JsNavigationTransitionProxy>::CustomMethod(
        "finishTransition", &JsNavigationTransitionProxy::FinishTransition);
    JSClass<JsNavigationTransitionProxy>::CustomProperty("isInteractive", &JsNavigationTransitionProxy::GetInteractive,
        &JsNavigationTransitionProxy::SetInteractive);
    JSClass<JsNavigationTransitionProxy>::CustomMethod("cancelTransition",
        &JsNavigationTransitionProxy::CancelAnimation);
    JSClass<JsNavigationTransitionProxy>::CustomMethod("updateTransition",
        &JsNavigationTransitionProxy::UpdateTransition);
    JSClass<JsNavigationTransitionProxy>::Bind(
        globalObj, &JsNavigationTransitionProxy::Constructor, &JsNavigationTransitionProxy::Destructor);
}

void JsNavigationTransitionProxy::SetFromContentInfo(const JSCallbackInfo& args)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation transition proxy can not support modify from attribute");
}

void JsNavigationTransitionProxy::GetFromContentInfo(const JSCallbackInfo& args)
{
    RefPtr<NG::NavDestinationContext> from;
    if (proxy_) {
        from = proxy_->GetPreDestinationContext();
    }
    auto fromVal = ConvertContentInfo(from);
    args.SetReturnValue(fromVal);
}

void JsNavigationTransitionProxy::SetToContentInfo(const JSCallbackInfo& args)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation transition context can not support modify to attribute");
}

void JsNavigationTransitionProxy::GetToContentInfo(const JSCallbackInfo& args)
{
    RefPtr<NG::NavDestinationContext> to;
    if (proxy_) {
        to = proxy_->GetTopDestinationContext();
    }
    auto toVal = ConvertContentInfo(to);
    args.SetReturnValue(toVal);
}

void JsNavigationTransitionProxy::FinishTransition(const JSCallbackInfo& info)
{
    if (proxy_) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "fire custom animation finish");
        proxy_->FireFinishCallback();
    } else {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "finish interactive animation failed");
    }
}

void JsNavigationTransitionProxy::Constructor(const JSCallbackInfo& info)
{
    auto proxy = Referenced::MakeRefPtr<JsNavigationTransitionProxy>();
    proxy->IncRefCount();
    info.SetReturnValue(Referenced::RawPtr(proxy));
}

void JsNavigationTransitionProxy::Destructor(JsNavigationTransitionProxy* proxy)
{
    if (proxy != nullptr) {
        proxy->DecRefCount();
    }
}

JSRef<JSVal> JsNavigationTransitionProxy::ConvertContentInfo(RefPtr<NG::NavDestinationContext> context)
{
    auto value = JSRef<JSObject>::New();
    if (!context) {
        // current nav content is navBar.Don't need to set name and mode.
        value->SetProperty<int32_t>("index", -1);
        return value;
    }
    auto info = context->GetNavPathInfo();
    CHECK_NULL_RETURN(info, value);
    value->SetProperty<std::string>("name", info->GetName());
    value->SetProperty<int32_t>("index", context->GetIndex());
    value->SetProperty<int32_t>("mode", static_cast<int32_t>(context->GetMode()));
    value->SetProperty<std::string>("navDestinationId", std::to_string(context->GetNavDestinationId()));
    auto jsPathInfo = AceType::DynamicCast<JSNavPathInfo>(info);
    if (jsPathInfo) {
        value->SetPropertyObject("param", jsPathInfo->GetParam());
    }
    return value;
}

void JsNavigationFunction::JSBind(BindingTarget globalObj)
{
    JsNavigationTransitionProxy::JSBind(globalObj);
}

JSRef<JSVal> JsNavigationFunction::Execute(RefPtr<NG::NavDestinationContext> from,
    RefPtr<NG::NavDestinationContext> to, NG::NavigationOperation navigationOperation)
{
    JSRef<JSVal> fromVal = JsNavigationTransitionProxy::ConvertContentInfo(from);
    JSRef<JSVal> toVal = JsNavigationTransitionProxy::ConvertContentInfo(to);
    JSRef<JSVal> operation = JSRef<JSVal>::Make(ToJSValue(static_cast<int32_t>(navigationOperation)));
    JSRef<JSVal> params[] = { fromVal, toVal, operation };
    const int32_t argsNum = 3;
    return JsFunction::ExecuteJS(argsNum, params);
}

void JsNavigationFunction::Execute(const RefPtr<NG::NavigationTransitionProxy>& proxy)
{
    JSRef<JSObject> proxyObj = JSClass<JsNavigationTransitionProxy>::NewInstance();
    auto jsProxy = Referenced::Claim(proxyObj->Unwrap<JsNavigationTransitionProxy>());
    jsProxy->SetProxy(proxy);
    JSRef<JSVal> param = JSRef<JSObject>::Cast(proxyObj);
    JsFunction::ExecuteJS(1, &param);
}

void JsNavigationTransitionProxy::SetInteractive(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "not support set interactive attribute");
}

void JsNavigationTransitionProxy::GetInteractive(const JSCallbackInfo& info)
{
    auto interactive = proxy_ ? proxy_->GetInteractive() : false;
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(interactive)));
}

void JsNavigationTransitionProxy::CancelAnimation(const JSCallbackInfo& info)
{
    if (proxy_ == nullptr) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "cancel interactive animation failed");
        return;
    }
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "fire cancel interactive animation");
    proxy_->CancelInteractiveAnimation();
}

void JsNavigationTransitionProxy::UpdateTransition(const JSCallbackInfo& info)
{
    if (!proxy_) {
        return;
    }
    float progress = 0;
    if (info[0]->IsNumber()) {
        progress = info[0]->ToNumber<float>();
    }
    if (progress >= 0 && progress <= 1) {
        proxy_->UpdateTransition(progress);
    }
}
}; // namespace OHOS::Ace::Framework