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

#include "js_navigation_function.h"

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
    JSClass<JsNavigationTransitionProxy>::Bind(
        globalObj, &JsNavigationTransitionProxy::Constructor, &JsNavigationTransitionProxy::Destructor);
}

void JsNavigationTransitionProxy::SetFromContentInfo(const JSCallbackInfo& args)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation transition proxy can not support modify from attribute");
}

void JsNavigationTransitionProxy::GetFromContentInfo(const JSCallbackInfo& args)
{
    NG::NavContentInfo from;
    if (proxy_) {
        from = proxy_->GetPreDestination();
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
    NG::NavContentInfo to;
    if (proxy_) {
        to = proxy_->GetTopDestination();
    }
    auto toVal = ConvertContentInfo(to);
    args.SetReturnValue(toVal);
}

void JsNavigationTransitionProxy::FinishTransition(const JSCallbackInfo& info)
{
    if (proxy_) {
        proxy_->FireFinishCallback();
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

JSRef<JSVal> JsNavigationTransitionProxy::ConvertContentInfo(NG::NavContentInfo info)
{
    auto value = JSRef<JSObject>::New();
    if (info.index == -1) {
        // current nav content is navBar.Don't need to set name and mode.
        value->SetProperty<int32_t>("index", -1);
    } else {
        value->SetProperty<std::string>("name", info.name);
        value->SetProperty<int32_t>("index", info.index);
        value->SetProperty<int32_t>("mode", static_cast<int32_t>(info.mode));
    }
    return value;
}

void JsNavigationFunction::JSBind(BindingTarget globalObj)
{
    JsNavigationTransitionProxy::JSBind(globalObj);
}

JSRef<JSVal> JsNavigationFunction::Execute(
    NG::NavContentInfo from, NG::NavContentInfo to, NG::NavigationOperation navigationOperation)
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
}; // namespace OHOS::Ace::Framework