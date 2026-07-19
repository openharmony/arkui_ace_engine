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

#include "core/interfaces/native/node/node_swiper_modifier.h"

#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG {
namespace NodeModifier {
const ArkUISwiperModifier* GetSwiperModifier()
{
    static const ArkUISwiperModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Swiper");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUISwiperModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUISwiperModifier* GetCJUISwiperModifier()
{
    static const CJUISwiperModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Swiper");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const CJUISwiperModifier*>(module->GetCjModifier());
    }
    return cachedModifier;
}

const ArkUISwiperCustomModifier* GetSwiperCustomModifier()
{
    static const ArkUISwiperCustomModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Swiper");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier =
            reinterpret_cast<const ArkUISwiperCustomModifier*>(module->GetCustomModifier("swiperCustomModifier"));
    }
    return cachedModifier;
}

void ResetSwiperOnContentDidScroll(ArkUINodeHandle node)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetSwiperModifier();
    CHECK_NULL_VOID(modifier);
    CHECK_NULL_VOID(modifier->resetSwiperOnContentDidScroll);
    modifier->resetSwiperOnContentDidScroll(node);
}

} // namespace NodeModifier
} // namespace OHOS::Ace::NG
