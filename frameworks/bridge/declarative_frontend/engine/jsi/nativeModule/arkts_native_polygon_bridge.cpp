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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_polygon_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;

ArkUINativeModuleValue PolygonBridge::SetPolygonPoints(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> xPoint = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> yPoint = runtimeCallInfo->GetCallArgRef(NUM_2);
    if (!xPoint->IsArray(vm) || !yPoint->IsArray(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto xPointArray = panda::Local<panda::ArrayRef>(xPoint);
    auto yPointArray = panda::Local<panda::ArrayRef>(yPoint);
    auto xlength = xPointArray->Length(vm);
    auto ylength = yPointArray->Length(vm);
    if (xlength <= 0 || xlength != ylength) {
        GetArkUINodeModifiers()->getPolygonModifier()->resetPolygonPoints(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    bool flag = true;
    CalcDimension x;
    CalcDimension y;
    std::vector<ArkUI_Float32> xPointValues;
    std::vector<ArkUI_Float32> yPointValues;
    for (size_t i = 0; i < xlength; i++) {
        Local<JSValueRef> xValue = panda::ArrayRef::GetValueAt(vm, xPointArray, i);
        Local<JSValueRef> yValue = panda::ArrayRef::GetValueAt(vm, yPointArray, i);
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, xValue, x, false) ||
            !ArkTSUtils::ParseJsDimensionVpNG(vm, yValue, y, false)) {
            flag = false;
            break;
        }

        xPointValues.push_back(x.Value());
        yPointValues.push_back(y.Value());
    }

    if (flag) {
        GetArkUINodeModifiers()->getPolygonModifier()->
            setPolygonPoints(nativeNode, xPointValues.data(), yPointValues.data(), xlength);
    } else {
        GetArkUINodeModifiers()->getPolygonModifier()->resetPolygonPoints(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PolygonBridge::ResetPolygonPoints(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPolygonModifier()->resetPolygonPoints(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}
