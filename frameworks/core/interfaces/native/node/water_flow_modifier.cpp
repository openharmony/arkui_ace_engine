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
#include "core/interfaces/native/node/water_flow_modifier.h"

#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG {
namespace NodeModifier {
const ArkUIWaterFlowModifier* GetWaterFlowModifier()
{
    static const ArkUIWaterFlowModifier* cachedModifier = nullptr;
    if (!cachedModifier) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("WaterFlow");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUIWaterFlowModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUIWaterFlowModifier* GetCJUIWaterFlowModifier()
{
    static const CJUIWaterFlowModifier* cachedCJModifier = nullptr;
    if (!cachedCJModifier) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("WaterFlow");
        CHECK_NULL_RETURN(module, nullptr);
        cachedCJModifier = reinterpret_cast<const CJUIWaterFlowModifier*>(module->GetCjModifier());
    }
    return cachedCJModifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
