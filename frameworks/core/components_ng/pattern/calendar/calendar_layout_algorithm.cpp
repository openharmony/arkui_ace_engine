/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/calendar/calendar_layout_algorithm.h"

#include <optional>

#include "base/geometry/ng/size_t.h"
#include "core/components_ng/pattern/calendar/calendar_month_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CALENDAR_MIN_WIDTH = 350;
constexpr int32_t CALENDAR_MIN_HEIGHT = 230;
} // namespace

std::optional<SizeF> CalendarLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, std::nullopt);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto calendarMonthPattern = host->GetPattern<CalendarMonthPattern>();
    CHECK_NULL_RETURN(calendarMonthPattern, std::nullopt);
    if (calendarMonthPattern->IsCalendarDialog()) {
        return contentConstraint.maxSize;
    }

    SizeF calendarMinSize(CALENDAR_MIN_WIDTH, CALENDAR_MIN_HEIGHT);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, std::nullopt);
    auto maxSize = contentConstraint.maxSize;
    SizeF layoutSize;
    if (GreaterOrEqualToInfinity(maxSize.Width()) || GreaterOrEqualToInfinity(maxSize.Height())) {
        auto minSize = contentConstraint.minSize;
        layoutSize = SizeF(
            std::max(maxSize.Width(), calendarMinSize.Width()), std::max(minSize.Height(), calendarMinSize.Height()));
    } else {
        layoutSize = SizeF(
            std::max(maxSize.Width(), calendarMinSize.Width()), std::max(maxSize.Height(), calendarMinSize.Height()));
    }
    if (GreaterOrEqualToInfinity(maxSize.Width()) || GreaterOrEqualToInfinity(maxSize.Height())) {
        auto frameNode = layoutWrapper->GetHostNode();
        CHECK_NULL_RETURN(frameNode, std::nullopt);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_RETURN(pipeline, std::nullopt);
        maxWidth_ = pipeline->GetRootWidth();
        maxHeight_ = pipeline->GetRootHeight();
        return SizeF(static_cast<float>(pipeline->GetRootWidth()), static_cast<float>(pipeline->GetRootHeight()));
    }
    auto constrainSize = contentConstraint.Constrain(maxSize);
    maxWidth_ = constrainSize.Width();
    maxHeight_ = constrainSize.Height();
    return maxSize;
}
} // namespace OHOS::Ace::NG
