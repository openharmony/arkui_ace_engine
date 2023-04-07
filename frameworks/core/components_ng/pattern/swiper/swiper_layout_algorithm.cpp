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
#include <cstdint>

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

void SwiperLayoutAlgorithm::AddToItemRange(int32_t index)
{
    if (index != currentIndex_) {
        index = ClampIndex(index);
        itemRange_.insert(index);
    }
}

int32_t SwiperLayoutAlgorithm::ClampIndex(int32_t index)
{
    return isLoop_ ? (index + totalCount_) % totalCount_ : std::clamp(index, 0, totalCount_ - 1);
}

void SwiperLayoutAlgorithm::LoadItemWithDrag(float translateLength)
{
    if (NonPositive(translateLength) || NearZero(currentOffset_)) {
        return;
    }

    int32_t nextIndex = currentIndex_;
    auto loadItems = std::abs(static_cast<int32_t>(floorf(currentOffset_ / translateLength)));
    do {
        nextIndex = Positive(currentOffset_) ? (nextIndex - 1) : (nextIndex + 1);
        AddToItemRange(nextIndex);
        loadItems--;
    } while (loadItems >= 0);
}

void SwiperLayoutAlgorithm::InitInActiveItems(float translateLength)
{
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

    std::set<int32_t> activeItems;
    auto firstIndex = currentIndex_;
    if (!NearZero(currentOffset_) && Positive(translateLength)) {
        auto loadItems = std::abs(static_cast<int32_t>(floorf(currentOffset_ / translateLength)));
        firstIndex = Positive(currentOffset_) ? (firstIndex - loadItems - 1) : (firstIndex + loadItems - 1);
        firstIndex = ClampIndex(firstIndex);
    }

    auto displayCount = NearZero(currentOffset_) ? displayCount_ : displayCount_ + 1;
    for (int32_t i = 0; i <= displayCount; i++) {
        activeItems.insert(ClampIndex(firstIndex + i));
    }

    if (activeItems.empty()) {
        return;
    }

    set_difference(itemRange_.begin(), itemRange_.end(), activeItems.begin(), activeItems.end(),
        inserter(inActiveItems_, inActiveItems_.begin()));
}

void SwiperLayoutAlgorithm::InitItemRange(LayoutWrapper* layoutWrapper)
{
    itemRange_.clear();

    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    // If display mode is AutoLinear, expand all children.
    if (!SwiperUtils::IsStretch(layoutProperty)) {
        startIndex_ = 0;
        endIndex_ = totalCount_ - 1;
        for (int32_t i = 0; i < totalCount_; i++) {
            itemRange_.insert(i);
        }
        return;
    }

    if (currentIndex_ < 0 || currentIndex_ > totalCount_ - 1) {
        currentIndex_ = 0;
    }

    auto axis = layoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    auto itemSpace = SwiperUtils::GetItemSpace(layoutProperty);
    auto translateLength = axis == Axis::HORIZONTAL ? maxChildSize_.Width() : maxChildSize_.Height();
    translateLength += itemSpace;

    /* Load next index while swiping */
    LoadItemWithDrag(translateLength);

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

    InitInActiveItems(translateLength);
}

void SwiperLayoutAlgorithm::LoopMeasure(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint,
    Axis axis, float& crossSize, float& mainSize)
{
    auto loopIndex = (currentIndex_ - 1 + totalCount_) % totalCount_;
    std::list<int32_t> preItems;
    while (loopIndex >= 0 && itemRange_.find(loopIndex) != itemRange_.end()) {
        preItems.emplace_back(loopIndex);
        loopIndex--;
    }

    std::list<int32_t> nextItems;
    loopIndex = currentIndex_;
    while (itemRange_.find(loopIndex) != itemRange_.end()) {
        nextItems.emplace_back(loopIndex);
        loopIndex = (loopIndex + 1) % totalCount_;
    }

    if (targetIndex_.has_value()) {
        nextItems.emplace_back(targetIndex_.value());
    }

    for (const auto& index : preItems) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!wrapper) {
            break;
        }
        wrapper->Measure(layoutConstraint);
        crossSize = std::max(crossSize, GetCrossAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis));
        mainSize = std::max(mainSize, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis));
    }

    for (const auto& index : nextItems) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!wrapper) {
            break;
        }
        wrapper->Measure(layoutConstraint);
        crossSize = std::max(crossSize, GetCrossAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis));
        mainSize = std::max(mainSize, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis));
    }
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

    auto isSingleCase =
        (swiperLayoutProperty->GetDisplayCount().has_value() && swiperLayoutProperty->GetDisplayCountValue() == 1) ||
        (!swiperLayoutProperty->GetDisplayCount().has_value() && SwiperUtils::IsStretch(swiperLayoutProperty));

    OptionalSizeF idealSize;
    auto measureType = isSingleCase ? MeasureType::MATCH_CONTENT : MeasureType::MATCH_PARENT_MAIN_AXIS;
    idealSize = CreateIdealSize(constraint.value(), axis, swiperLayoutProperty->GetMeasureType(measureType));

    auto padding = swiperLayoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, idealSize);

    InitItemRange(layoutWrapper);

    // Measure children.
    auto layoutConstraint = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, idealSize);
    auto crossSize = 0.0f;
    auto mainSize = 0.0f;

    auto itemCount = static_cast<int32_t>(itemRange_.size());
    if (isLoop_ && itemCount < totalCount_) {
        LoopMeasure(layoutWrapper, layoutConstraint, axis, crossSize, mainSize);
    } else {
        for (const auto& index : itemRange_) {
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
            if (!wrapper) {
                break;
            }
            wrapper->Measure(layoutConstraint);
            crossSize = std::max(crossSize, GetCrossAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis));
            mainSize = std::max(mainSize, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis));
        }
    }

    maxChildSize_ = axis == Axis::HORIZONTAL ? SizeF(mainSize, crossSize) : SizeF(crossSize, mainSize);

    if (isSingleCase) {
        // single case.
        idealSize.UpdateIllegalSizeWithCheck(maxChildSize_);
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

    AddPaddingToSize(padding, idealSize);

    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameSize(idealSize.ConvertToSizeT());

    // Measure swiper indicator
    if (swiperLayoutProperty->GetShowIndicatorValue(true)) {
        auto indicatorWrapper = layoutWrapper->GetOrCreateChildByIndex(totalCount_);
        if (indicatorWrapper) {
            auto indicatorLayoutConstraint = swiperLayoutProperty->CreateChildConstraint();
            indicatorLayoutConstraint.parentIdealSize = idealSize;
            indicatorWrapper->Measure(indicatorLayoutConstraint);
        }
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
    auto itemWidth = (axis == Axis::HORIZONTAL ? (size.Width() / displayCount) : (size.Height() / displayCount));
    auto itemSpace = SwiperUtils::GetItemSpace(swiperLayoutProperty);
    auto padding = swiperLayoutProperty->CreatePaddingAndBorder();
    OffsetF paddingOffset = { padding.left.value_or(0.0f), padding.top.value_or(0.0f) };

    // Effect when difference between current index and target index is greater than 1.
    // e.g. Current index is 0, call swipeTo method to jump to index 2,
    // change item's position only 0 and 2, ignore others.
    if (SwiperUtils::IsStretch(swiperLayoutProperty) && targetIndex_.has_value() &&
        std::abs(targetIndex_.value() - currentIndex_) > 1) {
        auto currentOffset = axis == Axis::HORIZONTAL ? OffsetF(currentOffset_, 0.0f) : OffsetF(0.0f, currentOffset_);
        auto itemSpaceOffset = (axis == Axis::HORIZONTAL ? OffsetF(itemSpace / 2, 0) : OffsetF(0, itemSpace / 2));
        // Layout current item.
        auto currentWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex_);
        if (currentWrapper && currentWrapper->GetGeometryNode()) {
            currentWrapper->GetGeometryNode()->SetMarginFrameOffset(currentOffset + itemSpaceOffset + paddingOffset);
            currentWrapper->Layout();
        }

        // Layout target item.
        auto targetMainOffset = targetIndex_.value() > currentIndex_ ? itemWidth : -itemWidth;
        auto targetOffset =
            axis == Axis::HORIZONTAL ? OffsetF(targetMainOffset, 0.0f) : OffsetF(0.0f, targetMainOffset);
        auto targetWrapper = layoutWrapper->GetOrCreateChildByIndex(targetIndex_.value());
        if (targetWrapper && targetWrapper->GetGeometryNode()) {
            targetWrapper->GetGeometryNode()->SetMarginFrameOffset(
                currentOffset + targetOffset + itemSpaceOffset + paddingOffset);
            targetWrapper->Layout();
        }
        return;
    }
    
    if (swiperLayoutProperty->GetCachedCount().value_or(1) == 0) {
        LayoutOffScreen(layoutWrapper, axis);
    }

    if (isLoop_) {
        LoopLayout(layoutWrapper);
    } else {
        NonLoopLayout(layoutWrapper);
    }

    // Layout swiper indicator
    if (swiperLayoutProperty->GetShowIndicatorValue(true)) {
        auto indicatorWrapper = layoutWrapper->GetOrCreateChildByIndex(totalCount_);
        if (indicatorWrapper) {
            indicatorWrapper->Layout();
        }
    }

    // Mark inactive in wrapper.
    for (const auto& index : inActiveItems_) {
        if (!NearZero(currentOffset_)) {
            continue;
        }

        if (swiperLayoutProperty->GetShowIndicatorValue(true) && index == totalCount_) {
            continue;
        }
        layoutWrapper->RemoveChildInRenderTree(index);
    }
}

void SwiperLayoutAlgorithm::LayoutOffScreen(LayoutWrapper* layoutWrapper, Axis axis) const
{
    std::set<int32_t> outItems;
    set_difference(preItemRange_.begin(), preItemRange_.end(), itemRange_.begin(), itemRange_.end(),
        inserter(outItems, outItems.begin()));

    auto offset = (axis == Axis::HORIZONTAL ? OffsetF(-maxChildSize_.Width(), 0) : OffsetF(0, -maxChildSize_.Height()));
    for (const auto& index : outItems) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!wrapper) {
            continue;
        }
        auto geometryNode = wrapper->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        geometryNode->SetMarginFrameOffset(offset);
        wrapper->Layout();
    }
}

void SwiperLayoutAlgorithm::NonLoopLayout(LayoutWrapper* layoutWrapper)
{
    std::list<int32_t> preItems;
    std::list<int32_t> nextItems;
    for (const auto& index : itemRange_) {
        if (index < currentIndex_) {
            preItems.push_front(index);
        } else {
            nextItems.emplace_back(index);
        }
    }

    LayoutItems(layoutWrapper, preItems, nextItems);
}

void SwiperLayoutAlgorithm::LoopLayout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto displayCount = swiperLayoutProperty->GetDisplayCount().value_or(1);

    std::list<int32_t> preItems;
    std::list<int32_t> nextItems;
    SortItems(preItems, nextItems, displayCount);

    LayoutItems(layoutWrapper, preItems, nextItems);
}

void SwiperLayoutAlgorithm::SortItems(std::list<int32_t>& preItems, std::list<int32_t>& nextItems, int32_t displayCount)
{
    if (static_cast<int32_t>(itemRange_.size()) == totalCount_) {
        auto cacheCount = static_cast<int32_t>(ceilf(static_cast<float>(totalCount_ - displayCount) / 2.0f));
        auto loopIndex = (currentIndex_ - 1 + totalCount_) % totalCount_;
        int32_t count = 0;
        while (loopIndex >= 0 && itemRange_.find(loopIndex) != itemRange_.end() && count < cacheCount) {
            preItems.emplace_back(loopIndex);
            loopIndex--;
            count++;
        }

        loopIndex = currentIndex_;
        count = 0;
        while (itemRange_.find(loopIndex) != itemRange_.end() && count < (displayCount + cacheCount)) {
            nextItems.emplace_back(loopIndex);
            loopIndex = (loopIndex + 1) % totalCount_;
            count++;
        }

        if (targetIndex_.has_value()) {
            nextItems.emplace_back(targetIndex_.value());
        }
    } else {
        auto loopIndex = (currentIndex_ - 1 + totalCount_) % totalCount_;
        while (loopIndex >= 0 && itemRange_.find(loopIndex) != itemRange_.end()) {
            preItems.emplace_back(loopIndex);
            loopIndex--;
        }

        loopIndex = currentIndex_;
        while (itemRange_.find(loopIndex) != itemRange_.end()) {
            nextItems.emplace_back(loopIndex);
            loopIndex = (loopIndex + 1) % totalCount_;
        }

        if (targetIndex_.has_value()) {
            nextItems.emplace_back(targetIndex_.value());
        }
    }
}

void SwiperLayoutAlgorithm::LayoutItems(
    LayoutWrapper* layoutWrapper, const std::list<int32_t>& preItems, const std::list<int32_t>& nextItems)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto axis = swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    auto itemSpace = SwiperUtils::GetItemSpace(swiperLayoutProperty);
    auto padding = swiperLayoutProperty->CreatePaddingAndBorder();
    auto rightPadding = padding.right.value_or(0.0f);
    auto bottomPadding = padding.bottom.value_or(0.0f);
    OffsetF paddingOffset = { padding.left.value_or(0.0f), padding.top.value_or(0.0f) };
    auto displayCount = swiperLayoutProperty->GetDisplayCount().value_or(1);

    OffsetF preOffset =
        (axis == Axis::HORIZONTAL ? OffsetF(-itemSpace + currentOffset_, 0) : OffsetF(0, -itemSpace + currentOffset_));
    int32_t displayIndex = 0;
    for (const auto& index : preItems) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!wrapper) {
            continue;
        }
        auto geometryNode = wrapper->GetGeometryNode();
        preOffset -=
            (axis == Axis::HORIZONTAL ? OffsetF(maxChildSize_.Width(), 0) : OffsetF(0, maxChildSize_.Height()));
        geometryNode->SetMarginFrameOffset(preOffset + paddingOffset);
        wrapper->Layout();
        preOffset -= (axis == Axis::HORIZONTAL ? OffsetF(itemSpace, 0) : OffsetF(0, itemSpace));
        displayIndex++;
        if (displayIndex == displayCount) {
            preOffset += (axis == Axis::HORIZONTAL ? OffsetF(currentOffset_ == 0 ? rightPadding : 0, 0)
                                                   : OffsetF(0, bottomPadding));
        }
    }

    OffsetF nextOffset = (axis == Axis::HORIZONTAL ? OffsetF(currentOffset_, 0) : OffsetF(0, currentOffset_));
    displayIndex = 0;
    for (const auto& index : nextItems) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!wrapper) {
            continue;
        }
        auto geometryNode = wrapper->GetGeometryNode();
        geometryNode->SetMarginFrameOffset(nextOffset + paddingOffset);
        wrapper->Layout();
        nextOffset += (axis == Axis::HORIZONTAL ? OffsetF(maxChildSize_.Width() + itemSpace, 0)
                                                : OffsetF(0, maxChildSize_.Height() + itemSpace));

        displayIndex++;
        if (displayIndex == displayCount) {
            nextOffset += (axis == Axis::HORIZONTAL ? OffsetF(currentOffset_ == 0 ? rightPadding : 0, 0)
                                                    : OffsetF(0, bottomPadding));
        }
    }
}
} // namespace OHOS::Ace::NG
