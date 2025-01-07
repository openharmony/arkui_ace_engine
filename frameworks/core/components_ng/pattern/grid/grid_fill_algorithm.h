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

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "core/components_ng/base/scroll_window_adapter.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/irregular/grid_irregular_filler.h"

namespace OHOS::Ace::NG {

class GridFillAlgorithm : public FillAlgorithm {
public:
    GridFillAlgorithm(const GridLayoutProperty& props, GridLayoutInfo& info) : props_(props), info_(info) {}

    RectF CalcMarkItemRect(const SizeF& viewPort, Axis axis, FrameNode* node, int32_t index,
        const std::optional<OffsetF>& slidingOffset) override;

    RectF CalcItemRectAfterMarkItem(
        const SizeF& viewPort, Axis axis, FrameNode* node, int32_t index, const RectF& markItem) override;

    RectF CalcItemRectBeforeMarkItem(
        const SizeF& viewPort, Axis axis, FrameNode* node, int32_t index, const RectF& markItem) override;

    void OnSlidingOffsetUpdate(float x, float y) override {}

    bool IsReady() const override
    {
        return true;
    }

    bool CanFillMore(const SizeF& scrollWindowSize, const RectF& markItemRect, FillDirection direction) override
    {
        // TODO: Axis::HORIZONTAL
        if (direction == FillDirection::START) {
            return !(
                LessOrEqual(markItemRect.Top(), -scrollWindowSize.Height()) && LessOrEqual(markItemRect.Left(), 0));
        }
        return !(GreatOrEqual(markItemRect.Bottom(), scrollWindowSize.Height() * 2) &&
                 GreatOrEqual(markItemRect.Right(), scrollWindowSize.Width()));
    }

    void PreFill(const SizeF& viewport, Axis axis, int32_t totalCnt) override;

private:
    const GridLayoutProperty& props_;
    GridLayoutInfo& info_;

    GridIrregularFiller::FillParameters params_;
};

} // namespace OHOS::Ace::NG