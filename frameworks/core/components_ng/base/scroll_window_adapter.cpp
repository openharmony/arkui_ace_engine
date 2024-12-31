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

#include "base/geometry/ng/rect_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

void ScrollWindowAdapter::UpdateMarkItem(int32_t index, FrameNode* node)
{
    if (markIndex_ == index) {
        return;
    }
    markIndex_ = index;
    itemRectMap_.clear();
    if (updater_) {
        // 01: mark the first loop item.
        updater_(index, reinterpret_cast<void*>(0x01));
    }
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
    constexpr int32_t requestNewItemFlag = 0x01;
    if (markItem == nullptr) {
        return reinterpret_cast<FrameNode*>(requestNewItemFlag);
    }
    // the first loop item flag.
    if (markItem == reinterpret_cast<FrameNode*>(requestNewItemFlag)) {
        // get the really item.
        // TODO: LazyForEach has initial offset index.
        auto* item = GetChildPtrByIndex(markIndex_);
        if (!item) {
            item = static_cast<FrameNode*>(container_->GetLastChild().GetRawPtr());
        }
        if (!item) {
            LOGE("current node of %{public}d is nullptr", markIndex_);
            return nullptr;
        }
        RectF rect;
        auto iter = itemRectMap_.find(item);
        if (iter == itemRectMap_.end()) {
            // 1: remeasure the mark item and get the new size.
            rect = fillAlgorithm_->CalcMarkItemRect(size_, axis_, item, markIndex_, markItemOffset_);
            markItemOffset_.reset();
            indexToNode_.clear();
            nodeToIndex_.clear();
            itemRectMap_.try_emplace(item, rect);
        } else {
            rect = iter->second;
        }
        indexToNode_[markIndex_] = WeakClaim(item);
        nodeToIndex_[item] = markIndex_;
        // 2: check if more space for new item.
        if (!fillAlgorithm_->CanFillMore(size_, rect, direction)) {
            LOGI("no more space left");
            return nullptr;
        }
        return item;
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
    // 2: remeasure the mark item and get the new size.
    RectF rect;
    auto iter = itemRectMap_.find(pendingNode);
    if (iter == itemRectMap_.end()) {
        // 1: remeasure the mark item and get the new size.
        rect =
            direction == FillDirection::START
                ? fillAlgorithm_->CalcItemRectBeforeMarkItem(size_, axis_, pendingNode, index, itemRectMap_[markItem])
                : fillAlgorithm_->CalcItemRectAfterMarkItem(size_, axis_, pendingNode, index, itemRectMap_[markItem]);
        itemRectMap_.try_emplace(pendingNode, rect);
    } else {
        rect = iter->second;
    }
    // 3: check if more space for new item.
    if (!fillAlgorithm_->CanFillMore(size_, rect, direction)) {
        LOGE("no more space left");
        return nullptr;
    }
    return pendingNode;
}

} // namespace OHOS::Ace::NG