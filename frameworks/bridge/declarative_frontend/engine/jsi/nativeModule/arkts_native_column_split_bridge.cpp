/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "base/geometry/dimension.h"
#include "core/interfaces/native/node/node_api.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_column_split_bridge.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;

ArkUINativeModuleValue ColumnSplitBridge::SetResizable(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> resizableArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    bool resizable = false;
    if (resizableArg->IsBoolean()) {
        resizable = resizableArg->ToBoolean(vm)->BooleaValue(vm);
    }
    GetArkUINodeModifiers()->getColumnSplitModifier()->setColumnSplitResizable(nativeNode, resizable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnSplitBridge::ResetResizable(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getColumnSplitModifier()->resetColumnSplitResizable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnSplitBridge::SetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> startMarginArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> endMarginArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    CalcDimension startMargin(0.0, DimensionUnit::VP);
    CalcDimension endMargin(0.0, DimensionUnit::VP);
    RefPtr<ResourceObject> startMarginResObj;
    RefPtr<ResourceObject> endMarginResObj;
    ArkTSUtils::ParseJsDimensionVp(vm, startMarginArg, startMargin, startMarginResObj);
    ArkTSUtils::ParseJsDimensionVp(vm, endMarginArg, endMargin, endMarginResObj);
    auto startMarginRawPtr = AceType::RawPtr(startMarginResObj);
    auto endMarginRawPtr = AceType::RawPtr(endMarginResObj);
    GetArkUINodeModifiers()->getColumnSplitModifier()->setColumnSplitDivider(nativeNode, startMargin.Value(),
        static_cast<int32_t>(startMargin.Unit()), endMargin.Value(), static_cast<int32_t>(endMargin.Unit()),
        startMarginRawPtr, endMarginRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnSplitBridge::ResetDivider(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getColumnSplitModifier()->resetColumnSplitDivider(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
