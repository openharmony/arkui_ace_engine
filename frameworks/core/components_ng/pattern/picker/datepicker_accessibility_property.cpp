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

#include "core/components_ng/pattern/picker/datepicker_accessibility_property.h"
#include "core/interfaces/native/node/view_model.h"
#include "core/interfaces/native/node/node_timepicker_modifier.h"

#include "base/utils/utils.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/time_picker/bridge/timepicker_util.h"

namespace OHOS::Ace::NG {
namespace {
const std::string COLON = ":";
} // namespace

std::string DatePickerAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto pattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(pattern, "");

    std::string result;
    if (pattern->GetIsShowInDialog() && pattern->ShowMonthDays()) {
        result = GetColumnsText(frameNode, true);
        result.append(" ");
        result.append(GetShowTimePickerText());
    } else {
        result = GetColumnsText(frameNode, false);
    }
    return result;
}

std::string DatePickerAccessibilityProperty::GetColumnsText(
    const RefPtr<FrameNode>& frameNode, bool isMonthDaysDateNode) const
{
    CHECK_NULL_RETURN(frameNode, "");
    std::string result = "";
    for (const auto& child : frameNode->GetChildren()) {
        auto stackColumn = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_RETURN(stackColumn, "");
        auto blendColumn = AceType::DynamicCast<FrameNode>(stackColumn->GetLastChild());
        CHECK_NULL_RETURN(blendColumn, "");
        auto blendColumnLayoutProperty = blendColumn->GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_RETURN(blendColumnLayoutProperty, "");
        if (blendColumnLayoutProperty->GetVisibility() == VisibleType::GONE) {
            continue;
        }
        auto dataColumnNode = AceType::DynamicCast<FrameNode>(blendColumn->GetLastChild());
        CHECK_NULL_RETURN(dataColumnNode, "");
        auto columnPattern = dataColumnNode->GetPattern<DatePickerColumnPattern>();
        CHECK_NULL_RETURN(columnPattern, "");
        auto index = columnPattern->GetCurrentIndex();
        auto options = columnPattern->GetOptions();
        auto it = options.find(dataColumnNode);
        if (it != options.end() && index >= 0 && index < it->second.size()) {
            auto date = it->second.at(index);
            result.append(DatePickerPattern::GetFormatString(date));
        }
        if (isMonthDaysDateNode) {
            break;
        }
    }
    return result;
}

std::string DatePickerAccessibilityProperty::GetShowTimePickerText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto* modifier = NG::NodeModifier::GetTimepickerCustomModifier();
    CHECK_NULL_RETURN(modifier, "");
    auto result = modifier->getShowTimePickerText(frameNode);
    return result;
}
} // namespace OHOS::Ace::NG
