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

#include "core/components_ng/pattern/list/list_layout_algorithm.h"

#include <unordered_set>

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {

constexpr float CACHE_SIZE_RADIO = 0.1;

void UpdateListItemConstraint(Axis axis, const SizeF& selfIdealSize, LayoutConstraintF& contentConstraint)
{
    contentConstraint.parentIdealSize = selfIdealSize;
    if (axis == Axis::VERTICAL) {
        contentConstraint.maxSize.SetHeight(std::numeric_limits<float>::infinity());
        auto width = selfIdealSize.Width();
        if (width == std::numeric_limits<float>::infinity()) {
            contentConstraint.maxSize.SetWidth(width);
            contentConstraint.minSize.SetWidth(width);
        }
        return;
    }
    contentConstraint.maxSize.SetWidth(std::numeric_limits<float>::infinity());
    auto height = selfIdealSize.Height();
    if (height == std::numeric_limits<float>::infinity()) {
        contentConstraint.maxSize.SetHeight(height);
        contentConstraint.minSize.SetHeight(height);
    }
}
} // namespace

void ListLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(listLayoutProperty);

    auto initialIndex = listLayoutProperty->GetInitialIndex().value_or(0);
    if (!isInitialized_) {
        preStartIndex_ = initialIndex;
        isInitialized_ = true;
    }

    // calculate idealSize and set FrameSize
    auto axis = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    auto idealSize =
        CreateIdealSize(listLayoutProperty->GetLayoutConstraint().value(), axis, listLayoutProperty->GetMeasureType());
    if (GetMainAxisSize(idealSize, axis) == std::numeric_limits<float>::infinity()) {
        LOGE("the list is infinity, error");
        return;
    }
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
    MinusPaddingToSize(listLayoutProperty->CreatePaddingPropertyF(), idealSize);

    // calculate main size.
    auto mainSize = GetMainAxisSize(idealSize, axis);
    startMainPos_ = currentOffset_;
    endMainPos_ = currentOffset_ + mainSize;
    LOGD("pre start index: %{public}d, pre end index: %{public}d, offset is %{public}f", preStartIndex_, preEndIndex_,
        currentOffset_);

    auto space = listLayoutProperty->GetSpace().value_or(Dimension(0));
    spaceWidth_ = ConvertToPx(space, listLayoutProperty->GetLayoutConstraint()->scaleProperty, mainSize).value_or(0);

    // calculate child layout constraint.
    auto contentLayoutConstraint = listLayoutProperty->CreateChildConstraint();
    UpdateListItemConstraint(axis, idealSize, contentLayoutConstraint.value());

    itemPosition_.clear();

    if (NonNegative(currentOffset_)) {
        LayoutForward(layoutWrapper, contentLayoutConstraint.value(), axis, mainSize);
    } else {
        LayoutBackward(layoutWrapper, contentLayoutConstraint.value(), axis, mainSize);
    }

    LOGD("new start index is %{public}d, new end index is %{public}d, offset is %{public}f", startIndex_.value(),
        endIndex_.value(), currentOffset_);
}

void ListLayoutAlgorithm::LayoutForward(
    LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis, float mainSize)
{
    std::unordered_set<int32_t> inActiveItems;
    std::optional<int32_t> newStartIndex;
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(preStartIndex_);
    if (!wrapper) {
        LOGW("the %{public}d wrapper is null in LayoutForward", preStartIndex_);
        return;
    }
    // Calculate the end pos of the priv item ahead of the StartIndex.
    float currentEndPos = GetMainAxisOffset(wrapper->GetGeometryNode()->GetFrameOffset(), axis);
    float currentStartPos = currentEndPos;
    auto currentIndex = preStartIndex_ - 1;
    float cacheSize = mainSize * CACHE_SIZE_RADIO;
    do {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex + 1);
        if (!wrapper) {
            LOGE("the start %{public}d index wrapper is null", currentIndex + 1);
            break;
        }
        ++currentIndex;
        currentStartPos = currentEndPos;
        {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem");
            wrapper->Measure(layoutConstraint);
        }
        auto mainLength = GetMainAxisSize(wrapper->GetGeometryNode()->GetFrameSize(), axis);
        currentEndPos = currentStartPos + mainLength;
        // out of display area, mark inactive.
        if (LessNotEqual(currentEndPos, startMainPos_ - cacheSize)) {
            inActiveItems.emplace(currentIndex);
        } else {
            // mark new start index.
            if (!newStartIndex) {
                newStartIndex = currentIndex;
            }
        }
        itemPosition_[currentIndex] = { currentStartPos, currentEndPos };
        if ((currentIndex > 0) && (currentIndex < static_cast<int32_t>(itemPosition_.size()) - 1)) {
            currentEndPos = currentEndPos + spaceWidth_;
        }
    } while (LessNotEqual(currentEndPos, endMainPos_ + cacheSize));

    startIndex_ = newStartIndex.value_or(preStartIndex_);
    endIndex_ = currentIndex;

    // adjust offset.
    if (LessNotEqual(currentEndPos, endMainPos_)) {
        auto firstItemTop = itemPosition_[startIndex_.value()].first;
        auto itemTotalSize = currentEndPos - firstItemTop;
        if (LessOrEqual(itemTotalSize, mainSize) && (startIndex_ == 0)) {
            // all items size is less than list.
            currentOffset_ = firstItemTop;
        } else {
            currentOffset_ = currentEndPos - mainSize;
            startMainPos_ = currentOffset_;
            auto startIndex = startIndex_.value();
            auto currentStartPos = itemPosition_[startIndex].first;
            // After shrinking the offset, needs to find the deleted node and add it back again.
            while (GreatOrEqual(currentStartPos, startMainPos_ - cacheSize)) {
                auto item = itemPosition_.find(startIndex - 1);
                if (item == itemPosition_.end()) {
                    break;
                }
                --startIndex;
                currentStartPos = item->second.first;
                inActiveItems.erase(startIndex);
            }
            startIndex_ = startIndex;
        }
    }
    // Mark inactive in wrapper.
    for (const auto& index : inActiveItems) {
        layoutWrapper->RemoveChildInRenderTree(index);
    }
}

void ListLayoutAlgorithm::LayoutBackward(
    LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis, float mainSize)
{
    std::unordered_set<int32_t> inActiveItems;
    std::optional<int32_t> newEndIndex;
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(preEndIndex_);
    if (!wrapper) {
        LOGW("the %{public}d wrapper is null in LayoutBackward", preEndIndex_);
        return;
    }
    // Calculate the start pos of the next item behind the EndIndex.
    float currentStartPos = GetMainAxisOffset(wrapper->GetGeometryNode()->GetFrameOffset(), axis) +
                            GetMainAxisSize(wrapper->GetGeometryNode()->GetFrameSize(), axis);
    float currentEndPos = currentStartPos;
    auto currentIndex = preEndIndex_ + 1;
    float cacheSize = mainSize * CACHE_SIZE_RADIO;
    do {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex - 1);
        if (!wrapper) {
            LOGW("the %{public}d wrapper is null", currentIndex - 1);
            break;
        }
        --currentIndex;
        // the current item end pos is the prev item start pos in backward.
        currentEndPos = currentStartPos;
        {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem");
            wrapper->Measure(layoutConstraint);
        }
        auto mainLength = GetMainAxisSize(wrapper->GetGeometryNode()->GetFrameSize(), axis);
        currentStartPos = currentEndPos - mainLength;

        // out of display area, mark inactive.
        if (GreatNotEqual(currentStartPos, endMainPos_ + cacheSize)) {
            inActiveItems.emplace(currentIndex);
        } else {
            // mark new end index.
            if (!newEndIndex) {
                newEndIndex = currentIndex;
            }
        }
        itemPosition_[currentIndex] = { currentStartPos, currentEndPos };
        if ((currentIndex > 0) && (currentIndex < static_cast<int32_t>(itemPosition_.size()) - 1)) {
            currentStartPos = currentStartPos - spaceWidth_;
        }
    } while (GreatNotEqual(currentStartPos, startMainPos_ - cacheSize));

    endIndex_ = newEndIndex.value_or(preEndIndex_);
    startIndex_ = currentIndex;

    // adjust offset.
    if (GreatNotEqual(currentStartPos, startMainPos_)) {
        currentOffset_ = currentStartPos;
        endMainPos_ = currentOffset_ + mainSize;
        currentOffset_ = currentStartPos;
        auto endIndex = endIndex_.value();
        auto currentEndPos = itemPosition_[endIndex].second;
        // After shrinking the offset, needs to find the deleted node and add it back again.
        while (LessOrEqual(currentEndPos, endMainPos_ + cacheSize)) {
            auto item = itemPosition_.find(endIndex + 1);
            if (item == itemPosition_.end()) {
                break;
            }
            ++endIndex;
            currentEndPos = item->second.second;
            inActiveItems.erase(endIndex);
        }
        endIndex_ = endIndex;
    }
    // Mark inactive in wrapper.
    for (const auto& index : inActiveItems) {
        layoutWrapper->RemoveChildInRenderTree(index);
    }
}

void ListLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(listLayoutProperty);
    auto axis = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingPropertyF();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0.0f);
    auto top = padding.top.value_or(0.0f);
    auto paddingOffset = OffsetF(left, top);

    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();

    // layout items.
    for (auto index = startIndex_.value(); index <= endIndex_.value(); ++index) {
        auto offset = paddingOffset;
        if (axis == Axis::VERTICAL) {
            offset = offset + OffsetF(0, itemPosition_[index].first - currentOffset_);
        } else {
            offset = offset + OffsetF(itemPosition_[index].first - currentOffset_, 0);
        }
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        wrapper->GetGeometryNode()->SetFrameOffset(offset);
        wrapper->Layout(parentOffset);
    }
}

} // namespace OHOS::Ace::NG
