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

#include "core/interfaces/native/node/grid_item_modifier.h"

#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG::NodeModifier {
#ifdef ARKUI_CAPI_UNITTEST
const ArkUIGridItemModifier* GetGridItemDynamicModifier();
const CJUIGridItemModifier* GetCJUIGridItemDynamicModifier();
const GridItemCustomModifier* GetGridItemCustomDynamicModifier();
#endif
const ArkUIGridItemModifier* GetGridItemModifier()
{
    static const ArkUIGridItemModifier* cachedModifier = nullptr;
    if (!cachedModifier) {
#ifdef ARKUI_CAPI_UNITTEST
        cachedModifier = GetGridItemDynamicModifier();
#else
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("GridItem");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUIGridItemModifier*>(module->GetDynamicModifier());
#endif
    }
    return cachedModifier;
}

const CJUIGridItemModifier* GetCJUIGridItemModifier()
{
    static const CJUIGridItemModifier* cachedModifier = nullptr;
    if (!cachedModifier) {
#ifdef ARKUI_CAPI_UNITTEST
        cachedModifier = GetCJUIGridItemDynamicModifier();
#else
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("GridItem");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const CJUIGridItemModifier*>(module->GetCjModifier());
#endif
    }
    return cachedModifier;
}

const NG::GridItemCustomModifier* GetGridItemCustomModifier()
{
    static const NG::GridItemCustomModifier* cachedModifier = nullptr;
    if (!cachedModifier) {
#ifdef ARKUI_CAPI_UNITTEST
        cachedModifier = GetGridItemCustomDynamicModifier();
#else
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("GridItem");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier =
            reinterpret_cast<const NG::GridItemCustomModifier*>(module->GetCustomModifier("GridItemCustom"));
#endif
    }
    return cachedModifier;
}
} // namespace OHOS::Ace::NG::NodeModifier
