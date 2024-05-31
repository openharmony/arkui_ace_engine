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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_relative_container_bridge.h"

#include "base/geometry/calc_dimension.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/pattern/relative_container/relative_container_model_ng.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int POSITION_DIMENSION = 2;

void ParseReferencedId(EcmaVM* vm, int32_t referenceSize,
    const panda::Local<panda::ArrayRef>& array, std::vector<std::string>& referencedIds)
{
    for (int32_t i = 0; i < referenceSize; i++) {
        Local<JSValueRef> referencedId = panda::ArrayRef::GetValueAt(vm, array, i);
        if (referencedId->IsString()) {
            std::string str(referencedId->ToString(vm)->ToString());
            referencedIds.push_back(str);
        }
    }
}
} // namespace

ArkUINativeModuleValue RelativeContainerBridge::SetGuideLine(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> idsArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> directionsArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> positionsArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!idsArg->IsArray(vm) || !directionsArg->IsArray(vm) || !positionsArg->IsArray(vm)) {
        GetArkUINodeModifiers()->getRelativeContainerModifier()->resetGuideline(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<GuidelineInfo> guidelineInfos;
    auto idsArr = panda::Local<panda::ArrayRef>(idsArg);
    auto directionsArr = panda::Local<panda::ArrayRef>(directionsArg);
    auto positionsArr = panda::Local<panda::ArrayRef>(positionsArg);
    int32_t size = idsArr->Length(vm);
    for (int32_t i = 0; i < size; i++) {
        GuidelineInfo info;
        Local<JSValueRef> idVal = panda::ArrayRef::GetValueAt(vm, idsArr, i);
        if (idVal->IsString()) {
            info.id = idVal->ToString(vm)->ToString();
        }
        Local<JSValueRef> directionVal = panda::ArrayRef::GetValueAt(vm, directionsArr, i);
        if (directionVal->IsNumber()) {
            info.direction = static_cast<LineDirection>(directionVal->Int32Value(vm));
        }
        Local<JSValueRef> posStartVal = panda::ArrayRef::GetValueAt(vm,
            positionsArr, i * POSITION_DIMENSION);
        CalcDimension startPos;
        if (ArkTSUtils::ParseJsDimensionVpNG(vm, posStartVal, startPos)) {
            info.start = startPos;
        }
        Local<JSValueRef> posEndVal = panda::ArrayRef::GetValueAt(vm,
            positionsArr, i * POSITION_DIMENSION + 1);
        CalcDimension endPos;
        if (ArkTSUtils::ParseJsDimensionVpNG(vm, posEndVal, endPos)) {
            info.end = endPos;
        }
        guidelineInfos.push_back(info);
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    RelativeContainerModelNG::SetGuideline(frameNode, guidelineInfos);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RelativeContainerBridge::ResetGuideLine(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRelativeContainerModifier()->resetGuideline(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RelativeContainerBridge::SetBarrier(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> idsArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> directionsArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> referenceIdsArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!idsArg->IsArray(vm) || !directionsArg->IsArray(vm) || !referenceIdsArg->IsArray(vm)) {
        GetArkUINodeModifiers()->getRelativeContainerModifier()->resetBarrier(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<BarrierInfo> barrierInfos;
    auto idsArr = panda::Local<panda::ArrayRef>(idsArg);
    auto directionsArr = panda::Local<panda::ArrayRef>(directionsArg);
    auto referenceIdsArr = panda::Local<panda::ArrayRef>(referenceIdsArg);
    int32_t size = idsArr->Length(vm);
    for (int32_t i = 0; i < size; i++) {
        BarrierInfo info;
        Local<JSValueRef> idVal = panda::ArrayRef::GetValueAt(vm, idsArr, i);
        Local<JSValueRef> directionVal = panda::ArrayRef::GetValueAt(vm, directionsArr, i);
        Local<JSValueRef> referencedIdVal = panda::ArrayRef::GetValueAt(vm, referenceIdsArr, i);
        if (idVal->IsString()) {
            info.id = idVal->ToString(vm)->ToString();
        }
        if (directionVal->IsNumber()) {
            info.direction = static_cast<BarrierDirection>(directionVal->Int32Value(vm));
        }
        if (!referencedIdVal->IsArray(vm)) {
            auto array = panda::Local<panda::ArrayRef>(referencedIdVal);
            int32_t referenceSize = array->Length(vm);
            std::vector<std::string> referencedIds;
            ParseReferencedId(vm, referenceSize, array, referencedIds);
            info.referencedId = referencedIds;
        }
        barrierInfos.push_back(info);
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    RelativeContainerModelNG::SetBarrier(frameNode, barrierInfos);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RelativeContainerBridge::ResetBarrier(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRelativeContainerModifier()->resetBarrier(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
