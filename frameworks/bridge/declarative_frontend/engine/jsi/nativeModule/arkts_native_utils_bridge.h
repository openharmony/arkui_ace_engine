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
void DestructorInterceptor(void* nativePtr, void* data)
{
    auto* typePtr = reinterpret_cast<T*>(nativePtr);
    delete typePtr;
}

template<typename T>
T* GetPointerField(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, nullptr);
    Local<JSValueRef> thisRef = runtimeCallInfo->GetThisRef();
    if (!thisRef->IsObject()) {
        return nullptr;
    }
    Local<panda::ObjectRef> thisObj = thisRef->ToObject(vm);
    auto* pointer = reinterpret_cast<T*>(thisObj->GetNativePointerField(0));
    return pointer;
}

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
};
} // namespace OHOS::Ace::NG

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_UTILS_BRIDGE_H
