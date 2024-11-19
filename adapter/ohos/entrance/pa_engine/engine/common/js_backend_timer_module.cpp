/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "js_backend_timer_module.h"

#include "base/log/log.h"
#include "js_runtime_utils.h"

#ifdef SUPPORT_GRAPHICS
#include "core/common/container_scope.h"
#endif
#ifdef ENABLE_HITRACE
#include "hitrace/trace.h"
#endif

#ifdef SUPPORT_GRAPHICS
using OHOS::Ace::ContainerScope;
#endif

namespace OHOS::Ace {
namespace {
std::atomic<uint32_t> g_callbackId(1);
constexpr size_t ARGC_MIN = 2;

class TraceIdScope final {
public:
    explicit TraceIdScope(const OHOS::HiviewDFX::HiTraceId& traceId) : valid_(traceId.IsValid())
    {
        if (valid_) {
            OHOS::HiviewDFX::HiTraceChain::SetId(traceId);
        }
    }

    ~TraceIdScope()
    {
        if (valid_) {
            OHOS::HiviewDFX::HiTraceChain::ClearId();
        }
    }

    TraceIdScope(const TraceIdScope&) = delete;
    TraceIdScope(TraceIdScope&&) = delete;
    TraceIdScope& operator=(const TraceIdScope&) = delete;
    TraceIdScope& operator=(TraceIdScope&&) = delete;

private:
    bool valid_ = false;
};

class JsTimer final {
public:
    JsTimer(AbilityRuntime::JsRuntime& jsRuntime, const std::shared_ptr<NativeReference>& jsFunction,
        const std::string& name, int64_t interval, bool isInterval)
        : jsRuntime_(jsRuntime), jsFunction_(jsFunction), name_(name), interval_(interval), isInterval_(isInterval)
    {}

    ~JsTimer() = default;

    void operator()() const
    {
        if (isInterval_) {
            jsRuntime_.PostTask(*this, name_, interval_);
        }
#ifdef SUPPORT_GRAPHICS
        // call js function
        ContainerScope containerScope(containerScopeId_);
#endif
        AbilityRuntime::HandleScope handleScope(jsRuntime_);

        std::vector<napi_value> args_;
        args_.reserve(jsArgs_.size());
        for (auto arg : jsArgs_) {
            args_.emplace_back(arg->GetNapiValue());
        }

#ifdef ENABLE_HITRACE
        TraceIdScope traceIdScope(traceId_);
#endif
        NativeEngine* engine = jsRuntime_.GetNativeEnginePointer();
        auto env = reinterpret_cast<napi_env>(engine);
        napi_value result = nullptr;
        napi_value recv = nullptr;
        napi_get_undefined(env, &recv);
        napi_call_function(env, recv, jsFunction_->GetNapiValue(), args_.size(), args_.data(), &result);
        if (engine->HasPendingException()) {
            LOGE("Pending exception after CallFUnction in JsTimer. Handle uncaught exception here.");
            engine->HandleUncaughtException();
        }
    }

    void PushArgs(const std::shared_ptr<NativeReference>& ref)
    {
        jsArgs_.emplace_back(ref);
    }

private:
    AbilityRuntime::JsRuntime& jsRuntime_;
    std::shared_ptr<NativeReference> jsFunction_;
    std::vector<std::shared_ptr<NativeReference>> jsArgs_;
    std::string name_;
    int64_t interval_ = 0;
    bool isInterval_ = false;
#ifdef SUPPORT_GRAPHICS
    int32_t containerScopeId_ = ContainerScope::CurrentId();
#endif
#ifdef ENABLE_HITRACE
    OHOS::HiviewDFX::HiTraceId traceId_ = OHOS::HiviewDFX::HiTraceChain::GetId();
#endif
};

napi_value StartTimeoutOrInterval(napi_env env, napi_callback_info info, bool isInterval)
{
    napi_value result = nullptr;
    napi_get_undefined(env, &result);
    if (env == nullptr || info == nullptr) {
        LOGE("StartTimeoutOrInterval, engine or callback info is nullptr.");
        return result;
    }

    size_t argc = 0;
    napi_value* argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr);
    if (argc < ARGC_MIN) {
        LOGE("Additional or equal to 2 are required for participation");
        return result;
    }
    argv = new napi_value[argc];
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);

    if (!AbilityRuntime::CheckTypeForNapiValue(env, argv[0], napi_function)) {
        LOGE("first param is not napi_function");
        delete[] argv;
        return result;
    }
    if (!AbilityRuntime::CheckTypeForNapiValue(env, argv[1], napi_number)) {
        LOGE("second param is not napi_number");
        delete[] argv;
        return result;
    }

    napi_ref ref = nullptr;
    std::shared_ptr<NativeReference> jsFunction;
    napi_create_reference(env, argv[0], 1, &ref);
    jsFunction.reset(reinterpret_cast<NativeReference*>(ref));
    int64_t delayTime = 0;
    napi_get_value_int64(env, argv[1], &delayTime);

    uint32_t callbackId = g_callbackId.fetch_add(1, std::memory_order_relaxed);
    std::string name = "JsRuntimeTimer_";
    name.append(std::to_string(callbackId));

    AbilityRuntime::JsRuntime& jsRuntime =
        *reinterpret_cast<AbilityRuntime::JsRuntime*>(reinterpret_cast<NativeEngine*>(env)->GetJsEngine());
    JsTimer task(jsRuntime, jsFunction, name, delayTime, isInterval);
    for (size_t index = 2; index < argc; ++index) {
        napi_ref value = nullptr;
        std::shared_ptr<NativeReference> valueRef;
        napi_create_reference(env, argv[index], 1, &value);
        valueRef.reset(reinterpret_cast<NativeReference*>(value));
        task.PushArgs(valueRef);
    }

    jsRuntime.PostTask(task, name, delayTime);
    napi_create_uint32(env, callbackId, &result);
    delete[] argv;
    return result;
}

napi_value StartTimeout(napi_env env, napi_callback_info info)
{
    return StartTimeoutOrInterval(env, info, false);
}

napi_value StartInterval(napi_env env, napi_callback_info info)
{
    return StartTimeoutOrInterval(env, info, true);
}

napi_value StopTimeoutOrInterval(napi_env env, napi_callback_info info)
{
    napi_value result = nullptr;
    if (env == nullptr || info == nullptr) {
        LOGE("Stop timeout or interval failed with engine or callback info is nullptr.");
        return result;
    }

    size_t argc = 1;
    napi_value argv[1] = { nullptr };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);

    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv[0], &valueType);
    if (valueType != napi_number && argc < 1) {
        LOGE("Clear callback timer failed with invalid parameter.");
        return result;
    }

    uint32_t callbackId = 0;
    napi_get_value_uint32(env, argv[0], &callbackId);

    std::string name = "JsRuntimeTimer_";
    name.append(std::to_string(callbackId));

    // event should be cancelable before executed
    AbilityRuntime::JsRuntime& jsRuntime =
        *reinterpret_cast<AbilityRuntime::JsRuntime*>(reinterpret_cast<NativeEngine*>(env)->GetJsEngine());
    jsRuntime.RemoveTask(name);
    return result;
}
} // namespace

void InitTimerModule(napi_env env)
{
    LOGI("InitTimerModule begin.");
    AbilityRuntime::HandleScope handleScope(env);
    napi_value globalObj;
    napi_get_global(env, &globalObj);
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, globalObj, &valueType);
    if (valueType != napi_object) {
        LOGE("global is not NativeObject");
        return;
    }

    const char* moduleName = "JsTimer";
    AbilityRuntime::BindNativeFunction(env, globalObj, "setTimeout", moduleName, StartTimeout);
    AbilityRuntime::BindNativeFunction(env, globalObj, "setInterval", moduleName, StartInterval);
    AbilityRuntime::BindNativeFunction(env, globalObj, "clearTimeout", moduleName, StopTimeoutOrInterval);
    AbilityRuntime::BindNativeFunction(env, globalObj, "clearInterval", moduleName, StopTimeoutOrInterval);
}
} // namespace OHOS::Ace
