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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_row_split_bridge.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue RowSplitBridge::SetResizable(ArkUIRuntimeCallInfo *runtimeCallInfo)
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
    GetArkUINodeModifiers()->getRowSplitModifier()->setRowSplitResizable(nativeNode, resizable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RowSplitBridge::ResetResizable(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRowSplitModifier()->resetRowSplitResizable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}
