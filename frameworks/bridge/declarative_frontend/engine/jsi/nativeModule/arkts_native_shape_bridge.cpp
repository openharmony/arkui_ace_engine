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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_shape_bridge.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;

ArkUINativeModuleValue ShapeBridge::SetViewPort(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> xArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> yArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    CalcDimension dimLeft;
    ArkTSUtils::ParseJsDimensionVp(vm, xArg, dimLeft);
    CalcDimension dimTop;
    ArkTSUtils::ParseJsDimensionVp(vm, yArg, dimTop);
    CalcDimension dimWidth;
    ArkTSUtils::ParseJsDimensionVp(vm, widthArg, dimWidth);
    CalcDimension dimHeight;
    ArkTSUtils::ParseJsDimensionVp(vm, heightArg, dimHeight);
    std::vector<ArkUI_Float32> dimValues;
    std::vector<int32_t> dimUnits;
    dimValues.push_back(static_cast<ArkUI_Float32>(dimLeft.Value()));
    dimValues.push_back(static_cast<ArkUI_Float32>(dimTop.Value()));
    dimValues.push_back(static_cast<ArkUI_Float32>(dimWidth.Value()));
    dimValues.push_back(static_cast<ArkUI_Float32>(dimHeight.Value()));
    dimUnits.push_back(static_cast<int32_t>(dimLeft.Unit()));
    dimUnits.push_back(static_cast<int32_t>(dimTop.Unit()));
    dimUnits.push_back(static_cast<int32_t>(dimWidth.Unit()));
    dimUnits.push_back(static_cast<int32_t>(dimHeight.Unit()));
    GetArkUINodeModifiers()->getShapeModifier()->setShapeViewPort(nativeNode, dimValues.data(), dimUnits.data());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ShapeBridge::ResetViewPort(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getShapeModifier()->resetShapeViewPort(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ShapeBridge::SetMesh(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArrayArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> columnArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> rowArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    std::vector<ArkUI_Float32> mesh;
    if (valueArrayArg->IsArray(vm)) {
        auto arrayVal = panda::Local<panda::ArrayRef>(valueArrayArg);
        auto length = arrayVal->Length(vm);
        if (length <= 0) {
            return panda::JSValueRef::Undefined(vm);
        }
        for (size_t i = 0; i < length; i++) {
            Local<JSValueRef> radiusItem = panda::ArrayRef::GetValueAt(vm, arrayVal, i);
            double vert;
            if (ArkTSUtils::ParseJsDouble(vm, radiusItem, vert)) {
                mesh.push_back(static_cast<ArkUI_Float32>(vert));
            }
        }
    }
    int32_t column = 0;
    int32_t row = 0;
    if (!ArkTSUtils::ParseJsInteger(vm, columnArg, column)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (!ArkTSUtils::ParseJsInteger(vm, rowArg, row)) {
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getShapeModifier()->setShapeMesh(nativeNode, mesh.data(), mesh.size(), column, row);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ShapeBridge::ResetMesh(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getShapeModifier()->resetShapeMesh(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
