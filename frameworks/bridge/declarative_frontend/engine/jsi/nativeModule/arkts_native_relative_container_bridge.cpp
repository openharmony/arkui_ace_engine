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
constexpr int POSITION_DIMENSION = 2;
constexpr char END_CHAR = '\0';

ArkUI_CharPtr ParseStringToCharPtr(std::string str)
{
    char* id = static_cast<char*>(malloc((str.length() + 1) * sizeof(char)));
    CHECK_NULL_RETURN(id, nullptr);
    str.copy(id, str.length());
    id[str.length()] = END_CHAR;
    return id;
}

void FreeGuideLineCharPtr(ArkUIGuidelineStyle* values, ArkUI_Int32 size)
{
    for (int32_t i = 0; i < size; ++i) {
        free(const_cast<char*>(values[i].id));
        values[i].id = nullptr;
    }
}

void FreeBarrierCharPtr(ArkUIBarrierStyle* values, ArkUI_Int32 size)
{
    for (int32_t i = 0; i < size; ++i) {
        free(const_cast<char*>(values[i].id));
        values[i].id = nullptr;
        auto referencedIdChar = values[i].referencedId;
        auto referencedIdSize = values[i].referencedIdSize;
        for (int32_t j = 0; j < referencedIdSize; ++j) {
            free(const_cast<char*>(referencedIdChar[j]));
            referencedIdChar[j] = nullptr;
        }
    }
}

void ParseReferencedId(EcmaVM* vm, int32_t referenceSize,
    const panda::Local<panda::ArrayRef>& array, std::vector<ArkUI_CharPtr>& referencedIds)
{
    for (int32_t i = 0; i < referenceSize; i++) {
        Local<JSValueRef> referencedId = panda::ArrayRef::GetValueAt(vm, array, i);
        if (referencedId->IsString(vm)) {
            std::string str = referencedId->ToString(vm)->ToString(vm);
            referencedIds.push_back(ParseStringToCharPtr(str));
        }
    }
}
} // namespace

ArkUINativeModuleValue RelativeContainerBridge::SetGuideLine(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> idsArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> directionsArg = runtimeCallInfo->GetCallArgRef(2);
    Local<JSValueRef> positionsArg = runtimeCallInfo->GetCallArgRef(3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!idsArg->IsArray(vm) || !directionsArg->IsArray(vm) || !positionsArg->IsArray(vm)) {
        GetArkUINodeModifiers()->getRelativeContainerModifier()->resetGuideline(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<ArkUIGuidelineStyle> guidelineInfos;
    auto idsArr = panda::Local<panda::ArrayRef>(idsArg);
    auto directionsArr = panda::Local<panda::ArrayRef>(directionsArg);
    auto positionsArr = panda::Local<panda::ArrayRef>(positionsArg);
    int32_t size = static_cast<int32_t>(idsArr->Length(vm));
    for (int32_t i = 0; i < size; i++) {
        ArkUIGuidelineStyle info;
        Local<JSValueRef> idVal = panda::ArrayRef::GetValueAt(vm, idsArr, i);
        if (idVal->IsString(vm)) {
            std::string str = idVal->ToString(vm)->ToString(vm);
            info.id = ParseStringToCharPtr(str);
        }
        Local<JSValueRef> directionVal = panda::ArrayRef::GetValueAt(vm, directionsArr, i);
        if (directionVal->IsNumber()) {
            info.direction = directionVal->Int32Value(vm);
        }
        Local<JSValueRef> posStartVal = panda::ArrayRef::GetValueAt(vm,
            positionsArr, i * POSITION_DIMENSION);
        CalcDimension startPos;
        if (ArkTSUtils::ParseJsDimensionVpNG(vm, posStartVal, startPos)) {
            info.start = startPos.Value();
            info.hasStart = true;
        }
        Local<JSValueRef> posEndVal = panda::ArrayRef::GetValueAt(vm,
            positionsArr, i * POSITION_DIMENSION + 1);
        CalcDimension endPos;
        if (ArkTSUtils::ParseJsDimensionVpNG(vm, posEndVal, endPos)) {
            info.end = endPos.Value();
            info.hasEnd = true;
        }
        guidelineInfos.push_back(info);
    }
    ArkUIGuidelineStyle* values = guidelineInfos.data();
    GetArkUINodeModifiers()->getRelativeContainerModifier()->setGuideLine(nativeNode, values, size);
    FreeGuideLineCharPtr(values, size);
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
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> idsArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> directionsArg = runtimeCallInfo->GetCallArgRef(2);
    Local<JSValueRef> referenceIdsArg = runtimeCallInfo->GetCallArgRef(3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!idsArg->IsArray(vm) || !directionsArg->IsArray(vm) || !referenceIdsArg->IsArray(vm)) {
        GetArkUINodeModifiers()->getRelativeContainerModifier()->resetBarrier(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<ArkUIBarrierStyle> barrierInfos;
    auto idsArr = panda::Local<panda::ArrayRef>(idsArg);
    auto directionsArr = panda::Local<panda::ArrayRef>(directionsArg);
    auto referenceIdsArr = panda::Local<panda::ArrayRef>(referenceIdsArg);
    int32_t size = static_cast<int32_t>(idsArr->Length(vm));
    std::vector<ArkUI_CharPtr> referencedIds;
    for (int32_t i = 0; i < size; i++) {
        ArkUIBarrierStyle info;
        Local<JSValueRef> idVal = panda::ArrayRef::GetValueAt(vm, idsArr, i);
        Local<JSValueRef> directionVal = panda::ArrayRef::GetValueAt(vm, directionsArr, i);
        Local<JSValueRef> referencedIdVal = panda::ArrayRef::GetValueAt(vm, referenceIdsArr, i);
        if (idVal->IsString(vm)) {
            std::string str = idVal->ToString(vm)->ToString(vm);
            info.id = ParseStringToCharPtr(str);
        }
        if (directionVal->IsNumber()) {
            info.direction = directionVal->Int32Value(vm);
        }
        if (referencedIdVal->IsArray(vm)) {
            auto array = panda::Local<panda::ArrayRef>(referencedIdVal);
            uint32_t referenceSize = array->Length(vm);
            ParseReferencedId(vm, static_cast<int32_t>(referenceSize), array, referencedIds);
            info.referencedId = referencedIds.data();
            info.referencedIdSize = static_cast<int32_t>(referencedIds.size());
            referencedIds.clear();
        } else {
            info.referencedIdSize = 0;
        }
        barrierInfos.push_back(info);
    }
    ArkUIBarrierStyle* values = barrierInfos.data();
    GetArkUINodeModifiers()->getRelativeContainerModifier()->setBarrier(nativeNode, values, size);
    FreeBarrierCharPtr(values, size);
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
