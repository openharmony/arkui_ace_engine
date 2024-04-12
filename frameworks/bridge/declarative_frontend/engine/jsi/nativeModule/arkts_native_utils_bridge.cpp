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
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NativeUtilsBridge::GetNativeHandleForWeak));
    nativeWeakRef->Set(vm, panda::StringRef::NewFromUtf8(vm, "upgrade"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NativeUtilsBridge::Upgrade));
    return nativeWeakRef;
}

ArkUINativeModuleValue CreateStrongRef(EcmaVM* vm, const RefPtr<AceType>& ref)
{
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(ref, panda::JSValueRef::Undefined(vm));
    auto* nativeRef = new NativeStrongRef(ref);
    auto nativeStrongRef = panda::ObjectRef::New(vm);
    nativeStrongRef->SetNativePointerFieldCount(vm, 1);
    nativeStrongRef->SetNativePointerField(vm, 0, nativeRef, &DestructorInterceptor<NativeStrongRef>);
    nativeStrongRef->Set(vm, panda::StringRef::NewFromUtf8(vm, "getNativeHandle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NativeUtilsBridge::GetNativeHandleForStrong));
    return nativeStrongRef;
}

ArkUINativeModuleValue NativeUtilsBridge::CreateNativeStrongRef(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (firstArg.IsEmpty() || !firstArg->IsNativePointer()) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto refPtr = AceType::Claim(reinterpret_cast<AceType*>(firstArg->ToNativePointer(vm)->Value()));
    return CreateStrongRef(vm, refPtr);
}

ArkUINativeModuleValue NativeUtilsBridge::WeakRefInvalid(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::BooleanRef::New(vm, true));
    auto* weak = GetPointerField<NativeWeakRef>(runtimeCallInfo);
    if (weak != nullptr) {
        return panda::BooleanRef::New(vm, weak->Invalid());
    }
    return panda::BooleanRef::New(vm, true);
}

ArkUINativeModuleValue NativeUtilsBridge::GetNativeHandleForStrong(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* strong = GetPointerField<NativeStrongRef>(runtimeCallInfo);
    if (strong != nullptr && strong->strongRef) {
        return panda::NativePointerRef::New(vm, strong->RawPtr());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NativeUtilsBridge::GetNativeHandleForWeak(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* weak = GetPointerField<NativeWeakRef>(runtimeCallInfo);
    if (weak != nullptr && !weak->Invalid()) {
        return panda::NativePointerRef::New(vm, weak->rawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NativeUtilsBridge::Upgrade(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* weak = GetPointerField<NativeWeakRef>(runtimeCallInfo);
    if (weak != nullptr) {
        auto ref = weak->weakRef.Upgrade();
        return CreateStrongRef(vm, ref);
    }
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG
