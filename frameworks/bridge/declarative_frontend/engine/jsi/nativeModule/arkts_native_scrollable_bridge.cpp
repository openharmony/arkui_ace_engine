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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_scrollable_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue ScrollableBridge::SetContentClip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto* node = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (info[1]->IsObject()) {
        auto* clipShape = Framework::JSRef<Framework::JSObject>::Cast(info[1])->Unwrap<Framework::JSShapeAbstract>();
        if (clipShape) {
            ScrollableModelNG::SetContentClip(reinterpret_cast<FrameNode*>(node), ContentClipMode::CUSTOM,
                AceType::DynamicCast<ShapeRect>(clipShape->GetBasicShape()));
            return panda::JSValueRef::Undefined(vm);
        }
    } else if (info[1]->IsNumber()) {
        GetArkUINodeModifiers()->getScrollableModifier()->setContentClip(node, info[1]->ToNumber<int32_t>());
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUINodeModifiers()->getScrollableModifier()->resetContentClip(node);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollableBridge::ResetContentClip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto* node = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollableModifier()->resetContentClip(node);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollableBridge::SetEdgeEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> arg_effect = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> arg_edgeEffectOptions = runtimeCallInfo->GetCallArgRef(2);

    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    EdgeEffect effect = EdgeEffect::NONE;
    if (!arg_effect->IsUndefined() && !arg_effect->IsNull()) {
        effect = static_cast<EdgeEffect>(arg_effect->Int32Value(vm));
    }
    if (effect < EdgeEffect::SPRING || effect > EdgeEffect::NONE) {
        effect = EdgeEffect::NONE;
    }

    if (arg_edgeEffectOptions->IsNull() || arg_edgeEffectOptions->IsUndefined()) {
        GetArkUINodeModifiers()->getScrollableModifier()->setEdgeEffect(
            nativeNode, static_cast<int32_t>(effect), false);
    } else {
        GetArkUINodeModifiers()->getScrollableModifier()->setEdgeEffect(
            nativeNode, static_cast<int32_t>(effect), arg_edgeEffectOptions->ToBoolean(vm)->Value());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollableBridge::ResetEdgeEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollableModifier()->resetEdgeEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollableBridge::SetFadingEdge(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> fadingEdgeArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> fadingEdgeLengthArg = runtimeCallInfo->GetCallArgRef(2);
    CHECK_NULL_RETURN(frameNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    CalcDimension fadingEdgeLength = Dimension(32.0f, DimensionUnit::VP); // default value
    if (fadingEdgeArg->IsUndefined() || fadingEdgeArg->IsNull()) {
        GetArkUINodeModifiers()->getScrollableModifier()->resetFadingEdge(nativeNode);
    } else {
        bool fadingEdge = fadingEdgeArg->ToBoolean(vm)->Value();
        if (!fadingEdgeLengthArg->IsUndefined() && !fadingEdgeLengthArg->IsNull() &&
            fadingEdgeLengthArg->IsObject(vm)) {
            ArkTSUtils::ParseJsLengthMetrics(vm, fadingEdgeLengthArg, fadingEdgeLength);
        }
        GetArkUINodeModifiers()->getScrollableModifier()->setFadingEdge(
            nativeNode, fadingEdge, fadingEdgeLength.Value(), static_cast<int32_t>(fadingEdgeLength.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollableBridge::ResetFadingEdge(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollableModifier()->resetFadingEdge(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollableBridge::SetOnReachStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getScrollableModifier()->resetOnReachStartCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(void)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };

    GetArkUINodeModifiers()->getScrollableModifier()->setOnReachStartCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollableBridge::ResetOnReachStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollableModifier()->resetOnReachStartCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollableBridge::SetOnReachEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getScrollableModifier()->resetOnReachEndCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(void)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };

    GetArkUINodeModifiers()->getScrollableModifier()->setOnReachEndCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollableBridge::ResetOnReachEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollableModifier()->resetOnReachEndCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
