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

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_ITEM_HEIGHT = 64.f;
}
class ListHeightOffsetCalculator {
public:
    ListHeightOffsetCalculator(int32_t index, std::pair<float, float> pos, float space)
    {
        targetPos_ = pos;
        targetIndex_ = index;
        spaceWidth_ = space;
    }

    void GetFrameNodeEstimateHeightOffset(RefPtr<FrameNode> frameNode)
    {
        CHECK_NULL_VOID(frameNode);
        auto listItemPatten = frameNode->GetPattern<ListItemPattern>();
        if (listItemPatten) {
            if (currentIndex_ > 0) {
                estimateHeight_ += spaceWidth_;
            }
            if (currentIndex_ == targetIndex_) {
                estimateOffset_ = estimateHeight_ - targetPos_.first;
            }
            float height = listItemPatten->GetEstimateHeight(GetAverageItemHeight());
            estimateHeight_ += height;
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
            if (currentIndex_ == targetIndex_) {
                estimateOffset_ = listItemGroupPatten->GetEstimateOffset(estimateHeight_, targetPos_);
            }
            estimateHeight_ += listItemGroupPatten->GetEstimateHeight(groupedItemHeight_);
            currentIndex_++;
        }
    }

    bool GetEstimateHeightAndOffset(RefPtr<UINode> node)
    {
        CHECK_NULL_RETURN(node, false);
        auto children = node->GetChildren();
        for (const auto& child : children) {
            if (AceType::InstanceOf<FrameNode>(child)) {
                auto frameNode = AceType::DynamicCast<FrameNode>(child);
                GetFrameNodeEstimateHeightOffset(frameNode);
            } else if (AceType::InstanceOf<LazyForEachNode>(child)) {
                return false;
            } else {
                GetEstimateHeightAndOffset(child);
            }
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
        return DEFAULT_ITEM_HEIGHT;
    }

    int32_t currentIndex_ = 0;
    int32_t targetIndex_ = 0;
    std::pair<float, float> targetPos_ = { 0.0f, 0.0f };
    float estimateHeight_ = 0.0f;
    float estimateOffset_ = 0.0f;
    float spaceWidth_ = 0.0f;

    float totalItemHeight_ = 0.0f;
    float totalItemCount_ = 0.0f;

    float groupedItemHeight_ = DEFAULT_ITEM_HEIGHT;
};
} // namespace OHOS::Ace::NG
#endif
