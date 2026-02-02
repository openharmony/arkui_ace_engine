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
#include "core/interfaces/native/node/node_timepicker_modifier.h"

#include "ui/base/utils/utils.h"

#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG {
#ifdef ACE_UNITTEST
namespace NodeModifier {
const ArkUITimepickerModifier* GetTimePickerDynamicModifier();
const CJUITimepickerModifier* GetCJUITimePickerModifier();
} // namespace NodeModifier
namespace TimePickerUtil {
const TimepickerCustomModifier* GetTimePickerCustomModifier();
} // namespace TimePickerUtil
#endif
namespace NodeModifier {
const ArkUITimepickerModifier* GetTimepickerModifier()
{
    static const ArkUITimepickerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ACE_UNITTEST
        cachedModifier = NG::NodeModifier::GetTimePickerDynamicModifier();
#else
        // Dynamically load the independently compiled so library
        // from frameworks/core/components_ng/pattern/time_picker directory
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TimePicker");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUITimepickerModifier*>(module->GetDynamicModifier());
#endif
    }
    return cachedModifier;
}

const CJUITimepickerModifier* GetCJUITimepickerModifier()
{
    static const CJUITimepickerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ACE_UNITTEST
        cachedModifier = NG::NodeModifier::GetCJUITimePickerModifier();
#else
        // Dynamically load the independently compiled so library
        // from frameworks/core/components_ng/pattern/time_picker directory
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TimePicker");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const CJUITimepickerModifier*>(module->GetCjModifier());
#endif
    }
    return cachedModifier;
}
void SetTimePickerOnChange(ArkUINodeHandle node, void* extraParam)
{
    static const ArkUITimepickerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ACE_UNITTEST
        cachedModifier = NG::NodeModifier::GetTimePickerDynamicModifier();
#else
        // Dynamically load the independently compiled so library
        // from frameworks/core/components_ng/pattern/time_picker directory
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TimePicker");
        CHECK_NULL_VOID(module);
        cachedModifier = reinterpret_cast<const ArkUITimepickerModifier*>(module->GetDynamicModifier());
#endif
    }
    cachedModifier->setTimePickerOnChangeHandler(node, extraParam);
}

const NG::TimePickerUtil::TimepickerCustomModifier* GetTimepickerCustomModifier()
{
    static const NG::TimePickerUtil::TimepickerCustomModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ACE_UNITTEST
        cachedModifier = NG::TimePickerUtil::GetTimePickerCustomModifier();
#else
        // Dynamically load the independently compiled so library
        // from frameworks/core/components_ng/pattern/time_picker directory
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TimePicker");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const NG::TimePickerUtil::TimepickerCustomModifier*>(
            module->GetCustomModifier("customModifier"));
#endif
    }
    return cachedModifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
