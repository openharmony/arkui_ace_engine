/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_position_map.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_ITEM_HEIGHT = 64.f;
}
class ListHeightOffsetCalculator {
public:
    ListHeightOffsetCalculator(const ListLayoutAlgorithm::PositionMap& itemPosition, float space, int32_t lanes,
        Axis axis, int32_t itemStartIndex);

    void CalculateListItemGroup(RefPtr<ListItemGroupPattern> listItemGroupPatten);

    void CalculateFrameNode(RefPtr<FrameNode> frameNode);

    void CalculatePosMapNode();

    int32_t GetPosMapStartIndex();

    int32_t GetPosMapEndIndex();

    void CalculateLazyForEachNodeWithPosMap(RefPtr<UINode> node);

    void CalculateUINode(RefPtr<UINode> node, bool checkStart);

    float GetLazyForEachIndexAverageHeight(RefPtr<UINode> node,
        int32_t startIndex, int32_t endIndex, bool &hasGroup);

    float CalculateOffset(RefPtr<UINode> node, float averageHeight);

    void CalculateLazyForEachNode(RefPtr<UINode> node);

    bool GetEstimateHeightAndOffset(RefPtr<UINode> node);

    float GetEstimateHeight() const
    {
        return estimateHeight_;
    }

    float GetEstimateOffset() const
    {
        return estimateOffset_;
    }

    void SetPosMap(const RefPtr<ListPositionMap>& posMap, bool syncPosMap = false);

private:
    float GetAverageItemHeight() const;

    static int32_t GetLines(int32_t lanes, int32_t count);

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
    float groupHeaderHeight_ = 0.0f;
    float groupFooterHeight_ = 0.0f;
    float groupSpaceWidth_ = 0.0f;

    int32_t lanes_ = 1;
    int32_t currLane_ = 0;
    float currRowHeight_ = 0.0f;

    const ListLayoutAlgorithm::PositionMap& itemPosition_;
    int32_t itemStartIndex_ = 0;
    RefPtr<ListPositionMap> posMap_;
    bool syncPosMap_ = false;
};
} // namespace OHOS::Ace::NG
#endif
