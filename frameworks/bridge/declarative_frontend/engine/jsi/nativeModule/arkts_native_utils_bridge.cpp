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

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr uint32_t MAX_COLOR_ARRAY_COUNT = 4;
constexpr uint32_t ARRAY_INDEX_RED = 0;
constexpr uint32_t ARRAY_INDEX_GREEN = 1;
constexpr uint32_t ARRAY_INDEX_BLUE = 2;
constexpr uint32_t ARRAY_INDEX_ALPHA = 3;
constexpr uint32_t ARRAY_SIZE = 2;

ArkUINativeModuleValue NativeUtilsBridge::CreateNativeWeakRef(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (firstArg.IsEmpty() || !firstArg->IsNativePointer(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto refPtr = AceType::Claim(reinterpret_cast<AceType*>(firstArg->ToNativePointer(vm)->Value()));
    return NativeUtilsBridge::CreateWeakRef(vm, refPtr);
}

ArkUINativeModuleValue NativeUtilsBridge::CreateWeakRef(EcmaVM* vm, const RefPtr<AceType>& ref)
{
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(ref, panda::JSValueRef::Undefined(vm));
    auto* weak = new NativeWeakRef(AceType::RawPtr(ref));
    auto nativeWeakRef = panda::ObjectRef::New(vm);
    nativeWeakRef->SetNativePointerFieldCount(vm, 1);
    nativeWeakRef->SetConcurrentNativePointerField(vm, 0, weak, &DestructorInterceptor<NativeWeakRef>);
    nativeWeakRef->Set(vm, panda::StringRef::NewFromUtf8(vm, "invalid"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NativeUtilsBridge::WeakRefInvalid));
    nativeWeakRef->Set(vm, panda::StringRef::NewFromUtf8(vm, "getNativeHandle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NativeUtilsBridge::GetNativeHandleForWeak));
    nativeWeakRef->Set(vm, panda::StringRef::NewFromUtf8(vm, "upgrade"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NativeUtilsBridge::Upgrade));
    return nativeWeakRef;
}

ArkUINativeModuleValue NativeUtilsBridge::CreateStrongRef(EcmaVM* vm, const RefPtr<AceType>& ref)
{
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(ref, panda::JSValueRef::Undefined(vm));
    auto* nativeRef = new NativeStrongRef(ref);
    auto nativeStrongRef = panda::ObjectRef::New(vm);
    nativeStrongRef->SetNativePointerFieldCount(vm, 1);
    nativeStrongRef->SetConcurrentNativePointerField(vm, 0, nativeRef, &DestructorInterceptor<NativeStrongRef>);
    nativeStrongRef->Set(vm, panda::StringRef::NewFromUtf8(vm, "getNativeHandle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NativeUtilsBridge::GetNativeHandleForStrong));
    nativeStrongRef->Set(vm, panda::StringRef::NewFromUtf8(vm, "dispose"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NativeUtilsBridge::Dispose));
    return nativeStrongRef;
}

ArkUINativeModuleValue NativeUtilsBridge::CreateNativeStrongRef(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (firstArg.IsEmpty() || !firstArg->IsNativePointer(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto refPtr = AceType::Claim(reinterpret_cast<AceType*>(firstArg->ToNativePointer(vm)->Value()));
    return NativeUtilsBridge::CreateStrongRef(vm, refPtr);
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
        return NativeUtilsBridge::CreateStrongRef(vm, ref);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NativeUtilsBridge::Dispose(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto* ptr = GetPointerField<NativeStrongRef>(runtimeCallInfo);
    if (ptr != nullptr) {
        ptr->strongRef.Reset();
        return panda::JSValueRef::Undefined(vm);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NativeUtilsBridge::ParseResourceColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (firstArg.IsEmpty() || !firstArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Color color;
    if (!ArkTSUtils::ParseJsColorFromResource(vm, firstArg, color)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<panda::ArrayRef> chanels = panda::ArrayRef::New(vm, MAX_COLOR_ARRAY_COUNT);
    panda::ArrayRef::SetValueAt(vm, chanels, ARRAY_INDEX_RED, panda::NumberRef::New(vm, color.GetRed()));
    panda::ArrayRef::SetValueAt(vm, chanels, ARRAY_INDEX_GREEN, panda::NumberRef::New(vm, color.GetGreen()));
    panda::ArrayRef::SetValueAt(vm, chanels, ARRAY_INDEX_BLUE, panda::NumberRef::New(vm, color.GetBlue()));
    panda::ArrayRef::SetValueAt(vm, chanels, ARRAY_INDEX_ALPHA, panda::NumberRef::New(vm, color.GetAlpha()));
    return chanels;
}

ArkUINativeModuleValue NativeUtilsBridge::BlendColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
 
    if (firstArg.IsEmpty() || !firstArg->IsNumber() || secondArg.IsEmpty() || !secondArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }
    Color color;
    Color overlayColor;
    if (!ArkTSUtils::ParseJsColor(vm, firstArg, color) || !ArkTSUtils::ParseJsColor(vm, secondArg, overlayColor)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto blendColor = color.BlendColor(overlayColor);
    Local<panda::ArrayRef> chanels = panda::ArrayRef::New(vm, MAX_COLOR_ARRAY_COUNT);
    panda::ArrayRef::SetValueAt(vm, chanels, ARRAY_INDEX_RED, panda::NumberRef::New(vm, blendColor.GetRed()));
    panda::ArrayRef::SetValueAt(vm, chanels, ARRAY_INDEX_GREEN, panda::NumberRef::New(vm, blendColor.GetGreen()));
    panda::ArrayRef::SetValueAt(vm, chanels, ARRAY_INDEX_BLUE, panda::NumberRef::New(vm, blendColor.GetBlue()));
    panda::ArrayRef::SetValueAt(vm, chanels, ARRAY_INDEX_ALPHA, panda::NumberRef::New(vm, blendColor.GetAlpha()));
    return chanels;
}

ArkUINativeModuleValue NativeUtilsBridge::ResoureToLengthMetrics(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    CalcDimension result;
    ArkTSUtils::ParseJsDimensionFromResourceNG(vm, firstArg, DimensionUnit::VP, result);
    Local<panda::ArrayRef> length = panda::ArrayRef::New(vm, ARRAY_SIZE);
    panda::ArrayRef::SetValueAt(vm, length, 0, panda::NumberRef::New(vm, result.Value()));
    panda::ArrayRef::SetValueAt(vm, length, 1, panda::NumberRef::New(vm, static_cast<int32_t>(result.Unit())));
    return length;
}
} // namespace OHOS::Ace::NG
