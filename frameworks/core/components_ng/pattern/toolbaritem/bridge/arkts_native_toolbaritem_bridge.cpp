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

#include "core/components_ng/pattern/toolbaritem/bridge/arkts_native_toolbaritem_bridge.h"

#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_PLACEMENT = static_cast<int32_t>(ToolBarItemPlacement::TOP_BAR_LEADING);
constexpr int32_t TOP_BAR_TRAILING = static_cast<int32_t>(ToolBarItemPlacement::TOP_BAR_TRAILING);
} // namespace

panda::Local<panda::JSValueRef> ToolBarItemBridge::Create(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    int32_t count = runtimeCallInfo->GetArgsNumber();
    auto firstArg = runtimeCallInfo->GetCallArgRef(0);
    int32_t placement = DEFAULT_PLACEMENT;
    if (count == 1 && !firstArg->IsUndefined() && firstArg->IsObject(vm)) {
        auto obj = firstArg->ToObject(vm);
        auto placementArg = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "placement"));
        if (placementArg->IsNumber() && placementArg->Int32Value(vm) == TOP_BAR_TRAILING) {
            placement = TOP_BAR_TRAILING;
        }
    }
    GetArkUINodeModifiers()->getToolBarItemModifier()->create(static_cast<ArkUI_Uint32>(placement));
    return panda::JSValueRef::Undefined(vm);
}

void ToolBarItemBridge::RegisterToolBarItemAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    auto toolBarItem = panda::ObjectRef::New(vm);
    toolBarItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "create"),
        panda::FunctionRef::New(vm, ToolBarItemBridge::Create));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "toolBarItem"), toolBarItem);
}
} // namespace OHOS::Ace::NG
