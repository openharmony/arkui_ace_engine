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

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_utils.h"
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

    auto displayCount = swiperLayoutProperty->GetDisplayCount().value_or(1);

    OptionalSizeF idealSize;
    if (displayCount == 1) {
        // single case
        idealSize =
            CreateIdealSize(constraint.value(), axis, swiperLayoutProperty->GetMeasureType(MeasureType::MATCH_CONTENT));
    } else {
        idealSize = CreateIdealSize(
            constraint.value(), axis, swiperLayoutProperty->GetMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS));
    }
    InitItemRange();

    // Measure children.
    auto layoutConstraint = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, idealSize);
    auto crossSize = 0.0f;
    auto mainSize = 0.0f;
    for (const auto& index : itemRange_) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!wrapper) {
            break;
        }
        wrapper->Measure(layoutConstraint);
        crossSize = std::max(crossSize, GetCrossAxisSize(wrapper->GetGeometryNode()->GetFrameSize(), axis));
        mainSize = std::max(mainSize, GetMainAxisSize(wrapper->GetGeometryNode()->GetFrameSize(), axis));
    }

    // Mark inactive in wrapper.
    for (const auto& index : inActiveItems_) {
        layoutWrapper->RemoveChildInRenderTree(index);
    }

    if (displayCount == 1) {
        // single case.
        SizeF maxChildSize = axis == Axis::HORIZONTAL ? SizeF(mainSize, crossSize) : SizeF(crossSize, mainSize);
        idealSize.UpdateIllegalSizeWithCheck(maxChildSize);
    } else {
        // multi case, update cross size.
        if (axis == Axis::HORIZONTAL) {
            if (!idealSize.Height()) {
                idealSize.SetHeight(crossSize);
            }
        } else {
            if (!idealSize.Width()) {
                idealSize.SetWidth(crossSize);
            }
        }
    }

    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameSize(idealSize.ConvertToSizeT());
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
    auto itemSpace = SwiperUtils::GetItemSpace(swiperLayoutProperty);

    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();

    // Effect when difference between current index and target index is greater than 1.
    // eg. Current index is 0, call swipeTo method to jump to index 2,
    // change item's position only 0 and 2, ignore others.
    if (SwiperUtils::IsStretch(swiperLayoutProperty) && targetIndex_.has_value() &&
        std::abs(targetIndex_.value() - currentIndex_) > 1) {
        auto currentOffset = axis == Axis::HORIZONTAL ? OffsetF(currentOffset_, 0.0f) : OffsetF(0.0f, currentOffset_);
        auto itemSpaceOffset = (axis == Axis::HORIZONTAL ? OffsetF(itemSpace / 2, 0) : OffsetF(0, itemSpace / 2));
        // Layout current item.
        auto currentWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex_);
        if (currentWrapper && currentWrapper->GetGeometryNode()) {
            currentWrapper->GetGeometryNode()->SetFrameOffset(currentOffset + itemSpaceOffset);
            currentWrapper->Layout(parentOffset);
        }

        // Layout target item.
        auto targetMainOffset = targetIndex_.value() > currentIndex_ ? itemWidth : -itemWidth;
        auto targetOffset =
            axis == Axis::HORIZONTAL ? OffsetF(targetMainOffset, 0.0f) : OffsetF(0.0f, targetMainOffset);
        auto targetWrapper = layoutWrapper->GetOrCreateChildByIndex(targetIndex_.value());
        if (targetWrapper && targetWrapper->GetGeometryNode()) {
            targetWrapper->GetGeometryNode()->SetFrameOffset(currentOffset + targetOffset + itemSpaceOffset);
            targetWrapper->Layout(parentOffset);
        }
        return;
    }

    // Layout children.
    // Split item range by current index.
    std::set<int32_t, std::greater<>> preItems;
    std::set<int32_t> nextItems;
    for (const auto& index : itemRange_) {
        if (index < currentIndex_) {
            preItems.insert(index);
        } else {
            nextItems.insert(index);
        }
    }

    // Layout items behind current item.
    OffsetF preOffset = (axis == Axis::HORIZONTAL ? OffsetF(-itemSpace / 2 + currentOffset_, 0)
                                                  : OffsetF(0, -itemSpace / 2 + currentOffset_));
    for (const auto& index : preItems) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!wrapper) {
            continue;
        }
        auto geometryNode = wrapper->GetGeometryNode();
        auto frameSize = geometryNode->GetFrameSize();
        preOffset -= (axis == Axis::HORIZONTAL ? OffsetF(frameSize.Width(), 0) : OffsetF(0, frameSize.Height()));
        geometryNode->SetFrameOffset(preOffset);
        wrapper->Layout(parentOffset);
        preOffset -= (axis == Axis::HORIZONTAL ? OffsetF(itemSpace, 0) : OffsetF(0, itemSpace));
    }

    // Layout items after current item.
    OffsetF nextOffset = (axis == Axis::HORIZONTAL ? OffsetF(itemSpace / 2 + currentOffset_, 0)
                                                   : OffsetF(0, itemSpace / 2 + currentOffset_));
    for (const auto& index : nextItems) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!wrapper) {
            continue;
        }
        auto geometryNode = wrapper->GetGeometryNode();
        geometryNode->SetFrameOffset(nextOffset);
        wrapper->Layout(parentOffset);
        auto frameSize = geometryNode->GetFrameSize();
        nextOffset += (axis == Axis::HORIZONTAL ? OffsetF(frameSize.Width() + itemSpace, 0)
                                                : OffsetF(0, frameSize.Height() + itemSpace));
    }

    // Adjust offset when loop.
    if (!isLoop_) {
        return;
    }
    if (currentIndex_ == 0 && GreatNotEqual(currentOffset_, 0.0)) {
        auto lastWrapper = layoutWrapper->GetOrCreateChildByIndex(childrenSize - 1);
        if (lastWrapper) {
            auto geometryNode = lastWrapper->GetGeometryNode();
            auto frameSize = geometryNode->GetFrameSize();
            preOffset -= (axis == Axis::HORIZONTAL ? OffsetF(frameSize.Width(), 0) : OffsetF(0, frameSize.Height()));
            geometryNode->SetFrameOffset(preOffset);
            lastWrapper->Layout(parentOffset);
        }
    } else if (currentIndex_ == childrenSize - 1 && LessNotEqual(currentOffset_, 0.0)) {
        auto firstWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
        if (firstWrapper) {
            auto geometryNode = firstWrapper->GetGeometryNode();
            geometryNode->SetFrameOffset(nextOffset);
            firstWrapper->Layout(parentOffset);
        }
    }
}

} // namespace OHOS::Ace::NG
