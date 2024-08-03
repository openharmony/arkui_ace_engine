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

#include "core/components_ng/pattern/time_picker/timepicker_column_accessibility_property.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MIDDLE_OF_COUNTS = 2;
} // namespace
int32_t TimePickerColumnAccessibilityProperty::GetCollectionItemCounts() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, 0);
    auto pattern = frameNode->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(pattern, 0);
    auto options = pattern->GetOptions();
    auto it = options.find(frameNode);
    if (it != options.end()) {
        return it->second;
    }
    return 0;
}

int32_t TimePickerColumnAccessibilityProperty::GetCurrentIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto pattern = frameNode->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(pattern, -1);
    return pattern->GetCurrentIndex();
}

int32_t TimePickerColumnAccessibilityProperty::GetEndIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto pattern = frameNode->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(pattern, -1);
    auto itemCounts = GetCollectionItemCounts();
    if (itemCounts == 0) {
        return -1;
    }
    if (pattern->NotLoopOptions()) {
        return itemCounts - 1;
    }
    auto currentIndex = pattern->GetCurrentIndex();
    return (itemCounts + static_cast<int32_t>(currentIndex) +
               static_cast<int32_t>(pattern->GetShowCount()) / MIDDLE_OF_COUNTS) % itemCounts;
}

int32_t TimePickerColumnAccessibilityProperty::GetBeginIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto pattern = frameNode->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(pattern, -1);
    auto itemCounts = GetCollectionItemCounts();
    if (itemCounts == 0) {
        return -1;
    }
    if (pattern->NotLoopOptions()) {
        return 0;
    }
    auto currentIndex = pattern->GetCurrentIndex();
    return (itemCounts + static_cast<int32_t>(currentIndex) -
               static_cast<int32_t>(pattern->GetShowCount()) / MIDDLE_OF_COUNTS) %
           itemCounts;
}

std::string TimePickerColumnAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto blendNode = DynamicCast<FrameNode>(frameNode->GetParent());
    CHECK_NULL_RETURN(blendNode, "");
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_RETURN(stackNode, "");
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_RETURN(parentNode, "");
    auto timePickerRowPattern = parentNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerRowPattern, "");
    auto pattern = frameNode->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(pattern, "");
    auto index = pattern->GetCurrentIndex();
    auto options = pattern->GetOptions();
    auto it = options.find(frameNode);
    if (it != options.end()) {
        if (it->second < index) {
            return "";
        }
        return timePickerRowPattern->GetOptionsValue(frameNode, index);
    }
    return "";
}

void TimePickerColumnAccessibilityProperty::SetSpecificSupportAction()
{
    if (IsScrollable()) {
        auto frameNode = host_.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(pattern);
        if (pattern->CanMove(true)) {
            AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
        }
        if (pattern->CanMove(false)) {
            AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
        }
    }
}
} // namespace OHOS::Ace::NG
