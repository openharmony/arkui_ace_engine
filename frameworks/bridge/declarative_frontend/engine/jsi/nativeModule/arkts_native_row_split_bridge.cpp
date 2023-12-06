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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue RowSplitBridge::SetResizeable(ArkUIRuntimeCallInfo *runtimeCallInfo)
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
    GetArkUIInternalNodeAPI()->GetRowSplitModifier().SetRowSplitResizeable(nativeNode, resizeable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RowSplitBridge::ResetResizeable(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetRowSplitModifier().ResetRowSplitResizeable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}
