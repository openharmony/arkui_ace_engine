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

#include "base/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int PARAM_ARR_LENGTH_1 = 1;
constexpr uint32_t INDEX_FRAME_NODE_0 = 0;
constexpr uint32_t INDEX_ARGUMENT_1 = 1;
constexpr uint32_t INDEX_ARGUMENT_2 = 2;
constexpr uint32_t INDEX_ARGUMENT_3 = 3;
constexpr uint32_t INDEX_ARGUMENT_4 = 4;
const char* TOGGLE_NODEPTR_OF_UINODE = "nodePtr_";
panda::Local<panda::JSValueRef> JsToggleChangeCallback(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    auto vm = runtimeCallInfo->GetVM();
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    if (argc != 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsBoolean()) {
        return panda::JSValueRef::Undefined(vm);
    }
    bool value = firstArg->ToBoolean(vm)->Value();
    auto ref = runtimeCallInfo->GetThisRef();
    auto obj = ref->ToObject(vm);
    if (obj->GetNativePointerFieldCount(vm) < 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = static_cast<FrameNode*>(obj->GetNativePointerField(vm, 0));
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ToggleModelNG::SetChangeValue(frameNode, value);
    return panda::JSValueRef::Undefined(vm);
}

void SetHeightInner(const EcmaVM* vm, const Local<JSValueRef>& nodeArg, const Local<JSValueRef>& heightArg)
{
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CalcDimension height;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, heightArg, height)) {
        GetArkUINodeModifiers()->getToggleModifier()->resetToggleHeight(nativeNode);
    } else {
        if (height.IsNegative()) {
            GetArkUINodeModifiers()->getToggleModifier()->resetToggleHeight(nativeNode);
        } else {
            GetArkUINodeModifiers()->getToggleModifier()->setToggleHeight(
                nativeNode, height.Value(), static_cast<int32_t>(height.Unit()));
        }
    }
}

void PushDimensionVector(const std::optional<Dimension>& valueDimen, std::vector<ArkUI_Float32>& dimensions)
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
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<ArkUI_Float32>& fontSizesVector, int32_t argIndex)
{
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(argIndex);
    std::optional<CalcDimension> dimensionOptional = std::nullopt;
    CalcDimension parsedDimension;
    if (ArkTSUtils::ParseJsDimensionVp(vm, arg, parsedDimension)) {
        dimensionOptional = parsedDimension;
    }
    PushDimensionVector(dimensionOptional, fontSizesVector);
}

void PutToggleDimensionParameters(
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<ArkUI_Float32>& lengthVector)
{
    std::vector<int32_t> indexVector = { INDEX_ARGUMENT_1, INDEX_ARGUMENT_2, INDEX_ARGUMENT_3, INDEX_ARGUMENT_4 };
    for (size_t index = 0; index < indexVector.size(); index++) {
        PushToggleDimension(runtimeCallInfo, vm, lengthVector, indexVector[index]);
    }
}
} // namespace

ArkUINativeModuleValue ToggleBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    if (!secondArg->IsObject(vm)) {
        ToggleModelNG::SetBuilderFunc(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> obj(vm, secondArg);
    auto containerId = Container::CurrentId();
    ToggleModelNG::SetBuilderFunc(frameNode, [vm, frameNode, obj = std::move(obj), containerId](
                                  ToggleConfiguration config) -> RefPtr<FrameNode> {
        ContainerScope scope(containerId);
        auto context = ArkTSUtils::GetContext(vm);
        CHECK_EQUAL_RETURN(context->IsUndefined(), true, nullptr);
        const char* keysOfToggle[] = { "isOn", "enabled", "triggerChange"};
            Local<JSValueRef> valuesOfToggle[] = { panda::BooleanRef::New(vm, config.isOn_),
                panda::BooleanRef::New(vm, config.enabled_),
                panda::FunctionRef::New(vm, JsToggleChangeCallback)};
        auto toggle = panda::ObjectRef::NewWithNamedProperties(vm,
            ArraySize(keysOfToggle), keysOfToggle, valuesOfToggle);
        toggle->SetNativePointerFieldCount(vm, 1);
        toggle->SetNativePointerField(vm, 0, static_cast<void*>(frameNode));
        panda::Local<panda::JSValueRef> params[INDEX_ARGUMENT_2] = { context, toggle };
        LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto jsObject = obj.ToLocal();
        auto makeFunc = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
        CHECK_EQUAL_RETURN(makeFunc->IsFunction(vm), false, nullptr);
        panda::Local<panda::FunctionRef> func = makeFunc;
        auto result = func->Call(vm, jsObject, params, 2);
        JSNApi::ExecutePendingJob(vm);
        CHECK_EQUAL_RETURN(result.IsEmpty() || trycatch.HasCaught() || !result->IsObject(vm), true, nullptr);
        auto resultObj = result->ToObject(vm);
        panda::Local<panda::JSValueRef> nodeptr =
            resultObj->Get(vm, panda::StringRef::NewFromUtf8(vm, TOGGLE_NODEPTR_OF_UINODE));
        CHECK_EQUAL_RETURN(nodeptr.IsEmpty() || nodeptr->IsUndefined() || nodeptr->IsNull(), true, nullptr);
        auto* node = nodeptr->ToNativePointer(vm)->Value();
        auto* frameNode = reinterpret_cast<FrameNode*>(node);
        CHECK_NULL_RETURN(frameNode, nullptr);
        return AceType::Claim(frameNode);
    });
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != INDEX_ARGUMENT_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(INDEX_ARGUMENT_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getToggleModifier()->resetToggleOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(bool)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](bool isOnchange) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { panda::BooleanRef::New(vm, isOnchange) };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
    };
    GetArkUINodeModifiers()->getToggleModifier()->setToggleOnChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getToggleModifier()->resetToggleOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (colorArg->IsNull() || colorArg->IsUndefined() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorResObj, nodeInfo)) {
        GetArkUINodeModifiers()->getToggleModifier()->resetToggleSelectedColor(nativeNode);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        GetArkUINodeModifiers()->getToggleModifier()->setToggleSelectedColorPtr(
            nativeNode, color.GetValue(), colorRawPtr);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getToggleModifier()->resetToggleSelectedColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetSwitchPointColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (colorArg->IsNull() || colorArg->IsUndefined() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorResObj, nodeInfo)) {
        GetArkUINodeModifiers()->getToggleModifier()->resetToggleSwitchPointColor(nativeNode);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        GetArkUINodeModifiers()->getToggleModifier()->setToggleSwitchPointColorPtr(
            nativeNode, color.GetValue(), colorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetSwitchPointColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getToggleModifier()->resetToggleSwitchPointColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetSwitchStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> pointRadiusArg = runtimeCallInfo->GetCallArgRef(INDEX_ARGUMENT_1);
    Local<JSValueRef> unselectedColorArg = runtimeCallInfo->GetCallArgRef(INDEX_ARGUMENT_2);
    Local<JSValueRef> pointColorArg = runtimeCallInfo->GetCallArgRef(INDEX_ARGUMENT_3);
    Local<JSValueRef> trackRadiusArg = runtimeCallInfo->GetCallArgRef(INDEX_ARGUMENT_4);
    SetPointRadius(vm, nativeNode, pointRadiusArg);
    SetUnselectedColor(vm, nativeNode, unselectedColorArg);
    SetPointColor(vm, nativeNode, pointColorArg);
    SetTrackRadius(vm, nativeNode, trackRadiusArg);
    return panda::JSValueRef::Undefined(vm);
}

void ToggleBridge::SetPointRadius(const EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<JSValueRef>& arg)
{
    CHECK_NULL_VOID(vm);
    CalcDimension pointRadius;
    RefPtr<ResourceObject> resObj;
    if (!arg->IsUndefined() && ArkTSUtils::ParseJsDimensionVpNG(vm, arg, pointRadius, resObj) &&
        !pointRadius.IsNegative()) {
        auto pointRadiusRawPtr = AceType::RawPtr(resObj);
        GetArkUINodeModifiers()->getToggleModifier()->setTogglePointRadiusPtr(
            nativeNode, pointRadius.Value(), static_cast<int>(pointRadius.Unit()), pointRadiusRawPtr);
        return;
    }
    GetArkUINodeModifiers()->getToggleModifier()->resetTogglePointRadius(nativeNode);
}

void ToggleBridge::SetUnselectedColor(const EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<JSValueRef>& arg)
{
    CHECK_NULL_VOID(vm);
    Color unselectedColor;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (arg->IsNull() || arg->IsUndefined() || !ArkTSUtils::ParseJsColorAlpha(vm, arg, unselectedColor, resObj,
        nodeInfo)) {
        GetArkUINodeModifiers()->getToggleModifier()->resetToggleUnselectedColor(nativeNode);
        return;
    }
    auto colorRawPtr = AceType::RawPtr(resObj);
    GetArkUINodeModifiers()->getToggleModifier()->setToggleUnselectedColorPtr(
        nativeNode, unselectedColor.GetValue(), colorRawPtr);
}

void ToggleBridge::SetPointColor(const EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<JSValueRef>& arg)
{
    CHECK_NULL_VOID(vm);
    Color pointColor;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (arg->IsNull() || arg->IsUndefined() || !ArkTSUtils::ParseJsColorAlpha(vm, arg, pointColor, resObj, nodeInfo)) {
        GetArkUINodeModifiers()->getToggleModifier()->resetToggleSwitchPointColor(nativeNode);
        return;
    }
    auto colorRawPtr = AceType::RawPtr(resObj);
    GetArkUINodeModifiers()->getToggleModifier()->setToggleSwitchPointColorPtr(
        nativeNode, pointColor.GetValue(), colorRawPtr);
}

void ToggleBridge::SetTrackRadius(const EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<JSValueRef>& arg)
{
    CHECK_NULL_VOID(vm);
    CalcDimension trackRadius;
    RefPtr<ResourceObject> resObj;
    if (!arg->IsUndefined() && ArkTSUtils::ParseJsDimensionVpNG(vm, arg, trackRadius, resObj) &&
        !trackRadius.IsNegative()) {
        auto radiusRawPtr = AceType::RawPtr(resObj);
        GetArkUINodeModifiers()->getToggleModifier()->setToggleTrackBorderRadiusPtr(
            nativeNode, trackRadius.Value(), static_cast<int>(trackRadius.Unit()), radiusRawPtr);
        return;
    }
    GetArkUINodeModifiers()->getToggleModifier()->resetToggleTrackBorderRadius(nativeNode);
}

ArkUINativeModuleValue ToggleBridge::ResetSwitchStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getToggleModifier()->resetTogglePointRadius(nativeNode);
    GetArkUINodeModifiers()->getToggleModifier()->resetToggleUnselectedColor(nativeNode);
    GetArkUINodeModifiers()->getToggleModifier()->resetToggleSwitchPointColor(nativeNode);
    GetArkUINodeModifiers()->getToggleModifier()->resetToggleTrackBorderRadius(nativeNode);
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
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getToggleModifier()->resetToggleHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    Local<JSValueRef> regionArrayArg = runtimeCallInfo->GetCallArgRef(INDEX_ARGUMENT_1);
    Local<JSValueRef> lengthArg = runtimeCallInfo->GetCallArgRef(INDEX_ARGUMENT_2);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    uint32_t length = lengthArg->Uint32Value(vm);
    ArkUI_Float32 regionValueArray[length];
    int32_t regionUnitsArray[length];
    if (!ArkTSUtils::ParseResponseRegion(vm, regionArrayArg, regionValueArray, regionUnitsArray, length)) {
        GetArkUINodeModifiers()->getToggleModifier()->resetToggleResponseRegion(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getToggleModifier()->setToggleResponseRegion(
        nativeNode, regionValueArray, regionUnitsArray, length);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getToggleModifier()->resetToggleResponseRegion(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    std::vector<ArkUI_Float32> lengthVector;
    PutToggleDimensionParameters(runtimeCallInfo, vm, lengthVector);
    GetArkUINodeModifiers()->getToggleModifier()->setTogglePadding(
        nativeNode, lengthVector.data(), lengthVector.size());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getToggleModifier()->resetTogglePadding(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(INDEX_ARGUMENT_1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
        GetArkUINodeModifiers()->getToggleModifier()->resetToggleBackgroundColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getToggleModifier()->setToggleBackgroundColorWithColorSpace(
            nativeNode, color.GetValue(), color.GetColorSpace());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getToggleModifier()->resetToggleBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetHoverEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> hoverEffectArg = runtimeCallInfo->GetCallArgRef(INDEX_ARGUMENT_1);

    if (hoverEffectArg->IsUndefined() || !hoverEffectArg->IsNumber()) {
        GetArkUINodeModifiers()->getToggleModifier()->resetToggleHoverEffect(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t hoverEffectValue = hoverEffectArg->Int32Value(vm);
    GetArkUINodeModifiers()->getToggleModifier()->setToggleHoverEffect(nativeNode, hoverEffectValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetHoverEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getToggleModifier()->resetToggleHoverEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetToggleOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    CHECK_EQUAL_RETURN(nodeArg.IsEmpty(), true, panda::JSValueRef::Undefined(vm));
    auto pointer = nodeArg->ToNativePointer(vm);
    CHECK_EQUAL_RETURN(pointer.IsEmpty(), true, panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(pointer->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> isOnArg = runtimeCallInfo->GetCallArgRef(INDEX_ARGUMENT_1);
    CHECK_EQUAL_RETURN(isOnArg.IsEmpty(), true, panda::JSValueRef::Undefined(vm));
    bool isOn = false;
    if (!isOnArg->IsUndefined() && isOnArg->IsBoolean()) {
        isOn = isOnArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getToggleModifier()->setToggleState(nativeNode, isOn);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ParseParams(ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUI_Params& params)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    CHECK_EQUAL_RETURN(params.nodeType != ARKUI_TOGGLE, true, panda::JSValueRef::Undefined(vm));
    ArkUI_Toggle_Params* toggleParams = (ArkUI_Toggle_Params*)(&params);
    toggleParams->toggleType = ToggleType::SWITCH;
    toggleParams->isOn = false;
    CHECK_EQUAL_RETURN(runtimeCallInfo->GetArgsNumber() != INDEX_ARGUMENT_3, true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> paramsArg = runtimeCallInfo->GetCallArgRef(INDEX_ARGUMENT_2);
    if (!paramsArg->IsNull() && paramsArg->IsObject(vm)) {
        auto obj = Local<panda::ObjectRef>(paramsArg);
        auto typeStr = panda::StringRef::NewFromUtf8(vm, "type");
        auto isOnStr = panda::StringRef::NewFromUtf8(vm, "isOn");
        auto typeArg = obj->Get(vm, typeStr);
        auto isOnArg = obj->Get(vm, isOnStr);
        CHECK_EQUAL_RETURN(typeArg.IsEmpty(), true, panda::JSValueRef::Undefined(vm));
        CHECK_EQUAL_RETURN(isOnArg.IsEmpty(), true, panda::JSValueRef::Undefined(vm));
        if (!typeArg->IsNull() && !typeArg->IsUndefined() && typeArg->IsNumber()) {
            toggleParams->toggleType = static_cast<ToggleType>(typeArg->Int32Value(vm));
        }
        if (!isOnArg->IsNull() && !isOnArg->IsUndefined() && isOnArg->IsBoolean()) {
            toggleParams->isOn = isOnArg->ToBoolean(vm)->Value();
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(INDEX_FRAME_NODE_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    ArkUISizeType top = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    ArkUISizeType right = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    ArkUISizeType bottom = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    ArkUISizeType left = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    bool isLengthMetrics = ArkTSUtils::ParseMargin(runtimeCallInfo, top, right, bottom, left);
    if (isLengthMetrics) {
        auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
        GetArkUINodeModifiers()->getToggleModifier()->setToggleMargin(
            nativeNode, &top, isRightToLeft ? &left : &right, &bottom, isRightToLeft ? &right : &left);
    } else {
        GetArkUINodeModifiers()->getToggleModifier()->setToggleMargin(nativeNode, &top, &right, &bottom, &left);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getToggleModifier()->resetToggleMargin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
