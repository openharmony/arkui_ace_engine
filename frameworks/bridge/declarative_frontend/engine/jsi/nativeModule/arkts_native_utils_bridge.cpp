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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_utils_bridge.h"

#include "jsnapi_expo.h"

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {

struct NativeWeakRef {
    NativeWeakRef(AceType* ptr) : rawPtr(ptr)
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

ArkUINativeModuleValue NativeUtilsBridge::CreateNativeWeakRef(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (firstArg.IsEmpty() || !firstArg->IsNativePointer()) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto* weak = new NativeWeakRef(reinterpret_cast<AceType*>(firstArg->ToNativePointer(vm)->Value()));
    auto nativeWeakRef = panda::ObjectRef::New(vm);
    nativeWeakRef->SetNativePointerFieldCount(vm, 1);
    nativeWeakRef->SetNativePointerField(vm, 0, weak, &DestructorInterceptor<NativeWeakRef>);
    nativeWeakRef->Set(vm, panda::StringRef::NewFromUtf8(vm, "invalid"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NativeUtilsBridge::WeakRefInvalid));
    nativeWeakRef->Set(vm, panda::StringRef::NewFromUtf8(vm, "getNativeHandle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NativeUtilsBridge::GetNativeHandle));
    return nativeWeakRef;
}

NativeWeakRef* GetWeakRef(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, nullptr);
    Local<JSValueRef> thisRef = runtimeCallInfo->GetThisRef();
    if (!thisRef->IsObject()) {
        return nullptr;
    }
    Local<panda::ObjectRef> thisObj = thisRef->ToObject(vm);
    auto* weak = reinterpret_cast<NativeWeakRef*>(thisObj->GetNativePointerField(0));
    return weak;
}

ArkUINativeModuleValue NativeUtilsBridge::WeakRefInvalid(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::BooleanRef::New(vm, true));
    auto* weak = GetWeakRef(runtimeCallInfo);
    if (weak != nullptr) {
        return panda::BooleanRef::New(vm, weak->Invalid());
    }
    return panda::BooleanRef::New(vm, true);
}

ArkUINativeModuleValue NativeUtilsBridge::GetNativeHandle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* weak = GetWeakRef(runtimeCallInfo);
    if (weak != nullptr && !weak->Invalid()) {
        return panda::NativePointerRef::New(vm, weak->rawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG
