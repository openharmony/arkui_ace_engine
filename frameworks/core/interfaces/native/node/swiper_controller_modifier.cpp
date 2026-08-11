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
#include "core/interfaces/native/node/swiper_controller_modifier.h"

#include "core/common/dynamic_module_helper.h"
#include "core/interfaces/native/node/node_swiper_modifier.h"
#include "core/components_ng/pattern/swiper/bridge/swiper_controller_modifier_api.h"

namespace OHOS::Ace::NG {
namespace NodeModifier {
const ArkUISwiperControllerModifier* GetSwiperControllerModifier()
{
    static const ArkUISwiperControllerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Swiper");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier =
            reinterpret_cast<const ArkUISwiperControllerModifier*>(module->GetCustomModifier("swiperArkController"));
    }
    return cachedModifier;
}

const CJUISwiperControllerModifier* GetCJUISwiperControllerModifier()
{
    static const CJUISwiperControllerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Swiper");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier =
            reinterpret_cast<const CJUISwiperControllerModifier*>(module->GetCustomModifier("swiperCjController"));
    }
    return cachedModifier;
}

const ArkUICustomSwiperControllerModifier* GetCustomSwiperControllerModifier()
{
    static const ArkUICustomSwiperControllerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Swiper");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUICustomSwiperControllerModifier*>(
            module->GetCustomModifier("swiperController"));
    }
    return cachedModifier;
}
}
}
