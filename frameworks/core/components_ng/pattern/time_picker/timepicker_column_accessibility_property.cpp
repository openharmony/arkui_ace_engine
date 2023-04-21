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
}
int32_t TimePickerColumnAccessibilityProperty::GetCollectionItemCounts() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto pattern = frameNode->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(pattern, -1);
    auto options = pattern->GetOptions();
    if (options.find(frameNode) != options.end()) {
        return options[frameNode].size();
    }
    return -1;
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

    auto currentIndex = pattern->GetCurrentIndex();
    return currentIndex + pattern->GetShowCount() / MIDDLE_OF_COUNTS;
}

int32_t TimePickerColumnAccessibilityProperty::GetBeginIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto pattern = frameNode->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(pattern, -1);

    auto currentIndex = pattern->GetCurrentIndex();
    return currentIndex - pattern->GetShowCount() / MIDDLE_OF_COUNTS;
}

std::string TimePickerColumnAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto pattern = frameNode->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(pattern, "");
    auto index = pattern->GetCurrentIndex();
    auto options = pattern->GetOptions();
    if (options.find(frameNode) != options.end()) {
        if (options[frameNode].size() < index) {
            return "";
        }
        return options[frameNode].at(index);
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
