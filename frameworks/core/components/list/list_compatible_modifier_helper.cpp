/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components/list/list_compatible_modifier_helper.h"

#include "ui/base/utils/utils.h"

#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace {
const ArkUIListCompatibleModifier* ListCompatibleModifierHelper::GetListCompatibleModifier()
{
    static const ArkUIListCompatibleModifier* modifier = nullptr;
    if (!modifier) {
        auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("list");
        CHECK_NULL_RETURN(loader, nullptr);
        modifier = reinterpret_cast<const ArkUIListCompatibleModifier*>(loader->GetCustomModifier());
    }
    return modifier;
}
const ArkUIListItemCompatibleModifier* ListCompatibleModifierHelper::GetListItemCompatibleModifier()
{
    static const ArkUIListItemCompatibleModifier* modifier = nullptr;
    if (!modifier) {
        auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("list-item");
        CHECK_NULL_RETURN(loader, nullptr);
        modifier = reinterpret_cast<const ArkUIListItemCompatibleModifier*>(loader->GetCustomModifier());
    }
    return modifier;
}
} // OHOS::Ace