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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_counter_bridge.h"

#include "base/utils/string_utils.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components_ng/pattern/counter/counter_model_ng.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue CounterBridge::SetEnableInc(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsUndefined() || !secondArg->IsBoolean()) {
        GetArkUIInternalNodeAPI()->GetCounterModifier().SetEnableInc(nativeNode, true);
        return panda::JSValueRef::Undefined(vm);
    }
    bool flag = secondArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCounterModifier().SetEnableInc(nativeNode, flag);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CounterBridge::ResetEnableInc(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCounterModifier().ReSetEnableInc(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CounterBridge::SetEnableDec(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsUndefined() || !secondArg->IsBoolean()) {
        GetArkUIInternalNodeAPI()->GetCounterModifier().SetEnableDec(nativeNode, true);
        return panda::JSValueRef::Undefined(vm);
    }
    bool flag = secondArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCounterModifier().SetEnableDec(nativeNode, flag);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CounterBridge::ResetEnableDec(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCounterModifier().ReSetEnableDec(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}
