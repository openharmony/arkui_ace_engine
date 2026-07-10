/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/shape/bridge/arkts_native_rect_bridge.h"
#include "ecmascript/napi/include/jsnapi.h"
#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/shape/bridge/arkts_native_common_shape_bridge.h"
#include "core/components_ng/pattern/shape/rect_model_ng.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr uint32_t VALID_RADIUS_PAIR_FLAG = 1;
constexpr uint32_t INVALID_RADIUS_PAIR_FLAG = 0;

struct RadiusArrayResult {
    std::vector<ArkUI_Float32> radiusValues;
    std::vector<int32_t> radiusUnits;
    std::vector<uint32_t> radiusValidPairs;
    std::vector<RefPtr<ResourceObject>> radiusXResObjArray;
    std::vector<RefPtr<ResourceObject>> radiusYResObjArray;
};

void SetRadiusArraysInvalidValue(RadiusArrayResult& result)
{
    result.radiusValidPairs.push_back(INVALID_RADIUS_PAIR_FLAG);
    CalcDimension radiusXValue;
    CalcDimension radiusYValue;
    radiusXValue.Reset();
    radiusYValue.Reset();
    result.radiusValues.push_back(static_cast<ArkUI_Float32>(radiusXValue.Value()));
    result.radiusValues.push_back(static_cast<ArkUI_Float32>(radiusYValue.Value()));
    result.radiusUnits.push_back(static_cast<int32_t>(radiusXValue.Unit()));
    result.radiusUnits.push_back(static_cast<int32_t>(radiusYValue.Unit()));
}

void SetRadiusWithArray(const EcmaVM* vm, const Local<JSValueRef>& jsValue, RadiusArrayResult& result)
{
    if (!jsValue->IsArray(vm)) {
        return;
    }
    auto arrayVal = panda::Local<panda::ArrayRef>(jsValue);
    auto length = ArkTSUtils::GetArrayLength(vm, arrayVal);
    if (length <= 0) {
        return;
    }
    size_t radiusPairsCount = 4;
    size_t dataCount = 2;
    for (size_t i = 0; i < radiusPairsCount; i++) {
        if (i >= length && length < radiusPairsCount) {
            SetRadiusArraysInvalidValue(result);
            break;
        }
        Local<JSValueRef> radiusItem = panda::ArrayRef::GetValueAt(vm, arrayVal, i);
        if (!radiusItem->IsArray(vm)) {
            SetRadiusArraysInvalidValue(result);
            break;
        }
        auto radiusArray = panda::Local<panda::ArrayRef>(radiusItem);
        if (ArkTSUtils::GetArrayLength(vm, radiusArray) != dataCount) {
            SetRadiusArraysInvalidValue(result);
            break;
        }
        constexpr uint32_t indexX = 0;
        constexpr uint32_t indexY = 1;
        Local<JSValueRef> radiusX = panda::ArrayRef::GetValueAt(vm, radiusArray, indexX);
        Local<JSValueRef> radiusY = panda::ArrayRef::GetValueAt(vm, radiusArray, indexY);
        CalcDimension radiusXValue;
        CalcDimension radiusYValue;
        RefPtr<ResourceObject> radiusXResObj;
        RefPtr<ResourceObject> radiusYResObj;
        bool isSupportPercent = true;
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, radiusX, radiusXValue, radiusXResObj, isSupportPercent)) {
            radiusXValue.Reset();
        }
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, radiusY, radiusYValue, radiusYResObj, isSupportPercent)) {
            radiusYValue.Reset();
        }
        result.radiusValidPairs.push_back(VALID_RADIUS_PAIR_FLAG);
        result.radiusValues.push_back(static_cast<ArkUI_Float32>(radiusXValue.Value()));
        result.radiusValues.push_back(static_cast<ArkUI_Float32>(radiusYValue.Value()));
        result.radiusUnits.push_back(static_cast<int32_t>(radiusXValue.Unit()));
        result.radiusUnits.push_back(static_cast<int32_t>(radiusYValue.Unit()));
        result.radiusXResObjArray.push_back(radiusXResObj);
        result.radiusYResObjArray.push_back(radiusYResObj);
    }
}

void ParseRectWidthAndHeight(EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<ObjectRef>& paramObj)
{
    auto widthVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "width"));
    CalcDimension width;
    RefPtr<ResourceObject> widthResObj;
    CommonShapeBridge::ParseJsValue(vm, widthVal, width, widthResObj, true);
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }
    GetArkUINodeModifiers()->getCommonShapeModifier()->setShapeWidth(
        nativeNode, width.Value(), static_cast<int32_t>(width.Unit()), AceType::RawPtr(widthResObj));

    auto heightVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "height"));
    CalcDimension height;
    RefPtr<ResourceObject> heightResObj;
    CommonShapeBridge::ParseJsValue(vm, heightVal, height, heightResObj, false);
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }
    GetArkUINodeModifiers()->getCommonShapeModifier()->setShapeHeight(
        nativeNode, height.Value(), static_cast<int32_t>(height.Unit()), AceType::RawPtr(heightResObj));
}

void ParseRectRadiusOptions(EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<ObjectRef>& paramObj)
{
    auto radiusWidthArg = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "radiusWidth"));
    if (!radiusWidthArg->IsUndefined() && !radiusWidthArg->IsNull()) {
        CalcDimension radiusWidth(0.0f);
        RefPtr<ResourceObject> radiusWidthResObj;
        bool isSupportPercent = true;
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, radiusWidthArg, radiusWidth, radiusWidthResObj, isSupportPercent)) {
            radiusWidth.SetValue(0.0f);
        }
        GetArkUINodeModifiers()->getRectModifier()->setRectRadiusWidth(nativeNode, radiusWidth.Value(),
            static_cast<int32_t>(radiusWidth.Unit()), AceType::RawPtr(radiusWidthResObj));
    }

    auto radiusHeightArg = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "radiusHeight"));
    if (!radiusHeightArg->IsUndefined() && !radiusHeightArg->IsNull()) {
        CalcDimension radiusHeight(0.0f);
        RefPtr<ResourceObject> radiusHeightResObj;
        bool isSupportPercent = true;
        if (!ArkTSUtils::ParseJsDimensionVpNG(
                vm, radiusHeightArg, radiusHeight, radiusHeightResObj, isSupportPercent)) {
            radiusHeight.SetValue(0.0f);
        }
        GetArkUINodeModifiers()->getRectModifier()->setRectRadiusHeight(nativeNode, radiusHeight.Value(),
            static_cast<int32_t>(radiusHeight.Unit()), AceType::RawPtr(radiusHeightResObj));
    }

    auto radiusArg = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "radius"));
    if (radiusArg->IsUndefined() || radiusArg->IsNull()) {
        return;
    }
    if (radiusArg->IsArray(vm)) {
        RadiusArrayResult result;
        SetRadiusWithArray(vm, radiusArg, result);
        GetArkUINodeModifiers()->getRectModifier()->setRectRadiusWithArray(nativeNode, result.radiusValues.data(),
            result.radiusUnits.data(), result.radiusValidPairs.data(), result.radiusValidPairs.size(),
            result.radiusXResObjArray.data(), result.radiusYResObjArray.data());
    } else if (radiusArg->IsNumber() || radiusArg->IsString(vm) || radiusArg->IsObject(vm)) {
        CalcDimension radius(0.0f);
        RefPtr<ResourceObject> radiusResObj;
        bool isSupportPercent = true;
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, radiusArg, radius, radiusResObj, isSupportPercent)) {
            radius.SetValue(0.0f);
        }
        GetArkUINodeModifiers()->getRectModifier()->setRectRadiusWithValue(nativeNode, radius.Value(),
            static_cast<int32_t>(radius.Unit()), AceType::RawPtr(radiusResObj));
    }
}

void ParseRectCreateOptions(EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<JSValueRef>& firstArg)
{
    auto paramObj = firstArg->ToObject(vm);
    ParseRectWidthAndHeight(vm, nativeNode, paramObj);
    ParseRectRadiusOptions(vm, nativeNode, paramObj);
}
} // namespace

void RectBridge::RegisterRectAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create",
        "setRectRadiusWidth",
        "resetRectRadiusWidth",
        "setRectRadiusHeight",
        "resetRectRadiusHeight",
        "setRectRadius",
        "resetRectRadius",
    };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RectBridge::CreateRect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RectBridge::SetRadiusWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RectBridge::ResetRadiusWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RectBridge::SetRadiusHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RectBridge::ResetRadiusHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RectBridge::SetRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RectBridge::ResetRadius),
    };
    auto rect = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "rect"), rect);
}

ArkUINativeModuleValue RectBridge::CreateRect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    GetArkUINodeModifiers()->getRectModifier()->createRect();

    if (runtimeCallInfo->GetArgsNumber() > 0 && firstArg->IsObject(vm)) {
        auto nativeNode = reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
        CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
        ParseRectCreateOptions(vm, nativeNode, firstArg);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RectBridge::SetRadiusWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension radiusWidth;
    bool isSupportPercent = true;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, radiusWidth, resObj, isSupportPercent)) {
        if (ArkTSUtils::IsJsView(vm, firstArg)) {
            GetArkUINodeModifiers()->getRectModifier()->setRectRadiusWidth(
                nativeNode, 0.0f, static_cast<int32_t>(DimensionUnit::VP), nullptr);
        } else {
            GetArkUINodeModifiers()->getRectModifier()->resetRectRadiusWidth(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getRectModifier()->setRectRadiusWidth(
        nativeNode, radiusWidth.Value(), static_cast<int32_t>(radiusWidth.Unit()), AceType::RawPtr(resObj));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RectBridge::ResetRadiusWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getRectModifier()->resetRectRadiusWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RectBridge::SetRadiusHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension radiusHeight;
    bool isSupportPercent = true;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, radiusHeight, resObj, isSupportPercent)) {
        if (ArkTSUtils::IsJsView(vm, firstArg)) {
            GetArkUINodeModifiers()->getRectModifier()->setRectRadiusHeight(
                nativeNode, 0.0f, static_cast<int32_t>(DimensionUnit::VP), nullptr);
        } else {
            GetArkUINodeModifiers()->getRectModifier()->resetRectRadiusHeight(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getRectModifier()->setRectRadiusHeight(
        nativeNode, radiusHeight.Value(), static_cast<int32_t>(radiusHeight.Unit()), AceType::RawPtr(resObj));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RectBridge::ResetRadiusHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getRectModifier()->resetRectRadiusHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RectBridge::SetRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (jsValue->IsArray(vm)) {
        RadiusArrayResult result;
        SetRadiusWithArray(vm, jsValue, result);
        GetArkUINodeModifiers()->getRectModifier()->setRectRadiusWithArray(nativeNode, result.radiusValues.data(),
            result.radiusUnits.data(), result.radiusValidPairs.data(), result.radiusValidPairs.size(),
            result.radiusXResObjArray.data(), result.radiusYResObjArray.data());
        return panda::JSValueRef::Undefined(vm);
    }
    if (jsValue->IsNumber() || jsValue->IsString(vm) || jsValue->IsObject(vm)) {
        CalcDimension parsedValue;
        bool isSupportPercent = true;
        RefPtr<ResourceObject> resObj;
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, parsedValue, resObj, isSupportPercent)) {
            parsedValue.Reset();
        }
        GetArkUINodeModifiers()->getRectModifier()->setRectRadiusWithValue(
            nativeNode, parsedValue.Value(), static_cast<int32_t>(parsedValue.Unit()), AceType::RawPtr(resObj));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RectBridge::ResetRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getRectModifier()->resetRectRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG