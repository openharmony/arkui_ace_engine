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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_rich_editor_bridge.h"

#include "core/interfaces/native/node/api.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue RichEditorBridge::SetCopyOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t CopyOptionsValue = static_cast<uint32_t>(CopyOptions::Distributed);
    if (secondArg->IsNumber()) {
        CopyOptionsValue = secondArg->Uint32Value(vm);
        GetArkUIInternalNodeAPI()->GetRichEditorModifier().SetRichEditorCopyOptions(nativeNode, CopyOptionsValue);
    } else {
        GetArkUIInternalNodeAPI()->GetRichEditorModifier().ResetRichEditorCopyOptions(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetCopyOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetRichEditorModifier().ResetRichEditorCopyOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}