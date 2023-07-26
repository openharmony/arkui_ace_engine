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

#include "core/components_ng/pattern/list/list_lanes_layout_algorithm.h"

#include "base/utils/utils.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void ListLanesLayoutAlgorithm::UpdateListItemConstraint(
    Axis axis, const OptionalSizeF& selfIdealSize, LayoutConstraintF& contentConstraint)
{
    contentConstraint.parentIdealSize = selfIdealSize;
    contentConstraint.maxSize.SetMainSize(Infinity<float>(), axis);
    groupLayoutConstraint_ = contentConstraint;
    auto crossSizeOptional = selfIdealSize.CrossSize(axis);
    if (crossSizeOptional.has_value()) {
        float crossSize = crossSizeOptional.value();
        groupLayoutConstraint_.maxSize.SetCrossSize(crossSize, axis);
        if (lanes_ > 1) {
            float laneGutter = GetLaneGutter();
            crossSize = (crossSize + laneGutter) / lanes_ - laneGutter;
            crossSize = crossSize <= 0 ? 1 : crossSize;
        }
        if (maxLaneLength_.has_value() && maxLaneLength_.value() < crossSize) {
            crossSize = maxLaneLength_.value();
        }
        contentConstraint.percentReference.SetCrossSize(crossSize, axis);
        contentConstraint.parentIdealSize.SetCrossSize(crossSize, axis);
        contentConstraint.maxSize.SetCrossSize(crossSize, axis);
        if (minLaneLength_.has_value()) {
            contentConstraint.minSize.SetCrossSize(minLaneLength_.value(), axis);
        }
    }
}

int32_t ListLanesLayoutAlgorithm::LayoutALineForward(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, Axis axis, int32_t& currentIndex, float startPos, float& endPos)
{
    float mainLen = 0.0f;
    bool isGroup = false;
    int32_t cnt = 0;
    int32_t lanes = lanes_ > 1 ? lanes_ : 1;
    for (int32_t i = 0; i < lanes && currentIndex + 1 <= GetMaxListItemIndex(); i++) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex + 1);
        if (!wrapper) {
            break;
        }
        isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
        if (isGroup && cnt > 0) {
            LayoutWrapper::RemoveChildInRenderTree(wrapper);
            isGroup = false;
            break;
        }
        cnt++;
        ++currentIndex;
        if (isGroup) {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItemGroup:%d", currentIndex);
            auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
            SetListItemGroupParam(wrapper, startPos, true, listLayoutProperty, false);
            wrapper->Measure(groupLayoutConstraint_);
        } else {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem:%d", currentIndex);
            wrapper->Measure(layoutConstraint);
        }
        mainLen = std::max(mainLen, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis));
        if (isGroup) {
            break;
        }
    }
    if (cnt > 0) {
        endPos = startPos + mainLen;
        for (int32_t i = 0; i < cnt; i++) {
            SetItemInfo(currentIndex - i, { startPos, endPos, isGroup });
        }
    }
    return cnt;
}

int32_t ListLanesLayoutAlgorithm::LayoutALineBackward(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, Axis axis, int32_t& currentIndex, float endPos, float& startPos)
{
    float mainLen = 0.0f;
    bool isGroup = false;
    int32_t cnt = 0;
    int32_t lanes = lanes_ > 1 ? lanes_ : 1;
    for (int32_t i = 0; i < lanes && currentIndex - 1 >= 0; i++) {
        if (currentIndex > GetMaxListItemIndex() + 1) {
            --currentIndex;
            continue;
        }
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex - 1);
        if (!wrapper) {
            break;
        }
        isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
        if (isGroup && cnt > 0) {
            LayoutWrapper::RemoveChildInRenderTree(wrapper);
            isGroup = false;
            break;
        }
        --currentIndex;

        cnt++;
        if (isGroup) {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItemGroup:%d", currentIndex);
            auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
            SetListItemGroupParam(wrapper, endPos, false, listLayoutProperty, false);
            wrapper->Measure(groupLayoutConstraint_);
        } else {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem:%d", currentIndex);
            wrapper->Measure(layoutConstraint);
        }
        mainLen = std::max(mainLen, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis));
        if (isGroup || (currentIndex - FindLanesStartIndex(layoutWrapper, currentIndex)) % lanes == 0) {
            break;
        }
    }
    if (cnt > 0) {
        startPos = endPos - mainLen;
        for (int32_t i = 0; i < cnt; i++) {
            SetItemInfo(currentIndex + i, { startPos, endPos, isGroup });
        }
    }
    return cnt;
}

int32_t ListLanesLayoutAlgorithm::CalculateLanesParam(std::optional<float>& minLaneLength,
    std::optional<float>& maxLaneLength, int32_t lanes, std::optional<float> crossSizeOptional, float laneGutter)
{
    if (lanes < 1) {
        return 1;
    }
    // Case 1: lane length constrain is not set
    //      1.1: use [lanes] set by user if [lanes] is set
    //      1.2: set [lanes] to 1 if [lanes] is not set
    if (!crossSizeOptional.has_value() || GreaterOrEqualToInfinity(crossSizeOptional.value()) ||
        !minLaneLength.has_value() || !maxLaneLength.has_value()) {
        maxLaneLength.reset();
        minLaneLength.reset();
        return lanes;
    }
    // Case 2: lane length constrain is set --> need to calculate [lanes_] according to contraint.
    // We agreed on such rules (assuming we have a vertical list here):
    // rule 1: [minLaneLength_] has a higher priority than [maxLaneLength_] when decide [lanes_], for e.g.,
    //         if [minLaneLength_] is 40, [maxLaneLength_] is 60, list's width is 120,
    //         the [lanes_] is 3 rather than 2.
    // rule 2: after [lanes_] is determined by rule 1, the width of lane will be as large as it can be, for
    // e.g.,
    //         if [minLaneLength_] is 40, [maxLaneLength_] is 60, list's width is 132, the [lanes_] is 3
    //         according to rule 1, then the width of lane will be 132 / 3 = 44 rather than 40,
    //         its [minLaneLength_].
    auto crossSize = crossSizeOptional.value();
    ModifyLaneLength(minLaneLength, maxLaneLength, crossSize);

    // if minLaneLength is 40, maxLaneLength is 60
    // when list's width is 120, lanes_ = 3
    // when list's width is 80, lanes_ = 2
    // when list's width is 70, lanes_ = 1
    float maxLanes = (crossSize + laneGutter) / (minLaneLength.value() + laneGutter);
    float minLanes = (crossSize + laneGutter) / (maxLaneLength.value() + laneGutter);
    // let's considerate scenarios when maxCrossSize > 0
    // now it's guaranteed that [minLaneLength_] <= [maxLaneLength_], i.e., maxLanes >= minLanes > 0
    // there are 3 scenarios:
    // 1. 1 > maxLanes >= minLanes > 0
    // 2. maxLanes >= 1 >= minLanes > 0
    // 3. maxLanes >= minLanes > 1
    // 1. 1 > maxLanes >= minLanes > 0 ---> maxCrossSize < minLaneLength_ =< maxLaneLength
    if (GreatNotEqual(1, maxLanes) && GreatOrEqual(maxLanes, minLanes)) {
        lanes = 1;
        minLaneLength = crossSize;
        maxLaneLength = crossSize;
        return lanes;
    }
    // 2. maxLanes >= 1 >= minLanes > 0 ---> minLaneLength_ = maxCrossSize < maxLaneLength
    if (GreatOrEqual(maxLanes, 1) && LessOrEqual(minLanes, 1)) {
        lanes = std::floor(maxLanes);
        maxLaneLength = crossSize;
        return lanes;
    }
    // 3. maxLanes >= minLanes > 1 ---> minLaneLength_ <= maxLaneLength < maxCrossSize
    if (GreatOrEqual(maxLanes, minLanes) && GreatNotEqual(minLanes, 1)) {
        lanes = std::floor(maxLanes);
        return lanes;
    }
    lanes = 1;
    LOGE("unexpected situation, set lanes to 1, maxLanes: %{public}f, minLanes: %{public}f, minLaneLength_: "
            "%{public}f, maxLaneLength_: %{public}f",
        maxLanes, minLanes, minLaneLength.value(), maxLaneLength.value());
    return lanes;
}

void ListLanesLayoutAlgorithm::CalculateLanes(const RefPtr<ListLayoutProperty>& layoutProperty,
    const LayoutConstraintF& layoutConstraint, std::optional<float> crossSizeOptional, Axis axis)
{
    auto contentConstraint = layoutProperty->GetContentLayoutConstraint().value();
    auto mainPercentRefer = GetMainAxisSize(contentConstraint.percentReference, axis);
    int32_t lanes = layoutProperty->GetLanes().value_or(1);
    lanes = lanes > 1 ? lanes : 1;
    if (layoutProperty->GetLaneMinLength().has_value()) {
        minLaneLength_ = ConvertToPx(
            layoutProperty->GetLaneMinLength().value(), layoutConstraint.scaleProperty, mainPercentRefer);
    }
    if (layoutProperty->GetLaneMaxLength().has_value()) {
        maxLaneLength_ = ConvertToPx(
            layoutProperty->GetLaneMaxLength().value(), layoutConstraint.scaleProperty, mainPercentRefer);
    }
    float laneGutter = 0.0f;
    if (layoutProperty->GetLaneGutter().has_value()) {
        laneGutter = ConvertToPx(
            layoutProperty->GetLaneGutter().value(), layoutConstraint.scaleProperty, crossSizeOptional.value_or(0.0))
                .value();
        SetLaneGutter(laneGutter);
    }
    lanes_ = CalculateLanesParam(minLaneLength_, maxLaneLength_, lanes, crossSizeOptional, laneGutter);
}

void ListLanesLayoutAlgorithm::ModifyLaneLength(std::optional<float>& minLaneLength,
    std::optional<float>& maxLaneLength, float crossSize)
{
    if (GreatNotEqual(minLaneLength.value(), maxLaneLength.value())) {
        LOGI("minLaneLength: %{public}f is greater than maxLaneLength: %{public}f, assign minLaneLength to"
             " maxLaneLength",
            minLaneLength.value(), maxLaneLength.value());
        maxLaneLength = minLaneLength;
    }
}

float ListLanesLayoutAlgorithm::CalculateLaneCrossOffset(float crossSize, float childCrossSize)
{
    if (lanes_ <= 0) {
        return 0.0f;
    }
    return ListLayoutAlgorithm::CalculateLaneCrossOffset(crossSize / lanes_, childCrossSize / lanes_);
}

int32_t ListLanesLayoutAlgorithm::FindLanesStartIndex(LayoutWrapper* layoutWrapper, int32_t startIndex, int32_t index)
{
    auto wrapper  = layoutWrapper->GetOrCreateChildByIndex(index, false);
    CHECK_NULL_RETURN_NOLOG(wrapper, index);
    if (wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG) {
        return index;
    }
    for (int32_t idx = index; idx > startIndex; idx--) {
        auto wrapper  = layoutWrapper->GetOrCreateChildByIndex(idx - 1, false);
        CHECK_NULL_RETURN_NOLOG(wrapper, idx);
        if (wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG) {
            return idx;
        }
    }
    if (startIndex == 0) {
        return 0;
    }
    return -1;
}

int32_t ListLanesLayoutAlgorithm::FindLanesStartIndex(LayoutWrapper* layoutWrapper, int32_t index)
{
    if (lanes_ == 1) {
        return 0;
    }
    auto it = lanesItemRange_.upper_bound(index);
    if (it == lanesItemRange_.begin()) {
        int32_t startIdx = FindLanesStartIndex(layoutWrapper, 0, index);
        lanesItemRange_[startIdx] = index;
        return startIdx;
    }
    it--;
    if (it->second >= index) {
        return it->first;
    }
    int32_t startIdx = FindLanesStartIndex(layoutWrapper, it->second, index);
    if (startIdx >= 0) {
        lanesItemRange_[startIdx] = index;
        return startIdx;
    }
    it->second = index;
    return it->first;
}

int32_t ListLanesLayoutAlgorithm::GetLanesFloor(LayoutWrapper* layoutWrapper, int32_t index)
{
    if (lanes_ > 1) {
        int32_t startIndex = FindLanesStartIndex(layoutWrapper, index);
        return index - (index - startIndex) % lanes_;
    }
    return index;
}

void ListLanesLayoutAlgorithm::SetCacheCount(LayoutWrapper* layoutWrapper, int32_t cachedCount)
{
    auto range = layoutWrapper->GetLazyBuildRange();
    auto itemPosition = GetItemPosition();
    if (!itemPosition.empty() && range.first >= 0) {
        auto startNode = itemPosition.begin();
        if ((startNode->first >= range.first && startNode->first < range.second) && startNode->second.isGroup) {
            layoutWrapper->SetCacheCount(cachedCount);
            return;
        }
        auto endNode = itemPosition.rbegin();
        if ((endNode->first >= range.first && endNode->first < range.second) && endNode->second.isGroup) {
            layoutWrapper->SetCacheCount(cachedCount);
            return;
        }
    }
    layoutWrapper->SetCacheCount(cachedCount * GetLanes());
}
} // namespace OHOS::Ace::NG