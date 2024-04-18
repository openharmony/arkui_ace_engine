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

#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/pattern/waterflow/water_flow_sections.h"
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
    float JumpToTargetAlign(const std::pair<float, float>& item) const;
    void JumpTo(const std::pair<float, float>& item);

    /**
     * @brief Get the Segment index of a FlowItem
     *
     * @param itemIdx
     * @return segment index.
     */
    int32_t GetSegment(int32_t itemIdx) const;

    /**
     * @brief Init data structures based on new WaterFlow Sections.
     *
     * @param sections vector of Sections info.
     * @param start index of the first modified section, all sections prior to [start] remain the same.
     */
    void InitSegments(const std::vector<WaterFlowSections::Section>& sections, int32_t start);

    /**
     * @brief Initialize margin of each section, along with segmentStartPos_, which depends on margin_.
     *
     * @param sections vector of Sections info.
     * @param scale for calculating margins in PX.
     * @param percentWidth for calculating margins in PX.
     */
    void InitMargins(
        const std::vector<WaterFlowSections::Section>& sections, const ScaleProperty& scale, float percentWidth);

    void ResetSegmentStartPos();

    /**
     * @brief Record a new FlowItem in ItemMap and update related data structures.
     *
     * @param idx index of FlowItem.
     * @param pos position of this FlowItem
     * @param height FlowItem height.
     */
    void RecordItem(int32_t idx, const FlowItemPosition& pos, float height);

    /**
     * @brief FInd the first item inside viewport in log_n time using endPosReverseMap_.
     *
     * @return index of the starting item.
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
     * @param itemIdx index of the current flow item.
     */
    void SetNextSegmentStartPos(int32_t itemIdx);

    /**
     * @brief Update member variables after measure.
     *
     * @param mainSize waterFlow length on the main axis.
     * @param overScroll whether overScroll is allowed. Might adjust offset if not.
     */
    void Sync(float mainSize, bool overScroll);

    Axis axis_ = Axis::VERTICAL;
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

    // Map structure: [crossIndex, [index, {mainOffset, itemMainSize}]],
    using ItemMap = std::map<int32_t, std::map<int32_t, std::pair<float, float>>>;

    std::vector<ItemMap> items_ { ItemMap() };

    struct ItemInfo;
    // quick access to FlowItem by index
    std::vector<ItemInfo> itemInfos_;

    /**
     * @brief pair = { item bottom position, item index }.
     * A strictly increasing array of item endPos to speed up startIndex solver.
     * Only add to this map when a new endPos is greater than the last one in array.
     */
    std::vector<std::pair<float, int32_t>> endPosArray_;

    // Stores the tail item index of each segment.
    std::vector<int32_t> segmentTails_;

    // margin of each segment
    std::vector<PaddingPropertyF> margins_;

    // Stores the start position of each segment.
    std::vector<float> segmentStartPos_ = { 0.0f };

    // K: item index; V: corresponding segment index
    mutable std::unordered_map<int32_t, int32_t> segmentCache_;

    void PrintWaterFlowItems() const;
};

struct WaterFlowLayoutInfo::ItemInfo {
    ItemInfo() = default;
    ItemInfo(int32_t cross, float offset, float size) : crossIdx(cross), mainOffset(offset), mainSize(size) {}
    bool operator==(const ItemInfo& other) const
    {
        return crossIdx == other.crossIdx && mainOffset == other.mainOffset && mainSize == other.mainSize;
    }

    int32_t crossIdx = 0;
    float mainOffset = 0.0f;
    float mainSize = 0.0f;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_H
