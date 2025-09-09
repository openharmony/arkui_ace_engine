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

#include "base/log/event_report.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void ListLanesLayoutAlgorithm::UpdateListItemConstraint(
    Axis axis, const OptionalSizeF& selfIdealSize, LayoutConstraintF& contentConstraint)
{
    contentConstraint.parentIdealSize = selfIdealSize;
    contentConstraint.maxSize.SetMainSize(LayoutInfinity<float>(), axis);
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

float ListLanesLayoutAlgorithm::GetChildHeight(LayoutWrapper* layoutWrapper, int32_t childIndex)
{
    CHECK_NULL_RETURN(childrenSize_, 0.0f);
    float mainLen = 0.0f;
    int32_t laneCeil = GetLanesCeil(layoutWrapper, childIndex);
    for (int32_t index = GetLanesFloor(layoutWrapper, childIndex); index <= laneCeil; index++) {
        mainLen = std::max(mainLen, childrenSize_->GetChildSize(index, isStackFromEnd_));
    }
    return mainLen;
}

float ListLanesLayoutAlgorithm::MeasureAndGetChildHeight(LayoutWrapper* layoutWrapper, int32_t childIndex,
    bool groupLayoutAll)
{
    auto wrapper = GetListItem(layoutWrapper, childIndex);
    if (!wrapper) {
        ReportGetChildError("MeasureAndGetChildHeightLanes", childIndex);
        return 0.0f;
    }
    bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    float mainLen = 0.0f;
    if (isGroup) {
        auto listLayoutProperty =
            AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
        // true: layout forward, true: layout all group items.
        SetListItemGroupParam(wrapper, childIndex, 0.0f, true, listLayoutProperty, true);
        wrapper->Measure(groupLayoutConstraint_);
        mainLen = GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
        CheckGroupMeasureBreak(wrapper);
    } else {
        auto laneCeil = GetLanesCeil(layoutWrapper, childIndex);
        for (int32_t i = GetLanesFloor(layoutWrapper, childIndex); i <= laneCeil; i++) {
            auto wrapper = GetListItem(layoutWrapper, i);
            if (!wrapper) {
                ReportGetChildError("MeasureAndGetChildHeightLanesItem", i);
                continue;
            }
            wrapper->Measure(childLayoutConstraint_);
            mainLen = std::max(mainLen, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_));
        }
    }
    return mainLen;
}

void ListLanesLayoutAlgorithm::MeasureGroup(LayoutWrapper* listWrapper, const RefPtr<LayoutWrapper>& groupWrapper,
    int32_t index, float& pos, bool forward)
{
    CHECK_NULL_VOID(groupWrapper);
    auto host = groupWrapper->GetHostNode();
    const char* direction = forward ? "Forward" : "Backward";
    if (host) {
        ACE_SCOPED_TRACE("[Measure%sListItemGroup:%d][self:%d][parent:%d]", direction, index, host->GetId(),
            host->GetParent() ? host->GetParent()->GetId() : 0);
    }
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(listWrapper->GetLayoutProperty());
    SetListItemGroupParam(groupWrapper, index, pos, forward, listLayoutProperty, false);
    groupWrapper->Measure(groupLayoutConstraint_);
    if (forward && (LessOrEqual(pos, 0.0f) || GetPrevMeasureBreak())) {
        AdjustStartPosition(groupWrapper, pos);
    }
    CheckGroupMeasureBreak(groupWrapper);
}

void ListLanesLayoutAlgorithm::MeasureItem(const RefPtr<LayoutWrapper>& itemWrapper, int32_t index, bool forward)
{
    CHECK_NULL_VOID(itemWrapper);
    auto host = itemWrapper->GetHostNode();
    const char* direction = forward ? "Forward" : "Backward";
    if (host) {
        ACE_SCOPED_TRACE("[Measure%sListItem:%d][self:%d][parent:%d]", direction, index, host->GetId(),
            host->GetParent() ? host->GetParent()->GetId() : 0);
    }
    itemWrapper->Measure(childLayoutConstraint_);
}

int32_t ListLanesLayoutAlgorithm::LayoutALineForward(LayoutWrapper* layoutWrapper,
    int32_t& currentIndex, float startPos, float& endPos)
{
    float mainLen = 0.0f;
    bool isGroup = false;
    int32_t cnt = 0;
    int32_t lanes = lanes_ > 1 ? lanes_ : 1;
    if (firstItemInfo_ && firstItemInfo_.value().first == currentIndex + 1) {
        ++currentIndex;
        endPos = firstItemInfo_.value().second.endPos;
        SetItemInfo(currentIndex, std::move(firstItemInfo_.value().second));
        firstItemInfo_.reset();
        return 1;
    } else if (firstItemInfo_) {
        firstItemInfo_.reset();
    }
    for (int32_t i = 0; i < lanes && currentIndex + 1 <= GetMaxListItemIndex() && !isGroup; i++) {
        auto wrapper = GetListItem(layoutWrapper, currentIndex + 1);
        if (!wrapper) {
            ReportGetChildError("LayoutALineForwardLanes", currentIndex + 1);
            break;
        }
        isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
        if (isGroup && cnt > 0) {
            wrapper->SetActive(false);
            isGroup = false;
            break;
        }
        cnt++;
        ++currentIndex;
        if (isGroup) {
            MeasureGroup(layoutWrapper, wrapper, currentIndex, startPos, true);
        } else if (CheckNeedMeasure(wrapper)) {
            MeasureItem(wrapper, currentIndex, true);
        }
        mainLen = std::max(mainLen, childrenSize_ ? childrenSize_->GetChildSize(currentIndex, isStackFromEnd_) :
            GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_));
    }
    if (cnt > 0) {
        endPos = startPos + mainLen;
        for (int32_t i = 0; i < cnt; i++) {
            auto wrap = GetListItem(layoutWrapper, currentIndex - i);
            int32_t id = wrap->GetHostNode()->GetId();
            SetItemInfo(currentIndex - i, { id, startPos, endPos, isGroup });
        }
    }
    return cnt;
}

int32_t ListLanesLayoutAlgorithm::LayoutALineBackward(LayoutWrapper* layoutWrapper,
    int32_t& currentIndex, float endPos, float& startPos)
{
    float mainLen = 0.0f;
    bool isGroup = false;
    int32_t cnt = 0;
    int32_t lanes = lanes_ > 1 ? lanes_ : 1;
    if (firstItemInfo_ && firstItemInfo_.value().first == currentIndex - 1) {
        --currentIndex;
        startPos = firstItemInfo_.value().second.startPos;
        SetItemInfo(currentIndex, std::move(firstItemInfo_.value().second));
        firstItemInfo_.reset();
        return 1;
    } else if (firstItemInfo_) {
        firstItemInfo_.reset();
    }
    for (int32_t i = 0; i < lanes && currentIndex - 1 >= 0; i++) {
        if (currentIndex > GetMaxListItemIndex() + 1) {
            --currentIndex;
            continue;
        }
        auto wrapper = GetListItem(layoutWrapper, currentIndex - 1);
        if (!wrapper) {
            ReportGetChildError("LayoutALineBackwardLanes", currentIndex - 1);
            break;
        }
        isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
        if (isGroup && cnt > 0) {
            wrapper->SetActive(false);
            isGroup = false;
            break;
        }
        --currentIndex;
        cnt++;
        if (isGroup) {
            MeasureGroup(layoutWrapper, wrapper, currentIndex, endPos, false);
        } else if (CheckNeedMeasure(wrapper)) {
            MeasureItem(wrapper, currentIndex, false);
        }
        mainLen = std::max(mainLen, childrenSize_ ? childrenSize_->GetChildSize(currentIndex, isStackFromEnd_) :
            GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_));
        if (CheckCurRowMeasureFinished(layoutWrapper, currentIndex, isGroup)) {
            break;
        }
    }
    if (cnt > 0) {
        startPos = endPos - mainLen;
        for (int32_t i = 0; i < cnt; i++) {
            auto wrap = GetListItem(layoutWrapper, currentIndex + i);
            int32_t id = wrap->GetHostNode()->GetId();
            SetItemInfo(currentIndex + i, { id, startPos, endPos, isGroup });
        }
    }
    return cnt;
}

bool ListLanesLayoutAlgorithm::CheckCurRowMeasureFinished(LayoutWrapper* layoutWrapper, int32_t curIndex, bool isGroup)
{
    if (childrenSize_) {
        return isGroup || posMap_->GetRowStartIndex(curIndex) == curIndex;
    }
    int32_t lanes = lanes_ > 1 ? lanes_ : 1;
    return isGroup || (curIndex - FindLanesStartIndex(layoutWrapper, curIndex)) % lanes == 0;
}

void ListLanesLayoutAlgorithm::SetCacheCount(LayoutWrapper* layoutWrapper, int32_t cacheCount)
{
    bool hasGroup = false;
    auto& itemPosition = GetItemPosition();
    for (auto &pos : itemPosition) {
        if (pos.second.isGroup) {
            hasGroup = true;
            break;
        }
    }
    int32_t count = hasGroup ? cacheCount : cacheCount * lanes_;
    layoutWrapper->SetCacheCount(count);
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
    return lanes;
}

void ListLanesLayoutAlgorithm::CalculateLanes(const RefPtr<ListLayoutProperty>& layoutProperty,
    const LayoutConstraintF& layoutConstraint, std::optional<float> crossSizeOptional, Axis axis)
{
    const auto& contentConstraintOps = layoutProperty->GetContentLayoutConstraint();
    CHECK_NULL_VOID(contentConstraintOps);
    auto contentConstraint = contentConstraintOps.value();
    auto mainPercentRefer = GetMainAxisSize(contentConstraint.percentReference, axis);
    int32_t lanes = layoutProperty->GetLanes().value_or(1);
    lanes = lanes > 1 ? lanes : 1;
    if (layoutProperty->GetLaneMinLength().has_value()) {
        minLaneLength_ =
            ConvertToPx(layoutProperty->GetLaneMinLength().value(), layoutConstraint.scaleProperty, mainPercentRefer);
    }
    if (layoutProperty->GetLaneMaxLength().has_value()) {
        maxLaneLength_ =
            ConvertToPx(layoutProperty->GetLaneMaxLength().value(), layoutConstraint.scaleProperty, mainPercentRefer);
    }
    float laneGutter = 0.0f;
    if (layoutProperty->GetLaneGutter().has_value()) {
        laneGutter = ConvertToPx(layoutProperty->GetLaneGutter().value(),
            layoutConstraint.scaleProperty, crossSizeOptional.value_or(0.0)).value_or(0.0f);
        SetLaneGutter(laneGutter);
    }
    lanes_ = CalculateLanesParam(minLaneLength_, maxLaneLength_, lanes, crossSizeOptional, laneGutter);
}

void ListLanesLayoutAlgorithm::ModifyLaneLength(
    std::optional<float>& minLaneLength, std::optional<float>& maxLaneLength, float crossSize)
{
    if (GreatNotEqual(minLaneLength.value(), maxLaneLength.value())) {
        maxLaneLength = minLaneLength;
    }
}

float ListLanesLayoutAlgorithm::CalculateLaneCrossOffset(float crossSize, float childCrossSize, bool isGroup)
{
    if (lanes_ <= 0) {
        return 0.0f;
    }
    if (isGroup) {
        return ListLayoutAlgorithm::CalculateLaneCrossOffset(crossSize, childCrossSize, isGroup);
    }
    return ListLayoutAlgorithm::CalculateLaneCrossOffset((crossSize + GetLaneGutter()) / lanes_,
        childCrossSize / lanes_, isGroup);
}

int32_t ListLanesLayoutAlgorithm::GetLazyForEachIndex(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_RETURN(host, -1);
    auto parent = host->GetParent();
    auto lazyForEach = AceType::DynamicCast<LazyForEachNode>(parent);
    if (lazyForEach) {
        return lazyForEach->GetIndexByUINode(host);
    }
    while (parent && !AceType::InstanceOf<FrameNode>(parent)) {
        if (AceType::InstanceOf<RepeatVirtualScrollNode>(parent)) {
            return parent->GetFrameNodeIndex(host);
        }
        if (AceType::InstanceOf<RepeatVirtualScroll2Node>(parent)) {
            return parent->GetFrameNodeIndex(host);
        }
        parent = parent->GetParent();
    }
    return -1;
}

int32_t ListLanesLayoutAlgorithm::FindLanesStartIndex(LayoutWrapper* layoutWrapper, int32_t startIndex, int32_t index)
{
    auto wrapper = GetListItem(layoutWrapper, index);
    CHECK_NULL_RETURN(wrapper, index);
    if (wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG) {
        return index;
    }
    auto lazyIndex = GetLazyForEachIndex(wrapper->GetHostNode());
    if (lazyIndex > 0) {
        index -= lazyIndex;
    }
    for (int32_t idx = index; idx > startIndex; idx--) {
        auto wrapper = GetListItem(layoutWrapper, idx - 1);
        CHECK_NULL_RETURN(wrapper, idx);
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
        if (childrenSize_) {
            return posMap_->GetRowStartIndex(index);
        }
        int32_t startIndex = FindLanesStartIndex(layoutWrapper, index);
        return index - (index - startIndex) % lanes_;
    }
    return index;
}

int32_t ListLanesLayoutAlgorithm::GetLanesCeil(LayoutWrapper* layoutWrapper, int32_t index)
{
    if (lanes_ > 1) {
        if (childrenSize_) {
            return posMap_->GetRowEndIndex(index);
        }
        int32_t startIndex = GetLanesFloor(layoutWrapper, index);
        while (startIndex == GetLanesFloor(layoutWrapper, index + 1)) {
            index++;
        }
    }
    return index;
}

void ListLanesLayoutAlgorithm::LayoutCachedALine(LayoutWrapper* layoutWrapper,
    std::pair<const int, ListItemInfo>& pos, int32_t startIndex, float crossSize)
{
    auto wrapper = GetChildByIndex(layoutWrapper, pos.first, true);
    CHECK_NULL_VOID(wrapper);
    bool isDirty = wrapper->CheckNeedForceMeasureAndLayout() || !IsListLanesEqual(wrapper);
    LayoutItem(wrapper, pos.first, pos.second, startIndex, crossSize);
    SyncGeometry(wrapper, isDirty);
    wrapper->SetActive(false);
    SetCachedItemInfo(pos.first, std::move(pos.second));
}

std::pair<bool, bool> ListLanesLayoutAlgorithm::CheckACachedItem(
    const RefPtr<LayoutWrapper>& wrapper, int32_t cnt, bool& isGroup) const
{
    if (!wrapper) {
        return std::make_pair(true, true);
    }
    isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (isGroup && cnt > 0) {
        isGroup = false;
        return std::make_pair(true, false);
    }
    bool isDirty = wrapper->CheckNeedForceMeasureAndLayout() || !IsListLanesEqual(wrapper);
    if (!isGroup && (isDirty || CheckLayoutConstraintChanged(wrapper))) {
        if (isDirty && !wrapper->GetHostNode()->IsLayoutComplete()) {
            return std::make_pair(true, true);
        }
        return std::make_pair(false, true);
    }
    return std::make_pair(false, false);
}

int32_t ListLanesLayoutAlgorithm::LayoutCachedForward(LayoutWrapper* layoutWrapper,
    int32_t cacheCount, int32_t& cachedCount, int32_t curIndex, std::list<PredictLayoutItem>& predictList, bool show)
{
    float crossSize = GetLayoutCrossAxisSize(layoutWrapper);
    RefPtr<LayoutWrapper> wrapper;
    curIndex = GetItemPosition().rbegin()->first + 1;
    auto startPos = GetItemPosition().rbegin()->second.endPos + GetSpaceWidth();
    while (cachedCount < cacheCount && curIndex <= GetMaxListItemIndex()) {
        ListLayoutAlgorithm::PositionMap posMap;
        float mainLen = 0.0f;
        bool isGroup = false;
        int32_t cnt = 0;
        for (int32_t i = 0; i < lanes_ && curIndex + i <= GetMaxListItemIndex() && !isGroup; i++) {
            wrapper = GetChildByIndex(layoutWrapper, curIndex + i, !show);
            auto [needBreak, needPredict] = CheckACachedItem(wrapper, cnt, isGroup);
            if (needPredict) {
                predictList.emplace_back(PredictLayoutItem { curIndex + i, cachedCount, -1 });
            }
            if (needBreak) {
                break;
            }
            cnt++;
            mainLen = std::max(mainLen, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_));
            posMap[curIndex + i] = { wrapper->GetHostNode()->GetId(), startPos, startPos + mainLen, isGroup };
        }
        auto startIndex = curIndex;
        if (isGroup) {
            auto res = GetLayoutGroupCachedCount(layoutWrapper, wrapper, cacheCount - cachedCount, -1, curIndex, true);
            if (res.forwardCachedCount < res.forwardCacheMax && res.forwardCachedCount < cacheCount - cachedCount) {
                LayoutItem(wrapper, posMap.begin()->first, posMap.begin()->second, startIndex, crossSize);
                predictList.emplace_back(PredictLayoutItem { posMap.begin()->first, cachedCount, -1 });
                return res.forwardCachedCount > 0 ? curIndex : curIndex - 1;
            }
            cachedCount += std::max(res.forwardCacheMax, 1);
        } else if (cnt > 0) {
            cachedCount++;
        } else {
            break;
        }
        for (auto& pos : posMap) {
            pos.second.endPos = startPos + mainLen;
            LayoutCachedALine(layoutWrapper, pos, startIndex, crossSize);
        }
        if (isStackFromEnd_) {
            SetLaneIdx4Divider(cnt - 1);
        }
        startPos = startPos + mainLen + GetSpaceWidth();
        curIndex += cnt;
    }
    return curIndex - 1;
}

int32_t ListLanesLayoutAlgorithm::LayoutCachedBackward(LayoutWrapper* layoutWrapper,
    int32_t cacheCount, int32_t& cachedCount, int32_t curIndex, std::list<PredictLayoutItem>& predictList, bool show)
{
    float crossSize = GetLayoutCrossAxisSize(layoutWrapper);
    RefPtr<LayoutWrapper> wrapper;
    curIndex = GetItemPosition().begin()->first - 1;
    auto endPos = GetItemPosition().begin()->second.startPos - GetSpaceWidth();
    while (cachedCount < cacheCount && curIndex >= 0) {
        ListLayoutAlgorithm::PositionMap posMap;
        float mainLen = 0.0f;
        bool isGroup = false;
        int32_t cnt = 0;
        for (int32_t i = 0; i < lanes_ && curIndex - i >= 0; i++) {
            auto idx = curIndex - i;
            wrapper = GetChildByIndex(layoutWrapper, idx, !show);
            auto [needBreak, needPredict] = CheckACachedItem(wrapper, cnt, isGroup);
            if (needPredict) {
                predictList.emplace_back(PredictLayoutItem { idx, -1, cachedCount });
            }
            if (needBreak) {
                break;
            }
            cnt++;
            mainLen = std::max(mainLen, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_));
            posMap[idx] = { wrapper->GetHostNode()->GetId(), endPos - mainLen, endPos, isGroup };
            if (CheckCurRowMeasureFinished(layoutWrapper, idx, isGroup)) {
                break;
            }
        }
        auto startIndex = GetLanesFloor(layoutWrapper, curIndex);
        if (isGroup) {
            auto res = GetLayoutGroupCachedCount(layoutWrapper, wrapper, -1, cacheCount - cachedCount, curIndex, true);
            if (res.backwardCachedCount < res.backwardCacheMax && res.backwardCachedCount < cacheCount - cachedCount) {
                LayoutItem(wrapper, posMap.begin()->first, posMap.begin()->second, startIndex, crossSize);
                predictList.emplace_back(PredictLayoutItem { posMap.begin()->first, -1, cachedCount });
                return res.backwardCachedCount > 0 ? curIndex : curIndex + 1;
            }
            cachedCount += std::max(res.backwardCacheMax, 1);
        } else if (cnt > 0) {
            cachedCount++;
        } else {
            break;
        }
        for (auto& pos: posMap) {
            pos.second.startPos = endPos - mainLen;
            LayoutCachedALine(layoutWrapper, pos, startIndex, crossSize);
        }
        if (!isStackFromEnd_) {
            SetLaneIdx4Divider(curIndex - startIndex + 1 - cnt);
        }
        endPos = endPos - mainLen - GetSpaceWidth();
        curIndex -= cnt;
    }
    return curIndex + 1;
}
} // namespace OHOS::Ace::NG
