/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/list/list_height_offset_calculator.h"
#ifdef ACE_STATIC
#include "core/components_ng/syntax/arkoala_lazy_node.h"
#endif

namespace OHOS::Ace::NG {
ListHeightOffsetCalculator::ListHeightOffsetCalculator(const ListLayoutAlgorithm::PositionMap& itemPosition,
    float space, int32_t lanes, Axis axis, int32_t itemStartIndex)
    : axis_(axis), spaceWidth_(space), lanes_(lanes), itemPosition_(itemPosition), itemStartIndex_(itemStartIndex)
{
    if (!itemPosition.empty()) {
        targetPos_ = { itemPosition.begin()->second.startPos, itemPosition.begin()->second.endPos };
        startIndex_ = itemPosition.begin()->first;
        endIndex_ = itemPosition.rbegin()->first;
        float itemsSize = itemPosition.rbegin()->second.endPos - itemPosition.begin()->second.startPos + space;
        for (const auto& pos : itemPosition) {
            if (pos.second.groupInfo && pos.second.groupInfo.value().averageHeight > 0) {
                groupedItemHeight_ = pos.second.groupInfo.value().averageHeight;
                groupHeaderHeight_ = pos.second.groupInfo.value().headerSize;
                groupFooterHeight_ = pos.second.groupInfo.value().footerSize;
                groupSpaceWidth_ = pos.second.groupInfo.value().spaceWidth;
                hasGroup_ = true;
                lanes = 1;
                break;
            }
        }
        estimateItemHeight_ = itemsSize / GetLines(lanes, itemPosition.size()) - space;
    }
}

void ListHeightOffsetCalculator::CalculateListItemGroup(RefPtr<ListItemGroupPattern> listItemGroupPatten)
{
    if (currentIndex_ > 0) {
        estimateHeight_ += spaceWidth_;
    }
    if (currentIndex_ == startIndex_) {
        estimateOffset_ = listItemGroupPatten->GetEstimateOffset(estimateHeight_, targetPos_,
            groupHeaderHeight_, groupFooterHeight_);
    }
    if (currLane_ > 0) {
        if (syncPosMap_ && posMap_) {
            ListPositionInfo info = { estimateHeight_, currRowHeight_, false };
            posMap_->UpdatePosRange(currentIndex_ - currLane_, currentIndex_, info, spaceWidth_, lanes_);
        }
        estimateHeight_ += currRowHeight_;
        currLane_ = 0;
        currRowHeight_ = 0.0f;
    }
    float height = listItemGroupPatten->GetEstimateHeight(groupedItemHeight_,
        groupHeaderHeight_, groupFooterHeight_, groupSpaceWidth_);
    if (syncPosMap_ && posMap_) {
        posMap_->UpdatePos(currentIndex_, ListPositionInfo{ estimateHeight_, height, true });
    }
    estimateHeight_ += height;
    currentIndex_++;
}

void ListHeightOffsetCalculator::CalculateFrameNode(RefPtr<FrameNode> frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto listItemGroupPatten = frameNode->GetPattern<ListItemGroupPattern>();
    if (listItemGroupPatten) {
        CalculateListItemGroup(listItemGroupPatten);
        return;
    }
    auto listItemPatten = frameNode->GetPattern<ListItemPattern>();
    if (currentIndex_ > 0 && currLane_ == 0) {
        estimateHeight_ += spaceWidth_;
    }
    if (currentIndex_ == startIndex_) {
        estimateOffset_ = estimateHeight_ - targetPos_.first;
    }
    float height = 0.0f;
    if (listItemPatten) {
        height = listItemPatten->GetEstimateHeight(GetAverageItemHeight(), axis_);
    } else {
        height = GetMainAxisSize(frameNode->GetGeometryNode()->GetMarginFrameSize(), axis_);
    }
    currRowHeight_ = std::max(currRowHeight_, height);
    currLane_++;
    if (currLane_ == lanes_ || (posMap_ &&
        posMap_->GetPositionInfo(currentIndex_).mainPos != posMap_->GetPositionInfo(currentIndex_ + 1).mainPos)) {
        if (syncPosMap_ && posMap_) {
            ListPositionInfo info = { estimateHeight_, currRowHeight_, false };
            posMap_->UpdatePosRange(currentIndex_ - (lanes_ - 1), currentIndex_ + 1, info, spaceWidth_, lanes_);
        }
        estimateHeight_ += currRowHeight_;
        currLane_ = 0;
        currRowHeight_ = 0.0f;
    }
    currentIndex_++;
    if (listItemPatten && listItemPatten->GetLayouted()) {
        totalItemHeight_ += height;
        totalItemCount_++;
    }
}

void ListHeightOffsetCalculator::CalculatePosMapNode()
{
    if (currentIndex_ > 0 && currLane_ == 0) {
        estimateHeight_ += spaceWidth_;
    }
    if (currentIndex_ == startIndex_) {
        estimateOffset_ = estimateHeight_ - targetPos_.first;
    }
    ListPositionInfo posInfo = posMap_ ? posMap_->GetPositionInfo(currentIndex_) : ListPositionInfo{ -1.0f, -1.0f };
    float height = posInfo.mainSize < 0 ? GetAverageItemHeight() : posInfo.mainSize;
    currRowHeight_ = std::max(currRowHeight_, height);
    currLane_++;
    if (currLane_ == lanes_ || posInfo.isGroup) {
        estimateHeight_ += currRowHeight_;
        currLane_ = 0;
        currRowHeight_ = 0.0f;
    }
    currentIndex_++;
    if (posInfo.mainSize >= 0) {
        totalItemHeight_ += height;
        totalItemCount_++;
    }
}

int32_t ListHeightOffsetCalculator::GetPosMapStartIndex()
{
    return posMap_ ? posMap_->GetStartIndexAndPos().first : -1;
}

int32_t ListHeightOffsetCalculator::GetPosMapEndIndex()
{
    return posMap_ ? posMap_->GetEndIndexAndPos().first : -1;
}

bool ListHeightOffsetCalculator::CalculateRangeWithPosMap(int start, int end)
{
    auto prevHeight = estimateHeight_;
    ListPositionInfo posMapStart = posMap_ ? posMap_->GetPositionInfo(start) : ListPositionInfo { -1.0f, -1.0f };
    ListPositionInfo posMapEnd = posMap_ ? posMap_->GetPositionInfo(end) : ListPositionInfo { -1.0f, -1.0f };
    if (posMapStart.mainPos < 0.0f || posMapEnd.mainPos < 0.0f || posMapStart.mainSize < 0.0f ||
        posMapEnd.mainSize < 0.0f || posMapStart.isGroup || posMapEnd.isGroup) {
        return false;
    }
    estimateHeight_ += posMapEnd.mainPos - posMapStart.mainPos + posMapEnd.mainSize + (start == 0 ? 0.0f : spaceWidth_);
    auto rowCount = posMapStart.isGroup ? (end - start + 1) : (end - start + 1) / lanes_;
    auto totalSpaceWidth = (start == 0 ? spaceWidth_ * (rowCount - 1) : spaceWidth_ * rowCount);
    totalItemHeight_ += posMapStart.isGroup ? (estimateHeight_ - prevHeight - totalSpaceWidth)
                                            : (estimateHeight_ - prevHeight - totalSpaceWidth) * lanes_;
    totalItemCount_ += end - start + 1;
    currentIndex_ = end + 1;
    return true;
}

void ListHeightOffsetCalculator::CalculateLazyForEachNodeWithPosMap(RefPtr<UINode> node)
{
    auto repeatV2 = AceType::DynamicCast<RepeatVirtualScroll2Node>(node);
    int32_t count = 0;
    if (repeatV2) {
        auto totalCount = repeatV2->GetTotalCount();
        count = (totalCount <= INT_MAX) ? static_cast<int32_t>(totalCount) : INT_MAX;
    } else {
        count = node->FrameCount();
    }
    if (count <= 0) {
        return;
    }
    int32_t lazyStartIndex = currentIndex_;
    int32_t lazyEndIndex = currentIndex_ + count;
    bool hasGroup = false;

    while (currentIndex_ < lazyEndIndex) {
        if (currentIndex_ < startIndex_) {
            int32_t jumpTarget = (startIndex_ - 1 < lazyEndIndex) ? startIndex_ - 1 : lazyEndIndex - 1;
            if (hasGroup_ || !CalculateRangeWithPosMap(currentIndex_, jumpTarget)) {
                CalculatePosMapNode();
            }
        } else if (currentIndex_ <= endIndex_) {
            if (!hasGroup_) {
                CalculatePosMapNode();
                continue;
            }
            auto child = node->GetFrameChildByIndex(currentIndex_ - lazyStartIndex, false);
            auto frameNode = AceType::DynamicCast<FrameNode>(child);
            if (!frameNode) {
                CalculatePosMapNode();
                continue;
            }
            float prevHeight = estimateHeight_;
            CalculateFrameNode(frameNode);
            if (frameNode->GetTag() == V2::LIST_ITEM_GROUP_ETS_TAG) {
                totalItemHeight_ += estimateHeight_ - prevHeight - (currentIndex_ > 1 ? spaceWidth_ : 0);
                totalItemCount_++;
                hasGroup = true;
            }
        } else if (currentIndex_ <= GetPosMapEndIndex()) {
            int32_t jumpTarget = (GetPosMapEndIndex() < lazyEndIndex) ? GetPosMapEndIndex() : lazyEndIndex - 1;
            if (hasGroup_ || !CalculateRangeWithPosMap(currentIndex_, jumpTarget)) {
                CalculatePosMapNode();
            }
        } else if (currentIndex_ < lazyEndIndex) {
            int32_t lanes = hasGroup ? 1 : lanes_;
            int32_t remain = lazyEndIndex - currentIndex_;
            estimateHeight_ += (GetAverageItemHeight() + spaceWidth_) * GetLines(lanes, remain);
            currentIndex_ = lazyEndIndex;
        }
    }
}

void ListHeightOffsetCalculator::CalculateUINode(RefPtr<UINode> node, bool checkStart)
{
    CHECK_NULL_VOID(node);
    const auto& children = node->GetChildren();
    int32_t index = 0;
    for (const auto& child : children) {
        index++;
        if (checkStart && index <= itemStartIndex_) {  // ignore start header if exist
            continue;
        }
        if (AceType::InstanceOf<FrameNode>(child)) {
            auto frameNode = AceType::DynamicCast<FrameNode>(child);
            CalculateFrameNode(frameNode);
        } else if (AceType::InstanceOf<LazyForEachNode>(child) || AceType::InstanceOf<RepeatVirtualScrollNode>(child) ||
                   AceType::InstanceOf<RepeatVirtualScroll2Node>(child)
#ifdef ACE_STATIC
                   || AceType::InstanceOf<ArkoalaLazyNode>(child)
#endif
        ) {
            auto posMapStart = GetPosMapStartIndex();
            if (posMapStart >= 0 && posMapStart <= currentIndex_ && !syncPosMap_) {
                CalculateLazyForEachNodeWithPosMap(child);
            } else {
                CalculateLazyForEachNode(child);
            }
        } else {
            CalculateUINode(child, false);
        }
    }
}

float ListHeightOffsetCalculator::GetLazyForEachIndexAverageHeight(RefPtr<UINode> node,
    int32_t startIndex, int32_t endIndex, bool &hasGroup)
{
    auto itor = itemPosition_.find(startIndex);
    float totalHeight = 0.0f;
    int32_t itemCount = 0;
    while (itor != itemPosition_.end() && itor->first <= endIndex) {
        if (!itor->second.isGroup) {
            totalHeight += itor->second.endPos - itor->second.startPos;
            itor++;
            itemCount++;
            continue;
        }
        hasGroup = true;
        if (itor->first == startIndex_ || itor->first == endIndex_) {
            auto child = node->GetFrameChildByIndex(itor->first - currentIndex_, false);
            auto frameNode = AceType::DynamicCast<FrameNode>(child);
            if (!frameNode) {
                itor++;
                continue;
            }
            auto group = frameNode->GetPattern<ListItemGroupPattern>();
            if (!group || !group->HasLayoutedItem()) {
                itor++;
                continue;
            }
            totalHeight += group->GetEstimateHeight(
                groupedItemHeight_, groupHeaderHeight_, groupFooterHeight_, groupSpaceWidth_);
        } else {
            totalHeight += itor->second.endPos - itor->second.startPos;
        }
        itor++;
        itemCount++;
    }
    if (itemCount == 0) {
        return estimateItemHeight_;
    }
    return totalHeight / itemCount;
}

float ListHeightOffsetCalculator::CalculateOffset(RefPtr<UINode> node, float averageHeight)
{
    auto itor = itemPosition_.begin();
    float skipHeight = 0.0f;
    while (itor != itemPosition_.end() && itor->second.isGroup) {
        auto child = node->GetFrameChildByIndex(itor->first - currentIndex_, false);
        auto frameNode = AceType::DynamicCast<FrameNode>(child);
        if (frameNode) {
            auto group = frameNode->GetPattern<ListItemGroupPattern>();
            if (group && group->HasLayoutedItem()) {
                std::pair<float, float> pos = { itor->second.startPos, itor->second.endPos };
                return group->GetEstimateOffset(estimateOffset_ + skipHeight, pos,
                    groupHeaderHeight_, groupFooterHeight_);
            }
        }
        skipHeight += averageHeight;
        itor++;
    }
    return estimateOffset_ - targetPos_.first;
}

void ListHeightOffsetCalculator::CalculateLazyForEachNode(RefPtr<UINode> node)
{
    auto repeat2 = AceType::DynamicCast<RepeatVirtualScroll2Node>(node);
    int32_t count = node->FrameCount();
    if (repeat2) {
        auto totalCount = repeat2->GetTotalCount();
        count = (totalCount <= INT_MAX) ? static_cast<int32_t>(totalCount) : INT_MAX;
    }
    if (count <= 0) {
        return;
    }
    if ((endIndex_ < currentIndex_) || (startIndex_ >= currentIndex_ + count)) {
        if (syncPosMap_ && posMap_ && (startIndex_ >= currentIndex_ + count)) {
            ListPositionInfo info = { estimateHeight_, estimateItemHeight_, false };
            posMap_->UpdatePosRange(currentIndex_, startIndex_, info, spaceWidth_, lanes_);
        }
        estimateHeight_ += (estimateItemHeight_ + spaceWidth_) * GetLines(lanes_, count);
        if (currentIndex_ > 0) {
            estimateHeight_ -= spaceWidth_;
        }
        currentIndex_ += count;
        return;
    }
    if (currentIndex_ > 0 && currLane_ == 0) {
        estimateHeight_ += spaceWidth_;
    }
    bool hasGroup = false;
    int32_t startIndex = std::max(currentIndex_, startIndex_);
    int32_t endIndex = std::min(currentIndex_ + count - 1, endIndex_);
    float averageHeight = GetLazyForEachIndexAverageHeight(node, startIndex, endIndex, hasGroup);
    int32_t lanes = hasGroup ? 1 : lanes_;
    if (syncPosMap_ && posMap_) {
        ListPositionInfo info = { estimateHeight_, averageHeight, hasGroup };
        posMap_->UpdatePosRange(currentIndex_, startIndex_, info, spaceWidth_, lanes);
    }
    if (startIndex == startIndex_) {
        int32_t curr = GetLines(lanes, startIndex_ - currentIndex_);
        estimateOffset_ = estimateHeight_ + (averageHeight + spaceWidth_) * curr;
        estimateOffset_ = CalculateOffset(node, averageHeight);
    }
    estimateHeight_ += (averageHeight + spaceWidth_) * GetLines(lanes, count) - spaceWidth_;
    currentIndex_ += count;
}

bool ListHeightOffsetCalculator::GetEstimateHeightAndOffset(RefPtr<UINode> node)
{
    CalculateUINode(node, true);
    if (currLane_ > 0) {
        estimateHeight_ += currRowHeight_;
        currLane_ = 0;
        currRowHeight_ = 0.0f;
    }
    return true;
}

void ListHeightOffsetCalculator::SetPosMap(const RefPtr<ListPositionMap>& posMap, bool syncPosMap)
{
    posMap_ = posMap;
    syncPosMap_ = syncPosMap;
}

float ListHeightOffsetCalculator::GetAverageItemHeight() const
{
    if (totalItemCount_ > 0) {
        return totalItemHeight_ / totalItemCount_;
    }
    return estimateItemHeight_;
}

int32_t ListHeightOffsetCalculator::GetLines(int32_t lanes, int32_t count)
{
    if (lanes > 1) {
        int32_t lines = count / lanes;
        if (count % lanes > 0) {
            lines += 1;
        }
        return lines;
    } else {
        return count;
    }
}
} // namespace OHOS::Ace::NG
