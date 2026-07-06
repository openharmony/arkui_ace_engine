/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "base/log/log_wrapper.h"
#include "core/common/dynamic_module_helper.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUISwiperModifier* GetSwiperModifier()
{
    static const GENERATED_ArkUISwiperModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ARKUI_CAPI_UNITTEST
        cachedModifier = GeneratedModifier::GetSwiperModifier();
#else
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Swiper");
        if (module == nullptr) {
            LOGF_ABORT("Can't find swiper dynamic module");
        }
        cachedModifier = reinterpret_cast<const GENERATED_ArkUISwiperModifier*>(
            module->GetCustomModifier("swiperModifier"));
        if (cachedModifier == nullptr) {
            LOGF_ABORT("Can't find swiper static modifier");
        }
#endif
    }
    return cachedModifier;
}
} // namespace OHOS::Ace::NG::GeneratedModifier
