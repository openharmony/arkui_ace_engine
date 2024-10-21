/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_layout_info.h"

constexpr float HALF = 0.5f;

namespace OHOS::Ace::NG {
int32_t WaterFlowLayoutInfo::GetCrossIndex(int32_t itemIndex) const
{
    if (static_cast<size_t>(itemIndex) < itemInfos_.size()) {
        return itemInfos_[itemIndex].crossIdx;
    }
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
    if (childrenCount_ == 0) {
        return;
    }
    if (!itemInfos_.empty()) {
        // don't use in new segmented layout
        return;
    }
    auto mainHeight = GetMaxMainHeight();
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
    if (!endPosArray_.empty()) {
        const auto& margin = margins_.back();
        return endPosArray_.back().first + (axis_ == Axis::VERTICAL ? margin.bottom : margin.right).value_or(0.0f);
    }
    if (items_.empty()) {
        return 0.0f;
    }
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
    if (static_cast<size_t>(itemIndex) < itemInfos_.size() && itemInfos_[itemIndex].crossIdx == crossIndex) {
        return itemInfos_[itemIndex].mainOffset + itemInfos_[itemIndex].mainSize;
    }
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
    if (static_cast<size_t>(itemIndex) < itemInfos_.size() && itemInfos_[itemIndex].crossIdx == crossIndex) {
        return itemInfos_[itemIndex].mainOffset;
    }
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

OverScrollOffset WaterFlowLayoutInfo::GetOverScrolledDelta(float delta) const
{
    OverScrollOffset offset = { 0, 0 };
    if (startIndex_ == 0) {
        auto startPos = currentOffset_;
        auto newStartPos = startPos + delta;
        if (startPos > 0 && newStartPos > 0) {
            offset.start = delta;
        }
        if (startPos > 0 && newStartPos <= 0) {
            offset.start = -startPos;
        }
        if (startPos <= 0 && newStartPos > 0) {
            offset.start = newStartPos;
        }
    }
    if (itemEnd_) {
        auto endPos = currentOffset_ + maxHeight_;
        if (GreatNotEqual(lastMainSize_, currentOffset_ + maxHeight_)) {
            endPos = currentOffset_ + lastMainSize_;
        }
        auto newEndPos = endPos + delta;
        if (endPos < lastMainSize_ && newEndPos < lastMainSize_) {
            offset.end = delta;
        }
        if (endPos < lastMainSize_ && newEndPos >= lastMainSize_) {
            offset.end = lastMainSize_ - endPos;
        }
        if (endPos >= lastMainSize_ && newEndPos < lastMainSize_) {
            offset.end = newEndPos - lastMainSize_;
        }
    }
    return offset;
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
    items_ = { ItemMap() };
    itemInfos_.clear();
    endPosArray_.clear();
    segmentTails_.clear();
    margins_.clear();
    segmentStartPos_ = { 0.0f };
    segmentCache_.clear();
}

void WaterFlowLayoutInfo::ResetFooter()
{
    footerIndex_ = -1;
}

void WaterFlowLayoutInfo::Reset(int32_t resetFrom)
{
    TAG_LOGI(AceLogTag::ACE_WATERFLOW, "reset. updateIdx:%{public}d,endIndex:%{public}d", resetFrom, endIndex_);
    maxHeight_ = 0.0f;
    startIndex_ = resetFrom;
    ClearCacheAfterIndex(resetFrom - 1);
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
    size_t segment = static_cast<size_t>(GetSegment(currentIndex));
    for (auto& crossItems : items_[segment]) {
        if (crossItems.second.empty()) {
            continue;
        }
        auto clearFrom = std::find_if(crossItems.second.begin(), crossItems.second.end(),
            [currentIndex](const std::pair<const int, std::pair<float, float>>& crossItem) {
                return crossItem.first > currentIndex;
            });
        crossItems.second.erase(clearFrom, crossItems.second.end());
    }
    for (size_t i = segment + 1; i < items_.size(); ++i) {
        for (auto& col : items_[i]) {
            col.second.clear();
        }
    }

    if (static_cast<size_t>(currentIndex + 1) < itemInfos_.size()) {
        itemInfos_.resize(currentIndex + 1);
    }

    auto it = std::upper_bound(endPosArray_.begin(), endPosArray_.end(), currentIndex,
        [](int32_t index, const std::pair<float, int32_t>& pos) { return index < pos.second; });
    endPosArray_.erase(it, endPosArray_.end());

    if (segment + 1 < segmentStartPos_.size()) {
        segmentStartPos_.resize(segment + 1);
        if (currentIndex == segmentTails_[segment]) {
            SetNextSegmentStartPos(currentIndex);
        }
    }
}

bool WaterFlowLayoutInfo::ReachStart(float prevOffset, bool firstLayout) const
{
    auto scrollUpToReachTop = (LessNotEqual(prevOffset, 0.0) || firstLayout) && GreatOrEqual(currentOffset_, 0.0);
    auto scrollDownToReachTop = GreatNotEqual(prevOffset, 0.0) && LessOrEqual(currentOffset_, 0.0);
    return scrollUpToReachTop || scrollDownToReachTop;
}

bool WaterFlowLayoutInfo::ReachEnd(float prevOffset, bool firstLayout) const
{
    if (!offsetEnd_) {
        return false;
    }
    float minOffset = lastMainSize_ - maxHeight_;
    auto scrollDownToReachEnd =
        (GreatNotEqual(prevOffset, minOffset) || firstLayout) && LessOrEqual(currentOffset_, minOffset);
    auto scrollUpToReachEnd = LessNotEqual(prevOffset, minOffset) && GreatOrEqual(currentOffset_, minOffset);
    return scrollDownToReachEnd || scrollUpToReachEnd;
}

int32_t WaterFlowLayoutInfo::FastSolveStartIndex() const
{
    if (NearZero(currentOffset_ + TopMargin()) && !endPosArray_.empty() &&
        NearZero(endPosArray_[0].first - TopMargin())) {
        return endPosArray_[0].second;
    }
    auto it = std::upper_bound(endPosArray_.begin(), endPosArray_.end(), -currentOffset_,
        [](float value, const std::pair<float, int32_t>& info) { return LessNotEqual(value, info.first); });
    if (it == endPosArray_.end()) {
        return std::max(static_cast<int32_t>(itemInfos_.size()) - 1, 0);
    }
    return it->second;
}

int32_t WaterFlowLayoutInfo::FastSolveEndIndex(float mainSize) const
{
    if (itemInfos_.empty()) {
        return -1;
    }

    const float endBound = mainSize - currentOffset_;
    auto it = std::lower_bound(itemInfos_.begin(), itemInfos_.end(), endBound,
        [](const ItemInfo& info, float value) { return LessNotEqual(info.mainOffset, value); });

    // The last flowItem with the height of 0 should be regarded as endIndex_ when reach end.
    while (it != itemInfos_.end() && NearZero(it->mainSize) && NearEqual(it->mainOffset, endBound)) {
        ++it;
    }
    int32_t res = std::distance(itemInfos_.begin(), it) - 1;
    return std::max(res, 0);
}

void WaterFlowLayoutInfo::RecordItem(int32_t idx, const FlowItemPosition& pos, float height)
{
    if (itemInfos_.size() != static_cast<size_t>(idx)) {
        return;
    }
    items_[GetSegment(idx)][pos.crossIndex][idx] = { pos.startMainPos, height };
    itemInfos_.emplace_back(pos.crossIndex, pos.startMainPos, height);
    if (endPosArray_.empty() || LessNotEqual(endPosArray_.back().first, pos.startMainPos + height)) {
        endPosArray_.emplace_back(pos.startMainPos + height, idx);
    }

    if (idx == segmentTails_[GetSegment(idx)]) {
        SetNextSegmentStartPos(idx);
    }
}

void WaterFlowLayoutInfo::SetNextSegmentStartPos(int32_t itemIdx)
{
    auto segment = static_cast<size_t>(GetSegment(itemIdx));
    if (segmentStartPos_.size() > segment + 1) {
        return;
    }
    if (segmentStartPos_.size() <= segment || margins_.size() <= segment + 1) {
        return;
    }

    float nextStartPos = endPosArray_.empty() ? segmentStartPos_[segment] : endPosArray_.back().first;
    while (segment < segmentTails_.size() - 1 && itemIdx == segmentTails_[segment]) {
        // use while loop to skip empty segments
        if (axis_ == Axis::VERTICAL) {
            nextStartPos += margins_[segment].bottom.value_or(0.0f) + margins_[segment + 1].top.value_or(0.0f);
        } else {
            nextStartPos += margins_[segment].right.value_or(0.0f) + margins_[segment + 1].left.value_or(0.0f);
        }
        segmentStartPos_.push_back(nextStartPos);
        ++segment;
    }
}

void WaterFlowLayoutInfo::Sync(float mainSize, bool overScroll)
{
    // adjust offset when it can't overScroll at top
    if (!overScroll) {
        currentOffset_ = std::min(currentOffset_, 0.0f);
    }
    endIndex_ = FastSolveEndIndex(mainSize);

    maxHeight_ = GetMaxMainHeight();

    itemStart_ = GreatOrEqual(currentOffset_, 0.0f);
    itemEnd_ = endIndex_ >= 0 && endIndex_ == childrenCount_ - 1;
    offsetEnd_ = itemEnd_ && GreatOrEqual(mainSize - currentOffset_, maxHeight_);
    // adjust offset when it can't overScroll at bottom
    if (offsetEnd_ && !overScroll) {
        currentOffset_ = std::min(-maxHeight_ + mainSize, 0.0f);
    }

    startIndex_ = FastSolveStartIndex();
}

void WaterFlowLayoutInfo::InitSegments(const std::vector<WaterFlowSections::Section>& sections, int32_t start)
{
    size_t n = sections.size();
    if (n == 0) {
        Reset();
        currentOffset_ = 0.0f;
        return;
    }
    segmentTails_ = { sections[0].itemsCount - 1 };
    for (size_t i = 1; i < n; ++i) {
        segmentTails_.push_back(segmentTails_[i - 1] + sections[i].itemsCount);
    }

    segmentCache_.clear();
    if (static_cast<size_t>(start) < segmentStartPos_.size()) {
        segmentStartPos_.resize(start);
        // startPos of next segment can only be determined after margins_ is reinitialized.
    }

    int32_t lastValidItem = (start > 0) ? segmentTails_[start - 1] : -1;
    if (static_cast<size_t>(lastValidItem + 1) < itemInfos_.size()) {
        itemInfos_.resize(lastValidItem + 1);
    }

    auto it = std::upper_bound(endPosArray_.begin(), endPosArray_.end(), lastValidItem,
        [](int32_t index, const std::pair<float, int32_t>& pos) { return index < pos.second; });
    endPosArray_.erase(it, endPosArray_.end());
    items_.resize(n);
    for (size_t i = static_cast<size_t>(start); i < n; ++i) {
        items_[i].clear();
        for (int32_t j = 0; j < sections[i].crossCount; ++j) {
            items_[i][j] = {};
        }
    }

    margins_.clear(); // to be initialized during layout
}

void WaterFlowLayoutInfo::PrepareSegmentStartPos()
{
    if (segmentStartPos_.size() <= 1) {
        ResetSegmentStartPos();
    }
    int32_t lastItem = static_cast<int32_t>(itemInfos_.size()) - 1;
    if (GetSegment(lastItem) >= static_cast<int32_t>(segmentTails_.size())) {
        TAG_LOGW(AceLogTag::ACE_WATERFLOW, "Section data not initialized before layout");
        return;
    }
    if (segmentTails_[GetSegment(lastItem)] == lastItem) {
        SetNextSegmentStartPos(static_cast<int32_t>(itemInfos_.size()) - 1);
    }
}

void WaterFlowLayoutInfo::ResetSegmentStartPos()
{
    if (margins_.empty()) {
        segmentStartPos_ = { 0.0f };
    } else {
        segmentStartPos_ = { (axis_ == Axis::VERTICAL ? margins_[0].top : margins_[0].left).value_or(0.0f) };
    }
}

void WaterFlowLayoutInfo::PrintWaterFlowItems() const
{
    for (const auto& [key1, map1] : items_[0]) {
        std::stringstream ss;
        ss << key1 << ": {";
        for (const auto& [key2, pair] : map1) {
            ss << key2 << ": (" << pair.first << ", " << pair.second << ")";
            if (&pair != &map1.rbegin()->second) {
                ss << ", ";
            }
        }
        ss << "}";
        LOGI("%{public}s", ss.str().c_str());
    }
}

float WaterFlowLayoutInfo::JumpToTargetAlign(const std::pair<float, float>& item) const
{
    float targetPosition = 0.0f;
    ScrollAlign align = align_;
    switch (align) {
        case ScrollAlign::START:
            targetPosition = -item.first;
            break;
        case ScrollAlign::END:
            targetPosition = lastMainSize_ - (item.first + item.second);
            break;
        case ScrollAlign::AUTO:
            if (currentOffset_ + item.first < 0) {
                targetPosition = -item.first;
            } else if (currentOffset_ + item.first + item.second > lastMainSize_) {
                targetPosition = lastMainSize_ - (item.first + item.second);
            } else {
                targetPosition = currentOffset_;
            }
            break;
        case ScrollAlign::CENTER:
            targetPosition = -item.first + (lastMainSize_ - item.second) * HALF;
            break;
        default:
            break;
    }
    return targetPosition;
}

void WaterFlowLayoutInfo::JumpTo(const std::pair<float, float>& item)
{
    currentOffset_ = JumpToTargetAlign(item);
    if (extraOffset_.has_value()) {
        currentOffset_ += extraOffset_.value();
        extraOffset_.reset();
    }
    align_ = ScrollAlign::START;
    jumpIndex_ = EMPTY_JUMP_INDEX;
}

void WaterFlowLayoutInfo::UpdateOffset(float delta)
{
    currentOffset_ += delta;
}

float WaterFlowLayoutInfo::CalcTargetPosition(int32_t idx, int32_t crossIdx) const
{
    return -JumpToTargetAlign(items_[GetSegment(idx)].at(crossIdx).at(idx));
}

bool WaterFlowLayoutInfo::OutOfBounds() const
{
    bool outOfStart = itemStart_ && Positive(currentOffset_);
    bool outOfEnd = offsetEnd_ && LessNotEqual(currentOffset_ + maxHeight_, lastMainSize_);
    // not outOfEnd when content size < mainSize but currentOffset_ == 0
    if (LessNotEqual(maxHeight_, lastMainSize_)) {
        outOfEnd &= Negative(currentOffset_);
    }
    return outOfStart || outOfEnd;
}

float WaterFlowLayoutInfo::CalcOverScroll(float mainSize, float delta) const
{
    float res = 0;
    if (itemStart_) {
        res = currentOffset_ + delta;
    }
    if (offsetEnd_) {
        res = mainSize - (GetMaxMainHeight() + currentOffset_ - delta);
    }
    return res;
}

float WaterFlowLayoutInfo::EstimateContentHeight() const
{
    auto childCount = 0;
    if (!itemInfos_.empty()) {
        // in segmented layout
        childCount = static_cast<int32_t>(itemInfos_.size());
    } else if (maxHeight_) {
        // in original layout, already reach end.
        return maxHeight_;
    } else {
        // in original layout
        for (const auto& item : items_[0]) {
            childCount += static_cast<int32_t>(item.second.size());
        }
    }
    if (childCount == 0) {
        return 0;
    }
    auto estimateHeight = GetMaxMainHeight() / childCount * childrenCount_;
    return estimateHeight;
}

int32_t WaterFlowLayoutInfo::GetLastItem() const
{
    int32_t res = -1;
    if (items_.empty()) {
        return res;
    }
    for (auto&& map : items_[0]) {
        if (map.second.empty()) {
            continue;
        }
        res = std::max(res, map.second.rbegin()->first);
    }
    return res;
}
} // namespace OHOS::Ace::NG
