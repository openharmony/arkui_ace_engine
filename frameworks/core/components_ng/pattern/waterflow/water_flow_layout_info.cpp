/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/waterflow/water_flow_layout_info.h"

#include <algorithm>

namespace OHOS::Ace::NG {
int32_t WaterFlowLayoutInfo::GetCrossIndex(int32_t itemIndex) const
{
    for (const auto& crossItems : items_[GetSegment(itemIndex)]) {
        auto iter = crossItems.second.find(itemIndex);
        if (iter != crossItems.second.end()) {
            return crossItems.first;
        }
    }
    return -1;
}

void WaterFlowLayoutInfo::UpdateStartIndex()
{
    auto nextPosition = GetCrossIndexForNextItem(GetSegment(endIndex_));
    auto mainHeight = GetMainHeight(nextPosition.crossIndex, nextPosition.lastItemIndex);
    // need more items for currentOffset_
    if (LessOrEqual(currentOffset_ + mainHeight, 0.0f)) {
        return;
    }

    int32_t tempStartIndex = -1;
    for (const auto& crossItems : items_[GetSegment(tempStartIndex)]) {
        for (const auto& iter : crossItems.second) {
            if (GreatNotEqual(iter.second.first + iter.second.second + currentOffset_, 0.0f)) {
                tempStartIndex = tempStartIndex != -1 ? std::min(tempStartIndex, iter.first) : iter.first;
                break;
            }
            // FlowItem that have not been loaded at the beginning of each cross need to be selected as startIndex_ for
            // the ClearCache later.
            if (NearZero(iter.second.first + iter.second.second) && NearZero(currentOffset_)) {
                tempStartIndex = tempStartIndex != -1 ? std::min(tempStartIndex, iter.first) : iter.first;
                break;
            }
        }
    }
    startIndex_ = tempStartIndex == -1 ? 0 : tempStartIndex;
}

int32_t WaterFlowLayoutInfo::GetEndIndexByOffset(float offset) const
{
    int32_t endIndex = 0;
    bool found = false;
    for (const auto& crossItems : items_[GetSegment(endIndex)]) {
        for (const auto& iter : crossItems.second) {
            if (GreatNotEqual(iter.second.first + iter.second.second + offset, 0)) {
                endIndex = std::max(endIndex, iter.first);
                found = true;
                break;
            }
        }
    }
    return found ? endIndex : -1;
}

float WaterFlowLayoutInfo::GetMaxMainHeight() const
{
    float result = 0.0f;
    for (const auto& crossItems : *items_.rbegin()) {
        if (crossItems.second.empty()) {
            continue;
        }
        auto lastItem = crossItems.second.rbegin();
        auto crossMainHeight = lastItem->second.first + lastItem->second.second;
        if (NearEqual(result, 0.0f)) {
            result = crossMainHeight;
        }
        if (LessNotEqual(result, crossMainHeight)) {
            result = crossMainHeight;
        }
    }
    return result;
}

float WaterFlowLayoutInfo::GetContentHeight() const
{
    return NearZero(maxHeight_) ? GetMaxMainHeight() : maxHeight_;
}

float WaterFlowLayoutInfo::GetMainHeight(int32_t crossIndex, int32_t itemIndex) const
{
    auto seg = GetSegment(itemIndex);
    float result = segmentStartPos_[seg];

    auto cross = items_[seg].find(crossIndex);
    if (cross == items_[seg].end()) {
        return result;
    }
    auto item = cross->second.find(itemIndex);
    if (item == cross->second.end()) {
        return result;
    }
    result = item->second.first + item->second.second;
    return result;
}

float WaterFlowLayoutInfo::GetStartMainPos(int32_t crossIndex, int32_t itemIndex) const
{
    float result = 0.0f;
    auto cross = items_[GetSegment(itemIndex)].find(crossIndex);
    if (cross == items_[GetSegment(itemIndex)].end()) {
        return result;
    }
    auto item = cross->second.find(itemIndex);
    if (item == cross->second.end()) {
        return result;
    }
    result = item->second.first;
    return result;
}

bool WaterFlowLayoutInfo::IsAllCrossReachEnd(float mainSize) const
{
    bool result = true;
    for (const auto& crossItems : *items_.rbegin()) {
        if (crossItems.second.empty()) {
            result = false;
            break;
        }
        auto lastItem = crossItems.second.rbegin();
        auto lastOffset = lastItem->second.first + lastItem->second.second;
        if (LessNotEqual(lastOffset + currentOffset_, mainSize)) {
            result = false;
            break;
        }
    }
    return result;
}

FlowItemIndex WaterFlowLayoutInfo::GetCrossIndexForNextItem(int32_t segmentIdx) const
{
    FlowItemIndex position = { 0, -1 };
    auto minHeight = -1.0f;
    auto crossSize = static_cast<int32_t>(items_[segmentIdx].size());
    for (int32_t i = 0; i < crossSize; ++i) {
        const auto& crossItems = items_[segmentIdx].at(i);
        if (crossItems.empty()) {
            position.crossIndex = i;
            position.lastItemIndex = -1;
            break;
        }
        auto lastItem = crossItems.rbegin();
        auto lastOffset = lastItem->second.first + lastItem->second.second;
        if (NearEqual(minHeight, -1.0f)) {
            minHeight = lastOffset;
            position.crossIndex = i;
            position.lastItemIndex = lastItem->first;
        }
        if (LessNotEqual(lastOffset, minHeight)) {
            position.crossIndex = i;
            position.lastItemIndex = lastItem->first;
            minHeight = lastOffset;
            // first item height in this cross is 0
            if (NearZero(minHeight)) {
                break;
            }
        }
    }

    return position;
}

void WaterFlowLayoutInfo::Reset()
{
    itemEnd_ = false;
    itemStart_ = false;
    offsetEnd_ = false;
    maxHeight_ = 0.0f;

    jumpIndex_ = EMPTY_JUMP_INDEX;

    startIndex_ = 0;
    endIndex_ = -1;
    targetIndex_.reset();
    for (auto& map : items_) {
        map.clear();
    }
}

void WaterFlowLayoutInfo::Reset(int32_t resetFrom)
{
    if (resetFrom > endIndex_) {
        return;
    }
    Reset();
}

int32_t WaterFlowLayoutInfo::GetCrossCount() const
{
    return static_cast<int32_t>(items_[0].size());
}

int32_t WaterFlowLayoutInfo::GetMainCount() const
{
    int32_t maxMainCount = 0;
    for (const auto& crossItems : items_[0]) {
        if (crossItems.second.empty()) {
            continue;
        }
        auto mainCount = static_cast<int32_t>(std::count_if(crossItems.second.begin(), crossItems.second.end(),
            [start = startIndex_, end = endIndex_](const std::pair<const int, std::pair<float, float>>& crossItem) {
                return crossItem.first >= start && crossItem.first <= end;
            }));
        maxMainCount = std::max(maxMainCount, mainCount);
    }
    return maxMainCount;
}

void WaterFlowLayoutInfo::ClearCacheAfterIndex(int32_t currentIndex)
{
    for (auto& crossItems : items_[GetSegment(currentIndex)]) {
        if (crossItems.second.empty()) {
            continue;
        }
        auto clearFrom = std::find_if(crossItems.second.begin(), crossItems.second.end(),
            [currentIndex](const std::pair<const int, std::pair<float, float>>& crossItem) {
                return crossItem.first > currentIndex;
            });
        crossItems.second.erase(clearFrom, crossItems.second.end());
    }
    for (int32_t i = GetSegment(currentIndex) + 1; i < items_.size(); ++i) {
        items_[i].clear();
    }
}

bool WaterFlowLayoutInfo::ReachStart(float prevOffset, bool firstLayout) const
{
    auto scrollUpToReachTop = (LessNotEqual(prevOffset, 0.0) || firstLayout) && GreatOrEqual(currentOffset_, 0.0);
    auto scrollDownToReachTop = GreatNotEqual(prevOffset, 0.0) && LessOrEqual(currentOffset_, 0.0);
    return scrollUpToReachTop || scrollDownToReachTop;
}

bool WaterFlowLayoutInfo::ReachEnd(float prevOffset) const
{
    float minOffset = lastMainSize_ - maxHeight_;
    auto scrollDownToReachEnd = GreatNotEqual(prevOffset, minOffset) && LessOrEqual(currentOffset_, minOffset);
    auto scrollUpToReachEnd = LessNotEqual(prevOffset, minOffset) && GreatOrEqual(currentOffset_, minOffset);
    return scrollDownToReachEnd || scrollUpToReachEnd;
}

int32_t WaterFlowLayoutInfo::GetSegment(int32_t itemIdx) const
{
    if (segmentTails_.empty()) {
        return 0;
    }
    auto cache = segmentCache_.find(itemIdx);
    if (cache != segmentCache_.end()) {
        return cache->second;
    }

    auto it = std::lower_bound(segmentTails_.begin(), segmentTails_.end(), itemIdx);
    if (it == segmentTails_.end()) {
        return segmentTails_.size() - 1;
    }
    int32_t idx = it - segmentTails_.begin();
    segmentCache_[itemIdx] = idx;
    return idx;
}

int32_t WaterFlowLayoutInfo::FastSolveStartIndex() const
{
    auto it = std::upper_bound(endPosArray_.begin(), endPosArray_.end(), -currentOffset_,
        [](float value, const std::pair<float, int32_t>& info) { return value < info.first; });
    if (it == endPosArray_.end()) {
        return 0;
    }
    return it->second;
}

int32_t WaterFlowLayoutInfo::FastSolveEndIndex(float mainSize) const
{
    auto it = std::lower_bound(itemInfos_.begin(), itemInfos_.end(), mainSize - currentOffset_,
        [](const std::pair<int32_t, ItemInfo>& info, float value) { return info.second.first < value; });

    if (it == itemInfos_.end()) {
        return childrenCount_ - 1;
    }
    return it->first - 1;
}

void WaterFlowLayoutInfo::AddItemToCache(int32_t idx, float startPos, float height)
{
    itemInfos_[idx] = { startPos, height };
    if (endPosArray_.empty() || LessNotEqual(endPosArray_.back().first, startPos + height)) {
        endPosArray_.emplace_back(startPos + height, idx);
    }
}

void WaterFlowLayoutInfo::SetNextSegmentStartPos(
    const std::vector<PaddingPropertyF>& margins, int32_t itemIdx)
{
    int32_t segment = GetSegment(itemIdx);
    if (segmentStartPos_.size() > segment + 1) {
        return;
    }

    float nextStartPos = endPosArray_.back().first;
    while (segment < segmentTails_.size() - 1 && itemIdx == segmentTails_[segment]) {
        // use while loop to skip empty segments
        nextStartPos += margins[segment].bottom.value_or(0.0f) + margins[segment + 1].top.value_or(0.0f);
        segmentStartPos_.push_back(nextStartPos);
        ++segment;
    }
}
} // namespace OHOS::Ace::NG