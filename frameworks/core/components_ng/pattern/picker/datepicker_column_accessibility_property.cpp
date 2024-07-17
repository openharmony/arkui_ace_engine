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

#include "core/components_ng/pattern/picker/datepicker_column_accessibility_property.h"
#include <cstdint>

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/picker/datepicker_column_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MIDDLE_OF_COUNTS = 2;
} // namespace

int32_t DatePickerColumnAccessibilityProperty::GetCollectionItemCounts() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, 0);
    auto pattern = frameNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_RETURN(pattern, 0);
    auto options = pattern->GetOptions();
    auto it = options.find(frameNode);
    if (it != options.end()) {
        return it->second.size();
    }
    return 0;
}

int32_t DatePickerColumnAccessibilityProperty::GetCurrentIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto pattern = frameNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_RETURN(pattern, -1);
    return pattern->GetCurrentIndex();
}

int32_t DatePickerColumnAccessibilityProperty::GetEndIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto pattern = frameNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_RETURN(pattern, -1);
    auto itemCounts = GetCollectionItemCounts();
    if (itemCounts == 0) {
        return -1;
    }
    if (pattern->NotLoopOptions()) {
        return itemCounts - 1;
    }
    auto currentIndex = static_cast<int32_t>(pattern->GetCurrentIndex());
    return (itemCounts + currentIndex + static_cast<int32_t>(pattern->GetShowCount()) / MIDDLE_OF_COUNTS) % itemCounts;
}

int32_t DatePickerColumnAccessibilityProperty::GetBeginIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto pattern = frameNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_RETURN(pattern, -1);
    auto itemCounts = GetCollectionItemCounts();
    if (itemCounts == 0) {
        return -1;
    }
    if (pattern->NotLoopOptions()) {
        return 0;
    }
    auto currentIndex = static_cast<int32_t>(pattern->GetCurrentIndex());
    return (itemCounts + currentIndex - static_cast<int32_t>(pattern->GetShowCount()) / MIDDLE_OF_COUNTS) % itemCounts;
}

std::string DatePickerColumnAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto pattern = frameNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_RETURN(pattern, "");
    auto index = pattern->GetCurrentIndex();
    auto options = pattern->GetOptions();
    auto it = options.find(frameNode);
    if (it != options.end()) {
        if (it->second.size() < index) {
            return "";
        }
        auto date = it->second.at(index);
        return DatePickerPattern::GetFormatString(date);
    }
    return "";
}

void DatePickerColumnAccessibilityProperty::SetSpecificSupportAction()
{
    if (IsScrollable()) {
        auto frameNode = host_.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<DatePickerColumnPattern>();
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
