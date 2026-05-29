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

#include "core/interfaces/native/node/grid_modifier.h"

#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG::NodeModifier {
#ifdef ARKUI_CAPI_UNITTEST
const ArkUIGridModifier* GetGridDynamicModifier();
const CJUIGridModifier* GetCJUIGridDynamicModifier();
const GridCustomModifier* GetGridCustomDynamicModifier();
#endif
const ArkUIGridModifier* GetGridModifier()
{
    static const ArkUIGridModifier* cachedModifier = nullptr;
    if (!cachedModifier) {
#ifdef ARKUI_CAPI_UNITTEST
        cachedModifier = GetGridDynamicModifier();
#else
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Grid");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUIGridModifier*>(module->GetDynamicModifier());
#endif
    }
    return cachedModifier;
}

const CJUIGridModifier* GetCJUIGridModifier()
{
    static const CJUIGridModifier* cachedModifier = nullptr;
    if (!cachedModifier) {
#ifdef ARKUI_CAPI_UNITTEST
        cachedModifier = GetCJUIGridDynamicModifier();
#else
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Grid");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const CJUIGridModifier*>(module->GetCjModifier());
#endif
    }
    return cachedModifier;
}

const NG::GridCustomModifier* GetGridCustomModifier()
{
    static const NG::GridCustomModifier* cachedModifier = nullptr;
    if (!cachedModifier) {
#ifdef ARKUI_CAPI_UNITTEST
        cachedModifier = GetGridCustomDynamicModifier();
#else
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Grid");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const NG::GridCustomModifier*>(module->GetCustomModifier("GridCustom"));
#endif
    }
    return cachedModifier;
}
} // namespace OHOS::Ace::NG::NodeModifier
