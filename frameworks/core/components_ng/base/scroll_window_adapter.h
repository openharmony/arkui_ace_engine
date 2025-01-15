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

#pragma once

#include <cstdint>
#include <functional>
#include <optional>
#include <unordered_map>

#include "fill_algorithm.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

namespace OHOS::Ace::NG {

class FrameNode;

class ScrollWindowAdapter : public virtual AceType {
    DECLARE_ACE_TYPE(ScrollWindowAdapter, AceType);

public:
    ScrollWindowAdapter(FrameNode* container, const RefPtr<FillAlgorithm>& fillAlgorithm)
        : fillAlgorithm_(fillAlgorithm), container_(container)
    {}
    ~ScrollWindowAdapter() override = default;

    /**
     * @param index of the latest pivot item.
     * @param notify true if need to notify frontend of pivot change.
     */
    void UpdateMarkItem(int32_t index, bool notify);

    void UpdateSize(const SizeF& size)
    {
        size_ = size;
    }
    void UpdateSize(float width, float height)
    {
        size_.SetWidth(width);
        size_.SetHeight(height);
    }

    void UpdateAxis(Axis axis)
    {
        axis_ = axis;
    }

    /**
     * @param x positive if scrolling right, negative if scrolling left
     * @param y positive if scrolling down, negative if scrolling up
     */
    void UpdateSlidingOffset(float x, float y);

    FrameNode* InitPivotItem(FillDirection direction);

    RefPtr<FrameNode> GetChildByIndex(uint32_t index)
    {
        auto iter = indexToNode_.find(index);
        if (iter != indexToNode_.end()) {
            return iter->second.Upgrade();
        }
        return nullptr;
    }

    FrameNode* GetChildPtrByIndex(uint32_t index)
    {
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

    // return the mark item which new item will insert after or before.
    FrameNode* NeedMoreElements(FrameNode* markItem, FillDirection direction);

    void RegisterUpdater(std::function<void(int32_t, void*)>&& updater)
    {
        updater_ = std::move(updater);
    }

    void SetTotalCount(int32_t totalCount)
    {
        totalCount_ = totalCount;
    }

    int32_t GetTotalCount() const
    {
        return totalCount_;
    }

private:
    SizeF size_ = { 0.0f, 0.0f };
    RefPtr<FillAlgorithm> fillAlgorithm_;
    FrameNode* container_ = nullptr;

    int32_t markIndex_ = -1;
    std::optional<OffsetF> markItemOffset_;
    int32_t totalCount_ = 0;

    std::function<void(int32_t, void*)> updater_;
    std::unordered_map<uint32_t, WeakPtr<FrameNode>> indexToNode_;
    std::unordered_map<FrameNode*, uint32_t> nodeToIndex_;
    std::unordered_map<FrameNode*, RectF> itemRectMap_;
    RectF startRect_;
    RectF endRect_;

    Axis axis_ = Axis::VERTICAL;
};
} // namespace OHOS::Ace::NG
