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

#pragma once

#include <algorithm>
#include <cstdint>

#include "core/components_ng/base/fill_algorithm.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/irregular/grid_irregular_filler.h"

namespace OHOS::Ace::NG {

class GridFillAlgorithm : public FillAlgorithm {
    DECLARE_ACE_TYPE(GridFillAlgorithm, FillAlgorithm);

public:
    GridFillAlgorithm(const GridLayoutProperty& props, GridLayoutInfo& info) : props_(props), info_(info) {}

    void FillMarkItem(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index) override;

    void FillNext(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index) override;

    void FillPrev(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index) override;

    void OnSlidingOffsetUpdate(float delta) override;
    /* for parallel mode */
    bool OnSlidingOffsetUpdate(const SizeF& viewport, Axis axis, float delta) override;

    bool CanFillMore(Axis axis, const SizeF& scrollWindowSize, int32_t idx, FillDirection direction) override;

    void PreFill(const SizeF& viewport, Axis axis, int32_t totalCnt) override;

    void MarkJump() override
    {
        resetRangeOnJump_ = true;
    }

    int32_t GetMarkIndex() override
    {
        return info_.startIndex_;
    }

    std::pair<int32_t, int32_t> GetRange() const override
    {
        return { range_.startIdx, range_.endIdx };
    }

private:
    void Init(const SizeF& viewport, Axis axis, int32_t totalCnt);
    const GridLayoutProperty& props_;
    GridLayoutInfo& info_;

    struct LayoutRange {
        /**
         * @brief consume @c offset to adjust @c startLine when scrolling backward.
         * REQUIRES: @c lineHeights in range [row, startLine] are ready
         * @param gap gap between rows.
         */
        void AdjustBackward(const decltype(info_.lineHeightMap_)& lineHeights, float gap, int32_t firstRow);

        /**
         * @brief consume @c offset to adjust @c startLine when scrolling forward.
         * REQUIRES: @c lineHeights in range [startLine, endLine] are ready
         */
        void AdjustForward(const decltype(info_.lineHeightMap_)& lineHeights, float gap);

        std::string ToString() const
        {
            return "LayoutRange { startLine: " + std::to_string(startLine) + ", offset: " + std::to_string(offset) +
                   ", endLine: " + std::to_string(endLine) + ", startIdx: " + std::to_string(startIdx) +
                   ", endIdx: " + std::to_string(endIdx) + " }";
        }

        int32_t startLine = 0; // first line in viewport
        float offset = 0.0f;   // main-axis offset of the first line in viewport
        int32_t endLine = 0;   // last line in viewport
        int32_t startIdx = 0;  // only used in range mode
        int32_t endIdx = 0;    // only used in range mode
    };
    LayoutRange range_;
    GridIrregularFiller::FillParameters params_;

    bool resetRangeOnJump_ = false;
};

} // namespace OHOS::Ace::NG