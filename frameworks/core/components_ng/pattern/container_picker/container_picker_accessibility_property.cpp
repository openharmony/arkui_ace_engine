/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/container_picker/container_picker_accessibility_property.h"

#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"

namespace OHOS::Ace::NG {
std::string ContainerPickerAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto pickerPattern = frameNode->GetPattern<ContainerPickerPattern>();
    CHECK_NULL_RETURN(pickerPattern, "");
    return pickerPattern->GetTextOfCurrentChild();
}

int32_t ContainerPickerAccessibilityProperty::GetCurrentIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto pickerPattern = frameNode->GetPattern<ContainerPickerPattern>();
    CHECK_NULL_RETURN(pickerPattern, -1);
    return pickerPattern->GetTotalCount() < 1 ? -1 : pickerPattern->GetSelectedIndex();
}

int32_t ContainerPickerAccessibilityProperty::GetBeginIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto pickerPattern = frameNode->GetPattern<ContainerPickerPattern>();
    CHECK_NULL_RETURN(pickerPattern, -1);
    return pickerPattern->GetTotalCount() < 1 ? -1 : pickerPattern->GetStartIndex();
}

int32_t ContainerPickerAccessibilityProperty::GetEndIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto pickerPattern = frameNode->GetPattern<ContainerPickerPattern>();
    CHECK_NULL_RETURN(pickerPattern, -1);
    return pickerPattern->GetTotalCount() < 1 ? -1 : pickerPattern->GetEndIndex();
}

AccessibilityValue ContainerPickerAccessibilityProperty::GetAccessibilityValue() const
{
    AccessibilityValue result;
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, result);
    auto pickerPattern = frameNode->GetPattern<ContainerPickerPattern>();
    CHECK_NULL_RETURN(pickerPattern, result);

    result.min = 0;
    result.max = pickerPattern->GetTotalCount() < 1 ? 0 : pickerPattern->GetTotalCount() - 1;
    result.current = pickerPattern->GetSelectedIndex();
    return result;
}

bool ContainerPickerAccessibilityProperty::IsScrollable() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto pickerPattern = frameNode->GetPattern<ContainerPickerPattern>();
    CHECK_NULL_RETURN(pickerPattern, false);
    return pickerPattern->GetTotalCount() > 1;
}

int32_t ContainerPickerAccessibilityProperty::GetCollectionItemCounts() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto pickerPattern = frameNode->GetPattern<ContainerPickerPattern>();
    CHECK_NULL_RETURN(pickerPattern, -1);
    return pickerPattern->GetTotalCount();
}

void ContainerPickerAccessibilityProperty::SetSpecificSupportAction()
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto pickerPattern = frameNode->GetPattern<ContainerPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);
    if (IsScrollable()) {
        if (pickerPattern->IsLoop()) {
            AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
            AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
        } else {
            if (GetCurrentIndex() > 0) {
                AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
            }

            if (GetCurrentIndex() < GetCollectionItemCounts() - 1) {
                AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
            }
        }
    }
}
} // namespace OHOS::Ace::NG
