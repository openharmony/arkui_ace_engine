/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/lazy_water_flow_layout_modifier.h"

#include <mutex>

#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG {
namespace NodeModifier {
const ArkUILazyWaterFlowLayoutModifier* GetLazyWaterFlowLayoutModifier()
{
    static const ArkUILazyWaterFlowLayoutModifier* cachedModifier = nullptr;
    static std::mutex cachedModifierMutex;
    std::lock_guard<std::mutex> lock(cachedModifierMutex);
    if (!cachedModifier) {
        // LazyWaterFlow is split into its own ArkUI component library and loaded only when first used.
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("LazyVWaterFlowLayout");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUILazyWaterFlowLayoutModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
