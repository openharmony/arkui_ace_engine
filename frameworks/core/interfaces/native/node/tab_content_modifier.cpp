/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/tab_content_modifier.h"
#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG {
namespace NodeModifier {
const ArkUITabContentModifier* GetTabContentModifier()
{
    static const ArkUITabContentModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TabContent");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUITabContentModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUITabContentModifier* GetCJUITabContentModifier()
{
    static const CJUITabContentModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TabContent");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const CJUITabContentModifier*>(module->GetCjModifier());
    }
    return cachedModifier;
}

const ArkUITabContentCustomModifier* GetTabContentCustomModifier()
{
    static const ArkUITabContentCustomModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TabContent");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier =
            reinterpret_cast<const ArkUITabContentCustomModifier*>(module->GetCustomModifier("customModifier"));
    }
    return cachedModifier;
}
}
} // namespace OHOS::Ace::NG
