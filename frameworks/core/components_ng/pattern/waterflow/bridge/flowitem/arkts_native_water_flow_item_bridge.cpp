/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/waterflow/bridge/flowitem/arkts_native_water_flow_item_bridge.h"

#include "core/components_ng/pattern/waterflow/water_flow_item_model_ng.h"

namespace OHOS::Ace::NG {
void WaterFlowItemBridge::RegisterWaterFlowItemAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create" };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(vm, WaterFlowItemBridge::CreateFlowItem),
    };
    auto flowItem = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "flowItem"), flowItem);
}

ArkUINativeModuleValue WaterFlowItemBridge::CreateFlowItem(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    GetArkUINodeModifiers()->getWaterFlowItemModifier()->create();
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG