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
#include "core/interfaces/native/node/menu_item_modifier.h"

#include "base/log/log_wrapper.h"
#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG {
namespace NodeModifier {
const ArkUIMenuItemModifier* GetMenuItemModifier()
{
    static const ArkUIMenuItemModifier* modifier = nullptr;
    if (modifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("MenuItem");
        if (module == nullptr) {
            LOGF("Can't find MenuItem dynamic module");
            abort();
        }
        modifier = reinterpret_cast<const ArkUIMenuItemModifier*>(module->GetDynamicModifier());
    }
    return modifier;
}

const CJUIMenuItemModifier* GetCJUIMenuItemModifier()
{
    static const CJUIMenuItemModifier* modifier = nullptr;
    if (modifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("MenuItem");
        if (module == nullptr) {
            LOGF("Can't find MenuItem dynamic module");
            abort();
        }
        modifier = reinterpret_cast<const CJUIMenuItemModifier*>(module->GetCjModifier());
    }
    return modifier;
}

#ifndef ACE_UNITTEST
const ArkUIMenuItemInnerModifier* GetMenuItemInnerModifier()
{
    static const ArkUIMenuItemInnerModifier* modifier = nullptr;
    if (modifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("MenuItem");
        if (module == nullptr) {
            LOGF("Can't find MenuItem dynamic module");
            abort();
        }
        modifier =
            reinterpret_cast<const ArkUIMenuItemInnerModifier*>(module->GetCustomModifier("menuItemInnerModifier"));
    }
    return modifier;
}
#endif
} // namespace NodeModifier
} // namespace OHOS::Ace::NG