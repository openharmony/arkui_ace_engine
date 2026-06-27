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

#include "ui/base/utils/utils.h"
#include "core/common/dynamic_module_helper.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "frameworks/base/log/log_wrapper.h"

namespace OHOS::Ace::NG::GeneratedModifier {
#ifdef ACE_UNITTEST
const GENERATED_ArkUIDatePickerModifier* GetDatePickerStaticModifier();
#endif
const GENERATED_ArkUIDatePickerModifier* GetDatePickerModifier()
{
#ifdef ACE_UNITTEST
    return GetDatePickerStaticModifier();
#else
    static const GENERATED_ArkUIDatePickerModifier* datePickerModifier = nullptr;
    if (datePickerModifier == nullptr) {
        // Dynamically load the independently compiled so library
        // from frameworks/core/components_ng/pattern/picker directory
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("DatePicker");
        CHECK_NULL_RETURN(module, nullptr);
        datePickerModifier = reinterpret_cast<const GENERATED_ArkUIDatePickerModifier*>(module->GetStaticModifier());
    }

    return datePickerModifier;
#endif
}
} // namespace OHOS::Ace::NG::GeneratedModifier
