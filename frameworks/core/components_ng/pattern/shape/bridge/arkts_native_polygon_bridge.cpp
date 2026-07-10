/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/shape/bridge/arkts_native_polygon_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/polygon_model_ng.h"
#include "core/interfaces/native/node/polygon_modifier.h"
#include "core/components_ng/pattern/shape/shape_abstract_model.h"
#include "core/components_ng/pattern/shape/bridge/arkts_native_common_shape_bridge.h"

namespace OHOS::Ace::NG {

constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;

void PolygonBridge::RegisterPolygonAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setPolygonPoints", "resetPolygonPoints" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PolygonBridge::CreatePolygon),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PolygonBridge::SetPolygonPoints),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PolygonBridge::ResetPolygonPoints),
    };

    auto polygon = panda::ObjectRef::NewWithNamedProperties(vm,
        sizeof(functionNames) / sizeof(functionNames[0]), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "polygon"), polygon);
}

ArkUINativeModuleValue PolygonBridge::CreatePolygon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    GetArkUINodeModifiers()->getPolygonModifier()->createPolygon();

    CalcDimension width;
    CalcDimension height;
    if (runtimeCallInfo->GetArgsNumber() > 0 && firstArg->IsObject(vm)) {
        auto nativeNode = reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
        CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
        auto paramObj = firstArg->ToObject(vm);
        auto widthVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "width"));
        RefPtr<ResourceObject> widthResObj;
        CommonShapeBridge::ParseJsValue(vm, widthVal, width, widthResObj, true);
        auto heightVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "height"));
        RefPtr<ResourceObject> heightResObj;
        CommonShapeBridge::ParseJsValue(vm, heightVal, height, heightResObj, false);

        if (LessNotEqual(width.Value(), 0.0)) {
            width.SetValue(0.0);
        }
        if (LessNotEqual(height.Value(), 0.0)) {
            height.SetValue(0.0);
        }
        GetArkUINodeModifiers()->getCommonShapeModifier()->setShapeWidth(
            nativeNode, width.Value(), static_cast<int32_t>(width.Unit()), AceType::RawPtr(widthResObj));
        GetArkUINodeModifiers()->getCommonShapeModifier()->setShapeHeight(
            nativeNode, height.Value(), static_cast<int32_t>(height.Unit()), AceType::RawPtr(heightResObj));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PolygonBridge::SetPolygonPoints(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> xPoint = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> yPoint = runtimeCallInfo->GetCallArgRef(NUM_2);
    if (!xPoint->IsArray(vm) || !yPoint->IsArray(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto xPointArray = panda::Local<panda::ArrayRef>(xPoint);
    auto yPointArray = panda::Local<panda::ArrayRef>(yPoint);
    auto xlength = ArkTSUtils::GetArrayLength(vm, xPointArray);
    auto ylength = ArkTSUtils::GetArrayLength(vm, yPointArray);
    if (xlength <= 0 || xlength != ylength) {
        GetArkUINodeModifiers()->getPolygonModifier()->resetPolygonPoints(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    bool flag = true;
    CalcDimension x;
    CalcDimension y;
    std::vector<ArkUI_Float32> xPointValues;
    std::vector<ArkUI_Float32> yPointValues;
    std::vector<RefPtr<ResourceObject>> xResObjArray;
    std::vector<RefPtr<ResourceObject>> yResObjArray;
    for (size_t i = 0; i < xlength; i++) {
        Local<JSValueRef> xValue = panda::ArrayRef::GetValueAt(vm, xPointArray, i);
        Local<JSValueRef> yValue = panda::ArrayRef::GetValueAt(vm, yPointArray, i);
        RefPtr<ResourceObject> xResObj;
        RefPtr<ResourceObject> yResObj;
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, xValue, x, xResObj, false) ||
            !ArkTSUtils::ParseJsDimensionVpNG(vm, yValue, y, yResObj, false)) {
            flag = false;
            break;
        }

        xPointValues.push_back(x.Value());
        yPointValues.push_back(y.Value());
        xResObjArray.push_back(xResObj);
        yResObjArray.push_back(yResObj);
    }

    if (flag) {
        GetArkUINodeModifiers()->getPolygonModifier()->setPolygonPoints(
            nativeNode, xPointValues.data(), yPointValues.data(), xlength, xResObjArray.data(), yResObjArray.data());
    } else {
        GetArkUINodeModifiers()->getPolygonModifier()->resetPolygonPoints(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PolygonBridge::ResetPolygonPoints(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getPolygonModifier()->resetPolygonPoints(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
