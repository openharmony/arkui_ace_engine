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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_UTILS_BRIDGE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_UTILS_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_ref_manager.h"

namespace OHOS::Ace::NG {
struct NativeWeakRef {
    explicit NativeWeakRef(AceType* ptr) : rawPtr(ptr)
    {
        weakRef = AceType::WeakClaim(ptr);
    }

    bool Invalid() const
    {
        return weakRef.Invalid();
    }

    AceType* rawPtr = nullptr;
    WeakPtr<AceType> weakRef;
};

struct NativeStrongRef {
    explicit NativeStrongRef(const RefPtr<AceType>& ref) : strongRef(ref) {}

    AceType* RawPtr() const
    {
        return AceType::RawPtr(strongRef);
    }

    RefPtr<AceType> strongRef;
};

template<typename T>
void DestructorInterceptor(void* env, void* nativePtr, void* data)
{
    auto* typePtr = reinterpret_cast<T*>(nativePtr);
    NativeRefManager::GetInstance().PostDestructorInterceptorTask([typePtr]() { delete typePtr; });
}

template<typename T>
T* GetPointerField(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, nullptr);
    Local<JSValueRef> thisRef = runtimeCallInfo->GetThisRef();
    if (!thisRef->IsObject(vm)) {
        return nullptr;
    }
    Local<panda::ObjectRef> thisObj = thisRef->ToObject(vm);
    auto* pointer = reinterpret_cast<T*>(thisObj->GetNativePointerField(vm, 0));
    return pointer;
}

template<typename T>
class JsWeak {
public:
    JsWeak() {}
    ~JsWeak()
    {
        value_.Reset();
    }

    JsWeak(const JsWeak<T>& rhs) : value_(rhs.value_)
    {
        value_.SetWeakCallback(this, Reset, nullptr);
    }

    JsWeak(JsWeak<T>&& rhs) : value_(std::move(rhs.value_))
    {
        value_.SetWeakCallback(this, Reset, nullptr);
        rhs.value_.Reset();
    }

    explicit JsWeak(const T& rhs) : value_(rhs)
    {
        value_.SetWeakCallback(this, Reset, nullptr);
    }

    JsWeak<T>& operator=(const JsWeak<T>& rhs)
    {
        value_.Reset();
        value_ = rhs.value_;
        value_.SetWeakCallback(this, Reset, nullptr);
        return *this;
    }

    JsWeak<T>& operator=(const T& rhs)
    {
        value_ = rhs;
        value_.SetWeakCallback(this, Reset, nullptr);
        return *this;
    }

    JsWeak<T>& operator=(JsWeak<T>&& rhs)
    {
        value_.Reset();
        value_ = std::move(rhs.value_);
        value_.SetWeakCallback(this, Reset, nullptr);

        rhs.value_.Reset();
        return *this;
    }

    bool IsEmpty() const
    {
        return value_.IsEmpty();
    }

    void Reset()
    {
        value_.Reset();
    }

    T Lock() const
    {
        return T(value_);
    }

    static void Reset(void* ref)
    {
        auto that = reinterpret_cast<JsWeak<T>*>(ref);
        that->Reset();
    }

private:
    T value_;
};


template<typename T>
class JSFuncObjRef {
public:
    ~JSFuncObjRef()
    {
        jsStrongObj.Reset();
    }
    explicit JSFuncObjRef(const T& jsObject, bool isWeak = false) : isWeak_(isWeak)
    {
        if (isWeak) {
            jsWeakObj = JsWeak(jsObject);
        } else {
            jsStrongObj = jsObject;
        }
    }
    T Lock() const
    {
        return isWeak_ ? jsWeakObj.Lock() : jsStrongObj;
    }

private:
    bool isWeak_ = false;
    JsWeak<T> jsWeakObj;
    T jsStrongObj;
};

class NativeUtilsBridge {
public:
    static ArkUINativeModuleValue CreateNativeWeakRef(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue CreateNativeStrongRef(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue WeakRefInvalid(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetNativeHandleForWeak(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetNativeHandleForStrong(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Upgrade(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Dispose(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue CreateStrongRef(EcmaVM* vm, const RefPtr<AceType>& ref);
    static ArkUINativeModuleValue ParseResourceColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue BlendColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResoureToLengthMetrics(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue CreateWeakRef(EcmaVM* vm, const RefPtr<AceType>& ref);
};
} // namespace OHOS::Ace::NG

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_UTILS_BRIDGE_H
