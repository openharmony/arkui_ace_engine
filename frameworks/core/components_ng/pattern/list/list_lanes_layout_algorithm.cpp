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

namespace OHOS::Ace::NG {

void ListLanesLayoutAlgorithm::UpdateListItemConstraint(
    Axis axis, const OptionalSizeF& selfIdealSize, LayoutConstraintF& contentConstraint)
{
    contentConstraint.parentIdealSize = selfIdealSize;
    groupLayoutConstraint_ = contentConstraint;
    if (axis == Axis::VERTICAL) {
        contentConstraint.maxSize.SetHeight(Infinity<float>());
        groupLayoutConstraint_.maxSize.SetHeight(Infinity<float>());
        auto width = selfIdealSize.Width();
        if (width.has_value()) {
            float crossSize = width.value();
            groupLayoutConstraint_.maxSize.SetWidth(crossSize);
            if (lanes_.has_value() && lanes_.value() > 1) {
                crossSize /= lanes_.value();
            }
            if (maxLaneLength_.has_value() && maxLaneLength_.value() < crossSize) {
                crossSize = maxLaneLength_.value();
            }
            contentConstraint.percentReference.SetWidth(crossSize);
            contentConstraint.parentIdealSize.SetWidth(crossSize);
            contentConstraint.maxSize.SetWidth(crossSize);
            if (minLaneLength_.has_value()) {
                contentConstraint.minSize.SetWidth(minLaneLength_.value());
            } else {
                contentConstraint.minSize.SetWidth(crossSize);
            }
        }
        return;
    }
    contentConstraint.maxSize.SetWidth(Infinity<float>());
    groupLayoutConstraint_.maxSize.SetWidth(Infinity<float>());
    auto height = selfIdealSize.Height();
    if (height.has_value()) {
        float crossSize = height.value();
        groupLayoutConstraint_.maxSize.SetHeight(crossSize);
        if (lanes_.has_value() && lanes_.value() > 1) {
            crossSize /= lanes_.value();
        }
        if (maxLaneLength_.has_value() && maxLaneLength_.value() < crossSize) {
            crossSize = maxLaneLength_.value();
        }
        contentConstraint.percentReference.SetHeight(crossSize);
        contentConstraint.parentIdealSize.SetHeight(crossSize);
        contentConstraint.maxSize.SetHeight(crossSize);
        if (minLaneLength_.has_value()) {
            contentConstraint.minSize.SetHeight(minLaneLength_.value());
        } else {
            contentConstraint.minSize.SetHeight(crossSize);
        }
    }
}

int32_t ListLanesLayoutAlgorithm::LayoutALineForward(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, Axis axis, int32_t& currentIndex, float startPos, float& endPos)
{
    float mainLen = 0.0f;
    bool isGroup = false;
    int32_t cnt = 0;
    int32_t lanes = lanes_.has_value() && lanes_.value() > 1 ? lanes_.value() : 1;
    for (int32_t i = 0; i < lanes; i++) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex + 1);
        if (!wrapper) {
            LOGI("the start %{public}d index wrapper is null", currentIndex + 1);
            break;
        }
        auto itemGroup = GetListItemGroup(wrapper);
        if (itemGroup && cnt > 0) {
            LayoutWrapper::RemoveChildInRenderTree(wrapper);
            break;
        }
        cnt++;
        ++currentIndex;
        if (itemGroup) {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItemGroup:%d", currentIndex);
            SetListItemGroupProperty(itemGroup, axis, lanes);
            wrapper->Measure(groupLayoutConstraint_);
        } else {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem:%d", currentIndex);
            wrapper->Measure(layoutConstraint);
        }
        mainLen = std::max(mainLen, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis));
        if (itemGroup) {
            isGroup = true;
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
    int32_t lanes = lanes_.has_value() && lanes_.value() > 1 ? lanes_.value() : 1;
    for (int32_t i = 0; i < lanes; i++) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex - 1);
        if (!wrapper) {
            LOGI("the %{public}d wrapper is null", currentIndex - 1);
            break;
        }
        auto itemGroup = GetListItemGroup(wrapper);
        if (itemGroup && cnt > 0) {
            LayoutWrapper::RemoveChildInRenderTree(wrapper);
            break;
        }
        --currentIndex;
        cnt++;
        if (itemGroup) {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItemGroup:%d", currentIndex);
            SetListItemGroupProperty(itemGroup, axis, lanes);
            wrapper->Measure(groupLayoutConstraint_);
        } else {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem:%d", currentIndex);
            wrapper->Measure(layoutConstraint);
        }
        mainLen = std::max(mainLen, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis));
        if (itemGroup || (currentIndex - FindLanesStartIndex(layoutWrapper, currentIndex)) % lanes == 0) {
            isGroup = static_cast<bool>(itemGroup);
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

void ListLanesLayoutAlgorithm::CalculateLanes(const RefPtr<ListLayoutProperty>& layoutProperty,
    const LayoutConstraintF& layoutConstraint, Axis axis)
{
    auto contentConstraint = layoutProperty->GetContentLayoutConstraint().value();
    auto mainPercentRefer = GetMainAxisSize(contentConstraint.percentReference, axis);
    lanes_ = layoutProperty->GetLanes();
    if (layoutProperty->GetLaneMinLength().has_value()) {
        minLaneLength_ = ConvertToPx(
            layoutProperty->GetLaneMinLength().value(), layoutConstraint.scaleProperty, mainPercentRefer);
    }
    if (layoutProperty->GetLaneMaxLength().has_value()) {
        maxLaneLength_ = ConvertToPx(
            layoutProperty->GetLaneMaxLength().value(), layoutConstraint.scaleProperty, mainPercentRefer);
    }
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
        // rule 2: after [lanes_] is determined by rule 1, the width of lane will be as large as it can be, for
        // e.g.,
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
    } while (false);
}

void ListLanesLayoutAlgorithm::ModifyLaneLength(const LayoutConstraintF& layoutConstraint, Axis axis)
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

float ListLanesLayoutAlgorithm::CalculateLaneCrossOffset(float crossSize, float childCrossSize)
{
    if (!lanes_.has_value() || lanes_.value() <= 0) {
        return 0.0f;
    }
    return ListLayoutAlgorithm::CalculateLaneCrossOffset(crossSize / lanes_.value(), childCrossSize / lanes_.value());
}

int32_t ListLanesLayoutAlgorithm::FindLanesStartIndex(LayoutWrapper* layoutWrapper, int32_t startIndex, int32_t index)
{
    auto wrapper  = layoutWrapper->GetOrCreateChildByIndex(index, false);
    if (!wrapper) {
        return index;
    }
    auto itemGroup = GetListItemGroup(wrapper);
    if (itemGroup) {
        return index;
    }
    for (int32_t idx = index; idx > startIndex; idx--) {
        auto wrapper  = layoutWrapper->GetOrCreateChildByIndex(idx - 1, false);
        if (!wrapper) {
            return idx;
        }
        auto itemGroup = GetListItemGroup(wrapper);
        if (itemGroup) {
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
    if (GetLanes() == 1) {
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
    if (startIdx < 0) {
        lanesItemRange_[startIdx] = index;
        return startIdx;
    }
    it->second = index;
    return it->first;
}

int32_t ListLanesLayoutAlgorithm::GetLanesFloor(LayoutWrapper* layoutWrapper, int32_t index)
{
    if (GetLanes() > 1) {
        int32_t startIndex = FindLanesStartIndex(layoutWrapper, index);
        return index - (index - startIndex) % GetLanes();
    }
    return index;
}
} // namespace OHOS::Ace::NG