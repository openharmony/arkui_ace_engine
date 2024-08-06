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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_rect_bridge.h"
#include "ecmascript/napi/include/jsnapi.h"
#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
constexpr int CALL_ARG_0 = 0;
constexpr int CALL_ARG_1 = 1;
constexpr uint32_t VALID_RADIUS_PAIR_FLAG = 1;
constexpr uint32_t INVALID_RADIUS_PAIR_FLAG = 0;
} // namespace
ArkUINativeModuleValue RectBridge::SetRadiusWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CalcDimension radiusWidth;
    bool isSupportPercent = true;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, radiusWidth, isSupportPercent)) {
        GetArkUINodeModifiers()->getRectModifier()->resetRectRadiusWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getRectModifier()->setRectRadiusWidth(
        nativeNode, radiusWidth.Value(), static_cast<int32_t>(radiusWidth.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RectBridge::ResetRadiusWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRectModifier()->resetRectRadiusWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RectBridge::SetRadiusHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CalcDimension radiusHeight;
    bool isSupportPercent = true;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, radiusHeight, isSupportPercent)) {
        GetArkUINodeModifiers()->getRectModifier()->resetRectRadiusHeight(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getRectModifier()->setRectRadiusHeight(
        nativeNode, radiusHeight.Value(), static_cast<int32_t>(radiusHeight.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RectBridge::ResetRadiusHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRectModifier()->resetRectRadiusHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RectBridge::SetRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    std::vector<ArkUI_Float32> radiusValues;
    std::vector<int32_t> radiusUnits;
    std::vector<uint32_t> radiusValidPairs;
    if (jsValue->IsArray(vm)) {
        RectBridge::SetRadiusWithArray(vm, jsValue, radiusValues, radiusUnits, radiusValidPairs);
        GetArkUINodeModifiers()->getRectModifier()->setRectRadiusWithArray(
            nativeNode, radiusValues.data(), radiusUnits.data(), radiusValidPairs.data(), radiusValidPairs.size());
        return panda::JSValueRef::Undefined(vm);
    }
    if (jsValue->IsNumber() || jsValue->IsString(vm) || jsValue->IsObject(vm)) {
        CalcDimension parsedValue;
        bool isSupportPercent = true;
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, parsedValue, isSupportPercent)) {
            parsedValue.Reset();
        }
        GetArkUINodeModifiers()->getRectModifier()->setRectRadiusWithValue(
            nativeNode, parsedValue.Value(), static_cast<int32_t>(parsedValue.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RectBridge::ResetRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRectModifier()->resetRectRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void RectBridge::SetRadiusWithArray(const EcmaVM* vm, const Local<JSValueRef>& jsValue,
    std::vector<ArkUI_Float32>& radiusValues,
    std::vector<int32_t>& radiusUnits,
    std::vector<uint32_t>& radiusValidPairs)
{
    if (!jsValue->IsArray(vm)) {
        return;
    }
    auto arrayVal = panda::Local<panda::ArrayRef>(jsValue);
    auto length = arrayVal->Length(vm);
    if (length <= 0) {
        return;
    }
    size_t radiusPairsCount = 4;
    size_t dataCount = 2;
    for (size_t i = 0; i < radiusPairsCount; i++) {
        if (i >= length && length < radiusPairsCount) {
            SetRadiusArraysInvalidValue(radiusValues, radiusUnits, radiusValidPairs, i);
            break;
        }
        Local<JSValueRef> radiusItem = panda::ArrayRef::GetValueAt(vm, arrayVal, i);
        if (!radiusItem->IsArray(vm)) {
            SetRadiusArraysInvalidValue(radiusValues, radiusUnits, radiusValidPairs, i);
            break;
        }
        auto radiusArray = panda::Local<panda::ArrayRef>(radiusItem);
        if (radiusArray->Length(vm) != dataCount) {
            SetRadiusArraysInvalidValue(radiusValues, radiusUnits, radiusValidPairs, i);
            break;
        }
        uint32_t indexX = 0;
        uint32_t indexY = 1;
        Local<JSValueRef> radiusX = panda::ArrayRef::GetValueAt(vm, radiusArray, indexX);
        Local<JSValueRef> radiusY = panda::ArrayRef::GetValueAt(vm, radiusArray, indexY);
        CalcDimension radiusXValue;
        CalcDimension radiusYValue;
        bool isSupportPercent = true;
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, radiusX, radiusXValue, isSupportPercent)) {
            radiusXValue.Reset();
        }
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, radiusY, radiusYValue, isSupportPercent)) {
            radiusYValue.Reset();
        }
        radiusValidPairs.push_back(VALID_RADIUS_PAIR_FLAG);
        radiusValues.push_back(static_cast<ArkUI_Float32>(radiusXValue.Value()));
        radiusValues.push_back(static_cast<ArkUI_Float32>(radiusYValue.Value()));
        radiusUnits.push_back(static_cast<int32_t>(radiusXValue.Unit()));
        radiusUnits.push_back(static_cast<int32_t>(radiusYValue.Unit()));
    }
}

void RectBridge::SetRadiusArraysInvalidValue(std::vector<ArkUI_Float32>& radiusValues,
    std::vector<int32_t>& radiusUnits, std::vector<uint32_t>& radiusValidPairs, int index)
{
    radiusValidPairs.push_back(INVALID_RADIUS_PAIR_FLAG);
    CalcDimension radiusXValue;
    CalcDimension radiusYValue;
    radiusXValue.Reset();
    radiusYValue.Reset();
    radiusValues.push_back(static_cast<ArkUI_Float32>(radiusXValue.Value()));
    radiusValues.push_back(static_cast<ArkUI_Float32>(radiusYValue.Value()));
    radiusUnits.push_back(static_cast<int32_t>(radiusXValue.Unit()));
    radiusUnits.push_back(static_cast<int32_t>(radiusYValue.Unit()));
}
} // namespace OHOS::Ace::NG
