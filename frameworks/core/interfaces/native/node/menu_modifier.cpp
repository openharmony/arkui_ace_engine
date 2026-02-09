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
#include "core/interfaces/native/node/menu_modifier.h"

#include "base/log/log_wrapper.h"
#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG {
#ifdef ACE_UNITTEST
    const ArkUIMenuModifier* GetMenuDynamicModifier();
#endif
namespace NodeModifier {
const ArkUIMenuModifier* GetMenuModifier()
{
#ifdef ACE_UNITTEST
    return GetMenuDynamicModifier();
#else
    static const ArkUIMenuModifier* modifier = nullptr;
    if (modifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Menu");
        if (module == nullptr) {
            LOGF("Can't find Menu dynamic module");
            abort();
        }
        modifier = reinterpret_cast<const ArkUIMenuModifier*>(module->GetDynamicModifier());
    }
    return modifier;
#endif
}

const CJUIMenuModifier* GetCJUIMenuModifier()
{
    static const CJUIMenuModifier* modifier = nullptr;
    if (modifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Menu");
        if (module == nullptr) {
            LOGF("Can't find Menu dynamic module");
            abort();
        }
        modifier = reinterpret_cast<const CJUIMenuModifier*>(module->GetCjModifier());
    }
    return modifier;
}

#ifndef ACE_UNITTEST
const ArkUIMenuInnerModifier* GetMenuInnerModifier()
{
    static const ArkUIMenuInnerModifier* modifier = nullptr;
    if (modifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Menu");
        if (module == nullptr) {
            LOGF("Can't find Menu dynamic module");
            abort();
        }
        modifier = reinterpret_cast<const ArkUIMenuInnerModifier*>(module->GetCustomModifier("menuInnerModifier"));
    }
    return modifier;
}

const ArkUIMenuViewInnerModifier* GetMenuViewInnerModifier()
{
    static const ArkUIMenuViewInnerModifier* modifier = nullptr;
    if (modifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Menu");
        if (module == nullptr) {
            LOGF("Can't find Menu dynamic module");
            abort();
        }
        modifier =
            reinterpret_cast<const ArkUIMenuViewInnerModifier*>(module->GetCustomModifier("menuViewInnerModifier"));
    }
    return modifier;
}

const ArkUIMenuManagerInnerModifier* GetMenuManagerInnerModifier()
{
    static const ArkUIMenuManagerInnerModifier* modifier = nullptr;
    if (modifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Menu");
        if (module == nullptr) {
            LOGF("Can't find Menu dynamic module");
            abort();
        }
        modifier =
            reinterpret_cast<const ArkUIMenuManagerInnerModifier*>(
                module->GetCustomModifier("menuManagerInnerModifier"));
    }
    return modifier;
}
#endif
} // namespace NodeModifier
} // namespace OHOS::Ace::NG