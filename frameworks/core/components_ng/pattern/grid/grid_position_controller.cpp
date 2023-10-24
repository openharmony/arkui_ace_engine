/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid/grid_position_controller.h"

#include "base/geometry/axis.h"
#include "base/utils/utils.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

void GridPositionController::JumpTo(int32_t index, bool /* smooth */, ScrollAlign align, int32_t /* source */)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto gridPattern = AceType::DynamicCast<GridPattern>(pattern);
    if (align == ScrollAlign::NONE) {
        align = ScrollAlign::AUTO;
    }
    gridPattern->StopAnimate();
    gridPattern->UpdateStartIndex(index, align);
}

void GridPositionController::ScrollBy(double pixelX, double pixelY, bool smooth)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto gridPattern = AceType::DynamicCast<GridPattern>(pattern);
    CHECK_NULL_VOID(gridPattern);
    auto offset = gridPattern->GetAxis() == Axis::VERTICAL ? pixelY : pixelX;
    gridPattern->ScrollBy(static_cast<float>(offset));
}

void GridPositionController::ScrollToEdge(ScrollEdgeType scrollEdgeType, bool /* smooth */)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto gridPattern = AceType::DynamicCast<GridPattern>(pattern);
    gridPattern->StopAnimate();
    if (scrollEdgeType == ScrollEdgeType::SCROLL_TOP) {
        gridPattern->UpdateStartIndex(0);
    } else if (scrollEdgeType == ScrollEdgeType::SCROLL_BOTTOM) {
        gridPattern->UpdateStartIndex(gridPattern->GetGridLayoutInfo().childrenCount_ - 1);
    }
}

void GridPositionController::ScrollPage(bool reverse, bool /* smooth */)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto gridPattern = AceType::DynamicCast<GridPattern>(pattern);
    if (gridPattern->GetGridLayoutInfo().axis_ != Axis::NONE) {
        gridPattern->ScrollPage(reverse);
    }
}

bool GridPositionController::IsAtEnd() const
{
    auto gridPattern = AceType::DynamicCast<GridPattern>(scroll_.Upgrade());
    CHECK_NULL_RETURN(gridPattern, false);
    return gridPattern->IsAtBottom();
}

Rect GridPositionController::GetItemRect(int32_t index) const
{
    auto gridPattern = AceType::DynamicCast<GridPattern>(scroll_.Upgrade());
    CHECK_NULL_RETURN(gridPattern, Rect());
    return gridPattern->GetItemRect(index);
}
} // namespace OHOS::Ace::NG
