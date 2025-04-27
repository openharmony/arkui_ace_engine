/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_POSITION_MAP_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_POSITION_MAP_H


#include <cstddef>
#include <cstdint>
#include <functional>
#include <optional>
#include <tuple>
#include <queue>

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"
#include "core/components_ng/pattern/list/list_children_main_size.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/property/measure_property.h"


namespace OHOS::Ace::NG {
class ListItemGroupPattern;
namespace {

struct PositionInfo {
    float mainPos;
    float mainSize;
    bool isGroup;
};

enum class ListPosMapUpdate {
    NO_CHANGE = 0,
    UPDATE_ALL_SIZE,
    RE_CALCULATE,
};
}

class ListPositionMap : public virtual AceType {
    DECLARE_ACE_TYPE(ListPositionMap, AceType)
public:
    ListPositionMap() = default;
    ~ListPositionMap() override = default;

    void UpdatePos(int32_t index, PositionInfo posInfo)
    {
        posMap_[index] = posInfo;
    }

    void UpdatePosRange(int32_t startIndex, int32_t endIndex, PositionInfo posInfo, float space, int32_t lanes)
    {
        for (int32_t i = startIndex; i < endIndex; i++) {
            posMap_[i] = posInfo;
            if (lanes >= 1 && (i % lanes == lanes - 1)) {
                posInfo.mainPos = posInfo.mainPos + posInfo.mainSize + space;
            }
        }
    }

    void UpdatePosWithCheck(int32_t index, PositionInfo posInfo)
    {
        auto iter = posMap_.find(index);
        if (iter == posMap_.end()) {
            posMap_[index] = posInfo;
            return;
        }
        iter->second.isGroup = posInfo.isGroup;
        if (LessNotEqual(iter->second.mainSize, posInfo.mainSize)) {
            iter->second.mainSize = posInfo.mainSize;
        }
    }

    void ClearPosMap()
    {
        posMap_.clear();
    }

    void MarkDirty(ListChangeFlag flag)
    {
        dirty_ = dirty_ | flag;
    }

    void ClearDirty()
    {
        dirty_ = LIST_NO_CHANGE;
    }

    float GetTotalHeight() const
    {
        return totalHeight_;
    }

    float GetPrevTotalHeight() const
    {
        return prevTotalHeight_;
    }

    ListPosMapUpdate CheckPosMapUpdateRule()
    {
        ListPosMapUpdate flag;
        if (dirty_ == LIST_NO_CHANGE) {
            flag = ListPosMapUpdate::NO_CHANGE;
        } else if (0 == (dirty_ & (LIST_UPDATE_CHILD_SIZE | LIST_UPDATE_LANES | LIST_GROUP_UPDATE_HEADER_FOOTER |
                                      LIST_UPDATE_HEADER_FOOTER))) {
            flag = ListPosMapUpdate::UPDATE_ALL_SIZE;
        } else {
            flag = ListPosMapUpdate::RE_CALCULATE;
        }
        return flag;
    }

    void UpdatePosMapStart(float delta, float& listCurrentPos, float space,
        int32_t startIndex, float startPos, bool groupAtStart)
    {
        auto it = posMap_.find(startIndex);
        if (it == posMap_.begin() || it == posMap_.end()) {
            return;
        }
        startPos = startPos + listCurrentPos;
        it--;
        float prevPos = it->second.mainPos + it->second.mainSize + space;
        int32_t prevIndex = it->first;
        if (prevIndex + 1 >= startIndex && groupAtStart) {
            if (NearEqual(prevPos, startPos)) {
                return;
            }
        } else {
            if (LessNotEqual(prevPos, startPos)) {
                return;
            }
        }
        listCurrentPos += prevPos - startPos;
    }

    void UpdatePosMapEnd(int32_t prevEndIndex, float space, bool groupAtEnd)
    {
        auto it = posMap_.find(prevEndIndex);
        if (it == posMap_.end()) {
            return;
        }
        float prevPos = it->second.mainPos + it->second.mainSize + space;
        it++;
        if (it == posMap_.end()) {
            return;
        }
        if (prevEndIndex + 1 >= it->first && groupAtEnd) {
            if (NearEqual(prevPos, it->second.mainPos)) {
                return;
            }
        } else {
            if (LessNotEqual(prevPos, it->second.mainPos)) {
                return;
            }
        }
        float delta = prevPos - it->second.mainPos;
        while (it != posMap_.end()) {
            it->second.mainPos += delta;
            it++;
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
                // Rules: only one type node(ListItem or ListItemGroup) can exist in LazyForEach.
                CalculateLazyForEachNode(child);
            } else if (AceType::InstanceOf<RepeatVirtualScrollNode>(child)) {
                CalculateLazyForEachNode(child);
            } else if (AceType::InstanceOf<RepeatVirtualScroll2Node>(child)) {
                CalculateLazyForEachNode(child);
            } else {
                CalculateUINode(child);
            }
        }
    }

    std::optional<bool> GetLazyForEachChildIsGroup(RefPtr<UINode> node)
    {
        std::optional<bool> isGroup;
        auto children = node->GetChildren();
        if (children.size() > 0) {
            auto child = children.begin();
            while (child != children.end() && !((*child)->GetFrameChildByIndex(0, false))) {
                child++;
            }
            auto frameNode = AceType::DynamicCast<FrameNode>((*child)->GetFrameChildByIndex(0, false));
            if (frameNode) {
                isGroup = frameNode->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
            }
        }
        if (!(isGroup.has_value())) {
            auto listNode = node->GetParentFrameNode();
            CHECK_NULL_RETURN(listNode, isGroup);
            auto wrapper = listNode->GetOrCreateChildByIndex(curIndex_);
            CHECK_NULL_RETURN(wrapper, isGroup);
            isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
        }
        return isGroup;
    }

    void CalculateLazyForEachNode(RefPtr<UINode> node)
    {
        int32_t count = node->FrameCount();
        if (count <= 0) {
            return;
        }
        std::optional<bool> isGroup = GetLazyForEachChildIsGroup(node);
        if (!(isGroup.has_value())) {
            TAG_LOGW(AceLogTag::ACE_LIST,
                "ListPositionMap Conflict: LazyForEach FrameCount > 0, but get child type failed.");
            isGroup = false;
        }
        while (count--) {
            isGroup.value() ? CalculateGroupNode() : CalculateListItemNode();
        }
        return;
    }

    void CalculateFrameNode(RefPtr<FrameNode> frameNode)
    {
        CHECK_NULL_VOID(frameNode);
        auto listItemGroupPatten = frameNode->GetPattern<ListItemGroupPattern>();
        if (listItemGroupPatten) {
            CalculateGroupNode();
        } else {
            CalculateListItemNode();
        }
    }

    void CalculateListItemNode()
    {
        curRowHeight_ = std::max(curRowHeight_, childrenSize_->GetChildSize(curIndex_));
        curLine_++;
        if (curLine_ == lanes_ || curIndex_ == totalItemCount_ - 1) {
            while (curLine_) {
                curLine_--;
                posMap_[curIndex_ - curLine_] = { totalHeight_, curRowHeight_ };
            }
            totalHeight_ += (curRowHeight_ + space_);
            curRowHeight_ = 0.0f;
        }
        curIndex_++;
    }

    void CalculateGroupNode()
    {
        if (curLine_ > 0) {
            while (curLine_) {
                curLine_--;
                posMap_[curIndex_ - 1 - curLine_] = { totalHeight_, curRowHeight_ };
            }
            totalHeight_ += (curRowHeight_ + space_);
            curRowHeight_ = 0.0f;
        }
        curRowHeight_ = childrenSize_->GetChildSize(curIndex_);
        posMap_[curIndex_] = { totalHeight_, curRowHeight_ };
        totalHeight_ += (curRowHeight_ + space_);
        curLine_ = 0;
        curRowHeight_ = 0.0f;
        curIndex_++;
    }

    void PosMapRecalculate(LayoutWrapper* layoutWrapper)
    {
        curIndex_ = 0;
        curLine_ = 0;
        totalHeight_ = 0.0f;
        curRowHeight_ = 0.0f;
        if (lanes_ == 1) {
            for (int32_t index = 0; index < totalItemCount_; index++) {
                curRowHeight_ = childrenSize_->GetChildSize(index);
                posMap_[index] = { totalHeight_, curRowHeight_ };
                totalHeight_ += (curRowHeight_ + space_);
            }
            totalHeight_ -= space_;
        } else {
            auto listNode = layoutWrapper->GetHostNode();
            CHECK_NULL_VOID(listNode);
            CalculateUINode(listNode);
            totalHeight_ -= space_;
        }
        TAG_LOGI(AceLogTag::ACE_LIST, "List PosMapRecalculate totalHeight:%{public}f prevTotalHeight:%{public}f, "
            "lanes:%{public}d, space:%{public}f, totalItemCount:%{public}d",
            totalHeight_, prevTotalHeight_, lanes_, space_, totalItemCount_);
    }

    void GroupPosMapRecalculate()
    {
        curIndex_ = 0;
        totalHeight_ = headerSize_;
        curRowHeight_ = 0.0f;
        curLine_ = 0;

        for (int32_t index = 0; index < totalItemCount_;) {
            while (curLine_ < lanes_) {
                curRowHeight_ = std::max(curRowHeight_, childrenSize_->GetChildSize(index + curLine_));
                curLine_++;
            }
            curLine_ = 0;
            int32_t curRowEndIndex = std::min(index + lanes_ - 1, totalItemCount_ - 1);
            while (index <= curRowEndIndex) {
                posMap_[index++] = { totalHeight_, curRowHeight_ };
            }
            totalHeight_ += (curRowHeight_ + space_);
            curRowHeight_ = 0.0f;
        }
        totalHeight_ = totalHeight_ - space_ + footerSize_;
    }

    virtual void UpdatePosMap(LayoutWrapper* layoutWrapper, int32_t lanes, float space,
        RefPtr<ListChildrenMainSize>& childrenSize)
    {
        childrenSize_ = childrenSize;
        if (totalItemCount_ != layoutWrapper->GetTotalChildCount()) {
            dirty_ |= LIST_UPDATE_ITEM_COUNT;
            totalItemCount_ = layoutWrapper->GetTotalChildCount();
        }
        if (lanes != lanes_) {
            dirty_ |= LIST_UPDATE_LANES;
            lanes_ = lanes;
        }
        if (!NearEqual(space, space_)) {
            dirty_ |= LIST_UPDATE_SPACE;
            space_ = space;
        }
        switch (CheckPosMapUpdateRule()) {
            case ListPosMapUpdate::NO_CHANGE:
                break;
            case ListPosMapUpdate::UPDATE_ALL_SIZE:
                PosMapRecalculate(layoutWrapper);
                break;
            case ListPosMapUpdate::RE_CALCULATE:
            default:
                PosMapRecalculate(layoutWrapper);
        }
        ClearDirty();
    }

    void UpdateGroupPosMap(int32_t totalCount, int32_t lanes, float space,
        RefPtr<ListChildrenMainSize>& childrenSize, float headerSize, float footerSize)
    {
        childrenSize_ = childrenSize;
        prevTotalHeight_ = totalHeight_;
        if (totalCount != totalItemCount_) {
            dirty_ |= LIST_UPDATE_ITEM_COUNT;
            totalItemCount_ = totalCount;
        }
        if (lanes != lanes_) {
            dirty_ |= LIST_UPDATE_LANES;
            lanes_ = lanes;
        }
        if (!NearEqual(space, space_)) {
            dirty_ |= LIST_UPDATE_SPACE;
            space_ = space;
        }
        if (!NearEqual(headerSize, headerSize_) || !NearEqual(footerSize, footerSize_)) {
            dirty_ |= LIST_GROUP_UPDATE_HEADER_FOOTER;
            headerSize_ = headerSize;
            footerSize_ = footerSize;
        }
        if (totalItemCount_ <= 0) {
            totalHeight_ = 0;
            ClearPosMap();
            ClearDirty();
            return;
        }
        switch (CheckPosMapUpdateRule()) {
            case ListPosMapUpdate::NO_CHANGE:
                break;
            case ListPosMapUpdate::UPDATE_ALL_SIZE:
                GroupPosMapRecalculate();
                break;
            case ListPosMapUpdate::RE_CALCULATE:
            default:
                GroupPosMapRecalculate();
        }
        ClearDirty();
    }

    void UpdateTotalCount(int32_t totalCount)
    {
        totalItemCount_ = totalCount;
        auto iter = posMap_.lower_bound(totalCount);
        posMap_.erase(iter, posMap_.end());
    }

    float GetPos(int32_t index, float offset = 0.0f)
    {
        return posMap_[index].mainPos - offset;
    }

    float GetGroupLayoutOffset(int32_t startIndex, float startPos)
    {
        return posMap_[startIndex].mainPos - startPos;
    }

    PositionInfo GetPositionInfo(int32_t index) const
    {
        auto it = posMap_.find(index);
        if (it == posMap_.end()) {
            return { -1.0f, -1.0f };
        }
        return it->second;
    }

    std::pair<int32_t, float> GetStartIndexAndPos() const
    {
        if (posMap_.empty()) {
            return { -1, 0.0f };
        }
        const auto& start = posMap_.begin();
        return { start->first, start->second.mainPos };
    }

    std::pair<int32_t, float> GetEndIndexAndPos() const
    {
        if (posMap_.empty()) {
            return { -1, 0.0f };
        }
        const auto& end = posMap_.rbegin();
        return { end->first, end->second.mainPos + end->second.mainSize };
    }

    void OptimizeBeforeMeasure(int32_t& beginIndex, float& beginPos, const float offset, const float contentSize)
    {
        if (NearZero(offset) || GreatOrEqual(contentSize, totalHeight_)) {
            return;
        }
        float chainOffset = chainOffsetFunc_ ? chainOffsetFunc_(beginIndex) : 0.0f;
        if (Positive(offset)) {
            float criticalPos = offset;
            std::pair<int32_t, float> rowInfo = GetRowEndIndexAndHeight(beginIndex);
            while (!NearEqual(posMap_[beginIndex].mainPos + rowInfo.second, totalHeight_) &&
                LessNotEqual(beginPos + rowInfo.second + chainOffset, criticalPos)) {
                beginIndex = rowInfo.first + 1;
                beginPos += (rowInfo.second + space_);
                rowInfo = GetRowEndIndexAndHeight(beginIndex);
                chainOffset = chainOffsetFunc_ ? chainOffsetFunc_(beginIndex) : 0.0f;
            }
        } else {
            float criticalPos = offset + contentSize;
            std::pair<int32_t, float> rowInfo = GetRowEndIndexAndHeight(beginIndex);
            while (Positive(posMap_[beginIndex].mainPos) &&
                GreatNotEqual(beginPos - rowInfo.second + chainOffset, criticalPos)) {
                beginIndex = GetRowStartIndex(beginIndex) - 1;
                beginPos -= (rowInfo.second + space_);
                rowInfo = GetRowEndIndexAndHeight(beginIndex);
                chainOffset = chainOffsetFunc_ ? chainOffsetFunc_(beginIndex) : 0.0f;
            }
        }
    }

    void SetChainOffsetCallback(std::function<float(int32_t)> func)
    {
        chainOffsetFunc_ = std::move(func);
    }

    int32_t GetRowStartIndex(const int32_t input)
    {
        int32_t startIndex = input;
        while (startIndex > 0 && NearEqual(posMap_[startIndex].mainPos, posMap_[startIndex - 1].mainPos)) {
            startIndex--;
        }
        return startIndex;
    }

    int32_t GetRowEndIndex(const int32_t input)
    {
        std::pair<int32_t, float> rowInfo = GetRowEndIndexAndHeight(input);
        return rowInfo.first;
    }

    float GetRowHeight(int32_t input)
    {
        std::pair<int32_t, float> rowInfo = GetRowEndIndexAndHeight(input);
        return rowInfo.second;
    }

    std::pair<int32_t, float> GetRowEndIndexAndHeight(const int32_t input)
    {
        int32_t endIndex = input;
        float rowHeight = 0.0f;
        while (endIndex < (totalItemCount_ - 1) &&
            NearEqual(posMap_[endIndex].mainPos, posMap_[endIndex + 1].mainPos)) {
            endIndex++;
        }
        if (endIndex == totalItemCount_ - 1) {
            rowHeight = totalHeight_ - posMap_[endIndex].mainPos - footerSize_;
        } else {
            rowHeight = posMap_[endIndex + 1].mainPos  - posMap_[endIndex].mainPos - space_;
        }
        return { endIndex, rowHeight };
    }

    void ReversePosMap()
    {
        totalHeight_ = 0.0f;
        float curRowHeight = posMap_.begin()->second.mainSize;
        std::map<int32_t, PositionInfo> posMap;
        for (int32_t index = totalItemCount_ - 1; index >= 0; --index) {
            auto posIndex = totalItemCount_ - index - 1;
            posMap[posIndex] = {totalHeight_, posMap_[posIndex].mainSize};
            if (index > 0 && !NearEqual(posMap_[index].mainPos, posMap_[index - 1].mainPos)) {
                curRowHeight = std::max(posMap_[posIndex].mainSize, curRowHeight);
                totalHeight_ += (curRowHeight + space_);
                curRowHeight = 0.0f;
            } else {
                curRowHeight = std::max(posMap_[posIndex].mainSize, curRowHeight);
            }
        }
        posMap_ = std::move(posMap);
        totalHeight_ += curRowHeight;
    }
protected:
    RefPtr<ListChildrenMainSize> childrenSize_;
    ListChangeFlag dirty_ = LIST_NO_CHANGE;
    int32_t totalItemCount_ = 0;
    float space_ = 0.0f;
    int32_t lanes_ = -1;

private:
    std::map<int32_t, PositionInfo> posMap_;
    std::function<float(int32_t)> chainOffsetFunc_;
    int32_t curLine_ = 0;
    int32_t curIndex_ = 0;
    float totalHeight_ = 0.0f;
    float prevTotalHeight_ = 0.0f;
    float curRowHeight_ = 0.0f;
    float headerSize_ = 0.0f;
    float footerSize_ = 0.0f;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_POSITION_MAP_H