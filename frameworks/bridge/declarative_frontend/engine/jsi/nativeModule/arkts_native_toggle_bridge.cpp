/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_toggle_bridge.h"

#include "core/interfaces/native/node/api.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t INDEX_FRAME_NODE_0 = 0;
constexpr uint32_t INDEX_ARGUMENT_1 = 1;
constexpr uint32_t INDEX_ARGUMENT_2 = 2;
constexpr uint32_t INDEX_ARGUMENT_3 = 3;
constexpr uint32_t INDEX_ARGUMENT_4 = 4;

void SetHeightInner(const EcmaVM* vm, const Local<JSValueRef>& nodeArg, const Local<JSValueRef>& heightArg)
{
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    CalcDimension height;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, heightArg, height)) {
        GetArkUIInternalNodeAPI()->GetToggleModifier().ResetToggleHeight(nativeNode);
    } else {
        if (height.IsNegative()) {
            GetArkUIInternalNodeAPI()->GetToggleModifier().ResetToggleHeight(nativeNode);
        } else {
            GetArkUIInternalNodeAPI()->GetToggleModifier().SetToggleHeight(
                nativeNode, height.Value(), static_cast<int32_t>(height.Unit()));
        }
    }
}

void PushDimensionVector(const std::optional<Dimension>& valueDimen, std::vector<double>& dimensions)
{
    dimensions.push_back(static_cast<double>(valueDimen.has_value()));
    if (valueDimen.has_value()) {
        dimensions.push_back(static_cast<double>(valueDimen.value().Value()));
        dimensions.push_back(static_cast<double>(valueDimen.value().Unit()));
    } else {
        dimensions.push_back(0);
        dimensions.push_back(0);
    }
}

void PushToggleDimension(
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<double>& fontSizesVector, int32_t argIndex)
{
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(argIndex);
    std::optional<CalcDimension> dimemstionOptinal = std::nullopt;
    CalcDimension parsedDimension;
    if (ArkTSUtils::ParseJsDimensionVp(vm, arg, parsedDimension)) {
        dimemstionOptinal = parsedDimension;
    }
    PushDimensionVector(dimemstionOptinal, fontSizesVector);
}

void PutToggleDimensionParameters(
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<double>& lengthVector)
{
    std::vector<int32_t> indexVector = { INDEX_ARGUMENT_1, INDEX_ARGUMENT_2, INDEX_ARGUMENT_3, INDEX_ARGUMENT_4 };
    for (size_t index = 0; index < indexVector.size(); index++) {
        PushToggleDimension(runtimeCallInfo, vm, lengthVector, indexVector[index]);
    }
}
} // namespace
ArkUINativeModuleValue ToggleBridge::SetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    Color color;
    if (colorArg->IsNull() || colorArg->IsUndefined() || !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
        GetArkUIInternalNodeAPI()->GetToggleModifier().ResetToggleSelectedColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetToggleModifier().SetToggleSelectedColor(nativeNode, color.GetValue());
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetToggleModifier().ResetToggleSelectedColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetSwitchPointColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    Color color;
    if (colorArg->IsNull() || colorArg->IsUndefined() || !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
        GetArkUIInternalNodeAPI()->GetToggleModifier().ResetToggleSwitchPointColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetToggleModifier().SetToggleSwitchPointColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetSwitchPointColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetToggleModifier().ResetToggleSwitchPointColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(INDEX_ARGUMENT_1);
    SetHeightInner(vm, nodeArg, heightArg);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetToggleModifier().ResetToggleHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    Local<JSValueRef> regionArrayArg = runtimeCallInfo->GetCallArgRef(INDEX_ARGUMENT_1);
    Local<JSValueRef> lengthArg = runtimeCallInfo->GetCallArgRef(INDEX_ARGUMENT_2);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    uint32_t length = lengthArg->Uint32Value(vm);
    double regionValueArray[length];
    int32_t regionUnitsArray[length];
    if (!ArkTSUtils::ParseResponseRegion(vm, regionArrayArg, regionValueArray, regionUnitsArray, length)) {
        GetArkUIInternalNodeAPI()->GetToggleModifier().ResetToggleResponseRegion(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUIInternalNodeAPI()->GetToggleModifier().SetToggleResponseRegion(
        nativeNode, regionValueArray, regionUnitsArray, length);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetToggleModifier().ResetToggleResponseRegion(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    std::vector<double> lengthVector;
    PutToggleDimensionParameters(runtimeCallInfo, vm, lengthVector);
    GetArkUIInternalNodeAPI()->GetToggleModifier().SetTogglePadding(
        nativeNode, lengthVector.data(), lengthVector.size());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetToggleModifier().ResetTogglePadding(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(INDEX_ARGUMENT_1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
        GetArkUIInternalNodeAPI()->GetToggleModifier().ResetToggleBackgroundColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetToggleModifier().SetToggleBackgroundColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetToggleModifier().ResetToggleBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetHoverEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> hoverEffectArg = runtimeCallInfo->GetCallArgRef(INDEX_ARGUMENT_1);

    if (hoverEffectArg->IsUndefined() || !hoverEffectArg->IsNumber()) {
        GetArkUIInternalNodeAPI()->GetToggleModifier().ResetToggleHoverEffect(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t hoverEffectValue = hoverEffectArg->Int32Value(vm);
    GetArkUIInternalNodeAPI()->GetToggleModifier().SetToggleHoverEffect(nativeNode, hoverEffectValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetHoverEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetToggleModifier().ResetToggleHoverEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
