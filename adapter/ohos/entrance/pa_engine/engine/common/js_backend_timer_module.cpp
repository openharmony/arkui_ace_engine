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

#include <atomic>
#include <string>
#include <vector>

#include "hilog_wrapper.h"
#include "js_runtime.h"
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
        const std::string &name, int64_t interval, bool isInterval)
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

        std::vector<NativeValue*> args_;
        args_.reserve(jsArgs_.size());
        for (auto arg : jsArgs_) {
            args_.emplace_back(arg->Get());
        }

#ifdef ENABLE_HITRACE
        TraceIdScope traceIdScope(traceId_);
#endif
        NativeEngine& engine = jsRuntime_.GetNativeEngine();
        engine.CallFunction(engine.CreateUndefined(), jsFunction_->Get(), args_.data(), args_.size());
        if (engine.HasPendingException()) {
            HILOG_ERROR("Pending exception after CallFUnction in JsTimer. Handle uncaught exception here.");
            engine.HandleUncaughtException();
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

NativeValue* StartTimeoutOrInterval(NativeEngine* engine, NativeCallbackInfo* info, bool isInterval)
{
    if (engine == nullptr || info == nullptr) {
        HILOG_ERROR("StartTimeoutOrInterval, engine or callback info is nullptr.");
        return nullptr;
    }

    // parameter check, must have at least 2 params
    if (info->argc < 2 || info->argv[0]->TypeOf() != NATIVE_FUNCTION || info->argv[1]->TypeOf() != NATIVE_NUMBER) {
        HILOG_ERROR("Set callback timer failed with invalid parameter.");
        return engine->CreateUndefined();
    }

    // parse parameter
    std::shared_ptr<NativeReference> jsFunction(engine->CreateReference(info->argv[0], 1));
    int64_t delayTime = *AbilityRuntime::ConvertNativeValueTo<NativeNumber>(info->argv[1]);
    uint32_t callbackId = g_callbackId.fetch_add(1, std::memory_order_relaxed);
    std::string name = "JsRuntimeTimer_";
    name.append(std::to_string(callbackId));

    // create timer task
    AbilityRuntime::JsRuntime& jsRuntime = *reinterpret_cast<AbilityRuntime::JsRuntime*>(engine->GetJsEngine());
    JsTimer task(jsRuntime, jsFunction, name, delayTime, isInterval);
    for (size_t index = 2; index < info->argc; ++index) {
        task.PushArgs(std::shared_ptr<NativeReference>(engine->CreateReference(info->argv[index], 1)));
    }

    jsRuntime.PostTask(task, name, delayTime);
    return engine->CreateNumber(callbackId);
}

NativeValue* StartTimeout(NativeEngine* engine, NativeCallbackInfo* info)
{
    return StartTimeoutOrInterval(engine, info, false);
}

NativeValue* StartInterval(NativeEngine* engine, NativeCallbackInfo* info)
{
    return StartTimeoutOrInterval(engine, info, true);
}

NativeValue* StopTimeoutOrInterval(NativeEngine* engine, NativeCallbackInfo* info)
{
    if (engine == nullptr || info == nullptr) {
        HILOG_ERROR("Stop timeout or interval failed with engine or callback info is nullptr.");
        return nullptr;
    }

    // parameter check, must have at least 1 param
    if (info->argc < 1 || info->argv[0]->TypeOf() != NATIVE_NUMBER) {
        HILOG_ERROR("Clear callback timer failed with invalid parameter.");
        return engine->CreateUndefined();
    }

    uint32_t callbackId = *AbilityRuntime::ConvertNativeValueTo<NativeNumber>(info->argv[0]);
    std::string name = "JsRuntimeTimer_";
    name.append(std::to_string(callbackId));

    // event should be cancelable before executed
    AbilityRuntime::JsRuntime& jsRuntime = *reinterpret_cast<AbilityRuntime::JsRuntime*>(engine->GetJsEngine());
    jsRuntime.RemoveTask(name);
    return engine->CreateUndefined();
}
}

void InitTimerModule(NativeEngine& engine)
{
    HILOG_INFO("InitTimerModule begin.");
    AbilityRuntime::HandleScope handleScope(engine);
    NativeObject* globalObj = AbilityRuntime::ConvertNativeValueTo<NativeObject>(engine.GetGlobal());
    if (globalObj == nullptr) {
        HILOG_ERROR("Global object is invalid.");
        return;
    }

    const char *moduleName = "JsTimer";
    AbilityRuntime::BindNativeFunction(engine, *globalObj, "setTimeout", moduleName, StartTimeout);
    AbilityRuntime::BindNativeFunction(engine, *globalObj, "setInterval", moduleName, StartInterval);
    AbilityRuntime::BindNativeFunction(engine, *globalObj, "clearTimeout", moduleName, StopTimeoutOrInterval);
    AbilityRuntime::BindNativeFunction(engine, *globalObj, "clearInterval", moduleName, StopTimeoutOrInterval);
}
} // namespace OHOS::Ace
