/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_lazy_grid_layout_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue LazyGridLayoutBridge::SetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> arg_size = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());

    CalcDimension size;
    std::string calcStr;
    struct ArkUIResourceLength columnGap = { 0.0, 0, nullptr };
    if (arg_size->IsUndefined() || !ArkTSUtils::ParseJsLengthMetrics(vm, arg_size, size)) {
        GetArkUINodeModifiers()->getLazyGridLayoutModifier()->resetColumnsGap(nativeNode);
    } else {
        if (size.Unit() == DimensionUnit::CALC) {
            columnGap.unit = static_cast<int32_t>(DimensionUnit::CALC);
            calcStr = size.CalcValue();
            columnGap.string = calcStr.c_str();
            GetArkUINodeModifiers()->getLazyGridLayoutModifier()->setColumnsGap(nativeNode, &columnGap);
        } else {
            columnGap.value = size.Value();
            columnGap.unit = static_cast<int32_t>(size.Unit());
            columnGap.string = calcStr.c_str();
            GetArkUINodeModifiers()->getLazyGridLayoutModifier()->setColumnsGap(nativeNode, &columnGap);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyGridLayoutBridge::ResetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getLazyGridLayoutModifier()->resetColumnsGap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyGridLayoutBridge::SetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> arg_size = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());

    CalcDimension size;
    std::string calcStr;
    struct ArkUIResourceLength rowsGap = { 0.0, 0, nullptr };
    if (arg_size->IsUndefined() || !ArkTSUtils::ParseJsLengthMetrics(vm, arg_size, size)) {
        GetArkUINodeModifiers()->getLazyGridLayoutModifier()->resetRowsGap(nativeNode);
    } else {
        if (size.Unit() == DimensionUnit::CALC) {
            rowsGap.unit = static_cast<int32_t>(DimensionUnit::CALC);
            calcStr = size.CalcValue();
            rowsGap.string = calcStr.c_str();
            GetArkUINodeModifiers()->getLazyGridLayoutModifier()->setRowsGap(nativeNode, &rowsGap);
        } else {
            rowsGap.value = size.Value();
            rowsGap.unit = static_cast<int32_t>(size.Unit());
            rowsGap.string = calcStr.c_str();
            GetArkUINodeModifiers()->getLazyGridLayoutModifier()->setRowsGap(nativeNode, &rowsGap);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyGridLayoutBridge::ResetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getLazyGridLayoutModifier()->resetRowsGap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyVGridLayoutBridge::SetColumnsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> arg_columnsTemplate = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    if (arg_columnsTemplate->IsUndefined() || !arg_columnsTemplate->IsString(vm)) {
        GetArkUINodeModifiers()->getLazyGridLayoutModifier()->resetColumnsTemplate(nativeNode);
    } else {
        std::string columnsTemplate = arg_columnsTemplate->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getLazyGridLayoutModifier()->setColumnsTemplate(nativeNode, columnsTemplate.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyVGridLayoutBridge::ResetColumnsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getLazyGridLayoutModifier()->resetColumnsTemplate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}
