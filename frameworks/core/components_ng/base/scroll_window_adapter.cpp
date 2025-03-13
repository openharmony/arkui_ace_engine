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
    range_.start = range_.end = idx;
    jumpPending_ = std::make_unique<PendingJump>(idx, ScrollAlign::START, extraOffset);
    fillAlgorithm_->MarkJump();
    RequestRecompose(range_);
}

void ScrollWindowAdapter::PrepareJump(int32_t idx, ScrollAlign align, float extraOffset)
{
    if (idx == LAST_ITEM) {
        idx = totalCount_ - 1;
    }
    if (idx == range_.start) {
        return;
    }
    range_.start = range_.end = idx;
    jumpPending_ = std::make_unique<PendingJump>(idx, align, extraOffset);
    fillAlgorithm_->MarkJump();
    RequestRecompose(range_);
}

bool ScrollWindowAdapter::PrepareLoadToTarget(int32_t targetIdx, ScrollAlign align, float extraOffset)
{
    if (target_ && targetIdx == target_->index) {
        target_.reset(); // prevent loop and good timing to reset target_
        return true;
    }
    target_ = std::make_unique<PendingJump>(targetIdx, align, extraOffset);
    RequestRecompose(range_);
    return false;
}

FrameNode* ScrollWindowAdapter::InitPivotItem(FillDirection direction)
{
    const int32_t markIndex = direction == FillDirection::START ? range_.start : range_.end;
    auto* item = GetChildPtrByIndex(markIndex);
    if (!item) {
        nodeToIndex_.clear();
        indexToNode_.clear();
        item = static_cast<FrameNode*>(container_->GetLastChild().GetRawPtr());
    }
    if (!item) {
        LOGE("current node of %{public}d is nullptr, childrenCount = %{public}d", markIndex,
            container_->TotalChildCount());
        return nullptr;
    }
    // 1: remeasure the mark item.
    if (!filled_.count(markIndex)) {
        fillAlgorithm_->FillMarkItem(size_, axis_, item, markIndex);
        filled_.insert(markIndex);

        indexToNode_[markIndex] = WeakClaim(item);
        nodeToIndex_[item] = markIndex;
    }
    // 2: check if more space for new item.
    if (!fillAlgorithm_->CanFillMore(axis_, size_, markIndex, direction)) {
        LOGI("no more space left");
        return nullptr;
    }
    return item;
}

FrameNode* ScrollWindowAdapter::NeedMoreElements(FrameNode* markItem, FillDirection direction)
{
    // check range.
    if (direction == FillDirection::START && (range_.start <= 0)) {
        return nullptr;
    }
    if (direction == FillDirection::END && (range_.end >= totalCount_ - 1)) {
        return nullptr;
    }
    if (markItem == nullptr) {
        return InitPivotItem(direction);
    }

    auto* pendingNode = static_cast<FrameNode*>(
        direction == FillDirection::START ? container_->GetChildBefore(markItem) : container_->GetChildAfter(markItem));
    if (!pendingNode) {
        LOGE("fail to find pendingNode");
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
        return reached ? nullptr : pendingNode;
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
        LOGE("no more space left");
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
    if (parallelMode_) {
        bool res = fillAlgorithm_->OnSlidingOffsetUpdate(size_, axis_, delta);
        if (res) {
            RequestRecompose(fillAlgorithm_->GetRange());
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
    LOGD("need to load");
    range_ = fillAlgorithm_->GetRange();

    RequestRecompose(range_);
    return true;
}

void ScrollWindowAdapter::RequestRecompose(const ItemRange& currentRange) const
{
    for (auto&& updater : updaters_) {
        if (updater) {
            // nullptr to mark the first item
            updater(currentRange.start, currentRange.end, nullptr);
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
            scroll->ScrollToIndex(range_.start, false, jumpPending_->align, jumpPending_->extraOffset);
        } else if (auto swiper = container_->GetPattern<SwiperPattern>(); swiper) {
            swiper->ChangeIndex(range_.start, false);
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
        range_ = fillAlgorithm_->GetRange();
        RequestRecompose(range_);
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
