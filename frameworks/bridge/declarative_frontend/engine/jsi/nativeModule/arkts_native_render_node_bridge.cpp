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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_render_node_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue RenderNodeBridge::AppendChild(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* childNativeNode = secondArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().AppendChild(nativeNode, childNativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::InsertChildAfter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* child = secondArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    if (thirdArg.IsNull()) {
        GetArkUIInternalNodeAPI()->GetRenderNodeModifier().InsertChildAfter(nativeNode, child, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    void* sibling = thirdArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().InsertChildAfter(nativeNode, child, sibling);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::RemoveChild(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* childNativeNode = secondArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().RemoveChild(nativeNode, childNativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::ClearChildren(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().ClearChildren(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetClipToFrame(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    bool useClip = false;
    if (secondArg->IsBoolean()) {
        useClip = secondArg->ToBoolean(vm)->Value();
    }
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetClipToFrame(nativeNode, useClip);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetRotation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(3);
    double rotationX = 0.0;
    double rotationY = 0.0;
    double rotationZ = 0.0;
    if (secondArg->IsNumber()) {
        rotationX = secondArg->ToNumber(vm)->Value();
    }
    if (thirdArg->IsNumber()) {
        rotationY = thirdArg->ToNumber(vm)->Value();
    }
    if (fourthArg->IsNumber()) {
        rotationZ = fourthArg->ToNumber(vm)->Value();
    }
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetRotation(nativeNode, rotationX, rotationY, rotationZ);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetShadowColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> color = runtimeCallInfo->GetCallArgRef(1);
    uint32_t colorValue = 0;
    if (color->IsNumber()) {
        colorValue = color->Uint32Value(vm);
    }
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetShadowColor(nativeNode, colorValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetShadowOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    double offsetX = 0.0;
    double offsetY = 0.0;
    if (secondArg->IsNumber()) {
        offsetX = secondArg->ToNumber(vm)->Value();
    }
    if (thirdArg->IsNumber()) {
        offsetY = thirdArg->ToNumber(vm)->Value();
    }
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetShadowOffset(nativeNode, offsetX, offsetY);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RenderNodeBridge::SetShadowAlpha(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> alpha = runtimeCallInfo->GetCallArgRef(1);
    float alphaValue = 1.0;
    if (alpha->IsNumber()) {
        alphaValue = alpha->ToNumber(vm)->Value();
    }
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetShadowAlpha(nativeNode, alphaValue);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RenderNodeBridge::SetShadowElevation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> elevation = runtimeCallInfo->GetCallArgRef(1);
    float elevationValue = 0;
    if (elevation->IsNumber()) {
        elevationValue = elevation->ToNumber(vm)->Value();
    }
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetShadowElevation(nativeNode, elevationValue);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RenderNodeBridge::SetShadowRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> radius = runtimeCallInfo->GetCallArgRef(1);
    float radiusValue = 0;
    if (radius->IsNumber()) {
        radiusValue = radius->ToNumber(vm)->Value();
    }

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetShadowRadius(nativeNode, radiusValue);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
