/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/lazy_grid_layout_modifier.h"

#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/lazy_grid_layout/bridge/lazy_grid_layout_custom_modifier.h"

namespace OHOS::Ace::NG {
namespace NodeModifier {
const ArkUILazyGridLayoutModifier* GetLazyGridLayoutModifier()
{
    static const ArkUILazyGridLayoutModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("LazyVGridLayout");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUILazyGridLayoutModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const ArkUILazyGridLayoutCustomModifier* GetLazyGridLayoutCustomModifier()
{
    static const ArkUILazyGridLayoutCustomModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("LazyVGridLayout");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUILazyGridLayoutCustomModifier*>(
            module->GetCustomModifier("customModifier"));
    }
    return cachedModifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
