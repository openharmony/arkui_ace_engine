/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/node_button_modifier.h"

#include "base/log/log_wrapper.h"
#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG::NodeModifier {
ACE_FORCE_EXPORT const ArkUIButtonModifier* GetButtonModifier()
{
    static const ArkUIButtonModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Button");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUIButtonModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

ACE_FORCE_EXPORT const CJUIButtonModifier* GetCJUIButtonModifier()
{
    static const CJUIButtonModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Button");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const CJUIButtonModifier*>(module->GetCjModifier());
    }
    return cachedModifier;
}

ACE_FORCE_EXPORT const ArkUIButtonCustomModifier* GetButtonCustomModifier()
{
    static const ArkUIButtonCustomModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Button");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier =
            reinterpret_cast<const ArkUIButtonCustomModifier*>(module->GetCustomModifier("customModifier"));
    }
    return cachedModifier;
}
} // namespace OHOS::Ace::NG::NodeModifier