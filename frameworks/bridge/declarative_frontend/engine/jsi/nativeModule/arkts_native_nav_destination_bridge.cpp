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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_nav_destination_bridge.h"

#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
ArkUINativeModuleValue NavDestinationBridge::SetHideTitleBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> hideArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (hideArg->IsUndefined() || !hideArg->IsBoolean()) {
        GetArkUINodeModifiers()->getNavDestinationModifier()->resetHideTitleBar(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool hide = hideArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getNavDestinationModifier()->setHideTitleBar(nativeNode, hide);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::ResetHideTitleBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavDestinationModifier()->resetHideTitleBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::SetBackButtonIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    std::string src;
    auto noPixMap = Framework::JSViewAbstract::ParseJsMedia(info[1], src);

    RefPtr<PixelMap> pixMap = nullptr;
#if defined(PIXEL_MAP_SUPPORTED)
    if (!noPixMap) {
        pixMap = CreatePixelMapFromNapiValue(info[1]);
    }
#endif
    std::string bundleName;
    std::string moduleName;
    
    Framework::JSViewAbstract::GetJsMediaBundleInfo(info[1], bundleName, moduleName);
    NavDestinationModelNG::SetBackButtonIcon(frameNode, src, noPixMap, pixMap);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::ResetBackButtonIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    bool noPixMap = false;
    RefPtr<PixelMap> pixMap = nullptr;
    std::string src;
    NavDestinationModelNG::SetBackButtonIcon(frameNode, src, noPixMap, pixMap);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::SetNavDestinationMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (!info[1]->IsNumber()) {
        // set default back ground color
        GetArkUINodeModifiers()->getNavDestinationModifier()->resetNavDestinationMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto mode = info[1]->ToNumber<int32_t>();
    NavDestinationModelNG::SetNavDestinationMode(frameNode, static_cast<NG::NavDestinationMode>(mode));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::ResetNavDestinationMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavDestinationModifier()->resetNavDestinationMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::SetIgnoreLayoutSafeArea(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::string typeCppStr;
    std::string edgesCppStr;
    if (secondArg->IsString(vm)) {
        typeCppStr = secondArg->ToString(vm)->ToString();
    } else {
        //type system
        typeCppStr = "0";
    }

    if (thirdArg->IsString(vm)) {
        edgesCppStr = thirdArg->ToString(vm)->ToString();
    } else {
        //edge top and bottom
        edgesCppStr = "0|1";
    }
    const char* typeStr = typeCppStr.c_str();
    const char* edgesStr = edgesCppStr.c_str();
    GetArkUINodeModifiers()->getNavDestinationModifier()->setIgnoreLayoutSafeArea(nativeNode, typeStr, edgesStr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::ResetIgnoreLayoutSafeArea(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavDestinationModifier()->resetIgnoreLayoutSafeArea(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
