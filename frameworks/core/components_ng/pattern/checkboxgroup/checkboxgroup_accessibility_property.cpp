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

#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_accessibility_property.h"

#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
#include "accessibility_element_info.h"
#endif

#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"

namespace OHOS::Ace::NG {
bool CheckBoxGroupAccessibilityProperty::IsCheckable() const
{
    return true;
}

bool CheckBoxGroupAccessibilityProperty::IsChecked() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, false);
    auto selectStatus = paintProperty->GetSelectStatus();
    if (selectStatus == CheckBoxGroupPaintProperty::SelectStatus::ALL) {
        return true;
    }
    return false;
}

std::string CheckBoxGroupAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto checkBoxEventHub = frameNode->GetOrCreateEventHub<NG::CheckBoxGroupEventHub>();
    auto groupName = checkBoxEventHub ? checkBoxEventHub->GetGroupName() : "";
    return groupName;
}

int32_t CheckBoxGroupAccessibilityProperty::GetCollectionItemCounts() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, 0);
    auto checkBoxGroupPattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    CHECK_NULL_RETURN(checkBoxGroupPattern, 0);
    auto groupManager = checkBoxGroupPattern->GetGroupManager();
    CHECK_NULL_RETURN(groupManager, 0);
    auto checkBoxGroupEventHub = checkBoxGroupPattern->GetOrCreateEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_RETURN(checkBoxGroupEventHub, 0);
    auto group = checkBoxGroupEventHub->GetGroupName();
    auto list = groupManager->GetCheckboxList(group);
    return list.size();
}

void CheckBoxGroupAccessibilityProperty::GetExtraElementInfo(Accessibility::ExtraElementInfo& extraElementInfo)
{
#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto checkBoxGroupPaintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(checkBoxGroupPaintProperty);

    auto checkBoxGroupSelectStatus = checkBoxGroupPaintProperty->GetSelectStatus();

    extraElementInfo.SetExtraElementInfo(
        "CheckboxGroupSelectedStatus", static_cast<int32_t>(checkBoxGroupSelectStatus));
#endif
}
} // namespace OHOS::Ace::NG