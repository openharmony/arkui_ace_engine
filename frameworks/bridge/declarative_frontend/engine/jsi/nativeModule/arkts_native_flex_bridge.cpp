/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_flex_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "core/components/common/layout/constants.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue FlexBridge::SetFlexInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> directionArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> wrapArg = runtimeCallInfo->GetCallArgRef(2);
    Local<JSValueRef> justifyContentArg = runtimeCallInfo->GetCallArgRef(3);
    Local<JSValueRef> alignItemsArg = runtimeCallInfo->GetCallArgRef(4);
    Local<JSValueRef> alignContentArg = runtimeCallInfo->GetCallArgRef(5);
    Local<JSValueRef> mainArg = runtimeCallInfo->GetCallArgRef(6);
    Local<JSValueRef> crossArg = runtimeCallInfo->GetCallArgRef(7);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    int32_t options[5] = { 0, 0, 0, 1, 0 };
    if (!directionArg->IsNull() && directionArg->IsNumber()) {
        options[0] = directionArg->Int32Value(vm);
    }
    if (!wrapArg->IsNull() && wrapArg->IsNumber()) {
        options[1] = wrapArg->Int32Value(vm);
    }
    if (!justifyContentArg->IsNull() && justifyContentArg->IsNumber()) {
        options[2] = justifyContentArg->Int32Value(vm);
    }
    if (!alignItemsArg->IsNull() && alignItemsArg->IsNumber()) {
        options[3] = alignItemsArg->Int32Value(vm);
    }
    if (!alignContentArg->IsNull() && alignContentArg->IsNumber()) {
        options[4] = alignContentArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getFlexModifier()->setFlexOptions(nativeNode, options, 5);
    if (options[1] != 0) {
        if (!crossArg->IsNull() && !crossArg->IsUndefined()) {
            CalcDimension crossValue;
            if (crossArg->IsObject(vm) && ArkTSUtils::ParseJsLengthMetrics(vm, crossArg, crossValue)) {
                GetArkUINodeModifiers()->getFlexModifier()->setFlexCrossSpace(
                    nativeNode, crossValue.Value(), static_cast<int8_t>(crossValue.Unit()));
            }
        }
    }
    if (!mainArg->IsNull() && !mainArg->IsUndefined()) {
        CalcDimension mainValue;
        if (crossArg->IsObject(vm) && ArkTSUtils::ParseJsLengthMetrics(vm, crossArg, mainValue)) {
            GetArkUINodeModifiers()->getFlexModifier()->setFlexMainSpace(
                nativeNode, mainValue.Value(), static_cast<int8_t>(mainValue.Unit()));
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FlexBridge::ResetFlexInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getFlexModifier()->resetFlexOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}
