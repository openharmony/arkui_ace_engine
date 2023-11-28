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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_panel_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"

using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
ArkUINativeModuleValue PanelBridge::SetShowCloseIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsNull()) {
        GetArkUIInternalNodeAPI()->GetPanelModifier().SetShowCloseIcon(nativeNode, false);
        return panda::JSValueRef::Undefined(vm);
    }
    bool boolValue = false;
    if (secondArg->IsBoolean()) {
        boolValue = secondArg->ToBoolean(vm)->Value();
    }
    GetArkUIInternalNodeAPI()->GetPanelModifier().SetShowCloseIcon(nativeNode, boolValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetShowCloseIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetPanelModifier().ResetShowCloseIcon(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetDragBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsNull()) {
        GetArkUIInternalNodeAPI()->GetPanelModifier().SetShowCloseIcon(nativeNode, false);
        return panda::JSValueRef::Undefined(vm);
    }
    bool boolValue = false;
    if (secondArg->IsBoolean()) {
        boolValue = secondArg->ToBoolean(vm)->Value();
    }
    GetArkUIInternalNodeAPI()->GetPanelModifier().SetDragBar(nativeNode, boolValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetDragBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetPanelModifier().ResetDragBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetShow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) &&
        (secondArg->IsUndefined() || secondArg->IsNull())) {
        GetArkUIInternalNodeAPI()->GetPanelModifier().SetShow(nativeNode, false);
        return panda::JSValueRef::Undefined(vm);
    } else {
        GetArkUIInternalNodeAPI()->GetPanelModifier().SetShow(nativeNode, secondArg->ToBoolean(vm)->Value());
        return panda::JSValueRef::Undefined(vm);
    }
}

ArkUINativeModuleValue PanelBridge::ResetShow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetPanelModifier().ResetShow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
