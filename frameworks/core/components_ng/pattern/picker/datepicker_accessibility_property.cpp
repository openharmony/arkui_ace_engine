/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/picker/datepicker_accessibility_property.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"

namespace OHOS::Ace::NG {
std::string DatePickerAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto pattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(pattern, "");

    auto pickerDate = pattern->GetCurrentDate();

    if (!pattern->IsShowLunar()) {
        return std::to_string(pickerDate.GetYear()) + "-" + std::to_string(pickerDate.GetMonth()) + "-" +
               std::to_string(pickerDate.GetDay());
    } else {
        auto lunarDate = pattern->SolarToLunar(pickerDate);
        return std::to_string(lunarDate.year) + "-" + std::to_string(lunarDate.month) + "-" +
               std::to_string(lunarDate.day);
    }
}
} // namespace OHOS::Ace::NG
