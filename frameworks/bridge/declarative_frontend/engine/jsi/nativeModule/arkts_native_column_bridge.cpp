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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_column_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;

ArkUINativeModuleValue ColumnBridge::SetJustifyContent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    int32_t flexAlign = static_cast<int32_t>(FlexAlign::FLEX_START);
    if (secondArg->IsInt()) {
        flexAlign = secondArg->Int32Value(vm);
        if ((flexAlign == static_cast<int32_t>(FlexAlign::FLEX_START)) ||
            (flexAlign == static_cast<int32_t>(FlexAlign::FLEX_END)) ||
            (flexAlign == static_cast<int32_t>(FlexAlign::CENTER)) ||
            (flexAlign == static_cast<int32_t>(FlexAlign::SPACE_BETWEEN)) ||
            (flexAlign == static_cast<int32_t>(FlexAlign::SPACE_AROUND)) ||
            (flexAlign == static_cast<int32_t>(FlexAlign::SPACE_EVENLY))) {
            GetArkUIInternalNodeAPI()->GetColumnModifier().SetColumnJustifyContent(nativeNode, flexAlign);
        } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            GetArkUIInternalNodeAPI()->GetColumnModifier().ResetColumnJustifyContent(nativeNode);
        }
    }
    GetArkUIInternalNodeAPI()->GetColumnModifier().SetColumnJustifyContent(nativeNode, flexAlign);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnBridge::ResetJustifyContent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetColumnModifier().ResetColumnJustifyContent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnBridge::SetAlignItems(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    int32_t value;
    if (secondArg->IsNumber()) {
        value = secondArg->Int32Value(vm);
        if ((value == static_cast<int32_t>(FlexAlign::FLEX_START)) ||
            (value == static_cast<int32_t>(FlexAlign::FLEX_END)) ||
            (value == static_cast<int32_t>(FlexAlign::CENTER)) ||
            (value == static_cast<int32_t>(FlexAlign::STRETCH))) {
            GetArkUIInternalNodeAPI()->GetColumnModifier().SetColumnAlignItems(nativeNode, value);
        } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            GetArkUIInternalNodeAPI()->GetColumnModifier().ResetColumnAlignItems(nativeNode);
        }
    } else {
        GetArkUIInternalNodeAPI()->GetColumnModifier().ResetColumnAlignItems(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnBridge::ResetAlignItems(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetColumnModifier().ResetColumnAlignItems(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}
