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

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void SwiperLayoutAlgorithm::InitItemRange()
{
    ACE_SCOPED_TRACE("SwiperLayoutAlgorithm::InitItemRange");
    itemRange_.clear();
    if (startIndex_ <= endIndex_) {
        for (auto index = startIndex_; index <= endIndex_; ++index) {
            itemRange_.insert(index);
        }
    } else {
        for (auto index = startIndex_; index < totalCount_; ++index) {
            itemRange_.insert(index);
        }
        for (auto index = 0; index <= endIndex_; ++index) {
            itemRange_.insert(index);
        }
    }

    if (targetIndex_.has_value() && (targetIndex_.value() < startIndex_ || targetIndex_.value() > endIndex_)) {
        itemRange_.insert(targetIndex_.value());
    }

    if (preItemRange_.empty()) {
        return;
    }

    // inActiveItems collect items which exist in preItemRange_, but not exist in itemRange_,
    // need remove these items from wrapper.
    inActiveItems_.clear();

    // Collect the same item in itemRange_ and preItemRange_.
    std::vector<int32_t> intersection;
    set_intersection(itemRange_.begin(), itemRange_.end(), preItemRange_.begin(), preItemRange_.end(),
        inserter(intersection, intersection.begin()));

    // Collect difference items between preItemRange_ and intersection.
    set_difference(preItemRange_.begin(), preItemRange_.end(), intersection.begin(), intersection.end(),
        inserter(inActiveItems_, inActiveItems_.begin()));
}

void SwiperLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);

    auto axis = swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    const auto& constraint = swiperLayoutProperty->GetLayoutConstraint();
    if (!constraint) {
        LOGE("fail to measure swiper due to layoutConstraint is nullptr");
        return;
    }
    auto idealSize = CreateIdealSize(
        constraint.value(), axis, swiperLayoutProperty->GetMeasureType(MeasureType::MATCH_PARENT), true);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameSize(idealSize);

    InitItemRange();

    // Measure children.
    auto layoutConstraint = swiperLayoutProperty->CreateChildConstraint();
    layoutConstraint.parentIdealSize = OptionalSizeF(idealSize);
    for (const auto& index : itemRange_) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!wrapper) {
            break;
        }
        wrapper->Measure(layoutConstraint);
    }

    // Mark inactive in wrapper.
    for (const auto& index : inActiveItems_) {
        layoutWrapper->RemoveChildInRenderTree(index);
    }
}

void SwiperLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto axis = swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    auto displayCount = swiperLayoutProperty->GetDisplayCount().value_or(1);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto childrenSize = layoutWrapper->GetTotalChildCount();
    auto itemWidth = (axis == Axis::HORIZONTAL ? (size.Width() / displayCount) : (size.Height() / displayCount));

    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();

    // Effect when difference between current index and target index is greater than 1.
    // eg. Current index is 0, call swipeTo method to jump to index 2,
    // change item's position only 0 and 2, ignore others.
    if (targetIndex_.has_value() && std::abs(targetIndex_.value() - currentIndex_) > 1) {
        auto currentOffset = axis == Axis::HORIZONTAL ? OffsetF(currentOffset_, 0.0f) : OffsetF(0.0f, currentOffset_);
        // Layout current item.
        auto currentWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex_);
        if (currentWrapper && currentWrapper->GetGeometryNode()) {
            currentWrapper->GetGeometryNode()->SetFrameOffset(currentOffset);
            currentWrapper->Layout(parentOffset);
        }

        // Layout target item.
        auto targetMainOffset = targetIndex_.value() > currentIndex_ ? itemWidth : -itemWidth;
        auto targetOffset =
            axis == Axis::HORIZONTAL ? OffsetF(targetMainOffset, 0.0f) : OffsetF(0.0f, targetMainOffset);
        auto targetWrapper = layoutWrapper->GetOrCreateChildByIndex(targetIndex_.value());
        if (targetWrapper && targetWrapper->GetGeometryNode()) {
            targetWrapper->GetGeometryNode()->SetFrameOffset(currentOffset + targetOffset);
            targetWrapper->Layout(parentOffset);
        }
        return;
    }

    // Layout children.
    for (const auto& index : itemRange_) {
        // When enable loop, adjust offset.
        auto loopIndex = index;
        if (currentIndex_ == 0 && GreatNotEqual(currentOffset_, 0.0) && index == childrenSize - 1) {
            loopIndex = -1;
        } else if (currentIndex_ == childrenSize - 1 && LessNotEqual(currentOffset_, 0.0) && index == 0) {
            loopIndex = childrenSize;
        }

        auto offset = OffsetF(0.0, 0.0);
        if (axis == Axis::HORIZONTAL) {
            offset += OffsetF((loopIndex - currentIndex_) * itemWidth + currentOffset_, 0.0f);
        } else if (axis == Axis::VERTICAL) {
            offset += OffsetF(0.0f, (loopIndex - currentIndex_) * itemWidth + currentOffset_);
        } else {
            LOGW("axis [%{public}d] is not supported yet", axis);
        }
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        wrapper->GetGeometryNode()->SetFrameOffset(offset);
        wrapper->Layout(parentOffset);
    }
}

} // namespace OHOS::Ace::NG
