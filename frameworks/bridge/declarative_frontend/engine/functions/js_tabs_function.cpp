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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_tabs_function.h"

namespace OHOS::Ace::Framework {

void JsTabContentTransitionProxy::JSBind(BindingTarget globalObj)
{
    JSClass<JsTabContentTransitionProxy>::Declare("TabContentTransitionProxy");
    JSClass<JsTabContentTransitionProxy>::CustomProperty(
        "from", &JsTabContentTransitionProxy::GetFromIndex, &JsTabContentTransitionProxy::SetFromIndex);
    JSClass<JsTabContentTransitionProxy>::CustomProperty(
        "to", &JsTabContentTransitionProxy::GetToIndex, &JsTabContentTransitionProxy::SetToIndex);
    JSClass<JsTabContentTransitionProxy>::CustomMethod(
        "finishTransition", &JsTabContentTransitionProxy::FinishTransition);
    JSClass<JsTabContentTransitionProxy>::Bind(
        globalObj, &JsTabContentTransitionProxy::Constructor, &JsTabContentTransitionProxy::Destructor);
}

void JsTabContentTransitionProxy::SetFromIndex(const JSCallbackInfo& args)
{
    TAG_LOGD(AceLogTag::ACE_TABS, "TabContentTransitionProxy can not support set from value.");
}

void JsTabContentTransitionProxy::GetFromIndex(const JSCallbackInfo& args)
{
    auto fromIndex = 0;
    if (proxy_) {
        fromIndex = proxy_->GetFromIndex();
    }
    auto fromRef = JSRef<JSVal>::Make(JSVal(ToJSValue(fromIndex)));
    args.SetReturnValue(fromRef);
}

void JsTabContentTransitionProxy::SetToIndex(const JSCallbackInfo& args)
{
    TAG_LOGD(AceLogTag::ACE_TABS, "TabContentTransitionProxy can not support set to value.");
}

void JsTabContentTransitionProxy::GetToIndex(const JSCallbackInfo& args)
{
    auto toIndex = 0;
    if (proxy_) {
        toIndex = proxy_->GetToIndex();
    }
    auto toRef = JSRef<JSVal>::Make(JSVal(ToJSValue(toIndex)));
    args.SetReturnValue(toRef);
}

void JsTabContentTransitionProxy::FinishTransition(const JSCallbackInfo& args)
{
    if (proxy_) {
        proxy_->FinishTransition();
    }
}

void JsTabContentTransitionProxy::Constructor(const JSCallbackInfo& args)
{
    auto proxy = Referenced::MakeRefPtr<JsTabContentTransitionProxy>();
    proxy->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(proxy));
}

void JsTabContentTransitionProxy::Destructor(JsTabContentTransitionProxy* proxy)
{
    if (proxy != nullptr) {
        proxy->DecRefCount();
    }
}

void JsTabsFunction::JSBind(BindingTarget globalObj)
{
    JsTabContentTransitionProxy::JSBind(globalObj);
}

JSRef<JSVal> JsTabsFunction::Execute(int32_t fromIndex, int32_t toIndex)
{
    JSRef<JSVal> from = JSRef<JSVal>::Make(ToJSValue(fromIndex));
    JSRef<JSVal> to = JSRef<JSVal>::Make(ToJSValue(toIndex));

    JSRef<JSVal> params[] = { from, to };
    return JsFunction::ExecuteJS(2, params);
}

void JsTabsFunction::Execute(const RefPtr<TabContentTransitionProxy>& proxy)
{
    JSRef<JSObject> proxyObj = JSClass<JsTabContentTransitionProxy>::NewInstance();
    auto jsProxy = Referenced::Claim(proxyObj->Unwrap<JsTabContentTransitionProxy>());
    jsProxy->SetProxy(proxy);

    JSRef<JSVal> param = JSRef<JSObject>::Cast(proxyObj);
    JsFunction::ExecuteJS(1, &param);
}

} // namespace OHOS::Ace::Framework
