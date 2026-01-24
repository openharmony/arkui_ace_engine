/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_navdestination_context.h"

#include "base/log/ace_scoring_log.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_navigation_stack.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/core/components_ng/pattern/navigation/navigation_route.h"

namespace OHOS::Ace::Framework {
JSNavPathInfoScope::JSNavPathInfoScope(const EcmaVM* vm)
{
    if (vm) {
        scope_ = std::make_shared<LocalScope>(vm);
    }
}

napi_value JSNavPathInfo::GetParamObj() const
{
    return JsConverter::ConvertJsValToNapiValue(param_);
}

std::shared_ptr<NG::NavPathInfoScope> JSNavPathInfo::Scope()
{
    return std::make_shared<JSNavPathInfoScope>(param_->GetEcmaVM());
}

void JSNavDestinationContext::GetPathInfo(const JSCallbackInfo& info)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    auto pathInfo = context_->GetNavPathInfo();
    if (!pathInfo) {
        info.SetReturnValue(obj);
        return;
    }
    obj->SetProperty<std::string>("name", pathInfo->GetName());
    obj->SetProperty<bool>("isEntry", pathInfo->GetIsEntry());
    auto jsInfo = AceType::DynamicCast<JSNavPathInfo>(pathInfo);
    JSRef<JSVal> param;
    JSRef<JSVal> onPop;
    if (jsInfo) {
        param = jsInfo->GetParam();
        onPop = jsInfo->GetOnPop();
    }
    if (!param->IsEmpty()) {
        obj->SetPropertyObject("param", param);
    }
    if (!onPop->IsEmpty()) {
        obj->SetPropertyObject("onPop", onPop);
    }
    info.SetReturnValue(obj);
}

void JSNavDestinationContext::SetPathInfo(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navdestination context don't support set path stack");
}

void JSNavDestinationContext::GetPathStack(const JSCallbackInfo& info)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    auto stack = context_->GetNavigationStack().Upgrade();
    if (!stack) {
        info.SetReturnValue(obj);
        return;
    }
    auto jsStack = AceType::DynamicCast<JSNavigationStack>(stack);
    if (!jsStack) {
        info.SetReturnValue(obj);
        return;
    }
    auto navPathStackObj = jsStack->GetDataSourceObj();
    if (navPathStackObj->IsEmpty()) {
        info.SetReturnValue(obj);
        return;
    }
    info.SetReturnValue(navPathStackObj);
}

void JSNavDestinationContext::SetPathStack(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navdestination context not support set path stack");
}

void JSNavDestinationContext::GetRouteInfo(const JSCallbackInfo& info)
{
    auto container = Container::Current();
    auto navigationRoute = container->GetNavigationRoute();
    if (!navigationRoute) {
        return;
    }
    auto param = context_->GetNavPathInfo();
    CHECK_NULL_VOID(param);
    NG::RouteItem routeInfo;
    if (!navigationRoute->GetRouteItem(param->GetName(), routeInfo)) {
        return;
    }
    JSRef<JSObject> routeData = JSRef<JSObject>::New();
    routeData->SetProperty<std::string>("name", param->GetName().c_str());
    routeData->SetProperty<std::string>("pageSourceFile", routeInfo.pageSourceFile->c_str());
    JSRef<JSObject> data = JSRef<JSObject>::New();
    for (auto iter = routeInfo.data.begin(); iter != routeInfo.data.end(); iter++) {
        data->SetProperty<std::string>(iter->first.c_str(), iter->second.c_str());
    }
    routeData->SetPropertyObject("data", data);
    info.SetReturnValue(routeData);
}

void JSNavDestinationContext::SetNavDestinationId(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navdestination context not support set navdestinationId");
}

void JSNavDestinationContext::GetNavDestinationId(const JSCallbackInfo& info)
{
    JSRef<JSString> idStr = JSRef<JSString>::New(std::to_string(context_->GetNavDestinationId()));
    info.SetReturnValue(idStr);
}

void JSNavDestinationContext::SetNavDestinationMode(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navdestination context not support set NavDestinationMode");
}

void JSNavDestinationContext::GetNavDestinationMode(const JSCallbackInfo& info)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWENTY_TWO)) {
        return;
    }
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(static_cast<int8_t>(context_->GetMode()))));
}

void JSNavDestinationContext::JSBind(BindingTarget target)
{
    JSClass<JSNavDestinationContext>::Declare("NavDestinationContext");
    JSClass<JSNavDestinationContext>::CustomProperty("pathInfo", &JSNavDestinationContext::GetPathInfo,
        &JSNavDestinationContext::SetPathInfo);
    JSClass<JSNavDestinationContext>::CustomProperty("pathStack", &JSNavDestinationContext::GetPathStack,
        &JSNavDestinationContext::SetPathStack);
    JSClass<JSNavDestinationContext>::CustomProperty("navDestinationId", &JSNavDestinationContext::GetNavDestinationId,
        &JSNavDestinationContext::SetNavDestinationId);
    JSClass<JSNavDestinationContext>::CustomProperty(
        "mode", &JSNavDestinationContext::GetNavDestinationMode, &JSNavDestinationContext::SetNavDestinationMode);
    JSClass<JSNavDestinationContext>::CustomMethod("getConfigInRouteMap", &JSNavDestinationContext::GetRouteInfo);
    JSClass<JSNavDestinationContext>::Bind(
        target, &JSNavDestinationContext::Constructor, &JSNavDestinationContext::Destructor);
}

void JSNavDestinationContext::Constructor(const JSCallbackInfo& info)
{
    auto proxy = Referenced::MakeRefPtr<JSNavDestinationContext>();
    proxy->IncRefCount();
    info.SetReturnValue(Referenced::RawPtr(proxy));
}

void JSNavDestinationContext::Destructor(JSNavDestinationContext* context)
{
    if (context != nullptr) {
        context->DecRefCount();
    }
}

void JSNavPathInfo::UpdateNavPathInfo(const RefPtr<NG::NavPathInfo>& info)
{
    NG::NavPathInfo::UpdateNavPathInfo(info);
    auto jsPathInfo = AceType::DynamicCast<JSNavPathInfo>(info);
    if (!jsPathInfo) {
        return;
    }
    param_ = jsPathInfo->GetParam();
    onPop_ = jsPathInfo->GetOnPop();
    auto initParam = jsPathInfo->GetInitParam();
    if (!initParam->IsEmpty()) {
        initParam_ = initParam;
    }
}

std::string JSNavPathInfo::GetInitParamString() const
{
    std::string undefinedVal = "undefined";
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, undefinedVal);
    auto env = reinterpret_cast<napi_env>(engine->GetNativeEngine());
    if (!env) {
        return undefinedVal;
    }
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(env, &scope);
    if (scope == nullptr) {
        return undefinedVal;
    }
    napi_value param = JsConverter::ConvertJsValToNapiValue(initParam_);
    napi_value globalValue;
    napi_get_global(env, &globalValue);
    napi_value jsonClass;
    napi_get_named_property(env, globalValue, "JSON", &jsonClass);
    napi_value stringifyFunc;
    napi_get_named_property(env, jsonClass, "stringify", &stringifyFunc);
    napi_value stringifyParam;
    if (napi_call_function(env, jsonClass, stringifyFunc, 1, &param, &stringifyParam) != napi_ok) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "Can not stringify current param!");
        napi_get_and_clear_last_exception(env, &stringifyParam);
        napi_close_handle_scope(env, scope);
        return undefinedVal;
    }
    size_t len = 0;
    napi_get_value_string_utf8(env, stringifyParam, nullptr, 0, &len);
    std::unique_ptr<char[]> paramChar = std::make_unique<char[]>(len + 1);
    napi_get_value_string_utf8(env, stringifyParam, paramChar.get(), len + 1, &len);
    napi_close_handle_scope(env, scope);
    return paramChar.get();
}
} // namespace OHOS::Ace::Framework
