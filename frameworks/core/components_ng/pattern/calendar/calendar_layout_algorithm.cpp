/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <algorithm>
#include <optional>

#include "base/geometry/ng/size_t.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t CALENDAR_MIN_WIDTH = 350;
constexpr int32_t CALENDAR_MIN_HEIGHT = 230;

} // namespace

std::optional<SizeF> CalendarLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    SizeF calendarMinSize(CALENDAR_MIN_WIDTH, CALENDAR_MIN_HEIGHT);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, std::nullopt);
    auto maxSize = contentConstraint.maxSize;
    SizeF layoutSize;
    if (GreatOrEqual(maxSize.Width(), Infinity<float>()) || GreatOrEqual(maxSize.Height(), Infinity<float>())) {
        auto minSize = contentConstraint.minSize;
        layoutSize = SizeF(
            std::max(maxSize.Width(), calendarMinSize.Width()), std::max(minSize.Height(), calendarMinSize.Height()));
    } else {
        layoutSize = SizeF(
            std::max(maxSize.Width(), calendarMinSize.Width()), std::max(maxSize.Height(), calendarMinSize.Height()));
    }
    if (GreatOrEqual(maxSize.Width(), Infinity<float>()) || GreatOrEqual(maxSize.Height(), Infinity<float>())) {
        auto frameNode = layoutWrapper->GetHostNode();
        CHECK_NULL_RETURN(frameNode, std::nullopt);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_RETURN(frameNode, std::nullopt);
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