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

#include "core/components_ng/pattern/shape/bridge/arkts_native_line_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/line_model_ng.h"
#include "core/interfaces/native/node/line_modifier.h"
#include "core/components_ng/pattern/shape/shape_abstract_model.h"
#include "core/components_ng/pattern/shape/bridge/arkts_native_common_shape_bridge.h"
namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
}

void LineBridge::RegisterLineAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setStartPoint", "resetStartPoint", "setEndPoint", "resetEndPoint" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LineBridge::CreateLine),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LineBridge::SetStartPoint),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LineBridge::ResetStartPoint),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LineBridge::SetEndPoint),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LineBridge::ResetEndPoint),
    };

    auto line = panda::ObjectRef::NewWithNamedProperties(vm,
        sizeof(functionNames) / sizeof(functionNames[0]), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "line"), line);
}

ArkUINativeModuleValue LineBridge::CreateLine(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    GetArkUINodeModifiers()->getLineModifier()->createLine();

    CalcDimension width;
    CalcDimension height;
    if (runtimeCallInfo->GetArgsNumber() > 0 && firstArg->IsObject(vm)) {
        auto nativeNode = reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
        CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
        auto paramObj = firstArg->ToObject(vm);
        auto widthVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "width"));
        if (!widthVal->IsUndefined()) {
            RefPtr<ResourceObject> widthResObj;
            CommonShapeBridge::ParseJsValue(vm, widthVal, width, widthResObj, true);
            if (LessNotEqual(width.Value(), 0.0)) {
                width.SetValue(0.0);
            }
            GetArkUINodeModifiers()->getCommonShapeModifier()->setShapeWidth(
                nativeNode, width.Value(), static_cast<int32_t>(width.Unit()), AceType::RawPtr(widthResObj));
        }
        auto heightVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "height"));
        if (!heightVal->IsUndefined()) {
            RefPtr<ResourceObject> heightResObj;
            CommonShapeBridge::ParseJsValue(vm, heightVal, height, heightResObj, false);
            if (LessNotEqual(height.Value(), 0.0)) {
                height.SetValue(0.0);
            }
            GetArkUINodeModifiers()->getCommonShapeModifier()->setShapeHeight(
                nativeNode, height.Value(), static_cast<int32_t>(height.Unit()), AceType::RawPtr(heightResObj));
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LineBridge::SetStartPoint(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    bool isJsView = ArkTSUtils::IsJsView(vm, firstArg);
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsArray(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getLineModifier()->resetStartPoint(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }

    auto arrayVal = Local<panda::ArrayRef>(secondArg);
    auto length = ArkTSUtils::GetArrayLength(vm, arrayVal);
    if (length <= 0) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getLineModifier()->resetStartPoint(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension start;
    CalcDimension end;
    RefPtr<ResourceObject> startResObj;
    RefPtr<ResourceObject> endResObj;
    std::string calcStr;
    Local<JSValueRef> startItem = panda::ArrayRef::GetValueAt(vm, arrayVal, 0);
    Local<JSValueRef> endItem = panda::ArrayRef::GetValueAt(vm, arrayVal, 1);
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, startItem, start, startResObj, false)) {
        start = CalcDimension(0, DimensionUnit::VP);
    }
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, endItem, end, endResObj, false)) {
        end = CalcDimension(0, DimensionUnit::VP);
    }
    std::vector<RefPtr<ResourceObject>> resObjArray = { startResObj, endResObj };

    std::vector<ArkUI_Float32> pointValues;
    std::vector<int32_t> pointUnits;
    std::vector<const char*> pointStr;
    pointUnits.push_back(static_cast<int>(start.Unit()));
    pointUnits.push_back(static_cast<int>(end.Unit()));
    if (start.Unit() == DimensionUnit::CALC) {
        pointValues.push_back(0);
        pointStr.push_back(start.CalcValue().c_str());
    } else {
        pointValues.push_back(start.Value());
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
        pointUnits.data(), pointStr.data(), resObjArray.data());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LineBridge::ResetStartPoint(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getLineModifier()->resetStartPoint(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LineBridge::SetEndPoint(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    bool isJsView = ArkTSUtils::IsJsView(vm, firstArg);
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsArray(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getLineModifier()->resetEndPoint(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }

    auto arrayVal = Local<panda::ArrayRef>(secondArg);
    auto length = ArkTSUtils::GetArrayLength(vm, arrayVal);
    if (length <= 0) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getLineModifier()->resetEndPoint(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension start;
    CalcDimension end;
    RefPtr<ResourceObject> startResObj;
    RefPtr<ResourceObject> endResObj;
    std::string calcStr;
    Local<JSValueRef> startItem = panda::ArrayRef::GetValueAt(vm, arrayVal, 0);
    Local<JSValueRef> endItem = panda::ArrayRef::GetValueAt(vm, arrayVal, 1);
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, startItem, start, startResObj, false)) {
        start = CalcDimension(0, DimensionUnit::VP);
    }
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, endItem, end, endResObj, false)) {
        end = CalcDimension(0, DimensionUnit::VP);
    }
    std::vector<RefPtr<ResourceObject>> resObjArray = { startResObj, endResObj };

    std::vector<ArkUI_Float32> pointValues;
    std::vector<int32_t> pointUnits;
    std::vector<const char*> pointStr;
    pointUnits.push_back(static_cast<int>(start.Unit()));
    pointUnits.push_back(static_cast<int>(end.Unit()));
    if (start.Unit() == DimensionUnit::CALC) {
        pointValues.push_back(0);
        pointStr.push_back(start.CalcValue().c_str());
    } else {
        pointValues.push_back(start.Value());
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
        pointValues.data(), pointUnits.data(), pointStr.data(), resObjArray.data());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LineBridge::ResetEndPoint(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getLineModifier()->resetEndPoint(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
