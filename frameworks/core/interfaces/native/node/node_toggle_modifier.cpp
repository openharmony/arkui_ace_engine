/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
#include "node_toggle_modifier.h"

#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"

namespace OHOS::Ace::NG::NodeModifier {
const ArkUIToggleModifier* GetToggleModifier()
{
    static const ArkUIToggleModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Toggle");
        if (module == nullptr) {
            LOGF_ABORT("Can't find toggle dynamic module");
        }
        cachedModifier = reinterpret_cast<const ArkUIToggleModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUIToggleModifier* GetCJUIToggleModifier()
{
    static const CJUIToggleModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Toggle");
        if (module == nullptr) {
            LOGF_ABORT("Can't find toggle dynamic module");
        }
        cachedModifier = reinterpret_cast<const CJUIToggleModifier*>(module->GetCjModifier());
    }
    return cachedModifier;
}

void SetOnToggleChange(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(node);
    auto* modifier = GetToggleModifier();
    CHECK_NULL_VOID(modifier);
    std::function<void(bool)> onChange = [node, extraParam](const bool isOn) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_TOGGLE_CHANGE;
        event.componentAsyncEvent.data[0].u32 = isOn;
        SendArkUISyncEvent(&event);
    };
    modifier->setToggleOnChange(node, reinterpret_cast<void*>(&onChange));
}

void ResetOnToggleChange(ArkUINodeHandle node)
{
    CHECK_NULL_VOID(node);
    auto* modifier = GetToggleModifier();
    CHECK_NULL_VOID(modifier);
    modifier->resetToggleOnChange(node);
}
} // namespace OHOS::Ace::NG::NodeModifier
