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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_HEIGHT_OFFSET_CALCULATOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_HEIGHT_OFFSET_CALCULATOR_H

#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_ITEM_HEIGHT = 64.f;
}
class ListHeightOffsetCalculator {
public:
    ListHeightOffsetCalculator(const ListLayoutAlgorithm::PositionMap& itemPosition, float space,
        int32_t lanes, Axis axis) : axis_(axis), spaceWidth_(space), lanes_(lanes), itemPosition_(itemPosition)
    {
        if (!itemPosition.empty()) {
            targetPos_ = { itemPosition.begin()->second.startPos, itemPosition.begin()->second.endPos };
            startIndex_ = itemPosition.begin()->first;
            endIndex_ = itemPosition.rbegin()->first;
            float itemsSize = itemPosition.rbegin()->second.endPos - itemPosition.begin()->second.startPos + space;
            estimateItemHeight_ = itemsSize / itemPosition.size() - space;
        }
    }

    void CalculateFrameNode(RefPtr<FrameNode> frameNode)
    {
        CHECK_NULL_VOID(frameNode);
        auto listItemPatten = frameNode->GetPattern<ListItemPattern>();
        if (listItemPatten) {
            if (currentIndex_ > 0 && currLane_ == 0) {
                estimateHeight_ += spaceWidth_;
            }
            if (currentIndex_ == startIndex_) {
                estimateOffset_ = estimateHeight_ - targetPos_.first;
            }
            float height = listItemPatten->GetEstimateHeight(GetAverageItemHeight(), axis_);
            currRowHeight_ = std::max(currRowHeight_, height);
            currLane_++;
            if (currLane_ == lanes_) {
                estimateHeight_ += currRowHeight_;
                currLane_ = 0;
                currRowHeight_ = 0.0f;
            }
            currentIndex_++;
            if (listItemPatten->GetLayouted()) {
                totalItemHeight_ += height;
                totalItemCount_++;
            }
            return;
        }
        auto listItemGroupPatten = frameNode->GetPattern<ListItemGroupPattern>();
        if (listItemGroupPatten) {
            if (currentIndex_ > 0) {
                estimateHeight_ += spaceWidth_;
            }
            if (currentIndex_ == startIndex_) {
                estimateOffset_ = listItemGroupPatten->GetEstimateOffset(estimateHeight_, targetPos_);
            }
            if (currLane_ > 0) {
                estimateHeight_ += currRowHeight_;
                currLane_ = 0;
                currRowHeight_ = 0.0f;
            }
            estimateHeight_ += listItemGroupPatten->GetEstimateHeight(groupedItemHeight_);
            currentIndex_++;
        }
    }

    void CalculateUINode(RefPtr<UINode> node)
    {
        CHECK_NULL_VOID(node);
        auto children = node->GetChildren();
        for (const auto& child : children) {
            if (AceType::InstanceOf<FrameNode>(child)) {
                auto frameNode = AceType::DynamicCast<FrameNode>(child);
                CalculateFrameNode(frameNode);
            } else if (AceType::InstanceOf<LazyForEachNode>(child)) {
                auto lazyForEach = AceType::DynamicCast<LazyForEachNode>(child);
                CalculateLazyForEachNode(lazyForEach);
            } else {
                CalculateUINode(child);
            }
        }
    }

    float GetLazyForEachIndexAverageHeight(RefPtr<LazyForEachNode> node,
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
                auto group = frameNode->GetPattern<ListItemGroupPattern>();
                if (!group->HasLayoutedItem()) {
                    itor++;
                    continue;
                }
                totalHeight += group->GetEstimateHeight(groupedItemHeight_);
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

    float CalculateOffset(RefPtr<LazyForEachNode> node, float averageHeight)
    {
        auto itor = itemPosition_.begin();
        float skipHeight = 0.0f;
        while (itor != itemPosition_.end() && itor->second.isGroup) {
            auto child = node->GetFrameChildByIndex(itor->first - currentIndex_, false);
            auto frameNode = AceType::DynamicCast<FrameNode>(child);
            auto group = frameNode->GetPattern<ListItemGroupPattern>();
            if (group->HasLayoutedItem()) {
                std::pair<float, float> pos = { itor->second.startPos, itor->second.endPos };
                return group->GetEstimateOffset(estimateOffset_ + skipHeight, pos);
            }
            skipHeight += averageHeight;
            itor++;
        }
        return estimateOffset_ - targetPos_.first;
    }

    void CalculateLazyForEachNode(RefPtr<LazyForEachNode> node)
    {
        int32_t count = node->FrameCount();
        if (count <= 0) {
            return;
        }
        if ((endIndex_ < currentIndex_) || (startIndex_ >= currentIndex_ + count)) {
            estimateHeight_ += (estimateItemHeight_ + spaceWidth_) * GetLines(lanes_, count);
            if (currentIndex_ > 0) {
                estimateHeight_ -= spaceWidth_;
            }
            currentIndex_ += count;
            return;
        }

        bool hasGroup = false;
        int32_t startIndex = std::max(currentIndex_, startIndex_);
        int32_t endIndex = std::min(currentIndex_ + count - 1, endIndex_);
        float averageHeight = GetLazyForEachIndexAverageHeight(node, startIndex, endIndex, hasGroup);
        int32_t lanes = hasGroup ? 1 : lanes_;
        if (startIndex == startIndex_) {
            int32_t curr = GetLines(lanes, startIndex_ - currentIndex_);
            estimateOffset_ = estimateHeight_ + (averageHeight + spaceWidth_) * curr;
            estimateOffset_ = CalculateOffset(node, averageHeight);
            if (startIndex_ > 0) {
                estimateOffset_ -= spaceWidth_;
            }
        }
        estimateHeight_ += (averageHeight + spaceWidth_) * GetLines(lanes, count);
        if (currentIndex_ > 0) {
            estimateHeight_ -= spaceWidth_;
        }
        currentIndex_ += count;
    }

    bool GetEstimateHeightAndOffset(RefPtr<UINode> node)
    {
        CalculateUINode(node);
        if (currLane_ > 0) {
            estimateHeight_ += currRowHeight_;
            currLane_ = 0;
            currRowHeight_ = 0.0f;
        }
        return true;
    }

    float GetEstimateHeight() const
    {
        return estimateHeight_;
    }

    float GetEstimateOffset() const
    {
        return estimateOffset_;
    }

private:
    float GetAverageItemHeight() const
    {
        if (totalItemCount_ > 0) {
            return totalItemHeight_ / totalItemCount_;
        }
        return estimateItemHeight_;
    }

    static int32_t GetLines(int32_t lanes, int32_t count)
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

    Axis axis_ = Axis::VERTICAL;
    int32_t currentIndex_ = 0;
    int32_t startIndex_ = 0;
    int32_t endIndex_ = 0;
    std::pair<float, float> targetPos_ = { 0.0f, 0.0f };
    float estimateHeight_ = 0.0f;
    float estimateOffset_ = 0.0f;
    float spaceWidth_ = 0.0f;

    float totalItemHeight_ = 0.0f;
    float totalItemCount_ = 0.0f;

    float estimateItemHeight_ = DEFAULT_ITEM_HEIGHT;
    float groupedItemHeight_ = DEFAULT_ITEM_HEIGHT;

    int32_t lanes_ = 1;
    int32_t currLane_ = 0;
    float currRowHeight_ = 0.0f;

    const ListLayoutAlgorithm::PositionMap& itemPosition_;
};
} // namespace OHOS::Ace::NG
#endif
