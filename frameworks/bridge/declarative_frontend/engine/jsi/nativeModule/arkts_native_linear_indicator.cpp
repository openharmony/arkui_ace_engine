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

    CalcDimension space;
    if (ArkTSUtils::ParseJsLengthMetrics(vm, jsSpace, space)) {
        GetArkUINodeModifiers()->getLinearIndicatorModifier()->setLinearIndicatorIndicatorStyleSpace(
            nativeNode, space.Value(), static_cast<int>(space.Unit()));
    } else {
        GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorIndicatorStyleSpace(nativeNode);
    }

    CalcDimension strokeWidth;
    if (ArkTSUtils::ParseJsLengthMetrics(vm, jsStrokeWidth, strokeWidth)) {
        GetArkUINodeModifiers()->getLinearIndicatorModifier()->setLinearIndicatorIndicatorStyleStrokeWidth(
            nativeNode, strokeWidth.Value(), static_cast<int>(strokeWidth.Unit()));
    } else {
        GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorIndicatorStyleStrokeWidth(
            nativeNode);
    }

    CalcDimension strokeRadius;
    if (ArkTSUtils::ParseJsLengthMetrics(vm, jsStrokeRadius, strokeRadius)) {
        GetArkUINodeModifiers()->getLinearIndicatorModifier()->setLinearIndicatorIndicatorStyleStrokeRadius(
            nativeNode, strokeRadius.Value(), static_cast<int>(strokeRadius.Unit()));
    } else {
        GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorIndicatorStyleStrokeRadius(
            nativeNode);
    }
}

void LinearIndicatorBridge::SetIndicatorStyleColor(
    EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<panda::ObjectRef>& obj)
{
    auto jsTrackBackgroundColor = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "trackBackgroundColor"));
    auto jsTrackColor = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "trackColor"));

    Color trackBackgroundColor;
    if (ParseColorMetricsToColor(vm, jsTrackBackgroundColor, trackBackgroundColor)) {
        GetArkUINodeModifiers()->getLinearIndicatorModifier()->setLinearIndicatorIndicatorStyleTrackBackgroundColor(
            nativeNode, trackBackgroundColor.GetValue());
    } else {
        GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorIndicatorStyleTrackBackgroundColor(
            nativeNode);
    }

    Color trackColor;
    if (ParseColorMetricsToColor(vm, jsTrackColor, trackColor)) {
        GetArkUINodeModifiers()->getLinearIndicatorModifier()->setLinearIndicatorIndicatorStyleTrackColor(
            nativeNode, trackColor.GetValue());
    } else {
        GetArkUINodeModifiers()->getLinearIndicatorModifier()->resetLinearIndicatorIndicatorStyleTrackColor(nativeNode);
    }
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

bool LinearIndicatorBridge::ParseColorMetricsToColor(const EcmaVM* vm, const Local<JSValueRef>& jsValue, Color& result)
{
    if (!jsValue->IsObject(vm)) {
        return false;
    }
    auto obj = jsValue->ToObject(vm);
    auto toNumericProp = obj->Get(vm, "toNumeric");
    if (toNumericProp->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = toNumericProp;
        auto colorVal = func->Call(vm, obj, nullptr, 0);
        result.SetValue(colorVal->Uint32Value(vm));
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
