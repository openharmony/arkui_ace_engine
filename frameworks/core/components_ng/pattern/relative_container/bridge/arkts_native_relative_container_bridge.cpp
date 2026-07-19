/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/relative_container/bridge/arkts_native_relative_container_bridge.h"
#include <cstddef>

#include "base/geometry/calc_dimension.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/relative_container/relative_container_model_ng.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int POSITION_DIMENSION = 2;
constexpr int32_t LOCALIZED_BARRIER_DIRECTION_START = 4;
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
            auto idChar = ParseStringToCharPtr(str);
            if (idChar) {
                referencedIds.push_back(idChar);
            }
        }
    }
}

void ParseGuideLine(const EcmaVM* vm, panda::Local<panda::ArrayRef>& positionsArr, const int32_t& i,
    ArkUIGuidelineStyle& info, std::vector<RefPtr<ResourceObject>>& resObjs)
{
    Local<JSValueRef> posStartVal = panda::ArrayRef::GetValueAt(vm, positionsArr, i * POSITION_DIMENSION);
    CalcDimension startPos;
    RefPtr<ResourceObject> startPosResObj;
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, posStartVal, startPos, startPosResObj)) {
        info.start = startPos.Value();
        info.hasStart = true;
    }
    if (SystemProperties::ConfigChangePerform()) {
        if (startPosResObj) {
            resObjs.push_back(startPosResObj);
        } else {
            resObjs.push_back(nullptr);
        }
    }
    Local<JSValueRef> posEndVal = panda::ArrayRef::GetValueAt(vm, positionsArr, i * POSITION_DIMENSION + 1);
    CalcDimension endPos;
    RefPtr<ResourceObject> endPosResObj;
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, posEndVal, endPos, endPosResObj)) {
        info.end = endPos.Value();
        info.hasEnd = true;
    }
    if (SystemProperties::ConfigChangePerform()) {
        if (endPosResObj) {
            resObjs.push_back(endPosResObj);
        } else {
            resObjs.push_back(nullptr);
        }
    }
}

void JSParseGuideline(EcmaVM* vm, const Local<JSValueRef>& args, GuidelineInfo& guidelineInfoItem)
{
    if (!args->IsObject(vm)) {
        return;
    }

    auto guildLineInfoObj = args->ToObject(vm);
    Local<JSValueRef> idVal = guildLineInfoObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    Local<JSValueRef> directionVal = guildLineInfoObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "direction"));
    Local<JSValueRef> positionVal = guildLineInfoObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "position"));

    if (idVal->IsString(vm)) {
        guidelineInfoItem.id = idVal->ToString(vm)->ToString(vm);
    }

    if (directionVal->IsNumber()) {
        guidelineInfoItem.direction = static_cast<LineDirection>(directionVal->Int32Value(vm));
    }

    CalcDimension start;
    CalcDimension end;
    if (positionVal->IsObject(vm)) {
        auto val = positionVal->ToObject(vm);
        Local<JSValueRef> startVal = val->Get(vm, panda::StringRef::NewFromUtf8(vm, "start"));
        Local<JSValueRef> endVal = val->Get(vm, panda::StringRef::NewFromUtf8(vm, "end"));
        RefPtr<ResourceObject> startResObj;
        RefPtr<ResourceObject> endResObj;

        if (ArkTSUtils::ParseJsDimensionVpNG(vm, startVal, start, startResObj)) {
            guidelineInfoItem.start = start;
        }
        RelativeContainerModelNG::SetPositionResObj(
            startResObj, guidelineInfoItem, "relativeContainer.guideLine.position.start");
        if (ArkTSUtils::ParseJsDimensionVpNG(vm, endVal, end, endResObj)) {
            guidelineInfoItem.end = end;
        }
        RelativeContainerModelNG::SetPositionResObj(
            endResObj, guidelineInfoItem, "relativeContainer.guideLine.position.end");
    }
}

void JSParseBarrier(EcmaVM* vm, const Local<JSValueRef>& args, BarrierInfo& barrierInfoItem)
{
    if (!args->IsObject(vm)) {
        return;
    }

    auto barrierInfoObj = args->ToObject(vm);
    Local<JSValueRef> idVal = barrierInfoObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    Local<JSValueRef> directionVal = barrierInfoObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "direction"));
    Local<JSValueRef> localizedDirectionVal =
        barrierInfoObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "localizedDirection"));
    Local<JSValueRef> referencedIdVal = barrierInfoObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "referencedId"));

    if (idVal->IsString(vm)) {
        barrierInfoItem.id = idVal->ToString(vm)->ToString(vm);
    }

    if (directionVal->IsNumber()) {
        barrierInfoItem.direction = static_cast<BarrierDirection>(directionVal->Int32Value(vm));
    } else if (localizedDirectionVal->IsNumber()) {
        auto direction = localizedDirectionVal->Int32Value(vm);
        if (direction > static_cast<int32_t>(BarrierDirection::RIGHT)) {
            barrierInfoItem.direction = static_cast<BarrierDirection>(direction);
        } else {
            barrierInfoItem.direction =
                static_cast<BarrierDirection>(direction + LOCALIZED_BARRIER_DIRECTION_START);
        }
    }

    if (referencedIdVal->IsArray(vm)) {
        auto array = panda::Local<panda::ArrayRef>(referencedIdVal);
        size_t length = static_cast<size_t>(ArkTSUtils::GetArrayLength(vm, array));
        for (size_t i = 0; i < length; i++) {
            Local<JSValueRef> refIdVal = panda::ArrayRef::GetValueAt(vm, array, i);
            if (refIdVal->IsString(vm)) {
                barrierInfoItem.referencedId.emplace_back(refIdVal->ToString(vm)->ToString(vm));
            }
        }
    }
}

bool HandleSetGuideLineForJsView(EcmaVM* vm, const Local<JSValueRef>& firstArg, const Local<JSValueRef>& idsArg,
    FrameNode* frameNode)
{
    if (!ArkTSUtils::IsJsView(vm, firstArg)) {
        return false;
    }

    RelativeContainerModelNG::ResetResObj(frameNode, "relativeContainer.guideLine");
    std::vector<GuidelineInfo> jsGuidelineInfos;
    if (idsArg->IsUndefined() || (!idsArg->IsArray(vm) && !idsArg->IsObject(vm))) {
        RelativeContainerModelNG::SetGuideline(frameNode, jsGuidelineInfos);
        return true;
    }

    if (idsArg->IsArray(vm)) {
        auto array = panda::Local<panda::ArrayRef>(idsArg);
        size_t length = static_cast<size_t>(ArkTSUtils::GetArrayLength(vm, array));
        for (size_t i = 0; i < length; i++) {
            GuidelineInfo guidelineInfoItem;
            Local<JSValueRef> item = panda::ArrayRef::GetValueAt(vm, array, i);
            JSParseGuideline(vm, item, guidelineInfoItem);
            jsGuidelineInfos.emplace_back(guidelineInfoItem);
        }
    }

    RelativeContainerModelNG::SetGuideline(frameNode, jsGuidelineInfos);
    return true;
}

bool HandleSetBarrierForJsView(EcmaVM* vm, const Local<JSValueRef>& firstArg, const Local<JSValueRef>& idsArg,
    FrameNode* frameNode)
{
    if (!ArkTSUtils::IsJsView(vm, firstArg)) {
        return false;
    }

    std::vector<BarrierInfo> jsBarrierInfos;
    if (idsArg->IsUndefined() || (!idsArg->IsArray(vm) && !idsArg->IsObject(vm))) {
        RelativeContainerModelNG::SetBarrier(frameNode, jsBarrierInfos);
        return true;
    }

    if (idsArg->IsArray(vm)) {
        auto array = panda::Local<panda::ArrayRef>(idsArg);
        size_t length = static_cast<size_t>(ArkTSUtils::GetArrayLength(vm, array));
        for (size_t i = 0; i < length; i++) {
            BarrierInfo barrierInfoItem;
            Local<JSValueRef> item = panda::ArrayRef::GetValueAt(vm, array, i);
            JSParseBarrier(vm, item, barrierInfoItem);
            jsBarrierInfos.emplace_back(barrierInfoItem);
        }
    }

    RelativeContainerModelNG::SetBarrier(frameNode, jsBarrierInfos);
    return true;
}

bool HandleResetBarrierForInvalidArgs(EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<JSValueRef>& idsArg,
    const Local<JSValueRef>& directionsArg, const Local<JSValueRef>& referenceIdsArg)
{
    if (idsArg->IsArray(vm) && directionsArg->IsArray(vm) && referenceIdsArg->IsArray(vm)) {
        return false;
    }
    CHECK_NULL_RETURN(
        GetArkUINodeModifiers()->getRelativeContainerModifier()->resetBarrier, true);
    GetArkUINodeModifiers()->getRelativeContainerModifier()->resetBarrier(nativeNode);
    return true;
}
} // namespace

void RelativeContainerBridge::RegisterRelativeContainerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setGuideLine", "resetGuideLine", "setBarrier", "resetBarrier" };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RelativeContainerBridge::CreateRelativeContainer),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RelativeContainerBridge::SetGuideLine),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RelativeContainerBridge::ResetGuideLine),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RelativeContainerBridge::SetBarrier),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RelativeContainerBridge::ResetBarrier),
    };

    auto relativeContainer =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "relativeContainer"), relativeContainer);
}

ArkUINativeModuleValue RelativeContainerBridge::CreateRelativeContainer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    GetArkUINodeModifiers()->getRelativeContainerModifier()->createModel();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RelativeContainerBridge::SetGuideLine(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> idsArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> directionsArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> positionsArg = runtimeCallInfo->GetCallArgRef(NUM_3);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = nativeNode ? reinterpret_cast<FrameNode*>(nativeNode)
                                 : reinterpret_cast<FrameNode*>(ViewStackProcessor::GetInstance()->GetMainFrameNode());

    if (HandleSetGuideLineForJsView(vm, firstArg, idsArg, frameNode)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (!idsArg->IsArray(vm) || !directionsArg->IsArray(vm) || !positionsArg->IsArray(vm)) {
        CHECK_NULL_RETURN(
            GetArkUINodeModifiers()->getRelativeContainerModifier()->resetGuideline, panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getRelativeContainerModifier()->resetGuideline(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CHECK_NULL_RETURN(
        GetArkUINodeModifiers()->getRelativeContainerModifier()->setGuideLine, panda::JSValueRef::Undefined(vm));
    std::vector<ArkUIGuidelineStyle> guidelineInfos;
    auto idsArr = panda::Local<panda::ArrayRef>(idsArg);
    auto directionsArr = panda::Local<panda::ArrayRef>(directionsArg);
    auto positionsArr = panda::Local<panda::ArrayRef>(positionsArg);
    int32_t size = static_cast<int32_t>(ArkTSUtils::GetArrayLength(vm, idsArr));
    std::vector<RefPtr<ResourceObject>> resObjs;
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
        ParseGuideLine(vm, positionsArr, i, info, resObjs);
        guidelineInfos.push_back(info);
    }
    ArkUIGuidelineStyle* values = guidelineInfos.data();
    auto rawPtr = static_cast<void*>(&resObjs);
    GetArkUINodeModifiers()->getRelativeContainerModifier()->setGuideLine(nativeNode, values, size, rawPtr);
    FreeGuideLineCharPtr(values, size);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RelativeContainerBridge::ResetGuideLine(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getRelativeContainerModifier()->resetGuideline,
        panda::JSValueRef::Undefined(vm));
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

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = nativeNode ? reinterpret_cast<FrameNode*>(nativeNode)
                                 : reinterpret_cast<FrameNode*>(ViewStackProcessor::GetInstance()->GetMainFrameNode());

    CHECK_NE_RETURN(
        HandleSetBarrierForJsView(vm, firstArg, idsArg, frameNode), false, panda::JSValueRef::Undefined(vm));

    if (HandleResetBarrierForInvalidArgs(vm, nativeNode, idsArg, directionsArg, referenceIdsArg)) {
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<ArkUIBarrierStyle> barrierInfos;
    auto idsArr = panda::Local<panda::ArrayRef>(idsArg);
    auto directionsArr = panda::Local<panda::ArrayRef>(directionsArg);
    auto referenceIdsArr = panda::Local<panda::ArrayRef>(referenceIdsArg);
    int32_t size = static_cast<int32_t>(ArkTSUtils::GetArrayLength(vm, idsArr));
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
            uint32_t referenceSize = ArkTSUtils::GetArrayLength(vm, array);
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
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(
        GetArkUINodeModifiers()->getRelativeContainerModifier()->resetBarrier, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getRelativeContainerModifier()->resetBarrier(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
