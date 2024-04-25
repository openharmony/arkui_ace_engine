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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_BASE_H

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"
#include "core/components_ng/pattern/waterflow/water_flow_sections.h"

namespace OHOS::Ace::NG {
constexpr int32_t EMPTY_JUMP_INDEX = -2;

enum class WaterFlowLayoutMode;

class WaterFlowLayoutInfoBase : public AceType {
    DECLARE_ACE_TYPE(WaterFlowLayoutInfoBase, AceType);

public:
    WaterFlowLayoutInfoBase() = default;
    ~WaterFlowLayoutInfoBase() override = default;

    /* Factory method */
    static RefPtr<WaterFlowLayoutInfoBase> Create(WaterFlowLayoutMode mode);

    /* PURE GETTERs */
    virtual WaterFlowLayoutMode mode() const = 0;
    virtual float offset() const = 0;
    virtual int32_t firstIdx() const = 0; // for compatibility

    virtual void UpdateOffset(float delta) = 0;

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
    virtual bool ReachEnd(float prevPos) const = 0;

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

    virtual void Reset() = 0;

    // for compatibility
    virtual void InitSegments(const std::vector<WaterFlowSections::Section>& sections, int32_t start) {}
    // for compatibility
    virtual void UpdateStartIndex() {};

    bool itemStart_ = false;
    bool itemEnd_ = false;   // last item is partially in viewport
    bool offsetEnd_ = false; // last item's bottom is in viewport

    Axis axis_ = Axis::VERTICAL;

    int32_t jumpIndex_ = EMPTY_JUMP_INDEX;
    ScrollAlign align_ = ScrollAlign::START;
    std::optional<int32_t> targetIndex_;

    int32_t startIndex_ = 0;
    int32_t endIndex_ = -1;
    int32_t footerIndex_ = -1;

    float lastMainSize_ = 0.0f;

    // store offset for distributed migration
    float storedOffset_ = 0.0f;
    float restoreOffset_ = 0.0f;

    ACE_DISALLOW_COPY_AND_MOVE(WaterFlowLayoutInfoBase);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_BASE_H
