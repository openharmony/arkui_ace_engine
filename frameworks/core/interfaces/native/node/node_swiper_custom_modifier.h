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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_SWIPER_CUSTOM_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_SWIPER_CUSTOM_MODIFIER_H

#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/swiper/bridge/swiper_custom_modifier.h"

namespace OHOS::Ace::NG {

static const ArkUISwiperCustomModifier* GetSwiperCustomModifier()
{
    static const ArkUISwiperCustomModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Swiper");
        if (module) {
            cachedModifier = reinterpret_cast<const ArkUISwiperCustomModifier*>(
                module->GetCustomModifier("swiperCustomModifier"));
        }
    }
    return cachedModifier;
}

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_SWIPER_CUSTOM_MODIFIER_H
