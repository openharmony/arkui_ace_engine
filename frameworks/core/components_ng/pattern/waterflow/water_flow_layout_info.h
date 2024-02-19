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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_H

#include <cstdint>
#include <map>
#include <optional>
#include <sstream>

#include "base/utils/utils.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {
struct FlowItemIndex {
    int32_t crossIndex = 0;
    int32_t lastItemIndex = 0;
};

struct FlowItemPosition {
    int32_t crossIndex = 0;
    float startMainPos = 0;
};

constexpr int32_t EMPTY_JUMP_INDEX = -2;

class WaterFlowLayoutInfo {
public:
    int32_t GetCrossIndex(int32_t itemIndex) const;
    void UpdateStartIndex();
    int32_t GetEndIndexByOffset(float offset) const;
    float GetMaxMainHeight() const;
    float GetContentHeight() const;
    bool IsAllCrossReachEnd(float mainSize) const;

    /**
     * @brief Get the next available cross index to place a new item.
     * 
     * @param segmentIdx index of the WaterFlow segment.
     * @return FlowItemIndex 
     */
    FlowItemIndex GetCrossIndexForNextItem(int32_t segmentIdx) const;

    float GetMainHeight(int32_t crossIndex, int32_t itemIndex) const;
    float GetStartMainPos(int32_t crossIndex, int32_t itemIndex) const;
    void Reset();
    void Reset(int32_t resetFrom);
    int32_t GetCrossCount() const;
    int32_t GetMainCount() const;
    void ClearCacheAfterIndex(int32_t currentIndex);

    bool ReachStart(float prevOffset, bool firstLayout) const;
    bool ReachEnd(float prevOffset) const;

    int32_t GetSegment(int32_t itemIdx) const;

    void AddItemToCache(int32_t idx, float startPos, float height);

    /**
     * @brief FInd the first item inside viewport in log_n time using endPosReverseMap_.
     * 
     * @return index of the item. 
     */
    int32_t FastSolveStartIndex() const;

    /**
     * @brief Find the last item inside viewport in log_n time using itemInfos_.
     * 
     * @param mainSize main-axis length of viewport.
     * @return index of the item.
     */
    int32_t FastSolveEndIndex(float mainSize) const;

    /**
     * @brief Calculate and set the start position of next segment after filling the tail item of the current segment.
     * 
     * @param margins margin of each segment.
     * @param itemIdx index of the current flow item.
     */
    void SetNextSegmentStartPos(const std::vector<PaddingPropertyF>& margins, int32_t itemIdx);

    /**
     * @brief Update member variables after measure.
     * 
     * @param mainSize waterFlow length on the main axis.
     * @param bottomMargin of the last FlowItem segment.
     * @param overScroll whether overScroll is allowed. Might adjust offset if not.
     */
    void Sync(float mainSize, float bottomMargin, bool overScroll);

    float currentOffset_ = 0.0f;
    float prevOffset_ = 0.0f;
    float lastMainSize_ = 0.0f;
    // 0.0f until itemEnd_ is true
    float maxHeight_ = 0.0f;
    // store offset for distributed migration
    float storedOffset_ = 0.0f;
    float restoreOffset_ = 0.0f;

    bool itemStart_ = false;
    bool itemEnd_ = false;   // last item is partially in viewport
    bool offsetEnd_ = false; // last item's bottom is in viewport

    int32_t jumpIndex_ = EMPTY_JUMP_INDEX;

    ScrollAlign align_ = ScrollAlign::START;

    int32_t startIndex_ = 0;
    int32_t endIndex_ = -1;
    int32_t footerIndex_ = -1;
    int32_t childrenCount_ = 0;

    // first index for onScrollIndex
    int32_t firstIndex_ = 0;
    std::optional<int32_t> targetIndex_;

    // (mainOffset, itemMainSize)
    using ItemInfo = std::pair<float, float>;
    // Map structure: [crossIndex, [index, ItemInfo]],
    using ItemMap = std::map<int32_t, std::map<int32_t, ItemInfo>>;

    std::vector<ItemMap> items_ { ItemMap() };

    // quick access to item info, ignores crossIndex and segments
    std::map<int32_t, ItemInfo> itemInfos_;

    /**
     * @brief pair = { item bottom position, item index }.
     * A strictly increasing array of item endPos to speed up startIndex solver.
     * Only add to this map when a new endPos is greater than the last one in array.
     */
    std::vector<std::pair<float, int32_t>> endPosArray_;

    // Stores the tail item index of each segment.
    std::vector<int32_t> segmentTails_;

    // Stores the start position of each segment.
    std::vector<float> segmentStartPos_ = { 0.0f };

    // K: item index; V: corresponding segment index
    mutable std::unordered_map<int32_t, int32_t> segmentCache_;

    void PrintWaterFlowItems() const
    {
        for (const auto& [key1, map1] : items_[0]) {
            std::stringstream ss;
            ss << key1 << ": {";
            for (const auto& [key2, pair] : map1) {
                ss << key2 << ": (" << pair.first << ", " << pair.second << ")";
                if (&pair != &map1.rbegin()->second) {
                    ss << ", ";
                }
            }
            ss << "}";
            LOGI("%{public}s", ss.str().c_str());
        }
    }
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_H