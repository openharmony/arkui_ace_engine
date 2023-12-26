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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_radio_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/checkable/checkable_theme.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
ArkUINativeModuleValue RadioBridge::SetRadioChecked(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    bool isCheck = secondArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetRadioModifier().SetRadioChecked(nativeNode, isCheck);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioChecked(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetRadioModifier().ResetRadioChecked(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> checkedBackgroundColor = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> uncheckedBorderColor = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> indicatorColor = runtimeCallInfo->GetCallArgRef(NUM_3);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, panda::NativePointerRef::New(vm, nullptr));
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_RETURN(radioTheme, panda::NativePointerRef::New(vm, nullptr));

    Color checkedBackgroundColorVal;
    if (checkedBackgroundColor->IsNull() || checkedBackgroundColor->IsUndefined() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, checkedBackgroundColor, checkedBackgroundColorVal)) {
        checkedBackgroundColorVal = radioTheme->GetActiveColor();
    }
    Color uncheckedBorderColorVal;
    if (uncheckedBorderColor->IsNull() || uncheckedBorderColor->IsUndefined() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, uncheckedBorderColor, uncheckedBorderColorVal)) {
        uncheckedBorderColorVal = radioTheme->GetInactiveColor();
    }
    Color indicatorColorVal;
    if (indicatorColor->IsNull() || indicatorColor->IsUndefined() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, indicatorColor, indicatorColorVal)) {
        indicatorColorVal = radioTheme->GetPointColor();
    }

    GetArkUIInternalNodeAPI()->GetRadioModifier().SetRadioStyle(nativeNode,
        checkedBackgroundColorVal.GetValue(), uncheckedBorderColorVal.GetValue(), indicatorColorVal.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetRadioModifier().ResetRadioStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}
