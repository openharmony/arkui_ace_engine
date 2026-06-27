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

#include "core/interfaces/native/node/node_date_picker_modifier.h"

#include "bridge/common/utils/utils.h"
#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG {
#ifdef ACE_UNITTEST
namespace NodeModifier {
const ArkUIDatePickerModifier* GetDatePickerDynamicModifier();
const CJUIDatePickerModifier* GetCJUIDatepickerModifier();
} // namespace NodeModifier
namespace DatePickerUtil {
const DatepickerCustomModifier* GetDatePickerCustomModifier();
} // namespace DatePickerUtil
#endif
namespace NodeModifier {
const ArkUIDatePickerModifier* GetDatePickerModifier()
{
    static const ArkUIDatePickerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ACE_UNITTEST
        cachedModifier = NG::NodeModifier::GetDatePickerDynamicModifier();
#else
        // Dynamically load the independently compiled so library
        // from frameworks/core/components_ng/pattern/picker directory
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("DatePicker");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUIDatePickerModifier*>(module->GetDynamicModifier());
#endif
    }
    return cachedModifier;
}

const CJUIDatePickerModifier* GetCJUIDatePickerModifier()
{
    static const CJUIDatePickerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ACE_UNITTEST
        cachedModifier = NG::NodeModifier::GetCJUIDatepickerModifier();
#else
        // Dynamically load the independently compiled so library
        // from frameworks/core/components_ng/pattern/picker directory
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("DatePicker");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const CJUIDatePickerModifier*>(module->GetCjModifier());
#endif
    }
    return cachedModifier;
}

void SetDatePickerOnDateChange(ArkUINodeHandle node, void* extraParam)
{
    static const ArkUIDatePickerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ACE_UNITTEST
        cachedModifier = NG::NodeModifier::GetDatePickerDynamicModifier();
#else
        // Dynamically load the independently compiled so library
        // from frameworks/core/components_ng/pattern/picker directory
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("DatePicker");
        CHECK_NULL_VOID(module);
        cachedModifier = reinterpret_cast<const ArkUIDatePickerModifier*>(module->GetDynamicModifier());
#endif
    }
    cachedModifier->setDatePickerOnDateChangeHandler(node, extraParam);
}

const NG::DatePickerUtil::DatepickerCustomModifier* GetDatepickerCustomModifier()
{
    static const NG::DatePickerUtil::DatepickerCustomModifier* cacheModifier = nullptr;
    if (cacheModifier == nullptr) {
#ifdef ACE_UNITTEST
        cacheModifier = NG::DatePickerUtil::GetDatePickerCustomModifier();
#else
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("DatePicker");
        CHECK_NULL_RETURN(module, nullptr);
        cacheModifier = reinterpret_cast<const NG::DatePickerUtil::DatepickerCustomModifier*>(
            module->GetCustomModifier("customModifier"));
#endif
    }
    return cacheModifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
