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
#include <list>
#include <optional>
#include <unordered_map>
#include <unordered_set>

#include "fill_algorithm.h"

#include "core/components/scroll/scroll_controller_base.h"

namespace OHOS::Ace::NG {

class FrameNode;

class ScrollWindowAdapter : public virtual AceType {
    DECLARE_ACE_TYPE(ScrollWindowAdapter, AceType);

public:
    ScrollWindowAdapter(FrameNode* container, const RefPtr<FillAlgorithm>& fillAlgorithm)
        : fillAlgorithm_(fillAlgorithm), container_(container)
    {}
    ~ScrollWindowAdapter() override = default;

    void UpdateViewport(const SizeF& size, Axis axis);

    void PrepareReset(int32_t idx, float extraOffset = 0.0f);
    void PrepareJump(int32_t idx, ScrollAlign align = ScrollAlign::START, float extraOffset = 0.0f);
    /**
     * @return true if underlying items are ready
     */
    bool PrepareLoadToTarget(int32_t targetIdx, ScrollAlign align = ScrollAlign::START, float extraOffset = 0.0f);

    /**
     * @param x positive if scrolling right, negative if scrolling left
     * @param y positive if scrolling down, negative if scrolling up
     * @return true if need to recompose
     */
    bool UpdateSlidingOffset(float delta);

    FrameNode* InitPivotItem(FillDirection direction);

    RefPtr<FrameNode> GetChildByIndex(uint32_t index);
    uint32_t GetIndexOfChild(const RefPtr<FrameNode>& child) const;

    // return the mark item which new item will insert after or before.
    FrameNode* NeedMoreElements(FrameNode* markItem, FillDirection direction);

    void RegisterUpdater(std::function<void(int32_t, void*)>&& updater)
    {
        updaters_.emplace_back(updater); // need to figure out when to detach updaters
    }

    void SetTotalCount(int32_t totalCount)
    {
        totalCount_ = totalCount;
    }

    int32_t GetTotalCount() const
    {
        return totalCount_;
    }

    /**
     * @brief initialize layout info when frontend recomposition starts
     *
     * @param offset offset of LazyForEach in parent's children list
     */
    void Prepare(uint32_t offset);

private:
    FrameNode* GetChildPtrByIndex(uint32_t index);

    /**
     * @brief Call updaters with @c markIdx to request recomposition.
     *
     * @param markIdx
     */
    void RequestRecompose(int32_t markIdx) const;

    /**
     * @brief Determine if more items can be filled in @c direction to reach targetIdx_
     * @return true if need to stop filling in @c direction
     */
    bool FillToTarget(FillDirection direction, int32_t curIdx) const;

    SizeF size_ = { 0.0f, 0.0f };
    RefPtr<FillAlgorithm> fillAlgorithm_;
    FrameNode* container_ = nullptr;

    int32_t markIndex_ = -1;
    int32_t totalCount_ = 0;

    using FrontendUpdater = std::function<void(int32_t, void*)>;
    std::list<FrontendUpdater> updaters_;

    std::unordered_map<int32_t, WeakPtr<FrameNode>> indexToNode_;
    std::unordered_map<FrameNode*, int32_t> nodeToIndex_;
    std::unordered_set<int32_t> filled_; // to record measured items during Fill

    Axis axis_ = Axis::VERTICAL;
    uint32_t offset_ = 0; // offset of current LazyForEach in node tree

    struct PendingJump {
        PendingJump(int32_t jumpIdx, ScrollAlign align, float extraOffset)
            : index(jumpIdx), align(align), extraOffset(extraOffset)
        {}
        int32_t index = -1;
        ScrollAlign align = ScrollAlign::START;
        float extraOffset = 0.0f;
    };
    std::unique_ptr<PendingJump> jumpPending_; // to perform a jump on the next recomposition
    std::unique_ptr<PendingJump> target_;      // to scroll with animation to target index
    bool rangeMode_ = false;                   // true if providing item range to frontend directly
};
} // namespace OHOS::Ace::NG
