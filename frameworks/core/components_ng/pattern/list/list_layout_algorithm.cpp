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
#include "core/components/common/layout/layout_param.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {

constexpr float CACHE_SIZE_RADIO = 0.1;

void UpdateListItemConstraint(Axis axis, const SizeF& selfIdealSize, LayoutConstraintF& contentConstraint)
{
    contentConstraint.parentIdealSize = OptionalSizeF(selfIdealSize);
    if (axis == Axis::VERTICAL) {
        contentConstraint.maxSize.SetHeight(Infinity<float>());
        auto width = selfIdealSize.Width();
        if (GreatOrEqual(width, Infinity<float>())) {
            contentConstraint.maxSize.SetWidth(width);
            contentConstraint.minSize.SetWidth(width);
        }
        return;
    }
    contentConstraint.maxSize.SetWidth(Infinity<float>());
    auto height = selfIdealSize.Height();
    if (GreatOrEqual(height, Infinity<float>())) {
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
    auto idealSize = CreateIdealSize(listLayoutProperty->GetLayoutConstraint().value(), axis,
        listLayoutProperty->GetMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS), true);

    // TODO: This scenario should go with adaptive child node logic.
    if (GreatOrEqual(GetMainAxisSize(idealSize, axis), Infinity<float>())) {
        LOGE("the list is infinity, error");
        return;
    }
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
    MinusPaddingToSize(listLayoutProperty->CreatePaddingAndBorder(), idealSize);

    // calculate main size.
    auto mainSize = GetMainAxisSize(idealSize, axis);
    startMainPos_ = currentOffset_;
    endMainPos_ = currentOffset_ + mainSize;
    LOGD("pre start index: %{public}d, pre end index: %{public}d, offset is %{public}f", preStartIndex_, preEndIndex_,
        currentOffset_);

    auto space = listLayoutProperty->GetSpace().value_or(Dimension(0));
    spaceWidth_ = ConvertToPx(space, listLayoutProperty->GetLayoutConstraint()->scaleProperty, mainSize).value_or(0);
    if (listLayoutProperty->GetDivider().has_value()) {
        auto divider = listLayoutProperty->GetDivider().value();
        std::optional<float> dividerSpace = ConvertToPx(divider.strokeWidth,
            listLayoutProperty->GetLayoutConstraint()->scaleProperty, mainSize);
        if (dividerSpace.has_value()) {
            spaceWidth_ = std::max(spaceWidth_, dividerSpace.value());
        }
    }

    // calculate child layout constraint.
    auto contentLayoutConstraint = listLayoutProperty->CreateChildConstraint();
    UpdateListItemConstraint(axis, idealSize, contentLayoutConstraint);

    itemPosition_.clear();

    lanes_ = listLayoutProperty->GetLanes();
    if (listLayoutProperty->GetLaneMinLength().has_value()) {
        minLaneLength_ = ConvertToPx(listLayoutProperty->GetLaneMinLength().value(),
            listLayoutProperty->GetLayoutConstraint()->scaleProperty, mainSize);
    }
    if (listLayoutProperty->GetLaneMaxLength().has_value()) {
        maxLaneLength_ = ConvertToPx(listLayoutProperty->GetLaneMaxLength().value(),
            listLayoutProperty->GetLayoutConstraint()->scaleProperty, mainSize);
    }
    listItemAlign_ = listLayoutProperty->GetListItemAlign().value_or(V2::ListItemAlign::CENTER);
    CalculateLanes(listLayoutProperty->GetLayoutConstraint().value(), axis);

    if (lanes_.has_value() && lanes_.value() > 1) {
        if (NonNegative(currentOffset_)) {
            LayoutForwardForLaneList(layoutWrapper, contentLayoutConstraint, axis, mainSize);
        } else {
            LayoutBackwardForLaneList(layoutWrapper, contentLayoutConstraint, axis, mainSize);
        }
    } else {
        if (NonNegative(currentOffset_)) {
            LayoutForward(layoutWrapper, contentLayoutConstraint, axis, mainSize);
        } else {
            LayoutBackward(layoutWrapper, contentLayoutConstraint, axis, mainSize);
        }
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
        LOGI("the %{public}d wrapper is null in LayoutForward", preStartIndex_);
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
            LOGI("the start %{public}d index wrapper is null", currentIndex + 1);
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
        if (currentIndex >= 0) {
            currentEndPos = currentEndPos + spaceWidth_;
        }
    } while (LessNotEqual(currentEndPos, endMainPos_ + cacheSize));
    currentEndPos = currentEndPos - spaceWidth_;

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
        LOGI("the %{public}d wrapper is null in LayoutBackward", preEndIndex_);
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
            LOGI("the %{public}d wrapper is null", currentIndex - 1);
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
        if (currentIndex > 0) {
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
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0.0f);
    auto top = padding.top.value_or(0.0f);
    auto paddingOffset = OffsetF(left, top);

    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();

    // layout items.
    for (auto index = startIndex_.value(); index <= endIndex_.value(); ++index) {
        auto offset = paddingOffset;
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!wrapper) {
            LOGI("wrapper is out of boundary");
            continue;
        }
        if (lanes_.has_value() && lanes_.value() > 1) {
            int32_t laneIndex = (index - startIndex_.value()) % lanes_.value();
            float laneCrossOffset = CalculateLaneCrossOffset(GetCrossAxisSize(size, axis),
                GetCrossAxisSize(wrapper->GetGeometryNode()->GetFrameSize() * lanes_.value(), axis));
            if (axis == Axis::VERTICAL) {
                offset = offset + OffsetF(0, itemPosition_[index].first - currentOffset_) +
                         OffsetF(size.Width() / lanes_.value() * laneIndex, 0) + OffsetF(laneCrossOffset, 0);
            } else {
                offset = offset + OffsetF(itemPosition_[index].first - currentOffset_, 0) +
                         OffsetF(0, size.Width() / lanes_.value() * laneIndex) + OffsetF(0, laneCrossOffset);
            }
        } else {
            lanes_ = 1;
            float crossSize = GetCrossAxisSize(size, axis);
            float childCrossSize = GetCrossAxisSize(wrapper->GetGeometryNode()->GetFrameSize(), axis);
            float laneCrossOffset = CalculateLaneCrossOffset(crossSize, childCrossSize);
            if (axis == Axis::VERTICAL) {
                offset = offset + OffsetF(0, itemPosition_[index].first - currentOffset_)
                    + OffsetF(laneCrossOffset, 0);
            } else {
                offset = offset + OffsetF(itemPosition_[index].first - currentOffset_, 0)
                    + OffsetF(0, laneCrossOffset);
            }
        }
        wrapper->GetGeometryNode()->SetFrameOffset(offset);
        wrapper->Layout(parentOffset);
    }
}

float ListLayoutAlgorithm::CalculateLaneCrossOffset(float crossSize, float childCrossSize)
{
    if (!lanes_.has_value() || lanes_.value() <= 0) {
        return 0.0f;
    }
    float delta = (crossSize - childCrossSize) / lanes_.value();
    if (LessOrEqual(delta, 0)) {
        return 0.0f;
    }
    switch (listItemAlign_) {
        case OHOS::Ace::V2::ListItemAlign::START:
            return 0.0f;
        case OHOS::Ace::V2::ListItemAlign::CENTER:
            return delta / 2.0f;
        case OHOS::Ace::V2::ListItemAlign::END:
            return delta;
        default:
            LOGW("Invalid ListItemAlign: %{public}d", listItemAlign_);
            return 0.0f;
    }
}

void ListLayoutAlgorithm::CalculateLanes(const LayoutConstraintF& layoutConstraint, Axis axis)
{
    do {
        SizeF layoutParamMaxSize = layoutConstraint.maxSize;
        SizeF layoutParamMinSize = layoutConstraint.minSize;
        // Case 1: lane length constrain is not set
        //      1.1: use [lanes_] set by user if [lanes_] is set
        //      1.2: set [lanes_] to 1 if [lanes_] is not set
        if (!minLaneLength_.has_value() || !maxLaneLength_.has_value()) {
            if (!lanes_.has_value() || lanes_.value() <= 0) {
                lanes_ = 1;
            }
            maxLaneLength_ = GetCrossAxisSize(layoutParamMaxSize, axis) / lanes_.value();
            minLaneLength_ = GetCrossAxisSize(layoutParamMinSize, axis) / lanes_.value();
            break;
        }
        // Case 2: lane length constrain is set --> need to calculate [lanes_] according to contraint.
        // We agreed on such rules (assuming we have a vertical list here):
        // rule 1: [minLaneLength_] has a higher priority than [maxLaneLength_] when decide [lanes_], for e.g.,
        //         if [minLaneLength_] is 40, [maxLaneLength_] is 60, list's width is 120,
        //         the [lanes_] is 3 rather than 2.
        // rule 2: after [lanes_] is determined by rule 1, the width of lane will be as large as it can be, for e.g.,
        //         if [minLaneLength_] is 40, [maxLaneLength_] is 60, list's width is 132, the [lanes_] is 3
        //         according to rule 1, then the width of lane will be 132 / 3 = 44 rather than 40,
        //         its [minLaneLength_].
        ModifyLaneLength(layoutConstraint, axis);

        // if minLaneLength is 40, maxLaneLength is 60
        // when list's width is 120, lanes_ = 3
        // when list's width is 80, lanes_ = 2
        // when list's width is 70, lanes_ = 1
        float maxCrossSize = GetCrossAxisSize(layoutParamMaxSize, axis);
        float maxLanes = maxCrossSize / minLaneLength_.value();
        float minLanes = maxCrossSize / maxLaneLength_.value();
        // let's considerate scenarios when maxCrossSize > 0
        // now it's guaranteed that [minLaneLength_] <= [maxLaneLength_], i.e., maxLanes >= minLanes > 0
        // there are 3 scenarios:
        // 1. 1 > maxLanes >= minLanes > 0
        // 2. maxLanes >= 1 >= minLanes > 0
        // 3. maxLanes >= minLanes > 1

        // 1. 1 > maxLanes >= minLanes > 0 ---> maxCrossSize < minLaneLength_ =< maxLaneLength
        if (GreatNotEqual(1, maxLanes) && GreatOrEqual(maxLanes, minLanes)) {
            lanes_ = 1;
            minLaneLength_ = maxCrossSize;
            maxLaneLength_ = maxCrossSize;
            break;
        }
        // 2. maxLanes >= 1 >= minLanes > 0 ---> minLaneLength_ = maxCrossSize < maxLaneLength
        if (GreatOrEqual(maxLanes, 1) && LessOrEqual(minLanes, 1)) {
            lanes_ = std::floor(maxLanes);
            maxLaneLength_ = maxCrossSize;
            break;
        }
        // 3. maxLanes >= minLanes > 1 ---> minLaneLength_ <= maxLaneLength < maxCrossSize
        if (GreatOrEqual(maxLanes, minLanes) && GreatNotEqual(minLanes, 1)) {
            lanes_ = std::floor(maxLanes);
            break;
        }
        lanes_ = 1;
        LOGE("unexpected situation, set lanes to 1, maxLanes: %{public}f, minLanes: %{public}f, minLaneLength_: "
             "%{public}f, maxLaneLength_: %{public}f",
            maxLanes, minLanes, minLaneLength_.value(), maxLaneLength_.value());
    } while (0);
}

void ListLayoutAlgorithm::ModifyLaneLength(const LayoutConstraintF& layoutConstraint, Axis axis)
{
    if (LessOrEqual(maxLaneLength_.value(), 0.0)) {
        maxLaneLength_ = GetCrossAxisSize(layoutConstraint.maxSize, axis);
    }
    if (LessOrEqual(minLaneLength_.value(), 0.0)) {
        minLaneLength_ = std::min(GetCrossAxisSize(layoutConstraint.maxSize, axis), maxLaneLength_.value());
    }
    if (GreatNotEqual(minLaneLength_.value(), maxLaneLength_.value())) {
        LOGI("minLaneLength: %{public}f is greater than maxLaneLength: %{public}f, assign minLaneLength to"
             " maxLaneLength",
            minLaneLength_.value(), maxLaneLength_.value());
        maxLaneLength_ = minLaneLength_;
    }
}

void ListLayoutAlgorithm::LayoutForwardForLaneList(
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
    float mainLength = 0.0f;
    bool outOfListSize = false;
    do {
        currentStartPos = currentEndPos;
        for (int32_t i = 0; i < lanes_.value(); i++) {
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex + 1);
            if (!wrapper) {
                LOGE("the start %{public}d index wrapper is null", currentIndex + 1);
                outOfListSize = true;
                break;
            }
            ++currentIndex;
            {
                ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem");
                wrapper->Measure(layoutConstraint);
            }
            mainLength = GetMainAxisSize(wrapper->GetGeometryNode()->GetFrameSize(), axis);
            // out of display area, mark inactive.
            if (LessNotEqual(currentStartPos + mainLength, startMainPos_ - cacheSize)) {
                inActiveItems.emplace(currentIndex);
            } else {
                // mark new start index.
                if (!newStartIndex) {
                    newStartIndex = currentIndex;
                }
            }
            itemPosition_[currentIndex] = { currentStartPos, currentStartPos + mainLength };
        }
        currentEndPos = currentStartPos + mainLength;
        if (outOfListSize) {
            break;
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

void ListLayoutAlgorithm::LayoutBackwardForLaneList(
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
        currentEndPos = currentStartPos;
        float mainLength = 0.0f;
        for (int32_t i = 0; i < lanes_.value(); i++) {
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex - 1);
            if (!wrapper) {
                LOGE("the start %{public}d index wrapper is null", currentIndex - 1);
                break;
            }
            --currentIndex;
            {
                ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem");
                wrapper->Measure(layoutConstraint);
            }
            mainLength = GetMainAxisSize(wrapper->GetGeometryNode()->GetFrameSize(), axis);
            // out of display area, mark inactive.
            if (LessNotEqual(currentEndPos - mainLength, startMainPos_ + cacheSize)) {
                inActiveItems.emplace(currentIndex);
            } else {
                // mark new start index.
                if (!newEndIndex) {
                    newEndIndex = currentIndex;
                }
            }
            itemPosition_[currentIndex] = { currentEndPos - mainLength, currentEndPos };
        }
        currentStartPos = currentEndPos - mainLength;
        if (currentIndex <= 0) {
            break;
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
} // namespace OHOS::Ace::NG
