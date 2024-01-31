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
constexpr int32_t ARGC_ONE = 1;
using ErrorCallback = std::function<void(const std::string&, int32_t)>;

struct NavgationAsyncContext {
    napi_env env = nullptr;
    napi_deferred deferred = nullptr;
    std::string pathName;
    JSRef<JSVal> param;
    JSRef<JSObject> navPathInfo;
};

std::string ErrorToMessage(int32_t code)
{
    switch (code) {
        case ERROR_CODE_INTERNAL_ERROR:
            return "Internal error.";
        case ERROR_CODE_DESTINATION_NOT_FOUND:
            return "NavDestination not found.";
        case ERROR_CODE_BUILDER_FUNCTION_NOT_REGISTERED:
            return "Builder function not registered.";
        case ERROR_CODE_PARAM_INVALID:
            return "Paramter error.";
        default:
            return "Error code is not supported.";
    }
}

void ProcessPromiseCallback(std::shared_ptr<NavgationAsyncContext> asyncContext, int32_t callbackCode)
{
    CHECK_NULL_VOID(asyncContext);
    CHECK_NULL_VOID(asyncContext->env);
    CHECK_NULL_VOID(asyncContext->deferred);
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(asyncContext->env, &scope);
    if (status != napi_ok) {
        return;
    }
    CHECK_NULL_VOID(scope);
    if (callbackCode == ERROR_CODE_NO_ERROR) {
        napi_value result = nullptr;
        napi_get_undefined(asyncContext->env, &result);
        napi_resolve_deferred(asyncContext->env, asyncContext->deferred, result);
    } else {
        napi_value code = nullptr;
        napi_create_int32(asyncContext->env, callbackCode, &code);

        napi_value msg = nullptr;
        std::string strMsg = ErrorToMessage(callbackCode);
        napi_create_string_utf8(asyncContext->env, strMsg.c_str(), strMsg.length(), &msg);

        napi_value error = nullptr;
        napi_create_error(asyncContext->env, code, msg, &error);
        napi_reject_deferred(asyncContext->env, asyncContext->deferred, error);
    }
    napi_close_handle_scope(asyncContext->env, scope);
}

void ReturnPromise(const JSCallbackInfo& info, napi_value result)
{
    CHECK_NULL_VOID(result);
    auto jsPromise = JsConverter::ConvertNapiValueToJsVal(result);
    if (!jsPromise->IsObject()) {
        return;
    }
    info.SetReturnValue(JSRef<JSObject>::Cast(jsPromise));
}
}

void JSNavPathStack::JSBind(BindingTarget globalObj)
{
    JSClass<JSNavPathStack>::Declare("NativeNavPathStack");
    JSClass<JSNavPathStack>::Method("onStateChanged", &JSNavPathStack::OnStateChanged);
    JSClass<JSNavPathStack>::CustomMethod("onPushDestination", &JSNavPathStack::OnPushDestination);
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

void JSNavPathStack::OnPushDestination(const JSCallbackInfo& info)
{
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);

    auto asyncContext = std::make_shared<NavgationAsyncContext>();
    asyncContext->env = reinterpret_cast<napi_env>(nativeEngine);
    napi_value result = nullptr;
    napi_create_promise(asyncContext->env, &asyncContext->deferred, &result);
    if (info.Length() != ARGC_ONE || !info[0]->IsObject()) {
        ProcessPromiseCallback(asyncContext, ERROR_CODE_INTERNAL_ERROR);
        ReturnPromise(info, result);
        return;
    }
    asyncContext->navPathInfo = JSRef<JSObject>::Cast(info[0]);
    if (!(asyncContext->navPathInfo->GetProperty("name")->IsString())) {
        ProcessPromiseCallback(asyncContext, ERROR_CODE_PARAM_INVALID);
        ReturnPromise(info, result);
        return;
    }

    ContainerScope scope(containerCurrentId_);
    auto context = PipelineContext::GetCurrentContext();
    if (context == nullptr) {
        ProcessPromiseCallback(asyncContext, ERROR_CODE_INTERNAL_ERROR);
        ReturnPromise(info, result);
        return;
    }

    auto asyncTask = [asyncContext, weakStack = WeakClaim(this)]() {
        CHECK_NULL_VOID(asyncContext);
        auto stack = weakStack.Upgrade();
        if (stack == nullptr || stack->checkNavDestinationExistsFunc_ == nullptr) {
            ProcessPromiseCallback(asyncContext, ERROR_CODE_INTERNAL_ERROR);
            return;
        }
        auto errorCode = stack->checkNavDestinationExistsFunc_(asyncContext->navPathInfo);
        ProcessPromiseCallback(asyncContext, errorCode);
    };

    context->PostAsyncEvent(asyncTask, TaskExecutor::TaskType::JS);
    ReturnPromise(info, result);
}
} // namespace OHOS::Ace::Framework
