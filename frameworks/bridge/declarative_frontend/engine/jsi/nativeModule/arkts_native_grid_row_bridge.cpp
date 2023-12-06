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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_grid_row_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue GridRowBridge::SetAlignItems(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsNumber()) {
        int32_t alignItem = secondArg->Int32Value(vm);
        if (alignItem == static_cast<int32_t>(OHOS::Ace::FlexAlign::FLEX_START) ||
            alignItem == static_cast<int32_t>(OHOS::Ace::FlexAlign::FLEX_END) ||
            alignItem == static_cast<int32_t>(OHOS::Ace::FlexAlign::CENTER) ||
            alignItem == static_cast<int32_t>(OHOS::Ace::FlexAlign::STRETCH)) {
            GetArkUIInternalNodeAPI()->GetGridRowModifier().SetAlignItems(nativeNode, alignItem);
        } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            GetArkUIInternalNodeAPI()->GetGridRowModifier().SetAlignItems(nativeNode,
                static_cast<int32_t>(OHOS::Ace::FlexAlign::FLEX_START));
        }
    } else {
        GetArkUIInternalNodeAPI()->GetGridRowModifier().ResetAlignItems(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::ResetAlignItems(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridRowModifier().ResetAlignItems(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}

