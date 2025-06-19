/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_BASE_H

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"
#include "core/components_ng/pattern/waterflow/water_flow_sections.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {

enum class WaterFlowLayoutMode;

class WaterFlowLayoutInfoBase : public AceType {
    DECLARE_ACE_TYPE(WaterFlowLayoutInfoBase, AceType);

public:
    static constexpr int32_t EMPTY_JUMP_INDEX = -2;

    WaterFlowLayoutInfoBase() = default;
    ~WaterFlowLayoutInfoBase() override = default;

    /* Factory method */
    static RefPtr<WaterFlowLayoutInfoBase> Create(WaterFlowLayoutMode mode);

    /* PURE GETTERs */
    virtual WaterFlowLayoutMode Mode() const = 0;
    virtual float Offset() const = 0;     // total offset of content
    virtual int32_t FirstIdx() const = 0; // for compatibility

    virtual void UpdateOffset(float delta) = 0;

    /**
     * @brief try calibrating total offset to an accurate value.
     *
     * @return amount of adjustment to total offset of content
     */
    virtual float CalibrateOffset() = 0;

    /**
     * @return estimated total content height.
     */
    virtual float EstimateTotalHeight() const = 0;

    /**
     * @brief Get which cross-axis lane the item is in.
     *
     * @param itemIndex
     * @return lane index
     */
    virtual int32_t GetCrossIndex(int32_t itemIndex) const = 0;

    // implementation of WaterFlowPattern::GetOverScrollOffset
    // returns the portion of [delta] that's in overScroll range
    virtual OverScrollOffset GetOverScrolledDelta(float delta) const = 0;

    /**
     * @param mainSize of viewport.
     * @param delta change in content offset.
     * @return amount of overScroll (distance to edge) after applying delta.
     */
    virtual float CalcOverScroll(float mainSize, float delta) const = 0;

    /**
     * @brief Check if WaterFlow just reached content top from the recent layout.
     * For triggering events.
     *
     * @param prevPos previous layout position.
     * @param firstLayout check this to emit ReachStart on the initial layout.
     * @return true if current position just reached content top.
     */
    virtual bool ReachStart(float prevPos, bool firstLayout) const = 0;
    /**
     * @brief Check if WaterFlow just reached content bottom from the recent layout.
     * For triggering events.
     *
     * @param prevPos previous layout position.
     * @return true if current position just reached content bottom.
     */
    virtual bool ReachEnd(float prevPos, bool firstLayout) const = 0;

    /**
     * @note should take unconsumed delta into account.
     */
    virtual bool OutOfBounds() const = 0;

    /**
     * @return total height of all recorded items.
     */
    virtual float GetContentHeight() const = 0;

    /**
     * @brief Get target item's position in order to perform scrollTo animation.
     *
     * @param idx item's index.
     * @param crossIdx item's cross-axis lane index.
     * @return absolute position to scroll to.
     */
    virtual float CalcTargetPosition(int32_t idx, int32_t crossIdx) const = 0;

    /**
     * @return change in position, comparing to [prevPos]
     */
    virtual float GetDelta(float prevPos) const = 0;

    virtual int32_t GetMainCount() const = 0;
    virtual int32_t GetCrossCount() const = 0;

    /* ======== provide position info for spring effect animation ========= */
    virtual float CurrentPos() const = 0;
    /**
     * @return final position to bounce back to after over-scrolling from top.
     */
    virtual float TopFinalPos() const = 0;
    /**
     * @param viewHeight height of the viewport.
     * @return final position to bounce back to after over-scrolling from bottom.
     */
    virtual float BottomFinalPos(float viewHeight) const = 0;
    /* ========================================== */

    virtual void Reset() = 0;
    virtual void ResetFooter() = 0;

    virtual bool IsAtTopWithDelta() = 0;
    virtual bool IsAtBottomWithDelta() = 0;

    // for compatibility
    virtual void UpdateStartIndex() {};

    /**
     * @brief Check if the layout is misaligned.
     *
     * If we jump and scroll back to top, the staring items might not be aligned with the top boundary.
     * @return true if 1. any lane misaligned with top boundary.
     *                 2. the first item is not in the first lane.
     */
    virtual bool IsMisaligned() const = 0;

    /**
     * @brief Initialize variables based on incoming section data.
     *
     * @param sections section data.
     * @param start first updated section.
     */
    virtual void InitSegments(const std::vector<WaterFlowSections::Section>& sections, int32_t start) = 0;

    /**
     * @brief Get the Segment index of a FlowItem
     *
     * @param itemIdx
     * @return segment index, guaranteed within range [0, total sections).
     */
    int32_t GetSegment(int32_t itemIdx) const;

    // convert FlowItem's index to children node index.
    inline int32_t NodeIdx(int32_t idx) const
    {
        return idx + footerIndex_ + 1;
    }

    /**
     * @brief obtain true total number of FlowItems by filtering out the footer node.
     */
    inline int32_t ItemCnt(int32_t childrenCount) const
    {
        return childrenCount - footerIndex_ - 1;
    }

    /**
     * @brief Initialize margin of each section, along with segmentStartPos_, which depends on margin_.
     *
     * @param sections vector of Sections info.
     * @param scale for calculating margins in PX.
     * @param percentWidth for calculating margins in PX.
     */
    void InitMargins(
        const std::vector<WaterFlowSections::Section>& sections, const ScaleProperty& scale, float percentWidth);

    virtual void NotifyDataChange(int32_t index, int32_t count) = 0;
    virtual void NotifySectionChange(int32_t index) = 0;
    virtual void InitSegmentsForKeepPositionMode(const std::vector<WaterFlowSections::Section>& sections,
        const std::vector<WaterFlowSections::Section>& prevSections, int32_t start) = 0;

    void UpdateDefaultCachedCount();

    int32_t GetChildrenCount() const
    {
        return firstRepeatCount_ > 0 ? firstRepeatCount_ : childrenCount_;
    }

    bool itemStart_ = false;
    /**
     * @brief last item is partially in viewport.
     * With footer, footer should be considered the last item.
     */
    bool itemEnd_ = false;
    bool offsetEnd_ = false; // last item's bottom is in viewport
    bool isDataValid_ = true;

    Axis axis_ = Axis::VERTICAL;

    int32_t jumpIndex_ = EMPTY_JUMP_INDEX;
    ScrollAlign align_ = ScrollAlign::START;
    std::optional<int32_t> targetIndex_;
    std::optional<float> extraOffset_;
    int32_t jumpForRecompose_ = EMPTY_JUMP_INDEX;

    int32_t startIndex_ = 0;
    int32_t endIndex_ = -1;
    int32_t footerIndex_ = -1;

    float lastMainSize_ = 0.0f;

    // store offset for distributed migration
    float storedOffset_ = 0.0f;
    float restoreOffset_ = 0.0f;

    float expandHeight_ = 0.0f;

    // Stores the tail item index of each segment.
    std::vector<int32_t> segmentTails_;
    // K: item index; V: corresponding segment index
    mutable std::unordered_map<int32_t, int32_t> segmentCache_;
    // margin of each segment
    std::vector<PaddingPropertyF> margins_;
    // default cached count
    int32_t defCachedCount_ = 1;

    int32_t repeatDifference_ = 0;
    int32_t firstRepeatCount_ = 0;
    int32_t childrenCount_ = 0;

    // unfold the LazyVGrid during the position calculation.
    bool duringPositionCalc_ = false;

    bool measureInNextFrame_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(WaterFlowLayoutInfoBase);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_BASE_H
