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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_xcomponent_bridge.h"

#include "core/interfaces/native/node/api.h"
#include "bridge/declarative_frontend/jsview/models/indexer_model_impl.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {

ArkUINativeModuleValue XComponentBridge::SetBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetXComponentModifier().ResetXComponentBackgroundColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetXComponentModifier().SetXComponentBackgroundColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetXComponentModifier().ResetXComponentBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetOpacity(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    double opacity;
    if (!ArkTSUtils::ParseJsDouble(vm, secondArg, opacity)) {
        GetArkUIInternalNodeAPI()->GetXComponentModifier().ResetXComponentOpacity(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetXComponentModifier().SetXComponentOpacity(nativeNode, opacity);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetOpacity(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetXComponentModifier().ResetXComponentOpacity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetLinearGradientBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetLinearGradientBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetPixelStretchEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetPixelStretchEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetLightUpEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetLightUpEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetSphericalEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetSphericalEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetColorBlend(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetColorBlend(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetHueRotate(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetHueRotate(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetSepia(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetSepia(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetInvert(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetInvert(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetContrast(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetContrast(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetSaturate(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetSaturate(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBrightness(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetBrightness(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetGrayscale(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetGrayscale(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBackdropBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetBackdropBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBackgroundImagePosition(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetBackgroundImagePosition(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBackgroundImageSize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetBackgroundImageSize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBackgroundImage(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetBackgroundImage(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
