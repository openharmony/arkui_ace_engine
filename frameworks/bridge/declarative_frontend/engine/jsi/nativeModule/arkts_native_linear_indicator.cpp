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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_linear_indicator.h"

#include <string>

#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_button_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_request_data.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {

constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;

void LinearIndicatorBridge::SetIndicatorStyleSize(
    EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<panda::ObjectRef>& obj)
{
    auto jsSpace = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "space"));
    auto jsStrokeWidth = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "strokeWidth"));
    auto jsStrokeRadius = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "strokeRadius"));
    ArkUI_Float32 space = .0f;
    if (jsSpace->IsNumber()) {
        space = jsSpace->ToNumber(vm)->Value();
    }
    ArkUI_Float32 strokeWidth = .0f;
    if (jsStrokeWidth->IsNumber()) {
        strokeWidth = jsStrokeWidth->ToNumber(vm)->Value();
    }
    ArkUI_Float32 strokeRadius = .0f;
    if (jsStrokeRadius->IsNumber()) {
        strokeRadius = jsStrokeRadius->ToNumber(vm)->Value();
    }
    GetArkUINodeModifiers()->getLinearIndicatorModifier()->setLinearIndicatorIndicatorStyleSpace(nativeNode, space);
    GetArkUINodeModifiers()->getLinearIndicatorModifier()->setLinearIndicatorIndicatorStyleStrokeWidth(
        nativeNode, strokeWidth);
    GetArkUINodeModifiers()->getLinearIndicatorModifier()->setLinearIndicatorIndicatorStyleStrokeRadius(
        nativeNode, strokeRadius);
}

void LinearIndicatorBridge::SetIndicatorStyleColor(
    EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<panda::ObjectRef>& obj)
{
    auto jsTrackBackgroundColor = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "trackBackgroundColor"));
    auto jsTrackColor = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "trackColor"));
    ArkUI_Uint32 trackBackgroundColor = 0;
    if (jsTrackBackgroundColor->IsNumber()) {
        trackBackgroundColor = jsTrackBackgroundColor->ToNumber(vm)->Value();
    }
    ArkUI_Uint32 trackColor = 0;
    if (jsTrackColor->IsNumber()) {
        trackColor = jsTrackColor->ToNumber(vm)->Value();
    }
    GetArkUINodeModifiers()->getLinearIndicatorModifier()->setLinearIndicatorIndicatorStyleTrackBackgroundColor(
        nativeNode, trackBackgroundColor);
    GetArkUINodeModifiers()->getLinearIndicatorModifier()->setLinearIndicatorIndicatorStyleTrackColor(
        nativeNode, trackColor);
}

ArkUINativeModuleValue LinearIndicatorBridge::SetIndicatorStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsObject(vm)) {
        Local<panda::ObjectRef> obj = secondArg->ToObject(vm);
        SetIndicatorStyleSize(vm, nativeNode, obj);
        SetIndicatorStyleColor(vm, nativeNode, obj);
    } else {
        GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorIndicatorStyleSpace(nativeNode);
        GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorIndicatorStyleStrokeWidth(
            nativeNode);
        GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorIndicatorStyleStrokeRadius(
            nativeNode);
        GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorIndicatorStyleTrackBackgroundColor(
            nativeNode);
        GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorIndicatorStyleTrackColor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LinearIndicatorBridge::ResetIndicatorStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorIndicatorStyleSpace(nativeNode);
    GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorIndicatorStyleStrokeWidth(nativeNode);
    GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorIndicatorStyleStrokeRadius(nativeNode);
    GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorIndicatorStyleTrackBackgroundColor(
        nativeNode);
    GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorIndicatorStyleTrackColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LinearIndicatorBridge::SetIndicatorLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    bool SetIndicatorLoop = true;
    if (secondArg->IsBoolean()) {
        SetIndicatorLoop = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getLinearIndicatorModifier()->setLinearIndicatorIndicatorLoop(
            nativeNode, SetIndicatorLoop);
    } else {
        GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorIndicatorLoop(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LinearIndicatorBridge::ResetIndicatorLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorIndicatorLoop(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LinearIndicatorBridge::SetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int index, float progress)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                                  int index, float progress) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_2] = { panda::NumberRef::New(vm, index),
            panda::NumberRef::New(vm, progress) };
        func->Call(vm, func.ToLocal(), params, NUM_2);
    };
    GetArkUINodeModifiers()->getLinearIndicatorModifier()->setLinearIndicatorOnChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LinearIndicatorBridge::ResetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG