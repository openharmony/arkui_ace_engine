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

#include "core/components_ng/pattern/swiper/swiper_layout_algorithm.h"

#include <algorithm>
#include <unordered_set>

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {

float GetCrossAxisSize(const SizeF& size, Axis axis)
{
    return axis == Axis::HORIZONTAL ? size.Height() : size.Width();
}

void SetCrossAxisSize(float value, Axis axis, SizeF& size)
{
    if (axis == Axis::VERTICAL) {
        size.SetWidth(value);
        return;
    }
    size.SetHeight(value);
}

SizeF CreateIdealSize(const LayoutConstraintF& layoutConstraint, Axis axis, MeasureType measureType)
{
    SizeF idealSize = { -1.0f, -1.0f };
    do {
        // Use idea size first if it is valid.
        if (layoutConstraint.selfIdealSize.has_value()) {
            const auto& selfIdeaSize = layoutConstraint.selfIdealSize.value();
            idealSize.UpdateSizeWithCheck(selfIdeaSize);
            if (idealSize.IsNonNegative()) {
                break;
            }
        }

        if (measureType == MeasureType::MATCH_PARENT && layoutConstraint.parentIdealSize.has_value()) {
            idealSize.UpdateIllegalSizeWithCheck(*layoutConstraint.parentIdealSize);
            if (idealSize.IsNonNegative()) {
                break;
            }
        }
        if (GetCrossAxisSize(idealSize, axis) < 0) {
            auto parentCrossSize = GetCrossAxisSize(layoutConstraint.parentIdealSize.value_or(SizeF(-1, -1)), axis);
            if (parentCrossSize < 0) {
                parentCrossSize = GetCrossAxisSize(layoutConstraint.maxSize, axis);
            }
            SetCrossAxisSize(parentCrossSize, axis, idealSize);
        }
    } while (false);
    idealSize.UpdateIllegalSizeWithCheck(layoutConstraint.maxSize);
    return idealSize;
}

} // namespace

void SwiperLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto axis = swiperLayoutProperty->GetDirection().value_or(Axis::VERTICAL);
    auto idealSize =
        CreateIdealSize(swiperLayoutProperty->GetLayoutConstraint().value(), axis, swiperLayoutProperty->GetMeasureType());
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);

    // Measure children.
    auto layoutConstraint = swiperLayoutProperty->CreateChildConstraint();
    auto currentIndex = preStartIndex_ - 1;
    auto totalCount = layoutWrapper->GetTotalChildCount();
    SizeF maxChildSize = SizeF(0.0, 0.0);
    do {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(++currentIndex);
        if (!wrapper) {
            LOGE("the start %{public}d index wrapper is null", currentIndex);
            break;
        }

        {
            ACE_SCOPED_TRACE("SwiperLayoutAlgorithm::Measure child");
            wrapper->Measure(layoutConstraint);
        }
        auto childSize = wrapper->GetGeometryNode()->GetFrameSize();
        LOGE("CCCC index: %{public}d, size: %{public}s, total: %{public}d",
            currentIndex, childSize.ToString().c_str(), layoutWrapper->GetTotalChildCount());
        maxChildSize = SizeF(std::max(maxChildSize.Width(), childSize.Width()), std::max(maxChildSize.Height(), childSize.Height()));
    } while (currentIndex < totalCount);

    startIndex_ = 0;
    endIndex_ = totalCount - 1;

    LOGE("CCCC idelSize: %{public}s, maxChildSize: %{public}s, %{public}d - %{public}d",
        idealSize.ToString().c_str(), maxChildSize.ToString().c_str(), preStartIndex_, preEndIndex_);
}

void SwiperLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto axis = swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();

    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();

    // layout chilren.
    for (auto index = startIndex_.value(); index <= endIndex_.value(); ++index) {
        auto offset = OffsetF(0.0, 0.0);
        if (axis == Axis::HORIZONTAL) {
            offset += OffsetF(size.Width() * (index - currentIndex_) + currentOffset_, 0.0f);
        } else if (axis == Axis::VERTICAL) {
            offset += OffsetF(0.0f, size.Height() * (index - currentIndex_) + currentOffset_);
        } else {
            LOGW("axis [%{public}d] is not supported yet", axis);
        }
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        wrapper->GetGeometryNode()->SetFrameOffset(offset);
        wrapper->Layout(parentOffset);

        LOGE("CCCC index: %{public}d, offset: %{public}s, parentOffset: %{public}s, current: %{public}lf",
            index, offset.ToString().c_str(), parentOffset.ToString().c_str(), currentOffset_);
    }
}

} // namespace OHOS::Ace::NG
