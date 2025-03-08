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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_plugin_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {

ArkUINativeModuleValue PluginBridge::SetSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);   // 0: index of parameter frameNode
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(1);  // 1: index of parameter width
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(2); // 2: index of parameter height
    if (!nodeArg->IsNativePointer(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    CalcDimension width = 0.0_vp;
    CalcDimension height = 0.0_vp;
    if (!(ArkTSUtils::ParseJsDimensionVp(vm, widthArg, width, false)) ||
        !(ArkTSUtils::ParseJsDimensionVp(vm, heightArg, height, false))) {
        auto pluginModifier = GetArkUINodeModifiers()->getPluginModifier();
        CHECK_NULL_RETURN(pluginModifier, panda::JSValueRef::Undefined(vm));
        pluginModifier->resetPluginSize(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }

    auto pluginModifier = GetArkUINodeModifiers()->getPluginModifier();
    CHECK_NULL_RETURN(pluginModifier, panda::JSValueRef::Undefined(vm));
    pluginModifier->setPluginSize(nativeNode, width.Value(), height.Value(),
        static_cast<int32_t>(width.Unit()), static_cast<int32_t>(height.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PluginBridge::SetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(1);
    if (!nodeArg->IsNativePointer(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    CalcDimension width = 0.0_vp;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, widthArg, width)) {
        auto pluginModifier = GetArkUINodeModifiers()->getPluginModifier();
        CHECK_NULL_RETURN(pluginModifier, panda::JSValueRef::Undefined(vm));
        pluginModifier->resetPluginWidth(nativeNode);
    }
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }

    auto pluginModifier = GetArkUINodeModifiers()->getPluginModifier();
    CHECK_NULL_RETURN(pluginModifier, panda::JSValueRef::Undefined(vm));
    pluginModifier->setPluginWidth(nativeNode, width.Value(), static_cast<int32_t>(width.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PluginBridge::SetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(1);
    if (!nodeArg->IsNativePointer(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    CalcDimension height = 0.0_vp;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, heightArg, height)) {
        auto pluginModifier = GetArkUINodeModifiers()->getPluginModifier();
        CHECK_NULL_RETURN(pluginModifier, panda::JSValueRef::Undefined(vm));
        pluginModifier->resetPluginHeight(nativeNode);
    }
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }

    auto pluginModifier = GetArkUINodeModifiers()->getPluginModifier();
    CHECK_NULL_RETURN(pluginModifier, panda::JSValueRef::Undefined(vm));
    pluginModifier->setPluginHeight(nativeNode, height.Value(), static_cast<int32_t>(height.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PluginBridge::ResetSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    if (!nodeArg->IsNativePointer(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto pluginModifier = GetArkUINodeModifiers()->getPluginModifier();
    CHECK_NULL_RETURN(pluginModifier, panda::JSValueRef::Undefined(vm));
    pluginModifier->resetPluginSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PluginBridge::ResetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    if (!nodeArg->IsNativePointer(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto pluginModifier = GetArkUINodeModifiers()->getPluginModifier();
    CHECK_NULL_RETURN(pluginModifier, panda::JSValueRef::Undefined(vm));
    pluginModifier->resetPluginWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PluginBridge::ResetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    if (!nodeArg->IsNativePointer(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto pluginModifier = GetArkUINodeModifiers()->getPluginModifier();
    CHECK_NULL_RETURN(pluginModifier, panda::JSValueRef::Undefined(vm));
    pluginModifier->resetPluginHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG