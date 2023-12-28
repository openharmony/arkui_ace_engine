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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_toggle_bridge.h"

#include "core/interfaces/native/node/api.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue ToggleBridge::SetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    Color color;
    if (colorArg->IsNull() || colorArg->IsUndefined() || !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
        GetArkUIInternalNodeAPI()->GetToggleModifier().ResetToggleSelectedColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetToggleModifier().SetToggleSelectedColor(nativeNode, color.GetValue());
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetToggleModifier().ResetToggleSelectedColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetSwitchPointColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    Color color;
    if (colorArg->IsNull() || colorArg->IsUndefined() || !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
        GetArkUIInternalNodeAPI()->GetToggleModifier().ResetToggleSwitchPointColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetToggleModifier().SetToggleSwitchPointColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetSwitchPointColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetToggleModifier().ResetToggleSwitchPointColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
