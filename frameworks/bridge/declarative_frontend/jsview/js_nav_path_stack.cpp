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

#include "bridge/declarative_frontend/jsview/js_nav_path_stack.h"

#include "base/log/ace_scoring_log.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "interfaces/napi/kits/utils/napi_utils.h"

namespace OHOS::Ace::Framework {
namespace {
constexpr char JS_NAV_PATH_STACK_CLASS_NAME[] = "NavPathStack";
constexpr char JS_SET_NATIVESTACK_FUNC[] = "setNativeStack";
}

void JSNavPathStack::JSBind(BindingTarget globalObj)
{
    JSClass<JSNavPathStack>::Declare("NativeNavPathStack");
    JSClass<JSNavPathStack>::Method("onStateChanged", &JSNavPathStack::OnStateChanged);
    JSClass<JSNavPathStack>::CustomMethod("onPopCallback", &JSNavPathStack::OnPopCallback);
    JSClass<JSNavPathStack>::Bind(globalObj, &JSNavPathStack::Constructor, &JSNavPathStack::Destructor);
}

void JSNavPathStack::Constructor(const JSCallbackInfo& info)
{
    auto stack = Referenced::MakeRefPtr<JSNavPathStack>();
    stack->IncRefCount();
    info.SetReturnValue(Referenced::RawPtr(stack));
}

void JSNavPathStack::Destructor(JSNavPathStack* stack)
{
    if (stack != nullptr) {
        stack->DecRefCount();
    }
}

JSRef<JSObject> JSNavPathStack::CreateNewNavPathStackJSObject()
{
    JSRef<JSObject> empty;
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, empty);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, empty);
    auto env = reinterpret_cast<napi_env>(nativeEngine);

    napi_value global;
    napi_status ret = napi_get_global(env, &global);
    if (ret != napi_ok) {
        return empty;
    }
    napi_value constructor;
    ret = napi_get_named_property(env, global, JS_NAV_PATH_STACK_CLASS_NAME, &constructor);
    if (ret != napi_ok) {
        return empty;
    }

    napi_value obj;
    ret = napi_new_instance(env, constructor, 0, nullptr, &obj);
    if (ret != napi_ok) {
        return empty;
    }

    JSRef<JSVal> value = JsConverter::ConvertNapiValueToJsVal(obj);
    if (!value->IsObject()) {
        return empty;
    }

    return JSRef<JSObject>::Cast(value);
}

void JSNavPathStack::SetNativeNavPathStack(JSRef<JSObject> jsStack, JSRef<JSObject> nativeStack)
{
    if (jsStack->IsEmpty() || nativeStack->IsEmpty()) {
        return;
    }

    auto property = jsStack->GetProperty(JS_SET_NATIVESTACK_FUNC);
    if (!property->IsFunction()) {
        return;
    }

    auto setNativeStackFunc = JSRef<JSFunc>::Cast(property);
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Cast(nativeStack);
    setNativeStackFunc->Call(jsStack, 1, params);
}

bool JSNavPathStack::CheckIsValid(JSValueWrapper object)
{
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, false);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, false);
    auto env = reinterpret_cast<napi_env>(nativeEngine);

    napi_value global;
    napi_status ret = napi_get_global(env, &global);
    if (ret != napi_ok) {
        return false;
    }
    napi_value constructor;
    ret = napi_get_named_property(env, global, JS_NAV_PATH_STACK_CLASS_NAME, &constructor);
    if (ret != napi_ok) {
        return false;
    }
    bool isInstance = false;
    ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
    napi_value stack = nativeEngine->ValueToNapiValue(object);
    napi_instanceof(env, stack, constructor, &isInstance);
    return isInstance;
}

void JSNavPathStack::OnPopCallback(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (onPopCallback_) {
        onPopCallback_(info[0]);
    }
}
} // namespace OHOS::Ace::Framework
