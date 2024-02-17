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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_line_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue LineBridge::SetStartPoint(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);

    if (!jsValue->IsArray(vm)) {
        GetArkUINodeModifiers()->getLineModifier()->resetStartPoint(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    auto arrayVal = panda::Local<panda::ArrayRef>(jsValue);
    auto length = arrayVal->Length(vm);
    if (length <= 0) {
        GetArkUINodeModifiers()->getLineModifier()->resetStartPoint(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension star;
    CalcDimension end;
    std::string calcStr;
    Local<JSValueRef> starItem = panda::ArrayRef::GetValueAt(vm, arrayVal, 0);
    Local<JSValueRef> endItem = panda::ArrayRef::GetValueAt(vm, arrayVal, 1);
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, starItem, star, false)) {
        star = CalcDimension(0, DimensionUnit::VP);
    }
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, endItem, end, false)) {
        end = CalcDimension(0, DimensionUnit::VP);
    }

    std::vector<ArkUI_Float32> pointValues;
    std::vector<int32_t> pointUnits;
    std::vector<const char*> pointStr;
    pointUnits.push_back(static_cast<int>(star.Unit()));
    pointUnits.push_back(static_cast<int>(end.Unit()));
    if (star.Unit() == DimensionUnit::CALC) {
        pointValues.push_back(0);
        pointStr.push_back(star.CalcValue().c_str());
    } else {
        pointValues.push_back(star.Value());
        pointStr.push_back(calcStr.c_str());
    }

    if (end.Unit() == DimensionUnit::CALC) {
        pointValues.push_back(0);
        pointStr.push_back(end.CalcValue().c_str());
    } else {
        pointValues.push_back(end.Value());
        pointStr.push_back(calcStr.c_str());
    }

    GetArkUINodeModifiers()->getLineModifier()->setStartPoint(nativeNode, pointValues.data(),
        pointUnits.data(), pointStr.data());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LineBridge::ResetStartPoint(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getLineModifier()->resetStartPoint(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LineBridge::SetEndPoint(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);

    if (!jsValue->IsArray(vm)) {
        GetArkUINodeModifiers()->getLineModifier()->resetEndPoint(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    auto arrayVal = panda::Local<panda::ArrayRef>(jsValue);
    auto length = arrayVal->Length(vm);
    if (length <= 0) {
        GetArkUINodeModifiers()->getLineModifier()->resetEndPoint(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension star;
    CalcDimension end;
    std::string calcStr;
    Local<JSValueRef> starItem = panda::ArrayRef::GetValueAt(vm, arrayVal, 0);
    Local<JSValueRef> endItem = panda::ArrayRef::GetValueAt(vm, arrayVal, 1);
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, starItem, star, false)) {
        star = CalcDimension(0, DimensionUnit::VP);
    }
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, endItem, end, false)) {
        end = CalcDimension(0, DimensionUnit::VP);
    }

    std::vector<ArkUI_Float32> pointValues;
    std::vector<int32_t> pointUnits;
    std::vector<const char*> pointStr;
    pointUnits.push_back(static_cast<int>(star.Unit()));
    pointUnits.push_back(static_cast<int>(end.Unit()));
    if (star.Unit() == DimensionUnit::CALC) {
        pointValues.push_back(0);
        pointStr.push_back(star.CalcValue().c_str());
    } else {
        pointValues.push_back(star.Value());
        pointStr.push_back(calcStr.c_str());
    }

    if (end.Unit() == DimensionUnit::CALC) {
        pointValues.push_back(0);
        pointStr.push_back(end.CalcValue().c_str());
    } else {
        pointValues.push_back(end.Value());
        pointStr.push_back(calcStr.c_str());
    }

    GetArkUINodeModifiers()->getLineModifier()->setEndPoint(nativeNode,
        pointValues.data(), pointUnits.data(), pointStr.data());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LineBridge::ResetEndPoint(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getLineModifier()->resetEndPoint(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}