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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_column_split_bridge.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;

ArkUINativeModuleValue ColumnSplitBridge::SetResizeable(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> resizeableArg = runtimeCallInfo->GetCallArgRef(1);
    void *nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    bool resizeable = false;
    if (resizeableArg->IsBoolean()) {
        resizeable = resizeableArg->ToBoolean(vm)->BooleaValue();
    }
    GetArkUIInternalNodeAPI()->GetColumnSplitModifier().SetColumnSplitResizeable(nativeNode, resizeable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnSplitBridge::ResetResizeable(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetColumnSplitModifier().ResetColumnSplitResizeable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnSplitBridge::SetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> startMarginArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> endMarginArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    CalcDimension startMargin(0.0, DimensionUnit::VP);
    CalcDimension endMargin(0.0, DimensionUnit::VP);
    ArkTSUtils::ParseJsDimensionVp(vm, startMarginArg, startMargin);
    ArkTSUtils::ParseJsDimensionVp(vm, endMarginArg, endMargin);
    GetArkUIInternalNodeAPI()->GetColumnSplitModifier().SetColumnSplitDivider(nativeNode, startMargin.Value(),
        static_cast<int32_t>(startMargin.Unit()), endMargin.Value(), static_cast<int32_t>(endMargin.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnSplitBridge::ResetDivider(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetColumnSplitModifier().ResetColumnSplitDivider(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
