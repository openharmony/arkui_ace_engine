/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_canvas_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/canvas/js_drawing_rendering_context.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/canvas/canvas_model_ng.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue CanvasBridge::SetCanvasOnReady(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getCanvasModifier()->resetCanvasOnReady(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    std::function<void(bool, CanvasUnit)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                         bool needDrawingContext, CanvasUnit unit) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        if (!needDrawingContext) {
            func->Call(vm, func.ToLocal(), nullptr, 0);
            return;
        }
        if (!frameNode) {
            return;
        }
        auto pattern = frameNode->GetPattern<NG::CanvasPattern>();
        if (!pattern) {
            return;
        }
        auto jsDrawingContext = Framework::JSClass<Framework::JSDrawingRenderingContext>::NewInstance();
        auto drawingContext = Referenced::Claim(jsDrawingContext->Unwrap<Framework::JSDrawingRenderingContext>());
        drawingContext->SetBuiltIn(true);
        drawingContext->SetInstanceId(Container::CurrentId());
        drawingContext->SetCanvasPattern(pattern);
        drawingContext->SetUnit(unit);
        pattern->SetUpdateContextCallback(
            [drawingContext = drawingContext](CanvasUnit unit) { drawingContext->SetUnit(unit); });
        pattern->SetRSCanvasForDrawingContext();
        std::vector<Local<JSValueRef>> argv;
        argv.emplace_back(jsDrawingContext->GetLocalHandle());
        func->Call(vm, func.ToLocal(), argv.data(), argv.size());
    };
    GetArkUINodeModifiers()->getCanvasModifier()->setCanvasOnReady(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasBridge::ResetCanvasOnReady(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCanvasModifier()->resetCanvasOnReady(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasBridge::SetCanvasEnableAnalyzer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> flagArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (!flagArg->IsBoolean()) {
        GetArkUINodeModifiers()->getCanvasModifier()->resetCanvasEnableAnalyzer(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool flag = flagArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getCanvasModifier()->setCanvasEnableAnalyzer(nativeNode, flag);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasBridge::ResetCanvasEnableAnalyzer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCanvasModifier()->resetCanvasEnableAnalyzer(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
