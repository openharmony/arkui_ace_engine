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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_MOCK_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_MOCK_H

#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/bindings_defines.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_types.h"

namespace OHOS::Ace::Framework {
class JSMock {
public:
    static void JSBind(BindingTarget globalObj);
    static void JSBind(BindingTarget globalObj, const shared_ptr<JsRuntime> runtime,
        const shared_ptr<JsValue> globalPtr);
    static bool PreloadWorkerRequireNative(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& global);
    static bool InitModule(const shared_ptr<JsRuntime>& runtime, shared_ptr<JsValue>& thisObj,
        const std::string& moduleName);
};

class JSMockBaseNode {
public:
    JSMockBaseNode() = default;
    ~JSMockBaseNode() = default;

    static void JSBind(BindingTarget globalObj);
    static void ConstructorCallback(const JSCallbackInfo& info) {}
    static void DestructorCallback(JSMockBaseNode* node) {}
    void FinishUpdateFunc(const JSCallbackInfo& info) {}
    void Create(const JSCallbackInfo& info) {}
    void PostTouchEvent(const JSCallbackInfo& info) {}
    void UpdateStart(const JSCallbackInfo& info) {}
    void UpdateEnd(const JSCallbackInfo& info) {}
    void Dispose(const JSCallbackInfo& info) {}
};

class JSMockViewPU {
public:
    JSMockViewPU() = default;
    ~JSMockViewPU() = default;

    static void JSBind(BindingTarget globalObj, std::string name);
    void Id(const JSCallbackInfo& info) {}
    void UpdateStateVars(const JSCallbackInfo& info) {}
    void AboutToReuseInternal(const JSCallbackInfo& info) {}
    void AboutToRecycleInternal(const JSCallbackInfo& info) {}
    void UpdateDirtyElements(const JSCallbackInfo& info) {}
};

class JSMockScopeUtil {
public:
    JSMockScopeUtil() = default;
    ~JSMockScopeUtil() = default;

    static void JSBind(BindingTarget globalObj);
    static void SyncInstanceId(const JSCallbackInfo& info) {}
    static void RestoreInstanceId(const JSCallbackInfo& info) {}
};

class MockCustomDialogController {
public:
    MockCustomDialogController() = default;
    ~MockCustomDialogController() = default;

    static void JSBind(BindingTarget globalObj);
    void Open(const JSCallbackInfo& info) {}
    void Close(const JSCallbackInfo& info) {}
};

class JSMockNativeCustomSpan {
public:
    JSMockNativeCustomSpan() = default;
    ~JSMockNativeCustomSpan() = default;

    static void JSBind(BindingTarget globalObj);
    void Invalidate(const JSCallbackInfo& info) {}
};

class JSMockLocalStorage {
public:
    JSMockLocalStorage() = default;
    ~JSMockLocalStorage() = default;

    static void JSBind(BindingTarget globalObj);
    Local<JSValueRef> ref(panda::JsiRuntimeCallInfo* runtimeCallInfo);
    Local<JSValueRef> setAndRef(panda::JsiRuntimeCallInfo* runtimeCallInfo);
    Local<JSValueRef> link(panda::JsiRuntimeCallInfo* runtimeCallInfo);
    Local<JSValueRef> setAndLink(panda::JsiRuntimeCallInfo* runtimeCallInfo);
    Local<JSValueRef> prop(panda::JsiRuntimeCallInfo* runtimeCallInfo);
    Local<JSValueRef> setAndProp(panda::JsiRuntimeCallInfo* runtimeCallInfo);
    void has(const JSCallbackInfo& info) {}
    void get(const JSCallbackInfo& info) {}
    void set(const JSCallbackInfo& info) {}
    void setOrCreate(const JSCallbackInfo& info) {}
    void deleteKeys(const JSCallbackInfo& info) {}
    void keys(const JSCallbackInfo& info) {}
    void size(const JSCallbackInfo& info) {}
    void clear(const JSCallbackInfo& info) {}
};

class JSMockAbstractProperty {
public:
    static panda::Local<panda::JSValueRef> get(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
    static panda::Local<panda::JSValueRef> set(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
    static panda::Local<panda::JSValueRef> info(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
};

class JSMockSubAbstractProperty {
public:
    static panda::Local<panda::JSValueRef> get(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
    static panda::Local<panda::JSValueRef> set(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
    static panda::Local<panda::JSValueRef> info(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
    static panda::Local<panda::JSValueRef> aboutToBeDeleted(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
};

class JSMockDecorator {
public:
    // @Entry
    static panda::Local<panda::JSValueRef> RegisterNamedRoute(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
    // V1 Decorator
    static panda::Local<panda::JSValueRef> Observed(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
    static panda::Local<panda::JSValueRef> Track(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
    static panda::Local<panda::JSValueRef> Reusable(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
    // V2 Decorator
    static panda::Local<panda::JSValueRef> ObservedV2(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
    static panda::Local<panda::JSValueRef> Trace(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
    static panda::Local<panda::JSValueRef> Local(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
    static panda::Local<panda::JSValueRef> Param(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
    static panda::Local<panda::JSValueRef> Once(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
    static panda::Local<panda::JSValueRef> Event(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
    static panda::Local<panda::JSValueRef> Computed(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
    static panda::Local<panda::JSValueRef> ReusableV2(panda::JsiRuntimeCallInfo* runtimeCallInfo)
    {
        EcmaVM *vm = runtimeCallInfo->GetVM();
        return panda::JSValueRef::Undefined(vm);
    }
};

class JsMockFunc {
public:
    static shared_ptr<JsValue> CreatFunction(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        auto lamdaFunc = [](const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
            const std::vector<shared_ptr<JsValue>>& argv, int32_t argc) -> shared_ptr<JsValue> {
            return runtime->NewUndefined();
        };
        return runtime->NewFunction(lamdaFunc);
    }
};

class JSMockPersistStorage {
public:
    static shared_ptr<JsValue> persistProp(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> deleteProp(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> persistProps(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> keys(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
};

class JSMockAppStorage {
public:
    static shared_ptr<JsValue> ref(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);
    static shared_ptr<JsValue> setAndRef(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);
    static shared_ptr<JsValue> link(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);
    static shared_ptr<JsValue> setAndLink(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);
    static shared_ptr<JsValue> prop(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);
    static shared_ptr<JsValue> setAndProp(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);
    static shared_ptr<JsValue> has(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> get(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> set(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> info(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> aboutToBeDeleted(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> setOrCreate(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> deleteKeys(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
        static shared_ptr<JsValue> keys(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> clear(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> size(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
};

class JSMockEnvironment {
public:
    static shared_ptr<JsValue> envProp(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> envProps(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> keys(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
};

class JSMockPersistenceV2 {
public:
    static shared_ptr<JsValue> connect(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> globalConnect(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> remove(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> keys(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> save(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> notifyOnError(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> instanceFunc(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);
};

class JSMockAppStorageV2 {
public:
    static shared_ptr<JsValue> connect(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> remove(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> getMemoryKeys(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> instanceFunc(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);
};

class JSMockUIUtils {
public:
    static shared_ptr<JsValue> getTarget(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> makeObserved(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> makeV1Observed(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> enableV2Compatibility(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
    {
        return runtime->NewUndefined();
    }
    static shared_ptr<JsValue> instanceFunc(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_MOCK_H
