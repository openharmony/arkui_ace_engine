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

#include "core/common/dynamic_module.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/tabs/bridge/tabs_transition_proxy_modifier_api.h"

namespace OHOS::Ace::Framework {
constexpr int PARAM_COUNT_FOUR = 4;

const NG::NodeModifier::ArkUITabContentTransitionModifier* GetTransitionProxyModifier()
{
    static const NG::NodeModifier::ArkUITabContentTransitionModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Tabs");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const NG::NodeModifier::ArkUITabContentTransitionModifier*>(
            module->GetCustomModifier("tabsTransitionProxy"));
    }
    return cachedModifier;
}

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
    if (auto* modifier = GetTransitionProxyModifier()) {
        fromIndex = modifier->getFromIndex(proxy_);
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
    if (auto* modifier = GetTransitionProxyModifier()) {
        toIndex = modifier->getToIndex(proxy_);
    }
    auto toRef = JSRef<JSVal>::Make(JSVal(ToJSValue(toIndex)));
    args.SetReturnValue(toRef);
}

void JsTabContentTransitionProxy::FinishTransition(const JSCallbackInfo& args)
{
    if (auto* modifier = GetTransitionProxyModifier()) {
        modifier->finishTransition(proxy_);
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

void JsTabsFunction::Execute(int32_t selectedIndex, int32_t index, float position, float mainAxisLength)
{
    JSRef<JSVal> selectedIndexValue = JSRef<JSVal>::Make(ToJSValue(selectedIndex));
    JSRef<JSVal> indexValue = JSRef<JSVal>::Make(ToJSValue(index));
    JSRef<JSVal> positionValue = JSRef<JSVal>::Make(ToJSValue(position));
    JSRef<JSVal> mainAxisLengthValue = JSRef<JSVal>::Make(ToJSValue(mainAxisLength));

    JSRef<JSVal> params[] = { selectedIndexValue, indexValue, positionValue, mainAxisLengthValue };
    JsFunction::ExecuteJS(PARAM_COUNT_FOUR, params);
}

void JsTabsFunction::Execute(const RefPtr<AceType>& proxy)
{
    JSRef<JSObject> proxyObj = JSClass<JsTabContentTransitionProxy>::NewInstance();
    auto jsProxy = Referenced::Claim(proxyObj->Unwrap<JsTabContentTransitionProxy>());
    jsProxy->SetProxy(proxy);

    JSRef<JSVal> param = JSRef<JSObject>::Cast(proxyObj);
    JsFunction::ExecuteJS(1, &param);
}

} // namespace OHOS::Ace::Framework
