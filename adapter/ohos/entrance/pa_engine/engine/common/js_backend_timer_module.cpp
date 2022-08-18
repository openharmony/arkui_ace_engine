/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

namespace OHOS::Ace {
namespace {
template<class T>
inline T* ConvertNativeValueTo(NativeValue* value)
{
    return (value != nullptr) ? static_cast<T*>(value->GetInterface(T::INTERFACE_ID)) : nullptr;
}

void BindNativeFunction(NativeEngine& engine, NativeObject& object, const char* name,
    const char* moduleName, NativeCallback func)
{
    std::string fullName(moduleName);
    fullName += ".";
    fullName += name;
    object.SetProperty(name, engine.CreateFunction(fullName.c_str(), fullName.length(), func, nullptr));
}

NativeValue* SetCallbackTimer(NativeEngine& engine, NativeCallbackInfo& info, bool isInterval)
{
    // Parameter check, must have at least 2 params
    if (info.argc < 2 || info.argv[0]->TypeOf() != NATIVE_FUNCTION || info.argv[1]->TypeOf() != NATIVE_NUMBER) {
        LOGE("Set callback timer failed with invalid parameter.");
        return engine.CreateUndefined();
    }

    // Parse parameter
    std::shared_ptr<NativeReference> func(engine.CreateReference(info.argv[0], 1));
    int64_t delayTime = *ConvertNativeValueTo<NativeNumber>(info.argv[1]);
    std::vector<std::shared_ptr<NativeReference>> params;
    for (size_t index = 2; index < info.argc; ++index) {
        params.emplace_back(std::shared_ptr<NativeReference>(engine.CreateReference(info.argv[index], 1)));
    }

    // Get callbackId
    uint32_t callbackId = JsBackendTimerModule::GetInstance()->AddCallBack(func, params, &engine);

    // Post task
    JsBackendTimerModule::GetInstance()->PostTimerCallback(callbackId, delayTime, isInterval, true, &engine);

    return engine.CreateNumber(callbackId);
}

NativeValue* ClearCallbackTimer(NativeEngine& engine, NativeCallbackInfo& info)
{
    // parameter check, must have at least 1 param
    if (info.argc < 1 || info.argv[0]->TypeOf() != NATIVE_NUMBER) {
        LOGE("Clear callback timer failed with invalid parameter.");
        return engine.CreateUndefined();
    }

    uint32_t callbackId = *ConvertNativeValueTo<NativeNumber>(info.argv[0]);
    JsBackendTimerModule::GetInstance()->RemoveTimerCallback(callbackId);
    return engine.CreateUndefined();
}

NativeValue* SetTimeout(NativeEngine* engine, NativeCallbackInfo* info)
{
    if (engine == nullptr || info == nullptr) {
        LOGE("Set timeout failed with engine or callback info is nullptr.");
        return nullptr;
    }

    return SetCallbackTimer(*engine, *info, false);
}

NativeValue* SetInterval(NativeEngine* engine, NativeCallbackInfo* info)
{
    if (engine == nullptr || info == nullptr) {
        LOGE("Set interval failed with engine or callback info is nullptr.");
        return nullptr;
    }

    return SetCallbackTimer(*engine, *info, true);
}

NativeValue* ClearTimeoutOrInterval(NativeEngine* engine, NativeCallbackInfo* info)
{
    if (engine == nullptr || info == nullptr) {
        LOGE("Clear timer failed with engine or callback info is nullptr.");
        return nullptr;
    }

    return ClearCallbackTimer(*engine, *info);
}
} // namespace

void JsBackendTimerModule::TimerCallback(uint32_t callbackId, int64_t delayTime, bool isInterval)
{
    std::shared_ptr<NativeReference> func;
    std::vector<std::shared_ptr<NativeReference>> params;
    NativeEngine* engine = nullptr;
    if (!GetCallBackById(callbackId, func, params, &engine)) {
        return;
    }

    if (!engine) {
        LOGE("engine is nullptr.");
        return;
    }

    std::vector<NativeValue*> argc;
    argc.reserve(params.size());
    for (auto arg : params) {
        argc.emplace_back(arg->Get());
    }

    engine->CallFunction(engine->CreateUndefined(), func->Get(), argc.data(), argc.size());

    if (isInterval) {
        PostTimerCallback(callbackId, delayTime, isInterval, false, engine);
    } else {
        RemoveTimerCallback(callbackId);
    }
}

void JsBackendTimerModule::PostTimerCallback(uint32_t callbackId, int64_t delayTime, bool isInterval, bool isFirst,
    NativeEngine* engine)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!isFirst) {
        auto taskNode = timeoutTaskMap_.find(callbackId);
        if (taskNode == timeoutTaskMap_.end()) {
            LOGE("Post timer callback failed, callbackId %{public}u not found.", callbackId);
            return;
        }
    }

    // CancelableCallback class can only be executed once.
    CancelableCallback<void()> cancelableTimer;
    cancelableTimer.Reset([callbackId, delayTime, isInterval] {
        JsBackendTimerModule::GetInstance()->TimerCallback(callbackId, delayTime, isInterval);
    });
    auto result = timeoutTaskMap_.try_emplace(callbackId, cancelableTimer);
    if (!result.second) {
        result.first->second = cancelableTimer;
    }

    RefPtr<BackendDelegate> delegate = GetDelegateWithoutLock(engine);
    if (delegate) {
        delegate->PostDelayedJsTask(cancelableTimer, delayTime);
    }
}

void JsBackendTimerModule::RemoveTimerCallback(uint32_t callbackId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (callbackNodeMap_.find(callbackId) != callbackNodeMap_.end()) {
        callbackNodeMap_.erase(callbackId);
    }

    auto timeoutNode = timeoutTaskMap_.find(callbackId);
    if (timeoutNode != timeoutTaskMap_.end()) {
        timeoutNode->second.Cancel();
        timeoutTaskMap_.erase(callbackId);
    }
}

uint32_t JsBackendTimerModule::AddCallBack(const std::shared_ptr<NativeReference>& func,
    const std::vector<std::shared_ptr<NativeReference>>& params, NativeEngine* engine)
{
    std::lock_guard<std::mutex> lock(mutex_);
    ++callbackId_;
    callbackNodeMap_[callbackId_].func = func;
    callbackNodeMap_[callbackId_].params = params;
    callbackNodeMap_[callbackId_].engine = engine;
    return callbackId_;
}

bool JsBackendTimerModule::GetCallBackById(uint32_t callbackId, std::shared_ptr<NativeReference>& func,
    std::vector<std::shared_ptr<NativeReference>>& params, NativeEngine** engine)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto taskNode = callbackNodeMap_.find(callbackId);
    if (taskNode == callbackNodeMap_.end()) {
        LOGE("Get callback failed, callbackId %{public}u not found.", callbackId);
        return false;
    }

    func = taskNode->second.func;
    params = taskNode->second.params;
    *engine = taskNode->second.engine;
    return true;
}

JsBackendTimerModule* JsBackendTimerModule::GetInstance()
{
    static JsBackendTimerModule instance;
    return &instance;
}

RefPtr<BackendDelegate> JsBackendTimerModule::GetDelegateWithoutLock(NativeEngine* engine)
{
    auto delegateNode = delegateMap_.find(engine);
    if (delegateNode == delegateMap_.end()) {
        LOGE("Get delegate failed.");
        return nullptr;
    }

    return delegateNode->second;
}

void JsBackendTimerModule::AddDelegate(NativeEngine* engine, const RefPtr<BackendDelegate>& delegate)
{
    std::lock_guard<std::mutex> lock(mutex_);
    delegateMap_[engine] = delegate;
}

void JsBackendTimerModule::InitTimerModule(NativeEngine* engine, const RefPtr<BackendDelegate>& delegate)
{
    if (engine == nullptr || delegate == nullptr) {
        LOGE("InitTimerModule failed with engine or delegate is nullptr.");
        return;
    }

    AddDelegate(engine, delegate);

    NativeObject* globalObject = ConvertNativeValueTo<NativeObject>(engine->GetGlobal());
    if (!globalObject) {
        LOGE("Failed to get global object.");
        return;
    }

    const char *moduleName = "JsBackendTimer";
    BindNativeFunction(*engine, *globalObject, "setTimeout", moduleName, SetTimeout);
    BindNativeFunction(*engine, *globalObject, "setInterval", moduleName, SetInterval);
    BindNativeFunction(*engine, *globalObject, "clearTimeout", moduleName, ClearTimeoutOrInterval);
    BindNativeFunction(*engine, *globalObject, "clearInterval", moduleName, ClearTimeoutOrInterval);
}
} // namespace OHOS::Ace