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

#include "arkoala_api_generated.h"
#include "ui/base/utils/utils.h"

#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUITimePickerDialogAccessor* GetTimePickerDialogAccessor()
{
    static const GENERATED_ArkUITimePickerDialogAccessor* cachedAccessor = nullptr;
    if (!cachedAccessor) {
        // Dynamically load the independently compiled so library
        // from frameworks/core/components_ng/pattern/time_picker directory
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TimePickerDialog");
        CHECK_NULL_RETURN(module, nullptr);
        cachedAccessor = reinterpret_cast<const GENERATED_ArkUITimePickerDialogAccessor*>(
            module->GetCustomModifier("configurationAccessor"));
    }
    return cachedAccessor;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
