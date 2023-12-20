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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_form_component_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue FormComponentBridge::SetVisibility(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> visibilityArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    int32_t visibility = visibilityArg->Int32Value(vm);
    GetArkUIInternalNodeAPI()->GetFormComponentModifier().SetFormVisibility(nativeNode, visibility);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FormComponentBridge::ResetVisibility(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetFormComponentModifier().ResetFormVisibility(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FormComponentBridge::AllowUpdate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> allowUpdateArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    bool allowUpdate = allowUpdateArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetFormComponentModifier().AllowUpdate(nativeNode, allowUpdate);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FormComponentBridge::DisallowUpdate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetFormComponentModifier().DisallowUpdate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FormComponentBridge::SetDimension(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> dimensionArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    if (dimensionArg->IsNull() || dimensionArg->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetFormComponentModifier().ResetDimension(nativeNode);
    } else {
        int32_t dimension = dimensionArg->Int32Value(vm);
        GetArkUIInternalNodeAPI()->GetFormComponentModifier().SetDimension(nativeNode, dimension);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FormComponentBridge::ResetDimension(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetFormComponentModifier().ResetDimension(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FormComponentBridge::SetModuleName(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> moduleNameArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    if (moduleNameArg->IsNull() || moduleNameArg->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetFormComponentModifier().ResetModuleName(nativeNode);
    } else {
        std::string moduleName = moduleNameArg->ToString(vm)->ToString();
        GetArkUIInternalNodeAPI()->GetFormComponentModifier().SetModuleName(nativeNode, moduleName.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FormComponentBridge::ResetModuleName(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetFormComponentModifier().ResetModuleName(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FormComponentBridge::SetSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> widthValue = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> heightValue = runtimeCallInfo->GetCallArgRef(2);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    CalcDimension width = 0.0_vp;
    CalcDimension height = 0.0_vp;
    bool hasWidth = (!widthValue->IsNull() && !widthValue->IsUndefined() &&
        ArkTSUtils::ParseJsDimensionVp(vm, widthValue, width));
    bool hasHeight = (!heightValue->IsNull() && !heightValue->IsUndefined() &&
        ArkTSUtils::ParseJsDimensionVp(vm, heightValue, height));
    if (!hasWidth && !hasHeight) {
        GetArkUIInternalNodeAPI()->GetFormComponentModifier().ResetFormSize(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetFormComponentModifier().SetFormSize(nativeNode,
            width.Value(), static_cast<int>(width.Unit()), height.Value(), static_cast<int>(height.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FormComponentBridge::ResetSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetFormComponentModifier().ResetFormSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}