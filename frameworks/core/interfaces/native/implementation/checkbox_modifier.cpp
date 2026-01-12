/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "core/common/dynamic_module_helper.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::NG::GeneratedModifier {
#ifdef ACE_UNITTEST
const GENERATED_ArkUICheckboxModifier* GetCheckboxStaticModifier();
#endif
const GENERATED_ArkUICheckboxModifier* GetCheckboxModifier()
{
#ifdef ACE_UNITTEST
    return GetCheckboxStaticModifier();
#else
    static const GENERATED_ArkUICheckboxModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Checkbox");
        if (module == nullptr) {
            LOGF("Can't find checkbox dynamic module");
            abort();
        }
        cachedModifier = reinterpret_cast<const GENERATED_ArkUICheckboxModifier*>(module->GetStaticModifier());
    }
    return cachedModifier;
#endif
}
} // namespace OHOS::Ace::NG::GeneratedModifier
