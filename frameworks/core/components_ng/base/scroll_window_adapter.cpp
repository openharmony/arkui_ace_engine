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

namespace OHOS::Ace::NG {

void ScrollWindowAdapter::UpdateMarkItem(int32_t index, bool notify)
{
    if (index == -1) {
        index = fillAlgorithm_->GetMarkIndex();
    }
    if (markIndex_ == index) {
        return;
    }
    markIndex_ = index;
    RequestRecompose();
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
        LOGE("current node of %{public}d is nullptr, childrenCount = %{public}d", markIndex_,
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
        LOGI("no more space left");
        return nullptr;
    }
    return item;
}

FrameNode* ScrollWindowAdapter::NeedMoreElements(FrameNode* markItem, FillDirection direction)
{
    CHECK_NULL_RETURN(fillAlgorithm_->IsReady(), nullptr);
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

void ScrollWindowAdapter::UpdateSlidingOffset(float delta)
{
    if (NearZero(delta)) {
        return;
    }
    fillAlgorithm_->OnSlidingOffsetUpdate(delta);
    if (rangeMode_) {
        bool res = fillAlgorithm_->OnSlidingOffsetUpdate(size_, axis_, delta);
        if (res && updater_) {
            auto range = fillAlgorithm_->GetRange();
            updater_(range.first, nullptr); // placeholder
        }
        return;
    }

    if (Negative(delta)) {
        if (!fillAlgorithm_->CanFillMore(axis_, size_, -1, FillDirection::END)) {
            return;
        }
    } else {
        if (!fillAlgorithm_->CanFillMore(axis_, size_, -1, FillDirection::START)) {
            return;
        }
    }
    LOGD("need to load");
    markIndex_ = fillAlgorithm_->GetMarkIndex();

    RequestRecompose();
}

void ScrollWindowAdapter::RequestRecompose()
{
    if (updater_) {
        // nullptr to mark the first item
        updater_(markIndex_, nullptr);
    }
}
void ScrollWindowAdapter::Prepare()
{
    filled_.clear();
    fillAlgorithm_->PreFill(size_, axis_, totalCount_);
}
} // namespace OHOS::Ace::NG