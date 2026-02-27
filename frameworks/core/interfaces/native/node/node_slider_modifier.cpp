/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_slider_modifier.h"

#include "ui/base/utils/utils.h"

#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG {
namespace NodeModifier {
const ArkUISliderModifier *GetSliderModifier()
{
    static const ArkUISliderModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Slider");
        if (module == nullptr) {
            LOGF("Can't find slider dynamic module");
            abort();
        }
        cachedModifier = reinterpret_cast<const ArkUISliderModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUISliderModifier* GetCJUISliderModifier()
{
    static const CJUISliderModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Slider");
        if (module == nullptr) {
            LOGF("Can't find slider dynamic module");
            abort();
        }
        cachedModifier = reinterpret_cast<const CJUISliderModifier*>(module->GetCjModifier());
    }
    return cachedModifier;
}

const ArkUISliderCustomModifier* GetSliderCustomModifier()
{
    static const ArkUISliderCustomModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Slider");
        if (module == nullptr) {
            LOGF("Can't find slider dynamic module");
            abort();
        }
        cachedModifier =
            reinterpret_cast<const ArkUISliderCustomModifier*>(module->GetCustomModifier("customModifier"));
    }
    return cachedModifier;
}

void SetSliderChange(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(node);
    auto* modifier = GetSliderModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setOnSliderChange(node, extraParam);
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
