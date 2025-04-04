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

#include "core/components_ng/base/scroll_window_adapter.h"

#include <cstdint>

#include "base/utils/utils.h"
#include "core/components_ng/base/fill_algorithm.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"

namespace OHOS::Ace::NG {

void ScrollWindowAdapter::PrepareReset(int32_t idx, float extraOffset)
{
    markIndex_ = idx;
    jumpPending_ = std::make_unique<PendingJump>(idx, ScrollAlign::START, extraOffset);
    fillAlgorithm_->MarkJump();
    RequestRecompose(idx);
}

void ScrollWindowAdapter::PrepareJump(int32_t idx, ScrollAlign align, float extraOffset)
{
    if (idx == LAST_ITEM) {
        idx = totalCount_ - 1;
    }
    if (idx == markIndex_) {
        return;
    }
    markIndex_ = idx;
    jumpPending_ = std::make_unique<PendingJump>(idx, align, extraOffset);
    fillAlgorithm_->MarkJump();
    RequestRecompose(idx);
}

bool ScrollWindowAdapter::PrepareLoadToTarget(int32_t targetIdx, ScrollAlign align, float extraOffset)
{
    if (target_ && targetIdx == target_->index) {
        return true; // prevent loop
    }
    target_ = std::make_unique<PendingJump>(targetIdx, align, extraOffset);
    RequestRecompose(markIndex_);
    return false;
}

FrameNode* ScrollWindowAdapter::InitPivotItem(FillDirection direction)
{
    auto* item = GetChildPtrByIndex(markIndex_);
    if (!item) {
        nodeToIndex_.clear();
        indexToNode_.clear();
        item = static_cast<FrameNode*>(container_->GetLastChild().GetRawPtr());
    }
    if (!item) {
        LOGW("current node of %{public}d is nullptr, childrenCount = %{public}d", markIndex_,
            container_->TotalChildCount());
        return nullptr;
    }
    // 1: remeasure the mark item.
    if (!filled_.count(markIndex_)) {
        fillAlgorithm_->FillMarkItem(size_, axis_, item, markIndex_);
        filled_.insert(markIndex_);

        indexToNode_[markIndex_] = WeakClaim(item);
        nodeToIndex_[item] = markIndex_;
    }
    // 2: check if more space for new item.
    if (!fillAlgorithm_->CanFillMore(axis_, size_, markIndex_, direction)) {
        return nullptr;
    }
    return item;
}

FrameNode* ScrollWindowAdapter::NeedMoreElements(FrameNode* markItem, FillDirection direction)
{
    // check range.
    if (direction == FillDirection::START && (markIndex_ <= 0)) {
        return nullptr;
    }
    if (direction == FillDirection::END && (markIndex_ >= totalCount_ - 1)) {
        return nullptr;
    }
    if (markItem == nullptr) {
        return InitPivotItem(direction);
    }

    auto* pendingNode = static_cast<FrameNode*>(
        direction == FillDirection::START ? container_->GetChildBefore(markItem) : container_->GetChildAfter(markItem));
    if (!pendingNode) {
        LOGW("fail to find pendingNode");
        return nullptr;
    }
    auto index = direction == FillDirection::START ? nodeToIndex_[markItem] - 1 : nodeToIndex_[markItem] + 1;
    indexToNode_[index] = WeakClaim(pendingNode);
    nodeToIndex_[pendingNode] = index;
    // 1: check index.
    if (index <= 0 && direction == FillDirection::START) {
        return nullptr;
    }
    if (index >= totalCount_ - 1 && direction == FillDirection::END) {
        return nullptr;
    }
    if (target_) {
        bool reached = FillToTarget(direction, index);
        if (reached) {
            target_.reset();
            return nullptr;
        }
        return pendingNode;
        // keep creating until targetNode is reached
    }
    if (!filled_.count(index)) {
        // 2: measure the pendingNode
        direction == FillDirection::START ? fillAlgorithm_->FillPrev(size_, axis_, pendingNode, index)
                                          : fillAlgorithm_->FillNext(size_, axis_, pendingNode, index);
        filled_.insert(index);
    }
    // 3: check if more space for new item.
    if (!fillAlgorithm_->CanFillMore(axis_, size_, index, direction)) {
        return nullptr;
    }
    return pendingNode;
}

bool ScrollWindowAdapter::UpdateSlidingOffset(float delta)
{
    if (NearZero(delta)) {
        return false;
    }
    fillAlgorithm_->OnSlidingOffsetUpdate(delta);
    if (rangeMode_) {
        bool res = fillAlgorithm_->OnSlidingOffsetUpdate(size_, axis_, delta);
        if (res) {
            auto range = fillAlgorithm_->GetRange();
            RequestRecompose(range.first);
        }
        return res;
    }

    if (Negative(delta)) {
        if (!fillAlgorithm_->CanFillMore(axis_, size_, -1, FillDirection::END)) {
            return false;
        }
    } else {
        if (!fillAlgorithm_->CanFillMore(axis_, size_, -1, FillDirection::START)) {
            return false;
        }
    }
    markIndex_ = fillAlgorithm_->GetMarkIndex();

    RequestRecompose(markIndex_);
    return true;
}

void ScrollWindowAdapter::RequestRecompose(int32_t markIdx) const
{
    for (auto&& updater : updaters_) {
        if (updater) {
            // nullptr to mark the first item
            updater(markIdx, nullptr);
        }
    }
}

void ScrollWindowAdapter::Prepare(uint32_t offset)
{
    offset_ = offset;
    filled_.clear();
    fillAlgorithm_->PreFill(size_, axis_, totalCount_);
    if (jumpPending_) {
        if (auto scroll = container_->GetPattern<ScrollablePattern>(); scroll) {
            scroll->ScrollToIndex(markIndex_, false, jumpPending_->align, jumpPending_->extraOffset);
        } else if (auto swiper = container_->GetPattern<SwiperPattern>(); swiper) {
            swiper->ChangeIndex(markIndex_, false);
        }
        jumpPending_.reset();
    } else if (target_) {
        if (auto scroll = container_->GetPattern<ScrollablePattern>(); scroll) {
            scroll->ScrollToIndex(target_->index, true, target_->align, target_->extraOffset);
        } else if (auto swiper = container_->GetPattern<SwiperPattern>(); swiper) {
            swiper->ChangeIndex(target_->index, true);
        }
    }
}

void ScrollWindowAdapter::UpdateViewport(const SizeF& size, Axis axis)
{
    if (size == size_ && axis == axis_) {
        return;
    }
    size_ = size;
    axis_ = axis;

    if (fillAlgorithm_->CanFillMore(axis_, size_, -1, FillDirection::END)) {
        markIndex_ = fillAlgorithm_->GetMarkIndex();
        RequestRecompose(markIndex_);
    }
}

FrameNode* ScrollWindowAdapter::GetChildPtrByIndex(uint32_t index)
{
    if (index < offset_) {
        return container_->GetFrameNodeChildByIndex(index);
    }
    if (index >= offset_ + totalCount_) {
        // LazyForEach generated items are at the back of children list
        return container_->GetFrameNodeChildByIndex(index - filled_.size()); // filled.size = active item count
    }
    FrameNode* node = nullptr;
    auto iter = indexToNode_.find(index);
    if (iter != indexToNode_.end()) {
        node = iter->second.Upgrade().GetRawPtr();
        if (node == nullptr) {
            indexToNode_.erase(iter);
        }
    }
    return node;
}

RefPtr<FrameNode> ScrollWindowAdapter::GetChildByIndex(uint32_t index)
{
    return Claim(GetChildPtrByIndex(index));
}

uint32_t ScrollWindowAdapter::GetIndexOfChild(const RefPtr<FrameNode>& child) const
{
    auto iter = nodeToIndex_.find(child.GetRawPtr());
    if (iter != nodeToIndex_.end()) {
        return iter->second;
    }
    return INT_MAX;
}

bool ScrollWindowAdapter::FillToTarget(FillDirection direction, int32_t curIdx) const
{
    if (!target_) {
        return true;
    }
    if (direction == FillDirection::START ? curIdx > target_->index : curIdx < target_->index) {
        return false;
    }
    if (curIdx == target_->index) {
        return true;
    }
    return true;
}
} // namespace OHOS::Ace::NG